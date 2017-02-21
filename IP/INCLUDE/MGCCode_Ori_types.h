/*
 * File: MGCCode_Ori_types.h
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

#ifndef RTW_HEADER_MGCCode_Ori_types_h_
#define RTW_HEADER_MGCCode_Ori_types_h_
#include "rtwtypes.h"
#ifndef SS_LONG
#define SS_LONG                        45
#endif

#ifndef SS_ULONG
#define SS_ULONG                       46
#endif

#ifndef _DEFINED_TYPEDEF_FOR_SystemMode_
#define _DEFINED_TYPEDEF_FOR_SystemMode_

typedef enum {
  Start = 0,                           /* Default value */
  ConstPConstQ,
  AGC,
  Independent,
  ActiveIsland,
  Island,
  IslandAGC,
  ActiveGrid
} SystemMode;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_GenMode_
#define _DEFINED_TYPEDEF_FOR_GenMode_

typedef enum {
  ConstPQ = 1,                         /* Default value */
  ConstPAVC,
  AGCConstQ,
  AGCAVC,
  Dull
} GenMode;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Warning_
#define _DEFINED_TYPEDEF_FOR_Warning_

typedef enum {
  None = 0,                            /* Default value */
  StartFail,
  IslandFail,
  GridFail
} Warning;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Status_
#define _DEFINED_TYPEDEF_FOR_Status_

typedef enum {
  All = 0,                             /* Default value */
  ID1D2B,
  ID1D2P,
  ID1D2,
  ID1BP,
  ID1B,
  ID1P,
  ID1,
  ID2BP,
  ID2B,
  ID2P,
  ID2,
  IBP,
  IB,
  IP,
  I,
  D1D2BP,
  D1D2B,
  D1D2P,
  D1D2,
  D1BP,
  D1B,
  D1P,
  D1,
  D2BP,
  D2B,
  D2P,
  D2,
  BP,
  B,
  P,
  Fail
} Status;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InEMSRoot_
#define _DEFINED_TYPEDEF_FOR_InEMSRoot_

typedef struct {
  SystemMode SystemModen;
  GenMode ICEMode;
  GenMode BatMode;
  GenMode PVMode;
  GenMode DFIG1Mode;
  GenMode DFIG2Mode;
  boolean_T RatioCtrlCmd;
} InEMSRoot;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InSystemRoot_
#define _DEFINED_TYPEDEF_FOR_InSystemRoot_

typedef struct {
  real32_T LinePref;
  real32_T LineP;
  real32_T Freqref;
  real32_T Fmeas;
  real32_T LineQref;
  real32_T LineQ;
  real32_T Vref;
  real32_T Vmeas;
  real32_T GridVmeas;
  real32_T GridFreqCmd;
  boolean_T SwitchSignal;
} InSystemRoot;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InICE_
#define _DEFINED_TYPEDEF_FOR_InICE_

typedef struct {
  real32_T ICESPref;
  real32_T ICESQref;
  real32_T ICESPout;
  real32_T ICESQout;
  boolean_T ICEStatus;
} InICE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InBat_
#define _DEFINED_TYPEDEF_FOR_InBat_

typedef struct {
  real32_T BatSPref;
  real32_T BatSQref;
  real32_T BatSPout;
  real32_T BatSQout;
  boolean_T BatStatus;
  boolean_T BatChargeCmd;
} InBat;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InPV_
#define _DEFINED_TYPEDEF_FOR_InPV_

typedef struct {
  real32_T PVSPref;
  real32_T PVSQref;
  real32_T PVSPout;
  real32_T PVSQout;
  boolean_T PVStatus;
} InPV;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InDFIG1_
#define _DEFINED_TYPEDEF_FOR_InDFIG1_

typedef struct {
  real32_T DFIG1SPref;
  real32_T DFIG1SQref;
  real32_T DFIG1SPout;
  real32_T DFIG1SQout;
  boolean_T DFIG1Status;
  real32_T DFIG1Omega;
  real32_T DFIG1Threshold;
  real32_T DFIG1Te;
  real32_T DFIG1PitchA;
} InDFIG1;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InDFIG2_
#define _DEFINED_TYPEDEF_FOR_InDFIG2_

typedef struct {
  real32_T DFIG2SPref;
  real32_T DFIG2SQref;
  real32_T DFIG2SPout;
  real32_T DFIG2SQout;
  boolean_T DFIG2Status;
  real32_T DFIG2Omega;
  real32_T DFIG2Threshold;
  real32_T DFIG2Te;
} InDFIG2;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_BASE_
#define _DEFINED_TYPEDEF_FOR_BASE_

typedef struct {
  real32_T LineP;
  real32_T LineQ;
  real32_T ActivePower;
  real32_T ReactivePower;
  real32_T Freq;
  real32_T Volt;
  real32_T ICE;
  real32_T Bat;
  real32_T PV;
  real32_T DFIG1;
  real32_T LoadP;
  real32_T LoadQ;
  real32_T AGCRatio;
  real32_T AVCRatio;
  real32_T ICEPmax;
  real32_T ICEQmax;
  real32_T BatPmax;
  real32_T BatQmax;
  real32_T DFIG1Pmax;
  real32_T DFIG1Qmax;
  real32_T PVPmax;
  real32_T PVPmax1;
  real32_T PVQmax;
  real32_T Nominator;
  real32_T Denominator;
} BASE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_CTRLPARAMSAGC_
#define _DEFINED_TYPEDEF_FOR_CTRLPARAMSAGC_

typedef struct {
  real32_T LinePPIGain;
  real32_T LinePPIIntegral;
  real32_T LinePPIUpperSat;
  real32_T LinePPILowerSat;
  real32_T FreqPIGain;
  real32_T FreqPIIntegral;
  real32_T FreqPIUpperSat;
  real32_T FreqPILowerSat;
} CTRLPARAMSAGC;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_CTRLPARAMSAVC_
#define _DEFINED_TYPEDEF_FOR_CTRLPARAMSAVC_

typedef struct {
  real32_T LineQPIGain;
  real32_T LineQPIIntegral;
  real32_T LineQPIUpperSat;
  real32_T LineQPILowerSat;
  real32_T VoltPIGain;
  real32_T VoltPIIntegral;
  real32_T VoltPIUpperSat;
  real32_T VoltPILowerSat;
} CTRLPARAMSAVC;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_CTRLPARAMSBAT_
#define _DEFINED_TYPEDEF_FOR_CTRLPARAMSBAT_

typedef struct {
  real32_T ConstPPIGain;
  real32_T ConstPPIIntegral;
  real32_T ConstPPIUpperSat;
  real32_T ConstPPILowerSat;
  real32_T ConstQPIGain;
  real32_T ConstQPIIntegral;
  real32_T ConstQPIUpperSat;
  real32_T ConstQPILowerSat;
  real32_T AGCInnerPIGain;
  real32_T AGCInnerPIIntegral;
  real32_T AGCInnerPIUpperSat;
  real32_T AGCInnerPILowerSat;
  real32_T AVCInnerPIGain;
  real32_T AVCInnerPIIntegral;
  real32_T AVCInnerPIUpperSat;
  real32_T AVCInnerPILowerSat;
} CTRLPARAMSBAT;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_OutBat_
#define _DEFINED_TYPEDEF_FOR_OutBat_

typedef struct {
  real32_T BatSPcmd;
  real32_T BatSQcmd;
} OutBat;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_OutICE_
#define _DEFINED_TYPEDEF_FOR_OutICE_

typedef struct {
  real32_T ICESPcmd;
  real32_T ICESQcmd;
} OutICE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Obe_
#define _DEFINED_TYPEDEF_FOR_Obe_

typedef struct {
  real32_T AGCref;
  real32_T AVCRef;
  real32_T ICEPout;
  real32_T ICEQout;
  real32_T BatPout;
  real32_T BatQout;
  real32_T PVPout;
  real32_T PVQout;
  real32_T DFIG1Pout;
  real32_T DFIG1Qout;
  real32_T Omegagen;
} Obe;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_CTRLPARAMSICE_
#define _DEFINED_TYPEDEF_FOR_CTRLPARAMSICE_

typedef struct {
  real32_T ConstPPIGain;
  real32_T ConstPPIIntegral;
  real32_T ConstPPIUpperSat;
  real32_T ConstPPILowerSat;
  real32_T ConstQPIGain;
  real32_T ConstQPIIntegral;
  real32_T ConstQPIUpperSat;
  real32_T ConstQPILowerSat;
  real32_T AGCInnerPIGain;
  real32_T AGCInnerPIIntegral;
  real32_T AGCInnerPIUpperSat;
  real32_T AGCInnerPILowerSat;
  real32_T AVCInnerPIGain;
  real32_T AVCInnerPIIntegral;
  real32_T AVCInnerPIUpperSat;
  real32_T AVCInnerPILowerSat;
} CTRLPARAMSICE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_CTRLPARAMSDFIG1_
#define _DEFINED_TYPEDEF_FOR_CTRLPARAMSDFIG1_

typedef struct {
  real32_T ConstPPIGain;
  real32_T ConstPPIIntegral;
  real32_T ConstPPIUpperSat;
  real32_T ConstPPILowerSat;
  real32_T ConstQPIGain;
  real32_T ConstQPIIntegral;
  real32_T ConstQPIUpperSat;
  real32_T ConstQPILowerSat;
  real32_T AGCInnerPIGain;
  real32_T AGCInnerPIIntegral;
  real32_T AGCInnerPIUpperSat;
  real32_T AGCInnerPILowerSat;
  real32_T AVCInnerPIGain;
  real32_T AVCInnerPIIntegral;
  real32_T AVCInnerPIUpperSat;
  real32_T AVCInnerPILowerSat;
} CTRLPARAMSDFIG1;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_OutDFIG1_
#define _DEFINED_TYPEDEF_FOR_OutDFIG1_

typedef struct {
  real32_T DFIG1SPcmd;
  real32_T DFIG1SQcmd;
} OutDFIG1;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_GRIDPARAM_
#define _DEFINED_TYPEDEF_FOR_GRIDPARAM_

typedef struct {
  real32_T PreventiveLineRatioUp;
  real32_T PreventiveLoadRatioUp;
  real32_T PreventiveTotalRatioUp;
  real32_T EmergencyTotalRatioUp;
} GRIDPARAM;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_ISLANDPARAM_
#define _DEFINED_TYPEDEF_FOR_ISLANDPARAM_

typedef struct {
  real32_T PreventiveLoadRatioUp;
  real32_T Stage3Freq;
  real32_T Stage3Cutting;
  real32_T Stage2Freq;
  real32_T Stage2Cutting;
  real32_T ActiveGridFreq;
} ISLANDPARAM;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_OutEMS_
#define _DEFINED_TYPEDEF_FOR_OutEMS_

typedef struct {
  SystemMode SystemModen;
  GenMode ICEMode;
  GenMode BatMode;
  GenMode PVMode;
  GenMode DFIG1Mode;
  GenMode DFIG2Mode;
} OutEMS;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_OutSystem_
#define _DEFINED_TYPEDEF_FOR_OutSystem_

typedef struct {
  real32_T LinePref;
  real32_T Fref;
  real32_T LineQref;
  real32_T Vref;
} OutSystem;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InEMS_
#define _DEFINED_TYPEDEF_FOR_InEMS_

typedef struct {
  SystemMode SystemModen;
  GenMode ICEMode;
  GenMode BatMode;
  GenMode PVMode;
  GenMode DFIG1Mode;
  GenMode DFIG2Mode;
  boolean_T ICEStatus;
  boolean_T BatStatus;
  boolean_T PVStatus;
  boolean_T DFIG1Status;
  boolean_T DFIG2Status;
} InEMS;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_InSystem_
#define _DEFINED_TYPEDEF_FOR_InSystem_

typedef struct {
  real32_T LinePref;
  real32_T LineP;
  real32_T Fref;
  real32_T Fmeas;
  real32_T LineQref;
  real32_T LineQ;
  real32_T Vref;
  real32_T Vmeas;
  real32_T GridVmeas;
  real32_T GridFreqCmd;
  boolean_T SwitchSignal;
} InSystem;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_SystemRatio_
#define _DEFINED_TYPEDEF_FOR_SystemRatio_

typedef struct {
  real32_T Pout;
  real32_T Pmax;
  real32_T AGCRatio;
  real32_T AVCRatio;
  real32_T PVAGCRatio;
  real32_T PVAVCRatio;
  real32_T DFIG1AGCRatio;
  real32_T DFIG1AVCRatio;
  real32_T DFIG3AGCRatio;
  real32_T DFIG3AVCRatio;
  real32_T BatAGCRatio;
  real32_T BatAVCRatio;
  real32_T ICEAGCRatio;
  real32_T ICEAVCRatio;
  real32_T Qout;
  real32_T Qmax;
} SystemRatio;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_StabControl_
#define _DEFINED_TYPEDEF_FOR_StabControl_

typedef struct {
  real32_T Pre_LinePowerCmd;
  real32_T Pre_LoadShedding;
  real32_T Pre_Pclear;
  boolean_T Pre_CutEn;
  real32_T EC_Pclear;
  real32_T Pre_IslandLoadShedding;
  real32_T Pre_IslandPclear;
  boolean_T Pre_IslandCutEn;
  real32_T EC_IslandPclear;
} StabControl;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_CTRLPARAMSPV_
#define _DEFINED_TYPEDEF_FOR_CTRLPARAMSPV_

typedef struct {
  real32_T ConstPPIGain;
  real32_T ConstPPIIntegral;
  real32_T ConstPPIUpperSat;
  real32_T ConstPPILowerSat;
  real32_T ConstQPIGain;
  real32_T ConstQPIIntegral;
  real32_T ConstQPIUpperSat;
  real32_T ConstQPILowerSat;
  real32_T AGCInnerPIGain;
  real32_T AGCInnerPIIntegral;
  real32_T AGCInnerPIUpperSat;
  real32_T AGCInnerPILowerSat;
  real32_T AVCInnerPIGain;
  real32_T AVCInnerPIIntegral;
  real32_T AVCInnerPIUpperSat;
  real32_T AVCInnerPILowerSat;
} CTRLPARAMSPV;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_OutPV_
#define _DEFINED_TYPEDEF_FOR_OutPV_

typedef struct {
  real32_T PVSPcmd;
  real32_T PVSQcmd;
} OutPV;

#endif

/* Parameters (auto storage) */
typedef struct Parameters_MGCCode_Ori_ Parameters_MGCCode_Ori;

/* Forward declaration for rtModel */
typedef struct tag_RTM_MGCCode_Ori RT_MODEL_MGCCode_Ori;

#endif                                 /* RTW_HEADER_MGCCode_Ori_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
