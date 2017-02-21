/*
 * File: MGCCode_Ori_private.h
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

#ifndef RTW_HEADER_MGCCode_Ori_private_h_
#define RTW_HEADER_MGCCode_Ori_private_h_
#include "rtwtypes.h"

/* Includes for objects with custom storage classes. */
#include "ModeSwitch.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C16S16I16L32N16F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C16S16I16L32N16F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

extern void MGCCode_Ori_EnablePI1_Init(real32_T rtu_I,
  rtDW_EnablePI1_MGCCode_Ori *localDW);
extern void MGCCode_Ori_EnablePI1_Start(real32_T rtu_I,
  rtDW_EnablePI1_MGCCode_Ori *localDW);
extern void MGCCode_Ori_EnablePI1_Disable(rtDW_EnablePI1_MGCCode_Ori *localDW);
extern void MGCCode_Ori_EnablePI1(int16_T rtu_0, real32_T rtu_Delata, real32_T
  rtu_RESET, real32_T rtu_I, rtB_EnablePI1_MGCCode_Ori *localB,
  rtDW_EnablePI1_MGCCode_Ori *localDW, real32_T rtp_P, real32_T
  rtp_LowerSaturationLimit, real32_T rtp_UpperSaturationLimit, real32_T rtp_I);
extern void MGCCode_Ori_EnablePI5_Init(real32_T rtu_RESET,
  rtDW_EnablePI5_MGCCode_Ori *localDW);
extern void MGCCode_Ori_EnablePI5_Start(real32_T rtu_RESET,
  rtDW_EnablePI5_MGCCode_Ori *localDW);
extern void MGCCode_Ori_EnablePI5_Disable(rtDW_EnablePI5_MGCCode_Ori *localDW);
extern void MGCCode_Ori_EnablePI5(int16_T rtu_0, real32_T rtu_Delata, real32_T
  rtu_RESET, rtB_EnablePI5_MGCCode_Ori *localB, rtDW_EnablePI5_MGCCode_Ori
  *localDW, real32_T rtp_P, real32_T rtp_LowerSaturationLimit, real32_T
  rtp_UpperSaturationLimit, real32_T rtp_I);
extern void MGCCode_Ori_ModeSelect(SystemMode rtu_SysMode, GenMode
  rtu_GenerationMode, rtB_ModeSelect_MGCCode_Ori *localB);

#endif                                 /* RTW_HEADER_MGCCode_Ori_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
