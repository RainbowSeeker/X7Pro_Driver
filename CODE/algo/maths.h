// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef _SWAP_H
#define _SWAP_H

#include "stdio.h"
#include <stdarg.h>

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))


static inline uint16_t swap_u16(uint16_t num)
{
    return ((num & 0xff ) << 8) | ((num >> 8) & 0xff);
}

static inline int16_t swap_i16(int16_t num)
{
    return ((num & 0xff ) << 8) | ((num >> 8) & 0xff);
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

#endif //_SWAP_H
