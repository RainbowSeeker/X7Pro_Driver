// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "thread.h"
#include "mem.h"

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
    return os_thread_find(IDLE_THREAD_NAME);
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

    idle = os_thread_find(IDLE_THREAD_NAME);
    if (idle == NULL)
    {
        idle = malloc(sizeof(struct thread));
        /* init thread list */
        list_init(&idle->tlist);
        object_init(&idle->parent, Object_Class_Thread, IDLE_THREAD_NAME);

        idle->error = E_OK;
        idle->stat = THREAD_READY;
        idle->priority = OSIdleTaskTCB.Prio;
        idle->stack_size = OSIdleTaskTCB.StkSize;
        memcpy(&idle->tid, &OSIdleTaskTCB, sizeof(OS_TCB));
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
 *         -E_NOSYS: hook was not found
 */
err_t os_thread_idle_delhook(void (*hook)(void))
{
    size_t i;
    base_t level;
    err_t ret = -E_NOSYS;

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

void os_thread_idle_hook(void)
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

void os_thread_create_hook(os_thread_t thread)
{
    if (thread_inited_hook)
    {
        thread_inited_hook(thread);
    }
}

void os_scheduler_sethook(void hook(os_thread_t from, os_thread_t to))
{
    scheduler_hook = hook;
}

void os_scheduler_hook(os_thread_t from, os_thread_t to)
{
    if (scheduler_hook && from && to)
    {
        scheduler_hook(from, to);
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
    os_thread_t thread = calloc(1, sizeof(struct thread));
    void *stack_start = malloc(stack_size * sizeof(CPU_STK_SIZE));
    ASSERT(thread && stack_start);

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

    OSTaskCreate(&thread->tid,
                 (CPU_CHAR *)name,
                 task_func_t,
                 parameter,
                 priority,
                 (CPU_STK *) stack_start,
                 stack_size / 10,
                 stack_size,
                 0,
                 0,
                 0,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);
    if (os_err != 0)
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
    ASSERT(thread);
    list_remove(&thread->parent.list);
    if (thread_deleted_hook)
    {
        thread_deleted_hook(thread);
    }
    OSTaskDel(&thread->tid, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

err_t os_thread_suspend(os_thread_t thread)
{
    ASSERT(thread);
    if (thread_suspend_hook)
    {
        thread_suspend_hook(thread);
    }
    OSTaskSuspend(&thread->tid, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

err_t os_thread_resume(os_thread_t thread)
{
    ASSERT(thread);

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

    OSTaskResume(&thread->tid, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}


void os_thread_update_info_all(void)
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
        os_thread_t thread = (os_thread_t)list_entry(node, struct object, list);
        if (strcmp(thread->parent.name, "idle") == 0)
        {
            memcpy(&thread->tid, &OSIdleTaskTCB, sizeof(OS_TCB));
        }
        switch (thread->tid.TaskState)
        {
            case OS_TASK_STATE_RDY:
                thread->stat = THREAD_READY;
                break;
            case OS_TASK_STATE_DLY:
            case OS_TASK_STATE_PEND:
                thread->stat = THREAD_BLOCK;
                break;
            case OS_TASK_STATE_SUSPENDED:
                thread->stat = THREAD_READY;
                break;
            case OS_TASK_STATE_DEL:
                thread->stat = THREAD_CLOSE;
                break;
            default:
                thread->stat = THREAD_READY;
                break;
        }
        thread->max_used = thread->tid.StkUsed;
    }
    /* leave critical */
    os_hw_interrupt_enable(level);

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
        if (&(((os_thread_t)obj)->tid) == OSTCBCurPtr)
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
    struct thread *thread = (struct thread *)parameter;

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