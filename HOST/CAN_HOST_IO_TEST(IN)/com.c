


#include  <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "com.h"
#include  "iomap.h"



void  Comport1Tx_interrupt(void);
void  Comport1Rx_interrupt(void);


#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)



UserDataType    RxBuffer[MAX_RTX_BUF]={0,0};
UserDataType    RcvBuf[MAX_SAVE_BUF]={0};
UserDataType    RxStatus=0;
UserDataType    RxCurCnt=0;
UserDataType    SerialTime=0x0;
UserDataType    Chksum=0;





void    Chksum_Sum(void)
{
        LocalType    i;
        LocalType    temp;

        Chksum=0;
        for(i=0;RxBuffer[i];i++){
                Chksum=Chksum+RxBuffer[i];
        }
        temp=(Chksum & 0xf0) >> 4;
        if(temp < 0x0a) temp=temp+'0';
        else            temp=temp+'7';
        RxBuffer[i]=temp;

        temp=(Chksum & 0x0f);
        if(temp<0x0a)   temp=temp+'0';        
        else            temp=temp+'7';
        RxBuffer[i+1]=temp;
        RxBuffer[i+2]=0;
}



void    Serial(void)
{

   	Chksum_Sum();
   	
   	RxCurCnt=0;
   	RxStatus=TX_SET;
    U1TXREG=RxBuffer[RxCurCnt];
   	RxCurCnt=1;   
}





void _ISR _U1TXInterrupt(void)
{
    unsigned int  i;
/*
    asm("push w0");
    asm("push w1");
    asm("push w2");
    asm("push w3");
    asm("push w4");
    asm("push w5");

    asm("push w6");
    asm("push w7");
    asm("push w8");
    asm("push w9");
    asm("push w10");
*/

    _U1TXIF=0;
    
    if(RxBuffer[RxCurCnt] == 0){
      i=0;
      while(!_U1TRMT && (i<2000)){
        i++;
      }  
      TXEN=1;
      SerialTime=0;
      RxStatus = STX_CHK;
    }
    else{
      U1TXREG=RxBuffer[RxCurCnt];
      RxCurCnt++;
      SerialTime=0;
      RxStatus = TX_SET;
    
      if(RxCurCnt >= MAX_RTX_BUF){
        RxCurCnt=0;
        RxBuffer[RxCurCnt]=0;
      }
    }

/*
    asm("pop w10");
    asm("pop w9");
    asm("pop w8");
    asm("pop w7");
    asm("pop w6");

    asm("pop w5");
    asm("pop w4");
    asm("pop w3");
    asm("pop w2");
    asm("pop w1");
    asm("pop w0");
*/
}




void _ISR _U1RXInterrupt(void)
{
   	LocalType   buf1=0;
   	LocalType   temp=0;
/*
    asm("push w0");
    asm("push w1");
    asm("push w2");
    asm("push w3");
    asm("push w4");
    asm("push w5");

    asm("push w6");
    asm("push w7");
    asm("push w8");
    asm("push w9");
    asm("push w10");
*/

    _U1RXIF=0;
    
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;

    SerialTime=0;

    if(_U1OERR){
        _U1OERR=0;
    }

    if(_U1FERR){
        _U1FERR=0;
    }

    if(_U1PERR){
        _U1PERR=0;
    }

	
    if(RxStatus != TX_SET){   
        SerialTime=0;
        if(RxCurCnt < (MAX_RTX_BUF-1)){
            RxCurCnt++;
        }
        else{
            RxCurCnt=0;
        }

        RxBuffer[RxCurCnt]=buf1;

        switch(RxStatus){
            case    STX_CHK:
                if((buf1==ACK) || (buf1==ENQ)){
                    RxStatus=ETX_CHK;
                    RxBuffer[0]=buf1;
                    RxCurCnt=0;
                    Chksum=buf1;
                }
                break;
            case    ETX_CHK:
                Chksum=Chksum+buf1;
                if((buf1==ETX) || (buf1 == EOT)){
                    RxBuffer[RxCurCnt]=0x0;
                    RxStatus=BCC1_CHK;                  
                }
                else if(buf1 < '0')   RxStatus=STX_CHK;
                break;
            case    BCC1_CHK:               
                buf1=ASCTOHEX(buf1);
                RxBuffer[RxCurCnt]=0x0;
                temp=(Chksum & 0xf0) >> 4; 
           
                if(temp==buf1){                 
                    RxStatus=BCC2_CHK;                                                                    
                }
                else    RxStatus=STX_CHK;                  
                break;
            case    BCC2_CHK :
                buf1=ASCTOHEX(buf1);
                temp=(Chksum & 0x0f);
                RxBuffer[RxCurCnt]=0x0;
                RxBuffer[MAX_RTX_BUF-1]=0x0;
               
                if((temp==buf1) && (RxCurCnt <= (MAX_RTX_BUF-1))){
                    buf1=0;                                                                             
                    for(temp=1;(RxBuffer[temp] >= '0');temp++){                   
                        RxBuffer[temp]=ASCTOHEX(RxBuffer[temp]);
                        RxBuffer[temp]=L_SHIFT(RxBuffer[temp]);
                        temp++;
                        RxBuffer[temp]=ASCTOHEX(RxBuffer[temp]);
                        RcvBuf[buf1]=(RxBuffer[temp-1] | RxBuffer[temp]);
                        buf1++;
                        if(buf1 > MAX_SAVE_BUF){
                            RxStatus=STX_CHK;
                            RxCurCnt=0;
                            break;
                        }                     
                    }
                    RxStatus=RX_GOOD;
                }
                else    RxStatus=STX_CHK;                  
                break;              
            case    RX_ERROR:
                RxStatus=STX_CHK;
                RxCurCnt=0;
                break;
            default:
                RxStatus=STX_CHK;
                RxCurCnt=0;
                break;
        }
    }

/*
    asm("pop w10");
    asm("pop w9");
    asm("pop w8");
    asm("pop w7");
    asm("pop w6");

    asm("pop w5");
    asm("pop w4");
    asm("pop w3");
    asm("pop w2");
    asm("pop w1");
    asm("pop w0");
*/   	
}


