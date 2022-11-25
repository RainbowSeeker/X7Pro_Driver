// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "board_config.h"
#ifdef USE_SENSOR_SPI_ADIS16470
#include <stdlib.h>
#include "accgyro_adis16470.h"
#include "algo/math/maths.h"


static bool ADIS16470_Init(gyro_t *gyro);
static void ADI_Callback(gyro_t *gyro)
{
    for (int i = 0; i < 3; ++i)     //adis 接收数据陀螺仪在前，故需要acc, gyro交换
    {
        gyro->gyro[i] = (float )swap_i16(gyro->accRaw[i]) * GYRO_SCALE_2000DPS;
        gyro->acc[i] = (float )swap_i16(gyro->gyroRaw[i]) * GYRO_SCALE_2000DPS;
    }
    gyro->temp = (float )swap_i16(gyro->tempRaw) * 1e-1;
}

gyro_t adis16470 = {
        .init = ADIS16470_Init,
        .updateCallback = ADI_Callback,
};


void Print_ADIS16470()
{
    for (int i = 0; i < 3; ++i)
    {
        println("gyro[%d]=%.2f, acc[%d]=%.2f, ", i, adis16470.gyro[i], i, adis16470.acc[i]);
    }
    println("AvgFreq=%d", adis16470.dev.extiStat.capAvgFreq);
}






//----------------------------------------------------

static bool ADI_VerifyDEVID(const device_t *dev)
{
    uint8_t txData[2] = {ADI_PROD_ID, 0};
    uint8_t rxData[2] = {0};

    SPI_ReadWriteBuf(dev, txData, rxData, 2);
    if (ADI_ID == (rxData[0] << 8 | rxData[1]))
    {
        return true;
    }
    return false;
}

static device_e ADIS16470_Detect(const device_t *dev)
{
    uint8_t attemptsRemaining = 20;
    while (attemptsRemaining--)
    {
        delay_ms(20);

        if (!ADI_VerifyDEVID(dev))
        {
            continue;
        }

        return ADIS16470_SPI;
    }
    return DEV_NONE;
}

STATIC_DMA_DATA_AUTO uint8_t adiBuf[ADI_BUF_SIZE];

static bool ADIS16470_Init(gyro_t *gyro)
{
    const hw_config_t hwConfig ={
            .name = "ADIS16470",
            .busE = BUS_SPI1,
            .leadingEdge = 0,
            .csPin = {.port = GPIOF, .pin = GPIO_PIN_10},
            .extiPin = {.port = GPIOE, .pin = GPIO_PIN_7}
    };
    const dr_config_t drConfig ={
            .pTxData        = adiBuf,
            .pRxData        = &adiBuf[ADI_BUF_SIZE/2],
            .len            = 24,
            .startDataReg   = BURST_READ,
            .aligenment     = 4,
            .transferSize   = 14,
    };
    if(!Gyro_MspInit(gyro, ADIS16470_Detect, &hwConfig, &drConfig))
        return false;

    return true;
}


static void ADI_CalChecknum(uint8_t *pRxData)
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