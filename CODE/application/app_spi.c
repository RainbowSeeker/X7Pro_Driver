// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "app_spi.h"
#include "sensor.h"
#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"

void Print_Gyro()
{
    for (int i = 0; i < 3; ++i)
    {
        println("gyro[%d]=%3.2f, acc[%d]=%3.2f, ", i, (float )adiValue.gyro[i]*GYRO_SCALE_2000DPS, i, (float )adiValue.acc[i]*GYRO_SCALE_2000DPS);
    }
    println("AvgFreq=%lu", sensorDevice[ADIS16470_SPI - 1].u.gyro.capAvgFreq);
}

void App_SPI_Main(void const * argument)
{
    Sensor_Init();

    while (1)
    {
        Sensor_Update(ICM42688P_SPI);
        Sensor_Update(ADIS16470_SPI);
        Print_Gyro();
        osDelay(5);
//        Sensor_Update(MS5611_SPI);
//        osDelay(25);
    }

}