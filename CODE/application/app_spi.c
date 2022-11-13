// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "app_spi.h"
#include "mpu.h"
#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"

void App_SPI_Main(void const * argument)
{
    MPU_Init();

    while (1)
    {
        MPU_Update(ICM42688P_SPI);
        MPU_Update(ADIS16470_SPI);

        MPU_Wait(ICM42688P_SPI);
        MPU_Wait(ADIS16470_SPI);

        for (int i = 0; i < 3; ++i)
        {
            icmValue.gyro[i] = __builtin_bswap16(icmValue.gyro[i]);
            icmValue.acc[i] = __builtin_bswap16(icmValue.acc[i]);
            adiValue.gyro[i] = __builtin_bswap16(adiValue.gyro[i]);
            adiValue.acc[i] = __builtin_bswap16(adiValue.acc[i]);
        }

        for (int i = 0; i < 3; ++i)
        {
            println("gyro[%d]=%3.2f, acc[%d]=%3.2f, ", i, (float )adiValue.gyro[i]*GYRO_SCALE_2000DPS, i, (float )adiValue.acc[i]*GYRO_SCALE_2000DPS);
        }
        adiValue.temp = __builtin_bswap16(adiValue.temp);
        println("temp=%3.1f ", (float )adiValue.temp/10);
    }

}