// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/8.
//

#ifndef X7PRO_DRIVER_RM3100_H
#define X7PRO_DRIVER_RM3100_H

#include "sensor/sensor_mag.h"

#define RM3100_MAX_SPI_CLK_HZ   1000000
#define RM3100_SCALE            (1.0f / 7.5f)

//  MagI2C Register Map. See Table 5-1 at page 28.
#define RM3100_ID       0x22

#define RM3100_POLL		0x00
#define RM3100_CMM		0x01        //Initiates Continuous Measurement Mode

#define RM3100_CCX_M	0x04        //Cycle Count Register – X Axis. See it at page 28.
#define RM3100_CCX_L	0x05        //Increasing the cycle count value increases measurement gain and resolution
#define RM3100_CCY_M	0x06        //Lowering the cycle count value reduces acquisition time, which increases maximum
#define RM3100_CCY_L	0x07        //achievable sample rate or, with a fixed sample rate, decreases power consumption
#define RM3100_CCZ_M	0x08
#define RM3100_CCZ_L	0x09

#define RM3100_TMRC		0x0B        //Sets Continuous Measurement Mode Data Rate

#define RM3100_MX		0x24        //X axis measurement. See it at page 34.
#define RM3100_MY		0x27
#define RM3100_MZ		0x2a

#define RM3100_BIST		0x33        //Built-In Self Test Register. See it at page 34.
#define RM3100_STATUS	0x34
#define RM3100_HSHAKE   0x35
#define RM3100_REVID	0x36

err_t drv_rm3100_init(const char* mag_device_name);
#endif //X7PRO_DRIVER_RM3100_H
