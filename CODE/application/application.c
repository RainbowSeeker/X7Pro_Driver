// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "application.h"
#include "common.h"
#include "init.h"
#include "workqueue/workqueue_manager.h"


os_thread_t app_vehicleHandle;
os_thread_t app_loggerHandle;
os_thread_t app_commHandle;
os_thread_t app_statusHandle;
os_thread_t app_ioHandle;

extern void App_Vehicle_Main(void *argument);
extern void App_Logger_Main(void *argument);
extern void App_Comm_Main(void *argument);
extern void App_Status_Main(void *argument);
extern void App_IO_Main(void *argument);



extern osThreadId defaultTaskHandle;
void Application_Create(void)
{
    bsp_init();

    OS_ENTER_CRITICAL();

    app_vehicleHandle = os_thread_create("app_vehicle", App_Vehicle_Main, NULL, VEHICLE_THREAD_PRIORITY, 2 * 1024);

    app_loggerHandle = os_thread_create("app_logger", App_Logger_Main, NULL, LOGGER_THREAD_PRIORITY, 1 * 1024);

    app_commHandle = os_thread_create("app_comm", App_Comm_Main, NULL, COMM_THREAD_PRIORITY, 1 * 1024);

    app_statusHandle = os_thread_create("app_status", App_Status_Main, NULL, STATUS_THREAD_PRIORITY, 2 * 1024);

//    app_ioHandle = os_thread_create("app_io", App_IO_Main, NULL, FMTIO_THREAD_PRIORITY, 1 * 1024);

    vTaskDelete(defaultTaskHandle);
    OS_EXIT_CRITICAL();
}