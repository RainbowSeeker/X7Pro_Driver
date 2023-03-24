// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_SEMAPHORE_H
#define X7PRO_DRIVER_SEMAPHORE_H
#include "os_common.h"

struct sem
{
    OS_SEM id;
};
typedef struct sem *os_sem_t;


/**
 * os_sem_init
 * @param sem
 * @param name
 * @param value the initial value of semaphore
 * @return
 */
__STATIC_INLINE err_t os_sem_init(os_sem_t sem, const char *name, size_t value)
{
    ASSERT(sem);
    OSSemCreate(&sem->id, (CPU_CHAR *)name, value, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 * os_sem_create
 * @param name
 * @param value the initial value of semaphore
 * @return
 */
__STATIC_INLINE os_sem_t os_sem_create(const char *name, size_t value)
{
    os_sem_t sem = calloc(1, sizeof(struct sem));
    ASSERT(sem);
    OSSemCreate(&sem->id, (CPU_CHAR *)name, value, &os_err);
    return os_err == 0 ? sem : NULL;
}


__STATIC_INLINE err_t os_sem_detach(os_sem_t sem)
{
    ASSERT(sem);
    OSSemDel(&sem->id, OS_OPT_DEL_ALWAYS, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

/**
 *
 * @param sem
 * @return
 */
__STATIC_INLINE err_t os_sem_delete(os_sem_t sem)
{
    ASSERT(sem);
    OSSemDel(&sem->id, OS_OPT_DEL_ALWAYS, &os_err);
    if (os_err == 0)
    {
        free(sem);
        return E_OK;
    }
    return E_RROR;
}

/**
 * os_sem_take
 * @param sem
 * @param millisec
 * @return
 */
__STATIC_INLINE err_t os_sem_take(os_sem_t sem, size_t millisec)
{
    ASSERT(sem);
    OSSemPend(&sem->id, millisec, (os_interrupt_get_nest() > 0 || millisec == 0 )? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING, NULL, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

__STATIC_INLINE err_t os_sem_trytake(os_sem_t sem)
{
    return os_sem_take(sem, 0);
}

/**
 * os_sem_release
 * @param sem
 * @return
 */
__STATIC_INLINE err_t os_sem_release(os_sem_t sem)
{
    ASSERT(sem);
    OSSemPost(&sem->id, OS_OPT_POST_1, &os_err);
    return os_err == 0 ? E_OK : E_RROR;
}

#endif //X7PRO_DRIVER_SEMAPHORE_H
