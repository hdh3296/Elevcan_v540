

#include    <pic18.h>



#include        "..\..\..\system_com\memory_map.h"
#include        "..\..\comm_4480\iodef.h"
#include        "..\..\comm_4480\fontout.h"
#include        "..\..\comm_4480\comdata.h"
#include        "..\..\comm_4480\keysort.h"
#include        "..\..\comm_4480\setup.h"
#include        "..\..\comm_4480\esdots.h"



#if   defined(I_AM_FLOOR_ONOFF) 


void  MyAdrRead(void)
{
   MyAddress=0;
   MyAddress=0x8a;
}





void    PortInit_X(void)
{

  TRISE2=1;	    // port E data direction...(output)
  TRISE1=1;
  TRISE0=1;


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

}




unsigned int  MyFunc(void)
{
	unsigned	char	tx_chk,tmpkey[4];
    unsigned 	int    IdPt;


	tx_chk=1;


    IdPt=(LocalNumber * HOST_DATA_RECOD) + RCV_DATA;


	tmpkey[0]=UpKeyCalu[0];
	tmpkey[1]=UpKeyCalu[1];
	tmpkey[2]=UpKeyCalu[2];
	tmpkey[3]=UpKeyCalu[3];			

	UpKeyCalu[0]=0xff;
	UpKeyCalu[1]=0xff;
	UpKeyCalu[2]=0xff;
	UpKeyCalu[3]=0xff;

	if(!IO_00)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xfe);
	if(!IO_01)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xfd);
	if(!IO_02)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xfb);
	if(!IO_03)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xf7);
	if(!IO_04)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xef);
	if(!IO_05)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xdf);
	if(!IO_06)	UpKeyCalu[0]=(UpKeyCalu[0] & 0xbf);
	if(!IO_07)	UpKeyCalu[0]=(UpKeyCalu[0] & 0x7f);

	if(!IO_08)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xfe);
	if(!IO_09)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xfd);
	if(!IO_10)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xfb);
	if(!IO_11)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xf7);
	if(!IO_12)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xef);
	if(!IO_13)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xdf);
	if(!IO_14)	UpKeyCalu[1]=(UpKeyCalu[1] & 0xbf);
	if(!IO_15)	UpKeyCalu[1]=(UpKeyCalu[1] & 0x7f);

	if(!IO_16)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xfe);
	if(!IO_17)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xfd);
	if(!IO_18)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xfb);
	if(!IO_19)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xf7);
	if(!IO_20)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xef);
	if(!IO_21)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xdf);
	if(!IO_22)	UpKeyCalu[2]=(UpKeyCalu[2] & 0xbf);
	if(!IO_23)	UpKeyCalu[2]=(UpKeyCalu[2] & 0x7f);


	if(!IO_24)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xfe);
	if(!IO_25)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xfd);
	if(!IO_26)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xfb);
	if(!IO_27)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xf7);
	if(!IO_28)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xef);
	if(!IO_29)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xdf);
	if(!IO_30)	UpKeyCalu[3]=(UpKeyCalu[3] & 0xbf);
	if(!IO_31)	UpKeyCalu[3]=(UpKeyCalu[3] & 0x7f);


	if((tmpkey[0]==UpKeyCalu[0]) && (tmpkey[1]==UpKeyCalu[1]) && (tmpkey[2]==UpKeyCalu[2]) && (tmpkey[3]==UpKeyCalu[3])){
		if(chartTime > 1){
			DnKeyCalu[0]=UpKeyCalu[0];
			DnKeyCalu[1]=UpKeyCalu[1];
			DnKeyCalu[2]=UpKeyCalu[2];
			DnKeyCalu[3]=UpKeyCalu[3];
			chartTime=2;			
		}		
	}
	else{
		chartTime=0;
	}

	if(BlinkTime > 30){
		tx_chk=0;
	}
	else{
		if( (RcvBuf[IdPt + FLR_ON_OFF0] != DnKeyCalu[0]) || (RcvBuf[IdPt + FLR_ON_OFF1] != DnKeyCalu[1]) || (RcvBuf[IdPt + FLR_ON_OFF2] != DnKeyCalu[2]) 
			|| (RcvBuf[IdPt + FLR_ON_OFF3] != DnKeyCalu[3])){
				tx_chk=0;
				BlinkTime =40;	
		}
	}


	if(tx_chk==0){
        if(CanTxAct){
			CanDatacnt1=8;
            CanCmd=DnKeyCalu[0];
            CanKeyValue[1]=DnKeyCalu[1];
            CanKeyValue[2]=DnKeyCalu[2];
            CanKeyValue[3]=DnKeyCalu[3];
            CanKeyValue[4]=0x0;
            CanKeyValue[5]=0x0;
            CanKeyValue[6]=0x0;
			CanKeyValue[7]=0x0;
            Tx1ConfirmCnt=1;

            CanTx1();

			if(Tx1ConfirmCnt==0){
				BlinkTime = 0;
				LATB5=!LATB5;
			}	
		}		
	}

	return(1);
}


#endif
