// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_BUTTER_H
#define X7PRO_DRIVER_BUTTER_H

typedef struct
{
    float A[4];
    float B[4];
    float X[4];
    float Y[4];
} Butter3;

/* butter lpf filter */
Butter3* butter3_filter_create(float b[4], float a[4]);
float butter3_filter_process(float in, Butter3* butter);
#endif //X7PRO_DRIVER_BUTTER_H
