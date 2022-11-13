// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#include "mpu.h"
#include "hw_config.h"
#include "accgyro_icm42688p.h"
#include "accgyro_adis16470.h"
#include "maths.h"


FAST_DATA_ZERO_INIT mpu_t mpuDevice[MPU_NUM];

typedef uint8_t (*mpu_detect_func_t)(const device_t *dev);

static mpu_detect_func_t spiMpuDetectFuncTable[] = {
#ifdef USE_MPU_SPI_ADIS16470
        ADIS16470_Detect,
#endif
#ifdef USE_MPU_SPI_ICM42688P
        ICM426xx_Detect,
#endif
        NULL,
};

static bool SPISensor_Detect(mpu_t *mpu, const mpu_hwconfig_t *config)
{
    if (!config->csPin.port || !SPI_SetBusInstance(&mpu->dev, config->device))
    {
        return false;
    }

    mpu->dev.name = config->name;
    SPI_SetClkPhasePolarity(&mpu->dev, config->leadingEdge);

    mpu->dev.busType_u.spi.csPin = config->csPin;

    IO_Init(mpu->dev.busType_u.spi.csPin, CS_CONFIG);
    IO_Set(mpu->dev.busType_u.spi.csPin, IO_HIGH);

    // Allow 100ms before attempting to access SPI bus
    while (HAL_GetTick() < 100);

    // Set a slow SPI clock (1M) that all potential devices can handle during gyro detection
    SPI_SetClkDivisor(&mpu->dev, SPI_CalDivider(1000000));

    mpu_e sensor = MPU_NONE;
    for (uint8_t i = 0; spiMpuDetectFuncTable[i]; i++)
    {
        sensor = (spiMpuDetectFuncTable[i])(&mpu->dev);
        if (sensor != MPU_NONE)
        {
            mpu->detectedMPU = sensor;
            Bus_DeviceRegister(&mpu->dev);
            return true;
        }
    }

    // Detection failed, disable CS pin again
    IO_DeInit(config->csPin);

    return false;
}

static bool MPU_DetectFromConfig(mpu_t *mpu, const mpu_hwconfig_t *config)
{
    // MPU datasheet specifies 30ms.
    delay_ms(35);

    if (config->device <= DEV_NULL || config->device >= DEV_ALLCOUNT || config->device == DEV_SPICOUNT)
    {
        return false;
    }
    else if (config->device < DEV_SPICOUNT) // spi Type
    {
        return SPISensor_Detect(mpu, config);
    }
    else    // I2C Type
    {
        assert(0);  //don't support yet.
    }

    return false;
}

static bool MPU_DevInit(mpu_t *mpu, const mpu_hwconfig_t *config)
{
    if (mpu->detectedMPU < MPU_GYROCOUNT)
    {
        mpu->u.gyro.gyroID = mpu->detectedMPU;
        mpu->u.gyro.dev = &mpu->dev;
        mpu->u.gyro.extiPin = &config->extiPin;

        return Gyro_Init(&mpu->u.gyro);
    }
    else
    {
        return false;
    }
}


void MPU_Init(void)
{
    mpu_t *mpu = &mpuDevice[0];
    const mpu_hwconfig_t *config = &mpuConfig[0];
    uint8_t mpuNum = MPU_NUM;

    memset(mpu, 0, sizeof(mpu_t) * MPU_NUM);
    while (mpuNum--)
    {
        if (MPU_DetectFromConfig(mpu, config))
        {
            LOG_INFO("Detected MPU Device[%d]: %s", mpu->detectedMPU, mpu->dev.name);

            if (MPU_DevInit(mpu, config))
            {
                LOG_INFO("MPU Device[%d]: %s Initialize succeed", mpu->detectedMPU, mpu->dev.name);
            }
            else
            {
                mpu->detectedMPU = MPU_NONE;
                LOG_ERROR("Cann't Initialize MPU Device[%d]: %s.\r\nPlease check your configuration.", mpu->detectedMPU, mpu->dev.name);
            }
        }
        else
        {
            LOG_ERROR("Cann't detected %s", config->name);
        }
        mpu++;
        config++;
    }
}
static bool IsGyro(mpu_e mpuID)
{
    if (mpuID > MPU_NONE && mpuID < MPU_GYROCOUNT)
        return true;
    return false;
}

bool MPU_Update(mpu_e mpuID)
{
    if (IsGyro(mpuID))
    {
        gyro_t *gyro = mpuDevice[mpuID - 1].detectedMPU == mpuID ? &mpuDevice[mpuID - 1].u.gyro : NULL;
        if (!gyro)
            return false;
        return Gyro_Update(gyro);
    }
    return false;
}
void MPU_Wait(mpu_e mpuID)
{
    if (IsGyro(mpuID))
    {
        gyro_t *gyro = mpuDevice[mpuID - 1].detectedMPU == mpuID ? &mpuDevice[mpuID - 1].u.gyro : NULL;
        if (!gyro)
            return;
        Gyro_Wait(gyro);
    }
}

