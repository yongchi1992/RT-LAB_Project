/*
 * File: Bat_Control_types.h
 *
 * Code generated for Simulink model 'Bat_Control'.
 *
 * Model version                  : 1.86
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Sun Feb 08 14:17:02 2015
 *
 * Target selection: idelink_ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Bat_Control_types_h_
#define RTW_HEADER_Bat_Control_types_h_
#include "rtwtypes.h"
#ifndef SS_LONG
#define SS_LONG                        21
#endif

#ifndef SS_ULONG
#define SS_ULONG                       22
#endif

#ifndef _DEFINED_TYPEDEF_FOR_Vabc_
#define _DEFINED_TYPEDEF_FOR_Vabc_

typedef struct {
  real32_T Va;
  real32_T Vb;
  real32_T Vc;
} Vabc;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Iabc_
#define _DEFINED_TYPEDEF_FOR_Iabc_

typedef struct {
  real32_T Ia;
  real32_T Ib;
  real32_T Ic;
} Iabc;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Iabco_
#define _DEFINED_TYPEDEF_FOR_Iabco_

typedef struct {
  real32_T Iao;
  real32_T Ibo;
  real32_T Ico;
} Iabco;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_PARAM_
#define _DEFINED_TYPEDEF_FOR_PARAM_

typedef struct {
  real32_T VdP;
  real32_T VdI;
  real32_T VdUp;
  real32_T VdLow;
  real32_T VqP;
  real32_T VqI;
  real32_T VqUp;
  real32_T VqLow;
  real32_T IdP;
  real32_T IdI;
  real32_T IdUp;
  real32_T IdLow;
  real32_T IqP;
  real32_T IqI;
  real32_T IqUp;
  real32_T IqLow;
} PARAM;

#endif

/* Parameters (auto storage) */
typedef struct P_Bat_Control_T_ P_Bat_Control_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Bat_Control_T RT_MODEL_Bat_Control_T;

#endif                                 /* RTW_HEADER_Bat_Control_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
