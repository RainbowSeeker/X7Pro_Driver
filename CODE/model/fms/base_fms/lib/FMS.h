/*
 * File: FMS.h
 *
 * Code generated for Simulink model 'FMS'.
 *
 * Model version                  : 9.79
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Feb 25 19:37:15 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FMS_h_
#define RTW_HEADER_FMS_h_
#ifndef FMS_COMMON_INCLUDES_
#define FMS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FMS_COMMON_INCLUDES_ */

#include <stddef.h>
#include "FMS_types.h"
#include <string.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<S351>/Hold Control' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S354>/Delay' */
  boolean_T icLoad;                    /* '<S354>/Delay' */
} DW_HoldControl_FMS_T;

/* Block states (default storage) for system '<S351>/Move Control' */
typedef struct {
  real32_T Integrator1_DSTATE;         /* '<S358>/Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S358>/Integrator' */
} DW_MoveControl_FMS_T;

/* Block states (default storage) for system '<S352>/Motion Status' */
typedef struct {
  uint16_T temporalCounter_i1;         /* '<S352>/Motion Status' */
  uint8_T is_c18_FMS;                  /* '<S352>/Motion Status' */
  uint8_T is_active_c18_FMS;           /* '<S352>/Motion Status' */
} DW_MotionStatus_FMS_T;

/* Block states (default storage) for system '<S361>/Hold Control' */
typedef struct {
  real32_T Delay_DSTATE[2];            /* '<S364>/Delay' */
  boolean_T icLoad;                    /* '<S364>/Delay' */
} DW_HoldControl_FMS_f_T;

/* Block states (default storage) for system '<S361>/Move Control' */
typedef struct {
  real32_T Integrator1_DSTATE[2];      /* '<S371>/Integrator1' */
  real32_T Integrator_DSTATE[2];       /* '<S371>/Integrator' */
} DW_MoveControl_FMS_f_T;

/* Block states (default storage) for system '<S362>/Motion State' */
typedef struct {
  uint16_T temporalCounter_i1;         /* '<S362>/Motion State' */
  uint8_T is_c19_FMS;                  /* '<S362>/Motion State' */
  uint8_T is_active_c19_FMS;           /* '<S362>/Motion State' */
} DW_MotionState_FMS_T;

/* Block states (default storage) for system '<S295>/Hold Control' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S298>/Delay' */
  boolean_T icLoad;                    /* '<S298>/Delay' */
} DW_HoldControl_FMS_m_T;

/* Block states (default storage) for system '<S295>/Move Control' */
typedef struct {
  real32_T Integrator1_DSTATE;         /* '<S304>/Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S304>/Integrator' */
} DW_MoveControl_FMS_c_T;

/* Block states (default storage) for system '<S296>/Motion State' */
typedef struct {
  uint8_T is_c10_FMS;                  /* '<S296>/Motion State' */
  uint8_T is_active_c10_FMS;           /* '<S296>/Motion State' */
  uint8_T temporalCounter_i1;          /* '<S296>/Motion State' */
} DW_MotionState_FMS_o_T;

/* Block signals (default storage) */
typedef struct {
  INS_Out_Bus BusConversion_InsertedFor_State;
  Pilot_Cmd_Bus BusConversion_InsertedFor_Sta_n;
  Commander_In_Bus Cmd_In;             /* '<Root>/State Machine' */
  real32_T Merge[2];                   /* '<S235>/Merge' */
  real32_T Merge_k;                    /* '<S211>/Merge' */
  real32_T Merge_d;                    /* '<S222>/Merge' */
  real32_T Merge_o[2];                 /* '<S264>/Merge' */
  real32_T Merge_n;                    /* '<S252>/Merge' */
  real32_T Merge_nj[2];                /* '<S88>/Merge' */
  real32_T Merge_e;                    /* '<S78>/Merge' */
  real32_T Merge_m[2];                 /* '<S307>/Merge' */
  real32_T Merge_ob;                   /* '<S285>/Merge' */
  real32_T Merge_p;                    /* '<S295>/Merge' */
  real32_T Merge_f[2];                 /* '<S361>/Merge' */
  real32_T Merge_pd;                   /* '<S351>/Merge' */
  VehicleState state;                  /* '<Root>/State Machine' */
  PilotMode target_mode;               /* '<Root>/SafeMode' */
  FMS_Cmd Switch1;                     /* '<S22>/Switch1' */
  uint8_T wp_consume;                  /* '<Root>/State Machine' */
  uint8_T wp_index;                    /* '<Root>/State Machine' */
  boolean_T LogicalOperator1;          /* '<S2>/Logical Operator1' */
  boolean_T LogicalOperator;           /* '<S1>/Logical Operator' */
} B_FMS_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T llo[2];                       /* '<Root>/State Machine' */
  real_T prep_mission_takeoff;         /* '<Root>/State Machine' */
  Msg_FMS_Cmd Msg[11];                 /* '<Root>/State Machine' */
  Queue_FMS_Cmd Queue;                 /* '<Root>/State Machine' */
  void* M_msgInterface;                /* '<Root>/State Machine' */
  void* M_msgHandle;                   /* '<Root>/State Machine' */
  void* M_msgDataPtr;                  /* '<Root>/State Machine' */
  real32_T DiscreteTimeIntegrator5_DSTATE[3];/* '<S12>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator5_DSTAT_j;/* '<S13>/Discrete-Time Integrator5' */
  real32_T Delay_DSTATE[2];            /* '<S71>/Delay' */
  real32_T l1_heading;                 /* '<S115>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_h;             /* '<S51>/Delay' */
  real32_T Integrator1_DSTATE;         /* '<S54>/Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S54>/Integrator' */
  real32_T Delay_DSTATE_p[2];          /* '<S347>/Delay' */
  real32_T l1_heading_a;               /* '<S388>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_d[2];          /* '<S327>/Delay' */
  real32_T Delay_DSTATE_do;            /* '<S328>/Delay' */
  real32_T Integrator1_DSTATE_e;       /* '<S331>/Integrator1' */
  real32_T Integrator_DSTATE_j;        /* '<S331>/Integrator' */
  uint32_T DelayInput1_DSTATE;         /* '<S25>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator1_DSTATE;/* '<S21>/Discrete-Time Integrator1' */
  uint32_T DelayInput1_DSTATE_f;       /* '<S30>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_i;       /* '<S26>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_p;       /* '<S27>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_c;       /* '<S8>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  uint32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S397>/Discrete-Time Integrator' */
  PilotMode Delay_DSTATE_c;            /* '<S23>/Delay' */
  real32_T home[3];                    /* '<Root>/State Machine' */
  int32_T sfEvent;                     /* '<Root>/State Machine' */
  int32_T durationCounter_1;           /* '<Root>/State Machine' */
  int32_T durationCounter_1_f;         /* '<Root>/State Machine' */
  int32_T durationCounter_1_i;         /* '<Root>/State Machine' */
  int32_T durationCounter_1_p;         /* '<Root>/State Machine' */
  int32_T durationCounter_1_i1;        /* '<Root>/State Machine' */
  int32_T durationCounter_2;           /* '<Root>/State Machine' */
  int32_T M_qId;                       /* '<Root>/State Machine' */
  uint32_T mission_timestamp_prev;     /* '<Root>/State Machine' */
  uint32_T mission_timestamp_start;    /* '<Root>/State Machine' */
  FMS_Cmd M;                           /* '<Root>/State Machine' */
  FMS_Cmd save_cmd;                    /* '<Root>/State Machine' */
  FMS_Cmd cmd_prev;                    /* '<Root>/State Machine' */
  FMS_Cmd cmd_start;                   /* '<Root>/State Machine' */
  FMS_Cmd M_msgData;                   /* '<Root>/State Machine' */
  FMS_Cmd M_msgReservedData;           /* '<Root>/State Machine' */
  PilotMode mode_prev;                 /* '<Root>/State Machine' */
  PilotMode mode_start;                /* '<Root>/State Machine' */
  uint16_T nav_cmd;                    /* '<Root>/State Machine' */
  uint16_T temporalCounter_i1;         /* '<Root>/State Machine' */
  uint16_T temporalCounter_i1_h;       /* '<S236>/Motion State' */
  uint16_T temporalCounter_i1_g;       /* '<S212>/Motion Status' */
  uint8_T Delay_DSTATE_o;              /* '<S9>/Delay' */
  uint8_T DelayInput1_DSTATE_pe;       /* '<S46>/Delay Input1' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S31>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_b; /* '<S33>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_l; /* '<S235>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_o; /* '<S211>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_j; /* '<S222>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_p; /* '<S264>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_bn;/* '<S252>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_i; /* '<S37>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_a; /* '<S88>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_e; /* '<S78>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_on;/* '<S41>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_g; /* '<S307>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_d; /* '<S285>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_bi;/* '<S295>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_c; /* '<S361>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_i5;/* '<S351>/Switch Case' */
  uint8_T DiscreteTimeIntegrator5_IC_LOAD;/* '<S12>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator5_IC_LO_g;/* '<S13>/Discrete-Time Integrator5' */
  uint8_T is_Command_Listener;         /* '<Root>/State Machine' */
  uint8_T is_Vehicle;                  /* '<Root>/State Machine' */
  uint8_T is_Arm;                      /* '<Root>/State Machine' */
  uint8_T is_Auto;                     /* '<Root>/State Machine' */
  uint8_T is_Offboard;                 /* '<Root>/State Machine' */
  uint8_T is_Mission;                  /* '<Root>/State Machine' */
  uint8_T is_Combo_Stick;              /* '<Root>/State Machine' */
  uint8_T is_active_c11_FMS;           /* '<Root>/State Machine' */
  uint8_T is_active_Command_Listener;  /* '<Root>/State Machine' */
  uint8_T is_active_Combo_Stick;       /* '<Root>/State Machine' */
  uint8_T is_active_Vehicle;           /* '<Root>/State Machine' */
  uint8_T is_c3_FMS;                   /* '<Root>/SafeMode' */
  uint8_T is_active_c3_FMS;            /* '<Root>/SafeMode' */
  uint8_T is_c16_FMS;                  /* '<S236>/Motion State' */
  uint8_T is_active_c16_FMS;           /* '<S236>/Motion State' */
  uint8_T is_c21_FMS;                  /* '<S223>/Motion State' */
  uint8_T is_active_c21_FMS;           /* '<S223>/Motion State' */
  uint8_T temporalCounter_i1_b;        /* '<S223>/Motion State' */
  uint8_T is_c20_FMS;                  /* '<S212>/Motion Status' */
  uint8_T is_active_c20_FMS;           /* '<S212>/Motion Status' */
  uint8_T Integrator1_IC_LOADING;      /* '<S54>/Integrator1' */
  uint8_T Integrator1_IC_LOADING_o;    /* '<S331>/Integrator1' */
  boolean_T valid_cmd;                 /* '<Root>/State Machine' */
  boolean_T bl;                        /* '<Root>/State Machine' */
  boolean_T br;                        /* '<Root>/State Machine' */
  boolean_T M_isValid;                 /* '<Root>/State Machine' */
  boolean_T icLoad;                    /* '<S71>/Delay' */
  boolean_T icLoad_k;                  /* '<S51>/Delay' */
  boolean_T icLoad_h;                  /* '<S347>/Delay' */
  boolean_T icLoad_j;                  /* '<S327>/Delay' */
  boolean_T icLoad_c;                  /* '<S328>/Delay' */
  DW_MoveControl_FMS_f_T MoveControl_k;/* '<S235>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_at;/* '<S235>/Hold Control' */
  DW_MoveControl_FMS_c_T MoveControl_mr;/* '<S222>/Move Control' */
  DW_HoldControl_FMS_m_T HoldControl_e;/* '<S222>/Hold Control' */
  DW_MoveControl_FMS_T MoveControl_be; /* '<S211>/Move Control' */
  DW_HoldControl_FMS_T HoldControl_p;  /* '<S211>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState_g;/* '<S265>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_i;/* '<S264>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_f;/* '<S264>/Hold Control' */
  DW_MotionState_FMS_o_T sf_MotionState_d;/* '<S253>/Motion State' */
  DW_MoveControl_FMS_c_T MoveControl_b;/* '<S252>/Move Control' */
  DW_HoldControl_FMS_m_T HoldControl_kq;/* '<S252>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState_n;/* '<S89>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_cp;/* '<S88>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_d;/* '<S88>/Hold Control' */
  DW_MotionStatus_FMS_T sf_MotionStatus_j;/* '<S79>/Motion Status' */
  DW_MoveControl_FMS_T MoveControl_m;  /* '<S78>/Move Control' */
  DW_HoldControl_FMS_T HoldControl_a;  /* '<S78>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState_l;/* '<S308>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_h;/* '<S307>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_h;/* '<S307>/Hold Control' */
  DW_MotionState_FMS_o_T sf_MotionState_i;/* '<S296>/Motion State' */
  DW_MoveControl_FMS_c_T MoveControl_o;/* '<S295>/Move Control' */
  DW_HoldControl_FMS_m_T HoldControl_k;/* '<S295>/Hold Control' */
  DW_MotionStatus_FMS_T sf_MotionStatus_d;/* '<S286>/Motion Status' */
  DW_MoveControl_FMS_T MoveControl_g;  /* '<S285>/Move Control' */
  DW_HoldControl_FMS_T HoldControl_b;  /* '<S285>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState; /* '<S362>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_c;/* '<S361>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_g;/* '<S361>/Hold Control' */
  DW_MotionStatus_FMS_T sf_MotionStatus;/* '<S352>/Motion Status' */
  DW_MoveControl_FMS_T MoveControl;    /* '<S351>/Move Control' */
  DW_HoldControl_FMS_T HoldControl;    /* '<S351>/Hold Control' */
} DW_FMS_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Mission_SubSystem_Reset_ZCE;/* '<S43>/Mission_SubSystem' */
} PrevZCX_FMS_T;

/* Invariant block signals for system '<S31>/Disarm' */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S35>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S35>/Data Type Conversion1' */
} ConstB_Disarm_FMS_T;

/* Invariant block signals for system '<S351>/Move Control' */
typedef struct {
  const real32_T Gain4;                /* '<S359>/Gain4' */
  const real32_T Square;               /* '<S359>/Square' */
  const real32_T d;                    /* '<S359>/Multiply' */
} ConstB_MoveControl_FMS_T;

/* Invariant block signals for system '<S361>/Hold Control' */
typedef struct {
  const real32_T VectorConcatenate3[3];/* '<S368>/Vector Concatenate3' */
} ConstB_HoldControl_FMS_g_T;

/* Invariant block signals for system '<S361>/Move Control' */
typedef struct {
  const real32_T Gain4;                /* '<S372>/Gain4' */
  const real32_T Square;               /* '<S372>/Square' */
  const real32_T d;                    /* '<S372>/Multiply' */
} ConstB_MoveControl_FMS_h_T;

/* Invariant block signals for system '<S295>/Move Control' */
typedef struct {
  const real32_T Gain4;                /* '<S305>/Gain4' */
  const real32_T Square;               /* '<S305>/Square' */
  const real32_T d;                    /* '<S305>/Multiply' */
} ConstB_MoveControl_FMS_n_T;

/* Invariant block signals for system '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
typedef struct {
  const real_T Sum;                    /* '<S400>/Sum' */
  const real_T ff;                     /* '<S400>/Multiply3' */
  const real_T Sum4;                   /* '<S400>/Sum4' */
} ConstB_VehicleArmAutoMissionL_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T Gain4;                /* '<S60>/Gain4' */
  const real32_T Square;               /* '<S60>/Square' */
  const real32_T d;                    /* '<S60>/Multiply' */
  const real32_T TmpSignalConversionAtMathFu[2];
  const real32_T MathFunction[2];      /* '<S64>/Math Function' */
  const real32_T SumofElements;        /* '<S64>/Sum of Elements' */
  const real32_T MathFunction1;        /* '<S64>/Math Function1' */
  const real32_T Product[2];           /* '<S64>/Product' */
  const real32_T Switch[3];            /* '<S64>/Switch' */
  const real32_T Divide[2];            /* '<S64>/Divide' */
  const real32_T VectorConcatenate3[3];/* '<S118>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_e[3];/* '<S129>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_o[3];/* '<S131>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_n[3];/* '<S191>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_i[3];/* '<S194>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_ny[3];/* '<S197>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_e0[3];/* '<S198>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_l[3];/* '<S205>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_iz[3];/* '<S207>/Vector Concatenate3' */
  const real32_T Gain4_o;              /* '<S337>/Gain4' */
  const real32_T Square_p;             /* '<S337>/Square' */
  const real32_T d_n;                  /* '<S337>/Multiply' */
  const real32_T TmpSignalConversionAtMath_f[2];
  const real32_T MathFunction_g[2];    /* '<S341>/Math Function' */
  const real32_T SumofElements_o;      /* '<S341>/Sum of Elements' */
  const real32_T MathFunction1_n;      /* '<S341>/Math Function1' */
  const real32_T Product_i[2];         /* '<S341>/Product' */
  const real32_T Switch_p[3];          /* '<S341>/Switch' */
  const real32_T Divide_o[2];          /* '<S341>/Divide' */
  const real32_T VectorConcatenate3_p[3];/* '<S391>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_n5[3];/* '<S324>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_pk[3];/* '<S396>/Vector Concatenate3' */
  const uint8_T DataTypeConversion;    /* '<S38>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S38>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_b;  /* '<S39>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_o; /* '<S39>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S39>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_g;  /* '<S40>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_i; /* '<S40>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_j; /* '<S40>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_l;  /* '<S47>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_b; /* '<S47>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_b; /* '<S47>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_a;  /* '<S44>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_n; /* '<S44>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_k; /* '<S44>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_b5; /* '<S281>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_m; /* '<S281>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_c;  /* '<S277>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_c; /* '<S277>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_l; /* '<S277>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_k;  /* '<S279>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_h; /* '<S279>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_m; /* '<S279>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_p;  /* '<S278>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_iv;/* '<S278>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_bf;/* '<S278>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_ge; /* '<S280>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_cc;/* '<S280>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_b0;/* '<S280>/Data Type Conversion2' */
  const uint8_T DataTypeConversion1_f; /* '<S36>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_h; /* '<S36>/Data Type Conversion2' */
  ConstB_VehicleArmAutoMissionL_T VehicleArmAutoMissionLLA2FLAT;
                                  /* '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
  ConstB_Disarm_FMS_T Unknown;         /* '<S33>/Unknown' */
  ConstB_MoveControl_FMS_h_T MoveControl_k;/* '<S235>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_at;/* '<S235>/Hold Control' */
  ConstB_MoveControl_FMS_n_T MoveControl_mr;/* '<S222>/Move Control' */
  ConstB_MoveControl_FMS_T MoveControl_be;/* '<S211>/Move Control' */
  ConstB_MoveControl_FMS_h_T MoveControl_i;/* '<S264>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_f;/* '<S264>/Hold Control' */
  ConstB_MoveControl_FMS_n_T MoveControl_b;/* '<S252>/Move Control' */
  ConstB_Disarm_FMS_T Unknown_d;       /* '<S37>/Unknown' */
  ConstB_MoveControl_FMS_h_T MoveControl_cp;/* '<S88>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_d;/* '<S88>/Hold Control' */
  ConstB_MoveControl_FMS_T MoveControl_m;/* '<S78>/Move Control' */
  ConstB_MoveControl_FMS_h_T MoveControl_h;/* '<S307>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_h;/* '<S307>/Hold Control' */
  ConstB_MoveControl_FMS_n_T MoveControl_o;/* '<S295>/Move Control' */
  ConstB_MoveControl_FMS_T MoveControl_g;/* '<S285>/Move Control' */
  ConstB_MoveControl_FMS_h_T MoveControl_c;/* '<S361>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_g;/* '<S361>/Hold Control' */
  ConstB_MoveControl_FMS_T MoveControl;/* '<S351>/Move Control' */
  ConstB_Disarm_FMS_T Disarm;          /* '<S31>/Disarm' */
} ConstB_FMS_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  Pilot_Cmd_Bus Pilot_Cmd;             /* '<Root>/Pilot_Cmd' */
  GCS_Cmd_Bus GCS_Cmd;                 /* '<Root>/GCS_Cmd' */
  Auto_Cmd_Bus Auto_Cmd;               /* '<Root>/Auto_Cmd' */
  Mission_Data_Bus Mission_Data;       /* '<Root>/Mission_Data' */
  INS_Out_Bus INS_Out;                 /* '<Root>/INS_Out' */
  Control_Out_Bus Control_Out;         /* '<Root>/Control_Out' */
} ExtU_FMS_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  FMS_Out_Bus FMS_Out;                 /* '<Root>/FMS_Out' */
} ExtY_FMS_T;

/* Real-time Model Data Structure */
struct tag_RTM_FMS_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_FMS_T FMS_B;

/* Block states (default storage) */
extern DW_FMS_T FMS_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_FMS_T FMS_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_FMS_T FMS_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_FMS_T FMS_Y;

/* External data declarations for dependent source files */
extern const FMS_Out_Bus FMS_rtZFMS_Out_Bus;/* FMS_Out_Bus ground */
extern const ConstB_FMS_T FMS_ConstB;  /* constant block i/o */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern struct_z8TbXuqo9JNiexfZo6b1iC FMS_PARAM;/* Variable: FMS_PARAM
                                                * Referenced by:
                                                *   '<Root>/ACCEPT_R'
                                                *   '<S279>/L1'
                                                *   '<S47>/L1'
                                                *   '<S121>/Saturation'
                                                *   '<S122>/Saturation1'
                                                *   '<S122>/Saturation2'
                                                *   '<S122>/Saturation3'
                                                *   '<S211>/Saturation1'
                                                *   '<S222>/Saturation'
                                                *   '<S235>/Saturation1'
                                                *   '<S252>/Saturation'
                                                *   '<S264>/Saturation1'
                                                *   '<S320>/Saturation1'
                                                *   '<S392>/Gain2'
                                                *   '<S392>/Saturation1'
                                                *   '<S175>/Gain2'
                                                *   '<S182>/Gain1'
                                                *   '<S182>/Gain2'
                                                *   '<S214>/Gain2'
                                                *   '<S215>/Gain1'
                                                *   '<S220>/Constant'
                                                *   '<S225>/Gain2'
                                                *   '<S226>/Gain1'
                                                *   '<S233>/Constant'
                                                *   '<S238>/Gain2'
                                                *   '<S239>/Gain6'
                                                *   '<S247>/Constant'
                                                *   '<S248>/Constant'
                                                *   '<S255>/Gain2'
                                                *   '<S256>/Gain1'
                                                *   '<S267>/Gain2'
                                                *   '<S268>/Gain6'
                                                *   '<S285>/Saturation1'
                                                *   '<S295>/Saturation'
                                                *   '<S307>/Saturation1'
                                                *   '<S321>/Gain2'
                                                *   '<S343>/vel'
                                                *   '<S343>/Saturation'
                                                *   '<S343>/Switch'
                                                *   '<S66>/Gain'
                                                *   '<S66>/Saturation1'
                                                *   '<S67>/vel'
                                                *   '<S67>/Saturation'
                                                *   '<S67>/Switch'
                                                *   '<S217>/Dead Zone'
                                                *   '<S217>/Gain'
                                                *   '<S230>/Dead Zone'
                                                *   '<S230>/Gain'
                                                *   '<S243>/Dead Zone'
                                                *   '<S243>/Gain'
                                                *   '<S244>/Dead Zone'
                                                *   '<S244>/Gain'
                                                *   '<S260>/Dead Zone'
                                                *   '<S260>/Gain'
                                                *   '<S272>/Dead Zone'
                                                *   '<S272>/Gain'
                                                *   '<S273>/Dead Zone'
                                                *   '<S273>/Gain'
                                                *   '<S288>/Gain2'
                                                *   '<S289>/Gain1'
                                                *   '<S298>/Gain2'
                                                *   '<S299>/Gain1'
                                                *   '<S310>/Gain2'
                                                *   '<S311>/Gain6'
                                                *   '<S330>/Gain2'
                                                *   '<S330>/Saturation'
                                                *   '<S331>/Integrator'
                                                *   '<S53>/Gain2'
                                                *   '<S53>/Saturation'
                                                *   '<S54>/Integrator'
                                                *   '<S291>/Dead Zone'
                                                *   '<S291>/Gain'
                                                *   '<S303>/Dead Zone'
                                                *   '<S303>/Gain'
                                                *   '<S315>/Dead Zone'
                                                *   '<S315>/Gain'
                                                *   '<S316>/Dead Zone'
                                                *   '<S316>/Gain'
                                                *   '<S351>/Saturation1'
                                                *   '<S361>/Saturation1'
                                                *   '<S78>/Saturation1'
                                                *   '<S88>/Saturation1'
                                                *   '<S354>/Gain2'
                                                *   '<S355>/Gain1'
                                                *   '<S364>/Gain2'
                                                *   '<S365>/Gain6'
                                                *   '<S81>/Gain2'
                                                *   '<S82>/Gain1'
                                                *   '<S91>/Gain2'
                                                *   '<S92>/Gain6'
                                                *   '<S357>/Dead Zone'
                                                *   '<S357>/Gain'
                                                *   '<S369>/Dead Zone'
                                                *   '<S369>/Gain'
                                                *   '<S370>/Dead Zone'
                                                *   '<S370>/Gain'
                                                *   '<S84>/Dead Zone'
                                                *   '<S84>/Gain'
                                                *   '<S96>/Dead Zone'
                                                *   '<S96>/Gain'
                                                *   '<S97>/Dead Zone'
                                                *   '<S97>/Gain'
                                                */
extern struct_TYt7YeNdxIDXfczXumtXXB FMS_EXPORT;/* Variable: FMS_EXPORT
                                                 * Referenced by:
                                                 *   '<S1>/Constant'
                                                 *   '<S21>/Constant1'
                                                 *   '<S397>/Constant'
                                                 */

/* Model entry point functions */
extern void FMS_init(void);
extern void FMS_step(void);
extern void FMS_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FMS_T *const FMS_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S10>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate' : Unused code path elimination
 * Block '<S65>/Data Type Duplicate' : Unused code path elimination
 * Block '<S112>/Data Type Duplicate' : Unused code path elimination
 * Block '<S113>/Data Type Duplicate' : Unused code path elimination
 * Block '<S109>/Data Type Duplicate' : Unused code path elimination
 * Block '<S110>/Data Type Duplicate' : Unused code path elimination
 * Block '<S116>/Data Type Duplicate' : Unused code path elimination
 * Block '<S341>/Data Type Duplicate' : Unused code path elimination
 * Block '<S342>/Data Type Duplicate' : Unused code path elimination
 * Block '<S385>/Data Type Duplicate' : Unused code path elimination
 * Block '<S386>/Data Type Duplicate' : Unused code path elimination
 * Block '<S382>/Data Type Duplicate' : Unused code path elimination
 * Block '<S383>/Data Type Duplicate' : Unused code path elimination
 * Block '<S389>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S69>/Reshape' : Reshape block reduction
 * Block '<S50>/Reshape' : Reshape block reduction
 * Block '<S50>/Reshape1' : Reshape block reduction
 * Block '<S345>/Reshape' : Reshape block reduction
 * Block '<S327>/Reshape' : Reshape block reduction
 * Block '<S327>/Reshape1' : Reshape block reduction
 * Block '<S395>/Reshape' : Reshape block reduction
 * Block '<S397>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S32>/Signal Copy3' : Eliminate redundant signal conversion block
 * Block '<S32>/Signal Copy4' : Eliminate redundant signal conversion block
 * Block '<S32>/Signal Copy5' : Eliminate redundant signal conversion block
 * Block '<S32>/Signal Copy6' : Eliminate redundant signal conversion block
 * Block '<S398>/Signal Conversion' : Eliminate redundant signal conversion block
 */

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
 * '<Root>' : 'FMS'
 * '<S1>'   : 'FMS/Auto_Cmd_Valid'
 * '<S2>'   : 'FMS/Brake Check'
 * '<S3>'   : 'FMS/Command Process'
 * '<S4>'   : 'FMS/FMS Commander'
 * '<S5>'   : 'FMS/SafeMode'
 * '<S6>'   : 'FMS/State Machine'
 * '<S7>'   : 'FMS/Auto_Cmd_Valid/Compare To Constant4'
 * '<S8>'   : 'FMS/Auto_Cmd_Valid/Detect Change'
 * '<S9>'   : 'FMS/Auto_Cmd_Valid/Ever_Valid'
 * '<S10>'  : 'FMS/Auto_Cmd_Valid/Interval Test'
 * '<S11>'  : 'FMS/Brake Check/Compare To Constant'
 * '<S12>'  : 'FMS/Brake Check/First Order LPF'
 * '<S13>'  : 'FMS/Brake Check/First Order LPF2'
 * '<S14>'  : 'FMS/Brake Check/Interval Test'
 * '<S15>'  : 'FMS/Brake Check/Quaternion To DCM'
 * '<S16>'  : 'FMS/Brake Check/Quaternion To DCM/Quaternion Normalize'
 * '<S17>'  : 'FMS/Brake Check/Quaternion To DCM/column_1'
 * '<S18>'  : 'FMS/Brake Check/Quaternion To DCM/column_2'
 * '<S19>'  : 'FMS/Brake Check/Quaternion To DCM/column_3'
 * '<S20>'  : 'FMS/Brake Check/Quaternion To DCM/Quaternion Normalize/Quaternion Modulus'
 * '<S21>'  : 'FMS/Command Process/Check Valid'
 * '<S22>'  : 'FMS/Command Process/Command Routing'
 * '<S23>'  : 'FMS/Command Process/Mode Routing'
 * '<S24>'  : 'FMS/Command Process/Check Valid/Compare To Constant1'
 * '<S25>'  : 'FMS/Command Process/Check Valid/Detect Change1'
 * '<S26>'  : 'FMS/Command Process/Command Routing/Detect Change3'
 * '<S27>'  : 'FMS/Command Process/Command Routing/Detect Change4'
 * '<S28>'  : 'FMS/Command Process/Mode Routing/Compare To Zero'
 * '<S29>'  : 'FMS/Command Process/Mode Routing/Compare To Zero1'
 * '<S30>'  : 'FMS/Command Process/Mode Routing/Detect Change'
 * '<S31>'  : 'FMS/FMS Commander/Commander'
 * '<S32>'  : 'FMS/FMS Commander/FMS_Input'
 * '<S33>'  : 'FMS/FMS Commander/Commander/Arm'
 * '<S34>'  : 'FMS/FMS Commander/Commander/Bus_Constructor'
 * '<S35>'  : 'FMS/FMS Commander/Commander/Disarm'
 * '<S36>'  : 'FMS/FMS Commander/Commander/Standby'
 * '<S37>'  : 'FMS/FMS Commander/Commander/Arm/Auto'
 * '<S38>'  : 'FMS/FMS Commander/Commander/Arm/Manual'
 * '<S39>'  : 'FMS/FMS Commander/Commander/Arm/Position'
 * '<S40>'  : 'FMS/FMS Commander/Commander/Arm/Stabilize'
 * '<S41>'  : 'FMS/FMS Commander/Commander/Arm/SubMode'
 * '<S42>'  : 'FMS/FMS Commander/Commander/Arm/Unknown'
 * '<S43>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission'
 * '<S44>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard'
 * '<S45>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Unknown'
 * '<S46>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Detect Change'
 * '<S47>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem'
 * '<S48>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander'
 * '<S49>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander'
 * '<S50>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Way Points'
 * '<S51>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control'
 * '<S52>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle'
 * '<S53>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control'
 * '<S54>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/TD'
 * '<S55>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/psi_saturation'
 * '<S56>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/psi_saturation1'
 * '<S57>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control/Bus_Selection'
 * '<S58>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control/psi_saturation'
 * '<S59>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control/psi_saturation/Compare To Constant'
 * '<S60>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/TD/fhan '
 * '<S61>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/psi_saturation/Compare To Constant'
 * '<S62>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/psi_saturation1/Compare To Constant'
 * '<S63>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle/2D Cross Product'
 * '<S64>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle/Vector Normalize'
 * '<S65>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle/Vector Normalize1'
 * '<S66>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control'
 * '<S67>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Cruise Speed '
 * '<S68>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position'
 * '<S69>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP'
 * '<S70>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration'
 * '<S71>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed'
 * '<S72>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control/Target Height'
 * '<S73>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control/Target Height/Vector Modulus'
 * '<S74>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control/Target Height/Vector Modulus1'
 * '<S75>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Cruise Speed /Vector Modulus'
 * '<S76>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold'
 * '<S77>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold'
 * '<S78>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller'
 * '<S79>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Detect Movement'
 * '<S80>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Brake Control'
 * '<S81>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Hold Control'
 * '<S82>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control'
 * '<S83>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Hold Control/Bus_Selection'
 * '<S84>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/DeadZone'
 * '<S85>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/TD1'
 * '<S86>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/TD1/fhan '
 * '<S87>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Altitude Hold/Detect Movement/Motion Status'
 * '<S88>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller'
 * '<S89>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Detect Movement'
 * '<S90>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Brake Control'
 * '<S91>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control'
 * '<S92>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Move Control'
 * '<S93>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S94>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S95>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S96>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/DeadZone'
 * '<S97>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/DeadZone1'
 * '<S98>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/TD'
 * '<S99>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/TD/fhan '
 * '<S100>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Hold Position/Position Hold/Detect Movement/Motion State'
 * '<S101>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/Compare To Constant'
 * '<S102>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/Compare To Constant1'
 * '<S103>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/NearbyRefWP'
 * '<S104>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/OutRegionRegWP'
 * '<S105>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/SearchL1RefWP'
 * '<S106>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle'
 * '<S107>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Modulus'
 * '<S108>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Modulus1'
 * '<S109>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Normalize'
 * '<S110>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Normalize1'
 * '<S111>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle/2D Cross Product'
 * '<S112>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize'
 * '<S113>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize1'
 * '<S114>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Ground Speed'
 * '<S115>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix'
 * '<S116>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Ground Speed/Vector Normalize2'
 * '<S117>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM'
 * '<S118>' : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM/Rotation Matrix Z'
 * '<S119>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command'
 * '<S120>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask'
 * '<S121>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command'
 * '<S122>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command'
 * '<S123>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Body_Frame'
 * '<S124>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Command_Mask'
 * '<S125>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Global_Frame'
 * '<S126>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Local_Frame'
 * '<S127>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Command_Mask/Compare To Zero2'
 * '<S128>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Global_Frame/Psi To DCM'
 * '<S129>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Global_Frame/Psi To DCM/Rotation Matrix Z'
 * '<S130>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Local_Frame/Psi To DCM2'
 * '<S131>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Local_Frame/Psi To DCM2/Rotation Matrix Z'
 * '<S132>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero'
 * '<S133>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero1'
 * '<S134>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero12'
 * '<S135>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero2'
 * '<S136>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero3'
 * '<S137>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero4'
 * '<S138>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero5'
 * '<S139>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem'
 * '<S140>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1'
 * '<S141>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ax_cmd_valid'
 * '<S142>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ay_cmd_valid'
 * '<S143>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/az_cmd_valid'
 * '<S144>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/p_cmd_valid'
 * '<S145>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/phi_cmd_valid'
 * '<S146>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/psi_rate_cmd_valid'
 * '<S147>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/q_cmd_valid'
 * '<S148>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/r_cmd_valid'
 * '<S149>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/theta_cmd_valid'
 * '<S150>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/throttle_cmd_valid'
 * '<S151>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/u_cmd_valid'
 * '<S152>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/v_cmd_valid'
 * '<S153>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/w_cmd_valid'
 * '<S154>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Constant'
 * '<S155>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Zero6'
 * '<S156>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Zero7'
 * '<S157>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Zero8'
 * '<S158>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Constant'
 * '<S159>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Zero10'
 * '<S160>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Zero11'
 * '<S161>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Zero9'
 * '<S162>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ax_cmd_valid/bit_shift'
 * '<S163>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ay_cmd_valid/bit_shift'
 * '<S164>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/az_cmd_valid/bit_shift'
 * '<S165>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/p_cmd_valid/bit_shift'
 * '<S166>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/phi_cmd_valid/bit_shift'
 * '<S167>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/psi_rate_cmd_valid/bit_shift'
 * '<S168>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/q_cmd_valid/bit_shift'
 * '<S169>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/r_cmd_valid/bit_shift'
 * '<S170>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/theta_cmd_valid/bit_shift'
 * '<S171>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/throttle_cmd_valid/bit_shift'
 * '<S172>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/u_cmd_valid/bit_shift'
 * '<S173>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/v_cmd_valid/bit_shift'
 * '<S174>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/w_cmd_valid/bit_shift'
 * '<S175>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control'
 * '<S176>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Psi_Rate_Command'
 * '<S177>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Compare To Zero'
 * '<S178>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Error'
 * '<S179>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Error/psi_err_saturation'
 * '<S180>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Error/psi_err_saturation/Compare To Constant'
 * '<S181>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Psi_Rate_Command/Compare To Zero1'
 * '<S182>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control'
 * '<S183>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command'
 * '<S184>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Body_Error'
 * '<S185>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Bus_Select1'
 * '<S186>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Bus_Select2'
 * '<S187>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Command_Mask'
 * '<S188>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Global_Error'
 * '<S189>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error'
 * '<S190>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Body_Error/Psi To DCM1'
 * '<S191>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Body_Error/Psi To DCM1/Rotation Matrix Z'
 * '<S192>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Command_Mask/Compare To Zero'
 * '<S193>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Global_Error/Psi To DCM'
 * '<S194>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Global_Error/Psi To DCM/Rotation Matrix Z'
 * '<S195>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM1'
 * '<S196>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM2'
 * '<S197>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM1/Rotation Matrix Z'
 * '<S198>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM2/Rotation Matrix Z'
 * '<S199>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Body_Frame'
 * '<S200>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Command_Mask'
 * '<S201>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Global_Frame'
 * '<S202>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Local_Frame'
 * '<S203>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Command_Mask/Compare To Zero2'
 * '<S204>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Global_Frame/Psi To DCM'
 * '<S205>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Global_Frame/Psi To DCM/Rotation Matrix Z'
 * '<S206>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Local_Frame/Psi To DCM2'
 * '<S207>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Local_Frame/Psi To DCM2/Rotation Matrix Z'
 * '<S208>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command'
 * '<S209>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command'
 * '<S210>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command'
 * '<S211>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller'
 * '<S212>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Detect Movement'
 * '<S213>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Brake Control'
 * '<S214>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Hold Control'
 * '<S215>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Move Control'
 * '<S216>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Hold Control/Bus_Selection'
 * '<S217>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Move Control/DeadZone'
 * '<S218>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Move Control/TD1'
 * '<S219>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Controller/Move Control/TD1/fhan '
 * '<S220>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Detect Movement/Compare To Constant'
 * '<S221>' : 'FMS/FMS Commander/Commander/Arm/Position/Altitude Command/Detect Movement/Motion Status'
 * '<S222>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller'
 * '<S223>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Detect Movement'
 * '<S224>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Brake Control'
 * '<S225>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control'
 * '<S226>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control'
 * '<S227>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control/Bus_Selection'
 * '<S228>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control/psi_err_saturation'
 * '<S229>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control/psi_err_saturation/Compare To Constant'
 * '<S230>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control/DeadZone'
 * '<S231>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control/TD'
 * '<S232>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control/TD/fhan '
 * '<S233>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Detect Movement/Compare To Constant'
 * '<S234>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Detect Movement/Motion State'
 * '<S235>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller'
 * '<S236>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement'
 * '<S237>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Brake Control'
 * '<S238>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control'
 * '<S239>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control'
 * '<S240>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control/Bus_Selection'
 * '<S241>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control/Psi To DCM'
 * '<S242>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S243>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/DeadZone'
 * '<S244>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/DeadZone1'
 * '<S245>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/TD'
 * '<S246>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/TD/fhan '
 * '<S247>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement/Compare To Constant'
 * '<S248>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement/Compare To Constant1'
 * '<S249>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement/Motion State'
 * '<S250>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold'
 * '<S251>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold'
 * '<S252>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller'
 * '<S253>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Detect Movement'
 * '<S254>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Brake Control'
 * '<S255>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control'
 * '<S256>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control'
 * '<S257>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control/Bus_Selection'
 * '<S258>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control/psi_err_saturation'
 * '<S259>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control/psi_err_saturation/Compare To Constant'
 * '<S260>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control/DeadZone'
 * '<S261>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control/TD'
 * '<S262>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control/TD/fhan '
 * '<S263>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Detect Movement/Motion State'
 * '<S264>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller'
 * '<S265>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Detect Movement'
 * '<S266>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Brake Control'
 * '<S267>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control'
 * '<S268>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control'
 * '<S269>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S270>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S271>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S272>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/DeadZone'
 * '<S273>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/DeadZone1'
 * '<S274>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/TD'
 * '<S275>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/TD/fhan '
 * '<S276>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Detect Movement/Motion State'
 * '<S277>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold'
 * '<S278>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land'
 * '<S279>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return'
 * '<S280>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff'
 * '<S281>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Unknown'
 * '<S282>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold'
 * '<S283>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold'
 * '<S284>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold'
 * '<S285>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller'
 * '<S286>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Detect Movement'
 * '<S287>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Brake Control'
 * '<S288>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Hold Control'
 * '<S289>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control'
 * '<S290>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Hold Control/Bus_Selection'
 * '<S291>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control/DeadZone'
 * '<S292>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control/TD1'
 * '<S293>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control/TD1/fhan '
 * '<S294>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Detect Movement/Motion Status'
 * '<S295>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller'
 * '<S296>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Detect Movement'
 * '<S297>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Brake Control'
 * '<S298>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control'
 * '<S299>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control'
 * '<S300>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control/Bus_Selection'
 * '<S301>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control/psi_err_saturation'
 * '<S302>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control/psi_err_saturation/Compare To Constant'
 * '<S303>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control/DeadZone'
 * '<S304>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control/TD'
 * '<S305>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control/TD/fhan '
 * '<S306>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Detect Movement/Motion State'
 * '<S307>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller'
 * '<S308>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Detect Movement'
 * '<S309>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Brake Control'
 * '<S310>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control'
 * '<S311>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control'
 * '<S312>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S313>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S314>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S315>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/DeadZone'
 * '<S316>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/DeadZone1'
 * '<S317>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/TD'
 * '<S318>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/TD/fhan '
 * '<S319>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Detect Movement/Motion State'
 * '<S320>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command'
 * '<S321>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control'
 * '<S322>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control/Bus_Selection'
 * '<S323>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control/Psi To DCM'
 * '<S324>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control/Psi To DCM/Rotation Matrix Z'
 * '<S325>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander'
 * '<S326>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander'
 * '<S327>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Way Points'
 * '<S328>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control'
 * '<S329>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle'
 * '<S330>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control'
 * '<S331>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/TD'
 * '<S332>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation'
 * '<S333>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation1'
 * '<S334>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control/Bus_Selection'
 * '<S335>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control/psi_saturation'
 * '<S336>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control/psi_saturation/Compare To Constant'
 * '<S337>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/TD/fhan '
 * '<S338>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation/Compare To Constant'
 * '<S339>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation1/Compare To Constant'
 * '<S340>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle/2D Cross Product'
 * '<S341>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle/Vector Normalize'
 * '<S342>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle/Vector Normalize1'
 * '<S343>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Cruise Speed '
 * '<S344>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position'
 * '<S345>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP'
 * '<S346>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration'
 * '<S347>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed'
 * '<S348>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Cruise Speed /Vector Modulus'
 * '<S349>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold'
 * '<S350>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold'
 * '<S351>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller'
 * '<S352>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Detect Movement'
 * '<S353>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Brake Control'
 * '<S354>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Hold Control'
 * '<S355>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control'
 * '<S356>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Hold Control/Bus_Selection'
 * '<S357>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/DeadZone'
 * '<S358>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/TD1'
 * '<S359>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/TD1/fhan '
 * '<S360>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Detect Movement/Motion Status'
 * '<S361>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller'
 * '<S362>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Detect Movement'
 * '<S363>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Brake Control'
 * '<S364>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control'
 * '<S365>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control'
 * '<S366>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S367>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S368>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S369>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/DeadZone'
 * '<S370>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/DeadZone1'
 * '<S371>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/TD'
 * '<S372>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/TD/fhan '
 * '<S373>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Detect Movement/Motion State'
 * '<S374>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/Compare To Constant'
 * '<S375>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/Compare To Constant1'
 * '<S376>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/NearbyRefWP'
 * '<S377>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/OutRegionRegWP'
 * '<S378>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/SearchL1RefWP'
 * '<S379>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle'
 * '<S380>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Modulus'
 * '<S381>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Modulus1'
 * '<S382>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Normalize'
 * '<S383>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Normalize1'
 * '<S384>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle/2D Cross Product'
 * '<S385>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize'
 * '<S386>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize1'
 * '<S387>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Ground Speed'
 * '<S388>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix'
 * '<S389>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Ground Speed/Vector Normalize2'
 * '<S390>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM'
 * '<S391>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM/Rotation Matrix Z'
 * '<S392>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position'
 * '<S393>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Bus_Selection'
 * '<S394>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Psi To DCM'
 * '<S395>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Target Position'
 * '<S396>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Psi To DCM/Rotation Matrix Z'
 * '<S397>' : 'FMS/FMS Commander/Commander/Bus_Constructor/timestamp'
 * '<S398>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT'
 * '<S399>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT'
 * '<S400>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LAT2FLAT Curve'
 * '<S401>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap'
 * '<S402>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/Rotation'
 * '<S403>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Weap Angle 180'
 * '<S404>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude'
 * '<S405>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Weap Angle 180/Compare To Constant1'
 * '<S406>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude/Compare To Constant1'
 * '<S407>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude/Weap Angle 180'
 * '<S408>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude/Weap Angle 180/Compare To Constant1'
 */
#endif                                 /* RTW_HEADER_FMS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
