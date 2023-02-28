/*
 * File: FMS_data.c
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

/* Invariant block signals (default storage) */
const ConstB_FMS_T FMS_ConstB = {
  -1.04719758F,                        /* '<S60>/Gain4' */
  0.616850317F,                        /* '<S60>/Square' */
  0.645964146F,                        /* '<S60>/Multiply' */

  { 0.0F, 1.0F },

  { 0.0F, 1.0F },                      /* '<S64>/Math Function' */
  1.0F,                                /* '<S64>/Sum of Elements' */
  1.0F,                                /* '<S64>/Math Function1' */

  { 0.0F, 0.0F },                      /* '<S64>/Product' */

  { 0.0F, 1.0F, 1.0F },                /* '<S64>/Switch' */

  { 0.0F, 1.0F },                      /* '<S64>/Divide' */

  { 0.0F, 0.0F, 1.0F },                /* '<S118>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S129>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S131>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S191>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S194>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S197>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S198>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S205>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S207>/Vector Concatenate3' */
  -1.04719758F,                        /* '<S337>/Gain4' */
  0.616850317F,                        /* '<S337>/Square' */
  0.645964146F,                        /* '<S337>/Multiply' */

  { 0.0F, 1.0F },

  { 0.0F, 1.0F },                      /* '<S341>/Math Function' */
  1.0F,                                /* '<S341>/Sum of Elements' */
  1.0F,                                /* '<S341>/Math Function1' */

  { 0.0F, 0.0F },                      /* '<S341>/Product' */

  { 0.0F, 1.0F, 1.0F },                /* '<S341>/Switch' */

  { 0.0F, 1.0F },                      /* '<S341>/Divide' */

  { 0.0F, 0.0F, 1.0F },                /* '<S391>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S324>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S396>/Vector Concatenate3' */
  1U,                                  /* '<S38>/Data Type Conversion' */
  12U,                                 /* '<S38>/Data Type Conversion1' */
  3U,                                  /* '<S39>/Data Type Conversion' */
  10U,                                 /* '<S39>/Data Type Conversion1' */
  5U,                                  /* '<S39>/Data Type Conversion2' */
  3U,                                  /* '<S40>/Data Type Conversion' */
  8U,                                  /* '<S40>/Data Type Conversion1' */
  5U,                                  /* '<S40>/Data Type Conversion2' */
  3U,                                  /* '<S47>/Data Type Conversion' */
  4U,                                  /* '<S47>/Data Type Conversion1' */
  5U,                                  /* '<S47>/Data Type Conversion2' */
  3U,                                  /* '<S44>/Data Type Conversion' */
  3U,                                  /* '<S44>/Data Type Conversion1' */
  6U,                                  /* '<S44>/Data Type Conversion2' */
  1U,                                  /* '<S281>/Data Type Conversion' */
  1U,                                  /* '<S281>/Data Type Conversion1' */
  3U,                                  /* '<S277>/Data Type Conversion' */
  6U,                                  /* '<S277>/Data Type Conversion1' */
  5U,                                  /* '<S277>/Data Type Conversion2' */
  3U,                                  /* '<S279>/Data Type Conversion' */
  16U,                                 /* '<S279>/Data Type Conversion1' */
  5U,                                  /* '<S279>/Data Type Conversion2' */
  3U,                                  /* '<S278>/Data Type Conversion' */
  15U,                                 /* '<S278>/Data Type Conversion1' */
  5U,                                  /* '<S278>/Data Type Conversion2' */
  3U,                                  /* '<S280>/Data Type Conversion' */
  17U,                                 /* '<S280>/Data Type Conversion1' */
  5U,                                  /* '<S280>/Data Type Conversion2' */
  2U,                                  /* '<S36>/Data Type Conversion1' */
  2U,                                  /* '<S36>/Data Type Conversion2' */

  /* Start of '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
  {
    1.9966471893352524,                /* '<S400>/Sum' */
    0.0066943799901413165,             /* '<S400>/Multiply3' */
    0.99330562000985867                /* '<S400>/Sum4' */
  }
  ,

  /* End of '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */

  /* Start of '<S33>/Unknown' */
  {
    1U,                                /* '<S42>/Data Type Conversion' */
    1U                                 /* '<S42>/Data Type Conversion1' */
  }
  ,

  /* End of '<S33>/Unknown' */

  /* Start of '<S235>/Move Control' */
  {
    -58.836F,                          /* '<S246>/Gain4' */
    0.00250000018F,                    /* '<S246>/Square' */
    0.14709F                           /* '<S246>/Multiply' */
  }
  ,

  /* End of '<S235>/Move Control' */

  /* Start of '<S235>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S242>/Vector Concatenate3' */
  }
  ,

  /* End of '<S235>/Hold Control' */

  /* Start of '<S222>/Move Control' */
  {
    -15.707963F,                       /* '<S232>/Gain4' */
    0.0004F,                           /* '<S232>/Square' */
    0.00628318498F                     /* '<S232>/Multiply' */
  }
  ,

  /* End of '<S222>/Move Control' */

  /* Start of '<S211>/Move Control' */
  {
    -78.448F,                          /* '<S219>/Gain4' */
    0.00250000018F,                    /* '<S219>/Square' */
    0.196120009F                       /* '<S219>/Multiply' */
  }
  ,

  /* End of '<S211>/Move Control' */

  /* Start of '<S264>/Move Control' */
  {
    -58.836F,                          /* '<S275>/Gain4' */
    0.00250000018F,                    /* '<S275>/Square' */
    0.14709F                           /* '<S275>/Multiply' */
  }
  ,

  /* End of '<S264>/Move Control' */

  /* Start of '<S264>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S271>/Vector Concatenate3' */
  }
  ,

  /* End of '<S264>/Hold Control' */

  /* Start of '<S252>/Move Control' */
  {
    -15.707963F,                       /* '<S262>/Gain4' */
    0.0004F,                           /* '<S262>/Square' */
    0.00628318498F                     /* '<S262>/Multiply' */
  }
  ,

  /* End of '<S252>/Move Control' */

  /* Start of '<S37>/Unknown' */
  {
    1U,                                /* '<S45>/Data Type Conversion' */
    1U                                 /* '<S45>/Data Type Conversion1' */
  }
  ,

  /* End of '<S37>/Unknown' */

  /* Start of '<S88>/Move Control' */
  {
    -58.836F,                          /* '<S99>/Gain4' */
    0.00250000018F,                    /* '<S99>/Square' */
    0.14709F                           /* '<S99>/Multiply' */
  }
  ,

  /* End of '<S88>/Move Control' */

  /* Start of '<S88>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S95>/Vector Concatenate3' */
  }
  ,

  /* End of '<S88>/Hold Control' */

  /* Start of '<S78>/Move Control' */
  {
    -78.448F,                          /* '<S86>/Gain4' */
    0.00250000018F,                    /* '<S86>/Square' */
    0.196120009F                       /* '<S86>/Multiply' */
  }
  ,

  /* End of '<S78>/Move Control' */

  /* Start of '<S307>/Move Control' */
  {
    -58.836F,                          /* '<S318>/Gain4' */
    0.00250000018F,                    /* '<S318>/Square' */
    0.14709F                           /* '<S318>/Multiply' */
  }
  ,

  /* End of '<S307>/Move Control' */

  /* Start of '<S307>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S314>/Vector Concatenate3' */
  }
  ,

  /* End of '<S307>/Hold Control' */

  /* Start of '<S295>/Move Control' */
  {
    -15.707963F,                       /* '<S305>/Gain4' */
    0.0004F,                           /* '<S305>/Square' */
    0.00628318498F                     /* '<S305>/Multiply' */
  }
  ,

  /* End of '<S295>/Move Control' */

  /* Start of '<S285>/Move Control' */
  {
    -78.448F,                          /* '<S293>/Gain4' */
    0.00250000018F,                    /* '<S293>/Square' */
    0.196120009F                       /* '<S293>/Multiply' */
  }
  ,

  /* End of '<S285>/Move Control' */

  /* Start of '<S361>/Move Control' */
  {
    -58.836F,                          /* '<S372>/Gain4' */
    0.00250000018F,                    /* '<S372>/Square' */
    0.14709F                           /* '<S372>/Multiply' */
  }
  ,

  /* End of '<S361>/Move Control' */

  /* Start of '<S361>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S368>/Vector Concatenate3' */
  }
  ,

  /* End of '<S361>/Hold Control' */

  /* Start of '<S351>/Move Control' */
  {
    -78.448F,                          /* '<S359>/Gain4' */
    0.00250000018F,                    /* '<S359>/Square' */
    0.196120009F                       /* '<S359>/Multiply' */
  }
  ,

  /* End of '<S351>/Move Control' */

  /* Start of '<S31>/Disarm' */
  {
    1U,                                /* '<S35>/Data Type Conversion' */
    1U                                 /* '<S35>/Data Type Conversion1' */
  }
  /* End of '<S31>/Disarm' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
