// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "icm42688.h"
#include "hal/spi/spi.h"
#include "imu/accel.h"
#include "imu/gyro.h"
#include "driver/io.h"
#include "sensor/sensor_imu.h"
#include "drivers/drv_exti.h"
#include "nvic.h"

static light_device_t spi_dev;
static float gyro_range_scale;
static float accel_range_scale;

#define ICM42688_BUF_SIZE   (12)
struct double_buf
{
    uint8_t buf[ICM42688_BUF_SIZE * 2];
    uint8_t idx;
};

static DMA_DATA struct double_buf icm42688_dma_data = {0};

/* Re-implement this function to define customized rotation */
__WEAK void icm42688_rotate_to_ned(float *val)
{
    /* do nothing */
}

static err_t gyro_read_raw(int16_t gyr[3])
{
    OS_ENTER_CRITICAL();

    // Invalidate the D cache covering the area into which data has been read
    int16_t *raw = (int16_t *)(&icm42688_dma_data.buf[!icm42688_dma_data.idx * ICM42688_BUF_SIZE]);
    // big-endian to little-endian
    gyr[0] = int16_t_from_bytes((uint8_t *) &raw[3]);
    gyr[1] = int16_t_from_bytes((uint8_t *) &raw[4]);
    gyr[2] = int16_t_from_bytes((uint8_t *) &raw[5]);

    OS_EXIT_CRITICAL();
    return E_OK;
}

static err_t gyro_read_rad(float gyr[3])
{
    int16_t gyr_raw[3];

    ERROR_TRY(gyro_read_raw(gyr_raw));

    gyr[0] = gyro_range_scale * gyr_raw[0];
    gyr[1] = gyro_range_scale * gyr_raw[1];
    gyr[2] = gyro_range_scale * gyr_raw[2];
    // change to NED coordinate
    icm42688_rotate_to_ned(gyr);

    return E_OK;
}

static err_t gyro_config(gyro_dev_t gyro, const struct gyro_configure *cfg)
{
    ASSERT(cfg != NULL);

    gyro_range_scale = (GYRO_SCALE_2000DPS * PI / 180.0f);
    gyro->config = *cfg;

    return E_OK;
}

static void exti_handler()
{
    // rechange the recv buf.
    icm42688_dma_data.idx = !icm42688_dma_data.idx;
    // transfer message
    spi_read_multi_reg8_msk(spi_dev, ICM426XX_RA_ACCEL_DATA_X1, &icm42688_dma_data.buf[icm42688_dma_data.idx * ICM42688_BUF_SIZE], ICM42688_BUF_SIZE);
}

static size_t gyro_read(gyro_dev_t gyro, off_t pos, void *data, size_t size)
{
    if (data == NULL)
        return 0;

    if (gyro_read_rad(((float *) data)) != E_OK)
    {
        return 0;
    }

    return size;
}

const static struct gyro_ops _gyro_ops = {
        gyro_config,
        NULL,
        gyro_read,
        exti_handler
};



static err_t accel_read_raw(int16_t acc[3])
{
    OS_ENTER_CRITICAL();

    int16_t *raw = (int16_t *)(&icm42688_dma_data.buf[!icm42688_dma_data.idx * ICM42688_BUF_SIZE]);

    // big-endian to little-endian
    acc[0] = int16_t_from_bytes((uint8_t *) &raw[0]);
    acc[1] = int16_t_from_bytes((uint8_t *) &raw[1]);
    acc[2] = int16_t_from_bytes((uint8_t *) &raw[2]);

    OS_EXIT_CRITICAL();
    return E_OK;
}

static err_t accel_read_m_s2(float acc[3])
{
    int16_t acc_raw[3];

    ERROR_TRY(accel_read_raw(acc_raw));

    acc[0] = accel_range_scale * acc_raw[0];
    acc[1] = accel_range_scale * acc_raw[1];
    acc[2] = accel_range_scale * acc_raw[2];
    // change to NED coordinate
    icm42688_rotate_to_ned(acc);

    return E_OK;
}

static err_t accel_config(accel_dev_t accel, const struct accel_configure *cfg)
{
    ASSERT(cfg != NULL);

    accel_range_scale = (ONE_G / ACCEL_SCALE_16G);
    accel->config = *cfg;

    return E_OK;
}

static err_t accel_control(accel_dev_t accel, int cmd, void *arg)
{
    return E_OK;
}

static size_t accel_read(accel_dev_t accel, off_t pos, void *data, size_t size)
{
    if (data == NULL)
    {
        return 0;
    }

    if (accel_read_m_s2(((float *) data)) != E_OK)
    {
        return 0;
    }

    return size;
}

const static struct accel_ops _accel_ops = {
        accel_config,
        accel_control,
        accel_read,
};


// Possible output data rates (ODRs)
static uint8_t odrLUT[ODR_CONFIG_COUNT] = {  // see GYRO_ODR in section 5.6
        [ODR_CONFIG_8K] = 3,
        [ODR_CONFIG_4K] = 4,
        [ODR_CONFIG_2K] = 5,
        [ODR_CONFIG_1K] = 6,
};

// Possible gyro Anti-Alias Filter (AAF) cutoffs
static aaf_config_t aafLUT[AAF_CONFIG_COUNT] = {  // see table in section 5.3
        [AAF_CONFIG_258HZ]  = {6, 36, 10},
        [AAF_CONFIG_536HZ]  = {12, 144, 8},
        [AAF_CONFIG_997HZ]  = {21, 440, 6},
        [AAF_CONFIG_1962HZ] = {37, 1376, 4},
};


static err_t imu_init(void)
{
    uint8_t dev_id;

    /* init spi bus */
    ERROR_TRY(light_device_open(spi_dev, DEVICE_OFLAG_RDWR));

    /* soft reset */
    spi_write_reg8(spi_dev, ICM426XX_RA_PWR_MGMT0, 0);
    delay_ms(100);

    ERROR_TRY(spi_read_reg8_msk(spi_dev, MPU_RA_WHO_AM_I, &dev_id));
    if (dev_id != ICM42688P_WHO_AM_I_CONST)
    {
        printf("icm42688 unmatch chip id:%x\n", dev_id);
    }

    spi_write_reg8(spi_dev, ICM426XX_RA_PWR_MGMT0, ICM426XX_PWR_MGMT0_TEMP_DISABLE_OFF | ICM426XX_PWR_MGMT0_ACCEL_MODE_LN |ICM426XX_PWR_MGMT0_GYRO_MODE_LN);
    delay_ms(15);

    // Get desired output data rate
    uint8_t odrConfig = odrLUT[ODR_CONFIG_2K];

    spi_write_reg8(spi_dev, ICM426XX_RA_GYRO_CONFIG0, (3 - INV_FSR_2000DPS) << 5 | (odrConfig & 0x0F));
    delay_ms(15);

    spi_write_reg8(spi_dev, ICM426XX_RA_ACCEL_CONFIG0, (3 - INV_FSR_16G) << 5 | (odrConfig & 0x0F));
    delay_ms(15);

    // Configure gyro Anti-Alias Filter (see section 5.3 "ANTI-ALIAS FILTER")
    aaf_config_t aafConfig = aafLUT[AAF_CONFIG_258HZ];
    spi_write_reg8(spi_dev, ICM426XX_RA_GYRO_CONFIG_STATIC3, aafConfig.delt);
    spi_write_reg8(spi_dev, ICM426XX_RA_GYRO_CONFIG_STATIC4, aafConfig.deltSqr & 0xFF);
    spi_write_reg8(spi_dev, ICM426XX_RA_GYRO_CONFIG_STATIC5, (aafConfig.deltSqr >> 8) | (aafConfig.bitshift << 4));

    // Configure acc Anti-Alias Filter for 1kHz sample rate (see tasks.c)
    aafConfig = aafLUT[AAF_CONFIG_258HZ];
    spi_write_reg8(spi_dev, ICM426XX_RA_ACCEL_CONFIG_STATIC2, aafConfig.delt << 1);
    spi_write_reg8(spi_dev, ICM426XX_RA_ACCEL_CONFIG_STATIC3, aafConfig.deltSqr & 0xFF);
    spi_write_reg8(spi_dev, ICM426XX_RA_ACCEL_CONFIG_STATIC4, (aafConfig.deltSqr >> 8) | (aafConfig.bitshift << 4));

    // Configure gyro and acc UI Filters
    spi_write_reg8(spi_dev, ICM426XX_RA_GYRO_ACCEL_CONFIG0,
                 ICM426XX_ACCEL_UI_FILT_BW_LOW_LATENCY | ICM426XX_GYRO_UI_FILT_BW_LOW_LATENCY);

    spi_write_reg8(spi_dev, ICM426XX_RA_INT_CONFIG,
                 ICM426XX_INT1_MODE_PULSED | ICM426XX_INT1_DRIVE_CIRCUIT_PP | ICM426XX_INT1_POLARITY_ACTIVE_HIGH);
    spi_write_reg8(spi_dev, ICM426XX_RA_INT_CONFIG0, ICM426XX_UI_DRDY_INT_CLEAR_ON_SBR);

    spi_write_reg8(spi_dev, ICM426XX_RA_INT_SOURCE0, ICM426XX_UI_DRDY_INT1_EN_ENABLED);

    uint8_t intConfig1Value;
    spi_read_reg8_msk(spi_dev, ICM426XX_RA_INT_CONFIG1, &intConfig1Value);
    // Datasheet says: "User should change setting to 0 from default setting of 1, for proper INT1 and INT2 pin operation"
    intConfig1Value &= ~(1 << ICM426XX_INT_ASYNC_RESET_BIT);
    intConfig1Value |= (ICM426XX_INT_TPULSE_DURATION_8 | ICM426XX_INT_TDEASSERT_DISABLED);

    spi_write_reg8(spi_dev, ICM426XX_RA_INT_CONFIG1, intConfig1Value);

    return E_OK;
}

#define GYRO_CONFIGURE                                \
    {                                                 \
        1000,                   /* 1K sample rate */  \
            92,                 /* 256Hz bandwidth */ \
            GYRO_RANGE_2000DPS, /* +-2000 deg/s */    \
    }

#define ACCEL_CONFIGURE                           \
    {                                             \
        1000,                /* 1K sample rate */ \
            99,              /* 99Hz bandwidth */ \
            ACCEL_RANGE_16G, /* +-16g */          \
    }

static struct gyro_device gyro_dev = {
        .ops = &_gyro_ops,
        .config = GYRO_CONFIGURE,
        .bus_type = GYRO_SPI_BUS_TYPE
};

static struct accel_device accel_dev = {
        .ops = &_accel_ops,
        .config = ACCEL_CONFIGURE,
        .bus_type = GYRO_SPI_BUS_TYPE
};

err_t drv_icm42688_init(const char* gyro_dev_name, const char* accel_dev_name)
{
    /* Initialize gyroscope */
    static struct spi_device spi_device;
    static io_tag cs = PA15;
    static io_tag exti = PB15;
    io_init(cs, CS_CONFIG);
    ERROR_TRY(spi_bus_attach_device(&spi_device,
                                    "icm42688",
                                    "spi4",
                                    (void *) &cs));

    /* config spi */
    struct spi_configuration cfg = {
            .data_width = 8,
            .mode = SPI_MODE_3 | SPI_MSB,
            .max_hz = ICM426XX_MAX_SPI_CLK_HZ
    };
    ERROR_TRY(spi_configure_device(&spi_device, &cfg));

    spi_dev = light_device_find("icm42688");
    ASSERT(spi_dev != NULL);

    /* device low-level init */
    ERROR_TRY(imu_init());

    /* register gyro hal device */
    ERROR_TRY(hal_gyro_register(&gyro_dev, gyro_dev_name, DEVICE_FLAG_RDWR, &exti));

    /* register accel hal device */
    ERROR_TRY(hal_accel_register(&accel_dev, accel_dev_name, DEVICE_FLAG_RDWR, NULL));

    return E_OK;
}
