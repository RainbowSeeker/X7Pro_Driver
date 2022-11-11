// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "accgyro_adis16470.h"
#include "maths.h"
#include "sensor.h"


acc_value_t accValue = {0};


uint8_t ADIS16470_Detect(const device_t *dev)
{
    uint8_t txData[2] = {PROD_ID >> 8, PROD_ID & 0xff};
    uint8_t rxData[2] = {0};

    uint8_t detected = MPU_NONE;
    uint8_t attemptsRemaining = 20;
    while (attemptsRemaining--)
    {
        delay_ms(20);
        SPI_ReadWriteBuf(dev, txData, rxData, 2);
        const uint16_t whoAmI = rxData[0] << 8 | rxData[1];
        if (whoAmI == ADIS_ID)
        {
            detected = ADIS16470_SPI;
            break;
        }
        if (!attemptsRemaining)
        {
            return MPU_NONE;
        }
    }
    return detected;
}


static void ADIS_Callback(uint8_t *pRxData)
{
    acc_value_t *rawValue = (acc_value_t *)pRxData;
    for (int i = 0; i < 3; ++i)
    {
        rawValue->gyro[i] = __builtin_bswap16(rawValue->gyro[i]);
        rawValue->accl[i] = __builtin_bswap16(rawValue->accl[i]);
    }
    rawValue->temp = __builtin_bswap16(rawValue->temp);

    memcpy(&accValue, pRxData, sizeof(accValue));

#if 1
    uint16_t  checknum = 0;
    for (int i = 0; i < 18; ++i)
    {
        checknum += pRxData[i+2];
    }
    if (checknum == swap_u16(rawValue->checknum))
    {
        print("\r\n\r\ncheck ok\r\n\r\n");
    }
#endif
}



void ADIS_Brust_Read(void)
{
    STATIC_DMA_DATA_AUTO uint8_t txBuf[24] = {0};
    STATIC_DMA_DATA_AUTO uint8_t rxBuf[24] = {0};
    txBuf[0] = BURST_READ >> 8;
    txBuf[1] = BURST_READ & 0xff;

}
