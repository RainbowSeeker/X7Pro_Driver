// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/10/30.
//

#include "drv_spi.h"



static void DMA_ClearFlag(DMA_TypeDef *DMAx, uint32_t stream)
{
    if (stream == LL_DMA_STREAM_2 || stream == LL_DMA_STREAM_3)
    {
        stream = stream * 6 + 4;
    }
    DMAx->LIFCR |= (uint32_t) 0x3d << stream;
}
static void SPI_DMA_Init(bus_t *spiBus)
{
    DMA_ClearFlag(spiBus->dmaTx, spiBus->streamTx);
    DMA_ClearFlag(spiBus->dmaRx, spiBus->streamRx);

    spiBus->initRxDMA.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    spiBus->initRxDMA.Mode = LL_DMA_MODE_NORMAL;
    spiBus->initRxDMA.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    spiBus->initRxDMA.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    spiBus->initRxDMA.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    spiBus->initRxDMA.MemoryOrM2MDstDataSize = LL_DMA_PDATAALIGN_BYTE;
    spiBus->initRxDMA.PeriphRequest = LL_DMAMUX1_REQ_SPI1_RX;
    spiBus->initRxDMA.Priority = LL_DMA_PRIORITY_MEDIUM;
    spiBus->initRxDMA.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
    spiBus->initRxDMA.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
    spiBus->initRxDMA.MemBurst = LL_DMA_MBURST_SINGLE;
    spiBus->initRxDMA.PeriphBurst = LL_DMA_MBURST_SINGLE;
    LL_DMA_Init(spiBus->dmaRx, spiBus->streamRx, &spiBus->initRxDMA);


    spiBus->initTxDMA.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
    spiBus->initTxDMA.Mode = LL_DMA_MODE_NORMAL;
    spiBus->initTxDMA.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    spiBus->initTxDMA.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    spiBus->initTxDMA.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    spiBus->initTxDMA.MemoryOrM2MDstDataSize = LL_DMA_PDATAALIGN_BYTE;
    spiBus->initTxDMA.PeriphRequest = LL_DMAMUX1_REQ_SPI1_TX;
    spiBus->initTxDMA.Priority = LL_DMA_PRIORITY_HIGH;
    spiBus->initTxDMA.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
    spiBus->initTxDMA.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
    spiBus->initTxDMA.MemBurst = LL_DMA_MBURST_SINGLE;
    spiBus->initTxDMA.PeriphBurst = LL_DMA_MBURST_SINGLE;
    LL_DMA_Init(spiBus->dmaTx, spiBus->streamTx, &spiBus->initTxDMA);


    //open interrupts of dma
    LL_DMA_EnableIT_TC(spiBus->dmaTx, spiBus->streamTx);
    LL_DMA_EnableIT_TE(spiBus->dmaTx, spiBus->streamTx);

    LL_DMA_EnableIT_TC(spiBus->dmaRx, spiBus->streamRx);
    LL_DMA_EnableIT_TE(spiBus->dmaRx, spiBus->streamRx);

}

void SPI_DMA_Config(bus_t *spiBus, uint32_t txAddr, uint32_t rxAddr, uint32_t len)
{

}


Status_t Drv_SPI_Init(bus_t *spiBus)
{
    SPI_TypeDef *instance = spiBus->busType_u.spi.instance;
    switch ((uint32_t)instance)
    {
        case (uint32_t)SPI1:
            MX_SPI1_Init();
            break;
        case (uint32_t)SPI4:
            MX_SPI4_Init();
            break;
        default:    //don't support yet.
            return -1;
    }

    if (spiBus->enDMA)
    {
        SPI_DMA_Init(spiBus);
        LL_SPI_EnableDMAReq_TX(instance);
        LL_SPI_EnableDMAReq_RX(instance);
    }

    LL_SPI_EnableGPIOControl(instance);
    LL_SPI_Enable(instance);
    return 0;
}



