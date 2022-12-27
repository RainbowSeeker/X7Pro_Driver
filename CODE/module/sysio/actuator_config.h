

#ifndef ACTUATOR_CONFIG_H__
#define ACTUATOR_CONFIG_H__

#include <common.h>

#include "module/toml/toml.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t freq;
} act_pwm_drv_config;

typedef struct {
    uint16_t speed;
    bool telem_req;
} act_dshot_drv_config;

typedef struct {
    char* protocol;
    char* name;
    void* config;
} actuator_device_info;

typedef struct {
    char* from;
    char* to;
    uint8_t map_size;
    uint8_t from_map[16]; /* channel mapping start from 1 */
    uint8_t to_map[16];   /* channel mapping start from 1 */
} actuator_mapping;

/* toml configuration */
err_t actuator_toml_config(toml_table_t* table);
uint8_t actuator_toml_get_device_num(void);
uint8_t actuator_toml_get_mapping_num(void);
actuator_device_info* actuator_toml_get_device_list(void);
actuator_mapping* actuator_toml_get_mapping_list(void);

#ifdef __cplusplus
}
#endif

#endif /* ACTUATOR_CONFIG_H__ */
