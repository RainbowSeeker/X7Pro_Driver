// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "application.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"


osThreadId app_cliHandle;
osThreadId app_spiHandle;
osThreadId app_sdHandle;
osThreadId app_pwmHandle;
osThreadId app_mcnHandle;

extern void App_Cli_Main(void const * argument);
extern void App_SPI_Main(void const * argument);
extern void App_SD_Main(void const * argument);
extern void App_PWM_Main(void const * argument);
extern void App_Mcn_Main(void const * argument);

extern osThreadId defaultTaskHandle;
void Application_Create(void)
{
    taskENTER_CRITICAL();

    osThreadDef(app_cli, App_Cli_Main, osPriorityIdle, 0, 512);
    app_cliHandle = osThreadCreate(osThread(app_cli), NULL);

    osThreadDef(app_spi, App_SPI_Main, osPriorityNormal, 0, 512);
    app_spiHandle = osThreadCreate(osThread(app_spi), NULL);

    osThreadDef(app_sd, App_SD_Main, osPriorityNormal, 0, 512);
//    app_sdHandle = osThreadCreate(osThread(app_sd), NULL);

    osThreadDef(app_pwm, App_PWM_Main, osPriorityNormal, 0, 512);
    app_pwmHandle = osThreadCreate(osThread(app_pwm), NULL);

    osThreadDef(app_mcn, App_Mcn_Main, osPriorityNormal, 0, 512);
    app_mcnHandle = osThreadCreate(osThread(app_mcn), NULL);

    osThreadTerminate(defaultTaskHandle);
    taskEXIT_CRITICAL();
}