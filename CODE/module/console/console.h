

#ifndef CONSOLE_H__
#define CONSOLE_H__

#include <common_def.h>
#include <stdarg.h>
#include "device.h"
#define printf console_printf

/* console API */
err_t console_init(void);
err_t console_enable_input(void);
err_t console_set_device(const char* device_name);
device_t console_get_device(void);
int console_printf(const char* fmt, ...);
int console_println(const char* fmt, ...);
int console_print_args(const char* fmt, va_list args);
int console_putc(char ch);
int console_write(const char* content, uint32_t len);
void console_format(char* buffer, const char* fmt, ...);
#endif
