// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/2.
//

#ifndef X7PRO_DRIVER_OS_DEF_H
#define X7PRO_DRIVER_OS_DEF_H
#include "common_def.h"
#include "cmsis_gcc.h"
#include "cmsis_os.h"

/* Thread Prority */
#define VEHICLE_THREAD_PRIORITY     0
#define FMTIO_THREAD_PRIORITY       1
#define LOGGER_THREAD_PRIORITY      2
#define MAVLINK_RX_THREAD_PRIORITY  3
#define COMM_THREAD_PRIORITY        4
#define STATUS_THREAD_PRIORITY      5

#define OS_MAX_PRIORITY             7

#if configMAX_PRIORITIES != OS_MAX_PRIORITY
#error "must ensure that 'configMAX_PRIORITIES' equal 'OS_MAX_PRIORITY' "
#endif

#define MAX_THREAD_NUM          10
#define TICK_PER_SECOND         1000
#define TICKS_FROM_MS(_ms)      ((TICK_PER_SECOND * _ms + 999) / 1000)



/* note: modify the following micro according to your os */
#define OS_ENTER_CRITICAL       vPortEnterCritical
#define OS_EXIT_CRITICAL        vPortExitCritical

#define MALLOC                  pvPortMalloc
#define FREE                    vPortFree


typedef osThreadId os_thread_t;
typedef osMutexId os_mutex_t;
typedef osMessageQId os_event_t;


static inline tick_t os_tick_get(void)
{
    return osKernelSysTick();
}

static inline void os_delay(uint32_t ms)
{
    vTaskDelay(TICKS_FROM_MS(ms));
}

static inline void os_delay_until(uint32_t *init_tick, uint32_t ms)
{
    osDelayUntil(init_tick, ms);
}

static inline os_thread_t os_thread_self(void)
{
    return osThreadGetId();
}

static inline base_t os_hw_interrupt_disable()
{
    return portSET_INTERRUPT_MASK_FROM_ISR();
}

static inline void os_hw_interrupt_enable(base_t x)
{
    portCLEAR_INTERRUPT_MASK_FROM_ISR(x);
}

static inline uint8_t os_interrupt_get_nest(void)
{
    return __get_IPSR();
}

static inline err_t os_mutex_init(os_mutex_t *mutex)
{
    *mutex = xSemaphoreCreateMutex();
    return (*mutex != NULL ? E_OK : E_NOMEM);
}

static inline void os_mutex_detach(os_mutex_t mutex)
{
    //mutex del must be done in thread.
    ASSERT(osMutexDelete(mutex) == 0);
}

static inline void os_mutex_delete(os_mutex_t mutex)
{
    //mutex del must be done in thread.
    ASSERT(osMutexDelete(mutex) == 0);
}

static inline err_t os_mutex_take(os_mutex_t mutex, size_t millisec)
{
    return osMutexWait(mutex, millisec);
}

static inline void os_mutex_release(os_mutex_t mutex)
{
    osMutexRelease(mutex);
}

static inline err_t os_event_init(os_event_t *event, size_t queue_size)
{
    *event = xQueueCreate(queue_size, sizeof(uint32_t));
    return (*event != NULL ? E_OK : E_NOMEM);
}

static inline err_t os_event_send(os_event_t event, uint32_t msg)
{
    return osMessagePut(event, msg, 0);
}

static inline err_t os_event_recv(os_event_t event, uint32_t timeout, uint32_t *recved)
{
    osEvent recv = osMessageGet(event, timeout);
    switch (recv.status)
    {
        case osEventMessage:
            *recved = recv.value.v;
            return E_OK;
        case osEventTimeout:
            return E_TIMEOUT;
        default:
            return E_RROR;
    }
}


os_thread_t os_thread_init(const char *name, void (*task_func_t)(void *), size_t priority, uint16_t stack_size);
err_t os_get_errno(void);
void os_set_errno(err_t error);
char *os_strdup(const char *s);
#endif //X7PRO_DRIVER_OS_DEF_H
