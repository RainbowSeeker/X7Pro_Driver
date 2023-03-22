// Copyright (c) 2023 By RainbowSeeker.

//
// Created by 19114 on 2023/3/19.
//
#include "common_def.h"
#include "os_common.h"

static ubase_t criticalNesting = 0;
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (CPU_CFG_KA_IPL_BOUNDARY << (8u - CPU_CFG_NVIC_PRIO_BITS))
void portEnterCritical( void )
{
    CPU_SR_Save(CPU_CFG_KA_IPL_BOUNDARY << (8u - CPU_CFG_NVIC_PRIO_BITS));
    criticalNesting++;
}
/*-----------------------------------------------------------*/

void portExitCritical( void )
{
    ASSERT( criticalNesting );
    criticalNesting--;
    if( criticalNesting == 0 )
    {
        CPU_SR_Restore(0);
    }
}