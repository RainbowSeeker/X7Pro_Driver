// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//
#include <common.h>
#include "gpio.h"
#include "drivers/drv_uart.h"
#include "module/ipc/uMCN.h"

#include "drivers/imu/icm20689.h"
#include "workqueue/workqueue_manager.h"
#include "drivers/drv_spi.h"
#include "drivers/drv_sdio.h"
#include "drivers/imu/icm42688.h"
#include "drivers/imu/adis16470.h"
#include "drivers/barometer/ms5611.h"
#include "drivers/mag/rm3100.h"
#include "drivers/gps/gps_ubx.h"
#include "sensor/sensor_hub.h"
#include "mavproxy/mavproxy.h"
#include "drivers/drv_systick.h"
#include "drivers/fram/fm25vx.h"

#include "fmtio/fmtio.h"
#include "shell.h"
#include "drivers/board.h"
#include "drivers/drv_pwm.h"
#include "drivers/drv_adc.h"
#include "drivers/usbd/drv_usbd_cdc.h"
#include "file_manager/file_manager.h"


static const struct dfs_mount_tbl mnt_table[] = {
        { "sd0", "/", "elm", 0, NULL },
        { NULL } /* NULL indicate the end */
};

void bsp_hw_init(void)
{
    system_heap_init((void*)SYSTEM_FREE_MEM_BEGIN, (void*)SYSTEM_FREE_MEM_END);

    //ALARM
    io_init(PE5, CS_CONFIG);
    io_set(PE5, IO_LOW);

    //SENSORS_SW
    io_init(PE3, CS_CONFIG);
    io_set(PE3, IO_HIGH);

    //SDEN
    io_init(PG7, CS_CONFIG);
    io_set(PG7, IO_HIGH);

    io_init(PD11, CS_CONFIG);
    io_set(PD11, IO_HIGH);

    io_init(PH15, CS_CONFIG);
    io_set(PH15, IO_HIGH);

    io_init(PG0, CS_CONFIG);
    io_set(PG0, IO_HIGH);

    io_init(PG4, CS_CONFIG);
    io_set(PG4, IO_HIGH);

    io_init(PG5, CS_CONFIG);
    io_set(PG5, IO_HIGH);

    /* usart driver init */
    SELF_CHECK(drv_uart_init());

    SELF_CHECK(console_init());

    /* system timer init */
    SELF_CHECK(drv_systick_init());

    /* system time module init */
    SELF_CHECK(systime_init());

    /* spi driver init */
    SELF_CHECK(drv_spi_init());
}

extern void bsp_post_init();

void bsp_init(void)
{
    /* system statistic module */
    SELF_CHECK(sys_stat_init());

    /* init uMCN */
    SELF_CHECK(mcn_init());

    /* create workqueue */
    SELF_CHECK(workqueue_manager_init());

    SELF_CHECK(drv_sdio_init());

    SELF_CHECK(file_manager_init(mnt_table));

    SELF_CHECK(param_init());

    /* init usbd_cdc */
    SELF_CHECK(drv_usb_cdc_init());

    /* adc driver init */
    SELF_CHECK(drv_adc_init());

    SELF_CHECK(drv_adis16470_init("gyro0", "accel0"));

    SELF_CHECK(drv_icm20689_init("gyro1", "accel1"));

    SELF_CHECK(drv_icm42688_init("gyro2", "accel2"));

    SELF_CHECK(drv_ms5611_init("baro0"));

    SELF_CHECK(drv_rm3100_init("mag0"));

    SELF_CHECK(drv_fm25v05_init("fram0"));

    SELF_CHECK(gps_ubx_init("serial2", "gps"));

    /* register sensor to sensor hub */
    SELF_CHECK(register_sensor_imu("gyro0", "accel0", 0));
    SELF_CHECK(register_sensor_imu("gyro1", "accel1", 1));
    SELF_CHECK(register_sensor_imu("gyro2", "accel2", 2));
    SELF_CHECK(register_sensor_mag("mag0", 0));
    SELF_CHECK(register_sensor_barometer("baro0"));

    SELF_CHECK(mavproxy_init());

    fmtio_init(FMTIO_DEVICE_NAME);

    drv_pwm_init();

    bsp_post_init();

    /* init finsh */
    finsh_system_init();
}
