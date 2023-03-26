// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#ifndef X7PRO_DRIVER_CACHE_H
#define X7PRO_DRIVER_CACHE_H
#include <stddef.h>
#include "stm32h743xx.h"

#define CACHE_LINE_SIZE 32
#define CACHE_LINE_MASK (CACHE_LINE_SIZE - 1)

// Invalidate the D cache covering the area into which data has been read
static_inline void scb_invalidate_dcache(void *addr, size_t dsize)
{
#ifdef __DCACHE_PRESENT
    SCB_InvalidateDCache_by_Addr(
            (uint32_t *) ((uint32_t) addr & ~CACHE_LINE_MASK),
            (((uint32_t) addr & CACHE_LINE_MASK) + dsize - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
#endif
}

// Flush the D cache to ensure the data to be written is in main memory
static_inline void scb_flush_dcache(void *addr, size_t dsize)
{
#ifdef __DCACHE_PRESENT
    SCB_CleanDCache_by_Addr(
            (uint32_t *) ((uint32_t) addr & ~CACHE_LINE_MASK),
            (((uint32_t) addr & CACHE_LINE_MASK) + dsize - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
#endif
}

static_inline void scb_flush_invalidate_dcache(void *addr, size_t dsize)
{
#ifdef __DCACHE_PRESENT
    SCB_CleanInvalidateDCache_by_Addr(
            (uint32_t *) ((uint32_t) addr & ~CACHE_LINE_MASK),
            (((uint32_t) addr & CACHE_LINE_MASK) + dsize - 1 + CACHE_LINE_SIZE) & ~CACHE_LINE_MASK);
#endif
}

#endif //X7PRO_DRIVER_CACHE_H
