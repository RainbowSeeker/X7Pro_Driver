
#include <common.h>

#include "hal/serial/serial.h"
#include "module/mavproxy/mavproxy.h"
#include "module/mavproxy/mavproxy_config.h"
#include "module/toml/toml.h"
#include "module/utils/devmq.h"

#define TOML_DBG_E(...) toml_debug("Mavproxy", "E", __VA_ARGS__)
#define TOML_DBG_W(...) toml_debug("Mavproxy", "W", __VA_ARGS__)

#define MAVPROXY_MAX_DEVICE_NUM     5
#undef MATCH
#define MATCH(a, b)                 (strcmp(a, b) == 0)
#define DEVICE_LIST                 mavproxy_device_list
#define DEVICE_NUM                  mavproxy_device_num
#define DEVICE_TYPE_IS(_idx, _name) MATCH(DEVICE_LIST[_idx].type, #_name)
#define FIND_DEVICE(_idx)           device_find(DEVICE_LIST[_idx].name)
#define MAVPROXY_SERIAL_BAUDRATE    57600

static mavproxy_device_info mavproxy_device_list[MAVPROXY_MAX_DEVICE_NUM] = { 0 };
static uint8_t mavproxy_device_num = 0;

int get_device_num(void)
{
    return DEVICE_NUM;
}

mavproxy_device_info* get_device_list(void)
{
    return DEVICE_LIST;
}

static void __handle_device_msg(device_t dev, void* msg)
{
    device_status status = *((device_status*)msg);

    for (int idx = 0; idx < DEVICE_NUM; idx++) {
        if (device_find(DEVICE_LIST[idx].name) == dev) {
            if (status == DEVICE_STATUS_CONNECT) {
                /* if usb conncted, switch to usb channel */
                mavproxy_set_channel(idx);
            } else if (status == DEVICE_STAUTS_DISCONNECT) {
                /* if usb disconncted, switch to default channel */
                mavproxy_set_channel(0);
            }
            break;
        }
    }
}

static void reset_device_list(void)
{
    for (int i = 0; i < MAVPROXY_MAX_DEVICE_NUM; i++) {
        if (DEVICE_LIST[i].type) {
            free(DEVICE_LIST[i].type);
        }
        if (DEVICE_LIST[i].name) {
            free(DEVICE_LIST[i].name);
        }
        if (DEVICE_LIST[i].config) {
            free(DEVICE_LIST[i].config);
        }
        DEVICE_LIST[i].type = NULL;
        DEVICE_LIST[i].name = NULL;
        DEVICE_LIST[i].config = NULL;
    }
    DEVICE_NUM = 0;
}

static err_t mavproxy_parse_device(const toml_table_t* curtab, int idx)
{
    err_t err = E_OK;
    int i;
    const char* key;

    /* get device type */
    if (toml_string_in(curtab, "type", &DEVICE_LIST[idx].type) == 0) {
        if (DEVICE_TYPE_IS(idx, serial)) {
            mavproxy_serial_dev_config serial_default_config = {
                .baudrate = MAVPROXY_SERIAL_BAUDRATE
            };
            DEVICE_LIST[idx].config = malloc(sizeof(mavproxy_serial_dev_config));

            /* set default value */
            if (DEVICE_LIST[idx].config) {
                *(mavproxy_serial_dev_config*)DEVICE_LIST[idx].config = serial_default_config;
            } else {
                TOML_DBG_E("malloc fail\n");
                err = E_RROR;
            }
        } else if (DEVICE_TYPE_IS(idx, usb)) {
            /* do nothing */
        } else if (DEVICE_TYPE_IS(idx, bb_com)) {
            /* do nothing */
        } else {
            TOML_DBG_E("unknown device type: %s\n", DEVICE_LIST[idx].type);
            err = E_RROR;
        }
    } else {
        TOML_DBG_E("fail to parse type value\n");
        return E_RROR;
    }

    if (toml_string_in(curtab, "name", &DEVICE_LIST[idx].name) != 0) {
        TOML_DBG_E("fail to parse name value\n");
        return E_RROR;
    }

    /* traverse keys in table */
    for (i = 0; 0 != (key = toml_key_in(curtab, i)); i++) {
        if (MATCH(key, "type") || MATCH(key, "name")) {
            /* already handled */
            continue;
        }

        if (DEVICE_TYPE_IS(idx, serial)) {
            mavproxy_serial_dev_config* config = (mavproxy_serial_dev_config*)DEVICE_LIST[idx].config;
            if (MATCH(key, "baudrate")) {
                int64_t ival;
                if (toml_int_in(curtab, key, &ival) == 0) {
                    config->baudrate = (uint32_t)ival;
                } else {
                    TOML_DBG_W("fail to parse baudrate value\n");
                    continue;
                }
            } else {
                TOML_DBG_W("unknown config key: %s\n", key);
                continue;
            }
        } else if (DEVICE_TYPE_IS(idx, usb)) {
            if (MATCH(key, "auto-switch")) {
                int bval;
                if (toml_bool_in(curtab, key, &bval) == 0) {
                    if (bval) {
                        /* if auto-switch is true, register devmq to monitor device status */
                        if (devmq_register(FIND_DEVICE(idx), __handle_device_msg) != E_OK) {
                            TOML_DBG_W("fail to register %s message queue\n", DEVICE_LIST[idx].name);
                        }
                    }
                } else {
                    TOML_DBG_E("fail to parse auto-switch value\n");
                    continue;
                }
            } else {
                TOML_DBG_E("unknown config key: %s\n", key);
                continue;
            }
        } else if (DEVICE_TYPE_IS(idx, bb_com)) {
            DEVICE_NUM = idx + 1; /* the DEVICE_NUM has not set here, so add 1 for temp */
            if (MATCH(key, "auto-switch")) {
                device_t ret = device_find(DEVICE_LIST[idx].name);
                if (ret != NULL) {
                    err_t ret = mavproxy_set_channel(idx);
                    if (ret != E_OK) {
                        TOML_DBG_W("mavproxy_set_channel = %d failed!!! \n", idx);
                    } else {
                        TOML_DBG_E("mavproxy_set_channel bb_com  \n");
                    }
                } else {
                    TOML_DBG_E("can't find bb_com  \n");
                }
            } else {
                TOML_DBG_E("unknown config key: %s \n", key);
                continue;
            }
        } else {
            TOML_DBG_W("unknown device type:%s \n", DEVICE_LIST[idx].type);
            continue;
        }
    }

    return err;
}

static err_t mavproxy_parse_devices(const toml_array_t* array)
{
    int i;
    toml_table_t* curtab;
    err_t err = E_OK;
    uint32_t idx = 0;

    for (i = 0; 0 != (curtab = toml_table_at(array, i)); i++) {
        err = mavproxy_parse_device(curtab, idx);

        if (err != E_OK) {
            TOML_DBG_W("device parse fail: %d\n", err);
            continue;
        }

        if (++idx >= MAVPROXY_MAX_DEVICE_NUM) {
            TOML_DBG_W("too many devices\n");
            break;
        }
    }

    DEVICE_NUM = idx;

    return err;
}

uint8_t mavproxy_get_channel_num(void)
{
    return DEVICE_NUM;
}

err_t mavproxy_get_devinfo(device_t dev, mavproxy_device_info* info)
{
    for (int idx = 0; idx < DEVICE_NUM; idx++) {
        if (device_find(DEVICE_LIST[idx].name) == dev) {
            *info = DEVICE_LIST[idx];
            return E_OK;
        }
    }

    return E_INVAL;
}

err_t mavproxy_switch_channel(uint8_t chan)
{
    device_t old_device, new_device;

    if (chan >= DEVICE_NUM) {
        return E_INVAL;
    }

    old_device = mavproxy_get_device();
    if (mavproxy_set_device(DEVICE_LIST[chan].name) == E_OK) {
        /* configure serial device if needed */
        if (DEVICE_TYPE_IS(chan, serial)) {
            serial_dev_t serial_dev;
            mavproxy_serial_dev_config* config = (mavproxy_serial_dev_config*)DEVICE_LIST[chan].config;

            new_device = mavproxy_get_device();
            serial_dev = (serial_dev_t)new_device;

            if (serial_dev->config.baud_rate != config->baudrate) {
                struct serial_configure pconfig = serial_dev->config;
                pconfig.baud_rate = config->baudrate;
                if (device_control(new_device, DEVICE_CTRL_CONFIG, &pconfig) != E_OK) {
                    return E_RROR;
                }
            }
        }
        /* now we can safely close the old device */
        if (old_device != NULL) {
            device_close(old_device);
        }
    } else {
        return E_RROR;
    }

    return E_OK;
}

/* config mavproxy via toml system configuration file */
err_t mavproxy_toml_config(toml_table_t* table)
{
    int i;
    const char* key;
    toml_array_t* arr;
    toml_table_t* tab;
    err_t err = E_OK;

    /* traverse keys in table */
    for (i = 0; 0 != (key = toml_key_in(table, i)); i++) {
        if (MATCH(key, "devices")) {
            /* we get new device configuration, override original one */
            reset_device_list();

            if (toml_array_table_in(table, key, &arr) == 0) {
                err = mavproxy_parse_devices(arr);
                if (err != E_OK) {
                    TOML_DBG_E("fail to parse devices\n");
                    return err;
                }
            } else {
                TOML_DBG_E("fail to get devices table\n");
                return E_RROR;
            }
        } else if (MATCH(key, "device")) {
            /* we get new device configuration, override original one */
            reset_device_list();

            if ((tab = toml_table_in(table, key)) != 0) {
                err = mavproxy_parse_device(tab, 0);
                if (err == E_OK) {
                    DEVICE_NUM = 1;
                }
            } else {
                TOML_DBG_E("wrong element type: %s\n", key);
                err = E_RROR;
            }
        } else {
            TOML_DBG_E("unknown config key: %s\n", key);
            err = E_RROR;
        }
    }

    return err;
}
