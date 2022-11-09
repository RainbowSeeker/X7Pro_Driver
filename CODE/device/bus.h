// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#ifndef BUS_H
#define BUS_H

#include <stdbool.h>
#include <stdio.h>
#include "stm32h7xx_ll_dma.h"
#include "board_config.h"
#include "ioconfig.h"
#include "algo/ring.h"

typedef enum
{
    BUS_TYPE_NONE = 0,
    BUS_TYPE_SPI,
    BUS_TYPE_I2C,
}bus_type_e;

typedef enum
{
    BUS_READY = 0,
    BUS_BUSY,
    BUS_ABORT,
}bus_status_e;

typedef enum
{
    DEV_SPI1 = (int)SPI1,
    DEV_SPI2 = (int)SPI2,
    DEV_SPI3 = (int)SPI3,
    DEV_SPI4 = (int)SPI4,
}device_e;


typedef struct bus_s
{   // bus base info
    bus_type_e busType;
    volatile bus_status_e busStatus;
    uint8_t deviceCount;
    bool isInit;

    osMutexId lock;
    union
    {
        // For those devices that need spi
        struct
        {
            SPI_TypeDef *instance;
            uint16_t speed;
        } spi;
        // For those devices that need i2c
    }busType_u;
    // for DMA initialization

    bool enDMA;
    DMA_TypeDef *dmaTx;
    DMA_TypeDef *dmaRx;
    uint32_t streamTx;
    uint32_t streamRx;
    LL_DMA_InitTypeDef initTxDMA;
    LL_DMA_InitTypeDef initRxDMA;

    ring_t ring;
    segment_t *curSegment;
}bus_t;

#define IS_DTCM(p) (((uint32_t)p & 0xfffe0000) == 0x20000000)
#define DMA_DATA_ZERO_INIT          __attribute__ ((section(".dmaram_bss"), aligned(32)))
#define DMA_DATA                    __attribute__ ((section(".dmaram_data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

extern uint8_t _dmaram_start__;
extern uint8_t _dmaram_end__;

// interface func
bus_t * Register_Bus(device_e device);
bool IsBusBusy(bus_t *bus);
void waitBus(bus_t *bus);
#endif //BUS_H
