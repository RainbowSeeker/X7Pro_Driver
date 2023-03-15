

#ifndef MAVPROXY_CONFIG_H__
#define MAVPROXY_CONFIG_H__

#include <common.h>

#include "module/toml/toml.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t baudrate;
} mavproxy_serial_dev_config;

typedef struct {
    char* type;
    char* name;
    void* config;
} mavproxy_device_info;

/* toml configuration */
err_t mavproxy_toml_config(toml_table_t* table);
err_t mavproxy_get_devinfo(device_t dev, mavproxy_device_info* info);

int get_device_num(void);
mavproxy_device_info* get_device_list(void);

#ifdef __cplusplus
}
#endif

#endif
