// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//


#include "sdop.h"
#include "asyncfatfs/sdcard.h"
#include "asyncfatfs/asyncfatfs.h"
#include "asyncfatfs/sdio.h"
#include "system/common.h"
#include "ff.h"
#include "fatfs.h"
#include "cli/log.h"


//#define SD_ON       HAL_GPIO_WritePin(SDEN_GPIO_Port, SDEN_Pin, GPIO_PIN_SET)
//afatfsFilePtr_t logFile;
//static void LogFileCreated(afatfsFilePtr_t file)
//{
//    if (file) {
//        logFile = file;
//    }
//}
#define FIFO_SIZE   30
extern volatile uint8_t headPos;
extern volatile uint8_t tailPos;
extern uint8_t bigdata[FIFO_SIZE][200];

void App_SD_Main(void const * argument)
{
//    SD_ON;
//    SDIO_GPIO_Init();
//    const sdcardConfig_t sdcardConfig = {SDIODEV_1, {GPIOB, GPIO_PIN_2}, {NULL},1,SDCARD_MODE_SDIO};
//    sdcard_init(&sdcardConfig);
//    afatfs_init();
//
//    while (afatfs_getFilesystemState() != AFATFS_FILESYSTEM_STATE_READY) {
//        afatfs_poll();
//
//        if (afatfs_getFilesystemState() == AFATFS_FILESYSTEM_STATE_FATAL) {
//            printf("error\n");
//        }
//    }
    SdCard_Init();
    Show_SD_Info();

    /* Infinite loop */
    assert(!f_open(&SDFile, "00001.xls", FA_OPEN_ALWAYS | FA_WRITE ));
    while (1)
    {
        if (headPos != tailPos)
        {
            f_write(&SDFile, (char *)bigdata[tailPos], 200, NULL);
            f_sync(&SDFile);
            tailPos = (tailPos + 1 ) % FIFO_SIZE;
        }
        osDelay(2);
    }
}