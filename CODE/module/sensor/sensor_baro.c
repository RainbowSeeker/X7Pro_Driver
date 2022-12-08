// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#include "sensor_baro.h"
#include "barometer/barometer.h"

/**
 * @brief Check if barometer data is ready to read
 *
 * @param baro_dev Barometer sensor device
 * @return uint8_t 1:ready 0:not-ready
 */
uint8_t sensor_baro_check_ready(sensor_baro_t *baro_dev)
{
    uint8_t ready = 0;

    light_device_control(baro_dev->dev, BARO_CMD_CHECK_READY, &ready);

    return ready;
}

/**
 * @brief Read barometer data
 *
 * @param baro_dev Barometer sensor device
 * @param baro_data Barometer data buffer
 * @return err_t E_OK for success
 */
err_t sensor_baro_read(sensor_baro_t *baro_dev, baro_data_t* baro_data)
{
    baro_report_t report;
    if (light_device_read(baro_dev->dev, BARO_RD_REPORT, &report, sizeof(baro_report_t)) != sizeof(baro_report_t)) {
        return E_RROR;
    }

    baro_data->temperature_deg = report.temperature_deg;
    baro_data->pressure_pa = report.pressure_Pa;
    baro_data->altitude_m = report.altitude_m;
    baro_data->timestamp_ms = report.timestamp_ms;

    return E_OK;
}

/**
 * @brief Initialize barometer sensor device
 *
 * @param baro_dev_name Barometer device name
 * @return sensor_baro_t *Barometer sensor device
 */
sensor_baro_t *sensor_baro_init(const char* baro_dev_name)
{
    sensor_baro_t *baro_dev = (sensor_baro_t *)malloc(sizeof(struct sensor_baro));
    ASSERT(baro_dev != NULL);

    /* find baro device */
    baro_dev->dev = light_device_find(baro_dev_name);
    ASSERT(baro_dev->dev != NULL);

    /* open device */
    SELF_CHECK(light_device_open(baro_dev->dev, DEVICE_OFLAG_RDWR));

    return baro_dev;
}