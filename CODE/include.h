//
// Created by 19114 on 2022/10/11.
//

#ifndef STM32H743IIT6_INCLUDE_H
#define STM32H743IIT6_INCLUDE_H

//-------driver 头文件 ----------
#include "sdmmc.h"
#include "usart.h"
#include "gpio.h"
#include  <stm32h7xx_hal.h>
#include  <stdio.h>
#include "string.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"



////-------user 自定义头文件 -------
#include "common.h"
#include "sys.h"
#include "com.h"
#include "task.h"
#include "ledbeep.h"
#include "sdop.h"


//-------uCosIII 头文件 ---------
#if USE_UCOS
#include  <cpu.h>
#include  <lib_mem.h>
#include  <os.h>
#include  "os_app_hooks.h"
#include  "app_cfg.h"
#endif




#endif //STM32H743IIT6_INCLUDE_H
