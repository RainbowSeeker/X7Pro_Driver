// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/9.
//


#include <common.h>
#include "module_common.h"
#include "module/file_manager/file_manager.h"
#include "drivers/board.h"
#include "fmtio/fmtio.h"


void App_IO_Main(void *argument)
{
//    fmtio_init(FMTIO_DEVICE_NAME);

    fmtio_loop();
}