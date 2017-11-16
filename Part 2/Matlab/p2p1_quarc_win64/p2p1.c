/*
 * p2p1.c
 *
 * Code generation for model "p2p1".
 *
 * Model version              : 1.74
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat Oct 07 11:49:45 2017
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "p2p1.h"
#include "p2p1_private.h"
#include "p2p1_dt.h"

/* Block signals (auto storage) */
B_p2p1_T p2p1_B;

/* Continuous states */
X_p2p1_T p2p1_X;

/* Block states (auto storage) */
DW_p2p1_T p2p1_DW;

/* Real-time model */
RT_MODEL_p2p1_T p2p1_M_;
RT_MODEL_p2p1_T *const p2p1_M = &p2p1_M_;
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
  rtmSampleHitPtr[1] = rtmStepTask(p2p1_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(p2p1_M, 2);
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
  if (p2p1_M->Timing.TaskCounters.TID[1] == 0) {
    p2p1_M->Timing.RateInteraction.TID1_2 = (p2p1_M->Timing.TaskCounters.TID[2] ==
      0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    p2p1_M->Timing.perTaskSampleHits[5] = p2p1_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (p2p1_M->Timing.TaskCounters.TID[2])++;
  if ((p2p1_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    p2p1_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  p2p1_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void p2p1_output0(void)                /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[2];
  real_T rtb_Backgain;
  real_T rtb_Sum_p;
  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* set solver stop time */
    if (!(p2p1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&p2p1_M->solverInfo, ((p2p1_M->Timing.clockTickH0 +
        1) * p2p1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&p2p1_M->solverInfo, ((p2p1_M->Timing.clockTick0 + 1)
        * p2p1_M->Timing.stepSize0 + p2p1_M->Timing.clockTickH0 *
        p2p1_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(p2p1_M)) {
    p2p1_M->Timing.t[0] = rtsiGetT(&p2p1_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: p2p1/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(p2p1_DW.HILReadEncoderTimebase_Task, 1,
        &p2p1_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 = p2p1_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 = p2p1_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 = p2p1_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* RateTransition: '<S4>/Rate Transition: x' */
    if (p2p1_M->Timing.RateInteraction.TID1_2) {
      p2p1_B.RateTransitionx = p2p1_DW.RateTransitionx_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: x' */

    /* DeadZone: '<S4>/Dead Zone: x' */
    if (p2p1_B.RateTransitionx > p2p1_P.DeadZonex_End) {
      rtb_Sum_p = p2p1_B.RateTransitionx - p2p1_P.DeadZonex_End;
    } else if (p2p1_B.RateTransitionx >= p2p1_P.DeadZonex_Start) {
      rtb_Sum_p = 0.0;
    } else {
      rtb_Sum_p = p2p1_B.RateTransitionx - p2p1_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: x' */

    /* Gain: '<S4>/Joystick_gain_x' incorporates:
     *  Gain: '<S4>/Gain: x'
     */
    p2p1_B.Joystick_gain_x = p2p1_P.Gainx_Gain * rtb_Sum_p *
      p2p1_P.Joystick_gain_x;

    /* Gain: '<Root>/Gain' */
    p2p1_B.Gain = p2p1_P.Gain_Gain * p2p1_B.Joystick_gain_x;

    /* Gain: '<S3>/Travel: Count to rad' */
    p2p1_B.TravelCounttorad = p2p1_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    p2p1_B.Gain_p = p2p1_P.Gain_Gain_a * p2p1_B.TravelCounttorad;
  }

  /* TransferFcn: '<S3>/Travel: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += p2p1_P.TravelTransferFcn_C * p2p1_X.TravelTransferFcn_CSTATE;
  rtb_Backgain += p2p1_P.TravelTransferFcn_D * p2p1_B.TravelCounttorad;

  /* Gain: '<S12>/Gain' */
  p2p1_B.Gain_d = p2p1_P.Gain_Gain_l * rtb_Backgain;
  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* Gain: '<S3>/Pitch: Count to rad' */
    p2p1_B.PitchCounttorad = p2p1_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    p2p1_B.Gain_i = p2p1_P.Gain_Gain_ar * p2p1_B.PitchCounttorad;
  }

  /* TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += p2p1_P.PitchTransferFcn_C * p2p1_X.PitchTransferFcn_CSTATE;
  rtb_Backgain += p2p1_P.PitchTransferFcn_D * p2p1_B.PitchCounttorad;

  /* Gain: '<S10>/Gain' */
  p2p1_B.Gain_b = p2p1_P.Gain_Gain_ae * rtb_Backgain;
  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* Gain: '<S3>/Elevation: Count to rad' */
    p2p1_B.ElevationCounttorad = p2p1_P.ElevationCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o3;

    /* Sum: '<S3>/Sum' incorporates:
     *  Constant: '<S3>/offset elevation'
     *  Gain: '<S7>/Gain'
     */
    p2p1_B.Sum = p2p1_P.Gain_Gain_lv * p2p1_B.ElevationCounttorad -
      p2p1_P.offsetelevation_Value;
  }

  /* TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += p2p1_P.ElevationTransferFcn_C *
    p2p1_X.ElevationTransferFcn_CSTATE;
  rtb_Backgain += p2p1_P.ElevationTransferFcn_D * p2p1_B.ElevationCounttorad;

  /* Gain: '<S8>/Gain' */
  p2p1_B.Gain_dg = p2p1_P.Gain_Gain_n * rtb_Backgain;

  /* Gain: '<Root>/deg to rad' */
  p2p1_B.degtorad[0] = p2p1_P.degtorad_Gain * p2p1_B.Gain_p;
  p2p1_B.degtorad[1] = p2p1_P.degtorad_Gain * p2p1_B.Gain_d;
  p2p1_B.degtorad[2] = p2p1_P.degtorad_Gain * p2p1_B.Gain_i;
  p2p1_B.degtorad[3] = p2p1_P.degtorad_Gain * p2p1_B.Gain_b;
  p2p1_B.degtorad[4] = p2p1_P.degtorad_Gain * p2p1_B.Sum;
  p2p1_B.degtorad[5] = p2p1_P.degtorad_Gain * p2p1_B.Gain_dg;
  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo File1Inport1' */
    rtb_TmpSignalConversionAtToFile[0] = p2p1_B.Gain;
    rtb_TmpSignalConversionAtToFile[1] = p2p1_B.degtorad[2];

    /* ToFile: '<Root>/To File1' */
    if (rtmIsMajorTimeStep(p2p1_M)) {
      {
        if (!(++p2p1_DW.ToFile1_IWORK.Decimation % 1) &&
            (p2p1_DW.ToFile1_IWORK.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) p2p1_DW.ToFile1_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            p2p1_DW.ToFile1_IWORK.Decimation = 0;
            u[0] = p2p1_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFile[0];
            u[2] = rtb_TmpSignalConversionAtToFile[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(p2p1_M, "Error writing to MAT-file pitch.mat");
              return;
            }

            if (((++p2p1_DW.ToFile1_IWORK.Count)*3)+1 >= 100000000) {
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
  }

  /* Step: '<S5>/wait t_d sec' */
  if (p2p1_M->Timing.t[0] < p2p1_P.t_d) {
    rtb_Backgain = p2p1_P.waitt_dsec_Y0;
  } else {
    rtb_Backgain = p2p1_P.waitt_dsec_YFinal;
  }

  /* End of Step: '<S5>/wait t_d sec' */

  /* Product: '<S5>/Product' incorporates:
   *  Gain: '<S5>/Kpd'
   *  Gain: '<S5>/Kpp'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/Sum1'
   */
  p2p1_B.Product = ((p2p1_B.Gain - p2p1_B.degtorad[2]) * p2p1_P.K_pp -
                    p2p1_P.K_pd * p2p1_B.degtorad[3]) * rtb_Backgain;
  if (rtmIsMajorTimeStep(p2p1_M)) {
  }

  /* Integrator: '<S6>/Integrator'
   *
   * Regarding '<S6>/Integrator':
   *  Limited Integrator
   */
  if (p2p1_X.Integrator_CSTATE >= p2p1_P.Integrator_UpperSat ) {
    p2p1_X.Integrator_CSTATE = p2p1_P.Integrator_UpperSat;
  } else if (p2p1_X.Integrator_CSTATE <= (p2p1_P.Integrator_LowerSat) ) {
    p2p1_X.Integrator_CSTATE = (p2p1_P.Integrator_LowerSat);
  }

  rtb_Backgain = p2p1_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* Constant: '<Root>/e ref' */
    p2p1_B.eref = p2p1_P.eref_Value;
  }

  /* Sum: '<S2>/Sum' */
  rtb_Sum_p = p2p1_B.eref - p2p1_B.degtorad[4];

  /* Sum: '<S6>/Sum' incorporates:
   *  Gain: '<S6>/K_ed'
   *  Gain: '<S6>/K_ep'
   */
  p2p1_B.Sum_l = (p2p1_P.K_ep_Gain * rtb_Sum_p + rtb_Backgain) -
    p2p1_P.K_ed_Gain * p2p1_B.degtorad[5];
  if (rtmIsMajorTimeStep(p2p1_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (p2p1_B.Sum_l - p2p1_B.Product) * p2p1_P.Backgain_Gain;

  /* Gain: '<S6>/K_ei' */
  p2p1_B.K_ei = p2p1_P.K_ei_Gain * rtb_Sum_p;
  if (rtmIsMajorTimeStep(p2p1_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Sum_p = (p2p1_B.Product + p2p1_B.Sum_l) * p2p1_P.Frontgain_Gain;

  /* Saturate: '<S3>/Front motor: Saturation' */
  if (rtb_Sum_p > p2p1_P.FrontmotorSaturation_UpperSat) {
    p2p1_B.FrontmotorSaturation = p2p1_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum_p < p2p1_P.FrontmotorSaturation_LowerSat) {
    p2p1_B.FrontmotorSaturation = p2p1_P.FrontmotorSaturation_LowerSat;
  } else {
    p2p1_B.FrontmotorSaturation = rtb_Sum_p;
  }

  /* End of Saturate: '<S3>/Front motor: Saturation' */

  /* Saturate: '<S3>/Back motor: Saturation' */
  if (rtb_Backgain > p2p1_P.BackmotorSaturation_UpperSat) {
    p2p1_B.BackmotorSaturation = p2p1_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < p2p1_P.BackmotorSaturation_LowerSat) {
    p2p1_B.BackmotorSaturation = p2p1_P.BackmotorSaturation_LowerSat;
  } else {
    p2p1_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S3>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(p2p1_M)) {
    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: p2p1/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      p2p1_DW.HILWriteAnalog_Buffer[0] = p2p1_B.FrontmotorSaturation;
      p2p1_DW.HILWriteAnalog_Buffer[1] = p2p1_B.BackmotorSaturation;
      result = hil_write_analog(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILWriteAnalog_channels, 2, &p2p1_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
      }
    }

    /* RateTransition: '<S4>/Rate Transition: y' */
    if (p2p1_M->Timing.RateInteraction.TID1_2) {
      p2p1_B.RateTransitiony = p2p1_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: y' */

    /* DeadZone: '<S4>/Dead Zone: y' */
    if (p2p1_B.RateTransitiony > p2p1_P.DeadZoney_End) {
      rtb_Sum_p = p2p1_B.RateTransitiony - p2p1_P.DeadZoney_End;
    } else if (p2p1_B.RateTransitiony >= p2p1_P.DeadZoney_Start) {
      rtb_Sum_p = 0.0;
    } else {
      rtb_Sum_p = p2p1_B.RateTransitiony - p2p1_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: y' */

    /* Gain: '<S4>/Joystick_gain_y' incorporates:
     *  Gain: '<S4>/Gain: y'
     */
    p2p1_B.Joystick_gain_y = p2p1_P.Gainy_Gain * rtb_Sum_p *
      p2p1_P.Joystick_gain_y;
  }
}

/* Model update function for TID0 */
void p2p1_update0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(p2p1_M)) {
    rt_ertODEUpdateContinuousStates(&p2p1_M->solverInfo);
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
  if (!(++p2p1_M->Timing.clockTick0)) {
    ++p2p1_M->Timing.clockTickH0;
  }

  p2p1_M->Timing.t[0] = rtsiGetSolverStopTime(&p2p1_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++p2p1_M->Timing.clockTick1)) {
    ++p2p1_M->Timing.clockTickH1;
  }

  p2p1_M->Timing.t[1] = p2p1_M->Timing.clockTick1 * p2p1_M->Timing.stepSize1 +
    p2p1_M->Timing.clockTickH1 * p2p1_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void p2p1_derivatives(void)
{
  XDot_p2p1_T *_rtXdot;
  _rtXdot = ((XDot_p2p1_T *) p2p1_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += p2p1_P.TravelTransferFcn_A *
    p2p1_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += p2p1_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += p2p1_P.PitchTransferFcn_A *
    p2p1_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += p2p1_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += p2p1_P.ElevationTransferFcn_A *
    p2p1_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += p2p1_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( p2p1_X.Integrator_CSTATE <= (p2p1_P.Integrator_LowerSat) );
    usat = ( p2p1_X.Integrator_CSTATE >= p2p1_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (p2p1_B.K_ei > 0)) ||
        (usat && (p2p1_B.K_ei < 0)) ) {
      ((XDot_p2p1_T *) p2p1_M->ModelData.derivs)->Integrator_CSTATE =
        p2p1_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_p2p1_T *) p2p1_M->ModelData.derivs)->Integrator_CSTATE = 0.0;
    }
  }
}

/* Model output function for TID2 */
void p2p1_output2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: p2p1/Joystick/Game Controller (game_controller_block) */
  {
    if (p2p1_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(p2p1_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        p2p1_B.GameController_o4 = state.x;
        p2p1_B.GameController_o5 = state.y;
      }
    } else {
      p2p1_B.GameController_o4 = 0;
      p2p1_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void p2p1_update2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S4>/Rate Transition: x' */
  p2p1_DW.RateTransitionx_Buffer0 = p2p1_B.GameController_o4;

  /* Update for RateTransition: '<S4>/Rate Transition: y' */
  p2p1_DW.RateTransitiony_Buffer0 = p2p1_B.GameController_o5;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++p2p1_M->Timing.clockTick2)) {
    ++p2p1_M->Timing.clockTickH2;
  }

  p2p1_M->Timing.t[2] = p2p1_M->Timing.clockTick2 * p2p1_M->Timing.stepSize2 +
    p2p1_M->Timing.clockTickH2 * p2p1_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void p2p1_output(int_T tid)
{
  switch (tid) {
   case 0 :
    p2p1_output0();
    break;

   case 2 :
    p2p1_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void p2p1_update(int_T tid)
{
  switch (tid) {
   case 0 :
    p2p1_update0();
    break;

   case 2 :
    p2p1_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void p2p1_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: p2p1/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &p2p1_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p2p1_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(p2p1_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p2p1_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(p2p1_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p2p1_M, _rt_error_message);
      return;
    }

    if ((p2p1_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (p2p1_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &p2p1_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = p2p1_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &p2p1_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = p2p1_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_analog_input_chan, 8U,
        &p2p1_DW.HILInitialize_AIMinimums[0], &p2p1_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if ((p2p1_P.HILInitialize_set_analog_output && !is_switching) ||
        (p2p1_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &p2p1_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = p2p1_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &p2p1_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = p2p1_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_analog_output_cha, 8U,
        &p2p1_DW.HILInitialize_AOMinimums[0], &p2p1_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if ((p2p1_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (p2p1_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &p2p1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = p2p1_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_analog_output_cha, 8U,
        &p2p1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if (p2p1_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &p2p1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = p2p1_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (p2p1_DW.HILInitialize_Card, p2p1_P.HILInitialize_analog_output_cha, 8U,
         &p2p1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if ((p2p1_P.HILInitialize_set_encoder_param && !is_switching) ||
        (p2p1_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &p2p1_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = p2p1_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode *)
        &p2p1_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if ((p2p1_P.HILInitialize_set_encoder_count && !is_switching) ||
        (p2p1_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &p2p1_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = p2p1_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_encoder_channels, 8U,
        &p2p1_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if ((p2p1_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (p2p1_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &p2p1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = p2p1_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &p2p1_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          p2p1_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &p2p1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            p2p1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            p2p1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              p2p1_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            p2p1_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            p2p1_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              p2p1_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(p2p1_DW.HILInitialize_Card,
          &p2p1_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &p2p1_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(p2p1_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(p2p1_DW.HILInitialize_Card,
          &p2p1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &p2p1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(p2p1_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &p2p1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = p2p1_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &p2p1_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = p2p1_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &p2p1_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = p2p1_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &p2p1_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &p2p1_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &p2p1_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &p2p1_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = p2p1_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &p2p1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p2p1_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_pwm_channels, 8U,
        &p2p1_DW.HILInitialize_POSortedFreqs[0],
        &p2p1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if ((p2p1_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (p2p1_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &p2p1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p2p1_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_pwm_channels, 8U, &p2p1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }

    if (p2p1_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &p2p1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p2p1_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(p2p1_DW.HILInitialize_Card,
        p2p1_P.HILInitialize_pwm_channels, 8U, &p2p1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: p2p1/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(p2p1_DW.HILInitialize_Card,
      p2p1_P.HILReadEncoderTimebase_samples_,
      p2p1_P.HILReadEncoderTimebase_channels, 3,
      &p2p1_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p2p1_M, _rt_error_message);
    }
  }

  /* Start for RateTransition: '<S4>/Rate Transition: x' */
  p2p1_B.RateTransitionx = p2p1_P.RateTransitionx_X0;

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "pitch.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(p2p1_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"pitch")) {
      rtmSetErrorStatus(p2p1_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    p2p1_DW.ToFile1_IWORK.Count = 0;
    p2p1_DW.ToFile1_IWORK.Decimation = -1;
    p2p1_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S4>/Rate Transition: y' */
  p2p1_B.RateTransitiony = p2p1_P.RateTransitiony_X0;

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: p2p1/Joystick/Game Controller (game_controller_block) */
  {
    if (p2p1_P.GameController_Enabled) {
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

      result = game_controller_open(p2p1_P.GameController_ControllerNumber,
        p2p1_P.GameController_BufferSize, deadzone, saturation,
        p2p1_P.GameController_AutoCenter, 0, 1.0,
        &p2p1_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p2p1_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: x' */
  p2p1_DW.RateTransitionx_Buffer0 = p2p1_P.RateTransitionx_X0;

  /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  p2p1_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  p2p1_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  p2p1_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  p2p1_X.Integrator_CSTATE = p2p1_P.Integrator_IC;

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: y' */
  p2p1_DW.RateTransitiony_Buffer0 = p2p1_P.RateTransitiony_X0;
}

/* Model terminate function */
void p2p1_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: p2p1/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(p2p1_DW.HILInitialize_Card);
    hil_monitor_stop_all(p2p1_DW.HILInitialize_Card);
    is_switching = false;
    if ((p2p1_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (p2p1_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &p2p1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = p2p1_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((p2p1_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (p2p1_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &p2p1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = p2p1_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(p2p1_DW.HILInitialize_Card
                         , p2p1_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , p2p1_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &p2p1_DW.HILInitialize_AOVoltages[0]
                         , &p2p1_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(p2p1_DW.HILInitialize_Card,
            p2p1_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &p2p1_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(p2p1_DW.HILInitialize_Card,
            p2p1_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &p2p1_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(p2p1_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(p2p1_DW.HILInitialize_Card);
    hil_monitor_delete_all(p2p1_DW.HILInitialize_Card);
    hil_close(p2p1_DW.HILInitialize_Card);
    p2p1_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) p2p1_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(p2p1_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(p2p1_M, "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, p2p1_DW.ToFile1_IWORK.Count, "pitch")) {
        rtmSetErrorStatus(p2p1_M,
                          "Error writing header for pitch to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(p2p1_M, "Error closing MAT-file pitch.mat");
        return;
      }

      p2p1_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: p2p1/Joystick/Game Controller (game_controller_block) */
  {
    if (p2p1_P.GameController_Enabled) {
      game_controller_close(p2p1_DW.GameController_Controller);
      p2p1_DW.GameController_Controller = NULL;
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
  p2p1_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  p2p1_update(tid);
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
  p2p1_initialize();
}

void MdlTerminate(void)
{
  p2p1_terminate();
}

/* Registration function */
RT_MODEL_p2p1_T *p2p1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  p2p1_P.Integrator_UpperSat = rtInf;
  p2p1_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)p2p1_M, 0,
                sizeof(RT_MODEL_p2p1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&p2p1_M->solverInfo, &p2p1_M->Timing.simTimeStep);
    rtsiSetTPtr(&p2p1_M->solverInfo, &rtmGetTPtr(p2p1_M));
    rtsiSetStepSizePtr(&p2p1_M->solverInfo, &p2p1_M->Timing.stepSize0);
    rtsiSetdXPtr(&p2p1_M->solverInfo, &p2p1_M->ModelData.derivs);
    rtsiSetContStatesPtr(&p2p1_M->solverInfo, (real_T **)
                         &p2p1_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&p2p1_M->solverInfo, &p2p1_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&p2p1_M->solverInfo, (&rtmGetErrorStatus(p2p1_M)));
    rtsiSetRTModelPtr(&p2p1_M->solverInfo, p2p1_M);
  }

  rtsiSetSimTimeStep(&p2p1_M->solverInfo, MAJOR_TIME_STEP);
  p2p1_M->ModelData.intgData.f[0] = p2p1_M->ModelData.odeF[0];
  p2p1_M->ModelData.contStates = ((real_T *) &p2p1_X);
  rtsiSetSolverData(&p2p1_M->solverInfo, (void *)&p2p1_M->ModelData.intgData);
  rtsiSetSolverName(&p2p1_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = p2p1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    p2p1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    p2p1_M->Timing.sampleTimes = (&p2p1_M->Timing.sampleTimesArray[0]);
    p2p1_M->Timing.offsetTimes = (&p2p1_M->Timing.offsetTimesArray[0]);

    /* task periods */
    p2p1_M->Timing.sampleTimes[0] = (0.0);
    p2p1_M->Timing.sampleTimes[1] = (0.002);
    p2p1_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    p2p1_M->Timing.offsetTimes[0] = (0.0);
    p2p1_M->Timing.offsetTimes[1] = (0.0);
    p2p1_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(p2p1_M, &p2p1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = p2p1_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = p2p1_M->Timing.perTaskSampleHitsArray;
    p2p1_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    p2p1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(p2p1_M, -1);
  p2p1_M->Timing.stepSize0 = 0.002;
  p2p1_M->Timing.stepSize1 = 0.002;
  p2p1_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  p2p1_M->Sizes.checksums[0] = (2400104852U);
  p2p1_M->Sizes.checksums[1] = (2695426961U);
  p2p1_M->Sizes.checksums[2] = (1703265816U);
  p2p1_M->Sizes.checksums[3] = (932016891U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    p2p1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(p2p1_M->extModeInfo,
      &p2p1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(p2p1_M->extModeInfo, p2p1_M->Sizes.checksums);
    rteiSetTPtr(p2p1_M->extModeInfo, rtmGetTPtr(p2p1_M));
  }

  p2p1_M->solverInfoPtr = (&p2p1_M->solverInfo);
  p2p1_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&p2p1_M->solverInfo, 0.002);
  rtsiSetSolverMode(&p2p1_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  p2p1_M->ModelData.blockIO = ((void *) &p2p1_B);

  {
    int_T i;
    for (i = 0; i < 6; i++) {
      p2p1_B.degtorad[i] = 0.0;
    }

    p2p1_B.RateTransitionx = 0.0;
    p2p1_B.Joystick_gain_x = 0.0;
    p2p1_B.Gain = 0.0;
    p2p1_B.TravelCounttorad = 0.0;
    p2p1_B.Gain_p = 0.0;
    p2p1_B.Gain_d = 0.0;
    p2p1_B.PitchCounttorad = 0.0;
    p2p1_B.Gain_i = 0.0;
    p2p1_B.Gain_b = 0.0;
    p2p1_B.ElevationCounttorad = 0.0;
    p2p1_B.Sum = 0.0;
    p2p1_B.Gain_dg = 0.0;
    p2p1_B.Product = 0.0;
    p2p1_B.eref = 0.0;
    p2p1_B.Sum_l = 0.0;
    p2p1_B.K_ei = 0.0;
    p2p1_B.FrontmotorSaturation = 0.0;
    p2p1_B.BackmotorSaturation = 0.0;
    p2p1_B.RateTransitiony = 0.0;
    p2p1_B.Joystick_gain_y = 0.0;
    p2p1_B.GameController_o4 = 0.0;
    p2p1_B.GameController_o5 = 0.0;
  }

  /* parameters */
  p2p1_M->ModelData.defaultParam = ((real_T *)&p2p1_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &p2p1_X;
    p2p1_M->ModelData.contStates = (x);
    (void) memset((void *)&p2p1_X, 0,
                  sizeof(X_p2p1_T));
  }

  /* states (dwork) */
  p2p1_M->ModelData.dwork = ((void *) &p2p1_DW);
  (void) memset((void *)&p2p1_DW, 0,
                sizeof(DW_p2p1_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      p2p1_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  p2p1_DW.RateTransitionx_Buffer0 = 0.0;
  p2p1_DW.HILWriteAnalog_Buffer[0] = 0.0;
  p2p1_DW.HILWriteAnalog_Buffer[1] = 0.0;
  p2p1_DW.RateTransitiony_Buffer0 = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    p2p1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  p2p1_M->Sizes.numContStates = (4);   /* Number of continuous states */
  p2p1_M->Sizes.numY = (0);            /* Number of model outputs */
  p2p1_M->Sizes.numU = (0);            /* Number of model inputs */
  p2p1_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  p2p1_M->Sizes.numSampTimes = (3);    /* Number of sample times */
  p2p1_M->Sizes.numBlocks = (62);      /* Number of blocks */
  p2p1_M->Sizes.numBlockIO = (23);     /* Number of block outputs */
  p2p1_M->Sizes.numBlockPrms = (156);  /* Sum of parameter "widths" */
  return p2p1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
