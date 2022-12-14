// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/2.
//

#ifndef X7PRO_DRIVER_OS_DEF_H
#define X7PRO_DRIVER_OS_DEF_H
#include "common_def.h"
#include "cmsis_gcc.h"
#include "cmsis_os.h"
#include "utils/list.h"
#include "object.h"

/* Thread Prority */
#define VEHICLE_THREAD_PRIORITY     5
#define FMTIO_THREAD_PRIORITY       4
#define LOGGER_THREAD_PRIORITY      3
#define MAVLINK_RX_THREAD_PRIORITY  2
#define COMM_THREAD_PRIORITY        1
#define STATUS_THREAD_PRIORITY      0

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

struct thread
{
    struct object parent;
    osThreadId tid;     //freertos thread ptr
    uint32_t    stack_size;                             /**< stack size */
    uint32_t    max_used;
    uint32_t    occupy;

    err_t       error;
    uint8_t     stat;
    uint8_t     priority;
};
typedef struct thread *os_thread_t;
typedef osMutexId os_mutex_t;
typedef osMessageQId os_event_t;
typedef osSemaphoreId os_sem_t;

/* ---------------------os common function---------------------------*/
/**
 * os_tick_get
 * @return
 */
static inline tick_t os_tick_get(void)
{
    return osKernelSysTick();
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

/* ---------------------os thread function---------------------------*/

/*
 * Thread
 */

/*
 * thread state definitions
 */
#define THREAD_INIT                  0x00                /**< Initialized status */
#define THREAD_READY                 0x01                /**< Ready status */
#define THREAD_SUSPEND               0x02                /**< Suspend status */
#define THREAD_RUNNING               0x03                /**< Running status */
#define THREAD_BLOCK                 THREAD_SUSPEND      /**< Blocked status */
#define THREAD_CLOSE                 0x04                /**< Closed status */
#define THREAD_STAT_MASK             0x07

#define THREAD_STAT_YIELD            0x08                /**< indicate whether remaining_tick has been reloaded since last schedule */
#define THREAD_STAT_YIELD_MASK       THREAD_STAT_YIELD

#define THREAD_STAT_SIGNAL           0x10                /**< task hold signals */
#define THREAD_STAT_SIGNAL_READY     (THREAD_STAT_SIGNAL | THREAD_READY)
#define THREAD_STAT_SIGNAL_WAIT      0x20                /**< task is waiting for signals */
#define THREAD_STAT_SIGNAL_PENDING   0x40                /**< signals is held and it has not been procressed */
#define THREAD_STAT_SIGNAL_MASK      0xf0

/**
 * thread control command definitions
 */
#define THREAD_CTRL_STARTUP          0x00                /**< Startup thread. */
#define THREAD_CTRL_CLOSE            0x01                /**< Close thread. */
#define THREAD_CTRL_CHANGE_PRIORITY  0x02                /**< Change thread priority. */
#define THREAD_CTRL_INFO             0x03                /**< Get thread information. */
#define THREAD_CTRL_BIND_CPU         0x04                /**< Set thread bind cpu. */

/**
 * os_thread_get_num
 * @return 
 */
static inline size_t  os_thread_get_num(void)
{
    return uxTaskGetNumberOfTasks();
}
/**
 * os_thread_create
 * @param name
 * @param task_func_t
 * @param parameter
 * @param priority
 * @param stack_size
 * @return
 */
os_thread_t os_thread_create(const char *name, void (*task_func_t)(void *), void *parameter, size_t priority, uint16_t stack_size);


/**
 * os_thread_find
 * @param name
 * @return
 */
os_thread_t os_thread_find(char *name);
/**
 * os_thread_delete
 * @param thread_id
 * @return
 */
err_t os_thread_delete(os_thread_t thread);

/**
 * os_thread_startup
 * @param thread
 * @return
 */
err_t os_thread_startup(os_thread_t thread);

/**
 * os_thread_self
 * @return
 */
os_thread_t os_thread_self(void);

/**
 * os_thread_update_info_all
 */
void os_thread_update_info_all(void);
/**
 * os_thread_suspend
 * @param thread_id
 * @return
 */
static inline err_t os_thread_suspend(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    return osThreadSuspend(thread->tid);
}

/**
 * os_thread_resume
 * @param thread_id
 * @return
 */
static inline err_t os_thread_resume(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    return osThreadResume(thread->tid);
}

static inline err_t os_schedule(void)
{
    //Freertos could yield when thread create, suspend or resume.
    //So it's no need to yield after that.
    return E_OK;
//    return osThreadYield();
}

/* ---------------------os semaphore function---------------------------*/

/**
 * os_sem_create
 * @param sem
 * @param millisec
 * @return
 */
static inline os_sem_t os_sem_create(size_t count)
{
    osSemaphoreId sem;
    if (count == 1) {
        vSemaphoreCreateBinary(sem);
        return sem;
    }
    else {
#if (configUSE_COUNTING_SEMAPHORES == 1 )
        return xSemaphoreCreateCounting(count, count);
#else
        return NULL;
#endif
    }
}

static inline err_t os_sem_delete(os_sem_t sem)
{
    return osSemaphoreDelete(sem);
}

/**
 * os_sem_take
 * @param sem
 * @param millisec
 * @return
 */
static inline err_t os_sem_take(os_sem_t sem, size_t millisec)
{
    return osSemaphoreWait(sem, millisec);
}

static inline err_t os_sem_trytake(os_sem_t sem)
{
    return osSemaphoreWait(sem, 0);
}

/**
 * os_sem_release
 * @param sem
 * @return
 */
static inline err_t os_sem_release(os_sem_t sem)
{
    return osSemaphoreRelease(sem);
}



/* ---------------------os mutex function---------------------------*/

/**
 * os_mutex_init
 * @param mutex
 * @return
 */
static inline err_t os_mutex_init(os_mutex_t *mutex)
{
    *mutex = xSemaphoreCreateMutex();
    return (*mutex != NULL ? E_OK : E_NOMEM);
}

/**
 * os_mutex_detach
 * @param mutex
 */
static inline void os_mutex_detach(os_mutex_t mutex)
{
    //mutex del must be done in thread.
    ASSERT(osMutexDelete(mutex) == 0);
}

/**
 * os_mutex_delete
 * @param mutex
 */
static inline err_t os_mutex_delete(os_mutex_t mutex)
{
    //mutex del must be done in thread.
    return osMutexDelete(mutex);
}

/**
 * os_mutex_take
 * @param mutex
 * @param millisec
 * @return
 */
static inline err_t os_mutex_take(os_mutex_t mutex, size_t millisec)
{
    return osMutexWait(mutex, millisec);
}

/**
 * os_mutex_release
 * @param mutex
 */
static inline void os_mutex_release(os_mutex_t mutex)
{
    osMutexRelease(mutex);
}

/* ---------------------os event function---------------------------*/

/**
 * os_event_init
 * @param event
 * @param queue_size
 * @return
 */
static inline err_t os_event_init(os_event_t *event, size_t queue_size)
{
    *event = xQueueCreate(queue_size, sizeof(uint32_t));
    return (*event != NULL ? E_OK : E_NOMEM);
}

/**
 * os_event_send
 * @param event
 * @param msg
 * @return
 */
static inline err_t os_event_send(os_event_t event, uint32_t msg)
{
    return osMessagePut(event, msg, 0);
}

/**
 * os_event_recv
 * @param event
 * @param timeout
 * @param recved
 * @return
 */
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





err_t os_get_errno(void);
void os_set_errno(err_t error);
char *os_strdup(const char *s);
#endif //X7PRO_DRIVER_OS_DEF_H
