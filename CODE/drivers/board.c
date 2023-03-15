// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/25.
//
#include <common.h>

#include "board.h"
#include "toml/toml.h"
#include "console/console_config.h"
#include "mavproxy/mavproxy_config.h"
#include "utils/devmq.h"
#include "sysio/gcs_cmd.h"
#include "sysio/mission_data.h"
#include "sysio/actuator_cmd.h"
#include "sysio/auto_cmd.h"
#include "sysio/pilot_cmd.h"
#include "sysio/pilot_cmd_config.h"
#include "sysio/actuator_config.h"
#include "pmu/power_manager.h"

static toml_table_t* __toml_root_tab = NULL;
#define SYS_CONFIG_FILE "/sys/sysconfig.toml"


static err_t bsp_parse_toml_sysconfig(toml_table_t* root_tab)
{
    err_t err =E_OK;
    toml_table_t* sub_tab;
    const char* key;
    const char* raw;
    char* target;
    int i;

    if (root_tab == NULL) {
        return E_RROR;
    }

    /* target should be defined and match with bsp */
    if ((raw = toml_raw_in(root_tab, "target")) != 0) {
        if (toml_rtos(raw, &target) != 0) {
            console_printf("Error: fail to parse type value\n");
            err =E_RROR;
        }
        if (!MATCH(target, TARGET_NAME)) {
            /* check if target match */
            console_printf("Error: target name doesn't match\n");
            err =E_RROR;
        }
        free(target);
    } else {
        console_printf("Error: can not find target key\n");
        err =E_RROR;
    }

    if (err ==E_OK) {
        /* traverse all sub-table */
        for (i = 0; 0 != (key = toml_key_in(root_tab, i)); i++) {
            /* handle all sub tables */
            if (0 != (sub_tab = toml_table_in(root_tab, key))) {
                if (MATCH(key, "console")) {
                    err = console_toml_config(sub_tab);
                } else if (MATCH(key, "mavproxy")) {
                    err = mavproxy_toml_config(sub_tab);
                } else if (MATCH(key, "pilot-cmd")) {
                    err = pilot_cmd_toml_config(sub_tab);
                } else if (MATCH(key, "actuator")) {
                    err = actuator_toml_config(sub_tab);
                } else {
                    console_printf("unknown table: %s\n", key);
                }
                if (err !=E_OK) {
                    console_printf("fail to parse %s\n", key);
                }
            }
        }
    }

    /* free toml root table */
    toml_free(root_tab);

    return err;
}


void bsp_post_init()
{
    /* toml system configure */
    __toml_root_tab = toml_parse_config_file(SYS_CONFIG_FILE);
    if (!__toml_root_tab) {
        /* use default system configuration */
        __toml_root_tab = toml_parse_config_string(default_conf);
    }
    SELF_CHECK(bsp_parse_toml_sysconfig(__toml_root_tab));

    /* init rc */
    SELF_CHECK(pilot_cmd_init());

    /* init gcs */
    SELF_CHECK(gcs_cmd_init());

    /* init auto command */
    SELF_CHECK(auto_cmd_init());

    /* init mission data */
    SELF_CHECK(mission_data_init());

    /* init actuator */
    SELF_CHECK(actuator_init());

    /* start device message queue work */
    SELF_CHECK(devmq_start_work());

    /* initialize led */
//    SELF_CHECK(led_control_init());

    /* initialize power management unit */
     SELF_CHECK(pmu_init());
}