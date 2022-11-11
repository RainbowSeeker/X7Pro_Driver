// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#ifndef X7PRO_DRIVER_HW_CONFIG_H
#define X7PRO_DRIVER_HW_CONFIG_H
#include "bus_spi.h"
#include "gyro.h"
#include "sensor.h"

#define SPI_NUM         (DEV_SPICOUNT - 1)
#define GYRO_NUM        (MPU_COUNT - 1)


extern const spi_hw_t spiHardware[SPI_NUM];
extern const gyro_config_t gyroConfig[GYRO_NUM];
#endif //X7PRO_DRIVER_HW_CONFIG_H
