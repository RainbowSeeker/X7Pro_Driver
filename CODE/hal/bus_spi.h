//// Copyright (c) 2022 By RainbowSeeker.
//
////
//// Created by 19114 on 2022/11/8.
////
//
//#ifndef _BUS_SPI_H
//#define _BUS_SPI_H
//#include "bus.h"
//
//// Use DMA if possible if this many bytes are to be transferred
//#define BUS_DMA_THRESHOLD   8
//#define BUS_SPI_FREE    0
//
//typedef struct spi_hw_s
//{
//    SPI_TypeDef *instance;
//    io_tag sck;
//    io_tag miso;
//    io_tag mosi;
//
//    uint8_t sckAF;
//    uint8_t misoAF;
//    uint8_t mosiAF;
//} spi_hw_t;
//
//void SPI_SetClkDivisor(const device_t *dev, uint16_t divisor);
//void SPI_SetClkPhasePolarity(const device_t *dev, bool leadingEdge);
//uint16_t SPI_CalculateDivider(uint32_t freq);
//bool SPI_SetBusInstance(device_t *dev, int device);
//void SPI_BusDeviceRegister(const device_t *dev);
//void SPI_InternalStopDMA(const device_t *dev);
//void SPI_SequenceStart(const device_t *dev);
//void SPI_Sequence(const device_t *dev, segment_t *segment);
//
//bool SPI_UseDMA(const device_t *dev);
//void SPI_Wait(const device_t *dev);
//bool SPI_IsBusy(const device_t *dev);
//void SPI_WriteReg(const device_t *dev, uint8_t reg, uint8_t data);
//bool SPI_WriteRegRB(const device_t *dev, uint8_t reg, uint8_t data);
//uint8_t SPI_ReadReg(const device_t *dev, uint8_t reg);
//uint8_t SPI_ReadRegMsk(const device_t *dev, uint8_t reg);
//void SPI_ReadRegBuf(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
//void SPI_ReadRegMskBuf(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
//bool SPI_ReadRegBufRB(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
//bool SPI_ReadRegMskBufRB(const device_t *dev, uint8_t reg, uint8_t *data, uint8_t length);
//void SPI_ReadWriteBuf(const device_t *dev, uint8_t *txData, uint8_t *rxData, int len);
//
//void SPI_BspInit(void);
//bool SPI_InitBusDMA(bus_e device);
//
//
//bool SPI_DeviceBindByHardware(device_t *dev, const hw_config_t *config);
//#endif //_BUS_SPI_H
