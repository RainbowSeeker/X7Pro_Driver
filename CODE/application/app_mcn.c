// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include "mcn/mcn.h"
#include "sensor_hub.h"
#include "cli/cli.h"

MCN_DECLARE(sensor_imu0);


void App_Mcn_Main(void const *argument)
{
    mcn_node_t *imu_sub_node_t = mcn_subscribe(MCN_HUB(sensor_imu0), NULL, NULL);
    while (1)
    {
        /* get sensor data */
        imu_data_t imu_report;
        if (mcn_poll(imu_sub_node_t))
        {
            mcn_copy(MCN_HUB(sensor_imu0), imu_sub_node_t, &imu_report);
//            MCN_HUB(sensor_imu0)->echo(MCN_HUB(sensor_imu0));
        }

        osDelay(5);
    }
}