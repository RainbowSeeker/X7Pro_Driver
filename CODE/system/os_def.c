// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/2.
//

#include "os_def.h"
#include "stdio.h"
/* global errno */
static volatile int os_errno;

struct
{
    struct {
        os_thread_t tid;
        int error;
    }thread_info[MAX_THREAD_NUM];
    size_t thread_count;
}save_thread_info;

os_thread_t os_thread_init(const char *name, void (*task_func_t)(void *), size_t priority, uint16_t stack_size)
{
    TaskHandle_t handle;

    if (save_thread_info.thread_count >= MAX_THREAD_NUM)
    {
        printf("\r\nnum of thread reach the limit! \r\n Please modify MAX_THREAD_NUM to repair this.");
        return NULL;
    }

    if (priority >= OS_MAX_PRIORITY)
    {
        printf("\r\nThe priority you set is too high! \r\n Please decrease priority to < %d.", OS_MAX_PRIORITY);
        return NULL;
    }

    if (xTaskCreate((TaskFunction_t)task_func_t,(const portCHAR *)name,
                    stack_size, NULL, priority,
                    &handle) != pdPASS)
    {
        return NULL;
    }
    save_thread_info.thread_info[save_thread_info.thread_count].tid = handle;
    save_thread_info.thread_count++;
    return handle;
}

/*
 * This function will get errno
 *
 * @return errno
 */
err_t os_get_errno(void)
{
    os_thread_t tid;

    if (os_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        return os_errno;
    }

    tid = os_thread_self();

    if (tid == NULL)
        return os_errno;

    base_t level = os_hw_interrupt_disable();
    for (size_t i = 0; i < save_thread_info.thread_count; ++i)
    {
        if (tid == save_thread_info.thread_info[i].tid)
        {
            os_hw_interrupt_enable(level);
            return save_thread_info.thread_info[i].error;
        }
    }
    os_hw_interrupt_enable(level);

    return os_errno;
}

/*
 * This function will set errno
 *
 * @param error the errno shall be set
 */
void os_set_errno(err_t error)
{
    os_thread_t tid;

    if (os_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        os_errno = error;
        return;
    }

    tid = os_thread_self();
    if (tid == NULL)
    {
        os_errno = error;
        return;
    }

    base_t level = os_hw_interrupt_disable();
    for (size_t i = 0; i < save_thread_info.thread_count; ++i)
    {
        if (tid == save_thread_info.thread_info[i].tid)
        {
            save_thread_info.thread_info[i].error = error;
            os_hw_interrupt_enable(level);
            return;
        }
    }
    os_hw_interrupt_enable(level);
}

