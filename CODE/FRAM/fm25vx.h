// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/17.
//

#ifndef X7PRO_DRIVER_FM25VX_H
#define X7PRO_DRIVER_FM25VX_H
#include "bus.h"

typedef struct
{
    device_t dev;
    uint8_t *pTxData;
    uint8_t *pRxData;

    void (* write)(uint16_t addr, uint8_t *buf, int len);
    void (* read)(uint16_t addr, uint8_t *buf, int len);
}fram_t;

extern fram_t fm25vx;
bool FM25Vx_Init();
#endif //X7PRO_DRIVER_FM25VX_H
