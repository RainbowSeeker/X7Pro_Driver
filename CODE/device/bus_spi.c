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
    int ret = 0;
    if (saveSpiId >= SPI_DEV_NUM)
        return -1;   //number of spi's device reach limit!

    if (!spiDevice || device < 0 || spiDevice->id || !spiDevice->pwrPin.port || !spiDevice->csPin.port)
        return -2;

    IO_Init(spiDevice->pwrPin, CS_CONFIG);
    IO_Init(spiDevice->csPin, CS_CONFIG);

    IO_Set(spiDevice->pwrPin, IO_HIGH);
    IO_Set(spiDevice->csPin, IO_HIGH);

    bus_t *bus = DeviceToBus(device);
    if (!bus)   return -3;

#ifdef SUPPORT_OS
    vPortEnterCritical();
#else
    __disable_irq();
#endif

    spiDevice->bus = bus;
    if (!spiDevice->bus->isInit)
    {
        Bus_SetInitialVal(spiDevice->bus);
        if (Bus_Driver_Init(spiDevice->bus) != S_OK)
        {
            ret = -3;
            goto error;
        }

        //ring buf init
        Ring_Init(&spiDevice->bus->ring);
        spiDevice->bus->isInit = 1;
    }
    spiDevice->bus->deviceCount++;
    spiDevice->id = ++saveSpiId;

    error:
#ifdef SUPPORT_OS
    vPortExitCritical();
#else
    __enable_irq();
#endif
    return ret;
}


static void SPI_TransferStart(spi_device_t *spiDevice)
{
    bus_t *bus = spiDevice->bus;
    segment_t *curSegment = bus->curSegment;

    bus->busStatus = BUS_BUSY;

    //select specified device
    IO_Set(spiDevice->csPin, IO_LOW);

    if (spiDevice->useDMA && bus->enDMA && curSegment->len > BUS_DMA_THRESHOLD)
    {
        LL_SPI_StartMasterTransfer(bus->busType_u.spi.instance);

        LL_DMA_SetPeriphAddress(bus->dmaRx, bus->streamRx, (uint32_t)&bus->busType_u.spi.instance->RXDR);
        LL_DMA_SetMemoryAddress(bus->dmaRx, bus->streamRx, (uint32_t)curSegment->pRxData);
        LL_DMA_SetDataLength(bus->dmaRx, bus->streamRx, curSegment->len);
        LL_DMA_EnableStream(bus->dmaRx, bus->streamRx);

        LL_DMA_SetPeriphAddress(bus->dmaTx, bus->streamTx, (uint32_t)&bus->busType_u.spi.instance->TXDR);
        LL_DMA_SetMemoryAddress(bus->dmaTx, bus->streamTx, (uint32_t)curSegment->pTxData);
        LL_DMA_SetDataLength(bus->dmaTx, bus->streamTx, curSegment->len);
        LL_DMA_EnableStream(bus->dmaTx, bus->streamTx);
    }
    else
    {
        LL_SPI_StartMasterTransfer(bus->busType_u.spi.instance);

        while (curSegment->len)
        {
            while (!LL_SPI_IsActiveFlag_TXP(bus->busType_u.spi.instance));
            uint8_t b = curSegment->pTxData ? *(curSegment->pTxData++) : 0xFF;
            LL_SPI_TransmitData8(bus->busType_u.spi.instance, b);

            while (!LL_SPI_IsActiveFlag_RXP(bus->busType_u.spi.instance));
            b = LL_SPI_ReceiveData8(bus->busType_u.spi.instance);
            if (curSegment->pRxData) {
                *(curSegment->pRxData++) = b;
            }
            curSegment->len--;
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
#ifdef SUPPORT_OS
    vPortEnterCritical();
#else
    __disable_irq();
#endif
    if (IsBusBusy(bus))     // if bus is busy, put data into buf
    {
        while (segment && Ring_PushBack(&bus->ring, segment) == S_OK)
        {
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
#ifdef SUPPORT_OS
    vPortExitCritical();
#else
    __enable_irq();
#endif
    if (segment->len && (segment->pTxData || segment->pRxData))    return -1;
    else return 0;
}

#define CACHE_LINE_SIZE 32
#define CACHE_LINE_MASK (CACHE_LINE_SIZE - 1)

void SPI_RxIrqHandler(spi_device_t *spiDevice)
{
    bus_t *bus = spiDevice->bus;

    if (bus->curSegment->pRxData)
    {
        SCB_InvalidateDCache_by_Addr(
                (uint32_t *)((uint32_t)bus->curSegment->pRxData & ~CACHE_LINE_MASK),
                (((uint32_t)bus->curSegment->pRxData & CACHE_LINE_MASK) +
                 bus->curSegment->len - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);

        bus->curSegment->callback(bus->curSegment->pRxData);
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
