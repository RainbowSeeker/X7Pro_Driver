// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "application.h"
#include "FreeRTOS.h"
#include "common.h"
#include "init.h"
#include "workqueue/workqueue_manager.h"


os_thread_t app_cliHandle;
os_thread_t app_spiHandle;
os_thread_t app_sdHandle;
os_thread_t app_pwmHandle;
os_thread_t app_mcnHandle;
os_thread_t app_logHandle;

extern void App_Cli_Main(void  *argument);
extern void App_SPI_Main(void *argument);
extern void App_SD_Main(void *argument);
extern void App_PWM_Main(void *argument);
extern void App_Mcn_Main(void *argument);
extern void App_Log_Main(void *argument);

extern osThreadId defaultTaskHandle;
void Application_Create(void)
{
    bsp_early_init();

    OS_ENTER_CRITICAL();

    app_spiHandle = os_thread_create("app_spi", App_SPI_Main, NULL, VEHICLE_THREAD_PRIORITY, 1024);

    app_logHandle = os_thread_create("app_log", App_Log_Main, NULL, LOGGER_THREAD_PRIORITY, 4 * 1024);

    app_mcnHandle = os_thread_create("app_mcn", App_Mcn_Main, NULL, COMM_THREAD_PRIORITY, 2 * 1024);

    vTaskDelete(defaultTaskHandle);
    OS_EXIT_CRITICAL();
}