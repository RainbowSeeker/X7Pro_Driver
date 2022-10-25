//
// Created by 19114 on 2022/10/11.
//

#include "sdop.h"
#include "fatfs.h"

HAL_SD_CardInfoTypeDef SDCardInfo;									//SD卡信息
#define SD_ON       HAL_GPIO_WritePin(SDEN_GPIO_Port, SDEN_Pin, GPIO_PIN_SET)


/*！
 * 挂载函数 f_mount 内置 SD 初始化
 * 默认挂载点为 "0:/"
 */
void SD_Init()
{
    SD_ON;      // enable vdd output of sdcard
    MX_SDMMC1_SD_Init();
    MX_FATFS_Init();
    while (BSP_SD_Init())
    {
        osDelay(1000);
        print("Please inplug your sdcard!\r\n");
    }
    retSD = f_mount(&SDFatFS, SDPath, 1);
    assert(!retSD);
    print(">> Filesystem mount Succeed.\r\n");
}


//串口打印sd卡相关信息
void Show_SD_Info(void)
{
    //得到卡的信息并输出到串口1
    HAL_SD_GetCardInfo(&hsd1, &SDCardInfo);
    print("Card CardType:%u\r\n",SDCardInfo.CardType);	     //CardVersion
    print("Card CardVersion:%u\r\n",SDCardInfo.CardVersion);	     //CardVersion
    print("Card RCA:%u\r\n",SDCardInfo.RelCardAdd);	//卡相对地址
    print("Card Capacity:%u MB\r\n",(uint32_t)(SDCardInfo.LogBlockNbr)>>11);	//显示容量
    print("Card BlockSize:%u\r\n\r\n",SDCardInfo.LogBlockSize);//显示块大小
}

sd_error_t Test_Write(const char* path, const char* string, uint32_t len)
{
    UINT bw = 0;
    sd_error_t err = SD_OK;
//    if (FR_OK != f_open(&SDFile, path, FA_OPEN_ALWAYS | FA_WRITE ))
//    {
//        err = SD_OPEN_ERR;
//        goto errors;
//    }
    f_sync(&SDFile);
    //Move to end of the file to append data
//    if(FR_OK != f_lseek(&SDFile, f_size(&SDFile)))
//    {
//        err = SD_WRITE_ERR;
//        goto errors;
//    }
    f_write(&SDFile, string, len, &bw);
    if (bw < len)
    {
        err = SD_WRITE_ERR;
        goto errors;
    }
    f_sync(&SDFile);
    errors:
    /* close file */
//    f_close(&SDFile);
    return err;
}


//uint8_t BSP_SD_IsDetected(void)
//{
//    return SD_PRESENT;
//}


