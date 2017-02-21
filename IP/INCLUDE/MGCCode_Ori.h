/*
 * File: MGCCode_Ori.h
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

#ifndef RTW_HEADER_MGCCode_Ori_h_
#define RTW_HEADER_MGCCode_Ori_h_
#ifndef MGCCode_Ori_COMMON_INCLUDES_
# define MGCCode_Ori_COMMON_INCLUDES_
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* MGCCode_Ori_COMMON_INCLUDES_ */

#include "MGCCode_Ori_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* user code (top of header file) */
#include"ModeSwitch.h"

/* Block signals for system '<S2>/EnablePI1' */
typedef struct {
  real32_T Saturation;                 /* '<S10>/Saturation' */
} rtB_EnablePI1_MGCCode_Ori;

/* Block states (auto storage) for system '<S2>/EnablePI1' */
typedef struct {
  real32_T Integrator_DSTATE;          /* '<S10>/Integrator' */
  int16_T Integrator_PrevResetState;   /* '<S10>/Integrator' */
  boolean_T EnablePI1_MODE;            /* '<S2>/EnablePI1' */
} rtDW_EnablePI1_MGCCode_Ori;

/* Block signals for system '<S2>/EnablePI5' */
typedef struct {
  real32_T Saturation;                 /* '<S14>/Saturation' */
} rtB_EnablePI5_MGCCode_Ori;

/* Block states (auto storage) for system '<S2>/EnablePI5' */
typedef struct {
  real32_T Integrator_DSTATE;          /* '<S14>/Integrator' */
  int16_T Integrator_PrevResetState;   /* '<S14>/Integrator' */
  boolean_T EnablePI5_MODE;            /* '<S2>/EnablePI5' */
} rtDW_EnablePI5_MGCCode_Ori;

/* Block signals for system '<S25>/ModeSelect' */
typedef struct {
  int16_T AGCInnerEnable;              /* '<S25>/ModeSelect' */
  int16_T ConstPEnable;                /* '<S25>/ModeSelect' */
  int16_T AVCInnerEnable;              /* '<S25>/ModeSelect' */
  int16_T ConstQEnable;                /* '<S25>/ModeSelect' */
  int16_T PCtrlSwitch;                 /* '<S25>/ModeSelect' */
  int16_T QCtrlSwitch;                 /* '<S25>/ModeSelect' */
} rtB_ModeSelect_MGCCode_Ori;

/* Block signals (auto storage) */
typedef struct {
  SystemRatio BusConversion_InsertedFor_Micro;
  InSystem BusConversion_InsertedFor_Mic_l;
  InEMS BusConversion_InsertedFor_Mi_l4;
  OutEMS OutEMS_c;                     /* '<S1>/MicrogridModelManager' */
  OutSystem OutSystem_k;               /* '<S1>/MicrogridModelManager' */
  real32_T RatioAGC;                   /* '<S2>/Switch6' */
  SystemMode SystemModen;              /* '<S1>/Rate Transition1' */
  GenMode ICEMode;                     /* '<S1>/Rate Transition1' */
  GenMode BatMode;                     /* '<S1>/Rate Transition1' */
  GenMode PVMode;                      /* '<S1>/Rate Transition1' */
  GenMode DFIG1Mode;                   /* '<S1>/Rate Transition1' */
  GenMode DFIG2Mode;                   /* '<S1>/Rate Transition1' */
  rtB_ModeSelect_MGCCode_Ori sf_ModeSelect_d;/* '<S50>/ModeSelect' */
  rtB_EnablePI1_MGCCode_Ori EnablePI3_l;/* '<S50>/EnablePI3' */
  rtB_EnablePI1_MGCCode_Ori EnablePI2_b;/* '<S50>/EnablePI2' */
  rtB_EnablePI1_MGCCode_Ori EnablePI1_o;/* '<S50>/EnablePI1' */
  rtB_EnablePI1_MGCCode_Ori EnablePI_g;/* '<S50>/EnablePI' */
  rtB_ModeSelect_MGCCode_Ori sf_ModeSelect1_l;/* '<S38>/ModeSelect1' */
  rtB_EnablePI1_MGCCode_Ori EnablePI7; /* '<S38>/EnablePI7' */
  rtB_EnablePI1_MGCCode_Ori EnablePI6; /* '<S38>/EnablePI6' */
  rtB_EnablePI1_MGCCode_Ori EnablePI5_p;/* '<S38>/EnablePI5' */
  rtB_EnablePI1_MGCCode_Ori EnablePI_b;/* '<S38>/EnablePI' */
  rtB_ModeSelect_MGCCode_Ori sf_ModeSelect;/* '<S25>/ModeSelect' */
  rtB_EnablePI1_MGCCode_Ori EnablePI3; /* '<S25>/EnablePI3' */
  rtB_EnablePI1_MGCCode_Ori EnablePI2; /* '<S25>/EnablePI2' */
  rtB_EnablePI1_MGCCode_Ori EnablePI1_m;/* '<S25>/EnablePI1' */
  rtB_EnablePI1_MGCCode_Ori EnablePI;  /* '<S25>/EnablePI' */
  rtB_EnablePI5_MGCCode_Ori EnablePI8; /* '<S2>/EnablePI8' */
  rtB_EnablePI5_MGCCode_Ori EnablePI5; /* '<S2>/EnablePI5' */
  rtB_EnablePI1_MGCCode_Ori EnablePI4; /* '<S2>/EnablePI4' */
  rtB_EnablePI1_MGCCode_Ori EnablePI1; /* '<S2>/EnablePI1' */
} BlockIO_MGCCode_Ori;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T count;                      /* '<S1>/MicrogridModelManager' */
  real32_T PassiveIslandSignal;        /* '<S1>/MicrogridModelManager' */
  real32_T Pload;                      /* '<S1>/MicrogridModelManager' */
  real32_T IslandCount;                /* '<S1>/MicrogridModelManager' */
  real32_T IslandFailCount;            /* '<S1>/MicrogridModelManager' */
  real32_T GridFailCount;              /* '<S1>/MicrogridModelManager' */
  real32_T GridCount;                  /* '<S1>/MicrogridModelManager' */
  uint32_T temporalCounter_i1;         /* '<S1>/MicrogridModelManager' */
  uint32_T temporalCounter_i2;         /* '<S1>/MicrogridModelManager' */
  SystemMode RateTransition1_1_Buffer0;/* '<S1>/Rate Transition1' */
  GenMode RateTransition1_2_Buffer0;   /* '<S1>/Rate Transition1' */
  GenMode RateTransition1_3_Buffer0;   /* '<S1>/Rate Transition1' */
  GenMode RateTransition1_4_Buffer0;   /* '<S1>/Rate Transition1' */
  GenMode RateTransition1_5_Buffer0;   /* '<S1>/Rate Transition1' */
  GenMode RateTransition1_6_Buffer0;   /* '<S1>/Rate Transition1' */
  uint16_T is_active_c15_MGCCode_Ori;  /* '<S1>/MicrogridModelManager' */
  uint16_T is_c15_MGCCode_Ori;         /* '<S1>/MicrogridModelManager' */
  uint16_T is_Logic;                   /* '<S1>/MicrogridModelManager' */
  uint16_T is_GridOperation;           /* '<S1>/MicrogridModelManager' */
  uint16_T is_IslandOperation;         /* '<S1>/MicrogridModelManager' */
  uint16_T temporalCounter_i3;         /* '<S1>/MicrogridModelManager' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI3_l;/* '<S50>/EnablePI3' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI2_b;/* '<S50>/EnablePI2' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI1_o;/* '<S50>/EnablePI1' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI_g;/* '<S50>/EnablePI' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI7;/* '<S38>/EnablePI7' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI6;/* '<S38>/EnablePI6' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI5_p;/* '<S38>/EnablePI5' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI_b;/* '<S38>/EnablePI' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI3;/* '<S25>/EnablePI3' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI2;/* '<S25>/EnablePI2' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI1_m;/* '<S25>/EnablePI1' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI; /* '<S25>/EnablePI' */
  rtDW_EnablePI5_MGCCode_Ori EnablePI8;/* '<S2>/EnablePI8' */
  rtDW_EnablePI5_MGCCode_Ori EnablePI5;/* '<S2>/EnablePI5' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI4;/* '<S2>/EnablePI4' */
  rtDW_EnablePI1_MGCCode_Ori EnablePI1;/* '<S2>/EnablePI1' */
} D_Work_MGCCode_Ori;

/* Invariant block signals (auto storage) */
typedef struct {
  const real32_T Constant23;           /* '<S2>/Constant23' */
  const real32_T Constant24;           /* '<S2>/Constant24' */
  const real32_T Constant4;            /* '<S25>/Constant4' */
  const real32_T Constant2;            /* '<S25>/Constant2' */
  const real32_T Constant25;           /* '<S2>/Constant25' */
  const real32_T Constant26;           /* '<S2>/Constant26' */
  const real32_T Constant5;            /* '<S25>/Constant5' */
  const real32_T Constant3;            /* '<S25>/Constant3' */
  const real32_T Constant4_p;          /* '<S50>/Constant4' */
  const real32_T Constant2_h;          /* '<S50>/Constant2' */
  const real32_T Constant5_k;          /* '<S50>/Constant5' */
  const real32_T Constant3_d;          /* '<S50>/Constant3' */
  const real32_T Constant4_f;          /* '<S38>/Constant4' */
  const real32_T Constant2_m;          /* '<S38>/Constant2' */
  const real32_T Constant5_a;          /* '<S38>/Constant5' */
  const real32_T Constant3_n;          /* '<S38>/Constant3' */
} ConstBlockIO_MGCCode_Ori;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  InEMSRoot InEMSRootn;                /* '<Root>/InEMSRootn' */
  InSystemRoot InSystemRootn;          /* '<Root>/InSystemRootn' */
  InICE InICEn;                        /* '<Root>/InICEn' */
  InBat InBatn;                        /* '<Root>/InBatn' */
  InPV InPVn;                          /* '<Root>/InPVn' */
  InDFIG1 InDFIG1n;                    /* '<Root>/InDFIG1n' */
  InDFIG2 InDFIG2n;                    /* '<Root>/InDFIG2n' */
} ExternalInputs_MGCCode_Ori;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  OutICE OutICEn;                      /* '<Root>/OutICEn' */
  OutBat OutBatn;                      /* '<Root>/OutBatn' */
  OutPV OutPVn;                        /* '<Root>/OutPVn' */
  OutDFIG1 OutDFIG1n;                  /* '<Root>/OutDFIG1n' */
  OutDFIG1 OutDFIG2n;                  /* '<Root>/OutDFIG2n' */
  boolean_T Islandsignal;              /* '<Root>/Islandsignal' */
  Warning Warningn;                    /* '<Root>/Warningn ' */
  StabControl EmergencyControl;        /* '<Root>/EmergencyControl' */
  Obe Observen;                        /* '<Root>/Observen' */
  real32_T Param;                      /* '<Root>/Param' */
  real32_T LineP;                      /* '<Root>/LineP' */
  real32_T LineQ;                      /* '<Root>/LineQ' */
  boolean_T SyncSignal;                /* '<Root>/SyncSignal ' */
} ExternalOutputs_MGCCode_Ori;

/* Parameters (auto storage) */
struct Parameters_MGCCode_Ori_ {
  BASE Base;                           /* Variable: Base
                                        * Referenced by:
                                        *   '<S1>/MicrogridModelManager'
                                        *   '<S2>/Constant1'
                                        *   '<S2>/Constant10'
                                        *   '<S2>/Constant2'
                                        *   '<S2>/Constant3'
                                        *   '<S5>/Constant'
                                        *   '<S5>/Constant1'
                                        *   '<S9>/Constant16'
                                        *   '<S9>/Constant17'
                                        *   '<S23>/Constant1'
                                        *   '<S23>/Constant3'
                                        *   '<S23>/Constant6'
                                        *   '<S23>/Constant9'
                                        *   '<S37>/Constant1'
                                        *   '<S37>/Constant3'
                                        *   '<S37>/Constant6'
                                        *   '<S48>/Constant1'
                                        *   '<S48>/Constant3'
                                        *   '<S48>/Constant6'
                                        */
  ISLANDPARAM IslandParam;             /* Variable: IslandParam
                                        * Referenced by: '<S1>/MicrogridModelManager'
                                        */
  GRIDPARAM GridParam;                 /* Variable: GridParam
                                        * Referenced by: '<S1>/MicrogridModelManager'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_MGCCode_Ori {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern Parameters_MGCCode_Ori MGCCode_Ori_P;

/* Block signals (auto storage) */
extern BlockIO_MGCCode_Ori MGCCode_Ori_B;

/* Block states (auto storage) */
extern D_Work_MGCCode_Ori MGCCode_Ori_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_MGCCode_Ori MGCCode_Ori_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_MGCCode_Ori MGCCode_Ori_Y;
extern const ConstBlockIO_MGCCode_Ori MGCCode_Ori_ConstB;/* constant block i/o */

/* External data declarations for dependent source files */
extern const InEMSRoot MGCCode_Ori_rtZInEMSRoot;/* InEMSRoot ground */
extern const OutEMS MGCCode_Ori_rtZOutEMS;/* OutEMS ground */
extern const InEMS MGCCode_Ori_rtZInEMS;/* InEMS ground */

/* Model entry point functions */
extern void MGCCode_Ori_initialize(void);
extern void MGCCode_Ori_step(void);
extern void MGCCode_Ori_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MGCCode_Ori *const MGCCode_Ori_M;

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
 * '<Root>' : 'MGCCode_Ori'
 * '<S1>'   : 'MGCCode_Ori/MGCC1'
 * '<S2>'   : 'MGCCode_Ori/MGCC1/AGCandAVC1'
 * '<S3>'   : 'MGCCode_Ori/MGCC1/BatControl2'
 * '<S4>'   : 'MGCCode_Ori/MGCC1/DFIG1Control'
 * '<S5>'   : 'MGCCode_Ori/MGCC1/LinePQMeasurement'
 * '<S6>'   : 'MGCCode_Ori/MGCC1/MicrogridModelManager'
 * '<S7>'   : 'MGCCode_Ori/MGCC1/PVControl2'
 * '<S8>'   : 'MGCCode_Ori/MGCC1/Subsystem2'
 * '<S9>'   : 'MGCCode_Ori/MGCC1/SystemRatio'
 * '<S10>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI1'
 * '<S11>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI2'
 * '<S12>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI3'
 * '<S13>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI4'
 * '<S14>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI5'
 * '<S15>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI8'
 * '<S16>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/ModeSelect1'
 * '<S17>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI1/Clamping circuit'
 * '<S18>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI2/Clamping circuit'
 * '<S19>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI3/Clamping circuit'
 * '<S20>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI4/Clamping circuit'
 * '<S21>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI5/Clamping circuit'
 * '<S22>'  : 'MGCCode_Ori/MGCC1/AGCandAVC1/EnablePI8/Clamping circuit'
 * '<S23>'  : 'MGCCode_Ori/MGCC1/BatControl2/InputTrans'
 * '<S24>'  : 'MGCCode_Ori/MGCC1/BatControl2/OutputTrans'
 * '<S25>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator'
 * '<S26>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/BatChargeControl'
 * '<S27>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI'
 * '<S28>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI1'
 * '<S29>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI2'
 * '<S30>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI3'
 * '<S31>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/ModeSelect'
 * '<S32>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI/Clamping circuit'
 * '<S33>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI1/Clamping circuit'
 * '<S34>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI2/Clamping circuit'
 * '<S35>'  : 'MGCCode_Ori/MGCC1/BatControl2/PowerRegulator/EnablePI3/Clamping circuit'
 * '<S36>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/ OutputTrans'
 * '<S37>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/InputTrans'
 * '<S38>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator'
 * '<S39>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI'
 * '<S40>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI5'
 * '<S41>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI6'
 * '<S42>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI7'
 * '<S43>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/ModeSelect1'
 * '<S44>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI/Clamping circuit'
 * '<S45>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI5/Clamping circuit'
 * '<S46>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI6/Clamping circuit'
 * '<S47>'  : 'MGCCode_Ori/MGCC1/DFIG1Control/PowerRegulator/EnablePI7/Clamping circuit'
 * '<S48>'  : 'MGCCode_Ori/MGCC1/PVControl2/InputTrans'
 * '<S49>'  : 'MGCCode_Ori/MGCC1/PVControl2/OutputTrans'
 * '<S50>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator'
 * '<S51>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI'
 * '<S52>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI1'
 * '<S53>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI2'
 * '<S54>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI3'
 * '<S55>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/ModeSelect'
 * '<S56>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI/Clamping circuit'
 * '<S57>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI1/Clamping circuit'
 * '<S58>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI2/Clamping circuit'
 * '<S59>'  : 'MGCCode_Ori/MGCC1/PVControl2/PowerRegulator/EnablePI3/Clamping circuit'
 * '<S60>'  : 'MGCCode_Ori/MGCC1/Subsystem2/Speed & Pitch Control'
 * '<S61>'  : 'MGCCode_Ori/MGCC1/Subsystem2/Subsystem'
 * '<S62>'  : 'MGCCode_Ori/MGCC1/Subsystem2/Subsystem1'
 */
#endif                                 /* RTW_HEADER_MGCCode_Ori_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
