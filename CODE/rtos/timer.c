// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "timer.h"

os_timer_t os_timer_create(const char *name,
                           void (*timeout)(void *p_tmr, void *p_arg),
                           void *parameter,
                           tick_t period,
                           uint8_t type)
{
    os_timer_t timer = calloc(1, sizeof(struct timer));

    if (timer == NULL)
    {
        printf("\r\nno mem");
        return NULL;
    }

    object_init(&timer->parent, Object_Class_Timer, name);
    timer->period = TICKS_FROM_MS(period);

    OSTmrCreate(&timer->tid,
                name,
                timer->period,
                timer->period,
                type == TIMER_TYPE_PERIODIC ? OS_OPT_TMR_PERIODIC : OS_OPT_TMR_ONE_SHOT,
                timeout,
                parameter,
                &os_err);
    return timer;
}
