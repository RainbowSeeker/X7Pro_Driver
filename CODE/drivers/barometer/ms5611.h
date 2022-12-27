// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#ifndef X7PRO_DRIVER_MS5611_H
#define X7PRO_DRIVER_MS5611_H

#include <common.h>

// 10 MHz max SPI frequency
#define MS5611_MAX_SPI_CLK_HZ 7000000

// MS5611, Standard address 0x77
#define MS5611_I2C_ADDR                 0x77

#define ADDR_RESET_CMD  0x1E /* write to this address to reset chip */
#define ADDR_ADC        0x00 /* address of 3 bytes / 32bit pressure data */
#define ADDR_PROM_SETUP 0xA0 /* address of 8x 2 bytes factory and calibration data */
#define ADDR_PROM_C1    0xA2 /* address of 6x 2 bytes calibration data */
#define ADDR_PROM_C2    0xA4
#define ADDR_PROM_C3    0xA6
#define ADDR_PROM_C4    0xA8
#define ADDR_PROM_C5    0xAA
#define ADDR_PROM_C6    0xAC
#define ADDR_PROM_CRC   0xAE

#define BARO_OSR_256  0
#define BARO_OSR_512  1
#define BARO_OSR_1024 2
#define BARO_OSR_2048 3
#define BARO_OSR_4096 4

#define DEFAULT_OSR BARO_OSR_2048

err_t drv_ms5611_init(const char* baro_device_name);
#endif //X7PRO_DRIVER_MS5611_H
