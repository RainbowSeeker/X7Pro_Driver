// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/16.
//

#ifndef X7PRO_DRIVER_MAGN_H
#define X7PRO_DRIVER_MAGN_H
#include "bus.h"
#include "accgyro.h"

typedef struct magn_s
{
    device_t dev;

    sample_mode_e sampleMode;
    uint8_t magRaw[9];

    float mag[3];
    //must bind func before init.
    bool (* init)(struct magn_s *);
    void (* updateCallback)(struct magn_s *);
}magn_t;


bool Magn_MspInit(magn_t *magn, detect_func_t detectFunc, const hw_config_t *hwConfig, const dr_config_t *drConfig);
bool Magn_Init(magn_t *magn);
void Magn_StartSample(magn_t *magn);
void Magn_StopSample(magn_t *magn);
#endif //X7PRO_DRIVER_MAGN_H
