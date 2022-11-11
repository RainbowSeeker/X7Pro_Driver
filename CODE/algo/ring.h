// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#ifndef _RING_H
#define _RING_H

#include <stdbool.h>
#include <stdio.h>
#include "stdint.h"

#define RING_MAX_LEN            64u


typedef struct
{
    void        *element[RING_MAX_LEN];
    uint16_t    pHead;
    uint16_t    pTail;
}ring_t;


void Ring_Init(ring_t *ring);
uint16_t Ring_GetSize(ring_t *ring);
uint16_t Ring_GetCapcity(ring_t *ring);
int Ring_PushBack(ring_t *ring, void *segment);
int Ring_PopBack(ring_t *ring, void **segment);
int Ring_PushFront(ring_t *ring, void *segment);
int Ring_PopFront(ring_t *ring, void **segment);
#endif //_RING_H
