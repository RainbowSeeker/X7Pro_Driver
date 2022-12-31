#include "systick.h"


size_t systick_read(light_device_t dev, off_t pos, void* buffer, size_t size)
{
    ASSERT(dev != NULL);

    systick_dev_t systick = (systick_dev_t)dev;

    if (pos == SYSTICK_RD_TIME_US) {
        *(uint32_t*)buffer = systick->ops->systick_read(systick);
        return sizeof(uint32_t);
    }

    return 0;
}

static err_t systick_control(light_device_t dev, int cmd, void* args)
{
    systick_dev_t systick;

    ASSERT(dev != NULL);

    systick = (systick_dev_t)dev;

    if (cmd == SYSTICK_CMD_SET_FREQUENCY) {
        if (systick->ops->systick_configure) {
            struct systick_configure config;
            config.tick_freq = *(uint16_t*)args;

            systick->ops->systick_configure(systick, &config);
        }
    }

    return E_OK;
}

void hal_systick_isr(systick_dev_t systick)
{
    if (systick && systick->systick_isr_cb) {
        systick->systick_isr_cb();
    }
}

err_t hal_systick_register(systick_dev_t systick, const char* name, uint32_t flag, void* data)
{
    struct device* device;

    ASSERT(systick != NULL);

    device = &(systick->parent);

    device->type = Device_Class_Timer;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = systick_read;
    device->write = NULL;
    device->control = systick_control;

    device->user_data = data;

    /* register pin device */
    return light_device_register(device, name, flag);
}
