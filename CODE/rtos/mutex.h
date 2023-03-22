// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MUTEX_H
#define X7PRO_DRIVER_MUTEX_H
#include "os_common.h"
typedef OS_MUTEX *mutex_t;


/**
 * mutex_init
 * @param mutex
 * @return
 */
static inline err_t mutex_init(mutex_t *mutex)
{
    *mutex = calloc(1, sizeof(OS_MUTEX));
    OSMutexCreate(*mutex, NULL, &os_err);
//    OSMutexPost(*mutex, OS_OPT_POST_NONE, &os_err);
    return os_err == 0 ? E_OK : E_NOMEM;
}

/**
 * mutex_detach
 * @param mutex
 */
static inline void mutex_detach(mutex_t mutex)
{
    //mutex del must be done in thread.
    OSMutexDel(mutex, OS_OPT_DEL_ALWAYS, &os_err);
    ASSERT(os_err == 0);
    free(mutex);
}

/**
 * mutex_delete
 * @param mutex
 */
static inline err_t mutex_delete(mutex_t mutex)
{
    //mutex del must be done in thread.
    OSMutexDel(mutex, OS_OPT_DEL_ALWAYS, &os_err);
    free(mutex);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 * mutex_take
 * @param mutex
 * @param millisec
 * @return
 */
static inline err_t mutex_take(mutex_t mutex, size_t millisec)
{
    OSMutexPend(mutex, millisec, os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING, NULL, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 * mutex_release
 * @param mutex
 */
static inline err_t mutex_release(mutex_t mutex)
{
    OSMutexPost(mutex, OS_OPT_POST_NONE, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

#endif //X7PRO_DRIVER_MUTEX_H
