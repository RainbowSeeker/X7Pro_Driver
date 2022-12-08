//// Copyright (c) 2022 By RainbowSeeker.
//
////
//// Created by 19114 on 2022/11/14.
////
//
//#ifndef X7PRO_DRIVER_BAROMETER_MS5611_H
//#define X7PRO_DRIVER_BAROMETER_MS5611_H
//#include "barometer.h"
//
//// 10 MHz max SPI frequency
//#define MS5611_MAX_SPI_CLK_HZ 10000000
//
//// MS5611, Standard address 0x77
//#define MS5611_I2C_ADDR                 0x77
//
//#define CMD_RESET               0x1E // ADC reset command
//#define CMD_ADC_READ            0x00 // ADC read command
//#define CMD_ADC_CONV            0x40 // ADC conversion command
//#define CMD_ADC_D1              0x00 // ADC D1 conversion
//#define CMD_ADC_D2              0x10 // ADC D2 conversion
//#define CMD_ADC_256             0x00 // ADC OSR=256
//#define CMD_ADC_512             0x02 // ADC OSR=512
//#define CMD_ADC_1024            0x04 // ADC OSR=1024
//#define CMD_ADC_2048            0x06 // ADC OSR=2048
//#define CMD_ADC_4096            0x08 // ADC OSR=4096
//#define CMD_PROM_RD             0xA0 // Prom read command
//#define PROM_NB                 8
//
//extern baro_t ms5611;
//#endif //X7PRO_DRIVER_BAROMETER_MS5611_H
