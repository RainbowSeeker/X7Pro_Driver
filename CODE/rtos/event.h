// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_EVENT_H
#define X7PRO_DRIVER_EVENT_H
#include "os_common.h"

typedef osMessageQId os_event_t;


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

#endif //X7PRO_DRIVER_EVENT_H
