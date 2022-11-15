// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#include "gpio.h"
#include "ledbeep.h"
#include "dma.h"
#include "mdma.h"
#include "bus_spi.h"
#include "sensor.h"

void Initialize(void)
{
    MX_GPIO_Init();
    EXTI_Init();
    LED_BEEP_Init();
//    MX_DMA_Init();
//    MX_MDMA_Init();
    Print_Init();
//    COM_Init();

    SPI_Init();
}