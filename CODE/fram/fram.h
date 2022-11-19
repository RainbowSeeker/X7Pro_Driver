// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/18.
//

#ifndef X7PRO_DRIVER_FRAM_H
#define X7PRO_DRIVER_FRAM_H

#include "bus.h"

typedef struct fram_s
{
    device_t dev;
    uint8_t *pTxData;
    uint8_t *pRxData;

    bool (* init)(struct fram_s *);
    void (* write)(uint16_t addr, uint8_t *buf, int len);
    void (* read)(uint16_t addr, uint8_t *buf, int len);
}fram_t;

bool Fram_Init(fram_t *fram);
#endif //X7PRO_DRIVER_FRAM_H
