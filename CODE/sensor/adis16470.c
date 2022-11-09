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

void ADIS_Init(void)
{
    if (adis16470.initialize(&adis16470, DEV_SPI1) == S_OK)
    {
        println("adis16470 initialize succeed!");
    }
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

    uint16_t  checknum = 0;
    for (int i = 0; i < 18; ++i)
    {
        checknum += pRxData[i+2];
    }

    if (checknum == swap_u16(rawValue->checknum))
    {
        println("\r\ncheck ok\r\n");
    }
    else
    {
        println("\r\ncheck error\r\n");
    }
}

void ADIS_Brust_Read(void)
{
    uint8_t buf[24] = {0};
    buf[0] = BURST_READ >> 8;
    buf[1] = BURST_READ & 0xff;
    segment_t segment[] = {
            {.pTxData = buf, .pRxData = (uint8_t *)&accValue, .len = 24, ADIS_Callback},
            {.pTxData = NULL, .pRxData = NULL, .len = 0, NULL}
    };
    adis16470.read(&adis16470, segment);
}
