// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#ifndef X7PRO_DRIVER_GYRO_H
#define X7PRO_DRIVER_GYRO_H

#include <common.h>

#define GYRO_RANGE_250DPS  250
#define GYRO_RANGE_500DPS  500
#define GYRO_RANGE_1000DPS 1000
#define GYRO_RANGE_2000DPS 2000

/* gyro device bus type */
#define GYRO_SPI_BUS_TYPE 1
#define GYRO_I2C_BUS_TYPE 2

/* default config for accel sensor */
#define GYRO_CONFIG_DEFAULT                              \
    {                                                    \
        1000,                   /* 1K sample rate */     \
            98,                 /* 256Hz internal lpf */ \
            GYRO_RANGE_2000DPS, /* +-2000 deg/s */       \
    }

struct gyro_configure {
    uint32_t sample_rate_hz;
    uint16_t dlpf_freq_hz;
    uint32_t gyro_range_dps;
};

struct gyro_device {
    struct device parent;
    const struct gyro_ops* ops;
    struct gyro_configure config;
    uint8_t bus_type;
};
typedef struct gyro_device* gyro_dev_t;

/* accel driver opeations */
struct gyro_ops {
    err_t (*gyro_config)(gyro_dev_t gyro, const struct gyro_configure* cfg);
    err_t (*gyro_control)(gyro_dev_t gyro, int cmd, void* arg);
    size_t (*gyro_read)(gyro_dev_t gyro, off_t pos, void* data, size_t size);
    void (* exti_cb)(uint32_t);
};

err_t hal_gyro_register(gyro_dev_t gyro, const char* name, uint32_t flag, void* data);

#endif //X7PRO_DRIVER_GYRO_H
