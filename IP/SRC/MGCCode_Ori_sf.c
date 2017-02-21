/*
 * MGCCode_Ori_sf.c
 *
 * This file contains a "wrapper style S-Function" for testing the generated
 * code from Simulink.  Simulink invokes the generated code through its
 * S-Function API.  Note that this file is not required for deployment
 * of the generated code outside of Simulink.
 *
 * Code generation for model "MGCCode_Ori".
 *
 * Model version              : 1.32
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Apr 22 10:12:50 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 */

#if !defined(S_FUNCTION_NAME)
#define S_FUNCTION_NAME                MGCCode_Ori_sf
#endif

#define S_FUNCTION_LEVEL               2

/* So mdlEnable and mdlDisable will be defined in the simstruc.h */
#if !defined(RTW_GENERATED_S_FUNCTION)
#define RTW_GENERATED_S_FUNCTION
#endif

#include <stdio.h>
#include <math.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define rt_logging_h
#define RTWSfcnInfo                    void *
#include "MGCCode_Ori.h"

static int8_T MGCCode_Ori_sf_counter = 0;

/* This function checks the attributes of tunable parameters. */
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)

static void mdlCheckParameters(SimStruct *S)
{
  /* Check attributes of parameter 'Base' */
  {
    int dimsArray[2] = { 1, 1 };

    ssCheckSFcnParamValueAttribs(S, 0, "Base", DYNAMICALLY_TYPED,
      2, dimsArray, FALSE);
  }

  /* Check attributes of parameter 'IslandParam' */
  {
    int dimsArray[2] = { 1, 1 };

    ssCheckSFcnParamValueAttribs(S, 1, "IslandParam", DYNAMICALLY_TYPED,
      2, dimsArray, FALSE);
  }

  /* Check attributes of parameter 'GridParam' */
  {
    int dimsArray[2] = { 1, 1 };

    ssCheckSFcnParamValueAttribs(S, 2, "GridParam", DYNAMICALLY_TYPED,
      2, dimsArray, FALSE);
  }
}

#endif                                 /* MDL_CHECK_PARAMETERS */

/* Copy parameter values from run-time parameters to global variables. */
static void updateGlobalVarsFromRunTimeParams(SimStruct *S)
{
  int_T i;

  /* Update parameter 'Base' */
  {
    const char * rtp_0 = ((const char *) ssGetRunTimeParamInfo(S,0)->data);
    MGCCode_Ori_P.Base.LineP = *((real32_T*)(rtp_0));
    MGCCode_Ori_P.Base.LineQ = *((real32_T*)(rtp_0 + 4));
    MGCCode_Ori_P.Base.ActivePower = *((real32_T*)(rtp_0 + 8));
    MGCCode_Ori_P.Base.ReactivePower = *((real32_T*)(rtp_0 + 12));
    MGCCode_Ori_P.Base.Freq = *((real32_T*)(rtp_0 + 16));
    MGCCode_Ori_P.Base.Volt = *((real32_T*)(rtp_0 + 20));
    MGCCode_Ori_P.Base.ICE = *((real32_T*)(rtp_0 + 24));
    MGCCode_Ori_P.Base.Bat = *((real32_T*)(rtp_0 + 28));
    MGCCode_Ori_P.Base.PV = *((real32_T*)(rtp_0 + 32));
    MGCCode_Ori_P.Base.DFIG1 = *((real32_T*)(rtp_0 + 36));
    MGCCode_Ori_P.Base.LoadP = *((real32_T*)(rtp_0 + 40));
    MGCCode_Ori_P.Base.LoadQ = *((real32_T*)(rtp_0 + 44));
    MGCCode_Ori_P.Base.AGCRatio = *((real32_T*)(rtp_0 + 48));
    MGCCode_Ori_P.Base.AVCRatio = *((real32_T*)(rtp_0 + 52));
    MGCCode_Ori_P.Base.ICEPmax = *((real32_T*)(rtp_0 + 56));
    MGCCode_Ori_P.Base.ICEQmax = *((real32_T*)(rtp_0 + 60));
    MGCCode_Ori_P.Base.BatPmax = *((real32_T*)(rtp_0 + 64));
    MGCCode_Ori_P.Base.BatQmax = *((real32_T*)(rtp_0 + 68));
    MGCCode_Ori_P.Base.DFIG1Pmax = *((real32_T*)(rtp_0 + 72));
    MGCCode_Ori_P.Base.DFIG1Qmax = *((real32_T*)(rtp_0 + 76));
    MGCCode_Ori_P.Base.PVPmax = *((real32_T*)(rtp_0 + 80));
    MGCCode_Ori_P.Base.PVPmax1 = *((real32_T*)(rtp_0 + 84));
    MGCCode_Ori_P.Base.PVQmax = *((real32_T*)(rtp_0 + 88));
    MGCCode_Ori_P.Base.Nominator = *((real32_T*)(rtp_0 + 92));
    MGCCode_Ori_P.Base.Denominator = *((real32_T*)(rtp_0 + 96));
  }

  /* Update parameter 'IslandParam' */
  {
    const char * rtp_1 = ((const char *) ssGetRunTimeParamInfo(S,1)->data);
    MGCCode_Ori_P.IslandParam.PreventiveLoadRatioUp = *((real32_T*)(rtp_1));
    MGCCode_Ori_P.IslandParam.Stage3Freq = *((real32_T*)(rtp_1 + 4));
    MGCCode_Ori_P.IslandParam.Stage3Cutting = *((real32_T*)(rtp_1 + 8));
    MGCCode_Ori_P.IslandParam.Stage2Freq = *((real32_T*)(rtp_1 + 12));
    MGCCode_Ori_P.IslandParam.Stage2Cutting = *((real32_T*)(rtp_1 + 16));
    MGCCode_Ori_P.IslandParam.ActiveGridFreq = *((real32_T*)(rtp_1 + 20));
  }

  /* Update parameter 'GridParam' */
  {
    const char * rtp_2 = ((const char *) ssGetRunTimeParamInfo(S,2)->data);
    MGCCode_Ori_P.GridParam.PreventiveLineRatioUp = *((real32_T*)(rtp_2));
    MGCCode_Ori_P.GridParam.PreventiveLoadRatioUp = *((real32_T*)(rtp_2 + 4));
    MGCCode_Ori_P.GridParam.PreventiveTotalRatioUp = *((real32_T*)(rtp_2 + 8));
    MGCCode_Ori_P.GridParam.EmergencyTotalRatioUp = *((real32_T*)(rtp_2 + 12));
  }
}

/* This function updates tunable parameter values during simulation. */
#define MDL_PROCESS_PARAMETERS
#if defined(MDL_PROCESS_PARAMETERS) && defined(MATLAB_MEX_FILE)

static void mdlProcessParameters(SimStruct *S)
{
  ssUpdateAllTunableParamsAsRunTimeParams(S);
  updateGlobalVarsFromRunTimeParams(S);
}

#endif                                 /* MDL_PROCESS_PARAMETERS */

/*
 * This function registers the input and output signal properties of the
 * generated ERT code.
 */
static void mdlInitializeSizes(SimStruct *S)
{
  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 3);
  ssFxpSetU32BitRegionCompliant(S, 1);

  /* Number of expected parameters */
  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL)) {
      return;
    }
  } else {
    return;                            /* Parameter mismatch will be reported by Simulink */
  }

  ssSetNumContStates(S, 0);
  ssSetNumDiscStates(S, 0);
  ssSetRTWGeneratedSFcn(S, 3);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 7))
    return;
  if (!ssSetInputPortVectorDimension(S, 0, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InEMSRoot",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 0, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortSampleTime(S, 0, 0.1);
  ssSetInputPortOffsetTime(S, 0, 0.0);
  if (!ssSetInputPortVectorDimension(S, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InSystemRoot",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 1, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortSampleTime(S, 1, 0.05);
  ssSetInputPortOffsetTime(S, 1, 0.0);
  if (!ssSetInputPortVectorDimension(S, 2, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InICE",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 2, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortSampleTime(S, 2, 0.05);
  ssSetInputPortOffsetTime(S, 2, 0.0);
  if (!ssSetInputPortVectorDimension(S, 3, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InBat",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 3, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortSampleTime(S, 3, 0.05);
  ssSetInputPortOffsetTime(S, 3, 0.0);
  if (!ssSetInputPortVectorDimension(S, 4, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InPV",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 4, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 4, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetInputPortSampleTime(S, 4, 0.05);
  ssSetInputPortOffsetTime(S, 4, 0.0);
  if (!ssSetInputPortVectorDimension(S, 5, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InDFIG1",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 5, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 5, 1);
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetInputPortSampleTime(S, 5, 0.05);
  ssSetInputPortOffsetTime(S, 5, 0.0);
  if (!ssSetInputPortVectorDimension(S, 6, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "InDFIG2",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetInputPortDataType(S, 6, dataTypeIdReg );
    }

#endif

  }

  ssSetBusInputAsStruct(S, 6, 1);
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  ssSetInputPortSampleTime(S, 6, 0.05);
  ssSetInputPortOffsetTime(S, 6, 0.0);

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 13))
    return;
  if (!ssSetOutputPortVectorDimension(S, 0, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "OutICE",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 0, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 0, (void *)"OutICE");
  ssSetBusOutputAsStruct(S, 0, 0);
  ssSetOutputPortSampleTime(S, 0, 0.05);
  ssSetOutputPortOffsetTime(S, 0, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "OutBat",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 1, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 1, (void *)"OutBat");
  ssSetBusOutputAsStruct(S, 1, 0);
  ssSetOutputPortSampleTime(S, 1, 0.05);
  ssSetOutputPortOffsetTime(S, 1, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 2, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "OutPV",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 2, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 2, (void *)"OutPV");
  ssSetBusOutputAsStruct(S, 2, 0);
  ssSetOutputPortSampleTime(S, 2, 0.05);
  ssSetOutputPortOffsetTime(S, 2, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 3, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "OutDFIG1",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 3, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 3, (void *)"OutDFIG1");
  ssSetBusOutputAsStruct(S, 3, 0);
  ssSetOutputPortSampleTime(S, 3, 0.05);
  ssSetOutputPortOffsetTime(S, 3, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 4, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "OutDFIG1",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 4, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 4, (void *)"OutDFIG1");
  ssSetBusOutputAsStruct(S, 4, 0);
  ssSetOutputPortSampleTime(S, 4, 0.05);
  ssSetOutputPortOffsetTime(S, 4, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 5, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 5, SS_BOOLEAN);
  }

  ssSetOutputPortSampleTime(S, 5, 0.05);
  ssSetOutputPortOffsetTime(S, 5, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 6, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "Warning",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 6, dataTypeIdReg );
    }

#endif

  }

  ssSetOutputPortSampleTime(S, 6, 0.05);
  ssSetOutputPortOffsetTime(S, 6, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 7, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "StabControl",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 7, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 7, (void *)"StabControl");
  ssSetBusOutputAsStruct(S, 7, 0);
  ssSetOutputPortSampleTime(S, 7, 0.05);
  ssSetOutputPortOffsetTime(S, 7, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 8, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {

#if defined (MATLAB_MEX_FILE)

    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(
        S,
        "Obe",
        &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID)
        return;
      ssSetOutputPortDataType(S, 8, dataTypeIdReg );
    }

#endif

  }

  ssSetBusObjectName(S, 8, (void *)"Obe");
  ssSetBusOutputAsStruct(S, 8, 0);
  ssSetOutputPortSampleTime(S, 8, 0.05);
  ssSetOutputPortOffsetTime(S, 8, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 9, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 9, SS_SINGLE);
  }

  ssSetOutputPortSampleTime(S, 9, 0.05);
  ssSetOutputPortOffsetTime(S, 9, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 10, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 10, SS_SINGLE);
  }

  ssSetOutputPortSampleTime(S, 10, 0.05);
  ssSetOutputPortOffsetTime(S, 10, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 11, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 11, SS_SINGLE);
  }

  ssSetOutputPortSampleTime(S, 11, 0.05);
  ssSetOutputPortOffsetTime(S, 11, 0.0);
  if (!ssSetOutputPortVectorDimension(S, 12, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 12, SS_BOOLEAN);
  }

  ssSetOutputPortSampleTime(S, 12, 0.05);
  ssSetOutputPortOffsetTime(S, 12, 0.0);

  /*
   * All sample times are available through ports.
   * Use port based sample times
   */
  ssSetNumSampleTimes(S, PORT_BASED_SAMPLE_TIMES);
  ssSetNumRWork(S, 0);
  ssSetNumIWork(S, 0);
  ssSetNumPWork(S, 0);
  ssSetNumModes(S, 0);
  ssSetNumNonsampledZCs(S, 0);

  /* ERT S-Function works with model reference normal mode */
  ssSetModelReferenceNormalModeSupport(S, MDL_START_AND_MDL_PROCESS_PARAMS_OK);

  /* Set SS_OPTIONS */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

/* This function registers the sample times of the generated ERT code. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  ssSetSampleTime(S, 0, 0.05);
  ssSetOffsetTime(S, 0, 0.0);
  ssSetSampleTime(S, 1, 0.1);
  ssSetOffsetTime(S, 1, 0.0);
}

/* This function registers run-time parameters for tunable parameters. */
#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)

static void mdlSetWorkWidths(SimStruct *S)
{
  /* Set number of run-time parameters */
  if (!ssSetNumRunTimeParams(S, 3))
    return;

  {
    uint32_T dtChecksum[4] = { 4282835747U, 363309455U, 3460489292U, 768905935U
    };

    DTypeId dtId = INVALID_DTYPE_ID;
    ssGetSFcnParamDataType(S, 0, &dtId);
    if (dtId == INVALID_DTYPE_ID)
      return;
    ssCheckStructParamChecksum(S, 0, dtChecksum);
    ssRegDlgParamAsRunTimeParam(S, 0, 0, "P0_Base", dtId);
    if (ssGetErrorStatus(S) != (NULL)) {
      return;
    }
  }

  {
    uint32_T dtChecksum[4] = { 1699410037U, 494348892U, 402623141U, 2992355817U
    };

    DTypeId dtId = INVALID_DTYPE_ID;
    ssGetSFcnParamDataType(S, 1, &dtId);
    if (dtId == INVALID_DTYPE_ID)
      return;
    ssCheckStructParamChecksum(S, 1, dtChecksum);
    ssRegDlgParamAsRunTimeParam(S, 1, 1, "P1_IslandParam", dtId);
    if (ssGetErrorStatus(S) != (NULL)) {
      return;
    }
  }

  {
    uint32_T dtChecksum[4] = { 2342502693U, 948994763U, 3345346859U, 3150938128U
    };

    DTypeId dtId = INVALID_DTYPE_ID;
    ssGetSFcnParamDataType(S, 2, &dtId);
    if (dtId == INVALID_DTYPE_ID)
      return;
    ssCheckStructParamChecksum(S, 2, dtChecksum);
    ssRegDlgParamAsRunTimeParam(S, 2, 2, "P2_GridParam", dtId);
    if (ssGetErrorStatus(S) != (NULL)) {
      return;
    }
  }

  updateGlobalVarsFromRunTimeParams(S);

  /* Validate checksums for user-defined data types used by this S-Function. */
  {
    const uint32_T *checksumVals;
    ssCallGetDataTypeChecksum(S, "SystemMode", &checksumVals);
    if (checksumVals[0] != 3569575952U ||
        checksumVals[1] != 2218916252U ||
        checksumVals[2] != 2612699348U ||
        checksumVals[3] != 2049672520U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'SystemMode' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "GenMode", &checksumVals);
    if (checksumVals[0] != 2152353793U ||
        checksumVals[1] != 3276879446U ||
        checksumVals[2] != 570206427U ||
        checksumVals[3] != 4145920097U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'GenMode' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InEMSRoot", &checksumVals);
    if (checksumVals[0] != 1474509092U ||
        checksumVals[1] != 3081260829U ||
        checksumVals[2] != 3115526572U ||
        checksumVals[3] != 3893754732U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InEMSRoot' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InSystemRoot", &checksumVals);
    if (checksumVals[0] != 3996679527U ||
        checksumVals[1] != 2492615257U ||
        checksumVals[2] != 2218784713U ||
        checksumVals[3] != 2752775291U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InSystemRoot' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InICE", &checksumVals);
    if (checksumVals[0] != 1308850053U ||
        checksumVals[1] != 2737171946U ||
        checksumVals[2] != 860693469U ||
        checksumVals[3] != 1036855507U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InICE' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InBat", &checksumVals);
    if (checksumVals[0] != 4184649938U ||
        checksumVals[1] != 2770418836U ||
        checksumVals[2] != 1848855274U ||
        checksumVals[3] != 227348338U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InBat' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InPV", &checksumVals);
    if (checksumVals[0] != 1308850053U ||
        checksumVals[1] != 2737171946U ||
        checksumVals[2] != 860693469U ||
        checksumVals[3] != 1036855507U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InPV' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InDFIG1", &checksumVals);
    if (checksumVals[0] != 3334488770U ||
        checksumVals[1] != 835745218U ||
        checksumVals[2] != 4236011413U ||
        checksumVals[3] != 2196782089U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InDFIG1' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InDFIG2", &checksumVals);
    if (checksumVals[0] != 754667238U ||
        checksumVals[1] != 4051345257U ||
        checksumVals[2] != 2655276805U ||
        checksumVals[3] != 24797262U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InDFIG2' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "BASE", &checksumVals);
    if (checksumVals[0] != 2670655114U ||
        checksumVals[1] != 4028327468U ||
        checksumVals[2] != 3298389879U ||
        checksumVals[3] != 3374715870U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'BASE' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "CTRLPARAMSAGC", &checksumVals);
    if (checksumVals[0] != 1091573522U ||
        checksumVals[1] != 3681035381U ||
        checksumVals[2] != 3050624018U ||
        checksumVals[3] != 1577742481U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'CTRLPARAMSAGC' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "CTRLPARAMSAVC", &checksumVals);
    if (checksumVals[0] != 1091573522U ||
        checksumVals[1] != 3681035381U ||
        checksumVals[2] != 3050624018U ||
        checksumVals[3] != 1577742481U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'CTRLPARAMSAVC' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "CTRLPARAMSBAT", &checksumVals);
    if (checksumVals[0] != 2031185785U ||
        checksumVals[1] != 3338451586U ||
        checksumVals[2] != 2227459047U ||
        checksumVals[3] != 2100951587U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'CTRLPARAMSBAT' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "OutBat", &checksumVals);
    if (checksumVals[0] != 2915191612U ||
        checksumVals[1] != 2280052566U ||
        checksumVals[2] != 3895984238U ||
        checksumVals[3] != 1059489311U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'OutBat' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "OutICE", &checksumVals);
    if (checksumVals[0] != 2915191612U ||
        checksumVals[1] != 2280052566U ||
        checksumVals[2] != 3895984238U ||
        checksumVals[3] != 1059489311U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'OutICE' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "Obe", &checksumVals);
    if (checksumVals[0] != 1787078277U ||
        checksumVals[1] != 1309493602U ||
        checksumVals[2] != 2103969242U ||
        checksumVals[3] != 887037211U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'Obe' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "CTRLPARAMSICE", &checksumVals);
    if (checksumVals[0] != 2031185785U ||
        checksumVals[1] != 3338451586U ||
        checksumVals[2] != 2227459047U ||
        checksumVals[3] != 2100951587U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'CTRLPARAMSICE' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "CTRLPARAMSDFIG1", &checksumVals);
    if (checksumVals[0] != 2031185785U ||
        checksumVals[1] != 3338451586U ||
        checksumVals[2] != 2227459047U ||
        checksumVals[3] != 2100951587U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'CTRLPARAMSDFIG1' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "OutDFIG1", &checksumVals);
    if (checksumVals[0] != 2915191612U ||
        checksumVals[1] != 2280052566U ||
        checksumVals[2] != 3895984238U ||
        checksumVals[3] != 1059489311U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'OutDFIG1' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "GRIDPARAM", &checksumVals);
    if (checksumVals[0] != 306448303U ||
        checksumVals[1] != 2287899631U ||
        checksumVals[2] != 3030697622U ||
        checksumVals[3] != 3568557005U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'GRIDPARAM' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "ISLANDPARAM", &checksumVals);
    if (checksumVals[0] != 2538856307U ||
        checksumVals[1] != 4048552281U ||
        checksumVals[2] != 1640092712U ||
        checksumVals[3] != 2742315916U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'ISLANDPARAM' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "OutEMS", &checksumVals);
    if (checksumVals[0] != 1481823974U ||
        checksumVals[1] != 3717342878U ||
        checksumVals[2] != 3926520752U ||
        checksumVals[3] != 4223668731U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'OutEMS' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "OutSystem", &checksumVals);
    if (checksumVals[0] != 1428649119U ||
        checksumVals[1] != 2291560519U ||
        checksumVals[2] != 3715134168U ||
        checksumVals[3] != 4236245040U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'OutSystem' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InEMS", &checksumVals);
    if (checksumVals[0] != 4271425398U ||
        checksumVals[1] != 3367376114U ||
        checksumVals[2] != 429982089U ||
        checksumVals[3] != 2294585540U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InEMS' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "InSystem", &checksumVals);
    if (checksumVals[0] != 4019755978U ||
        checksumVals[1] != 4196243075U ||
        checksumVals[2] != 1622581197U ||
        checksumVals[3] != 4020565341U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'InSystem' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "Warning", &checksumVals);
    if (checksumVals[0] != 2525750893U ||
        checksumVals[1] != 768262885U ||
        checksumVals[2] != 4116722689U ||
        checksumVals[3] != 2483772070U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'Warning' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "SystemRatio", &checksumVals);
    if (checksumVals[0] != 2848629000U ||
        checksumVals[1] != 364143464U ||
        checksumVals[2] != 1621704845U ||
        checksumVals[3] != 3325239337U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'SystemRatio' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "StabControl", &checksumVals);
    if (checksumVals[0] != 444053693U ||
        checksumVals[1] != 2972108061U ||
        checksumVals[2] != 867166163U ||
        checksumVals[3] != 61070008U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'StabControl' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "Status", &checksumVals);
    if (checksumVals[0] != 696104295U ||
        checksumVals[1] != 3071418899U ||
        checksumVals[2] != 2536886554U ||
        checksumVals[3] != 100807257U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'Status' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "CTRLPARAMSPV", &checksumVals);
    if (checksumVals[0] != 2031185785U ||
        checksumVals[1] != 3338451586U ||
        checksumVals[2] != 2227459047U ||
        checksumVals[3] != 2100951587U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'CTRLPARAMSPV' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }

    ssCallGetDataTypeChecksum(S, "OutPV", &checksumVals);
    if (checksumVals[0] != 2915191612U ||
        checksumVals[1] != 2280052566U ||
        checksumVals[2] != 3895984238U ||
        checksumVals[3] != 1059489311U) {
      ssSetErrorStatus(S, "The definition of the data type "
                       "'OutPV' has been updated since this S-Function was "
                       "generated; regenerate this S-Function.");
      return;
    }
  }
}

#endif                                 /* MDL_SET_WORK_WIDTHS */

static boolean_T enable_first_entry;

/*
 *   This function does sfunction consistent check, initializes internal memory if neccessary, and
 *   calls the initialization function of the generated ERT code.
 */
#define MDL_START                                                /* Change to #undef to remove function */
#if defined(MDL_START)

static void mdlStart(SimStruct *S)
{
  char *OutPort_0 = (char *)ssGetOutputPortSignal(S, 0);
  char *OutPort_1 = (char *)ssGetOutputPortSignal(S, 1);
  char *OutPort_2 = (char *)ssGetOutputPortSignal(S, 2);
  char *OutPort_3 = (char *)ssGetOutputPortSignal(S, 3);
  char *OutPort_4 = (char *)ssGetOutputPortSignal(S, 4);
  boolean_T *OutPort_5 = (boolean_T *)ssGetOutputPortSignal(S, 5);
  Warning *OutPort_6 = (Warning *)ssGetOutputPortSignal(S, 6);
  char *OutPort_7 = (char *)ssGetOutputPortSignal(S, 7);
  char *OutPort_8 = (char *)ssGetOutputPortSignal(S, 8);
  real32_T *OutPort_9 = (real32_T *)ssGetOutputPortSignal(S, 9);
  real32_T *OutPort_10 = (real32_T *)ssGetOutputPortSignal(S, 10);
  real32_T *OutPort_11 = (real32_T *)ssGetOutputPortSignal(S, 11);
  boolean_T *OutPort_12 = (boolean_T *)ssGetOutputPortSignal(S, 12);

  /* check if more than one instance of this S-Function has been used */
  if (++MGCCode_Ori_sf_counter > 1) {
    ssSetErrorStatus(S,"This S-Function is limited to one copy per model.");
    MGCCode_Ori_sf_counter = 0;
    return;
  }

  /* check if parent model's start time is the same as that used to generate code */
  if (ssGetTStart(S) != 0.0) {
    ssSetErrorStatus(S,
                     "The parent model of this S-Function must set the value of the 'Start time' on the Solver page of its Configuration Parameters Dialog to 0.0 since that was the value used when generating code for the S-Function's original model.");
    return;
  }

  if (ssGetSolverMode(S) == SOLVER_MODE_MULTITASKING) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "solver mode set to auto or multitasking "
                     "because this S-Function was created from a model with "
                     "solver mode set to singletasking. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

  enable_first_entry = TRUE;

#ifdef PIL_S_FUNCTION

  pilMarshallInitSFcnSimStruct(S);
  pilMarshallInitRootSimStruct(ssGetRootSS(S));

#endif

  MGCCode_Ori_initialize();
  *((real32_T*)(&OutPort_0[0])) = MGCCode_Ori_Y.OutICEn.ICESPcmd;
  *((real32_T*)(&OutPort_0[0] + 4)) = MGCCode_Ori_Y.OutICEn.ICESQcmd;
  *((real32_T*)(&OutPort_1[0])) = MGCCode_Ori_Y.OutBatn.BatSPcmd;
  *((real32_T*)(&OutPort_1[0] + 4)) = MGCCode_Ori_Y.OutBatn.BatSQcmd;
  *((real32_T*)(&OutPort_2[0])) = MGCCode_Ori_Y.OutPVn.PVSPcmd;
  *((real32_T*)(&OutPort_2[0] + 4)) = MGCCode_Ori_Y.OutPVn.PVSQcmd;
  *((real32_T*)(&OutPort_3[0])) = MGCCode_Ori_Y.OutDFIG1n.DFIG1SPcmd;
  *((real32_T*)(&OutPort_3[0] + 4)) = MGCCode_Ori_Y.OutDFIG1n.DFIG1SQcmd;
  *((real32_T*)(&OutPort_4[0])) = MGCCode_Ori_Y.OutDFIG2n.DFIG1SPcmd;
  *((real32_T*)(&OutPort_4[0] + 4)) = MGCCode_Ori_Y.OutDFIG2n.DFIG1SQcmd;
  OutPort_5[0] = MGCCode_Ori_Y.Islandsignal;
  OutPort_6[0] = MGCCode_Ori_Y.Warningn;
  *((real32_T*)(&OutPort_7[0])) =
    MGCCode_Ori_Y.EmergencyControl.Pre_LinePowerCmd;
  *((real32_T*)(&OutPort_7[0] + 4)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_LoadShedding;
  *((real32_T*)(&OutPort_7[0] + 8)) = MGCCode_Ori_Y.EmergencyControl.Pre_Pclear;
  *((boolean_T*)(&OutPort_7[0] + 12)) = MGCCode_Ori_Y.EmergencyControl.Pre_CutEn;
  *((real32_T*)(&OutPort_7[0] + 16)) = MGCCode_Ori_Y.EmergencyControl.EC_Pclear;
  *((real32_T*)(&OutPort_7[0] + 20)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_IslandLoadShedding;
  *((real32_T*)(&OutPort_7[0] + 24)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_IslandPclear;
  *((boolean_T*)(&OutPort_7[0] + 28)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_IslandCutEn;
  *((real32_T*)(&OutPort_7[0] + 32)) =
    MGCCode_Ori_Y.EmergencyControl.EC_IslandPclear;
  *((real32_T*)(&OutPort_8[0])) = MGCCode_Ori_Y.Observen.AGCref;
  *((real32_T*)(&OutPort_8[0] + 4)) = MGCCode_Ori_Y.Observen.AVCRef;
  *((real32_T*)(&OutPort_8[0] + 8)) = MGCCode_Ori_Y.Observen.ICEPout;
  *((real32_T*)(&OutPort_8[0] + 12)) = MGCCode_Ori_Y.Observen.ICEQout;
  *((real32_T*)(&OutPort_8[0] + 16)) = MGCCode_Ori_Y.Observen.BatPout;
  *((real32_T*)(&OutPort_8[0] + 20)) = MGCCode_Ori_Y.Observen.BatQout;
  *((real32_T*)(&OutPort_8[0] + 24)) = MGCCode_Ori_Y.Observen.PVPout;
  *((real32_T*)(&OutPort_8[0] + 28)) = MGCCode_Ori_Y.Observen.PVQout;
  *((real32_T*)(&OutPort_8[0] + 32)) = MGCCode_Ori_Y.Observen.DFIG1Pout;
  *((real32_T*)(&OutPort_8[0] + 36)) = MGCCode_Ori_Y.Observen.DFIG1Qout;
  *((real32_T*)(&OutPort_8[0] + 40)) = MGCCode_Ori_Y.Observen.Omegagen;
  OutPort_9[0] = MGCCode_Ori_Y.Param;
  OutPort_10[0] = MGCCode_Ori_Y.LineP;
  OutPort_11[0] = MGCCode_Ori_Y.LineQ;
  OutPort_12[0] = MGCCode_Ori_Y.SyncSignal;
}

#endif                                 /*  MDL_START */

#define MDL_INITIALIZE_CONDITIONS

/*   Nothing runs in this function */
static void mdlInitializeConditions(SimStruct *S)
{
}

/*
 * This function calls the step function of the generated ERT code
 * and provides an interface with the simulation data.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  const char * const * InPort_0 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 0);
  const char * const * InPort_1 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 1);
  const char * const * InPort_2 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 2);
  const char * const * InPort_3 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 3);
  const char * const * InPort_4 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 4);
  const char * const * InPort_5 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 5);
  const char * const * InPort_6 = (const char * const *)
    ssGetInputPortSignalPtrs(S, 6);
  char *OutPort_0 = (char *)ssGetOutputPortSignal(S, 0);
  char *OutPort_1 = (char *)ssGetOutputPortSignal(S, 1);
  char *OutPort_2 = (char *)ssGetOutputPortSignal(S, 2);
  char *OutPort_3 = (char *)ssGetOutputPortSignal(S, 3);
  char *OutPort_4 = (char *)ssGetOutputPortSignal(S, 4);
  boolean_T *OutPort_5 = (boolean_T *)ssGetOutputPortSignal(S, 5);
  Warning *OutPort_6 = (Warning *)ssGetOutputPortSignal(S, 6);
  char *OutPort_7 = (char *)ssGetOutputPortSignal(S, 7);
  char *OutPort_8 = (char *)ssGetOutputPortSignal(S, 8);
  real32_T *OutPort_9 = (real32_T *)ssGetOutputPortSignal(S, 9);
  real32_T *OutPort_10 = (real32_T *)ssGetOutputPortSignal(S, 10);
  real32_T *OutPort_11 = (real32_T *)ssGetOutputPortSignal(S, 11);
  boolean_T *OutPort_12 = (boolean_T *)ssGetOutputPortSignal(S, 12);
  MGCCode_Ori_U.InEMSRootn.SystemModen = *((SystemMode*)(&InPort_0[0][0]));
  MGCCode_Ori_U.InEMSRootn.ICEMode = *((GenMode*)(&InPort_0[0][0] + 4));
  MGCCode_Ori_U.InEMSRootn.BatMode = *((GenMode*)(&InPort_0[0][0] + 8));
  MGCCode_Ori_U.InEMSRootn.PVMode = *((GenMode*)(&InPort_0[0][0] + 12));
  MGCCode_Ori_U.InEMSRootn.DFIG1Mode = *((GenMode*)(&InPort_0[0][0] + 16));
  MGCCode_Ori_U.InEMSRootn.DFIG2Mode = *((GenMode*)(&InPort_0[0][0] + 20));
  MGCCode_Ori_U.InEMSRootn.RatioCtrlCmd = *((boolean_T*)(&InPort_0[0][0] + 24));
  MGCCode_Ori_U.InSystemRootn.LinePref = *((real32_T*)(&InPort_1[0][0]));
  MGCCode_Ori_U.InSystemRootn.LineP = *((real32_T*)(&InPort_1[0][0] + 4));
  MGCCode_Ori_U.InSystemRootn.Freqref = *((real32_T*)(&InPort_1[0][0] + 8));
  MGCCode_Ori_U.InSystemRootn.Fmeas = *((real32_T*)(&InPort_1[0][0] + 12));
  MGCCode_Ori_U.InSystemRootn.LineQref = *((real32_T*)(&InPort_1[0][0] + 16));
  MGCCode_Ori_U.InSystemRootn.LineQ = *((real32_T*)(&InPort_1[0][0] + 20));
  MGCCode_Ori_U.InSystemRootn.Vref = *((real32_T*)(&InPort_1[0][0] + 24));
  MGCCode_Ori_U.InSystemRootn.Vmeas = *((real32_T*)(&InPort_1[0][0] + 28));
  MGCCode_Ori_U.InSystemRootn.GridVmeas = *((real32_T*)(&InPort_1[0][0] + 32));
  MGCCode_Ori_U.InSystemRootn.GridFreqCmd = *((real32_T*)(&InPort_1[0][0] + 36));
  MGCCode_Ori_U.InSystemRootn.SwitchSignal = *((boolean_T*)(&InPort_1[0][0] + 40));
  MGCCode_Ori_U.InICEn.ICESPref = *((real32_T*)(&InPort_2[0][0]));
  MGCCode_Ori_U.InICEn.ICESQref = *((real32_T*)(&InPort_2[0][0] + 4));
  MGCCode_Ori_U.InICEn.ICESPout = *((real32_T*)(&InPort_2[0][0] + 8));
  MGCCode_Ori_U.InICEn.ICESQout = *((real32_T*)(&InPort_2[0][0] + 12));
  MGCCode_Ori_U.InICEn.ICEStatus = *((boolean_T*)(&InPort_2[0][0] + 16));
  MGCCode_Ori_U.InBatn.BatSPref = *((real32_T*)(&InPort_3[0][0]));
  MGCCode_Ori_U.InBatn.BatSQref = *((real32_T*)(&InPort_3[0][0] + 4));
  MGCCode_Ori_U.InBatn.BatSPout = *((real32_T*)(&InPort_3[0][0] + 8));
  MGCCode_Ori_U.InBatn.BatSQout = *((real32_T*)(&InPort_3[0][0] + 12));
  MGCCode_Ori_U.InBatn.BatStatus = *((boolean_T*)(&InPort_3[0][0] + 16));
  MGCCode_Ori_U.InBatn.BatChargeCmd = *((boolean_T*)(&InPort_3[0][0] + 17));
  MGCCode_Ori_U.InPVn.PVSPref = *((real32_T*)(&InPort_4[0][0]));
  MGCCode_Ori_U.InPVn.PVSQref = *((real32_T*)(&InPort_4[0][0] + 4));
  MGCCode_Ori_U.InPVn.PVSPout = *((real32_T*)(&InPort_4[0][0] + 8));
  MGCCode_Ori_U.InPVn.PVSQout = *((real32_T*)(&InPort_4[0][0] + 12));
  MGCCode_Ori_U.InPVn.PVStatus = *((boolean_T*)(&InPort_4[0][0] + 16));
  MGCCode_Ori_U.InDFIG1n.DFIG1SPref = *((real32_T*)(&InPort_5[0][0]));
  MGCCode_Ori_U.InDFIG1n.DFIG1SQref = *((real32_T*)(&InPort_5[0][0] + 4));
  MGCCode_Ori_U.InDFIG1n.DFIG1SPout = *((real32_T*)(&InPort_5[0][0] + 8));
  MGCCode_Ori_U.InDFIG1n.DFIG1SQout = *((real32_T*)(&InPort_5[0][0] + 12));
  MGCCode_Ori_U.InDFIG1n.DFIG1Status = *((boolean_T*)(&InPort_5[0][0] + 16));
  MGCCode_Ori_U.InDFIG1n.DFIG1Omega = *((real32_T*)(&InPort_5[0][0] + 20));
  MGCCode_Ori_U.InDFIG1n.DFIG1Threshold = *((real32_T*)(&InPort_5[0][0] + 24));
  MGCCode_Ori_U.InDFIG1n.DFIG1Te = *((real32_T*)(&InPort_5[0][0] + 28));
  MGCCode_Ori_U.InDFIG1n.DFIG1PitchA = *((real32_T*)(&InPort_5[0][0] + 32));
  MGCCode_Ori_U.InDFIG2n.DFIG2SPref = *((real32_T*)(&InPort_6[0][0]));
  MGCCode_Ori_U.InDFIG2n.DFIG2SQref = *((real32_T*)(&InPort_6[0][0] + 4));
  MGCCode_Ori_U.InDFIG2n.DFIG2SPout = *((real32_T*)(&InPort_6[0][0] + 8));
  MGCCode_Ori_U.InDFIG2n.DFIG2SQout = *((real32_T*)(&InPort_6[0][0] + 12));
  MGCCode_Ori_U.InDFIG2n.DFIG2Status = *((boolean_T*)(&InPort_6[0][0] + 16));
  MGCCode_Ori_U.InDFIG2n.DFIG2Omega = *((real32_T*)(&InPort_6[0][0] + 20));
  MGCCode_Ori_U.InDFIG2n.DFIG2Threshold = *((real32_T*)(&InPort_6[0][0] + 24));
  MGCCode_Ori_U.InDFIG2n.DFIG2Te = *((real32_T*)(&InPort_6[0][0] + 28));
  if (ssIsMajorTimeStep(S)) {
    MGCCode_Ori_step();
  }

  *((real32_T*)(&OutPort_0[0])) = MGCCode_Ori_Y.OutICEn.ICESPcmd;
  *((real32_T*)(&OutPort_0[0] + 4)) = MGCCode_Ori_Y.OutICEn.ICESQcmd;
  *((real32_T*)(&OutPort_1[0])) = MGCCode_Ori_Y.OutBatn.BatSPcmd;
  *((real32_T*)(&OutPort_1[0] + 4)) = MGCCode_Ori_Y.OutBatn.BatSQcmd;
  *((real32_T*)(&OutPort_2[0])) = MGCCode_Ori_Y.OutPVn.PVSPcmd;
  *((real32_T*)(&OutPort_2[0] + 4)) = MGCCode_Ori_Y.OutPVn.PVSQcmd;
  *((real32_T*)(&OutPort_3[0])) = MGCCode_Ori_Y.OutDFIG1n.DFIG1SPcmd;
  *((real32_T*)(&OutPort_3[0] + 4)) = MGCCode_Ori_Y.OutDFIG1n.DFIG1SQcmd;
  *((real32_T*)(&OutPort_4[0])) = MGCCode_Ori_Y.OutDFIG2n.DFIG1SPcmd;
  *((real32_T*)(&OutPort_4[0] + 4)) = MGCCode_Ori_Y.OutDFIG2n.DFIG1SQcmd;
  OutPort_5[0] = MGCCode_Ori_Y.Islandsignal;
  OutPort_6[0] = MGCCode_Ori_Y.Warningn;
  *((real32_T*)(&OutPort_7[0])) =
    MGCCode_Ori_Y.EmergencyControl.Pre_LinePowerCmd;
  *((real32_T*)(&OutPort_7[0] + 4)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_LoadShedding;
  *((real32_T*)(&OutPort_7[0] + 8)) = MGCCode_Ori_Y.EmergencyControl.Pre_Pclear;
  *((boolean_T*)(&OutPort_7[0] + 12)) = MGCCode_Ori_Y.EmergencyControl.Pre_CutEn;
  *((real32_T*)(&OutPort_7[0] + 16)) = MGCCode_Ori_Y.EmergencyControl.EC_Pclear;
  *((real32_T*)(&OutPort_7[0] + 20)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_IslandLoadShedding;
  *((real32_T*)(&OutPort_7[0] + 24)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_IslandPclear;
  *((boolean_T*)(&OutPort_7[0] + 28)) =
    MGCCode_Ori_Y.EmergencyControl.Pre_IslandCutEn;
  *((real32_T*)(&OutPort_7[0] + 32)) =
    MGCCode_Ori_Y.EmergencyControl.EC_IslandPclear;
  *((real32_T*)(&OutPort_8[0])) = MGCCode_Ori_Y.Observen.AGCref;
  *((real32_T*)(&OutPort_8[0] + 4)) = MGCCode_Ori_Y.Observen.AVCRef;
  *((real32_T*)(&OutPort_8[0] + 8)) = MGCCode_Ori_Y.Observen.ICEPout;
  *((real32_T*)(&OutPort_8[0] + 12)) = MGCCode_Ori_Y.Observen.ICEQout;
  *((real32_T*)(&OutPort_8[0] + 16)) = MGCCode_Ori_Y.Observen.BatPout;
  *((real32_T*)(&OutPort_8[0] + 20)) = MGCCode_Ori_Y.Observen.BatQout;
  *((real32_T*)(&OutPort_8[0] + 24)) = MGCCode_Ori_Y.Observen.PVPout;
  *((real32_T*)(&OutPort_8[0] + 28)) = MGCCode_Ori_Y.Observen.PVQout;
  *((real32_T*)(&OutPort_8[0] + 32)) = MGCCode_Ori_Y.Observen.DFIG1Pout;
  *((real32_T*)(&OutPort_8[0] + 36)) = MGCCode_Ori_Y.Observen.DFIG1Qout;
  *((real32_T*)(&OutPort_8[0] + 40)) = MGCCode_Ori_Y.Observen.Omegagen;
  OutPort_9[0] = MGCCode_Ori_Y.Param;
  OutPort_10[0] = MGCCode_Ori_Y.LineP;
  OutPort_11[0] = MGCCode_Ori_Y.LineQ;
  OutPort_12[0] = MGCCode_Ori_Y.SyncSignal;
}

/* This function calls the termination function of the generated ERT code. */
static void mdlTerminate(SimStruct *S)
{
  MGCCode_Ori_terminate();
  MGCCode_Ori_sf_counter = 0;
}

#define MDL_ENABLE

static void mdlEnable(SimStruct *S)
{
  if (!enable_first_entry) {
    static char msg[256];
    if (strlen(ssGetPath(S)) < 128) {
      sprintf(msg,
              "The model is attempting to invoke the enable method of the S-Function block %s for model 'MGCCode_Ori', yet the code generated for the model does not include the enable method\n",
              ssGetPath(S));
    } else {
      sprintf(msg,
              "The model is attempting to invoke the enable method of the S-Function block for model 'MGCCode_Ori', yet the code generated for the model does not include the enable method\n");
    }

    ssSetErrorStatus(S, msg);
  }

  enable_first_entry = FALSE;
}

#define MDL_DISABLE

static void mdlDisable(SimStruct *S)
{
  static char msg[256];
  if (strlen(ssGetPath(S)) < 128) {
    sprintf(msg,
            "The model is attempting to invoke the disable mothod of the S-Function block %s for model 'MGCCode_Ori', yet the code generated for the model does not include the disable method\n",
            ssGetPath(S));
  } else {
    sprintf(msg,
            "The model is attempting to invoke the disable mothod of the S-Function block for model 'MGCCode_Ori', yet the code generated for the model does not include the disable method\n");
  }

  ssSetErrorStatus(S, msg);
}

#ifdef MATLAB_MEX_FILE                 /* Is this file being compiled as a MEX-file? */
#include "simulink.c"                  /* MEX-file interface mechanism */
#include "fixedpoint.c"
#else
#include "cg_sfun.h"                   /* Code generation registration function */
#endif
