//
// Created by 19114 on 2022/10/20.
//

#ifndef STM32H743IIT6_COMMON_H
#define STM32H743IIT6_COMMON_H

#include "stdio.h"
//---------choose your os type---------
#define USE_FREERTOS    1
#define USE_UCOS        0
#define SUPPORT_OS      (USE_FREERTOS | USE_UCOS)

#define USE_SPI         0

#define delay_ms        HAL_Delay
#define UNUSED(x)       ((void)(x))


#endif //STM32H743IIT6_COMMON_H
