/* rtwdemo_importstruct_user.c */

/* $Revision: 1.1.6.1 $ */
/* Copyright 2006 The MathWorks, Inc. */

/* This source file defines two data structures that can be accessed via
 * pointer in code generated from Simulink. One of these structures,
 * called the ReferenceStruct, is located in const memory. The other,
 * called WorkingStruct, is located in volatile memory and is intended
 * to be changed during runtime by an external calibration tool. The
 * extern declaration for the const volatile StructPointer is included
 * in the corresponding header file.
 *
 * It also contains functions that can be used to initialize the working
 * structure and switch between the two parameter structures.
 * 
 * CAUTION!
 * When using a multitasking model or operating system, switching to a
 * different dataset must be done by the lowest-priority task (e.g.
 * background task) to ensure that data is not changed in the middle of
 * model calculation.
 */

#include "ModeSwitch.h"

/* Constant default data struct: ReferenceStruct */
const DataStruct_type GridConnectionStruct= 
{
    {  
		// SystemLineP
		(float)0.01,   
        (float)0.02,

		(float)0.5,
		(float)-1,
      
		// SystemFreq
		(float)0.2,
		(float)0.4,

		
        (float)0.5,
		(float)-1,
    },
    {
		// SystemLineQ
		(float)0.05,

                
		(float)0.05,

                
		(float)0.5,
		(float)-1,
		// SystemVolt
		(float)2.5
		(float)2.5,

		(float)0.5,
		(float)-1,
    },
	{  
		// DFIG1ConstP
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// DFIG1ConstQ
		(float)2,
		(float)3,
		(float)1,
		(float)-1,
		// DFIG1AGCInner
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// DFIG1AVCInner
		(float)1,
		(float)3,
		(float)1,
		(float)-1,
	},
	{  
		// DFIG2ConstP
		(float)0.5,
		(float)0.5,
		(float)1,
		(float)0,
		// DFIG2ConstQ
		(float)0.1,
		(float)0.05,
		(float)1,
		(float)0,
		// DFIG2AGCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
		// DFIG2AVCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
	},


	{  
		// PVConstP
		(float)0.5,
		(float)6,
		(float)1,
		(float)-1,
		// PVConstQ
		(float)0.5,
		(float)0.1,
		(float)1,
		(float)-1,
		// PVAGCInner
		(float)0.5,
		(float)6,
		(float)1,
		(float)-1,
		// PVAVCInner
		(float)0.5,
		(float)0.1,
		(float)1,
		(float)-1,
	},

	{  
		// BatConstP
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// BatConstQ
		(float)3,
		(float)3,
		(float)1,
		(float)-1,
		// BatAGCInner
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// BatAVCInner
		(float)1,
		(float)3,
		(float)1,
		(float)-1,
	},
    {  
		// ICEConstP
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// ICEConstQ
		(float)3,
		(float)3,
		(float)1,
		(float)-1,
		// ICEAGCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
		// ICEAVCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
	}
};

const DataStruct_type IslandStruct= 
{
    {  
		// SystemLineP
		(float)0.01,   
        (float)0.02,

		(float)0.5,
		(float)-1,
      
		// SystemFreq
		(float)0.2,
		(float)0.4,

		
        (float)0.5,
		(float)-1,
    },
    {
		// SystemLineQ
		(float)0.05,

                
		(float)0.05,

                
		(float)0.5,
		(float)-1,
		// SystemVolt
		(float)2.5
		(float)2.5,

		(float)0.5,
		(float)-1,
    },
	{  
		// DFIG1ConstP
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// DFIG1ConstQ
		(float)2,
		(float)3,
		(float)1,
		(float)-1,
		// DFIG1AGCInner
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// DFIG1AVCInner
		(float)1,
		(float)3,
		(float)1,
		(float)-1,
	},
	{  
		// DFIG2ConstP
		(float)0.5,
		(float)0.5,
		(float)1,
		(float)0,
		// DFIG2ConstQ
		(float)0.1,
		(float)0.05,
		(float)1,
		(float)0,
		// DFIG2AGCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
		// DFIG2AVCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
	},


	{  
		// PVConstP
		(float)0.5,
		(float)6,
		(float)1,
		(float)-1,
		// PVConstQ
		(float)0.5,
		(float)0.1,
		(float)1,
		(float)-1,
		// PVAGCInner
		(float)0.5,
		(float)6,
		(float)1,
		(float)-1,
		// PVAVCInner
		(float)0.5,
		(float)0.1,
		(float)1,
		(float)-1,
	},

	{  
		// BatConstP
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// BatConstQ
		(float)3,
		(float)3,
		(float)1,
		(float)-1,
		// BatAGCInner
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// BatAVCInner
		(float)1,
		(float)3,
		(float)1,
		(float)-1,
	},
    {  
		// ICEConstP
		(float)0.5,
		(float)5,
		(float)1,
		(float)-1,
		// ICEConstQ
		(float)3,
		(float)3,
		(float)1,
		(float)-1,
		// ICEAGCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
		// ICEAVCInner
		(float)0.05,
		(float)0.2,
		(float)1,
		(float)0,
	}
};





/* Volatile data struct: WorkingStruct */ 
//volatile DataStruct_type WorkingStruct;

/* Create pointer to the default data struct, e.g. ReferenceStruct */
const volatile DataStruct_type *StructPointer = &GridConnectionStruct;

/* Function to initialize WorkingStruct with data from ReferenceStruct */
// void Init_WorkingStruct(void)
// {
//       memcpy((void*)&WorkingStruct, &ReferenceStruct, sizeof(ReferenceStruct));
// }

/* Function to switch between structures */
void ModeSwitch(SystemMode Dataset)
{
    switch (Dataset)
    {
        case Start:
          StructPointer = &GridConnectionStruct;
          break;
        case ConstPConstQ:
          StructPointer = &GridConnectionStruct;
          break;
        case AGC:
          StructPointer = &GridConnectionStruct;
          break;
        case Independent:
          StructPointer = &GridConnectionStruct;
          break;
        case ActiveIsland:
          StructPointer = &GridConnectionStruct;
        case Island:
          StructPointer = &IslandStruct;
        case IslandAGC:
          StructPointer = &IslandStruct;
        case ActiveGrid:
          StructPointer = &IslandStruct;
          break;
        default:
          StructPointer = &GridConnectionStruct;
    }
}

/* EOF */
