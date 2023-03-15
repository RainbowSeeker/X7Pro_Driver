// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#include "sensor_imu.h"

/**
 * @brief Set gyro rotation matrix
 *
 * @param imu_dev IMU sensor device
 * @param rotation Gyro rotation matrix (3x3)
 */
void sensor_gyr_set_rotation(sensor_imu_t *imu_dev, const float rotation[9])
{
    imu_dev->gyr_rotation[0][0] = rotation[0];
    imu_dev->gyr_rotation[0][1] = rotation[1];
    imu_dev->gyr_rotation[0][2] = rotation[2];
    imu_dev->gyr_rotation[1][0] = rotation[3];
    imu_dev->gyr_rotation[1][1] = rotation[4];
    imu_dev->gyr_rotation[1][2] = rotation[5];
    imu_dev->gyr_rotation[2][0] = rotation[6];
    imu_dev->gyr_rotation[2][1] = rotation[7];
    imu_dev->gyr_rotation[2][2] = rotation[8];
}

/**
 * @brief Set gyro offset
 *
 * @param imu_dev IMU sensor device
 * @param offset Gyro offset
 */
void sensor_gyr_set_offset(sensor_imu_t *imu_dev, const float offset[3])
{
    imu_dev->gyr_offset[0] = offset[0];
    imu_dev->gyr_offset[1] = offset[1];
    imu_dev->gyr_offset[2] = offset[2];
}

/**
 * @brief Correct gyro data based on offset and rotation matrix
 *
 * @param imu_dev IMU sensor device
 * @param src Original gyro data
 * @param dst Corrected gyro data
 */
void sensor_gyr_correct(sensor_imu_t *imu_dev, const float src[3], float dst[3])
{
    float temp[3];

    temp[0] = src[0] - imu_dev->gyr_offset[0];
    temp[1] = src[1] - imu_dev->gyr_offset[1];
    temp[2] = src[2] - imu_dev->gyr_offset[2];

    dst[0] = imu_dev->gyr_rotation[0][0] * temp[0] + imu_dev->gyr_rotation[0][1] * temp[1] + imu_dev->gyr_rotation[0][2] * temp[2];
    dst[1] = imu_dev->gyr_rotation[1][0] * temp[0] + imu_dev->gyr_rotation[1][1] * temp[1] + imu_dev->gyr_rotation[1][2] * temp[2];
    dst[2] = imu_dev->gyr_rotation[2][0] * temp[0] + imu_dev->gyr_rotation[2][1] * temp[1] + imu_dev->gyr_rotation[2][2] * temp[2];
}

/**
 * @brief Measure scaled gyro data (rad/s)
 *
 * @param imu_dev IMU sensor device
 * @param buffer Data buffer
 * @return err_t E_OK for success
 */
err_t sensor_gyr_measure(sensor_imu_t *imu_dev, float buffer[3])
{
    uint8_t r_size;

    ASSERT(imu_dev != NULL);

    r_size = device_read(imu_dev->gyr_dev, 0, (void*)buffer, 12);

    return r_size == 12 ? E_OK : E_RROR;
}

/**
 * @brief Set accel rotation matrix
 *
 * @param imu_dev IMU sensor device
 * @param rotation Accel rotation matrix (3x3)
 */
void sensor_acc_set_rotation(sensor_imu_t *imu_dev, const float rotation[9])
{
    imu_dev->acc_rotation[0][0] = rotation[0];
    imu_dev->acc_rotation[0][1] = rotation[1];
    imu_dev->acc_rotation[0][2] = rotation[2];
    imu_dev->acc_rotation[1][0] = rotation[3];
    imu_dev->acc_rotation[1][1] = rotation[4];
    imu_dev->acc_rotation[1][2] = rotation[5];
    imu_dev->acc_rotation[2][0] = rotation[6];
    imu_dev->acc_rotation[2][1] = rotation[7];
    imu_dev->acc_rotation[2][2] = rotation[8];
}

/**
 * @brief Set accel offset
 *
 * @param imu_dev IMU sensor device
 * @param offset Accel offset
 */
void sensor_acc_set_offset(sensor_imu_t *imu_dev, const float offset[3])
{
    imu_dev->acc_offset[0] = offset[0];
    imu_dev->acc_offset[1] = offset[1];
    imu_dev->acc_offset[2] = offset[2];
}

/**
 * @brief Correct accel data based on offset and rotation matrix
 *
 * @param imu_dev IMU sensor device
 * @param src Original accel data
 * @param dst Corrected accel data
 */
void sensor_acc_correct(sensor_imu_t *imu_dev, const float src[3], float dst[3])
{
    float temp[3];

    temp[0] = src[0] - imu_dev->acc_offset[0];
    temp[1] = src[1] - imu_dev->acc_offset[1];
    temp[2] = src[2] - imu_dev->acc_offset[2];

    dst[0] = imu_dev->acc_rotation[0][0] * temp[0] + imu_dev->acc_rotation[0][1] * temp[1] + imu_dev->acc_rotation[0][2] * temp[2];
    dst[1] = imu_dev->acc_rotation[1][0] * temp[0] + imu_dev->acc_rotation[1][1] * temp[1] + imu_dev->acc_rotation[1][2] * temp[2];
    dst[2] = imu_dev->acc_rotation[2][0] * temp[0] + imu_dev->acc_rotation[2][1] * temp[1] + imu_dev->acc_rotation[2][2] * temp[2];
}

/**
 * @brief Measure scaled accel data (m/s2)
 *
 * @param imu_dev IMU sensor device
 * @param buffer Data buffer
 * @return err_t E_OK for success
 */
err_t sensor_acc_measure(sensor_imu_t *imu_dev, float buffer[3])
{
    uint8_t r_size;

    ASSERT(imu_dev != NULL);

    r_size = device_read(imu_dev->acc_dev, 0, (void*)buffer, 12);

    return r_size == 12 ? E_OK : E_RROR;
}

/**
 * @brief Initialize imu sensor device
 *
 * @param gyr_dev_name Gyroscope device name
 * @param acc_dev_name Accelerometer device name
 * @return sensor_imu_t *IMU sensor device
 */
sensor_imu_t *sensor_imu_init(const char* gyr_dev_name, const char* acc_dev_name)
{
    sensor_imu_t *imu_dev = (sensor_imu_t *)malloc(sizeof(struct sensor_imu));
    ASSERT(imu_dev != NULL);

    imu_dev->gyr_dev = device_find(gyr_dev_name);
    ASSERT(imu_dev->gyr_dev != NULL);

    SELF_CHECK(device_open(imu_dev->gyr_dev, DEVICE_OFLAG_RDWR));

    imu_dev->acc_dev = device_find(acc_dev_name);
    ASSERT(imu_dev->acc_dev != NULL);

    SELF_CHECK(device_open(imu_dev->acc_dev, DEVICE_OFLAG_RDWR));

    return imu_dev;
}