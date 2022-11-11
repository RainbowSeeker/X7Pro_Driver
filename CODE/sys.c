//
// Created by 19114 on 2022/10/21.
//

#include "sys.h"
#include "usart.h"
#include <stdarg.h>

void soft_delay(uint32_t time)
{
    for (int timeout = 0; timeout < time; ++timeout);
}
#define DEBUG_TIMEOUT               (30 * 1000)

#if DEBUG_CONFIG
//debug uart消息队列配置
#define PRINT_QUEUE_SIZE            10
#define READ_MSG                    1
#define WRITE_MSG                   2

static osMessageQId printQueue = NULL;

static void DEBUG_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    osMessagePut(printQueue, WRITE_MSG, 0);
}
static void DEBUG_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    osMessagePut(printQueue, READ_MSG, 0);
}
#endif
/**
 * 打印功能初始化, 包含：
 *           1.串口7 + DMA 初始化
 *           2.自定义 发送/接收 完成回调函数的绑定 (你需要在cubemx中打开对应功能)
 *           3.消息队列对 dma 发送进行处理
 */
void Print_Init(void)
{
    MX_UART7_Init();
#if DEBUG_CONFIG
    HAL_UART_RegisterCallback(&DEBUG_UART, HAL_UART_TX_COMPLETE_CB_ID, DEBUG_UART_TxCpltCallback);
    HAL_UART_RegisterCallback(&DEBUG_UART, HAL_UART_RX_COMPLETE_CB_ID, DEBUG_UART_RxCpltCallback);
    osMessageQDef(printQueue, PRINT_QUEUE_SIZE, uint8_t);
    printQueue = osMessageCreate(osMessageQ(printQueue), NULL);
#endif
}
/**
 * @param huart
 * @param buf
 */
void uart_putstr(UART_HandleTypeDef *huart, const void *buf)
{
#if DEBUG_CONFIG
    uint16_t len = strlen(buf);
    if (len > DEBUG_UART_THRESHOLD)
    {
        if (HAL_UART_Transmit_DMA(huart, (uint8_t *)buf, len) == S_OK)
        {
            osEvent event = osMessageGet(printQueue, DEBUG_TIMEOUT);
            if (event.status == osEventMessage && event.value.v == WRITE_MSG)
            {
                while(HAL_UART_GetState(huart) != HAL_UART_STATE_READY);
            }
        }
    }
    else
    {
        HAL_UART_Transmit(huart, (uint8_t *)buf, len, DEBUG_TIMEOUT);
    }

#else
    HAL_UART_Transmit(huart, (uint8_t *)buf, strlen(buf), DEBUG_TIMEOUT);
#endif
}
/**
 *  自定义打印函数 print，使用 DMA 发送
 * @param format
 * @param ...
 */
void print(const void *format,...)
{
    va_list args;
    char buf[256];
    va_start (args, format);
    vsprintf(buf, format, args);
    va_end (args);

    uart_putstr(&DEBUG_UART, buf);
}
/**
 * 自定义打印函数 println，使用 DMA 发送
 * @param format
 * @param ...
 */
void println(const void *format,...)
{
    va_list args;
    char buf[256];
    va_start (args, format);
    vsprintf(buf, format, args);
    va_end (args);

    uart_putstr(&DEBUG_UART, buf);
    uart_putstr(&DEBUG_UART, "\r\n");
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
 * 重定义 printf (GNU中)
 * @param ch
 * @return
 */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&DEBUG_UART, (uint8_t *)&ch, 1, DEBUG_TIMEOUT);
    return ch;
}
/**
 * 重定义 printf (MDK中)
 * @param ch
 * @param f
 * @return
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&DEBUG_UART, (uint8_t *)&ch, 1, DEBUG_TIMEOUT);
    return ch;
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



