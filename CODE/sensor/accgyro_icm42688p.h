// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef X7PRO_DRIVER_ACCGYRO_ICM42688P_H
#define X7PRO_DRIVER_ACCGYRO_ICM42688P_H
#include "bus_spi.h"
#include "cli/log.h"
#include "accgyro.h"

// 24 MHz max SPI frequency
#define ICM426XX_MAX_SPI_CLK_HZ 24000000

#define ICM426XX_RA_PWR_MGMT0                       0x4E
#define ICM426XX_PWR_MGMT0_ACCEL_MODE_LN            (3 << 0)
#define ICM426XX_PWR_MGMT0_GYRO_MODE_LN             (3 << 2)
#define ICM426XX_PWR_MGMT0_TEMP_DISABLE_OFF         (0 << 5)
#define ICM426XX_PWR_MGMT0_TEMP_DISABLE_ON          (1 << 5)

#define ICM426XX_RA_GYRO_CONFIG0                    0x4F
#define ICM426XX_RA_ACCEL_CONFIG0                   0x50

// --- Registers for gyro and acc Anti-Alias Filter ---------
#define ICM426XX_RA_GYRO_CONFIG_STATIC3             0x0C
#define ICM426XX_RA_GYRO_CONFIG_STATIC4             0x0D
#define ICM426XX_RA_GYRO_CONFIG_STATIC5             0x0E
#define ICM426XX_RA_ACCEL_CONFIG_STATIC2            0x03
#define ICM426XX_RA_ACCEL_CONFIG_STATIC3            0x04
#define ICM426XX_RA_ACCEL_CONFIG_STATIC4            0x05
// --- Register & setting for gyro and acc UI Filter --------
#define ICM426XX_RA_GYRO_ACCEL_CONFIG0              0x52
#define ICM426XX_ACCEL_UI_FILT_BW_LOW_LATENCY       (14 << 4)
#define ICM426XX_GYRO_UI_FILT_BW_LOW_LATENCY        (14 << 0)
// ----------------------------------------------------------

#define ICM426XX_RA_GYRO_DATA_X1                    0x25
#define ICM426XX_RA_ACCEL_DATA_X1                   0x1F

#define ICM426XX_RA_INT_CONFIG                      0x14
#define ICM426XX_INT1_MODE_PULSED                   (0 << 2)
#define ICM426XX_INT1_MODE_LATCHED                  (1 << 2)
#define ICM426XX_INT1_DRIVE_CIRCUIT_OD              (0 << 1)
#define ICM426XX_INT1_DRIVE_CIRCUIT_PP              (1 << 1)
#define ICM426XX_INT1_POLARITY_ACTIVE_LOW           (0 << 0)
#define ICM426XX_INT1_POLARITY_ACTIVE_HIGH          (1 << 0)

#define ICM426XX_RA_INT_CONFIG0                     0x63
#define ICM426XX_UI_DRDY_INT_CLEAR_ON_SBR           ((0 << 5) || (0 << 4))
#define ICM426XX_UI_DRDY_INT_CLEAR_ON_SBR_DUPLICATE ((0 << 5) || (0 << 4)) // duplicate settings in datasheet, Rev 1.2.
#define ICM426XX_UI_DRDY_INT_CLEAR_ON_F1BR          ((1 << 5) || (0 << 4))
#define ICM426XX_UI_DRDY_INT_CLEAR_ON_SBR_AND_F1BR  ((1 << 5) || (1 << 4))

#define ICM426XX_RA_INT_CONFIG1                     0x64
#define ICM426XX_INT_ASYNC_RESET_BIT                4
#define ICM426XX_INT_TDEASSERT_DISABLE_BIT          5
#define ICM426XX_INT_TDEASSERT_ENABLED              (0 << ICM426XX_INT_TDEASSERT_DISABLE_BIT)
#define ICM426XX_INT_TDEASSERT_DISABLED             (1 << ICM426XX_INT_TDEASSERT_DISABLE_BIT)
#define ICM426XX_INT_TPULSE_DURATION_BIT            6
#define ICM426XX_INT_TPULSE_DURATION_100            (0 << ICM426XX_INT_TPULSE_DURATION_BIT)
#define ICM426XX_INT_TPULSE_DURATION_8              (1 << ICM426XX_INT_TPULSE_DURATION_BIT)

#define ICM426XX_RA_INT_SOURCE0                     0x65
#define ICM426XX_UI_DRDY_INT1_EN_DISABLED           (0 << 3)
#define ICM426XX_UI_DRDY_INT1_EN_ENABLED            (1 << 3)



extern gyro_t icm42688;

void Print_ICM42688();
#endif //X7PRO_DRIVER_ACCGYRO_ICM42688P_H
