// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "thread.h"
#include "mem.h"

STATIC_DMA_DATA_AUTO uint8_t thread_stk_array[ALL_THREAD_STK_SIZE];
static uint32_t thread_stk_ptr = 0;

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
        idle->tid = &OSIdleTaskTCB;
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

void os_thread_idle_hook()
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
    os_thread_t thread = calloc(1, sizeof(struct thread));
    if (thread == NULL)
    {
        printf("\r\nno mem");
        return NULL;
    }
    thread->tid = calloc(1, sizeof(OS_TCB));
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

    if (stack_size > MAX_THREAD_STK_SIZE)
    {
        printf("\r\nThe stack_size you set is too high! \r\n Please decrease stack_size to < %d.", MAX_THREAD_STK_SIZE);
        goto _fail;
    }

    if (thread_stk_ptr + stack_size >= ALL_THREAD_STK_SIZE)
    {
        printf("\r\nThe thread_stk_ptr is exhausted! \r\n Please increase your thread_stk_ptr.");
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

    OSTaskCreate(thread->tid,
                 (CPU_CHAR *)name,
                 task_func_t,
                 parameter,
                 priority,
                 (CPU_STK *) &thread_stk_array[thread_stk_ptr],
                 stack_size / 10,
                 stack_size,
                 0,
                 0,
                 0,
                 (OS_OPT_TASK_STK_CHK | 0),
                 &os_err);
    if (os_err != 0)
    {
        goto _fail;
    }
//    memset(&thread_stk_array[thread_stk_ptr], 0, stack_size);
    thread_stk_ptr += stack_size;
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
    OSTaskDel(thread->tid, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

err_t os_thread_suspend(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    if (thread_suspend_hook)
    {
        thread_suspend_hook(thread);
    }
    OSTaskSuspend(thread->tid, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
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

    OSTaskResume(thread->tid, &os_err);
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
        switch (thread->tid->TaskState)
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
        thread->max_used = thread->tid->StkUsed;
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
        if (((os_thread_t)obj)->tid == OSTCBCurPtr)
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