/*
 * File: FMS.c
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

/* Named constants for Chart: '<S352>/Motion Status' */
#define FMS_IN_Brake                   ((uint8_T)1U)
#define FMS_IN_Hold                    ((uint8_T)2U)
#define FMS_IN_Move                    ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)

/* Named constants for Chart: '<S362>/Motion State' */
#define FMS_IN_Brake_k                 ((uint8_T)1U)
#define FMS_IN_Hold_e                  ((uint8_T)2U)
#define FMS_IN_Move_h                  ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD_j       ((uint8_T)0U)

/* Named constants for Chart: '<S296>/Motion State' */
#define FMS_IN_Brake_l                 ((uint8_T)1U)
#define FMS_IN_Hold_i                  ((uint8_T)2U)
#define FMS_IN_Move_f                  ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD_m       ((uint8_T)0U)

/* Named constants for Chart: '<S212>/Motion Status' */
#define FMS_IN_Brake_o                 ((uint8_T)1U)
#define FMS_IN_Hold_iv                 ((uint8_T)2U)
#define FMS_IN_Move_hn                 ((uint8_T)3U)
#define FMS_IN_NO_ACTIVE_CHILD_mn      ((uint8_T)0U)

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

struct_TYt7YeNdxIDXfczXumtXXB FMS_EXPORT = {
  4U,

  { 66, 97, 115, 101, 32, 70, 77, 83, 32, 118, 48, 46, 52, 46, 48, 0 }
} ;                                    /* Variable: FMS_EXPORT
                                        * Referenced by:
                                        *   '<S1>/Constant'
                                        *   '<S21>/Constant1'
                                        *   '<S397>/Constant'
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
static real32_T FMS_norm(const real32_T x[2]);
static void FMS_exit_internal_Auto(void);
static void FMS_Auto(void);
static void FMS_enter_internal_Arm(void);
static void FMS_Arm(void);
static void FMS_Vehicle(void);
static void FMS_c11_FMS(void);
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
 *    '<S37>/Unknown'
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
  rty_FMS_Out->actuator_cmd[0] = 0U;
  rty_FMS_Out->actuator_cmd[1] = 0U;
  rty_FMS_Out->actuator_cmd[2] = 0U;
  rty_FMS_Out->actuator_cmd[3] = 0U;
  for (i = 0; i < 12; i++) {
    rty_FMS_Out->actuator_cmd[i + 4] = 0U;
  }

  /* End of BusAssignment: '<S35>/Bus Assignment' */
}

/*
 * System initialize for action system:
 *    '<S351>/Hold Control'
 *    '<S285>/Hold Control'
 *    '<S78>/Hold Control'
 *    '<S211>/Hold Control'
 */
void FMS_HoldControl_Init(DW_HoldControl_FMS_T *localDW)
{
  /* InitializeConditions for Delay: '<S354>/Delay' */
  localDW->icLoad = true;
}

/*
 * System reset for action system:
 *    '<S351>/Hold Control'
 *    '<S285>/Hold Control'
 *    '<S78>/Hold Control'
 *    '<S211>/Hold Control'
 */
void FMS_HoldControl_Reset(DW_HoldControl_FMS_T *localDW)
{
  /* InitializeConditions for Delay: '<S354>/Delay' */
  localDW->icLoad = true;
}

/*
 * Output and update for action system:
 *    '<S351>/Hold Control'
 *    '<S285>/Hold Control'
 *    '<S78>/Hold Control'
 *    '<S211>/Hold Control'
 */
void FMS_HoldControl(real32_T rtu_FMS_In, real32_T *rty_w_cmd_mPs,
                     DW_HoldControl_FMS_T *localDW)
{
  /* Delay: '<S354>/Delay' incorporates:
   *  Gain: '<S356>/Gain'
   */
  if (localDW->icLoad) {
    localDW->Delay_DSTATE = -rtu_FMS_In;
  }

  /* Gain: '<S354>/Gain2' incorporates:
   *  Delay: '<S354>/Delay'
   *  Gain: '<S356>/Gain'
   *  Sum: '<S354>/Sum'
   */
  *rty_w_cmd_mPs = (localDW->Delay_DSTATE - (-rtu_FMS_In)) * FMS_PARAM.Z_P;

  /* Update for Delay: '<S354>/Delay' */
  localDW->icLoad = false;
}

/*
 * Output and update for action system:
 *    '<S351>/Brake Control'
 *    '<S285>/Brake Control'
 *    '<S295>/Brake Control'
 *    '<S78>/Brake Control'
 *    '<S252>/Brake Control'
 *    '<S211>/Brake Control'
 *    '<S222>/Brake Control'
 */
void FMS_BrakeControl(real32_T *rty_psi_rate_cmd_radPs)
{
  /* SignalConversion generated from: '<S353>/psi_rate_cmd_radPs' incorporates:
   *  Constant: '<S353>/Brake Speed'
   */
  *rty_psi_rate_cmd_radPs = 0.0F;
}

/*
 * System initialize for action system:
 *    '<S351>/Move Control'
 *    '<S285>/Move Control'
 *    '<S78>/Move Control'
 *    '<S211>/Move Control'
 */
void FMS_MoveControl_Init(DW_MoveControl_FMS_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S358>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S358>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * System reset for action system:
 *    '<S351>/Move Control'
 *    '<S285>/Move Control'
 *    '<S78>/Move Control'
 *    '<S211>/Move Control'
 */
void FMS_MoveControl_Reset(DW_MoveControl_FMS_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S358>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S358>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S351>/Move Control'
 *    '<S285>/Move Control'
 *    '<S78>/Move Control'
 *    '<S211>/Move Control'
 */
void FMS_MoveControl(real32_T rtu_FMS_In, real32_T *rty_w_cmd_mPs, const
                     ConstB_MoveControl_FMS_T *localC, DW_MoveControl_FMS_T
                     *localDW)
{
  real32_T rtb_Add3_e;
  real32_T rtb_Subtract3_m;
  real32_T rtb_a_ot;
  real32_T u;
  real32_T u_0;

  /* Product: '<S359>/Multiply1' incorporates:
   *  Constant: '<S359>/const1'
   *  DiscreteIntegrator: '<S358>/Integrator'
   */
  rtb_Add3_e = localDW->Integrator_DSTATE * 0.05F;

  /* DeadZone: '<S357>/Dead Zone' */
  if (rtu_FMS_In > FMS_PARAM.THROTTLE_DZ) {
    u = rtu_FMS_In - FMS_PARAM.THROTTLE_DZ;
  } else if (rtu_FMS_In >= -FMS_PARAM.THROTTLE_DZ) {
    u = 0.0F;
  } else {
    u = rtu_FMS_In - (-FMS_PARAM.THROTTLE_DZ);
  }

  /* Sum: '<S359>/Add' incorporates:
   *  DeadZone: '<S357>/Dead Zone'
   *  DiscreteIntegrator: '<S358>/Integrator1'
   *  Gain: '<S355>/Gain1'
   *  Gain: '<S357>/Gain'
   *  Sum: '<S358>/Subtract'
   */
  rtb_Subtract3_m = (localDW->Integrator1_DSTATE - 1.0F / (1.0F -
    FMS_PARAM.THROTTLE_DZ) * u * -FMS_PARAM.VEL_Z_LIM) + rtb_Add3_e;

  /* Signum: '<S359>/Sign' */
  if (rtb_Subtract3_m < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(rtb_Subtract3_m > 0.0F);
  }

  /* Sum: '<S359>/Add2' incorporates:
   *  Abs: '<S359>/Abs'
   *  Gain: '<S359>/Gain'
   *  Gain: '<S359>/Gain1'
   *  Product: '<S359>/Multiply2'
   *  Product: '<S359>/Multiply3'
   *  Signum: '<S359>/Sign'
   *  Sqrt: '<S359>/Sqrt'
   *  Sum: '<S359>/Add1'
   *  Sum: '<S359>/Subtract'
   */
  rtb_a_ot = (sqrtf((8.0F * fabsf(rtb_Subtract3_m) + localC->d) * localC->d) -
              localC->d) * 0.5F * u + rtb_Add3_e;

  /* Sum: '<S359>/Add3' */
  u = rtb_Subtract3_m + localC->d;

  /* Sum: '<S359>/Subtract1' */
  u_0 = rtb_Subtract3_m - localC->d;

  /* Signum: '<S359>/Sign1' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S359>/Sign2' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Sum: '<S359>/Add5' incorporates:
   *  Gain: '<S359>/Gain2'
   *  Product: '<S359>/Multiply4'
   *  Signum: '<S359>/Sign1'
   *  Signum: '<S359>/Sign2'
   *  Sum: '<S359>/Add4'
   *  Sum: '<S359>/Subtract2'
   */
  rtb_a_ot += ((rtb_Subtract3_m - rtb_a_ot) + rtb_Add3_e) * ((u - u_0) * 0.5F);

  /* SignalConversion generated from: '<S355>/w_cmd_mPs' incorporates:
   *  DiscreteIntegrator: '<S358>/Integrator1'
   */
  *rty_w_cmd_mPs = localDW->Integrator1_DSTATE;

  /* Update for DiscreteIntegrator: '<S358>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S358>/Integrator'
   */
  localDW->Integrator1_DSTATE += 0.004F * localDW->Integrator_DSTATE;

  /* Signum: '<S359>/Sign5' */
  if (rtb_a_ot < 0.0F) {
    /* Signum: '<S359>/Sign6' */
    rtb_Add3_e = -1.0F;
  } else {
    /* Signum: '<S359>/Sign6' */
    rtb_Add3_e = (real32_T)(rtb_a_ot > 0.0F);
  }

  /* Sum: '<S359>/Add6' */
  u = rtb_a_ot + localC->d;

  /* Sum: '<S359>/Subtract3' */
  u_0 = rtb_a_ot - localC->d;

  /* Signum: '<S359>/Sign3' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S359>/Sign4' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S358>/Integrator' incorporates:
   *  Constant: '<S359>/const'
   *  Gain: '<S359>/Gain3'
   *  Product: '<S359>/Divide'
   *  Product: '<S359>/Multiply5'
   *  Product: '<S359>/Multiply6'
   *  Signum: '<S359>/Sign3'
   *  Signum: '<S359>/Sign4'
   *  Signum: '<S359>/Sign5'
   *  Sum: '<S359>/Subtract4'
   *  Sum: '<S359>/Subtract5'
   *  Sum: '<S359>/Subtract6'
   */
  localDW->Integrator_DSTATE += ((rtb_a_ot / localC->d - rtb_Add3_e) *
    localC->Gain4 * ((u - u_0) * 0.5F) - rtb_Add3_e * 78.448F) * 0.004F;
}

/*
 * System initialize for atomic system:
 *    '<S352>/Motion Status'
 *    '<S286>/Motion Status'
 *    '<S79>/Motion Status'
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
 *    '<S352>/Motion Status'
 *    '<S286>/Motion Status'
 *    '<S79>/Motion Status'
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
 *    '<S352>/Motion Status'
 *    '<S286>/Motion Status'
 *    '<S79>/Motion Status'
 */
void FMS_MotionStatus(real32_T rtu_motion_req, real32_T rtu_speed, MotionState
                      *rty_state, DW_MotionStatus_FMS_T *localDW)
{
  if (localDW->temporalCounter_i1 < 511U) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S352>/Motion Status' */
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

  /* End of Chart: '<S352>/Motion Status' */
}

/*
 * System initialize for action system:
 *    '<S361>/Hold Control'
 *    '<S307>/Hold Control'
 *    '<S88>/Hold Control'
 *    '<S264>/Hold Control'
 *    '<S235>/Hold Control'
 */
void FMS_HoldControl_l_Init(DW_HoldControl_FMS_f_T *localDW)
{
  /* InitializeConditions for Delay: '<S364>/Delay' */
  localDW->icLoad = true;
}

/*
 * System reset for action system:
 *    '<S361>/Hold Control'
 *    '<S307>/Hold Control'
 *    '<S88>/Hold Control'
 *    '<S264>/Hold Control'
 *    '<S235>/Hold Control'
 */
void FMS_HoldControl_a_Reset(DW_HoldControl_FMS_f_T *localDW)
{
  /* InitializeConditions for Delay: '<S364>/Delay' */
  localDW->icLoad = true;
}

/*
 * Output and update for action system:
 *    '<S361>/Hold Control'
 *    '<S307>/Hold Control'
 *    '<S88>/Hold Control'
 *    '<S264>/Hold Control'
 *    '<S235>/Hold Control'
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

  /* Delay: '<S364>/Delay' incorporates:
   *  SignalConversion generated from: '<S364>/Delay'
   */
  if (localDW->icLoad) {
    localDW->Delay_DSTATE[0] = rtu_FMS_In;
    localDW->Delay_DSTATE[1] = rtu_FMS_In_g;
  }

  /* Trigonometry: '<S368>/Trigonometric Function1' incorporates:
   *  Gain: '<S367>/Gain'
   *  Trigonometry: '<S368>/Trigonometric Function3'
   */
  rtb_VectorConcatenate_bl_tmp_0 = arm_cos_f32(-rtu_FMS_In_n);
  rtb_VectorConcatenate_o[0] = rtb_VectorConcatenate_bl_tmp_0;

  /* Trigonometry: '<S368>/Trigonometric Function' incorporates:
   *  Gain: '<S367>/Gain'
   *  Trigonometry: '<S368>/Trigonometric Function2'
   */
  rtb_VectorConcatenate_bl_tmp = arm_sin_f32(-rtu_FMS_In_n);
  rtb_VectorConcatenate_o[1] = rtb_VectorConcatenate_bl_tmp;

  /* SignalConversion generated from: '<S368>/Vector Concatenate1' incorporates:
   *  Constant: '<S368>/Constant3'
   */
  rtb_VectorConcatenate_o[2] = 0.0F;

  /* Gain: '<S368>/Gain' */
  rtb_VectorConcatenate_o[3] = -rtb_VectorConcatenate_bl_tmp;

  /* Trigonometry: '<S368>/Trigonometric Function3' */
  rtb_VectorConcatenate_o[4] = rtb_VectorConcatenate_bl_tmp_0;

  /* SignalConversion generated from: '<S368>/Vector Concatenate2' incorporates:
   *  Constant: '<S368>/Constant4'
   */
  rtb_VectorConcatenate_o[5] = 0.0F;

  /* SignalConversion generated from: '<S368>/Vector Concatenate' incorporates:
   *  Concatenate: '<S368>/Vector Concatenate3'
   */
  rtb_VectorConcatenate_o[6] = localC->VectorConcatenate3[0];
  rtb_VectorConcatenate_o[7] = localC->VectorConcatenate3[1];
  rtb_VectorConcatenate_o[8] = localC->VectorConcatenate3[2];

  /* SignalConversion generated from: '<S364>/Multiply' incorporates:
   *  Delay: '<S364>/Delay'
   *  SignalConversion generated from: '<S364>/Delay'
   *  Sum: '<S364>/Sum'
   */
  rtb_VectorConcatenate_bl_tmp_0 = localDW->Delay_DSTATE[0] - rtu_FMS_In;
  rtb_VectorConcatenate_bl_tmp = localDW->Delay_DSTATE[1] - rtu_FMS_In_g;

  /* Product: '<S364>/Multiply' incorporates:
   *  Concatenate: '<S368>/Vector Concatenate'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_bl[i] = rtb_VectorConcatenate_o[i + 3] *
      rtb_VectorConcatenate_bl_tmp + rtb_VectorConcatenate_o[i] *
      rtb_VectorConcatenate_bl_tmp_0;
  }

  /* End of Product: '<S364>/Multiply' */

  /* Gain: '<S364>/Gain2' */
  rty_uv_cmd_mPs[0] = FMS_PARAM.XY_P * rtb_VectorConcatenate_bl[0];
  rty_uv_cmd_mPs[1] = FMS_PARAM.XY_P * rtb_VectorConcatenate_bl[1];

  /* Update for Delay: '<S364>/Delay' */
  localDW->icLoad = false;
}

/*
 * Output and update for action system:
 *    '<S361>/Brake Control'
 *    '<S307>/Brake Control'
 *    '<S88>/Brake Control'
 *    '<S264>/Brake Control'
 *    '<S235>/Brake Control'
 */
void FMS_BrakeControl_h(real32_T rty_uv_cmd_mPs[2])
{
  /* SignalConversion generated from: '<S363>/uv_cmd_mPs' incorporates:
   *  Constant: '<S363>/Brake Speed'
   */
  rty_uv_cmd_mPs[0] = 0.0F;
  rty_uv_cmd_mPs[1] = 0.0F;
}

/*
 * System initialize for action system:
 *    '<S361>/Move Control'
 *    '<S307>/Move Control'
 *    '<S88>/Move Control'
 *    '<S264>/Move Control'
 *    '<S235>/Move Control'
 */
void FMS_MoveControl_p_Init(DW_MoveControl_FMS_f_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator1' */
  localDW->Integrator1_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator' */
  localDW->Integrator_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator1' */
  localDW->Integrator1_DSTATE[1] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator' */
  localDW->Integrator_DSTATE[1] = 0.0F;
}

/*
 * System reset for action system:
 *    '<S361>/Move Control'
 *    '<S307>/Move Control'
 *    '<S88>/Move Control'
 *    '<S264>/Move Control'
 *    '<S235>/Move Control'
 */
void FMS_MoveControl_i_Reset(DW_MoveControl_FMS_f_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator1' */
  localDW->Integrator1_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator' */
  localDW->Integrator_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator1' */
  localDW->Integrator1_DSTATE[1] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator' */
  localDW->Integrator_DSTATE[1] = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S361>/Move Control'
 *    '<S307>/Move Control'
 *    '<S88>/Move Control'
 *    '<S264>/Move Control'
 *    '<S235>/Move Control'
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
  real32_T rtb_a_h;
  real32_T u;
  real32_T u_0;

  /* SignalConversion generated from: '<S365>/uv_cmd_mPs' incorporates:
   *  DiscreteIntegrator: '<S371>/Integrator1'
   */
  rty_uv_cmd_mPs[0] = localDW->Integrator1_DSTATE[0];

  /* Product: '<S372>/Multiply1' incorporates:
   *  Constant: '<S372>/const1'
   *  DiscreteIntegrator: '<S371>/Integrator'
   *  Sum: '<S372>/Add3'
   */
  rtb_Add3_h_idx_0 = localDW->Integrator_DSTATE[0] * 0.05F;

  /* SignalConversion generated from: '<S365>/uv_cmd_mPs' incorporates:
   *  DiscreteIntegrator: '<S371>/Integrator1'
   */
  rty_uv_cmd_mPs[1] = localDW->Integrator1_DSTATE[1];

  /* Product: '<S372>/Multiply1' incorporates:
   *  Constant: '<S372>/const1'
   *  DiscreteIntegrator: '<S371>/Integrator'
   *  Sum: '<S372>/Add3'
   */
  rtb_Add3_h_idx_1 = localDW->Integrator_DSTATE[1] * 0.05F;

  /* DeadZone: '<S369>/Dead Zone' */
  if (rtu_FMS_In > FMS_PARAM.PITCH_DZ) {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In - FMS_PARAM.PITCH_DZ;
  } else if (rtu_FMS_In >= -FMS_PARAM.PITCH_DZ) {
    rtb_Subtract3_o_idx_1 = 0.0F;
  } else {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In - (-FMS_PARAM.PITCH_DZ);
  }

  /* Sum: '<S372>/Add' incorporates:
   *  DeadZone: '<S369>/Dead Zone'
   *  DiscreteIntegrator: '<S371>/Integrator1'
   *  Gain: '<S365>/Gain6'
   *  Gain: '<S369>/Gain'
   *  Sum: '<S371>/Subtract'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Subtract3'
   */
  rtb_Subtract3_o_idx_0 = (localDW->Integrator1_DSTATE[0] - 1.0F / (1.0F -
    FMS_PARAM.PITCH_DZ) * rtb_Subtract3_o_idx_1 * FMS_PARAM.VEL_XY_LIM) +
    rtb_Add3_h_idx_0;

  /* DeadZone: '<S370>/Dead Zone' */
  if (rtu_FMS_In_d > FMS_PARAM.ROLL_DZ) {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In_d - FMS_PARAM.ROLL_DZ;
  } else if (rtu_FMS_In_d >= -FMS_PARAM.ROLL_DZ) {
    rtb_Subtract3_o_idx_1 = 0.0F;
  } else {
    rtb_Subtract3_o_idx_1 = rtu_FMS_In_d - (-FMS_PARAM.ROLL_DZ);
  }

  /* Sum: '<S372>/Add' incorporates:
   *  DeadZone: '<S370>/Dead Zone'
   *  DiscreteIntegrator: '<S371>/Integrator1'
   *  Gain: '<S365>/Gain6'
   *  Gain: '<S370>/Gain'
   *  Sum: '<S371>/Subtract'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Subtract3'
   */
  rtb_Subtract3_o_idx_1 = (localDW->Integrator1_DSTATE[1] - 1.0F / (1.0F -
    FMS_PARAM.ROLL_DZ) * rtb_Subtract3_o_idx_1 * FMS_PARAM.VEL_XY_LIM) +
    rtb_Add3_h_idx_1;

  /* Signum: '<S372>/Sign' incorporates:
   *  Sum: '<S372>/Subtract3'
   */
  if (rtb_Subtract3_o_idx_0 < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_Subtract3_o_idx_0 > 0.0F);
  }

  /* Sum: '<S372>/Add2' incorporates:
   *  Abs: '<S372>/Abs'
   *  Gain: '<S372>/Gain'
   *  Gain: '<S372>/Gain1'
   *  Product: '<S372>/Multiply2'
   *  Product: '<S372>/Multiply3'
   *  Signum: '<S372>/Sign'
   *  Sqrt: '<S372>/Sqrt'
   *  Sum: '<S372>/Add1'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Subtract'
   *  Sum: '<S372>/Subtract3'
   */
  rtb_a_h = (sqrtf((8.0F * fabsf(rtb_Subtract3_o_idx_0) + localC->d) * localC->d)
             - localC->d) * 0.5F * (real32_T)tmp + rtb_Add3_h_idx_0;

  /* Signum: '<S372>/Sign1' incorporates:
   *  Signum: '<S372>/Sign'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Subtract3'
   */
  u = rtb_Subtract3_o_idx_0 + localC->d;

  /* Signum: '<S372>/Sign2' incorporates:
   *  Signum: '<S372>/Sign'
   *  Sum: '<S372>/Subtract1'
   *  Sum: '<S372>/Subtract3'
   */
  u_0 = rtb_Subtract3_o_idx_0 - localC->d;

  /* Signum: '<S372>/Sign1' */
  if (u < 0.0F) {
    tmp = -1;
  } else {
    tmp = (u > 0.0F);
  }

  /* Signum: '<S372>/Sign2' */
  if (u_0 < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u_0 > 0.0F);
  }

  /* Sum: '<S372>/Add5' incorporates:
   *  Gain: '<S372>/Gain2'
   *  Product: '<S372>/Multiply4'
   *  Signum: '<S372>/Sign'
   *  Signum: '<S372>/Sign1'
   *  Signum: '<S372>/Sign2'
   *  Sum: '<S372>/Add2'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Add4'
   *  Sum: '<S372>/Subtract2'
   *  Sum: '<S372>/Subtract3'
   */
  rtb_a_h += ((rtb_Subtract3_o_idx_0 - rtb_a_h) + rtb_Add3_h_idx_0) * ((real32_T)
    (tmp - tmp_0) * 0.5F);

  /* Update for DiscreteIntegrator: '<S371>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S371>/Integrator'
   */
  localDW->Integrator1_DSTATE[0] += 0.004F * localDW->Integrator_DSTATE[0];

  /* Signum: '<S372>/Sign3' incorporates:
   *  Sum: '<S372>/Add6'
   */
  u = rtb_a_h + localC->d;

  /* Signum: '<S372>/Sign4' incorporates:
   *  Sum: '<S372>/Subtract3'
   */
  u_0 = rtb_a_h - localC->d;

  /* Signum: '<S372>/Sign5' */
  if (rtb_a_h < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_a_h > 0.0F);
  }

  /* Signum: '<S372>/Sign3' */
  if (u < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u > 0.0F);
  }

  /* Signum: '<S372>/Sign4' */
  if (u_0 < 0.0F) {
    tmp_1 = -1;
  } else {
    tmp_1 = (u_0 > 0.0F);
  }

  /* Signum: '<S372>/Sign6' */
  if (rtb_a_h < 0.0F) {
    tmp_2 = -1;
  } else {
    tmp_2 = (rtb_a_h > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S371>/Integrator' incorporates:
   *  Constant: '<S372>/const'
   *  Gain: '<S372>/Gain3'
   *  Product: '<S372>/Divide'
   *  Product: '<S372>/Multiply5'
   *  Product: '<S372>/Multiply6'
   *  Signum: '<S372>/Sign3'
   *  Signum: '<S372>/Sign4'
   *  Signum: '<S372>/Sign5'
   *  Signum: '<S372>/Sign6'
   *  Sum: '<S372>/Subtract4'
   *  Sum: '<S372>/Subtract5'
   *  Sum: '<S372>/Subtract6'
   */
  localDW->Integrator_DSTATE[0] += ((rtb_a_h / localC->d - (real32_T)tmp) *
    localC->Gain4 * ((real32_T)(tmp_0 - tmp_1) * 0.5F) - (real32_T)tmp_2 *
    58.836F) * 0.004F;

  /* Signum: '<S372>/Sign' incorporates:
   *  Sum: '<S372>/Subtract3'
   */
  if (rtb_Subtract3_o_idx_1 < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_Subtract3_o_idx_1 > 0.0F);
  }

  /* Sum: '<S372>/Add2' incorporates:
   *  Abs: '<S372>/Abs'
   *  Gain: '<S372>/Gain'
   *  Gain: '<S372>/Gain1'
   *  Product: '<S372>/Multiply2'
   *  Product: '<S372>/Multiply3'
   *  Signum: '<S372>/Sign'
   *  Sqrt: '<S372>/Sqrt'
   *  Sum: '<S372>/Add1'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Subtract'
   *  Sum: '<S372>/Subtract3'
   */
  rtb_a_h = (sqrtf((8.0F * fabsf(rtb_Subtract3_o_idx_1) + localC->d) * localC->d)
             - localC->d) * 0.5F * (real32_T)tmp + rtb_Add3_h_idx_1;

  /* Signum: '<S372>/Sign1' incorporates:
   *  Signum: '<S372>/Sign'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Subtract3'
   */
  u = rtb_Subtract3_o_idx_1 + localC->d;

  /* Signum: '<S372>/Sign2' incorporates:
   *  Signum: '<S372>/Sign'
   *  Sum: '<S372>/Subtract1'
   *  Sum: '<S372>/Subtract3'
   */
  u_0 = rtb_Subtract3_o_idx_1 - localC->d;

  /* Signum: '<S372>/Sign1' */
  if (u < 0.0F) {
    tmp = -1;
  } else {
    tmp = (u > 0.0F);
  }

  /* Signum: '<S372>/Sign2' */
  if (u_0 < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u_0 > 0.0F);
  }

  /* Sum: '<S372>/Add5' incorporates:
   *  Gain: '<S372>/Gain2'
   *  Product: '<S372>/Multiply4'
   *  Signum: '<S372>/Sign'
   *  Signum: '<S372>/Sign1'
   *  Signum: '<S372>/Sign2'
   *  Sum: '<S372>/Add2'
   *  Sum: '<S372>/Add3'
   *  Sum: '<S372>/Add4'
   *  Sum: '<S372>/Subtract2'
   *  Sum: '<S372>/Subtract3'
   */
  rtb_a_h += ((rtb_Subtract3_o_idx_1 - rtb_a_h) + rtb_Add3_h_idx_1) * ((real32_T)
    (tmp - tmp_0) * 0.5F);

  /* Update for DiscreteIntegrator: '<S371>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S371>/Integrator'
   */
  localDW->Integrator1_DSTATE[1] += 0.004F * localDW->Integrator_DSTATE[1];

  /* Signum: '<S372>/Sign3' incorporates:
   *  Sum: '<S372>/Add6'
   */
  u = rtb_a_h + localC->d;

  /* Signum: '<S372>/Sign4' incorporates:
   *  Sum: '<S372>/Subtract3'
   */
  u_0 = rtb_a_h - localC->d;

  /* Signum: '<S372>/Sign5' */
  if (rtb_a_h < 0.0F) {
    tmp = -1;
  } else {
    tmp = (rtb_a_h > 0.0F);
  }

  /* Signum: '<S372>/Sign3' */
  if (u < 0.0F) {
    tmp_0 = -1;
  } else {
    tmp_0 = (u > 0.0F);
  }

  /* Signum: '<S372>/Sign4' */
  if (u_0 < 0.0F) {
    tmp_1 = -1;
  } else {
    tmp_1 = (u_0 > 0.0F);
  }

  /* Signum: '<S372>/Sign6' */
  if (rtb_a_h < 0.0F) {
    tmp_2 = -1;
  } else {
    tmp_2 = (rtb_a_h > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S371>/Integrator' incorporates:
   *  Constant: '<S372>/const'
   *  Gain: '<S372>/Gain3'
   *  Product: '<S372>/Divide'
   *  Product: '<S372>/Multiply5'
   *  Product: '<S372>/Multiply6'
   *  Signum: '<S372>/Sign3'
   *  Signum: '<S372>/Sign4'
   *  Signum: '<S372>/Sign5'
   *  Signum: '<S372>/Sign6'
   *  Sum: '<S372>/Subtract4'
   *  Sum: '<S372>/Subtract5'
   *  Sum: '<S372>/Subtract6'
   */
  localDW->Integrator_DSTATE[1] += ((rtb_a_h / localC->d - (real32_T)tmp) *
    localC->Gain4 * ((real32_T)(tmp_0 - tmp_1) * 0.5F) - (real32_T)tmp_2 *
    58.836F) * 0.004F;
}

/*
 * System initialize for atomic system:
 *    '<S362>/Motion State'
 *    '<S308>/Motion State'
 *    '<S89>/Motion State'
 *    '<S265>/Motion State'
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
 *    '<S362>/Motion State'
 *    '<S308>/Motion State'
 *    '<S89>/Motion State'
 *    '<S265>/Motion State'
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
 *    '<S362>/Motion State'
 *    '<S308>/Motion State'
 *    '<S89>/Motion State'
 *    '<S265>/Motion State'
 */
void FMS_MotionState(real32_T rtu_motion_req, real32_T rtu_speed, MotionState
                     *rty_state, DW_MotionState_FMS_T *localDW)
{
  if (localDW->temporalCounter_i1 < 1023U) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S362>/Motion State' */
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

  /* End of Chart: '<S362>/Motion State' */
}

/*
 * Output and update for atomic system:
 *    '<S345>/NearbyRefWP'
 *    '<S69>/NearbyRefWP'
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
 *    '<S345>/OutRegionRegWP'
 *    '<S69>/OutRegionRegWP'
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
 *    '<S345>/SearchL1RefWP'
 *    '<S69>/SearchL1RefWP'
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
 *    '<S295>/Hold Control'
 *    '<S252>/Hold Control'
 *    '<S222>/Hold Control'
 */
void FMS_HoldControl_i_Init(DW_HoldControl_FMS_m_T *localDW)
{
  /* InitializeConditions for Delay: '<S298>/Delay' */
  localDW->icLoad = true;
}

/*
 * System reset for action system:
 *    '<S295>/Hold Control'
 *    '<S252>/Hold Control'
 *    '<S222>/Hold Control'
 */
void FMS_HoldControl_i_Reset(DW_HoldControl_FMS_m_T *localDW)
{
  /* InitializeConditions for Delay: '<S298>/Delay' */
  localDW->icLoad = true;
}

/*
 * Output and update for action system:
 *    '<S295>/Hold Control'
 *    '<S252>/Hold Control'
 *    '<S222>/Hold Control'
 */
void FMS_HoldControl_k(real32_T rtu_FMS_In, real32_T *rty_psi_rate_cmd_radPs,
  DW_HoldControl_FMS_m_T *localDW)
{
  real32_T rtb_Abs_b;
  real32_T rtb_psi_error_rad;

  /* Delay: '<S298>/Delay' */
  if (localDW->icLoad) {
    localDW->Delay_DSTATE = rtu_FMS_In;
  }

  /* Sum: '<S298>/Sum' incorporates:
   *  Delay: '<S298>/Delay'
   */
  rtb_psi_error_rad = localDW->Delay_DSTATE - rtu_FMS_In;

  /* Abs: '<S301>/Abs' */
  rtb_Abs_b = fabsf(rtb_psi_error_rad);

  /* Switch: '<S301>/Switch' incorporates:
   *  Constant: '<S301>/Constant'
   *  Constant: '<S302>/Constant'
   *  Product: '<S301>/Multiply'
   *  RelationalOperator: '<S302>/Compare'
   *  Signum: '<S301>/Sign'
   *  Sum: '<S301>/Subtract'
   */
  if (rtb_Abs_b > 3.14159274F) {
    /* Signum: '<S301>/Sign' */
    if (rtb_psi_error_rad < 0.0F) {
      rtb_psi_error_rad = -1.0F;
    } else {
      rtb_psi_error_rad = (real32_T)(rtb_psi_error_rad > 0.0F);
    }

    rtb_psi_error_rad *= rtb_Abs_b - 6.28318548F;
  }

  /* End of Switch: '<S301>/Switch' */

  /* Gain: '<S298>/Gain2' */
  *rty_psi_rate_cmd_radPs = FMS_PARAM.YAW_P * rtb_psi_error_rad;

  /* Update for Delay: '<S298>/Delay' */
  localDW->icLoad = false;
}

/*
 * System initialize for action system:
 *    '<S295>/Move Control'
 *    '<S252>/Move Control'
 *    '<S222>/Move Control'
 */
void FMS_MoveControl_m_Init(DW_MoveControl_FMS_c_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S304>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S304>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * System reset for action system:
 *    '<S295>/Move Control'
 *    '<S252>/Move Control'
 *    '<S222>/Move Control'
 */
void FMS_MoveControl_c_Reset(DW_MoveControl_FMS_c_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S304>/Integrator1' */
  localDW->Integrator1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S304>/Integrator' */
  localDW->Integrator_DSTATE = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S295>/Move Control'
 *    '<S252>/Move Control'
 *    '<S222>/Move Control'
 */
void FMS_MoveControl_o(real32_T rtu_FMS_In, real32_T *rty_psi_rate_cmd_radPs,
  const ConstB_MoveControl_FMS_n_T *localC, DW_MoveControl_FMS_c_T *localDW)
{
  real32_T rtb_Add3_p;
  real32_T rtb_Subtract3_k;
  real32_T rtb_a_c;
  real32_T u;
  real32_T u_0;

  /* Product: '<S305>/Multiply1' incorporates:
   *  Constant: '<S305>/const1'
   *  DiscreteIntegrator: '<S304>/Integrator'
   */
  rtb_Add3_p = localDW->Integrator_DSTATE * 0.02F;

  /* DeadZone: '<S303>/Dead Zone' */
  if (rtu_FMS_In > FMS_PARAM.YAW_DZ) {
    u = rtu_FMS_In - FMS_PARAM.YAW_DZ;
  } else if (rtu_FMS_In >= -FMS_PARAM.YAW_DZ) {
    u = 0.0F;
  } else {
    u = rtu_FMS_In - (-FMS_PARAM.YAW_DZ);
  }

  /* Sum: '<S305>/Add' incorporates:
   *  DeadZone: '<S303>/Dead Zone'
   *  DiscreteIntegrator: '<S304>/Integrator1'
   *  Gain: '<S299>/Gain1'
   *  Gain: '<S303>/Gain'
   *  Sum: '<S304>/Subtract'
   */
  rtb_Subtract3_k = (localDW->Integrator1_DSTATE - 1.0F / (1.0F -
    FMS_PARAM.YAW_DZ) * u * FMS_PARAM.YAW_RATE_LIM) + rtb_Add3_p;

  /* Signum: '<S305>/Sign' */
  if (rtb_Subtract3_k < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(rtb_Subtract3_k > 0.0F);
  }

  /* Sum: '<S305>/Add2' incorporates:
   *  Abs: '<S305>/Abs'
   *  Gain: '<S305>/Gain'
   *  Gain: '<S305>/Gain1'
   *  Product: '<S305>/Multiply2'
   *  Product: '<S305>/Multiply3'
   *  Signum: '<S305>/Sign'
   *  Sqrt: '<S305>/Sqrt'
   *  Sum: '<S305>/Add1'
   *  Sum: '<S305>/Subtract'
   */
  rtb_a_c = (sqrtf((8.0F * fabsf(rtb_Subtract3_k) + localC->d) * localC->d) -
             localC->d) * 0.5F * u + rtb_Add3_p;

  /* Sum: '<S305>/Add3' */
  u = rtb_Subtract3_k + localC->d;

  /* Sum: '<S305>/Subtract1' */
  u_0 = rtb_Subtract3_k - localC->d;

  /* Signum: '<S305>/Sign1' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S305>/Sign2' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Sum: '<S305>/Add5' incorporates:
   *  Gain: '<S305>/Gain2'
   *  Product: '<S305>/Multiply4'
   *  Signum: '<S305>/Sign1'
   *  Signum: '<S305>/Sign2'
   *  Sum: '<S305>/Add4'
   *  Sum: '<S305>/Subtract2'
   */
  rtb_a_c += ((rtb_Subtract3_k - rtb_a_c) + rtb_Add3_p) * ((u - u_0) * 0.5F);

  /* SignalConversion generated from: '<S299>/psi_rate_cmd_radPs' incorporates:
   *  DiscreteIntegrator: '<S304>/Integrator1'
   */
  *rty_psi_rate_cmd_radPs = localDW->Integrator1_DSTATE;

  /* Update for DiscreteIntegrator: '<S304>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S304>/Integrator'
   */
  localDW->Integrator1_DSTATE += 0.004F * localDW->Integrator_DSTATE;

  /* Signum: '<S305>/Sign5' */
  if (rtb_a_c < 0.0F) {
    /* Signum: '<S305>/Sign6' */
    rtb_Add3_p = -1.0F;
  } else {
    /* Signum: '<S305>/Sign6' */
    rtb_Add3_p = (real32_T)(rtb_a_c > 0.0F);
  }

  /* Sum: '<S305>/Add6' */
  u = rtb_a_c + localC->d;

  /* Sum: '<S305>/Subtract3' */
  u_0 = rtb_a_c - localC->d;

  /* Signum: '<S305>/Sign3' */
  if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Signum: '<S305>/Sign4' */
  if (u_0 < 0.0F) {
    u_0 = -1.0F;
  } else {
    u_0 = (real32_T)(u_0 > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S304>/Integrator' incorporates:
   *  Constant: '<S305>/const'
   *  Gain: '<S305>/Gain3'
   *  Product: '<S305>/Divide'
   *  Product: '<S305>/Multiply5'
   *  Product: '<S305>/Multiply6'
   *  Signum: '<S305>/Sign3'
   *  Signum: '<S305>/Sign4'
   *  Signum: '<S305>/Sign5'
   *  Sum: '<S305>/Subtract4'
   *  Sum: '<S305>/Subtract5'
   *  Sum: '<S305>/Subtract6'
   */
  localDW->Integrator_DSTATE += ((rtb_a_c / localC->d - rtb_Add3_p) *
    localC->Gain4 * ((u - u_0) * 0.5F) - rtb_Add3_p * 15.707963F) * 0.004F;
}

/*
 * System initialize for atomic system:
 *    '<S296>/Motion State'
 *    '<S253>/Motion State'
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
 *    '<S296>/Motion State'
 *    '<S253>/Motion State'
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
 *    '<S296>/Motion State'
 *    '<S253>/Motion State'
 */
void FMS_MotionState_i(real32_T rtu_motion_req, real32_T rtu_speed, MotionState *
  rty_state, DW_MotionState_FMS_o_T *localDW)
{
  if (localDW->temporalCounter_i1 < 255U) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S296>/Motion State' */
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

  /* End of Chart: '<S296>/Motion State' */
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
  real_T rtb_Sum_oz_idx_0;
  int32_T tmp;

  /* Gain: '<S399>/deg2rad' */
  rtb_Sum_oz_idx_0 = 0.017453292519943295 * rtu_llo[0];

  /* Trigonometry: '<S400>/Sin' */
  rtb_Sum2_i = sin(rtb_Sum_oz_idx_0);

  /* Product: '<S400>/Multiply1' incorporates:
   *  Math: '<S400>/Square1'
   *  Product: '<S400>/Multiply'
   */
  rtb_Gain_j1 = rtb_Sum2_i * rtb_Sum2_i * localC->ff;

  /* Product: '<S400>/Divide' incorporates:
   *  Constant: '<S400>/Constant'
   *  Constant: '<S400>/R'
   *  Sqrt: '<S400>/Sqrt'
   *  Sum: '<S400>/Sum1'
   */
  rtb_Sum2_i = 6.378137E+6 / sqrt(1.0 - rtb_Gain_j1);

  /* Product: '<S400>/Product3' incorporates:
   *  Constant: '<S400>/Constant1'
   *  Product: '<S400>/Multiply1'
   *  Sum: '<S400>/Sum2'
   */
  rtb_Gain_j1 = 1.0 / (1.0 - rtb_Gain_j1) * localC->Sum4 * rtb_Sum2_i;

  /* Product: '<S400>/Multiply2' incorporates:
   *  Trigonometry: '<S400>/Cos'
   */
  rtb_Sum2_i *= cos(rtb_Sum_oz_idx_0);

  /* Sum: '<S399>/Sum' */
  rtb_Sum_oz_idx_0 = rtu_lla[0] - rtu_llo[0];

  /* Abs: '<S404>/Abs' incorporates:
   *  Abs: '<S407>/Abs1'
   *  Switch: '<S404>/Switch1'
   */
  rtb_Sum_n = fabs(rtb_Sum_oz_idx_0);

  /* Switch: '<S404>/Switch1' incorporates:
   *  Abs: '<S404>/Abs'
   *  Bias: '<S404>/Bias2'
   *  Bias: '<S404>/Bias3'
   *  Constant: '<S401>/Constant'
   *  Constant: '<S401>/Constant1'
   *  Constant: '<S406>/Constant'
   *  Gain: '<S404>/Gain1'
   *  Product: '<S404>/Multiply'
   *  RelationalOperator: '<S406>/Compare'
   *  Signum: '<S404>/Sign'
   *  Switch: '<S401>/Switch'
   */
  if (rtb_Sum_n > 90.0) {
    /* Switch: '<S407>/Switch1' incorporates:
     *  Bias: '<S407>/Bias2'
     *  Bias: '<S407>/Bias3'
     *  Constant: '<S407>/Constant'
     *  Constant: '<S408>/Constant'
     *  Math: '<S407>/Math Function'
     *  RelationalOperator: '<S408>/Compare'
     */
    if (rtb_Sum_n > 180.0) {
      rtb_Sum_oz_idx_0 = rt_modd(rtb_Sum_oz_idx_0 + 180.0, 360.0) - 180.0;
    }

    /* End of Switch: '<S407>/Switch1' */

    /* Signum: '<S404>/Sign' */
    if (rtb_Sum_oz_idx_0 < 0.0) {
      rtb_Sum_oz_idx_0 = -1.0;
    } else {
      rtb_Sum_oz_idx_0 = (rtb_Sum_oz_idx_0 > 0.0);
    }

    rtb_Sum_oz_idx_0 *= -(rtb_Sum_n - 90.0) + 90.0;
    tmp = 180;
  } else {
    tmp = 0;
  }

  /* Sum: '<S401>/Sum' incorporates:
   *  Sum: '<S399>/Sum'
   *  Switch: '<S401>/Switch'
   */
  rtb_Sum_n = (rtu_lla[1] - rtu_llo[1]) + (real_T)tmp;

  /* Product: '<S399>/Multiply' incorporates:
   *  Gain: '<S399>/deg2rad1'
   */
  rtb_Sum_oz_idx_0 = 0.017453292519943295 * rtb_Sum_oz_idx_0 * rtb_Gain_j1;

  /* Switch: '<S403>/Switch1' incorporates:
   *  Abs: '<S403>/Abs1'
   *  Bias: '<S403>/Bias2'
   *  Bias: '<S403>/Bias3'
   *  Constant: '<S403>/Constant'
   *  Constant: '<S405>/Constant'
   *  Math: '<S403>/Math Function'
   *  RelationalOperator: '<S405>/Compare'
   */
  if (fabs(rtb_Sum_n) > 180.0) {
    rtb_Sum_n = rt_modd(rtb_Sum_n + 180.0, 360.0) - 180.0;
  }

  /* Product: '<S399>/Multiply' incorporates:
   *  Gain: '<S399>/deg2rad1'
   *  Switch: '<S403>/Switch1'
   */
  rtb_Sum2_i *= 0.017453292519943295 * rtb_Sum_n;

  /* Gain: '<S399>/deg2rad2' */
  rtb_Gain_j1 = 0.017453292519943295 * rtu_psio;

  /* Trigonometry: '<S402>/SinCos' */
  rtb_Sum_n = sin(rtb_Gain_j1);
  rtb_Gain_j1 = cos(rtb_Gain_j1);

  /* DataTypeConversion: '<S398>/Data Type Conversion' incorporates:
   *  Gain: '<S399>/Gain'
   *  Product: '<S402>/Multiply1'
   *  Product: '<S402>/Multiply2'
   *  Product: '<S402>/Multiply3'
   *  Product: '<S402>/Multiply4'
   *  Sum: '<S399>/Sum1'
   *  Sum: '<S402>/Sum2'
   *  Sum: '<S402>/Sum3'
   */
  rty_pos[0] = (real32_T)(rtb_Sum_oz_idx_0 * rtb_Gain_j1 + rtb_Sum2_i *
    rtb_Sum_n);
  rty_pos[1] = (real32_T)(rtb_Sum2_i * rtb_Gain_j1 - rtb_Sum_oz_idx_0 *
    rtb_Sum_n);
  rty_pos[2] = (real32_T)-(rtu_lla[2] + rtu_href);
}

int16_T rt_sqrt_Us16_Ys16_Is32_f_s(int16_T u)
{
  int32_T iBit;
  int16_T shiftMask;
  int16_T y;

  /* Fixed-Point Sqrt Computation by the bisection method. */
  y = 0;
  shiftMask = 16384;
  for (iBit = 0; iBit < 15; iBit++) {
    int16_T tmp01_y;
    tmp01_y = (int16_T)(y | shiftMask);
    if (tmp01_y * tmp01_y <= u) {
      y = tmp01_y;
    }

    shiftMask = (int16_T)((uint32_T)shiftMask >> 1U);
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
static real32_T FMS_norm(const real32_T x[2])
{
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  scale = 1.29246971E-26F;
  absxk = fabsf(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = fabsf(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrtf(y);
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_exit_internal_Auto(void)
{
  if (FMS_DW.is_Auto == FMS_IN_Mission_a) {
    FMS_DW.is_Mission = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_mn;
  } else {
    FMS_DW.is_Offboard = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_mn;
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_Auto(void)
{
  real_T lla[3];
  real32_T tmp[2];
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
            FMS_DW.is_Mission = FMS_IN_NO_ACTIVE_CHILD_mn;
            FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_mn;
            FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
            FMS_DW.is_Vehicle = FMS_IN_Disarm;
            FMS_B.state = VehicleState_Disarm;
            break;

           case FMS_IN_Land:
            {
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
            tmp[0] = FMS_B.BusConversion_InsertedFor_State.x_R -
              FMS_B.Cmd_In.sp_waypoint[0];
            tmp[1] = FMS_B.BusConversion_InsertedFor_State.y_R -
              FMS_B.Cmd_In.sp_waypoint[1];
            if (FMS_norm(tmp) < 0.5F) {
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
              tmp[0] = FMS_B.BusConversion_InsertedFor_State.x_R -
                FMS_B.Cmd_In.sp_waypoint[0];
              tmp[1] = FMS_B.BusConversion_InsertedFor_State.y_R -
                FMS_B.Cmd_In.sp_waypoint[1];
              if (FMS_norm(tmp) < 0.5F) {
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
              tmp[0] = FMS_B.BusConversion_InsertedFor_State.x_R -
                FMS_B.Cmd_In.sp_waypoint[0];
              tmp[1] = FMS_B.BusConversion_InsertedFor_State.y_R -
                FMS_B.Cmd_In.sp_waypoint[1];

              /* Constant: '<Root>/ACCEPT_R' */
              if (FMS_norm(tmp) <= FMS_PARAM.ACCEPT_R) {
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
        if (FMS_B.LogicalOperator) {
          FMS_DW.is_Offboard = FMS_IN_Run;
          FMS_B.state = VehicleState_Offboard;
        }
        break;

       case FMS_IN_Run:
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
static void FMS_Arm(void)
{
  if (!FMS_B.LogicalOperator1) {
    FMS_DW.durationCounter_1_p = 0;
  }

  if ((FMS_DW.durationCounter_1_p >= 75000) && (FMS_B.target_mode !=
       PilotMode_Mission)) {
    if (FMS_DW.is_Arm == FMS_IN_Auto) {
      FMS_exit_internal_Auto();
      FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
    } else {
      FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
    }

    FMS_DW.is_Vehicle = FMS_IN_Disarm;
    FMS_B.state = VehicleState_Disarm;
  } else if ((FMS_DW.mode_prev != FMS_DW.mode_start) && (FMS_B.target_mode !=
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

      FMS_DW.durationCounter_1_f = 0;
      FMS_DW.is_Arm = FMS_IN_Return;
      FMS_B.state = VehicleState_Return;
    } else {
      switch (FMS_DW.is_Arm) {
       case FMS_IN_Auto:
        FMS_Auto();
        break;

       case FMS_IN_InvalidMode:
        FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
        FMS_DW.is_Vehicle = FMS_IN_Disarm;
        FMS_B.state = VehicleState_Disarm;
        break;

       case FMS_IN_Manual_k:
       case FMS_IN_Position_m:
        break;

       case FMS_IN_Return:
        {
          if (!FMS_B.LogicalOperator1) {
            FMS_DW.durationCounter_1_f = 0;
          }

          if (FMS_DW.durationCounter_1_f >= 500) {
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
            FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
            FMS_DW.is_Vehicle = FMS_IN_Disarm;
            FMS_B.state = VehicleState_Disarm;
          }
        }
        break;

       case FMS_IN_Stabilize:
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
static void FMS_Vehicle(void)
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
    switch (FMS_DW.is_Vehicle) {
     case FMS_IN_Arm:
      if (FMS_DW.is_Arm == FMS_IN_Auto) {
        FMS_exit_internal_Auto();
        FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
      } else {
        FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
      }
      break;

     case FMS_IN_Standby:
      FMS_DW.prep_mission_takeoff = 0.0;
      FMS_DW.durationCounter_1_i = 0;
      break;
    }

    FMS_DW.is_Vehicle = FMS_IN_Disarm;
    FMS_B.state = VehicleState_Disarm;
  } else {
    boolean_T guard1 = false;
    boolean_T guard2 = false;
    guard1 = false;
    guard2 = false;
    switch (FMS_DW.is_Vehicle) {
     case FMS_IN_Arm:
      FMS_Arm();
      break;

     case FMS_IN_Disarm:
      {
        if (FMS_sf_msg_pop_M()) {
          out = (FMS_DW.M_msgReservedData == FMS_Cmd_PreArm);
        } else {
          out = false;
        }

        if (out) {
          FMS_DW.durationCounter_1_i = 0;
          FMS_DW.is_Vehicle = FMS_IN_Standby;
          FMS_DW.temporalCounter_i1 = 0U;
          if (FMS_B.target_mode == PilotMode_Mission) {
            if ((FMS_B.wp_index <= FMS_U.Mission_Data.valid_items) &&
                (FMS_U.Mission_Data.command[FMS_B.wp_index - 1] == (int32_T)
                 NAV_Cmd_Takeoff)) {
              FMS_DW.prep_mission_takeoff = 1.0;
              guard1 = true;
            } else {
              int32_T b_previousEvent;
              b_previousEvent = FMS_DW.sfEvent;
              FMS_DW.sfEvent = FMS_event_DisarmEvent;

              /* Chart: '<Root>/State Machine' */
              FMS_c11_FMS();
              FMS_DW.sfEvent = b_previousEvent;
              if (FMS_DW.is_Vehicle != FMS_IN_Standby) {
              } else {
                guard1 = true;
              }
            }
          } else {
            guard1 = true;
          }
        }
      }
      break;

     case FMS_IN_Standby:
      if (FMS_B.target_mode != PilotMode_None) {
        guard2 = true;
      } else if ((FMS_DW.temporalCounter_i1 >= 2500U) || (FMS_DW.sfEvent ==
                  FMS_event_DisarmEvent)) {
        FMS_DW.prep_mission_takeoff = 0.0;
        FMS_DW.durationCounter_1_i = 0;
        FMS_DW.is_Vehicle = FMS_IN_Disarm;
        FMS_B.state = VehicleState_Disarm;
      } else {
        if (FMS_DW.prep_mission_takeoff != 1.0) {
          FMS_DW.durationCounter_1_i = 0;
        }

        if (FMS_DW.durationCounter_1_i >= 500) {
          guard2 = true;
        }
      }
      break;
    }

    if (guard2) {
      FMS_DW.prep_mission_takeoff = 0.0;
      FMS_DW.durationCounter_1_i = 0;
      FMS_DW.durationCounter_1_p = 0;
      FMS_DW.is_Vehicle = FMS_IN_Arm;
      FMS_enter_internal_Arm();
    }

    if (guard1) {
      FMS_DW.home[0] = FMS_B.BusConversion_InsertedFor_State.x_R;
      FMS_DW.home[1] = FMS_B.BusConversion_InsertedFor_State.y_R;
      FMS_DW.home[2] = FMS_B.BusConversion_InsertedFor_State.h_R;
      FMS_B.state = VehicleState_Standby;
    }
  }
}

/* Function for Chart: '<Root>/State Machine' */
static void FMS_c11_FMS(void)
{
  /* Chart: '<Root>/State Machine' incorporates:
   *  Inport: '<Root>/Mission_Data'
   */
  if (FMS_DW.is_active_c11_FMS == 0U) {
    FMS_DW.mission_timestamp_prev = FMS_U.Mission_Data.timestamp;
    FMS_DW.mission_timestamp_start = FMS_U.Mission_Data.timestamp;
    FMS_DW.cmd_prev = FMS_B.Switch1;
    FMS_DW.cmd_start = FMS_B.Switch1;
    FMS_DW.mode_prev = FMS_B.target_mode;
    FMS_DW.mode_start = FMS_B.target_mode;
    FMS_DW.is_active_c11_FMS = 1U;
    FMS_DW.is_active_Command_Listener = 1U;
    FMS_DW.is_Command_Listener = FMS_IN_Listen;
    FMS_DW.is_active_Combo_Stick = 1U;
    FMS_DW.durationCounter_2 = 0;
    FMS_DW.durationCounter_1_i1 = 0;
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
        if ((FMS_DW.cmd_prev != FMS_DW.cmd_start) && (FMS_B.Switch1 !=
             FMS_Cmd_None)) {
          FMS_DW.save_cmd = FMS_B.Switch1;
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
        if (!FMS_BottomRight(FMS_B.BusConversion_InsertedFor_Sta_n.stick_yaw,
                             FMS_B.BusConversion_InsertedFor_Sta_n.stick_throttle))
        {
          FMS_DW.durationCounter_2 = 0;
          FMS_DW.durationCounter_1_i1 = 0;
          FMS_DW.is_Combo_Stick = FMS_IN_Idle;
        }
        break;

       case FMS_IN_Disarm:
        if (!FMS_BottomLeft(FMS_B.BusConversion_InsertedFor_Sta_n.stick_yaw,
                            FMS_B.BusConversion_InsertedFor_Sta_n.stick_throttle))
        {
          FMS_DW.durationCounter_2 = 0;
          FMS_DW.durationCounter_1_i1 = 0;
          FMS_DW.is_Combo_Stick = FMS_IN_Idle;
        }
        break;

       case FMS_IN_Idle:
        {
          if (!FMS_DW.br) {
            FMS_DW.durationCounter_1_i1 = 0;
          }

          if (FMS_DW.durationCounter_1_i1 > 375) {
            FMS_DW.is_Combo_Stick = FMS_IN_Arm;
            FMS_DW.M_msgReservedData = FMS_Cmd_PreArm;
            FMS_sf_msg_send_M();
          } else {
            if (!FMS_DW.bl) {
              FMS_DW.durationCounter_2 = 0;
            }

            if (FMS_DW.durationCounter_2 > 375) {
              int32_T b_previousEvent;
              FMS_DW.is_Combo_Stick = FMS_IN_Disarm;
              b_previousEvent = FMS_DW.sfEvent;
              FMS_DW.sfEvent = FMS_event_DisarmEvent;
              if (FMS_DW.is_active_Vehicle != 0U) {
                FMS_Vehicle();
              }

              FMS_DW.sfEvent = b_previousEvent;
            } else {
              FMS_DW.bl = FMS_BottomLeft
                (FMS_B.BusConversion_InsertedFor_Sta_n.stick_yaw,
                 FMS_B.BusConversion_InsertedFor_Sta_n.stick_throttle);
              if (!FMS_DW.bl) {
                FMS_DW.durationCounter_2 = 0;
              }

              FMS_DW.br = FMS_BottomRight
                (FMS_B.BusConversion_InsertedFor_Sta_n.stick_yaw,
                 FMS_B.BusConversion_InsertedFor_Sta_n.stick_throttle);
              if (!FMS_DW.br) {
                FMS_DW.durationCounter_1_i1 = 0;
              }
            }
          }
        }
        break;
      }
    }

    if (FMS_DW.is_active_Vehicle != 0U) {
      FMS_Vehicle();
    }
  }

  /* End of Chart: '<Root>/State Machine' */
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
  int32_T i;
  int32_T i_0;
  int32_T tmp;
  int32_T tmp_0;
  int32_T tmp_1;
  real32_T rtb_Transpose[9];
  real32_T rtb_MatrixConcatenate3[3];
  real32_T rtb_Multiply[3];
  real32_T rtb_Sum2_n[3];
  real32_T rtb_Transpose_0[3];
  real32_T rtb_MathFunction_ec[2];
  real32_T rtb_MathFunction_o[2];
  real32_T rtb_Saturation1_g[2];
  real32_T rtb_TmpSignalConversionAtMath_j[2];
  real32_T rtb_TmpSignalConversionAtSqua_d[2];
  real32_T rtb_Divide_o_idx_0;
  real32_T rtb_Divide_o_idx_1;
  real32_T rtb_Divide_o_idx_2;
  real32_T rtb_Gain_fj;
  real32_T rtb_MathFunction_c_idx_0;
  real32_T rtb_Rem_i;
  real32_T rtb_Square2;
  real32_T rtb_Switch_k;
  real32_T rtb_Transpose_tmp;
  real32_T rtb_Transpose_tmp_0;
  real32_T rtb_a_k;
  real32_T tmp_2;
  uint32_T qY;
  int16_T rtb_SquareRoot;
  int8_T rtPrevAction;
  MotionState rtb_state_ee;

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
  i = FMS_U.Control_Out.actuator_cmd[0] * FMS_U.Control_Out.actuator_cmd[0];
  if (i > 32767) {
    i = 32767;
  } else if (i < -32768) {
    i = -32768;
  }

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_Divide_o_idx_1 = FMS_U.INS_Out.quat[1] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  tmp_1 = FMS_U.Control_Out.actuator_cmd[1] * FMS_U.Control_Out.actuator_cmd[1];
  if (tmp_1 > 32767) {
    tmp_1 = 32767;
  } else if (tmp_1 < -32768) {
    tmp_1 = -32768;
  }

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_Divide_o_idx_2 = FMS_U.INS_Out.quat[2] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  tmp_0 = FMS_U.Control_Out.actuator_cmd[2] * FMS_U.Control_Out.actuator_cmd[2];
  if (tmp_0 > 32767) {
    tmp_0 = 32767;
  } else if (tmp_0 < -32768) {
    tmp_0 = -32768;
  }

  /* Product: '<S16>/Divide' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_Square2 = FMS_U.INS_Out.quat[3] / rtb_Square2;

  /* Math: '<S2>/Square' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  tmp = FMS_U.Control_Out.actuator_cmd[3] * FMS_U.Control_Out.actuator_cmd[3];
  if (tmp > 32767) {
    tmp = 32767;
  } else if (tmp < -32768) {
    tmp = -32768;
  }

  /* Math: '<S17>/Square' incorporates:
   *  Math: '<S18>/Square'
   *  Math: '<S19>/Square'
   */
  rtb_MathFunction_c_idx_0 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_0;

  /* Math: '<S17>/Square2' incorporates:
   *  Math: '<S18>/Square2'
   *  Math: '<S19>/Square2'
   */
  rtb_Switch_k = rtb_Divide_o_idx_2 * rtb_Divide_o_idx_2;

  /* Math: '<S17>/Square1' incorporates:
   *  Math: '<S18>/Square1'
   *  Math: '<S19>/Square1'
   */
  rtb_a_k = rtb_Divide_o_idx_1 * rtb_Divide_o_idx_1;

  /* Math: '<S17>/Square3' incorporates:
   *  Math: '<S18>/Square3'
   *  Math: '<S19>/Square3'
   */
  rtb_Gain_fj = rtb_Square2 * rtb_Square2;

  /* Sum: '<S17>/Subtract' incorporates:
   *  Math: '<S17>/Square'
   *  Math: '<S17>/Square1'
   *  Math: '<S17>/Square2'
   *  Math: '<S17>/Square3'
   *  Sum: '<S17>/Add'
   *  Sum: '<S17>/Add1'
   */
  rtb_Transpose[0] = (rtb_MathFunction_c_idx_0 + rtb_a_k) - (rtb_Switch_k +
    rtb_Gain_fj);

  /* Product: '<S17>/Multiply' incorporates:
   *  Product: '<S18>/Multiply'
   */
  tmp_2 = rtb_Divide_o_idx_1 * rtb_Divide_o_idx_2;

  /* Product: '<S17>/Multiply1' incorporates:
   *  Product: '<S18>/Multiply1'
   */
  rtb_Rem_i = rtb_Divide_o_idx_0 * rtb_Square2;

  /* Gain: '<S17>/Gain' incorporates:
   *  Product: '<S17>/Multiply'
   *  Product: '<S17>/Multiply1'
   *  Sum: '<S17>/Subtract1'
   */
  rtb_Transpose[1] = (tmp_2 - rtb_Rem_i) * 2.0F;

  /* Product: '<S17>/Multiply2' incorporates:
   *  Product: '<S19>/Multiply'
   */
  rtb_Transpose_tmp = rtb_Divide_o_idx_1 * rtb_Square2;

  /* Product: '<S17>/Multiply3' incorporates:
   *  Product: '<S19>/Multiply1'
   */
  rtb_Transpose_tmp_0 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_2;

  /* Gain: '<S17>/Gain1' incorporates:
   *  Product: '<S17>/Multiply2'
   *  Product: '<S17>/Multiply3'
   *  Sum: '<S17>/Add2'
   */
  rtb_Transpose[2] = (rtb_Transpose_tmp + rtb_Transpose_tmp_0) * 2.0F;

  /* Gain: '<S18>/Gain' incorporates:
   *  Sum: '<S18>/Add3'
   */
  rtb_Transpose[3] = (tmp_2 + rtb_Rem_i) * 2.0F;

  /* Sum: '<S18>/Subtract' incorporates:
   *  Sum: '<S18>/Add'
   *  Sum: '<S18>/Add1'
   */
  rtb_Transpose[4] = (rtb_MathFunction_c_idx_0 + rtb_Switch_k) - (rtb_a_k +
    rtb_Gain_fj);

  /* Product: '<S18>/Multiply2' incorporates:
   *  Product: '<S19>/Multiply2'
   */
  tmp_2 = rtb_Divide_o_idx_2 * rtb_Square2;

  /* Product: '<S18>/Multiply3' incorporates:
   *  Product: '<S19>/Multiply3'
   */
  rtb_Rem_i = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_1;

  /* Gain: '<S18>/Gain1' incorporates:
   *  Product: '<S18>/Multiply2'
   *  Product: '<S18>/Multiply3'
   *  Sum: '<S18>/Subtract1'
   */
  rtb_Transpose[5] = (tmp_2 - rtb_Rem_i) * 2.0F;

  /* Gain: '<S19>/Gain' incorporates:
   *  Sum: '<S19>/Subtract2'
   */
  rtb_Transpose[6] = (rtb_Transpose_tmp - rtb_Transpose_tmp_0) * 2.0F;

  /* Gain: '<S19>/Gain1' incorporates:
   *  Sum: '<S19>/Add2'
   */
  rtb_Transpose[7] = (tmp_2 + rtb_Rem_i) * 2.0F;

  /* Sum: '<S19>/Subtract' incorporates:
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_Transpose[8] = (rtb_MathFunction_c_idx_0 + rtb_Gain_fj) - (rtb_a_k +
    rtb_Switch_k);

  /* Product: '<S2>/Multiply' incorporates:
   *  Inport: '<Root>/INS_Out'
   *  Math: '<S2>/Transpose'
   *  SignalConversion generated from: '<S2>/Matrix Concatenate3'
   * */
  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_Multiply[i_0] = (rtb_Transpose[3 * i_0 + 1] * FMS_U.INS_Out.ay +
                         rtb_Transpose[3 * i_0] * FMS_U.INS_Out.ax) +
      rtb_Transpose[3 * i_0 + 2] * FMS_U.INS_Out.az;
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
  rtb_SquareRoot = rt_sqrt_Us16_Ys16_Is32_f_s((int16_T)((int16_T)((((int16_T)i +
    (int16_T)tmp_1) + (int16_T)tmp_0) + (int16_T)tmp) >> 2));

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
    FMS_B.Switch1 = (FMS_Cmd)FMS_U.Pilot_Cmd.cmd_1;
  } else if (FMS_U.GCS_Cmd.cmd_1 != FMS_DW.DelayInput1_DSTATE_p) {
    /* Switch: '<S22>/Switch2' incorporates:
     *  DataTypeConversion: '<S22>/Data Type Conversion1'
     *  Inport: '<Root>/GCS_Cmd'
     *  Switch: '<S22>/Switch1'
     */
    FMS_B.Switch1 = (FMS_Cmd)FMS_U.GCS_Cmd.cmd_1;
  } else {
    /* Switch: '<S22>/Switch1' incorporates:
     *  Constant: '<S22>/Constant1'
     *  Switch: '<S22>/Switch2'
     */
    FMS_B.Switch1 = FMS_Cmd_None;
  }

  /* End of Switch: '<S22>/Switch1' */

  /* BusCreator generated from: '<Root>/State Machine' incorporates:
   *  Inport: '<Root>/Pilot_Cmd'
   */
  FMS_B.BusConversion_InsertedFor_Sta_n = FMS_U.Pilot_Cmd;

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
   *  Inport: '<Root>/Mission_Data'
   */
  if (FMS_DW.temporalCounter_i1 < 4095U) {
    FMS_DW.temporalCounter_i1++;
  }

  FMS_DW.sfEvent = -1;
  FMS_DW.mission_timestamp_prev = FMS_DW.mission_timestamp_start;
  FMS_DW.mission_timestamp_start = FMS_U.Mission_Data.timestamp;
  FMS_DW.cmd_prev = FMS_DW.cmd_start;
  FMS_DW.cmd_start = FMS_B.Switch1;
  FMS_DW.mode_prev = FMS_DW.mode_start;
  FMS_DW.mode_start = FMS_B.target_mode;
  FMS_DW.M_isValid = false;
  FMS_c11_FMS();
  FMS_sf_msg_discard_M();
  if (FMS_B.LogicalOperator1) {
    FMS_DW.durationCounter_1++;
    FMS_DW.durationCounter_1_f++;
    FMS_DW.durationCounter_1_p++;
  } else {
    FMS_DW.durationCounter_1 = 0;
    FMS_DW.durationCounter_1_f = 0;
    FMS_DW.durationCounter_1_p = 0;
  }

  if (FMS_DW.prep_mission_takeoff == 1.0) {
    FMS_DW.durationCounter_1_i++;
  } else {
    FMS_DW.durationCounter_1_i = 0;
  }

  if (FMS_DW.br) {
    FMS_DW.durationCounter_1_i1++;
  } else {
    FMS_DW.durationCounter_1_i1 = 0;
  }

  if (FMS_DW.bl) {
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
      switch (FMS_DW.SwitchCase_ActiveSubsystem_on) {
       case 0:
       case 1:
       case 4:
        break;

       case 2:
        /* SwitchCase: '<S361>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

        /* SwitchCase: '<S351>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;
        break;

       case 3:
        /* SwitchCase: '<S307>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

        /* SwitchCase: '<S285>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

        /* SwitchCase: '<S295>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;
        break;
      }

      /* SwitchCase: '<S41>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_on = -1;
      break;

     case 1:
      /* Disable for SwitchCase: '<S37>/Switch Case' */
      if (FMS_DW.SwitchCase_ActiveSubsystem_i == 1) {
        /* Disable for Resettable SubSystem: '<S43>/Mission_SubSystem' */
        /* SwitchCase: '<S88>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_a = -1;

        /* SwitchCase: '<S78>/Switch Case' */
        FMS_DW.SwitchCase_ActiveSubsystem_e = -1;

        /* End of Disable for SubSystem: '<S43>/Mission_SubSystem' */
      }

      /* SwitchCase: '<S37>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_i = -1;
      break;

     case 2:
      /* SwitchCase: '<S264>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_p = -1;

      /* SwitchCase: '<S252>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_bn = -1;
      break;

     case 3:
      /* SwitchCase: '<S235>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_l = -1;

      /* SwitchCase: '<S211>/Switch Case' */
      FMS_DW.SwitchCase_ActiveSubsystem_o = -1;

      /* SwitchCase: '<S222>/Switch Case' */
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
    FMS_Y.FMS_Out.actuator_cmd[0] = 0U;
    FMS_Y.FMS_Out.actuator_cmd[1] = 0U;
    FMS_Y.FMS_Out.actuator_cmd[2] = 0U;
    FMS_Y.FMS_Out.actuator_cmd[3] = 0U;
    for (i = 0; i < 12; i++) {
      FMS_Y.FMS_Out.actuator_cmd[i + 4] = 0U;
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
          switch (FMS_DW.SwitchCase_ActiveSubsystem_on) {
           case 0:
           case 1:
           case 4:
            break;

           case 2:
            /* SwitchCase: '<S361>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

            /* SwitchCase: '<S351>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;
            break;

           case 3:
            /* SwitchCase: '<S307>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

            /* SwitchCase: '<S285>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

            /* SwitchCase: '<S295>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;
            break;
          }

          /* SwitchCase: '<S41>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_on = -1;
          break;

         case 1:
          /* Disable for SwitchCase: '<S37>/Switch Case' */
          if (FMS_DW.SwitchCase_ActiveSubsystem_i == 1) {
            /* Disable for Resettable SubSystem: '<S43>/Mission_SubSystem' */
            /* SwitchCase: '<S88>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_a = -1;

            /* SwitchCase: '<S78>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_e = -1;

            /* End of Disable for SubSystem: '<S43>/Mission_SubSystem' */
          }

          /* SwitchCase: '<S37>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_i = -1;
          break;

         case 2:
          /* SwitchCase: '<S264>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_p = -1;

          /* SwitchCase: '<S252>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_bn = -1;
          break;

         case 3:
          /* SwitchCase: '<S235>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_l = -1;

          /* SwitchCase: '<S211>/Switch Case' */
          FMS_DW.SwitchCase_ActiveSubsystem_o = -1;

          /* SwitchCase: '<S222>/Switch Case' */
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
         *  Math: '<S348>/Square'
         *  Math: '<S383>/Math Function'
         *  Outport: '<Root>/FMS_Out'
         *  Product: '<S342>/Divide'
         *  Product: '<S385>/Divide'
         *  Product: '<S386>/Divide'
         *  Sum: '<S343>/Sum'
         *  Sum: '<S346>/Subtract'
         */
        rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_on;

        /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
        switch (FMS_B.state) {
         case VehicleState_Takeoff:
          FMS_DW.SwitchCase_ActiveSubsystem_on = 0;
          break;

         case VehicleState_Land:
          FMS_DW.SwitchCase_ActiveSubsystem_on = 1;
          break;

         case VehicleState_Return:
          FMS_DW.SwitchCase_ActiveSubsystem_on = 2;
          break;

         case VehicleState_Hold:
          FMS_DW.SwitchCase_ActiveSubsystem_on = 3;
          break;

         default:
          FMS_DW.SwitchCase_ActiveSubsystem_on = 4;
          break;
        }

        /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
        if (rtPrevAction != FMS_DW.SwitchCase_ActiveSubsystem_on) {
          switch (rtPrevAction) {
           case 0:
           case 1:
           case 4:
            break;

           case 2:
            /* SwitchCase: '<S361>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

            /* SwitchCase: '<S351>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;
            break;

           case 3:
            /* SwitchCase: '<S307>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

            /* SwitchCase: '<S285>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

            /* SwitchCase: '<S295>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;
            break;
          }
        }

        switch (FMS_DW.SwitchCase_ActiveSubsystem_on) {
         case 0:
          /* Outputs for IfAction SubSystem: '<S41>/Takeoff' incorporates:
           *  ActionPort: '<S280>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Product: '<S395>/Divide' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           *  Sum: '<S395>/Sum1'
           *  Sum: '<S395>/Sum2'
           */
          rtb_Divide_o_idx_1 = 1.0F / (FMS_B.Cmd_In.sp_waypoint[2] -
            FMS_B.Cmd_In.cur_waypoint[2]) * (FMS_U.INS_Out.h_R -
            FMS_B.Cmd_In.cur_waypoint[2]);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Saturate: '<S395>/Saturation' */
          if (rtb_Divide_o_idx_1 > 1.0F) {
            rtb_Divide_o_idx_1 = 1.0F;
          } else if (rtb_Divide_o_idx_1 < 0.0F) {
            rtb_Divide_o_idx_1 = 0.0F;
          }

          /* End of Saturate: '<S395>/Saturation' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S396>/Trigonometric Function1' incorporates:
           *  Gain: '<S394>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S396>/Trigonometric Function3'
           */
          rtb_Square2 = arm_cos_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[0] = rtb_Square2;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S396>/Trigonometric Function' incorporates:
           *  Gain: '<S394>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S396>/Trigonometric Function2'
           */
          rtb_Divide_o_idx_0 = arm_sin_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[1] = rtb_Divide_o_idx_0;

          /* SignalConversion generated from: '<S396>/Vector Concatenate1' incorporates:
           *  Constant: '<S396>/Constant3'
           */
          rtb_Transpose[2] = 0.0F;

          /* Gain: '<S396>/Gain' */
          rtb_Transpose[3] = -rtb_Divide_o_idx_0;

          /* Trigonometry: '<S396>/Trigonometric Function3' */
          rtb_Transpose[4] = rtb_Square2;

          /* SignalConversion generated from: '<S396>/Vector Concatenate2' incorporates:
           *  Constant: '<S396>/Constant4'
           */
          rtb_Transpose[5] = 0.0F;

          /* SignalConversion generated from: '<S396>/Vector Concatenate' incorporates:
           *  Concatenate: '<S396>/Vector Concatenate3'
           */
          rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_pk[0];
          rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_pk[1];
          rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_pk[2];

          /* Saturate: '<S392>/Saturation1' */
          rtb_Square2 = -FMS_PARAM.VEL_XY_LIM / 5.0F;
          rtb_Divide_o_idx_2 = FMS_PARAM.VEL_XY_LIM / 5.0F;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Product: '<S392>/Multiply' incorporates:
           *  Concatenate: '<S396>/Vector Concatenate'
           *  Inport: '<Root>/INS_Out'
           *  Product: '<S395>/Multiply'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           *  Sum: '<S392>/Sum'
           *  Sum: '<S395>/Sum3'
           *  Sum: '<S395>/Sum4'
           */
          rtb_Divide_o_idx_0 = ((FMS_B.Cmd_In.sp_waypoint[0] -
            FMS_B.Cmd_In.cur_waypoint[0]) * rtb_Divide_o_idx_1 +
                                FMS_B.Cmd_In.cur_waypoint[0]) -
            FMS_U.INS_Out.x_R;
          rtb_Divide_o_idx_1 = ((FMS_B.Cmd_In.sp_waypoint[1] -
            FMS_B.Cmd_In.cur_waypoint[1]) * rtb_Divide_o_idx_1 +
                                FMS_B.Cmd_In.cur_waypoint[1]) -
            FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          for (i = 0; i < 3; i++) {
            rtb_Transpose_0[i] = rtb_Transpose[i + 3] * rtb_Divide_o_idx_1 +
              rtb_Transpose[i] * rtb_Divide_o_idx_0;
          }

          /* End of Product: '<S392>/Multiply' */

          /* Saturate: '<S392>/Saturation1' incorporates:
           *  Gain: '<S392>/Gain2'
           */
          rtb_Divide_o_idx_1 = FMS_PARAM.XY_P * rtb_Transpose_0[0];
          rtb_Divide_o_idx_0 = FMS_PARAM.XY_P * rtb_Transpose_0[1];

          /* End of Outputs for SubSystem: '<S41>/Takeoff' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Takeoff' incorporates:
           *  ActionPort: '<S280>/Action Port'
           */
          /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S280>/Constant'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_ge;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_cc;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_b0;
          FMS_Y.FMS_Out.psi_rate_cmd = 0.0F;

          /* Saturate: '<S392>/Saturation1' */
          if (rtb_Divide_o_idx_1 > rtb_Divide_o_idx_2) {
            /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_2;
          } else if (rtb_Divide_o_idx_1 < rtb_Square2) {
            /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Square2;
          } else {
            /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_1;
          }

          if (rtb_Divide_o_idx_0 > rtb_Divide_o_idx_2) {
            /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_2;
          } else if (rtb_Divide_o_idx_0 < rtb_Square2) {
            /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Square2;
          } else {
            /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_0;
          }

          /* BusAssignment: '<S280>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S280>/Constant4'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.w_cmd = 0.0F;

          /* End of Outputs for SubSystem: '<S41>/Takeoff' */
          break;

         case 1:
          /* Outputs for IfAction SubSystem: '<S41>/Land' incorporates:
           *  ActionPort: '<S278>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S324>/Trigonometric Function1' incorporates:
           *  Gain: '<S323>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S324>/Trigonometric Function3'
           */
          rtb_Square2 = arm_cos_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[0] = rtb_Square2;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Trigonometry: '<S324>/Trigonometric Function' incorporates:
           *  Gain: '<S323>/Gain'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Trigonometry: '<S324>/Trigonometric Function2'
           */
          rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_Transpose[1] = rtb_Divide_o_idx_1;

          /* SignalConversion generated from: '<S324>/Vector Concatenate1' incorporates:
           *  Constant: '<S324>/Constant3'
           */
          rtb_Transpose[2] = 0.0F;

          /* Gain: '<S324>/Gain' */
          rtb_Transpose[3] = -rtb_Divide_o_idx_1;

          /* Trigonometry: '<S324>/Trigonometric Function3' */
          rtb_Transpose[4] = rtb_Square2;

          /* SignalConversion generated from: '<S324>/Vector Concatenate2' incorporates:
           *  Constant: '<S324>/Constant4'
           */
          rtb_Transpose[5] = 0.0F;

          /* SignalConversion generated from: '<S324>/Vector Concatenate' incorporates:
           *  Concatenate: '<S324>/Vector Concatenate3'
           */
          rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_n5[0];
          rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_n5[1];
          rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_n5[2];

          /* Saturate: '<S320>/Saturation1' */
          rtb_Square2 = -FMS_PARAM.VEL_XY_LIM / 5.0F;
          rtb_Divide_o_idx_2 = FMS_PARAM.VEL_XY_LIM / 5.0F;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* SignalConversion generated from: '<S321>/Multiply' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           *  Sum: '<S321>/Sum'
           */
          rtb_Divide_o_idx_0 = FMS_B.Cmd_In.sp_waypoint[0] - FMS_U.INS_Out.x_R;
          rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[1] - FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Product: '<S321>/Multiply' incorporates:
           *  Concatenate: '<S324>/Vector Concatenate'
           */
          for (i = 0; i < 3; i++) {
            rtb_Transpose_0[i] = rtb_Transpose[i + 3] * rtb_Divide_o_idx_1 +
              rtb_Transpose[i] * rtb_Divide_o_idx_0;
          }

          /* End of Product: '<S321>/Multiply' */

          /* Saturate: '<S320>/Saturation1' incorporates:
           *  Gain: '<S321>/Gain2'
           */
          rtb_Divide_o_idx_1 = FMS_PARAM.XY_P * rtb_Transpose_0[0];
          rtb_Divide_o_idx_0 = FMS_PARAM.XY_P * rtb_Transpose_0[1];

          /* End of Outputs for SubSystem: '<S41>/Land' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Land' incorporates:
           *  ActionPort: '<S278>/Action Port'
           */
          /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S278>/Constant'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_p;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_iv;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_bf;
          FMS_Y.FMS_Out.psi_rate_cmd = 0.0F;

          /* Saturate: '<S320>/Saturation1' */
          if (rtb_Divide_o_idx_1 > rtb_Divide_o_idx_2) {
            /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_2;
          } else if (rtb_Divide_o_idx_1 < rtb_Square2) {
            /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Square2;
          } else {
            /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_1;
          }

          if (rtb_Divide_o_idx_0 > rtb_Divide_o_idx_2) {
            /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_2;
          } else if (rtb_Divide_o_idx_0 < rtb_Square2) {
            /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Square2;
          } else {
            /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = rtb_Divide_o_idx_0;
          }

          /* BusAssignment: '<S278>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S278>/Constant4'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.w_cmd = 0.5F;

          /* End of Outputs for SubSystem: '<S41>/Land' */
          break;

         case 2:
          if (FMS_DW.SwitchCase_ActiveSubsystem_on != rtPrevAction) {
            /* InitializeConditions for IfAction SubSystem: '<S41>/Return' incorporates:
             *  ActionPort: '<S279>/Action Port'
             */
            /* InitializeConditions for SwitchCase: '<S41>/Switch Case' incorporates:
             *  Delay: '<S327>/Delay'
             *  Delay: '<S328>/Delay'
             *  Delay: '<S347>/Delay'
             *  DiscreteIntegrator: '<S331>/Integrator'
             *  DiscreteIntegrator: '<S331>/Integrator1'
             *  DiscreteIntegrator: '<S388>/Discrete-Time Integrator'
             */
            FMS_DW.icLoad_h = true;
            FMS_DW.l1_heading_a = 0.0F;
            FMS_DW.icLoad_j = true;
            FMS_DW.icLoad_c = true;
            FMS_DW.Integrator1_IC_LOADING_o = 1U;
            FMS_DW.Integrator_DSTATE_j = 0.0F;

            /* End of InitializeConditions for SubSystem: '<S41>/Return' */

            /* SystemReset for IfAction SubSystem: '<S41>/Return' incorporates:
             *  ActionPort: '<S279>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S41>/Switch Case' incorporates:
             *  Chart: '<S352>/Motion Status'
             *  Chart: '<S362>/Motion State'
             */
            FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState);
            FMS_MotionStatus_Reset(&rtb_state_ee, &FMS_DW.sf_MotionStatus);

            /* End of SystemReset for SubSystem: '<S41>/Return' */
          }

          /* Outputs for IfAction SubSystem: '<S41>/Return' incorporates:
           *  ActionPort: '<S279>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* SignalConversion generated from: '<S327>/Delay' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          rtb_Saturation1_g[0] = FMS_U.INS_Out.x_R;
          rtb_Saturation1_g[1] = FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Delay: '<S347>/Delay' incorporates:
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
          /* Sum: '<S343>/Sum' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          tmp_2 = FMS_U.INS_Out.x_R - FMS_B.Cmd_In.sp_waypoint[0];

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_TmpSignalConversionAtSqua_d[0] = tmp_2 * tmp_2;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S343>/Sum' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S348>/Square'
           *  Product: '<S385>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          tmp_2 = FMS_U.INS_Out.y_R - FMS_B.Cmd_In.sp_waypoint[1];

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Sqrt: '<S348>/Sqrt' incorporates:
           *  Math: '<S348>/Square'
           *  Sum: '<S348>/Sum of Elements'
           */
          rtb_Square2 = sqrtf(tmp_2 * tmp_2 + rtb_TmpSignalConversionAtSqua_d[0]);

          /* Switch: '<S343>/Switch' incorporates:
           *  Constant: '<S343>/vel'
           */
          if (rtb_Square2 > FMS_PARAM.L1) {
            rtb_Switch_k = FMS_PARAM.CRUISE_SPEED;
          } else {
            /* Gain: '<S343>/Gain' */
            rtb_Switch_k = 0.5F * rtb_Square2;

            /* Saturate: '<S343>/Saturation' */
            if (rtb_Switch_k > FMS_PARAM.CRUISE_SPEED) {
              rtb_Switch_k = FMS_PARAM.CRUISE_SPEED;
            } else if (rtb_Switch_k < 0.5F) {
              rtb_Switch_k = 0.5F;
            }

            /* End of Saturate: '<S343>/Saturation' */
          }

          /* End of Switch: '<S343>/Switch' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S362>/Motion State' incorporates:
           *  Constant: '<S362>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S362>/Square'
           *  Math: '<S362>/Square1'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sqrt: '<S362>/Sqrt'
           *  Sum: '<S362>/Add'
           */
          FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
            FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                          &FMS_DW.sf_MotionState);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S361>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S361>/Hold Control' incorporates:
               *  ActionPort: '<S364>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S361>/Switch Case' */
              FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_g);

              /* End of SystemReset for SubSystem: '<S361>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S361>/Hold Control' incorporates:
             *  ActionPort: '<S364>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                              FMS_U.INS_Out.psi, FMS_B.Merge_f,
                              &FMS_ConstB.HoldControl_g, &FMS_DW.HoldControl_g);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S361>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S361>/Brake Control' incorporates:
             *  ActionPort: '<S363>/Action Port'
             */
            FMS_BrakeControl_h(FMS_B.Merge_f);

            /* End of Outputs for SubSystem: '<S361>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_c != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S361>/Move Control' incorporates:
               *  ActionPort: '<S365>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S361>/Switch Case' */
              FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_c);

              /* End of SystemReset for SubSystem: '<S361>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S361>/Move Control' incorporates:
             *  ActionPort: '<S365>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                              FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_f,
                              &FMS_ConstB.MoveControl_c, &FMS_DW.MoveControl_c);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S361>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S352>/Motion Status' incorporates:
           *  Abs: '<S352>/Abs'
           *  Constant: '<S352>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          FMS_MotionStatus(0.0F, fabsf(FMS_U.INS_Out.vd), &rtb_state_ee,
                           &FMS_DW.sf_MotionStatus);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S351>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S351>/Hold Control' incorporates:
               *  ActionPort: '<S354>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S351>/Switch Case' */
              FMS_HoldControl_Reset(&FMS_DW.HoldControl);

              /* End of SystemReset for SubSystem: '<S351>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S351>/Hold Control' incorporates:
             *  ActionPort: '<S354>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl(FMS_U.INS_Out.h_R, &FMS_B.Merge_pd,
                            &FMS_DW.HoldControl);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S351>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S351>/Brake Control' incorporates:
             *  ActionPort: '<S353>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_pd);

            /* End of Outputs for SubSystem: '<S351>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_i5 != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S351>/Move Control' incorporates:
               *  ActionPort: '<S355>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S351>/Switch Case' */
              FMS_MoveControl_Reset(&FMS_DW.MoveControl);

              /* End of SystemReset for SubSystem: '<S351>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S351>/Move Control' incorporates:
             *  ActionPort: '<S355>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl(FMS_U.Pilot_Cmd.stick_throttle, &FMS_B.Merge_pd,
                            &FMS_ConstB.MoveControl, &FMS_DW.MoveControl);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S351>/Move Control' */
            break;
          }

          /* Delay: '<S327>/Delay' incorporates:
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
          /* Sum: '<S279>/Sum' incorporates:
           *  Delay: '<S327>/Delay'
           *  Product: '<S385>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          rtb_TmpSignalConversionAtSqua_d[0] = FMS_B.Cmd_In.sp_waypoint[0] -
            FMS_DW.Delay_DSTATE_d[0];
          rtb_TmpSignalConversionAtSqua_d[1] = FMS_B.Cmd_In.sp_waypoint[1] -
            FMS_DW.Delay_DSTATE_d[1];

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Math: '<S342>/Math Function' incorporates:
           *  SignalConversion generated from: '<S342>/Math Function'
           */
          rtb_MathFunction_ec[0] = rtb_TmpSignalConversionAtSqua_d[1] *
            rtb_TmpSignalConversionAtSqua_d[1];
          rtb_MathFunction_ec[1] = rtb_TmpSignalConversionAtSqua_d[0] *
            rtb_TmpSignalConversionAtSqua_d[0];

          /* Sum: '<S342>/Sum of Elements' */
          rtb_Square2 = rtb_MathFunction_ec[0] + rtb_MathFunction_ec[1];

          /* Math: '<S342>/Math Function1' incorporates:
           *  Sum: '<S342>/Sum of Elements'
           *
           * About '<S342>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Square2 < 0.0F) {
            rtb_a_k = -sqrtf(fabsf(rtb_Square2));
          } else {
            rtb_a_k = sqrtf(rtb_Square2);
          }

          /* End of Math: '<S342>/Math Function1' */

          /* Switch: '<S342>/Switch' incorporates:
           *  Constant: '<S342>/Constant'
           *  Product: '<S342>/Product'
           */
          if (rtb_a_k > 0.0F) {
            rtb_MatrixConcatenate3[0] = rtb_TmpSignalConversionAtSqua_d[1];
            rtb_MatrixConcatenate3[1] = rtb_TmpSignalConversionAtSqua_d[0];
            rtb_MatrixConcatenate3[2] = rtb_a_k;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S342>/Switch' */

          /* Product: '<S342>/Divide' */
          tmp_2 = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S329>/Dot Product' incorporates:
           *  Product: '<S341>/Divide'
           */
          rtb_Square2 = FMS_ConstB.Divide_o[0] * tmp_2;
          rtb_TmpSignalConversionAtSqua_d[0] = tmp_2;

          /* Product: '<S342>/Divide' */
          tmp_2 = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S329>/Dot Product' incorporates:
           *  Product: '<S341>/Divide'
           */
          rtb_Divide_o_idx_1 = FMS_ConstB.Divide_o[1] * tmp_2 + rtb_Square2;

          /* Sum: '<S340>/Subtract' incorporates:
           *  Product: '<S340>/Multiply'
           *  Product: '<S340>/Multiply1'
           */
          rtb_Square2 = rtb_TmpSignalConversionAtSqua_d[0] *
            FMS_ConstB.Divide_o[1] - FMS_ConstB.Divide_o[0] * tmp_2;

          /* Signum: '<S329>/Sign1' */
          if (rtb_Square2 < 0.0F) {
            rtb_a_k = -1.0F;
          } else {
            rtb_a_k = (real32_T)(rtb_Square2 > 0.0F);
          }

          /* End of Signum: '<S329>/Sign1' */

          /* Trigonometry: '<S329>/Acos' incorporates:
           *  DotProduct: '<S329>/Dot Product'
           */
          if (rtb_Divide_o_idx_1 > 1.0F) {
            rtb_Divide_o_idx_1 = 1.0F;
          } else if (rtb_Divide_o_idx_1 < -1.0F) {
            rtb_Divide_o_idx_1 = -1.0F;
          }

          /* Switch: '<S329>/Switch2' incorporates:
           *  Constant: '<S329>/Constant4'
           */
          if (rtb_a_k == 0.0F) {
            rtb_a_k = 1.0F;
          }

          /* Product: '<S329>/Multiply' incorporates:
           *  Switch: '<S329>/Switch2'
           *  Trigonometry: '<S329>/Acos'
           */
          rtb_a_k *= acosf(rtb_Divide_o_idx_1);

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Math: '<S333>/Rem' incorporates:
           *  Constant: '<S333>/Constant1'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S328>/Sum1'
           */
          rtb_Divide_o_idx_1 = rt_remf(rtb_a_k - FMS_U.INS_Out.psi, 6.28318548F);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S333>/Switch' incorporates:
           *  Abs: '<S333>/Abs'
           *  Constant: '<S333>/Constant'
           *  Constant: '<S339>/Constant'
           *  Product: '<S333>/Multiply'
           *  RelationalOperator: '<S339>/Compare'
           *  Signum: '<S333>/Sign'
           *  Sum: '<S333>/Add'
           */
          if (fabsf(rtb_Divide_o_idx_1) > 3.14159274F) {
            /* Signum: '<S333>/Sign' */
            if (rtb_Divide_o_idx_1 < 0.0F) {
              rtb_Square2 = -1.0F;
            } else {
              rtb_Square2 = (real32_T)(rtb_Divide_o_idx_1 > 0.0F);
            }

            rtb_Divide_o_idx_1 -= 6.28318548F * rtb_Square2;
          }

          /* End of Switch: '<S333>/Switch' */

          /* Abs: '<S326>/Abs' */
          rtb_Divide_o_idx_1 = fabsf(rtb_Divide_o_idx_1);

          /* Switch: '<S326>/Switch' incorporates:
           *  Concatenate: '<S391>/Vector Concatenate'
           *  Product: '<S347>/Multiply'
           *  Sum: '<S347>/Sum'
           */
          if (rtb_Divide_o_idx_1 > 0.34906584F) {
            /* Saturate: '<S361>/Saturation1' incorporates:
             *  Merge: '<S361>/Merge'
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

            /* End of Saturate: '<S361>/Saturation1' */

            /* Saturate: '<S351>/Saturation1' */
            if (FMS_B.Merge_pd > FMS_PARAM.VEL_Z_LIM) {
              rtb_MatrixConcatenate3[2] = FMS_PARAM.VEL_Z_LIM;
            } else if (FMS_B.Merge_pd < -FMS_PARAM.VEL_Z_LIM) {
              rtb_MatrixConcatenate3[2] = -FMS_PARAM.VEL_Z_LIM;
            } else {
              rtb_MatrixConcatenate3[2] = FMS_B.Merge_pd;
            }

            /* End of Saturate: '<S351>/Saturation1' */
          } else {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            /* Sum: '<S347>/Sum' incorporates:
             *  Delay: '<S347>/Delay'
             *  SignalConversion generated from: '<S32>/Signal Copy3'
             */
            rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[0] -
              FMS_DW.Delay_DSTATE_p[0];

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

            /* SignalConversion generated from: '<S389>/Math Function' */
            rtb_MatrixConcatenate3[0] = rtb_Divide_o_idx_1;
            rtb_TmpSignalConversionAtMath_j[0] = rtb_Divide_o_idx_1;

            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            /* Sum: '<S347>/Sum' incorporates:
             *  Delay: '<S347>/Delay'
             *  SignalConversion generated from: '<S32>/Signal Copy3'
             */
            rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[1] -
              FMS_DW.Delay_DSTATE_p[1];

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

            /* SignalConversion generated from: '<S391>/Vector Concatenate2' incorporates:
             *  Constant: '<S391>/Constant4'
             */
            rtb_Transpose[5] = 0.0F;

            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            /* Gain: '<S390>/Gain' incorporates:
             *  DiscreteIntegrator: '<S388>/Discrete-Time Integrator'
             *  Inport: '<Root>/INS_Out'
             *  SignalConversion generated from: '<S32>/Signal Copy1'
             *  Sum: '<S388>/Add'
             */
            rtb_Square2 = -(FMS_U.INS_Out.psi - FMS_DW.l1_heading_a);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

            /* Trigonometry: '<S391>/Trigonometric Function3' incorporates:
             *  Trigonometry: '<S391>/Trigonometric Function1'
             */
            rtb_Divide_o_idx_0 = arm_cos_f32(rtb_Square2);
            rtb_Transpose[4] = rtb_Divide_o_idx_0;

            /* Trigonometry: '<S391>/Trigonometric Function2' incorporates:
             *  Trigonometry: '<S391>/Trigonometric Function'
             */
            rtb_Square2 = arm_sin_f32(rtb_Square2);

            /* Gain: '<S391>/Gain' incorporates:
             *  Trigonometry: '<S391>/Trigonometric Function2'
             */
            rtb_Transpose[3] = -rtb_Square2;

            /* SignalConversion generated from: '<S391>/Vector Concatenate1' incorporates:
             *  Constant: '<S391>/Constant3'
             */
            rtb_Transpose[2] = 0.0F;

            /* Trigonometry: '<S391>/Trigonometric Function' */
            rtb_Transpose[1] = rtb_Square2;

            /* Trigonometry: '<S391>/Trigonometric Function1' */
            rtb_Transpose[0] = rtb_Divide_o_idx_0;

            /* SignalConversion generated from: '<S391>/Vector Concatenate' incorporates:
             *  Concatenate: '<S391>/Vector Concatenate3'
             */
            rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_p[0];
            rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_p[1];
            rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_p[2];

            /* Sum: '<S389>/Sum of Elements' incorporates:
             *  Math: '<S389>/Math Function'
             *  SignalConversion generated from: '<S389>/Math Function'
             */
            rtb_Square2 = rtb_MatrixConcatenate3[0] * rtb_MatrixConcatenate3[0]
              + rtb_Divide_o_idx_1 * rtb_Divide_o_idx_1;

            /* Math: '<S389>/Math Function1' incorporates:
             *  Sum: '<S389>/Sum of Elements'
             *
             * About '<S389>/Math Function1':
             *  Operator: sqrt
             */
            if (rtb_Square2 < 0.0F) {
              rtb_Square2 = -sqrtf(fabsf(rtb_Square2));
            } else {
              rtb_Square2 = sqrtf(rtb_Square2);
            }

            /* End of Math: '<S389>/Math Function1' */

            /* Switch: '<S389>/Switch' incorporates:
             *  Constant: '<S389>/Constant'
             *  Product: '<S389>/Product'
             */
            if (rtb_Square2 > 0.0F) {
              rtb_Divide_o_idx_0 = rtb_TmpSignalConversionAtMath_j[0];
            } else {
              rtb_Divide_o_idx_0 = 0.0F;
              rtb_Divide_o_idx_1 = 0.0F;
              rtb_Square2 = 1.0F;
            }

            /* End of Switch: '<S389>/Switch' */

            /* Product: '<S387>/Multiply2' incorporates:
             *  Product: '<S389>/Divide'
             */
            rtb_Divide_o_idx_0 = rtb_Divide_o_idx_0 / rtb_Square2 * rtb_Switch_k;
            rtb_Divide_o_idx_1 = rtb_Divide_o_idx_1 / rtb_Square2 * rtb_Switch_k;
            for (i = 0; i < 3; i++) {
              rtb_MatrixConcatenate3[i] = rtb_Transpose[i + 3] *
                rtb_Divide_o_idx_1 + rtb_Transpose[i] * rtb_Divide_o_idx_0;
            }
          }

          /* End of Switch: '<S326>/Switch' */

          /* Delay: '<S328>/Delay' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.icLoad_c) {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_DW.Delay_DSTATE_do = FMS_U.INS_Out.psi;

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          }

          /* DiscreteIntegrator: '<S331>/Integrator1' incorporates:
           *  Delay: '<S328>/Delay'
           */
          if (FMS_DW.Integrator1_IC_LOADING_o != 0) {
            FMS_DW.Integrator1_DSTATE_e = FMS_DW.Delay_DSTATE_do;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Math: '<S335>/Rem' incorporates:
           *  Constant: '<S335>/Constant1'
           *  DiscreteIntegrator: '<S331>/Integrator1'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S330>/Sum'
           */
          rtb_Divide_o_idx_1 = rt_remf(FMS_DW.Integrator1_DSTATE_e -
            FMS_U.INS_Out.psi, 6.28318548F);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S335>/Switch' incorporates:
           *  Abs: '<S335>/Abs'
           *  Constant: '<S335>/Constant'
           *  Constant: '<S336>/Constant'
           *  Product: '<S335>/Multiply'
           *  RelationalOperator: '<S336>/Compare'
           *  Signum: '<S335>/Sign'
           *  Sum: '<S335>/Add'
           */
          if (fabsf(rtb_Divide_o_idx_1) > 3.14159274F) {
            /* Signum: '<S335>/Sign' */
            if (rtb_Divide_o_idx_1 < 0.0F) {
              rtb_Square2 = -1.0F;
            } else {
              rtb_Square2 = (real32_T)(rtb_Divide_o_idx_1 > 0.0F);
            }

            rtb_Divide_o_idx_1 -= 6.28318548F * rtb_Square2;
          }

          /* End of Switch: '<S335>/Switch' */

          /* Gain: '<S330>/Gain2' */
          rtb_Divide_o_idx_1 *= FMS_PARAM.YAW_P;

          /* End of Outputs for SubSystem: '<S41>/Return' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Return' incorporates:
           *  ActionPort: '<S279>/Action Port'
           */
          /* BusAssignment: '<S279>/Bus Assignment1' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_k;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_h;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_m;
          FMS_Y.FMS_Out.u_cmd = rtb_MatrixConcatenate3[0];
          FMS_Y.FMS_Out.v_cmd = rtb_MatrixConcatenate3[1];
          FMS_Y.FMS_Out.w_cmd = rtb_MatrixConcatenate3[2];

          /* Saturate: '<S330>/Saturation' */
          if (rtb_Divide_o_idx_1 > FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S279>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
          } else if (rtb_Divide_o_idx_1 < -FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S279>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
          } else {
            /* BusAssignment: '<S279>/Bus Assignment1' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = rtb_Divide_o_idx_1;
          }

          /* End of Saturate: '<S330>/Saturation' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S382>/Sum of Elements' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S382>/Math Function'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sum: '<S380>/Sum of Elements'
           */
          rtb_Square2 = FMS_U.INS_Out.vn * FMS_U.INS_Out.vn + FMS_U.INS_Out.ve *
            FMS_U.INS_Out.ve;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Math: '<S382>/Math Function1' incorporates:
           *  Sum: '<S382>/Sum of Elements'
           *
           * About '<S382>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Square2 < 0.0F) {
            rtb_Divide_o_idx_1 = -sqrtf(fabsf(rtb_Square2));
          } else {
            rtb_Divide_o_idx_1 = sqrtf(rtb_Square2);
          }

          /* End of Math: '<S382>/Math Function1' */

          /* Switch: '<S382>/Switch' incorporates:
           *  Constant: '<S382>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  Product: '<S382>/Product'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (rtb_Divide_o_idx_1 > 0.0F) {
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            rtb_MatrixConcatenate3[0] = FMS_U.INS_Out.vn;
            rtb_MatrixConcatenate3[1] = FMS_U.INS_Out.ve;

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            rtb_MatrixConcatenate3[2] = rtb_Divide_o_idx_1;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S382>/Switch' */

          /* Product: '<S382>/Divide' */
          rtb_TmpSignalConversionAtSqua_d[0] = rtb_MatrixConcatenate3[0] /
            rtb_MatrixConcatenate3[2];
          rtb_TmpSignalConversionAtSqua_d[1] = rtb_MatrixConcatenate3[1] /
            rtb_MatrixConcatenate3[2];

          /* SignalConversion generated from: '<S385>/Math Function' */
          rtb_MathFunction_ec[0] = rtb_TmpSignalConversionAtSqua_d[1];
          rtb_MathFunction_ec[1] = rtb_TmpSignalConversionAtSqua_d[0];

          /* Math: '<S385>/Math Function' incorporates:
           *  SignalConversion generated from: '<S385>/Math Function'
           */
          rtb_MathFunction_o[0] = rtb_TmpSignalConversionAtSqua_d[1] *
            rtb_TmpSignalConversionAtSqua_d[1];
          rtb_MathFunction_o[1] = rtb_TmpSignalConversionAtSqua_d[0] *
            rtb_TmpSignalConversionAtSqua_d[0];

          /* Sum: '<S385>/Sum of Elements' */
          rtb_Divide_o_idx_2 = rtb_MathFunction_o[0] + rtb_MathFunction_o[1];

          /* Math: '<S385>/Math Function1' incorporates:
           *  Sum: '<S385>/Sum of Elements'
           *
           * About '<S385>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_2 < 0.0F) {
            rtb_Divide_o_idx_1 = -sqrtf(fabsf(rtb_Divide_o_idx_2));
          } else {
            rtb_Divide_o_idx_1 = sqrtf(rtb_Divide_o_idx_2);
          }

          /* End of Math: '<S385>/Math Function1' */

          /* Switch: '<S385>/Switch' incorporates:
           *  Constant: '<S385>/Constant'
           *  Product: '<S385>/Product'
           */
          if (rtb_Divide_o_idx_1 > 0.0F) {
            rtb_MatrixConcatenate3[0] = rtb_TmpSignalConversionAtSqua_d[1];
            rtb_MatrixConcatenate3[1] = rtb_TmpSignalConversionAtSqua_d[0];
            rtb_MatrixConcatenate3[2] = rtb_Divide_o_idx_1;
          } else {
            rtb_MatrixConcatenate3[0] = 0.0F;
            rtb_MatrixConcatenate3[1] = 0.0F;
            rtb_MatrixConcatenate3[2] = 1.0F;
          }

          /* End of Switch: '<S385>/Switch' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* MATLAB Function: '<S345>/NearbyRefWP' incorporates:
           *  Constant: '<S279>/L1'
           *  Reshape: '<S327>/Reshape2'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          FMS_NearbyRefWP(&FMS_B.Cmd_In.sp_waypoint[0], rtb_Saturation1_g,
                          FMS_PARAM.L1, rtb_MathFunction_ec, &rtb_Rem_i);

          /* MATLAB Function: '<S345>/SearchL1RefWP' incorporates:
           *  Constant: '<S279>/L1'
           *  Delay: '<S327>/Delay'
           *  Reshape: '<S327>/Reshape2'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          FMS_SearchL1RefWP(FMS_DW.Delay_DSTATE_d, &FMS_B.Cmd_In.sp_waypoint[0],
                            rtb_Saturation1_g, FMS_PARAM.L1,
                            rtb_TmpSignalConversionAtSqua_d, &rtb_Divide_o_idx_1);

          /* MATLAB Function: '<S345>/OutRegionRegWP' incorporates:
           *  Delay: '<S327>/Delay'
           *  Reshape: '<S327>/Reshape2'
           *  SignalConversion generated from: '<S32>/Signal Copy3'
           */
          FMS_OutRegionRegWP(FMS_DW.Delay_DSTATE_d, &FMS_B.Cmd_In.sp_waypoint[0],
                             rtb_Saturation1_g, rtb_MathFunction_o);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Switch: '<S345>/Switch1' incorporates:
           *  Constant: '<S374>/Constant'
           *  Constant: '<S375>/Constant'
           *  Product: '<S385>/Divide'
           *  RelationalOperator: '<S374>/Compare'
           *  RelationalOperator: '<S375>/Compare'
           *  Switch: '<S345>/Switch'
           */
          if (rtb_Rem_i > 0.0F) {
            rtb_TmpSignalConversionAtSqua_d[0] = rtb_MathFunction_ec[0];
            rtb_TmpSignalConversionAtSqua_d[1] = rtb_MathFunction_ec[1];
          } else if (rtb_Divide_o_idx_1 < 0.0F) {
            /* Product: '<S385>/Divide' incorporates:
             *  Switch: '<S345>/Switch'
             */
            rtb_TmpSignalConversionAtSqua_d[0] = rtb_MathFunction_o[0];
            rtb_TmpSignalConversionAtSqua_d[1] = rtb_MathFunction_o[1];
          }

          /* End of Switch: '<S345>/Switch1' */

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S346>/Subtract' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Product: '<S385>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          rtb_Divide_o_idx_0 = rtb_TmpSignalConversionAtSqua_d[0] -
            FMS_U.INS_Out.x_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          rtb_TmpSignalConversionAtSqua_d[0] = rtb_Divide_o_idx_0;
          rtb_Saturation1_g[0] = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_0;

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Sum: '<S346>/Subtract' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S383>/Math Function'
           *  Product: '<S385>/Divide'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          rtb_Divide_o_idx_0 = rtb_TmpSignalConversionAtSqua_d[1] -
            FMS_U.INS_Out.y_R;

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Sum: '<S383>/Sum of Elements' incorporates:
           *  Math: '<S383>/Math Function'
           *  Sum: '<S381>/Sum of Elements'
           */
          rtb_Divide_o_idx_2 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_0 +
            rtb_Saturation1_g[0];

          /* Math: '<S383>/Math Function1' incorporates:
           *  Sum: '<S383>/Sum of Elements'
           *
           * About '<S383>/Math Function1':
           *  Operator: sqrt
           */
          if (rtb_Divide_o_idx_2 < 0.0F) {
            rtb_Divide_o_idx_1 = -sqrtf(fabsf(rtb_Divide_o_idx_2));
          } else {
            rtb_Divide_o_idx_1 = sqrtf(rtb_Divide_o_idx_2);
          }

          /* End of Math: '<S383>/Math Function1' */

          /* Switch: '<S383>/Switch' incorporates:
           *  Constant: '<S383>/Constant'
           *  Product: '<S383>/Product'
           *  Switch: '<S386>/Switch'
           */
          if (rtb_Divide_o_idx_1 > 0.0F) {
            rtb_MathFunction_c_idx_0 = rtb_TmpSignalConversionAtSqua_d[0];
          } else {
            rtb_MathFunction_c_idx_0 = 0.0F;
            rtb_Divide_o_idx_0 = 0.0F;
            rtb_Divide_o_idx_1 = 1.0F;
          }

          /* End of Switch: '<S383>/Switch' */

          /* Product: '<S383>/Divide' incorporates:
           *  Product: '<S386>/Divide'
           */
          rtb_MathFunction_ec[0] = rtb_MathFunction_c_idx_0 / rtb_Divide_o_idx_1;
          rtb_MathFunction_ec[1] = rtb_Divide_o_idx_0 / rtb_Divide_o_idx_1;

          /* Sum: '<S386>/Sum of Elements' incorporates:
           *  Math: '<S386>/Math Function'
           *  SignalConversion generated from: '<S386>/Math Function'
           */
          tmp_2 = rtb_MathFunction_ec[1] * rtb_MathFunction_ec[1] +
            rtb_MathFunction_ec[0] * rtb_MathFunction_ec[0];

          /* Math: '<S386>/Math Function1' incorporates:
           *  Sum: '<S386>/Sum of Elements'
           *
           * About '<S386>/Math Function1':
           *  Operator: sqrt
           */
          if (tmp_2 < 0.0F) {
            rtb_Divide_o_idx_1 = -sqrtf(fabsf(tmp_2));
          } else {
            rtb_Divide_o_idx_1 = sqrtf(tmp_2);
          }

          /* End of Math: '<S386>/Math Function1' */

          /* Switch: '<S386>/Switch' incorporates:
           *  Constant: '<S386>/Constant'
           *  Product: '<S386>/Product'
           */
          if (rtb_Divide_o_idx_1 > 0.0F) {
            rtb_MathFunction_c_idx_0 = rtb_MathFunction_ec[1];
            rtb_Divide_o_idx_0 = rtb_MathFunction_ec[0];
          } else {
            rtb_MathFunction_c_idx_0 = 0.0F;
            rtb_Divide_o_idx_0 = 0.0F;
            rtb_Divide_o_idx_1 = 1.0F;
          }

          /* End of Switch: '<S386>/Switch' */

          /* Product: '<S386>/Divide' */
          rtb_MathFunction_c_idx_0 /= rtb_Divide_o_idx_1;

          /* Product: '<S385>/Divide' */
          tmp_2 = rtb_MatrixConcatenate3[0] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S379>/Dot Product' */
          rtb_Rem_i = tmp_2 * rtb_MathFunction_c_idx_0;
          rtb_MathFunction_ec[0] = rtb_MathFunction_c_idx_0;
          rtb_TmpSignalConversionAtSqua_d[0] = tmp_2;

          /* Product: '<S386>/Divide' incorporates:
           *  Product: '<S385>/Divide'
           */
          rtb_MathFunction_c_idx_0 = rtb_Divide_o_idx_0 / rtb_Divide_o_idx_1;

          /* Product: '<S385>/Divide' */
          tmp_2 = rtb_MatrixConcatenate3[1] / rtb_MatrixConcatenate3[2];

          /* DotProduct: '<S379>/Dot Product' */
          rtb_Rem_i += tmp_2 * rtb_MathFunction_c_idx_0;

          /* Sqrt: '<S380>/Sqrt' */
          rtb_Divide_o_idx_1 = sqrtf(rtb_Square2);

          /* Gain: '<S346>/Gain' incorporates:
           *  Math: '<S346>/Square'
           */
          rtb_Gain_fj = rtb_Divide_o_idx_1 * rtb_Divide_o_idx_1 * 2.0F;

          /* Sum: '<S384>/Subtract' incorporates:
           *  Product: '<S384>/Multiply'
           *  Product: '<S384>/Multiply1'
           */
          rtb_Square2 = rtb_MathFunction_ec[0] * tmp_2 -
            rtb_TmpSignalConversionAtSqua_d[0] * rtb_MathFunction_c_idx_0;

          /* Signum: '<S379>/Sign1' */
          if (rtb_Square2 < 0.0F) {
            rtb_Divide_o_idx_1 = -1.0F;
          } else {
            rtb_Divide_o_idx_1 = (real32_T)(rtb_Square2 > 0.0F);
          }

          /* End of Signum: '<S379>/Sign1' */

          /* Trigonometry: '<S379>/Acos' incorporates:
           *  DotProduct: '<S379>/Dot Product'
           */
          if (rtb_Rem_i > 1.0F) {
            rtb_Rem_i = 1.0F;
          } else if (rtb_Rem_i < -1.0F) {
            rtb_Rem_i = -1.0F;
          }

          /* Switch: '<S379>/Switch2' incorporates:
           *  Constant: '<S379>/Constant4'
           */
          if (rtb_Divide_o_idx_1 == 0.0F) {
            rtb_Divide_o_idx_1 = 1.0F;
          }

          /* Product: '<S379>/Multiply' incorporates:
           *  Switch: '<S379>/Switch2'
           *  Trigonometry: '<S379>/Acos'
           */
          rtb_Divide_o_idx_1 *= acosf(rtb_Rem_i);

          /* Saturate: '<S346>/Saturation' */
          if (rtb_Divide_o_idx_1 > 1.57079637F) {
            rtb_Divide_o_idx_0 = 1.57079637F;
          } else if (rtb_Divide_o_idx_1 < -1.57079637F) {
            rtb_Divide_o_idx_0 = -1.57079637F;
          } else {
            rtb_Divide_o_idx_0 = rtb_Divide_o_idx_1;
          }

          /* End of Saturate: '<S346>/Saturation' */

          /* Math: '<S332>/Rem' incorporates:
           *  Constant: '<S332>/Constant1'
           *  Delay: '<S328>/Delay'
           *  Sum: '<S328>/Sum2'
           */
          rtb_Rem_i = rt_remf(rtb_a_k - FMS_DW.Delay_DSTATE_do, 6.28318548F);

          /* Switch: '<S332>/Switch' incorporates:
           *  Abs: '<S332>/Abs'
           *  Constant: '<S332>/Constant'
           *  Constant: '<S338>/Constant'
           *  Product: '<S332>/Multiply'
           *  RelationalOperator: '<S338>/Compare'
           *  Signum: '<S332>/Sign'
           *  Sum: '<S332>/Add'
           */
          if (fabsf(rtb_Rem_i) > 3.14159274F) {
            /* Signum: '<S332>/Sign' */
            if (rtb_Rem_i < 0.0F) {
              rtb_Square2 = -1.0F;
            } else {
              rtb_Square2 = (real32_T)(rtb_Rem_i > 0.0F);
            }

            rtb_Rem_i -= 6.28318548F * rtb_Square2;
          }

          /* End of Switch: '<S332>/Switch' */

          /* Sum: '<S328>/Sum' incorporates:
           *  Delay: '<S328>/Delay'
           */
          rtb_Square2 = rtb_Rem_i + FMS_DW.Delay_DSTATE_do;

          /* Product: '<S337>/Multiply1' incorporates:
           *  Constant: '<S337>/const1'
           *  DiscreteIntegrator: '<S331>/Integrator'
           */
          rtb_Rem_i = FMS_DW.Integrator_DSTATE_j * 0.785398185F;

          /* Sum: '<S337>/Add' incorporates:
           *  DiscreteIntegrator: '<S331>/Integrator1'
           *  Sum: '<S331>/Subtract'
           */
          rtb_Divide_o_idx_1 = (FMS_DW.Integrator1_DSTATE_e - rtb_Square2) +
            rtb_Rem_i;

          /* Signum: '<S337>/Sign' */
          if (rtb_Divide_o_idx_1 < 0.0F) {
            rtb_Square2 = -1.0F;
          } else {
            rtb_Square2 = (real32_T)(rtb_Divide_o_idx_1 > 0.0F);
          }

          /* Sum: '<S337>/Add2' incorporates:
           *  Abs: '<S337>/Abs'
           *  Gain: '<S337>/Gain'
           *  Gain: '<S337>/Gain1'
           *  Product: '<S337>/Multiply2'
           *  Product: '<S337>/Multiply3'
           *  Signum: '<S337>/Sign'
           *  Sqrt: '<S337>/Sqrt'
           *  Sum: '<S337>/Add1'
           *  Sum: '<S337>/Subtract'
           */
          rtb_a_k = (sqrtf((8.0F * fabsf(rtb_Divide_o_idx_1) + FMS_ConstB.d_n) *
                           FMS_ConstB.d_n) - FMS_ConstB.d_n) * 0.5F *
            rtb_Square2 + rtb_Rem_i;

          /* Sum: '<S337>/Add3' */
          rtb_Square2 = rtb_Divide_o_idx_1 + FMS_ConstB.d_n;

          /* Sum: '<S337>/Subtract1' */
          rtb_MathFunction_c_idx_0 = rtb_Divide_o_idx_1 - FMS_ConstB.d_n;

          /* Signum: '<S337>/Sign1' */
          if (rtb_Square2 < 0.0F) {
            rtb_Square2 = -1.0F;
          } else {
            rtb_Square2 = (real32_T)(rtb_Square2 > 0.0F);
          }

          /* Signum: '<S337>/Sign2' */
          if (rtb_MathFunction_c_idx_0 < 0.0F) {
            tmp_2 = -1.0F;
          } else {
            tmp_2 = (real32_T)(rtb_MathFunction_c_idx_0 > 0.0F);
          }

          /* Sum: '<S337>/Add5' incorporates:
           *  Gain: '<S337>/Gain2'
           *  Product: '<S337>/Multiply4'
           *  Signum: '<S337>/Sign1'
           *  Signum: '<S337>/Sign2'
           *  Sum: '<S337>/Add4'
           *  Sum: '<S337>/Subtract2'
           */
          rtb_a_k += ((rtb_Divide_o_idx_1 - rtb_a_k) + rtb_Rem_i) *
            ((rtb_Square2 - tmp_2) * 0.5F);

          /* Update for Delay: '<S347>/Delay' */
          FMS_DW.icLoad_h = false;

          /* Update for DiscreteIntegrator: '<S388>/Discrete-Time Integrator' incorporates:
           *  Constant: '<S279>/L1'
           *  Constant: '<S346>/Constant'
           *  MinMax: '<S346>/Max'
           *  MinMax: '<S346>/Min'
           *  Product: '<S346>/Divide'
           *  Product: '<S346>/Multiply1'
           *  Product: '<S347>/Divide1'
           *  Sqrt: '<S381>/Sqrt'
           *  Trigonometry: '<S346>/Sin'
           */
          FMS_DW.l1_heading_a += arm_sin_f32(rtb_Divide_o_idx_0) * rtb_Gain_fj /
            fminf(FMS_PARAM.L1, fmaxf(sqrtf(rtb_Divide_o_idx_2), 0.5F)) /
            rtb_Switch_k * 0.004F;

          /* Update for Delay: '<S327>/Delay' */
          FMS_DW.icLoad_j = false;

          /* Update for Delay: '<S328>/Delay' */
          FMS_DW.icLoad_c = false;

          /* Update for DiscreteIntegrator: '<S331>/Integrator1' incorporates:
           *  DiscreteIntegrator: '<S331>/Integrator'
           */
          FMS_DW.Integrator1_IC_LOADING_o = 0U;
          FMS_DW.Integrator1_DSTATE_e += 0.004F * FMS_DW.Integrator_DSTATE_j;

          /* Signum: '<S337>/Sign5' */
          if (rtb_a_k < 0.0F) {
            /* Signum: '<S337>/Sign6' */
            rtb_Divide_o_idx_1 = -1.0F;
          } else {
            /* Signum: '<S337>/Sign6' */
            rtb_Divide_o_idx_1 = (real32_T)(rtb_a_k > 0.0F);
          }

          /* Sum: '<S337>/Add6' */
          rtb_Square2 = rtb_a_k + FMS_ConstB.d_n;

          /* Sum: '<S337>/Subtract3' */
          rtb_MathFunction_c_idx_0 = rtb_a_k - FMS_ConstB.d_n;

          /* Signum: '<S337>/Sign3' */
          if (rtb_Square2 < 0.0F) {
            rtb_Square2 = -1.0F;
          } else {
            rtb_Square2 = (real32_T)(rtb_Square2 > 0.0F);
          }

          /* Signum: '<S337>/Sign4' */
          if (rtb_MathFunction_c_idx_0 < 0.0F) {
            rtb_Divide_o_idx_2 = -1.0F;
          } else {
            rtb_Divide_o_idx_2 = (real32_T)(rtb_MathFunction_c_idx_0 > 0.0F);
          }

          /* Update for DiscreteIntegrator: '<S331>/Integrator' incorporates:
           *  Constant: '<S337>/const'
           *  Gain: '<S337>/Gain3'
           *  Product: '<S337>/Divide'
           *  Product: '<S337>/Multiply5'
           *  Product: '<S337>/Multiply6'
           *  Signum: '<S337>/Sign3'
           *  Signum: '<S337>/Sign4'
           *  Signum: '<S337>/Sign5'
           *  Sum: '<S337>/Subtract4'
           *  Sum: '<S337>/Subtract5'
           *  Sum: '<S337>/Subtract6'
           */
          FMS_DW.Integrator_DSTATE_j += ((rtb_a_k / FMS_ConstB.d_n -
            rtb_Divide_o_idx_1) * FMS_ConstB.Gain4_o * ((rtb_Square2 -
            rtb_Divide_o_idx_2) * 0.5F) - rtb_Divide_o_idx_1 * 1.04719758F) *
            0.004F;
          if (FMS_DW.Integrator_DSTATE_j >= FMS_PARAM.YAW_RATE_LIM) {
            FMS_DW.Integrator_DSTATE_j = FMS_PARAM.YAW_RATE_LIM;
          } else if (FMS_DW.Integrator_DSTATE_j <= -FMS_PARAM.YAW_RATE_LIM) {
            FMS_DW.Integrator_DSTATE_j = -FMS_PARAM.YAW_RATE_LIM;
          }

          /* End of Update for DiscreteIntegrator: '<S331>/Integrator' */
          /* End of Outputs for SubSystem: '<S41>/Return' */
          break;

         case 3:
          if (FMS_DW.SwitchCase_ActiveSubsystem_on != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S41>/Hold' incorporates:
             *  ActionPort: '<S277>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S41>/Switch Case' incorporates:
             *  Chart: '<S286>/Motion Status'
             *  Chart: '<S296>/Motion State'
             *  Chart: '<S308>/Motion State'
             */
            FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_l);
            FMS_MotionStatus_Reset(&rtb_state_ee, &FMS_DW.sf_MotionStatus_d);
            FMS_MotionState_i_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_i);

            /* End of SystemReset for SubSystem: '<S41>/Hold' */
          }

          /* Outputs for IfAction SubSystem: '<S41>/Hold' incorporates:
           *  ActionPort: '<S277>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S308>/Motion State' incorporates:
           *  Constant: '<S308>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S308>/Square'
           *  Math: '<S308>/Square1'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sqrt: '<S308>/Sqrt'
           *  Sum: '<S308>/Add'
           */
          FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
            FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                          &FMS_DW.sf_MotionState_l);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S307>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S307>/Hold Control' incorporates:
               *  ActionPort: '<S310>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S307>/Switch Case' */
              FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_h);

              /* End of SystemReset for SubSystem: '<S307>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S307>/Hold Control' incorporates:
             *  ActionPort: '<S310>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                              FMS_U.INS_Out.psi, FMS_B.Merge_m,
                              &FMS_ConstB.HoldControl_h, &FMS_DW.HoldControl_h);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S307>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S307>/Brake Control' incorporates:
             *  ActionPort: '<S309>/Action Port'
             */
            FMS_BrakeControl_h(FMS_B.Merge_m);

            /* End of Outputs for SubSystem: '<S307>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_g != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S307>/Move Control' incorporates:
               *  ActionPort: '<S311>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S307>/Switch Case' */
              FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_h);

              /* End of SystemReset for SubSystem: '<S307>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S307>/Move Control' incorporates:
             *  ActionPort: '<S311>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                              FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_m,
                              &FMS_ConstB.MoveControl_h, &FMS_DW.MoveControl_h);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S307>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S286>/Motion Status' incorporates:
           *  Abs: '<S286>/Abs'
           *  Constant: '<S286>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          FMS_MotionStatus(0.0F, fabsf(FMS_U.INS_Out.vd), &rtb_state_ee,
                           &FMS_DW.sf_MotionStatus_d);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S285>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S285>/Hold Control' incorporates:
               *  ActionPort: '<S288>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S285>/Switch Case' */
              FMS_HoldControl_Reset(&FMS_DW.HoldControl_b);

              /* End of SystemReset for SubSystem: '<S285>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S285>/Hold Control' incorporates:
             *  ActionPort: '<S288>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl(FMS_U.INS_Out.h_R, &FMS_B.Merge_ob,
                            &FMS_DW.HoldControl_b);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S285>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S285>/Brake Control' incorporates:
             *  ActionPort: '<S287>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_ob);

            /* End of Outputs for SubSystem: '<S285>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_d != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S285>/Move Control' incorporates:
               *  ActionPort: '<S289>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S285>/Switch Case' */
              FMS_MoveControl_Reset(&FMS_DW.MoveControl_g);

              /* End of SystemReset for SubSystem: '<S285>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S285>/Move Control' incorporates:
             *  ActionPort: '<S289>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl(FMS_U.Pilot_Cmd.stick_throttle, &FMS_B.Merge_ob,
                            &FMS_ConstB.MoveControl_g, &FMS_DW.MoveControl_g);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S285>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Chart: '<S296>/Motion State' incorporates:
           *  Abs: '<S296>/Abs'
           *  Constant: '<S296>/Constant'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          FMS_MotionState_i(0.0F, fabsf(FMS_U.INS_Out.r), &rtb_state_ee,
                            &FMS_DW.sf_MotionState_i);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* SwitchCase: '<S295>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S295>/Hold Control' incorporates:
               *  ActionPort: '<S298>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S295>/Switch Case' */
              FMS_HoldControl_i_Reset(&FMS_DW.HoldControl_k);

              /* End of SystemReset for SubSystem: '<S295>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S295>/Hold Control' incorporates:
             *  ActionPort: '<S298>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_k(FMS_U.INS_Out.psi, &FMS_B.Merge_p,
                              &FMS_DW.HoldControl_k);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S295>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S295>/Brake Control' incorporates:
             *  ActionPort: '<S297>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_p);

            /* End of Outputs for SubSystem: '<S295>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_bi != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S295>/Move Control' incorporates:
               *  ActionPort: '<S299>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S295>/Switch Case' */
              FMS_MoveControl_c_Reset(&FMS_DW.MoveControl_o);

              /* End of SystemReset for SubSystem: '<S295>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S295>/Move Control' incorporates:
             *  ActionPort: '<S299>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_o(FMS_U.Pilot_Cmd.stick_yaw, &FMS_B.Merge_p,
                              &FMS_ConstB.MoveControl_o, &FMS_DW.MoveControl_o);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S295>/Move Control' */
            break;
          }

          /* End of Outputs for SubSystem: '<S41>/Hold' */
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Hold' incorporates:
           *  ActionPort: '<S277>/Action Port'
           */
          /* BusAssignment: '<S277>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_c;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_c;
          FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_l;

          /* Saturate: '<S295>/Saturation' */
          if (FMS_B.Merge_p > FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
          } else if (FMS_B.Merge_p < -FMS_PARAM.YAW_RATE_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
          } else {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.psi_rate_cmd = FMS_B.Merge_p;
          }

          /* End of Saturate: '<S295>/Saturation' */

          /* Saturate: '<S307>/Saturation1' incorporates:
           *  Merge: '<S307>/Merge'
           */
          if (FMS_B.Merge_m[0] > FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = FMS_PARAM.VEL_XY_LIM;
          } else if (FMS_B.Merge_m[0] < -FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = -FMS_PARAM.VEL_XY_LIM;
          } else {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.u_cmd = FMS_B.Merge_m[0];
          }

          if (FMS_B.Merge_m[1] > FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = FMS_PARAM.VEL_XY_LIM;
          } else if (FMS_B.Merge_m[1] < -FMS_PARAM.VEL_XY_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = -FMS_PARAM.VEL_XY_LIM;
          } else {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.v_cmd = FMS_B.Merge_m[1];
          }

          /* End of Saturate: '<S307>/Saturation1' */

          /* Saturate: '<S285>/Saturation1' */
          if (FMS_B.Merge_ob > FMS_PARAM.VEL_Z_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = FMS_PARAM.VEL_Z_LIM;
          } else if (FMS_B.Merge_ob < -FMS_PARAM.VEL_Z_LIM) {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = -FMS_PARAM.VEL_Z_LIM;
          } else {
            /* BusAssignment: '<S277>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = FMS_B.Merge_ob;
          }

          /* End of Saturate: '<S285>/Saturation1' */
          /* End of Outputs for SubSystem: '<S41>/Hold' */
          break;

         default:
          memset(&FMS_Y.FMS_Out, 0, sizeof(FMS_Out_Bus));

          /* Outputs for IfAction SubSystem: '<S41>/Unknown' incorporates:
           *  ActionPort: '<S281>/Action Port'
           */
          /* BusAssignment: '<S281>/Bus Assignment' incorporates:
           *  BusAssignment: '<S34>/Bus Assignment'
           *  Constant: '<S281>/Constant2'
           *  Constant: '<S281>/Constant3'
           *  Outport: '<Root>/FMS_Out'
           */
          FMS_Y.FMS_Out.reset = 1U;
          FMS_Y.FMS_Out.status = FMS_ConstB.DataTypeConversion_b5;
          FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_m;
          FMS_Y.FMS_Out.actuator_cmd[0] = 1000U;
          FMS_Y.FMS_Out.actuator_cmd[1] = 1000U;
          FMS_Y.FMS_Out.actuator_cmd[2] = 1000U;
          FMS_Y.FMS_Out.actuator_cmd[3] = 1000U;
          for (i = 0; i < 12; i++) {
            FMS_Y.FMS_Out.actuator_cmd[i + 4] = 0U;
          }

          /* End of BusAssignment: '<S281>/Bus Assignment' */
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
           *  Math: '<S110>/Math Function'
           *  Math: '<S75>/Square'
           *  Outport: '<Root>/FMS_Out'
           *  Product: '<S112>/Divide'
           *  Product: '<S113>/Divide'
           *  Product: '<S65>/Divide'
           *  Sum: '<S67>/Sum'
           *  Sum: '<S70>/Subtract'
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
          if ((rtPrevAction != FMS_DW.SwitchCase_ActiveSubsystem_i) &&
              (rtPrevAction == 1)) {
            /* Disable for Resettable SubSystem: '<S43>/Mission_SubSystem' */
            /* SwitchCase: '<S88>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_a = -1;

            /* SwitchCase: '<S78>/Switch Case' */
            FMS_DW.SwitchCase_ActiveSubsystem_e = -1;

            /* End of Disable for SubSystem: '<S43>/Mission_SubSystem' */
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_i) {
           case 0:
            {
              boolean_T rtb_Compare_og;
              boolean_T rtb_LogicalOperator_i;
              boolean_T rtb_LogicalOperator_o;
              boolean_T rtb_Switch_p_idx_1;

              /* Outputs for IfAction SubSystem: '<S37>/Offboard' incorporates:
               *  ActionPort: '<S44>/Action Port'
               */
              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* SignalConversion generated from: '<S184>/Multiply2' incorporates:
               *  Gain: '<S185>/Gain'
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_MathFunction_c_idx_0 = FMS_U.INS_Out.x_R;
              rtb_Divide_o_idx_0 = FMS_U.INS_Out.y_R;
              rtb_Divide_o_idx_1 = -FMS_U.INS_Out.h_R;

              /* MultiPortSwitch: '<S182>/Index Vector' incorporates:
               *  Concatenate: '<S194>/Vector Concatenate'
               *  Concatenate: '<S198>/Vector Concatenate'
               *  Inport: '<Root>/Auto_Cmd'
               *  Product: '<S188>/Multiply1'
               *  Product: '<S189>/Multiply3'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              switch (FMS_U.Auto_Cmd.frame) {
               case 0:
                /* SignalConversion generated from: '<S194>/Vector Concatenate2' incorporates:
                 *  Constant: '<S194>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S194>/Trigonometric Function3' incorporates:
                 *  Gain: '<S193>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S194>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S194>/Trigonometric Function2' incorporates:
                 *  Gain: '<S193>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S194>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S194>/Gain' incorporates:
                 *  Trigonometry: '<S194>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S194>/Vector Concatenate1' incorporates:
                 *  Constant: '<S194>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S194>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S194>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* SignalConversion generated from: '<S194>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S194>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_i[0];

                /* Saturate: '<S188>/Saturation' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S188>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/x_cmd valid'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S188>/Sum1'
                 */
                rtb_Divide_o_idx_1 = (FMS_U.Auto_Cmd.cmd_mask & 128U) > 0U ?
                  FMS_U.Auto_Cmd.x_cmd - FMS_U.INS_Out.x_R : 0.0F;
                if (rtb_Divide_o_idx_1 > 4.0F) {
                  rtb_Divide_o_idx_1 = 4.0F;
                } else if (rtb_Divide_o_idx_1 < -4.0F) {
                  rtb_Divide_o_idx_1 = -4.0F;
                }

                /* SignalConversion generated from: '<S194>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S194>/Vector Concatenate3'
                 */
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_i[1];

                /* Saturate: '<S188>/Saturation' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S188>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/y_cmd valid'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S188>/Sum1'
                 */
                rtb_Divide_o_idx_0 = (FMS_U.Auto_Cmd.cmd_mask & 256U) > 0U ?
                  FMS_U.Auto_Cmd.y_cmd - FMS_U.INS_Out.y_R : 0.0F;
                if (rtb_Divide_o_idx_0 > 4.0F) {
                  rtb_Divide_o_idx_0 = 4.0F;
                } else if (rtb_Divide_o_idx_0 < -4.0F) {
                  rtb_Divide_o_idx_0 = -4.0F;
                }

                /* SignalConversion generated from: '<S194>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S194>/Vector Concatenate3'
                 */
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_i[2];

                /* Saturate: '<S188>/Saturation' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Gain: '<S185>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S188>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/z_cmd valid'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S188>/Sum1'
                 */
                rtb_Square2 = (FMS_U.Auto_Cmd.cmd_mask & 512U) > 0U ?
                  FMS_U.Auto_Cmd.z_cmd - (-FMS_U.INS_Out.h_R) : 0.0F;
                if (rtb_Square2 > 2.0F) {
                  rtb_Square2 = 2.0F;
                } else if (rtb_Square2 < -2.0F) {
                  rtb_Square2 = -2.0F;
                }

                for (i = 0; i < 3; i++) {
                  rtb_MatrixConcatenate3[i] = (rtb_Transpose[i + 3] *
                    rtb_Divide_o_idx_0 + rtb_Transpose[i] * rtb_Divide_o_idx_1)
                    + rtb_Transpose[i + 6] * rtb_Square2;
                }
                break;

               case 1:
                /* SignalConversion generated from: '<S197>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S197>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_ny[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_ny[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_ny[2];

                /* SignalConversion generated from: '<S197>/Vector Concatenate2' incorporates:
                 *  Constant: '<S197>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S197>/Trigonometric Function3' incorporates:
                 *  Gain: '<S195>/Gain'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Trigonometry: '<S197>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(-FMS_B.Cmd_In.offboard_psi_0);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S197>/Trigonometric Function2' incorporates:
                 *  Gain: '<S195>/Gain'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Trigonometry: '<S197>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_2 = arm_sin_f32(-FMS_B.Cmd_In.offboard_psi_0);

                /* Gain: '<S197>/Gain' incorporates:
                 *  Trigonometry: '<S197>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_2;

                /* SignalConversion generated from: '<S197>/Vector Concatenate1' incorporates:
                 *  Constant: '<S197>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S197>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_2;

                /* Trigonometry: '<S197>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* Product: '<S189>/Multiply2' incorporates:
                 *  Concatenate: '<S197>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_Sum2_n[i] = (rtb_Transpose[i + 3] * rtb_Divide_o_idx_0 +
                                   rtb_Transpose[i] * rtb_MathFunction_c_idx_0)
                    + rtb_Transpose[i + 6] * rtb_Divide_o_idx_1;
                }

                /* End of Product: '<S189>/Multiply2' */

                /* SignalConversion generated from: '<S198>/Vector Concatenate2' incorporates:
                 *  Constant: '<S198>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Gain: '<S196>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S189>/Subtract'
                 */
                rtb_Divide_o_idx_1 = -(FMS_U.INS_Out.psi -
                  FMS_B.Cmd_In.offboard_psi_0);

                /* Trigonometry: '<S198>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S198>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(rtb_Divide_o_idx_1);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S198>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S198>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_1 = arm_sin_f32(rtb_Divide_o_idx_1);

                /* Gain: '<S198>/Gain' incorporates:
                 *  Trigonometry: '<S198>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_1;

                /* SignalConversion generated from: '<S198>/Vector Concatenate1' incorporates:
                 *  Constant: '<S198>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S198>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_1;

                /* Trigonometry: '<S198>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* SignalConversion generated from: '<S198>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S198>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_e0[0];

                /* Saturate: '<S189>/Saturation1' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Product: '<S189>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/x_cmd valid'
                 *  Sum: '<S189>/Sum2'
                 */
                rtb_Divide_o_idx_1 = (FMS_U.Auto_Cmd.cmd_mask & 128U) > 0U ?
                  FMS_U.Auto_Cmd.x_cmd - rtb_Sum2_n[0] : 0.0F;
                if (rtb_Divide_o_idx_1 > 4.0F) {
                  rtb_Divide_o_idx_1 = 4.0F;
                } else if (rtb_Divide_o_idx_1 < -4.0F) {
                  rtb_Divide_o_idx_1 = -4.0F;
                }

                /* SignalConversion generated from: '<S198>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S198>/Vector Concatenate3'
                 */
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_e0[1];

                /* Saturate: '<S189>/Saturation1' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Product: '<S189>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/y_cmd valid'
                 *  Sum: '<S189>/Sum2'
                 */
                rtb_Divide_o_idx_0 = (FMS_U.Auto_Cmd.cmd_mask & 256U) > 0U ?
                  FMS_U.Auto_Cmd.y_cmd - rtb_Sum2_n[1] : 0.0F;
                if (rtb_Divide_o_idx_0 > 4.0F) {
                  rtb_Divide_o_idx_0 = 4.0F;
                } else if (rtb_Divide_o_idx_0 < -4.0F) {
                  rtb_Divide_o_idx_0 = -4.0F;
                }

                /* SignalConversion generated from: '<S198>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S198>/Vector Concatenate3'
                 */
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_e0[2];

                /* Saturate: '<S189>/Saturation1' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Product: '<S189>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/z_cmd valid'
                 *  Sum: '<S189>/Sum2'
                 */
                rtb_Square2 = (FMS_U.Auto_Cmd.cmd_mask & 512U) > 0U ?
                  FMS_U.Auto_Cmd.z_cmd - rtb_Sum2_n[2] : 0.0F;
                if (rtb_Square2 > 2.0F) {
                  rtb_Square2 = 2.0F;
                } else if (rtb_Square2 < -2.0F) {
                  rtb_Square2 = -2.0F;
                }

                for (i = 0; i < 3; i++) {
                  rtb_MatrixConcatenate3[i] = (rtb_Transpose[i + 3] *
                    rtb_Divide_o_idx_0 + rtb_Transpose[i] * rtb_Divide_o_idx_1)
                    + rtb_Transpose[i + 6] * rtb_Square2;
                }
                break;

               default:
                /* SignalConversion generated from: '<S191>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S191>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_n[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_n[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_n[2];

                /* SignalConversion generated from: '<S191>/Vector Concatenate2' incorporates:
                 *  Constant: '<S191>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S191>/Trigonometric Function3' incorporates:
                 *  Gain: '<S190>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S191>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S191>/Trigonometric Function2' incorporates:
                 *  Gain: '<S190>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S191>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_2 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S191>/Gain' incorporates:
                 *  Trigonometry: '<S191>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_2;

                /* SignalConversion generated from: '<S191>/Vector Concatenate1' incorporates:
                 *  Constant: '<S191>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S191>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_2;

                /* Trigonometry: '<S191>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* Product: '<S184>/Multiply2' incorporates:
                 *  Concatenate: '<S191>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_MatrixConcatenate3[i] = (rtb_Transpose[i + 3] *
                    rtb_Divide_o_idx_0 + rtb_Transpose[i] *
                    rtb_MathFunction_c_idx_0) + rtb_Transpose[i + 6] *
                    rtb_Divide_o_idx_1;
                }

                /* End of Product: '<S184>/Multiply2' */

                /* Sum: '<S184>/Sum2' */
                rtb_Divide_o_idx_1 = rtb_MatrixConcatenate3[0];
                rtb_Square2 = rtb_MatrixConcatenate3[1];
                rtb_Divide_o_idx_0 = rtb_MatrixConcatenate3[2];

                /* Saturate: '<S184>/Saturation1' incorporates:
                 *  Constant: '<S192>/Constant'
                 *  Product: '<S184>/Multiply'
                 *  RelationalOperator: '<S192>/Compare'
                 *  S-Function (sfix_bitop): '<S187>/x_cmd valid'
                 *  S-Function (sfix_bitop): '<S187>/y_cmd valid'
                 *  S-Function (sfix_bitop): '<S187>/z_cmd valid'
                 *  Sum: '<S184>/Sum2'
                 */
                rtb_Divide_o_idx_1 = (FMS_U.Auto_Cmd.cmd_mask & 128U) > 0U ?
                  FMS_U.Auto_Cmd.x_cmd - rtb_Divide_o_idx_1 : 0.0F;
                if (rtb_Divide_o_idx_1 > 4.0F) {
                  rtb_MatrixConcatenate3[0] = 4.0F;
                } else if (rtb_Divide_o_idx_1 < -4.0F) {
                  rtb_MatrixConcatenate3[0] = -4.0F;
                } else {
                  rtb_MatrixConcatenate3[0] = rtb_Divide_o_idx_1;
                }

                rtb_Divide_o_idx_1 = (FMS_U.Auto_Cmd.cmd_mask & 256U) > 0U ?
                  FMS_U.Auto_Cmd.y_cmd - rtb_Square2 : 0.0F;
                if (rtb_Divide_o_idx_1 > 4.0F) {
                  rtb_MatrixConcatenate3[1] = 4.0F;
                } else if (rtb_Divide_o_idx_1 < -4.0F) {
                  rtb_MatrixConcatenate3[1] = -4.0F;
                } else {
                  rtb_MatrixConcatenate3[1] = rtb_Divide_o_idx_1;
                }

                rtb_Divide_o_idx_1 = (FMS_U.Auto_Cmd.cmd_mask & 512U) > 0U ?
                  FMS_U.Auto_Cmd.z_cmd - rtb_Divide_o_idx_0 : 0.0F;
                if (rtb_Divide_o_idx_1 > 2.0F) {
                  rtb_MatrixConcatenate3[2] = 2.0F;
                } else if (rtb_Divide_o_idx_1 < -2.0F) {
                  rtb_MatrixConcatenate3[2] = -2.0F;
                } else {
                  rtb_MatrixConcatenate3[2] = rtb_Divide_o_idx_1;
                }

                /* End of Saturate: '<S184>/Saturation1' */
                break;
              }

              /* End of MultiPortSwitch: '<S182>/Index Vector' */

              /* Product: '<S119>/Multiply' incorporates:
               *  Constant: '<S127>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  RelationalOperator: '<S127>/Compare'
               *  S-Function (sfix_bitop): '<S124>/ax_cmd valid'
               *  S-Function (sfix_bitop): '<S124>/ay_cmd valid'
               *  S-Function (sfix_bitop): '<S124>/az_cmd valid'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              rtb_MathFunction_c_idx_0 = (FMS_U.Auto_Cmd.cmd_mask & 65536U) > 0U
                ? FMS_U.Auto_Cmd.ax_cmd : 0.0F;
              rtb_Divide_o_idx_0 = (FMS_U.Auto_Cmd.cmd_mask & 131072U) > 0U ?
                FMS_U.Auto_Cmd.ay_cmd : 0.0F;
              rtb_Divide_o_idx_1 = (FMS_U.Auto_Cmd.cmd_mask & 262144U) > 0U ?
                FMS_U.Auto_Cmd.az_cmd : 0.0F;

              /* MultiPortSwitch: '<S119>/Index Vector' incorporates:
               *  Inport: '<Root>/Auto_Cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              switch (FMS_U.Auto_Cmd.frame) {
               case 0:
                /* SignalConversion generated from: '<S129>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S129>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_e[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_e[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_e[2];

                /* SignalConversion generated from: '<S129>/Vector Concatenate2' incorporates:
                 *  Constant: '<S129>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S129>/Trigonometric Function3' incorporates:
                 *  Gain: '<S128>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S129>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S129>/Trigonometric Function2' incorporates:
                 *  Gain: '<S128>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S129>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_2 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S129>/Gain' incorporates:
                 *  Trigonometry: '<S129>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_2;

                /* SignalConversion generated from: '<S129>/Vector Concatenate1' incorporates:
                 *  Constant: '<S129>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S129>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_2;

                /* Trigonometry: '<S129>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* Product: '<S125>/Multiply' incorporates:
                 *  Concatenate: '<S129>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_Transpose_0[i] = (rtb_Transpose[i + 3] *
                                        rtb_Divide_o_idx_0 + rtb_Transpose[i] *
                                        rtb_MathFunction_c_idx_0) +
                    rtb_Transpose[i + 6] * rtb_Divide_o_idx_1;
                }

                /* End of Product: '<S125>/Multiply' */
                rtb_MathFunction_c_idx_0 = rtb_Transpose_0[0];
                rtb_Divide_o_idx_0 = rtb_Transpose_0[1];
                rtb_Divide_o_idx_1 = rtb_Transpose_0[2];
                break;

               case 1:
                /* SignalConversion generated from: '<S131>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S131>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_o[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_o[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_o[2];

                /* SignalConversion generated from: '<S131>/Vector Concatenate2' incorporates:
                 *  Constant: '<S131>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Gain: '<S130>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S126>/Subtract'
                 */
                rtb_Divide_o_idx_2 = -(FMS_U.INS_Out.psi -
                  FMS_B.Cmd_In.offboard_psi_0);

                /* Trigonometry: '<S131>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S131>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(rtb_Divide_o_idx_2);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S131>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S131>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_2 = arm_sin_f32(rtb_Divide_o_idx_2);

                /* Gain: '<S131>/Gain' incorporates:
                 *  Trigonometry: '<S131>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_2;

                /* SignalConversion generated from: '<S131>/Vector Concatenate1' incorporates:
                 *  Constant: '<S131>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S131>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_2;

                /* Trigonometry: '<S131>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* Product: '<S126>/Multiply3' incorporates:
                 *  Concatenate: '<S131>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_Transpose_0[i] = (rtb_Transpose[i + 3] *
                                        rtb_Divide_o_idx_0 + rtb_Transpose[i] *
                                        rtb_MathFunction_c_idx_0) +
                    rtb_Transpose[i + 6] * rtb_Divide_o_idx_1;
                }

                /* End of Product: '<S126>/Multiply3' */
                rtb_MathFunction_c_idx_0 = rtb_Transpose_0[0];
                rtb_Divide_o_idx_0 = rtb_Transpose_0[1];
                rtb_Divide_o_idx_1 = rtb_Transpose_0[2];
                break;
              }

              /* End of MultiPortSwitch: '<S119>/Index Vector' */

              /* Product: '<S183>/Multiply' incorporates:
               *  Constant: '<S203>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  RelationalOperator: '<S203>/Compare'
               *  S-Function (sfix_bitop): '<S200>/u_cmd valid'
               *  S-Function (sfix_bitop): '<S200>/v_cmd valid'
               *  S-Function (sfix_bitop): '<S200>/w_cmd valid'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              rtb_Sum2_n[0] = (FMS_U.Auto_Cmd.cmd_mask & 8192U) > 0U ?
                FMS_U.Auto_Cmd.u_cmd : 0.0F;
              rtb_Sum2_n[1] = (FMS_U.Auto_Cmd.cmd_mask & 16384U) > 0U ?
                FMS_U.Auto_Cmd.v_cmd : 0.0F;
              rtb_Sum2_n[2] = (FMS_U.Auto_Cmd.cmd_mask & 32768U) > 0U ?
                FMS_U.Auto_Cmd.w_cmd : 0.0F;

              /* MultiPortSwitch: '<S183>/Index Vector' incorporates:
               *  Inport: '<Root>/Auto_Cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              switch (FMS_U.Auto_Cmd.frame) {
               case 0:
                /* SignalConversion generated from: '<S205>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S205>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_l[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_l[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_l[2];

                /* SignalConversion generated from: '<S205>/Vector Concatenate2' incorporates:
                 *  Constant: '<S205>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Trigonometry: '<S205>/Trigonometric Function3' incorporates:
                 *  Gain: '<S204>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S205>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(-FMS_U.INS_Out.psi);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S205>/Trigonometric Function2' incorporates:
                 *  Gain: '<S204>/Gain'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Trigonometry: '<S205>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_2 = arm_sin_f32(-FMS_U.INS_Out.psi);

                /* Gain: '<S205>/Gain' incorporates:
                 *  Trigonometry: '<S205>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_2;

                /* SignalConversion generated from: '<S205>/Vector Concatenate1' incorporates:
                 *  Constant: '<S205>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S205>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_2;

                /* Trigonometry: '<S205>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* Product: '<S201>/Multiply' incorporates:
                 *  Concatenate: '<S205>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_Transpose_0[i] = (rtb_Transpose[i + 3] * rtb_Sum2_n[1] +
                                        rtb_Transpose[i] * rtb_Sum2_n[0]) +
                    rtb_Transpose[i + 6] * rtb_Sum2_n[2];
                }

                /* End of Product: '<S201>/Multiply' */
                rtb_Sum2_n[0] = rtb_Transpose_0[0];
                rtb_Sum2_n[1] = rtb_Transpose_0[1];
                rtb_Sum2_n[2] = rtb_Transpose_0[2];
                break;

               case 1:
                /* SignalConversion generated from: '<S207>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S207>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3_iz[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3_iz[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3_iz[2];

                /* SignalConversion generated from: '<S207>/Vector Concatenate2' incorporates:
                 *  Constant: '<S207>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Gain: '<S206>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S202>/Subtract'
                 */
                rtb_Divide_o_idx_2 = -(FMS_U.INS_Out.psi -
                  FMS_B.Cmd_In.offboard_psi_0);

                /* Trigonometry: '<S207>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S207>/Trigonometric Function1'
                 */
                rtb_Square2 = arm_cos_f32(rtb_Divide_o_idx_2);
                rtb_Transpose[4] = rtb_Square2;

                /* Trigonometry: '<S207>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S207>/Trigonometric Function'
                 */
                rtb_Divide_o_idx_2 = arm_sin_f32(rtb_Divide_o_idx_2);

                /* Gain: '<S207>/Gain' incorporates:
                 *  Trigonometry: '<S207>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Divide_o_idx_2;

                /* SignalConversion generated from: '<S207>/Vector Concatenate1' incorporates:
                 *  Constant: '<S207>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S207>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Divide_o_idx_2;

                /* Trigonometry: '<S207>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Square2;

                /* Product: '<S202>/Multiply3' incorporates:
                 *  Concatenate: '<S207>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_Transpose_0[i] = (rtb_Transpose[i + 3] * rtb_Sum2_n[1] +
                                        rtb_Transpose[i] * rtb_Sum2_n[0]) +
                    rtb_Transpose[i + 6] * rtb_Sum2_n[2];
                }

                /* End of Product: '<S202>/Multiply3' */
                rtb_Sum2_n[0] = rtb_Transpose_0[0];
                rtb_Sum2_n[1] = rtb_Transpose_0[1];
                rtb_Sum2_n[2] = rtb_Transpose_0[2];
                break;
              }

              /* End of MultiPortSwitch: '<S183>/Index Vector' */
              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sum: '<S122>/Sum1' incorporates:
               *  Gain: '<S182>/Gain1'
               *  Gain: '<S182>/Gain2'
               */
              rtb_Divide_o_idx_2 = FMS_PARAM.XY_P * rtb_MatrixConcatenate3[0] +
                rtb_Sum2_n[0];
              rtb_Switch_k = FMS_PARAM.XY_P * rtb_MatrixConcatenate3[1] +
                rtb_Sum2_n[1];
              rtb_Sum2_n[2] += FMS_PARAM.Z_P * rtb_MatrixConcatenate3[2];

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Switch: '<S139>/Switch' incorporates:
               *  Constant: '<S154>/Constant'
               *  Constant: '<S155>/Constant'
               *  Constant: '<S156>/Constant'
               *  Constant: '<S159>/Constant'
               *  Constant: '<S161>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  RelationalOperator: '<S154>/Compare'
               *  RelationalOperator: '<S155>/Compare'
               *  RelationalOperator: '<S156>/Compare'
               *  RelationalOperator: '<S159>/Compare'
               *  RelationalOperator: '<S161>/Compare'
               *  S-Function (sfix_bitop): '<S139>/x_u_cmd'
               *  S-Function (sfix_bitop): '<S139>/y_v_cmd'
               *  S-Function (sfix_bitop): '<S140>/ax_cmd'
               *  S-Function (sfix_bitop): '<S140>/ay_cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               *  Switch: '<S140>/Switch'
               */
              if (FMS_U.Auto_Cmd.frame < 2) {
                /* Logic: '<S139>/Logical Operator' incorporates:
                 *  Constant: '<S155>/Constant'
                 *  Constant: '<S156>/Constant'
                 *  RelationalOperator: '<S155>/Compare'
                 *  RelationalOperator: '<S156>/Compare'
                 *  S-Function (sfix_bitop): '<S139>/x_u_cmd'
                 *  S-Function (sfix_bitop): '<S139>/y_v_cmd'
                 */
                rtb_LogicalOperator_i = (((FMS_U.Auto_Cmd.cmd_mask & 8320U) > 0U)
                  || ((FMS_U.Auto_Cmd.cmd_mask & 16640U) > 0U));
                rtb_Compare_og = rtb_LogicalOperator_i;

                /* Logic: '<S140>/Logical Operator' incorporates:
                 *  Constant: '<S159>/Constant'
                 *  Constant: '<S161>/Constant'
                 *  RelationalOperator: '<S159>/Compare'
                 *  RelationalOperator: '<S161>/Compare'
                 *  S-Function (sfix_bitop): '<S140>/ax_cmd'
                 *  S-Function (sfix_bitop): '<S140>/ay_cmd'
                 */
                rtb_LogicalOperator_o = (((FMS_U.Auto_Cmd.cmd_mask & 65536U) >
                  0U) || ((FMS_U.Auto_Cmd.cmd_mask & 131072U) > 0U));
                rtb_Switch_p_idx_1 = rtb_LogicalOperator_o;
              } else {
                rtb_LogicalOperator_i = ((FMS_U.Auto_Cmd.cmd_mask & 8320U) > 0U);
                rtb_Compare_og = ((FMS_U.Auto_Cmd.cmd_mask & 16640U) > 0U);
                rtb_LogicalOperator_o = ((FMS_U.Auto_Cmd.cmd_mask & 65536U) > 0U);
                rtb_Switch_p_idx_1 = ((FMS_U.Auto_Cmd.cmd_mask & 131072U) > 0U);
              }

              /* End of Switch: '<S139>/Switch' */

              /* Sum: '<S178>/Sum1' incorporates:
               *  Constant: '<S178>/Constant'
               *  Inport: '<Root>/Auto_Cmd'
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S178>/Math Function'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_Square2 = rt_remf(FMS_U.Auto_Cmd.psi_cmd, 6.28318548F) -
                FMS_U.INS_Out.psi;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Abs: '<S179>/Abs' */
              rtb_a_k = fabsf(rtb_Square2);

              /* Switch: '<S179>/Switch' incorporates:
               *  Constant: '<S179>/Constant'
               *  Constant: '<S180>/Constant'
               *  Product: '<S179>/Multiply'
               *  RelationalOperator: '<S180>/Compare'
               *  Signum: '<S179>/Sign'
               *  Sum: '<S179>/Subtract'
               */
              if (rtb_a_k > 3.14159274F) {
                /* Signum: '<S179>/Sign' */
                if (rtb_Square2 < 0.0F) {
                  rtb_Square2 = -1.0F;
                } else {
                  rtb_Square2 = (real32_T)(rtb_Square2 > 0.0F);
                }

                rtb_Square2 *= rtb_a_k - 6.28318548F;
              }

              /* End of Switch: '<S179>/Switch' */
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
              FMS_Y.FMS_Out.ax_cmd = rtb_MathFunction_c_idx_0;
              FMS_Y.FMS_Out.ay_cmd = rtb_Divide_o_idx_0;
              FMS_Y.FMS_Out.az_cmd = rtb_Divide_o_idx_1;

              /* Saturate: '<S178>/Saturation' */
              if (rtb_Square2 > 0.314159274F) {
                rtb_Square2 = 0.314159274F;
              } else if (rtb_Square2 < -0.314159274F) {
                rtb_Square2 = -0.314159274F;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S121>/Sum' incorporates:
               *  Constant: '<S177>/Constant'
               *  Constant: '<S181>/Constant'
               *  Gain: '<S175>/Gain2'
               *  Inport: '<Root>/Auto_Cmd'
               *  Product: '<S175>/Multiply2'
               *  Product: '<S176>/Multiply1'
               *  RelationalOperator: '<S177>/Compare'
               *  RelationalOperator: '<S181>/Compare'
               *  S-Function (sfix_bitop): '<S175>/psi_cmd valid'
               *  S-Function (sfix_bitop): '<S176>/psi_rate_cmd valid'
               *  Saturate: '<S178>/Saturation'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               */
              rtb_Divide_o_idx_1 = ((FMS_U.Auto_Cmd.cmd_mask & 32U) > 0U ?
                                    FMS_PARAM.YAW_P * rtb_Square2 : 0.0F) +
                ((FMS_U.Auto_Cmd.cmd_mask & 64U) > 0U ?
                 FMS_U.Auto_Cmd.psi_rate_cmd : 0.0F);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Saturate: '<S121>/Saturation' */
              if (rtb_Divide_o_idx_1 > FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
              } else if (rtb_Divide_o_idx_1 < -FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = -FMS_PARAM.YAW_RATE_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = rtb_Divide_o_idx_1;
              }

              /* End of Saturate: '<S121>/Saturation' */

              /* Saturate: '<S122>/Saturation2' */
              if (rtb_Divide_o_idx_2 > FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.u_cmd = FMS_PARAM.VEL_XY_LIM;
              } else if (rtb_Divide_o_idx_2 < -FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.u_cmd = -FMS_PARAM.VEL_XY_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.u_cmd = rtb_Divide_o_idx_2;
              }

              /* End of Saturate: '<S122>/Saturation2' */

              /* Saturate: '<S122>/Saturation1' */
              if (rtb_Switch_k > FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.v_cmd = FMS_PARAM.VEL_XY_LIM;
              } else if (rtb_Switch_k < -FMS_PARAM.VEL_XY_LIM) {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.v_cmd = -FMS_PARAM.VEL_XY_LIM;
              } else {
                /* BusAssignment: '<S44>/Bus Assignment' incorporates:
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.v_cmd = rtb_Switch_k;
              }

              /* End of Saturate: '<S122>/Saturation1' */

              /* Saturate: '<S122>/Saturation3' */
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

              /* End of Saturate: '<S122>/Saturation3' */

              /* Outputs for Atomic SubSystem: '<S120>/q_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Outputs for Atomic SubSystem: '<S120>/r_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/phi_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/theta_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/psi_rate_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/u_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/v_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/w_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/ax_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/ay_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/az_cmd_valid' */
              /* Outputs for Atomic SubSystem: '<S120>/throttle_cmd_valid' */
              /* BusAssignment: '<S44>/Bus Assignment' incorporates:
               *  Constant: '<S132>/Constant'
               *  Constant: '<S133>/Constant'
               *  Constant: '<S134>/Constant'
               *  Constant: '<S135>/Constant'
               *  Constant: '<S136>/Constant'
               *  Constant: '<S137>/Constant'
               *  Constant: '<S138>/Constant'
               *  Constant: '<S157>/Constant'
               *  Constant: '<S160>/Constant'
               *  DataTypeConversion: '<S120>/Data Type Conversion10'
               *  DataTypeConversion: '<S120>/Data Type Conversion6'
               *  DataTypeConversion: '<S120>/Data Type Conversion7'
               *  DataTypeConversion: '<S120>/Data Type Conversion9'
               *  Inport: '<Root>/Auto_Cmd'
               *  MATLAB Function: '<S141>/bit_shift'
               *  MATLAB Function: '<S142>/bit_shift'
               *  MATLAB Function: '<S143>/bit_shift'
               *  MATLAB Function: '<S145>/bit_shift'
               *  MATLAB Function: '<S146>/bit_shift'
               *  MATLAB Function: '<S147>/bit_shift'
               *  MATLAB Function: '<S148>/bit_shift'
               *  MATLAB Function: '<S149>/bit_shift'
               *  MATLAB Function: '<S150>/bit_shift'
               *  MATLAB Function: '<S151>/bit_shift'
               *  MATLAB Function: '<S152>/bit_shift'
               *  MATLAB Function: '<S153>/bit_shift'
               *  Outport: '<Root>/FMS_Out'
               *  RelationalOperator: '<S132>/Compare'
               *  RelationalOperator: '<S133>/Compare'
               *  RelationalOperator: '<S134>/Compare'
               *  RelationalOperator: '<S135>/Compare'
               *  RelationalOperator: '<S136>/Compare'
               *  RelationalOperator: '<S137>/Compare'
               *  RelationalOperator: '<S138>/Compare'
               *  RelationalOperator: '<S157>/Compare'
               *  RelationalOperator: '<S160>/Compare'
               *  S-Function (sfix_bitop): '<S120>/p_cmd'
               *  S-Function (sfix_bitop): '<S120>/phi_cmd'
               *  S-Function (sfix_bitop): '<S120>/psi_psi_rate_cmd'
               *  S-Function (sfix_bitop): '<S120>/q_cmd'
               *  S-Function (sfix_bitop): '<S120>/r_cmd'
               *  S-Function (sfix_bitop): '<S120>/theta_cmd'
               *  S-Function (sfix_bitop): '<S120>/throttle_cmd'
               *  S-Function (sfix_bitop): '<S139>/z_w_cmd'
               *  S-Function (sfix_bitop): '<S140>/az_cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy'
               *  Sum: '<S120>/Add'
               */
              FMS_Y.FMS_Out.cmd_mask = (uint16_T)((((((((((((uint32_T)(uint16_T)
                ((uint32_T)(((FMS_U.Auto_Cmd.cmd_mask & 2U) > 0U) << 1) +
                 (uint32_T)((FMS_U.Auto_Cmd.cmd_mask & 1U) > 0U)) + (uint16_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 4U) > 0U) << 2)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 8U) > 0U) << 3)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 16U) > 0U) << 4)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 96U) > 0U) << 5)) + (uint32_T)
                (rtb_LogicalOperator_i << 6)) + (uint32_T)(rtb_Compare_og << 7))
                + (uint32_T)(((FMS_U.Auto_Cmd.cmd_mask & 33280U) > 0U) << 8)) +
                (uint32_T)(rtb_LogicalOperator_o << 9)) + (uint32_T)
                (rtb_Switch_p_idx_1 << 10)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 262144U) > 0U) << 11)) + (uint32_T)
                (((FMS_U.Auto_Cmd.cmd_mask & 524288U) > 0U) << 12));

              /* End of Outputs for SubSystem: '<S120>/throttle_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/az_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/ay_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/ax_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/w_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/v_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/u_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/psi_rate_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/theta_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/phi_cmd_valid' */
              /* End of Outputs for SubSystem: '<S120>/r_cmd_valid' */
              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              /* End of Outputs for SubSystem: '<S120>/q_cmd_valid' */
              /* End of Outputs for SubSystem: '<S37>/Offboard' */
            }
            break;

           case 1:
            {
              boolean_T rtb_Compare_og;
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
                 *  Chart: '<S79>/Motion Status'
                 *  Chart: '<S89>/Motion State'
                 *  Delay: '<S51>/Delay'
                 *  Delay: '<S71>/Delay'
                 *  DiscreteIntegrator: '<S115>/Discrete-Time Integrator'
                 *  DiscreteIntegrator: '<S54>/Integrator'
                 *  DiscreteIntegrator: '<S54>/Integrator1'
                 */
                FMS_DW.icLoad = true;
                FMS_DW.l1_heading = 0.0F;
                FMS_DW.icLoad_k = true;
                FMS_DW.Integrator1_IC_LOADING = 1U;
                FMS_DW.Integrator_DSTATE = 0.0F;
                FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_n);
                FMS_MotionStatus_Reset(&rtb_state_ee, &FMS_DW.sf_MotionStatus_j);

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
              rtb_Compare_og = (FMS_B.wp_index != FMS_DW.DelayInput1_DSTATE_pe);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Outputs for Resettable SubSystem: '<S43>/Mission_SubSystem' incorporates:
               *  ResetPort: '<S47>/Reset'
               */
              if (rtb_Compare_og && (FMS_PrevZCX.Mission_SubSystem_Reset_ZCE !=
                                     POS_ZCSIG)) {
                /* SwitchCase: '<S88>/Switch Case' */
                FMS_DW.SwitchCase_ActiveSubsystem_a = -1;

                /* SwitchCase: '<S78>/Switch Case' */
                FMS_DW.SwitchCase_ActiveSubsystem_e = -1;

                /* InitializeConditions for Delay: '<S71>/Delay' */
                FMS_DW.icLoad = true;

                /* InitializeConditions for DiscreteIntegrator: '<S115>/Discrete-Time Integrator' */
                FMS_DW.l1_heading = 0.0F;

                /* InitializeConditions for Delay: '<S51>/Delay' */
                FMS_DW.icLoad_k = true;

                /* InitializeConditions for DiscreteIntegrator: '<S54>/Integrator1' */
                FMS_DW.Integrator1_IC_LOADING = 1U;

                /* InitializeConditions for DiscreteIntegrator: '<S54>/Integrator' */
                FMS_DW.Integrator_DSTATE = 0.0F;

                /* SystemReset for Chart: '<S89>/Motion State' */
                FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_n);

                /* SystemReset for Chart: '<S79>/Motion Status' */
                FMS_MotionStatus_Reset(&rtb_state_ee, &FMS_DW.sf_MotionStatus_j);
              }

              FMS_PrevZCX.Mission_SubSystem_Reset_ZCE = rtb_Compare_og;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Reshape: '<S50>/Reshape2' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_TmpSignalConversionAtMath_j[0] = FMS_U.INS_Out.x_R;
              rtb_TmpSignalConversionAtMath_j[1] = FMS_U.INS_Out.y_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Delay: '<S71>/Delay' incorporates:
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
              /* Sum: '<S67>/Sum' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_MathFunction_c_idx_0 = FMS_U.INS_Out.x_R -
                FMS_B.Cmd_In.sp_waypoint[0];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              rtb_MathFunction_ec[0] = rtb_MathFunction_c_idx_0 *
                rtb_MathFunction_c_idx_0;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S67>/Sum' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S75>/Square'
               *  Product: '<S112>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              rtb_MathFunction_c_idx_0 = FMS_U.INS_Out.y_R -
                FMS_B.Cmd_In.sp_waypoint[1];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sqrt: '<S75>/Sqrt' incorporates:
               *  Math: '<S75>/Square'
               *  Sum: '<S75>/Sum of Elements'
               */
              rtb_Square2 = sqrtf(rtb_MathFunction_c_idx_0 *
                                  rtb_MathFunction_c_idx_0 +
                                  rtb_MathFunction_ec[0]);

              /* Switch: '<S67>/Switch' incorporates:
               *  Constant: '<S67>/vel'
               */
              if (rtb_Square2 > FMS_PARAM.L1) {
                rtb_Switch_k = FMS_PARAM.CRUISE_SPEED;
              } else {
                /* Gain: '<S67>/Gain' */
                rtb_Switch_k = 0.5F * rtb_Square2;

                /* Saturate: '<S67>/Saturation' */
                if (rtb_Switch_k > FMS_PARAM.CRUISE_SPEED) {
                  rtb_Switch_k = FMS_PARAM.CRUISE_SPEED;
                } else if (rtb_Switch_k < 0.5F) {
                  rtb_Switch_k = 0.5F;
                }

                /* End of Saturate: '<S67>/Saturation' */
              }

              /* End of Switch: '<S67>/Switch' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Chart: '<S89>/Motion State' incorporates:
               *  Constant: '<S89>/Constant'
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S89>/Square'
               *  Math: '<S89>/Square1'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sqrt: '<S89>/Sqrt'
               *  Sum: '<S89>/Add'
               */
              FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
                FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                              &FMS_DW.sf_MotionState_n);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* SwitchCase: '<S88>/Switch Case' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Inport: '<Root>/Pilot_Cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy2'
               */
              rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_a;
              switch (rtb_state_ee) {
               case MotionState_Hold:
                FMS_DW.SwitchCase_ActiveSubsystem_a = 0;
                break;

               case MotionState_Brake:
                FMS_DW.SwitchCase_ActiveSubsystem_a = 1;
                break;

               default:
                FMS_DW.SwitchCase_ActiveSubsystem_a = 2;
                break;
              }

              switch (FMS_DW.SwitchCase_ActiveSubsystem_a) {
               case 0:
                if (FMS_DW.SwitchCase_ActiveSubsystem_a != rtPrevAction) {
                  /* SystemReset for IfAction SubSystem: '<S88>/Hold Control' incorporates:
                   *  ActionPort: '<S91>/Action Port'
                   */
                  /* SystemReset for SwitchCase: '<S88>/Switch Case' */
                  FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_d);

                  /* End of SystemReset for SubSystem: '<S88>/Hold Control' */
                }

                /* Outputs for IfAction SubSystem: '<S88>/Hold Control' incorporates:
                 *  ActionPort: '<S91>/Action Port'
                 */
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                                  FMS_U.INS_Out.psi, FMS_B.Merge_nj,
                                  &FMS_ConstB.HoldControl_d,
                                  &FMS_DW.HoldControl_d);

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                /* End of Outputs for SubSystem: '<S88>/Hold Control' */
                break;

               case 1:
                /* Outputs for IfAction SubSystem: '<S88>/Brake Control' incorporates:
                 *  ActionPort: '<S90>/Action Port'
                 */
                FMS_BrakeControl_h(FMS_B.Merge_nj);

                /* End of Outputs for SubSystem: '<S88>/Brake Control' */
                break;

               default:
                if (FMS_DW.SwitchCase_ActiveSubsystem_a != rtPrevAction) {
                  /* SystemReset for IfAction SubSystem: '<S88>/Move Control' incorporates:
                   *  ActionPort: '<S92>/Action Port'
                   */
                  /* SystemReset for SwitchCase: '<S88>/Switch Case' */
                  FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_cp);

                  /* End of SystemReset for SubSystem: '<S88>/Move Control' */
                }

                /* Outputs for IfAction SubSystem: '<S88>/Move Control' incorporates:
                 *  ActionPort: '<S92>/Action Port'
                 */
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                                  FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_nj,
                                  &FMS_ConstB.MoveControl_cp,
                                  &FMS_DW.MoveControl_cp);

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                /* End of Outputs for SubSystem: '<S88>/Move Control' */
                break;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Chart: '<S79>/Motion Status' incorporates:
               *  Abs: '<S79>/Abs'
               *  Constant: '<S79>/Constant'
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              FMS_MotionStatus(0.0F, fabsf(FMS_U.INS_Out.vd), &rtb_state_ee,
                               &FMS_DW.sf_MotionStatus_j);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* SwitchCase: '<S78>/Switch Case' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Inport: '<Root>/Pilot_Cmd'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy2'
               */
              rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_e;
              switch (rtb_state_ee) {
               case MotionState_Hold:
                FMS_DW.SwitchCase_ActiveSubsystem_e = 0;
                break;

               case MotionState_Brake:
                FMS_DW.SwitchCase_ActiveSubsystem_e = 1;
                break;

               default:
                FMS_DW.SwitchCase_ActiveSubsystem_e = 2;
                break;
              }

              switch (FMS_DW.SwitchCase_ActiveSubsystem_e) {
               case 0:
                if (FMS_DW.SwitchCase_ActiveSubsystem_e != rtPrevAction) {
                  /* SystemReset for IfAction SubSystem: '<S78>/Hold Control' incorporates:
                   *  ActionPort: '<S81>/Action Port'
                   */
                  /* SystemReset for SwitchCase: '<S78>/Switch Case' */
                  FMS_HoldControl_Reset(&FMS_DW.HoldControl_a);

                  /* End of SystemReset for SubSystem: '<S78>/Hold Control' */
                }

                /* Outputs for IfAction SubSystem: '<S78>/Hold Control' incorporates:
                 *  ActionPort: '<S81>/Action Port'
                 */
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                FMS_HoldControl(FMS_U.INS_Out.h_R, &FMS_B.Merge_e,
                                &FMS_DW.HoldControl_a);

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                /* End of Outputs for SubSystem: '<S78>/Hold Control' */
                break;

               case 1:
                /* Outputs for IfAction SubSystem: '<S78>/Brake Control' incorporates:
                 *  ActionPort: '<S80>/Action Port'
                 */
                FMS_BrakeControl(&FMS_B.Merge_e);

                /* End of Outputs for SubSystem: '<S78>/Brake Control' */
                break;

               default:
                if (FMS_DW.SwitchCase_ActiveSubsystem_e != rtPrevAction) {
                  /* SystemReset for IfAction SubSystem: '<S78>/Move Control' incorporates:
                   *  ActionPort: '<S82>/Action Port'
                   */
                  /* SystemReset for SwitchCase: '<S78>/Switch Case' */
                  FMS_MoveControl_Reset(&FMS_DW.MoveControl_m);

                  /* End of SystemReset for SubSystem: '<S78>/Move Control' */
                }

                /* Outputs for IfAction SubSystem: '<S78>/Move Control' incorporates:
                 *  ActionPort: '<S82>/Action Port'
                 */
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                FMS_MoveControl(FMS_U.Pilot_Cmd.stick_throttle, &FMS_B.Merge_e,
                                &FMS_ConstB.MoveControl_m, &FMS_DW.MoveControl_m);

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                /* End of Outputs for SubSystem: '<S78>/Move Control' */
                break;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S47>/Sum' incorporates:
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               *  Sum: '<S72>/Sum1'
               *  Switch: '<S49>/Switch'
               */
              rtb_Divide_o_idx_2 = FMS_B.Cmd_In.sp_waypoint[0] -
                FMS_B.Cmd_In.cur_waypoint[0];
              rtb_Gain_fj = FMS_B.Cmd_In.sp_waypoint[1] -
                FMS_B.Cmd_In.cur_waypoint[1];

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Math: '<S65>/Math Function' incorporates:
               *  Sum: '<S47>/Sum'
               */
              rtb_TmpSignalConversionAtSqua_d[0] = rtb_Gain_fj * rtb_Gain_fj;
              rtb_TmpSignalConversionAtSqua_d[1] = rtb_Divide_o_idx_2 *
                rtb_Divide_o_idx_2;

              /* Sum: '<S65>/Sum of Elements' */
              rtb_Square2 = rtb_TmpSignalConversionAtSqua_d[0] +
                rtb_TmpSignalConversionAtSqua_d[1];

              /* Math: '<S65>/Math Function1' incorporates:
               *  Sum: '<S65>/Sum of Elements'
               *
               * About '<S65>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Square2 < 0.0F) {
                rtb_a_k = -sqrtf(fabsf(rtb_Square2));
              } else {
                rtb_a_k = sqrtf(rtb_Square2);
              }

              /* End of Math: '<S65>/Math Function1' */

              /* Switch: '<S65>/Switch' incorporates:
               *  Constant: '<S65>/Constant'
               *  Product: '<S65>/Product'
               *  Sum: '<S47>/Sum'
               */
              if (rtb_a_k > 0.0F) {
                rtb_MatrixConcatenate3[0] = rtb_Gain_fj;
                rtb_MatrixConcatenate3[1] = rtb_Divide_o_idx_2;
                rtb_MatrixConcatenate3[2] = rtb_a_k;
              } else {
                rtb_MatrixConcatenate3[0] = 0.0F;
                rtb_MatrixConcatenate3[1] = 0.0F;
                rtb_MatrixConcatenate3[2] = 1.0F;
              }

              /* End of Switch: '<S65>/Switch' */

              /* Product: '<S65>/Divide' */
              rtb_MathFunction_c_idx_0 = rtb_MatrixConcatenate3[0] /
                rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S52>/Dot Product' incorporates:
               *  Product: '<S64>/Divide'
               */
              rtb_Square2 = FMS_ConstB.Divide[0] * rtb_MathFunction_c_idx_0;
              rtb_MathFunction_ec[0] = rtb_MathFunction_c_idx_0;

              /* Product: '<S65>/Divide' */
              rtb_MathFunction_c_idx_0 = rtb_MatrixConcatenate3[1] /
                rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S52>/Dot Product' incorporates:
               *  Product: '<S64>/Divide'
               */
              rtb_Divide_o_idx_1 = FMS_ConstB.Divide[1] *
                rtb_MathFunction_c_idx_0 + rtb_Square2;
              rtb_MathFunction_ec[1] = rtb_MathFunction_c_idx_0;

              /* Sum: '<S63>/Subtract' incorporates:
               *  Product: '<S63>/Multiply'
               *  Product: '<S63>/Multiply1'
               *  Product: '<S65>/Divide'
               */
              rtb_Square2 = rtb_MathFunction_ec[0] * FMS_ConstB.Divide[1] -
                FMS_ConstB.Divide[0] * rtb_MathFunction_c_idx_0;

              /* Signum: '<S52>/Sign1' */
              if (rtb_Square2 < 0.0F) {
                rtb_a_k = -1.0F;
              } else {
                rtb_a_k = (real32_T)(rtb_Square2 > 0.0F);
              }

              /* End of Signum: '<S52>/Sign1' */

              /* Trigonometry: '<S52>/Acos' incorporates:
               *  DotProduct: '<S52>/Dot Product'
               */
              if (rtb_Divide_o_idx_1 > 1.0F) {
                rtb_Divide_o_idx_1 = 1.0F;
              } else if (rtb_Divide_o_idx_1 < -1.0F) {
                rtb_Divide_o_idx_1 = -1.0F;
              }

              /* Switch: '<S52>/Switch2' incorporates:
               *  Constant: '<S52>/Constant4'
               */
              if (rtb_a_k == 0.0F) {
                rtb_a_k = 1.0F;
              }

              /* Product: '<S52>/Multiply' incorporates:
               *  Switch: '<S52>/Switch2'
               *  Trigonometry: '<S52>/Acos'
               */
              rtb_a_k *= acosf(rtb_Divide_o_idx_1);

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Math: '<S56>/Rem' incorporates:
               *  Constant: '<S56>/Constant1'
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sum: '<S51>/Sum1'
               */
              rtb_Divide_o_idx_1 = rt_remf(rtb_a_k - FMS_U.INS_Out.psi,
                6.28318548F);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Switch: '<S56>/Switch' incorporates:
               *  Abs: '<S56>/Abs'
               *  Constant: '<S56>/Constant'
               *  Constant: '<S62>/Constant'
               *  Product: '<S56>/Multiply'
               *  RelationalOperator: '<S62>/Compare'
               *  Signum: '<S56>/Sign'
               *  Sum: '<S56>/Add'
               */
              if (fabsf(rtb_Divide_o_idx_1) > 3.14159274F) {
                /* Signum: '<S56>/Sign' */
                if (rtb_Divide_o_idx_1 < 0.0F) {
                  rtb_Square2 = -1.0F;
                } else {
                  rtb_Square2 = (real32_T)(rtb_Divide_o_idx_1 > 0.0F);
                }

                rtb_Divide_o_idx_1 -= 6.28318548F * rtb_Square2;
              }

              /* End of Switch: '<S56>/Switch' */

              /* Abs: '<S49>/Abs' */
              rtb_Divide_o_idx_1 = fabsf(rtb_Divide_o_idx_1);

              /* Switch: '<S49>/Switch' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S71>/Multiply'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               *  Sum: '<S71>/Sum'
               *  Sum: '<S72>/Sum'
               */
              if (rtb_Divide_o_idx_1 > 0.34906584F) {
                /* Saturate: '<S88>/Saturation1' incorporates:
                 *  Merge: '<S88>/Merge'
                 */
                if (FMS_B.Merge_nj[0] > FMS_PARAM.VEL_XY_LIM) {
                  rtb_MatrixConcatenate3[0] = FMS_PARAM.VEL_XY_LIM;
                } else if (FMS_B.Merge_nj[0] < -FMS_PARAM.VEL_XY_LIM) {
                  rtb_MatrixConcatenate3[0] = -FMS_PARAM.VEL_XY_LIM;
                } else {
                  rtb_MatrixConcatenate3[0] = FMS_B.Merge_nj[0];
                }

                if (FMS_B.Merge_nj[1] > FMS_PARAM.VEL_XY_LIM) {
                  rtb_MatrixConcatenate3[1] = FMS_PARAM.VEL_XY_LIM;
                } else if (FMS_B.Merge_nj[1] < -FMS_PARAM.VEL_XY_LIM) {
                  rtb_MatrixConcatenate3[1] = -FMS_PARAM.VEL_XY_LIM;
                } else {
                  rtb_MatrixConcatenate3[1] = FMS_B.Merge_nj[1];
                }

                /* End of Saturate: '<S88>/Saturation1' */

                /* Saturate: '<S78>/Saturation1' */
                if (FMS_B.Merge_e > FMS_PARAM.VEL_Z_LIM) {
                  rtb_MatrixConcatenate3[2] = FMS_PARAM.VEL_Z_LIM;
                } else if (FMS_B.Merge_e < -FMS_PARAM.VEL_Z_LIM) {
                  rtb_MatrixConcatenate3[2] = -FMS_PARAM.VEL_Z_LIM;
                } else {
                  rtb_MatrixConcatenate3[2] = FMS_B.Merge_e;
                }

                /* End of Saturate: '<S78>/Saturation1' */
              } else {
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                /* Sum: '<S71>/Sum' incorporates:
                 *  Delay: '<S71>/Delay'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 */
                rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[0] -
                  FMS_DW.Delay_DSTATE[0];

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

                /* SignalConversion generated from: '<S116>/Math Function' */
                rtb_MatrixConcatenate3[0] = rtb_Divide_o_idx_1;
                rtb_Saturation1_g[0] = rtb_Divide_o_idx_1;

                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                /* Sum: '<S71>/Sum' incorporates:
                 *  Delay: '<S71>/Delay'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 */
                rtb_Divide_o_idx_1 = FMS_B.Cmd_In.sp_waypoint[1] -
                  FMS_DW.Delay_DSTATE[1];

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

                /* SignalConversion generated from: '<S118>/Vector Concatenate2' incorporates:
                 *  Constant: '<S118>/Constant4'
                 */
                rtb_Transpose[5] = 0.0F;

                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                /* Gain: '<S117>/Gain' incorporates:
                 *  DiscreteIntegrator: '<S115>/Discrete-Time Integrator'
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  Sum: '<S115>/Add'
                 */
                rtb_Square2 = -(FMS_U.INS_Out.psi - FMS_DW.l1_heading);

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

                /* Trigonometry: '<S118>/Trigonometric Function3' incorporates:
                 *  Trigonometry: '<S118>/Trigonometric Function1'
                 */
                rtb_Divide_o_idx_0 = arm_cos_f32(rtb_Square2);
                rtb_Transpose[4] = rtb_Divide_o_idx_0;

                /* Trigonometry: '<S118>/Trigonometric Function2' incorporates:
                 *  Trigonometry: '<S118>/Trigonometric Function'
                 */
                rtb_Square2 = arm_sin_f32(rtb_Square2);

                /* Gain: '<S118>/Gain' incorporates:
                 *  Trigonometry: '<S118>/Trigonometric Function2'
                 */
                rtb_Transpose[3] = -rtb_Square2;

                /* SignalConversion generated from: '<S118>/Vector Concatenate1' incorporates:
                 *  Constant: '<S118>/Constant3'
                 */
                rtb_Transpose[2] = 0.0F;

                /* Trigonometry: '<S118>/Trigonometric Function' */
                rtb_Transpose[1] = rtb_Square2;

                /* Trigonometry: '<S118>/Trigonometric Function1' */
                rtb_Transpose[0] = rtb_Divide_o_idx_0;

                /* SignalConversion generated from: '<S118>/Vector Concatenate' incorporates:
                 *  Concatenate: '<S118>/Vector Concatenate3'
                 */
                rtb_Transpose[6] = FMS_ConstB.VectorConcatenate3[0];
                rtb_Transpose[7] = FMS_ConstB.VectorConcatenate3[1];
                rtb_Transpose[8] = FMS_ConstB.VectorConcatenate3[2];

                /* Sum: '<S116>/Sum of Elements' incorporates:
                 *  Math: '<S116>/Math Function'
                 *  SignalConversion generated from: '<S116>/Math Function'
                 */
                rtb_Square2 = rtb_MatrixConcatenate3[0] *
                  rtb_MatrixConcatenate3[0] + rtb_Divide_o_idx_1 *
                  rtb_Divide_o_idx_1;

                /* Math: '<S116>/Math Function1' incorporates:
                 *  Sum: '<S116>/Sum of Elements'
                 *
                 * About '<S116>/Math Function1':
                 *  Operator: sqrt
                 */
                if (rtb_Square2 < 0.0F) {
                  rtb_Square2 = -sqrtf(fabsf(rtb_Square2));
                } else {
                  rtb_Square2 = sqrtf(rtb_Square2);
                }

                /* End of Math: '<S116>/Math Function1' */

                /* Switch: '<S116>/Switch' incorporates:
                 *  Constant: '<S116>/Constant'
                 *  Product: '<S116>/Product'
                 */
                if (rtb_Square2 > 0.0F) {
                  rtb_Divide_o_idx_0 = rtb_Saturation1_g[0];
                } else {
                  rtb_Divide_o_idx_0 = 0.0F;
                  rtb_Divide_o_idx_1 = 0.0F;
                  rtb_Square2 = 1.0F;
                }

                /* End of Switch: '<S116>/Switch' */

                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                /* Sum: '<S72>/Sum' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 */
                rtb_Saturation1_g[1] = FMS_U.INS_Out.y_R -
                  FMS_B.Cmd_In.cur_waypoint[1];
                rtb_MathFunction_c_idx_0 = FMS_U.INS_Out.x_R -
                  FMS_B.Cmd_In.cur_waypoint[0];

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

                /* Product: '<S114>/Multiply2' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S116>/Divide'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S72>/Sum'
                 */
                rtb_Divide_o_idx_0 = rtb_Divide_o_idx_0 / rtb_Square2 *
                  rtb_Switch_k;
                rtb_Divide_o_idx_1 = rtb_Divide_o_idx_1 / rtb_Square2 *
                  rtb_Switch_k;

                /* Product: '<S71>/Multiply' incorporates:
                 *  Concatenate: '<S118>/Vector Concatenate'
                 */
                for (i = 0; i < 3; i++) {
                  rtb_Transpose_0[i] = rtb_Transpose[i + 3] * rtb_Divide_o_idx_1
                    + rtb_Transpose[i] * rtb_Divide_o_idx_0;
                }

                /* Product: '<S72>/Divide' incorporates:
                 *  Math: '<S73>/Square'
                 *  Math: '<S74>/Square'
                 *  Sqrt: '<S73>/Sqrt'
                 *  Sqrt: '<S74>/Sqrt'
                 *  Sum: '<S73>/Sum of Elements'
                 *  Sum: '<S74>/Sum of Elements'
                 */
                rtb_Divide_o_idx_1 = sqrtf(rtb_MathFunction_c_idx_0 *
                  rtb_MathFunction_c_idx_0 + rtb_Saturation1_g[1] *
                  rtb_Saturation1_g[1]) / sqrtf(rtb_Gain_fj * rtb_Gain_fj +
                  rtb_Divide_o_idx_2 * rtb_Divide_o_idx_2);

                /* Saturate: '<S72>/Saturation' */
                if (rtb_Divide_o_idx_1 > 1.0F) {
                  rtb_Divide_o_idx_1 = 1.0F;
                }

                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                /* Gain: '<S66>/Gain' incorporates:
                 *  Inport: '<Root>/INS_Out'
                 *  Product: '<S72>/Multiply'
                 *  Saturate: '<S72>/Saturation'
                 *  SignalConversion generated from: '<S32>/Signal Copy1'
                 *  SignalConversion generated from: '<S32>/Signal Copy3'
                 *  Sum: '<S66>/Sum2'
                 *  Sum: '<S72>/Add'
                 *  Sum: '<S72>/Subtract'
                 */
                rtb_Divide_o_idx_1 = (FMS_U.INS_Out.h_R -
                                      ((FMS_B.Cmd_In.sp_waypoint[2] -
                  FMS_B.Cmd_In.cur_waypoint[2]) * rtb_Divide_o_idx_1 +
                  FMS_B.Cmd_In.cur_waypoint[2])) * FMS_PARAM.Z_P;

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                rtb_MatrixConcatenate3[0] = rtb_Transpose_0[0];
                rtb_MatrixConcatenate3[1] = rtb_Transpose_0[1];

                /* Saturate: '<S66>/Saturation1' incorporates:
                 *  Product: '<S71>/Multiply'
                 */
                if (rtb_Divide_o_idx_1 > FMS_PARAM.VEL_Z_LIM) {
                  rtb_MatrixConcatenate3[2] = FMS_PARAM.VEL_Z_LIM;
                } else if (rtb_Divide_o_idx_1 < -FMS_PARAM.VEL_Z_LIM) {
                  rtb_MatrixConcatenate3[2] = -FMS_PARAM.VEL_Z_LIM;
                } else {
                  rtb_MatrixConcatenate3[2] = rtb_Divide_o_idx_1;
                }

                /* End of Saturate: '<S66>/Saturation1' */
              }

              /* Delay: '<S51>/Delay' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              if (FMS_DW.icLoad_k) {
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                FMS_DW.Delay_DSTATE_h = FMS_U.INS_Out.psi;

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              }

              /* DiscreteIntegrator: '<S54>/Integrator1' incorporates:
               *  Delay: '<S51>/Delay'
               */
              if (FMS_DW.Integrator1_IC_LOADING != 0) {
                FMS_DW.Integrator1_DSTATE = FMS_DW.Delay_DSTATE_h;
              }

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Math: '<S58>/Rem' incorporates:
               *  Constant: '<S58>/Constant1'
               *  DiscreteIntegrator: '<S54>/Integrator1'
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sum: '<S53>/Sum'
               */
              rtb_Gain_fj = rt_remf(FMS_DW.Integrator1_DSTATE -
                                    FMS_U.INS_Out.psi, 6.28318548F);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Switch: '<S58>/Switch' incorporates:
               *  Abs: '<S58>/Abs'
               *  Constant: '<S58>/Constant'
               *  Constant: '<S59>/Constant'
               *  Product: '<S58>/Multiply'
               *  RelationalOperator: '<S59>/Compare'
               *  Signum: '<S58>/Sign'
               *  Sum: '<S58>/Add'
               */
              if (fabsf(rtb_Gain_fj) > 3.14159274F) {
                /* Signum: '<S58>/Sign' */
                if (rtb_Gain_fj < 0.0F) {
                  rtb_Square2 = -1.0F;
                } else {
                  rtb_Square2 = (real32_T)(rtb_Gain_fj > 0.0F);
                }

                rtb_Gain_fj -= 6.28318548F * rtb_Square2;
              }

              /* End of Switch: '<S58>/Switch' */

              /* Gain: '<S53>/Gain2' */
              rtb_Divide_o_idx_1 = FMS_PARAM.YAW_P * rtb_Gain_fj;

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
              FMS_Y.FMS_Out.state = FMS_ConstB.DataTypeConversion1_b;
              FMS_Y.FMS_Out.ctrl_mode = FMS_ConstB.DataTypeConversion2_b;
              FMS_Y.FMS_Out.u_cmd = rtb_MatrixConcatenate3[0];
              FMS_Y.FMS_Out.v_cmd = rtb_MatrixConcatenate3[1];
              FMS_Y.FMS_Out.w_cmd = rtb_MatrixConcatenate3[2];

              /* Saturate: '<S53>/Saturation' */
              if (rtb_Divide_o_idx_1 > FMS_PARAM.YAW_RATE_LIM) {
                /* BusAssignment: '<S47>/Bus Assignment' incorporates:
                 *  BusAssignment: '<S34>/Bus Assignment'
                 *  Outport: '<Root>/FMS_Out'
                 */
                FMS_Y.FMS_Out.psi_rate_cmd = FMS_PARAM.YAW_RATE_LIM;
              } else if (rtb_Divide_o_idx_1 < -FMS_PARAM.YAW_RATE_LIM) {
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
                FMS_Y.FMS_Out.psi_rate_cmd = rtb_Divide_o_idx_1;
              }

              /* End of Saturate: '<S53>/Saturation' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* SignalConversion generated from: '<S107>/Square' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_TmpSignalConversionAtSqua_d[0] = FMS_U.INS_Out.vn;
              rtb_TmpSignalConversionAtSqua_d[1] = FMS_U.INS_Out.ve;

              /* Sum: '<S109>/Sum of Elements' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S109>/Math Function'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               *  Sum: '<S107>/Sum of Elements'
               */
              rtb_Square2 = FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
                FMS_U.INS_Out.ve * FMS_U.INS_Out.ve;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Math: '<S109>/Math Function1' incorporates:
               *  Sum: '<S109>/Sum of Elements'
               *
               * About '<S109>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Square2 < 0.0F) {
                rtb_Gain_fj = -sqrtf(fabsf(rtb_Square2));
              } else {
                rtb_Gain_fj = sqrtf(rtb_Square2);
              }

              /* End of Math: '<S109>/Math Function1' */

              /* Switch: '<S109>/Switch' incorporates:
               *  Constant: '<S109>/Constant'
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S109>/Product'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              if (rtb_Gain_fj > 0.0F) {
                /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
                rtb_MatrixConcatenate3[0] = FMS_U.INS_Out.vn;
                rtb_MatrixConcatenate3[1] = FMS_U.INS_Out.ve;

                /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
                rtb_MatrixConcatenate3[2] = rtb_Gain_fj;
              } else {
                rtb_MatrixConcatenate3[0] = 0.0F;
                rtb_MatrixConcatenate3[1] = 0.0F;
                rtb_MatrixConcatenate3[2] = 1.0F;
              }

              /* End of Switch: '<S109>/Switch' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* MATLAB Function: '<S69>/NearbyRefWP' incorporates:
               *  Constant: '<S47>/L1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              FMS_NearbyRefWP(&FMS_B.Cmd_In.sp_waypoint[0],
                              rtb_TmpSignalConversionAtMath_j, FMS_PARAM.L1,
                              rtb_TmpSignalConversionAtSqua_d, &rtb_Rem_i);

              /* MATLAB Function: '<S69>/SearchL1RefWP' incorporates:
               *  Constant: '<S47>/L1'
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              FMS_SearchL1RefWP(&FMS_B.Cmd_In.cur_waypoint[0],
                                &FMS_B.Cmd_In.sp_waypoint[0],
                                rtb_TmpSignalConversionAtMath_j, FMS_PARAM.L1,
                                rtb_MathFunction_ec, &rtb_Divide_o_idx_1);

              /* MATLAB Function: '<S69>/OutRegionRegWP' incorporates:
               *  SignalConversion generated from: '<S32>/Signal Copy3'
               */
              FMS_OutRegionRegWP(&FMS_B.Cmd_In.cur_waypoint[0],
                                 &FMS_B.Cmd_In.sp_waypoint[0],
                                 rtb_TmpSignalConversionAtMath_j,
                                 rtb_MathFunction_o);

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Switch: '<S69>/Switch1' incorporates:
               *  Constant: '<S101>/Constant'
               *  Constant: '<S102>/Constant'
               *  Product: '<S112>/Divide'
               *  RelationalOperator: '<S101>/Compare'
               *  RelationalOperator: '<S102>/Compare'
               *  Switch: '<S69>/Switch'
               */
              if (rtb_Rem_i > 0.0F) {
                rtb_MathFunction_ec[0] = rtb_TmpSignalConversionAtSqua_d[0];
                rtb_MathFunction_ec[1] = rtb_TmpSignalConversionAtSqua_d[1];
              } else if (rtb_Divide_o_idx_1 < 0.0F) {
                /* Product: '<S112>/Divide' incorporates:
                 *  Switch: '<S69>/Switch'
                 */
                rtb_MathFunction_ec[0] = rtb_MathFunction_o[0];
                rtb_MathFunction_ec[1] = rtb_MathFunction_o[1];
              }

              /* End of Switch: '<S69>/Switch1' */

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S70>/Subtract' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Product: '<S112>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_Divide_o_idx_0 = rtb_MathFunction_ec[0] - FMS_U.INS_Out.x_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              rtb_MathFunction_ec[0] = rtb_Divide_o_idx_0;
              rtb_TmpSignalConversionAtMath_j[0] = rtb_Divide_o_idx_0 *
                rtb_Divide_o_idx_0;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              /* Sum: '<S70>/Subtract' incorporates:
               *  Inport: '<Root>/INS_Out'
               *  Math: '<S110>/Math Function'
               *  Product: '<S112>/Divide'
               *  SignalConversion generated from: '<S32>/Signal Copy1'
               */
              rtb_Divide_o_idx_0 = rtb_MathFunction_ec[1] - FMS_U.INS_Out.y_R;

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

              /* Sum: '<S110>/Sum of Elements' incorporates:
               *  Math: '<S110>/Math Function'
               *  Sum: '<S108>/Sum of Elements'
               */
              rtb_Divide_o_idx_2 = rtb_Divide_o_idx_0 * rtb_Divide_o_idx_0 +
                rtb_TmpSignalConversionAtMath_j[0];

              /* Math: '<S110>/Math Function1' incorporates:
               *  Sum: '<S110>/Sum of Elements'
               *
               * About '<S110>/Math Function1':
               *  Operator: sqrt
               */
              if (rtb_Divide_o_idx_2 < 0.0F) {
                rtb_Gain_fj = -sqrtf(fabsf(rtb_Divide_o_idx_2));
              } else {
                rtb_Gain_fj = sqrtf(rtb_Divide_o_idx_2);
              }

              /* End of Math: '<S110>/Math Function1' */

              /* Switch: '<S110>/Switch' incorporates:
               *  Constant: '<S110>/Constant'
               *  Product: '<S110>/Product'
               *  Switch: '<S113>/Switch'
               */
              if (rtb_Gain_fj > 0.0F) {
                rtb_MathFunction_c_idx_0 = rtb_MathFunction_ec[0];
                rtb_Divide_o_idx_1 = rtb_Gain_fj;
              } else {
                rtb_MathFunction_c_idx_0 = 0.0F;
                rtb_Divide_o_idx_0 = 0.0F;
                rtb_Divide_o_idx_1 = 1.0F;
              }

              /* End of Switch: '<S110>/Switch' */

              /* Product: '<S109>/Divide' */
              rtb_TmpSignalConversionAtSqua_d[0] = rtb_MatrixConcatenate3[0] /
                rtb_MatrixConcatenate3[2];
              rtb_TmpSignalConversionAtSqua_d[1] = rtb_MatrixConcatenate3[1] /
                rtb_MatrixConcatenate3[2];

              /* Sum: '<S112>/Sum of Elements' incorporates:
               *  Math: '<S112>/Math Function'
               *  SignalConversion generated from: '<S112>/Math Function'
               */
              tmp_2 = rtb_TmpSignalConversionAtSqua_d[1] *
                rtb_TmpSignalConversionAtSqua_d[1] +
                rtb_TmpSignalConversionAtSqua_d[0] *
                rtb_TmpSignalConversionAtSqua_d[0];

              /* Math: '<S112>/Math Function1' incorporates:
               *  Sum: '<S112>/Sum of Elements'
               *
               * About '<S112>/Math Function1':
               *  Operator: sqrt
               */
              if (tmp_2 < 0.0F) {
                rtb_Gain_fj = -sqrtf(fabsf(tmp_2));
              } else {
                rtb_Gain_fj = sqrtf(tmp_2);
              }

              /* End of Math: '<S112>/Math Function1' */

              /* Switch: '<S112>/Switch' incorporates:
               *  Constant: '<S112>/Constant'
               *  Product: '<S112>/Product'
               */
              if (rtb_Gain_fj > 0.0F) {
                rtb_MatrixConcatenate3[0] = rtb_TmpSignalConversionAtSqua_d[1];
                rtb_MatrixConcatenate3[1] = rtb_TmpSignalConversionAtSqua_d[0];
                rtb_MatrixConcatenate3[2] = rtb_Gain_fj;
              } else {
                rtb_MatrixConcatenate3[0] = 0.0F;
                rtb_MatrixConcatenate3[1] = 0.0F;
                rtb_MatrixConcatenate3[2] = 1.0F;
              }

              /* End of Switch: '<S112>/Switch' */

              /* Product: '<S110>/Divide' incorporates:
               *  Product: '<S113>/Divide'
               */
              rtb_TmpSignalConversionAtSqua_d[0] = rtb_MathFunction_c_idx_0 /
                rtb_Divide_o_idx_1;
              rtb_TmpSignalConversionAtSqua_d[1] = rtb_Divide_o_idx_0 /
                rtb_Divide_o_idx_1;

              /* Sum: '<S113>/Sum of Elements' incorporates:
               *  Math: '<S113>/Math Function'
               *  SignalConversion generated from: '<S113>/Math Function'
               */
              tmp_2 = rtb_TmpSignalConversionAtSqua_d[1] *
                rtb_TmpSignalConversionAtSqua_d[1] +
                rtb_TmpSignalConversionAtSqua_d[0] *
                rtb_TmpSignalConversionAtSqua_d[0];

              /* Math: '<S113>/Math Function1' incorporates:
               *  Sum: '<S113>/Sum of Elements'
               *
               * About '<S113>/Math Function1':
               *  Operator: sqrt
               */
              if (tmp_2 < 0.0F) {
                rtb_Gain_fj = -sqrtf(fabsf(tmp_2));
              } else {
                rtb_Gain_fj = sqrtf(tmp_2);
              }

              /* End of Math: '<S113>/Math Function1' */

              /* Switch: '<S113>/Switch' incorporates:
               *  Constant: '<S113>/Constant'
               *  Product: '<S113>/Product'
               */
              if (rtb_Gain_fj > 0.0F) {
                rtb_MathFunction_c_idx_0 = rtb_TmpSignalConversionAtSqua_d[1];
                rtb_Divide_o_idx_0 = rtb_TmpSignalConversionAtSqua_d[0];
                rtb_Divide_o_idx_1 = rtb_Gain_fj;
              } else {
                rtb_MathFunction_c_idx_0 = 0.0F;
                rtb_Divide_o_idx_0 = 0.0F;
                rtb_Divide_o_idx_1 = 1.0F;
              }

              /* End of Switch: '<S113>/Switch' */

              /* Product: '<S113>/Divide' */
              tmp_2 = rtb_MathFunction_c_idx_0 / rtb_Divide_o_idx_1;

              /* Product: '<S112>/Divide' */
              rtb_MathFunction_c_idx_0 = rtb_MatrixConcatenate3[0] /
                rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S106>/Dot Product' */
              rtb_Rem_i = rtb_MathFunction_c_idx_0 * tmp_2;
              rtb_TmpSignalConversionAtSqua_d[0] = tmp_2;
              rtb_MathFunction_ec[0] = rtb_MathFunction_c_idx_0;

              /* Product: '<S113>/Divide' incorporates:
               *  Product: '<S112>/Divide'
               */
              tmp_2 = rtb_Divide_o_idx_0 / rtb_Divide_o_idx_1;

              /* Product: '<S112>/Divide' */
              rtb_MathFunction_c_idx_0 = rtb_MatrixConcatenate3[1] /
                rtb_MatrixConcatenate3[2];

              /* DotProduct: '<S106>/Dot Product' */
              rtb_Rem_i += rtb_MathFunction_c_idx_0 * tmp_2;

              /* Sqrt: '<S107>/Sqrt' */
              rtb_Gain_fj = sqrtf(rtb_Square2);

              /* Gain: '<S70>/Gain' incorporates:
               *  Math: '<S70>/Square'
               */
              rtb_Divide_o_idx_1 = rtb_Gain_fj * rtb_Gain_fj * 2.0F;

              /* Sum: '<S111>/Subtract' incorporates:
               *  Product: '<S111>/Multiply'
               *  Product: '<S111>/Multiply1'
               */
              rtb_Square2 = rtb_TmpSignalConversionAtSqua_d[0] *
                rtb_MathFunction_c_idx_0 - rtb_MathFunction_ec[0] * tmp_2;

              /* Signum: '<S106>/Sign1' */
              if (rtb_Square2 < 0.0F) {
                rtb_Gain_fj = -1.0F;
              } else {
                rtb_Gain_fj = (real32_T)(rtb_Square2 > 0.0F);
              }

              /* End of Signum: '<S106>/Sign1' */

              /* Trigonometry: '<S106>/Acos' incorporates:
               *  DotProduct: '<S106>/Dot Product'
               */
              if (rtb_Rem_i > 1.0F) {
                rtb_Rem_i = 1.0F;
              } else if (rtb_Rem_i < -1.0F) {
                rtb_Rem_i = -1.0F;
              }

              /* Switch: '<S106>/Switch2' incorporates:
               *  Constant: '<S106>/Constant4'
               */
              if (rtb_Gain_fj == 0.0F) {
                rtb_Gain_fj = 1.0F;
              }

              /* Product: '<S106>/Multiply' incorporates:
               *  Switch: '<S106>/Switch2'
               *  Trigonometry: '<S106>/Acos'
               */
              rtb_Gain_fj *= acosf(rtb_Rem_i);

              /* Saturate: '<S70>/Saturation' */
              if (rtb_Gain_fj > 1.57079637F) {
                rtb_Divide_o_idx_0 = 1.57079637F;
              } else if (rtb_Gain_fj < -1.57079637F) {
                rtb_Divide_o_idx_0 = -1.57079637F;
              } else {
                rtb_Divide_o_idx_0 = rtb_Gain_fj;
              }

              /* End of Saturate: '<S70>/Saturation' */

              /* Math: '<S55>/Rem' incorporates:
               *  Constant: '<S55>/Constant1'
               *  Delay: '<S51>/Delay'
               *  Sum: '<S51>/Sum2'
               */
              rtb_Rem_i = rt_remf(rtb_a_k - FMS_DW.Delay_DSTATE_h, 6.28318548F);

              /* Switch: '<S55>/Switch' incorporates:
               *  Abs: '<S55>/Abs'
               *  Constant: '<S55>/Constant'
               *  Constant: '<S61>/Constant'
               *  Product: '<S55>/Multiply'
               *  RelationalOperator: '<S61>/Compare'
               *  Signum: '<S55>/Sign'
               *  Sum: '<S55>/Add'
               */
              if (fabsf(rtb_Rem_i) > 3.14159274F) {
                /* Signum: '<S55>/Sign' */
                if (rtb_Rem_i < 0.0F) {
                  rtb_Square2 = -1.0F;
                } else {
                  rtb_Square2 = (real32_T)(rtb_Rem_i > 0.0F);
                }

                rtb_Rem_i -= 6.28318548F * rtb_Square2;
              }

              /* End of Switch: '<S55>/Switch' */

              /* Sum: '<S51>/Sum' incorporates:
               *  Delay: '<S51>/Delay'
               */
              rtb_Square2 = rtb_Rem_i + FMS_DW.Delay_DSTATE_h;

              /* Product: '<S60>/Multiply1' incorporates:
               *  Constant: '<S60>/const1'
               *  DiscreteIntegrator: '<S54>/Integrator'
               */
              rtb_Rem_i = FMS_DW.Integrator_DSTATE * 0.785398185F;

              /* Sum: '<S60>/Add' incorporates:
               *  DiscreteIntegrator: '<S54>/Integrator1'
               *  Sum: '<S54>/Subtract'
               */
              rtb_Gain_fj = (FMS_DW.Integrator1_DSTATE - rtb_Square2) +
                rtb_Rem_i;

              /* Signum: '<S60>/Sign' */
              if (rtb_Gain_fj < 0.0F) {
                rtb_Square2 = -1.0F;
              } else {
                rtb_Square2 = (real32_T)(rtb_Gain_fj > 0.0F);
              }

              /* Sum: '<S60>/Add2' incorporates:
               *  Abs: '<S60>/Abs'
               *  Gain: '<S60>/Gain'
               *  Gain: '<S60>/Gain1'
               *  Product: '<S60>/Multiply2'
               *  Product: '<S60>/Multiply3'
               *  Signum: '<S60>/Sign'
               *  Sqrt: '<S60>/Sqrt'
               *  Sum: '<S60>/Add1'
               *  Sum: '<S60>/Subtract'
               */
              rtb_a_k = (sqrtf((8.0F * fabsf(rtb_Gain_fj) + FMS_ConstB.d) *
                               FMS_ConstB.d) - FMS_ConstB.d) * 0.5F *
                rtb_Square2 + rtb_Rem_i;

              /* Sum: '<S60>/Add3' */
              rtb_Square2 = rtb_Gain_fj + FMS_ConstB.d;

              /* Sum: '<S60>/Subtract1' */
              rtb_MathFunction_c_idx_0 = rtb_Gain_fj - FMS_ConstB.d;

              /* Signum: '<S60>/Sign1' */
              if (rtb_Square2 < 0.0F) {
                rtb_Square2 = -1.0F;
              } else {
                rtb_Square2 = (real32_T)(rtb_Square2 > 0.0F);
              }

              /* Signum: '<S60>/Sign2' */
              if (rtb_MathFunction_c_idx_0 < 0.0F) {
                tmp_2 = -1.0F;
              } else {
                tmp_2 = (real32_T)(rtb_MathFunction_c_idx_0 > 0.0F);
              }

              /* Sum: '<S60>/Add5' incorporates:
               *  Gain: '<S60>/Gain2'
               *  Product: '<S60>/Multiply4'
               *  Signum: '<S60>/Sign1'
               *  Signum: '<S60>/Sign2'
               *  Sum: '<S60>/Add4'
               *  Sum: '<S60>/Subtract2'
               */
              rtb_a_k += ((rtb_Gain_fj - rtb_a_k) + rtb_Rem_i) * ((rtb_Square2 -
                tmp_2) * 0.5F);

              /* Update for Delay: '<S71>/Delay' */
              FMS_DW.icLoad = false;

              /* Update for DiscreteIntegrator: '<S115>/Discrete-Time Integrator' incorporates:
               *  Constant: '<S47>/L1'
               *  Constant: '<S70>/Constant'
               *  MinMax: '<S70>/Max'
               *  MinMax: '<S70>/Min'
               *  Product: '<S70>/Divide'
               *  Product: '<S70>/Multiply1'
               *  Product: '<S71>/Divide1'
               *  Sqrt: '<S108>/Sqrt'
               *  Trigonometry: '<S70>/Sin'
               */
              FMS_DW.l1_heading += arm_sin_f32(rtb_Divide_o_idx_0) *
                rtb_Divide_o_idx_1 / fminf(FMS_PARAM.L1, fmaxf(sqrtf
                (rtb_Divide_o_idx_2), 0.5F)) / rtb_Switch_k * 0.004F;

              /* Update for Delay: '<S51>/Delay' */
              FMS_DW.icLoad_k = false;

              /* Update for DiscreteIntegrator: '<S54>/Integrator1' incorporates:
               *  DiscreteIntegrator: '<S54>/Integrator'
               */
              FMS_DW.Integrator1_IC_LOADING = 0U;
              FMS_DW.Integrator1_DSTATE += 0.004F * FMS_DW.Integrator_DSTATE;

              /* Signum: '<S60>/Sign5' */
              if (rtb_a_k < 0.0F) {
                /* Signum: '<S60>/Sign6' */
                rtb_Divide_o_idx_1 = -1.0F;
              } else {
                /* Signum: '<S60>/Sign6' */
                rtb_Divide_o_idx_1 = (real32_T)(rtb_a_k > 0.0F);
              }

              /* Sum: '<S60>/Add6' */
              rtb_Square2 = rtb_a_k + FMS_ConstB.d;

              /* Sum: '<S60>/Subtract3' */
              rtb_MathFunction_c_idx_0 = rtb_a_k - FMS_ConstB.d;

              /* Signum: '<S60>/Sign3' */
              if (rtb_Square2 < 0.0F) {
                rtb_Square2 = -1.0F;
              } else {
                rtb_Square2 = (real32_T)(rtb_Square2 > 0.0F);
              }

              /* Signum: '<S60>/Sign4' */
              if (rtb_MathFunction_c_idx_0 < 0.0F) {
                rtb_Divide_o_idx_2 = -1.0F;
              } else {
                rtb_Divide_o_idx_2 = (real32_T)(rtb_MathFunction_c_idx_0 > 0.0F);
              }

              /* Update for DiscreteIntegrator: '<S54>/Integrator' incorporates:
               *  Constant: '<S60>/const'
               *  Gain: '<S60>/Gain3'
               *  Product: '<S60>/Divide'
               *  Product: '<S60>/Multiply5'
               *  Product: '<S60>/Multiply6'
               *  Signum: '<S60>/Sign3'
               *  Signum: '<S60>/Sign4'
               *  Signum: '<S60>/Sign5'
               *  Sum: '<S60>/Subtract4'
               *  Sum: '<S60>/Subtract5'
               *  Sum: '<S60>/Subtract6'
               */
              FMS_DW.Integrator_DSTATE += ((rtb_a_k / FMS_ConstB.d -
                rtb_Divide_o_idx_1) * FMS_ConstB.Gain4 * ((rtb_Square2 -
                rtb_Divide_o_idx_2) * 0.5F) - rtb_Divide_o_idx_1 * 1.04719758F) *
                0.004F;
              if (FMS_DW.Integrator_DSTATE >= FMS_PARAM.YAW_RATE_LIM) {
                FMS_DW.Integrator_DSTATE = FMS_PARAM.YAW_RATE_LIM;
              } else if (FMS_DW.Integrator_DSTATE <= -FMS_PARAM.YAW_RATE_LIM) {
                FMS_DW.Integrator_DSTATE = -FMS_PARAM.YAW_RATE_LIM;
              }

              /* End of Update for DiscreteIntegrator: '<S54>/Integrator' */
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
            /* Outputs for IfAction SubSystem: '<S37>/Unknown' incorporates:
             *  ActionPort: '<S45>/Action Port'
             */
            /* Outport: '<Root>/FMS_Out' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             */
            FMS_Disarm(&FMS_Y.FMS_Out, &FMS_ConstB.Unknown_d);

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
           *  Chart: '<S253>/Motion State'
           *  Chart: '<S265>/Motion State'
           */
          FMS_MotionState_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_g);
          FMS_MotionState_i_Reset(&rtb_state_ee, &FMS_DW.sf_MotionState_d);

          /* End of SystemReset for SubSystem: '<S33>/Stabilize' */
        }

        /* Outputs for IfAction SubSystem: '<S33>/Stabilize' incorporates:
         *  ActionPort: '<S40>/Action Port'
         */
        /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
        /* Chart: '<S265>/Motion State' incorporates:
         *  Constant: '<S265>/Constant'
         *  Inport: '<Root>/INS_Out'
         *  Math: '<S265>/Square'
         *  Math: '<S265>/Square1'
         *  SignalConversion generated from: '<S32>/Signal Copy1'
         *  Sqrt: '<S265>/Sqrt'
         *  Sum: '<S265>/Add'
         */
        FMS_MotionState(0.0F, sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn +
          FMS_U.INS_Out.ve * FMS_U.INS_Out.ve), &rtb_state_ee,
                        &FMS_DW.sf_MotionState_g);

        /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

        /* SwitchCase: '<S264>/Switch Case' incorporates:
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
            /* SystemReset for IfAction SubSystem: '<S264>/Hold Control' incorporates:
             *  ActionPort: '<S267>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S264>/Switch Case' */
            FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_f);

            /* End of SystemReset for SubSystem: '<S264>/Hold Control' */
          }

          /* Outputs for IfAction SubSystem: '<S264>/Hold Control' incorporates:
           *  ActionPort: '<S267>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                            FMS_U.INS_Out.psi, FMS_B.Merge_o,
                            &FMS_ConstB.HoldControl_f, &FMS_DW.HoldControl_f);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S264>/Hold Control' */
          break;

         case 1:
          /* Outputs for IfAction SubSystem: '<S264>/Brake Control' incorporates:
           *  ActionPort: '<S266>/Action Port'
           */
          FMS_BrakeControl_h(FMS_B.Merge_o);

          /* End of Outputs for SubSystem: '<S264>/Brake Control' */
          break;

         default:
          if (FMS_DW.SwitchCase_ActiveSubsystem_p != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S264>/Move Control' incorporates:
             *  ActionPort: '<S268>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S264>/Switch Case' */
            FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_i);

            /* End of SystemReset for SubSystem: '<S264>/Move Control' */
          }

          /* Outputs for IfAction SubSystem: '<S264>/Move Control' incorporates:
           *  ActionPort: '<S268>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                            FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge_o,
                            &FMS_ConstB.MoveControl_i, &FMS_DW.MoveControl_i);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S264>/Move Control' */
          break;
        }

        /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
        /* Chart: '<S253>/Motion State' incorporates:
         *  Abs: '<S253>/Abs'
         *  Constant: '<S253>/Constant'
         *  Inport: '<Root>/INS_Out'
         *  SignalConversion generated from: '<S32>/Signal Copy1'
         */
        FMS_MotionState_i(0.0F, fabsf(FMS_U.INS_Out.r), &rtb_state_ee,
                          &FMS_DW.sf_MotionState_d);

        /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

        /* SwitchCase: '<S252>/Switch Case' incorporates:
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
            /* SystemReset for IfAction SubSystem: '<S252>/Hold Control' incorporates:
             *  ActionPort: '<S255>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S252>/Switch Case' */
            FMS_HoldControl_i_Reset(&FMS_DW.HoldControl_kq);

            /* End of SystemReset for SubSystem: '<S252>/Hold Control' */
          }

          /* Outputs for IfAction SubSystem: '<S252>/Hold Control' incorporates:
           *  ActionPort: '<S255>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_HoldControl_k(FMS_U.INS_Out.psi, &FMS_B.Merge_n,
                            &FMS_DW.HoldControl_kq);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S252>/Hold Control' */
          break;

         case 1:
          /* Outputs for IfAction SubSystem: '<S252>/Brake Control' incorporates:
           *  ActionPort: '<S254>/Action Port'
           */
          FMS_BrakeControl(&FMS_B.Merge_n);

          /* End of Outputs for SubSystem: '<S252>/Brake Control' */
          break;

         default:
          if (FMS_DW.SwitchCase_ActiveSubsystem_bn != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S252>/Move Control' incorporates:
             *  ActionPort: '<S256>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S252>/Switch Case' */
            FMS_MoveControl_c_Reset(&FMS_DW.MoveControl_b);

            /* End of SystemReset for SubSystem: '<S252>/Move Control' */
          }

          /* Outputs for IfAction SubSystem: '<S252>/Move Control' incorporates:
           *  ActionPort: '<S256>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          FMS_MoveControl_o(FMS_U.Pilot_Cmd.stick_yaw, &FMS_B.Merge_n,
                            &FMS_ConstB.MoveControl_b, &FMS_DW.MoveControl_b);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
          /* End of Outputs for SubSystem: '<S252>/Move Control' */
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

        /* Saturate: '<S252>/Saturation' */
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

        /* End of Saturate: '<S252>/Saturation' */

        /* Saturate: '<S264>/Saturation1' incorporates:
         *  Merge: '<S264>/Merge'
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

        /* End of Saturate: '<S264>/Saturation1' */
        /* End of Outputs for SubSystem: '<S33>/Stabilize' */
        break;

       case 3:
        {
          boolean_T rtb_Compare_og;
          if (FMS_DW.SwitchCase_ActiveSubsystem_b != rtPrevAction) {
            /* SystemReset for IfAction SubSystem: '<S33>/Position' incorporates:
             *  ActionPort: '<S39>/Action Port'
             */
            /* SystemReset for SwitchCase: '<S33>/Switch Case' incorporates:
             *  Chart: '<S212>/Motion Status'
             *  Chart: '<S223>/Motion State'
             *  Chart: '<S236>/Motion State'
             */
            FMS_DW.temporalCounter_i1_h = 0U;
            FMS_DW.is_active_c16_FMS = 0U;
            FMS_DW.is_c16_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;
            FMS_DW.temporalCounter_i1_g = 0U;
            FMS_DW.is_active_c20_FMS = 0U;
            FMS_DW.is_c20_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;
            FMS_DW.temporalCounter_i1_b = 0U;
            FMS_DW.is_active_c21_FMS = 0U;
            FMS_DW.is_c21_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;

            /* End of SystemReset for SubSystem: '<S33>/Position' */
          }

          /* Outputs for IfAction SubSystem: '<S33>/Position' incorporates:
           *  ActionPort: '<S39>/Action Port'
           */
          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* Logic: '<S236>/Logical Operator' incorporates:
           *  Abs: '<S236>/Abs1'
           *  Abs: '<S236>/Abs2'
           *  Constant: '<S247>/Constant'
           *  Constant: '<S248>/Constant'
           *  Inport: '<Root>/Pilot_Cmd'
           *  RelationalOperator: '<S247>/Compare'
           *  RelationalOperator: '<S248>/Compare'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtb_Compare_og = ((fabsf(FMS_U.Pilot_Cmd.stick_pitch) >
                             FMS_PARAM.PITCH_DZ) || (fabsf
            (FMS_U.Pilot_Cmd.stick_roll) > FMS_PARAM.ROLL_DZ));

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Chart: '<S236>/Motion State' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Math: '<S236>/Square'
           *  Math: '<S236>/Square1'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  Sqrt: '<S236>/Sqrt'
           *  Sum: '<S236>/Add'
           */
          if (FMS_DW.temporalCounter_i1_h < 1023U) {
            FMS_DW.temporalCounter_i1_h++;
          }

          if (FMS_DW.is_active_c16_FMS == 0U) {
            FMS_DW.is_active_c16_FMS = 1U;
            FMS_DW.is_c16_FMS = FMS_IN_Move_hn;
            rtb_state_ee = MotionState_Move;
          } else {
            switch (FMS_DW.is_c16_FMS) {
             case FMS_IN_Brake_o:
              rtb_state_ee = MotionState_Brake;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              if ((sqrtf(FMS_U.INS_Out.vn * FMS_U.INS_Out.vn + FMS_U.INS_Out.ve *
                         FMS_U.INS_Out.ve) <= 0.2) ||
                  (FMS_DW.temporalCounter_i1_h >= 625U)) {
                FMS_DW.is_c16_FMS = FMS_IN_Hold_iv;
                rtb_state_ee = MotionState_Hold;
              } else if (rtb_Compare_og) {
                FMS_DW.is_c16_FMS = FMS_IN_Move_hn;
                rtb_state_ee = MotionState_Move;
              }

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              break;

             case FMS_IN_Hold_iv:
              rtb_state_ee = MotionState_Hold;
              if (rtb_Compare_og) {
                FMS_DW.is_c16_FMS = FMS_IN_Move_hn;
                rtb_state_ee = MotionState_Move;
              }
              break;

             default:
              /* case IN_Move: */
              rtb_state_ee = MotionState_Move;
              if (!rtb_Compare_og) {
                FMS_DW.is_c16_FMS = FMS_IN_Brake_o;
                FMS_DW.temporalCounter_i1_h = 0U;
                rtb_state_ee = MotionState_Brake;
              }
              break;
            }
          }

          /* End of Chart: '<S236>/Motion State' */

          /* SwitchCase: '<S235>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S235>/Hold Control' incorporates:
               *  ActionPort: '<S238>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S235>/Switch Case' */
              FMS_HoldControl_a_Reset(&FMS_DW.HoldControl_at);

              /* End of SystemReset for SubSystem: '<S235>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S235>/Hold Control' incorporates:
             *  ActionPort: '<S238>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_g(FMS_U.INS_Out.x_R, FMS_U.INS_Out.y_R,
                              FMS_U.INS_Out.psi, FMS_B.Merge,
                              &FMS_ConstB.HoldControl_at, &FMS_DW.HoldControl_at);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S235>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S235>/Brake Control' incorporates:
             *  ActionPort: '<S237>/Action Port'
             */
            FMS_BrakeControl_h(FMS_B.Merge);

            /* End of Outputs for SubSystem: '<S235>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_l != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S235>/Move Control' incorporates:
               *  ActionPort: '<S239>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S235>/Switch Case' */
              FMS_MoveControl_i_Reset(&FMS_DW.MoveControl_k);

              /* End of SystemReset for SubSystem: '<S235>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S235>/Move Control' incorporates:
             *  ActionPort: '<S239>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_c(FMS_U.Pilot_Cmd.stick_pitch,
                              FMS_U.Pilot_Cmd.stick_roll, FMS_B.Merge,
                              &FMS_ConstB.MoveControl_k, &FMS_DW.MoveControl_k);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S235>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* RelationalOperator: '<S220>/Compare' incorporates:
           *  Abs: '<S212>/Abs1'
           *  Constant: '<S220>/Constant'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtb_Compare_og = (fabsf(FMS_U.Pilot_Cmd.stick_throttle) >
                            FMS_PARAM.THROTTLE_DZ);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Chart: '<S212>/Motion Status' incorporates:
           *  Abs: '<S212>/Abs'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.temporalCounter_i1_g < 511U) {
            FMS_DW.temporalCounter_i1_g++;
          }

          if (FMS_DW.is_active_c20_FMS == 0U) {
            FMS_DW.is_active_c20_FMS = 1U;
            FMS_DW.is_c20_FMS = FMS_IN_Move_hn;
            rtb_state_ee = MotionState_Move;
          } else {
            switch (FMS_DW.is_c20_FMS) {
             case FMS_IN_Brake_o:
              rtb_state_ee = MotionState_Brake;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              if ((fabsf(FMS_U.INS_Out.vd) <= 0.15) ||
                  (FMS_DW.temporalCounter_i1_g >= 375U)) {
                FMS_DW.is_c20_FMS = FMS_IN_Hold_iv;
                rtb_state_ee = MotionState_Hold;
              } else if (rtb_Compare_og) {
                FMS_DW.is_c20_FMS = FMS_IN_Move_hn;
                rtb_state_ee = MotionState_Move;
              }

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              break;

             case FMS_IN_Hold_iv:
              rtb_state_ee = MotionState_Hold;
              if (rtb_Compare_og) {
                FMS_DW.is_c20_FMS = FMS_IN_Move_hn;
                rtb_state_ee = MotionState_Move;
              }
              break;

             default:
              /* case IN_Move: */
              rtb_state_ee = MotionState_Move;
              if (!rtb_Compare_og) {
                FMS_DW.is_c20_FMS = FMS_IN_Brake_o;
                FMS_DW.temporalCounter_i1_g = 0U;
                rtb_state_ee = MotionState_Brake;
              }
              break;
            }
          }

          /* End of Chart: '<S212>/Motion Status' */

          /* SwitchCase: '<S211>/Switch Case' incorporates:
           *  Inport: '<Root>/INS_Out'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtPrevAction = FMS_DW.SwitchCase_ActiveSubsystem_o;
          switch (rtb_state_ee) {
           case MotionState_Hold:
            FMS_DW.SwitchCase_ActiveSubsystem_o = 0;
            break;

           case MotionState_Brake:
            FMS_DW.SwitchCase_ActiveSubsystem_o = 1;
            break;

           default:
            FMS_DW.SwitchCase_ActiveSubsystem_o = 2;
            break;
          }

          switch (FMS_DW.SwitchCase_ActiveSubsystem_o) {
           case 0:
            if (FMS_DW.SwitchCase_ActiveSubsystem_o != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S211>/Hold Control' incorporates:
               *  ActionPort: '<S214>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S211>/Switch Case' */
              FMS_HoldControl_Reset(&FMS_DW.HoldControl_p);

              /* End of SystemReset for SubSystem: '<S211>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S211>/Hold Control' incorporates:
             *  ActionPort: '<S214>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl(FMS_U.INS_Out.h_R, &FMS_B.Merge_k,
                            &FMS_DW.HoldControl_p);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S211>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S211>/Brake Control' incorporates:
             *  ActionPort: '<S213>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_k);

            /* End of Outputs for SubSystem: '<S211>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_o != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S211>/Move Control' incorporates:
               *  ActionPort: '<S215>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S211>/Switch Case' */
              FMS_MoveControl_Reset(&FMS_DW.MoveControl_be);

              /* End of SystemReset for SubSystem: '<S211>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S211>/Move Control' incorporates:
             *  ActionPort: '<S215>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl(FMS_U.Pilot_Cmd.stick_throttle, &FMS_B.Merge_k,
                            &FMS_ConstB.MoveControl_be, &FMS_DW.MoveControl_be);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S211>/Move Control' */
            break;
          }

          /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
          /* RelationalOperator: '<S233>/Compare' incorporates:
           *  Abs: '<S223>/Abs1'
           *  Constant: '<S233>/Constant'
           *  Inport: '<Root>/Pilot_Cmd'
           *  SignalConversion generated from: '<S32>/Signal Copy2'
           */
          rtb_Compare_og = (fabsf(FMS_U.Pilot_Cmd.stick_yaw) > FMS_PARAM.YAW_DZ);

          /* End of Outputs for SubSystem: '<S4>/FMS_Input' */

          /* Chart: '<S223>/Motion State' incorporates:
           *  Abs: '<S223>/Abs'
           *  Inport: '<Root>/INS_Out'
           *  SignalConversion generated from: '<S32>/Signal Copy1'
           */
          if (FMS_DW.temporalCounter_i1_b < 255U) {
            FMS_DW.temporalCounter_i1_b++;
          }

          if (FMS_DW.is_active_c21_FMS == 0U) {
            FMS_DW.is_active_c21_FMS = 1U;
            FMS_DW.is_c21_FMS = FMS_IN_Move_hn;
            rtb_state_ee = MotionState_Move;
          } else {
            switch (FMS_DW.is_c21_FMS) {
             case FMS_IN_Brake_o:
              rtb_state_ee = MotionState_Brake;

              /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
              if ((fabsf(FMS_U.INS_Out.r) <= 0.1) ||
                  (FMS_DW.temporalCounter_i1_b >= 250U)) {
                FMS_DW.is_c21_FMS = FMS_IN_Hold_iv;
                rtb_state_ee = MotionState_Hold;
              } else if (rtb_Compare_og) {
                FMS_DW.is_c21_FMS = FMS_IN_Move_hn;
                rtb_state_ee = MotionState_Move;
              }

              /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
              break;

             case FMS_IN_Hold_iv:
              rtb_state_ee = MotionState_Hold;
              if (rtb_Compare_og) {
                FMS_DW.is_c21_FMS = FMS_IN_Move_hn;
                rtb_state_ee = MotionState_Move;
              }
              break;

             default:
              /* case IN_Move: */
              rtb_state_ee = MotionState_Move;
              if (!rtb_Compare_og) {
                FMS_DW.is_c21_FMS = FMS_IN_Brake_o;
                FMS_DW.temporalCounter_i1_b = 0U;
                rtb_state_ee = MotionState_Brake;
              }
              break;
            }
          }

          /* End of Chart: '<S223>/Motion State' */

          /* SwitchCase: '<S222>/Switch Case' incorporates:
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
              /* SystemReset for IfAction SubSystem: '<S222>/Hold Control' incorporates:
               *  ActionPort: '<S225>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S222>/Switch Case' */
              FMS_HoldControl_i_Reset(&FMS_DW.HoldControl_e);

              /* End of SystemReset for SubSystem: '<S222>/Hold Control' */
            }

            /* Outputs for IfAction SubSystem: '<S222>/Hold Control' incorporates:
             *  ActionPort: '<S225>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_HoldControl_k(FMS_U.INS_Out.psi, &FMS_B.Merge_d,
                              &FMS_DW.HoldControl_e);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S222>/Hold Control' */
            break;

           case 1:
            /* Outputs for IfAction SubSystem: '<S222>/Brake Control' incorporates:
             *  ActionPort: '<S224>/Action Port'
             */
            FMS_BrakeControl(&FMS_B.Merge_d);

            /* End of Outputs for SubSystem: '<S222>/Brake Control' */
            break;

           default:
            if (FMS_DW.SwitchCase_ActiveSubsystem_j != rtPrevAction) {
              /* SystemReset for IfAction SubSystem: '<S222>/Move Control' incorporates:
               *  ActionPort: '<S226>/Action Port'
               */
              /* SystemReset for SwitchCase: '<S222>/Switch Case' */
              FMS_MoveControl_c_Reset(&FMS_DW.MoveControl_mr);

              /* End of SystemReset for SubSystem: '<S222>/Move Control' */
            }

            /* Outputs for IfAction SubSystem: '<S222>/Move Control' incorporates:
             *  ActionPort: '<S226>/Action Port'
             */
            /* Outputs for Atomic SubSystem: '<S4>/FMS_Input' */
            FMS_MoveControl_o(FMS_U.Pilot_Cmd.stick_yaw, &FMS_B.Merge_d,
                              &FMS_ConstB.MoveControl_mr, &FMS_DW.MoveControl_mr);

            /* End of Outputs for SubSystem: '<S4>/FMS_Input' */
            /* End of Outputs for SubSystem: '<S222>/Move Control' */
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

          /* Saturate: '<S222>/Saturation' */
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

          /* End of Saturate: '<S222>/Saturation' */

          /* Saturate: '<S235>/Saturation1' incorporates:
           *  Merge: '<S235>/Merge'
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

          /* End of Saturate: '<S235>/Saturation1' */

          /* Saturate: '<S211>/Saturation1' */
          if (FMS_B.Merge_k > FMS_PARAM.VEL_Z_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = FMS_PARAM.VEL_Z_LIM;
          } else if (FMS_B.Merge_k < -FMS_PARAM.VEL_Z_LIM) {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = -FMS_PARAM.VEL_Z_LIM;
          } else {
            /* BusAssignment: '<S39>/Bus Assignment' incorporates:
             *  BusAssignment: '<S34>/Bus Assignment'
             *  Outport: '<Root>/FMS_Out'
             */
            FMS_Y.FMS_Out.w_cmd = FMS_B.Merge_k;
          }

          /* End of Saturate: '<S211>/Saturation1' */
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
   *  DiscreteIntegrator: '<S397>/Discrete-Time Integrator'
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

  /* Update for DiscreteIntegrator: '<S397>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S397>/Constant'
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
    FMS_B.Switch1 = FMS_Cmd_None;
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
    FMS_DW.is_c3_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_B.target_mode = PilotMode_None;

    /* SystemInitialize for Chart: '<Root>/State Machine' */
    initialize_msg_local_queues_for();
    FMS_DW.sfEvent = -1;
    FMS_DW.is_active_Combo_Stick = 0U;
    FMS_DW.is_Combo_Stick = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_active_Command_Listener = 0U;
    FMS_DW.is_Command_Listener = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_active_Vehicle = 0U;
    FMS_DW.is_Vehicle = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_Arm = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_Auto = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_Mission = FMS_IN_NO_ACTIVE_CHILD_mn;
    FMS_DW.is_Offboard = FMS_IN_NO_ACTIVE_CHILD_mn;
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
    FMS_DW.prep_mission_takeoff = 0.0;
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
    FMS_DW.cmd_prev = FMS_Cmd_None;
    FMS_DW.cmd_start = FMS_Cmd_None;
    FMS_DW.mode_prev = PilotMode_None;
    FMS_DW.mode_start = PilotMode_None;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FMS Commander' */
    /* Start for SwitchCase: '<S31>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem = -1;

    /* SystemInitialize for IfAction SubSystem: '<S31>/Arm' */
    /* Start for SwitchCase: '<S33>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_b = -1;

    /* SystemInitialize for IfAction SubSystem: '<S33>/SubMode' */
    /* Start for SwitchCase: '<S41>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_on = -1;

    /* SystemInitialize for IfAction SubSystem: '<S41>/Return' */
    /* Start for SwitchCase: '<S361>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_c = -1;

    /* Start for SwitchCase: '<S351>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_i5 = -1;

    /* InitializeConditions for Delay: '<S347>/Delay' */
    FMS_DW.icLoad_h = true;

    /* InitializeConditions for DiscreteIntegrator: '<S388>/Discrete-Time Integrator' */
    FMS_DW.l1_heading_a = 0.0F;

    /* InitializeConditions for Delay: '<S327>/Delay' */
    FMS_DW.icLoad_j = true;

    /* InitializeConditions for Delay: '<S328>/Delay' */
    FMS_DW.icLoad_c = true;

    /* InitializeConditions for DiscreteIntegrator: '<S331>/Integrator1' */
    FMS_DW.Integrator1_IC_LOADING_o = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S331>/Integrator' */
    FMS_DW.Integrator_DSTATE_j = 0.0F;

    /* SystemInitialize for Chart: '<S362>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState);

    /* SystemInitialize for IfAction SubSystem: '<S361>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_g);

    /* End of SystemInitialize for SubSystem: '<S361>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S361>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_c);

    /* End of SystemInitialize for SubSystem: '<S361>/Move Control' */

    /* SystemInitialize for Merge: '<S361>/Merge' */
    FMS_B.Merge_f[0] = 0.0F;
    FMS_B.Merge_f[1] = 0.0F;

    /* SystemInitialize for Chart: '<S352>/Motion Status' */
    FMS_MotionStatus_Init(&rtb_state_l, &FMS_DW.sf_MotionStatus);

    /* SystemInitialize for IfAction SubSystem: '<S351>/Hold Control' */
    FMS_HoldControl_Init(&FMS_DW.HoldControl);

    /* End of SystemInitialize for SubSystem: '<S351>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S351>/Move Control' */
    FMS_MoveControl_Init(&FMS_DW.MoveControl);

    /* End of SystemInitialize for SubSystem: '<S351>/Move Control' */

    /* SystemInitialize for Merge: '<S351>/Merge' */
    FMS_B.Merge_pd = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S41>/Return' */

    /* SystemInitialize for IfAction SubSystem: '<S41>/Hold' */
    /* Start for SwitchCase: '<S307>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_g = -1;

    /* Start for SwitchCase: '<S285>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_d = -1;

    /* Start for SwitchCase: '<S295>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_bi = -1;

    /* SystemInitialize for Chart: '<S308>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState_l);

    /* SystemInitialize for IfAction SubSystem: '<S307>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_h);

    /* End of SystemInitialize for SubSystem: '<S307>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S307>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_h);

    /* End of SystemInitialize for SubSystem: '<S307>/Move Control' */

    /* SystemInitialize for Merge: '<S307>/Merge' */
    FMS_B.Merge_m[0] = 0.0F;
    FMS_B.Merge_m[1] = 0.0F;

    /* SystemInitialize for Chart: '<S286>/Motion Status' */
    FMS_MotionStatus_Init(&rtb_state_l, &FMS_DW.sf_MotionStatus_d);

    /* SystemInitialize for IfAction SubSystem: '<S285>/Hold Control' */
    FMS_HoldControl_Init(&FMS_DW.HoldControl_b);

    /* End of SystemInitialize for SubSystem: '<S285>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S285>/Move Control' */
    FMS_MoveControl_Init(&FMS_DW.MoveControl_g);

    /* End of SystemInitialize for SubSystem: '<S285>/Move Control' */

    /* SystemInitialize for Merge: '<S285>/Merge' */
    FMS_B.Merge_ob = 0.0F;

    /* SystemInitialize for Chart: '<S296>/Motion State' */
    FMS_MotionState_b_Init(&rtb_state_l, &FMS_DW.sf_MotionState_i);

    /* SystemInitialize for IfAction SubSystem: '<S295>/Hold Control' */
    FMS_HoldControl_i_Init(&FMS_DW.HoldControl_k);

    /* End of SystemInitialize for SubSystem: '<S295>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S295>/Move Control' */
    FMS_MoveControl_m_Init(&FMS_DW.MoveControl_o);

    /* End of SystemInitialize for SubSystem: '<S295>/Move Control' */

    /* SystemInitialize for Merge: '<S295>/Merge' */
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
    /* Start for SwitchCase: '<S88>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_a = -1;

    /* Start for SwitchCase: '<S78>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_e = -1;

    /* InitializeConditions for Delay: '<S71>/Delay' */
    FMS_DW.icLoad = true;

    /* InitializeConditions for DiscreteIntegrator: '<S115>/Discrete-Time Integrator' */
    FMS_DW.l1_heading = 0.0F;

    /* InitializeConditions for Delay: '<S51>/Delay' */
    FMS_DW.icLoad_k = true;

    /* InitializeConditions for DiscreteIntegrator: '<S54>/Integrator1' */
    FMS_DW.Integrator1_IC_LOADING = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S54>/Integrator' */
    FMS_DW.Integrator_DSTATE = 0.0F;

    /* SystemInitialize for Chart: '<S89>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState_n);

    /* SystemInitialize for IfAction SubSystem: '<S88>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_d);

    /* End of SystemInitialize for SubSystem: '<S88>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S88>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_cp);

    /* End of SystemInitialize for SubSystem: '<S88>/Move Control' */

    /* SystemInitialize for Merge: '<S88>/Merge' */
    FMS_B.Merge_nj[0] = 0.0F;
    FMS_B.Merge_nj[1] = 0.0F;

    /* SystemInitialize for Chart: '<S79>/Motion Status' */
    FMS_MotionStatus_Init(&rtb_state_l, &FMS_DW.sf_MotionStatus_j);

    /* SystemInitialize for IfAction SubSystem: '<S78>/Hold Control' */
    FMS_HoldControl_Init(&FMS_DW.HoldControl_a);

    /* End of SystemInitialize for SubSystem: '<S78>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S78>/Move Control' */
    FMS_MoveControl_Init(&FMS_DW.MoveControl_m);

    /* End of SystemInitialize for SubSystem: '<S78>/Move Control' */

    /* SystemInitialize for Merge: '<S78>/Merge' */
    FMS_B.Merge_e = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S43>/Mission_SubSystem' */
    /* End of SystemInitialize for SubSystem: '<S37>/Mission' */
    /* End of SystemInitialize for SubSystem: '<S33>/Auto' */

    /* SystemInitialize for IfAction SubSystem: '<S33>/Stabilize' */
    /* Start for SwitchCase: '<S264>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_p = -1;

    /* Start for SwitchCase: '<S252>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_bn = -1;

    /* SystemInitialize for Chart: '<S265>/Motion State' */
    FMS_MotionState_Init(&rtb_state_l, &FMS_DW.sf_MotionState_g);

    /* SystemInitialize for IfAction SubSystem: '<S264>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_f);

    /* End of SystemInitialize for SubSystem: '<S264>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S264>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_i);

    /* End of SystemInitialize for SubSystem: '<S264>/Move Control' */

    /* SystemInitialize for Merge: '<S264>/Merge' */
    FMS_B.Merge_o[0] = 0.0F;
    FMS_B.Merge_o[1] = 0.0F;

    /* SystemInitialize for Chart: '<S253>/Motion State' */
    FMS_MotionState_b_Init(&rtb_state_l, &FMS_DW.sf_MotionState_d);

    /* SystemInitialize for IfAction SubSystem: '<S252>/Hold Control' */
    FMS_HoldControl_i_Init(&FMS_DW.HoldControl_kq);

    /* End of SystemInitialize for SubSystem: '<S252>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S252>/Move Control' */
    FMS_MoveControl_m_Init(&FMS_DW.MoveControl_b);

    /* End of SystemInitialize for SubSystem: '<S252>/Move Control' */

    /* SystemInitialize for Merge: '<S252>/Merge' */
    FMS_B.Merge_n = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S33>/Stabilize' */

    /* SystemInitialize for IfAction SubSystem: '<S33>/Position' */
    /* Start for SwitchCase: '<S235>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_l = -1;

    /* Start for SwitchCase: '<S211>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_o = -1;

    /* Start for SwitchCase: '<S222>/Switch Case' */
    FMS_DW.SwitchCase_ActiveSubsystem_j = -1;

    /* SystemInitialize for Chart: '<S236>/Motion State' */
    FMS_DW.temporalCounter_i1_h = 0U;
    FMS_DW.is_active_c16_FMS = 0U;
    FMS_DW.is_c16_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;

    /* SystemInitialize for IfAction SubSystem: '<S235>/Hold Control' */
    FMS_HoldControl_l_Init(&FMS_DW.HoldControl_at);

    /* End of SystemInitialize for SubSystem: '<S235>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S235>/Move Control' */
    FMS_MoveControl_p_Init(&FMS_DW.MoveControl_k);

    /* End of SystemInitialize for SubSystem: '<S235>/Move Control' */

    /* SystemInitialize for Merge: '<S235>/Merge' */
    FMS_B.Merge[0] = 0.0F;
    FMS_B.Merge[1] = 0.0F;

    /* SystemInitialize for Chart: '<S212>/Motion Status' */
    FMS_DW.temporalCounter_i1_g = 0U;
    FMS_DW.is_active_c20_FMS = 0U;
    FMS_DW.is_c20_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;

    /* SystemInitialize for IfAction SubSystem: '<S211>/Hold Control' */
    FMS_HoldControl_Init(&FMS_DW.HoldControl_p);

    /* End of SystemInitialize for SubSystem: '<S211>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S211>/Move Control' */
    FMS_MoveControl_Init(&FMS_DW.MoveControl_be);

    /* End of SystemInitialize for SubSystem: '<S211>/Move Control' */

    /* SystemInitialize for Merge: '<S211>/Merge' */
    FMS_B.Merge_k = 0.0F;

    /* SystemInitialize for Chart: '<S223>/Motion State' */
    FMS_DW.temporalCounter_i1_b = 0U;
    FMS_DW.is_active_c21_FMS = 0U;
    FMS_DW.is_c21_FMS = FMS_IN_NO_ACTIVE_CHILD_mn;

    /* SystemInitialize for IfAction SubSystem: '<S222>/Hold Control' */
    FMS_HoldControl_i_Init(&FMS_DW.HoldControl_e);

    /* End of SystemInitialize for SubSystem: '<S222>/Hold Control' */

    /* SystemInitialize for IfAction SubSystem: '<S222>/Move Control' */
    FMS_MoveControl_m_Init(&FMS_DW.MoveControl_mr);

    /* End of SystemInitialize for SubSystem: '<S222>/Move Control' */

    /* SystemInitialize for Merge: '<S222>/Merge' */
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
