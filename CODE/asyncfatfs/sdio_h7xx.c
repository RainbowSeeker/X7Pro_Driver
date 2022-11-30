//// Copyright (c) 2022 By RainbowSeeker.
//
///*
// * This file is part of Cleanflight and Betaflight.
// *
// * Cleanflight and Betaflight are free software. You can redistribute
// * this software and/or modify this software under the terms of the
// * GNU General Public License as published by the Free Software
// * Foundation, either version 3 of the License, or (at your option)
// * any later version.
// *
// * Cleanflight and Betaflight are distributed in the hope that they
// * will be useful, but WITHOUT ANY WARRANTY; without even the implied
// * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// * See the GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this software.
// *
// * If not, see <http://www.gnu.org/licenses/>.
// */
//
///*
// * Original author: Alain (https://github.com/aroyer-qc)
// * Modified for BF source: Chris Hockuba (https://github.com/conkerkh)
// */
//
///* Include(s) -------------------------------------------------------------------------------------------------------*/
//
//#include <stdbool.h>
//#include <string.h>
//
////#include "platform.h"
////
////#ifdef USE_SDCARD_SDIO
//
//#include "stm32h7xx.h"
//#include "sdmmc_sdio.h"
//#include "driver/io.h"
//#include "sdio.h"
//
//typedef struct SD_Handle_s
//{
//    uint32_t          CSD[4];           // SD card specific data table
//    uint32_t          CID[4];           // SD card identification number table
//    volatile uint32_t RXCplt;          // SD RX Complete is equal 0 when no transfer
//    volatile uint32_t TXCplt;          // SD TX Complete is equal 0 when no transfer
//
//    uint32_t RXErrors;
//    uint32_t TXErrors;
//} SD_Handle_t;
//
//SD_HandleTypeDef hsd1;
//
//SD_CardInfo_t                      SD_CardInfo;
//SD_CardType_t                      SD_CardType;
//
//SD_Handle_t                        SD_Handle;
//
//typedef struct sdioPin_s {
//    io_t pin;
//    uint8_t af;
//} sdioPin_t;
//
//#define SDIO_PIN_D0  0
//#define SDIO_PIN_D1  1
//#define SDIO_PIN_D2  2
//#define SDIO_PIN_D3  3
//#define SDIO_PIN_CK  4
//#define SDIO_PIN_CMD 5
//#define SDIO_PIN_COUNT  6
//
//#define SDIO_MAX_PINDEFS 2
//
//typedef struct sdioHardware_s {
//    SDMMC_TypeDef *instance;
//    IRQn_Type irqn;
//    sdioPin_t sdioPinCK[SDIO_MAX_PINDEFS];
//    sdioPin_t sdioPinCMD[SDIO_MAX_PINDEFS];
//    sdioPin_t sdioPinD0[SDIO_MAX_PINDEFS];
//    sdioPin_t sdioPinD1[SDIO_MAX_PINDEFS];
//    sdioPin_t sdioPinD2[SDIO_MAX_PINDEFS];
//    sdioPin_t sdioPinD3[SDIO_MAX_PINDEFS];
//} sdioHardware_t;
//
//// Possible pin assignments
//
//#define PINDEF(device, afnum) GPIO_AF ## afnum ## _SDMMC ## device
//
//static const sdioHardware_t sdioPinHardware[SDIODEV_COUNT] = {
//    {
//        .instance = SDMMC1,
//        .irqn = SDMMC1_IRQn,
//        .sdioPinCK  = { {GPIOC, GPIO_PIN_12, PINDEF(1, 12)}},
//        .sdioPinCMD = { {GPIOD, GPIO_PIN_2 , PINDEF(1, 12)}},
//        .sdioPinD0  = { {GPIOC, GPIO_PIN_8 , PINDEF(1, 12)}},
//        .sdioPinD1  = { {GPIOC, GPIO_PIN_9, PINDEF(1, 12)}},
//        .sdioPinD2  = { {GPIOC, GPIO_PIN_10, PINDEF(1, 12)}},
//        .sdioPinD3  = { {GPIOC, GPIO_PIN_11, PINDEF(1, 12)}},
//    },
//    {
//        .instance = SDMMC2,
//        .irqn = SDMMC2_IRQn,
//        .sdioPinCK  = { {GPIOC, GPIO_PIN_1 , PINDEF(2, 9)}, {GPIOD, GPIO_PIN_6 , PINDEF(2, 11)} },
//        .sdioPinCMD = { {GPIOA, GPIO_PIN_0 , PINDEF(2, 9)}, {GPIOD, GPIO_PIN_7 , PINDEF(2, 11)} },
//        .sdioPinD0  = { {GPIOB, GPIO_PIN_14, PINDEF(2, 9)},  },
//        .sdioPinD1  = { {GPIOB, GPIO_PIN_15, PINDEF(2, 9)},  },
//        .sdioPinD2  = { {GPIOB, GPIO_PIN_3 , PINDEF(2, 9)},  },
//        .sdioPinD3  = { {GPIOB, GPIO_PIN_4 , PINDEF(2, 9)},  },
//    }
//};
//
//#undef PINDEF
//
//// Active configuration
//static const sdioHardware_t *sdioHardware;
//static sdioPin_t sdioPin[SDIO_PIN_COUNT];
//
//#undef SDIOFINDPIN
//
//#define IOCFG_SDMMC       GPIO_MODE_AF_PP, GPIO_NOPULL,  GPIO_SPEED_FREQ_VERY_HIGH
//
//void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
//{
//    UNUSED(hsd);
//
//    if (!sdioHardware) {
//        return;
//    }
//
//    if (sdioHardware->instance == SDMMC1) {
//        __HAL_RCC_SDMMC1_CLK_DISABLE();
//        __HAL_RCC_SDMMC1_FORCE_RESET();
//        __HAL_RCC_SDMMC1_RELEASE_RESET();
//        __HAL_RCC_SDMMC1_CLK_ENABLE();
//    } else if (sdioHardware->instance == SDMMC2) {
//        __HAL_RCC_SDMMC2_CLK_DISABLE();
//        __HAL_RCC_SDMMC2_FORCE_RESET();
//        __HAL_RCC_SDMMC2_RELEASE_RESET();
//        __HAL_RCC_SDMMC2_CLK_ENABLE();
//    }
//
//    uint8_t is4BitWidth = 1;
//
//    const io_t clk = sdioPin[SDIO_PIN_CK].pin;
//    const io_t cmd = sdioPin[SDIO_PIN_CMD].pin;
//    const io_t d0 = sdioPin[SDIO_PIN_D0].pin;
//    const io_t d1 = sdioPin[SDIO_PIN_D1].pin;
//    const io_t d2 = sdioPin[SDIO_PIN_D2].pin;
//    const io_t d3 = sdioPin[SDIO_PIN_D3].pin;
//
//    IO_Init(clk, IOCFG_SDMMC, sdioPin[SDIO_PIN_CK].af);
//    IO_Init(cmd, IOCFG_SDMMC, sdioPin[SDIO_PIN_CMD].af);
//    IO_Init(d0, IOCFG_SDMMC, sdioPin[SDIO_PIN_D0].af);
//
//    if(is4BitWidth) {
//        IO_Init(d1, IOCFG_SDMMC, sdioPin[SDIO_PIN_D1].af);
//        IO_Init(d2, IOCFG_SDMMC, sdioPin[SDIO_PIN_D2].af);
//        IO_Init(d3, IOCFG_SDMMC, sdioPin[SDIO_PIN_D3].af);
//    }
//
//    HAL_NVIC_SetPriority(sdioHardware->irqn, 5, 0);
//    HAL_NVIC_EnableIRQ(sdioHardware->irqn);
//}
//
//void SDIO_GPIO_Init(void)
//{
//    SDIODevice device = SDIODEV_1;
//    sdioHardware = &sdioPinHardware[device];
//
//    sdioPin[SDIO_PIN_D0] = sdioPinHardware[device].sdioPinD0[0];
//    sdioPin[SDIO_PIN_D1] = sdioPinHardware[device].sdioPinD1[0];
//    sdioPin[SDIO_PIN_D2] = sdioPinHardware[device].sdioPinD2[0];
//    sdioPin[SDIO_PIN_D3] = sdioPinHardware[device].sdioPinD3[0];
//    sdioPin[SDIO_PIN_CK] = sdioPinHardware[device].sdioPinCK[0];
//    sdioPin[SDIO_PIN_CMD] = sdioPinHardware[device].sdioPinCMD[0];
//
//    if (!sdioHardware) {
//        return;
//    }
//
//    uint8_t is4BitWidth = 1;
//
//    const io_t clk = sdioPin[SDIO_PIN_CK].pin;
//    const io_t cmd = sdioPin[SDIO_PIN_CMD].pin;
//    const io_t d0 = sdioPin[SDIO_PIN_D0].pin;
//    const io_t d1 = sdioPin[SDIO_PIN_D1].pin;
//    const io_t d2 = sdioPin[SDIO_PIN_D2].pin;
//    const io_t d3 = sdioPin[SDIO_PIN_D3].pin;
//
//#define IOCFG_OUT_PP         GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0
//    //
//    // Setting all the SDIO pins to high for a short time results in more robust initialisation.
//    //
//    IO_Set(d0, IO_HIGH);
//    IO_Init(d0, IOCFG_OUT_PP);
//
//    if(is4BitWidth) {
//        IO_Set(d1, IO_HIGH);
//        IO_Set(d2, IO_HIGH);
//        IO_Set(d3, IO_HIGH);
//        IO_Init(d1, IOCFG_OUT_PP);
//        IO_Init(d2, IOCFG_OUT_PP);
//        IO_Init(d3, IOCFG_OUT_PP);
//    }
//
//    IO_Set(clk, IO_HIGH);
//    IO_Set(cmd, IO_HIGH);
//    IO_Init(clk, IOCFG_OUT_PP);
//    IO_Init(cmd, IOCFG_OUT_PP);
//}
//
//bool SD_Initialize_LL(DMA_Stream_TypeDef *dma)
//{
//    UNUSED(dma);
//
//    return true;
//}
//
//bool SD_GetState(void)
//{
//    HAL_SD_CardStateTypedef cardState = HAL_SD_GetCardState(&hsd1);
//
//    return (cardState == HAL_SD_CARD_TRANSFER);
//}
//
//static SD_Error_t SD_DoInit(void)
//{
//    HAL_StatusTypeDef status;
//
//    memset(&hsd1, 0, sizeof(hsd1));
//
//    hsd1.Instance = sdioHardware->instance;
//
//    hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
//    hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_ENABLE;
//    if (1) {
//        hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
//    } else {
//        hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
//    }
//    hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE;
//#if defined(STM32H730xx)
//    hsd1.Init.ClockDiv = 2; // 200Mhz / (2 * 2 ) = 50Mhz, used for "UltraHigh speed SD card" only, see   HAL_SD_ConfigWideBusOperation, SDMMC_HSpeed_CLK_DIV, SDMMC_NSpeed_CLK_DIV
//#else
//    hsd1.Init.ClockDiv = 1; // 200Mhz / (2 * 1 ) = 100Mhz, used for "UltraHigh speed SD card" only, see   HAL_SD_ConfigWideBusOperation, SDMMC_HSpeed_CLK_DIV, SDMMC_NSpeed_CLK_DIV
//#endif
//    status = HAL_SD_Init(&hsd1); // Will call HAL_SD_MspInit
//
//    if (status != HAL_OK) {
//        return SD_ERROR;
//    }
//
//    switch(hsd1.SdCard.CardType) {
//    case CARD_SDSC:
//        switch (hsd1.SdCard.CardVersion) {
//        case CARD_V1_X:
//            SD_CardType = SD_STD_CAPACITY_V1_1;
//            break;
//        case CARD_V2_X:
//            SD_CardType = SD_STD_CAPACITY_V2_0;
//            break;
//        default:
//            return SD_ERROR;
//        }
//        break;
//
//    case CARD_SDHC_SDXC:
//        SD_CardType = SD_HIGH_CAPACITY;
//        break;
//
//    default:
//        return SD_ERROR;
//    }
//
//
//    memcpy(&SD_Handle.CSD, &hsd1.CSD, sizeof(SD_Handle.CSD));
//    memcpy(&SD_Handle.CID, &hsd1.CID, sizeof(SD_Handle.CID));
//
//    return SD_OK;
//}
//
//SD_Error_t SD_GetCardInfo(void)
//{
//    SD_Error_t ErrorState = SD_OK;
//
//    // fill in SD_CardInfo
//
//    uint32_t Temp = 0;
//
//    // Byte 0
//    Temp = (SD_Handle.CSD[0] & 0xFF000000) >> 24;
//    SD_CardInfo.SD_csd.CSDStruct      = (uint8_t)((Temp & 0xC0) >> 6);
//    SD_CardInfo.SD_csd.SysSpecVersion = (uint8_t)((Temp & 0x3C) >> 2);
//    SD_CardInfo.SD_csd.Reserved1      = Temp & 0x03;
//
//    // Byte 1
//    Temp = (SD_Handle.CSD[0] & 0x00FF0000) >> 16;
//    SD_CardInfo.SD_csd.TAAC = (uint8_t)Temp;
//
//    // Byte 2
//    Temp = (SD_Handle.CSD[0] & 0x0000FF00) >> 8;
//    SD_CardInfo.SD_csd.NSAC = (uint8_t)Temp;
//
//    // Byte 3
//    Temp = SD_Handle.CSD[0] & 0x000000FF;
//    SD_CardInfo.SD_csd.MaxBusClkFrec = (uint8_t)Temp;
//
//    // Byte 4
//    Temp = (SD_Handle.CSD[1] & 0xFF000000) >> 24;
//    SD_CardInfo.SD_csd.CardComdClasses = (uint16_t)(Temp << 4);
//
//    // Byte 5
//    Temp = (SD_Handle.CSD[1] & 0x00FF0000) >> 16;
//    SD_CardInfo.SD_csd.CardComdClasses |= (uint16_t)((Temp & 0xF0) >> 4);
//    SD_CardInfo.SD_csd.RdBlockLen       = (uint8_t)(Temp & 0x0F);
//
//    // Byte 6
//    Temp = (SD_Handle.CSD[1] & 0x0000FF00) >> 8;
//    SD_CardInfo.SD_csd.PartBlockRead   = (uint8_t)((Temp & 0x80) >> 7);
//    SD_CardInfo.SD_csd.WrBlockMisalign = (uint8_t)((Temp & 0x40) >> 6);
//    SD_CardInfo.SD_csd.RdBlockMisalign = (uint8_t)((Temp & 0x20) >> 5);
//    SD_CardInfo.SD_csd.DSRImpl         = (uint8_t)((Temp & 0x10) >> 4);
//    SD_CardInfo.SD_csd.Reserved2       = 0; /*!< Reserved */
//
//    if((SD_CardType == SD_STD_CAPACITY_V1_1) || (SD_CardType == SD_STD_CAPACITY_V2_0)) {
//        SD_CardInfo.SD_csd.DeviceSize = (Temp & 0x03) << 10;
//
//        // Byte 7
//        Temp = (uint8_t)(SD_Handle.CSD[1] & 0x000000FF);
//        SD_CardInfo.SD_csd.DeviceSize |= (Temp) << 2;
//
//        // Byte 8
//        Temp = (uint8_t)((SD_Handle.CSD[2] & 0xFF000000) >> 24);
//        SD_CardInfo.SD_csd.DeviceSize |= (Temp & 0xC0) >> 6;
//
//        SD_CardInfo.SD_csd.MaxRdCurrentVDDMin = (Temp & 0x38) >> 3;
//        SD_CardInfo.SD_csd.MaxRdCurrentVDDMax = (Temp & 0x07);
//
//        // Byte 9
//        Temp = (uint8_t)((SD_Handle.CSD[2] & 0x00FF0000) >> 16);
//        SD_CardInfo.SD_csd.MaxWrCurrentVDDMin = (Temp & 0xE0) >> 5;
//        SD_CardInfo.SD_csd.MaxWrCurrentVDDMax = (Temp & 0x1C) >> 2;
//        SD_CardInfo.SD_csd.DeviceSizeMul      = (Temp & 0x03) << 1;
//
//        // Byte 10
//        Temp = (uint8_t)((SD_Handle.CSD[2] & 0x0000FF00) >> 8);
//        SD_CardInfo.SD_csd.DeviceSizeMul |= (Temp & 0x80) >> 7;
//
//        SD_CardInfo.CardCapacity  = (SD_CardInfo.SD_csd.DeviceSize + 1) ;
//        SD_CardInfo.CardCapacity *= (1 << (SD_CardInfo.SD_csd.DeviceSizeMul + 2));
//        SD_CardInfo.CardBlockSize = 1 << (SD_CardInfo.SD_csd.RdBlockLen);
//        SD_CardInfo.CardCapacity = SD_CardInfo.CardCapacity * SD_CardInfo.CardBlockSize / 512; // In 512 byte blocks
//    } else if(SD_CardType == SD_HIGH_CAPACITY) {
//        // Byte 7
//        Temp = (uint8_t)(SD_Handle.CSD[1] & 0x000000FF);
//        SD_CardInfo.SD_csd.DeviceSize = (Temp & 0x3F) << 16;
//
//        // Byte 8
//        Temp = (uint8_t)((SD_Handle.CSD[2] & 0xFF000000) >> 24);
//
//        SD_CardInfo.SD_csd.DeviceSize |= (Temp << 8);
//
//        // Byte 9
//        Temp = (uint8_t)((SD_Handle.CSD[2] & 0x00FF0000) >> 16);
//
//        SD_CardInfo.SD_csd.DeviceSize |= (Temp);
//
//        // Byte 10
//        Temp = (uint8_t)((SD_Handle.CSD[2] & 0x0000FF00) >> 8);
//
//        SD_CardInfo.CardCapacity  = ((uint64_t)SD_CardInfo.SD_csd.DeviceSize + 1) * 1024;
//        SD_CardInfo.CardBlockSize = 512;
//    } else {
//        // Not supported card type
//        ErrorState = SD_ERROR;
//    }
//
//    SD_CardInfo.SD_csd.EraseGrSize = (Temp & 0x40) >> 6;
//    SD_CardInfo.SD_csd.EraseGrMul  = (Temp & 0x3F) << 1;
//
//    // Byte 11
//    Temp = (uint8_t)(SD_Handle.CSD[2] & 0x000000FF);
//    SD_CardInfo.SD_csd.EraseGrMul     |= (Temp & 0x80) >> 7;
//    SD_CardInfo.SD_csd.WrProtectGrSize = (Temp & 0x7F);
//
//    // Byte 12
//    Temp = (uint8_t)((SD_Handle.CSD[3] & 0xFF000000) >> 24);
//    SD_CardInfo.SD_csd.WrProtectGrEnable = (Temp & 0x80) >> 7;
//    SD_CardInfo.SD_csd.ManDeflECC        = (Temp & 0x60) >> 5;
//    SD_CardInfo.SD_csd.WrSpeedFact       = (Temp & 0x1C) >> 2;
//    SD_CardInfo.SD_csd.MaxWrBlockLen     = (Temp & 0x03) << 2;
//
//    // Byte 13
//    Temp = (uint8_t)((SD_Handle.CSD[3] & 0x00FF0000) >> 16);
//    SD_CardInfo.SD_csd.MaxWrBlockLen      |= (Temp & 0xC0) >> 6;
//    SD_CardInfo.SD_csd.WriteBlockPaPartial = (Temp & 0x20) >> 5;
//    SD_CardInfo.SD_csd.Reserved3           = 0;
//    SD_CardInfo.SD_csd.ContentProtectAppli = (Temp & 0x01);
//
//    // Byte 14
//    Temp = (uint8_t)((SD_Handle.CSD[3] & 0x0000FF00) >> 8);
//    SD_CardInfo.SD_csd.FileFormatGrouop = (Temp & 0x80) >> 7;
//    SD_CardInfo.SD_csd.CopyFlag         = (Temp & 0x40) >> 6;
//    SD_CardInfo.SD_csd.PermWrProtect    = (Temp & 0x20) >> 5;
//    SD_CardInfo.SD_csd.TempWrProtect    = (Temp & 0x10) >> 4;
//    SD_CardInfo.SD_csd.FileFormat       = (Temp & 0x0C) >> 2;
//    SD_CardInfo.SD_csd.ECC              = (Temp & 0x03);
//
//    // Byte 15
//    Temp = (uint8_t)(SD_Handle.CSD[3] & 0x000000FF);
//    SD_CardInfo.SD_csd.CSD_CRC   = (Temp & 0xFE) >> 1;
//    SD_CardInfo.SD_csd.Reserved4 = 1;
//
//    // Byte 0
//    Temp = (uint8_t)((SD_Handle.CID[0] & 0xFF000000) >> 24);
//    SD_CardInfo.SD_cid.ManufacturerID = Temp;
//
//    // Byte 1
//    Temp = (uint8_t)((SD_Handle.CID[0] & 0x00FF0000) >> 16);
//    SD_CardInfo.SD_cid.OEM_AppliID = Temp << 8;
//
//    // Byte 2
//    Temp = (uint8_t)((SD_Handle.CID[0] & 0x000000FF00) >> 8);
//    SD_CardInfo.SD_cid.OEM_AppliID |= Temp;
//
//    // Byte 3
//    Temp = (uint8_t)(SD_Handle.CID[0] & 0x000000FF);
//    SD_CardInfo.SD_cid.ProdName1 = Temp << 24;
//
//    // Byte 4
//    Temp = (uint8_t)((SD_Handle.CID[1] & 0xFF000000) >> 24);
//    SD_CardInfo.SD_cid.ProdName1 |= Temp << 16;
//
//    // Byte 5
//    Temp = (uint8_t)((SD_Handle.CID[1] & 0x00FF0000) >> 16);
//    SD_CardInfo.SD_cid.ProdName1 |= Temp << 8;
//
//    // Byte 6
//    Temp = (uint8_t)((SD_Handle.CID[1] & 0x0000FF00) >> 8);
//    SD_CardInfo.SD_cid.ProdName1 |= Temp;
//
//    // Byte 7
//    Temp = (uint8_t)(SD_Handle.CID[1] & 0x000000FF);
//    SD_CardInfo.SD_cid.ProdName2 = Temp;
//
//    // Byte 8
//    Temp = (uint8_t)((SD_Handle.CID[2] & 0xFF000000) >> 24);
//    SD_CardInfo.SD_cid.ProdRev = Temp;
//
//    // Byte 9
//    Temp = (uint8_t)((SD_Handle.CID[2] & 0x00FF0000) >> 16);
//    SD_CardInfo.SD_cid.ProdSN = Temp << 24;
//
//    // Byte 10
//    Temp = (uint8_t)((SD_Handle.CID[2] & 0x0000FF00) >> 8);
//    SD_CardInfo.SD_cid.ProdSN |= Temp << 16;
//
//    // Byte 11
//    Temp = (uint8_t)(SD_Handle.CID[2] & 0x000000FF);
//    SD_CardInfo.SD_cid.ProdSN |= Temp << 8;
//
//    // Byte 12
//    Temp = (uint8_t)((SD_Handle.CID[3] & 0xFF000000) >> 24);
//    SD_CardInfo.SD_cid.ProdSN |= Temp;
//
//    // Byte 13
//    Temp = (uint8_t)((SD_Handle.CID[3] & 0x00FF0000) >> 16);
//    SD_CardInfo.SD_cid.Reserved1   |= (Temp & 0xF0) >> 4;
//    SD_CardInfo.SD_cid.ManufactDate = (Temp & 0x0F) << 8;
//
//    // Byte 14
//    Temp = (uint8_t)((SD_Handle.CID[3] & 0x0000FF00) >> 8);
//    SD_CardInfo.SD_cid.ManufactDate |= Temp;
//
//    // Byte 15
//    Temp = (uint8_t)(SD_Handle.CID[3] & 0x000000FF);
//    SD_CardInfo.SD_cid.CID_CRC   = (Temp & 0xFE) >> 1;
//    SD_CardInfo.SD_cid.Reserved2 = 1;
//
//    return ErrorState;
//}
//
//SD_Error_t SD_Init(void)
//{
//    static bool sdInitAttempted = false;
//    static SD_Error_t result = SD_ERROR;
//
//    if (sdInitAttempted) {
//        return result;
//    }
//
//    sdInitAttempted = true;
//
//    result = SD_DoInit();
//
//    return result;
//}
//
//SD_Error_t SD_CheckWrite(void)
//{
//    if (SD_Handle.TXCplt != 0) return SD_BUSY;
//    return SD_OK;
//}
//
//SD_Error_t SD_CheckRead(void)
//{
//    if (SD_Handle.RXCplt != 0) return SD_BUSY;
//    return SD_OK;
//}
//
//SD_Error_t SD_WriteBlocks_DMA(uint64_t WriteAddress, uint32_t *buffer, uint32_t BlockSize, uint32_t NumberOfBlocks)
//{
//    SD_Error_t ErrorState = SD_OK;
//    SD_Handle.TXCplt = 1;
//
//    if (BlockSize != 512) {
//        return SD_ERROR; // unsupported.
//    }
//
//    if ((uint32_t)buffer & 0x1f) {
//        return SD_ADDR_MISALIGNED;
//    }
//
//    // Ensure the data is flushed to main memory
//    SCB_CleanDCache_by_Addr(buffer, NumberOfBlocks * BlockSize);
//
//    HAL_StatusTypeDef status;
//    if ((status = HAL_SD_WriteBlocks_DMA(&hsd1, (uint8_t *)buffer, WriteAddress, NumberOfBlocks)) != HAL_OK) {
//        return SD_ERROR;
//    }
//
//    return ErrorState;
//}
//
//typedef struct {
//    uint32_t *buffer;
//    uint32_t BlockSize;
//    uint32_t NumberOfBlocks;
//} sdReadParameters_t;
//
//sdReadParameters_t sdReadParameters;
//
//SD_Error_t SD_ReadBlocks_DMA(uint64_t ReadAddress, uint32_t *buffer, uint32_t BlockSize, uint32_t NumberOfBlocks)
//{
//    SD_Error_t ErrorState = SD_OK;
//
//    if (BlockSize != 512) {
//        return SD_ERROR; // unsupported.
//    }
//
//    if ((uint32_t)buffer & 0x1f) {
//        return SD_ADDR_MISALIGNED;
//    }
//
//    SD_Handle.RXCplt = 1;
//
//    sdReadParameters.buffer = buffer;
//    sdReadParameters.BlockSize = BlockSize;
//    sdReadParameters.NumberOfBlocks = NumberOfBlocks;
//
//    HAL_StatusTypeDef status;
//    if ((status = HAL_SD_ReadBlocks_DMA(&hsd1, (uint8_t *)buffer, ReadAddress, NumberOfBlocks)) != HAL_OK) {
//        return SD_ERROR;
//    }
//
//    return ErrorState;
//}
//
///**
//  * @brief Tx Transfer completed callback
//  * @param hsd: SD handle
//  * @retval None
//  */
//void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
//{
//    UNUSED(hsd);
//
//    SD_Handle.TXCplt = 0;
//}
//
///**
//  * @brief Rx Transfer completed callback
//  * @param hsd: SD handle
//  * @retval None
//  */
//void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
//{
//    UNUSED(hsd);
//
//    SD_Handle.RXCplt = 0;
//
//    /*
//       the SCB_InvalidateDCache_by_Addr() requires a 32-Byte aligned address,
//       adjust the address and the D-Cache size to invalidate accordingly.
//     */
//    uint32_t alignedAddr = (uint32_t)sdReadParameters.buffer &  ~0x1F;
//    SCB_InvalidateDCache_by_Addr((uint32_t*)alignedAddr, sdReadParameters.NumberOfBlocks * sdReadParameters.BlockSize + ((uint32_t)sdReadParameters.buffer - alignedAddr));
//}
//
//void HAL_SD_ErrorCallback(SD_HandleTypeDef *hsd)
//{
//    UNUSED(hsd);
//    if (SD_Handle.RXCplt) {
//        SD_Handle.RXErrors++;
//        SD_Handle.RXCplt = 0;
//    }
//
//    if (SD_Handle.TXCplt) {
//        SD_Handle.TXErrors++;
//        SD_Handle.TXCplt = 0;
//    }
//}
//
//void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd)
//{
//    UNUSED(hsd);
//
//    SD_Handle.TXCplt = 0;
//    SD_Handle.RXCplt = 0;
//}
//
//void SDMMC1_IRQHandler(void)
//{
//    HAL_SD_IRQHandler(&hsd1);
//}
//
//void SDMMC2_IRQHandler(void)
//{
//    HAL_SD_IRQHandler(&hsd1);
//}
//
////#endif
