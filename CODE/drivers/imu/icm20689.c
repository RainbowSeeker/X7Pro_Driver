// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "icm20689.h"
#include "hal/imu/accel.h"
#include "hal/imu/gyro.h"
#include "hal/spi/spi.h"
#include "sensor/sensor_imu.h"
#include "nvic.h"
#include "drivers/drv_exti.h"

#define DRV_DBG(...)    printf(__VA_ARGS__)

#define DIR_READ       0x80
#define DIR_WRITE      0x00


#define BIT(_idx) (1 << _idx)
#define REG_VAL(_setbits, _clearbits) \
    (reg_val_t) { .setbits = (_setbits), .clearbits = (_clearbits) }


#define GYRO_RANGE_2000_DPS REG_VAL(BIT(3) | BIT(4), 0)
#define GYRO_RANGE_1000_DPS REG_VAL(BIT(4), BIT(3))
#define GYRO_RANGE_500_DPS  REG_VAL(BIT(3), BIT(4))
#define GYRO_RANGE_250_DPS  REG_VAL(0, BIT(3) | BIT(4))

#define GYRO_BW_5    REG_VAL(BIT(1) | BIT(2), BIT(0))
#define GYRO_BW_10   REG_VAL(BIT(0) | BIT(2), BIT(1))
#define GYRO_BW_20   REG_VAL(BIT(2), BIT(0) | BIT(1))
#define GYRO_BW_41   REG_VAL(BIT(0) | BIT(1), BIT(2))
#define GYRO_BW_92   REG_VAL(BIT(1), BIT(0) | BIT(2))
#define GYRO_BW_176  REG_VAL(BIT(0), BIT(1) | BIT(2))
#define GYRO_BW_250  REG_VAL(0, BIT(0) | BIT(1) | BIT(2))
#define GYRO_BW_3281 REG_VAL(BIT(0) | BIT(1) | BIT(2), 0)

#define ACCEL_RANGE_2_G  REG_VAL(0, BIT(3) | BIT(4))
#define ACCEL_RANGE_4_G  REG_VAL(BIT(3), BIT(4))
#define ACCEL_RANGE_8_G  REG_VAL(BIT(4), BIT(3))
#define ACCEL_RANGE_16_G REG_VAL(BIT(3) | BIT(4), 0)

#define ACCEL_BW_5_1   REG_VAL(BIT(1) | BIT(2), BIT(0))
#define ACCEL_BW_10_2  REG_VAL(BIT(0) | BIT(2), BIT(1))
#define ACCEL_BW_21_2  REG_VAL(BIT(2), BIT(0) | BIT(1))
#define ACCEL_BW_44_8  REG_VAL(BIT(0) | BIT(1), BIT(2))
#define ACCEL_BW_99    REG_VAL(BIT(1), BIT(0) | BIT(2))
#define ACCEL_BW_218_1 REG_VAL(BIT(0), BIT(1) | BIT(2))
#define ACCEL_BW_420   REG_VAL(BIT(0) | BIT(1) | BIT(2), 0)

typedef struct
{
    uint8_t setbits;
    uint8_t clearbits;
} reg_val_t;


static float gyro_range_scale;
static float accel_range_scale;
static light_device_t imu_spi_dev;

#define ICM20689_BUF_SIZE   (14)
struct double_buf
{
    uint8_t buf[ICM20689_BUF_SIZE * 2];
    uint8_t idx;
};

static BDMA_DATA struct double_buf icm20689_dma_data = {0};

/* Re-implement this function to define customized rotation */
__WEAK void icm20689_rotate_to_ned(float *val)
{
    /* do nothing */
}

static err_t __write_checked_reg(light_device_t spi_device, uint8_t reg, uint8_t val)
{
    uint8_t r_val;

    ERROR_TRY(spi_write_reg8(spi_device, reg, val));
    ERROR_TRY(spi_read_reg8_msk(spi_device, reg, &r_val));

    return (r_val == val) ? E_OK : E_RROR;
}

static err_t __modify_reg(light_device_t spi_device, uint8_t reg, reg_val_t reg_val)
{
    uint8_t value;

    ERROR_TRY(spi_read_reg8_msk(spi_device, reg, &value));

    value &= ~reg_val.clearbits;
    value |= reg_val.setbits;

    ERROR_TRY(__write_checked_reg(spi_device, reg, value));

    return E_OK;
}

static err_t gyro_set_dlpf_filter(uint32_t frequency_hz)
{
    reg_val_t reg_val;

    if (frequency_hz < 10)
    {
        reg_val = GYRO_BW_5;
    }
    else if (frequency_hz < 20)
    {
        reg_val = GYRO_BW_10;
    }
    else if (frequency_hz < 41)
    {
        reg_val = GYRO_BW_20;
    }
    else if (frequency_hz < 92)
    {
        reg_val = GYRO_BW_41;
    }
    else if (frequency_hz < 176)
    {
        reg_val = GYRO_BW_92;
    }
    else if (frequency_hz < 250)
    {
        reg_val = GYRO_BW_176;
    }
    else if (frequency_hz < 3281)
    {
        reg_val = GYRO_BW_250;
    }
    else
    {
        reg_val = GYRO_BW_3281;
    }

    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_CONFIG, reg_val));

    return E_OK;
}

static err_t gyro_set_range(uint32_t max_dps)
{
    reg_val_t reg_val;
    float lsb_per_dps;

    if (max_dps == 0)
    {
        max_dps = 2000;
    }

    if (max_dps <= 250)
    {
        reg_val = GYRO_RANGE_250_DPS;
        lsb_per_dps = 131;
    }
    else if (max_dps <= 500)
    {
        reg_val = GYRO_RANGE_500_DPS;
        lsb_per_dps = 65.5;
    }
    else if (max_dps <= 1000)
    {
        reg_val = GYRO_RANGE_1000_DPS;
        lsb_per_dps = 32.8;
    }
    else if (max_dps <= 2000)
    {
        reg_val = GYRO_RANGE_2000_DPS;
        lsb_per_dps = 16.4;
    }
    else
    {
        return E_INVAL;
    }

    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_GYRO_CONFIG, reg_val));

    gyro_range_scale = (PI / (180.0f * lsb_per_dps));

    return E_OK;
}

static err_t accel_set_dlpf_filter(uint32_t frequency_hz)
{
    reg_val_t reg_val;

    if (frequency_hz < 8)
    {
        reg_val = ACCEL_BW_5_1;
    }
    else if (frequency_hz < 16)
    {
        reg_val = ACCEL_BW_10_2;
    }
    else if (frequency_hz < 38)
    {
        reg_val = ACCEL_BW_21_2;
    }
    else if (frequency_hz < 72)
    {
        reg_val = ACCEL_BW_44_8;
    }
    else if (frequency_hz < 159)
    {
        reg_val = ACCEL_BW_99;
    }
    else if (frequency_hz < 319)
    {
        reg_val = ACCEL_BW_218_1;
    }
    else
    {
        reg_val = ACCEL_BW_420;
    }

    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_ACCEL_CONFIG2, reg_val));

    return E_OK;
}

static err_t accel_set_range(uint32_t max_g)
{
    reg_val_t reg_val;
    float lsb_per_g;

    if (max_g == 0)
    {
        max_g = 16;
    }

    if (max_g <= 2)
    {
        reg_val = ACCEL_RANGE_2_G;
        lsb_per_g = 16384;
    }
    else if (max_g <= 4)
    {
        reg_val = ACCEL_RANGE_4_G;
        lsb_per_g = 8192;
    }
    else if (max_g <= 8)
    {
        reg_val = ACCEL_RANGE_8_G;
        lsb_per_g = 4096;
    }
    else if (max_g <= 16)
    {
        reg_val = ACCEL_RANGE_16_G;
        lsb_per_g = 2048;
    }
    else
    {
        return E_INVAL;
    }

    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_ACCEL_CONFIG, reg_val));

    accel_range_scale = (ONE_G / lsb_per_g);

    return E_OK;
}

static err_t imu_init(void)
{
    uint8_t chip_id;

    /* open spi device */
    ERROR_TRY(light_device_open(imu_spi_dev, DEVICE_OFLAG_RDWR));

    /* soft reset */
    spi_write_reg8(imu_spi_dev, MPU_RA_PWR_MGMT_1, ICM20689_BIT_RESET);
    delay_ms(ICM20689_RESET_DELAY_MS);

    ERROR_TRY(spi_read_reg8_msk(imu_spi_dev, MPU_RA_WHO_AM_I, &chip_id));
    if (chip_id != 0x98)
    {
        DRV_DBG("ICM20689 unmatched chip id:0x%x\n", chip_id);
        return E_RROR;
    }

    spi_write_reg8(imu_spi_dev, MPU_RA_SIGNAL_PATH_RESET,
                   ICM20689_ACCEL_RST | ICM20689_TEMP_RST);              // Reset the device signal paths
    delay_ms(ICM20689_PATH_RESET_DELAY_MS);

    /* wakeup and set clock */
    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_PWR_MGMT_1, REG_VAL(BIT(0),
                                                                   BIT(6)))); /* CLKSEL[2:0] set to 001 to achieve full gyroscope performance. */
    systime_udelay(1000);

    ERROR_TRY(__write_checked_reg(imu_spi_dev, MPU_RA_CONFIG,0x06));                                           // Gyro 1K rate,
    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_GYRO_CONFIG,REG_VAL(BIT(3) | BIT(4), BIT(0) | BIT(1))));    // 2000dps, FCHOICE_B[0,0]
    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_ACCEL_CONFIG, REG_VAL(BIT(3) | BIT(4), 0)));                 // 16g
    ERROR_TRY(__modify_reg(imu_spi_dev, MPU_RA_ACCEL_CONFIG2,REG_VAL(0, 0x0F)));                           // Accel 1K rate, 218Hz BW
    ERROR_TRY(__write_checked_reg(imu_spi_dev, MPU_RA_INT_ENABLE,MPU_RF_DATA_RDY_EN));                            // enable interrupts
    ERROR_TRY(__write_checked_reg(imu_spi_dev, MPU_RA_USER_CTRL,ICM20689_I2C_IF_DIS));                         // Disable Primary I2C Interface

    return E_OK;
}

static err_t gyro_read_raw(int16_t gyr[3])
{
    OS_ENTER_CRITICAL();

    // Invalidate the D cache covering the area into which data has been read
    int16_t *raw = (int16_t *)(&icm20689_dma_data.buf[!icm20689_dma_data.idx * ICM20689_BUF_SIZE]);

    // big-endian to little-endian
    gyr[0] = int16_t_from_bytes((uint8_t *) &raw[4]);
    gyr[1] = int16_t_from_bytes((uint8_t *) &raw[5]);
    gyr[2] = int16_t_from_bytes((uint8_t *) &raw[6]);

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
    icm20689_rotate_to_ned(gyr);

    return E_OK;
}

static err_t gyro_config(gyro_dev_t gyro, const struct gyro_configure *cfg)
{
    ASSERT(cfg != NULL);

    ERROR_TRY(gyro_set_range(cfg->gyro_range_dps));

    ERROR_TRY(gyro_set_dlpf_filter(cfg->dlpf_freq_hz));

    gyro->config = *cfg;

    return E_OK;
}

static void exti_handler()
{
    //rechange the recv buf.
    icm20689_dma_data.idx = !icm20689_dma_data.idx;
    spi_read_multi_reg8_msk(imu_spi_dev, MPU_RA_ACCEL_XOUT_H, &icm20689_dma_data.buf[icm20689_dma_data.idx * ICM20689_BUF_SIZE], ICM20689_BUF_SIZE);
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
    int16_t *raw = (int16_t *)(&icm20689_dma_data.buf[!icm20689_dma_data.idx * ICM20689_BUF_SIZE]);

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
    icm20689_rotate_to_ned(acc);

    return E_OK;
}

static err_t accel_config(accel_dev_t accel, const struct accel_configure *cfg)
{
    ASSERT(cfg != NULL);

    ERROR_TRY(accel_set_range(cfg->acc_range_g));

    ERROR_TRY(accel_set_dlpf_filter(cfg->dlpf_freq_hz));

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

err_t drv_icm20689_init(const char *gyro_device_name, const char *accel_device_name)
{
    static struct spi_device spi_device;
    static io_tag cs = PE15;
    static io_tag exti = PH5;
    io_init(cs, CS_CONFIG);
    ERROR_TRY(spi_bus_attach_device(&spi_device,
                                    "icm20689",
                                    "spi6",
                                    (void *) &cs));

    /* config spi */
    struct spi_configuration cfg = {
            .data_width = 8,
            .mode = SPI_MODE_3 | SPI_MSB,
            .max_hz = ICM20689_MAX_SPI_CLK_HZ
    };
    ERROR_TRY(spi_configure_device(&spi_device, &cfg));

    imu_spi_dev = light_device_find("icm20689");
    ASSERT(imu_spi_dev != NULL);

    /* driver low-level init */
    ERROR_TRY(imu_init());

    /* register gyro hal device */
    ERROR_TRY(hal_gyro_register(&gyro_dev, gyro_device_name, DEVICE_FLAG_RDWR, &exti));

    /* register accel hal device */
    ERROR_TRY(hal_accel_register(&accel_dev, accel_device_name, DEVICE_FLAG_RDWR, NULL));

    return E_OK;
}