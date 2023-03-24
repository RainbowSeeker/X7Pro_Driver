// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "timer.h"

err_t os_timer_init(os_timer_t timer,
                           const char *name,
                           void (*timeout)(void *p_tmr, void *p_arg),
                           void *parameter,
                           tick_t period,
                           uint8_t type)
{
    ASSERT(timer);

    object_init(&timer->parent, Object_Class_Timer, name);
    timer->period = TICKS_FROM_MS(period);

    OSTmrCreate(&timer->tid,
                (CPU_CHAR *)name,
                timer->period,
                timer->period,
                (type & TIMER_TYPE_PERIODIC) ? OS_OPT_TMR_PERIODIC : OS_OPT_TMR_ONE_SHOT,
                timeout,
                parameter,
                &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

os_timer_t os_timer_create(const char *name,
                           void (*timeout)(void *p_tmr, void *p_arg),
                           void *parameter,
                           tick_t period,
                           uint8_t type)
{
    os_timer_t timer = calloc(1, sizeof(struct timer));
    ASSERT(timer);
    if (os_timer_init(timer, name, timeout, parameter, period, type) != E_OK)
    {
        os_set_errno(-E_EMPTY);
        return NULL;
    }

    return timer;
}
