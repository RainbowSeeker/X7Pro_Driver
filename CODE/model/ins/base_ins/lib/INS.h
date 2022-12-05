/*
 * File: INS.h
 *
 * Code generated for Simulink model 'INS'.
 *
 * Model version                  : 1.3716
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Dec  1 10:46:07 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_INS_h_
#define RTW_HEADER_INS_h_
#ifndef INS_COMMON_INCLUDES_
#define INS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* INS_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>
#include "zero_crossing_types.h"

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_INS_T RT_MODEL_INS_T;

#ifndef DEFINED_TYPEDEF_FOR_IMU_Bus_
#define DEFINED_TYPEDEF_FOR_IMU_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T gyr_x;
  real32_T gyr_y;
  real32_T gyr_z;
  real32_T acc_x;
  real32_T acc_y;
  real32_T acc_z;
} IMU_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MAG_Bus_
#define DEFINED_TYPEDEF_FOR_MAG_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T mag_x;
  real32_T mag_y;
  real32_T mag_z;
} MAG_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Barometer_Bus_
#define DEFINED_TYPEDEF_FOR_Barometer_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T pressure;
  real32_T temperature;
} Barometer_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_GPS_uBlox_Bus_
#define DEFINED_TYPEDEF_FOR_GPS_uBlox_Bus_

typedef struct {
  uint32_T timestamp;
  uint32_T iTOW;
  uint16_T year;
  uint8_T month;
  uint8_T day;
  uint8_T hour;
  uint8_T min;
  uint8_T sec;
  uint8_T valid;
  uint32_T tAcc;
  int32_T nano;
  uint8_T fixType;
  uint8_T flags;
  uint8_T reserved1;
  uint8_T numSV;
  int32_T lon;
  int32_T lat;
  int32_T height;
  int32_T hMSL;
  uint32_T hAcc;
  uint32_T vAcc;
  int32_T velN;
  int32_T velE;
  int32_T velD;
  int32_T gSpeed;
  int32_T heading;
  uint32_T sAcc;
  uint32_T headingAcc;
  uint16_T pDOP;
  uint16_T reserved2;
} GPS_uBlox_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Rangefinder_Bus_
#define DEFINED_TYPEDEF_FOR_Rangefinder_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T distance;
} Rangefinder_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Optical_Flow_Bus_
#define DEFINED_TYPEDEF_FOR_Optical_Flow_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T vx;
  real32_T vy;
  uint8_T quality;
  uint8_T reserved1;
  uint16_T reserved2;
} Optical_Flow_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AirSpeed_Bus_
#define DEFINED_TYPEDEF_FOR_AirSpeed_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T diff_pressure;
  real32_T temperature;
} AirSpeed_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_INS_Out_Bus_
#define DEFINED_TYPEDEF_FOR_INS_Out_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T phi;
  real32_T theta;
  real32_T psi;
  real32_T quat[4];
  real32_T p;
  real32_T q;
  real32_T r;
  real32_T ax;
  real32_T ay;
  real32_T az;
  real32_T vn;
  real32_T ve;
  real32_T vd;
  real32_T airspeed;
  real_T lat;
  real_T lon;
  real_T alt;
  real_T lat_0;
  real_T lon_0;
  real_T alt_0;
  real32_T x_R;
  real32_T y_R;
  real32_T h_R;
  real32_T h_AGL;
  uint32_T flag;
  uint32_T status;
} INS_Out_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_Gsh1YUlqR57cYRpVuxG74E_
#define DEFINED_TYPEDEF_FOR_struct_Gsh1YUlqR57cYRpVuxG74E_

typedef struct {
  real_T dt;
  real32_T g;
  real32_T wmm_mag[629];
  real32_T wmm_dec[629];
  real32_T wmm_inc[629];
} struct_Gsh1YUlqR57cYRpVuxG74E;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_TYt7YeNdxIDXfczXumtXXB_
#define DEFINED_TYPEDEF_FOR_struct_TYt7YeNdxIDXfczXumtXXB_

typedef struct {
  uint32_T period;
  int8_T model_info[16];
} struct_TYt7YeNdxIDXfczXumtXXB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_tF4zDkO7m7jeFfXSvhWnpB_
#define DEFINED_TYPEDEF_FOR_struct_tF4zDkO7m7jeFfXSvhWnpB_

typedef struct {
  real32_T GPS_HOR_Q_BIAS;
  real32_T GPS_HOR_Q_SCALE;
  real32_T GPS_VER_Q_BIAS;
  real32_T GPS_VER_Q_SCALE;
  real32_T GPS_VEL_Q_BIAS;
  real32_T GPS_VEL_Q_SCALE;
  real32_T ATT_GAIN;
  real32_T HEADING_GAIN;
  real32_T MAG_GAIN;
  real32_T BIAS_G_GAIN;
  real32_T GPS_POS_GAIN;
  real32_T GPS_ALT_GAIN;
  real32_T GPS_VEL_GAIN;
  real32_T GPS_BIAS_A_GAIN;
  uint32_T GPS_POS_DELAY;
  uint32_T GPS_VEL_DELAY;
  real32_T OPF_VEL_GAIN;
  real32_T OPF_BIAS_A_GAIN;
  uint32_T OPF_VEL_DELAY;
  real32_T BARO_H_GAIN;
  real32_T BARO_VZ_GAIN;
  real32_T BARO_BIAS_AZ_GAIN;
  uint32_T BARO_H_DELAY;
  real32_T RF_H_GAIN;
  real32_T RF_VZ_GAIN;
  real32_T RF_BIAS_AZ_GAIN;
  uint32_T RF_H_DELAY;
} struct_tF4zDkO7m7jeFfXSvhWnpB;

#endif

/* Block signals (default storage) */
typedef struct {
  real_T DataTypeConversion;           /* '<S348>/Data Type Conversion' */
  real_T DataTypeConversion1;          /* '<S348>/Data Type Conversion1' */
  real_T Multiply2;                    /* '<S364>/Multiply2' */
  real_T Rm;                           /* '<S364>/Product3' */
  real32_T Divide;                     /* '<S334>/Divide' */
  real32_T Merge;                      /* '<S244>/Merge' */
  real32_T Merge_e;                    /* '<S245>/Merge' */
  real32_T Merge_n[2];                 /* '<S203>/Merge' */
  real32_T rf_height_bias;             /* '<S236>/Switch' */
  real32_T Sum1[3];                    /* '<S230>/Sum1' */
  real32_T Sum1_p[3];                  /* '<S221>/Sum1' */
  real32_T Sum1_pu[3];                 /* '<S212>/Sum1' */
  real32_T Saturation;                 /* '<S212>/Saturation' */
  real32_T DataTypeConversion_n[2];    /* '<S204>/Data Type Conversion' */
  real32_T Sum1_f[6];                  /* '<S193>/Sum1' */
  real32_T Sum1_o[6];                  /* '<S183>/Sum1' */
  real32_T Merge_l[4];                 /* '<S128>/Merge' */
  real32_T OutportBufferForquat_0[4];  /* '<S112>/DCM To Quaternion' */
  real32_T Integrator[3];              /* '<S91>/Integrator' */
} BlockIO_INS_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay1_DSTATE;                /* '<S317>/Delay1' */
  real_T Delay_DSTATE[2];              /* '<S318>/Delay' */
  real_T Delay1_DSTATE_o[2];           /* '<S318>/Delay1' */
  real32_T Delay_2_DSTATE;             /* '<Root>/Delay' */
  real32_T Delay_3_DSTATE;             /* '<Root>/Delay' */
  real32_T Delay_8_DSTATE[9];          /* '<Root>/Delay' */
  real32_T DiscreteTimeIntegrator5_DSTATE[2];/* '<S393>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S381>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S381>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator1_DSTAT_g;/* '<S361>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator1_DSTAT_m;/* '<S362>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_k;/* '<S361>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_l;/* '<S362>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_d;             /* '<S334>/Delay' */
  real32_T Delay_4_DSTATE;             /* '<S56>/Delay' */
  real32_T Delay_5_DSTATE;             /* '<S56>/Delay' */
  real32_T Delay_6_DSTATE;             /* '<S56>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f;/* '<S271>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTAT_h;/* '<S271>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_b;/* '<S286>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_c;/* '<S298>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S285>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_h;/* '<S297>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_k3;/* '<S299>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_b[3];          /* '<S241>/Delay' */
  real32_T Delay_DSTATE_l[6];          /* '<S199>/Delay' */
  real32_T h_delay_DSTATE[3];          /* '<S234>/h_delay' */
  real32_T Delay_DSTATE_o;             /* '<S239>/Delay' */
  real32_T h_delay_DSTATE_l[75];       /* '<S225>/h_delay' */
  real32_T vd_delay_DSTATE[50];        /* '<S225>/vd_delay' */
  real32_T Delay_DSTATE_dr[3];         /* '<S214>/Delay' */
  real32_T x_delay_DSTATE[5];          /* '<S216>/x_delay' */
  real32_T Delay_DSTATE_h;             /* '<S218>/Delay' */
  real32_T vn_delay_DSTATE[3];         /* '<S197>/vn_delay' */
  real32_T ve_delay_DSTATE[3];         /* '<S197>/ve_delay' */
  real32_T x_delay_DSTATE_k[75];       /* '<S187>/x_delay' */
  real32_T x_delay1_DSTATE[75];        /* '<S187>/x_delay1' */
  real32_T vn_delay_DSTATE_n[50];      /* '<S187>/vn_delay' */
  real32_T vn_delay1_DSTATE[50];       /* '<S187>/vn_delay1' */
  real32_T DiscreteTimeIntegrator5_DSTAT_o[2];/* '<S164>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator5_DSTAT_m;/* '<S162>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator5_DSTA_ow;/* '<S163>/Discrete-Time Integrator5' */
  real32_T Delay_7_DSTATE[9];          /* '<S57>/Delay' */
  real32_T Delay_8_DSTATE_l[9];        /* '<S57>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTAT_kk[4];/* '<S96>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator2_DSTATE[3];/* '<S97>/Discrete-Time Integrator2' */
  real32_T DiscreteTimeIntegrator1_DSTAT_o[3];/* '<S88>/Discrete-Time Integrator1' */
  real32_T Delay_DSTATE_lv[600];       /* '<S86>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTAT_lq[3];/* '<S88>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTAT_b[3];/* '<S94>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTAT_ce[3];/* '<S94>/Discrete-Time Integrator' */
  real32_T Integrator_DSTATE[3];       /* '<S91>/Integrator' */
  real32_T Integrator1_DSTATE[3];      /* '<S91>/Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTAT_bo;/* '<S12>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_hi;/* '<S15>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_b3;/* '<S17>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_ca;/* '<S11>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_e;/* '<S13>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_kg;/* '<S14>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_a;/* '<S16>/Discrete-Time Integrator' */
  int32_T UnitDelay_DSTATE;            /* '<S357>/Unit Delay' */
  uint32_T DelayInput1_DSTATE;         /* '<S403>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_e3;/* '<S399>/Discrete-Time Integrator' */
  uint32_T DiscreteTimeIntegrator_DSTAT_cv;/* '<S400>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_k;       /* '<S395>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S392>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_n;       /* '<S388>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_lg;/* '<S374>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_h;       /* '<S368>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_lp;/* '<S366>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_i;       /* '<S360>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTATE_i;/* '<S351>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_g;       /* '<S337>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_c;       /* '<S340>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_nm;/* '<S333>/Discrete-Time Integrator' */
  uint32_T Delay_DSTATE_f;             /* '<S335>/Delay' */
  uint32_T Delay1_DSTATE_i;            /* '<S334>/Delay1' */
  uint32_T DelayInput1_DSTATE_l;       /* '<S231>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_d;       /* '<S222>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_lg;      /* '<S213>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_m;       /* '<S194>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_d0;      /* '<S184>/Delay Input1' */
  uint32_T Delay_DSTATE_i;             /* '<S121>/Delay' */
  uint32_T Delay_DSTATE_n;             /* '<S118>/Delay' */
  uint32_T Output_DSTATE;              /* '<S4>/Output' */
  real32_T Memory_PreviousInput;       /* '<S236>/Memory' */
  real32_T Memory_PreviousInput_f[3];  /* '<S232>/Memory' */
  real32_T Memory_PreviousInput_b;     /* '<S227>/Memory' */
  real32_T Memory_PreviousInput_e[3];  /* '<S223>/Memory' */
  real32_T Memory_PreviousInput_n[6];  /* '<S195>/Memory' */
  real32_T Memory_PreviousInput_d[2];  /* '<S190>/Memory' */
  real32_T Memory_PreviousInput_h[6];  /* '<S185>/Memory' */
  uint8_T Delay_DSTATE_j;              /* '<S404>/Delay' */
  uint8_T Delay_DSTATE_fp;             /* '<S389>/Delay' */
  uint8_T Delay_DSTATE_bw;             /* '<S369>/Delay' */
  uint8_T Delay_DSTATE_i1;             /* '<S341>/Delay' */
  boolean_T Delay_DSTATE_c;            /* '<S396>/Delay' */
  boolean_T DelayInput1_DSTATE_o;      /* '<S279>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_hg;     /* '<S295>/Delay Input1' */
  boolean_T Delay_DSTATE_k;            /* '<S286>/Delay' */
  boolean_T DelayInput1_DSTATE_j;      /* '<S280>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_p;      /* '<S308>/Delay Input1' */
  boolean_T Delay_DSTATE_k4;           /* '<S298>/Delay' */
  boolean_T Delay_DSTATE_ng;           /* '<S285>/Delay' */
  boolean_T DelayInput1_DSTATE_kh;     /* '<S290>/Delay Input1' */
  boolean_T Delay_DSTATE_c1;           /* '<S297>/Delay' */
  boolean_T DelayInput1_DSTATE_ch;     /* '<S303>/Delay Input1' */
  boolean_T Delay_DSTATE_n2;           /* '<S299>/Delay' */
  boolean_T DelayInput1_DSTATE_jx;     /* '<S313>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_dp;     /* '<S319>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_mw;     /* '<S321>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_d2;     /* '<S238>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_ib;     /* '<S229>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_f;      /* '<S220>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_gn;     /* '<S192>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_pr;     /* '<S116>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_mm;     /* '<S123>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_ff;     /* '<S90>/Delay Input1' */
  boolean_T Delay_DSTATE_bn;           /* '<S12>/Delay' */
  boolean_T Delay_DSTATE_cx;           /* '<S15>/Delay' */
  boolean_T Delay_DSTATE_l0;           /* '<S17>/Delay' */
  boolean_T Delay_DSTATE_cn;           /* '<S11>/Delay' */
  boolean_T Delay_DSTATE_p;            /* '<S13>/Delay' */
  boolean_T Delay_DSTATE_db;           /* '<S14>/Delay' */
  boolean_T Delay_DSTATE_ly;           /* '<S16>/Delay' */
  boolean_T DelayInput1_DSTATE_dx;     /* '<S21>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_mu;     /* '<S26>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_dq;     /* '<S31>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_f4;     /* '<S36>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_ng;     /* '<S41>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_dql;    /* '<S46>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_fq;     /* '<S51>/Delay Input1' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S400>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_k;/* '<S381>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S381>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_l;/* '<S361>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_j;/* '<S362>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_a;/* '<S361>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_j;/* '<S362>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_h;/* '<S271>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevR_d;/* '<S271>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevR_ky;/* '<S286>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_l;/* '<S298>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_d;/* '<S285>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_b;/* '<S297>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_kt;/* '<S299>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_bk;/* '<S96>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevR_p;/* '<S88>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_f;/* '<S88>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevR_o;/* '<S94>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_n;/* '<S94>/Discrete-Time Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S91>/Integrator' */
  int8_T Integrator1_PrevResetState;   /* '<S91>/Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevR_nf;/* '<S12>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_m;/* '<S15>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_dj;/* '<S17>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_h1;/* '<S11>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_as;/* '<S13>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_o;/* '<S14>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_ar;/* '<S16>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator5_IC_LOAD;/* '<S393>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator1_IC_LOAD;/* '<S381>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_j;/* '<S361>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_e;/* '<S362>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_k;/* '<S271>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator5_IC_LO_p;/* '<S164>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator5_IC_LO_n;/* '<S162>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator5_IC_L_ns;/* '<S163>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator_IC_LOADI;/* '<S96>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_i;/* '<S88>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_l;/* '<S94>/Discrete-Time Integrator1' */
  uint8_T Integrator1_IC_LOADING;      /* '<S91>/Integrator1' */
  boolean_T Relay_Mode;                /* '<S392>/Relay' */
  boolean_T Relay_Mode_n;              /* '<S273>/Relay' */
  boolean_T Relay1_Mode;               /* '<S273>/Relay1' */
  boolean_T icLoad;                    /* '<S234>/h_delay' */
  boolean_T icLoad_o;                  /* '<S225>/h_delay' */
  boolean_T icLoad_f;                  /* '<S225>/vd_delay' */
  boolean_T icLoad_a;                  /* '<S216>/x_delay' */
  boolean_T icLoad_h;                  /* '<S197>/vn_delay' */
  boolean_T icLoad_j;                  /* '<S197>/ve_delay' */
  boolean_T icLoad_op;                 /* '<S187>/x_delay' */
  boolean_T icLoad_i;                  /* '<S187>/x_delay1' */
  boolean_T icLoad_m;                  /* '<S187>/vn_delay' */
  boolean_T icLoad_jp;                 /* '<S187>/vn_delay1' */
  boolean_T Relay_Mode_n5;             /* '<S113>/Relay' */
  boolean_T Relay_Mode_nf;             /* '<S92>/Relay' */
  boolean_T Relay1_Mode_l;             /* '<S71>/Relay1' */
  boolean_T Relay1_Mode_j;             /* '<S9>/Relay1' */
  boolean_T Reference_Height_MODE;     /* '<S332>/Reference_Height' */
  boolean_T Rangefinder_Correct_MODE;  /* '<S211>/Rangefinder_Correct' */
  boolean_T GPS_Correct_MODE;          /* '<S210>/GPS_Correct' */
  boolean_T Baro_Correct_MODE;         /* '<S209>/Baro_Correct' */
  boolean_T OptFlow_Correct_MODE;      /* '<S182>/OptFlow_Correct' */
  boolean_T GPS_Correct_MODE_o;        /* '<S181>/GPS_Correct' */
  boolean_T GPS_Meas_Acc_MODE;         /* '<S87>/GPS_Meas_Acc' */
} D_Work_INS_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState WGS84_Model_Trig_ZCE;     /* '<S325>/WGS84_Model' */
  ZCSigState h_delay_Reset_ZCE;        /* '<S234>/h_delay' */
  ZCSigState h_delay_Reset_ZCE_m;      /* '<S225>/h_delay' */
  ZCSigState vd_delay_Reset_ZCE;       /* '<S225>/vd_delay' */
  ZCSigState x_delay_Reset_ZCE;        /* '<S216>/x_delay' */
  ZCSigState vn_delay_Reset_ZCE;       /* '<S197>/vn_delay' */
  ZCSigState ve_delay_Reset_ZCE;       /* '<S197>/ve_delay' */
  ZCSigState x_delay_Reset_ZCE_b;      /* '<S187>/x_delay' */
  ZCSigState x_delay1_Reset_ZCE;       /* '<S187>/x_delay1' */
  ZCSigState vn_delay_Reset_ZCE_p;     /* '<S187>/vn_delay' */
  ZCSigState vn_delay1_Reset_ZCE;      /* '<S187>/vn_delay1' */
} PrevZCSigStates_INS_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  IMU_Bus IMU;                         /* '<Root>/IMU' */
  MAG_Bus MAG;                         /* '<Root>/MAG' */
  Barometer_Bus Barometer;             /* '<Root>/Barometer' */
  GPS_uBlox_Bus GPS_uBlox;             /* '<Root>/GPS_uBlox' */
  Rangefinder_Bus Rangefinder;         /* '<Root>/Rangefinder' */
  Optical_Flow_Bus Optical_Flow;       /* '<Root>/Optical_Flow' */
  AirSpeed_Bus AirSpeed;               /* '<Root>/AirSpeed' */
} ExternalInputs_INS_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  INS_Out_Bus INS_Out;                 /* '<Root>/INS_Out' */
} ExternalOutputs_INS_T;

/* Parameters for system: '<S245>/Baro_Velocity' */
struct rtP_Baro_Velocity_INS_T_ {
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S249>/Constant'
                                        */
};

/* Parameters for system: '<S245>/Baro_Velocity' */
typedef struct rtP_Baro_Velocity_INS_T_ rtP_Baro_Velocity_INS_T;

/* Parameters (default storage) */
struct Parameters_INS_T_ {
  struct_Gsh1YUlqR57cYRpVuxG74E INS_CONST;/* Variable: INS_CONST
                                           * Referenced by:
                                           *   '<S377>/Declination_Lookup_Table'
                                           *   '<S377>/Inclination_Lookup_Table'
                                           *   '<S377>/Magnitude_Lookup_Table'
                                           *   '<S69>/Constant'
                                           *   '<S242>/Constant1'
                                           */
  real_T WMM_LUT_resolution;           /* Mask Parameter: WMM_LUT_resolution
                                        * Referenced by: '<S377>/rad_to_index'
                                        */
  int32_T valid_samples_const;         /* Mask Parameter: valid_samples_const
                                        * Referenced by: '<S358>/Constant'
                                        */
  real32_T Sensor_Valid_acc_max;       /* Mask Parameter: Sensor_Valid_acc_max
                                        * Referenced by: '<S370>/Upper Limit'
                                        */
  real32_T Sensor_Valid_acc_min;       /* Mask Parameter: Sensor_Valid_acc_min
                                        * Referenced by: '<S370>/Lower Limit'
                                        */
  real32_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S93>/Constant'
                                       */
  real32_T CompareToConstant_const_p;
                                    /* Mask Parameter: CompareToConstant_const_p
                                     * Referenced by: '<S114>/Constant'
                                     */
  real32_T CompareToConstant1_const; /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S115>/Constant'
                                      */
  real32_T CompareToConstant_const_n;
                                    /* Mask Parameter: CompareToConstant_const_n
                                     * Referenced by: '<S240>/Constant'
                                     */
  real32_T Sensor_Valid_gyr_max;       /* Mask Parameter: Sensor_Valid_gyr_max
                                        * Referenced by: '<S371>/Upper Limit'
                                        */
  real32_T Sensor_Valid_gyr_min;       /* Mask Parameter: Sensor_Valid_gyr_min
                                        * Referenced by: '<S371>/Lower Limit'
                                        */
  real32_T IntervalTest_lowlimit;      /* Mask Parameter: IntervalTest_lowlimit
                                        * Referenced by: '<S117>/Lower Limit'
                                        */
  real32_T Sensor_Valid_mag_max;       /* Mask Parameter: Sensor_Valid_mag_max
                                        * Referenced by: '<S390>/Upper Limit'
                                        */
  real32_T Sensor_Valid_mag_min;       /* Mask Parameter: Sensor_Valid_mag_min
                                        * Referenced by: '<S390>/Lower Limit'
                                        */
  real32_T Sensor_Valid_max_alt;       /* Mask Parameter: Sensor_Valid_max_alt
                                        * Referenced by: '<S405>/Upper Limit'
                                        */
  real32_T Sensor_Valid_max_pressure;
                                    /* Mask Parameter: Sensor_Valid_max_pressure
                                     * Referenced by: '<S342>/Upper Limit'
                                     */
  real32_T Sensor_Valid_max_temp;      /* Mask Parameter: Sensor_Valid_max_temp
                                        * Referenced by: '<S343>/Upper Limit'
                                        */
  real32_T Sensor_Valid_max_vel;       /* Mask Parameter: Sensor_Valid_max_vel
                                        * Referenced by:
                                        *   '<S397>/Upper Limit'
                                        *   '<S398>/Upper Limit'
                                        */
  real32_T Sensor_Valid_min_alt;       /* Mask Parameter: Sensor_Valid_min_alt
                                        * Referenced by: '<S405>/Lower Limit'
                                        */
  real32_T Sensor_Valid_min_pressure;
                                    /* Mask Parameter: Sensor_Valid_min_pressure
                                     * Referenced by: '<S342>/Lower Limit'
                                     */
  real32_T Sensor_Valid_min_temp;      /* Mask Parameter: Sensor_Valid_min_temp
                                        * Referenced by: '<S343>/Lower Limit'
                                        */
  real32_T Sensor_Valid_min_vel;       /* Mask Parameter: Sensor_Valid_min_vel
                                        * Referenced by:
                                        *   '<S397>/Lower Limit'
                                        *   '<S398>/Lower Limit'
                                        */
  real32_T valid_check2_time_out;      /* Mask Parameter: valid_check2_time_out
                                        * Referenced by: '<S23>/Constant'
                                        */
  real32_T valid_check5_time_out;      /* Mask Parameter: valid_check5_time_out
                                        * Referenced by: '<S38>/Constant'
                                        */
  real32_T valid_check8_time_out;      /* Mask Parameter: valid_check8_time_out
                                        * Referenced by: '<S48>/Constant'
                                        */
  real32_T valid_check1_time_out;      /* Mask Parameter: valid_check1_time_out
                                        * Referenced by: '<S18>/Constant'
                                        */
  real32_T valid_check3_time_out;      /* Mask Parameter: valid_check3_time_out
                                        * Referenced by: '<S28>/Constant'
                                        */
  real32_T valid_check4_time_out;      /* Mask Parameter: valid_check4_time_out
                                        * Referenced by: '<S33>/Constant'
                                        */
  real32_T valid_check6_time_out;      /* Mask Parameter: valid_check6_time_out
                                        * Referenced by: '<S43>/Constant'
                                        */
  real32_T valid_hold1_time_out;       /* Mask Parameter: valid_hold1_time_out
                                        * Referenced by: '<S292>/Constant'
                                        */
  real32_T valid_hold1_time_out_m;     /* Mask Parameter: valid_hold1_time_out_m
                                        * Referenced by: '<S305>/Constant'
                                        */
  real32_T valid_hold_time_out;        /* Mask Parameter: valid_hold_time_out
                                        * Referenced by: '<S287>/Constant'
                                        */
  real32_T valid_hold_time_out_d;      /* Mask Parameter: valid_hold_time_out_d
                                        * Referenced by: '<S300>/Constant'
                                        */
  real32_T valid_hold2_time_out;       /* Mask Parameter: valid_hold2_time_out
                                        * Referenced by: '<S310>/Constant'
                                        */
  real32_T IntervalTest_uplimit;       /* Mask Parameter: IntervalTest_uplimit
                                        * Referenced by: '<S117>/Upper Limit'
                                        */
  uint32_T valid_samples_const_k;      /* Mask Parameter: valid_samples_const_k
                                        * Referenced by: '<S125>/Constant'
                                        */
  uint32_T CompareToConstant_const_nb;
                                   /* Mask Parameter: CompareToConstant_const_nb
                                    * Referenced by: '<S336>/Constant'
                                    */
  uint32_T CompareToConstant4_const; /* Mask Parameter: CompareToConstant4_const
                                      * Referenced by: '<S359>/Constant'
                                      */
  uint32_T CompareToConstant_const_d;
                                    /* Mask Parameter: CompareToConstant_const_d
                                     * Referenced by: '<S355>/Constant'
                                     */
  uint32_T CompareToConstant_const_m;
                                    /* Mask Parameter: CompareToConstant_const_m
                                     * Referenced by: '<S406>/Constant'
                                     */
  uint32_T IntervalTest3_lowlimit;     /* Mask Parameter: IntervalTest3_lowlimit
                                        * Referenced by: '<S338>/Lower Limit'
                                        */
  uint32_T Sensor_Valid_timeout;       /* Mask Parameter: Sensor_Valid_timeout
                                        * Referenced by: '<S339>/Constant'
                                        */
  uint32_T Sensor_Valid_timeout_a;     /* Mask Parameter: Sensor_Valid_timeout_a
                                        * Referenced by: '<S367>/Constant'
                                        */
  uint32_T Sensor_Valid_timeout_b;     /* Mask Parameter: Sensor_Valid_timeout_b
                                        * Referenced by: '<S387>/Constant'
                                        */
  uint32_T Sensor_Valid_timeout_ai;   /* Mask Parameter: Sensor_Valid_timeout_ai
                                       * Referenced by: '<S394>/Constant'
                                       */
  uint32_T Sensor_Valid_timeout_p;     /* Mask Parameter: Sensor_Valid_timeout_p
                                        * Referenced by: '<S402>/Constant'
                                        */
  uint32_T IntervalTest3_uplimit;      /* Mask Parameter: IntervalTest3_uplimit
                                        * Referenced by: '<S338>/Upper Limit'
                                        */
  uint32_T DetectChange_vinit;         /* Mask Parameter: DetectChange_vinit
                                        * Referenced by: '<S184>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_l;       /* Mask Parameter: DetectChange_vinit_l
                                        * Referenced by: '<S194>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_m;       /* Mask Parameter: DetectChange_vinit_m
                                        * Referenced by: '<S213>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_h;       /* Mask Parameter: DetectChange_vinit_h
                                        * Referenced by: '<S222>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_g;       /* Mask Parameter: DetectChange_vinit_g
                                        * Referenced by: '<S231>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_d;       /* Mask Parameter: DetectChange_vinit_d
                                        * Referenced by: '<S337>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_n;       /* Mask Parameter: DetectChange_vinit_n
                                        * Referenced by: '<S340>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_e;       /* Mask Parameter: DetectChange_vinit_e
                                        * Referenced by: '<S360>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_md;      /* Mask Parameter: DetectChange_vinit_md
                                        * Referenced by: '<S368>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_lp;      /* Mask Parameter: DetectChange_vinit_lp
                                        * Referenced by: '<S388>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_j;       /* Mask Parameter: DetectChange_vinit_j
                                        * Referenced by: '<S395>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_c;       /* Mask Parameter: DetectChange_vinit_c
                                        * Referenced by: '<S403>/Delay Input1'
                                        */
  boolean_T CompareToConstant1_const_m;
                                   /* Mask Parameter: CompareToConstant1_const_m
                                    * Referenced by: '<S24>/Constant'
                                    */
  boolean_T CompareToConstant1_const_j;
                                   /* Mask Parameter: CompareToConstant1_const_j
                                    * Referenced by: '<S39>/Constant'
                                    */
  boolean_T CompareToConstant1_const_g;
                                   /* Mask Parameter: CompareToConstant1_const_g
                                    * Referenced by: '<S49>/Constant'
                                    */
  boolean_T CompareToConstant1_const_e;
                                   /* Mask Parameter: CompareToConstant1_const_e
                                    * Referenced by: '<S19>/Constant'
                                    */
  boolean_T CompareToConstant1_const_ei;
                                  /* Mask Parameter: CompareToConstant1_const_ei
                                   * Referenced by: '<S29>/Constant'
                                   */
  boolean_T CompareToConstant1_const_ec;
                                  /* Mask Parameter: CompareToConstant1_const_ec
                                   * Referenced by: '<S34>/Constant'
                                   */
  boolean_T CompareToConstant1_const_em;
                                  /* Mask Parameter: CompareToConstant1_const_em
                                   * Referenced by: '<S44>/Constant'
                                   */
  boolean_T CompareToConstant2_const;/* Mask Parameter: CompareToConstant2_const
                                      * Referenced by: '<S20>/Constant'
                                      */
  boolean_T CompareToConstant2_const_c;
                                   /* Mask Parameter: CompareToConstant2_const_c
                                    * Referenced by: '<S25>/Constant'
                                    */
  boolean_T CompareToConstant2_const_n;
                                   /* Mask Parameter: CompareToConstant2_const_n
                                    * Referenced by: '<S30>/Constant'
                                    */
  boolean_T CompareToConstant2_const_b;
                                   /* Mask Parameter: CompareToConstant2_const_b
                                    * Referenced by: '<S35>/Constant'
                                    */
  boolean_T CompareToConstant2_const_i;
                                   /* Mask Parameter: CompareToConstant2_const_i
                                    * Referenced by: '<S40>/Constant'
                                    */
  boolean_T CompareToConstant2_const_l;
                                   /* Mask Parameter: CompareToConstant2_const_l
                                    * Referenced by: '<S45>/Constant'
                                    */
  boolean_T CompareToConstant2_const_i1;
                                  /* Mask Parameter: CompareToConstant2_const_i1
                                   * Referenced by: '<S50>/Constant'
                                   */
  boolean_T CompareToConstant1_const_i;
                                   /* Mask Parameter: CompareToConstant1_const_i
                                    * Referenced by: '<S293>/Constant'
                                    */
  boolean_T CompareToConstant2_const_j;
                                   /* Mask Parameter: CompareToConstant2_const_j
                                    * Referenced by: '<S294>/Constant'
                                    */
  boolean_T CompareToConstant1_const_a;
                                   /* Mask Parameter: CompareToConstant1_const_a
                                    * Referenced by: '<S306>/Constant'
                                    */
  boolean_T CompareToConstant2_const_d;
                                   /* Mask Parameter: CompareToConstant2_const_d
                                    * Referenced by: '<S307>/Constant'
                                    */
  boolean_T CompareToConstant1_const_h;
                                   /* Mask Parameter: CompareToConstant1_const_h
                                    * Referenced by: '<S288>/Constant'
                                    */
  boolean_T CompareToConstant2_const_a;
                                   /* Mask Parameter: CompareToConstant2_const_a
                                    * Referenced by: '<S289>/Constant'
                                    */
  boolean_T CompareToConstant1_const_hv;
                                  /* Mask Parameter: CompareToConstant1_const_hv
                                   * Referenced by: '<S301>/Constant'
                                   */
  boolean_T CompareToConstant2_const_dj;
                                  /* Mask Parameter: CompareToConstant2_const_dj
                                   * Referenced by: '<S302>/Constant'
                                   */
  boolean_T CompareToConstant1_const_l;
                                   /* Mask Parameter: CompareToConstant1_const_l
                                    * Referenced by: '<S311>/Constant'
                                    */
  boolean_T CompareToConstant2_const_h;
                                   /* Mask Parameter: CompareToConstant2_const_h
                                    * Referenced by: '<S312>/Constant'
                                    */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S21>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_c;
                                   /* Mask Parameter: DetectRisePositive_vinit_c
                                    * Referenced by: '<S26>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_m;
                                   /* Mask Parameter: DetectRisePositive_vinit_m
                                    * Referenced by: '<S31>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_k;
                                   /* Mask Parameter: DetectRisePositive_vinit_k
                                    * Referenced by: '<S36>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_a;
                                   /* Mask Parameter: DetectRisePositive_vinit_a
                                    * Referenced by: '<S41>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_f;
                                   /* Mask Parameter: DetectRisePositive_vinit_f
                                    * Referenced by: '<S46>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_l;
                                   /* Mask Parameter: DetectRisePositive_vinit_l
                                    * Referenced by: '<S51>/Delay Input1'
                                    */
  boolean_T DetectIncrease_vinit;      /* Mask Parameter: DetectIncrease_vinit
                                        * Referenced by: '<S90>/Delay Input1'
                                        */
  boolean_T DetectRisePositive_vinit_fc;
                                  /* Mask Parameter: DetectRisePositive_vinit_fc
                                   * Referenced by: '<S116>/Delay Input1'
                                   */
  boolean_T DetectRisePositive1_vinit;
                                    /* Mask Parameter: DetectRisePositive1_vinit
                                     * Referenced by: '<S123>/Delay Input1'
                                     */
  boolean_T DetectIncrease_vinit_p;    /* Mask Parameter: DetectIncrease_vinit_p
                                        * Referenced by: '<S192>/Delay Input1'
                                        */
  boolean_T DetectIncrease_vinit_c;    /* Mask Parameter: DetectIncrease_vinit_c
                                        * Referenced by: '<S220>/Delay Input1'
                                        */
  boolean_T DetectIncrease_vinit_j;    /* Mask Parameter: DetectIncrease_vinit_j
                                        * Referenced by: '<S229>/Delay Input1'
                                        */
  boolean_T DetectIncrease_vinit_g;    /* Mask Parameter: DetectIncrease_vinit_g
                                        * Referenced by: '<S238>/Delay Input1'
                                        */
  boolean_T DetectRisePositive_vinit_me;
                                  /* Mask Parameter: DetectRisePositive_vinit_me
                                   * Referenced by: '<S279>/Delay Input1'
                                   */
  boolean_T DetectRisePositive_vinit_o;
                                   /* Mask Parameter: DetectRisePositive_vinit_o
                                    * Referenced by: '<S295>/Delay Input1'
                                    */
  boolean_T DetectRisePositive1_vinit_h;
                                  /* Mask Parameter: DetectRisePositive1_vinit_h
                                   * Referenced by: '<S280>/Delay Input1'
                                   */
  boolean_T DetectRisePositive_vinit_h;
                                   /* Mask Parameter: DetectRisePositive_vinit_h
                                    * Referenced by: '<S308>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_d;
                                   /* Mask Parameter: DetectRisePositive_vinit_d
                                    * Referenced by: '<S290>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_dn;
                                  /* Mask Parameter: DetectRisePositive_vinit_dn
                                   * Referenced by: '<S303>/Delay Input1'
                                   */
  boolean_T DetectRisePositive_vinit_cj;
                                  /* Mask Parameter: DetectRisePositive_vinit_cj
                                   * Referenced by: '<S313>/Delay Input1'
                                   */
  boolean_T DetectRisePositive3_vinit;
                                    /* Mask Parameter: DetectRisePositive3_vinit
                                     * Referenced by: '<S319>/Delay Input1'
                                     */
  boolean_T DetectRisePositive3_vinit_h;
                                  /* Mask Parameter: DetectRisePositive3_vinit_h
                                   * Referenced by: '<S321>/Delay Input1'
                                   */
  uint8_T CompareToConstant1_const_n;
                                   /* Mask Parameter: CompareToConstant1_const_n
                                    * Referenced by: '<S356>/Constant'
                                    */
  uint8_T CompareToConstant_const_i;/* Mask Parameter: CompareToConstant_const_i
                                     * Referenced by: '<S344>/Constant'
                                     */
  uint8_T CompareToConstant1_const_la;
                                  /* Mask Parameter: CompareToConstant1_const_la
                                   * Referenced by: '<S345>/Constant'
                                   */
  uint8_T CompareToConstant2_const_bv;
                                  /* Mask Parameter: CompareToConstant2_const_bv
                                   * Referenced by: '<S349>/Constant'
                                   */
  uint8_T Sensor_Valid_q_high;         /* Mask Parameter: Sensor_Valid_q_high
                                        * Referenced by: '<S392>/Relay'
                                        */
  uint8_T Sensor_Valid_q_low;          /* Mask Parameter: Sensor_Valid_q_low
                                        * Referenced by: '<S392>/Relay'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 10e7
                                        * Referenced by: '<S178>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 1e-6
                                        * Referenced by: '<S178>/Saturation'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S178>/Constant'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S317>/Delay1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S318>/Delay'
                                        */
  real_T Delay1_InitialCondition_e;    /* Expression: 0.0
                                        * Referenced by: '<S318>/Delay1'
                                        */
  real_T lon_0_rad_Y0;                 /* Expression: 0
                                        * Referenced by: '<S348>/lon_0_rad'
                                        */
  real_T lat_0_rad_Y0;                 /* Expression: 0
                                        * Referenced by: '<S348>/lat_0_rad'
                                        */
  real_T dx_dlat_Y0;                   /* Expression: 1
                                        * Referenced by: '<S348>/dx_dlat'
                                        */
  real_T dy_dlon_Y0;                   /* Expression: 1
                                        * Referenced by: '<S348>/dy_dlon'
                                        */
  real_T dz_dh_Y0;                     /* Expression: 1
                                        * Referenced by: '<S348>/dz_dh'
                                        */
  real_T Constant_Value_n;             /* Expression: 1
                                        * Referenced by: '<S364>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S364>/Constant1'
                                        */
  real_T Constant2_Value;              /* Expression: 2
                                        * Referenced by: '<S364>/Constant2'
                                        */
  real_T R_Value;                      /* Expression: 6378137
                                        * Referenced by: '<S364>/R'
                                        */
  real_T f_Value;                      /* Expression: 1/298.257223563
                                        * Referenced by: '<S364>/f'
                                        */
  int32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S357>/Unit Delay'
                                */
  int32_T Saturation_UpperSat_a;    /* Computed Parameter: Saturation_UpperSat_a
                                     * Referenced by: '<S357>/Saturation'
                                     */
  int32_T Saturation_LowerSat_f;    /* Computed Parameter: Saturation_LowerSat_f
                                     * Referenced by: '<S357>/Saturation'
                                     */
  int32_T offset_Value[2];             /* Computed Parameter: offset_Value
                                        * Referenced by: '<S377>/offset'
                                        */
  int32_T Saturation1_UpperSat[2];   /* Computed Parameter: Saturation1_UpperSat
                                      * Referenced by: '<S377>/Saturation1'
                                      */
  int32_T Saturation1_LowerSat;      /* Computed Parameter: Saturation1_LowerSat
                                      * Referenced by: '<S377>/Saturation1'
                                      */
  int32_T Gain_Gain;                   /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S346>/Gain'
                                        */
  int32_T Gain1_Gain;                  /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S346>/Gain1'
                                        */
  int32_T Gain2_Gain;                  /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S346>/Gain2'
                                        */
  int32_T Scalefactor3_Gain;           /* Computed Parameter: Scalefactor3_Gain
                                        * Referenced by: '<S346>/Scalefactor3'
                                        */
  int32_T Scalefactor1_Gain;           /* Computed Parameter: Scalefactor1_Gain
                                        * Referenced by: '<S346>/Scalefactor1'
                                        */
  int32_T Scalefactor2_Gain;           /* Computed Parameter: Scalefactor2_Gain
                                        * Referenced by: '<S346>/Scalefactor2'
                                        */
  real32_T Constant_Value_h;           /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S53>/Constant'
                                        */
  real32_T Constant_Value_j;           /* Computed Parameter: Constant_Value_j
                                        * Referenced by: '<S54>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<S12>/Discrete-Time Integrator'
                            */
  real32_T DiscreteTimeIntegrator_IC;
                                /* Computed Parameter: DiscreteTimeIntegrator_IC
                                 * Referenced by: '<S12>/Discrete-Time Integrator'
                                 */
  real32_T DiscreteTimeIntegrator_UpperSat;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperSat
                           * Referenced by: '<S12>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerSat;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerSat
                           * Referenced by: '<S12>/Discrete-Time Integrator'
                           */
  real32_T Gain10_Gain;                /* Computed Parameter: Gain10_Gain
                                        * Referenced by: '<S8>/Gain10'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_i;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_i
                           * Referenced by: '<S15>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_i;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_i
                               * Referenced by: '<S15>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_g;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_g
                           * Referenced by: '<S15>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_j;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_j
                           * Referenced by: '<S15>/Discrete-Time Integrator'
                           */
  real32_T Relay1_OnVal;               /* Computed Parameter: Relay1_OnVal
                                        * Referenced by: '<S9>/Relay1'
                                        */
  real32_T Relay1_OffVal;              /* Computed Parameter: Relay1_OffVal
                                        * Referenced by: '<S9>/Relay1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_m;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_m
                           * Referenced by: '<S17>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_o;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_o
                               * Referenced by: '<S17>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_d;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_d
                           * Referenced by: '<S17>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_n;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_n
                           * Referenced by: '<S17>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainva_k;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                           * Referenced by: '<S11>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_l;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_l
                               * Referenced by: '<S11>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_n;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_n
                           * Referenced by: '<S11>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_l;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_l
                           * Referenced by: '<S11>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainva_p;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_p
                           * Referenced by: '<S13>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_j;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_j
                               * Referenced by: '<S13>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_f;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_f
                           * Referenced by: '<S13>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_f;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_f
                           * Referenced by: '<S13>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainv_me;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_me
                           * Referenced by: '<S14>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_ig;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_ig
                              * Referenced by: '<S14>/Discrete-Time Integrator'
                              */
  real32_T DiscreteTimeIntegrator_UpperS_m;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_m
                           * Referenced by: '<S14>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_i;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_i
                           * Referenced by: '<S14>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainv_my;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_my
                           * Referenced by: '<S16>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_e;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_e
                               * Referenced by: '<S16>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_Upper_ml;
                          /* Computed Parameter: DiscreteTimeIntegrator_Upper_ml
                           * Referenced by: '<S16>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_g;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_g
                           * Referenced by: '<S16>/Discrete-Time Integrator'
                           */
  real32_T Constant_Value_c;           /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S64>/Constant'
                                        */
  real32_T Saturation_UpperSat_h;   /* Computed Parameter: Saturation_UpperSat_h
                                     * Referenced by: '<S64>/Saturation'
                                     */
  real32_T Saturation_LowerSat_m;   /* Computed Parameter: Saturation_LowerSat_m
                                     * Referenced by: '<S64>/Saturation'
                                     */
  real32_T Constant1_Value_o;          /* Computed Parameter: Constant1_Value_o
                                        * Referenced by: '<S64>/Constant1'
                                        */
  real32_T Constant2_Value_d;          /* Computed Parameter: Constant2_Value_d
                                        * Referenced by: '<S64>/Constant2'
                                        */
  real32_T Gain_Gain_f;                /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S63>/Gain'
                                        */
  real32_T Constant_Value_j1;          /* Computed Parameter: Constant_Value_j1
                                        * Referenced by: '<S67>/Constant'
                                        */
  real32_T Constant1_Value_j;          /* Computed Parameter: Constant1_Value_j
                                        * Referenced by: '<S67>/Constant1'
                                        */
  real32_T Constant2_Value_a;          /* Computed Parameter: Constant2_Value_a
                                        * Referenced by: '<S67>/Constant2'
                                        */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S67>/Constant3'
                                        */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S67>/Constant4'
                                        */
  real32_T Gain_Gain_n;                /* Computed Parameter: Gain_Gain_n
                                        * Referenced by: '<S67>/Gain'
                                        */
  real32_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S81>/Constant'
                                        */
  real32_T Constant_Value_jy;          /* Computed Parameter: Constant_Value_jy
                                        * Referenced by: '<S82>/Constant'
                                        */
  real32_T gps_acc_O_mPs2_Y0;          /* Computed Parameter: gps_acc_O_mPs2_Y0
                                        * Referenced by: '<S91>/gps_acc_O_mPs2'
                                        */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S91>/Integrator'
                                        */
  real32_T Integrator_IC;              /* Computed Parameter: Integrator_IC
                                        * Referenced by: '<S91>/Integrator'
                                        */
  real32_T Integrator1_gainval;       /* Computed Parameter: Integrator1_gainval
                                       * Referenced by: '<S91>/Integrator1'
                                       */
  real32_T gain_Gain;                  /* Computed Parameter: gain_Gain
                                        * Referenced by: '<S91>/gain'
                                        */
  real32_T gain1_Gain;                 /* Computed Parameter: gain1_Gain
                                        * Referenced by: '<S91>/gain1'
                                        */
  real32_T Constant_Value_g;           /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S88>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator1_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                           * Referenced by: '<S88>/Discrete-Time Integrator1'
                           */
  real32_T Relay_OnVal;                /* Computed Parameter: Relay_OnVal
                                        * Referenced by: '<S92>/Relay'
                                        */
  real32_T Relay_OffVal;               /* Computed Parameter: Relay_OffVal
                                        * Referenced by: '<S92>/Relay'
                                        */
  real32_T Relay_YOn;                  /* Computed Parameter: Relay_YOn
                                        * Referenced by: '<S92>/Relay'
                                        */
  real32_T Relay_YOff;                 /* Computed Parameter: Relay_YOff
                                        * Referenced by: '<S92>/Relay'
                                        */
  real32_T Delay_InitialCondition_m;
                                 /* Computed Parameter: Delay_InitialCondition_m
                                  * Referenced by: '<S86>/Delay'
                                  */
  real32_T gravity_Value[3];           /* Expression: [0;0;-INS_CONST.g]
                                        * Referenced by: '<S73>/gravity'
                                        */
  real32_T Gain1_Gain_l;               /* Computed Parameter: Gain1_Gain_l
                                        * Referenced by: '<S74>/Gain1'
                                        */
  real32_T Gain2_Gain_i;               /* Computed Parameter: Gain2_Gain_i
                                        * Referenced by: '<S74>/Gain2'
                                        */
  real32_T DeadZone2_Start;            /* Computed Parameter: DeadZone2_Start
                                        * Referenced by: '<S74>/Dead Zone2'
                                        */
  real32_T DeadZone2_End;              /* Computed Parameter: DeadZone2_End
                                        * Referenced by: '<S74>/Dead Zone2'
                                        */
  real32_T Saturation_UpperSat_k;   /* Computed Parameter: Saturation_UpperSat_k
                                     * Referenced by: '<S74>/Saturation'
                                     */
  real32_T Saturation_LowerSat_k;   /* Computed Parameter: Saturation_LowerSat_k
                                     * Referenced by: '<S74>/Saturation'
                                     */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S81>/Switch'
                                        */
  real32_T Switch_Threshold_m;         /* Computed Parameter: Switch_Threshold_m
                                        * Referenced by: '<S82>/Switch'
                                        */
  real32_T max_Value;                  /* Computed Parameter: max_Value
                                        * Referenced by: '<S80>/max'
                                        */
  real32_T Saturation_UpperSat_e;   /* Computed Parameter: Saturation_UpperSat_e
                                     * Referenced by: '<S80>/Saturation'
                                     */
  real32_T Saturation_LowerSat_fo; /* Computed Parameter: Saturation_LowerSat_fo
                                    * Referenced by: '<S80>/Saturation'
                                    */
  real32_T Constant1_Value_n;          /* Computed Parameter: Constant1_Value_n
                                        * Referenced by: '<S80>/Constant1'
                                        */
  real32_T Gain_Gain_o[3];
                        /* Expression: [INS_PARAM.ATT_GAIN;INS_PARAM.ATT_GAIN;0]
                         * Referenced by: '<S75>/Gain'
                         */
  real32_T DiscreteTimeIntegrator_gainva_n;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_n
                           * Referenced by: '<S88>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_a;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_a
                               * Referenced by: '<S88>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_p;                /* Computed Parameter: Gain_Gain_p
                                        * Referenced by: '<S88>/Gain'
                                        */
  real32_T Gain1_Gain_p;               /* Computed Parameter: Gain1_Gain_p
                                        * Referenced by: '<S88>/Gain1'
                                        */
  real32_T Relay1_OnVal_i;             /* Computed Parameter: Relay1_OnVal_i
                                        * Referenced by: '<S71>/Relay1'
                                        */
  real32_T Relay1_OffVal_o;            /* Computed Parameter: Relay1_OffVal_o
                                        * Referenced by: '<S71>/Relay1'
                                        */
  real32_T Relay1_YOn;                 /* Computed Parameter: Relay1_YOn
                                        * Referenced by: '<S71>/Relay1'
                                        */
  real32_T Relay1_YOff;                /* Computed Parameter: Relay1_YOff
                                        * Referenced by: '<S71>/Relay1'
                                        */
  real32_T Constant_Value_no;          /* Computed Parameter: Constant_Value_no
                                        * Referenced by: '<S94>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator1_gainv_j;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_j
                           * Referenced by: '<S94>/Discrete-Time Integrator1'
                           */
  real32_T Saturation2_UpperSat;     /* Computed Parameter: Saturation2_UpperSat
                                      * Referenced by: '<S69>/Saturation2'
                                      */
  real32_T Saturation2_LowerSat;     /* Computed Parameter: Saturation2_LowerSat
                                      * Referenced by: '<S69>/Saturation2'
                                      */
  real32_T DiscreteTimeIntegrator_gainv_kw;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_kw
                           * Referenced by: '<S94>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_m;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_m
                               * Referenced by: '<S94>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_i;                /* Computed Parameter: Gain_Gain_i
                                        * Referenced by: '<S94>/Gain'
                                        */
  real32_T Gain1_Gain_i;               /* Computed Parameter: Gain1_Gain_i
                                        * Referenced by: '<S94>/Gain1'
                                        */
  real32_T Constant_Value_p;           /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S96>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_j;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_j
                           * Referenced by: '<S96>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator2_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator2_gainval
                           * Referenced by: '<S97>/Discrete-Time Integrator2'
                           */
  real32_T DiscreteTimeIntegrator2_IC;
                               /* Computed Parameter: DiscreteTimeIntegrator2_IC
                                * Referenced by: '<S97>/Discrete-Time Integrator2'
                                */
  real32_T DiscreteTimeIntegrator2_UpperSa;
                          /* Computed Parameter: DiscreteTimeIntegrator2_UpperSa
                           * Referenced by: '<S97>/Discrete-Time Integrator2'
                           */
  real32_T DiscreteTimeIntegrator2_LowerSa;
                          /* Computed Parameter: DiscreteTimeIntegrator2_LowerSa
                           * Referenced by: '<S97>/Discrete-Time Integrator2'
                           */
  real32_T Gain2_Gain_i4;              /* Computed Parameter: Gain2_Gain_i4
                                        * Referenced by: '<S96>/Gain2'
                                        */
  real32_T Gain_Gain_e;                /* Computed Parameter: Gain_Gain_e
                                        * Referenced by: '<S107>/Gain'
                                        */
  real32_T Gain1_Gain_pl;              /* Computed Parameter: Gain1_Gain_pl
                                        * Referenced by: '<S107>/Gain1'
                                        */
  real32_T Gain_Gain_j;                /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S108>/Gain'
                                        */
  real32_T Gain1_Gain_b;               /* Computed Parameter: Gain1_Gain_b
                                        * Referenced by: '<S108>/Gain1'
                                        */
  real32_T Gain_Gain_oz;               /* Computed Parameter: Gain_Gain_oz
                                        * Referenced by: '<S109>/Gain'
                                        */
  real32_T Gain1_Gain_f;               /* Computed Parameter: Gain1_Gain_f
                                        * Referenced by: '<S109>/Gain1'
                                        */
  real32_T Delay_7_InitialCondition;
                                 /* Computed Parameter: Delay_7_InitialCondition
                                  * Referenced by: '<S57>/Delay'
                                  */
  real32_T Delay_8_InitialCondition;
                                 /* Computed Parameter: Delay_8_InitialCondition
                                  * Referenced by: '<S57>/Delay'
                                  */
  real32_T Constant_Value_c0;          /* Computed Parameter: Constant_Value_c0
                                        * Referenced by: '<S138>/Constant'
                                        */
  real32_T Gain_Gain_eu;               /* Computed Parameter: Gain_Gain_eu
                                        * Referenced by: '<S138>/Gain'
                                        */
  real32_T Gain1_Gain_h;               /* Computed Parameter: Gain1_Gain_h
                                        * Referenced by: '<S138>/Gain1'
                                        */
  real32_T Constant1_Value_e;          /* Computed Parameter: Constant1_Value_e
                                        * Referenced by: '<S151>/Constant1'
                                        */
  real32_T Constant2_Value_az[2];      /* Computed Parameter: Constant2_Value_az
                                        * Referenced by: '<S151>/Constant2'
                                        */
  real32_T Constant_Value_ae;          /* Computed Parameter: Constant_Value_ae
                                        * Referenced by: '<S152>/Constant'
                                        */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S140>/Gain'
                                        */
  real32_T Gain1_Gain_g;               /* Computed Parameter: Gain1_Gain_g
                                        * Referenced by: '<S140>/Gain1'
                                        */
  real32_T Gain3_Gain;                 /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<S140>/Gain3'
                                        */
  real32_T Gain4_Gain;                 /* Computed Parameter: Gain4_Gain
                                        * Referenced by: '<S140>/Gain4'
                                        */
  real32_T Constant1_Value_l;          /* Computed Parameter: Constant1_Value_l
                                        * Referenced by: '<S156>/Constant1'
                                        */
  real32_T Constant2_Value_o[2];       /* Computed Parameter: Constant2_Value_o
                                        * Referenced by: '<S156>/Constant2'
                                        */
  real32_T Constant_Value_f;           /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<S157>/Constant'
                                        */
  real32_T Gain_Gain_l;                /* Computed Parameter: Gain_Gain_l
                                        * Referenced by: '<S141>/Gain'
                                        */
  real32_T Gain1_Gain_m;               /* Computed Parameter: Gain1_Gain_m
                                        * Referenced by: '<S141>/Gain1'
                                        */
  real32_T Gain2_Gain_o;               /* Computed Parameter: Gain2_Gain_o
                                        * Referenced by: '<S141>/Gain2'
                                        */
  real32_T Gain3_Gain_e;               /* Computed Parameter: Gain3_Gain_e
                                        * Referenced by: '<S141>/Gain3'
                                        */
  real32_T Constant1_Value_a;          /* Computed Parameter: Constant1_Value_a
                                        * Referenced by: '<S146>/Constant1'
                                        */
  real32_T Constant2_Value_m[2];       /* Computed Parameter: Constant2_Value_m
                                        * Referenced by: '<S146>/Constant2'
                                        */
  real32_T Constant_Value_hd;          /* Computed Parameter: Constant_Value_hd
                                        * Referenced by: '<S147>/Constant'
                                        */
  real32_T Gain_Gain_g;                /* Computed Parameter: Gain_Gain_g
                                        * Referenced by: '<S139>/Gain'
                                        */
  real32_T Gain1_Gain_ig;              /* Computed Parameter: Gain1_Gain_ig
                                        * Referenced by: '<S139>/Gain1'
                                        */
  real32_T Gain2_Gain_m;               /* Computed Parameter: Gain2_Gain_m
                                        * Referenced by: '<S139>/Gain2'
                                        */
  real32_T Gain3_Gain_ea;              /* Computed Parameter: Gain3_Gain_ea
                                        * Referenced by: '<S139>/Gain3'
                                        */
  real32_T Constant_Value_h1;          /* Computed Parameter: Constant_Value_h1
                                        * Referenced by: '<S129>/Constant'
                                        */
  real32_T Constant_Value_aee;         /* Computed Parameter: Constant_Value_aee
                                        * Referenced by: '<S130>/Constant'
                                        */
  real32_T Constant_Value_hp;          /* Computed Parameter: Constant_Value_hp
                                        * Referenced by: '<S131>/Constant'
                                        */
  real32_T quat_0_Y0[4];               /* Computed Parameter: quat_0_Y0
                                        * Referenced by: '<S112>/quat_0'
                                        */
  real32_T Gain_Gain_d;                /* Computed Parameter: Gain_Gain_d
                                        * Referenced by: '<S112>/Gain'
                                        */
  real32_T Switch_Threshold_a;         /* Computed Parameter: Switch_Threshold_a
                                        * Referenced by: '<S129>/Switch'
                                        */
  real32_T Switch_Threshold_f;         /* Computed Parameter: Switch_Threshold_f
                                        * Referenced by: '<S130>/Switch'
                                        */
  real32_T Switch_Threshold_mm;       /* Computed Parameter: Switch_Threshold_mm
                                       * Referenced by: '<S131>/Switch'
                                       */
  real32_T Merge_InitialOutput;       /* Computed Parameter: Merge_InitialOutput
                                       * Referenced by: '<S128>/Merge'
                                       */
  real32_T DiscreteTimeIntegrator5_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainval
                           * Referenced by: '<S164>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_fr;               /* Computed Parameter: Gain_Gain_fr
                                        * Referenced by: '<S164>/Gain'
                                        */
  real32_T DiscreteTimeIntegrator5_gainv_n;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainv_n
                           * Referenced by: '<S162>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_je;               /* Computed Parameter: Gain_Gain_je
                                        * Referenced by: '<S162>/Gain'
                                        */
  real32_T Saturation2_UpperSat_i; /* Computed Parameter: Saturation2_UpperSat_i
                                    * Referenced by: '<S113>/Saturation2'
                                    */
  real32_T Saturation2_LowerSat_g; /* Computed Parameter: Saturation2_LowerSat_g
                                    * Referenced by: '<S113>/Saturation2'
                                    */
  real32_T DiscreteTimeIntegrator5_gainv_m;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainv_m
                           * Referenced by: '<S163>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_h;                /* Computed Parameter: Gain_Gain_h
                                        * Referenced by: '<S163>/Gain'
                                        */
  real32_T Relay_OnVal_g;              /* Computed Parameter: Relay_OnVal_g
                                        * Referenced by: '<S113>/Relay'
                                        */
  real32_T Relay_OffVal_f;             /* Computed Parameter: Relay_OffVal_f
                                        * Referenced by: '<S113>/Relay'
                                        */
  real32_T Relay_YOn_k;                /* Computed Parameter: Relay_YOn_k
                                        * Referenced by: '<S113>/Relay'
                                        */
  real32_T Relay_YOff_f;               /* Computed Parameter: Relay_YOff_f
                                        * Referenced by: '<S113>/Relay'
                                        */
  real32_T X_Next_Y0;                  /* Computed Parameter: X_Next_Y0
                                        * Referenced by: '<S183>/X_Next'
                                        */
  real32_T Memory_InitialCondition[2];
                                  /* Computed Parameter: Memory_InitialCondition
                                   * Referenced by: '<S190>/Memory'
                                   */
  real32_T Memory_InitialCondition_o;
                                /* Computed Parameter: Memory_InitialCondition_o
                                 * Referenced by: '<S185>/Memory'
                                 */
  real32_T Gain3_Gain_o;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S185>/Gain3'
                                        */
  real32_T Constant_Value_o[2];        /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S196>/Constant'
                                        */
  real32_T X_Next_Y0_k;                /* Computed Parameter: X_Next_Y0_k
                                        * Referenced by: '<S193>/X_Next'
                                        */
  real32_T Memory_InitialCondition_i;
                                /* Computed Parameter: Memory_InitialCondition_i
                                 * Referenced by: '<S195>/Memory'
                                 */
  real32_T Gain3_Gain_p;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S195>/Gain3'
                                        */
  real32_T X_0_Y0;                     /* Computed Parameter: X_0_Y0
                                        * Referenced by: '<S204>/X_0'
                                        */
  real32_T Constant_Value_b[2];        /* Computed Parameter: Constant_Value_b
                                        * Referenced by: '<S201>/Constant'
                                        */
  real32_T Saturation_UpperSat_b;   /* Computed Parameter: Saturation_UpperSat_b
                                     * Referenced by: '<S215>/Saturation'
                                     */
  real32_T Saturation_LowerSat_c;   /* Computed Parameter: Saturation_LowerSat_c
                                     * Referenced by: '<S215>/Saturation'
                                     */
  real32_T X_Next_Y0_m;                /* Computed Parameter: X_Next_Y0_m
                                        * Referenced by: '<S212>/X_Next'
                                        */
  real32_T Delay_InitialCondition_j;
                                 /* Computed Parameter: Delay_InitialCondition_j
                                  * Referenced by: '<S214>/Delay'
                                  */
  real32_T Delay_InitialCondition_mk;
                                /* Computed Parameter: Delay_InitialCondition_mk
                                 * Referenced by: '<S218>/Delay'
                                 */
  real32_T Gain_Gain_pl;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S214>/Gain'
                                        */
  real32_T Saturation_UpperSat_as; /* Computed Parameter: Saturation_UpperSat_as
                                    * Referenced by: '<S212>/Saturation'
                                    */
  real32_T Saturation_LowerSat_e;   /* Computed Parameter: Saturation_LowerSat_e
                                     * Referenced by: '<S212>/Saturation'
                                     */
  real32_T X_Next_Y0_i;                /* Computed Parameter: X_Next_Y0_i
                                        * Referenced by: '<S221>/X_Next'
                                        */
  real32_T Memory_InitialCondition_p;
                                /* Computed Parameter: Memory_InitialCondition_p
                                 * Referenced by: '<S227>/Memory'
                                 */
  real32_T Memory_InitialCondition_c;
                                /* Computed Parameter: Memory_InitialCondition_c
                                 * Referenced by: '<S223>/Memory'
                                 */
  real32_T Gain3_Gain_k;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S223>/Gain3'
                                        */
  real32_T Saturation_UpperSat_i;   /* Computed Parameter: Saturation_UpperSat_i
                                     * Referenced by: '<S233>/Saturation'
                                     */
  real32_T Saturation_LowerSat_h;   /* Computed Parameter: Saturation_LowerSat_h
                                     * Referenced by: '<S233>/Saturation'
                                     */
  real32_T X_Next_Y0_mm;               /* Computed Parameter: X_Next_Y0_mm
                                        * Referenced by: '<S230>/X_Next'
                                        */
  real32_T rf_bias_Y0;                 /* Computed Parameter: rf_bias_Y0
                                        * Referenced by: '<S230>/rf_bias'
                                        */
  real32_T Delay_InitialCondition_mg;
                                /* Computed Parameter: Delay_InitialCondition_mg
                                 * Referenced by: '<S239>/Delay'
                                 */
  real32_T udT_Gain;                   /* Computed Parameter: udT_Gain
                                        * Referenced by: '<S239>/1//dT'
                                        */
  real32_T Memory_InitialCondition_o5;
                               /* Computed Parameter: Memory_InitialCondition_o5
                                * Referenced by: '<S236>/Memory'
                                */
  real32_T Memory_InitialCondition_h;
                                /* Computed Parameter: Memory_InitialCondition_h
                                 * Referenced by: '<S232>/Memory'
                                 */
  real32_T Gain3_Gain_j;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S232>/Gain3'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S243>/Constant'
                                        */
  real32_T Merge_InitialOutput_g;   /* Computed Parameter: Merge_InitialOutput_g
                                     * Referenced by: '<S244>/Merge'
                                     */
  real32_T Merge_InitialOutput_d;   /* Computed Parameter: Merge_InitialOutput_d
                                     * Referenced by: '<S245>/Merge'
                                     */
  real32_T Delay_InitialCondition_mt;
                                /* Computed Parameter: Delay_InitialCondition_mt
                                 * Referenced by: '<S241>/Delay'
                                 */
  real32_T Gain1_Gain_k;               /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S242>/Gain1'
                                        */
  real32_T Constant_Value_nn;          /* Computed Parameter: Constant_Value_nn
                                        * Referenced by: '<S242>/Constant'
                                        */
  real32_T Gain_Gain_m;                /* Expression: INS_CONST.dt
                                        * Referenced by: '<S242>/Gain'
                                        */
  real32_T Merge_InitialOutput_c;   /* Computed Parameter: Merge_InitialOutput_c
                                     * Referenced by: '<S203>/Merge'
                                     */
  real32_T Delay_InitialCondition_g;
                                 /* Computed Parameter: Delay_InitialCondition_g
                                  * Referenced by: '<S199>/Delay'
                                  */
  real32_T Constant_Value_l[2];        /* Computed Parameter: Constant_Value_l
                                        * Referenced by: '<S200>/Constant'
                                        */
  real32_T Gain_Gain_ic;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S200>/Gain'
                                        */
  real32_T Relay_OnVal_l;              /* Computed Parameter: Relay_OnVal_l
                                        * Referenced by: '<S273>/Relay'
                                        */
  real32_T Relay_OffVal_p;             /* Computed Parameter: Relay_OffVal_p
                                        * Referenced by: '<S273>/Relay'
                                        */
  real32_T Relay_YOn_b;                /* Computed Parameter: Relay_YOn_b
                                        * Referenced by: '<S273>/Relay'
                                        */
  real32_T Relay_YOff_d;               /* Computed Parameter: Relay_YOff_d
                                        * Referenced by: '<S273>/Relay'
                                        */
  real32_T Relay1_OnVal_b;             /* Computed Parameter: Relay1_OnVal_b
                                        * Referenced by: '<S273>/Relay1'
                                        */
  real32_T Relay1_OffVal_n;            /* Computed Parameter: Relay1_OffVal_n
                                        * Referenced by: '<S273>/Relay1'
                                        */
  real32_T Relay1_YOn_b;               /* Computed Parameter: Relay1_YOn_b
                                        * Referenced by: '<S273>/Relay1'
                                        */
  real32_T Relay1_YOff_a;              /* Computed Parameter: Relay1_YOff_a
                                        * Referenced by: '<S273>/Relay1'
                                        */
  real32_T Constant_Value_oi;          /* Computed Parameter: Constant_Value_oi
                                        * Referenced by: '<S271>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_b;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_b
                           * Referenced by: '<S271>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_c;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_c
                               * Referenced by: '<S271>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator1_gainv_d;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_d
                           * Referenced by: '<S271>/Discrete-Time Integrator1'
                           */
  real32_T Gain_Gain_b;                /* Computed Parameter: Gain_Gain_b
                                        * Referenced by: '<S271>/Gain'
                                        */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S271>/Gain1'
                                        */
  real32_T Constant_Value_gd;          /* Computed Parameter: Constant_Value_gd
                                        * Referenced by: '<S269>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainv_bt;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_bt
                           * Referenced by: '<S286>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_g;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_g
                               * Referenced by: '<S286>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_p;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_p
                           * Referenced by: '<S286>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_p;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_p
                           * Referenced by: '<S286>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainv_jo;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_jo
                           * Referenced by: '<S298>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_lb;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_lb
                              * Referenced by: '<S298>/Discrete-Time Integrator'
                              */
  real32_T DiscreteTimeIntegrator_UpperS_j;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_j
                           * Referenced by: '<S298>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_Lower_f2;
                          /* Computed Parameter: DiscreteTimeIntegrator_Lower_f2
                           * Referenced by: '<S298>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainv_iy;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_iy
                           * Referenced by: '<S285>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_b;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_b
                               * Referenced by: '<S285>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_Upper_jm;
                          /* Computed Parameter: DiscreteTimeIntegrator_Upper_jm
                           * Referenced by: '<S285>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_d;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_d
                           * Referenced by: '<S285>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainva_a;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_a
                           * Referenced by: '<S297>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_h;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_h
                               * Referenced by: '<S297>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_Upper_fv;
                          /* Computed Parameter: DiscreteTimeIntegrator_Upper_fv
                           * Referenced by: '<S297>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_b;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_b
                           * Referenced by: '<S297>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainv_jp;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_jp
                           * Referenced by: '<S299>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_ms;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_ms
                              * Referenced by: '<S299>/Discrete-Time Integrator'
                              */
  real32_T DiscreteTimeIntegrator_UpperS_e;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_e
                           * Referenced by: '<S299>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_Lower_no;
                          /* Computed Parameter: DiscreteTimeIntegrator_Lower_no
                           * Referenced by: '<S299>/Discrete-Time Integrator'
                           */
  real32_T Delay_4_InitialCondition;
                                 /* Computed Parameter: Delay_4_InitialCondition
                                  * Referenced by: '<S56>/Delay'
                                  */
  real32_T Delay_5_InitialCondition;
                                 /* Computed Parameter: Delay_5_InitialCondition
                                  * Referenced by: '<S56>/Delay'
                                  */
  real32_T Delay_6_InitialCondition;
                                 /* Computed Parameter: Delay_6_InitialCondition
                                  * Referenced by: '<S56>/Delay'
                                  */
  real32_T AirDensity_15C_Value;     /* Computed Parameter: AirDensity_15C_Value
                                      * Referenced by: '<S330>/AirDensity_15C'
                                      */
  real32_T Gain_Gain_ozb;              /* Computed Parameter: Gain_Gain_ozb
                                        * Referenced by: '<S330>/Gain'
                                        */
  real32_T Saturation1_UpperSat_i; /* Computed Parameter: Saturation1_UpperSat_i
                                    * Referenced by: '<S323>/Saturation1'
                                    */
  real32_T Saturation1_LowerSat_n; /* Computed Parameter: Saturation1_LowerSat_n
                                    * Referenced by: '<S323>/Saturation1'
                                    */
  real32_T h_R_m_Y0;                   /* Computed Parameter: h_R_m_Y0
                                        * Referenced by: '<S334>/h_R_m'
                                        */
  real32_T Delay_InitialCondition_p;
                                 /* Computed Parameter: Delay_InitialCondition_p
                                  * Referenced by: '<S334>/Delay'
                                  */
  real32_T Gain1_Gain_a;               /* Computed Parameter: Gain1_Gain_a
                                        * Referenced by: '<S331>/Gain1'
                                        */
  real32_T p1_Value;                   /* Computed Parameter: p1_Value
                                        * Referenced by: '<S331>/p1'
                                        */
  real32_T aR_g_Value;                 /* Computed Parameter: aR_g_Value
                                        * Referenced by: '<S331>/aR_g'
                                        */
  real32_T T1_Value;                   /* Computed Parameter: T1_Value
                                        * Referenced by: '<S331>/T1'
                                        */
  real32_T a_Value;                    /* Computed Parameter: a_Value
                                        * Referenced by: '<S331>/a'
                                        */
  real32_T Constant_Value_n5;          /* Computed Parameter: Constant_Value_n5
                                        * Referenced by: '<S361>/Constant'
                                        */
  real32_T Saturation1_UpperSat_m; /* Computed Parameter: Saturation1_UpperSat_m
                                    * Referenced by: '<S352>/Saturation1'
                                    */
  real32_T Saturation1_LowerSat_d; /* Computed Parameter: Saturation1_LowerSat_d
                                    * Referenced by: '<S352>/Saturation1'
                                    */
  real32_T DiscreteTimeIntegrator1_gainv_b;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_b
                           * Referenced by: '<S361>/Discrete-Time Integrator1'
                           */
  real32_T Constant_Value_k;           /* Computed Parameter: Constant_Value_k
                                        * Referenced by: '<S362>/Constant'
                                        */
  real32_T Saturation_UpperSat_l;   /* Computed Parameter: Saturation_UpperSat_l
                                     * Referenced by: '<S353>/Saturation'
                                     */
  real32_T Saturation_LowerSat_ku; /* Computed Parameter: Saturation_LowerSat_ku
                                    * Referenced by: '<S353>/Saturation'
                                    */
  real32_T DiscreteTimeIntegrator1_gainv_e;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_e
                           * Referenced by: '<S362>/Discrete-Time Integrator1'
                           */
  real32_T DiscreteTimeIntegrator_gainva_g;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_g
                           * Referenced by: '<S361>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_d;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_d
                               * Referenced by: '<S361>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_j2;               /* Computed Parameter: Gain_Gain_j2
                                        * Referenced by: '<S361>/Gain'
                                        */
  real32_T Gain1_Gain_kf;              /* Computed Parameter: Gain1_Gain_kf
                                        * Referenced by: '<S361>/Gain1'
                                        */
  real32_T DiscreteTimeIntegrator_gainv_mf;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_mf
                           * Referenced by: '<S362>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_f;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_f
                               * Referenced by: '<S362>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_gh;               /* Computed Parameter: Gain_Gain_gh
                                        * Referenced by: '<S362>/Gain'
                                        */
  real32_T Gain1_Gain_cj;              /* Computed Parameter: Gain1_Gain_cj
                                        * Referenced by: '<S362>/Gain1'
                                        */
  real32_T default_mag_quality_Value;
                                /* Computed Parameter: default_mag_quality_Value
                                 * Referenced by: '<S375>/default_mag_quality'
                                 */
  real32_T Constant1_Value_l1;         /* Computed Parameter: Constant1_Value_l1
                                        * Referenced by: '<S386>/Constant1'
                                        */
  real32_T Constant_Value_a1;          /* Computed Parameter: Constant_Value_a1
                                        * Referenced by: '<S384>/Constant'
                                        */
  real32_T Constant1_Value_i;          /* Computed Parameter: Constant1_Value_i
                                        * Referenced by: '<S384>/Constant1'
                                        */
  real32_T Constant2_Value_mb;         /* Computed Parameter: Constant2_Value_mb
                                        * Referenced by: '<S384>/Constant2'
                                        */
  real32_T Constant4_Value_c;          /* Computed Parameter: Constant4_Value_c
                                        * Referenced by: '<S384>/Constant4'
                                        */
  real32_T Gain_Gain_gg;               /* Computed Parameter: Gain_Gain_gg
                                        * Referenced by: '<S376>/Gain'
                                        */
  real32_T Gain_Gain_bo;               /* Computed Parameter: Gain_Gain_bo
                                        * Referenced by: '<S384>/Gain'
                                        */
  real32_T Constant3_Value_f;          /* Computed Parameter: Constant3_Value_f
                                        * Referenced by: '<S384>/Constant3'
                                        */
  real32_T Constant_Value_hy;          /* Computed Parameter: Constant_Value_hy
                                        * Referenced by: '<S385>/Constant'
                                        */
  real32_T Switch_Threshold_b;         /* Computed Parameter: Switch_Threshold_b
                                        * Referenced by: '<S385>/Switch'
                                        */
  real32_T Gauss_to_uT_Gain;           /* Computed Parameter: Gauss_to_uT_Gain
                                        * Referenced by: '<S327>/Gauss_to_uT'
                                        */
  real32_T Gain1_Gain_o;               /* Computed Parameter: Gain1_Gain_o
                                        * Referenced by: '<S379>/Gain1'
                                        */
  real32_T Constant2_Value_h;          /* Computed Parameter: Constant2_Value_h
                                        * Referenced by: '<S379>/Constant2'
                                        */
  real32_T gain_Gain_g;                /* Computed Parameter: gain_Gain_g
                                        * Referenced by: '<S379>/gain'
                                        */
  real32_T Saturation_UpperSat_g;   /* Computed Parameter: Saturation_UpperSat_g
                                     * Referenced by: '<S379>/Saturation'
                                     */
  real32_T Saturation_LowerSat_a;   /* Computed Parameter: Saturation_LowerSat_a
                                     * Referenced by: '<S379>/Saturation'
                                     */
  real32_T Nominal_Magnitude_Value;
                                  /* Computed Parameter: Nominal_Magnitude_Value
                                   * Referenced by: '<S380>/Nominal_Magnitude'
                                   */
  real32_T Constant1_Value_c;          /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<S380>/Constant1'
                                        */
  real32_T gain_Gain_m;                /* Computed Parameter: gain_Gain_m
                                        * Referenced by: '<S380>/gain'
                                        */
  real32_T Saturation_UpperSat_gv; /* Computed Parameter: Saturation_UpperSat_gv
                                    * Referenced by: '<S380>/Saturation'
                                    */
  real32_T Saturation_LowerSat_p;   /* Computed Parameter: Saturation_LowerSat_p
                                     * Referenced by: '<S380>/Saturation'
                                     */
  real32_T Constant_Value_fn;          /* Computed Parameter: Constant_Value_fn
                                        * Referenced by: '<S381>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainv_bm;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_bm
                           * Referenced by: '<S381>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_mb;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_mb
                              * Referenced by: '<S381>/Discrete-Time Integrator'
                              */
  real32_T DiscreteTimeIntegrator1_gainv_m;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_m
                           * Referenced by: '<S381>/Discrete-Time Integrator1'
                           */
  real32_T Gain_Gain_c;                /* Computed Parameter: Gain_Gain_c
                                        * Referenced by: '<S381>/Gain'
                                        */
  real32_T Gain1_Gain_bn;              /* Computed Parameter: Gain1_Gain_bn
                                        * Referenced by: '<S381>/Gain1'
                                        */
  real32_T DiscreteTimeIntegrator5_gainv_c;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainv_c
                           * Referenced by: '<S393>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_ca;               /* Computed Parameter: Gain_Gain_ca
                                        * Referenced by: '<S393>/Gain'
                                        */
  real32_T Delay_2_InitialCondition;
                                 /* Computed Parameter: Delay_2_InitialCondition
                                  * Referenced by: '<Root>/Delay'
                                  */
  real32_T Delay_3_InitialCondition;
                                 /* Computed Parameter: Delay_3_InitialCondition
                                  * Referenced by: '<Root>/Delay'
                                  */
  real32_T Delay_8_InitialCondition_m;
                               /* Computed Parameter: Delay_8_InitialCondition_m
                                * Referenced by: '<Root>/Delay'
                                */
  uint32_T Gain1_Gain_ap;              /* Computed Parameter: Gain1_Gain_ap
                                        * Referenced by: '<S10>/Gain1'
                                        */
  uint32_T Gain9_Gain;                 /* Computed Parameter: Gain9_Gain
                                        * Referenced by: '<S8>/Gain9'
                                        */
  uint32_T Gain1_Gain_po;              /* Computed Parameter: Gain1_Gain_po
                                        * Referenced by: '<S352>/Gain1'
                                        */
  uint32_T Gain5_Gain;                 /* Computed Parameter: Gain5_Gain
                                        * Referenced by: '<S353>/Gain5'
                                        */
  uint32_T Output_InitialCondition;
                                  /* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S4>/Output'
                                   */
  uint32_T Constant_Value_pt;          /* Computed Parameter: Constant_Value_pt
                                        * Referenced by: '<S8>/Constant'
                                        */
  uint32_T Constant_Value_lm;          /* Computed Parameter: Constant_Value_lm
                                        * Referenced by: '<S10>/Constant'
                                        */
  uint32_T Constant_Value_m;           /* Computed Parameter: Constant_Value_m
                                        * Referenced by: '<S124>/Constant'
                                        */
  uint32_T Delay_InitialCondition_n;
                                 /* Computed Parameter: Delay_InitialCondition_n
                                  * Referenced by: '<S121>/Delay'
                                  */
  uint32_T Saturation_UpperSat_k5; /* Computed Parameter: Saturation_UpperSat_k5
                                    * Referenced by: '<S121>/Saturation'
                                    */
  uint32_T Saturation_LowerSat_hb; /* Computed Parameter: Saturation_LowerSat_hb
                                    * Referenced by: '<S121>/Saturation'
                                    */
  uint32_T Delay_InitialCondition_i;
                                 /* Computed Parameter: Delay_InitialCondition_i
                                  * Referenced by: '<S118>/Delay'
                                  */
  uint32_T Saturation_UpperSat_p;   /* Computed Parameter: Saturation_UpperSat_p
                                     * Referenced by: '<S118>/Saturation'
                                     */
  uint32_T Saturation_LowerSat_mo; /* Computed Parameter: Saturation_LowerSat_mo
                                    * Referenced by: '<S118>/Saturation'
                                    */
  uint32_T Constant1_Value_f;          /* Computed Parameter: Constant1_Value_f
                                        * Referenced by: '<S334>/Constant1'
                                        */
  uint32_T Delay1_InitialCondition_k;
                                /* Computed Parameter: Delay1_InitialCondition_k
                                 * Referenced by: '<S334>/Delay1'
                                 */
  uint32_T Saturation1_UpperSat_n; /* Computed Parameter: Saturation1_UpperSat_n
                                    * Referenced by: '<S334>/Saturation1'
                                    */
  uint32_T Saturation1_LowerSat_m; /* Computed Parameter: Saturation1_LowerSat_m
                                    * Referenced by: '<S334>/Saturation1'
                                    */
  uint32_T DiscreteTimeIntegrator_IC_iu;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_iu
                              * Referenced by: '<S333>/Discrete-Time Integrator'
                              */
  uint32_T Delay_InitialCondition_nt;
                                /* Computed Parameter: Delay_InitialCondition_nt
                                 * Referenced by: '<S335>/Delay'
                                 */
  uint32_T Saturation_UpperSat_f;   /* Computed Parameter: Saturation_UpperSat_f
                                     * Referenced by: '<S335>/Saturation'
                                     */
  uint32_T Saturation_LowerSat_pw; /* Computed Parameter: Saturation_LowerSat_pw
                                    * Referenced by: '<S335>/Saturation'
                                    */
  uint32_T DiscreteTimeIntegrator_IC_p;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_p
                               * Referenced by: '<S351>/Discrete-Time Integrator'
                               */
  uint32_T DiscreteTimeIntegrator_IC_ba;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_ba
                              * Referenced by: '<S366>/Discrete-Time Integrator'
                              */
  uint32_T DiscreteTimeIntegrator_IC_k;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_k
                               * Referenced by: '<S374>/Discrete-Time Integrator'
                               */
  uint32_T DiscreteTimeIntegrator_IC_n;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_n
                               * Referenced by: '<S392>/Discrete-Time Integrator'
                               */
  uint32_T DiscreteTimeIntegrator_IC_f4;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_f4
                              * Referenced by: '<S399>/Discrete-Time Integrator'
                              */
  uint32_T DiscreteTimeIntegrator_IC_n1;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_n1
                              * Referenced by: '<S400>/Discrete-Time Integrator'
                              */
  uint32_T DiscreteTimeIntegrator_UpperS_l;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_l
                           * Referenced by: '<S400>/Discrete-Time Integrator'
                           */
  uint32_T DiscreteTimeIntegrator_Lower_bq;
                          /* Computed Parameter: DiscreteTimeIntegrator_Lower_bq
                           * Referenced by: '<S400>/Discrete-Time Integrator'
                           */
  uint16_T Gain1_Gain_kq;              /* Computed Parameter: Gain1_Gain_kq
                                        * Referenced by: '<S8>/Gain1'
                                        */
  uint16_T Gain13_Gain;                /* Computed Parameter: Gain13_Gain
                                        * Referenced by: '<S8>/Gain13'
                                        */
  uint16_T Gain12_Gain;                /* Computed Parameter: Gain12_Gain
                                        * Referenced by: '<S8>/Gain12'
                                        */
  uint16_T Gain11_Gain;                /* Computed Parameter: Gain11_Gain
                                        * Referenced by: '<S8>/Gain11'
                                        */
  uint16_T Gain5_Gain_e;               /* Computed Parameter: Gain5_Gain_e
                                        * Referenced by: '<S8>/Gain5'
                                        */
  uint16_T Gain4_Gain_a;               /* Computed Parameter: Gain4_Gain_a
                                        * Referenced by: '<S8>/Gain4'
                                        */
  uint16_T Gain2_Gain_o5;              /* Computed Parameter: Gain2_Gain_o5
                                        * Referenced by: '<S8>/Gain2'
                                        */
  uint16_T GPS_Delay_Value;            /* Computed Parameter: GPS_Delay_Value
                                        * Referenced by: '<S86>/GPS_Delay'
                                        */
  uint16_T Constant_Value_gn;          /* Computed Parameter: Constant_Value_gn
                                        * Referenced by: '<S281>/Constant'
                                        */
  uint16_T Constant_Value_bt;          /* Computed Parameter: Constant_Value_bt
                                        * Referenced by: '<S282>/Constant'
                                        */
  uint16_T Constant_Value_m3;          /* Computed Parameter: Constant_Value_m3
                                        * Referenced by: '<S320>/Constant'
                                        */
  uint16_T Constant_Value_pti;         /* Computed Parameter: Constant_Value_pti
                                        * Referenced by: '<S322>/Constant'
                                        */
  boolean_T Constant_Value_mt;         /* Computed Parameter: Constant_Value_mt
                                        * Referenced by: '<S22>/Constant'
                                        */
  boolean_T Constant_Value_m2;         /* Computed Parameter: Constant_Value_m2
                                        * Referenced by: '<S27>/Constant'
                                        */
  boolean_T Constant_Value_o2;         /* Computed Parameter: Constant_Value_o2
                                        * Referenced by: '<S32>/Constant'
                                        */
  boolean_T Constant_Value_hk;         /* Computed Parameter: Constant_Value_hk
                                        * Referenced by: '<S37>/Constant'
                                        */
  boolean_T Constant_Value_l1;         /* Computed Parameter: Constant_Value_l1
                                        * Referenced by: '<S42>/Constant'
                                        */
  boolean_T Constant_Value_m2n;        /* Computed Parameter: Constant_Value_m2n
                                        * Referenced by: '<S47>/Constant'
                                        */
  boolean_T Constant_Value_ao;         /* Computed Parameter: Constant_Value_ao
                                        * Referenced by: '<S52>/Constant'
                                        */
  boolean_T Delay_InitialCondition_go;
                                /* Computed Parameter: Delay_InitialCondition_go
                                 * Referenced by: '<S12>/Delay'
                                 */
  boolean_T Delay_InitialCondition_mz;
                                /* Computed Parameter: Delay_InitialCondition_mz
                                 * Referenced by: '<S15>/Delay'
                                 */
  boolean_T Relay1_YOn_i;              /* Computed Parameter: Relay1_YOn_i
                                        * Referenced by: '<S9>/Relay1'
                                        */
  boolean_T Relay1_YOff_k;             /* Computed Parameter: Relay1_YOff_k
                                        * Referenced by: '<S9>/Relay1'
                                        */
  boolean_T Delay_InitialCondition_a;
                                 /* Computed Parameter: Delay_InitialCondition_a
                                  * Referenced by: '<S17>/Delay'
                                  */
  boolean_T Delay_InitialCondition_c;
                                 /* Computed Parameter: Delay_InitialCondition_c
                                  * Referenced by: '<S11>/Delay'
                                  */
  boolean_T Delay_InitialCondition_cj;
                                /* Computed Parameter: Delay_InitialCondition_cj
                                 * Referenced by: '<S13>/Delay'
                                 */
  boolean_T Delay_InitialCondition_ae;
                                /* Computed Parameter: Delay_InitialCondition_ae
                                 * Referenced by: '<S14>/Delay'
                                 */
  boolean_T Delay_InitialCondition_e;
                                 /* Computed Parameter: Delay_InitialCondition_e
                                  * Referenced by: '<S16>/Delay'
                                  */
  boolean_T Constant_Value_af;         /* Computed Parameter: Constant_Value_af
                                        * Referenced by: '<S122>/Constant'
                                        */
  boolean_T Constant_Value_ps;         /* Computed Parameter: Constant_Value_ps
                                        * Referenced by: '<S261>/Constant'
                                        */
  boolean_T Constant_Value_pf;         /* Computed Parameter: Constant_Value_pf
                                        * Referenced by: '<S262>/Constant'
                                        */
  boolean_T Constant_Value_ha;         /* Computed Parameter: Constant_Value_ha
                                        * Referenced by: '<S263>/Constant'
                                        */
  boolean_T Constant_Value_nm;         /* Computed Parameter: Constant_Value_nm
                                        * Referenced by: '<S291>/Constant'
                                        */
  boolean_T Constant_Value_d;          /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S296>/Constant'
                                        */
  boolean_T Constant_Value_ej;         /* Computed Parameter: Constant_Value_ej
                                        * Referenced by: '<S304>/Constant'
                                        */
  boolean_T Constant_Value_jo;         /* Computed Parameter: Constant_Value_jo
                                        * Referenced by: '<S309>/Constant'
                                        */
  boolean_T Constant_Value_i;          /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S314>/Constant'
                                        */
  boolean_T Delay_InitialCondition_in;
                                /* Computed Parameter: Delay_InitialCondition_in
                                 * Referenced by: '<S286>/Delay'
                                 */
  boolean_T Delay_InitialCondition_ns;
                                /* Computed Parameter: Delay_InitialCondition_ns
                                 * Referenced by: '<S298>/Delay'
                                 */
  boolean_T Delay_InitialCondition_k;
                                 /* Computed Parameter: Delay_InitialCondition_k
                                  * Referenced by: '<S285>/Delay'
                                  */
  boolean_T Delay_InitialCondition_d;
                                 /* Computed Parameter: Delay_InitialCondition_d
                                  * Referenced by: '<S297>/Delay'
                                  */
  boolean_T Delay_InitialCondition_ia;
                                /* Computed Parameter: Delay_InitialCondition_ia
                                 * Referenced by: '<S299>/Delay'
                                 */
  boolean_T Delay_InitialCondition_f;
                                 /* Computed Parameter: Delay_InitialCondition_f
                                  * Referenced by: '<S396>/Delay'
                                  */
  boolean_T Constant_Value_pa;         /* Computed Parameter: Constant_Value_pa
                                        * Referenced by: '<S407>/Constant'
                                        */
  int8_T Constant_Value_ej5;           /* Computed Parameter: Constant_Value_ej5
                                        * Referenced by: '<S259>/Constant'
                                        */
  int8_T Constant_Value_m2k;           /* Computed Parameter: Constant_Value_m2k
                                        * Referenced by: '<S260>/Constant'
                                        */
  int8_T Constant_Value_c1;            /* Computed Parameter: Constant_Value_c1
                                        * Referenced by: '<S264>/Constant'
                                        */
  int8_T Constant_Value_lc;            /* Computed Parameter: Constant_Value_lc
                                        * Referenced by: '<S265>/Constant'
                                        */
  int8_T Constant_Value_kt;            /* Computed Parameter: Constant_Value_kt
                                        * Referenced by: '<S266>/Constant'
                                        */
  int8_T Saturation_UpperSat_m;     /* Computed Parameter: Saturation_UpperSat_m
                                     * Referenced by: '<S257>/Saturation'
                                     */
  int8_T Saturation_LowerSat_h5;   /* Computed Parameter: Saturation_LowerSat_h5
                                    * Referenced by: '<S257>/Saturation'
                                    */
  int8_T Saturation_UpperSat_gx;   /* Computed Parameter: Saturation_UpperSat_gx
                                    * Referenced by: '<S258>/Saturation'
                                    */
  int8_T Saturation_LowerSat_co;   /* Computed Parameter: Saturation_LowerSat_co
                                    * Referenced by: '<S258>/Saturation'
                                    */
  int8_T Saturation1_UpperSat_ig; /* Computed Parameter: Saturation1_UpperSat_ig
                                   * Referenced by: '<S258>/Saturation1'
                                   */
  int8_T Saturation1_LowerSat_g;   /* Computed Parameter: Saturation1_LowerSat_g
                                    * Referenced by: '<S258>/Saturation1'
                                    */
  uint8_T Gain6_Gain;                  /* Computed Parameter: Gain6_Gain
                                        * Referenced by: '<S10>/Gain6'
                                        */
  uint8_T Gain5_Gain_a;                /* Computed Parameter: Gain5_Gain_a
                                        * Referenced by: '<S10>/Gain5'
                                        */
  uint8_T Gain4_Gain_p;                /* Computed Parameter: Gain4_Gain_p
                                        * Referenced by: '<S10>/Gain4'
                                        */
  uint8_T Gain3_Gain_f;                /* Computed Parameter: Gain3_Gain_f
                                        * Referenced by: '<S10>/Gain3'
                                        */
  uint8_T Gain2_Gain_h;                /* Computed Parameter: Gain2_Gain_h
                                        * Referenced by: '<S10>/Gain2'
                                        */
  uint8_T Constant1_Value_b;           /* Computed Parameter: Constant1_Value_b
                                        * Referenced by: '<S341>/Constant1'
                                        */
  uint8_T Delay_InitialCondition_j0;
                                /* Computed Parameter: Delay_InitialCondition_j0
                                 * Referenced by: '<S341>/Delay'
                                 */
  uint8_T Constant1_Value_no;          /* Computed Parameter: Constant1_Value_no
                                        * Referenced by: '<S369>/Constant1'
                                        */
  uint8_T Delay_InitialCondition_ja;
                                /* Computed Parameter: Delay_InitialCondition_ja
                                 * Referenced by: '<S369>/Delay'
                                 */
  uint8_T Constant1_Value_ev;          /* Computed Parameter: Constant1_Value_ev
                                        * Referenced by: '<S389>/Constant1'
                                        */
  uint8_T Delay_InitialCondition_jy;
                                /* Computed Parameter: Delay_InitialCondition_jy
                                 * Referenced by: '<S389>/Delay'
                                 */
  uint8_T Constant1_Value_o0;          /* Computed Parameter: Constant1_Value_o0
                                        * Referenced by: '<S396>/Constant1'
                                        */
  uint8_T Relay_OnVal_f;               /* Computed Parameter: Relay_OnVal_f
                                        * Referenced by: '<S392>/Relay'
                                        */
  uint8_T Relay_OffVal_k;              /* Computed Parameter: Relay_OffVal_k
                                        * Referenced by: '<S392>/Relay'
                                        */
  uint8_T Constant1_Value_h;           /* Computed Parameter: Constant1_Value_h
                                        * Referenced by: '<S404>/Constant1'
                                        */
  uint8_T Delay_InitialCondition_ny;
                                /* Computed Parameter: Delay_InitialCondition_ny
                                 * Referenced by: '<S404>/Delay'
                                 */
  rtP_Baro_Velocity_INS_T Rf_Velocity; /* '<S245>/Rf_Velocity' */
  rtP_Baro_Velocity_INS_T Baro_Velocity;/* '<S245>/Baro_Velocity' */
};

/* Parameters (default storage) */
typedef struct Parameters_INS_T_ Parameters_INS_T;

/* Real-time Model Data Structure */
struct tag_RTM_INS_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern Parameters_INS_T INS_P;

/* Block signals (default storage) */
extern BlockIO_INS_T INS_B;

/* Block states (default storage) */
extern D_Work_INS_T INS_DWork;

/* Zero-crossing (trigger) state */
extern PrevZCSigStates_INS_T INS_PrevZCSigState;

/* External inputs (root inport signals with default storage) */
extern ExternalInputs_INS_T INS_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExternalOutputs_INS_T INS_Y;

/* External data declarations for dependent source files */
extern const INS_Out_Bus INS_rtZINS_Out_Bus;/* INS_Out_Bus ground */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern struct_tF4zDkO7m7jeFfXSvhWnpB INS_PARAM;/* Variable: INS_PARAM
                                                * Referenced by:
                                                *   '<S352>/Constant1'
                                                *   '<S352>/Gain2'
                                                *   '<S353>/Constant7'
                                                *   '<S353>/Gain3'
                                                *   '<S69>/Gain1'
                                                *   '<S71>/mag_correct_gain'
                                                *   '<S74>/Gain'
                                                *   '<S186>/Gain'
                                                *   '<S186>/Gain2'
                                                *   '<S186>/Gain3'
                                                *   '<S196>/Gain'
                                                *   '<S196>/Gain2'
                                                *   '<S215>/Gain'
                                                *   '<S215>/Gain1'
                                                *   '<S215>/Gain2'
                                                *   '<S224>/Gain'
                                                *   '<S224>/Gain1'
                                                *   '<S224>/Gain2'
                                                *   '<S233>/Gain'
                                                *   '<S233>/Gain1'
                                                *   '<S233>/Gain2'
                                                */
extern struct_TYt7YeNdxIDXfczXumtXXB INS_EXPORT;/* Variable: INS_EXPORT
                                                 * Referenced by:
                                                 *   '<S4>/Constant'
                                                 *   '<S333>/Constant'
                                                 *   '<S366>/Constant'
                                                 *   '<S374>/Constant'
                                                 *   '<S392>/Constant'
                                                 *   '<S399>/Constant'
                                                 *   '<S11>/Constant'
                                                 *   '<S12>/Constant'
                                                 *   '<S13>/Constant'
                                                 *   '<S14>/Constant'
                                                 *   '<S15>/Constant'
                                                 *   '<S16>/Constant'
                                                 *   '<S17>/Constant'
                                                 *   '<S351>/Constant'
                                                 *   '<S285>/Constant'
                                                 *   '<S286>/Constant'
                                                 *   '<S297>/Constant'
                                                 *   '<S298>/Constant'
                                                 *   '<S299>/Constant'
                                                 */

/* Model entry point functions */
extern void INS_init(void);
extern void INS_step(void);

/* Real-time Model object */
extern RT_MODEL_INS_T *const INS_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'INS'
 * '<S1>'   : 'INS/Bus_Constructor'
 * '<S2>'   : 'INS/Data_Fusion'
 * '<S3>'   : 'INS/Sensor_PreProcess'
 * '<S4>'   : 'INS/Bus_Constructor/Counter'
 * '<S5>'   : 'INS/Bus_Constructor/Rotation_Output'
 * '<S6>'   : 'INS/Bus_Constructor/Status_Output'
 * '<S7>'   : 'INS/Bus_Constructor/Translation_Output'
 * '<S8>'   : 'INS/Bus_Constructor/Status_Output/INS_Flag'
 * '<S9>'   : 'INS/Bus_Constructor/Status_Output/INS_Quality'
 * '<S10>'  : 'INS/Bus_Constructor/Status_Output/Sensor_Status'
 * '<S11>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1'
 * '<S12>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2'
 * '<S13>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3'
 * '<S14>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4'
 * '<S15>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5'
 * '<S16>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check6'
 * '<S17>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8'
 * '<S18>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Compare To Constant'
 * '<S19>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Compare To Constant1'
 * '<S20>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Compare To Constant2'
 * '<S21>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Detect Rise Positive'
 * '<S22>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Detect Rise Positive/Positive'
 * '<S23>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Compare To Constant'
 * '<S24>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Compare To Constant1'
 * '<S25>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Compare To Constant2'
 * '<S26>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Detect Rise Positive'
 * '<S27>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Detect Rise Positive/Positive'
 * '<S28>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Compare To Constant'
 * '<S29>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Compare To Constant1'
 * '<S30>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Compare To Constant2'
 * '<S31>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Detect Rise Positive'
 * '<S32>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Detect Rise Positive/Positive'
 * '<S33>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Compare To Constant'
 * '<S34>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Compare To Constant1'
 * '<S35>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Compare To Constant2'
 * '<S36>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Detect Rise Positive'
 * '<S37>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Detect Rise Positive/Positive'
 * '<S38>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Compare To Constant'
 * '<S39>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Compare To Constant1'
 * '<S40>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Compare To Constant2'
 * '<S41>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Detect Rise Positive'
 * '<S42>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Detect Rise Positive/Positive'
 * '<S43>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check6/Compare To Constant'
 * '<S44>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check6/Compare To Constant1'
 * '<S45>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check6/Compare To Constant2'
 * '<S46>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check6/Detect Rise Positive'
 * '<S47>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check6/Detect Rise Positive/Positive'
 * '<S48>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Compare To Constant'
 * '<S49>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Compare To Constant1'
 * '<S50>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Compare To Constant2'
 * '<S51>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Detect Rise Positive'
 * '<S52>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Detect Rise Positive/Positive'
 * '<S53>'  : 'INS/Bus_Constructor/Status_Output/Sensor_Status/Compare To Zero'
 * '<S54>'  : 'INS/Bus_Constructor/Status_Output/Sensor_Status/Compare To Zero1'
 * '<S55>'  : 'INS/Data_Fusion/Rotation_Filter'
 * '<S56>'  : 'INS/Data_Fusion/Translation_Filter'
 * '<S57>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS'
 * '<S58>'  : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess'
 * '<S59>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor'
 * '<S60>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct'
 * '<S61>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update'
 * '<S62>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle'
 * '<S63>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Psi To DCM'
 * '<S64>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle/Quaternion To Euler'
 * '<S65>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle/Quaternion To Euler/Quaternion Normalize'
 * '<S66>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle/Quaternion To Euler/Quaternion Normalize/Quaternion Modulus'
 * '<S67>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Psi To DCM/Rotation Matrix Z'
 * '<S68>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction'
 * '<S69>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction'
 * '<S70>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct'
 * '<S71>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Mag_Correct'
 * '<S72>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct'
 * '<S73>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator'
 * '<S74>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct'
 * '<S75>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct'
 * '<S76>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct/Cross Product'
 * '<S77>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct/Cross Product/Subsystem'
 * '<S78>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct/Cross Product/Subsystem1'
 * '<S79>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Cross Product'
 * '<S80>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Saturation'
 * '<S81>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Vector Normalize'
 * '<S82>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Vector Normalize1'
 * '<S83>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Cross Product/Subsystem'
 * '<S84>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Cross Product/Subsystem1'
 * '<S85>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Saturation/Vector Modulus'
 * '<S86>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Estimate_Acc'
 * '<S87>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc'
 * '<S88>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Estimate_Acc/Second Order LPF'
 * '<S89>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/Bus_Selection'
 * '<S90>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/Detect Increase'
 * '<S91>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/GPS_Meas_Acc'
 * '<S92>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/Valid_Check'
 * '<S93>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction/Compare To Constant'
 * '<S94>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction/Second Order LPF'
 * '<S95>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction/Vector Modulus'
 * '<S96>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update'
 * '<S97>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Gyro_Bias_Update'
 * '<S98>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply'
 * '<S99>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Normalize'
 * '<S100>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM'
 * '<S101>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_0'
 * '<S102>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_1'
 * '<S103>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_2'
 * '<S104>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_4'
 * '<S105>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Normalize/Quaternion Modulus'
 * '<S106>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/Quaternion Normalize'
 * '<S107>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/column_1'
 * '<S108>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/column_2'
 * '<S109>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/column_3'
 * '<S110>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/Quaternion Normalize/Quaternion Modulus'
 * '<S111>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset'
 * '<S112>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude'
 * '<S113>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill'
 * '<S114>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Compare To Constant'
 * '<S115>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Compare To Constant1'
 * '<S116>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Detect Rise Positive'
 * '<S117>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Interval Test'
 * '<S118>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Reset Heading'
 * '<S119>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Vector Modulus'
 * '<S120>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Vector Modulus1'
 * '<S121>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/sample_valid'
 * '<S122>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Detect Rise Positive/Positive'
 * '<S123>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Reset Heading/Detect Rise Positive1'
 * '<S124>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Reset Heading/Detect Rise Positive1/Positive'
 * '<S125>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/sample_valid/valid_samples'
 * '<S126>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product'
 * '<S127>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product1'
 * '<S128>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion'
 * '<S129>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Vector Normalize'
 * '<S130>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Vector Normalize1'
 * '<S131>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Vector Normalize2'
 * '<S132>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product/Subsystem'
 * '<S133>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product/Subsystem1'
 * '<S134>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product1/Subsystem'
 * '<S135>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product1/Subsystem1'
 * '<S136>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/DCM Trace'
 * '<S137>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace'
 * '<S138>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace'
 * '<S139>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)'
 * '<S140>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)'
 * '<S141>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)'
 * '<S142>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/diag(DCM)'
 * '<S143>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) -sin(theta)'
 * '<S144>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/cos(theta)sin(phi) - (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S145>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/cos(theta)sin(psi) + (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S146>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/if s~=0; s=0.5//s'
 * '<S147>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/u(1) -(u(5)+u(9)) +1'
 * '<S148>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) +sin(theta)'
 * '<S149>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/cos(theta)sin(phi) + (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S150>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/cos(theta)sin(psi) + (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S151>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/if s~=0; s=0.5//s'
 * '<S152>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/u(5) -(u(1)+u(9)) +1'
 * '<S153>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) -sin(theta)'
 * '<S154>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/cos(theta)sin(phi) + (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S155>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/cos(theta)sin(psi) - (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S156>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/if s~=0; s=0.5//s'
 * '<S157>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/u(9) -(u(1)+u(5)) +1'
 * '<S158>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) +sin(theta)'
 * '<S159>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace/cos(theta)sin(phi) - (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S160>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace/cos(theta)sin(psi) - (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S161>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order HPF'
 * '<S162>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order LPF'
 * '<S163>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order LPF1'
 * '<S164>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order HPF/First Order LPF'
 * '<S165>' : 'INS/Data_Fusion/Translation_Filter/CF'
 * '<S166>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess'
 * '<S167>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor'
 * '<S168>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter'
 * '<S169>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter'
 * '<S170>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select'
 * '<S171>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Bus_Select'
 * '<S172>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Height_Above_Ground'
 * '<S173>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Local_Position'
 * '<S174>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Velocity'
 * '<S175>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position'
 * '<S176>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position/WGS84_Position'
 * '<S177>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position/WGS84_Position/safe_divide'
 * '<S178>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position/WGS84_Position/safe_divide/Zero_Value_Exclusion'
 * '<S179>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct'
 * '<S180>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict'
 * '<S181>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct'
 * '<S182>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct'
 * '<S183>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct'
 * '<S184>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Detect Change'
 * '<S185>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Error_Integrate'
 * '<S186>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Error_Scaling'
 * '<S187>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Estimate_State'
 * '<S188>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement'
 * '<S189>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation'
 * '<S190>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation/Bias'
 * '<S191>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation/Bias/Bias_Update'
 * '<S192>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation/Bias/Detect Increase'
 * '<S193>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct/OptFlow_Correct'
 * '<S194>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct/OptFlow_Correct/Detect Change'
 * '<S195>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct/OptFlow_Correct/Error_Integrate'
 * '<S196>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct/OptFlow_Correct/Error_Scaling'
 * '<S197>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct/OptFlow_Correct/Estimate_State'
 * '<S198>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/OptFlow Correct/OptFlow_Correct/Measurement'
 * '<S199>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate'
 * '<S200>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Update'
 * '<S201>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init'
 * '<S202>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Pos_Init'
 * '<S203>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Vel_Init'
 * '<S204>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Pos_Init/GPS_Pos_Init'
 * '<S205>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Vel_Init/GPS_Vel_Init'
 * '<S206>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Vel_Init/OptFlow_Vel_Init'
 * '<S207>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct'
 * '<S208>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict'
 * '<S209>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct'
 * '<S210>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct'
 * '<S211>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct'
 * '<S212>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct'
 * '<S213>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Detect Change'
 * '<S214>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Error_Hold'
 * '<S215>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Error_Scaling'
 * '<S216>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Estimate_States'
 * '<S217>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Measurement'
 * '<S218>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Measurement/Bias_Estimation'
 * '<S219>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Measurement/Bias_Estimation/Bias'
 * '<S220>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Baro_Correct/Baro_Correct/Measurement/Bias_Estimation/Detect Increase'
 * '<S221>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct'
 * '<S222>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Detect Change'
 * '<S223>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Error_Hold'
 * '<S224>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Error_Scaling'
 * '<S225>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Estimate_State'
 * '<S226>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement'
 * '<S227>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement/Bias_Estimation'
 * '<S228>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement/Bias_Estimation/Bias'
 * '<S229>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement/Bias_Estimation/Detect Increase'
 * '<S230>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct'
 * '<S231>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Detect Change'
 * '<S232>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Error_Hold'
 * '<S233>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Error_Scaling'
 * '<S234>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Estimate_State'
 * '<S235>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Measurement'
 * '<S236>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Measurement/Bias_Estimation'
 * '<S237>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Measurement/Bias_Estimation/Bias'
 * '<S238>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Measurement/Bias_Estimation/Detect Increase'
 * '<S239>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Measurement/Bias_Estimation/Detect_Jump_Signal'
 * '<S240>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/Rf_Correct/Rangefinder_Correct/Measurement/Bias_Estimation/Detect_Jump_Signal/Compare To Constant'
 * '<S241>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate'
 * '<S242>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Update'
 * '<S243>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init'
 * '<S244>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Height_Init'
 * '<S245>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Velocity_Init'
 * '<S246>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Height_Init/Baro_Reference_Height'
 * '<S247>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Height_Init/GPS_Reference_Height'
 * '<S248>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Height_Init/Rf_Reference_Height'
 * '<S249>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Velocity_Init/Baro_Velocity'
 * '<S250>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Velocity_Init/GPS_Velocity'
 * '<S251>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Velocity_Init/Rf_Velocity'
 * '<S252>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process'
 * '<S253>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control'
 * '<S254>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select'
 * '<S255>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures'
 * '<S256>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status'
 * '<S257>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Horizontal_Sensor_Select'
 * '<S258>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select'
 * '<S259>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Horizontal_Sensor_Select/Compare To Zero2'
 * '<S260>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Horizontal_Sensor_Select/Compare To Zero3'
 * '<S261>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Horizontal_Sensor_Select/Compare To Zero4'
 * '<S262>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select/Compare To Zero1'
 * '<S263>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select/Compare To Zero2'
 * '<S264>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select/Compare To Zero3'
 * '<S265>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select/Compare To Zero4'
 * '<S266>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select/Compare To Zero6'
 * '<S267>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures/Barometer_Meas'
 * '<S268>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures/GPS_Meas'
 * '<S269>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures/OpticalFlow_Meas'
 * '<S270>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures/Rangefinder_Meas'
 * '<S271>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures/Barometer_Meas/Second Order LPF'
 * '<S272>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status/Barometer_Status'
 * '<S273>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status/GPS_Status'
 * '<S274>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status/OpticalFlow_Status'
 * '<S275>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status/Rangefinder_Status'
 * '<S276>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset'
 * '<S277>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid'
 * '<S278>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference'
 * '<S279>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive'
 * '<S280>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive1'
 * '<S281>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive/Positive'
 * '<S282>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive1/Positive'
 * '<S283>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid'
 * '<S284>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid'
 * '<S285>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold'
 * '<S286>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold1'
 * '<S287>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Compare To Constant'
 * '<S288>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Compare To Constant1'
 * '<S289>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Compare To Constant2'
 * '<S290>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Detect Rise Positive'
 * '<S291>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Detect Rise Positive/Positive'
 * '<S292>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold1/Compare To Constant'
 * '<S293>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold1/Compare To Constant1'
 * '<S294>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold1/Compare To Constant2'
 * '<S295>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold1/Detect Rise Positive'
 * '<S296>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold1/Detect Rise Positive/Positive'
 * '<S297>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold'
 * '<S298>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold1'
 * '<S299>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold2'
 * '<S300>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Compare To Constant'
 * '<S301>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Compare To Constant1'
 * '<S302>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Compare To Constant2'
 * '<S303>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Detect Rise Positive'
 * '<S304>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Detect Rise Positive/Positive'
 * '<S305>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold1/Compare To Constant'
 * '<S306>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold1/Compare To Constant1'
 * '<S307>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold1/Compare To Constant2'
 * '<S308>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold1/Detect Rise Positive'
 * '<S309>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold1/Detect Rise Positive/Positive'
 * '<S310>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold2/Compare To Constant'
 * '<S311>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold2/Compare To Constant1'
 * '<S312>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold2/Compare To Constant2'
 * '<S313>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold2/Detect Rise Positive'
 * '<S314>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold2/Detect Rise Positive/Positive'
 * '<S315>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Bus_Constructor'
 * '<S316>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Bus_Select'
 * '<S317>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Height_Ref'
 * '<S318>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Position_Ref'
 * '<S319>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Height_Ref/Detect Rise Positive3'
 * '<S320>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Height_Ref/Detect Rise Positive3/Positive'
 * '<S321>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Position_Ref/Detect Rise Positive3'
 * '<S322>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Position_Ref/Detect Rise Positive3/Positive'
 * '<S323>' : 'INS/Sensor_PreProcess/AirSpeed_Process'
 * '<S324>' : 'INS/Sensor_PreProcess/Baro_PreProcess'
 * '<S325>' : 'INS/Sensor_PreProcess/GPS_PreProcess'
 * '<S326>' : 'INS/Sensor_PreProcess/IMU_PreProcess'
 * '<S327>' : 'INS/Sensor_PreProcess/MAG_PreProcess'
 * '<S328>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess'
 * '<S329>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess'
 * '<S330>' : 'INS/Sensor_PreProcess/AirSpeed_Process/Calculate_IAS'
 * '<S331>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Pressure_Height'
 * '<S332>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Relative_Height'
 * '<S333>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Sensor_Valid'
 * '<S334>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Relative_Height/Reference_Height'
 * '<S335>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Relative_Height/Sampling'
 * '<S336>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Relative_Height/Sampling/Compare To Constant'
 * '<S337>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Relative_Height/Sampling/Detect Change'
 * '<S338>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Relative_Height/Sampling/Interval Test3'
 * '<S339>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S340>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Sensor_Valid/Detect Change'
 * '<S341>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S342>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Sensor_Valid/Interval Test1'
 * '<S343>' : 'INS/Sensor_PreProcess/Baro_PreProcess/Sensor_Valid/Interval Test2'
 * '<S344>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Compare To Constant'
 * '<S345>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Compare To Constant1'
 * '<S346>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Data_Scalling'
 * '<S347>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality'
 * '<S348>' : 'INS/Sensor_PreProcess/GPS_PreProcess/WGS84_Model'
 * '<S349>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/Compare To Constant2'
 * '<S350>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status'
 * '<S351>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/check_timeout'
 * '<S352>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/horizontal_quality'
 * '<S353>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/speed_acc'
 * '<S354>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/vertical_quality'
 * '<S355>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Compare To Constant'
 * '<S356>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Compare To Constant1'
 * '<S357>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Ready'
 * '<S358>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Ready/valid_samples'
 * '<S359>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/check_timeout/Compare To Constant4'
 * '<S360>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/check_timeout/Detect Change'
 * '<S361>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/horizontal_quality/Second Order LPF'
 * '<S362>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/speed_acc/Second Order LPF'
 * '<S363>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/vertical_quality/Second Order LPF'
 * '<S364>' : 'INS/Sensor_PreProcess/GPS_PreProcess/WGS84_Model/LAT2FLAT Curve'
 * '<S365>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Data_Select'
 * '<S366>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid'
 * '<S367>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S368>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Detect Change'
 * '<S369>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S370>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Interval Test1'
 * '<S371>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Interval Test3'
 * '<S372>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Bus_Select'
 * '<S373>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process'
 * '<S374>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid'
 * '<S375>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate'
 * '<S376>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation'
 * '<S377>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_LUT'
 * '<S378>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality'
 * '<S379>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Inclination_Quality_Estimate'
 * '<S380>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Intensity_Quality_Estimate'
 * '<S381>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Second Order LPF'
 * '<S382>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Inclination_Quality_Estimate/Vector Modulus'
 * '<S383>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Intensity_Quality_Estimate/Vector Modulus'
 * '<S384>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation/Rotation Matrix Z'
 * '<S385>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation/Vector Normalize'
 * '<S386>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation/safe_divide'
 * '<S387>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S388>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Detect Change'
 * '<S389>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S390>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Interval Test1'
 * '<S391>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Height_Compensation'
 * '<S392>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Sensor_Valid'
 * '<S393>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Height_Compensation/First Order LPF'
 * '<S394>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S395>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Sensor_Valid/Detect Change'
 * '<S396>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S397>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Sensor_Valid/Interval Test1'
 * '<S398>' : 'INS/Sensor_PreProcess/OpticalFlow_PreProcess/Sensor_Valid/Interval Test2'
 * '<S399>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Sensor_Valid'
 * '<S400>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Subsystem'
 * '<S401>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Tilt_Compensation'
 * '<S402>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S403>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Sensor_Valid/Detect Change'
 * '<S404>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S405>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Sensor_Valid/Interval Test1'
 * '<S406>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Subsystem/Compare To Constant'
 * '<S407>' : 'INS/Sensor_PreProcess/Rangefinder_PreProcess/Subsystem/Compare To Zero'
 */
#endif                                 /* RTW_HEADER_INS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
