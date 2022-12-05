// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/18.
//

#include "fram.h"


#define LOG_TAG     "fram"
#include "ulog.h"

bool Fram_Init(fram_t *fram)
{
    if (fram->init(fram))
    {
        LOG_I("Initialized Fram[%d]: %s", fram->dev.deviceID, fram->dev.name);
    }
    else
    {
        LOG_E("Cann't Initialize Fram Device: %s.\r\nPlease check your configuration.", fram->dev.name);
        return false;
    }

    return true;
}