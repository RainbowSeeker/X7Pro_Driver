// Copyright (c) 2022 By RainbowSeeker.

#include <common.h>
#include "hal/systick/systick.h"

static systick_dev_t _systick_dev;
uint32_t _ticksPerUs; /* tick count for 1us */


static void _set_systick_freq(uint32_t freq)
{
    uint32_t ClockFreq;
    uint32_t TicksNum;

    ASSERT(freq > 0);
    ASSERT(_systick_dev != NULL);

    ClockFreq = SystemCoreClock;
    TicksNum = ClockFreq / freq;

    _systick_dev->ticks_per_us = ClockFreq / 1e6;
    _systick_dev->ticks_per_isr = TicksNum;
}

static err_t systick_configure(systick_dev_t systick, struct systick_configure* cfg)
{
    _set_systick_freq(cfg->tick_freq);
    systick->config = *cfg;

    return E_OK;
}

static uint32_t systick_read(systick_dev_t systick)
{
    return (SysTick->LOAD - SysTick->VAL) / systick->ticks_per_us;
}

const static struct systick_ops _systick_ops = {
    systick_configure,
    systick_read
};

err_t drv_systick_init(void)
{
    static struct systick_device systick_dev = {
        .ops = &_systick_ops,
        .config = SYSTICK_CONFIG_DEFAULT,
        .systick_isr_cb = NULL
    };

    _systick_dev = &systick_dev;

    _set_systick_freq(systick_dev.config.tick_freq);

    return hal_systick_register(&systick_dev, "systick", DEVICE_FLAG_RDONLY, NULL);
}
