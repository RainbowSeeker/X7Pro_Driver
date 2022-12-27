// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/15.
//

#ifndef X7PRO_DRIVER_LOGGER_H
#define X7PRO_DRIVER_LOGGER_H
#include "mlog.h"

err_t logger_start_mlog(char* path);
void logger_stop_mlog(void);
#endif //X7PRO_DRIVER_LOGGER_H
