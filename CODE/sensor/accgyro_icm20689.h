// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/18.
//

#ifndef X7PRO_DRIVER_ACCGYRO_ICM20689_H
#define X7PRO_DRIVER_ACCGYRO_ICM20689_H
#include "accgyro.h"

// 8 MHz max SPI frequency
#define ICM20689_MAX_SPI_CLK_HZ     8000000

// Register 0x37 - INT_PIN_CFG / Pin Bypass Enable Configuration
#define ICM20689_INT_ANYRD_2CLEAR   0x10

// Register 0x68 - SIGNAL_PATH_RESET / Pin Bypass Enable Configuration
#define ICM20689_ACCEL_RST          0x02
#define ICM20689_TEMP_RST           0x01

// Register 0x6a - USER_CTRL / User Control
#define ICM20689_I2C_IF_DIS         0x10

// Register 0x6b - PWR_MGMT_1 / Power Management 1
#define ICM20689_BIT_RESET          0x80

/* Allow CLKSEL setting time to settle when PLL is selected
 *
 * Not specified in the ICM-20689 datasheet, but in the ICM-20690 datasheet,
 *
 * https://invensense.tdk.com/wp-content/uploads/2016/10/DS-000178-ICM-20690-v1.0.pdf
 *
 * says (section 10.11) that the clock selection takes ~20us to settle. Testing
 * has shown that 60us is required, so double to allow a margin
 */
#define ICM20689_CLKSEL_SETTLE_US   120

/* Not specified in the ICM-20689 datasheet, but in the MPU-6000 datasheet,
 *
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * says (section 4.28) suggest a delay of 100ms after a reset
 */
#define ICM20689_RESET_DELAY_MS     100

/* Not specified in the ICM-20689 datasheet, but in the MPU-6000 datasheet,
 *
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * says (section 4.28) suggest a delay of 100ms after a path reset
 */
#define ICM20689_PATH_RESET_DELAY_MS 100


extern gyro_t icm20689;
#endif //X7PRO_DRIVER_ACCGYRO_ICM20689_H
