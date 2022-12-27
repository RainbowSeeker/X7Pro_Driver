// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/8.
//

#include "rm3100.h"
#include "driver/io.h"
#include "hal/spi/spi.h"
#include "hal/mag/mag.h"
#include "drivers/drv_exti.h"
#include "nvic.h"

#define DRV_DBG(...)    printf(__VA_ARGS__)

static light_device_t spi_dev;

#define RM3100_BUF_SIZE   (9)
struct double_buf
{
    uint8_t buf[RM3100_BUF_SIZE * 2];
    uint8_t idx;
};

static DMA_DATA struct double_buf rm3100_dma_data = {0};

//upate rate enum
enum
{
    UR_600HZ = 0,
    UR_300HZ,
    UR_150HZ,
    UR_75HZ,
    UR_37HZ,
};

static err_t _modify_reg(light_device_t spi_device, uint8_t reg, uint8_t val)
{
    uint8_t r_val;

    ERROR_TRY(spi_write_reg8(spi_device, reg, val));
    ERROR_TRY(spi_read_reg8_msk(spi_device, reg, &r_val));

    return val == r_val ? E_OK : E_RROR;
}

static void exti_handler()
{
    // rechange the recv buf.
    rm3100_dma_data.idx = !rm3100_dma_data.idx;
    // transfer message
    spi_read_multi_reg8_msk(spi_dev, RM3100_MX, &rm3100_dma_data.buf[rm3100_dma_data.idx * RM3100_BUF_SIZE], RM3100_BUF_SIZE);
}

static err_t mag_measure(float mag[3])
{
    OS_ENTER_CRITICAL();

    uint8_t *raw = &rm3100_dma_data.buf[!rm3100_dma_data.idx * RM3100_BUF_SIZE];
    for (uint8_t i = 0; i < 3; ++i)
    {
        mag[i] = (float )(((raw[3 * i]<<24)|(raw[3 * i + 1]<<16)|raw[3 * i + 2]<<8)>>8) * RM3100_SCALE;
    }
    OS_EXIT_CRITICAL();

    return E_OK;
}

size_t mag_read(mag_dev_t mag, off_t pos, void* data, size_t size)
{
    if (data == NULL)
        return 0;

    if (mag_measure(((float *) data)) != E_OK)
    {
        return 0;
    }

    return size;
}

const static struct mag_ops __mag_ops = {
        NULL,
        NULL,
        mag_read,
        exti_handler
};

/**
 * verify the default cycle Count Registers
 * @param dev
 * @return
 */
static err_t _verify_CCV(light_device_t device)
{
    uint8_t value[6];
    spi_read_multi_reg8_msk(device, RM3100_CCX_M, value, 6);
    if (value[0] == 0x00 && value[1] == 0xC8
        && value[2] == 0x00 && value[3] == 0xC8
        && value[4] == 0x00 && value[5] == 0xC8)
    {
        return E_OK;
    }
    return E_RROR;
}

static err_t _modify_TMRC(light_device_t device, uint8_t rate)
{
    uint8_t tmrc_val[5] = {
            [UR_600HZ] = 0x92,
            [UR_300HZ] = 0x93,
            [UR_150HZ] = 0x94,
            [UR_75HZ ] = 0x95,
            [UR_37HZ ] = 0x96,//default
    };

    ERROR_TRY(_modify_reg(device, RM3100_TMRC, tmrc_val[rate]));

    return E_OK;
}

/**
 *  set continuous mode (Bit0 = 1), DRDY to HIGH after a full measurement by CMX, CMY, CMZ
 * @param device
 * @return
 */
static err_t _modify_CCM(light_device_t device)
{
    while (_modify_reg(device, RM3100_CMM, 0x79) != E_OK);
    return E_OK;
}

static err_t lowlevel_init(void)
{
    uint8_t mag_id;

    /* init spi bus */
    ERROR_TRY(light_device_open(spi_dev, DEVICE_OFLAG_RDWR));
    
    // verify the revision identification
    ERROR_TRY(spi_read_reg8_msk(spi_dev, RM3100_REVID, &mag_id));
    if (mag_id != RM3100_ID) {
        DRV_DBG("rm3100 wrong chip id:0x%x\n", mag_id);
        return ERROR;
    }

    ERROR_TRY(_verify_CCV(spi_dev));

    ERROR_TRY(_modify_TMRC(spi_dev, UR_150HZ));

    ERROR_TRY(_modify_CCM(spi_dev));

    return E_OK;
}

static struct mag_device mag_dev = {
        .ops = &__mag_ops,
        .config = {0},
        .bus_type = MAG_SPI_BUS_TYPE
};

err_t drv_rm3100_init(const char* mag_device_name)
{
    /* Initialize mag */
    static struct spi_device spi_device;
    static io_tag cs = PF2;
    static io_tag exti = PE4;
    io_set(cs, IO_HIGH);
    io_init(cs, CS_CONFIG);
    ERROR_TRY(spi_bus_attach_device(&spi_device,
                                    "rm3100",
                                    "spi2",
                                    (void *) &cs));

    /* config spi */
    struct spi_configuration cfg = {
            .data_width = 8,
            .mode = SPI_MODE_3 | SPI_MSB,
            .max_hz = RM3100_MAX_SPI_CLK_HZ
    };
    ERROR_TRY(spi_configure_device(&spi_device, &cfg));


    spi_dev = light_device_find("rm3100");
    ASSERT(spi_dev != NULL);

    ERROR_TRY(lowlevel_init());

    ERROR_TRY(hal_mag_register(&mag_dev, mag_device_name, DEVICE_FLAG_RDWR, &exti));

    return E_OK;
}