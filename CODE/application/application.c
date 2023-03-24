// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "application.h"
#include "common.h"
#include "init.h"

extern void App_Vehicle_Main(void *argument);
extern void App_Logger_Main(void *argument);
extern void App_Comm_Main(void *argument);
extern void App_Status_Main(void *argument);
extern void App_IO_Main(void *argument);

void application_create(void *p_arg)
{
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&os_err);                            /* Compute CPU capacity with no task running            */
#endif
#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
#if	OS_CFG_SCHED_ROUND_ROBIN_EN
    OSSchedRoundRobinCfg(DEF_ENABLED,5,&os_err);
#endif


    bsp_init();

    os_thread_create("app_vehicle", App_Vehicle_Main, NULL, VEHICLE_THREAD_PRIORITY, 512);

    os_thread_create("app_logger", App_Logger_Main, NULL, LOGGER_THREAD_PRIORITY, 512);

    os_thread_create("app_comm", App_Comm_Main, NULL, COMM_THREAD_PRIORITY, 512);

    os_thread_create("app_status", App_Status_Main, NULL, STATUS_THREAD_PRIORITY, 512);

    os_thread_create("app_io", App_IO_Main, NULL, FMTIO_THREAD_PRIORITY, 512);

    os_thread_delete(os_thread_self());
}

