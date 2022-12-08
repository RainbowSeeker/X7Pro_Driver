// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "accel.h"

static err_t hal_accel_init(struct light_device* dev)
{
    err_t ret = E_OK;
    accel_dev_t accel;

    ASSERT(dev != NULL);
    accel = (accel_dev_t)dev;

    /* apply configuration */
    if (accel->ops->accel_config) {
        ret = accel->ops->accel_config(accel, &accel->config);
    }

    return ret;
}

static size_t hal_accel_read(struct light_device* dev,
                                off_t pos,
                                void* buffer,
                                size_t size)
{
    size_t rb = 0;
    accel_dev_t accel;

    ASSERT(dev != NULL);

    accel = (accel_dev_t)dev;

    if (accel->ops->accel_read && size) {
        rb = accel->ops->accel_read(accel, pos, buffer, size);
    }

    return rb;
}

static err_t hal_accel_control(struct light_device* dev,
                                  int cmd,
                                  void* args)
{
    err_t ret = E_OK;
    accel_dev_t accel;

    ASSERT(dev != NULL);

    accel = (accel_dev_t)dev;

    if (accel->ops->accel_control) {
        ret = accel->ops->accel_control(accel, cmd, args);
    }

    return ret;
}

err_t hal_accel_register(accel_dev_t accel, const char* name, uint32_t flag, void* data)
{
    err_t ret;
    struct light_device* device;

    ASSERT(accel != NULL);

    device = &(accel->parent);

    device->type = (accel->bus_type == ACCEL_SPI_BUS_TYPE) ? Device_Class_SPIDevice : Device_Class_I2CBUS;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_accel_init;
    device->open = NULL;
    device->close = NULL;
    device->read = hal_accel_read;
    device->write = NULL;
    device->control = hal_accel_control;
    device->user_data = data;

    /* register a character device */
    ret = light_device_register(device, name, flag);

    return ret;
}