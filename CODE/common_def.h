// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/1.
//

#ifndef X7PRO_DRIVER_COMMON_DEF_H
#define X7PRO_DRIVER_COMMON_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __CLANG_ARM
#endif

#if defined(__CC_ARM)          /* ARM C Compiler */
#include "cmsis_armcc.h"
#include <rt_sys.h>
#include <errno.h>

#define	O_RDONLY	0		/* +1 == FREAD */
#define	O_WRONLY	1		/* +1 == FWRITE */
#define	O_RDWR		2		/* +1 == FREAD|FWRITE */
#define	O_APPEND	_FAPPEND
#define	O_CREAT		_FCREAT
#define	O_TRUNC		_FTRUNC
#define	O_EXCL		_FEXCL
#define O_SYNC		_FSYNC
#define	_FOPEN		(-1)	/* from sys/file.h, kernel use only */
#define	_FREAD		0x0001	/* read enabled */
#define	_FWRITE		0x0002	/* write enabled */
#define	_FAPPEND	0x0008	/* append (writes guaranteed at the end) */
#define	_FMARK		0x0010	/* internal; mark during gc() */
#define	_FDEFER		0x0020	/* internal; defer for next gc pass */
#define	_FASYNC		0x0040	/* signal pgrp when data ready */
#define	_FSHLOCK	0x0080	/* BSD flock() shared lock present */
#define	_FEXLOCK	0x0100	/* BSD flock() exclusive lock present */
#define	_FCREAT		0x0200	/* open with file create */
#define	_FTRUNC		0x0400	/* open with truncation */
#define	_FEXCL		0x0800	/* error on open if file exists */
#define	_FNBIO		0x1000	/* non blocking I/O (sys5 style) */
#define	_FSYNC		0x2000	/* do all writes synchronously */
#define	_FNONBLOCK	0x4000	/* non blocking I/O (POSIX style) */
#define	_FNDELAY	_FNONBLOCK	/* non blocking I/O (4.2 style) */
#define	_FNOCTTY	0x8000	/* don't assign a ctty on this open */

typedef uint32_t mode_t;
#elif defined(__GNUC__)
#include "cmsis_gcc.h"
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
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

#define SOFT_DELAY(__endtime)   for (size_t start = 0; start < __endtime; ++start)
#define SELF_CHECK(func)        ASSERT(func == E_OK)




#endif //X7PRO_DRIVER_COMMON_DEF_H
