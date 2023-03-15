// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "mag.h"
#include "driver/io.h"
#include "drivers/drv_exti.h"


static err_t hal_mag_init(struct device* dev)
{
    err_t ret = E_OK;
    mag_dev_t mag;

    ASSERT(dev != NULL);
    mag = (mag_dev_t)dev;

    /* apply configuration */
    if (mag->ops->mag_config) {
        ret = mag->ops->mag_config(mag, &mag->config);
    }

    return ret;
}

static err_t hal_mag_open(struct device* dev,
                           uint16_t oflag)
{
    mag_dev_t mag;

    ASSERT(dev != NULL);

    mag = (mag_dev_t)dev;

    if (mag->parent.user_data)
    {
        io_tag exti = *(io_tag *)mag->parent.user_data;
        exti_init(exti, mag->ops->exti_cb, 0, NVIC_PRIO_EXTI, EXTI_RISING);
        exti_enable(exti);
    }
    return E_OK;
}

static err_t hal_mag_close(struct device* dev)
{
    mag_dev_t mag;

    ASSERT(dev != NULL);

    mag = (mag_dev_t)dev;

    if (mag->parent.user_data)
    {
        io_tag exti = *(io_tag *)mag->parent.user_data;
        exti_disable(exti);
    }
    return E_RROR;
}


static size_t hal_mag_read(struct device* dev,
                              off_t pos,
                              void* buffer,
                              size_t size)
{
    size_t rb = 0;
    mag_dev_t mag;

    ASSERT(dev != NULL);

    mag = (mag_dev_t)dev;

    if (mag->ops->mag_read && size) {
        rb = mag->ops->mag_read(mag, pos, buffer, size);
    }

    return rb;
}

static err_t hal_mag_control(struct device* dev,
                                int cmd,
                                void* args)
{
    err_t ret = E_OK;
    mag_dev_t mag;

    ASSERT(dev != NULL);

    mag = (mag_dev_t)dev;

    if (mag->ops->mag_control) {
        ret = mag->ops->mag_control(mag, cmd, args);
    }

    return ret;
}

err_t hal_mag_register(mag_dev_t mag, const char* name, uint32_t flag, void* data)
{
    err_t ret;
    struct device* device;

    ASSERT(mag != NULL);

    device = &(mag->parent);

    device->type = (mag->bus_type == MAG_SPI_BUS_TYPE) ? Device_Class_SPIDevice : Device_Class_I2CBUS;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_mag_init;
    device->open = hal_mag_open;
    device->close = hal_mag_close;
    device->read = hal_mag_read;
    device->write = NULL;
    device->control = hal_mag_control;
    device->user_data = data;

    /* register a character device */
    ret = device_register(device, name, flag);

    return ret;
}