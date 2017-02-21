/*
 * File: MGCCode_Ori.c
 *
 * Code generated for Simulink model 'MGCCode_Ori'.
 *
 * Model version                  : 1.32
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Tue Apr 22 10:12:50 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MGCCode_Ori.h"
#include "MGCCode_Ori_private.h"

/* Named constants for Chart: '<S1>/MicrogridModelManager' */
#define MGCCode_Ori_IN_AGC             ((uint8_T)1U)
#define MGCCode_Ori_IN_ActiveGrid      ((uint8_T)1U)
#define MGCCode_Ori_IN_ActiveIsland    ((uint8_T)2U)
#define MGCCode_Ori_IN_ConstPConstQ    ((uint8_T)3U)
#define MGCCode_Ori_IN_Failure         ((uint8_T)1U)
#define MGCCode_Ori_IN_GridOperation   ((uint8_T)2U)
#define MGCCode_Ori_IN_Independent     ((uint8_T)4U)
#define MGCCode_Ori_IN_Island          ((uint8_T)2U)
#define MGCCode_Ori_IN_IslandAGC       ((uint8_T)3U)
#define MGCCode_Ori_IN_IslandOperation ((uint8_T)3U)
#define MGCCode_Ori_IN_Logic           ((uint8_T)1U)
#define MGCCode_Ori_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define MGCCode_Ori_IN_ShutDown        ((uint8_T)4U)
#define MGCCode_Ori_IN_Start           ((uint8_T)5U)

const InEMSRoot MGCCode_Ori_rtZInEMSRoot = {
  Start,                               /* SystemModen */
  ConstPQ,                             /* ICEMode */
  ConstPQ,                             /* BatMode */
  ConstPQ,                             /* PVMode */
  ConstPQ,                             /* DFIG1Mode */
  ConstPQ,                             /* DFIG2Mode */
  FALSE                                /* RatioCtrlCmd */
} ;                                    /* InEMSRoot ground */

const OutEMS MGCCode_Ori_rtZOutEMS = {
  Start,                               /* SystemModen */
  ConstPQ,                             /* ICEMode */
  ConstPQ,                             /* BatMode */
  ConstPQ,                             /* PVMode */
  ConstPQ,                             /* DFIG1Mode */
  ConstPQ                              /* DFIG2Mode */
} ;                                    /* OutEMS ground */

const InEMS MGCCode_Ori_rtZInEMS = {
  Start,                               /* SystemModen */
  ConstPQ,                             /* ICEMode */
  ConstPQ,                             /* BatMode */
  ConstPQ,                             /* PVMode */
  ConstPQ,                             /* DFIG1Mode */
  ConstPQ,                             /* DFIG2Mode */
  FALSE,                               /* ICEStatus */
  FALSE,                               /* BatStatus */
  FALSE,                               /* PVStatus */
  FALSE,                               /* DFIG1Status */
  FALSE                                /* DFIG2Status */
} ;                                    /* InEMS ground */

/* Block signals (auto storage) */
BlockIO_MGCCode_Ori MGCCode_Ori_B;

/* Block states (auto storage) */
D_Work_MGCCode_Ori MGCCode_Ori_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_MGCCode_Ori MGCCode_Ori_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_MGCCode_Ori MGCCode_Ori_Y;

/* Real-time model */
RT_MODEL_MGCCode_Ori MGCCode_Ori_M_;
RT_MODEL_MGCCode_Ori *const MGCCode_Ori_M = &MGCCode_Ori_M_;

/* Forward declaration for local functions */
static Status MGCCode_Ori_status(boolean_T ICE, boolean_T DFIG1, boolean_T DFIG2,
  boolean_T PV, boolean_T Bat);
static boolean_T MGCCode_Ori_PassiveIsland(real32_T Freq);
static real32_T MGCCode_Ori_EmergencyControl(boolean_T PassiveIslandSignal,
  real32_T Pload, real32_T Pmax);
static void MGCCode_Ori_PreventiveControl(real32_T Pline, real32_T Pload,
  real32_T Pmax, real32_T *Pre_LinePowerCmd, real32_T *Pre_LoadShedding,
  real32_T *Pre_Pclear, boolean_T *Pre_CutEn);
static void MGCCode_Ori_fcn(real32_T LineP, real32_T LineQ, boolean_T
  *IslandSignal, Warning *Warning_0);
static real32_T MGCCode__IslandEmergencyControl(real32_T Freq, real32_T Pmax);
static void MGCCode_IslandPreventiveControl(real32_T Pmax, real32_T
  *Pre_LoadShedding, real32_T *Pre_Pclear, boolean_T *Pre_CutEn);
static void MGCCode_Ori_GridSync(real32_T GridFreqCmd, real32_T Freq, real32_T
  Vmeas, real32_T GridVmeas, boolean_T *SyncSignal, Warning *Warning_0);
static void MGCCode_Ori_Logic(void);
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (MGCCode_Ori_M->Timing.TaskCounters.TID[1])++;
  if ((MGCCode_Ori_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.1s, 0.0s] */
    MGCCode_Ori_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/*
 * Initial conditions for enable system:
 *    '<S2>/EnablePI1'
 *    '<S2>/EnablePI4'
 *    '<S25>/EnablePI'
 *    '<S25>/EnablePI1'
 *    '<S25>/EnablePI2'
 *    '<S25>/EnablePI3'
 *    '<S38>/EnablePI'
 *    '<S38>/EnablePI5'
 *    '<S38>/EnablePI6'
 *    '<S38>/EnablePI7'
 *    ...
 */
void MGCCode_Ori_EnablePI1_Init(real32_T rtu_I, rtDW_EnablePI1_MGCCode_Ori
  *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S10>/Integrator' */
  localDW->Integrator_DSTATE = rtu_I;
  localDW->Integrator_PrevResetState = 2;
}

/*
 * Disable for enable system:
 *    '<S2>/EnablePI1'
 *    '<S2>/EnablePI4'
 *    '<S25>/EnablePI'
 *    '<S25>/EnablePI1'
 *    '<S25>/EnablePI2'
 *    '<S25>/EnablePI3'
 *    '<S38>/EnablePI'
 *    '<S38>/EnablePI5'
 *    '<S38>/EnablePI6'
 *    '<S38>/EnablePI7'
 *    ...
 */
void MGCCode_Ori_EnablePI1_Disable(rtDW_EnablePI1_MGCCode_Ori *localDW)
{
  localDW->EnablePI1_MODE = FALSE;
}

/*
 * Start for enable system:
 *    '<S2>/EnablePI1'
 *    '<S2>/EnablePI4'
 *    '<S25>/EnablePI'
 *    '<S25>/EnablePI1'
 *    '<S25>/EnablePI2'
 *    '<S25>/EnablePI3'
 *    '<S38>/EnablePI'
 *    '<S38>/EnablePI5'
 *    '<S38>/EnablePI6'
 *    '<S38>/EnablePI7'
 *    ...
 */
void MGCCode_Ori_EnablePI1_Start(real32_T rtu_I, rtDW_EnablePI1_MGCCode_Ori
  *localDW)
{
  /* InitializeConditions for Enabled SubSystem: '<S2>/EnablePI1' */
  MGCCode_Ori_EnablePI1_Init(rtu_I, localDW);

  /* End of InitializeConditions for SubSystem: '<S2>/EnablePI1' */
}

/*
 * Output and update for enable system:
 *    '<S2>/EnablePI1'
 *    '<S2>/EnablePI4'
 *    '<S25>/EnablePI'
 *    '<S25>/EnablePI1'
 *    '<S25>/EnablePI2'
 *    '<S25>/EnablePI3'
 *    '<S38>/EnablePI'
 *    '<S38>/EnablePI5'
 *    '<S38>/EnablePI6'
 *    '<S38>/EnablePI7'
 *    ...
 */
void MGCCode_Ori_EnablePI1(int16_T rtu_0, real32_T rtu_Delata, real32_T
  rtu_RESET, real32_T rtu_I, rtB_EnablePI1_MGCCode_Ori *localB,
  rtDW_EnablePI1_MGCCode_Ori *localDW, real32_T rtp_P, real32_T
  rtp_LowerSaturationLimit, real32_T rtp_UpperSaturationLimit, real32_T rtp_I)
{
  real32_T rtb_Sum_o;
  real32_T rtb_IntegralGain2;
  real_T rtb_Sum_o_0;
  real_T rtb_Sum_o_1;
  real_T rtb_IntegralGain;

  /* Outputs for Enabled SubSystem: '<S2>/EnablePI1' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (rtu_0 > 0) {
    if (!localDW->EnablePI1_MODE) {
      MGCCode_Ori_EnablePI1_Init(rtu_I, localDW);
      localDW->EnablePI1_MODE = TRUE;
    }

    /* DiscreteIntegrator: '<S10>/Integrator' */
    if (((rtu_RESET > 0.0F) && (localDW->Integrator_PrevResetState <= 0)) ||
        ((rtu_RESET <= 0.0F) && (localDW->Integrator_PrevResetState == 1))) {
      localDW->Integrator_DSTATE = rtu_I;
    }

    /* Sum: '<S10>/Sum' incorporates:
     *  DiscreteIntegrator: '<S10>/Integrator'
     *  Gain: '<S10>/Proportional Gain2'
     */
    rtb_Sum_o = rtp_P * rtu_Delata + localDW->Integrator_DSTATE;

    /* Gain: '<S10>/Integral Gain2' */
    rtb_IntegralGain2 = rtp_I * rtu_Delata;

    /* Saturate: '<S10>/Saturation' */
    if (rtb_Sum_o >= rtp_UpperSaturationLimit) {
      localB->Saturation = rtp_UpperSaturationLimit;
    } else if (rtb_Sum_o <= rtp_LowerSaturationLimit) {
      localB->Saturation = rtp_LowerSaturationLimit;
    } else {
      localB->Saturation = rtb_Sum_o;
    }

    /* End of Saturate: '<S10>/Saturation' */

    /* DeadZone: '<S17>/DeadZone' incorporates:
     *  DataTypeConversion: '<S17>/DataTypeConv1'
     */
    if (rtb_Sum_o > rtp_UpperSaturationLimit) {
      rtb_Sum_o_0 = (real_T)rtb_Sum_o - (real_T)rtp_UpperSaturationLimit;
    } else if (rtb_Sum_o >= rtp_LowerSaturationLimit) {
      rtb_Sum_o_0 = 0.0;
    } else {
      rtb_Sum_o_0 = (real_T)rtb_Sum_o - (real_T)rtp_LowerSaturationLimit;
    }

    /* End of DeadZone: '<S17>/DeadZone' */

    /* Signum: '<S17>/SignPreSat' incorporates:
     *  DataTypeConversion: '<S17>/DataTypeConv1'
     */
    if (rtb_Sum_o < 0.0F) {
      rtb_Sum_o_1 = -1.0;
    } else if (rtb_Sum_o > 0.0F) {
      rtb_Sum_o_1 = 1.0;
    } else if (rtb_Sum_o == 0.0F) {
      rtb_Sum_o_1 = 0.0;
    } else {
      rtb_Sum_o_1 = (real_T)rtb_Sum_o;
    }

    /* Signum: '<S17>/SignPreIntegrator' incorporates:
     *  DataTypeConversion: '<S17>/DataTypeConv2'
     */
    if (rtb_IntegralGain2 < 0.0F) {
      rtb_IntegralGain = -1.0;
    } else if (rtb_IntegralGain2 > 0.0F) {
      rtb_IntegralGain = 1.0;
    } else if (rtb_IntegralGain2 == 0.0F) {
      rtb_IntegralGain = 0.0;
    } else {
      rtb_IntegralGain = (real_T)rtb_IntegralGain2;
    }

    /* Switch: '<S10>/Switch' incorporates:
     *  Constant: '<S10>/Constant'
     *  Constant: '<S17>/Constant'
     *  Logic: '<S17>/AND'
     *  RelationalOperator: '<S17>/Equal'
     *  RelationalOperator: '<S17>/NotEqual'
     *  Signum: '<S17>/SignPreIntegrator'
     *  Signum: '<S17>/SignPreSat'
     */
    if ((0.0 != rtb_Sum_o_0) && (rtb_Sum_o_1 == rtb_IntegralGain)) {
      rtb_IntegralGain2 = 0.0F;
    }

    /* End of Switch: '<S10>/Switch' */

    /* Update for DiscreteIntegrator: '<S10>/Integrator' */
    localDW->Integrator_DSTATE += 0.05F * rtb_IntegralGain2;
    if (rtu_RESET > 0.0F) {
      localDW->Integrator_PrevResetState = 1;
    } else if (rtu_RESET < 0.0F) {
      localDW->Integrator_PrevResetState = -1;
    } else if (rtu_RESET == 0.0F) {
      localDW->Integrator_PrevResetState = 0;
    } else {
      localDW->Integrator_PrevResetState = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S10>/Integrator' */
  } else {
    if (localDW->EnablePI1_MODE) {
      MGCCode_Ori_EnablePI1_Disable(localDW);
    }
  }

  /* End of Outputs for SubSystem: '<S2>/EnablePI1' */
}

/*
 * Initial conditions for enable system:
 *    '<S2>/EnablePI5'
 *    '<S2>/EnablePI8'
 */
void MGCCode_Ori_EnablePI5_Init(real32_T rtu_RESET, rtDW_EnablePI5_MGCCode_Ori
  *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S14>/Integrator' */
  localDW->Integrator_DSTATE = rtu_RESET;
  localDW->Integrator_PrevResetState = 2;
}

/*
 * Disable for enable system:
 *    '<S2>/EnablePI5'
 *    '<S2>/EnablePI8'
 */
void MGCCode_Ori_EnablePI5_Disable(rtDW_EnablePI5_MGCCode_Ori *localDW)
{
  localDW->EnablePI5_MODE = FALSE;
}

/*
 * Start for enable system:
 *    '<S2>/EnablePI5'
 *    '<S2>/EnablePI8'
 */
void MGCCode_Ori_EnablePI5_Start(real32_T rtu_RESET, rtDW_EnablePI5_MGCCode_Ori *
  localDW)
{
  /* InitializeConditions for Enabled SubSystem: '<S2>/EnablePI5' */
  MGCCode_Ori_EnablePI5_Init(rtu_RESET, localDW);

  /* End of InitializeConditions for SubSystem: '<S2>/EnablePI5' */
}

/*
 * Output and update for enable system:
 *    '<S2>/EnablePI5'
 *    '<S2>/EnablePI8'
 */
void MGCCode_Ori_EnablePI5(int16_T rtu_0, real32_T rtu_Delata, real32_T
  rtu_RESET, rtB_EnablePI5_MGCCode_Ori *localB, rtDW_EnablePI5_MGCCode_Ori
  *localDW, real32_T rtp_P, real32_T rtp_LowerSaturationLimit, real32_T
  rtp_UpperSaturationLimit, real32_T rtp_I)
{
  real32_T rtb_Sum_a;
  real32_T rtb_IntegralGain2_f;
  real_T rtb_Sum_a_0;
  real_T rtb_Sum_a_1;
  real_T rtb_IntegralGain2_f_0;

  /* Outputs for Enabled SubSystem: '<S2>/EnablePI5' incorporates:
   *  EnablePort: '<S14>/Enable'
   */
  if (rtu_0 > 0) {
    if (!localDW->EnablePI5_MODE) {
      MGCCode_Ori_EnablePI5_Init(rtu_RESET, localDW);
      localDW->EnablePI5_MODE = TRUE;
    }

    /* DiscreteIntegrator: '<S14>/Integrator' */
    if (((rtu_RESET > 0.0F) && (localDW->Integrator_PrevResetState <= 0)) ||
        ((rtu_RESET <= 0.0F) && (localDW->Integrator_PrevResetState == 1))) {
      localDW->Integrator_DSTATE = rtu_RESET;
    }

    /* Sum: '<S14>/Sum' incorporates:
     *  DiscreteIntegrator: '<S14>/Integrator'
     *  Gain: '<S14>/Proportional Gain2'
     */
    rtb_Sum_a = rtp_P * rtu_Delata + localDW->Integrator_DSTATE;

    /* Gain: '<S14>/Integral Gain2' */
    rtb_IntegralGain2_f = rtp_I * rtu_Delata;

    /* Saturate: '<S14>/Saturation' */
    if (rtb_Sum_a >= rtp_UpperSaturationLimit) {
      localB->Saturation = rtp_UpperSaturationLimit;
    } else if (rtb_Sum_a <= rtp_LowerSaturationLimit) {
      localB->Saturation = rtp_LowerSaturationLimit;
    } else {
      localB->Saturation = rtb_Sum_a;
    }

    /* End of Saturate: '<S14>/Saturation' */

    /* DeadZone: '<S21>/DeadZone' incorporates:
     *  DataTypeConversion: '<S21>/DataTypeConv1'
     */
    if (rtb_Sum_a > rtp_UpperSaturationLimit) {
      rtb_Sum_a_0 = (real_T)rtb_Sum_a - (real_T)rtp_UpperSaturationLimit;
    } else if (rtb_Sum_a >= rtp_LowerSaturationLimit) {
      rtb_Sum_a_0 = 0.0;
    } else {
      rtb_Sum_a_0 = (real_T)rtb_Sum_a - (real_T)rtp_LowerSaturationLimit;
    }

    /* End of DeadZone: '<S21>/DeadZone' */

    /* Signum: '<S21>/SignPreSat' incorporates:
     *  DataTypeConversion: '<S21>/DataTypeConv1'
     */
    if (rtb_Sum_a < 0.0F) {
      rtb_Sum_a_1 = -1.0;
    } else if (rtb_Sum_a > 0.0F) {
      rtb_Sum_a_1 = 1.0;
    } else if (rtb_Sum_a == 0.0F) {
      rtb_Sum_a_1 = 0.0;
    } else {
      rtb_Sum_a_1 = (real_T)rtb_Sum_a;
    }

    /* Signum: '<S21>/SignPreIntegrator' incorporates:
     *  DataTypeConversion: '<S21>/DataTypeConv2'
     */
    if (rtb_IntegralGain2_f < 0.0F) {
      rtb_IntegralGain2_f_0 = -1.0;
    } else if (rtb_IntegralGain2_f > 0.0F) {
      rtb_IntegralGain2_f_0 = 1.0;
    } else if (rtb_IntegralGain2_f == 0.0F) {
      rtb_IntegralGain2_f_0 = 0.0;
    } else {
      rtb_IntegralGain2_f_0 = (real_T)rtb_IntegralGain2_f;
    }

    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S14>/Constant'
     *  Constant: '<S21>/Constant'
     *  Logic: '<S21>/AND'
     *  RelationalOperator: '<S21>/Equal'
     *  RelationalOperator: '<S21>/NotEqual'
     *  Signum: '<S21>/SignPreIntegrator'
     *  Signum: '<S21>/SignPreSat'
     */
    if ((0.0 != rtb_Sum_a_0) && (rtb_Sum_a_1 == rtb_IntegralGain2_f_0)) {
      rtb_IntegralGain2_f = 0.0F;
    }

    /* End of Switch: '<S14>/Switch' */

    /* Update for DiscreteIntegrator: '<S14>/Integrator' */
    localDW->Integrator_DSTATE += 0.05F * rtb_IntegralGain2_f;
    if (rtu_RESET > 0.0F) {
      localDW->Integrator_PrevResetState = 1;
    } else if (rtu_RESET < 0.0F) {
      localDW->Integrator_PrevResetState = -1;
    } else if (rtu_RESET == 0.0F) {
      localDW->Integrator_PrevResetState = 0;
    } else {
      localDW->Integrator_PrevResetState = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S14>/Integrator' */
  } else {
    if (localDW->EnablePI5_MODE) {
      MGCCode_Ori_EnablePI5_Disable(localDW);
    }
  }

  /* End of Outputs for SubSystem: '<S2>/EnablePI5' */
}

/*
 * Output and update for atomic system:
 *    '<S25>/ModeSelect'
 *    '<S38>/ModeSelect1'
 *    '<S50>/ModeSelect'
 */
void MGCCode_Ori_ModeSelect(SystemMode rtu_SysMode, GenMode rtu_GenerationMode,
  rtB_ModeSelect_MGCCode_Ori *localB)
{
  /* MATLAB Function 'MGCC1/BatControl2/PowerRegulator/ModeSelect': '<S31>:1' */
  if (rtu_SysMode == Start) {
    /* '<S31>:1:3' */
    /* '<S31>:1:4' */
    localB->AGCInnerEnable = 0;

    /* '<S31>:1:5' */
    localB->ConstPEnable = 0;

    /* '<S31>:1:6' */
    localB->AVCInnerEnable = 0;

    /* '<S31>:1:7' */
    localB->ConstQEnable = 0;

    /* '<S31>:1:8' */
    localB->PCtrlSwitch = 0;

    /* '<S31>:1:9' */
    localB->QCtrlSwitch = 0;
  } else if (rtu_GenerationMode == ConstPQ) {
    /* '<S31>:1:10' */
    /* ConstP ConstQ */
    /* '<S31>:1:11' */
    localB->AGCInnerEnable = 0;

    /* '<S31>:1:12' */
    localB->ConstPEnable = 1;

    /* '<S31>:1:13' */
    localB->AVCInnerEnable = 0;

    /* '<S31>:1:14' */
    localB->ConstQEnable = 1;

    /* '<S31>:1:15' */
    localB->PCtrlSwitch = 0;

    /* '<S31>:1:16' */
    localB->QCtrlSwitch = 0;
  } else if (rtu_GenerationMode == ConstPAVC) {
    /* '<S31>:1:17' */
    /* ConstP AVC */
    /* '<S31>:1:18' */
    localB->AGCInnerEnable = 0;

    /* '<S31>:1:19' */
    localB->ConstPEnable = 1;

    /* '<S31>:1:20' */
    localB->AVCInnerEnable = 1;

    /* '<S31>:1:21' */
    localB->ConstQEnable = 0;

    /* '<S31>:1:22' */
    localB->PCtrlSwitch = 0;

    /* '<S31>:1:23' */
    localB->QCtrlSwitch = 1;
  } else if (rtu_GenerationMode == AGCConstQ) {
    /* '<S31>:1:24' */
    /* AGC ConstQ */
    /* '<S31>:1:25' */
    localB->AGCInnerEnable = 1;

    /* '<S31>:1:26' */
    localB->ConstPEnable = 0;

    /* '<S31>:1:27' */
    localB->AVCInnerEnable = 0;

    /* '<S31>:1:28' */
    localB->ConstQEnable = 1;

    /* '<S31>:1:29' */
    localB->PCtrlSwitch = 1;

    /* '<S31>:1:30' */
    localB->QCtrlSwitch = 0;
  } else if (rtu_GenerationMode == AGCAVC) {
    /* '<S31>:1:31' */
    /* AGC AVC */
    /* '<S31>:1:32' */
    localB->AGCInnerEnable = 1;

    /* '<S31>:1:33' */
    localB->ConstPEnable = 0;

    /* '<S31>:1:34' */
    localB->AVCInnerEnable = 1;

    /* '<S31>:1:35' */
    localB->ConstQEnable = 0;

    /* '<S31>:1:36' */
    localB->PCtrlSwitch = 1;

    /* '<S31>:1:37' */
    localB->QCtrlSwitch = 1;
  } else {
    /* '<S31>:1:39' */
    localB->AGCInnerEnable = 0;

    /* '<S31>:1:40' */
    localB->ConstPEnable = 0;

    /* '<S31>:1:41' */
    localB->AVCInnerEnable = 0;

    /* '<S31>:1:42' */
    localB->ConstQEnable = 0;

    /* '<S31>:1:43' */
    localB->PCtrlSwitch = 0;

    /* '<S31>:1:44' */
    localB->QCtrlSwitch = 0;
  }
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static Status MGCCode_Ori_status(boolean_T ICE, boolean_T DFIG1, boolean_T DFIG2,
  boolean_T PV, boolean_T Bat)
{
  Status Status_0;
  boolean_T aVarTruthTableCondition;

  /* Truth Table Function 'status': '<S6>:999' */
  Status_0 = All;

  /* Condition '#1': '<S6>:1246' */
  /*  ICE is online  */
  aVarTruthTableCondition = (ICE == 1);

  /* Condition '#2': '<S6>:1248' */
  /*  DFIG1 is online  */
  /* Condition '#3': '<S6>:1250' */
  /*  DFIG2 is online  */
  /* Condition '#4': '<S6>:1252' */
  /*  Bat is online  */
  /* Condition '#5': '<S6>:1254' */
  /*  PV is online  */
  if (!(aVarTruthTableCondition && DFIG1 && DFIG2 && Bat && PV)) {
    if (aVarTruthTableCondition && DFIG1 && DFIG2 && Bat && (!PV)) {
      /* Decision 'D2': '<S6>:1262' */
      /* Action '2': '<S6>:1264' */
      /*  'ID1D2B':  */
      Status_0 = ID1D2B;
    } else if (aVarTruthTableCondition && DFIG1 && DFIG2 && (!Bat) && PV) {
      /* Decision 'D3': '<S6>:1268' */
      /* Action '3': '<S6>:1270' */
      /*  'ID1D2P':  */
      Status_0 = ID1D2P;
    } else if (aVarTruthTableCondition && DFIG1 && DFIG2 && (!Bat) && (!PV)) {
      /* Decision 'D4': '<S6>:1274' */
      /* Action '4': '<S6>:1276' */
      /*  'ID1D2':  */
      Status_0 = ID1D2;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && Bat && PV) {
      /* Decision 'D5': '<S6>:1280' */
      /* Action '5': '<S6>:1282' */
      /*  'ID1BP':  */
      Status_0 = ID1BP;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && Bat && (!PV)) {
      /* Decision 'D6': '<S6>:1286' */
      /* Action '6': '<S6>:1288' */
      /*  'ID1B':  */
      Status_0 = ID1B;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && (!Bat) && PV) {
      /* Decision 'D7': '<S6>:1292' */
      /* Action '7': '<S6>:1294' */
      /*  'ID1P':  */
      Status_0 = ID1P;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && (!Bat) && (!PV))
    {
      /* Decision 'D8': '<S6>:1298' */
      /* Action '8': '<S6>:1300' */
      /*  'ID1':  */
      Status_0 = ID1;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && Bat && PV) {
      /* Decision 'D9': '<S6>:1304' */
      /* Action '9': '<S6>:1306' */
      /*  'ID2BP':  */
      Status_0 = ID2BP;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && Bat && (!PV)) {
      /* Decision 'D10': '<S6>:1310' */
      /* Action '10': '<S6>:1312' */
      /*  'ID2B':  */
      Status_0 = ID2B;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && (!Bat) && PV) {
      /* Decision 'D11': '<S6>:1316' */
      /* Action '11': '<S6>:1318' */
      /*  'ID2P':  */
      Status_0 = ID2P;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && (!Bat) && (!PV))
    {
      /* Decision 'D12': '<S6>:1322' */
      /* Action '12': '<S6>:1324' */
      /*  'ID2':  */
      Status_0 = ID2;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && Bat && PV) {
      /* Decision 'D13': '<S6>:1328' */
      /* Action '13': '<S6>:1330' */
      /*  'IBP':  */
      Status_0 = IBP;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && Bat && (!PV))
    {
      /* Decision 'D14': '<S6>:1334' */
      /* Action '14': '<S6>:1336' */
      /*  'IB':  */
      Status_0 = IB;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && (!Bat) && PV)
    {
      /* Decision 'D15': '<S6>:1340' */
      /* Action '15': '<S6>:1342' */
      /*  'IP':  */
      Status_0 = IP;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && (!Bat) && (!PV))
    {
      /* Decision 'D16': '<S6>:1346' */
      /* Action '16': '<S6>:1348' */
      /*  'I':  */
      Status_0 = I;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && Bat && PV) {
      /* Decision 'D17': '<S6>:1352' */
      /* Action '17': '<S6>:1354' */
      /*  'D1D2BP':  */
      Status_0 = D1D2BP;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && Bat && (!PV)) {
      /* Decision 'D18': '<S6>:1358' */
      /* Action '18': '<S6>:1360' */
      /*  'D1D2B':  */
      Status_0 = D1D2B;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && (!Bat) && PV) {
      /* Decision 'D19': '<S6>:1364' */
      /* Action '19': '<S6>:1366' */
      /*  'D1D2P':  */
      Status_0 = D1D2P;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && (!Bat) && (!PV))
    {
      /* Decision 'D20': '<S6>:1370' */
      /* Action '20': '<S6>:1372' */
      /*  'D1D2':  */
      Status_0 = D1D2;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && Bat && PV) {
      /* Decision 'D21': '<S6>:1376' */
      /* Action '21': '<S6>:1378' */
      /*  'D1BP':  */
      Status_0 = D1BP;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && Bat && (!PV))
    {
      /* Decision 'D22': '<S6>:1382' */
      /* Action '22': '<S6>:1384' */
      /*  'D1B':  */
      Status_0 = D1B;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && (!Bat) && PV)
    {
      /* Decision 'D23': '<S6>:1388' */
      /* Action '23': '<S6>:1390' */
      /*  'D1P':  */
      Status_0 = D1P;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && (!Bat) && (!PV))
    {
      /* Decision 'D24': '<S6>:1394' */
      /* Action '24': '<S6>:1396' */
      /*  'D1':  */
      Status_0 = D1;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && Bat && PV) {
      /* Decision 'D25': '<S6>:1400' */
      /* Action '25': '<S6>:1402' */
      /*  'D2BP':  */
      Status_0 = D2BP;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && Bat && (!PV))
    {
      /* Decision 'D26': '<S6>:1406' */
      /* Action '26': '<S6>:1408' */
      /*  'D2B':  */
      Status_0 = D2B;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && (!Bat) && PV)
    {
      /* Decision 'D27': '<S6>:1412' */
      /* Action '27': '<S6>:1414' */
      /*  'D2P':  */
      Status_0 = D2P;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && (!Bat) && (!PV))
    {
      /* Decision 'D28': '<S6>:1418' */
      /* Action '28': '<S6>:1420' */
      /*  'D2':  */
      Status_0 = D2;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && Bat && PV)
    {
      /* Decision 'D29': '<S6>:1424' */
      /* Action '29': '<S6>:1426' */
      /*  'BP':  */
      Status_0 = BP;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && Bat && (!PV))
    {
      /* Decision 'D30': '<S6>:1430' */
      /* Action '30': '<S6>:1432' */
      /*  'B':  */
      Status_0 = B;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && (!Bat) &&
               PV) {
      /* Decision 'D31': '<S6>:1436' */
      /* Action '31': '<S6>:1438' */
      /*  'P':  */
      Status_0 = P;
    } else {
      if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && (!Bat) && (!PV))
      {
        /* Decision 'D32': '<S6>:1442' */
        /* Action '32': '<S6>:1444' */
        /*  'Fail':  */
        Status_0 = Fail;
      }
    }
  } else {
    /* Decision 'D1': '<S6>:1256' */
    /* Action '1': '<S6>:1258' */
    /*  'All':  */
  }

  return Status_0;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static boolean_T MGCCode_Ori_PassiveIsland(real32_T Freq)
{
  boolean_T PassiveIslandSignal;

  /* MATLAB Function 'PassiveIsland': '<S6>:1463' */
  if (((real_T)Freq <= 50.1) && ((real_T)Freq >= 49.9)) {
    /* '<S6>:1463:2' */
    /* '<S6>:1463:3' */
    MGCCode_Ori_DWork.count = 0.0F;
  } else if ((((real_T)Freq > 50.1) && (Freq <= 50.5F)) || ((Freq >= 49.5F) &&
              ((real_T)Freq < 49.9))) {
    /* '<S6>:1463:4' */
    /* '<S6>:1463:5' */
    MGCCode_Ori_DWork.count++;
  } else if (((Freq > 50.5F) && (Freq <= 51.0F)) || ((Freq >= 49.0F) && (Freq <
               49.5F))) {
    /* '<S6>:1463:6' */
    /* '<S6>:1463:7' */
    MGCCode_Ori_DWork.count += 10.0F;
  } else {
    /* '<S6>:1463:9' */
    MGCCode_Ori_DWork.count += 50.0F;
  }

  if (MGCCode_Ori_DWork.count >= 50.0F) {
    /* '<S6>:1463:12' */
    /* '<S6>:1463:13' */
    PassiveIslandSignal = TRUE;
  } else {
    /* '<S6>:1463:15' */
    PassiveIslandSignal = FALSE;
  }

  return PassiveIslandSignal;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static real32_T MGCCode_Ori_EmergencyControl(boolean_T PassiveIslandSignal,
  real32_T Pload, real32_T Pmax)
{
  real32_T E_Pclear;

  /* MATLAB Function 'EmergencyControl': '<S6>:1460' */
  /* % */
  /*  函数名 ：EmergencyControl */
  /*  函数功能描述 ：实现紧急控制 */
  /*  函数参数 ：PCC点电压，频率，联络线功率，系统等效ratio值，风机转速， */
  /*  函数返回值 ：系统运行信息，需要切负荷的值，强制孤网信号，运行方式的调整 */
  /*  作者 ：Zhang Leiqi */
  /*  函数创建日期 ：2013.5.30 */
  /*  函数修改日期 ： */
  /*  修改人 ： */
  /*  修改原因 ： */
  /*  版本 ：1.0 */
  /*  历史版本 ：  */
  /* 底层连切不成功时，中央控制器切 */
  /* % 被动孤网 */
  if (PassiveIslandSignal == 1) {
    /* '<S6>:1460:18' */
    /* '<S6>:1460:19' */
    E_Pclear = Pmax * MGCCode_Ori_P.GridParam.EmergencyTotalRatioUp - Pload;
    if (E_Pclear <= 0.0F) {
      /* '<S6>:1460:20' */
      /* '<S6>:1460:21' */
      E_Pclear = 0.0F;
    }
  } else {
    /* '<S6>:1460:23' */
    E_Pclear = 0.0F;
  }

  /* % 外网故障 */
  return E_Pclear;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_Ori_PreventiveControl(real32_T Pline, real32_T Pload,
  real32_T Pmax, real32_T *Pre_LinePowerCmd, real32_T *Pre_LoadShedding,
  real32_T *Pre_Pclear, boolean_T *Pre_CutEn)
{
  /* MATLAB Function 'PreventiveControl': '<S6>:1450' */
  /* % */
  /*  函数名 ：PreventiveControl */
  /*  函数功能描述 ：实现预防控制 */
  /*  函数参数 ：PCC点电压，频率，联络线功率，系统等效ratio值，风机转速， */
  /*  函数返回值 ：系统运行信息，需要切负荷的值，连切使能信号，运行方式的调整 */
  /*  作者 ：Zhang Leiqi */
  /*  函数创建日期 ：2013.5.30 */
  /*  函数修改日期 ： */
  /*  修改人 ： */
  /*  修改原因 ： */
  /*  版本 ：1.0 */
  /*  历史版本 ： */
  /* % */
  /* 几条原则 */
  /* 以Pmax作为基值 */
  /* 控制Pload的值在GridParam.PreventiveLoadRatioUp(如1.5)以下 */
  /* 控制Pline的绝对值GridParam.PreventiveLineRationUp(如0.4)以下 */
  /* 连切使能时，将切载量和使能指令发到下层控制器 */
  /* % 系统外送功率 */
  if (Pline >= 0.0F) {
    /* '<S6>:1450:23' */
    /* '<S6>:1450:24' */
    *Pre_LinePowerCmd = Pmax * MGCCode_Ori_P.GridParam.PreventiveLineRatioUp;

    /* Pline - Pmax*GridPreventive.LineRatioUp;  */
    /* '<S6>:1450:25' */
    *Pre_LoadShedding = 0.0F;

    /* '<S6>:1450:26' */
    *Pre_Pclear = 0.0F;

    /* '<S6>:1450:27' */
    *Pre_CutEn = FALSE;

    /* % 电网内送功率 */
  } else {
    /*  Pre_LinePowerCmd = - Pmax * GridPreventive.LineRatioUp %single(1e16); */
    /* '<S6>:1450:31' */
    *Pre_LinePowerCmd = -1.0E+16F;

    /* '<S6>:1450:32' */
    *Pre_LoadShedding = Pload - MGCCode_Ori_P.GridParam.PreventiveLoadRatioUp *
      Pmax;
    if (*Pre_LoadShedding <= 0.0F) {
      /* '<S6>:1450:33' */
      /* '<S6>:1450:34' */
      *Pre_LoadShedding = 0.0F;
    }

    /* '<S6>:1450:36' */
    *Pre_Pclear = (Pload - Pmax * MGCCode_Ori_P.GridParam.PreventiveTotalRatioUp)
      - *Pre_LoadShedding;
    if (*Pre_Pclear <= 0.0F) {
      /* '<S6>:1450:37' */
      /* '<S6>:1450:38' */
      *Pre_Pclear = 0.0F;

      /* '<S6>:1450:39' */
      *Pre_CutEn = FALSE;
    } else {
      /* '<S6>:1450:41' */
      *Pre_CutEn = TRUE;
    }
  }

  /* % 风机转速控制 */
  /* % 电池SOC过低 */
  /* % 系统等效ratio过高 */
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_Ori_fcn(real32_T LineP, real32_T LineQ, boolean_T
  *IslandSignal, Warning *Warning_0)
{
  /* Graphical Function 'fcn': '<S6>:292' */
  *IslandSignal = FALSE;
  *Warning_0 = None;

  /* Transition: '<S6>:297' */
  if (((real_T)(real32_T)fabs(LineP / MGCCode_Ori_P.Base.LineP) <= 0.2) &&
      ((real_T)(real32_T)fabs(LineQ / MGCCode_Ori_P.Base.LineQ) <= 0.2)) {
    /* Transition: '<S6>:301' */
    MGCCode_Ori_DWork.IslandCount++;
    if (MGCCode_Ori_DWork.IslandCount >= 100.0F) {
      /* Transition: '<S6>:307' */
      *IslandSignal = TRUE;
    } else {
      /* Transition: '<S6>:1227' */
    }
  } else {
    /* Transition: '<S6>:300' */
    MGCCode_Ori_DWork.IslandFailCount++;
    MGCCode_Ori_DWork.IslandCount = 0.0F;
    if (MGCCode_Ori_DWork.IslandFailCount >= 100000.0F) {
      /* Transition: '<S6>:306' */
      *Warning_0 = IslandFail;
    } else {
      /* Transition: '<S6>:1226' */
    }
  }
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static real32_T MGCCode__IslandEmergencyControl(real32_T Freq, real32_T Pmax)
{
  real32_T E_Pclear;

  /* MATLAB Function 'IslandEmergencyControl': '<S6>:1504' */
  /* % */
  /*  函数名 ：EmergencyControl */
  /*  函数功能描述 ：实现紧急控制 */
  /*  函数参数 ：PCC点电压，频率，联络线功率，系统等效ratio值，风机转速， */
  /*  函数返回值 ：系统运行信息，需要切负荷的值，强制孤网信号，运行方式的调整 */
  /*  作者 ：Zhang Leiqi */
  /*  函数创建日期 ：2013.5.30 */
  /*  函数修改日期 ： */
  /*  修改人 ： */
  /*  修改原因 ： */
  /*  版本 ：1.0 */
  /*  历史版本 ：  */
  /* % 紧急控制，根据低频切载 */
  if (Freq <= MGCCode_Ori_P.IslandParam.Stage3Freq) {
    /* '<S6>:1504:16' */
    /* '<S6>:1504:17' */
    E_Pclear = MGCCode_Ori_P.IslandParam.Stage3Cutting * Pmax;
  } else if (Freq <= MGCCode_Ori_P.IslandParam.Stage2Freq) {
    /* '<S6>:1504:18' */
    /* '<S6>:1504:19' */
    E_Pclear = MGCCode_Ori_P.IslandParam.Stage2Cutting * Pmax;
  } else if (Freq <= MGCCode_Ori_P.IslandParam.Stage3Freq) {
    /* '<S6>:1504:20' */
    /* '<S6>:1504:21' */
    E_Pclear = MGCCode_Ori_P.IslandParam.Stage3Cutting * Pmax;
  } else {
    /* '<S6>:1504:23' */
    E_Pclear = 0.0F;
  }

  /* % */
  return E_Pclear;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_IslandPreventiveControl(real32_T Pmax, real32_T
  *Pre_LoadShedding, real32_T *Pre_Pclear, boolean_T *Pre_CutEn)
{
  /* MATLAB Function 'IslandPreventiveControl': '<S6>:1499' */
  /* % */
  /*  函数名 ：IslandPreventiveControl */
  /*  函数功能描述 ：实现孤网预防控制 */
  /*  函数参数 ：系统同频率，系统负荷，系统容量 */
  /*  函数返回值 ：系统运行信息，需要切负荷的值，连切使能信号，运行方式的调整 */
  /*  作者 ：Zhang Leiqi */
  /*  函数创建日期 ：2013.9.12 */
  /*  函数修改日期 ： */
  /*  修改人 ： */
  /*  修改原因 ： */
  /*  版本 ：1.0 */
  /*  历史版本 ： */
  /* % */
  /* 几条原则 */
  /* 保证系统裕度在一定范围之内 */
  /* % 保证系统裕度 */
  /* '<S6>:1499:19' */
  *Pre_Pclear = 0.0F;

  /* '<S6>:1499:20' */
  *Pre_LoadShedding = MGCCode_Ori_DWork.Pload -
    MGCCode_Ori_P.IslandParam.PreventiveLoadRatioUp * Pmax;

  /* '<S6>:1499:21' */
  *Pre_CutEn = TRUE;
  if (*Pre_LoadShedding < 0.0F) {
    /* '<S6>:1499:22' */
    /* '<S6>:1499:23' */
    *Pre_LoadShedding = 0.0F;

    /* '<S6>:1499:24' */
    *Pre_CutEn = FALSE;
  }

  /* % 风机转速控制 */
  /* % 电池SOC过低 */
  /* % 系统等效ratio过高 */
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_Ori_GridSync(real32_T GridFreqCmd, real32_T Freq, real32_T
  Vmeas, real32_T GridVmeas, boolean_T *SyncSignal, Warning *Warning_0)
{
  /* Graphical Function 'GridSync': '<S6>:1512' */
  *SyncSignal = FALSE;
  *Warning_0 = None;

  /* Transition: '<S6>:1517' */
  if (((real_T)(real32_T)fabs(Freq - GridFreqCmd) <= 0.05) && ((real_T)(Vmeas /
        GridVmeas) <= 1.05) && ((real_T)(Vmeas / GridVmeas) >= 0.95)) {
    /* Transition: '<S6>:1518' */
    MGCCode_Ori_DWork.GridCount++;
    if (MGCCode_Ori_DWork.GridCount >= 100.0F) {
      /* Transition: '<S6>:1521' */
      *SyncSignal = TRUE;
    } else {
      /* Transition: '<S6>:1520' */
    }
  } else {
    /* Transition: '<S6>:1519' */
    MGCCode_Ori_DWork.GridFailCount++;
    MGCCode_Ori_DWork.GridCount = 0.0F;
    if (MGCCode_Ori_DWork.GridFailCount >= 100000.0F) {
      /* Transition: '<S6>:1523' */
      *Warning_0 = GridFail;
    } else {
      /* Transition: '<S6>:1522' */
    }
  }
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_Ori_Logic(void)
{
  boolean_T Pre_CutEn;
  real32_T Pre_Pclear;
  real32_T Pre_LoadShedding;
  Warning Warning_0;
  real32_T Status_0;

  /* During 'Logic': '<S6>:1229' */
  Status_0 = (real32_T)(int16_T)MGCCode_Ori_status
    (MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.ICEStatus,
     MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.BatStatus,
     MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.PVStatus,
     MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.DFIG1Status,
     MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.DFIG2Status);
  switch (MGCCode_Ori_DWork.is_Logic) {
   case MGCCode_Ori_IN_Failure:
    /* During 'Failure': '<S6>:39' */
    break;

   case MGCCode_Ori_IN_GridOperation:
    /* During 'GridOperation': '<S6>:38' */
    if ((MGCCode_Ori_DWork.PassiveIslandSignal == 1.0F) ||
        (MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen == Island) ||
        (!MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.SwitchSignal)) {
      /* Transition: '<S6>:319' */
      /* Exit Internal 'GridOperation': '<S6>:38' */
      MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_NO_ACTIVE_CHILD;
      MGCCode_Ori_DWork.is_Logic = MGCCode_Ori_IN_IslandOperation;
      MGCCode_Ori_DWork.temporalCounter_i2 = 0UL;

      /* Entry 'IslandOperation': '<S6>:317' */
      MGCCode_Ori_B.OutEMS_c.SystemModen = Island;
      MGCCode_Ori_Y.Islandsignal = TRUE;
      ModeSwitch(Island);
      MGCCode_Ori_Y.SyncSignal = FALSE;

      /* Entry Internal 'IslandOperation': '<S6>:317' */
      /* Transition: '<S6>:326' */
      MGCCode_Ori_DWork.is_IslandOperation = MGCCode_Ori_IN_Island;

      /* Entry 'Island': '<S6>:322' */
      MGCCode_Ori_B.OutEMS_c.SystemModen = Island;
      MGCCode_Ori_B.OutSystem_k.Fref =
        MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fref;
      MGCCode_Ori_B.OutSystem_k.Vref =
        MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Vref;
      MGCCode_Ori_B.OutEMS_c.ICEMode = AGCAVC;
      MGCCode_Ori_B.OutEMS_c.PVMode = AGCAVC;
      MGCCode_Ori_B.OutEMS_c.DFIG1Mode = AGCAVC;
      MGCCode_Ori_B.OutEMS_c.DFIG2Mode = AGCAVC;
      MGCCode_Ori_B.OutEMS_c.BatMode = AGCAVC;
    } else {
      MGCCode_Ori_DWork.Pload =
        MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pout -
        MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineP;
      MGCCode_Ori_DWork.PassiveIslandSignal = (real32_T)
        MGCCode_Ori_PassiveIsland
        (MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fmeas);
      MGCCode_Ori_Y.EmergencyControl.EC_Pclear = MGCCode_Ori_EmergencyControl
        (MGCCode_Ori_DWork.PassiveIslandSignal != 0.0F, MGCCode_Ori_DWork.Pload,
         MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pmax);
      if (MGCCode_Ori_DWork.temporalCounter_i1 == 60UL) {
        MGCCode_Ori_PreventiveControl
          (MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineP,
           MGCCode_Ori_DWork.Pload,
           MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pmax, &Status_0,
           &Pre_LoadShedding, &Pre_Pclear, &Pre_CutEn);
        MGCCode_Ori_Y.EmergencyControl.Pre_LoadShedding = Pre_LoadShedding;
        MGCCode_Ori_Y.EmergencyControl.Pre_Pclear = Pre_Pclear;
        MGCCode_Ori_Y.EmergencyControl.Pre_CutEn = Pre_CutEn;
      }

      if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen ==
           ConstPConstQ) && (!((int16_T)MGCCode_Ori_DWork.is_GridOperation ==
            (int16_T)MGCCode_Ori_IN_ConstPConstQ))) {
        /* Transition: '<S6>:73' */
        /* Exit Internal 'GridOperation': '<S6>:38' */
        MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_ConstPConstQ;

        /* Entry 'ConstPConstQ': '<S6>:33' */
        MGCCode_Ori_B.OutEMS_c.SystemModen = ConstPConstQ;
        MGCCode_Ori_B.OutEMS_c.ICEMode = ConstPQ;
        MGCCode_Ori_B.OutEMS_c.DFIG1Mode = ConstPQ;
        MGCCode_Ori_B.OutEMS_c.DFIG2Mode = ConstPQ;
        MGCCode_Ori_B.OutEMS_c.BatMode = ConstPQ;
        MGCCode_Ori_B.OutEMS_c.PVMode = ConstPQ;
      } else if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen ==
                  AGC) && (!((int16_T)MGCCode_Ori_DWork.is_GridOperation ==
                             (int16_T)MGCCode_Ori_IN_AGC))) {
        /* Transition: '<S6>:74' */
        /* Exit Internal 'GridOperation': '<S6>:38' */
        MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_AGC;

        /* Entry 'AGC': '<S6>:34' */
        MGCCode_Ori_B.OutEMS_c.SystemModen = AGC;
        MGCCode_Ori_B.OutEMS_c.ICEMode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.DFIG1Mode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.DFIG2Mode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.BatMode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.PVMode = AGCAVC;
      } else if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen ==
                  Independent) && (!((int16_T)MGCCode_Ori_DWork.is_GridOperation
        == (int16_T)MGCCode_Ori_IN_Independent))) {
        /* Transition: '<S6>:75' */
        /* Exit Internal 'GridOperation': '<S6>:38' */
        MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_Independent;
      } else if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen ==
                  ActiveIsland) && (!((int16_T)
                   MGCCode_Ori_DWork.is_GridOperation == (int16_T)
                   MGCCode_Ori_IN_ActiveIsland))) {
        /* Transition: '<S6>:76' */
        /* Exit Internal 'GridOperation': '<S6>:38' */
        MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_ActiveIsland;

        /* Entry 'ActiveIsland': '<S6>:35' */
        MGCCode_Ori_B.OutEMS_c.SystemModen = AGC;
        MGCCode_Ori_B.OutEMS_c.ICEMode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.DFIG1Mode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.DFIG2Mode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.BatMode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.PVMode = AGCAVC;
        MGCCode_Ori_B.OutSystem_k.LinePref = 0.0F;
        MGCCode_Ori_B.OutSystem_k.LineQref = 0.0F;
        MGCCode_Ori_B.OutSystem_k.Fref = 50.0F;
        MGCCode_Ori_B.OutSystem_k.Vref = 0.95F;
        MGCCode_Ori_DWork.IslandCount = 0.0F;
        MGCCode_Ori_DWork.IslandFailCount = 0.0F;
        MGCCode_Ori_Y.Islandsignal = FALSE;
        MGCCode_Ori_Y.Warningn = None;
      } else {
        switch (MGCCode_Ori_DWork.is_GridOperation) {
         case MGCCode_Ori_IN_AGC:
          /* During 'AGC': '<S6>:34' */
          MGCCode_Ori_B.OutSystem_k.LinePref =
            MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LinePref;
          MGCCode_Ori_B.OutSystem_k.LineQref =
            MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineQref;
          break;

         case MGCCode_Ori_IN_ActiveIsland:
          /* During 'ActiveIsland': '<S6>:35' */
          MGCCode_Ori_fcn(MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineP,
                          MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineQ,
                          &Pre_CutEn, &Warning_0);
          MGCCode_Ori_Y.Islandsignal = Pre_CutEn;
          MGCCode_Ori_Y.Warningn = Warning_0;
          break;

         case MGCCode_Ori_IN_ConstPConstQ:
          /* During 'ConstPConstQ': '<S6>:33' */
          MGCCode_Ori_B.OutSystem_k.LinePref =
            MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LinePref;
          MGCCode_Ori_B.OutSystem_k.LineQref =
            MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineQref;
          break;

         default:
          /* During 'Independent': '<S6>:36' */
          break;
        }
      }
    }
    break;

   case MGCCode_Ori_IN_IslandOperation:
    /* During 'IslandOperation': '<S6>:317' */
    if (MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.SwitchSignal &&
        MGCCode_Ori_Y.SyncSignal) {
      /* Transition: '<S6>:320' */
      /* Exit Internal 'IslandOperation': '<S6>:317' */
      MGCCode_Ori_DWork.is_IslandOperation = MGCCode_Ori_IN_NO_ACTIVE_CHILD;
      MGCCode_Ori_DWork.is_Logic = MGCCode_Ori_IN_GridOperation;
      MGCCode_Ori_DWork.temporalCounter_i1 = 0UL;

      /* Entry 'GridOperation': '<S6>:38' */
      ModeSwitch(ConstPConstQ);
      MGCCode_Ori_Y.SyncSignal = FALSE;
      MGCCode_Ori_DWork.PassiveIslandSignal = 0.0F;
      MGCCode_Ori_Y.Islandsignal = FALSE;

      /* Entry Internal 'GridOperation': '<S6>:38' */
      /* Transition: '<S6>:290' */
      MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_ConstPConstQ;

      /* Entry 'ConstPConstQ': '<S6>:33' */
      MGCCode_Ori_B.OutEMS_c.SystemModen = ConstPConstQ;
      MGCCode_Ori_B.OutEMS_c.ICEMode = ConstPQ;
      MGCCode_Ori_B.OutEMS_c.DFIG1Mode = ConstPQ;
      MGCCode_Ori_B.OutEMS_c.DFIG2Mode = ConstPQ;
      MGCCode_Ori_B.OutEMS_c.BatMode = ConstPQ;
      MGCCode_Ori_B.OutEMS_c.PVMode = ConstPQ;
    } else {
      MGCCode_Ori_DWork.Pload =
        MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pout;
      MGCCode_Ori_Y.EmergencyControl.EC_IslandPclear =
        MGCCode__IslandEmergencyControl
        (MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fmeas,
         MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pmax);
      if (MGCCode_Ori_DWork.temporalCounter_i2 == 60UL) {
        MGCCode_IslandPreventiveControl
          (MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pmax, &Status_0,
           &Pre_LoadShedding, &Pre_CutEn);
        MGCCode_Ori_Y.EmergencyControl.Pre_IslandLoadShedding = Status_0;
        MGCCode_Ori_Y.EmergencyControl.Pre_IslandPclear = Pre_LoadShedding;
        MGCCode_Ori_Y.EmergencyControl.Pre_IslandCutEn = Pre_CutEn;
      }

      if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen == Island) &&
          (!((int16_T)MGCCode_Ori_DWork.is_IslandOperation == (int16_T)
             MGCCode_Ori_IN_Island))) {
        /* Transition: '<S6>:324' */
        /* Exit Internal 'IslandOperation': '<S6>:317' */
        MGCCode_Ori_DWork.is_IslandOperation = MGCCode_Ori_IN_Island;

        /* Entry 'Island': '<S6>:322' */
        MGCCode_Ori_B.OutEMS_c.SystemModen = Island;
        MGCCode_Ori_B.OutSystem_k.Fref =
          MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fref;
        MGCCode_Ori_B.OutSystem_k.Vref =
          MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Vref;
        MGCCode_Ori_B.OutEMS_c.ICEMode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.PVMode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.DFIG1Mode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.DFIG2Mode = AGCAVC;
        MGCCode_Ori_B.OutEMS_c.BatMode = AGCAVC;
      } else if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen ==
                  ActiveGrid) && (!((int16_T)
                   MGCCode_Ori_DWork.is_IslandOperation == (int16_T)
                   MGCCode_Ori_IN_ActiveGrid))) {
        /* Transition: '<S6>:325' */
        /* Exit Internal 'IslandOperation': '<S6>:317' */
        MGCCode_Ori_DWork.is_IslandOperation = MGCCode_Ori_IN_ActiveGrid;

        /* Entry 'ActiveGrid': '<S6>:323' */
        MGCCode_Ori_B.OutEMS_c.SystemModen = ActiveGrid;
        MGCCode_Ori_DWork.GridFailCount = 0.0F;
        MGCCode_Ori_DWork.GridCount = 0.0F;
      } else if ((MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen ==
                  IslandAGC) && (!((int16_T)MGCCode_Ori_DWork.is_IslandOperation
        == (int16_T)MGCCode_Ori_IN_IslandAGC))) {
        /* Transition: '<S6>:334' */
        /* Exit Internal 'IslandOperation': '<S6>:317' */
        MGCCode_Ori_DWork.is_IslandOperation = MGCCode_Ori_IN_IslandAGC;
      } else {
        switch (MGCCode_Ori_DWork.is_IslandOperation) {
         case MGCCode_Ori_IN_ActiveGrid:
          /* During 'ActiveGrid': '<S6>:323' */
          MGCCode_Ori_B.OutSystem_k.Fref =
            MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.GridFreqCmd;
          MGCCode_Ori_B.OutSystem_k.Vref =
            MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.GridVmeas;
          MGCCode_Ori_GridSync
            (MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.GridFreqCmd,
             MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fmeas,
             MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Vmeas,
             MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.GridVmeas, &Pre_CutEn,
             &Warning_0);
          MGCCode_Ori_Y.SyncSignal = Pre_CutEn;
          MGCCode_Ori_Y.Warningn = Warning_0;
          break;

         case MGCCode_Ori_IN_Island:
          /* During 'Island': '<S6>:322' */
          break;

         default:
          /* During 'IslandAGC': '<S6>:332' */
          break;
        }
      }
    }
    break;

   case MGCCode_Ori_IN_ShutDown:
    /* During 'ShutDown': '<S6>:3' */
    break;

   default:
    /* During 'Start': '<S6>:2' */
    if ((int16_T)MGCCode_Ori_DWork.temporalCounter_i3 >= 2) {
      /* Transition: '<S6>:40' */
      if ((int16_T)Status_0 == (int16_T)Fail) {
        /* Transition: '<S6>:41' */
        MGCCode_Ori_Y.Warningn = StartFail;
        MGCCode_Ori_DWork.is_Logic = MGCCode_Ori_IN_Failure;
      } else {
        if ((int16_T)Status_0 != (int16_T)Fail) {
          /* Transition: '<S6>:70' */
          MGCCode_Ori_DWork.is_Logic = MGCCode_Ori_IN_GridOperation;
          MGCCode_Ori_DWork.temporalCounter_i1 = 0UL;

          /* Entry 'GridOperation': '<S6>:38' */
          ModeSwitch(ConstPConstQ);
          MGCCode_Ori_Y.SyncSignal = FALSE;
          MGCCode_Ori_DWork.PassiveIslandSignal = 0.0F;
          MGCCode_Ori_Y.Islandsignal = FALSE;

          /* Entry Internal 'GridOperation': '<S6>:38' */
          /* Transition: '<S6>:290' */
          MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_ConstPConstQ;

          /* Entry 'ConstPConstQ': '<S6>:33' */
          MGCCode_Ori_B.OutEMS_c.SystemModen = ConstPConstQ;
          MGCCode_Ori_B.OutEMS_c.ICEMode = ConstPQ;
          MGCCode_Ori_B.OutEMS_c.DFIG1Mode = ConstPQ;
          MGCCode_Ori_B.OutEMS_c.DFIG2Mode = ConstPQ;
          MGCCode_Ori_B.OutEMS_c.BatMode = ConstPQ;
          MGCCode_Ori_B.OutEMS_c.PVMode = ConstPQ;
        }
      }
    }
    break;
  }
}

/* Model step function */
void MGCCode_Ori_step(void)
{
  /* local block i/o variables */
  real32_T rtb_Saturation4;
  real32_T rtb_Saturation5;
  real32_T rtb_Sum;
  real32_T rtb_Sum1;
  real32_T rtb_Saturation6;
  real32_T rtb_Saturation7;
  real32_T rtb_Sum5;
  real32_T rtb_Sum6;
  real32_T rtb_Sum_m;
  real32_T rtb_Sum1_i;
  real32_T rtb_Sum5_d;
  real32_T rtb_Sum6_b;
  real32_T rtb_Sum2_l;
  real32_T rtb_Sum3_b;
  real32_T rtb_Sum4_i;
  real32_T rtb_Sum7;
  SystemMode rtb_SystemModen_nz;
  SystemMode rtb_SystemModen_nzs;
  SystemMode rtb_SystemModen_nzsd;
  GenMode rtb_BatMode_ly;
  GenMode rtb_PVMode_a11;
  GenMode rtb_DFIG1Mode_loxt;
  int16_T rtb_LinePEnable;
  int16_T rtb_FreqCtrlEnable;
  int16_T rtb_LineQEnable;
  int16_T rtb_VoltCtrlEnable;
  real32_T rtb_Divide7_p;
  real32_T rtb_Sum_n;
  real32_T rtb_Pmax;
  real32_T rtb_AGCRatio;
  real32_T rtb_DFIG1SPcmd;
  real32_T rtb_DFIG1SQcmd;
  real32_T rtb_Divide5;
  real32_T rtb_Divide2;
  real32_T rtb_Sum3;
  real32_T rtb_AVCRatio;
  real32_T rtb_Fref;
  real32_T rtb_Divide5_g;
  real32_T rtb_Divide7_d;
  real32_T rtb_AGCref;
  int16_T rtb_AGCSwitch;
  int16_T rtb_AVCSwitch;
  real32_T tmp;

  /* Outport: '<Root>/OutICEn' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutICEn_at_inport_0'
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant2'
   */
  MGCCode_Ori_Y.OutICEn.ICESPcmd = 1.0F;
  MGCCode_Ori_Y.OutICEn.ICESQcmd = 1.0F;

  /* Switch: '<S9>/Switch15' incorporates:
   *  Constant: '<S9>/Constant15'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_Ori_U.InICEn.ICEStatus) {
    tmp = MGCCode_Ori_U.InICEn.ICESPout;
  } else {
    tmp = 0.0F;
  }

  /* End of Switch: '<S9>/Switch15' */

  /* Switch: '<S9>/Switch14' incorporates:
   *  Constant: '<S9>/Constant14'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_Ori_U.InBatn.BatStatus) {
    rtb_Divide7_d = MGCCode_Ori_U.InBatn.BatSPout;
  } else {
    rtb_Divide7_d = 0.0F;
  }

  /* End of Switch: '<S9>/Switch14' */

  /* Switch: '<S9>/Switch13' incorporates:
   *  Constant: '<S9>/Constant13'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_Ori_U.InPVn.PVStatus) {
    rtb_Sum3 = MGCCode_Ori_U.InPVn.PVSPout;
  } else {
    rtb_Sum3 = 0.0F;
  }

  /* End of Switch: '<S9>/Switch13' */

  /* Switch: '<S9>/Switch12' incorporates:
   *  Constant: '<S9>/Constant12'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_Ori_U.InDFIG1n.DFIG1Status) {
    rtb_Fref = MGCCode_Ori_U.InDFIG1n.DFIG1SPout;
  } else {
    rtb_Fref = 0.0F;
  }

  /* End of Switch: '<S9>/Switch12' */

  /* Sum: '<S9>/Sum' */
  rtb_Sum_n = (((tmp + rtb_Divide7_d) + rtb_Sum3) + rtb_Fref) + 0.0F;

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S23>/Constant1'
   *  Constant: '<S23>/Constant9'
   */
  rtb_Divide7_p = MGCCode_Ori_P.Base.Bat * MGCCode_Ori_P.Base.BatPmax;

  /* Switch: '<S9>/Switch11' incorporates:
   *  Constant: '<S9>/Constant11'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_Ori_U.InBatn.BatStatus) {
    tmp = rtb_Divide7_p;
  } else {
    tmp = 0.1F;
  }

  /* End of Switch: '<S9>/Switch11' */

  /* Switch: '<S9>/Switch10' incorporates:
   *  Constant: '<S9>/Constant10'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_Ori_U.InICEn.ICEStatus) {
    rtb_Divide7_d = 0.0F;
  } else {
    rtb_Divide7_d = 0.1F;
  }

  /* End of Switch: '<S9>/Switch10' */

  /* Switch: '<S9>/Switch9' incorporates:
   *  Constant: '<S37>/Constant1'
   *  Constant: '<S9>/Constant9'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_Ori_U.InDFIG1n.DFIG1Status) {
    rtb_Sum3 = MGCCode_Ori_P.Base.DFIG1;
  } else {
    rtb_Sum3 = 0.1F;
  }

  /* End of Switch: '<S9>/Switch9' */

  /* Switch: '<S9>/Switch8' incorporates:
   *  Constant: '<S48>/Constant3'
   *  Constant: '<S9>/Constant8'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_Ori_U.InPVn.PVStatus) {
    rtb_Fref = MGCCode_Ori_P.Base.PV;
  } else {
    rtb_Fref = 0.1F;
  }

  /* End of Switch: '<S9>/Switch8' */

  /* Sum: '<S9>/Sum1' */
  rtb_Pmax = (((tmp + rtb_Divide7_d) + rtb_Sum3) + rtb_Fref) + 0.0F;

  /* Product: '<S9>/Divide' */
  rtb_AGCRatio = rtb_Sum_n / rtb_Pmax;

  /* RateTransition: '<S1>/Rate Transition1' */
  if (MGCCode_Ori_M->Timing.TaskCounters.TID[1] == 0) {
    MGCCode_Ori_B.SystemModen = MGCCode_Ori_DWork.RateTransition1_1_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_Ori_B.ICEMode = MGCCode_Ori_DWork.RateTransition1_2_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_Ori_B.BatMode = MGCCode_Ori_DWork.RateTransition1_3_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_Ori_B.PVMode = MGCCode_Ori_DWork.RateTransition1_4_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_Ori_B.DFIG1Mode = MGCCode_Ori_DWork.RateTransition1_5_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_Ori_B.DFIG2Mode = MGCCode_Ori_DWork.RateTransition1_6_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition1' */

  /* BusCreator: '<S1>/BusConversion_InsertedFor_MicrogridModelManager_at_inport_0' incorporates:
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InDFIG2n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   */
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.SystemModen =
    MGCCode_Ori_B.SystemModen;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.ICEMode = MGCCode_Ori_B.ICEMode;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.BatMode = MGCCode_Ori_B.BatMode;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.PVMode = MGCCode_Ori_B.PVMode;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.DFIG1Mode =
    MGCCode_Ori_B.DFIG1Mode;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.DFIG2Mode =
    MGCCode_Ori_B.DFIG2Mode;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.ICEStatus =
    MGCCode_Ori_U.InICEn.ICEStatus;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.BatStatus =
    MGCCode_Ori_U.InBatn.BatStatus;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.PVStatus =
    MGCCode_Ori_U.InPVn.PVStatus;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.DFIG1Status =
    MGCCode_Ori_U.InDFIG1n.DFIG1Status;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4.DFIG2Status =
    MGCCode_Ori_U.InDFIG2n.DFIG2Status;

  /* BusCreator: '<S1>/BusConversion_InsertedFor_MicrogridModelManager_at_inport_1' incorporates:
   *  Inport: '<Root>/InSystemRootn'
   */
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LinePref =
    MGCCode_Ori_U.InSystemRootn.LinePref;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineP =
    MGCCode_Ori_U.InSystemRootn.LineP;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fref =
    MGCCode_Ori_U.InSystemRootn.Freqref;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fmeas =
    MGCCode_Ori_U.InSystemRootn.Fmeas;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineQref =
    MGCCode_Ori_U.InSystemRootn.LineQref;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.LineQ =
    MGCCode_Ori_U.InSystemRootn.LineQ;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Vref =
    MGCCode_Ori_U.InSystemRootn.Vref;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Vmeas =
    MGCCode_Ori_U.InSystemRootn.Vmeas;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.GridVmeas =
    MGCCode_Ori_U.InSystemRootn.GridVmeas;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.GridFreqCmd =
    MGCCode_Ori_U.InSystemRootn.GridFreqCmd;
  MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.SwitchSignal =
    MGCCode_Ori_U.InSystemRootn.SwitchSignal;

  /* Switch: '<S9>/Switch7' incorporates:
   *  Constant: '<S9>/Constant7'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_Ori_U.InICEn.ICEStatus) {
    tmp = MGCCode_Ori_U.InICEn.ICESQout;
  } else {
    tmp = 0.0F;
  }

  /* End of Switch: '<S9>/Switch7' */

  /* Switch: '<S9>/Switch6' incorporates:
   *  Constant: '<S9>/Constant6'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_Ori_U.InBatn.BatStatus) {
    rtb_Divide7_d = MGCCode_Ori_U.InBatn.BatSQout;
  } else {
    rtb_Divide7_d = 0.0F;
  }

  /* End of Switch: '<S9>/Switch6' */

  /* Switch: '<S9>/Switch5' incorporates:
   *  Constant: '<S9>/Constant5'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_Ori_U.InPVn.PVStatus) {
    rtb_Sum3 = MGCCode_Ori_U.InPVn.PVSQout;
  } else {
    rtb_Sum3 = 0.0F;
  }

  /* End of Switch: '<S9>/Switch5' */

  /* Switch: '<S9>/Switch4' incorporates:
   *  Constant: '<S9>/Constant4'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_Ori_U.InDFIG1n.DFIG1Status) {
    rtb_Fref = MGCCode_Ori_U.InDFIG1n.DFIG1SQout;
  } else {
    rtb_Fref = 0.0F;
  }

  /* End of Switch: '<S9>/Switch4' */

  /* Sum: '<S9>/Sum2' */
  rtb_Divide2 = (((tmp + rtb_Divide7_d) + rtb_Sum3) + rtb_Fref) + 0.0F;

  /* Product: '<S48>/Product1' incorporates:
   *  Constant: '<S48>/Constant1'
   *  Constant: '<S48>/Constant6'
   */
  rtb_DFIG1SPcmd = MGCCode_Ori_P.Base.PV * MGCCode_Ori_P.Base.PVQmax;

  /* Product: '<S37>/Product1' incorporates:
   *  Constant: '<S37>/Constant3'
   *  Constant: '<S37>/Constant6'
   */
  rtb_DFIG1SQcmd = MGCCode_Ori_P.Base.DFIG1 * MGCCode_Ori_P.Base.DFIG1Qmax;

  /* Product: '<S23>/Product1' incorporates:
   *  Constant: '<S23>/Constant3'
   *  Constant: '<S23>/Constant6'
   */
  rtb_Divide5 = MGCCode_Ori_P.Base.Bat * MGCCode_Ori_P.Base.BatQmax;

  /* Switch: '<S9>/Switch3' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_Ori_U.InPVn.PVStatus) {
    tmp = rtb_DFIG1SPcmd;
  } else {
    tmp = 0.1F;
  }

  /* End of Switch: '<S9>/Switch3' */

  /* Switch: '<S9>/Switch2' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_Ori_U.InDFIG1n.DFIG1Status) {
    rtb_Divide7_d = rtb_DFIG1SQcmd;
  } else {
    rtb_Divide7_d = 0.1F;
  }

  /* End of Switch: '<S9>/Switch2' */

  /* Switch: '<S9>/Switch1' incorporates:
   *  Constant: '<S9>/Constant1'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_Ori_U.InBatn.BatStatus) {
    rtb_Sum3 = rtb_Divide5;
  } else {
    rtb_Sum3 = 0.1F;
  }

  /* End of Switch: '<S9>/Switch1' */

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S9>/Constant'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_Ori_U.InICEn.ICEStatus) {
    rtb_Fref = 0.0F;
  } else {
    rtb_Fref = 0.1F;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Sum: '<S9>/Sum3' */
  rtb_Sum3 = (((tmp + rtb_Divide7_d) + rtb_Sum3) + rtb_Fref) + 0.0F;

  /* Product: '<S9>/Divide1' */
  rtb_AVCRatio = rtb_Divide2 / rtb_Sum3;

  /* BusCreator: '<S1>/BusConversion_InsertedFor_MicrogridModelManager_at_inport_2' incorporates:
   *  Constant: '<S37>/Constant1'
   *  Constant: '<S48>/Constant3'
   *  Constant: '<S9>/Constant16'
   *  Constant: '<S9>/Constant17'
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   *  Product: '<S9>/Divide10'
   *  Product: '<S9>/Divide11'
   *  Product: '<S9>/Divide2'
   *  Product: '<S9>/Divide3'
   *  Product: '<S9>/Divide4'
   *  Product: '<S9>/Divide5'
   *  Product: '<S9>/Divide6'
   *  Product: '<S9>/Divide7'
   *  Product: '<S9>/Divide8'
   *  Product: '<S9>/Divide9'
   */
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pout = rtb_Sum_n;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Pmax = rtb_Pmax;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.AGCRatio = rtb_AGCRatio;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.AVCRatio = rtb_AVCRatio;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.PVAGCRatio =
    MGCCode_Ori_U.InPVn.PVSPout / MGCCode_Ori_P.Base.PV;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.PVAVCRatio =
    MGCCode_Ori_U.InPVn.PVSQout / rtb_DFIG1SPcmd;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.DFIG1AGCRatio =
    MGCCode_Ori_U.InDFIG1n.DFIG1SPout / MGCCode_Ori_P.Base.DFIG1;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.DFIG1AVCRatio =
    MGCCode_Ori_U.InDFIG1n.DFIG1SQout / rtb_DFIG1SQcmd;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.DFIG3AGCRatio =
    MGCCode_Ori_U.InDFIG1n.DFIG1SPout / MGCCode_Ori_P.Base.DFIG1;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.DFIG3AVCRatio =
    MGCCode_Ori_U.InDFIG1n.DFIG1SQout / rtb_DFIG1SQcmd;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.BatAGCRatio =
    MGCCode_Ori_U.InBatn.BatSPout / rtb_Divide7_p;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.BatAVCRatio =
    MGCCode_Ori_U.InBatn.BatSQout / rtb_Divide5;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.ICEAGCRatio =
    MGCCode_Ori_U.InICEn.ICESPout / MGCCode_Ori_P.Base.ICE;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.ICEAVCRatio =
    MGCCode_Ori_U.InICEn.ICESQout / MGCCode_Ori_P.Base.ICE;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Qout = rtb_Divide2;
  MGCCode_Ori_B.BusConversion_InsertedFor_Micro.Qmax = rtb_Sum3;

  /* Chart: '<S1>/MicrogridModelManager' */
  /* Gateway: MGCC1/MicrogridModelManager */
  if ((real32_T)MGCCode_Ori_DWork.temporalCounter_i1 < 60.0F) {
    MGCCode_Ori_DWork.temporalCounter_i1++;
  }

  if ((real32_T)MGCCode_Ori_DWork.temporalCounter_i2 < 60.0F) {
    MGCCode_Ori_DWork.temporalCounter_i2++;
  }

  if ((int16_T)MGCCode_Ori_DWork.temporalCounter_i3 < 3) {
    MGCCode_Ori_DWork.temporalCounter_i3 = (uint16_T)((uint16_T)(int16_T)
      ((int16_T)MGCCode_Ori_DWork.temporalCounter_i3 + 1) & 255U);
  }

  /* During: MGCC1/MicrogridModelManager */
  if (MGCCode_Ori_DWork.is_active_c15_MGCCode_Ori == 0U) {
    /* Entry: MGCC1/MicrogridModelManager */
    MGCCode_Ori_DWork.is_active_c15_MGCCode_Ori = 1U;

    /* Entry Internal: MGCC1/MicrogridModelManager */
    MGCCode_Ori_DWork.is_c15_MGCCode_Ori = MGCCode_Ori_IN_Logic;

    /* Entry 'Logic': '<S6>:1229' */
    MGCCode_Ori_DWork.count = 0.0F;
    MGCCode_Ori_B.OutSystem_k.Fref =
      MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Fref;
    MGCCode_Ori_B.OutSystem_k.Vref =
      MGCCode_Ori_B.BusConversion_InsertedFor_Mic_l.Vref;

    /* Entry Internal 'Logic': '<S6>:1229' */
    /* Transition: '<S6>:72' */
    MGCCode_Ori_DWork.is_Logic = MGCCode_Ori_IN_Start;
    MGCCode_Ori_DWork.temporalCounter_i3 = 0U;

    /* Entry 'Start': '<S6>:2' */
    MGCCode_Ori_B.OutEMS_c.SystemModen = Start;
  } else {
    MGCCode_Ori_Logic();
  }

  if ((real32_T)MGCCode_Ori_DWork.temporalCounter_i1 == 60.0F) {
    MGCCode_Ori_DWork.temporalCounter_i1 = 0UL;
  }

  if ((real32_T)MGCCode_Ori_DWork.temporalCounter_i2 == 60.0F) {
    MGCCode_Ori_DWork.temporalCounter_i2 = 0UL;
  }

  /* End of Chart: '<S1>/MicrogridModelManager' */

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator13_at_inport_3' */
  rtb_Sum_n = MGCCode_Ori_B.OutSystem_k.LinePref;
  rtb_Fref = MGCCode_Ori_B.OutSystem_k.Fref;

  /* MATLAB Function: '<S2>/ModeSelect1' incorporates:
   *  BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator13_at_inport_1'
   */
  /* MATLAB Function 'MGCC1/AGCandAVC1/ModeSelect1': '<S16>:1' */
  if ((MGCCode_Ori_B.OutEMS_c.SystemModen == ConstPConstQ) ||
      (MGCCode_Ori_B.OutEMS_c.SystemModen == Start)) {
    /* '<S16>:1:3' */
    /* '<S16>:1:4' */
    rtb_LinePEnable = 0;

    /* '<S16>:1:5' */
    rtb_FreqCtrlEnable = 0;

    /* '<S16>:1:6' */
    rtb_LineQEnable = 0;

    /* '<S16>:1:7' */
    rtb_VoltCtrlEnable = 0;

    /* '<S16>:1:8' */
    rtb_AGCSwitch = 1;

    /* '<S16>:1:9' */
    rtb_AVCSwitch = 1;
  } else if (MGCCode_Ori_B.OutEMS_c.SystemModen == AGC) {
    /* '<S16>:1:11' */
    /* '<S16>:1:12' */
    rtb_LinePEnable = 1;

    /* '<S16>:1:13' */
    rtb_FreqCtrlEnable = 0;

    /* '<S16>:1:14' */
    rtb_LineQEnable = 1;

    /* '<S16>:1:15' */
    rtb_VoltCtrlEnable = 0;

    /* '<S16>:1:16' */
    rtb_AGCSwitch = 1;

    /* '<S16>:1:17' */
    rtb_AVCSwitch = 1;
  } else if (MGCCode_Ori_B.OutEMS_c.SystemModen == Independent) {
    /* '<S16>:1:19' */
    /* '<S16>:1:20' */
    rtb_LinePEnable = 1;

    /* '<S16>:1:21' */
    rtb_FreqCtrlEnable = 0;

    /* '<S16>:1:22' */
    rtb_LineQEnable = 1;

    /* '<S16>:1:23' */
    rtb_VoltCtrlEnable = 0;

    /* '<S16>:1:24' */
    rtb_AGCSwitch = 1;

    /* '<S16>:1:25' */
    rtb_AVCSwitch = 1;
  } else if (MGCCode_Ori_B.OutEMS_c.SystemModen == Island) {
    /* '<S16>:1:27' */
    /* '<S16>:1:28' */
    rtb_LinePEnable = 0;

    /* '<S16>:1:29' */
    rtb_FreqCtrlEnable = 1;

    /* '<S16>:1:30' */
    rtb_LineQEnable = 0;

    /* '<S16>:1:31' */
    rtb_VoltCtrlEnable = 1;

    /* '<S16>:1:32' */
    rtb_AGCSwitch = 0;

    /* '<S16>:1:33' */
    rtb_AVCSwitch = 0;
  } else {
    /* '<S16>:1:36' */
    rtb_LinePEnable = 0;

    /* '<S16>:1:37' */
    rtb_FreqCtrlEnable = 1;

    /* '<S16>:1:38' */
    rtb_LineQEnable = 0;

    /* '<S16>:1:39' */
    rtb_VoltCtrlEnable = 1;

    /* '<S16>:1:40' */
    rtb_AGCSwitch = 0;

    /* '<S16>:1:41' */
    rtb_AVCSwitch = 0;
  }

  /* End of MATLAB Function: '<S2>/ModeSelect1' */

  /* Switch: '<S2>/Switch5' incorporates:
   *  BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator13_at_inport_3'
   *  Constant: '<S2>/Constant19'
   *  Inport: '<Root>/InSystemRootn'
   *  Sum: '<S2>/Sum2'
   */
  if (rtb_LinePEnable != 0) {
    tmp = MGCCode_Ori_B.OutSystem_k.LinePref - MGCCode_Ori_U.InSystemRootn.LineP;
  } else {
    tmp = 0.0F;
  }

  /* End of Switch: '<S2>/Switch5' */

  /* Product: '<S2>/Divide2' incorporates:
   *  Constant: '<S2>/Constant10'
   */
  rtb_Divide5_g = tmp / MGCCode_Ori_P.Base.LineP;

  /* Saturate: '<S2>/Saturation4' */
  if (rtb_Divide5_g >= 2.0F) {
    rtb_Saturation4 = 2.0F;
  } else if (rtb_Divide5_g <= -2.0F) {
    rtb_Saturation4 = -2.0F;
  } else {
    rtb_Saturation4 = rtb_Divide5_g;
  }

  /* End of Saturate: '<S2>/Saturation4' */

  /* Outputs for Enabled SubSystem: '<S2>/EnablePI1' */
  MGCCode_Ori_EnablePI1(rtb_LinePEnable, rtb_Saturation4, 0.0F,
                        MGCCode_Ori_ConstB.Constant23, &MGCCode_Ori_B.EnablePI1,
                        &MGCCode_Ori_DWork.EnablePI1,
                        StructPointer->CtrlParamAGC.LinePPIGain,
                        StructPointer->CtrlParamAGC.LinePPILowerSat,
                        StructPointer->CtrlParamAGC.LinePPIUpperSat,
                        StructPointer->CtrlParamAGC.LinePPIIntegral);

  /* End of Outputs for SubSystem: '<S2>/EnablePI1' */

  /* Switch: '<S2>/Switch9' incorporates:
   *  Constant: '<S2>/Constant20'
   *  Inport: '<Root>/InSystemRootn'
   *  Sum: '<S2>/Sum3'
   */
  if (rtb_FreqCtrlEnable != 0) {
    tmp = rtb_Fref - MGCCode_Ori_U.InSystemRootn.Fmeas;
  } else {
    tmp = 0.0F;
  }

  /* End of Switch: '<S2>/Switch9' */

  /* Product: '<S2>/Divide1' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_Divide5_g = tmp / MGCCode_Ori_P.Base.Freq;

  /* Saturate: '<S2>/Saturation5' */
  if (rtb_Divide5_g >= 2.0F) {
    rtb_Saturation5 = 2.0F;
  } else if (rtb_Divide5_g <= -2.0F) {
    rtb_Saturation5 = -2.0F;
  } else {
    rtb_Saturation5 = rtb_Divide5_g;
  }

  /* End of Saturate: '<S2>/Saturation5' */

  /* Outputs for Enabled SubSystem: '<S2>/EnablePI4' */
  MGCCode_Ori_EnablePI1(rtb_FreqCtrlEnable, rtb_Saturation5, 0.0F,
                        MGCCode_Ori_ConstB.Constant24, &MGCCode_Ori_B.EnablePI4,
                        &MGCCode_Ori_DWork.EnablePI4,
                        StructPointer->CtrlParamAGC.FreqPIGain,
                        StructPointer->CtrlParamAGC.FreqPILowerSat,
                        StructPointer->CtrlParamAGC.FreqPIUpperSat,
                        StructPointer->CtrlParamAGC.FreqPIIntegral);

  /* End of Outputs for SubSystem: '<S2>/EnablePI4' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant13'
   *  Logic: '<S2>/Logical Operator'
   */
  if ((rtb_LinePEnable != 0) || (rtb_FreqCtrlEnable != 0)) {
    /* Switch: '<S2>/Switch3' incorporates:
     *  Constant: '<S2>/Constant17'
     *  Inport: '<Root>/InSystemRootn'
     *  Product: '<S2>/Divide'
     *  Sum: '<S2>/Sum11'
     */
    if (rtb_LinePEnable != 0) {
      rtb_Sum_n = (rtb_Sum_n - MGCCode_Ori_U.InSystemRootn.LineP) / rtb_Pmax;
    } else {
      rtb_Sum_n = 0.0F;
    }

    /* End of Switch: '<S2>/Switch3' */

    /* Switch: '<S2>/Switch1' */
    if (rtb_AGCSwitch != 0) {
      rtb_Divide7_d = MGCCode_Ori_B.EnablePI1.Saturation;
    } else {
      rtb_Divide7_d = MGCCode_Ori_B.EnablePI4.Saturation;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Sum: '<S2>/Sum7' incorporates:
     *  Sum: '<S2>/Sum9'
     */
    rtb_AGCref = (rtb_AGCRatio + rtb_Sum_n) + rtb_Divide7_d;

    /* Saturate: '<S2>/Saturation' */
    if (rtb_AGCref >= 1.0F) {
      rtb_AGCref = 1.0F;
    } else {
      if (rtb_AGCref <= 0.0F) {
        rtb_AGCref = 0.0F;
      }
    }

    /* End of Saturate: '<S2>/Saturation' */
  } else {
    rtb_AGCref = 0.0F;
  }

  /* End of Switch: '<S2>/Switch' */
  if (MGCCode_Ori_M->Timing.TaskCounters.TID[1] == 0) {
    /* Switch: '<S2>/Switch6' incorporates:
     *  Constant: '<S2>/Constant28'
     */
    MGCCode_Ori_B.RatioAGC = 0.0F;
  }

  /* Sum: '<S25>/Sum2' */
  rtb_Sum_n = rtb_AGCref + MGCCode_Ori_B.RatioAGC;

  /* MATLAB Function: '<S25>/BatChargeControl' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  /* MATLAB Function 'MGCC1/BatControl2/PowerRegulator/BatChargeControl': '<S26>:1' */
  if (MGCCode_Ori_U.InBatn.BatChargeCmd) {
    /* '<S26>:1:6' */
    rtb_Sum_n = -(1.0F - rtb_Sum_n);
  } else {
    /* '<S26>:1:3' */
    /* '<S26>:1:4' */
  }

  /* End of MATLAB Function: '<S25>/BatChargeControl' */

  /* Product: '<S23>/Divide5' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Divide5_g = MGCCode_Ori_U.InBatn.BatSPout / rtb_Divide7_p;

  /* Sum: '<S25>/Sum' */
  rtb_Sum = rtb_Sum_n - rtb_Divide5_g;

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator6_at_inport_1' */
  rtb_SystemModen_nz = MGCCode_Ori_B.OutEMS_c.SystemModen;
  rtb_BatMode_ly = MGCCode_Ori_B.OutEMS_c.BatMode;

  /* MATLAB Function: '<S25>/ModeSelect' */
  MGCCode_Ori_ModeSelect(rtb_SystemModen_nz, rtb_BatMode_ly,
    &MGCCode_Ori_B.sf_ModeSelect);

  /* Outputs for Enabled SubSystem: '<S25>/EnablePI' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect.AGCInnerEnable, rtb_Sum,
                        0.0F, MGCCode_Ori_ConstB.Constant4,
                        &MGCCode_Ori_B.EnablePI, &MGCCode_Ori_DWork.EnablePI,
                        StructPointer->CtrlParamBat.AGCInnerPIGain,
                        StructPointer->CtrlParamBat.AGCInnerPILowerSat,
                        StructPointer->CtrlParamBat.AGCInnerPIUpperSat,
                        StructPointer->CtrlParamBat.AGCInnerPIIntegral);

  /* End of Outputs for SubSystem: '<S25>/EnablePI' */

  /* Product: '<S23>/Divide1' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Fref = MGCCode_Ori_U.InBatn.BatSPref / rtb_Divide7_p;

  /* Saturate: '<S23>/Saturation1' */
  if (rtb_Fref >= 1.0F) {
    rtb_Fref = 1.0F;
  } else {
    if (rtb_Fref <= -1.0F) {
      rtb_Fref = -1.0F;
    }
  }

  /* End of Saturate: '<S23>/Saturation1' */

  /* Sum: '<S25>/Sum1' */
  rtb_Sum1 = rtb_Fref - rtb_Divide5_g;

  /* Outputs for Enabled SubSystem: '<S25>/EnablePI1' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect.ConstPEnable, rtb_Sum1, 0.0F,
                        MGCCode_Ori_ConstB.Constant2, &MGCCode_Ori_B.EnablePI1_m,
                        &MGCCode_Ori_DWork.EnablePI1_m,
                        StructPointer->CtrlParamBat.ConstPPIGain,
                        StructPointer->CtrlParamBat.ConstPPILowerSat,
                        StructPointer->CtrlParamBat.ConstPPIUpperSat,
                        StructPointer->CtrlParamBat.ConstPPIIntegral);

  /* End of Outputs for SubSystem: '<S25>/EnablePI1' */

  /* Switch: '<S25>/Switch1' incorporates:
   *  Constant: '<S25>/Constant'
   *  Logic: '<S25>/Logical Operator'
   */
  if ((MGCCode_Ori_B.sf_ModeSelect.AGCInnerEnable != 0) ||
      (MGCCode_Ori_B.sf_ModeSelect.ConstPEnable != 0)) {
    /* Switch: '<S25>/Switch' incorporates:
     *  Sum: '<S25>/Add'
     *  Sum: '<S25>/Add1'
     */
    if (MGCCode_Ori_B.sf_ModeSelect.PCtrlSwitch != 0) {
      rtb_Sum_n += MGCCode_Ori_B.EnablePI.Saturation;
    } else {
      rtb_Sum_n = MGCCode_Ori_B.EnablePI1_m.Saturation + rtb_Fref;
    }

    /* End of Switch: '<S25>/Switch' */

    /* Saturate: '<S25>/Saturation' */
    if (rtb_Sum_n >= 1.0F) {
      rtb_Divide7_d = 1.0F;
    } else if (rtb_Sum_n <= 0.0F) {
      rtb_Divide7_d = 0.0F;
    } else {
      rtb_Divide7_d = rtb_Sum_n;
    }

    /* End of Saturate: '<S25>/Saturation' */
  } else {
    rtb_Divide7_d = 0.0F;
  }

  /* End of Switch: '<S25>/Switch1' */

  /* Product: '<S24>/Product' */
  rtb_Fref = rtb_Divide7_d * rtb_Divide7_p;

  /* Switch: '<S2>/Switch10' incorporates:
   *  Constant: '<S2>/Constant21'
   *  Inport: '<Root>/InSystemRootn'
   *  Sum: '<S2>/Sum1'
   */
  if (rtb_LineQEnable != 0) {
    tmp = MGCCode_Ori_U.InSystemRootn.LineQref -
      MGCCode_Ori_U.InSystemRootn.LineQ;
  } else {
    tmp = 0.0F;
  }

  /* End of Switch: '<S2>/Switch10' */

  /* Product: '<S2>/Divide4' incorporates:
   *  Constant: '<S2>/Constant2'
   */
  rtb_Divide7_d = tmp / MGCCode_Ori_P.Base.LineQ;

  /* Saturate: '<S2>/Saturation6' */
  if (rtb_Divide7_d >= 2.0F) {
    rtb_Saturation6 = 2.0F;
  } else if (rtb_Divide7_d <= -2.0F) {
    rtb_Saturation6 = -2.0F;
  } else {
    rtb_Saturation6 = rtb_Divide7_d;
  }

  /* End of Saturate: '<S2>/Saturation6' */

  /* Outputs for Enabled SubSystem: '<S2>/EnablePI8' */
  MGCCode_Ori_EnablePI5(rtb_LineQEnable, rtb_Saturation6,
                        MGCCode_Ori_ConstB.Constant25, &MGCCode_Ori_B.EnablePI8,
                        &MGCCode_Ori_DWork.EnablePI8,
                        StructPointer->CtrlParamAVC.LineQPIGain,
                        StructPointer->CtrlParamAVC.LineQPILowerSat,
                        StructPointer->CtrlParamAVC.LineQPIUpperSat,
                        StructPointer->CtrlParamAVC.LineQPIIntegral);

  /* End of Outputs for SubSystem: '<S2>/EnablePI8' */

  /* Switch: '<S2>/Switch11' incorporates:
   *  Constant: '<S2>/Constant22'
   *  Inport: '<Root>/InSystemRootn'
   */
  if (rtb_VoltCtrlEnable != 0) {
    tmp = MGCCode_Ori_U.InSystemRootn.Vref;
  } else {
    tmp = 0.0F;
  }

  /* End of Switch: '<S2>/Switch11' */

  /* Product: '<S2>/Divide6' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Inport: '<Root>/InSystemRootn'
   *  Sum: '<S2>/Sum4'
   */
  rtb_Divide7_d = (tmp - MGCCode_Ori_U.InSystemRootn.Vmeas) /
    MGCCode_Ori_P.Base.Volt;

  /* Saturate: '<S2>/Saturation7' */
  if (rtb_Divide7_d >= 2.0F) {
    rtb_Saturation7 = 2.0F;
  } else if (rtb_Divide7_d <= -2.0F) {
    rtb_Saturation7 = -2.0F;
  } else {
    rtb_Saturation7 = rtb_Divide7_d;
  }

  /* End of Saturate: '<S2>/Saturation7' */

  /* Outputs for Enabled SubSystem: '<S2>/EnablePI5' */
  MGCCode_Ori_EnablePI5(rtb_VoltCtrlEnable, rtb_Saturation7,
                        MGCCode_Ori_ConstB.Constant26, &MGCCode_Ori_B.EnablePI5,
                        &MGCCode_Ori_DWork.EnablePI5,
                        StructPointer->CtrlParamAVC.VoltPIGain,
                        StructPointer->CtrlParamAVC.VoltPILowerSat,
                        StructPointer->CtrlParamAVC.VoltPIUpperSat,
                        StructPointer->CtrlParamAVC.VoltPIIntegral);

  /* End of Outputs for SubSystem: '<S2>/EnablePI5' */

  /* Switch: '<S2>/Switch7' incorporates:
   *  Constant: '<S2>/Constant15'
   *  Logic: '<S2>/Logical Operator1'
   */
  if ((rtb_LineQEnable != 0) || (rtb_VoltCtrlEnable != 0)) {
    /* Switch: '<S2>/Switch4' incorporates:
     *  Constant: '<S2>/Constant18'
     *  Inport: '<Root>/InSystemRootn'
     *  Product: '<S2>/Divide7'
     *  Sum: '<S2>/Sum12'
     */
    if (rtb_LineQEnable != 0) {
      rtb_Sum_n = (MGCCode_Ori_U.InSystemRootn.LineQref -
                   MGCCode_Ori_U.InSystemRootn.LineQ) / rtb_Sum3;
    } else {
      rtb_Sum_n = 0.0F;
    }

    /* End of Switch: '<S2>/Switch4' */

    /* Switch: '<S2>/Switch2' */
    if (rtb_AVCSwitch != 0) {
      rtb_Divide7_d = MGCCode_Ori_B.EnablePI8.Saturation;
    } else {
      rtb_Divide7_d = MGCCode_Ori_B.EnablePI5.Saturation;
    }

    /* End of Switch: '<S2>/Switch2' */

    /* Sum: '<S2>/Sum8' incorporates:
     *  Sum: '<S2>/Sum10'
     */
    rtb_AGCRatio = (rtb_AVCRatio + rtb_Sum_n) + rtb_Divide7_d;

    /* Saturate: '<S2>/Saturation1' */
    if (rtb_AGCRatio >= 1.0F) {
      rtb_AGCRatio = 1.0F;
    } else {
      if (rtb_AGCRatio <= 0.0F) {
        rtb_AGCRatio = 0.0F;
      }
    }

    /* End of Saturate: '<S2>/Saturation1' */
  } else {
    rtb_AGCRatio = 0.0F;
  }

  /* End of Switch: '<S2>/Switch7' */

  /* Product: '<S23>/Divide7' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Divide7_d = MGCCode_Ori_U.InBatn.BatSQout / rtb_Divide5;

  /* Sum: '<S25>/Sum5' */
  rtb_Sum5 = rtb_AGCRatio - rtb_Divide7_d;

  /* Outputs for Enabled SubSystem: '<S25>/EnablePI2' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect.AVCInnerEnable, rtb_Sum5,
                        0.0F, MGCCode_Ori_ConstB.Constant5,
                        &MGCCode_Ori_B.EnablePI2, &MGCCode_Ori_DWork.EnablePI2,
                        StructPointer->CtrlParamBat.AVCInnerPIGain,
                        StructPointer->CtrlParamBat.AVCInnerPILowerSat,
                        StructPointer->CtrlParamBat.AVCInnerPIUpperSat,
                        StructPointer->CtrlParamBat.AVCInnerPIIntegral);

  /* End of Outputs for SubSystem: '<S25>/EnablePI2' */

  /* Product: '<S23>/Divide2' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Sum_n = MGCCode_Ori_U.InBatn.BatSQref / rtb_Divide5;

  /* Saturate: '<S23>/Saturation2' */
  if (rtb_Sum_n >= 1.0F) {
    rtb_Sum_n = 1.0F;
  } else {
    if (rtb_Sum_n <= -1.0F) {
      rtb_Sum_n = -1.0F;
    }
  }

  /* End of Saturate: '<S23>/Saturation2' */

  /* Sum: '<S25>/Sum6' */
  rtb_Sum6 = rtb_Sum_n - rtb_Divide7_d;

  /* Outputs for Enabled SubSystem: '<S25>/EnablePI3' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect.ConstQEnable, rtb_Sum6, 0.0F,
                        MGCCode_Ori_ConstB.Constant3, &MGCCode_Ori_B.EnablePI3,
                        &MGCCode_Ori_DWork.EnablePI3,
                        StructPointer->CtrlParamBat.ConstQPIGain,
                        StructPointer->CtrlParamBat.ConstQPILowerSat,
                        StructPointer->CtrlParamBat.ConstQPIUpperSat,
                        StructPointer->CtrlParamBat.ConstQPIIntegral);

  /* End of Outputs for SubSystem: '<S25>/EnablePI3' */

  /* Switch: '<S25>/Switch3' incorporates:
   *  Constant: '<S25>/Constant1'
   *  Logic: '<S25>/Logical Operator1'
   */
  if ((MGCCode_Ori_B.sf_ModeSelect.AVCInnerEnable != 0) ||
      (MGCCode_Ori_B.sf_ModeSelect.ConstQEnable != 0)) {
    /* Switch: '<S25>/Switch2' incorporates:
     *  Sum: '<S25>/Add2'
     *  Sum: '<S25>/Add3'
     */
    if (MGCCode_Ori_B.sf_ModeSelect.QCtrlSwitch != 0) {
      rtb_Sum_n = rtb_AGCRatio + MGCCode_Ori_B.EnablePI2.Saturation;
    } else {
      rtb_Sum_n += MGCCode_Ori_B.EnablePI3.Saturation;
    }

    /* End of Switch: '<S25>/Switch2' */

    /* Saturate: '<S25>/Saturation2' */
    if (rtb_Sum_n >= 1.0F) {
      rtb_Pmax = 1.0F;
    } else if (rtb_Sum_n <= -0.5F) {
      rtb_Pmax = -0.5F;
    } else {
      rtb_Pmax = rtb_Sum_n;
    }

    /* End of Saturate: '<S25>/Saturation2' */
  } else {
    rtb_Pmax = 0.0F;
  }

  /* End of Switch: '<S25>/Switch3' */

  /* Outport: '<Root>/OutBatn' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutBatn_at_inport_0'
   *  Product: '<S24>/Product1'
   */
  MGCCode_Ori_Y.OutBatn.BatSPcmd = rtb_Fref;
  MGCCode_Ori_Y.OutBatn.BatSQcmd = rtb_Divide5 * rtb_Pmax;

  /* Product: '<S48>/Divide5' incorporates:
   *  Constant: '<S48>/Constant3'
   *  Inport: '<Root>/InPVn'
   */
  rtb_Divide5 = MGCCode_Ori_U.InPVn.PVSPout / MGCCode_Ori_P.Base.PV;

  /* Sum: '<S50>/Sum' */
  rtb_Sum_m = rtb_AGCref - rtb_Divide5;

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator9_at_inport_1' */
  rtb_SystemModen_nzs = MGCCode_Ori_B.OutEMS_c.SystemModen;
  rtb_PVMode_a11 = MGCCode_Ori_B.OutEMS_c.PVMode;

  /* MATLAB Function: '<S50>/ModeSelect' */
  MGCCode_Ori_ModeSelect(rtb_SystemModen_nzs, rtb_PVMode_a11,
    &MGCCode_Ori_B.sf_ModeSelect_d);

  /* Outputs for Enabled SubSystem: '<S50>/EnablePI' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect_d.AGCInnerEnable, rtb_Sum_m,
                        0.0F, MGCCode_Ori_ConstB.Constant4_p,
                        &MGCCode_Ori_B.EnablePI_g, &MGCCode_Ori_DWork.EnablePI_g,
                        StructPointer->CtrlParamPV.AGCInnerPIGain,
                        StructPointer->CtrlParamPV.AGCInnerPILowerSat,
                        StructPointer->CtrlParamPV.AGCInnerPIUpperSat,
                        StructPointer->CtrlParamPV.AGCInnerPIIntegral);

  /* End of Outputs for SubSystem: '<S50>/EnablePI' */

  /* Product: '<S48>/Divide7' incorporates:
   *  Constant: '<S48>/Constant3'
   *  Inport: '<Root>/InPVn'
   */
  rtb_Sum_n = MGCCode_Ori_U.InPVn.PVSPref / MGCCode_Ori_P.Base.PV;

  /* Saturate: '<S48>/Saturation1' */
  if (rtb_Sum_n >= 1.0F) {
    rtb_Sum_n = 1.0F;
  } else {
    if (rtb_Sum_n <= 0.0F) {
      rtb_Sum_n = 0.0F;
    }
  }

  /* End of Saturate: '<S48>/Saturation1' */

  /* Sum: '<S50>/Sum1' */
  rtb_Sum1_i = rtb_Sum_n - rtb_Divide5;

  /* Outputs for Enabled SubSystem: '<S50>/EnablePI1' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect_d.ConstPEnable, rtb_Sum1_i,
                        0.0F, MGCCode_Ori_ConstB.Constant2_h,
                        &MGCCode_Ori_B.EnablePI1_o,
                        &MGCCode_Ori_DWork.EnablePI1_o,
                        StructPointer->CtrlParamPV.ConstPPIGain,
                        StructPointer->CtrlParamPV.ConstPPILowerSat,
                        StructPointer->CtrlParamPV.ConstPPIUpperSat,
                        StructPointer->CtrlParamPV.ConstPPIIntegral);

  /* End of Outputs for SubSystem: '<S50>/EnablePI1' */

  /* Switch: '<S50>/Switch1' incorporates:
   *  Constant: '<S50>/Constant'
   *  Logic: '<S50>/Logical Operator'
   */
  if ((MGCCode_Ori_B.sf_ModeSelect_d.AGCInnerEnable != 0) ||
      (MGCCode_Ori_B.sf_ModeSelect_d.ConstPEnable != 0)) {
    /* Switch: '<S50>/Switch' incorporates:
     *  Sum: '<S50>/Add'
     *  Sum: '<S50>/Add1'
     */
    if (MGCCode_Ori_B.sf_ModeSelect_d.PCtrlSwitch != 0) {
      rtb_Sum_n = MGCCode_Ori_B.EnablePI_g.Saturation + rtb_AGCref;
    } else {
      rtb_Sum_n += MGCCode_Ori_B.EnablePI1_o.Saturation;
    }

    /* End of Switch: '<S50>/Switch' */

    /* Saturate: '<S50>/Saturation' */
    if (rtb_Sum_n >= 1.0F) {
      rtb_Pmax = 1.0F;
    } else if (rtb_Sum_n <= 0.0F) {
      rtb_Pmax = 0.0F;
    } else {
      rtb_Pmax = rtb_Sum_n;
    }

    /* End of Saturate: '<S50>/Saturation' */
  } else {
    rtb_Pmax = 0.0F;
  }

  /* End of Switch: '<S50>/Switch1' */

  /* Product: '<S49>/Product' incorporates:
   *  Constant: '<S48>/Constant3'
   */
  rtb_Fref = rtb_Pmax * MGCCode_Ori_P.Base.PV;

  /* Product: '<S48>/Divide2' incorporates:
   *  Inport: '<Root>/InPVn'
   */
  rtb_Pmax = MGCCode_Ori_U.InPVn.PVSQout / rtb_DFIG1SPcmd;

  /* Sum: '<S50>/Sum5' */
  rtb_Sum5_d = rtb_AGCRatio - rtb_Pmax;

  /* Outputs for Enabled SubSystem: '<S50>/EnablePI2' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect_d.AVCInnerEnable, rtb_Sum5_d,
                        0.0F, MGCCode_Ori_ConstB.Constant5_k,
                        &MGCCode_Ori_B.EnablePI2_b,
                        &MGCCode_Ori_DWork.EnablePI2_b,
                        StructPointer->CtrlParamPV.AVCInnerPIGain,
                        StructPointer->CtrlParamPV.AVCInnerPILowerSat,
                        StructPointer->CtrlParamPV.AVCInnerPIUpperSat,
                        StructPointer->CtrlParamPV.AVCInnerPIIntegral);

  /* End of Outputs for SubSystem: '<S50>/EnablePI2' */

  /* Product: '<S48>/Divide1' incorporates:
   *  Inport: '<Root>/InPVn'
   */
  rtb_Sum_n = MGCCode_Ori_U.InPVn.PVSQref / rtb_DFIG1SPcmd;

  /* Saturate: '<S48>/Saturation2' */
  if (rtb_Sum_n >= 1.0F) {
    rtb_Sum_n = 1.0F;
  } else {
    if (rtb_Sum_n <= 0.0F) {
      rtb_Sum_n = 0.0F;
    }
  }

  /* End of Saturate: '<S48>/Saturation2' */

  /* Sum: '<S50>/Sum6' */
  rtb_Sum6_b = rtb_Sum_n - rtb_Pmax;

  /* Outputs for Enabled SubSystem: '<S50>/EnablePI3' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect_d.ConstQEnable, rtb_Sum6_b,
                        0.0F, MGCCode_Ori_ConstB.Constant3_d,
                        &MGCCode_Ori_B.EnablePI3_l,
                        &MGCCode_Ori_DWork.EnablePI3_l,
                        StructPointer->CtrlParamPV.ConstQPIGain,
                        StructPointer->CtrlParamPV.ConstQPILowerSat,
                        StructPointer->CtrlParamPV.ConstQPIUpperSat,
                        StructPointer->CtrlParamPV.ConstQPIIntegral);

  /* End of Outputs for SubSystem: '<S50>/EnablePI3' */

  /* Switch: '<S50>/Switch3' incorporates:
   *  Constant: '<S50>/Constant1'
   *  Logic: '<S50>/Logical Operator1'
   */
  if ((MGCCode_Ori_B.sf_ModeSelect_d.AVCInnerEnable != 0) ||
      (MGCCode_Ori_B.sf_ModeSelect_d.ConstQEnable != 0)) {
    /* Switch: '<S50>/Switch2' incorporates:
     *  Sum: '<S50>/Add2'
     *  Sum: '<S50>/Add3'
     */
    if (MGCCode_Ori_B.sf_ModeSelect_d.QCtrlSwitch != 0) {
      rtb_Sum_n = MGCCode_Ori_B.EnablePI2_b.Saturation + rtb_AGCRatio;
    } else {
      rtb_Sum_n += MGCCode_Ori_B.EnablePI3_l.Saturation;
    }

    /* End of Switch: '<S50>/Switch2' */

    /* Saturate: '<S50>/Saturation2' */
    if (rtb_Sum_n >= 1.0F) {
      rtb_Divide2 = 1.0F;
    } else if (rtb_Sum_n <= -0.5F) {
      rtb_Divide2 = -0.5F;
    } else {
      rtb_Divide2 = rtb_Sum_n;
    }

    /* End of Saturate: '<S50>/Saturation2' */
  } else {
    rtb_Divide2 = 0.0F;
  }

  /* End of Switch: '<S50>/Switch3' */

  /* Outport: '<Root>/OutPVn' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutPVn_at_inport_0'
   *  Product: '<S49>/Product1'
   */
  MGCCode_Ori_Y.OutPVn.PVSPcmd = rtb_Fref;
  MGCCode_Ori_Y.OutPVn.PVSQcmd = rtb_DFIG1SPcmd * rtb_Divide2;

  /* Product: '<S37>/Divide2' incorporates:
   *  Constant: '<S37>/Constant1'
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Divide2 = MGCCode_Ori_U.InDFIG1n.DFIG1SPout / MGCCode_Ori_P.Base.DFIG1;

  /* Sum: '<S38>/Sum2' */
  rtb_Sum2_l = rtb_AGCref - rtb_Divide2;

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator8_at_inport_1' */
  rtb_SystemModen_nzsd = MGCCode_Ori_B.OutEMS_c.SystemModen;
  rtb_DFIG1Mode_loxt = MGCCode_Ori_B.OutEMS_c.DFIG1Mode;

  /* MATLAB Function: '<S38>/ModeSelect1' */
  MGCCode_Ori_ModeSelect(rtb_SystemModen_nzsd, rtb_DFIG1Mode_loxt,
    &MGCCode_Ori_B.sf_ModeSelect1_l);

  /* Outputs for Enabled SubSystem: '<S38>/EnablePI' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect1_l.AGCInnerEnable,
                        rtb_Sum2_l, 0.0F, MGCCode_Ori_ConstB.Constant4_f,
                        &MGCCode_Ori_B.EnablePI_b, &MGCCode_Ori_DWork.EnablePI_b,
                        StructPointer->CtrlParamDFIG1.AGCInnerPIGain,
                        StructPointer->CtrlParamDFIG1.AGCInnerPILowerSat,
                        StructPointer->CtrlParamDFIG1.AGCInnerPIUpperSat,
                        StructPointer->CtrlParamDFIG1.AGCInnerPIIntegral);

  /* End of Outputs for SubSystem: '<S38>/EnablePI' */

  /* Product: '<S37>/Divide5' incorporates:
   *  Constant: '<S37>/Constant1'
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Sum_n = MGCCode_Ori_U.InDFIG1n.DFIG1SPref / MGCCode_Ori_P.Base.DFIG1;

  /* Saturate: '<S37>/Saturation1' */
  if (rtb_Sum_n >= 1.0F) {
    rtb_Sum_n = 1.0F;
  } else {
    if (rtb_Sum_n <= 0.0F) {
      rtb_Sum_n = 0.0F;
    }
  }

  /* End of Saturate: '<S37>/Saturation1' */

  /* Sum: '<S38>/Sum3' */
  rtb_Sum3_b = rtb_Sum_n - rtb_Divide2;

  /* Outputs for Enabled SubSystem: '<S38>/EnablePI5' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect1_l.ConstPEnable, rtb_Sum3_b,
                        0.0F, MGCCode_Ori_ConstB.Constant2_m,
                        &MGCCode_Ori_B.EnablePI5_p,
                        &MGCCode_Ori_DWork.EnablePI5_p,
                        StructPointer->CtrlParamDFIG1.ConstPPIGain,
                        StructPointer->CtrlParamDFIG1.ConstPPILowerSat,
                        StructPointer->CtrlParamDFIG1.ConstPPIUpperSat,
                        StructPointer->CtrlParamDFIG1.ConstPPIIntegral);

  /* End of Outputs for SubSystem: '<S38>/EnablePI5' */

  /* Switch: '<S38>/Switch3' incorporates:
   *  Constant: '<S38>/Constant'
   *  Logic: '<S38>/Logical Operator'
   */
  if ((MGCCode_Ori_B.sf_ModeSelect1_l.AGCInnerEnable != 0) ||
      (MGCCode_Ori_B.sf_ModeSelect1_l.ConstPEnable != 0)) {
    /* Switch: '<S38>/Switch1' incorporates:
     *  Sum: '<S38>/Add'
     *  Sum: '<S38>/Add1'
     */
    if (MGCCode_Ori_B.sf_ModeSelect1_l.PCtrlSwitch != 0) {
      rtb_Sum_n = MGCCode_Ori_B.EnablePI_b.Saturation + rtb_AGCref;
    } else {
      rtb_Sum_n += MGCCode_Ori_B.EnablePI5_p.Saturation;
    }

    /* End of Switch: '<S38>/Switch1' */

    /* Saturate: '<S38>/Saturation1' */
    if (rtb_Sum_n >= 1.0F) {
      rtb_DFIG1SPcmd = 1.0F;
    } else if (rtb_Sum_n <= 0.0F) {
      rtb_DFIG1SPcmd = 0.0F;
    } else {
      rtb_DFIG1SPcmd = rtb_Sum_n;
    }

    /* End of Saturate: '<S38>/Saturation1' */
  } else {
    rtb_DFIG1SPcmd = 0.0F;
  }

  /* End of Switch: '<S38>/Switch3' */

  /* Product: '<S36>/Product2' incorporates:
   *  Constant: '<S37>/Constant1'
   */
  rtb_DFIG1SPcmd *= MGCCode_Ori_P.Base.DFIG1;

  /* Product: '<S37>/Divide7' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Divide7_p = MGCCode_Ori_U.InDFIG1n.DFIG1SQout / rtb_DFIG1SQcmd;

  /* Sum: '<S38>/Sum4' */
  rtb_Sum4_i = rtb_AGCRatio - rtb_Divide7_p;

  /* Outputs for Enabled SubSystem: '<S38>/EnablePI6' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect1_l.AVCInnerEnable,
                        rtb_Sum4_i, 0.0F, MGCCode_Ori_ConstB.Constant5_a,
                        &MGCCode_Ori_B.EnablePI6, &MGCCode_Ori_DWork.EnablePI6,
                        StructPointer->CtrlParamDFIG1.AVCInnerPIGain,
                        StructPointer->CtrlParamDFIG1.AVCInnerPILowerSat,
                        StructPointer->CtrlParamDFIG1.AVCInnerPIUpperSat,
                        StructPointer->CtrlParamDFIG1.AVCInnerPIIntegral);

  /* End of Outputs for SubSystem: '<S38>/EnablePI6' */

  /* Product: '<S37>/Divide1' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Sum_n = MGCCode_Ori_U.InDFIG1n.DFIG1SQref / rtb_DFIG1SQcmd;

  /* Saturate: '<S37>/Saturation2' */
  if (rtb_Sum_n >= 1.0F) {
    rtb_Sum_n = 1.0F;
  } else {
    if (rtb_Sum_n <= 0.0F) {
      rtb_Sum_n = 0.0F;
    }
  }

  /* End of Saturate: '<S37>/Saturation2' */

  /* Sum: '<S38>/Sum7' */
  rtb_Sum7 = rtb_Sum_n - rtb_Divide7_p;

  /* Outputs for Enabled SubSystem: '<S38>/EnablePI7' */
  MGCCode_Ori_EnablePI1(MGCCode_Ori_B.sf_ModeSelect1_l.ConstQEnable, rtb_Sum7,
                        0.0F, MGCCode_Ori_ConstB.Constant3_n,
                        &MGCCode_Ori_B.EnablePI7, &MGCCode_Ori_DWork.EnablePI7,
                        StructPointer->CtrlParamDFIG1.ConstQPIGain,
                        StructPointer->CtrlParamDFIG1.ConstQPILowerSat,
                        StructPointer->CtrlParamDFIG1.ConstQPIUpperSat,
                        StructPointer->CtrlParamDFIG1.ConstQPIIntegral);

  /* End of Outputs for SubSystem: '<S38>/EnablePI7' */

  /* Switch: '<S38>/Switch5' incorporates:
   *  Constant: '<S38>/Constant1'
   *  Logic: '<S38>/Logical Operator1'
   */
  if ((MGCCode_Ori_B.sf_ModeSelect1_l.AVCInnerEnable != 0) ||
      (MGCCode_Ori_B.sf_ModeSelect1_l.ConstQEnable != 0)) {
    /* Switch: '<S38>/Switch4' incorporates:
     *  Sum: '<S38>/Add2'
     *  Sum: '<S38>/Add3'
     */
    if (MGCCode_Ori_B.sf_ModeSelect1_l.QCtrlSwitch != 0) {
      rtb_Sum_n = MGCCode_Ori_B.EnablePI6.Saturation + rtb_AGCRatio;
    } else {
      rtb_Sum_n += MGCCode_Ori_B.EnablePI7.Saturation;
    }

    /* End of Switch: '<S38>/Switch4' */

    /* Saturate: '<S38>/Saturation3' */
    if (rtb_Sum_n >= 1.0F) {
      rtb_Sum_n = 1.0F;
    } else {
      if (rtb_Sum_n <= -0.5F) {
        rtb_Sum_n = -0.5F;
      }
    }

    /* End of Saturate: '<S38>/Saturation3' */
  } else {
    rtb_Sum_n = 0.0F;
  }

  /* End of Switch: '<S38>/Switch5' */

  /* Product: '<S36>/Product3' */
  rtb_DFIG1SQcmd *= rtb_Sum_n;

  /* Outport: '<Root>/OutDFIG1n' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutDFIG1n_at_inport_0'
   */
  MGCCode_Ori_Y.OutDFIG1n.DFIG1SPcmd = rtb_DFIG1SPcmd;
  MGCCode_Ori_Y.OutDFIG1n.DFIG1SQcmd = rtb_DFIG1SQcmd;

  /* Outport: '<Root>/OutDFIG2n' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutDFIG2n_at_inport_0'
   */
  MGCCode_Ori_Y.OutDFIG2n.DFIG1SPcmd = rtb_DFIG1SPcmd;
  MGCCode_Ori_Y.OutDFIG2n.DFIG1SQcmd = rtb_DFIG1SQcmd;

  /* Outport: '<Root>/Observen' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_Observen_at_inport_0'
   */
  MGCCode_Ori_Y.Observen.AGCref = rtb_AGCref;
  MGCCode_Ori_Y.Observen.AVCRef = rtb_AGCRatio;
  MGCCode_Ori_Y.Observen.ICEPout = 0.0F;
  MGCCode_Ori_Y.Observen.ICEQout = 0.0F;
  MGCCode_Ori_Y.Observen.BatPout = rtb_Divide5_g;
  MGCCode_Ori_Y.Observen.BatQout = rtb_Divide7_d;
  MGCCode_Ori_Y.Observen.PVPout = rtb_Divide5;
  MGCCode_Ori_Y.Observen.PVQout = rtb_Pmax;
  MGCCode_Ori_Y.Observen.DFIG1Pout = rtb_Divide2;
  MGCCode_Ori_Y.Observen.DFIG1Qout = rtb_Divide7_p;
  MGCCode_Ori_Y.Observen.Omegagen = 0.0F;

  /* Outport: '<Root>/Param' incorporates:
   *  Constant: '<S1>/Constant'
   */
  MGCCode_Ori_Y.Param = StructPointer->CtrlParamICE.AVCInnerPIGain;

  /* Outport: '<Root>/LineP' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   *  Sum: '<S5>/Sum'
   */
  MGCCode_Ori_Y.LineP = (((MGCCode_Ori_U.InICEn.ICESPout +
    MGCCode_Ori_U.InBatn.BatSPout) + MGCCode_Ori_U.InPVn.PVSPout) +
    MGCCode_Ori_U.InDFIG1n.DFIG1SPout) - MGCCode_Ori_P.Base.LoadP;

  /* Outport: '<Root>/LineQ' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   *  Sum: '<S5>/Sum1'
   */
  MGCCode_Ori_Y.LineQ = (((MGCCode_Ori_U.InICEn.ICESQout +
    MGCCode_Ori_U.InBatn.BatSQout) + MGCCode_Ori_U.InPVn.PVSQout) +
    MGCCode_Ori_U.InDFIG1n.DFIG1SQout) - MGCCode_Ori_P.Base.LoadQ;

  /* Update for RateTransition: '<S1>/Rate Transition1' incorporates:
   *  Update for Inport: '<Root>/InEMSRootn'
   */
  if (MGCCode_Ori_M->Timing.TaskCounters.TID[1] == 0) {
    MGCCode_Ori_DWork.RateTransition1_1_Buffer0 =
      MGCCode_Ori_U.InEMSRootn.SystemModen;

    /* Update for RateTransition: '<S1>/Rate Transition1' incorporates:
     *  Update for Inport: '<Root>/InEMSRootn'
     */
    MGCCode_Ori_DWork.RateTransition1_2_Buffer0 =
      MGCCode_Ori_U.InEMSRootn.ICEMode;

    /* Update for RateTransition: '<S1>/Rate Transition1' incorporates:
     *  Update for Inport: '<Root>/InEMSRootn'
     */
    MGCCode_Ori_DWork.RateTransition1_3_Buffer0 =
      MGCCode_Ori_U.InEMSRootn.BatMode;

    /* Update for RateTransition: '<S1>/Rate Transition1' incorporates:
     *  Update for Inport: '<Root>/InEMSRootn'
     */
    MGCCode_Ori_DWork.RateTransition1_4_Buffer0 =
      MGCCode_Ori_U.InEMSRootn.PVMode;

    /* Update for RateTransition: '<S1>/Rate Transition1' incorporates:
     *  Update for Inport: '<Root>/InEMSRootn'
     */
    MGCCode_Ori_DWork.RateTransition1_5_Buffer0 =
      MGCCode_Ori_U.InEMSRootn.DFIG1Mode;

    /* Update for RateTransition: '<S1>/Rate Transition1' incorporates:
     *  Update for Inport: '<Root>/InEMSRootn'
     */
    MGCCode_Ori_DWork.RateTransition1_6_Buffer0 =
      MGCCode_Ori_U.InEMSRootn.DFIG2Mode;
  }

  /* End of Update for RateTransition: '<S1>/Rate Transition1' */
  rate_scheduler();
}

/* Model initialize function */
void MGCCode_Ori_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)MGCCode_Ori_M, 0,
                sizeof(RT_MODEL_MGCCode_Ori));

  /* block I/O */
  (void) memset(((void *) &MGCCode_Ori_B), 0,
                sizeof(BlockIO_MGCCode_Ori));

  {
    MGCCode_Ori_B.BusConversion_InsertedFor_Mi_l4 = MGCCode_Ori_rtZInEMS;
    MGCCode_Ori_B.OutEMS_c = MGCCode_Ori_rtZOutEMS;
    MGCCode_Ori_B.SystemModen = Start;
    MGCCode_Ori_B.ICEMode = ConstPQ;
    MGCCode_Ori_B.BatMode = ConstPQ;
    MGCCode_Ori_B.PVMode = ConstPQ;
    MGCCode_Ori_B.DFIG1Mode = ConstPQ;
    MGCCode_Ori_B.DFIG2Mode = ConstPQ;
  }

  /* states (dwork) */
  (void) memset((void *)&MGCCode_Ori_DWork, 0,
                sizeof(D_Work_MGCCode_Ori));

  /* external inputs */
  (void) memset((void *)&MGCCode_Ori_U, 0,
                sizeof(ExternalInputs_MGCCode_Ori));
  MGCCode_Ori_U.InEMSRootn = MGCCode_Ori_rtZInEMSRoot;

  /* external outputs */
  (void) memset((void *)&MGCCode_Ori_Y, 0,
                sizeof(ExternalOutputs_MGCCode_Ori));
  MGCCode_Ori_Y.Warningn = None;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_B.ICEMode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_B.BatMode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_B.PVMode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_B.DFIG1Mode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_B.DFIG2Mode = ConstPQ;

  /* Start for Enabled SubSystem: '<S2>/EnablePI1' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant23,
    &MGCCode_Ori_DWork.EnablePI1);

  /* End of Start for SubSystem: '<S2>/EnablePI1' */

  /* Start for Enabled SubSystem: '<S2>/EnablePI4' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant24,
    &MGCCode_Ori_DWork.EnablePI4);

  /* End of Start for SubSystem: '<S2>/EnablePI4' */

  /* Start for Enabled SubSystem: '<S25>/EnablePI' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant4,
    &MGCCode_Ori_DWork.EnablePI);

  /* End of Start for SubSystem: '<S25>/EnablePI' */

  /* Start for Enabled SubSystem: '<S25>/EnablePI1' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant2,
    &MGCCode_Ori_DWork.EnablePI1_m);

  /* End of Start for SubSystem: '<S25>/EnablePI1' */

  /* Start for Enabled SubSystem: '<S2>/EnablePI8' */
  MGCCode_Ori_EnablePI5_Start(MGCCode_Ori_ConstB.Constant25,
    &MGCCode_Ori_DWork.EnablePI8);

  /* End of Start for SubSystem: '<S2>/EnablePI8' */

  /* Start for Enabled SubSystem: '<S2>/EnablePI5' */
  MGCCode_Ori_EnablePI5_Start(MGCCode_Ori_ConstB.Constant26,
    &MGCCode_Ori_DWork.EnablePI5);

  /* End of Start for SubSystem: '<S2>/EnablePI5' */

  /* Start for Enabled SubSystem: '<S25>/EnablePI2' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant5,
    &MGCCode_Ori_DWork.EnablePI2);

  /* End of Start for SubSystem: '<S25>/EnablePI2' */

  /* Start for Enabled SubSystem: '<S25>/EnablePI3' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant3,
    &MGCCode_Ori_DWork.EnablePI3);

  /* End of Start for SubSystem: '<S25>/EnablePI3' */

  /* Start for Enabled SubSystem: '<S50>/EnablePI' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant4_p,
    &MGCCode_Ori_DWork.EnablePI_g);

  /* End of Start for SubSystem: '<S50>/EnablePI' */

  /* Start for Enabled SubSystem: '<S50>/EnablePI1' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant2_h,
    &MGCCode_Ori_DWork.EnablePI1_o);

  /* End of Start for SubSystem: '<S50>/EnablePI1' */

  /* Start for Enabled SubSystem: '<S50>/EnablePI2' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant5_k,
    &MGCCode_Ori_DWork.EnablePI2_b);

  /* End of Start for SubSystem: '<S50>/EnablePI2' */

  /* Start for Enabled SubSystem: '<S50>/EnablePI3' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant3_d,
    &MGCCode_Ori_DWork.EnablePI3_l);

  /* End of Start for SubSystem: '<S50>/EnablePI3' */

  /* Start for Enabled SubSystem: '<S38>/EnablePI' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant4_f,
    &MGCCode_Ori_DWork.EnablePI_b);

  /* End of Start for SubSystem: '<S38>/EnablePI' */

  /* Start for Enabled SubSystem: '<S38>/EnablePI5' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant2_m,
    &MGCCode_Ori_DWork.EnablePI5_p);

  /* End of Start for SubSystem: '<S38>/EnablePI5' */

  /* Start for Enabled SubSystem: '<S38>/EnablePI6' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant5_a,
    &MGCCode_Ori_DWork.EnablePI6);

  /* End of Start for SubSystem: '<S38>/EnablePI6' */

  /* Start for Enabled SubSystem: '<S38>/EnablePI7' */
  MGCCode_Ori_EnablePI1_Start(MGCCode_Ori_ConstB.Constant3_n,
    &MGCCode_Ori_DWork.EnablePI7);

  /* End of Start for SubSystem: '<S38>/EnablePI7' */

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_DWork.RateTransition1_2_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_DWork.RateTransition1_3_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_DWork.RateTransition1_4_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_DWork.RateTransition1_5_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_Ori_DWork.RateTransition1_6_Buffer0 = ConstPQ;

  /* InitializeConditions for Chart: '<S1>/MicrogridModelManager' */
  MGCCode_Ori_DWork.is_Logic = MGCCode_Ori_IN_NO_ACTIVE_CHILD;
  MGCCode_Ori_DWork.is_GridOperation = MGCCode_Ori_IN_NO_ACTIVE_CHILD;
  MGCCode_Ori_DWork.temporalCounter_i1 = 0UL;
  MGCCode_Ori_DWork.is_IslandOperation = MGCCode_Ori_IN_NO_ACTIVE_CHILD;
  MGCCode_Ori_DWork.temporalCounter_i2 = 0UL;
  MGCCode_Ori_DWork.temporalCounter_i3 = 0U;
  MGCCode_Ori_DWork.is_active_c15_MGCCode_Ori = 0U;
  MGCCode_Ori_DWork.is_c15_MGCCode_Ori = MGCCode_Ori_IN_NO_ACTIVE_CHILD;
  MGCCode_Ori_DWork.count = 0.0F;
  MGCCode_Ori_DWork.PassiveIslandSignal = 0.0F;
  MGCCode_Ori_DWork.Pload = 0.0F;
  MGCCode_Ori_DWork.IslandCount = 0.0F;
  MGCCode_Ori_DWork.IslandFailCount = 0.0F;
  MGCCode_Ori_DWork.GridFailCount = 0.0F;
  MGCCode_Ori_DWork.GridCount = 0.0F;
  MGCCode_Ori_B.OutEMS_c.SystemModen = Start;
  MGCCode_Ori_B.OutEMS_c.ICEMode = ConstPQ;
  MGCCode_Ori_B.OutEMS_c.BatMode = ConstPQ;
  MGCCode_Ori_B.OutEMS_c.PVMode = ConstPQ;
  MGCCode_Ori_B.OutEMS_c.DFIG1Mode = ConstPQ;
  MGCCode_Ori_B.OutEMS_c.DFIG2Mode = ConstPQ;
  MGCCode_Ori_B.OutSystem_k.LinePref = 0.0F;
  MGCCode_Ori_B.OutSystem_k.Fref = 0.0F;
  MGCCode_Ori_B.OutSystem_k.LineQref = 0.0F;
  MGCCode_Ori_B.OutSystem_k.Vref = 0.0F;

  /* InitializeConditions for Outport: '<Root>/Islandsignal' incorporates:
   *  InitializeConditions for Chart: '<S1>/MicrogridModelManager'
   */
  MGCCode_Ori_Y.Islandsignal = FALSE;

  /* InitializeConditions for Outport: '<Root>/Warningn ' incorporates:
   *  InitializeConditions for Chart: '<S1>/MicrogridModelManager'
   */
  MGCCode_Ori_Y.Warningn = None;

  /* InitializeConditions for Chart: '<S1>/MicrogridModelManager' */
  MGCCode_Ori_Y.EmergencyControl.Pre_LinePowerCmd = 0.0F;
  MGCCode_Ori_Y.EmergencyControl.Pre_LoadShedding = 0.0F;
  MGCCode_Ori_Y.EmergencyControl.Pre_Pclear = 0.0F;
  MGCCode_Ori_Y.EmergencyControl.Pre_CutEn = FALSE;
  MGCCode_Ori_Y.EmergencyControl.EC_Pclear = 0.0F;
  MGCCode_Ori_Y.EmergencyControl.Pre_IslandLoadShedding = 0.0F;
  MGCCode_Ori_Y.EmergencyControl.Pre_IslandPclear = 0.0F;
  MGCCode_Ori_Y.EmergencyControl.Pre_IslandCutEn = FALSE;
  MGCCode_Ori_Y.EmergencyControl.EC_IslandPclear = 0.0F;

  /* InitializeConditions for Outport: '<Root>/SyncSignal ' incorporates:
   *  InitializeConditions for Chart: '<S1>/MicrogridModelManager'
   */
  MGCCode_Ori_Y.SyncSignal = FALSE;
}

/* Model terminate function */
void MGCCode_Ori_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
