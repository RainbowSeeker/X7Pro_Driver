// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#ifndef X7PRO_DRIVER_BAROMETER_H
#define X7PRO_DRIVER_BAROMETER_H
#include "bus.h"
#include "exti.h"

typedef enum
{
    BARO_STATE_TEMPERATURE_READ = 0,
    BARO_STATE_TEMPERATURE_SAMPLE,
    BARO_STATE_PRESSURE_START,
    BARO_STATE_PRESSURE_READ,
    BARO_STATE_PRESSURE_SAMPLE,
    BARO_STATE_TEMPERATURE_START,
    BARO_STATE_COUNT
}barometerState_e;

struct baro_s;

typedef void (*baroOpFuncPtr)(struct baro_s *baro);                       // baro start operation
typedef bool (*baroGetFuncPtr)(struct baro_s *baro);                       // baro read/get operation
typedef void (*baroCalculateFuncPtr)(int32_t *pressure, int32_t *temperature); // baro calculation (filled params are pressure and temperature)

// the 'u' in these variable names means 'uncompensated', 't' is temperature, 'p' pressure.
typedef struct baro_s
{
    device_t dev;

    bool combined_read;
    uint16_t ut_delay;
    uint16_t up_delay;
    baroOpFuncPtr start_ut;
    baroGetFuncPtr read_ut;
    baroGetFuncPtr get_ut;
    baroOpFuncPtr start_up;
    baroGetFuncPtr read_up;
    baroGetFuncPtr get_up;
    baroCalculateFuncPtr calculate;


    float altitude;
    int32_t temperature;                    // Use temperature for telemetry
    int32_t pressure;                       // Use pressure for telemetry


    bool (* init)(struct baro_s *);
    void (* updateCallback)(struct baro_s *);
}baro_t;

bool Baro_MspInit(baro_t *baro, detect_func_t detectFunc, const hw_config_t *hwConfig);
bool Baro_Init(baro_t *baro);
uint32_t Baro_Update(baro_t *baro, uint32_t currentTimeUs);
void baroStartCalibration(void);
void baroSetGroundLevel(void);
#endif //X7PRO_DRIVER_BAROMETER_H
