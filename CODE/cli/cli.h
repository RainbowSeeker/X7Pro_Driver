// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//

#ifndef X7PRO_DRIVER_CLI_H
#define X7PRO_DRIVER_CLI_H
#include "driver/uart.h"

#define CLI_UART    UART_7

typedef struct
{
    uart_t *uart;
}cli_t;

typedef void (* prase_func_t)();

void Cli_Init();
void CLi_Handle();
#endif //X7PRO_DRIVER_CLI_H
