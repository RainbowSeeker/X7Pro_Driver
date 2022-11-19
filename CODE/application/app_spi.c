// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "app_spi.h"
#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"
#include "magn_rm3100.h"
#include "FRAM/fm25vx.h"
#include "barometer_ms5611.h"
#include "accgyro_icm20689.h"

void Print_Gyro()
{
    for (int i = 0; i < 3; ++i)
    {
        println("gyro[%d]=%.2f, acc[%d]=%.2f, ", i, icm20689.gyro[i], i, icm426xx.acc[i]);
    }
    println("AvgFreq=%d", icm20689.dev.extiStat.capAvgFreq);
}

void App_SPI_Main(void const * argument)
{
    Gyro_Init(&adis16470);
    Gyro_Init(&icm426xx);
    Gyro_Init(&icm20689);

    while (1)
    {
        Gyro_Update(&adis16470);
        Gyro_Update(&icm426xx);
        Gyro_Update(&icm20689);
        Print_Gyro();
        osDelay(5);
    }

}