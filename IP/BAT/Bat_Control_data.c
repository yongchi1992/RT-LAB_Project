/*
 * File: Bat_Control_data.c
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

#include "Bat_Control.h"
#include "Bat_Control_private.h"

/* Block parameters (auto storage) */
P_Bat_Control_T Bat_Control_P = {
  27.0,                                /* Expression: Q_value
                                        * Referenced by: '<S5>/Float to IQN'
                                        */
  27.0,                                /* Expression: Q_value
                                        * Referenced by: '<S5>/Float to IQN1'
                                        */
  0.1F,                                /* Computed Parameter: Constant24_Value
                                        * Referenced by: '<S1>/Constant24'
                                        */
  0.3849F,                             /* Computed Parameter: puV_Gain
                                        * Referenced by: '<S12>/pu->V'
                                        */
  1.0F,                                /* Computed Parameter: Constant18_Value
                                        * Referenced by: '<S1>/Constant18'
                                        */
  1.1F,                                /* Computed Parameter: Saturation5_UpperSat
                                        * Referenced by: '<S4>/Saturation5'
                                        */
  0.9F,                                /* Computed Parameter: Saturation5_LowerSat
                                        * Referenced by: '<S4>/Saturation5'
                                        */
  50.0F,                               /* Computed Parameter: Constant21_Value
                                        * Referenced by: '<S1>/Constant21'
                                        */
  1.0F,                                /* Computed Parameter: Constant22_Value
                                        * Referenced by: '<S1>/Constant22'
                                        */
  0.66667F,                            /* Computed Parameter: puV1_Gain
                                        * Referenced by: '<S12>/pu->V1'
                                        */
  51.0F,                               /* Computed Parameter: Saturation6_UpperSat
                                        * Referenced by: '<S4>/Saturation6'
                                        */
  49.0F,                               /* Computed Parameter: Saturation6_LowerSat
                                        * Referenced by: '<S4>/Saturation6'
                                        */
  6.28318548F,                         /* Computed Parameter: m1_Gain
                                        * Referenced by: '<S4>/m1'
                                        */
  0.0F,                                /* Computed Parameter: UnitDelay1_InitialCondition
                                        * Referenced by: '<S4>/Unit Delay1'
                                        */
  0.00025F,                            /* Computed Parameter: DiscreteTimeIntegrator2_gainval
                                        * Referenced by: '<S4>/Discrete-Time Integrator2'
                                        */
  0.5F,                                /* Computed Parameter: K1_Value
                                        * Referenced by: '<S15>/K1'
                                        */
  0.866025F,                           /* Computed Parameter: K2_Value
                                        * Referenced by: '<S15>/K2'
                                        */
  0.5F,                                /* Expression: P
                                        * Referenced by: '<S18>/Proportional Gain'
                                        */
  0.00025F,                            /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S18>/Integrator'
                                        */
  0.0F,                                /* Computed Parameter: Integrator_IC
                                        * Referenced by: '<S18>/Integrator'
                                        */
  1.2F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S18>/Saturation'
                                        */
  -1.2F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S18>/Saturation'
                                        */
  0.5F,                                /* Expression: P
                                        * Referenced by: '<S8>/Proportional Gain'
                                        */
  0.00025F,                            /* Computed Parameter: Integrator_gainval_j
                                        * Referenced by: '<S8>/Integrator'
                                        */
  0.0F,                                /* Computed Parameter: Integrator_IC_o
                                        * Referenced by: '<S8>/Integrator'
                                        */
  1.6F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S8>/Saturation'
                                        */
  -1.6F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S8>/Saturation'
                                        */
  0.0F,                                /* Computed Parameter: Constant7_Value
                                        * Referenced by: '<S7>/Constant7'
                                        */
  0.5F,                                /* Expression: P
                                        * Referenced by: '<S19>/Proportional Gain'
                                        */
  0.00025F,                            /* Computed Parameter: Integrator_gainval_k
                                        * Referenced by: '<S19>/Integrator'
                                        */
  0.0F,                                /* Computed Parameter: Integrator_IC_k
                                        * Referenced by: '<S19>/Integrator'
                                        */
  1.2F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S19>/Saturation'
                                        */
  -1.2F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S19>/Saturation'
                                        */
  0.5F,                                /* Expression: P
                                        * Referenced by: '<S9>/Proportional Gain'
                                        */
  0.00025F,                            /* Computed Parameter: Integrator_gainval_o
                                        * Referenced by: '<S9>/Integrator'
                                        */
  0.0F,                                /* Computed Parameter: Integrator_IC_b
                                        * Referenced by: '<S9>/Integrator'
                                        */
  1.3F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S9>/Saturation'
                                        */
  -1.3F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S9>/Saturation'
                                        */
  0.6505F,                             /* Computed Parameter: Constant8_Value
                                        * Referenced by: '<S5>/Constant8'
                                        */
  1.0F,                                /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S5>/Saturation1'
                                        */
  -1.0F,                               /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S5>/Saturation1'
                                        */
  0.0F,                                /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S10>/Gain'
                                        */
  -1.6F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S10>/DeadZone'
                                        */
  1.6F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S10>/DeadZone'
                                        */
  10.0F,                               /* Expression: I
                                        * Referenced by: '<S8>/Integral Gain'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S8>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: Gain_Gain_o
                                        * Referenced by: '<S11>/Gain'
                                        */
  -1.3F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S11>/DeadZone'
                                        */
  1.3F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S11>/DeadZone'
                                        */
  10.0F,                               /* Expression: I
                                        * Referenced by: '<S9>/Integral Gain'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S9>/Constant'
                                        */
  62.831852F,                          /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S4>/Constant1'
                                        */
  6.28318548F,                         /* Computed Parameter: IC_Value
                                        * Referenced by: '<S4>/IC'
                                        */
  0.0F,                                /* Computed Parameter: Gain_Gain_m
                                        * Referenced by: '<S20>/Gain'
                                        */
  -1.2F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S20>/DeadZone'
                                        */
  1.2F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S20>/DeadZone'
                                        */
  25.0F,                               /* Expression: I
                                        * Referenced by: '<S18>/Integral Gain'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S18>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S21>/Gain'
                                        */
  -1.2F,                               /* Expression: LowerSaturationLimit
                                        * Referenced by: '<S21>/DeadZone'
                                        */
  1.2F,                                /* Expression: UpperSaturationLimit
                                        * Referenced by: '<S21>/DeadZone'
                                        */
  25.0F,                               /* Expression: I
                                        * Referenced by: '<S19>/Integral Gain'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value_j
                                        * Referenced by: '<S19>/Constant'
                                        */
  32768,                               /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S5>/Constant'
                                        */
  32768,                               /* Computed Parameter: Constant1_Value_i
                                        * Referenced by: '<S5>/Constant1'
                                        */
  32768,                               /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S5>/Constant2'
                                        */
  0                                    /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S4>/Unit Delay'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
