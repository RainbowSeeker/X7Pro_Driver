/*
 * File: FMS.c
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

#include "FMS.h"
#include "FMS_types.h"
#include "rtwtypes.h"
#include "FMS_private.h"
#include <string.h>
#include <math.h>
#include "arm_math.h"
#include <float.h>
#include <stddef.h>
#include "zero_crossing_types.h"

/* Named constants for Chart: '<S308>/Motion Status' */
#define FMS_IN_Brake                   ((uint8_T)1U)
#define FMS_IN_Hold                    ((uint8_T)2U)
#define FMS_IN_Move                    ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)

/* Named constants for Chart: '<S318>/Motion State' */
#define FMS_IN_Brake_k                 ((uint8_T)1U)
#define FMS_IN_Hold_e                  ((uint8_T)2U)
#define FMS_IN_Move_h                  ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD_j       ((uint8_T)0U)

/* Named constants for Chart: '<S252>/Motion State' */
#define FMS_IN_Brake_l                 ((uint8_T)1U)
#define FMS_IN_Hold_i                  ((uint8_T)2U)
#define FMS_IN_Move_f                  ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD_m       ((uint8_T)0U)

/* Named constants for Chart: '<S179>/Motion State' */
#define FMS_IN_Brake_b                 ((uint8_T)1U)
#define FMS_IN_Hold_g                  ((uint8_T)2U)
#define FMS_IN_Move_g                  ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD_d       ((uint8_T)0U)

/* Named constants for Chart: '<Root>/SafeMode' */
#define FMS_IN_Manual                  ((uint8_T)1U)
#define FMS_IN_Mission                 ((uint8_T)2U)
#define FMS_IN_Offboard                ((uint8_T)3U)
#define FMS_IN_Other                   ((uint8_T)4U)
#define FMS_IN_Position                ((uint8_T)5U)
#define FMS_IN_Stabilize               ((uint8_T)6U)

/* Named constants for Chart: '<Root>/State Machine' */
#define FMS_IN_Arm                     ((uint8_T)1U)
#define FMS_IN_Auto                    ((uint8_T)1U)
#define FMS_IN_Check                   ((uint8_T)1U)
#define FMS_IN_Disarm                  ((uint8_T)2U)
#define FMS_IN_Disarming               ((uint8_T)1U)
#define FMS_IN_Idle                    ((uint8_T)3U)
#define FMS_IN_InvalidMode             ((uint8_T)2U)
#define FMS_IN_Land                    ((uint8_T)2U)
#define FMS_IN_Listen                  ((uint8_T)2U)
#define FMS_IN_Loiter                  ((uint8_T)1U)
#define FMS_IN_Loiter_b                ((uint8_T)3U)
#define FMS_IN_Manual_k                ((uint8_T)3U)
#define FMS_IN_Mission_a               ((uint8_T)1U)
#define FMS_IN_NextWP                  ((uint8_T)4U)
#define FMS_IN_Offboard_l              ((uint8_T)2U)
#define FMS_IN_Position_m              ((uint8_T)4U)
#define FMS_IN_Return                  ((uint8_T)5U)
#define FMS_IN_Run                     ((uint8_T)2U)
#define FMS_IN_Send                    ((uint8_T)3U)
#define FMS_IN_Standby                 ((uint8_T)3U)
#define FMS_IN_Takeoff                 ((uint8_T)6U)
#define FMS_IN_Waypoint                ((uint8_T)7U)
#define FMS_event_DisarmEvent          (0)

/* Exported block parameters */
struct_z8TbXuqo9JNiexfZo6b1iC FMS_PARAM = {
  0.15F,
  0.15F,
  0.1F,
  0.1F,
  0.95F,
  1.0F,
  5.0F,
  2.5F,
  2.5F,
  1.04719758F,
  0.52359879F,
  10.0F,
  5.0F,
  1.5F,
  0.5F
} ;                                    /* Variable: FMS_PARAM
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

struct_TYt7YeNdxIDXfczXumtXXB FMS_EXPORT = {
  4U,

  { 66, 97, 115, 101, 32, 70, 77, 83, 32, 118, 48, 46, 52, 46, 48, 0 }
} ;                                    /* Variable: FMS_EXPORT
                                        * Referenced by:
                                        *   '<S1>/Constant'
                                        *   '<S21>/Constant1'
                                        *   '<S364>/Constant'
                                        */

/* Block signals (default storage) */
B_FMS_T FMS_B;

/* Block states (default storage) */
DW_FMS_T FMS_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_FMS_T FMS_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_FMS_T FMS_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FMS_T FMS_Y;

/* Real-time model */
static RT_MODEL_FMS_T FMS_M_;
RT_MODEL_FMS_T *const FMS_M = &FMS_M_;

/* Forward declaration for local functions */
static void FMS_sf_msg_send_M(void);
static boolean_T FMS_CheckCmdValid(FMS_Cmd cmd_in, PilotMode mode_in, uint32_T
  ins_flag);
static boolean_T FMS_BottomRight(real32_T pilot_cmd_stick_yaw, real32_T
  pilot_cmd_stick_throttle);
static boolean_T FMS_BottomLeft(real32_T pilot_cmd_stick_yaw, real32_T
  pilot_cmd_stick_throttle);
static boolean_T FMS_sf_msg_pop_M(void);
static void FMS_exit_internal_Auto(void);
static void FMS_Auto(void);
static void FMS_enter_internal_Arm(void);
static void FMS_Arm(const PilotMode *mode_prev);
static void FMS_Vehicle(const int32_T *sfEvent, const PilotMode *mode_prev);
static void FMS_sf_msg_discard_M(void);
static void initialize_msg_local_queues_for(void);
const FMS_Out_Bus FMS_rtZFMS_Out_Bus = { 0U,/* timestamp */
  0.0F,                                /* p_cmd */
  0.0F,                                /* q_cmd */
  0.0F,                                /* r_cmd */
  0.0F,                                /* phi_cmd */
  0.0F,                                /* theta_cmd */
  0.0F,                                /* psi_rate_cmd */
  0.0F,                                /* u_cmd */
  0.0F,                                /* v_cmd */
  0.0F,                                /* w_cmd */
  0.0F,                                /* ax_cmd */
  0.0F,                                /* ay_cmd */
  0.0F,                                /* az_cmd */

  { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U },/* actuator_cmd */
  0U,                                  /* throttle_cmd */
  0U,                                  /* cmd_mask */
  0U,                                  /* status */
  0U,                                  /* state */
  0U,                                  /* ctrl_mode */
  0U,                                  /* mode */
  0U,                                  /* reset */
  0U,                                  /* wp_consume */
  0U,                                  /* wp_current */
  0U                                   /* reserved */
};

/*
 * Output and update for action system:
 *    '<S31>/Disarm'
 *    '<S41>/Unknown'
 *    '<S33>/Unknown'
 */
void FMS_Disarm(FMS_Out_Bus *rty_FMS_Out, const ConstB_Disarm_FMS_T *localC)
{
  int32_T i;
  memset(rty_FMS_Out, 0, sizeof(FMS_Out_Bus));

  /* BusAssignment: '<S35>/Bus Assignment' incorporates:
   *  Constant: '<S35>/Constant2'
   *  Constant: '<S35>/Constant3'
   */
  rty_FMS_Out->reset = 1U;
  rty_FMS_Out->status = localC->DataTypeConversion;
  rty_FMS_Out->state = localC->DataTypeConversion1;
  rty_FMS_Out->actuator_cmd[0] = 750U;
  rty_FMS_Out->actuator_cmd[1] = 10000U;
  rty_FMS_Out->actuator_cmd[2] = 10000U;
  rty_FMS_Out->actuator_cmd[3] = 10000U;
  for (i = 0; i < 12; i++) {
    rty_FMS_Out->actuator_cmd[i + 4] = 0U;
  }

  /* End of BusAssignment: '<S35>/Bus Assignment' */
}

/*
 * System initialize for action system:
 *    '<S307>/Hold Control'
 *    '<S241>/Hold Control'
 */
void FMS_HoldControl_Init(DW_HoldControl_FMS_T *localDW)
{
  /* InitializeConditions for Delay: '<S310>/Delay' */
  localDW->icLoad = true;
}

/*
 * System reset for action system:
 *    '<S307>/Hold Control'
 *    '<S241>/Hold Control'
 */
void FMS_HoldControl_Reset(DW_HoldControl_FMS_T *localDW)
{
  /* InitializeConditions for Delay: '<S310>/Delay' */
  localDW->icLoad = true;
}

/*
 * Output and update for action system:
 *    '<S307>/Hold Control'
 *    '<S241>/Hold Control'
 */
void FMS_HoldControl(real32_T rtu_FMS_In, real32_T *rty_w_cmd_mPs,
                     DW_HoldControl_FMS_T *localDW)
{
  /* Delay: '<S310>/Delay' incorporates:
   *  Gain: '<S312>/Gain'
   */
  if (localDW->icLoad) {
    localDW->Delay_DSTATE = -rtu_FMS_In;
  }

  /* Gain: '<S310>/Gain2' incorporates:
   *  Delay: '<S310>/Delay'
   *  Gain: '<S312>/Gain'
   *  Sum: '<S310>/Sum'
   */
  *rty_w_cmd_mPs = (localDW->Delay_DSTATE - (-rtu_FMS_In)) * FMS_PARAM.Z_P;

  /* Update for Delay: '<S310>/Delay' */
  localDW->icLoad = false;
}

/*
 * Output and update for action system:
 *    '<S307>/Brake Control'
 *    '<S241>/Brake Control'
 *    '<S251>/Brake Control'
 *    '<S208>/Brake Control'
 *    '<S178>/Brake Control'
 */
void FMS_BrakeControl(real32_T *rty_psi_rate_cmd_radPs)
{
  /* SignalConversion generated from: '<S309>/psi_rate_cmd_radPs' incorporates:
   *  Constant: '<S309>/Brake Speed'
   */
  *rty_psi_rate_cmd_radPs = 0.0F;
}

/*
 * System initialize for action system:
 *    '<S307>/Move Control'
 *    '<S241>/Move Control'
 */
void FMS_MoveControl_Init(DW_MoveControl_FMS_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S314>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S314>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * System reset for action system:
 *    '<S307>/Move Control'
 *    '<S241>/Move Control'
 */
void FMS_MoveControl_Reset(DW_MoveControl_FMS_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S314>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S314>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S307>/Move Control'
 *    '<S241>/Move Control'
 */
void FMS_MoveControl(real32_T rtu_FMS_In, real32_T *rty_w_cmd_mPs, const
                     ConstB_MoveControl_FMS_T *localC, DW_MoveControl_FMS_T
                     *localDW)
{
  real32_T rtb_Add3_e;
  real32_T rtb_Subtract3_m;
  real32_T rtb_a_d;
  real32_T u;
  real32_T u_0;

  /* Product: '<S315>/Multiply1' incorporates:
   *  Constant: '<S315>/const1'
   *  DiscreteIntegrator: '<S314>/Integrator'
   */
  rtb_Add3_e = localDW->Integrator_DSTATE * 0.05F;

  /* DeadZone: '<S313>/Dead Zone' */
  if (rtu_FMS_In > FMS_PARAM.THROTTLE_DZ) {
    u = rtu_FMS_In - FMS_PARAM.THROTTLE_DZ;
  } else if (rtu_FMS_In >= -FMS_PARAM.THROTTLE_DZ) {
    u = 0.0F;
  } else {
    u = rtu_FMS_In - (-FMS_PARAM.THROTTLE_DZ);
  }

  /* Sum: '<S315>/Add' incorporates:
   *  DeadZone: '<S313>/Dead Zone'
   *  DiscreteIntegrator: '<S314>/Integrator1'
   *  Gain: '<S311>/Gain1'
   *  Gain: '<S313>/Gain'
   *  Sum: '<S314>/Subtract'
   */
  rtb_Subtract3_m = (localDW->Integrator1_DSTATE - 1.0F / (1.0F -
    FMS_PARAM.THROTTLE_DZ) * u * -FMS_PARAM.VEL_Z_LIM) + rtb_Add3_e;

  /* Signum: '<S315>/Sign' */
  if (rtb_Subtract3_m < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(rtb_Subtract3_m > 0.0F);
  }

  /* Sum: '<S315>/Add2' incorporates:
   *  Abs: '<S315>/Abs'
   *  Gain: '<S315>/Gain'
   *  Gain: '<S315>/Gain1'
   *  Product: '<S315>/Multiply2'
   *  Product: '<S315>/Multiply3'
   *  Signum: '<S315>/Sign'
   *  Sqrt: '<S315>/Sqrt'
   *  Sum: '<S315>/Add1'
   *  Sum: '<S315>/Subtract'
   */
  rtb_a_d = (sqrtf((8.0F * fabsf(rtb_Subtract3_m) + localC->d) * localC->d) -
             localC->d) * 0.5F * u + rtb_Add3_e;

  /* Sum: '<S315>/Add3' */
  u = rtb_Subtract3_m + localC->d;

  /* Sum: '<S315>/Subtract1' */
  u_0 = rtb_Subtract3_m - localC->d;

  /* Signum: '<S315>/Sign1' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S315>/Sign2' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Sum: '<S315>/Add5' incorporates:
   *  Gain: '<S315>/Gain2'
   *  Product: '<S315>/Multiply4'
   *  Signum: '<S315>/Sign1'
   *  Signum: '<S315>/Sign2'
   *  Sum: '<S315>/Add4'
   *  Sum: '<S315>/Subtract2'
   */
  rtb_a_d += ((rtb_Subtract3_m - rtb_a_d) + rtb_Add3_e) * ((u - u_0) * 0.5F);

  /* SignalConversion generated from: '<S311>/w_cmd_mPs' incorporates:
   *  DiscreteIntegrator: '<S314>/Integrator1'
   */
  *rty_w_cmd_mPs = localDW->Integrator1_DSTATE;

  /* Update for DiscreteIntegrator: '<S314>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S314>/Integrator'
   */
  localDW->Integrator1_DSTATE += 0.004F * localDW->Integrator_DSTATE;

  /* Signum: '<S315>/Sign5' */
  if (rtb_a_d < 0.0F) {
    /* Signum: '<S315>/Sign6' */
    rtb_Add3_e = -1.0F;
  } else {
    /* Signum: '<S315>/Sign6' */
    rtb_Add3_e = (real32_T)(rtb_a_d > 0.0F);
  }

  /* Sum: '<S315>/Add6' */
  u = rtb_a_d + localC->d;

  /* Sum: '<S315>/Subtract3' */
  u_0 = rtb_a_d - localC->d;

  /* Signum: '<S315>/Sign3' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S315>/Sign4' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S314>/Integrator' incorporates:
   *  Constant: '<S315>/const'
   *  Gain: '<S315>/Gain3'
   *  Product: '<S315>/Divide'
   *  Product: '<S315>/Multiply5'
   *  Product: '<S315>/Multiply6'
   *  Signum: '<S315>/Sign3'
   *  Signum: '<S315>/Sign4'
   *  Signum: '<S315>/Sign5'
   *  Sum: '<S315>/Subtract4'
   *  Sum: '<S315>/Subtract5'
   *  Sum: '<S315>/Subtract6'
   */
  localDW->Integrator_DSTATE += ((rtb_a_d / localC->d - rtb_Add3_e) *
    localC->Gain4 * ((u - u_0) * 0.5F) - rtb_Add3_e * 78.448F) * 0.004F;
}

/*
 * System initialize for atomic system:
 *    '<S308>/Motion Status'
 *    '<S242>/Motion Status'
 */
void FMS_MotionStatus_Init(MotionState *rty_state, DW_MotionStatus_FMS_T
  *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c18_FMS = 0U;
  localDW->is_c18_FMS = FMS_IN_NO_ACTIVE_CHILD;
  *rty_state = MotionState_Hold;
}

/*
 * System reset for atomic system:
 *    '<S308>/Motion Status'
 *    '<S242>/Motion Status'
 */
void FMS_MotionStatus_Reset(MotionState *rty_state, DW_MotionStatus_FMS_T
  *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c18_FMS = 0U;
  localDW->is_c18_FMS = FMS_IN_NO_ACTIVE_CHILD;
  *rty_state = MotionState_Hold;
}

/*
 * Output and update for atomic system:
 *    '<S308>/Motion Status'
 *    '<S242>/Motion Status'
 */
void FMS_MotionStatus(real32_T rtu_motion_req, real32_T rtu_speed, MotionState
                      *rty_state, DW_MotionStatus_FMS_T *localDW)
{
  if (localDW->temporalCounter_i1 < 511U) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S308>/Motion Status' */
  if (localDW->is_active_c18_FMS == 0U) {
    localDW->is_active_c18_FMS = 1U;
    localDW->is_c18_FMS = FMS_IN_Move;
    *rty_state = MotionState_Move;
  } else {
    switch (localDW->is_c18_FMS) {
     case FMS_IN_Brake:
      *rty_state = MotionState_Brake;
      if ((rtu_speed <= 0.15) || (localDW->temporalCounter_i1 >= 375U)) {
        localDW->is_c18_FMS = FMS_IN_Hold;
        *rty_state = MotionState_Hold;
      } else if (rtu_motion_req == 1.0F) {
        localDW->is_c18_FMS = FMS_IN_Move;
        *rty_state = MotionState_Move;
      }
      break;

     case FMS_IN_Hold:
      *rty_state = MotionState_Hold;
      if (rtu_motion_req == 1.0F) {
        localDW->is_c18_FMS = FMS_IN_Move;
        *rty_state = MotionState_Move;
      }
      break;

     default:
      /* case IN_Move: */
      *rty_state = MotionState_Move;
      if (rtu_motion_req == 0.0F) {
        localDW->is_c18_FMS = FMS_IN_Brake;
        localDW->temporalCounter_i1 = 0U;
        *rty_state = MotionState_Brake;
      }
      break;
    }
  }

  /* End of Chart: '<S308>/Motion Status' */
}

/*
 * System initialize for action system:
 *    '<S317>/Hold Control'
 *    '<S263>/Hold Control'
 *    '<S220>/Hold Control'
 *    '<S191>/Hold Control'
 */
void FMS_HoldControl_l_Init(DW_HoldControl_FMS_f_T *localDW)
{
  /* InitializeConditions for Delay: '<S320>/Delay' */
  localDW->icLoad = true;
}

/*
 * System reset for action system:
 *    '<S317>/Hold Control'
 *    '<S263>/Hold Control'
 *    '<S220>/Hold Control'
 *    '<S191>/Hold Control'
 */
void FMS_HoldControl_a_Reset(DW_HoldControl_FMS_f_T *localDW)
{
  /* InitializeConditions for Delay: '<S320>/Delay' */
  localDW->icLoad = true;
}

/*
 * Output and update for action system:
 *    '<S317>/Hold Control'
 *    '<S263>/Hold Control'
 *    '<S220>/Hold Control'
 *    '<S191>/Hold Control'
 */
void FMS_HoldControl_g(real32_T rtu_FMS_In, real32_T rtu_FMS_In_g, real32_T
  rtu_FMS_In_n, real32_T rty_uv_cmd_mPs[2], const ConstB_HoldControl_FMS_g_T
  *localC, DW_HoldControl_FMS_f_T *localDW)
{
  int32_T i;
  real32_T rtb_VectorConcatenate_o[9];
  real32_T rtb_VectorConcatenate_bl[3];
  real32_T rtb_VectorConcatenate_bl_tmp;
  real32_T rtb_VectorConcatenate_bl_tmp_0;

  /* Delay: '<S320>/Delay' incorporates:
   *  SignalConversion generated from: '<S320>/Delay'
   */
  if (localDW->icLoad) {
    localDW->Delay_DSTATE[0] = rtu_FMS_In;
    localDW->Delay_DSTATE[1] = rtu_FMS_In_g;
  }

  /* Trigonometry: '<S324>/Trigonometric Function1' incorporates:
   *  Gain: '<S323>/Gain'
   *  Trigonometry: '<S324>/Trigonometric Function3'
   */
  rtb_VectorConcatenate_bl_tmp_0 = arm_cos_f32(-rtu_FMS_In_n);
  rtb_VectorConcatenate_o[0] = rtb_VectorConcatenate_bl_tmp_0;

  /* Trigonometry: '<S324>/Trigonometric Function' incorporates:
   *  Gain: '<S323>/Gain'
   *  Trigonometry: '<S324>/Trigonometric Function2'
   */
  rtb_VectorConcatenate_bl_tmp = arm_sin_f32(-rtu_FMS_In_n);
  rtb_VectorConcatenate_o[1] = rtb_VectorConcatenate_bl_tmp;

  /* SignalConversion generated from: '<S324>/Vector Concatenate1' incorporates:
   *  Constant: '<S324>/Constant3'
   */
  rtb_VectorConcatenate_o[2] = 0.0F;

  /* Gain: '<S324>/Gain' */
  rtb_VectorConcatenate_o[3] = -rtb_VectorConcatenate_bl_tmp;

  /* Trigonometry: '<S324>/Trigonometric Function3' */
  rtb_VectorConcatenate_o[4] = rtb_VectorConcatenate_bl_tmp_0;

  /* SignalConversion generated from: '<S324>/Vector Concatenate2' incorporates:
   *  Constant: '<S324>/Constant4'
   */
  rtb_VectorConcatenate_o[5] = 0.0F;

  /* SignalConversion generated from: '<S324>/Vector Concatenate' incorporates:
   *  Concatenate: '<S324>/Vector Concatenate3'
   */
  rtb_VectorConcatenate_o[6] = localC->VectorConcatenate3[0];
  rtb_VectorConcatenate_o[7] = localC->VectorConcatenate3[1];
  rtb_VectorConcatenate_o[8] = localC->VectorConcatenate3[2];

  /* SignalConversion generated from: '<S320>/Multiply' incorporates:
   *  Delay: '<S320>/Delay'
   *  SignalConversion generated from: '<S320>/Delay'
   *  Sum: '<S320>/Sum'
   */
  rtb_VectorConcatenate_bl_tmp_0 = localDW->Delay_DSTATE[0] - rtu_FMS_In;
  rtb_VectorConcatenate_bl_tmp = localDW->Delay_DSTATE[1] - rtu_FMS_In_g;

  /* Product: '<S320>/Multiply' incorporates:
   *  Concatenate: '<S324>/Vector Concatenate'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_bl[i] = rtb_VectorConcatenate_o[i + 3] *
      rtb_VectorConcatenate_bl_tmp + rtb_VectorConcatenate_o[i] *
      rtb_VectorConcatenate_bl_tmp_0;
  }

  /* End of Product: '<S320>/Multiply' */

  /* Gain: '<S320>/Gain2' */
  rty_uv_cmd_mPs[0] = FMS_PARAM.XY_P * rtb_VectorConcatenate_bl[0];
  rty_uv_cmd_mPs[1] = FMS_PARAM.XY_P * rtb_VectorConcatenate_bl[1];

  /* Update for Delay: '<S320>/Delay' */
  localDW->icLoad = false;
}

/*
 * Output and update for action system:
 *    '<S317>/Brake Control'
 *    '<S263>/Brake Control'
 *    '<S220>/Brake Control'
 *    '<S191>/Brake Control'
 */
void FMS_BrakeControl_h(real32_T rty_uv_cmd_mPs[2])
{
  /* SignalConversion generated from: '<S319>/uv_cmd_mPs' incorporates:
   *  Constant: '<S319>/Brake Speed'
   */
  rty_uv_cmd_mPs[0] = 0.0F;
  rty_uv_cmd_mPs[1] = 0.0F;
}

/*
 * System initialize for action system:
 *    '<S317>/Move Control'
 *    '<S263>/Move Control'
 *    '<S220>/Move Control'
 *    '<S191>/Move Control'
 */
void FMS_MoveControl_p_Init(DW_MoveControl_FMS_f_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator1' */
  localDW->Integrator1_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator' */
  localDW->Integrator_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator1' */
  localDW->Integrator1_DSTATE[1] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator' */
  localDW->Integrator_DSTATE[1] = 0.0F;
}

/*
 * System reset for action system:
 *    '<S317>/Move Control'
 *    '<S263>/Move Control'
 *    '<S220>/Move Control'
 *    '<S191>/Move Control'
 */
void FMS_MoveControl_i_Reset(DW_MoveControl_FMS_f_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator1' */
  localDW->Integrator1_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator' */
  localDW->Integrator_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator1' */
  localDW->Integrator1_DSTATE[1] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S327>/Integrator' */
  localDW->Integrator_DSTATE[1] = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S317>/Move Control'
 *    '<S263>/Move Control'
 *    '<S220>/Move Control'
 *    '<S191>/Move Control'
 */
void FMS_MoveControl_c(real32_T rtu_FMS_In, real32_T rtu_FMS_In_d, real32_T
  rty_uv_cmd_mPs[2], const ConstB_MoveControl_FMS_h_T *localC,
  DW_MoveControl_FMS_f_T *localDW)
{
  int32_T tmp;
  int32_T tmp_0;
  int32_T tmp_1;
  int32_T tmp_2;
  real32_T rtb_Add3_h_idx_0;
  real32_T rtb_Add3_h_idx_1;
  real32_T rtb_Subtract3_o_idx_0;
  real32_T rtb_Subtract3_o_idx_1;
  real32_T rtb_a_j;
  real32_T u;
  real32_T u_0;

  /* SignalConversion generated from: '<S321>/uv_cmd_mPs' incorporates:
   *  DiscreteIntegrator: '<S327>/Integrator1'
   */
  rty_uv_cmd_mPs[0] = localDW->Integrator1_DSTATE[0];

  /* Product: '<S328>/Multiply1' incorporates:
   *  Constant: '<S328>/const1'
   *  DiscreteIntegrator: '<S327>/Integrator'
   *  Sum: '<S328>/Add3'
   */
  rtb_Add3_h_idx_0 = localDW->Integrator_DSTATE[0] * 0.05F;

  /* SignalConversion generated from: '<S321>/uv_cmd_mPs' incorporates:
   *  DiscreteIntegrator: '<S327>/Integrator1'
   */
  rty_uv_cmd_mPs[1] = localDW->Integrator1_DSTATE[1];

  /* Product: '<S328>/Multiply1' incorporates:
   *  Constant: '<S328>/const1'
   *  DiscreteIntegrator: '<S327>/Integrator'
   *  Sum: '<S328>/Add3'
   */
  rtb_Add3_h_idx_1 = localDW->Integrator_DSTATE[1] * 0.05F;

  /* DeadZone: '<S325>/Dead Zone' */
  if (rtu_FMS_In > FMS_PARAM.PITCH_DZ) {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In - FMS_PARAM.PITCH_DZ;
  } else if (rtu_FMS_In >= -FMS_PARAM.PITCH_DZ) {
    rtb_Subtract3_o_idx_1 = 0.0F;
  } else {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In - (-FMS_PARAM.PITCH_DZ);
  }

  /* Sum: '<S328>/Add' incorporates:
   *  DeadZone: '<S325>/Dead Zone'
   *  DiscreteIntegrator: '<S327>/Integrator1'
   *  Gain: '<S321>/Gain6'
   *  Gain: '<S325>/Gain'
   *  Sum: '<S327>/Subtract'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Subtract3'
   */
  rtb_Subtract3_o_idx_0 = (localDW->Integrator1_DSTATE[0] - 1.0F / (1.0F -
    FMS_PARAM.PITCH_DZ) * rtb_Subtract3_o_idx_1 * FMS_PARAM.VEL_XY_LIM) +
    rtb_Add3_h_idx_0;

  /* DeadZone: '<S326>/Dead Zone' */
  if (rtu_FMS_In_d > FMS_PARAM.ROLL_DZ) {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In_d - FMS_PARAM.ROLL_DZ;
  } else if (rtu_FMS_In_d >= -FMS_PARAM.ROLL_DZ) {
    rtb_Subtract3_o_idx_1 = 0.0F;
  } else {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In_d - (-FMS_PARAM.ROLL_DZ);
  }

  /* Sum: '<S328>/Add' incorporates:
   *  DeadZone: '<S326>/Dead Zone'
   *  DiscreteIntegrator: '<S327>/Integrator1'
   *  Gain: '<S321>/Gain6'
   *  Gain: '<S326>/Gain'
   *  Sum: '<S327>/Subtract'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Subtract3'
   */
  rtb_Subtract3_o_idx_1 = (localDW->Integrator1_DSTATE[1] - 1.0F / (1.0F -
    FMS_PARAM.ROLL_DZ) * rtb_Subtract3_o_idx_1 * FMS_PARAM.VEL_XY_LIM) +
    rtb_Add3_h_idx_1;

  /* Signum: '<S328>/Sign' incorporates:
   *  Sum: '<S328>/Subtract3'
   */
  if (rtb_Subtract3_o_idx_0 < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_Subtract3_o_idx_0 > 0.0F);
  }

  /* Sum: '<S328>/Add2' incorporates:
   *  Abs: '<S328>/Abs'
   *  Gain: '<S328>/Gain'
   *  Gain: '<S328>/Gain1'
   *  Product: '<S328>/Multiply2'
   *  Product: '<S328>/Multiply3'
   *  Signum: '<S328>/Sign'
   *  Sqrt: '<S328>/Sqrt'
   *  Sum: '<S328>/Add1'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Subtract'
   *  Sum: '<S328>/Subtract3'
   */
  rtb_a_j = (sqrtf((8.0F * fabsf(rtb_Subtract3_o_idx_0) + localC->d) * localC->d)
             - localC->d) * 0.5F * (real32_T)tmp + rtb_Add3_h_idx_0;

  /* Signum: '<S328>/Sign1' incorporates:
   *  Signum: '<S328>/Sign'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Subtract3'
   */
  u = rtb_Subtract3_o_idx_0 + localC->d;

  /* Signum: '<S328>/Sign2' incorporates:
   *  Signum: '<S328>/Sign'
   *  Sum: '<S328>/Subtract1'
   *  Sum: '<S328>/Subtract3'
   */
  u_0 = rtb_Subtract3_o_idx_0 - localC->d;

  /* Signum: '<S328>/Sign1' */
  if (u < 0.0F) {
    tmp = -1;
  } else {
    tmp = (u > 0.0F);
  }

  /* Signum: '<S328>/Sign2' */
  if (u_0 < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u_0 > 0.0F);
  }

  /* Sum: '<S328>/Add5' incorporates:
   *  Gain: '<S328>/Gain2'
   *  Product: '<S328>/Multiply4'
   *  Signum: '<S328>/Sign'
   *  Signum: '<S328>/Sign1'
   *  Signum: '<S328>/Sign2'
   *  Sum: '<S328>/Add2'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Add4'
   *  Sum: '<S328>/Subtract2'
   *  Sum: '<S328>/Subtract3'
   */
  rtb_a_j += ((rtb_Subtract3_o_idx_0 - rtb_a_j) + rtb_Add3_h_idx_0) * ((real32_T)
    (tmp - tmp_0) * 0.5F);

  /* Update for DiscreteIntegrator: '<S327>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S327>/Integrator'
   */
  localDW->Integrator1_DSTATE[0] += 0.004F * localDW->Integrator_DSTATE[0];

  /* Signum: '<S328>/Sign3' incorporates:
   *  Sum: '<S328>/Add6'
   */
  u = rtb_a_j + localC->d;

  /* Signum: '<S328>/Sign4' incorporates:
   *  Sum: '<S328>/Subtract3'
   */
  u_0 = rtb_a_j - localC->d;

  /* Signum: '<S328>/Sign5' */
  if (rtb_a_j < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_a_j > 0.0F);
  }

  /* Signum: '<S328>/Sign3' */
  if (u < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u > 0.0F);
  }

  /* Signum: '<S328>/Sign4' */
  if (u_0 < 0.0F) {
    tmp_1 = -1;
  } else {
    tmp_1 = (u_0 > 0.0F);
  }

  /* Signum: '<S328>/Sign6' */
  if (rtb_a_j < 0.0F) {
    tmp_2 = -1;
  } else {
    tmp_2 = (rtb_a_j > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S327>/Integrator' incorporates:
   *  Constant: '<S328>/const'
   *  Gain: '<S328>/Gain3'
   *  Product: '<S328>/Divide'
   *  Product: '<S328>/Multiply5'
   *  Product: '<S328>/Multiply6'
   *  Signum: '<S328>/Sign3'
   *  Signum: '<S328>/Sign4'
   *  Signum: '<S328>/Sign5'
   *  Signum: '<S328>/Sign6'
   *  Sum: '<S328>/Subtract4'
   *  Sum: '<S328>/Subtract5'
   *  Sum: '<S328>/Subtract6'
   */
  localDW->Integrator_DSTATE[0] += ((rtb_a_j / localC->d - (real32_T)tmp) *
    localC->Gain4 * ((real32_T)(tmp_0 - tmp_1) * 0.5F) - (real32_T)tmp_2 *
    58.836F) * 0.004F;

  /* Signum: '<S328>/Sign' incorporates:
   *  Sum: '<S328>/Subtract3'
   */
  if (rtb_Subtract3_o_idx_1 < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_Subtract3_o_idx_1 > 0.0F);
  }

  /* Sum: '<S328>/Add2' incorporates:
   *  Abs: '<S328>/Abs'
   *  Gain: '<S328>/Gain'
   *  Gain: '<S328>/Gain1'
   *  Product: '<S328>/Multiply2'
   *  Product: '<S328>/Multiply3'
   *  Signum: '<S328>/Sign'
   *  Sqrt: '<S328>/Sqrt'
   *  Sum: '<S328>/Add1'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Subtract'
   *  Sum: '<S328>/Subtract3'
   */
  rtb_a_j = (sqrtf((8.0F * fabsf(rtb_Subtract3_o_idx_1) + localC->d) * localC->d)
             - localC->d) * 0.5F * (real32_T)tmp + rtb_Add3_h_idx_1;

  /* Signum: '<S328>/Sign1' incorporates:
   *  Signum: '<S328>/Sign'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Subtract3'
   */
  u = rtb_Subtract3_o_idx_1 + localC->d;

  /* Signum: '<S328>/Sign2' incorporates:
   *  Signum: '<S328>/Sign'
   *  Sum: '<S328>/Subtract1'
   *  Sum: '<S328>/Subtract3'
   */
  u_0 = rtb_Subtract3_o_idx_1 - localC->d;

  /* Signum: '<S328>/Sign1' */
  if (u < 0.0F) {
    tmp = -1;
  } else {
    tmp = (u > 0.0F);
  }

  /* Signum: '<S328>/Sign2' */
  if (u_0 < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u_0 > 0.0F);
  }

  /* Sum: '<S328>/Add5' incorporates:
   *  Gain: '<S328>/Gain2'
   *  Product: '<S328>/Multiply4'
   *  Signum: '<S328>/Sign'
   *  Signum: '<S328>/Sign1'
   *  Signum: '<S328>/Sign2'
   *  Sum: '<S328>/Add2'
   *  Sum: '<S328>/Add3'
   *  Sum: '<S328>/Add4'
   *  Sum: '<S328>/Subtract2'
   *  Sum: '<S328>/Subtract3'
   */
  rtb_a_j += ((rtb_Subtract3_o_idx_1 - rtb_a_j) + rtb_Add3_h_idx_1) * ((real32_T)
    (tmp - tmp_0) * 0.5F);

  /* Update for DiscreteIntegrator: '<S327>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S327>/Integrator'
   */
  localDW->Integrator1_DSTATE[1] += 0.004F * localDW->Integrator_DSTATE[1];

  /* Signum: '<S328>/Sign3' incorporates:
   *  Sum: '<S328>/Add6'
   */
  u = rtb_a_j + localC->d;

  /* Signum: '<S328>/Sign4' incorporates:
   *  Sum: '<S328>/Subtract3'
   */
  u_0 = rtb_a_j - localC->d;

  /* Signum: '<S328>/Sign5' */
  if (rtb_a_j < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_a_j > 0.0F);
  }

  /* Signum: '<S328>/Sign3' */
  if (u < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u > 0.0F);
  }

  /* Signum: '<S328>/Sign4' */
  if (u_0 < 0.0F) {
    tmp_1 = -1;
  } else {
    tmp_1 = (u_0 > 0.0F);
  }

  /* Signum: '<S328>/Sign6' */
  if (rtb_a_j < 0.0F) {
    tmp_2 = -1;
  } else {
    tmp_2 = (rtb_a_j > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S327>/Integrator' incorporates:
   *  Constant: '<S328>/const'
   *  Gain: '<S328>/Gain3'
   *  Product: '<S328>/Divide'
   *  Product: '<S328>/Multiply5'
   *  Product: '<S328>/Multiply6'
   *  Signum: '<S328>/Sign3'
   *  Signum: '<S328>/Sign4'
   *  Signum: '<S328>/Sign5'
   *  Signum: '<S328>/Sign6'
   *  Sum: '<S328>/Subtract4'
   *  Sum: '<S328>/Subtract5'
   *  Sum: '<S328>/Subtract6'
   */
  localDW->Integrator_DSTATE[1] += ((rtb_a_j / localC->d - (real32_T)tmp) *
    localC->Gain4 * ((real32_T)(tmp_0 - tmp_1) * 0.5F) - (real32_T)tmp_2 *
    58.836F) * 0.004F;
}

/*
 * System initialize for atomic system:
 *    '<S318>/Motion State'
 *    '<S264>/Motion State'
 *    '<S221>/Motion State'
 */
void FMS_MotionState_Init(MotionState *rty_state, DW_MotionState_FMS_T *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c19_FMS = 0U;
  localDW->is_c19_FMS = FMS_IN_NO_ACTIVE_CHILD_j;
  *rty_state = MotionState_Hold;
}

/*
 * System reset for atomic system:
 *    '<S318>/Motion State'
 *    '<S264>/Motion State'
 *    '<S221>/Motion State'
 */
void FMS_MotionState_Reset(MotionState *rty_state, DW_MotionState_FMS_T *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c19_FMS = 0U;
  localDW->is_c19_FMS = FMS_IN_NO_ACTIVE_CHILD_j;
  *rty_state = MotionState_Hold;
}

/*
 * Output and update for atomic system:
 *    '<S318>/Motion State'
 *    '<S264>/Motion State'
 *    '<S221>/Motion State'
 */
void FMS_MotionState(real32_T rtu_motion_req, real32_T rtu_speed, MotionState
                     *rty_state, DW_MotionState_FMS_T *localDW)
{
  if (localDW->temporalCounter_i1 < 1023U) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S318>/Motion State' */
  if (localDW->is_active_c19_FMS == 0U) {
    localDW->is_active_c19_FMS = 1U;
    localDW->is_c19_FMS = FMS_IN_Move_h;
    *rty_state = MotionState_Move;
  } else {
    switch (localDW->is_c19_FMS) {
     case FMS_IN_Brake_k:
      *rty_state = MotionState_Brake;
      if ((rtu_speed <= 0.2) || (localDW->temporalCounter_i1 >= 625U)) {
        localDW->is_c19_FMS = FMS_IN_Hold_e;
        *rty_state = MotionState_Hold;
      } else if (rtu_motion_req == 1.0F) {
        localDW->is_c19_FMS = FMS_IN_Move_h;
        *rty_state = MotionState_Move;
      }
      break;

     case FMS_IN_Hold_e:
      *rty_state = MotionState_Hold;
      if (rtu_motion_req == 1.0F) {
        localDW->is_c19_FMS = FMS_IN_Move_h;
        *rty_state = MotionState_Move;
      }
      break;

     default:
      /* case IN_Move: */
      *rty_state = MotionState_Move;
      if (rtu_motion_req == 0.0F) {
        localDW->is_c19_FMS = FMS_IN_Brake_k;
        localDW->temporalCounter_i1 = 0U;
        *rty_state = MotionState_Brake;
      }
      break;
    }
  }

  /* End of Chart: '<S318>/Motion State' */
}

/*
 * Output and update for atomic system:
 *    '<S301>/NearbyRefWP'
 *    '<S62>/NearbyRefWP'
 */
void FMS_NearbyRefWP(const real32_T rtu_P2[2], const real32_T rtu_P3[2],
                     real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_d)
{
  real32_T dis;
  real32_T y_idx_0;
  dis = rtu_P2[0] - rtu_P3[0];
  y_idx_0 = dis * dis;
  dis = rtu_P2[1] - rtu_P3[1];
  dis = sqrtf(dis * dis + y_idx_0);
  if (dis <= rtu_L1) {
    *rty_d = dis;
    rty_P[0] = rtu_P2[0];
    rty_P[1] = rtu_P2[1];
  } else {
    *rty_d = -1.0F;
    rty_P[0] = 0.0F;
    rty_P[1] = 0.0F;
  }
}

/*
 * Output and update for atomic system:
 *    '<S301>/OutRegionRegWP'
 *    '<S62>/OutRegionRegWP'
 */
void FMS_OutRegionRegWP(const real32_T rtu_P1[2], const real32_T rtu_P2[2],
  const real32_T rtu_P3[2], real32_T rty_P[2])
{
  real32_T b_x_idx_0;
  real32_T u;
  rty_P[0] = rtu_P2[0] - rtu_P1[0];
  u = (rtu_P3[0] - rtu_P1[0]) * rty_P[0];
  b_x_idx_0 = rty_P[0] * rty_P[0];
  rty_P[1] = rtu_P2[1] - rtu_P1[1];
  u = ((rtu_P3[1] - rtu_P1[1]) * rty_P[1] + u) / (rty_P[1] * rty_P[1] +
    b_x_idx_0);
  if (u <= 0.0F) {
    rty_P[0] = rtu_P1[0];
    rty_P[1] = rtu_P1[1];
  } else if (u >= 1.0F) {
    rty_P[0] = rtu_P2[0];
    rty_P[1] = rtu_P2[1];
  } else {
    rty_P[0] = u * rty_P[0] + rtu_P1[0];
    rty_P[1] = u * rty_P[1] + rtu_P1[1];
  }
}

/*
 * Output and update for atomic system:
 *    '<S301>/SearchL1RefWP'
 *    '<S62>/SearchL1RefWP'
 */
void FMS_SearchL1RefWP(const real32_T rtu_P1[2], const real32_T rtu_P2[2], const
  real32_T rtu_P3[2], real32_T rtu_L1, real32_T rty_P[2], real32_T *rty_u)
{
  real32_T A;
  real32_T B;
  real32_T D;
  real32_T a_tmp;
  real32_T b_a_tmp;
  real32_T u;
  boolean_T guard1 = false;
  a_tmp = rtu_P2[0] - rtu_P1[0];
  b_a_tmp = rtu_P2[1] - rtu_P1[1];
  A = a_tmp * a_tmp + b_a_tmp * b_a_tmp;
  B = ((rtu_P1[0] - rtu_P3[0]) * a_tmp + (rtu_P1[1] - rtu_P3[1]) * b_a_tmp) *
    2.0F;
  D = B * B - (((((rtu_P3[0] * rtu_P3[0] + rtu_P3[1] * rtu_P3[1]) + rtu_P1[0] *
                  rtu_P1[0]) + rtu_P1[1] * rtu_P1[1]) - (rtu_P3[0] * rtu_P1[0] +
    rtu_P3[1] * rtu_P1[1]) * 2.0F) - rtu_L1 * rtu_L1) * (4.0F * A);
  u = -1.0F;
  rty_P[0] = 0.0F;
  rty_P[1] = 0.0F;
  guard1 = false;
  if (D > 0.0F) {
    real32_T u1_tmp;
    u1_tmp = sqrtf(D);
    D = (-B + u1_tmp) / (2.0F * A);
    A = (-B - u1_tmp) / (2.0F * A);
    if ((D >= 0.0F) && (D <= 1.0F) && (A >= 0.0F) && (A <= 1.0F)) {
      u = fmaxf(D, A);
      guard1 = true;
    } else if ((D >= 0.0F) && (D <= 1.0F)) {
      u = D;
      guard1 = true;
    } else if ((A >= 0.0F) && (A <= 1.0F)) {
      u = A;
      guard1 = true;
    }
  } else if (D == 0.0F) {
    D = -B / (2.0F * A);
    if ((D >= 0.0F) && (D <= 1.0F)) {
      u = D;
      guard1 = true;
    }
  }

  if (guard1) {
    rty_P[0] = a_tmp * u + rtu_P1[0];
    rty_P[1] = b_a_tmp * u + rtu_P1[1];
  }

  *rty_u = u;
}

/*
 * System initialize for action system:
 *    '<S251>/Hold Control'
 *    '<S208>/Hold Control'
 *    '<S178>/Hold Control'
 */
void FMS_HoldControl_i_Init(DW_HoldControl_FMS_m_T *localDW)
{
  /* InitializeConditions for Delay: '<S254>/Delay' */
  localDW->icLoad = true;
}

/*
 * System reset for action system:
 *    '<S251>/Hold Control'
 *    '<S208>/Hold Control'
 *    '<S178>/Hold Control'
 */
void FMS_HoldControl_i_Reset(DW_HoldControl_FMS_m_T *localDW)
{
  /* InitializeConditions for Delay: '<S254>/Delay' */
  localDW->icLoad = true;
}

/*
 * Output and update for action system:
 *    '<S251>/Hold Control'
 *    '<S208>/Hold Control'
 *    '<S178>/Hold Control'
 */
void FMS_HoldControl_k(real32_T rtu_FMS_In, real32_T *rty_psi_rate_cmd_radPs,
  DW_HoldControl_FMS_m_T *localDW)
{
  real32_T rtb_Abs_b;
  real32_T rtb_psi_error_rad;

  /* Delay: '<S254>/Delay' */
  if (localDW->icLoad) {
    localDW->Delay_DSTATE = rtu_FMS_In;
  }

  /* Sum: '<S254>/Sum' incorporates:
   *  Delay: '<S254>/Delay'
   */
  rtb_psi_error_rad = localDW->Delay_DSTATE - rtu_FMS_In;

  /* Abs: '<S257>/Abs' */
  rtb_Abs_b = fabsf(rtb_psi_error_rad);

  /* Switch: '<S257>/Switch' incorporates:
   *  Constant: '<S257>/Constant'
   *  Constant: '<S258>/Constant'
   *  Product: '<S257>/Multiply'
   *  RelationalOperator: '<S258>/Compare'
   *  Signum: '<S257>/Sign'
   *  Sum: '<S257>/Subtract'
   */
  if (rtb_Abs_b > 3.14159274F) {
    /* Signum: '<S257>/Sign' */
    if (rtb_psi_error_rad < 0.0F) {
      rtb_psi_error_rad = -1.0F;
    } else {
      rtb_psi_error_rad = (real32_T)(rtb_psi_error_rad > 0.0F);
    }

    rtb_psi_error_rad *= rtb_Abs_b - 6.28318548F;
  }

  /* End of Switch: '<S257>/Switch' */

  /* Gain: '<S254>/Gain2' */
  *rty_psi_rate_cmd_radPs = FMS_PARAM.YAW_P * rtb_psi_error_rad;

  /* Update for Delay: '<S254>/Delay' */
  localDW->icLoad = false;
}

/*
 * System initialize for action system:
 *    '<S251>/Move Control'
 *    '<S208>/Move Control'
 *    '<S178>/Move Control'
 */
void FMS_MoveControl_m_Init(DW_MoveControl_FMS_c_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S260>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S260>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * System reset for action system:
 *    '<S251>/Move Control'
 *    '<S208>/Move Control'
 *    '<S178>/Move Control'
 */
void FMS_MoveControl_c_Reset(DW_MoveControl_FMS_c_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S260>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S260>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S251>/Move Control'
 *    '<S208>/Move Control'
 *    '<S178>/Move Control'
 */
void FMS_MoveControl_o(real32_T rtu_FMS_In, real32_T *rty_psi_rate_cmd_radPs,
  const ConstB_MoveControl_FMS_n_T *localC, DW_MoveControl_FMS_c_T *localDW)
{
  real32_T rtb_Add3_p;
  real32_T rtb_Subtract3_k;
  real32_T rtb_a_n;
  real32_T u;
  real32_T u_0;

  /* Product: '<S261>/Multiply1' incorporates:
   *  Constant: '<S261>/const1'
   *  DiscreteIntegrator: '<S260>/Integrator'
   */
  rtb_Add3_p = localDW->Integrator_DSTATE * 0.02F;

  /* DeadZone: '<S259>/Dead Zone' */
  if (rtu_FMS_In > FMS_PARAM.YAW_DZ) {
    u = rtu_FMS_In - FMS_PARAM.YAW_DZ;
  } else if (rtu_FMS_In >= -FMS_PARAM.YAW_DZ) {
    u = 0.0F;
  } else {
    u = rtu_FMS_In - (-FMS_PARAM.YAW_DZ);
  }

  /* Sum: '<S261>/Add' incorporates:
   *  DeadZone: '<S259>/Dead Zone'
   *  DiscreteIntegrator: '<S260>/Integrator1'
   *  Gain: '<S255>/Gain1'
   *  Gain: '<S259>/Gain'
   *  Sum: '<S260>/Subtract'
   */
  rtb_Subtract3_k = (localDW->Integrator1_DSTATE - 1.0F / (1.0F -
    FMS_PARAM.YAW_DZ) * u * FMS_PARAM.YAW_RATE_LIM) + rtb_Add3_p;

  /* Signum: '<S261>/Sign' */
  if (rtb_Subtract3_k < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(rtb_Subtract3_k > 0.0F);
  }

  /* Sum: '<S261>/Add2' incorporates:
   *  Abs: '<S261>/Abs'
   *  Gain: '<S261>/Gain'
   *  Gain: '<S261>/Gain1'
   *  Product: '<S261>/Multiply2'
   *  Product: '<S261>/Multiply3'
   *  Signum: '<S261>/Sign'
   *  Sqrt: '<S261>/Sqrt'
   *  Sum: '<S261>/Add1'
   *  Sum: '<S261>/Subtract'
   */
  rtb_a_n = (sqrtf((8.0F * fabsf(rtb_Subtract3_k) + localC->d) * localC->d) -
             localC->d) * 0.5F * u + rtb_Add3_p;

  /* Sum: '<S261>/Add3' */
  u = rtb_Subtract3_k + localC->d;

  /* Sum: '<S261>/Subtract1' */
  u_0 = rtb_Subtract3_k - localC->d;

  /* Signum: '<S261>/Sign1' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S261>/Sign2' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Sum: '<S261>/Add5' incorporates:
   *  Gain: '<S261>/Gain2'
   *  Product: '<S261>/Multiply4'
   *  Signum: '<S261>/Sign1'
   *  Signum: '<S261>/Sign2'
   *  Sum: '<S261>/Add4'
   *  Sum: '<S261>/Subtract2'
   */
  rtb_a_n += ((rtb_Subtract3_k - rtb_a_n) + rtb_Add3_p) * ((u - u_0) * 0.5F);

  /* SignalConversion generated from: '<S255>/psi_rate_cmd_radPs' incorporates:
   *  DiscreteIntegrator: '<S260>/Integrator1'
   */
  *rty_psi_rate_cmd_radPs = localDW->Integrator1_DSTATE;

  /* Update for DiscreteIntegrator: '<S260>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S260>/Integrator'
   */
  localDW->Integrator1_DSTATE += 0.004F * localDW->Integrator_DSTATE;

  /* Signum: '<S261>/Sign5' */
  if (rtb_a_n < 0.0F) {
    /* Signum: '<S261>/Sign6' */
    rtb_Add3_p = -1.0F;
  } else {
    /* Signum: '<S261>/Sign6' */
    rtb_Add3_p = (real32_T)(rtb_a_n > 0.0F);
  }

  /* Sum: '<S261>/Add6' */
  u = rtb_a_n + localC->d;

  /* Sum: '<S261>/Subtract3' */
  u_0 = rtb_a_n - localC->d;

  /* Signum: '<S261>/Sign3' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S261>/Sign4' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S260>/Integrator' incorporates:
   *  Constant: '<S261>/const'
   *  Gain: '<S261>/Gain3'
   *  Product: '<S261>/Divide'
   *  Product: '<S261>/Multiply5'
   *  Product: '<S261>/Multiply6'
   *  Signum: '<S261>/Sign3'
   *  Signum: '<S261>/Sign4'
   *  Signum: '<S261>/Sign5'
   *  Sum: '<S261>/Subtract4'
   *  Sum: '<S261>/Subtract5'
   *  Sum: '<S261>/Subtract6'
   */
  localDW->Integrator_DSTATE += ((rtb_a_n / localC->d - rtb_Add3_p) *
    localC->Gain4 * ((u - u_0) * 0.5F) - rtb_Add3_p * 15.707963F) * 0.004F;
}

/*
 * System initialize for atomic system:
 *    '<S252>/Motion State'
 *    '<S209>/Motion State'
 */
void FMS_MotionState_b_Init(MotionState *rty_state, DW_MotionState_FMS_o_T
  *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c10_FMS = 0U;
  localDW->is_c10_FMS = FMS_IN_NO_ACTIVE_CHILD_m;
  *rty_state = MotionState_Hold;
}

/*
 * System reset for atomic system:
 *    '<S252>/Motion State'
 *    '<S209>/Motion State'
 */
void FMS_MotionState_i_Reset(MotionState *rty_state, DW_MotionState_FMS_o_T
  *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c10_FMS = 0U;
  localDW->is_c10_FMS = FMS_IN_NO_ACTIVE_CHILD_m;
  *rty_state = MotionState_Hold;
}

/*
 * Output and update for atomic system:
 *    '<S252>/Motion State'
 *    '<S209>/Motion State'
 */
void FMS_MotionState_i(real32_T rtu_motion_req, real32_T rtu_speed, MotionState *
  rty_state, DW_MotionState_FMS_o_T *localDW)
{
  if (localDW->temporalCounter_i1 < 255U) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S252>/Motion State' */
  if (localDW->is_active_c10_FMS == 0U) {
    localDW->is_active_c10_FMS = 1U;
    localDW->is_c10_FMS = FMS_IN_Move_f;
    *rty_state = MotionState_Move;
  } else {
    switch (localDW->is_c10_FMS) {
     case FMS_IN_Brake_l:
      *rty_state = MotionState_Brake;
      if ((rtu_speed <= 0.1) || (localDW->temporalCounter_i1 >= 250U)) {
        localDW->is_c10_FMS = FMS_IN_Hold_i;
        *rty_state = MotionState_Hold;
      } else if (rtu_motion_req == 1.0F) {
        localDW->is_c10_FMS = FMS_IN_Move_f;
        *rty_state = MotionState_Move;
      }
      break;

     case FMS_IN_Hold_i:
      *rty_state = MotionState_Hold;
      if (rtu_motion_req == 1.0F) {
        localDW->is_c10_FMS = FMS_IN_Move_f;
        *rty_state = MotionState_Move;
      }
      break;

     default:
      /* case IN_Move: */
      *rty_state = MotionState_Move;
      if (rtu_motion_req == 0.0F) {
        localDW->is_c10_FMS = FMS_IN_Brake_l;
        localDW->temporalCounter_i1 = 0U;
        *rty_state = MotionState_Brake;
      }
      break;
    }
  }

  /* End of Chart: '<S252>/Motion State' */
}

real_T rt_modd(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else {
    boolean_T yEq;
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      real_T q;
      q = fabs(u0 / u1);
      yEq = (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q);
    }

    if (yEq) {
      y = 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Output and update for function-call system: '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
void F_VehicleArmAutoMissionLLA2FLAT(const real_T rtu_lla[3], const real_T
  rtu_llo[2], real_T rtu_href, real_T rtu_psio, real32_T rty_pos[3], const
  ConstB_VehicleArmAutoMissionL_T *localC)
{
  real_T rtb_Gain_j1;
  real_T rtb_Sum2_i;
  real_T rtb_Sum_n;
  real_T rtb_Sum_o_idx_0;
  int32_T tmp;

  /* Gain: '<S366>/deg2rad' */
  rtb_Sum_o_idx_0 = 0.017453292519943295 * rtu_llo[0];

  /* Trigonometry: '<S367>/Sin' */
  rtb_Sum2_i = sin(rtb_Sum_o_idx_0);

  /* Product: '<S367>/Multiply1' incorporates:
   *  Math: '<S367>/Square1'
   *  Product: '<S367>/Multiply'
   */
  rtb_Gain_j1 = rtb_Sum2_i * rtb_Sum2_i * localC->ff;

  /* Product: '<S367>/Divide' incorporates:
   *  Constant: '<S367>/Constant'
   *  Constant: '<S367>/R'
   *  Sqrt: '<S367>/Sqrt'
   *  Sum: '<S367>/Sum1'
   */
  rtb_Sum2_i = 6.378137E+6 / sqrt(1.0 - rtb_Gain_j1);

  /* Product: '<S367>/Product3' incorporates:
   *  Constant: '<S367>/Constant1'
   *  Product: '<S367>/Multiply1'
   *  Sum: '<S367>/Sum2'
   */
  rtb_Gain_j1 = 1.0 / (1.0 - rtb_Gain_j1) * localC->Sum4 * rtb_Sum2_i;

  /* Product: '<S367>/Multiply2' incorporates:
   *  Trigonometry: '<S367>/Cos'
   */
  rtb_Sum2_i *= cos(rtb_Sum_o_idx_0);

  /* Sum: '<S366>/Sum' */
  rtb_Sum_o_idx_0 = rtu_lla[0] - rtu_llo[0];

  /* Abs: '<S371>/Abs' incorporates:
   *  Abs: '<S374>/Abs1'
   *  Switch: '<S371>/Switch1'
   */
  rtb_Sum_n = fabs(rtb_Sum_o_idx_0);

  /* Switch: '<S371>/Switch1' incorporates:
   *  Abs: '<S371>/Abs'
   *  Bias: '<S371>/Bias2'
   *  Bias: '<S371>/Bias3'
   *  Constant: '<S368>/Constant'
   *  Constant: '<S368>/Constant1'
   *  Constant: '<S373>/Constant'
   *  Gain: '<S371>/Gain1'
   *  Product: '<S371>/Multiply'
   *  RelationalOperator: '<S373>/Compare'
   *  Signum: '<S371>/Sign'
   *  Switch: '<S368>/Switch'
   */
  if (rtb_Sum_n > 90.0) {
    /* Switch: '<S374>/Switch1' incorporates:
     *  Bias: '<S374>/Bias2'
     *  Bias: '<S374>/Bias3'
     *  Constant: '<S374>/Constant'
     *  Constant: '<S375>/Constant'
     *  Math: '<S374>/Math Function'
     *  RelationalOperator: '<S375>/Compare'
     */
    if (rtb_Sum_n > 180.0) {
      rtb_Sum_o_idx_0 = rt_modd(rtb_Sum_o_idx_0 + 180.0, 360.0) - 180.0;
    }

    /* End of Switch: '<S374>/Switch1' */

    /* Signum: '<S371>/Sign' */
    if (rtb_Sum_o_idx_0 < 0.0) {
      rtb_Sum_o_idx_0 = -1.0;
    } else {
      rtb_Sum_o_idx_0 = (rtb_Sum_o_idx_0 > 0.0);
    }

    rtb_Sum_o_idx_0 *= -(rtb_Sum_n - 90.0) + 90.0;
    tmp = 180;
  } else {
    tmp = 0;
  }

  /* Sum: '<S368>/Sum' incorporates:
   *  Sum: '<S366>/Sum'
   *  Switch: '<S368>/Switch'
   */
  rtb_Sum_n = (rtu_lla[1] - rtu_llo[1]) + (real_T)tmp;

  /* Product: '<S366>/Multiply' incorporates:
   *  Gain: '<S366>/deg2rad1'
   */
  rtb_Sum_o_idx_0 = 0.017453292519943295 * rtb_Sum_o_idx_0 * rtb_Gain_j1;

  /* Switch: '<S370>/Switch1' incorporates:
   *  Abs: '<S370>/Abs1'
   *  Bias: '<S370>/Bias2'
   *  Bias: '<S370>/Bias3'
   *  Constant: '<S370>/Constant'
   *  Constant: '<S372>/Constant'
   *  Math: '<S370>/Math Function'
   *  RelationalOperator: '<S372>/Compare'
   */
  if (fabs(rtb_Sum_n) > 180.0) {
    rtb_Sum_n = rt_modd(rtb_Sum_n + 180.0, 360.0) - 180.0;
  }

  /* Product: '<S366>/Multiply' incorporates:
   *  Gain: '<S366>/deg2rad1'
   *  Switch: '<S370>/Switch1'
   */
  rtb_Sum2_i *= 0.017453292519943295 * rtb_Sum_n;

  /* Gain: '<S366>/deg2rad2' */
  rtb_Gain_j1 = 0.017453292519943295 * rtu_psio;

  /* Trigonometry: '<S369>/SinCos' */
  rtb_Sum_n = sin(rtb_Gain_j1);
  rtb_Gain_j1 = cos(rtb_Gain_j1);

  /* DataTypeConversion: '<S365>/Data Type Conversion' incorporates:
   *  Gain: '<S366>/Gain'
   *  Product: '<S369>/Multiply1'
   *  Product: '<S369>/Multiply2'
   *  Product: '<S369>/Multiply3'
   *  Product: '<S369>/Multiply4'
   *  Sum: '<S366>/Sum1'
   *  Sum: '<S369>/Sum2'
   *  Sum: '<S369>/Sum3'
   */
  rty_pos[0] = (real32_T)(rtb_Sum_o_idx_0 * rtb_Gain_j1 + rtb_Sum2_i * rtb_Sum_n);
  rty_pos[1] = (real32_T)(rtb_Sum2_i * rtb_Gain_j1 - rtb_Sum_o_idx_0 * rtb_Sum_n);
  rty_pos[2] = (real32_T)-(rtu_lla[2] + rtu_href);
}

uint16_T rt_sqrt_Uu16_Yu16_Iu32_f_s(uint16_T u)
{
  int32_T iBit;
  uint16_T shiftMask;
  uint16_T y;

  /* Fixed-Point Sqrt Computation by the bisection method. */
  y = 0U;
  shiftMask = 32768U;
  for (iBit = 0; iBit < 16; iBit++) {
    uint16_T tmp01_y;
    tmp01_y = (uint16_T)(y | shiftMask);
    if ((uint32_T)tmp01_y * tmp01_y <= u) {
      y = tmp01_y;
    }

    shiftMask = (uint16_T)((uint32_T)shiftMask >> 1U);
  }

  return y;
}

boolean_T FMS_emplace(Queue_FMS_Cmd *q, const FMS_Cmd *dataIn)
{
  Msg_FMS_Cmd *msg;
  int32_T newTail;
  boolean_T isEmplaced = false;
  newTail = (q->fTail + 1) % q->fCapacity;
  if (q->fHead != newTail) {
    q->fTail = newTail;
    msg = &q->fArray[newTail];
    msg->fData = *dataIn;
    if (q->fHead == -1) {
      q->fHead = q->fTail;
    }

    isEmplaced = true;
  }

  return isEmplaced;
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_sf_msg_send_M(void)
{
  FMS_emplace(&FMS_DW.Queue, &FMS_DW.M_msgReservedData);
}

/* Function for Chart: '<Root>/State Machine' */
static boolean_T FMS_CheckCmdValid(FMS_Cmd cmd_in, PilotMode mode_in, uint32_T
  ins_flag)
{
  boolean_T valid;
  valid = false;
  switch (cmd_in) {
   case FMS_Cmd_PreArm:
    if (((ins_flag & 1U) == 0U) || ((ins_flag & 4U) == 0U) || ((ins_flag & 8U) ==
         0U)) {
    } else {
      switch (mode_in) {
       case PilotMode_Position:
       case PilotMode_Mission:
        valid = (((ins_flag & 16U) != 0U) && ((ins_flag & 64U) != 0U) &&
                 ((ins_flag & 128U) != 0U));
        break;

       case PilotMode_Stabilize:
        valid = true;
        break;
      }
    }
    break;

   case FMS_Cmd_Continue:
    valid = ((mode_in == PilotMode_Offboard) || (mode_in == PilotMode_Mission));
    break;

   case FMS_Cmd_Disarm:
    valid = true;
    break;
  }

  return valid;
}

/* Function for Chart: '<Root>/State Machine' */
static boolean_T FMS_BottomRight(real32_T pilot_cmd_stick_yaw, real32_T
  pilot_cmd_stick_throttle)
{
  return (pilot_cmd_stick_throttle < -0.8) && (pilot_cmd_stick_yaw > 0.8);
}

/* Function for Chart: '<Root>/State Machine' */
static boolean_T FMS_BottomLeft(real32_T pilot_cmd_stick_yaw, real32_T
  pilot_cmd_stick_throttle)
{
  return (pilot_cmd_stick_throttle < -0.8) && (pilot_cmd_stick_yaw < -0.8);
}

boolean_T FMS_pop(Queue_FMS_Cmd *q, Msg_FMS_Cmd *elementOut)
{
  boolean_T isPop;
  if (q->fHead == -1) {
    isPop = false;
  } else {
    *elementOut = q->fArray[q->fHead];
    isPop = true;
    if (q->fHead == q->fTail) {
      q->fHead = -1;
      q->fTail = -1;
    } else {
      q->fHead = (q->fHead + 1) % q->fCapacity;
    }
  }

  return isPop;
}

/* Function for Chart: '<Root>/State Machine' */
static boolean_T FMS_sf_msg_pop_M(void)
{
  boolean_T isPresent;
  if (FMS_DW.M_isValid) {
    isPresent = true;
  } else {
    if (FMS_pop(&FMS_DW.Queue, &FMS_DW.Msg[0])) {
      FMS_DW.M_msgHandle = &FMS_DW.Msg[0];
    } else {
      FMS_DW.M_msgHandle = NULL;
    }

    if (FMS_DW.M_msgHandle != NULL) {
      FMS_DW.M_msgDataPtr = &((Msg_FMS_Cmd *)FMS_DW.M_msgHandle)->fData;
      isPresent = true;
      FMS_DW.M_msgReservedData = *(FMS_Cmd *)FMS_DW.M_msgDataPtr;
      FMS_DW.M_isValid = true;
    } else {
      isPresent = false;
    }
  }

  return isPresent;
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_exit_internal_Auto(void)
{
  if (FMS_DW.is_Auto == FMS_IN_Mission_a) {
    FMS_DW.is_Mission = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_d;
  } else {
    FMS_DW.is_Offboard = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_d;
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_Auto(void)
{
  real_T lla[3];
  boolean_T out;
  if (FMS_sf_msg_pop_M()) {
    out = (FMS_DW.M_msgReservedData == FMS_Cmd_Pause);
  } else {
    out = false;
  }

  if (out) {
    FMS_exit_internal_Auto();
    FMS_DW.is_Arm = FMS_IN_Stabilize;
    FMS_B.state = VehicleState_Stabilize;
  } else {
    switch (FMS_DW.is_Auto) {
     case FMS_IN_Mission_a:
      {
        if (FMS_DW.mission_timestamp_prev != FMS_DW.mission_timestamp_start) {
          FMS_DW.is_Mission = FMS_IN_NextWP;

          /* Inport: '<Root>/Mission_Data' */
          if (FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) {
            FMS_DW.nav_cmd = FMS_U.Mission_Data.command[FMS_B.wp_index - 1];
          } else {
            int32_T qY;
            FMS_DW.nav_cmd = (uint16_T)NAV_Cmd_None;
            qY = (int32_T)(FMS_B.wp_index - /*MW:OvSatOk*/ 1U);
            if (FMS_B.wp_index - 1U > FMS_B.wp_index) {
              qY = 0;
            }

            FMS_B.wp_consume = (uint8_T)qY;
          }
        } else {
          switch (FMS_DW.is_Mission) {
           case FMS_IN_Disarming:
            FMS_DW.is_Mission = FMS_IN_NO_ACTIVE_CHILD_d;
            FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_d;
            FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
            FMS_DW.is_Vehicle = FMS_IN_Disarm;
            FMS_B.state = VehicleState_Disarm;
            break;

           case FMS_IN_Land:
            {
              FMS_B.state = VehicleState_Land;
              if (!FMS_B.LogicalOperator1) {
                FMS_DW.durationCounter_1 = 0;
              }

              if (FMS_DW.durationCounter_1 >= 500) {
                int32_T qY;
                qY = (int32_T)(FMS_B.wp_index + 1U);
                if (FMS_B.wp_index + 1U > 255U) {
                  qY = 255;
                }

                FMS_B.wp_index = (uint8_T)qY;
                FMS_DW.is_Mission = FMS_IN_NextWP;

                /* Inport: '<Root>/Mission_Data' */
                if (FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) {
                  FMS_DW.nav_cmd = FMS_U.Mission_Data.command[FMS_B.wp_index - 1];
                } else {
                  FMS_DW.nav_cmd = (uint16_T)NAV_Cmd_None;
                  qY = (int32_T)(FMS_B.wp_index - /*MW:OvSatOk*/ 1U);
                  if (FMS_B.wp_index - 1U > FMS_B.wp_index) {
                    qY = 0;
                  }

                  FMS_B.wp_consume = (uint8_T)qY;
                }
              }
            }
            break;

           case FMS_IN_Loiter_b:
            FMS_B.state = VehicleState_Hold;
            break;

           case FMS_IN_NextWP:
            if (FMS_DW.nav_cmd == (int32_T)NAV_Cmd_Takeoff) {
              FMS_DW.is_Mission = FMS_IN_Takeoff;
              FMS_B.Cmd_In.cur_waypoint[0] =
                FMS_B.BusConversion_InsertedFor_State.x_R;
              FMS_B.Cmd_In.cur_waypoint[1] =
                FMS_B.BusConversion_InsertedFor_State.y_R;
              FMS_B.Cmd_In.cur_waypoint[2] =
                FMS_B.BusConversion_InsertedFor_State.h_R;

              /* Inport: '<Root>/Mission_Data' */
              lla[0] = (real_T)FMS_U.Mission_Data.x[FMS_B.wp_index - 1] * 1.0E-7;
              lla[1] = (real_T)FMS_U.Mission_Data.y[FMS_B.wp_index - 1] * 1.0E-7;
              lla[2] = -(FMS_U.Mission_Data.z[FMS_B.wp_index - 1] + FMS_DW.home
                         [2]);

              /* Outputs for Function Call SubSystem: '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
              F_VehicleArmAutoMissionLLA2FLAT(lla, FMS_DW.llo, 0.0, 0.0,
                FMS_B.Cmd_In.sp_waypoint,
                &FMS_ConstB.VehicleArmAutoMissionLLA2FLAT);

              /* End of Outputs for SubSystem: '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
              FMS_B.state = VehicleState_Takeoff;
            } else if (FMS_DW.nav_cmd == (int32_T)NAV_Cmd_Waypoint) {
              FMS_DW.is_Mission = FMS_IN_Waypoint;

              /* Inport: '<Root>/Mission_Data' */
              lla[0] = (real_T)FMS_U.Mission_Data.x[FMS_B.wp_index - 1] * 1.0E-7;
              lla[1] = (real_T)FMS_U.Mission_Data.y[FMS_B.wp_index - 1] * 1.0E-7;
              lla[2] = -(FMS_U.Mission_Data.z[FMS_B.wp_index - 1] + FMS_DW.home
                         [2]);

              /* Outputs for Function Call SubSystem: '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
              F_VehicleArmAutoMissionLLA2FLAT(lla, FMS_DW.llo, 0.0, 0.0,
                FMS_B.Cmd_In.sp_waypoint,
                &FMS_ConstB.VehicleArmAutoMissionLLA2FLAT);

              /* End of Outputs for SubSystem: '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
              FMS_B.state = VehicleState_Mission;
            } else if (FMS_DW.nav_cmd == (int32_T)NAV_Cmd_Land) {
              FMS_DW.durationCounter_1 = 0;
              FMS_DW.is_Mission = FMS_IN_Land;
              FMS_B.Cmd_In.sp_waypoint[0] =
                FMS_B.BusConversion_InsertedFor_State.x_R;
              FMS_B.Cmd_In.sp_waypoint[1] =
                FMS_B.BusConversion_InsertedFor_State.y_R;
              FMS_B.Cmd_In.sp_waypoint[2] = 0.0F;
              FMS_B.state = VehicleState_Land;
            } else if (FMS_DW.nav_cmd == (int32_T)NAV_Cmd_Return) {
              FMS_DW.is_Mission = FMS_IN_Return;
              FMS_B.Cmd_In.sp_waypoint[0] = FMS_DW.home[0];
              FMS_B.Cmd_In.sp_waypoint[1] = FMS_DW.home[1];
              FMS_B.Cmd_In.sp_waypoint[2] =
                FMS_B.BusConversion_InsertedFor_State.h_R;
              FMS_B.state = VehicleState_Return;
            } else if (FMS_B.LogicalOperator1) {
              FMS_DW.is_Mission = FMS_IN_Disarming;
            } else {
              FMS_DW.is_Mission = FMS_IN_Loiter_b;
              FMS_B.state = VehicleState_Hold;
            }
            break;

           case FMS_IN_Return:
            FMS_B.state = VehicleState_Return;
            if (FMS_B.BusConversion_InsertedFor_State.x_R -
                FMS_B.Cmd_In.sp_waypoint[0] <= 1.0F) {
              FMS_DW.durationCounter_1 = 0;
              FMS_DW.is_Mission = FMS_IN_Land;
              FMS_B.Cmd_In.sp_waypoint[0] =
                FMS_B.BusConversion_InsertedFor_State.x_R;
              FMS_B.Cmd_In.sp_waypoint[1] =
                FMS_B.BusConversion_InsertedFor_State.y_R;
              FMS_B.Cmd_In.sp_waypoint[2] = 0.0F;
              FMS_B.state = VehicleState_Land;
            }
            break;

           case FMS_IN_Takeoff:
            {
              FMS_B.state = VehicleState_Takeoff;
              if (FMS_B.BusConversion_InsertedFor_State.x_R -
                  FMS_B.Cmd_In.sp_waypoint[0] <= 1.0F) {
                int32_T qY;
                qY = (int32_T)(FMS_B.wp_index + 1U);
                if (FMS_B.wp_index + 1U > 255U) {
                  qY = 255;
                }

                FMS_B.wp_index = (uint8_T)qY;
                FMS_DW.is_Mission = FMS_IN_NextWP;

                /* Inport: '<Root>/Mission_Data' */
                if (FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) {
                  FMS_DW.nav_cmd = FMS_U.Mission_Data.command[FMS_B.wp_index - 1];
                } else {
                  FMS_DW.nav_cmd = (uint16_T)NAV_Cmd_None;
                  qY = (int32_T)(FMS_B.wp_index - /*MW:OvSatOk*/ 1U);
                  if (FMS_B.wp_index - 1U > FMS_B.wp_index) {
                    qY = 0;
                  }

                  FMS_B.wp_consume = (uint8_T)qY;
                }
              }
            }
            break;

           case FMS_IN_Waypoint:
            {
              FMS_B.state = VehicleState_Mission;

              /* Constant: '<Root>/ACCEPT_R' */
              if (FMS_B.BusConversion_InsertedFor_State.x_R -
                  FMS_B.Cmd_In.sp_waypoint[0] <= FMS_PARAM.ACCEPT_R) {
                int32_T qY;
                FMS_B.Cmd_In.cur_waypoint[0] = FMS_B.Cmd_In.sp_waypoint[0];
                FMS_B.Cmd_In.cur_waypoint[1] = FMS_B.Cmd_In.sp_waypoint[1];
                FMS_B.Cmd_In.cur_waypoint[2] = FMS_B.Cmd_In.sp_waypoint[2];
                qY = (int32_T)(FMS_B.wp_index + 1U);
                if (FMS_B.wp_index + 1U > 255U) {
                  qY = 255;
                }

                FMS_B.wp_index = (uint8_T)qY;
                FMS_DW.is_Mission = FMS_IN_NextWP;

                /* Inport: '<Root>/Mission_Data' */
                if (FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) {
                  FMS_DW.nav_cmd = FMS_U.Mission_Data.command[FMS_B.wp_index - 1];
                } else {
                  FMS_DW.nav_cmd = (uint16_T)NAV_Cmd_None;
                  qY = (int32_T)(FMS_B.wp_index - /*MW:OvSatOk*/ 1U);
                  if (FMS_B.wp_index - 1U > FMS_B.wp_index) {
                    qY = 0;
                  }

                  FMS_B.wp_consume = (uint8_T)qY;
                }
              }

              /* End of Constant: '<Root>/ACCEPT_R' */
            }
            break;
          }
        }
      }
      break;

     case FMS_IN_Offboard_l:
      switch (FMS_DW.is_Offboard) {
       case FMS_IN_Loiter:
        FMS_B.state = VehicleState_Hold;
        if (FMS_B.LogicalOperator) {
          FMS_DW.is_Offboard = FMS_IN_Run;
          FMS_B.state = VehicleState_Offboard;
        }
        break;

       case FMS_IN_Run:
        FMS_B.state = VehicleState_Offboard;
        if (!FMS_B.LogicalOperator) {
          FMS_DW.is_Offboard = FMS_IN_Loiter;
          FMS_B.state = VehicleState_Hold;
        }
        break;
      }
      break;
    }
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_enter_internal_Arm(void)
{
  switch (FMS_B.target_mode) {
   case PilotMode_Offboard:
    FMS_DW.is_Arm = FMS_IN_Auto;
    FMS_DW.is_Auto = FMS_IN_Offboard_l;
    FMS_B.Cmd_In.offboard_psi_0 = FMS_B.BusConversion_InsertedFor_State.psi;
    if (FMS_B.LogicalOperator) {
      FMS_DW.is_Offboard = FMS_IN_Run;
      FMS_B.state = VehicleState_Offboard;
    } else {
      FMS_DW.is_Offboard = FMS_IN_Loiter;
      FMS_B.state = VehicleState_Hold;
    }
    break;

   case PilotMode_Mission:
    {
      FMS_DW.is_Arm = FMS_IN_Auto;
      FMS_DW.is_Auto = FMS_IN_Mission_a;
      FMS_DW.llo[0] = FMS_B.BusConversion_InsertedFor_State.lat_0 *
        57.295779513082323;
      FMS_DW.llo[1] = FMS_B.BusConversion_InsertedFor_State.lon_0 *
        57.295779513082323;
      FMS_DW.is_Mission = FMS_IN_NextWP;

      /* Inport: '<Root>/Mission_Data' */
      if (FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) {
        FMS_DW.nav_cmd = FMS_U.Mission_Data.command[FMS_B.wp_index - 1];
      } else {
        int32_T qY;
        FMS_DW.nav_cmd = (uint16_T)NAV_Cmd_None;
        qY = (int32_T)(FMS_B.wp_index - /*MW:OvSatOk*/ 1U);
        if (FMS_B.wp_index - 1U > FMS_B.wp_index) {
          qY = 0;
        }

        FMS_B.wp_consume = (uint8_T)qY;
      }

      /* End of Inport: '<Root>/Mission_Data' */
    }
    break;

   case PilotMode_Stabilize:
    FMS_DW.is_Arm = FMS_IN_Stabilize;
    FMS_B.state = VehicleState_Stabilize;
    break;

   case PilotMode_Position:
    FMS_DW.is_Arm = FMS_IN_Position_m;
    FMS_B.state = VehicleState_Position;
    break;

   case PilotMode_Manual:
    FMS_DW.is_Arm = FMS_IN_Manual_k;
    FMS_B.state = VehicleState_Manual;
    break;

   default:
    FMS_DW.is_Arm = FMS_IN_InvalidMode;
    break;
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_Arm(const PilotMode *mode_prev)
{
  if (!FMS_B.LogicalOperator1) {
    FMS_DW.durationCounter_1_i = 0;
  }

  if ((FMS_DW.durationCounter_1_i >= 75000) && (FMS_B.target_mode !=
       PilotMode_Mission)) {
    if (FMS_DW.is_Arm == FMS_IN_Auto) {
      FMS_exit_internal_Auto();
      FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
    } else {
      FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
    }

    FMS_DW.is_Vehicle = FMS_IN_Disarm;
    FMS_B.state = VehicleState_Disarm;
  } else if ((*mode_prev != FMS_DW.mode_start) && (FMS_B.target_mode !=
              PilotMode_None)) {
    switch (FMS_B.target_mode) {
     case PilotMode_Offboard:
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
      }

      FMS_DW.is_Arm = FMS_IN_Auto;
      FMS_DW.is_Auto = FMS_IN_Offboard_l;
      FMS_B.Cmd_In.offboard_psi_0 = FMS_B.BusConversion_InsertedFor_State.psi;
      if (FMS_B.LogicalOperator) {
        FMS_DW.is_Offboard = FMS_IN_Run;
        FMS_B.state = VehicleState_Offboard;
      } else {
        FMS_DW.is_Offboard = FMS_IN_Loiter;
        FMS_B.state = VehicleState_Hold;
      }
      break;

     case PilotMode_Mission:
      {
        if (FMS_DW.is_Arm == FMS_IN_Auto) {
          FMS_exit_internal_Auto();
        }

        FMS_DW.is_Arm = FMS_IN_Auto;
        FMS_DW.is_Auto = FMS_IN_Mission_a;
        FMS_DW.llo[0] = FMS_B.BusConversion_InsertedFor_State.lat_0 *
          57.295779513082323;
        FMS_DW.llo[1] = FMS_B.BusConversion_InsertedFor_State.lon_0 *
          57.295779513082323;
        FMS_DW.is_Mission = FMS_IN_NextWP;

        /* Inport: '<Root>/Mission_Data' */
        if (FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) {
          FMS_DW.nav_cmd = FMS_U.Mission_Data.command[FMS_B.wp_index - 1];
        } else {
          int32_T qY;
          FMS_DW.nav_cmd = (uint16_T)NAV_Cmd_None;
          qY = (int32_T)(FMS_B.wp_index - /*MW:OvSatOk*/ 1U);
          if (FMS_B.wp_index - 1U > FMS_B.wp_index) {
            qY = 0;
          }

          FMS_B.wp_consume = (uint8_T)qY;
        }

        /* End of Inport: '<Root>/Mission_Data' */
      }
      break;

     case PilotMode_Stabilize:
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
      }

      FMS_DW.is_Arm = FMS_IN_Stabilize;
      FMS_B.state = VehicleState_Stabilize;
      break;

     case PilotMode_Position:
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
      }

      FMS_DW.is_Arm = FMS_IN_Position_m;
      FMS_B.state = VehicleState_Position;
      break;

     case PilotMode_Manual:
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
      }

      FMS_DW.is_Arm = FMS_IN_Manual_k;
      FMS_B.state = VehicleState_Manual;
      break;

     default:
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
      }

      FMS_DW.is_Arm = FMS_IN_InvalidMode;
      break;
    }
  } else {
    boolean_T c_out;
    if (FMS_sf_msg_pop_M()) {
      c_out = (FMS_DW.M_msgReservedData == FMS_Cmd_Return);
    } else {
      c_out = false;
    }

    if (c_out) {
      FMS_B.Cmd_In.sp_waypoint[0] = FMS_DW.home[0];
      FMS_B.Cmd_In.sp_waypoint[1] = FMS_DW.home[1];
      FMS_B.Cmd_In.sp_waypoint[2] = FMS_B.BusConversion_InsertedFor_State.h_R;
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
      }

      FMS_DW.durationCounter_1_o = 0;
      FMS_DW.is_Arm = FMS_IN_Return;
      FMS_B.state = VehicleState_Return;
    } else {
      switch (FMS_DW.is_Arm) {
       case FMS_IN_Auto:
        FMS_Auto();
        break;

       case FMS_IN_InvalidMode:
        FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
        FMS_DW.is_Vehicle = FMS_IN_Disarm;
        FMS_B.state = VehicleState_Disarm;
        break;

       case FMS_IN_Manual_k:
        FMS_B.state = VehicleState_Manual;
        break;

       case FMS_IN_Position_m:
        FMS_B.state = VehicleState_Position;
        break;

       case FMS_IN_Return:
        {
          FMS_B.state = VehicleState_Return;
          if (!FMS_B.LogicalOperator1) {
            FMS_DW.durationCounter_1_o = 0;
          }

          if (FMS_DW.durationCounter_1_o >= 500) {
            real32_T absxk;
            real32_T scale;
            real32_T t;
            real32_T y;
            scale = 1.29246971E-26F;
            absxk = fabsf(FMS_B.BusConversion_InsertedFor_State.x_R -
                          FMS_DW.home[0]);
            if (absxk > 1.29246971E-26F) {
              y = 1.0F;
              scale = absxk;
            } else {
              t = absxk / 1.29246971E-26F;
              y = t * t;
            }

            absxk = fabsf(FMS_B.BusConversion_InsertedFor_State.y_R -
                          FMS_DW.home[1]);
            if (absxk > scale) {
              t = scale / absxk;
              y = y * t * t + 1.0F;
              scale = absxk;
            } else {
              t = absxk / scale;
              y += t * t;
            }

            /* Constant: '<Root>/ACCEPT_R' */
            c_out = (scale * sqrtf(y) <= FMS_PARAM.ACCEPT_R);
          } else {
            c_out = false;
          }

          if (c_out) {
            FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
            FMS_DW.is_Vehicle = FMS_IN_Disarm;
            FMS_B.state = VehicleState_Disarm;
          }
        }
        break;

       case FMS_IN_Stabilize:
        FMS_B.state = VehicleState_Stabilize;
        if (FMS_sf_msg_pop_M()) {
          c_out = (FMS_DW.M_msgReservedData == FMS_Cmd_Continue);
        } else {
          c_out = false;
        }

        if (c_out) {
          FMS_enter_internal_Arm();
        }
        break;
      }
    }
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_Vehicle(const int32_T *sfEvent, const PilotMode *mode_prev)
{
  boolean_T out;
  if (FMS_DW.mission_timestamp_prev != FMS_DW.mission_timestamp_start) {
    FMS_B.wp_consume = 0U;
    FMS_B.wp_index = 1U;
  }

  if (FMS_sf_msg_pop_M()) {
    out = (FMS_DW.M_msgReservedData == FMS_Cmd_Disarm);
  } else {
    out = false;
  }

  if (out) {
    if (FMS_DW.is_Vehicle == FMS_IN_Arm) {
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
        FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
      } else {
        FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
      }
    }

    FMS_DW.is_Vehicle = FMS_IN_Disarm;
    FMS_B.state = VehicleState_Disarm;
  } else {
    switch (FMS_DW.is_Vehicle) {
     case FMS_IN_Arm:
      FMS_Arm(mode_prev);
      break;

     case FMS_IN_Disarm:
      FMS_B.state = VehicleState_Disarm;
      if (FMS_sf_msg_pop_M()) {
        out = (FMS_DW.M_msgReservedData == FMS_Cmd_PreArm);
      } else {
        out = false;
      }

      if (out) {
        FMS_DW.is_Vehicle = FMS_IN_Standby;
        FMS_DW.temporalCounter_i1 = 0U;
        FMS_DW.home[0] = FMS_B.BusConversion_InsertedFor_State.x_R;
        FMS_DW.home[1] = FMS_B.BusConversion_InsertedFor_State.y_R;
        FMS_DW.home[2] = FMS_B.BusConversion_InsertedFor_State.h_R;
        FMS_B.state = VehicleState_Standby;
      }
      break;

     case FMS_IN_Standby:
      FMS_B.state = VehicleState_Standby;
      if (FMS_B.target_mode != PilotMode_None) {
        FMS_DW.durationCounter_1_i = 0;
        FMS_DW.is_Vehicle = FMS_IN_Arm;
        FMS_enter_internal_Arm();
      } else if ((FMS_DW.temporalCounter_i1 >= 2500U) || (*sfEvent ==
                  FMS_event_DisarmEvent)) {
        FMS_DW.is_Vehicle = FMS_IN_Disarm;
        FMS_B.state = VehicleState_Disarm;
      }
      break;
    }
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_sf_msg_discard_M(void)
{
  FMS_DW.M_isValid = false;
}

real32_T rt_remf(real32_T u0, real32_T u1)
{
  real32_T y;
  if ((u1 != 0.0F) && (u1 != truncf(u1))) {
    real32_T q;
    q = fabsf(u0 / u1);
    if (fabsf(q - floorf(q + 0.5F)) <= FLT_EPSILON * q) {
      y = 0.0F;
    } else {
      y = fmodf(u0, u1);
    }
  } else {
    y = fmodf(u0, u1);
  }

  return y;
}

void FMS_initQueue(Queue_FMS_Cmd *q, QueuePolicy_T policy, int32_T capacity,
                   Msg_FMS_Cmd *qPool)
{
  q->fPolicy = policy;
  q->fCapacity = capacity;
  q->fHead = -1;
  q->fTail = -1;
  q->fArray = qPool;
}

/* Function for Chart: '<Root>/State Machine' */
static void initialize_msg_local_queues_for(void)
{
  FMS_initQueue(&FMS_DW.Queue, MSG_FIFO_QUEUE, 10, &FMS_DW.Msg[1]);
}

/* Model step function */
void FMS_step(void)
{
  int32_T sfEvent;
  real32_T rtb_Transpose[9];
  real32_T rtb_MathFunction_a[3];
  real32_T rtb_MatrixConcatenate3[3];
  real32_T rtb_Multiply[3];
  real32_T rtb_Sum2_n[3];
  real32_T rtb_Transpose_0[3];
  real32_T rtb_Divide_od[2];
  real32_T rtb_MathFunction_ab[2];
  real32_T rtb_MathFunction_f[2];
  real32_T rtb_MathFunction_h[2];
  real32_T rtb_TmpSignalConversionAtMat_bs[2];
  real32_T rtb_Divide_o_idx_0;
  real32_T rtb_Divide_o_idx_1;
  real32_T rtb_Divide_o_idx_2;
  real32_T rtb_MathFunction1;
  real32_T rtb_Rem_h;
  real32_T rtb_Rem_j;
  real32_T rtb_Square2;
  real32_T rtb_Transpose_tmp;
  real32_T rtb_Transpose_tmp_0;
  real32_T rtb_Transpose_tmp_1;
  real32_T rtb_Transpose_tmp_2;
  real32_T rtb_u_b;
  uint32_T qY;
  uint32_T tmp;
  uint32_T tmp_0;
  uint32_T tmp_1;
  uint16_T rtb_SquareRoot;
  int8_T rtPrevAction;
  FMS_Cmd Switch1;
  FMS_Cmd cmd_prev;
  MotionState rtb_state_ee;
  PilotMode mode_prev;

  /* Sqrt: '<S20>/Sqrt' incorporates:
   *  Inport: '<Root>/INS_Out'
   *  Math: '<S20>/Square'
   *  Sum: '<S20>/Sum of Elements'
   */
  rtb_Square2 = sqrtf(((FMS_U.INS_Out.quat[0] * FMS_U.INS_Out.quat[0] +
                        FMS_U.INS_Out.quat[1] * FMS_U.INS_Out.quat[1]) +
                       FMS_U.INS_Out.quat[2] * FMS_U.INS_Out.quat[2]) +
                      FMS_U.INS_Out.quat[3] * FMS_U.INS_Out.quat[3]);

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_Divide_o_idx_0 = FMS_U.INS_Out.quat[0] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  qY = (uint32_T)FMS_U.Control_Out.actuator_cmd[0] *
    FMS_U.Control_Out.actuator_cmd[0];
  if (qY > 65535U) {
    qY = 65535U;
  }

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_Divide_o_idx_1 = FMS_U.INS_Out.quat[1] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  tmp_1 = (uint32_T)FMS_U.Control_Out.actuator_cmd[1] *
    FMS_U.Control_Out.actuator_cmd[1];
  if (tmp_1 > 65535U) {
    tmp_1 = 65535U;
  }

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_Divide_o_idx_2 = FMS_U.INS_Out.quat[2] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  tmp_0 = (uint32_T)FMS_U.Control_Out.actuator_cmd[2] *
    FMS_U.Control_Out.actuator_cmd[2];
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_MathFunction1 = FMS_U.INS_Out.quat[3] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  tmp = (uint32_T)FMS_U.Control_Out.actuator_cmd[3] *
    FMS_U.Control_Out.actuator_cmd[3];
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  /* Math: '<S17>/Square' incorporates:
   *  Math: '<S18>/Square'
   *  Math: '<S19>/Square'
   */
  rtb_Square2 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_0;

  /* Math: '<S17>/Square2' incorporates:
   *  Math: '<S18>/Square2'
   *  Math: '<S19>/Square2'
   */
  rtb_u_b = rtb_Divide_o_idx_2 * rtb_Divide_o_idx_2;

  /* Math: '<S17>/Square1' incorporates:
   *  Math: '<S18>/Square1'
   *  Math: '<S19>/Square1'
   */
  rtb_Rem_h = rtb_Divide_o_idx_1 * rtb_Divide_o_idx_1;

  /* Math: '<S17>/Square3' incorporates:
   *  Math: '<S18>/Square3'
   *  Math: '<S19>/Square3'
   */
  rtb_Rem_j = rtb_MathFunction1 * rtb_MathFunction1;

  /* Sum: '<S17>/Subtract' incorporates:
   *  Math: '<S17>/Square'
   *  Math: '<S17>/Square1'
   *  Math: '<S17>/Square2'
   *  Math: '<S17>/Square3'
   *  Sum: '<S17>/Add'
   *  Sum: '<S17>/Add1'
   */
  rtb_Transpose[0] = (rtb_Square2 + rtb_Rem_h) - (rtb_u_b + rtb_Rem_j);

  /* Product: '<S17>/Multiply' incorporates:
   *  Product: '<S18>/Multiply'
   */
  rtb_Transpose_tmp = rtb_Divide_o_idx_1 * rtb_Divide_o_idx_2;

  /* Product: '<S17>/Multiply1' incorporates:
   *  Product: '<S18>/Multiply1'
   */
  rtb_Transpose_tmp_0 = rtb_Divide_o_idx_0 * rtb_MathFunction1;

  /* Gain: '<S17>/Gain' incorporates:
   *  Product: '<S17>/Multiply'
   *  Product: '<S17>/Multiply1'
   *  Sum: '<S17>/Subtract1'
   */
  rtb_Transpose[1] = (rtb_Transpose_tmp - rtb_Transpose_tmp_0) * 2.0F;

  /* Product: '<S17>/Multiply2' incorporates:
   *  Product: '<S19>/Multiply'
   */
  rtb_Transpose_tmp_1 = rtb_Divide_o_idx_1 * rtb_MathFunction1;

  /* Product: '<S17>/Multiply3' incorporates:
   *  Product: '<S19>/Multiply1'
   */
  rtb_Transpose_tmp_2 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_2;

  /* Gain: '<S17>/Gain1' incorporates:
   *  Product: '<S17>/Multiply2'
   *  Product: '<S17>/Multiply3'
   *  Sum: '<S17>/Add2'
   */
  rtb_Transpose[2] = (rtb_Transpose_tmp_1 + rtb_Transpose_tmp_2) * 2.0F;

  /* Gain: '<S18>/Gain' incorporates:
   *  Sum: '<S18>/Add3'
   */
  rtb_Transpose[3] = (rtb_Transpose_tmp + rtb_Transpose_tmp_0) * 2.0F;

  /* Sum: '<S18>/Subtract' incorporates:
   *  Sum: '<S18>/Add'
   *  Sum: '<S18>/Add1'
   */
  rtb_Transpose[4] = (rtb_Square2 + rtb_u_b) - (rtb_Rem_h + rtb_Rem_j);

  /* Product: '<S18>/Multiply2' incorporates:
   *  Product: '<S19>/Multiply2'
   */
  rtb_Transpose_tmp = rtb_Divide_o_idx_2 * rtb_MathFunction1;

  /* Product: '<S18>/Multiply3' incorporates:
   *  Product: '<S19>/Multiply3'
   */
  rtb_Transpose_tmp_0 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_1;

  /* Gain: '<S18>/Gain1' incorporates:
   *  Product: '<S18>/Multiply2'
   *  Product: '<S18>/Multiply3'
   *  Sum: '<S18>/Subtract1'
   */
  rtb_Transpose[5] = (rtb_Transpose_tmp - rtb_Transpose_tmp_0) * 2.0F;

  /* Gain: '<S19>/Gain' incorporates:
   *  Sum: '<S19>/Subtract2'
   */
  rtb_Transpose[6] = (rtb_Transpose_tmp_1 - rtb_Transpose_tmp_2) * 2.0F;

  /* Gain: '<S19>/Gain1' incorporates:
   *  Sum: '<S19>/Add2'
   */
  rtb_Transpose[7] = (rtb_Transpose_tmp + rtb_Transpose_tmp_0) * 2.0F;

  /* Sum: '<S19>/Subtract' incorporates:
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_Transpose[8] = (rtb_Square2 + rtb_Rem_j) - (rtb_Rem_h + rtb_u_b);

  /* Product: '<S2>/Multiply' incorporates:
   *  Inport: '<Root>/INS_Out'
   *  Math: '<S2>/Transpose'
   *  SignalConversion generated from: '<S2>/Matrix Concatenate3'
   * */
  for (sfEvent = 0; sfEvent < 3; sfEvent++) {
    rtb_Multiply[sfEvent] = (rtb_Transpose[3 * sfEvent + 1] * FMS_U.INS_Out.ay +
      rtb_Transpose[3 * sfEvent] * FMS_U.INS_Out.ax) + rtb_Transpose[3 * sfEvent
      + 2] * FMS_U.INS_Out.az;
  }

  /* End of Product: '<S2>/Multiply' */

  /* DiscreteIntegrator: '<S12>/Discrete-Time Integrator5' */
  if (FMS_DW.DiscreteTimeIntegrator5_IC_LOAD != 0) {
    FMS_DW.DiscreteTimeIntegrator5_DSTATE[0] = rtb_Multiply[0];
    FMS_DW.DiscreteTimeIntegrator5_DSTATE[1] = rtb_Multiply[1];
    FMS_DW.DiscreteTimeIntegrator5_DSTATE[2] = rtb_Multiply[2];
  }

  /* Sqrt: '<S2>/Square Root' incorporates:
   *  Math: '<S2>/Square'
   *  Product: '<S2>/Divide'
   *  Sum: '<S2>/Sum of Elements'
   */
  rtb_SquareRoot = rt_sqrt_Uu16_Yu16_Iu32_f_s((uint16_T)((uint32_T)(uint16_T)
    ((((uint32_T)(uint16_T)qY + (uint16_T)tmp_1) + (uint16_T)tmp_0) + (uint16_T)
     tmp) >> 2));

  /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator5' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion'
   */
  if (FMS_DW.DiscreteTimeIntegrator5_IC_LO_g != 0) {
    FMS_DW.DiscreteTimeIntegrator5_DSTAT_j = rtb_SquareRoot;
  }

  /* Logic: '<S2>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S14>/Lower Limit'
   *  Constant: '<S14>/Upper Limit'
   *  DiscreteIntegrator: '<S12>/Discrete-Time Integrator5'
   *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator5'
   *  Logic: '<S14>/AND'
   *  Logic: '<S2>/Logical Operator'
   *  RelationalOperator: '<S11>/Compare'
   *  RelationalOperator: '<S14>/Lower Test'
   *  RelationalOperator: '<S14>/Upper Test'
   */
  FMS_B.LogicalOperator1 = ((FMS_DW.DiscreteTimeIntegrator5_DSTATE[0] >= -0.5F) &&
    (FMS_DW.DiscreteTimeIntegrator5_DSTATE[0] <= 0.5F) &&
    ((FMS_DW.DiscreteTimeIntegrator5_DSTATE[1] >= -0.5F) &&
     (FMS_DW.DiscreteTimeIntegrator5_DSTATE[1] <= 0.5F)) &&
    ((FMS_DW.DiscreteTimeIntegrator5_DSTATE[2] >= -10.306F) &&
     (FMS_DW.DiscreteTimeIntegrator5_DSTATE[2] <= -9.306F)) &&
    (FMS_DW.DiscreteTimeIntegrator5_DSTAT_j < 1250.0F));

  /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/Pilot_Cmd'
   *  RelationalOperator: '<S25>/FixPt Relational Operator'
   *  UnitDelay: '<S25>/Delay Input1'
   *
   * Block description for '<S25>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if (FMS_U.Pilot_Cmd.timestamp != FMS_DW.DelayInput1_DSTATE) {
    FMS_DW.DiscreteTimeIntegrator1_DSTATE = 0U;
  }

  /* Switch: '<S23>/Switch' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S28>/Constant'
   *  Constant: '<S29>/Constant'
   *  DataTypeConversion: '<S23>/Data Type Conversion2'
   *  Delay: '<S23>/Delay'
   *  DiscreteIntegrator: '<S21>/Discrete-Time Integrator1'
   *  Inport: '<Root>/GCS_Cmd'
   *  Inport: '<Root>/Pilot_Cmd'
   *  Logic: '<S23>/Logical Operator'
   *  Logic: '<S23>/Logical Operator1'
   *  RelationalOperator: '<S24>/Compare'
   *  RelationalOperator: '<S28>/Compare'
   *  RelationalOperator: '<S29>/Compare'
   *  RelationalOperator: '<S30>/FixPt Relational Operator'
   *  Switch: '<S23>/Switch1'
   *  UnitDelay: '<S30>/Delay Input1'
   *
   * Block description for '<S30>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if ((FMS_U.Pilot_Cmd.mode != 0U) && (FMS_DW.DiscreteTimeIntegrator1_DSTATE <
       500U)) {
    FMS_DW.Delay_DSTATE_c = (PilotMode)FMS_U.Pilot_Cmd.mode;
  } else if ((FMS_U.GCS_Cmd.mode != FMS_DW.DelayInput1_DSTATE_f) &&
             (FMS_U.GCS_Cmd.mode != 0U)) {
    /* Delay: '<S23>/Delay' incorporates:
     *  DataTypeConversion: '<S23>/Data Type Conversion1'
     *  Inport: '<Root>/GCS_Cmd'
     *  Switch: '<S23>/Switch1'
     */
    FMS_DW.Delay_DSTATE_c = (PilotMode)FMS_U.GCS_Cmd.mode;
  }

  /* End of Switch: '<S23>/Switch' */

  /* Chart: '<Root>/SafeMode' incorporates:
   *  Delay: '<S23>/Delay'
   *  Inport: '<Root>/INS_Out'
   */
  if (FMS_DW.is_active_c3_FMS == 0U) {
    FMS_DW.is_active_c3_FMS = 1U;
    switch (FMS_DW.Delay_DSTATE_c) {
     case PilotMode_Manual:
      FMS_DW.is_c3_FMS = FMS_IN_Manual;
      break;

     case PilotMode_Stabilize:
      FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
      break;

     case PilotMode_Position:
      FMS_DW.is_c3_FMS = FMS_IN_Position;
      break;

     case PilotMode_Mission:
      FMS_DW.is_c3_FMS = FMS_IN_Mission;
      break;

     case PilotMode_Offboard:
      FMS_DW.is_c3_FMS = FMS_IN_Offboard;
      break;

     default:
      FMS_DW.is_c3_FMS = FMS_IN_Other;
      break;
    }
  } else {
    switch (FMS_DW.is_c3_FMS) {
     case FMS_IN_Manual:
      FMS_B.target_mode = PilotMode_Manual;
      switch (FMS_DW.Delay_DSTATE_c) {
       case PilotMode_Manual:
        FMS_DW.is_c3_FMS = FMS_IN_Manual;
        break;

       case PilotMode_Stabilize:
        FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
        break;

       case PilotMode_Position:
        FMS_DW.is_c3_FMS = FMS_IN_Position;
        break;

       case PilotMode_Mission:
        FMS_DW.is_c3_FMS = FMS_IN_Mission;
        break;

       case PilotMode_Offboard:
        FMS_DW.is_c3_FMS = FMS_IN_Offboard;
        break;

       default:
        FMS_DW.is_c3_FMS = FMS_IN_Other;
        break;
      }
      break;

     case FMS_IN_Mission:
      if (((FMS_U.INS_Out.flag & 4U) != 0U) && ((FMS_U.INS_Out.flag & 64U) != 0U)
          && ((FMS_U.INS_Out.flag & 128U) != 0U)) {
        FMS_B.target_mode = PilotMode_Mission;
        switch (FMS_DW.Delay_DSTATE_c) {
         case PilotMode_Manual:
          FMS_DW.is_c3_FMS = FMS_IN_Manual;
          break;

         case PilotMode_Stabilize:
          FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
          break;

         case PilotMode_Position:
          FMS_DW.is_c3_FMS = FMS_IN_Position;
          break;

         case PilotMode_Mission:
          FMS_DW.is_c3_FMS = FMS_IN_Mission;
          break;

         case PilotMode_Offboard:
          FMS_DW.is_c3_FMS = FMS_IN_Offboard;
          break;

         default:
          FMS_DW.is_c3_FMS = FMS_IN_Other;
          break;
        }
      } else {
        FMS_DW.is_c3_FMS = FMS_IN_Position;
      }
      break;

     case FMS_IN_Offboard:
      if (((FMS_U.INS_Out.flag & 4U) != 0U) && ((FMS_U.INS_Out.flag & 64U) != 0U)
          && ((FMS_U.INS_Out.flag & 128U) != 0U)) {
        FMS_B.target_mode = PilotMode_Offboard;
        switch (FMS_DW.Delay_DSTATE_c) {
         case PilotMode_Manual:
          FMS_DW.is_c3_FMS = FMS_IN_Manual;
          break;

         case PilotMode_Stabilize:
          FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
          break;

         case PilotMode_Position:
          FMS_DW.is_c3_FMS = FMS_IN_Position;
          break;

         case PilotMode_Mission:
          FMS_DW.is_c3_FMS = FMS_IN_Mission;
          break;

         case PilotMode_Offboard:
          FMS_DW.is_c3_FMS = FMS_IN_Offboard;
          break;

         default:
          FMS_DW.is_c3_FMS = FMS_IN_Other;
          break;
        }
      } else {
        FMS_DW.is_c3_FMS = FMS_IN_Position;
      }
      break;

     case FMS_IN_Other:
      FMS_B.target_mode = FMS_DW.Delay_DSTATE_c;
      switch (FMS_DW.Delay_DSTATE_c) {
       case PilotMode_Manual:
        FMS_DW.is_c3_FMS = FMS_IN_Manual;
        break;

       case PilotMode_Stabilize:
        FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
        break;

       case PilotMode_Position:
        FMS_DW.is_c3_FMS = FMS_IN_Position;
        break;

       case PilotMode_Mission:
        FMS_DW.is_c3_FMS = FMS_IN_Mission;
        break;

       case PilotMode_Offboard:
        FMS_DW.is_c3_FMS = FMS_IN_Offboard;
        break;

       default:
        FMS_DW.is_c3_FMS = FMS_IN_Other;
        break;
      }
      break;

     case FMS_IN_Position:
      if (((FMS_U.INS_Out.flag & 4U) != 0U) && ((FMS_U.INS_Out.flag & 64U) != 0U)
          && ((FMS_U.INS_Out.flag & 128U) != 0U)) {
        FMS_B.target_mode = PilotMode_Position;
        switch (FMS_DW.Delay_DSTATE_c) {
         case PilotMode_Manual:
          FMS_DW.is_c3_FMS = FMS_IN_Manual;
          break;

         case PilotMode_Stabilize:
          FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
          break;

         case PilotMode_Position:
          FMS_DW.is_c3_FMS = FMS_IN_Position;
          break;

         case PilotMode_Mission:
          FMS_DW.is_c3_FMS = FMS_IN_Mission;
          break;

         case PilotMode_Offboard:
          FMS_DW.is_c3_FMS = FMS_IN_Offboard;
          break;

         default:
          FMS_DW.is_c3_FMS = FMS_IN_Other;
          break;
        }
      } else {
        FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
      }
      break;

     default:
      /* case IN_Stabilize: */
      if ((FMS_U.INS_Out.flag & 4U) != 0U) {
        FMS_B.target_mode = PilotMode_Stabilize;
        switch (FMS_DW.Delay_DSTATE_c) {
         case PilotMode_Manual:
          FMS_DW.is_c3_FMS = FMS_IN_Manual;
          break;

         case PilotMode_Stabilize:
          FMS_DW.is_c3_FMS = FMS_IN_Stabilize;
          break;

         case PilotMode_Position:
          FMS_DW.is_c3_FMS = FMS_IN_Position;
          break;

         case PilotMode_Mission:
          FMS_DW.is_c3_FMS = FMS_IN_Mission;
          break;

         case PilotMode_Offboard:
          FMS_DW.is_c3_FMS = FMS_IN_Offboard;
          break;

         default:
          FMS_DW.is_c3_FMS = FMS_IN_Other;
          break;
        }
      } else {
        FMS_DW.is_c3_FMS = FMS_IN_Manual;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/SafeMode' */

  /* Switch: '<S22>/Switch1' incorporates:
   *  Inport: '<Root>/GCS_Cmd'
   *  Inport: '<Root>/Pilot_Cmd'
   *  RelationalOperator: '<S26>/FixPt Relational Operator'
   *  RelationalOperator: '<S27>/FixPt Relational Operator'
   *  Switch: '<S22>/Switch2'
   *  UnitDelay: '<S26>/Delay Input1'
   *  UnitDelay: '<S27>/Delay Input1'
   *
   * Block description for '<S26>/Delay Input1':
   *
   *  Store in Global RAM
   *
   * Block description for '<S27>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if (FMS_U.Pilot_Cmd.cmd_1 != FMS_DW.DelayInput1_DSTATE_i) {
    /* Switch: '<S22>/Switch1' incorporates:
     *  DataTypeConversion: '<S22>/Data Type Conversion2'
     */
    Switch1 = (FMS_Cmd)FMS_U.Pilot_Cmd.cmd_1;
  } else if (FMS_U.GCS_Cmd.cmd_1 != FMS_DW.DelayInput1_DSTATE_p) {
    /* Switch: '<S22>/Switch2' incorporates:
     *  DataTypeConversion: '<S22>/Data Type Conversion1'
     *  Inport: '<Root>/GCS_Cmd'
     *  Switch: '<S22>/Switch1'
     */
    Switch1 = (FMS_Cmd)FMS_U.GCS_Cmd.cmd_1;
  } else {
    /* Switch: '<S22>/Switch1' incorporates:
     *  Constant: '<S22>/Constant1'
     *  Switch: '<S22>/Switch2'
     */
    Switch1 = FMS_Cmd_None;
  }

  /* End of Switch: '<S22>/Switch1' */

  /* BusCreator generated from: '<Root>/State Machine' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  FMS_B.BusConversion_InsertedFor_State = FMS_U.INS_Out;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/Auto_Cmd'
   *  RelationalOperator: '<S8>/FixPt Relational Operator'
   *  UnitDelay: '<S8>/Delay Input1'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if (FMS_U.Auto_Cmd.timestamp != FMS_DW.DelayInput1_DSTATE_c) {
    FMS_DW.DiscreteTimeIntegrator_DSTATE = 0U;

    /* Switch: '<S9>/Switch' incorporates:
     *  Constant: '<S9>/Constant1'
     *  Delay: '<S9>/Delay'
     */
    FMS_DW.Delay_DSTATE_o = 1U;
  }

  /* Logic: '<S1>/Logical Operator' incorporates:
   *  Constant: '<S10>/Upper Limit'
   *  Constant: '<S7>/Constant'
   *  Delay: '<S9>/Delay'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Inport: '<Root>/Auto_Cmd'
   *  RelationalOperator: '<S10>/Upper Test'
   *  RelationalOperator: '<S7>/Compare'
   */
  FMS_B.LogicalOperator = ((FMS_DW.DiscreteTimeIntegrator_DSTATE < 500U) &&
    (FMS_DW.Delay_DSTATE_o != 0) && (FMS_U.Auto_Cmd.frame <= 2));

  /* Chart: '<Root>/State Machine' incorporates:
   *  BusCreator generated from: '<Root>/State Machine'
   *  Inport: '<Root>/Mission_Data'
   *  Inport: '<Root>/Pilot_Cmd'
   */
  if (FMS_DW.temporalCounter_i1 < 4095U) {
    FMS_DW.temporalCounter_i1++;
  }

  sfEvent = -1;
  FMS_DW.mission_timestamp_prev = FMS_DW.mission_timestamp_start;
  FMS_DW.mission_timestamp_start = FMS_U.Mission_Data.timestamp;
  cmd_prev = FMS_DW.cmd_start;
  FMS_DW.cmd_start = Switch1;
  mode_prev = FMS_DW.mode_start;
  FMS_DW.mode_start = FMS_B.target_mode;
  FMS_DW.M_isValid = false;
  if (FMS_DW.is_active_c11_FMS == 0U) {
    FMS_DW.mission_timestamp_prev = FMS_U.Mission_Data.timestamp;
    FMS_DW.is_active_c11_FMS = 1U;
    FMS_DW.is_active_Command_Listener = 1U;
    FMS_DW.is_Command_Listener = FMS_IN_Listen;
    FMS_DW.is_active_Combo_Stick = 1U;
    FMS_DW.durationCounter_2 = 0;
    FMS_DW.durationCounter_1_f = 0;
    FMS_DW.is_Combo_Stick = FMS_IN_Idle;
    FMS_DW.is_active_Vehicle = 1U;
    FMS_DW.is_Vehicle = FMS_IN_Disarm;
    FMS_B.state = VehicleState_Disarm;
  } else {
    if (FMS_DW.is_active_Command_Listener != 0U) {
      switch (FMS_DW.is_Command_Listener) {
       case FMS_IN_Check:
        if (FMS_DW.valid_cmd) {
          FMS_DW.is_Command_Listener = FMS_IN_Send;
          FMS_DW.M_msgReservedData = FMS_DW.save_cmd;
          FMS_sf_msg_send_M();
        } else {
          FMS_DW.is_Command_Listener = FMS_IN_Listen;
        }
        break;

       case FMS_IN_Listen:
        if ((cmd_prev != FMS_DW.cmd_start) && (Switch1 != FMS_Cmd_None)) {
          FMS_DW.save_cmd = Switch1;
          FMS_DW.is_Command_Listener = FMS_IN_Check;
          FMS_DW.valid_cmd = FMS_CheckCmdValid(FMS_DW.save_cmd,
            FMS_B.target_mode, FMS_B.BusConversion_InsertedFor_State.flag);
        }
        break;

       case FMS_IN_Send:
        FMS_DW.is_Command_Listener = FMS_IN_Listen;
        break;
      }
    }

    if (FMS_DW.is_active_Combo_Stick != 0U) {
      switch (FMS_DW.is_Combo_Stick) {
       case FMS_IN_Arm:
        if (!FMS_BottomRight(FMS_U.Pilot_Cmd.stick_yaw,
                             FMS_U.Pilot_Cmd.stick_throttle)) {
          FMS_DW.durationCounter_2 = 0;
          FMS_DW.durationCounter_1_f = 0;
          FMS_DW.is_Combo_Stick = FMS_IN_Idle;
        }
        break;

       case FMS_IN_Disarm:
        if (!FMS_BottomLeft(FMS_U.Pilot_Cmd.stick_yaw,
                            FMS_U.Pilot_Cmd.stick_throttle)) {
          FMS_DW.durationCounter_2 = 0;
          FMS_DW.durationCounter_1_f = 0;
          FMS_DW.is_Combo_Stick = FMS_IN_Idle;
        }
        break;

       case FMS_IN_Idle:
        if (!FMS_DW.br) {
          FMS_DW.durationCounter_2 = 0;
        }

        if (FMS_DW.durationCounter_2 > 375) {
          FMS_DW.is_Combo_Stick = FMS_IN_Arm;
          FMS_DW.M_msgReservedData = FMS_Cmd_PreArm;
          FMS_sf_msg_send_M();
        } else {
          if (!FMS_DW.bl) {
            FMS_DW.durationCounter_1_f = 0;
          }

          if (FMS_DW.durationCounter_1_f > 375) {
            FMS_DW.is_Combo_Stick = FMS_IN_Disarm;
            sfEvent = FMS_event_DisarmEvent;
            if (FMS_DW.is_active_Vehicle != 0U) {
              FMS_Vehicle(&sfEvent, &mode_prev);
            }

            sfEvent = -1;
          } else {
            FMS_DW.bl = FMS_BottomLeft(FMS_U.Pilot_Cmd.stick_yaw,
              FMS_U.Pilot_Cmd.stick_throttle);
            if (!FMS_DW.bl) {
              FMS_DW.durationCounter_1_f = 0;
            }

            FMS_DW.br = FMS_BottomRight(FMS_U.Pilot_Cmd.stick_yaw,
              FMS_U.Pilot_Cmd.stick_throttle);
            if (!FMS_DW.br) {
              FMS_DW.durationCounter_2 = 0;
            }
          }
        }
        break;
      }
    }

    if (FMS_DW.is_active_Vehicle != 0U) {
      FMS_Vehicle(&sfEvent, &mode_prev);
    }
  }

  FMS_sf_msg_discard_M();
  if (FMS_B.LogicalOperator1) {
    FMS_DW.durationCounter_1++;
    FMS_DW.durationCounter_1_o++;
    FMS_DW.durationCounter_1_i++;
  } else {
    FMS_DW.durationCounter_1 = 0;
    FMS_DW.durationCounter_1_o = 0;
    FMS_DW.durationCounter_1_i = 0;
  }

  if (FMS_DW.bl) {
    FMS_DW.durationCounter_1_f++;
  } else {
    FMS_DW.durationCounter_1_f = 0;
  }

  if (FMS_DW.br) {
    FMS_DW.durationCounter_2++;
  } else {
    FMS_DW.durationCounter_2 = 0;
  }

  /* End of Chart: '<Root>/State Machine' */

  /* Outputs for Atomic SubSystem: '<Root>/FMS Commander' */
  /* SwitchCase: '<S31>/Switch Case' incorporates:
   *  Outport: '<Root>/FMS_Out'
   *  SignalConversion generated from: '<S32>/Signal Copy6'
   */
  rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem;

  /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
  switch (FMS_B.state) {
   case VehicleState_Disarm:
   case VehicleState_None:
    FMS_DW.SwitchCase_ActiveSubsystem = 0;
    break;

   case VehicleState_Standby:
    FMS_DW.SwitchCase_ActiveSubsystem = 1;
    break;

   default:
    FMS_DW.SwitchCase_ActiveSubsystem = 2;
    break;
  }

  /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
  if ((rtPrevAction != FMS_DW.SwitchCase_ActiveSubsystem) && (rtPrevAction == 2))
  {
    /* Disable for SwitchCase: '<S33>/Switch Case' */
    switch (FMS_DW.SwitchCase_ActiveSubsystem_b) {
     case 0:
      /* Disable for SwitchCase: '<S41>/Switch Case' */
      switch (FMS_DW.SwitchCase_ActiveSubsystem_o) {
       case 0:
       case 1:
       case 4:
        break;

       case 2:
        /* SwitchCase: '<S317>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

        /* SwitchCase: '<S307>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;
        break;

       case 3:
        /* SwitchCase: '<S263>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

        /* SwitchCase: '<S241>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

        /* SwitchCase: '<S251>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;
        break;
      }

      /* SwitchCase: '<S41>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_o = -1;
      break;

     case 1:
      /* SwitchCase: '<S37>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_i = -1;
      break;

     case 2:
      /* SwitchCase: '<S220>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_p = -1;

      /* SwitchCase: '<S208>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_bn = -1;
      break;

     case 3:
      /* SwitchCase: '<S191>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_l = -1;

      /* SwitchCase: '<S178>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_j = -1;
      break;

     case 4:
     case 5:
      break;
    }

    /* SwitchCase: '<S33>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_b = -1;
  }

  switch (FMS_DW.SwitchCase_ActiveSubsystem) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S31>/Disarm' incorporates:
     *  ActionPort: '<S35>/Action Port'
     */
    /* Outport: '<Root>/FMS_Out' incorporates:
     *  BusAssignment: '<S34>/Bus Assignment'
     */
    FMS_Disarm(&FMS_Y.FMS_Out, &FMS_ConstB.Disarm);

    /* End of Outputs for SubSystem: '<S31>/Disarm' */
    break;

   case 1:
    memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

    /* Outputs for IfAction SubSystem: '<S31>/Standby' incorporates:
     *  ActionPort: '<S36>/Action Port'
     */
    /* BusAssignment: '<S36>/Bus Assignment' incorporates:
     *  BusAssignment: '<S34>/Bus Assignment'
     *  Constant: '<S36>/Constant2'
     *  Constant: '<S36>/Constant3'
     *  Outport: '<Root>/FMS_Out'
     */
    FMS_Y.FMS_Out.reset = 1U;
    FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion2_h;
    FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_f;
    FMS_Y.FMS_Out.actuator_cmd[0] = 750U;
    FMS_Y.FMS_Out.actuator_cmd[1] = 10000U;
    FMS_Y.FMS_Out.actuator_cmd[2] = 10000U;
    FMS_Y.FMS_Out.actuator_cmd[3] = 10000U;
    for (sfEvent = 0; sfEvent < 12; sfEvent++) {
      FMS_Y.FMS_Out.actuator_cmd[sfEvent + 4] = 0U;
    }

    /* End of BusAssignment: '<S36>/Bus Assignment' */
    /* End of Outputs for SubSystem: '<S31>/Standby' */
    break;

   default:
    {
      /* Outputs for IfAction SubSystem: '<S31>/Arm' incorporates:
       *  ActionPort: '<S33>/Action Port'
       */
      /* SwitchCase: '<S33>/Switch Case' incorporates:
       *  Outport: '<Root>/FMS_Out'
       */
      rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_b;

      /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
      switch (FMS_B.state) {
       case VehicleState_Takeoff:
       case VehicleState_Land:
       case VehicleState_Return:
       case VehicleState_Hold:
        FMS_DW.SwitchCase_ActiveSubsystem_b = 0;
        break;

       case VehicleState_Offboard:
       case VehicleState_Mission:
        FMS_DW.SwitchCase_ActiveSubsystem_b = 1;
        break;

       case VehicleState_Stabilize:
        FMS_DW.SwitchCase_ActiveSubsystem_b = 2;
        break;

       case VehicleState_Position:
        FMS_DW.SwitchCase_ActiveSubsystem_b = 3;
        break;

       case VehicleState_Manual:
        FMS_DW.SwitchCase_ActiveSubsystem_b = 4;
        break;

       default:
        FMS_DW.SwitchCase_ActiveSubsystem_b = 5;
        break;
      }

      /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
      if (rtPrevAction != FMS_DW.SwitchCase_ActiveSubsystem_b) {
        switch (rtPrevAction) {
         case 0:
          /* Disable for SwitchCase: '<S41>/Switch Case' */
          switch (FMS_DW.SwitchCase_ActiveSubsystem_o) {
           case 0:
           case 1:
           case 4:
            break;

           case 2:
            /* SwitchCase: '<S317>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

            /* SwitchCase: '<S307>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;
            break;

           case 3:
            /* SwitchCase: '<S263>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

            /* SwitchCase: '<S241>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

            /* SwitchCase: '<S251>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;
            break;
          }

          /* SwitchCase: '<S41>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_o = -1;
          break;

         case 1:
          /* SwitchCase: '<S37>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_i = -1;
          break;

         case 2:
          /* SwitchCase: '<S220>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_p = -1;

          /* SwitchCase: '<S208>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_bn = -1;
          break;

         case 3:
          /* SwitchCase: '<S191>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_l = -1;

          /* SwitchCase: '<S178>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_j = -1;
          break;

         case 4:
         case 5:
          break;
        }
      }

      switch (FMS_DW.SwitchCase_ActiveSubsystem_b) {
       case 0:
        /* Outputs for IfAction SubSystem: '<S33>/SubMode' incorporates:
         *  ActionPort: '<S41>/Action Port'
         */
        /* SwitchCase: '<S41>/Switch Case' incorporates:
         *  Math: '<S304>/Square'
         *  Math: '<S339>/Math Function'
         *  Outport: '<Root>/FMS_Out'
         *  Product: '<S298>/Divide'
         *  Product: '<S341>/Divide'
         *  Product: '<S342>/Divide'
         *  Sum: '<S299>/Sum'
         *  Sum: '<S302>/Subtract'
         */
        rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_o;

        /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
        switch (FMS_B.state) {
         case VehicleState_Takeoff:
          FMS_DW.SwitchCase_ActiveSubsystem_o = 0;
          break;

         case VehicleState_Land:
          FMS_DW.SwitchCase_ActiveSubsystem_o = 1;
          break;

         case VehicleState_Return:
          FMS_DW.SwitchCase_ActiveSubsystem_o = 2;
          break;

         case VehicleState_Hold:
          FMS_DW.SwitchCase_ActiveSubsystem_o = 3;
          break;

         default:
          FMS_DW.SwitchCase_ActiveSubsystem_o = 4;
          break;
        }

        /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
        if (rtPrevAction != FMS_DW.SwitchCase_ActiveSubsystem_o) {
          switch (rtPrevAction) {
           case 0:
           case 1:
           case 4:
            break;

           case 2:
            /* SwitchCase: '<S317>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

            /* SwitchCase: '<S307>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;
            break;

           case 3:
            /* SwitchCase: '<S263>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

            /* SwitchCase: '<S241>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

            /* SwitchCase: '<S251>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;
            break;
          }
        }

        switch (FMS_DW.SwitchCase_ActiveSubsystem_o) {
         case 0:
          /* Outputs for IfAction SubSystem: '<S41>/Takeoff' incorporates:
           *  ActionPort: '<S236>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S363>/Trigonometric Function1' incorporates:
           *  Gain: '<S361>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S363>/Trigonometric Function3'
           */
          rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[0] = rtb_Divide_o_idx_0;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S363>/Trigonometric Function' incorporates:
           *  Gain: '<S361>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S363>/Trigonometric Function2'
           */
          rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[1] = rtb_Divide_o_idx_1;

          /* SignalConversion generated from: '<S363>/Vector Concatenate1' incorporates:
           *  Constant: '<S363>/Constant3'
           */
          rtb_Transpose[2] = 0.0F;

          /* Gain: '<S363>/Gain' */
          rtb_Transpose[3] = -rtb_Divide_o_idx_1;

          /* Trigonometry: '<S363>/Trigonometric Function3' */
          rtb_Transpose[4] = rtb_Divide_o_idx_0;

          /* SignalConversion generated from: '<S363>/Vector Concatenate2' incorporates:
           *  Constant: '<S363>/Constant4'
           */
          rtb_Transpose[5] = 0.0F;

          /* SignalConversion generated from: '<S363>/Vector Concatenate' incorporates:
           *  Concatenate: '<S363>/Vector Concatenate3'
           */
          rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_pk[0];
          rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_pk[1];
          rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_pk[2];

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S236>/Sum' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           *  Sum: '<S349>/Sum'
           */
          rtb_Square2 = FMS_B.Cmd_In.sp_waypoint[0] - FMS_U.INS_Out.x_R;
          rtb_MathFunction1 = FMS_B.Cmd_In.sp_waypoint[1] - FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Sum: '<S359>/Sum of Elements' incorporates:
           *  Math: '<S359>/Math Function'
           *  Sum: '<S236>/Sum'
           */
          rtb_Divide_o_idx_0 = rtb_MathFunction1 * rtb_MathFunction1 +
            rtb_Square2 * rtb_Square2;

          /* Math: '<S359>/Math Function1' incorporates:
           *  Sum: '<S359>/Sum of Elements'
           *
           * About '<S359>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_0 < 0.0F) {
            rtb_Divide_o_idx_2 = -sqrtf(fabsf(rtb_Divide_o_idx_0));
          } else {
            rtb_Divide_o_idx_2 = sqrtf(rtb_Divide_o_idx_0);
          }

          /* End of Math: '<S359>/Math Function1' */

          /* Switch: '<S359>/Switch' incorporates:
           *  Constant: '<S359>/Constant'
           *  Product: '<S359>/Product'
           *  Sum: '<S236>/Sum'
           */
          if (rtb_Divide_o_idx_2 > 0.0F) {
            rtb_MatrixConcatenate3[0] = rtb_MathFunction1;
            rtb_MatrixConcatenate3[1] = rtb_Square2;
            rtb_MatrixConcatenate3[2] = rtb_Divide_o_idx_2;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S359>/Switch' */

          /* Product: '<S359>/Divide' */
          rtb_Divide_od[0] = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3
            [2];
          rtb_Divide_od[1] = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3
            [2];

          /* Saturate: '<S349>/Saturation1' */
          rtb_Divide_o_idx_0 = -FMS_PARAM.VEL_XY_LIM / 5.0F;
          rtb_Divide_o_idx_1 = FMS_PARAM.VEL_XY_LIM / 5.0F;

          /* Product: '<S349>/Multiply' incorporates:
           *  Concatenate: '<S363>/Vector Concatenate'
           */
          for (sfEvent = 0; sfEvent < 3; sfEvent++) {
            rtb_Transpose_0[sfEvent] = rtb_Transpose[sfEvent + 3] *
              rtb_MathFunction1 + rtb_Transpose[sfEvent] * rtb_Square2;
          }

          /* End of Product: '<S349>/Multiply' */

          /* Sum: '<S357>/Subtract' incorporates:
           *  Product: '<S357>/Multiply'
           *  Product: '<S357>/Multiply1'
           */
          rtb_u_b = rtb_Divide_od[0] * FMS_ConstB.Divide_j[1] -
            FMS_ConstB.Divide_j[0] * rtb_Divide_od[1];

          /* Signum: '<S352>/Sign1' */
          if (rtb_u_b < 0.0F) {
            rtb_Divide_o_idx_2 = -1.0F;
          } else {
            rtb_Divide_o_idx_2 = (real32_T)(rtb_u_b > 0.0F);
          }

          /* End of Signum: '<S352>/Sign1' */

          /* Saturate: '<S349>/Saturation1' incorporates:
           *  Gain: '<S349>/Gain2'
           */
          rtb_MathFunction1 = FMS_PARAM.XY_P * rtb_Transpose_0[0];
          rtb_Square2 = FMS_PARAM.XY_P * rtb_Transpose_0[1];

          /* DotProduct: '<S352>/Dot Product' incorporates:
           *  Product: '<S358>/Divide'
           */
          rtb_u_b = FMS_ConstB.Divide_j[0] * rtb_Divide_od[0] +
            FMS_ConstB.Divide_j[1] * rtb_Divide_od[1];

          /* Trigonometry: '<S352>/Acos' incorporates:
           *  DotProduct: '<S352>/Dot Product'
           */
          if (rtb_u_b > 1.0F) {
            rtb_u_b = 1.0F;
          } else if (rtb_u_b < -1.0F) {
            rtb_u_b = -1.0F;
          }

          /* Switch: '<S352>/Switch2' incorporates:
           *  Constant: '<S352>/Constant4'
           */
          if (rtb_Divide_o_idx_2 == 0.0F) {
            rtb_Divide_o_idx_2 = 1.0F;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Math: '<S355>/Rem' incorporates:
           *  Constant: '<S355>/Constant1'
           *  Inport: '<Root>/INS_Out'
           *  Product: '<S352>/Multiply'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S353>/Sum'
           *  Switch: '<S352>/Switch2'
           *  Trigonometry: '<S352>/Acos'
           */
          rtb_Divide_o_idx_2 = rt_remf(acosf(rtb_u_b) * rtb_Divide_o_idx_2 -
            FMS_U.INS_Out.psi, 6.28318548F);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S355>/Switch' incorporates:
           *  Abs: '<S355>/Abs'
           *  Constant: '<S355>/Constant'
           *  Constant: '<S356>/Constant'
           *  Product: '<S355>/Multiply'
           *  RelationalOperator: '<S356>/Compare'
           *  Signum: '<S355>/Sign'
           *  Sum: '<S355>/Add'
           */
          if (fabsf(rtb_Divide_o_idx_2) > 3.14159274F) {
            /* Signum: '<S355>/Sign' */
            if (rtb_Divide_o_idx_2 < 0.0F) {
              rtb_u_b = -1.0F;
            } else {
              rtb_u_b = (real32_T)(rtb_Divide_o_idx_2 > 0.0F);
            }

            rtb_Divide_o_idx_2 -= 6.28318548F * rtb_u_b;
          }

          /* End of Switch: '<S355>/Switch' */
          /* End of Outputs for SubSystem: '<S41>/Takeoff' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Takeoff' incorporates:
           *  ActionPort: '<S236>/Action Port'
           */
          /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_ge;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_cc;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_b0;

          /* Gain: '<S353>/Gain2' */
          rtb_u_b = FMS_PARAM.YAW_P * rtb_Divide_o_idx_2;

          /* Saturate: '<S353>/Saturation' */
          if (rtb_u_b > FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
          } else if (rtb_u_b < -FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
          } else {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = rtb_u_b;
          }

          /* End of Saturate: '<S353>/Saturation' */

          /* Saturate: '<S349>/Saturation1' */
          if (rtb_MathFunction1 > rtb_Divide_o_idx_1) {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_1;
          } else if (rtb_MathFunction1 < rtb_Divide_o_idx_0) {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_0;
          } else {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_MathFunction1;
          }

          if (rtb_Square2 > rtb_Divide_o_idx_1) {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_1;
          } else if (rtb_Square2 < rtb_Divide_o_idx_0) {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_0;
          } else {
            /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Square2;
          }

          /* BusAssignment: '<S236>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S236>/Constant4'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.w_cmd = 0.0F;

          /* End of Outputs for SubSystem: '<S41>/Takeoff' */
          break;

         case 1:
          /* Outputs for IfAction SubSystem: '<S41>/Land' incorporates:
           *  ActionPort: '<S234>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S280>/Trigonometric Function1' incorporates:
           *  Gain: '<S279>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S280>/Trigonometric Function3'
           */
          rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[0] = rtb_Divide_o_idx_0;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S280>/Trigonometric Function' incorporates:
           *  Gain: '<S279>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S280>/Trigonometric Function2'
           */
          rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[1] = rtb_Divide_o_idx_1;

          /* SignalConversion generated from: '<S280>/Vector Concatenate1' incorporates:
           *  Constant: '<S280>/Constant3'
           */
          rtb_Transpose[2] = 0.0F;

          /* Gain: '<S280>/Gain' */
          rtb_Transpose[3] = -rtb_Divide_o_idx_1;

          /* Trigonometry: '<S280>/Trigonometric Function3' */
          rtb_Transpose[4] = rtb_Divide_o_idx_0;

          /* SignalConversion generated from: '<S280>/Vector Concatenate2' incorporates:
           *  Constant: '<S280>/Constant4'
           */
          rtb_Transpose[5] = 0.0F;

          /* SignalConversion generated from: '<S280>/Vector Concatenate' incorporates:
           *  Concatenate: '<S280>/Vector Concatenate3'
           */
          rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_n5[0];
          rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_n5[1];
          rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_n5[2];

          /* Saturate: '<S276>/Saturation1' */
          rtb_Divide_o_idx_0 = -FMS_PARAM.VEL_XY_LIM / 5.0F;
          rtb_Divide_o_idx_1 = FMS_PARAM.VEL_XY_LIM / 5.0F;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* SignalConversion generated from: '<S277>/Multiply' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           *  Sum: '<S277>/Sum'
           */
          rtb_Divide_o_idx_2 = FMS_B.Cmd_In.sp_waypoint[0] - FMS_U.INS_Out.x_R;
          rtb_Square2 = FMS_B.Cmd_In.sp_waypoint[1] - FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Product: '<S277>/Multiply' incorporates:
           *  Concatenate: '<S280>/Vector Concatenate'
           */
          for (sfEvent = 0; sfEvent < 3; sfEvent++) {
            rtb_Transpose_0[sfEvent] = rtb_Transpose[sfEvent + 3] * rtb_Square2
              + rtb_Transpose[sfEvent] * rtb_Divide_o_idx_2;
          }

          /* End of Product: '<S277>/Multiply' */

          /* Saturate: '<S276>/Saturation1' incorporates:
           *  Gain: '<S277>/Gain2'
           */
          rtb_MathFunction1 = FMS_PARAM.XY_P * rtb_Transpose_0[0];
          rtb_Square2 = FMS_PARAM.XY_P * rtb_Transpose_0[1];

          /* End of Outputs for SubSystem: '<S41>/Land' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Land' incorporates:
           *  ActionPort: '<S234>/Action Port'
           */
          /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_p;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_iv;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_bf;

          /* Saturate: '<S276>/Saturation1' */
          if (rtb_Square2 > rtb_Divide_o_idx_1) {
            /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = rtb_Divide_o_idx_1;
          } else if (rtb_Square2 < rtb_Divide_o_idx_0) {
            /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = rtb_Divide_o_idx_0;
          } else {
            /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = rtb_Square2;
          }

          if (rtb_MathFunction1 > rtb_Divide_o_idx_1) {
            /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_1;
          } else if (rtb_MathFunction1 < rtb_Divide_o_idx_0) {
            /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_0;
          } else {
            /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_MathFunction1;
          }

          /* BusAssignment: '<S234>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S234>/Constant'
           *  Constant: '<S234>/Constant4'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.v_cmd = 0.0F;
          FMS_Y.FMS_Out.w_cmd = 0.5F;

          /* End of Outputs for SubSystem: '<S41>/Land' */
          break;

         case 2:
          if (FMS_DW.SwitchCase_ActiveSubsystem_o != rtPrevAction) {
            /* InitializeConditions for IfAction SubSystem: '<S41>/Return' incorporates:
             *  ActionPort: '<S235>/Action Port'
             */
            /* InitializeConditions for SwitchCase: '<S41>/Switch Case' incorporates:
             *  Delay: '<S283>/Delay'
             *  Delay: '<S284>/Delay'
             *  Delay: '<S303>/Delay'
             *  DiscreteIntegrator: '<S287>/Integrator'
             *  DiscreteIntegrator: '<S287>/Integrator1'
             *  DiscreteIntegrator: '<S344>/Discrete-Time Integrator'
             */
            FMS_DW.icLoad_h = true;
            FMS_DW.l1_heading_a = 0.0F;
            FMS_DW.icLoad_j = true;
            FMS_DW.icLoad_c = true;
            FMS_DW.Integrator1_IC_LOADING = 1U;
            FMS_DW.Integrator_DSTATE = 0.0F;

            /* End of InitializeConditions for SubSystem: '<S41>/Return' */

            /* SystemReset for IfAction SubSystem: '<S41>/Return' incorporates:
             *  ActionPort: '<S235>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S41>/Switch Case' incorporates:
             *  Chart: '<S308>/Motion Status'
             *  Chart: '<S318>/Motion State'
             */
            FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState);
            FMS_MotionStatus_Reset(&rtb_state_ee, &FMS_DW.sf_MotionStatus);

            /* End of SystemReset for SubSystem: '<S41>/Return' */
          }

          /* Outputs for IfAction SubSystem: '<S41>/Return' incorporates:
           *  ActionPort: '<S235>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* SignalConversion generated from: '<S283>/Delay' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          rtb_Divide_od[0] = FMS_U.INS_Out.x_R;
          rtb_Divide_od[1] = FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Delay: '<S303>/Delay' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.icLoad_h) {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_DW.Delay_DSTATE_p[0] = FMS_U.INS_Out.x_R;
            FMS_DW.Delay_DSTATE_p[1] = FMS_U.INS_Out.y_R;

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S299>/Sum' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          rtb_u_b = FMS_U.INS_Out.x_R - FMS_B.Cmd_In.sp_waypoint[0];

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_MathFunction_f[0] = rtb_u_b * rtb_u_b;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S299>/Sum' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S304>/Square'
           *  Product: '<S341>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          rtb_u_b = FMS_U.INS_Out.y_R - FMS_B.Cmd_In.sp_waypoint[1];

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Sqrt: '<S304>/Sqrt' incorporates:
           *  Math: '<S304>/Square'
           *  Sum: '<S304>/Sum of Elements'
           */
          rtb_Divide_o_idx_0 = sqrtf(rtb_u_b * rtb_u_b + rtb_MathFunction_f[0]);

          /* Switch: '<S299>/Switch' incorporates:
           *  Constant: '<S299>/vel'
           */
          if (rtb_Divide_o_idx_0 > FMS_PARAM.L1) {
            rtb_Divide_o_idx_2 = FMS_PARAM.CRUISE_SPEED;
          } else {
            /* Gain: '<S299>/Gain' */
            rtb_Divide_o_idx_2 = 0.5F * rtb_Divide_o_idx_0;

            /* Saturate: '<S299>/Saturation' */
            if (rtb_Divide_o_idx_2 > FMS_PARAM.CRUISE_SPEED) {
              rtb_Divide_o_idx_2 = FMS_PARAM.CRUISE_SPEED;
            } else if (rtb_Divide_o_idx_2 < 0.5F) {
              rtb_Divide_o_idx_2 = 0.5F;
            }

            /* End of Saturate: '<S299>/Saturation' */
          }

          /* End of Switch: '<S299>/Switch' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S318>/Motion State' incorporates:
           *  Constant: '<S318>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S318>/Square'
           *  Math: '<S318>/Square1'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sqrt: '<S318>/Sqrt'
           *  Sum: '<S318>/Add'
           */
          FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
            FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                          &FMS_DW.sf_MotionState);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S317>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_c;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_c = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_c = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_c = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_c) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_c != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S317>/Hold Control' incorporates:
               *  ActionPort: '<S320>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S317>/Switch Case' */
              FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_g);

              /* End of SystemReset for SubSystem: '<S317>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S317>/Hold Control' incorporates:
             *  ActionPort: '<S320>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                              FMS_U.INS_Out.psi, FMS_B.Merge_f,
                              &FMS_ConstB.HoldControl_g, &FMS_DW.HoldControl_g);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S317>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S317>/Brake Control' incorporates:
             *  ActionPort: '<S319>/Action Port'
             */
            FMS_BrakeControl_h(FMS_B.Merge_f);

            /* End of Outputs for SubSystem: '<S317>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_c != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S317>/Move Control' incorporates:
               *  ActionPort: '<S321>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S317>/Switch Case' */
              FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_c);

              /* End of SystemReset for SubSystem: '<S317>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S317>/Move Control' incorporates:
             *  ActionPort: '<S321>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                              FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_f,
                              &FMS_ConstB.MoveControl_c, &FMS_DW.MoveControl_c);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S317>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S308>/Motion Status' incorporates:
           *  Abs: '<S308>/Abs'
           *  Constant: '<S308>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          FMS_MotionStatus(0.0F, fabsf(FMS_U.INS_Out.vd), &rtb_state_ee,
                           &FMS_DW.sf_MotionStatus);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S307>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_i5;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_i5) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_i5 != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S307>/Hold Control' incorporates:
               *  ActionPort: '<S310>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S307>/Switch Case' */
              FMS_HoldControl_Reset(&FMS_DW.HoldControl);

              /* End of SystemReset for SubSystem: '<S307>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S307>/Hold Control' incorporates:
             *  ActionPort: '<S310>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl(FMS_U.INS_Out.h_R, &FMS_B.Merge_pd,
                            &FMS_DW.HoldControl);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S307>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S307>/Brake Control' incorporates:
             *  ActionPort: '<S309>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_pd);

            /* End of Outputs for SubSystem: '<S307>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_i5 != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S307>/Move Control' incorporates:
               *  ActionPort: '<S311>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S307>/Switch Case' */
              FMS_MoveControl_Reset(&FMS_DW.MoveControl);

              /* End of SystemReset for SubSystem: '<S307>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S307>/Move Control' incorporates:
             *  ActionPort: '<S311>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl(FMS_U.Pilot_Cmd.stick_throttle, &FMS_B.Merge_pd,
                            &FMS_ConstB.MoveControl, &FMS_DW.MoveControl);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S307>/Move Control' */
            break;
          }

          /* Delay: '<S283>/Delay' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.icLoad_j) {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_DW.Delay_DSTATE_d[0] = FMS_U.INS_Out.x_R;
            FMS_DW.Delay_DSTATE_d[1] = FMS_U.INS_Out.y_R;

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S235>/Sum' incorporates:
           *  Delay: '<S283>/Delay'
           *  Product: '<S341>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          rtb_MathFunction_f[0] = FMS_B.Cmd_In.sp_waypoint[0] -
            FMS_DW.Delay_DSTATE_d[0];
          rtb_MathFunction_f[1] = FMS_B.Cmd_In.sp_waypoint[1] -
            FMS_DW.Delay_DSTATE_d[1];

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Math: '<S298>/Math Function' incorporates:
           *  SignalConversion generated from: '<S298>/Math Function'
           */
          rtb_MathFunction_h[0] = rtb_MathFunction_f[1] * rtb_MathFunction_f[1];
          rtb_MathFunction_h[1] = rtb_MathFunction_f[0] * rtb_MathFunction_f[0];

          /* Sum: '<S298>/Sum of Elements' */
          rtb_Divide_o_idx_0 = rtb_MathFunction_h[0] + rtb_MathFunction_h[1];

          /* Math: '<S298>/Math Function1' incorporates:
           *  Sum: '<S298>/Sum of Elements'
           *
           * About '<S298>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_0 < 0.0F) {
            rtb_Square2 = -sqrtf(fabsf(rtb_Divide_o_idx_0));
          } else {
            rtb_Square2 = sqrtf(rtb_Divide_o_idx_0);
          }

          /* End of Math: '<S298>/Math Function1' */

          /* Switch: '<S298>/Switch' incorporates:
           *  Constant: '<S298>/Constant'
           *  Product: '<S298>/Product'
           */
          if (rtb_Square2 > 0.0F) {
            rtb_MatrixConcatenate3[0] = rtb_MathFunction_f[1];
            rtb_MatrixConcatenate3[1] = rtb_MathFunction_f[0];
            rtb_MatrixConcatenate3[2] = rtb_Square2;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S298>/Switch' */

          /* Product: '<S298>/Divide' */
          rtb_u_b = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S285>/Dot Product' incorporates:
           *  Product: '<S297>/Divide'
           */
          rtb_Divide_o_idx_0 = FMS_ConstB.Divide_o[0] * rtb_u_b;
          rtb_MathFunction_f[0] = rtb_u_b;

          /* Product: '<S298>/Divide' */
          rtb_u_b = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S285>/Dot Product' incorporates:
           *  Product: '<S297>/Divide'
           */
          rtb_MathFunction1 = FMS_ConstB.Divide_o[1] * rtb_u_b +
            rtb_Divide_o_idx_0;

          /* Sum: '<S296>/Subtract' incorporates:
           *  Product: '<S296>/Multiply'
           *  Product: '<S296>/Multiply1'
           */
          rtb_u_b = rtb_MathFunction_f[0] * FMS_ConstB.Divide_o[1] -
            FMS_ConstB.Divide_o[0] * rtb_u_b;

          /* Signum: '<S285>/Sign1' */
          if (rtb_u_b < 0.0F) {
            rtb_Square2 = -1.0F;
          } else {
            rtb_Square2 = (real32_T)(rtb_u_b > 0.0F);
          }

          /* End of Signum: '<S285>/Sign1' */

          /* Trigonometry: '<S285>/Acos' incorporates:
           *  DotProduct: '<S285>/Dot Product'
           */
          if (rtb_MathFunction1 > 1.0F) {
            rtb_MathFunction1 = 1.0F;
          } else if (rtb_MathFunction1 < -1.0F) {
            rtb_MathFunction1 = -1.0F;
          }

          /* Switch: '<S285>/Switch2' incorporates:
           *  Constant: '<S285>/Constant4'
           */
          if (rtb_Square2 == 0.0F) {
            rtb_Square2 = 1.0F;
          }

          /* Product: '<S285>/Multiply' incorporates:
           *  Switch: '<S285>/Switch2'
           *  Trigonometry: '<S285>/Acos'
           */
          rtb_Square2 *= acosf(rtb_MathFunction1);

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Math: '<S289>/Rem' incorporates:
           *  Constant: '<S289>/Constant1'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S284>/Sum1'
           */
          rtb_Divide_o_idx_1 = rt_remf(rtb_Square2 - FMS_U.INS_Out.psi,
            6.28318548F);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S289>/Switch' incorporates:
           *  Abs: '<S289>/Abs'
           *  Constant: '<S289>/Constant'
           *  Constant: '<S295>/Constant'
           *  Product: '<S289>/Multiply'
           *  RelationalOperator: '<S295>/Compare'
           *  Signum: '<S289>/Sign'
           *  Sum: '<S289>/Add'
           */
          if (fabsf(rtb_Divide_o_idx_1) > 3.14159274F) {
            /* Signum: '<S289>/Sign' */
            if (rtb_Divide_o_idx_1 < 0.0F) {
              rtb_Divide_o_idx_0 = -1.0F;
            } else {
              rtb_Divide_o_idx_0 = (real32_T)(rtb_Divide_o_idx_1 > 0.0F);
            }

            rtb_Divide_o_idx_1 -= 6.28318548F * rtb_Divide_o_idx_0;
          }

          /* End of Switch: '<S289>/Switch' */

          /* Abs: '<S282>/Abs' */
          rtb_Divide_o_idx_1 = fabsf(rtb_Divide_o_idx_1);

          /* Switch: '<S282>/Switch' incorporates:
           *  Concatenate: '<S347>/Vector Concatenate'
           *  Product: '<S303>/Multiply'
           *  Sum: '<S303>/Sum'
           */
          if (rtb_Divide_o_idx_1 > 0.34906584F) {
            /* Saturate: '<S317>/Saturation1' incorporates:
             *  Merge: '<S317>/Merge'
             */
            if (FMS_B.Merge_f[0] > FMS_PARAM.VEL_XY_LIM) {
              rtb_MatrixConcatenate3[0] = FMS_PARAM.VEL_XY_LIM;
            } else if (FMS_B.Merge_f[0] < -FMS_PARAM.VEL_XY_LIM) {
              rtb_MatrixConcatenate3[0] = -FMS_PARAM.VEL_XY_LIM;
            } else {
              rtb_MatrixConcatenate3[0] = FMS_B.Merge_f[0];
            }

            if (FMS_B.Merge_f[1] > FMS_PARAM.VEL_XY_LIM) {
              rtb_MatrixConcatenate3[1] = FMS_PARAM.VEL_XY_LIM;
            } else if (FMS_B.Merge_f[1] < -FMS_PARAM.VEL_XY_LIM) {
              rtb_MatrixConcatenate3[1] = -FMS_PARAM.VEL_XY_LIM;
            } else {
              rtb_MatrixConcatenate3[1] = FMS_B.Merge_f[1];
            }

            /* End of Saturate: '<S317>/Saturation1' */

            /* Saturate: '<S307>/Saturation1' */
            if (FMS_B.Merge_pd > FMS_PARAM.VEL_Z_LIM) {
              rtb_MatrixConcatenate3[2] = FMS_PARAM.VEL_Z_LIM;
            } else if (FMS_B.Merge_pd < -FMS_PARAM.VEL_Z_LIM) {
              rtb_MatrixConcatenate3[2] = -FMS_PARAM.VEL_Z_LIM;
            } else {
              rtb_MatrixConcatenate3[2] = FMS_B.Merge_pd;
            }

            /* End of Saturate: '<S307>/Saturation1' */
          } else {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            /* Sum: '<S303>/Sum' incorporates:
             *  Delay: '<S303>/Delay'
             *  SignalConversion generated from: '<S32>/Signal Copy3'
             */
            rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[0] -
              FMS_DW.Delay_DSTATE_p[0];

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

            /* SignalConversion generated from: '<S345>/Math Function' */
            rtb_MatrixConcatenate3[0] = rtb_Divide_o_idx_1;
            rtb_TmpSignalConversionAtMat_bs[0] = rtb_Divide_o_idx_1;

            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            /* Sum: '<S303>/Sum' incorporates:
             *  Delay: '<S303>/Delay'
             *  SignalConversion generated from: '<S32>/Signal Copy3'
             */
            rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[1] -
              FMS_DW.Delay_DSTATE_p[1];

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

            /* SignalConversion generated from: '<S347>/Vector Concatenate2' incorporates:
             *  Constant: '<S347>/Constant4'
             */
            rtb_Transpose[5] = 0.0F;

            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            /* Gain: '<S346>/Gain' incorporates:
             *  DiscreteIntegrator: '<S344>/Discrete-Time Integrator'
             *  Inport: '<Root>/INS_Out'
             *  SignalConversion generated from: '<S32>/Signal Copy1'
             *  Sum: '<S344>/Add'
             */
            rtb_MathFunction1 = -(FMS_U.INS_Out.psi - FMS_DW.l1_heading_a);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

            /* Trigonometry: '<S347>/Trigonometric Function3' incorporates:
             *  Trigonometry: '<S347>/Trigonometric Function1'
             */
            rtb_Divide_o_idx_0 = arm_cos_f32(rtb_MathFunction1);
            rtb_Transpose[4] = rtb_Divide_o_idx_0;

            /* Trigonometry: '<S347>/Trigonometric Function2' incorporates:
             *  Trigonometry: '<S347>/Trigonometric Function'
             */
            rtb_MathFunction1 = arm_sin_f32(rtb_MathFunction1);

            /* Gain: '<S347>/Gain' incorporates:
             *  Trigonometry: '<S347>/Trigonometric Function2'
             */
            rtb_Transpose[3] = -rtb_MathFunction1;

            /* SignalConversion generated from: '<S347>/Vector Concatenate1' incorporates:
             *  Constant: '<S347>/Constant3'
             */
            rtb_Transpose[2] = 0.0F;

            /* Trigonometry: '<S347>/Trigonometric Function' */
            rtb_Transpose[1] = rtb_MathFunction1;

            /* Trigonometry: '<S347>/Trigonometric Function1' */
            rtb_Transpose[0] = rtb_Divide_o_idx_0;

            /* SignalConversion generated from: '<S347>/Vector Concatenate' incorporates:
             *  Concatenate: '<S347>/Vector Concatenate3'
             */
            rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_p[0];
            rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_p[1];
            rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_p[2];

            /* Sum: '<S345>/Sum of Elements' incorporates:
             *  Math: '<S345>/Math Function'
             *  SignalConversion generated from: '<S345>/Math Function'
             */
            rtb_Divide_o_idx_0 = rtb_MatrixConcatenate3[0] *
              rtb_MatrixConcatenate3[0] + rtb_Divide_o_idx_1 *
              rtb_Divide_o_idx_1;

            /* Math: '<S345>/Math Function1' incorporates:
             *  Sum: '<S345>/Sum of Elements'
             *
             * About '<S345>/Math Function1':
             *  Operator: sqrt
             */
            if (rtb_Divide_o_idx_0 < 0.0F) {
              rtb_MathFunction1 = -sqrtf(fabsf(rtb_Divide_o_idx_0));
            } else {
              rtb_MathFunction1 = sqrtf(rtb_Divide_o_idx_0);
            }

            /* End of Math: '<S345>/Math Function1' */

            /* Switch: '<S345>/Switch' incorporates:
             *  Constant: '<S345>/Constant'
             *  Product: '<S345>/Product'
             */
            if (rtb_MathFunction1 > 0.0F) {
              rtb_Divide_o_idx_0 = rtb_TmpSignalConversionAtMat_bs[0];
            } else {
              rtb_Divide_o_idx_0 = 0.0F;
              rtb_Divide_o_idx_1 = 0.0F;
              rtb_MathFunction1 = 1.0F;
            }

            /* End of Switch: '<S345>/Switch' */

            /* Product: '<S343>/Multiply2' incorporates:
             *  Product: '<S345>/Divide'
             */
            rtb_Divide_o_idx_0 = rtb_Divide_o_idx_0 / rtb_MathFunction1 *
              rtb_Divide_o_idx_2;
            rtb_Divide_o_idx_1 = rtb_Divide_o_idx_1 / rtb_MathFunction1 *
              rtb_Divide_o_idx_2;
            for (sfEvent = 0; sfEvent < 3; sfEvent++) {
              rtb_MatrixConcatenate3[sfEvent] = rtb_Transpose[sfEvent + 3] *
                rtb_Divide_o_idx_1 + rtb_Transpose[sfEvent] * rtb_Divide_o_idx_0;
            }
          }

          /* End of Switch: '<S282>/Switch' */

          /* Delay: '<S284>/Delay' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.icLoad_c) {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_DW.Delay_DSTATE_do = FMS_U.INS_Out.psi;

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          }

          /* DiscreteIntegrator: '<S287>/Integrator1' incorporates:
           *  Delay: '<S284>/Delay'
           */
          if (FMS_DW.Integrator1_IC_LOADING != 0) {
            FMS_DW.Integrator1_DSTATE = FMS_DW.Delay_DSTATE_do;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Math: '<S291>/Rem' incorporates:
           *  Constant: '<S291>/Constant1'
           *  DiscreteIntegrator: '<S287>/Integrator1'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S286>/Sum'
           */
          rtb_Rem_j = rt_remf(FMS_DW.Integrator1_DSTATE - FMS_U.INS_Out.psi,
                              6.28318548F);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S291>/Switch' incorporates:
           *  Abs: '<S291>/Abs'
           *  Constant: '<S291>/Constant'
           *  Constant: '<S292>/Constant'
           *  Product: '<S291>/Multiply'
           *  RelationalOperator: '<S292>/Compare'
           *  Signum: '<S291>/Sign'
           *  Sum: '<S291>/Add'
           */
          if (fabsf(rtb_Rem_j) > 3.14159274F) {
            /* Signum: '<S291>/Sign' */
            if (rtb_Rem_j < 0.0F) {
              rtb_Divide_o_idx_0 = -1.0F;
            } else {
              rtb_Divide_o_idx_0 = (real32_T)(rtb_Rem_j > 0.0F);
            }

            rtb_Rem_j -= 6.28318548F * rtb_Divide_o_idx_0;
          }

          /* End of Switch: '<S291>/Switch' */

          /* Gain: '<S286>/Gain2' */
          rtb_MathFunction1 = FMS_PARAM.YAW_P * rtb_Rem_j;

          /* End of Outputs for SubSystem: '<S41>/Return' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Return' incorporates:
           *  ActionPort: '<S235>/Action Port'
           */
          /* BusAssignment: '<S235>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_k;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_h;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_m;
          FMS_Y.FMS_Out.u_cmd = rtb_MatrixConcatenate3[0];
          FMS_Y.FMS_Out.v_cmd = rtb_MatrixConcatenate3[1];
          FMS_Y.FMS_Out.w_cmd = rtb_MatrixConcatenate3[2];

          /* Saturate: '<S286>/Saturation' */
          if (rtb_MathFunction1 > FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S235>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
          } else if (rtb_MathFunction1 < -FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S235>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
          } else {
            /* BusAssignment: '<S235>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = rtb_MathFunction1;
          }

          /* End of Saturate: '<S286>/Saturation' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S338>/Sum of Elements' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S338>/Math Function'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S336>/Sum of Elements'
           */
          rtb_Divide_o_idx_0 = FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
            FMS_U.INS_Out.ve * FMS_U.INS_Out.ve;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Math: '<S338>/Math Function1' incorporates:
           *  Sum: '<S338>/Sum of Elements'
           *
           * About '<S338>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_0 < 0.0F) {
            rtb_Rem_j = -sqrtf(fabsf(rtb_Divide_o_idx_0));
          } else {
            rtb_Rem_j = sqrtf(rtb_Divide_o_idx_0);
          }

          /* End of Math: '<S338>/Math Function1' */

          /* Switch: '<S338>/Switch' incorporates:
           *  Constant: '<S338>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  Product: '<S338>/Product'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (rtb_Rem_j > 0.0F) {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            rtb_MatrixConcatenate3[0] = FMS_U.INS_Out.vn;
            rtb_MatrixConcatenate3[1] = FMS_U.INS_Out.ve;

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            rtb_MatrixConcatenate3[2] = rtb_Rem_j;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S338>/Switch' */

          /* Product: '<S338>/Divide' */
          rtb_MathFunction_f[0] = rtb_MatrixConcatenate3[0] /
            rtb_MatrixConcatenate3[2];
          rtb_MathFunction_f[1] = rtb_MatrixConcatenate3[1] /
            rtb_MatrixConcatenate3[2];

          /* SignalConversion generated from: '<S341>/Math Function' */
          rtb_MathFunction_h[0] = rtb_MathFunction_f[1];
          rtb_MathFunction_h[1] = rtb_MathFunction_f[0];

          /* Math: '<S341>/Math Function' incorporates:
           *  SignalConversion generated from: '<S341>/Math Function'
           */
          rtb_MathFunction_ab[0] = rtb_MathFunction_f[1] * rtb_MathFunction_f[1];
          rtb_MathFunction_ab[1] = rtb_MathFunction_f[0] * rtb_MathFunction_f[0];

          /* Sum: '<S341>/Sum of Elements' */
          rtb_Divide_o_idx_1 = rtb_MathFunction_ab[0] + rtb_MathFunction_ab[1];

          /* Math: '<S341>/Math Function1' incorporates:
           *  Sum: '<S341>/Sum of Elements'
           *
           * About '<S341>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_1 < 0.0F) {
            rtb_Rem_j = -sqrtf(fabsf(rtb_Divide_o_idx_1));
          } else {
            rtb_Rem_j = sqrtf(rtb_Divide_o_idx_1);
          }

          /* End of Math: '<S341>/Math Function1' */

          /* Switch: '<S341>/Switch' incorporates:
           *  Constant: '<S341>/Constant'
           *  Product: '<S341>/Product'
           */
          if (rtb_Rem_j > 0.0F) {
            rtb_MatrixConcatenate3[0] = rtb_MathFunction_f[1];
            rtb_MatrixConcatenate3[1] = rtb_MathFunction_f[0];
            rtb_MatrixConcatenate3[2] = rtb_Rem_j;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S341>/Switch' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* MATLAB Function: '<S301>/NearbyRefWP' incorporates:
           *  Constant: '<S235>/L1'
           *  Reshape: '<S283>/Reshape2'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          FMS_NearbyRefWP(&FMS_B.Cmd_In.sp_waypoint[0], rtb_Divide_od,
                          FMS_PARAM.L1, rtb_MathFunction_h, &rtb_Rem_h);

          /* MATLAB Function: '<S301>/SearchL1RefWP' incorporates:
           *  Constant: '<S235>/L1'
           *  Delay: '<S283>/Delay'
           *  Reshape: '<S283>/Reshape2'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          FMS_SearchL1RefWP(FMS_DW.Delay_DSTATE_d, &FMS_B.Cmd_In.sp_waypoint[0],
                            rtb_Divide_od, FMS_PARAM.L1, rtb_MathFunction_f,
                            &rtb_Divide_o_idx_1);

          /* MATLAB Function: '<S301>/OutRegionRegWP' incorporates:
           *  Delay: '<S283>/Delay'
           *  Reshape: '<S283>/Reshape2'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          FMS_OutRegionRegWP(FMS_DW.Delay_DSTATE_d, &FMS_B.Cmd_In.sp_waypoint[0],
                             rtb_Divide_od, rtb_MathFunction_ab);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S301>/Switch1' incorporates:
           *  Constant: '<S330>/Constant'
           *  Constant: '<S331>/Constant'
           *  Product: '<S341>/Divide'
           *  RelationalOperator: '<S330>/Compare'
           *  RelationalOperator: '<S331>/Compare'
           *  Switch: '<S301>/Switch'
           */
          if (rtb_Rem_h > 0.0F) {
            rtb_MathFunction_f[0] = rtb_MathFunction_h[0];
            rtb_MathFunction_f[1] = rtb_MathFunction_h[1];
          } else if (rtb_Divide_o_idx_1 < 0.0F) {
            /* Product: '<S341>/Divide' incorporates:
             *  Switch: '<S301>/Switch'
             */
            rtb_MathFunction_f[0] = rtb_MathFunction_ab[0];
            rtb_MathFunction_f[1] = rtb_MathFunction_ab[1];
          }

          /* End of Switch: '<S301>/Switch1' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S302>/Subtract' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Product: '<S341>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          rtb_u_b = rtb_MathFunction_f[0] - FMS_U.INS_Out.x_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_MathFunction_f[0] = rtb_u_b;
          rtb_Divide_od[0] = rtb_u_b * rtb_u_b;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S302>/Subtract' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S339>/Math Function'
           *  Product: '<S341>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          rtb_u_b = rtb_MathFunction_f[1] - FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Sum: '<S339>/Sum of Elements' incorporates:
           *  Math: '<S339>/Math Function'
           *  Sum: '<S337>/Sum of Elements'
           */
          rtb_Divide_o_idx_1 = rtb_u_b * rtb_u_b + rtb_Divide_od[0];

          /* Math: '<S339>/Math Function1' incorporates:
           *  Sum: '<S339>/Sum of Elements'
           *
           * About '<S339>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_1 < 0.0F) {
            rtb_Rem_j = -sqrtf(fabsf(rtb_Divide_o_idx_1));
          } else {
            rtb_Rem_j = sqrtf(rtb_Divide_o_idx_1);
          }

          /* End of Math: '<S339>/Math Function1' */

          /* Switch: '<S339>/Switch' incorporates:
           *  Constant: '<S339>/Constant'
           *  Product: '<S339>/Product'
           *  Switch: '<S342>/Switch'
           */
          if (rtb_Rem_j > 0.0F) {
            rtb_MathFunction_a[0] = rtb_MathFunction_f[0];
            rtb_MathFunction_a[1] = rtb_u_b;
            rtb_MathFunction_a[2] = rtb_Rem_j;
          } else {
            rtb_MathFunction_a[0] = 0.0F;
            rtb_MathFunction_a[1] = 0.0F;
            rtb_MathFunction_a[2] = 1.0F;
          }

          /* End of Switch: '<S339>/Switch' */

          /* Product: '<S339>/Divide' incorporates:
           *  Product: '<S342>/Divide'
           */
          rtb_MathFunction_h[0] = rtb_MathFunction_a[0] / rtb_MathFunction_a[2];
          rtb_MathFunction_h[1] = rtb_MathFunction_a[1] / rtb_MathFunction_a[2];

          /* Sum: '<S342>/Sum of Elements' incorporates:
           *  Math: '<S342>/Math Function'
           *  SignalConversion generated from: '<S342>/Math Function'
           */
          rtb_u_b = rtb_MathFunction_h[1] * rtb_MathFunction_h[1] +
            rtb_MathFunction_h[0] * rtb_MathFunction_h[0];

          /* Math: '<S342>/Math Function1' incorporates:
           *  Sum: '<S342>/Sum of Elements'
           *
           * About '<S342>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_u_b < 0.0F) {
            rtb_Rem_j = -sqrtf(fabsf(rtb_u_b));
          } else {
            rtb_Rem_j = sqrtf(rtb_u_b);
          }

          /* End of Math: '<S342>/Math Function1' */

          /* Switch: '<S342>/Switch' incorporates:
           *  Constant: '<S342>/Constant'
           *  Product: '<S342>/Product'
           */
          if (rtb_Rem_j > 0.0F) {
            rtb_MathFunction_a[0] = rtb_MathFunction_h[1];
            rtb_MathFunction_a[1] = rtb_MathFunction_h[0];
            rtb_MathFunction_a[2] = rtb_Rem_j;
          } else {
            rtb_MathFunction_a[0] = 0.0F;
            rtb_MathFunction_a[1] = 0.0F;
            rtb_MathFunction_a[2] = 1.0F;
          }

          /* End of Switch: '<S342>/Switch' */

          /* Product: '<S342>/Divide' */
          rtb_Rem_h = rtb_MathFunction_a[0] / rtb_MathFunction_a[2];

          /* Product: '<S341>/Divide' */
          rtb_u_b = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S335>/Dot Product' */
          rtb_Transpose_tmp = rtb_u_b * rtb_Rem_h;
          rtb_MathFunction_h[0] = rtb_Rem_h;
          rtb_MathFunction_f[0] = rtb_u_b;

          /* Product: '<S342>/Divide' incorporates:
           *  Product: '<S341>/Divide'
           */
          rtb_Rem_h = rtb_MathFunction_a[1] / rtb_MathFunction_a[2];

          /* Product: '<S341>/Divide' */
          rtb_u_b = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S335>/Dot Product' */
          rtb_Transpose_tmp += rtb_u_b * rtb_Rem_h;

          /* Sqrt: '<S336>/Sqrt' */
          rtb_Rem_j = sqrtf(rtb_Divide_o_idx_0);

          /* Gain: '<S302>/Gain' incorporates:
           *  Math: '<S302>/Square'
           */
          rtb_MathFunction1 = rtb_Rem_j * rtb_Rem_j * 2.0F;

          /* Sum: '<S340>/Subtract' incorporates:
           *  Product: '<S340>/Multiply'
           *  Product: '<S340>/Multiply1'
           */
          rtb_u_b = rtb_MathFunction_h[0] * rtb_u_b - rtb_MathFunction_f[0] *
            rtb_Rem_h;

          /* Signum: '<S335>/Sign1' */
          if (rtb_u_b < 0.0F) {
            rtb_Rem_j = -1.0F;
          } else {
            rtb_Rem_j = (real32_T)(rtb_u_b > 0.0F);
          }

          /* End of Signum: '<S335>/Sign1' */

          /* Trigonometry: '<S335>/Acos' incorporates:
           *  DotProduct: '<S335>/Dot Product'
           */
          if (rtb_Transpose_tmp > 1.0F) {
            rtb_Transpose_tmp = 1.0F;
          } else if (rtb_Transpose_tmp < -1.0F) {
            rtb_Transpose_tmp = -1.0F;
          }

          /* Switch: '<S335>/Switch2' incorporates:
           *  Constant: '<S335>/Constant4'
           */
          if (rtb_Rem_j == 0.0F) {
            rtb_Rem_j = 1.0F;
          }

          /* Product: '<S335>/Multiply' incorporates:
           *  Switch: '<S335>/Switch2'
           *  Trigonometry: '<S335>/Acos'
           */
          rtb_Rem_j *= acosf(rtb_Transpose_tmp);

          /* Saturate: '<S302>/Saturation' */
          if (rtb_Rem_j > 1.57079637F) {
            rtb_Transpose_tmp = 1.57079637F;
          } else if (rtb_Rem_j < -1.57079637F) {
            rtb_Transpose_tmp = -1.57079637F;
          } else {
            rtb_Transpose_tmp = rtb_Rem_j;
          }

          /* End of Saturate: '<S302>/Saturation' */

          /* Math: '<S288>/Rem' incorporates:
           *  Constant: '<S288>/Constant1'
           *  Delay: '<S284>/Delay'
           *  Sum: '<S284>/Sum2'
           */
          rtb_Rem_h = rt_remf(rtb_Square2 - FMS_DW.Delay_DSTATE_do, 6.28318548F);

          /* Switch: '<S288>/Switch' incorporates:
           *  Abs: '<S288>/Abs'
           *  Constant: '<S288>/Constant'
           *  Constant: '<S294>/Constant'
           *  Product: '<S288>/Multiply'
           *  RelationalOperator: '<S294>/Compare'
           *  Signum: '<S288>/Sign'
           *  Sum: '<S288>/Add'
           */
          if (fabsf(rtb_Rem_h) > 3.14159274F) {
            /* Signum: '<S288>/Sign' */
            if (rtb_Rem_h < 0.0F) {
              rtb_Divide_o_idx_0 = -1.0F;
            } else {
              rtb_Divide_o_idx_0 = (real32_T)(rtb_Rem_h > 0.0F);
            }

            rtb_Rem_h -= 6.28318548F * rtb_Divide_o_idx_0;
          }

          /* End of Switch: '<S288>/Switch' */

          /* Sum: '<S284>/Sum' incorporates:
           *  Delay: '<S284>/Delay'
           */
          rtb_Divide_o_idx_0 = rtb_Rem_h + FMS_DW.Delay_DSTATE_do;

          /* Product: '<S293>/Multiply1' incorporates:
           *  Constant: '<S293>/const1'
           *  DiscreteIntegrator: '<S287>/Integrator'
           */
          rtb_Rem_h = FMS_DW.Integrator_DSTATE * 0.785398185F;

          /* Sum: '<S293>/Add' incorporates:
           *  DiscreteIntegrator: '<S287>/Integrator1'
           *  Sum: '<S287>/Subtract'
           */
          rtb_Rem_j = (FMS_DW.Integrator1_DSTATE - rtb_Divide_o_idx_0) +
            rtb_Rem_h;

          /* Signum: '<S293>/Sign' */
          if (rtb_Rem_j < 0.0F) {
            rtb_Divide_o_idx_0 = -1.0F;
          } else {
            rtb_Divide_o_idx_0 = (real32_T)(rtb_Rem_j > 0.0F);
          }

          /* Sum: '<S293>/Add2' incorporates:
           *  Abs: '<S293>/Abs'
           *  Gain: '<S293>/Gain'
           *  Gain: '<S293>/Gain1'
           *  Product: '<S293>/Multiply2'
           *  Product: '<S293>/Multiply3'
           *  Signum: '<S293>/Sign'
           *  Sqrt: '<S293>/Sqrt'
           *  Sum: '<S293>/Add1'
           *  Sum: '<S293>/Subtract'
           */
          rtb_Square2 = (sqrtf((8.0F * fabsf(rtb_Rem_j) + FMS_ConstB.d) *
                               FMS_ConstB.d) - FMS_ConstB.d) * 0.5F *
            rtb_Divide_o_idx_0 + rtb_Rem_h;

          /* Sum: '<S293>/Add3' */
          rtb_u_b = rtb_Rem_j + FMS_ConstB.d;

          /* Sum: '<S293>/Subtract1' */
          rtb_Transpose_tmp_0 = rtb_Rem_j - FMS_ConstB.d;

          /* Signum: '<S293>/Sign1' */
          if (rtb_u_b < 0.0F) {
            rtb_Divide_o_idx_0 = -1.0F;
          } else {
            rtb_Divide_o_idx_0 = (real32_T)(rtb_u_b > 0.0F);
          }

          /* Signum: '<S293>/Sign2' */
          if (rtb_Transpose_tmp_0 < 0.0F) {
            rtb_u_b = -1.0F;
          } else {
            rtb_u_b = (real32_T)(rtb_Transpose_tmp_0 > 0.0F);
          }

          /* Sum: '<S293>/Add5' incorporates:
           *  Gain: '<S293>/Gain2'
           *  Product: '<S293>/Multiply4'
           *  Signum: '<S293>/Sign1'
           *  Signum: '<S293>/Sign2'
           *  Sum: '<S293>/Add4'
           *  Sum: '<S293>/Subtract2'
           */
          rtb_Square2 += ((rtb_Rem_j - rtb_Square2) + rtb_Rem_h) *
            ((rtb_Divide_o_idx_0 - rtb_u_b) * 0.5F);

          /* Update for Delay: '<S303>/Delay' */
          FMS_DW.icLoad_h = false;

          /* Update for DiscreteIntegrator: '<S344>/Discrete-Time Integrator' incorporates:
           *  Constant: '<S235>/L1'
           *  Constant: '<S302>/Constant'
           *  MinMax: '<S302>/Max'
           *  MinMax: '<S302>/Min'
           *  Product: '<S302>/Divide'
           *  Product: '<S302>/Multiply1'
           *  Product: '<S303>/Divide1'
           *  Sqrt: '<S337>/Sqrt'
           *  Trigonometry: '<S302>/Sin'
           */
          FMS_DW.l1_heading_a += arm_sin_f32(rtb_Transpose_tmp) *
            rtb_MathFunction1 / fminf(FMS_PARAM.L1, fmaxf(sqrtf
            (rtb_Divide_o_idx_1), 0.5F)) / rtb_Divide_o_idx_2 * 0.004F;

          /* Update for Delay: '<S283>/Delay' */
          FMS_DW.icLoad_j = false;

          /* Update for Delay: '<S284>/Delay' */
          FMS_DW.icLoad_c = false;

          /* Update for DiscreteIntegrator: '<S287>/Integrator1' incorporates:
           *  DiscreteIntegrator: '<S287>/Integrator'
           */
          FMS_DW.Integrator1_IC_LOADING = 0U;
          FMS_DW.Integrator1_DSTATE += 0.004F * FMS_DW.Integrator_DSTATE;

          /* Signum: '<S293>/Sign5' */
          if (rtb_Square2 < 0.0F) {
            /* Signum: '<S293>/Sign6' */
            rtb_Divide_o_idx_2 = -1.0F;
          } else {
            /* Signum: '<S293>/Sign6' */
            rtb_Divide_o_idx_2 = (real32_T)(rtb_Square2 > 0.0F);
          }

          /* Sum: '<S293>/Add6' */
          rtb_u_b = rtb_Square2 + FMS_ConstB.d;

          /* Sum: '<S293>/Subtract3' */
          rtb_Transpose_tmp_0 = rtb_Square2 - FMS_ConstB.d;

          /* Signum: '<S293>/Sign3' */
          if (rtb_u_b < 0.0F) {
            rtb_Divide_o_idx_0 = -1.0F;
          } else {
            rtb_Divide_o_idx_0 = (real32_T)(rtb_u_b > 0.0F);
          }

          /* Signum: '<S293>/Sign4' */
          if (rtb_Transpose_tmp_0 < 0.0F) {
            rtb_Divide_o_idx_1 = -1.0F;
          } else {
            rtb_Divide_o_idx_1 = (real32_T)(rtb_Transpose_tmp_0 > 0.0F);
          }

          /* Update for DiscreteIntegrator: '<S287>/Integrator' incorporates:
           *  Constant: '<S293>/const'
           *  Gain: '<S293>/Gain3'
           *  Product: '<S293>/Divide'
           *  Product: '<S293>/Multiply5'
           *  Product: '<S293>/Multiply6'
           *  Signum: '<S293>/Sign3'
           *  Signum: '<S293>/Sign4'
           *  Signum: '<S293>/Sign5'
           *  Sum: '<S293>/Subtract4'
           *  Sum: '<S293>/Subtract5'
           *  Sum: '<S293>/Subtract6'
           */
          FMS_DW.Integrator_DSTATE += ((rtb_Square2 / FMS_ConstB.d -
            rtb_Divide_o_idx_2) * FMS_ConstB.Gain4 * ((rtb_Divide_o_idx_0 -
            rtb_Divide_o_idx_1) * 0.5F) - rtb_Divide_o_idx_2 * 1.04719758F) *
            0.004F;
          if (FMS_DW.Integrator_DSTATE >= FMS_PARAM.YAW_RATE_LIM) {
            FMS_DW.Integrator_DSTATE = FMS_PARAM.YAW_RATE_LIM;
          } else if (FMS_DW.Integrator_DSTATE <= -FMS_PARAM.YAW_RATE_LIM) {
            FMS_DW.Integrator_DSTATE = -FMS_PARAM.YAW_RATE_LIM;
          }

          /* End of Update for DiscreteIntegrator: '<S287>/Integrator' */
          /* End of Outputs for SubSystem: '<S41>/Return' */
          break;

         case 3:
          if (FMS_DW.SwitchCase_ActiveSubsystem_o != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S41>/Hold' incorporates:
             *  ActionPort: '<S233>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S41>/Switch Case' incorporates:
             *  Chart: '<S242>/Motion Status'
             *  Chart: '<S252>/Motion State'
             *  Chart: '<S264>/Motion State'
             */
            FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_l);
            FMS_MotionStatus_Reset(&rtb_state_ee, &FMS_DW.sf_MotionStatus_d);
            FMS_MotionState_i_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_i);

            /* End of SystemReset for SubSystem: '<S41>/Hold' */
          }

          /* Outputs for IfAction SubSystem: '<S41>/Hold' incorporates:
           *  ActionPort: '<S233>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S264>/Motion State' incorporates:
           *  Constant: '<S264>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S264>/Square'
           *  Math: '<S264>/Square1'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sqrt: '<S264>/Sqrt'
           *  Sum: '<S264>/Add'
           */
          FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
            FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                          &FMS_DW.sf_MotionState_l);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S263>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_g;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_g = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_g = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_g = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_g) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_g != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S263>/Hold Control' incorporates:
               *  ActionPort: '<S266>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S263>/Switch Case' */
              FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_h);

              /* End of SystemReset for SubSystem: '<S263>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S263>/Hold Control' incorporates:
             *  ActionPort: '<S266>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                              FMS_U.INS_Out.psi, FMS_B.Merge_m,
                              &FMS_ConstB.HoldControl_h, &FMS_DW.HoldControl_h);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S263>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S263>/Brake Control' incorporates:
             *  ActionPort: '<S265>/Action Port'
             */
            FMS_BrakeControl_h(FMS_B.Merge_m);

            /* End of Outputs for SubSystem: '<S263>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_g != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S263>/Move Control' incorporates:
               *  ActionPort: '<S267>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S263>/Switch Case' */
              FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_h);

              /* End of SystemReset for SubSystem: '<S263>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S263>/Move Control' incorporates:
             *  ActionPort: '<S267>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                              FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_m,
                              &FMS_ConstB.MoveControl_h, &FMS_DW.MoveControl_h);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S263>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S242>/Motion Status' incorporates:
           *  Abs: '<S242>/Abs'
           *  Constant: '<S242>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          FMS_MotionStatus(0.0F, fabsf(FMS_U.INS_Out.vd), &rtb_state_ee,
                           &FMS_DW.sf_MotionStatus_d);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S241>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_d;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_d = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_d = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_d = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_d) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_d != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S241>/Hold Control' incorporates:
               *  ActionPort: '<S244>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S241>/Switch Case' */
              FMS_HoldControl_Reset(&FMS_DW.HoldControl_b);

              /* End of SystemReset for SubSystem: '<S241>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S241>/Hold Control' incorporates:
             *  ActionPort: '<S244>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl(FMS_U.INS_Out.h_R, &FMS_B.Merge_ob,
                            &FMS_DW.HoldControl_b);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S241>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S241>/Brake Control' incorporates:
             *  ActionPort: '<S243>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_ob);

            /* End of Outputs for SubSystem: '<S241>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_d != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S241>/Move Control' incorporates:
               *  ActionPort: '<S245>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S241>/Switch Case' */
              FMS_MoveControl_Reset(&FMS_DW.MoveControl_g);

              /* End of SystemReset for SubSystem: '<S241>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S241>/Move Control' incorporates:
             *  ActionPort: '<S245>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl(FMS_U.Pilot_Cmd.stick_throttle, &FMS_B.Merge_ob,
                            &FMS_ConstB.MoveControl_g, &FMS_DW.MoveControl_g);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S241>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S252>/Motion State' incorporates:
           *  Abs: '<S252>/Abs'
           *  Constant: '<S252>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          FMS_MotionState_i(0.0F, fabsf(FMS_U.INS_Out.r), &rtb_state_ee,
                            &FMS_DW.sf_MotionState_i);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S251>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_bi;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_bi = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_bi = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_bi = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_bi) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_bi != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S251>/Hold Control' incorporates:
               *  ActionPort: '<S254>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S251>/Switch Case' */
              FMS_HoldControl_i_Reset(&FMS_DW.HoldControl_k);

              /* End of SystemReset for SubSystem: '<S251>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S251>/Hold Control' incorporates:
             *  ActionPort: '<S254>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_k(FMS_U.INS_Out.psi, &FMS_B.Merge_p,
                              &FMS_DW.HoldControl_k);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S251>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S251>/Brake Control' incorporates:
             *  ActionPort: '<S253>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_p);

            /* End of Outputs for SubSystem: '<S251>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_bi != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S251>/Move Control' incorporates:
               *  ActionPort: '<S255>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S251>/Switch Case' */
              FMS_MoveControl_c_Reset(&FMS_DW.MoveControl_o);

              /* End of SystemReset for SubSystem: '<S251>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S251>/Move Control' incorporates:
             *  ActionPort: '<S255>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_o(FMS_U.Pilot_Cmd.stick_yaw, &FMS_B.Merge_p,
                              &FMS_ConstB.MoveControl_o, &FMS_DW.MoveControl_o);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S251>/Move Control' */
            break;
          }

          /* End of Outputs for SubSystem: '<S41>/Hold' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Hold' incorporates:
           *  ActionPort: '<S233>/Action Port'
           */
          /* BusAssignment: '<S233>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_c;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_c;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_l;

          /* Saturate: '<S251>/Saturation' */
          if (FMS_B.Merge_p > FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
          } else if (FMS_B.Merge_p < -FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
          } else {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_B.Merge_p;
          }

          /* End of Saturate: '<S251>/Saturation' */

          /* Saturate: '<S263>/Saturation1' incorporates:
           *  Merge: '<S263>/Merge'
           */
          if (FMS_B.Merge_m[0] > FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = FMS_PARAM.VEL_XY_LIM;
          } else if (FMS_B.Merge_m[0] < -FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = -FMS_PARAM.VEL_XY_LIM;
          } else {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = FMS_B.Merge_m[0];
          }

          if (FMS_B.Merge_m[1] > FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = FMS_PARAM.VEL_XY_LIM;
          } else if (FMS_B.Merge_m[1] < -FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = -FMS_PARAM.VEL_XY_LIM;
          } else {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = FMS_B.Merge_m[1];
          }

          /* End of Saturate: '<S263>/Saturation1' */

          /* Saturate: '<S241>/Saturation1' */
          if (FMS_B.Merge_ob > FMS_PARAM.VEL_Z_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = FMS_PARAM.VEL_Z_LIM;
          } else if (FMS_B.Merge_ob < -FMS_PARAM.VEL_Z_LIM) {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = -FMS_PARAM.VEL_Z_LIM;
          } else {
            /* BusAssignment: '<S233>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = FMS_B.Merge_ob;
          }

          /* End of Saturate: '<S241>/Saturation1' */
          /* End of Outputs for SubSystem: '<S41>/Hold' */
          break;

         default:
          /* Outputs for IfAction SubSystem: '<S41>/Unknown' incorporates:
           *  ActionPort: '<S237>/Action Port'
           */
          /* Outport: '<Root>/FMS_Out' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           */
          FMS_Disarm(&FMS_Y.FMS_Out, &FMS_ConstB.Unknown_m);

          /* End of Outputs for SubSystem: '<S41>/Unknown' */
          break;
        }

        /* End of Outputs for SubSystem: '<S33>/SubMode' */
        break;

       case 1:
        {
          /* Outputs for IfAction SubSystem: '<S33>/Auto' incorporates:
           *  ActionPort: '<S37>/Action Port'
           */
          /* SwitchCase: '<S37>/Switch Case' incorporates:
           *  Math: '<S66>/Square'
           *  Math: '<S67>/Square'
           *  Math: '<S68>/Square'
           *  Math: '<S78>/Math Function'
           *  Outport: '<Root>/FMS_Out'
           *  Product: '<S59>/Divide'
           *  Product: '<S80>/Divide'
           *  Product: '<S81>/Divide'
           *  Sum: '<S61>/Sum'
           *  Sum: '<S63>/Subtract'
           *  Sum: '<S64>/Sum'
           *  Sum: '<S65>/Sum1'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_i;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          switch (FMS_B.state) {
           case VehicleState_Offboard:
            FMS_DW.SwitchCase_ActiveSubsystem_i = 0;
            break;

           case VehicleState_Mission:
            FMS_DW.SwitchCase_ActiveSubsystem_i = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_i = 2;
            break;
          }

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          switch (FMS_DW.SwitchCase_ActiveSubsystem_i) {
           case 0:
            {
              boolean_T rtb_Compare_n;
              boolean_T rtb_LogicalOperator_i;
              boolean_T rtb_LogicalOperator_o;
              boolean_T rtb_Switch_p_idx_1;

              /* Outputs for IfAction SubSystem: '<S37>/Offboard' incorporates:
               *  ActionPort: '<S44>/Action Port'
               */
              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* SignalConversion generated from: '<S152>/Multiply2' incorporates:
               *  Gain: '<S153>/Gain'
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_MathFunction_a[0] = FMS_U.INS_Out.x_R;
              rtb_MathFunction_a[1] = FMS_U.INS_Out.y_R;
              rtb_MathFunction_a[2] = -FMS_U.INS_Out.h_R;

              /* MultiPortSwitch: '<S150>/Index Vector' incorporates:
               *  Concatenate: '<S162>/Vector Concatenate'
               *  Concatenate: '<S166>/Vector Concatenate'
               *  Inport: '<Root>/Auto_Cmd'
               *  Product: '<S156>/Multiply1'
               *  Product: '<S157>/Multiply3'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              switch (FMS_U.Auto_Cmd.frame) {
               case 0:
                /* SignalConversion generated from: '<S162>/Vector Concatenate2' incorporates:
                 *  Constant: '<S162>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S162>/Trigonometric Function3' incorporates:
                 *  Gain: '<S161>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S162>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S162>/Trigonometric Function2' incorporates:
                 *  Gain: '<S161>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S162>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S162>/Gain' incorporates:
                 *  Trigonometry: '<S162>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S162>/Vector Concatenate1' incorporates:
                 *  Constant: '<S162>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S162>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S162>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* SignalConversion generated from: '<S162>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S162>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_i[0];

                /* Saturate: '<S156>/Saturation' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S156>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/x_cmd valid'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S156>/Sum1'
                 */
                rtb_MathFunction1 = (FMS_U.Auto_Cmd.cmd_mask & 128U) > 0U ?
                  FMS_U.Auto_Cmd.x_cmd - FMS_U.INS_Out.x_R : 0.0F;
                if (rtb_MathFunction1 > 4.0F) {
                  rtb_MathFunction1 = 4.0F;
                } else if (rtb_MathFunction1 < -4.0F) {
                  rtb_MathFunction1 = -4.0F;
                }

                /* SignalConversion generated from: '<S162>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S162>/Vector Concatenate3'
                 */
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_i[1];

                /* Saturate: '<S156>/Saturation' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S156>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/y_cmd valid'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S156>/Sum1'
                 */
                rtb_Square2 = (FMS_U.Auto_Cmd.cmd_mask & 256U) > 0U ?
                  FMS_U.Auto_Cmd.y_cmd - FMS_U.INS_Out.y_R : 0.0F;
                if (rtb_Square2 > 4.0F) {
                  rtb_Square2 = 4.0F;
                } else if (rtb_Square2 < -4.0F) {
                  rtb_Square2 = -4.0F;
                }

                /* SignalConversion generated from: '<S162>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S162>/Vector Concatenate3'
                 */
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_i[2];

                /* Saturate: '<S156>/Saturation' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Gain: '<S153>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S156>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/z_cmd valid'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S156>/Sum1'
                 */
                rtb_u_b = (FMS_U.Auto_Cmd.cmd_mask & 512U) > 0U ?
                  FMS_U.Auto_Cmd.z_cmd - (-FMS_U.INS_Out.h_R) : 0.0F;
                if (rtb_u_b > 2.0F) {
                  rtb_u_b = 2.0F;
                } else if (rtb_u_b < -2.0F) {
                  rtb_u_b = -2.0F;
                }

                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_MatrixConcatenate3[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_Square2 + rtb_Transpose[sfEvent] * rtb_MathFunction1) +
                    rtb_Transpose[sfEvent + 6] * rtb_u_b;
                }
                break;

               case 1:
                /* SignalConversion generated from: '<S165>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S165>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_ny[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_ny[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_ny[2];

                /* SignalConversion generated from: '<S165>/Vector Concatenate2' incorporates:
                 *  Constant: '<S165>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S165>/Trigonometric Function3' incorporates:
                 *  Gain: '<S163>/Gain'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Trigonometry: '<S165>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_B.Cmd_In.offboard_psi_0);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S165>/Trigonometric Function2' incorporates:
                 *  Gain: '<S163>/Gain'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Trigonometry: '<S165>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_B.Cmd_In.offboard_psi_0);

                /* Gain: '<S165>/Gain' incorporates:
                 *  Trigonometry: '<S165>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S165>/Vector Concatenate1' incorporates:
                 *  Constant: '<S165>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S165>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S165>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* Product: '<S157>/Multiply2' incorporates:
                 *  Concatenate: '<S165>/Vector Concatenate'
                 */
                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_Sum2_n[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_MathFunction_a[1] + rtb_Transpose[sfEvent] *
                    rtb_MathFunction_a[0]) + rtb_Transpose[sfEvent + 6] *
                    rtb_MathFunction_a[2];
                }

                /* End of Product: '<S157>/Multiply2' */

                /* SignalConversion generated from: '<S166>/Vector Concatenate2' incorporates:
                 *  Constant: '<S166>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Gain: '<S164>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S157>/Subtract'
                 */
                rtb_Divide_o_idx_1 = -(FMS_U.INS_Out.psi -
                  FMS_B.Cmd_In.offboard_psi_0);

                /* Trigonometry: '<S166>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S166>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(rtb_Divide_o_idx_1);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S166>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S166>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(rtb_Divide_o_idx_1);

                /* Gain: '<S166>/Gain' incorporates:
                 *  Trigonometry: '<S166>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S166>/Vector Concatenate1' incorporates:
                 *  Constant: '<S166>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S166>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S166>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* SignalConversion generated from: '<S166>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S166>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_e0[0];

                /* Saturate: '<S157>/Saturation1' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Product: '<S157>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/x_cmd valid'
                 *  Sum: '<S157>/Sum2'
                 */
                rtb_MathFunction1 = (FMS_U.Auto_Cmd.cmd_mask & 128U) > 0U ?
                  FMS_U.Auto_Cmd.x_cmd - rtb_Sum2_n[0] : 0.0F;
                if (rtb_MathFunction1 > 4.0F) {
                  rtb_MathFunction1 = 4.0F;
                } else if (rtb_MathFunction1 < -4.0F) {
                  rtb_MathFunction1 = -4.0F;
                }

                /* SignalConversion generated from: '<S166>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S166>/Vector Concatenate3'
                 */
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_e0[1];

                /* Saturate: '<S157>/Saturation1' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Product: '<S157>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/y_cmd valid'
                 *  Sum: '<S157>/Sum2'
                 */
                rtb_Square2 = (FMS_U.Auto_Cmd.cmd_mask & 256U) > 0U ?
                  FMS_U.Auto_Cmd.y_cmd - rtb_Sum2_n[1] : 0.0F;
                if (rtb_Square2 > 4.0F) {
                  rtb_Square2 = 4.0F;
                } else if (rtb_Square2 < -4.0F) {
                  rtb_Square2 = -4.0F;
                }

                /* SignalConversion generated from: '<S166>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S166>/Vector Concatenate3'
                 */
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_e0[2];

                /* Saturate: '<S157>/Saturation1' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Product: '<S157>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/z_cmd valid'
                 *  Sum: '<S157>/Sum2'
                 */
                rtb_u_b = (FMS_U.Auto_Cmd.cmd_mask & 512U) > 0U ?
                  FMS_U.Auto_Cmd.z_cmd - rtb_Sum2_n[2] : 0.0F;
                if (rtb_u_b > 2.0F) {
                  rtb_u_b = 2.0F;
                } else if (rtb_u_b < -2.0F) {
                  rtb_u_b = -2.0F;
                }

                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_MatrixConcatenate3[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_Square2 + rtb_Transpose[sfEvent] * rtb_MathFunction1) +
                    rtb_Transpose[sfEvent + 6] * rtb_u_b;
                }
                break;

               default:
                /* SignalConversion generated from: '<S159>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S159>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_n[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_n[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_n[2];

                /* SignalConversion generated from: '<S159>/Vector Concatenate2' incorporates:
                 *  Constant: '<S159>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S159>/Trigonometric Function3' incorporates:
                 *  Gain: '<S158>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S159>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S159>/Trigonometric Function2' incorporates:
                 *  Gain: '<S158>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S159>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S159>/Gain' incorporates:
                 *  Trigonometry: '<S159>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S159>/Vector Concatenate1' incorporates:
                 *  Constant: '<S159>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S159>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S159>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* Product: '<S152>/Multiply2' incorporates:
                 *  Concatenate: '<S159>/Vector Concatenate'
                 */
                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_MatrixConcatenate3[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_MathFunction_a[1] + rtb_Transpose[sfEvent] *
                    rtb_MathFunction_a[0]) + rtb_Transpose[sfEvent + 6] *
                    rtb_MathFunction_a[2];
                }

                /* End of Product: '<S152>/Multiply2' */

                /* Sum: '<S152>/Sum2' */
                rtb_Divide_o_idx_2 = rtb_MatrixConcatenate3[0];
                rtb_Divide_o_idx_0 = rtb_MatrixConcatenate3[1];
                rtb_Divide_o_idx_1 = rtb_MatrixConcatenate3[2];

                /* Saturate: '<S152>/Saturation1' incorporates:
                 *  Constant: '<S160>/Constant'
                 *  Product: '<S152>/Multiply'
                 *  RelationalOperator: '<S160>/Compare'
                 *  S-Function (sfix_bitop): '<S155>/x_cmd valid'
                 *  S-Function (sfix_bitop): '<S155>/y_cmd valid'
                 *  S-Function (sfix_bitop): '<S155>/z_cmd valid'
                 *  Sum: '<S152>/Sum2'
                 */
                rtb_MathFunction1 = (FMS_U.Auto_Cmd.cmd_mask & 128U) > 0U ?
                  FMS_U.Auto_Cmd.x_cmd - rtb_Divide_o_idx_2 : 0.0F;
                if (rtb_MathFunction1 > 4.0F) {
                  rtb_MatrixConcatenate3[0] = 4.0F;
                } else if (rtb_MathFunction1 < -4.0F) {
                  rtb_MatrixConcatenate3[0] = -4.0F;
                } else {
                  rtb_MatrixConcatenate3[0] = rtb_MathFunction1;
                }

                rtb_MathFunction1 = (FMS_U.Auto_Cmd.cmd_mask & 256U) > 0U ?
                  FMS_U.Auto_Cmd.y_cmd - rtb_Divide_o_idx_0 : 0.0F;
                if (rtb_MathFunction1 > 4.0F) {
                  rtb_MatrixConcatenate3[1] = 4.0F;
                } else if (rtb_MathFunction1 < -4.0F) {
                  rtb_MatrixConcatenate3[1] = -4.0F;
                } else {
                  rtb_MatrixConcatenate3[1] = rtb_MathFunction1;
                }

                rtb_MathFunction1 = (FMS_U.Auto_Cmd.cmd_mask & 512U) > 0U ?
                  FMS_U.Auto_Cmd.z_cmd - rtb_Divide_o_idx_1 : 0.0F;
                if (rtb_MathFunction1 > 2.0F) {
                  rtb_MatrixConcatenate3[2] = 2.0F;
                } else if (rtb_MathFunction1 < -2.0F) {
                  rtb_MatrixConcatenate3[2] = -2.0F;
                } else {
                  rtb_MatrixConcatenate3[2] = rtb_MathFunction1;
                }

                /* End of Saturate: '<S152>/Saturation1' */
                break;
              }

              /* End of MultiPortSwitch: '<S150>/Index Vector' */

              /* Product: '<S87>/Multiply' incorporates:
               *  Constant: '<S95>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  RelationalOperator: '<S95>/Compare'
               *  S-Function (sfix_bitop): '<S92>/ax_cmd valid'
               *  S-Function (sfix_bitop): '<S92>/ay_cmd valid'
               *  S-Function (sfix_bitop): '<S92>/az_cmd valid'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              rtb_MathFunction_a[0] = (FMS_U.Auto_Cmd.cmd_mask & 65536U) > 0U ?
                FMS_U.Auto_Cmd.ax_cmd : 0.0F;
              rtb_MathFunction_a[1] = (FMS_U.Auto_Cmd.cmd_mask & 131072U) > 0U ?
                FMS_U.Auto_Cmd.ay_cmd : 0.0F;
              rtb_MathFunction_a[2] = (FMS_U.Auto_Cmd.cmd_mask & 262144U) > 0U ?
                FMS_U.Auto_Cmd.az_cmd : 0.0F;

              /* MultiPortSwitch: '<S87>/Index Vector' incorporates:
               *  Inport: '<Root>/Auto_Cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              switch (FMS_U.Auto_Cmd.frame) {
               case 0:
                /* SignalConversion generated from: '<S97>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S97>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_e[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_e[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_e[2];

                /* SignalConversion generated from: '<S97>/Vector Concatenate2' incorporates:
                 *  Constant: '<S97>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S97>/Trigonometric Function3' incorporates:
                 *  Gain: '<S96>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S97>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S97>/Trigonometric Function2' incorporates:
                 *  Gain: '<S96>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S97>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S97>/Gain' incorporates:
                 *  Trigonometry: '<S97>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S97>/Vector Concatenate1' incorporates:
                 *  Constant: '<S97>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S97>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S97>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* Product: '<S93>/Multiply' incorporates:
                 *  Concatenate: '<S97>/Vector Concatenate'
                 */
                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_Transpose_0[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_MathFunction_a[1] + rtb_Transpose[sfEvent] *
                    rtb_MathFunction_a[0]) + rtb_Transpose[sfEvent + 6] *
                    rtb_MathFunction_a[2];
                }

                /* End of Product: '<S93>/Multiply' */
                rtb_MathFunction_a[0] = rtb_Transpose_0[0];
                rtb_MathFunction_a[1] = rtb_Transpose_0[1];
                rtb_MathFunction_a[2] = rtb_Transpose_0[2];
                break;

               case 1:
                /* SignalConversion generated from: '<S99>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S99>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_o[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_o[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_o[2];

                /* SignalConversion generated from: '<S99>/Vector Concatenate2' incorporates:
                 *  Constant: '<S99>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Gain: '<S98>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S94>/Subtract'
                 */
                rtb_Divide_o_idx_1 = -(FMS_U.INS_Out.psi -
                  FMS_B.Cmd_In.offboard_psi_0);

                /* Trigonometry: '<S99>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S99>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(rtb_Divide_o_idx_1);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S99>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S99>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(rtb_Divide_o_idx_1);

                /* Gain: '<S99>/Gain' incorporates:
                 *  Trigonometry: '<S99>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S99>/Vector Concatenate1' incorporates:
                 *  Constant: '<S99>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S99>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S99>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* Product: '<S94>/Multiply3' incorporates:
                 *  Concatenate: '<S99>/Vector Concatenate'
                 */
                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_Transpose_0[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_MathFunction_a[1] + rtb_Transpose[sfEvent] *
                    rtb_MathFunction_a[0]) + rtb_Transpose[sfEvent + 6] *
                    rtb_MathFunction_a[2];
                }

                /* End of Product: '<S94>/Multiply3' */
                rtb_MathFunction_a[0] = rtb_Transpose_0[0];
                rtb_MathFunction_a[1] = rtb_Transpose_0[1];
                rtb_MathFunction_a[2] = rtb_Transpose_0[2];
                break;
              }

              /* End of MultiPortSwitch: '<S87>/Index Vector' */

              /* Product: '<S151>/Multiply' incorporates:
               *  Constant: '<S171>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  RelationalOperator: '<S171>/Compare'
               *  S-Function (sfix_bitop): '<S168>/u_cmd valid'
               *  S-Function (sfix_bitop): '<S168>/v_cmd valid'
               *  S-Function (sfix_bitop): '<S168>/w_cmd valid'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              rtb_Sum2_n[0] = (FMS_U.Auto_Cmd.cmd_mask & 8192U) > 0U ?
                FMS_U.Auto_Cmd.u_cmd : 0.0F;
              rtb_Sum2_n[1] = (FMS_U.Auto_Cmd.cmd_mask & 16384U) > 0U ?
                FMS_U.Auto_Cmd.v_cmd : 0.0F;
              rtb_Sum2_n[2] = (FMS_U.Auto_Cmd.cmd_mask & 32768U) > 0U ?
                FMS_U.Auto_Cmd.w_cmd : 0.0F;

              /* MultiPortSwitch: '<S151>/Index Vector' incorporates:
               *  Inport: '<Root>/Auto_Cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              switch (FMS_U.Auto_Cmd.frame) {
               case 0:
                /* SignalConversion generated from: '<S173>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S173>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_l[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_l[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_l[2];

                /* SignalConversion generated from: '<S173>/Vector Concatenate2' incorporates:
                 *  Constant: '<S173>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S173>/Trigonometric Function3' incorporates:
                 *  Gain: '<S172>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S173>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S173>/Trigonometric Function2' incorporates:
                 *  Gain: '<S172>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S173>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S173>/Gain' incorporates:
                 *  Trigonometry: '<S173>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S173>/Vector Concatenate1' incorporates:
                 *  Constant: '<S173>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S173>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S173>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* Product: '<S169>/Multiply' incorporates:
                 *  Concatenate: '<S173>/Vector Concatenate'
                 */
                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_Transpose_0[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_Sum2_n[1] + rtb_Transpose[sfEvent] * rtb_Sum2_n[0]) +
                    rtb_Transpose[sfEvent + 6] * rtb_Sum2_n[2];
                }

                /* End of Product: '<S169>/Multiply' */
                rtb_Sum2_n[0] = rtb_Transpose_0[0];
                rtb_Sum2_n[1] = rtb_Transpose_0[1];
                rtb_Sum2_n[2] = rtb_Transpose_0[2];
                break;

               case 1:
                /* SignalConversion generated from: '<S175>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S175>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_iz[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_iz[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_iz[2];

                /* SignalConversion generated from: '<S175>/Vector Concatenate2' incorporates:
                 *  Constant: '<S175>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Gain: '<S174>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S170>/Subtract'
                 */
                rtb_Divide_o_idx_1 = -(FMS_U.INS_Out.psi -
                  FMS_B.Cmd_In.offboard_psi_0);

                /* Trigonometry: '<S175>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S175>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(rtb_Divide_o_idx_1);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S175>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S175>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(rtb_Divide_o_idx_1);

                /* Gain: '<S175>/Gain' incorporates:
                 *  Trigonometry: '<S175>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S175>/Vector Concatenate1' incorporates:
                 *  Constant: '<S175>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S175>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S175>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* Product: '<S170>/Multiply3' incorporates:
                 *  Concatenate: '<S175>/Vector Concatenate'
                 */
                for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                  rtb_Transpose_0[sfEvent] = (rtb_Transpose[sfEvent + 3] *
                    rtb_Sum2_n[1] + rtb_Transpose[sfEvent] * rtb_Sum2_n[0]) +
                    rtb_Transpose[sfEvent + 6] * rtb_Sum2_n[2];
                }

                /* End of Product: '<S170>/Multiply3' */
                rtb_Sum2_n[0] = rtb_Transpose_0[0];
                rtb_Sum2_n[1] = rtb_Transpose_0[1];
                rtb_Sum2_n[2] = rtb_Transpose_0[2];
                break;
              }

              /* End of MultiPortSwitch: '<S151>/Index Vector' */
              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sum: '<S90>/Sum1' incorporates:
               *  Gain: '<S150>/Gain1'
               *  Gain: '<S150>/Gain2'
               */
              rtb_Divide_o_idx_1 = FMS_PARAM.XY_P * rtb_MatrixConcatenate3[0] +
                rtb_Sum2_n[0];
              rtb_Divide_o_idx_2 = FMS_PARAM.XY_P * rtb_MatrixConcatenate3[1] +
                rtb_Sum2_n[1];
              rtb_Sum2_n[2] += FMS_PARAM.Z_P * rtb_MatrixConcatenate3[2];

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Switch: '<S107>/Switch' incorporates:
               *  Constant: '<S122>/Constant'
               *  Constant: '<S123>/Constant'
               *  Constant: '<S124>/Constant'
               *  Constant: '<S127>/Constant'
               *  Constant: '<S129>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  RelationalOperator: '<S122>/Compare'
               *  RelationalOperator: '<S123>/Compare'
               *  RelationalOperator: '<S124>/Compare'
               *  RelationalOperator: '<S127>/Compare'
               *  RelationalOperator: '<S129>/Compare'
               *  S-Function (sfix_bitop): '<S107>/x_u_cmd'
               *  S-Function (sfix_bitop): '<S107>/y_v_cmd'
               *  S-Function (sfix_bitop): '<S108>/ax_cmd'
               *  S-Function (sfix_bitop): '<S108>/ay_cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               *  Switch: '<S108>/Switch'
               */
              if (FMS_U.Auto_Cmd.frame < 2) {
                /* Logic: '<S107>/Logical Operator' incorporates:
                 *  Constant: '<S123>/Constant'
                 *  Constant: '<S124>/Constant'
                 *  RelationalOperator: '<S123>/Compare'
                 *  RelationalOperator: '<S124>/Compare'
                 *  S-Function (sfix_bitop): '<S107>/x_u_cmd'
                 *  S-Function (sfix_bitop): '<S107>/y_v_cmd'
                 */
                rtb_LogicalOperator_i = (((FMS_U.Auto_Cmd.cmd_mask & 8320U) > 0U)
                  || ((FMS_U.Auto_Cmd.cmd_mask & 16640U) > 0U));
                rtb_Compare_n = rtb_LogicalOperator_i;

                /* Logic: '<S108>/Logical Operator' incorporates:
                 *  Constant: '<S127>/Constant'
                 *  Constant: '<S129>/Constant'
                 *  RelationalOperator: '<S127>/Compare'
                 *  RelationalOperator: '<S129>/Compare'
                 *  S-Function (sfix_bitop): '<S108>/ax_cmd'
                 *  S-Function (sfix_bitop): '<S108>/ay_cmd'
                 */
                rtb_LogicalOperator_o = (((FMS_U.Auto_Cmd.cmd_mask & 65536U) >
                  0U) || ((FMS_U.Auto_Cmd.cmd_mask & 131072U) > 0U));
                rtb_Switch_p_idx_1 = rtb_LogicalOperator_o;
              } else {
                rtb_LogicalOperator_i = ((FMS_U.Auto_Cmd.cmd_mask & 8320U) > 0U);
                rtb_Compare_n = ((FMS_U.Auto_Cmd.cmd_mask & 16640U) > 0U);
                rtb_LogicalOperator_o = ((FMS_U.Auto_Cmd.cmd_mask & 65536U) > 0U);
                rtb_Switch_p_idx_1 = ((FMS_U.Auto_Cmd.cmd_mask & 131072U) > 0U);
              }

              /* End of Switch: '<S107>/Switch' */

              /* Sum: '<S146>/Sum1' incorporates:
               *  Constant: '<S146>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S146>/Math Function'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_Divide_o_idx_0 = rt_remf(FMS_U.Auto_Cmd.psi_cmd, 6.28318548F)
                - FMS_U.INS_Out.psi;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Abs: '<S147>/Abs' */
              rtb_Square2 = fabsf(rtb_Divide_o_idx_0);

              /* Switch: '<S147>/Switch' incorporates:
               *  Constant: '<S147>/Constant'
               *  Constant: '<S148>/Constant'
               *  Product: '<S147>/Multiply'
               *  RelationalOperator: '<S148>/Compare'
               *  Signum: '<S147>/Sign'
               *  Sum: '<S147>/Subtract'
               */
              if (rtb_Square2 > 3.14159274F) {
                /* Signum: '<S147>/Sign' */
                if (rtb_Divide_o_idx_0 < 0.0F) {
                  rtb_Divide_o_idx_0 = -1.0F;
                } else {
                  rtb_Divide_o_idx_0 = (real32_T)(rtb_Divide_o_idx_0 > 0.0F);
                }

                rtb_Divide_o_idx_0 *= rtb_Square2 - 6.28318548F;
              }

              /* End of Switch: '<S147>/Switch' */
              /* End of Outputs for SubSystem: '<S37>/Offboard' */
              memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

              /* Outputs for IfAction SubSystem: '<S37>/Offboard' incorporates:
               *  ActionPort: '<S44>/Action Port'
               */
              /* BusAssignment: '<S44>/Bus Assignment' incorporates:
               *  Inport: '<Root>/Auto_Cmd'
               *  Outport: '<Root>/FMS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_a;
              FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_n;
              FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_k;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              FMS_Y.FMS_Out.p_cmd = FMS_U.Auto_Cmd.p_cmd;
              FMS_Y.FMS_Out.q_cmd = FMS_U.Auto_Cmd.q_cmd;
              FMS_Y.FMS_Out.r_cmd = FMS_U.Auto_Cmd.r_cmd;
              FMS_Y.FMS_Out.phi_cmd = FMS_U.Auto_Cmd.phi_cmd;
              FMS_Y.FMS_Out.theta_cmd = FMS_U.Auto_Cmd.theta_cmd;
              FMS_Y.FMS_Out.throttle_cmd = FMS_U.Auto_Cmd.throttle_cmd;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              FMS_Y.FMS_Out.ax_cmd = rtb_MathFunction_a[0];
              FMS_Y.FMS_Out.ay_cmd = rtb_MathFunction_a[1];
              FMS_Y.FMS_Out.az_cmd = rtb_MathFunction_a[2];

              /* Saturate: '<S146>/Saturation' */
              if (rtb_Divide_o_idx_0 > 0.314159274F) {
                rtb_Divide_o_idx_0 = 0.314159274F;
              } else if (rtb_Divide_o_idx_0 < -0.314159274F) {
                rtb_Divide_o_idx_0 = -0.314159274F;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S89>/Sum' incorporates:
               *  Constant: '<S145>/Constant'
               *  Constant: '<S149>/Constant'
               *  Gain: '<S143>/Gain2'
               *  Inport: '<Root>/Auto_Cmd'
               *  Product: '<S143>/Multiply2'
               *  Product: '<S144>/Multiply1'
               *  RelationalOperator: '<S145>/Compare'
               *  RelationalOperator: '<S149>/Compare'
               *  S-Function (sfix_bitop): '<S143>/psi_cmd valid'
               *  S-Function (sfix_bitop): '<S144>/psi_rate_cmd valid'
               *  Saturate: '<S146>/Saturation'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              rtb_MathFunction1 = ((FMS_U.Auto_Cmd.cmd_mask & 32U) > 0U ?
                                   FMS_PARAM.YAW_P * rtb_Divide_o_idx_0 : 0.0F)
                + ((FMS_U.Auto_Cmd.cmd_mask & 64U) > 0U ?
                   FMS_U.Auto_Cmd.psi_rate_cmd : 0.0F);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Saturate: '<S89>/Saturation' */
              if (rtb_MathFunction1 > FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
              } else if (rtb_MathFunction1 < -FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = rtb_MathFunction1;
              }

              /* End of Saturate: '<S89>/Saturation' */

              /* Saturate: '<S90>/Saturation2' */
              if (rtb_Divide_o_idx_1 > FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.u_cmd = FMS_PARAM.VEL_XY_LIM;
              } else if (rtb_Divide_o_idx_1 < -FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.u_cmd = -FMS_PARAM.VEL_XY_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_1;
              }

              /* End of Saturate: '<S90>/Saturation2' */

              /* Saturate: '<S90>/Saturation1' */
              if (rtb_Divide_o_idx_2 > FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.v_cmd = FMS_PARAM.VEL_XY_LIM;
              } else if (rtb_Divide_o_idx_2 < -FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.v_cmd = -FMS_PARAM.VEL_XY_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_2;
              }

              /* End of Saturate: '<S90>/Saturation1' */

              /* Saturate: '<S90>/Saturation3' */
              if (rtb_Sum2_n[2] > FMS_PARAM.VEL_Z_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.w_cmd = FMS_PARAM.VEL_Z_LIM;
              } else if (rtb_Sum2_n[2] < -FMS_PARAM.VEL_Z_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.w_cmd = -FMS_PARAM.VEL_Z_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.w_cmd = rtb_Sum2_n[2];
              }

              /* End of Saturate: '<S90>/Saturation3' */

              /* Outputs for Atomic SubSystem: '<S88>/q_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Outputs for Atomic SubSystem: '<S88>/r_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/phi_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/theta_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/psi_rate_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/u_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/v_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/w_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/ax_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/ay_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/az_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S88>/throttle_cmd_valid' */
              /* BusAssignment: '<S44>/Bus Assignment' incorporates:
               *  Constant: '<S100>/Constant'
               *  Constant: '<S101>/Constant'
               *  Constant: '<S102>/Constant'
               *  Constant: '<S103>/Constant'
               *  Constant: '<S104>/Constant'
               *  Constant: '<S105>/Constant'
               *  Constant: '<S106>/Constant'
               *  Constant: '<S125>/Constant'
               *  Constant: '<S128>/Constant'
               *  DataTypeConversion: '<S88>/Data Type Conversion10'
               *  DataTypeConversion: '<S88>/Data Type Conversion6'
               *  DataTypeConversion: '<S88>/Data Type Conversion7'
               *  DataTypeConversion: '<S88>/Data Type Conversion9'
               *  Inport: '<Root>/Auto_Cmd'
               *  MATLAB Function: '<S109>/bit_shift'
               *  MATLAB Function: '<S110>/bit_shift'
               *  MATLAB Function: '<S111>/bit_shift'
               *  MATLAB Function: '<S113>/bit_shift'
               *  MATLAB Function: '<S114>/bit_shift'
               *  MATLAB Function: '<S115>/bit_shift'
               *  MATLAB Function: '<S116>/bit_shift'
               *  MATLAB Function: '<S117>/bit_shift'
               *  MATLAB Function: '<S118>/bit_shift'
               *  MATLAB Function: '<S119>/bit_shift'
               *  MATLAB Function: '<S120>/bit_shift'
               *  MATLAB Function: '<S121>/bit_shift'
               *  Outport: '<Root>/FMS_Out'
               *  RelationalOperator: '<S100>/Compare'
               *  RelationalOperator: '<S101>/Compare'
               *  RelationalOperator: '<S102>/Compare'
               *  RelationalOperator: '<S103>/Compare'
               *  RelationalOperator: '<S104>/Compare'
               *  RelationalOperator: '<S105>/Compare'
               *  RelationalOperator: '<S106>/Compare'
               *  RelationalOperator: '<S125>/Compare'
               *  RelationalOperator: '<S128>/Compare'
               *  S-Function (sfix_bitop): '<S107>/z_w_cmd'
               *  S-Function (sfix_bitop): '<S108>/az_cmd'
               *  S-Function (sfix_bitop): '<S88>/p_cmd'
               *  S-Function (sfix_bitop): '<S88>/phi_cmd'
               *  S-Function (sfix_bitop): '<S88>/psi_psi_rate_cmd'
               *  S-Function (sfix_bitop): '<S88>/q_cmd'
               *  S-Function (sfix_bitop): '<S88>/r_cmd'
               *  S-Function (sfix_bitop): '<S88>/theta_cmd'
               *  S-Function (sfix_bitop): '<S88>/throttle_cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               *  Sum: '<S88>/Add'
               */
              FMS_Y.FMS_Out.cmd_mask = (uint16_T)((((((((((((uint32_T)(uint16_T)
                ((uint32_T)(((FMS_U.Auto_Cmd.cmd_mask & 2U) > 0U) << 1) +
                 (uint32_T)((FMS_U.Auto_Cmd.cmd_mask & 1U) > 0U)) + (uint16_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 4U) > 0U) << 2)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 8U) > 0U) << 3)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 16U) > 0U) << 4)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 96U) > 0U) << 5)) + (uint32_T)
                (rtb_LogicalOperator_i << 6)) + (uint32_T)(rtb_Compare_n << 7))
                + (uint32_T)(((FMS_U.Auto_Cmd.cmd_mask & 33280U) > 0U) << 8)) +
                (uint32_T)(rtb_LogicalOperator_o << 9)) + (uint32_T)
                (rtb_Switch_p_idx_1 << 10)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 262144U) > 0U) << 11)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 524288U) > 0U) << 12));

              /* End of Outputs for SubSystem: '<S88>/throttle_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/az_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/ay_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/ax_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/w_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/v_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/u_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/psi_rate_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/theta_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/phi_cmd_valid' */
              /* End of Outputs for SubSystem: '<S88>/r_cmd_valid' */
              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              /* End of Outputs for SubSystem: '<S88>/q_cmd_valid' */
              /* End of Outputs for SubSystem: '<S37>/Offboard' */
            }
            break;

           case 1:
            {
              boolean_T rtb_Compare_n;
              if (FMS_DW.SwitchCase_ActiveSubsystem_i != rtPrevAction) {
                /* InitializeConditions for IfAction SubSystem: '<S37>/Mission' incorporates:
                 *  ActionPort: '<S43>/Action Port'
                 */
                /* InitializeConditions for SwitchCase: '<S37>/Switch Case' incorporates:
                 *  UnitDelay: '<S46>/Delay Input1'
                 *
                 * Block description for '<S46>/Delay Input1':
                 *
                 *  Store in Global RAM
                 */
                FMS_DW.DelayInput1_DSTATE_pe = 0U;

                /* End of InitializeConditions for SubSystem: '<S37>/Mission' */

                /* SystemReset for IfAction SubSystem: '<S37>/Mission' incorporates:
                 *  ActionPort: '<S43>/Action Port'
                 */
                /* SystemReset for Resettable SubSystem: '<S43>/Mission_SubSystem' */
                /* SystemReset for SwitchCase: '<S37>/Switch Case' incorporates:
                 *  Delay: '<S64>/Delay'
                 *  DiscreteIntegrator: '<S83>/Discrete-Time Integrator'
                 */
                FMS_DW.icLoad = true;
                FMS_DW.l1_heading = 0.0F;

                /* End of SystemReset for SubSystem: '<S43>/Mission_SubSystem' */
                /* End of SystemReset for SubSystem: '<S37>/Mission' */
              }

              /* Outputs for IfAction SubSystem: '<S37>/Mission' incorporates:
               *  ActionPort: '<S43>/Action Port'
               */
              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* RelationalOperator: '<S46>/FixPt Relational Operator' incorporates:
               *  SignalConversion generated from: '<S32>/Signal Copy5'
               *  UnitDelay: '<S46>/Delay Input1'
               *
               * Block description for '<S46>/Delay Input1':
               *
               *  Store in Global RAM
               */
              rtb_Compare_n = (FMS_B.wp_index != FMS_DW.DelayInput1_DSTATE_pe);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Outputs for Resettable SubSystem: '<S43>/Mission_SubSystem' incorporates:
               *  ResetPort: '<S47>/Reset'
               */
              if (rtb_Compare_n && (FMS_PrevZCX.Mission_SubSystem_Reset_ZCE !=
                                    POS_ZCSIG)) {
                /* InitializeConditions for Delay: '<S64>/Delay' */
                FMS_DW.icLoad = true;

                /* InitializeConditions for DiscreteIntegrator: '<S83>/Discrete-Time Integrator' */
                FMS_DW.l1_heading = 0.0F;
              }

              FMS_PrevZCX.Mission_SubSystem_Reset_ZCE = rtb_Compare_n;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Reshape: '<S50>/Reshape2' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_TmpSignalConversionAtMat_bs[0] = FMS_U.INS_Out.x_R;
              rtb_TmpSignalConversionAtMat_bs[1] = FMS_U.INS_Out.y_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Delay: '<S64>/Delay' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              if (FMS_DW.icLoad) {
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                FMS_DW.Delay_DSTATE[0] = FMS_U.INS_Out.x_R;
                FMS_DW.Delay_DSTATE[1] = FMS_U.INS_Out.y_R;

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S64>/Sum' incorporates:
               *  Delay: '<S64>/Delay'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[0] -
                FMS_DW.Delay_DSTATE[0];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* SignalConversion generated from: '<S84>/Math Function' */
              rtb_MatrixConcatenate3[0] = rtb_Divide_o_idx_1;
              rtb_MathFunction_f[0] = rtb_Divide_o_idx_1;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S64>/Sum' incorporates:
               *  Delay: '<S64>/Delay'
               *  Product: '<S81>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[1] -
                FMS_DW.Delay_DSTATE[1];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sum: '<S84>/Sum of Elements' incorporates:
               *  Math: '<S84>/Math Function'
               *  SignalConversion generated from: '<S84>/Math Function'
               */
              rtb_Divide_o_idx_0 = rtb_MatrixConcatenate3[0] *
                rtb_MatrixConcatenate3[0] + rtb_Divide_o_idx_1 *
                rtb_Divide_o_idx_1;

              /* Math: '<S84>/Math Function1' incorporates:
               *  Sum: '<S84>/Sum of Elements'
               *
               * About '<S84>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Divide_o_idx_0 < 0.0F) {
                rtb_Divide_o_idx_2 = -sqrtf(fabsf(rtb_Divide_o_idx_0));
              } else {
                rtb_Divide_o_idx_2 = sqrtf(rtb_Divide_o_idx_0);
              }

              /* End of Math: '<S84>/Math Function1' */

              /* Switch: '<S84>/Switch' incorporates:
               *  Constant: '<S84>/Constant'
               *  Product: '<S84>/Product'
               */
              if (rtb_Divide_o_idx_2 > 0.0F) {
                rtb_Divide_o_idx_0 = rtb_MathFunction_f[0];
                rtb_MathFunction1 = rtb_Divide_o_idx_2;
              } else {
                rtb_Divide_o_idx_0 = 0.0F;
                rtb_Divide_o_idx_1 = 0.0F;
                rtb_MathFunction1 = 1.0F;
              }

              /* End of Switch: '<S84>/Switch' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S61>/Sum' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_u_b = FMS_U.INS_Out.x_R - FMS_B.Cmd_In.sp_waypoint[0];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              rtb_MathFunction_f[0] = rtb_u_b * rtb_u_b;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S61>/Sum' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S68>/Square'
               *  Product: '<S81>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_u_b = FMS_U.INS_Out.y_R - FMS_B.Cmd_In.sp_waypoint[1];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sqrt: '<S68>/Sqrt' incorporates:
               *  Math: '<S68>/Square'
               *  Sum: '<S68>/Sum of Elements'
               */
              rtb_Divide_o_idx_2 = sqrtf(rtb_u_b * rtb_u_b + rtb_MathFunction_f
                [0]);

              /* Switch: '<S61>/Switch' incorporates:
               *  Constant: '<S61>/vel'
               */
              if (rtb_Divide_o_idx_2 > FMS_PARAM.L1) {
                rtb_Divide_o_idx_2 = FMS_PARAM.CRUISE_SPEED;
              } else {
                /* Gain: '<S61>/Gain' */
                rtb_Divide_o_idx_2 *= 0.5F;

                /* Saturate: '<S61>/Saturation' */
                if (rtb_Divide_o_idx_2 > FMS_PARAM.CRUISE_SPEED) {
                  rtb_Divide_o_idx_2 = FMS_PARAM.CRUISE_SPEED;
                } else if (rtb_Divide_o_idx_2 < 0.5F) {
                  rtb_Divide_o_idx_2 = 0.5F;
                }

                /* End of Saturate: '<S61>/Saturation' */
              }

              /* End of Switch: '<S61>/Switch' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Gain: '<S85>/Gain' incorporates:
               *  DiscreteIntegrator: '<S83>/Discrete-Time Integrator'
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sum: '<S83>/Add'
               */
              rtb_u_b = -(FMS_U.INS_Out.psi - FMS_DW.l1_heading);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Trigonometry: '<S86>/Trigonometric Function1' incorporates:
               *  Trigonometry: '<S86>/Trigonometric Function3'
               */
              rtb_Square2 = arm_cos_f32(rtb_u_b);
              rtb_Transpose[0] = rtb_Square2;

              /* Trigonometry: '<S86>/Trigonometric Function' incorporates:
               *  Trigonometry: '<S86>/Trigonometric Function2'
               */
              rtb_u_b = arm_sin_f32(rtb_u_b);
              rtb_Transpose[1] = rtb_u_b;

              /* SignalConversion generated from: '<S86>/Vector Concatenate1' incorporates:
               *  Constant: '<S86>/Constant3'
               */
              rtb_Transpose[2] = 0.0F;

              /* Gain: '<S86>/Gain' */
              rtb_Transpose[3] = -rtb_u_b;

              /* Trigonometry: '<S86>/Trigonometric Function3' */
              rtb_Transpose[4] = rtb_Square2;

              /* SignalConversion generated from: '<S86>/Vector Concatenate2' incorporates:
               *  Constant: '<S86>/Constant4'
               */
              rtb_Transpose[5] = 0.0F;

              /* SignalConversion generated from: '<S86>/Vector Concatenate' incorporates:
               *  Concatenate: '<S86>/Vector Concatenate3'
               */
              rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3[0];

              /* Product: '<S82>/Multiply2' incorporates:
               *  Product: '<S84>/Divide'
               */
              rtb_Divide_o_idx_0 = rtb_Divide_o_idx_0 / rtb_MathFunction1 *
                rtb_Divide_o_idx_2;

              /* SignalConversion generated from: '<S86>/Vector Concatenate' incorporates:
               *  Concatenate: '<S86>/Vector Concatenate3'
               */
              rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3[1];

              /* Product: '<S82>/Multiply2' incorporates:
               *  Product: '<S84>/Divide'
               */
              rtb_Divide_o_idx_1 = rtb_Divide_o_idx_1 / rtb_MathFunction1 *
                rtb_Divide_o_idx_2;

              /* SignalConversion generated from: '<S86>/Vector Concatenate' incorporates:
               *  Concatenate: '<S86>/Vector Concatenate3'
               */
              rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3[2];

              /* Product: '<S64>/Multiply' incorporates:
               *  Concatenate: '<S86>/Vector Concatenate'
               */
              for (sfEvent = 0; sfEvent < 3; sfEvent++) {
                rtb_MathFunction_a[sfEvent] = rtb_Transpose[sfEvent + 3] *
                  rtb_Divide_o_idx_1 + rtb_Transpose[sfEvent] *
                  rtb_Divide_o_idx_0;
              }

              /* End of Product: '<S64>/Multiply' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S65>/Sum' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_MathFunction_h[0] = FMS_U.INS_Out.x_R -
                FMS_B.Cmd_In.cur_waypoint[0];
              rtb_MathFunction_h[1] = FMS_U.INS_Out.y_R -
                FMS_B.Cmd_In.cur_waypoint[1];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              rtb_MathFunction_h[0] *= rtb_MathFunction_h[0];

              /* Sum: '<S66>/Sum of Elements' incorporates:
               *  Math: '<S66>/Square'
               */
              rtb_Divide_o_idx_0 = rtb_MathFunction_h[1] * rtb_MathFunction_h[1]
                + rtb_MathFunction_h[0];

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S65>/Sum1' incorporates:
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_Rem_h = FMS_B.Cmd_In.sp_waypoint[0] -
                FMS_B.Cmd_In.cur_waypoint[0];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              rtb_MathFunction_h[0] = rtb_Rem_h * rtb_Rem_h;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S65>/Sum1' incorporates:
               *  Math: '<S67>/Square'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_Rem_h = FMS_B.Cmd_In.sp_waypoint[1] -
                FMS_B.Cmd_In.cur_waypoint[1];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Product: '<S65>/Divide' incorporates:
               *  Math: '<S67>/Square'
               *  Sqrt: '<S66>/Sqrt'
               *  Sqrt: '<S67>/Sqrt'
               *  Sum: '<S66>/Sum of Elements'
               *  Sum: '<S67>/Sum of Elements'
               */
              rtb_MathFunction1 = sqrtf(rtb_Divide_o_idx_0) / sqrtf(rtb_Rem_h *
                rtb_Rem_h + rtb_MathFunction_h[0]);

              /* Saturate: '<S65>/Saturation' */
              if (rtb_MathFunction1 > 1.0F) {
                rtb_MathFunction1 = 1.0F;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Gain: '<S60>/Gain' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S65>/Multiply'
               *  Saturate: '<S65>/Saturation'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               *  Sum: '<S60>/Sum2'
               *  Sum: '<S65>/Add'
               *  Sum: '<S65>/Subtract'
               */
              rtb_MathFunction1 = (FMS_U.INS_Out.h_R -
                                   ((FMS_B.Cmd_In.sp_waypoint[2] -
                FMS_B.Cmd_In.cur_waypoint[2]) * rtb_MathFunction1 +
                                    FMS_B.Cmd_In.cur_waypoint[2])) *
                FMS_PARAM.Z_P;

              /* Sum: '<S47>/Sum' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S80>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_MathFunction_h[0] = FMS_B.Cmd_In.sp_waypoint[0] -
                FMS_U.INS_Out.x_R;
              rtb_MathFunction_h[1] = FMS_B.Cmd_In.sp_waypoint[1] -
                FMS_U.INS_Out.y_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Math: '<S59>/Math Function' incorporates:
               *  SignalConversion generated from: '<S59>/Math Function'
               */
              rtb_MathFunction_f[0] = rtb_MathFunction_h[1] *
                rtb_MathFunction_h[1];
              rtb_MathFunction_f[1] = rtb_MathFunction_h[0] *
                rtb_MathFunction_h[0];

              /* Sum: '<S59>/Sum of Elements' */
              rtb_Divide_o_idx_0 = rtb_MathFunction_f[0] + rtb_MathFunction_f[1];

              /* Math: '<S59>/Math Function1' incorporates:
               *  Sum: '<S59>/Sum of Elements'
               *
               * About '<S59>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Divide_o_idx_0 < 0.0F) {
                rtb_Divide_o_idx_1 = -sqrtf(fabsf(rtb_Divide_o_idx_0));
              } else {
                rtb_Divide_o_idx_1 = sqrtf(rtb_Divide_o_idx_0);
              }

              /* End of Math: '<S59>/Math Function1' */

              /* Switch: '<S59>/Switch' incorporates:
               *  Constant: '<S59>/Constant'
               *  Product: '<S59>/Product'
               */
              if (rtb_Divide_o_idx_1 > 0.0F) {
                rtb_MatrixConcatenate3[0] = rtb_MathFunction_h[1];
                rtb_MatrixConcatenate3[1] = rtb_MathFunction_h[0];
                rtb_MatrixConcatenate3[2] = rtb_Divide_o_idx_1;
              } else {
                rtb_MatrixConcatenate3[0] = 0.0F;
                rtb_MatrixConcatenate3[1] = 0.0F;
                rtb_MatrixConcatenate3[2] = 1.0F;
              }

              /* End of Switch: '<S59>/Switch' */

              /* Product: '<S59>/Divide' */
              rtb_Rem_h = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S52>/Dot Product' incorporates:
               *  Product: '<S58>/Divide'
               */
              rtb_Divide_o_idx_0 = FMS_ConstB.Divide[0] * rtb_Rem_h;
              rtb_MathFunction_h[0] = rtb_Rem_h;

              /* Product: '<S59>/Divide' */
              rtb_Rem_h = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S52>/Dot Product' incorporates:
               *  Product: '<S58>/Divide'
               */
              rtb_Square2 = FMS_ConstB.Divide[1] * rtb_Rem_h +
                rtb_Divide_o_idx_0;
              rtb_MathFunction_h[1] = rtb_Rem_h;

              /* Sum: '<S57>/Subtract' incorporates:
               *  Product: '<S57>/Multiply'
               *  Product: '<S57>/Multiply1'
               *  Product: '<S59>/Divide'
               */
              rtb_u_b = rtb_MathFunction_h[0] * FMS_ConstB.Divide[1] -
                FMS_ConstB.Divide[0] * rtb_Rem_h;

              /* Signum: '<S52>/Sign1' */
              if (rtb_u_b < 0.0F) {
                rtb_Divide_o_idx_1 = -1.0F;
              } else {
                rtb_Divide_o_idx_1 = (real32_T)(rtb_u_b > 0.0F);
              }

              /* End of Signum: '<S52>/Sign1' */

              /* Trigonometry: '<S52>/Acos' incorporates:
               *  DotProduct: '<S52>/Dot Product'
               */
              if (rtb_Square2 > 1.0F) {
                rtb_Square2 = 1.0F;
              } else if (rtb_Square2 < -1.0F) {
                rtb_Square2 = -1.0F;
              }

              /* Switch: '<S52>/Switch2' incorporates:
               *  Constant: '<S52>/Constant4'
               */
              if (rtb_Divide_o_idx_1 == 0.0F) {
                rtb_Divide_o_idx_1 = 1.0F;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Math: '<S55>/Rem' incorporates:
               *  Constant: '<S55>/Constant1'
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S52>/Multiply'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sum: '<S53>/Sum'
               *  Switch: '<S52>/Switch2'
               *  Trigonometry: '<S52>/Acos'
               */
              rtb_Divide_o_idx_1 = rt_remf(acosf(rtb_Square2) *
                rtb_Divide_o_idx_1 - FMS_U.INS_Out.psi, 6.28318548F);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Switch: '<S55>/Switch' incorporates:
               *  Abs: '<S55>/Abs'
               *  Constant: '<S55>/Constant'
               *  Constant: '<S56>/Constant'
               *  Product: '<S55>/Multiply'
               *  RelationalOperator: '<S56>/Compare'
               *  Signum: '<S55>/Sign'
               *  Sum: '<S55>/Add'
               */
              if (fabsf(rtb_Divide_o_idx_1) > 3.14159274F) {
                /* Signum: '<S55>/Sign' */
                if (rtb_Divide_o_idx_1 < 0.0F) {
                  rtb_Divide_o_idx_0 = -1.0F;
                } else {
                  rtb_Divide_o_idx_0 = (real32_T)(rtb_Divide_o_idx_1 > 0.0F);
                }

                rtb_Divide_o_idx_1 -= 6.28318548F * rtb_Divide_o_idx_0;
              }

              /* End of Switch: '<S55>/Switch' */
              /* End of Outputs for SubSystem: '<S43>/Mission_SubSystem' */
              /* End of Outputs for SubSystem: '<S37>/Mission' */
              memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

              /* Outputs for IfAction SubSystem: '<S37>/Mission' incorporates:
               *  ActionPort: '<S43>/Action Port'
               */
              /* Outputs for Resettable SubSystem: '<S43>/Mission_SubSystem' incorporates:
               *  ResetPort: '<S47>/Reset'
               */
              /* BusAssignment: '<S47>/Bus Assignment' incorporates:
               *  BusAssignment: '<S34>/Bus Assignment'
               *  Outport: '<Root>/FMS_Out'
               */
              FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_l;
              FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_bp;
              FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_b;
              FMS_Y.FMS_Out.u_cmd = rtb_MathFunction_a[0];
              FMS_Y.FMS_Out.v_cmd = rtb_MathFunction_a[1];

              /* Saturate: '<S60>/Saturation1' */
              if (rtb_MathFunction1 > FMS_PARAM.VEL_Z_LIM) {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.w_cmd = FMS_PARAM.VEL_Z_LIM;
              } else if (rtb_MathFunction1 < -FMS_PARAM.VEL_Z_LIM) {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.w_cmd = -FMS_PARAM.VEL_Z_LIM;
              } else {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.w_cmd = rtb_MathFunction1;
              }

              /* End of Saturate: '<S60>/Saturation1' */

              /* Gain: '<S53>/Gain2' */
              rtb_MathFunction1 = FMS_PARAM.YAW_P * rtb_Divide_o_idx_1;

              /* Saturate: '<S53>/Saturation' */
              if (rtb_MathFunction1 > FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
              } else if (rtb_MathFunction1 < -FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
              } else {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = rtb_MathFunction1;
              }

              /* End of Saturate: '<S53>/Saturation' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* SignalConversion generated from: '<S75>/Square' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_MathFunction_f[0] = FMS_U.INS_Out.vn;
              rtb_MathFunction_f[1] = FMS_U.INS_Out.ve;

              /* Sum: '<S77>/Sum of Elements' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S77>/Math Function'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sum: '<S75>/Sum of Elements'
               */
              rtb_Divide_o_idx_0 = FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
                FMS_U.INS_Out.ve * FMS_U.INS_Out.ve;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Math: '<S77>/Math Function1' incorporates:
               *  Sum: '<S77>/Sum of Elements'
               *
               * About '<S77>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Divide_o_idx_0 < 0.0F) {
                rtb_Square2 = -sqrtf(fabsf(rtb_Divide_o_idx_0));
              } else {
                rtb_Square2 = sqrtf(rtb_Divide_o_idx_0);
              }

              /* End of Math: '<S77>/Math Function1' */

              /* Switch: '<S77>/Switch' incorporates:
               *  Constant: '<S77>/Constant'
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S77>/Product'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              if (rtb_Square2 > 0.0F) {
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                rtb_MatrixConcatenate3[0] = FMS_U.INS_Out.vn;
                rtb_MatrixConcatenate3[1] = FMS_U.INS_Out.ve;

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                rtb_MatrixConcatenate3[2] = rtb_Square2;
              } else {
                rtb_MatrixConcatenate3[0] = 0.0F;
                rtb_MatrixConcatenate3[1] = 0.0F;
                rtb_MatrixConcatenate3[2] = 1.0F;
              }

              /* End of Switch: '<S77>/Switch' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* MATLAB Function: '<S62>/NearbyRefWP' incorporates:
               *  Constant: '<S47>/L1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              FMS_NearbyRefWP(&FMS_B.Cmd_In.sp_waypoint[0],
                              rtb_TmpSignalConversionAtMat_bs, FMS_PARAM.L1,
                              rtb_MathFunction_h, &rtb_Square2);

              /* MATLAB Function: '<S62>/SearchL1RefWP' incorporates:
               *  Constant: '<S47>/L1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              FMS_SearchL1RefWP(&FMS_B.Cmd_In.cur_waypoint[0],
                                &FMS_B.Cmd_In.sp_waypoint[0],
                                rtb_TmpSignalConversionAtMat_bs, FMS_PARAM.L1,
                                rtb_MathFunction_f, &rtb_u_b);

              /* MATLAB Function: '<S62>/OutRegionRegWP' incorporates:
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              FMS_OutRegionRegWP(&FMS_B.Cmd_In.cur_waypoint[0],
                                 &FMS_B.Cmd_In.sp_waypoint[0],
                                 rtb_TmpSignalConversionAtMat_bs,
                                 rtb_MathFunction_ab);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Switch: '<S62>/Switch1' incorporates:
               *  Constant: '<S70>/Constant'
               *  RelationalOperator: '<S70>/Compare'
               */
              if (rtb_Square2 <= 0.0F) {
                /* Switch: '<S62>/Switch' incorporates:
                 *  Constant: '<S69>/Constant'
                 *  Product: '<S80>/Divide'
                 *  RelationalOperator: '<S69>/Compare'
                 */
                if (rtb_u_b >= 0.0F) {
                  rtb_MathFunction_h[0] = rtb_MathFunction_f[0];
                  rtb_MathFunction_h[1] = rtb_MathFunction_f[1];
                } else {
                  rtb_MathFunction_h[0] = rtb_MathFunction_ab[0];
                  rtb_MathFunction_h[1] = rtb_MathFunction_ab[1];
                }

                /* End of Switch: '<S62>/Switch' */
              }

              /* End of Switch: '<S62>/Switch1' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S63>/Subtract' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S80>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_Rem_h = rtb_MathFunction_h[0] - FMS_U.INS_Out.x_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              rtb_MathFunction_h[0] = rtb_Rem_h;
              rtb_TmpSignalConversionAtMat_bs[0] = rtb_Rem_h * rtb_Rem_h;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S63>/Subtract' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S78>/Math Function'
               *  Product: '<S80>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_Rem_h = rtb_MathFunction_h[1] - FMS_U.INS_Out.y_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sum: '<S78>/Sum of Elements' incorporates:
               *  Math: '<S78>/Math Function'
               *  Sum: '<S76>/Sum of Elements'
               */
              rtb_Divide_o_idx_1 = rtb_Rem_h * rtb_Rem_h +
                rtb_TmpSignalConversionAtMat_bs[0];

              /* Math: '<S78>/Math Function1' incorporates:
               *  Sum: '<S78>/Sum of Elements'
               *
               * About '<S78>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Divide_o_idx_1 < 0.0F) {
                rtb_Square2 = -sqrtf(fabsf(rtb_Divide_o_idx_1));
              } else {
                rtb_Square2 = sqrtf(rtb_Divide_o_idx_1);
              }

              /* End of Math: '<S78>/Math Function1' */

              /* Switch: '<S78>/Switch' incorporates:
               *  Constant: '<S78>/Constant'
               *  Product: '<S78>/Product'
               *  Switch: '<S81>/Switch'
               */
              if (rtb_Square2 > 0.0F) {
                rtb_MathFunction_a[0] = rtb_MathFunction_h[0];
                rtb_MathFunction_a[1] = rtb_Rem_h;
                rtb_MathFunction_a[2] = rtb_Square2;
              } else {
                rtb_MathFunction_a[0] = 0.0F;
                rtb_MathFunction_a[1] = 0.0F;
                rtb_MathFunction_a[2] = 1.0F;
              }

              /* End of Switch: '<S78>/Switch' */

              /* Product: '<S77>/Divide' */
              rtb_MathFunction_f[0] = rtb_MatrixConcatenate3[0] /
                rtb_MatrixConcatenate3[2];
              rtb_MathFunction_f[1] = rtb_MatrixConcatenate3[1] /
                rtb_MatrixConcatenate3[2];

              /* Sum: '<S80>/Sum of Elements' incorporates:
               *  Math: '<S80>/Math Function'
               *  SignalConversion generated from: '<S80>/Math Function'
               */
              rtb_u_b = rtb_MathFunction_f[1] * rtb_MathFunction_f[1] +
                rtb_MathFunction_f[0] * rtb_MathFunction_f[0];

              /* Math: '<S80>/Math Function1' incorporates:
               *  Sum: '<S80>/Sum of Elements'
               *
               * About '<S80>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_u_b < 0.0F) {
                rtb_Square2 = -sqrtf(fabsf(rtb_u_b));
              } else {
                rtb_Square2 = sqrtf(rtb_u_b);
              }

              /* End of Math: '<S80>/Math Function1' */

              /* Switch: '<S80>/Switch' incorporates:
               *  Constant: '<S80>/Constant'
               *  Product: '<S80>/Product'
               */
              if (rtb_Square2 > 0.0F) {
                rtb_MatrixConcatenate3[0] = rtb_MathFunction_f[1];
                rtb_MatrixConcatenate3[1] = rtb_MathFunction_f[0];
                rtb_MatrixConcatenate3[2] = rtb_Square2;
              } else {
                rtb_MatrixConcatenate3[0] = 0.0F;
                rtb_MatrixConcatenate3[1] = 0.0F;
                rtb_MatrixConcatenate3[2] = 1.0F;
              }

              /* End of Switch: '<S80>/Switch' */

              /* Product: '<S78>/Divide' incorporates:
               *  Product: '<S81>/Divide'
               */
              rtb_MathFunction_f[0] = rtb_MathFunction_a[0] /
                rtb_MathFunction_a[2];
              rtb_MathFunction_f[1] = rtb_MathFunction_a[1] /
                rtb_MathFunction_a[2];

              /* Sum: '<S81>/Sum of Elements' incorporates:
               *  Math: '<S81>/Math Function'
               *  SignalConversion generated from: '<S81>/Math Function'
               */
              rtb_u_b = rtb_MathFunction_f[1] * rtb_MathFunction_f[1] +
                rtb_MathFunction_f[0] * rtb_MathFunction_f[0];

              /* Math: '<S81>/Math Function1' incorporates:
               *  Sum: '<S81>/Sum of Elements'
               *
               * About '<S81>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_u_b < 0.0F) {
                rtb_Square2 = -sqrtf(fabsf(rtb_u_b));
              } else {
                rtb_Square2 = sqrtf(rtb_u_b);
              }

              /* End of Math: '<S81>/Math Function1' */

              /* Switch: '<S81>/Switch' incorporates:
               *  Constant: '<S81>/Constant'
               *  Product: '<S81>/Product'
               */
              if (rtb_Square2 > 0.0F) {
                rtb_MathFunction_a[0] = rtb_MathFunction_f[1];
                rtb_MathFunction_a[1] = rtb_MathFunction_f[0];
                rtb_MathFunction_a[2] = rtb_Square2;
              } else {
                rtb_MathFunction_a[0] = 0.0F;
                rtb_MathFunction_a[1] = 0.0F;
                rtb_MathFunction_a[2] = 1.0F;
              }

              /* End of Switch: '<S81>/Switch' */

              /* Product: '<S81>/Divide' */
              rtb_u_b = rtb_MathFunction_a[0] / rtb_MathFunction_a[2];

              /* Product: '<S80>/Divide' */
              rtb_Rem_h = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S74>/Dot Product' */
              rtb_MathFunction1 = rtb_Rem_h * rtb_u_b;
              rtb_MathFunction_f[0] = rtb_u_b;
              rtb_MathFunction_h[0] = rtb_Rem_h;

              /* Product: '<S81>/Divide' incorporates:
               *  Product: '<S80>/Divide'
               */
              rtb_u_b = rtb_MathFunction_a[1] / rtb_MathFunction_a[2];

              /* Product: '<S80>/Divide' */
              rtb_Rem_h = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S74>/Dot Product' */
              rtb_MathFunction1 += rtb_Rem_h * rtb_u_b;

              /* Sqrt: '<S75>/Sqrt' */
              rtb_Square2 = sqrtf(rtb_Divide_o_idx_0);

              /* Gain: '<S63>/Gain' incorporates:
               *  Math: '<S63>/Square'
               */
              rtb_Divide_o_idx_0 = rtb_Square2 * rtb_Square2 * 2.0F;

              /* Sum: '<S79>/Subtract' incorporates:
               *  Product: '<S79>/Multiply'
               *  Product: '<S79>/Multiply1'
               */
              rtb_u_b = rtb_MathFunction_f[0] * rtb_Rem_h - rtb_MathFunction_h[0]
                * rtb_u_b;

              /* Signum: '<S74>/Sign1' */
              if (rtb_u_b < 0.0F) {
                rtb_Square2 = -1.0F;
              } else {
                rtb_Square2 = (real32_T)(rtb_u_b > 0.0F);
              }

              /* End of Signum: '<S74>/Sign1' */

              /* Trigonometry: '<S74>/Acos' incorporates:
               *  DotProduct: '<S74>/Dot Product'
               */
              if (rtb_MathFunction1 > 1.0F) {
                rtb_MathFunction1 = 1.0F;
              } else if (rtb_MathFunction1 < -1.0F) {
                rtb_MathFunction1 = -1.0F;
              }

              /* Switch: '<S74>/Switch2' incorporates:
               *  Constant: '<S74>/Constant4'
               */
              if (rtb_Square2 == 0.0F) {
                rtb_Square2 = 1.0F;
              }

              /* Product: '<S74>/Multiply' incorporates:
               *  Switch: '<S74>/Switch2'
               *  Trigonometry: '<S74>/Acos'
               */
              rtb_MathFunction1 = acosf(rtb_MathFunction1) * rtb_Square2;

              /* Update for Delay: '<S64>/Delay' */
              FMS_DW.icLoad = false;

              /* Saturate: '<S63>/Saturation' */
              if (rtb_MathFunction1 > 1.57079637F) {
                rtb_MathFunction1 = 1.57079637F;
              } else if (rtb_MathFunction1 < -1.57079637F) {
                rtb_MathFunction1 = -1.57079637F;
              }

              /* Update for DiscreteIntegrator: '<S83>/Discrete-Time Integrator' incorporates:
               *  Constant: '<S47>/L1'
               *  Constant: '<S63>/Constant'
               *  MinMax: '<S63>/Max'
               *  MinMax: '<S63>/Min'
               *  Product: '<S63>/Divide'
               *  Product: '<S63>/Multiply1'
               *  Product: '<S64>/Divide1'
               *  Saturate: '<S63>/Saturation'
               *  Sqrt: '<S76>/Sqrt'
               *  Trigonometry: '<S63>/Sin'
               */
              FMS_DW.l1_heading += arm_sin_f32(rtb_MathFunction1) *
                rtb_Divide_o_idx_0 / fminf(FMS_PARAM.L1, fmaxf(sqrtf
                (rtb_Divide_o_idx_1), 0.5F)) / rtb_Divide_o_idx_2 * 0.004F;

              /* End of Outputs for SubSystem: '<S43>/Mission_SubSystem' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Update for UnitDelay: '<S46>/Delay Input1' incorporates:
               *  SignalConversion generated from: '<S32>/Signal Copy5'
               *
               * Block description for '<S46>/Delay Input1':
               *
               *  Store in Global RAM
               */
              FMS_DW.DelayInput1_DSTATE_pe = FMS_B.wp_index;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              /* End of Outputs for SubSystem: '<S37>/Mission' */
            }
            break;

           default:
            memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

            /* Outputs for IfAction SubSystem: '<S37>/Unknown' incorporates:
             *  ActionPort: '<S45>/Action Port'
             */
            /* BusAssignment: '<S45>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Constant: '<S45>/Constant2'
             *  Constant: '<S45>/Constant3'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.reset = 1U;
            FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_ga;
            FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_b;
            FMS_Y.FMS_Out.actuator_cmd[0] = 0U;
            FMS_Y.FMS_Out.actuator_cmd[1] = 0U;
            FMS_Y.FMS_Out.actuator_cmd[2] = 0U;
            FMS_Y.FMS_Out.actuator_cmd[3] = 0U;
            for (sfEvent = 0; sfEvent < 12; sfEvent++) {
              FMS_Y.FMS_Out.actuator_cmd[sfEvent + 4] = 0U;
            }

            /* End of BusAssignment: '<S45>/Bus Assignment' */
            /* End of Outputs for SubSystem: '<S37>/Unknown' */
            break;
          }

          /* End of Outputs for SubSystem: '<S33>/Auto' */
        }
        break;

       case 2:
        if (FMS_DW.SwitchCase_ActiveSubsystem_b != rtPrevAction) {
          /* SystemReset for IfAction SubSystem: '<S33>/Stabilize' incorporates:
           *  ActionPort: '<S40>/Action Port'
           */
          /* SystemReset for SwitchCase: '<S33>/Switch Case' incorporates:
           *  Chart: '<S209>/Motion State'
           *  Chart: '<S221>/Motion State'
           */
          FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_g);
          FMS_MotionState_i_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_d);

          /* End of SystemReset for SubSystem: '<S33>/Stabilize' */
        }

        /* Outputs for IfAction SubSystem: '<S33>/Stabilize' incorporates:
         *  ActionPort: '<S40>/Action Port'
         */
        /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
        /* Chart: '<S221>/Motion State' incorporates:
         *  Constant: '<S221>/Constant'
         *  Inport: '<Root>/INS_Out'
         *  Math: '<S221>/Square'
         *  Math: '<S221>/Square1'
         *  SignalConversion generated from: '<S32>/Signal Copy1'
         *  Sqrt: '<S221>/Sqrt'
         *  Sum: '<S221>/Add'
         */
        FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
          FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                        &FMS_DW.sf_MotionState_g);

        /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

        /* SwitchCase: '<S220>/Switch Case' incorporates:
         *  Inport: '<Root>/INS_Out'
         *  Inport: '<Root>/Pilot_Cmd'
         *  SignalConversion generated from: '<S32>/Signal Copy1'
         *  SignalConversion generated from: '<S32>/Signal Copy2'
         */
        rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_p;
        switch (rtb_state_ee) {
         case MotionState_Hold:
          FMS_DW.SwitchCase_ActiveSubsystem_p = 0;
          break;

         case MotionState_Brake:
          FMS_DW.SwitchCase_ActiveSubsystem_p = 1;
          break;

         default:
          FMS_DW.SwitchCase_ActiveSubsystem_p = 2;
          break;
        }

        switch (FMS_DW.SwitchCase_ActiveSubsystem_p) {
         case 0:
          if (FMS_DW.SwitchCase_ActiveSubsystem_p != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S220>/Hold Control' incorporates:
             *  ActionPort: '<S223>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S220>/Switch Case' */
            FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_f);

            /* End of SystemReset for SubSystem: '<S220>/Hold Control' */
          }

          /* Outputs for IfAction SubSystem: '<S220>/Hold Control' incorporates:
           *  ActionPort: '<S223>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                            FMS_U.INS_Out.psi, FMS_B.Merge_o,
                            &FMS_ConstB.HoldControl_f, &FMS_DW.HoldControl_f);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S220>/Hold Control' */
          break;

         case 1:
          /* Outputs for IfAction SubSystem: '<S220>/Brake Control' incorporates:
           *  ActionPort: '<S222>/Action Port'
           */
          FMS_BrakeControl_h(FMS_B.Merge_o);

          /* End of Outputs for SubSystem: '<S220>/Brake Control' */
          break;

         default:
          if (FMS_DW.SwitchCase_ActiveSubsystem_p != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S220>/Move Control' incorporates:
             *  ActionPort: '<S224>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S220>/Switch Case' */
            FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_i);

            /* End of SystemReset for SubSystem: '<S220>/Move Control' */
          }

          /* Outputs for IfAction SubSystem: '<S220>/Move Control' incorporates:
           *  ActionPort: '<S224>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                            FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_o,
                            &FMS_ConstB.MoveControl_i, &FMS_DW.MoveControl_i);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S220>/Move Control' */
          break;
        }

        /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
        /* Chart: '<S209>/Motion State' incorporates:
         *  Abs: '<S209>/Abs'
         *  Constant: '<S209>/Constant'
         *  Inport: '<Root>/INS_Out'
         *  SignalConversion generated from: '<S32>/Signal Copy1'
         */
        FMS_MotionState_i(0.0F, fabsf(FMS_U.INS_Out.r), &rtb_state_ee,
                          &FMS_DW.sf_MotionState_d);

        /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

        /* SwitchCase: '<S208>/Switch Case' incorporates:
         *  Inport: '<Root>/INS_Out'
         *  Inport: '<Root>/Pilot_Cmd'
         *  SignalConversion generated from: '<S32>/Signal Copy1'
         *  SignalConversion generated from: '<S32>/Signal Copy2'
         */
        rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_bn;
        switch (rtb_state_ee) {
         case MotionState_Hold:
          FMS_DW.SwitchCase_ActiveSubsystem_bn = 0;
          break;

         case MotionState_Brake:
          FMS_DW.SwitchCase_ActiveSubsystem_bn = 1;
          break;

         default:
          FMS_DW.SwitchCase_ActiveSubsystem_bn = 2;
          break;
        }

        switch (FMS_DW.SwitchCase_ActiveSubsystem_bn) {
         case 0:
          if (FMS_DW.SwitchCase_ActiveSubsystem_bn != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S208>/Hold Control' incorporates:
             *  ActionPort: '<S211>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S208>/Switch Case' */
            FMS_HoldControl_i_Reset(&FMS_DW.HoldControl_kq);

            /* End of SystemReset for SubSystem: '<S208>/Hold Control' */
          }

          /* Outputs for IfAction SubSystem: '<S208>/Hold Control' incorporates:
           *  ActionPort: '<S211>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_HoldControl_k(FMS_U.INS_Out.psi, &FMS_B.Merge_n,
                            &FMS_DW.HoldControl_kq);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S208>/Hold Control' */
          break;

         case 1:
          /* Outputs for IfAction SubSystem: '<S208>/Brake Control' incorporates:
           *  ActionPort: '<S210>/Action Port'
           */
          FMS_BrakeControl(&FMS_B.Merge_n);

          /* End of Outputs for SubSystem: '<S208>/Brake Control' */
          break;

         default:
          if (FMS_DW.SwitchCase_ActiveSubsystem_bn != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S208>/Move Control' incorporates:
             *  ActionPort: '<S212>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S208>/Switch Case' */
            FMS_MoveControl_c_Reset(&FMS_DW.MoveControl_b);

            /* End of SystemReset for SubSystem: '<S208>/Move Control' */
          }

          /* Outputs for IfAction SubSystem: '<S208>/Move Control' incorporates:
           *  ActionPort: '<S212>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_MoveControl_o(FMS_U.Pilot_Cmd.stick_yaw, &FMS_B.Merge_n,
                            &FMS_ConstB.MoveControl_b, &FMS_DW.MoveControl_b);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S208>/Move Control' */
          break;
        }

        /* End of Outputs for SubSystem: '<S33>/Stabilize' */
        memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

        /* Outputs for IfAction SubSystem: '<S33>/Stabilize' incorporates:
         *  ActionPort: '<S40>/Action Port'
         */
        /* BusAssignment: '<S40>/Bus Assignment' incorporates:
         *  BusAssignment: '<S34>/Bus Assignment'
         *  Outport: '<Root>/FMS_Out'
         */
        FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_g;
        FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_i;
        FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_j;

        /* Saturate: '<S208>/Saturation' */
        if (FMS_B.Merge_n > FMS_PARAM.YAW_RATE_LIM) {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
        } else if (FMS_B.Merge_n < -FMS_PARAM.YAW_RATE_LIM) {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
        } else {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.psi_rate_cmd = FMS_B.Merge_n;
        }

        /* End of Saturate: '<S208>/Saturation' */

        /* Saturate: '<S220>/Saturation1' incorporates:
         *  Merge: '<S220>/Merge'
         */
        if (FMS_B.Merge_o[0] > FMS_PARAM.VEL_XY_LIM) {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.u_cmd = FMS_PARAM.VEL_XY_LIM;
        } else if (FMS_B.Merge_o[0] < -FMS_PARAM.VEL_XY_LIM) {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.u_cmd = -FMS_PARAM.VEL_XY_LIM;
        } else {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.u_cmd = FMS_B.Merge_o[0];
        }

        if (FMS_B.Merge_o[1] > FMS_PARAM.VEL_XY_LIM) {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.v_cmd = FMS_PARAM.VEL_XY_LIM;
        } else if (FMS_B.Merge_o[1] < -FMS_PARAM.VEL_XY_LIM) {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.v_cmd = -FMS_PARAM.VEL_XY_LIM;
        } else {
          /* BusAssignment: '<S40>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.v_cmd = FMS_B.Merge_o[1];
        }

        /* End of Saturate: '<S220>/Saturation1' */
        /* End of Outputs for SubSystem: '<S33>/Stabilize' */
        break;

       case 3:
        {
          boolean_T rtb_Compare_n;
          if (FMS_DW.SwitchCase_ActiveSubsystem_b != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S33>/Position' incorporates:
             *  ActionPort: '<S39>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S33>/Switch Case' incorporates:
             *  Chart: '<S179>/Motion State'
             *  Chart: '<S192>/Motion State'
             */
            FMS_DW.temporalCounter_i1_h = 0U;
            FMS_DW.is_active_c16_FMS = 0U;
            FMS_DW.is_c16_FMS = FMS_IN_NO_ACTIVE_CHILD_d;
            FMS_DW.temporalCounter_i1_b = 0U;
            FMS_DW.is_active_c21_FMS = 0U;
            FMS_DW.is_c21_FMS = FMS_IN_NO_ACTIVE_CHILD_d;

            /* End of SystemReset for SubSystem: '<S33>/Position' */
          }

          /* Outputs for IfAction SubSystem: '<S33>/Position' incorporates:
           *  ActionPort: '<S39>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Logic: '<S192>/Logical Operator' incorporates:
           *  Abs: '<S192>/Abs1'
           *  Abs: '<S192>/Abs2'
           *  Constant: '<S203>/Constant'
           *  Constant: '<S204>/Constant'
           *  Inport: '<Root>/Pilot_Cmd'
           *  RelationalOperator: '<S203>/Compare'
           *  RelationalOperator: '<S204>/Compare'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtb_Compare_n = ((fabsf(FMS_U.Pilot_Cmd.stick_pitch) >
                            FMS_PARAM.PITCH_DZ) || (fabsf
            (FMS_U.Pilot_Cmd.stick_roll) > FMS_PARAM.ROLL_DZ));

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Chart: '<S192>/Motion State' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S192>/Square'
           *  Math: '<S192>/Square1'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sqrt: '<S192>/Sqrt'
           *  Sum: '<S192>/Add'
           */
          if (FMS_DW.temporalCounter_i1_h < 1023U) {
            FMS_DW.temporalCounter_i1_h++;
          }

          if (FMS_DW.is_active_c16_FMS == 0U) {
            FMS_DW.is_active_c16_FMS = 1U;
            FMS_DW.is_c16_FMS = FMS_IN_Move_g;
            rtb_state_ee = MotionState_Move;
          } else {
            switch (FMS_DW.is_c16_FMS) {
             case FMS_IN_Brake_b:
              rtb_state_ee = MotionState_Brake;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              if ((sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn + FMS_U.INS_Out.ve *
                         FMS_U.INS_Out.ve) <= 0.2) ||
                  (FMS_DW.temporalCounter_i1_h >= 625U)) {
                FMS_DW.is_c16_FMS = FMS_IN_Hold_g;
                rtb_state_ee = MotionState_Hold;
              } else if (rtb_Compare_n) {
                FMS_DW.is_c16_FMS = FMS_IN_Move_g;
                rtb_state_ee = MotionState_Move;
              }

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              break;

             case FMS_IN_Hold_g:
              rtb_state_ee = MotionState_Hold;
              if (rtb_Compare_n) {
                FMS_DW.is_c16_FMS = FMS_IN_Move_g;
                rtb_state_ee = MotionState_Move;
              }
              break;

             default:
              /* case IN_Move: */
              rtb_state_ee = MotionState_Move;
              if (!rtb_Compare_n) {
                FMS_DW.is_c16_FMS = FMS_IN_Brake_b;
                FMS_DW.temporalCounter_i1_h = 0U;
                rtb_state_ee = MotionState_Brake;
              }
              break;
            }
          }

          /* End of Chart: '<S192>/Motion State' */

          /* SwitchCase: '<S191>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_l;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_l = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_l = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_l = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_l) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_l != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S191>/Hold Control' incorporates:
               *  ActionPort: '<S194>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S191>/Switch Case' */
              FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_a);

              /* End of SystemReset for SubSystem: '<S191>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S191>/Hold Control' incorporates:
             *  ActionPort: '<S194>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                              FMS_U.INS_Out.psi, FMS_B.Merge,
                              &FMS_ConstB.HoldControl_a, &FMS_DW.HoldControl_a);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S191>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S191>/Brake Control' incorporates:
             *  ActionPort: '<S193>/Action Port'
             */
            FMS_BrakeControl_h(FMS_B.Merge);

            /* End of Outputs for SubSystem: '<S191>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_l != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S191>/Move Control' incorporates:
               *  ActionPort: '<S195>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S191>/Switch Case' */
              FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_k);

              /* End of SystemReset for SubSystem: '<S191>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S191>/Move Control' incorporates:
             *  ActionPort: '<S195>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                              FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge,
                              &FMS_ConstB.MoveControl_k, &FMS_DW.MoveControl_k);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S191>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* RelationalOperator: '<S189>/Compare' incorporates:
           *  Abs: '<S179>/Abs1'
           *  Constant: '<S189>/Constant'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtb_Compare_n = (fabsf(FMS_U.Pilot_Cmd.stick_yaw) > FMS_PARAM.YAW_DZ);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Chart: '<S179>/Motion State' incorporates:
           *  Abs: '<S179>/Abs'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.temporalCounter_i1_b < 255U) {
            FMS_DW.temporalCounter_i1_b++;
          }

          if (FMS_DW.is_active_c21_FMS == 0U) {
            FMS_DW.is_active_c21_FMS = 1U;
            FMS_DW.is_c21_FMS = FMS_IN_Move_g;
            rtb_state_ee = MotionState_Move;
          } else {
            switch (FMS_DW.is_c21_FMS) {
             case FMS_IN_Brake_b:
              rtb_state_ee = MotionState_Brake;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              if ((fabsf(FMS_U.INS_Out.r) <= 0.1) ||
                  (FMS_DW.temporalCounter_i1_b >= 250U)) {
                FMS_DW.is_c21_FMS = FMS_IN_Hold_g;
                rtb_state_ee = MotionState_Hold;
              } else if (rtb_Compare_n) {
                FMS_DW.is_c21_FMS = FMS_IN_Move_g;
                rtb_state_ee = MotionState_Move;
              }

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              break;

             case FMS_IN_Hold_g:
              rtb_state_ee = MotionState_Hold;
              if (rtb_Compare_n) {
                FMS_DW.is_c21_FMS = FMS_IN_Move_g;
                rtb_state_ee = MotionState_Move;
              }
              break;

             default:
              /* case IN_Move: */
              rtb_state_ee = MotionState_Move;
              if (!rtb_Compare_n) {
                FMS_DW.is_c21_FMS = FMS_IN_Brake_b;
                FMS_DW.temporalCounter_i1_b = 0U;
                rtb_state_ee = MotionState_Brake;
              }
              break;
            }
          }

          /* End of Chart: '<S179>/Motion State' */

          /* SwitchCase: '<S178>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_j;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_j = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_j = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_j = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_j) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_j != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S178>/Hold Control' incorporates:
               *  ActionPort: '<S181>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S178>/Switch Case' */
              FMS_HoldControl_i_Reset(&FMS_DW.HoldControl_e);

              /* End of SystemReset for SubSystem: '<S178>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S178>/Hold Control' incorporates:
             *  ActionPort: '<S181>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_k(FMS_U.INS_Out.psi, &FMS_B.Merge_d,
                              &FMS_DW.HoldControl_e);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S178>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S178>/Brake Control' incorporates:
             *  ActionPort: '<S180>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_d);

            /* End of Outputs for SubSystem: '<S178>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_j != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S178>/Move Control' incorporates:
               *  ActionPort: '<S182>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S178>/Switch Case' */
              FMS_MoveControl_c_Reset(&FMS_DW.MoveControl_m);

              /* End of SystemReset for SubSystem: '<S178>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S178>/Move Control' incorporates:
             *  ActionPort: '<S182>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_o(FMS_U.Pilot_Cmd.stick_yaw, &FMS_B.Merge_d,
                              &FMS_ConstB.MoveControl_m, &FMS_DW.MoveControl_m);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S178>/Move Control' */
            break;
          }

          /* End of Outputs for SubSystem: '<S33>/Position' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S33>/Position' incorporates:
           *  ActionPort: '<S39>/Action Port'
           */
          /* BusAssignment: '<S39>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_b;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_o;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2;

          /* Saturate: '<S178>/Saturation' */
          if (FMS_B.Merge_d > FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
          } else if (FMS_B.Merge_d < -FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
          } else {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_B.Merge_d;
          }

          /* End of Saturate: '<S178>/Saturation' */

          /* Saturate: '<S191>/Saturation1' incorporates:
           *  Merge: '<S191>/Merge'
           */
          if (FMS_B.Merge[0] > FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = FMS_PARAM.VEL_XY_LIM;
          } else if (FMS_B.Merge[0] < -FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = -FMS_PARAM.VEL_XY_LIM;
          } else {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = FMS_B.Merge[0];
          }

          if (FMS_B.Merge[1] > FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = FMS_PARAM.VEL_XY_LIM;
          } else if (FMS_B.Merge[1] < -FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = -FMS_PARAM.VEL_XY_LIM;
          } else {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = FMS_B.Merge[1];
          }

          /* End of Saturate: '<S191>/Saturation1' */

          /* BusAssignment: '<S39>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.w_cmd = 0.0F;

          /* End of Outputs for SubSystem: '<S33>/Position' */
        }
        break;

       case 4:
        memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

        /* Outputs for IfAction SubSystem: '<S33>/Manual' incorporates:
         *  ActionPort: '<S38>/Action Port'
         */
        /* BusAssignment: '<S38>/Bus Assignment' incorporates:
         *  BusAssignment: '<S34>/Bus Assignment'
         *  Constant: '<S38>/Constant2'
         *  Outport: '<Root>/FMS_Out'
         */
        FMS_Y.FMS_Out.reset = 1U;
        FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion;
        FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1;

        /* End of Outputs for SubSystem: '<S33>/Manual' */
        break;

       default:
        /* Outputs for IfAction SubSystem: '<S33>/Unknown' incorporates:
         *  ActionPort: '<S42>/Action Port'
         */
        /* Outport: '<Root>/FMS_Out' incorporates:
         *  BusAssignment: '<S34>/Bus Assignment'
         */
        FMS_Disarm(&FMS_Y.FMS_Out, &FMS_ConstB.Unknown);

        /* End of Outputs for SubSystem: '<S33>/Unknown' */
        break;
      }

      /* End of Outputs for SubSystem: '<S31>/Arm' */
    }
    break;
  }

  /* End of SwitchCase: '<S31>/Switch Case' */

  /* BusAssignment: '<S34>/Bus Assignment' incorporates:
   *  Constant: '<S34>/Constant'
   *  DataTypeConversion: '<S34>/Data Type Conversion'
   *  DiscreteIntegrator: '<S364>/Discrete-Time Integrator'
   *  Outport: '<Root>/FMS_Out'
   *  SignalConversion generated from: '<S32>/Signal Copy4'
   *  SignalConversion generated from: '<S32>/Signal Copy5'
   *  Sum: '<S34>/Sum'
   */
  FMS_Y.FMS_Out.timestamp = FMS_DW.DiscreteTimeIntegrator_DSTATE_g;
  FMS_Y.FMS_Out.mode = (uint8_T)FMS_B.target_mode;

  /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
  FMS_Y.FMS_Out.wp_consume = FMS_B.wp_consume;
  FMS_Y.FMS_Out.wp_current = (uint8_T)(FMS_B.wp_index - 1);

  /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

  /* Update for DiscreteIntegrator: '<S364>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S364>/Constant'
   */
  FMS_DW.DiscreteTimeIntegrator_DSTATE_g += FMS_EXPORT.period;

  /* End of Outputs for SubSystem: '<Root>/FMS Commander' */

  /* Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S12>/Gain'
   *  Sum: '<S12>/Sum5'
   */
  FMS_DW.DiscreteTimeIntegrator5_IC_LOAD = 0U;
  FMS_DW.DiscreteTimeIntegrator5_DSTATE[0] += (rtb_Multiply[0] -
    FMS_DW.DiscreteTimeIntegrator5_DSTATE[0]) * 2.0F * 0.004F;
  FMS_DW.DiscreteTimeIntegrator5_DSTATE[1] += (rtb_Multiply[1] -
    FMS_DW.DiscreteTimeIntegrator5_DSTATE[1]) * 2.0F * 0.004F;
  FMS_DW.DiscreteTimeIntegrator5_DSTATE[2] += (rtb_Multiply[2] -
    FMS_DW.DiscreteTimeIntegrator5_DSTATE[2]) * 2.0F * 0.004F;

  /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S13>/Gain'
   *  Sum: '<S13>/Sum5'
   */
  FMS_DW.DiscreteTimeIntegrator5_IC_LO_g = 0U;
  FMS_DW.DiscreteTimeIntegrator5_DSTAT_j += ((real32_T)rtb_SquareRoot -
    FMS_DW.DiscreteTimeIntegrator5_DSTAT_j) * 10.0F * 0.004F;

  /* Update for UnitDelay: '<S25>/Delay Input1' incorporates:
   *  Inport: '<Root>/Pilot_Cmd'
   *
   * Block description for '<S25>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FMS_DW.DelayInput1_DSTATE = FMS_U.Pilot_Cmd.timestamp;

  /* Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S21>/Constant1'
   */
  if (FMS_EXPORT.period < 4.2949673E+9F) {
    qY = (uint32_T)(real32_T)FMS_EXPORT.period;
  } else {
    qY = MAX_uint32_T;
  }

  qY += /*MW:OvSatOk*/ FMS_DW.DiscreteTimeIntegrator1_DSTATE;
  if (qY < FMS_DW.DiscreteTimeIntegrator1_DSTATE) {
    qY = MAX_uint32_T;
  }

  FMS_DW.DiscreteTimeIntegrator1_DSTATE = qY;

  /* End of Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator1' */

  /* Update for UnitDelay: '<S30>/Delay Input1' incorporates:
   *  Inport: '<Root>/GCS_Cmd'
   *
   * Block description for '<S30>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FMS_DW.DelayInput1_DSTATE_f = FMS_U.GCS_Cmd.mode;

  /* Update for UnitDelay: '<S26>/Delay Input1' incorporates:
   *  Inport: '<Root>/Pilot_Cmd'
   *
   * Block description for '<S26>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FMS_DW.DelayInput1_DSTATE_i = FMS_U.Pilot_Cmd.cmd_1;

  /* Update for UnitDelay: '<S27>/Delay Input1' incorporates:
   *  Inport: '<Root>/GCS_Cmd'
   *
   * Block description for '<S27>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FMS_DW.DelayInput1_DSTATE_p = FMS_U.GCS_Cmd.cmd_1;

  /* Update for UnitDelay: '<S8>/Delay Input1' incorporates:
   *  Inport: '<Root>/Auto_Cmd'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FMS_DW.DelayInput1_DSTATE_c = FMS_U.Auto_Cmd.timestamp;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S1>/Constant'
   */
  if (FMS_EXPORT.period < 4.2949673E+9F) {
    qY = (uint32_T)(real32_T)FMS_EXPORT.period;
  } else {
    qY = MAX_uint32_T;
  }

  qY += /*MW:OvSatOk*/ FMS_DW.DiscreteTimeIntegrator_DSTATE;
  if (qY < FMS_DW.DiscreteTimeIntegrator_DSTATE) {
    qY = MAX_uint32_T;
  }

  FMS_DW.DiscreteTimeIntegrator_DSTATE = qY;

  /* End of Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
}

/* Model initialize function */
void FMS_init(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(FMS_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &FMS_B), 0,
                sizeof(B_FMS_T));

  {
    FMS_B.state = VehicleState_None;
    FMS_B.target_mode = PilotMode_None;
  }

  /* states (dwork) */
  (void) memset((void *)&FMS_DW, 0,
                sizeof(DW_FMS_T));

  /* external inputs */
  (void)memset(&FMS_U, 0, sizeof(ExtU_FMS_T));

  /* external outputs */
  FMS_Y.FMS_Out = FMS_rtZFMS_Out_Bus;

  {
    MotionState rtb_state_l;
    FMS_PrevZCX.Mission_SubSystem_Reset_ZCE = POS_ZCSIG;

    /* InitializeConditions for DiscreteIntegrator: '<S12>/Discrete-Time Integrator5' */
    FMS_DW.DiscreteTimeIntegrator5_IC_LOAD = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator5' */
    FMS_DW.DiscreteTimeIntegrator5_IC_LO_g = 1U;

    /* SystemInitialize for Chart: '<Root>/SafeMode' */
    FMS_DW.is_active_c3_FMS = 0U;
    FMS_DW.is_c3_FMS = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_B.target_mode = PilotMode_None;

    /* SystemInitialize for Chart: '<Root>/State Machine' */
    initialize_msg_local_queues_for();
    FMS_DW.is_active_Combo_Stick = 0U;
    FMS_DW.is_Combo_Stick = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_active_Command_Listener = 0U;
    FMS_DW.is_Command_Listener = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_active_Vehicle = 0U;
    FMS_DW.is_Vehicle = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_Mission = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.is_Offboard = FMS_IN_NO_ACTIVE_CHILD_d;
    FMS_DW.temporalCounter_i1 = 0U;
    FMS_DW.is_active_c11_FMS = 0U;
    FMS_DW.valid_cmd = false;
    FMS_DW.M_msgReservedData = FMS_Cmd_None;
    FMS_DW.home[0] = 0.0F;
    FMS_DW.home[1] = 0.0F;
    FMS_DW.home[2] = 0.0F;
    FMS_DW.bl = false;
    FMS_DW.br = false;
    FMS_DW.nav_cmd = 0U;
    FMS_DW.llo[0] = 0.0;
    FMS_DW.llo[1] = 0.0;
    FMS_DW.save_cmd = FMS_Cmd_None;
    FMS_B.state = VehicleState_None;
    FMS_B.wp_consume = 0U;
    FMS_B.wp_index = 1U;
    FMS_B.Cmd_In.sp_waypoint[0] = 0.0F;
    FMS_B.Cmd_In.cur_waypoint[0] = 0.0F;
    FMS_B.Cmd_In.sp_waypoint[1] = 0.0F;
    FMS_B.Cmd_In.cur_waypoint[1] = 0.0F;
    FMS_B.Cmd_In.sp_waypoint[2] = 0.0F;
    FMS_B.Cmd_In.cur_waypoint[2] = 0.0F;
    FMS_B.Cmd_In.offboard_psi_0 = 0.0F;
    FMS_DW.cmd_start = FMS_Cmd_None;
    FMS_DW.mode_start = PilotMode_None;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FMS Commander' */
    /* Start for SwitchCase: '<S31>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem = -1;

    /* SystemInitialize for IfAction SubSystem: '<S31>/Arm' */
    /* Start for SwitchCase: '<S33>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_b = -1;

    /* SystemInitialize for IfAction SubSystem: '<S33>/SubMode' */
    /* Start for SwitchCase: '<S41>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_o = -1;

    /* SystemInitialize for IfAction SubSystem: '<S41>/Return' */
    /* Start for SwitchCase: '<S317>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

    /* Start for SwitchCase: '<S307>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;

    /* InitializeConditions for Delay: '<S303>/Delay' */
    FMS_DW.icLoad_h = true;

    /* InitializeConditions for DiscreteIntegrator: '<S344>/Discrete-Time Integrator' */
    FMS_DW.l1_heading_a = 0.0F;

    /* InitializeConditions for Delay: '<S283>/Delay' */
    FMS_DW.icLoad_j = true;

    /* InitializeConditions for Delay: '<S284>/Delay' */
    FMS_DW.icLoad_c = true;

    /* InitializeConditions for DiscreteIntegrator: '<S287>/Integrator1' */
    FMS_DW.Integrator1_IC_LOADING = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S287>/Integrator' */
    FMS_DW.Integrator_DSTATE = 0.0F;

    /* SystemInitialize for Chart: '<S318>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState);

    /* SystemInitialize for IfAction SubSystem: '<S317>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_g);

    /* End of SystemInitialize for SubSystem: '<S317>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S317>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_c);

    /* End of SystemInitialize for SubSystem: '<S317>/Move Control' */

    /* SystemInitialize for Merge: '<S317>/Merge' */
    FMS_B.Merge_f[0] = 0.0F;
    FMS_B.Merge_f[1] = 0.0F;

    /* SystemInitialize for Chart: '<S308>/Motion Status' */
    FMS_MotionStatus_Init(&rtb_state_l, &FMS_DW.sf_MotionStatus);

    /* SystemInitialize for IfAction SubSystem: '<S307>/Hold Control' */
    FMS_HoldControl_Init(&FMS_DW.HoldControl);

    /* End of SystemInitialize for SubSystem: '<S307>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S307>/Move Control' */
    FMS_MoveControl_Init(&FMS_DW.MoveControl);

    /* End of SystemInitialize for SubSystem: '<S307>/Move Control' */

    /* SystemInitialize for Merge: '<S307>/Merge' */
    FMS_B.Merge_pd = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S41>/Return' */

    /* SystemInitialize for IfAction SubSystem: '<S41>/Hold' */
    /* Start for SwitchCase: '<S263>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

    /* Start for SwitchCase: '<S241>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

    /* Start for SwitchCase: '<S251>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;

    /* SystemInitialize for Chart: '<S264>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState_l);

    /* SystemInitialize for IfAction SubSystem: '<S263>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_h);

    /* End of SystemInitialize for SubSystem: '<S263>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S263>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_h);

    /* End of SystemInitialize for SubSystem: '<S263>/Move Control' */

    /* SystemInitialize for Merge: '<S263>/Merge' */
    FMS_B.Merge_m[0] = 0.0F;
    FMS_B.Merge_m[1] = 0.0F;

    /* SystemInitialize for Chart: '<S242>/Motion Status' */
    FMS_MotionStatus_Init(&rtb_state_l, &FMS_DW.sf_MotionStatus_d);

    /* SystemInitialize for IfAction SubSystem: '<S241>/Hold Control' */
    FMS_HoldControl_Init(&FMS_DW.HoldControl_b);

    /* End of SystemInitialize for SubSystem: '<S241>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S241>/Move Control' */
    FMS_MoveControl_Init(&FMS_DW.MoveControl_g);

    /* End of SystemInitialize for SubSystem: '<S241>/Move Control' */

    /* SystemInitialize for Merge: '<S241>/Merge' */
    FMS_B.Merge_ob = 0.0F;

    /* SystemInitialize for Chart: '<S252>/Motion State' */
    FMS_MotionState_b_Init(&rtb_state_l, &FMS_DW.sf_MotionState_i);

    /* SystemInitialize for IfAction SubSystem: '<S251>/Hold Control' */
    FMS_HoldControl_i_Init(&FMS_DW.HoldControl_k);

    /* End of SystemInitialize for SubSystem: '<S251>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S251>/Move Control' */
    FMS_MoveControl_m_Init(&FMS_DW.MoveControl_o);

    /* End of SystemInitialize for SubSystem: '<S251>/Move Control' */

    /* SystemInitialize for Merge: '<S251>/Merge' */
    FMS_B.Merge_p = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S41>/Hold' */
    /* End of SystemInitialize for SubSystem: '<S33>/SubMode' */

    /* SystemInitialize for IfAction SubSystem: '<S33>/Auto' */
    /* Start for SwitchCase: '<S37>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_i = -1;

    /* SystemInitialize for IfAction SubSystem: '<S37>/Mission' */
    /* InitializeConditions for UnitDelay: '<S46>/Delay Input1'
     *
     * Block description for '<S46>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FMS_DW.DelayInput1_DSTATE_pe = 0U;

    /* SystemInitialize for Resettable SubSystem: '<S43>/Mission_SubSystem' */
    /* InitializeConditions for Delay: '<S64>/Delay' */
    FMS_DW.icLoad = true;

    /* InitializeConditions for DiscreteIntegrator: '<S83>/Discrete-Time Integrator' */
    FMS_DW.l1_heading = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S43>/Mission_SubSystem' */
    /* End of SystemInitialize for SubSystem: '<S37>/Mission' */
    /* End of SystemInitialize for SubSystem: '<S33>/Auto' */

    /* SystemInitialize for IfAction SubSystem: '<S33>/Stabilize' */
    /* Start for SwitchCase: '<S220>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_p = -1;

    /* Start for SwitchCase: '<S208>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_bn = -1;

    /* SystemInitialize for Chart: '<S221>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState_g);

    /* SystemInitialize for IfAction SubSystem: '<S220>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_f);

    /* End of SystemInitialize for SubSystem: '<S220>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S220>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_i);

    /* End of SystemInitialize for SubSystem: '<S220>/Move Control' */

    /* SystemInitialize for Merge: '<S220>/Merge' */
    FMS_B.Merge_o[0] = 0.0F;
    FMS_B.Merge_o[1] = 0.0F;

    /* SystemInitialize for Chart: '<S209>/Motion State' */
    FMS_MotionState_b_Init(&rtb_state_l, &FMS_DW.sf_MotionState_d);

    /* SystemInitialize for IfAction SubSystem: '<S208>/Hold Control' */
    FMS_HoldControl_i_Init(&FMS_DW.HoldControl_kq);

    /* End of SystemInitialize for SubSystem: '<S208>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S208>/Move Control' */
    FMS_MoveControl_m_Init(&FMS_DW.MoveControl_b);

    /* End of SystemInitialize for SubSystem: '<S208>/Move Control' */

    /* SystemInitialize for Merge: '<S208>/Merge' */
    FMS_B.Merge_n = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S33>/Stabilize' */

    /* SystemInitialize for IfAction SubSystem: '<S33>/Position' */
    /* Start for SwitchCase: '<S191>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_l = -1;

    /* Start for SwitchCase: '<S178>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_j = -1;

    /* SystemInitialize for Chart: '<S192>/Motion State' */
    FMS_DW.temporalCounter_i1_h = 0U;
    FMS_DW.is_active_c16_FMS = 0U;
    FMS_DW.is_c16_FMS = FMS_IN_NO_ACTIVE_CHILD_d;

    /* SystemInitialize for IfAction SubSystem: '<S191>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_a);

    /* End of SystemInitialize for SubSystem: '<S191>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S191>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_k);

    /* End of SystemInitialize for SubSystem: '<S191>/Move Control' */

    /* SystemInitialize for Merge: '<S191>/Merge' */
    FMS_B.Merge[0] = 0.0F;
    FMS_B.Merge[1] = 0.0F;

    /* SystemInitialize for Chart: '<S179>/Motion State' */
    FMS_DW.temporalCounter_i1_b = 0U;
    FMS_DW.is_active_c21_FMS = 0U;
    FMS_DW.is_c21_FMS = FMS_IN_NO_ACTIVE_CHILD_d;

    /* SystemInitialize for IfAction SubSystem: '<S178>/Hold Control' */
    FMS_HoldControl_i_Init(&FMS_DW.HoldControl_e);

    /* End of SystemInitialize for SubSystem: '<S178>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S178>/Move Control' */
    FMS_MoveControl_m_Init(&FMS_DW.MoveControl_m);

    /* End of SystemInitialize for SubSystem: '<S178>/Move Control' */

    /* SystemInitialize for Merge: '<S178>/Merge' */
    FMS_B.Merge_d = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S33>/Position' */
    /* End of SystemInitialize for SubSystem: '<S31>/Arm' */
    /* End of SystemInitialize for SubSystem: '<Root>/FMS Commander' */
  }
}

/* Model terminate function */
void FMS_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
