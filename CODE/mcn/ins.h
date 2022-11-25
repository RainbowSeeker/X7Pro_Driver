// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/22.
//

#ifndef X7PRO_DRIVER_INS_H
#define X7PRO_DRIVER_INS_H
#include "stdio.h"

typedef struct {
    uint32_t period;
    int8_t model_info[16];
} struct_TYt7YeNdxIDXfczXumtXXB;

typedef struct {
    uint32_t timestamp;
    float phi;
    float theta;
    float psi;
    float quat[4];
    float p;
    float q;
    float r;
    float ax;
    float ay;
    float az;
    float vn;
    float ve;
    float vd;
    float airspeed;
    double lat;
    double lon;
    double alt;
    double lat_0;
    double lon_0;
    double alt_0;
    float x_R;
    float y_R;
    float h_R;
    float h_AGL;
    uint32_t flag;
    uint32_t status;
} INS_Out_Bus;

extern struct_TYt7YeNdxIDXfczXumtXXB INS_EXPORT;/* Variable: INS_EXPORT
                                                 * Referenced by:
                                                 *   '<S4>/Constant'
                                                 *   '<S334>/Constant'
                                                 *   '<S367>/Constant'
                                                 *   '<S375>/Constant'
                                                 *   '<S393>/Constant'
                                                 *   '<S400>/Constant'
                                                 *   '<S11>/Constant'
                                                 *   '<S12>/Constant'
                                                 *   '<S13>/Constant'
                                                 *   '<S14>/Constant'
                                                 *   '<S15>/Constant'
                                                 *   '<S16>/Constant'
                                                 *   '<S17>/Constant'
                                                 *   '<S352>/Constant'
                                                 *   '<S286>/Constant'
                                                 *   '<S287>/Constant'
                                                 *   '<S298>/Constant'
                                                 *   '<S299>/Constant'
                                                 *   '<S300>/Constant'
                                                 */

#endif //X7PRO_DRIVER_INS_H
