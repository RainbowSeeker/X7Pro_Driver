//
// Created by 19114 on 2022/10/21.
//

#ifndef STM32H743IIT6_SYS_H
#define STM32H743IIT6_SYS_H
#include "stdio.h"
#include "stdint.h"
#include "board_config.h"


//-------------sys config---------------------
#define delay_ms        HAL_Delay
#define delay_us        Sys_DelayUs
//#define printf          print
#define DEBUG_UART_THRESHOLD    10



#define TickCount(__FUNC__)     { \
                                TickStart();\
                                __FUNC__;   \
                                printf("Function \"%s\" cost %3.3f ms.", #__FUNC__, (float)TickEnd() / 1000);\
                                }


uint32_t Sys_GetTickUs(void);
void Sys_DelayUs(uint32_t Delay);
void TickStart(void);
uint32_t TickEnd(void);
#endif //STM32H743IIT6_SYS_H
