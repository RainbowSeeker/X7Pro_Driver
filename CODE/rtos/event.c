// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "event.h"

/**
 * os_event_init
 * @param event
 * @param queue_size
 * @return
 */
err_t os_event_init(os_event_t event, const char *name)
{
    OS_ERR err;
    ASSERT(event);
    OSFlagCreate(&event->id, (CPU_CHAR *)name, 0, &err);
    return (err == 0 ? E_OK : E_RROR);
}

/**
 * os_event_send
 * @param event
 * @param msg
 * @return
 */
err_t os_event_send(os_event_t event, uint32_t msg)
{
    OS_ERR err;
    ASSERT(event);
    OSFlagPost(&event->id, msg, OS_OPT_POST_FLAG_SET, &err);
    return err == 0 ? E_OK : E_RROR;
}

/**
 *
 * @param event
 * @param set
 * @param timeout
 * @param recved
 * @return
 */
err_t os_event_recv(os_event_t event, uint32_t set, uint32_t timeout, uint32_t *recved)
{
    OS_ERR err;
    ASSERT(event);
    OS_OPT opt = OS_OPT_PEND_FLAG_SET_ANY | OS_OPT_PEND_FLAG_CONSUME | (os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING);
    *recved = OSFlagPend(&event->id, set, TICKS_FROM_MS(timeout), opt, NULL, &err);

    switch (err)
    {
        case OS_ERR_TIMEOUT:
            return E_TIMEOUT;
        case OS_ERR_NONE:
            return E_OK;
        default:
            return E_RROR;
    }
}
