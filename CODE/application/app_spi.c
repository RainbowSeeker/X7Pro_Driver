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

void Print_Gyro()
{
    for (int i = 0; i < 3; ++i)
    {
        println("gyro[%d]=%.2f, acc[%d]=%.2f, ", i, icm426xx.gyro[i], i, icm426xx.acc[i]);
    }
    println("temp=%.1f", adis16470.temp);
}

void App_SPI_Main(void const * argument)
{
    assert(adis16470.init(&adis16470));
    assert(icm426xx.init(&icm426xx));
    Gyro_StartSample(&adis16470);
    Gyro_StartSample(&icm426xx);



    while (1)
    {
        Gyro_Update(&adis16470);
        Gyro_Update(&icm426xx);
//        Print_Gyro();
//        println("magx=%.2f, magy=%.2f, magz=%.2f, ", rm3100Value.mag[X], rm3100Value.mag[Y], rm3100Value.mag[Z]);
        osDelay(5);
    }

}