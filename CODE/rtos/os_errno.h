// Copyright (c) 2023 By RainbowSeeker.

//
// Created by 19114 on 2023/3/17.
//

#ifndef X7PRO_DRIVER_OS_ERRNO_H
#define X7PRO_DRIVER_OS_ERRNO_H
#include <common_def.h>
#include "os.h"


extern OS_ERR os_err;

err_t os_get_errno(void);
void os_set_errno(err_t error);
int *_os_errno(void);
#endif //X7PRO_DRIVER_OS_ERRNO_H
