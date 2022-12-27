// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//
#include <stdbool.h>
#include "cmsis_os.h"
#include "driver/pwm.h"
#include "stm32h7xx_ll_tim.h"
#include "algo/math/maths.h"

pwm_t pwm[8];

const timer_hw_t pwmHw[8] = {
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH1, .io = PH10, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH2, .io = PH11, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH3, .io = PH12, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH4, .io = PI0, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH1, .io = PD12, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH2, .io = PD13, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH3, .io = PD14, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH4, .io = PD15, .output = TIMER_OUTPUT_NONE},
};


void App_PWM_Main(void const * argument)
{
    uint16_t value = 5000;
    bool  dir = 1;

    for (int i = 0; i < ARRAYLEN(pwm); ++i)
    {
        //actual freq = 1MHz / period = 200Hz, cycle = 1 / freq = 20ms;
        PWM_Init(&pwm[i], &pwmHw[i], PWM_CONFIG);
    }

    while (1)
    {
        if (value > PWM_MAX_DUTY || value < 0)
        {
            dir = !dir;
            value = dir ? 0 : PWM_MAX_DUTY;
        }
        else
        {
            value += dir ? 10 : -10;
        }

        for (int i = 0; i < ARRAYLEN(pwm); ++i)
        {
            PWM_Output(&pwm[i], value);
        }
        osDelay(10);
    }

}