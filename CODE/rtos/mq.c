// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "mq.h"

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
                     size_t   max_msgs)
{
    OS_ERR err;
    os_mq_t mq = (os_mq_t ) malloc(sizeof(struct messagequeue));
    ASSERT(mq);
    object_init(&mq->parent, Object_Class_MessageQueue, name);
    mq->msg_size = msg_size;
    mq->max_msgs = max_msgs;
    OSQCreate(&mq->qid, (CPU_CHAR *)name, max_msgs, &err);
    return err == 0 ? mq : NULL;
}

/**
 * os_mq_send
 * @param mq
 * @param buffer
 * @param size
 * @return
 */
err_t os_mq_send(os_mq_t mq, const void *buffer, size_t size)
{
    OS_ERR err;
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
            &err);

//    if (size != mq->msg_size) free(buf_to);
    return err == 0 ? E_OK : E_RROR;
}


/**
 *
 * @param mq
 * @param buffer
 * @param size
 * @param timeout
 * @return
 */
err_t os_mq_recv(os_mq_t mq, void *buffer, size_t size, uint32_t timeout)
{
    OS_ERR err;
    size_t size_g;
    ASSERT(mq);
    void *recv_ptr = OSQPend(&mq->qid,
                             timeout,
                             os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING,
                             &size_g,
                             0,
                             &err);

    if (recv_ptr)
    {
        memcpy(buffer, recv_ptr, MIN(size, size_g));
        return E_OK;
    }
    return E_RROR;
}
