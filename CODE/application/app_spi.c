// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "module/sensor/accgyro_adis16470.h"
#include "module/sensor/accgyro_icm42688p.h"
#include "module/sensor/magn_rm3100.h"
#include "fram/fm25vx.h"
#include "module/sensor/barometer_ms5611.h"
#include "module/sensor/accgyro_icm20689.h"
#include "module/sensor/sensor_hub.h"
#include "model/ins/base_ins/lib/INS.h"

void Print_Gyro()
{
    for (int i = 0; i < 3; ++i)
    {
        printf("gyro[%d]=%.2f, acc[%d]=%.2f, \n", i, icm20689.gyro[i], i, icm20689.acc[i]);
    }
    printf("AvgFreq=%d\n", icm20689.dev.extiStat.capAvgFreq);
}

/* define log data */
static mlog_elem_t IMU_Elems[] = {
        MLOG_ELEMENT(timestamp, MLOG_UINT32),
        MLOG_ELEMENT(gyr_x, MLOG_FLOAT),
        MLOG_ELEMENT(gyr_y, MLOG_FLOAT),
        MLOG_ELEMENT(gyr_z, MLOG_FLOAT),
        MLOG_ELEMENT(acc_x, MLOG_FLOAT),
        MLOG_ELEMENT(acc_y, MLOG_FLOAT),
        MLOG_ELEMENT(acc_z, MLOG_FLOAT),
};
MLOG_BUS_DEFINE(IMU, IMU_Elems);

uint8_t log_data[200] = {0};

void App_SPI_Main(void *argument)
{
//    Fram_Init(&fm25vx);
//    uint8_t txbuf[25] = "fm25vx read & write test";
//    uint8_t rxbuf[25] = {0};
//    uint8_t len = strlen((char *)txbuf);
//    uint8_t str[] = "hello world123\r\n";
    Gyro_Init(&adis16470);
    Gyro_Init(&icm42688);
    Gyro_Init(&icm20689);

    Magn_Init(&rm3100);

    Baro_Init(&ms5611);
    baroStartCalibration();

    int IMU_ID = mlog_get_bus_id("IMU");
    IMU_Bus imu;
    uint32_t tick = os_tick_get();
    while (1)
    {
//        sensor_collect();
        Gyro_Update(&adis16470);


        imu.timestamp = os_tick_get();
        imu.gyr_x = adis16470.gyro[0];
        imu.gyr_y = adis16470.gyro[1];
        imu.gyr_z = adis16470.gyro[2];
        imu.acc_x = adis16470.acc[0];
        imu.acc_y = adis16470.acc[1];
        imu.acc_z = adis16470.acc[2];
        memcpy(log_data, &imu, sizeof(IMU_Bus));
        mlog_push_msg((uint8_t*)log_data, IMU_ID, 200);

        os_delay_until(&tick, 5);
//        osDelay(Baro_Update(&ms5611, Sys_GetTickUs()) / 1000);
//        fm25vx.write(0x00C1, txbuf, len);
//        fm25vx.read(0x00C1, rxbuf, len);
//        println("%s", rxbuf);
    }

}