
//ÃèÊö

#include "RotateVector.h"
#include "iqmathlib.h"

void RotateVecotr_calc(RotateVecotr_Handle v)
{
     _iq Ua,Ub;
   
// Using look-up IQ sine table
     Ub   = _IQsinPU(v->Angle);
     Ua   = _IQcosPU(v->Angle);
 
     v->Ualpha = _IQmpy(v->k,Ua);
     v->Ubeta  = _IQmpy(v->k,Ub);  
}

