// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "gps.h"


static err_t hal_gps_init(device_t dev)
{
    err_t ret = E_OK;
    gps_dev_t gps_dev;

    ASSERT(dev != NULL);

    gps_dev = (gps_dev_t)dev;

    if (gps_dev->ops->gps_control) {
        ret = gps_dev->ops->gps_control(gps_dev, GPS_CMD_INIT, NULL);
    }

    return ret;
}

static err_t hal_gps_open(device_t dev, uint16_t oflag)
{
    err_t ret = E_OK;
    gps_dev_t gps_dev;

    ASSERT(dev != NULL);

    gps_dev = (gps_dev_t)dev;

    if (gps_dev->ops->gps_control) {
        ret = gps_dev->ops->gps_control(gps_dev, GPS_CMD_OPEN, &oflag);
    }

    return ret;
}

static err_t hal_gps_close(device_t dev)
{
    err_t ret = E_OK;
    gps_dev_t gps_dev;

    ASSERT(dev != NULL);

    gps_dev = (gps_dev_t)dev;

    if (gps_dev->ops->gps_control) {
        ret = gps_dev->ops->gps_control(gps_dev, GPS_CMD_CLOSE, NULL);
    }

    return ret;
}

static size_t hal_gps_read(struct device* dev,
                              off_t pos,
                              void* buffer,
                              size_t size)
{
    size_t rb = 0;
    gps_dev_t gps_dev;

    ASSERT(dev != NULL);
    ASSERT(buffer != NULL);

    gps_dev = (gps_dev_t)dev;

    if (pos == GPS_READ_REPORT && gps_dev->ops->gps_read) {
        rb = gps_dev->ops->gps_read(gps_dev, buffer);
    }

    return rb;
}

static err_t hal_gps_control(struct device* dev,
                                int cmd,
                                void* args)
{
    err_t ret = E_OK;
    gps_dev_t gps_dev;

    ASSERT(dev != NULL);

    gps_dev = (gps_dev_t)dev;

    if (gps_dev->ops->gps_control) {
        ret = gps_dev->ops->gps_control(gps_dev, cmd, args);
    }

    return ret;
}

err_t hal_gps_register(gps_dev_t gps_dev, const char* name, uint32_t flag, void* data)
{
    err_t ret;
    struct device* device;

    ASSERT(gps_dev != NULL);

    device = &(gps_dev->parent);

    device->type = Device_Class_Char;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_gps_init;
    device->open = hal_gps_open;
    device->close = hal_gps_close;
    device->read = hal_gps_read;
    device->write = NULL;
    device->control = hal_gps_control;
    device->user_data = data;

    /* register a character device */
    ret = device_register(device, name, flag);

    return ret;
}