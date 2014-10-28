


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


extern	void  			MyAdrRead(void);
extern	unsigned int  	MyFunc(void);
extern	void    		PortInit_X(void);



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



unsigned    char  UpKeyCalu[MAX_ELEV];
unsigned    char  DnKeyCalu[MAX_ELEV];
unsigned    char  MoveTime[MAX_ELEV];
unsigned    char  UpKeyEqualGood[MAX_ELEV];
unsigned    char  DnKeyEqualGood[MAX_ELEV];

unsigned    char  BlinkTime;
unsigned    char  UpHallElev;
unsigned    char  DnHallElev;


unsigned    char 	dsplamp0,dsplamp1;

unsigned    char  	TopFloor;

unsigned    char  	TwoDoorDrive;
unsigned    char  	CallMeAdr;
unsigned    char	OnTime;

unsigned 	char 	iocnt;
unsigned 	char 	chartTime;



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


unsigned char  SubDoorMainDoorCheck(void)
{

    unsigned char ret=1;

    if( bIamXSubDoor  &&  (EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;
    if( !bIamXSubDoor && !(EqualDataBuf[2] & SUB_DOOR_BIT))    ret=0;

    return(ret);
}



void    MyLampCheck(void)
{
}            


void    SetupDisplayES15(unsigned char mdata,unsigned char mode)
{
}

void  WaitMyAdr(void)
{
}



void    PortInit(void)
{
	PortInit_X();
}







void main(void)
{
    unsigned char confirmkey;
    unsigned int	i;

    di();

    Initial();
    PortInit();
    Timer0Init(); 


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


    if(bMainSubDoor){
  		CallMeAdr=(MyAddress + 64);
		bIamXSubDoor=1;
	}		

/*
    if(SubkDoor & 0x01){
  		CallMeAdr=(MyAddress + 64);
		bIamXSubDoor=1;
	}		
*/

    HostCallMe=0;    
    SetupBit=0;     //2


	iocnt=0x0;  
	MoveTime[0]=0;
    do{

        if(MainTimer>5){
//////////////			iotest();
            MainTimer=0;
            FDsp=!FDsp;
            WaitMyAdr();            
        }
        CompanyChk(LocalNumber);  //new

        CLRWDT();
    }while(MoveTime[0] < 4 );

     
    if(CmpSetBit){              //new
    	new_value[5]=Company;   //
        CompanyWrite();  		//new
    }                           //new


	SelHostAdr=LocalNumber;


    di();                       //new
    MaskSetBit=1;               //new
    CAN_Init();                 //new
    ei();                       //new



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

    CANSetMask(0,0x007f,0x0001c000);
    CANSetMask(1,0x007f,0x0001c000);

	REQOP2 = 0 ;
	REQOP1 = 0 ;
	REQOP0 = 0 ;


    ei();
*/


    FDsp=1;
    MainTimer=0;
    WaitMyAdr();            
       
    CanDatacnt0=3;
    CanDatacnt1=3;
    CanCmd=0;

	
	for(i=0;i<(MAX_SAVE_BUF-1);i++)	RcvBuf[i]=0;

	SelHostAdr=LocalNumber;

    while(1){    

        CLRWDT();

        Lamp(LocalNumber);
		MyFunc();




/*                  
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
*/
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
    
        msec100++;
    
        if(msec100>100){
            msec100=0;
			NoCanInt++;                        
            for(i=0;i<MAX_ELEV;i++){          
                CanLiveTimeAdr[i]++;
            }        
            
            MainTimer++;
            BlinkTime++;
			chartTime++;
    
            sec1++;
            if(sec1>10){

                sec1=0;
                for(i=0;i<MAX_ELEV;i++){          
                    MoveTime[i]++;
                }

				#ifndef	I_AM_FLOOR_ONOFF 
				LATB5=!LATB5;
				#endif
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




