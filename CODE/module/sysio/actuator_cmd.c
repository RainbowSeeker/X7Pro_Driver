
#include <common.h>
#include <string.h>

#include "model/control/control_interface.h"
#include "module/mavproxy/mavproxy.h"
#include "module/sysio/actuator_config.h"

MCN_DECLARE(control_output);
MCN_DECLARE(rc_trim_channels);

enum {
    ACTUATOR_FROM_CONTROL_OUT,
    ACTUATOR_FROM_RC_CHANNELS,
    ACTUATOR_FROM_UNKNOWN
};

static McnNode_t _control_out_nod;
static McnNode_t _rc_channels_nod;
static uint8_t* from_dev;
static device_t* to_dev;
static uint8_t mapping_num;
static actuator_mapping* mapping_list;


err_t send_actuator_cmd(void)
{
    err_t err = E_OK;
    int i, j;
    bool has_poll_control_out = false;
    bool has_poll_rc_channels = false;
    Control_Out_Bus control_out;
    int16_t rc_channel[16];

    DEFINE_TIMETAG(actuator_intv, 2);

    if (check_timetag(TIMETAG(actuator_intv)) == 0) {
        return E_BUSY;
    }

    for (i = 0; i < mapping_num; i++) {
        size_t size = mapping_list[i].map_size;
        uint16_t chan_sel = 0;
        int16_t chan_val[16];

        if (from_dev[i] == ACTUATOR_FROM_CONTROL_OUT) {
            if (has_poll_control_out == false) {
                if (mcn_poll(_control_out_nod) == false) {
                    return E_RROR;
                }
                mcn_copy(MCN_HUB(control_output), _control_out_nod, &control_out);
                has_poll_control_out = true;
            }

            for (j = 0; j < mapping_list[i].map_size; j++) {
                /* set channel select according to to mapping */
                chan_sel |= 1 << (mapping_list[i].to_map[j] - 1);
                /* set channel value according to from mapping */
                chan_val[j] = control_out.actuator_cmd[mapping_list[i].from_map[j] - 1];
            }
        } else if (from_dev[i] == ACTUATOR_FROM_RC_CHANNELS) {
            if (has_poll_rc_channels == false) {
                if (mcn_poll(_rc_channels_nod) == 0) {
                    return E_RROR;
                }
                mcn_copy(MCN_HUB(rc_trim_channels), _rc_channels_nod, &rc_channel);
                has_poll_rc_channels = true;
            }

            for (j = 0; j < mapping_list[i].map_size; j++) {
                /* set channel select according to mapping */
                chan_sel |= 1 << (mapping_list[i].to_map[j] - 1);
                /* set channel value according to from mapping */
                chan_val[j] = rc_channel[mapping_list[i].from_map[j] - 1];
            }
        } else {
            /* to avoid warning */
            (void)size;
            (void)chan_sel;
            (void)chan_val;
            continue;
        }

#if defined(FMT_HIL_WITH_ACTUATOR) || (!defined(FMT_USING_HIL) && !defined(FMT_USING_SIH))
        /* write actuator command */
        if (device_write(to_dev[i], chan_sel, chan_val, size) != size) {
            err = E_RROR;
        }
#endif

#if defined(FMT_USING_HIL)
        send_hil_actuator_cmd(chan_sel, chan_val);
#endif
    }

    return err;
}

err_t actuator_init(void)
{
    _control_out_nod = mcn_subscribe(MCN_HUB(control_output), NULL, NULL);
    if (_control_out_nod == NULL) {
        return E_RROR;
    }

    _rc_channels_nod = mcn_subscribe(MCN_HUB(rc_trim_channels), NULL, NULL);
    if (_rc_channels_nod == NULL) {
        return E_RROR;
    }

    mapping_num = actuator_toml_get_mapping_num();
    mapping_list = actuator_toml_get_mapping_list();

    if (mapping_num) {
        from_dev = (uint8_t*)malloc(sizeof(uint8_t) * mapping_num);
        to_dev = (device_t*)malloc(sizeof(device_t) * mapping_num);
        if (from_dev == NULL || to_dev == NULL) {
            return E_NOMEM;
        }
    }

    for (int i = 0; i < mapping_num; i++) {
        if (strcmp(mapping_list[i].from, "control_out") == 0) {
            from_dev[i] = ACTUATOR_FROM_CONTROL_OUT;
        } else if (strcmp(mapping_list[i].from, "rc_channels") == 0) {
            from_dev[i] = ACTUATOR_FROM_RC_CHANNELS;
        } else {
            from_dev[i] = ACTUATOR_FROM_UNKNOWN;
        }

        to_dev[i] = device_find(mapping_list[i].to);
        if (to_dev[i] == NULL) {
            return E_EMPTY;
        }
    }

    return E_OK;
}
