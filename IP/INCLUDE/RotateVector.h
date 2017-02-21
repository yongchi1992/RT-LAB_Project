
#include "IQMATHLIB.H"
#ifndef __RotateVector_H__
#define __RotateVector_H__

#define PI _IQ(3.1415926)

typedef struct{
				void (*calc)(void *);
				//输入
				_iq Angle;  //旋转的角度  -1 ~ 1
				_iq k;  	//输出电压乘的系数  0~1
				//输出
				_iq  Ualpha; 			// Input: reference alpha-axis phase voltage 
				_iq  Ubeta;			// Input: reference beta-axis phase voltage
				}ROTATEVECTOR;

#define ROTATEVECTOR_DEFAULTS {(void (*)(void *))RotateVecotr_calc, \
							0,0,0,0 }

typedef ROTATEVECTOR *RotateVecotr_Handle;

void RotateVecotr_calc(RotateVecotr_Handle);

#endif
