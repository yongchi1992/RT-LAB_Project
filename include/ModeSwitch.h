/* rtwdemo_importstruct_user.h */

/* Copyright 2006-2012 The MathWorks, Inc. */

/*
 * This header file contains the type definition of the parameter
 * structure to be imported via const volatile pointer.
 */

#ifndef rtwdemo_import_struct_h
#define rtwdemo_import_struct_h

#include "rtwtypes.h"

#ifndef _DEFINED_TYPEDEF_FOR_SystemMode_
#define _DEFINED_TYPEDEF_FOR_SystemMode_
typedef enum {
        Start = 0,
        ConstPConstQ,
        AGC,
        Independent,
        ActiveIsland,
        Island,
        IslandAGC,
        ActiveGrid
} SystemMode;
 #endif

typedef struct {
    real32_T LinePPIGain;

    
    real32_T LinePPIIntegral;

            
    real32_T LinePPIUpperSat;
    real32_T LinePPILowerSat;
    
	real32_T FreqPIGain;

            
    real32_T FreqPIIntegral;

            
    real32_T FreqPIUpperSat;
    real32_T FreqPILowerSat;
}AGCCtrlParam;

typedef struct {
	real32_T LineQPIGain;

    
	real32_T LineQPIIntegral;

	
    real32_T LineQPIUpperSat;
	real32_T LineQPILowerSat;
	
	real32_T VoltPIGain;

    
	real32_T VoltPIIntegral;

    
	real32_T VoltPIUpperSat;
	real32_T VoltPILowerSat;
 } AVCCtrlParam;


typedef struct {
	real32_T ConstPPIGain;
	real32_T ConstPPIIntegral;
	real32_T ConstPPIUpperSat;
	real32_T ConstPPILowerSat;

	real32_T ConstQPIGain ;
	real32_T ConstQPIIntegral ;
	real32_T ConstQPIUpperSat ;
	real32_T ConstQPILowerSat ;
	
	real32_T AGCInnerPIGain ;
	real32_T AGCInnerPIIntegral ; 
	real32_T AGCInnerPIUpperSat ;
	real32_T AGCInnerPILowerSat;
		
	real32_T AVCInnerPIGain;
	real32_T AVCInnerPIIntegral;
	real32_T AVCInnerPIUpperSat;
	real32_T AVCInnerPILowerSat;
}GenCtrlParam;


typedef struct DataStruct_tag {
      AGCCtrlParam CtrlParamAGC; 
      AVCCtrlParam CtrlParamAVC;
	  GenCtrlParam CtrlParamDFIG1;
	  GenCtrlParam CtrlParamDFIG2;
      GenCtrlParam CtrlParamPV ;
	  GenCtrlParam CtrlParamBat;
      GenCtrlParam CtrlParamICE;
} DataStruct_type;

extern const volatile DataStruct_type *StructPointer;
//extern void Init_WorkingStruct(void);
extern void ModeSwitch(SystemMode Dataset);
#endif
