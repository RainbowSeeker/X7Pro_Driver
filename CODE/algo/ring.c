// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "ring.h"
#include "string.h"


void Ring_Init(ring_t *ring)
{
    ring->pHead = 0;
    ring->pTail = 0;
    memset(ring->element, 0, sizeof(ring->element));
}

uint16_t Ring_GetSize(ring_t *ring)
{
    return (ring->pTail - ring->pHead + RING_MAX_LEN) % RING_MAX_LEN;
}

uint16_t Ring_GetCapcity(ring_t *ring)
{
    return RING_MAX_LEN - Ring_GetSize(ring) - 1;
}

int Ring_PushBack(ring_t *ring, void *element)
{
    if (ring->pHead == (ring->pTail + 1 + RING_MAX_LEN) % RING_MAX_LEN)
    {
        return -1;  // ring buf is full
    }
    ring->element[ring->pTail] = element;
    ring->pTail = (ring->pTail + 1 + RING_MAX_LEN) % RING_MAX_LEN;
    return 0;
}

int Ring_PopBack(ring_t *ring, void **element)
{
    if (ring->pHead == ring->pTail)
    {
        return -1;      //no spare buf
    }
    ring->pTail = (ring->pTail - 1 + RING_MAX_LEN) % RING_MAX_LEN;
    *element = ring->element[ring->pTail];
    return 0;
}

int Ring_PushFront(ring_t *ring, void *element)
{
    if (ring->pTail == (ring->pHead - 1 + RING_MAX_LEN) % RING_MAX_LEN)
    {
        return -1;  // ring buf is full
    }
    ring->pHead = (ring->pHead - 1 + RING_MAX_LEN) % RING_MAX_LEN;
    ring->element[ring->pHead] = element;
    return 0;
}

int Ring_PopFront(ring_t *ring, void **element)
{
    if (ring->pHead == ring->pTail)
    {
        return -1;
    }
    *element = ring->element[ring->pHead];
    ring->pHead = (ring->pHead + 1 + RING_MAX_LEN) % RING_MAX_LEN;
    return 0;
}