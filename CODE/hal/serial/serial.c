// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/3.
//


#include "serial.h"
#include "stm32h7xx_ll_dma.h"
#include "algo/math/maths.h"


/*
 * This function initializes serial device.
 */
static err_t hal_serial_init(struct light_device *dev)
{
    err_t result = E_OK;
    struct serial_device *serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device *) dev;

    /* initialize rx/tx */
    serial->serial_rx = NULL;
    serial->serial_tx = NULL;

    /* apply configuration */
    if (serial->ops->configure)
        result = serial->ops->configure(serial, &serial->config);

    return result;
}

static err_t hal_serial_open(struct light_device *dev, uint16_t oflag)
{
    struct serial_device *serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device *) dev;

    /* check device flag with the open flag */
    if ((oflag & DEVICE_FLAG_INT_RX) && !(dev->flag & DEVICE_FLAG_INT_RX))
        return E_IO;

    if ((oflag & DEVICE_FLAG_DMA_RX) && !(dev->flag & DEVICE_FLAG_DMA_RX))
        return E_IO;

    if ((oflag & DEVICE_FLAG_DMA_TX) && !(dev->flag & DEVICE_FLAG_DMA_TX))
        return E_IO;

    /* get open flags */
    dev->open_flag = oflag;

    /* initialize the Rx/Tx structure according to open flag */
    if (oflag & DEVICE_FLAG_INT_RX || oflag & DEVICE_FLAG_DMA_RX)
    {
        if (serial->serial_rx == NULL)
        {
            struct serial_rx_fifo *rx_fifo;

            /* create dma rx fifo */
            rx_fifo = (struct serial_rx_fifo *) malloc(sizeof(struct serial_rx_fifo) + serial->config.bufsz);
            ASSERT(rx_fifo != NULL);
            rx_fifo->buffer = (uint8_t *) (rx_fifo + 1);
            memset(rx_fifo->buffer, 0, serial->config.bufsz);
            rx_fifo->put_index = 0;
            rx_fifo->get_index = 0;
            rx_fifo->is_full = FALSE;

            serial->serial_rx = rx_fifo;
        }
    }
    else
    {
        serial->serial_rx = NULL;
    }

    /* we don't use serial_tx */
    serial->serial_tx = NULL;

    if (oflag & DEVICE_FLAG_INT_RX)
    {
        /* configure low level device */
        serial->ops->control(serial, DEVICE_CTRL_SET_INT, (void *) DEVICE_FLAG_INT_RX);
    }
    else if (oflag & DEVICE_FLAG_DMA_RX)
    {
        /* configure fifo address and length to low level device */
        serial->ops->control(serial, DEVICE_CTRL_CONFIG, (void *) DEVICE_FLAG_DMA_RX);
    }

    if (oflag & DEVICE_FLAG_DMA_TX)
    {
        /* configure fifo address and length to low level device */
        serial->ops->control(serial, DEVICE_CTRL_CONFIG, (void *) DEVICE_FLAG_DMA_TX);
    }
  
    return E_OK;
}

static err_t hal_serial_close(struct light_device *dev)
{
    struct serial_device *serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device *) dev;

    /* this device has more reference count */
    if (dev->ref_count > 1)
        return EBUSY;

    /* configure low level device, disable ineterrupts and dma*/
    serial->ops->control(serial, DEVICE_CTRL_SUSPEND, NULL);

    serial->parent.rx_indicate = NULL;
    serial->parent.tx_complete = NULL;

    if (dev->open_flag & DEVICE_FLAG_INT_RX)
    {
        struct serial_rx_fifo *rx_fifo;

        rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;

        if (rx_fifo)
            free(rx_fifo);

        serial->serial_rx = NULL;
        dev->open_flag &= ~DEVICE_FLAG_INT_RX;
    }
    else if (dev->open_flag & DEVICE_FLAG_DMA_RX)
    {
        struct serial_rx_fifo *rx_fifo;

        rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;

        if (rx_fifo)
            free(rx_fifo);

        serial->serial_rx = NULL;
        dev->open_flag &= ~DEVICE_FLAG_DMA_RX;
    }

    if (dev->open_flag & DEVICE_FLAG_DMA_TX)
    {
        if (serial->serial_tx)
            free(serial->serial_tx);

        serial->serial_tx = NULL;
        dev->open_flag &= ~DEVICE_FLAG_DMA_TX;
    }

    return E_OK;
}

static size_t serial_fifo_calc_recved_len(struct serial_device *serial)
{
    struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;

    ASSERT(rx_fifo != NULL);

    if (rx_fifo->put_index == rx_fifo->get_index)
    {
        return (rx_fifo->is_full == FALSE ? 0 : serial->config.bufsz);
    }
    else
    {
        if (rx_fifo->put_index > rx_fifo->get_index)
        {
            return rx_fifo->put_index - rx_fifo->get_index;
        }
        else
        {
            return serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index);
        }
    }
}

static void serial_fifo_update_get_index(struct serial_device *serial, size_t len)
{
    struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;

    ASSERT(rx_fifo != NULL);
    ASSERT(len <= serial_fifo_calc_recved_len(serial));

    if (rx_fifo->is_full && len != 0)
        rx_fifo->is_full = FALSE;

    rx_fifo->get_index += len;

    if (rx_fifo->get_index >= serial->config.bufsz)
    {
        rx_fifo->get_index %= serial->config.bufsz;
    }
}

static size_t hal_serial_read(struct light_device *dev,
                              off_t pos,
                              void *buffer,
                              size_t size)
{
    struct serial_device *serial;

    ASSERT(dev != NULL);

    if (size == 0 || buffer == NULL)
        return 0;

    serial = (struct serial_device *) dev;

    if (dev->open_flag & DEVICE_FLAG_INT_RX)
    {
        uint8_t *data = (uint8_t *) buffer;
        size_t left_size = size;
        struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;
        ASSERT(rx_fifo != NULL);

        uint8_t ch;
        base_t level;

        /* read from software FIFO */
        while (left_size)
        {
            /* disable interrupt */
            level = os_hw_interrupt_disable();

            /* there's no data: */
            if ((rx_fifo->get_index == rx_fifo->put_index) && (rx_fifo->is_full == FALSE))
            {
                /* no data, enable interrupt and break out */
                os_hw_interrupt_enable(level);
                break;
            }

            /* otherwise there's the data: */
            ch = rx_fifo->buffer[rx_fifo->get_index];
            rx_fifo->get_index += 1;

            if (rx_fifo->get_index >= serial->config.bufsz)
                rx_fifo->get_index = 0;

            if (rx_fifo->is_full == TRUE)
            {
                rx_fifo->is_full = FALSE;
            }

            /* enable interrupt */
            os_hw_interrupt_enable(level);

            *data = ch & 0xff;
            data++;
            left_size--;
        }

        return size - left_size;
    }
    else if (dev->open_flag & DEVICE_FLAG_DMA_RX)
    {
        base_t level = os_hw_interrupt_disable();

        struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;
        size_t recv_len = 0, fifo_recved_len = serial_fifo_calc_recved_len(serial);

        recv_len = min(size, fifo_recved_len);

        if (rx_fifo->get_index + recv_len < serial->config.bufsz)
            memcpy(buffer, rx_fifo->buffer + rx_fifo->get_index, recv_len);
        else
        {
            memcpy(buffer, rx_fifo->buffer + rx_fifo->get_index, serial->config.bufsz - rx_fifo->get_index);
            memcpy(buffer + serial->config.bufsz - rx_fifo->get_index, rx_fifo->buffer,
                   recv_len + rx_fifo->get_index - serial->config.bufsz);
        }

        serial_fifo_update_get_index(serial, recv_len);

        os_hw_interrupt_enable(level);

        return recv_len;
    }
    else
    {
        int ch;
        int rx_length;
        uint8_t *data = (uint8_t *) buffer;
        size_t left_size = size;
        while (left_size) {
            ch = serial->ops->getc(serial);

            if (ch == -1)
                break;

            *data = ch & 0xff;
            data++;
            left_size--;

            if (ch == '\n')
                break;
        }

        rx_length = size - left_size;

        /* invoke callback */
        if (serial->parent.rx_indicate != NULL && rx_length) {
            serial->parent.rx_indicate(&serial->parent, rx_length);
        }

        return rx_length;
    }
}

static size_t hal_serial_write(struct light_device *dev,
                               off_t pos,
                               const void *buffer,
                               size_t size)
{
    struct serial_device *serial;

    ASSERT(dev != NULL);

    if (size == 0 || buffer == NULL)
        return 0;

    serial = (struct serial_device *) dev;
    if (dev->open_flag & DEVICE_FLAG_DMA_TX && IS_AXI_SRAM(buffer))
    {
        scb_flush_dcache((void *)buffer, size);
        return serial->ops->dma_transmit(serial, (uint8_t *) buffer, size);
    }
    else
    {
        uint8_t *data = (uint8_t *) buffer;
        size_t left_size = size;
        while (left_size)
        {
            /**
             * to be polite with serial console add a line feed
             * to the carriage return character
             */
            if (*data == '\n' && (serial->parent.open_flag & DEVICE_FLAG_STREAM))
            {
                serial->ops->putc(serial, '\r');
            }

            serial->ops->putc(serial, *data);

            data++;
            left_size--;
        }

        /* invoke callback */
        if (serial->parent.tx_complete != NULL)
        {
            serial->parent.tx_complete(&serial->parent, (void *) NULL);
        }

        return size - left_size;
    }
}

static err_t hal_serial_control(struct light_device *dev,
                                int cmd,
                                void *args)
{
    err_t ret = E_OK;
    struct serial_device *serial;

    ASSERT(dev != NULL);
    serial = (struct serial_device *) dev;

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
            if (args)
            {
                struct serial_configure *pconfig = (struct serial_configure *) args;

                if (pconfig->bufsz != serial->config.bufsz && serial->parent.ref_count)
                {
                    /*can not change buffer size*/
                    return EBUSY;
                }

                /* set serial configure */
                serial->config = *pconfig;

                /* if device is opened before, re-configure it */
                if (serial->parent.flag & DEVICE_FLAG_ACTIVATED && serial->ops->configure)
                {
                    /* serial device has been opened, re-configure it */
                    serial->ops->configure(serial, (struct serial_configure *) args);
                }
            }

            break;

        default:
            /* control device */
            if (serial->ops->control)
            {
                ret = serial->ops->control(serial, cmd, args);
            }
            break;
    }

    return ret;
}


/*
 * serial register
 */
err_t hal_serial_register(serial_dev_t serial,
                          const char *name,
                          uint32_t flag,
                          void *data)
{
    err_t ret;
    struct light_device *device;
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
    ret = light_device_register(device, name, flag);

    return ret;
}