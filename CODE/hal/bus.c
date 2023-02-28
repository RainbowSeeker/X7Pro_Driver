//// Copyright (c) 2022 By RainbowSeeker.
//
////
//// Created by 19114 on 2022/11/7.
////
//
//#include "bus.h"
//#include "bus_spi.h"
//
//#include "nvic.h"
//#include "algo/math/maths.h"
//
//
//static void Dev_ExtiIntHandler(exti_callback_rec_t *cb)
//{
//    light_device_t *dev = container_of(cb, light_device_t, extiCallbackRec);
//#ifdef ENABLE_EXIT_STAT
//    exti_stat_t *extiStat = &dev->extiStat;
//
//    uint32_t nowTick = HAL_GetTick();
//    int32_t lastPeriod = (int32_t) (nowTick - extiStat->lastExtiTick);
//    if ((extiStat->shortPeriod == 0) || (lastPeriod < extiStat->shortPeriod))
//    {
//        extiStat->syncEXTI = extiStat->lastExtiTick + extiStat->dmaMaxDuration;
//    }
//
//    extiStat->lastExtiTick = nowTick;
//    extiStat->recordTime += lastPeriod;
//    extiStat->intoExti++;
//
//    if (extiStat->intoExti % extiStat->capAvgFreq == 0)
//    {
//        extiStat->capAvgFreq = 1000 * extiStat->intoExti / extiStat->recordTime;
//        extiStat->recordTime = 0;
//        extiStat->intoExti = 0;
//    }
//#endif
//
//    SPI_Sequence(dev, dev->segments);
//}
//
//
//static bool Device_BindByHardware(light_device_t *dev, const hw_config_t *config)
//{
//    if (!config || !dev)    return false;
//
//    if (config->busE > BUS_NULL && config->busE < BUS_SPICOUNT)
//    {
//        return SPI_DeviceBindByHardware(dev, config);
//    }
//    else if (config->busE > BUS_SPICOUNT && config->busE < BUS_ALLCOUNT)
//    {
//        return false;
//    }
//    return false;
//}
//
//static bool Device_PreConfigDataReady(light_device_t *dev, const dr_config_t *config)
//{
//    if (!config)    return true;
//
//    //check config is available.
//    if (config->pRxData < config->pTxData || !config->startDataReg || config->len < 0)
//        return false;
//
//    memset(config->pTxData, 0xff, config->len);
//    memset(&dev->segments[0], 0, sizeof(segment_t) * 2);
//
//    config->pTxData[0] = config->startDataReg;
//    dev->segments[0].len = config->len;
//    dev->segments[0].callback = NULL;
//    dev->segments[0].u.buffers.pTxData = config->pTxData;
//    dev->segments[0].u.buffers.pRxData = config->pRxData;
//    dev->segments[0].negateCS = true;
//    dev->segments[1].negateCS = true;
//    dev->callbackArg = (uint32_t) 0;
//    dev->transferSize = config->transferSize == 0 ? config->len - config->aligenment : config->transferSize;
//    dev->aligenment = config->aligenment;
//    return true;
//}
//
//
//static bool Device_PreConfigHardware(light_device_t *dev, detect_func_t detectFunc, const hw_config_t *hwConfig)
//{
//    if (!dev || !hwConfig || !Device_BindByHardware(dev, hwConfig))
//        return false;
//
//    dev->deviceID = detectFunc(dev);
//
//    if (dev->deviceID <= DEV_NONE || dev->deviceID >=DEV_ALLCOUNT)
//        return false;
//
//    dev->extiPin = hwConfig->extiPin;
//    if (1)
//    {
//        dev->extiCallbackRec.fn = Dev_ExtiIntHandler;
//        EXTI_Config(dev->extiPin, &dev->extiCallbackRec, NVIC_PRIO_EXTI, EXTI_RISING);
//        EXTI_Disable(dev->extiPin);
//
//#ifdef ENABLE_EXIT_STAT
//        dev->extiStat.lastExtiTick = 0;
//
//
//        dev->extiStat.syncEXTI = 0;
//        dev->extiStat.dmaMaxDuration = 0;
//        dev->extiStat.shortPeriod = 0;
//        dev->extiStat.recordTime = 0;
//        dev->extiStat.intoExti = 0;
//        dev->extiStat.capAvgFreq = 100;
//#endif
//    }
//
//    return true;
//}
//
//
//bool Device_PreConfig(light_device_t *dev, detect_func_t detectFunc, const hw_config_t *hwConfig, const dr_config_t *drConfig)
//{
//    if (!Device_PreConfigHardware(dev, detectFunc, hwConfig) || !Device_PreConfigDataReady(dev, drConfig))
//    {
//        return false;
//    }
//    return true;
//}
//
//void Device_BindRxCallback(light_device_t *dev, segment_callback callback, uint32_t arg)
//{
//    dev->segments[0].callback = callback;
//    dev->callbackArg = (uint32_t) arg;
//}
//
//
//
//
//
//
//
//
//void Bus_DeviceRegister(const light_device_t *dev)
//{
//    switch (dev->bus->busType) {
//#ifdef USE_SPI
//        case BUS_TYPE_SPI:
//        SPI_BusDeviceRegister(dev);
//        break;
//#endif
//#ifdef EN_I2C
//        case BUS_TYPE_I2C:
//        i2cBusDeviceRegister(dev);
//        break;
//#endif
//        default:
//            break;
//    }
//}
//
//// Write routines where the register is masked with 0x7f
//bool Bus_WriteRegister(const light_device_t *dev, uint8_t reg, uint8_t data)
//{
//#if !defined(USE_SPI) && !defined(USE_I2C)
//    UNUSED(reg);
//    UNUSED(data);
//#endif
//    switch (dev->bus->busType) {
//#ifdef USE_SPI
//        case BUS_TYPE_SPI:
//            return SPI_WriteRegRB(dev, reg & 0x7f, data);
//#endif
//#ifdef USE_I2C
//        case BUS_TYPE_I2C:
//            return i2cBusWriteRegister(dev, reg, data);
//#endif
//        default:
//            return false;
//    }
//}
//
//bool Bus_WriteRegisterStart(const light_device_t *dev, uint8_t reg, uint8_t data)
//{
//#if !defined(USE_SPI) && !defined(USE_I2C)
//    UNUSED(reg);
//    UNUSED(data);
//#endif
//    switch (dev->bus->busType) {
//#ifdef USE_SPI
//        case BUS_TYPE_SPI:
//            return SPI_WriteRegRB(dev, reg & 0x7f, data);
//#endif
//#ifdef USE_I2C
//            case BUS_TYPE_I2C:
////        return i2cBusWriteRegisterStart(dev, reg, data);
//#endif
//        default:
//            return false;
//    }
//}
//
//// Access routines where the register is accessed directly
//bool Bus_RawWriteRegister(const light_device_t *dev, uint8_t reg, uint8_t data)
//{
//#ifdef USE_SPI
//    if (dev->bus->busType ==  BUS_TYPE_SPI) {
//        return SPI_WriteRegRB(dev, reg, data);
//    } else
//#endif
//    {
//        return Bus_WriteRegister(dev, reg, data);
//    }
//}
//
//bool Bus_RawWriteRegisterStart(const light_device_t *dev, uint8_t reg, uint8_t data)
//{
//#ifdef USE_SPI
//    if (dev->bus->busType ==  BUS_TYPE_SPI) {
//        return SPI_WriteRegRB(dev, reg, data);
//    } else
//#endif
//    {
//        return Bus_WriteRegisterStart(dev, reg, data);
//    }
//}
//
//// Read routines where the register is ORed with 0x80
//bool Bus_ReadRegisterBuffer(const light_device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
//{
//#if !defined(USE_SPI) && !defined(USE_I2C)
//    UNUSED(reg);
//    UNUSED(data);
//    UNUSED(length);
//#endif
//    switch (dev->bus->busType) {
//#ifdef USE_SPI
//        case BUS_TYPE_SPI:
//            return SPI_ReadRegMskBufRB(dev, reg | 0x80, data, length);
//#endif
//#ifdef USE_I2C
//        case BUS_TYPE_I2C:
//            return i2cBusReadRegisterBuffer(dev, reg, data, length);
//#endif
//        default:
//            return false;
//    }
//}
//
//bool Bus_RawReadRegisterBuffer(const light_device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
//{
//#ifdef USE_SPI
//    if (dev->bus->busType == BUS_TYPE_SPI) {
//        return SPI_ReadRegBufRB(dev, reg, data, length);
//    } else
//#endif
//    {
//        return Bus_ReadRegisterBuffer(dev, reg, data, length);
//    }
//}
//
//bool Bus_RawReadRegisterBufferStart(const light_device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
//{
//#ifdef USE_SPI
//    if (dev->bus->busType == BUS_TYPE_SPI) {
//        return SPI_ReadRegBufRB(dev, reg, data, length);
//    } else
//#endif
//    {
//        return Bus_ReadRegisterBufferStart(dev, reg, data, length);
//    }
//}
//
//
//// Start the I2C read, but do not wait for completion
//bool Bus_ReadRegisterBufferStart(const light_device_t *dev, uint8_t reg, uint8_t *data, uint8_t length)
//{
//#if !defined(USE_SPI) && !defined(USE_I2C)
//    UNUSED(reg);
//    UNUSED(data);
//    UNUSED(length);
//#endif
//    switch (dev->bus->busType) {
//#ifdef USE_SPI
//        case BUS_TYPE_SPI:
//            // For SPI allow the transaction to complete
//            return SPI_ReadRegMskBufRB(dev, reg | 0x80, data, length);
//#endif
//#ifdef USE_I2C
//            case BUS_TYPE_I2C:
//        // Initiate the read access
//        return i2cBusReadRegisterBufferStart(dev, reg, data, length);
//#endif
//        default:
//            return false;
//    }
//}
//
//
//// Returns true if bus is still busy
//bool Bus_Busy(const light_device_t *dev, bool *error)
//{
//#if !defined(USE_I2C)
//    UNUSED(error);
//#endif
//    switch (dev->bus->busType) {
//#ifdef USE_SPI
//        case BUS_TYPE_SPI:
//            // No waiting on SPI
//            return false;
//#endif
//
//#ifdef USE_I2C
//        case BUS_TYPE_I2C:
//            return i2cBusBusy(dev, error);
//#endif
//
//        default:
//            return false;
//    }
//}