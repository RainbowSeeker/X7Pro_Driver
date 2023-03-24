// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/20.
//

#include "drv_uart.h"
#include "algo/math/maths.h"
#include "board_config.h"
/* STM32 uart driver */
struct stm32_uart {
    USART_TypeDef* instance;
    IRQn_Type irq;
    struct dma_device *dma_tx;
    struct dma_device *dma_rx;
    /* setting receive len */
    size_t setting_recv_len;
    /* last receive index */
    size_t last_recv_index;
};

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
    else if(instance == USART2) __HAL_RCC_USART2_CLK_ENABLE();
    else if(instance == UART4) __HAL_RCC_UART4_CLK_ENABLE();
    else if(instance == UART8) __HAL_RCC_UART8_CLK_ENABLE();
    else ASSERT(0); // not support yet.
}

static void uart_gpio_init(USART_TypeDef *instance)
{
    if (instance == UART7)
    {
        io_init(PF6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_UART7);
        io_init(PE8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_UART7);
    }
    else if (instance == USART1)
    {
        /**USART1 GPIO Configuration
        PB6     ------> USART1_TX
        PB7     ------> USART1_RX
        */
        io_init(PB7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART1);
        io_init(PB6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART1);
    }
    else if (instance == UART4)
    {
        io_init(PD0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF8_UART4);
        io_init(PD1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF8_UART4);
    }
    else if (instance == UART8)
    {
        io_init(PE0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF8_UART8);
        io_init(PE1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF8_UART8);
    }
    else ASSERT(0); // not support yet.
}


__STATIC_INLINE void _dma_clear_flags(struct dma_device *dma)
{
    LL_EX_DMA_ClearFlag(dma, 0x3D);
}

static size_t uart_dma_transmit(struct serial_device *serial, uint8_t *buf, size_t size, int direction)
{
    if (direction == SERIAL_DMA_TX) {
        struct stm32_uart* uart = serial->parent.user_data;
        if (LL_DMA_IsEnabledStream(uart->dma_tx->instance, uart->dma_tx->stream))
        {
            /* if the dma stream is enabled, disable it */
            LL_DMA_DisableStream(uart->dma_tx->instance, uart->dma_tx->stream);
            /* wait all current transfers are finished */
            while (LL_DMA_IsEnabledStream(uart->dma_tx->instance, uart->dma_tx->stream));
        }

        /* all interrupt flags much be cleared before the stream can be re-enabled */
        _dma_clear_flags(uart->dma_tx);
        /* set data length */
        LL_DMA_SetDataLength(uart->dma_tx->instance, uart->dma_tx->stream, size);
        /* configure dma address */
        LL_DMA_SetMemoryAddress(uart->dma_tx->instance, uart->dma_tx->stream, (uint32_t) buf);
        /* enable common interrupts */
        LL_DMA_EnableIT_TC(uart->dma_tx->instance, uart->dma_tx->stream);
        /* enable the specified dma stream */
        LL_DMA_EnableStream(uart->dma_tx->instance, uart->dma_tx->stream);

        /* clear uart transmission complete flag */
        LL_USART_ClearFlag_TC(uart->instance);
        /* enable the uart dma transmit */
        LL_USART_EnableDMAReq_TX(uart->instance);
        return size;
    }

    return 0;
}

static void uart_dma_receive(struct stm32_uart* uart)
{
    /* all interrupt flags much be cleared before the stream can be re-enabled */
    _dma_clear_flags(uart->dma_rx);
    /* enable common interrupts */
    LL_DMA_EnableIT_TC(uart->dma_rx->instance, uart->dma_rx->stream);
    /* enable the specified dma stream */
    LL_DMA_EnableStream(uart->dma_rx->instance, uart->dma_rx->stream);

    /* enable the uart dma receive */
    LL_USART_EnableDMAReq_RX(uart->instance);

    /* enable idle interrupts */
    LL_USART_ClearFlag_IDLE(uart->instance);
    LL_USART_EnableIT_IDLE(uart->instance);
}

static void uart_dma_tx_config(struct stm32_uart* uart)
{
    LL_DMA_InitTypeDef DMA_InitStruct;
    uint32_t request;
    ASSERT(dma_get_request_by_instance(uart->instance, &request) == E_OK);
    ASSERT(uart->dma_tx != NULL);

    DMA_InitStruct.PeriphOrM2MSrcAddress = (uint32_t) &uart->instance->TDR;
    DMA_InitStruct.MemoryOrM2MDstAddress = 0x00000000U; /* will be configured later */
    DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
    DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
    DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
    DMA_InitStruct.NbData = 0x00000000U; /* will be configured later */
    DMA_InitStruct.PeriphRequest = request;
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
    DMA_InitStruct.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_4;
    DMA_InitStruct.MemBurst = LL_DMA_MBURST_SINGLE;
    DMA_InitStruct.PeriphBurst = LL_DMA_PBURST_SINGLE;
    /* init tx dma */
    LL_DMA_Init(uart->dma_tx->instance, uart->dma_tx->stream, &DMA_InitStruct);

    /* disable double buffer mode */
    LL_DMA_DisableDoubleBufferMode(uart->dma_tx->instance, uart->dma_tx->stream);
    LL_DMA_DisableFifoMode(uart->dma_tx->instance, uart->dma_tx->stream);
}

static void uart_dma_rx_config(struct stm32_uart* uart, uint8_t *buf, size_t size)
{
    LL_DMA_InitTypeDef DMA_InitStruct;
    uint32_t request;
    ASSERT(dma_get_request_by_instance(uart->instance, &request) == E_OK);
    ASSERT(uart->dma_rx != NULL);

    /* set expected receive length */
    uart->setting_recv_len = size;

    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    DMA_InitStruct.PeriphOrM2MSrcAddress = (uint32_t) &uart->instance->RDR;
    DMA_InitStruct.MemoryOrM2MDstAddress = (uint32_t) buf;
    DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    DMA_InitStruct.Mode = LL_DMA_MODE_CIRCULAR;
    DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
    DMA_InitStruct.NbData = size;
    DMA_InitStruct.PeriphRequest = request - 1;
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
    DMA_InitStruct.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_4;
    DMA_InitStruct.MemBurst = LL_DMA_MBURST_SINGLE;
    DMA_InitStruct.PeriphBurst = LL_DMA_PBURST_SINGLE;

    /* init rx dma */
    LL_DMA_Init(uart->dma_rx->instance, uart->dma_rx->stream, &DMA_InitStruct);

    /* disable double buffer mode */
    LL_DMA_DisableDoubleBufferMode(uart->dma_rx->instance, uart->dma_rx->stream);
    LL_DMA_DisableFifoMode(uart->dma_rx->instance, uart->dma_rx->stream);

    /* start to receive data */
    uart_dma_receive(uart);
}

static void dma_tx_done_isr(struct serial_device* serial);
static void dma_rx_done_isr(struct serial_device* serial);

static err_t uart_configure(struct serial_device *serial, struct serial_configure *config)
{
    struct stm32_uart* uart;
    LL_USART_InitTypeDef USART_InitStructure = {0};

    ASSERT(serial != NULL);
    ASSERT(config != NULL);

    uart = (struct stm32_uart*)serial->parent.user_data;

    uart_enable_clock(uart->instance);
    uart_gpio_init(uart->instance);

    if (uart->instance == LPUART1)
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
    LL_USART_Disable(uart->instance);
    LL_USART_Init(uart->instance, &USART_InitStructure);
    LL_USART_ConfigAsyncMode(uart->instance);

    if (config->invert)
    {
        LL_USART_SetTXRXSwap(uart->instance, (config->invert & NRZ_TXRXSWAP) ? LL_USART_TXRX_SWAPPED : LL_USART_TXRX_STANDARD);
        LL_USART_SetTXPinLevel(uart->instance, (config->invert & NRZ_TXINV) ? LL_USART_TXPIN_LEVEL_INVERTED : LL_USART_TXPIN_LEVEL_STANDARD);
        LL_USART_SetRXPinLevel(uart->instance, (config->invert & NRZ_RXINV) ? LL_USART_RXPIN_LEVEL_INVERTED : LL_USART_RXPIN_LEVEL_STANDARD);
    }

    LL_USART_Enable(uart->instance);

    if (uart->dma_tx){
        ERROR_TRY(hal_dma_register(uart->dma_tx, uart->dma_tx->parent.name, DEVICE_FLAG_WRONLY));
        dma_configure_irq(uart->dma_tx, (void (*)(uint32_t)) dma_tx_done_isr, NVIC_PRIO_UART_DMA, (uint32_t) serial);
    }
    if (uart->dma_rx)
    {
        ERROR_TRY(hal_dma_register(uart->dma_rx, uart->dma_rx->parent.name, DEVICE_FLAG_RDONLY));
        dma_configure_irq(uart->dma_rx, (void (*)(uint32_t)) dma_rx_done_isr, NVIC_PRIO_UART_DMA, (uint32_t) serial);
    }

    return E_OK;
}

static void uart_close(struct serial_device *serial)
{
    ASSERT(serial != NULL);
    struct stm32_uart* uart = (struct stm32_uart*)serial->parent.user_data;

    if (serial->parent.open_flag & DEVICE_FLAG_INT_RX)
    {
        /* disable int rx irq */
        LL_USART_DisableIT_RXNE(uart->instance);
    }

    if (serial->parent.open_flag & DEVICE_FLAG_DMA_RX)
    {
        /* disable dma rx irq and disable rx dma */
        LL_DMA_DisableIT_TC(uart->dma_rx->instance, uart->dma_rx->stream);
        LL_USART_DisableIT_IDLE(uart->instance);
        LL_DMA_DisableStream(uart->dma_rx->instance, uart->dma_rx->stream);
        LL_USART_DisableDMAReq_RX(uart->instance);
    }

    if (serial->parent.open_flag & DEVICE_FLAG_DMA_TX)
    {
        /* disable dma tx irq and disable tx dma */
        LL_DMA_DisableIT_TC(uart->dma_tx->instance, uart->dma_tx->stream);
        LL_DMA_DisableStream(uart->dma_tx->instance, uart->dma_tx->stream);
        LL_USART_DisableDMAReq_TX(uart->instance);
    }
}

static err_t uart_control(struct serial_device *serial, int cmd, void *arg)
{
    struct stm32_uart* uart;
    uint32_t ctrl_arg = (uint32_t) (arg);

    ASSERT(serial != NULL);
    uart = (struct stm32_uart*)serial->parent.user_data;

    switch (cmd)
    {
        case DEVICE_CTRL_CLR_INT:
            if (ctrl_arg == DEVICE_FLAG_INT_RX)
            {
                /* disable rx irq */
                HAL_NVIC_DisableIRQ(uart->irq);
                /* disable interrupt */
                LL_USART_DisableIT_RXNE(uart->instance);
            }
            break;

        case DEVICE_CTRL_SET_INT:
            if (ctrl_arg == DEVICE_FLAG_INT_RX)
            {
                /* disable rx irq */
                HAL_NVIC_SetPriority(uart->irq, NVIC_PRIO_UART, 0);
                HAL_NVIC_EnableIRQ(uart->irq);
                /* disable interrupt */
                LL_USART_EnableIT_RXNE(uart->instance);
            }
            break;

            /* USART DMA config */
        case DEVICE_CTRL_CONFIG:
            if (ctrl_arg == DEVICE_FLAG_DMA_RX)
            {
                struct serial_rx_fifo *rx_fifo = (struct serial_rx_fifo *) serial->serial_rx;

                if (LL_DMA_IsEnabledStream(uart->dma_rx->instance, uart->dma_rx->stream))
                {
                    /* dma is busy */
                    return E_BUSY;
                }
                /* disable rx irq */
                HAL_NVIC_SetPriority(uart->irq, NVIC_PRIO_UART, 0);
                HAL_NVIC_EnableIRQ(uart->irq);
                uart_dma_rx_config(uart, rx_fifo->buffer, serial->config.bufsz);
            }

            if (ctrl_arg == DEVICE_FLAG_DMA_TX)
            {
                if (LL_DMA_IsEnabledStream(uart->dma_tx->instance, uart->dma_tx->stream))
                {
                    /* dma is busy */
                    return E_BUSY;
                }
                uart_dma_tx_config(uart);
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
    struct stm32_uart* uart;
    ASSERT(serial != NULL);
    uart = (struct stm32_uart*)serial->parent.user_data;

    LL_USART_TransmitData8(uart->instance, c);
    while (LL_USART_IsActiveFlag_TXE_TXFNF(uart->instance) == RESET);
    return 1;
}

static int uart_getc(struct serial_device *serial)
{
    int ch = -1;
    struct stm32_uart* uart;
    ASSERT(serial != NULL);
    uart = (struct stm32_uart*)serial->parent.user_data;

    /* check if read data register is not empty */
    if (LL_USART_IsActiveFlag_RXNE(uart->instance))
    {
        /* read DR will clear RXNE */
        ch = LL_USART_ReceiveData8(uart->instance);
    }

    return ch;
}


/**
 * Serial port receive idle process. This need add to uart idle ISR.
 *
 * @param serial serial device
 */
static void dma_uart_rx_idle_isr(struct serial_device* serial)
{
    struct stm32_uart* uart = (struct stm32_uart*)serial->parent.user_data;
    size_t recv_total_index, recv_len;
    base_t level;
    uint32_t remain_bytes;

    /* disable interrupt */
    level = os_hw_interrupt_disable();
    /* check remain bytes to receive */
    remain_bytes = LL_DMA_GetDataLength(uart->dma_rx->instance, uart->dma_rx->stream);
    /* total received bytes */
    recv_total_index = uart->setting_recv_len - remain_bytes;
    /* received bytes at this time */
    recv_len = recv_total_index - uart->last_recv_index;
    /* update last received total bytes */
    uart->last_recv_index = recv_total_index;
    /* enable interrupt */
    os_hw_interrupt_enable(level);

    if (recv_len) {
        /* high-level ISR routine */
        hal_serial_isr(serial, SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}


/**
 * DMA receive done process. This need add to DMA receive done ISR.
 *
 * @param serial serial device
 */
static void dma_rx_done_isr(struct serial_device* serial)
{
    struct stm32_uart* uart = (struct stm32_uart*)serial->parent.user_data;
    if (LL_EX_DMA_IsActiveFlag(uart->dma_rx, DMA_IT_TCIF))
    {
        size_t recv_len;
        base_t level;

        /* disable interrupt */
        level = os_hw_interrupt_disable();
        /* received bytes at this time */
        recv_len = uart->setting_recv_len - uart->last_recv_index;
        /* reset last recv index */
        uart->last_recv_index = 0;
        /* enable interrupt */
        os_hw_interrupt_enable(level);

        if (recv_len) {
            /* high-level ISR routine */
            hal_serial_isr(serial, SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
        /* clear the interrupt flag */
        LL_EX_DMA_ClearFlag(uart->dma_rx, DMA_IT_TCIF);
    }
}

/**
 * DMA transmit done process. This need add to DMA receive done ISR.
 *
 * @param serial serial device
 */
static void dma_tx_done_isr(struct serial_device* serial)
{
    struct stm32_uart* uart = (struct stm32_uart*)serial->parent.user_data;
    if (LL_EX_DMA_IsActiveFlag(uart->dma_tx, DMA_IT_TCIF))
    {
        /* high-level ISR routine */
        hal_serial_isr(serial, SERIAL_EVENT_TX_DMADONE);

        LL_EX_DMA_ClearFlag(uart->dma_tx, DMA_IT_TCIF);
    }
}


/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct serial_device *serial)
{
    struct stm32_uart* uart = (struct stm32_uart*)serial->parent.user_data;

    if (LL_USART_IsActiveFlag_RXNE(uart->instance) && LL_USART_IsEnabledIT_RXNE(uart->instance))
    {
        /* high-level ISR routine */
        hal_serial_isr(serial, SERIAL_EVENT_RX_IND);
        /* the RXNE flag is cleared by reading the USART_RDR register */
    }

    if (LL_USART_IsActiveFlag_IDLE(uart->instance) && LL_USART_IsEnabledIT_IDLE(uart->instance))
    {
        if (LL_USART_IsEnabledDMAReq_RX(uart->instance))
        {
            dma_uart_rx_idle_isr(serial);
        }
        /* clear interrupt flag */
        LL_USART_ClearFlag_IDLE(uart->instance);
    }

    if (LL_USART_IsActiveFlag_TC(uart->instance) && LL_USART_IsEnabledIT_TC(uart->instance))
    {
        // TODO: this can be used for TX_INT mode?
        // hal_serial_isr(serial, SERIAL_EVENT_TX_DONE);

        /* clear interrupt */
        LL_USART_ClearFlag_TC(uart->instance);
    }

    if (LL_USART_IsActiveFlag_ORE(uart->instance) != RESET)
    {
        uart_getc(serial);
        LL_USART_ClearFlag_ORE(uart->instance);
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


//---- serialx, uartx,  baudrate --------
SERIAL_DEFINE(0,  7,  115200);   //debug uart
SERIAL_DEFINE(1,  2,  115200);   //telem1
SERIAL_DEFINE(2,  1,  57600);    //gps1
SERIAL_DEFINE(5,  8,  100000);   //sbus ppm

err_t drv_uart_init()
{
#ifdef USE_UART7
    ERROR_TRY(hal_serial_register(&serial0,
                               "serial0",
                               DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_INT_RX,
                               &uart7));
#endif

#ifdef USE_UART2
    ERROR_TRY(hal_serial_register(&serial1,
                               "serial1",
                               DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_INT_RX,
                               &uart2));
#endif

#ifdef USE_UART1
    ERROR_TRY(hal_serial_register(&serial2,
                                  "serial2",
                                  DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_INT_RX,
                                  &uart1));
#endif

#ifdef USE_UART8
    uart8.dma_tx = LL_DMA_DeviceGetByName("dma2_stream0");
    uart8.dma_rx = LL_DMA_DeviceGetByName("dma2_stream1");
    serial5.config.data_bits = DATA_BITS_9;
    serial5.config.stop_bits = STOP_BITS_2;
    serial5.config.parity = PARITY_EVEN;
    serial5.config.invert = NRZ_TXRXSWAP | NRZ_RXINV;
    serial5.config.bufsz = 1024;

    ERROR_TRY(hal_serial_register(&serial5,
                                  "serial5",
                                  DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_INT_RX | DEVICE_FLAG_DMA_TX | DEVICE_FLAG_DMA_RX,
                                  &uart8));
#endif
    return E_OK;
}
