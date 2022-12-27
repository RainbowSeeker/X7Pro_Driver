

#ifndef CONSOLE_CONFIG_H__
#define CONSOLE_CONFIG_H__

#include <common.h>

#include "module/toml/toml.h"

#ifdef __cplusplus
extern "C" {
#endif

/* toml configuration */
err_t console_toml_config(toml_table_t* table);

#ifdef __cplusplus
}
#endif

#endif
