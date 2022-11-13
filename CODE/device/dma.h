// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#ifndef X7PRO_DRIVER_DMA_H
#define X7PRO_DRIVER_DMA_H
#include "stm32h7xx.h"
#include "common.h"

#define DMA_IDENTIFIER_TO_INDEX(x) ((x) - 1)


typedef enum {
    DMA_NONE = 0,
    DMA1_ST0_HANDLER = 1,
    DMA1_ST1_HANDLER,
    DMA1_ST2_HANDLER,
    DMA1_ST3_HANDLER,
    DMA1_ST4_HANDLER,
    DMA1_ST5_HANDLER,
    DMA1_ST6_HANDLER,
    DMA1_ST7_HANDLER,
    DMA2_ST0_HANDLER,
    DMA2_ST1_HANDLER,
    DMA2_ST2_HANDLER,
    DMA2_ST3_HANDLER,
    DMA2_ST4_HANDLER,
    DMA2_ST5_HANDLER,
    DMA2_ST6_HANDLER,
    DMA2_ST7_HANDLER,
    DMA_LAST_HANDLER = DMA2_ST7_HANDLER
} dma_stream_e;

#define DMA_DEVICE_NO(x)    ((((x)-1) / 8) + 1)
#define DMA_DEVICE_INDEX(x) ((((x)-1) % 8))
#define DMA_OUTPUT_INDEX    0
#define DMA_OUTPUT_STRING   "DMA%d Stream %d:"
#define DMA_INPUT_STRING    "DMA%d_ST%d"

#define DEFINE_DMA_CHANNEL(d, s, f) { \
    .dma = d, \
    .ref = d ## _Stream ## s, \
    .stream = s, \
    .irqHandlerCallback = NULL, \
    .flagsShift = f, \
    .irqN = d ## _Stream ## s ## _IRQn, \
    .userParam = 0, \
    }

#define DEFINE_DMA_IRQ_HANDLER(d, s, i)  void DMA ## d ## _Stream ## s ## _IRQHandler(void) {\
                                                                const uint8_t index = DMA_IDENTIFIER_TO_INDEX(i); \
                                                                dma_callback_func_ptr handler = dmaDescriptors[index].irqHandlerCallback; \
                                                                if (handler) \
                                                                    handler(&dmaDescriptors[index]); \
                                                            }

#define DMA_CLEAR_FLAG(d, flag) if (d->flagsShift > 31) d->dma->HIFCR = (flag << (d->flagsShift - 32)); else d->dma->LIFCR = (flag << d->flagsShift)
#define DMA_GET_FLAG_STATUS(d, flag) (d->flagsShift > 31 ? d->dma->HISR & (flag << (d->flagsShift - 32)): d->dma->LISR & (flag << d->flagsShift))

#define DMA_IT_TCIF         ((uint32_t)0x00000020)
#define DMA_IT_HTIF         ((uint32_t)0x00000010)
#define DMA_IT_TEIF         ((uint32_t)0x00000008)
#define DMA_IT_DMEIF        ((uint32_t)0x00000004)
#define DMA_IT_FEIF         ((uint32_t)0x00000001)

#define MAX_PERIPHERAL_DMA_OPTIONS      16
#define MAX_TIMER_DMA_OPTIONS           16

struct dma_s;
typedef void (*dma_callback_func_ptr)(struct dma_s *channelDescriptor);

typedef struct dma_s
{
    DMA_TypeDef                 *dma;
    uint8_t                     stream;
    DMA_Stream_TypeDef          *ref;
    uint32_t                    channel;
    dma_callback_func_ptr       irqHandlerCallback;
    uint8_t                     flagsShift;
    IRQn_Type                   irqN;
    uint32_t                    userParam;
}dma_t;

__STATIC_INLINE void LL_EX_DMA_EnableIT_TC(DMA_Stream_TypeDef *DMAx_Streamy)
{
    SET_BIT(DMAx_Streamy->CR, DMA_SxCR_TCIE);
}


typedef struct
{
    uint16_t              code;
    DMA_Stream_TypeDef    *ref;
    uint32_t              channel;
} dma_channel_t;

#define DMA_CODE(dma, stream, chanreq) ((dma << 12)|(stream << 8)|(chanreq << 0))
#define DMA_CODE_CONTROLLER(code) ((code >> 12) & 0xf)
#define DMA_CODE_STREAM(code) ((code >> 8) & 0xf)
#define DMA_CODE_CHANNEL(code) ((code >> 0) & 0xff)
#define DMA_CODE_REQUEST(code) DMA_CODE_CHANNEL(code)

typedef enum
{
    DMA_PERIPH_SPI_MOSI,
    DMA_PERIPH_SPI_MISO,
    DMA_PERIPH_ADC,
    DMA_PERIPH_SDIO,
    DMA_PERIPH_UART_TX,
    DMA_PERIPH_UART_RX,
    DMA_PERIPH_TIMUP,
} dma_peripheral_e;

typedef struct
{
    dma_peripheral_e dmaPeripheral;
    uint8_t index;
    uint8_t dmaRequest;
} dma_peripheral_mapping_t;

const dma_channel_t *DMA_GetChannelSpecByPeripheral(dma_peripheral_e device, uint8_t index, int8_t opt);
dma_stream_e DMA_GetIdentifier(const DMA_Stream_TypeDef *channel);
dma_t * DMA_GetDescriptorByIdentifier(const dma_stream_e identifier);
void DMA_Enable(dma_stream_e identifier);
void DMA_SetHandler(dma_stream_e identifier, dma_callback_func_ptr callback, uint32_t priority, uint32_t userParam);
#endif //X7PRO_DRIVER_DMA_H
