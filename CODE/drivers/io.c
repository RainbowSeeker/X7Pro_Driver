// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#include "io.h"

static GPIO_TypeDef *gpio_port_table[] = {
        GPIOA,
        GPIOB,
        GPIOC,
        GPIOD,
        GPIOE,
        GPIOF,
        GPIOG,
        GPIOH,
        GPIOI,
        GPIOJ,
};

static uint32_t gpio_pin_table[] = {
        GPIO_PIN_0,
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_10,
        GPIO_PIN_11,
        GPIO_PIN_12,
        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15,
};

enum io_state_e io_read(io_tag io) {
    return (enum io_state_e) HAL_GPIO_ReadPin(gpio_port_table[io >> 4], gpio_pin_table[io & 0x0f]);
}

void io_set(io_tag io, enum io_state_e ioState) {
    HAL_GPIO_WritePin(gpio_port_table[io >> 4] , gpio_pin_table[io & 0x0f], (GPIO_PinState) ioState);
}


int io_init(io_tag io, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate) {
    GPIO_TypeDef *port = gpio_port_table[io >> 4];

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    switch ((uint32_t) port) {
        case (uint32_t) GPIOA:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case (uint32_t) GPIOB:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case (uint32_t) GPIOC:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case (uint32_t) GPIOD:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case (uint32_t) GPIOE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
        case (uint32_t) GPIOF:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        case (uint32_t) GPIOG:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case (uint32_t) GPIOH:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        case (uint32_t) GPIOI:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
        case (uint32_t) GPIOJ:
            __HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
        default:
            return -1;
    }

    GPIO_InitStruct.Pin = gpio_pin_table[io & 0x0f];
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = speed;
    GPIO_InitStruct.Alternate = alternate;
    HAL_GPIO_Init(port, &GPIO_InitStruct);

    return 0;
}

void io_deinit(io_tag io) {
    HAL_GPIO_DeInit(gpio_port_table[io >> 4], gpio_pin_table[io & 0x0f]);
}

// zero based pin index
int io_pin_idx(io_tag io) {
    return 31 - __builtin_clz(gpio_pin_table[io & 0x0f]);  // CLZ is a bit faster than FFS
}

uint32_t IO_EXTI_Line(io_tag io) {
    return 1 << io_pin_idx(io);
}