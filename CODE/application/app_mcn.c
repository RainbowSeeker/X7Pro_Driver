// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include <module_common.h>
#include "module/sensor/sensor_hub.h"

MCN_DECLARE(sensor_imu0_0);
MCN_DECLARE(sensor_imu0);

MCN_DECLARE(sensor_imu1_0);
MCN_DECLARE(sensor_imu1);

MCN_DECLARE(sensor_imu2_0);
MCN_DECLARE(sensor_imu2);

MCN_DECLARE(sensor_mag0_0);
MCN_DECLARE(sensor_mag0);

MCN_DECLARE(sensor_mag1_0);
MCN_DECLARE(sensor_mag1);

MCN_DECLARE(sensor_baro);

MCN_DECLARE(sensor_airspeed);

MCN_DECLARE(sensor_gps);

MCN_DECLARE(sensor_optflow);

MCN_DECLARE(sensor_rangefinder);

void App_Mcn_Main(void *argument)
{
    McnNode_t imu0 = mcn_subscribe(MCN_HUB(sensor_imu0_0), NULL, NULL);
    McnNode_t imu1 = mcn_subscribe(MCN_HUB(sensor_imu1_0), NULL, NULL);
    McnNode_t imu2 = mcn_subscribe(MCN_HUB(sensor_imu2_0), NULL, NULL);
    McnNode_t mag0 = mcn_subscribe(MCN_HUB(sensor_mag0), NULL, NULL);
    McnNode_t baro = mcn_subscribe(MCN_HUB(sensor_baro), NULL, NULL);

    while (1)
    {
        if (mcn_poll(imu0)) {
            mcn_node_clear(imu0);
            if (MCN_HUB(sensor_imu0_0)->echo)
            {
                MCN_HUB(sensor_imu0_0)->echo(MCN_HUB(sensor_imu0_0));
            }
        }

        if (mcn_poll(imu1)) {
            mcn_node_clear(imu1);
            if (MCN_HUB(sensor_imu1_0)->echo)
            {
                MCN_HUB(sensor_imu1_0)->echo(MCN_HUB(sensor_imu1_0));
            }
        }

        if (mcn_poll(imu2)) {
            mcn_node_clear(imu2);
            if (MCN_HUB(sensor_imu2_0)->echo)
            {
                MCN_HUB(sensor_imu2_0)->echo(MCN_HUB(sensor_imu2_0));
            }
        }

        if (mcn_poll(mag0)) {
            mcn_node_clear(mag0);
            if (MCN_HUB(sensor_mag0_0)->echo)
            {
                MCN_HUB(sensor_mag0_0)->echo(MCN_HUB(sensor_mag0_0));
            }
        }

        if (mcn_poll(baro)) {
            mcn_node_clear(baro);
            if (MCN_HUB(sensor_baro)->echo)
            {
                MCN_HUB(sensor_baro)->echo(MCN_HUB(sensor_baro));
            }
        }

        os_delay(500);
    }
}