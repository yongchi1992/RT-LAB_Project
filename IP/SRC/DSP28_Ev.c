//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_Ev.c
//
// TITLE:	DSP28 Event Manager Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//###########################################################################

#include "DSP28_Device.h"


//---------------------------------------------------------------------------
// InitEv: 
//---------------------------------------------------------------------------
// This function initializes to a known state.
//
void EvaInit(EvaHandle p)
{
	EALLOW;
	GpioMuxRegs.GPAMUX.all=0x00ff;
	EDIS;
	
	EvaRegs.GPTCONA.all = 0x0;		 /* gp timer control register */
	//��ʱ��
	
	EvaRegs.T1CNT = 0;			 	 /* timer1 count is zero */
	EvaRegs.T1CON.all = 0x0840;      /* ������ʱ�� ��������ģʽ ����ʱ��װ��                                       sysclk/1   */
	EvaRegs.T1PR = T1_PERIODS;



	//�ȽϼĴ���
	EvaRegs.ACTR.all = 0x0999;       /* ������ת 1.3.5����Ч��2.4.6����Ч */

	//��������
	EvaRegs.DBTCONA.all = 0x0ff4;    /* ����ʱ��8us */
	//�жϿ���
	EvaRegs.EVAIMRA.all = 0x0200;    /* ����ʱ�������ж� */

}	

void EvaSetPwm(EvaHandle p)
{
   EvaRegs.CMPR1 = ((unsigned long)p->Ta *  T1_PERIODS) >> 16 ;
   EvaRegs.CMPR2 = ((unsigned long)p->Tb *  T1_PERIODS) >> 16 ;
   EvaRegs.CMPR3 = ((unsigned long)p->Tc *  T1_PERIODS) >> 16 ;
}

void EvaOpen(EvaHandle p)
{
   EvaRegs.COMCONA.all = 0x8200 ;       /* ��PWM�ܽ���Ч ʹ�ܱȽϲ��� 
                                            ������װ�� */
//EvaRegs.COMCONA.all = 0x8200 ;
}

void EvaClose(EvaHandle p)
{
   EvaRegs.COMCONA.all = 0x8000 ;       /* ��PWM�ܽ���Ч ʹ�ܱȽϲ��� 
                                            ������װ�� */
}




void EvbInit(EvbHandle p)
{
	EALLOW;
	GpioMuxRegs.GPBMUX.all=0x00ff;
	EDIS;
	
	EvbRegs.GPTCONB.all = 0x0;		 /* gp timer control register */
	//��ʱ��
	
	EvbRegs.T3CNT = 0;			 	 /* timer1 count is zero */
	EvbRegs.T3CON.all = 0x0840;      /* ������ʱ�� ��������ģʽ ����ʱ��װ��                                       sysclk/1   */
	EvbRegs.T3PR = T3_PERIODS;



	//�ȽϼĴ���
	EvbRegs.ACTRB.all = 0x0999;       /* ������ת 1.3.5����Ч��2.4.6����Ч */
	//��������
//	EvbRegs.DBTCONB.all = 0x0ff4;    /* ����ʱ��8us */
	//�жϿ���
//	EvbRegs.EVBIMRA.all = 0x0200;    /* ����ʱ�������ж� */

}	

void EvbSetPwm(EvbHandle p)
{
   EvbRegs.CMPR4 = ((unsigned long)p->Ta *  T3_PERIODS) >> 16 ;
   EvbRegs.CMPR5 = ((unsigned long)p->Tb *  T3_PERIODS) >> 16 ;
   EvbRegs.CMPR6 = ((unsigned long)p->Tc *  T3_PERIODS) >> 16 ;
}

void EvbOpen(EvbHandle p)
{
   EvbRegs.COMCONB.all = 0x8200 ;       /* ��PWM�ܽ���Ч ʹ�ܱȽϲ��� 
                                            ������װ�� */
//EvaRegs.COMCONA.all = 0x8200 ;
}

void EvbClose(EvbHandle p)
{
   EvbRegs.COMCONB.all = 0x8000 ;       /* ��PWM�ܽ���Ч ʹ�ܱȽϲ��� 
                                            ������װ�� */
}
//===========================================================================
// No more.
//===========================================================================























