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


extern uint8_t _dmaram_start__;
extern uint8_t _dmaram_end__;

extern uint8_t _dmaramd3_start__;
extern uint8_t _dmaramd3_end__;

#define DMA_DATA                    __attribute__ ((section(".data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

#define DMA_INIT_DATA                    __attribute__ ((section(".bss"), aligned(32)))
#define STATIC_DMA_INIT_DATA_AUTO        static DMA_INIT_DATA

#define BDMA_DATA                    __attribute__ ((section(".d3_data"), aligned(32)))
#define STATIC_BDMA_DATA_AUTO        static BDMA_DATA

#endif //X7PRO_DRIVER_MEM_H
