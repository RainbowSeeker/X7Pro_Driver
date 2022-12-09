// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//
#include <common.h>
#include "gpio.h"
#include "dma.h"
#include "bus_spi.h"
#include "drivers/drv_uart.h"
#include "cli/cli.h"
#include "module/ipc/uMCN.h"

#include "file_manager/file_manager.h"
#include "drivers/imu/icm20689.h"
#include "workqueue/workqueue_manager.h"
#include "drivers/drv_spi.h"
#include "drivers/drv_sdio.h"
#include "drivers/imu/icm42688.h"
#include "drivers/imu/adis16470.h"
#include "drivers/barometer/ms5611.h"
#include "drivers/mag/rm3100.h"
#include "drivers/gps/gps_m8n.h"
#include "sensor/sensor_hub.h"

static const struct dfs_mount_tbl mnt_table[] = {
        { "sd0", "/", "elm", 0, NULL },
        { NULL } /* NULL indicate the end */
};

void bsp_early_init(void)
{
    MX_GPIO_Init();

    EXTI_Init();

    /* usart driver init */
    SELF_CHECK(drv_uart_init());

    SELF_CHECK(console_init());

    SELF_CHECK(console_enable_input());

    /* spi driver init */
    SELF_CHECK(drv_spi_init());

    /* init uMCN */
    SELF_CHECK(mcn_init());

    /* create workqueue */
    SELF_CHECK(workqueue_manager_init());
}
void bsp_init(void)
{
    SELF_CHECK(drv_sdio_init());

//    SELF_CHECK(file_manager_init(mnt_table));
//
//    SELF_CHECK(param_init());

    SELF_CHECK(drv_adis16470_init("gyro0", "accel0"));

    SELF_CHECK(drv_icm42688_init("gyro1", "accel1"));

    SELF_CHECK(drv_icm20689_init("gyro2", "accel2"));

    SELF_CHECK(drv_ms5611_init("baro0"));

    SELF_CHECK(drv_rm3100_init("mag0"));

//    SELF_CHECK(gps_m8n_init("serial1", "gps"));

    /* register sensor to sensor hub */
    SELF_CHECK(register_sensor_imu("gyro0", "accel0", 0));
    SELF_CHECK(register_sensor_imu("gyro1", "accel1", 1));
    SELF_CHECK(register_sensor_imu("gyro2", "accel2", 2));

    SELF_CHECK(register_sensor_mag("mag0", 0));

    SELF_CHECK(register_sensor_barometer("baro0"));
}