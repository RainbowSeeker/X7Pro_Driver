// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MQ_H
#define X7PRO_DRIVER_MQ_H
#include "os_common.h"

struct messagequeue
{
    struct object parent;
    osMessageQId qid;
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
static inline os_mq_t os_mq_create(const char *name,
                                   size_t   msg_size,
                                   size_t   max_msgs)
{
    os_mq_t mq = (os_mq_t ) malloc(sizeof(struct messagequeue));

    object_init(&mq->parent, Object_Class_MessageQueue, name);
    mq->msg_size = msg_size;
    mq->max_msgs = max_msgs;
    mq->qid =  xQueueCreate(max_msgs, msg_size);
    return mq;
}

/**
 * os_mq_send
 * @param mq
 * @param buffer
 * @param size
 * @return
 */
static inline err_t os_mq_send(os_mq_t mq, const void *buffer, size_t size)
{
    err_t err = E_OK;
    ASSERT(mq);
    ASSERT(size <= mq->msg_size);

    void *buf_to;
    if (size != mq->msg_size)
    {
        buf_to = malloc(size);
        memcpy(buf_to, buffer, size);
    }
    else
    {
        buf_to = (void *)buffer;
    }

    long taskWoken = pdFALSE;
    if (os_interrupt_get_nest()) {
        if (xQueueSendFromISR(mq->qid, buf_to, &taskWoken) != pdTRUE) {
            err = E_RROR;
        } else{
            portEND_SWITCHING_ISR(taskWoken);
        }
    }
    else {
        if (xQueueSend(mq->qid, buf_to, 0) != pdTRUE) {
            err = E_RROR;
        }
    }
    if (size != mq->msg_size) free(buf_to);
    return err;
}


static inline err_t os_mq_recv(os_mq_t mq, void *buffer, size_t size, uint32_t timeout)
{
    osEvent recv = osMessageGet(mq->qid, timeout);
    switch (recv.status)
    {
        case osEventMessage:
            memcpy(buffer, &recv.value.v, size);
            return E_OK;
        case osEventTimeout:
            return E_TIMEOUT;
        default:
            return E_RROR;
    }
}

#endif //X7PRO_DRIVER_MQ_H
