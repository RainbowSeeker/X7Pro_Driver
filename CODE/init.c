// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//
#include <common.h>
#include "gpio.h"
#include "ledbeep.h"
#include "dma.h"
#include "bus_spi.h"
#include "drivers/serial/uart.h"
#include "cli/cli.h"
#include "module/ipc/uMCN.h"
#include "driver/sd/drv_sdio.h"

#include "file_manager/file_manager.h"

static const struct dfs_mount_tbl mnt_table[] = {
        { "sd0", "/", "elm", 0, NULL },
        { NULL } /* NULL indicate the end */
};

void Initialize(void)
{
    MX_GPIO_Init();

    drv_uart_init();

    console_init();

    console_enable_input();

    EXTI_Init();

    LED_BEEP_Init();

    SPI_BspInit();

    mcn_init();

    drv_sdio_init();

    file_manager_init(mnt_table);

//    MX_SDMMC1_SD_Init();
//    MX_FATFS_Init();
//
//    while (BSP_SD_Init())
//    {
//        delay_ms(1000);
//        printf("Please inplug your sdcard!\r\n");
//    }
//    retSD = f_mount(&SDFatFS, SDPath, 1);
//    ASSERT(!retSD);
//    printf(">> Filesystem mount Succeed.\r\n");
//
//    ASSERT(!f_open(&SDFile, "00001.xls", FA_OPEN_ALWAYS | FA_WRITE ));
    param_init();
}