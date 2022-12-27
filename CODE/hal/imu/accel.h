// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#ifndef X7PRO_DRIVER_ACCEL_H
#define X7PRO_DRIVER_ACCEL_H

#include <common.h>

#define ACCEL_RANGE_2G  2
#define ACCEL_RANGE_4G  4
#define ACCEL_RANGE_8G  8
#define ACCEL_RANGE_16G 16

/* accel device bus type */
#define ACCEL_SPI_BUS_TYPE 1
#define ACCEL_I2C_BUS_TYPE 2

/* default config for accel sensor */
#define ACCEL_CONFIG_DEFAULT                                    \
    {                                                           \
        1000,                /* 1K sample rate */               \
            98,              /* 260Hz internal lpf for accel */ \
            ACCEL_RANGE_16G, /* +-8g */                         \
    }

struct accel_configure {
    uint32_t sample_rate_hz;
    uint16_t dlpf_freq_hz;
    uint32_t acc_range_g;
};

struct accel_device {
    struct device parent;
    const struct accel_ops* ops;
    struct accel_configure config;
    uint8_t bus_type;
};
typedef struct accel_device* accel_dev_t;

/* accel driver opeations */
struct accel_ops {
    err_t (*accel_config)(accel_dev_t accel, const struct accel_configure* cfg);
    err_t (*accel_control)(accel_dev_t accel, int cmd, void* arg);
    size_t (*accel_read)(accel_dev_t accel, off_t pos, void* data, size_t size);
};

err_t hal_accel_register(accel_dev_t accel, const char* name, uint32_t flag, void* data);



#endif //X7PRO_DRIVER_ACCEL_H
