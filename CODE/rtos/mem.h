// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MEM_H
#define X7PRO_DRIVER_MEM_H
#include "os_common.h"

#define IS_DTCM(p)      (((uint32_t)p & 0xfffe0000) == 0x20000000)
#define IS_AXI_SRAM(p)  (((uint32_t)p & 0xfff80000) == 0x24000000)
#define IS_SRAM4(p)     (((uint32_t)p & 0xffff0000) == 0x38000000)


#define DMA_DATA                    __attribute__ ((section(".data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

#define HEAP_DATA                    __attribute__ ((section("._user_heap_stack"), aligned(32)))
#define STATIC_HEAP_DATA_AUTO        static HEAP_DATA

#define BDMA_DATA                    __attribute__ ((section(".d3_data"), aligned(32)))
#define STATIC_BDMA_DATA_AUTO        static BDMA_DATA

void system_heap_init(void *begin_addr, void *end_addr);
void *_malloc(size_t size);
void *_realloc(void *rmem, size_t newsize);
void *_calloc(size_t count, size_t size);
void _free(void *rmem);

#endif //X7PRO_DRIVER_MEM_H
