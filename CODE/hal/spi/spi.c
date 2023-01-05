// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "spi.h"
#include "dma/dma.h"

#define spi_lock(_bus)          os_sem_take(_bus->lock, osWaitForever)
#define spi_unlock(_bus)        os_sem_release(_bus->lock)

static err_t spi_bus_init(struct spi_bus *bus, const char *name)
{
    light_device_t device;

    ASSERT(bus != NULL);

    device = &bus->parent;

    /* set device type */
    device->type = Device_Class_SPIBUS;
    /* not allowed to directly read/write spi bus */
    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = NULL;
    device->write = NULL;
    device->control = NULL;

    /* register to device manager */
    return light_device_register(device, name, DEVICE_FLAG_RDWR);
}

err_t spi_bus_register(struct spi_bus *bus,
                       const char *name,
                       const struct spi_ops *ops)
{
    err_t result;

    result = spi_bus_init(bus, name);

    if (result != E_OK)
        return result;

    /* initialize os_mutex lock */
    bus->lock = os_sem_create(1);
    /* set ops */
    bus->ops = ops;
    /* initialize owner */
    bus->owner = NULL;

    return E_OK;
}

static size_t spi_bus_read(light_device_t dev,
                           off_t pos,
                           void *buffer,
                           size_t size)
{
    struct spi_device *device;

    device = (struct spi_device *) dev;
    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);

    return spi_transfer(device, NULL, buffer, size);
}

static size_t spi_bus_write(light_device_t dev,
                            off_t pos,
                            const void *buffer,
                            size_t size)
{
    struct spi_device *device;

    device = (struct spi_device *) dev;
    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);

    return spi_transfer(device, (void *)buffer, NULL, size);
}

static err_t spi_bus_control(light_device_t dev,
                             int cmd,
                             void *args)
{
    switch (cmd)
    {
        case 0: /* set device */
            break;

        case 1:
            break;
    }

    return E_OK;
}

static err_t spi_device_init(struct spi_device *dev, const char *name)
{
    light_device_t device;
    ASSERT(dev != NULL);

    device = &(dev->parent);

    /* set device type */
    device->type = Device_Class_SPIDevice;
    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = spi_bus_read;
    device->write = spi_bus_write;
    device->control = spi_bus_control;

    /* register to device manager */
    return light_device_register(device, name, DEVICE_FLAG_RDWR);
}


err_t spi_bus_attach_device(struct spi_device *device,
                            const char *name,
                            const char *bus_name,
                            void *user_data)
{
    err_t result;
    light_device_t bus;

    /* get physical spi bus */
    bus = light_device_find(bus_name);

    if (bus != NULL && bus->type == Device_Class_SPIBUS)
    {
        device->bus = (struct spi_bus *) bus;

        /* initialize spidev device */
        result = spi_device_init(device, name);

        if (result != E_OK)
            return result;

        memset(&device->config, 0, sizeof(device->config));
        device->parent.user_data = user_data;

        return E_OK;
    }

    /* not found the host bus */
    return -ERROR;
}

err_t spi_configure_device(struct spi_device *device,
                    struct spi_configuration *cfg)
{

    ASSERT(device != NULL);

    /* set configuration */
    device->config.data_width = cfg->data_width;
    device->config.mode = cfg->mode & SPI_MODE_MASK;
    device->config.max_hz = cfg->max_hz;

    return E_OK;
}

err_t spi_send_then_recv(struct spi_device *device,
                         void *send_buf,
                         size_t send_length,
                         void *recv_buf,
                         size_t recv_length)
{
    err_t result;

    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);
    ASSERT(send_length < DMA_THRESHOLD);

    result = spi_lock(device->bus);

    if (result == E_OK)
    {
        /* initial message */
        struct spi_message message[2] = {
                {send_buf,NULL,send_length,NULL, 1,0},
                {NULL,recv_buf,recv_length,NULL, 0,1},
        };

        result = device->bus->ops->xfer(device, &message[0]);

        if (result != E_OK)
        {
            os_set_errno(-E_IO);
            goto __exit;
        }

        result = device->bus->ops->xfer(device, &message[1]);

        if (result == E_BUSY)   //dma transmitting ...
        {
            return E_BUSY;
        }
        else if (result != E_OK) os_set_errno(-E_IO);
    }
    else
    {
        return -E_IO;
    }

    __exit:
    spi_unlock(device->bus);
    return result;
}

size_t spi_transfer(struct spi_device *device,
                    void *send_buf,
                    void *recv_buf,
                    size_t length)
{
    err_t result;

    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);

    result = spi_lock(device->bus);

    if (result == E_OK)
    {
        /* initial message */
        struct spi_message message = {
                send_buf, recv_buf, length, NULL, 1, 1
        };

        /* transfer message */
        result = device->bus->ops->xfer(device, &message);

        if (result == E_OK)
        {
            spi_unlock(device->bus);
            return length;
        }
        else if (result == E_BUSY)   //dma transmitting ...
        {
            return length;
        }
    }
    else
    {
        os_set_errno(-E_IO);
        return 0;
    }

    os_set_errno(-E_IO);
    spi_unlock(device->bus);
    return 0;
}

struct spi_message *spi_transfer_message(struct spi_device *device,
                                         struct spi_message *message)
{
    err_t result;

    ASSERT(device != NULL);

    result = spi_lock(device->bus);

    if (result != E_OK)
    {
        os_set_errno(-EBUSY);

        return message;
    }

    /* transmit SPI message */
    result = device->bus->ops->xfer(device, message);

    if (result != E_OK)
    {
        if (result == E_BUSY)   //dma transmitting ...
        {
            return message;
        }

        os_set_errno(-E_IO);
    }

    /* release bus lock */
    spi_unlock(device->bus);

    return message;
}

err_t spi_take_bus(struct spi_device *device)
{
    err_t result;

    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);

    result = spi_lock(device->bus);

    if (result != E_OK)
    {
        os_set_errno(-EBUSY);
        return -EBUSY;
    }

    return result;
}

err_t spi_release_bus(struct spi_device *device)
{
    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);
//    ASSERT(device->bus->owner == device);

    /* release lock */
    spi_unlock(device->bus);

    return E_OK;
}

err_t spi_take(struct spi_device *device)
{
    err_t result;
    struct spi_message message;

    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);

    memset(&message, 0, sizeof(message));
    message.cs_take = 1;

    result = device->bus->ops->xfer(device, &message);

    return result;
}

err_t spi_release(struct spi_device *device)
{
    err_t result;
    struct spi_message message;

    ASSERT(device != NULL);
    ASSERT(device->bus != NULL);

    memset(&message, 0, sizeof(message));
    message.cs_release = 1;

    result = device->bus->ops->xfer(device, &message);

    return result;
}


