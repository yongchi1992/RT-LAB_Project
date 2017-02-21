#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "net.h"

#define Mymac1 0x02
#define Mymac2 0xE0
#define Mymac3 0x4C       //一般来说都不需要改Mymac  除非板子多了起来，为了避免Mac重复，才要改。
#define Mymac4 0xA0
#define Mymac5 0x7E
#define Mymac6 0x7A

extern	Uint16  RxSuccessFlag;
extern	Uint16	TxEthnetFrameBuffer[1518/2];
extern	Uint16	RxEthnetFrameBuffer[1518/2];
extern Uint16 net_ad_buff0[240];
extern Uint16 net_ad_buff1[240];
extern Uint16 net_ad_buff2[240];
extern Uint16 net_ad_buff3[240];
extern Uint16 net_ad_buff4[240];
extern Uint16 net_ad_buff5[240];
extern Uint16 net_ad_buff6[240];
extern Uint16 net_ad_buff7[240];
extern Uint16 net_ad_buff8[240];
extern Uint16 net_ad_buff9[240];
extern Uint16 net_ad_buff10[240];
extern Uint16 net_ad_buff11[240];
extern Uint16 net_ad_buff12[240];
extern Uint16 net_ad_buff13[240];
extern Uint16 net_ad_buff14[240];
extern Uint16 net_ad_buff15[240];

/*
const Uint16 MyMAC[] = 		//02-E0-4C-A0-7E-7A
{0xE002,0xA04C,0x7A7E};

const Uint16 RemoteMAC[] = 		//60-EB-69-27-0A-75 
{0xEB60,0x2769,0x750A};
*/

const Uint16 MyMAC[] = 		//02-E0-4C-A0-7E-7A       //DSP的MAC，可以不变
{0xE002,0xA04C,0x7A7E};

const Uint16 RemoteMAC[] = 		//60-EB-69-27-0A-75   //这是我的电脑的MAC，学长你改成自己电脑
{0x8530,0x29A9,0x2F87};

//const Uint16 RemoteMAC[] = 	//	二级DSP的MAC
//{0xE002,0xA04C,0x7A7F};

//20-6A-8A-80-2A-94

//const Uint16 RemoteMAC[] =
//{0x6A20,0x808A,0x942A};


const Uint16 MyIP[] =		//222.205.47.170     //这是DSP的IP地址
{0xCDDE,0xAA2F};

const Uint16 RemoteIP[] =	//这是我的电脑的IP地址：222.205.47.166  学长去把自己电脑的IP地址也改成这个就好了
{0xCDDE,0xA62F};

const Uint16 SubnetMask[] =	//255.255.255.000
{0xFFFF,0x00FF};

const Uint16 GatewayIP[] = 	//222.205.47.1
{0xCDDE,0x012F};

Uint16	TxBufFlag;
Uint16	bnry,curr;
Uint16 UDPUserDataLenth; 
Uint16 IpEdition;                                //IP版本
Uint16 IpServiceType;
Uint16 IpIdent;
Uint16 MyUdpPort=1025;

Uint16 reclenth=0;
Uint16 recbox[1000];

//Uint16 RemoteMAC[3];                             // 48 bit MAC
Uint16 RecdFrameMAC[3];
Uint16 RecdFrameIP[2];
Uint16 RecdIpFrameLenth;
Uint16 TxFrameSize;
Uint16 ARPAnswerSuccessFlag;

Uint16 turn=0;
/**********************************************************************
**函数原型：    void  page(uchar pagenumber)
**入口参数:   	Uint16	pagenumber: 要切换的页
**出口参数:		无
**返 回 值：	无      
**说    明：	选择页,可选择0,1,2三页,第四页ne000兼容芯片保留 
************************************************************************/
void	page(Uint16 pagenumber)
		{
			Uint16	temp;
			temp = Reg00;				//command register
			temp = temp&0x3B ; 			//注意txp位不能要
			pagenumber=pagenumber <<6;
			temp=temp | pagenumber;
			Reg00=temp;
		}


/**********************************************************************
**函数原型:     void 	Init8019()
**入口参数:		无
**出口参数:		无
**返 回 值:		无              
**说    明:		对芯片的工作寄存器进行设置,各个寄存器的用法可参考文档和
**				络芯片的数据手册
************************************************************************/
void	Init8019()
		{
			DELAY_US(10000);
/**********************************************************************

1.Reg00命令寄存器: CR,命令寄存器,地址偏移量00H,为一个字节
  位:  7   6   5   4   3   2   1   0 
名字: PS1 PS0 RD2 RD1 RD0 TXP STA STP 
//============================================
2.
RD2,RD1,RD0: 这3个位代表要执行的功能。
 0   0   1 : 读网卡内存
 0   1   0 : 写网卡内存
 0   1   1 : 发送网卡数据包
 1   *   * : 完成或结束DMA的读写操作
//============================================
3.TXP位置1时发送数据包，发完自动清零
//============================================
4.
STA,STP:	这两个位用来启动命令或停止命令
 1   0 		启动命令
 0   1 		停止命令
//============================================
********************************************************/
			Reg00=0x21;   //使芯片处于停止模式,这时进行寄存器设置

			DELAY_US(10000); //延时10毫秒,确保芯片进入停止模式
			page(0);
			Reg0a=0x00;   //清rbcr0
			DELAY_US(5);
			Reg0b=0x00;   //清rbcr1
			DELAY_US(5);
			Reg0c= 0xe0;  //RCR,监视模式,不接收数据包          
			DELAY_US(5);
			Reg0d= 0xe2;  //TCR,loop back模式
			DELAY_US(5);

			Reg01=0x4c;
			DELAY_US(5);
			Reg02=0x80;
			DELAY_US(5);
			Reg03=0x4c;
			DELAY_US(5);
			Reg04=0x40;  //TPSR,发送起始页寄存器
			DELAY_US(5);
			Reg07=0xff;  //清除所有中断标志位，中断状态寄存器
			DELAY_US(5);
			Reg0f=0x00;  //中断屏蔽寄存器清0，禁止中断
			DELAY_US(5);

			Reg0e=0xC9;  // 数据配置寄存器，16位dma方式
			DELAY_US(5);
			page(1);
			DELAY_US(15);
			Reg07=0x4d;
			DELAY_US(5);
			Reg08=0x00;
			DELAY_US(5);
			Reg09=0x00;
			DELAY_US(5);
			Reg0a=0x00;
			DELAY_US(5);
			Reg0b=0x00;
			DELAY_US(5);
			Reg0c=0x00;
			DELAY_US(5);
			Reg0d=0x00;
			DELAY_US(5);
			Reg0e=0x00;
			DELAY_US(5);
			Reg0f=0x00;
			DELAY_US(5);

    		Reg01=Mymac1;
			DELAY_US(5);
    		Reg02=Mymac2;         //这里要修改的
			DELAY_US(5);
    		Reg03=Mymac3;
			DELAY_US(5);
    		Reg04=Mymac4;
			DELAY_US(5);
    		Reg05=Mymac5;
			DELAY_US(5);
    		Reg06=Mymac6;
			DELAY_US(5);

			page(0);
			DELAY_US(15);
			Reg0c=0xce;  //将芯片设置成正常模式,跟外部网络连接
			DELAY_US(5);
			Reg0d=0xe0;
			DELAY_US(5);
			Reg00=0x22;  //启动芯片开始工作
			DELAY_US(5);
//-----------------------------------
			Reg07=0xff;  //清除所有中断标志位
			DELAY_US(5);
		}

Uint16 CalcCheckSum(Uint16 *Start, Uint16 Count, Uint16 IsTCP, Uint16 IsUDP)
{
    Uint32 Sum;
  
    Sum = 0;
    if ((IsTCP)||(IsUDP)) 
    {
        Sum += MyIP[0];
        Sum += MyIP[1];
        Sum += RemoteIP[0];
        Sum += RemoteIP[1];
        Sum += SwapWord(Count*2);
        if(IsTCP)
             Sum += SwapWord(PROTOCOL_TCP);
        else
             Sum += SwapWord(PROTOCOL_UDP);
    }
    while (Count > 0) 
    {
        Sum += *Start;
        Start ++;
        Count --;
    }
    Sum = (Sum & 0xFFFF) + ((Sum >> 16)&0xFFFF);
    if(Sum&0xFFFF0000)
        Sum++;
    return((Uint16)((~Sum)&0xFFFF));
}


//=============================================================================
/**********************************************************************
**函数原型：    void 		SendFrame(Uint16 *TxdNetBuff,Uint16  length)
**入口参数:		Uint16    	*TxdNetBuff	:指向发送缓冲区
**              uint length					:发送数据包的长度
**出口参数:		无
**返 回 值：	无              
**说    明：	发送数据包,以太网底层驱动程序,所有的数据发送都要通过该程序
************************************************************************/
void	SendFrame(Uint16 *TxdNetBuff,Uint16 length)
		{
			Uint16	i,ii;
		   	if(length<46/2)
       			{
          			for(i=length;i<60/2;i++)	TxEthnetFrameBuffer[i]=0;
          			length=60/2;
       			}
			
			page(0);
			DELAY_US(5);					//切换至第0页
			length = length <<1;
			TxBufFlag=!TxBufFlag;			//设置两个发缓区,提高发送效率
			if(TxBufFlag)
				{Reg09=0x40 ;}				//设置发送页地址
			else
				{Reg09=0x46 ;}				//设置发送页地址
    		DELAY_US(5);
			Reg08=0x00; 					//read page address low
			DELAY_US(5);
			Reg0b = length >>8;				//写发送长度高位
			DELAY_US(5);
			Reg0a = length & 0x00ff;        //写发送长度低位  
			DELAY_US(5);
			Reg00=0x12;						//write dma, page0
			DELAY_US(5);

			for(i=0;i<length/2;i++)
				{
					Reg10 = TxEthnetFrameBuffer[i];
   				}
/***************************************/
//以下为终止DMA操作
			Reg0b=0x00; 
			DELAY_US(5);
			Reg0a=0x00;
			DELAY_US(5);
			Reg00=0x22;			//结束或放弃DMA操作
/***************************************/

			for(i=0;i<6;i++)	//最多重发6次
				{
					for(ii=0;ii<1000;ii++)
    					{//检查CR寄存器的txp位是否为低,为1说明正在发送,为0说明发完或出错放弃
        					if((Reg00&0x04)==0)  
        						{ break; }
        				}
					if((Reg04&0x01)!=0)//表示发送成功,判断发送状态寄存器TSR，决定是否出错
						{break;};
					Reg00=0x3e;
				}

			Reg07=0xff;
			DELAY_US(5);
			if(TxBufFlag)
				{
  					Reg04=0x40;   //txd packet start;
  				}
			else
				{
     				Reg04=0x46;  //txd packet start;
    			}
			DELAY_US(5);
			Reg06=length>>8;  //high byte counter
			DELAY_US(5);
			Reg05=length&0xff;//low byte counter
			DELAY_US(5);
			Reg07=0xff;
			DELAY_US(5);
			Reg00=0x3e;       //to sendpacket;
			DELAY_US(5);
	}

/**********************************************************************
**函数原型：    Uint16        Rec_NewPacket()
**入口参数:		无
**出口参数:		无
**返 回 值：	0          没有新数据包
**              1          接收到新数据包
**说    明：	查询是否有新数据包并接收进缓冲区
************************************************************************/
Uint16	RecFrame()
		{
			Uint16	i,ii;
			Uint16	Temp,length;
			union{
					Uint16	total;	
					struct{
							Uint16	high:8;
							Uint16	low:8;
						  }e;
				 }d;
				 		  		
			page(0);
			DELAY_US(15);
			bnry = Reg03;				//bnry page have read 读页指针
			bnry = bnry & 0x00FF;
			page(1);
			DELAY_US(15);
			curr = Reg07;				//curr writepoint 8019写页指针
			curr = curr & 0x00FF;
			page(0);
			if((curr==0))return(0);	//读的过程出错
			bnry++;
			if(bnry>0x7f)	bnry=0x4c;
			if(bnry!=curr)			//此时表示有新的数据包在缓冲区里
    			{					//在任何操作都最好返回page0
     				page(0);
     //=======================================
					DELAY_US(15);
     				Reg09=bnry;		//读页地址的高字节
					DELAY_US(5);
     				Reg08=0x00; 	//读页地址的低字节
					DELAY_US(5);
     				Reg0b=0x00;		//读取字节计数高字节
					DELAY_US(5);
     				Reg0a=18;       //读取字节计数高字节
					DELAY_US(5);
     				Reg00=0x0a;     //启动Remote DMA读操作
					DELAY_US(5);
	 
	 
     				for(i=0;i<9;i++)	//读取一包的前18个字节:4字节的8019头部,6字节目的地址,6字节原地址,2字节协议
                    	{
                       		RxEthnetFrameBuffer[i]=Reg10;
                      	}

     				if(RxEthnetFrameBuffer[5]!=RemoteMAC[0] || RxEthnetFrameBuffer[6]!=RemoteMAC[1] || RxEthnetFrameBuffer[7]!=RemoteMAC[2])
     				     				{

     				     					return 0;
     				     				}

 //=======================================中止DMA操作
					DELAY_US(5);
     				Reg0b=0x00;	//
					DELAY_US(5);
     				Reg0a=0x00;	//
					DELAY_US(5);
     				Reg00=0x22;	//结束或放弃DMA操作
					DELAY_US(5);
 //=======================================
					
					d.total = RxEthnetFrameBuffer[0];
					length = RxEthnetFrameBuffer[1];
     				if(((d.e.high & 0x01)==0)||(d.e.low > 0x7f) || (d.e.low < 0x4c)||( length > 1517))
    					{//接收状态错误或下一数据包的起始页地址错误或接收的数据包长度>1500字节
       						page(1);
							DELAY_US(15);
							curr=Reg07; 	//page1
							DELAY_US(5);
							page(0);		//切换回page0
							DELAY_US(15);
        					bnry = curr -1;
        					if(bnry < 0x4c) 	bnry =0x7f;
        					Reg03=bnry; 	//write to bnry     
							DELAY_US(15);
        					Reg07=0xff;
							return(0);
              			}
//=============================================
            
     				else//表示数据包是完好的.读取剩下的数据
     					{
     						Temp = SwapWord(RxEthnetFrameBuffer[8]);		
        					if((Temp == Frame_IP)||(Temp == Frame_ARP))
								{ //协议为IP或ARP才接收
                					Reg09 = bnry;   				//read page address high
									DELAY_US(5);
                					Reg08 = 4;      				//read page address low
									DELAY_US(5);
                					Reg0b = length>>8;  //read count high
									DELAY_US(5);
                					Reg0a = length & 0xff;//read count low;
									DELAY_US(5);
                					
                					Reg00=0x0a;                             //read dma
									DELAY_US(5);
						        	length=(length+1)/2;
                					for(ii=2;ii<length+2;ii++)
                						{
                							RxEthnetFrameBuffer[ii]=Reg10;
                						}
                        			//================终止DMA操作
                        			Reg0b=0x00;			//read count high   
									DELAY_US(5);
                        			Reg0a=0x00;			//read count low;
									DELAY_US(5);
                        			Reg00=0x22;			//结束或放弃DMA
									DELAY_US(5);
                        			//============================
                        		}
                        		//=========================================
                        	d.total = RxEthnetFrameBuffer[0];
                        	bnry = d.e.low - 1;	
                			if(bnry<0x4c)	bnry=0x7f;
	        				Reg03=bnry;      //write to bnry
							DELAY_US(5);
	               			Reg07=0xff;
							DELAY_US(5);
//--------------------------------------                			
                			RxSuccessFlag=1;
//--------------------------------------                			
                			return(1);   //have new packet
               			}
   				}
			else{	
					return(0);
				}	
		}

Uint16 SwapWord(Uint16 Data)
{
    return((Data>>8)|(Data<<8));
}

void WriteDWord(Uint16 *Address,Uint32 Data)
{
    Uint16 Temp;
    Temp=(Uint16)(Data>>16);
    *Address=SwapWord(Temp);
    Temp=(Uint16)(Data&0x0000FFFF);
    *(Address+1)=SwapWord(Temp);
}

void CopyFrameFromBE(Uint16 Offset,Uint16 Size)
{
    Uint16 i,Temp;
    for(i=0;i<Size;i++)
    {
         Temp=*(RxEthnetFrameBuffer+Offset+i);
         *(RxEthnetFrameBuffer+Offset+i)=SwapWord(Temp);
    }
}

//============================================================
//======================== ARP ================================
void ArpRequest(void)
{
	*(TxEthnetFrameBuffer + ETH_HEADER_START +0) = 0xFFFF;
	*(TxEthnetFrameBuffer + ETH_HEADER_START +1) = 0xFFFF;
	*(TxEthnetFrameBuffer + ETH_HEADER_START +2) = 0xFFFF;
	 
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_ARP);
//ARP
    *(TxEthnetFrameBuffer+ARP_HEADER_START+0)=SwapWord(HARDW_ETH);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+1)=SwapWord(Frame_IP);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+2)=SwapWord(IP_HLEN_PLEN);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+3)=SwapWord(OP_ARP_REQUEST);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+4),&MyMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+7),&MyIP,2);
    *(TxEthnetFrameBuffer + ARP_HEADER_START + 9) = 0;
    *(TxEthnetFrameBuffer + ARP_HEADER_START + 10) = 0;
    *(TxEthnetFrameBuffer + ARP_HEADER_START + 11) = 0;
    
    if(((RemoteIP[0]^MyIP[0])&SubnetMask[0])||((RemoteIP[1]^MyIP[1])&SubnetMask[1]))
         memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+12),&GatewayIP,2);
    else
         memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+12),&RemoteIP,2);
    TxFrameSize=ETH_HEADER_SIZE+ARP_FRAME_SIZE; 
    SendFrame(TxEthnetFrameBuffer,TxFrameSize);
}

void ArpAnswer(void)
{
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+0),&RecdFrameMAC,3);
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_ARP);
//ARP    
    *(TxEthnetFrameBuffer+ARP_HEADER_START+0)=SwapWord(HARDW_ETH);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+1)=SwapWord(Frame_IP);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+2)=SwapWord(IP_HLEN_PLEN);
    *(TxEthnetFrameBuffer+ARP_HEADER_START+3)=SwapWord(OP_ARP_ANSWER);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+4),&MyMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+7),&MyIP,2);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+9),&RecdFrameMAC,3);
    memcpy((TxEthnetFrameBuffer+ARP_HEADER_START+12),&RecdFrameIP,2);
    TxFrameSize=ETH_HEADER_SIZE+ARP_FRAME_SIZE;
    SendFrame(TxEthnetFrameBuffer,TxFrameSize);
}
//==============================================================
//===========================ICMP================================

void Process_ICMP_Frame(void)
{
    Uint16 ICMPTypeAndCode;
    
    CopyFrameFromBE(RTL8019_HEADER_SIZE+ICMP_HEADER_START,2);
    ICMPTypeAndCode=*(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+ICMP_HEADER_START);
    switch(ICMPTypeAndCode>>8)
    {
         case ICMP_ECHO: Prepare_ICMP_Answer();
                         break;
    }
}

void Prepare_ICMP_Answer(void)
{
    Uint16 ICMPDataCount;
    Uint16 CalcCkSum;

    ICMPDataCount=RecdIpFrameLenth-IP_HEADER_SIZE - ICMP_HEADER_SIZE;
//Ethnet
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START),&RecdFrameMAC,3);
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_IP);
//IP
    *(TxEthnetFrameBuffer+IP_HEADER_START+0)=SwapWord(Ip_Edition);
    *(TxEthnetFrameBuffer+IP_HEADER_START+1)=SwapWord(RecdIpFrameLenth*2);
    *(TxEthnetFrameBuffer+IP_HEADER_START+2)=SwapWord(0);
    *(TxEthnetFrameBuffer+IP_HEADER_START+3)=SwapWord(0);
    *(TxEthnetFrameBuffer+IP_HEADER_START+4)=SwapWord((DEFUALT_TTL<<8)|PROTOCOL_ICMP);
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=0;
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+6),&MyIP,2);
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+8),&RecdFrameIP,2);

    CalcCkSum=CalcCheckSum((TxEthnetFrameBuffer+IP_HEADER_START),IP_HEADER_SIZE,0,0);
    if(!CalcCkSum)
         CalcCkSum=0xFFFF;
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=CalcCkSum;
//ICMP    
    *(TxEthnetFrameBuffer+ICMP_HEADER_START+0)=SwapWord(ICMP_ECHO_REPLY<<8);
    *(TxEthnetFrameBuffer+ICMP_HEADER_START+1)=0;
//    CopyFrameFrom8900(ICMP_HEADER_START+2,ICMPDataCount);
    memcpy((TxEthnetFrameBuffer+ICMP_HEADER_START+2),(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+ICMP_HEADER_START+2),ICMPDataCount);
    CalcCkSum=CalcCheckSum((TxEthnetFrameBuffer+ICMP_HEADER_START),(ICMPDataCount+ICMP_HEADER_SIZE),0,0);
    if(!CalcCkSum)
        CalcCkSum=0xFFFF;
    *(TxEthnetFrameBuffer+ICMP_HEADER_START+1)=CalcCkSum;
    TxFrameSize=ETH_HEADER_SIZE+IP_HEADER_SIZE+ICMP_HEADER_SIZE+ICMPDataCount;
    SendFrame(TxEthnetFrameBuffer,TxFrameSize);
}

/***************UDP*******************/
/*
void Process_UDP_Frame(void)
{
    Uint16 UdpLenth;

    CopyFrameFromBE(RTL8019_HEADER_SIZE+UDP_HEADER_START,4);
    if(*(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+UDP_HEADER_START+1)==MY_UDP_PORT)
    {
         UdpLenth=*(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+UDP_HEADER_START+2)/2;
         UDPUserDataLenth=UdpLenth-UDP_HEADER_SIZE;
    }
}
*/

void Process_UDP_Frame(void)
{
    Uint16 UdpLenth;
    Uint16 j=0;
    
    CopyFrameFromBE(RTL8019_HEADER_SIZE+UDP_HEADER_START,4);
    if(*(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+UDP_HEADER_START+1)==MY_UDP_PORT)
    {
         UdpLenth=*(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+UDP_HEADER_START+2)/2;
         UDPUserDataLenth=UdpLenth-UDP_HEADER_SIZE;
         reclenth=UDPUserDataLenth;
         for(j=0;j<reclenth;j++)
         recbox[j]=SwapWord(*(RxEthnetFrameBuffer+RTL8019_HEADER_SIZE+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+j));
         /*
          1. recbox是二级发给一级（我）的数据
          2. 这些数据会修改一级的一些东西，就接着在这里写。
          */
    }
}


void UDPSetTxdata(Uint16 i)
{
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+0+16*i)=SwapWord(0x1201);

    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+0+16*i)=SwapWord(0x1201);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+1+16*i)=SwapWord(net_ad_buff0[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+2+16*i)=SwapWord(net_ad_buff1[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+3+16*i)=SwapWord(net_ad_buff2[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+4+16*i)=SwapWord(net_ad_buff3[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+5+16*i)=SwapWord(net_ad_buff4[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+6+16*i)=SwapWord(net_ad_buff5[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+7+16*i)=SwapWord(net_ad_buff6[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+8+16*i)=SwapWord(net_ad_buff7[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+9+16*i)=SwapWord(net_ad_buff8[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+10+16*i)=SwapWord(net_ad_buff9[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+11+16*i)=0x0000;
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+12+16*i)=SwapWord(net_ad_buff10[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+13+16*i)=SwapWord(net_ad_buff11[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+14+16*i)=SwapWord(net_ad_buff12[6*i]);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+15+16*i)=SwapWord(net_ad_buff13[6*i]);


}
/*
void UDPActiveTxData(Uint16 t)
{
	
	

    

   // for(i=0;i<10;i++)
    //     *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+i)=i+0x3030;

    
    // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+0)=SwapWord(0x1201);
    UDPUserDataLenth=16*t;
    Prepare_UDP_Frame(Remoteudpport,UDPUserDataLenth);



}
*/
void UDPActiveTxData(void)
{

    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+0)=SwapWord(0x1201);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+1)=SwapWord(SEND0);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+2)=SwapWord(SEND1);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+3)=SwapWord(SEND2);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+4)=SwapWord(SEND3);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+5)=SwapWord(SEND4);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+6)=SwapWord(SEND5);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+7)=SwapWord(SEND6);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+8)=SwapWord(SEND7);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+9)=SwapWord(SEND8);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+10)=SwapWord(SEND9);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+11)=SwapWord(SEND10);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+12)=SwapWord(SEND11);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+13)=SwapWord(SEND12);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+14)=SwapWord(SEND13);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+15)=SwapWord(SEND14);
    *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+16)=SwapWord(SEND15);
    UDPUserDataLenth=17;
    Prepare_UDP_Frame(Remoteudpport,UDPUserDataLenth);



}



//void UDPActiveTxData(Uint16 i)
//{


	// Uint16 i;


   /* for(i=0;i<10;i++)
         *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+i)=i+0x3030;

    */
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+0)=SwapWord(0x1201);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+1)=SwapWord(net_ad_buff0[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+2)=SwapWord(net_ad_buff1[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+3)=SwapWord(net_ad_buff2[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+4)=SwapWord(net_ad_buff3[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+5)=SwapWord(net_ad_buff4[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+6)=SwapWord(net_ad_buff5[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+7)=SwapWord(net_ad_buff6[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+8)=SwapWord(net_ad_buff7[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+9)=SwapWord(net_ad_buff8[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+10)=SwapWord(net_ad_buff9[i]);
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+11)=0x0000;
   // *(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+12)=SwapWord(net_ad_buff10[i]);
    //*(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+13)=SwapWord(net_ad_buff11[i]);
    //*(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+14)=SwapWord(net_ad_buff12[i]);
    //*(TxEthnetFrameBuffer+ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+15)=SwapWord(net_ad_buff13[i]);
    //UDPUserDataLenth=16;
   // Prepare_UDP_Frame(Remoteudpport,UDPUserDataLenth);



//}

void Prepare_UDP_Frame(Uint16 RemoteUdpPort,Uint16 TxUDPDataNum)
{

    Uint16 CalcCkSum;
//ETHNET    
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+0),&RemoteMAC,3);
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);//有改动
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_IP);
//IP
    *(TxEthnetFrameBuffer+IP_HEADER_START+0)=SwapWord(Ip_Edition);
    *(TxEthnetFrameBuffer+IP_HEADER_START+1)=SwapWord((TxUDPDataNum+IP_HEADER_SIZE+UDP_HEADER_SIZE)*2);//修改
    *(TxEthnetFrameBuffer+IP_HEADER_START+2)=SwapWord(0x0000);
    *(TxEthnetFrameBuffer+IP_HEADER_START+3)=SwapWord(0x0000);
    *(TxEthnetFrameBuffer+IP_HEADER_START+4)=SwapWord((DEFUALT_TTL<<8)|PROTOCOL_UDP);
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=0;
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+6),&MyIP,2);
    memcpy((TxEthnetFrameBuffer+IP_HEADER_START+8),&RemoteIP,2);
    CalcCkSum=CalcCheckSum((TxEthnetFrameBuffer+IP_HEADER_START),IP_HEADER_SIZE,0,0);
    if(!CalcCkSum)
         CalcCkSum=0xFFFF;
    *(TxEthnetFrameBuffer+IP_HEADER_START+5)=CalcCkSum;
//UDP                                                  
    *(TxEthnetFrameBuffer+UDP_HEADER_START+0)=SwapWord(MY_UDP_PORT);
    *(TxEthnetFrameBuffer+UDP_HEADER_START+1)=SwapWord(Remoteudpport);//该远端端口
    *(TxEthnetFrameBuffer+UDP_HEADER_START+2)=SwapWord((TxUDPDataNum+UDP_HEADER_SIZE)*2);//修改
    *(TxEthnetFrameBuffer+UDP_HEADER_START+3)=0;

    CalcCkSum=CalcCheckSum((TxEthnetFrameBuffer+UDP_HEADER_START),(TxUDPDataNum+UDP_HEADER_SIZE),0,1);
    if(!CalcCkSum)
         CalcCkSum=0xFFFF;
    *(TxEthnetFrameBuffer+UDP_HEADER_START+3)=CalcCkSum;
    TxFrameSize=ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+TxUDPDataNum;   //这里我改了
    //UDPActiveTxData();
    SendFrame(TxEthnetFrameBuffer,TxFrameSize);
}

/***************TCP/IP*****************/

void ProcessEthBroadcastFrame(void)
{
    Uint16 TargetIP[2],FrameLenth;
    
	FrameLenth=5;
    CopyFrameFromBE(RTL8019_HEADER_SIZE+6,FrameLenth);
    memcpy(&RecdFrameMAC,(RxEthnetFrameBuffer+ETH_HEADER_START+RTL8019_HEADER_SIZE+3),3);
    if(*(RxEthnetFrameBuffer+ETH_HEADER_START+RTL8019_HEADER_SIZE+6)==Frame_ARP)
    {
         if(*(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE)==HARDW_ETH)
         {
              if(*(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+1)==Frame_IP)
              {
                   if(*(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+2)==IP_HLEN_PLEN)
                   {
                        if(*(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+3)==OP_ARP_REQUEST)
                        {
                             memcpy(&RecdFrameIP,(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+7),2);
                             memcpy(&TargetIP,(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+12),2);
                             if((MyIP[0]==TargetIP[0]) && (MyIP[1]==TargetIP[1]))
                                  ArpAnswer();    
                        }
                   }
              }
         }
    }               
}

void ProcessEthIAFrame(void)
{
    Uint16 FrameType,IpHeaderLenth,ProtocolType;
    
    CopyFrameFromBE(RTL8019_HEADER_SIZE+6,1);    
    memcpy(&RecdFrameMAC,(RxEthnetFrameBuffer+ETH_HEADER_START+RTL8019_HEADER_SIZE+3),3);
    FrameType=*(RxEthnetFrameBuffer+ETH_HEADER_START+RTL8019_HEADER_SIZE+6);
    switch(FrameType)
    {
         case Frame_ARP:
         {
              CopyFrameFromBE(ARP_HEADER_START+RTL8019_HEADER_SIZE+0,4);
              if(*(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+2)==IP_HLEN_PLEN)
              {
                   if(*(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+3)==OP_ARP_ANSWER)
                   {
                        memcpy(&RecdFrameMAC,(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+4),3);
                        memcpy(&RecdFrameIP,(RxEthnetFrameBuffer+ARP_HEADER_START+RTL8019_HEADER_SIZE+7),2);
                        ARPAnswerSuccessFlag=1;
                   }
              }
         }
         break;
         case Frame_IP:
         {
              CopyFrameFromBE(IP_HEADER_START+RTL8019_HEADER_SIZE+0,1);
              IpHeaderLenth=*(RxEthnetFrameBuffer+IP_HEADER_START+RTL8019_HEADER_SIZE);
              if((IpHeaderLenth&0xFF00)==Ip_Edition)
              {
                   IpHeaderLenth=5*(32/8)/2;
                   CopyFrameFromBE(IP_HEADER_START+RTL8019_HEADER_SIZE+1,IpHeaderLenth-1-4);
                   RecdIpFrameLenth=*(RxEthnetFrameBuffer+IP_HEADER_START+RTL8019_HEADER_SIZE+1)/2;
                   ProtocolType=*(RxEthnetFrameBuffer+IP_HEADER_START+RTL8019_HEADER_SIZE+4)&0x00FF;
                   memcpy(&RecdFrameIP,(RxEthnetFrameBuffer+IP_HEADER_START+RTL8019_HEADER_SIZE+6),2);
                   switch(ProtocolType)
                   {
                        case PROTOCOL_ICMP:  Process_ICMP_Frame();
                                             break;
                        case PROTOCOL_TCP : // Process_TCP_Frame();
                                             break;
                        case PROTOCOL_UDP :  Process_UDP_Frame();
                                             break;
                   }
              }
         }
         default: break;
    }
}

void DoNetworkStuff()
{    
    Uint16 Temp;
    page(0);
    Temp=Reg0c;
    Temp&=0x20;
    if(Temp)
         ProcessEthBroadcastFrame();
    else    
         ProcessEthIAFrame(); 
}

//======================= END ===============================

