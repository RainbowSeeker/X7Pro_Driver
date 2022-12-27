// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/27.
//

#include "module/math/rotation.h"

void icm20689_rotate_to_ned(float* data)
{
    rotation(ROTATION_PITCH_180_YAW_270, data, data + 1, data + 2);
}

void adis16470_rotate_to_ned(float* data)
{
    rotation(ROTATION_PITCH_180_YAW_270, data, data + 1, data + 2);
}

void icm42688_rotate_to_ned(float* data)
{
    rotation(ROTATION_PITCH_180_YAW_270, data, data + 1, data + 2);
}