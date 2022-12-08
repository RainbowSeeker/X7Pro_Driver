//// Copyright (c) 2022 By RainbowSeeker.
//
////
//// Created by 19114 on 2022/11/18.
////
//#include "board_config.h"
//#ifdef USE_SENSOR_SPI_ICM20689
//#include "accgyro_icm20689.h"
//#include "algo/math/maths.h"
//
//
//static bool ICM20689_Init(gyro_t *gyro);
//static void ICM20689_Callback(gyro_t *gyro)
//{
//    int16_t *pRxData = (int16_t *)gyro->accRaw;
//    for (int i = 0; i < 3; ++i)
//    {
//        gyro->acc[i] = (float )swap_i16(pRxData[i]) * GYRO_SCALE_2000DPS;
//        gyro->gyro[i] = (float )swap_i16(pRxData[i + 4]) * GYRO_SCALE_2000DPS;
//    }
//    gyro->temp = (float )swap_i16(pRxData[3]) * 1e-2;
//}
//
//
//gyro_t icm20689 = {
//        .init = ICM20689_Init,
//        .updateCallback = ICM20689_Callback,
//};
//
//
//
//void Print_ICM20689()
//{
//    for (int i = 0; i < 3; ++i)
//    {
//        println("gyro[%d]=%.2f, acc[%d]=%.2f, ", i, icm20689.gyro[i], i, icm20689.acc[i]);
//    }
//    println("AvgFreq=%d", icm20689.dev.extiStat.capAvgFreq);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////------------------------------------------
//
//device_e ICM20689_Detect(const device_t *dev)
//{
//    SPI_WriteReg(dev, MPU_RA_PWR_MGMT_1, ICM20689_BIT_RESET);
//    delay_ms(ICM20689_RESET_DELAY_MS);
//
//    uint8_t attemptsRemaining = 20;
//    while (attemptsRemaining--)
//    {
//        delay_ms(20);
//        uint8_t whoAmI = SPI_ReadRegMsk(dev, MPU_RA_WHO_AM_I);
//        if (whoAmI == ICM20689_WHO_AM_I_CONST)
//        {
//            // Disable Primary I2C Interface
//            SPI_WriteReg(dev, MPU_RA_USER_CTRL, ICM20689_I2C_IF_DIS);
//
//            // Reset the device signal paths
//            SPI_WriteReg(dev, MPU_RA_SIGNAL_PATH_RESET, ICM20689_ACCEL_RST | ICM20689_TEMP_RST);
//
//            delay_ms(ICM20689_PATH_RESET_DELAY_MS);
//
//            return ICM20689_SPI;
//        }
//    }
//
//    return DEV_NONE;
//}
//
//STATIC_BDMA_DATA_AUTO uint8_t icm20689Buf[GYRO_BUF_SIZE];
//
//static bool ICM20689_Init(gyro_t *gyro)
//{
//    const hw_config_t hwConfig = {
//            .name = "ICM20689", .busE = BUS_SPI6,
//            .csPin = {.port = GPIOE, .pin = GPIO_PIN_15},
//            .extiPin = {.port = GPIOH, .pin = GPIO_PIN_5}
//    };
//    const dr_config_t drConfig = {
//            .pTxData        = icm20689Buf,
//            .pRxData        = &icm20689Buf[GYRO_BUF_SIZE / 2],
//            .len            = 15,
//            .startDataReg   = MPU_RA_ACCEL_XOUT_H | 0x80,
//            .aligenment     = 1,
//    };
//    if (!Gyro_MspInit(gyro, ICM20689_Detect, &hwConfig, &drConfig))
//        return false;
//
//    const device_t *dev = &gyro->dev;
//    SPI_SetClkDivisor(dev, SPI_CalculateDivider(ICM20689_MAX_SPI_CLK_HZ));
//
//    // Device was already reset during detection so proceed with configuration
//    SPI_WriteReg(dev, MPU_RA_PWR_MGMT_1, INV_CLK_PLL);
//    delay_us(ICM20689_CLKSEL_SETTLE_US);
//    SPI_WriteReg(dev, MPU_RA_CONFIG, 6);
//    SPI_WriteReg(dev, MPU_RA_GYRO_CONFIG, INV_FSR_2000DPS << 3);
//    SPI_WriteReg(dev, MPU_RA_ACCEL_CONFIG, INV_FSR_16G << 3);
//    SPI_WriteReg(dev, MPU_RA_SMPLRT_DIV, 0);
//
//    // Data ready interrupt configuration
//    SPI_WriteReg(dev, MPU_RA_INT_PIN_CFG, ICM20689_INT_ANYRD_2CLEAR);
//
//    SPI_WriteReg(dev, MPU_RA_INT_ENABLE, MPU_RF_DATA_RDY_EN);
//    return true;
//}
//
//#endif