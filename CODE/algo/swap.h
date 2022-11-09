// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef _SWAP_H
#define _SWAP_H

#include "stdio.h"


static inline uint16_t swap_u16(uint16_t num)
{
    return (num << 8) | (num >> 8);
}

static inline int16_t swap_i16(int16_t num)
{
    return (num << 8) | (num >> 8);
}


#endif //_SWAP_H
