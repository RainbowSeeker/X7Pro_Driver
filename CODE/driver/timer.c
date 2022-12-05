// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//

#include "timer.h"
#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_bus.h"
#include <common.h>

static uint32_t GetTimerClock(TIM_TypeDef *tim)
{
    int timpre;
    uint32_t pclk;
    uint32_t ppre;
#ifdef STM32H743xx
#define PERIPH_PRESCALER(bus) ((RCC->D2CFGR & RCC_D2CFGR_D2PPRE ## bus) >> RCC_D2CFGR_D2PPRE ## bus ## _Pos)
#endif
    if (tim == TIM1 || tim == TIM8 || tim == TIM15 || tim == TIM16 || tim == TIM17) {
        // Timers on APB2
        pclk = HAL_RCC_GetPCLK2Freq();
        ppre = PERIPH_PRESCALER(2);
    } else {
        // Timers on APB1
        pclk = HAL_RCC_GetPCLK1Freq();
        ppre = PERIPH_PRESCALER(1);
    }

    timpre = (RCC->CFGR & RCC_CFGR_TIMPRE) ? 1 : 0;

    int index = (timpre << 3) | ppre;

    static uint8_t periphToKernel[16] = { // The multiplier table
            1, 1, 1, 1, 2, 2, 2, 2, // TIMPRE = 0
            1, 1, 1, 1, 2, 4, 4, 4  // TIMPRE = 1
    };

    return pclk * periphToKernel[index];
}
static void Tim_EnableClock(TIM_TypeDef *tim)
{
    switch ((uint32_t)tim)
    {
        case (uint32_t)TIM1:
            __HAL_RCC_TIM1_CLK_ENABLE();
            break;
        case (uint32_t)TIM2:
            __HAL_RCC_TIM2_CLK_ENABLE();
            break;
        case (uint32_t)TIM3:
            __HAL_RCC_TIM3_CLK_ENABLE();
            break;
        case (uint32_t)TIM4:
            __HAL_RCC_TIM4_CLK_ENABLE();
            break;
        case (uint32_t)TIM5:
            __HAL_RCC_TIM5_CLK_ENABLE();
            break;
        default:
            break;
    }
}
void Timer_ConfigTimeBase(TIM_TypeDef *tim,  uint16_t period, uint32_t hz)
{
    Tim_EnableClock(tim);

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_StructInit(&TIM_InitStruct);

    // fclk = 200M
    TIM_InitStruct.Prescaler  = (GetTimerClock(tim) / hz) - 1;
    TIM_InitStruct.Autoreload = (period - 1) & 0xFFFF;
    TIM_InitStruct.ClockDivision = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;

    LL_TIM_Init(tim, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(tim);
    LL_TIM_SetClockSource(tim, LL_TIM_CLOCKSOURCE_INTERNAL);
}