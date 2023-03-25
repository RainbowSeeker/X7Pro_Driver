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
err_t os_sem_init(os_sem_t sem, const char *name, size_t value);


/**
 * os_sem_create
 * @param name
 * @param value the initial value of semaphore
 * @return
 */
os_sem_t os_sem_create(const char *name, size_t value);


/**
 *
 * @param sem
 * @return
 */
err_t os_sem_detach(os_sem_t sem);


/**
 *
 * @param sem
 * @return
 */
err_t os_sem_delete(os_sem_t sem);


/**
 * os_sem_take
 * @param sem
 * @param millisec
 * @return
 */
err_t os_sem_take(os_sem_t sem, size_t millisec);


/**
 *
 * @param sem
 * @return
 */
err_t os_sem_trytake(os_sem_t sem);


/**
 * os_sem_release
 * @param sem
 * @return
 */
err_t os_sem_release(os_sem_t sem);

#endif //X7PRO_DRIVER_SEMAPHORE_H
