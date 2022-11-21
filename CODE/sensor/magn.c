// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/16.
//
#include "magn.h"
#include "magn_rm3100.h"
#include "cli/log.h"

static bus_status_e Magn_IntCallback(uint32_t arg)
{
    magn_t *magn = (magn_t *)arg;

    memcpy(magn->magRaw, magn->dev.segments[0].u.buffers.pRxData + magn->dev.aligenment, magn->dev.transferSize);
    return BUS_READY;
}

bool Magn_MspInit(magn_t *magn, detect_func_t detectFunc, const hw_config_t *hwConfig, const dr_config_t *drConfig)
{
    device_t *dev = &magn->dev;
    if (!Device_PreConfig(dev, detectFunc, hwConfig, drConfig))
    {
        magn->sampleMode = SAMPLE_NO_INIT;
        return false;
    }

    Device_BindRxCallback(dev, Magn_IntCallback, (uint32_t)magn);

    if (magn->dev.extiPin.port)
    {
        magn->sampleMode = !SPI_UseDMA(dev);
    }
    else    magn->sampleMode = SAMPLE_NO_INT;

    return true;
}
void Magn_StartSample(magn_t *magn)
{
    EXTI_Enable(magn->dev.extiPin);
}

void Magn_StopSample(magn_t *magn)
{
    EXTI_Disable(magn->dev.extiPin);
}


bool Magn_Init(magn_t *magn)
{
    if (magn->init(magn))
    {
        LOG_INFO("Initialized Magn[%d]: %s", magn->dev.deviceID, magn->dev.name);
    }
    else
    {
        LOG_ERROR("Cann't Initialize Magn Device: %s.\r\nPlease check your configuration.", magn->dev.name);
        return false;
    }

    Magn_StartSample(magn);
    return true;
}


bool Magn_Update(magn_t *magn)
{
    switch (magn->sampleMode)
    {
        case SAMPLE_NO_INT:
        {
            SPI_Sequence(&magn->dev, &magn->dev.segments[0]);

            // Wait for completion
            SPI_Wait(&magn->dev);
        }
        case SAMPLE_EXTI_INT:
        case SAMPLE_EXTI_INT_DMA:
            if (magn->updateCallback)
            {
                magn->updateCallback(magn);
            }
        default:
            break;
    }

    return true;
}




