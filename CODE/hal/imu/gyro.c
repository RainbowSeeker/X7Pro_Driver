// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "gyro.h"
#include "driver/io.h"
#include "drivers/drv_exti.h"

static err_t hal_gyro_init(struct light_device* dev)
{
    err_t ret = E_OK;
    gyro_dev_t gyro;

    ASSERT(dev != NULL);
    gyro = (gyro_dev_t)dev;

    /* apply configuration */
    if (gyro->ops->gyro_config) {
        ret = gyro->ops->gyro_config(gyro, &gyro->config);
    }

    return ret;
}

static err_t hal_gyro_open(struct light_device* dev,
                            uint16_t oflag)
{
    gyro_dev_t gyro;

    ASSERT(dev != NULL);

    gyro = (gyro_dev_t)dev;
    if (gyro->parent.user_data)
    {
        io_t exti = *(io_t *)gyro->parent.user_data;
        exti_init(exti, gyro->ops->exti_cb, 0, NVIC_PRIO_EXTI, EXTI_RISING);
        exti_enable(exti);
    }

    return E_OK;
}

static err_t hal_gyro_close(struct light_device* dev)
{
    gyro_dev_t gyro;

    ASSERT(dev != NULL);

    gyro = (gyro_dev_t)dev;

    if (gyro->parent.user_data)
    {
        io_t exti = *(io_t *)gyro->parent.user_data;
        exti_disable(exti);
    }
    return E_OK;
}

static size_t hal_gyro_read(struct light_device* dev,
                               off_t pos,
                               void* buffer,
                               size_t size)
{
    size_t rb = 0;
    gyro_dev_t gyro;

    ASSERT(dev != NULL);

    gyro = (gyro_dev_t)dev;

    if (gyro->ops->gyro_read && size) {
        rb = gyro->ops->gyro_read(gyro, pos, buffer, size);
    }

    return rb;
}

static err_t hal_gyro_control(struct light_device* dev,
                                 int cmd,
                                 void* args)
{
    err_t ret = E_OK;
    gyro_dev_t gyro;

    ASSERT(dev != NULL);

    gyro = (gyro_dev_t)dev;

    if (gyro->ops->gyro_control) {
        ret = gyro->ops->gyro_control(gyro, cmd, args);
    }
    return ret;
}

err_t hal_gyro_register(gyro_dev_t gyro, const char* name, uint32_t flag, void* data)
{
    err_t ret;
    struct light_device* device;

    ASSERT(gyro != NULL);

    device = &(gyro->parent);

    device->type = (gyro->bus_type == GYRO_SPI_BUS_TYPE) ? Device_Class_SPIDevice : Device_Class_I2CBUS;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_gyro_init;
    device->open = hal_gyro_open;
    device->close = hal_gyro_close;
    device->read = hal_gyro_read;
    device->write = NULL;
    device->control = hal_gyro_control;
    device->user_data = data;

    /* register a character device */
    ret = light_device_register(device, name, flag);

    return ret;
}