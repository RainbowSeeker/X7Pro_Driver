// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef _SWAP_H
#define _SWAP_H

#include <stdarg.h>
#include "math.h"

#define ARRAYLEN(x)         (sizeof(x) / sizeof((x)[0]))

#define MAX(_X1, _X2)       (((_X1) > (_X2)) ? (_X1) : (_X2))
#define MIN(_X1, _X2)       (((_X1) < (_X2)) ? (_X1) : (_X2))

#define PI 3.14159265358979f
#define RAD2DEG(u) ((u)*180.0f / PI)
#define DEG2RAD(u) ((u)*PI / 180.0f)

static inline uint16_t swap_u16(uint16_t num)
{
    return __builtin_bswap16(num);
}

static inline int16_t swap_i16(int16_t num)
{
    return __builtin_bswap16(num);
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

static inline int16_t cmp16(uint16_t a, uint16_t b) { return (int16_t)(a-b); }
static inline int32_t cmp32(uint32_t a, uint32_t b) { return (int32_t)(a-b); }

static inline uint32_t llog2(uint32_t n) { return 31 - __builtin_clz(n | 1); }

#endif //_SWAP_H
