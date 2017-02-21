#define		RTL8019BASE		0x4900

#define		Reg00	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x00)))
#define		Reg01	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x01)))
#define		Reg02	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x02)))
#define		Reg03	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x03)))
#define		Reg04	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x04)))
#define		Reg05	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x05)))
#define		Reg06	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x06)))
#define		Reg07	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x07)))
#define		Reg08	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x08)))
#define		Reg09	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x09)))
#define		Reg0a	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0A)))
#define		Reg0b	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0B)))
#define		Reg0c	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0C)))
#define		Reg0d	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0D)))
#define		Reg0e	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0E)))
#define		Reg0f	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x0F)))
#define		Reg10	(*((volatile	unsigned  int  *)(RTL8019BASE + 0x10)))


#define MY_TCP_PORT    	     1024   //RTL8019的TCP发送的端口
#define MY_UDP_PORT  	     1025   //RTL8019的UDP发送的端口

#define ETH_HEADER_START     0
#define IP_HEADER_START      7
#define ARP_HEADER_START     7
#define TCP_HEADER_START     17
#define UDP_HEADER_START     17
#define ICMP_HEADER_START    17
#define USER_DATA_START      27

#define RTL8019_HEADER_SIZE  2 
#define ETH_HEADER_SIZE      7
#define IP_HEADER_SIZE       10
#define TCP_HEADER_SIZE      10
#define UDP_HEADER_SIZE      4
#define ARP_FRAME_SIZE       14
#define ICMP_HEADER_SIZE     2
#define DUMMY_HEADER_SIZE    6
#define MY_MAX_SEG_SIZE      1460

#define Frame_ARP            0x0806
#define Frame_IP             0x0800
#define Ip_Edition           0x4500              //Ip 版本和IP首部长度
#define DEFUALT_TTL          128
#define ICMP_ECHO            8
#define ICMP_ECHO_REPLY      0
//ARP

#define HARDW_ETH            1
#define IP_HLEN_PLEN         0x0604
#define OP_ARP_REQUEST       1
#define OP_ARP_ANSWER        2

#define PROTOCOL_ICMP        1
#define PROTOCOL_TCP         6
#define PROTOCOL_UDP         17

/////TCP define

#define TCP_MAX_RE_TXDNUM    20

#define TCP_CODE_FIN         0x0001
#define TCP_CODE_SYN         0x0002
#define TCP_CODE_RST         0x0004
#define TCP_CODE_PSH         0x0008
#define TCP_CODE_ACK         0x0010
#define TCP_CODE_URG         0x0020

#define 	TCP_STATE_LISTEN        0
#define 	TCP_STATE_SYN_RCVD      1
#define 	TCP_STATE_SYN_SENT      2
#define 	TCP_STATE_ESTABLISHED   3
#define 	TCP_STATE_FIN_WAIT1     4
#define 	TCP_STATE_FIN_WAIT2     5
#define 	TCP_STATE_CLOSING       6
#define 	TCP_STATE_CLOSE_WAIT    7
#define 	TCP_STATE_LAST_ACK      8
#define 	TCP_STATE_CLOSED        9
#define 	TCP_STATE_TIME_WAIT     10

//分别表示发送的数据长度和电脑的接收端口，16个数据+1个头
#define     Datanum                 17
#define     Remoteudpport           1028

#define    SEND0    AdcMirror.ADCRESULT0
#define    SEND1    AdcMirror.ADCRESULT1
#define    SEND2    AdcMirror.ADCRESULT2
#define    SEND3    AdcMirror.ADCRESULT3
#define    SEND4    AdcMirror.ADCRESULT4
#define    SEND5    AdcMirror.ADCRESULT5
#define    SEND6    AdcMirror.ADCRESULT6
#define    SEND7    AdcMirror.ADCRESULT7
#define    SEND8    AdcMirror.ADCRESULT8
#define    SEND9   AdcMirror.ADCRESULT9
#define    SEND10   AdcMirror.ADCRESULT10
#define    SEND11   AdcMirror.ADCRESULT11
#define    SEND12   AdcMirror.ADCRESULT12
#define    SEND13   AdcMirror.ADCRESULT13
#define    SEND14   AdcMirror.ADCRESULT14
#define    SEND15   AdcMirror.ADCRESULT15

void	Init8019();
Uint16	RecFrame();
void 	ArpRequest(void);
Uint16  SwapWord(Uint16 Data);

void 	TCP_Listen(void);
void 	TCP_Syn_Rec(void);
void 	TCP_Syn_Sent(void);
void 	TCP_Established(void);
void 	TCP_Close_Wait(void);
void 	TCP_Last_Ack(void);
void 	DoNetworkStuff(void);
void 	TCPActiveTxData(void);
void 	RTL8019ActiveOpen(void);
void 	Prepare_ICMP_Answer(void);
void 	Prepare_TCP_Frame(Uint16 TCPCode);
void 	CopyFrameFromBE(Uint16 Offset,Uint16 Size);
void 	ProcessEthBroadcastFrame(void);

void    Prepare_UDP_Frame(Uint16 RemoteUdpPort,Uint16 TxUDPDataNum);
void    UDPActiveTxData(Uint16 t);//UDPActiveTxData(Uint16 t);//UDPActiveTxData(Uint32 i);//UDPActiveTxData(Uint16 i);//UDPActiveTxData(void);
void    Process_UDP_Frame(void);

void	SendFrame(Uint16 *TxdNetBuff,Uint16 length);
void 	WriteDWord(Uint16 *Address,Uint32 Data);
Uint16 	CalcCheckSum(Uint16 *Start, Uint16 Count, Uint16 IsTCP, Uint16 IsUDP);
void	SendFrame(Uint16 *TxdNetBuff,Uint16 length);
void 	Process_TCP_Timeout(void);
void 	TCP_Init(void);
void Process_TCP_Frame(void);


//========================== end ==========================
