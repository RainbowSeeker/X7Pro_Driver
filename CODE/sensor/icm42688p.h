// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef X7PRO_DRIVER_ICM42688P_H
#define X7PRO_DRIVER_ICM42688P_H
#include "bus_spi.h"

#define ICM_CS_Port             GPIOA
#define ICM_CS_Pin              GPIO_PIN_15

extern spi_device_t icm42688p;

void ICM42688_Init(void);
#endif //X7PRO_DRIVER_ICM42688P_H
