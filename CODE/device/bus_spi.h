// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#ifndef _BUS_SPI_H
#define _BUS_SPI_H
#include "bus.h"

typedef struct spi_device_s
{
    //don't change those
    bus_t *bus;
    uint8_t id;

    //configure those following lines
    char name[20];

    // configure your gpio pin
    io_t pwrPin;
    io_t csPin;

    // configure dma
    bool useDMA;

    // operate function
    int (* initialize)(struct spi_device_s *, device_e);
    int (* read)(struct spi_device_s *, segment_t *segment);
    int (* write)(struct spi_device_s *, segment_t *segment);
}spi_device_t;

void waitSpiDevice(spi_device_t *spiDevice);
Status_t SPI_Register_Bus(spi_device_t *spiDevice, device_e device);
Status_t SPI_Transfer(spi_device_t *spiDevice, segment_t *segment);
void SPI_RxIrqHandler(spi_device_t *spiDevice);
#endif //_BUS_SPI_H
