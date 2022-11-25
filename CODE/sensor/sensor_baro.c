// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#include "sensor_baro.h"

/**
 * @brief Check if barometer data is ready to read
 *
 * @param baro_dev Barometer sensor device
 * @return uint8_t 1:ready 0:not-ready
 */
uint8_t sensor_baro_check_ready(sensor_baro_t *baro_dev)
{
    uint8_t ready = 0;

//    rt_device_control(baro_dev->dev, BARO_CMD_CHECK_READY, &ready);

    return ready;
}

/**
 * @brief Trigger barometer measure/conversion process
 *
 * @param baro_dev Barometer sensor device
 * @return err_status_e E_OK for success
 */
err_status_e sensor_baro_update(sensor_baro_t *baro_dev)
{
//    if (rt_device_control(baro_dev->dev, BARO_CMD_UPDATE, NULL) != RT_EOK) {
//        return E_RROR;
//    }
    return E_OK;
}

/**
 * @brief Read barometer data
 *
 * @param baro_dev Barometer sensor device
 * @param baro_data Barometer data buffer
 * @return err_status_e E_OK for success
 */
err_status_e sensor_baro_read(sensor_baro_t *baro_dev, baro_data_t* baro_data)
{
//    baro_report_t report;
//    if (rt_device_read(baro_dev->dev, BARO_RD_REPORT, &report, sizeof(baro_report_t)) != sizeof(baro_report_t)) {
//        return E_RROR;
//    }
//
//    baro_data->temperature_deg = report.temperature_deg;
//    baro_data->pressure_pa = report.pressure_Pa;
//    baro_data->altitude_m = report.altitude_m;
//    baro_data->timestamp_ms = report.timestamp_ms;

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
    sensor_baro_t *baro_dev = (sensor_baro_t *)MALLOC(sizeof(struct sensor_baro));
    assert(baro_dev != NULL);

    /* find baro device */
//    baro_dev->dev = rt_device_find(baro_dev_name);
//    assert(baro_dev->dev != NULL);
//
//    /* open device */
//    RT_CHECK(rt_device_open(baro_dev->dev, RT_DEVICE_OFLAG_RDWR));

    return baro_dev;
}