// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "accgyro_icm42688p.h"

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
