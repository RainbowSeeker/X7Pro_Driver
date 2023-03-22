// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/20.
//

#ifndef X7PRO_DRIVER_DRV_UART_H
#define X7PRO_DRIVER_DRV_UART_H

#include "hal/dma/dma.h"
#include "nvic.h"
#include "hal/serial/serial.h"
#include "stm32h7xx_ll_usart.h"
#include "drv_dma.h"

#define UART1   USART1
#define UART2   USART2
#define UART3   USART3
#define UART6   USART6

#define UART1_IRQHandler   USART1_IRQHandler
#define UART2_IRQHandler   USART2_IRQHandler
#define UART3_IRQHandler   USART3_IRQHandler
#define UART6_IRQHandler   USART6_IRQHandler

enum {
    UART1_IRQn = USART1_IRQn,
    UART2_IRQn = USART2_IRQn,
    UART3_IRQn = USART3_IRQn,
    UART6_IRQn = USART6_IRQn,
};

#define SERIAL_DEFINE(_devid, _uartx, _baudrate) \
static struct stm32_uart uart ## _uartx = {  \
.instance = UART ## _uartx,                  \
.irq = UART ## _uartx ##_IRQn,                  \
};                                  \
static struct serial_device serial ## _devid =                                  \
        {                                        \
            .ops = &_usart_ops,                                                    \
            _baudrate,                            \
            DATA_BITS_8,     /* 8 databits */     \
            STOP_BITS_1,     /* 1 stopbit */      \
            PARITY_NONE,     /* No parity  */     \
            BIT_ORDER_LSB,   /* LSB first sent */ \
            NRZ_NORMAL,      /* Normal mode */    \
            SERIAL_RB_BUFSZ, /* Buffer size */    \
            0                                     \
        };                                                                      \
void UART ## _uartx ## _IRQHandler(void)                  \
    {                                            \
        os_interrupt_enter();\
        uart_isr(&serial ## _devid);             \
        os_interrupt_leave();\
    }

err_t drv_uart_init();

#endif //X7PRO_DRIVER_DRV_UART_H
