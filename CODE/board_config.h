//
// Created by 19114 on 2022/10/30.
//

#pragma once
#include "main.h"
//---------choose your os type----------------
#define USE_FREERTOS    1
#define USE_UCOS        0
#define SUPPORT_OS      (USE_FREERTOS | USE_UCOS)


#define SDEN_Pin GPIO_PIN_7
#define SDEN_GPIO_Port GPIOG
#define RM3100_Pin GPIO_PIN_2
#define RM3100_GPIO_Port GPIOF
#define ADI_CS_Pin GPIO_PIN_10
#define ADI_CS_GPIO_Port GPIOF
#define DRDY1_Pin GPIO_PIN_7
#define DRDY1_GPIO_Port GPIOE

//-----------hardware config------------------
#define EN_SPI          1
#define EN_UART         1

// Use DMA if possible if this many bytes are to be transferred
#define BUS_DMA_THRESHOLD 8

#if EN_SPI
//---------spi----------
#define SPI_DEV_NUM     1   //number of devices using spi

#define SPI_BUS_NUM     1   //number of spi
#define USE_SPI1

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
#define EN_ADIS             0

#define SENSORS_ON          HAL_GPIO_WritePin(SENSORS_ON_GPIO_Port, SENSORS_ON_Pin, GPIO_PIN_SET)

#define ADI_CS_LOW          HAL_GPIO_WritePin(ADI_CS_GPIO_Port, ADI_CS_Pin, GPIO_PIN_RESET)
#define ADI_CS_HIGH         HAL_GPIO_WritePin(ADI_CS_GPIO_Port, ADI_CS_Pin, GPIO_PIN_SET)

#define RM3100_CS_LOW       HAL_GPIO_WritePin(RM3100_GPIO_Port, RM3100_Pin, GPIO_PIN_RESET)
#define RM3100_CS_HIGH      HAL_GPIO_WritePin(RM3100_GPIO_Port, RM3100_Pin, GPIO_PIN_SET)





