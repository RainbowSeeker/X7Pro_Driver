/*
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.903
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Dec  1 10:31:19 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"

/* Invariant block signals (default storage) */
const ConstB_Controller_T Controller_ConstB = {
  { 0.0F, 0.0F, 0.0F },                /* '<S20>/Constant' */
  19.1986F,                            /* '<S32>/Gain' */

  { 0.0F, 0.0F, 1.0F },                /* '<S44>/Vector Concatenate3' */
  -58.836F,                            /* '<S45>/Gain4' */
  0.00250000018F,                      /* '<S45>/Square' */
  0.14709F,                            /* '<S45>/Multiply' */
  0.0F,                                /* '<S47>/Constant' */
  -78.448F,                            /* '<S64>/Gain4' */
  0.00250000018F,                      /* '<S64>/Square' */
  0.196120009F,                        /* '<S64>/Multiply' */
  0.0F                                 /* '<S66>/Constant' */
};

/* Constant parameters (default storage) */
const ConstP_Controller_T Controller_ConstP = {
  /* Computed Parameter: X_Frame_Effective_Matrix_Value
   * Referenced by: '<S6>/X_Frame_Effective_Matrix'
   */
  { -1.0F, 1.0F, 1.0F, -1.0F, 1.0F, -1.0F, 1.0F, -1.0F, 1.0F, 1.0F, -1.0F, -1.0F
  }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
