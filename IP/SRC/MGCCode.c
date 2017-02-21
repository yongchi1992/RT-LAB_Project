/*
 * File: MGCCode.c
 *
 * Code generated for Simulink model 'MGCCode'.
 *
 * Model version                  : 1.26
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Thu Mar 13 21:28:25 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MGCCode.h"
#include "MGCCode_private.h"

/* Named constants for Chart: '<S1>/MicrogridModelManager' */
#define MGCCode_IN_AGC                 ((uint8_T)1U)
#define MGCCode_IN_ActiveGrid          ((uint8_T)1U)
#define MGCCode_IN_ActiveIsland        ((uint8_T)2U)
#define MGCCode_IN_ConstPConstQ        ((uint8_T)3U)
#define MGCCode_IN_Failure             ((uint8_T)1U)
#define MGCCode_IN_GridOperation       ((uint8_T)2U)
#define MGCCode_IN_Independent         ((uint8_T)4U)
#define MGCCode_IN_Island              ((uint8_T)2U)
#define MGCCode_IN_IslandAGC           ((uint8_T)3U)
#define MGCCode_IN_IslandOperation     ((uint8_T)3U)
#define MGCCode_IN_Logic               ((uint8_T)1U)
#define MGCCode_IN_NO_ACTIVE_CHILD     ((uint8_T)0U)
#define MGCCode_IN_ShutDown            ((uint8_T)4U)
#define MGCCode_IN_Start               ((uint8_T)5U)

const InEMSRoot MGCCode_rtZInEMSRoot = {
  Start,                               /* SystemModen */
  ConstPQ,                             /* ICEMode */
  ConstPQ,                             /* BatMode */
  ConstPQ,                             /* PVMode */
  ConstPQ,                             /* DFIG1Mode */
  ConstPQ                              /* DFIG2Mode */
} ;                                    /* InEMSRoot ground */

const OutEMS MGCCode_rtZOutEMS = {
  Start,                               /* SystemModen */
  ConstPQ,                             /* ICEMode */
  ConstPQ,                             /* BatMode */
  ConstPQ,                             /* PVMode */
  ConstPQ,                             /* DFIG1Mode */
  ConstPQ                              /* DFIG2Mode */
} ;                                    /* OutEMS ground */

const InEMS MGCCode_rtZInEMS = {
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
BlockIO_MGCCode MGCCode_B;

/* Block states (auto storage) */
D_Work_MGCCode MGCCode_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_MGCCode MGCCode_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_MGCCode MGCCode_Y;

/* Real-time model */
RT_MODEL_MGCCode MGCCode_M_;
RT_MODEL_MGCCode *const MGCCode_M = &MGCCode_M_;

/* Forward declaration for local functions */
static Status MGCCode_status(boolean_T ICE, boolean_T DFIG1, boolean_T DFIG2,
  boolean_T PV, boolean_T Bat);
static boolean_T MGCCode_PassiveIsland(real32_T Freq);
static real32_T MGCCode_EmergencyControl(boolean_T PassiveIslandSignal, real32_T
  Pload, real32_T Pmax);
static void MGCCode_PreventiveControl(real32_T Pline, real32_T Pload, real32_T
  Pmax, real32_T *Pre_LinePowerCmd, real32_T *Pre_LoadShedding, real32_T
  *Pre_Pclear, boolean_T *Pre_CutEn);
static void MGCCode_fcn(real32_T LineP, real32_T LineQ, boolean_T *IslandSignal,
  Warning *Warning_0);
static void MGCCode_Logic(void);
static void rate_scheduler(void);
real32_T look1_iflf_binlxpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex)
{
  real32_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

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
  (MGCCode_M->Timing.TaskCounters.TID[1])++;
  if ((MGCCode_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.1s, 0.0s] */
    MGCCode_M->Timing.TaskCounters.TID[1] = 0;
  }

  (MGCCode_M->Timing.TaskCounters.TID[2])++;
  if ((MGCCode_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.5s, 0.0s] */
    MGCCode_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * Output and update for atomic system:
 *    '<S27>/ModeSelect'
 *    '<S64>/ModeSelect'
 */
void MGCCode_ModeSelect(GenMode rtu_modeselect, rtB_ModeSelect_MGCCode *localB)
{
  /* MATLAB Function 'MGCC2/BatControl/PowerRegulator/ModeSelect': '<S33>:1' */
  if (rtu_modeselect == ConstPQ) {
    /* '<S33>:1:3' */
    /* ConstP ConstQ */
    /* '<S33>:1:4' */
    localB->PCtrl = 0;

    /* '<S33>:1:5' */
    localB->QCtrl = 0;
  } else if (rtu_modeselect == ConstPAVC) {
    /* '<S33>:1:6' */
    /* ConstP AVC */
    /* '<S33>:1:7' */
    localB->PCtrl = 0;

    /* '<S33>:1:8' */
    localB->QCtrl = 1;
  } else if (rtu_modeselect == AGCConstQ) {
    /* '<S33>:1:9' */
    /* AGC ConstQ */
    /* '<S33>:1:10' */
    localB->PCtrl = 1;

    /* '<S33>:1:11' */
    localB->QCtrl = 0;
  } else if (rtu_modeselect == AGCAVC) {
    /* '<S33>:1:12' */
    /* AGC AVC */
    /* '<S33>:1:13' */
    localB->PCtrl = 1;

    /* '<S33>:1:14' */
    localB->QCtrl = 1;
  } else {
    /* '<S33>:1:16' */
    localB->PCtrl = 0;

    /* '<S33>:1:17' */
    localB->QCtrl = 0;
  }
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static Status MGCCode_status(boolean_T ICE, boolean_T DFIG1, boolean_T DFIG2,
  boolean_T PV, boolean_T Bat)
{
  Status Status_0;
  boolean_T aVarTruthTableCondition;

  /* Truth Table Function 'status': '<S8>:999' */
  Status_0 = All;

  /* Condition '#1': '<S8>:1246' */
  /*  ICE is online  */
  aVarTruthTableCondition = (ICE == 1);

  /* Condition '#2': '<S8>:1248' */
  /*  DFIG1 is online  */
  /* Condition '#3': '<S8>:1250' */
  /*  DFIG2 is online  */
  /* Condition '#4': '<S8>:1252' */
  /*  Bat is online  */
  /* Condition '#5': '<S8>:1254' */
  /*  PV is online  */
  if (!(aVarTruthTableCondition && DFIG1 && DFIG2 && Bat && PV)) {
    if (aVarTruthTableCondition && DFIG1 && DFIG2 && Bat && (!PV)) {
      /* Decision 'D2': '<S8>:1262' */
      /* Action '2': '<S8>:1264' */
      /*  'ID1D2B':  */
      Status_0 = ID1D2B;
    } else if (aVarTruthTableCondition && DFIG1 && DFIG2 && (!Bat) && PV) {
      /* Decision 'D3': '<S8>:1268' */
      /* Action '3': '<S8>:1270' */
      /*  'ID1D2P':  */
      Status_0 = ID1D2P;
    } else if (aVarTruthTableCondition && DFIG1 && DFIG2 && (!Bat) && (!PV)) {
      /* Decision 'D4': '<S8>:1274' */
      /* Action '4': '<S8>:1276' */
      /*  'ID1D2':  */
      Status_0 = ID1D2;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && Bat && PV) {
      /* Decision 'D5': '<S8>:1280' */
      /* Action '5': '<S8>:1282' */
      /*  'ID1BP':  */
      Status_0 = ID1BP;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && Bat && (!PV)) {
      /* Decision 'D6': '<S8>:1286' */
      /* Action '6': '<S8>:1288' */
      /*  'ID1B':  */
      Status_0 = ID1B;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && (!Bat) && PV) {
      /* Decision 'D7': '<S8>:1292' */
      /* Action '7': '<S8>:1294' */
      /*  'ID1P':  */
      Status_0 = ID1P;
    } else if (aVarTruthTableCondition && DFIG1 && (!DFIG2) && (!Bat) && (!PV))
    {
      /* Decision 'D8': '<S8>:1298' */
      /* Action '8': '<S8>:1300' */
      /*  'ID1':  */
      Status_0 = ID1;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && Bat && PV) {
      /* Decision 'D9': '<S8>:1304' */
      /* Action '9': '<S8>:1306' */
      /*  'ID2BP':  */
      Status_0 = ID2BP;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && Bat && (!PV)) {
      /* Decision 'D10': '<S8>:1310' */
      /* Action '10': '<S8>:1312' */
      /*  'ID2B':  */
      Status_0 = ID2B;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && (!Bat) && PV) {
      /* Decision 'D11': '<S8>:1316' */
      /* Action '11': '<S8>:1318' */
      /*  'ID2P':  */
      Status_0 = ID2P;
    } else if (aVarTruthTableCondition && (!DFIG1) && DFIG2 && (!Bat) && (!PV))
    {
      /* Decision 'D12': '<S8>:1322' */
      /* Action '12': '<S8>:1324' */
      /*  'ID2':  */
      Status_0 = ID2;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && Bat && PV) {
      /* Decision 'D13': '<S8>:1328' */
      /* Action '13': '<S8>:1330' */
      /*  'IBP':  */
      Status_0 = IBP;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && Bat && (!PV))
    {
      /* Decision 'D14': '<S8>:1334' */
      /* Action '14': '<S8>:1336' */
      /*  'IB':  */
      Status_0 = IB;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && (!Bat) && PV)
    {
      /* Decision 'D15': '<S8>:1340' */
      /* Action '15': '<S8>:1342' */
      /*  'IP':  */
      Status_0 = IP;
    } else if (aVarTruthTableCondition && (!DFIG1) && (!DFIG2) && (!Bat) && (!PV))
    {
      /* Decision 'D16': '<S8>:1346' */
      /* Action '16': '<S8>:1348' */
      /*  'I':  */
      Status_0 = I;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && Bat && PV) {
      /* Decision 'D17': '<S8>:1352' */
      /* Action '17': '<S8>:1354' */
      /*  'D1D2BP':  */
      Status_0 = D1D2BP;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && Bat && (!PV)) {
      /* Decision 'D18': '<S8>:1358' */
      /* Action '18': '<S8>:1360' */
      /*  'D1D2B':  */
      Status_0 = D1D2B;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && (!Bat) && PV) {
      /* Decision 'D19': '<S8>:1364' */
      /* Action '19': '<S8>:1366' */
      /*  'D1D2P':  */
      Status_0 = D1D2P;
    } else if ((!aVarTruthTableCondition) && DFIG1 && DFIG2 && (!Bat) && (!PV))
    {
      /* Decision 'D20': '<S8>:1370' */
      /* Action '20': '<S8>:1372' */
      /*  'D1D2':  */
      Status_0 = D1D2;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && Bat && PV) {
      /* Decision 'D21': '<S8>:1376' */
      /* Action '21': '<S8>:1378' */
      /*  'D1BP':  */
      Status_0 = D1BP;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && Bat && (!PV))
    {
      /* Decision 'D22': '<S8>:1382' */
      /* Action '22': '<S8>:1384' */
      /*  'D1B':  */
      Status_0 = D1B;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && (!Bat) && PV)
    {
      /* Decision 'D23': '<S8>:1388' */
      /* Action '23': '<S8>:1390' */
      /*  'D1P':  */
      Status_0 = D1P;
    } else if ((!aVarTruthTableCondition) && DFIG1 && (!DFIG2) && (!Bat) && (!PV))
    {
      /* Decision 'D24': '<S8>:1394' */
      /* Action '24': '<S8>:1396' */
      /*  'D1':  */
      Status_0 = D1;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && Bat && PV) {
      /* Decision 'D25': '<S8>:1400' */
      /* Action '25': '<S8>:1402' */
      /*  'D2BP':  */
      Status_0 = D2BP;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && Bat && (!PV))
    {
      /* Decision 'D26': '<S8>:1406' */
      /* Action '26': '<S8>:1408' */
      /*  'D2B':  */
      Status_0 = D2B;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && (!Bat) && PV)
    {
      /* Decision 'D27': '<S8>:1412' */
      /* Action '27': '<S8>:1414' */
      /*  'D2P':  */
      Status_0 = D2P;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && DFIG2 && (!Bat) && (!PV))
    {
      /* Decision 'D28': '<S8>:1418' */
      /* Action '28': '<S8>:1420' */
      /*  'D2':  */
      Status_0 = D2;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && Bat && PV)
    {
      /* Decision 'D29': '<S8>:1424' */
      /* Action '29': '<S8>:1426' */
      /*  'BP':  */
      Status_0 = BP;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && Bat && (!PV))
    {
      /* Decision 'D30': '<S8>:1430' */
      /* Action '30': '<S8>:1432' */
      /*  'B':  */
      Status_0 = B;
    } else if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && (!Bat) &&
               PV) {
      /* Decision 'D31': '<S8>:1436' */
      /* Action '31': '<S8>:1438' */
      /*  'P':  */
      Status_0 = P;
    } else {
      if ((!aVarTruthTableCondition) && (!DFIG1) && (!DFIG2) && (!Bat) && (!PV))
      {
        /* Decision 'D32': '<S8>:1442' */
        /* Action '32': '<S8>:1444' */
        /*  'Fail':  */
        Status_0 = Fail;
      }
    }
  } else {
    /* Decision 'D1': '<S8>:1256' */
    /* Action '1': '<S8>:1258' */
    /*  'All':  */
  }

  return Status_0;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static boolean_T MGCCode_PassiveIsland(real32_T Freq)
{
  boolean_T PassiveIslandSignal;

  /* MATLAB Function 'PassiveIsland': '<S8>:1463' */
  if ((Freq <= 50.1) && (Freq >= 49.9)) {
    /* '<S8>:1463:2' */
    /* '<S8>:1463:3' */
    MGCCode_DWork.count = 0.0F;
  } else if (((Freq > 50.1) && (Freq <= 50.5F)) || ((Freq >= 49.5F) && (Freq <
               49.9))) {
    /* '<S8>:1463:4' */
    /* '<S8>:1463:5' */
    MGCCode_DWork.count++;
  } else if (((Freq > 50.5F) && (Freq <= 51.0F)) || ((Freq >= 49.0F) && (Freq <
               49.5F))) {
    /* '<S8>:1463:6' */
    /* '<S8>:1463:7' */
    MGCCode_DWork.count += 10.0F;
  } else {
    /* '<S8>:1463:9' */
    MGCCode_DWork.count += 50.0F;
  }

  if (MGCCode_DWork.count >= 50.0F) {
    /* '<S8>:1463:12' */
    /* '<S8>:1463:13' */
    PassiveIslandSignal = TRUE;
  } else {
    /* '<S8>:1463:15' */
    PassiveIslandSignal = FALSE;
  }

  return PassiveIslandSignal;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static real32_T MGCCode_EmergencyControl(boolean_T PassiveIslandSignal, real32_T
  Pload, real32_T Pmax)
{
  real32_T E_Pclear;

  /* MATLAB Function 'EmergencyControl': '<S8>:1460' */
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
  /* % 被动孤网 */
  if (PassiveIslandSignal == 1) {
    /* '<S8>:1460:16' */
    /* '<S8>:1460:17' */
    E_Pclear = Pmax * MGCCode_P.Base.TotalRatioUp - Pload;
    if (E_Pclear <= 0.0F) {
      /* '<S8>:1460:18' */
      /* '<S8>:1460:19' */
      E_Pclear = 0.0F;
    }
  } else {
    /* '<S8>:1460:21' */
    E_Pclear = 0.0F;
  }

  /* % 外网故障 */
  return E_Pclear;
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_PreventiveControl(real32_T Pline, real32_T Pload, real32_T
  Pmax, real32_T *Pre_LinePowerCmd, real32_T *Pre_LoadShedding, real32_T
  *Pre_Pclear, boolean_T *Pre_CutEn)
{
  /* MATLAB Function 'PreventiveControl': '<S8>:1450' */
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
  /* % 系统外送功率 */
  if (Pline >= 0.0F) {
    /* '<S8>:1450:16' */
    /* '<S8>:1450:17' */
    *Pre_LinePowerCmd = Pline - Pmax * MGCCode_P.Base.LineRatioUp;

    /* '<S8>:1450:18' */
    *Pre_LoadShedding = 0.0F;

    /* '<S8>:1450:19' */
    *Pre_Pclear = 0.0F;

    /* '<S8>:1450:20' */
    *Pre_CutEn = FALSE;
  } else {
    /* '<S8>:1450:22' */
    *Pre_LinePowerCmd = 1.0E+16F;

    /* '<S8>:1450:23' */
    *Pre_LoadShedding = Pload - MGCCode_P.Base.LoadRatioUp * Pmax;
    if (*Pre_LoadShedding <= 0.0F) {
      /* '<S8>:1450:24' */
      /* '<S8>:1450:25' */
      *Pre_LoadShedding = 0.0F;
    }

    /* '<S8>:1450:27' */
    *Pre_Pclear = (Pload - Pmax * MGCCode_P.Base.TotalRatioUp) -
      *Pre_LoadShedding;
    if (*Pre_Pclear <= 0.0F) {
      /* '<S8>:1450:28' */
      /* '<S8>:1450:29' */
      *Pre_Pclear = 0.0F;

      /* '<S8>:1450:30' */
      *Pre_CutEn = FALSE;
    } else {
      /* '<S8>:1450:32' */
      *Pre_CutEn = TRUE;
    }
  }

  /* % 风机转速控制 */
  /* % 电池SOC过低 */
  /* % 系统等效ratio过高 */
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_fcn(real32_T LineP, real32_T LineQ, boolean_T *IslandSignal,
  Warning *Warning_0)
{
  /* Graphical Function 'fcn': '<S8>:292' */
  *IslandSignal = FALSE;
  *Warning_0 = None;

  /* Transition: '<S8>:297' */
  if (((real32_T)fabs(LineP / MGCCode_P.Base.LineP) <= 0.2) && ((real32_T)fabs
       (LineQ / MGCCode_P.Base.LineQ) <= 0.2)) {
    /* Transition: '<S8>:301' */
    MGCCode_DWork.IslandCount++;
    if (MGCCode_DWork.IslandCount == 100.0F) {
      /* Transition: '<S8>:307' */
      *IslandSignal = TRUE;
    } else {
      /* Transition: '<S8>:1227' */
    }
  } else {
    /* Transition: '<S8>:300' */
    MGCCode_DWork.IslandFailCount++;
    MGCCode_DWork.IslandCount = 0.0F;
    if (MGCCode_DWork.IslandFailCount == 100000.0F) {
      /* Transition: '<S8>:306' */
      *Warning_0 = IslandFail;
    } else {
      /* Transition: '<S8>:1226' */
    }
  }
}

/* Function for Chart: '<S1>/MicrogridModelManager' */
static void MGCCode_Logic(void)
{
  boolean_T Pre_CutEn;
  real32_T Pre_Pclear;
  real32_T Pre_LoadShedding;
  real32_T Pre_LinePowerCmd;
  Warning Warning_0;
  real32_T Status_0;

  /* During 'Logic': '<S8>:1229' */
  Status_0 = (real32_T)(int32_T)MGCCode_status
    (MGCCode_B.BusConversion_InsertedFor_Mic_l.ICEStatus,
     MGCCode_B.BusConversion_InsertedFor_Mic_l.BatStatus,
     MGCCode_B.BusConversion_InsertedFor_Mic_l.PVStatus,
     MGCCode_B.BusConversion_InsertedFor_Mic_l.DFIG1Status,
     MGCCode_B.BusConversion_InsertedFor_Mic_l.DFIG2Status);
  switch (MGCCode_DWork.is_Logic) {
   case MGCCode_IN_Failure:
    /* During 'Failure': '<S8>:39' */
    break;

   case MGCCode_IN_GridOperation:
    /* During 'GridOperation': '<S8>:38' */
    if (MGCCode_Y.Islandsignal || (MGCCode_DWork.PassiveIslandSignal == 1.0F)) {
      /* Transition: '<S8>:319' */
      /* Exit Internal 'GridOperation': '<S8>:38' */
      MGCCode_DWork.is_GridOperation = MGCCode_IN_NO_ACTIVE_CHILD;
      MGCCode_DWork.is_Logic = MGCCode_IN_IslandOperation;

      /* Entry 'IslandOperation': '<S8>:317' */
      MGCCode_B.OutEMS_m.SystemModen = Island;
      MGCCode_Y.Islandsignal = TRUE;
      ModeSwitch(Island);

      /* Entry Internal 'IslandOperation': '<S8>:317' */
      /* Transition: '<S8>:326' */
      MGCCode_DWork.is_IslandOperation = MGCCode_IN_Island;

      /* Entry 'Island': '<S8>:322' */
      MGCCode_B.OutEMS_m.SystemModen = Island;
      MGCCode_B.OutEMS_m.ICEMode = AGCAVC;
      MGCCode_B.OutEMS_m.PVMode = AGCAVC;
      MGCCode_B.OutEMS_m.DFIG1Mode = AGCAVC;
      MGCCode_B.OutEMS_m.DFIG2Mode = AGCAVC;
      MGCCode_B.OutEMS_m.BatMode = AGCAVC;
    } else {
      Status_0 = MGCCode_B.BusConversion_InsertedFor_Micro.Pout -
        MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineP;
      MGCCode_DWork.PassiveIslandSignal = MGCCode_PassiveIsland
        (MGCCode_B.BusConversion_InsertedFor_Mi_l1.Fmeas);
      MGCCode_Y.EmergencyControl.EC_Pclear = MGCCode_EmergencyControl
        (MGCCode_DWork.PassiveIslandSignal != 0.0F, Status_0,
         MGCCode_B.BusConversion_InsertedFor_Micro.Pmax);
      if (MGCCode_DWork.temporalCounter_i1 == 60U) {
        MGCCode_PreventiveControl
          (MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineP, Status_0,
           MGCCode_B.BusConversion_InsertedFor_Micro.Pmax, &Pre_LinePowerCmd,
           &Pre_LoadShedding, &Pre_Pclear, &Pre_CutEn);
        MGCCode_Y.EmergencyControl.Pre_LoadShedding = Pre_LoadShedding;
        MGCCode_Y.EmergencyControl.Pre_Pclear = Pre_Pclear;
        MGCCode_Y.EmergencyControl.Pre_CutEn = Pre_CutEn;
      }

      if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen == ConstPConstQ)
          && (!(MGCCode_DWork.is_GridOperation == MGCCode_IN_ConstPConstQ))) {
        /* Transition: '<S8>:73' */
        /* Exit Internal 'GridOperation': '<S8>:38' */
        MGCCode_DWork.is_GridOperation = MGCCode_IN_ConstPConstQ;

        /* Entry 'ConstPConstQ': '<S8>:33' */
        MGCCode_B.OutEMS_m.SystemModen = ConstPConstQ;
        MGCCode_B.OutEMS_m.ICEMode = ConstPQ;
        MGCCode_B.OutEMS_m.DFIG1Mode = ConstPQ;
        MGCCode_B.OutEMS_m.DFIG2Mode = ConstPQ;
        MGCCode_B.OutEMS_m.BatMode = ConstPQ;
        MGCCode_B.OutEMS_m.PVMode = ConstPQ;
      } else if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen == AGC) &&
                 (!(MGCCode_DWork.is_GridOperation == MGCCode_IN_AGC))) {
        /* Transition: '<S8>:74' */
        /* Exit Internal 'GridOperation': '<S8>:38' */
        MGCCode_DWork.is_GridOperation = MGCCode_IN_AGC;

        /* Entry 'AGC': '<S8>:34' */
        MGCCode_B.OutEMS_m.SystemModen = AGC;
        MGCCode_B.OutEMS_m.ICEMode = AGCAVC;
        MGCCode_B.OutEMS_m.DFIG1Mode = AGCAVC;
        MGCCode_B.OutEMS_m.DFIG2Mode = AGCAVC;
        MGCCode_B.OutEMS_m.BatMode = AGCAVC;
        MGCCode_B.OutEMS_m.PVMode = AGCAVC;
      } else if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen ==
                  Independent) && (!(MGCCode_DWork.is_GridOperation ==
                   MGCCode_IN_Independent))) {
        /* Transition: '<S8>:75' */
        /* Exit Internal 'GridOperation': '<S8>:38' */
        MGCCode_DWork.is_GridOperation = MGCCode_IN_Independent;
      } else if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen ==
                  ActiveIsland) && (!(MGCCode_DWork.is_GridOperation ==
                   MGCCode_IN_ActiveIsland))) {
        /* Transition: '<S8>:76' */
        /* Exit Internal 'GridOperation': '<S8>:38' */
        MGCCode_DWork.is_GridOperation = MGCCode_IN_ActiveIsland;

        /* Entry 'ActiveIsland': '<S8>:35' */
        MGCCode_B.OutEMS_m.SystemModen = AGC;
        MGCCode_B.OutEMS_m.ICEMode = AGCAVC;
        MGCCode_B.OutEMS_m.DFIG1Mode = AGCAVC;
        MGCCode_B.OutEMS_m.DFIG2Mode = AGCAVC;
        MGCCode_B.OutEMS_m.BatMode = AGCAVC;
        MGCCode_B.OutEMS_m.PVMode = AGCAVC;
        MGCCode_B.OutSystem_e.LinePref = 0.0F;
        MGCCode_B.OutSystem_e.LineQref = 0.0F;
        MGCCode_B.OutSystem_e.Fref = 50.0F;
        MGCCode_B.OutSystem_e.Vref = 0.95F;
        MGCCode_DWork.IslandCount = 0.0F;
        MGCCode_DWork.IslandFailCount = 0.0F;
        MGCCode_Y.Islandsignal = FALSE;
        MGCCode_Y.Warningn = None;
      } else {
        switch (MGCCode_DWork.is_GridOperation) {
         case MGCCode_IN_AGC:
          /* During 'AGC': '<S8>:34' */
          MGCCode_B.OutSystem_e.LinePref =
            MGCCode_B.BusConversion_InsertedFor_Mi_l1.LinePref;
          MGCCode_B.OutSystem_e.LineQref =
            MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineQref;
          break;

         case MGCCode_IN_ActiveIsland:
          /* During 'ActiveIsland': '<S8>:35' */
          MGCCode_fcn(MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineP,
                      MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineQ,
                      &Pre_CutEn, &Warning_0);
          MGCCode_Y.Islandsignal = Pre_CutEn;
          MGCCode_Y.Warningn = Warning_0;
          break;

         case MGCCode_IN_ConstPConstQ:
          /* During 'ConstPConstQ': '<S8>:33' */
          break;

         default:
          /* During 'Independent': '<S8>:36' */
          break;
        }
      }
    }
    break;

   case MGCCode_IN_IslandOperation:
    /* During 'IslandOperation': '<S8>:317' */
    if (!MGCCode_Y.Islandsignal) {
      /* Transition: '<S8>:320' */
      /* Exit Internal 'IslandOperation': '<S8>:317' */
      MGCCode_DWork.is_IslandOperation = MGCCode_IN_NO_ACTIVE_CHILD;
      MGCCode_DWork.is_Logic = MGCCode_IN_GridOperation;
      MGCCode_DWork.temporalCounter_i1 = 0U;

      /* Entry 'GridOperation': '<S8>:38' */
      ModeSwitch(ConstPConstQ);

      /* Entry Internal 'GridOperation': '<S8>:38' */
      /* Transition: '<S8>:290' */
      MGCCode_DWork.is_GridOperation = MGCCode_IN_ConstPConstQ;

      /* Entry 'ConstPConstQ': '<S8>:33' */
      MGCCode_B.OutEMS_m.SystemModen = ConstPConstQ;
      MGCCode_B.OutEMS_m.ICEMode = ConstPQ;
      MGCCode_B.OutEMS_m.DFIG1Mode = ConstPQ;
      MGCCode_B.OutEMS_m.DFIG2Mode = ConstPQ;
      MGCCode_B.OutEMS_m.BatMode = ConstPQ;
      MGCCode_B.OutEMS_m.PVMode = ConstPQ;
    } else if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen == Island)
               && (!(MGCCode_DWork.is_IslandOperation == MGCCode_IN_Island))) {
      /* Transition: '<S8>:324' */
      /* Exit Internal 'IslandOperation': '<S8>:317' */
      MGCCode_DWork.is_IslandOperation = MGCCode_IN_Island;

      /* Entry 'Island': '<S8>:322' */
      MGCCode_B.OutEMS_m.SystemModen = Island;
      MGCCode_B.OutEMS_m.ICEMode = AGCAVC;
      MGCCode_B.OutEMS_m.PVMode = AGCAVC;
      MGCCode_B.OutEMS_m.DFIG1Mode = AGCAVC;
      MGCCode_B.OutEMS_m.DFIG2Mode = AGCAVC;
      MGCCode_B.OutEMS_m.BatMode = AGCAVC;
    } else if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen == Island)
               && (!(MGCCode_DWork.is_IslandOperation == MGCCode_IN_ActiveGrid)))
    {
      /* Transition: '<S8>:325' */
      /* Exit Internal 'IslandOperation': '<S8>:317' */
      MGCCode_DWork.is_IslandOperation = MGCCode_IN_ActiveGrid;

      /* Entry 'ActiveGrid': '<S8>:323' */
      MGCCode_B.OutEMS_m.SystemModen = ActiveGrid;
    } else {
      if ((MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen == IslandAGC) &&
          (!(MGCCode_DWork.is_IslandOperation == MGCCode_IN_IslandAGC))) {
        /* Transition: '<S8>:334' */
        /* Exit Internal 'IslandOperation': '<S8>:317' */
        MGCCode_DWork.is_IslandOperation = MGCCode_IN_IslandAGC;
      }
    }
    break;

   case MGCCode_IN_ShutDown:
    /* During 'ShutDown': '<S8>:3' */
    break;

   default:
    /* During 'Start': '<S8>:2' */
    if (MGCCode_DWork.temporalCounter_i2 >= 1) {
      /* Transition: '<S8>:40' */
      if (Status_0 == (int32_T)Fail) {
        /* Transition: '<S8>:41' */
        MGCCode_Y.Warningn = StartFail;
        MGCCode_DWork.is_Logic = MGCCode_IN_Failure;
      } else {
        if (Status_0 != (int32_T)Fail) {
          /* Transition: '<S8>:70' */
          MGCCode_DWork.is_Logic = MGCCode_IN_GridOperation;
          MGCCode_DWork.temporalCounter_i1 = 0U;

          /* Entry 'GridOperation': '<S8>:38' */
          ModeSwitch(ConstPConstQ);

          /* Entry Internal 'GridOperation': '<S8>:38' */
          /* Transition: '<S8>:290' */
          MGCCode_DWork.is_GridOperation = MGCCode_IN_ConstPConstQ;

          /* Entry 'ConstPConstQ': '<S8>:33' */
          MGCCode_B.OutEMS_m.SystemModen = ConstPConstQ;
          MGCCode_B.OutEMS_m.ICEMode = ConstPQ;
          MGCCode_B.OutEMS_m.DFIG1Mode = ConstPQ;
          MGCCode_B.OutEMS_m.DFIG2Mode = ConstPQ;
          MGCCode_B.OutEMS_m.BatMode = ConstPQ;
          MGCCode_B.OutEMS_m.PVMode = ConstPQ;
        }
      }
    }
    break;
  }
}

real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T tmp;
  real32_T tmp_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    tmp = (real32_T)fabs(u0);
    tmp_0 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (tmp == 1.0F) {
        y = (rtNaNF);
      } else if (tmp > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (tmp_0 == 0.0F) {
      y = 1.0F;
    } else if (tmp_0 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = (rtNaNF);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void MGCCode_step(void)
{
  /* local block i/o variables */
  real32_T rtb_DiscreteTimeIntegrator2;
  real32_T rtb_PoleYk1UkZeroUk1;
  real32_T rtb_DFIGR2PRelay;
  real32_T rtb_Switch;
  real32_T rtb_Switch_c;
  real32_T rtb_Switch_b;
  real32_T rtb_Switch_j;
  real32_T rtb_Saturation2;
  real32_T rtb_Saturation3;
  real32_T rtb_Switch_h;
  real32_T rtb_Switch2;
  real32_T rtb_Switch_ju;
  real32_T rtb_Switch_bm;
  real32_T rtb_Switch_k;
  real32_T rtb_Switch_jt;
  real32_T rtb_DFIGR2PSeamless1stOrder;
  real32_T rtb_DFIGR2PSeamless1stOrder1;
  real32_T rtb_Switch_e;
  real32_T rtb_Switch_hg;
  real32_T rtb_Switch_kd;
  real32_T rtb_Switch_pt;
  real32_T rtb_Switch2_j;
  real32_T rtb_Switch_gl;
  real32_T rtb_Switch_b1;
  real32_T rtb_Switch_pb;
  real32_T rtb_Switch_f;
  real32_T rtb_Switch_et;
  real32_T rtb_Switch2_a;
  real32_T rtb_Switch_l;
  real32_T rtb_Switch_n;
  real32_T rtb_Switch_o;
  real32_T rtb_Switch_kw;
  real32_T rtb_Switch_pk;
  real32_T rtb_Switch2_o;
  real32_T rtb_Switch_k2;
  real32_T rtb_Switch_o4;
  real32_T rtb_Switch_o2;
  real32_T rtb_Switch_o0;
  real32_T rtb_pitch_max_g;
  real32_T rtb_Switch_br;
  real32_T rtb_Switch_h2;
  real32_T rtb__2H_WT;
  real32_T rtb_DiscreteTimeIntegrator;
  real32_T rtb_Sum2_e;
  real32_T rtb__2H_WT2;
  real32_T rtb_wbase1;
  real32_T rtb_Sum1;
  GenMode rtb_BatMode_ly;
  GenMode rtb_ICEMode_lks;
  int8_T rtb_PCtrl;
  int8_T rtb_QCtrl;
  int8_T rtb_PCtrl_i;
  int8_T rtb_QCtrl_n;
  int8_T rtb_AGC;
  int8_T rtb_AVC;
  SystemMode rtb_SystemModen;
  GenMode rtb_ICEMode;
  GenMode rtb_BatMode;
  GenMode rtb_PVMode;
  GenMode rtb_DFIG1Mode;
  GenMode rtb_DFIG2Mode;
  real32_T rtb_Switch_g;
  real32_T rtb_Switch_p;
  real32_T rtb_DFIG1SPout;
  real32_T rtb_BatSPcmd;
  real32_T rtb_BatSQcmd;
  real32_T rtb_AGCref;
  real32_T rtb_AVCref;
  real32_T rtb_Divide5_l;
  real32_T rtb_Divide7_l;
  real32_T rtb_Divide2_g;
  real32_T rtb_Divide7_n;
  real32_T rtb_LineP_d;
  real32_T rtb_LineQ_b;
  real32_T rtb_Product_l;
  real32_T rtb_Product;
  real32_T rtb_Sum5;
  real32_T rtb_Sum_ky;
  real32_T rtb_Switch1;
  real32_T rtb_Gain_eq;
  real32_T rtb_PVSPcmd;
  real32_T rtb_Sum_l;
  real32_T rtb_Pmax;
  real32_T rtb_Integrator_c;
  real32_T rtb_DeadZone;
  real32_T rtb_Sqrt;
  real32_T rtb_DeadZone_d;
  real32_T rtb_Product2;
  real32_T rtb_Sum2;
  real32_T rtb_Cp;
  real32_T rtb_Integrator_a;
  real32_T rtb_Sum_e;
  real32_T rtb_Sum_p;
  GenMode rtb_PVMode_a115;
  boolean_T rtb_NotEqual_h;
  real32_T rtb_Add4;
  real32_T rtb_Add2;
  real32_T DFIGR2PSeamless1stOrder_tmp;
  real32_T DFIGR2PSeamless1stOrder1_tmp;
  real32_T u;
  real32_T rtb_Sum_ky_0;
  real32_T rtb_Sum_l_0;
  real32_T rtb_Pmax_0;
  real32_T rtb_Cp_0;

  /* BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_DFIG1SPout = MGCCode_U.InDFIG1n.DFIG1SPout;

  /* Outputs for Atomic SubSystem: '<Root>/MGCC2' */
  /* RateTransition: '<S1>/Rate Transition1' */
  if (MGCCode_M->Timing.TaskCounters.TID[1] == 0) {
    MGCCode_B.SystemModen = MGCCode_DWork.RateTransition1_1_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_B.ICEMode = MGCCode_DWork.RateTransition1_2_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_B.BatMode = MGCCode_DWork.RateTransition1_3_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_B.PVMode = MGCCode_DWork.RateTransition1_4_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_B.DFIG1Mode = MGCCode_DWork.RateTransition1_5_Buffer0;

    /* RateTransition: '<S1>/Rate Transition1' */
    MGCCode_B.DFIG2Mode = MGCCode_DWork.RateTransition1_6_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition1' */

  /* BusCreator: '<S1>/BusConversion_InsertedFor_MicrogridModelManager_at_inport_0' incorporates:
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InDFIG2n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   */
  MGCCode_B.BusConversion_InsertedFor_Mic_l.SystemModen = MGCCode_B.SystemModen;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.ICEMode = MGCCode_B.ICEMode;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.BatMode = MGCCode_B.BatMode;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.PVMode = MGCCode_B.PVMode;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.DFIG1Mode = MGCCode_B.DFIG1Mode;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.DFIG2Mode = MGCCode_B.DFIG2Mode;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.ICEStatus =
    MGCCode_U.InICEn.ICEStatus;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.BatStatus =
    MGCCode_U.InBatn.BatStatus;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.PVStatus = MGCCode_U.InPVn.PVStatus;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.DFIG1Status =
    MGCCode_U.InDFIG1n.DFIG1Status;
  MGCCode_B.BusConversion_InsertedFor_Mic_l.DFIG2Status =
    MGCCode_U.InDFIG2n.DFIG2Status;

  /* Sum: '<S7>/Sum' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0'
   *  Constant: '<S7>/Constant1'
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   */
  rtb_LineP_d = (((MGCCode_U.InICEn.ICESPout + MGCCode_U.InBatn.BatSPout) +
                  MGCCode_U.InPVn.PVSPout) + MGCCode_U.InDFIG1n.DFIG1SPout) -
    MGCCode_P.Base.LoadP;

  /* Sum: '<S7>/Sum1' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0'
   *  Constant: '<S7>/Constant'
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   */
  rtb_LineQ_b = (((MGCCode_U.InICEn.ICESQout + MGCCode_U.InBatn.BatSQout) +
                  MGCCode_U.InPVn.PVSQout) + MGCCode_U.InDFIG1n.DFIG1SPout) -
    MGCCode_P.Base.LoadQ;

  /* BusCreator: '<S1>/BusConversion_InsertedFor_MicrogridModelManager_at_inport_1' incorporates:
   *  Inport: '<Root>/InSystemRootn'
   */
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.LinePref =
    MGCCode_U.InSystemRootn.LinePref;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineP = rtb_LineP_d;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.Fref =
    MGCCode_U.InSystemRootn.Freqref;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.Fmeas =
    MGCCode_U.InSystemRootn.Fmeas;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineQref =
    MGCCode_U.InSystemRootn.LineQref;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.LineQ = rtb_LineQ_b;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.Vref = MGCCode_U.InSystemRootn.Vref;
  MGCCode_B.BusConversion_InsertedFor_Mi_l1.Vmeas =
    MGCCode_U.InSystemRootn.Vmeas;

  /* Switch: '<S11>/Switch15' incorporates:
   *  Constant: '<S11>/Constant15'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_U.InICEn.ICEStatus) {
    rtb_Cp_0 = MGCCode_U.InICEn.ICESPout;
  } else {
    rtb_Cp_0 = 0.0F;
  }

  /* End of Switch: '<S11>/Switch15' */

  /* Switch: '<S11>/Switch14' incorporates:
   *  Constant: '<S11>/Constant14'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_U.InBatn.BatStatus) {
    rtb_Sum_l_0 = MGCCode_U.InBatn.BatSPout;
  } else {
    rtb_Sum_l_0 = 0.0F;
  }

  /* End of Switch: '<S11>/Switch14' */

  /* Switch: '<S11>/Switch13' incorporates:
   *  Constant: '<S11>/Constant13'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_U.InPVn.PVStatus) {
    u = MGCCode_U.InPVn.PVSPout;
  } else {
    u = 0.0F;
  }

  /* End of Switch: '<S11>/Switch13' */

  /* Switch: '<S11>/Switch12' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0'
   *  Constant: '<S11>/Constant12'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_U.InDFIG1n.DFIG1Status) {
    rtb_Sum_ky_0 = MGCCode_U.InDFIG1n.DFIG1SPout;
  } else {
    rtb_Sum_ky_0 = 0.0F;
  }

  /* End of Switch: '<S11>/Switch12' */

  /* Sum: '<S11>/Sum' */
  rtb_Sum_l = (((rtb_Cp_0 + rtb_Sum_l_0) + u) + rtb_Sum_ky_0) + 0.0F;

  /* Product: '<S25>/Product' incorporates:
   *  Constant: '<S25>/Constant1'
   *  Constant: '<S25>/Constant9'
   */
  rtb_Product_l = MGCCode_P.Base.Bat * MGCCode_P.Base.BatPmax;

  /* Product: '<S62>/Product' incorporates:
   *  Constant: '<S62>/Constant1'
   *  Constant: '<S62>/Constant9'
   */
  rtb_Product = MGCCode_P.Base.ICE * MGCCode_P.Base.ICEPmax;

  /* DiscreteIntegrator: '<S88>/Discrete-Time Integrator2' */
  rtb_DiscreteTimeIntegrator2 = MGCCode_DWork.DiscreteTimeIntegrator2_DSTATE;

  /* Sum: '<S89>/Sum' incorporates:
   *  Gain: '<S89>/GainPole'
   *  Gain: '<S89>/GainZero'
   *  UnitDelay: '<S89>/Delay Input'
   *  UnitDelay: '<S89>/Delay Output'
   */
  rtb_PoleYk1UkZeroUk1 = (rtb_DiscreteTimeIntegrator2 - 0.75F *
    MGCCode_DWork.DelayInput_DSTATE) + 0.75F * MGCCode_DWork.DelayOutput_DSTATE;

  /* Saturate: '<S39>/DFIGR2POmegaSaturation' */
  if (rtb_PoleYk1UkZeroUk1 >= 1.3F) {
    rtb_Sum5 = 1.3F;
  } else if (rtb_PoleYk1UkZeroUk1 <= 0.51F) {
    rtb_Sum5 = 0.51F;
  } else {
    rtb_Sum5 = rtb_PoleYk1UkZeroUk1;
  }

  /* End of Saturate: '<S39>/DFIGR2POmegaSaturation' */

  /* Lookup_n-D: '<S39>/Omega2P Lookup Table' */
  rtb_Add4 = look1_iflf_binlxpw(rtb_Sum5, MGCCode_ConstP.pooled10,
    MGCCode_ConstP.pooled9, 77U);

  /* Sum: '<S42>/Add3' incorporates:
   *  UnitDelay: '<S42>/Unit Delay'
   */
  rtb_Add4 += MGCCode_DWork.UnitDelay_DSTATE;

  /* Sum: '<S39>/Sum6' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Sum_ky = rtb_Sum5 - MGCCode_U.InDFIG1n.DFIG1Threshold;

  /* Relay: '<S39>/DFIGR2PRelay' */
  if (rtb_Sum_ky >= 0.0F) {
    MGCCode_DWork.DFIGR2PRelay_Mode = TRUE;
  } else {
    if (rtb_Sum_ky <= -0.05F) {
      MGCCode_DWork.DFIGR2PRelay_Mode = FALSE;
    }
  }

  if (MGCCode_DWork.DFIGR2PRelay_Mode) {
    rtb_DFIGR2PRelay = 1.0F;
  } else {
    rtb_DFIGR2PRelay = 0.0F;
  }

  /* End of Relay: '<S39>/DFIGR2PRelay' */

  /* Saturate: '<S39>/DFIGR2PPoutSaturation' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_U.InDFIG1n.DFIG1SPout >= 0.0F) {
    rtb_Cp_0 = MGCCode_U.InDFIG1n.DFIG1SPout;
  } else {
    rtb_Cp_0 = 0.0F;
  }

  /* End of Saturate: '<S39>/DFIGR2PPoutSaturation' */

  /* Lookup_n-D: '<S39>/P2Omega Lookup Table1' */
  rtb_Sum_ky = look1_iflf_binlxpw(rtb_Cp_0, MGCCode_ConstP.pooled9,
    MGCCode_ConstP.pooled10, 77U);

  /* Saturate: '<S39>/DFIGR2POmegaSaturation1' */
  if (rtb_Sum_ky >= 1.3F) {
    rtb_Sum_ky = 1.3F;
  } else {
    if (rtb_Sum_ky <= 0.51F) {
      rtb_Sum_ky = 0.51F;
    }
  }

  /* Sum: '<S39>/Sum5' incorporates:
   *  Saturate: '<S39>/DFIGR2POmegaSaturation1'
   */
  rtb_Sum5 -= rtb_Sum_ky;

  /* Sum: '<S43>/Sum' incorporates:
   *  DiscreteIntegrator: '<S43>/Integrator'
   */
  rtb_Sum_ky = rtb_Sum5 + MGCCode_DWork.Integrator_DSTATE;

  /* Saturate: '<S43>/Saturation' */
  if (rtb_Sum_ky >= 1.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum_ky <= 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum_ky;
  }

  /* Sum: '<S42>/Add1' incorporates:
   *  Saturate: '<S43>/Saturation'
   *  UnitDelay: '<S42>/Unit Delay1'
   */
  rtb_Add2 = rtb_Sum_ky_0 + MGCCode_DWork.UnitDelay1_DSTATE;

  /* Switch: '<S42>/Switch1' */
  if (rtb_DFIGR2PRelay >= 0.5F) {
    rtb_Switch1 = rtb_Add4;
  } else {
    rtb_Switch1 = rtb_Add2;
  }

  /* End of Switch: '<S42>/Switch1' */

  /* Gain: '<S4>/Gain' */
  rtb_Gain_eq = MGCCode_P.Base.DFIG1 * rtb_Switch1;

  /* Product: '<S74>/Product' incorporates:
   *  Constant: '<S74>/Constant5'
   *  Constant: '<S74>/Constant9'
   */
  rtb_PVSPcmd = MGCCode_P.Base.PV * MGCCode_P.Base.PVPmax;

  /* Switch: '<S11>/Switch11' incorporates:
   *  Constant: '<S11>/Constant11'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_U.InBatn.BatStatus) {
    rtb_Cp_0 = rtb_Product_l;
  } else {
    rtb_Cp_0 = 0.1F;
  }

  /* End of Switch: '<S11>/Switch11' */

  /* Switch: '<S11>/Switch10' incorporates:
   *  Constant: '<S11>/Constant10'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_U.InICEn.ICEStatus) {
    rtb_Sum_l_0 = rtb_Product;
  } else {
    rtb_Sum_l_0 = 0.1F;
  }

  /* End of Switch: '<S11>/Switch10' */

  /* Switch: '<S11>/Switch9' incorporates:
   *  Constant: '<S11>/Constant9'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_U.InDFIG1n.DFIG1Status) {
    u = rtb_Gain_eq;
  } else {
    u = 0.1F;
  }

  /* End of Switch: '<S11>/Switch9' */

  /* Switch: '<S11>/Switch8' incorporates:
   *  Constant: '<S11>/Constant8'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_U.InPVn.PVStatus) {
    rtb_Sum_ky_0 = rtb_PVSPcmd;
  } else {
    rtb_Sum_ky_0 = 0.1F;
  }

  /* End of Switch: '<S11>/Switch8' */

  /* Sum: '<S11>/Sum1' */
  rtb_Pmax = (((rtb_Cp_0 + rtb_Sum_l_0) + u) + rtb_Sum_ky_0) + 0.0F;

  /* Product: '<S11>/Divide' */
  rtb_Integrator_c = rtb_Sum_l / rtb_Pmax;

  /* Switch: '<S11>/Switch4' incorporates:
   *  Constant: '<S11>/Constant4'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_U.InDFIG1n.DFIG1Status) {
    rtb_DeadZone = MGCCode_U.InDFIG1n.DFIG1SQout;
  } else {
    rtb_DeadZone = 0.0F;
  }

  /* End of Switch: '<S11>/Switch4' */

  /* Switch: '<S11>/Switch7' incorporates:
   *  Constant: '<S11>/Constant7'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_U.InICEn.ICEStatus) {
    rtb_Cp_0 = MGCCode_U.InICEn.ICESQout;
  } else {
    rtb_Cp_0 = 0.0F;
  }

  /* End of Switch: '<S11>/Switch7' */

  /* Switch: '<S11>/Switch6' incorporates:
   *  Constant: '<S11>/Constant6'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_U.InBatn.BatStatus) {
    rtb_Sum_l_0 = MGCCode_U.InBatn.BatSQout;
  } else {
    rtb_Sum_l_0 = 0.0F;
  }

  /* End of Switch: '<S11>/Switch6' */

  /* Switch: '<S11>/Switch5' incorporates:
   *  Constant: '<S11>/Constant5'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_U.InPVn.PVStatus) {
    u = MGCCode_U.InPVn.PVSQout;
  } else {
    u = 0.0F;
  }

  /* End of Switch: '<S11>/Switch5' */

  /* Sum: '<S11>/Sum2' */
  rtb_Sum2 = (((rtb_Cp_0 + rtb_Sum_l_0) + u) + rtb_DeadZone) + 0.0F;

  /* Sum: '<S74>/Subtract' incorporates:
   *  Constant: '<S74>/Constant6'
   *  Inport: '<Root>/InPVn'
   *  Math: '<S74>/Math Function'
   *  Math: '<S74>/Math Function1'
   */
  rtb_DeadZone = MGCCode_P.Base.PV * MGCCode_P.Base.PV - MGCCode_U.InPVn.PVSPout
    * MGCCode_U.InPVn.PVSPout;

  /* MinMax: '<S74>/MinMax' */
  if (!(rtb_DeadZone >= 0.1F)) {
    rtb_DeadZone = 0.1F;
  }

  /* End of MinMax: '<S74>/MinMax' */

  /* Sqrt: '<S74>/Sqrt' */
  rtb_DeadZone = (real32_T)sqrt(rtb_DeadZone);

  /* Sum: '<S38>/Subtract' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0'
   *  Constant: '<S38>/Constant6'
   *  Inport: '<Root>/InDFIG1n'
   *  Math: '<S38>/Math Function'
   *  Math: '<S38>/Math Function1'
   */
  u = MGCCode_P.Base.DFIG1 * MGCCode_P.Base.DFIG1 -
    MGCCode_U.InDFIG1n.DFIG1SPout * MGCCode_U.InDFIG1n.DFIG1SPout;

  /* MinMax: '<S38>/MinMax' */
  if (!(u >= 0.1F)) {
    u = 0.1F;
  }

  /* Sqrt: '<S38>/Sqrt' incorporates:
   *  MinMax: '<S38>/MinMax'
   */
  rtb_Sqrt = (real32_T)sqrt(u);

  /* Sum: '<S25>/Subtract' incorporates:
   *  Constant: '<S25>/Constant6'
   *  Inport: '<Root>/InBatn'
   *  Math: '<S25>/Math Function'
   *  Math: '<S25>/Math Function1'
   */
  u = MGCCode_P.Base.Bat * MGCCode_P.Base.Bat - MGCCode_U.InBatn.BatSPout *
    MGCCode_U.InBatn.BatSPout;

  /* MinMax: '<S25>/MinMax' */
  if (!(u >= 0.1F)) {
    u = 0.1F;
  }

  /* Sqrt: '<S25>/Sqrt' incorporates:
   *  MinMax: '<S25>/MinMax'
   */
  rtb_DeadZone_d = (real32_T)sqrt(u);

  /* Sum: '<S62>/Subtract' incorporates:
   *  Constant: '<S62>/Constant6'
   *  Inport: '<Root>/InICEn'
   *  Math: '<S62>/Math Function'
   *  Math: '<S62>/Math Function1'
   */
  u = MGCCode_P.Base.ICE * MGCCode_P.Base.ICE - MGCCode_U.InICEn.ICESPout *
    MGCCode_U.InICEn.ICESPout;

  /* MinMax: '<S62>/MinMax' */
  if (!(u >= 0.1F)) {
    u = 0.1F;
  }

  /* Sqrt: '<S62>/Sqrt' incorporates:
   *  MinMax: '<S62>/MinMax'
   */
  rtb_Product2 = (real32_T)sqrt(u);

  /* Switch: '<S11>/Switch' incorporates:
   *  Constant: '<S11>/Constant'
   *  Inport: '<Root>/InICEn'
   */
  if (MGCCode_U.InICEn.ICEStatus) {
    rtb_Sum1 = rtb_Product2;
  } else {
    rtb_Sum1 = 0.1F;
  }

  /* End of Switch: '<S11>/Switch' */

  /* Switch: '<S11>/Switch3' incorporates:
   *  Constant: '<S11>/Constant3'
   *  Inport: '<Root>/InPVn'
   */
  if (MGCCode_U.InPVn.PVStatus) {
    rtb_Cp_0 = rtb_DeadZone;
  } else {
    rtb_Cp_0 = 0.1F;
  }

  /* End of Switch: '<S11>/Switch3' */

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Inport: '<Root>/InDFIG1n'
   */
  if (MGCCode_U.InDFIG1n.DFIG1Status) {
    rtb_Sum_l_0 = rtb_Sqrt;
  } else {
    rtb_Sum_l_0 = 0.1F;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Switch: '<S11>/Switch1' incorporates:
   *  Constant: '<S11>/Constant1'
   *  Inport: '<Root>/InBatn'
   */
  if (MGCCode_U.InBatn.BatStatus) {
    u = rtb_DeadZone_d;
  } else {
    u = 0.1F;
  }

  /* End of Switch: '<S11>/Switch1' */

  /* Product: '<S11>/Divide1' incorporates:
   *  Sum: '<S11>/Sum3'
   */
  rtb_Sum1 = rtb_Sum2 / ((((rtb_Cp_0 + rtb_Sum_l_0) + u) + rtb_Sum1) + 0.0F);

  /* BusCreator: '<S1>/BusConversion_InsertedFor_MicrogridModelManager_at_inport_2' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_InDFIG1n_at_outport_0'
   *  Inport: '<Root>/InBatn'
   *  Inport: '<Root>/InDFIG1n'
   *  Inport: '<Root>/InICEn'
   *  Inport: '<Root>/InPVn'
   *  Product: '<S11>/Divide10'
   *  Product: '<S11>/Divide11'
   *  Product: '<S11>/Divide2'
   *  Product: '<S11>/Divide3'
   *  Product: '<S11>/Divide4'
   *  Product: '<S11>/Divide5'
   *  Product: '<S11>/Divide6'
   *  Product: '<S11>/Divide7'
   *  Product: '<S11>/Divide8'
   *  Product: '<S11>/Divide9'
   */
  MGCCode_B.BusConversion_InsertedFor_Micro.Pout = rtb_Sum_l;
  MGCCode_B.BusConversion_InsertedFor_Micro.Pmax = rtb_Pmax;
  MGCCode_B.BusConversion_InsertedFor_Micro.AGCRatio = rtb_Integrator_c;
  MGCCode_B.BusConversion_InsertedFor_Micro.AVCRatio = rtb_Sum1;
  MGCCode_B.BusConversion_InsertedFor_Micro.PVAGCRatio = MGCCode_U.InPVn.PVSPout
    / rtb_PVSPcmd;
  MGCCode_B.BusConversion_InsertedFor_Micro.PVAVCRatio = MGCCode_U.InPVn.PVSQout
    / rtb_DeadZone;
  MGCCode_B.BusConversion_InsertedFor_Micro.DFIG1AGCRatio =
    MGCCode_U.InDFIG1n.DFIG1SPout / rtb_Gain_eq;
  MGCCode_B.BusConversion_InsertedFor_Micro.DFIG1AVCRatio =
    MGCCode_U.InDFIG1n.DFIG1SQout / rtb_Sqrt;
  MGCCode_B.BusConversion_InsertedFor_Micro.DFIG3AGCRatio =
    MGCCode_U.InDFIG1n.DFIG1SPout / rtb_Gain_eq;
  MGCCode_B.BusConversion_InsertedFor_Micro.DFIG3AVCRatio =
    MGCCode_U.InDFIG1n.DFIG1SQout / rtb_Sqrt;
  MGCCode_B.BusConversion_InsertedFor_Micro.BatAGCRatio =
    MGCCode_U.InBatn.BatSPout / rtb_Product_l;
  MGCCode_B.BusConversion_InsertedFor_Micro.BatAVCRatio =
    MGCCode_U.InBatn.BatSQout / rtb_DeadZone_d;
  MGCCode_B.BusConversion_InsertedFor_Micro.ICEAGCRatio =
    MGCCode_U.InICEn.ICESPout / rtb_Product;
  MGCCode_B.BusConversion_InsertedFor_Micro.ICEAVCRatio =
    MGCCode_U.InICEn.ICESQout / rtb_Product2;

  /* Chart: '<S1>/MicrogridModelManager' */
  /* Gateway: MGCC2/MicrogridModelManager */
  if (MGCCode_DWork.temporalCounter_i1 < 60.0F) {
    MGCCode_DWork.temporalCounter_i1++;
  }

  if (MGCCode_DWork.temporalCounter_i2 < 3) {
    MGCCode_DWork.temporalCounter_i2++;
  }

  /* During: MGCC2/MicrogridModelManager */
  if (MGCCode_DWork.is_active_c7_MGCCode == 0U) {
    /* Entry: MGCC2/MicrogridModelManager */
    MGCCode_DWork.is_active_c7_MGCCode = 1U;

    /* Entry Internal: MGCC2/MicrogridModelManager */
    MGCCode_DWork.is_c7_MGCCode = MGCCode_IN_Logic;

    /* Entry 'Logic': '<S8>:1229' */
    MGCCode_DWork.count = 0.0F;
    MGCCode_B.OutSystem_e.Fref = MGCCode_B.BusConversion_InsertedFor_Mi_l1.Fref;
    MGCCode_B.OutSystem_e.Vref = MGCCode_B.BusConversion_InsertedFor_Mi_l1.Vref;

    /* Entry Internal 'Logic': '<S8>:1229' */
    /* Transition: '<S8>:72' */
    MGCCode_DWork.is_Logic = MGCCode_IN_Start;
    MGCCode_DWork.temporalCounter_i2 = 0U;

    /* Entry 'Start': '<S8>:2' */
    MGCCode_B.OutEMS_m.SystemModen = Start;
  } else {
    MGCCode_Logic();
  }

  if (MGCCode_DWork.temporalCounter_i1 == 60.0F) {
    MGCCode_DWork.temporalCounter_i1 = 0U;
  }

  /* End of Chart: '<S1>/MicrogridModelManager' */

  /* Sum: '<S2>/Sum2' incorporates:
   *  BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator8_at_inport_3'
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Product: '<S2>/Divide'
   *  Product: '<S2>/Divide1'
   */
  rtb_Cp = MGCCode_B.OutSystem_e.LinePref / MGCCode_P.Base.LineP - rtb_LineP_d /
    MGCCode_P.Base.LineP;

  /* MATLAB Function: '<S2>/ModeSelect1' incorporates:
   *  BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator8_at_inport_1'
   */
  /* MATLAB Function 'MGCC2/AGCandAVC/ModeSelect1': '<S18>:1' */
  if (MGCCode_B.OutEMS_m.SystemModen == ConstPConstQ) {
    /* '<S18>:1:3' */
    /* '<S18>:1:4' */
    rtb_AGC = 1;

    /* '<S18>:1:5' */
    rtb_AVC = 1;
  } else if (MGCCode_B.OutEMS_m.SystemModen == AGC) {
    /* '<S18>:1:6' */
    /* '<S18>:1:7' */
    rtb_AGC = 1;

    /* '<S18>:1:8' */
    rtb_AVC = 1;
  } else if (MGCCode_B.OutEMS_m.SystemModen == Independent) {
    /* '<S18>:1:9' */
    /* '<S18>:1:10' */
    rtb_AGC = 1;

    /* '<S18>:1:11' */
    rtb_AVC = 1;
  } else if (MGCCode_B.OutEMS_m.SystemModen == Island) {
    /* '<S18>:1:12' */
    /* '<S18>:1:13' */
    rtb_AGC = 0;

    /* '<S18>:1:14' */
    rtb_AVC = 0;
  } else {
    /* '<S18>:1:16' */
    rtb_AGC = 1;

    /* '<S18>:1:17' */
    rtb_AVC = 1;
  }

  /* End of MATLAB Function: '<S2>/ModeSelect1' */

  /* DiscreteIntegrator: '<S12>/Integrator' incorporates:
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING != 0) {
    MGCCode_DWork.Integrator_DSTATE_d = MGCCode_DWork.UnitDelay1_DSTATE_n;
  }

  if (((rtb_AGC > 0) && (MGCCode_DWork.Integrator_PrevResetState <= 0)) ||
      ((rtb_AGC <= 0) && (MGCCode_DWork.Integrator_PrevResetState == 1))) {
    MGCCode_DWork.Integrator_DSTATE_d = MGCCode_DWork.UnitDelay1_DSTATE_n;
  }

  /* Sum: '<S12>/Sum' incorporates:
   *  DiscreteIntegrator: '<S12>/Integrator'
   *  Gain: '<S12>/Proportional Gain'
   */
  rtb_Sum_l = StructPointer->CtrlParamAGC.LinePPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_d;

  /* Gain: '<S12>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamAGC.LinePPIIntegral * rtb_Cp;

  /* DeadZone: '<S19>/DeadZone' */
  if (rtb_Sum_l > StructPointer->CtrlParamAGC.LinePPIUpperSat) {
    rtb_Sum_l_0 = rtb_Sum_l - StructPointer->CtrlParamAGC.LinePPIUpperSat;
  } else if (rtb_Sum_l >= StructPointer->CtrlParamAGC.LinePPILowerSat) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum_l - StructPointer->CtrlParamAGC.LinePPILowerSat;
  }

  /* End of DeadZone: '<S19>/DeadZone' */

  /* Signum: '<S19>/SignPreSat' */
  if (rtb_Sum_l < 0.0F) {
    u = -1.0F;
  } else if (rtb_Sum_l > 0.0F) {
    u = 1.0F;
  } else if (rtb_Sum_l == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Sum_l;
  }

  /* Signum: '<S19>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S12>/Switch' incorporates:
   *  Constant: '<S12>/Constant'
   *  Gain: '<S19>/Gain'
   *  Logic: '<S19>/AND'
   *  RelationalOperator: '<S19>/Equal'
   *  RelationalOperator: '<S19>/NotEqual'
   *  Signum: '<S19>/SignPreIntegrator'
   *  Signum: '<S19>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_l != rtb_Sum_l_0) && (u == rtb_Cp_0)) {
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch = rtb_Cp;
  }

  /* End of Switch: '<S12>/Switch' */

  /* Sum: '<S2>/Sum3' incorporates:
   *  BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator8_at_inport_3'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  Inport: '<Root>/InSystemRootn'
   *  Product: '<S2>/Divide2'
   *  Product: '<S2>/Divide3'
   */
  rtb_Cp = MGCCode_B.OutSystem_e.Fref / MGCCode_P.Base.Freq -
    MGCCode_U.InSystemRootn.Fmeas / MGCCode_P.Base.Freq;

  /* DiscreteIntegrator: '<S13>/Integrator' incorporates:
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_l != 0) {
    MGCCode_DWork.Integrator_DSTATE_g = MGCCode_DWork.UnitDelay1_DSTATE_n;
  }

  if (((rtb_AGC > 0) && (MGCCode_DWork.Integrator_PrevResetState_p <= 0)) ||
      ((rtb_AGC <= 0) && (MGCCode_DWork.Integrator_PrevResetState_p == 1))) {
    MGCCode_DWork.Integrator_DSTATE_g = MGCCode_DWork.UnitDelay1_DSTATE_n;
  }

  /* Sum: '<S13>/Sum' incorporates:
   *  DiscreteIntegrator: '<S13>/Integrator'
   *  Gain: '<S13>/Proportional Gain'
   */
  rtb_Pmax = StructPointer->CtrlParamAGC.FreqPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_g;

  /* Gain: '<S13>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamAGC.FreqPIIntegral * rtb_Cp;

  /* DeadZone: '<S20>/DeadZone' */
  if (rtb_Pmax > StructPointer->CtrlParamAGC.FreqPIUpperSat) {
    rtb_Pmax_0 = rtb_Pmax - StructPointer->CtrlParamAGC.FreqPIUpperSat;
  } else if (rtb_Pmax >= StructPointer->CtrlParamAGC.FreqPILowerSat) {
    rtb_Pmax_0 = 0.0F;
  } else {
    rtb_Pmax_0 = rtb_Pmax - StructPointer->CtrlParamAGC.FreqPILowerSat;
  }

  /* End of DeadZone: '<S20>/DeadZone' */

  /* Signum: '<S20>/SignPreSat' */
  if (rtb_Pmax < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Pmax > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Pmax == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Pmax;
  }

  /* Signum: '<S20>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S13>/Switch' incorporates:
   *  Constant: '<S13>/Constant'
   *  Gain: '<S20>/Gain'
   *  Logic: '<S20>/AND'
   *  RelationalOperator: '<S20>/Equal'
   *  RelationalOperator: '<S20>/NotEqual'
   *  Signum: '<S20>/SignPreIntegrator'
   *  Signum: '<S20>/SignPreSat'
   */
  if ((0.0F * rtb_Pmax != rtb_Pmax_0) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_c = 0.0F;
  } else {
    rtb_Switch_c = rtb_Cp;
  }

  /* End of Switch: '<S13>/Switch' */

  /* Sum: '<S2>/Sum4' incorporates:
   *  Constant: '<S2>/Constant6'
   *  Constant: '<S2>/Constant7'
   *  Inport: '<Root>/InSystemRootn'
   *  Product: '<S2>/Divide6'
   *  Product: '<S2>/Divide7'
   */
  rtb_Cp = MGCCode_U.InSystemRootn.Vref / MGCCode_P.Base.Volt -
    MGCCode_U.InSystemRootn.Vmeas / MGCCode_P.Base.Volt;

  /* DiscreteIntegrator: '<S14>/Integrator' incorporates:
   *  UnitDelay: '<S2>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_i != 0) {
    MGCCode_DWork.Integrator_DSTATE_j = MGCCode_DWork.UnitDelay2_DSTATE;
  }

  if (((rtb_AVC > 0) && (MGCCode_DWork.Integrator_PrevResetState_i <= 0)) ||
      ((rtb_AVC <= 0) && (MGCCode_DWork.Integrator_PrevResetState_i == 1))) {
    MGCCode_DWork.Integrator_DSTATE_j = MGCCode_DWork.UnitDelay2_DSTATE;
  }

  /* Sum: '<S14>/Sum' incorporates:
   *  DiscreteIntegrator: '<S14>/Integrator'
   *  Gain: '<S14>/Proportional Gain'
   */
  rtb_Sum2 = StructPointer->CtrlParamAVC.VoltPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_j;

  /* Gain: '<S14>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamAVC.VoltPIIntegral * rtb_Cp;

  /* DeadZone: '<S21>/DeadZone' */
  if (rtb_Sum2 > StructPointer->CtrlParamAVC.VoltPIUpperSat) {
    rtb_Sum_l_0 = rtb_Sum2 - StructPointer->CtrlParamAVC.VoltPIUpperSat;
  } else if (rtb_Sum2 >= StructPointer->CtrlParamAVC.VoltPILowerSat) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum2 - StructPointer->CtrlParamAVC.VoltPILowerSat;
  }

  /* End of DeadZone: '<S21>/DeadZone' */

  /* Signum: '<S21>/SignPreSat' */
  if (rtb_Sum2 < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Sum2 > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum2 == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum2;
  }

  /* Signum: '<S21>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S14>/Switch' incorporates:
   *  Constant: '<S14>/Constant'
   *  Gain: '<S21>/Gain'
   *  Logic: '<S21>/AND'
   *  RelationalOperator: '<S21>/Equal'
   *  RelationalOperator: '<S21>/NotEqual'
   *  Signum: '<S21>/SignPreIntegrator'
   *  Signum: '<S21>/SignPreSat'
   */
  if ((0.0F * rtb_Sum2 != rtb_Sum_l_0) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_b = 0.0F;
  } else {
    rtb_Switch_b = rtb_Cp;
  }

  /* End of Switch: '<S14>/Switch' */

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S2>/Constant4'
   *  Constant: '<S2>/Constant5'
   *  Inport: '<Root>/InSystemRootn'
   *  Product: '<S2>/Divide4'
   *  Product: '<S2>/Divide5'
   */
  rtb_Cp = MGCCode_U.InSystemRootn.LineQref / MGCCode_P.Base.LineQ - rtb_LineQ_b
    / MGCCode_P.Base.LineQ;

  /* DiscreteIntegrator: '<S15>/Integrator' incorporates:
   *  UnitDelay: '<S2>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_b != 0) {
    MGCCode_DWork.Integrator_DSTATE_jw = MGCCode_DWork.UnitDelay2_DSTATE;
  }

  if (((rtb_AVC > 0) && (MGCCode_DWork.Integrator_PrevResetState_k <= 0)) ||
      ((rtb_AVC <= 0) && (MGCCode_DWork.Integrator_PrevResetState_k == 1))) {
    MGCCode_DWork.Integrator_DSTATE_jw = MGCCode_DWork.UnitDelay2_DSTATE;
  }

  /* Sum: '<S15>/Sum' incorporates:
   *  DiscreteIntegrator: '<S15>/Integrator'
   *  Gain: '<S15>/Proportional Gain'
   */
  rtb_Sum_e = StructPointer->CtrlParamAVC.LineQPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_jw;

  /* Gain: '<S15>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamAVC.LineQPIIntegral * rtb_Cp;

  /* DeadZone: '<S22>/DeadZone' */
  if (rtb_Sum_e > StructPointer->CtrlParamAVC.LineQPIUpperSat) {
    u = rtb_Sum_e - StructPointer->CtrlParamAVC.LineQPIUpperSat;
  } else if (rtb_Sum_e >= StructPointer->CtrlParamAVC.LineQPILowerSat) {
    u = 0.0F;
  } else {
    u = rtb_Sum_e - StructPointer->CtrlParamAVC.LineQPILowerSat;
  }

  /* End of DeadZone: '<S22>/DeadZone' */

  /* Signum: '<S22>/SignPreSat' */
  if (rtb_Sum_e < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Sum_e > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum_e == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum_e;
  }

  /* Signum: '<S22>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S15>/Switch' incorporates:
   *  Constant: '<S15>/Constant'
   *  Gain: '<S22>/Gain'
   *  Logic: '<S22>/AND'
   *  RelationalOperator: '<S22>/Equal'
   *  RelationalOperator: '<S22>/NotEqual'
   *  Signum: '<S22>/SignPreIntegrator'
   *  Signum: '<S22>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_e != u) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_j = 0.0F;
  } else {
    rtb_Switch_j = rtb_Cp;
  }

  /* End of Switch: '<S15>/Switch' */

  /* Switch: '<S2>/Switch1' incorporates:
   *  Saturate: '<S13>/Saturation'
   */
  if (rtb_AGC != 0) {
    /* Saturate: '<S12>/Saturation' */
    if (rtb_Sum_l >= StructPointer->CtrlParamAGC.LinePPIUpperSat) {
      rtb_Cp = StructPointer->CtrlParamAGC.LinePPIUpperSat;
    } else if (rtb_Sum_l <= StructPointer->CtrlParamAGC.LinePPILowerSat) {
      rtb_Cp = StructPointer->CtrlParamAGC.LinePPILowerSat;
    } else {
      rtb_Cp = rtb_Sum_l;
    }

    /* End of Saturate: '<S12>/Saturation' */
  } else if (rtb_Pmax >= StructPointer->CtrlParamAGC.FreqPIUpperSat) {
    /* Saturate: '<S13>/Saturation' */
    rtb_Cp = StructPointer->CtrlParamAGC.FreqPIUpperSat;
  } else if (rtb_Pmax <= StructPointer->CtrlParamAGC.FreqPILowerSat) {
    /* Saturate: '<S13>/Saturation' */
    rtb_Cp = StructPointer->CtrlParamAGC.FreqPILowerSat;
  } else {
    /* Saturate: '<S13>/Saturation' */
    rtb_Cp = rtb_Pmax;
  }

  /* End of Switch: '<S2>/Switch1' */

  /* Sum: '<S2>/Sum5' incorporates:
   *  Constant: '<S2>/Constant8'
   */
  MGCCode_B.Sum5 = rtb_Cp - MGCCode_P.Base.AGCRatio;
  if (MGCCode_M->Timing.TaskCounters.TID[2] == 0) {
    /* DiscreteIntegrator: '<S16>/Integrator' */
    if (MGCCode_DWork.Integrator_IC_LOADING_p != 0) {
      MGCCode_DWork.Integrator_DSTATE_l = 0.0F;
    }

    if (((0.0F > 0.0F) && (MGCCode_DWork.Integrator_PrevResetState_b <= 0)) ||
        ((0.0F <= 0.0F) && (MGCCode_DWork.Integrator_PrevResetState_b == 1))) {
      MGCCode_DWork.Integrator_DSTATE_l = 0.0F;
    }

    /* Sum: '<S16>/Sum' incorporates:
     *  DiscreteIntegrator: '<S16>/Integrator'
     *  Gain: '<S16>/Proportional Gain'
     */
    rtb_Sum_l = 0.0F * MGCCode_B.Sum5 + MGCCode_DWork.Integrator_DSTATE_l;

    /* Gain: '<S16>/Integral Gain' */
    rtb_Pmax = 0.0F * MGCCode_B.Sum5;

    /* Saturate: '<S16>/Saturation' */
    if (rtb_Sum_l >= 1.0F) {
      MGCCode_B.Saturation = 1.0F;
    } else if (rtb_Sum_l <= -1.0F) {
      MGCCode_B.Saturation = -1.0F;
    } else {
      MGCCode_B.Saturation = rtb_Sum_l;
    }

    /* End of Saturate: '<S16>/Saturation' */

    /* DeadZone: '<S23>/DeadZone' */
    if (rtb_Sum_l > 1.0F) {
      rtb_Sum_l_0 = rtb_Sum_l - 1.0F;
    } else if (rtb_Sum_l >= -1.0F) {
      rtb_Sum_l_0 = 0.0F;
    } else {
      rtb_Sum_l_0 = rtb_Sum_l - -1.0F;
    }

    /* End of DeadZone: '<S23>/DeadZone' */

    /* Signum: '<S23>/SignPreSat' */
    if (rtb_Sum_l < 0.0F) {
      u = -1.0F;
    } else if (rtb_Sum_l > 0.0F) {
      u = 1.0F;
    } else if (rtb_Sum_l == 0.0F) {
      u = 0.0F;
    } else {
      u = rtb_Sum_l;
    }

    /* Signum: '<S23>/SignPreIntegrator' */
    if (rtb_Pmax == 0.0F) {
      rtb_Pmax_0 = 0.0F;
    } else {
      rtb_Pmax_0 = rtb_Pmax;
    }

    /* Switch: '<S16>/Switch' incorporates:
     *  Constant: '<S16>/Constant'
     *  Gain: '<S23>/Gain'
     *  Logic: '<S23>/AND'
     *  RelationalOperator: '<S23>/Equal'
     *  RelationalOperator: '<S23>/NotEqual'
     *  Signum: '<S23>/SignPreIntegrator'
     *  Signum: '<S23>/SignPreSat'
     */
    if ((0.0F * rtb_Sum_l != rtb_Sum_l_0) && (u == rtb_Pmax_0)) {
      rtb_Switch_g = 0.0F;
    } else {
      rtb_Switch_g = rtb_Pmax;
    }

    /* End of Switch: '<S16>/Switch' */
  }

  /* Switch: '<S2>/Switch2' incorporates:
   *  Saturate: '<S14>/Saturation'
   */
  if (rtb_AVC != 0) {
    /* Saturate: '<S15>/Saturation' */
    if (rtb_Sum_e >= StructPointer->CtrlParamAVC.LineQPIUpperSat) {
      rtb_Integrator_a = StructPointer->CtrlParamAVC.LineQPIUpperSat;
    } else if (rtb_Sum_e <= StructPointer->CtrlParamAVC.LineQPILowerSat) {
      rtb_Integrator_a = StructPointer->CtrlParamAVC.LineQPILowerSat;
    } else {
      rtb_Integrator_a = rtb_Sum_e;
    }

    /* End of Saturate: '<S15>/Saturation' */
  } else if (rtb_Sum2 >= StructPointer->CtrlParamAVC.VoltPIUpperSat) {
    /* Saturate: '<S14>/Saturation' */
    rtb_Integrator_a = StructPointer->CtrlParamAVC.VoltPIUpperSat;
  } else if (rtb_Sum2 <= StructPointer->CtrlParamAVC.VoltPILowerSat) {
    /* Saturate: '<S14>/Saturation' */
    rtb_Integrator_a = StructPointer->CtrlParamAVC.VoltPILowerSat;
  } else {
    /* Saturate: '<S14>/Saturation' */
    rtb_Integrator_a = rtb_Sum2;
  }

  /* End of Switch: '<S2>/Switch2' */

  /* Sum: '<S2>/Sum6' incorporates:
   *  Constant: '<S2>/Constant9'
   */
  MGCCode_B.Sum6 = rtb_Integrator_a - MGCCode_P.Base.AVCRatio;
  if (MGCCode_M->Timing.TaskCounters.TID[2] == 0) {
    /* DiscreteIntegrator: '<S17>/Integrator' */
    if (MGCCode_DWork.Integrator_IC_LOADING_m != 0) {
      MGCCode_DWork.Integrator_DSTATE_g5 = 0.0F;
    }

    if (((0.0F > 0.0F) && (MGCCode_DWork.Integrator_PrevResetState_c <= 0)) ||
        ((0.0F <= 0.0F) && (MGCCode_DWork.Integrator_PrevResetState_c == 1))) {
      MGCCode_DWork.Integrator_DSTATE_g5 = 0.0F;
    }

    /* Sum: '<S17>/Sum' incorporates:
     *  DiscreteIntegrator: '<S17>/Integrator'
     *  Gain: '<S17>/Proportional Gain'
     */
    rtb_Pmax = 0.0F * MGCCode_B.Sum6 + MGCCode_DWork.Integrator_DSTATE_g5;

    /* Gain: '<S17>/Integral Gain' */
    rtb_Sum_l = 0.0F * MGCCode_B.Sum6;

    /* Saturate: '<S17>/Saturation' */
    if (rtb_Pmax >= 1.0F) {
      MGCCode_B.Saturation_j = 1.0F;
    } else if (rtb_Pmax <= -1.0F) {
      MGCCode_B.Saturation_j = -1.0F;
    } else {
      MGCCode_B.Saturation_j = rtb_Pmax;
    }

    /* End of Saturate: '<S17>/Saturation' */

    /* DeadZone: '<S24>/DeadZone' */
    if (rtb_Pmax > 1.0F) {
      rtb_Pmax_0 = rtb_Pmax - 1.0F;
    } else if (rtb_Pmax >= -1.0F) {
      rtb_Pmax_0 = 0.0F;
    } else {
      rtb_Pmax_0 = rtb_Pmax - -1.0F;
    }

    /* End of DeadZone: '<S24>/DeadZone' */

    /* Signum: '<S24>/SignPreSat' */
    if (rtb_Pmax < 0.0F) {
      rtb_Sum_ky_0 = -1.0F;
    } else if (rtb_Pmax > 0.0F) {
      rtb_Sum_ky_0 = 1.0F;
    } else if (rtb_Pmax == 0.0F) {
      rtb_Sum_ky_0 = 0.0F;
    } else {
      rtb_Sum_ky_0 = rtb_Pmax;
    }

    /* Signum: '<S24>/SignPreIntegrator' */
    if (rtb_Sum_l == 0.0F) {
      rtb_Sum_l_0 = 0.0F;
    } else {
      rtb_Sum_l_0 = rtb_Sum_l;
    }

    /* Switch: '<S17>/Switch' incorporates:
     *  Constant: '<S17>/Constant'
     *  Gain: '<S24>/Gain'
     *  Logic: '<S24>/AND'
     *  RelationalOperator: '<S24>/Equal'
     *  RelationalOperator: '<S24>/NotEqual'
     *  Signum: '<S24>/SignPreIntegrator'
     *  Signum: '<S24>/SignPreSat'
     */
    if ((0.0F * rtb_Pmax != rtb_Pmax_0) && (rtb_Sum_ky_0 == rtb_Sum_l_0)) {
      rtb_Switch_p = 0.0F;
    } else {
      rtb_Switch_p = rtb_Sum_l;
    }

    /* End of Switch: '<S17>/Switch' */
  }

  /* Sum: '<S2>/Sum7' */
  rtb_Integrator_c += rtb_Cp;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_Integrator_c >= 1.0F) {
    rtb_AGCref = 1.0F;
  } else if (rtb_Integrator_c <= 0.0F) {
    rtb_AGCref = 0.0F;
  } else {
    rtb_AGCref = rtb_Integrator_c;
  }

  /* End of Saturate: '<S2>/Saturation' */

  /* Sum: '<S2>/Sum8' */
  rtb_Sum1 += rtb_Integrator_a;

  /* Saturate: '<S2>/Saturation1' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_AVCref = 1.0F;
  } else if (rtb_Sum1 <= 0.0F) {
    rtb_AVCref = 0.0F;
  } else {
    rtb_AVCref = rtb_Sum1;
  }

  /* End of Saturate: '<S2>/Saturation1' */

  /* Saturate: '<S2>/Saturation2' */
  if (rtb_Cp >= 0.5F) {
    rtb_Saturation2 = 0.5F;
  } else if (rtb_Cp <= 0.0F) {
    rtb_Saturation2 = 0.0F;
  } else {
    rtb_Saturation2 = rtb_Cp;
  }

  /* End of Saturate: '<S2>/Saturation2' */

  /* Saturate: '<S2>/Saturation3' */
  if (rtb_Integrator_a >= 0.5F) {
    rtb_Saturation3 = 0.5F;
  } else if (rtb_Integrator_a <= 0.0F) {
    rtb_Saturation3 = 0.0F;
  } else {
    rtb_Saturation3 = rtb_Integrator_a;
  }

  /* End of Saturate: '<S2>/Saturation3' */

  /* Product: '<S25>/Divide1' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Sum1 = MGCCode_U.InBatn.BatSPref / rtb_Product_l;

  /* Product: '<S25>/Divide5' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Divide5_l = MGCCode_U.InBatn.BatSPout / rtb_Product_l;

  /* Product: '<S25>/Divide7' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  rtb_Divide7_l = MGCCode_U.InBatn.BatSQout / rtb_DeadZone_d;

  /* Saturate: '<S25>/Saturation1' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_Pmax = 1.0F;
  } else if (rtb_Sum1 <= -1.0F) {
    rtb_Pmax = -1.0F;
  } else {
    rtb_Pmax = rtb_Sum1;
  }

  /* End of Saturate: '<S25>/Saturation1' */

  /* Product: '<S25>/Divide2' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  u = MGCCode_U.InBatn.BatSQref / rtb_DeadZone_d;

  /* Sum: '<S27>/Sum2' */
  rtb_Sum_l = rtb_AGCref + MGCCode_B.Saturation;

  /* MATLAB Function: '<S27>/BatChargeControl' incorporates:
   *  Inport: '<Root>/InBatn'
   */
  /* MATLAB Function 'MGCC2/BatControl/PowerRegulator/BatChargeControl': '<S28>:1' */
  if (MGCCode_U.InBatn.BatChargeCmd) {
    /* '<S28>:1:6' */
    rtb_Sum_l = -(1.0F - rtb_Sum_l);
  } else {
    /* '<S28>:1:3' */
    /* '<S28>:1:4' */
  }

  /* End of MATLAB Function: '<S27>/BatChargeControl' */

  /* Sum: '<S27>/Sum' */
  rtb_Sum1 = rtb_Sum_l - rtb_Divide5_l;

  /* Gain: '<S29>/Proportional Gain' */
  rtb_Sum_l = StructPointer->CtrlParamBat.AGCInnerPIGain * rtb_Sum1;

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator3_at_inport_1' */
  rtb_BatMode_ly = MGCCode_B.OutEMS_m.BatMode;

  /* MATLAB Function: '<S27>/ModeSelect' */
  MGCCode_ModeSelect(rtb_BatMode_ly, &MGCCode_B.sf_ModeSelect);

  /* DiscreteIntegrator: '<S29>/Integrator' incorporates:
   *  UnitDelay: '<S27>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_a != 0) {
    MGCCode_DWork.Integrator_DSTATE_l5 = MGCCode_DWork.UnitDelay2_DSTATE_l;
  }

  if (((MGCCode_B.sf_ModeSelect.PCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_l <= 0)) ||
      ((MGCCode_B.sf_ModeSelect.PCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_l == 1))) {
    MGCCode_DWork.Integrator_DSTATE_l5 = MGCCode_DWork.UnitDelay2_DSTATE_l;
  }

  /* Sum: '<S29>/Sum' incorporates:
   *  DiscreteIntegrator: '<S29>/Integrator'
   */
  rtb_Sum_p = rtb_Sum_l + MGCCode_DWork.Integrator_DSTATE_l5;

  /* Sum: '<S27>/Sum1' */
  rtb_Cp = rtb_Pmax - rtb_Divide5_l;

  /* DiscreteIntegrator: '<S30>/Integrator' incorporates:
   *  UnitDelay: '<S27>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_d != 0) {
    MGCCode_DWork.Integrator_DSTATE_h = MGCCode_DWork.UnitDelay2_DSTATE_l;
  }

  if (((MGCCode_B.sf_ModeSelect.PCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_e <= 0)) ||
      ((MGCCode_B.sf_ModeSelect.PCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_e == 1))) {
    MGCCode_DWork.Integrator_DSTATE_h = MGCCode_DWork.UnitDelay2_DSTATE_l;
  }

  /* Sum: '<S30>/Sum' incorporates:
   *  DiscreteIntegrator: '<S30>/Integrator'
   *  Gain: '<S30>/Proportional Gain'
   */
  rtb_Sum_e = StructPointer->CtrlParamBat.ConstPPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_h;

  /* Switch: '<S27>/Switch' incorporates:
   *  Saturate: '<S30>/Saturation'
   */
  if (MGCCode_B.sf_ModeSelect.PCtrl != 0) {
    /* Saturate: '<S29>/Saturation' */
    if (rtb_Sum_p >= StructPointer->CtrlParamBat.AGCInnerPIUpperSat) {
      rtb_Switch_h = StructPointer->CtrlParamBat.AGCInnerPIUpperSat;
    } else if (rtb_Sum_p <= StructPointer->CtrlParamBat.AGCInnerPILowerSat) {
      rtb_Switch_h = StructPointer->CtrlParamBat.AGCInnerPILowerSat;
    } else {
      rtb_Switch_h = rtb_Sum_p;
    }

    /* End of Saturate: '<S29>/Saturation' */
  } else if (rtb_Sum_e >= StructPointer->CtrlParamBat.ConstPPIUpperSat) {
    /* Saturate: '<S30>/Saturation' */
    rtb_Switch_h = StructPointer->CtrlParamBat.ConstPPIUpperSat;
  } else if (rtb_Sum_e <= StructPointer->CtrlParamBat.ConstPPILowerSat) {
    /* Saturate: '<S30>/Saturation' */
    rtb_Switch_h = StructPointer->CtrlParamBat.ConstPPILowerSat;
  } else {
    /* Saturate: '<S30>/Saturation' */
    rtb_Switch_h = rtb_Sum_e;
  }

  /* End of Switch: '<S27>/Switch' */

  /* Saturate: '<S27>/Saturation' */
  if (rtb_Switch_h >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch_h <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch_h;
  }

  /* Product: '<S26>/Product' incorporates:
   *  Saturate: '<S27>/Saturation'
   */
  rtb_BatSPcmd = rtb_Cp_0 * rtb_Product_l;

  /* Sum: '<S27>/Sum5' incorporates:
   *  Sum: '<S27>/Sum3'
   */
  rtb_Integrator_a = (rtb_AVCref + MGCCode_B.Saturation_j) - rtb_Divide7_l;

  /* DiscreteIntegrator: '<S32>/Integrator' incorporates:
   *  UnitDelay: '<S27>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_e != 0) {
    MGCCode_DWork.Integrator_DSTATE_a = MGCCode_DWork.UnitDelay4_DSTATE;
  }

  if (((MGCCode_B.sf_ModeSelect.QCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_j <= 0)) ||
      ((MGCCode_B.sf_ModeSelect.QCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_j == 1))) {
    MGCCode_DWork.Integrator_DSTATE_a = MGCCode_DWork.UnitDelay4_DSTATE;
  }

  /* Sum: '<S32>/Sum' incorporates:
   *  DiscreteIntegrator: '<S32>/Integrator'
   *  Gain: '<S32>/Proportional Gain'
   */
  rtb_Pmax = StructPointer->CtrlParamBat.AVCInnerPIGain * rtb_Integrator_a +
    MGCCode_DWork.Integrator_DSTATE_a;

  /* Saturate: '<S25>/Saturation2' */
  if (u >= 1.0F) {
    u = 1.0F;
  } else {
    if (u <= -1.0F) {
      u = -1.0F;
    }
  }

  /* End of Saturate: '<S25>/Saturation2' */

  /* Sum: '<S27>/Sum6' */
  rtb_Integrator_c = u - rtb_Divide7_l;

  /* DiscreteIntegrator: '<S31>/Integrator' incorporates:
   *  UnitDelay: '<S27>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_mx != 0) {
    MGCCode_DWork.Integrator_DSTATE_p = MGCCode_DWork.UnitDelay4_DSTATE;
  }

  if (((MGCCode_B.sf_ModeSelect.QCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_jr <= 0)) ||
      ((MGCCode_B.sf_ModeSelect.QCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_jr == 1))) {
    MGCCode_DWork.Integrator_DSTATE_p = MGCCode_DWork.UnitDelay4_DSTATE;
  }

  /* Sum: '<S31>/Sum' incorporates:
   *  DiscreteIntegrator: '<S31>/Integrator'
   *  Gain: '<S31>/Proportional Gain'
   */
  rtb_Sum_l = StructPointer->CtrlParamBat.ConstQPIGain * rtb_Integrator_c +
    MGCCode_DWork.Integrator_DSTATE_p;

  /* Switch: '<S27>/Switch2' incorporates:
   *  Saturate: '<S31>/Saturation'
   */
  if (MGCCode_B.sf_ModeSelect.QCtrl != 0) {
    /* Saturate: '<S32>/Saturation' */
    if (rtb_Pmax >= StructPointer->CtrlParamBat.AVCInnerPIUpperSat) {
      rtb_Switch2 = StructPointer->CtrlParamBat.AVCInnerPIUpperSat;
    } else if (rtb_Pmax <= StructPointer->CtrlParamBat.AVCInnerPILowerSat) {
      rtb_Switch2 = StructPointer->CtrlParamBat.AVCInnerPILowerSat;
    } else {
      rtb_Switch2 = rtb_Pmax;
    }

    /* End of Saturate: '<S32>/Saturation' */
  } else if (rtb_Sum_l >= StructPointer->CtrlParamICE.ConstQPIUpperSat) {
    /* Saturate: '<S31>/Saturation' */
    rtb_Switch2 = StructPointer->CtrlParamICE.ConstQPIUpperSat;
  } else if (rtb_Sum_l <= StructPointer->CtrlParamICE.ConstQPILowerSat) {
    /* Saturate: '<S31>/Saturation' */
    rtb_Switch2 = StructPointer->CtrlParamICE.ConstQPILowerSat;
  } else {
    /* Saturate: '<S31>/Saturation' */
    rtb_Switch2 = rtb_Sum_l;
  }

  /* End of Switch: '<S27>/Switch2' */

  /* Saturate: '<S27>/Saturation2' */
  if (rtb_Switch2 >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch2 <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch2;
  }

  /* Product: '<S26>/Product1' incorporates:
   *  Saturate: '<S27>/Saturation2'
   */
  rtb_BatSQcmd = rtb_DeadZone_d * rtb_Cp_0;

  /* Gain: '<S29>/Integral Gain' */
  rtb_Sum1 = StructPointer->CtrlParamBat.AGCInnerPIIntegral * rtb_Sum1;

  /* DeadZone: '<S34>/DeadZone' */
  if (rtb_Sum_p > StructPointer->CtrlParamBat.AGCInnerPIUpperSat) {
    u = rtb_Sum_p - StructPointer->CtrlParamBat.AGCInnerPIUpperSat;
  } else if (rtb_Sum_p >= StructPointer->CtrlParamBat.AGCInnerPILowerSat) {
    u = 0.0F;
  } else {
    u = rtb_Sum_p - StructPointer->CtrlParamBat.AGCInnerPILowerSat;
  }

  /* End of DeadZone: '<S34>/DeadZone' */

  /* Signum: '<S34>/SignPreSat' */
  if (rtb_Sum_p < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Sum_p > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum_p == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum_p;
  }

  /* Signum: '<S34>/SignPreIntegrator' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant'
   *  Gain: '<S34>/Gain'
   *  Logic: '<S34>/AND'
   *  RelationalOperator: '<S34>/Equal'
   *  RelationalOperator: '<S34>/NotEqual'
   *  Signum: '<S34>/SignPreIntegrator'
   *  Signum: '<S34>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_p != u) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_ju = 0.0F;
  } else {
    rtb_Switch_ju = rtb_Sum1;
  }

  /* End of Switch: '<S29>/Switch' */

  /* DeadZone: '<S35>/DeadZone' */
  if (rtb_Sum_e > StructPointer->CtrlParamBat.ConstPPIUpperSat) {
    rtb_Sum1 = rtb_Sum_e - StructPointer->CtrlParamBat.ConstPPIUpperSat;
  } else if (rtb_Sum_e >= StructPointer->CtrlParamBat.ConstPPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_e - StructPointer->CtrlParamBat.ConstPPILowerSat;
  }

  /* End of DeadZone: '<S35>/DeadZone' */

  /* Gain: '<S30>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamBat.ConstPPIIntegral * rtb_Cp;

  /* Signum: '<S35>/SignPreSat' */
  if (rtb_Sum_e < 0.0F) {
    u = -1.0F;
  } else if (rtb_Sum_e > 0.0F) {
    u = 1.0F;
  } else if (rtb_Sum_e == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Sum_e;
  }

  /* Signum: '<S35>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S30>/Switch' incorporates:
   *  Constant: '<S30>/Constant'
   *  Gain: '<S35>/Gain'
   *  Logic: '<S35>/AND'
   *  RelationalOperator: '<S35>/Equal'
   *  RelationalOperator: '<S35>/NotEqual'
   *  Signum: '<S35>/SignPreIntegrator'
   *  Signum: '<S35>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_e != rtb_Sum1) && (u == rtb_Cp_0)) {
    rtb_Switch_bm = 0.0F;
  } else {
    rtb_Switch_bm = rtb_Cp;
  }

  /* End of Switch: '<S30>/Switch' */

  /* DeadZone: '<S36>/DeadZone' */
  if (rtb_Sum_l > StructPointer->CtrlParamICE.ConstQPIUpperSat) {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamICE.ConstQPIUpperSat;
  } else if (rtb_Sum_l >= StructPointer->CtrlParamICE.ConstQPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamICE.ConstQPILowerSat;
  }

  /* End of DeadZone: '<S36>/DeadZone' */

  /* Gain: '<S31>/Integral Gain' */
  rtb_Integrator_c = StructPointer->CtrlParamBat.ConstQPIIntegral *
    rtb_Integrator_c;

  /* Signum: '<S36>/SignPreSat' */
  if (rtb_Sum_l < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum_l > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum_l == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum_l;
  }

  /* Signum: '<S36>/SignPreIntegrator' */
  if (rtb_Integrator_c < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Integrator_c > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Integrator_c == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Integrator_c;
  }

  /* Switch: '<S31>/Switch' incorporates:
   *  Constant: '<S31>/Constant'
   *  Gain: '<S36>/Gain'
   *  Logic: '<S36>/AND'
   *  RelationalOperator: '<S36>/Equal'
   *  RelationalOperator: '<S36>/NotEqual'
   *  Signum: '<S36>/SignPreIntegrator'
   *  Signum: '<S36>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_l != rtb_Sum1) && (rtb_Sum_l_0 == rtb_Sum_ky_0)) {
    rtb_Switch_k = 0.0F;
  } else {
    rtb_Switch_k = rtb_Integrator_c;
  }

  /* End of Switch: '<S31>/Switch' */

  /* DeadZone: '<S37>/DeadZone' */
  if (rtb_Pmax > StructPointer->CtrlParamBat.AVCInnerPIUpperSat) {
    rtb_Sum1 = rtb_Pmax - StructPointer->CtrlParamBat.AVCInnerPIUpperSat;
  } else if (rtb_Pmax >= StructPointer->CtrlParamBat.AVCInnerPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Pmax - StructPointer->CtrlParamBat.AVCInnerPILowerSat;
  }

  /* End of DeadZone: '<S37>/DeadZone' */

  /* Gain: '<S32>/Integral Gain' */
  rtb_Integrator_a = StructPointer->CtrlParamBat.AVCInnerPIIntegral *
    rtb_Integrator_a;

  /* Signum: '<S37>/SignPreSat' */
  if (rtb_Pmax < 0.0F) {
    rtb_Pmax_0 = -1.0F;
  } else if (rtb_Pmax > 0.0F) {
    rtb_Pmax_0 = 1.0F;
  } else if (rtb_Pmax == 0.0F) {
    rtb_Pmax_0 = 0.0F;
  } else {
    rtb_Pmax_0 = rtb_Pmax;
  }

  /* Signum: '<S37>/SignPreIntegrator' */
  if (rtb_Integrator_a < 0.0F) {
    u = -1.0F;
  } else if (rtb_Integrator_a > 0.0F) {
    u = 1.0F;
  } else if (rtb_Integrator_a == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Integrator_a;
  }

  /* Switch: '<S32>/Switch' incorporates:
   *  Constant: '<S32>/Constant'
   *  Gain: '<S37>/Gain'
   *  Logic: '<S37>/AND'
   *  RelationalOperator: '<S37>/Equal'
   *  RelationalOperator: '<S37>/NotEqual'
   *  Signum: '<S37>/SignPreIntegrator'
   *  Signum: '<S37>/SignPreSat'
   */
  if ((0.0F * rtb_Pmax != rtb_Sum1) && (rtb_Pmax_0 == u)) {
    rtb_Switch_jt = 0.0F;
  } else {
    rtb_Switch_jt = rtb_Integrator_a;
  }

  /* End of Switch: '<S32>/Switch' */

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator2_at_inport_1' */
  rtb_ICEMode_lks = MGCCode_B.OutEMS_m.ICEMode;

  /* BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator4_at_inport_1' */
  rtb_PVMode_a115 = MGCCode_B.OutEMS_m.PVMode;

  /* Product: '<S38>/Divide5' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Sum1 = MGCCode_U.InDFIG1n.DFIG1SPref / rtb_Gain_eq;

  /* Saturate: '<S38>/Saturation1' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_Sum2 = 1.0F;
  } else if (rtb_Sum1 <= 0.0F) {
    rtb_Sum2 = 0.0F;
  } else {
    rtb_Sum2 = rtb_Sum1;
  }

  /* End of Saturate: '<S38>/Saturation1' */

  /* Product: '<S38>/Divide1' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Sum1 = MGCCode_U.InDFIG1n.DFIG1SQref / rtb_Sqrt;

  /* Product: '<S38>/Divide2' */
  rtb_Divide2_g = rtb_DFIG1SPout / rtb_Gain_eq;

  /* Product: '<S38>/Divide7' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   */
  rtb_Divide7_n = MGCCode_U.InDFIG1n.DFIG1SQout / rtb_Sqrt;

  /* Saturate: '<S38>/Saturation2' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_Sum_p = 1.0F;
  } else if (rtb_Sum1 <= 0.0F) {
    rtb_Sum_p = 0.0F;
  } else {
    rtb_Sum_p = rtb_Sum1;
  }

  /* End of Saturate: '<S38>/Saturation2' */

  /* Sum: '<S42>/Add2' */
  rtb_Add2 = rtb_Switch1 - rtb_Add2;

  /* Sum: '<S42>/Add4' */
  rtb_Add4 = rtb_Switch1 - rtb_Add4;

  /* DiscreteIntegrator: '<S45>/Integrator' */
  if ((rtb_DFIGR2PRelay > 0.0F) && (MGCCode_DWork.Integrator_PrevResetState_e3 <=
       0)) {
    MGCCode_DWork.Integrator_DSTATE_aa = 0.0F;
  }

  rtb_Sum1 = MGCCode_DWork.Integrator_DSTATE_aa;

  /* End of DiscreteIntegrator: '<S45>/Integrator' */

  /* Sum: '<S45>/Sum' */
  rtb_Sum1 += rtb_Add4;

  /* Saturate: '<S45>/Saturation' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* End of Saturate: '<S45>/Saturation' */

  /* DiscreteFilter: '<S42>/DFIGR2PSeamless1stOrder' */
  DFIGR2PSeamless1stOrder_tmp = rtb_Cp_0 - -0.9512F *
    MGCCode_DWork.DFIGR2PSeamless1stOrder_states;
  rtb_DFIGR2PSeamless1stOrder = 0.02459F * DFIGR2PSeamless1stOrder_tmp +
    0.02418F * MGCCode_DWork.DFIGR2PSeamless1stOrder_states;

  /* DiscreteIntegrator: '<S44>/Integrator' */
  if ((rtb_DFIGR2PRelay <= 0.0F) && (MGCCode_DWork.Integrator_PrevResetState_ix ==
       1)) {
    MGCCode_DWork.Integrator_DSTATE_k = 0.0F;
  }

  /* Sum: '<S44>/Sum' incorporates:
   *  DiscreteIntegrator: '<S44>/Integrator'
   */
  rtb_Cp = rtb_Add2 + MGCCode_DWork.Integrator_DSTATE_k;

  /* Saturate: '<S44>/Saturation' */
  if (rtb_Cp >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* End of Saturate: '<S44>/Saturation' */

  /* DiscreteFilter: '<S42>/DFIGR2PSeamless1stOrder1' */
  DFIGR2PSeamless1stOrder1_tmp = rtb_Cp_0 - -0.9512F *
    MGCCode_DWork.DFIGR2PSeamless1stOrder1_states;
  rtb_DFIGR2PSeamless1stOrder1 = 0.02459F * DFIGR2PSeamless1stOrder1_tmp +
    0.02418F * MGCCode_DWork.DFIGR2PSeamless1stOrder1_states;

  /* DeadZone: '<S46>/DeadZone' */
  if (rtb_Cp > 1.0F) {
    rtb_Cp_0 = rtb_Cp - 1.0F;
  } else if (rtb_Cp >= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* End of DeadZone: '<S46>/DeadZone' */

  /* Signum: '<S46>/SignPreSat' */
  if (rtb_Cp < 0.0F) {
    u = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    u = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Cp;
  }

  /* Signum: '<S46>/SignPreIntegrator' */
  if (rtb_Add2 < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Add2 > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Add2 == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Add2;
  }

  /* Switch: '<S44>/Switch' incorporates:
   *  Constant: '<S44>/Constant'
   *  Gain: '<S46>/Gain'
   *  Logic: '<S46>/AND'
   *  RelationalOperator: '<S46>/Equal'
   *  RelationalOperator: '<S46>/NotEqual'
   *  Signum: '<S46>/SignPreIntegrator'
   *  Signum: '<S46>/SignPreSat'
   */
  if ((0.0F * rtb_Cp != rtb_Cp_0) && (u == rtb_Sum_ky_0)) {
    rtb_Switch_e = 0.0F;
  } else {
    rtb_Switch_e = rtb_Add2;
  }

  /* End of Switch: '<S44>/Switch' */

  /* DeadZone: '<S47>/DeadZone' */
  if (rtb_Sum1 > 1.0F) {
    rtb_Cp_0 = rtb_Sum1 - 1.0F;
  } else if (rtb_Sum1 >= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* End of DeadZone: '<S47>/DeadZone' */

  /* Signum: '<S47>/SignPreSat' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum1;
  }

  /* Signum: '<S47>/SignPreIntegrator' */
  if (rtb_Add4 < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Add4 > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Add4 == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Add4;
  }

  /* Switch: '<S45>/Switch' incorporates:
   *  Constant: '<S45>/Constant'
   *  Gain: '<S47>/Gain'
   *  Logic: '<S47>/AND'
   *  RelationalOperator: '<S47>/Equal'
   *  RelationalOperator: '<S47>/NotEqual'
   *  Signum: '<S47>/SignPreIntegrator'
   *  Signum: '<S47>/SignPreSat'
   */
  if ((0.0F * rtb_Sum1 != rtb_Cp_0) && (rtb_Sum_l_0 == rtb_Sum_ky_0)) {
    rtb_Switch_hg = 0.0F;
  } else {
    rtb_Switch_hg = rtb_Add4;
  }

  /* End of Switch: '<S45>/Switch' */

  /* DeadZone: '<S48>/DeadZone' */
  if (rtb_Sum_ky > 1.0F) {
    rtb_Sum1 = rtb_Sum_ky - 1.0F;
  } else if (rtb_Sum_ky >= 0.0F) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_ky;
  }

  /* End of DeadZone: '<S48>/DeadZone' */

  /* Signum: '<S48>/SignPreSat' */
  if (rtb_Sum_ky < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Sum_ky > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum_ky == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum_ky;
  }

  /* Signum: '<S48>/SignPreIntegrator' */
  if (rtb_Sum5 < 0.0F) {
    u = -1.0F;
  } else if (rtb_Sum5 > 0.0F) {
    u = 1.0F;
  } else if (rtb_Sum5 == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Sum5;
  }

  /* Switch: '<S43>/Switch' incorporates:
   *  Constant: '<S43>/Constant'
   *  Gain: '<S48>/Gain'
   *  Logic: '<S48>/AND'
   *  RelationalOperator: '<S48>/Equal'
   *  RelationalOperator: '<S48>/NotEqual'
   *  Signum: '<S48>/SignPreIntegrator'
   *  Signum: '<S48>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_ky != rtb_Sum1) && (rtb_Sum_ky_0 == u)) {
    rtb_Switch_kd = 0.0F;
  } else {
    rtb_Switch_kd = rtb_Sum5;
  }

  /* End of Switch: '<S43>/Switch' */

  /* Sum: '<S41>/Sum' */
  rtb_Sum1 = rtb_AGCref - rtb_Divide2_g;

  /* MATLAB Function: '<S41>/ModeSelect' incorporates:
   *  BusSelector: '<S1>/BusConversion_InsertedFor_Bus Creator5_at_inport_1'
   */
  /* MATLAB Function 'MGCC2/DFIG1Control/PowerRegulator/ModeSelect': '<S53>:1' */
  if (MGCCode_B.OutEMS_m.DFIG1Mode == ConstPQ) {
    /* '<S53>:1:3' */
    /* ConstP ConstQ */
    /* '<S53>:1:4' */
    rtb_PCtrl_i = 0;

    /* '<S53>:1:5' */
    rtb_QCtrl_n = 0;
  } else if (MGCCode_B.OutEMS_m.DFIG1Mode == ConstPAVC) {
    /* '<S53>:1:6' */
    /* ConstP AVC */
    /* '<S53>:1:7' */
    rtb_PCtrl_i = 0;

    /* '<S53>:1:8' */
    rtb_QCtrl_n = 1;
  } else if (MGCCode_B.OutEMS_m.DFIG1Mode == AGCConstQ) {
    /* '<S53>:1:9' */
    /* AGC ConstQ */
    /* '<S53>:1:10' */
    rtb_PCtrl_i = 1;

    /* '<S53>:1:11' */
    rtb_QCtrl_n = 0;
  } else if (MGCCode_B.OutEMS_m.DFIG1Mode == AGCAVC) {
    /* '<S53>:1:12' */
    /* AGC AVC */
    /* '<S53>:1:13' */
    rtb_PCtrl_i = 1;

    /* '<S53>:1:14' */
    rtb_QCtrl_n = 1;
  } else {
    /* '<S53>:1:16' */
    rtb_PCtrl_i = 0;

    /* '<S53>:1:17' */
    rtb_QCtrl_n = 0;
  }

  /* End of MATLAB Function: '<S41>/ModeSelect' */

  /* DiscreteIntegrator: '<S49>/Integrator' incorporates:
   *  UnitDelay: '<S41>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_h != 0) {
    MGCCode_DWork.Integrator_DSTATE_d1 = MGCCode_DWork.UnitDelay2_DSTATE_c;
  }

  if (((rtb_PCtrl_i > 0) && (MGCCode_DWork.Integrator_PrevResetState_ja <= 0)) ||
      ((rtb_PCtrl_i <= 0) && (MGCCode_DWork.Integrator_PrevResetState_ja == 1)))
  {
    MGCCode_DWork.Integrator_DSTATE_d1 = MGCCode_DWork.UnitDelay2_DSTATE_c;
  }

  /* Sum: '<S49>/Sum' incorporates:
   *  DiscreteIntegrator: '<S49>/Integrator'
   *  Gain: '<S49>/Proportional Gain'
   */
  rtb_Sum_e = StructPointer->CtrlParamDFIG1.AGCInnerPIGain * rtb_Sum1 +
    MGCCode_DWork.Integrator_DSTATE_d1;

  /* Sum: '<S41>/Sum1' */
  rtb_Cp = rtb_Sum2 - rtb_Divide2_g;

  /* DiscreteIntegrator: '<S50>/Integrator' incorporates:
   *  UnitDelay: '<S41>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_c != 0) {
    MGCCode_DWork.Integrator_DSTATE_ps = MGCCode_DWork.UnitDelay2_DSTATE_c;
  }

  if (((rtb_PCtrl_i > 0) && (MGCCode_DWork.Integrator_PrevResetState_cx <= 0)) ||
      ((rtb_PCtrl_i <= 0) && (MGCCode_DWork.Integrator_PrevResetState_cx == 1)))
  {
    MGCCode_DWork.Integrator_DSTATE_ps = MGCCode_DWork.UnitDelay2_DSTATE_c;
  }

  /* Sum: '<S50>/Sum' incorporates:
   *  DiscreteIntegrator: '<S50>/Integrator'
   *  Gain: '<S50>/Proportional Gain'
   */
  rtb_Sum2 = StructPointer->CtrlParamDFIG1.ConstPPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_ps;

  /* Switch: '<S41>/Switch' incorporates:
   *  Saturate: '<S50>/Saturation'
   */
  if (rtb_PCtrl_i != 0) {
    /* Saturate: '<S49>/Saturation' */
    if (rtb_Sum_e >= StructPointer->CtrlParamDFIG1.AGCInnerPIUpperSat) {
      rtb_Switch_pt = StructPointer->CtrlParamDFIG1.AGCInnerPIUpperSat;
    } else if (rtb_Sum_e <= StructPointer->CtrlParamDFIG1.AGCInnerPILowerSat) {
      rtb_Switch_pt = StructPointer->CtrlParamDFIG1.AGCInnerPILowerSat;
    } else {
      rtb_Switch_pt = rtb_Sum_e;
    }

    /* End of Saturate: '<S49>/Saturation' */
  } else if (rtb_Sum2 >= StructPointer->CtrlParamDFIG1.ConstPPIUpperSat) {
    /* Saturate: '<S50>/Saturation' */
    rtb_Switch_pt = StructPointer->CtrlParamDFIG1.ConstPPIUpperSat;
  } else if (rtb_Sum2 <= StructPointer->CtrlParamDFIG1.ConstPPILowerSat) {
    /* Saturate: '<S50>/Saturation' */
    rtb_Switch_pt = StructPointer->CtrlParamDFIG1.ConstPPILowerSat;
  } else {
    /* Saturate: '<S50>/Saturation' */
    rtb_Switch_pt = rtb_Sum2;
  }

  /* End of Switch: '<S41>/Switch' */

  /* Saturate: '<S41>/Saturation' */
  if (rtb_Switch_pt >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch_pt <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch_pt;
  }

  /* Product: '<S40>/Product2' incorporates:
   *  Saturate: '<S41>/Saturation'
   */
  rtb_Sum_ky = rtb_Cp_0 * rtb_Gain_eq;

  /* Sum: '<S41>/Sum5' */
  rtb_DeadZone_d = rtb_AVCref - rtb_Divide7_n;

  /* DiscreteIntegrator: '<S52>/Integrator' incorporates:
   *  UnitDelay: '<S41>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_m1 != 0) {
    MGCCode_DWork.Integrator_DSTATE_b = MGCCode_DWork.UnitDelay4_DSTATE_c;
  }

  if (((rtb_QCtrl_n > 0) && (MGCCode_DWork.Integrator_PrevResetState_ks <= 0)) ||
      ((rtb_QCtrl_n <= 0) && (MGCCode_DWork.Integrator_PrevResetState_ks == 1)))
  {
    MGCCode_DWork.Integrator_DSTATE_b = MGCCode_DWork.UnitDelay4_DSTATE_c;
  }

  /* Sum: '<S52>/Sum' incorporates:
   *  DiscreteIntegrator: '<S52>/Integrator'
   *  Gain: '<S52>/Proportional Gain'
   */
  rtb_Pmax = StructPointer->CtrlParamDFIG1.AVCInnerPIGain * rtb_DeadZone_d +
    MGCCode_DWork.Integrator_DSTATE_b;

  /* Sum: '<S41>/Sum6' */
  rtb_Integrator_a = rtb_Sum_p - rtb_Divide7_n;

  /* DiscreteIntegrator: '<S51>/Integrator' incorporates:
   *  UnitDelay: '<S41>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_b4 != 0) {
    MGCCode_DWork.Integrator_DSTATE_gp = MGCCode_DWork.UnitDelay4_DSTATE_c;
  }

  if (((rtb_QCtrl_n > 0) && (MGCCode_DWork.Integrator_PrevResetState_bh <= 0)) ||
      ((rtb_QCtrl_n <= 0) && (MGCCode_DWork.Integrator_PrevResetState_bh == 1)))
  {
    MGCCode_DWork.Integrator_DSTATE_gp = MGCCode_DWork.UnitDelay4_DSTATE_c;
  }

  /* Sum: '<S51>/Sum' incorporates:
   *  DiscreteIntegrator: '<S51>/Integrator'
   *  Gain: '<S51>/Proportional Gain'
   */
  rtb_Sum_l = StructPointer->CtrlParamDFIG1.ConstQPIGain * rtb_Integrator_a +
    MGCCode_DWork.Integrator_DSTATE_gp;

  /* Switch: '<S41>/Switch2' incorporates:
   *  Saturate: '<S51>/Saturation'
   */
  if (rtb_QCtrl_n != 0) {
    /* Saturate: '<S52>/Saturation' */
    if (rtb_Pmax >= StructPointer->CtrlParamDFIG1.AVCInnerPIUpperSat) {
      rtb_Switch2_j = StructPointer->CtrlParamDFIG1.AVCInnerPIUpperSat;
    } else if (rtb_Pmax <= StructPointer->CtrlParamDFIG1.AVCInnerPILowerSat) {
      rtb_Switch2_j = StructPointer->CtrlParamDFIG1.AVCInnerPILowerSat;
    } else {
      rtb_Switch2_j = rtb_Pmax;
    }

    /* End of Saturate: '<S52>/Saturation' */
  } else if (rtb_Sum_l >= StructPointer->CtrlParamDFIG1.ConstQPIUpperSat) {
    /* Saturate: '<S51>/Saturation' */
    rtb_Switch2_j = StructPointer->CtrlParamDFIG1.ConstQPIUpperSat;
  } else if (rtb_Sum_l <= StructPointer->CtrlParamDFIG1.ConstQPILowerSat) {
    /* Saturate: '<S51>/Saturation' */
    rtb_Switch2_j = StructPointer->CtrlParamDFIG1.ConstQPILowerSat;
  } else {
    /* Saturate: '<S51>/Saturation' */
    rtb_Switch2_j = rtb_Sum_l;
  }

  /* End of Switch: '<S41>/Switch2' */

  /* Saturate: '<S41>/Saturation2' */
  if (rtb_Switch2_j >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch2_j <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch2_j;
  }

  /* Product: '<S40>/Product3' incorporates:
   *  Saturate: '<S41>/Saturation2'
   */
  rtb_Add4 = rtb_Sqrt * rtb_Cp_0;

  /* Gain: '<S49>/Integral Gain' */
  rtb_Sum1 = StructPointer->CtrlParamDFIG1.AGCInnerPIIntegral * rtb_Sum1;

  /* DeadZone: '<S54>/DeadZone' */
  if (rtb_Sum_e > StructPointer->CtrlParamDFIG1.AGCInnerPIUpperSat) {
    u = rtb_Sum_e - StructPointer->CtrlParamDFIG1.AGCInnerPIUpperSat;
  } else if (rtb_Sum_e >= StructPointer->CtrlParamDFIG1.AGCInnerPILowerSat) {
    u = 0.0F;
  } else {
    u = rtb_Sum_e - StructPointer->CtrlParamDFIG1.AGCInnerPILowerSat;
  }

  /* End of DeadZone: '<S54>/DeadZone' */

  /* Signum: '<S54>/SignPreSat' */
  if (rtb_Sum_e < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Sum_e > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum_e == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum_e;
  }

  /* Signum: '<S54>/SignPreIntegrator' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* Switch: '<S49>/Switch' incorporates:
   *  Constant: '<S49>/Constant'
   *  Gain: '<S54>/Gain'
   *  Logic: '<S54>/AND'
   *  RelationalOperator: '<S54>/Equal'
   *  RelationalOperator: '<S54>/NotEqual'
   *  Signum: '<S54>/SignPreIntegrator'
   *  Signum: '<S54>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_e != u) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_gl = 0.0F;
  } else {
    rtb_Switch_gl = rtb_Sum1;
  }

  /* End of Switch: '<S49>/Switch' */

  /* DeadZone: '<S55>/DeadZone' */
  if (rtb_Sum2 > StructPointer->CtrlParamDFIG1.ConstPPIUpperSat) {
    rtb_Sum1 = rtb_Sum2 - StructPointer->CtrlParamDFIG1.ConstPPIUpperSat;
  } else if (rtb_Sum2 >= StructPointer->CtrlParamDFIG1.ConstPPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum2 - StructPointer->CtrlParamDFIG1.ConstPPILowerSat;
  }

  /* End of DeadZone: '<S55>/DeadZone' */

  /* Gain: '<S50>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamDFIG1.ConstPPIIntegral * rtb_Cp;

  /* Signum: '<S55>/SignPreSat' */
  if (rtb_Sum2 < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum2 > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum2 == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum2;
  }

  /* Signum: '<S55>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S50>/Switch' incorporates:
   *  Constant: '<S50>/Constant'
   *  Gain: '<S55>/Gain'
   *  Logic: '<S55>/AND'
   *  RelationalOperator: '<S55>/Equal'
   *  RelationalOperator: '<S55>/NotEqual'
   *  Signum: '<S55>/SignPreIntegrator'
   *  Signum: '<S55>/SignPreSat'
   */
  if ((0.0F * rtb_Sum2 != rtb_Sum1) && (rtb_Sum_l_0 == rtb_Cp_0)) {
    rtb_Switch_b1 = 0.0F;
  } else {
    rtb_Switch_b1 = rtb_Cp;
  }

  /* End of Switch: '<S50>/Switch' */

  /* DeadZone: '<S56>/DeadZone' */
  if (rtb_Sum_l > StructPointer->CtrlParamDFIG1.ConstQPIUpperSat) {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamDFIG1.ConstQPIUpperSat;
  } else if (rtb_Sum_l >= StructPointer->CtrlParamDFIG1.ConstQPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamDFIG1.ConstQPILowerSat;
  }

  /* End of DeadZone: '<S56>/DeadZone' */

  /* Gain: '<S51>/Integral Gain' */
  rtb_Integrator_a = StructPointer->CtrlParamDFIG1.ConstQPIIntegral *
    rtb_Integrator_a;

  /* Signum: '<S56>/SignPreSat' */
  if (rtb_Sum_l < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum_l > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum_l == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum_l;
  }

  /* Signum: '<S56>/SignPreIntegrator' */
  if (rtb_Integrator_a < 0.0F) {
    u = -1.0F;
  } else if (rtb_Integrator_a > 0.0F) {
    u = 1.0F;
  } else if (rtb_Integrator_a == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Integrator_a;
  }

  /* Switch: '<S51>/Switch' incorporates:
   *  Constant: '<S51>/Constant'
   *  Gain: '<S56>/Gain'
   *  Logic: '<S56>/AND'
   *  RelationalOperator: '<S56>/Equal'
   *  RelationalOperator: '<S56>/NotEqual'
   *  Signum: '<S56>/SignPreIntegrator'
   *  Signum: '<S56>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_l != rtb_Sum1) && (rtb_Sum_l_0 == u)) {
    rtb_Switch_pb = 0.0F;
  } else {
    rtb_Switch_pb = rtb_Integrator_a;
  }

  /* End of Switch: '<S51>/Switch' */

  /* DeadZone: '<S57>/DeadZone' */
  if (rtb_Pmax > StructPointer->CtrlParamDFIG1.AVCInnerPIUpperSat) {
    rtb_Sum1 = rtb_Pmax - StructPointer->CtrlParamDFIG1.AVCInnerPIUpperSat;
  } else if (rtb_Pmax >= StructPointer->CtrlParamDFIG1.AVCInnerPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Pmax - StructPointer->CtrlParamDFIG1.AVCInnerPILowerSat;
  }

  /* End of DeadZone: '<S57>/DeadZone' */

  /* Gain: '<S52>/Integral Gain' */
  rtb_DeadZone_d = StructPointer->CtrlParamDFIG1.AVCInnerPIIntegral *
    rtb_DeadZone_d;

  /* Signum: '<S57>/SignPreSat' */
  if (rtb_Pmax < 0.0F) {
    rtb_Pmax_0 = -1.0F;
  } else if (rtb_Pmax > 0.0F) {
    rtb_Pmax_0 = 1.0F;
  } else if (rtb_Pmax == 0.0F) {
    rtb_Pmax_0 = 0.0F;
  } else {
    rtb_Pmax_0 = rtb_Pmax;
  }

  /* Signum: '<S57>/SignPreIntegrator' */
  if (rtb_DeadZone_d < 0.0F) {
    u = -1.0F;
  } else if (rtb_DeadZone_d > 0.0F) {
    u = 1.0F;
  } else if (rtb_DeadZone_d == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_DeadZone_d;
  }

  /* Switch: '<S52>/Switch' incorporates:
   *  Constant: '<S52>/Constant'
   *  Gain: '<S57>/Gain'
   *  Logic: '<S57>/AND'
   *  RelationalOperator: '<S57>/Equal'
   *  RelationalOperator: '<S57>/NotEqual'
   *  Signum: '<S57>/SignPreIntegrator'
   *  Signum: '<S57>/SignPreSat'
   */
  if ((0.0F * rtb_Pmax != rtb_Sum1) && (rtb_Pmax_0 == u)) {
    rtb_Switch_f = 0.0F;
  } else {
    rtb_Switch_f = rtb_DeadZone_d;
  }

  /* End of Switch: '<S52>/Switch' */

  /* Product: '<S62>/Divide1' incorporates:
   *  Inport: '<Root>/InICEn'
   */
  rtb_Sum1 = MGCCode_U.InICEn.ICESPref / rtb_Product;

  /* Product: '<S62>/Divide5' incorporates:
   *  Inport: '<Root>/InICEn'
   */
  rtb_Switch1 = MGCCode_U.InICEn.ICESPout / rtb_Product;

  /* Product: '<S62>/Divide7' incorporates:
   *  Inport: '<Root>/InICEn'
   */
  rtb_Sum5 = MGCCode_U.InICEn.ICESQout / rtb_Product2;

  /* Saturate: '<S62>/Saturation' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_Pmax = 1.0F;
  } else if (rtb_Sum1 <= 0.0F) {
    rtb_Pmax = 0.0F;
  } else {
    rtb_Pmax = rtb_Sum1;
  }

  /* End of Saturate: '<S62>/Saturation' */

  /* Product: '<S62>/Divide2' incorporates:
   *  Inport: '<Root>/InICEn'
   */
  u = MGCCode_U.InICEn.ICESQref / rtb_Product2;

  /* Sum: '<S64>/Sum' */
  rtb_Sum1 = rtb_AGCref - rtb_Switch1;

  /* Gain: '<S65>/Proportional Gain' */
  rtb_Sum_l = StructPointer->CtrlParamICE.AGCInnerPIGain * rtb_Sum1;

  /* MATLAB Function: '<S64>/ModeSelect' */
  MGCCode_ModeSelect(rtb_ICEMode_lks, &MGCCode_B.sf_ModeSelect_k);

  /* DiscreteIntegrator: '<S65>/Integrator' incorporates:
   *  UnitDelay: '<S64>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_n != 0) {
    MGCCode_DWork.Integrator_DSTATE_kx = MGCCode_DWork.UnitDelay2_DSTATE_o;
  }

  if (((MGCCode_B.sf_ModeSelect_k.PCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_g <= 0)) ||
      ((MGCCode_B.sf_ModeSelect_k.PCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_g == 1))) {
    MGCCode_DWork.Integrator_DSTATE_kx = MGCCode_DWork.UnitDelay2_DSTATE_o;
  }

  /* Sum: '<S65>/Sum' incorporates:
   *  DiscreteIntegrator: '<S65>/Integrator'
   */
  rtb_Sum_p = rtb_Sum_l + MGCCode_DWork.Integrator_DSTATE_kx;

  /* Sum: '<S64>/Sum1' */
  rtb_Cp = rtb_Pmax - rtb_Switch1;

  /* DiscreteIntegrator: '<S66>/Integrator' incorporates:
   *  UnitDelay: '<S64>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_k != 0) {
    MGCCode_DWork.Integrator_DSTATE_pc = MGCCode_DWork.UnitDelay2_DSTATE_o;
  }

  if (((MGCCode_B.sf_ModeSelect_k.PCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_d <= 0)) ||
      ((MGCCode_B.sf_ModeSelect_k.PCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_d == 1))) {
    MGCCode_DWork.Integrator_DSTATE_pc = MGCCode_DWork.UnitDelay2_DSTATE_o;
  }

  /* Sum: '<S66>/Sum' incorporates:
   *  DiscreteIntegrator: '<S66>/Integrator'
   *  Gain: '<S66>/Proportional Gain'
   */
  rtb_Sum_e = StructPointer->CtrlParamICE.ConstPPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_pc;

  /* Switch: '<S64>/Switch' incorporates:
   *  Saturate: '<S66>/Saturation'
   */
  if (MGCCode_B.sf_ModeSelect_k.PCtrl != 0) {
    /* Saturate: '<S65>/Saturation' */
    if (rtb_Sum_p >= StructPointer->CtrlParamICE.AGCInnerPIUpperSat) {
      rtb_Switch_et = StructPointer->CtrlParamICE.AGCInnerPIUpperSat;
    } else if (rtb_Sum_p <= StructPointer->CtrlParamICE.AGCInnerPILowerSat) {
      rtb_Switch_et = StructPointer->CtrlParamICE.AGCInnerPILowerSat;
    } else {
      rtb_Switch_et = rtb_Sum_p;
    }

    /* End of Saturate: '<S65>/Saturation' */
  } else if (rtb_Sum_e >= StructPointer->CtrlParamICE.ConstPPIUpperSat) {
    /* Saturate: '<S66>/Saturation' */
    rtb_Switch_et = StructPointer->CtrlParamICE.ConstPPIUpperSat;
  } else if (rtb_Sum_e <= StructPointer->CtrlParamICE.ConstPPILowerSat) {
    /* Saturate: '<S66>/Saturation' */
    rtb_Switch_et = StructPointer->CtrlParamICE.ConstPPILowerSat;
  } else {
    /* Saturate: '<S66>/Saturation' */
    rtb_Switch_et = rtb_Sum_e;
  }

  /* End of Switch: '<S64>/Switch' */

  /* Saturate: '<S64>/Saturation' */
  if (rtb_Switch_et >= 1.0F) {
    rtb_DFIG1SPout = 1.0F;
  } else if (rtb_Switch_et <= 0.0F) {
    rtb_DFIG1SPout = 0.0F;
  } else {
    rtb_DFIG1SPout = rtb_Switch_et;
  }

  /* Sum: '<S64>/Sum5' */
  rtb_DeadZone_d = rtb_AVCref - rtb_Sum5;

  /* DiscreteIntegrator: '<S68>/Integrator' incorporates:
   *  UnitDelay: '<S64>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_ae != 0) {
    MGCCode_DWork.Integrator_DSTATE_c = MGCCode_DWork.UnitDelay4_DSTATE_e;
  }

  if (((MGCCode_B.sf_ModeSelect_k.QCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_gk <= 0)) ||
      ((MGCCode_B.sf_ModeSelect_k.QCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_gk == 1))) {
    MGCCode_DWork.Integrator_DSTATE_c = MGCCode_DWork.UnitDelay4_DSTATE_e;
  }

  /* Sum: '<S68>/Sum' incorporates:
   *  DiscreteIntegrator: '<S68>/Integrator'
   *  Gain: '<S68>/Proportional Gain'
   */
  rtb_Pmax = StructPointer->CtrlParamICE.AVCInnerPIGain * rtb_DeadZone_d +
    MGCCode_DWork.Integrator_DSTATE_c;

  /* Saturate: '<S62>/Saturation1' */
  if (u >= 1.0F) {
    u = 1.0F;
  } else {
    if (u <= 0.0F) {
      u = 0.0F;
    }
  }

  /* End of Saturate: '<S62>/Saturation1' */

  /* Sum: '<S64>/Sum6' */
  rtb_Integrator_a = u - rtb_Sum5;

  /* DiscreteIntegrator: '<S67>/Integrator' incorporates:
   *  UnitDelay: '<S64>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_ak != 0) {
    MGCCode_DWork.Integrator_DSTATE_dq = MGCCode_DWork.UnitDelay4_DSTATE_e;
  }

  if (((MGCCode_B.sf_ModeSelect_k.QCtrl > 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_jd <= 0)) ||
      ((MGCCode_B.sf_ModeSelect_k.QCtrl <= 0) &&
       (MGCCode_DWork.Integrator_PrevResetState_jd == 1))) {
    MGCCode_DWork.Integrator_DSTATE_dq = MGCCode_DWork.UnitDelay4_DSTATE_e;
  }

  /* Sum: '<S67>/Sum' incorporates:
   *  DiscreteIntegrator: '<S67>/Integrator'
   *  Gain: '<S67>/Proportional Gain'
   */
  rtb_Sum_l = StructPointer->CtrlParamICE.ConstQPIGain * rtb_Integrator_a +
    MGCCode_DWork.Integrator_DSTATE_dq;

  /* Switch: '<S64>/Switch2' incorporates:
   *  Saturate: '<S67>/Saturation'
   */
  if (MGCCode_B.sf_ModeSelect_k.QCtrl != 0) {
    /* Saturate: '<S68>/Saturation' */
    if (rtb_Pmax >= StructPointer->CtrlParamICE.AVCInnerPIUpperSat) {
      rtb_Switch2_a = StructPointer->CtrlParamICE.AVCInnerPIUpperSat;
    } else if (rtb_Pmax <= StructPointer->CtrlParamICE.AVCInnerPILowerSat) {
      rtb_Switch2_a = StructPointer->CtrlParamICE.AVCInnerPILowerSat;
    } else {
      rtb_Switch2_a = rtb_Pmax;
    }

    /* End of Saturate: '<S68>/Saturation' */
  } else if (rtb_Sum_l >= StructPointer->CtrlParamICE.ConstQPIUpperSat) {
    /* Saturate: '<S67>/Saturation' */
    rtb_Switch2_a = StructPointer->CtrlParamICE.ConstQPIUpperSat;
  } else if (rtb_Sum_l <= StructPointer->CtrlParamICE.ConstQPILowerSat) {
    /* Saturate: '<S67>/Saturation' */
    rtb_Switch2_a = StructPointer->CtrlParamICE.ConstQPILowerSat;
  } else {
    /* Saturate: '<S67>/Saturation' */
    rtb_Switch2_a = rtb_Sum_l;
  }

  /* End of Switch: '<S64>/Switch2' */

  /* Saturate: '<S64>/Saturation2' */
  if (rtb_Switch2_a >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch2_a <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch2_a;
  }

  /* Product: '<S63>/Product1' incorporates:
   *  Saturate: '<S64>/Saturation2'
   */
  rtb_Integrator_c = rtb_Product2 * rtb_Cp_0;

  /* Gain: '<S65>/Integral Gain' */
  rtb_Sum1 = StructPointer->CtrlParamICE.AGCInnerPIIntegral * rtb_Sum1;

  /* DeadZone: '<S70>/DeadZone' */
  if (rtb_Sum_p > StructPointer->CtrlParamICE.AGCInnerPIUpperSat) {
    u = rtb_Sum_p - StructPointer->CtrlParamICE.AGCInnerPIUpperSat;
  } else if (rtb_Sum_p >= StructPointer->CtrlParamICE.AGCInnerPILowerSat) {
    u = 0.0F;
  } else {
    u = rtb_Sum_p - StructPointer->CtrlParamICE.AGCInnerPILowerSat;
  }

  /* End of DeadZone: '<S70>/DeadZone' */

  /* Signum: '<S70>/SignPreSat' */
  if (rtb_Sum_p < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Sum_p > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Sum_p == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Sum_p;
  }

  /* Signum: '<S70>/SignPreIntegrator' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* Switch: '<S65>/Switch' incorporates:
   *  Constant: '<S65>/Constant'
   *  Gain: '<S70>/Gain'
   *  Logic: '<S70>/AND'
   *  RelationalOperator: '<S70>/Equal'
   *  RelationalOperator: '<S70>/NotEqual'
   *  Signum: '<S70>/SignPreIntegrator'
   *  Signum: '<S70>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_p != u) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_l = 0.0F;
  } else {
    rtb_Switch_l = rtb_Sum1;
  }

  /* End of Switch: '<S65>/Switch' */

  /* DeadZone: '<S71>/DeadZone' */
  if (rtb_Sum_e > StructPointer->CtrlParamICE.ConstPPIUpperSat) {
    rtb_Sum1 = rtb_Sum_e - StructPointer->CtrlParamICE.ConstPPIUpperSat;
  } else if (rtb_Sum_e >= StructPointer->CtrlParamICE.ConstPPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_e - StructPointer->CtrlParamICE.ConstPPILowerSat;
  }

  /* End of DeadZone: '<S71>/DeadZone' */

  /* Gain: '<S66>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamICE.ConstPPIIntegral * rtb_Cp;

  /* Signum: '<S71>/SignPreSat' */
  if (rtb_Sum_e < 0.0F) {
    u = -1.0F;
  } else if (rtb_Sum_e > 0.0F) {
    u = 1.0F;
  } else if (rtb_Sum_e == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Sum_e;
  }

  /* Signum: '<S71>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S66>/Switch' incorporates:
   *  Constant: '<S66>/Constant'
   *  Gain: '<S71>/Gain'
   *  Logic: '<S71>/AND'
   *  RelationalOperator: '<S71>/Equal'
   *  RelationalOperator: '<S71>/NotEqual'
   *  Signum: '<S71>/SignPreIntegrator'
   *  Signum: '<S71>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_e != rtb_Sum1) && (u == rtb_Cp_0)) {
    rtb_Switch_n = 0.0F;
  } else {
    rtb_Switch_n = rtb_Cp;
  }

  /* End of Switch: '<S66>/Switch' */

  /* DeadZone: '<S72>/DeadZone' */
  if (rtb_Sum_l > StructPointer->CtrlParamICE.ConstQPIUpperSat) {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamICE.ConstQPIUpperSat;
  } else if (rtb_Sum_l >= StructPointer->CtrlParamICE.ConstQPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamICE.ConstQPILowerSat;
  }

  /* End of DeadZone: '<S72>/DeadZone' */

  /* Gain: '<S67>/Integral Gain' */
  rtb_Integrator_a = StructPointer->CtrlParamICE.ConstQPIIntegral *
    rtb_Integrator_a;

  /* Signum: '<S72>/SignPreSat' */
  if (rtb_Sum_l < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum_l > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum_l == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum_l;
  }

  /* Signum: '<S72>/SignPreIntegrator' */
  if (rtb_Integrator_a < 0.0F) {
    u = -1.0F;
  } else if (rtb_Integrator_a > 0.0F) {
    u = 1.0F;
  } else if (rtb_Integrator_a == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Integrator_a;
  }

  /* Switch: '<S67>/Switch' incorporates:
   *  Constant: '<S67>/Constant'
   *  Gain: '<S72>/Gain'
   *  Logic: '<S72>/AND'
   *  RelationalOperator: '<S72>/Equal'
   *  RelationalOperator: '<S72>/NotEqual'
   *  Signum: '<S72>/SignPreIntegrator'
   *  Signum: '<S72>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_l != rtb_Sum1) && (rtb_Sum_l_0 == u)) {
    rtb_Switch_o = 0.0F;
  } else {
    rtb_Switch_o = rtb_Integrator_a;
  }

  /* End of Switch: '<S67>/Switch' */

  /* DeadZone: '<S73>/DeadZone' */
  if (rtb_Pmax > StructPointer->CtrlParamICE.AVCInnerPIUpperSat) {
    rtb_Sum1 = rtb_Pmax - StructPointer->CtrlParamICE.AVCInnerPIUpperSat;
  } else if (rtb_Pmax >= StructPointer->CtrlParamICE.AVCInnerPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Pmax - StructPointer->CtrlParamICE.AVCInnerPILowerSat;
  }

  /* End of DeadZone: '<S73>/DeadZone' */

  /* Gain: '<S68>/Integral Gain' */
  rtb_DeadZone_d = StructPointer->CtrlParamICE.AVCInnerPIIntegral *
    rtb_DeadZone_d;

  /* Signum: '<S73>/SignPreSat' */
  if (rtb_Pmax < 0.0F) {
    rtb_Pmax_0 = -1.0F;
  } else if (rtb_Pmax > 0.0F) {
    rtb_Pmax_0 = 1.0F;
  } else if (rtb_Pmax == 0.0F) {
    rtb_Pmax_0 = 0.0F;
  } else {
    rtb_Pmax_0 = rtb_Pmax;
  }

  /* Signum: '<S73>/SignPreIntegrator' */
  if (rtb_DeadZone_d < 0.0F) {
    u = -1.0F;
  } else if (rtb_DeadZone_d > 0.0F) {
    u = 1.0F;
  } else if (rtb_DeadZone_d == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_DeadZone_d;
  }

  /* Switch: '<S68>/Switch' incorporates:
   *  Constant: '<S68>/Constant'
   *  Gain: '<S73>/Gain'
   *  Logic: '<S73>/AND'
   *  RelationalOperator: '<S73>/Equal'
   *  RelationalOperator: '<S73>/NotEqual'
   *  Signum: '<S73>/SignPreIntegrator'
   *  Signum: '<S73>/SignPreSat'
   */
  if ((0.0F * rtb_Pmax != rtb_Sum1) && (rtb_Pmax_0 == u)) {
    rtb_Switch_kw = 0.0F;
  } else {
    rtb_Switch_kw = rtb_DeadZone_d;
  }

  /* End of Switch: '<S68>/Switch' */

  /* Product: '<S74>/Divide1' incorporates:
   *  Inport: '<Root>/InPVn'
   */
  rtb_Sum1 = MGCCode_U.InPVn.PVSQref / rtb_DeadZone;

  /* Product: '<S74>/Divide2' incorporates:
   *  Inport: '<Root>/InPVn'
   */
  rtb_Sum_p = MGCCode_U.InPVn.PVSQout / rtb_DeadZone;

  /* Product: '<S74>/Divide5' incorporates:
   *  Inport: '<Root>/InPVn'
   */
  rtb_Product_l = MGCCode_U.InPVn.PVSPout / rtb_PVSPcmd;

  /* Saturate: '<S74>/Saturation2' */
  if (rtb_Sum1 >= 1.0F) {
    rtb_Sum_l = 1.0F;
  } else if (rtb_Sum1 <= 0.0F) {
    rtb_Sum_l = 0.0F;
  } else {
    rtb_Sum_l = rtb_Sum1;
  }

  /* End of Saturate: '<S74>/Saturation2' */

  /* Sum: '<S76>/Sum' */
  rtb_Sum1 = rtb_AGCref - rtb_Product_l;

  /* MATLAB Function: '<S76>/ModeSelect' */
  /* MATLAB Function 'MGCC2/PVControl/PowerRegulator/ModeSelect': '<S81>:1' */
  if (rtb_PVMode_a115 == ConstPQ) {
    /* '<S81>:1:3' */
    /* ConstP ConstQ */
    /* '<S81>:1:4' */
    rtb_PCtrl = 0;

    /* '<S81>:1:5' */
    rtb_QCtrl = 0;
  } else if (rtb_PVMode_a115 == ConstPAVC) {
    /* '<S81>:1:6' */
    /* ConstP AVC */
    /* '<S81>:1:7' */
    rtb_PCtrl = 0;

    /* '<S81>:1:8' */
    rtb_QCtrl = 1;
  } else if (rtb_PVMode_a115 == AGCConstQ) {
    /* '<S81>:1:9' */
    /* AGC ConstQ */
    /* '<S81>:1:10' */
    rtb_PCtrl = 1;

    /* '<S81>:1:11' */
    rtb_QCtrl = 0;
  } else if (rtb_PVMode_a115 == AGCAVC) {
    /* '<S81>:1:12' */
    /* AGC AVC */
    /* '<S81>:1:13' */
    rtb_PCtrl = 1;

    /* '<S81>:1:14' */
    rtb_QCtrl = 1;
  } else {
    /* '<S81>:1:16' */
    rtb_PCtrl = 0;

    /* '<S81>:1:17' */
    rtb_QCtrl = 0;
  }

  /* End of MATLAB Function: '<S76>/ModeSelect' */

  /* DiscreteIntegrator: '<S77>/Integrator' incorporates:
   *  UnitDelay: '<S76>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_iv != 0) {
    MGCCode_DWork.Integrator_DSTATE_bp = MGCCode_DWork.UnitDelay2_DSTATE_b;
  }

  if (((rtb_PCtrl > 0) && (MGCCode_DWork.Integrator_PrevResetState_m <= 0)) ||
      ((rtb_PCtrl <= 0) && (MGCCode_DWork.Integrator_PrevResetState_m == 1))) {
    MGCCode_DWork.Integrator_DSTATE_bp = MGCCode_DWork.UnitDelay2_DSTATE_b;
  }

  /* Sum: '<S77>/Sum' incorporates:
   *  DiscreteIntegrator: '<S77>/Integrator'
   *  Gain: '<S77>/Proportional Gain'
   */
  rtb_Pmax = StructPointer->CtrlParamPV.AGCInnerPIGain * rtb_Sum1 +
    MGCCode_DWork.Integrator_DSTATE_bp;

  /* Product: '<S74>/Divide7' incorporates:
   *  Inport: '<Root>/InPVn'
   */
  u = MGCCode_U.InPVn.PVSPref / rtb_PVSPcmd;

  /* Saturate: '<S74>/Saturation1' */
  if (u >= 1.0F) {
    u = 1.0F;
  } else {
    if (u <= 0.0F) {
      u = 0.0F;
    }
  }

  /* Sum: '<S76>/Sum1' incorporates:
   *  Saturate: '<S74>/Saturation1'
   */
  rtb_Product2 = u - rtb_Product_l;

  /* DiscreteIntegrator: '<S78>/Integrator' incorporates:
   *  UnitDelay: '<S76>/Unit Delay2'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_g != 0) {
    MGCCode_DWork.Integrator_DSTATE_e = MGCCode_DWork.UnitDelay2_DSTATE_b;
  }

  if (((rtb_PCtrl > 0) && (MGCCode_DWork.Integrator_PrevResetState_bp <= 0)) ||
      ((rtb_PCtrl <= 0) && (MGCCode_DWork.Integrator_PrevResetState_bp == 1))) {
    MGCCode_DWork.Integrator_DSTATE_e = MGCCode_DWork.UnitDelay2_DSTATE_b;
  }

  /* Sum: '<S78>/Sum' incorporates:
   *  DiscreteIntegrator: '<S78>/Integrator'
   *  Gain: '<S78>/Proportional Gain'
   */
  rtb_Sum2 = StructPointer->CtrlParamPV.ConstPPIGain * rtb_Product2 +
    MGCCode_DWork.Integrator_DSTATE_e;

  /* Switch: '<S76>/Switch' incorporates:
   *  Saturate: '<S78>/Saturation'
   */
  if (rtb_PCtrl != 0) {
    /* Saturate: '<S77>/Saturation' */
    if (rtb_Pmax >= StructPointer->CtrlParamPV.AGCInnerPIUpperSat) {
      rtb_Switch_pk = StructPointer->CtrlParamPV.AGCInnerPIUpperSat;
    } else if (rtb_Pmax <= StructPointer->CtrlParamPV.AGCInnerPILowerSat) {
      rtb_Switch_pk = StructPointer->CtrlParamPV.AGCInnerPILowerSat;
    } else {
      rtb_Switch_pk = rtb_Pmax;
    }

    /* End of Saturate: '<S77>/Saturation' */
  } else if (rtb_Sum2 >= StructPointer->CtrlParamPV.ConstPPIUpperSat) {
    /* Saturate: '<S78>/Saturation' */
    rtb_Switch_pk = StructPointer->CtrlParamPV.ConstPPIUpperSat;
  } else if (rtb_Sum2 <= StructPointer->CtrlParamPV.ConstPPILowerSat) {
    /* Saturate: '<S78>/Saturation' */
    rtb_Switch_pk = StructPointer->CtrlParamPV.ConstPPILowerSat;
  } else {
    /* Saturate: '<S78>/Saturation' */
    rtb_Switch_pk = rtb_Sum2;
  }

  /* End of Switch: '<S76>/Switch' */

  /* Saturate: '<S76>/Saturation' */
  if (rtb_Switch_pk >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch_pk <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch_pk;
  }

  /* Product: '<S75>/Product' incorporates:
   *  Saturate: '<S76>/Saturation'
   */
  rtb_PVSPcmd *= rtb_Cp_0;

  /* Sum: '<S76>/Sum5' */
  rtb_Cp = rtb_AVCref - rtb_Sum_p;

  /* DiscreteIntegrator: '<S80>/Integrator' incorporates:
   *  UnitDelay: '<S76>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_f != 0) {
    MGCCode_DWork.Integrator_DSTATE_at = MGCCode_DWork.UnitDelay4_DSTATE_d;
  }

  if (((rtb_QCtrl > 0) && (MGCCode_DWork.Integrator_PrevResetState_le <= 0)) ||
      ((rtb_QCtrl <= 0) && (MGCCode_DWork.Integrator_PrevResetState_le == 1))) {
    MGCCode_DWork.Integrator_DSTATE_at = MGCCode_DWork.UnitDelay4_DSTATE_d;
  }

  /* Sum: '<S80>/Sum' incorporates:
   *  DiscreteIntegrator: '<S80>/Integrator'
   *  Gain: '<S80>/Proportional Gain'
   */
  rtb_Sum_e = StructPointer->CtrlParamPV.AVCInnerPIGain * rtb_Cp +
    MGCCode_DWork.Integrator_DSTATE_at;

  /* Sum: '<S76>/Sum6' */
  rtb_DeadZone_d = rtb_Sum_l - rtb_Sum_p;

  /* DiscreteIntegrator: '<S79>/Integrator' incorporates:
   *  UnitDelay: '<S76>/Unit Delay4'
   */
  if (MGCCode_DWork.Integrator_IC_LOADING_ke != 0) {
    MGCCode_DWork.Integrator_DSTATE_o = MGCCode_DWork.UnitDelay4_DSTATE_d;
  }

  if (((rtb_QCtrl > 0) && (MGCCode_DWork.Integrator_PrevResetState_ko <= 0)) ||
      ((rtb_QCtrl <= 0) && (MGCCode_DWork.Integrator_PrevResetState_ko == 1))) {
    MGCCode_DWork.Integrator_DSTATE_o = MGCCode_DWork.UnitDelay4_DSTATE_d;
  }

  /* Sum: '<S79>/Sum' incorporates:
   *  DiscreteIntegrator: '<S79>/Integrator'
   *  Gain: '<S79>/Proportional Gain'
   */
  rtb_Sum_l = StructPointer->CtrlParamPV.ConstQPIGain * rtb_DeadZone_d +
    MGCCode_DWork.Integrator_DSTATE_o;

  /* Switch: '<S76>/Switch2' incorporates:
   *  Saturate: '<S79>/Saturation'
   */
  if (rtb_QCtrl != 0) {
    /* Saturate: '<S80>/Saturation' */
    if (rtb_Sum_e >= StructPointer->CtrlParamPV.AVCInnerPIUpperSat) {
      rtb_Switch2_o = StructPointer->CtrlParamPV.AVCInnerPIUpperSat;
    } else if (rtb_Sum_e <= StructPointer->CtrlParamPV.AVCInnerPILowerSat) {
      rtb_Switch2_o = StructPointer->CtrlParamPV.AVCInnerPILowerSat;
    } else {
      rtb_Switch2_o = rtb_Sum_e;
    }

    /* End of Saturate: '<S80>/Saturation' */
  } else if (rtb_Sum_l >= StructPointer->CtrlParamPV.ConstQPIUpperSat) {
    /* Saturate: '<S79>/Saturation' */
    rtb_Switch2_o = StructPointer->CtrlParamPV.ConstQPIUpperSat;
  } else if (rtb_Sum_l <= StructPointer->CtrlParamPV.ConstQPILowerSat) {
    /* Saturate: '<S79>/Saturation' */
    rtb_Switch2_o = StructPointer->CtrlParamPV.ConstQPILowerSat;
  } else {
    /* Saturate: '<S79>/Saturation' */
    rtb_Switch2_o = rtb_Sum_l;
  }

  /* End of Switch: '<S76>/Switch2' */

  /* Saturate: '<S76>/Saturation2' */
  if (rtb_Switch2_o >= 1.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Switch2_o <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Switch2_o;
  }

  /* Product: '<S75>/Product1' incorporates:
   *  Saturate: '<S76>/Saturation2'
   */
  rtb_DeadZone *= rtb_Cp_0;

  /* RateTransition: '<S75>/Rate Transition' */
  if (MGCCode_M->Timing.TaskCounters.TID[1] == 0) {
    MGCCode_B.PVSPcmd = rtb_PVSPcmd;

    /* RateTransition: '<S75>/Rate Transition' */
    MGCCode_B.PVSQcmd = rtb_DeadZone;
  }

  /* End of RateTransition: '<S75>/Rate Transition' */

  /* DeadZone: '<S82>/DeadZone' */
  if (rtb_Pmax > StructPointer->CtrlParamPV.AGCInnerPIUpperSat) {
    rtb_DeadZone = rtb_Pmax - StructPointer->CtrlParamPV.AGCInnerPIUpperSat;
  } else if (rtb_Pmax >= StructPointer->CtrlParamPV.AGCInnerPILowerSat) {
    rtb_DeadZone = 0.0F;
  } else {
    rtb_DeadZone = rtb_Pmax - StructPointer->CtrlParamPV.AGCInnerPILowerSat;
  }

  /* End of DeadZone: '<S82>/DeadZone' */

  /* Gain: '<S77>/Integral Gain' */
  rtb_Sum1 = StructPointer->CtrlParamPV.AGCInnerPIIntegral * rtb_Sum1;

  /* Signum: '<S82>/SignPreSat' */
  if (rtb_Pmax < 0.0F) {
    rtb_Pmax_0 = -1.0F;
  } else if (rtb_Pmax > 0.0F) {
    rtb_Pmax_0 = 1.0F;
  } else if (rtb_Pmax == 0.0F) {
    rtb_Pmax_0 = 0.0F;
  } else {
    rtb_Pmax_0 = rtb_Pmax;
  }

  /* Signum: '<S82>/SignPreIntegrator' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* Switch: '<S77>/Switch' incorporates:
   *  Constant: '<S77>/Constant'
   *  Gain: '<S82>/Gain'
   *  Logic: '<S82>/AND'
   *  RelationalOperator: '<S82>/Equal'
   *  RelationalOperator: '<S82>/NotEqual'
   *  Signum: '<S82>/SignPreIntegrator'
   *  Signum: '<S82>/SignPreSat'
   */
  if ((0.0F * rtb_Pmax != rtb_DeadZone) && (rtb_Pmax_0 == rtb_Cp_0)) {
    rtb_Switch_k2 = 0.0F;
  } else {
    rtb_Switch_k2 = rtb_Sum1;
  }

  /* End of Switch: '<S77>/Switch' */

  /* DeadZone: '<S83>/DeadZone' */
  if (rtb_Sum2 > StructPointer->CtrlParamPV.ConstPPIUpperSat) {
    rtb_Sum1 = rtb_Sum2 - StructPointer->CtrlParamPV.ConstPPIUpperSat;
  } else if (rtb_Sum2 >= StructPointer->CtrlParamPV.ConstPPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum2 - StructPointer->CtrlParamPV.ConstPPILowerSat;
  }

  /* End of DeadZone: '<S83>/DeadZone' */

  /* Gain: '<S78>/Integral Gain' */
  rtb_Product2 = StructPointer->CtrlParamPV.ConstPPIIntegral * rtb_Product2;

  /* Signum: '<S83>/SignPreSat' */
  if (rtb_Sum2 < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum2 > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum2 == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum2;
  }

  /* Signum: '<S83>/SignPreIntegrator' */
  if (rtb_Product2 < 0.0F) {
    u = -1.0F;
  } else if (rtb_Product2 > 0.0F) {
    u = 1.0F;
  } else if (rtb_Product2 == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Product2;
  }

  /* Switch: '<S78>/Switch' incorporates:
   *  Constant: '<S78>/Constant'
   *  Gain: '<S83>/Gain'
   *  Logic: '<S83>/AND'
   *  RelationalOperator: '<S83>/Equal'
   *  RelationalOperator: '<S83>/NotEqual'
   *  Signum: '<S83>/SignPreIntegrator'
   *  Signum: '<S83>/SignPreSat'
   */
  if ((0.0F * rtb_Sum2 != rtb_Sum1) && (rtb_Sum_l_0 == u)) {
    rtb_Switch_o4 = 0.0F;
  } else {
    rtb_Switch_o4 = rtb_Product2;
  }

  /* End of Switch: '<S78>/Switch' */

  /* DeadZone: '<S84>/DeadZone' */
  if (rtb_Sum_l > StructPointer->CtrlParamPV.ConstQPIUpperSat) {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamPV.ConstQPIUpperSat;
  } else if (rtb_Sum_l >= StructPointer->CtrlParamPV.ConstQPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_l - StructPointer->CtrlParamPV.ConstQPILowerSat;
  }

  /* End of DeadZone: '<S84>/DeadZone' */

  /* Gain: '<S79>/Integral Gain' */
  rtb_DeadZone_d = StructPointer->CtrlParamPV.ConstQPIIntegral * rtb_DeadZone_d;

  /* Signum: '<S84>/SignPreSat' */
  if (rtb_Sum_l < 0.0F) {
    rtb_Sum_l_0 = -1.0F;
  } else if (rtb_Sum_l > 0.0F) {
    rtb_Sum_l_0 = 1.0F;
  } else if (rtb_Sum_l == 0.0F) {
    rtb_Sum_l_0 = 0.0F;
  } else {
    rtb_Sum_l_0 = rtb_Sum_l;
  }

  /* Signum: '<S84>/SignPreIntegrator' */
  if (rtb_DeadZone_d < 0.0F) {
    u = -1.0F;
  } else if (rtb_DeadZone_d > 0.0F) {
    u = 1.0F;
  } else if (rtb_DeadZone_d == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_DeadZone_d;
  }

  /* Switch: '<S79>/Switch' incorporates:
   *  Constant: '<S79>/Constant'
   *  Gain: '<S84>/Gain'
   *  Logic: '<S84>/AND'
   *  RelationalOperator: '<S84>/Equal'
   *  RelationalOperator: '<S84>/NotEqual'
   *  Signum: '<S84>/SignPreIntegrator'
   *  Signum: '<S84>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_l != rtb_Sum1) && (rtb_Sum_l_0 == u)) {
    rtb_Switch_o2 = 0.0F;
  } else {
    rtb_Switch_o2 = rtb_DeadZone_d;
  }

  /* End of Switch: '<S79>/Switch' */

  /* DeadZone: '<S85>/DeadZone' */
  if (rtb_Sum_e > StructPointer->CtrlParamPV.AVCInnerPIUpperSat) {
    rtb_Sum1 = rtb_Sum_e - StructPointer->CtrlParamPV.AVCInnerPIUpperSat;
  } else if (rtb_Sum_e >= StructPointer->CtrlParamPV.AVCInnerPILowerSat) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Sum_e - StructPointer->CtrlParamPV.AVCInnerPILowerSat;
  }

  /* End of DeadZone: '<S85>/DeadZone' */

  /* Gain: '<S80>/Integral Gain' */
  rtb_Cp = StructPointer->CtrlParamPV.AVCInnerPIIntegral * rtb_Cp;

  /* Signum: '<S85>/SignPreSat' */
  if (rtb_Sum_e < 0.0F) {
    u = -1.0F;
  } else if (rtb_Sum_e > 0.0F) {
    u = 1.0F;
  } else if (rtb_Sum_e == 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Sum_e;
  }

  /* Signum: '<S85>/SignPreIntegrator' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Cp == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Switch: '<S80>/Switch' incorporates:
   *  Constant: '<S80>/Constant'
   *  Gain: '<S85>/Gain'
   *  Logic: '<S85>/AND'
   *  RelationalOperator: '<S85>/Equal'
   *  RelationalOperator: '<S85>/NotEqual'
   *  Signum: '<S85>/SignPreIntegrator'
   *  Signum: '<S85>/SignPreSat'
   */
  if ((0.0F * rtb_Sum_e != rtb_Sum1) && (u == rtb_Cp_0)) {
    rtb_Switch_o0 = 0.0F;
  } else {
    rtb_Switch_o0 = rtb_Cp;
  }

  /* End of Switch: '<S80>/Switch' */

  /* Sum: '<S86>/Sum' incorporates:
   *  Constant: '<S86>/wref1'
   */
  rtb_Sum1 = rtb_DiscreteTimeIntegrator2 - 1.25F;

  /* Sum: '<S90>/Sum' incorporates:
   *  DiscreteIntegrator: '<S90>/Integrator'
   *  Gain: '<S90>/Proportional Gain'
   */
  rtb_Product2 = 150.0F * rtb_Sum1 + MGCCode_DWork.Integrator_DSTATE_i;

  /* Sum: '<S91>/Sum' incorporates:
   *  DiscreteIntegrator: '<S91>/Integrator'
   *  Gain: '<S91>/Proportional Gain'
   */
  rtb_Cp = 3.0F * MGCCode_ConstB.Sum2 + MGCCode_DWork.Integrator_DSTATE_lh;

  /* Saturate: '<S90>/Saturation' */
  if (rtb_Product2 >= 27.0F) {
    u = 27.0F;
  } else if (rtb_Product2 <= 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Product2;
  }

  /* Saturate: '<S86>/0-pitch_max' incorporates:
   *  Saturate: '<S90>/Saturation'
   */
  if (u >= 27.0F) {
    u = 27.0F;
  } else {
    if (u <= 0.0F) {
      u = 0.0F;
    }
  }

  /* Saturate: '<S91>/Saturation' */
  if (rtb_Cp >= 27.0F) {
    rtb_Cp_0 = 27.0F;
  } else if (rtb_Cp <= 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Cp;
  }

  /* Sum: '<S86>/Sum3' incorporates:
   *  Saturate: '<S86>/0-pitch_max'
   *  Saturate: '<S90>/Saturation'
   *  Saturate: '<S91>/Saturation'
   */
  u += rtb_Cp_0;

  /* Saturate: '<S86>/0-pitch_max ' */
  if (u >= 30.0F) {
    rtb_pitch_max_g = 30.0F;
  } else if (u <= 0.0F) {
    rtb_pitch_max_g = 0.0F;
  } else {
    rtb_pitch_max_g = u;
  }

  /* End of Saturate: '<S86>/0-pitch_max ' */

  /* Gain: '<S90>/Integral Gain' */
  rtb_Sum1 *= 50.0F;

  /* DeadZone: '<S93>/DeadZone' */
  if (rtb_Product2 > 27.0F) {
    u = rtb_Product2 - 27.0F;
  } else if (rtb_Product2 >= 0.0F) {
    u = 0.0F;
  } else {
    u = rtb_Product2;
  }

  /* End of DeadZone: '<S93>/DeadZone' */

  /* Signum: '<S93>/SignPreSat' */
  if (rtb_Product2 < 0.0F) {
    rtb_Sum_ky_0 = -1.0F;
  } else if (rtb_Product2 > 0.0F) {
    rtb_Sum_ky_0 = 1.0F;
  } else if (rtb_Product2 == 0.0F) {
    rtb_Sum_ky_0 = 0.0F;
  } else {
    rtb_Sum_ky_0 = rtb_Product2;
  }

  /* Signum: '<S93>/SignPreIntegrator' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* Switch: '<S90>/Switch' incorporates:
   *  Constant: '<S90>/Constant'
   *  Gain: '<S93>/Gain'
   *  Logic: '<S93>/AND'
   *  RelationalOperator: '<S93>/Equal'
   *  RelationalOperator: '<S93>/NotEqual'
   *  Signum: '<S93>/SignPreIntegrator'
   *  Signum: '<S93>/SignPreSat'
   */
  if ((0.0F * rtb_Product2 != u) && (rtb_Sum_ky_0 == rtb_Cp_0)) {
    rtb_Switch_br = 0.0F;
  } else {
    rtb_Switch_br = rtb_Sum1;
  }

  /* End of Switch: '<S90>/Switch' */

  /* DeadZone: '<S94>/DeadZone' */
  if (rtb_Cp > 27.0F) {
    rtb_Sum1 = rtb_Cp - 27.0F;
  } else if (rtb_Cp >= 0.0F) {
    rtb_Sum1 = 0.0F;
  } else {
    rtb_Sum1 = rtb_Cp;
  }

  /* End of DeadZone: '<S94>/DeadZone' */

  /* RelationalOperator: '<S94>/NotEqual' incorporates:
   *  Gain: '<S94>/Gain'
   */
  rtb_NotEqual_h = (0.0F * rtb_Cp != rtb_Sum1);

  /* Gain: '<S91>/Integral Gain' */
  rtb_Sum1 = 30.0F * MGCCode_ConstB.Sum2;

  /* Signum: '<S94>/SignPreSat' */
  if (rtb_Cp < 0.0F) {
    rtb_Cp = -1.0F;
  } else if (rtb_Cp > 0.0F) {
    rtb_Cp = 1.0F;
  } else {
    if (rtb_Cp == 0.0F) {
      rtb_Cp = 0.0F;
    }
  }

  /* Signum: '<S94>/SignPreIntegrator' */
  if (rtb_Sum1 < 0.0F) {
    rtb_Cp_0 = -1.0F;
  } else if (rtb_Sum1 > 0.0F) {
    rtb_Cp_0 = 1.0F;
  } else if (rtb_Sum1 == 0.0F) {
    rtb_Cp_0 = 0.0F;
  } else {
    rtb_Cp_0 = rtb_Sum1;
  }

  /* Switch: '<S91>/Switch' incorporates:
   *  Constant: '<S91>/Constant'
   *  Logic: '<S94>/AND'
   *  RelationalOperator: '<S94>/Equal'
   *  Signum: '<S94>/SignPreIntegrator'
   *  Signum: '<S94>/SignPreSat'
   */
  if (rtb_NotEqual_h && (rtb_Cp == rtb_Cp_0)) {
    rtb_Switch_h2 = 0.0F;
  } else {
    rtb_Switch_h2 = rtb_Sum1;
  }

  /* End of Switch: '<S91>/Switch' */

  /* DiscreteStateSpace: '<S92>/Discrete State-Space' */
  {
    rtb_Sum1 = 0.048780486F*MGCCode_DWork.DiscreteStateSpace_DSTATE;
    rtb_Sum1 += 0.024390243F*rtb_pitch_max_g;
  }

  /* Saturate: '<S87>/Avoid div. by zero ' incorporates:
   *  UnitDelay: '<S10>/Unit Delay3'
   */
  if (MGCCode_DWork.UnitDelay3_DSTATE >= 0.666666687F) {
    rtb_Product2 = MGCCode_DWork.UnitDelay3_DSTATE;
  } else {
    rtb_Product2 = 0.666666687F;
  }

  /* End of Saturate: '<S87>/Avoid div. by zero ' */

  /* Fcn: '<S87>/Fcn1' */
  rtb_Cp = 57.5958633F * rtb_Product2 / MGCCode_ConstB.Avoiddivbyzero;

  /* Fcn: '<S87>/Fcn2' */
  rtb_Cp = (((1.0F / ((2.5F + rtb_Sum1) * 0.08F + rtb_Cp) - 0.035F /
              (rt_powf_snf(2.5F + rtb_Sum1, 3.0F) + 1.0F)) * 116.0F + (-5.0F -
              (2.5F + rtb_Sum1) * 0.4F)) / (real32_T)exp((1.0F / ((2.5F +
    rtb_Sum1) * 0.08F + rtb_Cp) - 0.035F / (rt_powf_snf(2.5F + rtb_Sum1, 3.0F) +
    1.0F)) * 21.0F) + 0.00912F * rtb_Cp) * 0.645F;

  /* Fcn: '<S87>/K2*Cp*wind^3 ' */
  rtb_Sum1 = 3010.50854F * rt_powf_snf(MGCCode_ConstB.Avoiddivbyzero, 3.0F) *
    rtb_Cp;

  /* Product: '<S87>/Product2' incorporates:
   *  Gain: '<S87>/->pu'
   */
  rtb_Product2 = 6.66666665E-7F * rtb_Sum1 / rtb_Product2;

  /* Gain: '<S88>/1_2H_WT' incorporates:
   *  Sum: '<S88>/Sum'
   *  UnitDelay: '<S88>/Unit Delay2'
   */
  rtb__2H_WT = (rtb_Product2 - MGCCode_DWork.UnitDelay2_DSTATE_lp) *
    0.150387153F;

  /* DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' incorporates:
   *  Gain: '<S88>/Stiffness1'
   */
  if (MGCCode_DWork.DiscreteTimeIntegrator1_IC_LOAD != 0) {
    MGCCode_DWork.DiscreteTimeIntegrator1_DSTATE = 1.61970758F * rtb_Product2;
  }

  rtb_Sum1 = MGCCode_DWork.DiscreteTimeIntegrator1_DSTATE;

  /* End of DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' */

  /* Gain: '<S88>/Stiffness' */
  rtb_Sum_l = 0.617395401F * rtb_Sum1;

  /* DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator = MGCCode_DWork.DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S88>/Sum1' */
  rtb_Sum1 = rtb_DiscreteTimeIntegrator - rtb_DiscreteTimeIntegrator2;

  /* Sum: '<S88>/Sum2' incorporates:
   *  Gain: '<S88>/Mutual damping'
   *  Gain: '<S88>/wbase2'
   */
  rtb_Sum2_e = 157.079636F * rtb_Sum1 * 0.358080894F + rtb_Sum_l;

  /* Gain: '<S88>/1_2H_WT2' incorporates:
   *  Inport: '<Root>/InDFIG1n'
   *  Sum: '<S88>/Sum3'
   */
  rtb__2H_WT2 = (rtb_Sum2_e - MGCCode_U.InDFIG1n.DFIG1Te) * 0.45031637F;

  /* Gain: '<S88>/wbase1' */
  rtb_wbase1 = 157.079636F * rtb_Sum1;

  /* Outport: '<Root>/OutICEn' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutICEn_at_inport_0'
   *  Product: '<S63>/Product'
   *  Saturate: '<S64>/Saturation'
   */
  MGCCode_Y.OutICEn.ICESPcmd = rtb_DFIG1SPout * rtb_Product;

  /* End of Outputs for SubSystem: '<Root>/MGCC2' */
  MGCCode_Y.OutICEn.ICESQcmd = rtb_Integrator_c;

  /* Outport: '<Root>/OutBatn' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutBatn_at_inport_0'
   */
  MGCCode_Y.OutBatn.BatSPcmd = rtb_BatSPcmd;
  MGCCode_Y.OutBatn.BatSQcmd = rtb_BatSQcmd;
  if (MGCCode_M->Timing.TaskCounters.TID[1] == 0) {
    /* Outport: '<Root>/OutPVn' incorporates:
     *  BusCreator: '<Root>/BusConversion_InsertedFor_OutPVn_at_inport_0'
     */
    MGCCode_Y.OutPVn.PVSPcmd = MGCCode_B.PVSPcmd;
    MGCCode_Y.OutPVn.PVSQcmd = MGCCode_B.PVSQcmd;
  }

  /* Outport: '<Root>/OutDFIG1n' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutDFIG1n_at_inport_0'
   */
  MGCCode_Y.OutDFIG1n.DFIG1SPcmd = rtb_Sum_ky;
  MGCCode_Y.OutDFIG1n.DFIG1SQcmd = rtb_Add4;

  /* Outport: '<Root>/OutDFIG2n' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_OutDFIG2n_at_inport_0'
   */
  MGCCode_Y.OutDFIG2n.DFIG1SPcmd = rtb_Sum_ky;
  MGCCode_Y.OutDFIG2n.DFIG1SQcmd = rtb_Add4;

  /* Outport: '<Root>/Observen' incorporates:
   *  BusCreator: '<Root>/BusConversion_InsertedFor_Observen_at_inport_0'
   */
  MGCCode_Y.Observen.AGCref = rtb_AGCref;
  MGCCode_Y.Observen.AVCref = rtb_AVCref;
  MGCCode_Y.Observen.ICEPout = rtb_Switch1;
  MGCCode_Y.Observen.ICEQout = rtb_Sum5;
  MGCCode_Y.Observen.BatPout = rtb_Divide5_l;
  MGCCode_Y.Observen.BatQout = rtb_Divide7_l;
  MGCCode_Y.Observen.PVPout = rtb_Product_l;
  MGCCode_Y.Observen.PVQout = rtb_Sum_p;
  MGCCode_Y.Observen.DFIG1Pout = rtb_Divide2_g;
  MGCCode_Y.Observen.DFIG1Qout = rtb_Divide7_n;
  MGCCode_Y.Observen.Omegagen = rtb_PoleYk1UkZeroUk1;

  /* Outport: '<Root>/Param' incorporates:
   *  Constant: '<S1>/Constant'
   */
  MGCCode_Y.Param = StructPointer->CtrlParamICE.AVCInnerPIGain;

  /* Outport: '<Root>/LineP' */
  MGCCode_Y.LineP = rtb_LineP_d;

  /* Outport: '<Root>/LineQ' */
  MGCCode_Y.LineQ = rtb_LineQ_b;
  if (MGCCode_M->Timing.TaskCounters.TID[1] == 0) {
    /* BusSelector: '<Root>/BusConversion_InsertedFor_InEMSRootn_at_outport_0' incorporates:
     *  Inport: '<Root>/InEMSRootn'
     */
    rtb_SystemModen = MGCCode_U.InEMSRootn.SystemModen;
    rtb_ICEMode = MGCCode_U.InEMSRootn.ICEMode;
    rtb_BatMode = MGCCode_U.InEMSRootn.BatMode;
    rtb_PVMode = MGCCode_U.InEMSRootn.PVMode;
    rtb_DFIG1Mode = MGCCode_U.InEMSRootn.DFIG1Mode;
    rtb_DFIG2Mode = MGCCode_U.InEMSRootn.DFIG2Mode;

    /* Update for Atomic SubSystem: '<Root>/MGCC2' */
    /* Update for RateTransition: '<S1>/Rate Transition1' */
    MGCCode_DWork.RateTransition1_1_Buffer0 = rtb_SystemModen;

    /* Update for RateTransition: '<S1>/Rate Transition1' */
    MGCCode_DWork.RateTransition1_2_Buffer0 = rtb_ICEMode;

    /* Update for RateTransition: '<S1>/Rate Transition1' */
    MGCCode_DWork.RateTransition1_3_Buffer0 = rtb_BatMode;

    /* Update for RateTransition: '<S1>/Rate Transition1' */
    MGCCode_DWork.RateTransition1_4_Buffer0 = rtb_PVMode;

    /* Update for RateTransition: '<S1>/Rate Transition1' */
    MGCCode_DWork.RateTransition1_5_Buffer0 = rtb_DFIG1Mode;

    /* Update for RateTransition: '<S1>/Rate Transition1' */
    MGCCode_DWork.RateTransition1_6_Buffer0 = rtb_DFIG2Mode;

    /* End of Update for SubSystem: '<Root>/MGCC2' */
  }

  /* Update for Atomic SubSystem: '<Root>/MGCC2' */
  /* Update for UnitDelay: '<S42>/Unit Delay' */
  MGCCode_DWork.UnitDelay_DSTATE = rtb_DFIGR2PSeamless1stOrder;

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator2' */
  MGCCode_DWork.DiscreteTimeIntegrator2_DSTATE += 0.05F * rtb__2H_WT2;

  /* Update for UnitDelay: '<S89>/Delay Input' */
  MGCCode_DWork.DelayInput_DSTATE = rtb_DiscreteTimeIntegrator2;

  /* Update for UnitDelay: '<S89>/Delay Output' */
  MGCCode_DWork.DelayOutput_DSTATE = rtb_PoleYk1UkZeroUk1;

  /* Update for DiscreteIntegrator: '<S43>/Integrator' */
  MGCCode_DWork.Integrator_DSTATE += 0.05F * rtb_Switch_kd;

  /* Update for UnitDelay: '<S42>/Unit Delay1' */
  MGCCode_DWork.UnitDelay1_DSTATE = rtb_DFIGR2PSeamless1stOrder1;

  /* Update for UnitDelay: '<S2>/Unit Delay1' */
  MGCCode_DWork.UnitDelay1_DSTATE_n = rtb_Saturation2;

  /* Update for DiscreteIntegrator: '<S12>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING = 0U;
  MGCCode_DWork.Integrator_DSTATE_d += 0.05F * rtb_Switch;
  if (rtb_AGC > 0) {
    MGCCode_DWork.Integrator_PrevResetState = 1;
  } else if (rtb_AGC < 0) {
    MGCCode_DWork.Integrator_PrevResetState = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S12>/Integrator' */

  /* Update for DiscreteIntegrator: '<S13>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_l = 0U;
  MGCCode_DWork.Integrator_DSTATE_g += 0.05F * rtb_Switch_c;
  if (rtb_AGC > 0) {
    MGCCode_DWork.Integrator_PrevResetState_p = 1;
  } else if (rtb_AGC < 0) {
    MGCCode_DWork.Integrator_PrevResetState_p = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_p = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S13>/Integrator' */

  /* Update for UnitDelay: '<S2>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE = rtb_Saturation3;

  /* Update for DiscreteIntegrator: '<S14>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_i = 0U;
  MGCCode_DWork.Integrator_DSTATE_j += 0.05F * rtb_Switch_b;
  if (rtb_AVC > 0) {
    MGCCode_DWork.Integrator_PrevResetState_i = 1;
  } else if (rtb_AVC < 0) {
    MGCCode_DWork.Integrator_PrevResetState_i = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_i = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S14>/Integrator' */

  /* Update for DiscreteIntegrator: '<S15>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_b = 0U;
  MGCCode_DWork.Integrator_DSTATE_jw += 0.05F * rtb_Switch_j;
  if (rtb_AVC > 0) {
    MGCCode_DWork.Integrator_PrevResetState_k = 1;
  } else if (rtb_AVC < 0) {
    MGCCode_DWork.Integrator_PrevResetState_k = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_k = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S15>/Integrator' */
  if (MGCCode_M->Timing.TaskCounters.TID[2] == 0) {
    /* Update for DiscreteIntegrator: '<S16>/Integrator' */
    MGCCode_DWork.Integrator_IC_LOADING_p = 0U;
    MGCCode_DWork.Integrator_DSTATE_l += 0.5F * rtb_Switch_g;
    if (0.0F > 0.0F) {
      MGCCode_DWork.Integrator_PrevResetState_b = 1;
    } else if (0.0F < 0.0F) {
      MGCCode_DWork.Integrator_PrevResetState_b = -1;
    } else if (0.0F == 0.0F) {
      MGCCode_DWork.Integrator_PrevResetState_b = 0;
    } else {
      MGCCode_DWork.Integrator_PrevResetState_b = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S16>/Integrator' */

    /* Update for DiscreteIntegrator: '<S17>/Integrator' */
    MGCCode_DWork.Integrator_IC_LOADING_m = 0U;
    MGCCode_DWork.Integrator_DSTATE_g5 += 0.5F * rtb_Switch_p;
    if (0.0F > 0.0F) {
      MGCCode_DWork.Integrator_PrevResetState_c = 1;
    } else if (0.0F < 0.0F) {
      MGCCode_DWork.Integrator_PrevResetState_c = -1;
    } else if (0.0F == 0.0F) {
      MGCCode_DWork.Integrator_PrevResetState_c = 0;
    } else {
      MGCCode_DWork.Integrator_PrevResetState_c = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S17>/Integrator' */
  }

  /* Update for UnitDelay: '<S27>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE_l = rtb_Switch_h;

  /* Update for DiscreteIntegrator: '<S29>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_a = 0U;
  MGCCode_DWork.Integrator_DSTATE_l5 += 0.05F * rtb_Switch_ju;
  if (MGCCode_B.sf_ModeSelect.PCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_l = 1;
  } else if (MGCCode_B.sf_ModeSelect.PCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_l = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_l = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S29>/Integrator' */

  /* Update for DiscreteIntegrator: '<S30>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_d = 0U;
  MGCCode_DWork.Integrator_DSTATE_h += 0.05F * rtb_Switch_bm;
  if (MGCCode_B.sf_ModeSelect.PCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_e = 1;
  } else if (MGCCode_B.sf_ModeSelect.PCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_e = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_e = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S30>/Integrator' */

  /* Update for UnitDelay: '<S27>/Unit Delay4' */
  MGCCode_DWork.UnitDelay4_DSTATE = rtb_Switch2;

  /* Update for DiscreteIntegrator: '<S32>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_e = 0U;
  MGCCode_DWork.Integrator_DSTATE_a += 0.05F * rtb_Switch_jt;
  if (MGCCode_B.sf_ModeSelect.QCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_j = 1;
  } else if (MGCCode_B.sf_ModeSelect.QCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_j = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_j = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S32>/Integrator' */

  /* Update for DiscreteIntegrator: '<S31>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_mx = 0U;
  MGCCode_DWork.Integrator_DSTATE_p += 0.05F * rtb_Switch_k;
  if (MGCCode_B.sf_ModeSelect.QCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_jr = 1;
  } else if (MGCCode_B.sf_ModeSelect.QCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_jr = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_jr = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S31>/Integrator' */

  /* Update for DiscreteIntegrator: '<S45>/Integrator' */
  MGCCode_DWork.Integrator_DSTATE_aa += 0.05F * rtb_Switch_hg;
  if (rtb_DFIGR2PRelay > 0.0F) {
    MGCCode_DWork.Integrator_PrevResetState_e3 = 1;
  } else if (rtb_DFIGR2PRelay < 0.0F) {
    MGCCode_DWork.Integrator_PrevResetState_e3 = -1;
  } else if (rtb_DFIGR2PRelay == 0.0F) {
    MGCCode_DWork.Integrator_PrevResetState_e3 = 0;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_e3 = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S45>/Integrator' */

  /* Update for DiscreteFilter: '<S42>/DFIGR2PSeamless1stOrder' */
  MGCCode_DWork.DFIGR2PSeamless1stOrder_states = DFIGR2PSeamless1stOrder_tmp;

  /* Update for DiscreteIntegrator: '<S44>/Integrator' */
  MGCCode_DWork.Integrator_DSTATE_k += 0.05F * rtb_Switch_e;
  if (rtb_DFIGR2PRelay > 0.0F) {
    MGCCode_DWork.Integrator_PrevResetState_ix = 1;
  } else if (rtb_DFIGR2PRelay < 0.0F) {
    MGCCode_DWork.Integrator_PrevResetState_ix = -1;
  } else if (rtb_DFIGR2PRelay == 0.0F) {
    MGCCode_DWork.Integrator_PrevResetState_ix = 0;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_ix = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S44>/Integrator' */

  /* Update for DiscreteFilter: '<S42>/DFIGR2PSeamless1stOrder1' */
  MGCCode_DWork.DFIGR2PSeamless1stOrder1_states = DFIGR2PSeamless1stOrder1_tmp;

  /* Update for UnitDelay: '<S41>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE_c = rtb_Switch_pt;

  /* Update for DiscreteIntegrator: '<S49>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_h = 0U;
  MGCCode_DWork.Integrator_DSTATE_d1 += 0.05F * rtb_Switch_gl;
  if (rtb_PCtrl_i > 0) {
    MGCCode_DWork.Integrator_PrevResetState_ja = 1;
  } else if (rtb_PCtrl_i < 0) {
    MGCCode_DWork.Integrator_PrevResetState_ja = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_ja = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S49>/Integrator' */

  /* Update for DiscreteIntegrator: '<S50>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_c = 0U;
  MGCCode_DWork.Integrator_DSTATE_ps += 0.05F * rtb_Switch_b1;
  if (rtb_PCtrl_i > 0) {
    MGCCode_DWork.Integrator_PrevResetState_cx = 1;
  } else if (rtb_PCtrl_i < 0) {
    MGCCode_DWork.Integrator_PrevResetState_cx = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_cx = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S50>/Integrator' */

  /* Update for UnitDelay: '<S41>/Unit Delay4' */
  MGCCode_DWork.UnitDelay4_DSTATE_c = rtb_Switch2_j;

  /* Update for DiscreteIntegrator: '<S52>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_m1 = 0U;
  MGCCode_DWork.Integrator_DSTATE_b += 0.05F * rtb_Switch_f;
  if (rtb_QCtrl_n > 0) {
    MGCCode_DWork.Integrator_PrevResetState_ks = 1;
  } else if (rtb_QCtrl_n < 0) {
    MGCCode_DWork.Integrator_PrevResetState_ks = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_ks = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S52>/Integrator' */

  /* Update for DiscreteIntegrator: '<S51>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_b4 = 0U;
  MGCCode_DWork.Integrator_DSTATE_gp += 0.05F * rtb_Switch_pb;
  if (rtb_QCtrl_n > 0) {
    MGCCode_DWork.Integrator_PrevResetState_bh = 1;
  } else if (rtb_QCtrl_n < 0) {
    MGCCode_DWork.Integrator_PrevResetState_bh = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_bh = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S51>/Integrator' */

  /* Update for UnitDelay: '<S64>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE_o = rtb_Switch_et;

  /* Update for DiscreteIntegrator: '<S65>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_n = 0U;
  MGCCode_DWork.Integrator_DSTATE_kx += 0.05F * rtb_Switch_l;
  if (MGCCode_B.sf_ModeSelect_k.PCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_g = 1;
  } else if (MGCCode_B.sf_ModeSelect_k.PCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_g = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_g = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S65>/Integrator' */

  /* Update for DiscreteIntegrator: '<S66>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_k = 0U;
  MGCCode_DWork.Integrator_DSTATE_pc += 0.05F * rtb_Switch_n;
  if (MGCCode_B.sf_ModeSelect_k.PCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_d = 1;
  } else if (MGCCode_B.sf_ModeSelect_k.PCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_d = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_d = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S66>/Integrator' */

  /* Update for UnitDelay: '<S64>/Unit Delay4' */
  MGCCode_DWork.UnitDelay4_DSTATE_e = rtb_Switch2_a;

  /* Update for DiscreteIntegrator: '<S68>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_ae = 0U;
  MGCCode_DWork.Integrator_DSTATE_c += 0.05F * rtb_Switch_kw;
  if (MGCCode_B.sf_ModeSelect_k.QCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_gk = 1;
  } else if (MGCCode_B.sf_ModeSelect_k.QCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_gk = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_gk = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S68>/Integrator' */

  /* Update for DiscreteIntegrator: '<S67>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_ak = 0U;
  MGCCode_DWork.Integrator_DSTATE_dq += 0.05F * rtb_Switch_o;
  if (MGCCode_B.sf_ModeSelect_k.QCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_jd = 1;
  } else if (MGCCode_B.sf_ModeSelect_k.QCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_jd = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_jd = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S67>/Integrator' */

  /* Update for UnitDelay: '<S76>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE_b = rtb_Switch_pk;

  /* Update for DiscreteIntegrator: '<S77>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_iv = 0U;
  MGCCode_DWork.Integrator_DSTATE_bp += 0.05F * rtb_Switch_k2;
  if (rtb_PCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_m = 1;
  } else if (rtb_PCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_m = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_m = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S77>/Integrator' */

  /* Update for DiscreteIntegrator: '<S78>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_g = 0U;
  MGCCode_DWork.Integrator_DSTATE_e += 0.05F * rtb_Switch_o4;
  if (rtb_PCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_bp = 1;
  } else if (rtb_PCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_bp = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_bp = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S78>/Integrator' */

  /* Update for UnitDelay: '<S76>/Unit Delay4' */
  MGCCode_DWork.UnitDelay4_DSTATE_d = rtb_Switch2_o;

  /* Update for DiscreteIntegrator: '<S80>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_f = 0U;
  MGCCode_DWork.Integrator_DSTATE_at += 0.05F * rtb_Switch_o0;
  if (rtb_QCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_le = 1;
  } else if (rtb_QCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_le = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_le = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S80>/Integrator' */

  /* Update for DiscreteIntegrator: '<S79>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_ke = 0U;
  MGCCode_DWork.Integrator_DSTATE_o += 0.05F * rtb_Switch_o2;
  if (rtb_QCtrl > 0) {
    MGCCode_DWork.Integrator_PrevResetState_ko = 1;
  } else if (rtb_QCtrl < 0) {
    MGCCode_DWork.Integrator_PrevResetState_ko = -1;
  } else {
    MGCCode_DWork.Integrator_PrevResetState_ko = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S79>/Integrator' */

  /* Update for DiscreteIntegrator: '<S90>/Integrator' */
  MGCCode_DWork.Integrator_DSTATE_i += 0.05F * rtb_Switch_br;

  /* Update for DiscreteIntegrator: '<S91>/Integrator' */
  MGCCode_DWork.Integrator_DSTATE_lh += 0.05F * rtb_Switch_h2;

  /* Update for DiscreteStateSpace: '<S92>/Discrete State-Space' */
  {
    real32_T xnew[1];
    xnew[0] = 0.951219499F*MGCCode_DWork.DiscreteStateSpace_DSTATE;
    xnew[0] += 0.975609779F*rtb_pitch_max_g;
    (void) memcpy(&MGCCode_DWork.DiscreteStateSpace_DSTATE, xnew,
                  sizeof(real32_T)*1);
  }

  /* Update for UnitDelay: '<S10>/Unit Delay3' */
  MGCCode_DWork.UnitDelay3_DSTATE = rtb_DiscreteTimeIntegrator;

  /* Update for UnitDelay: '<S88>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE_lp = rtb_Sum2_e;

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' */
  MGCCode_DWork.DiscreteTimeIntegrator1_IC_LOAD = 0U;
  MGCCode_DWork.DiscreteTimeIntegrator1_DSTATE += 0.05F * rtb_wbase1;

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
  MGCCode_DWork.DiscreteTimeIntegrator_DSTATE += 0.05F * rtb__2H_WT;

  /* End of Update for SubSystem: '<Root>/MGCC2' */
  rate_scheduler();
}

/* Model initialize function */
void MGCCode_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)MGCCode_M, 0,
                sizeof(RT_MODEL_MGCCode));

  /* block I/O */
  (void) memset(((void *) &MGCCode_B), 0,
                sizeof(BlockIO_MGCCode));

  {
    MGCCode_B.BusConversion_InsertedFor_Mic_l = MGCCode_rtZInEMS;
    MGCCode_B.OutEMS_m = MGCCode_rtZOutEMS;
    MGCCode_B.SystemModen = Start;
    MGCCode_B.ICEMode = ConstPQ;
    MGCCode_B.BatMode = ConstPQ;
    MGCCode_B.PVMode = ConstPQ;
    MGCCode_B.DFIG1Mode = ConstPQ;
    MGCCode_B.DFIG2Mode = ConstPQ;
  }

  /* states (dwork) */
  (void) memset((void *)&MGCCode_DWork, 0,
                sizeof(D_Work_MGCCode));

  /* external inputs */
  (void) memset((void *)&MGCCode_U, 0,
                sizeof(ExternalInputs_MGCCode));
  MGCCode_U.InEMSRootn = MGCCode_rtZInEMSRoot;

  /* external outputs */
  (void) memset((void *)&MGCCode_Y, 0,
                sizeof(ExternalOutputs_MGCCode));
  MGCCode_Y.Warningn = None;

  /* Start for Atomic SubSystem: '<Root>/MGCC2' */
  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_B.ICEMode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_B.BatMode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_B.PVMode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_B.DFIG1Mode = ConstPQ;

  /* Start for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_B.DFIG2Mode = ConstPQ;

  /* End of Start for SubSystem: '<Root>/MGCC2' */

  /* InitializeConditions for Atomic SubSystem: '<Root>/MGCC2' */
  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_DWork.RateTransition1_2_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_DWork.RateTransition1_3_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_DWork.RateTransition1_4_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_DWork.RateTransition1_5_Buffer0 = ConstPQ;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  MGCCode_DWork.RateTransition1_6_Buffer0 = ConstPQ;

  /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator2' */
  MGCCode_DWork.DiscreteTimeIntegrator2_DSTATE = MGCCode_ConstB.w2;

  /* InitializeConditions for DiscreteIntegrator: '<S43>/Integrator' */
  MGCCode_DWork.Integrator_DSTATE = 0.7F;

  /* InitializeConditions for Chart: '<S1>/MicrogridModelManager' */
  MGCCode_DWork.is_Logic = MGCCode_IN_NO_ACTIVE_CHILD;
  MGCCode_DWork.is_GridOperation = MGCCode_IN_NO_ACTIVE_CHILD;
  MGCCode_DWork.temporalCounter_i1 = 0U;
  MGCCode_DWork.is_IslandOperation = MGCCode_IN_NO_ACTIVE_CHILD;
  MGCCode_DWork.temporalCounter_i2 = 0U;
  MGCCode_DWork.is_active_c7_MGCCode = 0U;
  MGCCode_DWork.is_c7_MGCCode = MGCCode_IN_NO_ACTIVE_CHILD;
  MGCCode_DWork.IslandCount = 0.0F;
  MGCCode_DWork.IslandFailCount = 0.0F;
  MGCCode_DWork.count = 0.0F;
  MGCCode_DWork.PassiveIslandSignal = 0.0F;
  MGCCode_B.OutEMS_m.SystemModen = Start;
  MGCCode_B.OutEMS_m.ICEMode = ConstPQ;
  MGCCode_B.OutEMS_m.BatMode = ConstPQ;
  MGCCode_B.OutEMS_m.PVMode = ConstPQ;
  MGCCode_B.OutEMS_m.DFIG1Mode = ConstPQ;
  MGCCode_B.OutEMS_m.DFIG2Mode = ConstPQ;
  MGCCode_B.OutSystem_e.LinePref = 0.0F;
  MGCCode_B.OutSystem_e.Fref = 0.0F;
  MGCCode_B.OutSystem_e.LineQref = 0.0F;
  MGCCode_B.OutSystem_e.Vref = 0.0F;

  /* InitializeConditions for Outport: '<Root>/Islandsignal' incorporates:
   *  InitializeConditions for Chart: '<S1>/MicrogridModelManager'
   */
  MGCCode_Y.Islandsignal = FALSE;

  /* InitializeConditions for Outport: '<Root>/Warningn ' incorporates:
   *  InitializeConditions for Chart: '<S1>/MicrogridModelManager'
   */
  MGCCode_Y.Warningn = None;

  /* InitializeConditions for Chart: '<S1>/MicrogridModelManager' */
  MGCCode_Y.EmergencyControl.Pre_LinePowerCmd = 0.0F;
  MGCCode_Y.EmergencyControl.Pre_LoadShedding = 0.0F;
  MGCCode_Y.EmergencyControl.Pre_Pclear = 0.0F;
  MGCCode_Y.EmergencyControl.Pre_CutEn = FALSE;
  MGCCode_Y.EmergencyControl.EC_Pclear = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S12>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING = 1U;
  MGCCode_DWork.Integrator_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_l = 1U;
  MGCCode_DWork.Integrator_PrevResetState_p = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S14>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_i = 1U;
  MGCCode_DWork.Integrator_PrevResetState_i = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S15>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_b = 1U;
  MGCCode_DWork.Integrator_PrevResetState_k = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S16>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_p = 1U;
  MGCCode_DWork.Integrator_PrevResetState_b = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_m = 1U;
  MGCCode_DWork.Integrator_PrevResetState_c = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S29>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_a = 1U;
  MGCCode_DWork.Integrator_PrevResetState_l = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S30>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_d = 1U;
  MGCCode_DWork.Integrator_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_e = 1U;
  MGCCode_DWork.Integrator_PrevResetState_j = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_mx = 1U;
  MGCCode_DWork.Integrator_PrevResetState_jr = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S45>/Integrator' */
  MGCCode_DWork.Integrator_PrevResetState_e3 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S44>/Integrator' */
  MGCCode_DWork.Integrator_PrevResetState_ix = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S49>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_h = 1U;
  MGCCode_DWork.Integrator_PrevResetState_ja = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S50>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_c = 1U;
  MGCCode_DWork.Integrator_PrevResetState_cx = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S52>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_m1 = 1U;
  MGCCode_DWork.Integrator_PrevResetState_ks = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S51>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_b4 = 1U;
  MGCCode_DWork.Integrator_PrevResetState_bh = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S65>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_n = 1U;
  MGCCode_DWork.Integrator_PrevResetState_g = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S66>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_k = 1U;
  MGCCode_DWork.Integrator_PrevResetState_d = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S68>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_ae = 1U;
  MGCCode_DWork.Integrator_PrevResetState_gk = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S67>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_ak = 1U;
  MGCCode_DWork.Integrator_PrevResetState_jd = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S77>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_iv = 1U;
  MGCCode_DWork.Integrator_PrevResetState_m = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S78>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_g = 1U;
  MGCCode_DWork.Integrator_PrevResetState_bp = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S80>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_f = 1U;
  MGCCode_DWork.Integrator_PrevResetState_le = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S79>/Integrator' */
  MGCCode_DWork.Integrator_IC_LOADING_ke = 1U;
  MGCCode_DWork.Integrator_PrevResetState_ko = 2;

  /* InitializeConditions for UnitDelay: '<S88>/Unit Delay2' */
  MGCCode_DWork.UnitDelay2_DSTATE_lp = 1.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' */
  MGCCode_DWork.DiscreteTimeIntegrator1_IC_LOAD = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
  MGCCode_DWork.DiscreteTimeIntegrator_DSTATE = MGCCode_ConstB.w2;

  /* End of InitializeConditions for SubSystem: '<Root>/MGCC2' */
}

/* Model terminate function */
void MGCCode_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
