// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/17.
//

#include "fm25vx.h"
#include "drivers/drv_spi.h"
#include "drivers/io.h"
#include "hal/spi/spi.h"

#define DRV_DBG(...) printf(__VA_ARGS__)

static device_t spi_dev;

#define FRAM_BUF_SIZE   (36)
static DMA_DATA uint8_t send_buf[FRAM_BUF_SIZE];
static DMA_DATA uint8_t recv_buf[FRAM_BUF_SIZE];

static size_t _read(device_t dev, off_t pos, void *buffer, size_t size)
{
    send_buf[0] = 0x03;
    for (int i = 0; i < size;)
    {
        int true_len = size - i;
        int rx_len = MIN(true_len, 29);
        send_buf[1] = (pos >> 8) & 0xff;
        send_buf[2] = pos & 0xff;
        spi_transfer((struct spi_device *)spi_dev, send_buf, recv_buf, rx_len + 3);
        spi_wait(spi_dev);
        memcpy(buffer + i, recv_buf + 3, rx_len);
        pos += rx_len;
        i += rx_len;
        delay_ms(1);
    }
    return size;
}

static size_t _write(device_t dev, off_t pos, const void *buffer, size_t size)
{
    send_buf[0] = 0x02;
    for (int i = 0; i < size; i += 32)
    {
        int true_len=size-i;
        spi_sendrecv8((struct spi_device *) spi_dev, 0x06);
        delay_ms(1);
        send_buf[1] = (pos >> 8) & 0xff;
        send_buf[2] = pos & 0xff;
        memcpy(&send_buf[3], buffer + i, MIN(true_len, 32));
        spi_send((struct spi_device *)spi_dev, send_buf, true_len + 3);
        pos += 32;
        delay_ms(1);
    }
    return size;
}

static err_t lowlevel_init(void)
{
    uint8_t retry = 0;
    uint8_t buf[20] = {0x9F};
    ERROR_TRY(device_open(spi_dev, DEVICE_OFLAG_RDWR));

    do {
        spi_transfer((struct spi_device *)spi_dev, buf, &buf[10], 10);
        systime_msleep(10);
    } while (buf[17] != 0xC2 && ++retry < 20);

    if(retry >= 20)
    {
        DRV_DBG("\nfram init error!\n");
        return E_RROR;
    }

    memset(send_buf, 0, FRAM_BUF_SIZE);
    memset(recv_buf, 0, FRAM_BUF_SIZE);

    return E_OK;
}

static struct device fm25v05;

err_t drv_fm25v05_init(const char *fram_device_name)
{
    static struct spi_device spi_device;
    static io_tag cs = PF5;
    io_init(cs, CS_CONFIG);
    ERROR_TRY(spi_bus_attach_device(&spi_device,
                                    "fm25v05",
                                    "spi2",
                                    (void *) &cs));

    /* config spi */
    struct spi_configuration cfg = {
            .data_width = 8,
            .mode = SPI_MODE_3 | SPI_MSB,
            .max_hz = FM25V05_MAX_SPI_CLK_HZ
    };
    ERROR_TRY(spi_configure_device(&spi_device, &cfg));

    spi_dev = device_find("fm25v05");
    ASSERT(spi_dev != NULL);

    /* driver internal init */
    ERROR_TRY(lowlevel_init());

    device_t device = &fm25v05;
    device->type = Device_Class_SPIDevice;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;
    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = _read;
    device->write = _write;

    return device_register(device, fram_device_name, DEVICE_FLAG_RDWR);
}
