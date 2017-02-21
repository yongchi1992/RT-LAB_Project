
#include "IQMATHLIB.H"
#ifndef __RotateVector_H__
#define __RotateVector_H__

#define PI _IQ(3.1415926)

typedef struct{
				void (*calc)(void *);
				//����
				_iq Angle;  //��ת�ĽǶ�  -1 ~ 1
				_iq k;  	//�����ѹ�˵�ϵ��  0~1
				//���
				_iq  Ualpha; 			// Input: reference alpha-axis phase voltage 
				_iq  Ubeta;			// Input: reference beta-axis phase voltage
				}ROTATEVECTOR;

#define ROTATEVECTOR_DEFAULTS {(void (*)(void *))RotateVecotr_calc, \
							0,0,0,0 }

typedef ROTATEVECTOR *RotateVecotr_Handle;

void RotateVecotr_calc(RotateVecotr_Handle);

#endif
