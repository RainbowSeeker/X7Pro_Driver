// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/16.
//
#include "magn.h"
#include "magn_rm3100.h"
#include "log.h"

static bus_status_e Magn_IntCallback(uint32_t arg)
{
    magn_t *magn = (magn_t *)arg;

    memcpy(magn->magRaw, magn->dev.segments[0].u.buffers.pRxData + magn->dev.aligenment, magn->dev.transferSize);
    return BUS_READY;
}

bool Magn_MspInit(magn_t *magn, detect_func_t detectFunc, const hw_config_t *hwConfig, const dr_config_t *drConfig)
{
    device_t *dev = &magn->dev;
    if (Device_PreConfigHardware(dev, detectFunc, hwConfig) && Device_PreConfigDataReady(dev, drConfig))
    {
        LOG_INFO("Detected Magn[%d]: %s", dev->deviceID, dev->name);
    }
    else
    {
        magn->sampleMode = SAMPLE_NO_INIT;
        LOG_ERROR("Cann't Initialize Magn Device: %s.\r\nPlease check your configuration.", dev->name);
        return false;
    }

    dev->callbackArg = (uint32_t)magn;
    dev->segments[0].callback = Magn_IntCallback;

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

}



