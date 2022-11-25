// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/17.
//

#include "fm25vx.h"
#include "algo/math/maths.h"
#include "bus_spi.h"

static bool FM25Vx_Init(fram_t *fram);
static void FM25Vx_Read(uint16_t address, uint8_t *buf, int len);
static void FM25Vx_Write(uint16_t address, uint8_t *buf, int len);

fram_t fm25vx = {
        .init = FM25Vx_Init,
        .read = FM25Vx_Read,
        .write = FM25Vx_Write,
};







//------------------------------------------

static void FM25Vx_WriteCommandByte(const device_t *dev, uint8_t data)
{
    segment_t segment[] = {
            {.u.buffers = {&data, NULL},  sizeof(data),  true, NULL},
            {.u.link = {NULL, NULL},     0,            true,  NULL},
    };

    SPI_Sequence(dev, &segment[0]);

    SPI_Wait(dev);
}

static void FM25Vx_Write(uint16_t address, uint8_t *buf, int len)
{
    fram_t *fram = &fm25vx;
    memset(fram->pTxData, 0, 36);
    fram->pTxData[0] = 0x02;
    for (int i = 0; i < len; i += 32)
    {
        int actLen=len-i;
        FM25Vx_WriteCommandByte(&fram->dev, 0x06);
        delay_ms(1);
        fram->pTxData[1] = (address>>8)&0xff;
        fram->pTxData[2] = address&0xff;
        memcpy(fram->pTxData + 3, buf + i, min(actLen, 32));
        SPI_ReadWriteBuf(&fram->dev, fram->pTxData, NULL, actLen + 3);
        SPI_Wait(&fram->dev);
        address += 32;
        delay_ms(1);

    }
}
static void FM25Vx_Read(uint16_t address, uint8_t *buf, int len)
{
    fram_t *fram = &fm25vx;
    memset(fram->pTxData, 0, 36);
    fram->pTxData[0] = 0x03;
    for (int i = 0; i < len;)
    {
        int actLen = len - i;
        int rxLen = min(actLen, 29);
        actLen = rxLen + !(rxLen & 1);
        fram->pTxData[1] = (address>>8)&0xff;
        fram->pTxData[2] = address&0xff;
        SPI_ReadWriteBuf(&fram->dev, fram->pTxData, fram->pRxData, rxLen + 3);
        SPI_Wait(&fram->dev);
        memcpy(buf + i, fram->pRxData + 3, rxLen);
        address += rxLen;
        i += rxLen;
        delay_ms(1);
    }
}

static device_e FM25V05_Detect(const device_t *dev)
{
    uint8_t buf[20] = {0x9F,};
    uint8_t attemptsRemaining = 20;
    while (attemptsRemaining--)
    {
        delay_ms(10);
        SPI_ReadWriteBuf(dev, buf, &buf[10], 10);
        if (buf[17] == 0xC2)
        {
            return FM25V05_SPI;
        }
    }
    return DEV_NONE;
}

STATIC_DMA_DATA_AUTO uint8_t fm25vxTxBuf[36];
STATIC_DMA_DATA_AUTO uint8_t fm25vxRxBuf[36];

static bool FM25Vx_Init(fram_t *fram)
{
    const hw_config_t fm25vx_config = {
            .name = "FM25V05", .busE = BUS_SPI2,
            .csPin = {.port = GPIOF, .pin = GPIO_PIN_5}
    };

    if (!Device_PreConfig(&fram->dev, FM25V05_Detect, &fm25vx_config, NULL))
    {
        return false;
    }

    fram->pTxData = fm25vxTxBuf;
    fram->pRxData = fm25vxRxBuf;
    return true;
}



