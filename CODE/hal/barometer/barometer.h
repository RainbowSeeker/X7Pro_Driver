// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#ifndef X7PRO_DRIVER_BAROMETER_H
#define X7PRO_DRIVER_BAROMETER_H

#include <common.h>
/* baro read pos */
#define BARO_RD_REPORT 1

/* baro command */
#define BARO_CMD_CHECK_READY 0x20

typedef struct {
    uint32_t timestamp_ms;
    float temperature_deg;
    float pressure_Pa;
    float altitude_m;
} baro_report_t;

struct baro_configure {
    uint16_t osr; /* oversampling ratio */
};

struct baro_device {
    struct light_device parent;
    const struct baro_ops* ops;
};
typedef struct baro_device* baro_dev_t;

/* baro driver opeations */
struct baro_ops {
    err_t (*baro_control)(baro_dev_t baro, int cmd, void* arg);
    size_t (*baro_read)(baro_dev_t baro, baro_report_t* report);
};

err_t hal_baro_register(baro_dev_t baro, const char* name, uint32_t flag, void* data);


#endif //X7PRO_DRIVER_BAROMETER_H
