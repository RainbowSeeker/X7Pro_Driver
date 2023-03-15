/*
 * File: FMS_private.h
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

#ifndef RTW_HEADER_FMS_private_h_
#define RTW_HEADER_FMS_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "zero_crossing_types.h"
#include "FMS_types.h"
#include "FMS.h"

extern real_T rt_modd(real_T u0, real_T u1);
extern uint16_T rt_sqrt_Uu16_Yu16_Iu32_f_s(uint16_T u);
extern real32_T rt_remf(real32_T u0, real32_T u1);

/* Exported functions */
extern boolean_T FMS_emplace(Queue_FMS_Cmd *q, const FMS_Cmd *dataIn);
extern boolean_T FMS_pop(Queue_FMS_Cmd *q, Msg_FMS_Cmd *elementOut);
extern void FMS_initQueue(Queue_FMS_Cmd *q, QueuePolicy_T policy, int32_T
  capacity, Msg_FMS_Cmd *qPool);
extern void FMS_Disarm(FMS_Out_Bus *rty_FMS_Out, const ConstB_Disarm_FMS_T
  *localC);
extern void FMS_HoldControl_Init(DW_HoldControl_FMS_T *localDW);
extern void FMS_HoldControl_Reset(DW_HoldControl_FMS_T *localDW);
extern void FMS_HoldControl(real32_T rtu_FMS_In, real32_T *rty_w_cmd_mPs,
  DW_HoldControl_FMS_T *localDW);
extern void FMS_BrakeControl(real32_T *rty_psi_rate_cmd_radPs);
extern void FMS_MoveControl_Init(DW_MoveControl_FMS_T *localDW);
extern void FMS_MoveControl_Reset(DW_MoveControl_FMS_T *localDW);
extern void FMS_MoveControl(real32_T rtu_FMS_In, real32_T *rty_w_cmd_mPs, const
  ConstB_MoveControl_FMS_T *localC, DW_MoveControl_FMS_T *localDW);
extern void FMS_MotionStatus_Init(MotionState *rty_state, DW_MotionStatus_FMS_T *
  localDW);
extern void FMS_MotionStatus_Reset(MotionState *rty_state, DW_MotionStatus_FMS_T
  *localDW);
extern void FMS_MotionStatus(real32_T rtu_motion_req, real32_T rtu_speed,
  MotionState *rty_state, DW_MotionStatus_FMS_T *localDW);
extern void FMS_HoldControl_l_Init(DW_HoldControl_FMS_f_T *localDW);
extern void FMS_HoldControl_a_Reset(DW_HoldControl_FMS_f_T *localDW);
extern void FMS_HoldControl_g(real32_T rtu_FMS_In, real32_T rtu_FMS_In_g,
  real32_T rtu_FMS_In_n, real32_T rty_uv_cmd_mPs[2], const
  ConstB_HoldControl_FMS_g_T *localC, DW_HoldControl_FMS_f_T *localDW);
extern void FMS_BrakeControl_h(real32_T rty_uv_cmd_mPs[2]);
extern void FMS_MoveControl_p_Init(DW_MoveControl_FMS_f_T *localDW);
extern void FMS_MoveControl_i_Reset(DW_MoveControl_FMS_f_T *localDW);
extern void FMS_MoveControl_c(real32_T rtu_FMS_In, real32_T rtu_FMS_In_d,
  real32_T rty_uv_cmd_mPs[2], const ConstB_MoveControl_FMS_h_T *localC,
  DW_MoveControl_FMS_f_T *localDW);
extern void FMS_MotionState_Init(MotionState *rty_state, DW_MotionState_FMS_T
  *localDW);
extern void FMS_MotionState_Reset(MotionState *rty_state, DW_MotionState_FMS_T
  *localDW);
extern void FMS_MotionState(real32_T rtu_motion_req, real32_T rtu_speed,
  MotionState *rty_state, DW_MotionState_FMS_T *localDW);
extern void FMS_NearbyRefWP(const real32_T rtu_P2[2], const real32_T rtu_P3[2],
  real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_d);
extern void FMS_OutRegionRegWP(const real32_T rtu_P1[2], const real32_T rtu_P2[2],
  const real32_T rtu_P3[2], real32_T rty_P[2]);
extern void FMS_SearchL1RefWP(const real32_T rtu_P1[2], const real32_T rtu_P2[2],
  const real32_T rtu_P3[2], real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_u);
extern void FMS_HoldControl_i_Init(DW_HoldControl_FMS_m_T *localDW);
extern void FMS_HoldControl_i_Reset(DW_HoldControl_FMS_m_T *localDW);
extern void FMS_HoldControl_k(real32_T rtu_FMS_In, real32_T
  *rty_psi_rate_cmd_radPs, DW_HoldControl_FMS_m_T *localDW);
extern void FMS_MoveControl_m_Init(DW_MoveControl_FMS_c_T *localDW);
extern void FMS_MoveControl_c_Reset(DW_MoveControl_FMS_c_T *localDW);
extern void FMS_MoveControl_o(real32_T rtu_FMS_In, real32_T
  *rty_psi_rate_cmd_radPs, const ConstB_MoveControl_FMS_n_T *localC,
  DW_MoveControl_FMS_c_T *localDW);
extern void FMS_MotionState_b_Init(MotionState *rty_state,
  DW_MotionState_FMS_o_T *localDW);
extern void FMS_MotionState_i_Reset(MotionState *rty_state,
  DW_MotionState_FMS_o_T *localDW);
extern void FMS_MotionState_i(real32_T rtu_motion_req, real32_T rtu_speed,
  MotionState *rty_state, DW_MotionState_FMS_o_T *localDW);
extern void F_VehicleArmAutoMissionLLA2FLAT(const real_T rtu_lla[3], const
  real_T rtu_llo[2], real_T rtu_href, real_T rtu_psio, real32_T rty_pos[3],
  const ConstB_VehicleArmAutoMissionL_T *localC);

#endif                                 /* RTW_HEADER_FMS_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
