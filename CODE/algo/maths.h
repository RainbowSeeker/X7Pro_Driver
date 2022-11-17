// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef _SWAP_H
#define _SWAP_H

#include "stdio.h"
#include <stdarg.h>
#include "math.h"

#define ARRAYLEN(x)         (sizeof(x) / sizeof((x)[0]))

#define max(_X1, _X2)       (((_X1) > (_X2)) ? (_X1) : (_X2))
#define min(_X1, _X2)       (((_X1) < (_X2)) ? (_X1) : (_X2))

static inline uint16_t swap_u16(uint16_t num)
{
    return __builtin_bswap16(num);
}

static inline int16_t swap_i16(int16_t num)
{
    return __builtin_bswap16(num);
}
static inline int constrain(int amt, int low, int high)
{
    if (amt < low)
        return low;
    else if (amt > high)
        return high;
    else
        return amt;
}

static inline float constrainf(float amt, float low, float high)
{
    if (amt < low)
        return low;
    else if (amt > high)
        return high;
    else
        return amt;
}

// non ISO variant from linux kernel; checks ptr type, but triggers 'ISO C forbids braced-groups within expressions [-Wpedantic]'
//  __extension__ is here to disable this warning
#define container_of(ptr, type, member)  ( __extension__ ({     \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );}))

static inline int16_t cmp16(uint16_t a, uint16_t b) { return (int16_t)(a-b); }
static inline int32_t cmp32(uint32_t a, uint32_t b) { return (int32_t)(a-b); }

static inline uint32_t llog2(uint32_t n) { return 31 - __builtin_clz(n | 1); }

#endif //_SWAP_H
