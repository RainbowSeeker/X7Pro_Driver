// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/6.
//

#include "drv_spi.h"
#include "hal/spi/spi.h"
#include "hal/dma/dma.h"
#include "stm32h7xx.h"
#include "driver/io.h"
#include "board_config.h"
#include "drv_dma.h"
#include "nvic.h"

#define SPI_TIMEOUT     5

struct stm32_spi_bus
{
    struct spi_bus parent;
    SPI_TypeDef *instance;
    struct spi_configuration config;
#ifdef SPI_USE_DMA
    struct dma_device *dma_tx;
    struct dma_device *dma_rx;
    struct {
        bool dma_release;
        uint8_t *recv_buf;
        size_t len;
    };
#endif
};


static uint32_t spi_cal_prescaler(uint16_t divisor)
{
    size_t i = 1;
    while (divisor > i)
    {
        i *= 2;
    }
    divisor = i;

    const uint32_t baudRatePrescaler[8] = {
            LL_SPI_BAUDRATEPRESCALER_DIV2,
            LL_SPI_BAUDRATEPRESCALER_DIV4,
            LL_SPI_BAUDRATEPRESCALER_DIV8,
            LL_SPI_BAUDRATEPRESCALER_DIV16,
            LL_SPI_BAUDRATEPRESCALER_DIV32,
            LL_SPI_BAUDRATEPRESCALER_DIV64,
            LL_SPI_BAUDRATEPRESCALER_DIV128,
            LL_SPI_BAUDRATEPRESCALER_DIV256,
    };
    int prescalerIndex = ffs(divisor) - 2; // prescaler begins at "/2"

    return baudRatePrescaler[prescalerIndex];
}

/**
 * @brief Configure spi device
 *
 * @param device SPI device
 * @param configuration SPI device configuration
 * @return err_t E_OK for success
 */
static err_t configure(struct spi_device *device,
                       struct spi_configuration *config)
{
    struct stm32_spi_bus *stm32_spi_bus = (struct stm32_spi_bus *) device->bus;
    SPI_TypeDef *instance = stm32_spi_bus->instance;

    if (stm32_spi_bus->config.data_width != config->data_width)
    {
        LL_SPI_SetDataWidth(instance,
                            (config->data_width > 8) ? LL_SPI_DATAWIDTH_16BIT : LL_SPI_DATAWIDTH_8BIT);
        stm32_spi_bus->config.data_width = config->data_width;
    }

    if (stm32_spi_bus->config.mode != config->mode)
    {
        /* CPOL */
        LL_SPI_SetClockPolarity(instance,
                                (config->mode & SPI_CPOL) ? LL_SPI_POLARITY_HIGH : LL_SPI_POLARITY_LOW);

        /* CPHA */
        LL_SPI_SetClockPhase(instance,
                             (config->mode & SPI_CPHA) ? LL_SPI_PHASE_2EDGE : LL_SPI_PHASE_1EDGE);

        /* MSB or LSB */
        LL_SPI_SetTransferBitOrder(instance,
                                   (config->mode & SPI_MSB) ? LL_SPI_MSB_FIRST : LL_SPI_LSB_FIRST);

        stm32_spi_bus->config.mode = config->mode;
    }

    if (stm32_spi_bus->config.max_hz != config->max_hz)
    {
        uint32_t PCLK;
        LL_RCC_ClocksTypeDef rcc_clocks;
        LL_RCC_GetSystemClocksFreq(&rcc_clocks);
        if (instance == SPI2 || instance == SPI3)
        {
            PCLK = rcc_clocks.PCLK1_Frequency;
        }
        else
        {
            PCLK = rcc_clocks.PCLK2_Frequency;
        }
        /* set baudrate */
        LL_SPI_SetBaudRatePrescaler(instance, spi_cal_prescaler(PCLK / config->max_hz));

        stm32_spi_bus->config.max_hz = config->max_hz;
    }
    return E_OK;
}



/**
 * @brief SPI transfer function
 *
 * @param device SPI device instance
 * @param message SPI message to be transfered
 * @return uint32_t bytes have been transfered
 */
static err_t transfer(struct spi_device *device, struct spi_message *message)
{
    struct stm32_spi_bus *stm32_spi_bus = (struct stm32_spi_bus *) device->bus;
    struct spi_configuration *config = &device->config;
    SPI_TypeDef *instance = stm32_spi_bus->instance;
    io_t cs_io = *(io_t *) device->parent.user_data;

    if (device->bus->owner != device)
    {
        /* not the same owner as current, re-configure SPI bus */
        configure(device, &device->config);
        /* set SPI bus owner */
        device->bus->owner = device;
    }

#ifdef SPI_USE_DMA
    if (message->len >= DMA_THRESHOLD)
    {
        struct dma_elm elm_tx;
        struct dma_elm elm_rx;
        dma_get_elm(stm32_spi_bus->dma_tx->stream, &elm_tx);
        dma_get_elm(stm32_spi_bus->dma_rx->stream, &elm_rx);

            // Check if RX data can be DMAed
        if (!((message->recv_buf) && (elm_rx.base == BDMA ? (!IS_SRAM4(message->recv_buf)) : (!IS_AXI_SRAM(message->recv_buf)))) &&
            // Check if TX data can be DMAed
            !((message->send_buf) && (elm_tx.base == BDMA ? (!IS_SRAM4(message->send_buf)) : (!IS_AXI_SRAM(message->send_buf)))) &&
            light_device_open(&stm32_spi_bus->dma_tx->parent, DEVICE_OFLAG_OPEN) == E_OK &&
            light_device_open(&stm32_spi_bus->dma_rx->parent, DEVICE_OFLAG_OPEN) == E_OK)
        {
            // Intialize the init structures for the first transfer
            if (elm_tx.base == BDMA)
            {
                STATIC_BDMA_DATA_AUTO uint8_t dummyTxByte = 0xff;
                STATIC_BDMA_DATA_AUTO uint8_t dummyRxByte;

                if (message->send_buf)
                {
                    // Flush the D cache to ensure the data to be written is in main memory
                    scb_flush_dcache((void *) message->send_buf, message->len);

                    LL_BDMA_SetMemoryAddress(elm_tx.base, elm_tx.stream, (uint32_t) message->send_buf);
                    LL_BDMA_SetMemoryIncMode(elm_tx.base, elm_tx.stream, LL_BDMA_MEMORY_INCREMENT);
                }
                else
                {
                    LL_BDMA_SetMemoryAddress(elm_tx.base, elm_tx.stream, (uint32_t) &dummyTxByte);
                    LL_BDMA_SetMemoryIncMode(elm_tx.base, elm_tx.stream, 0);
                }
                LL_BDMA_SetDataLength(elm_tx.base, elm_tx.stream, message->len);

                if (message->recv_buf)
                {
                    scb_flush_invalidate_dcache(message->recv_buf, message->len);

                    LL_BDMA_SetMemoryAddress(elm_rx.base, elm_rx.stream, (uint32_t) message->recv_buf);
                    LL_BDMA_SetMemoryIncMode(elm_rx.base, elm_rx.stream, LL_BDMA_MEMORY_INCREMENT);
                }
                else
                {
                    LL_BDMA_SetMemoryAddress(elm_rx.base, elm_rx.stream, (uint32_t) &dummyRxByte);
                    LL_BDMA_SetMemoryIncMode(elm_rx.base, elm_rx.stream, 0);
                }
                LL_BDMA_SetDataLength(elm_rx.base, elm_rx.stream, message->len);
            }
            else
            {
                STATIC_DMA_DATA_AUTO uint8_t dummyTxByte = 0xff;
                STATIC_DMA_DATA_AUTO uint8_t dummyRxByte;

                if (message->send_buf)
                {
                    // Flush the D cache to ensure the data to be written is in main memory
                    scb_flush_dcache((void *) message->send_buf, message->len);

                    LL_DMA_SetMemoryAddress(elm_tx.base, elm_tx.stream, (uint32_t) message->send_buf);
                    LL_DMA_SetMemoryIncMode(elm_tx.base, elm_tx.stream, LL_DMA_MEMORY_INCREMENT);
                }
                else
                {
                    LL_DMA_SetMemoryAddress(elm_tx.base, elm_tx.stream, (uint32_t) &dummyTxByte);
                    LL_DMA_SetMemoryIncMode(elm_tx.base, elm_tx.stream, LL_DMA_MEMORY_NOINCREMENT);
                }
                LL_DMA_SetDataLength(elm_tx.base, elm_tx.stream, message->len);

                if (message->recv_buf)
                {
                    scb_flush_invalidate_dcache(message->recv_buf, message->len);

                    LL_DMA_SetMemoryAddress(elm_rx.base, elm_rx.stream, (uint32_t) message->recv_buf);
                    LL_DMA_SetMemoryIncMode(elm_rx.base, elm_rx.stream, LL_DMA_MEMORY_INCREMENT);
                }
                else
                {
                    LL_DMA_SetMemoryAddress(elm_rx.base, elm_rx.stream, (uint32_t) &dummyRxByte);
                    LL_DMA_SetMemoryIncMode(elm_rx.base, elm_rx.stream, LL_DMA_MEMORY_NOINCREMENT);
                }
                LL_DMA_SetDataLength(elm_rx.base, elm_rx.stream, message->len);
            }

            /* take CS */
            if (message->cs_take)
            {
                io_set(cs_io, IO_LOW);
            }

            // Use the correct callback argument
            stm32_spi_bus->parent.parent.user_data = device;
            stm32_spi_bus->dma_release = message->cs_release;
            stm32_spi_bus->recv_buf = message->recv_buf;
            stm32_spi_bus->len = message->len;

            //start transfer
            LL_SPI_SetTransferSize(instance, message->len);

            /* Use the Rx interrupt as this occurs once the SPI operation is complete whereas the Tx interrupt
             * occurs earlier when the Tx FIFO is empty, but the SPI operation is still in progress
             */
            if (elm_tx.base == BDMA)
            {
                // Clear transfer flags
                LL_EX_DMA_ClearFlag(stm32_spi_bus->dma_tx->stream, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
                LL_EX_DMA_ClearFlag(stm32_spi_bus->dma_rx->stream, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);

                LL_BDMA_EnableIT_TC(elm_rx.base, elm_rx.stream);

                LL_BDMA_EnableChannel(elm_tx.base, elm_tx.stream);
                LL_BDMA_EnableChannel(elm_rx.base, elm_rx.stream);
            }
            else
            {
                // Clear transfer flags
                LL_EX_DMA_ClearFlag(stm32_spi_bus->dma_tx->stream, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
                LL_EX_DMA_ClearFlag(stm32_spi_bus->dma_rx->stream, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);

                LL_DMA_EnableIT_TC(elm_rx.base, elm_rx.stream);

                LL_DMA_EnableStream(elm_tx.base, elm_tx.stream);
                LL_DMA_EnableStream(elm_rx.base, elm_rx.stream);
            }

            LL_SPI_EnableDMAReq_TX(instance);
            LL_SPI_EnableDMAReq_RX(instance);
            LL_SPI_Enable(instance);
            LL_SPI_StartMasterTransfer(instance);

            return E_BUSY;
        }
    }
#endif
    {
        // Manually work through the segment list performing a transfer for each
        /* take CS */
        if (message->cs_take)
        {
            io_set(cs_io, IO_LOW);
        }
        base_t level = os_hw_interrupt_disable();
        uint32_t init_tick = os_tick_get();

        LL_SPI_SetTransferSize(instance, message->len);
        LL_SPI_Enable(instance);
        LL_SPI_StartMasterTransfer(instance);
        if (config->data_width <= 8)
        {
            const uint8_t *send_ptr = message->send_buf;
            uint8_t *recv_ptr = message->recv_buf;

            while (message->len--)
            {
                while (!LL_SPI_IsActiveFlag_TXP(instance))
                {
                    if (os_tick_get() > init_tick + SPI_TIMEOUT)
                    {
                        return E_TIMEOUT;
                    }
                }
                uint8_t b = send_ptr ? *(send_ptr++) : 0xFF;
                LL_SPI_TransmitData8(instance, b);

                while (!LL_SPI_IsActiveFlag_RXP(instance))
                {
                    if (os_tick_get() > init_tick + SPI_TIMEOUT)
                    {
                        return E_TIMEOUT;
                    }
                }
                b = LL_SPI_ReceiveData8(instance);
                if (recv_ptr)
                {
                    *(recv_ptr++) = b;
                }
            }
        }
        else if (config->data_width <= 16)
        {
            uint16_t *send_ptr = (uint16_t *) message->send_buf;
            uint16_t *recv_ptr = (uint16_t *) message->recv_buf;

            while (message->len--)
            {
                while (!LL_SPI_IsActiveFlag_TXP(instance))
                {
                    if (os_tick_get() > init_tick + SPI_TIMEOUT)
                    {
                        return E_TIMEOUT;
                    }
                }
                uint16_t b = send_ptr ? *(send_ptr++) : 0xFF;
                LL_SPI_TransmitData16(instance, b);

                while (!LL_SPI_IsActiveFlag_RXP(instance))
                {
                    if (os_tick_get() > init_tick + SPI_TIMEOUT)
                    {
                        return E_TIMEOUT;
                    }
                }
                b = LL_SPI_ReceiveData16(instance);
                if (recv_ptr)
                {
                    *(recv_ptr++) = b;
                }
            }
        }

        while (!LL_SPI_IsActiveFlag_EOT(instance));
        LL_SPI_ClearFlag_TXTF(instance);
        LL_SPI_Disable(instance);
        os_hw_interrupt_enable(level);

        /* release CS */
        if (message->cs_release)
        {
            io_set(cs_io, IO_HIGH);
        }

        return E_OK;
    }
}



static struct spi_ops stm32_spi_ops = {
                transfer
};

static void SPI_PeriphCLKConfig(SPI_TypeDef *instance)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (instance == SPI1 || instance == SPI2 || instance == SPI3)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI123;
        PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    }
    else if (instance == SPI4 || instance == SPI5)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI45;
        PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    }
    else if (instance == SPI6)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI6;
        PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_D3PCLK1;
    }
    else ASSERT(0);
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        return;
    }
}

static LL_SPI_InitTypeDef defaultInit =
        {
                .TransferDirection = LL_SPI_FULL_DUPLEX,
                .Mode = LL_SPI_MODE_MASTER,
                .DataWidth = LL_SPI_DATAWIDTH_8BIT,
                .NSS = LL_SPI_NSS_SOFT,
                .BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8,
                .BitOrder = LL_SPI_MSB_FIRST,
                .CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE,
                .ClockPolarity = LL_SPI_POLARITY_HIGH,
                .ClockPhase = LL_SPI_PHASE_2EDGE,
        };


static void spi_dma_preinit(SPI_TypeDef *instance, void *dma_stream_tx, void *dma_stream_rx, uint32_t request)
{
    struct dma_elm elm_tx;
    struct dma_elm elm_rx;
    dma_get_elm(dma_stream_tx, &elm_tx);
    dma_get_elm(dma_stream_rx, &elm_rx);

    LL_EX_DMA_ResetStream(dma_stream_tx);
    LL_EX_DMA_ResetStream(dma_stream_rx);

    if (elm_tx.base == BDMA)
    {
        __HAL_RCC_BDMA_CLK_ENABLE();
        LL_BDMA_SetPeriphRequest(elm_tx.base, elm_tx.stream, request);
        LL_BDMA_SetMode(elm_tx.base, elm_tx.stream, LL_BDMA_MODE_NORMAL);
        LL_BDMA_SetDataTransferDirection(elm_tx.base, elm_tx.stream, LL_BDMA_DIRECTION_MEMORY_TO_PERIPH);
        LL_BDMA_SetPeriphAddress(elm_tx.base, elm_tx.stream, (uint32_t) &instance->TXDR);
        LL_BDMA_SetChannelPriorityLevel(elm_tx.base, elm_tx.stream, LL_BDMA_PRIORITY_LOW);
        LL_BDMA_SetPeriphIncMode(elm_tx.base, elm_tx.stream, LL_BDMA_PERIPH_NOINCREMENT);
        LL_BDMA_SetPeriphSize(elm_tx.base, elm_tx.stream, LL_BDMA_PDATAALIGN_BYTE);
        LL_BDMA_SetMemorySize(elm_tx.base, elm_tx.stream, LL_BDMA_PDATAALIGN_BYTE);


        LL_BDMA_SetPeriphRequest(elm_rx.base, elm_rx.stream, request - 1);
        LL_BDMA_SetMode(elm_rx.base, elm_rx.stream, LL_BDMA_MODE_NORMAL);
        LL_BDMA_SetDataTransferDirection(elm_rx.base, elm_rx.stream, LL_BDMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_BDMA_SetPeriphAddress(elm_rx.base, elm_rx.stream, (uint32_t) &instance->RXDR);
        LL_BDMA_SetChannelPriorityLevel(elm_rx.base, elm_rx.stream, LL_BDMA_PRIORITY_LOW);
        LL_BDMA_SetPeriphIncMode(elm_rx.base, elm_rx.stream, LL_BDMA_PERIPH_NOINCREMENT);
        LL_BDMA_SetPeriphSize(elm_rx.base, elm_rx.stream, LL_BDMA_PDATAALIGN_BYTE);
        LL_BDMA_SetMemorySize(elm_rx.base, elm_rx.stream, LL_BDMA_PDATAALIGN_BYTE);
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();
        LL_DMA_SetPeriphRequest(elm_tx.base, elm_tx.stream, request);
        LL_DMA_SetMode(elm_tx.base, elm_tx.stream, LL_DMA_MODE_NORMAL);
        LL_DMA_SetDataTransferDirection(elm_tx.base, elm_tx.stream, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
        LL_DMA_SetPeriphAddress(elm_tx.base, elm_tx.stream, (uint32_t) &instance->TXDR);
        LL_DMA_SetStreamPriorityLevel(elm_tx.base, elm_tx.stream, LL_DMA_PRIORITY_LOW);
        LL_DMA_SetPeriphIncMode(elm_tx.base, elm_tx.stream, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetPeriphSize(elm_tx.base, elm_tx.stream, LL_DMA_PDATAALIGN_BYTE);
        LL_DMA_SetMemorySize(elm_tx.base, elm_tx.stream, LL_DMA_PDATAALIGN_BYTE);


        LL_DMA_SetPeriphRequest(elm_rx.base, elm_rx.stream, request - 1);
        LL_DMA_SetMode(elm_rx.base, elm_rx.stream, LL_DMA_MODE_NORMAL);
        LL_DMA_SetDataTransferDirection(elm_rx.base, elm_rx.stream, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_DMA_SetPeriphAddress(elm_rx.base, elm_rx.stream, (uint32_t) &instance->RXDR);
        LL_DMA_SetStreamPriorityLevel(elm_rx.base, elm_rx.stream, LL_DMA_PRIORITY_LOW);
        LL_DMA_SetPeriphIncMode(elm_rx.base, elm_rx.stream, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetPeriphSize(elm_rx.base, elm_rx.stream, LL_DMA_PDATAALIGN_BYTE);
        LL_DMA_SetMemorySize(elm_rx.base, elm_rx.stream, LL_DMA_PDATAALIGN_BYTE);
    }
}

static void spi_dma_callback(uint32_t user_data)
{
    struct stm32_spi_bus *stm32_spi_bus = (struct stm32_spi_bus *)user_data;

    struct spi_device *device = (struct spi_device *)stm32_spi_bus->parent.parent.user_data;
    io_t cs_io = *(io_t *) device->parent.user_data;

    if (!device) return;

    if (stm32_spi_bus->dma_release)
    {
        io_set(cs_io, IO_HIGH);
    }

    struct dma_elm elm_tx;
    struct dma_elm elm_rx;
    dma_get_elm(stm32_spi_bus->dma_tx->stream, &elm_tx);
    dma_get_elm(stm32_spi_bus->dma_rx->stream, &elm_rx);

    if (elm_tx.base == BDMA)
    {
        LL_BDMA_DisableChannel(elm_rx.base, elm_rx.stream);
        LL_BDMA_DisableChannel(elm_tx.base, elm_tx.stream);
        LL_EX_DMA_ClearFlag(stm32_spi_bus->dma_rx->stream, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
    }
    else
    {
        // Disable the DMA engine and SPI interface
        LL_DMA_DisableStream(elm_rx.base, elm_rx.stream);
        LL_DMA_DisableStream(elm_tx.base, elm_tx.stream);
        LL_EX_DMA_ClearFlag(stm32_spi_bus->dma_rx->stream, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
    }

    LL_SPI_DisableDMAReq_TX(stm32_spi_bus->instance);
    LL_SPI_DisableDMAReq_RX(stm32_spi_bus->instance);
    LL_SPI_ClearFlag_TXTF(stm32_spi_bus->instance);
    LL_SPI_Disable(stm32_spi_bus->instance);


    if (stm32_spi_bus->recv_buf && !IS_DTCM(stm32_spi_bus->recv_buf))
    {
        // Invalidate the D cache covering the area into which data has been read
        scb_invalidate_dcache(stm32_spi_bus->recv_buf, stm32_spi_bus->len);
    }

    light_device_close(&stm32_spi_bus->dma_tx->parent);
    light_device_close(&stm32_spi_bus->dma_rx->parent);
    /* unlock mutex */
    os_mutex_release(device->bus->lock);
}


/**
 *
 * @param stm32_spi
 * @param spi_bus_name
 * @param spi_dma_name1
 * @param spi_dma_name2
 * @return
 */
static err_t stm32_spi_register(struct stm32_spi_bus *stm32_spi,
                                const char *spi_bus_name,
                                const char *spi_tx_dma_name,
                                const char *spi_rx_dma_name)
{
    err_t ret = E_OK;
    uint32_t request;

    if (MATCH(spi_bus_name, "spi1"))
    {
        stm32_spi->instance = SPI1;
        SPI_PeriphCLKConfig(stm32_spi->instance);
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();

        /* SPI1 configure */
        io_t sck = {.port = GPIOG, .pin = GPIO_PIN_11};
        io_t miso = {.port = GPIOA, .pin = GPIO_PIN_6};
        io_t mosi = {.port = GPIOD, .pin = GPIO_PIN_7};
        /*  SPI1 GPIO Configuration
            PD7   ------> SPI1_MOSI
            PG11  ------> SPI1_SCK
            PA6   ------> SPI1_MISO */
        io_init(sck, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI1);
        io_init(miso, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI1);
        io_init(mosi, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI1);
        request = DMA_REQUEST_SPI1_TX;
    }
    else if (MATCH(spi_bus_name, "spi2"))
    {
        stm32_spi->instance = SPI2;
        SPI_PeriphCLKConfig(stm32_spi->instance);
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();

        /* SPI2 configure */
        io_t sck = {.port = GPIOI, .pin = GPIO_PIN_1};
        io_t miso = {.port = GPIOI, .pin = GPIO_PIN_2};
        io_t mosi = {.port = GPIOI, .pin = GPIO_PIN_3};
        /*  SPI2 GPIO Configuration
            PI3   ------> SPI2_MOSI
            PI1   ------> SPI2_SCK
            PI2   ------> SPI2_MISO */
        io_init(sck, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI2);
        io_init(miso, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI2);
        io_init(mosi, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI2);
        request = DMA_REQUEST_SPI2_TX;
    }
    else if (MATCH(spi_bus_name, "spi3"))
    {
        stm32_spi->instance = SPI3;
        SPI_PeriphCLKConfig(stm32_spi->instance);
        /* Peripheral clock enable */
        __HAL_RCC_SPI3_CLK_ENABLE();
        request = DMA_REQUEST_SPI3_TX;
        ASSERT(0);
    }
    else if (MATCH(spi_bus_name, "spi4"))
    {
        stm32_spi->instance = SPI4;
        SPI_PeriphCLKConfig(stm32_spi->instance);
        /* Peripheral clock enable */
        __HAL_RCC_SPI4_CLK_ENABLE();

        /* SPI4 configure */
        io_t sck = {.port = GPIOE, .pin = GPIO_PIN_2};
        io_t miso = {.port = GPIOE, .pin = GPIO_PIN_13};
        io_t mosi = {.port = GPIOE, .pin = GPIO_PIN_6};
        /*  SPI4 GPIO Configuration
            PE6   ------> SPI4_MOSI
            PE2   ------> SPI4_SCK
            PE13  ------> SPI4_MISO */
        io_init(sck, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI4);
        io_init(miso, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI4);
        io_init(mosi, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI4);
        request = DMA_REQUEST_SPI4_TX;
    }
    else if (MATCH(spi_bus_name, "spi5"))
    {
        stm32_spi->instance = SPI5;
        SPI_PeriphCLKConfig(stm32_spi->instance);
        /* Peripheral clock enable */
        __HAL_RCC_SPI5_CLK_ENABLE();
        request = DMA_REQUEST_SPI5_TX;
        ASSERT(0);
    }
    else if (MATCH(spi_bus_name, "spi6"))
    {
        stm32_spi->instance = SPI6;
        SPI_PeriphCLKConfig(stm32_spi->instance);
        /* Peripheral clock enable */
        __HAL_RCC_SPI6_CLK_ENABLE();

        /* SPI6 configure */
        io_t sck = {.port = GPIOG, .pin = GPIO_PIN_13};
        io_t miso = {.port = GPIOG, .pin = GPIO_PIN_12};
        io_t mosi = {.port = GPIOA, .pin = GPIO_PIN_7};
        /*  SPI6 GPIO Configuration
            PA7   ------> SPI6_MOSI
            PG13  ------> SPI6_SCK
            PG12  ------> SPI6_MISO */
        io_init(sck, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI6);
        io_init(miso, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF5_SPI6);
        io_init(mosi, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF8_SPI6);
        request = BDMA_REQUEST_SPI6_TX;
    }
    else
    {
        return ENOSYS;
    }

    LL_SPI_Disable(stm32_spi->instance);
    LL_SPI_DeInit(stm32_spi->instance);
    // Prevent glitching when SPI is disabled
    LL_SPI_EnableGPIOControl(stm32_spi->instance);
    LL_SPI_DisableNSSPulseMgt(stm32_spi->instance);
    LL_SPI_SetStandard(stm32_spi->instance, LL_SPI_PROTOCOL_MOTOROLA);
    LL_SPI_SetFIFOThreshold(stm32_spi->instance, LL_SPI_FIFO_TH_01DATA);
    LL_SPI_Init(stm32_spi->instance, &defaultInit);

    /* register physical dma dev */
    if (spi_tx_dma_name && spi_rx_dma_name)
    {
        stm32_spi->dma_tx = LL_DMA_DeviceGetByName(spi_tx_dma_name);
        ret |= hal_dma_register(stm32_spi->dma_tx, spi_tx_dma_name, DEVICE_FLAG_WRONLY);

        stm32_spi->dma_rx = LL_DMA_DeviceGetByName(spi_rx_dma_name);
        ret |= hal_dma_register(stm32_spi->dma_rx, spi_rx_dma_name, DEVICE_FLAG_RDONLY);

        spi_dma_preinit(stm32_spi->instance, stm32_spi->dma_tx->stream, stm32_spi->dma_rx->stream, request);

        dma_configure_irq(stm32_spi->dma_rx->stream, spi_dma_callback, NVIC_PRIO_SPI_DMA, (uint32_t)stm32_spi);
    }
    ret |= spi_bus_register(&stm32_spi->parent, spi_bus_name, &stm32_spi_ops);
    return ret;
}

static struct stm32_spi_bus stm32_spi1;
static struct stm32_spi_bus stm32_spi2;
static struct stm32_spi_bus stm32_spi4;
static struct stm32_spi_bus stm32_spi6;

/**
 * @brief Initialize spi bus and device
 *
 * @return err_t E_OK for success
 */
err_t drv_spi_init(void)
{
    /* register SPI bus */
    ERROR_TRY(stm32_spi_register(&stm32_spi1,
                                 "spi1",
                                 "dma1_stream0",
                                 "dma1_stream1"));

    ERROR_TRY(stm32_spi_register(&stm32_spi2,
                                 "spi2",
                                 "dma1_stream2",
                                 "dma1_stream3"));

    ERROR_TRY(stm32_spi_register(&stm32_spi4,
                                 "spi4",
                                 "dma1_stream4",
                                 "dma1_stream5"));

    ERROR_TRY(stm32_spi_register(&stm32_spi6,
                                 "spi6",
                                 "bdma_channel0",
                                 "bdma_channel1"));
    return E_OK;
}
