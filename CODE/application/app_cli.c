// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"
#include "accgyro_icm20689.h"
#include "barometer_ms5611.h"
#include "fram/fm25vx.h"
#include "magn_rm3100.h"
#include "driver/uart.h"
#include "cli/cli.h"
#include "mcn/mcn.h"
#include "sensor_hub.h"

MCN_DECLARE(sensor_imu0);

void App_Cli_Main(void const * argument)
{

    while (1)
    {
        CLi_Handle();
        osDelay(10);
    }
}