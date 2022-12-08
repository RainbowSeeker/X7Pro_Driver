// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/7.
//

#ifndef X7PRO_DRIVER_DRV_EXTI_H
#define X7PRO_DRIVER_DRV_EXTI_H

#include <common.h>
#include "driver/io.h"
#include "nvic.h"


typedef void (* exti_cb_t)(uint32_t);

typedef enum
{
    EXTI_RISING = 0,
    EXTI_FALLING,
    EXTI_BOTH,
}exti_trigger;

void exti_init(io_t io, exti_cb_t cb, uint32_t user_data, int priority, exti_trigger trigger);
void exti_enable(io_t io);
void exti_disable(io_t io);
#endif //X7PRO_DRIVER_DRV_EXTI_H
