// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/20.
//

#ifndef X7PRO_DRIVER_UART_H
#define X7PRO_DRIVER_UART_H
#include "board_config.h"
#include <stdbool.h>
#include "stm32h7xx.h"
#include "io.h"
#include "dma.h"
#include "algo/ring.h"

#define UART_NUM                    (UART_COUNT - 1)
#define UART_COMMON_CONFIG
#define UART_TX_BUF_SIZE            256
#define UART_RX_BUF_SIZE            64

typedef enum {
    UART_NULL = 0,
#ifdef USE_UART1
    UART_1,
#endif
#ifdef USE_UART2
    UART_2,
#endif
#ifdef USE_UART3
    UART_3,
#endif
#ifdef USE_UART4
    UART_4,
#endif
#ifdef USE_UART5
    UART_5,
#endif
#ifdef USE_UART6
    UART_6,
#endif
#ifdef USE_UART7
    UART_7,
#endif
#ifdef USE_UART8
    UART_8,
#endif
    UART_COUNT,
} uart_device_e;

typedef enum
{
    UART_TX = UART_MODE_RX,
    UART_RX = UART_MODE_TX,
    UART_TXRX = UART_MODE_TX_RX,
}uart_mode_e;

typedef void (*uart_receive_callback)(uint8_t data, uint32_t arg);   // used by serial drivers to return frames to app

typedef struct
{
    io_t txPin;
    uint32_t txAF;
    io_t rxPin;
    uint32_t rxAF;
    uint32_t baudRate;
//    uint32_t wordLength;
//    uint32_t stopBits;
//    uint32_t parity;
//    uint32_t mode;
    uint32_t hwFlowCtl;
//    uint32_t oneBitSampling;
    bool useDMA;
}uart_hwconfig_t;



typedef struct
{
    uart_device_e uartID;
    uart_mode_e uartMode;

    UART_HandleTypeDef huart;
    dma_t *dmaRx;
    dma_t *dmaTx;
    DMA_HandleTypeDef rxDMAHandle;
    DMA_HandleTypeDef txDMAHandle;
    bool useDMA;

//    osMutexId lock;

    uint8_t *txBuffer;
    uint16_t txBufferTail;
    uint16_t txBufferHead;
    uint16_t txBufferSize;

    uint8_t *rxBuffer;
    uint16_t rxBufferTail;
    uint16_t rxBufferHead;
    uint16_t rxBufferSize;

    uint32_t rxDMAPos;
    uart_receive_callback rxCallback;
    uint32_t callbackParam;
    bool txDMAEmpty;
}uart_t;

void UART_BspInit();


uart_t * Uart_Init(uart_device_e uartDevice, uart_receive_callback rxCallback);
void Uart_Write(uart_t *uart, uint8_t *str, uint16_t len);
uint8_t Uart_ReadByte(uart_t *uart);
uint32_t Uart_TotalRxBytesWaiting(uart_t *uart);
uint32_t Uart_TotalTxBytesFree(uart_t *uart);
#endif //X7PRO_DRIVER_UART_H
