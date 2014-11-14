




#include    <pic18.h>

#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"
#include        "..\..\comm_4480\esdots.h"

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

bit   bCardKeyValid=0;


bit   	bCmdUpKey=0;
bit   	bCmdDnKey=0;




unsigned char  SubDoorMainDoorCheck(void)
{
    unsigned char ret=1;
    if( bIamXSubDoor  &&  (EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
    if( !bIamXSubDoor && !(EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
//    if(EqualDataBuf[2] & SUB_DOOR_BIT)    ret=0;

    return(ret);
}


void	MyLampCheck(void)
{			
	if( !(RxEidBuffer & 0x80)){
	    if((EqualDataBuf[1] & 0x1f) == (MyAddress-1)){
	        if(EqualDataBuf[0] == CAN_PARKING_COMMAND){
				bParkingIgnor=1;	
			}

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
					if(ButtonType>0){
		                if( (EqualDataBuf[1] & CAR_READY)  && (Up_Key_Clear==0)){
		                    UP_KEY_LAMP=1;
		                }
					}
					else{
		                if( (EqualDataBuf[1] & UP_READY)  && (Up_Key_Clear==0)){
		                    UP_KEY_LAMP=1;
		                }
		                if((EqualDataBuf[1] & DN_READY) && (Dn_Key_Clear==0)){
		                    DN_KEY_LAMP=1;
		                }
					}
	            }
	        }          
	    }    
	}
}            







#ifdef	CPU65K80
void  MyAdrRead(void)
{
	TRISA = 0xff;

   	MyAddress=0;

	PORTA=0xff;

	if(!RA0)	MyAddress = (MyAddress | 0x01);
	if(!RA1)	MyAddress = (MyAddress | 0x02);
	if(!RA2)	MyAddress = (MyAddress | 0x04);
	if(!RA3)	MyAddress = (MyAddress | 0x08);
	if(!RA5)	MyAddress = (MyAddress | 0x10);
	
//	MyAddress= ~PORTA;
//	MyAddress=((MyAddress >> 2) & 0x1f);	
}
#else
void  MyAdrRead(void)
{
   	IN_ACT=0;   
   	MyAddress=0;
   
	MyAddress=(~PORTD);
	MyAddress=((MyAddress >> 2) & 0x1f);
	
   	IN_ACT=1;
}

#endif



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






#ifdef	CPU65K80
void    PortInit(void)
{
	TRISA=0;
	TRISB=0;
	TRISC=0;
	TRISD=0;
	TRISE=0;
	TRISF=0;
	TRISG=0;

	TRISE=0x0f;
	TRISB=0xff;

  	LATA=0xff;	
  	LATB=0xff;	
  	LATC=0xff;	
  	LATD=0xff;	
  	LATE=0xff;	
  	LATF=0xff;	
  	LATG=0xff;	

	MANUAL_LAMP=0;
	AUTO_LAMP=0;
	USER_LAMP3=0;
	USER_LAMP4=0;
}

#else

void    PortInit(void)
{
	TRISA=0;
	TRISB=0;
	TRISC=0;
	TRISD=0;
	TRISE=0;

  	LATA=0;	
  	LATB=0;	
  	LATC=0;	
  	LATD=0;	
  	LATE=0;
	
}

#endif


/*
void	spd_dsp(unsigned char id)
{
	unsigned int spd1,spd2;
    unsigned int    IdPt;

	IdPt=IsBufferPt(id);

	spd1=(unsigned int)(RcvBuf[IdPt+SL_mUnKnown21]);
	spd2=(unsigned int)(RcvBuf[IdPt+SL_mUnKnown22] << 8);
	spd1=(spd1 | spd2);

	if(!CarMove)	spd1=0;	
	

	spd1=(spd1 % 10000);
	spd1=(spd1 / 10);   //999

	spd2=(spd1 / 100);
	spd1=(spd1 % 100);

	EngDisplay(0,(unsigned char)(spd1/10));               
	EngDisplay(6,(unsigned char)(spd1%10));               
	EngDisplay(11,(unsigned char)(spd2));

	if((spd1/10)==0){
		for(spd1=0;spd1<=5;spd1++){
			DspBuf[spd1]=0x0;
		}
	}

	if(spd2==0){
		for(spd1=11;spd1<=15;spd1++){
			DspBuf[spd1]=0x0;
		}
	}

               
	for(spd1=0;spd1<=15;spd1++){
		shiftDataBuf[spd1]=DspBuf[spd1];
	}
}
*/


void	xxx(void)
{

#ifdef	CARD_KEY
	if(bCardKeyValid && (CanCmd==CAN_KEY_SET)){
#else
	if(ExtCallKey){
#endif

		CanCmd=CAN_KEY_SET;
		SelHostAdr=ReceiveAdr=LocalNumber;
     	CanKeyValue[1] = ((MyAddress-1) | CAR_READY);

		if(!UP_KEY_SUB)   CanKeyValue[2] = (CanKeyValue[2] | HALL_SENSOR);
		else		   	  CanKeyValue[2] = (CanKeyValue[2] & ~(HALL_SENSOR));	
	}

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
    

#ifdef		 	CPU65K80			
	bParkingBd=1;
#endif
        
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

//    if(SubkDoor & 0x01){
    if(bMainSubDoor){
  		CallMeAdr=(MyAddress + 64);
		bIamXSubDoor=1;
	}		

    HostCallMe=0;    
//    SetupBit=0;     //2
	ChangeSetup=0;

    OnTime=0;

	if(!bToggleOn){ 
	    if(ButtonType == 1){
	        OnTime=2;
	    }
	}

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


		if(bToggleOn){
			ButtonType = 0;
		}



/*
#ifdef		 	CPU65K80			
		SlaveParkingChk();
#endif
*/


        if(CanTxAct){

			MyConfigSet();

            if(!UpKeyLoad(ReceiveAdr) || (ExtCallKey)){
				xxx();
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
				#ifdef	CARD_KEY
					xxx();
				#endif

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


#ifdef	CPU65K80			
			if(bParkingCmdValid && (ReceiveAdr == LocalNumber)){
        		SelHostAdr=LocalNumber;                  
                CanCmd=CAN_PARKING_COMMAND;
                CanKeyValue[1] = ((MyAddress-1) | CAR_READY);  
				HostCallMe=0;              
				bParkingCmdValid=0;
                CanTx0();

				if(ParkingCmdCnt < 200)	ParkingCmdCnt++;
			}
#endif

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

#ifdef	CPU65K80
		P0=(~shiftDataBuf[htpt]);


		if(ParkingKeyTime < 200)	ParkingKeyTime++;

		if(!HIB_PARKING_KEY){
			if(ParkingKeyTime > 100){
				bSlaveParking = 1;
				bParkingIgnor=0;	
			}
		}
		else{
			bSlaveParking = 0;
			ParkingKeyTime=0;
		}

#else
        LATE0=0;
        LATE1=0;

        if(bHALL_LAMP_UP)    P0=(~shiftDataBuf[htpt] | 0x80);
        else                 P0=(~shiftDataBuf[htpt] & 0x7f);

        WR_CLK=0;
        WR_CLK=1;
#endif
 






        if(htpt>7){
            switch(htpt){
                case  8:
                    P20=1;
                    break;      
                case  9:
                    P21=1;
                    break;      
                case  10:
                    P22=1;
                    break;      
                case  11:
                    P23=1;
                    break;      
                case  12:
                    P24=1;
                    break;      
                case  13:
                    P25=1;
                    break;      
                case  14:
                    P26=1;
                    break;      
                case  15:
                    P27=1;
                    break;      
            }
        }
        else{

            switch(htpt){
                case  0:
                    P10=1;
                    break;      
                case  1:
                    P11=1;
                    break;      
                case  2:
                    P12=1;
                    break;      
                case  3:
                    P13=1;
                    break;      
                case  4:
                    P14=1;
                    break;      
                case  5:
                    P15=1;
                    break;      
                case  6:
                    P16=1;
                    break;      
                case  7:
                    P17=1;
                    break;      
            }
      
        }
            
        htpt++;
        if(htpt == 0x10){  
            htpt = 0x0;
        }


#ifndef	CPU65K80
        IN_ACT=0;
        TRISD=0xff;  //nnn
#endif
		
        UpKeyBit=0;
        DnKeyBit=0;   
		ExtCallKey=0;	 
		bSensorButton=0;




//		if(!SetupBit && Auto && !Parking){
		if(Auto && !Parking){
			if(!UP_KEY_SUB){
				if(offset_flr == 1){			// reopen use
					if( !CarMove && (CurFloor  == MyAddress) && !Close){
						bSensorButton=1;
					}
				}
				else if(offset_flr == 2){
					UpKeyBit=1;
				}

				#ifdef	CARD_KEY
				else{
					Up_Key_Valid=1;
					Dn_Key_Valid=1;
				}
				#endif
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





#ifdef	CARD_KEY
	if(!bCardKeyValid){
	    if(!UP_KEY) 	UpKeyBit=1;   
	    if(!DN_KEY) 	DnKeyBit=1;
	}
#else
	if(!UP_KEY)		UpKeyBit=1;
	if(!DN_KEY)		DnKeyBit=1;


/*
	if( !(UP_KEY_LAMP && !Up_Key_Valid)){
		if(!bCmdUpKey){
			if(!UP_KEY)		UpKeyBit=1;
		}
	}
	if( !(DN_KEY_LAMP && !Dn_Key_Valid)){
		if(!bCmdDnKey){
			if(!DN_KEY)		DnKeyBit=1;
		}
	}
*/
#endif



#ifndef	CPU65K80
        TRISD=0x00;
        IN_ACT=1;
#endif      

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
				if(bCurOpenKey){
					if(UpButtonTime > 150)	UpButtonTime=150;
				}
            }
            if(DnButtonTime < (BUT_CANLE_T - OnTime)){
                DnButtonTime++;
				if(bCurOpenKey){
					if(DnButtonTime > 150)	DnButtonTime=150;
				}
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

#ifdef	CPU65K80
    if(PIR5>0){
        CanInterrupt();
    }
#else
    if(PIR3>0){
        CanInterrupt();
    }
#endif

}




