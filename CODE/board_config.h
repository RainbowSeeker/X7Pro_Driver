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
#define EN_UART         1

// Use DMA if possible if this many bytes are to be transferred
#define BUS_DMA_THRESHOLD   8


//---------spi----------
#define USE_SPI1
//#define USE_SPI2
//#define USE_SPI3
#define USE_SPI4
//#define USE_SPI5
//#define USE_SPI6
#if defined(USE_SPI1) || defined(USE_SPI2) || defined(USE_SPI3) || defined(USE_SPI4) || defined(USE_SPI5) || defined(USE_SPI6)
#define USE_SPI
#endif




#if EN_UART
//--------debug uart config-------------------
#define DEBUG_UART      (huart7)
#define DEBUG_EN_DMA    0
#define DEBUG_CONFIG    (DEBUG_EN_DMA && SUPPORT_OS)
#endif


//---------sensor--------
#define SENSORS_ON_Port         GPIOE
#define SENSORS_ON_Pin          GPIO_PIN_3


#define USE_SENSOR_SPI_ADIS16470
#define USE_SENSOR_SPI_ICM42688P
#define USE_SENSOR_SPI_MS5611




