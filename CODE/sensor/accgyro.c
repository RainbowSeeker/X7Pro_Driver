// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/12.
//

#include <stdlib.h>
#include "accgyro.h"
#include "accgyro_icm42688p.h"
#include "accgyro_adis16470.h"
#include "maths.h"
#include "nvic.h"

static void MPU_IntExtiHandler(exti_callback_rec_t *cb)
{
    gyro_t *gyro = (gyro_t *)container_of(cb, device_t, exti);

    uint32_t nowTick = HAL_GetTick();
    int32_t gyroLastPeriod = (int32_t) (nowTick - gyro->lastExtiTick);
    // This detects the short (~79us) EXTI interval of an MPU6xxx gyro
    if ((gyro->gyroShortPeriod == 0) || (gyroLastPeriod < gyro->gyroShortPeriod))
    {
        gyro->gyroSyncEXTI = gyro->lastExtiTick + gyro->gyroDmaMaxDuration;
    }

    gyro->lastExtiTick = nowTick;
    gyro->recordTime += gyroLastPeriod;
    gyro->intoExti++;

    if (gyro->intoExti % gyro->capAvgFreq == 0)
    {
        gyro->capAvgFreq = 1000 * gyro->intoExti / gyro->recordTime;
        gyro->recordTime = 0;
        gyro->intoExti = 0;
    }

    if (gyro->config->gyroExtiMode == GYRO_EXTI_INT_DMA)
    {
        SPI_Sequence(&gyro->dev, gyro->segments);
    }
}

static void MPU_IntExtiInit(gyro_t *gyro)
{
    gyro->dev.exti.fn = MPU_IntExtiHandler;
    EXTI_Config(*gyro->dev.extiPin, &gyro->dev.exti, NVIC_PRIO_EXTI, EXTI_RISING);
    EXTI_Enable(*gyro->dev.extiPin);
}

static bus_status_e Gyro_IntCallback(uint32_t arg)
{
    gyro_t *gyro = (gyro_t *) arg;
    int32_t gyroDmaDuration = (int32_t) (HAL_GetTick() - gyro->lastExtiTick);

    if (gyroDmaDuration > gyro->gyroDmaMaxDuration)
    {
        gyro->gyroDmaMaxDuration = gyroDmaDuration;
    }

    memcpy(gyro->config->transferDst, gyro->config->pRxData + gyro->config->aligenment, gyro->config->len - gyro->config->aligenment);

    gyro->dataReady = true;
    return BUS_READY;
}

static bool Gyro_PreConfig(gyro_t *gyro, const gyro_config_t *config)
{
    //check config is available.
    if (!gyro || !config || config->maxClk < 0 || config->pRxData < config->pTxData || !config->transferDst || !config->gyroDataReg || config->len < 0)
        return false;

    const device_t *dev = &gyro->dev;
    gyro->config = config;
    gyro->lastExtiTick = 0;
    gyro->gyroSyncEXTI = 0;
    gyro->gyroDmaMaxDuration = 0;
    gyro->gyroShortPeriod = 0;
    gyro->recordTime = 0;
    gyro->intoExti = 0;
    gyro->capAvgFreq = 1000;

    SPI_SetClkDivisor(dev, SPI_CalculateDivider(gyro->config->maxClk));

    if (gyro->config->initFunc)
    {
        if(gyro->config->initFunc(gyro) == false)    return false;
    }

    // Initialise the tx buffer to all 0xff
    memset(gyro->config->pTxData, 0xff, config->len);

    if (gyro->config->gyroExtiMode == GYRO_EXTI_INT_DMA)
    {
        if (gyro->dev.extiPin && SPI_UseDMA(&gyro->dev))
        {
            gyro->dev.callbackArg = (uint32_t)gyro;
            gyro->config->pTxData[0] = gyro->config->gyroDataReg;
            //configure segment for transfer
            memset(&gyro->segments[0], 0, sizeof(segment_t) * 2);
            gyro->segments[0].len = gyro->config->len;
            gyro->segments[0].callback = Gyro_IntCallback;
            gyro->segments[0].u.buffers.pTxData = gyro->config->pTxData;
            gyro->segments[0].u.buffers.pRxData = gyro->config->pRxData;
            gyro->segments[0].negateCS = true;
            gyro->segments[1].negateCS = true;
            MPU_IntExtiInit(gyro);
        }
        else
        {
            //don't support GYRO_EXTI_INT_DMA mode
            return false;
        }
    }
    return true;
}


bool Gyro_Init(gyro_t *gyro)
{
    const gyro_config_t *config;
    switch (gyro->dev.deviceID)
    {
#ifdef USE_SENSOR_SPI_ADIS16470
        case ADIS16470_SPI:
            config = &adi_config;
            break;
#endif
#ifdef USE_SENSOR_SPI_ICM42688P
        case ICM42688P_SPI:
            config = &icm426xx_config;
            break;
#endif
        default:
            return false;
    }

    return Gyro_PreConfig(gyro, config);
}

bool Gyro_Update(gyro_t *gyro)
{
    switch (gyro->config->gyroExtiMode)
    {
        case GYRO_EXTI_INT:
        case GYRO_EXTI_NO_INT:
        {
            gyro->config->pTxData[0] = gyro->config->gyroDataReg | 0x80;

            segment_t segments[] = {
                    {.u.buffers = {NULL, NULL}, 7, true, NULL},
                    {.u.link = {NULL, NULL},    0, true, NULL},
            };
            segments[0].u.buffers.pTxData = gyro->config->pTxData;
            segments[0].u.buffers.pRxData = gyro->config->pRxData;

            SPI_Sequence(&gyro->dev, &segments[0]);

            // Wait for completion
            SPI_Wait(&gyro->dev);
            break;
        }
        case GYRO_EXTI_INT_DMA:
        default:
            break;
    }

    if (gyro->config->callback)
    {
        gyro->config->callback(gyro->config->transferDst);
    }

    return true;
}


void Gyro_Wait(gyro_t *gyro)
{
    while (gyro->dataReady == false);
}

