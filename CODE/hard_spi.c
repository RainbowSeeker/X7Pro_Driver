//
// Created by 19114 on 2022/10/24.
//
#if USE_SPI
#include "hard_spi.h"


void SPI_Init()
{
    MX_SPI2_Init();
}

extern DMA_HandleTypeDef hdma_spi2_tx;

void spi_send(SPI_HandleTypeDef *hspi, uint8_t *modata, uint32_t len)
{
    HAL_SPI_Transmit_DMA(hspi, modata, len);
    while (hspi->State == HAL_SPI_STATE_BUSY_TX);

}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{

}

#endif