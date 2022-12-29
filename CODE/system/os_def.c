// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/2.
//

#include "os_def.h"

/* global errno */
static volatile int os_errno;

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
                             uint16_t stack_size)
{
    os_thread_t thread = malloc(sizeof(struct thread));

    if (thread == NULL)
    {
        printf("\r\nno mem");
        return NULL;
    }

    if (priority >= OS_MAX_PRIORITY)
    {
        printf("\r\nThe priority you set is too high! \r\n Please decrease priority to < %d.", OS_MAX_PRIORITY);
        return NULL;
    }

    /* init thread list */
    list_init(&thread->tlist);
    object_init(&thread->parent, Object_Class_Thread, name);

    thread->error = E_OK;
    thread->stat = THREAD_INIT;
    thread->priority = priority;
    thread->stack_size = stack_size;

    if (xTaskCreate((TaskFunction_t)task_func_t,(const portCHAR *)name,
                    stack_size, parameter, priority,
                    &thread->tid) != pdPASS)
    {
        free(thread);
        return NULL;
    }
    return thread;
}

err_t os_thread_delete(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    vTaskDelete(thread->tid);
    return E_OK;
}

err_t os_thread_suspend(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;

    return osThreadSuspend(thread->tid);
}

err_t os_thread_resume(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    /* disable interrupt */
    base_t level = os_hw_interrupt_disable();

    /* remove from suspend list */
    list_remove(&thread->tlist);

    /* enable interrupt */
    os_hw_interrupt_enable(level);

    return osThreadResume(thread->tid);
}

err_t os_schedule(void)
{
    return E_OK;
//    return osThreadYield();
}

void os_thread_update_info(const char *name)
{
    uint32_t total_runtime = 0;
    size_t task_num = os_thread_get_num();
    TaskStatus_t task_status;

//    vTaskGetInfo();
//    for(size_t i = 0; i < task_num; i++ )
//    {
//        os_thread_t thread = os_thread_find(task_status[i].pcTaskName);
//
//        thread->max_used = thread->stack_size - task_status[i].usStackHighWaterMark;
//        if (total_runtime)  thread->occupy = task_status[i].ulRunTimeCounter * 100 / total_runtime;
//        else thread->occupy = 0;
//        if (task_status[i].eCurrentState == eReady) thread->stat = THREAD_READY;
//        else if (task_status[i].eCurrentState == eSuspended) thread->stat = THREAD_SUSPEND;
//        else if (task_status[i].eCurrentState == eRunning) thread->stat = THREAD_RUNNING;
//        else if (task_status[i].eCurrentState == eBlocked) thread->stat = THREAD_BLOCK;
//        else thread->stat = THREAD_CLOSE;
//    }
}


void os_thread_update_info_all(void)
{
    uint32_t total_runtime = 0;
    size_t task_num = os_thread_get_num();
    TaskStatus_t *task_status = malloc(task_num * sizeof(TaskStatus_t));

    if (task_status)
    {
        task_num = uxTaskGetSystemState(task_status, task_num, &total_runtime);

        /* update all thread info */
        for(size_t i = 0; i < task_num; i++ )
        {
            os_thread_t thread = os_thread_find(task_status[i].pcTaskName);

            thread->max_used = thread->stack_size - task_status[i].usStackHighWaterMark;
            if (total_runtime)  thread->occupy = task_status[i].ulRunTimeCounter * 100 / total_runtime;
            else thread->occupy = 0;
            if (task_status[i].eCurrentState == eReady) thread->stat = THREAD_READY;
            else if (task_status[i].eCurrentState == eSuspended) thread->stat = THREAD_SUSPEND;
            else if (task_status[i].eCurrentState == eRunning) thread->stat = THREAD_RUNNING;
            else if (task_status[i].eCurrentState == eBlocked) thread->stat = THREAD_BLOCK;
            else thread->stat = THREAD_CLOSE;
        }

        free(task_status);
    }
}

os_thread_t os_thread_find(char *name)
{
    list_t *node;

    struct object_information *information;
    information = object_get_information(Object_Class_Thread);
    ASSERT(information != NULL);

    /* enter critical */
    OS_ENTER_CRITICAL();
    /* try to find object */
    list_for_each(node, &information->object_list)
    {
        struct object *obj;
        obj = list_entry(node, struct object, list);
        if (strncmp(obj->name, name, NAME_MAX_LEN) == 0)
        {
            OS_EXIT_CRITICAL();
            return (os_thread_t)obj;
        }
    }
    /* leave critical */
    OS_EXIT_CRITICAL();
    return NULL;
}


os_thread_t os_thread_self(void)
{
    osThreadId tid = osThreadGetId();
    list_t *node;

    struct object_information *information;
    information = object_get_information(Object_Class_Thread);
    ASSERT(information != NULL);

    /* enter critical */
    OS_ENTER_CRITICAL();
    /* try to find object */
    list_for_each(node, &information->object_list)
    {
        struct object *obj;
        obj = list_entry(node, struct object, list);
        if (((os_thread_t)obj)->tid == tid)
        {
            OS_EXIT_CRITICAL();
            return (os_thread_t)obj;
        }
    }
    /* leave critical */
    OS_EXIT_CRITICAL();
    return NULL;
}

err_t os_thread_startup(os_thread_t thread)
{
    return E_OK;
}

/**
 * This function is the timeout function for thread, normally which is invoked
 * when thread is timeout to wait some resource.
 *
 * @param parameter the parameter of thread timeout function
 */
void os_thread_timeout(void *parameter)
{
    struct thread *thread = (struct thread *)os_timer_get_parameter(parameter);

    /* thread check */
    ASSERT(thread != NULL);

    /* set error number */
    thread->error = -E_TIMEOUT;

    /* remove from suspend list */
    list_remove(&(thread->tlist));

    /* insert to schedule ready list */
    os_thread_resume(thread);

    /* do schedule */
    os_schedule();
}

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
os_timer_t os_timer_create(const char *name,
                           void (*timeout)(void *),
                           void *parameter,
                           tick_t period,
                           uint8_t type)
{
    os_timer_t timer = malloc(sizeof(struct timer));
    if (timer == NULL)
    {
        printf("\r\nno mem");
        return NULL;
    }

    object_init(&timer->parent, Object_Class_Timer, name);
    timer->period = TICKS_FROM_MS(period);

    timer->tid = xTimerCreate(name,
                              timer->period,
                              type == TIMER_TYPE_PERIODIC,
                              (void *) parameter,
                              (TimerCallbackFunction_t)timeout);
    return timer;
}





/*
 * This function will get errno
 *
 * @return errno
 */
err_t os_get_errno(void)
{
    os_thread_t thread;

    if (os_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        return os_errno;
    }

    thread = os_thread_self();
    if (thread == NULL)
        return os_errno;

    return thread->error;
}

/*
 * This function will set errno
 *
 * @param error the errno shall be set
 */
void os_set_errno(err_t error)
{
    os_thread_t thread;

    if (os_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        os_errno = error;
        return;
    }

    thread = os_thread_self();
    if (thread == NULL)
    {
        os_errno = error;
        return;
    }

    thread->error = error;
}

