// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/1.
//

#ifndef X7PRO_DRIVER_COMMON_H
#define X7PRO_DRIVER_COMMON_H

#include "common_def.h"
#include "cmsis_os.h"
#include "system/os_map.h"
#include "system/cache.h"
#include "utils/list.h"
#include "module_common.h"
#include "finsh_api.h"

/* HIL simulation */
// #define FMT_USING_HIL
/* SIH simulation */
//#define FMT_USING_SIH

/* MLog */
#define MLOG_BUFFER_SIZE         (80 * 1024)
#define MLOG_SECTOR_SIZE         (4096)
#define MLOG_MAX_SECTOR_TO_WRITE 5

/* ULog */
#define FMT_USING_ULOG
#ifdef FMT_USING_ULOG
// #define ENABLE_ULOG_FS_BACKEND
#define ENABLE_ULOG_CONSOLE_BACKEND
#endif
#endif //X7PRO_DRIVER_COMMON_H
