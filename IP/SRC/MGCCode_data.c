/*
 * File: MGCCode_data.c
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

/* Invariant block signals (auto storage) */
const ConstBlockIO_MGCCode MGCCode_ConstB = {
  1.25F
  ,                                    /* '<S1>/w2' */
  0.0F
  ,                                    /* '<S86>/0-inf' */
  -1.0F
  ,                                    /* '<S86>/Sum2' */
  11.0F
  /* '<S87>/Avoid div. by zero' */
};

/* Block parameters (auto storage) */
Parameters_MGCCode MGCCode_P = {
  {
    100000.0F,
    100000.0F,
    1.0F,
    1.0F,
    250000.0F,
    1.0e+6F,
    250000.0F,
    1.5e+6F,
    1.0e+6F,
    200000.0F,
    0.8F,
    0.8F,
    1.0F,
    0.4F,
    1.0F,
    0.4F,
    1.0F,
    250000.0F,
    0.4F,
    0.4F,
    0.2F,
    1.1F,
    0.8F,
    0.75F,
    0.75F
  }                                    /* Variable: Base
                                        * Referenced by:
                                        *   '<S1>/MicrogridModelManager'
                                        *   '<S2>/Constant'
                                        *   '<S2>/Constant1'
                                        *   '<S2>/Constant2'
                                        *   '<S2>/Constant3'
                                        *   '<S2>/Constant4'
                                        *   '<S2>/Constant5'
                                        *   '<S2>/Constant6'
                                        *   '<S2>/Constant7'
                                        *   '<S2>/Constant8'
                                        *   '<S2>/Constant9'
                                        *   '<S4>/Gain'
                                        *   '<S7>/Constant'
                                        *   '<S7>/Constant1'
                                        *   '<S25>/Constant1'
                                        *   '<S25>/Constant6'
                                        *   '<S25>/Constant9'
                                        *   '<S38>/Constant6'
                                        *   '<S62>/Constant1'
                                        *   '<S62>/Constant6'
                                        *   '<S62>/Constant9'
                                        *   '<S74>/Constant5'
                                        *   '<S74>/Constant6'
                                        *   '<S74>/Constant9'
                                        */
};

/* Constant parameters (auto storage) */
const ConstParam_MGCCode MGCCode_ConstP = {
  /* Pooled Parameter (Expression: [0
     0.01
     0.02
     0.03
     0.04
     0.05
     0.06
     0.07
     0.08
     0.09
     0.1
     0.11
     0.12
     0.13
     0.14
     0.15
     0.16
     0.17
     0.18
     0.19
     0.2
     0.21
     0.22
     0.23
     0.24
     0.25
     0.26
     0.27
     0.28
     0.29
     0.3
     0.31
     0.32
     0.33
     0.34
     0.35
     0.36
     0.37
     0.38
     0.39
     0.4
     0.41
     0.42
     0.43
     0.44
     0.45
     0.46
     0.47
     0.48
     0.49
     0.5
     0.51
     0.52
     0.53
     0.54
     0.55
     0.56
     0.57
     0.58
     0.59
     0.6
     0.61
     0.62
     0.63
     0.64
     0.65
     0.66
     0.67
     0.68
     0.69
     0.7
     0.71
     0.72
     0.73
     0.74
     0.75
     0.76
     1
     ])
   * Referenced by:
   *   '<S39>/Omega2P Lookup Table'
   *   '<S39>/P2Omega Lookup Table1'
   */
  { 0.0F, 0.01F, 0.02F, 0.03F, 0.04F, 0.05F, 0.06F, 0.07F, 0.08F, 0.09F, 0.1F,
    0.11F, 0.12F, 0.13F, 0.14F, 0.15F, 0.16F, 0.17F, 0.18F, 0.19F, 0.2F, 0.21F,
    0.22F, 0.23F, 0.24F, 0.25F, 0.26F, 0.27F, 0.28F, 0.29F, 0.3F, 0.31F, 0.32F,
    0.33F, 0.34F, 0.35F, 0.36F, 0.37F, 0.38F, 0.39F, 0.4F, 0.41F, 0.42F, 0.43F,
    0.44F, 0.45F, 0.46F, 0.47F, 0.48F, 0.49F, 0.5F, 0.51F, 0.52F, 0.53F, 0.54F,
    0.55F, 0.56F, 0.57F, 0.58F, 0.59F, 0.6F, 0.61F, 0.62F, 0.63F, 0.64F, 0.65F,
    0.66F, 0.67F, 0.68F, 0.69F, 0.7F, 0.71F, 0.72F, 0.73F, 0.74F, 0.75F, 0.76F,
    1.0F },

  /* Pooled Parameter (Expression: [0.510
     0.524
     0.538
     0.552
     0.566
     0.579
     0.593
     0.606
     0.619
     0.632
     0.645
     0.658
     0.671
     0.683
     0.696
     0.708
     0.720
     0.732
     0.744
     0.756
     0.767
     0.779
     0.790
     0.801
     0.812
     0.823
     0.834
     0.845
     0.855
     0.865
     0.876
     0.886
     0.896
     0.906
     0.915
     0.925
     0.934
     0.944
     0.953
     0.962
     0.971
     0.980
     0.988
     0.997
     1.005
     1.013
     1.021
     1.029
     1.037
     1.045
     1.053
     1.060
     1.067
     1.074
     1.081
     1.088
     1.095
     1.102
     1.108
     1.115
     1.121
     1.127
     1.133
     1.139
     1.144
     1.150
     1.155
     1.161
     1.166
     1.171
     1.176
     1.180
     1.185
     1.190
     1.194
     1.198
     1.200
     1.3
     ])
   * Referenced by:
   *   '<S39>/Omega2P Lookup Table'
   *   '<S39>/P2Omega Lookup Table1'
   */
  { 0.51F, 0.524F, 0.538F, 0.552F, 0.566F, 0.579F, 0.593F, 0.606F, 0.619F,
    0.632F, 0.645F, 0.658F, 0.671F, 0.683F, 0.696F, 0.708F, 0.72F, 0.732F,
    0.744F, 0.756F, 0.767F, 0.779F, 0.79F, 0.801F, 0.812F, 0.823F, 0.834F,
    0.845F, 0.855F, 0.865F, 0.876F, 0.886F, 0.896F, 0.906F, 0.915F, 0.925F,
    0.934F, 0.944F, 0.953F, 0.962F, 0.971F, 0.98F, 0.988F, 0.997F, 1.005F,
    1.013F, 1.021F, 1.029F, 1.037F, 1.045F, 1.053F, 1.06F, 1.067F, 1.074F,
    1.081F, 1.088F, 1.095F, 1.102F, 1.108F, 1.115F, 1.121F, 1.127F, 1.133F,
    1.139F, 1.144F, 1.15F, 1.155F, 1.161F, 1.166F, 1.171F, 1.176F, 1.18F, 1.185F,
    1.19F, 1.194F, 1.198F, 1.2F, 1.3F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
