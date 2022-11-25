#include "systime.h"

typedef struct {
    volatile uint32_t msPeriod; /* current time in ms */
    uint32_t msPerPeriod;       /* ms count for each period (SysTick_Handler fire) */
} systime_t;

static systime_t __systime;

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
uint8_t check_timetag(TimeTag* timetag)
{
    uint32_t now = systime_now_ms();

    if (timetag->period > 0 && now - timetag->tag >= timetag->period) {
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
uint8_t check_timetag2(TimeTag* timetag, uint32_t now)
{
    if (timetag->period && now - timetag->tag >= timetag->period) {
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
uint8_t check_timetag3(TimeTag* timetag, uint32_t now, uint32_t period)
{
    if (period > 0 && now - timetag->tag >= period) {
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
    return Sys_GetTickUs();
}

/**
 * @brief Get current systime in ms
 *
 * @return uint32_t systime in ms
 */
uint32_t systime_now_ms(void)
{
    return HAL_GetTick();
}

/**
 * @brief Delay for us
 *
 * @param time_us Delay time in us
 */
void systime_udelay(uint32_t time_us)
{
    uint64_t target = systime_now_us() + time_us;

    while (systime_now_us() < target)
        ;
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


