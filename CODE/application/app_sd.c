// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//


#include <common.h>
#include "module_common.h"
#include "module/file_manager/file_manager.h"


void App_SD_Main(void *argument)
{
    int fd = open("/log/session_id100", O_TRUNC | O_CREAT | O_RDWR);
    if (fd < 0) {
        printf("fail to create log session id file! err:%ld\n", os_get_errno());
    }
    uint32_t previousWakeTime = os_tick_get();
    uint32_t lastTime = os_tick_get();
    uint32_t minu;
    while (1)
    {
        minu = os_tick_get() - lastTime;
        if (minu > 50)
        {
            printf("\r\nsd error:%d at %.1f", minu, (float )lastTime / 1000);
        }
        lastTime = os_tick_get();
        fm_fprintf(fd, "tick:\t%d\thelloworld\r\n", lastTime);
        fsync(fd);
        osDelayUntil(&previousWakeTime, 50);
    }

}