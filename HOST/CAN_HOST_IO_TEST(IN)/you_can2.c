

#include <p30f6010.h>            
#include "you_can_lib.h" 
#include "you_can2.h" 

           
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"



UserDataType   C2Time=0;
//UserDataType   C2ReceiveTime=0;
UserDataType   C2DataSeq=0;
unsigned int   C2Company=0;
unsigned int   C2ReceiveGroupNumber=0;
unsigned int   C2ReceiveMaterAdr=0;
unsigned int   C2ReceiveSlaveAdr=0;
unsigned int   C2ReceiveAdrStatus=0;
unsigned int   C2Loop=0;


#define  H2_INTV_TIME1  100   //msec
#define  H2_INTV_TIME2  105   //msec
#define  H2_INTV_TIME3  110   //msec
#define  H2_INTV_TIME4  115   //msec
#define  H2_INTV_TIME5  120  //msec


void CAN2SendMessageyou(char MsgFlag,unsigned int * data, unsigned int  datalen) 
{
    int i;

    for(i = 0;i < datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0: 
            *((unsigned char *)&C2TX0B1+i)= data[i];
            break;
        case 1: *((unsigned char *)&C2TX1B1+i)= data[i];
            break;
        case 2: *((unsigned char *)&C2TX2B1+i)= data[i];
            break;
        default:*((unsigned char *)&C2TX0B1+i)= data[i];
            break;
        }
    }

    
    
    switch(MsgFlag)
    {
    case 0:
        C2TX0DLCbits.DLC = datalen;
        C2TX0CON=7;         
        C2TX0CONbits.TXREQ = 1;
        break;
    case 1:
        C2TX1DLCbits.DLC = datalen;
        C2TX1CON=7; 
        C2TX1CONbits.TXREQ = 1;
        break;
    case 2:
        C2TX2DLCbits.DLC = datalen;
        C2TX2CON=7; 
        C2TX2CONbits.TXREQ = 1;
        break;
    default:
        C2TX0DLCbits.DLC = datalen;
        C2TX0CON=7; 
        C2TX0CONbits.TXREQ = 1;
        break;
    }
}






void  Can2Init(void)
{
    unsigned int sid;

    C2CTRLbits.REQOP    = 0x4;      // Entry Configration Mode
//    C2CTRLbits.CANCAP   = 0x1;      // enable CAN Capture mode
    C2CTRLbits.CANCAP   = 0x0;      // disable CAN Capture mode
    C2CTRLbits.CSIDL    = 0x1;      // when idle mode,stop can
    C2CTRLbits.ABAT     = 0x1;      // aboart all pending transmit
    C2CTRLbits.CANCKS   = 0x1;      // fcan=fcy

    C2CFG2bits.SAM      = 0x1 ;     // Bus Line is sampled three times prior to the sample point
    C2CFG2bits.WAKFIL   = 0x0 ; 	// CAN bus line filter is not used for wake-up
    C2CFG2bits.SEG2PHTS = 0x1 ;     // Freely programmable;

//    C1CFG1bits.BRP      = 0x9;      // tq=0.00000125
    C2CFG1bits.BRP      = 19;      // tq=0.0000025
  
    C2CFG1bits.SJW      = 0x0;      // Synchronized Jump Width bits 1xTq
    C2CFG2bits.SEG1PH   = 0x1 ;     // 2 Tq
    C2CFG2bits.PRSEG    = 0x2 ;     // 3 Tq
    C2CFG2bits.SEG2PH   = 0x1 ; 	// 2 Tq

    C2TX0CON            = 0x3;
    C2TX1CON            = 0x3;

    C2TX0SIDbits.TXIDE  = 0x1;
    C2TX0SIDbits.SRR    = 0x0;
    C2TX0DLCbits.TXRB0  = 0x0;
    C2TX0DLCbits.TXRB1  = 0x0;
    C2TX0DLCbits.TXRTR  = 0x0;

    C2TX1SIDbits.TXIDE  = 0x1;
    C2TX1SIDbits.SRR    = 0x0;
    C2TX1DLCbits.TXRB0  = 0x0;
    C2TX1DLCbits.TXRB1  = 0x0;
    C2TX1DLCbits.TXRTR  = 0x0;

    C2TX2SIDbits.TXIDE  = 0x1;
    C2TX2SIDbits.SRR    = 0x1;
    C2TX2DLCbits.TXRB0  = 0x0;
    C2TX2DLCbits.TXRB1  = 0x0;
    C2TX2DLCbits.TXRTR  = 0x0;


    C2RXM0SID           = 0x0;
    C2RXM0EIDH          = 0x0;
    C2RXM0EIDL          = 0x0;
    C2RXM0SIDbits.MIDE  = 0x0;

    C2RXM1SID           = 0x0;
    C2RXM1EIDH          = 0x0;
    C2RXM1EIDL          = 0x0;
    C2RXM1SIDbits.MIDE  = 0x0;

    C2RXF0SID           = 0x0;
    C2RXF0EIDH          = 0x0;
    C2RXF0EIDL          = 0x0;
    C2RXF0SIDbits.EXIDE = 0x0;

    C2RXF1SID           = 0x0;
    C2RXF1EIDH          = 0x0;
    C2RXF1EIDL          = 0x0;
    C2RXF1SIDbits.EXIDE = 0x0;

    C2RXF2SID           = 0x0;
    C2RXF2EIDH          = 0x0;
    C2RXF2EIDL          = 0x0;
    C2RXF2SIDbits.EXIDE = 0x0;

    C2RXF3SID           = 0x0;
    C2RXF3EIDH          = 0x0;
    C2RXF3EIDL          = 0x0;
    C2RXF3SIDbits.EXIDE = 0x0;

    C2RXF4SID           = 0x0;
    C2RXF4EIDH          = 0x0;
    C2RXF4EIDL          = 0x0;
    C2RXF4SIDbits.EXIDE = 0x0;

    C2RXF5SID           = 0x0;
    C2RXF5EIDH          = 0x0;
    C2RXF5EIDL          = 0x0;
    C2RXF5SIDbits.EXIDE = 0x0;

    C2RX0CONbits.RXFUL  = 0x0;
//    C1RX0CONbits.DBEN   = 0x1;
    C2RX0CONbits.DBEN   = 0x0;
    C2RX0CONbits.JTOFF  = 0x0;
    C2RX0CONbits.FILHIT0= 0x0;

    C2RX1CONbits.RXFUL  = 0x0;


    C2INTE              = 0x0;
    C2INTEbits.ERRIE    = 0x1;
    C2INTEbits.RX0IE    = 0x1;
    C2INTEbits.RX1IE    = 0x1;
//    C1INTEbits.TX0IE    = 0x1;
//    C1INTEbits.TX1IE    = 0x1;
//    C1INTEbits.TX2IE    = 0x1;

    C2IE       = 0x1;

    sid=(unsigned int)COMPANY;
//    sid=(unsigned int)(sid | (MyGroupAddr << 7));

    
    youCAN2SetFilter(0,sid,0xffff,0xffff);
    youCAN2SetFilter(1,sid,0xffff,0xffff);
    youCAN2SetFilter(2,sid,0xffff,0xffff);
    youCAN2SetFilter(3,sid,0xffff,0xffff);
    youCAN2SetFilter(4,sid,0xffff,0xffff);
    youCAN2SetFilter(5,sid,0xffff,0xffff);
 
    youCAN2SetMask(5,0xffff,0xffff,0xffff);
    youCAN2SetMask(4,0xffff,0xffff,0xffff);
    youCAN2SetMask(3,0xffff,0xffff,0xffff);
    youCAN2SetMask(1,0xffff,0xffff,0xffff);
    youCAN2SetMask(0,sid,0x0,0x0);


    IPC9bits.C2IP=4;
    

    C2CTRLbits.REQOP    = 0x0;
                
    C2DataSeq=0;                
    C2Time=0;
    C2EC=0;
}







void  Can2Check(void)
{

    LocalType sel;
    unsigned int tmpeidH,tmpeidL;
    unsigned int tmpsidH,tmpsidL;

    sel=0;

    tmpeidH=C2EC;
    tmpeidL=C2EC & 0x00ff;

    if(tmpeidH >= 0x8100){
        Can2Init();
    }
    else if(tmpeidL >= 0x81){
        Can2Init();
    } 


/*
    if(C2ReceiveTime>200){
//        Can2Init();
        C2ReceiveTime=0;
    }
*/

    tmpsidH=(unsigned int)COMPANY;
    tmpsidL=(unsigned int)(MyGroupAddr);
    tmpsidL=(unsigned int)(tmpsidL << 7);
    tmpsidL=tmpsidL | tmpsidH;

    tmpeidH=(unsigned int)(MyNc_Addr << 1);
    tmpeidL=(unsigned int)((MyLocalAddr >> 2) & 0x0001);
    tmpeidH=(unsigned int)(tmpeidL | tmpeidH);

    tmpeidL=(unsigned int)(MyLocalAddr << 14);
    tmpeidL=(unsigned int)(tmpeidL | 0x2000);



    if(!C2TX0CONbits.TXREQ){
        if((C2Time > H2_INTV_TIME5) && (C2DataSeq==4)){
            youCAN2TxSidSet(sel,tmpsidL);
            youCAN2TxEidSet(sel,tmpeidH,tmpeidL+8);
            LoadCanBuffer(C2DataSeq);
            CAN2SendMessageyou(sel,&CAN_Buf[0], 8);        
            C2Time=0;
            C2DataSeq=0;       
        }
        else  if((C2Time > H2_INTV_TIME4) && (C2DataSeq==3)){
            youCAN2TxSidSet(sel,tmpsidL);
            youCAN2TxEidSet(sel,tmpeidH,tmpeidL+3);
            LoadCanBuffer(C2DataSeq);
            CAN2SendMessageyou(sel,&CAN_Buf[0], 8);        
            C2DataSeq=4;       
        }
        else if((C2Time > H2_INTV_TIME3) && (C2DataSeq==2)){
            youCAN2TxSidSet(sel,tmpsidL);
            youCAN2TxEidSet(sel,tmpeidH,tmpeidL+2);
            LoadCanBuffer(C2DataSeq);
            CAN2SendMessageyou(sel,&CAN_Buf[0], 8);        
            C2DataSeq=3;       
        }
        else if((C2Time > H2_INTV_TIME2) && (C2DataSeq==1)){
            youCAN2TxSidSet(sel,tmpsidL);
            youCAN2TxEidSet(sel,tmpeidH,tmpeidL+1);
            LoadCanBuffer(C2DataSeq);
            CAN2SendMessageyou(sel,&CAN_Buf[0], 8);        
            C2DataSeq=2;       
        }
        else if((C2Time > H2_INTV_TIME1) && (C2DataSeq==0)){
            youCAN2TxSidSet(sel,tmpsidL);
            youCAN2TxEidSet(sel,tmpeidH,tmpeidL+0);         
            LoadCanBuffer(C2DataSeq);
            CAN2SendMessageyou(sel,&CAN_Buf[0], 8);        
            C2DataSeq=1;
            C2Time = H2_INTV_TIME1;       
        }
        else if((C2Time > H2_INTV_TIME5) && (C2DataSeq>4)){
            C2Time=0;
            C2DataSeq=0;       
        }
    }
}




void    Can2ReceiveSIDEIDArrary(void)
{

    unsigned int  tmpid1,tmpid2;

    C2ReceiveGroupNumber=(C2RX0SID >> 9) & 0x000f;
    C2ReceiveMaterAdr=(C2RX0EID >> 8) & 0x0007;

    if(C2RX0EID & 0x80){
        C2ReceiveAdrStatus=MASTER_TX_SLAVE;
    }
    else{
        C2ReceiveAdrStatus=SLAVE_TX_MASTER;
        tmpid1=(C2RX0DLC >> 10) & 0x0007;
        tmpid2=(C2RX0EID << 6)  & 0x00c0;
        C2ReceiveSlaveAdr=(tmpid1 | tmpid2);
    }

}



/*
void _ISR _C2Interrupt(void)
{

    if(C2INTFbits.RX0IF){
        
//        C2ReceiveTime=0;
        Can2ReceiveSIDEIDArrary();

//        C2Time=0;
        C2DataSeq=0;       

        if(C2ReceiveAdrStatus == MASTER_TX_SLAVE){

            if(C2ReceiveGroupNumber==3){
//                if(MyLocalAddr==4)           C2Time=40;
//                else if(MyLocalAddr==5)      C2Time=35;
//                else if(MyLocalAddr==6)      C2Time=30;
//                else if(MyLocalAddr==7)      C2Time=25;

                if(MyGroupAddr==0)              C2Time=30;
                else if(MyGroupAddr==1)         C2Time=20;
                else if(MyGroupAddr==2)         C2Time=10;
                else                            C2Time=0;
            }
            else if(C2ReceiveGroupNumber==2){
                if(MyGroupAddr==3)           C2Time=30;
//                else if(MyLocalAddr==4)      C2Time=35;
//                else if(MyLocalAddr==5)      C2Time=30;
//                else if(MyLocalAddr==6)      C2Time=25;
//                else if(MyLocalAddr==7)      C2Time=20;
                else if(MyGroupAddr==0)      C2Time=20;
                else if(MyGroupAddr==1)      C2Time=10;
                else                         C2Time=0;
            }
            else if(C2ReceiveGroupNumber==1){
                if(MyGroupAddr==2)           C2Time=30;
                else if(MyGroupAddr==3)      C2Time=20;
//                else if(MyLocalAddr==4)      C2Time=30;
//                else if(MyLocalAddr==5)      C2Time=25;
//                else if(MyLocalAddr==6)      C2Time=20;
//                else if(MyLocalAddr==7)      C2Time=15;
                else if(MyGroupAddr==0)      C2Time=10;
                else                         C2Time=0;
            }
            else if(C2ReceiveGroupNumber==0){
//                if(MyGroupAddr==1)           C2Time=30;
//                else if(MyGroupAddr==2)      C2Time=20;
//                else if(MyGroupAddr==3)      C2Time=10;
                if(MyLocalAddr==1)      C2Time=30;
                else if(MyLocalAddr==2)      C2Time=25;
                else if(MyLocalAddr==3)      C2Time=20;
//                else if(MyLocalAddr==7)      C2Time=10;
                else                         C2Time=0;
            }

        }
        C2INTFbits.RX0IF=0;
        C2RX0CONbits.RXFUL=0;
        C2Loop=0;
    }    


    else{
        C2CTRLbits.ABAT=1;      // aboart all pending transmit
        C2INTFbits.RX1IF=0;
        C2RX1CONbits.RXFUL=0;
        C2INTFbits.WAKIF=0;
        C2INTF=0;
        C2INTFbits.ERRIF=0;        
        if(C2Loop < 65530)    C2Loop++;
    }

    C2IF=0;
}
*/



void _ISR _C2Interrupt(void)
{

    if(C2INTFbits.RX0IF){
//        if(TestCan2 < 100)  TestCan2++;
        
//        C2ReceiveTime=0;
        Can2ReceiveSIDEIDArrary();

        C2Time=0;
        C2DataSeq=0;       

        if(C2ReceiveAdrStatus == MASTER_TX_SLAVE){
            if(C2ReceiveMaterAdr==3){
//                if(MyLocalAddr==4)           C2Time=40;
//                else if(MyLocalAddr==5)      C2Time=35;
//                else if(MyLocalAddr==6)      C2Time=30;
//                else if(MyLocalAddr==7)      C2Time=25;

                if(MyLocalAddr==0)              C2Time=30;
                else if(MyLocalAddr==1)         C2Time=20;
                else if(MyLocalAddr==2)         C2Time=10;
                else                            C2Time=0;
            }
            else if(C2ReceiveMaterAdr==2){
                if(MyLocalAddr==3)           C2Time=30;
//                else if(MyLocalAddr==4)      C2Time=35;
//                else if(MyLocalAddr==5)      C2Time=30;
//                else if(MyLocalAddr==6)      C2Time=25;
//                else if(MyLocalAddr==7)      C2Time=20;
                else if(MyLocalAddr==0)      C2Time=20;
                else if(MyLocalAddr==1)      C2Time=10;
                else                         C2Time=0;
            }
            else if(C2ReceiveMaterAdr==1){
                if(MyLocalAddr==2)           C2Time=30;
                else if(MyLocalAddr==3)      C2Time=20;
//                else if(MyLocalAddr==4)      C2Time=30;
//                else if(MyLocalAddr==5)      C2Time=25;
//                else if(MyLocalAddr==6)      C2Time=20;
//                else if(MyLocalAddr==7)      C2Time=15;
                else if(MyLocalAddr==0)      C2Time=10;
                else                         C2Time=0;
            }
            else if(C2ReceiveMaterAdr==0){
//                if(MyGroupAddr==1)           C2Time=30;
//                else if(MyGroupAddr==2)      C2Time=20;
//                else if(MyGroupAddr==3)      C2Time=10;
                if(MyLocalAddr==1)          C2Time=30;
                else if(MyLocalAddr==2)      C2Time=25;
                else if(MyLocalAddr==3)      C2Time=20;
                else                         C2Time=0;
            }

        }
        C2INTFbits.RX0IF=0;
        C2RX0CONbits.RXFUL=0;
        C2Loop=0;

        if(TestCan2 < 200)  TestCan2++;
        C2Time=90;
    }    


    else{
        TestCan2=0;
        C2CTRLbits.ABAT=1;      // aboart all pending transmit
        C2INTFbits.RX1IF=0;
        C2RX1CONbits.RXFUL=0;
        C2INTFbits.WAKIF=0;
        C2INTF=0;
        C2INTFbits.ERRIF=0;        
        if(C2Loop < 65530)    C2Loop++;
    }

    C2IF=0;
}


