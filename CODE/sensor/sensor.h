// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#ifndef X7PRO_DRIVER_SENSOR_H
#define X7PRO_DRIVER_SENSOR_H
#include "bus.h"
#include "bus_spi.h"
#include "exti.h"
#include "accgyro.h"
#include "barometer.h"

#define SENSOR_NUM                 (SENSOR_ALLCOUNT - 2)

typedef enum
{
    SENSOR_NONE = 0,
#ifdef USE_SENSOR_SPI_ADIS16470
    ADIS16470_SPI,
#endif
#ifdef USE_SENSOR_SPI_ICM42688P
    ICM42688P_SPI,
#endif
    SENSOR_GYROCOUNT,
#ifdef USE_SENSOR_SPI_MS5611
    MS5611_SPI,
#endif
    SENSOR_ALLCOUNT,
}sensor_e;


typedef struct
{
    char *name;
    bus_e device;
    io_t csPin;
    bool leadingEdge;
    uint8_t i2cBus;
    uint8_t i2cAddress;
    io_t extiPin;
} sensor_hw_config_t;

typedef struct sensor_s
{
    sensor_e    detectedMPU;
    union
    {
        gyro_t gyro;
        baro_t baro;
    }u;

}sensor_t;

//typedef void *

extern sensor_t sensorDevice[SENSOR_NUM];

void Sensor_Init(void);
bool Sensor_Update(sensor_e sensorID);
void Sensor_Wait(sensor_e sensorID);
#endif //X7PRO_DRIVER_SENSOR_H
