// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "io.h"

io_state_e IO_Read(io_t io)
{
    return (io_state_e)HAL_GPIO_ReadPin(io.port, io.pin);
}

void IO_Set(io_t io, io_state_e ioState)
{
    HAL_GPIO_WritePin(io.port, io.pin, (GPIO_PinState)ioState);
}


int IO_Init(io_t io, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate)
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

void IO_DeInit(io_t io)
{
    HAL_GPIO_DeInit(io.port, io.pin);
}
