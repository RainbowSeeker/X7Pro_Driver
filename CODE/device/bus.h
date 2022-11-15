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
#include "io.h"
#include "algo/ring.h"
#include "common.h"
#include "device/dma.h"
#include "board_config.h"
#include "exti.h"

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
    BUS_NULL = 0,
#ifdef USE_SPI1
    BUS_SPI1,
#endif
#ifdef USE_SPI2
    BUS_SPI2,
#endif
#ifdef USE_SPI3
    BUS_SPI3,
#endif
#ifdef USE_SPI4
    BUS_SPI4,
#endif
#ifdef USE_SPI5
    BUS_SPI5,
#endif
#ifdef USE_SPI6
    BUS_SPI6,
#endif
    BUS_SPICOUNT,
    BUS_I2C1,
    BUS_ALLCOUNT,
}bus_e;

#define SPI_NUM         (BUS_SPICOUNT - 1)

typedef bus_status_e (* segment_callback)(uint32_t arg);
typedef struct segment_s
{
    union {
        struct {
            // Transmit buffer
            uint8_t *pTxData;
            // Receive buffer, or in the case of the final segment to
            uint8_t *pRxData;
        } buffers;
        struct {
            // Link to the device associated with the next transfer
            const struct device_s *dev;
            // Segments to process in the next transfer.
            volatile struct segment_s *segment;
        } link;
    } u;
    int len;
    bool negateCS; // Should CS be negated at the end of this segment
    segment_callback callback;
}segment_t;

typedef struct bus_s
{   // bus base info
    bus_type_e busType;
    union
    {
        // For those devices that need spi
        struct  spiBus_s
        {
            SPI_TypeDef *instance;
            uint16_t speed;
            bool leadingEdge;
        } spi;
        // For those devices that need i2c
    }busType_u;
    // for DMA initialization

    bool enDMA;
    uint8_t deviceCount;
    dma_t *dmaTx;
    dma_t *dmaRx;

    LL_DMA_InitTypeDef *initTx;
    LL_DMA_InitTypeDef *initRx;

    volatile struct segment_s *volatile curSegment;
    bool initSegment;
}bus_t;

// External device has an associated bus and bus dependent address
typedef struct device_s
{
    uint8_t  deviceID;
    char  *name;
    bus_t *bus;
    union {
        struct spiDev_s {
            uint16_t speed;
            io_t csPin;
            bool leadingEdge;
        } spi;
        struct i2cDev_s {
            uint8_t address;
        } i2c;
    } busType_u;

    LL_DMA_InitTypeDef  initTx;
    LL_DMA_InitTypeDef  initRx;

    // Support disabling DMA on a per device basis
    bool useDMA;
    // Connected devices on the same bus may support different speeds
    uint32_t callbackArg;

    const io_t          *extiPin;
    exti_callback_rec_t exti;
}device_t;


#define CACHE_LINE_SIZE 32
#define CACHE_LINE_MASK (CACHE_LINE_SIZE - 1)

#define IDX_BY_BUS(__X__)        ((__X__) - 1)

void Bus_DeviceRegister(const device_t *dev);
bool Bus_WriteRegisterStart(const device_t *dev, uint8_t reg, uint8_t data);
bool Bus_RawWriteRegister(const device_t *dev, uint8_t reg, uint8_t data);
bool Bus_RawWriteRegisterStart(const device_t *dev, uint8_t reg, uint8_t data);
bool Bus_RawReadRegisterBuffer(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
bool Bus_RawReadRegisterBufferStart(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
bool Bus_ReadRegisterBufferStart(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
bool Bus_Busy(const device_t *dev, bool *error);
#endif //BUS_H
