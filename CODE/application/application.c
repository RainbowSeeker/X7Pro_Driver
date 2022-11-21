// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "application.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"


osThreadId app_testHandle;
osThreadId app_spiHandle;
osThreadId app_sdHandle;
osThreadId app_pwmHandle;

extern void App_Test_Main(void const * argument);
extern void App_SPI_Main(void const * argument);
extern void App_SD_Main(void const * argument);
extern void App_PWM_Main(void const * argument);

extern osThreadId defaultTaskHandle;
void Application_Create(void)
{
    taskENTER_CRITICAL();

    osThreadDef(app_test, App_Test_Main, osPriorityNormal, 0, 512);
    app_testHandle = osThreadCreate(osThread(app_test), NULL);

    osThreadDef(app_spi, App_SPI_Main, osPriorityNormal, 0, 512);
    app_spiHandle = osThreadCreate(osThread(app_spi), NULL);

    osThreadDef(app_sd, App_SD_Main, osPriorityNormal, 0, 512);
//    app_sdHandle = osThreadCreate(osThread(app_sd), NULL);

    osThreadDef(app_pwm, App_PWM_Main, osPriorityNormal, 0, 512);
//    app_pwmHandle = osThreadCreate(osThread(app_pwm), NULL);

    osThreadTerminate(defaultTaskHandle);
    taskEXIT_CRITICAL();
}