// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_SENSOR_GPS_H
#define X7PRO_DRIVER_SENSOR_GPS_H

#include "sensor_hub.h"

sensor_gps_t *sensor_gps_init(const char* gps_dev_name);
err_t sensor_gps_read(sensor_gps_t *gps_dev, gps_data_t* gps_data);
uint8_t sensor_gps_check_ready(sensor_gps_t *gps_dev);

#endif //X7PRO_DRIVER_SENSOR_GPS_H
