// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "app_spi.h"
#include "device/bus.h"
#include "adis16470.h"
#include "swap.h"


void App_SPI_Main(void)
{
    ADIS_Init();

    while (1)
    {
        ADIS_Brust_Read();

        waitSpiDevice(&adis16470);

        for (int t = 0; t < 3; ++t)
        {
            println("gyro[%d]=%5.3f, accl[%d]=%5.3f, ", t, (float )accValue.gyro[t] * 1e-1, t, (float )accValue.accl[t] * 1.25e-3);
        }
        println("temp=%5.3f", (float )accValue.temp*1e-1);
        osDelay(100);
    }

}