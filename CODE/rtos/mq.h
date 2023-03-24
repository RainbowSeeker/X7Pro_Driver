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
__STATIC_INLINE os_mq_t os_mq_create(const char *name,
                                   size_t   msg_size,
                                   size_t   max_msgs)
{
    os_mq_t mq = (os_mq_t ) malloc(sizeof(struct messagequeue));
    ASSERT(mq);
    object_init(&mq->parent, Object_Class_MessageQueue, name);
    mq->msg_size = msg_size;
    mq->max_msgs = max_msgs;
    OSQCreate(&mq->qid, (CPU_CHAR *)name, max_msgs, &os_err);
    return os_err == 0 ? mq : NULL;
}

/**
 * os_mq_send
 * @param mq
 * @param buffer
 * @param size
 * @return
 */
__STATIC_INLINE err_t os_mq_send(os_mq_t mq, const void *buffer, size_t size)
{
    ASSERT(mq);
    ASSERT(size <= mq->msg_size);

//    void *buf_to;
//    if (size != mq->msg_size)
//    {
//        buf_to = malloc(size);
//        memcpy(buf_to, buffer, size);
//    }
//    else
//    {
//        buf_to = (void *)buffer;
//    }
    OSQPost(&mq->qid,
            (void *)buffer,
            size,
            OS_OPT_POST_FIFO,
            &os_err);

//    if (size != mq->msg_size) free(buf_to);
    return os_err == 0 ? E_OK : E_RROR;
}


__STATIC_INLINE err_t os_mq_recv(os_mq_t mq, void *buffer, size_t size, uint32_t timeout)
{
    size_t size_g;
    ASSERT(mq);
    void *recv_ptr = OSQPend(&mq->qid,
                                timeout,
                                os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING,
                                &size_g,
                                0,
                                &os_err);

    if (recv_ptr)
    {
        memcpy(buffer, recv_ptr, MIN(size, size_g));
        return E_OK;
    }
    return E_RROR;
}

#endif //X7PRO_DRIVER_MQ_H
