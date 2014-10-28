


#include  <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "com.h"


void  Comport2Tx_interrupt(void);
void  Comport2Rx_interrupt(void);


#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)



UserDataType    RxBuffer2[MAX_RTX_BUF]={0,0};
UserDataType    RcvBuf2[MAX_SAVE_BUF]={0};
UserDataType    RxStatus2=0;
UserDataType    RxCurCnt2=0;
UserDataType    SerialTime2=0x0;
UserDataType    Chksum2=0;


void    Chksum_Sum2(void)
{
    
    LocalType    i;
    LocalType    temp;
    
    Chksum2=0;
    for(i=0;RxBuffer2[i];i++){
    Chksum2=Chksum2+RxBuffer2[i];
    }
    temp=(Chksum2 & 0xf0) >> 4;
    if(temp < 0x0a) temp=temp+'0';
    else            temp=temp+'7';
    RxBuffer2[i]=temp;
    
    temp=(Chksum2 & 0x0f);
    if(temp<0x0a)   temp=temp+'0';        
    else            temp=temp+'7';
    RxBuffer2[i+1]=temp;
    RxBuffer2[i+2]=0;
}



void    Serial2(void)
{

   	Chksum_Sum2();   	
   	RxCurCnt2=0;
   	RxStatus2=TX_SET;   
    U2TXREG=RxBuffer2[RxCurCnt2];
   	RxCurCnt2=1;   
}





void _ISR _U2TXInterrupt(void)
{
//    unsigned int  i;
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

    _U2TXIF=0;
    
    if(RxBuffer2[RxCurCnt2] == 0){
//      i=0;
//      while(!_U2TRMT && (i<2000)){
//        i++;
//      }  
//      TXEN=1;
      SerialTime2=0;
      RxStatus2 = STX_CHK;
    }
    else{
      U2TXREG=RxBuffer2[RxCurCnt2];
      RxCurCnt2++;
      SerialTime2=0;
      RxStatus2 = TX_SET;
    
      if(RxCurCnt2 >= MAX_RTX_BUF){
        RxCurCnt2=0;
        RxBuffer2[RxCurCnt2]=0;
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




void _ISR _U2RXInterrupt(void)
{
   	LocalType   buf1=0;
   	LocalType   temp=0;


    _U2RXIF=0;
    
   	if(_U2RXDA)    buf1=U2RXREG;
   	if(_U2RXDA)    buf1=U2RXREG;
   	if(_U2RXDA)    buf1=U2RXREG;
   	if(_U2RXDA)    buf1=U2RXREG;

    SerialTime2=0;

    if(_U2OERR){
        _U2OERR=0;
    }

    if(_U2FERR){
        _U2FERR=0;
    }

    if(_U2PERR){
        _U2PERR=0;
    }

	
    if(RxStatus2 != TX_SET){   
        SerialTime2=0;
        if(RxCurCnt2 < (MAX_RTX_BUF-1)){
            RxCurCnt2++;
        }
        else{
            RxCurCnt2=0;
        }

        RxBuffer2[RxCurCnt2]=buf1;

        switch(RxStatus2){
            case    STX_CHK:
                if((buf1==ACK) || (buf1==ENQ)){
                    RxStatus2=ETX_CHK;
                    RxBuffer2[0]=buf1;
                    RxCurCnt2=0;
                    Chksum2=buf1;
                }
                break;
            case    ETX_CHK:
                Chksum2=Chksum2+buf1;
                if((buf1==ETX) || (buf1 == EOT)){
                    RxBuffer2[RxCurCnt2]=0x0;
                    RxStatus2=BCC1_CHK;                  
                }
//                else if(buf1 < '0')   RxStatus2=STX_CHK;
                break;
            case    BCC1_CHK:               
                buf1=ASCTOHEX(buf1);
                RxBuffer2[RxCurCnt2]=0x0;
                temp=(Chksum2 & 0xf0) >> 4; 
           
                if(temp==buf1){                 
                    RxStatus2=BCC2_CHK;                                                                    
                }
                else    RxStatus2=STX_CHK;                  
                break;
            case    BCC2_CHK :
                buf1=ASCTOHEX(buf1);
                temp=(Chksum2 & 0x0f);
                RxBuffer2[RxCurCnt2]=0x0;
                RxBuffer2[MAX_RTX_BUF-1]=0x0;
                if(temp==buf1){
                    for(temp=0;((RxBuffer2[temp] > 0) && (temp < MAX_SAVE_BUF));temp++){                   
                        RcvBuf2[temp]=RxBuffer2[temp];
/*
                        RxBuffer2[temp]=ASCTOHEX(RxBuffer2[temp]);
                        RxBuffer2[temp]=L_SHIFT(RxBuffer2[temp]);
                        temp++;
                        RxBuffer2[temp]=ASCTOHEX(RxBuffer2[temp]);
                        RcvBuf2[buf1]=(RxBuffer2[temp-1] | RxBuffer2[temp]);
                        buf1++;
                        if(buf1 > MAX_SAVE_BUF){
                            RxStatus2=STX_CHK;
                            RxCurCnt2=0;
                            break;
                        }                     
*/
                    }
                    RxStatus2=RX_GOOD;
                }

/*               
                if((temp==buf1) && (RxCurCnt2 <= (MAX_RTX_BUF-1))){
                    buf1=0;                                                                             
                    for(temp=1;(RxBuffer2[temp] >= '0');temp++){                   
                        RxBuffer2[temp]=ASCTOHEX(RxBuffer2[temp]);
                        RxBuffer2[temp]=L_SHIFT(RxBuffer2[temp]);
                        temp++;
                        RxBuffer2[temp]=ASCTOHEX(RxBuffer2[temp]);
                        RcvBuf2[buf1]=(RxBuffer2[temp-1] | RxBuffer2[temp]);
                        buf1++;
                        if(buf1 > MAX_SAVE_BUF){
                            RxStatus2=STX_CHK;
                            RxCurCnt2=0;
                            break;
                        }                     
                    }
                    RxStatus2=RX_GOOD;
                }
*/
                else    RxStatus2=STX_CHK;                  
                break;              
            case    RX_ERROR:
                RxStatus2=STX_CHK;
                RxCurCnt2=0;
                break;
            default:
                RxStatus2=STX_CHK;
                RxCurCnt2=0;
                break;
        }
    }

}


