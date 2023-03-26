// Copyright (c) 2023 By RainbowSeeker.

//
// Created by 19114 on 2023/2/25.
//

#include "drv_rc.h"
#include "hal/rc/rc.h"
#include "hal/rc/ppm.h"

#define RC_CHANNEL_NUM    16

/* default config for rc device */
#define RC_CONFIG_DEFAULT                      \
    {                                          \
        RC_PROTOCOL_SBUS, /* sbus */           \
            6,            /* 6 channel */      \
            0.05f,        /* sample time */    \
            1000,         /* minimal 1000us */ \
            2000,         /* maximal 2000us */ \
    }

typedef struct {
    uint32_t timestamp_ms;
    uint16_t rc_chan_val[RC_CHANNEL_NUM];
} rc_data_t;

/* rc configuration */
typedef struct {
    uint16_t protocol; // 1:sbus 2:ppm
    float sample_time; // rc sample time in seconds (-1 for inherits)
} IO_RCConfig;

static rc_data_t rc_data;
static uint8_t rc_updated;
static IO_RCConfig rc_config = { .protocol = 1, .sample_time = 0.05 };

static err_t rc_configure(rc_dev_t rc, struct rc_configure* cfg)
{
    IO_RCConfig new_config = { .protocol = cfg->protocol, .sample_time = cfg->sample_time };

    if (rc_config.protocol == new_config.protocol
        && rc_config.sample_time == new_config.sample_time) {
        /* it's same configuration already */
        return E_OK;
    }


//    if (io_rc_config(new_config) == E_OK)
//    {
//        /* update default configuration */
//        rc_config = new_config;
//        /* update rc device configuration */
//        rc->config = *cfg;
//        return E_OK;
//    } else {
//        return ERROR;
//    }
}

static err_t rc_control(rc_dev_t rc, int cmd, void* arg)
{
    switch (cmd) {
        case RC_CMD_CHECK_UPDATE: {
            *(uint8_t*)arg = rc_updated;
        } break;

        default:
            break;
    }

    return E_OK;
}

static uint16_t rc_read(rc_dev_t rc, uint16_t chan_mask, uint16_t* chan_val)
{
    uint16_t* index = chan_val;
    uint16_t rb = 0;

    if (!rc_updated)
        return 0;

    for (uint8_t i = 0; i < RC_CHANNEL_NUM; i++) {
        if (chan_mask & (1 << i)) {
            *(index++) = rc_data.rc_chan_val[i];
            rb += 2;
        }
    }

    rc_updated = 0;

    return rb;
}

const static struct rc_ops _rc_ops = {
        .rc_configure = rc_configure,
        .rc_control = rc_control,
        .rc_read = rc_read,
};

static struct rc_device rc_dev = {
        .config = RC_CONFIG_DEFAULT,
        .ops = &_rc_ops,
};

err_t drv_rc_init(void)
{
    SELF_CHECK(hal_rc_register(&rc_dev, "rc", DEVICE_FLAG_RDWR, NULL));

    return E_OK;
}