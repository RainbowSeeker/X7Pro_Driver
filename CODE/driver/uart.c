// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/20.
//

#include "uart.h"
#include "dma.h"
#include "nvic.h"
#include "atomic.h"
#include "algo/math/maths.h"

static uart_t uartDev[UART_NUM];

static DMA_DATA uint8_t UART_TX_BUF[UART_NUM][UART_TX_BUF_SIZE];
static DMA_DATA uint8_t UART_RX_BUF[UART_NUM][UART_RX_BUF_SIZE];

static const uart_hwconfig_t uartHwconfig[UART_NUM] =
        {
#ifdef USE_UART1
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART2
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART3
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART4
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART5
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART6
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART7
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
#ifdef USE_UART8
                {{GPIOE,GPIO_PIN_8}, GPIO_AF7_UART7, {GPIOF,GPIO_PIN_6},GPIO_AF7_UART7,
                 460800, UART_HWCONTROL_NONE, 1,}
#endif
        };




static IRQn_Type uartIrqEnum[UART_NUM] =
        {
#ifdef USE_UART1
                USART1_IRQn,
#endif
#ifdef USE_UART2
                USART2_IRQn,
#endif
#ifdef USE_UART3
                USART3_IRQn,
#endif
#ifdef USE_UART4
                USART4_IRQn,
#endif
#ifdef USE_UART5
                USART5_IRQn,
#endif
#ifdef USE_UART6
                USART6_IRQn,
#endif
#ifdef USE_UART7
                UART7_IRQn,
#endif
#ifdef USE_UART8
                USART8_IRQn,
#endif
        };

static void *Uart_InstanceByID(uart_device_e uartDevice)
{
    switch (uartDevice)
    {
#ifdef USE_UART1
        case UART_1:
            return USART1;
#endif
#ifdef USE_UART2
        case UART_2:
            return USART2;
#endif
#ifdef USE_UART3
        case UART_3:
            return USART3;
#endif
#ifdef USE_UART4
        case UART_4:
            return UART4;
#endif
#ifdef USE_UART5
        case UART_5:
            return UART5;
#endif
#ifdef USE_UART6
        case UART_6:
            return USART6;
#endif
#ifdef USE_UART7
        case UART_7:
            return UART7;
#endif
#ifdef USE_UART8
            case UART_8:
                return UART8;
#endif
        default:
            return NULL;
    }
}

static void Uart_EnableClock(uart_device_e uartDevice)
{
    USART_TypeDef *instance = Uart_InstanceByID(uartDevice);
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

    switch (uartDevice)
    {
#ifdef USE_UART1
        case UART_1:
            __HAL_RCC_USART1_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART2
        case UART_2:
            __HAL_RCC_UART2_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART3
        case UART_3:
            __HAL_RCC_UART3_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART4
        case UART_4:
            __HAL_RCC_UART4_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART5
        case UART_5:
            __HAL_RCC_UART5_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART6
        case UART_6:
            __HAL_RCC_UART6_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART7
        case UART_7:
            __HAL_RCC_UART7_CLK_ENABLE();
            break;
#endif
#ifdef USE_UART8
            __HAL_RCC_UART8_CLK_ENABLE();
            break;
#endif
        default:
            break;
    }

}

static void Uart_TxDMAIrqHandler(dma_t *dma)
{
    uart_t *uart = (uart_t *) dma->userParam;
    HAL_DMA_IRQHandler(uart->huart.hdmatx);
}

void UART_InitDev(uart_device_e uartDevice, const uart_hwconfig_t *config)
{
    if (!config->txPin.port && !config->rxPin.port) return;
    uart_t *uart = &uartDev[uartDevice - 1];
    UART_HandleTypeDef *huart = &uart->huart;

    huart->Instance = Uart_InstanceByID(uartDevice);
    HAL_UART_DeInit(huart);

    huart->Init.BaudRate = config->baudRate;
//    huart->Init.WordLength = config->wordLength;
//    huart->Init.StopBits = config->stopBits;
//    huart->Init.Parity = config->parity;
//    huart->Init.Mode = config->mode;
    huart->Init.WordLength = UART_WORDLENGTH_8B;
    huart->Init.StopBits = UART_STOPBITS_1;
    huart->Init.Parity = UART_PARITY_NONE;
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = config->hwFlowCtl;
//    huart->Init.OneBitSampling = config->oneBitSampling;
    huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    if (huart->Instance == LPUART1)
    {
        huart->Init.ClockPrescaler = UART_PRESCALER_DIV8;
    }
    Uart_EnableClock(uartDevice);

    HAL_UART_Init(huart);

    uart->useDMA = config->useDMA;
    if (config->txPin.port && (huart->Init.Mode & UART_MODE_TX))
    {
        IO_Init(config->txPin, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, config->txAF);

        if (uart->useDMA)
        {
            for (uint8_t opt = 0; opt < MAX_PERIPHERAL_DMA_OPTIONS; opt++)
            {
                const dma_channel_t *dmaTxChannelSpec = DMA_GetChannelSpecByPeripheral(DMA_PERIPH_UART_TX, uartDevice,
                                                                                       opt);

                if (dmaTxChannelSpec)
                {
                    uint8_t dmaTxStream = DMA_GetIdentifier(dmaTxChannelSpec->ref);

                    uart->dmaTx = DMA_GetDescriptorByIdentifier(dmaTxStream);
                    uart->dmaTx->stream = DMA_DEVICE_INDEX(dmaTxStream);
                    uart->dmaTx->channel = dmaTxChannelSpec->channel;

                    DMA_Enable(dmaTxStream);
                    DMA_SetHandler(dmaTxStream, Uart_TxDMAIrqHandler, NVIC_PRIO_UART_DMA, (uint32_t) uart);

                    break;
                }
                if (opt == MAX_PERIPHERAL_DMA_OPTIONS - 1) return;
            }

            uart->txDMAHandle.Instance = uart->dmaTx->ref;
            uart->txDMAHandle.Init.Request = uart->dmaTx->channel;
            uart->txDMAHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
            uart->txDMAHandle.Init.PeriphInc = DMA_PINC_DISABLE;
            uart->txDMAHandle.Init.MemInc = DMA_MINC_ENABLE;
            uart->txDMAHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            uart->txDMAHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
            uart->txDMAHandle.Init.Mode = DMA_NORMAL;
            uart->txDMAHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
            uart->txDMAHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
            uart->txDMAHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;
            uart->txDMAHandle.Init.MemBurst = DMA_MBURST_SINGLE;
            uart->txDMAHandle.Init.Priority = DMA_PRIORITY_LOW;
            HAL_DMA_DeInit(&uart->txDMAHandle);

            if (HAL_OK != HAL_DMA_Init(&uart->txDMAHandle))
                while (1);

            __HAL_LINKDMA(huart, hdmatx, uart->txDMAHandle);

            __HAL_DMA_SET_COUNTER(&uart->txDMAHandle, 0);
        }
        else
        {
            /* Enable the UART Transmit Data Register Empty Interrupt */
            SET_BIT(huart->Instance->CR1, USART_CR1_TXEIE);
        }

    }
    if (config->rxPin.port && (huart->Init.Mode & UART_MODE_RX))
    {
        IO_Init(config->rxPin, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, config->rxAF);

        if (uart->useDMA)
        {
            for (uint8_t opt = 0; opt < MAX_PERIPHERAL_DMA_OPTIONS; opt++)
            {
                const dma_channel_t *dmaRxChannelSpec = DMA_GetChannelSpecByPeripheral(DMA_PERIPH_UART_RX, uartDevice,
                                                                                       opt);

                if (dmaRxChannelSpec)
                {
                    uint8_t dmaRxStream = DMA_GetIdentifier(dmaRxChannelSpec->ref);

                    uart->dmaRx = DMA_GetDescriptorByIdentifier(dmaRxStream);
                    uart->dmaRx->stream = DMA_DEVICE_INDEX(dmaRxStream);
                    uart->dmaRx->channel = dmaRxChannelSpec->channel;

                    DMA_Enable(dmaRxStream);
                    break;
                }
                if (opt == MAX_PERIPHERAL_DMA_OPTIONS - 1) return;
            }

            uart->rxDMAHandle.Instance = uart->dmaRx->ref;
            uart->rxDMAHandle.Init.Request = uart->dmaRx->channel;
            uart->rxDMAHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
            uart->rxDMAHandle.Init.PeriphInc = DMA_PINC_DISABLE;
            uart->rxDMAHandle.Init.MemInc = DMA_MINC_ENABLE;
            uart->rxDMAHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            uart->rxDMAHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
            uart->rxDMAHandle.Init.Mode = DMA_CIRCULAR;
            uart->rxDMAHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
            uart->rxDMAHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
            uart->rxDMAHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;
            uart->rxDMAHandle.Init.MemBurst = DMA_MBURST_SINGLE;
            uart->rxDMAHandle.Init.Priority = DMA_PRIORITY_LOW;

            HAL_DMA_DeInit(&uart->rxDMAHandle);
            HAL_DMA_Init(&uart->rxDMAHandle);
            /* Associate the initialized DMA handle to the UART handle */
            __HAL_LINKDMA(huart, hdmarx, uart->rxDMAHandle);

            HAL_UART_Receive_DMA(huart, (uint8_t *) &UART_RX_BUF[uartDevice - 1][0], UART_RX_BUF_SIZE);

        }
        else
        {
            /* Enable the UART Parity Error Interrupt */
            SET_BIT(huart->Instance->CR1, USART_CR1_PEIE);

            /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
            SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

            /* Enable the UART Data Register not empty Interrupt */
            SET_BIT(huart->Instance->CR1, USART_CR1_RXNEIE);

            /* Enable Idle Line detection */
            SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
        }

    }

    HAL_NVIC_SetPriority(uartIrqEnum[uartDevice], NVIC_PRIO_UART, 0);
    HAL_NVIC_EnableIRQ(uartIrqEnum[uartDevice]);

}

void UART_BspInit()
{
#ifdef USE_UART1
    UART_InitDev(UART_1, &uartHwconfig[UART_1 - 1]);
#endif
#ifdef USE_UART2
    UART_InitDev(UART_2, &uartHwconfig[UART_2 - 1]);
#endif
#ifdef USE_UART3
    UART_InitDev(UART_3, &uartHwconfig[UART_3 - 1]);
#endif
#ifdef USE_UART4
    UART_InitDev(UART_4, &uartHwconfig[UART_4 - 1]);
#endif
#ifdef USE_UART5
    UART_InitDev(UART_5, &uartHwconfig[UART_5 - 1]);
#endif
#ifdef USE_UART6
    UART_InitDev(UART_6, &uartHwconfig[UART_6 - 1]);
#endif
#ifdef USE_UART7
    UART_InitDev(UART_7, &uartHwconfig[UART_7 - 1]);
#endif
#ifdef USE_UART8
    UART_InitDev(UART_8, &uartHwconfig[UART_8 - 1]);
#endif
}



uart_t *Uart_Init(uart_device_e uartDevice, uart_receive_callback rxCallback)
{
    uart_t *uart = &uartDev[uartDevice - 1];

    uart->uartID = uartDevice;
    uart->uartMode = uart->huart.Init.Mode;
    uart->txBuffer = UART_TX_BUF[uartDevice - 1];
    uart->txBufferHead = uart->txBufferTail = 0;
    uart->txBufferSize = UART_TX_BUF_SIZE;

    uart->rxBuffer = UART_RX_BUF[uartDevice - 1];
    uart->rxBufferHead = uart->rxBufferTail = 0;
    uart->rxBufferSize = UART_RX_BUF_SIZE;

    uart->rxCallback = rxCallback;
    uart->callbackParam = (uint32_t) uart;
    uart->txDMAEmpty = true;

//    osSemaphoreDef(uart);
//    uart->lock = osSemaphoreCreate(osSemaphore(uart), 1);

    if (uart->huart.hdmarx)    uart->rxDMAPos = __HAL_DMA_GET_COUNTER(uart->huart.hdmarx);
    return uart;
}


static void Uart_TryStartTxDMA(uart_t *uart)
{
    if (IS_DMA_ENABLED(uart->huart.hdmatx))
    {
        // DMA is already in progress
        return;
    }

    HAL_UART_StateTypeDef state = HAL_UART_GetState(&uart->huart);
    if ((state & HAL_UART_STATE_BUSY_TX) == HAL_UART_STATE_BUSY_TX)
    {
        // UART is still transmitting
        return;
    }

    if (uart->txBufferHead == uart->txBufferTail)
    {
        // No more data to transmit
        uart->txDMAEmpty = true;
        return;
    }

    ATOMIC_ENTER_CRITICAL();

    uint16_t size;
    uint32_t fromwhere = uart->txBufferTail;
    if (uart->txBufferHead > uart->txBufferTail)
    {
        size = uart->txBufferHead - uart->txBufferTail;
        uart->txBufferTail = uart->txBufferHead;
    }
    else
    {
        size = uart->txBufferSize - uart->txBufferTail;
        uart->txBufferTail = 0;
    }
    uart->txDMAEmpty = false;

    HAL_UART_Transmit_DMA(&uart->huart, (uint8_t *) &uart->txBuffer[fromwhere], size);

    ATOMIC_EXIT_CRITICAL();
}

void Uart_Write(uart_t *uart, uint8_t *str, uint16_t len)
{
    uint16_t remainingLen = uart->txBufferSize - (uart->txBufferHead - uart->txBufferTail + uart->txBufferSize) % uart->txBufferSize - 1;
    uint16_t trueLen = min(remainingLen, len);

    OS_ENTER_CRITICAL;
    for (uint16_t i = 0; i < trueLen; ++i)
    {
        uart->txBuffer[uart->txBufferHead] = str[i];
        uart->txBufferHead = (uart->txBufferHead + 1) % uart->txBufferSize;
    }
    OS_EXIT_CRITICAL;

    if (uart->huart.hdmatx)
    {
        Uart_TryStartTxDMA(uart);
    }
    else
    {
        __HAL_UART_ENABLE_IT(&uart->huart, UART_IT_TXE);
    }
}

uint8_t Uart_ReadByte(uart_t *uart)
{
    uint8_t ch;

    if (uart->huart.hdmarx)
    {
        ch = uart->rxBuffer[uart->rxBufferSize - uart->rxDMAPos];
        if (--uart->rxDMAPos == 0)
            uart->rxDMAPos = uart->rxBufferSize;
    }
    else
    {
        ch = uart->rxBuffer[uart->rxBufferTail];
        if (uart->rxBufferTail + 1 >= uart->rxBufferSize)
        {
            uart->rxBufferTail = 0;
        }
        else
        {
            uart->rxBufferTail++;
        }
    }

    return ch;
}

uint32_t Uart_TotalRxBytesWaiting(uart_t *uart)
{
    if (uart->huart.hdmarx)
    {
        // XXX Could be consolidated
        uint32_t rxDMAHead = __HAL_DMA_GET_COUNTER(uart->huart.hdmarx);
        // uart->rxDMAPos and rxDMAHead represent distances from the end
        // of the buffer.  They count DOWN as they advance.
        if (uart->rxDMAPos >= rxDMAHead)
        {
            return uart->rxDMAPos - rxDMAHead;
        }
        else
        {
            return uart->rxBufferSize + uart->rxDMAPos - rxDMAHead;
        }
    }

    if (uart->rxBufferHead >= uart->rxBufferTail)
    {
        return uart->rxBufferHead - uart->rxBufferTail;
    }
    else
    {
        return uart->rxBufferSize + uart->rxBufferHead - uart->rxBufferTail;
    }
}

uint32_t Uart_TotalTxBytesFree(uart_t *uart)
{
    uint32_t bytesUsed;
    if (uart->txBufferHead >= uart->txBufferTail)
    {
        bytesUsed = uart->txBufferHead - uart->txBufferTail;
    }
    else
    {
        bytesUsed = uart->txBufferSize + uart->txBufferHead - uart->txBufferTail;
    }


    if (uart->huart.hdmatx)
    {
        /*
         * When we queue up a DMA request, we advance the Tx buffer tail before the transfer finishes, so we must add
         * the remaining size of that in-progress transfer here instead:
         */

        bytesUsed += __HAL_DMA_GET_COUNTER(uart->huart.hdmatx);
        /*
         * If the Tx buffer is being written to very quickly, we might have advanced the head into the buffer
         * space occupied by the current DMA transfer. In that case the "bytesUsed" total will actually end up larger
         * than the total Tx buffer size, because we'll end up transmitting the same buffer region twice. (So we'll be
         * transmitting a garbage mixture of old and new bytes).
         *
         * Be kind to callers and pretend like our buffer can only ever be 100% full.
         */
        if (bytesUsed >= uart->txBufferSize - 1)
        {
            return 0;
        }
    }

    return (uart->txBufferSize - 1) - bytesUsed;
}


void Uart_IrqHandler(uart_t *uart)
{
    UART_HandleTypeDef *huart = &uart->huart;

    /* UART in mode Receiver ---------------------------------------------------*/
    if ((__HAL_UART_GET_IT(huart, UART_IT_RXNE) != RESET))
    {
        uint8_t res = (uint8_t) (huart->Instance->RDR & (uint8_t) 0xff);

        if (uart->rxCallback)
        {
            uart->rxCallback(res, uart->callbackParam);
        }
        else
        {
            uart->rxBuffer[uart->rxBufferHead] = res;
            uart->rxBufferHead = (uart->rxBufferHead + 1) % uart->rxBufferSize;
        }
        CLEAR_BIT(huart->Instance->CR1, (USART_CR1_PEIE));

        /* Disable the UART Error Interrupt: (Frame error, noise error, overrun error) */
        CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

        __HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST);
    }

    /* UART parity error interrupt occurred -------------------------------------*/
    if ((__HAL_UART_GET_IT(huart, UART_IT_PE) != RESET))
    {
        __HAL_UART_CLEAR_IT(huart, UART_CLEAR_PEF);
    }

    /* UART frame error interrupt occurred --------------------------------------*/
    if ((__HAL_UART_GET_IT(huart, UART_IT_FE) != RESET))
    {
        __HAL_UART_CLEAR_IT(huart, UART_CLEAR_FEF);
    }

    /* UART noise error interrupt occurred --------------------------------------*/
    if ((__HAL_UART_GET_IT(huart, UART_IT_NE) != RESET))
    {
        __HAL_UART_CLEAR_IT(huart, UART_CLEAR_NEF);
    }

    /* UART Over-Run interrupt occurred -----------------------------------------*/
    if ((__HAL_UART_GET_IT(huart, UART_IT_ORE) != RESET))
    {
        __HAL_UART_CLEAR_IT(huart, UART_CLEAR_OREF);
    }

    // UART transmitter in interrupting mode, tx buffer empty
    if (!uart->huart.hdmatx && (__HAL_UART_GET_IT(huart, UART_IT_TXE) != RESET))
    {
        /* Check that a Tx process is ongoing */
        if (huart->gState != HAL_UART_STATE_BUSY_TX)
        {
            if (uart->txBufferTail == uart->txBufferHead)
            {
                huart->TxXferCount = 0;
                /* Disable the UART Transmit Data Register Empty Interrupt */
                CLEAR_BIT(huart->Instance->CR1, USART_CR1_TXEIE);
            }
            else
            {
                if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
                {
                    huart->Instance->TDR = (((uint16_t) uart->txBuffer[uart->txBufferTail]) & (uint16_t) 0x01FFU);
                }
                else
                {
                    huart->Instance->TDR = (uint8_t) (uart->txBuffer[uart->txBufferTail]);
                }
                uart->txBufferTail = (uart->txBufferTail + 1) % uart->txBufferSize;
            }
        }
    }

    // UART transmitter in DMA mode, transmission completed
    if ((__HAL_UART_GET_IT(huart, UART_IT_TC) != RESET))
    {
        HAL_UART_IRQHandler(huart);

        if (uart->huart.hdmatx)
        {
            Uart_TryStartTxDMA(uart);
        }

    }

    // UART reception idle detected
    if (__HAL_UART_GET_IT(huart, UART_IT_IDLE))
    {
//        if (uart->idleCallback)
//        {
//            uart->idleCallback();
//        }

        __HAL_UART_CLEAR_IDLEFLAG(huart);
    }

}

#define UART_IRQHandler(type, number, dev)                    \
    void type ## number ## _IRQHandler(void)                  \
    {                                                         \
        uart_t *uart = &(uartDev[UART_ ## dev - 1]);    \
        Uart_IrqHandler(uart);                                 \
    }


#ifdef USE_UART1
UART_IRQHandler(USART, 1, 1) // USART1 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART2
UART_IRQHandler(USART, 2, 2) // USART2 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART3
UART_IRQHandler(USART, 3, 3) // USART3 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART4
UART_IRQHandler(UART, 4, 4)  // UART4 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART5
UART_IRQHandler(UART, 5, 5)  // UART5 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART6
UART_IRQHandler(USART, 6, 6) // USART6 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART7

UART_IRQHandler(UART, 7, 7)  // UART7 Rx/Tx IRQ Handler
#endif

#ifdef USE_UART8
UART_IRQHandler(UART, 8, 8)  // UART8 Rx/Tx IRQ Handler
#endif
