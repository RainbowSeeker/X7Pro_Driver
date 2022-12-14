#include <common.h>

//#include "hal/systick/systick.h"
#include "module/system/systime.h"
#include "sys.h"

typedef struct
{
    volatile uint32_t msPeriod; /* current time in ms */
    uint32_t msPerPeriod;       /* ms count for each period (SysTick_Handler fire) */
} systime_t;

static systime_t __systime;
static light_device_t systick_dev;

/**
 * @brief Systick ISR callback
 *
 */
static void systick_isr_cb(void)
{
    __systime.msPeriod += __systime.msPerPeriod;
}

/**
 * @brief Check if the period of time has elapsed
 *
 * @param timetag Time tag which stores the period and time information
 * @return uint8_t 1 indicates true
 */
uint8_t check_timetag(TimeTag *timetag)
{
    uint32_t now = systime_now_ms();

    if (timetag->period > 0 && now - timetag->tag >= timetag->period)
    {
        timetag->tag = now;
        return 1;
    }
    return 0;
}

/**
 * @brief Check if the period of time has elapsed with specified time now
 *
 * @param timetag Time tag which stores the period and time information
 * @param now Time now in ms
 * @return uint8_t uint8_t 1 indicates true
 */
uint8_t check_timetag2(TimeTag *timetag, uint32_t now)
{
    if (timetag->period && now - timetag->tag >= timetag->period)
    {
        timetag->tag = now;
        return 1;
    }
    return 0;
}

/**
 * @brief Check if the period of time has elapsed with specified time now and period
 *
 * @param timetag Time tag which stores the period and time information
 * @param now Time now in ms
 * @param period Period in ms
 * @return uint8_t uint8_t 1 indicates true
 */
uint8_t check_timetag3(TimeTag *timetag, uint32_t now, uint32_t period)
{
    if (period > 0 && now - timetag->tag >= period)
    {
        timetag->tag = now;
        return 1;
    }
    return 0;
}

/**
 * @brief Get current systime in us
 *
 * @return uint64_t systime in us
 */
uint64_t systime_now_us(void)
{
//    uint32_t systick_us = 0;
//    uint64_t time_now_ms;
//    uint32_t level;
//
//    light_device_read(systick_dev, SYSTICK_RD_TIME_US, &systick_us, sizeof(uint32_t));
//
//    level = os_hw_interrupt_disable();
//    /* atomic read */
//    time_now_ms = __systime.msPeriod;
//    os_hw_interrupt_enable(level);
//
//    return time_now_ms * (uint64_t)1000 + systick_us;
    return Sys_GetTickUs();
}

/**
 * @brief Get current systime in ms
 *
 * @return uint32_t systime in ms
 */
uint32_t systime_now_ms(void)
{
    uint32_t time_now_ms = systime_now_us() / 1e3;

    return time_now_ms;
}

/**
 * @brief Delay for us
 *
 * @param time_us Delay time in us
 */
void systime_udelay(uint32_t time_us)
{
    uint64_t target = systime_now_us() + time_us;

    while (systime_now_us() < target);
}

/**
 * @brief Delay for ms
 *
 * @param time_ms Delay time in ms
 */
inline void systime_mdelay(uint32_t time_ms)
{
    systime_udelay(time_ms * 1000);
}

/**
 * @brief Sleep for ms
 * @note In thread context it will suspend the thread for specific milliseconds,
 *       otherwise it will just do normal delay.
 *
 * @param time_ms Sleep time in ms
 */
void systime_msleep(uint32_t time_ms)
{
    if (os_interrupt_get_nest() == 0)
    {
        os_delay(time_ms);
    }
    else
    {
        systime_mdelay(time_ms);
    }
}

/**
 * @brief Initialize systime module
 *
 * @return err_t E_OK indicates success
 */
err_t systime_init(void)
{
//    systick_dev_t systick_device;
//
//    systick_dev = light_device_find("systick");
//
//    if (systick_dev == NULL) {
//        return E_RROR;
//    }
//
//    if (light_device_open(systick_dev, DEVICE_FLAG_RDONLY) != E_OK) {
//        return E_RROR;
//    }
//
//    systick_device = (systick_dev_t)systick_dev;
//
//    __systime.msPeriod = 0;
//    __systime.msPerPeriod = systick_device->ticks_per_isr / systick_device->ticks_per_us / 1e3;
//
//    systick_device->systick_isr_cb = systick_isr_cb;
//
//    ASSERT(__systime.msPerPeriod > 0);

    return E_OK;
}
