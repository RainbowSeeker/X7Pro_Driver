/******************************************************************************
 * Copyright 2020-2021 The Firmament Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <common.h>
#include <string.h>

#include "hal/rc/rc.h"
#include "module/sysio/pilot_cmd.h"
#include "module/toml/toml.h"

#define TOML_DBG_E(...) toml_debug("Pilot_Cmd", "E", __VA_ARGS__)
#define TOML_DBG_W(...) toml_debug("Pilot_Cmd", "W", __VA_ARGS__)

#define PILOT_CMD_MAX_DEVICE_NUM 1
#define MATCH(a, b)              (strcmp(a, b) == 0)

typedef struct {
    char* type;
    char* name;
    void* config;
} pilot_cmd_device_info;

typedef struct {
    uint16_t protocol;
    uint16_t channel_num;
    float sample_time;
    int16_t range[2];
} pilot_cmd_rc_dev_config;

extern uint8_t modeNum;
extern uint8_t eventCmdNum;
extern uint8_t statusCmdNum;
extern pilot_mode_config* pilotModes;
extern pilot_event_cmd_t* pilotEventCmds;
extern pilot_status_cmd_t* pilotStatusCmds;

static pilot_cmd_device_info rcDevInfo;

static err_t pilot_cmd_parse_command(const toml_array_t* curarr)
{
    int i, j;
    toml_table_t* tab;
    toml_array_t* arr;
    int64_t ival;

    if (pilotEventCmds) {
        free(pilotEventCmds);
        pilotEventCmds = NULL;
    }

    /* first count the number of event command and status command */
    for (i = 0; 0 != (tab = toml_table_at(curarr, i)); i++) {
        if (toml_int_in(tab, "type", &ival) == 0) {
            if (ival == 1) {
                eventCmdNum++;
            } else if (ival == 2) {
                statusCmdNum++;
            } else {
                TOML_DBG_W("unknown type value: %d\n", ival);
            }
        } else {
            TOML_DBG_E("fail to parse type value\n");
            return E_RROR;
        }
    }

    /* memory allocation */
    pilotEventCmds = (pilot_event_cmd_t*)malloc(sizeof(pilot_event_cmd_t) * eventCmdNum);
    if (pilotEventCmds == NULL && eventCmdNum > 0) {
        TOML_DBG_E("event command malloc fail\n");
        return E_NOMEM;
    }

    pilotStatusCmds = (pilot_status_cmd_t*)malloc(sizeof(pilot_status_cmd_t) * statusCmdNum);
    if (pilotStatusCmds == NULL && statusCmdNum > 0) {
        TOML_DBG_E("status command malloc fail\n");
        return E_NOMEM;
    }

    /* start to parse command */
    uint16_t eventCmdIdx = 0;
    uint16_t statusCmdIdx = 0;
    for (i = 0; 0 != (tab = toml_table_at(curarr, i)); i++) {
        /* get command type */
        if (toml_int_in(tab, "type", &ival) != 0) {
            TOML_DBG_E("fail to parse type value\n");
            return E_RROR;
        }

        if (ival == 1) {
            /* parse event command */
            pilotEventCmds[eventCmdIdx]._set = 0;

            if (toml_int_in(tab, "cmd", &ival) == 0) {
                pilotEventCmds[eventCmdIdx].cmd = (int32_t)ival;
            } else {
                TOML_DBG_E("fail to parse event command\n");
                return E_RROR;
            }

            if (toml_int_in(tab, "channel", &ival) == 0) {
                /* single channel mapping */
                pilotEventCmds[eventCmdIdx].chan_dim = 1;

                pilotEventCmds[eventCmdIdx].channel = (int8_t*)malloc(pilotEventCmds[eventCmdIdx].chan_dim);
                if (pilotEventCmds[eventCmdIdx].channel) {
                    *pilotEventCmds[eventCmdIdx].channel = (int8_t)ival;
                } else {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }
            } else if ((arr = toml_array_in(tab, "channel")) != 0) {
                /* multi channel mapping */
                pilotEventCmds[eventCmdIdx].chan_dim = toml_array_nelem(arr);

                pilotEventCmds[eventCmdIdx].channel = (int8_t*)malloc(pilotEventCmds[eventCmdIdx].chan_dim);
                if (pilotEventCmds[eventCmdIdx].channel == NULL) {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }

                for (int d = 0; d < pilotEventCmds[eventCmdIdx].chan_dim; d++) {
                    if (toml_int_at(arr, d, &ival) == 0) {
                        pilotEventCmds[eventCmdIdx].channel[d] = ival;
                    } else {
                        TOML_DBG_E("fail to parse channel value\n");
                        return E_RROR;
                    }
                }
            } else {
                TOML_DBG_E("fail to get channel value\n");
                return E_RROR;
            }

            if (pilotEventCmds[eventCmdIdx].chan_dim == 1) {
                if (toml_array_value_in(tab, "range", &arr) == 0) {
                    if ((pilotEventCmds[eventCmdIdx].range = (int16_t*)malloc(pilotEventCmds[eventCmdIdx].chan_dim * 2)) == NULL) {
                        TOML_DBG_E("malloc fail\n");
                        return E_NOMEM;
                    }

                    for (j = 0; j < 2; j++) {
                        if (toml_int_at(arr, j, &ival) == 0) {
                            pilotEventCmds[eventCmdIdx].range[j] = (int16_t)ival;
                        } else {
                            TOML_DBG_E("fail to parse range\n");
                            return E_RROR;
                        }
                    }
                }
            } else if (pilotEventCmds[eventCmdIdx].chan_dim > 1) {
                toml_array_t* range_array;
                toml_array_t* arr;
                if ((range_array = toml_array_in(tab, "range")) == NULL) {
                    TOML_DBG_E("mode[%d] range parse fail\n", eventCmdIdx);
                    return E_RROR;
                }

                if (toml_array_nelem(range_array) != pilotEventCmds[eventCmdIdx].chan_dim) {
                    TOML_DBG_E("command[%d] range dim not match\n", eventCmdIdx);
                    return E_RROR;
                }

                if ((pilotEventCmds[eventCmdIdx].range = (int16_t*)malloc(pilotEventCmds[eventCmdIdx].chan_dim * 2)) == NULL) {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }

                for (int d = 0; d < pilotEventCmds[eventCmdIdx].chan_dim; d++) {
                    arr = toml_array_at(range_array, d);

                    for (int k = 0; k < 2; k++) {
                        if (toml_int_at(arr, k, &ival) == 0) {
                            pilotEventCmds[eventCmdIdx].range[d * 2 + k] = (int16_t)ival;
                        } else {
                            TOML_DBG_E("command[%d] range value parse fail\n", eventCmdIdx);
                            return E_RROR;
                        }
                    }
                }
            } else {
                TOML_DBG_E("command[%d] requires a channel mapping\n", i);
                return E_RROR;
            }

            eventCmdIdx++;
        } else if (ival == 2) {
            /* parse status command */
            if (toml_int_in(tab, "cmd", &ival) == 0) {
                pilotStatusCmds[statusCmdIdx].cmd = (int32_t)ival;
            } else {
                TOML_DBG_E("fail to parse status command\n");
                return E_RROR;
            }

            if (toml_int_in(tab, "channel", &ival) == 0) {
                /* single channel mapping */
                pilotStatusCmds[statusCmdIdx].chan_dim = 1;

                pilotStatusCmds[statusCmdIdx].channel = (int8_t*)malloc(pilotStatusCmds[statusCmdIdx].chan_dim);
                if (pilotStatusCmds[statusCmdIdx].channel) {
                    *pilotStatusCmds[statusCmdIdx].channel = (int8_t)ival;
                } else {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }
            } else if ((arr = toml_array_in(tab, "channel")) != 0) {
                /* multi channel mapping */
                pilotStatusCmds[statusCmdIdx].chan_dim = toml_array_nelem(arr);

                pilotStatusCmds[statusCmdIdx].channel = (int8_t*)malloc(pilotStatusCmds[statusCmdIdx].chan_dim);
                if (pilotStatusCmds[statusCmdIdx].channel == NULL) {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }

                for (int d = 0; d < pilotStatusCmds[statusCmdIdx].chan_dim; d++) {
                    if (toml_int_at(arr, d, &ival) == 0) {
                        pilotStatusCmds[statusCmdIdx].channel[d] = ival;
                    } else {
                        TOML_DBG_E("fail to parse rc command channel value\n");
                        return E_RROR;
                    }
                }
            } else {
                TOML_DBG_E("fail to parse status command channel\n");
                return E_RROR;
            }

            if (pilotStatusCmds[statusCmdIdx].chan_dim == 1) {
                if (toml_array_value_in(tab, "range", &arr) == 0) {
                    if ((pilotStatusCmds[statusCmdIdx].range = (int16_t*)malloc(pilotStatusCmds[statusCmdIdx].chan_dim * 2)) == NULL) {
                        TOML_DBG_E("malloc fail\n");
                        return E_NOMEM;
                    }

                    for (j = 0; j < 2; j++) {
                        if (toml_int_at(arr, j, &ival) == 0) {
                            pilotStatusCmds[statusCmdIdx].range[j] = (int16_t)ival;
                        } else {
                            TOML_DBG_E("fail to parse event command range\n");
                            return E_RROR;
                        }
                    }
                }
            } else if (pilotStatusCmds[statusCmdIdx].chan_dim > 1) {
                toml_array_t* range_array;
                toml_array_t* arr;
                if ((range_array = toml_array_in(tab, "range")) == NULL) {
                    TOML_DBG_E("mode[%d] range parse fail\n", statusCmdIdx);
                    return E_RROR;
                }

                if (toml_array_nelem(range_array) != pilotStatusCmds[statusCmdIdx].chan_dim) {
                    TOML_DBG_E("command[%d] range dim not match\n", statusCmdIdx);
                    return E_RROR;
                }

                if ((pilotStatusCmds[statusCmdIdx].range = (int16_t*)malloc(pilotStatusCmds[statusCmdIdx].chan_dim * 2)) == NULL) {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }

                for (int d = 0; d < pilotStatusCmds[statusCmdIdx].chan_dim; d++) {
                    arr = toml_array_at(range_array, d);

                    for (int k = 0; k < 2; k++) {
                        if (toml_int_at(arr, k, &ival) == 0) {
                            pilotStatusCmds[statusCmdIdx].range[d * 2 + k] = (int16_t)ival;
                        } else {
                            TOML_DBG_E("command[%d] range value parse fail\n", statusCmdIdx);
                            return E_RROR;
                        }
                    }
                }
            } else {
                TOML_DBG_E("command[%d] requires a channel mapping\n", statusCmdIdx);
                return E_RROR;
            }

            statusCmdIdx++;
        } else {
            TOML_DBG_E("unknown command type:%d\n", ival);
            return E_RROR;
        }
    }

    return E_OK;
}

static err_t pilot_cmd_parse_mode(const toml_array_t* curarr)
{
    int i, j;
    toml_table_t* tab;
    toml_array_t* arr;
    int64_t ival;

    if (pilotModes) {
        free(pilotModes);
        pilotModes = NULL;
    }

    pilotModes = (pilot_mode_config*)malloc(toml_array_nelem(curarr) * sizeof(pilot_mode_config));
    if (pilotModes == NULL) {
        TOML_DBG_E("mode malloc fail\n");
        return E_RROR;
    }

    for (i = 0; 0 != (tab = toml_table_at(curarr, i)); i++) {
        if (toml_int_in(tab, "mode", &ival) == 0) {
            pilotModes[i].mode = (int8_t)ival;
        } else {
            TOML_DBG_E("fail to parse mode\n");
            return E_RROR;
        }

        if (toml_int_in(tab, "channel", &ival) == 0) {
            /* single channel mapping */
            pilotModes[i].channel = (int8_t*)malloc(1);
            if (pilotModes[i].channel) {
                *pilotModes[i].channel = (int8_t)ival;
            } else {
                TOML_DBG_E("malloc fail\n");
                return E_NOMEM;
            }
            pilotModes[i].chan_dim = 1; // single channel mapping
        } else if ((arr = toml_array_in(tab, "channel")) != 0) {
            /* multi channel mapping */
            pilotModes[i].chan_dim = toml_array_nelem(arr);

            pilotModes[i].channel = (int8_t*)malloc(pilotModes[i].chan_dim);
            if (pilotModes[i].channel == NULL) {
                TOML_DBG_E("mode channel malloc fail\n");
                return E_NOMEM;
            }

            for (int d = 0; d < pilotModes[i].chan_dim; d++) {
                if (toml_int_at(arr, d, &ival) == 0) {
                    pilotModes[i].channel[d] = ival;
                } else {
                    TOML_DBG_E("fail to parse rc mode channel value\n");
                    return E_RROR;
                }
            }
        } else {
            TOML_DBG_E("fail to parse channel\n");
            return E_RROR;
        }

        if (pilotModes[i].chan_dim == 1) {
            if (toml_array_value_in(tab, "range", &arr) == 0) {
                if ((pilotModes[i].range = (int16_t*)malloc(pilotModes[i].chan_dim * 2)) == NULL) {
                    TOML_DBG_E("malloc fail\n");
                    return E_NOMEM;
                }

                for (j = 0; j < 2; j++) {
                    if (toml_int_at(arr, j, &ival) == 0) {
                        pilotModes[i].range[j] = (int16_t)ival;
                    } else {
                        TOML_DBG_E("fail to parse event command range\n");
                        return E_RROR;
                    }
                }
            }
        } else if (pilotModes[i].chan_dim > 1) {
            toml_array_t* range_array;
            toml_array_t* arr;
            if ((range_array = toml_array_in(tab, "range")) == NULL) {
                TOML_DBG_E("rc mode[%d] range parse fail\n", i);
                return E_RROR;
            }

            if (toml_array_nelem(range_array) != pilotModes[i].chan_dim) {
                TOML_DBG_E("rc mode[%d] range dim not match\n", i);
                return E_RROR;
            }

            if ((pilotModes[i].range = (int16_t*)malloc(pilotModes[i].chan_dim * 2)) == NULL) {
                TOML_DBG_E("Malloc fail\n");
                return E_NOMEM;
            }

            for (int d = 0; d < pilotModes[i].chan_dim; d++) {
                arr = toml_array_at(range_array, d);

                for (int k = 0; k < 2; k++) {
                    if (toml_int_at(arr, k, &ival) == 0) {
                        pilotModes[i].range[d * 2 + k] = (int16_t)ival;
                    } else {
                        TOML_DBG_E("rc mode[%d] range value parse fail\n", i);
                        return E_RROR;
                    }
                }
            }
        } else {
            TOML_DBG_E("rc mode[%d] requires a channel mapping\n", i);
            return E_RROR;
        }
    }

    modeNum = i;

    return E_OK;
}

static err_t pilot_cmd_parse_device(const toml_table_t* curtab)
{
    int i;
    const char* key;

    /* get device type */
    if (toml_string_in(curtab, "type", &rcDevInfo.type) == 0) {
        if (MATCH(rcDevInfo.type, "rc")) {
            pilot_cmd_rc_dev_config rc_default_config = {
                .protocol = 1, // sbus
                .channel_num = 6,
                .sample_time = 0.05, // 20Hz
                .range = { 1000, 2000 }
            };

            if ((rcDevInfo.config = malloc(sizeof(pilot_cmd_rc_dev_config))) != NULL) {
                /* set default value */
                *(pilot_cmd_rc_dev_config*)rcDevInfo.config = rc_default_config;
            } else {
                TOML_DBG_E("Fail to malloc memory for rc device config\n");
                return E_NOMEM;
            }
        } else {
            TOML_DBG_E("Unknown device type: %s\n", rcDevInfo.type);
            return E_INVAL;
        }
    } else {
        TOML_DBG_E("Fail to parse type value\n");
        return E_RROR;
    }

    if (toml_string_in(curtab, "name", &rcDevInfo.name) != 0) {
        TOML_DBG_E("Fail to parse name value\n");
        return E_RROR;
    }

    /* traverse keys in table */
    for (i = 0; 0 != (key = toml_key_in(curtab, i)); i++) {
        if (MATCH(key, "type") || MATCH(key, "name")) {
            /* already handled */
            continue;
        }

        pilot_cmd_rc_dev_config* config = (pilot_cmd_rc_dev_config*)rcDevInfo.config;
        if (MATCH(key, "protocol")) {
            char* strval;
            if (toml_string_in(curtab, "protocol", &strval) == 0) {
                if (MATCH(strval, "sbus")) {
                    config->protocol = 1;
                } else if (MATCH(strval, "ppm")) {
                    config->protocol = 2;
                } else {
                    TOML_DBG_W("unknown rc protocol:%s\n", strval);
                    free(strval);
                }
            }
            free(strval);
        } else if (MATCH(key, "channel-num")) {
            int64_t ival;
            if (toml_int_in(curtab, key, &ival) == 0) {
                config->channel_num = (uint16_t)ival;
                /* set channel number */
                pilot_cmd_set_chan_num(config->channel_num);
            } else {
                TOML_DBG_W("Fail to parse %s value\n", key);
                continue;
            }
        } else if (MATCH(key, "sample-time")) {
            double dval;
            if (toml_double_in(curtab, key, &dval) == 0) {
                config->sample_time = (float)dval;
            } else {
                TOML_DBG_W("Fail to parse %s value\n", key);
                continue;
            }
        } else if (MATCH(key, "range")) {
            toml_array_t* arr;
            int64_t ival;
            if (toml_array_value_in(curtab, key, &arr) == 0 && toml_array_nelem(arr) == 2) {
                int idx;
                for (idx = 0; idx < 2; idx++) {
                    if (toml_int_at(arr, idx, &ival) == 0) {
                        config->range[idx] = (int16_t)ival;
                    } else {
                        TOML_DBG_W("Fail to parse %s value\n", key);
                        break;
                    }
                }
            }
        } else {
            TOML_DBG_W("Unknown config key: %s\n", key);
            continue;
        }
    }

    return E_OK;
}

/* config pilot_cmd via toml system configuration file */
err_t pilot_cmd_toml_config(toml_table_t* table)
{
    int i, j;
    const char* key;
    toml_table_t* tab;
    toml_array_t* arr;
    int64_t ival;

    /* traverse keys in table */
    for (i = 0; 0 != (key = toml_key_in(table, i)); i++) {
        if (MATCH(key, "stick-channel")) {
            if (toml_array_value_in(table, key, &arr) == 0 && toml_array_nelem(arr) == 4) {
                uint8_t stick_mapping[4];
                for (j = 0; j < 4; j++) {
                    if (toml_int_at(arr, j, &ival) == 0) {
                        stick_mapping[j] = (uint8_t)ival;
                    } else {
                        TOML_DBG_E("Parse stick-channel fail\n");
                        return E_RROR;
                    }
                }
                ERROR_TRY(pilot_cmd_map_stick(
                    stick_mapping[0], stick_mapping[1], stick_mapping[2], stick_mapping[3]));
            } else {
                TOML_DBG_E("Wrong stick-channel definition\n");
                return E_RROR;
            }
        } else if (MATCH(key, "device")) {
            if ((tab = toml_table_in(table, key)) != 0) {
                if (pilot_cmd_parse_device(tab) != E_OK) {
                    TOML_DBG_E("Device parse fail\n");
                    return E_RROR;
                }
            } else {
                TOML_DBG_E("Fail to parse device\n");
                return E_RROR;
            }
        } else if (MATCH(key, "mode")) {
            if (toml_array_table_in(table, key, &arr) == 0) {
                if (pilot_cmd_parse_mode(arr) != E_OK) {
                    TOML_DBG_E("Mode parse fail\n");
                    return E_RROR;
                }
            } else {
                TOML_DBG_E("Wrong mode definition\n");
                return E_RROR;
            }
        } else if (MATCH(key, "command")) {
            if (toml_array_table_in(table, key, &arr) == 0) {
                if (pilot_cmd_parse_command(arr) != E_OK) {
                    TOML_DBG_E("Command parse fail\n");
                    return E_RROR;
                }
            } else {
                TOML_DBG_E("Wrong command definition\n");
                return E_RROR;
            }
        } else {
            TOML_DBG_E("unknown key: %s\n", key);
            return E_RROR;
        }
    }

    rc_dev_t rc_dev = (rc_dev_t)device_find(rcDevInfo.name);
    ASSERT(rc_dev != NULL);

    pilot_cmd_rc_dev_config* config = (pilot_cmd_rc_dev_config*)rcDevInfo.config;
    struct rc_configure pconfig = {
        .protocol = config->protocol,
        .channel_num = config->channel_num,
        .sample_time = config->sample_time,
        .rc_min_value = config->range[0],
        .rc_max_value = config->range[1],
    };

    /* configure console device according to the toml configure */
    if (device_control(&rc_dev->parent, DEVICE_CTRL_CONFIG, &pconfig) != E_OK) {
        TOML_DBG_E("fail to configure device %s\n", rcDevInfo.name);
        return E_RROR;
    }

    ERROR_TRY(pilot_cmd_set_device(rcDevInfo.name));

    return E_OK;
}
