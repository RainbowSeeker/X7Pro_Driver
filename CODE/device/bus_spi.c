// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "bus_spi.h"

static uint8_t saveSpiId = 0;

void waitSpiDevice(spi_device_t *spiDevice)
{
    waitBus(spiDevice->bus);
}

Status_t SPI_Register_Bus(spi_device_t *spiDevice, device_e device)
{
    if (saveSpiId >= SPI_DEV_NUM)
        return -1;   //number of spi's device reach limit!

    if (!spiDevice || device < 0 || spiDevice->id || !spiDevice->pwrPin.port || !spiDevice->csPin.port)
        return -2;

    IO_Set(spiDevice->pwrPin, IO_LOW);
    IO_Set(spiDevice->csPin, IO_HIGH);

    IO_Init(spiDevice->pwrPin, CS_CONFIG);
    IO_Init(spiDevice->csPin, CS_CONFIG);

    spiDevice->bus = Register_Bus(device);
    if (!spiDevice->bus)
        return -3;

    spiDevice->id = ++saveSpiId;
    IO_Set(spiDevice->pwrPin, IO_HIGH);
    return 0;
}

#define CACHE_LINE_SIZE 32
#define CACHE_LINE_MASK (CACHE_LINE_SIZE - 1)

static void SPI_TransferStart(spi_device_t *spiDevice)
{
    STATIC_DMA_DATA_AUTO uint8_t dummyTxByte = 0xff;
    STATIC_DMA_DATA_AUTO uint8_t dummyRxByte;
    bus_t *bus = spiDevice->bus;
    segment_t *curSegment = bus->curSegment;
    bool dmaSafe = spiDevice->useDMA && bus->enDMA;
    uint32_t xferLen = 0;
    uint16_t segmentCount = 0;


    bus->busStatus = BUS_BUSY;

    //select specified device
    IO_Set(spiDevice->csPin, IO_LOW);

    // Check that any reads are cache aligned and of multiple cache lines in length
    for (segment_t *checkSegment = (segment_t *)bus->curSegment; checkSegment->len; checkSegment++) {
        // Check there is no receive data as only transmit DMA is available
        if ((checkSegment->pRxData) && (bus->dmaRx == NULL)) {
            dmaSafe = false;
            break;
        }

        // Check if RX data can be DMAed
        if ((checkSegment->pRxData) &&
            // DTCM can't be accessed by DMA1/2 on the H7
            (IS_DTCM(checkSegment->pRxData) ||
             // Memory declared as DMA_RAM will have an address between &_dmaram_start__ and &_dmaram_end__
             (((checkSegment->pRxData < &_dmaram_start__) || (checkSegment->pRxData >= &_dmaram_end__)) &&
              (((uint32_t)checkSegment->pRxData & (CACHE_LINE_SIZE - 1)) || (checkSegment->len & (CACHE_LINE_SIZE - 1)))))) {
            dmaSafe = false;
            break;
        }
            // Check if TX data can be DMAed
        else if ((checkSegment->pTxData) && IS_DTCM(checkSegment->pTxData)) {
            dmaSafe = false;
            break;
        }

        // Note that these counts are only valid if dmaSafe is true
        segmentCount++;
        xferLen += checkSegment->len;
    }

    if (dmaSafe && ((segmentCount > 1) || (xferLen >= BUS_DMA_THRESHOLD)))
    {
        LL_SPI_StartMasterTransfer(bus->busType_u.spi.instance);

        LL_DMA_SetPeriphAddress(bus->dmaRx, bus->streamRx, (uint32_t)&bus->busType_u.spi.instance->RXDR);
        if (curSegment->pRxData)
        {
            if ((curSegment->pRxData < &_dmaram_start__) || (curSegment->pRxData >= &_dmaram_end__))
            {
                SCB_CleanDCache_by_Addr(
                        (uint32_t *)((uint32_t)curSegment->pRxData & ~CACHE_LINE_MASK),
                        (((uint32_t)curSegment->pRxData & CACHE_LINE_MASK) + curSegment->len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);

            }
            LL_DMA_SetMemoryAddress(bus->dmaRx, bus->streamRx, (uint32_t)curSegment->pRxData);
            LL_DMA_SetMemoryIncMode(bus->dmaRx, bus->streamRx, LL_DMA_MEMORY_INCREMENT);
        } else
        {
            LL_DMA_SetMemoryAddress(bus->dmaRx, bus->streamRx, (uint32_t)&dummyRxByte);
            LL_DMA_SetMemoryIncMode(bus->dmaRx, bus->streamRx, LL_DMA_MEMORY_NOINCREMENT);
        }
        LL_DMA_SetDataLength(bus->dmaRx, bus->streamRx, curSegment->len);
        LL_DMA_EnableStream(bus->dmaRx, bus->streamRx);

        LL_DMA_SetPeriphAddress(bus->dmaTx, bus->streamTx, (uint32_t)&bus->busType_u.spi.instance->TXDR);
        if (curSegment->pTxData)
        {
            if ((curSegment->pTxData < &_dmaram_start__) || (curSegment->pTxData >= &_dmaram_end__))
            {
                SCB_CleanDCache_by_Addr(
                        (uint32_t *)((uint32_t)curSegment->pTxData & ~CACHE_LINE_MASK),
                        (((uint32_t)curSegment->pTxData & CACHE_LINE_MASK) + curSegment->len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);

            }
            LL_DMA_SetMemoryAddress(bus->dmaTx, bus->streamTx, (uint32_t)curSegment->pTxData);
            LL_DMA_SetMemoryIncMode(bus->dmaTx, bus->streamTx, LL_DMA_MEMORY_INCREMENT);
        } else
        {
            LL_DMA_SetMemoryAddress(bus->dmaTx, bus->streamTx, (uint32_t)&dummyTxByte);
            LL_DMA_SetMemoryIncMode(bus->dmaTx, bus->streamTx, LL_DMA_MEMORY_NOINCREMENT);
        }
        LL_DMA_SetDataLength(bus->dmaTx, bus->streamTx, curSegment->len);
        LL_DMA_EnableStream(bus->dmaTx, bus->streamTx);
    }
    else
    {
        uint16_t idx = 0;
        LL_SPI_StartMasterTransfer(bus->busType_u.spi.instance);

        while (curSegment->len)
        {
            while (!LL_SPI_IsActiveFlag_TXP(bus->busType_u.spi.instance));
            uint8_t b = curSegment->pTxData ? *(curSegment->pTxData+idx) : 0xFF;
            LL_SPI_TransmitData8(bus->busType_u.spi.instance, b);

            while (!LL_SPI_IsActiveFlag_RXP(bus->busType_u.spi.instance));
            b = LL_SPI_ReceiveData8(bus->busType_u.spi.instance);
            if (curSegment->pRxData) {
                *(curSegment->pRxData+idx) = b;
            }
            curSegment->len--;
            idx++;
        }

        if (curSegment->callback && curSegment->pRxData)
        {
            curSegment->callback(curSegment->pRxData);
        }

        if (Ring_GetSize(&bus->ring))
        {
            Ring_PopFront(&bus->ring, &bus->curSegment);
            if (bus->curSegment)
            {
                SPI_TransferStart(spiDevice);
            }
        }
        else
        {
            bus->busStatus = BUS_READY;
            IO_Set(spiDevice->csPin, IO_HIGH);
        }
    }

}


Status_t SPI_Transfer(spi_device_t *spiDevice, segment_t *segment)
{
    bus_t *bus = spiDevice->bus;

    osMutexWait(bus->lock, osWaitForever);
    if (IsBusBusy(bus))     // if bus is busy, put data into buf
    {
        while (segment->len && (segment->pTxData || segment->pRxData))    //put  segments into buf
        {
            if (Ring_PushBack(&bus->ring, segment) != S_OK)
            {
                break;
            }
            segment++;
        }
    }
    else
    {
        bus->curSegment = segment++;
        while (segment->len && (segment->pTxData || segment->pRxData))    //put left segments into buf
        {
            if (Ring_PushBack(&bus->ring, segment) != S_OK)
            {
                break;
            }
            segment++;
        }
        SPI_TransferStart(spiDevice);
    }
    osMutexRelease(bus->lock);

    if (segment->len && (segment->pTxData || segment->pRxData))    return -1;
    else return 0;
}

void SPI_RxIrqHandler(spi_device_t *spiDevice)
{
    bus_t *bus = spiDevice->bus;

    if (bus->curSegment->pRxData)
    {
        if ((bus->curSegment->pRxData < &_dmaram_start__) || (bus->curSegment->pRxData >= &_dmaram_end__))
        {
            SCB_InvalidateDCache_by_Addr(
                    (uint32_t *)((uint32_t)bus->curSegment->pRxData & ~CACHE_LINE_MASK),
                    (((uint32_t)bus->curSegment->pRxData & CACHE_LINE_MASK) +
                     bus->curSegment->len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
        }

        if (bus->curSegment->callback)
        {
            bus->curSegment->callback(bus->curSegment->pRxData);
        }
    }

    if (Ring_GetSize(&bus->ring))
    {
        Ring_PopFront(&bus->ring, &bus->curSegment);
        SPI_TransferStart(spiDevice);
    }
    else
    {
        //unlock bus
        bus->busStatus = BUS_READY;
        IO_Set(spiDevice->csPin, IO_HIGH);
    }

}



// Write data to a register
void SPI_WriteReg(spi_device_t *spiDevice, uint8_t reg, uint8_t data)
{
    // This routine blocks so no need to use static data
    segment_t segments[] = {
            {&reg, NULL, sizeof(reg), NULL},
            {&data, NULL, sizeof(data), NULL},
            {NULL, NULL, 0, NULL},
    };

    SPI_Transfer(spiDevice, &segments[0]);

    waitSpiDevice(spiDevice);
}