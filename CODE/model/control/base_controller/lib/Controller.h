/*
 * File: Controller.h
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

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#ifndef Controller_COMMON_INCLUDES_
#define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

#include "Controller_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTimeIntegrator5_DSTATE;/* '<S25>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S27>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S29>/Discrete-Time Integrator1' */
  real32_T Integrator1_DSTATE;         /* '<S12>/Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_i;/* '<S17>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTAT_j;/* '<S19>/Discrete-Time Integrator1' */
  real32_T Integrator_DSTATE;          /* '<S12>/Integrator' */
  uint32_T DiscreteTimeIntegrator_DSTATE_p;/* '<S4>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S27>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S29>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_k;/* '<S17>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevR_l;/* '<S19>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator5_IC_LOAD;/* '<S25>/Discrete-Time Integrator5' */
} DW_Controller_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T VectorConcatenate3[3];/* '<S14>/Vector Concatenate3' */
  const real32_T Gain4;                /* '<S15>/Gain4' */
  const real32_T Square;               /* '<S15>/Square' */
  const real32_T d;                    /* '<S15>/Multiply' */
  const real32_T Constant;             /* '<S17>/Constant' */
  const real32_T Constant_o;           /* '<S27>/Constant' */
} ConstB_Controller_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  FMS_Out_Bus FMS_Out;                 /* '<Root>/FMS_Out' */
  INS_Out_Bus INS_Out;                 /* '<Root>/INS_Out' */
} ExtU_Controller_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  Control_Out_Bus Control_Out;         /* '<Root>/Control_Out' */
} ExtY_Controller_T;

/* Real-time Model Data Structure */
struct tag_RTM_Controller_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_Controller_T Controller_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Controller_T Controller_Y;
extern const ConstB_Controller_T Controller_ConstB;/* constant block i/o */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern struct_Ae52N6uY2eO0jd5TMQiCYB CONTROL_PARAM;/* Variable: CONTROL_PARAM
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
extern struct_ny3PY9hontv4J5WqwlFzJB CONTROL_EXPORT;/* Variable: CONTROL_EXPORT
                                                     * Referenced by: '<S4>/Constant'
                                                     */

/* Model entry point functions */
extern void Controller_initialize(void);
extern void Controller_step(void);
extern void Controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Controller_T *const Controller_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Gain1' : Unused code path elimination
 * Block '<S5>/Multiply' : Unused code path elimination
 * Block '<S5>/Saturation' : Unused code path elimination
 * Block '<S5>/X_Frame_Effective_Matrix' : Unused code path elimination
 * Block '<S4>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * '<Root>' : 'Controller'
 * '<S1>'   : 'Controller/Bus_Constructor'
 * '<S2>'   : 'Controller/Controller'
 * '<S3>'   : 'Controller/Bus_Constructor/Compare To Constant'
 * '<S4>'   : 'Controller/Bus_Constructor/timestamp'
 * '<S5>'   : 'Controller/Controller/Control_Allocation'
 * '<S6>'   : 'Controller/Controller/Movement_Controller'
 * '<S7>'   : 'Controller/Controller/Rotate_Controller'
 * '<S8>'   : 'Controller/Controller/Movement_Controller/Error'
 * '<S9>'   : 'Controller/Controller/Movement_Controller/PID_Controller'
 * '<S10>'  : 'Controller/Controller/Movement_Controller/Signal_Select'
 * '<S11>'  : 'Controller/Controller/Movement_Controller/Error/Bus_Select'
 * '<S12>'  : 'Controller/Controller/Movement_Controller/Error/TD'
 * '<S13>'  : 'Controller/Controller/Movement_Controller/Error/Bus_Select/Psi To DCM'
 * '<S14>'  : 'Controller/Controller/Movement_Controller/Error/Bus_Select/Psi To DCM/Rotation Matrix Z'
 * '<S15>'  : 'Controller/Controller/Movement_Controller/Error/TD/fhan '
 * '<S16>'  : 'Controller/Controller/Movement_Controller/PID_Controller/D_Control'
 * '<S17>'  : 'Controller/Controller/Movement_Controller/PID_Controller/I_Control'
 * '<S18>'  : 'Controller/Controller/Movement_Controller/PID_Controller/P_Control'
 * '<S19>'  : 'Controller/Controller/Movement_Controller/PID_Controller/D_Control/DT Filter'
 * '<S20>'  : 'Controller/Controller/Movement_Controller/Signal_Select/Offboard'
 * '<S21>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller'
 * '<S22>'  : 'Controller/Controller/Rotate_Controller/Signal_Select'
 * '<S23>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/Error'
 * '<S24>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/PID_Controller'
 * '<S25>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/Error/First Order LPF1'
 * '<S26>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/PID_Controller/D_Control'
 * '<S27>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/PID_Controller/I_Control'
 * '<S28>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/PID_Controller/P_Control'
 * '<S29>'  : 'Controller/Controller/Rotate_Controller/Rate_Controller/PID_Controller/D_Control/DT Filter'
 * '<S30>'  : 'Controller/Controller/Rotate_Controller/Signal_Select/Compare To Constant'
 * '<S31>'  : 'Controller/Controller/Rotate_Controller/Signal_Select/Compare To Constant1'
 * '<S32>'  : 'Controller/Controller/Rotate_Controller/Signal_Select/Offboard_Signal_Select'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
