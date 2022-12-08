#ifndef SYSCMD_H__
#define SYSCMD_H__

#include <common.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#define PRINT_USAGE(cmd, usage)         console_printf("usage: %s %s\n", #cmd, #usage)
#define PRINT_STRING(str)               console_printf("%s", str)
#define PRINT_ACTION(action, len, desc) console_printf(" %-" #len "s  %s\n", action, desc)

#define COMMAND_USAGE(cmd, usage) console_printf("usage: %s %s\n", cmd, usage)
#define SHELL_COMMAND(cmd, desc)  console_printf(" %-10s  %s\n", cmd, desc)
#define SHELL_OPTION(opt, desc)   console_printf(" %-15s  %s\n", opt, desc)

bool syscmd_is_num(const char* str);
bool syscmd_is_hex(const char* str);
char syscmd_getc(void);
bool syscmd_has_input(void);
void syscmd_flush(void);
void syscmd_putc(const char c, int cnt);
void syscmd_printf(const char pad, uint32_t len, uint8_t align, const char* fmt, ...);
int syscmd_process(int argc, char** argv, shell_handle_func func);

#ifdef __cplusplus
}
#endif

#endif