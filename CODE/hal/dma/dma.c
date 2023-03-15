// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/6.
//

#include "dma.h"



err_t hal_dma_register(struct dma_device * dma, const char *name, uint32_t flag)
{
    err_t ret;
    struct device *device;

    ASSERT(dma != NULL);
    ASSERT((flag & DEVICE_FLAG_RDWR) != DEVICE_FLAG_RDWR);

    device = &(dma->parent);

    device->type = Device_Class_MTD;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = NULL;
    device->write = NULL;
    device->control = NULL;
    device->user_data = NULL;

    /* register a dma device */
    ret = device_register(device, name, flag | DEVICE_FLAG_STANDALONE);

    return ret;
}
