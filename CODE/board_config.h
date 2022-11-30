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

//--------uart----------
//#define USE_UART1
//#define USE_UART2
//#define USE_UART3
//#define USE_UART4
//#define USE_UART5
//#define USE_UART6
#define USE_UART7
//#define USE_UART8
//#define USE_LPUART1
#if defined(USE_UART1) || defined(USE_UART2) || defined(USE_UART3) || defined(USE_UART4) || defined(USE_UART5) || defined(USE_UART6) || defined(USE_UART7) || defined(USE_UART8) || defined(USE_LPUART1)
#define USE_UART
#endif

//---------spi----------
#define USE_SPI1
#define USE_SPI2
//#define USE_SPI3
#define USE_SPI4
//#define USE_SPI5
#define USE_SPI6
#if defined(USE_SPI1) || defined(USE_SPI2) || defined(USE_SPI3) || defined(USE_SPI4) || defined(USE_SPI5) || defined(USE_SPI6)
#define USE_SPI
#endif




//---------sensor--------
#define SENSORS_ON_Port         GPIOE
#define SENSORS_ON_Pin          GPIO_PIN_3

//外部中断信息统计
#define ENABLE_EXIT_STAT

#define USE_SENSOR_SPI_ADIS16470
#define USE_SENSOR_SPI_ICM42688P
#define USE_SENSOR_SPI_ICM20689
#define USE_SENSOR_SPI_MS5611
#define USE_SENSOR_SPI_RM3100

#define USE_FRAM_FM25V05


