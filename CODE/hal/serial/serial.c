#include "hal/serial/serial.h"
#include <common.h>

/*
 * Serial poll routines
 */
inline int _serial_poll_rx(struct serial_device* serial, uint8_t* data, int length)
{
    int ch;
    int size;
    int rx_length;

    ASSERT(serial != NULL);
    size = length;

    while (length) {
        ch = serial->ops->getc(serial);

        if (ch == -1)
            break;

        *data = ch;
        data++;
        length--;

        if (ch == '\n')
            break;
    }

    rx_length = size - length;

    /* invoke callback */
    if (serial->parent.rx_indicate != NULL && rx_length) {
        serial->parent.rx_indicate(&serial->parent, rx_length);
    }

    return rx_length;
}

inline int _serial_poll_tx(struct serial_device* serial, const uint8_t* data, int length)
{
    int size;
    ASSERT(serial != NULL);

    size = length;

    while (length) {
        /**
         * to be polite with serial console add a line feed
         * to the carriage return character
         */
        if (*data == '\n' && (serial->parent.open_flag & DEVICE_FLAG_STREAM)) {
            serial->ops->putc(serial, '\r');
        }

        serial->ops->putc(serial, *data);

        ++data;
        --length;
    }

    /* invoke callback */
    if (serial->parent.tx_complete != NULL) {
        serial->parent.tx_complete(&serial->parent, (void*)NULL);
    }

    return size - length;
}

/*
 * Serial interrupt routines
 */
inline int _serial_int_rx(struct serial_device* serial, uint8_t* data, int length)
{
    int size;
    struct serial_rx_fifo* rx_fifo;

    ASSERT(serial != NULL);
    size = length;

    rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;
    ASSERT(rx_fifo != NULL);

    /* read from software FIFO */
    while (length) {
        int ch;
        base_t level;

        /* disable interrupt */
        level = os_hw_interrupt_disable();

        /* there's no data: */
        if ((rx_fifo->get_index == rx_fifo->put_index) && (rx_fifo->is_full == FALSE)) {
            /* no data, enable interrupt and break out */
            os_hw_interrupt_enable(level);
            break;
        }

        /* otherwise there's the data: */
        ch = rx_fifo->buffer[rx_fifo->get_index];
        rx_fifo->get_index += 1;

        if (rx_fifo->get_index >= serial->config.bufsz)
            rx_fifo->get_index = 0;

        if (rx_fifo->is_full == TRUE) {
            rx_fifo->is_full = FALSE;
        }

        /* enable interrupt */
        os_hw_interrupt_enable(level);

        *data = ch & 0xff;
        data++;
        length--;
    }

    return size - length;
}

//inline int _serial_int_tx(struct serial_device* serial, const uint8_t* data, int length)
//{
//    int size;
//    struct serial_tx_fifo* tx;
//
//    ASSERT(serial != NULL);
//
//    size = length;
//    tx = (struct serial_tx_fifo*)serial->serial_tx;
//    ASSERT(tx != NULL);
//
//    while (length) {
//        if (serial->ops->putc(serial, *(char*)data) == -1) {
//            completion_wait(&(tx->completion), osWaitForever);
//            continue;
//        }
//
//        data++;
//        length--;
//    }
//
//    return size - length;
//}

static size_t _serial_fifo_calc_recved_len(struct serial_device* serial)
{
    struct serial_rx_fifo* rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;

    ASSERT(rx_fifo != NULL);

    if (rx_fifo->put_index == rx_fifo->get_index) {
        return (rx_fifo->is_full == FALSE ? 0 : serial->config.bufsz);
    } else {
        if (rx_fifo->put_index > rx_fifo->get_index) {
            return rx_fifo->put_index - rx_fifo->get_index;
        } else {
            return serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index);
        }
    }
}

/**
 * Calculate DMA received data length.
 *
 * @param serial serial device
 *
 * @return length
 */
static size_t _dma_calc_recved_len(struct serial_device* serial)
{
    return _serial_fifo_calc_recved_len(serial);
}

/**
 * Read data finish by DMA mode then update the get index for receive fifo.
 *
 * @param serial serial device
 * @param len get data length for this operate
 */
static void _dma_recv_update_get_index(struct serial_device* serial, size_t len)
{
    struct serial_rx_fifo* rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;

    ASSERT(rx_fifo != NULL);
    ASSERT(len <= _dma_calc_recved_len(serial));

    if (rx_fifo->is_full && len != 0)
        rx_fifo->is_full = FALSE;

    rx_fifo->get_index += len;

    if (rx_fifo->get_index >= serial->config.bufsz) {
        rx_fifo->get_index %= serial->config.bufsz;
    }
}

/**
 * DMA received finish then update put index for receive fifo.
 *
 * @param serial serial device
 * @param len received length for this transmit
 */
static void _dma_recv_update_put_index(struct serial_device* serial, size_t len)
{
    struct serial_rx_fifo* rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;

    ASSERT(rx_fifo != NULL);

    if (rx_fifo->get_index <= rx_fifo->put_index) {
        rx_fifo->put_index += len;

        /* beyond the fifo end */
        if (rx_fifo->put_index >= serial->config.bufsz) {
            rx_fifo->put_index %= serial->config.bufsz;

            /* force overwrite get index */
            if (rx_fifo->put_index >= rx_fifo->get_index) {
                rx_fifo->is_full = TRUE;
            }
        }
    } else {
        rx_fifo->put_index += len;

        if (rx_fifo->put_index >= rx_fifo->get_index) {
            /* beyond the fifo end */
            if (rx_fifo->put_index >= serial->config.bufsz) {
                rx_fifo->put_index %= serial->config.bufsz;
            }

            /* force overwrite get index */
            rx_fifo->is_full = TRUE;
        }
    }

    if (rx_fifo->is_full == TRUE) {
        rx_fifo->get_index = rx_fifo->put_index;
    }

    if (rx_fifo->get_index >= serial->config.bufsz)
        rx_fifo->get_index = 0;
}

/*
 * Serial DMA routines
 */
inline int _serial_dma_rx(struct serial_device* serial, uint8_t* data, int length)
{
    base_t level;

    ASSERT((serial != NULL) && (data != NULL));

    level = os_hw_interrupt_disable();

    struct serial_rx_fifo* rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;
    size_t recv_len = 0, fifo_recved_len = _dma_calc_recved_len(serial);

    ASSERT(rx_fifo != NULL);

    if (length < fifo_recved_len)
        recv_len = length;
    else
        recv_len = fifo_recved_len;

    if (rx_fifo->get_index + recv_len < serial->config.bufsz)
        memcpy(data, rx_fifo->buffer + rx_fifo->get_index, recv_len);
    else {
        memcpy(data, rx_fifo->buffer + rx_fifo->get_index, serial->config.bufsz - rx_fifo->get_index);
        memcpy(data + serial->config.bufsz - rx_fifo->get_index, rx_fifo->buffer, recv_len + rx_fifo->get_index - serial->config.bufsz);
    }

    _dma_recv_update_get_index(serial, recv_len);

    os_hw_interrupt_enable(level);

    return recv_len;
}

inline int _serial_dma_tx(struct serial_device* serial, const uint8_t* data, int length)
{
    /* make a DMA transfer */
    serial->ops->dma_transmit(serial, (uint8_t*)data, length, SERIAL_DMA_TX);

    return length;
}

/* ISR for serial interrupt */
void hal_serial_isr(struct serial_device* serial, int event)
{
    switch (event & 0xff) {
        case SERIAL_EVENT_RX_IND: {
            int ch = -1;
            base_t level;
            struct serial_rx_fifo* rx_fifo;

            /* interrupt mode receive */
            rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;
            ASSERT(rx_fifo != NULL);

            while (1) {
                ch = serial->ops->getc(serial);

                if (ch == -1)
                    break;

                /* disable interrupt */
                level = os_hw_interrupt_disable();

                rx_fifo->buffer[rx_fifo->put_index] = ch;
                rx_fifo->put_index += 1;

                if (rx_fifo->put_index >= serial->config.bufsz)
                    rx_fifo->put_index = 0;

                /* if the next position is read index, discard this 'read char' */
                if (rx_fifo->put_index == rx_fifo->get_index) {
                    rx_fifo->get_index += 1;
                    rx_fifo->is_full = TRUE;

                    if (rx_fifo->get_index >= serial->config.bufsz)
                        rx_fifo->get_index = 0;
                }

                /* enable interrupt */
                os_hw_interrupt_enable(level);
            }

            /* invoke callback */
            if (serial->parent.rx_indicate != NULL) {
                size_t rx_length;

                /* get rx length */
                level = os_hw_interrupt_disable();
                rx_length = (rx_fifo->put_index >= rx_fifo->get_index) ? (rx_fifo->put_index - rx_fifo->get_index) : (serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index));
                os_hw_interrupt_enable(level);

                if (rx_length) {
                    serial->parent.rx_indicate(&serial->parent, rx_length);
                }
            }

            break;
        }

        case SERIAL_EVENT_TX_DMADONE: {

            /* invoke callback */
            if (serial->parent.tx_complete != NULL) {
                serial->parent.tx_complete(&serial->parent, (void*)NULL);
            }

            break;
        }

        case SERIAL_EVENT_RX_DMADONE: {
            int length;
            base_t level;

            /* get DMA rx length */
            length = (event & (~0xff)) >> 8;

            /* disable interrupt */
            level = os_hw_interrupt_disable();
            /* update fifo put index */
            _dma_recv_update_put_index(serial, length);
            /* calculate received total length in fifo */
            length = _dma_calc_recved_len(serial);
            /* enable interrupt */
            os_hw_interrupt_enable(level);

            /* invoke callback */
            if (serial->parent.rx_indicate != NULL) {
                serial->parent.rx_indicate(&(serial->parent), length);
            }

            break;
        }
    }
}

/* RT-Thread Device Interface */
/*
 * This function initializes serial device.
 */
static err_t hal_serial_init(struct device* dev)
{
    err_t result = E_OK;
    struct serial_device* serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device*)dev;

    /* initialize rx/tx */
    serial->serial_rx = NULL;
    serial->serial_tx = NULL;

    /* apply configuration */
    if (serial->ops->configure)
        result = serial->ops->configure(serial, &serial->config);

    return result;
}

static err_t hal_serial_open(struct device* dev, uint16_t oflag)
{
    struct serial_device* serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device*)dev;

    /*dbg_log(DBG_LOG, "open serial device: 0x%08x with open flag: 0x%04x\n",
	    dev, oflag);*/

    /* check device flag with the open flag */
    if ((oflag & DEVICE_FLAG_INT_RX) && !(dev->flag & DEVICE_FLAG_INT_RX))
        return -EIO;

    if ((oflag & DEVICE_FLAG_DMA_RX) && !(dev->flag & DEVICE_FLAG_DMA_RX))
        return -EIO;

    if ((oflag & DEVICE_FLAG_DMA_TX) && !(dev->flag & DEVICE_FLAG_DMA_TX))
        return -EIO;

    /* get open flags */
    dev->open_flag = oflag;

    /* initialize the Rx/Tx structure according to open flag */
    if (oflag & DEVICE_FLAG_INT_RX || oflag & DEVICE_FLAG_DMA_RX) {
        if (serial->serial_rx == NULL) {
            struct serial_rx_fifo* rx_fifo;

            /* create dma rx fifo */
            rx_fifo = (struct serial_rx_fifo*)malloc(sizeof(struct serial_rx_fifo) + serial->config.bufsz);
            ASSERT(rx_fifo != NULL);
            rx_fifo->buffer = (uint8_t*)(rx_fifo + 1);
            memset(rx_fifo->buffer, 0, serial->config.bufsz);
            rx_fifo->put_index = 0;
            rx_fifo->get_index = 0;
            rx_fifo->is_full = FALSE;

            serial->serial_rx = rx_fifo;
        }
    } else {
        serial->serial_rx = NULL;
    }

    /* we don't use serial_tx */
    serial->serial_tx = NULL;

    if (oflag & DEVICE_FLAG_INT_RX) {
        /* configure low level device */
        serial->ops->control(serial, DEVICE_CTRL_SET_INT, (void*)DEVICE_FLAG_INT_RX);
    } else if (oflag & DEVICE_FLAG_DMA_RX) {
        /* configure fifo address and length to low level device */
        serial->ops->control(serial, DEVICE_CTRL_CONFIG, (void*)DEVICE_FLAG_DMA_RX);
    }

    if (oflag & DEVICE_FLAG_DMA_TX) {
        /* configure fifo address and length to low level device */
        serial->ops->control(serial, DEVICE_CTRL_CONFIG, (void*)DEVICE_FLAG_DMA_TX);
    }

    return E_OK;
}

static err_t hal_serial_close(struct device* dev)
{
    struct serial_device* serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device*)dev;

    /* this device has more reference count */
    if (dev->ref_count > 1)
        return EBUSY;

    /* configure low level device, disable ineterrupts and dma*/
    serial->ops->control(serial, DEVICE_CTRL_SUSPEND, NULL);

    serial->parent.rx_indicate = NULL;
    serial->parent.tx_complete = NULL;

    if (dev->open_flag & DEVICE_FLAG_INT_RX) {
        struct serial_rx_fifo* rx_fifo;

        rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;

        if (rx_fifo)
            free(rx_fifo);

        serial->serial_rx = NULL;

        dev->open_flag &= ~DEVICE_FLAG_INT_RX;
    } else if (dev->open_flag & DEVICE_FLAG_DMA_RX) {
        struct serial_rx_fifo* rx_fifo;

        rx_fifo = (struct serial_rx_fifo*)serial->serial_rx;

        if (rx_fifo)
            free(rx_fifo);

        serial->serial_rx = NULL;

        dev->open_flag &= ~DEVICE_FLAG_DMA_RX;
    }

    if (dev->open_flag & DEVICE_FLAG_DMA_TX) {
        if (serial->serial_tx)
            free(serial->serial_tx);

        serial->serial_tx = NULL;

        dev->open_flag &= ~DEVICE_FLAG_DMA_TX;
    }

    return E_OK;
}

static size_t hal_serial_read(struct device* dev,
                                 off_t pos,
                                 void* buffer,
                                 size_t size)
{
    struct serial_device* serial;

    ASSERT(dev != NULL);

    if (size == 0)
        return 0;

    serial = (struct serial_device*)dev;

    if (dev->open_flag & DEVICE_FLAG_INT_RX) {
        return _serial_int_rx(serial, buffer, size);
    } else if (dev->open_flag & DEVICE_FLAG_DMA_RX) {
        return _serial_dma_rx(serial, buffer, size);
    } else {
        return _serial_poll_rx(serial, buffer, size);
    }
}

static size_t hal_serial_write(struct device* dev,
                                  off_t pos,
                                  const void* buffer,
                                  size_t size)
{
    struct serial_device* serial;

    ASSERT(dev != NULL);

    if (size == 0)
        return 0;

    serial = (struct serial_device*)dev;

    if (dev->open_flag & DEVICE_FLAG_DMA_TX) {
        return _serial_dma_tx(serial, buffer, size);
    } else {
        return _serial_poll_tx(serial, buffer, size);
    }
}

static err_t hal_serial_control(struct device* dev,
                                   int cmd,
                                   void* args)
{
    err_t ret = E_OK;
    struct serial_device* serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device*)dev;

    switch (cmd) {
        case DEVICE_CTRL_SUSPEND:
            /* suspend device */
            dev->flag |= DEVICE_FLAG_SUSPENDED;
            break;

        case DEVICE_CTRL_RESUME:
            /* resume device */
            dev->flag &= ~DEVICE_FLAG_SUSPENDED;
            break;

        case DEVICE_CTRL_CONFIG:
            if (args) {
                struct serial_configure* pconfig = (struct serial_configure*)args;

                if (pconfig->bufsz != serial->config.bufsz && serial->parent.ref_count) {
                    /*can not change buffer size*/
                    return EBUSY;
                }

                /* set serial configure */
                serial->config = *pconfig;

                /* if device is opened before, re-configure it */
                if (serial->parent.flag & DEVICE_FLAG_ACTIVATED && serial->ops->configure) {
                    /* serial device has been opened, re-configure it */
                    serial->ops->configure(serial, (struct serial_configure*)args);
                }
            }

            break;

        default:
            /* control device */
            if (serial->ops->control) {
                ret = serial->ops->control(serial, cmd, args);
            }
            break;
    }

    return ret;
}

/*
 * serial register
 */
err_t hal_serial_register(struct serial_device* serial,
                             const char* name,
                             uint32_t flag,
                             void* data)
{
    err_t ret;
    struct device* device;
    ASSERT(serial != NULL);

    device = &(serial->parent);

    device->type = Device_Class_Char;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;


    device->init = hal_serial_init;
    device->open = hal_serial_open;
    device->close = hal_serial_close;
    device->read = hal_serial_read;
    device->write = hal_serial_write;
    device->control = hal_serial_control;
    device->user_data = data;

    /* register a character device */
    ret = device_register(device, name, flag);

    return ret;
}
