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
#define printf          print
#define UNUSED(x)       ((void)(x))
#define DEBUG_UART_THRESHOLD    10

//--------------assert------------------------
#define ALARM_FREQ      0x00afffffu
#define    __str(x)     #x
#define    __xstr(x)    __str(x)

#define assert(expr) ((expr) ? (void)0U : assert_failed("Assertion: \"" #expr \
                    "\" failed, file " __xstr(__FILE__) \
                    ", line " __xstr(__LINE__) "\n"))

#define TickCount(__FUNC__)     { \
                                TickStart();\
                                __FUNC__;   \
                                print("Function \"%s\" cost %3.3f ms.\r\n", __xstr(__FUNC__), (float)TickEnd() / 1000);\
                                }


void soft_delay(uint32_t time);
int print(const void *format,...);
int println(const void *format,...);
void assert_failed(void *string);
uint32_t Sys_GetTickUs(void);
void Sys_DelayUs(uint32_t Delay);
void TickStart(void);
uint32_t TickEnd(void);
#endif //STM32H743IIT6_SYS_H
