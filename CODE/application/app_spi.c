// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include <common.h>
#include "module_common.h"
#include "model/ins/base_ins/lib/INS.h"
#include "sensor/accgyro_adis16470.h"
#include "spi/spi.h"
#include "barometer/barometer.h"
#include "sensor/sensor_hub.h"
#include "sysio/pilot_cmd.h"
#include "sysio/gcs_cmd.h"
#include "sysio/mission_data.h"
#include "model/ins/ins_interface.h"
#include "model/fms/fms_interface.h"
#include "model/control/control_interface.h"
#include "sysio/actuator_cmd.h"

uint8_t log_data[200] = {0};
void App_SPI_Main(void *argument)
{
    static uint32_t time_start = 0;
    uint32_t time_now;
    uint32_t timestamp;
//    Fram_Init(&fm25vx);
//    uint8_t txbuf[25] = "fm25vx read & write test";
//    uint8_t rxbuf[25] = {0};
//    uint8_t len = strlen((char *)txbuf);
//    uint8_t str[] = "hello world123\r\n";

#if defined(FMT_USING_SIH)
    /* init plant model */
    plant_interface_init();
#endif

    /* init ins model */
    ins_interface_init();

    /* init fms model */
    fms_interface_init();

    /* init controller model */
    control_interface_init();
    
    while (1)
    {
        time_now = systime_now_ms();
        /* record loop start time */
        if (time_start == 0) {
            time_start = time_now;
        }
        /* the model simulation start from 0, so we calcualtet the timestamp relative to start time */
        timestamp = time_now - time_start;

#if !defined(FMT_USING_HIL) && !defined(FMT_USING_SIH)
        sensor_collect();
#endif
        pilot_cmd_collect();
        gcs_cmd_collect();
        mission_data_collect();

#ifdef FMT_USING_SIH
        /* run Plant model */
        PERIOD_EXECUTE3(plant_step, plant_model_info.period, time_now, plant_interface_step(timestamp););
#endif
        /* run INS model */
        PERIOD_EXECUTE3(ins_step, ins_model_info.period, time_now, ins_interface_step(timestamp););
        /* run FMS model */
        PERIOD_EXECUTE3(fms_step, fms_model_info.period, time_now, fms_interface_step(timestamp););
        /* run Controller model */
        PERIOD_EXECUTE3(control_step, control_model_info.period, time_now, control_interface_step(timestamp););

        /* send actuator command */
        send_actuator_cmd();


        os_delay(1);
//        osDelay(Baro_Update(&ms5611, Sys_GetTickUs()) / 1000);
//        fm25vx.write(0x00C1, txbuf, len);
//        fm25vx.read(0x00C1, rxbuf, len);
//        println("%s", rxbuf);
    }

}