// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/10.
//

#include "os_mem.h"
#include <common.h>

#ifdef RT_USING_FINSH
#include <finsh.h>

static size_t mem_size = configTOTAL_HEAP_SIZE;
static size_t used_mem, max_mem;

void list_mem(void)
{
    HeapStats_t stat;
    vPortGetHeapStats(&stat);

    printf("total memory: %d\n", mem_size);
    printf("used memory : %d\n", mem_size - stat.xAvailableHeapSpaceInBytes);
    printf("maximum allocated memory: %d\n", mem_size - stat.xMinimumEverFreeBytesRemaining);
}
#endif