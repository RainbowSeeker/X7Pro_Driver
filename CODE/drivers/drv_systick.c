// Copyright (c) 2022 By RainbowSeeker.

#include <common.h>
#include "hal/systick/systick.h"

static systick_dev_t _systick_dev;
uint32_t _ticksPerUs; /* tick count for 1us */

void SysTick_Handler(void)
{
    uwTick += (uint32_t)uwTickFreq;
    hal_systick_isr(_systick_dev);
}

static void _set_systick_freq(uint32_t freq)
{
    //don't modify systick_freq for this function.
    ASSERT(freq == TICK_PER_SECOND);

    if (_systick_dev) {
        _systick_dev->ms_per_isr = 1e3 / TICK_PER_SECOND;
    }

}

static err_t systick_configure(systick_dev_t systick, struct systick_configure* cfg)
{
    _set_systick_freq(cfg->tick_freq);
    systick->config = *cfg;

    return E_OK;
}

static uint32_t systick_read(systick_dev_t systick)
{
    extern TIM_HandleTypeDef htim1;
    return htim1.Instance->CNT * 1000 / htim1.Instance->ARR;
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
