// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "board_config.h"
#ifdef USE_SENSOR_SPI_ADIS16470
#include <stdlib.h>
#include "accgyro_adis16470.h"
#include "maths.h"


adi_value_t adiValue = {0};
static adi_value_t stageValue = {0};
STATIC_DMA_DATA_AUTO uint8_t adiBuf[ADI_BUF_SIZE];

static void ADI_Callback(uint8_t *pRxData);
bool ADIS16470_Init(gyro_t *gyro);

const gyro_config_t adi_config = {
        .gyroExtiMode   = GYRO_EXTI_INT_DMA,
        .maxClk         = ADI_MAX_SPI_CLK_HZ,
        .gyroDataReg    = BURST_READ,
        .pTxData        = adiBuf,
        .pRxData        = &adiBuf[ADI_BUF_SIZE/2],
        .transferDst    = (uint8_t *)&stageValue,
        .len            = 24,
        .initFunc       = ADIS16470_Init,
        .callback       = ADI_Callback,     //指定数据更新的回调函数
        .aligenment     = 4,
};



uint8_t ADIS16470_Detect(const device_t *dev)
{
    uint8_t txData[2] = {ADI_PROD_ID, 0};
    uint8_t rxData[2] = {0};

    uint8_t detected = SENSOR_NONE;
    uint8_t attemptsRemaining = 20;
    while (attemptsRemaining--)
    {
        delay_ms(20);
        SPI_ReadWriteBuf(dev, txData, rxData, 2);
        const uint16_t whoAmI = rxData[0] << 8 | rxData[1];
        if (whoAmI == ADI_ID)
        {
            detected = ADIS16470_SPI;
            break;
        }
        if (!attemptsRemaining)
        {
            return SENSOR_NONE;
        }
    }
    return detected;
}


bool ADIS16470_Init(gyro_t *gyro)
{
    UNUSED(gyro);
    return true;
}


static void ADI_Callback(uint8_t *pRxData)
{
    adi_value_t *pValue = (adi_value_t *)pRxData;
    for (int i = 0; i < 3; ++i)
    {
        adiValue.gyro[i] = __builtin_bswap16(pValue->gyro[i]);
        adiValue.acc[i] = __builtin_bswap16(pValue->acc[i]);
    }
    adiValue.temp = __builtin_bswap16(pValue->temp);
}


void ADI_CalChecknum(uint8_t *pRxData)
{
    uint16_t  checknum = 0;
    for (int i = 0; i < 18; ++i)
    {
        checknum += pRxData[i+2];
    }
    if (checknum == (uint16_t)(pRxData[20] << 8 | pRxData[21]))
    {
        print("\r\n\r\ncheck ok\r\n\r\n");
    }

}

#endif