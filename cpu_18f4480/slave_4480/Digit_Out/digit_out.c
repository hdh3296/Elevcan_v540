


#include    <pic18.h>



#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"


/////////////////////////////////
#ifndef  __TYPE_ES15
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
#endif

/////////////////////////////////




extern  unsigned char    Lamp(unsigned char id);  //4
extern  void    ButtonLampClrChk(void);
extern  void    ShiftData(void);
extern  void    UpDownBlink(unsigned char id);
extern  void    CompanyChk(unsigned char id);  //new

                            



unsigned    char  DisableFlr[4]   ={0,0,0,0};            

unsigned    char  CurStatus;       /*current floor */
unsigned    char  CurFloor;       /*current floor */
unsigned    char  BefCurFloor;   /*current floor */
unsigned    char  Arrowshift;    /*current floor */
unsigned    char  htpt;
unsigned    char  shift;
unsigned    char  shiftTime;
unsigned    char  MyAddress;        
unsigned    char  src;
unsigned    char  MainTimer=0;
unsigned    char  msec100=0;
unsigned    char  sec1=0;
unsigned    char  UpButtonTime=0;
unsigned    char  DnButtonTime=0;
//unsigned    char  TopFloor;



unsigned    char  UpKeyCalu[MAX_ELEV];
unsigned    char  DnKeyCalu[MAX_ELEV];
unsigned    char  MoveTime[MAX_ELEV];
unsigned    char  UpKeyEqualGood[MAX_ELEV];
unsigned    char  DnKeyEqualGood[MAX_ELEV];
//unsigned    char  CallCounter[MAX_ELEV];

unsigned    char  BlinkTime;
unsigned    char  UpHallElev;
unsigned    char  DnHallElev;


unsigned    char dsplamp0,dsplamp1;

unsigned    char  TopFloor;

unsigned    char  TwoDoorDrive;
unsigned    char  CallMeAdr;
unsigned    char  OnTime;

bit   HostCallMe;


bit   UpMove;
bit   DnMove;
bit   FloorChange;
bit   ManualToggle;
bit   CarMove;
bit   KeyClr;
bit   KeyClrExt;
bit   Auto;
bit   FDsp;
bit   Parking;
bit   Vip;
bit   Fire;
bit   ShiftOn;
bit   Open;
bit   Close;
bit   UpKeyBit;
bit   DnKeyBit;
bit   Emg;
bit   StopBit;
bit   Full;
bit   OverLoad;
//bit   UpDnBlinkBit;
//bit   TopFloorBit;
bit   LowOn;
bit   HighOn;

bit   BlinkOn;

bit   HallLampUpBit;
bit   HallLampDnBit;
bit   CurKey;


bit   Up_Key_Valid;
bit   Up_Key_Clear;
bit   Dn_Key_Valid;
bit   Dn_Key_Clear;

bit   SetupBit;                     //5

bit   TogUpKeyBitSet;                     
bit   TogUpKeyBitReset;                     
bit   TogDnKeyBitSet;                     
bit   TogDnKeyBitReset;                     

bit   b_vip=0;                    
bit   b_MyFamily=0;                    
bit   bIamXSubDoor=0;                    

bit	  bHALL_LAMP_UP=0;

const   unsigned        char    seg1[]={0x0,0x06,0x0b,0x07};
const   unsigned        char    seg0[]={0x3f,0x06,0xdb,0xcf,0xe6,0xed,0xfd,0x27,0xff,0xef,0x5c};


/*
unsigned char  	SyncButtonCheck(void)
{
	return(0);
}
*/

unsigned char  SubDoorMainDoorCheck(void)
{
    unsigned char ret=1;

    if( bIamXSubDoor  &&  (EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
    if( !bIamXSubDoor && !(EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;

    return(ret);
}

/*
unsigned char  SubDoorMainDoorCheck(void)
{
    unsigned char ret=1;

    if((SubDoor & 0x01)  &&  (EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
    if(!(SubDoor & 0x01) && !(EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;

    return(ret);
}
*/




void    MyLampCheck(void)
{


    if((EqualDataBuf[1] & 0x1f) == (MyAddress-1)){
        if(!SubDoorMainDoorCheck()){
            if(EqualDataBuf[0] == CAN_KEY_CLEAR){
                if(EqualDataBuf[1] & UP_READY){
                    UP_KEY_LAMP=0;
                    Up_Key_Valid=0;
                }
                if(EqualDataBuf[1] & DN_READY){
                    DN_KEY_LAMP=0;
                    Dn_Key_Valid=0;
                }
            }
            else if((EqualDataBuf[0] != CAN_NO_KEY_SET)){
                if((EqualDataBuf[1] & UP_READY) && (Up_Key_Clear==0)){
                    UP_KEY_LAMP=1;
                }
                if((EqualDataBuf[1] & DN_READY) && (Dn_Key_Clear==0)){
                    DN_KEY_LAMP=1;
                }
            }

        }          
    }    

}            




/*
void    UpDownKey(void)
{

    unsigned  char  i;
    unsigned  char  valid;
    unsigned  char  tmpTopFlr;
    unsigned  int   IdPt; 


    tmpTopFlr=0;
    for(i=0;i<MAX_ELEV;i++){
        IdPt=(i * HOST_DATA_RECOD) + RCV_DATA;
        if(tmpTopFlr < RcvBuf[IdPt + SL_mTopFlr]){
            tmpTopFlr=RcvBuf[IdPt + SL_mTopFlr];
        }
    }



    valid=1;
    i=0;
    
    for(i=0;i<MAX_ELEV;i++){
        if(!SelElevNoUseCheck(i)){
            if(!SelElevFlrDsbCheck(i)){
                valid=0;
            }
        }   
    }

    if(!KeyCancleCheck(LocalNumber)) valid=1;  

                
    if((valid == 0) && ((MyAddress-1) <= tmpTopFlr)){   
        if(UpKeyBit){
            if((UpButtonTime<BUT_CANLE_T) && (UpButtonTime > 0) ){
                if((MyAddress-1) < (tmpTopFlr+ButtonType)){
                    #ifdef  TOGGLE_BUTTON_ON
                    if(TogUpKeyBitSet){
                        if(!UP_KEY_LAMP){                        
                            UP_KEY_LAMP=1;
                            Up_Key_Valid=1;
                            Up_Key_Clear=0;
                            Tx1ConfirmCnt=3;
                        }
                    }                    
                    else if(TogUpKeyBitReset){
                        UP_KEY_LAMP=0;
                        Up_Key_Valid=0;
                        Up_Key_Clear=1;
                        Tx1ConfirmCnt=3;    
                    }
                    else if(!UP_KEY_LAMP){
                        UP_KEY_LAMP=1;
                        Up_Key_Valid=1;
                        Up_Key_Clear=0;
                        Tx1ConfirmCnt=3;
                        TogUpKeyBitSet=1;
                    }
                    else{                
                        UP_KEY_LAMP=0;
                        Up_Key_Valid=0;
                        Up_Key_Clear=1;
                        Tx1ConfirmCnt=3;    
                        TogUpKeyBitReset=1;
                    }
                    #else
                    if(!UP_KEY_LAMP){
                        UP_KEY_LAMP=1;
                        Up_Key_Valid=1;
                        Up_Key_Clear=0;
                        Tx1ConfirmCnt=3;
                    }
                    #endif    
                }
            }
        }
        else{
            UpButtonTime=0;
            TogUpKeyBitSet=0;
            TogUpKeyBitReset=0;
        }

               
        if(DnKeyBit){
            if((DnButtonTime<BUT_CANLE_T) && (DnButtonTime > 0) ){
                if((MyAddress > 1) || (ButtonType==1)){
                    if(ButtonType==0){
                        if(!DN_KEY_LAMP && (MyAddress > 1)){
                            DN_KEY_LAMP=1;
                            Dn_Key_Valid=1;
                            Dn_Key_Clear=0;
                            Tx0ConfirmCnt=3;
                        }
                    }
                    else{
                        if(!DnKeyOkCheck(LocalNumber)){
                            DN_KEY_LAMP=1;
                            Dn_Key_Valid=1;
                            Dn_Key_Clear=0;
                            Tx0ConfirmCnt=3;
                        }
                        else{
                            DN_KEY_LAMP=0;
                            Dn_Key_Valid=0;
                            Dn_Key_Clear=0;
                            Tx0ConfirmCnt=0;
                        }
                    }
                }

///youa
//                    if(!DnKeyOkCheck(ReceiveAdr)){                                                                
//                        #ifdef  TOGGLE_BUTTON_ON
//                        if(TogDnKeyBitSet){
//                            if(!DN_KEY_LAMP){
//                                DN_KEY_LAMP=1;
//                                Dn_Key_Valid=1;
//                                Dn_Key_Clear=0;
//                                Tx0ConfirmCnt=3;
//                            }
//                        }                    
//                        else if(TogDnKeyBitReset){
//                            DN_KEY_LAMP=0;
//                            Dn_Key_Valid=0;
//                            Dn_Key_Clear=1;
//                            Tx0ConfirmCnt=3;
//                        }
//                        else if(!DN_KEY_LAMP){
//                            DN_KEY_LAMP=1;
//                            Dn_Key_Valid=1;
//                            Dn_Key_Clear=0;
//                            Tx0ConfirmCnt=3;
//                            TogDnKeyBitSet=1;
//                        }
//                        else{                
//                            DN_KEY_LAMP=0;
//                            Dn_Key_Valid=0;
//                            Dn_Key_Clear=1;
//                            Tx0ConfirmCnt=3;    
//                            TogDnKeyBitReset=1;
//                        }
//                        #else    
//                        if(!DN_KEY_LAMP){
//                            DN_KEY_LAMP=1;
//                            Dn_Key_Valid=1;
//                            Dn_Key_Clear=0;
//                            Tx0ConfirmCnt=3;
//                        }
//    
//                        else{
//                            DN_KEY_LAMP=0;
//                            Dn_Key_Valid=0;
//                            Dn_Key_Clear=0;
//                            Tx0ConfirmCnt=0;
//                        }
//                        #endif                    
//                    }                                        
//                }
//youa/
//            }
//        }
            
//        else{
//           DnButtonTime=0;
//            TogDnKeyBitSet=0;
//            TogDnKeyBitReset=0;

//            if(ButtonType==1){
//                DN_KEY_LAMP=0;
//                Dn_Key_Valid=0;
//                Dn_Key_Clear=0;
//                Tx0ConfirmCnt=0;
//            }                        

//        }
//    }
//    else{
//        UP_KEY_LAMP=0;
//        DN_KEY_LAMP=0;  
//        DnButtonTime=0;
//        UpButtonTime=0;
//        Up_Key_Valid=0;
//        Dn_Key_Valid=0;
//        Up_Key_Clear=0;
//        Dn_Key_Clear=0;
//        Tx0ConfirmCnt=0;
//        Tx1ConfirmCnt=0;

//        TogUpKeyBitReset=0;
//        TogUpKeyBitSet=0;
//        TogDnKeyBitSet=0;
//        TogDnKeyBitReset=0;
//    }      
}
*/






/*


void    UpDownKey(void)
{
    unsigned  char  i;
    unsigned  char  valid;
    unsigned  char  tmpTopFlr;
    unsigned  int   IdPt; 


    tmpTopFlr=0;
    for(i=0;i<MAX_ELEV;i++){
        IdPt=(i * HOST_DATA_RECOD) + RCV_DATA;
        if(tmpTopFlr < RcvBuf[IdPt + SL_mTopFlr]){
            tmpTopFlr=RcvBuf[IdPt + SL_mTopFlr];
        }
    }



    valid=1;
    i=0;
    
    for(i=0;i<MAX_ELEV;i++){
        if(!SelElevNoUseCheck(i)){
            if(!SelElevFlrDsbCheck(i)){
                valid=0;
            }
        }   
    }

                
    if((valid == 0) && ((MyAddress-1) <= tmpTopFlr)){   
        if(UpKeyBit){
            if((UpButtonTime<BUT_CANLE_T) && (UpButtonTime > 0) ){
                if((MyAddress-1) < tmpTopFlr){
//                    UpButtonTime=BUT_CANLE_T;

                    if(!UP_KEY_LAMP){
                        UP_KEY_LAMP=1;
                        Up_Key_Valid=1;
                        Up_Key_Clear=0;
                        Tx1ConfirmCnt=3;
                    }

                    #ifdef  TOGGLE_BUTTON_ON
//                    else if(!UpMove || CarMove  && 
                    else if(!((CurFloor == MyAddress) && UpMove && !CarMove)){                
                        UP_KEY_LAMP=0;
                        Up_Key_Valid=0;
                        Up_Key_Clear=1;
                        Tx1ConfirmCnt=3;    
                    }
                    #endif
                }
            }
        }
        else{
            UpButtonTime=0;
        }
       
        if(DnKeyBit){
            if((DnButtonTime<BUT_CANLE_T) && (DnButtonTime > 0) ){
                if(MyAddress > 1){
//                    DnButtonTime=BUT_CANLE_T;
                    if(!DN_KEY_LAMP){
                        DN_KEY_LAMP=1;
                        Dn_Key_Valid=1;
                        Dn_Key_Clear=0;
                        Tx0ConfirmCnt=3;
                    }
                    #ifdef  TOGGLE_BUTTON_ON
//                      else if(!DnMove || CarMove  || (CurFloor != MyAddress)){                
                    else if(!((CurFloor == MyAddress) && DnMove && !CarMove)){                
//                  else{
                        DN_KEY_LAMP=0;
                        Dn_Key_Valid=0;
                        Dn_Key_Clear=1;
                        Tx0ConfirmCnt=3;
                    }
                    #endif
                }
            }
        }
        else{
            DnButtonTime=0;
        }
    }
    else{
        UP_KEY_LAMP=0;
        DN_KEY_LAMP=0;  
        DnButtonTime=0;
        UpButtonTime=0;
        Up_Key_Valid=0;
        Dn_Key_Valid=0;
        Up_Key_Clear=0;
        Dn_Key_Clear=0;
        Tx0ConfirmCnt=0;
        Tx1ConfirmCnt=0;
    }      
}

*/




/*
void  KeyClrCheck(void)
{
  unsigned char i,j,k;
   
  i=(TwoDoorAdr-1)/8;
  j=(TwoDoorAdr-1)%8;
  k=(0x01 << j);
   
  if(!(DisableFlr[i] & k)){
    if(KeyDisable < 5)  KeyDisable++;  
  }
  else if(!Auto || Fire || Parking || Vip || KeyClr){
    if(KeyDisable < 5)  KeyDisable++;
  }
  else{
    if(KeyDisable > 0)  KeyDisable--;  
  }  
}
*/


void    SetupDisplayES15(unsigned char mdata,unsigned char mode)
{
/*
   unsigned char i,t;

   if(FDsp){
        switch(mode){
            case    0: 
                t=0x1f; 
                break;
            case    2: 
                t=0x06; 
                break;
            case    3: 
                t=0x0b; 
                break;
            case    4: 
                t=0x07; 
                break;
            default:
                t=0;
                break;
        }
        i=(P2 & 0xe0);
        P2=(i | t);

        P0=seg0[mdata];         
   }
   else{
      P2=(P2 & 0xe0);
      P0=0x0;         
   }            
*/
   CLRWDT();        
}



void  MyAdrRead(void)
{
   MyAddress=0;
/*      
   if(!RA0)       MyAddress=MyAddress | 0x01;       
   if(!RA1)       MyAddress=MyAddress | 0x02;       
   if(!RA2)       MyAddress=MyAddress | 0x04;       
   if(!RA3)       MyAddress=MyAddress | 0x08;       
   if(!RA4)       MyAddress=MyAddress | 0x10;       
*/

}



void  WaitMyAdr(void)
{
/*
   unsigned char i,t;

   if(FDsp){
      MyAdrRead();
      
      t=MyAddress/10;
      t=seg1[t];
      
      i=(P2 & 0xe0);
      P2=(i | t);
                  
      t=MyAddress%10;
      P0=seg0[t];         
      DN_LAMP=0;
      UP_LAMP=0;
   }
   else{
      P2=(P2 & 0xe0);
      P0=seg0[EXT_VERSION];         
      DN_LAMP=1;
      UP_LAMP=1;
   }                    
*/
}


/*
void  WaitMyAdr(void)
{
   unsigned char i;

   if(FDsp){   
      string_load_ram(0,MyAddress);
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
*/


void    PortInit(void)
{

//input == porte,porta
//output== portd,portc,portb

  TRISE2=1;	    // port E data direction...(output)
  TRISE1=1;
  TRISE0=1;


// TRISD Register


	TRISD=0xff;
	TRISC=0xff;
	TRISB=0xff;
	TRISA=0xff;


// LATE Register
	  LATE2=1;	// port E data latch
	  LATE1=1;
	  LATE0=1;

// LATD Register
	LATD=0;
	LATC=0;
	LATB=0;
	LATA=0;




	TRISC5=0;
	TRISC6=0;

	TRISE0=0;
	TRISE1=0;
	TRISE2=0;

	TRISC0=0;
	TRISC1=0;
	TRISC2=0;
	TRISC3=0;
	TRISC4=0;

	TRISD0=0;
	TRISD1=0;
	TRISD2=0;
	TRISD3=0;    
}




void main(void)
{
    unsigned char confirmkey;
    
    di();

    Initial();
    PortInit();
    Timer0Init(); 


	UP_KEY=1;
	DN_KEY=1;


	UP_KEY_LAMP=0;
	DN_KEY_LAMP=0;
	HALL_LAMP_UP=0;
	HALL_LAMP_DN=0;
	AUTO_LAMP=0;
	
	BCD1_LAMP=0;
	BCD2_LAMP=0;
	BCD3_LAMP=0;
	BCD4_LAMP=0;
	UP_LAMP=0;
	DN_LAMP=0;
	DOOR_OPEN_LAMP=0;
	PARKING_LAMP=0;
	FULL_LAMP=0;
	MANUAL_LAMP=0;
	EMG_LAMP_B=0;
	EMG_LAMP=0;


    Up_Key_Valid=0;
    Dn_Key_Valid=0;
    Up_Key_Clear=0;
    Dn_Key_Clear=0;


    Tx1ConfirmCnt=0;
    Tx0ConfirmCnt=0;

    CmpSetBit=0;            //new
    MaskSetBit=0;           //new
    
    MyAdrRead();


    LoadSetupValue();  //1
    CAN_Init();
    ei();
    
        
    FloorChange=0;
    BefCurFloor=0;
    ManualToggle=0;
    
        
    htpt=0;

    sec1=0;
    MoveTime[0]=0; 


	CallMeAdr=MyAddress;
	bIamXSubDoor=0;

    if(SubkDoor & 0x01){
  		CallMeAdr=(MyAddress + 64);
		bIamXSubDoor=1;
	}		


    HostCallMe=0;    
    SetupBit=0;     //2
 

/*  
    do{
        if(MainTimer>5){
            MainTimer=0;
            FDsp=!FDsp;
            WaitMyAdr();            
        }
        CompanyChk(LocalNumber);  //new

        CLRWDT();
    }while(MoveTime[0] < 4);
       
    if(CmpSetBit){              //new
        CompanyWrite(Company);  //new
    }                           //new
*/

    di();                       //new
    MaskSetBit=1;               //new
    CAN_Init();                 //new
    ei();                       //new


    FDsp=1;
    MainTimer=0;
    WaitMyAdr();            
       
    CanDatacnt0=3;
    CanDatacnt1=3;
    CanCmd=0;

    OnTime=0;
    if(ButtonType == 1){
        OnTime=2;
    }


    while(1){    
        CLRWDT();
//        CanLiveChk();  //////////////////?????????????
        Lamp(LocalNumber);                  


        if(!SetupBit){                  //3
            UpDownBlink(LocalNumber);        
            ButtonLampClrChk();                  
            UpDownKey();
        }
        else{
            SetupMode();
        }

                                
        if(CanTxAct){
            if(!UpKeyLoad(ReceiveAdr)){
                CanTx1();
                HostCallMe=0;
            }
            else if(Up_Key_Valid && Tx1ConfirmCnt){
                SelHostAdr=ReceiveAdr;
                CanCmd=CAN_KEY_CONFIRM;
                confirmkey=(MyAddress-1);
                CanKeyValue[1] = (confirmkey | UP_READY);                
                CanTx1();
                HostCallMe=0;
            }            

            #ifdef  TOGGLE_BUTTON_ON
            else if(Up_Key_Clear && Tx1ConfirmCnt){
                SelHostAdr=ReceiveAdr;
                CanCmd=CAN_KEY_CLEAR;
                confirmkey=(MyAddress-1);
                CanKeyValue[1] = (confirmkey | UP_READY);                
                CanTx1();
                HostCallMe=0;
            }            
            else if(Tx1ConfirmCnt==0)   Up_Key_Clear=0;
            #endif          


            if(!DnKeyLoad(ReceiveAdr) && (ButtonType==0)){
                CanTx0();
                HostCallMe=0;
            }
            else if(Dn_Key_Valid && Tx0ConfirmCnt){
                SelHostAdr=ReceiveAdr;
                CanCmd=CAN_KEY_CONFIRM;
                confirmkey=(MyAddress-1);
                CanKeyValue[1] = (confirmkey | DN_READY);                
                CanTx0();
                HostCallMe=0;
            }

            #ifdef  TOGGLE_BUTTON_ON
            else if(Dn_Key_Clear && Tx0ConfirmCnt){
                SelHostAdr=ReceiveAdr;
                CanCmd=CAN_KEY_CLEAR;
                confirmkey=(MyAddress-1);
                CanKeyValue[1] = (confirmkey | DN_READY);                
                CanTx0();
                HostCallMe=0;
            }            
            else if(Tx0ConfirmCnt==0)   Dn_Key_Clear=0;
            #endif

            if(HostCallMe){
        		SelHostAdr=LocalNumber;                  
                CanCmd=CAN_NO_KEY_SET;
                CanKeyValue[1] = 0x0;                
				HostCallMe=0;              
                CanTx0();
            }
			CanTxAct=0;
        }            

    }
}



void interrupt isr(void)
{
    unsigned char i;
    

    if( TMR0IF )
    {
    
        TMR0IF = 0 ;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;    

        shiftTime++;

        if(!UP_KEY)	UpKeyBit=1;   
        else        UpKeyBit=0;

        if(!DN_KEY) DnKeyBit=1;   
        else        DnKeyBit=0;   
 
		UpKeyBit=0;
		DnKeyBit=0;   
              

    
        msec100++;
    
        if(msec100>100){
            msec100=0;
			NoCanInt++;                        
            for(i=0;i<MAX_ELEV;i++){          
                CanLiveTimeAdr[i]++;
            }        
            
            MainTimer++;
            BlinkTime++;
            
            if(UpButtonTime < (BUT_CANLE_T - OnTime)){
                UpButtonTime++;   
            }
            if(DnButtonTime < (BUT_CANLE_T - OnTime)){
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
      
    }

    if(PIR3>0){
        CanInterrupt();
    }
}




