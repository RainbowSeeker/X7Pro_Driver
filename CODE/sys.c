//
// Created by 19114 on 2022/10/21.
//

#include "sys.h"
#include "usart.h"


void soft_delay(uint32_t time)
{
    for (int timeout = 0; timeout < time; ++timeout);
}


//标准库需要的支持函数
struct __FILE
{
    int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}



/**
 * 断言错误处理
 * @param string
 */
void assert_failed(void *string)
{
    __disable_irq();
    while (1)
    {
        print("%s", string);
        soft_delay(ALARM_FREQ); //soft delay
    }
}


/**
 * 返回当前滴答时间
 * @return now tick/us
 */
uint32_t Sys_GetTickUs(void)
{
#include "stm32h7xx_hal.h"
    extern TIM_HandleTypeDef htim1;
    return HAL_GetTick() * 1000 + htim1.Instance->CNT * 1000 / htim1.Instance->ARR;

}
void Sys_DelayUs(uint32_t Delay)
{
    uint32_t tickstart = Sys_GetTickUs();
    uint32_t wait = Delay;

    while ((Sys_GetTickUs() - tickstart) < wait)
    {
    }
}

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



