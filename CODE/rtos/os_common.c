// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "os_common.h"
#include "bsp_os.h"
#include "lib_mem.h"
#include "os_app_hooks.h"
#include "thread.h"

void bsp_os_init(void (*StartupTask)(void *p_arg))
{
    Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    CPU_IntDis();                                               /* Disable all Interrupts       */

    CPU_Init();                          //Initialize the uC/CPU services
    OSInit(&os_err);               //Initialize uC/OS-III
    ASSERT(!os_err);

    OS_ENTER_CRITICAL();
    App_OS_SetAllHooks();               //Set all applications hooks
    os_thread_create("Startup Task",    //Create the startup task
                     StartupTask,
                     NULL,
                     STARTUP_THREAD_PRIORITY,
                     STARTUP_TASK_STK_SIZE);
    OS_EXIT_CRITICAL();
    OSStart(&os_err);             //Start multitasking (i.e. give control to uC/OS-III)
    ASSERT(!os_err);
}