

#ifndef PILOT_CMD_CONFIG_H__
#define PILOT_CMD_CONFIG_H__

#include <common.h>

#include "module/toml/toml.h"

#ifdef __cplusplus
extern "C" {
#endif

/* toml configuration */
err_t pilot_cmd_toml_config(toml_table_t* table);

#ifdef __cplusplus
}
#endif

#endif
