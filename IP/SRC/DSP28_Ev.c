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
	//定时器
	
	EvaRegs.T1CNT = 0;			 	 /* timer1 count is zero */
	EvaRegs.T1CON.all = 0x0840;      /* 启动定时器 连续增减模式 下溢时重装载                                       sysclk/1   */
	EvaRegs.T1PR = T1_PERIODS;



	//比较寄存器
	EvaRegs.ACTR.all = 0x0999;       /* 反向旋转 1.3.5低有效，2.4.6高有效 */

	//死区控制
	EvaRegs.DBTCONA.all = 0x0ff4;    /* 死区时间8us */
	//中断控制
	EvaRegs.EVAIMRA.all = 0x0200;    /* 开定时器下溢中断 */

}	

void EvaSetPwm(EvaHandle p)
{
   EvaRegs.CMPR1 = ((unsigned long)p->Ta *  T1_PERIODS) >> 16 ;
   EvaRegs.CMPR2 = ((unsigned long)p->Tb *  T1_PERIODS) >> 16 ;
   EvaRegs.CMPR3 = ((unsigned long)p->Tc *  T1_PERIODS) >> 16 ;
}

void EvaOpen(EvaHandle p)
{
   EvaRegs.COMCONA.all = 0x8200 ;       /* 置PWM管脚有效 使能比较操作 
                                            下溢重装载 */
//EvaRegs.COMCONA.all = 0x8200 ;
}

void EvaClose(EvaHandle p)
{
   EvaRegs.COMCONA.all = 0x8000 ;       /* 置PWM管脚无效 使能比较操作 
                                            下溢重装载 */
}




void EvbInit(EvbHandle p)
{
	EALLOW;
	GpioMuxRegs.GPBMUX.all=0x00ff;
	EDIS;
	
	EvbRegs.GPTCONB.all = 0x0;		 /* gp timer control register */
	//定时器
	
	EvbRegs.T3CNT = 0;			 	 /* timer1 count is zero */
	EvbRegs.T3CON.all = 0x0840;      /* 启动定时器 连续增减模式 下溢时重装载                                       sysclk/1   */
	EvbRegs.T3PR = T3_PERIODS;



	//比较寄存器
	EvbRegs.ACTRB.all = 0x0999;       /* 反向旋转 1.3.5低有效，2.4.6高有效 */
	//死区控制
//	EvbRegs.DBTCONB.all = 0x0ff4;    /* 死区时间8us */
	//中断控制
//	EvbRegs.EVBIMRA.all = 0x0200;    /* 开定时器下溢中断 */

}	

void EvbSetPwm(EvbHandle p)
{
   EvbRegs.CMPR4 = ((unsigned long)p->Ta *  T3_PERIODS) >> 16 ;
   EvbRegs.CMPR5 = ((unsigned long)p->Tb *  T3_PERIODS) >> 16 ;
   EvbRegs.CMPR6 = ((unsigned long)p->Tc *  T3_PERIODS) >> 16 ;
}

void EvbOpen(EvbHandle p)
{
   EvbRegs.COMCONB.all = 0x8200 ;       /* 置PWM管脚有效 使能比较操作 
                                            下溢重装载 */
//EvaRegs.COMCONA.all = 0x8200 ;
}

void EvbClose(EvbHandle p)
{
   EvbRegs.COMCONB.all = 0x8000 ;       /* 置PWM管脚无效 使能比较操作 
                                            下溢重装载 */
}
//===========================================================================
// No more.
//===========================================================================























