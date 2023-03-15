/*
 * File: FMS.h
 *
 * Code generated for Simulink model 'FMS'.
 *
 * Model version                  : 9.102
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Mar  9 21:57:53 2023
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

/* Block states (default storage) for system '<S307>/Hold Control' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S310>/Delay' */
  boolean_T icLoad;                    /* '<S310>/Delay' */
} DW_HoldControl_FMS_T;

/* Block states (default storage) for system '<S307>/Move Control' */
typedef struct {
  real32_T Integrator1_DSTATE;         /* '<S314>/Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S314>/Integrator' */
} DW_MoveControl_FMS_T;

/* Block states (default storage) for system '<S308>/Motion Status' */
typedef struct {
  uint16_T temporalCounter_i1;         /* '<S308>/Motion Status' */
  uint8_T is_c18_FMS;                  /* '<S308>/Motion Status' */
  uint8_T is_active_c18_FMS;           /* '<S308>/Motion Status' */
} DW_MotionStatus_FMS_T;

/* Block states (default storage) for system '<S317>/Hold Control' */
typedef struct {
  real32_T Delay_DSTATE[2];            /* '<S320>/Delay' */
  boolean_T icLoad;                    /* '<S320>/Delay' */
} DW_HoldControl_FMS_f_T;

/* Block states (default storage) for system '<S317>/Move Control' */
typedef struct {
  real32_T Integrator1_DSTATE[2];      /* '<S327>/Integrator1' */
  real32_T Integrator_DSTATE[2];       /* '<S327>/Integrator' */
} DW_MoveControl_FMS_f_T;

/* Block states (default storage) for system '<S318>/Motion State' */
typedef struct {
  uint16_T temporalCounter_i1;         /* '<S318>/Motion State' */
  uint8_T is_c19_FMS;                  /* '<S318>/Motion State' */
  uint8_T is_active_c19_FMS;           /* '<S318>/Motion State' */
} DW_MotionState_FMS_T;

/* Block states (default storage) for system '<S251>/Hold Control' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S254>/Delay' */
  boolean_T icLoad;                    /* '<S254>/Delay' */
} DW_HoldControl_FMS_m_T;

/* Block states (default storage) for system '<S251>/Move Control' */
typedef struct {
  real32_T Integrator1_DSTATE;         /* '<S260>/Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S260>/Integrator' */
} DW_MoveControl_FMS_c_T;

/* Block states (default storage) for system '<S252>/Motion State' */
typedef struct {
  uint8_T is_c10_FMS;                  /* '<S252>/Motion State' */
  uint8_T is_active_c10_FMS;           /* '<S252>/Motion State' */
  uint8_T temporalCounter_i1;          /* '<S252>/Motion State' */
} DW_MotionState_FMS_o_T;

/* Block signals (default storage) */
typedef struct {
  INS_Out_Bus BusConversion_InsertedFor_State;
  Commander_In_Bus Cmd_In;             /* '<Root>/State Machine' */
  real32_T Merge[2];                   /* '<S191>/Merge' */
  real32_T Merge_d;                    /* '<S178>/Merge' */
  real32_T Merge_o[2];                 /* '<S220>/Merge' */
  real32_T Merge_n;                    /* '<S208>/Merge' */
  real32_T Merge_m[2];                 /* '<S263>/Merge' */
  real32_T Merge_ob;                   /* '<S241>/Merge' */
  real32_T Merge_p;                    /* '<S251>/Merge' */
  real32_T Merge_f[2];                 /* '<S317>/Merge' */
  real32_T Merge_pd;                   /* '<S307>/Merge' */
  VehicleState state;                  /* '<Root>/State Machine' */
  PilotMode target_mode;               /* '<Root>/SafeMode' */
  uint8_T wp_consume;                  /* '<Root>/State Machine' */
  uint8_T wp_index;                    /* '<Root>/State Machine' */
  boolean_T LogicalOperator1;          /* '<S2>/Logical Operator1' */
  boolean_T LogicalOperator;           /* '<S1>/Logical Operator' */
} B_FMS_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T llo[2];                       /* '<Root>/State Machine' */
  Msg_FMS_Cmd Msg[11];                 /* '<Root>/State Machine' */
  Queue_FMS_Cmd Queue;                 /* '<Root>/State Machine' */
  void* M_msgInterface;                /* '<Root>/State Machine' */
  void* M_msgHandle;                   /* '<Root>/State Machine' */
  void* M_msgDataPtr;                  /* '<Root>/State Machine' */
  real32_T DiscreteTimeIntegrator5_DSTATE[3];/* '<S12>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator5_DSTAT_j;/* '<S13>/Discrete-Time Integrator5' */
  real32_T Delay_DSTATE[2];            /* '<S64>/Delay' */
  real32_T l1_heading;                 /* '<S83>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_p[2];          /* '<S303>/Delay' */
  real32_T l1_heading_a;               /* '<S344>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_d[2];          /* '<S283>/Delay' */
  real32_T Delay_DSTATE_do;            /* '<S284>/Delay' */
  real32_T Integrator1_DSTATE;         /* '<S287>/Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S287>/Integrator' */
  uint32_T DelayInput1_DSTATE;         /* '<S25>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator1_DSTATE;/* '<S21>/Discrete-Time Integrator1' */
  uint32_T DelayInput1_DSTATE_f;       /* '<S30>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_i;       /* '<S26>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_p;       /* '<S27>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_c;       /* '<S8>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  uint32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S364>/Discrete-Time Integrator' */
  PilotMode Delay_DSTATE_c;            /* '<S23>/Delay' */
  real32_T home[3];                    /* '<Root>/State Machine' */
  int32_T durationCounter_1;           /* '<Root>/State Machine' */
  int32_T durationCounter_1_o;         /* '<Root>/State Machine' */
  int32_T durationCounter_1_f;         /* '<Root>/State Machine' */
  int32_T durationCounter_1_i;         /* '<Root>/State Machine' */
  int32_T durationCounter_2;           /* '<Root>/State Machine' */
  int32_T M_qId;                       /* '<Root>/State Machine' */
  uint32_T mission_timestamp_prev;     /* '<Root>/State Machine' */
  uint32_T mission_timestamp_start;    /* '<Root>/State Machine' */
  FMS_Cmd M;                           /* '<Root>/State Machine' */
  FMS_Cmd save_cmd;                    /* '<Root>/State Machine' */
  FMS_Cmd cmd_start;                   /* '<Root>/State Machine' */
  FMS_Cmd M_msgData;                   /* '<Root>/State Machine' */
  FMS_Cmd M_msgReservedData;           /* '<Root>/State Machine' */
  PilotMode mode_start;                /* '<Root>/State Machine' */
  uint16_T nav_cmd;                    /* '<Root>/State Machine' */
  uint16_T temporalCounter_i1;         /* '<Root>/State Machine' */
  uint16_T temporalCounter_i1_h;       /* '<S192>/Motion State' */
  uint8_T Delay_DSTATE_o;              /* '<S9>/Delay' */
  uint8_T DelayInput1_DSTATE_pe;       /* '<S46>/Delay Input1' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S31>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_b; /* '<S33>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_l; /* '<S191>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_j; /* '<S178>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_p; /* '<S220>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_bn;/* '<S208>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_i; /* '<S37>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_o; /* '<S41>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_g; /* '<S263>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_d; /* '<S241>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_bi;/* '<S251>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_c; /* '<S317>/Switch Case' */
  int8_T SwitchCase_ActiveSubsystem_i5;/* '<S307>/Switch Case' */
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
  uint8_T is_c16_FMS;                  /* '<S192>/Motion State' */
  uint8_T is_active_c16_FMS;           /* '<S192>/Motion State' */
  uint8_T is_c21_FMS;                  /* '<S179>/Motion State' */
  uint8_T is_active_c21_FMS;           /* '<S179>/Motion State' */
  uint8_T temporalCounter_i1_b;        /* '<S179>/Motion State' */
  uint8_T Integrator1_IC_LOADING;      /* '<S287>/Integrator1' */
  boolean_T valid_cmd;                 /* '<Root>/State Machine' */
  boolean_T bl;                        /* '<Root>/State Machine' */
  boolean_T br;                        /* '<Root>/State Machine' */
  boolean_T M_isValid;                 /* '<Root>/State Machine' */
  boolean_T icLoad;                    /* '<S64>/Delay' */
  boolean_T icLoad_h;                  /* '<S303>/Delay' */
  boolean_T icLoad_j;                  /* '<S283>/Delay' */
  boolean_T icLoad_c;                  /* '<S284>/Delay' */
  DW_MoveControl_FMS_f_T MoveControl_k;/* '<S191>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_a;/* '<S191>/Hold Control' */
  DW_MoveControl_FMS_c_T MoveControl_m;/* '<S178>/Move Control' */
  DW_HoldControl_FMS_m_T HoldControl_e;/* '<S178>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState_g;/* '<S221>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_i;/* '<S220>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_f;/* '<S220>/Hold Control' */
  DW_MotionState_FMS_o_T sf_MotionState_d;/* '<S209>/Motion State' */
  DW_MoveControl_FMS_c_T MoveControl_b;/* '<S208>/Move Control' */
  DW_HoldControl_FMS_m_T HoldControl_kq;/* '<S208>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState_l;/* '<S264>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_h;/* '<S263>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_h;/* '<S263>/Hold Control' */
  DW_MotionState_FMS_o_T sf_MotionState_i;/* '<S252>/Motion State' */
  DW_MoveControl_FMS_c_T MoveControl_o;/* '<S251>/Move Control' */
  DW_HoldControl_FMS_m_T HoldControl_k;/* '<S251>/Hold Control' */
  DW_MotionStatus_FMS_T sf_MotionStatus_d;/* '<S242>/Motion Status' */
  DW_MoveControl_FMS_T MoveControl_g;  /* '<S241>/Move Control' */
  DW_HoldControl_FMS_T HoldControl_b;  /* '<S241>/Hold Control' */
  DW_MotionState_FMS_T sf_MotionState; /* '<S318>/Motion State' */
  DW_MoveControl_FMS_f_T MoveControl_c;/* '<S317>/Move Control' */
  DW_HoldControl_FMS_f_T HoldControl_g;/* '<S317>/Hold Control' */
  DW_MotionStatus_FMS_T sf_MotionStatus;/* '<S308>/Motion Status' */
  DW_MoveControl_FMS_T MoveControl;    /* '<S307>/Move Control' */
  DW_HoldControl_FMS_T HoldControl;    /* '<S307>/Hold Control' */
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

/* Invariant block signals for system '<S307>/Move Control' */
typedef struct {
  const real32_T Gain4;                /* '<S315>/Gain4' */
  const real32_T Square;               /* '<S315>/Square' */
  const real32_T d;                    /* '<S315>/Multiply' */
} ConstB_MoveControl_FMS_T;

/* Invariant block signals for system '<S317>/Hold Control' */
typedef struct {
  const real32_T VectorConcatenate3[3];/* '<S324>/Vector Concatenate3' */
} ConstB_HoldControl_FMS_g_T;

/* Invariant block signals for system '<S317>/Move Control' */
typedef struct {
  const real32_T Gain4;                /* '<S328>/Gain4' */
  const real32_T Square;               /* '<S328>/Square' */
  const real32_T d;                    /* '<S328>/Multiply' */
} ConstB_MoveControl_FMS_h_T;

/* Invariant block signals for system '<S251>/Move Control' */
typedef struct {
  const real32_T Gain4;                /* '<S261>/Gain4' */
  const real32_T Square;               /* '<S261>/Square' */
  const real32_T d;                    /* '<S261>/Multiply' */
} ConstB_MoveControl_FMS_n_T;

/* Invariant block signals for system '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
typedef struct {
  const real_T Sum;                    /* '<S367>/Sum' */
  const real_T ff;                     /* '<S367>/Multiply3' */
  const real_T Sum4;                   /* '<S367>/Sum4' */
} ConstB_VehicleArmAutoMissionL_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T TmpSignalConversionAtMathFu[2];
  const real32_T MathFunction[2];      /* '<S58>/Math Function' */
  const real32_T SumofElements;        /* '<S58>/Sum of Elements' */
  const real32_T MathFunction1;        /* '<S58>/Math Function1' */
  const real32_T Product[2];           /* '<S58>/Product' */
  const real32_T Switch[3];            /* '<S58>/Switch' */
  const real32_T Divide[2];            /* '<S58>/Divide' */
  const real32_T VectorConcatenate3[3];/* '<S86>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_e[3];/* '<S97>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_o[3];/* '<S99>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_n[3];/* '<S159>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_i[3];/* '<S162>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_ny[3];/* '<S165>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_e0[3];/* '<S166>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_l[3];/* '<S173>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_iz[3];/* '<S175>/Vector Concatenate3' */
  const real32_T Gain4;                /* '<S293>/Gain4' */
  const real32_T Square;               /* '<S293>/Square' */
  const real32_T d;                    /* '<S293>/Multiply' */
  const real32_T TmpSignalConversionAtMath_f[2];
  const real32_T MathFunction_g[2];    /* '<S297>/Math Function' */
  const real32_T SumofElements_o;      /* '<S297>/Sum of Elements' */
  const real32_T MathFunction1_n;      /* '<S297>/Math Function1' */
  const real32_T Product_i[2];         /* '<S297>/Product' */
  const real32_T Switch_p[3];          /* '<S297>/Switch' */
  const real32_T Divide_o[2];          /* '<S297>/Divide' */
  const real32_T VectorConcatenate3_p[3];/* '<S347>/Vector Concatenate3' */
  const real32_T VectorConcatenate3_n5[3];/* '<S280>/Vector Concatenate3' */
  const real32_T TmpSignalConversionAtMath_m[2];
  const real32_T MathFunction_l[2];    /* '<S358>/Math Function' */
  const real32_T SumofElements_g;      /* '<S358>/Sum of Elements' */
  const real32_T MathFunction1_j;      /* '<S358>/Math Function1' */
  const real32_T Product_h[2];         /* '<S358>/Product' */
  const real32_T Switch_f[3];          /* '<S358>/Switch' */
  const real32_T Divide_j[2];          /* '<S358>/Divide' */
  const real32_T VectorConcatenate3_pk[3];/* '<S363>/Vector Concatenate3' */
  const uint8_T DataTypeConversion;    /* '<S38>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S38>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_b;  /* '<S39>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_o; /* '<S39>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S39>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_g;  /* '<S40>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_i; /* '<S40>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_j; /* '<S40>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_ga; /* '<S45>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_b; /* '<S45>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_l;  /* '<S47>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_bp;/* '<S47>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_b; /* '<S47>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_a;  /* '<S44>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_n; /* '<S44>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_k; /* '<S44>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_c;  /* '<S233>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_c; /* '<S233>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_l; /* '<S233>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_k;  /* '<S235>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_h; /* '<S235>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_m; /* '<S235>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_p;  /* '<S234>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_iv;/* '<S234>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_bf;/* '<S234>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_ge; /* '<S236>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_cc;/* '<S236>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_b0;/* '<S236>/Data Type Conversion2' */
  const uint8_T DataTypeConversion1_f; /* '<S36>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_h; /* '<S36>/Data Type Conversion2' */
  ConstB_VehicleArmAutoMissionL_T VehicleArmAutoMissionLLA2FLAT;
                                  /* '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
  ConstB_Disarm_FMS_T Unknown;         /* '<S33>/Unknown' */
  ConstB_MoveControl_FMS_h_T MoveControl_k;/* '<S191>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_a;/* '<S191>/Hold Control' */
  ConstB_MoveControl_FMS_n_T MoveControl_m;/* '<S178>/Move Control' */
  ConstB_MoveControl_FMS_h_T MoveControl_i;/* '<S220>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_f;/* '<S220>/Hold Control' */
  ConstB_MoveControl_FMS_n_T MoveControl_b;/* '<S208>/Move Control' */
  ConstB_Disarm_FMS_T Unknown_m;       /* '<S41>/Unknown' */
  ConstB_MoveControl_FMS_h_T MoveControl_h;/* '<S263>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_h;/* '<S263>/Hold Control' */
  ConstB_MoveControl_FMS_n_T MoveControl_o;/* '<S251>/Move Control' */
  ConstB_MoveControl_FMS_T MoveControl_g;/* '<S241>/Move Control' */
  ConstB_MoveControl_FMS_h_T MoveControl_c;/* '<S317>/Move Control' */
  ConstB_HoldControl_FMS_g_T HoldControl_g;/* '<S317>/Hold Control' */
  ConstB_MoveControl_FMS_T MoveControl;/* '<S307>/Move Control' */
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
                                                *   '<S235>/L1'
                                                *   '<S47>/L1'
                                                *   '<S89>/Saturation'
                                                *   '<S90>/Saturation1'
                                                *   '<S90>/Saturation2'
                                                *   '<S90>/Saturation3'
                                                *   '<S178>/Saturation'
                                                *   '<S191>/Saturation1'
                                                *   '<S208>/Saturation'
                                                *   '<S220>/Saturation1'
                                                *   '<S276>/Saturation1'
                                                *   '<S349>/Gain2'
                                                *   '<S349>/Saturation1'
                                                *   '<S143>/Gain2'
                                                *   '<S150>/Gain1'
                                                *   '<S150>/Gain2'
                                                *   '<S181>/Gain2'
                                                *   '<S182>/Gain1'
                                                *   '<S189>/Constant'
                                                *   '<S194>/Gain2'
                                                *   '<S195>/Gain6'
                                                *   '<S203>/Constant'
                                                *   '<S204>/Constant'
                                                *   '<S211>/Gain2'
                                                *   '<S212>/Gain1'
                                                *   '<S223>/Gain2'
                                                *   '<S224>/Gain6'
                                                *   '<S241>/Saturation1'
                                                *   '<S251>/Saturation'
                                                *   '<S263>/Saturation1'
                                                *   '<S277>/Gain2'
                                                *   '<S299>/vel'
                                                *   '<S299>/Saturation'
                                                *   '<S299>/Switch'
                                                *   '<S60>/Gain'
                                                *   '<S60>/Saturation1'
                                                *   '<S61>/vel'
                                                *   '<S61>/Saturation'
                                                *   '<S61>/Switch'
                                                *   '<S186>/Dead Zone'
                                                *   '<S186>/Gain'
                                                *   '<S199>/Dead Zone'
                                                *   '<S199>/Gain'
                                                *   '<S200>/Dead Zone'
                                                *   '<S200>/Gain'
                                                *   '<S216>/Dead Zone'
                                                *   '<S216>/Gain'
                                                *   '<S228>/Dead Zone'
                                                *   '<S228>/Gain'
                                                *   '<S229>/Dead Zone'
                                                *   '<S229>/Gain'
                                                *   '<S244>/Gain2'
                                                *   '<S245>/Gain1'
                                                *   '<S254>/Gain2'
                                                *   '<S255>/Gain1'
                                                *   '<S266>/Gain2'
                                                *   '<S267>/Gain6'
                                                *   '<S286>/Gain2'
                                                *   '<S286>/Saturation'
                                                *   '<S287>/Integrator'
                                                *   '<S353>/Gain2'
                                                *   '<S353>/Saturation'
                                                *   '<S53>/Gain2'
                                                *   '<S53>/Saturation'
                                                *   '<S247>/Dead Zone'
                                                *   '<S247>/Gain'
                                                *   '<S259>/Dead Zone'
                                                *   '<S259>/Gain'
                                                *   '<S271>/Dead Zone'
                                                *   '<S271>/Gain'
                                                *   '<S272>/Dead Zone'
                                                *   '<S272>/Gain'
                                                *   '<S307>/Saturation1'
                                                *   '<S317>/Saturation1'
                                                *   '<S310>/Gain2'
                                                *   '<S311>/Gain1'
                                                *   '<S320>/Gain2'
                                                *   '<S321>/Gain6'
                                                *   '<S313>/Dead Zone'
                                                *   '<S313>/Gain'
                                                *   '<S325>/Dead Zone'
                                                *   '<S325>/Gain'
                                                *   '<S326>/Dead Zone'
                                                *   '<S326>/Gain'
                                                */
extern struct_TYt7YeNdxIDXfczXumtXXB FMS_EXPORT;/* Variable: FMS_EXPORT
                                                 * Referenced by:
                                                 *   '<S1>/Constant'
                                                 *   '<S21>/Constant1'
                                                 *   '<S364>/Constant'
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
 * Block '<S58>/Data Type Duplicate' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S80>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S77>/Data Type Duplicate' : Unused code path elimination
 * Block '<S78>/Data Type Duplicate' : Unused code path elimination
 * Block '<S84>/Data Type Duplicate' : Unused code path elimination
 * Block '<S297>/Data Type Duplicate' : Unused code path elimination
 * Block '<S298>/Data Type Duplicate' : Unused code path elimination
 * Block '<S341>/Data Type Duplicate' : Unused code path elimination
 * Block '<S342>/Data Type Duplicate' : Unused code path elimination
 * Block '<S338>/Data Type Duplicate' : Unused code path elimination
 * Block '<S339>/Data Type Duplicate' : Unused code path elimination
 * Block '<S345>/Data Type Duplicate' : Unused code path elimination
 * Block '<S358>/Data Type Duplicate' : Unused code path elimination
 * Block '<S359>/Data Type Duplicate' : Unused code path elimination
 * Block '<S350>/Reshape1' : Unused code path elimination
 * Block '<S12>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S62>/Reshape' : Reshape block reduction
 * Block '<S50>/Reshape' : Reshape block reduction
 * Block '<S50>/Reshape1' : Reshape block reduction
 * Block '<S301>/Reshape' : Reshape block reduction
 * Block '<S283>/Reshape' : Reshape block reduction
 * Block '<S283>/Reshape1' : Reshape block reduction
 * Block '<S350>/Reshape' : Reshape block reduction
 * Block '<S364>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S32>/Signal Copy3' : Eliminate redundant signal conversion block
 * Block '<S32>/Signal Copy4' : Eliminate redundant signal conversion block
 * Block '<S32>/Signal Copy5' : Eliminate redundant signal conversion block
 * Block '<S32>/Signal Copy6' : Eliminate redundant signal conversion block
 * Block '<S365>/Signal Conversion' : Eliminate redundant signal conversion block
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
 * '<S54>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control/Bus_Selection'
 * '<S55>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control/psi_saturation'
 * '<S56>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Heading Control/Heading Control/psi_saturation/Compare To Constant'
 * '<S57>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle/2D Cross Product'
 * '<S58>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle/Vector Normalize'
 * '<S59>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Heading Commander/Included Angle/Vector Normalize1'
 * '<S60>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control'
 * '<S61>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Cruise Speed '
 * '<S62>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP'
 * '<S63>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration'
 * '<S64>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed'
 * '<S65>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control/Target Height'
 * '<S66>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control/Target Height/Vector Modulus'
 * '<S67>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Altitude Control/Target Height/Vector Modulus1'
 * '<S68>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Cruise Speed /Vector Modulus'
 * '<S69>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/Compare To Constant'
 * '<S70>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/Compare To Constant1'
 * '<S71>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/NearbyRefWP'
 * '<S72>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/OutRegionRegWP'
 * '<S73>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/L1 Reference WP/SearchL1RefWP'
 * '<S74>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle'
 * '<S75>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Modulus'
 * '<S76>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Modulus1'
 * '<S77>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Normalize'
 * '<S78>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Vector Normalize1'
 * '<S79>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle/2D Cross Product'
 * '<S80>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize'
 * '<S81>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize1'
 * '<S82>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Ground Speed'
 * '<S83>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix'
 * '<S84>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Ground Speed/Vector Normalize2'
 * '<S85>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM'
 * '<S86>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Mission/Mission_SubSystem/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM/Rotation Matrix Z'
 * '<S87>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command'
 * '<S88>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask'
 * '<S89>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command'
 * '<S90>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command'
 * '<S91>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Body_Frame'
 * '<S92>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Command_Mask'
 * '<S93>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Global_Frame'
 * '<S94>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Local_Frame'
 * '<S95>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Command_Mask/Compare To Zero2'
 * '<S96>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Global_Frame/Psi To DCM'
 * '<S97>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Global_Frame/Psi To DCM/Rotation Matrix Z'
 * '<S98>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Local_Frame/Psi To DCM2'
 * '<S99>'  : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Acc_Command/Local_Frame/Psi To DCM2/Rotation Matrix Z'
 * '<S100>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero'
 * '<S101>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero1'
 * '<S102>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero12'
 * '<S103>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero2'
 * '<S104>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero3'
 * '<S105>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero4'
 * '<S106>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Compare To Zero5'
 * '<S107>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem'
 * '<S108>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1'
 * '<S109>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ax_cmd_valid'
 * '<S110>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ay_cmd_valid'
 * '<S111>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/az_cmd_valid'
 * '<S112>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/p_cmd_valid'
 * '<S113>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/phi_cmd_valid'
 * '<S114>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/psi_rate_cmd_valid'
 * '<S115>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/q_cmd_valid'
 * '<S116>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/r_cmd_valid'
 * '<S117>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/theta_cmd_valid'
 * '<S118>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/throttle_cmd_valid'
 * '<S119>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/u_cmd_valid'
 * '<S120>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/v_cmd_valid'
 * '<S121>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/w_cmd_valid'
 * '<S122>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Constant'
 * '<S123>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Zero6'
 * '<S124>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Zero7'
 * '<S125>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem/Compare To Zero8'
 * '<S126>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Constant'
 * '<S127>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Zero10'
 * '<S128>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Zero11'
 * '<S129>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/Subsystem1/Compare To Zero9'
 * '<S130>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ax_cmd_valid/bit_shift'
 * '<S131>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/ay_cmd_valid/bit_shift'
 * '<S132>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/az_cmd_valid/bit_shift'
 * '<S133>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/p_cmd_valid/bit_shift'
 * '<S134>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/phi_cmd_valid/bit_shift'
 * '<S135>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/psi_rate_cmd_valid/bit_shift'
 * '<S136>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/q_cmd_valid/bit_shift'
 * '<S137>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/r_cmd_valid/bit_shift'
 * '<S138>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/theta_cmd_valid/bit_shift'
 * '<S139>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/throttle_cmd_valid/bit_shift'
 * '<S140>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/u_cmd_valid/bit_shift'
 * '<S141>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/v_cmd_valid/bit_shift'
 * '<S142>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Command_Mask/w_cmd_valid/bit_shift'
 * '<S143>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control'
 * '<S144>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Psi_Rate_Command'
 * '<S145>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Compare To Zero'
 * '<S146>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Error'
 * '<S147>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Error/psi_err_saturation'
 * '<S148>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Heading_Control/Error/psi_err_saturation/Compare To Constant'
 * '<S149>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Heading_Command/Psi_Rate_Command/Compare To Zero1'
 * '<S150>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control'
 * '<S151>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command'
 * '<S152>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Body_Error'
 * '<S153>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Bus_Select1'
 * '<S154>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Bus_Select2'
 * '<S155>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Command_Mask'
 * '<S156>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Global_Error'
 * '<S157>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error'
 * '<S158>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Body_Error/Psi To DCM1'
 * '<S159>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Body_Error/Psi To DCM1/Rotation Matrix Z'
 * '<S160>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Command_Mask/Compare To Zero'
 * '<S161>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Global_Error/Psi To DCM'
 * '<S162>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Global_Error/Psi To DCM/Rotation Matrix Z'
 * '<S163>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM1'
 * '<S164>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM2'
 * '<S165>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM1/Rotation Matrix Z'
 * '<S166>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Position_Control/Local_Error/Psi To DCM2/Rotation Matrix Z'
 * '<S167>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Body_Frame'
 * '<S168>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Command_Mask'
 * '<S169>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Global_Frame'
 * '<S170>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Local_Frame'
 * '<S171>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Command_Mask/Compare To Zero2'
 * '<S172>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Global_Frame/Psi To DCM'
 * '<S173>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Global_Frame/Psi To DCM/Rotation Matrix Z'
 * '<S174>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Local_Frame/Psi To DCM2'
 * '<S175>' : 'FMS/FMS Commander/Commander/Arm/Auto/Offboard/Velocity_Command/Velocity_Command/Local_Frame/Psi To DCM2/Rotation Matrix Z'
 * '<S176>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command'
 * '<S177>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command'
 * '<S178>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller'
 * '<S179>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Detect Movement'
 * '<S180>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Brake Control'
 * '<S181>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control'
 * '<S182>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control'
 * '<S183>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control/Bus_Selection'
 * '<S184>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control/psi_err_saturation'
 * '<S185>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Hold Control/psi_err_saturation/Compare To Constant'
 * '<S186>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control/DeadZone'
 * '<S187>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control/TD'
 * '<S188>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Controller/Move Control/TD/fhan '
 * '<S189>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Detect Movement/Compare To Constant'
 * '<S190>' : 'FMS/FMS Commander/Commander/Arm/Position/Heading Command/Detect Movement/Motion State'
 * '<S191>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller'
 * '<S192>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement'
 * '<S193>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Brake Control'
 * '<S194>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control'
 * '<S195>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control'
 * '<S196>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control/Bus_Selection'
 * '<S197>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control/Psi To DCM'
 * '<S198>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S199>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/DeadZone'
 * '<S200>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/DeadZone1'
 * '<S201>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/TD'
 * '<S202>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Controller/Move Control/TD/fhan '
 * '<S203>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement/Compare To Constant'
 * '<S204>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement/Compare To Constant1'
 * '<S205>' : 'FMS/FMS Commander/Commander/Arm/Position/Position Command/Detect Movement/Motion State'
 * '<S206>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold'
 * '<S207>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold'
 * '<S208>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller'
 * '<S209>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Detect Movement'
 * '<S210>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Brake Control'
 * '<S211>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control'
 * '<S212>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control'
 * '<S213>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control/Bus_Selection'
 * '<S214>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control/psi_err_saturation'
 * '<S215>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Hold Control/psi_err_saturation/Compare To Constant'
 * '<S216>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control/DeadZone'
 * '<S217>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control/TD'
 * '<S218>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Controller/Move Control/TD/fhan '
 * '<S219>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Heading Hold/Detect Movement/Motion State'
 * '<S220>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller'
 * '<S221>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Detect Movement'
 * '<S222>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Brake Control'
 * '<S223>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control'
 * '<S224>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control'
 * '<S225>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S226>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S227>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S228>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/DeadZone'
 * '<S229>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/DeadZone1'
 * '<S230>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/TD'
 * '<S231>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Controller/Move Control/TD/fhan '
 * '<S232>' : 'FMS/FMS Commander/Commander/Arm/Stabilize/Position Hold/Detect Movement/Motion State'
 * '<S233>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold'
 * '<S234>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land'
 * '<S235>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return'
 * '<S236>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff'
 * '<S237>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Unknown'
 * '<S238>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold'
 * '<S239>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold'
 * '<S240>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold'
 * '<S241>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller'
 * '<S242>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Detect Movement'
 * '<S243>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Brake Control'
 * '<S244>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Hold Control'
 * '<S245>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control'
 * '<S246>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Hold Control/Bus_Selection'
 * '<S247>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control/DeadZone'
 * '<S248>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control/TD1'
 * '<S249>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Controller/Move Control/TD1/fhan '
 * '<S250>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Altitude Hold/Detect Movement/Motion Status'
 * '<S251>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller'
 * '<S252>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Detect Movement'
 * '<S253>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Brake Control'
 * '<S254>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control'
 * '<S255>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control'
 * '<S256>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control/Bus_Selection'
 * '<S257>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control/psi_err_saturation'
 * '<S258>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Hold Control/psi_err_saturation/Compare To Constant'
 * '<S259>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control/DeadZone'
 * '<S260>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control/TD'
 * '<S261>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Controller/Move Control/TD/fhan '
 * '<S262>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Heading Hold/Detect Movement/Motion State'
 * '<S263>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller'
 * '<S264>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Detect Movement'
 * '<S265>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Brake Control'
 * '<S266>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control'
 * '<S267>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control'
 * '<S268>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S269>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S270>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S271>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/DeadZone'
 * '<S272>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/DeadZone1'
 * '<S273>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/TD'
 * '<S274>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Controller/Move Control/TD/fhan '
 * '<S275>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Hold/Position Hold/Detect Movement/Motion State'
 * '<S276>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command'
 * '<S277>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control'
 * '<S278>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control/Bus_Selection'
 * '<S279>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control/Psi To DCM'
 * '<S280>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Land/Position Command/Position Control/Psi To DCM/Rotation Matrix Z'
 * '<S281>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander'
 * '<S282>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander'
 * '<S283>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Way Points'
 * '<S284>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control'
 * '<S285>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle'
 * '<S286>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control'
 * '<S287>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/TD'
 * '<S288>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation'
 * '<S289>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation1'
 * '<S290>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control/Bus_Selection'
 * '<S291>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control/psi_saturation'
 * '<S292>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/Heading Control/psi_saturation/Compare To Constant'
 * '<S293>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/TD/fhan '
 * '<S294>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation/Compare To Constant'
 * '<S295>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Heading Control/psi_saturation1/Compare To Constant'
 * '<S296>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle/2D Cross Product'
 * '<S297>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle/Vector Normalize'
 * '<S298>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Heading Commander/Included Angle/Vector Normalize1'
 * '<S299>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Cruise Speed '
 * '<S300>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position'
 * '<S301>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP'
 * '<S302>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration'
 * '<S303>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed'
 * '<S304>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Cruise Speed /Vector Modulus'
 * '<S305>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold'
 * '<S306>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold'
 * '<S307>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller'
 * '<S308>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Detect Movement'
 * '<S309>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Brake Control'
 * '<S310>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Hold Control'
 * '<S311>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control'
 * '<S312>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Hold Control/Bus_Selection'
 * '<S313>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/DeadZone'
 * '<S314>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/TD1'
 * '<S315>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Controller/Move Control/TD1/fhan '
 * '<S316>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Altitude Hold/Detect Movement/Motion Status'
 * '<S317>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller'
 * '<S318>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Detect Movement'
 * '<S319>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Brake Control'
 * '<S320>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control'
 * '<S321>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control'
 * '<S322>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Bus_Selection'
 * '<S323>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Psi To DCM'
 * '<S324>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Hold Control/Psi To DCM/Rotation Matrix Z'
 * '<S325>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/DeadZone'
 * '<S326>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/DeadZone1'
 * '<S327>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/TD'
 * '<S328>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Controller/Move Control/TD/fhan '
 * '<S329>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Hold Position/Position Hold/Detect Movement/Motion State'
 * '<S330>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/Compare To Constant'
 * '<S331>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/Compare To Constant1'
 * '<S332>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/NearbyRefWP'
 * '<S333>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/OutRegionRegWP'
 * '<S334>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/L1 Reference WP/SearchL1RefWP'
 * '<S335>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle'
 * '<S336>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Modulus'
 * '<S337>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Modulus1'
 * '<S338>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Normalize'
 * '<S339>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Vector Normalize1'
 * '<S340>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle/2D Cross Product'
 * '<S341>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize'
 * '<S342>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration/Included Angle/Vector Normalize1'
 * '<S343>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Ground Speed'
 * '<S344>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix'
 * '<S345>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Ground Speed/Vector Normalize2'
 * '<S346>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM'
 * '<S347>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Return/Velocity Commander/Lateral Acceleration To Speed/Rotation Matrix/Psi To DCM/Rotation Matrix Z'
 * '<S348>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander'
 * '<S349>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position'
 * '<S350>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Way Points'
 * '<S351>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Heading Control'
 * '<S352>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Included Angle'
 * '<S353>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Heading Control/Heading Control'
 * '<S354>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Heading Control/Heading Control/Bus_Selection'
 * '<S355>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Heading Control/Heading Control/psi_saturation'
 * '<S356>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Heading Control/Heading Control/psi_saturation/Compare To Constant'
 * '<S357>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Included Angle/2D Cross Product'
 * '<S358>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Included Angle/Vector Normalize'
 * '<S359>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Heading Commander/Included Angle/Vector Normalize1'
 * '<S360>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Bus_Selection'
 * '<S361>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Psi To DCM'
 * '<S362>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Target Position'
 * '<S363>' : 'FMS/FMS Commander/Commander/Arm/SubMode/Takeoff/Track Position/Psi To DCM/Rotation Matrix Z'
 * '<S364>' : 'FMS/FMS Commander/Commander/Bus_Constructor/timestamp'
 * '<S365>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT'
 * '<S366>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT'
 * '<S367>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LAT2FLAT Curve'
 * '<S368>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap'
 * '<S369>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/Rotation'
 * '<S370>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Weap Angle 180'
 * '<S371>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude'
 * '<S372>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Weap Angle 180/Compare To Constant1'
 * '<S373>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude/Compare To Constant1'
 * '<S374>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude/Weap Angle 180'
 * '<S375>' : 'FMS/State Machine/Vehicle.Arm.Auto.Mission.LLA2FLAT/LLA2FLAT/LatLon Wrap/Wrap Latitude/Weap Angle 180/Compare To Constant1'
 */
#endif                                 /* RTW_HEADER_FMS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
