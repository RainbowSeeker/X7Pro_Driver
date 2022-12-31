// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_OS_COMMON_H
#define X7PRO_DRIVER_OS_COMMON_H

#include "common_def.h"
#include "cmsis_gcc.h"
#include "cmsis_os.h"
#include "utils/list.h"
#include "object.h"
#include "system/systime.h"

/* Thread Prority */
#define VEHICLE_THREAD_PRIORITY     6
#define FMTIO_THREAD_PRIORITY       4
#define LOGGER_THREAD_PRIORITY      3
#define MAVLINK_RX_THREAD_PRIORITY  2
#define COMM_THREAD_PRIORITY        1
#define STATUS_THREAD_PRIORITY      0

#define OS_MAX_PRIORITY             7

#if OS_MAX_PRIORITY != configMAX_PRIORITIES
#error "must ensure that 'configMAX_PRIORITIES' equal 'OS_MAX_PRIORITY' "
#endif

/* note: modify the following micro according to your os */
#define OS_ENTER_CRITICAL()     vPortEnterCritical()
#define OS_EXIT_CRITICAL()      vPortExitCritical()

#define MALLOC                  pvPortMalloc
#define FREE                    vPortFree

#define TICK_PER_SECOND         configTICK_RATE_HZ
#define TICKS_FROM_MS(_ms)      ((TICK_PER_SECOND * _ms + 999) / 1000)

/**
 * os_tick_get
 * @return
 */
static inline tick_t os_tick_get(void)
{
    return systime_now_ms();
}

/**
 * os_delay
 * @param ms
 */
static inline void os_delay(uint32_t ms)
{
    vTaskDelay(TICKS_FROM_MS(ms));
}

/**
 * os_delay_until
 * @param init_tick
 * @param ms
 */
static inline void os_delay_until(uint32_t *init_tick, uint32_t ms)
{
    osDelayUntil(init_tick, ms);
}

/**
 * os_hw_interrupt_disable
 * @return
 */
static inline base_t os_hw_interrupt_disable()
{
    return portSET_INTERRUPT_MASK_FROM_ISR();
}

/**
 * os_hw_interrupt_enable
 * @param x
 */
static inline void os_hw_interrupt_enable(base_t x)
{
    portCLEAR_INTERRUPT_MASK_FROM_ISR(x);
}

/**
 * os_interrupt_get_nest
 * @return
 */
static inline uint8_t os_interrupt_get_nest(void)
{
    return __get_IPSR();
}

static inline void os_interrupt_enter(void)
{

}

static inline void os_interrupt_leave(void)
{

}


#endif //X7PRO_DRIVER_OS_COMMON_H
