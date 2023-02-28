// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/6.
//

#ifndef X7PRO_DRIVER_DRV_DMA_H
#define X7PRO_DRIVER_DRV_DMA_H

#include "hal/dma/dma.h"
#include "stm32h7xx.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_bdma.h"

#define DMA_IT_TCIF         ((uint32_t)0x00000020)
#define DMA_IT_HTIF         ((uint32_t)0x00000010)
#define DMA_IT_TEIF         ((uint32_t)0x00000008)
#define DMA_IT_DMEIF        ((uint32_t)0x00000004)
#define DMA_IT_FEIF         ((uint32_t)0x00000001)

#define BDMA_IT_TCIF         ((uint32_t)0x00000002)
#define BDMA_IT_HTIF         ((uint32_t)0x00000004)
#define BDMA_IT_TEIF         ((uint32_t)0x00000008)


#define DMA_CLEAR_FLAG(d, flag)   if (d->flagsShift > 31) ((DMA_TypeDef *)d->dma)->HIFCR = (flag << (d->flagsShift - 32)); else ((DMA_TypeDef *)d->dma)->LIFCR = (flag << d->flagsShift)
#define BDMA_CLEAR_FLAG(d, flag)   (BDMA->IFCR = (flag << d->flagsShift))


err_t dma_get_request_by_instance(void *instance, uint32_t *request);
void dma_configure_irq(struct dma_device *dma, void (*cb)(uint32_t), uint32_t priority, uint32_t user_data);

uint32_t LL_EX_DMA_IsActiveFlag(struct dma_device *dma, uint32_t flag);
void LL_EX_DMA_ClearFlag(struct dma_device *dma, uint32_t flag);
struct dma_device * LL_DMA_DeviceGetByName(const char *name);
void LL_EX_DMA_ResetStream(struct dma_device *dma);



#endif //X7PRO_DRIVER_DRV_DMA_H
