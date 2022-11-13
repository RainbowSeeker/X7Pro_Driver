// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/12.
//

#ifndef X7PRO_DRIVER_ACCGYRO_H
#define X7PRO_DRIVER_ACCGYRO_H
#include "exti.h"
#include "bus_spi.h"

#define GYRO_SCALE_2000DPS              (2000.0f / (1 << 15))   // 16.384 dps/lsb scalefactor for 2000dps sensors
#define GYRO_SCALE_4000DPS              (4000.0f / (1 << 15))   //  8.192 dps/lsb scalefactor for 4000dps sensors

#define GYRO_BUF_SIZE                   32


enum gyro_fsr_e {
    INV_FSR_250DPS = 0,
    INV_FSR_500DPS,
    INV_FSR_1000DPS,
    INV_FSR_2000DPS,
    NUM_GYRO_FSR
};

enum accel_fsr_e {
    INV_FSR_2G = 0,
    INV_FSR_4G,
    INV_FSR_8G,
    INV_FSR_16G,
    NUM_ACCEL_FSR
};


typedef enum {
    GYRO_RATE_1_kHz,
    GYRO_RATE_1100_Hz,
    GYRO_RATE_3200_Hz,
    GYRO_RATE_6400_Hz,
    GYRO_RATE_6664_Hz,
    GYRO_RATE_8_kHz,
    GYRO_RATE_9_kHz,
    GYRO_RATE_32_kHz,
}gyro_rate_e;

typedef enum {
    GYRO_EXTI_INT_DMA = 0,
    GYRO_EXTI_INT,
    GYRO_EXTI_NO_INT
}gyro_mode_e;

struct gyro_s;
typedef struct
{
    uint32_t maxClk;
    uint8_t *pTxData;
    uint8_t *pRxData;
    uint8_t *transferDst;
    int16_t len;
    uint8_t gyroDataReg;

    float scale;                                // scalefactor
    gyro_mode_e gyroExtiMode;
    // Check that minimum number of interrupts have been detected
    // We need some offset from the gyro interrupts to ensure sampling after the interrupt
    int32_t gyroDmaMaxDuration;
    uint8_t aligenment;

    bool (*initFunc)(struct gyro_s *gyro);        // init function
    void (*callback)(uint8_t *pRxData);
}gyro_config_t;

typedef struct gyro_s
{
    uint8_t     gyroID;
    device_t    *dev;

    segment_t segments[2];
    volatile bool dataReady;

    const gyro_config_t *config;
    gyro_rate_e gyroRateKHz;
    uint8_t mpuDividerDrops;

    const io_t *extiPin;
    exti_callback_rec_t exti;
    uint32_t lastExtiTick;
//    uint32_t detectedExti;
    uint32_t gyroSyncEXTI;
    int32_t gyroShortPeriod;
}gyro_t;



bool Gyro_Init(gyro_t *gyro);
bool Gyro_Update(gyro_t *gyro);
void Gyro_Wait(gyro_t *gyro);
#endif //X7PRO_DRIVER_ACCGYRO_H
