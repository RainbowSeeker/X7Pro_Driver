// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//

#ifndef X7PRO_DRIVER_PWM_H
#define X7PRO_DRIVER_PWM_H
#include "timer.h"


#define PWM_MAX_DUTY        10000
#define PWM_PERIOD          5000
#define PWM_CONFIG          1*1000*1000, PWM_PERIOD, 0, 0


typedef struct {
    volatile uint32_t *ccr;
    TIM_TypeDef       *tim;
}pwm_t;



void PWM_Init(pwm_t *pwm, const timer_hw_t *timerHardware, uint32_t hz, uint16_t period, uint16_t value, uint8_t inversion);

__STATIC_INLINE void PWM_Output(pwm_t *pwm, uint16_t value)
{
    WRITE_REG(*pwm->ccr, value * (pwm->tim->ARR + 1) / PWM_MAX_DUTY);
}

#endif //X7PRO_DRIVER_PWM_H
