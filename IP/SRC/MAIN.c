//=====================================�ļ�ͷ==========================================
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "net.h"                 //�������¼�֮�䡢���֮��ͨѶ��ͷ�ļ�����ͨѶ�йص��ļ�ֻ��net.c �� net.h

//���漸������һ�������йص�ͷ�ļ�����ͬ��΢����ģ�Ͷ�Ӧ��ͷ�ļ���ͬ�����Ǳ���ǵ�include������Ҫ����ͷ�ļ���include,��������׺��ԡ�
#include "c2000_main.h"
#include "rtwtypes.h"
#include "Bat_Control.h"
#include "Bat_Control_private.h"
#include "Bat_Control_types.h"

//���漸������ϵͳʱ�ӡ�ADCʱ�ӡ���������ʱ���йصĺ궨
#define ADC_SHCLK  0x1
#define ADC_CKPS   0x0
#define ADC_MODCLK 0x3
#define CPU_FREQ 	 150E6
#define LSPCLK_FREQ  CPU_FREQ/4

//��4������I/O�ź��йصĺ궨��
#define DOUT1 GpioDataRegs.GPBDAT.bit.GPIO51
#define DOUT2 GpioDataRegs.GPBDAT.bit.GPIO50
#define DOUT3 GpioDataRegs.GPBDAT.bit.GPIO53
#define DOUT4 GpioDataRegs.GPBDAT.bit.GPIO52

//3����PWM���Ƶ���йصĺ궨�塣37500��Ӧ4kHz�������ڣ�30000��Ӧ5kHz, 25000��Ӧ6kHz���������Ҫ�������ױ����ԡ�
#define EPWM1_TIMER_TBPRD  37500
#define EPWM2_TIMER_TBPRD  37500
#define EPWM3_TIMER_TBPRD  37500

//������PWM����йصĺ궨��
#define EPWM1_CMPA     1
#define EPWM1_CMPB     37499
#define EPWM2_CMPA     1
#define EPWM2_CMPB     37499
#define EPWM3_CMPA     1
#define EPWM3_CMPB     37499
#define EPWM_CMP_UP   1
#define EPWM_CMP_DOWN 0

//��PWM����йصĽṹ��ĸ��ı������Ͷ���
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

//������������
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

//������PWM����йص�ȫ�ֱ���
EPWM_INFO epwm1_info;
EPWM_INFO epwm2_info;
EPWM_INFO epwm3_info;

//�������ڴ���float�ͱ��������飬��������CCS��Graphicsʵʱ�鿴�������εĹ��ܡ������á�����һֱ��������
//������������������Ӧ�ı�����ͬһ���������ͣ���Graphics�Ի����еı�������Ҳ�������ó�һ���ģ��������Ҫ��
float temp01[250];
float temp02[250];
float temp03[250];
float temp04[250];
//�������ڴ���uint16�ͱ��������飬��������CCS��Graphicsʵʱ�鿴�������εĹ��ܡ������á�����һֱ��������
//������������������Ӧ�ı�����ͬһ���������ͣ���Graphics�Ի����еı�������Ҳ�������ó�һ���ģ��������Ҫ��
unsigned int uint16temp01[250];
unsigned int uint16temp02[250];
unsigned int uint16temp03[250];
int tempabindex = 0;

//������ͨѶ�йص�ȫ�ֱ���������˵Ӧ�ö�����net.c�У�extern������net.h�С�����������ԸĽ���
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

//������ʱ�ļ�����־λ��ȫ�ֱ�����
Uint16 T0flag=0;
Uint16 T1flag=0;
Uint16 T2flag=0;
Uint16 adcflag=0;
Uint16 seeflag=0;


//=======================================MAIN.C����=================================

//ͨ����ʱ����
void Delay(unsigned int  x)
{
    unsigned int i;
    for(i=0;i<x;i++){

    }
}

//ADCת������жϣ����ȼ�����T0�жϣ���Ϊ������������ģʽ������û��������жϡ�
interrupt void  adc_isr(void)
{
  adcflag=1;
  AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         //������������λ��״̬CONV00
  AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       //���ADC����жϱ�־λ
  AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;     //��ֹADC����ж�
  AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;         //����ƺ�û���á���������

  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
  return;
}

//CPUTIMER0�жϣ�0��1��2��Ωһ�õ��Ķ�ʱ���жϡ�
interrupt void cpu_timer0_isr(void)   //ĿǰΪ1/4ms��ʱ��
{
	CpuTimer0.InterruptCount++;
	T0flag=1;

	//����������¡�
	//9��ADC���룬 ֮���Գ���3.052503������֣�����Ϊԭ�����㷨Ϊ�� = 2.0 * (AdcRegs.ADCRESULTx >> 4)/ 4095 - 1; ��ֵ����������ڵı仯���仯��
	//����㷨���ڽ�0~3Vת��Ϊ-1~+1����ADCRESULT�Ĵ���Ϊ16λ�Ĵ����������������ڸ�12λ�С�
	//Pref��QrefΪ��Ϊ���룬����AD�����õ���
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

	//����ĵ����㺯����ռʱ����������ڵ�Ƶ����Ҫȡ�����������������ʱ����
	//��ʱ��������ʵʱ����ʱ����CCS�Դ���clock���߲�þ�ȷ����ʱ��������ߺ���Ҫ������һֱ��������
	//�˺���������ɿ����㷨�ļ��㡢�Լ� SVPWM��ռ�ձ����ֵ���㣬��2�����ܡ�
	Bat_Control_step();

    //6·PWM�����ռ�ձȸ��¡�ʵ��SVPWM�Ĺ��ܡ�
	//Bat_Control_Y�ĳ�Ա�ķ�ΧΪ0~65535��
	//֮���Գ���0.5722133211����Ϊ֮ǰ���㷨Ϊ��EPWMx_TIMER_TBPRD/65536����ֵ���ſ������ڵı仯���仯����������ױ����ԡ�
	EPwm1Regs.CMPA.half.CMPA = 0.5722133211 * Bat_Control_Y.Ta;     // Set compare A value
	EPwm1Regs.CMPB =           0.5722133211 * Bat_Control_Y.Ta;     // Set Compare B value
	EPwm2Regs.CMPA.half.CMPA = 0.5722133211 * Bat_Control_Y.Tb;     // Set compare A value
	EPwm2Regs.CMPB =           0.5722133211 * Bat_Control_Y.Tb;     // Set Compare B value
	EPwm3Regs.CMPA.half.CMPA = 0.5722133211 * Bat_Control_Y.Tc;     // Set compare A value
	EPwm3Regs.CMPB =           0.5722133211 * Bat_Control_Y.Tc;     // Set Compare B value

	//�����ؼ�ֵ�ļ�¼������CCS�Դ���Graphicsʵʱ�鿴�������εĹ��ܣ�������ܺ���Ҫ������һֱ��������
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

	//�жϱ�־λ����
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	return;
}

//CPUTIMER1�жϷ���������ʱ���á�
interrupt void cpu_timer1_isr(void)
{
	CpuTimer1.InterruptCount++;
	T1flag=1;
	EDIS;
	return;
}

//CPUTIMER2�жϷ���������ʱ���á�
interrupt void cpu_timer2_isr(void)
{
	EALLOW;
	CpuTimer2.InterruptCount++;
	T2flag=1;
	EDIS;
	return;
}

//������
void 	main(void)
{
	Uint16	mmm=0,t=0,Temp=0;

	//ϵͳ��ʼ�����á�ʵ��3�����ܣ��ؿ��Ź���ϵͳʱ������Ϊ150MHz��ʹ�ܸ�����ʱ�ӡ�
	InitSysCtrl();
	//���ø�GPIO���ŵĹ��ܡ�����DSP�ͺ�ʱ���ر�ע�����������
	InitXintf16Gpio();
	//6·PWM��Ӧ��GPIO���ŵĵ������á�
	InitEPwm1Gpio();
	InitEPwm2Gpio();
	InitEPwm3Gpio();

	//��ʼ��PIEģ�飨���ⲿ�ж���չģ�飩��ʱ�ӡ����ܶ���
	//�����йر����жϡ�
	InitPieCtrl();

	//CPU���жϵĳ�ʼ��ĬĬ��
	IER = 0x0000;
	IFR = 0x0000;
	//PIEģ��ĳ�ʼ�����á����ж�����������á����ܶ���
	InitPieVectTable();
	//CPUTIMER��ʱ���ĳ�ʼ�����á�
	InitCpuTimers();

	//�򿪼Ĵ���д�������ء�
	EALLOW;
	//���жϷ��������������ж��������Ӧ������һ�����Ƴ�����ʵֻ�õ���CPUTIMER0�жϡ�
	PieVectTable.TINT0 = &cpu_timer0_isr;
	PieVectTable.XINT13 = &cpu_timer1_isr;
	PieVectTable.TINT2 = &cpu_timer2_isr;
    //�رռĴ���д�������ء�
	EDIS;

	//��3��CPUTIMER��ʱ����ʱ������ã�һ�����Ƴ�����ʵֻ�õ���CPUTIMER0��ʱ����
	#if (CPU_FRQ_150MHZ)
	ConfigCpuTimer(&CpuTimer0, 150, 250);         //25O��Ӧ4kHz��200��Ӧ5kHz,1000/6��Ӧ6kHz
	ConfigCpuTimer(&CpuTimer1, 150, 10000);
	ConfigCpuTimer(&CpuTimer2, 150, 40000);
	#endif

	#if (CPU_FRQ_100MHZ)
	ConfigCpuTimer(&CpuTimer0, 100, 1000000);
	ConfigCpuTimer(&CpuTimer1, 100, 1000000);
	ConfigCpuTimer(&CpuTimer2, 100, 1000000);
	#endif


	//=========================ePWM���������ʼ��===========================��һ�β�Ҫ����
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;       //ePWM������ʱ�ӽ��ã���ȫ���Ĵ���������ٿ�����
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
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;      //ePWM������ʱ��ʹ�ܡ�
	EDIS;
	//==============================ePWM���������ʼ�������========================��һ�β�Ҫ����


	//====================================ADC��ʼ��===============================��һ�β�Ҫ����
	//ADC�ж����ȼ�����T0�ж�
	InitAdc();  // For this example, init the ADC

	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
	EDIS;

	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;   //���òɼ����Ĵ�С
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  //ADCʱ������
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         //����ģʽ
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;         //��������ģʽ
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;         //��ֹ����������λ
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;     //ADC�ɼ�����ж�ʹ��
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;     //SEQ1ת������һ��ɾ����жϱ�־λ
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;       //������������λ��CONV00

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;    //��01��ת��A0ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;    //��02��ת��A1ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;    //��03��ת��A2ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;    //��04��ת��A3ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV04 = 0x4;    //��05��ת��A4ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV05 = 0x5;    //��06��ת��A5ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV06 = 0x6;    //��07��ת��A6ͨ��
	AdcRegs.ADCCHSELSEQ1.bit.CONV07 = 0x7;    //��08��ת��A7ͨ��

	AdcRegs.ADCCHSELSEQ2.bit.CONV08 = 0x8;    //��09��ת��B0ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV09 = 0x9;    //��10��ת��B1ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV10 = 0xA;    //��11��ת��B2ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV11 = 0xB;    //��12��ת��B3ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV12 = 0xC;    //��13��ת��B4ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV13 = 0xD;    //��14��ת��B5ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV14 = 0xE;    //��15��ת��B6ͨ��
	AdcRegs.ADCCHSELSEQ2.bit.CONV15 = 0xF;    //��16��ת��B7ͨ��
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 15;    //һ�ι�ת��16��ͨ����// Set up ADC to perform 4 conversions for every SOC

	//=================================ADC��ʼ������==========================================��һ�β�Ҫ����

	//==================================����жϿ���===========================================
	IER |= M_INT1;
	IER |= M_INT13;//T1
	IER |= M_INT14;//T2
	//   IER |= M_INT3;//pwm1-3
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   //T0
	//PieCtrlRegs.PIEIER1.bit.INTx6 = 1;//ADC
	EINT;

	//��CPUȫ���ж�����λ��
	ERTM;

	//��ͨѶ�йصĳ�ʼ����
	Init8019();

    //��һ�������йصĳ�ʼ�������������Ҫ�������׺��ԡ�
	Bat_Control_initialize();

	//CPUTIMERʱ�ӿ�ʼ������һ�����Ƴ�����ֻ��CPUTIMER0ʱ�ӹ�����
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	//CpuTimer1Regs.TCR.all = 0x4001;
	//CpuTimer2Regs.TCR.all = 0x4001;

	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;     //�������ADCת����һ�δ������������ܣ���������ģ�������ô���á�

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

	/////////////////////�������̫��ͨ�Ų���
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

//PWM�жϷ��������ò��ţ��ѽ���
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


//PWM��ʼ������
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

//4·���ֿ��ؿ����źŵĳ�ʼ��������
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
	//������������
    //GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;  // Enable pull-up on GPIO51 (DOUT1)
    //GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;  // Enable pull-up on GPIO50 (DOUT2)
    //GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;  // Enable pull-up on GPIO53 (DOUT3)
    //GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;  // Enable pull-up on GPIO52 (DOUT4)
}

//===========================================================================
// No more.
//===========================================================================
