// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "bus.h"
#include "drv_spi.h"

static bus_t Bus[BUS_NUM] = {
            //modify the following lines
        {   .busType = BUS_TYPE_SPI, .busType_u.spi.instance = SPI1,
                .enDMA = 1, .dmaTx = DMA1, .streamTx = LL_DMA_STREAM_0, .dmaRx = DMA1, .streamRx = LL_DMA_STREAM_1},
        {   .busType = BUS_TYPE_SPI, .busType_u.spi.instance = SPI4,
                .enDMA = 1, .dmaTx = DMA1, .streamTx = LL_DMA_STREAM_2, .dmaRx = DMA1, .streamRx = LL_DMA_STREAM_3},
};


static bus_t *DeviceToBus(device_e device)
{
    bus_t *bus;
    switch (device)
    {
        case DEV_SPI1:
#ifdef USE_SPI1
            for (bus = &Bus[0]; bus; bus++)
            {
                if (device == (int)bus->busType_u.spi.instance)
                {
                    return bus;
                }
            }
#endif
            break;
        case DEV_SPI2:
#ifdef USE_SPI2
            for (bus = &Bus[0]; bus; bus++)
            {
                if (device == (int)bus->busType_u.spi.instance)
                {
                    return bus;
                }
            }
#endif
            break;
        case DEV_SPI3:
#ifdef USE_SPI3
            for (bus = &Bus[0]; bus; bus++)
            {
                if (device == (int)bus->busType_u.spi.instance)
                {
                    return bus;
                }
            }
#endif
            break;
        case DEV_SPI4:
#ifdef USE_SPI4
            for (bus = &Bus[0]; bus; bus++)
            {
                if (device == (int)bus->busType_u.spi.instance)
                {
                    return bus;
                }
            }
#endif
            break;
        default:
            break;
    }
    return NULL;
}

static void Bus_SetInitialVal(bus_t *bus)
{
    bus->busStatus = BUS_READY;
    bus->deviceCount = 0;
    bus->isInit = 0;
    bus->curSegment = 0;
}

static Status_t Bus_Driver_Init(bus_t *bus)
{
    switch (bus->busType)
    {
        case BUS_TYPE_SPI:
            return Drv_SPI_Init(bus);
        case BUS_TYPE_I2C:
        case BUS_TYPE_NONE:
        default:
            break;
    }
    return S_Error;
}

bus_t * Register_Bus(device_e device)
{
    bus_t *bus = DeviceToBus(device);
    if (!bus) return NULL;

    if (!bus->isInit)
    {
        Bus_SetInitialVal(bus);
        if (Bus_Driver_Init(bus) != S_OK)   return NULL;

        //ring buf init
        Ring_Init(&bus->ring);

        //lock init
        osMutexDef(lock);
        bus->lock = osMutexCreate(osMutex(lock));
        bus->isInit = 1;
    }
    bus->deviceCount++;

    return bus;
}


bool IsBusBusy(bus_t *bus)
{
    return (bus->busStatus == BUS_BUSY ? 1 : 0);
}
void waitBus(bus_t *bus)
{
    while (bus->busStatus != BUS_READY);
}




