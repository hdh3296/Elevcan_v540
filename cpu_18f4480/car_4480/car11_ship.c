
//dotlamp_ship.c


#include    <pic18.h>
//#include    <pic18fxx8.h>

#include        "..\..\system_com\memory_map.h"
#include        "..\comm_4480\iodef.h"
#include        "..\comm_4480\fontout.h"
#include        "..\comm_4480\setup.h"
//#include        "..\comm_4480\cpu18f4480.h"
//#include        "..\can_4480\you_can.h"
//#include        "..\comm_4480\comdata.h"


//#include        "..\system_com\memory_map.h"
//#include        "..\dot_lamp\fontout.h"
//#include        "..\dot_lamp\iodef.h"
//#include        "..\dot_lamp\setup.h"
//#include        "..\18f448_can\you_can.h"


/////////////////////////////////
#ifndef  __TYPE_CAR
     #error  "\nType Not Define Error(iodef.h)"
     #error  "\nType Not Define Error(iodef.h)"
     #error  "\nType Not Define Error(iodef.h)"
     #error  "\nType Not Define Error(iodef.h)"
     #error  "\nType Not Define Error(iodef.h)"
#endif

/////////////////////////////////

extern  unsigned char  Lamp(unsigned char id);   //5
//extern  void    ButtonLampClrChk(void);
extern  void    ShiftData(void);
//extern  void    UpDownBlink(unsigned char id);
extern  void    CompanyChk(unsigned char id);  //new





extern  int     KeyLoad(unsigned char id);



#define         ON            1
#define         OFF           0





#define     MSEC_H    0xfc
#define     MSEC_L    0x18


unsigned    char  DisableFlr[4]={0,0,0,0};            
unsigned    char  BefDisableFlr[4]={0,0,0,0};            
unsigned    char  DoorKey=0;            
unsigned    char  CarKey[4]={0,0,0,0};            
unsigned    char  ToggleKey[4]={0,0,0,0};
unsigned    char  newscan[4] ={0,0,0,0};
unsigned    char  oldscan[4] ={0,0,0,0};
unsigned    char  scantime[4]={0,0,0,0};
unsigned    char  ClrKey[4]={0,0,0,0};

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

unsigned    char  TopFloor;
unsigned    char  CurFloor;          /*current floor */
unsigned    char  BellTime;          /* bell time */
unsigned    char  OffsetAdr;          /* bell time */
unsigned    char  MyAddress;        
//unsigned    char  src;
//unsigned    char  firstdata;
//unsigned    char  seconddata;
unsigned    char  Arrowshift;    
unsigned    char  htpt;
unsigned    char  BefCurFloor;
unsigned    char  shift;
unsigned    char  shiftTime;
unsigned    char  MainTimer;   
unsigned    char  msec100;
unsigned    char  UpButtonTime;
unsigned    char  DnButtonTime;
unsigned    char  EqualFlr;
unsigned    char  HighFlr;
unsigned    char  LowFlr;

                    
unsigned    char    Door;
unsigned    char    sfttime;
unsigned    char    ButCnt;
unsigned    char    RstTimer;
unsigned    char    KeyClrTime;
unsigned    char    DisableOnOff;
unsigned    char    DoorSel;
unsigned    char    YourLiveTimer;


unsigned    char  MoveTime[MAX_ELEV];
unsigned    char  BlinkTime;

unsigned    char  TwoDoorDrive;
unsigned    char  CallMeAdr;


bit   HostCallMe;

bit   BlinkOn;
bit   Up_Key_Valid;
bit   Dn_Key_Valid;
bit   Open;
bit   Close;


bit   Bell;
bit   BellSet;
bit   UpMove;
bit   DnMove;
bit   Toggle;
bit   CarMove;
bit   Fire;
bit   KeyClr;
bit   OpenLampSet;
bit   KeyClrExt;
bit   Auto;
bit   Parking;
bit   Vip;
bit   BefVip;
bit   FloorChange;
bit   ManualToggle;
bit   FDsp;
bit   ShiftOn;
//bit   OpenSet;
bit   OnceMoveCar;
/////////////
bit   UpKeyBit;   
bit   DnKeyBit;   
bit   Emg;   
bit   CurKey;
bit   sft;   
bit   StopBit;
bit   Full;
bit   OverLoad;
bit   Car_Key_Valid;
bit   SetupBit;         
bit   EqualKeyOn;         
bit   bIamXSubDoor=0;                    
bit   bRealOpenkey=0;
bit   bDoorOpenWaitOn=0;

bit   bBefDoorOpen=0;


//extern	bit		Alarm;
//extern	bit		NoRunErr;
extern	bit		ArrivalFlow;
extern	bit		DoorOpenSig;
extern	bit		Rolling;
extern	bit 	Co2Foam; 


unsigned char  SyncButtonCheck(void)
{
	if(SrcAddress  == SelHostAdr)	return(1);
	else							return(0);
}



unsigned char  SubDoorMainDoorCheck(void)
{
    unsigned char ret=1;

    if( bIamXSubDoor  &&  (EqualDataBuf[7] & SUB_DOOR_BIT))    ret=0;
    if( !bIamXSubDoor && !(EqualDataBuf[7] & SUB_DOOR_BIT))    ret=0;

    if(EqualDataBuf[7] & SUB_DOOR_BIT){
        if(TwoDoorDrive < 100)   TwoDoorDrive++;                                                                          
    }

    return(ret);
}


void    MyLampCheck(void)
{
    unsigned int i,j;
    i=0;
    j=0;
    
    if(SelHostAdr == ReceiveAdr){
    
        if(!SubDoorMainDoorCheck()){    
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
        }
    }
}            






unsigned char SetHighFloor(unsigned char i)
{

    unsigned char j,k,l=0;
   
    k=HighFlr;
   
    if((!UpMove && !DnMove) || UpMove){
        j=(HighFlr & ONLY_FLR);
   
        if(j == 0)        HighFlr = (i |  CAR_READY);
        else if(j > i)    HighFlr = (i |  CAR_READY);
        else if(j < i){
            if((HighFlr & UPDN_CAR_READY)== DN_READY)   HighFlr = (i |  CAR_READY);            
            else if(!(HighFlr & UPDN_CAR_READY))   HighFlr = (i |  CAR_READY);   
            else{
                ButCnt++;
                l=1;   
            }            
        }
        else if(j == i) HighFlr = (HighFlr |  CAR_READY);
    }

    if(l==1)                        return(1);
    if(k != HighFlr)                return(0);
    else                            return(1);
}



unsigned char SetLowFloor(unsigned char i)
{
       unsigned char j,k,l=0;
    
       k=LowFlr;
       
       if((!UpMove && !DnMove) || DnMove){
          j=(LowFlr & ONLY_FLR);      
          if(j == 0)  LowFlr = (i |  CAR_READY);      
          else if(j < i)  LowFlr = (i |  CAR_READY);
          else if(j > i){
             if((LowFlr & UPDN_CAR_READY) == UP_READY)   LowFlr = (i |  CAR_READY);   
             else if(!(LowFlr & UPDN_CAR_READY))   LowFlr = (i |  CAR_READY);   
             else{
                ButCnt++;   
                l=1;
             }            
          }        
          else if(j == i) LowFlr = (LowFlr |  CAR_READY);
       }
    
       if(l==1)          return(1);
       if(k != LowFlr)   return(0);
       else              return(1);
}







unsigned char  CarKeyLoad(unsigned char id)
{

    unsigned char  i,j,k,ret,Curf; 

    ret=1;
    k=0x01; 
    j=0;
    Curf=(CurFloor-1);
       
    ButCnt=0;
    EqualKeyOn=0;

    for(i=0;i<32;i++){
//    for(i=0;i<24;i++){
        if(CarKey[j] & k){            
            if(i>Curf){
                if(!SetHighFloor(i)) ret=0;
            }
            else if(i<Curf){
                if(!SetLowFloor(i))  ret=0;
            }
            else{                
                if(EqualFlr)    EqualFlr=(EqualFlr | CAR_READY);            
                else            EqualFlr=(i | CAR_READY);

                EqualKeyOn=1;
                ret=0;
            }
        }     
        
        k=(k<<1);
        
        if(k==0){
            k=0x01;
            j++;
        }  
    }  
    


    if((ButCnt>0) && !(Door & CAR_READY)){        
        Door=(Door | CAR_READY);
        ret=0;
    }


    DoorSel = 0;

    if(((bRealOpenkey) || CLOSE_LAMP) &&  !CarMove){
       if(bIamXSubDoor){
       		if(bRealOpenkey){
     			DoorSel = (DoorSel | 0x04);
				if(bDoorOpenWaitOn)	DoorSel = (DoorSel | 0x10);	
			}
          	else if(CLOSE_LAMP)  DoorSel = (DoorSel | 0x08);
       }         
       else{
          	if(bRealOpenkey){
  				DoorSel=DoorSel | 0x01;
				if(bDoorOpenWaitOn)	DoorSel = (DoorSel | 0x10);	
			}
          	if(CLOSE_LAMP) 	DoorSel=DoorSel | 0x02;
       }     
       ret=0;      
    }

   return(ret); 
}



unsigned char NoKeyClr(unsigned char srcflr)
{
    unsigned char  i,j,k;       

    if(srcflr & CAR_READY){          
        i=(srcflr & ONLY_FLR)/8;                              
        j=(srcflr & ONLY_FLR)%8;
        k=(0x01 << j);
        if( (!(CarKey[i] & k)) && (ToggleKey[i] & k) ){
            srcflr =  (srcflr  &  ~CAR_READY);
            if(TwoDoorDrive > 10)   ToggleKey[i] = (ToggleKey[i] & ~k);
        }
    }
       
    return(srcflr);
}



unsigned char  NoKeyCheck(unsigned char id)
{ 
    unsigned char  i,ret;
    unsigned int    IdPt;

    ret=1;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;

    EqualFlr=(RcvBuf[IdPt + mEqualFloor]);
    HighFlr=(RcvBuf[IdPt + mHighFloor]);
    LowFlr=(RcvBuf[IdPt + mLowFloor]);

    i=NoKeyClr(EqualFlr);
    if(i != EqualFlr){
       EqualFlr=i;
       ret=0;
    }

    i=NoKeyClr(HighFlr);
    if(i != HighFlr){
       HighFlr=i;
       ret=0;
    }    

    i=NoKeyClr(LowFlr);
    if(i != LowFlr){
       LowFlr=i;
       ret=0;
    }

    return(ret); 
}



int KeyLoad(unsigned char id)
{ 
    int i=1;
    int j=0;
    unsigned char hi,lo,eq,dr;
    unsigned int IdPt;

    CanCmd=CAN_NO_KEY_SET;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
    
    hi=RcvBuf[IdPt+mHighFloor];
    lo=RcvBuf[IdPt+mLowFloor];
    eq=RcvBuf[IdPt+mEqualFloor];
    dr=RcvBuf[IdPt+mDoor];


    EqualFlr=eq;
    HighFlr=hi;
    LowFlr=lo;


    if(!NoKeyCheck(id) && !Fire){
        i=0;
        if(hi != HighFlr){
            CanCmd=CAN_KEY_CLEAR;
            CanKeyValue[1] = (HighFlr & ONLY_FLR) | CAR_READY;            
        }
        else if(lo != LowFlr){
            CanCmd=CAN_KEY_CLEAR;
            CanKeyValue[1] = (LowFlr & ONLY_FLR) | CAR_READY;            
        }
        else if(eq !=  EqualFlr){
            CanCmd=CAN_KEY_CLEAR;
            CanKeyValue[1] = (EqualFlr & ONLY_FLR) | CAR_READY;            
        } 
        else i=1;
    }
    else if(!CarKeyLoad(id)){ 
        i=0;
        if(DoorSel){
            CanCmd=CAN_KEY_DOOR;
            CanKeyValue[1] = DoorSel;            
        }
        else  if(hi != HighFlr){
            CanCmd=CAN_KEY_SET;
            CanKeyValue[1] = (HighFlr & ONLY_FLR) | CAR_READY;            
        }
        else if(lo != LowFlr){
            CanCmd=CAN_KEY_SET;
            CanKeyValue[1] = (LowFlr & ONLY_FLR) | CAR_READY;            
        }
        else if((eq !=  EqualFlr) || (EqualKeyOn &&  Close && !CarMove)){
            if( bIamXSubDoor && !(dr & 0x04)){
                CanCmd=CAN_KEY_SET;
                CanKeyValue[1] = (EqualFlr & ONLY_FLR) | CAR_READY;            
            }
            else if( !bIamXSubDoor && !(dr & 0x01)){
                CanCmd=CAN_KEY_SET;
                CanKeyValue[1] = (EqualFlr & ONLY_FLR) | CAR_READY;            
            }
            else    i=1;
        }
        else i=1;
    }


/*
    else if(!NoKeyCheck(id) && !Fire){
        i=0;
        if(hi != HighFlr){
            CanCmd=CAN_KEY_CLEAR;
            CanKeyValue[1] = (HighFlr & ONLY_FLR) | CAR_READY;            
        }
        else if(lo != LowFlr){
            CanCmd=CAN_KEY_CLEAR;
            CanKeyValue[1] = (LowFlr & ONLY_FLR) | CAR_READY;            
        }
        else if(eq !=  EqualFlr){
            CanCmd=CAN_KEY_CLEAR;
            CanKeyValue[1] = (EqualFlr & ONLY_FLR) | CAR_READY;            
        } 
        else i=1;
    }
*/


    if(Fire || Vip){
//ship        j=(CarKey[0] | YourKey[0] | CarKey[1] | YourKey[1] | CarKey[2] | YourKey[2] | CarKey[3] | YourKey[3] | YourDoor | DoorKey);
        j=(CarKey[0] | YourKey[0] | CarKey[1] | YourKey[1] | CarKey[2] | YourKey[2] | YourDoor | DoorKey);
        if(j==0){
            if(hi | lo | eq | dr){
                CanCmd=ALL_KEY_CLEAR;
                CanKeyValue[1] = 0x0;
                i=0;             
            }
        }
    }  


    return(i);
}






/*
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
*/


void  MyLocalAdr(void)
{

   if(MULTI_ADR0 && MULTI_ADR1){
      SelHostAdr=0;
   }            
   else if(!MULTI_ADR0 && MULTI_ADR1){
      SelHostAdr=1;
   }            
   else if(MULTI_ADR0 && !MULTI_ADR1){
      SelHostAdr=2;
   }            
   else if(!MULTI_ADR0 && !MULTI_ADR1){
      SelHostAdr=3;
   } 

//	if(MAX_ELEV == 8)	SelHostAdr=4;
           
}



void  MyAdrRead(void)
{

   if(DIPS2 && DIPS3){
      MyAddress=0;
   }            
   else if(!DIPS2 && DIPS3){
      MyAddress=1;
   }      
   else if( DIPS2 && !DIPS3){
      MyAddress=2;
   }      
   else{
      MyAddress=3;
   }      

   MyAddress=MyAddress | 0x80;
}



void  WaitMyAdr(void)
{
   unsigned char i;
   
//   MyAdrRead();

   if(FDsp){ 
      if(MyAddress == 0x80)        i='1';
      else if(MyAddress == 0x81)   i='2';
      else if(MyAddress == 0x82)   i='3';
      else if(MyAddress == 0x83)   i='4';

      
      Floor_Char_load(0,'C',i);

      EngDisplay(11,EXT_VERSION);             
      for(i=0;i<=15;i++){
         shiftDataBuf[i]=DspBuf[i];
      }
   }
   else{
      for(i=0;i<=15;i++){
         shiftDataBuf[i]=0x0;
      }   
   }                    
}



void  KeyClearAll(void)
{
   unsigned char  i,j,k,l;
   l=3;
   i=0;
   j=0;
   k=0;
   
   
   if(KeyClr && CarMove){   
      i=(CurFloor-1)/8;                              
      j=((CurFloor-1))%8;
      k=(0x01 << j);   
      j = (CarKey[i] & k);        
   }
   

   for(k=0;k<l;k++){
      if((i==k) && Auto){
		CarKey[k] = j;
      }        
      else{
        CarKey[k] = 0x0;        
      }  

      ToggleKey[k]  = 0x0;      
      YourKey0[k]   = 0x0;
      YourKey1[k]   = 0x0;
      YourKey2[k]   = 0x0;
      YourKey3[k]   = 0x0;
      YourKey[k]    = 0x0;
   }
   
}



void  FloorCalu(unsigned char id)
{

    unsigned int IdPt;
    unsigned char i;
    
    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;



    i=0;
    if((RcvBuf[IdPt + mEqualFloor]==0) &&  (RcvBuf[IdPt + mHighFloor]==0) && (RcvBuf[IdPt + mLowFloor]==0)){
//        if(!CarMove && !UpMove && !DnMove && !OpenSet){
        if(!CarMove && !UpMove && !DnMove && !Open){
            if(YourKey[0] | YourKey[1] | YourKey[2] | YourKey[3]){
                i=1;
            }
        } 
    }

    if(i==0)    YourLiveTimer=0;
}




void  MasterRetKeySave(unsigned char id)
{
    unsigned int IdPt;
    unsigned char  dsbtmp[4];

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;

	dsbtmp[0]=RcvBuf[IdPt + FLR_ON_OFF0];
   	dsbtmp[1]=RcvBuf[IdPt + FLR_ON_OFF1];
   	dsbtmp[2]=RcvBuf[IdPt + FLR_ON_OFF2];
   	dsbtmp[3]=RcvBuf[IdPt + FLR_ON_OFF3];

   if((BefDisableFlr[0] == dsbtmp[0]) &&
      (BefDisableFlr[1] == dsbtmp[1]) &&  
      (BefDisableFlr[2] == dsbtmp[2]) &&  
      (BefDisableFlr[3] == dsbtmp[3])){
         DisableOnOff++;
         if(DisableOnOff > 5){  

            DisableFlr[0]=dsbtmp[0];
            DisableFlr[1]=dsbtmp[1];
            DisableFlr[2]=dsbtmp[2];
            DisableFlr[3]=dsbtmp[3];
            DisableOnOff=0;
         }            
   }
   else{
     DisableOnOff=0;   
   }
   
   BefDisableFlr[0]=dsbtmp[0];
   BefDisableFlr[1]=dsbtmp[1];
   BefDisableFlr[2]=dsbtmp[2];
   BefDisableFlr[3]=dsbtmp[3];


/*
   if((BefDisableFlr[0] == RcvBuf[IdPt + FLR_ON_OFF0]) &&
      (BefDisableFlr[1] == RcvBuf[IdPt + FLR_ON_OFF1]) &&  
      (BefDisableFlr[2] == RcvBuf[IdPt + FLR_ON_OFF2]) &&  
      (BefDisableFlr[3] == RcvBuf[IdPt + FLR_ON_OFF3])){
         DisableOnOff++;
         if(DisableOnOff > 5){  
            DisableFlr[0]=RcvBuf[IdPt + FLR_ON_OFF0];
            DisableFlr[1]=RcvBuf[IdPt + FLR_ON_OFF1];
            DisableFlr[2]=RcvBuf[IdPt + FLR_ON_OFF2];
            DisableFlr[3]=RcvBuf[IdPt + FLR_ON_OFF3];
            DisableOnOff=0;
         }            
   }
   else{
     DisableOnOff=0;   
   }
   
   BefDisableFlr[0]=RcvBuf[IdPt + FLR_ON_OFF0];
   BefDisableFlr[1]=RcvBuf[IdPt + FLR_ON_OFF1];
   BefDisableFlr[2]=RcvBuf[IdPt + FLR_ON_OFF2];
   BefDisableFlr[3]=RcvBuf[IdPt + FLR_ON_OFF3];
 */  
}







void  io(void)
{    
   unsigned char a;
   unsigned char tmp,extkey;
   

   a=htpt%4;
   
   if(a==0){
      SEL0=0;
      SEL1=0;
      SEL2=0;
      SEL_ACT=0;

//yousangyong
    tmp=IN_DATA_PORT;
    tmp=IN_DATA_PORT;
//      tmp=IN_DATA_PORT;
//      tmp=IN_DATA_PORT;

      newscan[0]=~tmp;

      extkey=~YourKey[0];  
      newscan[0]=(newscan[0] & extkey); 

      SEL_ACT=1;      
   }

   else if(a==1){
      SEL0=1;
      SEL1=0;
      SEL2=0;
      SEL_ACT=0;
      tmp=IN_DATA_PORT;
      tmp=IN_DATA_PORT;
      newscan[1]=~tmp;
      extkey=~YourKey[1];  
      newscan[1]=(newscan[1] & extkey); 
      SEL_ACT=1;
   }

   else if(a==2){
      SEL0=0;
      SEL1=1;
      SEL2=0;
      SEL_ACT=0;
      tmp=IN_DATA_PORT;
      tmp=IN_DATA_PORT;
      newscan[2]=~tmp;
      extkey=~YourKey[2];  
      newscan[2]=(newscan[2] & extkey); 
      SEL_ACT=1;   
   }
      
   else if(a==3){
      SEL0=1;
      SEL1=1;
      SEL2=0;
      SEL_ACT=0;
      tmp=IN_DATA_PORT;
      tmp=IN_DATA_PORT;
      newscan[3]=~tmp;

      extkey=~YourKey[3];  
      newscan[3]=(newscan[3] & extkey);    
      SEL_ACT=1;
   }  
}



void    CarLampNormal(unsigned char id)
{

    unsigned int IdPt;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
    
    MasterRetKeySave(id);

    Lamp(id);


///////////////////////    if(SetupBit)    SetupMode();                      //3

    FloorCalu(id);
      
    if( ((!bIamXSubDoor) && (RcvBuf[IdPt+1] & S1_OPEN)) || ((bIamXSubDoor==1) && (RcvBuf[IdPt+3] & S3_OPEN_SUB))){
    
       switch(CurFloor){
          case  1:
             CarKey[0]    = CarKey[0]   & 0xfe;
             ToggleKey[0] =ToggleKey[0] & 0xfe;
             YourKey0[0]  = YourKey0[0] & 0xfe;
             YourKey1[0]  = YourKey1[0] & 0xfe;
             YourKey2[0]  = YourKey2[0] & 0xfe;
             YourKey3[0]  = YourKey3[0] & 0xfe;
             break;
          case  2:            
             CarKey[0]    = CarKey[0]    & 0xfd;
             ToggleKey[0] = ToggleKey[0] & 0xfd;
             YourKey0[0]  = YourKey0[0]  & 0xfd;
             YourKey1[0]  = YourKey1[0]  & 0xfd;
             YourKey2[0]  = YourKey2[0]  & 0xfd;
             YourKey3[0]  = YourKey3[0]  & 0xfd;
             break;
          case  3:            
             CarKey[0]    = CarKey[0]    & 0xfb;  
             ToggleKey[0] = ToggleKey[0] & 0xfb;
             YourKey0[0]  = YourKey0[0]  & 0xfb;
             YourKey1[0]  = YourKey1[0]  & 0xfb;
             YourKey2[0]  = YourKey2[0]  & 0xfb;
             YourKey3[0]  = YourKey3[0]  & 0xfb;
             break;
          case  4:            
             CarKey[0]    = CarKey[0]    & 0xf7;
             ToggleKey[0] = ToggleKey[0] & 0xf7;
             YourKey0[0]  = YourKey0[0]  & 0xf7;
             YourKey1[0]  = YourKey1[0]  & 0xf7;
             YourKey2[0]  = YourKey2[0]  & 0xf7;
             YourKey3[0]  = YourKey3[0]  & 0xf7;
             break;
          case  5:            
             CarKey[0]    = CarKey[0]    & 0xef;
             ToggleKey[0] = ToggleKey[0] & 0xef;
             YourKey0[0]  = YourKey0[0]  & 0xef;
             YourKey1[0]  = YourKey1[0]  & 0xef;
             YourKey2[0]  = YourKey2[0]  & 0xef;
             YourKey3[0]  = YourKey3[0]  & 0xef;
             break;
          case  6:            
             CarKey[0]    = CarKey[0]    & 0xdf;
             ToggleKey[0] = ToggleKey[0] & 0xdf;
             YourKey0[0]  = YourKey0[0]  & 0xdf;
             YourKey1[0]  = YourKey1[0]  & 0xdf;
             YourKey2[0]  = YourKey2[0]  & 0xdf;
             YourKey3[0]  = YourKey3[0]  & 0xdf;
             break;
          case  7:            
             CarKey[0]    = CarKey[0]    & 0xbf;
             ToggleKey[0] = ToggleKey[0] & 0xbf;
             YourKey0[0]  = YourKey0[0]  & 0xbf;
             YourKey1[0]  = YourKey1[0]  & 0xbf;
             YourKey2[0]  = YourKey2[0]  & 0xbf;
             YourKey3[0]  = YourKey3[0]  & 0xbf;
             break;
          case  8:            
             CarKey[0]    = CarKey[0]    & 0x7f;
             ToggleKey[0] = ToggleKey[0] & 0x7f;
             YourKey0[0]  = YourKey0[0]  & 0x7f;
             YourKey1[0]  = YourKey1[0]  & 0x7f;
             YourKey2[0]  = YourKey2[0]  & 0x7f;
             YourKey3[0]  = YourKey3[0]  & 0x7f;
             break;            
          case  9:            
             CarKey[1]    = CarKey[1]    & 0xfe;
             ToggleKey[1] = ToggleKey[1] & 0xfe;
             YourKey0[1]  = YourKey0[1]  & 0xfe;
             YourKey1[1]  = YourKey1[1]  & 0xfe;
             YourKey2[1]  = YourKey2[1]  & 0xfe;
             YourKey3[1]  = YourKey3[1]  & 0xfe;
             break;
          case  10:            
             CarKey[1]    = CarKey[1]    & 0xfd;
             ToggleKey[1] = ToggleKey[1] & 0xfd;
             YourKey0[1]  = YourKey0[1]  & 0xfd;
             YourKey1[1]  = YourKey1[1]  & 0xfd;
             YourKey2[1]  = YourKey2[1]  & 0xfd;
             YourKey3[1]  = YourKey3[1]  & 0xfd;
             break;
          case  11:            
             CarKey[1]    = CarKey[1]    & 0xfb;
             ToggleKey[1] = ToggleKey[1] & 0xfb;
             YourKey0[1]  = YourKey0[1]  & 0xfb;
             YourKey1[1]  = YourKey1[1]  & 0xfb;
             YourKey2[1]  = YourKey2[1]  & 0xfb;
             YourKey3[1]  = YourKey3[1]  & 0xfb;
             break;
          case  12:            
             CarKey[1]    = CarKey[1]    & 0xf7;
             ToggleKey[1] = ToggleKey[1] & 0xf7;
             YourKey0[1]  = YourKey0[1]  & 0xf7;
             YourKey1[1]  = YourKey1[1]  & 0xf7;
             YourKey2[1]  = YourKey2[1]  & 0xf7;
             YourKey3[1]  = YourKey3[1]  & 0xf7;
             break;
          case  13:            
             CarKey[1]    = CarKey[1]    & 0xef;
             ToggleKey[1] = ToggleKey[1] & 0xef;
             YourKey0[1]  = YourKey0[1]  & 0xef;
             YourKey1[1]  = YourKey1[1]  & 0xef;
             YourKey2[1]  = YourKey2[1]  & 0xef;
             YourKey3[1]  = YourKey3[1]  & 0xef;
             break;
          case  14:            
             CarKey[1]    = CarKey[1]    & 0xdf;
             ToggleKey[1] = ToggleKey[1] & 0xdf;
             YourKey0[1]  = YourKey0[1]  & 0xdf;
             YourKey1[1]  = YourKey1[1]  & 0xdf;
             YourKey2[1]  = YourKey2[1]  & 0xdf;
             YourKey3[1]  = YourKey3[1]  & 0xdf;
             break;
          case  15:            
             CarKey[1]    = CarKey[1]    & 0xbf;
             ToggleKey[1] = ToggleKey[1] & 0xbf;
             YourKey0[1]  = YourKey0[1]  & 0xbf;
             YourKey1[1]  = YourKey1[1]  & 0xbf;
             YourKey2[1]  = YourKey2[1]  & 0xbf;
             YourKey3[1]  = YourKey3[1]  & 0xbf;
             break;
          case  16:            
             CarKey[1]    = CarKey[1]    & 0x7f;
             ToggleKey[1] = ToggleKey[1] & 0x7f;
             YourKey0[1]  = YourKey0[1]  & 0x7f;
             YourKey1[1]  = YourKey1[1]  & 0x7f;
             YourKey2[1]  = YourKey2[1]  & 0x7f;
             YourKey3[1]  = YourKey3[1]  & 0x7f;
             break;
          case  17:            
             CarKey[2]    = CarKey[2]    & 0xfe;
             ToggleKey[2] = ToggleKey[2] & 0xfe;
             YourKey0[2]  = YourKey0[2]  & 0xfe;
             YourKey1[2]  = YourKey1[2]  & 0xfe;
             YourKey2[2]  = YourKey2[2]  & 0xfe;
             YourKey3[2]  = YourKey3[2]  & 0xfe;
             break;
          case  18:            
             CarKey[2]    = CarKey[2]    & 0xfd;
             ToggleKey[2] = ToggleKey[2] & 0xfd;
             YourKey0[2]  = YourKey0[2]  & 0xfd;
             YourKey1[2]  = YourKey1[2]  & 0xfd;
             YourKey2[2]  = YourKey2[2]  & 0xfd;
             YourKey3[2]  = YourKey3[2]  & 0xfd;
             break;
          case  19:            
             CarKey[2]    = CarKey[2]    & 0xfb;
             ToggleKey[2] = ToggleKey[2] & 0xfb;
             YourKey0[2]  = YourKey0[2]  & 0xfb;
             YourKey1[2]  = YourKey1[2]  & 0xfb;
             YourKey2[2]  = YourKey2[2]  & 0xfb;
             YourKey3[2]  = YourKey3[2]  & 0xfb;
             break;
          case  20:            
             CarKey[2]    = CarKey[2]    & 0xf7;
             ToggleKey[2] = ToggleKey[2] & 0xf7;
             YourKey0[2]  = YourKey0[2]  & 0xf7;
             YourKey1[2]  = YourKey1[2]  & 0xf7;
             YourKey2[2]  = YourKey2[2]  & 0xf7;
             YourKey3[2]  = YourKey3[2]  & 0xf7;
             break;
          case  21:            
             CarKey[2]    = CarKey[2]    & 0xef;
             ToggleKey[2] = ToggleKey[2] & 0xef;
             YourKey0[2]  = YourKey0[2]  & 0xef;
             YourKey1[2]  = YourKey1[2]  & 0xef;
             YourKey2[2]  = YourKey2[2]  & 0xef;
             YourKey3[2]  = YourKey3[2]  & 0xef;
             break;
          case  22:            
             CarKey[2]    = CarKey[2]    & 0xdf;
             ToggleKey[2] = ToggleKey[2] & 0xdf;
             YourKey0[2]  = YourKey0[2]  & 0xdf;
             YourKey1[2]  = YourKey1[2]  & 0xdf;
             YourKey2[2]  = YourKey2[2]  & 0xdf;
             YourKey3[2]  = YourKey3[2]  & 0xdf;
             break;
          case  23:            
             CarKey[2]    = CarKey[2]    & 0xbf;
             ToggleKey[2] = ToggleKey[2] & 0xbf;
             YourKey0[2]  = YourKey0[2]  & 0xbf;
             YourKey1[2]  = YourKey1[2]  & 0xbf;
             YourKey2[2]  = YourKey2[2]  & 0xbf;
             YourKey3[2]  = YourKey3[2]  & 0xbf;
             break;
          case  24:            
             CarKey[2]    = CarKey[2]    & 0x7f;
             ToggleKey[2] = ToggleKey[2] & 0x7f;
             YourKey0[2]  = YourKey0[2]  & 0x7f;
             YourKey1[2]  = YourKey1[2]  & 0x7f;
             YourKey2[2]  = YourKey2[2]  & 0x7f;
             YourKey3[2]  = YourKey3[2]  & 0x7f;
             break;
/*
          case  25:            
             CarKey[3]    = CarKey[3]    & 0xfe;
             ToggleKey[3] = ToggleKey[3] & 0xfe;
             YourKey0[3]  = YourKey0[3]  & 0xfe;
             YourKey1[3]  = YourKey1[3]  & 0xfe;
             YourKey2[3]  = YourKey2[3]  & 0xfe;
             YourKey3[3]  = YourKey3[3]  & 0xfe;
             break;
          case  26:            
             CarKey[3]    = CarKey[3]    & 0xfd;
             ToggleKey[3] = ToggleKey[3] & 0xfd;
             YourKey0[3]  = YourKey0[3]  & 0xfd;
             YourKey1[3]  = YourKey1[3]  & 0xfd;
             YourKey2[3]  = YourKey2[3]  & 0xfd;
             YourKey3[3]  = YourKey3[3]  & 0xfd;
             break;
          case  27:            
             CarKey[3]    = CarKey[3]    & 0xfb;
             ToggleKey[3] = ToggleKey[3] & 0xfb;
             YourKey0[3]  = YourKey0[3]  & 0xfb;
             YourKey1[3]  = YourKey1[3]  & 0xfb;
             YourKey2[3]  = YourKey2[3]  & 0xfb;
             YourKey3[3]  = YourKey3[3]  & 0xfb;
             break;
          case  28:            
             CarKey[3]    = CarKey[3]    & 0xf7;
             ToggleKey[3] = ToggleKey[3] & 0xf7;
             YourKey0[3]  = YourKey0[3]  & 0xf7;
             YourKey1[3]  = YourKey1[3]  & 0xf7;
             YourKey2[3]  = YourKey2[3]  & 0xf7;
             YourKey3[3]  = YourKey3[3]  & 0xf7;
             break;
          case  29:            
             CarKey[3]    = CarKey[3]    & 0xef;
             ToggleKey[3] = ToggleKey[3] & 0xef;
             YourKey0[3]  = YourKey0[3]  & 0xef;
             YourKey1[3]  = YourKey1[3]  & 0xef;
             YourKey2[3]  = YourKey2[3]  & 0xef;
             YourKey3[3]  = YourKey3[3]  & 0xef;
             break;
          case  30:            
             CarKey[3]    = CarKey[3]    & 0xdf;
             ToggleKey[3] = ToggleKey[3] & 0xdf;
             YourKey0[3]  = YourKey0[3]  & 0xdf;
             YourKey1[3]  = YourKey1[3]  & 0xdf;
             YourKey2[3]  = YourKey2[3]  & 0xdf;
             YourKey3[3]  = YourKey3[3]  & 0xdf;
             break;
          case  31:            
             CarKey[3]    = CarKey[3]    & 0xbf;
             ToggleKey[3] = ToggleKey[3] & 0xbf;
             YourKey0[3]  = YourKey0[3]  & 0xbf;
             YourKey1[3]  = YourKey1[3]  & 0xbf;
             YourKey2[3]  = YourKey2[3]  & 0xbf;
             YourKey3[3]  = YourKey3[3]  & 0xbf;
             break;
          case  32:            
             CarKey[3]    = CarKey[3]    & 0x7f;
             ToggleKey[3] = ToggleKey[3] & 0x7f;
             YourKey0[3]  = YourKey0[3]  & 0x7f;
             YourKey1[3]  = YourKey1[3]  & 0x7f;
             YourKey2[3]  = YourKey2[3]  & 0x7f;
             YourKey3[3]  = YourKey3[3]  & 0x7f;
             break;
*/
       }

        YourKey[0]=YourKey0[0] | YourKey1[0] | YourKey2[0] | YourKey3[0];
        YourKey[1]=YourKey0[1] | YourKey1[1] | YourKey2[1] | YourKey3[1];
        YourKey[2]=YourKey0[2] | YourKey1[2] | YourKey2[2] | YourKey3[2];
        YourKey[3]=YourKey0[3] | YourKey1[3] | YourKey2[3] | YourKey3[3];
    }
}



void    SetKey(unsigned char    pt,unsigned char tfloor)
{
    unsigned char i,st;

      
    st=0x01;
    for(i=0;i<8;i++){      
        if((oldscan[pt] & st) && ((TopFloor+1) >= (tfloor+i))){        
            if(!(ClrKey[pt] & st)){
                ClrKey[pt]   = ClrKey[pt] | st;
				BellTime=0;               
                Car_Key_Valid=1;
                Tx0ConfirmCnt=3;

                if((CarKey[pt] & st) && !Fire){
                    if(Toggle){
                        CarKey[pt] = CarKey[pt] & ~st;
                        ToggleKey[pt]  = ToggleKey[pt]  |  st;
                    }               
                }
                else if(CurFloor != (tfloor+i)){
                    CarKey[pt] = CarKey[pt] | st;
                    ToggleKey[pt]  = ToggleKey[pt]  & ~st;
                }
            }               
			if(CurKey) BellTime=0; 
        }
        else{
            ClrKey[pt]   = ClrKey[pt] & ~st;
            if(CurKey){
                CarKey[pt] = CarKey[pt] & ~st;
                ToggleKey[pt]  = ToggleKey[pt]  &  ~st;          
            }
        }            
        st=st << 1;
    }   
}





void  SetKeyButton(void)
{ 
   	unsigned char i,j,k,l;

	l=3;
//    unsigned int    IdPt;


   if((newscan[0] == oldscan[0])){
      if(scantime[0]>60){
         SetKey(0,1);
         scantime[0]=0;
      }
   }
   else{
      scantime[0]=0x0;
      oldscan[0]=newscan[0];
   }

   if((newscan[1] == oldscan[1])){
      if(scantime[1]>60){
         SetKey(1,9);
         scantime[1]=0;
      }
   }
   else{
      scantime[1]=0x0;
      oldscan[1]=newscan[1];
   }

   if((newscan[2] == oldscan[2])){
      if(scantime[2]>60){
         SetKey(2,17);
         scantime[2]=0;
      }
   }
   else{
      scantime[2]=0x0;
      oldscan[2]=newscan[2];
   }


   if((newscan[3] == oldscan[3])){
      if(scantime[3]>60){
         SetKey(3,25);
         scantime[3]=0;
      }
   }
   else{
      scantime[3]=0x0;
      oldscan[3]=newscan[3];
   }
 

   for(j=0;j<l;j++){   
      k=0x01;
      if((DisableFlr[j] != 0xff) && !Fire){
         for(i=0;i<8;i++){            
            if(!(DisableFlr[j] & k)){
               CarKey[j] = CarKey[j] & ~k;
               ToggleKey[j]  = ToggleKey[j]  & ~k;
            }
            k=(k << 1);
         }
      }
   }
 


   if(CurKey){   
     for(j=0;j<l;j++){      
        ClrKey[j]     = 0x0;  
        ToggleKey[j]  = 0x0;
        CarKey[j]     = oldscan[j];   
      }         
   }
		


	if(Vip){
		if(!CarMove){		
			if(!BefVip){
				BefVip=Vip;
		     	for(j=0;j<l;j++){      
		        	ClrKey[j]     = 0x0;  
		        	ToggleKey[j]  = 0x0;
		        	CarKey[j]     = 0x0;   
		      	}         
			}
		}
		else	BefVip = !Vip;		
	}   
	else{
		BefVip=Vip;
	}



/*
//////
if(Auto && !CarMove){
	    IdPt=(LocalNumber * HOST_DATA_RECOD) + RCV_DATA;
	
		if((RcvBuf[IdPt + 21 ] == 57)){  //open
			if( !bBefDoorOpen){
	            KeyClearAll();  
	            KeyClrTime=0;
				DoorKey=(DoorKey & 0xfd);				
			}
			bBefDoorOpen=1;  
		}
		else if((RcvBuf[IdPt + 21 ] == 58)){ //close
			bBefDoorOpen=0;
		}
	

//		if(Auto && !CarMove && Open){
		if(Open){
			for(j=0;j<4;j++){   
		      	k=0x01;
				for(i=0;i<8;i++){            
					if(CarKey[j] & k){
				         CLOSE_LAMP=1;
				         DoorKey=DoorKey | 0x02;				
					}
					k=(k << 1);
				}
		   	}
		}
}
////////
*/




//open wait
//////////////////////////////
//////////////////////////////

//	CarKey[3]= 0;
	bDoorOpenWaitOn=0;
	if(Auto && !CarMove){
		if(newscan[3] & 0x80){
			OPEN_LAMP=1;
		 	bRealOpenkey=1;
         	DoorKey=DoorKey | 0x01;
			CarKey[3]= (CarKey[3] | 0x80);
		}
	}

	if(!Auto || CarMove || Close){
		CarKey[3]= (CarKey[3] & 0x7f);
	}

/*

	else{
		CarKey[3]= (CarKey[3] & 0x7f);
	}

	if(Close)	CarKey[3]= (CarKey[3] & 0x7f);	   
*/



/*
	if(RcvBuf[S1_STATE] & S1_MANUAL)			CarKey[3]= (CarKey[3] | 0x02);
	else										CarKey[3]= (CarKey[3] & 0xfd);
	if(RcvBuf[S2_STATE] & S2_LAMP_USER)			CarKey[3]= (CarKey[3] | 0x01);
	else										CarKey[3]= (CarKey[3] & 0xfe);
	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_UP)  	CarKey[3]= (CarKey[3] | 0x04);
	else										CarKey[3]= (CarKey[3] & 0xfb);
	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_DN)  	CarKey[3]= (CarKey[3] | 0x08);
	else										CarKey[3]= (CarKey[3] & 0xf7);

	if(Fire)  									CarKey[3]= (CarKey[3] | 0x10);
	else										CarKey[3]= (CarKey[3] & 0xef);

	if(StopBit | Co2Foam)  						CarKey[3]= (CarKey[3] | 0x20);
	else										CarKey[3]= (CarKey[3] & 0xdf);

	if(Rolling)  								CarKey[3]= (CarKey[3] | 0x40);
	else										CarKey[3]= (CarKey[3] & 0xbf);
*/


                                             
//open wait
//////////////////////////////
//////////////////////////////


}


void    CarUpDownKeyNormal(void)
{
/*
	bDoorOpenWaitOn=0;
	if(Auto && !CarMove && (newscan[3] & 0x80)){
		bDoorOpenWaitOn=1;
		oldscan[3]= (oldscan[3] | 0x80);
	}
*/

   if(UpKeyBit || bDoorOpenWaitOn){
      if((UpButtonTime<BUT_CANLE_T) && (UpButtonTime > 0) ){
         OPEN_LAMP=1;
		 bRealOpenkey=1;
         DoorKey=DoorKey | 0x01;
      }
      else{
         OPEN_LAMP=0;
		 bRealOpenkey=0;
         DoorKey=DoorKey & 0xfe;
      }      
   }
   else{
      OPEN_LAMP=0;
	  bRealOpenkey=0;

      UpButtonTime=0;
      DoorKey=DoorKey & 0xfe;
   }
   


   if(DnKeyBit && !Close && Auto){
      if((DnButtonTime<BUT_CANLE_T) && (DnButtonTime > 0)){
         CLOSE_LAMP=1;
         DoorKey=DoorKey | 0x02;
      }
      else{
         CLOSE_LAMP=0;
         DoorKey=DoorKey & 0xfd;
      }         
   }
   else{
      CLOSE_LAMP=0;
      DnButtonTime=0;
      DoorKey=DoorKey & 0xfd;
   }

	
	if(!bRealOpenkey && OpenLampSet){
         OPEN_LAMP=1;
	}

   SetKeyButton();
}






void    PortInit(void)
{
  TRISE2=0;	    // port E data direction...(output)
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
  TRISC7=0;	// port C data direction
  TRISC6=1;
  TRISC5=1;
  TRISC4=0;
  TRISC3=0;
  TRISC2=0;
  TRISC1=0;
  TRISC0=0;



// TRISB Register
  TRISB7=0;	// port B data direction
  TRISB6=0;
  TRISB5=1;
  TRISB4=0;
  TRISB3=1;   //can rx 
  TRISB2=0;   //can tx
  TRISB1=1;   //in
  TRISB0=1;   //in

// TRISA Register
  TRISA7=0;	// port A data direction
  TRISA6=0;
  TRISA5=0;
  TRISA4=0;
  TRISA3=0;
  TRISA2=0;
  TRISA1=0;
  TRISA0=0;


// LATE Register
  LATE2=0;	// port E data latch
  LATE1=0;
  LATE0=0;

// LATD Register
  LATD7=0;	// port D data latch
  LATD6=0;
  LATD5=0;
  LATD4=0;
  LATD3=0;
  LATD2=0;
  LATD1=0;
  LATD0=0;

  LATD7=1;	// port D data latch
  LATD6=1;
  LATD5=1;
  LATD4=1;
  LATD3=1;
  LATD2=1;
  LATD1=1;
  LATD0=1;

// LATC Register
  LATC7=0;	// port C data latch
  LATC6=0;
  LATC5=0;
  LATC4=0;
  LATC3=0;
  LATC2=0;
  LATC1=0;
  LATC0=0;

// LATB Register
  LATB7=0;	// port B data latch
  LATB6=0;
  LATB5=0;
  LATB4=0;
  LATB3=0;
  LATB2=0;
  LATB1=1;
  LATB0=0;

// LATA Register
  LATA7=0;	// port A data latch
  LATA6=0;
  LATA5=0;
  LATA4=0;
  LATA3=0;
  LATA2=0;
  LATA1=0;
  LATA0=0;    
}

  
void main(void)
{
	unsigned char i;

    di();

    Initial();
    PortInit();
    Timer0Init(); 


    MyLocalAdr();
    MyAdrRead();


    CmpSetBit=0;            //new
    MaskSetBit=0;           //new

    LoadSetupValue();  //1
	LocalNumber=0;

    CAN_Init();    
    ei();

    MainTimer=0;
    KeyClrTime=0;



    do{
        if(MainTimer>5){
            MainTimer=0;
            FDsp=!FDsp;
            WaitMyAdr();            
        }
        CompanyChk(LocalNumber);  //new
        CLRWDT();
    }while(KeyClrTime<40);


    if(CmpSetBit){              //new
    	new_value[5]=Company;   //
        CompanyWrite();  		//new
    }                           //new

//    if(CmpSetBit){              //new
//        CompanyWrite(Company);  //new
//    }                           //new


    di();                       //new
    MaskSetBit=1;               //new
    CAN_Init();                 //new
    ei();                       //new


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

    CANSetMask(0,0x007f,0x0001c000);
    CANSetMask(1,0x007f,0x0001c000);


	REQOP2 = 0 ;
	REQOP1 = 0 ;
	REQOP0 = 0 ;



    ei();


//    SetupCheck();


//    DspModel=1;

	bHibHpiSel=1;
       
    SEL_ACT=1;
    SEL0=1;
    SEL1=1;
    SEL2=1;

    CanCmd=0x0;
    CanDatacnt0=0x8;
    CanDatacnt1=0x2;

    TwoDoorDrive=0;

   for(OffsetAdr=0;OffsetAdr<4;OffsetAdr++){
      CarKey[OffsetAdr] =0x0;
      newscan[OffsetAdr]=0x0;
      oldscan[OffsetAdr]=0x0;
      YourKey[OffsetAdr]=0x0;
      YourKey0[OffsetAdr]=0x0;
      YourKey1[OffsetAdr]=0x0;
      YourKey2[OffsetAdr]=0x0;
      YourKey3[OffsetAdr]=0x0;
   }         
   
   OPEN_LAMP=0;
   CLOSE_LAMP=0;
   OPEN_KEY=1;
   CLOSE_KEY=1;

   WR_CLK=1;

   DATA_PORT=0xff;

   
   Toggle=0;   
   TOGGLE=1;   
   if(!TOGGLE)   Toggle=1;      
   

   P2=0xff;

   BELL=1;
   BellTime=100;
   
   MainTimer=0;
   RstTimer=0;
   Car_Key_Valid=0;
   Tx0ConfirmCnt=0;


	bIamXSubDoor=0;
    if(bMainSubDoor)	bIamXSubDoor=1;

//	bIamXSubDoor=0;
//    if(SubkDoor & 0x01)	bIamXSubDoor=1;

//  CallMeAdr=(MyAddress + 64);
//  else                CallMeAdr=(MyAddress);

    CallMeAdr=(MyAddress);
    HostCallMe=0;    
    SetupBit=0;                     //2
	ChangeSetup=0;

	LocalNumber=SelHostAdr;

   while(1){

/*
/////////////
    RcvBuf[DSP1] = 'B';
    RcvBuf[DSP2] = '1';

    RcvBuf[1]=(RcvBuf[1] | S1_UP);
    RcvBuf[1]=(RcvBuf[1] | S1_AUTO);

    CanLiveTimeAdr[0] = 0;
	NoCanInt=0;
    FloorChange=1;   
////////////
*/

	    if(ChangeSetup){
			ChangeSetup=0;
			CompanyWrite();
	    }

        CLRWDT();            

        CanLiveChk();

        if(bIamXSubDoor)    CanKeyValue[7]=(CanKeyValue[7] |  SUB_DOOR_BIT);                
        else                CanKeyValue[7]=(CanKeyValue[7] & ~SUB_DOOR_BIT);                
                                
        if(CanTxAct){
			i=CarKey[3];
			if( !(newscan[3] & 0x80))	i=(i & 0x7f);	

            if(!KeyLoad(SelHostAdr)){
                CanKeyValue[2]=DoorKey;
                CanKeyValue[3]=CarKey[0];
                CanKeyValue[4]=CarKey[1];
                CanKeyValue[5]=CarKey[2];
                CanKeyValue[6]=i;                
                CanTx0();
				LIVE_LAMP=!LIVE_LAMP;
				HostCallMe=0;
            }          
            else if((Car_Key_Valid && (Tx0ConfirmCnt) )){
                CanCmd=CAN_KEY_CONFIRM;
                CanKeyValue[2]=DoorKey;
                CanKeyValue[3]=CarKey[0];
                CanKeyValue[4]=CarKey[1];
                CanKeyValue[5]=CarKey[2];
                CanKeyValue[6]= i;                
                CanTx0();
				LIVE_LAMP=!LIVE_LAMP;
				HostCallMe=0;
            }

            else if(HostCallMe){
                CanCmd=CAN_NO_KEY_SET;
                CanKeyValue[2]=DoorKey;
                CanKeyValue[3]=CarKey[0];
                CanKeyValue[4]=CarKey[1];
                CanKeyValue[5]=CarKey[2];
                CanKeyValue[6]= i;                
                CanTx0();
				LIVE_LAMP=!LIVE_LAMP;
				HostCallMe=0;
            }
        	CanTxAct=0;
        }            
        CarLampNormal(SelHostAdr);              
        io();           
        CarUpDownKeyNormal();
       

        if(shiftTime > 100){         
            ShiftData();
            shiftTime=0;
        }                  

        
//        if(sft && Auto && !KeyClr && !Parking && !KeyClrExt && (MyAddress==A_CAR1)){
        if(sft && Auto && !KeyClr && !Parking && (MyAddress==A_CAR1)){
			BellTime=0;
        }

                    
        if((Auto==0) || KeyClr || Parking || (YourLiveTimer>10) || Vip){
            KeyClearAll();  
            KeyClrTime=0;
        }        

    }
}




void interrupt isr(void)
{

    unsigned char a,i,tmp;


    if( TMR0IF )
    {
        TMR0IF = 0 ;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;
        
        CanTime++;
        
        scantime[0]++;
        scantime[1]++;
        scantime[2]++;
        scantime[3]++;
        
        
        BellTime++;
        
        if(BellTime<100){
            BELL=0;
        }
        else{
            BELL=1;
            BellTime=100;
        }

        
        tmp=P1;

        TRISD=0x00;       
 
        SEL_ACT=1;
        
        shiftTime++;
        
        DSP_OFF=1;
        
        DATA_PORT=shiftDataBuf[htpt];
        
        WR_CLK=0;   
        WR_CLK=1;
        
        P2=(htpt | 0xf0);      
        
        DSP_OFF=0;
        
        htpt++;
        
        if(htpt == 0x10){  
            htpt = 0x0;
        }
        
        
        a=htpt%4;
        
        if(a==0){         
            DATA_PORT=(CarKey[0] | YourKey[0]);
            SEL0=0;
            SEL1=0;
            SEL2=1;

            SEL_ACT=0;            
            SEL_ACT=1; 
        }
        
        else if(a==1){
            DATA_PORT=(CarKey[1] | YourKey[1]);
            SEL0=1;
            SEL1=0;
            SEL2=1;
            SEL_ACT=0;
            SEL_ACT=1;
        }
        
        else if(a==2){
            DATA_PORT=(CarKey[2] | YourKey[2]);
            SEL0=0;
            SEL1=1;
            SEL2=1;
            SEL_ACT=0;   
            SEL_ACT=1;   
        }
        
        else if(a==3){   
///            DATA_PORT=(CarKey[3] | YourKey[3]);
            DATA_PORT=(CarKey[3]);
            SEL0=1;
            SEL1=1;
            SEL2=1;
            SEL_ACT=0;
            SEL_ACT=1;
        }   
        
        DATA_PORT=0xff;
        TRISD=0xff;       

        
        CLOSE_KEY=1;
        OPEN_KEY=1;
        
        if(!OPEN_KEY)  UpKeyBit=1;   
        else           UpKeyBit=0;   
        if(!CLOSE_KEY) DnKeyBit=1;   
        else           DnKeyBit=0;
        
        
        msec100++;
        if(msec100>100){
            msec100=0;
			NoCanInt++;
            sfttime++;
            MainTimer++;
            KeyClrTime++;
            YourLiveTimer++;

            if(UpButtonTime<BUT_CANLE_T){
                UpButtonTime++;   
            }
            if(DnButtonTime<BUT_CANLE_T){
                DnButtonTime++;   
            }      

            for(i=0;i<MAX_ELEV;i++){          
                CanLiveTimeAdr[i]++;
            }                

        }  
                
        P1=tmp;   
    }


    if(PIR3>0){
        CanInterrupt();
    }

}





