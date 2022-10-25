//
// Created by 19114 on 2022/10/21.
//

#ifndef STM32H743IIT6_SYS_H
#define STM32H743IIT6_SYS_H
#include "stdio.h"

//--------debug uart config-------------------
#define DEBUG_UART      (huart7)
#define DEBUG_USE_DMA   1
#define DEBUG_CONFIG    (DEBUG_USE_DMA && USE_FREERTOS)

//--------------assert------------------------
#define ALARM_FREQ          0x004fffff
#define    __str(x)     #x
#define    __xstr(x)    __str(x)

#define assert(expr) ((expr) ? (void)0U : assert_failed("Assertion: \"" #expr \
                    "\" failed, file " __xstr(__FILE__) \
                    ", line " __xstr(__LINE__) "\n"))



void Print_Init(void);
void print(const void *format,...);
void println(const void *format,...);
void assert_failed(void *string);
uint32_t Sys_GetTickUs(void);
#endif //STM32H743IIT6_SYS_H
