//
// Created by 19114 on 2022/10/24.
//

#ifndef STM32H743IIT6_HARD_SPI_H
#define STM32H743IIT6_HARD_SPI_H

#if USE_SPI
#include "main.h"
#include "spi.h"

#define HARD_SPIN       hspi2           //定义使用的SPI号


void SPI_Init();
void spi_send(SPI_HandleTypeDef *hspi, uint8_t *modata, uint32_t len);
#endif
#endif //STM32H743IIT6_HARD_SPI_H
