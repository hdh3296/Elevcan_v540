
#include <p30f6010.h>      
      
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"






void  QEI_Init(void)
{

    ADPCFG=0xFFFF;

    UPDN_SRC=0;    //QEB
    TQCS    =0;    //internal
    POSRES  =0;    //index  no reset
    TQGATE  =0;
    PCDOUT  =0;
    SWPAB   =0;    
    QEISIDL =0;
    CNTERR  =0;

    QEICONbits.TQCKPS =0;
    QEICONbits.QEIM   =7;

    CEID  =1;                //disable 
    INDOUT=1;                //filter on
    QEOUT =1;
    DFLTCONbits.INDCK=7;
    DFLTCONbits.QECK =3;
//    DFLTCONbits.QECK =7;

//    DFLTCON=0x188;

    POSCNT = 0;
    MAXCNT = DOUBL_CNT ;

    QEIIF  = 0;
    QEIIE  = 1;
} 



void _ISR _QEIInterrupt(void)
{ 
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

    if(QEIIF){ 
      QEIIF=0;
      if(UPDN)    CurPulse++;
      else{
        if(CurPulse > 0)    CurPulse--;
      }
      CounterTime=0;

      TestCnt++;  
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

