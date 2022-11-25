// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/11.
//

#include <stdarg.h>
#include "log.h"
#include "stdint.h"
#include "stdio.h"
#include "sys.h"
#include "stm32h7xx_hal.h"

void Log_Info(const void *format,...)
{
    va_list args;
    char buf[MAX_LOG_SIZE];
    va_start(args, format);
    vsprintf(buf, format, args);
    va_end(args);

    print("\r\n<<LOG_INFO %5.2fs>> %s\r\n", (float )HAL_GetTick() * 1e-3, buf);
}

void Log_Error(const void *format,...)
{
    va_list args;
    char buf[MAX_LOG_SIZE];
    va_start(args, format);
    vsprintf(buf, format, args);
    va_end(args);

    print("\r\n<<LOG_ERROR%5.2fs>> %s\r\n", (float )HAL_GetTick() * 1e-3, buf);
}
