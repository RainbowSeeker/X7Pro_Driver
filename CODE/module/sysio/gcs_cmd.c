/******************************************************************************
 * Copyright 2021 The Firmament Authors. All Rights Reserved.
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

#include "module/utils/ringbuffer.h"
#include <FMS.h>

#define LOG_TAG "GCS"
#include "ulog.h"

MCN_DEFINE(gcs_cmd, sizeof(GCS_Cmd_Bus));
MCN_DECLARE(fms_output);

static uint32_t gcs_cmd_buffer[20];
static ringbuffer* gcs_cmd_rb;
static PilotMode gcs_mode_buffer[20];
static ringbuffer* gcs_mode_rb;
static GCS_Cmd_Bus gcs_cmd;
static McnNode_t fms_out_nod;
static FMS_Out_Bus fms_out;

static int gcs_cmd_echo(void* parameter)
{
    GCS_Cmd_Bus gcs_cmd;

    if (mcn_copy_from_hub((McnHub*)parameter, &gcs_cmd) != E_OK) {
        return -1;
    }

    printf("timestamp:%u mode:%u cmd1:%u cmd2:%u\n",
           gcs_cmd.timestamp,
           gcs_cmd.mode,
           gcs_cmd.cmd_1,
           gcs_cmd.cmd_2);

    return 0;
}

err_t gcs_set_cmd(FMS_Cmd cmd)
{
    uint32_t new_cmd = cmd;

    switch (cmd) {
    case FMS_Cmd_PreArm:
        LOG_I("recv PreArm command.");
        break;
    case FMS_Cmd_Arm:
        LOG_I("recv Arm command.");
        break;
    case FMS_Cmd_Disarm:
        LOG_I("recv Disarm command.");
        break;
    case FMS_Cmd_Takeoff:
        LOG_I("recv Takeoff command.");
        break;
    case FMS_Cmd_Land:
        LOG_I("recv Land command.");
        break;
    case FMS_Cmd_Return:
        LOG_I("recv Return command.");
        break;
    case FMS_Cmd_Pause:
        LOG_I("recv Pause command.");
        break;
    case FMS_Cmd_Continue:
        LOG_I("recv Continue command.");
        break;
    default:
        LOG_W("recv Unknown command %d.", cmd);
        return E_NOTHANDLE;
    }

    ringbuffer_put(gcs_cmd_rb, (uint8_t*)&new_cmd, sizeof(new_cmd));

    return E_OK;
}

err_t gcs_set_mode(PilotMode mode)
{
    uint32_t new_mode = mode;

    switch (mode) {
    case PilotMode_Manual:
        LOG_I("set Manual mode.");
        break;
    case PilotMode_Acro:
        LOG_I("set Acro mode.");
        break;
    case PilotMode_Stabilize:
        LOG_I("set Stabilize mode.");
        break;
    case PilotMode_Altitude:
        LOG_I("set Altitude mode.");
        break;
    case PilotMode_Position:
        LOG_I("set Position mode.");
        break;
    case PilotMode_Mission:
        LOG_I("set Mission mode.");
        break;
    case PilotMode_Offboard:
        LOG_I("set Offboard mode.");
        break;
    default:
        LOG_W("set Unknown mode %d.", mode);
        return E_INVAL;
    }

    if (mcn_poll(fms_out_nod)) {
        mcn_copy(MCN_HUB(fms_output), fms_out_nod, &fms_out);
    }

    if ((fms_out.mode == PilotMode_Mission || fms_out.mode == PilotMode_Offboard)
        && fms_out.mode == mode && fms_out.state == VehicleState_Hold) {
        /* When vehicle is in auto mode (mission,offboard), reset the mode would trigger FMS_Cmd_Continue.
           e.g, When mission is paused, the vehicle would enter hold mode (state = VehicleState_Hold), 
           however, the mode is still PilotMode_Mission, so the mode would not change when user try
           to set mode to Mission and continue. Therefore, we send FMS_Cmd_Continue instead to continue
           the mission mode. */
        gcs_set_cmd(FMS_Cmd_Continue);
    } else {
        /* For normal case, we just set the new mode. */
        ringbuffer_put(gcs_mode_rb, (uint8_t*)&new_mode, sizeof(new_mode));
    }

    return E_OK;
}

err_t gcs_cmd_collect(void)
{
    static uint32_t last_cmd_timestamp = 0;
    uint8_t updated = 0;
    uint32_t time_now = systime_now_ms();

    if (ringbuffer_getlen(gcs_mode_rb) >= sizeof(gcs_cmd.mode)) {
        ringbuffer_get(gcs_mode_rb, (uint8_t*)&gcs_cmd.mode, sizeof(gcs_cmd.mode));
        updated = 1;
    }

    /* the command need to last at least FMS_CONST.dt */
    if (time_now - last_cmd_timestamp > 100) {
        /* check if there is new command in buffer */
        if (ringbuffer_getlen(gcs_cmd_rb) >= sizeof(gcs_cmd.cmd_1)) {
            last_cmd_timestamp = time_now;

            ringbuffer_get(gcs_cmd_rb, (uint8_t*)&gcs_cmd.cmd_1, sizeof(gcs_cmd.cmd_1));
            updated = 1;
        } else {
            if (gcs_cmd.cmd_1 > 0) {
                gcs_cmd.cmd_1 = 0;
                updated = 1;
            }
        }
    }

    if (updated) {
        gcs_cmd.timestamp = systime_now_ms();
        ERROR_TRY(mcn_publish(MCN_HUB(gcs_cmd), &gcs_cmd));
    }

    return E_OK;
}

err_t gcs_cmd_init(void)
{
    gcs_cmd_rb = ringbuffer_static_create(sizeof(gcs_cmd_buffer), (uint8_t*)gcs_cmd_buffer);
    gcs_mode_rb = ringbuffer_static_create(sizeof(gcs_mode_buffer), (uint8_t*)gcs_mode_buffer);
    ASSERT(gcs_cmd_rb != NULL);
    ASSERT(gcs_mode_rb != NULL);

    ERROR_TRY(mcn_advertise(MCN_HUB(gcs_cmd), gcs_cmd_echo));

    fms_out_nod = mcn_subscribe(MCN_HUB(fms_output), NULL, NULL);
    ASSERT(fms_out_nod != NULL);

    return E_OK;
}