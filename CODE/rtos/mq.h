// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MQ_H
#define X7PRO_DRIVER_MQ_H
#include "os_common.h"
#include "algo/math/maths.h"

struct messagequeue
{
    struct object parent;
    OS_Q   qid;
    size_t msg_size;
    size_t max_msgs;
};
typedef struct messagequeue *os_mq_t;


/**
 * This function will create a message queue object from system resource
 *
 * @param name the name of message queue
 * @param msg_size the size of message
 * @param max_msgs the maximum number of message in queue
 * @return the created message queue, NULL on error happen
 */
os_mq_t os_mq_create(const char *name,
                     size_t   msg_size,
                     size_t   max_msgs);


/**
 * os_mq_send
 * @param mq
 * @param buffer
 * @param size
 * @return
 */
err_t os_mq_send(os_mq_t mq, const void *buffer, size_t size);


/**
 *
 * @param mq
 * @param buffer
 * @param size
 * @param timeout
 * @return
 */
err_t os_mq_recv(os_mq_t mq, void *buffer, size_t size, uint32_t timeout);
#endif //X7PRO_DRIVER_MQ_H
