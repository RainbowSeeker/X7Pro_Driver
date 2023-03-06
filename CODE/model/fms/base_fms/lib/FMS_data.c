/*
 * File: FMS_data.c
 *
 * Code generated for Simulink model 'FMS'.
 *
 * Model version                  : 9.85
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Mar  4 19:48:47 2023
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
  -1.04719758F,                        /* '<S325>/Gain4' */
  0.616850317F,                        /* '<S325>/Square' */
  0.645964146F,                        /* '<S325>/Multiply' */

  { 0.0F, 1.0F },

  { 0.0F, 1.0F },                      /* '<S329>/Math Function' */
  1.0F,                                /* '<S329>/Sum of Elements' */
  1.0F,                                /* '<S329>/Math Function1' */

  { 0.0F, 0.0F },                      /* '<S329>/Product' */

  { 0.0F, 1.0F, 1.0F },                /* '<S329>/Switch' */

  { 0.0F, 1.0F },                      /* '<S329>/Divide' */

  { 0.0F, 0.0F, 1.0F },                /* '<S379>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S312>/Vector Concatenate3' */

  { 0.0F, 0.0F, 1.0F },                /* '<S384>/Vector Concatenate3' */
  1U,                                  /* '<S38>/Data Type Conversion' */
  12U,                                 /* '<S38>/Data Type Conversion1' */
  3U,                                  /* '<S39>/Data Type Conversion' */
  10U,                                 /* '<S39>/Data Type Conversion1' */
  5U,                                  /* '<S39>/Data Type Conversion2' */
  3U,                                  /* '<S40>/Data Type Conversion' */
  8U,                                  /* '<S40>/Data Type Conversion1' */
  5U,                                  /* '<S40>/Data Type Conversion2' */
  1U,                                  /* '<S45>/Data Type Conversion' */
  1U,                                  /* '<S45>/Data Type Conversion1' */
  3U,                                  /* '<S47>/Data Type Conversion' */
  4U,                                  /* '<S47>/Data Type Conversion1' */
  5U,                                  /* '<S47>/Data Type Conversion2' */
  3U,                                  /* '<S44>/Data Type Conversion' */
  3U,                                  /* '<S44>/Data Type Conversion1' */
  6U,                                  /* '<S44>/Data Type Conversion2' */
  3U,                                  /* '<S265>/Data Type Conversion' */
  6U,                                  /* '<S265>/Data Type Conversion1' */
  5U,                                  /* '<S265>/Data Type Conversion2' */
  3U,                                  /* '<S267>/Data Type Conversion' */
  16U,                                 /* '<S267>/Data Type Conversion1' */
  5U,                                  /* '<S267>/Data Type Conversion2' */
  3U,                                  /* '<S266>/Data Type Conversion' */
  15U,                                 /* '<S266>/Data Type Conversion1' */
  5U,                                  /* '<S266>/Data Type Conversion2' */
  3U,                                  /* '<S268>/Data Type Conversion' */
  17U,                                 /* '<S268>/Data Type Conversion1' */
  5U,                                  /* '<S268>/Data Type Conversion2' */
  2U,                                  /* '<S36>/Data Type Conversion1' */
  2U,                                  /* '<S36>/Data Type Conversion2' */

  /* Start of '<S6>/Vehicle.Arm.Auto.Mission.LLA2FLAT' */
  {
    1.9966471893352524,                /* '<S388>/Sum' */
    0.0066943799901413165,             /* '<S388>/Multiply3' */
    0.99330562000985867                /* '<S388>/Sum4' */
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

  /* Start of '<S223>/Move Control' */
  {
    -58.836F,                          /* '<S234>/Gain4' */
    0.00250000018F,                    /* '<S234>/Square' */
    0.14709F                           /* '<S234>/Multiply' */
  }
  ,

  /* End of '<S223>/Move Control' */

  /* Start of '<S223>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S230>/Vector Concatenate3' */
  }
  ,

  /* End of '<S223>/Hold Control' */

  /* Start of '<S210>/Move Control' */
  {
    -15.707963F,                       /* '<S220>/Gain4' */
    0.0004F,                           /* '<S220>/Square' */
    0.00628318498F                     /* '<S220>/Multiply' */
  }
  ,

  /* End of '<S210>/Move Control' */

  /* Start of '<S252>/Move Control' */
  {
    -58.836F,                          /* '<S263>/Gain4' */
    0.00250000018F,                    /* '<S263>/Square' */
    0.14709F                           /* '<S263>/Multiply' */
  }
  ,

  /* End of '<S252>/Move Control' */

  /* Start of '<S252>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S259>/Vector Concatenate3' */
  }
  ,

  /* End of '<S252>/Hold Control' */

  /* Start of '<S240>/Move Control' */
  {
    -15.707963F,                       /* '<S250>/Gain4' */
    0.0004F,                           /* '<S250>/Square' */
    0.00628318498F                     /* '<S250>/Multiply' */
  }
  ,

  /* End of '<S240>/Move Control' */

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

  /* Start of '<S41>/Unknown' */
  {
    1U,                                /* '<S269>/Data Type Conversion' */
    1U                                 /* '<S269>/Data Type Conversion1' */
  }
  ,

  /* End of '<S41>/Unknown' */

  /* Start of '<S295>/Move Control' */
  {
    -58.836F,                          /* '<S306>/Gain4' */
    0.00250000018F,                    /* '<S306>/Square' */
    0.14709F                           /* '<S306>/Multiply' */
  }
  ,

  /* End of '<S295>/Move Control' */

  /* Start of '<S295>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S302>/Vector Concatenate3' */
  }
  ,

  /* End of '<S295>/Hold Control' */

  /* Start of '<S283>/Move Control' */
  {
    -15.707963F,                       /* '<S293>/Gain4' */
    0.0004F,                           /* '<S293>/Square' */
    0.00628318498F                     /* '<S293>/Multiply' */
  }
  ,

  /* End of '<S283>/Move Control' */

  /* Start of '<S273>/Move Control' */
  {
    -78.448F,                          /* '<S281>/Gain4' */
    0.00250000018F,                    /* '<S281>/Square' */
    0.196120009F                       /* '<S281>/Multiply' */
  }
  ,

  /* End of '<S273>/Move Control' */

  /* Start of '<S349>/Move Control' */
  {
    -58.836F,                          /* '<S360>/Gain4' */
    0.00250000018F,                    /* '<S360>/Square' */
    0.14709F                           /* '<S360>/Multiply' */
  }
  ,

  /* End of '<S349>/Move Control' */

  /* Start of '<S349>/Hold Control' */
  {
    { 0.0F, 0.0F, 1.0F }               /* '<S356>/Vector Concatenate3' */
  }
  ,

  /* End of '<S349>/Hold Control' */

  /* Start of '<S339>/Move Control' */
  {
    -78.448F,                          /* '<S347>/Gain4' */
    0.00250000018F,                    /* '<S347>/Square' */
    0.196120009F                       /* '<S347>/Multiply' */
  }
  ,

  /* End of '<S339>/Move Control' */

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
