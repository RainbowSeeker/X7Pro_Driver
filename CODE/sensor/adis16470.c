// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#include "adis16470.h"
#include "swap.h"

spi_device_t adis16470 = {
        .name = "ADIS16470",
        .pwrPin = {.port = SENSORS_ON_Port, .pin = SENSORS_ON_Pin},
        .csPin = {.port = ADI_CS_Port, .pin = ADI_CS_Pin},
        .useDMA = 1,
        .initialize = SPI_Register_Bus,
        .read = SPI_Transfer,
        .write = SPI_Transfer
};

acc_value_t accValue = {0};

static int16_t ADIS_Read_ID(void)
{
    uint8_t buf[2] = {0};
    uint8_t rxData[2] = {0};
    buf[0] = PROD_ID >> 8;
    buf[1] = PROD_ID & 0xff;
    segment_t segment[] = {
            {.pTxData = buf, .pRxData = rxData, .len = 2, NULL},
            {.pTxData = NULL, .pRxData = NULL, .len = 0, NULL},
    };
    adis16470.read(&adis16470, &segment[0]);
    return (int16_t)(rxData[0] << 8 | rxData[1]);
}

void ADIS_Init(void)
{
    if (adis16470.initialize(&adis16470, DEV_SPI1) == S_OK)
    {
        println("adis16470 initialize succeed!");
    }
    else
    {
        println("adis16470 initialize failed!");
    }

//    while (ADIS_ID != ADIS_Read_ID());
}

static void ADIS_Callback(uint8_t *pRxData)
{
    acc_value_t *rawValue = (acc_value_t *)pRxData;
    for (int i = 0; i < 3; ++i)
    {
        rawValue->gyro[i] = swap_i16(rawValue->gyro[i]);
        rawValue->accl[i] = swap_i16(rawValue->accl[i]);
    }
    rawValue->temp = swap_i16(rawValue->temp);

    memcpy(&accValue, pRxData, sizeof(accValue));

#if 0
    uint16_t  checknum = 0;
    for (int i = 0; i < 18; ++i)
    {
        checknum += pRxData[i+2];
    }
    if (checknum == swap_u16(rawValue->checknum))
    {
        print("\r\ncheck ok\r\n");
    }
#endif
}



void ADIS_Brust_Read(void)
{
    if (!adis16470.id) return;
    STATIC_DMA_DATA_AUTO uint8_t txBuf[24] = {0};
    STATIC_DMA_DATA_AUTO uint8_t rxBuf[24] = {0};
    txBuf[0] = BURST_READ >> 8;
    txBuf[1] = BURST_READ & 0xff;
    segment_t segment[] = {
            {.pTxData = txBuf, .pRxData = rxBuf, .len = 24, ADIS_Callback},
            {.pTxData = NULL, .pRxData = NULL, .len = 0, NULL}
    };
    adis16470.read(&adis16470, &segment[0]);
}
