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
#include        "..\comm_4480\spi.h"



#define	FLOOR_ANOUNCE	1	//101112 - B6층 적용할때는 이상한거 같음
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



#define   		TEST_MODE     RD4     //in    
#define   		MASTER_MODE   RD5     //in
#define   		LOCAL0        RD6     //in    
#define   		LOCAL1        RD7     //in    
////////////////#define   		MASTER_MODE   RD5     //in

//#define   		POWER_DOWN    RA4     //in              
///////////////////#define   		BUSY          RA0     //in


//#define   		SEN           LATA1   //out
//#define   		SI            LATA2   //out
//#define   		BATTERY       LATA5   //out           
//#define   		V_LAMP        LATE1   //out           
//#define   		SCK           LATE2   //out
//#define   		VoiceAct      LATE0   //out


#ifdef	CPU45K80
	#define   		VoiceAct      LATE0   //out
#else
	#define   		VoiceAct      LATA4   //out
#endif;


#define   		BATTERY       LATC0   //out           
#define   		POWER_DOWN    RC2     //in              
#define   		VOICE_DOWN_P  RC1     //in              



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
//unsigned    char     CurCarKey[4]={0,0,0,0};

unsigned    char     BefFloorX;
unsigned    char     FloorX;
//unsigned    char     ButtonStatus;
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


/*
unsigned    char     CarKeySetButFlr,CarKeyCancleButFlr=0;
unsigned    char     BefCarKeySetButFlr,BefCarKeyCancleButFlr=0;
*/

unsigned    char  YourDoor;
unsigned    char  YourDoor0;
unsigned    char  YourDoor1;
unsigned    char  YourDoor2;
unsigned    char  YourDoor3;

unsigned    char  YourKey[4]={0,0,0,0};
unsigned    char  YourKey0[4]={0,0,0,0};
unsigned    char  YourKey1[4]={0,0,0,0};
unsigned    char  YourKey2[4]={0,0,0,0};
unsigned    char  YourKey3[4]={0,0,0,0};


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

bit		BUSY=0;


//bit   bUp=0;
//bit   bDn=0;



/*
void    Wait(unsigned char   x)
{
   delay=0;
   while(delay<x);
}
*/


void	WaitDownLoader(void)
{

	SSPEN=0;

	SSPCON1=0;

	TRISC3=1;   //sck
	TRISC4=1;   //sdi
	TRISC5=1;   //sdo
	TRISA5=1;   //ss

	do{
        CLRWDT();	
	}while(VOICE_DOWN_P);


	while(1);

}
            

void    SetupDisplayES15(unsigned char mdata,unsigned char mode)
{
}

void  SetupDisplay(unsigned char ft,unsigned char sd)
{
}



unsigned char SyncButtonCheck(void)
{
	unsigned char i;

	if(SrcAddress  == LocalNumber){
        i=(unsigned char)RxEidBuffer;
		if( (i == 0x80) || (i == 0x81) || (i == 0x82)|| (i == 0x83)){
			return(1);
		}
		else	return(0);
	}
	else	return(0);
}



void    ButtonReChk(void)
{
    unsigned int    IdPt;

    unsigned char BefButClrSet;
    unsigned char TmpButSta1,TmpButSta2,TmpButSta3;

	unsigned char i,j,k;

    IdPt=(LocalNumber * HOST_DATA_RECOD) + RCV_DATA;


	BefButClrSet=0;

	TmpButSta1=RcvBuf[IdPt+1];
	TmpButSta2=RcvBuf[IdPt+2];
	TmpButSta3=RcvBuf[IdPt+3];

	if( !(TmpButSta1 & S1_UP) && !(TmpButSta2 & S2_DN) ){  //UP=0,DN=0
		BefButClrSet=1;
	}
	  
	if( (TmpButSta2 & S2_EXT_BUT_CLR) || ( TmpButSta2 & S2_CAR_BUT_CLR)){
		BefButClrSet=1;
	}


	if(BefButClrSet == 1){
	    YourKey[0]=YourKey0[0]= YourKey1[0] = YourKey2[0] = YourKey3[0]=BefCarKey[0]=0;
	    YourKey[1]=YourKey0[1]= YourKey1[1] = YourKey2[1] = YourKey3[1]=BefCarKey[1]=0;
	    YourKey[2]=YourKey0[2]= YourKey1[2] = YourKey2[2] = YourKey3[2]=BefCarKey[2]=0;
	    YourKey[3]=YourKey0[3]= YourKey1[3] = YourKey2[3] = YourKey3[3]=BefCarKey[3]=0;                
	}

	if( (TmpButSta1 & S1_OPEN) || (TmpButSta3 & S3_OPEN_SUB) ){
		k= (RcvBuf[IdPt+0] -1);
		i=(k/8);
		j=(k % 8);
		k=0x01;
		k=(k<<j);

		BefCarKey[i]=(BefCarKey[i] & ~k);
	    YourKey[i]  =(YourKey[i]  & ~k);
	    YourKey0[i] =(YourKey0[i] & ~k);
	    YourKey1[i] =(YourKey1[i] & ~k);
	    YourKey2[i] =(YourKey2[i] & ~k);
	    YourKey3[i] =(YourKey3[i] & ~k);
	}
}



void    MyLampCheck(void)
{
    unsigned int i,j;
    i=0;
    j=0;
    
	i=(unsigned char)RxEidBuffer;
	
	switch(i){
	    case    0x80:
	        YourDoor0=EqualDataBuf[2];
	        YourKey0[0]=EqualDataBuf[3];
	        YourKey0[1]=EqualDataBuf[4];
	        YourKey0[2]=EqualDataBuf[5];
	        YourKey0[3]=EqualDataBuf[6];
	        j=1;
	        break;
	    case    0x81:
	        YourDoor1=EqualDataBuf[2];
	        YourKey1[0]=EqualDataBuf[3];
	        YourKey1[1]=EqualDataBuf[4];
	        YourKey1[2]=EqualDataBuf[5];
	        YourKey1[3]=EqualDataBuf[6];
	        j=1;
	        break;
	    case    0x82:
	        YourDoor2=EqualDataBuf[2];
	        YourKey2[0]=EqualDataBuf[3];
	        YourKey2[1]=EqualDataBuf[4];
	        YourKey2[2]=EqualDataBuf[5];
	        YourKey2[3]=EqualDataBuf[6];
	        j=1;
	        break;
	    case    0x83:
	        YourDoor3=EqualDataBuf[2];
	        YourKey3[0]=EqualDataBuf[3];
	        YourKey3[1]=EqualDataBuf[4];
	        YourKey3[2]=EqualDataBuf[5];
	        YourKey3[3]=EqualDataBuf[6];
	        j=1;
	        break;
	}
	
	if(j==1){    
	    YourDoor  =YourDoor0   | YourDoor1   | YourDoor2   | YourDoor3;
	    YourKey[0]=YourKey0[0] | YourKey1[0] | YourKey2[0] | YourKey3[0];
	    YourKey[1]=YourKey0[1] | YourKey1[1] | YourKey2[1] | YourKey3[1];
	    YourKey[2]=YourKey0[2] | YourKey1[2] | YourKey2[2] | YourKey3[2];
	    YourKey[3]=YourKey0[3] | YourKey1[3] | YourKey2[3] | YourKey3[3];                
	}

	ButtonReChk();
}            



/*
void    MyLampCheck(void)
{
	unsigned char i,j,k;

	k= (EqualDataBuf[1] & 0x1f);
	i=(k/8);
	j=(k % 8);
	k=0x01;
	k=(k<<j);


	if(EqualDataBuf[0] == CAN_KEY_CLEAR){
		CurCarKey[i]=(CurCarKey[i] & ~k);
	}
    else if( (EqualDataBuf[0]==CAN_KEY_SET) || (EqualDataBuf[0] == CAN_KEY_CONFIRM)){
		CurCarKey[i]=(CurCarKey[i] | k);
	}                
}

*/



unsigned char DspCharRdWr(unsigned char id)
{
    unsigned int    IdPt;
    unsigned char   ThisCurFlr;


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
void    Wait(void)
{
    unsigned char j;
    for(j=0;j<10;j++);
}



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



void    Stop_Play(void)
{
   unsigned char temp;
   temp=CurVoice;
   CurVoice=0xff;

   Play();

   CurVoice=temp;   
}
*/



void    Manual_Play(void)
{

   CurVoice=0;
   delay=0;
   VoiceAct=VOICE_ON;


   for(;1;){
        CLRWDT();	

		if(VOICE_DOWN_P)	WaitDownLoader();	
	  
		if(SPI_Play_Status_Chk())	BUSY=1;
		else						BUSY=0;
	
	      CLRWDT();
	        
	      if(!BUSY){
	         if(delay>200){
	            SPI_Play(CurVoice);  
	            CurVoice++;
	            if(CurVoice>100)     CurVoice=0;
	            delay=0;
	         }
	      }
	      else{
	        delay=0;
	      }
     
			 //     if(BUSY)  V_LAMP=0;
			 //     else      V_LAMP=1;
   }
	   
}




#ifdef	FLOOR_ANOUNCE

unsigned char   CarButton_Voice_Valid_Chk(unsigned char flr,unsigned char k)
{
	if(!(BefCarKey[flr] & k))				return(0); 
//	if( flr == (FloorX-1))					return(0); 
//	if( ButtonStatus & S2_EXT_BUT_CLR)	return(0);
//	if( ButtonStatus & S2_CAR_BUT_CLR)	return(0);

	if(FloorXCnt < 5)	return(0);

	return(1);
}


void    CarButton_Voice_Chk(unsigned char dsp_pt)
{
//    unsigned int    IdPt;
    unsigned char   f,i,valid;


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
//     	floor=(RcvBuf[IdPt] | 0x80);
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
         	//floor=FLOOR_G;
      	} 
      	else if(f == 'M'){
         	//floor=FLOOR_M;
      	}
      	else if(f == 'H'){
         	//floor=FLOOR_PH;
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
			if(YourKey[j] != BefCarKey[j]){
				if( (YourKey[j] & k) &&  !(BefCarKey[j] & k)){
//					if(!(BefCarKey[j] & k) ){
						CarButton_Voice_Chk(i);
						BefCarKey[j] = (BefCarKey[j] | k);

//						BefFloorX=FloorX;
						return(0);
//					}
				}
				else if( !(YourKey[j] & k) &&  (BefCarKey[j] & k)){

//				else{
//					if(CarButton_Voice_Valid_Chk(j,k) && (i != (FloorX-1)) ){
						BefCarKey[j] = (BefCarKey[j] & ~k);
					   	CurVoice=CANCLE_VOICE;
					   	CurFloor=CANCLE_VOICE;
//						BefFloorX=FloorX;
						return(0);
//					}

//					BefCarKey[j] = (BefCarKey[j] & ~k);
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



unsigned char	FloorAnounce_XX(void)
{

	unsigned char i,j,k;


/*
	if((CarKeySetButFlr & 0x20) && (CarKeySetButFlr != BefCarKeySetButFlr)){
		CarButton_Voice_Chk((CarKeySetButFlr & 0x1f));
		BefCarKeySetButFlr = CarKeySetButFlr;
		return(0);
	}
	else if( (CarKeyCancleButFlr & 0x20) && (CarKeyCancleButFlr != BefCarKeyCancleButFlr)){
//		CarButton_Voice_Chk( (CarKeyCancleButFlr & 0x1f));
		BefCarKeyCancleButFlr= CarKeyCancleButFlr;

	   	CurVoice=CANCLE_VOICE;
	   	CurFloor=CANCLE_VOICE;
		return(0);
	}
*/

/*
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
*/


	return(0);
}	                   

#endif




void    Serial_Flow_Voice_Chk(unsigned char id)
{
    unsigned int    IdPt;
    unsigned char f,valid;

    unsigned char BefButClrSet;
    unsigned char TmpButSta1,TmpButSta2,TmpButSta3;

	unsigned char i,j,k;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
   
	FloorX=RcvBuf[IdPt];

	if(BefFloorX != FloorX){
		FloorXCnt=0;
		BefFloorX = FloorX;
	}


ButtonReChk();




   valid=1;
   
   f=RcvBuf[IdPt+DSP1];
   if(f == 'B'){
      floor=FLOOR_1;    
   }
   else if(f == 'P'){
      floor=FLOOR_1;    
   }
   else if(f == 'G'){
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
			if(RcvBuf[IdPt+DSP1] == 'G'){
         		floor=FLOOR_G;
			}
			else  floor=(floor + 4);
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
			SPI_Stop_Play();
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





void    PortInit(void)
{
  TRISE2=1;	    // port E data direction...(output)
  TRISE1=1;
  TRISE0=1;


// TRISD Register
  TRISD7=1;	// port D data direction....(output)
  TRISD6=1;
  TRISD5=1;
  TRISD4=1;
  TRISD3=1;
  TRISD2=1;
  TRISD1=1;
  TRISD0=1;



// TRISC Register
  TRISC7=1;	// port C data direction
  TRISC6=1;
  TRISC5=1;
  TRISC4=1;
  TRISC3=1;
  TRISC2=1;
  TRISC1=1;
  TRISC0=1;


// TRISB Register
  TRISB7=1;	// port B data direction
  TRISB6=1;
  TRISB5=1;
  TRISB4=1;
  TRISB3=1;   //can rx 
  TRISB2=1;   //can tx
  TRISB1=1;   //in
  TRISB0=1;   //in


// TRISA Register
  TRISA7=1;	// port A data direction
  TRISA6=1;
  TRISA5=1;

  TRISA3=1;
  TRISA2=1;
  TRISA1=1;
  TRISA0=1;


  TRISC0=0;


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
  LATA3=1;
  LATA2=1;
  LATA1=1;
  LATA0=1;    

#ifndef		CPU45K80
	TRISA4=0;
  	LATA4=1;
#else
  TRISE0=0;
  LATE0=1;
#endif


}


void main(void)
{
    unsigned char i;
    
    di();
    Initial();
    PortInit();
    Timer0Init();
 
	InitSPI();

    Tx1ConfirmCnt=0;
    Tx0ConfirmCnt=0;

    

    ei();
    
    LoadSetupValue();  //120927 :SetupCheck() 함수 대체
    CmpSetBit=0;            //new
    MaskSetBit=0;           //new

   if(LOCAL0 && LOCAL1)         LocalNumber=0; 
   else if(!LOCAL0 && LOCAL1)   LocalNumber=1; 
   else if( LOCAL0 && !LOCAL1)  LocalNumber=2; 
   else if(!LOCAL0 && !LOCAL1)  LocalNumber=3; 


    di();
    CAN_Init();
    ei();

	FloorXCnt=0;
	for(;FloorXCnt<10;){
       CLRWDT();
	}
	FloorXCnt=0;

WriteSPI_ADDR(ADD00_SYS_CON,0x08);
WriteSPI_ADDR(ADD00_SBC_CON,0x0);
WriteSPI_ADDR(ADD00_AUDIO_CON,0x02);
WriteSPI_ADDR(ADD00_LED_CON,0xff);
WriteSPI_ADDR(ADD00_SYS_CON,0x0);

/*
ddata=ReadSPI_ADDR(ADD00_Total_CHAP_Num);
atest =  ddata;
*/


//////////////////
   VoiceAct=VOICE_OFF;

   SPI_Stop_Play();

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

		if(VOICE_DOWN_P)	WaitDownLoader();	


		if(SPI_Play_Status_Chk())	BUSY=1;
		else						BUSY=0;


		DspCharRdWr(LocalNumber);
          
        CurVoice=0xff;
      
		Serial_Flow_Voice_Chk(LocalNumber);
        Serial_Status_Voice_Check(LocalNumber);
        Serial_Emer_Voice_Check(LocalNumber);
                
               
        if(CurVoice != 0xff){
           VoiceAct=VOICE_ON;
           SelVoice=CurVoice;
           if(VoiceRun != 0){
              SPI_Stop_Play();


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
           SPI_Play(CurVoice);
           PlaySeq=31;
        }
        else if(PlaySeq==31){
           if(VoiceRun){
              PlaySeq=20;
           }
        }

        else if(PlaySeq==40){ 
           BeforeVoice=CurVoice=SelVoice;
           SPI_Play(CurVoice);
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
 /*          
        if(BUSY)  V_LAMP=0;
        else      V_LAMP=1;
*/

    }
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
    }


#ifdef	CPU45K80
    if(PIR5>0){
        CanInterrupt();
    }
#else
    if(PIR3>0){
        CanInterrupt();
    }
#endif

}











