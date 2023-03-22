// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/8.
//

#ifndef IOCONFIG_H
#define IOCONFIG_H

#include "stm32h7xx_hal.h"

// Keep this in sync with TEST_PIN_NAMES below.
enum pin_enum {
    /* PAx*/
    PA0 = 0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
    /* PBx*/
    PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
    /* PCx*/
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
    /* PDx*/
    PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,
    /* PEx*/
    PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15,
    /* PFx*/
    PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7, PF8, PF9, PF10, PF11, PF12, PF13, PF14, PF15,
    /* PGx*/
    PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13, PG14, PG15,
    /* PHx*/
    PH0, PH1, PH2, PH3, PH4, PH5, PH6, PH7, PH8, PH9, PH10, PH11, PH12, PH13, PH14, PH15,
    /* PIx*/
    PI0, PI1, PI2, PI3, PI4, PI5, PI6, PI7, PI8, PI9, PI10, PI11, PI12, PI13, PI14, PI15,
    /* PJx*/
    PJ0, PJ1, PJ2, PJ3, PJ4, PJ5, PJ6, PJ7, PJ8, PJ9, PJ10, PJ11, PJ12, PJ13, PJ14, PJ15,
};

enum io_state_e{
    IO_LOW = 0U,
    IO_HIGH
};

typedef enum pin_enum io_tag;


#define CS_CONFIG       GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_MEDIUM, 0


enum io_state_e io_read(io_tag io);

void io_set(io_tag io, enum io_state_e ioState);

int io_init(io_tag io, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate);

void io_deinit(io_tag io);

int io_pin_idx(io_tag io);

uint32_t IO_EXTI_Line(io_tag io);

#endif //IOCONFIG_H
