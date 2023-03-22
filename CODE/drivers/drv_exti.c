// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/7.
//

#include "drv_exti.h"

#define EXTI_REG_IMR (EXTI_D1->IMR1)
#define EXTI_REG_PR  (EXTI_D1->PR1)
#define EXTI_IRQ_GROUPS     7


struct exti_cb
{
    exti_cb_t cb;
    uint32_t user_data;
};
static struct exti_cb exti_cb_table[16] = {0};

static const uint8_t exti_groups[16] = {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6};
static uint32_t trigger_lookup_table[] = {
        [EXTI_RISING] = GPIO_MODE_IT_RISING,
        [EXTI_FALLING] = GPIO_MODE_IT_FALLING,
        [EXTI_BOTH] = GPIO_MODE_IT_RISING_FALLING
};



static const uint8_t exti_irqn_table[EXTI_IRQ_GROUPS] = {
        EXTI0_IRQn,
        EXTI1_IRQn,
        EXTI2_IRQn,
        EXTI3_IRQn,
        EXTI4_IRQn,
        EXTI9_5_IRQn,
        EXTI15_10_IRQn
};

#define EXTI_EVENT_MASK 0xFFFF

void exti_irq_handler(uint32_t mask)
{
    uint32_t exti_active = (EXTI_REG_IMR & EXTI_REG_PR) & mask;

    EXTI_REG_PR = exti_active;  // clear pending mask (by writing 1)

    while (exti_active)
    {
        unsigned idx = 31 - __builtin_clz(exti_active);
        if (exti_cb_table[idx].cb)
        {
            exti_cb_table[idx].cb(exti_cb_table[idx].user_data);
        }
        exti_active &= ~(1 << idx);
    }
}

#define DEFINE_EXTI_IRQ_HANDLER(name, mask)       \
    void name(void) {                             \
        os_interrupt_enter();                     \
        exti_irq_handler(mask & EXTI_EVENT_MASK); \
        os_interrupt_leave();                     \
    }


DEFINE_EXTI_IRQ_HANDLER(EXTI0_IRQHandler, 0x0001);
DEFINE_EXTI_IRQ_HANDLER(EXTI1_IRQHandler, 0x0002);
DEFINE_EXTI_IRQ_HANDLER(EXTI2_IRQHandler, 0x0004);
DEFINE_EXTI_IRQ_HANDLER(EXTI3_IRQHandler, 0x0008);
DEFINE_EXTI_IRQ_HANDLER(EXTI4_IRQHandler, 0x0010);
DEFINE_EXTI_IRQ_HANDLER(EXTI9_5_IRQHandler, 0x03e0);
DEFINE_EXTI_IRQ_HANDLER(EXTI15_10_IRQHandler, 0xfc00);


void exti_init(io_tag io, exti_cb_t cb, uint32_t user_data, int priority, exti_trigger trigger)
{
    int io_idx = io_pin_idx(io);

    if (io_idx < 0)
        return;

    exti_cb_table[io_idx].cb = cb;
    exti_cb_table[io_idx].user_data = user_data;

    exti_disable(io);
    io_init(io, trigger_lookup_table[trigger], GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0);
    HAL_NVIC_SetPriority(exti_irqn_table[exti_groups[io_idx]], priority, 0);
}

void exti_enable(io_tag io)
{
    int io_idx = io_pin_idx(io);
    uint32_t extiLine = 1 << io_idx;

    if (io_idx < 0 || !extiLine)
        return;


//    HAL_NVIC_EnableIRQ(exti_irqn_table[exti_groups[io_idx]]);
//    EXTI_REG_IMR |= extiLine;
}

void exti_disable(io_tag io)
{
    int io_idx = io_pin_idx(io);
    uint32_t extiLine = 1 << io_idx;

    if (io_idx < 0 || !extiLine)
        return;

    HAL_NVIC_DisableIRQ(exti_irqn_table[exti_groups[io_idx]]);

    EXTI_REG_IMR &= ~extiLine;
    EXTI_REG_PR = extiLine;
}