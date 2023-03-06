/*
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.54
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Mar  2 15:20:36 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"

/* Invariant block signals (default storage) */
const ConstB_Controller_T Controller_ConstB = {
  { 0.0F, 0.0F, 1.0F },                /* '<S14>/Vector Concatenate3' */
  -58.836F,                            /* '<S15>/Gain4' */
  0.00250000018F,                      /* '<S15>/Square' */
  0.14709F,                            /* '<S15>/Multiply' */
  0.0F,                                /* '<S17>/Constant' */
  0.0F                                 /* '<S27>/Constant' */
};

/* Constant parameters (default storage) */
const ConstP_Controller_T Controller_ConstP = {
  /* Computed Parameter: X_Frame_Effective_Matrix_Value
   * Referenced by: '<S5>/X_Frame_Effective_Matrix'
   */
  { 0.0F, 1.0F, 1.0F, 1.0F, 1.0F, -1.0F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
