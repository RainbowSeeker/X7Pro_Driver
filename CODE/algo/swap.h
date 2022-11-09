// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//

#ifndef _SWAP_H
#define _SWAP_H

#include "stdio.h"


static inline uint16_t swap_u16(uint16_t num)
{
    return ((num & 0xff ) << 8) | ((num >> 8) & 0xff);
}

static inline int16_t swap_i16(int16_t num)
{
    return ((num & 0xff ) << 8) | ((num >> 8) & 0xff);
}


#endif //_SWAP_H
