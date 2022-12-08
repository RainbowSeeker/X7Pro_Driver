//
//// Copyright (c) 2022 By RainbowSeeker.
//
//#include <common.h>
//
//#include "hal/systick/systick.h"
//
//static systick_dev_t _systick_dev;
//uint32_t _ticksPerUs; /* tick count for 1us */
//
///**
// * This is the systick timer interrupt service routine.
// *
// */
//void SysTick_Handler(void)
//{
//    /* enter interrupt */
//    rt_interrupt_enter();
//
//    hal_systick_isr(_systick_dev);
//
//    rt_tick_increase();
//
//    /* leave interrupt */
//    rt_interrupt_leave();
//}
//
//static void _set_systick_freq(uint32_t freq)
//{
//    RCC_ClocksTypeDef rcc_clocks;
//    uint32_t cnts;
//
//    RCC_GetClocksFreq(&rcc_clocks);
//
//    cnts = (uint32_t)rcc_clocks.HCLK_Frequency / freq;
//
//    if (_systick_dev) {
//        _systick_dev->ticks_per_us = rcc_clocks.HCLK_Frequency / 1e6;
//        _systick_dev->ticks_per_isr = cnts;
//    }
//
//    SysTick_Config(cnts);
//    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
//}
//
//static rt_err_t systick_configure(systick_dev_t systick, struct systick_configure* cfg)
//{
//    _set_systick_freq(cfg->tick_freq);
//
//    systick->config = *cfg;
//
//    return E_OK;
//}
//
//static uint32_t systick_read(systick_dev_t systick)
//{
//    return (SysTick->LOAD - SysTick->VAL) / systick->ticks_per_us;
//}
//
//const static struct systick_ops _systick_ops = {
//    systick_configure,
//    systick_read
//};
//
//rt_err_t drv_systick_init(void)
//{
//    RCC_ClocksTypeDef rcc_clocks;
//    static struct systick_device systick_dev = {
//        .ops = &_systick_ops,
//        .config = SYSTICK_CONFIG_DEFAULT,
//        .systick_isr_cb = NULL
//    };
//
//    _systick_dev = &systick_dev;
//
//    _set_systick_freq(systick_dev.config.tick_freq);
//
//    RCC_GetClocksFreq(&rcc_clocks);
//
//    return hal_systick_register(&systick_dev, "systick", RT_DEVICE_FLAG_RDONLY, NULL);
//}
