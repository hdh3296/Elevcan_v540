//keysort.c
//setup.h
//dotlamp
//hib


//keysort_ship.c
//dotlamp_ship.c


#include    <pic18.h>

#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"

//#include        "..\..\comm_4480\cpu18f4480.h"
//#include        "..\..\can_4480\you_can.h"


/////////////////////////////////
#ifndef  __TYPE_HIB_HPI
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

                            

#define     MSEC_H    0xfc
#define     MSEC_L    0x18


//unsigned    char  LockMove; //????????        
//bit   LockOnce; //????????        


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
unsigned    char  BlinkTime;
unsigned    char  UpHallElev;
unsigned    char  DnHallElev;
unsigned    char  TopFloor;
unsigned    char  TwoDoorDrive;
unsigned    char  CallMeAdr;
unsigned    char  OnTime;
unsigned    char  SensorTime;





bit   HostCallMe;
bit   UpMove;
bit   DnMove;
bit   FloorChange;
bit   ManualToggle;
bit   CarMove;
bit   KeyClr;
//bit   OpenLampSet;
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
bit   KeyClrExt;
bit   LowOn;
bit   HighOn;
bit   BlinkOn;
bit   HallLampUpBit;
bit   HallLampDnBit;
bit   Up_Key_Valid;
bit   Up_Key_Clear;
bit   Dn_Key_Valid;
bit   Dn_Key_Clear;
bit   CurKey;
//bit   SetupBit=0;                     
bit   TogUpKeyBitSet;                     
bit   TogUpKeyBitReset;                     
bit   TogDnKeyBitSet;                     
bit   TogDnKeyBitReset;                     
bit   b_vip=0;                    
bit   b_MyFamily=0;                    
bit   bIamXSubDoor=0;                    


bit   ExtCallKey=0;                    
bit   bHALL_LAMP_UP=0;
bit   bSensorButton=0;

bit   	bCmdUpKey=0;
bit   	bCmdDnKey=0;


/*
shipshipshipshipshipshipshipship ship

unsigned char  SubDoorMainDoorCheck(void)
{
    unsigned char ret=1;

    if( bIamXSubDoor  &&  (EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
    if( !bIamXSubDoor && !(EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;

    return(ret);
}
shipshipshipshipshipshipshipship ship

*/

void	MyLampCheck(void)
{
/*			
shipshipshipshipshipshipshipship ship

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
shipshipshipshipshipshipshipship ship
    
*/
}            











void  MyAdrRead(void)
{
   	IN_ACT=0;   
   	MyAddress=0;
   
	MyAddress=(~PORTD);
	MyAddress=((MyAddress >> 2) & 0x1f);
	
   	IN_ACT=1;
}




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







void    PortInit(void)
{
	TRISA=0;
	TRISB=0;
	TRISC=0;
	TRISD=0;
	TRISE=0;

  	LATA=0;	
  	LATB=2;	
  	LATC=0;	
  	LATD=0;	
  	LATE=0;	

/*
  TRISE2=0;	    // port E data direction...(output)
  TRISE1=0;
  TRISE0=0;

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
  TRISA7=0;	// port A data direction
  TRISA6=0;
  TRISA5=0;
  TRISA4=0;
  TRISA3=0;
  TRISA2=0;
  TRISA1=0;
  TRISA0=0;
*/

/*
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
  LATA7=0;	// port A data latch
  LATA6=0;
  LATA5=0;
  LATA4=0;
  LATA3=0;
  LATA2=0;
  LATA1=0;
  LATA0=0;    
*/
}




void main(void)
{
    unsigned char confirmkey;
    
    di();

    Initial();
    PortInit();
    Timer0Init(); 

  
	UpButtonClear();
	DownButtonClear();
            
///////////////////////////////////////////////////////////////////    HALL_LAMP_UP=0;
    HALL_LAMP_DN=0;
    MANUAL_LAMP=0;
    AUTO_LAMP=0;


    Tx1ConfirmCnt=0;
    Tx0ConfirmCnt=0;

    CmpSetBit=0;            //new
    MaskSetBit=0;           //new
    
    TRISD=0xff;
    MyAdrRead();
    TRISD=0x00;

    LoadSetupValue();  //1
    CAN_Init();

    ei();
    
        
    FloorChange=0;
    BefCurFloor=0;
    ManualToggle=0;
    
        
    htpt=0;

    sec1=0;
    MoveTime[0]=0; 
   
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


	CallMeAdr=MyAddress;
	bIamXSubDoor=0;


/*
    if(SubkDoor & 0x01){
  		CallMeAdr=(MyAddress + 64);
		bIamXSubDoor=1;
	}		
*/

    HostCallMe=0;    
//    SetupBit=0;     //2
	ChangeSetup=0;


    OnTime=0;

	if(!bToggleOn){ 
	    if(ButtonType == 1){
	        OnTime=2;
	    }
	}

 
//LockMove=0;

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

/*
        if(!SetupBit){                  //3
            UpDownBlink(LocalNumber);        
            ButtonLampClrChk();                  
            UpDownKey();
        }
        else{
            SetupMode();
        }
*/


		if(bToggleOn){
			ButtonType = 0;
		}


        if(CanTxAct){
            if(!UpKeyLoad(ReceiveAdr) || (ExtCallKey)){
				if(ExtCallKey){
//ship    				CanCmd=CAN_KEY_SET;

					if( !CarMove && (CurFloor  == MyAddress)){
    					CanCmd=CAN_KEY_SET;
					}
					else	CanCmd=CAN_VIP_COMMAND;

					SelHostAdr=ReceiveAdr=LocalNumber;
        			CanKeyValue[1] = ((MyAddress-1) | CAR_READY);

				    if(bIamXSubDoor)  	CanKeyValue[2] = (CanKeyValue[2] | SUB_DOOR_BIT);
				    else            	CanKeyValue[2] = (CanKeyValue[2] & ~SUB_DOOR_BIT);
				}
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

//            if(HostCallMe && (ReceiveAdr == LocalNumber)){
            if(HostCallMe){
        		SelHostAdr=LocalNumber;                  
                CanCmd=CAN_NO_KEY_SET;
                CanKeyValue[1] = 0x0;  
				HostCallMe=0;              
                CanTx0();
            }
			CanTxAct=0;
        }            

        if(shiftTime>100){
            ShiftData();
            shiftTime=0;         
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


        P1=0;
        P2=0;

        LATE0=0;
        LATE1=0;
 
        if(bHALL_LAMP_UP)    P0=(~shiftDataBuf[htpt] | 0x80);
        else                 P0=(~shiftDataBuf[htpt] & 0x7f);



        WR_CLK=0;
        WR_CLK=1;


        if(htpt>7){
            switch(htpt){
                case  8:
                    LATC0=1;
                    break;      
                case  9:
                    LATC1=1;
                    break;      
                case  10:
                    LATC2=1;
                    break;      
                case  11:
                    LATC3=1;
                    break;      
                case  12:
                    LATC4=1;
                    break;      
                case  13:
                    LATC5=1;
                    break;      
                case  14:
                    LATC6=1;
                    break;      
                case  15:
                    LATC7=1;
                    break;      
            }
        }
        else{
            switch(htpt){
                case  0:
                    LATA0=1;
                    break;      
                case  1:
                    LATA1=1;
                    break;      
                case  2:
                    LATA2=1;
                    break;      
                case  3:
                    LATA3=1;
                    break;      
                case  4:
                    LATA4=1;
                    break;      
                case  5:
                    LATA5=1;
                    break;      
                case  6:
                    LATE0=1;
                    break;      
                case  7:
                    LATE1=1;
                    break;      
            }      
        }
            
        htpt++;
        if(htpt == 0x10){  
            htpt = 0x0;
        }


        IN_ACT=0;


        TRISD=0xff;  //nnn

		
        UpKeyBit=0;
        DnKeyBit=0;   
		ExtCallKey=0;	 
		bSensorButton=0;


		if(Auto && !Parking && !Vip){
			if(!UP_KEY_SUB){
				bSensorButton=1;

/*
				if(offset_flr == 1){			// reopen use
//ship					if( !CarMove && (CurFloor  == MyAddress)){
						bSensorButton=1;
//ship					}
				}
				else if(offset_flr == 2){
					UpKeyBit=1;
				}
*/
			}
		}

		if(bSensorButton){
			SensorTime++;
			if(SensorTime > 10){
				SensorTime=11;
				ExtCallKey=1;
			}
		}
		else	SensorTime=0;	





		UP_KEY=1;
        DN_KEY=1;
	
        if(!UP_KEY){
 			UpKeyBit=1;
		}
        if(!DN_KEY){
 			DnKeyBit=1;   
		}


/*
		if(LockMove > 50){
	        UpKeyBit=0;
	        DnKeyBit=0;   
		}

*/

        TRISD=0x00;


        IN_ACT=1;
      

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
///////////////if(UpButtonTime > 150)	UpButtonTime=150;
            }
            if(DnButtonTime < (BUT_CANLE_T - OnTime)){
                DnButtonTime++;   
///////////////if(DnButtonTime > 150)	DnButtonTime=150;
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




