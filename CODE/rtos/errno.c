// Copyright (c) 2023 By RainbowSeeker.

//
// Created by 19114 on 2023/3/17.
//

#include "errno.h"
#include "thread.h"

/* err used for ucos3*/
OS_ERR os_err;

/* global errno */
static err_t os_errno;

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
