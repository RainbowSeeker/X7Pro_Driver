// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "semaphore.h"

/**
 * os_sem_init
 * @param sem
 * @param name
 * @param value the initial value of semaphore
 * @return
 */
err_t os_sem_init(os_sem_t sem, const char *name, size_t value)
{
    OS_ERR err;
    ASSERT(sem);
    OSSemCreate(&sem->id, (CPU_CHAR *)name, value, &err);
    return err == 0 ? E_OK : E_RROR;
}

/**
 * os_sem_create
 * @param name
 * @param value the initial value of semaphore
 * @return
 */
os_sem_t os_sem_create(const char *name, size_t value)
{
    OS_ERR err;
    os_sem_t sem = calloc(1, sizeof(struct sem));
    ASSERT(sem);
    OSSemCreate(&sem->id, (CPU_CHAR *)name, value, &err);
    return err == 0 ? sem : NULL;
}


/**
 *
 * @param sem
 * @return
 */
err_t os_sem_detach(os_sem_t sem)
{
    OS_ERR err;
    ASSERT(sem);
    OSSemDel(&sem->id, OS_OPT_DEL_ALWAYS, &err);
    return err == 0 ? E_OK : E_RROR;
}

/**
 *
 * @param sem
 * @return
 */
err_t os_sem_delete(os_sem_t sem)
{
    OS_ERR err;
    ASSERT(sem);
    OSSemDel(&sem->id, OS_OPT_DEL_ALWAYS, &err);
    if (err == 0)
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
err_t os_sem_take(os_sem_t sem, size_t millisec)
{
    OS_ERR err;
    ASSERT(sem);
    OSSemPend(&sem->id, millisec, (os_interrupt_get_nest() > 0 || millisec == 0 )? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING, NULL, &err);
    return err == 0 ? E_OK : E_RROR;
}

/**
 *
 * @param sem
 * @return
 */
err_t os_sem_trytake(os_sem_t sem)
{
    return os_sem_take(sem, 0);
}

/**
 * os_sem_release
 * @param sem
 * @return
 */
err_t os_sem_release(os_sem_t sem)
{
    OS_ERR err;
    ASSERT(sem);
    OSSemPost(&sem->id, OS_OPT_POST_1, &err);
    return err == 0 ? E_OK : E_RROR;
}
