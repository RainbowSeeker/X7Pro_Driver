// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef RTOS_TIMER_H
#define RTOS_TIMER_H
#include "os_common.h"


#define TIMER_TYPE_ONE_SHOT         0
#define TIMER_TYPE_PERIODIC         1

struct timer
{
    struct object parent;
    OS_TMR tid;     //timer ptr
    tick_t period;
};
typedef struct timer *os_timer_t;


/**
 * This function will initialize a timer, normally this function is used to
 * initialize a static timer object.
 *
 * @param timer the static timer object
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param period the tick of timer
 * @param type the type of timer
 */
err_t os_timer_init(os_timer_t timer,
                    const char *name,
                    void (*timeout)(void *p_tmr, void *p_arg),
                    void *parameter,
                    tick_t period,
                    uint8_t type);


/**
 *
 * @param name
 * @param timeout
 * @param parameter
 * @param period
 * @param type
 * @return
 */
os_timer_t os_timer_create(const char *name,
                           void (*timeout)(void *p_tmr, void *p_arg),
                           void *parameter,
                           tick_t period,
                           uint8_t type);


/**
 * os_timer_start
 * @param timer
 * @return
 */
err_t os_timer_start(os_timer_t timer);


/**
 * os_timer_stop
 * @param timer
 * @return
 */
err_t os_timer_stop(os_timer_t timer);

#endif //RTOS_TIMER_H
