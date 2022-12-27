// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/15.
//
#include "common.h"
#include "syscmd.h"


int cmd_reboot(int argc, char** argv)
{
    console_printf("\nrebooting...\n");
    sys_msleep(10);

    NVIC_SystemReset();

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_reboot, __cmd_reboot, reboot the system);

int cmd_shutdown(int argc, char** argv)
{
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_shutdown, __cmd_shutdown, shutdown the system);
