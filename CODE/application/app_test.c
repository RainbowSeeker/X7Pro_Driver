// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"
#include "accgyro_icm20689.h"
#include "barometer_ms5611.h"
#include "fram/fm25vx.h"
#include "magn_rm3100.h"
#include "driver/uart.h"
#include "cli/cli.h"

void App_Test_Main(void const * argument)
{
//    Magn_Init(&rm3100);
//    Baro_Init(&ms5611);
//    baroStartCalibration();
//
//    Fram_Init(&fm25vx);
//    uint8_t txbuf[25] = "fm25vx read & write test";
//    uint8_t rxbuf[25] = {0};
//    uint8_t len = strlen((char *)txbuf);

    uint8_t str[] = "hello world123\r\n";
    while (1)
    {
        CLi_Handle();
        osDelay(10);
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