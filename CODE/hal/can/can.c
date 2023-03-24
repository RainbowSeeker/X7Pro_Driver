#include "can.h"

#define CAN_LOCK(can)   os_mutex_take(&(can->lock), OS_WAITING_FOREVER)
#define CAN_UNLOCK(can) os_mutex_release(&(can->lock))

static err_t can_init(struct device *dev)
{
    err_t result = E_OK;
    struct can_device *can;

    ASSERT(dev != NULL);
    can = (struct can_device *)dev;

    /* initialize rx/tx */
    can->can_rx = NULL;
    can->can_tx = NULL;
#ifdef RT_CAN_USING_HDR
    can->hdr = NULL;
#endif

    /* apply configuration */
    if (can->ops->configure)
        result = can->ops->configure(can, &can->config);
    else
        result = -E_NOSYS;

    return result;
}

/*
 * can interrupt routines
 */
inline int _can_int_rx(struct can_device *can, struct can_msg *data, int msgs)
{
    int size;
    struct can_rx_fifo *rx_fifo;
    ASSERT(can != NULL);
    size = msgs;

    rx_fifo = (struct can_rx_fifo *) can->can_rx;
    ASSERT(rx_fifo != NULL);

    /* read from software FIFO */
    while (msgs)
    {
        base_t level;
#ifdef RT_CAN_USING_HDR
        int8_t hdr;
#endif /*RT_CAN_USING_HDR*/
        struct can_msg_list *listmsg = NULL;

        /* disable interrupt */
        level = os_hw_interrupt_disable();
#ifdef RT_CAN_USING_HDR
        hdr = data->hdr;

        if (hdr >= 0 && can->hdr && hdr < can->config.maxhdr && !list_isempty(&can->hdr[hdr].list))
        {
            listmsg = list_entry(can->hdr[hdr].list.next, struct can_msg_list, hdrlist);
            list_remove(&listmsg->list);
            list_remove(&listmsg->hdrlist);
            if (can->hdr[hdr].msgs)
            {
                can->hdr[hdr].msgs--;
            }
            listmsg->owner = NULL;
        }
        else if (hdr == -1)
#endif /*RT_CAN_USING_HDR*/
        {
            if (!list_isempty(&rx_fifo->uselist))
            {
                listmsg = list_entry(rx_fifo->uselist.next, struct can_msg_list, list);
                list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
                list_remove(&listmsg->hdrlist);
                if (listmsg->owner != NULL && listmsg->owner->msgs)
                {
                    listmsg->owner->msgs--;
                }
                listmsg->owner = NULL;
#endif /*RT_CAN_USING_HDR*/
            }
            else
            {
                /* no data, enable interrupt and break out */
                os_hw_interrupt_enable(level);
                break;
            }
        }

        /* enable interrupt */
        os_hw_interrupt_enable(level);
        if (listmsg != NULL)
        {
            memcpy(data, &listmsg->data, sizeof(struct can_msg));

            level = os_hw_interrupt_disable();
            list_insert_before(&rx_fifo->freelist, &listmsg->list);
            rx_fifo->freenumbers++;
            ASSERT(rx_fifo->freenumbers <= can->config.msgboxsz);
            os_hw_interrupt_enable(level);

            listmsg = NULL;
        }
        else
        {
            break;
        }
        data ++;
        msgs -= sizeof(struct can_msg);
    }

    return (size - msgs);
}

inline int _can_int_tx(struct can_device *can, const struct can_msg *data, int msgs)
{
    int size;
    struct can_tx_fifo *tx_fifo;

    ASSERT(can != NULL);

    size = msgs;
    tx_fifo = (struct can_tx_fifo *) can->can_tx;
    ASSERT(tx_fifo != NULL);

    while (msgs)
    {
        base_t level;
        uint32_t no;
        uint32_t result;
        struct can_sndbxinx_list *tx_tosnd = NULL;

        os_sem_take(&(tx_fifo->sem), OS_WAITING_FOREVER);
        level = os_hw_interrupt_disable();
        tx_tosnd = list_entry(tx_fifo->freelist.next, struct can_sndbxinx_list, list);
        ASSERT(tx_tosnd != NULL);
        list_remove(&tx_tosnd->list);
        os_hw_interrupt_enable(level);

        no = ((uint32_t)tx_tosnd - (uint32_t)tx_fifo->buffer) / sizeof(struct can_sndbxinx_list);
        tx_tosnd->result = CAN_SND_RESULT_WAIT;
        if (can->ops->sendmsg(can, data, no) != E_OK)
        {
            /* send failed. */
            level = os_hw_interrupt_disable();
            list_insert_after(&tx_fifo->freelist, &tx_tosnd->list);
            os_hw_interrupt_enable(level);
            os_sem_release(&(tx_fifo->sem));
            continue;
        }

        can->status.sndchange = 1;
        completion_wait(&(tx_tosnd->completion), OS_WAITING_FOREVER);

        level = os_hw_interrupt_disable();
        result = tx_tosnd->result;
        if (!list_isempty(&tx_tosnd->list))
        {
            list_remove(&tx_tosnd->list);
        }
        list_insert_before(&tx_fifo->freelist, &tx_tosnd->list);
        os_hw_interrupt_enable(level);
        os_sem_release(&(tx_fifo->sem));

        if (result == CAN_SND_RESULT_OK)
        {
            level = os_hw_interrupt_disable();
            can->status.sndpkg++;
            os_hw_interrupt_enable(level);

            data ++;
            msgs -= sizeof(struct can_msg);
            if (!msgs) break;
        }
        else
        {
            level = os_hw_interrupt_disable();
            can->status.dropedsndpkg++;
            os_hw_interrupt_enable(level);
            break;
        }
    }

    return (size - msgs);
}

inline int _can_int_tx_priv(struct can_device *can, const struct can_msg *data, int msgs)
{
    int size;
    base_t level;
    uint32_t no, result;
    struct can_tx_fifo *tx_fifo;

    ASSERT(can != NULL);

    size = msgs;
    tx_fifo = (struct can_tx_fifo *) can->can_tx;
    ASSERT(tx_fifo != NULL);

    while (msgs)
    {
        no = data->priv;
        if (no >= can->config.sndboxnumber)
        {
            break;
        }

        level = os_hw_interrupt_disable();
        if ((tx_fifo->buffer[no].result != CAN_SND_RESULT_OK))
        {
            os_hw_interrupt_enable(level);

            completion_wait(&(tx_fifo->buffer[no].completion), OS_WAITING_FOREVER);
            continue;
        }
        tx_fifo->buffer[no].result = CAN_SND_RESULT_WAIT;
        os_hw_interrupt_enable(level);

        if (can->ops->sendmsg(can, data, no) != E_OK)
        {
            continue;
        }
        can->status.sndchange = 1;
        completion_wait(&(tx_fifo->buffer[no].completion), OS_WAITING_FOREVER);

        result = tx_fifo->buffer[no].result;
        if (result == CAN_SND_RESULT_OK)
        {
            level = os_hw_interrupt_disable();
            can->status.sndpkg++;
            os_hw_interrupt_enable(level);
            data ++;
            msgs -= sizeof(struct can_msg);
            if (!msgs) break;
        }
        else
        {
            level = os_hw_interrupt_disable();
            can->status.dropedsndpkg++;
            os_hw_interrupt_enable(level);
            break;
        }
    }

    return (size - msgs);
}

static err_t can_open(struct device *dev, uint16_t oflag)
{
    struct can_device *can;
    char tmpname[16];
    ASSERT(dev != NULL);
    can = (struct can_device *)dev;

    CAN_LOCK(can);

    /* get open flags */
    dev->open_flag = oflag & 0xff;
    if (can->can_rx == NULL)
    {
        if (oflag & DEVICE_FLAG_INT_RX)
        {
            int i = 0;
            struct can_rx_fifo *rx_fifo;

            rx_fifo = (struct can_rx_fifo *) malloc(sizeof(struct can_rx_fifo) +
                      can->config.msgboxsz * sizeof(struct can_msg_list));
            ASSERT(rx_fifo != NULL);

            rx_fifo->buffer = (struct can_msg_list *)(rx_fifo + 1);
            memset(rx_fifo->buffer, 0, can->config.msgboxsz * sizeof(struct can_msg_list));
            list_init(&rx_fifo->freelist);
            list_init(&rx_fifo->uselist);
            rx_fifo->freenumbers = can->config.msgboxsz;
            for (i = 0;  i < can->config.msgboxsz; i++)
            {
                list_insert_before(&rx_fifo->freelist, &rx_fifo->buffer[i].list);
#ifdef RT_CAN_USING_HDR
                list_init(&rx_fifo->buffer[i].hdrlist);
                rx_fifo->buffer[i].owner = NULL;
#endif
            }
            can->can_rx = rx_fifo;

            dev->open_flag |= DEVICE_FLAG_INT_RX;
            /* open can rx interrupt */
            can->ops->control(can, DEVICE_CTRL_SET_INT, (void *)DEVICE_FLAG_INT_RX);
        }
    }

    if (can->can_tx == NULL)
    {
        if (oflag & DEVICE_FLAG_INT_TX)
        {
            int i = 0;
            struct can_tx_fifo *tx_fifo;

            tx_fifo = (struct can_tx_fifo *) malloc(sizeof(struct can_tx_fifo) +
                      can->config.sndboxnumber * sizeof(struct can_sndbxinx_list));
            ASSERT(tx_fifo != NULL);

            tx_fifo->buffer = (struct can_sndbxinx_list *)(tx_fifo + 1);
            memset(tx_fifo->buffer, 0,
                    can->config.sndboxnumber * sizeof(struct can_sndbxinx_list));
            list_init(&tx_fifo->freelist);
            for (i = 0;  i < can->config.sndboxnumber; i++)
            {
                list_insert_before(&tx_fifo->freelist, &tx_fifo->buffer[i].list);
                completion_init(&(tx_fifo->buffer[i].completion));
                tx_fifo->buffer[i].result = CAN_SND_RESULT_OK;
            }

            sprintf(tmpname, "%stl", dev->name);
            os_sem_init(&(tx_fifo->sem), tmpname, can->config.sndboxnumber);
            can->can_tx = tx_fifo;

            dev->open_flag |= DEVICE_FLAG_INT_TX;
            /* open can tx interrupt */
            can->ops->control(can, DEVICE_CTRL_SET_INT, (void *)DEVICE_FLAG_INT_TX);
        }
    }

    can->ops->control(can, DEVICE_CTRL_SET_INT, (void *)DEVICE_CAN_INT_ERR);

#ifdef RT_CAN_USING_HDR
    if (can->hdr == NULL)
    {
        int i = 0;
        struct can_hdr *phdr;

        phdr = (struct can_hdr *) malloc(can->config.maxhdr * sizeof(struct can_hdr));
        ASSERT(phdr != NULL);
        memset(phdr, 0, can->config.maxhdr * sizeof(struct can_hdr));
        for (i = 0;  i < can->config.maxhdr; i++)
        {
            list_init(&phdr[i].list);
        }

        can->hdr = phdr;
    }
#endif

    if (!can->timerinitflag)
    {
        can->timerinitflag = 1;

        os_timer_start(&can->timer);
    }

    CAN_UNLOCK(can);

    return E_OK;
}

static err_t can_close(struct device *dev)
{
    struct can_device *can;

    ASSERT(dev != NULL);
    can = (struct can_device *)dev;

    CAN_LOCK(can);

    /* this device has more reference count */
    if (dev->ref_count > 1)
    {
        CAN_UNLOCK(can);
        return E_OK;
    }

    if (can->timerinitflag)
    {
        can->timerinitflag = 0;

        os_timer_stop(&can->timer);
    }

    can->status_indicate.ind = NULL;
    can->status_indicate.args = NULL;

#ifdef RT_CAN_USING_HDR
    if (can->hdr != NULL)
    {
        free(can->hdr);
        can->hdr = NULL;
    }
#endif

    if (dev->open_flag & DEVICE_FLAG_INT_RX)
    {
        struct can_rx_fifo *rx_fifo;

        rx_fifo = (struct can_rx_fifo *)can->can_rx;
        ASSERT(rx_fifo != NULL);

        free(rx_fifo);
        dev->open_flag &= ~DEVICE_FLAG_INT_RX;
        can->can_rx = NULL;
        /* clear can rx interrupt */
        can->ops->control(can, DEVICE_CTRL_CLR_INT, (void *)DEVICE_FLAG_INT_RX);
    }

    if (dev->open_flag & DEVICE_FLAG_INT_TX)
    {
        struct can_tx_fifo *tx_fifo;

        tx_fifo = (struct can_tx_fifo *)can->can_tx;
        ASSERT(tx_fifo != NULL);

        os_sem_detach(&(tx_fifo->sem));
        free(tx_fifo);
        dev->open_flag &= ~DEVICE_FLAG_INT_TX;
        can->can_tx = NULL;
        /* clear can tx interrupt */
        can->ops->control(can, DEVICE_CTRL_CLR_INT, (void *)DEVICE_FLAG_INT_TX);
    }

    can->ops->control(can, DEVICE_CTRL_CLR_INT, (void *)DEVICE_CAN_INT_ERR);

    CAN_UNLOCK(can);

    return E_OK;
}

static size_t can_read(struct device *dev,
                             off_t          pos,
                             void             *buffer,
                             size_t         size)
{
    struct can_device *can;

    ASSERT(dev != NULL);
    if (size == 0) return 0;

    can = (struct can_device *)dev;

    if ((dev->open_flag & DEVICE_FLAG_INT_RX) && (dev->ref_count > 0))
    {
        return _can_int_rx(can, buffer, size);
    }

    return 0;
}

static size_t can_write(struct device *dev,
                              off_t          pos,
                              const void       *buffer,
                              size_t         size)
{
    struct can_device *can;

    ASSERT(dev != NULL);
    if (size == 0) return 0;

    can = (struct can_device *)dev;

    if ((dev->open_flag & DEVICE_FLAG_INT_TX) && (dev->ref_count > 0))
    {
        if (can->config.privmode)
        {
            return _can_int_tx_priv(can, buffer, size);
        }
        else
        {
            return _can_int_tx(can, buffer, size);
        }
    }
    return 0;
}

static err_t can_control(struct device *dev,
                               int              cmd,
                               void             *args)
{
    struct can_device *can;
    err_t res;

    res = E_OK;
    ASSERT(dev != NULL);
    can = (struct can_device *)dev;

    switch (cmd)
    {
    case DEVICE_CTRL_SUSPEND:
        /* suspend device */
        dev->flag |= DEVICE_FLAG_SUSPENDED;
        break;

    case DEVICE_CTRL_RESUME:
        /* resume device */
        dev->flag &= ~DEVICE_FLAG_SUSPENDED;
        break;

    case DEVICE_CTRL_CONFIG:
        /* configure device */
        res = can->ops->configure(can, (struct can_configure *)args);
        break;

    case CAN_CMD_SET_PRIV:
        /* configure device */
        if ((uint32_t)args != can->config.privmode)
        {
            int i;
            base_t level;
            struct can_tx_fifo *tx_fifo;

            res = can->ops->control(can, cmd, args);
            if (res != E_OK) return res;
            tx_fifo = (struct can_tx_fifo *) can->can_tx;
            if (can->config.privmode)
            {
                for (i = 0;  i < can->config.sndboxnumber; i++)
                {
                    level = os_hw_interrupt_disable();
                    if(list_isempty(&tx_fifo->buffer[i].list))
                    {
                        os_sem_release(&(tx_fifo->sem));
                    }
                    else
                    {
                        list_remove(&tx_fifo->buffer[i].list);
                    }
                    os_hw_interrupt_enable(level);
                }

            }
            else
            {
                for (i = 0;  i < can->config.sndboxnumber; i++)
                {
                    level = os_hw_interrupt_disable();
                    if (tx_fifo->buffer[i].result == CAN_SND_RESULT_OK)
                    {
                        list_insert_before(&tx_fifo->freelist, &tx_fifo->buffer[i].list);
                    }
                    os_hw_interrupt_enable(level);
                }
            }
        }
        break;

    case CAN_CMD_SET_STATUS_IND:
        can->status_indicate.ind = ((can_status_ind_type_t)args)->ind;
        can->status_indicate.args = ((can_status_ind_type_t)args)->args;
        break;

#ifdef RT_CAN_USING_HDR
    case RT_CAN_CMD_SET_FILTER:
        res = can->ops->control(can, cmd, args);
        if (res != E_OK || can->hdr == NULL)
        {
            return res;
        }

        struct can_filter_config *pfilter;
        struct can_filter_item *pitem;
        uint32_t count;
        base_t level;

        pfilter = (struct can_filter_config *)args;
        ASSERT(pfilter);
        count = pfilter->count;
        pitem = pfilter->items;
        if (pfilter->actived)
        {
            while (count)
            {
                if (pitem->hdr >= can->config.maxhdr || pitem->hdr < 0)
                {
                    count--;
                    pitem++;
                    continue;
                }

                level = os_hw_interrupt_disable();
                if (!can->hdr[pitem->hdr].connected)
                {
                    os_hw_interrupt_enable(level);
                    memcpy(&can->hdr[pitem->hdr].filter, pitem,
                              sizeof(struct can_filter_item));
                    level = os_hw_interrupt_disable();
                    can->hdr[pitem->hdr].connected = 1;
                    can->hdr[pitem->hdr].msgs = 0;
                    list_init(&can->hdr[pitem->hdr].list);
                }
                os_hw_interrupt_enable(level);

                count--;
                pitem++;
            }
        }
        else
        {
            while (count)
            {
                if (pitem->hdr >= can->config.maxhdr || pitem->hdr < 0)
                {
                    count--;
                    pitem++;
                    continue;
                }
                level = os_hw_interrupt_disable();

                if (can->hdr[pitem->hdr].connected)
                {
                    can->hdr[pitem->hdr].connected = 0;
                    can->hdr[pitem->hdr].msgs = 0;
                    if (!list_isempty(&can->hdr[pitem->hdr].list))
                    {
                        list_remove(can->hdr[pitem->hdr].list.next);
                    }
                    os_hw_interrupt_enable(level);
                    memset(&can->hdr[pitem->hdr].filter, 0,
                              sizeof(struct can_filter_item));
                }
                else
                {
                    os_hw_interrupt_enable(level);
                }
                count--;
                pitem++;
            }
        }
        break;
#endif /*RT_CAN_USING_HDR*/
#ifdef RT_CAN_USING_BUS_HOOK
    case RT_CAN_CMD_SET_BUS_HOOK:
        can->bus_hook = (can_bus_hook) args;
        break;
#endif /*RT_CAN_USING_BUS_HOOK*/
    default :
        /* control device */
        if (can->ops->control != NULL)
        {
            res = can->ops->control(can, cmd, args);
        }
        else
        {
            res = -E_NOSYS;
        }
        break;
    }

    return res;
}

/*
 * can timer
 */
static void cantimeout(void *tmr,void *arg)
{
    can_t can;

    can = (can_t)arg;
    ASSERT(can);
    device_control((device_t)can, CAN_CMD_GET_STATUS, (void *)&can->status);

    if (can->status_indicate.ind != NULL)
    {
        can->status_indicate.ind(can, can->status_indicate.args);
    }
#ifdef RT_CAN_USING_BUS_HOOK
    if(can->bus_hook)
    {
        can->bus_hook(can);
    }
#endif /*RT_CAN_USING_BUS_HOOK*/
    if (can->timerinitflag == 1)
    {
        can->timerinitflag = 0xFF;
    }
}

#ifdef RT_USING_DEVICE_OPS
const static struct device_ops can_device_ops =
{
    can_init,
    can_open,
    can_close,
    can_read,
    can_write,
    can_control
};
#endif

/*
 * can register
 */
err_t hw_can_register(struct can_device    *can,
                            const char              *name,
                            const struct can_ops *ops,
                            void                    *data)
{
    struct device *device;
    ASSERT(can != NULL);

    device = &(can->parent);

    device->type        = Device_Class_CAN;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;
#ifdef RT_CAN_USING_HDR
    can->hdr            = NULL;
#endif
    can->can_rx         = NULL;
    can->can_tx         = NULL;
    os_mutex_init(&can->lock, "can");

#ifdef RT_CAN_USING_BUS_HOOK
    can->bus_hook       = NULL;
#endif /*RT_CAN_USING_BUS_HOOK*/

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &can_device_ops;
#else
    device->init        = can_init;
    device->open        = can_open;
    device->close       = can_close;
    device->read        = can_read;
    device->write       = can_write;
    device->control     = can_control;
#endif
    can->ops            = ops;

    can->status_indicate.ind  = NULL;
    can->status_indicate.args = NULL;
    memset(&can->status, 0, sizeof(can->status));

    device->user_data   = data;

    can->timerinitflag  = 0;
    os_timer_init(&can->timer,
                  name,
                  cantimeout,
                  (void *)can,
                  can->config.ticks,
                  TIMER_TYPE_PERIODIC);
    /* register a character device */
    return device_register(device, name, DEVICE_FLAG_RDWR);
}

/* ISR for can interrupt */
void hw_can_isr(struct can_device *can, int event)
{
    switch (event & 0xff)
    {
    case CAN_EVENT_RXOF_IND:
    {
        base_t level;
        level = os_hw_interrupt_disable();
        can->status.dropedrcvpkg++;
        os_hw_interrupt_enable(level);
    }
    case CAN_EVENT_RX_IND:
    {
        struct can_msg tmpmsg;
        struct can_rx_fifo *rx_fifo;
        struct can_msg_list *listmsg = NULL;
#ifdef RT_CAN_USING_HDR
        int8_t hdr;
#endif
        int ch = -1;
        base_t level;
        uint32_t no;

        rx_fifo = (struct can_rx_fifo *)can->can_rx;
        ASSERT(rx_fifo != NULL);
        /* interrupt mode receive */
        ASSERT(can->parent.open_flag & DEVICE_FLAG_INT_RX);

        no = event >> 8;
        ch = can->ops->recvmsg(can, &tmpmsg, no);
        if (ch == -1) break;

        /* disable interrupt */
        level = os_hw_interrupt_disable();
        can->status.rcvpkg++;
        can->status.rcvchange = 1;
        if (!list_isempty(&rx_fifo->freelist))
        {
            listmsg = list_entry(rx_fifo->freelist.next, struct can_msg_list, list);
            list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
            list_remove(&listmsg->hdrlist);
            if (listmsg->owner != NULL && listmsg->owner->msgs)
            {
                listmsg->owner->msgs--;
            }
            listmsg->owner = NULL;
#endif /*RT_CAN_USING_HDR*/
            ASSERT(rx_fifo->freenumbers > 0);
            rx_fifo->freenumbers--;
        }
        else if (!list_isempty(&rx_fifo->uselist))
        {
            listmsg = list_entry(rx_fifo->uselist.next, struct can_msg_list, list);
            can->status.dropedrcvpkg++;
            list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
            list_remove(&listmsg->hdrlist);
            if (listmsg->owner != NULL && listmsg->owner->msgs)
            {
                listmsg->owner->msgs--;
            }
            listmsg->owner = NULL;
#endif
        }
        /* enable interrupt */
        os_hw_interrupt_enable(level);

        if (listmsg != NULL)
        {
            memcpy(&listmsg->data, &tmpmsg, sizeof(struct can_msg));
            level = os_hw_interrupt_disable();
            list_insert_before(&rx_fifo->uselist, &listmsg->list);
#ifdef RT_CAN_USING_HDR
            hdr = tmpmsg.hdr;
            if (can->hdr != NULL)
            {
                ASSERT(hdr < can->config.maxhdr && hdr >= 0);
                if (can->hdr[hdr].connected)
                {
                    list_insert_before(&can->hdr[hdr].list, &listmsg->hdrlist);
                    listmsg->owner = &can->hdr[hdr];
                    can->hdr[hdr].msgs++;
                }

            }
#endif
            os_hw_interrupt_enable(level);
        }

        /* invoke callback */
#ifdef RT_CAN_USING_HDR
        if (can->hdr != NULL && can->hdr[hdr].connected && can->hdr[hdr].filter.ind)
        {
            size_t rx_length;
            ASSERT(hdr < can->config.maxhdr && hdr >= 0);

            level = os_hw_interrupt_disable();
            rx_length = can->hdr[hdr].msgs * sizeof(struct can_msg);
            os_hw_interrupt_enable(level);
            if (rx_length)
            {
                can->hdr[hdr].filter.ind(&can->parent, can->hdr[hdr].filter.args, hdr, rx_length);
            }
        }
        else
#endif
        {
            if (can->parent.rx_indicate != NULL)
            {
                size_t rx_length;

                level = os_hw_interrupt_disable();
                /* get rx length */
                rx_length = list_len(&rx_fifo->uselist)* sizeof(struct can_msg);
                os_hw_interrupt_enable(level);

                if (rx_length)
                {
                    can->parent.rx_indicate(&can->parent, rx_length);
                }
            }
        }
        break;
    }

    case CAN_EVENT_TX_DONE:
    case CAN_EVENT_TX_FAIL:
    {
        struct can_tx_fifo *tx_fifo;
        uint32_t no;
        no = event >> 8;
        tx_fifo = (struct can_tx_fifo *) can->can_tx;
        ASSERT(tx_fifo != NULL);

        if ((event & 0xff) == CAN_EVENT_TX_DONE)
        {
            tx_fifo->buffer[no].result = CAN_SND_RESULT_OK;
        }
        else
        {
            tx_fifo->buffer[no].result = CAN_SND_RESULT_ERR;
        }
        completion_done(&(tx_fifo->buffer[no].completion));
        break;
    }
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
int cmd_canstat(int argc, char **argv)
{
    static const char *ErrCode[] =
    {
        "No Error!",
        "Warning !",
        "Passive !",
        "Bus Off !"
    };

    if (argc >= 2)
    {
        struct can_status status;
        device_t candev = device_find(argv[1]);
        if (!candev)
        {
            printf(" Can't find can device %s\n", argv[1]);
            return -1;
        }
        printf(" Finded can device: %s...", argv[1]);

        device_control(candev, CAN_CMD_GET_STATUS, &status);
        printf("\n Receive...error..count: %010ld. Send.....error....count: %010ld.",
                   status.rcverrcnt, status.snderrcnt);
        printf("\n Bit..pad..error..count: %010ld. Format...error....count: %010ld",
                   status.bitpaderrcnt, status.formaterrcnt);
        printf("\n Ack.......error..count: %010ld. Bit......error....count: %010ld.",
                   status.ackerrcnt, status.biterrcnt);
        printf("\n CRC.......error..count: %010ld. Error.code.[%010ld]: ",
                   status.crcerrcnt, status.errcode);
        switch (status.errcode)
        {
        case 0:
            printf("%s.", ErrCode[0]);
            break;
        case 1:
            printf("%s.", ErrCode[1]);
            break;
        case 2:
        case 3:
            printf("%s.", ErrCode[2]);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            printf("%s.", ErrCode[3]);
            break;
        }
        printf("\n Total.receive.packages: %010ld. Droped.receive.packages: %010ld.",
                   status.rcvpkg, status.dropedrcvpkg);
        printf("\n Total..send...packages: %010ld. Droped...send..packages: %010ld.\n",
                   status.sndpkg + status.dropedsndpkg, status.dropedsndpkg);
    }
    else
    {
        printf(" Invalid Call %s\n", argv[0]);
        printf(" Please using %s cannamex .Here canname is driver name and x is candrive number.\n", argv[0]);
    }
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_canstat, __cmd_canstat, Stat Can Device Status.);
#endif

