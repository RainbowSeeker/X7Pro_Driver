// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_SENSOR_IMU_H
#define X7PRO_DRIVER_SENSOR_IMU_H
#include "sensor_hub.h"
sensor_imu_t *sensor_imu_init(const char* gyr_dev_name, const char* acc_dev_name);
/* gyro api */
err_status_e sensor_gyr_measure(sensor_imu_t *imu_dev, float buffer[3]);
void sensor_gyr_set_rotation(sensor_imu_t *imu_dev, const float rotation[9]);
void sensor_gyr_set_offset(sensor_imu_t *imu_dev, const float offset[3]);
void sensor_gyr_correct(sensor_imu_t *imu_dev, const float src[3], float dst[3]);
/* accel api */
err_status_e sensor_acc_measure(sensor_imu_t *imu_dev, float buffer[3]);
void sensor_acc_set_rotation(sensor_imu_t *imu_dev, const float rotation[9]);
void sensor_acc_set_offset(sensor_imu_t *imu_dev, const float offset[3]);
void sensor_acc_correct(sensor_imu_t *imu_dev, const float src[3], float dst[3]);


#endif //X7PRO_DRIVER_SENSOR_IMU_H
