/*
 * File: Bat_Control.h
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

#ifndef RTW_HEADER_Bat_Control_h_
#define RTW_HEADER_Bat_Control_h_
#ifndef Bat_Control_COMMON_INCLUDES_
# define Bat_Control_COMMON_INCLUDES_
#include <IQmathLib.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#endif                                 /* Bat_Control_COMMON_INCLUDES_ */

#include "Bat_Control_types.h"

#define Vdpp 0.3F
#define VdII 40.0F

#define Vqpp 0.3F
#define VqII 40.0F

#define Idpp 1.5F
#define IdII 10.0F

#define Iqpp 1.5F
#define IqII 10.0F



/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay1_DSTATE;          /* '<S4>/Unit Delay1' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S4>/Discrete-Time Integrator2' */
  real32_T Integrator_DSTATE;          /* '<S18>/Integrator' */
  real32_T Integrator_DSTATE_c;        /* '<S8>/Integrator' */
  real32_T Integrator_DSTATE_m;        /* '<S19>/Integrator' */
  real32_T Integrator_DSTATE_g;        /* '<S9>/Integrator' */
  boolean_T UnitDelay_DSTATE;          /* '<S4>/Unit Delay' */
  int16_T DiscreteTimeIntegrator2_PrevResetState;/* '<S4>/Discrete-Time Integrator2' */
  uint16_T DiscreteTimeIntegrator2_IC_LOADING;/* '<S4>/Discrete-Time Integrator2' */
  boolean_T IC_FirstOutputTime;        /* '<S4>/IC' */
} DW_Bat_Control_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T Pref;                       /* '<Root>/Pref' */
  real32_T Qref;                       /* '<Root>/Qref' */
  Vabc Vabc_p;                         /* '<Root>/Vabc' */
  Iabc Iabc_j;                         /* '<Root>/Iabc' */
  Iabco Iabco_c;                       /* '<Root>/Iabco' */
} ExtU_Bat_Control_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint16_T Ta;                         /* '<Root>/Ta' */
  uint16_T Tb;                         /* '<Root>/Tb' */
  uint16_T Tc;                         /* '<Root>/Tc' */
  real32_T Vdref;                      /* '<Root>/Vdref' */
  real32_T Vd;                         /* '<Root>/Vd' */
  real32_T Vq;                         /* '<Root>/Vq' */
  real32_T Idref;                      /* '<Root>/Idref' */
  real32_T Iqref;                      /* '<Root>/Iqref' */
  real32_T Id;                         /* '<Root>/Id' */
  real32_T Iq;                         /* '<Root>/Iq' */
} ExtY_Bat_Control_T;

/* Parameters (auto storage) */
struct P_Bat_Control_T_ {
  real_T FloattoIQN_P1;                /* Expression: Q_value
                                        * Referenced by: '<S5>/Float to IQN'
                                        */
  real_T FloattoIQN1_P1;               /* Expression: Q_value
                                        * Referenced by: '<S5>/Float to IQN1'
                                        */
  real32_T Constant24_Value;           /* Computed Parameter: Constant24_Value
                                        * Referenced by: '<S1>/Constant24'
                                        */
  real32_T puV_Gain;                   /* Computed Parameter: puV_Gain
                                        * Referenced by: '<S12>/pu->V'
                                        */
  real32_T Constant18_Value;           /* Computed Parameter: Constant18_Value
                                        * Referenced by: '<S1>/Constant18'
                                        */
  real32_T Saturation5_UpperSat;       /* Computed Parameter: Saturation5_UpperSat
                                        * Referenced by: '<S4>/Saturation5'
                                        */
  real32_T Saturation5_LowerSat;       /* Computed Parameter: Saturation5_LowerSat
                                        * Referenced by: '<S4>/Saturation5'
                                        */
  real32_T Constant21_Value;           /* Computed Parameter: Constant21_Value
                                        * Referenced by: '<S1>/Constant21'
                                        */
  real32_T Constant22_Value;           /* Computed Parameter: Constant22_Value
                                        * Referenced by: '<S1>/Constant22'
                                        */
  real32_T puV1_Gain;                  /* Computed Parameter: puV1_Gain
                                        * Referenced by: '<S12>/pu->V1'
                                        */
  real32_T Saturation6_UpperSat;       /* Computed Parameter: Saturation6_UpperSat
                                        * Referenced by: '<S4>/Saturation6'
                                        */
  real32_T Saturation6_LowerSat;       /* Computed Parameter: Saturation6_LowerSat
                                        * Referenced by: '<S4>/Saturation6'
                                        */
  real32_T m1_Gain;                    /* Computed Parameter: m1_Gain
                                        * Referenced by: '<S4>/m1'
                                        */
  real32_T UnitDelay1_InitialCondition;/* Computed Parameter: UnitDelay1_InitialCondition
                                        * Referenced by: '<S4>/Unit Delay1'
                                        */
  real32_T DiscreteTimeIntegrator2_gainval;/* Computed Parameter: DiscreteTimeIntegrator2_gainval
                                            * Referenced by: '<S4>/Discrete-Time Integrator2'
                                            */
  real32_T K1_Value;                   /* Computed Parameter: K1_Value
                                        * Referenced by: '<S15>/K1'
                                        */
  real32_T K2_Value;                   /* Computed Parameter: K2_Value
                                        * Referenced by: '<S15>/K2'
                                        */
  real32_T ProportionalGain_Gain;      /* Expression: P
                                        * Referenced by: '<S18>/Proportional Gain'
                                        */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S18>/Integrator'
                                        */
  real32_T Integrator_IC;              /* Computed Parameter: Integrator_IC
                                        * Referenced by: '<S18>/Integrator'
                                        */
  real32_T Saturation_UpperSat;        /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S18>/Saturation'
                                        */
  real32_T Saturation_LowerSat;        /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S18>/Saturation'
                                        */
  real32_T ProportionalGain_Gain_b;    /* Expression: P
                                        * Referenced by: '<S8>/Proportional Gain'
                                        */
  real32_T Integrator_gainval_j;       /* Computed Parameter: Integrator_gainval_j
                                        * Referenced by: '<S8>/Integrator'
                                        */
  real32_T Integrator_IC_o;            /* Computed Parameter: Integrator_IC_o
                                        * Referenced by: '<S8>/Integrator'
                                        */
  real32_T Saturation_UpperSat_e;      /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real32_T Saturation_LowerSat_d;      /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real32_T Constant7_Value;            /* Computed Parameter: Constant7_Value
                                        * Referenced by: '<S7>/Constant7'
                                        */
  real32_T ProportionalGain_Gain_l;    /* Expression: P
                                        * Referenced by: '<S19>/Proportional Gain'
                                        */
  real32_T Integrator_gainval_k;       /* Computed Parameter: Integrator_gainval_k
                                        * Referenced by: '<S19>/Integrator'
                                        */
  real32_T Integrator_IC_k;            /* Computed Parameter: Integrator_IC_k
                                        * Referenced by: '<S19>/Integrator'
                                        */
  real32_T Saturation_UpperSat_c;      /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S19>/Saturation'
                                        */
  real32_T Saturation_LowerSat_p;      /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S19>/Saturation'
                                        */
  real32_T ProportionalGain_Gain_o;    /* Expression: P
                                        * Referenced by: '<S9>/Proportional Gain'
                                        */
  real32_T Integrator_gainval_o;       /* Computed Parameter: Integrator_gainval_o
                                        * Referenced by: '<S9>/Integrator'
                                        */
  real32_T Integrator_IC_b;            /* Computed Parameter: Integrator_IC_b
                                        * Referenced by: '<S9>/Integrator'
                                        */
  real32_T Saturation_UpperSat_d;      /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S9>/Saturation'
                                        */
  real32_T Saturation_LowerSat_n;      /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S9>/Saturation'
                                        */
  real32_T Constant8_Value;            /* Computed Parameter: Constant8_Value
                                        * Referenced by: '<S5>/Constant8'
                                        */
  real32_T Saturation1_UpperSat;       /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S5>/Saturation1'
                                        */
  real32_T Saturation1_LowerSat;       /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S5>/Saturation1'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S10>/Gain'
                                        */
  real32_T DeadZone_Start;             /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S10>/DeadZone'
                                        */
  real32_T DeadZone_End;               /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S10>/DeadZone'
                                        */
  real32_T IntegralGain_Gain;          /* Expression: I
                                        * Referenced by: '<S8>/Integral Gain'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S8>/Constant'
                                        */
  real32_T Gain_Gain_o;                /* Computed Parameter: Gain_Gain_o
                                        * Referenced by: '<S11>/Gain'
                                        */
  real32_T DeadZone_Start_m;           /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S11>/DeadZone'
                                        */
  real32_T DeadZone_End_o;             /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S11>/DeadZone'
                                        */
  real32_T IntegralGain_Gain_h;        /* Expression: I
                                        * Referenced by: '<S9>/Integral Gain'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S9>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real32_T IC_Value;                   /* Computed Parameter: IC_Value
                                        * Referenced by: '<S4>/IC'
                                        */
  real32_T Gain_Gain_m;                /* Computed Parameter: Gain_Gain_m
                                        * Referenced by: '<S20>/Gain'
                                        */
  real32_T DeadZone_Start_i;           /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S20>/DeadZone'
                                        */
  real32_T DeadZone_End_i;             /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S20>/DeadZone'
                                        */
  real32_T IntegralGain_Gain_b;        /* Expression: I
                                        * Referenced by: '<S18>/Integral Gain'
                                        */
  real32_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S18>/Constant'
                                        */
  real32_T Gain_Gain_f;                /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S21>/Gain'
                                        */
  real32_T DeadZone_Start_b;           /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S21>/DeadZone'
                                        */
  real32_T DeadZone_End_f;             /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S21>/DeadZone'
                                        */
  real32_T IntegralGain_Gain_e;        /* Expression: I
                                        * Referenced by: '<S19>/Integral Gain'
                                        */
  real32_T Constant_Value_j;           /* Computed Parameter: Constant_Value_j
                                        * Referenced by: '<S19>/Constant'
                                        */
  int32_T Constant_Value_o;            /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S5>/Constant'
                                        */
  int32_T Constant1_Value_i;           /* Computed Parameter: Constant1_Value_i
                                        * Referenced by: '<S5>/Constant1'
                                        */
  int32_T Constant2_Value;             /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S5>/Constant2'
                                        */
  boolean_T UnitDelay_InitialCondition;/* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S4>/Unit Delay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Bat_Control_T {
  const char_T *errorStatus;

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
extern P_Bat_Control_T Bat_Control_P;

/* Block states (auto storage) */
extern DW_Bat_Control_T Bat_Control_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Bat_Control_T Bat_Control_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Bat_Control_T Bat_Control_Y;

/* Model entry point functions */
extern void Bat_Control_initialize(void);
extern void Bat_Control_step(void);
extern void Bat_Control_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Bat_Control_T *const Bat_Control_M;

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
 * '<Root>' : 'Bat_Control'
 * '<S1>'   : 'Bat_Control/Control1'
 * '<S2>'   : 'Bat_Control/powergui'
 * '<S3>'   : 'Bat_Control/Control1/Current Voltage'
 * '<S4>'   : 'Bat_Control/Control1/Droop Controllor'
 * '<S5>'   : 'Bat_Control/Control1/PWM'
 * '<S6>'   : 'Bat_Control/Control1/ParkTransformation'
 * '<S7>'   : 'Bat_Control/Control1/Voltage Cotrollor'
 * '<S8>'   : 'Bat_Control/Control1/Current Voltage/PID Controller'
 * '<S9>'   : 'Bat_Control/Control1/Current Voltage/PID Controller1'
 * '<S10>'  : 'Bat_Control/Control1/Current Voltage/PID Controller/Clamping circuit'
 * '<S11>'  : 'Bat_Control/Control1/Current Voltage/PID Controller1/Clamping circuit'
 * '<S12>'  : 'Bat_Control/Control1/Droop Controllor/Subsystem1'
 * '<S13>'  : 'Bat_Control/Control1/PWM/Subsystem'
 * '<S14>'  : 'Bat_Control/Control1/ParkTransformation/Subsystem'
 * '<S15>'  : 'Bat_Control/Control1/ParkTransformation/Subsystem1'
 * '<S16>'  : 'Bat_Control/Control1/ParkTransformation/Subsystem2'
 * '<S17>'  : 'Bat_Control/Control1/ParkTransformation/Subsystem3'
 * '<S18>'  : 'Bat_Control/Control1/Voltage Cotrollor/PID Controller2'
 * '<S19>'  : 'Bat_Control/Control1/Voltage Cotrollor/PID Controller3'
 * '<S20>'  : 'Bat_Control/Control1/Voltage Cotrollor/PID Controller2/Clamping circuit'
 * '<S21>'  : 'Bat_Control/Control1/Voltage Cotrollor/PID Controller3/Clamping circuit'
 */
#endif                                 /* RTW_HEADER_Bat_Control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
