#ifndef SYSTICK_H__
#define SYSTICK_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSTICK_RD_TIME_US          0
#define SYSTICK_CMD_SET_FREQUENCY   0x20

/* default config for systick device */
#define SYSTICK_CONFIG_DEFAULT \
    {                          \
        TICK_PER_SECOND,    \
    }

struct systick_configure {
    uint16_t tick_freq;
};

struct systick_device {
    struct device parent;
    const struct systick_ops* ops;
    struct systick_configure config;
    uint32_t ticks_per_us;
    uint32_t ticks_per_isr;
    void (*systick_isr_cb)(void);
};
typedef struct systick_device* systick_dev_t;

struct systick_ops {
    err_t (*systick_configure)(systick_dev_t systick, struct systick_configure* cfg);
    uint32_t (*systick_read)(systick_dev_t systick);
};

err_t hal_systick_register(systick_dev_t systick, const char* name, uint32_t flag, void* data);
void hal_systick_isr(systick_dev_t systick);

#ifdef __cplusplus
}
#endif

#endif
