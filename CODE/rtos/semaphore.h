// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_SEMAPHORE_H
#define X7PRO_DRIVER_SEMAPHORE_H
#include "os_common.h"

typedef OS_SEM *os_sem_t;

/**
 * os_sem_create
 * @param sem
 * @param millisec
 * @return
 */
static inline os_sem_t os_sem_create(size_t count)
{
    os_sem_t sem = calloc(1, sizeof(OS_SEM));
    OSSemCreate(sem, NULL, count, &os_err);
    return os_err == 0 ? sem : NULL;
}

static inline err_t os_sem_delete(os_sem_t sem)
{
    OSSemDel(sem, OS_OPT_DEL_ALWAYS, &os_err);
    free(sem);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 * os_sem_take
 * @param sem
 * @param millisec
 * @return
 */
static inline err_t os_sem_take(os_sem_t sem, size_t millisec)
{
    OSSemPend(sem, millisec, os_interrupt_get_nest() > 0 ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING, NULL, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

static inline err_t os_sem_trytake(os_sem_t sem)
{
    OSSemPend(sem, 0, OS_OPT_PEND_NON_BLOCKING, NULL, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 * os_sem_release
 * @param sem
 * @return
 */
static inline err_t os_sem_release(os_sem_t sem)
{
    OSSemPost(sem, OS_OPT_POST_1, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

#endif //X7PRO_DRIVER_SEMAPHORE_H
