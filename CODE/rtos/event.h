// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_EVENT_H
#define X7PRO_DRIVER_EVENT_H
#include "os_common.h"

struct event
{
    OS_FLAG_GRP id;
};
typedef struct event *os_event_t;


/**
 * os_event_init
 * @param event
 * @param queue_size
 * @return
 */
err_t os_event_init(os_event_t event, const char *name);



/**
 * os_event_send
 * @param event
 * @param msg
 * @return
 */
err_t os_event_send(os_event_t event, uint32_t msg);



/**
 *
 * @param event
 * @param set
 * @param timeout
 * @param recved
 * @return
 */
err_t os_event_recv(os_event_t event, uint32_t set, uint32_t timeout, uint32_t *recved);

#endif //X7PRO_DRIVER_EVENT_H
