// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/6.
//

#include "dma.h"



err_t hal_dma_register(struct dma_device * dma, const char *name, uint32_t flag)
{
    err_t ret;
    struct light_device *device;

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
    ret = light_device_register(device, name, flag | DEVICE_FLAG_STANDALONE);

    //初始化失败，则开启设备，使得设备无法再次打开！
    if (ret != E_OK) light_device_open(device, DEVICE_OFLAG_OPEN);
    return ret;
}
