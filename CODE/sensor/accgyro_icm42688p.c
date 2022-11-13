// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "accgyro_icm42688p.h"
#include "maths.h"

icm_value_t icmValue = {0};

STATIC_DMA_DATA_AUTO uint8_t icm426xxBuf[GYRO_BUF_SIZE];

bool ICM426xx_Init(gyro_t *gyro);

const gyro_config_t icm426xx_config = {
        .gyroExtiMode   = GYRO_EXTI_INT_DMA,
        .maxClk         = ICM426XX_MAX_SPI_CLK_HZ,
        .gyroDataReg    = ICM426XX_RA_ACCEL_DATA_X1 | 0x80,
        .pTxData        = icm426xxBuf,
        .pRxData        = &icm426xxBuf[GYRO_BUF_SIZE/2],
        .transferDst    = (uint8_t *)&icmValue,
        .len            = 13,
        .scale          = GYRO_SCALE_2000DPS,
        .gyroDmaMaxDuration = 5,
        .initFunc       = ICM426xx_Init,
        .callback       = NULL,
        .aligenment     = 1,
};


typedef enum {
    ODR_CONFIG_8K = 0,
    ODR_CONFIG_4K,
    ODR_CONFIG_2K,
    ODR_CONFIG_1K,
    ODR_CONFIG_COUNT
} odr_config_e;

typedef enum {
    AAF_CONFIG_258HZ = 0,
    AAF_CONFIG_536HZ,
    AAF_CONFIG_997HZ,
    AAF_CONFIG_1962HZ,
    AAF_CONFIG_COUNT
} aaf_config_e;

typedef struct aaf_config_s {
    uint8_t delt;
    uint16_t deltSqr;
    uint8_t bitshift;
} aaf_config_t;

// Possible output data rates (ODRs)
static uint8_t odrLUT[ODR_CONFIG_COUNT] = {  // see GYRO_ODR in section 5.6
        [ODR_CONFIG_8K] = 3,
        [ODR_CONFIG_4K] = 4,
        [ODR_CONFIG_2K] = 5,
        [ODR_CONFIG_1K] = 6,
};

// Possible gyro Anti-Alias Filter (AAF) cutoffs
static aaf_config_t aafLUT[AAF_CONFIG_COUNT] = {  // see table in section 5.3
        [AAF_CONFIG_258HZ]  = {  6,   36, 10 },
        [AAF_CONFIG_536HZ]  = { 12,  144,  8 },
        [AAF_CONFIG_997HZ]  = { 21,  440,  6 },
        [AAF_CONFIG_1962HZ] = { 37, 1376,  4 },
};

uint8_t ICM426xx_Detect(const device_t *dev)
{
    SPI_WriteReg(dev, ICM426XX_RA_PWR_MGMT0, 0x00);

    uint8_t detected = MPU_NONE;
    uint8_t attemptsRemaining = 20;
    while (attemptsRemaining--)
    {
        delay_ms(20);
        const uint8_t whoAmI = SPI_ReadRegMsk(dev, MPU_RA_WHO_AM_I);
        switch (whoAmI)
        {
            case ICM42688P_WHO_AM_I_CONST:
                detected = ICM42688P_SPI;
                break;
            default:
                detected = MPU_NONE;
                break;
        }
        if (detected != MPU_NONE)
        {
            break;
        }
        if (!attemptsRemaining)
        {
            return MPU_NONE;
        }
    }

    return detected;
}

bool ICM426xx_Init(gyro_t *gyro)
{
    const device_t *dev = gyro->dev;
    SPI_WriteReg(dev, ICM426XX_RA_PWR_MGMT0, ICM426XX_PWR_MGMT0_TEMP_DISABLE_OFF | ICM426XX_PWR_MGMT0_ACCEL_MODE_LN | ICM426XX_PWR_MGMT0_GYRO_MODE_LN);
    delay_ms(15);

    // Get desired output data rate
    uint8_t odrConfig;
    const unsigned decim = llog2(gyro->mpuDividerDrops + 1);
    if (gyro->gyroRateKHz && decim < ODR_CONFIG_COUNT) {
        odrConfig = odrLUT[decim];
    } else {
        odrConfig = odrLUT[ODR_CONFIG_1K];
        gyro->gyroRateKHz = GYRO_RATE_1_kHz;
    }

    assert(INV_FSR_2000DPS == 3);
    SPI_WriteReg(dev, ICM426XX_RA_GYRO_CONFIG0, (3 - INV_FSR_2000DPS) << 5 | (odrConfig & 0x0F));
    delay_ms(15);

    assert(INV_FSR_16G == 3);
    SPI_WriteReg(dev, ICM426XX_RA_ACCEL_CONFIG0, (3 - INV_FSR_16G) << 5 | (odrConfig & 0x0F));
    delay_ms(15);

    // Configure gyro Anti-Alias Filter (see section 5.3 "ANTI-ALIAS FILTER")
    aaf_config_t aafConfig = aafLUT[AAF_CONFIG_258HZ];
    SPI_WriteReg(dev, ICM426XX_RA_GYRO_CONFIG_STATIC3, aafConfig.delt);
    SPI_WriteReg(dev, ICM426XX_RA_GYRO_CONFIG_STATIC4, aafConfig.deltSqr & 0xFF);
    SPI_WriteReg(dev, ICM426XX_RA_GYRO_CONFIG_STATIC5, (aafConfig.deltSqr >> 8) | (aafConfig.bitshift << 4));

    // Configure acc Anti-Alias Filter for 1kHz sample rate (see tasks.c)
    aafConfig = aafLUT[AAF_CONFIG_258HZ];
    SPI_WriteReg(dev, ICM426XX_RA_ACCEL_CONFIG_STATIC2, aafConfig.delt << 1);
    SPI_WriteReg(dev, ICM426XX_RA_ACCEL_CONFIG_STATIC3, aafConfig.deltSqr & 0xFF);
    SPI_WriteReg(dev, ICM426XX_RA_ACCEL_CONFIG_STATIC4, (aafConfig.deltSqr >> 8) | (aafConfig.bitshift << 4));

    // Configure gyro and acc UI Filters
    SPI_WriteReg(dev, ICM426XX_RA_GYRO_ACCEL_CONFIG0, ICM426XX_ACCEL_UI_FILT_BW_LOW_LATENCY | ICM426XX_GYRO_UI_FILT_BW_LOW_LATENCY);

    SPI_WriteReg(dev, ICM426XX_RA_INT_CONFIG, ICM426XX_INT1_MODE_PULSED | ICM426XX_INT1_DRIVE_CIRCUIT_PP | ICM426XX_INT1_POLARITY_ACTIVE_HIGH);
    SPI_WriteReg(dev, ICM426XX_RA_INT_CONFIG0, ICM426XX_UI_DRDY_INT_CLEAR_ON_SBR);

    SPI_WriteReg(dev, ICM426XX_RA_INT_SOURCE0, ICM426XX_UI_DRDY_INT1_EN_ENABLED);

    uint8_t intConfig1Value = SPI_ReadRegMsk(dev, ICM426XX_RA_INT_CONFIG1);
    // Datasheet says: "User should change setting to 0 from default setting of 1, for proper INT1 and INT2 pin operation"
    intConfig1Value &= ~(1 << ICM426XX_INT_ASYNC_RESET_BIT);
    intConfig1Value |= (ICM426XX_INT_TPULSE_DURATION_8 | ICM426XX_INT_TDEASSERT_DISABLED);

    SPI_WriteReg(dev, ICM426XX_RA_INT_CONFIG1, intConfig1Value);
    return true;
}
