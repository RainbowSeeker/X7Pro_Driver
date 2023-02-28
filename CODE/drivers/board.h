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
//[[mavproxy.devices]]\n
//        type = "serial"\n
//        name = "serial1"\n
//        baudrate = 57600\n
[[mavproxy.devices]]\n
        type = "usb"\n
        name = "usbd0"\n
        auto-switch = true\n
[pilot-cmd]\n
        stick-channel = [4,3,2,1]\n
[pilot-cmd.device]\n
        type = "rc"\n
        name = "rc"\n
        protocol = "sbus"\n
        channel-num = 16\n
        sample-time = 0.05\n
        range = [1000,2000]\n
);


// clang-format on

#define BSP_USING_FDCAN1
//#define BSP_USING_FDCAN2

// Device Name
#define FMTIO_DEVICE_NAME "serial5"

#endif //X7PRO_DRIVER_BOARD_H
