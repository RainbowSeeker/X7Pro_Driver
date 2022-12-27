// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/17.
//
#include "board.h"

#if defined(BSP_USING_FDCAN1) || defined(BSP_USING_FDCAN2)
#include "drv_fdcan.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.fdcan"
#include <ulog.h>

static struct stm32_fdcan fdcan = {0};


void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
#ifdef BSP_USING_FDCAN1
    if(fdcanHandle->Instance==FDCAN1)
    {
        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
        SELF_CHECK(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct));

        /* FDCAN1 clock enable */
        __HAL_RCC_FDCAN_CLK_ENABLE();

        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();
        /**FDCAN1 GPIO Configuration
        PH13     ------> FDCAN1_TX
        PI9     ------> FDCAN1_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
    }
#endif
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{
#ifdef BSP_USING_FDCAN1
    if(fdcanHandle->Instance==FDCAN1)
    {
        /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

        /* USER CODE END FDCAN1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_FDCAN_CLK_DISABLE();

        /**FDCAN1 GPIO Configuration
        PH13     ------> FDCAN1_TX
        PI9     ------> FDCAN1_RX
        */
        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_13);

        HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9);

        /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

        /* USER CODE END FDCAN1_MspDeInit 1 */
    }
#endif
}

static err_t fdcan_init(light_device_t dev)
{
    ASSERT(dev != NULL);
    struct stm32_fdcan *device = (struct stm32_fdcan *)dev;

    device->fdcan.Instance                  = FDCAN1;
    device->fdcan.Init.FrameFormat          = FDCAN_FRAME_CLASSIC;
    device->fdcan.Init.Mode                 = FDCAN_MODE_INTERNAL_LOOPBACK;
    device->fdcan.Init.AutoRetransmission   = ENABLE;
    device->fdcan.Init.TransmitPause        = DISABLE;
    device->fdcan.Init.ProtocolException    = ENABLE;
    device->fdcan.Init.NominalPrescaler     = 0x01; /* tq = NominalPrescaler x (1/fdcan_ker_ck) */
    device->fdcan.Init.NominalSyncJumpWidth = 0x08;
    device->fdcan.Init.DataPrescaler        = 0x01;
    device->fdcan.Init.DataSyncJumpWidth    = 0x04;
    device->fdcan.Init.DataTimeSeg1         = 0x05; /* DataTimeSeg1 = Propagation_segment + Phase_segment_1 */
    device->fdcan.Init.DataTimeSeg2         = 0x04;
    device->fdcan.Init.NominalTimeSeg1      = 0x1F; /* NominalTimeSeg1 = Propagation_segment + Phase_segment_1 */
    device->fdcan.Init.NominalTimeSeg2      = 0x08;
    device->fdcan.Init.MessageRAMOffset     = 0x00;
    device->fdcan.Init.StdFiltersNbr        = 0x01;
    device->fdcan.Init.ExtFiltersNbr        = 0x01;
    device->fdcan.Init.RxFifo0ElmtsNbr      = 0x01;
    device->fdcan.Init.RxFifo0ElmtSize      = FDCAN_DATA_BYTES_8;
    device->fdcan.Init.RxFifo1ElmtsNbr      = 0x02;
    device->fdcan.Init.RxFifo1ElmtSize      = FDCAN_DATA_BYTES_8;
    device->fdcan.Init.RxBuffersNbr         = 0x00;
    device->fdcan.Init.TxEventsNbr          = 0x00;
    device->fdcan.Init.TxBuffersNbr         = 0x00;
    device->fdcan.Init.TxFifoQueueElmtsNbr  = 0x01;
    device->fdcan.Init.TxFifoQueueMode      = FDCAN_TX_FIFO_OPERATION;
    device->fdcan.Init.TxElmtSize           = FDCAN_DATA_BYTES_8;

    if (HAL_FDCAN_Init(&device->fdcan) != HAL_OK)
    {
        return E_RROR;
    }

    device->filter.IdType             = FDCAN_EXTENDED_ID;
    device->filter.FilterIndex        = 0;
    device->filter.FilterType         = FDCAN_FILTER_MASK;
    device->filter.FilterConfig       = FDCAN_FILTER_TO_RXFIFO0;
    device->filter.FilterID1          = 0x1111111;
    device->filter.FilterID2          = 0x2222222;

    if (HAL_FDCAN_ConfigFilter(&device->fdcan, &device->filter)!=HAL_OK)
    {
        return E_RROR;
    }
    HAL_FDCAN_Start(&device->fdcan);
    HAL_FDCAN_ActivateNotification(&device->fdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0); /* open rx fifo0 new message it */

    device->fifo0 = RESET;
    device->fifo1 = RESET;

    return E_OK;
}


static err_t fdcan_control(light_device_t dev, int cmd, void *args)
{
    ASSERT(dev != NULL);
    struct stm32_fdcan *device = (struct stm32_fdcan *)dev;

    switch (cmd)
    {
        case FDCAN_MODE_NORMAL:
            device->fdcan.Init.Mode  = FDCAN_MODE_NORMAL;
            break;
        case FDCAN_MODE_INTERNAL_LOOPBACK:
            device->fdcan.Init.Mode  = FDCAN_MODE_INTERNAL_LOOPBACK;
            break;
        default:
            break;
    }

    HAL_FDCAN_Init(&device->fdcan);

    return E_OK;
}

static size_t fdcan_read(light_device_t dev, off_t pos, void *buffer, size_t size)
{
    ASSERT(dev != NULL);
    struct stm32_fdcan *device = (struct stm32_fdcan *)dev;

    if (fdcan.fifo0 == SET)
    {
        fdcan.fifo0 = RESET;
        if (HAL_FDCAN_GetRxMessage(&device->fdcan, FDCAN_RX_FIFO0, &device->rx_config, (uint8_t *)buffer) != HAL_OK)
        {
            LOG_E("get msg error from fdcan fifo0!");
            return 0;
        }

        return device->rx_config.DataLength >> 16;
    }
    if (fdcan.fifo1 == SET)
    {
        fdcan.fifo0 = RESET;
        if (HAL_FDCAN_GetRxMessage(&device->fdcan, FDCAN_RX_FIFO1, &device->rx_config, (uint8_t *)buffer) != HAL_OK)
        {
            LOG_E("get msg error from fdcan fifo1!");
            return 0;
        }

        return device->rx_config.DataLength >> 16;
    }

    return 0;
}

static size_t fdcan_write(light_device_t dev, off_t pos, const void *buffer, size_t size)
{
    ASSERT(dev != NULL);
    struct stm32_fdcan *device = (struct stm32_fdcan *)dev;

    device->tx_config.Identifier          = 0x1111112;
    device->tx_config.IdType              = FDCAN_EXTENDED_ID;
    device->tx_config.TxFrameType         = FDCAN_DATA_FRAME;
    device->tx_config.DataLength          = FDCAN_DLC_BYTES_8;
    device->tx_config.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    device->tx_config.BitRateSwitch       = FDCAN_BRS_OFF;
    device->tx_config.FDFormat            = FDCAN_CLASSIC_CAN;
    device->tx_config.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
    device->tx_config.MessageMarker       = 0xCC;

    if (HAL_FDCAN_AddMessageToTxFifoQ(&device->fdcan, &device->tx_config, (uint8_t *)buffer) != HAL_OK)
    {
        return E_RROR;
    }

    return E_OK;
}

void FDCAN1_IT0_IRQHandler(void)
{
    /* enter interrupt */
    os_interrupt_enter();

    HAL_FDCAN_IRQHandler(&fdcan.fdcan);

    /* leave interrupt */
    os_interrupt_leave();
}

void FDCAN1_IT1_IRQHandler(void)
{
   /* enter interrupt */
   os_interrupt_enter();

   HAL_FDCAN_IRQHandler(&fdcan.fdcan);

   /* leave interrupt */
   os_interrupt_leave();
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if (hfdcan->Instance == FDCAN1)
    {
        if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
        {
            fdcan.fifo0 = SET;
            HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
        }
    }
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
    {
        fdcan.fifo1 = SET;
        HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0);
    }
}

int drv_fdcan_init(const char *name)
{
    fdcan.dev.type      = Device_Class_CAN;
    fdcan.dev.init      = fdcan_init;
    fdcan.dev.open      = NULL;
    fdcan.dev.close     = NULL;
    fdcan.dev.read      = fdcan_read;
    fdcan.dev.write     = fdcan_write;
    fdcan.dev.control   = fdcan_control;
    fdcan.dev.user_data = NULL;

    light_device_register(&fdcan.dev, name, DEVICE_FLAG_RDWR | DEVICE_FLAG_REMOVABLE | DEVICE_FLAG_STANDALONE);

    LOG_I("%s init success!", name);
    return E_OK;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

int fdcan_sample(int argc, char **argv)
{
    err_t result = E_OK;
    uint8_t i, rx_buf[8], tx_buf[8];
    struct device *dev = NULL;

    if (argc != 9)
    {
        printf("Usage:\n");
        printf("fdcan_sample 1 2 3 4 5 6 7 8\n");
        return -1;
    }

    for (i = 0; i < 8; i++)
    {
        tx_buf[i] = atoi(argv[i+1]);
    }

    dev = light_device_find("fdcan1");
    if (dev == NULL)
    {
        printf("can't find fdcan1 device!\n");
        return E_RROR;
    }
    light_device_open(dev, DEVICE_OFLAG_RDWR);

    light_device_write(dev, 0, tx_buf, 8);
    os_delay(1);
    light_device_read(dev, 0, rx_buf, 8);

    printf("fdcan1 loopback test over, rbuf = ");
    for (i = 0; i < 8; i++)
    {
        printf(" %x ", rx_buf[i]);
    }
    printf("\n");

    return result;
}
FINSH_FUNCTION_EXPORT_CMD(fdcan_sample, __cmd_fdcan_sample, fdcan loopback mode test);

#endif
#endif