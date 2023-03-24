// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MUTEX_H
#define X7PRO_DRIVER_MUTEX_H
#include "os_common.h"

struct mutex
{
    OS_MUTEX id;
};
typedef struct mutex *os_mutex_t;


/**
 * os_mutex_init
 * @param mutex
 * @return
 */
__STATIC_INLINE err_t os_mutex_init(os_mutex_t mutex, const char *name)
{
    ASSERT(mutex);
    OSMutexCreate(&mutex->id, (CPU_CHAR *)name, &os_err);
    return os_err == 0 ? E_OK : E_NOMEM;
}

/**
 * os_mutex_create
 * @param name
 * @return
 */
__STATIC_INLINE os_mutex_t os_mutex_create(const char *name)
{
    os_mutex_t mutex = calloc(1, sizeof(struct mutex));
    ASSERT(mutex);
    OSMutexCreate(&mutex->id, (CPU_CHAR *)name, &os_err);
    return os_err == 0 ? mutex : NULL;
}

/**
 * os_mutex_detach
 * @param mutex
 */
__STATIC_INLINE void os_mutex_detach(os_mutex_t mutex)
{
    ASSERT(mutex);
    //mutex del must be done in thread.
    OSMutexDel(&mutex->id, OS_OPT_DEL_ALWAYS, &os_err);
    ASSERT(os_err == 0);
}

/**
 * os_mutex_delete
 * @param mutex
 */
__STATIC_INLINE err_t os_mutex_delete(os_mutex_t mutex)
{
    ASSERT(mutex);
    //mutex del must be done in thread.
    OSMutexDel(&mutex->id, OS_OPT_DEL_ALWAYS, &os_err);
    if (os_err == 0)
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
__STATIC_INLINE err_t os_mutex_take(os_mutex_t mutex, size_t millisec)
{
    ASSERT(mutex);
    OSMutexPend(&mutex->id,
                millisec,
                os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING,
                NULL,
                &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 * os_mutex_release
 * @param mutex
 */
__STATIC_INLINE err_t os_mutex_release(os_mutex_t mutex)
{
    ASSERT(mutex);
    OSMutexPost(&mutex->id, OS_OPT_POST_NONE, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

#endif //X7PRO_DRIVER_MUTEX_H
