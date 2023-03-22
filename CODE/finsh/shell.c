/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-04-30     Bernard      the first version for FinSH
 * 2006-05-08     Bernard      change finsh thread stack to 2048
 * 2006-06-03     Bernard      add support for skyeye
 * 2006-09-24     Bernard      remove the code related with hardware
 * 2010-01-18     Bernard      fix down then up key bug.
 * 2010-03-19     Bernard      fix backspace issue and fix device read in shell.
 * 2010-04-01     Bernard      add prompt output when start and remove the empty history
 * 2011-02-23     Bernard      fix variable section end issue of finsh shell
 *                             initialization when use GNU GCC compiler.
 * 2016-11-26     armink       add password authentication
 * 2018-07-02     aozima       add custom prompt support.
 */

#include <finsh_api.h>

#ifdef RT_USING_FINSH

#include "finsh.h"
#include "shell.h"

#ifdef FINSH_USING_MSH
#include "msh.h"
#endif

#ifdef _WIN32
#include <stdio.h> /* for putchar */
#endif

/* finsh thread */
#ifndef RT_USING_HEAP
static struct rt_thread finsh_thread;
__ALIGN(ALIGN_SIZE)
static char finsh_thread_stack[FINSH_THREAD_STACK_SIZE];
struct finsh_shell _shell;
#endif

/* finsh symtab */
#ifdef FINSH_USING_SYMTAB
struct finsh_syscall *_syscall_table_begin  = NULL;
struct finsh_syscall *_syscall_table_end    = NULL;
struct finsh_sysvar *_sysvar_table_begin    = NULL;
struct finsh_sysvar *_sysvar_table_end      = NULL;
#endif

struct finsh_shell *shell;
static char *finsh_prompt_custom = NULL;

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
struct finsh_syscall* finsh_syscall_next(struct finsh_syscall* call)
{
    unsigned int *ptr;
    ptr = (unsigned int*) (call + 1);
    while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*) _syscall_table_end))
        ptr ++;

    return (struct finsh_syscall*)ptr;
}

struct finsh_sysvar* finsh_sysvar_next(struct finsh_sysvar* call)
{
    unsigned int *ptr;
    ptr = (unsigned int*) (call + 1);
    while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*) _sysvar_table_end))
        ptr ++;

    return (struct finsh_sysvar*)ptr;
}
#endif /* defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__)) */

#ifdef RT_USING_HEAP
int finsh_set_prompt(const char * prompt)
{
    if(finsh_prompt_custom)
    {
        free(finsh_prompt_custom);
        finsh_prompt_custom = NULL;
    }

    /* strdup */
    if(prompt)
    {
        finsh_prompt_custom = (char *)malloc(strlen(prompt)+1);
        if(finsh_prompt_custom)
        {
            strcpy(finsh_prompt_custom, prompt);
        }
    }

    return 0;
}
#endif /* RT_USING_HEAP */

#if defined(RT_USING_DFS)
#include <dfs_posix.h>
#endif /* RT_USING_DFS */

const char *finsh_get_prompt(void)
{
#define _MSH_PROMPT "msh "
#define _PROMPT     "finsh "
    static char finsh_prompt[RT_CONSOLEBUF_SIZE + 1] = {0};

    /* check prompt mode */
    if (!shell->prompt_mode)
    {
        finsh_prompt[0] = '\0';
        return finsh_prompt;
    }

    if(finsh_prompt_custom)
    {
        strncpy(finsh_prompt, finsh_prompt_custom, sizeof(finsh_prompt)-1);
        return finsh_prompt;
    }

#ifdef FINSH_USING_MSH
    if (msh_is_used()) strcpy(finsh_prompt, _MSH_PROMPT);
    else
#endif
        strcpy(finsh_prompt, _PROMPT);

#if defined(RT_USING_DFS) && defined(DFS_USING_WORKDIR)
    /* get current working directory */
    getcwd(&finsh_prompt[strlen(finsh_prompt)], RT_CONSOLEBUF_SIZE - strlen(finsh_prompt));
#endif

    strcat(finsh_prompt, ">");

    return finsh_prompt;
}

/**
 * @ingroup finsh
 *
 * This function get the prompt mode of finsh shell.
 *
 * @return prompt the prompt mode, 0 disable prompt mode, other values enable prompt mode.
 */
uint32_t finsh_get_prompt_mode(void)
{
    ASSERT(shell != NULL);
    return shell->prompt_mode;
}

/**
 * @ingroup finsh
 *
 * This function set the prompt mode of finsh shell.
 *
 * The parameter 0 disable prompt mode, other values enable prompt mode.
 *
 * @param prompt the prompt mode
 */
void finsh_set_prompt_mode(uint32_t prompt_mode)
{
    ASSERT(shell != NULL);
    shell->prompt_mode = prompt_mode;
}

static int finsh_getchar(void)
{
#ifdef RT_USING_POSIX
    return getchar();
#else
    char ch = 0;

    ASSERT(shell != NULL);
    while (device_read(shell->device, -1, &ch, 1) != 1)
        os_sem_take(shell->rx_sem, OS_WAIT_FOREVER);

    return (int)ch;
#endif
}

#if !defined(RT_USING_POSIX) && defined(RT_USING_DEVICE)
static err_t finsh_rx_ind(device_t dev, size_t size)
{
    ASSERT(shell != NULL);

    /* release semaphore to let finsh thread rx data */
    os_sem_release(shell->rx_sem);

    return E_OK;
}

/**
 * @ingroup finsh
 *
 * This function sets the input device of finsh shell.
 *
 * @param device_name the name of new input device.
 */
void finsh_set_device(const char *device_name)
{
    device_t dev = NULL;

    ASSERT(shell != NULL);
    dev = device_find(device_name);
    if (dev == NULL)
    {
        printf("finsh: can not find device: %s\n", device_name);
        return;
    }

    /* check whether it's a same device */
    if (dev == shell->device) return;
    /* open this device and set the new device in finsh shell */
    if (device_open(dev, DEVICE_OFLAG_RDWR | DEVICE_FLAG_INT_RX | \
                       DEVICE_FLAG_STREAM) == E_OK)
    {
        if (shell->device != NULL)
        {
            /* close old finsh device */
            device_close(shell->device);
            device_set_rx_indicate(shell->device, NULL);
        }

        /* clear line buffer before switch to new device */
        memset(shell->line, 0, sizeof(shell->line));
        shell->line_curpos = shell->line_position = 0;

        shell->device = dev;
        device_set_rx_indicate(dev, finsh_rx_ind);
    }
}

/**
 * @ingroup finsh
 *
 * This function sets the input device of finsh shell but won't open it.
 *
 * @param device_name the name of new input device.
 */
void finsh_set_device_without_open(const char *device_name)
{
	device_t dev = NULL;

	if(shell == NULL) {
		/* finsh system is not initialized yet */
		return ;
	}

	dev = device_find(device_name);

	if(dev == NULL) {
		printf("finsh: can not find device: %s\n", device_name);
		return;
	}

	/* device should be opened by upper layer console */
	if(shell->device != NULL) {
		/* clear the rx indicate of old device */
		device_set_rx_indicate(shell->device, NULL);
	}

	/* clear line buffer before switch to new device */
	memset(shell->line, 0, sizeof(shell->line));
	shell->line_curpos = shell->line_position = 0;

	/* set new shell device */
	shell->device = dev;
	/* set rx indicate for new deivce */
	device_set_rx_indicate(dev, finsh_rx_ind);
}

/**
 * @ingroup finsh
 *
 * This function returns current finsh shell input device.
 *
 * @return the finsh shell input device name is returned.
 */
const char *finsh_get_device()
{
    ASSERT(shell != NULL);
    return shell->device->name;
}
#endif

/**
 * @ingroup finsh
 *
 * This function set the echo mode of finsh shell.
 *
 * FINSH_OPTION_ECHO=0x01 is echo mode, other values are none-echo mode.
 *
 * @param echo the echo mode
 */
void finsh_set_echo(uint32_t echo)
{
    ASSERT(shell != NULL);
    shell->echo_mode = (uint8_t)echo;
}

/**
 * @ingroup finsh
 *
 * This function gets the echo mode of finsh shell.
 *
 * @return the echo mode
 */
uint32_t finsh_get_echo()
{
    ASSERT(shell != NULL);

    return shell->echo_mode;
}

#ifdef FINSH_USING_AUTH
/**
 * set a new password for finsh
 *
 * @param password new password
 *
 * @return result, E_OK on OK, -E_RROR on the new password length is less than
 *  FINSH_PASSWORD_MIN or greater than FINSH_PASSWORD_MAX
 */
err_t finsh_set_password(const char *password) {
    ubase_t level;
    size_t pw_len = strlen(password);

    if (pw_len < FINSH_PASSWORD_MIN || pw_len > FINSH_PASSWORD_MAX)
        return -E_RROR;

    level = os_hw_interrupt_disable();
    strncpy(shell->password, password, FINSH_PASSWORD_MAX);
    os_hw_interrupt_enable(level);

    return E_OK;
}

/**
 * get the finsh password
 *
 * @return password
 */
const char *finsh_get_password(void)
{
    return shell->password;
}

static void finsh_wait_auth(void)
{
    int ch;
    bool_t input_finish = FALSE;
    char password[FINSH_PASSWORD_MAX] = { 0 };
    size_t cur_pos = 0;
    /* password not set */
    if (strlen(finsh_get_password()) == 0) return;

    while (1)
    {
        printf("Password for login: ");
        while (!input_finish)
        {
            while (1)
            {
                /* read one character from device */
                ch = finsh_getchar();
                if (ch < 0)
                {
                    continue;
                }

                if (ch >= ' ' && ch <= '~' && cur_pos < FINSH_PASSWORD_MAX)
                {
                    /* change the printable characters to '*' */
                    printf("*");
                    password[cur_pos++] = ch;
                }
                else if (ch == '\b' && cur_pos > 0)
                {
                    /* backspace */
                    cur_pos--;
                    password[cur_pos] = '\0';
                    printf("\b \b");
                }
                else if (ch == '\r' || ch == '\n')
                {
                    printf("\n");
                    input_finish = TRUE;
                    break;
                }
            }
        }
        if (!rt_strncmp(shell->password, password, FINSH_PASSWORD_MAX)) return;
        else
        {
            /* authentication failed, delay 2S for retry */
            rt_thread_delay(2 * RT_TICK_PER_SECOND);
            printf("Sorry, try again.\n");
            cur_pos = 0;
            input_finish = FALSE;
            rt_memset(password, '\0', FINSH_PASSWORD_MAX);
        }
    }
}
#endif /* FINSH_USING_AUTH */

static void shell_auto_complete(char *prefix)
{

    printf("\n");
#ifdef FINSH_USING_MSH
    if (msh_is_used() == TRUE)
    {
        msh_auto_complete(prefix);
    }
    else
#endif
    {
#ifndef FINSH_USING_MSH_ONLY
        extern void list_prefix(char * prefix);
        list_prefix(prefix);
#endif
    }

    printf("%s%s", FINSH_PROMPT, prefix);
}

#ifndef FINSH_USING_MSH_ONLY
void finsh_run_line(struct finsh_parser *parser, const char *line)
{
    const char *err_str;

    if(shell->echo_mode)
        printf("\n");
    finsh_parser_run(parser, (unsigned char *)line);

    /* compile node root */
    if (finsh_errno() == 0)
    {
        finsh_compiler_run(parser->root);
    }
    else
    {
        err_str = finsh_error_string(finsh_errno());
        printf("%s\n", err_str);
    }

    /* run virtual machine */
    if (finsh_errno() == 0)
    {
        char ch;
        finsh_vm_run();

        ch = (unsigned char)finsh_stack_bottom();
        if (ch > 0x20 && ch < 0x7e)
        {
            printf("\t'%c', %d, 0x%08x\n",
                       (unsigned char)finsh_stack_bottom(),
                       (unsigned int)finsh_stack_bottom(),
                       (unsigned int)finsh_stack_bottom());
        }
        else
        {
            printf("\t%d, 0x%08x\n",
                       (unsigned int)finsh_stack_bottom(),
                       (unsigned int)finsh_stack_bottom());
        }
    }

    finsh_flush(parser);
}
#endif

#ifdef FINSH_USING_HISTORY
static bool_t shell_handle_history(struct finsh_shell *shell)
{
#if defined(_WIN32)
    int i;
    printf("\r");

    for (i = 0; i <= 60; i++)
        putchar(' ');
    printf("\r");

#else
    printf("\033[2K\r");
#endif
    printf("%s%s", FINSH_PROMPT, shell->line);
    return FALSE;
}

static void shell_push_history(struct finsh_shell *shell)
{
    if (shell->line_position != 0)
    {
        /* push history */
        if (shell->history_count >= FINSH_HISTORY_LINES)
        {
            /* if current cmd is same as last cmd, don't push */
            if (memcmp(&shell->cmd_history[FINSH_HISTORY_LINES - 1], shell->line, FINSH_CMD_SIZE))
            {
                /* move history */
                int index;
                for (index = 0; index < FINSH_HISTORY_LINES - 1; index ++)
                {
                    memcpy(&shell->cmd_history[index][0],
                           &shell->cmd_history[index + 1][0], FINSH_CMD_SIZE);
                }
                memset(&shell->cmd_history[index][0], 0, FINSH_CMD_SIZE);
                memcpy(&shell->cmd_history[index][0], shell->line, shell->line_position);

                /* it's the maximum history */
                shell->history_count = FINSH_HISTORY_LINES;
            }
        }
        else
        {
            /* if current cmd is same as last cmd, don't push */
            if (shell->history_count == 0 || memcmp(&shell->cmd_history[shell->history_count - 1], shell->line, FINSH_CMD_SIZE))
            {
                shell->current_history = shell->history_count;
                memset(&shell->cmd_history[shell->history_count][0], 0, FINSH_CMD_SIZE);
                memcpy(&shell->cmd_history[shell->history_count][0], shell->line, shell->line_position);

                /* increase count and set current history position */
                shell->history_count ++;
            }
        }
    }
    shell->current_history = shell->history_count;
}
#endif

void finsh_thread_entry(void *parameter)
{
    int ch;

    /* normal is echo mode */
#ifndef FINSH_ECHO_DISABLE_DEFAULT
    shell->echo_mode = 1;
#else
    shell->echo_mode = 0;
#endif

#ifndef FINSH_USING_MSH_ONLY
    finsh_init(&shell->parser);
#endif

#if !defined(RT_USING_POSIX) && defined(RT_USING_DEVICE)
    /* set console device as shell device */
    if (shell->device == NULL)
    {
        device_t console = console_get_device();
        if (console)
        {
            SELF_CHECK(console_enable_input());
        }
    }
#endif

#ifdef FINSH_USING_AUTH
    /* set the default password when the password isn't setting */
    if (strlen(finsh_get_password()) == 0)
    {
        if (finsh_set_password(FINSH_DEFAULT_PASSWORD) != E_OK)
        {
            printf("Finsh password set failed.\n");
        }
    }
    /* waiting authenticate success */
    finsh_wait_auth();
#endif
    extern void show_version();
    show_version();
    printf(FINSH_PROMPT);

    while (1)
    {
        ch = finsh_getchar();
        if (ch < 0)
        {
            continue;
        }

        /*
         * handle control key
         * up key  : 0x1b 0x5b 0x41
         * down key: 0x1b 0x5b 0x42
         * right key:0x1b 0x5b 0x43
         * left key: 0x1b 0x5b 0x44
         */
        if (ch == 0x1b)
        {
            shell->stat = WAIT_SPEC_KEY;
            continue;
        }
        else if (shell->stat == WAIT_SPEC_KEY)
        {
            if (ch == 0x5b)
            {
                shell->stat = WAIT_FUNC_KEY;
                continue;
            }

            shell->stat = WAIT_NORMAL;
        }
        else if (shell->stat == WAIT_FUNC_KEY)
        {
            shell->stat = WAIT_NORMAL;

            if (ch == 0x41) /* up key */
            {
#ifdef FINSH_USING_HISTORY
                /* prev history */
                if (shell->current_history > 0)
                    shell->current_history --;
                else
                {
                    shell->current_history = 0;
                    continue;
                }

                /* copy the history command */
                memcpy(shell->line, &shell->cmd_history[shell->current_history][0],
                       FINSH_CMD_SIZE);
                shell->line_curpos = shell->line_position = strlen(shell->line);
                shell_handle_history(shell);
#endif
                continue;
            }
            else if (ch == 0x42) /* down key */
            {
#ifdef FINSH_USING_HISTORY
                /* next history */
                if (shell->current_history < shell->history_count - 1)
                    shell->current_history ++;
                else
                {
                    /* set to the end of history */
                    if (shell->history_count != 0)
                        shell->current_history = shell->history_count - 1;
                    else
                        continue;
                }

                memcpy(shell->line, &shell->cmd_history[shell->current_history][0],
                       FINSH_CMD_SIZE);
                shell->line_curpos = shell->line_position = strlen(shell->line);
                shell_handle_history(shell);
#endif
                continue;
            }
            else if (ch == 0x44) /* left key */
            {
                if (shell->line_curpos)
                {
                    printf("\b");
                    shell->line_curpos --;
                }

                continue;
            }
            else if (ch == 0x43) /* right key */
            {
                if (shell->line_curpos < shell->line_position)
                {
                    printf("%c", shell->line[shell->line_curpos]);
                    shell->line_curpos ++;
                }

                continue;
            }
        }

        /* received null or error */
        if (ch == '\0' || ch == 0xFF) continue;
        /* handle tab key */
        else if (ch == '\t')
        {
            int i;
            /* move the cursor to the beginning of line */
            for (i = 0; i < shell->line_curpos; i++)
                printf("\b");

            /* auto complete */
            shell_auto_complete(&shell->line[0]);
            /* re-calculate position */
            shell->line_curpos = shell->line_position = strlen(shell->line);

            continue;
        }
        /* handle backspace key */
        else if (ch == 0x7f || ch == 0x08)
        {
            /* note that shell->line_curpos >= 0 */
            if (shell->line_curpos == 0)
                continue;

            shell->line_position--;
            shell->line_curpos--;

            if (shell->line_position > shell->line_curpos)
            {
                int i;

                memmove(&shell->line[shell->line_curpos],
                           &shell->line[shell->line_curpos + 1],
                           shell->line_position - shell->line_curpos);
                shell->line[shell->line_position] = 0;

                printf("\b%s  \b", &shell->line[shell->line_curpos]);

                /* move the cursor to the origin position */
                for (i = shell->line_curpos; i <= shell->line_position; i++)
                    printf("\b");
            }
            else
            {
                printf("\b \b");
                shell->line[shell->line_position] = 0;
            }

            continue;
        }

        /* handle end of line, break */
        if (ch == '\r' || ch == '\n')
        {
#ifdef FINSH_USING_HISTORY
            shell_push_history(shell);
#endif

#ifdef FINSH_USING_MSH
            if (msh_is_used() == TRUE)
            {
                if (shell->echo_mode)
                    printf("\n");
                msh_exec(shell->line, shell->line_position);
            }
            else
#endif
            {
#ifndef FINSH_USING_MSH_ONLY
                /* add ';' and run the command line */
                shell->line[shell->line_position] = ';';

                if (shell->line_position != 0) finsh_run_line(&shell->parser, shell->line);
                else
                    if (shell->echo_mode) printf("\n");
#endif
            }

            printf(FINSH_PROMPT);
            memset(shell->line, 0, sizeof(shell->line));
            shell->line_curpos = shell->line_position = 0;
            continue;
        }

        /* it's a large line, discard it */
        if (shell->line_position >= FINSH_CMD_SIZE)
            shell->line_position = 0;

        /* normal character */
        if (shell->line_curpos < shell->line_position)
        {
            int i;

            memmove(&shell->line[shell->line_curpos + 1],
                       &shell->line[shell->line_curpos],
                       shell->line_position - shell->line_curpos);
            shell->line[shell->line_curpos] = ch;
            if (shell->echo_mode)
                printf("%s", &shell->line[shell->line_curpos]);

            /* move the cursor to new position */
            for (i = shell->line_curpos; i < shell->line_position; i++)
                printf("\b");
        }
        else
        {
            shell->line[shell->line_position] = ch;
            if (shell->echo_mode)
                printf("%c", ch);
        }

        ch = 0;
        shell->line_position ++;
        shell->line_curpos++;
        if (shell->line_position >= FINSH_CMD_SIZE)
        {
            /* clear command line */
            shell->line_position = 0;
            shell->line_curpos = 0;
        }
    } /* end of device read */
}

void finsh_system_function_init(const void *begin, const void *end)
{
    _syscall_table_begin = (struct finsh_syscall *) begin;
    _syscall_table_end = (struct finsh_syscall *) end;
}

void finsh_system_var_init(const void *begin, const void *end)
{
    _sysvar_table_begin = (struct finsh_sysvar *) begin;
    _sysvar_table_end = (struct finsh_sysvar *) end;
}

#if defined(__ICCARM__) || defined(__ICCRX__)               /* for IAR compiler */
#ifdef FINSH_USING_SYMTAB
#pragma section="FSymTab"
#pragma section="VSymTab"
#endif
#elif defined(__ADSPBLACKFIN__) /* for VisaulDSP++ Compiler*/
#ifdef FINSH_USING_SYMTAB
extern "asm" int __fsymtab_start;
extern "asm" int __fsymtab_end;
extern "asm" int __vsymtab_start;
extern "asm" int __vsymtab_end;
#endif
#elif defined(_MSC_VER)
#pragma section("FSymTab$a", read)
const char __fsym_begin_name[] = "__start";
const char __fsym_begin_desc[] = "begin of finsh";
__declspec(allocate("FSymTab$a")) const struct finsh_syscall __fsym_begin =
{
    __fsym_begin_name,
    __fsym_begin_desc,
    NULL
};

#pragma section("FSymTab$z", read)
const char __fsym_end_name[] = "__end";
const char __fsym_end_desc[] = "end of finsh";
__declspec(allocate("FSymTab$z")) const struct finsh_syscall __fsym_end =
{
    __fsym_end_name,
    __fsym_end_desc,
    NULL
};
#endif

/*
 * @ingroup finsh
 *
 * This function will initialize finsh shell
 */
int finsh_system_init(void)
{
    err_t result = E_OK;
    os_thread_t tid;

#ifdef FINSH_USING_SYMTAB
#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
    extern const int FSymTab$$Base;
    extern const int FSymTab$$Limit;
    extern const int VSymTab$$Base;
    extern const int VSymTab$$Limit;
    finsh_system_function_init(&FSymTab$$Base, &FSymTab$$Limit);
#ifndef FINSH_USING_MSH_ONLY
    finsh_system_var_init(&VSymTab$$Base, &VSymTab$$Limit);
#endif
#elif defined (__ICCARM__) || defined(__ICCRX__)      /* for IAR Compiler */
    finsh_system_function_init(__section_begin("FSymTab"),
                               __section_end("FSymTab"));
    finsh_system_var_init(__section_begin("VSymTab"),
                          __section_end("VSymTab"));
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__)
    /* GNU GCC Compiler and TI CCS */
    extern const int __fsymtab_start;
    extern const int __fsymtab_end;
    extern const int __vsymtab_start;
    extern const int __vsymtab_end;
    finsh_system_function_init(&__fsymtab_start, &__fsymtab_end);
    finsh_system_var_init(&__vsymtab_start, &__vsymtab_end);
#elif defined(__ADSPBLACKFIN__) /* for VisualDSP++ Compiler */
    finsh_system_function_init(&__fsymtab_start, &__fsymtab_end);
    finsh_system_var_init(&__vsymtab_start, &__vsymtab_end);
#elif defined(_MSC_VER)
    unsigned int *ptr_begin, *ptr_end;

    if(shell)
    {
        printf("finsh shell already init.\n");
        return E_OK;
    }

    ptr_begin = (unsigned int *)&__fsym_begin;
    ptr_begin += (sizeof(struct finsh_syscall) / sizeof(unsigned int));
    while (*ptr_begin == 0) ptr_begin ++;

    ptr_end = (unsigned int *) &__fsym_end;
    ptr_end --;
    while (*ptr_end == 0) ptr_end --;

    finsh_system_function_init(ptr_begin, ptr_end);
#endif
#endif

    /* create or set shell structure */
    shell = (struct finsh_shell *)calloc(1, sizeof(struct finsh_shell));
    if (shell == NULL)
    {
        printf("no memory for shell\n");
        return -1;
    }

    shell->rx_sem = os_sem_create(1);
    os_sem_take(shell->rx_sem, OS_WAIT_FOREVER);

    finsh_set_prompt_mode(1);

    tid = os_thread_create(FINSH_THREAD_NAME,
                           finsh_thread_entry, NULL,
                           FINSH_THREAD_PRIORITY, FINSH_THREAD_STACK_SIZE);

    if (tid != NULL && result == E_OK)
        os_thread_startup(tid);
    return 0;
}

#endif /* RT_USING_FINSH */

