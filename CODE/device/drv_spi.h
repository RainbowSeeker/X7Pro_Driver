// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/10/30.
//

#ifndef DRV_SPI_H
#define DRV_SPI_H

#include "board_config.h"
#include "bus.h"

//#define SPI1_REG_SIZE			0x40
//extern ALIGN_32BYTES(uint8_t SPI1_RX_REG[SPI1_REG_SIZE]);





Status_t Drv_SPI_Init(bus_t *spiDev);
uint16_t SPI_TransferData16(uint16_t txData);
//void SPI_Transfer_DMA(spi_dev_t *spiDev, uint8_t *pTxData, uint8_t *pRxData, uint16_t len);
//void SPI_Transfer(spi_dev_t *spiDev, uint16_t *pTxData, uint16_t *pRxData, uint16_t len);
#endif //DRV_SPI_H
