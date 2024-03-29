#include <common.h>


#include <string.h>

#include "hal/serial/serial.h"
#include "module/toml/toml.h"
#include "module/utils/devmq.h"

#define TOML_DBG_E(...) toml_debug("Console", "E", __VA_ARGS__)
#define TOML_DBG_W(...) toml_debug("Console", "W", __VA_ARGS__)

#define CONSOLE_MAX_DEVICE_NUM      5
#undef MATCH
#define MATCH(a, b)                 (strcmp(a, b) == 0)
#define DEVICE_LIST                 console_dev_list
#define DEVICE_NUM                  console_dev_num
#define DEVICE_TYPE_IS(_idx, _name) MATCH(DEVICE_LIST[_idx].type, #_name)
#define FIND_DEVICE(_idx)           device_find(DEVICE_LIST[_idx].name)

typedef struct {
    uint32_t baudrate;
    bool auto_switch;
} console_serial_dev_config;

typedef struct {
    bool auto_switch;
} console_mavlink_dev_config;

typedef struct {
    char* type;
    char* name;
    void* config;
} console_device_info;

static uint8_t console_dev_num = 0;
static console_device_info console_dev_list[CONSOLE_MAX_DEVICE_NUM] = { 0 };

static err_t switch_device_to(int idx);

static void __handle_device_msg(device_t dev, void* msg)
{
    int idx;
    device_status status = *((device_status*)msg);

    for (idx = 0; idx < DEVICE_NUM; idx++) {
        if (FIND_DEVICE(idx) == dev) {
            /* if data received, switch console to this device */
            if (status == DEVICE_STATUS_RX) {
                switch_device_to(idx);
                break;
            }
        }
    }
}

static int find_device_idx(device_t device)
{
    int idx;

    for (idx = 0; idx < DEVICE_NUM; idx++) {
        if (device_find(DEVICE_LIST[idx].name) == device) {
            return idx;
        }
    }
    return -1;
}

static void reset_device_list(void)
{
    for (int i = 0; i < CONSOLE_MAX_DEVICE_NUM; i++) {
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

static err_t console_device_rx_ind(device_t dev, size_t size)
{
    err_t err = E_OK;

    /* if it's not the current working console device, notify the rx status */
    if (console_get_device() != dev) {
        device_status status = DEVICE_STATUS_RX;
        devmq_notify(dev, &status);
    }
    return err;
}

static err_t set_rx_indicator(void)
{
    err_t err;
    int idx;

    for (idx = 0; idx < DEVICE_NUM; idx++) {
        if (idx == find_device_idx(console_get_device())) {
            /* do not set rx indicator for current console deivce */
            /* because shell is using that */
            continue;
        }

        if (DEVICE_TYPE_IS(idx, serial)) {
            console_serial_dev_config* config = (console_serial_dev_config*)DEVICE_LIST[idx].config;

            if (config->auto_switch) {
                /* set rx indicator to notify the device status */
                err = device_set_rx_indicate(FIND_DEVICE(idx), console_device_rx_ind);
                if (err != E_OK) {
                    return E_RROR;
                }
            }
        } else if (DEVICE_TYPE_IS(idx, mavlink)) {
            console_mavlink_dev_config* config = (console_mavlink_dev_config*)DEVICE_LIST[idx].config;

            if (config->auto_switch) {
                /* set rx indicator to notify the device status */
                err = device_set_rx_indicate(FIND_DEVICE(idx), console_device_rx_ind);
                if (err != E_OK) {
                    return E_RROR;
                }
            }
        } else {
            /* unknown device type */
            return E_RROR;
        }
    }

    return E_OK;
}

/**
 * Switch console device by device id
 *
 * @param idx device id in device list
 *
 * @return Errors Status
 */
static err_t switch_device_to(int idx)
{
    if (idx >= DEVICE_NUM || idx < 0) {
        return E_RROR;
    }

    if (console_set_device(DEVICE_LIST[idx].name) != E_OK) {
        return E_RROR;
    }

    /* we just switch the console device, set rx indicator for other devices */
    if (set_rx_indicator() != E_OK) {
        return E_RROR;
    }

    return E_OK;
}

/**
 * Parse device table
 *
 * @param array device table
 * @param idx device index in device list
 *
 * @return Errors Status
 */
static err_t console_parse_device(const toml_table_t* curtab, int idx)
{
    err_t err = E_OK;
    int i;
    const char* key;

    /* get device type */
    if (toml_string_in(curtab, "type", &DEVICE_LIST[idx].type) == 0) {
        if (DEVICE_TYPE_IS(idx, serial)) {
            console_serial_dev_config serial_default_config = {
                .baudrate = 57600,
                .auto_switch = true
            };
            DEVICE_LIST[idx].config = malloc(sizeof(console_serial_dev_config));

            /* set default value */
            if (DEVICE_LIST[idx].config != NULL) {
                *(console_serial_dev_config*)DEVICE_LIST[idx].config = serial_default_config;
            } else {
                TOML_DBG_E("fail to malloc memory\n");
                err = E_RROR;
            }
        } else if (DEVICE_TYPE_IS(idx, mavlink)) {
            console_mavlink_dev_config mavlink_default_config = {
                .auto_switch = true
            };
            DEVICE_LIST[idx].config = malloc(sizeof(console_mavlink_dev_config));

            /* set default value */
            if (DEVICE_LIST[idx].config != NULL) {
                *(console_mavlink_dev_config*)DEVICE_LIST[idx].config = mavlink_default_config;
            } else {
                TOML_DBG_E("fail to malloc memory\n");
                err = E_RROR;
            }
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
            console_serial_dev_config* config = (console_serial_dev_config*)DEVICE_LIST[idx].config;
            if (MATCH(key, "baudrate")) {
                int64_t ival;
                if (toml_int_in(curtab, key, &ival) == 0) {
                    config->baudrate = (uint32_t)ival;
                } else {
                    TOML_DBG_W("fail to parse baudrate value\n");
                    continue;
                }
            } else if (MATCH(key, "auto-switch")) {
                int bval;
                if (toml_bool_in(curtab, key, &bval) == 0) {
                    config->auto_switch = bval ? true : false;
                    if (config->auto_switch) {
                        /* create device mq to monitor the device status */
                        if (devmq_create(FIND_DEVICE(idx), sizeof(device_status), 5) != E_OK) {
                            TOML_DBG_E("fail to create devmq\n");
                            return E_RROR;
                        }
                        /* monitor device status */
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
        } else if (DEVICE_TYPE_IS(idx, mavlink)) {
            console_mavlink_dev_config* config = (console_mavlink_dev_config*)DEVICE_LIST[idx].config;
            if (MATCH(key, "auto-switch")) {
                int bval;
                if (toml_bool_in(curtab, key, &bval) == 0) {
                    config->auto_switch = bval ? true : false;
                    if (config->auto_switch) {
                        /* create device mq to monitor the device status */
                        if (devmq_create(FIND_DEVICE(idx), sizeof(device_status), 5) != E_OK) {
                            TOML_DBG_E("fail to create devmq\n");
                            return E_RROR;
                        }
                        /* monitor device status */
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
        } else {
            // unknown type
            continue;
        }
    }

    return err;
}

/**
 * Parse devices table array
 *
 * @param array devices table array
 *
 * @return Errors Status
 */
static err_t console_parse_devices(const toml_array_t* array)
{
    int i;
    toml_table_t* curtab;
    err_t err = E_OK;
    uint32_t idx = 0;

    for (i = 0; 0 != (curtab = toml_table_at(array, i)); i++) {
        /* parse all devices in the table */
        err = console_parse_device(curtab, idx);
        if (err != E_OK) {
            TOML_DBG_W("serial device parse fail: %d\n", i);
            continue;
        }

        if (++idx >= CONSOLE_MAX_DEVICE_NUM) {
            break;
        }
    }

    DEVICE_NUM = idx;

    return err;
}

/**
 * Configure console according to toml system configuration.
 *
 * @param table console toml table
 *
 * @return Errors Status
 */
err_t console_toml_config(toml_table_t* table)
{
    int i;
    const char* key;
    toml_array_t* arr;
    toml_table_t* tab;
    err_t err;

    /* traverse keys in table */
    for (i = 0; 0 != (key = toml_key_in(table, i)); i++) {
        if (MATCH(key, "devices")) {
            /* get new device configuration, reset device list first */
            reset_device_list();
            /* parse devices */
            if (toml_array_table_in(table, key, &arr) == 0) {
                err = console_parse_devices(arr);
                if (err != E_OK) {
                    TOML_DBG_E("fail to parse devices\n");
                    return err;
                }
            } else {
                TOML_DBG_E("fail to parse devices table\n");
                return E_RROR;
            }
        } else if (MATCH(key, "device")) {
            /* get new device configuration, reset device list first */
            reset_device_list();
            /* parse device */
            if ((tab = toml_table_in(table, key)) != 0) {
                err = console_parse_device(tab, 0);
                if (err != E_OK) {
                    TOML_DBG_E("fail to parse device\n");
                    return err;
                }
                DEVICE_NUM = 1;
            } else {
                console_printf("Error: wrong element type: %s\n", key);
                TOML_DBG_E("wrong element type: %s\n", key);
                return E_INVAL;
            }
        } else {
            TOML_DBG_E("unknown config key: %s\n", key);
            return E_INVAL;
        }
    }

    if (DEVICE_NUM == 0) {
        /* didn't confiure the console device */
        TOML_DBG_W("no console device configured");
        return E_OK;
    }

    /* first close the old console device */
    device_t old_dev = console_get_device();
    if (old_dev != NULL) {
        device_close(old_dev);
    }

    /* open all console devices by default, because we may need auto-switch feature */
    for (int idx = 0; idx < DEVICE_NUM; idx++) {
        device_t cur_dev = FIND_DEVICE(idx);
        uint16_t oflag = DEVICE_OFLAG_RDWR | DEVICE_FLAG_INT_RX | DEVICE_FLAG_STREAM;

        /* open all devices as we may need auto switch feature */
        if ((cur_dev->open_flag & DEVICE_OFLAG_OPEN)
            && (cur_dev->open_flag != oflag)) {
            /* reopen console device */
            device_close(cur_dev);
        }
        if (device_open(cur_dev, oflag) != E_OK) {
            /* fail to open */
            return E_RROR;
        }

        /* configure device if needed */
        if (DEVICE_TYPE_IS(idx, serial)) {
            serial_dev_t serial_dev = (serial_dev_t)cur_dev;
            /* toml device configuration */
            console_serial_dev_config* config = (console_serial_dev_config*)DEVICE_LIST[idx].config;
            /* console device configuration */
            struct serial_configure pconfig = serial_dev->config;
            /* configure console device according to the toml configure */
            pconfig.baud_rate = config->baudrate;
            if (device_control(&serial_dev->parent, DEVICE_CTRL_CONFIG, &pconfig) != E_OK) {
                TOML_DBG_E("fail to configure device %s\n", DEVICE_LIST[idx].name);
                return E_RROR;
            }
        }
    }
    /* switch to the first device */
    err = switch_device_to(0);

    return err;
}
