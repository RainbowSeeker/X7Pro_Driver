#include <common.h>

#include "hal/fmtio_dev/fmtio_dev.h"
#include "hal/serial/serial.h"

static struct device fmtio_dev;
static device_t fmtio_dev_t = &fmtio_dev;
static device_t io_dev_t;
static struct completion tx_cplt, rx_cplt;
static os_sem_t tx_lock;

static err_t fmtio_dev_tx_done(device_t dev, void* buffer)
{
    err_t ret;

    completion_done(&tx_cplt);

    /* invoke tx indicator if set */
    if (fmtio_dev_t->tx_complete) {
        fmtio_dev_t->tx_complete(fmtio_dev_t, buffer);
    }

    return ret;
}

static err_t fmtio_dev_rx_ind(device_t dev, size_t size)
{
    err_t ret;

    completion_done(&rx_cplt);

    /* invoke rx indicator if set */
    if (fmtio_dev_t->rx_indicate) {
        fmtio_dev_t->rx_indicate(fmtio_dev_t, size);
    }

    return ret;
}

static err_t fmtio_dev_open(device_t dev, uint16_t oflag)
{
    return device_open(io_dev_t, oflag);
}

static err_t fmtio_dev_close(device_t dev)
{
    return device_close(io_dev_t);
}

static size_t fmtio_dev_read(device_t dev, off_t pos, void* buffer, size_t size)
{
    size_t cnt = 0;
    int32_t timeout = (int32_t)pos;

    /* try to read data */
    cnt = device_read(io_dev_t, 0, buffer, size);

    /* if not enough data received, wait it */
    while (cnt < size) {
        /* wait receive some data */
        if (completion_wait(&rx_cplt, timeout) != E_OK) {
            return cnt;
        }
        /* read left data */
        cnt += device_read(io_dev_t, 0, (void*)((uint32_t)buffer + cnt), size - cnt);
    }

    return cnt;
}

static size_t fmtio_dev_write(device_t dev, off_t pos, const void* buffer, size_t size)
{
    size_t wb;
    int32_t timeout = (int32_t)pos;

    /* take tx lock */
    if (os_sem_take(tx_lock, timeout) != E_OK) {
        return 0;
    }
    /* write data to device */
    wb = device_write(io_dev_t, 0, buffer, size);
    /* wait write complete */
    completion_wait(&tx_cplt, timeout);
    /* release tx lock */
    os_sem_release(tx_lock);

    return wb;
}

err_t fmtio_dev_control(device_t dev, int cmd, void* args)
{
    err_t ret = E_OK;
    serial_dev_t serial = (serial_dev_t)io_dev_t;

    switch (cmd) {
    case FMTIO_SET_BAUDRATE: {
        struct serial_configure config = serial->config;
        config.baud_rate = (uint32_t)args;
        ret = serial->ops->configure(serial, &config);
        if (ret == E_OK) {
            serial->config.baud_rate = config.baud_rate;
        }
    } break;

    case FMTIO_GET_BAUDRATE:
        if (args == NULL) {
            return E_INVAL;
        }
        *(uint32_t*)args = serial->config.baud_rate;
        break;

    default:
        break;
    }

    return ret;
}

/**
 * @brief Register fmtio device
 * 
 * @param io_dev The io device which is used by fmtio
 * @param name The name of fmtio device
 * @param flag Open flag, should be equal to io device flag
 * @param data User data
 * @return err_t
 */
err_t hal_fmtio_dev_register(device_t io_dev, const char* name, uint32_t flag, void* data)
{
    io_dev_t = io_dev;

    ASSERT(io_dev_t != NULL);
    ASSERT(io_dev_t->flag == flag);

    completion_init(&tx_cplt);
    completion_init(&rx_cplt);

    /* write lock */
    tx_lock = os_sem_create(1);
    ASSERT(tx_lock != NULL);

    /* set tx/rx callback functions */
    SELF_CHECK(device_set_tx_complete(io_dev_t, fmtio_dev_tx_done));
    SELF_CHECK(device_set_rx_indicate(io_dev_t, fmtio_dev_rx_ind));

    /* init fmtio device */
    fmtio_dev_t->type = Device_Class_Char;
    fmtio_dev_t->rx_indicate = NULL;
    fmtio_dev_t->tx_complete = NULL;

    fmtio_dev_t->init = NULL;
    fmtio_dev_t->open = fmtio_dev_open;
    fmtio_dev_t->close = fmtio_dev_close;
    fmtio_dev_t->read = fmtio_dev_read;
    fmtio_dev_t->write = fmtio_dev_write;
    fmtio_dev_t->control = fmtio_dev_control;

    fmtio_dev_t->user_data = data;

    return device_register(fmtio_dev_t, name, flag);
}