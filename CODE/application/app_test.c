// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include "app_test.h"
#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"
#include "barometer_ms5611.h"
#include "FRAM/fm25vx.h"
#include "magn_rm3100.h"

void App_Test_Main(void const * argument)
{
    ms5611.init(&ms5611);
    baroStartCalibration();
//    FM25Vx_Init();
//    uint8_t txbuf[20] = "HelloWorld";
//    uint8_t rxbuf[20] = {0};
//    uint8_t len = strlen((char *)txbuf);
    rm3100.init(&rm3100);
    Magn_StartSample(&rm3100);
    while (1)
    {
        for (int i = 0; i < 3; ++i)
        {
            println("mag[%d]=%.2f", i, rm3100.mag[i]);
        }
//        osDelay(Baro_Update(&ms5611, Sys_GetTickUs()) / 1000);
//        fm25vx.write(0x00C1, txbuf, len);
//        fm25vx.read(0x00C1, rxbuf, len);
//        println("%s", rxbuf);
    }
}