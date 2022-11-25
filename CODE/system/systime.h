#ifndef SYSTIME_H__
#define SYSTIME_H__

#include "sys.h"
#ifdef __cplusplus
extern "C" {
#endif

#define TICKS_FROM_MS(_ms) ((RT_TICK_PER_SECOND * _ms + 999) / 1000)

typedef struct {
    uint32_t tag;
    uint32_t period;
} TimeTag;

#define DEFINE_TIMETAG(_name, _period)   \
    static TimeTag __timetag_##_name = { \
        .tag = 0,                        \
        .period = _period                \
    }

#define TIMETAG(_name) (&__timetag_##_name)

#define PERIOD_EXECUTE(_name, _period, _operation) \
    DEFINE_TIMETAG(_name, _period);                \
    do {                                           \
        if (check_timetag(TIMETAG(_name))) {       \
            _operation                             \
        }                                          \
    } while (0)

#define PERIOD_EXECUTE2(_name, _period, _time_now, _operation) \
    DEFINE_TIMETAG(_name, _period);                            \
    do {                                                       \
        if (check_timetag2(TIMETAG(_name), _time_now)) {       \
            _operation                                         \
        }                                                      \
    } while (0)

#define PERIOD_EXECUTE3(_name, _period, _time_now, _operation)    \
    DEFINE_TIMETAG(_name, 0);                                     \
    do {                                                          \
        if (check_timetag3(TIMETAG(_name), _time_now, _period)) { \
            _operation                                            \
        }                                                         \
    } while (0)

#define WAIT_TIMEOUT(_cond, _timeout_us, _opt)               \
    do {                                                     \
        uint64_t start = systime_now_us();                   \
        uint8_t timeout = 1;                                 \
        while ((systime_now_us() - start) < (_timeout_us)) { \
            if (!(_cond)) {                                  \
                timeout = 0;                                 \
                break;                                       \
            }                                                \
        }                                                    \
        if (timeout) {                                       \
            _opt                                             \
        }                                                    \
    } while (0)

#define WAIT_TIMEOUT2(_cond, _break_cond, _timeout_us, _opt) \
    do {                                                     \
        uint64_t start = systime_now_us();                   \
        uint8_t timeout = 1;                                 \
        while ((systime_now_us() - start) < (_timeout_us)) { \
            if (!(_cond)) {                                  \
                timeout = 0;                                 \
                break;                                       \
            }                                                \
            if ((_break_cond)) {                             \
                break;                                       \
            }                                                \
        }                                                    \
        if (timeout) {                                       \
            _opt                                             \
        }                                                    \
    } while (0)

uint64_t systime_now_us(void);
uint32_t systime_now_ms(void);
void systime_udelay(uint32_t delay);
void systime_mdelay(uint32_t time_ms);
void systime_msleep(uint32_t time_ms);
uint8_t check_timetag(TimeTag* timetag);
uint8_t check_timetag2(TimeTag* timetag, uint32_t now);
uint8_t check_timetag3(TimeTag* timetag, uint32_t now, uint32_t period);

#ifdef __cplusplus
}
#endif

#endif
