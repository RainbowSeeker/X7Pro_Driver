// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/20.
//

#include "drv_uart.h"
#include "driver/dma.h"
#include "nvic.h"
#include "atomic.h"
#include "algo/math/maths.h"
#include "hal/serial/serial.h"
#include "stm32h7xx_ll_usart.h"

static void uart_enable_clock(USART_TypeDef *instance)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (instance == USART1 || instance == USART6)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART16;
        PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
    }
    else if (instance == LPUART1)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
        PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_D3PCLK1;
    }
    else
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART234578;
        PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    }
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    if (instance == UART7) __HAL_RCC_UART7_CLK_ENABLE();
    else if(instance == USART1) __HAL_RCC_USART1_CLK_ENABLE();
    else ASSERT(0); // not support yet.
}

static void uart_gpio_init(USART_TypeDef *instance)
{
    if (instance == UART7)
    {
        io_t tx = {GPIOE, GPIO_PIN_8};
        io_t rx = {GPIOF, GPIO_PIN_6};
        io_init(rx, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF7_UART7);
        io_init(tx, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF7_UART7);
    }
    else if (instance == USART1)
    {
        io_t tx = {GPIOB, GPIO_PIN_6};
        io_t rx = {GPIOB, GPIO_PIN_7};
        io_init(rx, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF4_USART1);
        io_init(tx, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF4_USART1);
    }
    else ASSERT(0); // not support yet.
}


static void uart_disable_irq(USART_TypeDef *instance)
{
    if (instance == UART7)
    {
        HAL_NVIC_DisableIRQ(UART7_IRQn);
    }
    else ASSERT(0); // not support yet.
}

static void uart_enable_irq(USART_TypeDef *instance)
{
    if (instance == UART7)
    {
        HAL_NVIC_EnableIRQ(UART7_IRQn);
    }
    else if (instance == USART1)
    {
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else ASSERT(0); // not support yet.
}

static void uart_dma_clear_flags(DMA_TypeDef *dma, uint32_t stream)
{
    static const uint8_t flagBitshiftOffset[8] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};

    uint8_t stream_index = flagBitshiftOffset[stream];
    if (stream < LL_DMA_STREAM_4)
    {
        dma->LIFCR = 0x3DU << stream_index;
    }
    else
    {
        dma->HIFCR = 0x3DU << stream_index;
    }

}

static size_t uart_dma_transmit(struct serial_device *serial, uint8_t *buf, size_t size)
{
    if (LL_DMA_IsEnabledStream(serial->config.dma.instance, serial->config.dma.tx_stream))
    {
        /* if the dma stream is enabled, disable it */
        LL_DMA_DisableStream(serial->config.dma.instance, serial->config.dma.tx_stream);
        /* wait all current transfers are finished */
        while (LL_DMA_IsEnabledStream(serial->config.dma.instance, serial->config.dma.tx_stream));
    }

    /* all interrupt flags much be cleared before the stream can be re-enabled */
    uart_dma_clear_flags(serial->config.dma.instance, serial->config.dma.tx_stream);
    /* set data length */
    LL_DMA_SetDataLength(serial->config.dma.instance, serial->config.dma.tx_stream, size);
    /* configure dma address */
    LL_DMA_SetMemoryAddress(serial->config.dma.instance, serial->config.dma.tx_stream, (uint32_t) buf);
    /* enable common interrupts */
    LL_DMA_EnableIT_TC(serial->config.dma.instance, serial->config.dma.tx_stream);
    /* enable the specified dma stream */
    LL_DMA_EnableStream(serial->config.dma.instance, serial->config.dma.tx_stream);

    /* clear uart transmission complete flag */
    LL_USART_ClearFlag_TC(serial->config.instance);
    /* enable the uart dma transmit */
    LL_USART_EnableDMAReq_TX(serial->config.instance);
    return size;
}

static void uart_dma_receive(struct serial_device *serial)
{
    /* all interrupt flags much be cleared before the stream can be re-enabled */
    uart_dma_clear_flags(serial->config.dma.instance, serial->config.dma.rx_stream);
    /* enable common interrupts */
    LL_DMA_EnableIT_TC(serial->config.dma.instance, serial->config.dma.tx_stream);
    LL_USART_EnableIT_IDLE(serial->config.instance);
    /* enable the specified dma stream */
    LL_DMA_EnableStream(serial->config.dma.instance, serial->config.dma.rx_stream);

    /* clear uart transmission complete flag */
    LL_USART_ClearFlag_TC(serial->config.instance);
    /* enable the uart dma receive */
    LL_USART_EnableDMAReq_RX(serial->config.instance);
}


static void uart_dma_tx_config(struct serial_device *serial)
{
    LL_DMA_InitTypeDef DMA_InitStruct;

    DMA_InitStruct.PeriphOrM2MSrcAddress = (uint32_t) &serial->config.instance->TDR;
    DMA_InitStruct.MemoryOrM2MDstAddress = 0x00000000U; /* will be configured later */
    DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
    DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
    DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
    DMA_InitStruct.NbData = 0x00000000U; /* will be configured later */
    DMA_InitStruct.PeriphRequest = serial->config.dma.tx_channel;
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
    DMA_InitStruct.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_4;
    DMA_InitStruct.MemBurst = LL_DMA_MBURST_SINGLE;
    DMA_InitStruct.PeriphBurst = LL_DMA_PBURST_SINGLE;
    /* init tx dma */
    LL_DMA_Init(serial->config.dma.instance, serial->config.dma.tx_stream, &DMA_InitStruct);

    /* disable double buffer mode */
    LL_DMA_DisableDoubleBufferMode(serial->config.dma.instance, serial->config.dma.tx_stream);
    LL_DMA_DisableFifoMode(serial->config.dma.instance, serial->config.dma.tx_stream);
}

static void uart_dma_rx_config(struct serial_device *serial, uint8_t *buf, size_t size)
{
    LL_DMA_InitTypeDef DMA_InitStruct;

    /* set expected receive length */
    serial->setting_recv_len = size;

    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    DMA_InitStruct.PeriphOrM2MSrcAddress = (uint32_t) &serial->config.instance->RDR;
    DMA_InitStruct.MemoryOrM2MDstAddress = (uint32_t) buf;
    DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    DMA_InitStruct.Mode = LL_DMA_MODE_CIRCULAR;
    DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
    DMA_InitStruct.NbData = size;
    DMA_InitStruct.PeriphRequest = serial->config.dma.rx_channel;
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
    DMA_InitStruct.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_4;
    DMA_InitStruct.MemBurst = LL_DMA_MBURST_SINGLE;
    DMA_InitStruct.PeriphBurst = LL_DMA_PBURST_SINGLE;
    /* init rx dma */
    LL_DMA_Init(serial->config.dma.instance, serial->config.dma.rx_stream, &DMA_InitStruct);

    /* disable double buffer mode */
    LL_DMA_DisableDoubleBufferMode(serial->config.dma.instance, serial->config.dma.rx_stream);
    LL_DMA_DisableFifoMode(serial->config.dma.instance, serial->config.dma.rx_stream);

    /* start to receive data */
    uart_dma_receive(serial);
}

/**
 * Calculate DMA received data length.
 *
 * @param serial serial device
 *
 * @return length
 */
static size_t uart_dma_calc_recved_len(struct serial_device *serial)
{
    struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;

    ASSERT(rx_fifo != NULL);

    if (rx_fifo->put_index == rx_fifo->get_index)
    {
        return (rx_fifo->is_full == FALSE ? 0 : serial->config.bufsz);
    }
    else
    {
        if (rx_fifo->put_index > rx_fifo->get_index)
        {
            return rx_fifo->put_index - rx_fifo->get_index;
        }
        else
        {
            return serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index);
        }
    }
}


static err_t uart_configure(struct serial_device *serial, struct serial_configure *config)
{
    ASSERT(serial != NULL);
    ASSERT(config != NULL && config->instance);

    LL_USART_InitTypeDef USART_InitStructure = {0};

    uart_enable_clock(config->instance);
    uart_gpio_init(config->instance);

    if (config->instance == LPUART1)
    {
        USART_InitStructure.PrescalerValue = LL_USART_PRESCALER_DIV8;
    }
    USART_InitStructure.BaudRate = config->baud_rate;

    if (config->data_bits == DATA_BITS_8)
    {
        USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;
    }
    else if (config->data_bits == DATA_BITS_9)
    {
        USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_9B;
    }

    if (config->stop_bits == STOP_BITS_1)
    {
        USART_InitStructure.StopBits = LL_USART_STOPBITS_1;
    }
    else if (config->stop_bits == STOP_BITS_2)
    {
        USART_InitStructure.StopBits = LL_USART_STOPBITS_2;
    }

    if (config->parity == PARITY_NONE)
    {
        USART_InitStructure.Parity = LL_USART_PARITY_NONE;
    }
    else if (config->parity == PARITY_ODD)
    {
        USART_InitStructure.Parity = LL_USART_PARITY_ODD;
    }
    else if (config->parity == PARITY_EVEN)
    {
        USART_InitStructure.Parity = LL_USART_PARITY_EVEN;
    }
    // TODO: Add hw flow control
    USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStructure.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;

    /* USART need be disabled first in order to configure it */
    LL_USART_Disable(config->instance);
    LL_USART_Init(config->instance, &USART_InitStructure);
    LL_USART_ConfigAsyncMode(config->instance);
    LL_USART_Enable(config->instance);
    return 0;
}

static void uart_close(struct serial_device *serial)
{
    if (serial->parent.open_flag & DEVICE_FLAG_INT_RX)
    {
        /* disable int rx irq */
        LL_USART_DisableIT_RXNE(serial->config.instance);
    }

    if (serial->parent.open_flag & DEVICE_FLAG_DMA_RX)
    {
        /* disable dma rx irq and disable rx dma */
        LL_DMA_DisableIT_TC(serial->config.dma.instance, serial->config.dma.rx_stream);
        LL_USART_DisableIT_IDLE(serial->config.instance);
        LL_DMA_DisableStream(serial->config.dma.instance, serial->config.dma.rx_stream);
        LL_USART_DisableDMAReq_RX(serial->config.instance);
    }

    if (serial->parent.open_flag & DEVICE_FLAG_DMA_TX)
    {
        /* disable dma tx irq and disable tx dma */
        LL_DMA_DisableIT_TC(serial->config.dma.instance, serial->config.dma.tx_stream);
        LL_DMA_DisableStream(serial->config.dma.instance, serial->config.dma.tx_stream);
        LL_USART_DisableDMAReq_TX(serial->config.instance);
    }
}

static err_t uart_control(struct serial_device *serial, int cmd, void *arg)
{
    uint32_t ctrl_arg = (uint32_t) (arg);

    ASSERT(serial != NULL);

    switch (cmd)
    {
        case DEVICE_CTRL_CLR_INT:
            if (ctrl_arg == DEVICE_FLAG_INT_RX)
            {
                /* disable rx irq */
                uart_disable_irq(serial->config.instance);
                /* disable interrupt */
                LL_USART_DisableIT_RXNE(serial->config.instance);
            }
            break;

        case DEVICE_CTRL_SET_INT:
            if (ctrl_arg == DEVICE_FLAG_INT_RX)
            {
                /* disable rx irq */
                uart_enable_irq(serial->config.instance);
                /* disable interrupt */
                LL_USART_EnableIT_RXNE(serial->config.instance);
            }
            break;

            /* USART DMA config */
        case DEVICE_CTRL_CONFIG:
            if (ctrl_arg == DEVICE_FLAG_DMA_RX)
            {
                struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;
                if (LL_DMA_IsEnabledStream(serial->config.dma.instance, serial->config.dma.rx_stream))
                {
                    /* dma is busy */
                    return E_BUSY;
                }
                uart_dma_rx_config(serial, rx_fifo->buffer, serial->config.bufsz);
            }

            if (ctrl_arg == DEVICE_FLAG_DMA_TX)
            {
                if (LL_DMA_IsEnabledStream(serial->config.dma.instance, serial->config.dma.tx_stream))
                {
                    /* dma is busy */
                    return E_BUSY;
                }
                uart_dma_tx_config(serial);
            }
            break;

            /* close device */
        case DEVICE_CTRL_SUSPEND:
            uart_close(serial);
            break;

        default:
            break;
    }

    return E_OK;
}

static int uart_putc(struct serial_device *serial, char c)
{
    ASSERT(serial != NULL);

    // /* clear tc flag before write */
    // LL_USART_ClearFlag_TC(uart->uart_device);
    /* TC flag is cleared by a write to TDR */
    serial->config.instance->TDR = c;
    /* wait write finish */
    while (LL_USART_IsActiveFlag_TC(serial->config.instance) == RESET);

    return 1;
}

static int uart_getc(struct serial_device *serial)
{
    int ch = -1;

    ASSERT(serial != NULL);

    /* check if read data register is not empty */
    if (LL_USART_IsActiveFlag_RXNE(serial->config.instance))
    {
        /* read DR will clear RXNE */
        ch = serial->config.instance->RDR & 0xff;
    }

    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct serial_device *serial)
{
    if (LL_USART_IsActiveFlag_RXNE(serial->config.instance) && LL_USART_IsEnabledIT_RXNE(serial->config.instance))
    {
        int ch = -1;
        base_t level;
        struct serial_rx_fifo *rx_fifo;

        /* interrupt mode receive */
        rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;
        ASSERT(rx_fifo != NULL);

        while (1)
        {
            ch = serial->ops->getc(serial);

            if (ch == -1)
                break;

            /* disable interrupt */
            level = os_hw_interrupt_disable();

            rx_fifo->buffer[rx_fifo->put_index] = ch;
            rx_fifo->put_index += 1;

            if (rx_fifo->put_index >= serial->config.bufsz)
                rx_fifo->put_index = 0;

            /* if the next position is read index, discard this 'read char' */
            if (rx_fifo->put_index == rx_fifo->get_index)
            {
                rx_fifo->get_index += 1;
                rx_fifo->is_full = TRUE;

                if (rx_fifo->get_index >= serial->config.bufsz)
                    rx_fifo->get_index = 0;
            }

            /* enable interrupt */
            os_hw_interrupt_enable(level);
        }

        /* invoke callback */
        if (serial->parent.rx_indicate != NULL)
        {
            size_t rx_length;

            /* get rx length */
            level = os_hw_interrupt_disable();
            rx_length = (rx_fifo->put_index >= rx_fifo->get_index) ? (rx_fifo->put_index - rx_fifo->get_index) : (
                    serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index));
            os_hw_interrupt_enable(level);
            if (rx_length)
            {
                serial->parent.rx_indicate(&serial->parent, rx_length);
            }
        }
        /* the RXNE flag is cleared by reading the USART_RDR register */
    }

    if (LL_USART_IsActiveFlag_IDLE(serial->config.instance) && LL_USART_IsEnabledIT_IDLE(serial->config.instance))
    {
        if (LL_USART_IsEnabledDMAReq_RX(serial->config.instance))
        {
            size_t recv_total_index, recv_len;
            base_t level;
            uint32_t remain_bytes;

            /* disable interrupt */
            level = os_hw_interrupt_disable();
            /* check remain bytes to receive */
            remain_bytes = LL_DMA_GetDataLength(serial->config.dma.instance, serial->config.dma.rx_stream);
            /* total received bytes */
            recv_total_index = serial->setting_recv_len - remain_bytes;
            /* received bytes at this time */
            recv_len = recv_total_index - serial->last_recv_index;
            /* update last received total bytes */
            serial->last_recv_index = recv_total_index;
            /* enable interrupt */
            os_hw_interrupt_enable(level);

            if (recv_len)
            {
                /* high-level ISR routine */
                int length = recv_len;

                /* disable interrupt */
                level = os_hw_interrupt_disable();
                /* update fifo put index */
                struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;
                ASSERT(rx_fifo != NULL);
                if (rx_fifo->get_index <= rx_fifo->put_index)
                {
                    rx_fifo->put_index += length;

                    /* beyond the fifo end */
                    if (rx_fifo->put_index >= serial->config.bufsz)
                    {
                        rx_fifo->put_index %= serial->config.bufsz;

                        /* force overwrite get index */
                        if (rx_fifo->put_index >= rx_fifo->get_index)
                        {
                            rx_fifo->is_full = TRUE;
                        }
                    }
                }
                else
                {
                    rx_fifo->put_index += length;

                    if (rx_fifo->put_index >= rx_fifo->get_index)
                    {
                        /* beyond the fifo end */
                        if (rx_fifo->put_index >= serial->config.bufsz)
                        {
                            rx_fifo->put_index %= serial->config.bufsz;
                        }

                        /* force overwrite get index */
                        rx_fifo->is_full = TRUE;
                    }
                }

                if (rx_fifo->is_full == TRUE)
                {
                    rx_fifo->get_index = rx_fifo->put_index;
                }

                if (rx_fifo->get_index >= serial->config.bufsz)
                    rx_fifo->get_index = 0;

                /* calculate received total length in fifo */
                length = uart_dma_calc_recved_len(serial);
                /* enable interrupt */
                os_hw_interrupt_enable(level);

                /* invoke callback */
                if (serial->parent.rx_indicate != NULL)
                {
                    serial->parent.rx_indicate(&(serial->parent), length);
                }
            }

        }
        /* clear interrupt flag */
        LL_USART_ClearFlag_IDLE(serial->config.instance);
    }

    if (LL_USART_IsActiveFlag_TC(serial->config.instance) && LL_USART_IsEnabledIT_TC(serial->config.instance))
    {
        // TODO: this can be used for TX_INT mode?
        // hal_serial_isr(serial, SERIAL_EVENT_TX_DONE);

        /* clear interrupt */
        LL_USART_ClearFlag_TC(serial->config.instance);
    }

    if (LL_USART_IsActiveFlag_ORE(serial->config.instance) != RESET)
    {
        uart_getc(serial);
        LL_USART_ClearFlag_ORE(serial->config.instance);
    }
}


/* usart driver operations */
static const struct uart_ops _usart_ops = {
        uart_configure,
        uart_control,
        uart_putc,
        uart_getc,
        uart_dma_transmit
};


SERIAL_DEFINE(0, UART7 );   //debug uart
SERIAL_DEFINE(1, USART1);   //gps1
SERIAL_DEFINE(2, USART2);   //telem1
SERIAL_DEFINE(3, UART8 );   //sbus ppm

err_t drv_uart_init()
{
#ifdef USE_UART7
    ERROR_TRY(hal_serial_register(&serial0,
                               "serial0",
                               DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_INT_RX,
                               NULL));
#endif

#ifdef USE_UART1
    ERROR_TRY(hal_serial_register(&serial1,
                               "serial1",
                               DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_INT_RX,
                               NULL));
#endif
    return E_OK;
}