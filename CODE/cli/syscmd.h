// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_SYSCMD_H
#define X7PRO_DRIVER_SYSCMD_H

#include "stdio.h"
#include "stdbool.h"

enum {
    SYSCMD_ALIGN_LEFT,
    SYSCMD_ALIGN_MIDDLE,
    SYSCMD_ALIGN_RIGHT
};

typedef struct {
    char* opt;
    char* val;
} optv_t;

typedef int (*shell_handle_func)(int, char**, int, optv_t*);

#define STRING_COMPARE(str1, str2) (strcmp(str1, str2) == 0)

#define PRINT_USAGE(cmd, usage)         printf("usage: %s %s\n", #cmd, #usage)
#define PRINT_STRING(str)               printf("%s", str)
#define PRINT_ACTION(action, len, desc) printf(" %-" #len "s  %s\n", action, desc)

#define COMMAND_USAGE(cmd, usage) printf("usage: %s %s\n", cmd, usage)
#define SHELL_COMMAND(cmd, desc)  printf(" %-10s  %s\n", cmd, desc)
#define SHELL_OPTION(opt, desc)   printf(" %-15s  %s\n", opt, desc)

#define console_write(_ch, _len)    Cli_Print((uint8_t *)_ch, _len)
#define console_printf              printf

bool syscmd_is_num(const char* str);
bool syscmd_is_hex(const char* str);
char syscmd_getc(void);
bool syscmd_has_input(void);
void syscmd_flush(void);
void syscmd_putc(const char c, int cnt);
void syscmd_printf(const char pad, uint32_t len, uint8_t align, const char* fmt, ...);
int syscmd_process(int argc, char** argv, shell_handle_func func);


#endif //X7PRO_DRIVER_SYSCMD_H
