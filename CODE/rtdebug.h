// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/17.
//

#ifndef _RTDEBUG_H
#define _RTDEBUG_H


#define ASSERT(expr)    \
if(!(expr))             \
{                       \
    assert_failed(#expr, __FUNCTION__, __FILE__, __LINE__); \
}

/**
 * 断言错误处理
 * @param string
 */
static inline void assert_failed(const char *ex_string, const char *func, const char *file, size_t line)
{
    printf("\r\n(%s) assertion failed at function:%s, in file:%s, line:%d\r\n", ex_string, func, file, line);
    while(1);
}


#define RT_DEBUG_NOT_IN_INTERRUPT                                             \
do                                                                            \
{                                                                             \
    base_t _level;                                                          \
    _level = os_hw_interrupt_disable();                                        \
    if (os_interrupt_get_nest() != 0)                                         \
    {                                                                         \
        printf("Function[%s] shall not be used in ISR\n", __FUNCTION__);  \
        ASSERT(0)                                                          \
    }                                                                         \
    os_hw_interrupt_enable(_level);                                            \
}                                                                             \
while (0)

/* "In thread context" means:
 *     1) the scheduler has been started
 *     2) not in interrupt context.
 */
#define RT_DEBUG_IN_THREAD_CONTEXT                                            \
do                                                                            \
{                                                                             \
    base_t level;                                                          \
    level = os_hw_interrupt_disable();                                        \
    if (os_thread_self() == NULL)                                          \
    {                                                                         \
        printf("Function[%s] shall not be used before scheduler start\n", \
                   __FUNCTION__);                                             \
        ASSERT(0)                                                          \
    }                                                                         \
    RT_DEBUG_NOT_IN_INTERRUPT;                                                \
    os_hw_interrupt_enable(level);                                            \
}                                                                             \
while (0)


/* "scheduler available" means:
 *     1) the scheduler has been started.
 *     2) not in interrupt context.
 *     3) scheduler is not locked.
 */
#define RT_DEBUG_SCHEDULER_AVAILABLE(need_check)                              \
do                                                                            \
{                                                                             \
    if (need_check)                                                           \
    {                                                                         \
        base_t level;                                                      \
        level = os_hw_interrupt_disable();                                    \
        if (os_interrupt_get_nest() != 0)                                         \
        {                                                                     \
            printf("Function[%s]: scheduler is not available\n",          \
                    __FUNCTION__);                                            \
            ASSERT(0)                                                      \
        }                                                                     \
        RT_DEBUG_IN_THREAD_CONTEXT;                                           \
        os_hw_interrupt_enable(level);                                        \
    }                                                                         \
}                                                                             \
while (0)

#endif //X7PRO_DRIVER_RTDEBUG_H
