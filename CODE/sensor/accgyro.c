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
#include "log.h"

static bus_status_e Gyro_IntCallback(uint32_t arg)
{
    gyro_t *gyro = (gyro_t *)arg;

    memcpy(gyro->accRaw, gyro->dev.segments[0].u.buffers.pRxData + gyro->dev.aligenment, gyro->dev.transferSize);
    return BUS_READY;
}

bool Gyro_MspInit(gyro_t *gyro, detect_func_t detectFunc, const hw_config_t *hwConfig, const dr_config_t *drConfig)
{
    device_t *dev = &gyro->dev;
    if (Device_PreConfigHardware(dev, detectFunc, hwConfig) && Device_PreConfigDataReady(dev, drConfig))
    {
        LOG_INFO("Detected Gyro[%d]: %s", dev->deviceID, dev->name);
    }
    else
    {
        gyro->sampleMode = SAMPLE_NO_INIT;
        LOG_ERROR("Cann't Initialize Gyro Device: %s.\r\nPlease check your configuration.", dev->name);
        return false;
    }

    dev->callbackArg = (uint32_t)gyro;
    dev->segments[0].callback = Gyro_IntCallback;

    if (gyro->dev.extiPin.port)
    {
        gyro->sampleMode = !SPI_UseDMA(dev);
    }
    else    gyro->sampleMode = SAMPLE_NO_INT;

    return true;
}
void Gyro_StartSample(gyro_t *gyro)
{
    EXTI_Enable(gyro->dev.extiPin);
}

void Gyro_StopSample(gyro_t *gyro)
{
    EXTI_Disable(gyro->dev.extiPin);
}

bool Gyro_Update(gyro_t *gyro)
{
    switch (gyro->sampleMode)
    {
        case SAMPLE_NO_INT:
        {
            SPI_Sequence(&gyro->dev, &gyro->dev.segments[0]);

            // Wait for completion
            SPI_Wait(&gyro->dev);
        }
        case SAMPLE_EXTI_INT:
        case SAMPLE_EXTI_INT_DMA:
            if (gyro->updateCallback)
            {
                gyro->updateCallback(gyro);
            }
        default:
            break;
    }

    return true;
}


