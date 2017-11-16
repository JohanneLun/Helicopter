/*
 * p3p3.c
 *
 * Code generation for model "p3p3".
 *
 * Model version              : 1.69
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat Oct 07 12:11:52 2017
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "p3p3.h"
#include "p3p3_private.h"
#include "p3p3_dt.h"

/* Block signals (auto storage) */
B_p3p3_T p3p3_B;

/* Continuous states */
X_p3p3_T p3p3_X;

/* Block states (auto storage) */
DW_p3p3_T p3p3_DW;

/* Real-time model */
RT_MODEL_p3p3_T p3p3_M_;
RT_MODEL_p3p3_T *const p3p3_M = &p3p3_M_;
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(p3p3_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(p3p3_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (p3p3_M->Timing.TaskCounters.TID[1] == 0) {
    p3p3_M->Timing.RateInteraction.TID1_2 = (p3p3_M->Timing.TaskCounters.TID[2] ==
      0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    p3p3_M->Timing.perTaskSampleHits[5] = p3p3_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (p3p3_M->Timing.TaskCounters.TID[2])++;
  if ((p3p3_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    p3p3_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  p3p3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void p3p3_output0(void)                /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtToFile[2];
  real_T rtb_DeadZoney;
  real_T rtb_Frontgain;
  real_T rtb_rvector[2];
  real_T tmp[5];
  int32_T i;
  int32_T i_0;
  real_T u0;
  if (rtmIsMajorTimeStep(p3p3_M)) {
    /* set solver stop time */
    if (!(p3p3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&p3p3_M->solverInfo, ((p3p3_M->Timing.clockTickH0 +
        1) * p3p3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&p3p3_M->solverInfo, ((p3p3_M->Timing.clockTick0 + 1)
        * p3p3_M->Timing.stepSize0 + p3p3_M->Timing.clockTickH0 *
        p3p3_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(p3p3_M)) {
    p3p3_M->Timing.t[0] = rtsiGetT(&p3p3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(p3p3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: p3p3/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(p3p3_DW.HILReadEncoderTimebase_Task, 1,
        &p3p3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 = p3p3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 = p3p3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZoney = p3p3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S2>/Travel: Count to rad' */
    p3p3_B.TravelCounttorad = p3p3_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    p3p3_B.Gain = p3p3_P.Gain_Gain * p3p3_B.TravelCounttorad;
  }

  /* Gain: '<S12>/Gain' incorporates:
   *  TransferFcn: '<S2>/Travel: Transfer Fcn'
   */
  p3p3_B.Gain_d = (p3p3_P.TravelTransferFcn_C * p3p3_X.TravelTransferFcn_CSTATE
                   + p3p3_P.TravelTransferFcn_D * p3p3_B.TravelCounttorad) *
    p3p3_P.Gain_Gain_l;
  if (rtmIsMajorTimeStep(p3p3_M)) {
    /* Gain: '<S2>/Pitch: Count to rad' */
    p3p3_B.PitchCounttorad = p3p3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    p3p3_B.Gain_i = p3p3_P.Gain_Gain_a * p3p3_B.PitchCounttorad;
  }

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S2>/Pitch: Transfer Fcn'
   */
  p3p3_B.Gain_b = (p3p3_P.PitchTransferFcn_C * p3p3_X.PitchTransferFcn_CSTATE +
                   p3p3_P.PitchTransferFcn_D * p3p3_B.PitchCounttorad) *
    p3p3_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(p3p3_M)) {
    /* Gain: '<S2>/Elevation: Count to rad' */
    p3p3_B.ElevationCounttorad = p3p3_P.ElevationCounttorad_Gain * rtb_DeadZoney;

    /* Sum: '<S2>/Sum' incorporates:
     *  Constant: '<S2>/offset'
     *  Gain: '<S7>/Gain'
     */
    p3p3_B.Sum = p3p3_P.Gain_Gain_lv * p3p3_B.ElevationCounttorad -
      p3p3_P.offset_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S2>/Elevation: Transfer Fcn'
   */
  p3p3_B.Gain_dg = (p3p3_P.ElevationTransferFcn_C *
                    p3p3_X.ElevationTransferFcn_CSTATE +
                    p3p3_P.ElevationTransferFcn_D * p3p3_B.ElevationCounttorad) *
    p3p3_P.Gain_Gain_n;

  /* Gain: '<Root>/deg to rad' */
  p3p3_B.degtorad[0] = p3p3_P.degtorad_Gain * p3p3_B.Gain;
  p3p3_B.degtorad[1] = p3p3_P.degtorad_Gain * p3p3_B.Gain_d;
  p3p3_B.degtorad[2] = p3p3_P.degtorad_Gain * p3p3_B.Gain_i;
  p3p3_B.degtorad[3] = p3p3_P.degtorad_Gain * p3p3_B.Gain_b;
  p3p3_B.degtorad[4] = p3p3_P.degtorad_Gain * p3p3_B.Sum;
  p3p3_B.degtorad[5] = p3p3_P.degtorad_Gain * p3p3_B.Gain_dg;

  /* RateTransition: '<S3>/Rate Transition: x' incorporates:
   *  Constant: '<S4>/Ki matrix'
   */
  if (rtmIsMajorTimeStep(p3p3_M)) {
    if (p3p3_M->Timing.RateInteraction.TID1_2) {
      p3p3_B.RateTransitionx = p3p3_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S3>/Dead Zone: x' */
    if (p3p3_B.RateTransitionx > p3p3_P.DeadZonex_End) {
      rtb_DeadZoney = p3p3_B.RateTransitionx - p3p3_P.DeadZonex_End;
    } else if (p3p3_B.RateTransitionx >= p3p3_P.DeadZonex_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney = p3p3_B.RateTransitionx - p3p3_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: x' */

    /* Gain: '<S3>/Joystick_gain_x' incorporates:
     *  Gain: '<S3>/Gain: x'
     */
    p3p3_B.Joystick_gain_x = p3p3_P.Gainx_Gain * rtb_DeadZoney *
      p3p3_P.Joystick_gain_x;

    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo FileInport1' */
    rtb_TmpSignalConversionAtToFile[0] = p3p3_B.degtorad[2];
    rtb_TmpSignalConversionAtToFile[1] = p3p3_B.Joystick_gain_x;

    /* ToFile: '<Root>/To File' */
    if (rtmIsMajorTimeStep(p3p3_M)) {
      {
        if (!(++p3p3_DW.ToFile_IWORK.Decimation % 1) &&
            (p3p3_DW.ToFile_IWORK.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) p3p3_DW.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            p3p3_DW.ToFile_IWORK.Decimation = 0;
            u[0] = p3p3_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFile[0];
            u[2] = rtb_TmpSignalConversionAtToFile[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(p3p3_M, "Error writing to MAT-file pitch.mat");
              return;
            }

            if (((++p3p3_DW.ToFile_IWORK.Count)*3)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file pitch.mat.\n");
            }
          }
        }
      }
    }

    /* RateTransition: '<S3>/Rate Transition: y' */
    if (p3p3_M->Timing.RateInteraction.TID1_2) {
      p3p3_B.RateTransitiony = p3p3_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S3>/Rate Transition: y' */

    /* DeadZone: '<S3>/Dead Zone: y' */
    if (p3p3_B.RateTransitiony > p3p3_P.DeadZoney_End) {
      rtb_DeadZoney = p3p3_B.RateTransitiony - p3p3_P.DeadZoney_End;
    } else if (p3p3_B.RateTransitiony >= p3p3_P.DeadZoney_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney = p3p3_B.RateTransitiony - p3p3_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: y' */

    /* Gain: '<S3>/Joystick_gain_y' incorporates:
     *  Gain: '<S3>/Gain: y'
     */
    p3p3_B.Joystick_gain_y = p3p3_P.Gainy_Gain * rtb_DeadZoney *
      p3p3_P.Joystick_gain_y;

    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo File1Inport1' */
    rtb_TmpSignalConversionAtToFile[0] = p3p3_B.degtorad[5];
    rtb_TmpSignalConversionAtToFile[1] = p3p3_B.Joystick_gain_y;

    /* ToFile: '<Root>/To File1' */
    if (rtmIsMajorTimeStep(p3p3_M)) {
      {
        if (!(++p3p3_DW.ToFile1_IWORK.Decimation % 1) &&
            (p3p3_DW.ToFile1_IWORK.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) p3p3_DW.ToFile1_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            p3p3_DW.ToFile1_IWORK.Decimation = 0;
            u[0] = p3p3_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFile[0];
            u[2] = rtb_TmpSignalConversionAtToFile[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(p3p3_M, "Error writing to MAT-file elevrate.mat");
              return;
            }

            if (((++p3p3_DW.ToFile1_IWORK.Count)*3)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file elevrate.mat.\n");
            }
          }
        }
      }
    }

    /* Product: '<S5>/P x r' incorporates:
     *  Constant: '<S5>/Pi'
     *  SignalConversion: '<S5>/ConcatBufferAtr vectorIn1'
     *  SignalConversion: '<S5>/ConcatBufferAtr vectorIn2'
     */
    p3p3_B.Pxr[0] = 0.0;
    p3p3_B.Pxr[0] += p3p3_P.P3_3[0] * p3p3_B.Joystick_gain_x;
    p3p3_B.Pxr[0] += p3p3_P.P3_3[2] * p3p3_B.Joystick_gain_y;
    p3p3_B.Pxr[1] = 0.0;
    p3p3_B.Pxr[1] += p3p3_P.P3_3[1] * p3p3_B.Joystick_gain_x;
    p3p3_B.Pxr[1] += p3p3_P.P3_3[3] * p3p3_B.Joystick_gain_y;
    memcpy(&p3p3_B.Kimatrix[0], &p3p3_P.K3_3[0], 10U * sizeof(real_T));
  }

  /* End of RateTransition: '<S3>/Rate Transition: x' */

  /* SignalConversion: '<S4>/TmpSignal ConversionAtKi x XInport2' incorporates:
   *  Integrator: '<S6>/int 1'
   *  Integrator: '<S6>/int 2'
   *  Product: '<S4>/Ki x X'
   */
  tmp[0] = p3p3_B.degtorad[2];
  tmp[1] = p3p3_B.degtorad[3];
  tmp[2] = p3p3_B.degtorad[5];
  tmp[3] = p3p3_X.int1_CSTATE;
  tmp[4] = p3p3_X.int2_CSTATE;

  /* Sum: '<Root>/Sum' incorporates:
   *  Product: '<S4>/Ki x X'
   */
  for (i = 0; i < 2; i++) {
    rtb_Frontgain = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      rtb_Frontgain += p3p3_B.Kimatrix[(i_0 << 1) + i] * tmp[i_0];
    }

    rtb_rvector[i] = p3p3_B.Pxr[i] - rtb_Frontgain;
  }

  /* End of Sum: '<Root>/Sum' */
  if (rtmIsMajorTimeStep(p3p3_M)) {
    /* Constant: '<S1>/Constant' */
    p3p3_B.Constant = p3p3_P.Vs_star;
  }

  /* Sum: '<S1>/Sum' */
  rtb_Frontgain = rtb_rvector[0] - p3p3_B.Constant;
  if (rtmIsMajorTimeStep(p3p3_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  u0 = (rtb_rvector[1] + rtb_Frontgain) * p3p3_P.Frontgain_Gain;

  /* Saturate: '<S2>/Front motor: Saturation' */
  if (u0 > p3p3_P.FrontmotorSaturation_UpperSat) {
    p3p3_B.FrontmotorSaturation = p3p3_P.FrontmotorSaturation_UpperSat;
  } else if (u0 < p3p3_P.FrontmotorSaturation_LowerSat) {
    p3p3_B.FrontmotorSaturation = p3p3_P.FrontmotorSaturation_LowerSat;
  } else {
    p3p3_B.FrontmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  u0 = (rtb_Frontgain - rtb_rvector[1]) * p3p3_P.Backgain_Gain;

  /* Saturate: '<S2>/Back motor: Saturation' */
  if (u0 > p3p3_P.BackmotorSaturation_UpperSat) {
    p3p3_B.BackmotorSaturation = p3p3_P.BackmotorSaturation_UpperSat;
  } else if (u0 < p3p3_P.BackmotorSaturation_LowerSat) {
    p3p3_B.BackmotorSaturation = p3p3_P.BackmotorSaturation_LowerSat;
  } else {
    p3p3_B.BackmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(p3p3_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: p3p3/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      p3p3_DW.HILWriteAnalog_Buffer[0] = p3p3_B.FrontmotorSaturation;
      p3p3_DW.HILWriteAnalog_Buffer[1] = p3p3_B.BackmotorSaturation;
      result = hil_write_analog(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILWriteAnalog_channels, 2, &p3p3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
      }
    }
  }

  /* Sum: '<S6>/Sum1' */
  p3p3_B.Sum1 = p3p3_B.degtorad[2] - p3p3_B.Joystick_gain_x;

  /* Sum: '<S6>/Sum2' */
  p3p3_B.Sum2 = p3p3_B.degtorad[5] - p3p3_B.Joystick_gain_y;
}

/* Model update function for TID0 */
void p3p3_update0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(p3p3_M)) {
    rt_ertODEUpdateContinuousStates(&p3p3_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++p3p3_M->Timing.clockTick0)) {
    ++p3p3_M->Timing.clockTickH0;
  }

  p3p3_M->Timing.t[0] = rtsiGetSolverStopTime(&p3p3_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++p3p3_M->Timing.clockTick1)) {
    ++p3p3_M->Timing.clockTickH1;
  }

  p3p3_M->Timing.t[1] = p3p3_M->Timing.clockTick1 * p3p3_M->Timing.stepSize1 +
    p3p3_M->Timing.clockTickH1 * p3p3_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void p3p3_derivatives(void)
{
  XDot_p3p3_T *_rtXdot;
  _rtXdot = ((XDot_p3p3_T *) p3p3_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += p3p3_P.TravelTransferFcn_A *
    p3p3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += p3p3_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += p3p3_P.PitchTransferFcn_A *
    p3p3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += p3p3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += p3p3_P.ElevationTransferFcn_A *
    p3p3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += p3p3_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S6>/int 1' */
  _rtXdot->int1_CSTATE = p3p3_B.Sum1;

  /* Derivatives for Integrator: '<S6>/int 2' */
  _rtXdot->int2_CSTATE = p3p3_B.Sum2;
}

/* Model output function for TID2 */
void p3p3_output2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: p3p3/Joystick/Game Controller (game_controller_block) */
  {
    if (p3p3_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(p3p3_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        p3p3_B.GameController_o4 = state.x;
        p3p3_B.GameController_o5 = state.y;
      }
    } else {
      p3p3_B.GameController_o4 = 0;
      p3p3_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void p3p3_update2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S3>/Rate Transition: x' */
  p3p3_DW.RateTransitionx_Buffer0 = p3p3_B.GameController_o4;

  /* Update for RateTransition: '<S3>/Rate Transition: y' */
  p3p3_DW.RateTransitiony_Buffer0 = p3p3_B.GameController_o5;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++p3p3_M->Timing.clockTick2)) {
    ++p3p3_M->Timing.clockTickH2;
  }

  p3p3_M->Timing.t[2] = p3p3_M->Timing.clockTick2 * p3p3_M->Timing.stepSize2 +
    p3p3_M->Timing.clockTickH2 * p3p3_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void p3p3_output(int_T tid)
{
  switch (tid) {
   case 0 :
    p3p3_output0();
    break;

   case 2 :
    p3p3_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void p3p3_update(int_T tid)
{
  switch (tid) {
   case 0 :
    p3p3_update0();
    break;

   case 2 :
    p3p3_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void p3p3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: p3p3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &p3p3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p3p3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(p3p3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p3p3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(p3p3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p3p3_M, _rt_error_message);
      return;
    }

    if ((p3p3_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (p3p3_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &p3p3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = p3p3_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &p3p3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = p3p3_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_analog_input_chan, 8U,
        &p3p3_DW.HILInitialize_AIMinimums[0], &p3p3_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if ((p3p3_P.HILInitialize_set_analog_output && !is_switching) ||
        (p3p3_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &p3p3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = p3p3_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &p3p3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = p3p3_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_analog_output_cha, 8U,
        &p3p3_DW.HILInitialize_AOMinimums[0], &p3p3_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if ((p3p3_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (p3p3_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &p3p3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = p3p3_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_analog_output_cha, 8U,
        &p3p3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if (p3p3_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &p3p3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = p3p3_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (p3p3_DW.HILInitialize_Card, p3p3_P.HILInitialize_analog_output_cha, 8U,
         &p3p3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if ((p3p3_P.HILInitialize_set_encoder_param && !is_switching) ||
        (p3p3_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &p3p3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = p3p3_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode *)
        &p3p3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if ((p3p3_P.HILInitialize_set_encoder_count && !is_switching) ||
        (p3p3_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &p3p3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = p3p3_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_encoder_channels, 8U,
        &p3p3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if ((p3p3_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (p3p3_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &p3p3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = p3p3_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &p3p3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          p3p3_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &p3p3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            p3p3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            p3p3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              p3p3_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            p3p3_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            p3p3_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              p3p3_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(p3p3_DW.HILInitialize_Card,
          &p3p3_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &p3p3_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(p3p3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(p3p3_DW.HILInitialize_Card,
          &p3p3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &p3p3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(p3p3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &p3p3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = p3p3_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &p3p3_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = p3p3_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &p3p3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = p3p3_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &p3p3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &p3p3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &p3p3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &p3p3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = p3p3_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &p3p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p3p3_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_pwm_channels, 8U,
        &p3p3_DW.HILInitialize_POSortedFreqs[0],
        &p3p3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if ((p3p3_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (p3p3_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &p3p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p3p3_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_pwm_channels, 8U, &p3p3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }

    if (p3p3_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &p3p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p3p3_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(p3p3_DW.HILInitialize_Card,
        p3p3_P.HILInitialize_pwm_channels, 8U, &p3p3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: p3p3/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(p3p3_DW.HILInitialize_Card,
      p3p3_P.HILReadEncoderTimebase_samples_,
      p3p3_P.HILReadEncoderTimebase_channels, 3,
      &p3p3_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p3p3_M, _rt_error_message);
    }
  }

  /* Start for RateTransition: '<S3>/Rate Transition: x' */
  p3p3_B.RateTransitionx = p3p3_P.RateTransitionx_X0;

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "pitch.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(p3p3_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"pitch")) {
      rtmSetErrorStatus(p3p3_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    p3p3_DW.ToFile_IWORK.Count = 0;
    p3p3_DW.ToFile_IWORK.Decimation = -1;
    p3p3_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S3>/Rate Transition: y' */
  p3p3_B.RateTransitiony = p3p3_P.RateTransitiony_X0;

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "elevrate.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(p3p3_M, "Error creating .mat file elevrate.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"elevrate")) {
      rtmSetErrorStatus(p3p3_M,
                        "Error writing mat file header to file elevrate.mat");
      return;
    }

    p3p3_DW.ToFile1_IWORK.Count = 0;
    p3p3_DW.ToFile1_IWORK.Decimation = -1;
    p3p3_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: p3p3/Joystick/Game Controller (game_controller_block) */
  {
    if (p3p3_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open(p3p3_P.GameController_ControllerNumber,
        p3p3_P.GameController_BufferSize, deadzone, saturation,
        p3p3_P.GameController_AutoCenter, 0, 1.0,
        &p3p3_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p3p3_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  p3p3_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  p3p3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  p3p3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition: x' */
  p3p3_DW.RateTransitionx_Buffer0 = p3p3_P.RateTransitionx_X0;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition: y' */
  p3p3_DW.RateTransitiony_Buffer0 = p3p3_P.RateTransitiony_X0;

  /* InitializeConditions for Integrator: '<S6>/int 1' */
  p3p3_X.int1_CSTATE = p3p3_P.int1_IC;

  /* InitializeConditions for Integrator: '<S6>/int 2' */
  p3p3_X.int2_CSTATE = p3p3_P.int2_IC;
}

/* Model terminate function */
void p3p3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: p3p3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(p3p3_DW.HILInitialize_Card);
    hil_monitor_stop_all(p3p3_DW.HILInitialize_Card);
    is_switching = false;
    if ((p3p3_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (p3p3_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &p3p3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = p3p3_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((p3p3_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (p3p3_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &p3p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p3p3_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(p3p3_DW.HILInitialize_Card
                         , p3p3_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , p3p3_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &p3p3_DW.HILInitialize_AOVoltages[0]
                         , &p3p3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(p3p3_DW.HILInitialize_Card,
            p3p3_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &p3p3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(p3p3_DW.HILInitialize_Card,
            p3p3_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &p3p3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(p3p3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(p3p3_DW.HILInitialize_Card);
    hil_monitor_delete_all(p3p3_DW.HILInitialize_Card);
    hil_close(p3p3_DW.HILInitialize_Card);
    p3p3_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) p3p3_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(p3p3_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(p3p3_M, "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, p3p3_DW.ToFile_IWORK.Count, "pitch")) {
        rtmSetErrorStatus(p3p3_M,
                          "Error writing header for pitch to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(p3p3_M, "Error closing MAT-file pitch.mat");
        return;
      }

      p3p3_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) p3p3_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevrate.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(p3p3_M, "Error closing MAT-file elevrate.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(p3p3_M, "Error reopening MAT-file elevrate.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, p3p3_DW.ToFile1_IWORK.Count, "elevrate"))
      {
        rtmSetErrorStatus(p3p3_M,
                          "Error writing header for elevrate to MAT-file elevrate.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(p3p3_M, "Error closing MAT-file elevrate.mat");
        return;
      }

      p3p3_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: p3p3/Joystick/Game Controller (game_controller_block) */
  {
    if (p3p3_P.GameController_Enabled) {
      game_controller_close(p3p3_DW.GameController_Controller);
      p3p3_DW.GameController_Controller = NULL;
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  p3p3_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  p3p3_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  p3p3_initialize();
}

void MdlTerminate(void)
{
  p3p3_terminate();
}

/* Registration function */
RT_MODEL_p3p3_T *p3p3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)p3p3_M, 0,
                sizeof(RT_MODEL_p3p3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&p3p3_M->solverInfo, &p3p3_M->Timing.simTimeStep);
    rtsiSetTPtr(&p3p3_M->solverInfo, &rtmGetTPtr(p3p3_M));
    rtsiSetStepSizePtr(&p3p3_M->solverInfo, &p3p3_M->Timing.stepSize0);
    rtsiSetdXPtr(&p3p3_M->solverInfo, &p3p3_M->ModelData.derivs);
    rtsiSetContStatesPtr(&p3p3_M->solverInfo, (real_T **)
                         &p3p3_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&p3p3_M->solverInfo, &p3p3_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&p3p3_M->solverInfo, (&rtmGetErrorStatus(p3p3_M)));
    rtsiSetRTModelPtr(&p3p3_M->solverInfo, p3p3_M);
  }

  rtsiSetSimTimeStep(&p3p3_M->solverInfo, MAJOR_TIME_STEP);
  p3p3_M->ModelData.intgData.f[0] = p3p3_M->ModelData.odeF[0];
  p3p3_M->ModelData.contStates = ((real_T *) &p3p3_X);
  rtsiSetSolverData(&p3p3_M->solverInfo, (void *)&p3p3_M->ModelData.intgData);
  rtsiSetSolverName(&p3p3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = p3p3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    p3p3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    p3p3_M->Timing.sampleTimes = (&p3p3_M->Timing.sampleTimesArray[0]);
    p3p3_M->Timing.offsetTimes = (&p3p3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    p3p3_M->Timing.sampleTimes[0] = (0.0);
    p3p3_M->Timing.sampleTimes[1] = (0.002);
    p3p3_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    p3p3_M->Timing.offsetTimes[0] = (0.0);
    p3p3_M->Timing.offsetTimes[1] = (0.0);
    p3p3_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(p3p3_M, &p3p3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = p3p3_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = p3p3_M->Timing.perTaskSampleHitsArray;
    p3p3_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    p3p3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(p3p3_M, -1);
  p3p3_M->Timing.stepSize0 = 0.002;
  p3p3_M->Timing.stepSize1 = 0.002;
  p3p3_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  p3p3_M->Sizes.checksums[0] = (2097996831U);
  p3p3_M->Sizes.checksums[1] = (3131831005U);
  p3p3_M->Sizes.checksums[2] = (2264668433U);
  p3p3_M->Sizes.checksums[3] = (1023427908U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    p3p3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(p3p3_M->extModeInfo,
      &p3p3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(p3p3_M->extModeInfo, p3p3_M->Sizes.checksums);
    rteiSetTPtr(p3p3_M->extModeInfo, rtmGetTPtr(p3p3_M));
  }

  p3p3_M->solverInfoPtr = (&p3p3_M->solverInfo);
  p3p3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&p3p3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&p3p3_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  p3p3_M->ModelData.blockIO = ((void *) &p3p3_B);

  {
    int_T i;
    for (i = 0; i < 6; i++) {
      p3p3_B.degtorad[i] = 0.0;
    }

    for (i = 0; i < 10; i++) {
      p3p3_B.Kimatrix[i] = 0.0;
    }

    p3p3_B.TravelCounttorad = 0.0;
    p3p3_B.Gain = 0.0;
    p3p3_B.Gain_d = 0.0;
    p3p3_B.PitchCounttorad = 0.0;
    p3p3_B.Gain_i = 0.0;
    p3p3_B.Gain_b = 0.0;
    p3p3_B.ElevationCounttorad = 0.0;
    p3p3_B.Sum = 0.0;
    p3p3_B.Gain_dg = 0.0;
    p3p3_B.RateTransitionx = 0.0;
    p3p3_B.Joystick_gain_x = 0.0;
    p3p3_B.RateTransitiony = 0.0;
    p3p3_B.Joystick_gain_y = 0.0;
    p3p3_B.Pxr[0] = 0.0;
    p3p3_B.Pxr[1] = 0.0;
    p3p3_B.Constant = 0.0;
    p3p3_B.FrontmotorSaturation = 0.0;
    p3p3_B.BackmotorSaturation = 0.0;
    p3p3_B.GameController_o4 = 0.0;
    p3p3_B.GameController_o5 = 0.0;
    p3p3_B.Sum1 = 0.0;
    p3p3_B.Sum2 = 0.0;
  }

  /* parameters */
  p3p3_M->ModelData.defaultParam = ((real_T *)&p3p3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &p3p3_X;
    p3p3_M->ModelData.contStates = (x);
    (void) memset((void *)&p3p3_X, 0,
                  sizeof(X_p3p3_T));
  }

  /* states (dwork) */
  p3p3_M->ModelData.dwork = ((void *) &p3p3_DW);
  (void) memset((void *)&p3p3_DW, 0,
                sizeof(DW_p3p3_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p3p3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  p3p3_DW.RateTransitionx_Buffer0 = 0.0;
  p3p3_DW.RateTransitiony_Buffer0 = 0.0;
  p3p3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  p3p3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    p3p3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  p3p3_M->Sizes.numContStates = (5);   /* Number of continuous states */
  p3p3_M->Sizes.numY = (0);            /* Number of model outputs */
  p3p3_M->Sizes.numU = (0);            /* Number of model inputs */
  p3p3_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  p3p3_M->Sizes.numSampTimes = (3);    /* Number of sample times */
  p3p3_M->Sizes.numBlocks = (65);      /* Number of blocks */
  p3p3_M->Sizes.numBlockIO = (23);     /* Number of block outputs */
  p3p3_M->Sizes.numBlockPrms = (160);  /* Sum of parameter "widths" */
  return p3p3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
