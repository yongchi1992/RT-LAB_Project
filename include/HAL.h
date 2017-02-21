///////////////////////////hal.h//////////////////////////
#define  SL811_ADDR_PORT    (*(volatile Uint16 *)(0x48FB))
#define  SL811_DATA_PORT    (*(volatile Uint16 *)(0x48FF))

Uint16 SL811Read(Uint16 a);
void SL811Write(Uint16 a, Uint16 d);
void SL811BufRead(Uint16 addr, Uint16 *s, Uint16 c);
void SL811BufWrite(Uint16 addr, Uint16 *s, Uint16 c);
Uint16 WordSwap(Uint16 input);
void DelayMs(Uint16 nFactor);
Uint32 SwapINT32(Uint32 dData);
Uint16 SwapINT16(Uint16 dData);

Uint16 LSwapINT16(Uint16 dData1,Uint16 dData2);
Uint32 LSwapINT32(Uint32 dData1,Uint32 dData2,Uint32 dData3,Uint32 dData4);
