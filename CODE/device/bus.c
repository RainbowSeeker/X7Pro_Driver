// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "bus.h"
#include "drv_spi.h"

static bus_t Bus[BUS_NUM] = {
        {   .busType = BUS_TYPE_SPI, .busType_u.spi.instance = SPI1,
                 //modify the following lines
                .enDMA = 1, .dmaTx = DMA1, .streamTx = LL_DMA_STREAM_0, .dmaRx = DMA1, .streamRx = LL_DMA_STREAM_1}
};


bus_t *DeviceToBus(device_e device)
{
    bus_t *bus;
    switch (device)
    {
        case DEV_SPI1:
#ifndef USE_SPI1
            break;
#endif
        case DEV_SPI2:
#ifndef USE_SPI1
            break;
#endif
            for (bus = &Bus[0]; bus; bus++)
            {
                if (device == (int)bus->busType_u.spi.instance)
                {
                    return bus;
                }
            }
        default:
            break;
    }
    return NULL;
}

void Bus_SetInitialVal(bus_t *bus)
{
    bus->busStatus = BUS_READY;
    bus->deviceCount = 0;
    bus->isInit = 0;
    bus->curSegment = 0;
}

Status_t Bus_Driver_Init(bus_t *bus)
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

bool IsBusBusy(bus_t *bus)
{
    return (bus->busStatus == BUS_BUSY ? 1 : 0);
}
void waitBus(bus_t *bus)
{
    while (bus->busStatus != BUS_READY);
}




