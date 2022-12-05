//// Copyright (c) 2022 By RainbowSeeker.
//
////
//// Created by 19114 on 2022/11/19.
////
//
//#include "cli.h"
//#include "module/sensor/accgyro_icm20689.h"
//#include "module/sensor/accgyro_icm42688p.h"
//#include "module/sensor/accgyro_adis16470.h"
//#include "algo/math/maths.h"
//#include "algo/array.h"
//#include "syscmd.h"
//#include <stdarg.h>
//typedef struct
//{
//    char *praseName;
//    prase_func_t praseFunc;
//    char *annotation;
//}prase_t;
//
//static int cmd_list(int argc, char** argv);
//extern int cmd_mcn(int argc, char** argv);
//prase_t praseFuncTable[] = {
//        {"list", cmd_list, "list all available commands"},
////        {"mcn", cmd_mcn, "show & control mcn topics"},
//};
//
//static uint32_t cmd_maxlen()
//{
//    uint32_t maxLen = 0;
//    for (int i = 0; i < ARRAYLEN(praseFuncTable); ++i)
//    {
//        uint32_t len = strlen(praseFuncTable[i].praseName);
//        if (maxLen < len)
//        {
//            maxLen = len;
//        }
//    }
//    return maxLen;
//}
//static int cmd_list(int argc, char** argv)
//{
//    UNUSED(argc);
//    UNUSED(argv);
//    uint32_t maxLen = cmd_maxlen() + 2;
//    printf("\r\nAll available commands are as follows:\r\n");
//    syscmd_putc('-', maxLen);
//    printf("\r\n");
//    for (int i = 0; i < ARRAYLEN(praseFuncTable); ++i)
//    {
//        printf("%-*s\t", maxLen - 2, praseFuncTable[i].praseName);
//        if (praseFuncTable[i].annotation)
//        {
//            printf("-->%s", praseFuncTable[i].annotation);
//        }
//        printf("\r\n");
//    }
//    syscmd_putc('-', maxLen);
//    printf("\r\n");
//    return 0;
//}
//
//
//
//
//
//
//#define CLI_IN_BUFFER_SIZE 256
//
//
//static cli_t cli;
//static char cliBuffer[CLI_IN_BUFFER_SIZE] = {0};
//static uint8_t bufIndex = 0;
//
//
//
//void Cli_Init()
//{
//    cli.uart = Uart_Init(CLI_UART, NULL);
//    println("\r\nCli start.");
//}
//
//
//void Cli_Print(uint8_t *str, uint16_t len)
//{
//    Uart_Write(cli.uart, (uint8_t *)str, len);
//}
//
//bool Cli_IsReceived()
//{
//    return Uart_TotalRxBytesWaiting(cli.uart) > 0 ? true : false;
//}
//
//const char separator[] = " ";
//
//void CLi_Handle()
//{
//    uart_t *uart = cli.uart;
//    bool isOver = 0;
//    while (Uart_TotalRxBytesWaiting(uart))
//    {
//        uint8_t ch = Uart_ReadByte(uart);
//        if (ch == '\n')
//        {
//            isOver = 1;
//            break;
//        }
//        cliBuffer[bufIndex++] = ch;
//    }
//
//    if (isOver)
//    {
//        int argc = 0;
//        char **argv = NULL;
//        if (cliBuffer[bufIndex - 1] == '\r') cliBuffer[bufIndex - 1] = 0;
//        argc = split_ch(cliBuffer, separator, argv);
//        if (argc > 0)
//        {
//            for (int i = 0; i < ARRAYLEN(praseFuncTable); ++i)
//            {
//                if (strcmp(praseFuncTable[i].praseName, argv[0]) == 0)
//                {
//                    praseFuncTable[i].praseFunc(argc, argv);
//                }
//            }
//        }
//        memset(cliBuffer, 0, bufIndex);
//        bufIndex = 0;
//    }
//}
//
//
//
///**
// *  自定义打印函数 print，使用 DMA 发送
// * @param format
// * @param ...
// */
//int print(const void *format,...)
//{
//    va_list args;
//    char buf[256];
//    va_start (args, format);
//    vsprintf(buf, format, args);
//    va_end (args);
//
//    uint16_t len = strlen(buf);
//    Cli_Print( (uint8_t *)buf, len);
//    return len;
//}
///**
// * 自定义打印函数 println，使用 DMA 发送
// * @param format
// * @param ...
// */
//int println(const void *format,...)
//{
//    va_list args;
//    char buf[256];
//    va_start (args, format);
//    vsprintf(buf, format, args);
//    va_end (args);
//
//    uint16_t len = strlen(buf) + 2;
//    Cli_Print( (uint8_t *)buf, len);
//    Cli_Print( (uint8_t *)"\r\n", 2);
//    return len;
//}
//
///**
// * 重定义 printf (GNU中)
// * @param ch
// * @return
// */
//int __io_putchar(int ch)
//{
//    Cli_Print((uint8_t *)&ch, 1);
//    return ch;
//}
///**
// * 重定义 printf (MDK中)
// * @param ch
// * @param f
// * @return
// */
//int fputc(int ch, FILE *f)
//{
//    Cli_Print( (uint8_t *)&ch, 1);
//    return ch;
//}