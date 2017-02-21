#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "net.h"

#define Mymac1 0x02
#define Mymac2 0xE0
#define Mymac3 0x4C       //һ����˵������Ҫ��Mymac  ���ǰ��Ӷ���������Ϊ�˱���Mac�ظ�����Ҫ�ġ�
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

const Uint16 MyMAC[] = 		//02-E0-4C-A0-7E-7A       //DSP��MAC�����Բ���
{0xE002,0xA04C,0x7A7E};

const Uint16 RemoteMAC[] = 		//60-EB-69-27-0A-75   //�����ҵĵ��Ե�MAC��ѧ����ĳ��Լ�����
{0x8530,0x29A9,0x2F87};

//const Uint16 RemoteMAC[] = 	//	����DSP��MAC
//{0xE002,0xA04C,0x7A7F};

//20-6A-8A-80-2A-94

//const Uint16 RemoteMAC[] =
//{0x6A20,0x808A,0x942A};


const Uint16 MyIP[] =		//222.205.47.170     //����DSP��IP��ַ
{0xCDDE,0xAA2F};

const Uint16 RemoteIP[] =	//�����ҵĵ��Ե�IP��ַ��222.205.47.166  ѧ��ȥ���Լ����Ե�IP��ַҲ�ĳ�����ͺ���
{0xCDDE,0xA62F};

const Uint16 SubnetMask[] =	//255.255.255.000
{0xFFFF,0x00FF};

const Uint16 GatewayIP[] = 	//222.205.47.1
{0xCDDE,0x012F};

Uint16	TxBufFlag;
Uint16	bnry,curr;
Uint16 UDPUserDataLenth; 
Uint16 IpEdition;                                //IP�汾
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
**����ԭ�ͣ�    void  page(uchar pagenumber)
**��ڲ���:   	Uint16	pagenumber: Ҫ�л���ҳ
**���ڲ���:		��
**�� �� ֵ��	��      
**˵    ����	ѡ��ҳ,��ѡ��0,1,2��ҳ,����ҳne000����оƬ���� 
************************************************************************/
void	page(Uint16 pagenumber)
		{
			Uint16	temp;
			temp = Reg00;				//command register
			temp = temp&0x3B ; 			//ע��txpλ����Ҫ
			pagenumber=pagenumber <<6;
			temp=temp | pagenumber;
			Reg00=temp;
		}


/**********************************************************************
**����ԭ��:     void 	Init8019()
**��ڲ���:		��
**���ڲ���:		��
**�� �� ֵ:		��              
**˵    ��:		��оƬ�Ĺ����Ĵ�����������,�����Ĵ������÷��ɲο��ĵ���
**				��оƬ�������ֲ�
************************************************************************/
void	Init8019()
		{
			DELAY_US(10000);
/**********************************************************************

1.Reg00����Ĵ���: CR,����Ĵ���,��ַƫ����00H,Ϊһ���ֽ�
  λ:  7   6   5   4   3   2   1   0 
����: PS1 PS0 RD2 RD1 RD0 TXP STA STP 
//============================================
2.
RD2,RD1,RD0: ��3��λ����Ҫִ�еĹ��ܡ�
 0   0   1 : �������ڴ�
 0   1   0 : д�����ڴ�
 0   1   1 : �����������ݰ�
 1   *   * : ��ɻ����DMA�Ķ�д����
//============================================
3.TXPλ��1ʱ�������ݰ��������Զ�����
//============================================
4.
STA,STP:	������λ�������������ֹͣ����
 1   0 		��������
 0   1 		ֹͣ����
//============================================
********************************************************/
			Reg00=0x21;   //ʹоƬ����ֹͣģʽ,��ʱ���мĴ�������

			DELAY_US(10000); //��ʱ10����,ȷ��оƬ����ֹͣģʽ
			page(0);
			Reg0a=0x00;   //��rbcr0
			DELAY_US(5);
			Reg0b=0x00;   //��rbcr1
			DELAY_US(5);
			Reg0c= 0xe0;  //RCR,����ģʽ,���������ݰ�          
			DELAY_US(5);
			Reg0d= 0xe2;  //TCR,loop backģʽ
			DELAY_US(5);

			Reg01=0x4c;
			DELAY_US(5);
			Reg02=0x80;
			DELAY_US(5);
			Reg03=0x4c;
			DELAY_US(5);
			Reg04=0x40;  //TPSR,������ʼҳ�Ĵ���
			DELAY_US(5);
			Reg07=0xff;  //��������жϱ�־λ���ж�״̬�Ĵ���
			DELAY_US(5);
			Reg0f=0x00;  //�ж����μĴ�����0����ֹ�ж�
			DELAY_US(5);

			Reg0e=0xC9;  // �������üĴ�����16λdma��ʽ
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
    		Reg02=Mymac2;         //����Ҫ�޸ĵ�
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
			Reg0c=0xce;  //��оƬ���ó�����ģʽ,���ⲿ��������
			DELAY_US(5);
			Reg0d=0xe0;
			DELAY_US(5);
			Reg00=0x22;  //����оƬ��ʼ����
			DELAY_US(5);
//-----------------------------------
			Reg07=0xff;  //��������жϱ�־λ
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
**����ԭ�ͣ�    void 		SendFrame(Uint16 *TxdNetBuff,Uint16  length)
**��ڲ���:		Uint16    	*TxdNetBuff	:ָ���ͻ�����
**              uint length					:�������ݰ��ĳ���
**���ڲ���:		��
**�� �� ֵ��	��              
**˵    ����	�������ݰ�,��̫���ײ���������,���е����ݷ��Ͷ�Ҫͨ���ó���
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
			DELAY_US(5);					//�л�����0ҳ
			length = length <<1;
			TxBufFlag=!TxBufFlag;			//��������������,��߷���Ч��
			if(TxBufFlag)
				{Reg09=0x40 ;}				//���÷���ҳ��ַ
			else
				{Reg09=0x46 ;}				//���÷���ҳ��ַ
    		DELAY_US(5);
			Reg08=0x00; 					//read page address low
			DELAY_US(5);
			Reg0b = length >>8;				//д���ͳ��ȸ�λ
			DELAY_US(5);
			Reg0a = length & 0x00ff;        //д���ͳ��ȵ�λ  
			DELAY_US(5);
			Reg00=0x12;						//write dma, page0
			DELAY_US(5);

			for(i=0;i<length/2;i++)
				{
					Reg10 = TxEthnetFrameBuffer[i];
   				}
/***************************************/
//����Ϊ��ֹDMA����
			Reg0b=0x00; 
			DELAY_US(5);
			Reg0a=0x00;
			DELAY_US(5);
			Reg00=0x22;			//���������DMA����
/***************************************/

			for(i=0;i<6;i++)	//����ط�6��
				{
					for(ii=0;ii<1000;ii++)
    					{//���CR�Ĵ�����txpλ�Ƿ�Ϊ��,Ϊ1˵�����ڷ���,Ϊ0˵�������������
        					if((Reg00&0x04)==0)  
        						{ break; }
        				}
					if((Reg04&0x01)!=0)//��ʾ���ͳɹ�,�жϷ���״̬�Ĵ���TSR�������Ƿ����
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
**����ԭ�ͣ�    Uint16        Rec_NewPacket()
**��ڲ���:		��
**���ڲ���:		��
**�� �� ֵ��	0          û�������ݰ�
**              1          ���յ������ݰ�
**˵    ����	��ѯ�Ƿ��������ݰ������ս�������
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
			bnry = Reg03;				//bnry page have read ��ҳָ��
			bnry = bnry & 0x00FF;
			page(1);
			DELAY_US(15);
			curr = Reg07;				//curr writepoint 8019дҳָ��
			curr = curr & 0x00FF;
			page(0);
			if((curr==0))return(0);	//���Ĺ��̳���
			bnry++;
			if(bnry>0x7f)	bnry=0x4c;
			if(bnry!=curr)			//��ʱ��ʾ���µ����ݰ��ڻ�������
    			{					//���κβ�������÷���page0
     				page(0);
     //=======================================
					DELAY_US(15);
     				Reg09=bnry;		//��ҳ��ַ�ĸ��ֽ�
					DELAY_US(5);
     				Reg08=0x00; 	//��ҳ��ַ�ĵ��ֽ�
					DELAY_US(5);
     				Reg0b=0x00;		//��ȡ�ֽڼ������ֽ�
					DELAY_US(5);
     				Reg0a=18;       //��ȡ�ֽڼ������ֽ�
					DELAY_US(5);
     				Reg00=0x0a;     //����Remote DMA������
					DELAY_US(5);
	 
	 
     				for(i=0;i<9;i++)	//��ȡһ����ǰ18���ֽ�:4�ֽڵ�8019ͷ��,6�ֽ�Ŀ�ĵ�ַ,6�ֽ�ԭ��ַ,2�ֽ�Э��
                    	{
                       		RxEthnetFrameBuffer[i]=Reg10;
                      	}

     				if(RxEthnetFrameBuffer[5]!=RemoteMAC[0] || RxEthnetFrameBuffer[6]!=RemoteMAC[1] || RxEthnetFrameBuffer[7]!=RemoteMAC[2])
     				     				{

     				     					return 0;
     				     				}

 //=======================================��ֹDMA����
					DELAY_US(5);
     				Reg0b=0x00;	//
					DELAY_US(5);
     				Reg0a=0x00;	//
					DELAY_US(5);
     				Reg00=0x22;	//���������DMA����
					DELAY_US(5);
 //=======================================
					
					d.total = RxEthnetFrameBuffer[0];
					length = RxEthnetFrameBuffer[1];
     				if(((d.e.high & 0x01)==0)||(d.e.low > 0x7f) || (d.e.low < 0x4c)||( length > 1517))
    					{//����״̬�������һ���ݰ�����ʼҳ��ַ�������յ����ݰ�����>1500�ֽ�
       						page(1);
							DELAY_US(15);
							curr=Reg07; 	//page1
							DELAY_US(5);
							page(0);		//�л���page0
							DELAY_US(15);
        					bnry = curr -1;
        					if(bnry < 0x4c) 	bnry =0x7f;
        					Reg03=bnry; 	//write to bnry     
							DELAY_US(15);
        					Reg07=0xff;
							return(0);
              			}
//=============================================
            
     				else//��ʾ���ݰ�����õ�.��ȡʣ�µ�����
     					{
     						Temp = SwapWord(RxEthnetFrameBuffer[8]);		
        					if((Temp == Frame_IP)||(Temp == Frame_ARP))
								{ //Э��ΪIP��ARP�Ž���
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
                        			//================��ֹDMA����
                        			Reg0b=0x00;			//read count high   
									DELAY_US(5);
                        			Reg0a=0x00;			//read count low;
									DELAY_US(5);
                        			Reg00=0x22;			//���������DMA
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
          1. recbox�Ƕ�������һ�����ң�������
          2. ��Щ���ݻ��޸�һ����һЩ�������ͽ���������д��
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
    memcpy((TxEthnetFrameBuffer+ETH_HEADER_START+3),&MyMAC,3);//�иĶ�
    *(TxEthnetFrameBuffer+ETH_HEADER_START+6)=SwapWord(Frame_IP);
//IP
    *(TxEthnetFrameBuffer+IP_HEADER_START+0)=SwapWord(Ip_Edition);
    *(TxEthnetFrameBuffer+IP_HEADER_START+1)=SwapWord((TxUDPDataNum+IP_HEADER_SIZE+UDP_HEADER_SIZE)*2);//�޸�
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
    *(TxEthnetFrameBuffer+UDP_HEADER_START+1)=SwapWord(Remoteudpport);//��Զ�˶˿�
    *(TxEthnetFrameBuffer+UDP_HEADER_START+2)=SwapWord((TxUDPDataNum+UDP_HEADER_SIZE)*2);//�޸�
    *(TxEthnetFrameBuffer+UDP_HEADER_START+3)=0;

    CalcCkSum=CalcCheckSum((TxEthnetFrameBuffer+UDP_HEADER_START),(TxUDPDataNum+UDP_HEADER_SIZE),0,1);
    if(!CalcCkSum)
         CalcCkSum=0xFFFF;
    *(TxEthnetFrameBuffer+UDP_HEADER_START+3)=CalcCkSum;
    TxFrameSize=ETH_HEADER_SIZE+IP_HEADER_SIZE+UDP_HEADER_SIZE+TxUDPDataNum;   //�����Ҹ���
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

