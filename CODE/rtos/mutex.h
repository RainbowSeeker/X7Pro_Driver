// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MUTEX_H
#define X7PRO_DRIVER_MUTEX_H
#include "os_common.h"
typedef osMutexId mutex_t;


/**
 * mutex_init
 * @param mutex
 * @return
 */
static inline err_t mutex_init(mutex_t *mutex)
{
    *mutex = xSemaphoreCreateMutex();
    return (*mutex != NULL ? E_OK : E_NOMEM);
}

/**
 * mutex_detach
 * @param mutex
 */
static inline void mutex_detach(mutex_t mutex)
{
    //mutex del must be done in thread.
    ASSERT(osMutexDelete(mutex) == 0);
}

/**
 * mutex_delete
 * @param mutex
 */
static inline err_t mutex_delete(mutex_t mutex)
{
    //mutex del must be done in thread.
    return osMutexDelete(mutex);
}

/**
 * mutex_take
 * @param mutex
 * @param millisec
 * @return
 */
static inline err_t mutex_take(mutex_t mutex, size_t millisec)
{
    if (os_interrupt_get_nest())
    {
        long taskWoken = pdFALSE;
        if (xSemaphoreTakeFromISR(mutex, &taskWoken) != pdTRUE)
        {
            return E_RROR;
        }
        portEND_SWITCHING_ISR(taskWoken);
    }
    else
        return xSemaphoreTake(mutex, TICKS_FROM_MS(millisec)) == pdTRUE ? E_OK : E_RROR;

    return E_OK;
}

/**
 * mutex_release
 * @param mutex
 */
static inline err_t mutex_release(mutex_t mutex)
{
    if (os_interrupt_get_nest())
    {
        long taskWoken = pdFALSE;
        if (xSemaphoreGiveFromISR(mutex, &taskWoken) != pdTRUE)
        {
            return E_RROR;
        }
        portEND_SWITCHING_ISR(taskWoken);
    }
    else
        return xSemaphoreGive(mutex) == pdTRUE ? E_OK : E_RROR;

    return E_OK;
}

#endif //X7PRO_DRIVER_MUTEX_H
