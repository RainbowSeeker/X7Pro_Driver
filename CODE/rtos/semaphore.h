// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_SEMAPHORE_H
#define X7PRO_DRIVER_SEMAPHORE_H
#include "os_common.h"

typedef osSemaphoreId os_sem_t;


/**
 * os_sem_create
 * @param sem
 * @param millisec
 * @return
 */
static inline os_sem_t os_sem_create(size_t count)
{
    osSemaphoreId sem;
    if (count == 1) {
        vSemaphoreCreateBinary(sem);
        return sem;
    }
    else {
#if (configUSE_COUNTING_SEMAPHORES == 1 )
        return xSemaphoreCreateCounting(count, count);
#else
        return NULL;
#endif
    }
}

static inline err_t os_sem_delete(os_sem_t sem)
{
    return osSemaphoreDelete(sem);
}

/**
 * os_sem_take
 * @param sem
 * @param millisec
 * @return
 */
static inline err_t os_sem_take(os_sem_t sem, size_t millisec)
{
    if (os_interrupt_get_nest())
    {
        long taskWoken = pdFALSE;
        if (xSemaphoreTakeFromISR(sem, &taskWoken) != pdTRUE)
        {
            return E_RROR;
        }
        portEND_SWITCHING_ISR(taskWoken);
    }
    else
        return xSemaphoreTake(sem, TICKS_FROM_MS(millisec)) == pdTRUE ? E_OK : E_RROR;

    return E_OK;
}

static inline err_t os_sem_trytake(os_sem_t sem)
{
    return os_sem_take(sem, 0);
}

/**
 * os_sem_release
 * @param sem
 * @return
 */
static inline err_t os_sem_release(os_sem_t sem)
{
    if (os_interrupt_get_nest())
    {
        long taskWoken = pdFALSE;
        if (xSemaphoreGiveFromISR(sem, &taskWoken) != pdTRUE)
        {
            return E_RROR;
        }
        portEND_SWITCHING_ISR(taskWoken);
    }
    else
        return xSemaphoreGive(sem) == pdTRUE ? E_OK : E_RROR;

    return E_OK;
}

#endif //X7PRO_DRIVER_SEMAPHORE_H
