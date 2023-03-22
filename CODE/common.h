// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/1.
//

#ifndef X7PRO_DRIVER_COMMON_H
#define X7PRO_DRIVER_COMMON_H

#include "common_def.h"
#include "drivers/cache.h"
#include "utils/list.h"
#include "module_common.h"
#include "finsh_api.h"
#include <rtconfig.h>
#include "stm32h7xx_hal.h"

/* rtos include */
#include "rtos/semaphore.h"
#include "rtos/thread.h"
#include "rtos/device.h"
#include "rtos/timer.h"
#include "rtos/mutex.h"
#include "rtos/event.h"
#include "rtos/mem.h"
#include "rtos/mq.h"
#include "rtos/completion/completion.h"

/* HIL simulation */
// #define FMT_USING_HIL
/* SIH simulation */
//#define FMT_USING_SIH

/* Mavlink */
#define FMT_USING_MAVLINK_V2

/* MLog */
#define MLOG_BUFFER_SIZE         (120 * 1024)
#define MLOG_SECTOR_SIZE         (4096)
#define MLOG_MAX_SECTOR_TO_WRITE 5

/* ULog */
#define FMT_USING_ULOG
#ifdef FMT_USING_ULOG
// #define ENABLE_ULOG_FS_BACKEND
#define ENABLE_ULOG_CONSOLE_BACKEND
#endif
#endif //X7PRO_DRIVER_COMMON_H
