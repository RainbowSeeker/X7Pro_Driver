#ifndef ACTUATOR_H__
#define ACTUATOR_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ACT_CMD_CHANNEL_ENABLE  0x20
#define ACT_CMD_CHANNEL_DISABLE 0x21
#define ACT_CMD_SET_PROTOCOL    0x22

enum {
    ACT_PROTOCOL_PWM = 1,
    ACT_PROTOCOL_DSHOT = 2
};

struct pwm_drv_configure {
    uint16_t pwm_freq; /* pwm frequency in hz */
};

struct dshot_drv_configure {
    uint16_t speed;   /* 600, 300, 150 */
    bool_t telem_req; /* telemetry request */
};

struct actuator_configure {
    uint8_t protocol;
    uint16_t chan_num;
    struct pwm_drv_configure pwm_config;
    struct dshot_drv_configure dshot_config;
};

struct actuator_device {
    struct device parent;
    const struct actuator_ops* ops;
    struct actuator_configure config;
    uint16_t chan_mask;
    uint16_t range[2]; /* [min, max] value */
};
typedef struct actuator_device* actuator_dev_t;

struct actuator_ops {
    err_t (*dev_config)(actuator_dev_t dev, const struct actuator_configure* cfg);
    err_t (*dev_control)(actuator_dev_t dev, int cmd, void* arg);
    size_t (*dev_read)(actuator_dev_t dev, uint16_t chan_sel, uint16_t* chan_val, size_t size);
    size_t (*dev_write)(actuator_dev_t dev, uint16_t chan_sel, const uint16_t* chan_val, size_t size);
};

err_t hal_actuator_register(actuator_dev_t dev, const char* name, uint32_t flag, void* data);

#ifdef __cplusplus
}
#endif

#endif /* ACTUATOR_H__ */