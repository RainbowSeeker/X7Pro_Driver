// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/19.
//

#include "cli.h"
#include "accgyro_icm20689.h"
#include "accgyro_icm42688p.h"
#include "accgyro_adis16470.h"
#include "maths.h"
#include <stdarg.h>

typedef struct
{
    char *cmdString;
    prase_func_t praseFunc;
}cli_command_t;

cli_command_t cliCommand[] = {
        {"adis16470", Print_ADIS16470},
        {"icm42688", Print_ICM42688},
        {"icm20689", Print_ICM20689},
};


#define CLI_IN_BUFFER_SIZE 256


static cli_t cli;
static char cliBuffer[CLI_IN_BUFFER_SIZE] = {0};
static uint8_t bufIndex = 0;


void Cli_Init()
{
    cli.uart = Uart_Init(CLI_UART, NULL);
    println("Cli start.");
}

bool NextArg(uint8_t ch)
{
    if ((ch >= 'a' && ch <= 'z') || (bufIndex && (ch == ' ' || (ch >= '0' && ch <= '9'))))
    {
        cliBuffer[bufIndex++] = ch;
    }
    else if (bufIndex)
    {
        bufIndex = 0;
        return true;
    }
    return false;
}

void CLi_Prase(const char *str, prase_func_t prase)
{
    uint8_t idx = 0;
    while (str[idx] && str[idx] == cliBuffer[idx])
    {
        idx++;
    }
    if (!str[idx])
    {
        prase();
        memset(cliBuffer, 0, idx);
    }
}

void CLi_Handle()
{
    uart_t *uart = cli.uart;
    while (Uart_TotalRxBytesWaiting(uart))
    {
        uint8_t ch = Uart_ReadByte(uart);
        if (NextArg(ch))
        {
            for (int i = 0; i < ARRAYLEN(cliCommand); ++i)
            {
                CLi_Prase(cliCommand[i].cmdString, cliCommand[i].praseFunc);
            }
        }
    }
}



/**
 *  自定义打印函数 print，使用 DMA 发送
 * @param format
 * @param ...
 */
void print(const void *format,...)
{
    va_list args;
    char buf[256];
    va_start (args, format);
    vsprintf(buf, format, args);
    va_end (args);

    Uart_Write(cli.uart, (uint8_t *)buf, strlen(buf));
}
/**
 * 自定义打印函数 println，使用 DMA 发送
 * @param format
 * @param ...
 */
void println(const void *format,...)
{
    va_list args;
    char buf[256];
    va_start (args, format);
    vsprintf(buf, format, args);
    va_end (args);

    Uart_Write(cli.uart, (uint8_t *)buf, strlen(buf));
    Uart_Write(cli.uart, (uint8_t *)"\r\n", 2);
}

/**
 * 重定义 printf (GNU中)
 * @param ch
 * @return
 */
int __io_putchar(int ch)
{
    Uart_Write(cli.uart, (uint8_t *)&ch, 1);
    return ch;
}
/**
 * 重定义 printf (MDK中)
 * @param ch
 * @param f
 * @return
 */
int fputc(int ch, FILE *f)
{
    Uart_Write(cli.uart, (uint8_t *)&ch, 1);
    return ch;
}