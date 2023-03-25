// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "mutex.h"


/**
 *
 * @param mutex
 * @param name
 * @return
 */
err_t os_mutex_init(os_mutex_t mutex, const char *name)
{
    OS_ERR err;
    ASSERT(mutex);
    OSMutexCreate(&mutex->id, (CPU_CHAR *)name, &err);
    return err == 0 ? E_OK : E_NOMEM;
}

/**
 * os_mutex_create
 * @param name
 * @return
 */
os_mutex_t os_mutex_create(const char *name)
{
    OS_ERR err;
    os_mutex_t mutex = calloc(1, sizeof(struct mutex));
    ASSERT(mutex);
    OSMutexCreate(&mutex->id, (CPU_CHAR *)name, &err);
    return err == 0 ? mutex : NULL;
}

/**
 * os_mutex_detach
 * @param mutex
 */
void os_mutex_detach(os_mutex_t mutex)
{
    OS_ERR err;
    ASSERT(mutex);
    //mutex del must be done in thread.
    OSMutexDel(&mutex->id, OS_OPT_DEL_ALWAYS, &err);
    ASSERT(err == 0);
}

/**
 * os_mutex_delete
 * @param mutex
 */
err_t os_mutex_delete(os_mutex_t mutex)
{
    OS_ERR err;
    ASSERT(mutex);
    //mutex del must be done in thread.
    OSMutexDel(&mutex->id, OS_OPT_DEL_ALWAYS, &err);
    if (err == 0)
    {
        free(mutex);
        return E_OK;
    }
    return E_RROR;
}

/**
 * os_mutex_take
 * @param mutex
 * @param millisec
 * @return
 */
err_t os_mutex_take(os_mutex_t mutex, size_t millisec)
{
    OS_ERR err;
    ASSERT(mutex);
    OSMutexPend(&mutex->id,
                millisec,
                os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING,
                NULL,
                &err);
    return err == 0 ? E_OK : E_RROR;
}

/**
 * os_mutex_release
 * @param mutex
 */
err_t os_mutex_release(os_mutex_t mutex)
{
    OS_ERR err;
    ASSERT(mutex);
    OSMutexPost(&mutex->id, OS_OPT_POST_NONE, &err);
    return err == 0 ? E_OK : E_RROR;
}