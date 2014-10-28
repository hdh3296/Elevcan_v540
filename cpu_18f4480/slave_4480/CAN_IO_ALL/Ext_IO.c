

#include    <pic18.h>



#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"
#include        "..\..\comm_4480\esdots.h"



#if   defined(I_AM_EXT_IO_ONOFF) 


#define  OUT_FAN	IO_00         
#define  OUT_LIT	IO_01        
#define  OUT_BUZ	IO_02
#define  OUT_BELL   IO_03


#define  IN_SAFETY	IO_08         
#define  IN_OVL		IO_09        
#define  IN_VIP		IO_10
#define  IN_FULL   	IO_11



//bit	b_safety,b_overload,b_vip,b_full;


void  MyAdrRead(void)
{
   MyAddress=0;
   MyAddress=0x8b;
}





void    PortInit_X(void)
{

  	TRISE2=1;	    // port E data direction...(output)
  	TRISE1=1;
  	TRISE0=1;

  	TRISA=0xff;
  	TRISB=0xff;
  	TRISC=0xff;
  	TRISD=0x00;
	

	PORTA=0xff;
	PORTB=0xff;
	PORTC=0xff;
	PORTD=0x00;
	
	PORTE=0xff;
//	PORTE1=1;
//	PORTE2=1;


/*
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
  TRISA4=1;
  TRISA3=1;
  TRISA2=1;
  TRISA1=1;
  TRISA0=1;



// LATE Register
  LATE2=1;	// port E data latch
  LATE1=1;
  LATE0=1;
	RE2=1;	
	RE1=1;	
	RE0=1;	

// LATD Register
  LATD7=1;	// port D data latch
  LATD6=1;
  LATD5=1;
  LATD4=1;
  LATD3=1;
  LATD2=1;
  LATD1=1;
  LATD0=1;
	PORTD=0xff;

// LATC Register
  LATC7=1;	// port C data latch
  LATC6=1;
  LATC5=1;
  LATC4=1;
  LATC3=1;
  LATC2=1;
  LATC1=1;
  LATC0=1;
	PORTC=0xff;

// LATB Register
  LATB7=1;	// port B data latch
  LATB6=1;
  LATB5=1;
  LATB4=1;
  LATB3=1;
  LATB2=1;
  LATB1=1;
  LATB0=1;
	PORTB=0xff;

// LATA Register
  LATA7=1;	// port A data latch
  LATA6=1;
  LATA5=1;
  LATA4=1;
  LATA3=1;
  LATA2=1;
  LATA1=1;
  LATA0=1;
	PORTA=0xff;


  TRISB5=0;		//RUN LED 
  TRISB3=1;   	//can rx 
  TRISB2=0;   	//can tx

  LATB5=0;		//RUN LED
  LATB3=1;		//can rx
  LATB2=0;		//can tx
*/

}




unsigned int  MyFunc(void)
{
	unsigned	char	tmpbuf;
    unsigned 	int    IdPt;


    IdPt=(LocalNumber * HOST_DATA_RECOD) + RCV_DATA;


	if(RcvBuf[IdPt + SL_OUT_FAN] & 0x01)	OUT_FAN=1;
	else									OUT_FAN=0;

	if(RcvBuf[IdPt + SL_OUT_FAN] & 0x02)	OUT_LIT=1;
	else									OUT_LIT=0;
	
	if(RcvBuf[IdPt + SL_OUT_FAN] & 0x04)	OUT_BUZ=1;
	else									OUT_BUZ=0;

	if(RcvBuf[IdPt + SL_OUT_FAN] & 0x08)	OUT_BELL=1;
	else									OUT_BELL=0;


	tmpbuf=0xff;
	if( !IN_SAFETY)	tmpbuf= (tmpbuf & 0xfe); 
	if( !IN_OVL)	tmpbuf= (tmpbuf & 0xfd); 
	if( !IN_VIP)	tmpbuf= (tmpbuf & 0xfb); 
	if( !IN_FULL)	tmpbuf= (tmpbuf & 0xf7); 


	if(RcvBuf[IdPt + SL_mEXT_IN0]  != tmpbuf){
		BlinkTime=10;
	}


	if(BlinkTime >= 10){
        if(CanTxAct){
			CanDatacnt1=8;
            CanCmd=tmpbuf;
            CanKeyValue[1]=0x0;
            CanKeyValue[2]=0x0;
            CanKeyValue[3]=0x0;
            CanKeyValue[4]=0x0;
            CanKeyValue[5]=0x0;
            CanKeyValue[6]=0x0;
			CanKeyValue[7]=0x0;
            Tx1ConfirmCnt=1;

            CanTx1();

			if(Tx1ConfirmCnt==0){
				BlinkTime = 0;
			}	
		}		
	}

	return(1);
}


#endif
