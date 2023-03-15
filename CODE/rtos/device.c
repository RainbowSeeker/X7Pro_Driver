// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/1.
//

#include "device.h"
#include "thread.h"


static LIST_DEF(device_list);       /* associate all devices */
static size_t device_num = 0;       /* calculate the number of device */


/**
 * This function registers a device driver with specified name.
 *
 * @param dev the pointer of device driver structure
 * @param name the device driver's name
 * @param flags the capabilities flag of device
 *
 * @return the error code, E_OK on initialization successfully.
 */
err_t device_register(device_t device, const char *name, uint16_t flags)
{
    if (device == NULL)
        return E_RROR;

    if (device_find(name) != NULL)
        return E_RROR;

    strncpy(device->name, name, NAME_MAX_LEN);

    OS_ENTER_CRITICAL();
    list_insert_after(&device_list, &device->list);
    device_num++;
    OS_EXIT_CRITICAL();

    device->flag = flags;
    device->ref_count = 0;
    device->open_flag = 0;

    return E_OK;
}


/**
 * This function removes a previously registered device driver
 *
 * @param dev the pointer of device driver structure
 *
 * @return the error code, E_OK on successfully.
 */
err_t device_unregister(device_t device)
{
    ASSERT(device != NULL);
    OS_ENTER_CRITICAL();
    list_remove(&device->list);
    OS_EXIT_CRITICAL();
    return E_OK;
}

/**
 * This function finds a device driver by specified name.
 *
 * @param name the device driver's name
 *
 * @return the registered device driver on successful, or NULL on failure.
 */
device_t device_find(const char *name)
{
    device_t device = NULL;
    struct list_node *node = NULL;

    /* parameter check */
    if ((name == NULL) || (device_num == 0)) return NULL;

    /* enter critical */
    OS_ENTER_CRITICAL();

    /* try to find object */
    list_for_each(node, &device_list)
    {
        device = list_entry(node, struct device, list);
        if (strncmp(device->name, name, NAME_MAX_LEN) == 0)
        {
            /* leave critical */
            OS_EXIT_CRITICAL();
            return device;
        }
    }

    /* leave critical */
    OS_EXIT_CRITICAL();

    return NULL;
}


/**
 * This function creates a device object with user data size.
 *
 * @param type, the kind type of this device object.
 * @param attach_size, the size of user data.
 *
 * @return the allocated device object, or NULL when failed.
 */
device_t device_create(int type, int attach_size)
{
    int size;
    device_t device;

    size = ALIGN(sizeof(struct device), ALIGN_SIZE);
    attach_size = ALIGN(attach_size, ALIGN_SIZE);
    /* use the total size */
    size += attach_size;

    device = (device_t) malloc(size);
    if (device)
    {
        memset(device, 0x0, sizeof(struct device));
        device->type = (enum device_class) type;
    }

    return device;
}


/**
 * This function destroy the specific device object.
 *
 * @param dev, the specific device object.
 */
void device_destroy(device_t dev)
{
    ASSERT(dev != NULL);

    device_unregister(dev);

    /* release this device object */
    free(dev);
}


/**
 * This function will initialize the specified device
 *
 * @param dev the pointer of device driver structure
 *
 * @return the result
 */
err_t device_init(device_t dev)
{
    err_t result = E_OK;

    ASSERT(dev != NULL);

    /* get device_init handler */
    if (dev->init != NULL)
    {
        if (!(dev->flag & DEVICE_FLAG_ACTIVATED))
        {
            result = dev->init(dev);
            if (result != E_OK)
            {
                printf("To initialize device:%s failed. The error code is %d\n", dev->name, result);
            }
            else
            {
                dev->flag |= DEVICE_FLAG_ACTIVATED;
            }
        }
    }

    return result;
}

/**
 * This function will open a device
 *
 * @param dev the pointer of device driver structure
 * @param oflag the flags for device open
 *
 * @return the result
 */
err_t device_open(device_t dev, uint16_t oflag)
{
    err_t result = E_OK;
    ASSERT(dev != NULL);

    /* if device is not initialized, initialize it. */
    if (!(dev->flag & DEVICE_FLAG_ACTIVATED))
    {
        if (dev->init != NULL)
        {
            result = dev->init(dev);
            if (result != E_OK)
            {
                printf("To initialize device:%s failed. The error code is %d\n", dev->name, result);
                return result;
            }
        }

        dev->flag |= DEVICE_FLAG_ACTIVATED;
    }

    /* device is a standalone device and opened */
    if ((dev->flag & DEVICE_FLAG_STANDALONE) &&
        (dev->open_flag & DEVICE_OFLAG_OPEN))
    {
        return E_BUSY;
    }

    /* call device_open interface */
    if (dev->open != NULL)
    {
        result = dev->open(dev, oflag);
    }
    else
    {
        /* set open flag */
        dev->open_flag = (oflag & DEVICE_OFLAG_MASK);
    }

    /* set open flag */
    if (result == E_OK || result == E_NOSYS)
    {
        dev->open_flag |= DEVICE_OFLAG_OPEN;

        dev->ref_count++;
        /* don't let bad things happen silently. If you are bitten by this assert,
         * please set the ref_count to a bigger type. */
        ASSERT(dev->ref_count != 0);
    }

    return result;
}


/**
 * This function will close a device
 *
 * @param dev the pointer of device driver structure
 *
 * @return the result
 */
err_t device_close(device_t dev)
{
    err_t result = E_OK;
    ASSERT(dev != NULL);

    if (dev->ref_count == 0)
        return E_RROR;

    dev->ref_count--;

    if (dev->ref_count != 0)
        return E_OK;

    /* call device_close interface */
    if (dev->close != NULL)
    {
        result = dev->close(dev);
    }

    /* set open flag */
    if (result == E_OK || result == E_NOSYS)
        dev->open_flag = DEVICE_OFLAG_CLOSE;

    return result;
}


/**
 * This function will read some data from a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of reading
 * @param buffer the data buffer to save read data
 * @param size the size of buffer
 *
 * @return the actually read size on successful, otherwise negative returned.
 *
 * @note since 0.4.0, the unit of size/pos is a block for block device.
 */
size_t device_read(device_t dev, off_t pos, void *buffer, size_t size)
{
    ASSERT(dev != NULL);
    ASSERT(dev->flag & DEVICE_FLAG_RDONLY);

    if (dev->ref_count == 0)
    {
        os_set_errno(E_RROR);

        return 0;
    }

    /* call device_read interface */
    if (dev->read != NULL)
    {
        return dev->read(dev, pos, buffer, size);
    }

    /* set error code */
    os_set_errno(E_NOSYS);

    return 0;
}


/**
 * This function will write some data to a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of written
 * @param buffer the data buffer to be written to device
 * @param size the size of buffer
 *
 * @return the actually written size on successful, otherwise negative returned.
 *
 * @note since 0.4.0, the unit of size/pos is a block for block device.
 */
size_t device_write(device_t dev, off_t pos, const void *buffer, size_t size)
{
    ASSERT(dev != NULL);
    ASSERT(dev->flag & DEVICE_FLAG_WRONLY);

    if (dev->ref_count == 0)
    {
        os_set_errno(E_RROR);
        return 0;
    }

    /* call device_write interface */
    if (dev->write != NULL)
    {
        return dev->write(dev, pos, buffer, size);
    }

    /* set error code */
    os_set_errno(E_NOSYS);

    return 0;
}


/**
 * This function will perform a variety of control functions on devices.
 *
 * @param dev the pointer of device driver structure
 * @param cmd the command sent to device
 * @param arg the argument of command
 *
 * @return the result
 */
err_t device_control(device_t dev, int cmd, void *arg)
{
    ASSERT(dev != NULL);

    /* call device_control interface */
    if (dev->control != NULL)
    {
        return dev->control(dev, cmd, arg);
    }

    return E_NOSYS;
}


/**
 * This function will set the reception indication callback function. This callback function
 * is invoked when this device receives data.
 *
 * @param dev the pointer of device driver structure
 * @param rx_ind the indication callback function
 *
 * @return E_OK
 */
err_t device_set_rx_indicate(device_t dev, err_t (*rx_ind)(device_t dev, size_t size))
{
    ASSERT(dev != NULL);

    dev->rx_indicate = rx_ind;

    return E_OK;
}


/**
 * This function will set the indication callback function when device has
 * written data to physical hardware.
 *
 * @param dev the pointer of device driver structure
 * @param tx_done the indication callback function
 *
 * @return E_OK
 */
err_t device_set_tx_complete(device_t dev, err_t (*tx_done)(device_t dev, void *buffer))
{
    ASSERT(dev != NULL);

    dev->tx_complete = tx_done;

    return E_OK;
}

