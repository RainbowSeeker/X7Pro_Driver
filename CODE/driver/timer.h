// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//

#ifndef X7PRO_DRIVER_TIMER_H
#define X7PRO_DRIVER_TIMER_H
#include "stm32h743xx.h"
#include "io.h"

typedef enum {
    TIMER_OUTPUT_NONE      = 0,
    TIMER_OUTPUT_INVERTED  = (1 << 0),
    TIMER_OUTPUT_N_CHANNEL = (1 << 1),
} timer_flag_e;

typedef struct
{
    TIM_TypeDef *tim;
    uint32_t channel;
    uint8_t output;
    io_tag io;

}timer_hw_t;

void Timer_ConfigTimeBase(TIM_TypeDef *tim,  uint16_t period, uint32_t hz);
#endif //X7PRO_DRIVER_TIMER_H
