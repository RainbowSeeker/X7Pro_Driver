#include <common.h>

#include "hal/usb/usbd_cdc.h"
#include "module/utils/devmq.h"

#define USBD_WAIT_TIMEOUT 1000
#define USBD_RX_FIFO_SIZE 2048

static err_t hal_usbd_cdc_init(device_t device)
{
    usbd_cdc_dev_t usbd = (usbd_cdc_dev_t)device;
    err_t err = E_OK;

    usbd->rx_rb = ringbuffer_create(USBD_RX_FIFO_SIZE);
    if (usbd->rx_rb == NULL) {
        return E_NOMEM;
    }

    mutex_init(&usbd->tx_lock);
    if (usbd->tx_lock == NULL) {
        return E_NOMEM;
    }

    if (usbd->ops->dev_init) {
        err = usbd->ops->dev_init(usbd);
    }
    return err;
}

static err_t hal_usbd_cdc_open(device_t device, uint16_t oflag)
{
    if ((device->flag & oflag) != oflag) {
        return E_IO;
    }

    return E_OK;
}

static size_t hal_usbd_cdc_read(device_t device, off_t pos, void* buffer, size_t size)
{
    usbd_cdc_dev_t usbd = (usbd_cdc_dev_t)device;
    size_t rb = 0;

    if (usbd->ops->dev_read) {
        rb = usbd->ops->dev_read(usbd, pos, buffer, size);
    }

    return rb;
}

static size_t hal_usbd_cdc_write(device_t device, off_t pos, const void* buffer, size_t size)
{
    usbd_cdc_dev_t usbd = (usbd_cdc_dev_t)device;
    size_t wb = 0;

    if (usbd->status != USBD_STATUS_CONNECT) {
        return 0;
    }

    if (mutex_take(usbd->tx_lock, TICKS_FROM_MS(USBD_WAIT_TIMEOUT)) != E_OK) {
        return 0;
    }

    if (usbd->ops->dev_write) {
        wb = usbd->ops->dev_write(usbd, pos, buffer, size);
    }

    /* wait until send is finished */
    completion_wait(&usbd->tx_cplt, TICKS_FROM_MS(USBD_WAIT_TIMEOUT));

    mutex_release(usbd->tx_lock);
    return wb;
}

void hal_usbd_cdc_notify_status(usbd_cdc_dev_t usbd, int status)
{
    device_status dev_sta;
    switch (status) {
    case USBD_STATUS_DISCONNECT:
        usbd->status = USBD_STATUS_DISCONNECT;
        /* notify usb disconnect status */
        dev_sta = DEVICE_STAUTS_DISCONNECT;
        devmq_notify(&usbd->parent, &dev_sta);
        break;
    case USBD_STATUS_CONNECT:
        usbd->status = USBD_STATUS_CONNECT;
        /* notify usb connect status */
        dev_sta = DEVICE_STATUS_CONNECT;
        devmq_notify(&usbd->parent, &dev_sta);
        break;
    case USBD_STATUS_TX_COMPLETE:
        completion_done(&usbd->tx_cplt);
        if (usbd->parent.tx_complete) {
            usbd->parent.tx_complete(&usbd->parent, NULL);
        }
        break;
    case USBD_STATUS_RX:
        if (usbd->parent.rx_indicate) {
            usbd->parent.rx_indicate(&usbd->parent, ringbuffer_getlen(usbd->rx_rb));
        }
        break;
    default:
        break;
    }
}

err_t hal_usbd_cdc_register(usbd_cdc_dev_t usbd, const char* name, uint16_t flag, void* data)
{
    device_t dev = &usbd->parent;

    dev->type = Device_Class_USBDevice;
    dev->ref_count = 0;

    dev->rx_indicate = NULL;
    dev->tx_complete = NULL;

    dev->init = hal_usbd_cdc_init;
    dev->open = hal_usbd_cdc_open;
    dev->close = NULL;
    dev->read = hal_usbd_cdc_read;
    dev->write = hal_usbd_cdc_write;
    dev->control = NULL;

    dev->user_data = NULL;

    if (device_register(dev, name, flag) != E_OK) {
        return E_RROR;
    }

    if (devmq_create(dev, sizeof(device_status), 5) != E_OK) {
        return E_RROR;
    }

    completion_init(&usbd->tx_cplt);

    return E_OK;
}