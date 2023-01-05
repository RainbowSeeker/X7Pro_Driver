

#include <common.h>

#include "module/param/param.h"

/* define parameters */
static param_t __param_list[] = {
        /* gyro_dev 0*/
        /* GYRO_CAL = GYRO - OFFSET */
        PARAM_FLOAT(GYRO0_XOFF, 0.0),
        PARAM_FLOAT(GYRO0_YOFF, 0.0),
        PARAM_FLOAT(GYRO0_ZOFF, 0.0),
        /* ACC_CAL = ROT_M * (ACC-OFFSET)
                   |  XX  XY  XZ |
           ROT_M = |  XY  YY  YZ |
                   |  XZ  YZ  ZZ |   */
        PARAM_FLOAT(ACC0_XOFF, 0.0),
        PARAM_FLOAT(ACC0_YOFF, 0.0),
        PARAM_FLOAT(ACC0_ZOFF, 0.0),
        PARAM_FLOAT(ACC0_XXSCALE, 1.0),
        PARAM_FLOAT(ACC0_YYSCALE, 1.0),
        PARAM_FLOAT(ACC0_ZZSCALE, 1.0),
        PARAM_FLOAT(ACC0_XYSCALE, 0.0),
        PARAM_FLOAT(ACC0_XZSCALE, 0.0),
        PARAM_FLOAT(ACC0_YZSCALE, 0.0),
        /* gyro_dev 1*/
        PARAM_FLOAT(GYRO1_XOFF, 0.0),
        PARAM_FLOAT(GYRO1_YOFF, 0.0),
        PARAM_FLOAT(GYRO1_ZOFF, 0.0),
        PARAM_FLOAT(ACC1_XOFF, 0.0),
        PARAM_FLOAT(ACC1_YOFF, 0.0),
        PARAM_FLOAT(ACC1_ZOFF, 0.0),
        PARAM_FLOAT(ACC1_XXSCALE, 1.0),
        PARAM_FLOAT(ACC1_YYSCALE, 1.0),
        PARAM_FLOAT(ACC1_ZZSCALE, 1.0),
        PARAM_FLOAT(ACC1_XYSCALE, 0.0),
        PARAM_FLOAT(ACC1_XZSCALE, 0.0),
        PARAM_FLOAT(ACC1_YZSCALE, 0.0),
        /* gyro_dev 2*/
//        PARAM_FLOAT(GYRO2_XOFF, 0.0),
//        PARAM_FLOAT(GYRO2_YOFF, 0.0),
//        PARAM_FLOAT(GYRO2_ZOFF, 0.0),
//        PARAM_FLOAT(ACC2_XOFF, 0.0),
//        PARAM_FLOAT(ACC2_YOFF, 0.0),
//        PARAM_FLOAT(ACC2_ZOFF, 0.0),
//        PARAM_FLOAT(ACC2_XXSCALE, 1.0),
//        PARAM_FLOAT(ACC2_YYSCALE, 1.0),
//        PARAM_FLOAT(ACC2_ZZSCALE, 1.0),
//        PARAM_FLOAT(ACC2_XYSCALE, 0.0),
//        PARAM_FLOAT(ACC2_XZSCALE, 0.0),
//        PARAM_FLOAT(ACC2_YZSCALE, 0.0),

        /* MAG_CAL = ROT_M * (MAG-OFFSET)
                   |  XX  XY  XZ |
           ROT_M = |  XY  YY  YZ |
                   |  XZ  YZ  ZZ |   */
        PARAM_FLOAT(MAG0_XOFF, 0.0),
        PARAM_FLOAT(MAG0_YOFF, 0.0),
        PARAM_FLOAT(MAG0_ZOFF, 0.0),
        PARAM_FLOAT(MAG0_XXSCALE, 1.0),
        PARAM_FLOAT(MAG0_YYSCALE, 1.0),
        PARAM_FLOAT(MAG0_ZZSCALE, 1.0),
        PARAM_FLOAT(MAG0_XYSCALE, 0.0),
        PARAM_FLOAT(MAG0_XZSCALE, 0.0),
        PARAM_FLOAT(MAG0_YZSCALE, 0.0),

        PARAM_FLOAT(MAG1_XOFF, 0.0),
        PARAM_FLOAT(MAG1_YOFF, 0.0),
        PARAM_FLOAT(MAG1_ZOFF, 0.0),
        PARAM_FLOAT(MAG1_XXSCALE, 1.0),
        PARAM_FLOAT(MAG1_YYSCALE, 1.0),
        PARAM_FLOAT(MAG1_ZZSCALE, 1.0),
        PARAM_FLOAT(MAG1_XYSCALE, 0.0),
        PARAM_FLOAT(MAG1_XZSCALE, 0.0),
        PARAM_FLOAT(MAG1_YZSCALE, 0.0),
        /* Level Calibration. Roll,Pitch,Yaw offset in rad */
        PARAM_FLOAT(LEVEL_XOFF, 0.0),
        PARAM_FLOAT(LEVEL_YOFF, 0.0),
        PARAM_FLOAT(LEVEL_ZOFF, 0.0),
        /* Airspeed Calibration */
        PARAM_FLOAT(DIFF_PRESS_OFFSET, 0.0),
};
PARAM_GROUP_DEFINE(CALIB, __param_list);