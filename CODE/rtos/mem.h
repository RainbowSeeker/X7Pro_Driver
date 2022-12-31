// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#ifndef X7PRO_DRIVER_MEM_H
#define X7PRO_DRIVER_MEM_H
#include "os_common.h"

// DMA to/from any memory
#define DMA_DATA_ZERO_INIT          __attribute__ ((section(".dmaram_bss"), aligned(32)))
#define DMA_DATA                    __attribute__ ((section(".dmaram_data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

#define IS_DTCM(p)      (((uint32_t)p & 0xfffe0000) == 0x20000000)
#define IS_AXI_SRAM(p)  (((uint32_t)p & 0xfff80000) == 0x24000000)
#define IS_SRAM4(p)     (((uint32_t)p & 0xffff0000) == 0x38000000)


#define DMA_RAM __attribute__((section(".DMA_RAM"), aligned(32)))
#define DMA_RAM_D2 __attribute__((section(".DMA_RW_D2"), aligned(32)))
#define DMA_RW_AXI __attribute__((section(".DMA_RW_AXI"), aligned(32)))

extern uint8_t _dmaram_start__;
extern uint8_t _dmaram_end__;

extern uint8_t _dmaramd3_start__;
extern uint8_t _dmaramd3_end__;

#define DMA_DATA                    __attribute__ ((section(".dmaram_data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

#define BDMA_DATA                    __attribute__ ((section(".dmaramd3_data"), aligned(32)))
#define STATIC_BDMA_DATA_AUTO        static BDMA_DATA

#endif //X7PRO_DRIVER_MEM_H
