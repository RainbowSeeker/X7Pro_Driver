// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/12.
//

#ifndef X7PRO_DRIVER_EXTI_H
#define X7PRO_DRIVER_EXTI_H
#include "io.h"
#include "nvic.h"

typedef enum {
    EXTI_RISING = 0,
    EXTI_FALLING = 1,
    EXTI_BOTH = 2
} exti_trigger_t;

typedef struct exti_callback_rec_s exti_callback_rec_t;
typedef void ExtiHandler_Callback(exti_callback_rec_t *self);

struct exti_callback_rec_s {
    ExtiHandler_Callback *fn;
};

void EXTI_Init(void);
void EXTI_Disable(io_t io);
void EXTI_Enable(io_t io);
void EXTI_Config(io_t io, exti_callback_rec_t *cb, int irqPriority, exti_trigger_t trigger);
#endif //X7PRO_DRIVER_EXTI_H
