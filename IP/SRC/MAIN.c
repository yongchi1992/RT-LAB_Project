//=====================================文件头==========================================
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "net.h"                 //这是上下级之间、多机之间通讯的头文件，与通讯有关的文件只有net.c 和 net.h

//下面几个是与一级控制有关的头文件。不同的微电网模型对应的头文件不同，但是必须记得include，而且要所有头文件均include,这个很容易忽略。
#include "c2000_main.h"
#include "rtwtypes.h"
#include "Bat_Control.h"
#include "Bat_Control_private.h"
#include "Bat_Control_types.h"

//下面几个是与系统时钟、ADC时钟、低速外设时钟有关的宏定
#define ADC_SHCLK  0x1
#define ADC_CKPS   0x0
#define ADC_MODCLK 0x3
#define CPU_FREQ 	 150E6
#define LSPCLK_FREQ  CPU_FREQ/4

//与4个数字I/O信号有关的宏定义
#define DOUT1 GpioDataRegs.GPBDAT.bit.GPIO51
#define DOUT2 GpioDataRegs.GPBDAT.bit.GPIO50
#define DOUT3 GpioDataRegs.GPBDAT.bit.GPIO53
#define DOUT4 GpioDataRegs.GPBDAT.bit.GPIO52

//3个与PWM输出频率有关的宏定义。37500对应4kHz控制周期，30000对应5kHz, 25000对应6kHz，这个很重要，很容易被忽略。
#define EPWM1_TIMER_TBPRD  37500
#define EPWM2_TIMER_TBPRD  37500
#define EPWM3_TIMER_TBPRD  37500

//几个与PWM输出有关的宏定义
#define EPWM1_CMPA     1
#define EPWM1_CMPB     37499
#define EPWM2_CMPA     1
#define EPWM2_CMPB     37499
#define EPWM3_CMPA     1
#define EPWM3_CMPB     37499
#define EPWM_CMP_UP   1
#define EPWM_CMP_DOWN 0

//与PWM输出有关的结构体母体的变量类型定义
typedef struct
{
   volatile struct EPWM_REGS *EPwmRegHandle;
   Uint16 EPwm_CMPA_Direction;
   Uint16 EPwm_CMPB_Direction;
   Uint16 EPwmTimerIntCount;
   Uint16 EPwmMaxCMPA;
   Uint16 EPwmMinCMPA;
   Uint16 EPwmMaxCMPB;
   Uint16 EPwmMinCMPB;
}EPWM_INFO;

//几个函数声明
void Init4DigCtlGpio(void);
interrupt void  adc_isr(void);
interrupt void cpu_timer0_isr(void);
interrupt void cpu_timer1_isr(void);
interrupt void cpu_timer2_isr(void);

void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
interrupt void epwm1_isr(void);
interrupt void epwm2_isr(void);
interrupt void epwm3_isr(void);
void update_compare(EPWM_INFO*);

//几个与PWM输出有关的全局变量
EPWM_INFO epwm1_info;
EPWM_INFO epwm2_info;
EPWM_INFO epwm3_info;

//几个用于储存float型变量的数组，可以用于CCS的Graphics实时查看变量波形的功能。很有用。我们一直都用它。
//变量储存数组必须跟对应的变量是同一个变量类型，在Graphics对话框中的变量类型也必须设置成一样的，这个很重要。
float temp01[250];
float temp02[250];
float temp03[250];
float temp04[250];
//几个用于储存uint16型变量的数组，可以用于CCS的Graphics实时查看变量波形的功能。很有用。我们一直都用它。
//变量储存数组必须跟对应的变量是同一个变量类型，在Graphics对话框中的变量类型也必须设置成一样的，这个很重要。
unsigned int uint16temp01[250];
unsigned int uint16temp02[250];
unsigned int uint16temp03[250];
int tempabindex = 0;

//几个与通讯有关的全局变量，按理说应该定义在net.c中，extern声明在net.h中。所以这里可以改进。
Uint16 net_ad_buff0[240];
Uint16 net_ad_buff1[240];
Uint16 net_ad_buff2[240];
Uint16 net_ad_buff3[240];
Uint16 net_ad_buff4[240];
Uint16 net_ad_buff5[240];
Uint16 net_ad_buff6[240];
Uint16 net_ad_buff7[240];
Uint16 net_ad_buff8[240];
Uint16 net_ad_buff9[240];
Uint16 net_ad_buff10[240];
Uint16 net_ad_buff11[240];
Uint16 net_ad_buff12[240];
Uint16 net_ad_buff13[240];
Uint16 net_ad_buff14[240];
Uint16 net_ad_buff15[240];
Uint16	TxEthnetFrameBuffer[1518/2];
Uint16	RxEthnetFrameBuffer[1518/2];
Uint16  RxSuccessFlag;

//几个临时的计数标志位，全局变量。
Uint16 T0flag=0;
Uint16 T1flag=0;
Uint16 T2flag=0;
Uint16 adcflag=0;
Uint16 seeflag=0;


//=======================================MAIN.C正文=================================

//通用延时函数
void Delay(unsigned int  x)
{
    unsigned int i;
    for(i=0;i<x;i++){

    }
}

//ADC转换完成中断，优先级大于T0中断，因为采用连续运行模式，所以没有用这个中断。
interrupt void  adc_isr(void)
{
  adcflag=1;
  AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         //排序器立即复位到状态CONV00
  AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       //清除ADC完成中断标志位
  AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;     //禁止ADC完成中断
  AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;         //这个似乎没有用。。。。。

  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
  return;
}

//CPUTIMER0中断，0、1、2中惟一用到的定时器中断。
interrupt void cpu_timer0_isr(void)   //目前为1/4ms定时器
{
	CpuTimer0.InterruptCount++;
	T0flag=1;

	//输入变量更新。
	//9个ADC输入， 之所以出现3.052503这个数字，是因为原来的算法为： = 2.0 * (AdcRegs.ADCRESULTx >> 4)/ 4095 - 1; 此值不随控制周期的变化而变化。
	//这个算法意在将0~3V转换为-1~+1，而ADCRESULT寄存器为16位寄存器，采样结果存放在高12位中。
	//Pref和Qref为人为输入，不是AD采样得到。
	Bat_Control_U.Pref = 0.6;
	Bat_Control_U.Qref = 0;
	Bat_Control_U.Vabc_p.Va = 3.052503e-5*(AdcRegs.ADCRESULT0 ) - 1;
	Bat_Control_U.Vabc_p.Vb = 3.052503e-5*(AdcRegs.ADCRESULT1 ) - 1;
	Bat_Control_U.Vabc_p.Vc = 3.052503e-5*(AdcRegs.ADCRESULT2 ) - 1;
	Bat_Control_U.Iabc_j.Ia = 3.052503e-5*(AdcRegs.ADCRESULT3 ) - 1;
	Bat_Control_U.Iabc_j.Ib = 3.052503e-5*(AdcRegs.ADCRESULT4 ) - 1;
	Bat_Control_U.Iabc_j.Ic = 3.052503e-5*(AdcRegs.ADCRESULT5 ) - 1;
	Bat_Control_U.Iabco_c.Iao = 3.052503e-5*(AdcRegs.ADCRESULT6 ) - 1;
	Bat_Control_U.Iabco_c.Ibo = 3.052503e-5*(AdcRegs.ADCRESULT7 ) - 1;
	Bat_Control_U.Iabco_c.Ico = 3.052503e-5*(AdcRegs.ADCRESULT8 ) - 1;

	//最核心的运算函数，占时最长，控制周期的频率主要取决于这个函数的运行时长。
	//其时长可以在实时仿真时，用CCS自带的clock工具测得精确的用时。这个工具很重要，我们一直都用它。
	//此函数可以完成控制算法的计算、以及 SVPWM的占空比输出值计算，共2个功能。
	Bat_Control_step();

    //6路PWM输出的占空比更新。实现SVPWM的功能。
	//Bat_Control_Y的成员的范围为0~65535。
	//之所以出现0.5722133211是因为之前的算法为：EPWMx_TIMER_TBPRD/65536，此值随着控制周期的变化而变化。这个很容易被忽略。
	EPwm1Regs.CMPA.half.CMPA = 0.5722133211 * Bat_Control_Y.Ta;     // Set compare A value
	EPwm1Regs.CMPB =           0.5722133211 * Bat_Control_Y.Ta;     // Set Compare B value
	EPwm2Regs.CMPA.half.CMPA = 0.5722133211 * Bat_Control_Y.Tb;     // Set compare A value
	EPwm2Regs.CMPB =           0.5722133211 * Bat_Control_Y.Tb;     // Set Compare B value
	EPwm3Regs.CMPA.half.CMPA = 0.5722133211 * Bat_Control_Y.Tc;     // Set compare A value
	EPwm3Regs.CMPB =           0.5722133211 * Bat_Control_Y.Tc;     // Set Compare B value

	//几个关键值的记录，用于CCS自带的Graphics实时查看变量波形的功能，这个功能很重要，我们一直都用它。
	uint16temp01[tempabindex] = Bat_Control_Y.Ta;
	uint16temp02[tempabindex] = Bat_Control_Y.Tb;
	uint16temp03[tempabindex] = Bat_Control_Y.Tc;
	temp01[tempabindex] = Bat_Control_Y.Id;
	temp02[tempabindex] = Bat_Control_Y.Idref;
	temp03[tempabindex] = Bat_Control_Y.Vd;
	temp04[tempabindex] = Bat_Control_Y.Vdref;
	tempabindex++;
	if(tempabindex >= 250)
	{
		tempabindex = 0;
	}

	//中断标志位清零
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	return;
}

//CPUTIMER1中断服务函数，暂时不用。
interrupt void cpu_timer1_isr(void)
{
	CpuTimer1.InterruptCount++;
	T1flag=1;
	EDIS;
	return;
}

//CPUTIMER2中断服务函数，暂时不用。
interrupt void cpu_timer2_isr(void)
{
	EALLOW;
	CpuTimer2.InterruptCount++;
	T2flag=1;
	EDIS;
	return;
}

//主函数
void 	main(void)
{
	Uint16	mmm=0,t=0,Temp=0;

	//系统初始化配置。实现3个功能：关看门狗，系统时钟配置为150MHz，使能各外设时钟。
	InitSysCtrl();
	//配置各GPIO引脚的功能。更改DSP型号时需特别注意这个函数。
	InitXintf16Gpio();
	//6路PWM对应的GPIO引脚的单独配置。
	InitEPwm1Gpio();
	InitEPwm2Gpio();
	InitEPwm3Gpio();

	//初始化PIE模块（即外部中断扩展模块）的时钟。不能动。
	//里面有关闭总中断。
	InitPieCtrl();

	//CPU级中断的初始化默默。
	IER = 0x0000;
	IFR = 0x0000;
	//PIE模块的初始化配置。即中断向量表的配置。不能动。
	InitPieVectTable();
	//CPUTIMER定时器的初始化配置。
	InitCpuTimers();

	//打开寄存器写保护开关。
	EALLOW;
	//将中断服务函数的名字与中断向量表对应起来，一级控制程序其实只用到了CPUTIMER0中断。
	PieVectTable.TINT0 = &cpu_timer0_isr;
	PieVectTable.XINT13 = &cpu_timer1_isr;
	PieVectTable.TINT2 = &cpu_timer2_isr;
    //关闭寄存器写保护开关。
	EDIS;

	//对3个CPUTIMER定时器的时间的设置，一级控制程序其实只用到了CPUTIMER0定时器。
	#if (CPU_FRQ_150MHZ)
	ConfigCpuTimer(&CpuTimer0, 150, 250);         //25O对应4kHz，200对应5kHz,1000/6对应6kHz
	ConfigCpuTimer(&CpuTimer1, 150, 10000);
	ConfigCpuTimer(&CpuTimer2, 150, 40000);
	#endif

	#if (CPU_FRQ_100MHZ)
	ConfigCpuTimer(&CpuTimer0, 100, 1000000);
	ConfigCpuTimer(&CpuTimer1, 100, 1000000);
	ConfigCpuTimer(&CpuTimer2, 100, 1000000);
	#endif


	//=========================ePWM数字输出初始化===========================这一段不要动。
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;       //ePWM计数器时钟禁用，等全部寄存设置完成再开启。
	EDIS;
	InitEPwm1Example();
	InitEPwm2Example();
	InitEPwm3Example();
	Init4DigCtlGpio();
	/*
	DOUT1 = 1;
	DOUT2 = 0;
	DOUT3 = 1;
	DOUT4 = 0;
	*/
	GpioDataRegs.GPBDAT.bit.GPIO51 = 1;
	for(t = 0; t < 1000; t++) {}
	GpioDataRegs.GPBDAT.bit.GPIO50 = 0;
	for(t = 0; t < 1000; t++) {}
	GpioDataRegs.GPBDAT.bit.GPIO53 = 1;
	for(t = 0; t < 1000; t++) {}
	GpioDataRegs.GPBDAT.bit.GPIO52 = 0;
	for(t = 0; t < 1000; t++) {}
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;      //ePWM计数器时钟使能。
	EDIS;
	//==============================ePWM数字输出初始化化完毕========================这一段不要动。


	//====================================ADC初始化===============================这一段不要动。
	//ADC中断优先级大于T0中断
	InitAdc();  // For this example, init the ADC

	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
	EDIS;

	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;   //设置采集窗的大小
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  //ADC时钟设置
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         //级联模式
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;         //连续运行模式
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;         //禁止排序器覆盖位
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;     //ADC采集完成中断使能
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;     //SEQ1转换序列一完成就置中断标志位
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;       //排序器立即复位到CONV00

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;    //第01个转换A0通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;    //第02个转换A1通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;    //第03个转换A2通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;    //第04个转换A3通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV04 = 0x4;    //第05个转换A4通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV05 = 0x5;    //第06个转换A5通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV06 = 0x6;    //第07个转换A6通道
	AdcRegs.ADCCHSELSEQ1.bit.CONV07 = 0x7;    //第08个转换A7通道

	AdcRegs.ADCCHSELSEQ2.bit.CONV08 = 0x8;    //第09个转换B0通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV09 = 0x9;    //第10个转换B1通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV10 = 0xA;    //第11个转换B2通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV11 = 0xB;    //第12个转换B3通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV12 = 0xC;    //第13个转换B4通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV13 = 0xD;    //第14个转换B5通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV14 = 0xE;    //第15个转换B6通道
	AdcRegs.ADCCHSELSEQ2.bit.CONV15 = 0xF;    //第16个转换B7通道
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 15;    //一次共转换16个通道。// Set up ADC to perform 4 conversions for every SOC

	//=================================ADC初始化结束==========================================这一段不要动。

	//==================================层层中断开启===========================================
	IER |= M_INT1;
	IER |= M_INT13;//T1
	IER |= M_INT14;//T2
	//   IER |= M_INT3;//pwm1-3
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   //T0
	//PieCtrlRegs.PIEIER1.bit.INTx6 = 1;//ADC
	EINT;

	//打开CPU全局中断屏蔽位。
	ERTM;

	//与通讯有关的初始化。
	Init8019();

    //与一级控制有关的初始化程序，这个很重要，很容易忽略。
	Bat_Control_initialize();

	//CPUTIMER时钟开始工作，一级控制程序中只有CPUTIMER0时钟工作。
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	//CpuTimer1Regs.TCR.all = 0x4001;
	//CpuTimer2Regs.TCR.all = 0x4001;

	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;     //软件触发ADC转换。一次触发，终生不管，连续工作模块就是这么好用。

	while(1)
	{
	if(T0flag){
	T0flag=0;
	seeflag++;
	mmm++;
	if(mmm==4){
	UDPActiveTxData();
	mmm=0;
	    }
	}

	/////////////////////加入的以太网通信部分
		do{
			Temp=RecFrame();
		}while(Temp);
		if(RxSuccessFlag)
		{
			RxSuccessFlag=0;
			DoNetworkStuff();
		}
	//////////////////////////////////
	}		
}

//PWM中断服务函数，用不着，已禁用
interrupt void epwm1_isr(void)
{
   // Update the CMPA and CMPB values
  // update_compare(&epwm1_info);

   // Clear INT flag for this timer
   EPwm1Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


interrupt void epwm2_isr(void)
{

   // Update the CMPA and CMPB values
  // update_compare(&epwm2_info);

   // Clear INT flag for this timer
   EPwm2Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void epwm3_isr(void)
{

   // Update the CMPA and CMPB values
  // update_compare(&epwm3_info);

   // Clear INT flag for this timer
   EPwm3Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


//PWM初始化函数
void InitEPwm1Example()
{

   // Setup TBCLK
   EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;           // Set timer period 801 TBCLKs
   EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA ;     // Set compare A value
   EPwm1Regs.CMPB = EPWM1_CMPB ; //EPWM1_MAX_CMPB;               // Set Compare B value

   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR =0;                      // Clear counter

   // Set Compare values


   // Setup counter mode
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;

   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;


   // Setup shadowing
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


   // Set actions


   EPwm1Regs.AQCTLA.bit.PRD = AQ_SET;             // Set PWM1A on event A, up count
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;           // Clear PWM1A on event A, down count

   EPwm1Regs.AQCTLB.bit.PRD =AQ_CLEAR;            // Set PWM1B on event B, up count
   EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;           // Clear PWM1B on event B, down count

}


void InitEPwm2Example()
{


   // Setup TBCLK
   EPwm2Regs.TBPRD = EPWM2_TIMER_TBPRD;           // Set timer period 801 TBCLKs
   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

   // Set Compare values
   EPwm2Regs.CMPA.half.CMPA = EPWM2_CMPA;     // Set compare A value
   EPwm2Regs.CMPB = EPWM2_CMPB;               // Set Compare B value

   // Setup counter mode
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;//DOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   // Setup shadowing
   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


   // Set actions
   EPwm2Regs.AQCTLA.bit.PRD = AQ_SET;             // Set PWM1A on event A, up count
   EPwm2Regs.AQCTLA.bit.CAU  = AQ_CLEAR;           // Clear PWM1A on event A, down count

   EPwm2Regs.AQCTLB.bit.PRD = AQ_CLEAR;            // Set PWM1B on event B, up count
   EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;           // Clear PWM1B on event B, down count

}

void InitEPwm3Example(void)
{


   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;// Count up/down
   EPwm3Regs.TBPRD = EPWM3_TIMER_TBPRD;          // Set timer period
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;       // Disable phase loading
   EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;          // Phase is 0
   EPwm3Regs.TBCTR = 0x0000;                     // Clear counter
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;      // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   // Setup shadow register load on ZERO
   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

  // Set Compare values
   EPwm3Regs.CMPA.half.CMPA = EPWM3_CMPA;    // Set compare A value
   EPwm3Regs.CMPB =EPWM3_CMPB; // EPWM3_MAX_CMPB;              // Set Compare B value

   // Set Actions

   EPwm3Regs.AQCTLA.bit.PRD = AQ_SET;             // Set PWM1A on event A, up count
   EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;           // Clear PWM1A on event A, down count

   EPwm3Regs.AQCTLB.bit.PRD = AQ_CLEAR;            // Set PWM1B on event B, up count
   EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;           // Clear PWM1B on event B, down count





}

//4路数字开关控制信号的初始化函数。
void Init4DigCtlGpio(void)
{
	// 1 51
	// 2 50
	// 3 53
	// 4 52
	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;  // Configure GPIO21 as GPIO
	GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;  // Configure GPIO21 as GPIO
	GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;  // Configure GPIO21 as GPIO
	GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;  // Configure GPIO21 as GPIO

	GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;   // GPIO51 output
	GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;   // GPIO51 output
	GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;   // GPIO51 output
	GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1;   // GPIO51 output

	EDIS;
	//增加驱动能力
    //GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;  // Enable pull-up on GPIO51 (DOUT1)
    //GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;  // Enable pull-up on GPIO50 (DOUT2)
    //GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;  // Enable pull-up on GPIO53 (DOUT3)
    //GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;  // Enable pull-up on GPIO52 (DOUT4)
}

//===========================================================================
// No more.
//===========================================================================
