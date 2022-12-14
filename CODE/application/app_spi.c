// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include <common.h>
#include "module_common.h"
#include "model/ins/base_ins/lib/INS.h"
#include "sensor/accgyro_adis16470.h"
#include "spi/spi.h"
#include "barometer/barometer.h"
#include "sensor/sensor_hub.h"


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

    int IMU_ID = mlog_get_bus_id("IMU");
    IMU_Bus imu;
    uint32_t tick = os_tick_get();
    while (1)
    {
        sensor_collect();

        imu.timestamp = os_tick_get();
        memcpy(log_data, &imu, sizeof(IMU_Bus));
//        mlog_push_msg((uint8_t*)log_data, IMU_ID, 200);

        os_delay_until(&tick, 5);
//        osDelay(Baro_Update(&ms5611, Sys_GetTickUs()) / 1000);
//        fm25vx.write(0x00C1, txbuf, len);
//        fm25vx.read(0x00C1, rxbuf, len);
//        println("%s", rxbuf);
    }

}