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
#define SPI_MAX_NUM     6




struct stm32_spi_bus {
    struct spi_bus parent;
    SPI_TypeDef *instance;
    struct spi_configuration config;
#ifdef SPI_USE_DMA
    struct dma_device *dma_tx;
    struct dma_device *dma_rx;
    struct {
        uint8_t *recv_buf;
        size_t  len;
        uint8_t cs_release;
    }dma_msg;
#endif
};


static uint32_t spi_cal_prescaler(uint16_t divisor) {
    size_t i = 1;
    while (divisor > i) {
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
                       struct spi_configuration *config) {
    struct stm32_spi_bus *bus = (struct stm32_spi_bus *) device->bus;
    SPI_TypeDef *instance = bus->instance;

    if (bus->config.data_width != config->data_width) {
        LL_SPI_SetDataWidth(instance,
                            (config->data_width > 8) ? LL_SPI_DATAWIDTH_16BIT : LL_SPI_DATAWIDTH_8BIT);
        bus->config.data_width = config->data_width;
    }

    if (bus->config.mode != config->mode) {
        /* CPOL */
        LL_SPI_SetClockPolarity(instance,
                                (config->mode & SPI_CPOL) ? LL_SPI_POLARITY_HIGH : LL_SPI_POLARITY_LOW);

        /* CPHA */
        LL_SPI_SetClockPhase(instance,
                             (config->mode & SPI_CPHA) ? LL_SPI_PHASE_2EDGE : LL_SPI_PHASE_1EDGE);

        /* MSB or LSB */
        LL_SPI_SetTransferBitOrder(instance,
                                   (config->mode & SPI_MSB) ? LL_SPI_MSB_FIRST : LL_SPI_LSB_FIRST);

        bus->config.mode = config->mode;
    }

    if (bus->config.max_hz != config->max_hz) {
        uint32_t PCLK;
        LL_RCC_ClocksTypeDef rcc_clocks;
        LL_RCC_GetSystemClocksFreq(&rcc_clocks);
        if (instance == SPI2 || instance == SPI3) {
            PCLK = rcc_clocks.PCLK1_Frequency;
        } else {
            PCLK = rcc_clocks.PCLK2_Frequency;
        }
        /* set baudrate */
        LL_SPI_SetBaudRatePrescaler(instance, spi_cal_prescaler(PCLK / config->max_hz));

        bus->config.max_hz = config->max_hz;
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
static err_t transfer(struct spi_device *device, struct spi_message *message) {
    struct stm32_spi_bus *bus = (struct stm32_spi_bus *) device->bus;
    struct spi_configuration *config = &device->config;
    SPI_TypeDef *instance = bus->instance;
    io_tag cs = *(io_tag *) device->parent.user_data;

    if (device->bus->owner != device) {
        /* not the same owner as current, re-configure SPI bus */
        configure(device, &device->config);
        /* set SPI bus owner */
        device->bus->owner = device;
    }

#ifdef SPI_USE_DMA
    if (message->len >= DMA_THRESHOLD) {
        struct dma_device *dma_tx = bus->dma_tx;
        struct dma_device *dma_rx = bus->dma_rx;
        // Check if RX data can be DMAed
        if (!((message->recv_buf) &&
              (dma_rx->instance == BDMA ? (!IS_SRAM4(message->recv_buf)) : (!IS_AXI_SRAM(message->recv_buf)))) &&
            // Check if TX data can be DMAed
            !((message->send_buf) &&
              (dma_tx->instance == BDMA ? (!IS_SRAM4(message->send_buf)) : (!IS_AXI_SRAM(message->send_buf)))) &&
            device_open(&bus->dma_tx->parent, DEVICE_OFLAG_OPEN) == E_OK &&
            device_open(&bus->dma_rx->parent, DEVICE_OFLAG_OPEN) == E_OK) {
            // Intialize the init structures for the first transfer
            if (dma_tx->instance == BDMA) {
                STATIC_BDMA_DATA_AUTO uint8_t dummyTxByte = 0xff;
                STATIC_BDMA_DATA_AUTO uint8_t dummyRxByte;

                if (message->send_buf) {
                    // Flush the D cache to ensure the data to be written is in main memory
                    scb_flush_dcache((void *) message->send_buf, message->len);

                    LL_BDMA_SetMemoryAddress(dma_tx->instance, dma_tx->stream, (uint32_t) message->send_buf);
                    LL_BDMA_SetMemoryIncMode(dma_tx->instance, dma_tx->stream, LL_BDMA_MEMORY_INCREMENT);
                } else {
                    LL_BDMA_SetMemoryAddress(dma_tx->instance, dma_tx->stream, (uint32_t) &dummyTxByte);
                    LL_BDMA_SetMemoryIncMode(dma_tx->instance, dma_tx->stream, 0);
                }
                LL_BDMA_SetDataLength(dma_tx->instance, dma_tx->stream, message->len);

                if (message->recv_buf) {
                    scb_flush_invalidate_dcache(message->recv_buf, message->len);

                    LL_BDMA_SetMemoryAddress(dma_rx->instance, dma_rx->stream, (uint32_t) message->recv_buf);
                    LL_BDMA_SetMemoryIncMode(dma_rx->instance, dma_rx->stream, LL_BDMA_MEMORY_INCREMENT);
                } else {
                    LL_BDMA_SetMemoryAddress(dma_rx->instance, dma_rx->stream, (uint32_t) &dummyRxByte);
                    LL_BDMA_SetMemoryIncMode(dma_rx->instance, dma_rx->stream, 0);
                }
                LL_BDMA_SetDataLength(dma_rx->instance, dma_rx->stream, message->len);
            } else {
                STATIC_DMA_DATA_AUTO uint8_t dummyTxByte = 0xff;
                STATIC_DMA_DATA_AUTO uint8_t dummyRxByte;

                if (message->send_buf) {
                    // Flush the D cache to ensure the data to be written is in main memory
                    scb_flush_dcache((void *) message->send_buf, message->len);

                    LL_DMA_SetMemoryAddress(dma_tx->instance, dma_tx->stream, (uint32_t) message->send_buf);
                    LL_DMA_SetMemoryIncMode(dma_tx->instance, dma_tx->stream, LL_DMA_MEMORY_INCREMENT);
                } else {
                    LL_DMA_SetMemoryAddress(dma_tx->instance, dma_tx->stream, (uint32_t) &dummyTxByte);
                    LL_DMA_SetMemoryIncMode(dma_tx->instance, dma_tx->stream, LL_DMA_MEMORY_NOINCREMENT);
                }
                LL_DMA_SetDataLength(dma_tx->instance, dma_tx->stream, message->len);

                if (message->recv_buf) {
                    scb_flush_invalidate_dcache(message->recv_buf, message->len);

                    LL_DMA_SetMemoryAddress(dma_rx->instance, dma_rx->stream, (uint32_t) message->recv_buf);
                    LL_DMA_SetMemoryIncMode(dma_rx->instance, dma_rx->stream, LL_DMA_MEMORY_INCREMENT);
                } else {
                    LL_DMA_SetMemoryAddress(dma_rx->instance, dma_rx->stream, (uint32_t) &dummyRxByte);
                    LL_DMA_SetMemoryIncMode(dma_rx->instance, dma_rx->stream, LL_DMA_MEMORY_NOINCREMENT);
                }
                LL_DMA_SetDataLength(dma_rx->instance, dma_rx->stream, message->len);
            }

            /* take CS */
            if (message->cs_take) {
                io_set(cs, IO_LOW);
            }

            // Use the correct callback argument
            bus->parent.parent.user_data = device;
            bus->dma_msg.recv_buf = message->recv_buf;
            bus->dma_msg.len = message->len;
            bus->dma_msg.cs_release = message->cs_release;

            //start transfer
            LL_SPI_SetTransferSize(instance, message->len);

            /* Use the Rx interrupt as this occurs once the SPI operation is complete whereas the Tx interrupt
             * occurs earlier when the Tx FIFO is empty, but the SPI operation is still in progress
             */
            if (dma_tx->instance == BDMA) {
                // Clear transfer flags
                LL_EX_DMA_ClearFlag(dma_tx, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
                LL_EX_DMA_ClearFlag(dma_rx, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);

                LL_BDMA_EnableIT_TC(dma_rx->instance, dma_rx->stream);

                LL_BDMA_EnableChannel(dma_tx->instance, dma_tx->stream);
                LL_BDMA_EnableChannel(dma_rx->instance, dma_rx->stream);
            } else {
                // Clear transfer flags
                LL_EX_DMA_ClearFlag(dma_tx, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
                LL_EX_DMA_ClearFlag(dma_rx, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);

                LL_DMA_EnableIT_TC(dma_rx->instance, dma_rx->stream);

                LL_DMA_EnableStream(dma_tx->instance, dma_tx->stream);
                LL_DMA_EnableStream(dma_rx->instance, dma_rx->stream);
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
        if (message->cs_take) {
            io_set(cs, IO_LOW);
        }

        LL_SPI_SetTransferSize(instance, message->len);
        LL_SPI_Enable(instance);
        LL_SPI_StartMasterTransfer(instance);
        if (config->data_width <= 8) {
            const uint8_t *send_ptr = message->send_buf;
            uint8_t *recv_ptr = message->recv_buf;

            while (message->len--) {
                while (!LL_SPI_IsActiveFlag_TXP(instance));
                uint8_t b = send_ptr ? *(send_ptr++) : 0xFF;
                LL_SPI_TransmitData8(instance, b);

                while (!LL_SPI_IsActiveFlag_RXP(instance));
                b = LL_SPI_ReceiveData8(instance);
                if (recv_ptr) {
                    *(recv_ptr++) = b;
                }
            }
        } else if (config->data_width <= 16) {
            uint16_t *send_ptr = (uint16_t *) message->send_buf;
            uint16_t *recv_ptr = (uint16_t *) message->recv_buf;

            while (message->len--) {
                while (!LL_SPI_IsActiveFlag_TXP(instance));
                uint16_t b = send_ptr ? *(send_ptr++) : 0xFF;
                LL_SPI_TransmitData16(instance, b);

                while (!LL_SPI_IsActiveFlag_RXP(instance));
                b = LL_SPI_ReceiveData16(instance);
                if (recv_ptr) {
                    *(recv_ptr++) = b;
                }
            }
        }

        while (!LL_SPI_IsActiveFlag_EOT(instance));
        LL_SPI_ClearFlag_TXTF(instance);
        LL_SPI_Disable(instance);

        /* release CS */
        if (message->cs_release) {
            io_set(cs, IO_HIGH);
        }

        return E_OK;
    }
}


static struct spi_ops stm32_spi_ops = {
        transfer
};

static void SPI_PeriphCLKConfig(SPI_TypeDef *instance) {
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (instance == SPI1 || instance == SPI2 || instance == SPI3) {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI123;
        PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    } else if (instance == SPI4 || instance == SPI5) {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI45;
        PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    } else if (instance == SPI6) {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI6;
        PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_D3PCLK1;
    } else ASSERT(0); //not handler yet.
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        return;
    }
}



static void spi_dma_callback(uint32_t user_data) {
    struct stm32_spi_bus *bus = (struct stm32_spi_bus *) user_data;

    struct spi_device *device = (struct spi_device *) bus->parent.parent.user_data;
    io_tag cs = *(io_tag *) device->parent.user_data;

    if (!device) return;

    if (bus->dma_msg.cs_release) {
        io_set(cs, IO_HIGH);
    }


    if (bus->dma_tx->instance == BDMA) {
        LL_BDMA_DisableChannel(bus->dma_rx->instance, bus->dma_rx->stream);
        LL_BDMA_DisableChannel(bus->dma_tx->instance, bus->dma_tx->stream);
        LL_EX_DMA_ClearFlag(bus->dma_rx, BDMA_IT_HTIF | BDMA_IT_TEIF | BDMA_IT_TCIF);
    } else {
        // Disable the DMA engine and SPI interface
        LL_DMA_DisableStream(bus->dma_rx->instance, bus->dma_rx->stream);
        LL_DMA_DisableStream(bus->dma_tx->instance, bus->dma_tx->stream);
        LL_EX_DMA_ClearFlag(bus->dma_rx, DMA_IT_HTIF | DMA_IT_TEIF | DMA_IT_TCIF);
    }

    LL_SPI_DisableDMAReq_TX(bus->instance);
    LL_SPI_DisableDMAReq_RX(bus->instance);
    LL_SPI_ClearFlag_TXTF(bus->instance);
    LL_SPI_Disable(bus->instance);


    if (bus->dma_msg.recv_buf && !IS_DTCM(bus->dma_msg.recv_buf)) {
        // Invalidate the D cache covering the area into which data has been read
        scb_invalidate_dcache(bus->dma_msg.recv_buf, bus->dma_msg.len);
    }

    device_close(&bus->dma_tx->parent);
    device_close(&bus->dma_rx->parent);
    /* unlock mutex */
    mutex_release(device->bus->lock);
}

static err_t stm32_spi_verify_name(const char *name, int *idx) {
    ASSERT(MATCH(name, "spi"));
    *idx = name[3] - '0';
    if (*idx > 0 && *idx <= SPI_MAX_NUM) {
        return E_OK;
    } else {
        *idx = -1;
        return E_INVAL;
    }
}

static struct {
    void *instance;
    io_tag mosi, miso, sck;
    uint8_t af1, af2, af3;
} spi_io_table[] = {
        /* spi 1 */
        {SPI1, PD7, PA6, PG11, GPIO_AF5_SPI1, GPIO_AF5_SPI1, GPIO_AF5_SPI1},
        /* spi 2 */
        {SPI2, PI3, PI2, PI1, GPIO_AF5_SPI2, GPIO_AF5_SPI2, GPIO_AF5_SPI2},
        /* spi 3 */
        {NULL},
        /* spi 4 */
        {SPI4, PE6, PE13, PE2, GPIO_AF5_SPI4, GPIO_AF5_SPI4, GPIO_AF5_SPI4},
        /* spi 5 */
        {NULL},
        /* spi 6 */
        {SPI6, PA7, PG12, PG13, GPIO_AF8_SPI6, GPIO_AF5_SPI6, GPIO_AF5_SPI6},
};

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

static void stm32_spi_init(struct stm32_spi_bus *bus, int idx) {
    /* Peripheral clock enable */
    switch (idx) {
        case 1:
            __HAL_RCC_SPI1_CLK_ENABLE();
            break;
        case 2:
            __HAL_RCC_SPI2_CLK_ENABLE();
            break;
        case 4:
            __HAL_RCC_SPI4_CLK_ENABLE();
            break;
        case 6:
            __HAL_RCC_SPI6_CLK_ENABLE();
            break;
        default:
            ASSERT(0);
    }

    bus->instance = spi_io_table[idx - 1].instance;
    SPI_PeriphCLKConfig(bus->instance);

    io_init(spi_io_table[idx - 1].mosi, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, spi_io_table[idx - 1].af1);
    io_init(spi_io_table[idx - 1].miso, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, spi_io_table[idx - 1].af2);
    io_init(spi_io_table[idx - 1].sck, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, spi_io_table[idx - 1].af3);

    LL_SPI_Disable(bus->instance);
    LL_SPI_DeInit(bus->instance);
    // Prevent glitching when SPI is disabled
    LL_SPI_EnableGPIOControl(bus->instance);
    LL_SPI_DisableNSSPulseMgt(bus->instance);
    LL_SPI_SetStandard(bus->instance, LL_SPI_PROTOCOL_MOTOROLA);
    LL_SPI_SetFIFOThreshold(bus->instance, LL_SPI_FIFO_TH_01DATA);
    LL_SPI_Init(bus->instance, &defaultInit);
}

static void stm32_spi_dma_init(SPI_TypeDef *instance, struct dma_device *dma_tx, struct dma_device *dma_rx) {
    uint32_t request;
    ASSERT(dma_get_request_by_instance(instance, &request) == E_OK);

    LL_EX_DMA_ResetStream(dma_tx);
    LL_EX_DMA_ResetStream(dma_rx);

    if (dma_tx->instance == BDMA) {
        __HAL_RCC_BDMA_CLK_ENABLE();
        LL_BDMA_SetPeriphRequest(dma_tx->instance, dma_tx->stream, request);
        LL_BDMA_SetMode(dma_tx->instance, dma_tx->stream, LL_BDMA_MODE_NORMAL);
        LL_BDMA_SetDataTransferDirection(dma_tx->instance, dma_tx->stream, LL_BDMA_DIRECTION_MEMORY_TO_PERIPH);
        LL_BDMA_SetPeriphAddress(dma_tx->instance, dma_tx->stream, (uint32_t) &instance->TXDR);
        LL_BDMA_SetChannelPriorityLevel(dma_tx->instance, dma_tx->stream, LL_BDMA_PRIORITY_LOW);
        LL_BDMA_SetPeriphIncMode(dma_tx->instance, dma_tx->stream, LL_BDMA_PERIPH_NOINCREMENT);
        LL_BDMA_SetPeriphSize(dma_tx->instance, dma_tx->stream, LL_BDMA_PDATAALIGN_BYTE);
        LL_BDMA_SetMemorySize(dma_tx->instance, dma_tx->stream, LL_BDMA_PDATAALIGN_BYTE);


        LL_BDMA_SetPeriphRequest(dma_rx->instance, dma_rx->stream, request - 1);
        LL_BDMA_SetMode(dma_rx->instance, dma_rx->stream, LL_BDMA_MODE_NORMAL);
        LL_BDMA_SetDataTransferDirection(dma_rx->instance, dma_rx->stream, LL_BDMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_BDMA_SetPeriphAddress(dma_rx->instance, dma_rx->stream, (uint32_t) &instance->RXDR);
        LL_BDMA_SetChannelPriorityLevel(dma_rx->instance, dma_rx->stream, LL_BDMA_PRIORITY_LOW);
        LL_BDMA_SetPeriphIncMode(dma_rx->instance, dma_rx->stream, LL_BDMA_PERIPH_NOINCREMENT);
        LL_BDMA_SetPeriphSize(dma_rx->instance, dma_rx->stream, LL_BDMA_PDATAALIGN_BYTE);
        LL_BDMA_SetMemorySize(dma_rx->instance, dma_rx->stream, LL_BDMA_PDATAALIGN_BYTE);
    } else {
        __HAL_RCC_DMA1_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();
        LL_DMA_SetPeriphRequest(dma_tx->instance, dma_tx->stream, request);
        LL_DMA_SetMode(dma_tx->instance, dma_tx->stream, LL_DMA_MODE_NORMAL);
        LL_DMA_SetDataTransferDirection(dma_tx->instance, dma_tx->stream, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
        LL_DMA_SetPeriphAddress(dma_tx->instance, dma_tx->stream, (uint32_t) &instance->TXDR);
        LL_DMA_SetStreamPriorityLevel(dma_tx->instance, dma_tx->stream, LL_DMA_PRIORITY_LOW);
        LL_DMA_SetPeriphIncMode(dma_tx->instance, dma_tx->stream, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetPeriphSize(dma_tx->instance, dma_tx->stream, LL_DMA_PDATAALIGN_BYTE);
        LL_DMA_SetMemorySize(dma_tx->instance, dma_tx->stream, LL_DMA_PDATAALIGN_BYTE);


        LL_DMA_SetPeriphRequest(dma_rx->instance, dma_rx->stream, request - 1);
        LL_DMA_SetMode(dma_rx->instance, dma_rx->stream, LL_DMA_MODE_NORMAL);
        LL_DMA_SetDataTransferDirection(dma_rx->instance, dma_rx->stream, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_DMA_SetPeriphAddress(dma_rx->instance, dma_rx->stream, (uint32_t) &instance->RXDR);
        LL_DMA_SetStreamPriorityLevel(dma_rx->instance, dma_rx->stream, LL_DMA_PRIORITY_LOW);
        LL_DMA_SetPeriphIncMode(dma_rx->instance, dma_rx->stream, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetPeriphSize(dma_rx->instance, dma_rx->stream, LL_DMA_PDATAALIGN_BYTE);
        LL_DMA_SetMemorySize(dma_rx->instance, dma_rx->stream, LL_DMA_PDATAALIGN_BYTE);
    }
}

/**
 *
 * @param stm32_spi
 * @param spi_bus_name
 * @param spi_dma_name1
 * @param spi_dma_name2
 * @return
 */
static err_t stm32_spi_register(struct stm32_spi_bus *bus,
                                const char *spi_bus_name,
                                const char *spi_tx_dma_name,
                                const char *spi_rx_dma_name) {

    int spi_idx;

    ERROR_TRY(stm32_spi_verify_name(spi_bus_name, &spi_idx));

    memset(bus, 0 , sizeof(struct stm32_spi_bus));
    stm32_spi_init(bus, spi_idx);

    /* register physical dma dev */
    if (spi_tx_dma_name && spi_rx_dma_name) {
        bus->dma_tx = LL_DMA_DeviceGetByName(spi_tx_dma_name);
        bus->dma_rx = LL_DMA_DeviceGetByName(spi_rx_dma_name);

        ERROR_TRY(hal_dma_register(bus->dma_tx, spi_tx_dma_name, DEVICE_FLAG_WRONLY));
        ERROR_TRY(hal_dma_register(bus->dma_rx, spi_rx_dma_name, DEVICE_FLAG_RDONLY));

        stm32_spi_dma_init(bus->instance, bus->dma_tx, bus->dma_rx);

        dma_configure_irq(bus->dma_rx, spi_dma_callback, NVIC_PRIO_SPI_DMA, (uint32_t) bus);
    }
    ERROR_TRY(spi_bus_register(&bus->parent, spi_bus_name, &stm32_spi_ops));

    return E_OK;
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
err_t drv_spi_init(void) {
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
                                 "bdma_stream0",
                                 "bdma_stream1"));
    return E_OK;
}
