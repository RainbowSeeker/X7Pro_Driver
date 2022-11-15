// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include "app_test.h"
#include "sensor.h"
#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"



void App_Test_Main(void const * argument)
{
    baroSetGroundLevel();
    while (1)
    {
//        println("nowTick=%lu", osKernelSysTick());
//        osDelay(Baro_Update(&sensorDevice[MS5611_SPI-2].u.baro, Sys_GetTickUs()) / 1000);
    }
}