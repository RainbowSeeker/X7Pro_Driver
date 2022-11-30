// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/27.
//

#include "sdcard.h"
#include "driver/dma.h"
#include "device/bus_spi.h"
#include "sdcard_impl.h"


#ifdef AFATFS_USE_INTROSPECTIVE_LOGGING
#define SDCARD_PROFILING
#endif

#define SDCARD_INIT_NUM_DUMMY_BYTES                 10
#define SDCARD_MAXIMUM_BYTE_DELAY_FOR_CMD_REPLY     8
// Chosen so that CMD8 will have the same CRC as CMD0:
#define SDCARD_IF_COND_CHECK_PATTERN                0xAB

#define SDCARD_TIMEOUT_INIT_MILLIS                  200
#define SDCARD_MAX_CONSECUTIVE_FAILURES             8

/* SPI_CLOCK_INITIALIZATION (256) is the slowest (Spec calls for under 400KHz) */
#define SDCARD_SPI_INITIALIZATION_CLOCK_DIVIDER     SPI_CLOCK_INITIALIZATION

/* Operational speed <= 25MHz */
#define SDCARD_SPI_FULL_SPEED_CLOCK_DIVIDER         SPI_CLOCK_FAST

/* Break up 512-byte SD card sectors into chunks of this size when writing without DMA to reduce the peak overhead
 * per call to sdcard_poll().
 */
#define SDCARD_NON_DMA_CHUNK_SIZE                   256

sdcard_t sdcard;

//STATIC_ASSERT(sizeof(sdcardCSD_t) == 16, sdcard_csd_bitfields_didnt_pack_properly);

static void sdcardInsertionDetectInit(const sdcardConfig_t *config)
{
    if (config->cardDetectTag.port) {
        sdcard.cardDetectPin = config->cardDetectTag;
        sdcard.detectionInverted = config->cardDetectInverted;
    } else {
        sdcard.cardDetectPin.port = NULL;
        sdcard.detectionInverted = false;
    }

    if (sdcard.cardDetectPin.port) {
        IO_Init(sdcard.cardDetectPin, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0);
    }
}

/**
 * Detect if a SD card is physically present in the memory slot.
 */
bool sdcard_isInserted(void)
{
    bool result = true;
    if (sdcard.cardDetectPin.port) {
        result = IO_Read(sdcard.cardDetectPin) != 0;
        if (sdcard.detectionInverted) {
            result = !result;
        }
    }
    return result;
}

/**
 * Dispatch
 */
sdcardVTable_t *sdcardVTable;

void sdcard_preInit(const sdcardConfig_t *config)
{
#ifdef USE_SDCARD_SPI
    sdcardSpiVTable.sdcard_preInit(config);
#else
    UNUSED(config);
#endif
}

void sdcard_init(const sdcardConfig_t *config)
{
    sdcardInsertionDetectInit(config);

    switch (config->mode) {
#ifdef USE_SDCARD_SPI
        case SDCARD_MODE_SPI:
        sdcardVTable = &sdcardSpiVTable;
        break;
#endif
//#ifdef USE_SDCARD_SDIO
        case SDCARD_MODE_SDIO:
        sdcardVTable = &sdcardSdioVTable;
        break;
//#endif
        default:
            break;
    }

    if (sdcardVTable) {
        sdcardVTable->sdcard_init(config, NULL);
    }
}

bool sdcard_readBlock(uint32_t blockIndex, uint8_t *buffer, sdcard_operationCompleteCallback_c callback, uint32_t callbackData)
{
    return sdcardVTable->sdcard_readBlock(blockIndex, buffer, callback, callbackData);
}

sdcardOperationStatus_e sdcard_beginWriteBlocks(uint32_t blockIndex, uint32_t blockCount)
{
    return sdcardVTable->sdcard_beginWriteBlocks(blockIndex, blockCount);
}

sdcardOperationStatus_e sdcard_writeBlock(uint32_t blockIndex, uint8_t *buffer, sdcard_operationCompleteCallback_c callback, uint32_t callbackData)
{
    return sdcardVTable->sdcard_writeBlock(blockIndex, buffer, callback, callbackData);
}

bool sdcard_poll(void)
{
    // sdcard_poll is called from taskMain() via afatfs_poll() and  for USE_SDCARD.
    if (sdcardVTable) {
        return sdcardVTable->sdcard_poll();
    } else {
        return false;
    }
}

bool sdcard_isFunctional(void)
{
    // sdcard_isFunctional is called from multiple places, including the case of hardware implementation
    // without a detect pin in which case sdcard_isInserted() always returns true.
    if (sdcardVTable) {
        return sdcardVTable->sdcard_isFunctional();
    } else {
        return false;
    }
}

bool sdcard_isInitialized(void)
{
    return sdcardVTable->sdcard_isInitialized();
}

const sdcardMetadata_t* sdcard_getMetadata(void)
{
    return sdcardVTable->sdcard_getMetadata();
}