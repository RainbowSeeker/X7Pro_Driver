//
// Created by 19114 on 2022/10/11.
//

#ifndef STM32H743IIT6_SDCARD_H
#define STM32H743IIT6_SDCARD_H
#include "main.h"

typedef enum
{
    SD_OK = 0,
    SD_OPEN_ERR,        // open/Create file  Fail
    SD_WRITE_ERR
}sd_error_t;


void SdCard_Init();
void Show_SD_Info(void);
sd_error_t Test_Write(const char* path, const char* string, uint32_t len);

#endif //STM32H743IIT6_SDCARD_H
