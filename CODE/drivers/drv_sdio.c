// Copyright (c) 2022 By RainbowSeeker.

#include "common.h"


#include "module_common.h"
#include "drv_sdio.h"
#include "hal/sd/sd.h"
#include "stm32h7xx_ll_sdmmc.h"
#include "nvic.h"

#define SD_TIMEOUT    5000
#define EVENT_TX_CPLT 0x00000001
#define EVENT_RX_CPLT 0x00000002
#define EVENT_ERROR   0x00000004
#define EVENT_ABORT   0x00000008
/* SDMMC1 */
SD_HandleTypeDef hsd1;

static struct sd_device sd0_dev;

void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
    if (hsd == &hsd1)
    {
        os_event_send(&sd0_dev.event, EVENT_TX_CPLT);
    }
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
    if (hsd == &hsd1)
    {
        os_event_send(&sd0_dev.event, EVENT_RX_CPLT);
    }
}

void HAL_SD_ErrorCallback(SD_HandleTypeDef *hsd)
{
    if (hsd == &hsd1)
    {
        os_event_send(&sd0_dev.event, EVENT_ERROR);
    }
}

void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd)
{
    if (hsd == &hsd1)
    {
        os_event_send(&sd0_dev.event, EVENT_ABORT);
    }
}

/**
 * @brief This function handles SDMMC1 global interrupt.
 */
void SDMMC1_IRQHandler(void)
{
    os_interrupt_enter();

    HAL_SD_IRQHandler(&hsd1);

    os_interrupt_leave();
}

void HAL_SD_MspInit(SD_HandleTypeDef *sdHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (sdHandle->Instance == SDMMC1)
    {
        /* USER CODE BEGIN SDMMC1_MspInit 0 */
        /* USER CODE END SDMMC1_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
        PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            ASSERT(0);
        }

        /* SDMMC1 clock enable */
        __HAL_RCC_SDMMC1_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**SDMMC1 GPIO Configuration
        PC10     ------> SDMMC1_D2
        PC11     ------> SDMMC1_D3
        PC12     ------> SDMMC1_CK
        PD2     ------> SDMMC1_CMD
        PC8     ------> SDMMC1_D0
        PC9     ------> SDMMC1_D1
        */
        GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_8
                              | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* SDMMC1 interrupt Init */
        HAL_NVIC_SetPriority(SDMMC1_IRQn, NVIC_PRIO_SDMMC, 0);
        HAL_NVIC_EnableIRQ(SDMMC1_IRQn);
        /* USER CODE BEGIN SDMMC1_MspInit 1 */
        /* USER CODE END SDMMC1_MspInit 1 */
    }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef *sdHandle)
{

    if (sdHandle->Instance == SDMMC1)
    {
        /* USER CODE BEGIN SDMMC1_MspDeInit 0 */
        /* USER CODE END SDMMC1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_SDMMC1_CLK_DISABLE();

        /**SDMMC1 GPIO Configuration
        PC10     ------> SDMMC1_D2
        PC11     ------> SDMMC1_D3
        PC12     ------> SDMMC1_CK
        PD2     ------> SDMMC1_CMD
        PC8     ------> SDMMC1_D0
        PC9     ------> SDMMC1_D1
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_8
                               | GPIO_PIN_9);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

        /* SDMMC1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(SDMMC1_IRQn);
        /* USER CODE BEGIN SDMMC1_MspDeInit 1 */
        /* USER CODE END SDMMC1_MspDeInit 1 */
    }
}

static err_t sdio_wait_complete(sd_dev_t sd_dev, uint32_t *status)
{
    if (os_event_recv(&sd_dev->event, 0xffffffff,
                      SD_TIMEOUT, status) != E_OK)
    {
        /* wait timeout */
        return E_TIMEOUT;
    }

    return E_OK;
}

static err_t init(sd_dev_t sd)
{
    SD_HandleTypeDef *sd_handle = sd->parent.user_data;

    ASSERT(sd_handle != NULL);

    hsd1.Instance = SDMMC1;
    hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
    hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
    hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
    hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd1.Init.ClockDiv = 0;
//    hsd1.Init.TranceiverPresent = SDMMC_TRANSCEIVER_NOT_PRESENT;
    if (HAL_SD_Init(&hsd1) != HAL_OK)
    {
        return E_RROR;
    }


    return E_OK;
}

static err_t write_disk(sd_dev_t sd, uint8_t *buffer, uint32_t sector, uint32_t count)
{
    err_t err = E_OK;
    uint32_t status;
    SD_HandleTypeDef *sd_handle = sd->parent.user_data;

    ASSERT(sd_handle != NULL);

    if (HAL_SD_WriteBlocks_DMA(sd_handle, buffer, sector, count) != HAL_OK)
    {
        return E_RROR;
    }

    err = sdio_wait_complete(sd, &status);
    if ((err == E_OK) && (status & EVENT_TX_CPLT))
    {
        /* block until SDIO IP is ready or a timeout occur */
        uint32_t start = systime_now_ms();
        uint32_t now;
        while (HAL_SD_GetCardState(sd_handle) != HAL_SD_CARD_TRANSFER)
        {
            now = systime_now_ms();
            if (now - start > SD_TIMEOUT)
            {
                err = E_TIMEOUT;
                break;
            }
            sys_msleep(1);
        }
    }

    return err;
}

static err_t read_disk(sd_dev_t sd, uint8_t *buffer, uint32_t sector, uint32_t count)
{
    err_t err = E_OK;
    uint32_t status;
    SD_HandleTypeDef *sd_handle = sd->parent.user_data;

    ASSERT(sd_handle != NULL);

    if (HAL_SD_ReadBlocks_DMA(sd_handle, buffer, sector, count) != HAL_OK)
    {
        return E_RROR;
    }

    err = sdio_wait_complete(sd, &status);
    if ((err == E_OK) && (status & EVENT_RX_CPLT))
    {
        /* block until SDIO IP is ready or a timeout occur */
        uint32_t start = systime_now_ms();
        uint32_t now;
        while (HAL_SD_GetCardState(sd_handle) != HAL_SD_CARD_TRANSFER)
        {
            now = systime_now_ms();
            if (now - start > SD_TIMEOUT)
            {
                err = E_TIMEOUT;
                break;
            }
            sys_msleep(1);
        }
    }

    return err;
}

static err_t io_control(sd_dev_t sd, int cmd, void *arg)
{
    SD_HandleTypeDef *sd_handle = sd->parent.user_data;

    ASSERT(sd_handle != NULL);

    switch (cmd)
    {
        case DEVICE_CTRL_BLK_GETGEOME:
        {
            struct device_blk_geometry geometry;
            HAL_SD_CardInfoTypeDef pCardInfo;

            if (arg == NULL)
            {
                return E_INVAL;
            }
            /* get sd card information */
            if (HAL_SD_GetCardInfo(sd_handle, &pCardInfo) != HAL_OK)
            {
                return E_RROR;
            }

            geometry.bytes_per_sector = pCardInfo.BlockSize;
            geometry.block_size = pCardInfo.BlockSize;
            geometry.sector_count = pCardInfo.BlockNbr;
            *(struct device_blk_geometry *) arg = geometry;
        }
            break;
        case DEVICE_CTRL_BLK_SYNC:
        {
            // TODO, improve it?
            if (HAL_SD_GetCardState(sd_handle) != HAL_SD_CARD_TRANSFER)
            {
                return E_RROR;
            }
        }
            break;
        case DEVICE_CTRL_BLK_ERASE:
        {
            // uint32_t* tbl = (uint32_t*)arg;
            // HAL_SD_Erase(sd_handle, tbl[0], tbl[1]);

            /* sd card is not needed to erase */
            return E_RROR;
        }
        default:
        {
            console_printf("unknown sd control cmd:%d\n", cmd);
        }
            break;
    }

    return E_OK;
}

const static struct sd_ops dev_ops = {.init = init, .write_disk = write_disk, .read_disk = read_disk, .io_control = io_control};


err_t drv_sdio_init(void)
{

    sd0_dev.ops = &dev_ops;

    if (os_event_init(&sd0_dev.event, "sdio") != E_OK)
    {
        printf("\r\nfail to init sdio event");
        return E_RROR;
    }

    return hal_sd_register(&sd0_dev, "sd0", DEVICE_FLAG_RDWR | DEVICE_FLAG_REMOVABLE | DEVICE_FLAG_STANDALONE, &hsd1);
}
