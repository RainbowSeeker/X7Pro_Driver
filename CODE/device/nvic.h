// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/11.
//

#ifndef X7PRO_DRIVER_NVIC_H
#define X7PRO_DRIVER_NVIC_H

//!!!warining!!!  只有抢占优先级， 无相应优先级
//prio must be > 5 due to rtos
#define NVIC_PRIO_SPI_DMA           6
#define NVIC_PRIO_UART              14
#define NVIC_PRIO_UART_DMA          7
#define NVIC_PRIO_EXTI              15


#define NVIC_PRIO_MAX                 NVIC_BUILD_PRIORITY(5)


#define NVIC_BUILD_PRIORITY(base)     NVIC_EncodePriority(NVIC_GetPriorityGrouping(),base, 0)

#endif //X7PRO_DRIVER_NVIC_H
