// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_OS_COMMON_H
#define X7PRO_DRIVER_OS_COMMON_H
#include "rtdebug.h"
#include "os.h"
#include "common_def.h"
#include "system/systime.h"
#include "utils/list.h"
#include "object.h"
#include "system/systime.h"

/* Thread Prority MUST BE !!!UNIQUE!!! */
#define VEHICLE_THREAD_PRIORITY     2
#define FMTIO_THREAD_PRIORITY       3
#define LOGGER_THREAD_PRIORITY      4
#define MAVLINK_RX_THREAD_PRIORITY  5
#define COMM_THREAD_PRIORITY        6
#define STATUS_THREAD_PRIORITY      7

#define FINSH_THREAD_PRIORITY       0
#define GPS_PROBE_THREAD_PRIORITY   10
#define WQ_HP_THREAD_PRIORITY       1
#define WQ_LP_THREAD_PRIORITY       19
#define STARTUP_THREAD_PRIORITY     20
#define STARTUP_TASK_STK_SIZE       1024

#define OS_MAX_PRIORITY             64

#if OS_MAX_PRIORITY != OS_CFG_PRIO_MAX
#error "must ensure that 'OS_MAX_PRIORITY' equal 'OS_CFG_PRIO_MAX' "
#endif

/* note: modify the following micro according to your os */
#define OS_ENTER_CRITICAL()     CPU_SR_ALLOC();CPU_CRITICAL_ENTER()
#define OS_EXIT_CRITICAL()      CPU_CRITICAL_EXIT()

#define TICK_PER_SECOND         OS_CFG_TICK_RATE_HZ
#define TICKS_FROM_MS(_ms)      ((TICK_PER_SECOND * _ms + 999) / 1000)

#define OS_WAITING_FOREVER      (size_t)(-1)


/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __ffs(int value);

void *memset(void *src, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

int strncmp(const char *cs, const char *ct, size_t count);
int strcmp(const char *cs, const char *ct);
size_t strlen(const char *src);
char *strdup(const char *s);
#if defined(__CC_ARM) || defined(__CLANG_ARM)
/* leak strdup interface */
char* strdup(const char* str);
#endif

char *strstr(const char *str1, const char *str2);
int sscanf(const char *buf, const char *fmt, ...);
char *strncpy(char *dest, const char *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *cs, const void *ct, size_t count);
int strcasecmp(const char *a, const char *b);


/*
 * This function will get errno
 *
 * @return errno
 */
err_t os_get_errno(void);

/*
 * This function will set errno
 *
 * @param error the errno shall be set
 */
void os_set_errno(err_t error);

/**
 * This function returns errno.
 *
 * @return the errno in the system
 */
int *_os_errno(void);

/**
 *
 * @param OS_TASK_PTR
 */
void bsp_os_init(void (*StartupTask)(void *p_arg));

/**
 * os_tick_get
 * @return
 */
static_inline tick_t os_tick_get(void)
{
    return systime_now_ms();
}

/**
 * os_delay
 * @param ms
 */
static_inline void os_delay(uint32_t ms)
{
    OS_ERR err;
    OSTimeDly(TICKS_FROM_MS(ms), OS_OPT_TIME_DLY, &err);
}

/**
 * os_delay_until
 * @param init_tick
 * @param ms
 */
static_inline void os_delay_until(uint32_t *init_tick, uint32_t ms)
{
    OS_ERR err;
    OSTimeDly(TICKS_FROM_MS(ms), OS_OPT_TIME_DLY, &err);
}

/**
 * os_hw_interrupt_disable
 * @return
 */
static_inline base_t os_hw_interrupt_disable(void)
{
    return CPU_SR_Save(CPU_CFG_KA_IPL_BOUNDARY << (8u - CPU_CFG_NVIC_PRIO_BITS));
}

/**
 * os_hw_interrupt_enable
 * @param x
 */
static_inline void os_hw_interrupt_enable(base_t x)
{
    CPU_SR_Restore(x);
}

/**
 * os_interrupt_get_nest
 * @return
 */
static_inline uint8_t os_interrupt_get_nest(void)
{
    return OSIntNestingCtr;
}

static_inline void os_interrupt_enter(void)
{
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    OSIntEnter();                                               /* Tell uC/OS-III that we are starting an ISR           */
    CPU_CRITICAL_EXIT();
}

static_inline void os_interrupt_leave(void)
{
    OSIntExit();
}


#endif //X7PRO_DRIVER_OS_COMMON_H
