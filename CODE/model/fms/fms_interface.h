
#ifndef FMS_INTERFACE_H__
#define FMS_INTERFACE_H__
#include <common.h>
#include "base_fms/lib/FMS.h"

#ifdef __cplusplus
extern "C" {
#endif

extern model_info_t fms_model_info;

void fms_interface_init(void);
void fms_interface_step(uint32_t timestamp);

#ifdef __cplusplus
}
#endif

#endif