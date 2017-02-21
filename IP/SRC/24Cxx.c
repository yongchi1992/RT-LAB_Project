#include "DSP28_Device.h"
#include	"24Cxx.h"

#define	  	WriteDeviceAddress 	0xa0
#define		ReadDeviceAddress 	0xa1

#define	  	SetSCL	  	GpioDataRegs.GPBDAT.bit.GPIOB13 = 1
#define	  	ClrSCL		GpioDataRegs.GPBDAT.bit.GPIOB13 = 0
#define	  	SetSDA		GpioDataRegs.GPBDAT.bit.GPIOB14 = 1
#define	  	ClrSDA		GpioDataRegs.GPBDAT.bit.GPIOB14 = 0	

#define		SDAPORT		GpioDataRegs.GPBDAT.bit.GPIOB14
#define		SDAIN		EALLOW; GpioMuxRegs.GPBDIR.bit.GPIOB14 = 0; EDIS
#define		SDAOUT		EALLOW; GpioMuxRegs.GPBDIR.bit.GPIOB14 = 1; EDIS	 

void Init24Cxx(void)
{
	EALLOW;
	GpioMuxRegs.GPBMUX.bit.C4TRIP_GPIOB13 =0;	//定义为IO口，接SCL
	GpioMuxRegs.GPBDIR.bit.GPIOB13 =1;   		//方向输出	
	GpioMuxRegs.GPBMUX.bit.C5TRIP_GPIOB14 =0;	//定义为IO口，接SDA
	GpioMuxRegs.GPBDIR.bit.GPIOB14 =1;   		//方向输出		
		
	GpioMuxRegs.GPBQUAL.all=0x0000;	// Input qualifier disabled
	EDIS;
}

void	delay(Uint16  number)
{
	Uint16  i,j;
	for(j = 0;j < number;j++) 
		for(i=50;i>0;i--);
}		

void	IStart(void)
{
	ClrSCL;
//----------------	
	SDAOUT;
	delay(50);
	SetSDA;
	SetSCL;
	delay(15);
	ClrSDA;
	delay(5);
	ClrSCL;
//---------------------
	delay(5);
	SetSDA;	
}

void	IStop(void)
{
	ClrSCL;	
	SDAOUT;
	delay(50);
	ClrSDA;
	delay(15);
	SetSCL;
	delay(5);
	SetSDA;
//----------------------
	delay(5);
	ClrSCL;	
}

void	IAck(void)
{
	SDAOUT;
	delay(50);
	ClrSDA;
	delay(5);
	SetSCL;
	delay(15);
	ClrSCL;
	delay(5);
	SetSDA;
}
void	INAck(void)
{
	SDAOUT;
	delay(50);
	SetSDA;
	SetSCL;
	delay(15);
	ClrSCL;
}

Uint16	TestAck(void)
{
	Uint16	Temp;
	ClrSCL;
	delay(5); 
	SDAIN;
	delay(50);
	SetSCL;
	delay(15);
	if(SDAPORT == 1) Temp = 1;
	else Temp = 0;
	delay(15);
	ClrSCL;
	
	return Temp;
}
void	WriteByte(Uint16  data)
{
	Uint16	i;
	Uint16	Temp = 0x8000;
	data = data<<8;
	SDAOUT;
	delay(50);
	for(i=8;i!=0;i--)
	{
		if (Temp & data)	SetSDA;
		else	ClrSDA;
		SetSCL;
		delay(15);
		ClrSCL;
		data = data<<1;
		delay(5);
	}
}

Uint16	ReadByte(void)
{
	Uint16	i;
	Uint16	Temp = 0x0000;
	SDAIN;
	delay(50);
	for (i=8;i!=0;i--)
	{
		SetSCL;
		delay(5);
		Temp = Temp<<1;
		if(SDAPORT == 1) Temp = Temp | 1;
		else	Temp = Temp | 0;
		delay(15);
		ClrSCL;
		delay(5);
	}
	return Temp;
}

Uint16	Write24Cxx(Uint16	*Wdata, Uint16	RomAddress, Uint16	number)
{	
	IStart();
	WriteByte(WriteDeviceAddress);
	if(TestAck())	return 1;
	WriteByte(RomAddress);
	if(TestAck())	return 1;
	for(;number!=0;number--)
	{
		WriteByte(*Wdata);
		if(TestAck())	return 1;
		Wdata++;
	}
	IStop();
	delay(10000);
	return 0;
}

Uint16	Read24Cxx(Uint16  *RamAddr, Uint16	RomAddress, Uint16 number)
{
	IStart();
	WriteByte(WriteDeviceAddress);
	if(TestAck())	return  1;
	WriteByte(RomAddress);
	if(TestAck())	return	1;
	IStart();
	WriteByte(ReadDeviceAddress);
	if(TestAck())	return  1;
	while(number!=1)
	{
		*RamAddr = ReadByte();
		IAck();
		RamAddr++;
		number--;
	}
	*RamAddr = ReadByte();
	INAck();
	IStop();
	return 0;
}

//===========================================================================
// No more.
//===========================================================================
