// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#include "gyro.h"
#include "sensor.h"
#include "hw_config.h"
#include "accgyro_icm42688p.h"
#include "maths.h"
#include "accgyro_adis16470.h"

FAST_DATA_ZERO_INIT static gyro_t gyroSensor[GYRO_NUM];

typedef uint8_t (*gyro_detectFn_t)(const device_t *dev);

static gyro_detectFn_t gyroSpiDetectFnTable[] = {
#ifdef USE_GYRO_SPI_ADIS16470
        ADIS16470_Detect,
#endif
#ifdef USE_GYRO_SPI_ICM42688P
        ICM426xx_Detect,
#endif
        NULL,
};

bool SPISensor_Detect(gyro_t *gyro, const gyro_config_t *config)
{
    if (!config->csPin.port || !SPI_SetBusInstance(&gyro->dev, config->device)) {
        return false;
    }

    strcpy(gyro->dev.name, config->name);
    SPI_SetClkPhasePolarity(&gyro->dev, config->leadingEdge);

    gyro->dev.busType_u.spi.csPin = config->csPin;

    IO_Init(gyro->dev.busType_u.spi.csPin, CS_CONFIG);
    IO_Set(gyro->dev.busType_u.spi.csPin, IO_HIGH);

    // Allow 100ms before attempting to access SPI bus
    while (HAL_GetTick() < 100);

    // Set a slow SPI clock (1M) that all potential devices can handle during gyro detection
    SPI_SetClkDivisor(&gyro->dev, SPI_CalDivider(1000000));

    sensor_e sensor = MPU_NONE;
    for (size_t index = 0 ; gyroSpiDetectFnTable[index] ; index++) {
        sensor = (gyroSpiDetectFnTable[index])(&gyro->dev);
        if (sensor != MPU_NONE) {
            gyro->detectedSensor = sensor;
            Bus_DeviceRegister(&gyro->dev);
            return true;
        }
    }

    // Detection failed, disable CS pin again
    IO_DeInit(config->csPin);

    return false;
}

bool Gyro_Detect(gyro_t *gyro, const gyro_config_t *config)
{
    // MPU datasheet specifies 30ms.
    delay_ms(35);

    if (config->device <= DEV_NULL || config->device >= DEV_ALLCOUNT || config->device == DEV_SPICOUNT)
    {
        return false;
    }
    else if (config->device < DEV_SPICOUNT) // spi Type
    {
        return SPISensor_Detect(gyro, config);
    }
    else    // I2C Type
    {
        assert(0);  //don't support yet.
    }

    return false;
}

void Gyro_Init(void)
{
    for (uint8_t i = 0; i < GYRO_NUM; ++i)
    {
        if (Gyro_Detect(&gyroSensor[i], &gyroConfig[i]))
        {
            LOG_INFO("Detected Gyro Sensor[%d]: %s", gyroSensor[i].detectedSensor, gyroSensor[i].dev.name);
        }
        else
        {
            LOG_ERROR("Cann't detected %s", gyroConfig[i].name);
        }
    }
}

