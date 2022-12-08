// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/2.
//

#include "os_def.h"


/* global errno */
static volatile int os_errno;

slist_t save_thread_info;
uint8_t save_thread_num = 0;
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
    os_thread_t thread = malloc(sizeof(struct os_thread));

    if (thread == NULL)
    {
        printf("\r\nno mem");
        return NULL;
    }

    if (save_thread_num >= MAX_THREAD_NUM)
    {
        printf("\r\nnum of thread reach the limit! \r\n Please modify MAX_THREAD_NUM to repair this.");
        return NULL;
    }

    if (priority >= OS_MAX_PRIORITY)
    {
        printf("\r\nThe priority you set is too high! \r\n Please decrease priority to < %d.", OS_MAX_PRIORITY);
        return NULL;
    }

    strcpy(thread->name, name);
    slist_append(&save_thread_info, &thread->list);

    if (xTaskCreate((TaskFunction_t)task_func_t,(const portCHAR *)name,
                    stack_size, parameter, priority,
                    &thread->tid) != pdPASS)
    {
        slist_remove(&save_thread_info, &thread->list);
        free(thread);
        return NULL;
    }

    save_thread_num++;
    return thread;
}

err_t os_thread_delete(os_thread_t thread)
{
    if (thread == NULL) return E_EMPTY;
    vTaskDelete(thread->tid);
    return E_OK;
}

os_thread_t os_thread_self(void)
{
    osThreadId tid = osThreadGetId();
    slist_t *node;
    os_thread_t thread;
    slist_for_each(node, &save_thread_info)
    {
        thread = slist_entry(node, struct os_thread, list);
        if (tid == thread->tid)
        {
            return thread;
        }
    }

    return NULL;
}

err_t os_thread_startup(os_thread_t thread)
{
    os_thread_resume(thread);
    if (os_thread_self() != NULL)
    {
        os_schedule();
    }
    return E_OK;
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

