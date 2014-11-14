


#include    <pic18.h>
//#include    <pic18fxx8x.h>



#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"
//#include        "..\..\comm_4480\cpu18f4480.h"
//#include        "..\..\can_4480\you_can.h"


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

                            

//#define     MSEC_H    0xfc
//#define     MSEC_L    0x18


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



unsigned    char  UpKeyCalu[MAX_ELEV];
unsigned    char  DnKeyCalu[MAX_ELEV];
unsigned    char  MoveTime[MAX_ELEV];
unsigned    char  UpKeyEqualGood[MAX_ELEV];
unsigned    char  DnKeyEqualGood[MAX_ELEV];

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
bit   DoorOpenWait;
bit   OverLoad;
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


unsigned char  SubDoorMainDoorCheck(void)
{

    unsigned char ret=1;

    if( bIamXSubDoor  &&  (EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
    if( !bIamXSubDoor && !(EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;

    return(ret);
}



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








void    SetupDisplayES15(unsigned char mdata,unsigned char mode)
{

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
   CLRWDT();
        
}



void  MyAdrRead(void)
{

   MyAddress=0;
   //dip switch   
   if(!RA0)       MyAddress=MyAddress | 0x01;   //p1.0    
   if(!RA1)       MyAddress=MyAddress | 0x02;   //p1.1    
   if(!RA2)       MyAddress=MyAddress | 0x04;   //p1.2    
   if(!RA3)       MyAddress=MyAddress | 0x08;   //p1.3   

#ifdef	CPU45K80
   if(!RA5)       MyAddress=MyAddress | 0x10;  //p1.4     
#else
   if(!RA4)       MyAddress=MyAddress | 0x10;       
#endif

}



void  WaitMyAdr(void)
{

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
}




void    PortInit(void)
{

//input == porte,porta
//output== portd,portc,portb

  TRISE2=1;	    // port E data direction...(output)
  TRISE1=1;
  TRISE0=1;


// TRISD Register
  TRISD7=0;	// port D data direction....(output)
  TRISD6=0;
  TRISD5=0;
  TRISD4=0;
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
//  TRISA7=1;	// port A data direction
  TRISA6=1;
  TRISA5=1;
  TRISA3=1;
  TRISA2=1;
  TRISA1=1;
  TRISA0=1;

#ifndef	CPU45K80
  TRISA4=1;
#endif




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
//  LATA7=0;	// port A data latch
  LATA6=0;
  LATA5=0;
  LATA3=0;
  LATA2=0;
  LATA1=0;
  LATA0=0;    


#ifndef	CPU45K80
	LATA4=0;
#endif

}




void main(void)
{
    unsigned char confirmkey;
    
    di();

    Initial();
    PortInit();
    Timer0Init(); 


    UP_LAMP=0;
    DN_LAMP=0;              
    HALL_LAMP_UP=0;
    HALL_LAMP_DN=0;
    MANUAL_LAMP=0;
    AUTO_LAMP=0;
    DN_KEY_LAMP=0;
    UP_KEY_LAMP=0;
    Up_Key_Valid=0;
    Dn_Key_Valid=0;
    Up_Key_Clear=0;
    Dn_Key_Clear=0;

    Tx1ConfirmCnt=0;
    Tx0ConfirmCnt=0;

    CmpSetBit=0;            //new
    MaskSetBit=0;           //new
    
    MyAdrRead(); //dip switch Ãþ¼³Á¤.


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

    if(bMainSubDoor){
  		CallMeAdr=(MyAddress + 64);
		bIamXSubDoor=1;
	}		


    HostCallMe=0;    
	ChangeSetup=0;
   
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
    	new_value[5]=Company;   //
        CompanyWrite();  		//new
    }                           //new

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

//    for(;1;)    P0=0xf7;

    while(1){    
	    if(ChangeSetup){
			ChangeSetup=0;
			CompanyWrite();
	    }


        CLRWDT();
        CanLiveChk();  
        Lamp(LocalNumber);                  


        UpDownBlink(LocalNumber);        
        ButtonLampClrChk();                  
        UpDownKey();

                                
        if(CanTxAct){
			MyConfigSet();

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
            else if(bToggleOn){
	            if(Up_Key_Clear && Tx1ConfirmCnt){
	                SelHostAdr=ReceiveAdr;
	                CanCmd=CAN_KEY_CLEAR;
	                confirmkey=(MyAddress-1);
	                CanKeyValue[1] = (confirmkey | UP_READY);                
	                CanTx1();
	                HostCallMe=0;
	            }            
	            else if(Tx1ConfirmCnt==0)   Up_Key_Clear=0;
			}


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
			else if(bToggleOn){ 
	            if(Dn_Key_Clear && Tx0ConfirmCnt){
	                SelHostAdr=ReceiveAdr;
	                CanCmd=CAN_KEY_CLEAR;
	                confirmkey=(MyAddress-1);
	                CanKeyValue[1] = (confirmkey | DN_READY);                
	                CanTx0();
	                HostCallMe=0;
	            }            
	            else if(Tx0ConfirmCnt==0)   Dn_Key_Clear=0;
			}

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




