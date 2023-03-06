// Copyright (c) 2023 By RainbowSeeker.

//
// Created by 19114 on 2023/2/28.
//

#ifndef X7PRO_DRIVER_SBUS_H
#define X7PRO_DRIVER_SBUS_H

#include <common.h>


void sbus_init();
uint8_t sbus_putc(uint8_t c);
bool sbus_input(uint16_t *values, uint16_t *num_values, bool *sbus_failsafe,
                bool *sbus_frame_drop, uint16_t max_channels);
#endif //X7PRO_DRIVER_SBUS_H
