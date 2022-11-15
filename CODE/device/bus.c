// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "bus.h"
#include "bus_spi.h"

void Bus_DeviceRegister(const device_t *dev)
{
    switch (dev->bus->busType) {
#ifdef USE_SPI
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

// Write routines where the register is masked with 0x7f
bool Bus_WriteRegister(const device_t *dev, uint8_t reg, uint8_t data)
{
#if !defined(USE_SPI) && !defined(USE_I2C)
    UNUSED(reg);
    UNUSED(data);
#endif
    switch (dev->bus->busType) {
#ifdef USE_SPI
        case BUS_TYPE_SPI:
            return SPI_WriteRegRB(dev, reg & 0x7f, data);
#endif
#ifdef USE_I2C
        case BUS_TYPE_I2C:
            return i2cBusWriteRegister(dev, reg, data);
#endif
        default:
            return false;
    }
}

bool Bus_WriteRegisterStart(const device_t *dev, uint8_t reg, uint8_t data)
{
#if !defined(USE_SPI) && !defined(USE_I2C)
    UNUSED(reg);
    UNUSED(data);
#endif
    switch (dev->bus->busType) {
#ifdef USE_SPI
        case BUS_TYPE_SPI:
            return SPI_WriteRegRB(dev, reg & 0x7f, data);
#endif
#ifdef USE_I2C
            case BUS_TYPE_I2C:
//        return i2cBusWriteRegisterStart(dev, reg, data);
#endif
        default:
            return false;
    }
}

// Access routines where the register is accessed directly
bool Bus_RawWriteRegister(const device_t *dev, uint8_t reg, uint8_t data)
{
#ifdef USE_SPI
    if (dev->bus->busType ==  BUS_TYPE_SPI) {
        return SPI_WriteRegRB(dev, reg, data);
    } else
#endif
    {
        return Bus_WriteRegister(dev, reg, data);
    }
}

bool Bus_RawWriteRegisterStart(const device_t *dev, uint8_t reg, uint8_t data)
{
#ifdef USE_SPI
    if (dev->bus->busType ==  BUS_TYPE_SPI) {
        return SPI_WriteRegRB(dev, reg, data);
    } else
#endif
    {
        return Bus_WriteRegisterStart(dev, reg, data);
    }
}

// Read routines where the register is ORed with 0x80
bool Bus_ReadRegisterBuffer(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
#if !defined(USE_SPI) && !defined(USE_I2C)
    UNUSED(reg);
    UNUSED(data);
    UNUSED(length);
#endif
    switch (dev->bus->busType) {
#ifdef USE_SPI
        case BUS_TYPE_SPI:
            return SPI_ReadRegMskBufRB(dev, reg | 0x80, data, length);
#endif
#ifdef USE_I2C
        case BUS_TYPE_I2C:
            return i2cBusReadRegisterBuffer(dev, reg, data, length);
#endif
        default:
            return false;
    }
}

bool Bus_RawReadRegisterBuffer(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
#ifdef USE_SPI
    if (dev->bus->busType == BUS_TYPE_SPI) {
        return SPI_ReadRegBufRB(dev, reg, data, length);
    } else
#endif
    {
        return Bus_ReadRegisterBuffer(dev, reg, data, length);
    }
}

bool Bus_RawReadRegisterBufferStart(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
#ifdef USE_SPI
    if (dev->bus->busType == BUS_TYPE_SPI) {
        return SPI_ReadRegBufRB(dev, reg, data, length);
    } else
#endif
    {
        return Bus_ReadRegisterBufferStart(dev, reg, data, length);
    }
}


// Start the I2C read, but do not wait for completion
bool Bus_ReadRegisterBufferStart(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
#if !defined(USE_SPI) && !defined(USE_I2C)
    UNUSED(reg);
    UNUSED(data);
    UNUSED(length);
#endif
    switch (dev->bus->busType) {
#ifdef USE_SPI
        case BUS_TYPE_SPI:
            // For SPI allow the transaction to complete
            return SPI_ReadRegMskBufRB(dev, reg | 0x80, data, length);
#endif
#ifdef USE_I2C
            case BUS_TYPE_I2C:
        // Initiate the read access
        return i2cBusReadRegisterBufferStart(dev, reg, data, length);
#endif
        default:
            return false;
    }
}


// Returns true if bus is still busy
bool Bus_Busy(const device_t *dev, bool *error)
{
#if !defined(USE_I2C)
    UNUSED(error);
#endif
    switch (dev->bus->busType) {
#ifdef USE_SPI
        case BUS_TYPE_SPI:
            // No waiting on SPI
            return false;
#endif

#ifdef USE_I2C
        case BUS_TYPE_I2C:
            return i2cBusBusy(dev, error);
#endif

        default:
            return false;
    }
}