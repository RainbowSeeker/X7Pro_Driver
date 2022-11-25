// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"
#include "magn_rm3100.h"
#include "fram/fm25vx.h"
#include "barometer_ms5611.h"
#include "accgyro_icm20689.h"
#include "mcn/mcn.h"
#include "sensor_hub.h"

void Print_Gyro()
{
    for (int i = 0; i < 3; ++i)
    {
        println("gyro[%d]=%.2f, acc[%d]=%.2f, ", i, icm20689.gyro[i], i, icm20689.acc[i]);
    }
    println("AvgFreq=%d", icm20689.dev.extiStat.capAvgFreq);
}

MCN_DECLARE(sensor_imu0);

void App_SPI_Main(void const * argument)
{
    //    Magn_Init(&rm3100);
//    Baro_Init(&ms5611);
//    baroStartCalibration();
//
//    Fram_Init(&fm25vx);
//    uint8_t txbuf[25] = "fm25vx read & write test";
//    uint8_t rxbuf[25] = {0};
//    uint8_t len = strlen((char *)txbuf);

//    uint8_t str[] = "hello world123\r\n";
    Gyro_Init(&adis16470);
    Gyro_Init(&icm42688);
    Gyro_Init(&icm20689);
    advertise_sensor_imu(0);
    while (1)
    {
        Gyro_Update(&adis16470);
        Gyro_Update(&icm42688);
        Gyro_Update(&icm20689);

        imu_data_t imu_data;
        imu_data.timestamp_ms = HAL_GetTick();
        imu_data.acc_B_mDs2[0] = adis16470.acc[0];
        imu_data.acc_B_mDs2[1] = adis16470.acc[1];
        imu_data.acc_B_mDs2[2] = adis16470.acc[2];
        imu_data.gyr_B_radDs[0] = adis16470.gyro[0];
        imu_data.gyr_B_radDs[1] = adis16470.gyro[1];
        imu_data.gyr_B_radDs[2] = adis16470.gyro[2];
        mcn_publish(MCN_HUB(sensor_imu0), &imu_data);
//        Print_Gyro();
        osDelay(5);
        //        Magn_Update(&rm3100);
//        for (int i = 0; i < 3; ++i)
//        {
//            println("mag[%d]=%.2f", i, rm3100.mag[i]);
//        }
//
//        osDelay(Baro_Update(&ms5611, Sys_GetTickUs()) / 1000);
//
//        fm25vx.write(0x00C1, txbuf, len);
//        fm25vx.read(0x00C1, rxbuf, len);
//        println("%s", rxbuf);
    }

}