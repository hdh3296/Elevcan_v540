




#include    <pic18.h>

#include        "you_can.h"
#include        "com.h"
#include        "crt_45k80.h"


unsigned    char  	MainTimer=0;
unsigned    char	msec100=0;


extern  void  Timer0Init(void);
extern  void  Initial(void);



void    PortInit(void)
{
	TRISA=0;
	TRISB=0;
	TRISC=0;
	TRISD=0;
	TRISE=0;

  	LATA=0xff;	
  	LATB=0xff;	
  	LATC=0xff;	
  	LATD=0xff;	
  	LATE=0xff;	
}


void    UserBaudRate(void)
{
	unsigned char val;
	val=0;

	TRISE0=1;
	TRISE1=1;
	TRISE2=1;
	if(!RE0)	val= (val | 0x01);		
	if(!RE1)	val= (val | 0x02);		
	if(!RE2)	val= (val | 0x04);
	switch(val){
		case	0:	
			Com1BaudRate=9600;
			break;
		case	1:	
			Com1BaudRate=19200;
			break;
		case	2:	
			Com1BaudRate=38400;
			break;
		case	3:	
			Com1BaudRate=57600;
			break;
		default:
			Com1BaudRate=57600;
			break;		
	}			
}


void  Serial2Check(void)
{
	unsigned char i;

    if(Com1RxStatus==RX_GOOD){      
		for(i=0;i<(Com1RxBuffer[3]+4);i++)	Can1TxBuf[i]=Com1RxBuffer[i];
		Can1TxDataTxPointer=2;	
		Can1TxDataTotalCnt= (Com1RxBuffer[3]+4);
        Com1RxStatus=STX_CHK; 
		RXLED = !RXLED;
    }             

    Can1Check();               
}



void main(void)
{
    
    di();
    Initial();
    PortInit();
    Timer0Init(); 

	UserBaudRate();
    init_comms();
	Can1RxSid=0;
	Can1RxEid=0;

    Can1Init();

    ei();


	MainTimer=0;
	msec100=0;
	Com1SerialTime=0;		

	TXIE=0;
	RCIE=1;

	TRISD5=0;
	TX_EN=0;

	Com1RxStatus=STX_CHK; 

    while(1){    
        CLRWDT();
        Serial2Check();

		if(Com1RxStatus == TX_SET){
			if(Com1SerialTime > 3){
				Com1SerialTime=0;
				Com1RxStatus=STX_CHK; 
				Com1TxThisPt=0;
				Com1TxCnt=0;
				TXIE=0;
				TX_EN=0;
			}
		}
    }
}



void interrupt isr(void)
{
   
    if( TMR0IF )
    {    
        TMR0IF = 0 ;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;    

        Com1SerialTime++;
        msec100++;

        if(msec100>100){
            msec100=0;
			MainTimer++;
			if(MainTimer > 5){
				RUNLED=!RUNLED;
			}				
        }  
    }

#if defined(CPU65K80)  || defined(CPU45K80)
    if(PIR5>0){
        Can1Interrupt();
    }
#else
    if(PIR3>0){
        Can1Interrupt();
    }
#endif


	if((RCIE)&&(RCIF))										/*receive interrupt routine*/
	{
        RCIF=0;
        USART0_RXC();
	}	

	if((TXIE)&&(TXIF))										/*transmit interrupt routine*/
	{
        TXIF=0;
        USART0_TXC();
	}	


	if(OERR) {
      	TXEN=0;
      	TXEN=1;
      	SPEN=0;
      	SPEN=1;
		CREN1=0;
    }

	if( !CREN1)	CREN1=1;
	
}




