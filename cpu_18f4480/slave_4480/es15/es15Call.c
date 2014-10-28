


#include    <pic18.h>
//#include    <pic18fxx8x.h>



#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"
#include        "..\..\comm_4480\esdots.h"
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

                            

extern  unsigned char	DsbChk(unsigned int id);

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
bit   DoorOpenWait;
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

bit	  bOneElevatorSel=0;


const   unsigned        char    seg1[]={0x0,0x06,0x0b,0x07};
const   unsigned        char    seg0[]={0x3f,0x06,0xdb,0xcf,0xe6,0xed,0xfd,0x27,0xff,0xef,0x5c};


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
      
   if(!RA0)       MyAddress=MyAddress | 0x01;       
   if(!RA1)       MyAddress=MyAddress | 0x02;       
   if(!RA2)       MyAddress=MyAddress | 0x04;       
   if(!RA3)       MyAddress=MyAddress | 0x08;       
   if(!RA4)       MyAddress=MyAddress | 0x10;       
}


/*
extern    unsigned char dsplamp0,dsplamp1;

extern    const   unsigned        char    seg1[];
extern    const   unsigned        char    seg0[];

//#define     EXT_VERSION     1
*/

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
  TRISA4=1;
  TRISA3=1;
  TRISA2=1;
  TRISA1=1;
  TRISA0=1;



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
  LATA4=0;
  LATA3=0;
  LATA2=0;
  LATA1=0;
  LATA0=0;    
}


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
  PEIE=0;	    // peripheral interrupt enable
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
}
*/



unsigned char	ThisCarMyFloorStop(void)
{
	if(!IsYouFlrEqualMe(xtmpadr,xTmpCurFloor))	return(0);
	if(!IsYouFlrEqualMe(xdestflr,xtmpadr))		return(0);
	if(!IsYouFlrEqualMe(0,xtmphigh))			return(0);
	if(!IsYouFlrEqualMe(0,xtmplow))				return(0);

	return(1);
}			



void main(void)
{
    unsigned char confirmkey;
    unsigned char id,onecaron;

    
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
    
    MyAdrRead();

/*
    ei();    
    SetupCheck();
    di();
*/

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
        Lamp(LocalNumber);                  

        if(!SetupBit){                  
            UpDownBlink(LocalNumber);        
            ButtonLampClrChk();                  
            UpDownKey();
        }
        else{
            SetupMode();
        }


	bOneElevatorSel=0;
	onecaron=0;
    for(id=0;id<MAX_ELEV;id++){
		UpKeyCalu[id]=0xff;	
		GetElevPointer(id);

		if(!bOneElevatorSel){
			if(!DsbChk(id)){
				if(ThisCarMyFloorStop()){				
		            if(IsCarNoneWard(xIdPt)){
						UpKeyCalu[id]=0x0;
						onecaron=1;		
						bOneElevatorSel=1;
					}
				}
				else{
					if(!IsYouFlrEqualMe(xdestflr,xtmpadr)){
			            if(IsCarNoneWard(xIdPt)){
							onecaron=1;		
							if(xtmpadr>xTmpCurFloor){
								UpKeyCalu[id]=(xtmpadr - xTmpCurFloor) + 2;
							}
							else{
								UpKeyCalu[id]=(xTmpCurFloor-xtmpadr) + 2;
							}				
						}
					}
					else{
						bOneElevatorSel=1;
						onecaron=0;		
					}
				}
			}
		}		
    }

	if(onecaron){
		SelHostAdr=0x0;
		for(id=0;id<MAX_ELEV;id++){
			if(UpKeyCalu[id] != 0xff){			
				if(UpKeyCalu[SelHostAdr] > UpKeyCalu[id])	SelHostAdr=id;		
			}
		}
	}

                                
        if(CanTxAct){
            if(onecaron){
//				if(!bOneElevatorSel){
	                CanCmd=CAN_KEY_SET;
	                confirmkey=(MyAddress-1);
	                CanKeyValue[1] = (confirmkey | CAR_READY);         
				    if(bIamXSubDoor)  	CanKeyValue[2] = (CanKeyValue[2] | SUB_DOOR_BIT);
				    else            	CanKeyValue[2] = (CanKeyValue[2] & ~SUB_DOOR_BIT);

	                CanTx1();
	                HostCallMe=0;

/*
				}
				else{

	                CanCmd=CAN_KEY_DOOR;
	
				    if(bIamXSubDoor)  	CanKeyValue[1] = 0x04;
				    else            	CanKeyValue[1] = 0x01;
	                         				
	                CanKeyValue[2]=0x01;
	                CanKeyValue[3]=0x0;
	                CanKeyValue[4]=0x0;
	                CanKeyValue[5]=0x0;
	                CanKeyValue[6]=0x0;                
	
				    if(bIamXSubDoor)  	CanKeyValue[7] = (CanKeyValue[7] | SUB_DOOR_BIT);
				    else            	CanKeyValue[7] = (CanKeyValue[7] & ~SUB_DOOR_BIT);
		
					LocalNumber=SelHostAdr;
					CallMeAdr=0x83;
				    CanDatacnt0=8;
				    CanTx0();
				    HostCallMe=0;
				
					CallMeAdr=MyAddress;
				}
*/
            }




/*
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
*/
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

    if(PIR3>0){
        CanInterrupt();
    }
}




