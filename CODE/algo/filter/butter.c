// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//
#include "system/common.h"
#include "butter.h"

Butter3* butter3_filter_create(float b[4], float a[4])
{
    Butter3* butter = MALLOC(sizeof(Butter3));
    if (butter == NULL) {
        return NULL;
    }
    for (uint8_t i = 0; i < 4; i++) {
        butter->B[i] = b[i];
        butter->A[i] = a[i];
        butter->X[i] = butter->Y[i] = 0.0f;
    }

    return butter;
}

float butter3_filter_process(float in, Butter3* butter)
{
    float out;
    butter->X[3] = in;
    /* a(1)*y(n) = b(1)*x(n) + b(2)*x(n-1) + ... + b(nb+1)*x(n-nb)
                         - a(2)*y(n-1) - ... - a(na+1)*y(n-na)  */
    butter->Y[3] = butter->B[0] * butter->X[3] + butter->B[1] * butter->X[2] + butter->B[2] * butter->X[1]
                   + butter->B[3] * butter->X[0] - butter->A[1] * butter->Y[2] - butter->A[2] * butter->Y[1] - butter->A[3] * butter->Y[0];

    /* we assume a(1)=1 */
    out = butter->Y[3];

    /* move X and Y */
    butter->X[0] = butter->X[1];
    butter->X[1] = butter->X[2];
    butter->X[2] = butter->X[3];
    butter->Y[0] = butter->Y[1];
    butter->Y[1] = butter->Y[2];
    butter->Y[2] = butter->Y[3];

    return out;
}