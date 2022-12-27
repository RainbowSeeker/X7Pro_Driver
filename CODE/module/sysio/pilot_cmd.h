
#ifndef PILOT_CMD_H__
#define PILOT_CMD_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    STICK_YAW = 0,
    STICK_THRO = 1,
    STICK_ROLL = 2,
    STICK_PITCH = 3,
} stick_enum;

typedef struct {
    int8_t mode;
    int8_t chan_dim;
    int8_t* channel;
    int16_t* range;
} pilot_mode_config;

typedef struct {
    int32_t cmd;
    int8_t chan_dim;
    int8_t* channel;
    int16_t* range;
    uint8_t _set;
} pilot_event_cmd_t;

typedef struct {
    int32_t cmd;
    int8_t chan_dim;
    int8_t* channel;
    int16_t* range;
} pilot_status_cmd_t;

err_t pilot_cmd_init(void);
err_t pilot_cmd_collect(void);
err_t pilot_cmd_set_device(const char* dev_name);
err_t pilot_cmd_set_chan_num(uint8_t chan_num);
err_t pilot_cmd_map_stick(uint8_t yaw_chan, uint8_t thro_chan, uint8_t roll_chan, uint8_t pitch_chan);
uint8_t pilot_cmd_get_stick_chan(stick_enum stick);

#ifdef __cplusplus
}
#endif

#endif