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
#include "cli/log.h"

MCN_DECLARE(sensor_imu0);

#define FIFO_SIZE   30
volatile uint8_t headPos = 0;
volatile uint8_t tailPos = 0;
DMA_DATA uint8_t bigdata[FIFO_SIZE][200];

uint32_t count = 0;
void App_Mcn_Main(void const *argument)
{
    mcn_node_t *imu_sub_node_t = mcn_subscribe(MCN_HUB(sensor_imu0), NULL, NULL);
    uint32_t pWakeTime = osKernelSysTick();

    memset(bigdata[0], 0, 200 * FIFO_SIZE);
    while (1)
    {
        /* get sensor data */
        imu_data_t imu_report;
        if (mcn_poll(imu_sub_node_t))
        {
            mcn_copy(MCN_HUB(sensor_imu0), imu_sub_node_t, &imu_report);
            OS_ENTER_CRITICAL;
            {
                if ((headPos + 1) % FIFO_SIZE != tailPos)
                {
                    sprintf((char *)bigdata[headPos], "%lu\t%f\t%f\t%f\t%f\t%f\t%f\r\n", HAL_GetTick(),
                            imu_report.gyr_B_radDs[0],
                            imu_report.gyr_B_radDs[1],
                            imu_report.gyr_B_radDs[2],
                            imu_report.acc_B_mDs2[0],
                            imu_report.acc_B_mDs2[1],
                            imu_report.acc_B_mDs2[2]);
                    headPos = (headPos + 1) % FIFO_SIZE;
                }
                else
                {
                    LOG_ERROR("FIFO overflow");
                }

                if (count++ % 100 == 0)
                {
                    println("distance=%d", (headPos - tailPos + FIFO_SIZE) % FIFO_SIZE);
                }
            }
            OS_EXIT_CRITICAL;
        }
        osDelayUntil(&pWakeTime, 5);
    }
}