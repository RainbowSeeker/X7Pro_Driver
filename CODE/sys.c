//
// Created by 19114 on 2022/10/21.
//

#include "sys.h"
#include "usart.h"


volatile static uint32_t usTick = 0;
/**
 * 计时器开始计时
 */
void TickStart(void)
{
    usTick = Sys_GetTickUs();
}
/**
 * 计时器结束计时
 */
uint32_t TickEnd(void)
{
    return (Sys_GetTickUs() - usTick);
}



