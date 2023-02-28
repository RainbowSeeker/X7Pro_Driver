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

struct dma_request {
    void *instance;
    uint32_t request;
};
static struct dma_request dma_request_table[] = {
        {SPI1, LL_DMAMUX1_REQ_SPI1_TX},
        {SPI2, LL_DMAMUX1_REQ_SPI2_TX},
        {SPI3, LL_DMAMUX1_REQ_SPI3_TX},
        {SPI4, LL_DMAMUX1_REQ_SPI4_TX},
        {SPI5, LL_DMAMUX1_REQ_SPI5_TX},
        {SPI6, LL_DMAMUX2_REQ_SPI6_TX},
        {USART1, LL_DMAMUX1_REQ_USART1_TX},
        {UART4, LL_DMAMUX1_REQ_UART4_TX},
        {UART7, LL_DMAMUX1_REQ_UART7_TX},
        {UART8, LL_DMAMUX1_REQ_UART8_TX},
};


DEFINE_DMA_IRQ_HANDLER(1, 0);
DEFINE_DMA_IRQ_HANDLER(1, 1);
DEFINE_DMA_IRQ_HANDLER(1, 2);
DEFINE_DMA_IRQ_HANDLER(1, 3);
DEFINE_DMA_IRQ_HANDLER(1, 4);
DEFINE_DMA_IRQ_HANDLER(1, 5);
DEFINE_DMA_IRQ_HANDLER(1, 6);
DEFINE_DMA_IRQ_HANDLER(1, 7);

DEFINE_DMA_IRQ_HANDLER(2, 0);
DEFINE_DMA_IRQ_HANDLER(2, 1);
DEFINE_DMA_IRQ_HANDLER(2, 2);
DEFINE_DMA_IRQ_HANDLER(2, 3);
DEFINE_DMA_IRQ_HANDLER(2, 4);
DEFINE_DMA_IRQ_HANDLER(2, 5);
DEFINE_DMA_IRQ_HANDLER(2, 6);
DEFINE_DMA_IRQ_HANDLER(2, 7);

DEFINE_BDMA_IRQ_HANDLER(0);
DEFINE_BDMA_IRQ_HANDLER(1);
DEFINE_BDMA_IRQ_HANDLER(2);
DEFINE_BDMA_IRQ_HANDLER(3);
DEFINE_BDMA_IRQ_HANDLER(4);
DEFINE_BDMA_IRQ_HANDLER(5);
DEFINE_BDMA_IRQ_HANDLER(6);
DEFINE_BDMA_IRQ_HANDLER(7);

err_t dma_get_request_by_instance(void *instance, uint32_t *request) {
    for (int i = 0; i < ARRAY_LEN(dma_request_table); ++i) {
        if (instance == dma_request_table[i].instance)
        {
            *request = dma_request_table[i].request;
            return E_OK;
        }
    }
    return E_INVAL;
}

void dma_configure_irq(struct dma_device *dma, void (*cb)(uint32_t), uint32_t priority, uint32_t user_data) {
    __HAL_RCC_BDMA_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    dma->cb = cb;
    dma->user_data = user_data;

    HAL_NVIC_SetPriority(dma->irqn, priority, 0);
    HAL_NVIC_EnableIRQ(dma->irqn);
}

uint32_t LL_EX_DMA_IsActiveFlag(struct dma_device *dma, uint32_t flag) {
    if (dma->instance == BDMA) {
        return READ_BIT(BDMA->ISR, (flag << dma->flag_shift)) ? 1UL : 0UL;
    } else {
        if (dma->flag_shift > 31) {
            return READ_BIT(((DMA_TypeDef *) dma->instance)->HISR, (flag << (dma->flag_shift - 32))) ? 1UL : 0UL;
        } else {
            return READ_BIT(((DMA_TypeDef *) dma->instance)->LISR, (flag << dma->flag_shift)) ? 1UL : 0UL;
        }
    }
}

void LL_EX_DMA_ClearFlag(struct dma_device *dma, uint32_t flag) {
    if (dma->instance == BDMA) {
        BDMA->IFCR = flag << dma->flag_shift;
    } else {
        if (dma->flag_shift > 31) {
            ((DMA_TypeDef *) dma->instance)->HIFCR = (flag << (dma->flag_shift - 32));
        } else {
            ((DMA_TypeDef *) dma->instance)->LIFCR = (flag << dma->flag_shift);
        }
    }
}


struct dma_device *LL_DMA_DeviceGetByName(const char *name) {
    for (int i = 0; i < ARRAY_LEN(dma_device_table); ++i)
    {
        if (MATCH(name, dma_device_table[i].parent.name))   return &dma_device_table[i];
    }
    return NULL;
}

void LL_EX_DMA_ResetStream(struct dma_device *dma)
{
    if (dma->instance == BDMA)
    {
        LL_BDMA_DisableChannel(dma->instance, dma->stream);
        while (LL_BDMA_IsEnabledChannel(dma->instance, dma->stream));
        LL_EX_DMA_ClearFlag(dma, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
    }
    else
    {
        // Disable the stream
        LL_DMA_DisableStream(dma->instance, dma->stream);
        while (LL_DMA_IsEnabledStream(dma->instance, dma->stream));
        LL_EX_DMA_ClearFlag(dma, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
    }

}
