// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/6.
//

#ifndef X7PRO_DRIVER_DMA_H
#define X7PRO_DRIVER_DMA_H

#include "common.h"



#define DMA_THRESHOLD       8

enum dma_handler_e
{
    DMA1_STREAM0_HANDLER = 0,
    DMA1_STREAM1_HANDLER,
    DMA1_STREAM2_HANDLER,
    DMA1_STREAM3_HANDLER,
    DMA1_STREAM4_HANDLER,
    DMA1_STREAM5_HANDLER,
    DMA1_STREAM6_HANDLER,
    DMA1_STREAM7_HANDLER,
    DMA2_STREAM0_HANDLER,
    DMA2_STREAM1_HANDLER,
    DMA2_STREAM2_HANDLER,
    DMA2_STREAM3_HANDLER,
    DMA2_STREAM4_HANDLER,
    DMA2_STREAM5_HANDLER,
    DMA2_STREAM6_HANDLER,
    DMA2_STREAM7_HANDLER,
    BDMA_CHANNEL0_HANDLER,
    BDMA_CHANNEL1_HANDLER,
    BDMA_CHANNEL2_HANDLER,
    BDMA_CHANNEL3_HANDLER,
    BDMA_CHANNEL4_HANDLER,
    BDMA_CHANNEL5_HANDLER,
    BDMA_CHANNEL6_HANDLER,
    BDMA_CHANNEL7_HANDLER,
    DMA_HANDLER_COUNT,
};

#define DEFINE_DMA_STREAM(d, s, f) { \
    .instance = DMA ## d,            \
    .stream = LL_DMA_STREAM_ ## s,     \
    .ref = DMA ## d ## _Stream ## s, \
    .channel = 0,               \
    .cb = NULL, \
    .flag_shift = f,                 \
    .irqn = DMA ## d ## _Stream ## s ## _IRQn,                              \
    .user_data = 0 \
    }

#define DEFINE_BDMA_STREAM(ch, f) { \
    .instance = BDMA,               \
    .stream = LL_BDMA_CHANNEL_ ## ch,     \
    .ref = BDMA_Channel ## ch, \
    .channel = 0, \
    .cb = NULL, \
    .flag_shift = f,                \
    .irqn = BDMA_Channel ## ch ## _IRQn,               \
    .user_data = 0, \
    }


#define DEFINE_DMA_IRQ_HANDLER(d, s, i)  void DMA ## d ## _Stream ## s ## _IRQHandler(void) {\
                                                                if (dma_device_table[i].cb) \
                                                                    dma_device_table[i].cb(dma_device_table[i].user_data); \
                                                            }

#define DEFINE_BDMA_IRQ_HANDLER(ch, i)  void BDMA ## _Channel ## ch ## _IRQHandler(void) {\
                                                                if (dma_device_table[i].cb) \
                                                                    dma_device_table[i].cb(dma_device_table[i].user_data); \
                                                            }


struct dma_device
{
    struct device parent;
    void *const instance;
    const uint32_t stream;
    void *const ref;
    uint32_t channel;
    const uint8_t flag_shift;
    const IRQn_Type irqn;

    void (*cb)(uint32_t user_data);
    uint32_t user_data;
};


err_t hal_dma_register(struct dma_device * dma, const char *name, uint32_t flag);



#endif //X7PRO_DRIVER_DMA_H
