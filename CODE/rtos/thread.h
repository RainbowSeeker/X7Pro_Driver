// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_THREAD_H
#define X7PRO_DRIVER_THREAD_H


#include "os_common.h"
#include "timer.h"

#define IDLE_THREAD_NAME        "uC/OS-III Idle Task"
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

struct thread
{
    struct object parent;
    OS_TCB      tid;     //thread ptr
    list_t      tlist;                                  /**< the thread list */

    uint32_t    stack_size;                             /**< stack size */
    uint32_t    max_used;

    err_t       error;
    uint8_t     stat;
    uint8_t     priority;
    os_timer_t  thread_timer;
    uint32_t    user_data;
};
typedef struct thread *os_thread_t;

/**
 * os_thread_get_num
 * @return
 */
static_inline size_t  os_thread_get_num(void)
{
    return 0;
}

/**
 * os_schedule
 * @return
 */
static_inline err_t os_schedule(void)
{
    return E_OK;
}

void os_thread_suspend_sethook(void (*hook)(os_thread_t thread));
void os_thread_resume_sethook (void (*hook)(os_thread_t thread));
void os_thread_inited_sethook (void (*hook)(os_thread_t thread));
void os_thread_deleted_sethook(void (*hook)(os_thread_t thread));
os_thread_t os_thread_idle_gethandler();
err_t os_thread_idle_sethook(void (*hook)(void));
err_t os_thread_idle_delhook(void (*hook)(void));
void os_scheduler_sethook(void hook(os_thread_t from, os_thread_t to));


//you should put them in right place according to your os;
void os_scheduler_hook(os_thread_t from, os_thread_t to);
void os_thread_idle_hook(void);
void os_thread_create_hook(os_thread_t thread);
/**
 * os_thread_create
 * @param name
 * @param task_func_t
 * @param parameter
 * @param priority
 * @param stack_size
 * @return
 */
os_thread_t os_thread_create(const char *name,
                             void (*task_func_t)(void *),
                             void *parameter,
                             size_t priority,
                             uint16_t stack_size);
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
 * os_thread_resume
 * @param thread
 * @return
 */
err_t os_thread_resume(os_thread_t thread);

/**
 * os_thread_suspend
 * @param thread_id
 * @return
 */
err_t os_thread_suspend(os_thread_t thread);

void os_thread_timeout(void *parameter);
/**
 * os_thread_self
 * @return
 */
os_thread_t os_thread_self(void);

/**
 * os_thread_update_info_all
 */
void os_thread_update_info_all(void);
#endif //X7PRO_DRIVER_THREAD_H
