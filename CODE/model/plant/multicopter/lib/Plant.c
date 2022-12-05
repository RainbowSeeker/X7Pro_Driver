/*
 * File: Plant.c
 *
 * Code generated for Simulink model 'Plant'.
 *
 * Model version                  : 1.760
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Dec  1 10:46:57 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Plant.h"
#include "rtwtypes.h"
#include "arm_math.h"
#include <math.h>
#include "Plant_private.h"
#include <string.h>
#include "Plant_types.h"

/* Exported block parameters */
struct_zjTVXoT1Wcig2PfNqPD1gB PLANT_EXPORT = {
  2U,

  { 77, 117, 108, 116, 105, 99, 111, 112, 116, 101, 114, 32, 118, 48, 46, 50, 46,
    50, 0 }
} ;                                    /* Variable: PLANT_EXPORT
                                        * Referenced by:
                                        *   '<S20>/dt'
                                        *   '<S66>/dt'
                                        */

/* Block states (default storage) */
DW_Plant_T Plant_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Plant_T Plant_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Plant_T Plant_Y;

/* Real-time model */
static RT_MODEL_Plant_T Plant_M_;
RT_MODEL_Plant_T *const Plant_M = &Plant_M_;
static void rate_scheduler(void);
const Control_Out_Bus Plant_rtZControl_Out_Bus = { 0U,/* timestamp */
  { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }/* actuator_cmd */
};

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Plant_M->Timing.TaskCounters.TID[1])++;
  if ((Plant_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.01s, 0.0s] */
    Plant_M->Timing.TaskCounters.TID[1] = 0;
  }

  (Plant_M->Timing.TaskCounters.TID[2])++;
  if ((Plant_M->Timing.TaskCounters.TID[2]) > 49) {/* Sample time: [0.1s, 0.0s] */
    Plant_M->Timing.TaskCounters.TID[2] = 0;
  }
}

void rt_mldivide_U1f3x3_U2f3x1_Yf3x1(const real32_T u0[9], const real32_T u1[3],
  real32_T y[3])
{
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real32_T A[9];
  real32_T a21;
  real32_T maxval;
  for (r1 = 0; r1 < 9; r1++) {
    A[r1] = u0[r1];
  }

  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabsf(u0[0]);
  a21 = fabsf(u0[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabsf(u0[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  A[r2] = u0[r2] / u0[r1];
  A[r3] /= A[r1];
  A[r2 + 3] -= A[r1 + 3] * A[r2];
  A[r3 + 3] -= A[r1 + 3] * A[r3];
  A[r2 + 6] -= A[r1 + 6] * A[r2];
  A[r3 + 6] -= A[r1 + 6] * A[r3];
  if (fabsf(A[r3 + 3]) > fabsf(A[r2 + 3])) {
    int32_T rtemp;
    rtemp = r2 + 1;
    r2 = r3;
    r3 = rtemp - 1;
  }

  A[r3 + 3] /= A[r2 + 3];
  A[r3 + 6] -= A[r3 + 3] * A[r2 + 6];
  y[1] = u1[r2] - u1[r1] * A[r2];
  y[2] = (u1[r3] - u1[r1] * A[r3]) - A[r3 + 3] * y[1];
  maxval = y[2] / A[r3 + 6];
  y[2] = maxval;
  y[0] = u1[r1] - A[r1 + 6] * maxval;
  y[1] -= A[r2 + 6] * maxval;
  maxval = y[1] / A[r2 + 3];
  y[1] = maxval;
  y[0] -= A[r1 + 3] * maxval;
  y[0] /= A[r1];
}

void RandSrc_GZ_R(real32_T y[], const real32_T mean[], int32_T meanLen, const
                  real32_T xstd[], int32_T xstdLen, uint32_T state[], int32_T
                  nChans, int32_T nSamps)
{
  int32_T chan;
  int32_T samp;
  static const real32_T vt[65] = { 0.340945F, 0.45731461F, 0.539779305F,
    0.606242716F, 0.663169086F, 0.713697493F, 0.759612501F, 0.80203563F,
    0.841722727F, 0.879210174F, 0.914894819F, 0.949079096F, 0.98200053F,
    1.01384926F, 1.04478097F, 1.07492542F, 1.10439169F, 1.13327384F, 1.16165304F,
    1.18960094F, 1.21718144F, 1.24445164F, 1.27146351F, 1.29826498F, 1.32490075F,
    1.35141253F, 1.37783992F, 1.40422106F, 1.43059289F, 1.45699155F, 1.48345268F,
    1.51001215F, 1.53670609F, 1.56357121F, 1.59064543F, 1.61796796F, 1.64558017F,
    1.67352545F, 1.7018503F, 1.73060453F, 1.75984216F, 1.78962231F, 1.82001F,
    1.85107696F, 1.88290441F, 1.91558313F, 1.9492166F, 1.98392391F, 2.0198431F,
    2.05713558F, 2.09599304F, 2.13664508F, 2.17937136F, 2.22451758F, 2.27251863F,
    2.32393384F, 2.37950087F, 2.44022179F, 2.50751162F, 2.58346581F, 2.67139149F,
    2.77699423F, 2.77699423F, 2.77699423F, 2.77699423F };

  /* S-Function (sdsprandsrc2): '<S77>/Random Source' */
  /* RandSrc_GZ_R */
  for (chan = 0; chan < nChans; chan++) {
    int32_T icng_tmp;
    real32_T std;
    uint32_T icng;
    uint32_T jsr;
    std = xstd[xstdLen > 1 ? chan : 0];
    icng_tmp = chan << 1;
    icng = state[icng_tmp];
    jsr = state[icng_tmp + 1];
    for (samp = 0; samp < nSamps; samp++) {
      int32_T i;
      int32_T j;
      real32_T r;
      real32_T x;
      real32_T y_0;
      icng = 69069U * icng + 1234567U;
      jsr ^= jsr << 13;
      jsr ^= jsr >> 17;
      jsr ^= jsr << 5;
      i = (int32_T)(icng + jsr);
      j = (i & 63) + 1;
      r = (real32_T)i * 4.65661287E-10F * vt[j];
      x = fabsf(r);
      y_0 = vt[j - 1];
      if (x > y_0) {
        real32_T s;
        x = (x - y_0) / (vt[j] - y_0);
        icng = 69069U * icng + 1234567U;
        jsr ^= jsr << 13;
        jsr ^= jsr >> 17;
        jsr ^= jsr << 5;
        y_0 = (real32_T)(int32_T)(icng + jsr) * 2.32830644E-10F + 0.5F;
        s = x + y_0;
        if (s > 1.30119801F) {
          r = r < 0.0F ? 0.487899214F * x - 0.487899214F : 0.487899214F -
            0.487899214F * x;
        } else if (s > 0.96892792F) {
          x = 0.487899214F - 0.487899214F * x;
          if (y_0 > 12.6770601F - expf(-0.5F * x * x) * 12.3758602F) {
            r = r < 0.0F ? -x : x;
          } else if (expf(-0.5F * vt[j] * vt[j]) + y_0 * 0.0195830297F / vt[j] >
                     expf(-0.5F * r * r)) {
            do {
              icng = 69069U * icng + 1234567U;
              jsr ^= jsr << 13;
              jsr ^= jsr >> 17;
              jsr ^= jsr << 5;
              x = logf((real32_T)(int32_T)(icng + jsr) * 2.32830644E-10F + 0.5F)
                / 2.77699399F;
              icng = 69069U * icng + 1234567U;
              jsr ^= jsr << 13;
              jsr ^= jsr >> 17;
              jsr ^= jsr << 5;
            } while (logf((real32_T)(int32_T)(icng + jsr) * 2.32830644E-10F +
                          0.5F) * -2.0F <= x * x);

            r = r < 0.0F ? x - 2.77699399F : 2.77699399F - x;
          }
        }
      }

      y[chan * nSamps + samp] = mean[meanLen > 1 ? chan : 0] + std * r;
    }

    state[icng_tmp] = icng;
    state[icng_tmp + 1] = jsr;
  }

  /* End of S-Function (sdsprandsrc2): '<S77>/Random Source' */
}

void RandSrcInitState_GZ(const uint32_T seed[], uint32_T state[], int32_T nChans)
{
  int32_T i;

  /* InitializeConditions for S-Function (sdsprandsrc2): '<S77>/Random Source' */
  /* RandSrcInitState_GZ */
  for (i = 0; i < nChans; i++) {
    int32_T tmp;
    tmp = i << 1;
    state[tmp] = 362436069U;
    state[tmp + 1] = seed[i] == 0U ? 521288629U : seed[i];
  }

  /* End of InitializeConditions for S-Function (sdsprandsrc2): '<S77>/Random Source' */
}

void RandSrcInitState_U_32(const uint32_T seed[], real32_T state[], int32_T
  nChans)
{
  int32_T i;
  int32_T k;
  int32_T n;

  /* InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
  /* RandSrcInitState_U_32 */
  for (i = 0; i < nChans; i++) {
    uint32_T j;
    j = seed[i] != 0U ? seed[i] : 2147483648U;
    state[35 * i + 34] = (real32_T)j;
    for (k = 0; k < 32; k++) {
      real32_T d;
      d = 0.0F;
      for (n = 0; n < 24; n++) {
        j ^= j << 13;
        j ^= j >> 17;
        j ^= j << 5;
        d = (real32_T)((int32_T)(j >> 19) & 1) + (d + d);
      }

      state[35 * i + k] = ldexpf(d, -24);
    }

    state[35 * i + 32] = 0.0F;
    state[35 * i + 33] = 0.0F;
  }

  /* End of InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
}

void RandSrc_U_R(real32_T y[], const real32_T minVec[], int32_T minLen, const
                 real32_T maxVec[], int32_T maxLen, real32_T state[], int32_T
                 nChans, int32_T nSamps)
{
  int32_T chan;
  int32_T ii;
  int32_T samps;
  real32_T d;

  /* InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
  /* RandSrc_U_R */
  for (chan = 0; chan < nChans; chan++) {
    int32_T i;
    int32_T i_tmp;
    int32_T j_tmp;
    real32_T min;
    real32_T scale;
    uint32_T j;
    min = minVec[minLen > 1 ? chan : 0];
    scale = maxVec[maxLen > 1 ? chan : 0] - min;
    i_tmp = chan * 35 + 33;
    i = (int32_T)((uint32_T)state[i_tmp] & 31U);
    j_tmp = chan * 35 + 34;
    j = (uint32_T)state[j_tmp];
    for (samps = 0; samps < nSamps; samps++) {
      int32_T d_tmp;

      /* "Subtract with borrow" generator */
      d_tmp = chan * 35 + 32;
      d = (state[((i + 20) & 31) + chan * 35] - state[((i + 5) & 31) + chan * 35])
        - state[d_tmp];
      if (d >= 0.0F) {
        state[d_tmp] = 0.0F;
      } else {
        d++;

        /* set 1 in LSB */
        state[d_tmp] = 5.96046448E-8F;
      }

      state[chan * 35 + i] = d;
      i = (i + 1) & 31;

      /* XOR with shift register sequence */
      memcpy(&ii, &d, sizeof(real32_T));
      j ^= j << 13;
      j ^= j >> 17;
      j ^= j << 5;
      ii ^= j & 8388607U;
      memcpy(&d, &ii, sizeof(real32_T));
      y[chan * nSamps + samps] = scale * d + min;
    }

    state[i_tmp] = (real32_T)i;
    state[j_tmp] = (real32_T)j;
  }

  /* End of InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
}

void RandSrcCreateSeeds_32(uint32_T initSeed, uint32_T seedArray[], int32_T
  numSeeds)
{
  int32_T i;
  real32_T state[35];
  real32_T max;
  real32_T min;
  real32_T tmp;

  /* InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
  /* RandSrcCreateSeeds_32 */
  min = 0.0F;
  max = 1.0F;
  RandSrcInitState_U_32(&initSeed, &state[0], 1);
  for (i = 0; i < numSeeds; i++) {
    RandSrc_U_R(&tmp, &min, 1, &max, 1, state, 1, 1);
    seedArray[i] = (uint32_T)(tmp * 2.14748365E+9F);
  }

  /* End of InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
}

/* Model step function */
void Plant_step(void)
{
  real_T rtb_VectorConcatenate_d[3];
  real_T rtb_Divide2_idx_0;
  real_T rtb_Divide2_idx_2;
  real_T rtb_Product1_c_tmp_idx_2;
  real_T rtb_Product1_g;
  real_T rtb_Product1_h;
  real_T rtb_Product1_l;
  real_T rtb_Product2_g_idx_1;
  real_T rtb_Product2_g_idx_2;
  real_T rtb_StratosphereModel;
  real_T rtb_SumofElements;
  int32_T i;
  int32_T rtb_RateTransition_gSpeed;
  int32_T rtb_RateTransition_height;
  int32_T rtb_RateTransition_lat;
  int32_T rtb_RateTransition_lon;
  int32_T rtb_RateTransition_velD;
  int32_T rtb_RateTransition_velE;
  int32_T rtb_RateTransition_velN;
  int32_T rtb_Saturation1_idx_1;
  real32_T rtb_MatrixConcatenate4[16];
  real32_T rtb_MatrixConcatenate1[9];
  real32_T rtb_VectorConcatenate_c[9];
  real32_T rtb_MatrixConcatenate4_0[4];
  real32_T rtb_Add1_c[3];
  real32_T rtb_Add_ch[3];
  real32_T rtb_RandomSource[3];
  real32_T rtb_RandomSource1[3];
  real32_T rtb_RandomSource_f[3];
  real32_T rtb_Saturation_f[3];
  real32_T rtb_Sum_hq[3];
  real32_T rtb_Switch_i[3];
  real32_T rtb_VectorConcatenate_dy[3];
  real32_T rtb_omega_B_radPs[3];
  real32_T rtb_vel_O_mPs[3];
  real32_T rtb_DiscreteTimeIntegrator_l__0;
  real32_T rtb_DiscreteTimeIntegrator_l__1;
  real32_T rtb_DiscreteTimeIntegrator_l__2;
  real32_T rtb_DiscreteTimeIntegrator_l_id;
  real32_T rtb_Divide_f_idx_0;
  real32_T rtb_Divide_f_idx_1;
  real32_T rtb_Divide_f_idx_2;
  real32_T rtb_Divide_f_idx_3;
  real32_T rtb_Divide_n_idx_1;
  real32_T rtb_Divide_n_idx_2;
  real32_T rtb_Gain1_idx_0;
  real32_T rtb_Gain1_idx_1;
  real32_T rtb_Gain1_idx_2;
  real32_T rtb_Gain1_idx_3;
  real32_T rtb_Gain_d_tmp;
  real32_T rtb_Gain_h;
  real32_T rtb_RateTransition_b_mag_x;
  real32_T rtb_RateTransition_b_mag_y;
  real32_T rtb_RateTransition_b_mag_z;
  real32_T rtb_RateTransition_m_pressure;
  real32_T rtb_RateTransition_m_temperatur;
  real32_T rtb_Sum_d;
  real32_T rtb_Switch_f;
  real32_T rtb_Switch_j_tmp;
  real32_T rtb_Switch_j_tmp_0;
  real32_T rtb_TrigonometricFunction1_id_0;
  real32_T rtb_TrigonometricFunction1_id_1;
  real32_T rtb_TrigonometricFunction1_id_2;
  real32_T rtb_TrigonometricFunction1_id_3;
  real32_T rtb_TrigonometricFunction1_idx_;
  uint32_T rtb_RateTransition_b_timestamp;
  uint32_T rtb_RateTransition_hAcc;
  uint32_T rtb_RateTransition_m_timestamp;
  uint32_T rtb_RateTransition_sAcc;
  uint32_T rtb_RateTransition_timestamp;
  uint32_T rtb_RateTransition_vAcc;
  uint16_T tmp;
  boolean_T rtb_Compare_oo_idx_0;
  boolean_T rtb_Compare_oo_idx_1;
  boolean_T rtb_Compare_oo_idx_2;

  /* Outputs for Atomic SubSystem: '<Root>/Actuators' */
  /* Saturate: '<S8>/Saturation' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  if (Plant_U.Control_Out.actuator_cmd[0] > 2000) {
    tmp = 2000U;
  } else if (Plant_U.Control_Out.actuator_cmd[0] < 1000) {
    tmp = 1000U;
  } else {
    tmp = Plant_U.Control_Out.actuator_cmd[0];
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S8>/Constant'
   *  Sum: '<S8>/Subtract'
   */
  rtb_TrigonometricFunction1_idx_ = ((real32_T)tmp - 1000.0F) * 0.000999987125F;

  /* RelationalOperator: '<S13>/Compare' incorporates:
   *  Constant: '<S13>/Constant'
   */
  rtb_Compare_oo_idx_0 = (rtb_TrigonometricFunction1_idx_ > 0.1F);

  /* Gain: '<S12>/Gain1' */
  rtb_Gain1_idx_0 = 718.078F * rtb_TrigonometricFunction1_idx_;

  /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator_l__2 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[0];

  /* Math: '<S14>/Square' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  Math: '<S16>/Square'
   */
  rtb_Gain1_idx_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[0] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[0];

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S14>/cT'
   *  Product: '<S14>/Multiply'
   */
  rtb_Divide_f_idx_0 = (real32_T)(rtb_Gain1_idx_3 * 1.239E-5);

  /* Math: '<S14>/Square' */
  rtb_TrigonometricFunction1_id_2 = rtb_Gain1_idx_3;

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  if (Plant_U.Control_Out.actuator_cmd[1] > 2000) {
    tmp = 2000U;
  } else if (Plant_U.Control_Out.actuator_cmd[1] < 1000) {
    tmp = 1000U;
  } else {
    tmp = Plant_U.Control_Out.actuator_cmd[1];
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S8>/Constant'
   *  Sum: '<S8>/Subtract'
   */
  rtb_TrigonometricFunction1_idx_ = ((real32_T)tmp - 1000.0F) * 0.000999987125F;

  /* RelationalOperator: '<S13>/Compare' incorporates:
   *  Constant: '<S13>/Constant'
   */
  rtb_Compare_oo_idx_1 = (rtb_TrigonometricFunction1_idx_ > 0.1F);

  /* Gain: '<S12>/Gain1' */
  rtb_Gain1_idx_1 = 718.078F * rtb_TrigonometricFunction1_idx_;

  /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator_l__1 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[1];

  /* Math: '<S14>/Square' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  Math: '<S16>/Square'
   */
  rtb_Gain1_idx_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[1] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[1];

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S14>/cT'
   *  Product: '<S14>/Multiply'
   */
  rtb_Divide_f_idx_1 = (real32_T)(rtb_Gain1_idx_3 * 1.239E-5);

  /* Math: '<S14>/Square' */
  rtb_TrigonometricFunction1_id_1 = rtb_Gain1_idx_3;

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  if (Plant_U.Control_Out.actuator_cmd[2] > 2000) {
    tmp = 2000U;
  } else if (Plant_U.Control_Out.actuator_cmd[2] < 1000) {
    tmp = 1000U;
  } else {
    tmp = Plant_U.Control_Out.actuator_cmd[2];
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S8>/Constant'
   *  Sum: '<S8>/Subtract'
   */
  rtb_TrigonometricFunction1_idx_ = ((real32_T)tmp - 1000.0F) * 0.000999987125F;

  /* RelationalOperator: '<S13>/Compare' incorporates:
   *  Constant: '<S13>/Constant'
   */
  rtb_Compare_oo_idx_2 = (rtb_TrigonometricFunction1_idx_ > 0.1F);

  /* Gain: '<S12>/Gain1' */
  rtb_Gain1_idx_2 = 718.078F * rtb_TrigonometricFunction1_idx_;

  /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator_l__0 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[2];

  /* Math: '<S14>/Square' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  Math: '<S16>/Square'
   */
  rtb_Gain1_idx_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[2] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[2];

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S14>/cT'
   *  Product: '<S14>/Multiply'
   */
  rtb_Divide_f_idx_2 = (real32_T)(rtb_Gain1_idx_3 * 1.239E-5);

  /* Math: '<S14>/Square' */
  rtb_TrigonometricFunction1_id_0 = rtb_Gain1_idx_3;

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Inport: '<Root>/Control_Out'
   */
  if (Plant_U.Control_Out.actuator_cmd[3] > 2000) {
    tmp = 2000U;
  } else if (Plant_U.Control_Out.actuator_cmd[3] < 1000) {
    tmp = 1000U;
  } else {
    tmp = Plant_U.Control_Out.actuator_cmd[3];
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  Constant: '<S8>/Constant'
   *  Sum: '<S8>/Subtract'
   */
  rtb_TrigonometricFunction1_idx_ = ((real32_T)tmp - 1000.0F) * 0.000999987125F;

  /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator_l_id = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[3];

  /* Math: '<S14>/Square' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  Math: '<S16>/Square'
   */
  rtb_Gain1_idx_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_n[3] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[3];

  /* Sum: '<S15>/Add' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   */
  rtb_Gain_h = ((Plant_DW.DiscreteTimeIntegrator_DSTATE_n[2] -
                 Plant_DW.DiscreteTimeIntegrator_DSTATE_n[0]) -
                Plant_DW.DiscreteTimeIntegrator_DSTATE_n[1]) +
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[3];

  /* Product: '<S18>/Multiply' incorporates:
   *  Constant: '<S15>/Constant'
   */
  rtb_Switch_i[0] = 0.0F;

  /* Product: '<S18>/Multiply1' incorporates:
   *  Constant: '<S15>/Constant'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S15>/Multiply'
   */
  rtb_Switch_i[1] = rtb_Gain_h * Plant_Y.Plant_States.rot_x_B * 0.0001287F;

  /* Product: '<S18>/Multiply2' incorporates:
   *  Constant: '<S15>/Constant'
   */
  rtb_Switch_i[2] = 0.0F;

  /* Product: '<S19>/Multiply3' incorporates:
   *  Constant: '<S15>/Constant'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S15>/Multiply'
   */
  rtb_Saturation_f[0] = rtb_Gain_h * Plant_Y.Plant_States.rot_y_B * 0.0001287F;

  /* Product: '<S19>/Multiply4' incorporates:
   *  Constant: '<S15>/Constant'
   */
  rtb_Saturation_f[1] = 0.0F;

  /* Product: '<S19>/Multiply5' incorporates:
   *  Constant: '<S15>/Constant'
   */
  rtb_Saturation_f[2] = 0.0F;

  /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S12>/Constant1'
   *  Constant: '<S13>/Constant'
   *  Gain: '<S11>/Gain'
   *  Gain: '<S12>/Gain1'
   *  Product: '<S12>/Multiply'
   *  RelationalOperator: '<S13>/Compare'
   *  Saturate: '<S12>/Saturation1'
   *  Sum: '<S11>/Subtract'
   *  Sum: '<S12>/Add'
   */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_n[0] += ((rtb_Compare_oo_idx_0 ?
    rtb_Gain1_idx_0 + 88.448F : 0.0F) -
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[0]) * 50.0F * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_n[1] += ((rtb_Compare_oo_idx_1 ?
    rtb_Gain1_idx_1 + 88.448F : 0.0F) -
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[1]) * 50.0F * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_n[2] += ((rtb_Compare_oo_idx_2 ?
    rtb_Gain1_idx_2 + 88.448F : 0.0F) -
    Plant_DW.DiscreteTimeIntegrator_DSTATE_n[2]) * 50.0F * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_n[3] +=
    ((rtb_TrigonometricFunction1_idx_ > 0.1F ? 718.078F *
      rtb_TrigonometricFunction1_idx_ + 88.448F : 0.0F) -
     Plant_DW.DiscreteTimeIntegrator_DSTATE_n[3]) * 50.0F * 0.002F;

  /* End of Outputs for SubSystem: '<Root>/Actuators' */

  /* Outputs for Atomic SubSystem: '<Root>/Environment' */
  /* Trigonometry: '<S35>/Trigonometric Function1' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  Gain: '<S34>/Gain'
   *  Trigonometry: '<S35>/Trigonometric Function3'
   */
  rtb_Gain1_idx_0 = arm_cos_f32(-Plant_Y.Plant_States.psi);
  rtb_VectorConcatenate_c[0] = rtb_Gain1_idx_0;

  /* Trigonometry: '<S35>/Trigonometric Function' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  Gain: '<S34>/Gain'
   *  Trigonometry: '<S35>/Trigonometric Function2'
   */
  rtb_Gain1_idx_1 = arm_sin_f32(-Plant_Y.Plant_States.psi);
  rtb_VectorConcatenate_c[1] = rtb_Gain1_idx_1;

  /* SignalConversion generated from: '<S35>/Vector Concatenate1' incorporates:
   *  Constant: '<S35>/Constant3'
   */
  rtb_VectorConcatenate_c[2] = 0.0F;

  /* Gain: '<S35>/Gain' */
  rtb_VectorConcatenate_c[3] = -rtb_Gain1_idx_1;

  /* Trigonometry: '<S35>/Trigonometric Function3' */
  rtb_VectorConcatenate_c[4] = rtb_Gain1_idx_0;

  /* SignalConversion generated from: '<S35>/Vector Concatenate2' incorporates:
   *  Constant: '<S35>/Constant4'
   */
  rtb_VectorConcatenate_c[5] = 0.0F;

  /* SignalConversion generated from: '<S35>/Vector Concatenate' incorporates:
   *  Concatenate: '<S35>/Vector Concatenate3'
   */
  rtb_VectorConcatenate_c[6] = Plant_ConstB.VectorConcatenate3_e[0];
  rtb_VectorConcatenate_c[7] = Plant_ConstB.VectorConcatenate3_e[1];
  rtb_VectorConcatenate_c[8] = Plant_ConstB.VectorConcatenate3_e[2];
  for (i = 0; i < 3; i++) {
    /* Gain: '<S33>/Gain' incorporates:
     *  Concatenate: '<S35>/Vector Concatenate'
     *  Delay generated from: '<Root>/Delay'
     *  Product: '<S33>/Multiply'
     */
    rtb_Add1_c[i] = ((rtb_VectorConcatenate_c[i + 3] *
                      Plant_Y.Plant_States.vel_y_O + rtb_VectorConcatenate_c[i] *
                      Plant_Y.Plant_States.vel_x_O) + rtb_VectorConcatenate_c[i
                     + 6] * Plant_Y.Plant_States.vel_z_O) * -0.15F;
  }

  /* Product: '<S33>/Multiply1' incorporates:
   *  Concatenate: '<S35>/Vector Concatenate'
   *  Math: '<S33>/Square'
   */
  for (i = 0; i < 3; i++) {
    rtb_Add_ch[i] = (rtb_VectorConcatenate_c[3 * i + 1] * rtb_Add1_c[1] +
                     rtb_VectorConcatenate_c[3 * i] * rtb_Add1_c[0]) +
      rtb_VectorConcatenate_c[3 * i + 2] * rtb_Add1_c[2];
  }

  /* End of Product: '<S33>/Multiply1' */

  /* Product: '<S33>/Multiply2' incorporates:
   *  Delay generated from: '<Root>/Delay'
   */
  for (i = 0; i < 3; i++) {
    rtb_RandomSource_f[i] = (Plant_Y.Extended_States.M_BO[i + 3] * rtb_Add_ch[1]
      + Plant_Y.Extended_States.M_BO[i] * rtb_Add_ch[0]) +
      Plant_Y.Extended_States.M_BO[i + 6] * rtb_Add_ch[2];
  }

  /* End of Product: '<S33>/Multiply2' */

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S14>/cT'
   *  Gain: '<S9>/Gain'
   *  Product: '<S14>/Multiply'
   *  Sum: '<S9>/Sum of Elements'
   */
  rtb_Gain1_idx_0 = rtb_RandomSource_f[0];
  rtb_Gain1_idx_1 = rtb_RandomSource_f[1];
  rtb_Gain1_idx_2 = rtb_RandomSource_f[2];
  rtb_RandomSource_f[0] = rtb_Gain1_idx_0;
  rtb_RandomSource_f[1] = rtb_Gain1_idx_1;

  /* Outputs for Atomic SubSystem: '<Root>/Actuators' */
  rtb_RandomSource_f[2] = -(((rtb_Divide_f_idx_0 + rtb_Divide_f_idx_1) +
    rtb_Divide_f_idx_2) + (real32_T)(rtb_Gain1_idx_3 * 1.239E-5)) +
    rtb_Gain1_idx_2;

  /* End of Outputs for SubSystem: '<Root>/Actuators' */

  /* RelationalOperator: '<S36>/Compare' incorporates:
   *  Constant: '<S36>/Constant'
   *  Delay generated from: '<Root>/Delay'
   */
  rtb_Compare_oo_idx_0 = (Plant_Y.Plant_States.h_R < 0.0F);

  /* Switch: '<S32>/Switch2' incorporates:
   *  Constant: '<S32>/Constant'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S37>/Multiply'
   *  Reshape: '<S37>/Reshape'
   *  Sum: '<S42>/Sum'
   */
  if (rtb_Compare_oo_idx_0) {
    /* Switch: '<S37>/Switch1' incorporates:
     *  Constant: '<S37>/mg'
     *  Constant: '<S39>/Constant'
     *  Delay generated from: '<Root>/Delay'
     *  Gain: '<S37>/Gain'
     *  RelationalOperator: '<S39>/Compare'
     *  Sum: '<S37>/Add'
     */
    if (Plant_Y.Plant_States.h_R <= -0.05F) {
      /* Switch: '<S37>/Switch3' incorporates:
       *  Constant: '<S37>/mg'
       *  Constant: '<S40>/Constant'
       *  Gain: '<S37>/Gain1'
       *  Gain: '<S37>/Gain2'
       *  Gain: '<S37>/Gain4'
       *  RelationalOperator: '<S40>/Compare'
       *  Sum: '<S37>/Add1'
       *  Sum: '<S37>/Add2'
       */
      if (Plant_Y.Plant_States.h_R <= -0.1F) {
        rtb_Gain1_idx_0 = (Plant_Y.Plant_States.h_R - 8.68811607F) - 50.0F *
          Plant_Y.Plant_States.vel_z_O;
      } else {
        rtb_Gain1_idx_0 = (0.5F * Plant_Y.Plant_States.h_R - 8.68811607F) -
          20.0F * Plant_Y.Plant_States.vel_z_O;
      }

      /* End of Switch: '<S37>/Switch3' */
    } else {
      rtb_Gain1_idx_0 = -8.68811607F - 10.0F * Plant_Y.Plant_States.vel_z_O;
    }

    /* End of Switch: '<S37>/Switch1' */

    /* Product: '<S37>/Multiply' incorporates:
     *  Delay generated from: '<Root>/Delay'
     *  Gain: '<S37>/Gain5'
     *  Gain: '<S37>/Gain6'
     */
    rtb_Gain1_idx_1 = -50.0F * Plant_Y.Plant_States.vel_x_O;
    rtb_Gain1_idx_2 = -50.0F * Plant_Y.Plant_States.vel_y_O;
    for (i = 0; i < 3; i++) {
      rtb_Sum_hq[i] = (Plant_Y.Extended_States.M_BO[i + 3] * rtb_Gain1_idx_2 +
                       Plant_Y.Extended_States.M_BO[i] * rtb_Gain1_idx_1) +
        Plant_Y.Extended_States.M_BO[i + 6] * rtb_Gain1_idx_0;
    }
  } else {
    rtb_Sum_hq[0] = 0.0F;
    rtb_Sum_hq[1] = 0.0F;
    rtb_Sum_hq[2] = 0.0F;
  }

  /* End of Switch: '<S32>/Switch2' */
  for (i = 0; i < 3; i++) {
    /* Sum: '<S3>/Add' incorporates:
     *  Constant: '<S31>/mg'
     *  Delay generated from: '<Root>/Delay'
     *  Product: '<S31>/Multiply3'
     *  Sum: '<S42>/Sum'
     */
    rtb_Add_ch[i] = (Plant_Y.Extended_States.M_BO[i + 6] * 8.69166F +
                     rtb_Sum_hq[i]) + rtb_RandomSource_f[i];
  }

  /* Switch: '<S32>/Switch1' incorporates:
   *  Constant: '<S32>/Constant1'
   *  Delay generated from: '<Root>/Delay'
   *  Gain: '<S38>/Gain1'
   *  Gain: '<S38>/Gain2'
   *  Gain: '<S38>/Gain3'
   *  Sum: '<S38>/Subtract'
   *  Sum: '<S42>/Sum'
   */
  if (rtb_Compare_oo_idx_0) {
    rtb_Sum_hq[0] = ((0.0F - 30.0F * Plant_Y.Plant_States.phi) - 5.0F *
                     Plant_Y.Plant_States.rot_x_B) * 0.289603859F;
    rtb_Sum_hq[1] = ((0.0F - 30.0F * Plant_Y.Plant_States.theta) - 5.0F *
                     Plant_Y.Plant_States.rot_y_B) * 0.289603859F;
    rtb_Sum_hq[2] = (0.0F - 5.0F * Plant_Y.Plant_States.rot_z_B) * 0.289603859F;
  } else {
    rtb_Sum_hq[0] = 0.0F;
    rtb_Sum_hq[1] = 0.0F;
    rtb_Sum_hq[2] = 0.0F;
  }

  /* End of Switch: '<S32>/Switch1' */

  /* Outputs for Atomic SubSystem: '<Root>/Actuators' */
  for (i = 0; i < 3; i++) {
    /* Sum: '<S3>/Add1' incorporates:
     *  Constant: '<S16>/X_Frame_CM'
     *  Math: '<S16>/Square'
     *  Product: '<S16>/Multiply'
     *  Sum: '<S10>/Sum'
     *  Sum: '<S17>/Sum'
     *  Sum: '<S42>/Sum'
     */
    rtb_Add1_c[i] = ((((Plant_ConstP.X_Frame_CM_Value[i + 3] *
                        rtb_TrigonometricFunction1_id_1 +
                        Plant_ConstP.X_Frame_CM_Value[i] *
                        rtb_TrigonometricFunction1_id_2) +
                       Plant_ConstP.X_Frame_CM_Value[i + 6] *
                       rtb_TrigonometricFunction1_id_0) +
                      Plant_ConstP.X_Frame_CM_Value[i + 9] * rtb_Gain1_idx_3) +
                     (rtb_Switch_i[i] - rtb_Saturation_f[i])) + rtb_Sum_hq[i];
  }

  /* End of Outputs for SubSystem: '<Root>/Actuators' */
  /* End of Outputs for SubSystem: '<Root>/Environment' */

  /* Outputs for Atomic SubSystem: '<Root>/Kinematic_Equation' */
  /* DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
  if (Plant_DW.DiscreteTimeIntegrator_PrevRese != 0) {
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0] = Plant_ConstB.quat0[0];
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1] = Plant_ConstB.quat0[1];
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2] = Plant_ConstB.quat0[2];
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3] = Plant_ConstB.quat0[3];
  }

  rtb_Gain1_idx_0 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0];
  rtb_Gain1_idx_1 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1];
  rtb_Gain1_idx_2 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2];
  rtb_Gain1_idx_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate' incorporates:
   *  Constant: '<S50>/Constant'
   */
  rtb_MatrixConcatenate4[0] = 0.0F;

  /* DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
  if (Plant_DW.DiscreteTimeIntegrator_PrevRe_d != 0) {
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0] = 0.0F;
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1] = 0.0F;
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2] = 0.0F;
  }

  rtb_omega_B_radPs[0] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0];
  rtb_omega_B_radPs[1] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1];
  rtb_omega_B_radPs[2] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[1] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[2] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[3] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];

  /* Gain: '<S50>/Gain1' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[4] = -Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate1' incorporates:
   *  Constant: '<S50>/Constant1'
   */
  rtb_MatrixConcatenate4[5] = 0.0F;

  /* Gain: '<S50>/Gain2' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[6] = -Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate1' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[7] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1];

  /* Gain: '<S50>/Gain3' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[8] = -Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate2' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[9] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate2' incorporates:
   *  Constant: '<S50>/Constant2'
   */
  rtb_MatrixConcatenate4[10] = 0.0F;

  /* Gain: '<S50>/Gain4' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[11] = -Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0];

  /* Gain: '<S50>/Gain6' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[12] = -Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];

  /* Gain: '<S50>/Gain7' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[13] = -Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate3' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_MatrixConcatenate4[14] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0];

  /* SignalConversion generated from: '<S50>/Matrix Concatenate3' incorporates:
   *  Constant: '<S50>/Constant3'
   */
  rtb_MatrixConcatenate4[15] = 0.0F;

  /* Sqrt: '<S49>/Sqrt' incorporates:
   *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
   *  Math: '<S49>/Square'
   *  Sqrt: '<S60>/Sqrt'
   *  Sqrt: '<S65>/Sqrt'
   *  Sum: '<S49>/Sum of Elements'
   */
  rtb_Divide_f_idx_1 = sqrtf(((Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0] +
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1]) +
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2]) +
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3]);

  /* Product: '<S48>/Divide' incorporates:
   *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
   *  Product: '<S56>/Divide'
   *  Product: '<S61>/Divide'
   *  Sqrt: '<S49>/Sqrt'
   */
  rtb_TrigonometricFunction1_id_2 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0] /
    rtb_Divide_f_idx_1;
  rtb_TrigonometricFunction1_id_1 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1] /
    rtb_Divide_f_idx_1;
  rtb_TrigonometricFunction1_id_0 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2] /
    rtb_Divide_f_idx_1;
  rtb_TrigonometricFunction1_id_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3] /
    rtb_Divide_f_idx_1;

  /* Product: '<S41>/Multiply' incorporates:
   *  Constant: '<S41>/Inertia_Matrix'
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   */
  for (i = 0; i < 3; i++) {
    rtb_RandomSource_f[i] = (Plant_ConstP.Inertia_Matrix_Value[i + 3] *
      Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1] +
      Plant_ConstP.Inertia_Matrix_Value[i] *
      Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0]) +
      Plant_ConstP.Inertia_Matrix_Value[i + 6] *
      Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];
  }

  /* End of Product: '<S41>/Multiply' */

  /* Product: '<S46>/Multiply1' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_VectorConcatenate_dy[1] = rtb_RandomSource_f[0] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2];

  /* Product: '<S46>/Multiply2' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_VectorConcatenate_dy[2] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0] *
    rtb_RandomSource_f[1];

  /* Product: '<S47>/Multiply5' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_Switch_i[2] = rtb_RandomSource_f[0] *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1];

  /* DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */
  if (Plant_DW.DiscreteTimeIntegrator_PrevRe_k != 0) {
    Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0] = 0.0F;
    Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1] = 0.0F;
    Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2] = 0.0F;
  }

  /* Product: '<S59>/Product3' incorporates:
   *  Product: '<S57>/Product6'
   */
  rtb_Divide_f_idx_1 = rtb_TrigonometricFunction1_id_0 *
    rtb_TrigonometricFunction1_id_0;

  /* Product: '<S59>/Product6' incorporates:
   *  Product: '<S57>/Product9'
   */
  rtb_Divide_f_idx_0 = rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_3;

  /* Product: '<S59>/Product7' incorporates:
   *  Product: '<S57>/Product2'
   */
  rtb_Divide_f_idx_2 = rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_0;

  /* Sum: '<S59>/Sum2' incorporates:
   *  Constant: '<S59>/Constant'
   *  Product: '<S59>/Product2'
   *  Sum: '<S58>/Sum1'
   */
  rtb_Sum_d = 0.5F - rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_1;

  /* Product: '<S59>/Product1' incorporates:
   *  Product: '<S58>/Product2'
   */
  rtb_Switch_j_tmp = rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_1;

  /* Product: '<S59>/Product9' incorporates:
   *  Product: '<S58>/Product3'
   */
  rtb_Switch_j_tmp_0 = rtb_TrigonometricFunction1_id_0 *
    rtb_TrigonometricFunction1_id_3;

  /* Sum: '<S59>/Sum' incorporates:
   *  DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
   *  Gain: '<S59>/Gain1'
   *  Gain: '<S59>/Gain2'
   *  Gain: '<S59>/Gain3'
   *  Product: '<S59>/Product1'
   *  Product: '<S59>/Product3'
   *  Product: '<S59>/Product4'
   *  Product: '<S59>/Product5'
   *  Product: '<S59>/Product6'
   *  Product: '<S59>/Product7'
   *  Product: '<S59>/Product8'
   *  Product: '<S59>/Product9'
   *  Sum: '<S59>/Sum1'
   *  Sum: '<S59>/Sum2'
   *  Sum: '<S59>/Sum3'
   */
  rtb_Switch_f = ((rtb_Divide_f_idx_0 + rtb_Divide_f_idx_2) * 2.0F *
                  Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0] +
                  (rtb_Switch_j_tmp_0 - rtb_Switch_j_tmp) * 2.0F *
                  Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1]) + (rtb_Sum_d -
    rtb_Divide_f_idx_1) * 2.0F * Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2];

  /* Product: '<S57>/Product7' incorporates:
   *  Product: '<S58>/Product9'
   */
  rtb_Gain_d_tmp = rtb_TrigonometricFunction1_id_3 *
    rtb_TrigonometricFunction1_id_3;

  /* Product: '<S57>/Product' incorporates:
   *  Product: '<S58>/Product6'
   */
  rtb_Divide_n_idx_1 = rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_0;

  /* Product: '<S57>/Product1' incorporates:
   *  Product: '<S58>/Product7'
   */
  rtb_TrigonometricFunction1_idx_ = rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_3;

  /* Sum: '<S57>/Sum' incorporates:
   *  Constant: '<S57>/Constant'
   *  DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain2'
   *  Gain: '<S57>/Gain3'
   *  Product: '<S57>/Product'
   *  Product: '<S57>/Product1'
   *  Product: '<S57>/Product4'
   *  Product: '<S57>/Product5'
   *  Product: '<S57>/Product7'
   *  Product: '<S57>/Product8'
   *  Sum: '<S57>/Sum1'
   *  Sum: '<S57>/Sum2'
   *  Sum: '<S57>/Sum3'
   */
  rtb_Gain_h = (((0.5F - rtb_Divide_f_idx_1) - rtb_Gain_d_tmp) * 2.0F *
                Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0] +
                (rtb_Divide_n_idx_1 + rtb_TrigonometricFunction1_idx_) * 2.0F *
                Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1]) +
    (rtb_Divide_f_idx_0 - rtb_Divide_f_idx_2) * 2.0F *
    Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2];

  /* Product: '<S54>/Multiply1' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_Saturation_f[1] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2] * rtb_Gain_h;

  /* Product: '<S55>/Multiply5' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   */
  rtb_Sum_hq[2] = Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1] * rtb_Gain_h;

  /* Sum: '<S58>/Sum' incorporates:
   *  DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
   *  Gain: '<S58>/Gain1'
   *  Gain: '<S58>/Gain2'
   *  Gain: '<S58>/Gain3'
   *  Product: '<S58>/Product4'
   *  Product: '<S58>/Product5'
   *  Product: '<S58>/Product8'
   *  Sum: '<S58>/Sum1'
   *  Sum: '<S58>/Sum2'
   *  Sum: '<S58>/Sum3'
   */
  rtb_Gain_h = ((rtb_Sum_d - rtb_Gain_d_tmp) * 2.0F *
                Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1] +
                (rtb_Divide_n_idx_1 - rtb_TrigonometricFunction1_idx_) * 2.0F *
                Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0]) + (rtb_Switch_j_tmp
    + rtb_Switch_j_tmp_0) * 2.0F * Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2];

  /* DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */
  rtb_vel_O_mPs[0] = Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0];

  /* Sum: '<S41>/Sum' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   *  Product: '<S46>/Multiply'
   *  Product: '<S47>/Multiply3'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S3>/Add1'
   *  Sum: '<S43>/Sum'
   */
  rtb_RandomSource_f[0] = rtb_Add1_c[0] -
    (Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1] * rtb_RandomSource_f[2] -
     rtb_RandomSource_f[1] * Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2]);

  /* Sum: '<S42>/Sum' incorporates:
   *  Constant: '<S42>/mass'
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   *  Product: '<S42>/Divide'
   *  Product: '<S54>/Multiply'
   *  Product: '<S55>/Multiply3'
   *  Sum: '<S3>/Add'
   *  Sum: '<S51>/Sum'
   */
  rtb_TrigonometricFunction1_idx_ = rtb_Add_ch[0] / 0.886F -
    (Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1] * rtb_Switch_f -
     Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2] * rtb_Gain_h);

  /* DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */
  rtb_vel_O_mPs[1] = Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1];

  /* Sum: '<S41>/Sum' incorporates:
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   *  Product: '<S47>/Multiply4'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S3>/Add1'
   *  Sum: '<S43>/Sum'
   */
  rtb_RandomSource_f[1] = rtb_Add1_c[1] - (rtb_VectorConcatenate_dy[1] -
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0] * rtb_RandomSource_f[2]);

  /* Sum: '<S42>/Sum' incorporates:
   *  Constant: '<S42>/mass'
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   *  Product: '<S42>/Divide'
   *  Product: '<S55>/Multiply4'
   *  Sum: '<S3>/Add'
   *  Sum: '<S51>/Sum'
   */
  rtb_Switch_f = rtb_Add_ch[1] / 0.886F - (rtb_Saturation_f[1] -
    Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0] * rtb_Switch_f);

  /* DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */
  rtb_vel_O_mPs[2] = Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2];

  /* Sum: '<S41>/Sum' incorporates:
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S3>/Add1'
   *  Sum: '<S43>/Sum'
   */
  rtb_RandomSource_f[2] = rtb_Add1_c[2] - (rtb_VectorConcatenate_dy[2] -
    rtb_Switch_i[2]);

  /* Sum: '<S42>/Sum' incorporates:
   *  Constant: '<S42>/mass'
   *  DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
   *  Product: '<S42>/Divide'
   *  Product: '<S54>/Multiply2'
   *  Sum: '<S3>/Add'
   *  Sum: '<S51>/Sum'
   */
  rtb_Divide_n_idx_1 = rtb_Add_ch[2] / 0.886F -
    (Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0] * rtb_Gain_h - rtb_Sum_hq[2]);

  /* Product: '<S62>/Product7' incorporates:
   *  Product: '<S63>/Product7'
   */
  rtb_Switch_j_tmp_0 = rtb_TrigonometricFunction1_id_3 *
    rtb_TrigonometricFunction1_id_3;

  /* Product: '<S62>/Product' incorporates:
   *  Product: '<S63>/Product'
   */
  rtb_Gain_d_tmp = rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_0;

  /* Product: '<S62>/Product1' incorporates:
   *  Product: '<S63>/Product1'
   */
  rtb_Divide_f_idx_1 = rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_3;

  /* Product: '<S62>/Product2' incorporates:
   *  Product: '<S64>/Product9'
   */
  rtb_Divide_n_idx_2 = rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_3;

  /* Product: '<S62>/Product3' incorporates:
   *  Product: '<S64>/Product1'
   */
  rtb_Gain_h = rtb_TrigonometricFunction1_id_2 * rtb_TrigonometricFunction1_id_0;

  /* Product: '<S62>/Product6' incorporates:
   *  Product: '<S64>/Product7'
   */
  rtb_Switch_j_tmp = rtb_TrigonometricFunction1_id_0 *
    rtb_TrigonometricFunction1_id_0;

  /* Sum: '<S62>/Sum' incorporates:
   *  Constant: '<S62>/Constant'
   *  Gain: '<S62>/Gain'
   *  Gain: '<S62>/Gain1'
   *  Gain: '<S62>/Gain2'
   *  Product: '<S62>/Product'
   *  Product: '<S62>/Product1'
   *  Product: '<S62>/Product2'
   *  Product: '<S62>/Product3'
   *  Product: '<S62>/Product4'
   *  Product: '<S62>/Product5'
   *  Product: '<S62>/Product6'
   *  Product: '<S62>/Product7'
   *  Product: '<S62>/Product8'
   *  Sum: '<S62>/Sum1'
   *  Sum: '<S62>/Sum2'
   *  Sum: '<S62>/Sum3'
   */
  rtb_Sum_d = (((0.5F - rtb_Switch_j_tmp) - rtb_Switch_j_tmp_0) * 2.0F *
               rtb_TrigonometricFunction1_idx_ + (rtb_Gain_d_tmp -
    rtb_Divide_f_idx_1) * 2.0F * rtb_Switch_f) + (rtb_Divide_n_idx_2 +
    rtb_Gain_h) * 2.0F * rtb_Divide_n_idx_1;

  /* Product: '<S63>/Product2' incorporates:
   *  Product: '<S64>/Product2'
   */
  rtb_Divide_f_idx_0 = rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_1;

  /* Product: '<S63>/Product3' incorporates:
   *  Product: '<S64>/Product3'
   */
  rtb_Divide_f_idx_2 = rtb_TrigonometricFunction1_id_0 *
    rtb_TrigonometricFunction1_id_3;

  /* Sum: '<S63>/Sum3' incorporates:
   *  Constant: '<S63>/Constant'
   *  Product: '<S63>/Product6'
   *  Sum: '<S64>/Sum3'
   */
  rtb_Divide_f_idx_3 = 0.5F - rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_1;

  /* Sum: '<S63>/Sum' incorporates:
   *  Gain: '<S63>/Gain'
   *  Gain: '<S63>/Gain1'
   *  Gain: '<S63>/Gain2'
   *  Product: '<S63>/Product2'
   *  Product: '<S63>/Product3'
   *  Product: '<S63>/Product4'
   *  Product: '<S63>/Product5'
   *  Product: '<S63>/Product8'
   *  Sum: '<S63>/Sum1'
   *  Sum: '<S63>/Sum2'
   *  Sum: '<S63>/Sum3'
   */
  rtb_Divide_f_idx_1 = ((rtb_Divide_f_idx_3 - rtb_Switch_j_tmp_0) * 2.0F *
                        rtb_Switch_f + (rtb_Gain_d_tmp + rtb_Divide_f_idx_1) *
                        2.0F * rtb_TrigonometricFunction1_idx_) +
    (rtb_Divide_f_idx_2 - rtb_Divide_f_idx_0) * 2.0F * rtb_Divide_n_idx_1;

  /* Sum: '<S64>/Sum' incorporates:
   *  Gain: '<S64>/Gain1'
   *  Gain: '<S64>/Gain2'
   *  Gain: '<S64>/Gain3'
   *  Product: '<S64>/Product4'
   *  Product: '<S64>/Product5'
   *  Product: '<S64>/Product8'
   *  Sum: '<S64>/Sum1'
   *  Sum: '<S64>/Sum2'
   *  Sum: '<S64>/Sum3'
   */
  rtb_Divide_f_idx_0 = ((rtb_Divide_n_idx_2 - rtb_Gain_h) * 2.0F *
                        rtb_TrigonometricFunction1_idx_ + (rtb_Divide_f_idx_0 +
    rtb_Divide_f_idx_2) * 2.0F * rtb_Switch_f) + (rtb_Divide_f_idx_3 -
    rtb_Switch_j_tmp) * 2.0F * rtb_Divide_n_idx_1;

  /* Math: '<S44>/Square1' incorporates:
   *  Product: '<S48>/Divide'
   */
  rtb_Switch_f = rtb_TrigonometricFunction1_id_0 *
    rtb_TrigonometricFunction1_id_0;

  /* Product: '<S44>/Multiply6' incorporates:
   *  Constant: '<S44>/Constant'
   *  Product: '<S44>/Multiply4'
   *  Product: '<S44>/Multiply5'
   *  Product: '<S48>/Divide'
   *  Sum: '<S44>/Subtract'
   */
  rtb_Divide_f_idx_2 = (rtb_TrigonometricFunction1_id_2 *
                        rtb_TrigonometricFunction1_id_0 -
                        rtb_TrigonometricFunction1_id_1 *
                        rtb_TrigonometricFunction1_id_3) * 2.0F;

  /* DiscreteIntegrator: '<S42>/Discrete-Time Integrator1' */
  if (Plant_DW.DiscreteTimeIntegrator1_PrevRes != 0) {
    Plant_DW.DiscreteTimeIntegrator1_DSTATE[0] = 0.0F;
    Plant_DW.DiscreteTimeIntegrator1_DSTATE[1] = 0.0F;
    Plant_DW.DiscreteTimeIntegrator1_DSTATE[2] = 0.0F;
  }

  rtb_Switch_i[0] = Plant_DW.DiscreteTimeIntegrator1_DSTATE[0];
  rtb_Switch_i[1] = Plant_DW.DiscreteTimeIntegrator1_DSTATE[1];
  rtb_Switch_i[2] = Plant_DW.DiscreteTimeIntegrator1_DSTATE[2];

  /* End of DiscreteIntegrator: '<S42>/Discrete-Time Integrator1' */

  /* Product: '<S45>/Multiply' incorporates:
   *  Concatenate: '<S50>/Matrix Concatenate4'
   *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
   */
  for (i = 0; i < 4; i++) {
    rtb_MatrixConcatenate4_0[i] = ((rtb_MatrixConcatenate4[i + 4] *
      Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1] + rtb_MatrixConcatenate4[i] *
      Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0]) + rtb_MatrixConcatenate4[i +
      8] * Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2]) +
      rtb_MatrixConcatenate4[i + 12] * Plant_DW.DiscreteTimeIntegrator_DSTATE_d
      [3];
  }

  /* End of Product: '<S45>/Multiply' */

  /* Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S45>/Gain'
   */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0] += 0.5F *
    rtb_MatrixConcatenate4_0[0] * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1] += 0.5F *
    rtb_MatrixConcatenate4_0[1] * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2] += 0.5F *
    rtb_MatrixConcatenate4_0[2] * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3] += 0.5F *
    rtb_MatrixConcatenate4_0[3] * 0.002F;
  Plant_DW.DiscreteTimeIntegrator_PrevRese = 0;

  /* Product: '<S41>/Divide' incorporates:
   *  Constant: '<S41>/Inertia_Matrix'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   */
  rt_mldivide_U1f3x3_U2f3x1_Yf3x1(Plant_ConstP.Inertia_Matrix_Value,
    rtb_RandomSource_f, rtb_Add1_c);

  /* Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
  Plant_DW.DiscreteTimeIntegrator_PrevRe_d = 0;

  /* Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */
  rtb_TrigonometricFunction1_idx_ = Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0];
  rtb_Divide_f_idx_3 = Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1];
  rtb_Divide_n_idx_1 = Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2];
  Plant_DW.DiscreteTimeIntegrator_DSTATE_f[0] = 0.002F * rtb_Sum_d +
    rtb_TrigonometricFunction1_idx_;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_f[1] = 0.002F * rtb_Divide_f_idx_1 +
    rtb_Divide_f_idx_3;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_f[2] = 0.002F * rtb_Divide_f_idx_0 +
    rtb_Divide_n_idx_1;
  Plant_DW.DiscreteTimeIntegrator_PrevRe_k = 0;

  /* Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_e[0] += 0.002F * rtb_Add1_c[0];

  /* Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator1' */
  Plant_DW.DiscreteTimeIntegrator1_DSTATE[0] += 0.002F * rtb_vel_O_mPs[0];

  /* Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_e[1] += 0.002F * rtb_Add1_c[1];

  /* Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator1' */
  Plant_DW.DiscreteTimeIntegrator1_DSTATE[1] += 0.002F * rtb_vel_O_mPs[1];

  /* Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_e[2] += 0.002F * rtb_Add1_c[2];

  /* Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator1' */
  Plant_DW.DiscreteTimeIntegrator1_DSTATE[2] += 0.002F * rtb_vel_O_mPs[2];
  Plant_DW.DiscreteTimeIntegrator1_PrevRes = 0;

  /* End of Outputs for SubSystem: '<Root>/Kinematic_Equation' */

  /* Outputs for Atomic SubSystem: '<Root>/Bus_Constructor' */
  /* Sqrt: '<S27>/Sqrt' incorporates:
   *  Math: '<S27>/Square'
   *  Sum: '<S27>/Sum of Elements'
   */
  rtb_Gain_h = sqrtf(((rtb_Gain1_idx_0 * rtb_Gain1_idx_0 + rtb_Gain1_idx_1 *
                       rtb_Gain1_idx_1) + rtb_Gain1_idx_2 * rtb_Gain1_idx_2) +
                     rtb_Gain1_idx_3 * rtb_Gain1_idx_3);

  /* BusAssignment: '<S2>/Bus Assignment2' incorporates:
   *  Constant: '<S2>/Constant5'
   *  Delay generated from: '<Root>/Delay'
   */
  memset(&Plant_Y.Extended_States, 0, sizeof(Extended_States_Bus));
  Plant_Y.Extended_States.temprature = 25.0F;

  /* Product: '<S23>/Divide' */
  rtb_TrigonometricFunction1_idx_ = rtb_Gain1_idx_0 / rtb_Gain_h;

  /* BusAssignment: '<S2>/Bus Assignment2' incorporates:
   *  Constant: '<S2>/Constant6'
   *  Delay generated from: '<Root>/Delay'
   */
  Plant_Y.Extended_States.prop_vel[0] = rtb_DiscreteTimeIntegrator_l__2;
  Plant_Y.Extended_States.prop_vel[4] = 0.0F;

  /* Product: '<S23>/Divide' */
  rtb_Divide_n_idx_1 = rtb_Gain1_idx_1 / rtb_Gain_h;

  /* BusAssignment: '<S2>/Bus Assignment2' incorporates:
   *  Constant: '<S2>/Constant6'
   *  Delay generated from: '<Root>/Delay'
   */
  Plant_Y.Extended_States.prop_vel[1] = rtb_DiscreteTimeIntegrator_l__1;
  Plant_Y.Extended_States.prop_vel[5] = 0.0F;

  /* Product: '<S23>/Divide' */
  rtb_Divide_n_idx_2 = rtb_Gain1_idx_2 / rtb_Gain_h;

  /* BusAssignment: '<S2>/Bus Assignment2' incorporates:
   *  Constant: '<S2>/Constant6'
   *  Delay generated from: '<Root>/Delay'
   */
  Plant_Y.Extended_States.prop_vel[2] = rtb_DiscreteTimeIntegrator_l__0;
  Plant_Y.Extended_States.prop_vel[6] = 0.0F;

  /* Product: '<S23>/Divide' */
  rtb_Gain_h = rtb_Gain1_idx_3 / rtb_Gain_h;

  /* BusAssignment: '<S2>/Bus Assignment2' incorporates:
   *  Constant: '<S2>/Constant6'
   *  Delay generated from: '<Root>/Delay'
   */
  Plant_Y.Extended_States.prop_vel[3] = rtb_DiscreteTimeIntegrator_l_id;
  Plant_Y.Extended_States.prop_vel[7] = 0.0F;

  /* Math: '<S24>/Square' incorporates:
   *  Math: '<S25>/Square'
   *  Math: '<S26>/Square'
   */
  rtb_DiscreteTimeIntegrator_l__2 = rtb_TrigonometricFunction1_idx_ *
    rtb_TrigonometricFunction1_idx_;

  /* Math: '<S24>/Square2' incorporates:
   *  Math: '<S25>/Square2'
   *  Math: '<S26>/Square2'
   */
  rtb_DiscreteTimeIntegrator_l__1 = rtb_Divide_n_idx_2 * rtb_Divide_n_idx_2;

  /* Math: '<S24>/Square1' incorporates:
   *  Math: '<S25>/Square1'
   *  Math: '<S26>/Square1'
   */
  rtb_DiscreteTimeIntegrator_l__0 = rtb_Divide_n_idx_1 * rtb_Divide_n_idx_1;

  /* Math: '<S24>/Square3' incorporates:
   *  Math: '<S25>/Square3'
   *  Math: '<S26>/Square3'
   */
  rtb_DiscreteTimeIntegrator_l_id = rtb_Gain_h * rtb_Gain_h;

  /* Sum: '<S24>/Subtract' incorporates:
   *  Math: '<S24>/Square'
   *  Math: '<S24>/Square1'
   *  Math: '<S24>/Square2'
   *  Math: '<S24>/Square3'
   *  Sum: '<S24>/Add'
   *  Sum: '<S24>/Add1'
   */
  rtb_MatrixConcatenate1[0] = (rtb_DiscreteTimeIntegrator_l__2 +
    rtb_DiscreteTimeIntegrator_l__0) - (rtb_DiscreteTimeIntegrator_l__1 +
    rtb_DiscreteTimeIntegrator_l_id);

  /* Product: '<S24>/Multiply' incorporates:
   *  Product: '<S25>/Multiply'
   */
  rtb_Divide_f_idx_3 = rtb_Divide_n_idx_1 * rtb_Divide_n_idx_2;

  /* Product: '<S24>/Multiply1' incorporates:
   *  Product: '<S25>/Multiply1'
   */
  rtb_Switch_j_tmp = rtb_TrigonometricFunction1_idx_ * rtb_Gain_h;

  /* Gain: '<S24>/Gain' incorporates:
   *  Product: '<S24>/Multiply'
   *  Product: '<S24>/Multiply1'
   *  Sum: '<S24>/Subtract1'
   */
  rtb_MatrixConcatenate1[1] = (rtb_Divide_f_idx_3 - rtb_Switch_j_tmp) * 2.0F;

  /* Product: '<S24>/Multiply2' incorporates:
   *  Product: '<S26>/Multiply'
   */
  rtb_Switch_j_tmp_0 = rtb_Divide_n_idx_1 * rtb_Gain_h;

  /* Product: '<S24>/Multiply3' incorporates:
   *  Product: '<S26>/Multiply1'
   */
  rtb_Gain_d_tmp = rtb_TrigonometricFunction1_idx_ * rtb_Divide_n_idx_2;

  /* Gain: '<S24>/Gain1' incorporates:
   *  Product: '<S24>/Multiply2'
   *  Product: '<S24>/Multiply3'
   *  Sum: '<S24>/Add2'
   */
  rtb_MatrixConcatenate1[2] = (rtb_Switch_j_tmp_0 + rtb_Gain_d_tmp) * 2.0F;

  /* Gain: '<S25>/Gain' incorporates:
   *  Sum: '<S25>/Add3'
   */
  rtb_MatrixConcatenate1[3] = (rtb_Divide_f_idx_3 + rtb_Switch_j_tmp) * 2.0F;

  /* Sum: '<S25>/Subtract' incorporates:
   *  Sum: '<S25>/Add'
   *  Sum: '<S25>/Add1'
   */
  rtb_MatrixConcatenate1[4] = (rtb_DiscreteTimeIntegrator_l__2 +
    rtb_DiscreteTimeIntegrator_l__1) - (rtb_DiscreteTimeIntegrator_l__0 +
    rtb_DiscreteTimeIntegrator_l_id);

  /* Product: '<S25>/Multiply2' incorporates:
   *  Product: '<S26>/Multiply2'
   */
  rtb_Divide_f_idx_3 = rtb_Divide_n_idx_2 * rtb_Gain_h;

  /* Product: '<S25>/Multiply3' incorporates:
   *  Product: '<S26>/Multiply3'
   */
  rtb_Switch_j_tmp = rtb_TrigonometricFunction1_idx_ * rtb_Divide_n_idx_1;

  /* Gain: '<S25>/Gain1' incorporates:
   *  Product: '<S25>/Multiply2'
   *  Product: '<S25>/Multiply3'
   *  Sum: '<S25>/Subtract1'
   */
  rtb_MatrixConcatenate1[5] = (rtb_Divide_f_idx_3 - rtb_Switch_j_tmp) * 2.0F;

  /* Gain: '<S26>/Gain' incorporates:
   *  Sum: '<S26>/Subtract2'
   */
  rtb_MatrixConcatenate1[6] = (rtb_Switch_j_tmp_0 - rtb_Gain_d_tmp) * 2.0F;

  /* Gain: '<S26>/Gain1' incorporates:
   *  Sum: '<S26>/Add2'
   */
  rtb_MatrixConcatenate1[7] = (rtb_Divide_f_idx_3 + rtb_Switch_j_tmp) * 2.0F;

  /* Sum: '<S26>/Subtract' incorporates:
   *  Sum: '<S26>/Add'
   *  Sum: '<S26>/Add1'
   */
  rtb_MatrixConcatenate1[8] = (rtb_DiscreteTimeIntegrator_l__2 +
    rtb_DiscreteTimeIntegrator_l_id) - (rtb_DiscreteTimeIntegrator_l__0 +
    rtb_DiscreteTimeIntegrator_l__1);

  /* BusAssignment: '<S2>/Bus Assignment2' incorporates:
   *  Concatenate: '<S21>/Matrix Concatenate1'
   *  Delay generated from: '<Root>/Delay'
   *  Math: '<S2>/Square'
   */
  for (i = 0; i < 9; i++) {
    Plant_Y.Extended_States.M_BO[i] = rtb_MatrixConcatenate1[i];
  }

  for (i = 0; i < 3; i++) {
    Plant_Y.Extended_States.M_OB[3 * i] = rtb_MatrixConcatenate1[i];
    Plant_Y.Extended_States.M_OB[3 * i + 1] = rtb_MatrixConcatenate1[i + 3];
    Plant_Y.Extended_States.M_OB[3 * i + 2] = rtb_MatrixConcatenate1[i + 6];
  }

  Plant_Y.Extended_States.quat[0] = rtb_Gain1_idx_0;
  Plant_Y.Extended_States.quat[1] = rtb_Gain1_idx_1;
  Plant_Y.Extended_States.quat[2] = rtb_Gain1_idx_2;
  Plant_Y.Extended_States.quat[3] = rtb_Gain1_idx_3;

  /* BusAssignment: '<S2>/Bus Assignment1' incorporates:
   *  Delay generated from: '<Root>/Delay'
   */
  memset(&Plant_Y.Plant_States, 0, sizeof(Plant_States_Bus));

  /* Outputs for Atomic SubSystem: '<Root>/Kinematic_Equation' */
  /* BusAssignment: '<S2>/Bus Assignment' incorporates:
   *  BusAssignment: '<S2>/Bus Assignment1'
   *  Constant: '<S44>/Constant'
   *  Constant: '<S44>/Constant2'
   *  Delay generated from: '<Root>/Delay'
   *  Math: '<S44>/Square'
   *  Product: '<S44>/Multiply'
   *  Product: '<S44>/Multiply1'
   *  Product: '<S44>/Multiply2'
   *  Product: '<S44>/Multiply3'
   *  Product: '<S48>/Divide'
   *  Sum: '<S44>/Add'
   *  Sum: '<S44>/Add1'
   *  Sum: '<S44>/Subtract2'
   *  Trigonometry: '<S44>/Atan2'
   */
  Plant_Y.Plant_States.phi = atan2f((rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_1 + rtb_TrigonometricFunction1_id_0 *
    rtb_TrigonometricFunction1_id_3) * 2.0F, 1.0F -
    (rtb_TrigonometricFunction1_id_1 * rtb_TrigonometricFunction1_id_1 +
     rtb_Switch_f) * 2.0F);

  /* End of Outputs for SubSystem: '<Root>/Bus_Constructor' */

  /* Saturate: '<S44>/Saturation' */
  if (rtb_Divide_f_idx_2 > 1.0F) {
    rtb_Divide_f_idx_2 = 1.0F;
  } else if (rtb_Divide_f_idx_2 < -1.0F) {
    rtb_Divide_f_idx_2 = -1.0F;
  }

  /* End of Saturate: '<S44>/Saturation' */

  /* Outputs for Atomic SubSystem: '<Root>/Bus_Constructor' */
  /* BusAssignment: '<S2>/Bus Assignment' incorporates:
   *  BusAssignment: '<S2>/Bus Assignment1'
   *  Constant: '<S44>/Constant'
   *  Constant: '<S44>/Constant1'
   *  Delay generated from: '<Root>/Delay'
   *  Math: '<S44>/Square2'
   *  Product: '<S44>/Multiply10'
   *  Product: '<S44>/Multiply7'
   *  Product: '<S44>/Multiply8'
   *  Product: '<S44>/Multiply9'
   *  Product: '<S48>/Divide'
   *  Sum: '<S44>/Add2'
   *  Sum: '<S44>/Add3'
   *  Sum: '<S44>/Subtract1'
   *  Trigonometry: '<S44>/Asin'
   *  Trigonometry: '<S44>/Atan1'
   */
  Plant_Y.Plant_States.theta = asinf(rtb_Divide_f_idx_2);
  Plant_Y.Plant_States.psi = atan2f((rtb_TrigonometricFunction1_id_2 *
    rtb_TrigonometricFunction1_id_3 + rtb_TrigonometricFunction1_id_1 *
    rtb_TrigonometricFunction1_id_0) * 2.0F, 1.0F -
    (rtb_TrigonometricFunction1_id_3 * rtb_TrigonometricFunction1_id_3 +
     rtb_Switch_f) * 2.0F);

  /* End of Outputs for SubSystem: '<Root>/Kinematic_Equation' */
  Plant_Y.Plant_States.rot_x_B = rtb_omega_B_radPs[0];
  Plant_Y.Plant_States.rot_y_B = rtb_omega_B_radPs[1];
  Plant_Y.Plant_States.rot_z_B = rtb_omega_B_radPs[2];
  Plant_Y.Plant_States.acc_x_O = rtb_Sum_d;
  Plant_Y.Plant_States.acc_y_O = rtb_Divide_f_idx_1;
  Plant_Y.Plant_States.acc_z_O = rtb_Divide_f_idx_0;
  Plant_Y.Plant_States.vel_x_O = rtb_vel_O_mPs[0];
  Plant_Y.Plant_States.vel_y_O = rtb_vel_O_mPs[1];
  Plant_Y.Plant_States.vel_z_O = rtb_vel_O_mPs[2];

  /* Trigonometry: '<S28>/Trigonometric Function1' incorporates:
   *  Delay: '<S22>/Delay1'
   *  Trigonometry: '<S28>/Trigonometric Function2'
   */
  rtb_Divide2_idx_0 = cos(Plant_DW.Delay1_DSTATE[0]);

  /* Trigonometry: '<S28>/Trigonometric Function' incorporates:
   *  Delay: '<S22>/Delay1'
   */
  rtb_StratosphereModel = sin(Plant_DW.Delay1_DSTATE[0]);

  /* Sum: '<S28>/Subtract' incorporates:
   *  Constant: '<S28>/c'
   *  Math: '<S28>/u^2'
   *  Product: '<S28>/Product'
   */
  rtb_StratosphereModel = 1.0 - rtb_StratosphereModel * rtb_StratosphereModel *
    Plant_ConstB.Product1;

  /* Math: '<S28>/sqrt'
   *
   * About '<S28>/sqrt':
   *  Operator: sqrt
   */
  if (rtb_StratosphereModel < 0.0) {
    rtb_StratosphereModel = -sqrt(fabs(rtb_StratosphereModel));
  } else {
    rtb_StratosphereModel = sqrt(rtb_StratosphereModel);
  }

  /* End of Math: '<S28>/sqrt' */

  /* Product: '<S28>/Divide' incorporates:
   *  Constant: '<S28>/earth_radius'
   */
  rtb_StratosphereModel = 6.378137E+6 / rtb_StratosphereModel;

  /* Sum: '<S28>/Add' incorporates:
   *  Constant: '<S28>/constant2'
   *  Delay: '<S22>/Delay1'
   *  Math: '<S28>/u^1'
   *  Product: '<S28>/Product2'
   *  Product: '<S28>/Product3'
   *  Sum: '<S28>/Subtract2'
   *  Trigonometry: '<S28>/Trigonometric Function1'
   */
  rtb_SumofElements = (1.0 - rtb_Divide2_idx_0 * rtb_Divide2_idx_0 *
                       Plant_ConstB.Product1) * rtb_StratosphereModel +
    Plant_DW.Delay1_DSTATE[2];

  /* Product: '<S28>/Product4' incorporates:
   *  Delay: '<S22>/Delay1'
   *  Sum: '<S28>/Add1'
   */
  rtb_StratosphereModel = (Plant_DW.Delay1_DSTATE[2] + rtb_StratosphereModel) *
    rtb_Divide2_idx_0;

  /* BusAssignment: '<S2>/Bus Assignment1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  Delay generated from: '<Root>/Delay'
   *  Delay: '<S20>/Delay'
   *  Gain: '<S2>/Gain'
   */
  Plant_Y.Plant_States.x_R = rtb_Switch_i[0];
  Plant_Y.Plant_States.y_R = rtb_Switch_i[1];
  Plant_Y.Plant_States.h_R = -rtb_Switch_i[2];
  Plant_Y.Plant_States.lat_0 = 0.65673;
  Plant_Y.Plant_States.lon_0 = -2.1361;
  Plant_Y.Plant_States.alt_0 = 4.5;
  Plant_Y.Plant_States.timestamp = Plant_DW.Delay_DSTATE_c;

  /* Sum: '<S20>/Sum' incorporates:
   *  Constant: '<S20>/dt'
   *  Delay: '<S20>/Delay'
   */
  Plant_DW.Delay_DSTATE_c += PLANT_EXPORT.period;

  /* Signum: '<S29>/Sign' */
  if (rtb_SumofElements < 0.0) {
    i = -1;
  } else {
    i = (rtb_SumofElements > 0.0);
  }

  /* Abs: '<S29>/Abs' */
  rtb_Divide2_idx_0 = fabs(rtb_SumofElements);

  /* Saturate: '<S29>/Saturation' */
  if (rtb_Divide2_idx_0 > 1.0E+8) {
    rtb_Divide2_idx_0 = 1.0E+8;
  } else if (rtb_Divide2_idx_0 < 1.0E-6) {
    rtb_Divide2_idx_0 = 1.0E-6;
  }

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant'
   */
  if (i == 0) {
    i = 1;
  }

  /* Sum: '<S22>/Add' incorporates:
   *  Abs: '<S29>/Abs'
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   *  Delay: '<S22>/Delay'
   *  Delay: '<S22>/Delay1'
   *  Product: '<S22>/Divide'
   *  Product: '<S29>/Product'
   *  Sum: '<S22>/Subtract'
   */
  Plant_DW.Delay1_DSTATE[0] += 1.0 / (rtb_Divide2_idx_0 * (real_T)i) *
    (rtb_Switch_i[0] - Plant_DW.Delay_DSTATE_a[0]);

  /* Update for Delay: '<S22>/Delay' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   */
  Plant_DW.Delay_DSTATE_a[0] = rtb_Switch_i[0];

  /* Signum: '<S29>/Sign' */
  if (rtb_StratosphereModel < 0.0) {
    i = -1;
  } else {
    i = (rtb_StratosphereModel > 0.0);
  }

  /* Abs: '<S29>/Abs' */
  rtb_Divide2_idx_0 = fabs(rtb_StratosphereModel);

  /* Saturate: '<S29>/Saturation' */
  if (rtb_Divide2_idx_0 > 1.0E+8) {
    rtb_Divide2_idx_0 = 1.0E+8;
  } else if (rtb_Divide2_idx_0 < 1.0E-6) {
    rtb_Divide2_idx_0 = 1.0E-6;
  }

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant'
   */
  if (i == 0) {
    i = 1;
  }

  /* Sum: '<S22>/Add' incorporates:
   *  Abs: '<S29>/Abs'
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   *  Delay: '<S22>/Delay'
   *  Delay: '<S22>/Delay1'
   *  Product: '<S22>/Divide'
   *  Product: '<S29>/Product'
   *  Sum: '<S22>/Subtract'
   */
  Plant_DW.Delay1_DSTATE[1] += 1.0 / (rtb_Divide2_idx_0 * (real_T)i) *
    (rtb_Switch_i[1] - Plant_DW.Delay_DSTATE_a[1]);

  /* Update for Delay: '<S22>/Delay' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   */
  Plant_DW.Delay_DSTATE_a[1] = rtb_Switch_i[1];

  /* Sum: '<S22>/Add' incorporates:
   *  Abs: '<S29>/Abs'
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   *  Delay: '<S22>/Delay'
   *  Delay: '<S22>/Delay1'
   *  Product: '<S22>/Divide'
   *  Sum: '<S22>/Subtract'
   */
  Plant_DW.Delay1_DSTATE[2] += -(rtb_Switch_i[2] - Plant_DW.Delay_DSTATE_a[2]);

  /* Update for Delay: '<S22>/Delay' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   */
  Plant_DW.Delay_DSTATE_a[2] = rtb_Switch_i[2];

  /* BusAssignment: '<S2>/Bus Assignment1' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  Delay: '<S22>/Delay1'
   */
  Plant_Y.Plant_States.lat = Plant_DW.Delay1_DSTATE[0];
  Plant_Y.Plant_States.lon = Plant_DW.Delay1_DSTATE[1];
  Plant_Y.Plant_States.alt = Plant_DW.Delay1_DSTATE[2];

  /* End of Outputs for SubSystem: '<Root>/Bus_Constructor' */

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_Model' */
  /* Outputs for Atomic SubSystem: '<S5>/Sensor_Barometer' */
  /* Saturate: '<S75>/Limit  altitude  to troposhere' incorporates:
   *  DataTypeConversion: '<S73>/Data Type Conversion'
   *  Delay generated from: '<Root>/Delay'
   */
  if ((real32_T)Plant_Y.Plant_States.alt > 11000.0F) {
    rtb_TrigonometricFunction1_id_1 = 11000.0F;
  } else if ((real32_T)Plant_Y.Plant_States.alt < 0.0F) {
    rtb_TrigonometricFunction1_id_1 = 0.0F;
  } else {
    rtb_TrigonometricFunction1_id_1 = (real32_T)Plant_Y.Plant_States.alt;
  }

  /* End of Saturate: '<S75>/Limit  altitude  to troposhere' */

  /* Sum: '<S75>/Sum1' incorporates:
   *  Constant: '<S75>/Sea Level  Temperature'
   *  Gain: '<S75>/Lapse Rate'
   */
  rtb_SumofElements = 288.15 - (real32_T)(0.0065 *
    rtb_TrigonometricFunction1_id_1);

  /* S-Function (sdsprandsrc2): '<S77>/Random Source' */
  RandSrc_GZ_R(&rtb_TrigonometricFunction1_id_1, &Plant_ConstP.pooled14, 1,
               &Plant_ConstP.pooled24, 1, Plant_DW.RandomSource_STATE_DWORK_b, 1,
               1);

  /* RateTransition: '<S72>/Rate Transition' incorporates:
   *  Constant: '<S72>/Constant2'
   *  DataTypeConversion: '<S72>/Data Type Conversion1'
   *  Gain: '<S75>/1//T0'
   *  Gain: '<S75>/P0'
   *  Gain: '<S75>/g//R'
   *  Math: '<S75>/(T//T0)^(g//LR) '
   *  Math: '<S75>/Stratosphere Model'
   *  Memory: '<S66>/Memory1'
   *  Product: '<S75>/Product1'
   *  Product: '<S75>/Product2'
   *  Sum: '<S72>/Sum1'
   *  Sum: '<S74>/Add'
   *
   * About '<S75>/Stratosphere Model':
   *  Operator: exp
   */
  if (Plant_M->Timing.TaskCounters.TID[1] == 0) {
    rtb_RateTransition_m_timestamp = Plant_DW.Memory1_PreviousInput;

    /* Saturate: '<S75>/Limit  altitude  to Stratosphere' incorporates:
     *  Constant: '<S75>/Altitude of Troposphere'
     *  DataTypeConversion: '<S73>/Data Type Conversion'
     *  Delay generated from: '<Root>/Delay'
     *  Memory: '<S66>/Memory1'
     *  RateTransition: '<S72>/Rate Transition'
     *  Sum: '<S75>/Sum'
     */
    if (11000.0 - (real32_T)Plant_Y.Plant_States.alt > 0.0) {
      rtb_StratosphereModel = 0.0;
    } else if (11000.0 - (real32_T)Plant_Y.Plant_States.alt < -9000.0) {
      rtb_StratosphereModel = -9000.0;
    } else {
      rtb_StratosphereModel = 11000.0 - (real32_T)Plant_Y.Plant_States.alt;
    }

    /* End of Saturate: '<S75>/Limit  altitude  to Stratosphere' */
    rtb_RateTransition_m_pressure = (real32_T)(pow(0.00347041471455839 *
      rtb_SumofElements, 5.2558756014667134) * 101325.0 * exp(1.0 /
      rtb_SumofElements * (0.034163191409533639 * rtb_StratosphereModel))) +
      rtb_TrigonometricFunction1_id_1;
    rtb_RateTransition_m_temperatur = (real32_T)(rtb_SumofElements - 273.15);
  }

  /* End of RateTransition: '<S72>/Rate Transition' */
  /* End of Outputs for SubSystem: '<S5>/Sensor_Barometer' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_GPS' */
  /* Trigonometry: '<S90>/Sin' incorporates:
   *  Delay: '<S83>/Delay'
   */
  rtb_SumofElements = sin(Plant_DW.Delay_DSTATE[0]);

  /* Product: '<S90>/Multiply1' incorporates:
   *  Math: '<S90>/Square1'
   *  Product: '<S90>/Multiply'
   */
  rtb_StratosphereModel = rtb_SumofElements * rtb_SumofElements *
    Plant_ConstB.ff;

  /* Product: '<S90>/Divide' incorporates:
   *  Constant: '<S90>/Constant'
   *  Constant: '<S90>/R'
   *  Sqrt: '<S90>/Sqrt'
   *  Sum: '<S90>/Sum1'
   */
  rtb_SumofElements = 6.378137E+6 / sqrt(1.0 - rtb_StratosphereModel);

  /* S-Function (sdsprandsrc2): '<S86>/Random Source' */
  RandSrc_GZ_R(rtb_RandomSource, &Plant_ConstP.pooled14, 1,
               Plant_ConstP.RandomSource_VarianceRTP, 3,
               Plant_DW.RandomSource_STATE_DWORK_l, 3, 1);

  /* Sum: '<S84>/Sum2' incorporates:
   *  Constant: '<S90>/Constant1'
   *  Delay: '<S83>/Delay'
   *  Product: '<S87>/Divide2'
   *  Product: '<S90>/Multiply1'
   *  Product: '<S90>/Multiply2'
   *  Product: '<S90>/Product3'
   *  S-Function (sdsprandsrc2): '<S86>/Random Source'
   *  Sum: '<S90>/Sum2'
   *  Trigonometry: '<S90>/Cos'
   */
  rtb_Divide2_idx_0 = rtb_RandomSource[0] / (1.0 / (1.0 - rtb_StratosphereModel)
    * Plant_ConstB.Sum4 * rtb_SumofElements) + Plant_DW.Delay_DSTATE[0];
  rtb_SumofElements = rtb_RandomSource[1] / (rtb_SumofElements * cos
    (Plant_DW.Delay_DSTATE[0])) + Plant_DW.Delay_DSTATE[1];
  rtb_Divide2_idx_2 = Plant_DW.Delay_DSTATE[2] + -(real_T)rtb_RandomSource[2];

  /* S-Function (sdsprandsrc2): '<S86>/Random Source1' */
  RandSrc_GZ_R(rtb_RandomSource1, &Plant_ConstP.pooled14, 1,
               Plant_ConstP.RandomSource1_VarianceRTP, 3,
               Plant_DW.RandomSource1_STATE_DWORK, 3, 1);

  /* Delay: '<S83>/Delay1' incorporates:
   *  Switch: '<S96>/Switch'
   */
  rtb_omega_B_radPs[0] = Plant_DW.Delay1_DSTATE_a[0];

  /* Sum: '<S84>/Sum1' incorporates:
   *  Delay: '<S83>/Delay1'
   *  S-Function (sdsprandsrc2): '<S86>/Random Source1'
   */
  rtb_VectorConcatenate_dy[0] = rtb_RandomSource1[0] + Plant_DW.Delay1_DSTATE_a
    [0];

  /* Delay: '<S83>/Delay1' incorporates:
   *  Switch: '<S96>/Switch'
   */
  rtb_omega_B_radPs[1] = Plant_DW.Delay1_DSTATE_a[1];

  /* Sum: '<S84>/Sum1' incorporates:
   *  Delay: '<S83>/Delay1'
   *  S-Function (sdsprandsrc2): '<S86>/Random Source1'
   */
  rtb_VectorConcatenate_dy[1] = rtb_RandomSource1[1] + Plant_DW.Delay1_DSTATE_a
    [1];

  /* Delay: '<S83>/Delay1' incorporates:
   *  Switch: '<S96>/Switch'
   */
  rtb_omega_B_radPs[2] = Plant_DW.Delay1_DSTATE_a[2];

  /* Sum: '<S84>/Sum1' incorporates:
   *  Delay: '<S83>/Delay1'
   *  S-Function (sdsprandsrc2): '<S86>/Random Source1'
   */
  rtb_VectorConcatenate_dy[2] = rtb_RandomSource1[2] + Plant_DW.Delay1_DSTATE_a
    [2];

  /* DiscreteFir: '<S89>/Discrete FIR Filter' incorporates:
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S84>/Sum1'
   */
  rtb_RandomSource_f[0] = rtb_VectorConcatenate_dy[0] * 0.5F +
    Plant_DW.DiscreteFIRFilter_states_f[0] * 0.5F;
  rtb_RandomSource_f[1] = rtb_VectorConcatenate_dy[1] * 0.5F +
    Plant_DW.DiscreteFIRFilter_states_f[1] * 0.5F;
  rtb_RandomSource_f[2] = rtb_VectorConcatenate_dy[2] * 0.5F +
    Plant_DW.DiscreteFIRFilter_states_f[2] * 0.5F;

  /* Gain: '<S78>/Gain6' incorporates:
   *  Math: '<S85>/Math Function'
   *  Product: '<S85>/Matrix Multiply'
   *  Sqrt: '<S85>/Sqrt'
   *  Switch: '<S85>/Switch'
   */
  rtb_StratosphereModel = fmod(floor(sqrtf(rtb_RandomSource[0] *
    rtb_RandomSource[0] + rtb_RandomSource[1] * rtb_RandomSource[1]) * 1000.0),
    4.294967296E+9);

  /* Gain: '<S78>/Gain4' incorporates:
   *  DiscreteFir: '<S88>/Discrete FIR Filter'
   *  Sum: '<S84>/Sum2'
   */
  rtb_Product1_g = fmod(floor((rtb_Divide2_idx_2 * 0.5 +
    Plant_DW.DiscreteFIRFilter_states[2] * 0.5) * 1000.0), 4.294967296E+9);
  i = rtb_Product1_g < 0.0 ? -(int32_T)(uint32_T)-rtb_Product1_g : (int32_T)
    (uint32_T)rtb_Product1_g;

  /* Gain: '<S78>/Gain5' incorporates:
   *  Math: '<S85>/Math Function2'
   *  Product: '<S85>/Matrix Multiply2'
   *  Sqrt: '<S85>/Sqrt2'
   *  Switch: '<S85>/Switch1'
   */
  rtb_Product1_g = fmod(floor(sqrtf(rtb_RandomSource[2] * rtb_RandomSource[2]) *
    1000.0), 4.294967296E+9);

  /* RateTransition: '<S78>/Rate Transition' incorporates:
   *  BusAssignment: '<S78>/Bus Assignment'
   *  Gain: '<S78>/Gain'
   *  Gain: '<S78>/Gain1'
   *  Gain: '<S78>/Gain10'
   *  Gain: '<S78>/Gain11'
   *  Gain: '<S78>/Gain5'
   *  Gain: '<S78>/Gain6'
   *  Gain: '<S78>/Gain7'
   *  Gain: '<S78>/Gain8'
   *  Gain: '<S78>/Gain9'
   *  Math: '<S80>/Math Function'
   *  Math: '<S80>/Math Function1'
   *  Memory: '<S66>/Memory1'
   *  Saturate: '<S80>/Saturation'
   *  Sqrt: '<S80>/Sqrt'
   *  Sum: '<S80>/Add'
   */
  if (Plant_M->Timing.TaskCounters.TID[2] == 0) {
    rtb_RateTransition_timestamp = Plant_DW.Memory1_PreviousInput;

    /* Gain: '<S78>/Gain' incorporates:
     *  DiscreteFir: '<S88>/Discrete FIR Filter'
     *  Gain: '<S78>/Gain2'
     *  Memory: '<S66>/Memory1'
     *  RateTransition: '<S78>/Rate Transition'
     *  Sum: '<S84>/Sum2'
     */
    rtb_Product1_c_tmp_idx_2 = fmod(floor((rtb_Divide2_idx_0 * 0.5 +
      Plant_DW.DiscreteFIRFilter_states[0] * 0.5) * 57.295779513082323 * 1.0E+7),
      4.294967296E+9);
    rtb_RateTransition_lon = rtb_Product1_c_tmp_idx_2 < 0.0 ? -(int32_T)
      (uint32_T)-rtb_Product1_c_tmp_idx_2 : (int32_T)(uint32_T)
      rtb_Product1_c_tmp_idx_2;

    /* Gain: '<S78>/Gain1' incorporates:
     *  DiscreteFir: '<S88>/Discrete FIR Filter'
     *  Gain: '<S78>/Gain'
     *  Gain: '<S78>/Gain3'
     *  RateTransition: '<S78>/Rate Transition'
     *  Sum: '<S84>/Sum2'
     */
    rtb_Product1_c_tmp_idx_2 = fmod(floor((rtb_SumofElements * 0.5 +
      Plant_DW.DiscreteFIRFilter_states[1] * 0.5) * 57.295779513082323 * 1.0E+7),
      4.294967296E+9);
    rtb_RateTransition_lat = rtb_Product1_c_tmp_idx_2 < 0.0 ? -(int32_T)
      (uint32_T)-rtb_Product1_c_tmp_idx_2 : (int32_T)(uint32_T)
      rtb_Product1_c_tmp_idx_2;
    rtb_RateTransition_height = i;
    rtb_RateTransition_hAcc = rtb_StratosphereModel < 0.0 ? (uint32_T)-(int32_T)
      (uint32_T)-rtb_StratosphereModel : (uint32_T)rtb_StratosphereModel;
    rtb_RateTransition_vAcc = rtb_Product1_g < 0.0 ? (uint32_T)-(int32_T)
      (uint32_T)-rtb_Product1_g : (uint32_T)rtb_Product1_g;

    /* Gain: '<S78>/Gain7' incorporates:
     *  BusAssignment: '<S78>/Bus Assignment'
     *  Gain: '<S78>/Gain1'
     *  Gain: '<S78>/Gain5'
     *  Gain: '<S78>/Gain6'
     *  RateTransition: '<S78>/Rate Transition'
     */
    rtb_TrigonometricFunction1_idx_ = fmodf(floorf(1000.0F * rtb_RandomSource_f
      [0]), 4.2949673E+9F);
    rtb_RateTransition_velN = rtb_TrigonometricFunction1_idx_ < 0.0F ? -(int32_T)
      (uint32_T)-rtb_TrigonometricFunction1_idx_ : (int32_T)(uint32_T)
      rtb_TrigonometricFunction1_idx_;

    /* Gain: '<S78>/Gain8' incorporates:
     *  Gain: '<S78>/Gain7'
     *  RateTransition: '<S78>/Rate Transition'
     */
    rtb_TrigonometricFunction1_idx_ = fmodf(floorf(1000.0F * rtb_RandomSource_f
      [1]), 4.2949673E+9F);
    rtb_RateTransition_velE = rtb_TrigonometricFunction1_idx_ < 0.0F ? -(int32_T)
      (uint32_T)-rtb_TrigonometricFunction1_idx_ : (int32_T)(uint32_T)
      rtb_TrigonometricFunction1_idx_;

    /* Gain: '<S78>/Gain9' incorporates:
     *  Gain: '<S78>/Gain8'
     *  RateTransition: '<S78>/Rate Transition'
     */
    rtb_TrigonometricFunction1_idx_ = fmodf(floorf(1000.0F * rtb_RandomSource_f
      [2]), 4.2949673E+9F);
    rtb_RateTransition_velD = rtb_TrigonometricFunction1_idx_ < 0.0F ? -(int32_T)
      (uint32_T)-rtb_TrigonometricFunction1_idx_ : (int32_T)(uint32_T)
      rtb_TrigonometricFunction1_idx_;
    rtb_RateTransition_gSpeed = (int32_T)(uint32_T)fmodf(floorf(sqrtf(fmaxf
      (rtb_RandomSource_f[0] * rtb_RandomSource_f[0] + rtb_RandomSource_f[1] *
       rtb_RandomSource_f[1], 0.0F)) * 1000.0F), 4.2949673E+9F);

    /* Gain: '<S78>/Gain10' incorporates:
     *  Gain: '<S78>/Gain11'
     *  Gain: '<S78>/Gain9'
     *  Math: '<S80>/Math Function'
     *  Math: '<S80>/Math Function1'
     *  Math: '<S85>/Math Function1'
     *  Product: '<S85>/Matrix Multiply1'
     *  RateTransition: '<S78>/Rate Transition'
     *  S-Function (sdsprandsrc2): '<S86>/Random Source1'
     *  Saturate: '<S80>/Saturation'
     *  Sqrt: '<S80>/Sqrt'
     *  Sqrt: '<S85>/Sqrt1'
     *  Sum: '<S80>/Add'
     *  Switch: '<S85>/Switch2'
     */
    rtb_StratosphereModel = fmod(floor(sqrtf((rtb_RandomSource1[0] *
      rtb_RandomSource1[0] + rtb_RandomSource1[1] * rtb_RandomSource1[1]) +
      rtb_RandomSource1[2] * rtb_RandomSource1[2]) * 1000.0), 4.294967296E+9);
    rtb_RateTransition_sAcc = rtb_StratosphereModel < 0.0 ? (uint32_T)-(int32_T)
      (uint32_T)-rtb_StratosphereModel : (uint32_T)rtb_StratosphereModel;
  }

  /* End of RateTransition: '<S78>/Rate Transition' */

  /* Update for Delay: '<S83>/Delay' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S83>/Vector Concatenate'
   */
  for (i = 0; i < 74; i++) {
    rtb_Saturation1_idx_1 = (i + 1) * 3;
    Plant_DW.Delay_DSTATE[i * 3] = Plant_DW.Delay_DSTATE[rtb_Saturation1_idx_1];
    Plant_DW.Delay_DSTATE[i * 3 + 1] =
      Plant_DW.Delay_DSTATE[rtb_Saturation1_idx_1 + 1];
    Plant_DW.Delay_DSTATE[i * 3 + 2] =
      Plant_DW.Delay_DSTATE[rtb_Saturation1_idx_1 + 2];
  }

  /* Update states */
  Plant_DW.Delay_DSTATE[222] = Plant_Y.Plant_States.lon;

  /* Update for DiscreteFir: '<S88>/Discrete FIR Filter' incorporates:
   *  Sum: '<S84>/Sum2'
   */
  Plant_DW.DiscreteFIRFilter_states[0] = rtb_Divide2_idx_0;

  /* Update for Delay: '<S83>/Delay' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S83>/Vector Concatenate'
   */
  Plant_DW.Delay_DSTATE[223] = Plant_Y.Plant_States.lat;

  /* Update for DiscreteFir: '<S88>/Discrete FIR Filter' incorporates:
   *  Sum: '<S84>/Sum2'
   */
  Plant_DW.DiscreteFIRFilter_states[1] = rtb_SumofElements;

  /* Update for Delay: '<S83>/Delay' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S83>/Vector Concatenate'
   */
  Plant_DW.Delay_DSTATE[224] = Plant_Y.Plant_States.alt;

  /* Update for DiscreteFir: '<S88>/Discrete FIR Filter' incorporates:
   *  Sum: '<S84>/Sum2'
   */
  Plant_DW.DiscreteFIRFilter_states[2] = rtb_Divide2_idx_2;

  /* Update for Delay: '<S83>/Delay1' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S83>/Vector Concatenate1'
   */
  for (i = 0; i < 49; i++) {
    rtb_Saturation1_idx_1 = (i + 1) * 3;
    Plant_DW.Delay1_DSTATE_a[i * 3] =
      Plant_DW.Delay1_DSTATE_a[rtb_Saturation1_idx_1];
    Plant_DW.Delay1_DSTATE_a[i * 3 + 1] =
      Plant_DW.Delay1_DSTATE_a[rtb_Saturation1_idx_1 + 1];
    Plant_DW.Delay1_DSTATE_a[i * 3 + 2] =
      Plant_DW.Delay1_DSTATE_a[rtb_Saturation1_idx_1 + 2];
  }

  /* Update states */
  Plant_DW.Delay1_DSTATE_a[147] = Plant_Y.Plant_States.vel_x_O;

  /* Update for DiscreteFir: '<S89>/Discrete FIR Filter' incorporates:
   *  Sum: '<S84>/Sum1'
   */
  Plant_DW.DiscreteFIRFilter_states_f[0] = rtb_VectorConcatenate_dy[0];

  /* Update for Delay: '<S83>/Delay1' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S83>/Vector Concatenate1'
   */
  Plant_DW.Delay1_DSTATE_a[148] = Plant_Y.Plant_States.vel_y_O;

  /* Update for DiscreteFir: '<S89>/Discrete FIR Filter' incorporates:
   *  Sum: '<S84>/Sum1'
   */
  Plant_DW.DiscreteFIRFilter_states_f[1] = rtb_VectorConcatenate_dy[1];

  /* Update for Delay: '<S83>/Delay1' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S83>/Vector Concatenate1'
   */
  Plant_DW.Delay1_DSTATE_a[149] = Plant_Y.Plant_States.vel_z_O;

  /* Update for DiscreteFir: '<S89>/Discrete FIR Filter' incorporates:
   *  Sum: '<S84>/Sum1'
   */
  Plant_DW.DiscreteFIRFilter_states_f[2] = rtb_VectorConcatenate_dy[2];

  /* End of Outputs for SubSystem: '<S5>/Sensor_GPS' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  /* Outputs for Atomic SubSystem: '<S106>/Vibration_Model' */
  /* Product: '<S112>/Divide2' incorporates:
   *  Constant: '<S112>/Constant2'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S101>/Divide2'
   */
  rtb_Divide2_idx_0 = Plant_Y.Extended_States.prop_vel[0] / 1047.1975511965977;

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */

  /* Math: '<S112>/u^2' */
  rtb_Product1_g = rtb_Divide2_idx_0 * rtb_Divide2_idx_0;

  /* Product: '<S108>/Product2' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Product: '<S97>/Product2'
   *  Trigonometry: '<S108>/Trigonometric Function2'
   */
  rtb_StratosphereModel = arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[0])
    * rtb_Product1_g;

  /* Product: '<S108>/Product1' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Trigonometry: '<S108>/Trigonometric Function1'
   */
  rtb_Product1_l = arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[0]) *
    rtb_Product1_g;

  /* Product: '<S112>/Divide2' incorporates:
   *  Constant: '<S112>/Constant2'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S101>/Divide2'
   */
  rtb_SumofElements = rtb_Divide2_idx_0;

  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  rtb_Divide2_idx_0 = Plant_Y.Extended_States.prop_vel[1] / 1047.1975511965977;

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */

  /* Math: '<S112>/u^2' */
  rtb_Product1_g = rtb_Divide2_idx_0 * rtb_Divide2_idx_0;

  /* Product: '<S108>/Product2' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Product: '<S97>/Product2'
   *  Trigonometry: '<S108>/Trigonometric Function2'
   */
  rtb_Product2_g_idx_1 = arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[1]) *
    rtb_Product1_g;

  /* Product: '<S108>/Product1' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Trigonometry: '<S108>/Trigonometric Function1'
   */
  rtb_Product1_h = arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[1]) *
    rtb_Product1_g;

  /* Product: '<S112>/Divide2' incorporates:
   *  Constant: '<S112>/Constant2'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S101>/Divide2'
   */
  rtb_Divide2_idx_2 = rtb_Divide2_idx_0;

  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  rtb_Divide2_idx_0 = Plant_Y.Extended_States.prop_vel[2] / 1047.1975511965977;

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */

  /* Math: '<S112>/u^2' */
  rtb_Product1_g = rtb_Divide2_idx_0 * rtb_Divide2_idx_0;

  /* Product: '<S108>/Product2' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Product: '<S97>/Product2'
   *  Trigonometry: '<S108>/Trigonometric Function2'
   */
  rtb_Product2_g_idx_2 = arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[2]) *
    rtb_Product1_g;

  /* Product: '<S108>/Product1' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Trigonometry: '<S108>/Trigonometric Function1'
   */
  rtb_Product1_g *= arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[2]);

  /* Product: '<S112>/Divide2' incorporates:
   *  Constant: '<S112>/Constant2'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S101>/Divide2'
   */
  rtb_Product1_c_tmp_idx_2 = rtb_Divide2_idx_0;

  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  rtb_Divide2_idx_0 = Plant_Y.Extended_States.prop_vel[3] / 1047.1975511965977;

  /* Math: '<S112>/u^2' incorporates:
   *  Math: '<S101>/u^2'
   */
  rtb_Divide2_idx_0 *= rtb_Divide2_idx_0;

  /* Update for DiscreteIntegrator: '<S108>/Discrete-Time Integrator' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   */
  rtb_TrigonometricFunction1_id_1 = 0.002F * Plant_Y.Extended_States.prop_vel[0];

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE[0] += rtb_TrigonometricFunction1_id_1;

  /* End of Outputs for SubSystem: '<S106>/Vibration_Model' */
  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_Model' */
  rtb_DiscreteTimeIntegrator_l__2 = rtb_TrigonometricFunction1_id_1;

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_Model' */
  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  /* Outputs for Atomic SubSystem: '<S106>/Vibration_Model' */
  /* Update for DiscreteIntegrator: '<S108>/Discrete-Time Integrator' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   */
  rtb_TrigonometricFunction1_id_1 = 0.002F * Plant_Y.Extended_States.prop_vel[1];

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE[1] += rtb_TrigonometricFunction1_id_1;

  /* End of Outputs for SubSystem: '<S106>/Vibration_Model' */
  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_Model' */
  rtb_DiscreteTimeIntegrator_l__1 = rtb_TrigonometricFunction1_id_1;

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_Model' */
  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  /* Outputs for Atomic SubSystem: '<S106>/Vibration_Model' */
  /* Update for DiscreteIntegrator: '<S108>/Discrete-Time Integrator' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   */
  rtb_TrigonometricFunction1_id_1 = 0.002F * Plant_Y.Extended_States.prop_vel[2];

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE[2] += rtb_TrigonometricFunction1_id_1;

  /* End of Outputs for SubSystem: '<S106>/Vibration_Model' */
  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_Model' */
  rtb_DiscreteTimeIntegrator_l__0 = rtb_TrigonometricFunction1_id_1;

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_Model' */
  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* Outputs for Atomic SubSystem: '<S106>/Vibration_Model' */
  /* Sum: '<S108>/Sum of Elements' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Math: '<S112>/u^2'
   *  Product: '<S108>/Product2'
   *  Product: '<S97>/Product2'
   *  Trigonometry: '<S108>/Trigonometric Function2'
   */
  rtb_StratosphereModel = ((rtb_StratosphereModel + rtb_Product2_g_idx_1) +
    rtb_Product2_g_idx_2) + arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[3])
    * rtb_Divide2_idx_0;

  /* Sum: '<S108>/Sum of Elements1' incorporates:
   *  DiscreteIntegrator: '<S108>/Discrete-Time Integrator'
   *  Math: '<S112>/u^2'
   *  Product: '<S108>/Product1'
   *  Trigonometry: '<S108>/Trigonometric Function1'
   */
  rtb_Product1_g = ((rtb_Product1_l + rtb_Product1_h) + rtb_Product1_g) +
    arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE[3]) * rtb_Divide2_idx_0;

  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  /* Update for DiscreteIntegrator: '<S108>/Discrete-Time Integrator' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   */
  rtb_TrigonometricFunction1_id_1 = 0.002F * Plant_Y.Extended_States.prop_vel[3];

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE[3] += rtb_TrigonometricFunction1_id_1;

  /* Switch: '<S106>/Switch' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  Gain: '<S108>/Gain2'
   *  Gain: '<S108>/Gain4'
   *  Product: '<S108>/Divide'
   *  S-Function (sdsprandsrc2): '<S126>/Random Source'
   *  SignalConversion generated from: '<S110>/Vector Concatenate'
   *  Sum: '<S106>/Sum'
   *  Sum: '<S108>/Sum'
   *  Sum: '<S108>/Sum of Elements'
   *  Sum: '<S108>/Sum of Elements1'
   * */
  rtb_VectorConcatenate_dy[0] = (real32_T)(rtb_StratosphereModel / 4.0 * 0.5 +
    Plant_Y.Plant_States.rot_x_B);
  rtb_TrigonometricFunction1_id_2 = (real32_T)(rtb_Product1_g / 4.0 * 0.5 +
    Plant_Y.Plant_States.rot_y_B);
  rtb_VectorConcatenate_dy[2] = (real32_T)((rtb_StratosphereModel +
    rtb_Product1_g) * 0.5 / 4.0 * 0.5 + Plant_Y.Plant_States.rot_z_B);

  /* End of Outputs for SubSystem: '<S106>/Vibration_Model' */

  /* Sum: '<S114>/Sum' incorporates:
   *  Product: '<S114>/Product'
   *  S-Function (sdsprandsrc2): '<S126>/Random Source'
   *  Sum: '<S114>/Add'
   */
  for (i = 0; i < 3; i++) {
    rtb_RandomSource[i] = (Plant_ConstB.Add_g[i + 3] *
      rtb_TrigonometricFunction1_id_2 + Plant_ConstB.Add_g[i] *
      rtb_VectorConcatenate_dy[0]) + Plant_ConstB.Add_g[i + 6] *
      rtb_VectorConcatenate_dy[2];
  }

  /* End of Sum: '<S114>/Sum' */

  /* DiscreteIntegrator: '<S113>/Discrete-Time Integrator5' incorporates:
   *  Sum: '<S114>/Sum'
   */
  if (Plant_DW.DiscreteTimeIntegrator5_IC_LOAD != 0) {
    Plant_DW.DiscreteTimeIntegrator5_DSTATE[0] = rtb_RandomSource[0];
    Plant_DW.DiscreteTimeIntegrator5_DSTATE[1] = rtb_RandomSource[1];
    Plant_DW.DiscreteTimeIntegrator5_DSTATE[2] = rtb_RandomSource[2];
  }

  /* S-Function (sdsprandsrc2): '<S104>/Random Source' */
  RandSrc_GZ_R(rtb_RandomSource_f, &Plant_ConstP.pooled14, 1,
               Plant_ConstP.RandomSource_VarianceRTP_f, 3,
               Plant_DW.RandomSource_STATE_DWORK_k, 3, 1);

  /* S-Function (sdsprandsrc2): '<S115>/Random Source' incorporates:
   *  Switch: '<S96>/Switch'
   */
  RandSrc_GZ_R(rtb_omega_B_radPs, &Plant_ConstP.pooled14, 1,
               Plant_ConstP.RandomSource_VarianceRTP_b, 3,
               Plant_DW.RandomSource_STATE_DWORK_h, 3, 1);

  /* Saturate: '<S107>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S113>/Discrete-Time Integrator5'
   */
  if (Plant_DW.DiscreteTimeIntegrator5_DSTATE[0] > 34.9065857F) {
    rtb_TrigonometricFunction1_idx_ = 34.9065857F;
  } else if (Plant_DW.DiscreteTimeIntegrator5_DSTATE[0] < -34.9065857F) {
    rtb_TrigonometricFunction1_idx_ = -34.9065857F;
  } else {
    rtb_TrigonometricFunction1_idx_ = Plant_DW.DiscreteTimeIntegrator5_DSTATE[0];
  }

  /* Sum: '<S107>/Sum' incorporates:
   *  Switch: '<S96>/Switch'
   */
  rtb_TrigonometricFunction1_id_2 = rtb_TrigonometricFunction1_idx_ +
    rtb_omega_B_radPs[0];

  /* Switch: '<S107>/Switch' incorporates:
   *  S-Function (sdsprandsrc2): '<S126>/Random Source'
   */
  rtb_VectorConcatenate_dy[0] = rtb_TrigonometricFunction1_id_2;

  /* Sum: '<S107>/Sum' */
  rtb_RandomSource1[0] = rtb_TrigonometricFunction1_id_2;

  /* Saturate: '<S107>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S113>/Discrete-Time Integrator5'
   */
  if (Plant_DW.DiscreteTimeIntegrator5_DSTATE[1] > 34.9065857F) {
    rtb_TrigonometricFunction1_idx_ = 34.9065857F;
  } else if (Plant_DW.DiscreteTimeIntegrator5_DSTATE[1] < -34.9065857F) {
    rtb_TrigonometricFunction1_idx_ = -34.9065857F;
  } else {
    rtb_TrigonometricFunction1_idx_ = Plant_DW.DiscreteTimeIntegrator5_DSTATE[1];
  }

  /* Sum: '<S107>/Sum' incorporates:
   *  Switch: '<S96>/Switch'
   */
  rtb_TrigonometricFunction1_id_2 = rtb_TrigonometricFunction1_idx_ +
    rtb_omega_B_radPs[1];

  /* Switch: '<S107>/Switch' incorporates:
   *  S-Function (sdsprandsrc2): '<S126>/Random Source'
   */
  rtb_VectorConcatenate_dy[1] = rtb_TrigonometricFunction1_id_2;

  /* Sum: '<S107>/Sum' */
  rtb_RandomSource1[1] = rtb_TrigonometricFunction1_id_2;

  /* Saturate: '<S107>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S113>/Discrete-Time Integrator5'
   */
  if (Plant_DW.DiscreteTimeIntegrator5_DSTATE[2] > 34.9065857F) {
    rtb_TrigonometricFunction1_idx_ = 34.9065857F;
  } else if (Plant_DW.DiscreteTimeIntegrator5_DSTATE[2] < -34.9065857F) {
    rtb_TrigonometricFunction1_idx_ = -34.9065857F;
  } else {
    rtb_TrigonometricFunction1_idx_ = Plant_DW.DiscreteTimeIntegrator5_DSTATE[2];
  }

  /* Sum: '<S107>/Sum' incorporates:
   *  Switch: '<S96>/Switch'
   */
  rtb_TrigonometricFunction1_id_2 = rtb_TrigonometricFunction1_idx_ +
    rtb_omega_B_radPs[2];

  /* Switch: '<S107>/Switch' incorporates:
   *  S-Function (sdsprandsrc2): '<S126>/Random Source'
   */
  rtb_VectorConcatenate_dy[2] = rtb_TrigonometricFunction1_id_2;

  /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
  /* Math: '<S101>/u^2' incorporates:
   *  Product: '<S101>/Divide2'
   */
  rtb_Product1_g = rtb_SumofElements * rtb_SumofElements;

  /* Product: '<S97>/Product2' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Trigonometry: '<S97>/Trigonometric Function2'
   */
  rtb_StratosphereModel = arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[0])
    * rtb_Product1_g;

  /* Product: '<S97>/Product1' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Trigonometry: '<S97>/Trigonometric Function1'
   */
  rtb_Product1_l = arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[0]) *
    rtb_Product1_g;

  /* Math: '<S101>/u^2' incorporates:
   *  Product: '<S101>/Divide2'
   */
  rtb_Product1_g = rtb_Divide2_idx_2 * rtb_Divide2_idx_2;

  /* Product: '<S97>/Product2' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Trigonometry: '<S97>/Trigonometric Function2'
   */
  rtb_Product2_g_idx_1 = arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[1])
    * rtb_Product1_g;

  /* Product: '<S97>/Product1' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Trigonometry: '<S97>/Trigonometric Function1'
   */
  rtb_Product1_h = arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[1]) *
    rtb_Product1_g;

  /* Math: '<S101>/u^2' incorporates:
   *  Product: '<S101>/Divide2'
   */
  rtb_Product1_g = rtb_Product1_c_tmp_idx_2 * rtb_Product1_c_tmp_idx_2;

  /* Product: '<S97>/Product2' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Trigonometry: '<S97>/Trigonometric Function2'
   */
  rtb_Product2_g_idx_2 = arm_sin_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[2])
    * rtb_Product1_g;

  /* Product: '<S97>/Product1' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Trigonometry: '<S97>/Trigonometric Function1'
   */
  rtb_Product1_g *= arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[2]);

  /* Update for DiscreteIntegrator: '<S97>/Discrete-Time Integrator' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_p[0] += rtb_DiscreteTimeIntegrator_l__2;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_p[1] += rtb_DiscreteTimeIntegrator_l__1;
  Plant_DW.DiscreteTimeIntegrator_DSTATE_p[2] += rtb_DiscreteTimeIntegrator_l__0;

  /* Sum: '<S97>/Sum of Elements' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Product: '<S97>/Product2'
   *  Trigonometry: '<S97>/Trigonometric Function2'
   */
  rtb_StratosphereModel = ((rtb_StratosphereModel + rtb_Product2_g_idx_1) +
    rtb_Product2_g_idx_2) + arm_sin_f32
    (Plant_DW.DiscreteTimeIntegrator_DSTATE_p[3]) * rtb_Divide2_idx_0;

  /* Sum: '<S97>/Sum of Elements1' incorporates:
   *  DiscreteIntegrator: '<S97>/Discrete-Time Integrator'
   *  Product: '<S97>/Product1'
   *  Trigonometry: '<S97>/Trigonometric Function1'
   */
  rtb_Product1_g = ((rtb_Product1_l + rtb_Product1_h) + rtb_Product1_g) +
    arm_cos_f32(Plant_DW.DiscreteTimeIntegrator_DSTATE_p[3]) * rtb_Divide2_idx_0;

  /* Update for DiscreteIntegrator: '<S97>/Discrete-Time Integrator' */
  Plant_DW.DiscreteTimeIntegrator_DSTATE_p[3] += rtb_TrigonometricFunction1_id_1;

  /* SignalConversion generated from: '<S97>/Vector Concatenate' incorporates:
   *  Sum: '<S97>/Sum of Elements'
   */
  rtb_VectorConcatenate_d[0] = rtb_StratosphereModel;

  /* SignalConversion generated from: '<S97>/Vector Concatenate' incorporates:
   *  Sum: '<S97>/Sum of Elements1'
   */
  rtb_VectorConcatenate_d[1] = rtb_Product1_g;

  /* Gain: '<S97>/Gain2' incorporates:
   *  Sum: '<S97>/Sum'
   *  Sum: '<S97>/Sum of Elements'
   *  Sum: '<S97>/Sum of Elements1'
   */
  rtb_VectorConcatenate_d[2] = (rtb_StratosphereModel + rtb_Product1_g) * 0.5;

  /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */

  /* Switch: '<S95>/Switch' incorporates:
   *  Concatenate: '<S97>/Vector Concatenate'
   *  Constant: '<S99>/Gravity'
   *  Delay generated from: '<Root>/Delay'
   *  Gain: '<S97>/Gain4'
   *  Product: '<S97>/Divide'
   *  Product: '<S99>/Product1'
   *  SignalConversion generated from: '<S99>/Vector Concatenate1'
   *  Sum: '<S95>/Sum'
   *  Sum: '<S99>/Sum'
   *  Switch: '<S96>/Switch'
   * */
  for (i = 0; i < 3; i++) {
    /* Outputs for Atomic SubSystem: '<S95>/Vibration_Model' */
    rtb_omega_B_radPs[i] = (real32_T)(((Plant_Y.Extended_States.M_BO[i + 3] *
      Plant_Y.Plant_States.acc_y_O + Plant_Y.Extended_States.M_BO[i] *
      Plant_Y.Plant_States.acc_x_O) + Plant_Y.Extended_States.M_BO[i + 6] *
      (Plant_Y.Plant_States.acc_z_O - 9.80665F)) + rtb_VectorConcatenate_d[i] /
      4.0 * Plant_ConstP.Gain4_Gain[i]);

    /* End of Outputs for SubSystem: '<S95>/Vibration_Model' */
  }

  /* End of Switch: '<S95>/Switch' */

  /* Sum: '<S103>/Sum' incorporates:
   *  Product: '<S103>/Product'
   *  Sum: '<S103>/Add'
   *  Switch: '<S96>/Switch'
   */
  for (i = 0; i < 3; i++) {
    rtb_vel_O_mPs[i] = (Plant_ConstB.Add_m[i + 3] * rtb_omega_B_radPs[1] +
                        Plant_ConstB.Add_m[i] * rtb_omega_B_radPs[0]) +
      Plant_ConstB.Add_m[i + 6] * rtb_omega_B_radPs[2];
  }

  /* End of Sum: '<S103>/Sum' */

  /* DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' incorporates:
   *  Sum: '<S103>/Sum'
   */
  if (Plant_DW.DiscreteTimeIntegrator5_IC_LO_j != 0) {
    Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[0] = rtb_vel_O_mPs[0];
    Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[1] = rtb_vel_O_mPs[1];
    Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[2] = rtb_vel_O_mPs[2];
  }

  /* Outport: '<Root>/IMU' incorporates:
   *  BusAssignment: '<S92>/Bus Assignment'
   *  Memory: '<S66>/Memory1'
   */
  Plant_Y.IMU.timestamp = Plant_DW.Memory1_PreviousInput;

  /* Update for DiscreteIntegrator: '<S113>/Discrete-Time Integrator5' */
  Plant_DW.DiscreteTimeIntegrator5_IC_LOAD = 0U;

  /* Update for DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' */
  Plant_DW.DiscreteTimeIntegrator5_IC_LO_j = 0U;

  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_MAG' */
  /* Gain: '<S121>/rad_to_index' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S121>/rad_to_index'
   */
  rtb_StratosphereModel = fmod(floor(5.7295779513082321 *
    Plant_Y.Plant_States.lat), 4.294967296E+9);

  /* Sum: '<S121>/Add' incorporates:
   *  Constant: '<S121>/offset'
   *  Gain: '<S121>/rad_to_index'
   */
  i = (rtb_StratosphereModel < 0.0 ? -(int32_T)(uint32_T)-rtb_StratosphereModel :
       (int32_T)(uint32_T)rtb_StratosphereModel) + 8;

  /* Saturate: '<S121>/Saturation1' */
  if (i > 16) {
    i = 16;
  } else if (i < 0) {
    i = 0;
  }

  /* Gain: '<S121>/rad_to_index' incorporates:
   *  Delay generated from: '<Root>/Delay'
   *  SignalConversion generated from: '<S121>/rad_to_index'
   */
  rtb_StratosphereModel = fmod(floor(5.7295779513082321 *
    Plant_Y.Plant_States.lon), 4.294967296E+9);

  /* Sum: '<S121>/Add' incorporates:
   *  Constant: '<S121>/offset'
   *  Gain: '<S121>/rad_to_index'
   */
  rtb_Saturation1_idx_1 = (rtb_StratosphereModel < 0.0 ? -(int32_T)(uint32_T)
    -rtb_StratosphereModel : (int32_T)(uint32_T)rtb_StratosphereModel) + 18;

  /* Saturate: '<S121>/Saturation1' */
  if (rtb_Saturation1_idx_1 > 36) {
    rtb_Saturation1_idx_1 = 36;
  } else if (rtb_Saturation1_idx_1 < 0) {
    rtb_Saturation1_idx_1 = 0;
  }

  /* LookupNDDirect: '<S121>/Declination_Lookup_Table' incorporates:
   *  LookupNDDirect: '<S121>/Inclination_Lookup_Table'
   *  LookupNDDirect: '<S121>/Magnitude_Lookup_Table'
   *
   * About '<S121>/Declination_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   *
   * About '<S121>/Inclination_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   *
   * About '<S121>/Magnitude_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  i += rtb_Saturation1_idx_1 * 17;

  /* Gain: '<S122>/Gain1' incorporates:
   *  LookupNDDirect: '<S121>/Declination_Lookup_Table'
   *
   * About '<S121>/Declination_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  rtb_TrigonometricFunction1_id_1 =
    Plant_ConstP.Declination_Lookup_Table_table[i] * 0.0174532924F;

  /* Trigonometry: '<S124>/Trigonometric Function1' incorporates:
   *  Trigonometry: '<S124>/Trigonometric Function3'
   */
  rtb_TrigonometricFunction1_id_0 = arm_cos_f32(rtb_TrigonometricFunction1_id_1);
  rtb_VectorConcatenate_c[0] = rtb_TrigonometricFunction1_id_0;

  /* Trigonometry: '<S124>/Trigonometric Function' incorporates:
   *  Trigonometry: '<S124>/Trigonometric Function2'
   */
  rtb_TrigonometricFunction1_id_1 = arm_sin_f32(rtb_TrigonometricFunction1_id_1);
  rtb_VectorConcatenate_c[1] = rtb_TrigonometricFunction1_id_1;

  /* SignalConversion generated from: '<S124>/Vector Concatenate1' incorporates:
   *  Constant: '<S124>/Constant3'
   */
  rtb_VectorConcatenate_c[2] = 0.0F;

  /* Gain: '<S124>/Gain' */
  rtb_VectorConcatenate_c[3] = -rtb_TrigonometricFunction1_id_1;

  /* Trigonometry: '<S124>/Trigonometric Function3' */
  rtb_VectorConcatenate_c[4] = rtb_TrigonometricFunction1_id_0;

  /* SignalConversion generated from: '<S124>/Vector Concatenate2' incorporates:
   *  Constant: '<S124>/Constant4'
   */
  rtb_VectorConcatenate_c[5] = 0.0F;

  /* Gain: '<S122>/Gain' incorporates:
   *  LookupNDDirect: '<S121>/Inclination_Lookup_Table'
   *
   * About '<S121>/Inclination_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  rtb_TrigonometricFunction1_id_1 =
    Plant_ConstP.Inclination_Lookup_Table_table[i] * -0.0174532924F;

  /* Trigonometry: '<S123>/Trigonometric Function3' incorporates:
   *  Trigonometry: '<S123>/Trigonometric Function1'
   */
  rtb_DiscreteTimeIntegrator_l__2 = arm_cos_f32(rtb_TrigonometricFunction1_id_1);
  rtb_MatrixConcatenate1[0] = rtb_DiscreteTimeIntegrator_l__2;

  /* SignalConversion generated from: '<S123>/Vector Concatenate2' incorporates:
   *  Constant: '<S123>/Constant4'
   */
  rtb_MatrixConcatenate1[1] = 0.0F;

  /* Trigonometry: '<S123>/Trigonometric Function2' incorporates:
   *  Trigonometry: '<S123>/Trigonometric Function'
   */
  rtb_DiscreteTimeIntegrator_l__1 = arm_sin_f32(rtb_TrigonometricFunction1_id_1);

  /* Gain: '<S123>/Gain' incorporates:
   *  Trigonometry: '<S123>/Trigonometric Function2'
   */
  rtb_MatrixConcatenate1[2] = -rtb_DiscreteTimeIntegrator_l__1;

  /* End of Outputs for SubSystem: '<S5>/Sensor_MAG' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' */
  rtb_Divide_f_idx_2 = Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[0];

  /* Update for DiscreteIntegrator: '<S113>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S113>/Gain'
   *  Sum: '<S113>/Sum5'
   *  Sum: '<S114>/Sum'
   */
  Plant_DW.DiscreteTimeIntegrator5_DSTATE[0] += (rtb_RandomSource[0] -
    Plant_DW.DiscreteTimeIntegrator5_DSTATE[0]) * 314.159271F * 0.002F;

  /* Update for DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S102>/Gain'
   *  Sum: '<S102>/Sum5'
   *  Sum: '<S103>/Sum'
   */
  Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[0] += (rtb_vel_O_mPs[0] -
    Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[0]) * 314.159271F * 0.002F;

  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_MAG' */
  /* SignalConversion generated from: '<S124>/Vector Concatenate' incorporates:
   *  Concatenate: '<S124>/Vector Concatenate3'
   */
  rtb_VectorConcatenate_c[6] = Plant_ConstB.VectorConcatenate3_n[0];

  /* SignalConversion generated from: '<S123>/Vector Concatenate' incorporates:
   *  Concatenate: '<S123>/Vector Concatenate3'
   */
  rtb_MatrixConcatenate1[3] = Plant_ConstB.VectorConcatenate3[0];

  /* End of Outputs for SubSystem: '<S5>/Sensor_MAG' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' */
  rtb_TrigonometricFunction1_id_1 = Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[1];

  /* Update for DiscreteIntegrator: '<S113>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S113>/Gain'
   *  Sum: '<S113>/Sum5'
   *  Sum: '<S114>/Sum'
   */
  Plant_DW.DiscreteTimeIntegrator5_DSTATE[1] += (rtb_RandomSource[1] -
    Plant_DW.DiscreteTimeIntegrator5_DSTATE[1]) * 314.159271F * 0.002F;

  /* Update for DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S102>/Gain'
   *  Sum: '<S102>/Sum5'
   *  Sum: '<S103>/Sum'
   */
  Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[1] += (rtb_vel_O_mPs[1] -
    Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[1]) * 314.159271F * 0.002F;

  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_MAG' */
  /* SignalConversion generated from: '<S124>/Vector Concatenate' incorporates:
   *  Concatenate: '<S124>/Vector Concatenate3'
   */
  rtb_VectorConcatenate_c[7] = Plant_ConstB.VectorConcatenate3_n[1];

  /* SignalConversion generated from: '<S123>/Vector Concatenate' incorporates:
   *  Concatenate: '<S123>/Vector Concatenate3'
   */
  rtb_MatrixConcatenate1[4] = Plant_ConstB.VectorConcatenate3[1];

  /* End of Outputs for SubSystem: '<S5>/Sensor_MAG' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' */
  rtb_TrigonometricFunction1_id_0 = Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[2];

  /* Update for DiscreteIntegrator: '<S113>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S113>/Gain'
   *  Sum: '<S113>/Sum5'
   *  Sum: '<S114>/Sum'
   */
  Plant_DW.DiscreteTimeIntegrator5_DSTATE[2] += (rtb_RandomSource[2] -
    Plant_DW.DiscreteTimeIntegrator5_DSTATE[2]) * 314.159271F * 0.002F;

  /* Update for DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S102>/Gain'
   *  Sum: '<S102>/Sum5'
   *  Sum: '<S103>/Sum'
   */
  Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[2] += (rtb_vel_O_mPs[2] -
    Plant_DW.DiscreteTimeIntegrator5_DSTAT_c[2]) * 314.159271F * 0.002F;

  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_MAG' */
  /* SignalConversion generated from: '<S124>/Vector Concatenate' incorporates:
   *  Concatenate: '<S124>/Vector Concatenate3'
   */
  rtb_VectorConcatenate_c[8] = Plant_ConstB.VectorConcatenate3_n[2];

  /* SignalConversion generated from: '<S123>/Vector Concatenate' incorporates:
   *  Concatenate: '<S123>/Vector Concatenate3'
   */
  rtb_MatrixConcatenate1[5] = Plant_ConstB.VectorConcatenate3[2];

  /* Trigonometry: '<S123>/Trigonometric Function' */
  rtb_MatrixConcatenate1[6] = rtb_DiscreteTimeIntegrator_l__1;

  /* SignalConversion generated from: '<S123>/Vector Concatenate1' incorporates:
   *  Constant: '<S123>/Constant3'
   */
  rtb_MatrixConcatenate1[7] = 0.0F;

  /* Trigonometry: '<S123>/Trigonometric Function1' */
  rtb_MatrixConcatenate1[8] = rtb_DiscreteTimeIntegrator_l__2;

  /* Gain: '<S122>/toGauss' incorporates:
   *  LookupNDDirect: '<S121>/Magnitude_Lookup_Table'
   *
   * About '<S121>/Magnitude_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  rtb_DiscreteTimeIntegrator_l__2 = Plant_ConstP.Magnitude_Lookup_Table_table[i]
    * 0.01F;

  /* S-Function (sdsprandsrc2): '<S126>/Random Source' */
  RandSrc_GZ_R(rtb_VectorConcatenate_dy, &Plant_ConstP.pooled14, 1,
               Plant_ConstP.RandomSource_VarianceRTP_a, 3,
               Plant_DW.RandomSource_STATE_DWORK, 3, 1);

  /* Product: '<S122>/Multiply1' incorporates:
   *  Concatenate: '<S123>/Vector Concatenate'
   *  Product: '<S122>/Multiply'
   */
  for (i = 0; i < 3; i++) {
    rtb_Switch_i[i] = rtb_MatrixConcatenate1[i] *
      rtb_DiscreteTimeIntegrator_l__2;
  }

  /* End of Product: '<S122>/Multiply1' */

  /* Product: '<S122>/Multiply2' incorporates:
   *  Concatenate: '<S124>/Vector Concatenate'
   */
  for (i = 0; i < 3; i++) {
    rtb_Add_ch[i] = (rtb_VectorConcatenate_c[i + 3] * rtb_Switch_i[1] +
                     rtb_VectorConcatenate_c[i] * rtb_Switch_i[0]) +
      rtb_VectorConcatenate_c[i + 6] * rtb_Switch_i[2];
  }

  /* End of Product: '<S122>/Multiply2' */

  /* Product: '<S119>/Product' incorporates:
   *  Delay generated from: '<Root>/Delay'
   */
  for (i = 0; i < 3; i++) {
    rtb_Add1_c[i] = (Plant_Y.Extended_States.M_BO[i + 3] * rtb_Add_ch[1] +
                     Plant_Y.Extended_States.M_BO[i] * rtb_Add_ch[0]) +
      Plant_Y.Extended_States.M_BO[i + 6] * rtb_Add_ch[2];
  }

  /* End of Product: '<S119>/Product' */
  for (i = 0; i < 3; i++) {
    /* Sum: '<S125>/Sum' incorporates:
     *  Product: '<S125>/Product'
     *  Sum: '<S125>/Add'
     */
    rtb_TrigonometricFunction1_idx_ = (Plant_ConstB.Add[i + 3] * rtb_Add1_c[1] +
      Plant_ConstB.Add[i] * rtb_Add1_c[0]) + Plant_ConstB.Add[i + 6] *
      rtb_Add1_c[2];

    /* Saturate: '<S120>/Saturation' incorporates:
     *  Sum: '<S125>/Sum'
     */
    if (rtb_TrigonometricFunction1_idx_ > 4.0F) {
      rtb_TrigonometricFunction1_idx_ = 4.0F;
    } else if (rtb_TrigonometricFunction1_idx_ < -4.0F) {
      rtb_TrigonometricFunction1_idx_ = -4.0F;
    }

    /* Sum: '<S120>/Add' incorporates:
     *  S-Function (sdsprandsrc2): '<S126>/Random Source'
     *  Saturate: '<S120>/Saturation'
     */
    rtb_VectorConcatenate_dy[i] += rtb_TrigonometricFunction1_idx_;
  }

  /* RateTransition: '<S116>/Rate Transition' incorporates:
   *  Memory: '<S66>/Memory1'
   *  Sum: '<S120>/Add'
   *  Switch: '<S120>/Switch'
   */
  if (Plant_M->Timing.TaskCounters.TID[1] == 0) {
    rtb_RateTransition_b_timestamp = Plant_DW.Memory1_PreviousInput;
    rtb_RateTransition_b_mag_x = rtb_VectorConcatenate_dy[0];
    rtb_RateTransition_b_mag_y = rtb_VectorConcatenate_dy[1];
    rtb_RateTransition_b_mag_z = rtb_VectorConcatenate_dy[2];
  }

  /* End of RateTransition: '<S116>/Rate Transition' */
  /* End of Outputs for SubSystem: '<S5>/Sensor_MAG' */

  /* Update for Memory: '<S66>/Memory1' incorporates:
   *  Constant: '<S66>/dt'
   *  Sum: '<S66>/Sum'
   */
  Plant_DW.Memory1_PreviousInput += PLANT_EXPORT.period;

  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* Outport: '<Root>/IMU' incorporates:
   *  Sum: '<S107>/Sum'
   *  Switch: '<S107>/Switch'
   */
  Plant_Y.IMU.gyr_x = rtb_RandomSource1[0];
  Plant_Y.IMU.gyr_y = rtb_RandomSource1[1];

  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_Model' */
  Plant_Y.IMU.gyr_z = rtb_TrigonometricFunction1_id_2;

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_Model' */
  /* Outputs for Atomic SubSystem: '<S5>/Sensor_IMU' */
  /* Saturate: '<S96>/Saturation' */
  if (rtb_Divide_f_idx_2 > 78.4532F) {
    rtb_Divide_f_idx_2 = 78.4532F;
  } else if (rtb_Divide_f_idx_2 < -78.4532F) {
    rtb_Divide_f_idx_2 = -78.4532F;
  }

  /* Outport: '<Root>/IMU' incorporates:
   *  DiscreteIntegrator: '<S102>/Discrete-Time Integrator5'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S96>/Sum'
   */
  Plant_Y.IMU.acc_x = rtb_Divide_f_idx_2 + rtb_RandomSource_f[0];

  /* Saturate: '<S96>/Saturation' */
  if (rtb_TrigonometricFunction1_id_1 > 78.4532F) {
    rtb_TrigonometricFunction1_id_1 = 78.4532F;
  } else if (rtb_TrigonometricFunction1_id_1 < -78.4532F) {
    rtb_TrigonometricFunction1_id_1 = -78.4532F;
  }

  /* Outport: '<Root>/IMU' incorporates:
   *  DiscreteIntegrator: '<S102>/Discrete-Time Integrator5'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S96>/Sum'
   */
  Plant_Y.IMU.acc_y = rtb_TrigonometricFunction1_id_1 + rtb_RandomSource_f[1];

  /* Saturate: '<S96>/Saturation' */
  if (rtb_TrigonometricFunction1_id_0 > 78.4532F) {
    rtb_TrigonometricFunction1_id_0 = 78.4532F;
  } else if (rtb_TrigonometricFunction1_id_0 < -78.4532F) {
    rtb_TrigonometricFunction1_id_0 = -78.4532F;
  }

  /* Outport: '<Root>/IMU' incorporates:
   *  DiscreteIntegrator: '<S102>/Discrete-Time Integrator5'
   *  S-Function (sdsprandsrc2): '<S104>/Random Source'
   *  Sum: '<S96>/Sum'
   */
  Plant_Y.IMU.acc_z = rtb_TrigonometricFunction1_id_0 + rtb_RandomSource_f[2];

  /* End of Outputs for SubSystem: '<S5>/Sensor_IMU' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_Model' */
  if (Plant_M->Timing.TaskCounters.TID[1] == 0) {
    /* Outport: '<Root>/MAG' incorporates:
     *  RateTransition: '<S116>/Rate Transition'
     */
    Plant_Y.MAG.timestamp = rtb_RateTransition_b_timestamp;
    Plant_Y.MAG.mag_x = rtb_RateTransition_b_mag_x;
    Plant_Y.MAG.mag_y = rtb_RateTransition_b_mag_y;
    Plant_Y.MAG.mag_z = rtb_RateTransition_b_mag_z;

    /* Outport: '<Root>/Barometer' incorporates:
     *  RateTransition: '<S72>/Rate Transition'
     */
    Plant_Y.Barometer.timestamp = rtb_RateTransition_m_timestamp;
    Plant_Y.Barometer.pressure = rtb_RateTransition_m_pressure;
    Plant_Y.Barometer.temperature = rtb_RateTransition_m_temperatur;
  }

  if (Plant_M->Timing.TaskCounters.TID[2] == 0) {
    /* Outport: '<Root>/GPS' incorporates:
     *  RateTransition: '<S78>/Rate Transition'
     */
    Plant_Y.GPS.timestamp = rtb_RateTransition_timestamp;
    Plant_Y.GPS.iTOW = 1U;
    Plant_Y.GPS.year = 2020U;
    Plant_Y.GPS.month = 1U;
    Plant_Y.GPS.day = 1U;
    Plant_Y.GPS.hour = 0U;
    Plant_Y.GPS.min = 0U;
    Plant_Y.GPS.sec = 0U;
    Plant_Y.GPS.valid = 1U;
    Plant_Y.GPS.tAcc = 0U;
    Plant_Y.GPS.nano = 0;
    Plant_Y.GPS.fixType = Plant_ConstB.DataTypeConversion;
    Plant_Y.GPS.flags = 0U;
    Plant_Y.GPS.reserved1 = 0U;
    Plant_Y.GPS.numSV = Plant_ConstB.DataTypeConversion1;
    Plant_Y.GPS.lon = rtb_RateTransition_lon;
    Plant_Y.GPS.lat = rtb_RateTransition_lat;
    Plant_Y.GPS.height = rtb_RateTransition_height;
    Plant_Y.GPS.hMSL = rtb_RateTransition_height;
    Plant_Y.GPS.hAcc = rtb_RateTransition_hAcc;
    Plant_Y.GPS.vAcc = rtb_RateTransition_vAcc;
    Plant_Y.GPS.velN = rtb_RateTransition_velN;
    Plant_Y.GPS.velE = rtb_RateTransition_velE;
    Plant_Y.GPS.velD = rtb_RateTransition_velD;
    Plant_Y.GPS.gSpeed = rtb_RateTransition_gSpeed;
    Plant_Y.GPS.heading = 0;
    Plant_Y.GPS.sAcc = rtb_RateTransition_sAcc;
    Plant_Y.GPS.headingAcc = 0U;
    Plant_Y.GPS.pDOP = 0U;
    Plant_Y.GPS.reserved2 = 0U;
  }

  rate_scheduler();
}

/* Model initialize function */
void Plant_init(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Plant_M, 0,
                sizeof(RT_MODEL_Plant_T));

  /* states (dwork) */
  (void) memset((void *)&Plant_DW, 0,
                sizeof(DW_Plant_T));

  /* external inputs */
  Plant_U.Control_Out = Plant_rtZControl_Out_Bus;

  /* external outputs */
  (void)memset(&Plant_Y, 0, sizeof(ExtY_Plant_T));

  {
    uint32_T RandomSource_SEED_DWORK_k;

    /* SystemInitialize for Atomic SubSystem: '<Root>/Kinematic_Equation' */
    /* InitializeConditions for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[0] = Plant_ConstB.quat0[0];
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[1] = Plant_ConstB.quat0[1];
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[2] = Plant_ConstB.quat0[2];
    Plant_DW.DiscreteTimeIntegrator_DSTATE_d[3] = Plant_ConstB.quat0[3];
    Plant_DW.DiscreteTimeIntegrator_PrevRese = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
    Plant_DW.DiscreteTimeIntegrator_PrevRe_d = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */
    Plant_DW.DiscreteTimeIntegrator_PrevRe_k = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S42>/Discrete-Time Integrator1' */
    Plant_DW.DiscreteTimeIntegrator1_PrevRes = 0;

    /* End of SystemInitialize for SubSystem: '<Root>/Kinematic_Equation' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/Bus_Constructor' */
    /* InitializeConditions for Delay: '<S22>/Delay1' */
    Plant_DW.Delay1_DSTATE[0] = 0.65673;
    Plant_DW.Delay1_DSTATE[1] = -2.1361;
    Plant_DW.Delay1_DSTATE[2] = 4.5;

    /* End of SystemInitialize for SubSystem: '<Root>/Bus_Constructor' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/Sensor_Model' */
    /* SystemInitialize for Atomic SubSystem: '<S5>/Sensor_Barometer' */
    /* InitializeConditions for S-Function (sdsprandsrc2): '<S77>/Random Source' */
    RandomSource_SEED_DWORK_k = 91337U;
    RandSrcInitState_GZ(&RandomSource_SEED_DWORK_k,
                        &Plant_DW.RandomSource_STATE_DWORK_b[0], 1);

    /* End of SystemInitialize for SubSystem: '<S5>/Sensor_Barometer' */

    /* SystemInitialize for Atomic SubSystem: '<S5>/Sensor_GPS' */
    /* InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source' */
    RandSrcCreateSeeds_32(63235U, Plant_DW.RandomSource_SEED_DWORK_m, 3);
    RandSrcInitState_GZ(&Plant_DW.RandomSource_SEED_DWORK_m[0],
                        &Plant_DW.RandomSource_STATE_DWORK_l[0], 3);

    /* InitializeConditions for DiscreteFir: '<S88>/Discrete FIR Filter' */
    Plant_DW.DiscreteFIRFilter_states[0] = 0.0;
    Plant_DW.DiscreteFIRFilter_states[1] = 0.0;
    Plant_DW.DiscreteFIRFilter_states[2] = 0.0;

    /* InitializeConditions for S-Function (sdsprandsrc2): '<S86>/Random Source1' */
    RandSrcCreateSeeds_32(9754U, Plant_DW.RandomSource1_SEED_DWORK, 3);
    RandSrcInitState_GZ(&Plant_DW.RandomSource1_SEED_DWORK[0],
                        &Plant_DW.RandomSource1_STATE_DWORK[0], 3);

    /* InitializeConditions for DiscreteFir: '<S89>/Discrete FIR Filter' */
    Plant_DW.DiscreteFIRFilter_states_f[0] = 0.0F;
    Plant_DW.DiscreteFIRFilter_states_f[1] = 0.0F;
    Plant_DW.DiscreteFIRFilter_states_f[2] = 0.0F;

    /* End of SystemInitialize for SubSystem: '<S5>/Sensor_GPS' */

    /* SystemInitialize for Atomic SubSystem: '<S5>/Sensor_IMU' */
    /* InitializeConditions for DiscreteIntegrator: '<S113>/Discrete-Time Integrator5' */
    Plant_DW.DiscreteTimeIntegrator5_IC_LOAD = 1U;

    /* InitializeConditions for S-Function (sdsprandsrc2): '<S104>/Random Source' */
    RandSrcCreateSeeds_32(90579U, Plant_DW.RandomSource_SEED_DWORK_f, 3);
    RandSrcInitState_GZ(&Plant_DW.RandomSource_SEED_DWORK_f[0],
                        &Plant_DW.RandomSource_STATE_DWORK_k[0], 3);

    /* InitializeConditions for S-Function (sdsprandsrc2): '<S115>/Random Source' */
    RandSrcCreateSeeds_32(81472U, Plant_DW.RandomSource_SEED_DWORK_n, 3);
    RandSrcInitState_GZ(&Plant_DW.RandomSource_SEED_DWORK_n[0],
                        &Plant_DW.RandomSource_STATE_DWORK_h[0], 3);

    /* InitializeConditions for DiscreteIntegrator: '<S102>/Discrete-Time Integrator5' */
    Plant_DW.DiscreteTimeIntegrator5_IC_LO_j = 1U;

    /* End of SystemInitialize for SubSystem: '<S5>/Sensor_IMU' */

    /* SystemInitialize for Atomic SubSystem: '<S5>/Sensor_MAG' */
    /* InitializeConditions for S-Function (sdsprandsrc2): '<S126>/Random Source' */
    RandSrcCreateSeeds_32(12698U, Plant_DW.RandomSource_SEED_DWORK, 3);
    RandSrcInitState_GZ(&Plant_DW.RandomSource_SEED_DWORK[0],
                        &Plant_DW.RandomSource_STATE_DWORK[0], 3);

    /* End of SystemInitialize for SubSystem: '<S5>/Sensor_MAG' */
    /* End of SystemInitialize for SubSystem: '<Root>/Sensor_Model' */
  }
}

/* Model terminate function */
void Plant_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
