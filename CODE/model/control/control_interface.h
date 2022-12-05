
#ifndef CONTROL_INTERFACE_H__
#define CONTROL_INTERFACE_H__
#include <common.h>
#include "base_controller/lib/Controller.h"

#ifdef __cplusplus
extern "C" {
#endif

extern model_info_t control_model_info;

void control_interface_init(void);
void control_interface_step(uint32_t timestamp);

#ifdef __cplusplus
}
#endif

#endif