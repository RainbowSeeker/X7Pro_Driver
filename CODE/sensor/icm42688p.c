// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "icm42688p.h"

spi_device_t icm42688p = {
        .name = "ICM42688P",
        .pwrPin = {.port = SENSORS_ON_Port, .pin = SENSORS_ON_Pin},
        .csPin = {.port = ICM_CS_Port, .pin = ICM_CS_Pin},
        .useDMA = 1,
        .initialize = SPI_Register_Bus,
        .read = SPI_Transfer,
        .write = SPI_Transfer
};

void ICM42688_Init(void)
{
    if (icm42688p.initialize(&icm42688p, DEV_SPI4) == S_OK)
    {
        println("icm42688p initialize succeed!");
    }
    else
    {
        println("icm42688p initialize failed!");
    }
}