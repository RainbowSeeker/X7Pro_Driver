// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#include "dma.h"
#include "maths.h"
#include "board_config.h"
#include "bus.h"

/*
 * DMA descriptors.
 */
dma_t dmaDescriptors[DMA_LAST_HANDLER] = {
        DEFINE_DMA_CHANNEL(DMA1, 0, 0),
        DEFINE_DMA_CHANNEL(DMA1, 1, 6),
        DEFINE_DMA_CHANNEL(DMA1, 2, 16),
        DEFINE_DMA_CHANNEL(DMA1, 3, 22),
        DEFINE_DMA_CHANNEL(DMA1, 4, 32),
        DEFINE_DMA_CHANNEL(DMA1, 5, 38),
        DEFINE_DMA_CHANNEL(DMA1, 6, 48),
        DEFINE_DMA_CHANNEL(DMA1, 7, 54),

        DEFINE_DMA_CHANNEL(DMA2, 0, 0),
        DEFINE_DMA_CHANNEL(DMA2, 1, 6),
        DEFINE_DMA_CHANNEL(DMA2, 2, 16),
        DEFINE_DMA_CHANNEL(DMA2, 3, 22),
        DEFINE_DMA_CHANNEL(DMA2, 4, 32),
        DEFINE_DMA_CHANNEL(DMA2, 5, 38),
        DEFINE_DMA_CHANNEL(DMA2, 6, 48),
        DEFINE_DMA_CHANNEL(DMA2, 7, 54),
};

/*
 * DMA IRQ Handlers
 */
DEFINE_DMA_IRQ_HANDLER(1, 0, DMA1_ST0_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 1, DMA1_ST1_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 2, DMA1_ST2_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 3, DMA1_ST3_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 4, DMA1_ST4_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 5, DMA1_ST5_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 6, DMA1_ST6_HANDLER)

DEFINE_DMA_IRQ_HANDLER(1, 7, DMA1_ST7_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 0, DMA2_ST0_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 1, DMA2_ST1_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 2, DMA2_ST2_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 3, DMA2_ST3_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 4, DMA2_ST4_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 5, DMA2_ST5_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 6, DMA2_ST6_HANDLER)

DEFINE_DMA_IRQ_HANDLER(2, 7, DMA2_ST7_HANDLER)

/**
 * remap
 */
#define REQMAP_SGL(periph) { DMA_PERIPH_ ## periph, 0, DMA_REQUEST_ ## periph }
#define REQMAP(periph, device) { DMA_PERIPH_ ## periph, periph ## DEV_ ## device, DMA_REQUEST_ ## periph ## device }
#define REQMAP_DIR(periph, device, dir) { DMA_PERIPH_ ## periph ## _ ## dir, DEV_ ## periph ## device  , DMA_REQUEST_ ## periph ## device ## _ ## dir }
#define REQMAP_TIMUP(periph, timno) { DMA_PERIPH_TIMUP, timno - 1, DMA_REQUEST_ ## TIM ## timno ## _UP }

// Resolve UART/USART mess
#define DMA_REQUEST_UART1_RX DMA_REQUEST_USART1_RX
#define DMA_REQUEST_UART1_TX DMA_REQUEST_USART1_TX
#define DMA_REQUEST_UART2_RX DMA_REQUEST_USART2_RX
#define DMA_REQUEST_UART2_TX DMA_REQUEST_USART2_TX
#define DMA_REQUEST_UART3_RX DMA_REQUEST_USART3_RX
#define DMA_REQUEST_UART3_TX DMA_REQUEST_USART3_TX
#define DMA_REQUEST_UART6_RX DMA_REQUEST_USART6_RX
#define DMA_REQUEST_UART6_TX DMA_REQUEST_USART6_TX
#define DMA_REQUEST_UART10_RX DMA_REQUEST_USART10_RX
#define DMA_REQUEST_UART10_TX DMA_REQUEST_USART10_TX

// Resolve our preference for MOSI/MISO rather than TX/RX
#define DMA_REQUEST_SPI1_MOSI DMA_REQUEST_SPI1_TX
#define DMA_REQUEST_SPI1_MISO DMA_REQUEST_SPI1_RX
#define DMA_REQUEST_SPI2_MOSI DMA_REQUEST_SPI2_TX
#define DMA_REQUEST_SPI2_MISO DMA_REQUEST_SPI2_RX
#define DMA_REQUEST_SPI3_MOSI DMA_REQUEST_SPI3_TX
#define DMA_REQUEST_SPI3_MISO DMA_REQUEST_SPI3_RX
#define DMA_REQUEST_SPI4_MOSI DMA_REQUEST_SPI4_TX
#define DMA_REQUEST_SPI4_MISO DMA_REQUEST_SPI4_RX
#define DMA_REQUEST_SPI5_MOSI DMA_REQUEST_SPI5_TX
#define DMA_REQUEST_SPI5_MISO DMA_REQUEST_SPI5_RX
static const dma_peripheral_mapping_t dmaPeripheralMapping[] = {
#ifdef USE_SPI1
        REQMAP_DIR(SPI, 1, MOSI),
        REQMAP_DIR(SPI, 1, MISO),
#endif
#ifdef USE_SPI2
        REQMAP_DIR(SPI, 2, MOSI),
        REQMAP_DIR(SPI, 2, MISO),
#endif
#ifdef USE_SPI3
        REQMAP_DIR(SPI, 3, MOSI),
        REQMAP_DIR(SPI, 3, MISO),
#endif
#ifdef USE_SPI4
        REQMAP_DIR(SPI, 4, MOSI),
        REQMAP_DIR(SPI, 4, MISO),
#endif
#ifdef USE_SPI5
        REQMAP_DIR(SPI, 5, MOSI), // Not available in smaller packages
        REQMAP_DIR(SPI, 5, MISO), // ditto
#endif
#ifdef USE_SPI6
         REQMAP_DIR(SPI, 6, MOSI), // SPI6 is on BDMA
         REQMAP_DIR(SPI, 6, MOSI), // ditto
#endif // USE_SPI

#ifdef USE_ADC
        REQMAP(ADC, 1),
        REQMAP(ADC, 2),
        REQMAP(ADC, 3),
#endif

#ifdef USE_UART
        REQMAP_DIR(UART, 1, TX),
        REQMAP_DIR(UART, 1, RX),
        REQMAP_DIR(UART, 2, TX),
        REQMAP_DIR(UART, 2, RX),
        REQMAP_DIR(UART, 3, TX),
        REQMAP_DIR(UART, 3, RX),
        REQMAP_DIR(UART, 4, TX),
        REQMAP_DIR(UART, 4, RX),
        REQMAP_DIR(UART, 5, TX),
        REQMAP_DIR(UART, 5, RX),
        REQMAP_DIR(UART, 6, TX),
        REQMAP_DIR(UART, 6, RX),
        REQMAP_DIR(UART, 7, TX),
        REQMAP_DIR(UART, 7, RX),
        REQMAP_DIR(UART, 8, TX),
        REQMAP_DIR(UART, 8, RX),
#ifdef USE_LPUART1
        { DMA_PERIPH_UART_TX, LPUARTDEV_1, BDMA_REQUEST_LPUART1_TX },
        { DMA_PERIPH_UART_RX, LPUARTDEV_1, BDMA_REQUEST_LPUART1_RX },
#endif
#endif

#ifdef USE_TIMER
        // Pseudo peripheral for TIMx_UP channel
    REQMAP_TIMUP(TIMUP, 1),
    REQMAP_TIMUP(TIMUP, 2),
    REQMAP_TIMUP(TIMUP, 3),
    REQMAP_TIMUP(TIMUP, 4),
    REQMAP_TIMUP(TIMUP, 5),
    REQMAP_TIMUP(TIMUP, 6),
    REQMAP_TIMUP(TIMUP, 7),
    REQMAP_TIMUP(TIMUP, 8),
    REQMAP_TIMUP(TIMUP, 15),
    REQMAP_TIMUP(TIMUP, 16),
    REQMAP_TIMUP(TIMUP, 17),
#endif
};

#define DMA(d, s) { DMA_CODE(d, s, 0), (DMA_Stream_TypeDef *)DMA ## d ## _Stream ## s, 0 }

static dma_channel_t dmaChannelSpec[MAX_PERIPHERAL_DMA_OPTIONS] = {
        DMA(1, 0),
        DMA(1, 1),
        DMA(1, 2),
        DMA(1, 3),
        DMA(1, 4),
        DMA(1, 5),
        DMA(1, 6),
        DMA(1, 7),
        DMA(2, 0),
        DMA(2, 1),
        DMA(2, 2),
        DMA(2, 3),
        DMA(2, 4),
        DMA(2, 5),
        DMA(2, 6),
        DMA(2, 7),
};

static void DMA_SetupRequest(dma_channel_t *dmaSpec, uint8_t request)
{
    // Setup request as channel
    dmaSpec->channel = request;

    // Insert DMA request into code
    uint16_t code = dmaSpec->code;
    dmaSpec->code = DMA_CODE(DMA_CODE_CONTROLLER(code), DMA_CODE_STREAM(code), dmaSpec->channel);
}

const dma_channel_t *DMA_GetChannelSpecByPeripheral(dma_peripheral_e dmaPeripheral, uint8_t index, int8_t opt)
{
    static uint32_t isSave = 0;
    if (opt < 0 || opt >= MAX_PERIPHERAL_DMA_OPTIONS)
    {
        return NULL;
    }

    for (unsigned i = 0; i < ARRAYLEN(dmaPeripheralMapping); i++)
    {
        const dma_peripheral_mapping_t *periph = &dmaPeripheralMapping[i];
        if (periph->dmaPeripheral == dmaPeripheral && periph->index == index)
        {
            if (isSave & (1 << opt))
            {
                return NULL;
            }
            else
            {
                isSave = isSave | (1 << opt);
                dma_channel_t *dmaSpec = &dmaChannelSpec[opt];
                DMA_SetupRequest(dmaSpec, periph->dmaRequest);
                return dmaSpec;
            }
        }
    }

    return NULL;
}


dma_stream_e DMA_GetIdentifier(const DMA_Stream_TypeDef *channel)
{
    for (int i = 0; i < DMA_LAST_HANDLER; i++)
    {
        if (dmaDescriptors[i].ref == channel)
        {
            return i + 1;
        }
    }

    return 0;
}

dma_t *DMA_GetDescriptorByIdentifier(const dma_stream_e identifier)
{
    return &dmaDescriptors[DMA_IDENTIFIER_TO_INDEX(identifier)];
}

static void EnableDmaClock(int index)
{
    if (dmaDescriptors[index].dma == DMA1)
    {
        __HAL_RCC_DMA1_CLK_ENABLE();
    }
    else
    {
        __HAL_RCC_DMA2_CLK_ENABLE();
    }
}

void DMA_Enable(dma_stream_e identifier)
{
    const int index = DMA_IDENTIFIER_TO_INDEX(identifier);

    EnableDmaClock(index);
}

void DMA_SetHandler(dma_stream_e identifier, dma_callback_func_ptr callback, uint32_t priority, uint32_t userParam)
{
    const int index = DMA_IDENTIFIER_TO_INDEX(identifier);

    EnableDmaClock(index);
    dmaDescriptors[index].irqHandlerCallback = callback;
    dmaDescriptors[index].userParam = userParam;

    HAL_NVIC_SetPriority(dmaDescriptors[index].irqN, priority, 0);
    HAL_NVIC_EnableIRQ(dmaDescriptors[index].irqN);
}