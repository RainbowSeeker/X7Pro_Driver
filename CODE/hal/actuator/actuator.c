#include "hal/actuator/actuator.h"

static bool_t dev_suspend;

static err_t hal_actuator_init(struct device* dev)
{
    ASSERT(dev != NULL);

    actuator_dev_t act = (actuator_dev_t)dev;

    /* apply default configuration */
    if (act->ops->dev_config) {
        return act->ops->dev_config(act, &act->config);
    }

    return E_OK;
}

static err_t hal_actuator_control(struct device* dev, int cmd, void* args)
{
    ASSERT(dev != NULL);

    actuator_dev_t act = (actuator_dev_t)dev;

    switch (cmd) {
    case DEVICE_CTRL_SUSPEND:
        dev_suspend = TRUE;
        break;

    case DEVICE_CTRL_RESUME:
        dev_suspend = FALSE;
        break;

    default:
        if (act->ops->dev_control) {
            return act->ops->dev_control(act, cmd, args);
        }
    }

    return E_OK;
}

static err_t hal_actuator_open(light_device_t dev, uint16_t oflag)
{
    return hal_actuator_control(dev, ACT_CMD_CHANNEL_ENABLE, NULL);
}

static err_t hal_actuator_close(light_device_t dev)
{
    return hal_actuator_control(dev, ACT_CMD_CHANNEL_DISABLE, NULL);
}

static size_t hal_actuator_read(struct device* dev, off_t pos, void* buffer, size_t size)
{
    ASSERT(dev != NULL);

    actuator_dev_t act = (actuator_dev_t)dev;
    size_t rb = 0;

    if (buffer == NULL || pos == 0) {
        return 0;
    }

    /* apply channel mask */
    pos = pos & act->chan_mask;

    if (act->ops->dev_read) {
        rb = act->ops->dev_read(act, pos, buffer, size);
    }

    return rb;
}

static size_t hal_actuator_write(light_device_t dev, off_t pos, const void* buffer, size_t size)
{
    ASSERT(dev != NULL);

    actuator_dev_t act = (actuator_dev_t)dev;
    size_t wb = 0;
    uint16_t chan_val[16];
    uint8_t index = 0;
    uint16_t* val_ptr = (uint16_t*)buffer;

    if (dev_suspend == TRUE || buffer == NULL || pos == 0) {
        return 0;
    }

    /* apply channel mask */
    pos = pos & act->chan_mask;
    /* saturate channel value */
    for (uint8_t i = 0; i < 16; i++) {
        if (pos & (1 << i)) {
            chan_val[index] = constrain_uint16(val_ptr[index], act->range[0], act->range[1]);
            index++;
        }
    }

    if (act->ops->dev_write) {
        wb = act->ops->dev_write(act, pos, chan_val, size);
    }

    return wb;
}

err_t hal_actuator_register(actuator_dev_t dev, const char* name, uint32_t flag, void* data)
{
    ASSERT(dev != NULL);

    struct device* device;

    device = &(dev->parent);

    device->type = Device_Class_Miscellaneous;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_actuator_init;
    device->open = hal_actuator_open;
    device->close = hal_actuator_close;
    device->read = hal_actuator_read;
    device->write = hal_actuator_write;
    device->control = hal_actuator_control;
    device->user_data = data;

    /* register device */
    return light_device_register(device, name, flag);
}
