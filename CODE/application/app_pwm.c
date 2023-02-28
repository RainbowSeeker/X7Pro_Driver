// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//
#include <common.h>
#include "driver/pwm.h"
#include "stm32h7xx_ll_tim.h"
#include "algo/math/maths.h"
#include "syscmd/optparse.h"
#include "syscmd/syscmd.h"
#include "FMS_types.h"

pwm_t pwm[3];

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

static void Motor_Output(int16_t output_l, int16_t output_r)
{
    if (output_l > 0)
    {
        io_set(PD13, IO_LOW);
        PWM_Output(&pwm[1], MIN(output_l, PWM_MAX_DUTY));
    }
    else
    {
        io_set(PD13, IO_HIGH);
        PWM_Output(&pwm[1], MIN(-output_l, PWM_MAX_DUTY));
    }

    if (output_r > 0)
    {
        io_set(PD15, IO_LOW);
        PWM_Output(&pwm[2], MIN(output_r, PWM_MAX_DUTY));
    }
    else
    {
        io_set(PD15, IO_HIGH);
        PWM_Output(&pwm[2], MIN(-output_r, PWM_MAX_DUTY));
    }
}

MCN_DECLARE(control_output);

void App_PWM_Main(void const * argument)
{
    // steer
    //actual freq = 1MHz / period = 50Hz, cycle = 1 / freq = 20ms;
    PWM_Init(&pwm[0], &pwmHw[3], 1*1000*1000, 20000, 0, 0);
    // motor
    //actual freq = 100MHz / period = 10*1000Hz, cycle = 1 / freq = 0.1ms;
    PWM_Init(&pwm[1], &pwmHw[4], 100*1000*1000, 10000, 0, 0);
    PWM_Init(&pwm[2], &pwmHw[6], 100*1000*1000, 10000, 0, 0);

    io_init(PD13, CS_CONFIG);
    io_init(PD15, CS_CONFIG);


    Control_Out_Bus control_out;
    static McnNode_t _control_out_nod;
    _control_out_nod = mcn_subscribe(MCN_HUB(control_output), NULL, NULL);

    while (1)
    {
        if (mcn_poll(_control_out_nod))
        {
            mcn_copy(MCN_HUB(control_output), _control_out_nod, &control_out);

            PWM_Output(&pwm[0], MAX(MIN(control_out.actuator_cmd[1], 1250), 250));
            Motor_Output(control_out.actuator_cmd[1], control_out.actuator_cmd[2]);
        }
        osDelay(1);
    }
    //250 - 750 - 1250
}

int cmd_pwm(int argc, char** argv)
{
    if (argc < 3)   return -1;

    struct optparse options;
    int duty_l, duty_r;

    optparse_init(&options, argv);

    duty_l = atoi(optparse_arg(&options));
    duty_r = atoi(optparse_arg(&options));

    Motor_Output(duty_l, duty_r);

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_pwm, __cmd_pwm, test PWM);