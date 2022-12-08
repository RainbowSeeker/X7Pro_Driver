// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "io.h"

io_state_e IO_Read(io_t io)
{
    return (io_state_e)HAL_GPIO_ReadPin(io.port, io.pin);
}

void io_set(io_t io, io_state_e ioState)
{
    HAL_GPIO_WritePin(io.port, io.pin, (GPIO_PinState)ioState);
}


int io_init(io_t io, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    switch ((uint32_t)io.port)
    {
        case (uint32_t)GPIOA:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case (uint32_t)GPIOB:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case (uint32_t)GPIOC:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case (uint32_t)GPIOD:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case (uint32_t)GPIOE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
        case (uint32_t)GPIOF:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        case (uint32_t)GPIOG:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case (uint32_t)GPIOH:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        case (uint32_t)GPIOI:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
        case (uint32_t)GPIOJ:
            __HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
        default:
            return -1;
    }

    GPIO_InitStruct.Pin = io.pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = speed;
    GPIO_InitStruct.Alternate = alternate;
    HAL_GPIO_Init(io.port, &GPIO_InitStruct);

    return 0;
}

void io_deinit(io_t io)
{
    HAL_GPIO_DeInit(io.port, io.pin);
}

// zero based pin index
int io_pin_idx(io_t io)
{
    if (!io.port) {
        return -1;
    }
    return 31 - __builtin_clz(io.pin);  // CLZ is a bit faster than FFS
}

uint32_t IO_EXTI_Line(io_t io)
{
    if (!io.port) {
        return 0;
    }
    return 1 << io_pin_idx(io);
}