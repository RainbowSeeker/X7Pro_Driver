
#ifndef PLANT_INTERFACE_H__
#define PLANT_INTERFACE_H__
#include <common.h>
#include "multicopter/lib/Plant.h"

#ifdef __cplusplus
extern "C" {
#endif

extern model_info_t plant_model_info;

void plant_interface_init(void);
void plant_interface_step(uint32_t timestamp);

#ifdef __cplusplus
}
#endif

#endif