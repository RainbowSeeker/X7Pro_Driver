// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "barometer.h"


static size_t hal_baro_read(struct light_device* dev,
                               off_t pos,
                               void* buffer,
                               size_t size)
{
    size_t rb = 0;
    baro_dev_t baro;

    ASSERT(dev != NULL);
    ASSERT(buffer != NULL);

    baro = (baro_dev_t)dev;

    if (pos == BARO_RD_REPORT && baro->ops->baro_read) {
        rb = baro->ops->baro_read(baro, buffer);
    }

    return rb;
}

static err_t hal_baro_control(struct light_device* dev,
                                 int cmd,
                                 void* args)
{
    err_t ret = E_OK;
    baro_dev_t baro;

    ASSERT(dev != NULL);

    baro = (baro_dev_t)dev;

    if (baro->ops->baro_control) {
        ret = baro->ops->baro_control(baro, cmd, args);
    }

    return ret;
}

err_t hal_baro_register(baro_dev_t baro, const char* name, uint32_t flag, void* data)
{
    err_t ret;
    struct light_device* device;

    ASSERT(baro != NULL);

    device = &(baro->parent);

    device->type = Device_Class_SPIDevice;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = hal_baro_read;
    device->write = NULL;
    device->control = hal_baro_control;
    device->user_data = data;

    /* register a character device */
    ret = light_device_register(device, name, flag);

    return ret;
}