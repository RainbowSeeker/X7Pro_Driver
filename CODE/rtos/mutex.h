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
 *
 * @param mutex
 * @param name
 * @return
 */
err_t os_mutex_init(os_mutex_t mutex, const char *name);

/**
 * os_mutex_create
 * @param name
 * @return
 */
os_mutex_t os_mutex_create(const char *name);


/**
 * os_mutex_detach
 * @param mutex
 */
void os_mutex_detach(os_mutex_t mutex);


/**
 * os_mutex_delete
 * @param mutex
 */
err_t os_mutex_delete(os_mutex_t mutex);


/**
 * os_mutex_take
 * @param mutex
 * @param millisec
 * @return
 */
err_t os_mutex_take(os_mutex_t mutex, size_t millisec);


/**
 * os_mutex_release
 * @param mutex
 */
err_t os_mutex_release(os_mutex_t mutex);


#endif //X7PRO_DRIVER_MUTEX_H
