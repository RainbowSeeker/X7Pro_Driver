// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/20.
//

#ifndef X7PRO_DRIVER_DRV_UART_H
#define X7PRO_DRIVER_DRV_UART_H
#include "board_config.h"
#include <stdbool.h>
#include "stm32h7xx.h"
#include "driver/io.h"
#include "driver/dma.h"


#define SERIAL_DEFINE_DMA(_devid, _uartx, _dma, _stream_tx, _stream_rx)         \
static struct serial_device serial ## _devid =                                  \
        {.ops = &_usart_ops,                                                    \
        .config.instance = _uartx,                                      \
        .config.dma.instance = DMA ## _dma,                                     \
        .config.dma.tx_stream = LL_DMA_STREAM_ ## _stream_tx,                   \
        .config.dma.tx_channel = LL_DMAMUX1_REQ_ ## _uartx ## _TX,          \
        .config.dma.rx_stream = LL_DMA_STREAM_ ## _stream_rx,                   \
        .config.dma.rx_channel = LL_DMAMUX1_REQ_ ## _uartx ## _RX,              \
        SERIAL_DEFAULT_CONFIG                                                              \
        };                                                                      \
void _uartx ## _IRQHandler(void)                  \
    {                                                         \
        uart_isr(&serial ## _devid);                                 \
    }


#define SERIAL_DEFINE(_devid, _uartx)         \
static struct serial_device serial ## _devid =                                  \
        {.ops = &_usart_ops,                                                    \
        .config.instance = _uartx,                                      \
        .config.baud_rate =             \
        SERIAL_DEFAULT_CONFIG                                                              \
        };                                                                      \
void _uartx ## _IRQHandler(void)                  \
    {                                                         \
        uart_isr(&serial ## _devid);                                 \
    }

err_t drv_uart_init();

#endif //X7PRO_DRIVER_DRV_UART_H
