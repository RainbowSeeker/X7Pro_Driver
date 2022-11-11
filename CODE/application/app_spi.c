// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "app_spi.h"
#include "device/bus.h"
#include "accgyro_adis16470.h"
#include "accgyro_icm42688p.h"



void App_SPI_Main(void const * argument)
{

    while (1)
    {
        STATIC_DMA_DATA_AUTO uint8_t txBuf[24] = {0};
        STATIC_DMA_DATA_AUTO uint8_t rxBuf[24] = {0};
        txBuf[0] = BURST_READ >> 8;
        txBuf[1] = BURST_READ & 0xff;

        println("App_SPI_Main Running...");
        osDelay(100);
    }

}