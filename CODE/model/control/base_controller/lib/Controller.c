/*
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.37
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Feb 25 18:26:08 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Controller_types.h"
#include "Controller_private.h"

/* Exported block parameters */
struct_Ae52N6uY2eO0jd5TMQiCYB CONTROL_PARAM = {
  1.4F,
  0.2F,
  0.2F,
  0.6F,
  0.1F,
  0.0F,
  -1.0F,
  1.0F,
  -1.0F,
  1.0F,
  -0.15F,
  0.15F,
  -0.1F,
  0.1F,
  5.0F,
  5.0F,
  0.52359879F,
  0.1F,
  0.1F,
  0.15F,
  0.1F,
  0.1F,
  0.2F,
  0.003F,
  0.003F,
  0.001F,
  -0.1F,
  0.1F,
  -0.1F,
  0.1F,
  1.57079637F,
  3.14159274F
} ;                                    /* Variable: CONTROL_PARAM
                                        * Referenced by:
                                        *   '<S7>/Saturation'
                                        *   '<S16>/kd'
                                        *   '<S16>/Saturation'
                                        *   '<S17>/ki'
                                        *   '<S17>/Discrete-Time Integrator'
                                        *   '<S18>/kp'
                                        *   '<S26>/gain3'
                                        *   '<S26>/Saturation'
                                        *   '<S27>/gain3'
                                        *   '<S27>/Discrete-Time Integrator'
                                        *   '<S28>/gain'
                                        */

struct_ny3PY9hontv4J5WqwlFzJB CONTROL_EXPORT = {
  2U,

  { 70, 108, 97, 116, 32, 67, 111, 110, 116, 114, 111, 108, 108, 101, 114, 32,
    118, 48, 46, 49, 0 }
} ;                                    /* Variable: CONTROL_EXPORT
                                        * Referenced by: '<S4>/Constant'
                                        */

/* Block states (default storage) */
DW_Controller_T Controller_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Controller_T Controller_Y;

/* Real-time model */
static RT_MODEL_Controller_T Controller_M_;
RT_MODEL_Controller_T *const Controller_M = &Controller_M_;

/* Model step function */
void Controller_step(void)
{
  int32_T i;
  real32_T rtb_VectorConcatenate[9];
  real32_T rtb_VectorConcatenate_0[3];
  real32_T rtb_DiscreteTimeIntegrator1_l;
  real32_T rtb_Gain;
  real32_T rtb_Gain_i;
  real32_T rtb_Multiply_e;
  real32_T rtb_Saturation2;
  real32_T rtb_Subtract1;
  real32_T rtb_Subtract3;
  real32_T rtb_u_error_C_mPs;
  real32_T u;

  /* Switch: '<S22>/Switch' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S31>/Constant'
   *  Inport: '<Root>/FMS_Out'
   *  RelationalOperator: '<S30>/Compare'
   *  RelationalOperator: '<S31>/Compare'
   *  Saturate: '<S7>/Saturation'
   *  Switch: '<S22>/Switch1'
   */
  if (Controller_U.FMS_Out.ctrl_mode == 2) {
    rtb_DiscreteTimeIntegrator1_l = Controller_U.FMS_Out.r_cmd;
  } else if (Controller_U.FMS_Out.ctrl_mode == 6) {
    /* Switch: '<S32>/Switch' incorporates:
     *  S-Function (sfix_bitop): '<S32>/cmd_r valid'
     *  Saturate: '<S7>/Saturation'
     *  Switch: '<S22>/Switch1'
     */
    if ((Controller_U.FMS_Out.cmd_mask & 4) > 0) {
      rtb_DiscreteTimeIntegrator1_l = Controller_U.FMS_Out.r_cmd;
    } else if (Controller_U.FMS_Out.psi_rate_cmd > CONTROL_PARAM.R_CMD_LIM) {
      /* Saturate: '<S7>/Saturation' */
      rtb_DiscreteTimeIntegrator1_l = CONTROL_PARAM.R_CMD_LIM;
    } else if (Controller_U.FMS_Out.psi_rate_cmd < -CONTROL_PARAM.R_CMD_LIM) {
      /* Saturate: '<S7>/Saturation' */
      rtb_DiscreteTimeIntegrator1_l = -CONTROL_PARAM.R_CMD_LIM;
    } else {
      /* Saturate: '<S7>/Saturation' */
      rtb_DiscreteTimeIntegrator1_l = Controller_U.FMS_Out.psi_rate_cmd;
    }

    /* End of Switch: '<S32>/Switch' */
  } else if (Controller_U.FMS_Out.psi_rate_cmd > CONTROL_PARAM.R_CMD_LIM) {
    /* Saturate: '<S7>/Saturation' incorporates:
     *  Switch: '<S22>/Switch1'
     */
    rtb_DiscreteTimeIntegrator1_l = CONTROL_PARAM.R_CMD_LIM;
  } else if (Controller_U.FMS_Out.psi_rate_cmd < -CONTROL_PARAM.R_CMD_LIM) {
    /* Saturate: '<S7>/Saturation' incorporates:
     *  Switch: '<S22>/Switch1'
     */
    rtb_DiscreteTimeIntegrator1_l = -CONTROL_PARAM.R_CMD_LIM;
  } else {
    /* Switch: '<S22>/Switch1' incorporates:
     *  Saturate: '<S7>/Saturation'
     */
    rtb_DiscreteTimeIntegrator1_l = Controller_U.FMS_Out.psi_rate_cmd;
  }

  /* End of Switch: '<S22>/Switch' */

  /* Sum: '<S23>/Sum' incorporates:
   *  Inport: '<Root>/INS_Out'
   */
  rtb_DiscreteTimeIntegrator1_l -= Controller_U.INS_Out.r;

  /* DiscreteIntegrator: '<S25>/Discrete-Time Integrator5' */
  if (Controller_DW.DiscreteTimeIntegrator5_IC_LOAD != 0) {
    Controller_DW.DiscreteTimeIntegrator5_DSTATE = rtb_DiscreteTimeIntegrator1_l;
  }

  /* DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  if ((Controller_U.FMS_Out.reset != 0) ||
      (Controller_DW.DiscreteTimeIntegrator_PrevRese != 0)) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = Controller_ConstB.Constant_o;
    if (Controller_DW.DiscreteTimeIntegrator_DSTATE >= CONTROL_PARAM.RATE_I_MAX)
    {
      Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MAX;
    } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE <=
               CONTROL_PARAM.RATE_I_MIN) {
      Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MIN;
    }
  }

  if (Controller_DW.DiscreteTimeIntegrator_DSTATE >= CONTROL_PARAM.RATE_I_MAX) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MAX;
  } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE <=
             CONTROL_PARAM.RATE_I_MIN) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MIN;
  }

  /* DiscreteIntegrator: '<S29>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  if ((Controller_U.FMS_Out.reset != 0) ||
      (Controller_DW.DiscreteTimeIntegrator1_PrevRes != 0)) {
    Controller_DW.DiscreteTimeIntegrator1_DSTATE = 0.0F;
  }

  /* Gain: '<S29>/Gain' incorporates:
   *  DiscreteIntegrator: '<S25>/Discrete-Time Integrator5'
   *  DiscreteIntegrator: '<S29>/Discrete-Time Integrator1'
   *  Sum: '<S29>/Sum5'
   */
  rtb_Gain = (Controller_DW.DiscreteTimeIntegrator5_DSTATE -
              Controller_DW.DiscreteTimeIntegrator1_DSTATE) * 188.49556F;

  /* Trigonometry: '<S14>/Trigonometric Function1' incorporates:
   *  Gain: '<S13>/Gain'
   *  Inport: '<Root>/INS_Out'
   *  Trigonometry: '<S14>/Trigonometric Function3'
   */
  rtb_u_error_C_mPs = cosf(-Controller_U.INS_Out.psi);
  rtb_VectorConcatenate[0] = rtb_u_error_C_mPs;

  /* Trigonometry: '<S14>/Trigonometric Function' incorporates:
   *  Gain: '<S13>/Gain'
   *  Inport: '<Root>/INS_Out'
   *  Trigonometry: '<S14>/Trigonometric Function2'
   */
  rtb_Gain_i = sinf(-Controller_U.INS_Out.psi);
  rtb_VectorConcatenate[1] = rtb_Gain_i;

  /* SignalConversion generated from: '<S14>/Vector Concatenate1' incorporates:
   *  Constant: '<S14>/Constant3'
   */
  rtb_VectorConcatenate[2] = 0.0F;

  /* Gain: '<S14>/Gain' */
  rtb_VectorConcatenate[3] = -rtb_Gain_i;

  /* Trigonometry: '<S14>/Trigonometric Function3' */
  rtb_VectorConcatenate[4] = rtb_u_error_C_mPs;

  /* SignalConversion generated from: '<S14>/Vector Concatenate2' incorporates:
   *  Constant: '<S14>/Constant4'
   */
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion generated from: '<S14>/Vector Concatenate' incorporates:
   *  Concatenate: '<S14>/Vector Concatenate3'
   */
  rtb_VectorConcatenate[6] = Controller_ConstB.VectorConcatenate3[0];
  rtb_VectorConcatenate[7] = Controller_ConstB.VectorConcatenate3[1];
  rtb_VectorConcatenate[8] = Controller_ConstB.VectorConcatenate3[2];

  /* Product: '<S11>/Multiply' incorporates:
   *  Concatenate: '<S14>/Vector Concatenate'
   *  Inport: '<Root>/INS_Out'
   *  SignalConversion generated from: '<S11>/Multiply'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_0[i] = (rtb_VectorConcatenate[i + 3] *
      Controller_U.INS_Out.ve + rtb_VectorConcatenate[i] *
      Controller_U.INS_Out.vn) + rtb_VectorConcatenate[i + 6] * 0.0F;
  }

  /* End of Product: '<S11>/Multiply' */

  /* Sum: '<S8>/Sum' incorporates:
   *  DiscreteIntegrator: '<S12>/Integrator1'
   */
  rtb_u_error_C_mPs = Controller_DW.Integrator1_DSTATE -
    rtb_VectorConcatenate_0[0];

  /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  if ((Controller_U.FMS_Out.reset != 0) ||
      (Controller_DW.DiscreteTimeIntegrator_PrevRe_k != 0)) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = Controller_ConstB.Constant;
    if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i >=
        CONTROL_PARAM.VEL_XY_I_MAX) {
      Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MAX;
    } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i <=
               CONTROL_PARAM.VEL_XY_I_MIN) {
      Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MIN;
    }
  }

  if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i >=
      CONTROL_PARAM.VEL_XY_I_MAX) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MAX;
  } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i <=
             CONTROL_PARAM.VEL_XY_I_MIN) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MIN;
  }

  /* DiscreteIntegrator: '<S19>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  if ((Controller_U.FMS_Out.reset != 0) ||
      (Controller_DW.DiscreteTimeIntegrator1_PrevR_l != 0)) {
    Controller_DW.DiscreteTimeIntegrator1_DSTAT_j = 0.0F;
  }

  /* Gain: '<S19>/Gain' incorporates:
   *  DiscreteIntegrator: '<S19>/Discrete-Time Integrator1'
   *  Sum: '<S19>/Sum5'
   */
  rtb_Gain_i = (rtb_u_error_C_mPs -
                Controller_DW.DiscreteTimeIntegrator1_DSTAT_j) * 62.831852F;

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/FMS_Out'
   *  RelationalOperator: '<S3>/Compare'
   */
  if (Controller_U.FMS_Out.status == 3) {
    real_T tmp;
    int16_T rtb_DataTypeConversion1;

    /* Switch: '<S10>/Switch' incorporates:
     *  Constant: '<S18>/kp'
     *  Constant: '<S20>/Constant'
     *  DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
     *  Product: '<S18>/Multiply'
     *  RelationalOperator: '<S20>/Compare'
     *  Saturate: '<S16>/Saturation'
     *  Sum: '<S9>/Add'
     *  Switch: '<S19>/Switch'
     */
    if (Controller_U.FMS_Out.ctrl_mode == 6) {
      rtb_Saturation2 = 0.0F;
    } else {
      if (Controller_U.FMS_Out.reset > 0) {
        /* Switch: '<S19>/Switch' incorporates:
         *  Gain: '<S19>/Gain1'
         */
        rtb_Multiply_e = 0.0F * rtb_Gain_i;
      } else {
        /* Switch: '<S19>/Switch' */
        rtb_Multiply_e = rtb_Gain_i;
      }

      /* Product: '<S16>/Multiply' incorporates:
       *  Constant: '<S16>/kd'
       *  Switch: '<S19>/Switch'
       */
      rtb_Saturation2 = CONTROL_PARAM.VEL_XY_D * rtb_Multiply_e;

      /* Saturate: '<S16>/Saturation' */
      if (rtb_Saturation2 > CONTROL_PARAM.VEL_XY_D_MAX) {
        rtb_Saturation2 = CONTROL_PARAM.VEL_XY_D_MAX;
      } else if (rtb_Saturation2 < CONTROL_PARAM.VEL_XY_D_MIN) {
        rtb_Saturation2 = CONTROL_PARAM.VEL_XY_D_MIN;
      }

      rtb_Saturation2 += CONTROL_PARAM.VEL_XY_P * rtb_u_error_C_mPs +
        Controller_DW.DiscreteTimeIntegrator_DSTATE_i;
    }

    /* End of Switch: '<S10>/Switch' */

    /* Saturate: '<S5>/Saturation1' */
    if (rtb_Saturation2 > 1.0F) {
      rtb_Saturation2 = 1.0F;
    } else if (rtb_Saturation2 < -1.0F) {
      rtb_Saturation2 = -1.0F;
    }

    /* DataTypeConversion: '<S5>/Data Type Conversion1' incorporates:
     *  Constant: '<S5>/Constant4'
     *  Product: '<S5>/Product1'
     *  Saturate: '<S5>/Saturation1'
     */
    tmp = floor(rtb_Saturation2 * 10000.0);
    if (rtIsNaN(tmp)) {
      i = 0;
    } else {
      i = (int32_T)fmod(tmp, 65536.0);
    }

    rtb_DataTypeConversion1 = (int16_T)(i < 0 ? (int32_T)(int16_T)-(int16_T)
      (uint16_T)-(real_T)i : i);

    /* End of DataTypeConversion: '<S5>/Data Type Conversion1' */

    /* Switch: '<S29>/Switch' incorporates:
     *  Gain: '<S29>/Gain1'
     */
    if (Controller_U.FMS_Out.reset > 0) {
      rtb_Multiply_e = 0.0F * rtb_Gain;
    } else {
      rtb_Multiply_e = rtb_Gain;
    }

    /* Product: '<S26>/Multiply' incorporates:
     *  Constant: '<S26>/gain3'
     *  Switch: '<S29>/Switch'
     */
    rtb_Saturation2 = CONTROL_PARAM.YAW_RATE_D * rtb_Multiply_e;

    /* Saturate: '<S26>/Saturation' */
    if (rtb_Saturation2 > CONTROL_PARAM.RATE_D_MAX) {
      rtb_Saturation2 = CONTROL_PARAM.RATE_D_MAX;
    } else if (rtb_Saturation2 < CONTROL_PARAM.RATE_D_MIN) {
      rtb_Saturation2 = CONTROL_PARAM.RATE_D_MIN;
    }

    /* Sum: '<S24>/Add' incorporates:
     *  Constant: '<S28>/gain'
     *  DiscreteIntegrator: '<S25>/Discrete-Time Integrator5'
     *  DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
     *  Product: '<S28>/Multiply'
     *  Saturate: '<S26>/Saturation'
     */
    rtb_Saturation2 += CONTROL_PARAM.YAW_RATE_P *
      Controller_DW.DiscreteTimeIntegrator5_DSTATE +
      Controller_DW.DiscreteTimeIntegrator_DSTATE;

    /* Saturate: '<S5>/Saturation2' */
    if (rtb_Saturation2 > 1.0F) {
      rtb_Saturation2 = 1.0F;
    } else if (rtb_Saturation2 < -1.0F) {
      rtb_Saturation2 = -1.0F;
    }

    /* DataTypeConversion: '<S5>/Data Type Conversion' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     *  Product: '<S5>/Product'
     *  Saturate: '<S5>/Saturation2'
     *  Sum: '<S5>/Sum'
     */
    tmp = floor(rtb_Saturation2 * 500.0 + 750.0);
    if (rtIsNaN(tmp)) {
      /* Outport: '<Root>/Control_Out' */
      Controller_Y.Control_Out.actuator_cmd[0] = 0;
    } else {
      /* Outport: '<Root>/Control_Out' */
      Controller_Y.Control_Out.actuator_cmd[0] = (int16_T)(int32_T)tmp;
    }

    /* End of DataTypeConversion: '<S5>/Data Type Conversion' */

    /* Outport: '<Root>/Control_Out' incorporates:
     *  Reshape: '<S5>/Reshape'
     */
    Controller_Y.Control_Out.actuator_cmd[1] = rtb_DataTypeConversion1;
    Controller_Y.Control_Out.actuator_cmd[2] = rtb_DataTypeConversion1;
    for (i = 0; i < 13; i++) {
      Controller_Y.Control_Out.actuator_cmd[i + 3] = 0;
    }
  } else {
    /* Outport: '<Root>/Control_Out' */
    for (i = 0; i < 16; i++) {
      Controller_Y.Control_Out.actuator_cmd[i] = (int16_T)
        Controller_U.FMS_Out.actuator_cmd[i];
    }
  }

  /* End of Switch: '<S1>/Switch' */

  /* Outport: '<Root>/Control_Out' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
   */
  Controller_Y.Control_Out.timestamp =
    Controller_DW.DiscreteTimeIntegrator_DSTATE_p;

  /* Product: '<S15>/Multiply1' incorporates:
   *  Constant: '<S15>/const1'
   *  DiscreteIntegrator: '<S12>/Integrator'
   */
  rtb_Subtract3 = Controller_DW.Integrator_DSTATE * 0.05F;

  /* Sum: '<S15>/Add' incorporates:
   *  DiscreteIntegrator: '<S12>/Integrator1'
   *  Inport: '<Root>/FMS_Out'
   *  Sum: '<S12>/Subtract'
   */
  rtb_Subtract1 = (Controller_DW.Integrator1_DSTATE - Controller_U.FMS_Out.u_cmd)
    + rtb_Subtract3;

  /* Signum: '<S15>/Sign' */
  if (rtIsNaNF(rtb_Subtract1)) {
    rtb_Multiply_e = (rtNaNF);
  } else if (rtb_Subtract1 < 0.0F) {
    rtb_Multiply_e = -1.0F;
  } else {
    rtb_Multiply_e = (real32_T)(rtb_Subtract1 > 0.0F);
  }

  /* Sum: '<S15>/Add2' incorporates:
   *  Abs: '<S15>/Abs'
   *  Gain: '<S15>/Gain'
   *  Gain: '<S15>/Gain1'
   *  Product: '<S15>/Multiply2'
   *  Product: '<S15>/Multiply3'
   *  Signum: '<S15>/Sign'
   *  Sqrt: '<S15>/Sqrt'
   *  Sum: '<S15>/Add1'
   *  Sum: '<S15>/Subtract'
   */
  rtb_Saturation2 = (sqrtf((8.0F * fabsf(rtb_Subtract1) + Controller_ConstB.d) *
    Controller_ConstB.d) - Controller_ConstB.d) * 0.5F * rtb_Multiply_e +
    rtb_Subtract3;

  /* Sum: '<S15>/Add3' */
  rtb_Multiply_e = rtb_Subtract1 + Controller_ConstB.d;

  /* Sum: '<S15>/Subtract1' */
  u = rtb_Subtract1 - Controller_ConstB.d;

  /* Signum: '<S15>/Sign1' */
  if (rtIsNaNF(rtb_Multiply_e)) {
    rtb_Multiply_e = (rtNaNF);
  } else if (rtb_Multiply_e < 0.0F) {
    rtb_Multiply_e = -1.0F;
  } else {
    rtb_Multiply_e = (real32_T)(rtb_Multiply_e > 0.0F);
  }

  /* Signum: '<S15>/Sign2' */
  if (rtIsNaNF(u)) {
    u = (rtNaNF);
  } else if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Sum: '<S15>/Add5' incorporates:
   *  Gain: '<S15>/Gain2'
   *  Product: '<S15>/Multiply4'
   *  Signum: '<S15>/Sign1'
   *  Signum: '<S15>/Sign2'
   *  Sum: '<S15>/Add4'
   *  Sum: '<S15>/Subtract2'
   */
  rtb_Saturation2 += ((rtb_Subtract1 - rtb_Saturation2) + rtb_Subtract3) *
    ((rtb_Multiply_e - u) * 0.5F);

  /* Product: '<S27>/Multiply' incorporates:
   *  Constant: '<S27>/gain3'
   *  DiscreteIntegrator: '<S25>/Discrete-Time Integrator5'
   */
  rtb_Multiply_e = CONTROL_PARAM.YAW_RATE_I *
    Controller_DW.DiscreteTimeIntegrator5_DSTATE;

  /* Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S25>/Gain'
   *  Sum: '<S25>/Sum5'
   */
  Controller_DW.DiscreteTimeIntegrator5_IC_LOAD = 0U;
  Controller_DW.DiscreteTimeIntegrator5_DSTATE += (rtb_DiscreteTimeIntegrator1_l
    - Controller_DW.DiscreteTimeIntegrator5_DSTATE) * 188.49556F * 0.002F;

  /* Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  Controller_DW.DiscreteTimeIntegrator_DSTATE += 0.002F * rtb_Multiply_e;
  if (Controller_DW.DiscreteTimeIntegrator_DSTATE >= CONTROL_PARAM.RATE_I_MAX) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MAX;
  } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE <=
             CONTROL_PARAM.RATE_I_MIN) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MIN;
  }

  Controller_DW.DiscreteTimeIntegrator_PrevRese = (int8_T)
    (Controller_U.FMS_Out.reset > 0);

  /* End of Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S29>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  Controller_DW.DiscreteTimeIntegrator1_DSTATE += 0.002F * rtb_Gain;
  Controller_DW.DiscreteTimeIntegrator1_PrevRes = (int8_T)
    (Controller_U.FMS_Out.reset > 0);

  /* Update for DiscreteIntegrator: '<S12>/Integrator1' incorporates:
   *  DiscreteIntegrator: '<S12>/Integrator'
   */
  Controller_DW.Integrator1_DSTATE += 0.002F * Controller_DW.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S17>/ki'
   *  Inport: '<Root>/FMS_Out'
   *  Product: '<S17>/Multiply'
   */
  Controller_DW.DiscreteTimeIntegrator_DSTATE_i += CONTROL_PARAM.VEL_XY_I *
    rtb_u_error_C_mPs * 0.002F;
  if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i >=
      CONTROL_PARAM.VEL_XY_I_MAX) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MAX;
  } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i <=
             CONTROL_PARAM.VEL_XY_I_MIN) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MIN;
  }

  Controller_DW.DiscreteTimeIntegrator_PrevRe_k = (int8_T)
    (Controller_U.FMS_Out.reset > 0);

  /* End of Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/FMS_Out'
   */
  Controller_DW.DiscreteTimeIntegrator1_DSTAT_j += 0.002F * rtb_Gain_i;
  Controller_DW.DiscreteTimeIntegrator1_PrevR_l = (int8_T)
    (Controller_U.FMS_Out.reset > 0);

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S4>/Constant'
   */
  Controller_DW.DiscreteTimeIntegrator_DSTATE_p += CONTROL_EXPORT.period;

  /* Signum: '<S15>/Sign5' */
  if (rtIsNaNF(rtb_Saturation2)) {
    /* Signum: '<S15>/Sign6' */
    rtb_DiscreteTimeIntegrator1_l = (rtNaNF);
  } else if (rtb_Saturation2 < 0.0F) {
    /* Signum: '<S15>/Sign6' */
    rtb_DiscreteTimeIntegrator1_l = -1.0F;
  } else {
    /* Signum: '<S15>/Sign6' */
    rtb_DiscreteTimeIntegrator1_l = (real32_T)(rtb_Saturation2 > 0.0F);
  }

  /* Sum: '<S15>/Add6' */
  rtb_Multiply_e = rtb_Saturation2 + Controller_ConstB.d;

  /* Sum: '<S15>/Subtract3' */
  u = rtb_Saturation2 - Controller_ConstB.d;

  /* Signum: '<S15>/Sign3' */
  if (rtIsNaNF(rtb_Multiply_e)) {
    rtb_Multiply_e = (rtNaNF);
  } else if (rtb_Multiply_e < 0.0F) {
    rtb_Multiply_e = -1.0F;
  } else {
    rtb_Multiply_e = (real32_T)(rtb_Multiply_e > 0.0F);
  }

  /* Signum: '<S15>/Sign4' */
  if (rtIsNaNF(u)) {
    u = (rtNaNF);
  } else if (u < 0.0F) {
    u = -1.0F;
  } else {
    u = (real32_T)(u > 0.0F);
  }

  /* Update for DiscreteIntegrator: '<S12>/Integrator' incorporates:
   *  Constant: '<S15>/const'
   *  Gain: '<S15>/Gain3'
   *  Product: '<S15>/Divide'
   *  Product: '<S15>/Multiply5'
   *  Product: '<S15>/Multiply6'
   *  Signum: '<S15>/Sign3'
   *  Signum: '<S15>/Sign4'
   *  Signum: '<S15>/Sign5'
   *  Sum: '<S15>/Subtract4'
   *  Sum: '<S15>/Subtract5'
   *  Sum: '<S15>/Subtract6'
   */
  Controller_DW.Integrator_DSTATE += ((rtb_Saturation2 / Controller_ConstB.d -
    rtb_DiscreteTimeIntegrator1_l) * Controller_ConstB.Gain4 * ((rtb_Multiply_e
    - u) * 0.5F) - rtb_DiscreteTimeIntegrator1_l * 58.836F) * 0.002F;
}

/* Model initialize function */
void Controller_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator5' */
  Controller_DW.DiscreteTimeIntegrator5_IC_LOAD = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' */
  Controller_DW.DiscreteTimeIntegrator_DSTATE = Controller_ConstB.Constant_o;
  if (Controller_DW.DiscreteTimeIntegrator_DSTATE >= CONTROL_PARAM.RATE_I_MAX) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MAX;
  } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE <=
             CONTROL_PARAM.RATE_I_MIN) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE = CONTROL_PARAM.RATE_I_MIN;
  }

  /* End of InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' */

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
  Controller_DW.DiscreteTimeIntegrator_DSTATE_i = Controller_ConstB.Constant;
  if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i >=
      CONTROL_PARAM.VEL_XY_I_MAX) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MAX;
  } else if (Controller_DW.DiscreteTimeIntegrator_DSTATE_i <=
             CONTROL_PARAM.VEL_XY_I_MIN) {
    Controller_DW.DiscreteTimeIntegrator_DSTATE_i = CONTROL_PARAM.VEL_XY_I_MIN;
  }

  /* End of InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
}

/* Model terminate function */
void Controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
