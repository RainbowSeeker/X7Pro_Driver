// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#ifndef _COMMON_H
#define _COMMON_H

#include "stm32h7xx_hal.h"

#ifdef STM32H7
#define USE_ITCM_RAM
#define USE_FAST_DATA
#define USE_DSHOT
#define USE_DSHOT_BITBANG
#define USE_DSHOT_TELEMETRY
#define USE_DSHOT_TELEMETRY_STATS
#define USE_RPM_FILTER
#define USE_DYN_IDLE
#define USE_DYN_NOTCH_FILTER
#define USE_ADC_INTERNAL
#define USE_USB_CDC_HID
#define USE_DMA_SPEC
#define USE_TIMER_MGMT
#define USE_PERSISTENT_OBJECTS
#define USE_DMA_RAM
#define USE_USB_MSC
#define USE_RTC_TIME
#define USE_PERSISTENT_MSC_RTC
#define USE_DSHOT_CACHE_MGMT
#define USE_LATE_TASK_STATISTICS
// Move ISRs to fast ram to avoid flash latency.
//#define FAST_IRQ_HANDLER
#define FAST_IRQ_HANDLER FAST_CODE

// DMA to/from any memory
#define DMA_DATA_ZERO_INIT          __attribute__ ((section(".dmaram_bss"), aligned(32)))
#define DMA_DATA                    __attribute__ ((section(".dmaram_data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

#define IS_DTCM(p) (((uint32_t)p & 0xfffe0000) == 0x20000000)
#endif

#ifdef USE_DMA_RAM
#define DMA_RAM __attribute__((section(".DMA_RAM"), aligned(32)))
#define DMA_RW_AXI __attribute__((section(".DMA_RW_AXI"), aligned(32)))

extern uint8_t _dmaram_start__;
extern uint8_t _dmaram_end__;

extern uint8_t _dmaramd3_start__;
extern uint8_t _dmaramd3_end__;
#endif


#define DMA_DATA_ZERO_INIT          __attribute__ ((section(".dmaram_bss"), aligned(32)))
#define DMA_DATA                    __attribute__ ((section(".dmaram_data"), aligned(32)))
#define STATIC_DMA_DATA_AUTO        static DMA_DATA

#define BDMA_DATA                    __attribute__ ((section(".dmaramd3_data"), aligned(32)))
#define STATIC_BDMA_DATA_AUTO        static BDMA_DATA

#define FAST_CODE                   __attribute__((section(".tcm_code")))
// Handle case where we'd prefer code to be in ITCM
#define FAST_CODE_PREF              __attribute__((section(".tcm_code")))
#define FAST_CODE_NOINLINE          NOINLINE


#ifdef USE_FAST_DATA
#define FAST_DATA_ZERO_INIT         __attribute__ ((section(".fastram_bss"), aligned(4)))
#define FAST_DATA                   __attribute__ ((section(".fastram_data"), aligned(4)))
#else
#define FAST_DATA_ZERO_INIT
#define FAST_DATA
#endif // USE_FAST_DATA


#define ATOMIC_BLOCK(prio) for ( uint8_t __basepri_save __attribute__ ((__cleanup__ (__basepriRestoreMem), __unused__)) = __get_BASEPRI(), \
                                     __ToDo = __basepriSetMemRetVal(prio); __ToDo ; __ToDo = 0 )

// set BASEPRI_MAX, with global memory barrier, returns true
static inline uint8_t __basepriSetMemRetVal(uint8_t prio)
{
    __set_BASEPRI_MAX(prio);
    return 1;
}


// restore BASEPRI (called as cleanup function), with global memory barrier
static inline void __basepriRestoreMem(uint8_t *val)
{
    __set_BASEPRI(*val);
}
#endif //_COMMON_H
