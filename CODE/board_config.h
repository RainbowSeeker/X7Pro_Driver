//
// Created by 19114 on 2022/10/30.
//

#pragma once
#include "main.h"
//---------choose your os type----------------
#define USE_FREERTOS    1
#define USE_UCOS        0
#define SUPPORT_OS      (USE_FREERTOS | USE_UCOS)


//-----------hardware config------------------
#define EN_SPI          1
#define EN_UART         1

// Use DMA if possible if this many bytes are to be transferred
#define BUS_DMA_THRESHOLD 8

#if EN_SPI
//---------spi----------
#define SPI_DEV_NUM     2   //number of devices using spi

#define SPI_BUS_NUM     2   //number of spi
#define USE_SPI1
//#define USE_SPI2
//#define USE_SPI3
#define USE_SPI4

#else
#define SPI_BUS_NUM     0   //number of spi
#endif

#define BUS_NUM         (SPI_BUS_NUM)


#if EN_UART

//--------debug uart config-------------------
#define DEBUG_UART      (huart7)
#define DEBUG_EN_DMA    0
#define DEBUG_CONFIG    (DEBUG_EN_DMA && SUPPORT_OS)

#endif





//---------sensor--------
#define SENSORS_ON_Port         GPIOE
#define SENSORS_ON_Pin          GPIO_PIN_3




