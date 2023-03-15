#include <common.h>

#include "hal/rc/rc.h"

static err_t hal_rc_init(struct device* dev)
{
    err_t ret = E_OK;
    rc_dev_t rc;

    ASSERT(dev != NULL);

    rc = (rc_dev_t)dev;

    /* apply configuration */
    if (rc->ops->rc_configure) {
        ret = rc->ops->rc_configure(rc, &rc->config);
    }

    return ret;
}

static size_t hal_rc_read(struct device* dev, off_t pos, void* buffer, size_t size)
{
    rc_dev_t rc;
    uint16_t read_mask = (uint16_t)pos;
    uint16_t channel_mask;
    int16_t* rc_channel = (int16_t*)buffer;
    size_t rb = 0;
    uint8_t n = 0;

    ASSERT(dev != NULL);

    rc = (rc_dev_t)dev;

    /* apply channel mask */
    channel_mask = (1 << rc->config.channel_num) - 1;
    read_mask &= channel_mask;

    if (rc->ops->rc_read && buffer) {
        rb = rc->ops->rc_read(rc, read_mask, buffer);
    }

    for (int i = 0; i < rc->config.channel_num; i++) {
        if (read_mask & (1 << i)) {
            /* saturate read value */
            if (rc_channel[i] > rc->config.rc_max_value) {
                rc_channel[i] = rc->config.rc_max_value;
            }
            if (rc_channel[i] < rc->config.rc_min_value) {
                rc_channel[i] = rc->config.rc_min_value;
            }
            /* check if we have saturated all value */
            if (++n >= rb / 2) {
                break;
            }
        }
    }

    return rb;
}

static err_t hal_rc_control(struct device* dev, int cmd, void* args)
{
    rc_dev_t rc;

    ASSERT(dev != NULL);

    rc = (rc_dev_t)dev;

    switch (cmd) {
    case DEVICE_CTRL_CONFIG:
        if (args) {
            struct rc_configure* pconfig = (struct rc_configure*)args;
            /* set rc configure */
            rc->config = *pconfig;

            /* if device is opened before, re-configure it */
            if (rc->parent.flag & DEVICE_FLAG_ACTIVATED && rc->ops->rc_configure) {
                rc->ops->rc_configure(rc, pconfig);
            }
        }
        break;

    default:
        if (rc->ops->rc_control) {
            return rc->ops->rc_control(rc, cmd, args);
        }
        break;
    }

    return E_OK;
}

err_t hal_rc_rx_ind(rc_dev_t rc, size_t size)
{
    device_t device = &(rc->parent);

    if (device->rx_indicate) {
        return device->rx_indicate(device, size);
    }

    return E_OK;
}

err_t hal_rc_register(rc_dev_t rc, const char* name, uint32_t flag, void* data)
{
    struct device* device;

    ASSERT(rc != NULL);

    device = &(rc->parent);

    device->type = Device_Class_Miscellaneous;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_rc_init;
    device->open = NULL;
    device->close = NULL;
    device->read = hal_rc_read;
    device->write = NULL;
    device->control = hal_rc_control;

    device->user_data = data;

    /* register pin device */
    return device_register(device, name, flag);
}
