// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#include "app_sd.h"
#include "sdop.h"
#include "fatfs.h"

const uint8_t text_to_send[]="hello world";
uint8_t bigdata[200];
uint32_t count = 0;
uint32_t nowTick = 0;
uint32_t avgTick = 0;
char tickstr[20];

void App_SD_Main(void const * argument)
{
    SD_Init();
    Show_SD_Info();

    uint16_t len = strlen((char *)text_to_send);
    for (uint16_t i = 0; i < 200 - 3; i += len)
    {
        if (200 < (len + i)) len = 200 - i;
        memcpy(&bigdata[i], text_to_send, len);
    }
    bigdata[200 - 3] = '\r';
    bigdata[200 - 2] = '\n';
    bigdata[200 - 1] = '\0';
    /* Infinite loop */
    assert(!f_open(&SDFile, "hello.xls", FA_OPEN_ALWAYS | FA_WRITE ));
    uint32_t pWakeTime = osKernelSysTick();
    while (1)
    {
//        nowTick = HAL_GetTick();
//        sprintf(tickstr, "%lu\t", nowTick);
//        memcpy(bigdata, tickstr, strlen(tickstr));

//        if (SD_OK ==Test_Write("hello.xls", (char *)bigdata, sizeof(bigdata)))
//        {
//            count++;
//            avgTick += HAL_GetTick() - nowTick;
//            if (count % 10 == 0)
//            {
//                LED_Toggle(led1);
//                print("avgTime=%3.2f\r\n", (float)avgTick / 10);
//                avgTick = 0;
//            }
//        }
//        osDelayUntil(&pWakeTime, 5);
    }
}