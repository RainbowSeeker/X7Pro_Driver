// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#ifndef _RING_H
#define _RING_H

#include <stdbool.h>
#include <stdio.h>
#include "stdint.h"



typedef struct
{
    uint8_t     *element;
    uint16_t    pHead;
    uint16_t    pTail;
    uint16_t    size ;
}ring_t;


void Ring_Init(ring_t *ring, uint8_t *pData, uint32_t size);
uint16_t Ring_GetSize(ring_t *ring);
uint16_t Ring_GetCapcity(ring_t *ring);
int Ring_PushBack(ring_t *ring, uint8_t element);
int Ring_PopBack(ring_t *ring, uint8_t *element);
int Ring_PushFront(ring_t *ring, uint8_t element);
int Ring_PopFront(ring_t *ring, uint8_t *element);
#endif //_RING_H
