#include "sd.h"

#define SECTOR_SIZE 512

/* local sector buffer */
static DMA_DATA uint8_t sector_buffer[SECTOR_SIZE];

static err_t hal_sd_init(device_t dev)
{
    err_t ret = E_OK;
    sd_dev_t sd;

    ASSERT(dev != NULL);
    sd = (sd_dev_t) dev;

    /* init low-level device */
    if (sd->ops->init)
    {
        ret = sd->ops->init(sd);
    }

    return ret;
}

static size_t hal_sd_read(device_t dev, off_t pos, void *buffer, size_t size)
{
    uint32_t sector = pos;
    uint32_t count = size;
    uint8_t *rp = (uint8_t *) buffer;
    sd_dev_t sd;
    int i;

    ASSERT(dev != NULL);
    sd = (sd_dev_t) dev;


    /* check if the buffer address is 4B allignment since DMA is configured to transfer word, 
    make sure the buffer is 4B allignment to improve the transfer speed */
    if (((uint32_t) buffer & 0x03) || !IS_AXI_SRAM(buffer))  // SDMMC1's IDMA only can visit AXI_SRAM.
    {
        for (i = 0; i < count; i++)
        {
            /* read 1 sector */
            if (sd->ops->read_disk(sd, sector_buffer, sector + i, 1) != E_OK)
            {
                if (dev->rx_indicate)
                {
                    dev->rx_indicate(dev, i);
                }
                return i;
            }
            /*
                invalidate the scratch buffer before the next read to get the actual data instead of the cached one
            */
            scb_invalidate_dcache(sector_buffer, BLOCKSIZE);
            /* copy data to user buffer */
            memcpy(rp, sector_buffer, SECTOR_SIZE);
            rp += SECTOR_SIZE;
        }
    }
    else
    {
        /* Flush the D cache for the start and end of the receive buffer as
         * the cache will be invalidated after the transfer and any valid data
         * just before/after must be in memory at that point
         */
        scb_flush_invalidate_dcache(rp, count * BLOCKSIZE);
        /* read multi sectors */
        if (sd->ops->read_disk(sd, rp, sector, count) != E_OK)
        {
            return 0;
        }
    }

    if (dev->rx_indicate)
    {
        dev->rx_indicate(dev, size);
    }

    return size;
}

static size_t hal_sd_write(device_t dev, off_t pos, const void *buffer, size_t size)
{
    uint32_t sector = pos;
    uint32_t count = size;
    uint8_t *wp = (uint8_t *) buffer;
    sd_dev_t sd;
    int i;

    ASSERT(dev != NULL);
    sd = (sd_dev_t) dev;

    /* check if the buffer address is 4B allignment since DMA is configured to transfer word, 
    make sure the buffer is 4B allignment to improve the transfer speed */
    if (((uint32_t) buffer & 0x03) || !IS_AXI_SRAM(buffer))  // SDMMC1's IDMA only can visit AXI_SRAM.
    {
        //invalidate the buffer before the next write to get the actual data instead of the cached one
        scb_invalidate_dcache(sector_buffer, BLOCKSIZE);
        SCB_InvalidateDCache_by_Addr((uint32_t *) sector_buffer, BLOCKSIZE);

        for (i = 0; i < count; i++)
        {
            /* copy data to a 4B alignment buffer */
            memcpy(sector_buffer, wp, SECTOR_SIZE);
            wp += SECTOR_SIZE;
            /* write 1 sector */
            if (sd->ops->write_disk(sd, (uint8_t *) sector_buffer, sector + i, 1) != E_OK)
            {
                return i;
            }
        }
    }
    else
    {
        // Flush the D cache to ensure the data to be written is in main memory
        scb_flush_dcache(wp, count * BLOCKSIZE);
        /* write multi sectors */
        if (sd->ops->write_disk(sd, wp, sector, count) != E_OK)
        {
            return 0;
        }
    }


    if (dev->tx_complete)
    {
        /* inform upper layer the write is completed */
        dev->tx_complete(dev, NULL);
    }

    return size;
}

err_t hal_sd_control(device_t dev, int cmd, void *args)
{
    err_t ret = E_OK;
    sd_dev_t sd;

    ASSERT(dev != NULL);
    sd = (sd_dev_t) dev;

    switch (cmd)
    {
        default:
            if (sd->ops->io_control)
            {
                ret = sd->ops->io_control(sd, cmd, args);
            }
            break;
    }

    return ret;
}

err_t hal_sd_register(sd_dev_t sd, const char *name, uint32_t flag, void *data)
{
    err_t ret;
    struct device *device;

    ASSERT(sd != NULL);

    device = &(sd->parent);

    device->type = Device_Class_SDIO;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = hal_sd_init;
    device->open = NULL;
    device->close = NULL;
    device->read = hal_sd_read;
    device->write = hal_sd_write;
    device->control = hal_sd_control;
    device->user_data = data;

    /* register a character device */
    ret = device_register(device, name, flag);

    return ret;
}
