// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include <module_common.h>
#include "module/sensor/sensor_hub.h"

MCN_DECLARE(sensor_baro);

void App_Mcn_Main(void *argument)
{
    McnNode_t imu0 = mcn_subscribe(MCN_HUB(sensor_baro), NULL, NULL);

    while (1)
    {
        if (mcn_poll(imu0)) {
            if (MCN_HUB(sensor_baro)->echo)
            {
                MCN_HUB(sensor_baro)->echo(MCN_HUB(sensor_baro));
            }
        }
        os_delay(5);
    }
}