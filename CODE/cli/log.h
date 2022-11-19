// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/11.
//

#ifndef X7PRO_DRIVER_LOG_H
#define X7PRO_DRIVER_LOG_H

#define MAX_LOG_SIZE        128

#define LOG_INFO            Log_Info
#define LOG_ERROR           Log_Error

void Log_Info(const void *format,...);
void Log_Error(const void *format,...);
#endif //X7PRO_DRIVER_LOG_H
