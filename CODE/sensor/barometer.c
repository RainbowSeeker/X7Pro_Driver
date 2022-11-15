// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//

#include "barometer.h"
#include "sensor.h"
#include "barometer_ms5611.h"

#define NUM_CALIBRATION_CYCLES   100        // 10 seconds init_delay + 100 * 25 ms = 12.5 seconds before valid baro altitude
#define NUM_GROUND_LEVEL_CYCLES   10        // calibrate baro to new ground level (10 * 25 ms = ~250 ms non blocking)

static uint16_t calibrationCycles = 0;      // baro calibration = get new ground pressure value
static float baroGroundAltitude = 0.0f;
static bool baroCalibrated = false;
static bool baroReady = false;

bool Baro_Init(baro_t *baro)
{
    switch (baro->dev.deviceID)
    {
#ifdef USE_SENSOR_SPI_MS5611
        case MS5611_SPI:
            baroReady = MS5611_Init(baro);
            break;
#endif
        default:
            return false;
    }
    return baroReady;
}

static float PressureToAltitude(const float pressure)
{
    return (1.0f - pow(pressure / 101325.0f, 0.190295f)) * 4433000.0f;
}

static void PerformBaroCalibrationCycle(const float altitude)
{
    static uint16_t cycleCount = 0;

    baroGroundAltitude += altitude;
    cycleCount++;

    if (cycleCount >= calibrationCycles) {
        baroGroundAltitude /= cycleCount;  // simple average
        baroCalibrated = true;
        cycleCount = 0;
    }
}
bool BaroIsCalibrated(void)
{
    return baroCalibrated;
}

static void baroSetCalibrationCycles(uint16_t calibrationCyclesRequired)
{
    calibrationCycles = calibrationCyclesRequired;
}

void baroStartCalibration(void)
{
    baroSetCalibrationCycles(NUM_CALIBRATION_CYCLES);
    baroGroundAltitude = 0;
    baroCalibrated = false;
}

void baroSetGroundLevel(void)
{
    baroSetCalibrationCycles(NUM_GROUND_LEVEL_CYCLES);
    baroGroundAltitude = 0;
    baroCalibrated = false;
}

uint32_t Baro_Update(baro_t *baro, uint32_t currentTimeUs)
{
    static uint32_t baroStateDurationUs[BARO_STATE_COUNT];
    static barometerState_e state = BARO_STATE_TEMPERATURE_START;
    barometerState_e oldState = state;
    uint32_t executeTimeUs;
    uint32_t sleepTime = 1000; // Wait 1ms between states


    if (Bus_Busy(&baro->dev, NULL))
    {
        // If the bus is busy, simply return to have another go later
        return sleepTime;
    }

    switch (state)
    {
        default:
        case BARO_STATE_TEMPERATURE_START:
            baro->start_ut(baro);
            state = BARO_STATE_TEMPERATURE_READ;
            sleepTime = baro->ut_delay;
            break;
        case BARO_STATE_TEMPERATURE_READ:
            if (baro->read_ut(baro))
            {
                state = BARO_STATE_TEMPERATURE_SAMPLE;
            }
            break;
        case BARO_STATE_TEMPERATURE_SAMPLE:
            if (baro->get_ut(baro))
            {
                state = BARO_STATE_PRESSURE_START;
            }
            break;
        case BARO_STATE_PRESSURE_START:
            baro->start_up(baro);
            state = BARO_STATE_PRESSURE_READ;
            sleepTime = baro->up_delay;
            break;
        case BARO_STATE_PRESSURE_READ:
            if (baro->read_up(baro))
            {
                state = BARO_STATE_PRESSURE_SAMPLE;
            }
            break;
        case BARO_STATE_PRESSURE_SAMPLE:
            if (!baro->get_up(baro))
            {
                break;
            }

            // update baro data
            baro->calculate(&baro->pressure, &baro->temperature);
            baro->altitude = PressureToAltitude(baro->pressure);

            if (BaroIsCalibrated())
            {
                // zero baro altitude
                baro->altitude -= baroGroundAltitude;
            }
            else
            {
                // establish stable baroGroundAltitude value to zero baro altitude with
                PerformBaroCalibrationCycle(baro->altitude);
                baro->altitude = 0.0f;
            }

            println("pressure=%3.2f, ",baro->pressure / 100.0f);
            println("temperature=%3.2f, ",baro->temperature / 100.0f);
            println("altitude=%3.2f, ",baro->altitude / 10.0f);

            if (baro->combined_read)
            {
                state = BARO_STATE_PRESSURE_START;
            }
            else
            {
                state = BARO_STATE_TEMPERATURE_START;
            }
            break;
    }
    executeTimeUs = Sys_GetTickUs() - currentTimeUs;
    if (executeTimeUs > baroStateDurationUs[oldState])
    {
        baroStateDurationUs[oldState] = executeTimeUs;
    }

    return sleepTime;
}