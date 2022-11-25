// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_ERROR_H
#define X7PRO_DRIVER_ERROR_H

typedef enum
{
    E_OK = 0,         /**< There is no error */
    E_RROR = 1,       /**< A generic error happens */
    E_TIMEOUT = 2,    /**< Timed out */
    E_FULL = 3,       /**< The resource is full */
    E_EMPTY = 4,      /**< The resource is empty */
    E_NOMEM = 5,      /**< No memory */
    E_NOSYS = 6,      /**< No system */
    E_BUSY = 7,       /**< Busy */
    E_IO = 8,         /**< IO error */
    E_INTR = 9,       /**< Interrupted system call */
    E_INVAL = 10,     /**< Invalid argument */
    E_NOTHANDLE = 11, /**< Not handled */
}err_status_e;

#define ERROR_TRY(__exp)           \
    do {                         \
        err_status_e err = (__exp); \
        if (err != E_OK) {    \
            return err;          \
        }                        \
    } while (false)

#endif //X7PRO_DRIVER_ERROR_H
