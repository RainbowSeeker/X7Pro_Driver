// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#ifndef X7PRO_DRIVER_MAG_H
#define X7PRO_DRIVER_MAG_H

#include <common.h>

#define LSM303D_MAG_DEFAULT_RANGE_GA 2
#define LSM303D_MAG_DEFAULT_RATE     100

#define LSM303D_ONE_G 9.80665f

#define MAG_RANGE_2GA  2
#define MAG_RANGE_4GA  4
#define MAG_RANGE_8GA  6
#define MAG_RANGE_12GA 12
#define MAG_RANGE_16GA 16

/* mag device bus type */
#define MAG_SPI_BUS_TYPE 1
#define MAG_I2C_BUS_TYPE 2

/* default config for mag sensor */
#define MAG_CONFIG_DEFAULT                                  \
    {                                                       \
        100,               /* 100hz sample rate */          \
            50,            /* 260Hz internal lpf for mag */ \
            MAG_RANGE_8GA, /* +-8guess */                   \
    }

struct mag_configure {
    uint32_t sample_rate_hz;
    uint16_t dlpf_freq_hz;
    uint32_t mag_range_ga;
};

struct mag_device {
    struct device parent;
    const struct mag_ops* ops;
    struct mag_configure config;
    uint8_t bus_type;
};
typedef struct mag_device* mag_dev_t;

/* mag driver opeations */
struct mag_ops {
    err_t (*mag_config)(mag_dev_t mag, const struct mag_configure* cfg);
    err_t (*mag_control)(mag_dev_t mag, int cmd, void* arg);
    size_t (*mag_read)(mag_dev_t mag, off_t pos, void* data, size_t size);
    void (* exti_cb)(uint32_t);
};

err_t hal_mag_register(mag_dev_t mag, const char* name, uint32_t flag, void* data);


#endif //X7PRO_DRIVER_MAG_H
