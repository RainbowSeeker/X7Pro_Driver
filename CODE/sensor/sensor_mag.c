// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#include "sensor_mag.h"

/**
 * @brief Set mag rotation matrix
 *
 * @param mag_dev Mag sensor device
 * @param rotation Mag rotation matrix (3x3)
 */
void sensor_mag_set_rotation(sensor_mag_t *mag_dev, const float rotation[9])
{
    mag_dev->rotation[0][0] = rotation[0];
    mag_dev->rotation[0][1] = rotation[1];
    mag_dev->rotation[0][2] = rotation[2];
    mag_dev->rotation[1][0] = rotation[3];
    mag_dev->rotation[1][1] = rotation[4];
    mag_dev->rotation[1][2] = rotation[5];
    mag_dev->rotation[2][0] = rotation[6];
    mag_dev->rotation[2][1] = rotation[7];
    mag_dev->rotation[2][2] = rotation[8];
}

/**
 * @brief Set mag offset
 *
 * @param mag_dev Mag sensor device
 * @param offset Mag offset
 */
void sensor_mag_set_offset(sensor_mag_t *mag_dev, const float offset[3])
{
    mag_dev->offset[0] = offset[0];
    mag_dev->offset[1] = offset[1];
    mag_dev->offset[2] = offset[2];
}

/**
 * @brief Correct mag data based on offset and rotation matrix
 *
 * @param mag_dev Mag sensor device
 * @param src Original mag data
 * @param dst Corrected mag data
 */
void sensor_mag_correct(sensor_mag_t *mag_dev, const float src[3], float dst[3])
{
    float temp[3];

    temp[0] = src[0] - mag_dev->offset[0];
    temp[1] = src[1] - mag_dev->offset[1];
    temp[2] = src[2] - mag_dev->offset[2];

    dst[0] = mag_dev->rotation[0][0] * temp[0] + mag_dev->rotation[0][1] * temp[1] + mag_dev->rotation[0][2] * temp[2];
    dst[1] = mag_dev->rotation[1][0] * temp[0] + mag_dev->rotation[1][1] * temp[1] + mag_dev->rotation[1][2] * temp[2];
    dst[2] = mag_dev->rotation[2][0] * temp[0] + mag_dev->rotation[2][1] * temp[1] + mag_dev->rotation[2][2] * temp[2];
}

/**
 * @brief Measure scaled mag data (gauss)
 *
 * @param mag_dev Mag sensor device
 * @param buffer Data buffer
 * @return err_status_e E_OK for success
 */
err_status_e sensor_mag_measure(sensor_mag_t *mag_dev, float buffer[3])
{
    uint8_t r_byte;

//    r_byte = rt_device_read(mag_dev->dev, 0, (void*)buffer, 12);

    return r_byte == 12 ? E_OK : E_RROR;
}

/**
 * @brief Initialize magetometer sensor device
 *
 * @param mag_dev_name Magnetometer device name
 * @return sensor_mag_t *Magnetometer sensor device
 */
sensor_mag_t *sensor_mag_init(const char* mag_dev_name)
{
    sensor_mag_t *mag_dev = (sensor_mag_t *)MALLOC(sizeof(struct sensor_mag));
    assert(mag_dev != NULL);

//    mag_dev->dev = rt_device_find(mag_dev_name);
//    assert(mag_dev->dev);
//
//    RT_CHECK(rt_device_open(mag_dev->dev, RT_DEVICE_OFLAG_RDWR));

    return mag_dev;
}