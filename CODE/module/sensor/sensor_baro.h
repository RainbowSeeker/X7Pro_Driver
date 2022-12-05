// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_SENSOR_BARO_H
#define X7PRO_DRIVER_SENSOR_BARO_H

#include "sensor_hub.h"

sensor_baro_t *sensor_baro_init(const char* baro_dev_name);
err_status_e sensor_baro_update(sensor_baro_t *baro_dev);
uint8_t sensor_baro_check_ready(sensor_baro_t *baro_dev);
err_status_e sensor_baro_read(sensor_baro_t *baro_dev, baro_data_t* baro_data);


#endif //X7PRO_DRIVER_SENSOR_BARO_H
