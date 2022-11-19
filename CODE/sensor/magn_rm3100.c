// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/16.
//

#include "board_config.h"
#ifdef USE_SENSOR_SPI_RM3100
#include "magn_rm3100.h"
#include "bus_spi.h"

#include "magn.h"



static bool RM3100_Init(magn_t *magn);
static void RM3100_Callback(magn_t *magn)
{
    for (uint8_t i = 0; i < 3; ++i)
    {
        magn->mag[i] = (float )(((magn->magRaw[3 * i]<<24)|(magn->magRaw[3 * i + 1]<<16)|magn->magRaw[3 * i + 2]<<8)>>8) * RM3100_SCALE;
    }
}

magn_t rm3100 = {
        .init = RM3100_Init,
        .updateCallback = RM3100_Callback,
};












//----------------------------

//upate rate enum
enum
{
    UR_600HZ = 0,
    UR_300HZ,
    UR_150HZ,
    UR_75HZ,
    UR_37HZ,
};

static bool RM3100_ModifyTMRC(const device_t *dev, uint8_t rate)
{
    uint8_t tmrcVal[5] = {
            [UR_600HZ] = 0x92,
            [UR_300HZ] = 0x93,
            [UR_150HZ] = 0x94,
            [UR_75HZ ] = 0x95,
            [UR_37HZ ] = 0x96,//default
    };
    SPI_WriteReg(dev, RM3100_TMRC, tmrcVal[rate]);

    //verify
    if (tmrcVal[rate] == SPI_ReadRegMsk(dev, RM3100_TMRC))
    {
        return true;
    }

    return false;
}

/**
 * set continuous mode (Bit0 = 1), DRDY to HIGH after a full measurement by CMX, CMY, CMZ
 * @param dev
 * @return
 */
static bool RM3100_ModifyCCM(const device_t *dev)
{
    uint8_t cmm = 0x71;
    SPI_WriteReg(dev, RM3100_CMM, cmm);

    //verify
    if (cmm == SPI_ReadRegMsk(dev, RM3100_CMM))
    {
        return true;
    }

    return false;
}

/**
 * verify the default cycle Count Registers
 * @param dev
 * @return
 */
static bool RM3100_VerifyCCV(const device_t *dev)
{
    uint8_t value[6];
    SPI_ReadRegMskBuf(dev, RM3100_CCX_M, value, 6);
    if (value[0] == 0x00 && value[1] == 0xC8
        && value[2] == 0x00 && value[3] == 0xC8
        && value[4] == 0x00 && value[5] == 0xC8)
    {
        return true;
    }
    return false;
}

/**
 * verify the revision identification
 * @param dev
 * @return
 */
static bool RM3100_VerifyREVID(const device_t *dev)
{
    if (RM3100_ID == SPI_ReadRegMsk(dev, RM3100_REVID))
    {
        return true;
    }
    return false;
}
device_e RM3100_Detect(const device_t *dev)
{
    uint16_t remainingTime = 20;
    while (remainingTime--)
    {
        delay_ms(10);
        if (RM3100_VerifyREVID(dev))
        {
            return RM3100_SPI;
        }
    }
    return DEV_NONE;
}

STATIC_DMA_DATA_AUTO uint8_t rmBuf[RM3100_BUF_SIZE];

static bool RM3100_Init(magn_t *magn)
{
    const hw_config_t hwConfig ={
            .name = "RM3100", .busE = BUS_SPI2,
            .csPin = {.port = GPIOF, .pin = GPIO_PIN_2},
            .extiPin = {.port = GPIOE, .pin = GPIO_PIN_4}
    };
    const dr_config_t drConfig ={
            .pTxData = rmBuf,
            .pRxData = &rmBuf[RM3100_BUF_SIZE/2],
            .len = 10,
            .startDataReg = RM3100_MX | 0x80,
            .aligenment = 1,
    };
    if(!Magn_MspInit(magn, RM3100_Detect, &hwConfig, &drConfig))
        return false;

    const device_t *dev = &magn->dev;
    SPI_SetClkDivisor(dev, SPI_CalculateDivider(RM3100_MAX_SPI_CLK_HZ));
    if (!RM3100_VerifyCCV(dev) || !RM3100_ModifyTMRC(dev, UR_150HZ))
    {
        return false;
    }
    while (!RM3100_ModifyCCM(dev));

    return true;
}





#endif