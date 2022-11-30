// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/12.
//

#include <stdlib.h>
#include "accgyro.h"
#include "accgyro_icm42688p.h"
#include "accgyro_adis16470.h"
#include "algo/math/maths.h"
#include "nvic.h"
#include "cli/log.h"
#include "sensor_hub.h"

static uint8_t imu_num = 0;

static bus_status_e Gyro_IntCallback(uint32_t arg)
{
    gyro_t *gyro = (gyro_t *)arg;

    memcpy(gyro->accRaw, gyro->dev.segments[0].u.buffers.pRxData + gyro->dev.aligenment, gyro->dev.transferSize);
    return BUS_READY;
}

bool Gyro_MspInit(gyro_t *gyro, detect_func_t detectFunc, const hw_config_t *hwConfig, const dr_config_t *drConfig)
{
    device_t *dev = &gyro->dev;
    if (!Device_PreConfig(dev, detectFunc, hwConfig, drConfig))
    {
        gyro->sampleMode = SAMPLE_NO_INIT;
        return false;
    }

    Device_BindRxCallback(dev, Gyro_IntCallback, (uint32_t)gyro);

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

bool Gyro_Init(gyro_t *gyro)
{
    if (gyro->init(gyro))
    {
        LOG_INFO("Initialized Gyro[%d]: %s", gyro->dev.deviceID, gyro->dev.name);
    }
    else
    {
        LOG_ERROR("Cann't Initialize Gyro Device: %s.\r\nPlease check your configuration.", gyro->dev.name);
        return false;
    }

    Gyro_StartSample(gyro);
    register_sensor_imu(NULL, NULL, imu_num++);
    return true;
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


