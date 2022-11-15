// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#include "sensor.h"
#include "hw_config.h"
#include "accgyro_icm42688p.h"
#include "accgyro_adis16470.h"
#include "barometer_ms5611.h"
#include "maths.h"


FAST_DATA_ZERO_INIT sensor_t sensorDevice[SENSOR_NUM];

typedef uint8_t (*sensor_detect_func_t)(const device_t *dev);

static sensor_detect_func_t spiMpuDetectFuncTable[] = {
#ifdef USE_SENSOR_SPI_ADIS16470
        ADIS16470_Detect,
#endif
#ifdef USE_SENSOR_SPI_ICM42688P
        ICM426xx_Detect,
#endif
#ifdef USE_SENSOR_SPI_MS5611
        MS5611_Detect,
#endif
        NULL,
};

static bool SPISensor_Detect(sensor_t *sensor, const sensor_hw_config_t *config)
{
    device_t *dev = &sensor->u.gyro.dev;
    if (!config->csPin.port || !SPI_SetBusInstance(dev, config->device))
    {
        return false;
    }

    dev->name = config->name;
    SPI_SetClkPhasePolarity(dev, config->leadingEdge);

    dev->busType_u.spi.csPin = config->csPin;

    IO_Init(dev->busType_u.spi.csPin, CS_CONFIG);
    IO_Set(dev->busType_u.spi.csPin, IO_HIGH);

    // Allow 100ms before attempting to access SPI bus
    while (HAL_GetTick() < 100);

    // Set a slow SPI clock (1M) that all potential devices can handle during gyro detection
    SPI_SetClkDivisor(dev, SPI_CalculateDivider(1000000));

    sensor_e sensorID = SENSOR_NONE;
    for (uint8_t i = 0; spiMpuDetectFuncTable[i]; i++)
    {
        sensorID = (spiMpuDetectFuncTable[i])(dev);
        if (sensorID != SENSOR_NONE)
        {
            sensor->detectedMPU = sensorID;
            Bus_DeviceRegister(dev);
            return true;
        }
    }

    // Detection failed, disable CS pin again
    IO_DeInit(config->csPin);

    return false;
}

static bool Sensor_DetectFromConfig(sensor_t *sensor, const sensor_hw_config_t *config)
{
    // MPU datasheet specifies 30ms.
    delay_ms(35);

    if (config->device <= BUS_NULL || config->device >= BUS_ALLCOUNT || config->device == BUS_SPICOUNT)
    {
        return false;
    }
    else if (config->device < BUS_SPICOUNT) // spi Type
    {
        return SPISensor_Detect(sensor, config);
    }
    else    // I2C Type
    {
        assert(0);  //don't support yet.
    }

    return false;
}

static bool Sensor_DevInit(sensor_t *sensor, const sensor_hw_config_t *config)
{
    sensor->u.gyro.dev.deviceID = sensor->detectedMPU;
    sensor->u.gyro.dev.extiPin = &config->extiPin;
    if (sensor->detectedMPU < SENSOR_GYROCOUNT)     //gyro
    {
        return Gyro_Init(&sensor->u.gyro);
    }
    else if (sensor->detectedMPU < SENSOR_ALLCOUNT)    //baro
    {
        return Baro_Init(&sensor->u.baro);
    }
    return false;
}


void Sensor_Init(void)
{
    sensor_t *sensor = &sensorDevice[0];
    const sensor_hw_config_t *config = &sensorConfig[0];
    uint8_t sensorNum = SENSOR_NUM;

    while (sensorNum--)
    {
        if (Sensor_DetectFromConfig(sensor, config))
        {
            LOG_INFO("Detected Device[%d]: %s", sensor->detectedMPU, sensor->u.gyro.dev.name);

            if (Sensor_DevInit(sensor, config))
            {
                LOG_INFO("Device[%d]: %s Initialize succeed", sensor->detectedMPU, sensor->u.gyro.dev.name);
            }
            else
            {
                sensor->detectedMPU = SENSOR_NONE;
                LOG_ERROR("Cann't Initialize MPU Device: %s.\r\nPlease check your configuration.", sensor->u.gyro.dev.name);
            }
        }
        else
        {
            LOG_ERROR("Cann't detected %s", config->name);
        }
        sensor++;
        config++;
    }
}
static bool IsGyro(sensor_e sensorID)
{
    return (sensorID > SENSOR_NONE && sensorID < SENSOR_GYROCOUNT);
}
static bool IsBaro(sensor_e sensorID)
{
    return (sensorID > SENSOR_GYROCOUNT && sensorID < SENSOR_ALLCOUNT);
}

bool Sensor_Update(sensor_e sensorID)
{
    if (IsGyro(sensorID))
    {
        gyro_t *gyro = sensorDevice[sensorID - 1].detectedMPU == sensorID ? &sensorDevice[sensorID - 1].u.gyro : NULL;
        if (!gyro)
            return false;
        return Gyro_Update(gyro);
    }
    else if (IsBaro(sensorID))
    {
//        return Baro_Update()
    }
    return false;
}
void Sensor_Wait(sensor_e sensorID)
{
    if (IsGyro(sensorID))
    {
        gyro_t *gyro = sensorDevice[sensorID - 1].detectedMPU == sensorID ? &sensorDevice[sensorID - 1].u.gyro : NULL;
        if (!gyro)
            return;
        Gyro_Wait(gyro);
    }
}

