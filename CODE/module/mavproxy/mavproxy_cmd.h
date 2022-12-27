

#ifndef MAVPROXY_CMD_H__
#define MAVPROXY_CMD_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MAVCMD_CALIBRATION_GYR = 0,
    MAVCMD_CALIBRATION_ACC,
    MAVCMD_CALIBRATION_MAG,
    MAVCMD_CALIBRATION_LEVEL,
    MAVCMD_STREAM_SESSION,
    MAVCMD_ITEM_NUM // do not remove it
} MavCmd_ID;

void mavproxy_cmd_exec(void);
void mavproxy_cmd_set(MavCmd_ID cmd, void* data);
void mavproxy_cmd_reset(MavCmd_ID cmd);

#ifdef __cplusplus
}
#endif

#endif
