// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//
#include <stdbool.h>
#include "cmsis_os.h"
#include "driver/pwm.h"
#include "stm32h7xx_ll_tim.h"
#include "maths.h"

pwm_t pwm[8];

const timer_hw_t pwmHw[8] = {
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH1, .io = {.port = GPIOH, .pin = GPIO_PIN_10}, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH2, .io = {.port = GPIOH, .pin = GPIO_PIN_11}, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH3, .io = {.port = GPIOH, .pin = GPIO_PIN_12}, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM5, .channel = LL_TIM_CHANNEL_CH4, .io = {.port = GPIOI, .pin = GPIO_PIN_0 }, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH1, .io = {.port = GPIOD, .pin = GPIO_PIN_12}, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH2, .io = {.port = GPIOD, .pin = GPIO_PIN_13}, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH3, .io = {.port = GPIOD, .pin = GPIO_PIN_14}, .output = TIMER_OUTPUT_NONE},
        {.tim = TIM4, .channel = LL_TIM_CHANNEL_CH4, .io = {.port = GPIOD, .pin = GPIO_PIN_15}, .output = TIMER_OUTPUT_NONE},
};


void App_PWM_Main(void const * argument)
{
    uint16_t value = 5000;
    bool  dir = 1;

    for (int i = 0; i < ARRAYLEN(pwm); ++i)
    {
        //actual freq = 10MHz / period = 10k, cycle = 1 / freq = 0.1ms;
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