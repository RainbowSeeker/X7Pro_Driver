// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#ifndef IOCONFIG_H
#define IOCONFIG_H
#include "stm32h7xx_hal.h"

typedef enum
{
    IO_LOW = 0U,
    IO_HIGH
} io_state_e;

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
}io_t;

#define CS_CONFIG       GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0



io_state_e IO_Read(io_t io);
void IO_Set(io_t gpio, io_state_e ioState);
int IO_Init(io_t gpio, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate);
void IO_DeInit(io_t io);
int IO_GPIOPinIdx(io_t io);
uint32_t IO_EXTI_Line(io_t io);
#endif //IOCONFIG_H
