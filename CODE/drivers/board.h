// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/18.
//

#ifndef X7PRO_DRIVER_BOARD_H
#define X7PRO_DRIVER_BOARD_H
#include "common.h"

// Board Information
#define TARGET_NAME  "CUAV V7Pro"

// clang-format off
static char* default_conf = STRING(
target = "CUAV V7Pro"\n
[console]\n
[[console.devices]]\n
        type = "serial"\n
        name = "serial0"\n
        baudrate = 115200\n
        auto-switch = true\n
[[console.devices]]\n
        type = "mavlink"\n
        name = "mav_console"\n
        auto-switch = true\n
[mavproxy]\n
[[mavproxy.devices]]\n
        type = "usb"\n
        name = "usbd0"\n
        auto-switch = true\n
[pilot-cmd]\n
        stick-channel = [2,1,3,4]\n
[pilot-cmd.device]\n
        type = "rc"\n
        name = "rc"\n
        protocol = "sbus"\n
        channel-num = 16\n
        sample-time = 0.05\n
        range = [1000,2000]\n
[[pilot-cmd.mode]]\n
        mode = 0\n
        channel = 5\n
        range = [1060,1070]\n
[[pilot-cmd.mode]]\n
        mode = 5\n
        channel = 5\n
        range = [1490,1500]\n
[[pilot-cmd.mode]]\n
        mode = 6\n
        channel = 5\n
        range = [1930,1940]\n
[[pilot-cmd.command]]\n
        type = 1\n
        cmd = 1002\n
        channel = 6\n
        range = [1930,1940]\n
[[pilot-cmd.command]]\n
        type = 1\n
        cmd = 1000\n
        channel = 6\n
        range = [1060,1070]\n
[actuator]\n
[[actuator.devices]]\n
        protocol = "pwm"\n
        name = "aux_out"\n
        freq = 50\n
[[actuator.mappings]]\n
        from = "control_out"\n
        to = "aux_out"\n
        chan-map = [[1,2,3],[1,2,3]]\n
);
//[[actuator.mappings]]\n
//        from = "rc_channels"\n
//        to = "aux_out"\n
//        chan-map = [[1,4,4],[1,2,3]]\n

// clang-format on

#define BSP_USING_FDCAN1
//#define BSP_USING_FDCAN2

// Device Name
#define FMTIO_DEVICE_NAME "serial5"

#endif //X7PRO_DRIVER_BOARD_H
