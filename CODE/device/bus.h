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
    DEV_SPI2,
}device_e;


typedef struct bus_s
{   // bus base info
    bus_type_e busType;
    volatile bus_status_e busStatus;
    uint8_t deviceCount;
    bool isInit;

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


// don't use those
bus_t *DeviceToBus(device_e device);
void Bus_SetInitialVal(bus_t *bus);
Status_t Bus_Driver_Init(bus_t *bus);

// interface func
bool IsBusBusy(bus_t *bus);
void waitBus(bus_t *bus);
#endif //BUS_H
