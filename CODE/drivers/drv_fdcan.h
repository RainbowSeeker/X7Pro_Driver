// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/17.
//

#ifndef X7PRO_DRIVER_DRV_FDCAN_H
#define X7PRO_DRIVER_DRV_FDCAN_H
#include "hal/can/can.h"

struct stm32_fdcan
{
    struct device dev;
    FDCAN_HandleTypeDef fdcan;
    FDCAN_FilterTypeDef filter;
    FDCAN_TxHeaderTypeDef tx_config;
    FDCAN_RxHeaderTypeDef rx_config;
    volatile uint8_t fifo0;
    volatile uint8_t fifo1;
};


extern FDCAN_HandleTypeDef hfdcan1;
#endif //X7PRO_DRIVER_DRV_FDCAN_H
