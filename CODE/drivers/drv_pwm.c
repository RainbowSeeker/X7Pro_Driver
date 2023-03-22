// Copyright (c) 2022 By RainbowSeeker.

#include <common.h>

#include "hal/actuator/actuator.h"
#include "pwm.h"

#define MAX_PWM_OUT_CHAN      6             // AUX Out has 6 pwm channel

static int16_t _pwm_fmu_duty_cyc[MAX_PWM_OUT_CHAN] = {0};

static pwm_t pwm[MAX_PWM_OUT_CHAN];

static void _pwm_init(void)
{
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
    // steer
    //actual freq = 1MHz / period = 50Hz, cycle = 1 / freq = 20ms;
    PWM_Init(&pwm[0], &pwmHw[3], 1*1000*1000, 20000, 0, 0);
    // motor
    //actual freq = 100MHz / period = 10*1000Hz, cycle = 1 / freq = 0.1ms;
    PWM_Init(&pwm[1], &pwmHw[4], 100*1000*1000, 10000, 0, 0);
    PWM_Init(&pwm[2], &pwmHw[6], 100*1000*1000, 10000, 0, 0);

    io_init(PD13, CS_CONFIG);
    io_init(PD15, CS_CONFIG);

    pwm[1].dir = PD13;
    pwm[2].dir = PD15;
}


size_t pwm_read(actuator_dev_t dev, uint16_t chan_sel, uint16_t *chan_val, size_t size)
{
    int16_t *index = chan_val;

    for (uint8_t i = 0; i < MAX_PWM_OUT_CHAN; i++) {
        if (chan_sel & (1 << i)) {
            *index = _pwm_fmu_duty_cyc[i];
            index++;
        }
    }
    return size;
}

size_t pwm_write(actuator_dev_t dev, uint16_t chan_sel, const uint16_t* chan_val, size_t size)
{
    const uint16_t* index = chan_val;

    for (uint8_t i = 0; i < MAX_PWM_OUT_CHAN; i++) {
        if (chan_sel & (1 << i)) {
            if (i > 0) io_set(pwm[i].dir, *index > 10000 ? IO_LOW : IO_HIGH);
            PWM_Output(&pwm[i], i == 0 ? *index: abs(*index - 10000));
            _pwm_fmu_duty_cyc[i] = *index;
            index++;
        }
    }
    return size;
}

const static struct actuator_ops _act_ops = {
    .dev_config = NULL,
    .dev_control = NULL,
    .dev_read = pwm_read,
    .dev_write = pwm_write
};

static struct actuator_device act_dev = {
    .chan_mask = 0x3F,
    .range = { 0, 20000 },
    .config = {
        .protocol = ACT_PROTOCOL_PWM,
        .chan_num = MAX_PWM_OUT_CHAN,
        .pwm_config = { .pwm_freq = 50 },
        .dshot_config = { 0 } },
    .ops = &_act_ops
};

err_t drv_pwm_init(void)
{
    _pwm_init();

    /* register actuator hal device */
    return hal_actuator_register(&act_dev, "aux_out", DEVICE_FLAG_RDWR, NULL);
}
