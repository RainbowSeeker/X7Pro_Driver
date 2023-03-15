// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "thread.h"

/* global errno */
static volatile int os_errno;

static void (*thread_suspend_hook)(os_thread_t thread);
static void (*thread_resume_hook) (os_thread_t thread);
static void (*thread_inited_hook) (os_thread_t thread);
static void (*thread_deleted_hook)(os_thread_t thread);
static void (*scheduler_hook)(os_thread_t from, os_thread_t to);

/**
 * @ingroup Hook
 * This function sets a hook function when the system suspend a thread.
 *
 * @param hook the specified hook function
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
void os_thread_suspend_sethook(void (*hook)(os_thread_t thread))
{
    thread_suspend_hook = hook;
}

/**
 * @ingroup Hook
 * This function sets a hook function when the system resume a thread.
 *
 * @param hook the specified hook function
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
void os_thread_resume_sethook(void (*hook)(os_thread_t thread))
{
    thread_resume_hook = hook;
}

/**
 * @ingroup Hook
 * This function sets a hook function when a thread is initialized.
 *
 * @param hook the specified hook function
 */
void os_thread_inited_sethook(void (*hook)(os_thread_t thread))
{
    thread_inited_hook = hook;
}

/**
 * @ingroup Hook
 * This function sets a hook function when a thread is deleted.
 *
 * @param hook the specified hook function
 */
void os_thread_deleted_sethook(void (*hook)(os_thread_t thread))
{
    thread_deleted_hook = hook;
}

#define IDLE_HOOK_LIST_SIZE  4

static void (*idle_hook_list[IDLE_HOOK_LIST_SIZE])(void);


os_thread_t os_thread_idle_gethandler()
{
    return os_thread_find("idle");
}


/**
 * @ingroup Hook
 * This function sets a hook function to idle thread loop. When the system performs
 * idle loop, this hook function should be invoked.
 *
 * @param hook the specified hook function
 *
 * @return E_OK: set OK
 *         -EFULL: hook list is full
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
err_t os_thread_idle_sethook(void (*hook)(void))
{
    size_t i;
    base_t level;
    err_t ret = -E_FULL;
    os_thread_t idle;

    idle = os_thread_find("idle");
    if (idle == NULL)
    {
        idle = malloc(sizeof(struct thread));
        /* init thread list */
        list_init(&idle->tlist);
        object_init(&idle->parent, Object_Class_Thread, "idle");

        idle->error = E_OK;
        idle->stat = THREAD_READY;
        idle->priority = 0;
        idle->stack_size = 1024;
        idle->tid = xTaskGetIdleTaskHandle();
        if (thread_inited_hook)
        {
            thread_inited_hook(idle);
        }
    }


    /* disable interrupt */
    level = os_hw_interrupt_disable();

    for (i = 0; i < IDLE_HOOK_LIST_SIZE; i++)
    {
        if (idle_hook_list[i] == NULL)
        {
            idle_hook_list[i] = hook;
            ret = E_OK;
            break;
        }
    }
    /* enable interrupt */
    os_hw_interrupt_enable(level);

    return ret;
}

/**
 * delete the idle hook on hook list
 *
 * @param hook the specified hook function
 *
 * @return E_OK: delete OK
 *         -ENOSYS: hook was not found
 */
err_t os_thread_idle_delhook(void (*hook)(void))
{
    size_t i;
    base_t level;
    err_t ret = -ENOSYS;

    /* disable interrupt */
    level = os_hw_interrupt_disable();

    for (i = 0; i < IDLE_HOOK_LIST_SIZE; i++)
    {
        if (idle_hook_list[i] == hook)
        {
            idle_hook_list[i] = NULL;
            ret = E_OK;
            break;
        }
    }
    /* enable interrupt */
    os_hw_interrupt_enable(level);

    return ret;
}

static void os_thread_idle_hook()
{
    size_t i;
    for (i = 0; i < IDLE_HOOK_LIST_SIZE; i++)
    {
        if (idle_hook_list[i] != NULL)
        {
            idle_hook_list[i]();
        }
    }
}

/* Compiler Related Definitions */
#if defined(__CC_ARM) || defined(__CLANG_ARM)           /* ARM Compiler */
void IDLE_FUNC_NAME(){os_thread_idle_hook();}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
void IDLE_FUNC_NAME() __attribute__((weak, alias("os_thread_idle_hook")));
#else
#error not supported tool chain
#endif

void os_scheduler_sethook(void hook(os_thread_t from, os_thread_t to))
{
    scheduler_hook = hook;
}

void os_scheduler_hook()
{
    os_thread_t from = os_thread_self();
    if (from && scheduler_hook)
    {
        scheduler_hook(from, NULL);
    }
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
        goto _fail;
    }

    /* init thread list */
    list_init(&thread->tlist);
    object_init(&thread->parent, Object_Class_Thread, name);

    thread->error = E_OK;
    thread->stat = THREAD_READY;
    thread->priority = priority;
    thread->stack_size = stack_size;
    if (thread_inited_hook)
    {
        thread_inited_hook(thread);
    }

    if (xTaskCreate((TaskFunction_t)task_func_t,(const portCHAR *)name,
                    stack_size, parameter, priority,
                    &thread->tid) != pdPASS)
    {
        goto _fail;
    }
    return thread;

    _fail:
    free(thread);
    return NULL;
}

err_t os_thread_delete(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    if (thread_deleted_hook)
    {
        thread_deleted_hook(thread);
    }
    list_remove(&thread->parent.list);
    vTaskDelete(thread->tid);
    return E_OK;
}

err_t os_thread_suspend(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    if (thread_suspend_hook)
    {
        thread_suspend_hook(thread);
    }

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
    if (thread_resume_hook)
    {
        thread_resume_hook(thread);
    }

    return osThreadResume(thread->tid);
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
    size_t task_num = os_thread_get_num();
    TaskStatus_t *task_status = malloc(task_num * sizeof(TaskStatus_t));

    if (task_status)
    {
        task_num = uxTaskGetSystemState(task_status, task_num, NULL);

        /* update all thread info */
        for(size_t i = 0; i < task_num; i++ )
        {
            os_thread_t thread = os_thread_find(task_status[i].pcTaskName);

            thread->max_used = thread->stack_size - task_status[i].usStackHighWaterMark;
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
    base_t level = os_hw_interrupt_disable();
    /* try to find object */
    list_for_each(node, &information->object_list)
    {
        struct object *obj;
        obj = list_entry(node, struct object, list);
        if (strncmp(obj->name, name, NAME_MAX_LEN) == 0)
        {
            os_hw_interrupt_enable(level);
            return (os_thread_t)obj;
        }
    }
    /* leave critical */
    os_hw_interrupt_enable(level);
    return NULL;
}


os_thread_t os_thread_self(void)
{
    osThreadId tid = osThreadGetId();
    list_t *node;

    struct object_information *information;
    information = object_get_information(Object_Class_Thread);
    ASSERT(information != NULL);

    base_t level = os_hw_interrupt_disable();
    /* try to find object */
    list_for_each(node, &information->object_list)
    {
        struct object *obj;
        obj = list_entry(node, struct object, list);
        if (((os_thread_t)obj)->tid == tid)
        {
            os_hw_interrupt_enable(level);
            return (os_thread_t)obj;
        }
    }
    os_hw_interrupt_enable(level);
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
