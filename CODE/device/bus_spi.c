// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "bus_spi.h"
#include "atomic.h"
#include "algo/math/maths.h"

#include "nvic.h"

static uint8_t spiRegisteredDeviceCount = 0;

static bus_t spiBus[SPI_NUM];

const spi_hw_t spiHardware[SPI_NUM] = {
#ifdef USE_SPI1
        {
                .instance = SPI1,
                .sck = {.port = GPIOG, .pin = GPIO_PIN_11}, .sckAF = GPIO_AF5_SPI1,
                .miso = {.port = GPIOA, .pin = GPIO_PIN_6}, .misoAF = GPIO_AF5_SPI1,
                .mosi = {.port = GPIOD, .pin = GPIO_PIN_7}, .mosiAF = GPIO_AF5_SPI1,
        },
#endif
#ifdef USE_SPI2
        {
                .instance = SPI2,
                .sck = {.port = GPIOI, .pin = GPIO_PIN_1}, .sckAF = GPIO_AF5_SPI2,
                .miso = {.port = GPIOI, .pin = GPIO_PIN_2}, .misoAF = GPIO_AF5_SPI2,
                .mosi = {.port = GPIOI, .pin = GPIO_PIN_3}, .mosiAF = GPIO_AF5_SPI2,
        },
#endif
#ifdef USE_SPI3
        {
                NULL
        },
#endif
#ifdef USE_SPI4
        {
                .instance = SPI4,
                .sck = {.port = GPIOE, .pin = GPIO_PIN_2}, .sckAF = GPIO_AF5_SPI4,
                .miso = {.port = GPIOE, .pin = GPIO_PIN_13}, .misoAF = GPIO_AF5_SPI4,
                .mosi = {.port = GPIOE, .pin = GPIO_PIN_6}, .mosiAF = GPIO_AF5_SPI4,
        },
#endif
#ifdef USE_SPI5
        {
                .instance = SPI4,
                .sck = {.port = GPIOF, .pin = GPIO_PIN_7},
                .miso = {.port = GPIOF, .pin = GPIO_PIN_8},
                .mosi = {.port = GPIOF, .pin = GPIO_PIN_9},
        },
#endif
#ifdef USE_SPI6
        {
            .instance = SPI6,
            .sck = {.port = GPIOG, .pin = GPIO_PIN_13}, .sckAF = GPIO_AF5_SPI6,
            .miso = {.port = GPIOG, .pin = GPIO_PIN_12}, .misoAF = GPIO_AF5_SPI6,
            .mosi = {.port = GPIOA, .pin = GPIO_PIN_7}, .mosiAF = GPIO_AF8_SPI6,
        }
#endif
};


void SPI_SetClkDivisor(const device_t *dev, uint16_t divisor)
{
    ((device_t *)dev)->busType_u.spi.speed = divisor;
}

// Set the clock phase/polarity to be used for accesses by the given device
void SPI_SetClkPhasePolarity(const device_t *dev, bool leadingEdge)
{
    ((device_t *)dev)->busType_u.spi.leadingEdge = leadingEdge;
}

uint16_t SPI_CalculateDivider(uint32_t freq)
{
#ifdef STM32H7
    uint32_t spiClk = 100000000;
#else
#error "Base SPI clock not defined for this architecture"
#endif
    uint16_t divisor = 2;

    spiClk >>= 1;

    for (; (spiClk > freq) && (divisor < 256); divisor <<= 1, spiClk >>= 1);

    return divisor;
}

static uint32_t SPI_DivisorToBRbits(SPI_TypeDef *instance, uint16_t divisor)
{
    UNUSED(instance);

    divisor = constrain(divisor, 2, 256);

#ifdef STM32H7
    const uint32_t baudRatePrescaler[8] = {
            LL_SPI_BAUDRATEPRESCALER_DIV2,
            LL_SPI_BAUDRATEPRESCALER_DIV4,
            LL_SPI_BAUDRATEPRESCALER_DIV8,
            LL_SPI_BAUDRATEPRESCALER_DIV16,
            LL_SPI_BAUDRATEPRESCALER_DIV32,
            LL_SPI_BAUDRATEPRESCALER_DIV64,
            LL_SPI_BAUDRATEPRESCALER_DIV128,
            LL_SPI_BAUDRATEPRESCALER_DIV256,
    };
    int prescalerIndex = ffs(divisor) - 2; // prescaler begins at "/2"

    return baudRatePrescaler[prescalerIndex];
#else
    return (ffs(divisor) - 2) << SPI_CR1_BR_Pos;
#endif
}

bus_e SPI_BusByInstance(SPI_TypeDef *instance)
{
#ifdef USE_SPI1
    if (instance == SPI1)
    {
        return BUS_SPI1;
    }
#endif
#ifdef USE_SPI2
    if (instance == SPI2) {
        return BUS_SPI2;
    }
#endif
#ifdef USE_SPI3
    if (instance == SPI3) {
        return BUS_SPI3;
    }
#endif
#ifdef USE_SPI4
    if (instance == SPI4)
    {
        return BUS_SPI4;
    }
#endif
#ifdef USE_SPI5
    if (instance == SPI5) {
        return BUS_SPI5;
    }
#endif
#ifdef USE_SPI6
    if (instance == SPI6) {
        return BUS_SPI6;
    }
#endif

    return BUS_NULL;
}

SPI_TypeDef *SPI_InstanceByBus(bus_e busE)
{
    switch (busE)
    {
#ifdef USE_SPI1
        case BUS_SPI1:
            return SPI1;
#endif
#ifdef USE_SPI2
            case BUS_SPI2:
                return SPI2;
#endif
#ifdef USE_SPI3
            case BUS_SPI3:
                return SPI3;
#endif
#ifdef USE_SPI4
        case BUS_SPI4:
            return SPI4;
#endif
#ifdef USE_SPI5
            case BUS_SPI5:
                return SPI5;
#endif
#ifdef USE_SPI6
            case BUS_SPI6:
                return SPI6;
#endif
        default:
            return NULL;
    }
}

void SPI_InternalStartDMA(const device_t *dev)
{
    bus_t *bus = dev->bus;

    dma_t *dmaTx = bus->dmaTx;
    dma_t *dmaRx = bus->dmaRx;

    // Use the correct callback argument
    dmaRx->userParam = (uint32_t) dev;

    LL_SPI_SetTransferSize(dev->bus->busType_u.spi.instance, dev->bus->curSegment->len);
    if (dmaTx->dma == BDMA)
    {
        // Clear transfer flags
        BDMA_CLEAR_FLAG(dmaTx, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
        BDMA_CLEAR_FLAG(dmaRx, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);

        BDMA_Channel_TypeDef *streamRegsTx = dmaTx->ref;
        BDMA_Channel_TypeDef *streamRegsRx = dmaRx->ref;

        // Disable streams to enable update
        LL_DMA_WriteReg(streamRegsTx, CCR, 0U);
        LL_DMA_WriteReg(streamRegsRx, CCR, 0U);

        /* Use the Rx interrupt as this occurs once the SPI operation is complete whereas the Tx interrupt
         * occurs earlier when the Tx FIFO is empty, but the SPI operation is still in progress
         */

        LL_EX_BDMA_EnableIT_TC(streamRegsRx);

        // Update streams
        LL_BDMA_Init(dmaTx->dma, dmaTx->stream, (LL_BDMA_InitTypeDef *)bus->initTx);
        LL_BDMA_Init(dmaRx->dma, dmaRx->stream, (LL_BDMA_InitTypeDef *)bus->initRx);


        LL_BDMA_EnableChannel(dmaTx->dma, dmaTx->stream);
        LL_BDMA_EnableChannel(dmaRx->dma, dmaRx->stream);
    }
    else
    {
        // Clear transfer flags
        DMA_CLEAR_FLAG(dmaTx, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
        DMA_CLEAR_FLAG(dmaRx, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);

        DMA_Stream_TypeDef *streamRegsTx = dmaTx->ref;
        DMA_Stream_TypeDef *streamRegsRx = dmaRx->ref;

        // Disable streams to enable update
        LL_DMA_WriteReg(streamRegsTx, CR, 0U);
        LL_DMA_WriteReg(streamRegsRx, CR, 0U);

        /* Use the Rx interrupt as this occurs once the SPI operation is complete whereas the Tx interrupt
         * occurs earlier when the Tx FIFO is empty, but the SPI operation is still in progress
         */

        LL_EX_DMA_EnableIT_TC(streamRegsRx);

        // Update streams
        LL_DMA_Init(dmaTx->dma, dmaTx->stream, bus->initTx);
        LL_DMA_Init(dmaRx->dma, dmaRx->stream, bus->initRx);


        LL_DMA_EnableStream(dmaTx->dma, dmaTx->stream);
        LL_DMA_EnableStream(dmaRx->dma, dmaRx->stream);
    }

    LL_SPI_EnableDMAReq_TX(dev->bus->busType_u.spi.instance);
    LL_SPI_EnableDMAReq_RX(dev->bus->busType_u.spi.instance);
    LL_SPI_Enable(dev->bus->busType_u.spi.instance);
    LL_SPI_StartMasterTransfer(dev->bus->busType_u.spi.instance);

}

static void SPI_InternalInitStream(const device_t *dev, bool preInit)
{
    STATIC_DMA_DATA_AUTO uint8_t dummyTxByte = 0xff;
    STATIC_DMA_DATA_AUTO uint8_t dummyRxByte;

    bus_t *bus = dev->bus;

    segment_t *segment = (segment_t *) bus->curSegment;

    if (preInit)
    {
        // Prepare the init structure for the next segment to reduce inter-segment interval
        segment++;
        if (segment->len == 0)
        {
            // There's no following segment
            return;
        }
    }

    int len = segment->len;

    uint8_t *txData = segment->u.buffers.pTxData;
    LL_DMA_InitTypeDef *initTx = bus->initTx;

    if (txData)
    {
#ifdef __DCACHE_PRESENT
#ifdef STM32H7
        if (txData < &_dmaram_start__ || txData >= &_dmaram_end__)
        {
#else
            // No need to flush DTCM memory
        if (!IS_DTCM(txData)) {
#endif
            // Flush the D cache to ensure the data to be written is in main memory
            SCB_CleanDCache_by_Addr(
                    (uint32_t *) ((uint32_t) txData & ~CACHE_LINE_MASK),
                    (((uint32_t) txData & CACHE_LINE_MASK) + len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
        }
#endif // __DCACHE_PRESENT
        initTx->MemoryOrM2MDstAddress = (uint32_t) txData;
        initTx->MemoryOrM2MDstIncMode = bus->dmaTx->dma == BDMA ? LL_BDMA_MEMORY_INCREMENT : LL_DMA_MEMORY_INCREMENT;
    }
    else
    {
        initTx->MemoryOrM2MDstAddress = (uint32_t) &dummyTxByte;
        initTx->MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
    }
    initTx->NbData = len;

    uint8_t *rxData = segment->u.buffers.pRxData;
    LL_DMA_InitTypeDef *initRx = bus->initRx;

    if (rxData)
    {
        /* Flush the D cache for the start and end of the receive buffer as
         * the cache will be invalidated after the transfer and any valid data
         * just before/after must be in memory at that point
         */
#ifdef __DCACHE_PRESENT
        // No need to flush/invalidate DTCM memory
#ifdef STM32H7
        if (rxData < &_dmaram_start__ || rxData >= &_dmaram_end__)
        {
#else
            // No need to flush DTCM memory
            if (!IS_DTCM(rxData)) {
#endif
            SCB_CleanInvalidateDCache_by_Addr(
                    (uint32_t *) ((uint32_t) rxData & ~CACHE_LINE_MASK),
                    (((uint32_t) rxData & CACHE_LINE_MASK) + len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
        }
#endif // __DCACHE_PRESENT
        initRx->MemoryOrM2MDstAddress = (uint32_t) rxData;
        initRx->MemoryOrM2MDstIncMode = bus->dmaTx->dma == BDMA ? LL_BDMA_MEMORY_INCREMENT : LL_DMA_MEMORY_INCREMENT;
    }
    else
    {
        initRx->MemoryOrM2MDstAddress = (uint32_t) &dummyRxByte;
        initRx->MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
    }
    initRx->NbData = len;
}

// Interrupt handler for SPI receive DMA completion
static void SPI_IrqHandler(const device_t *dev)
{
    bus_t *bus = dev->bus;
    segment_t *nextSegment;

    if (bus->curSegment->callback)
    {
        switch (bus->curSegment->callback(dev->callbackArg))
        {
            case BUS_BUSY:
                // Repeat the last DMA segment
                bus->curSegment--;
                // Reinitialise the cached init values as segment is not progressing
                SPI_InternalInitStream(dev, true);
                break;

            case BUS_ABORT:
                bus->curSegment = (segment_t *) BUS_SPI_FREE;
                return;

            case BUS_READY:
            default:
                // Advance to the next DMA segment
                break;
        }
    }

    // Advance through the segment list
    // OK to discard the volatile qualifier here
    nextSegment = (segment_t *) bus->curSegment + 1;

    if (nextSegment->len == 0)
    {
        // If a following transaction has been linked, start it
        if (nextSegment->u.link.dev)
        {
            const device_t *nextDev = nextSegment->u.link.dev;
            segment_t *nextSegments = (segment_t *) nextSegment->u.link.segment;
            // The end of the segment list has been reached
            bus->curSegment = nextSegments;
            nextSegment->u.link.dev = NULL;
            nextSegment->u.link.segment = NULL;
            SPI_SequenceStart(nextDev);
        }
        else
        {
            // The end of the segment list has been reached, so mark transactions as complete
            bus->curSegment = (segment_t *) BUS_SPI_FREE;
        }
    }
    else
    {
        // Do as much processing as possible before asserting CS to avoid violating minimum high time
        bool negateCS = bus->curSegment->negateCS;

        bus->curSegment = nextSegment;

        // After the completion of the first segment setup the init structure for the subsequent segment
        if (bus->initSegment)
        {
            SPI_InternalInitStream(dev, false);
            bus->initSegment = false;
        }

        if (negateCS)
        {
            // Assert Chip Select - it's costly so only do so if necessary
            IO_Set(dev->busType_u.spi.csPin, IO_LOW);
        }

        // Launch the next transfer
        SPI_InternalStartDMA(dev);

        // Prepare the init structures ready for the next segment to reduce inter-segment time
        SPI_InternalInitStream(dev, true);
    }
}

// Interrupt handler for SPI receive DMA completion
static void SPI_RxIrqHandler(dma_t *descriptor)
{
    const device_t *dev = (const device_t *) descriptor->userParam;

    if (!dev)
    {
        return;
    }

    bus_t *bus = dev->bus;

    if (bus->curSegment->negateCS)
    {
        // Negate Chip Select
        IO_Set(dev->busType_u.spi.csPin, IO_HIGH);
    }

    SPI_InternalStopDMA(dev);

#ifdef __DCACHE_PRESENT
#ifdef STM32H7
    if (bus->curSegment->u.buffers.pRxData &&(bus->curSegment->u.buffers.pRxData < &_dmaram_start__ ||
                                        bus->curSegment->u.buffers.pRxData >= &_dmaram_end__))
    {
#else
        if (bus->curSegment->u.buffers.rxData) {
#endif
        // Invalidate the D cache covering the area into which data has been read
        SCB_InvalidateDCache_by_Addr(
                (uint32_t *) ((uint32_t) bus->curSegment->u.buffers.pRxData & ~CACHE_LINE_MASK),
                (((uint32_t) bus->curSegment->u.buffers.pRxData & CACHE_LINE_MASK) +
                 bus->curSegment->len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
    }
#endif // __DCACHE_PRESENT

    SPI_IrqHandler(dev);
}

// Mark this bus as being SPI and record the first owner to use it
bool SPI_SetBusInstance(device_t *dev, int busE)
{
    dev->bus = &spiBus[IDX_BY_BUS(busE)];

    // By default each device should use SPI DMA if the bus supports it
    dev->useDMA = true;

    if (dev->bus->busType == BUS_TYPE_SPI)
    {
        // This bus has already been initialised
        dev->bus->deviceCount++;
        return true;
    }
    bus_t *bus = dev->bus;

    bus->busType_u.spi.instance = SPI_InstanceByBus(busE);

    if (bus->busType_u.spi.instance == NULL)
    {
        return false;
    }
    bus->busType_u.spi.leadingEdge = false;

    bus->busType = BUS_TYPE_SPI;
    bus->deviceCount = 1;
    bus->initTx = &dev->initTx;
    bus->initRx = &dev->initRx;
    bus->enDMA = SPI_InitBusDMA(busE);

    return true;
}

// Wait for DMA completion
void SPI_Wait(const device_t *dev)
{
    // Wait for completion
    while (dev->bus->curSegment != (segment_t *) BUS_SPI_FREE);
}

// Return true if DMA engine is busy
bool SPI_IsBusy(const device_t *dev)
{
    return (dev->bus->curSegment != (segment_t *) BUS_SPI_FREE);
}

static bool SPI_InternalReadWriteBufPolled(SPI_TypeDef *instance, const uint8_t *txData, uint8_t *rxData, int len)
{
    LL_SPI_SetTransferSize(instance, len);
    LL_SPI_Enable(instance);
    LL_SPI_StartMasterTransfer(instance);
    while (len)
    {
        while (!LL_SPI_IsActiveFlag_TXP(instance));
        uint8_t b = txData ? *(txData++) : 0xFF;
        LL_SPI_TransmitData8(instance, b);

        while (!LL_SPI_IsActiveFlag_RXP(instance));
        b = LL_SPI_ReceiveData8(instance);
        if (rxData)
        {
            *(rxData++) = b;
        }
        --len;
    }
    while (!LL_SPI_IsActiveFlag_EOT(instance));
    LL_SPI_ClearFlag_TXTF(instance);
    LL_SPI_Disable(instance);

    return true;
}

void SPI_InternalStopDMA(const device_t *dev)
{
    bus_t *bus = dev->bus;

    dma_t *dmaTx = bus->dmaTx;
    dma_t *dmaRx = bus->dmaRx;
    SPI_TypeDef *instance = bus->busType_u.spi.instance;

    if (dmaTx->dma == BDMA)
    {
        LL_BDMA_DisableChannel(dmaRx->dma, dmaRx->stream);
        LL_BDMA_DisableChannel(dmaTx->dma, dmaTx->stream);

        BDMA_CLEAR_FLAG(dmaRx, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
    }
    else
    {
        // Disable the DMA engine and SPI interface
        LL_DMA_DisableStream(dmaRx->dma, dmaRx->stream);
        LL_DMA_DisableStream(dmaTx->dma, dmaTx->stream);

        // Clear transfer flags
        DMA_CLEAR_FLAG(dmaRx, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
    }
    LL_SPI_DisableDMAReq_TX(instance);
    LL_SPI_DisableDMAReq_RX(instance);
    LL_SPI_ClearFlag_TXTF(instance);
    LL_SPI_Disable(instance);

}

// DMA transfer setup and start
void SPI_SequenceStart(const device_t *dev)
{
    bus_t *bus = dev->bus;
    SPI_TypeDef *instance = bus->busType_u.spi.instance;
    const spi_hw_t *spi = &spiHardware[IDX_BY_BUS(SPI_BusByInstance(instance))];
    bool dmaSafe = dev->useDMA && bus->enDMA;
    uint32_t xferLen = 0;
    uint32_t segmentCount = 0;

    bus->initSegment = true;
    // Switch bus speed
    if (dev->busType_u.spi.speed != bus->busType_u.spi.speed)
    {
        LL_SPI_SetBaudRatePrescaler(instance, SPI_DivisorToBRbits(instance, dev->busType_u.spi.speed));
        bus->busType_u.spi.speed = dev->busType_u.spi.speed;
    }

    // Switch SPI clock polarity/phase if necessary
    if (dev->busType_u.spi.leadingEdge != bus->busType_u.spi.leadingEdge)
    {
        if (dev->busType_u.spi.leadingEdge)
        {
            IO_Init(spi->sck, GPIO_MODE_AF_PP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_PULLDOWN, spi->sckAF);
            LL_SPI_SetClockPhase(instance, LL_SPI_PHASE_1EDGE);
            LL_SPI_SetClockPolarity(instance, LL_SPI_POLARITY_LOW);
        }
        else
        {
            IO_Init(spi->sck, GPIO_MODE_AF_PP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_PULLUP, spi->sckAF);
            LL_SPI_SetClockPhase(instance, LL_SPI_PHASE_2EDGE);
            LL_SPI_SetClockPolarity(instance, LL_SPI_POLARITY_HIGH);
        }

        bus->busType_u.spi.leadingEdge = dev->busType_u.spi.leadingEdge;
    }

    // Check that any reads are cache aligned and of multiple cache lines in length
    for (segment_t *checkSegment = (segment_t *) bus->curSegment; checkSegment->len; checkSegment++)
    {
        // Check there is no receive data as only transmit DMA is available
        if ((checkSegment->u.buffers.pRxData) && (bus->dmaRx == NULL))
        {
            dmaSafe = false;
            break;
        }

        // Check if RX data can be DMAed
        if ((checkSegment->u.buffers.pRxData) &&
            // DTCM can't be accessed by DMA1/2 on the H7
            (IS_DTCM(checkSegment->u.buffers.pRxData) ||
             // Memory declared as DMA_RAM will have an address between &_dmaram_start__ and &_dmaram_end__
             ((bus->dmaTx->dma == BDMA ? ((checkSegment->u.buffers.pRxData < &_dmaramd3_start__) ||
                                        (checkSegment->u.buffers.pRxData >= &_dmaramd3_end__)) :
                                        ((checkSegment->u.buffers.pRxData < &_dmaram_start__) ||
                                        (checkSegment->u.buffers.pRxData >= &_dmaram_end__))) &&
              (((uint32_t) checkSegment->u.buffers.pRxData & (CACHE_LINE_SIZE - 1)) ||
               (checkSegment->len & (CACHE_LINE_SIZE - 1))))))
        {
            dmaSafe = false;
            break;

        }
            // Check if TX data can be DMAed
        else if ((checkSegment->u.buffers.pTxData) && (IS_DTCM(checkSegment->u.buffers.pTxData) ||
                (bus->dmaTx->dma == BDMA ? ((checkSegment->u.buffers.pTxData < &_dmaramd3_start__) ||
                                            (checkSegment->u.buffers.pTxData >= &_dmaramd3_end__)) : 0)))
        {
            dmaSafe = false;
            break;
        }

        // Note that these counts are only valid if dmaSafe is true
        segmentCount++;
        xferLen += checkSegment->len;
    }

    if (dmaSafe && ((segmentCount > 1) ||
                    (xferLen >= BUS_DMA_THRESHOLD) ||
                    !bus->curSegment[segmentCount].negateCS))
    {
        // Intialize the init structures for the first transfer
        SPI_InternalInitStream(dev, false);

        // Assert Chip Select
        IO_Set(dev->busType_u.spi.csPin, IO_LOW);

        // Start the transfers
        SPI_InternalStartDMA(dev);
    }
    else
    {
        segment_t *lastSegment = NULL;
        bool segmentComplete;

        // Manually work through the segment list performing a transfer for each
        while (bus->curSegment->len)
        {
            if (!lastSegment || lastSegment->negateCS)
            {
                // Assert Chip Select if necessary - it's costly so only do so if necessary
                IO_Set(dev->busType_u.spi.csPin, IO_LOW);
            }

            SPI_InternalReadWriteBufPolled(
                    bus->busType_u.spi.instance,
                    bus->curSegment->u.buffers.pTxData,
                    bus->curSegment->u.buffers.pRxData,
                    bus->curSegment->len);

            if (bus->curSegment->negateCS)
            {
                // Negate Chip Select
                IO_Set(dev->busType_u.spi.csPin, IO_HIGH);
            }

            segmentComplete = true;
            if (bus->curSegment->callback)
            {
                switch (bus->curSegment->callback(dev->callbackArg))
                {
                    case BUS_BUSY:
                        // Repeat the last DMA segment
                        segmentComplete = false;
                        break;

                    case BUS_ABORT:
                        bus->curSegment = (segment_t *) BUS_SPI_FREE;
                        segmentComplete = false;
                        return;

                    case BUS_READY:
                    default:
                        // Advance to the next DMA segment
                        break;
                }
            }
            if (segmentComplete)
            {
                lastSegment = (segment_t *) bus->curSegment;
                bus->curSegment++;
            }
        }

        // If a following transaction has been linked, start it
        if (bus->curSegment->u.link.dev)
        {
            segment_t *endSegment = (segment_t *) bus->curSegment;
            const device_t *nextDev = endSegment->u.link.dev;
            segment_t *nextSegments = (segment_t *) endSegment->u.link.segment;
            bus->curSegment = nextSegments;
            endSegment->u.link.dev = NULL;
            endSegment->u.link.segment = NULL;
            SPI_SequenceStart(nextDev);
        }
        else
        {
            // The end of the segment list has been reached, so mark transactions as complete
            bus->curSegment = (segment_t *) BUS_SPI_FREE;
        }
    }
}


void SPI_Sequence(const device_t *dev, segment_t *segment)
{
    bus_t *bus = dev->bus;
    bool start = false;

    ATOMIC_ENTER_CRITICAL();
    {
        if (SPI_IsBusy(dev))     // if bus is busy, put data into next segmnet
        {
            segment_t *endSegment;
            // Defer this transfer to be triggered upon completion of the current transfer

            // Find the last segment of the new transfer
            for (endSegment = segment; endSegment->len; endSegment++);

            segment_t *endCmpSegment = (segment_t *) bus->curSegment;

            if (endCmpSegment)
            {
                while (true)
                {
                    // Find the last segment of the current transfer
                    for (; endCmpSegment->len; endCmpSegment++);

                    if (endCmpSegment == endSegment)
                    {
                        /* Attempt to use the new segment list twice in the same queue. Abort.
                         * Note that this can only happen with non-blocking transfers so drivers must take
                         * care to avoid this.
                         * */
                        break;
                    }

                    if (endCmpSegment->u.link.dev == NULL)  // End of the segment list queue reached
                    {
                        // Record the dev and segments parameters in the terminating segment entry
                        endCmpSegment->u.link.dev = dev;
                        endCmpSegment->u.link.segment = segment;
                        break;
                    }
                    else
                    {
                        // Follow the link to the next queued segment list
                        endCmpSegment = (segment_t *) endCmpSegment->u.link.segment;
                    }
                }
            }
        }
        else
        {
            // Claim the bus with this list of segments
            bus->curSegment = segment;
            start = true;
        }
    }
    ATOMIC_EXIT_CRITICAL();

    if (start) SPI_SequenceStart(dev);
}

bool SPI_UseDMA(const device_t *dev)
{
    // Full DMA only requires both transmit and receive
    return dev->bus->enDMA && dev->bus->dmaRx && dev->useDMA;
}


// Write data to a register
void SPI_WriteReg(const device_t *dev, uint8_t reg, uint8_t data)
{
    // This routine blocks so no need to use static data
    segment_t segment[] = {
            {.u.buffers = {&reg, NULL},  sizeof(reg),  false, NULL},
            {.u.buffers = {&data, NULL}, sizeof(data), true,  NULL},
            {.u.link = {NULL, NULL},     0,            true,  NULL},
    };

    SPI_Sequence(dev, &segment[0]);

    SPI_Wait(dev);
}

// Write data to a register, returning false if the bus is busy
bool SPI_WriteRegRB(const device_t *dev, uint8_t reg, uint8_t data)
{
    // Ensure any prior DMA has completed before continuing
    if (SPI_IsBusy(dev)) {
        return false;
    }

    SPI_WriteReg(dev, reg, data);

    return true;
}

// Wait for bus to become free, then read a byte from a register
uint8_t SPI_ReadReg(const device_t *dev, uint8_t reg)
{
    uint8_t data;
    // This routine blocks so no need to use static data
    segment_t segments[] = {
            {.u.buffers = {&reg, NULL},  sizeof(reg),  false, NULL},
            {.u.buffers = {NULL, &data}, sizeof(data), true,  NULL},
            {.u.link = {NULL, NULL},     0,            true,  NULL},
    };

    SPI_Sequence(dev, &segments[0]);

    SPI_Wait(dev);

    return data;
}

// Wait for bus to become free, then read a byte of data where the register is ORed with 0x80
uint8_t SPI_ReadRegMsk(const device_t *dev, uint8_t reg)
{
    return SPI_ReadReg(dev, reg | 0x80);
}

// Read a block of data from a register
void SPI_ReadRegBuf(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
    // This routine blocks so no need to use static data
    segment_t segments[] = {
            {.u.buffers = {&reg, NULL}, sizeof(reg), false, NULL},
            {.u.buffers = {NULL, data}, length, true, NULL},
            {.u.link = {NULL, NULL}, 0, true, NULL},
    };

    SPI_Sequence(dev, &segments[0]);

    SPI_Wait(dev);
}

// Read a block of data where the register is ORed with 0x80
void SPI_ReadRegMskBuf(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
    return SPI_ReadRegBuf(dev, reg | 0x80, data, length);
}

// Read a block of data from a register, returning false if the bus is busy
bool SPI_ReadRegBufRB(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
    // Ensure any prior DMA has completed before continuing
    if (SPI_IsBusy(dev)) {
        return false;
    }

    SPI_ReadRegBuf(dev, reg, data, length);

    return true;
}

// Read a block of data where the register is ORed with 0x80, returning false if the bus is busy
bool SPI_ReadRegMskBufRB(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
    return SPI_ReadRegBufRB(dev, reg | 0x80, data, length);
}

// Wait for bus to become free, then read/write block of data
void SPI_ReadWriteBuf(const device_t *dev, uint8_t *txData, uint8_t *rxData, int len)
{
    // This routine blocks so no need to use static data
    segment_t segments[] = {
            {.u.buffers = {txData, rxData}, len, true, NULL},
            {.u.link = {NULL, NULL},        0,   true, NULL},
    };

    SPI_Sequence(dev, &segments[0]);

    SPI_Wait(dev);
}

void SPI_BusDeviceRegister(const device_t *dev)
{
    UNUSED(dev);

    spiRegisteredDeviceCount++;
}

static void SPI_EnableClock(bus_e busE)
{
    switch (busE)
    {
#ifdef USE_SPI1
        case BUS_SPI1:
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
            break;
#endif
#ifdef USE_SPI2
            case BUS_SPI2:
            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
            break;
#endif
#ifdef USE_SPI3
            case BUS_SPI3:
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI3);
            break;
#endif
#ifdef USE_SPI4
        case BUS_SPI4:
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
            break;
#endif
#ifdef USE_SPI5
            case BUS_SPI5:
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
            break;
#endif
#ifdef USE_SPI6
            case BUS_SPI6:
            LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SPI6);
            break;
#endif
        default:
            break;
    }
}

static LL_SPI_InitTypeDef defaultInit =
        {
                .TransferDirection = LL_SPI_FULL_DUPLEX,
                .Mode = LL_SPI_MODE_MASTER,
                .DataWidth = LL_SPI_DATAWIDTH_8BIT,
                .NSS = LL_SPI_NSS_SOFT,
                .BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8,
                .BitOrder = LL_SPI_MSB_FIRST,
                .CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE,
                .ClockPolarity = LL_SPI_POLARITY_HIGH,
                .ClockPhase = LL_SPI_PHASE_2EDGE,
        };

static void SPI_InitBus(bus_e busE)
{
    const spi_hw_t *spi = &spiHardware[IDX_BY_BUS(busE)];
    SPI_TypeDef *instance = spi->instance;

    if (!instance || busE <= BUS_NULL || busE >= BUS_SPICOUNT)
        return;

    // Enable SPI clock
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (instance == SPI1 || instance == SPI2 || instance == SPI3)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI123;
        PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    }
    else if (instance == SPI4 || instance == SPI5)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI45;
        PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    }
    else if (instance == SPI6)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI6;
        PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_D3PCLK1;
    }
    else    assert(0);
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        return;
    }

    /* Peripheral clock enable */
    SPI_EnableClock(busE);

    IO_Init(spi->miso, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, spi->misoAF);
    IO_Init(spi->mosi, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, spi->mosiAF);
    IO_Init(spi->sck, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, spi->sckAF);

    LL_SPI_Disable(instance);
    LL_SPI_DeInit(instance);

    // Prevent glitching when SPI is disabled
    LL_SPI_EnableGPIOControl(instance);

    LL_SPI_SetFIFOThreshold(instance, LL_SPI_FIFO_TH_01DATA);
    LL_SPI_Init(instance, &defaultInit);
}

void SPI_InternalResetStream(dma_t *descriptor)
{
    if (descriptor->dma == BDMA)
    {
        LL_BDMA_DisableChannel(descriptor->dma, descriptor->stream);
        while (LL_BDMA_IsEnabledChannel(descriptor->dma, descriptor->stream));
        BDMA_CLEAR_FLAG(descriptor, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
    }
    else
    {
        // Disable the stream
        LL_DMA_DisableStream(descriptor->dma, descriptor->stream);
        while (LL_DMA_IsEnabledStream(descriptor->dma, descriptor->stream));
        // Clear any pending interrupt flags
        DMA_CLEAR_FLAG(descriptor, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
    }
}

void SPI_InternalResetDescriptors(bus_t *bus)
{
    LL_DMA_InitTypeDef *initTx = bus->initTx;

    LL_DMA_StructInit(initTx);

    initTx->PeriphRequest = bus->dmaTx->channel;

    initTx->Mode = LL_DMA_MODE_NORMAL;
    initTx->Direction = bus->dmaTx->dma == BDMA ? LL_BDMA_DIRECTION_MEMORY_TO_PERIPH : LL_DMA_DIRECTION_MEMORY_TO_PERIPH;

    initTx->PeriphOrM2MSrcAddress = (uint32_t) &bus->busType_u.spi.instance->TXDR;
    initTx->Priority = LL_DMA_PRIORITY_LOW;
    initTx->PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    initTx->PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    initTx->MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;

    if (bus->dmaRx)
    {
        LL_DMA_InitTypeDef *initRx = bus->initRx;

        LL_DMA_StructInit(initRx);

        initRx->PeriphRequest = bus->dmaRx->channel;
        initRx->Mode = LL_DMA_MODE_NORMAL;
        initRx->Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
        initRx->PeriphOrM2MSrcAddress = (uint32_t) &bus->busType_u.spi.instance->RXDR;
        initRx->Priority = LL_DMA_PRIORITY_LOW;
        initRx->PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
        initRx->PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    }
}


void SPI_BspInit(void)
{
#ifdef USE_SPI1
    SPI_InitBus(BUS_SPI1);
#endif
#ifdef USE_SPI2
    SPI_InitBus(BUS_SPI2);
#endif
#ifdef USE_SPI3
    SPI_InitBus(BUS_SPI1);
#endif
#ifdef USE_SPI4
    SPI_InitBus(BUS_SPI4);
#endif
#ifdef USE_SPI5
    SPI_InitBus(BUS_SPI5);
#endif
#ifdef USE_SPI6
    SPI_InitBus(BUS_SPI6);
#endif
}

bool SPI_InitBusDMA(bus_e busE)
{
    if (busE <= BUS_NULL || busE >= BUS_SPICOUNT)
        return false;

    bus_t *bus = &spiBus[IDX_BY_BUS(busE)];

    if (bus->busType != BUS_TYPE_SPI)
    {
        // This bus is not in use
        return false;
    }

    uint8_t dmaTxStream = DMA_NONE;
    uint8_t dmaRxStream = DMA_NONE;
    dma_peripheral_e dmaTxPeripheral = bus->busType_u.spi.instance == SPI6 ? BDMA_PERIPH_SPI_MOSI : DMA_PERIPH_SPI_MOSI;
    dma_peripheral_e dmaRxPeripheral = bus->busType_u.spi.instance == SPI6 ? BDMA_PERIPH_SPI_MISO : DMA_PERIPH_SPI_MISO;


    for (uint8_t opt = 0; opt <= MAX_PERIPHERAL_DMA_OPTIONS - 1; opt++)
    {
        if (dmaTxStream == DMA_NONE)
        {
            const dma_channel_t *dmaTxChannelSpec = DMA_GetChannelSpecByPeripheral(dmaTxPeripheral, busE, opt);

            if (dmaTxChannelSpec)
            {
                dmaTxStream = DMA_GetIdentifier(dmaTxChannelSpec->ref);

                bus->dmaTx = DMA_GetDescriptorByIdentifier(dmaTxStream);
                bus->dmaTx->stream = DMA_DEVICE_INDEX(dmaTxStream);
                bus->dmaTx->channel = dmaTxChannelSpec->channel;

                DMA_Enable(dmaTxStream);
            }
        }
        else if (dmaRxStream == DMA_NONE)
        {
            const dma_channel_t *dmaRxChannelSpec = DMA_GetChannelSpecByPeripheral(dmaRxPeripheral, busE, opt);

            if (dmaRxChannelSpec)
            {
                dmaRxStream = DMA_GetIdentifier(dmaRxChannelSpec->ref);

                bus->dmaRx = DMA_GetDescriptorByIdentifier(dmaRxStream);
                bus->dmaRx->stream = DMA_DEVICE_INDEX(dmaRxStream);
                bus->dmaRx->channel = dmaRxChannelSpec->channel;

                DMA_Enable(dmaRxStream);
                break;
            }
        }
    }

    if (dmaTxStream && dmaRxStream)
    {
        // Ensure streams are disabled
        SPI_InternalResetStream(bus->dmaRx);
        SPI_InternalResetStream(bus->dmaTx);

        SPI_InternalResetDescriptors(bus);

        /* Note that this driver may be called both from the normal thread of execution, or from USB interrupt
         * handlers, so the DMA completion interrupt must be at a higher priority
         */
        DMA_SetHandler(dmaRxStream, SPI_RxIrqHandler, NVIC_PRIO_SPI_DMA, 0);
    }
    else
    {
        // Disassociate channels from bus
        bus->dmaRx = (dma_t *) NULL;
        bus->dmaTx = (dma_t *) NULL;
        return false;
    }
    return true;
}

bool SPI_DeviceBindByHardware(device_t *dev, const hw_config_t *config)
{
    if (!config->csPin.port || !SPI_SetBusInstance(dev, config->busE))
    {
        return false;
    }

    dev->name = config->name;
    SPI_SetClkPhasePolarity(dev, config->leadingEdge);

    dev->busType_u.spi.csPin = config->csPin;

    IO_Init(dev->busType_u.spi.csPin, CS_CONFIG);
    IO_Set(dev->busType_u.spi.csPin, IO_HIGH);

    while (HAL_GetTick() < 100);

    SPI_SetClkDivisor(dev, SPI_CalculateDivider(1000000));
    return true;
}