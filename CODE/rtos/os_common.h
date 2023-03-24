// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_OS_COMMON_H
#define X7PRO_DRIVER_OS_COMMON_H
#include "rtdebug.h"
#include "os_errno.h"
#include "common_def.h"
#include "utils/list.h"
#include "object.h"
#include "system/systime.h"

/* Thread Prority MUST BE !!!UNIQUE!!! */
#define VEHICLE_THREAD_PRIORITY     2
#define FMTIO_THREAD_PRIORITY       3
#define LOGGER_THREAD_PRIORITY      4
#define MAVLINK_RX_THREAD_PRIORITY  5
#define COMM_THREAD_PRIORITY        6
#define STATUS_THREAD_PRIORITY      7

#define FINSH_THREAD_PRIORITY       0
#define GPS_PROBE_THREAD_PRIORITY   10
#define WQ_HP_THREAD_PRIORITY       1
#define WQ_LP_THREAD_PRIORITY       19
#define STARTUP_THREAD_PRIORITY     20
#define STARTUP_TASK_STK_SIZE       1024

#define OS_MAX_PRIORITY             64

#if OS_MAX_PRIORITY != OS_CFG_PRIO_MAX
#error "must ensure that 'OS_MAX_PRIORITY' equal 'OS_CFG_PRIO_MAX' "
#endif

/* note: modify the following micro according to your os */
#define OS_ENTER_CRITICAL()     CPU_SR_ALLOC();CPU_CRITICAL_ENTER()
#define OS_EXIT_CRITICAL()      CPU_CRITICAL_EXIT()

#define TICK_PER_SECOND         OS_CFG_TICK_RATE_HZ
#define TICKS_FROM_MS(_ms)      ((TICK_PER_SECOND * _ms + 999) / 1000)

#define OS_WAITING_FOREVER      (size_t)(-1)

int __ffs(int value);
/**
 *
 * @param OS_TASK_PTR
 */
void bsp_os_init(void (*StartupTask)(void *p_arg));

/**
 * os_tick_get
 * @return
 */
__STATIC_INLINE tick_t os_tick_get(void)
{
    return systime_now_ms();
}

/**
 * os_delay
 * @param ms
 */
__STATIC_INLINE void os_delay(uint32_t ms)
{
    OSTimeDly(TICKS_FROM_MS(ms), OS_OPT_TIME_DLY, &os_err);
}

/**
 * os_delay_until
 * @param init_tick
 * @param ms
 */
__STATIC_INLINE void os_delay_until(uint32_t *init_tick, uint32_t ms)
{
    OSTimeDly(TICKS_FROM_MS(ms), OS_OPT_TIME_DLY, &os_err);
}

/**
 * os_hw_interrupt_disable
 * @return
 */
__STATIC_INLINE base_t os_hw_interrupt_disable(void)
{
    return CPU_SR_Save(CPU_CFG_KA_IPL_BOUNDARY << (8u - CPU_CFG_NVIC_PRIO_BITS));
}

/**
 * os_hw_interrupt_enable
 * @param x
 */
__STATIC_INLINE void os_hw_interrupt_enable(base_t x)
{
    CPU_SR_Restore(x);
}

/**
 * os_interrupt_get_nest
 * @return
 */
__STATIC_INLINE uint8_t os_interrupt_get_nest(void)
{
    return OSIntNestingCtr;
//    return __get_IPSR();
}

__STATIC_INLINE void os_interrupt_enter(void)
{
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    OSIntEnter();                                               /* Tell uC/OS-III that we are starting an ISR           */
    CPU_CRITICAL_EXIT();
}

__STATIC_INLINE void os_interrupt_leave(void)
{
    OSIntExit();
}


#endif //X7PRO_DRIVER_OS_COMMON_H
