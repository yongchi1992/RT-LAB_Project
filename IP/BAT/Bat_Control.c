/*
 * File: Bat_Control.c
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

/* Block states (auto storage) */
DW_Bat_Control_T Bat_Control_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Bat_Control_T Bat_Control_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Bat_Control_T Bat_Control_Y;

/* Real-time model */
RT_MODEL_Bat_Control_T Bat_Control_M_;
RT_MODEL_Bat_Control_T *const Bat_Control_M = &Bat_Control_M_;
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
  (Bat_Control_M->Timing.TaskCounters.TID[1])++;
  if ((Bat_Control_M->Timing.TaskCounters.TID[1]) > 3) {/* Sample time: [0.001s, 0.0s] */
    Bat_Control_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void Bat_Control_step(void)
{
  /* local block i/o variables */
  real32_T rtb_Saturation1[2];
  int32_T rtb_SpaceVectorGenerator_o1;
  int32_T rtb_Add;
  int32_T rtb_IQN1toIQN1;
  int32_T rtb_Add2;
  int32_T rtb_IQN1toIQN3;
  boolean_T rtb_UnitDelay;
  real32_T rtb_Vq;
  real32_T rtb_Sum_o;
  real32_T rtb_IntegralGain_b;
  real32_T rtb_Saturation_n;
  real32_T rtb_Sum1;
  real32_T rtb_Saturation5;
  real32_T rtb_P;
  real32_T rtb_Vd_l;
  real32_T rtb_IntegralGain;
  real32_T rtb_Sum;
  real32_T rtb_Saturation;
  real32_T rtb_Vd;
  real32_T rtb_IntegralGain_a;
  real32_T rtb_Sum_j;
  real32_T rtb_Sum1_k;
  real32_T rtb_DeadZone;
  real32_T rtb_coswt2pi3;
  real32_T DiscreteTimeIntegrator;
  real32_T tmp;
  real32_T rtb_Sum_0;

  /* BusSelector: '<Root>/BusConversion_InsertedFor_Vabc_at_outport_0' incorporates:
   *  Inport: '<Root>/Vabc'
   */
  rtb_Vq = Bat_Control_U.Vabc_p.Va;
  rtb_Sum_o = Bat_Control_U.Vabc_p.Vb;
  rtb_IntegralGain_b = Bat_Control_U.Vabc_p.Vc;

  /* Sum: '<S4>/Sum13' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_Iabco_at_outport_0'
   *  BusSelector: '<Root>/BusConversion_InsertedFor_Vabc_at_outport_0'
   *  Constant: '<S1>/Constant18'
   *  Constant: '<S1>/Constant24'
   *  Gain: '<S12>/pu->V'
   *  Inport: '<Root>/Iabco'
   *  Inport: '<Root>/Qref'
   *  Inport: '<Root>/Vabc'
   *  Product: '<S12>/Product3'
   *  Product: '<S4>/Product1'
   *  Sum: '<S12>/Sum'
   *  Sum: '<S12>/Sum1'
   *  Sum: '<S12>/Sum5'
   *  Sum: '<S12>/Sum6'
   *  Sum: '<S4>/Sum12'
   */
  rtb_Saturation5 = (Bat_Control_U.Qref - (((Bat_Control_U.Vabc_p.Vb -
    Bat_Control_U.Vabc_p.Vc) * Bat_Control_U.Iabco_c.Iao +
    (Bat_Control_U.Vabc_p.Vc - Bat_Control_U.Vabc_p.Va) *
    Bat_Control_U.Iabco_c.Ibo) + (Bat_Control_U.Vabc_p.Va -
    Bat_Control_U.Vabc_p.Vb) * Bat_Control_U.Iabco_c.Ico) *
                     Bat_Control_P.puV_Gain) * Bat_Control_P.Constant24_Value +
    Bat_Control_P.Constant18_Value;

  /* Saturate: '<S4>/Saturation5' */
  if (rtb_Saturation5 >= Bat_Control_P.Saturation5_UpperSat) {
    rtb_Saturation5 = Bat_Control_P.Saturation5_UpperSat;
  } else {
    if (rtb_Saturation5 <= Bat_Control_P.Saturation5_LowerSat) {
      rtb_Saturation5 = Bat_Control_P.Saturation5_LowerSat;
    }
  }

  /* End of Saturate: '<S4>/Saturation5' */

  /* UnitDelay: '<S4>/Unit Delay' */
  rtb_UnitDelay = Bat_Control_DW.UnitDelay_DSTATE;

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' incorporates:
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  if (Bat_Control_DW.DiscreteTimeIntegrator2_IC_LOADING != 0U) {
    Bat_Control_DW.DiscreteTimeIntegrator2_DSTATE =
      Bat_Control_DW.UnitDelay1_DSTATE;
  }

  if (rtb_UnitDelay && (Bat_Control_DW.DiscreteTimeIntegrator2_PrevResetState <=
                        0)) {
    Bat_Control_DW.DiscreteTimeIntegrator2_DSTATE =
      Bat_Control_DW.UnitDelay1_DSTATE;
  }

  /* Sum: '<S4>/Sum11' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_Iabco_at_outport_0'
   *  BusSelector: '<Root>/BusConversion_InsertedFor_Vabc_at_outport_0'
   *  Constant: '<S1>/Constant21'
   *  Constant: '<S1>/Constant22'
   *  Gain: '<S12>/pu->V1'
   *  Inport: '<Root>/Iabco'
   *  Inport: '<Root>/Pref'
   *  Inport: '<Root>/Vabc'
   *  Product: '<S12>/Product1'
   *  Product: '<S4>/Product'
   *  Sum: '<S12>/Sum4'
   *  Sum: '<S4>/Sum9'
   */
  DiscreteTimeIntegrator = (Bat_Control_U.Pref - ((Bat_Control_U.Vabc_p.Va *
    Bat_Control_U.Iabco_c.Iao + Bat_Control_U.Vabc_p.Vb *
    Bat_Control_U.Iabco_c.Ibo) + Bat_Control_U.Vabc_p.Vc *
    Bat_Control_U.Iabco_c.Ico) * Bat_Control_P.puV1_Gain) *
    Bat_Control_P.Constant22_Value + Bat_Control_P.Constant21_Value;

  /* Saturate: '<S4>/Saturation6' */
  if (DiscreteTimeIntegrator >= Bat_Control_P.Saturation6_UpperSat) {
    DiscreteTimeIntegrator = Bat_Control_P.Saturation6_UpperSat;
  } else {
    if (DiscreteTimeIntegrator <= Bat_Control_P.Saturation6_LowerSat) {
      DiscreteTimeIntegrator = Bat_Control_P.Saturation6_LowerSat;
    }
  }

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<S4>/m1'
   *  Saturate: '<S4>/Saturation6'
   */
  DiscreteTimeIntegrator = Bat_Control_P.m1_Gain * DiscreteTimeIntegrator *
    Bat_Control_P.DiscreteTimeIntegrator2_gainval +
    Bat_Control_DW.DiscreteTimeIntegrator2_DSTATE;

  /* DataTypeConversion: '<S4>/Data Type Conversion1' */
  rtb_Sum_0 = (real32_T)floor(DiscreteTimeIntegrator * 1.6777216E+7F);
  if (rtIsNaNF(rtb_Sum_0) || rtIsInfF(rtb_Sum_0)) {
    rtb_Sum_0 = 0.0F;
  } else {
    rtb_Sum_0 = (real32_T)fmod(rtb_Sum_0, 4.2949673E+9F);
  }

  rtb_SpaceVectorGenerator_o1 = rtb_Sum_0 < 0.0F ? -(int32_T)(uint32_T)
    -rtb_Sum_0 : (int32_T)(uint32_T)rtb_Sum_0;

  /* End of DataTypeConversion: '<S4>/Data Type Conversion1' */

  /* C28x IQmath Library (stiiqmath_iqtrig) - '<S4>/sin' */
  {
    rtb_Add = _IQ24sin(rtb_SpaceVectorGenerator_o1);
  }

  /* C28x IQmath Library (stiiqmath_iqtrig) - '<S4>/cos ' */
  {
    rtb_IQN1toIQN1 = _IQ24cos(rtb_SpaceVectorGenerator_o1);
  }

  /* DataTypeConversion: '<S4>/Data Type Conversion2' */
  rtb_Saturation1[0] = (real32_T)rtb_Add * 5.96046448E-8F;
  rtb_Saturation1[1] = (real32_T)rtb_IQN1toIQN1 * 5.96046448E-8F;

  /* Sum: '<S15>/Sum' incorporates:
   *  Constant: '<S15>/K1'
   *  Constant: '<S15>/K2'
   *  Product: '<S15>/Product'
   *  Product: '<S15>/Product1'
   */
  rtb_Saturation_n = (0.0F - rtb_Saturation1[0] * Bat_Control_P.K1_Value) -
    rtb_Saturation1[1] * Bat_Control_P.K2_Value;

  /* Sum: '<S15>/Sum1' incorporates:
   *  Constant: '<S15>/K1'
   *  Constant: '<S15>/K2'
   *  Product: '<S15>/Product2'
   *  Product: '<S15>/Product3'
   */
  rtb_Sum1 = rtb_Saturation1[0] * Bat_Control_P.K2_Value - rtb_Saturation1[1] *
    Bat_Control_P.K1_Value;

  /* Sum: '<S15>/Sum2' */
  rtb_P = (0.0F - rtb_Saturation_n) - rtb_Saturation1[0];

  /* Sum: '<S15>/Sum3' */
  rtb_coswt2pi3 = (0.0F - rtb_Sum1) - rtb_Saturation1[1];

  /* Fcn: '<S14>/Fcn2' */
  rtb_Vd_l = ((rtb_Vq * rtb_Saturation1[0] + rtb_Sum_o * rtb_Saturation_n) +
              rtb_IntegralGain_b * rtb_P) * 0.666667F;

  /* Sum: '<S7>/Sum1' */
  rtb_IntegralGain = rtb_Saturation5 - rtb_Vd_l;

  /* Sum: '<S18>/Sum' incorporates:
   *  DiscreteIntegrator: '<S18>/Integrator'
   *  Gain: '<S18>/Proportional Gain'
   */
  rtb_Sum = Bat_Control_P.ProportionalGain_Gain * rtb_IntegralGain +
    Bat_Control_DW.Integrator_DSTATE;

  /* Saturate: '<S18>/Saturation' */
  if (rtb_Sum >= Bat_Control_P.Saturation_UpperSat) {
    rtb_Saturation = Bat_Control_P.Saturation_UpperSat;
  } else if (rtb_Sum <= Bat_Control_P.Saturation_LowerSat) {
    rtb_Saturation = Bat_Control_P.Saturation_LowerSat;
  } else {
    rtb_Saturation = rtb_Sum;
  }

  /* End of Saturate: '<S18>/Saturation' */

  /* Fcn: '<S16>/Fcn2' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_Iabc_at_outport_0'
   *  Inport: '<Root>/Iabc'
   */
  rtb_Vd = ((Bat_Control_U.Iabc_j.Ia * rtb_Saturation1[0] +
             Bat_Control_U.Iabc_j.Ib * rtb_Saturation_n) +
            Bat_Control_U.Iabc_j.Ic * rtb_P) * 0.666667F;

  /* Sum: '<S3>/Sum' */
  rtb_IntegralGain_a = rtb_Saturation - rtb_Vd;

  /* Sum: '<S8>/Sum' incorporates:
   *  DiscreteIntegrator: '<S8>/Integrator'
   *  Gain: '<S8>/Proportional Gain'
   */
  rtb_Sum_j = Bat_Control_P.ProportionalGain_Gain_b * rtb_IntegralGain_a +
    Bat_Control_DW.Integrator_DSTATE_c;

  /* Saturate: '<S8>/Saturation' */
  if (rtb_Sum_j >= Bat_Control_P.Saturation_UpperSat_e) {
    rtb_Sum1_k = Bat_Control_P.Saturation_UpperSat_e;
  } else if (rtb_Sum_j <= Bat_Control_P.Saturation_LowerSat_d) {
    rtb_Sum1_k = Bat_Control_P.Saturation_LowerSat_d;
  } else {
    rtb_Sum1_k = rtb_Sum_j;
  }

  /* End of Saturate: '<S8>/Saturation' */

  /* Fcn: '<S14>/Fcn1' */
  rtb_Vq = ((rtb_Vq * rtb_Saturation1[1] + rtb_Sum_o * rtb_Sum1) +
            rtb_IntegralGain_b * rtb_coswt2pi3) * 0.666667F;

  /* Sum: '<S7>/Sum2' incorporates:
   *  Constant: '<S7>/Constant7'
   */
  rtb_IntegralGain_b = Bat_Control_P.Constant7_Value - rtb_Vq;

  /* Sum: '<S19>/Sum' incorporates:
   *  DiscreteIntegrator: '<S19>/Integrator'
   *  Gain: '<S19>/Proportional Gain'
   */
  rtb_Sum_o = Bat_Control_P.ProportionalGain_Gain_l * rtb_IntegralGain_b +
    Bat_Control_DW.Integrator_DSTATE_m;

  /* Saturate: '<S19>/Saturation' */
  if (rtb_Sum_o >= Bat_Control_P.Saturation_UpperSat_c) {
    rtb_DeadZone = Bat_Control_P.Saturation_UpperSat_c;
  } else if (rtb_Sum_o <= Bat_Control_P.Saturation_LowerSat_p) {
    rtb_DeadZone = Bat_Control_P.Saturation_LowerSat_p;
  } else {
    rtb_DeadZone = rtb_Sum_o;
  }

  /* End of Saturate: '<S19>/Saturation' */

  /* Fcn: '<S16>/Fcn1' incorporates:
   *  BusSelector: '<Root>/BusConversion_InsertedFor_Iabc_at_outport_0'
   *  Inport: '<Root>/Iabc'
   */
  rtb_Sum1 = ((Bat_Control_U.Iabc_j.Ia * rtb_Saturation1[1] +
               Bat_Control_U.Iabc_j.Ib * rtb_Sum1) + Bat_Control_U.Iabc_j.Ic *
              rtb_coswt2pi3) * 0.666667F;

  /* Sum: '<S3>/Sum3' */
  rtb_P = rtb_DeadZone - rtb_Sum1;

  /* Sum: '<S9>/Sum' incorporates:
   *  DiscreteIntegrator: '<S9>/Integrator'
   *  Gain: '<S9>/Proportional Gain'
   */
  rtb_coswt2pi3 = Bat_Control_P.ProportionalGain_Gain_o * rtb_P +
    Bat_Control_DW.Integrator_DSTATE_g;

  /* Saturate: '<S9>/Saturation' */
  if (rtb_coswt2pi3 >= Bat_Control_P.Saturation_UpperSat_d) {
    rtb_Saturation_n = Bat_Control_P.Saturation_UpperSat_d;
  } else if (rtb_coswt2pi3 <= Bat_Control_P.Saturation_LowerSat_n) {
    rtb_Saturation_n = Bat_Control_P.Saturation_LowerSat_n;
  } else {
    rtb_Saturation_n = rtb_coswt2pi3;
  }

  /* End of Saturate: '<S9>/Saturation' */

  /* Product: '<S13>/Product2' */
  rtb_Sum_0 = rtb_Saturation1[1];

  /* Product: '<S13>/Product3' */
  tmp = rtb_Saturation1[0];

  /* Product: '<S5>/Divide1' incorporates:
   *  Constant: '<S5>/Constant8'
   *  Product: '<S13>/Product'
   *  Product: '<S13>/Product1'
   *  Product: '<S13>/Product2'
   *  Product: '<S13>/Product3'
   *  Sum: '<S13>/Sum1'
   *  Sum: '<S13>/Sum2'
   */
  rtb_Saturation1[0] = (rtb_Sum1_k * rtb_Saturation1[1] - rtb_Saturation_n *
                        rtb_Saturation1[0]) * Bat_Control_P.Constant8_Value;
  rtb_Saturation1[1] = (rtb_Saturation_n * rtb_Sum_0 + rtb_Sum1_k * tmp) *
    Bat_Control_P.Constant8_Value;

  /* Saturate: '<S5>/Saturation1' */
  if (rtb_Saturation1[0] >= Bat_Control_P.Saturation1_UpperSat) {
    rtb_Saturation1[0] = Bat_Control_P.Saturation1_UpperSat;
  } else {
    if (rtb_Saturation1[0] <= Bat_Control_P.Saturation1_LowerSat) {
      rtb_Saturation1[0] = Bat_Control_P.Saturation1_LowerSat;
    }
  }

  if (rtb_Saturation1[1] >= Bat_Control_P.Saturation1_UpperSat) {
    rtb_Saturation1[1] = Bat_Control_P.Saturation1_UpperSat;
  } else {
    if (rtb_Saturation1[1] <= Bat_Control_P.Saturation1_LowerSat) {
      rtb_Saturation1[1] = Bat_Control_P.Saturation1_LowerSat;
    }
  }

  /* End of Saturate: '<S5>/Saturation1' */

  /* C28x IQmath Library (stiiqmath_iq) - '<S5>/Float to IQN' */
  {
    rtb_IQN1toIQN1 = _IQ27 (rtb_Saturation1[0]);
  }

  /* C28x IQmath Library (stiiqmath_iq) - '<S5>/Float to IQN1' */
  {
    rtb_Add = _IQ27 (rtb_Saturation1[1]);
  }

  /* C28x DMC Library (tidmcsvgendq) - '<S5>/Space Vector Generator' */
  {
    int16_T sector;
    int32_T Va, Vb, Vc;
    sector = 0;
    Va = rtb_Add;
    Vb = _IQ27mpy (_IQ27(-0.5),rtb_Add) + _IQ27mpy (_IQ27(0.8660254),
      rtb_IQN1toIQN1);
    Vc = _IQ27mpy (_IQ27(-0.5),rtb_Add) - _IQ27mpy (_IQ27(0.8660254),
      rtb_IQN1toIQN1);
    if (Va > 0)
      sector = 1;
    if (Vb > 0)
      sector = sector + 2;
    if (Vc > 0)
      sector = sector + 4;
    Vb = _IQ27mpy (_IQ27(0.5),rtb_Add) + _IQ27mpy (_IQ27(0.8660254),
      rtb_IQN1toIQN1);
    Vc = _IQ27mpy (_IQ27(0.5),rtb_Add) - _IQ27mpy (_IQ27(0.8660254),
      rtb_IQN1toIQN1);
    if (sector==0) {
      rtb_SpaceVectorGenerator_o1 = _IQ27(0.5);
      rtb_IQN1toIQN3 = _IQ27(0.5);
      rtb_Add2 = _IQ27(0.5);
    } else if (sector==1) {
      rtb_IQN1toIQN3 = _IQ27mpy (_IQ27(0.5), (_IQ27(1) - Vc - Vb));
      rtb_SpaceVectorGenerator_o1 = rtb_IQN1toIQN3 + Vc;
      rtb_Add2 = rtb_SpaceVectorGenerator_o1 + Vb;
    } else if (sector==2) {
      rtb_SpaceVectorGenerator_o1 = _IQ27mpy (_IQ27(0.5), (_IQ27(1) - Vb + Va));
      rtb_Add2 = rtb_SpaceVectorGenerator_o1 + Vb;
      rtb_IQN1toIQN3 = rtb_Add2 - Va;
    } else if (sector==3) {
      rtb_SpaceVectorGenerator_o1 = _IQ27mpy (_IQ27(0.5), (_IQ27(1) + Vc - Va));
      rtb_IQN1toIQN3 = rtb_SpaceVectorGenerator_o1 - Vc;
      rtb_Add2 = rtb_IQN1toIQN3 + Va;
    } else if (sector==4) {
      rtb_Add2 = _IQ27mpy (_IQ27(0.5), (_IQ27(1) + Va - Vc));
      rtb_IQN1toIQN3 = rtb_Add2 - Va;
      rtb_SpaceVectorGenerator_o1 = rtb_IQN1toIQN3 + Vc;
    } else if (sector==5) {
      rtb_IQN1toIQN3 = _IQ27mpy (_IQ27(0.5), (_IQ27(1) - Va + Vb));
      rtb_Add2 = rtb_IQN1toIQN3 + Va;
      rtb_SpaceVectorGenerator_o1 = rtb_Add2 - Vb;
    } else if (sector==6) {
      rtb_Add2 = _IQ27mpy (_IQ27(0.5), (_IQ27(1) + Vb + Vc));
      rtb_SpaceVectorGenerator_o1 = rtb_Add2 - Vb;
      rtb_IQN1toIQN3 = rtb_SpaceVectorGenerator_o1 - Vc;
    }

    rtb_SpaceVectorGenerator_o1 = _IQ27mpy (_IQ27(2),
      (rtb_SpaceVectorGenerator_o1 - _IQ27(0.5)));
    rtb_IQN1toIQN3 = _IQ27mpy (_IQ27(2), (rtb_IQN1toIQN3 - _IQ27(0.5)));
    rtb_Add2 = _IQ27mpy (_IQ27(2), (rtb_Add2 - _IQ27(0.5)));
  }

  /* C28x IQmath Library (stiiqmath_iqntoiq) - '<S5>/IQN1 to IQN2' */
  {
    rtb_IQN1toIQN1 = (long)(rtb_SpaceVectorGenerator_o1 >> 12);
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   */
  rtb_Add = Bat_Control_P.Constant_Value_o + rtb_IQN1toIQN1;

  /* Outport: '<Root>/Ta' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   */
  Bat_Control_Y.Ta = (uint16_T)rtb_Add;

  /* C28x IQmath Library (stiiqmath_iqntoiq) - '<S5>/IQN1 to IQN1' */
  {
    rtb_IQN1toIQN1 = (long)(rtb_IQN1toIQN3 >> 12);
  }

  /* Sum: '<S5>/Add1' incorporates:
   *  Constant: '<S5>/Constant1'
   */
  rtb_IQN1toIQN3 = Bat_Control_P.Constant1_Value_i + rtb_IQN1toIQN1;

  /* Outport: '<Root>/Tb' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   */
  Bat_Control_Y.Tb = (uint16_T)rtb_IQN1toIQN3;

  /* C28x IQmath Library (stiiqmath_iqntoiq) - '<S5>/IQN1 to IQN3' */
  {
    rtb_IQN1toIQN3 = (long)(rtb_Add2 >> 12);
  }

  /* Sum: '<S5>/Add2' incorporates:
   *  Constant: '<S5>/Constant2'
   */
  rtb_Add2 = Bat_Control_P.Constant2_Value + rtb_IQN1toIQN3;

  /* Outport: '<Root>/Tc' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion2'
   */
  Bat_Control_Y.Tc = (uint16_T)rtb_Add2;

  /* Outport: '<Root>/Vdref' */
  Bat_Control_Y.Vdref = rtb_Saturation5;

  /* Outport: '<Root>/Vd' */
  Bat_Control_Y.Vd = rtb_Vd_l;

  /* Outport: '<Root>/Vq' */
  Bat_Control_Y.Vq = rtb_Vq;

  /* Outport: '<Root>/Idref' */
  Bat_Control_Y.Idref = rtb_Saturation;

  /* Outport: '<Root>/Iqref' */
  Bat_Control_Y.Iqref = rtb_DeadZone;

  /* Outport: '<Root>/Id' */
  Bat_Control_Y.Id = rtb_Vd;

  /* Outport: '<Root>/Iq' */
  Bat_Control_Y.Iq = rtb_Sum1;

  /* Gain: '<S8>/Integral Gain' */
  rtb_IntegralGain_a *= Bat_Control_P.IntegralGain_Gain;

  /* Gain: '<S9>/Integral Gain' */
  rtb_P *= Bat_Control_P.IntegralGain_Gain_h;

  /* InitialCondition: '<S4>/IC' */
  if (Bat_Control_DW.IC_FirstOutputTime) {
    Bat_Control_DW.IC_FirstOutputTime = FALSE;

    /* Update for UnitDelay: '<S4>/Unit Delay1' */
    Bat_Control_DW.UnitDelay1_DSTATE = Bat_Control_P.IC_Value;
  } else {
    /* Update for UnitDelay: '<S4>/Unit Delay1' incorporates:
     *  Constant: '<S4>/Constant1'
     *  Sum: '<S4>/Sum1'
     */
    Bat_Control_DW.UnitDelay1_DSTATE = DiscreteTimeIntegrator -
      Bat_Control_P.Constant1_Value;
  }

  /* End of InitialCondition: '<S4>/IC' */

  /* Gain: '<S18>/Integral Gain' */
  rtb_IntegralGain *= Bat_Control_P.IntegralGain_Gain_b;

  /* Gain: '<S19>/Integral Gain' */
  rtb_IntegralGain_b *= Bat_Control_P.IntegralGain_Gain_e;

  /* Update for UnitDelay: '<S4>/Unit Delay' incorporates:
   *  Constant: '<S4>/Constant1'
   *  RelationalOperator: '<S4>/Relational Operator'
   */
  Bat_Control_DW.UnitDelay_DSTATE = (DiscreteTimeIntegrator >=
    Bat_Control_P.Constant1_Value);

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' */
  Bat_Control_DW.DiscreteTimeIntegrator2_IC_LOADING = 0U;
  Bat_Control_DW.DiscreteTimeIntegrator2_DSTATE = DiscreteTimeIntegrator;
  if (rtb_UnitDelay) {
    Bat_Control_DW.DiscreteTimeIntegrator2_PrevResetState = 1;
  } else {
    Bat_Control_DW.DiscreteTimeIntegrator2_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' */

  /* DeadZone: '<S20>/DeadZone' */
  if (rtb_Sum > Bat_Control_P.DeadZone_End_i) {
    DiscreteTimeIntegrator = rtb_Sum - Bat_Control_P.DeadZone_End_i;
  } else if (rtb_Sum >= Bat_Control_P.DeadZone_Start_i) {
    DiscreteTimeIntegrator = 0.0F;
  } else {
    DiscreteTimeIntegrator = rtb_Sum - Bat_Control_P.DeadZone_Start_i;
  }

  /* End of DeadZone: '<S20>/DeadZone' */

  /* Signum: '<S20>/SignPreSat' */
  if (rtb_Sum < 0.0F) {
    rtb_Sum_0 = -1.0F;
  } else if (rtb_Sum > 0.0F) {
    rtb_Sum_0 = 1.0F;
  } else if (rtb_Sum == 0.0F) {
    rtb_Sum_0 = 0.0F;
  } else {
    rtb_Sum_0 = rtb_Sum;
  }

  /* Signum: '<S20>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0F) {
    rtb_Saturation_n = -1.0F;
  } else if (rtb_IntegralGain > 0.0F) {
    rtb_Saturation_n = 1.0F;
  } else if (rtb_IntegralGain == 0.0F) {
    rtb_Saturation_n = 0.0F;
  } else {
    rtb_Saturation_n = rtb_IntegralGain;
  }

  /* Switch: '<S18>/Switch' incorporates:
   *  Constant: '<S18>/Constant'
   *  Gain: '<S20>/Gain'
   *  Logic: '<S20>/AND'
   *  RelationalOperator: '<S20>/Equal'
   *  RelationalOperator: '<S20>/NotEqual'
   *  Signum: '<S20>/SignPreIntegrator'
   *  Signum: '<S20>/SignPreSat'
   */
  if ((Bat_Control_P.Gain_Gain_m * rtb_Sum != DiscreteTimeIntegrator) &&
      (rtb_Sum_0 == rtb_Saturation_n)) {
    rtb_IntegralGain = Bat_Control_P.Constant_Value_a;
  }

  /* End of Switch: '<S18>/Switch' */

  /* Update for DiscreteIntegrator: '<S18>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE += Bat_Control_P.Integrator_gainval *
    rtb_IntegralGain;

  /* DeadZone: '<S10>/DeadZone' */
  if (rtb_Sum_j > Bat_Control_P.DeadZone_End) {
    DiscreteTimeIntegrator = rtb_Sum_j - Bat_Control_P.DeadZone_End;
  } else if (rtb_Sum_j >= Bat_Control_P.DeadZone_Start) {
    DiscreteTimeIntegrator = 0.0F;
  } else {
    DiscreteTimeIntegrator = rtb_Sum_j - Bat_Control_P.DeadZone_Start;
  }

  /* End of DeadZone: '<S10>/DeadZone' */

  /* Signum: '<S10>/SignPreSat' */
  if (rtb_Sum_j < 0.0F) {
    rtb_Sum_0 = -1.0F;
  } else if (rtb_Sum_j > 0.0F) {
    rtb_Sum_0 = 1.0F;
  } else if (rtb_Sum_j == 0.0F) {
    rtb_Sum_0 = 0.0F;
  } else {
    rtb_Sum_0 = rtb_Sum_j;
  }

  /* Signum: '<S10>/SignPreIntegrator' */
  if (rtb_IntegralGain_a < 0.0F) {
    rtb_Saturation_n = -1.0F;
  } else if (rtb_IntegralGain_a > 0.0F) {
    rtb_Saturation_n = 1.0F;
  } else if (rtb_IntegralGain_a == 0.0F) {
    rtb_Saturation_n = 0.0F;
  } else {
    rtb_Saturation_n = rtb_IntegralGain_a;
  }

  /* Switch: '<S8>/Switch' incorporates:
   *  Constant: '<S8>/Constant'
   *  Gain: '<S10>/Gain'
   *  Logic: '<S10>/AND'
   *  RelationalOperator: '<S10>/Equal'
   *  RelationalOperator: '<S10>/NotEqual'
   *  Signum: '<S10>/SignPreIntegrator'
   *  Signum: '<S10>/SignPreSat'
   */
  if ((Bat_Control_P.Gain_Gain * rtb_Sum_j != DiscreteTimeIntegrator) &&
      (rtb_Sum_0 == rtb_Saturation_n)) {
    rtb_IntegralGain_a = Bat_Control_P.Constant_Value;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Update for DiscreteIntegrator: '<S8>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE_c += Bat_Control_P.Integrator_gainval_j *
    rtb_IntegralGain_a;

  /* DeadZone: '<S21>/DeadZone' */
  if (rtb_Sum_o > Bat_Control_P.DeadZone_End_f) {
    DiscreteTimeIntegrator = rtb_Sum_o - Bat_Control_P.DeadZone_End_f;
  } else if (rtb_Sum_o >= Bat_Control_P.DeadZone_Start_b) {
    DiscreteTimeIntegrator = 0.0F;
  } else {
    DiscreteTimeIntegrator = rtb_Sum_o - Bat_Control_P.DeadZone_Start_b;
  }

  /* End of DeadZone: '<S21>/DeadZone' */

  /* Signum: '<S21>/SignPreSat' */
  if (rtb_Sum_o < 0.0F) {
    rtb_Sum_0 = -1.0F;
  } else if (rtb_Sum_o > 0.0F) {
    rtb_Sum_0 = 1.0F;
  } else if (rtb_Sum_o == 0.0F) {
    rtb_Sum_0 = 0.0F;
  } else {
    rtb_Sum_0 = rtb_Sum_o;
  }

  /* Signum: '<S21>/SignPreIntegrator' */
  if (rtb_IntegralGain_b < 0.0F) {
    rtb_Saturation_n = -1.0F;
  } else if (rtb_IntegralGain_b > 0.0F) {
    rtb_Saturation_n = 1.0F;
  } else if (rtb_IntegralGain_b == 0.0F) {
    rtb_Saturation_n = 0.0F;
  } else {
    rtb_Saturation_n = rtb_IntegralGain_b;
  }

  /* Switch: '<S19>/Switch' incorporates:
   *  Constant: '<S19>/Constant'
   *  Gain: '<S21>/Gain'
   *  Logic: '<S21>/AND'
   *  RelationalOperator: '<S21>/Equal'
   *  RelationalOperator: '<S21>/NotEqual'
   *  Signum: '<S21>/SignPreIntegrator'
   *  Signum: '<S21>/SignPreSat'
   */
  if ((Bat_Control_P.Gain_Gain_f * rtb_Sum_o != DiscreteTimeIntegrator) &&
      (rtb_Sum_0 == rtb_Saturation_n)) {
    rtb_IntegralGain_b = Bat_Control_P.Constant_Value_j;
  }

  /* End of Switch: '<S19>/Switch' */

  /* Update for DiscreteIntegrator: '<S19>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE_m += Bat_Control_P.Integrator_gainval_k *
    rtb_IntegralGain_b;

  /* DeadZone: '<S11>/DeadZone' */
  if (rtb_coswt2pi3 > Bat_Control_P.DeadZone_End_o) {
    DiscreteTimeIntegrator = rtb_coswt2pi3 - Bat_Control_P.DeadZone_End_o;
  } else if (rtb_coswt2pi3 >= Bat_Control_P.DeadZone_Start_m) {
    DiscreteTimeIntegrator = 0.0F;
  } else {
    DiscreteTimeIntegrator = rtb_coswt2pi3 - Bat_Control_P.DeadZone_Start_m;
  }

  /* End of DeadZone: '<S11>/DeadZone' */

  /* Signum: '<S11>/SignPreSat' */
  if (rtb_coswt2pi3 < 0.0F) {
    rtb_Sum_0 = -1.0F;
  } else if (rtb_coswt2pi3 > 0.0F) {
    rtb_Sum_0 = 1.0F;
  } else if (rtb_coswt2pi3 == 0.0F) {
    rtb_Sum_0 = 0.0F;
  } else {
    rtb_Sum_0 = rtb_coswt2pi3;
  }

  /* Signum: '<S11>/SignPreIntegrator' */
  if (rtb_P < 0.0F) {
    rtb_Saturation_n = -1.0F;
  } else if (rtb_P > 0.0F) {
    rtb_Saturation_n = 1.0F;
  } else if (rtb_P == 0.0F) {
    rtb_Saturation_n = 0.0F;
  } else {
    rtb_Saturation_n = rtb_P;
  }

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S9>/Constant'
   *  Gain: '<S11>/Gain'
   *  Logic: '<S11>/AND'
   *  RelationalOperator: '<S11>/Equal'
   *  RelationalOperator: '<S11>/NotEqual'
   *  Signum: '<S11>/SignPreIntegrator'
   *  Signum: '<S11>/SignPreSat'
   */
  if ((Bat_Control_P.Gain_Gain_o * rtb_coswt2pi3 != DiscreteTimeIntegrator) &&
      (rtb_Sum_0 == rtb_Saturation_n)) {
    rtb_P = Bat_Control_P.Constant_Value_e;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Update for DiscreteIntegrator: '<S9>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE_g += Bat_Control_P.Integrator_gainval_o *
    rtb_P;
  rate_scheduler();
}

/* Model initialize function */
void Bat_Control_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Bat_Control_M, 0,
                sizeof(RT_MODEL_Bat_Control_T));

  /* states (dwork) */
  (void) memset((void *)&Bat_Control_DW, 0,
                sizeof(DW_Bat_Control_T));

  /* external inputs */
  (void) memset((void *)&Bat_Control_U, 0,
                sizeof(ExtU_Bat_Control_T));

  /* external outputs */
  (void) memset((void *)&Bat_Control_Y, 0,
                sizeof(ExtY_Bat_Control_T));

  /* Start for InitialCondition: '<S4>/IC' */
  Bat_Control_DW.IC_FirstOutputTime = TRUE;

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
  Bat_Control_DW.UnitDelay_DSTATE = Bat_Control_P.UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay1' */
  Bat_Control_DW.UnitDelay1_DSTATE = Bat_Control_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' */
  Bat_Control_DW.DiscreteTimeIntegrator2_IC_LOADING = 1U;
  Bat_Control_DW.DiscreteTimeIntegrator2_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE = Bat_Control_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE_c = Bat_Control_P.Integrator_IC_o;

  /* InitializeConditions for DiscreteIntegrator: '<S19>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE_m = Bat_Control_P.Integrator_IC_k;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Integrator' */
  Bat_Control_DW.Integrator_DSTATE_g = Bat_Control_P.Integrator_IC_b;
}

/* Model terminate function */
void Bat_Control_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
