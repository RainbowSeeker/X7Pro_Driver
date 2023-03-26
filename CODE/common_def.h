// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/1.
//

#ifndef X7PRO_DRIVER_COMMON_DEF_H
#define X7PRO_DRIVER_COMMON_DEF_H

#include <rtconfig.h>

//libc header file
#include "lib/libc/libc_dirent.h"
#include "lib/libc/libc_errno.h"
#include "lib/libc/libc_fcntl.h"
#include "lib/libc/libc_fdset.h"
#include "lib/libc/libc_ioctl.h"
#include "lib/libc/libc_limits.h"
#include "lib/libc/libc_signal.h"
#include "lib/libc/libc_stat.h"
#include "lib/libc/libc_stdio.h"

#if defined(__CC_ARM) || defined(__CLANG_ARM) || defined(__IAR_SYSTEMS_ICC__)
typedef signed long off_t;
typedef int mode_t;
#endif

#if defined(__MINGW32__) || defined(_WIN32)
typedef signed long off_t;
typedef int mode_t;
#endif


#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __CLANG_ARM
#endif

typedef _Bool                   bool_t;      /**< boolean type */
typedef long                    base_t;      /**< Nbit CPU related date type */
typedef unsigned long           ubase_t;     /**< Nbit unsigned CPU related data type */

typedef int                     err_t;       /**< Type for error number */
typedef uint32_t                tick_t;      /**< Type for tick count */
typedef base_t                  flag_t;      /**< Type for flags */

//typedef ubase_t                 size_t;      /**< Type for size number */
//typedef ubase_t                 dev_t;       /**< Type for device */
typedef base_t                  off_t;       /**< Type for offset */

/* boolean type definitions */
#define TRUE                         1               /**< boolean true  */
#define FALSE                        0               /**< boolean fails */

#ifndef __INT8_MAX__
#define UINT8_MAX                    0xff            /**< Maxium number of UINT8 */
#endif
#ifndef __INT16_MAX__
#define UINT16_MAX                   0xffff          /**< Maxium number of UINT16 */
#endif
#ifndef __INT32_MAX__
#define UINT32_MAX                   0xffffffff      /**< Maxium number of UINT32 */
#endif

#define NAME_MAX_LEN              20

#define TICK_MAX                     UINT32_MAX   /**< Maxium number of tick */

/* Compiler Related Definitions */
#if defined(__CC_ARM) || defined(__CLANG_ARM)           /* ARM Compiler */
    #include <stdarg.h>
    #define SECTION(x)                  __attribute__((section(x)))
    #define __UNUSED                    __attribute__((unused))
    #define __USED                      __attribute__((used))
    #define __ALIGN(n)                  __attribute__((aligned(n)))
    #define __WEAK                      __attribute__((weak))
    #define static_inline               static __inline
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    /* the version of GNU GCC must be greater than 4.x */
    typedef __builtin_va_list           __gnuc_va_list;
    typedef __gnuc_va_list              va_list;
    #define va_start(v,l)               __builtin_va_start(v,l)
    #define va_end(v)                   __builtin_va_end(v)
    #define va_arg(v,l)                 __builtin_va_arg(v,l)

    #define SECTION(x)                  __attribute__((section(x)))
    #define __UNUSED                    __attribute__((unused))
    #define __USED                      __attribute__((used))
    #define __ALIGN(n)                  __attribute__((aligned(n)))
    #define __WEAK                      __attribute__((weak))
    #define static_inline               static __inline
#endif

#define ALIGN_SIZE                   4
/**
 * @ingroup BasicDef
 *
 * @def ALIGN(size, align)
 * Return the most contiguous size aligned at specified width. ALIGN(13, 4)
 * would return 16.
 */
#define ALIGN(size, align)           (((size) + (align) - 1) & ~((align) - 1))

/**
 * @ingroup BasicDef
 *
 * @def ALIGN_DOWN(size, align)
 * Return the down number of aligned at specified width. ALIGN_DOWN(13, 4)
 * would return 12.
 */
#define ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

/**
 *  match string1 and string2
 */
#define MATCH(_str1, _str2)         (strncmp(_str1, _str2, strlen(_str2)) == 0)

/**
 * get length of array
 */
#define ARRAY_LEN(_arr)             (sizeof(_arr) / sizeof(_arr[0]))

/**
 * get maximum of x1 & x2
 */
#ifndef MAX
#define MAX(_X1, _X2)       (((_X1) > (_X2)) ? (_X1) : (_X2))
#endif
/**
 * get minimum of x1 & x2
 */
#ifndef MIN
#define MIN(_X1, _X2)       (((_X1) < (_X2)) ? (_X1) : (_X2))
#endif

// Macro to define packed structures
#ifdef __GNUC__
#define __PACKED__(__Declaration__) __Declaration__ __attribute__((packed))
#else
#define __PACKED__(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#endif

#ifndef PI
#define PI 3.14159265358979f
#endif

#ifndef STRING
#define STRING_(...) #__VA_ARGS__
#define STRING(...) STRING_(__VA_ARGS__)
#endif

#ifndef CONTACT
#define CONTACT_(x,y) x ## y
#define CONTACT(x, y) CONTACT_(x, y)
#endif


#define OBJECT_HOOK_CALL(func, argv) \
    do { if ((func) != NULL) func argv; } while (0)

enum err_status
{
    E_OK = 0,         /**< There is no error */
    E_RROR = 1,       /**< A generic error happens */
    E_TIMEOUT = 2,    /**< Timed out */
    E_FULL = 3,       /**< The resource is full */
    E_EMPTY = 4,      /**< The resource is empty */
    E_NOMEM = 5,      /**< No memory */
    E_NOSYS = 6,      /**< No system */
    E_BUSY = 7,       /**< Busy */
    E_IO = 8,         /**< IO error */
    E_INTR = 9,       /**< Interrupted system call */
    E_INVAL = 10,     /**< Invalid argument */
    E_NOTHANDLE = 11, /**< Not handled */
};

typedef struct {
    uint32_t period;
    char* info;
}model_info_t;


#define ERROR_TRY(__exp)                                                                                \
    do {                                                                                              \
        err_t err = (__exp);                                                                      \
        if (err != E_OK) {                                                                         \
            printf("\r\nError occur at function: %s, in file: \n%s, line:%d, err:%d\r\n", __FUNCTION__, __FILE__, __LINE__, err); \
            return err;                                                                               \
        }                                                                                             \
    } while (false)

#define SELF_CHECK(func)        ASSERT(func == E_OK)

#endif //X7PRO_DRIVER_COMMON_DEF_H
