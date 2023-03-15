// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/7.
//

#include "adis16470.h"
#include "hal/spi/spi.h"
#include "imu/accel.h"
#include "imu/gyro.h"
#include "driver/io.h"
#include "sensor/sensor_imu.h"
#include "drivers/drv_exti.h"

static device_t spi_dev;
static float gyro_range_scale;
static float accel_range_scale;

#define ADIS_BUF_SIZE   (24)
static DMA_DATA uint8_t send_buf[ADIS_BUF_SIZE];
static DMA_DATA uint8_t recv_buf[ADIS_BUF_SIZE * 2];
static bool recv_idx = 0;

static void drdy_collect(uint32_t user_data)
{
    /* transfer message */
    if (spi_transfer((struct spi_device *)spi_dev, send_buf, &recv_buf[recv_idx * ADIS_BUF_SIZE], ADIS_BUF_SIZE))
    {
        //rechange the recv buf.
        recv_idx = !recv_idx;
    }
}

/* Re-implement this function to define customized rotation */
__WEAK void adis16470_rotate_to_ned(float *val)
{
    /* do nothing */
}

static err_t accel_read_raw(int16_t acc[3])
{
    OS_ENTER_CRITICAL();
    int16_t *raw = (int16_t *)(&recv_buf[!recv_idx * ADIS_BUF_SIZE + 4]);

    // big-endian to little-endian
    acc[0] = int16_t_from_bytes((uint8_t *) &raw[3]);
    acc[1] = int16_t_from_bytes((uint8_t *) &raw[4]);
    acc[2] = int16_t_from_bytes((uint8_t *) &raw[5]);

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
    adis16470_rotate_to_ned(acc);

    return E_OK;
}

static err_t accel_config(accel_dev_t accel, const struct accel_configure *cfg)
{
    ASSERT(cfg != NULL);

    accel_range_scale = ONE_G * 1.25e-3;
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


static err_t gyro_read_raw(int16_t gyr[3])
{
    OS_ENTER_CRITICAL();

    // Invalidate the D cache covering the area into which data has been read
    int16_t *raw = (int16_t *)(&recv_buf[!recv_idx * ADIS_BUF_SIZE + 4]);

    // big-endian to little-endian
    gyr[0] = int16_t_from_bytes((uint8_t *) &raw[0]);
    gyr[1] = int16_t_from_bytes((uint8_t *) &raw[1]);
    gyr[2] = int16_t_from_bytes((uint8_t *) &raw[2]);

    OS_EXIT_CRITICAL();

#ifdef SENSOR_SOFT_DRDY
    drdy_collect(0);
#endif

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
    adis16470_rotate_to_ned(gyr);

    return E_OK;
}

static err_t gyro_config(gyro_dev_t gyro, const struct gyro_configure *cfg)
{
    ASSERT(cfg != NULL);

    memset(send_buf, 0, sizeof(send_buf));
    memset(recv_buf, 0, sizeof(recv_buf));
    send_buf[0] = BURST_READ;
    gyro_range_scale = (1e-1 * PI / 180.0f);
    gyro->config = *cfg;
#ifdef SENSOR_SOFT_DRDY
    drdy_collect(0);
#endif

    return E_OK;
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
#ifndef SENSOR_SOFT_DRDY
        drdy_collect
#endif
};

static err_t imu_init(void)
{
    uint16_t dev_id;

    /* init spi bus */
    ERROR_TRY(device_open(spi_dev, DEVICE_OFLAG_RDWR));

    static uint8_t tx_data[2] = {ADI_PROD_ID, 0};
    static uint8_t rx_data[2];
    for (int i = 0; i < 20; ++i)
    {
        delay_ms(20);

        spi_transfer((struct spi_device *)spi_dev, tx_data, rx_data, 2);
        dev_id = rx_data[0] << 8 | rx_data[1];
        if (dev_id == ADI_ID)
        {
            break;
        }
    }
    if (dev_id != ADI_ID)
    {
        printf("adis16470 unmatch chip id:%x\n", dev_id);
    }
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

err_t drv_adis16470_init(const char* gyro_dev_name, const char* accel_dev_name)
{
    /* Initialize gyroscope */
    static struct spi_device spi_device;
    static io_tag cs = PF10;
    static io_tag exti = PE7;
    io_init(cs, CS_CONFIG);
    ERROR_TRY(spi_bus_attach_device(&spi_device,
                                    "adis16470",
                                    "spi1",
                                    (void *) &cs));

    /* config spi */
    struct spi_configuration cfg = {
            .data_width = 8,
            .mode = SPI_MODE_3 | SPI_MSB,
            .max_hz = ADI_MAX_SPI_CLK_HZ
    };
    ERROR_TRY(spi_configure_device(&spi_device, &cfg));

    spi_dev = device_find("adis16470");
    ASSERT(spi_dev != NULL);

    /* device low-level init */
    ERROR_TRY(imu_init());

    /* register gyro hal device */
    ERROR_TRY(hal_gyro_register(&gyro_dev, gyro_dev_name, DEVICE_FLAG_RDWR, &exti));

    /* register accel hal device */
    ERROR_TRY(hal_accel_register(&accel_dev, accel_dev_name, DEVICE_FLAG_RDWR, NULL));

    return E_OK;
}
