// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/10.
//

#include "hw_config.h"
#include "stm32h7xx_hal.h"


const gyro_config_t gyroConfig[GYRO_NUM] = {
#ifdef USE_GYRO_SPI_ADIS16470
        {.name = "ADIS16470", .device = DEV_SPI1,
            .csPin = {.port = GPIOF, .pin = GPIO_PIN_10},
            .extiPin = {.port = GPIOE, .pin = GPIO_PIN_7}},
#endif
#ifdef USE_GYRO_SPI_ICM42688P
        {.name = "ICM42688P", .device = DEV_SPI4,
            .csPin = {.port = GPIOA, .pin = GPIO_PIN_15},
            .extiPin = {.port = GPIOB, .pin = GPIO_PIN_15}},
#endif
};

const spi_hw_t spiHardware[SPI_NUM] = {
#ifdef USE_SPI1
        {
            .instance = SPI1,
            .sck = {.port = GPIOG, .pin = GPIO_PIN_11}, .sckAF = GPIO_AF5_SPI1,
            .miso = {.port = GPIOA, .pin = GPIO_PIN_6}, .misoAF = GPIO_AF5_SPI1,
            .mosi = {.port = GPIOD, .pin = GPIO_PIN_7}, .mosiAF = GPIO_AF5_SPI1,
        },
#endif
#ifdef USE_SPI2
        {
                .instance = SPI2,
                .sck = {.port = GPIOI, .pin = GPIO_PIN_1}, .sckAF = GPIO_AF5_SPI2,
                .miso = {.port = GPIOI, .pin = GPIO_PIN_2}, .misoAF = GPIO_AF5_SPI2,
                .mosi = {.port = GPIOI, .pin = GPIO_PIN_3}, .mosiAF = GPIO_AF5_SPI2,
        },
#endif
#ifdef USE_SPI3
        {
                NULL
        },
#endif
#ifdef USE_SPI4
        {
                .instance = SPI4,
                .sck = {.port = GPIOE, .pin = GPIO_PIN_2}, .sckAF = GPIO_AF5_SPI4,
                .miso = {.port = GPIOE, .pin = GPIO_PIN_13}, .misoAF = GPIO_AF5_SPI4,
                .mosi = {.port = GPIOE, .pin = GPIO_PIN_6}, .mosiAF = GPIO_AF5_SPI4,
        },
#endif
#ifdef USE_SPI5
        {
                .instance = SPI4,
                .sck = {.port = GPIOF, .pin = GPIO_PIN_7},
                .miso = {.port = GPIOF, .pin = GPIO_PIN_8},
                .mosi = {.port = GPIOF, .pin = GPIO_PIN_9},
        },
#endif
#ifdef USE_SPI6
        {
            .instance = SPI6,
            .sck = {.port = GPIOG, .pin = GPIO_PIN_13},
            .miso = {.port = GPIOG, .pin = GPIO_PIN_12},
            .mosi = {.port = GPIOA, .pin = GPIO_PIN_7},
        }
#endif
};
