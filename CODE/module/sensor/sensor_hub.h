// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/22.
//

#ifndef X7PRO_DRIVER_SENSOR_HUB_H
#define X7PRO_DRIVER_SENSOR_HUB_H

#include "common.h"

#define SENSOR_SOFT_DRDY       1

#define RAW_TEMPERATURE_POS 0
#define RAW_PRESSURE_POS    1
#define COLLECT_DATA_POS    2
#define GYR_RAW_POS         0
#define GYR_SCALE_POS       1
#define ACC_RAW_POS         2
#define ACC_SCALE_POS       3
#define MAG_RAW_POS         4
#define MAG_SCLAE_POS       5

//common cmd
#define SENSOR_GET_DEVICE_ID 0x00
//acc,mag cmd
#define SENSOR_SET_ACC_RANGE      0x01
#define SENSOR_SET_ACC_SAMPLERATE 0x02
#define SENSOR_SET_MAG_RANGE      0x03
#define SENSOR_SET_MAG_SAMPLERATE 0x04
//gyr cmd
#define SENSOR_SET_GYR_RANGE 0x20
//baro cmd
#define SENSOR_CONVERSION  0x30
#define SENSOR_IS_CONV_FIN 0x31

typedef struct sensor_imu
{
    light_device_t gyr_dev;
    light_device_t acc_dev;
    float gyr_rotation[3][3];
    float gyr_offset[3];
    float acc_rotation[3][3];
    float acc_offset[3];
}sensor_imu_t;

typedef struct sensor_mag
{
    light_device_t dev;
    float rotation[3][3];
    float offset[3];
}sensor_mag_t;

typedef struct sensor_baro
{
    light_device_t dev;
}sensor_baro_t;

typedef struct sensor_gps
{
    light_device_t dev;
}sensor_gps_t;

typedef struct sensor_airspeed
{
    light_device_t dev;
}sensor_airspeed_t;


typedef struct
{
    uint32_t timestamp_ms;
    float gyr_B_radDs[3];
    float acc_B_mDs2[3];
} imu_data_t;

typedef struct
{
    uint32_t timestamp_ms;
    float mag_B_gauss[3];
} mag_data_t;

typedef struct
{
    uint32_t timestamp_ms;
    float temperature_deg;
    int32_t pressure_pa;
    float altitude_m;
} baro_data_t;

typedef struct
{
    uint32_t timestamp_ms;
    int32_t lon;
    int32_t lat;
    int32_t height;
    float hAcc;
    float vAcc;
    float velN;
    float velE;
    float velD;
    float vel;
    float cog;
    float sAcc;
    uint8_t fixType;
    uint8_t numSV;
    uint16_t reserved;
} gps_data_t;

typedef struct
{
    uint32_t timestamp_ms;
    float vx_mPs;
    float vy_mPs;
    uint8_t quality;
} optflow_data_t;

typedef struct
{
    uint32_t timestamp_ms;
    float distance_m; // negative value indicate invalid
} rf_data_t;

typedef struct
{
    uint32_t timestamp_ms;
    float diff_pressure_pa;
    float temperature_deg;
} airspeed_data_t;

void sensor_collect(void);
err_t advertise_sensor_imu(uint8_t id);
err_t advertise_sensor_mag(uint8_t id);
err_t advertise_sensor_baro(uint8_t id);
err_t advertise_sensor_airspeed(uint8_t id);
err_t advertise_sensor_gps(uint8_t id);
err_t advertise_sensor_optflow(uint8_t id);
err_t advertise_sensor_rangefinder(uint8_t id);
err_t register_sensor_imu(const char* gyr_dev_name, const char* acc_dev_name, uint8_t id);
err_t register_sensor_mag(const char* dev_name, uint8_t id);
err_t register_sensor_barometer(const char* dev_name);
err_t register_sensor_airspeed(const char* dev_name);
err_t register_sensor_gps(const char* dev_name);
#endif //X7PRO_DRIVER_SENSOR_HUB_H
