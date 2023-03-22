// Copyright (c) 2022-2023 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//

#include "common.h"
#include "pwm.h"
#include "stm32h7xx_ll_tim.h"


void PWM_Init(pwm_t *pwm, const timer_hw_t *timerHardware, uint32_t hz, uint16_t period, uint16_t value, uint8_t inversion)
{
    Timer_ConfigTimeBase(timerHardware->tim, period, hz);

    uint8_t output = inversion ? timerHardware->output ^ TIMER_OUTPUT_INVERTED : timerHardware->output;
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    LL_TIM_OC_StructInit(&TIM_OC_InitStruct);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    if (output & TIMER_OUTPUT_N_CHANNEL) {
        TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_ENABLE;
        TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
        TIM_OC_InitStruct.OCNPolarity = (output & TIMER_OUTPUT_INVERTED) ? LL_TIM_OCPOLARITY_LOW : LL_TIM_OCPOLARITY_HIGH;
    } else {
        TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
        TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_HIGH;
        TIM_OC_InitStruct.OCPolarity =  (output & TIMER_OUTPUT_INVERTED) ? LL_TIM_OCPOLARITY_LOW : LL_TIM_OCPOLARITY_HIGH;
    }
    TIM_OC_InitStruct.CompareValue = value;
    LL_TIM_OC_EnablePreload(timerHardware->tim, timerHardware->channel);
    LL_TIM_OC_Init(timerHardware->tim, timerHardware->channel, &TIM_OC_InitStruct);

    uint32_t alternate = 0;
    if (timerHardware->tim == TIM1 || timerHardware->tim == TIM2 || timerHardware->tim == TIM16 || timerHardware->tim == TIM17)
    {
        alternate = 0x01;
    }
    else if(timerHardware->tim == TIM3 || timerHardware->tim == TIM4 || timerHardware->tim == TIM5 || timerHardware->tim == TIM12 || timerHardware->tim == TIM15)
    {
        alternate = 0x02;
    }
    else if(timerHardware->tim == TIM8)
    {
        alternate = 0x03;
    }
    else ASSERT(0);

    io_init(timerHardware->io, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, alternate);

    LL_TIM_CC_EnableChannel(timerHardware->tim, timerHardware->channel);
    LL_TIM_EnableCounter(timerHardware->tim);


    pwm->ccr = (volatile uint32_t *)((volatile uint32_t*)&timerHardware->tim->CCR1 + (31 - __builtin_clz(timerHardware->channel)) / 4);
    pwm->tim = timerHardware->tim;

    *pwm->ccr = 0;
}



