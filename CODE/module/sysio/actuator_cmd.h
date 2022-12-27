
#ifndef ACTUATOR_CMD_H__
#define ACTUATOR_CMD_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

err_t send_actuator_cmd(void);
err_t send_hil_actuator_cmd(void);
err_t actuator_init(void);

#ifdef __cplusplus
}
#endif

#endif