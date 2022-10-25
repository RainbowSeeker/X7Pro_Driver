//
// Created by 19114 on 2022/10/10.
//

#ifndef STM32H743IIT6_TASK_H
#define STM32H743IIT6_TASK_H

#include "main.h"


#define STARTUP_TASK_STK_SIZE   128
#define STARTUP_TASK_PRIO       4

#define TASK1_STK_SIZE          256
#define TASK1_PRIO              4

#define TASK2_STK_SIZE          256
#define TASK2_PRIO              3



void MY_OSInit();

#endif //STM32H743IIT6_TASK_H
