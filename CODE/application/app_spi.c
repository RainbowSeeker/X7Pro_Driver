// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "app_spi.h"
#include "device/bus.h"
#include "adis16470.h"
#include "icm42688p.h"



void App_SPI_Main(void const * argument)
{
    ADIS_Init();
//    ICM42688_Init();
    while (1)
    {
//        println("ok");
//        osDelay(100);
        ADIS_Brust_Read();
//        ADIS_Read_ID();
        waitSpiDevice(&adis16470);
        for (int t = 0; t < 3; ++t)
        {
            println("gyro[%d]=%5.3f, accl[%d]=%5.3f, ", t, (float )accValue.gyro[t] * 1e-1, t, (float )accValue.accl[t] * 1.25e-3);
        }
        println("temp=%5.3f", (float )accValue.temp*1e-1);
    }

}