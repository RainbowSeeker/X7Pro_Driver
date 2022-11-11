// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#ifndef X7PRO_DRIVER_GYRO_H
#define X7PRO_DRIVER_GYRO_H
#include "sensor.h"
#include "bus.h"
#include "bus_spi.h"

typedef struct gyro_config_s {
    char *name;
    device_e device;
    io_t csPin;
    bool leadingEdge;
    uint8_t i2cBus;
    uint8_t i2cAddress;
    io_t extiPin;
} gyro_config_t;


typedef struct  gyro_s
{
    sensor_e detectedSensor;
    void (*initFn)(struct gyro_s *gyro);        // initialize function
    device_t dev;
}gyro_t;

void Gyro_Init(void);
#endif //X7PRO_DRIVER_GYRO_H
