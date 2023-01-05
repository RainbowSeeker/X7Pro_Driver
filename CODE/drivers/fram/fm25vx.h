// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/17.
//

#ifndef X7PRO_DRIVER_FM25VX_H
#define X7PRO_DRIVER_FM25VX_H
#include <common.h>

#define FM25V05_MAX_SPI_CLK_HZ  1000000

err_t drv_fm25v05_init(const char *fram_device_name);
#endif //X7PRO_DRIVER_FM25VX_H
