// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/6.
//

#include "drv_dma.h"


static struct dma_device dma_device_table[] = {
        //DMA1 Stream[0:7]
        DEFINE_DMA_STREAM(1, 0, 0),
        DEFINE_DMA_STREAM(1, 1, 6),
        DEFINE_DMA_STREAM(1, 2, 16),
        DEFINE_DMA_STREAM(1, 3, 22),
        DEFINE_DMA_STREAM(1, 4, 32),
        DEFINE_DMA_STREAM(1, 5, 38),
        DEFINE_DMA_STREAM(1, 6, 48),
        DEFINE_DMA_STREAM(1, 7, 54),
        //DMA2 Stream[0:7]
        DEFINE_DMA_STREAM(2, 0, 0),
        DEFINE_DMA_STREAM(2, 1, 6),
        DEFINE_DMA_STREAM(2, 2, 16),
        DEFINE_DMA_STREAM(2, 3, 22),
        DEFINE_DMA_STREAM(2, 4, 32),
        DEFINE_DMA_STREAM(2, 5, 38),
        DEFINE_DMA_STREAM(2, 6, 48),
        DEFINE_DMA_STREAM(2, 7, 54),
        //BDMA1 Channel[0:7]
        DEFINE_BDMA_STREAM(0, 0),
        DEFINE_BDMA_STREAM(1, 4),
        DEFINE_BDMA_STREAM(2, 8),
        DEFINE_BDMA_STREAM(3, 12),
        DEFINE_BDMA_STREAM(4, 16),
        DEFINE_BDMA_STREAM(5, 20),
        DEFINE_BDMA_STREAM(6, 24),
        DEFINE_BDMA_STREAM(7, 28)
};

static uint32_t dma_irq_table[] = {
        DMA1_Stream0_IRQn,
        DMA1_Stream1_IRQn,
        DMA1_Stream2_IRQn,
        DMA1_Stream3_IRQn,
        DMA1_Stream4_IRQn,
        DMA1_Stream5_IRQn,
        DMA1_Stream6_IRQn,
        DMA1_Stream7_IRQn,

        DMA2_Stream0_IRQn,
        DMA2_Stream1_IRQn,
        DMA2_Stream2_IRQn,
        DMA2_Stream3_IRQn,
        DMA2_Stream4_IRQn,
        DMA2_Stream5_IRQn,
        DMA2_Stream6_IRQn,
        DMA2_Stream7_IRQn,

        BDMA_Channel0_IRQn,
        BDMA_Channel1_IRQn,
        BDMA_Channel2_IRQn,
        BDMA_Channel3_IRQn,
        BDMA_Channel4_IRQn,
        BDMA_Channel5_IRQn,
        BDMA_Channel6_IRQn,
        BDMA_Channel7_IRQn,
};


DEFINE_DMA_IRQ_HANDLER(1, 0, DMA1_STREAM0_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 1, DMA1_STREAM1_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 2, DMA1_STREAM2_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 3, DMA1_STREAM3_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 4, DMA1_STREAM4_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 5, DMA1_STREAM5_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 6, DMA1_STREAM6_HANDLER);
DEFINE_DMA_IRQ_HANDLER(1, 7, DMA1_STREAM7_HANDLER);

DEFINE_DMA_IRQ_HANDLER(2, 0, DMA1_STREAM0_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 1, DMA1_STREAM1_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 2, DMA1_STREAM2_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 3, DMA1_STREAM3_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 4, DMA1_STREAM4_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 5, DMA1_STREAM5_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 6, DMA1_STREAM6_HANDLER);
DEFINE_DMA_IRQ_HANDLER(2, 7, DMA1_STREAM7_HANDLER);

DEFINE_BDMA_IRQ_HANDLER(0, BDMA_CHANNEL0_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(1, BDMA_CHANNEL1_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(2, BDMA_CHANNEL2_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(3, BDMA_CHANNEL3_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(4, BDMA_CHANNEL4_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(5, BDMA_CHANNEL5_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(6, BDMA_CHANNEL6_HANDLER);
DEFINE_BDMA_IRQ_HANDLER(7, BDMA_CHANNEL7_HANDLER);


static uint8_t dma_get_descriptor_id(void *dma_stream)
{
    for (int i = 0; i < ARRAY_LEN(dma_device_table); ++i)
    {
        if (dma_stream == dma_device_table[i].stream)
        {
            return i;
        }
    }
    return 0;
}

void dma_configure_irq(void *dma_stream, void (*cb)(uint32_t), uint32_t priority, uint32_t user_data)
{
    uint8_t id = dma_get_descriptor_id(dma_stream);

    __HAL_RCC_BDMA_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    dma_device_table[id].cb = cb;
    dma_device_table[id].user_data = user_data;

    HAL_NVIC_SetPriority(dma_irq_table[id], priority, 0);
    HAL_NVIC_EnableIRQ(dma_irq_table[id]);

}

void dma_get_elm(void *dma_stream, struct dma_elm *elm)
{
    uint8_t id = dma_get_descriptor_id(dma_stream);
    if (id < 8)
    {
        elm->base = DMA1;
        elm->stream = id;
    }
    else if (id < 16)
    {
        elm->base = DMA2;
        elm->stream = id - 8;
    }
    else
    {
        elm->base = BDMA;
        elm->stream = id - 16;
    }
}

void LL_EX_DMA_ClearFlag(void *dma_stream, uint32_t flag)
{
    struct dma_elm elm;
    dma_get_elm(dma_stream, &elm);

    uint8_t flag_shift = dma_device_table[dma_get_descriptor_id(dma_stream)].flag_shift;

    if (elm.base == BDMA)
    {
        BDMA->IFCR = flag << flag_shift;
    }
    else
    {
        if (flag_shift > 31)
        {
            ((DMA_TypeDef *) elm.base)->HIFCR = (flag << (flag_shift - 32));
        }
        else
        {
            ((DMA_TypeDef *) elm.base)->LIFCR = (flag << flag_shift);
        }
    }
}


struct dma_device * LL_DMA_DeviceGetByName(const char *name)
{
    uint8_t idx;
    if (strncmp(name, "dma", 3) == 0 && strncmp(&name[4], "_stream", 6) == 0)
    {
        idx = (name[3] == '2' ? 8 : 0);
        idx += (name[11] >= '0' && name[11] <= '7') ? (name[11] - '0') : 0;
        return &dma_device_table[idx];
    }
    else if (strncmp(name, "bdma", 4) == 0 && strncmp(&name[4], "_channel", 8) == 0)
    {
        idx = 16 + ((name[12] >= '0' && name[12] <= '7') ? (name[12] - '0') : 0);
        return &dma_device_table[idx];
    }
    else
    {
        return NULL;
    }
}
