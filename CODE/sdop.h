//
// Created by 19114 on 2022/10/11.
//

#ifndef STM32H743IIT6_SDCARD_H
#define STM32H743IIT6_SDCARD_H
#include <common.h>



void SdCard_Init();
void Show_SD_Info(void);
err_t Test_Write(const char* path, const char* string, uint32_t len);

#endif //STM32H743IIT6_SDCARD_H
