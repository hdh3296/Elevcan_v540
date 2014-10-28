/*****************************************
project :       elev    voice
name    :       you sang yong
date    :       1999,9,21
******************************************/

#include    <pic18.h>


#include        "..\..\system_com\memory_map.h"
#include        "..\comm_4480\iodef.h"
#include        "..\comm_4480\comdata.h"
#include        "..\comm_4480\setup.h"
//#include        "..\comm_4480\cpu18f4480.h"
//#include        "..\can_4480\you_can.h"



//#define	FLOOR_ANOUNCE	1	//101112 - B6층 적용할때는 이상한거 같음
//#define   BASE_FL			FLOOR_21
#define   END_FL			FLOOR_NO

//#define   PCI_GOGLE     	1   


#define  VOICE_ADR   A_VOI;


#define         VOICE_ON               0
#define         VOICE_OFF              1


#define         ON                     1
#define         OFF                    0

#define         DINGDONG                0
#define         UP_VOICE                1
#define         DOWN_VOICE              2
#define         HWAJAE_VOICE            3
#define         OVERLOAD_VOICE          4
#define         EMERGENCY_VOICE         5
#define         CLOSE_VOICE             6
#define         POWER_DOWN_VOICE        7
#define         FLOOR_U7                6  /*27c040*/ //100819,,,B7부터 하고싶으면 6->8로 수정하면 된다.
#define         FLOOR_U6                FLOOR_U7+1
#define         FLOOR_U5                FLOOR_U7+2	//8
#define         FLOOR_U4                FLOOR_U7+3	//9	
#define         FLOOR_U3                FLOOR_U7+4	//10
#define         FLOOR_U2                FLOOR_U7+5	//11
#define         FLOOR_U1                FLOOR_U7+6	//12
#define         FLOOR_1                 FLOOR_U7+7	//13
#define         FLOOR_2                 FLOOR_U7+8	//14
#define         FLOOR_3                 FLOOR_U7+9	//15
#define         FLOOR_4                 FLOOR_U7+10	//16
#define         FLOOR_5                 FLOOR_U7+11	//17
#define         FLOOR_6                 FLOOR_U7+12	//18
#define         FLOOR_7                 FLOOR_U7+13	//19
#define         FLOOR_8                 FLOOR_U7+14	//20
#define         FLOOR_9                 FLOOR_U7+15	//21
#define         FLOOR_10                FLOOR_U7+16	//22
#define         FLOOR_11                FLOOR_U7+17	//23
#define         FLOOR_12                FLOOR_U7+18	//24
#define         FLOOR_13                FLOOR_U7+19	//25
#define         FLOOR_14                FLOOR_U7+20	//26
#define         FLOOR_15                FLOOR_U7+21	//27
#define         FLOOR_16                FLOOR_U7+22	//28
#define         FLOOR_17                FLOOR_U7+23	//29
#define         FLOOR_18                FLOOR_U7+24	//30
#define         FLOOR_19                FLOOR_U7+25	//31
#define         FLOOR_20                FLOOR_U7+26	//32
#define         FLOOR_21                FLOOR_U7+27	//33
#define         FLOOR_22                FLOOR_U7+28	//34
#define         FLOOR_23                FLOOR_U7+29	//35
#define         FLOOR_24                FLOOR_U7+30	//36
#define         FLOOR_25                FLOOR_U7+31	//37
#define         FLOOR_26                FLOOR_U7+32	//38
#define         FLOOR_27                FLOOR_U7+33	//39
#define         FLOOR_G                 FLOOR_U7+34	//40
#define         FLOOR_M                 FLOOR_U7+35	//41
#define         FLOOR_L                 FLOOR_U7+36	//42
#define         FLOOR_PH                FLOOR_U7+37	//43
#define         FLOOR_NO                FLOOR_U7+38	//44
#define         FLOOR_B5          		FLOOR_U7+39	//45
#define         FLOOR_B4          		FLOOR_U7+40	//46
#define         FLOOR_B3          		FLOOR_U7+41	//47
#define         FLOOR_B2          		FLOOR_U7+42	//48
#define         FLOOR_B1          		FLOOR_U7+43	//49
#define         FLOOR_F1          		FLOOR_U7+44	//50
#define         FLOOR_F2          		FLOOR_U7+45	//51
#define         FLOOR_F3          		FLOOR_U7+46	//52
#define         FLOOR_F4          		FLOOR_U7+47	//53
#define         FLOOR_F5          		FLOOR_U7+48	//54
#define         FLOOR_F6          		FLOOR_U7+49	//55
#define         FLOOR_F7          		FLOOR_U7+50	//56
#define         FLOOR_F8          		FLOOR_U7+51	//57
#define         FLOOR_F9          		FLOOR_U7+52	//58
#define         FLOOR_F10         		FLOOR_U7+53	//59
#define         FLOOR_F11          		FLOOR_U7+54	//60
#define         FLOOR_F12          		FLOOR_U7+55	//61
#define         FLOOR_F13          		FLOOR_U7+56	//62
#define         FLOOR_F14          		FLOOR_U7+57	//63
#define         FLOOR_F15          		FLOOR_U7+58	//64
#define         FLOOR_F16          		FLOOR_U7+59	//65
#define         FLOOR_F17          		FLOOR_U7+60	//66
#define         FLOOR_F18          		FLOOR_U7+61	//67
#define         FLOOR_F19          		FLOOR_U7+62	//68
#define         FLOOR_F20         		FLOOR_U7+63	//69
#define         FLOOR_F21          		FLOOR_U7+64	//70
#define         FLOOR_F22          		FLOOR_U7+65	//71
#define         FLOOR_F23          		FLOOR_U7+66	//72
#define         FLOOR_F24          		FLOOR_U7+67	//73
#define         FLOOR_F25          		FLOOR_U7+68	//74
#define         FLOOR_F26          		FLOOR_U7+69	//75
#define         FLOOR_F27          		FLOOR_U7+70	//76
#define         FLOOR_PARKING      		FLOOR_U7+71	//77
#define         OPEN_VOICE      		FLOOR_U7+72	//78
#define         CANCLE_VOICE      		FLOOR_U7+73	//79
#define         PUSH_VOICE      		FLOOR_U7+74	//80
#define         FLOOR_S            		FLOOR_U7+75	//81
#define         FLOOR__END            	FLOOR_U7+76	//82



#define   		TEST_MODE     RD4     //in    
#define   		MASTER_MODE   RD5     //in
#define   		LOCAL0        RD6     //in    
#define   		LOCAL1        RD7     //in    
////////////////#define   		MASTER_MODE   RD5     //in

#define   		POWER_DOWN    RA4     //in              
//#define   		BUSY          RA0     //in
#define   		BUSY          RA3     //in

#define   		SEN           LATA1   //out
#define   		SI            LATA2   //out
#define   		BATTERY       LATA5   //out           
#define   		V_LAMP        LATE1   //out           
#define   		SCK           LATE2   //out
#define   		VoiceAct      LATE0   //out



volatile const unsigned char FloorChar[] = {"B5B4B3B2B10102030405060708091011121314151617181920212223242526272829303132"}; 
   
unsigned char new_buf[64];	                                	    /*unlike the old_text this is not a CONST -> stored in data RAM */
far unsigned char * source_ptr_1 = (far unsigned char *)new_buf;    /*pointers to data*/
far unsigned char * dest_ptr_1 = (far unsigned char *)FloorChar;
unsigned char sizex = 64;						

            
unsigned    char     delay;
unsigned    char     CurFloor;
unsigned    char     floor;
unsigned    char     CurVoice;
unsigned    char     SelVoice;
unsigned    char     PlaySeq;
unsigned    char     RunPgm;
unsigned    char     BeforeVoice;
unsigned    char     HwajaeVoiceCnt;
unsigned    char     OverLoadVoiceCnt;
unsigned    char     EmergencyVoiceCnt;
unsigned    char     UpDnVoice;
unsigned    char     MyAddress;        
unsigned    char     MyLogAdr;        
unsigned    char     src;
unsigned    char     firstdata;
unsigned    char     seconddata;
unsigned    char     TimeOutBd=0;
unsigned    char     CallMeAdr=0;

unsigned    char     BefCarKey[4]={0,0,0,0};
unsigned    char     CurCarKey[4]={0,0,0,0};

unsigned    char     BefFloorX;
unsigned    char     FloorX;
unsigned    char     ButtonStatus;
unsigned    char     FloorXCnt;


#ifdef	PCI_GOGLE
unsigned    char     Message=0;
#endif

/*
Error[000]   : _SetupDisplay (C:\micom\project\elevcan\dot_lamp\setup.obj)
Error[000]   : _DspModel (C:\micom\project\elevcan\dot_lamp\setup.obj)
*/

unsigned    char  shiftTime;
unsigned    char  MainTimer=0;
unsigned    char  UpButtonTime=0;
unsigned    char  DnButtonTime=0;
unsigned    char  DspModel=0;
unsigned    int   CloseVoiceTime=0;

unsigned    char     UpDnVoiceTime=0;
unsigned    char     abctimer=0;

unsigned    char     BefFlr=0;
unsigned    char     BefFlrTime=0;



bit   FDsp;
bit   UpKeyBit;
bit   DnKeyBit;



bit   BatteryRun;
bit   Flow_Active;
bit   valid_key;
bit   active_key;        
bit   updown_valid;        
bit   flow_valid;        
bit   VoiceRun;
bit   CarMove;


bit   testbit;
bit   bCloseVoice;



bit   byou;

//bit   bUp=0;
//bit   bDn=0;



/*
void    Wait(unsigned char   x)
{
   delay=0;
   while(delay<x);
}
*/




#define dMLC108x_CMD_STOP					0x0000
/* Play Phrase */
#define dMLC108x_CMD_PLAY_PHRASE			0x8000
#define dMLC108x_REPEAT_1_TIME				0x0000
#define dMLC108x_REPEAT_2_TIME				0x0800
#define dMLC108x_REPEAT_4_TIME				0x1000
#define dMLC108x_REPEAT_INFINITE			0x1800
/* Play Phrase Group */
#define dMLC108x_CMD_PLAY_PHRASE_GROUP		0xA000
#define dMLC108x_REPEAT_1_TIME_GROUP		0x0000
#define dMLC108x_REPEAT_2_TIME_GROUP		0x0800
#define dMLC108x_REPEAT_4_TIME_GROUP		0x1000
#define dMLC108x_REPEAT_INFINITE_GROUP		0x1800
/*Play Beep Sound*/
#define dMLC108x_CMD_BEEP_SOUND				0xC000
#define dMLC108x_REPEAT_1_TIME_BEEP			0x0000
#define dMLC108x_REPEAT_2_TIME_BEEP			0x0800
#define dMLC108x_REPEAT_4_TIME_BEEP			0x1000
#define dMLC108x_REPEAT_INFINITE_BEEP		0x1800
#define dMLC108x_BEEP_800HZ					0x0000
#define dMLC108x_BEEP_1000HZ				0x0008
#define dMLC108x_BEEP_1333HZ				0x0010
#define dMLC108x_BEEP_2000HZ				0x0018
#define dMLC108x_BEEP_32MS					0x0000
#define dMLC108x_BEEP_64MS					0x0001
#define dMLC108x_BEEP_128MS					0x0002
#define dMLC108x_BEEP_192MS					0x0003
#define dMLC108x_BEEP_256MS					0x0004
#define dMLC108x_BEEP_384MS					0x0005
#define dMLC108x_BEEP_512MS					0x0006
#define dMLC108x_BEEP_1024MS				0x0007
/*Play Silence*/
#define dMLC108x_CMD_SILENCE				0xE000
#define dMLC108x_REPEAT_1_TIME_SILENCE		0x0000
#define dMLC108x_REPEAT_2_TIME_SILENCE		0x0800
#define dMLC108x_REPEAT_4_TIME_SILENCE		0x1000
#define dMLC108x_REPEAT_INFINITE_SILENCE	0x1800
#define dMLC108x_SILENCE_32MS				0x0000
#define dMLC108x_SILENCE_64MS				0x0001
#define dMLC108x_SILENCE_128MS				0x0002
#define dMLC108x_SILENCE_192MS				0x0003
#define dMLC108x_SILENCE_256MS				0x0004
#define dMLC108x_SILENCE_384MS				0x0005
#define dMLC108x_SILENCE_512MS				0x0006
#define dMLC108x_SILENCE_1024MS				0x0007
/* System Set up Command*/
/*Memory Select*/
#define dMLC108x_CMD_MEMORY_SEL				0x4000
#define dMLC108x_MEMORY_NORFLASH			0x0000
#define dMLC108x_MEMORY_SERIALFLASH			0x0001
/*Operation Select*/
#define dMLC108x_CMD_OP_MODE				0x4100
#define dMLC108x_NOMAL_MODE					0x0001
#define dMLC108x_DDP_MODE					0x0002
#define dMLC108x_INTERNAL_WRITE_MODE		0x0003
#define dMLC108x_STANDBY_MODE				0x0004
/*Clock Select*/
#define dMLC108x_CMD_CLOCK_SEL				0x4200
#define dMLC108x_CLOCK_512KZ				0x0000
#define dMLC108x_CLOCK_4096MHZ				0x0001
/*Volume Select */
#define dMLC108x_CMD_VOLUME					0x4300
#define dMLC108x_CMD_MUTE					0x0000
#define dMLC108x_CMD_2408DB					0x0001 //-24.08DB
#define dMLC108x_CMD_2056DB					0x0002 //-20.56DB
#define dMLC108x_CMD_1806DB					0x0003 //-18.06DB
#define dMLC108x_CMD_1612DB					0x0004 //-16.12DB
#define dMLC108x_CMD_1454DB					0x0005 //-14.54DB
#define dMLC108x_CMD_1320DB					0x0006 //-13.20DB
#define dMLC108x_CMD_1204DB					0x0007 //-12.04DB
#define dMLC108x_CMD_1102DB					0x0008 //-11.02DB
#define dMLC108x_CMD_1010DB					0x0009 //-10.10DB
#define dMLC108x_CMD_0927DB					0x000A //- 9.27DB
#define dMLC108x_CMD_0852DB					0x000B //- 8.52DB
#define dMLC108x_CMD_0782DB					0x000C //- 7.82DB
#define dMLC108x_CMD_0718DB					0x000D //- 7.18DB
#define dMLC108x_CMD_0658DB					0x000E //- 6.58DB
#define dMLC108x_CMD_0602DB					0x000F //- 6.02DB
#define dMLC108x_CMD_05490B					0x0010 //- 5.49DB
#define dMLC108x_CMD_0500DB					0x0011 //- 5.00DB
#define dMLC108x_CMD_0453DB					0x0012 //- 4.53DB
#define dMLC108x_CMD_0408DB					0x0013 //- 4.08DB
#define dMLC108x_CMD_0366DB					0x0014 //- 3.66DB
#define dMLC108x_CMD_0325DB					0x0015 //- 3.25DB
#define dMLC108x_CMD_0287DB					0x0016 //- 2.87DB
#define dMLC108x_CMD_0250DB					0x0017 //- 2.50DB
#define dMLC108x_CMD_0214DB					0x0018 //- 2.14DB
#define dMLC108x_CMD_0180DB					0x0019 //- 1.80DB
#define dMLC108x_CMD_0148DB					0x001A //- 1.48DB
#define dMLC108x_CMD_0116DB					0x001B //- 1.16DB
#define dMLC108x_CMD_0085DB					0x001C //- 0.85DB
#define dMLC108x_CMD_0056DB					0x001D //- 0.56DB
#define dMLC108x_CMD_0028DB					0x001E //- 0.28DB
#define dMLC108x_CMD_0000DB					0x001F //- 0DB
/*DAC POWER DOWN MODE*/
#define dMLC108x_CMD_DAC_PD					0x4600
#define dMLC108x_DAC_POWER_UP				0x0000
#define dMLC108x_AUTO_DAC_POWER				0x0001
#define dMLC108x_DAC_POWER_DOWN				0x0002



int MLC108x_WriteCommand(unsigned int cmd16 );


///
unsigned	long    SumAD=0;
unsigned 	int	    InPutAD = 0;
unsigned 	int	    ADBuf = 0;
unsigned	int	    SumCnt=0;
unsigned    char    AdSel=0;
unsigned    char    OneLoop=0;

unsigned	int	    CurVoltage=0;  // 500 ==5.00v
unsigned	int	    BefCurVoltage=0;  // 500 ==5.00v

bit   	bAdConversion=0;

void	AnlogInit(void)
{
	ADCON0=0x01;
	ADCON1=0x0E;  
    ADCON2=0x96;  // right just
	ADFM=1;		  // period is an 8 bit value, right justify to get result from ADRESH 

	ADIP=0;
	ADIF=0;
	ADIE=1;	
	GODONE=1;
}



void ADRead(void)
{
/*
    unsigned long LongBuf;
    unsigned int i;
//	unsigned int variable=55;
//	unsigned char	tmpTh1,tmpTh2;

	i=204;	
	LongBuf=(unsigned long)InPutAD;	
	if(LongBuf > 0){
		LongBuf=(LongBuf * 100);
		LongBuf=(LongBuf / i);
	}
	CurVoltage=(unsigned int)LongBuf;
*/
	InPutAD=(InPutAD >> 6);
	MLC108x_WriteCommand(dMLC108x_CMD_VOLUME | InPutAD);

    
    
	switch(AdSel){
		case    0:
/*				
			if(LongBuf > 2050)	variable=67;
			LongBuf = (LongBuf * variable);
			LongBuf = (LongBuf/1000);
			CurCt=(unsigned char)LongBuf;
			CurCurrentSet(CurCt);
*/
			CHS2=0;
			CHS1=0;
			CHS0=0;
			AdSel=0;
			break;
		default:				
			CHS2=0;
			CHS1=0;
			CHS0=0;
			AdSel=0;
			break;
	}
}


unsigned char	ADConversionChk(void)
{
	if(bAdConversion){
		SumCnt++;	
		SumAD=SumAD + (unsigned long)ADBuf; 		
		if(SumCnt > 10){
			if(SumAD>0){	
				InPutAD=(unsigned int)(SumAD/SumCnt);				
			}
			else{
				InPutAD=0;
			}
			ADRead();
			SumCnt=0;	
			SumAD=0;
		}

		bAdConversion=0;
		GODONE=1;
	}
	return(0);
}



void    Sw_Delay(void)
{
    unsigned char j;
    for(j=0;j<10;j++);
}



int MLC108x_WriteCommand(unsigned int cmd16 )
{
	unsigned int temp16;
	unsigned int i;
//	uint8_t i;
	
    SCK=1;
   	SEN=0;
	Sw_Delay();

//	SIENB_LOW();
//	delay32Us(0, 10);

	for( i= 0; i <= 15; i++ ){
		SCK=0;
		temp16 = ((cmd16 <<i) & 0x8000);
		if(temp16)	SI=1;
		else		SI=0;
		SCK=1;


/*
		SCLK_LOW();
		temp16 = ((cmd16 <<i)&0x8000);
		if( temp16 ){
			SI_HIGH();
		}else{
			SI_LOW();
		}
		SCLK_HIGH();
*/
	}
	Sw_Delay();
   	SEN=1;
//	delay32Us(0, 10);
//	SIENB_HIGH();
	return(1);
}



void    InitMLC108x(void)
{
	unsigned int i;

	MLC108x_WriteCommand(dMLC108x_CMD_CLOCK_SEL | dMLC108x_CLOCK_4096MHZ);
//	delay32Ms(0, 75);				// Delay 75ms
	for(i=0;i<530;i++){
		Sw_Delay();
		CLRWDT();
	}

	MLC108x_WriteCommand(dMLC108x_CMD_OP_MODE | dMLC108x_NOMAL_MODE);
	MLC108x_WriteCommand(dMLC108x_CMD_MEMORY_SEL | dMLC108x_MEMORY_SERIALFLASH);
	MLC108x_WriteCommand(dMLC108x_CMD_VOLUME | dMLC108x_CMD_0000DB);
	MLC108x_WriteCommand(dMLC108x_CMD_DAC_PD | dMLC108x_DAC_POWER_UP);
	MLC108x_WriteCommand(dMLC108x_CMD_STOP);
//	while(GPIOGetValue(PORT3, 0));	// Busy Check
	while(BUSY)	  CLRWDT();
}



void Play(void)
{

	if(CurVoice >= FLOOR__END){
		MLC108x_WriteCommand(dMLC108x_CMD_STOP);
	}
	else{
		MLC108x_WriteCommand(dMLC108x_CMD_STOP);
		while(BUSY);	// Busy Check
		MLC108x_WriteCommand(dMLC108x_CMD_PLAY_PHRASE | CurVoice);
	}

}


            

void    SetupDisplayES15(unsigned char mdata,unsigned char mode)
{
}

void  SetupDisplay(unsigned char ft,unsigned char sd)
{
}



unsigned char SyncButtonCheck(void)
{
	return(0);
}

void    MyLampCheck(void)
{
}



/*
void DspCharRdWr(unsigned char id)
{
    unsigned int    IdPt;
    unsigned int    i;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;


	if((RcvBuf[IdPt+S0_FLOOR] == 1) && (RcvBuf[IdPt+S1_STATE] & S1_UP) ){
		bCharCheckStart=1;		
	}
	
	if(bCharCheckStart){
		i=(RcvBuf[IdPt+S0_FLOOR]-1) * 2;
		new_buf[i+0] = RcvBuf[IdPt+DSP1];
		new_buf[i+1] = RcvBuf[IdPt+DSP2];
		
		if(RcvBuf[IdPt+S2_STATE] & S2_DN){
	    	flash_write(source_ptr_1,sizex,dest_ptr_1);
			bCharCheckStart=0;
		}
	}
}
*/


unsigned char DspCharRdWr(unsigned char id)
{
    unsigned int    IdPt;
//    unsigned int    i;
    unsigned char   ThisCurFlr;

//	bCharCheckStart=0;		

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;


	ThisCurFlr=(RcvBuf[IdPt+S0_FLOOR]);
	if(ThisCurFlr > 32)	return(0);
	if(ThisCurFlr < 1 )	return(0);

	ThisCurFlr = (ThisCurFlr-1);

	if(BefFlr == ThisCurFlr){
		BefFlrTime=0;
	}
	else{
		if(BefFlrTime > 3){
			BefFlr = ThisCurFlr;
			ThisCurFlr=(ThisCurFlr*2);
			BefFlrTime=0;

			if( (RcvBuf[IdPt+DSP1] != FloorChar[ThisCurFlr]) || (RcvBuf[IdPt+DSP2] != FloorChar[ThisCurFlr+1]) ){
				new_buf[ThisCurFlr+0] = RcvBuf[IdPt+DSP1];
				new_buf[ThisCurFlr+1] = RcvBuf[IdPt+DSP2];
			    flash_write(source_ptr_1,sizex,dest_ptr_1);
			}  
		}
	}

	return(0);
}




void    HextoASCIIByte(void)
{
   unsigned char   i;

   i=(src & 0xf0) >> 4;
   if(i<0x0a)   i= i + '0';
   else         i= i + '7';   
   firstdata=i;    
   
   i=(src & 0x0f);
   if(i<0x0a)   i= i + '0';
   else         i= i + '7';
   seconddata=i;        
}


/*
int    SlaveTx(void)
{
   RxBuffer[0]=ACK;

   src=GROUP_ID;   
   HextoASCIIByte();
   RxBuffer[1]=firstdata;
   RxBuffer[2]=seconddata;

   src=MyLogAdr;   
   HextoASCIIByte();
   RxBuffer[3]=firstdata;
   RxBuffer[4]=seconddata;
   
   src=MyAddress;   
   HextoASCIIByte();
   RxBuffer[5]=firstdata;
   RxBuffer[6]=seconddata;
   
   src=NO_DATA;   
   HextoASCIIByte();
   RxBuffer[7]=firstdata;
   RxBuffer[8]=seconddata;


   RxBuffer[9]=ETX;
   RxBuffer[10]=0;

   TX_EN=0;
   Serial();
   
   return(1);
}


void    Req_Logic_Adr(unsigned char Absadr,unsigned char Logadr,unsigned char cmd)
{

   RxBuffer[0]=ENQ;

   src=GROUP_ID;   
   HextoASCIIByte();
   RxBuffer[1]=firstdata;
   RxBuffer[2]=seconddata;

   src=Logadr;   
   HextoASCIIByte();
   RxBuffer[3]=firstdata;
   RxBuffer[4]=seconddata;
   
   src=Absadr;   
   HextoASCIIByte();
   RxBuffer[5]=firstdata;
   RxBuffer[6]=seconddata;

   src=cmd;   
   HextoASCIIByte();
   RxBuffer[7]=firstdata;
   RxBuffer[8]=seconddata;

   src=0;                        //cmdtype   
   HextoASCIIByte();
   RxBuffer[9]=firstdata;
   RxBuffer[10]=seconddata;


   src=0;   
   HextoASCIIByte();
   RxBuffer[11]=firstdata;
   RxBuffer[12]=seconddata;

   src=0;   
   HextoASCIIByte();
   RxBuffer[13]=firstdata;
   RxBuffer[14]=seconddata;
   
   src=0;                     //data cnt
   HextoASCIIByte();
   RxBuffer[15]=firstdata;
   RxBuffer[16]=seconddata;

   RxBuffer[17]=ETX;
   RxBuffer[18]=0;
   
   TX_EN=0;
   Serial();
   
}
*/

/*
void    Req_Logic_Adr(unsigned char Absadr,unsigned char Logadr,unsigned char cmd)
{
   RxBuffer[0]=ENQ;

   src=cmd;   
   HextoASCIIByte();
   RxBuffer[1]=firstdata;
   RxBuffer[2]=seconddata;

   src=GROUP_ID;   
   HextoASCIIByte();
   RxBuffer[3]=firstdata;
   RxBuffer[4]=seconddata;

   src=Logadr;   
   HextoASCIIByte();
   RxBuffer[5]=firstdata;
   RxBuffer[6]=seconddata;
   
   src=Absadr;   
   HextoASCIIByte();
   RxBuffer[7]=firstdata;
   RxBuffer[8]=seconddata;

   RxBuffer[9]='0';
   RxBuffer[10]='0';
   RxBuffer[11]=ETX;
   RxBuffer[12]=0;
   
   TX_EN=0;
   Serial();
}



int    SlaveTx(void)
{

   RxBuffer[0]=ACK;

   src=WRITE_DATA;   
   HextoASCIIByte();
   RxBuffer[1]=firstdata;
   RxBuffer[2]=seconddata;

   src=GROUP_ID;   
   HextoASCIIByte();
   RxBuffer[3]=firstdata;
   RxBuffer[4]=seconddata;

   src=MyLogAdr;   
   HextoASCIIByte();
   RxBuffer[5]=firstdata;
   RxBuffer[6]=seconddata;
   
   src=MyAddress;   
   HextoASCIIByte();
   RxBuffer[7]=firstdata;
   RxBuffer[8]=seconddata;
   
   RxBuffer[9]='0';
   RxBuffer[10]='A';

   src='0';   
   HextoASCIIByte();
   RxBuffer[11]=firstdata;
   RxBuffer[12]=seconddata;
   
   src='0';   
   HextoASCIIByte();
   RxBuffer[13]=firstdata;
   RxBuffer[14]=seconddata;

   RxBuffer[15]=ETX;
   
   RxBuffer[16]=0;

   TX_EN=0;
   Serial();
   
   return(1);
}
*/

/*
int    Plc_Read(void)
{

        unsigned int    base_memory;
        unsigned char   base_m_low;
        unsigned char   base_m_high;

        base_memory = (unsigned int)(BASE_MEMORY);
        base_m_low  = (unsigned char)(base_memory);
        base_m_high = (unsigned char)(base_memory>>8);

        RxBuffer[0]=PLC_ADDRESS;
        RxBuffer[1]=MASTER_ADDRESS;
        RxBuffer[2]=0x23;
         RxBuffer[3]=0x03;
        RxBuffer[4]=base_m_low;
        RxBuffer[5]=base_m_high;
        RxBuffer[6]=0x03;

        TX_ENABLE=0;
        Serial();
        TX_ENABLE=1;

        return(0);
}
*/

void    Wait(void)
{
    unsigned char j;
    for(j=0;j<10;j++);
}


/*
void    Play(void)
{

   unsigned char   temp;
   unsigned char   i;

    SEN=1;

    SCK=0;

    Wait();

   if(CurVoice==0xff)      temp=0x40;
   else                    temp=0xb0;

   SEN=0;
   Wait();

   for(i=0;i<8;i++){
      SCK=0;
      SI=0;
        Wait();

      if(0x80 & temp){
         SI=1;
        Wait();
      }
      SCK=1;
    Wait();
      temp=temp<<1;
   }

   temp=CurVoice;

   for(i=0;i<8;i++){
      SCK=0;
      SI=0;
    Wait();
      if(0x80 & temp){
         SI=1;
        Wait();
      }
      SCK=1;
        Wait();
      temp=temp<<1;
   }
   SEN=1;   
    Wait();
}
*/


void    Stop_Play(void)
{
   unsigned char temp;
   temp=CurVoice;
   CurVoice=0xff;

   Play();

   CurVoice=temp;   
}



void    Manual_Play(void)
{

   CurVoice=0;
   delay=0;
   VoiceAct=VOICE_ON;

   for(;1;){  
      CLRWDT();
		ADConversionChk();
        
      if(!BUSY){
         if(delay>200){
            Play();
            CurVoice++;
            if(CurVoice>100)     CurVoice=0;
            delay=0;
         }
      }
      else{
        delay=0;
      }
      
      if(BUSY)  V_LAMP=0;
      else      V_LAMP=1;
   }   
}




#ifdef	FLOOR_ANOUNCE

unsigned char   CarButton_Voice_Valid_Chk(unsigned char flr,unsigned char k)
{
	if(!(BefCarKey[flr] & k))				return(0); 
//	if( flr == (FloorX-1))					return(0); 
	if( ButtonStatus & S2_EXT_BUT_CLR)	return(0);
	if( ButtonStatus & S2_CAR_BUT_CLR)	return(0);

	if(FloorXCnt < 5)	return(0);

/*

	if(BefFloorX != FloorX){
		FloorXCnt=0;
		return(0);
	}
	else{	
		if(FloorXCnt<200)	FloorXCnt++;
		if(FloorXCnt < 10)	return(0);
	}	
*/

	return(1);
}


void    CarButton_Voice_Chk(unsigned char dsp_pt)
{
    unsigned int    IdPt;
    unsigned char   f,i,valid;

/*
    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;


	CurCarKey[0]=RcvBuf[IdPt+SL_mCarKey1];
	CurCarKey[1]=RcvBuf[IdPt+SL_mCarKey9];
	CurCarKey[2]=RcvBuf[IdPt+SL_mCarKey17];
	CurCarKey[3]=RcvBuf[IdPt+SL_mCarKey25];
*/
   

   	valid=1;

	i=(dsp_pt * 2); 

   	f=FloorChar[i + 0];
   	if(f == 'B'){
      	floor=FLOOR_F1;    
   	}
	else if(f == 'P'){
      	floor=FLOOR_F1;    
   	}
   	else if(f == '0'){
      	floor=FLOOR_B1;   
   	}
   	else if(f == '1'){
      	floor=10+FLOOR_B1;   
   	}
   	else if(f == '2'){
    	floor=20+FLOOR_B1;   
   	}
   	else if(f == '3'){
      	floor=30+FLOOR_B1;   
   	}
   	else{
     	floor=(RcvBuf[IdPt] | 0x80);
     	valid=0;
   	}     
   
   	if(valid){
   		f=FloorChar[i + 1];
      	if(f == '0'){
         	if(floor < (10+FLOOR_B1)) floor=0xfe;   
      	} 
      	else if(f == 'F'){
         	floor=(floor + 4);
      	}
      	else if(f == 'G'){
         	floor=FLOOR_G;
      	} 
      	else if(f == 'M'){
         	floor=FLOOR_M;
      	}
      	else if(f == 'H'){
         	floor=FLOOR_PH;
      	} 
      	else if((f >= '1') && (f <= '9')){
         	if(floor == FLOOR_F1) floor=floor-(f -'0');         
         	else                  floor=floor+(f -'0');   
      	} 
      	else  floor=0xfe;        
   	}      

   	CurVoice=floor;
   	CurFloor=floor;
}


unsigned char	FloorAnounce(void)
{

	unsigned char i,j,k;

	if(SelVoice == 0xff){
		k=0x01;
		j=0;
		for(i=0;i<32;i++){
			if(CurCarKey[j] != BefCarKey[j]){
				if(CurCarKey[j] & k){
					if(!(BefCarKey[j] & k) ){
						CarButton_Voice_Chk(i);
						BefCarKey[j] = (BefCarKey[j] | k);

//						BefFloorX=FloorX;
						return(0);
					}
				}
				else{
					if(CarButton_Voice_Valid_Chk(j,k) && (i != (FloorX-1)) ){
						BefCarKey[j] = (BefCarKey[j] & ~k);
					   	CurVoice=CANCLE_VOICE;
					   	CurFloor=CANCLE_VOICE;
//						BefFloorX=FloorX;
						return(0);
					}

					BefCarKey[j] = (BefCarKey[j] & ~k);
				}

				k = (k << 1);
				if(k == 0){
					j++;
					k=0x01;
				}
			}
			else{
				j++;
				k=0x01;
				i=(i + 7);
			}
		}
	}

//	BefFloorX=FloorX;

	return(0);
}	                   

#endif




void    Serial_Flow_Voice_Chk(unsigned char id)
{
    unsigned int    IdPt;
    unsigned char f,valid;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;


	CurCarKey[0]=RcvBuf[IdPt+SL_mCarKey1];
	CurCarKey[1]=RcvBuf[IdPt+SL_mCarKey9];
	CurCarKey[2]=RcvBuf[IdPt+SL_mCarKey17];
	CurCarKey[3]=RcvBuf[IdPt+SL_mCarKey25];

   
	FloorX=RcvBuf[IdPt];

	if(BefFloorX != FloorX){
		FloorXCnt=0;
		BefFloorX = FloorX;
	}


	ButtonStatus=RcvBuf[IdPt+2];

   valid=1;
   
   f=RcvBuf[IdPt+DSP1];
   if(f == 'B'){
      floor=FLOOR_1;    
   }
   else if(f == 'P'){
      floor=FLOOR_1;    
   }
   else if(f == '0'){
      floor=FLOOR_U1;   
   }
   else if(f == '1'){
      floor=10+FLOOR_U1;   
   }
   else if(f == '2'){
      floor=20+FLOOR_U1;   
   }
   else if(f == '3'){
      floor=30+FLOOR_U1;   
   }
   else{
     floor=(RcvBuf[IdPt] | 0x80);
     valid=0;
   }     
   
   if(valid){
      f=RcvBuf[IdPt+DSP2];      
      if(f == '0'){
         if(floor < (10+FLOOR_U1)) floor=0xfe;   
      } 
      else if(f == 'F'){
         floor=(floor + 4);
      }
      else if(f == 'G'){
         floor=FLOOR_G;
      } 
      else if(f == 'M'){
         floor=FLOOR_M;
      }
      else if(f == 'H'){
         	floor=FLOOR_PH;
      } 
      else if((f >= '1') && (f <= '9')){
         if(floor == FLOOR_1) floor=floor-(f -'0');         
         else                 floor=floor+(f -'0');   
      } 
      else  floor=0xfe;        
   }      


/*

   f=RcvBuf[IdPt+DSP1];
   
   if(f == 'B'){
      floor=FLOOR_1;    
   }
   else if(f == '0'){
      floor=FLOOR_U1+2;   
   }
   else if(f == '1'){
      floor=10+FLOOR_U1+2;   
   }
   else if(f == '2'){
      floor=20+FLOOR_U1+2;   
   }
   else if(f == '3'){
      floor=30+FLOOR_U1+2;   
   }
   else{
     floor=(RcvBuf[IdPt] | 0x80);
     valid=0;
   }     
   
   if(valid){
      f=RcvBuf[IdPt+DSP2];      
      if(f == '0'){
         if(floor < (10+FLOOR_U1+2)) floor=0xfe;   
      } 
      else if(f == 'F'){
         floor=(floor + 4);
      } 
      else if(f == 'G'){
         floor=FLOOR_1;
      } 
      else if(f == 'M'){
         floor=FLOOR_2;
      } 
      else if((f >= '1') && (f <= '9')){
         if(floor == FLOOR_1) floor=floor-(f -'0');         
         else                 floor=floor+(f -'0');   
      } 
      else  floor=0xfe;        
   }      

*/


/*
//G
   f=RcvBuf[IdPt+DSP2];
   
   if(f == 'B'){
      floor=FLOOR_U1;    
   }
   else if(f == 'G'){
      floor=FLOOR_1;    
   }      
   else if(f == '1'){
      floor=FLOOR_2;   
   }
   else if(f == '2'){
      floor=FLOOR_3;   
   }
   else if(f == '3'){
      floor=FLOOR_4;   
   }
   else if(f == '4'){
      floor=FLOOR_5;   
   }
   else if(f == '5'){
      floor=FLOOR_6;   
   }
   else if(f == '6'){
      floor=FLOOR_7;   
   }
   else if(f == '7'){
      floor=FLOOR_8;   
   }
   else if(f == '8'){
      floor=FLOOR_9;   
   }
   else if(f == '9'){
      floor=FLOOR_10;   
   }

//G
*/


/*
   	f=RcvBuf[IdPt+S0_FLOOR];
//   	floor=FLOOR_U5 + f;   
    floor=POWER_DOWN_VOICE+f;
*/

	if(RcvBuf[IdPt+1] & 0x20){
    	if(RcvBuf[IdPt+2] & 0x08){
        	if((floor != CurFloor) && !flow_valid){
            	CurVoice=floor;
            	CurFloor=floor;
            	flow_valid=1;
         	}
			else{
				#ifdef	FLOOR_ANOUNCE
				FloorAnounce();	                   
				#endif              
			}
      	}
		else{
  			flow_valid=0;
			#ifdef	FLOOR_ANOUNCE
			FloorAnounce();	     
			#endif              
		}
	}
   	else{
    	if(floor != CurFloor){
        	CurVoice=floor;
         	CurFloor=floor;
      	}      
   	}              
}


unsigned char	Serial_Status_Voice_Check(unsigned char id)
{
    unsigned int    IdPt;
    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;

	if(RcvBuf[IdPt+4] & S4_PARKING_READY)	return(0);	



   if(!(RcvBuf[IdPt+1] & 0x20)){		//manual
      if(RcvBuf[IdPt+2] & 0x02){
         if(!updown_valid){
            if((UpDnVoice != UP_VOICE) && (RcvBuf[IdPt+1] & 0x80)){
               CurVoice=UpDnVoice=UP_VOICE;
               updown_valid=1;                                
            }
            if((UpDnVoice != DOWN_VOICE) && (RcvBuf[IdPt+2] & 0x01)){
               CurVoice=UpDnVoice=DOWN_VOICE;                                
               updown_valid=1;                                
            }
         }       
      }
      else{
         UpDnVoice=0;
         updown_valid=0;                                      
      }                     
      testbit=0;
   }
   else{
///////////////////////////Door Open 적용>>>>>

		if( (UpDnVoiceTime > 50) && (RcvBuf[IdPt+1] & 0x01) && !updown_valid && (byou==0)){  		
	         if((RcvBuf[IdPt+1] & 0x80)){
	            CurVoice=UP_VOICE;
	            updown_valid=1;                                
	         }
	         if((RcvBuf[IdPt+2] & 0x01)){
	            CurVoice=DOWN_VOICE;                                
	            updown_valid=1;                                
	         }            
      	}     


		if( !(RcvBuf[IdPt+2] & S2_CAR_MOVE)){
			if((RcvBuf[IdPt + 21 ] == 57) && (byou==1) && !VoiceRun){  //open
		        //CurVoice=OPEN_VOICE;	//101112 - 문이열림이 필요할때만 풀어주면 됩니다.
				byou=0;
				UpDnVoiceTime=0;
			}
			else if((RcvBuf[IdPt + 21 ] == 58) && (byou==0)){  //close
		        CurVoice=CLOSE_VOICE;	
				byou=1;
			}

		}
		else{
			UpDnVoiceTime=0;
			updown_valid=0;
		}


/////////////////////////////////<<<<<<Door Open 적용

//************100917 - Door Open 없음**************>>>//
/*
//      if(RcvBuf[IdPt+3] & 0x08){
      if(RcvBuf[IdPt+3] & S3_UPDN_VO){
		if(!updown_valid){
			if((UpDnVoice != UP_VOICE) && (RcvBuf[IdPt+1] & 0x80)){
               CurVoice=UpDnVoice=UP_VOICE;
//               updown_valid=1;           
				CloseVoiceTime=0;                     
            }
            else if((UpDnVoice != DOWN_VOICE) && (RcvBuf[IdPt+2] & 0x01)){
               CurVoice=UpDnVoice=DOWN_VOICE;                                
//               updown_valid=1;                        
				CloseVoiceTime=0;        
            }
           
			if( (PlaySeq==51) && (CurVoice != UpDnVoice)){
				if(CloseVoiceTime > 1000)	updown_valid=1;                                
/////////////////////////				bCloseVoice=1;                                
			}
        }     
		else{
			if(RcvBuf[IdPt+1] & S1_CLOSE)	bCloseVoice=1;	
			
			if(!bCloseVoice){ 
				if(UpDnVoice != CLOSE_VOICE){
					CurVoice=UpDnVoice=CLOSE_VOICE;
					bCloseVoice=1;
				}			
			}
		}
      }
      else{   
         UpDnVoice=0;
         updown_valid=0;
		 bCloseVoice=0;
	  }
*/
//<<<************100917 - Door Open 없음**************//



///////////
#ifdef	PCI_GOGLE
			if((RcvBuf[IdPt+1] & S1_OPEN) && (RcvBuf[IdPt]==1)){
				Message = 0xff;
			}

			if(RcvBuf[IdPt] != 1)	Message  = FLOOR_9;


            if((Message != FLOOR_9) && (SelVoice == 0xff) && (RcvBuf[IdPt]==1) ){
	            if(RcvBuf[IdPt+1] & S1_UP){
					if(RcvBuf[IdPt+1] & S1_CLOSE){
						CurVoice = FLOOR_9;
						Message  = FLOOR_9;
					}					
				}
            }	
#endif	
///////////     


                           
   }         


   if((RcvBuf[IdPt+2] & 0x02) && (RcvBuf[IdPt+1] & 0x20)){
        CarMove=1;      
   }
   else{
        CarMove=0;
        testbit=0;
    }

	return(0);
}


void    Serial_Emer_Voice_Check(unsigned char id)
{
    unsigned int    IdPt;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;

   if( (RcvBuf[IdPt+4] & S4_PARKING_READY)  && (SelVoice != FLOOR_PARKING)){
		CurVoice=FLOOR_PARKING;
   }
   if( (RcvBuf[IdPt+3] & S3_PARKING)  && (SelVoice == FLOOR_PARKING)){
   		if(VoiceRun != 0){
			Stop_Play();
			VoiceRun = 0;
		}
   }


   if(((RcvBuf[IdPt+1] & 0x01) || (RcvBuf[IdPt+3] & S3_OPEN_SUB)) && (RcvBuf[IdPt+1] & 0x04) && (SelVoice != OVERLOAD_VOICE) ){  
      CurVoice=OVERLOAD_VOICE;
   }
         
   if( (RcvBuf[IdPt+2] & 0x10) && (SelVoice != HWAJAE_VOICE) ){                
      CurVoice=HWAJAE_VOICE;
   }

   if((RcvBuf[IdPt+1] & 0x08)  && (SelVoice != EMERGENCY_VOICE) ){
		if(EmergencyVoiceCnt < 10)	EmergencyVoiceCnt++;
	  	if(EmergencyVoiceCnt < 6)	CurVoice=EMERGENCY_VOICE;
   }
   if( !(RcvBuf[IdPt+1] & 0x08))	EmergencyVoiceCnt=0;
      
      
   if((RcvBuf[IdPt+1] & 0x10)  && (SelVoice != POWER_DOWN_VOICE) ){  
      CurVoice=POWER_DOWN_VOICE;
   }      
}


void    Serial_Pd_Voice_Check(unsigned char id)
{      
    unsigned int    IdPt;
    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;

   if( !(RcvBuf[IdPt+5] & 0x04)  && (SelVoice != POWER_DOWN_VOICE) && CarMove ){  
      CurVoice=POWER_DOWN_VOICE;
   }      
}

/*******************************************************
        manual play and record
*******************************************************/


/*
void main(void)
{

   EA=0;

   for(CurVoice=0;CurVoice<0xff;CurVoice++);
   

   TMOD=0x21;
   SCON=0x50;
        
   TH0=0xdb;
   TL0=0xd5;

   TX_EN=1;
   POWER_DOWN=1;
   RxStatus = TX_SET;  

   EA=1;

   
   VoiceAct=VOICE_OFF;

   Stop_Play();

   BATTERY=ON;

   while(!POWER_DOWN){
      BATTERY=ON;
   }
         
   RunPgm=0x0;
   valid_key=0;
   active_key=0;
   updown_valid=0;
   flow_valid=0;
   floor =0;
   CurFloor=0;
   BatteryRun=0;
   Flow_Active=0;
   SelVoice=0;
   PlaySeq=0;
   VoiceRun=0;       
   CurVoice=0xff;
   BeforeVoice=0;
   HwajaeVoiceCnt=0;
   OverLoadVoiceCnt=0;
   EmergencyVoiceCnt=0;
   UpDnVoice=0x0;
   RxStatus=STX_CHK;
      
   MyAddress=VOICE_ADR;

   if(!TEST_MODE){
      Manual_Play();
   }
   BatteryRun=0;

   BATTERY=OFF;

   RunPgm=0x55;

   RxStatus=STX_CHK;   

   while(1){
      WDTRST=0x1e;
      WDTRST=0xe1;
      

      for(;MyLogAdr==0;){
         WDTRST=0x1e;
         WDTRST=0xe1;
         
         if(delay>200){
            V_LAMP=~V_LAMP;
            delay=0;
         }
                     
         if(RxStatus==RX_GOOD){
            if((RcvBuf[RCV_GROUP] == GROUP_ID) && (RcvBuf[RCV_ABSADR] == MyAddress)){                                                
               if((RcvBuf[RCV_CMD] == ADR_SET_SEND)){                                                                                                                
                  delay=0;
                  while(delay<2){
                     V_LAMP=~V_LAMP;
                     WDTRST=0x1e;
                     WDTRST=0xe1;                  
                  };                  
                  Req_Logic_Adr(MyAddress,RcvBuf[RCV_LOGADR],ADR_SET_REC); 
                  TimeOutBd=90;                  
               }                                                            
               else if((RcvBuf[RCV_CMD] == ADR_SET_ACK)){                                       
                  MyLogAdr=RcvBuf[RCV_LOGADR];
                  RxStatus=STX_CHK;            
               }
               else  RxStatus=STX_CHK;            
            }                              
            else  RxStatus=STX_CHK;            
         }            
      }

      
      if(TimeOutBd == MyLogAdr){
         SlaveTx();
         TimeOutBd=90;
      }

               
      CurVoice=0xff;
      if(RxStatus==RX_GOOD){
         TimeOutBd=RcvBuf[RCV_LOGADR];
         if(TimeOutBd == (MyLogAdr-1)){
            SerialTime=5;
         }         
         if((RcvBuf[RCV_CMD] == NORMAL) && (RcvBuf[RCV_GROUP] == GROUP_ID) && (RcvBuf[RCV_LOGADR] == LOG_ADR) && (RcvBuf[RCV_ABSADR] == MAS_A)){
            Serial_Flow_Voice_Chk();
            Serial_Status_Voice_Check();
            Serial_Emer_Voice_Check();
            RxStatus=STX_CHK;
         }
         else if((RcvBuf[RCV_CMD] == LOGADR_CLR) && (RcvBuf[RCV_GROUP] == GROUP_ID) && (RcvBuf[RCV_LOGADR] == LOG_ADR) && (RcvBuf[RCV_ABSADR] == MAS_A)){
            MyLogAdr=0;
            RxStatus=STX_CHK;
         }
         else if((RcvBuf[RCV_CMD] == ADR_SET_SEND) && (RcvBuf[RCV_GROUP] == GROUP_ID)){ // && (RcvBuf[RCV_ABSADR] == MAS_A)){
//            Serial_Pd_Voice_Check();
            RxStatus=STX_CHK;
         }         
         else{
            RxStatus=STX_CHK;         
         }
      }
               
      if(CurVoice != 0xff){
         VoiceAct=VOICE_ON;
         SelVoice=CurVoice;
         if(VoiceRun != 0){
            Stop_Play();
            if(CurVoice >= FLOOR_U5){
               SelVoice=1;
               PlaySeq=10;
            }
            else{
               PlaySeq=20;
            }
         }
         else{
            if(CurVoice >= FLOOR_U5){
               PlaySeq=30;
            }
            else{
               PlaySeq=40;
            }
         }
      }

      if(PlaySeq==10){
         if(!VoiceRun){
            PlaySeq=30;
         }
      }
      else if(PlaySeq==20){
         if(!VoiceRun){
            if(SelVoice & 0x80)    PlaySeq=50;
            else                    PlaySeq=40;
         }
      }
      else if(PlaySeq==30){
         CurVoice=DINGDONG;
         Play();
         PlaySeq=31;
      }
      else if(PlaySeq==31){
         if(VoiceRun){
            PlaySeq=20;
         }
      }

      else if(PlaySeq==40){
         BeforeVoice=CurVoice=SelVoice;
         Play();
         PlaySeq=41;
      }
      else if(PlaySeq==41){
         if(VoiceRun){
            PlaySeq=50;
         }
      }
      else if(PlaySeq==50){
         if(!VoiceRun){
            PlaySeq=51;
            VoiceAct=VOICE_OFF;
         }
      }

      if(!BUSY){
         if(PlaySeq==51)   SelVoice=0xff; 
         VoiceRun=0;
      }
      else            VoiceRun=1;
         
      V_LAMP=~BUSY;
   }

}

*/

/*
interrupt [0x03] void EX0_int (void)
{
   if(RunPgm==0x55){
      WDTRST=0x1e;
      WDTRST=0xe1;

      Stop_Play();
      while(BUSY && !POWER_DOWN){
         WDTRST=0x1e;
         WDTRST=0xe1;
         Stop_Play();
      };

      CurVoice=POWER_DOWN_VOICE;
      Play();
      while(!BUSY && !POWER_DOWN){
         WDTRST=0x1e;
         WDTRST=0xe1;
      }
      
      while(BUSY && !POWER_DOWN){
         WDTRST=0x1e;
         WDTRST=0xe1;      
      }

      Play();
      
      while(!BUSY && !POWER_DOWN){
         WDTRST=0x1e;
         WDTRST=0xe1;      
      }
      
      while(BUSY && !POWER_DOWN){
         WDTRST=0x1e;
         WDTRST=0xe1;      
      }

      while(!POWER_DOWN){
         RunPgm=0x0;
         BATTERY=ON;
         Stop_Play();
      }
   }
   Stop_Play();
   
}
*/


/*
interrupt [0x0B] void T0_int (void)     
{
      
   TH0=0xf8;
   TL0=0xe0;

   SerialTime++;
   if(SerialTime>10){
      if(TimeOutBd < 100){
         TimeOutBd++;
      }         
      SerialTime=0;      
   }
   
   delay++;
}
*/



/*
void  Timer0Init(void)
{
  TMR0IE=1;
  TMR0IF=0;

  TMR0ON=1;	    // TMR0 on/off
  T08BIT=0;	    // 8/16 bit select    ..(16bit)
  T0CS=0;	    // TMR0 Source Select ..(internal clock)
  T0SE=0;	    // TMR0 Source Edge Select
  PSA=0;	    // Prescaler Assignment ..(enable)
  T0PS2=0;	    // Prescaler..............(1:2)
  T0PS1=1;
  T0PS0=0;
 
  TMR0L=MSEC_L;
  TMR0H=MSEC_H;
} 



void  Initial(void)
{

///////////////////////////////////////////////
// INTCON Register
  GIE=0;        // global interrupt enable
//  GIEH=0;     // enable high priority interrupts
  PEIE=1;	    // peripheral interrupt enable
//  GIEL=0;	    // enable low priority peripheral interrupts
  TMR0IE=1;	    // TMR0 overflow interrupt enable
  INT0IE=0;	    // external interrupt 0 enable
  RBIE=0;	    // RB port change interrupt enable
  TMR0IF=0;	    // TMR0 overflow interrupt flag
  INT0IF=0;	    // external interrupt 0 flag
  RBIF=0;	    // RB port change interrupt flag

///////////////////////////////////////////////
// INTCON2 Register
  RBPU=1;	    // port B pull-up enable
  INTEDG0=0;	// external interrupt 0 edge select
  INTEDG1=0;	// external interrupt 1 edge select
  INTEDG2=0;	// external interrupt 2 edge select
  TMR0IP=1;	    // TMR0 overflow interrupt priority
  RBIP=0;	    // RB port change interrupt priority

///////////////////////////////////////////////
// INTCON3 Register
  INT2IP=0;	    // external interrupt 2 priority
  INT1IP=0;	    // external interrupt 1 priority
  INT2IE=0;	    // external interrupt 2 enable
  INT1IE=0;	    // external interrupt 1 enable
  INT2IF=0;	    // external interrupt 2 flag
  INT1IF=0;	    // external interrupt 1 flag

///////////////////////////////////////////////
// T0CON Register
  TMR0ON=1;	    // TMR0 on/off
  T08BIT=0;	    // 8/16 bit select    ..(16bit)
  T0CS=0;	    // TMR0 Source Select ..(internal clock)
  T0SE=0;	    // TMR0 Source Edge Select
  PSA=0;	    // Prescaler Assignment ..(enable)
  T0PS2=0;	    // Prescaler..............(1:2)
  T0PS1=0;
  T0PS0=1;

// OSCCON Register
  SCS=0;	    // system clock switch bit

// LVDCON Register
  IRVST=0;	    // input reference voltage stable status..(read only)
  LVDEN=1;	    // low voltage detect enable..............(enable)
  LVDL3=1;	    // low voltage detection limits...........(4.16V - 4.5V)
  LVDL2=1;
  LVDL1=0;
  LVDL0=1;

// WDTCON Register
  SWDTEN=0;	    // software watchdog timer enable.......(disable)

// RCON Register
  IPEN=0;	    // interrupt priority enable............(disable)?????
  RI=0;	        // RESET instruction status
  TO=0;	        // watchdog timeout flag
  PD=0;	        // power-down detection
  POR=0;	    // power-on reset status
  BOR=0;	    // brown-our reset status

// T1CON Register
  RD1=1;	// 16 Bit Read/Write Enable
  //T1RD16=1;	// 16 Bit Read/Write Enable
  T1CKPS1=1;	// Prescaler ........(1/8)
  T1CKPS0=1;
  T1OSCEN=0;	// Oscillator Enable....(disable)
  T1SYNC=0;	    // Sync Selct
  TMR1CS=0;	    // TMR Clock Source Select..(internal clock)
  TMR1ON=1;	    // TMR on/off...............( tmr run)

// T2CON Register
  TOUTPS3=0;	// Postscale
  TOUTPS2=0;
  TOUTPS1=0;
  TOUTPS0=0;
  TMR2ON=0;	    // TMR2 On/Off............(off)
  T2CKPS1=0;	// Prescale
  T2CKPS0=0;

// SSPSTAT Register..........(not use)
  SMP=0;	    // Sample Bit
  CKE=0;	    // SPI Clk Edge Select
  DA=0;	        // Data/Address Bit
  STOP=0;	    // STOP Bit detected
  START=0;	    // START Bit detected
  RW=0;	        // Read/Write bit Information
  UA=0;	        // Update Adress
  BF=0;	        // Buffer Full Status bit

// SSPCON1 Register..........(not use)
  WCOL=0;	    // write collision detect
  SSPOV=0;	    // recieve overflow indicator
  SSPEN=0;	    // SSP enable
  CKP=0;	    // clock polarity select
  SSPM3=0;	    // SSP mode select 
  SSPM2=1;
  SSPM1=0;
  SSPM0=1;


// SSPCON2 Register.......(not use)
  GCEN=0;	    // general call enable
//  ACKSTA=0;	    // acknowledge status bit
  ACKDT=0;	    // acknowledge data bit
  ACKEN=0;	    // acknowledge sequence enable
  RCEN=0;	    // recieve enable bit
  PEN=0;	    // STOP condition enable
  RSEN=0;	    // repeated START enable
  SEN=0;	    // START condition enable


// ADCON0 Register...(not use)  
  ADCS1=0;	    // AD conv. clock select bits
  ADCS0=0;
  CHS2=0;	    // channel select
  CHS1=0;
  CHS0=0;
  GODONE=0;	    // AD conversion status
  ADON=0;	    // AD on status


// ADCON1 Register....(not use)
  ADFM=0;	    // AD result format
  ADCS2=0;	    // AD conv. clock select bits
  PCFG3=0;	    // AD port config bits....(all digital)
  PCFG2=1;
  PCFG1=1;
  PCFG0=0;


// CCP1CON Register......(not use)
  DC1B1=0;	    // Duty Cycle Bits 1 & 0
  DC1B0=0;
  CCP1M3=0;	    // Mode Select Bits...(can messag receive)
  CCP1M2=0;
  CCP1M1=1;
  CCP1M0=1;

// ECCP1CON Register.......(not use)     
  EPWM1M1=0;	// PWM output config bits
  EPWM1M0=0;
  EDC1B1=0;	// PWM duty cycle LSBs
  EDC1B0=0;
  ECCP1M3=0;	// EEPC1 mode select bits
  ECCP1M2=0;
  ECCP1M1=0;
  ECCP1M0=1;

// ECCP1DEL Register.....(not use)
  EPDC7=0;	// PWM delay
  EPDC6=0;
  EPDC5=0;
  EPDC4=0;
  EPDC3=0;
  EPDC2=0;
  EPDC1=0;
  EPDC0=0;

// ECCPAS Register.....(not use)
  ECCPASE=0;	// ECCP auto-shutdown event status
  ECCPAS2=0;	// EECP auto-shutdown bits
  ECCPAS1=0;
  ECCPAS0=0;
  PSSAC1=1;	    // pin A & C auto-shutdown control
  PSSAC0=0;
  PCCBD1=1;	    // pin B & D auto-shutdown control
  PCCBD0=0;


// CVRCON Register...............(not use)
  CVREN=0;	    // comparator voltage reference enable
  CVROE=0;	    // comparator VREF output enable
  CVRR=0;	    // comparator VREF range select
  CVRSS=0;	    // comparator VREF source select
  CVR3=0;	    // comparator VREF value selection
  CVR2=0;
  CVR1=0;
  CVR0=0;


// CMCON Comparator module register.....(not use)
  C2OUT=0;	   // comparator 2 output
  C1OUT=0;	   // comparator 1 output
  C2INV=0;	   // select to invert comp2 output
  C1INV=0;	   // select to invert comp1 output
  CIS=0;	   // comp input switch bit
  CM2=1;	   // comp mode select bits
  CM1=1;
  CM0=1;


// T3CON Register.......(not use) 
  T3RD16=0;	    // 16-Bit Read/Write select
  T3ECCP1=0;	// TMR3 & TMR1 CCPx Enable
  T3CKPS1=0;	// Prescaler
  T3CKPS0=0;
  T3CCP1=0;	    // TMR3 & TMR1 CCPx Enable
  T3SYNC=0;	    // Sync Select
  TMR3CS=0;	    // TMR3 source Select
  TMR3ON=0;	    // TMR3 on/off

// TXSTA Register
  CSRC=0;      // CLK source select
  TX9=0	;	   // 8/9 bit TX data select
  TXEN=1;	   // transmit enable bit
  SYNC=0;	   // USART mode select
  BRGH=1;	   // high baud rate select
  TRMT=1;	   // TX shift reg. status bit
  TX9D=1;	   // 9th Bit of TX data

// RCSTA Register  
  SPEN=0;	  // serial port enable...(disable)
  RX9=0;	  // 8/9 bit data reception
  SREN=0;	  // single recieve enable
  CREN=0;	  // continuous recieve enable
  ADDEN=0;	  // address detect enable
  FERR=0;	  // framing error
  OERR=0;	  // overrun error
  RX9D=0;	  // 9th Bit of RX data

// EECON1 Register
  EEPGD=0;	  // FLASH/EEPROM select
  EEFS=0;	  // access config regs./access FLASH-EEPROM

// alternate definition
  CFGS=0; 	  //Config./Calibration Select
  FREE=0;	  // FLASH row erase enable
  WRERR=0;	  // write error flag
  WREN=0;	  // write enable
  WR=0;	      // write control
  RD=0;	      // read control

// IPR3 Register
  IRXIP=0;	  // CAN invalid rec. message interrupt priority
  WAKIP=0;	  // CANbus activity wake-up interrupt priority
  ERRIP=0;	  // CANbus error interrupt priority
  TXB2IP=0;	  // CAN TX buffer 2 interrupt priority
  TXB1IP=0;	  // CAN TX buffer 1 interrupt priority
  TXB0IP=0;	  // CAN TX buffer 0 interrupt priority
  RXB1IP=0;	  // CAN RX buffer 1 interrupt priority
  RXB0IP=1;	  // CAN RX buffer 0 interrupt priority	     

// PIR3 Register
  IRXIF=0;	  // CAN invalid rec. message interrupt flag
  WAKIF=0;	  // CANbus activity wake-up interrupt flag
  ERRIF=0;	  // CANbus error interrupt flag
  TXB2IF=0;	  // CAN TX buffer 2 interrupt flag
  TXB1IF=0;	  // CAN TX buffer 1 interrupt flag
  TXB0IF=0;	  // CAN TX buffer 0 interrupt flag
  RXB1IF=0;	  // CAN RX buffer 1 interrupt flag
  RXB0IF=0;	  // CAN RX buffer 0 interrupt flag		

// PIE3 Register
  IRXIE=0;	  // CAN invalid rec. message interrupt enable
  WAKIE=0;	  // CANbus activity wake-up interrupt enable
  ERRIE=0;	  // CANbus error interrupt enable
  TXB2IE=0;	  // CAN TX buffer 2 interrupt enable
  TXB1IE=0;	  // CAN TX buffer 1 interrupt enable
  TXB0IE=0;	  // CAN TX buffer 0 interrupt enable
  RXB1IE=0;	  // CAN RX buffer 1 interrupt enable
  RXB0IE=0;	  // CAN RX buffer 0 interrupt enable	     

// IPR2 Register
  CMIP=0;	     // comparator interrupt priority		
  EEIP=0;   	// EEPROM write interrupt priority
  BCLIP=0;   	// bus collision interrupt priority
  LVDIP=0;	    // low voltage detect interrupt priority
  TMR3IP=0;	    // TMR3 overflow interrupt priority
  ECCP1IP=0;	// ECCP1 interrupt priority


// PIR2 Register
  CMIF=0;	   // comparator interrupt flag		
  EEIF=0;	   // EEPROM write interrupt flag
  BCLIF=0;	   // bus collision interrupt flag
  LVDIF=0;	   // low voltage detect interrupt flag
  TMR3IF=0;	   // TMR3 overflow interrupt flag
  ECCP1IF=0;   // ECCP1 interrupt flag


// PIE2 Register
  CMIE=0;	  // comparator interrupt enable		
  EEIE=0;	  // EEPROM write interrupt enable
  BCLIE=0; 	  // bus collision interrupt enable
  LVDIE=0;	  // low voltage detect interrupt enable
  TMR3IE=0;	  // TMR3 overflow interrupt enable
  ECCP1IE=0;  // ECCP1 interrupt enable


// IPR1 Register

  PSPIP=0;	  // para. slave port rd/wr interrupt priority
  ADIP=0;	  // AD conv. interrupt priority
  RCIP=0;	  // USART RX interrupt priority
  TXIP=0;	  // USART TX interrupt priority
  SSPIP=0;    // master SSP interrupt priority
  CCP1IP=0;	  // CCP1 interrupt priority
  TMR2IP=0;	  // TMR2 - PR2 match interrupt priority
  TMR1IP=0;	  // TMR1 overflow interrupt priority

// PIR1 Register
  PSPIF=0;	     // para. slave port rd/wr interrupt flag
  ADIF=0;	     // AD conv. interrupt flag
  RCIF=0;	     // USART RX interrupt flag
  TXIF=0;	     // USART TX interrupt flag
  SSPIF=0;	     // master SSP interrupt flag
  CCP1IF=0;	     // CCP1 interrupt flag
  TMR2IF=0;	     // TMR2 - PR2 match interrupt flag
  TMR1IF=0;	     // TMR1 overflow interrupt flag

// PIE1 Register
  PSPIE=0;	    // para. slave port rd/wr interrupt enable
  ADIE=0;	    // AD conv. interrupt enable
  RCIE=0;	    // USART RX interrupt enable
  TXIE=0;	    // USART TX interrupt enable
  SSPIE=0;	    // master SSP interrupt enable
  CCP1IE=0;	    // CCP1 interrupt enable
  TMR2IE=0;	    // TMR2 - PR2 match interrupt enable
  TMR1IE=0;	    // TMR1 overflow interrupt enable


// TRISE Register
  IBF=0;   	    // input buffer full status
  OBF=0;	    // output buffer full status
  IBOV=0;	    // input buffer overflow
  PSPMODE=0;	// parallel slave port mode select


/////////new board
/////////new board
/////////new board
/////////new board
/////////new board


//#define   TEST_MODE     RD4     //in    
//#define   MASTER_MODE   RD5     //in
//#define   POWER_DOWN    RA4     //in              
//#define   BUSY          RA0     //in

//#define   SEN           LATA1   //out
//#define   SI            LATA2   //out
//#define   BATTERY       LATA5   //out           


  TRISE2=0;	    // port E data direction...(output)
  TRISE1=0;
  TRISE0=0;


// TRISD Register
  TRISD7=0;	// port D data direction....(output)
  TRISD6=0;
  TRISD5=1;
  TRISD4=1;
  TRISD3=0;
  TRISD2=0;
  TRISD1=0;
  TRISD0=0;



// TRISC Register
  TRISC7=0;	// port C data direction
  TRISC6=0;
  TRISC5=0;
  TRISC4=0;
  TRISC3=0;
  TRISC2=0;
  TRISC1=0;
  TRISC0=0;


// TRISB Register
  TRISB7=0;	// port B data direction
  TRISB6=0;
  TRISB5=0;
  TRISB4=0;
  TRISB3=1;   //can rx 
  TRISB2=0;   //can tx
  TRISB1=0;   //in
  TRISB0=0;   //in


// TRISA Register
  TRISA7=0;	// port A data direction
  TRISA6=0;
  TRISA5=0;
  TRISA4=1;
  TRISA3=0;
  TRISA2=0;
  TRISA1=0;
  TRISA0=1;



// LATE Register
  LATE2=1;	// port E data latch
  LATE1=1;
  LATE0=1;

// LATD Register
  LATD7=1;	// port D data latch
  LATD6=1;
  LATD5=1;
  LATD4=1;
  LATD3=1;
  LATD2=1;
  LATD1=1;
  LATD0=1;


// LATC Register
  LATC7=1;	// port C data latch
  LATC6=1;
  LATC5=1;
  LATC4=1;
  LATC3=1;
  LATC2=1;
  LATC1=1;
  LATC0=1;

// LATB Register
  LATB7=1;	// port B data latch
  LATB6=1;
  LATB5=1;
  LATB4=1;
  LATB3=1;
  LATB2=1;
  LATB1=1;
  LATB0=1;

// LATA Register
  LATA7=1;	// port A data latch
  LATA6=1;
  LATA5=1;
  LATA4=1;
  LATA3=1;
  LATA2=1;
  LATA1=1;
  LATA0=1;    
/////////new board
/////////new board
/////////new board
/////////new board
/////////new board
/////////new board


  Timer0Init(); 

}

*/


void    PortInit(void)
{
  TRISE2=0;	    // port E data direction...(output)
  TRISE1=0;
  TRISE0=0;


// TRISD Register
  TRISD7=1;	// port D data direction....(output)
  TRISD6=1;
  TRISD5=1;
  TRISD4=1;
  TRISD3=0;
  TRISD2=0;
  TRISD1=0;
  TRISD0=0;



// TRISC Register
  TRISC7=0;	// port C data direction
  TRISC6=0;
  TRISC5=0;
  TRISC4=0;
  TRISC3=0;
  TRISC2=0;
  TRISC1=0;
  TRISC0=0;


// TRISB Register
  TRISB7=0;	// port B data direction
  TRISB6=0;
  TRISB5=0;
  TRISB4=0;
  TRISB3=1;   //can rx 
  TRISB2=0;   //can tx
  TRISB1=0;   //in
  TRISB0=0;   //in


// TRISA Register
  TRISA7=0;	// port A data direction
  TRISA6=0;
  TRISA5=0;
  TRISA4=1;
  TRISA3=1;
  TRISA2=0;
  TRISA1=0;
  TRISA0=1;



// LATE Register
  LATE2=1;	// port E data latch
  LATE1=1;
  LATE0=1;

// LATD Register
  LATD7=1;	// port D data latch
  LATD6=1;
  LATD5=1;
  LATD4=1;
  LATD3=1;
  LATD2=1;
  LATD1=1;
  LATD0=1;


// LATC Register
  LATC7=1;	// port C data latch
  LATC6=1;
  LATC5=1;
  LATC4=1;
  LATC3=1;
  LATC2=1;
  LATC1=1;
  LATC0=1;

// LATB Register
  LATB7=1;	// port B data latch
  LATB6=1;
  LATB5=1;
  LATB4=1;
  LATB3=1;
  LATB2=1;
  LATB1=1;
  LATB0=1;

// LATA Register
  LATA7=1;	// port A data latch
  LATA6=1;
  LATA5=1;
  LATA4=1;
  LATA3=1;
  LATA2=1;
  LATA1=1;
  LATA0=1;    
}


void main(void)
{
    unsigned char i;
    
    di();
    Initial();
    PortInit();
    Timer0Init(); 

	AnlogInit();


    Tx1ConfirmCnt=0;
    Tx0ConfirmCnt=0;


  	PEIE=1;
	ADCON1=0x0E;  
    
//    MyAdrRead();

    ei();
    
    SetupCheck();

    CmpSetBit=0;            //new
    MaskSetBit=0;           //new

   if(LOCAL0 && LOCAL1)         LocalNumber=0; 
   else if(!LOCAL0 && LOCAL1)   LocalNumber=1; 
   else if( LOCAL0 && !LOCAL1)  LocalNumber=2; 
   else if(!LOCAL0 && !LOCAL1)  LocalNumber=3; 


    di();
    CAN_Init();
    ei();

/*
    di();
    
	REQOP2 = 1 ;// Entry Configration Mode
    REQOP1 = 0 ;
    REQOP0 = 0 ;

    TxSidEidArrary();
        
    CANSetFilter(0,SidBuffer,EidBuffer);
    CANSetFilter(1,SidBuffer,EidBuffer);
    CANSetFilter(2,SidBuffer,EidBuffer);
    CANSetFilter(3,SidBuffer,EidBuffer);
    CANSetFilter(4,SidBuffer,EidBuffer);
    CANSetFilter(5,SidBuffer,EidBuffer);

    CANSetMask(0,0x007f,0x0000c000);
    CANSetMask(1,0x007f,0x0000c000);

    CANSetFilter(0,SidBuffer,EidBuffer);
    CANSetFilter(1,SidBuffer,EidBuffer);
    CANSetFilter(2,SidBuffer,EidBuffer);
    CANSetFilter(3,SidBuffer,EidBuffer);
    CANSetFilter(4,SidBuffer,EidBuffer);
    CANSetFilter(5,SidBuffer,EidBuffer);

    CANSetMask(0,0x007f,0x0000c000);
    CANSetMask(1,0x007f,0x0000c000);

	REQOP2 = 0 ;
	REQOP1 = 0 ;
	REQOP0 = 0 ;


    ei();
*/


//////////////////
   VoiceAct=VOICE_OFF;


	InitMLC108x();
	ADConversionChk();



   Stop_Play();
	
   BATTERY=ON;

   while(!POWER_DOWN){
      BATTERY=ON;
   }
         
   RunPgm=0x0;
   valid_key=0;
   active_key=0;
   updown_valid=0;
   flow_valid=0;
   floor =0;
   CurFloor=0;
   BatteryRun=0;
   Flow_Active=0;
   SelVoice=0;
   PlaySeq=0;
   VoiceRun=0;       
   CurVoice=0xff;
   BeforeVoice=0;
   HwajaeVoiceCnt=0;
   OverLoadVoiceCnt=0;
   EmergencyVoiceCnt=0;
   UpDnVoice=0x0;
//   RxStatus=STX_CHK;
      
   MyAddress=VOICE_ADR;

   if(!TEST_MODE && MASTER_MODE){
      Manual_Play();
   }
   BatteryRun=0;

   BATTERY=OFF;

   RunPgm=0x55;

       
    CanDatacnt0=2;
    CanDatacnt1=2;
    CanCmd=0;



	for(i=0;i<64;i++){	
		new_buf[i] = FloorChar[i];
		BefFlr=0;
		BefFlrTime=0;
	}

    i=(LocalNumber * HOST_DATA_RECOD) + RCV_DATA;
	RcvBuf[i+S0_FLOOR]=0x0;

    while(1){    
        CLRWDT();

////////////////////////////		

//	   if(!TEST_MODE && !MASTER_MODE){
//			DspCharRdWr(LocalNumber);
//	   }

		DspCharRdWr(LocalNumber);
          
        CurVoice=0xff;
      
		Serial_Flow_Voice_Chk(LocalNumber);
        Serial_Status_Voice_Check(LocalNumber);
        Serial_Emer_Voice_Check(LocalNumber);
                
               
        if(CurVoice != 0xff){
           VoiceAct=VOICE_ON;
           SelVoice=CurVoice;
           if(VoiceRun != 0){
              Stop_Play();


#ifdef	FLOOR_ANOUNCE
              if( (CurVoice >= FLOOR_U5) && (CurVoice <= END_FL)){
                 //SelVoice=1;	//100909 - 남녀음악멘트 개발시 버그로 인해 잘못되었음을 알아서 막았습니다.
                 PlaySeq=10;
              }
#else

#ifdef	PCI_GOGLE
			if( (CurVoice >= FLOOR_U5) && (CurVoice < FLOOR_9)){
#else
             if((CurVoice >= FLOOR_U5) && (CurVoice <= END_FL)){
#endif
                 //SelVoice=1;	//100909 - 남녀음악멘트 개발시 버그로 인해 잘못되었음을 알아서 막았습니다.
                 PlaySeq=10;
              }
#endif
              else{
                 PlaySeq=20;
              }
           }
           else{

#ifdef	FLOOR_ANOUNCE
              if( (CurVoice >= FLOOR_U5) && (CurVoice <= END_FL)){
                 PlaySeq=30;
              }
#else
#ifdef	PCI_GOGLE
              if( (CurVoice >= FLOOR_U5) && (CurVoice < FLOOR_9)){
#else
              if((CurVoice >= FLOOR_U5) && (CurVoice <= END_FL)){					
#endif
                  	PlaySeq=30;
              }
#endif
              else{
                 PlaySeq=40;
              }
           }
        }

        if(PlaySeq==10){
           if(!VoiceRun){
              PlaySeq=30;
           }
        }
        else if(PlaySeq==20){
           if(!VoiceRun){
              if(SelVoice & 0x80)     PlaySeq=50;
              else                    PlaySeq=40;
           }
        }
        else if(PlaySeq==30){
           CurVoice=DINGDONG;
           Play();
           PlaySeq=31;
        }
        else if(PlaySeq==31){
           if(VoiceRun){
              PlaySeq=20;
           }
        }

        else if(PlaySeq==40){ 
           BeforeVoice=CurVoice=SelVoice;
           Play();
           PlaySeq=41;
        }
        else if(PlaySeq==41){
           if(VoiceRun){
              PlaySeq=50;
           }
        }
        else if(PlaySeq==50){
           if(!VoiceRun){
              PlaySeq=51;
              VoiceAct=VOICE_OFF;
           }
        }

        if(!BUSY){
           if(PlaySeq==51)   SelVoice=0xff; 
           VoiceRun=0;
			ADConversionChk();
        }
        else            VoiceRun=1;
           
        if(BUSY)  V_LAMP=0;
        else      V_LAMP=1;

    }




/*

////////////////
//////////////////
        CLRWDT();
//        CanLiveChk();  //////////////////?????????????
        ButtonLampClrChk();                  
        Lamp(LocalNumber);                  
        UpDownBlink(LocalNumber);
        
        UpDownKey();
                                
        if(CanTxAct){
            if(!UpKeyLoad(ReceiveAdr)){
                CanTx1();
                Tx1ConfirmCnt=0;
            }
            else if(Up_Key_Valid && Tx1ConfirmCnt){
                SelHostAdr=ReceiveAdr;
                CanCmd=CAN_KEY_CONFIRM;
                confirmkey=(MyAddress-1);
                CanKeyValue[1] = (confirmkey | UP_READY);                
                CanTx1();
            }            

            if(!DnKeyLoad(ReceiveAdr)){
                CanTx0();
                Tx0ConfirmCnt=0;
            }
            else if(Dn_Key_Valid && Tx0ConfirmCnt){
                SelHostAdr=ReceiveAdr;
                CanCmd=CAN_KEY_CONFIRM;
                confirmkey=(MyAddress-1);
                CanKeyValue[1] = (confirmkey | DN_READY);                
                CanTx0();

            }

        }            
    }
*/

}



void interrupt isr(void)
{
//    unsigned char i;
    

    if( TMR0IF )
    {
    
        TMR0IF = 0 ;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;    

        delay++;


        shiftTime++;

		CloseVoiceTime++;

		abctimer++;
		if(abctimer>100){
			abctimer=0;
			if(UpDnVoiceTime < 200)	UpDnVoiceTime++;
			if(BefFlrTime < 200)	BefFlrTime++;

			if(FloorXCnt<200)	FloorXCnt++;
		}


/*        
        if(!UP_KEY){
            UpKeyBit=1;   
        }
        else        UpKeyBit=0;
        if(!DN_KEY){
            DnKeyBit=1;   
        }
        else        DnKeyBit=0;   
              
    
        msec100++;
    
        if(msec100>100){
            msec100=0;
                        
            for(i=0;i<MAX_ELEV;i++){          
                CanLiveTimeAdr[i]++;
            }        
            
            MainTimer++;
            BlinkTime++;
            
            if(UpButtonTime<BUT_CANLE_T){
                UpButtonTime++;   
            }
            if(DnButtonTime<BUT_CANLE_T){
                DnButtonTime++;   
            }
    
            sec1++;
            if(sec1>10){
                sec1=0;
                for(i=0;i<MAX_ELEV;i++){          
                    MoveTime[i]++;
                }        
            }
        }
*/
      
    }

    if(PIR3>0){
        CanInterrupt();
    }

	if(ADIF){
		ADIF=0;
		GODONE=0;
		if( !bAdConversion){
        	ADBuf=ADRES;
			bAdConversion=1;
		}
	}

}











