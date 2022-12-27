// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/12.
//

#include <memory.h>
#include "exti.h"

typedef struct {
    exti_callback_rec_t *handler;
} extiChannelRec_t;

extiChannelRec_t extiChannelRecs[16] = {0};

#define EXTI_REG_IMR (EXTI_D1->IMR1)
#define EXTI_REG_PR  (EXTI_D1->PR1)
// IRQ grouping, same on F40x, F7xx, H7xx and G4xx.
#define EXTI_IRQ_GROUPS 7
//                                      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
static const uint8_t extiGroups[16] = { 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6 };
//static uint8_t extiGroupPriority[EXTI_IRQ_GROUPS];

static uint32_t triggerLookupTable[] = {
        [EXTI_RISING] = GPIO_MODE_IT_RISING,
        [EXTI_FALLING] = GPIO_MODE_IT_FALLING,
        [EXTI_BOTH] = GPIO_MODE_IT_RISING_FALLING
};

static const uint8_t extiGroupIRQn[EXTI_IRQ_GROUPS] = {
        EXTI0_IRQn,
        EXTI1_IRQn,
        EXTI2_IRQn,
        EXTI3_IRQn,
        EXTI4_IRQn,
        EXTI9_5_IRQn,
        EXTI15_10_IRQn
};

void EXTI_Init(void)
{
//    memset(extiChannelRecs, 0, sizeof(extiChannelRecs));
//    memset(extiGroupPriority, 0xff, sizeof(extiGroupPriority));
}

void EXTI_Disable(io_tag io)
{
    uint32_t extiLine = IO_EXTI_Line(io);

    if (!extiLine) {
        return;
    }

    EXTI_REG_IMR &= ~extiLine;
    EXTI_REG_PR = extiLine;
}

void EXTI_Enable(io_tag io)
{
    uint32_t extiLine = IO_EXTI_Line(io);

    if (!extiLine) {
        return;
    }

    EXTI_REG_IMR |= extiLine;

}

void EXTI_Config(io_tag io, exti_callback_rec_t *cb, int irqPriority, exti_trigger_t trigger)
{
    int chIdx = io_pin_idx(io);

    if (chIdx < 0) {
        return;
    }

    int group = extiGroups[chIdx];

    extiChannelRec_t *rec = &extiChannelRecs[chIdx];
    rec->handler = cb;

    EXTI_Disable(io);

    io_init(io, (MODE_INPUT | EXTI_IT | triggerLookupTable[trigger]), GPIO_NOPULL, GPIO_SPEED_FREQ_LOW,  0);

    HAL_NVIC_SetPriority(extiGroupIRQn[group], irqPriority, 0);
    HAL_NVIC_EnableIRQ(extiGroupIRQn[group]);
}

#define EXTI_EVENT_MASK 0xFFFF // first 16 bits only, see also definition of extiChannelRecs.

void EXTI_IRQHandler(uint32_t mask)
{
    uint32_t exti_active = (EXTI_REG_IMR & EXTI_REG_PR) & mask;

    EXTI_REG_PR = exti_active;  // clear pending mask (by writing 1)

    while (exti_active) {
        unsigned idx = 31 - __builtin_clz(exti_active);
//        uint32_t mask = 1 << idx;
        if (extiChannelRecs[idx].handler)
        {
            extiChannelRecs[idx].handler->fn(extiChannelRecs[idx].handler);
        }
        exti_active &= ~(1 << idx);
    }
}

#define _EXTI_IRQ_HANDLER(name, mask)            \
    void name(void) {                            \
        EXTI_IRQHandler(mask & EXTI_EVENT_MASK); \
    }                                            \
    struct dummy                                 \
    /**/

//_EXTI_IRQ_HANDLER(EXTI0_IRQHandler, 0x0001);
//_EXTI_IRQ_HANDLER(EXTI1_IRQHandler, 0x0002);
//_EXTI_IRQ_HANDLER(EXTI2_IRQHandler, 0x0004);
//
//_EXTI_IRQ_HANDLER(EXTI3_IRQHandler, 0x0008);
//_EXTI_IRQ_HANDLER(EXTI4_IRQHandler, 0x0010);
//_EXTI_IRQ_HANDLER(EXTI9_5_IRQHandler, 0x03e0);
//_EXTI_IRQ_HANDLER(EXTI15_10_IRQHandler, 0xfc00);
