// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_SENSOR_MAG_H
#define X7PRO_DRIVER_SENSOR_MAG_H
#include "sensor_hub.h"

sensor_mag_t *sensor_mag_init(const char* mag_dev_name);
err_t sensor_mag_measure(sensor_mag_t *mag_dev, float buffer[3]);
void sensor_mag_set_rotation(sensor_mag_t *mag_dev, const float rotation[9]);
void sensor_mag_set_offset(sensor_mag_t *mag_dev, const float offset[3]);
void sensor_mag_correct(sensor_mag_t *mag_dev, const float src[3], float dst[3]);

#endif //X7PRO_DRIVER_SENSOR_MAG_H
