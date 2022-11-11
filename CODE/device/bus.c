// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "bus.h"
#include "bus_spi.h"

void Bus_DeviceRegister(const device_t *dev)
{
    switch (dev->bus->busType) {
#ifdef EN_SPI
        case BUS_TYPE_SPI:
        SPI_BusDeviceRegister(dev);
        break;
#endif
#ifdef EN_I2C
        case BUS_TYPE_I2C:
        i2cBusDeviceRegister(dev);
        break;
#endif
        default:
            break;
    }
}
