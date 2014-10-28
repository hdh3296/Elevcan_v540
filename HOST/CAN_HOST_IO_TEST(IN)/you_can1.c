

#include <p30f6010.h>      
      
#include "you_can_lib.h" 
#include "you_can1.h" 
//#include  "30f6010_io.h"            
//#include  "host_io.h"            
#include  "iodef.h"
#include  "..\..\system_com\memory_map.h"

//#include  "door.h"
//#include  "eeprom.h" 
//#include  "com.h"
//#include  "counter.h"



#define  H_INTV_TIME1  50   //msec
#define  H_INTV_TIME2  55   //msec
#define  H_INTV_TIME3  60   //msec
#define  H_INTV_TIME4  65   //msec
#define  H_INTV_TIME5  70   //msec



UserDataType   C1Time=0;
//UserDataType   C1ReceiveTime=0;
UserDataType   C1DataSeq=0;

unsigned int   C1Company=0;
unsigned int   C1ReceiveGroupNumber=0;
unsigned int   C1ReceiveMaterAdr=0;
unsigned int   C1ReceiveSlaveAdr=0;
unsigned int   C1ReceiveAdrStatus=0;
unsigned int   C1Loop=0;



void CAN1SendMessageyou(char MsgFlag,unsigned int * data, unsigned int  datalen) 
{
    int i;

    for(i = 0;i < datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0: 
            *((unsigned char *)&C1TX0B1+i)= data[i];
            break;
        case 1: *((unsigned char *)&C1TX1B1+i)= data[i];
            break;
        case 2: *((unsigned char *)&C1TX2B1+i)= data[i];
            break;
        default:*((unsigned char *)&C1TX0B1+i)= data[i];
            break;
        }
    }


    
    switch(MsgFlag)
    {
    case 0:
        C1TX0DLCbits.DLC = datalen;
        C1TX0CON=7;         
        C1TX0CONbits.TXREQ = 1;
        break;
    case 1:
        C1TX1DLCbits.DLC = datalen;
        C1TX1CON=7; 
        C1TX1CONbits.TXREQ = 1;
        break;
    case 2:
        C1TX2DLCbits.DLC = datalen;
        C1TX2CON=7; 
        C1TX2CONbits.TXREQ = 1;
        break;
    default:
        C1TX0DLCbits.DLC = datalen;
        C1TX0CON=7; 
        C1TX0CONbits.TXREQ = 1;
        break;
    }
}


/*
unsigned int WhichCAN1IsTXReady(void)
{
    if(!C1TX0CONbits.TXREQ)         return(0);  
    else if(!C1TX0CONbits.TXREQ)    return(1);  
    else if(!C1TX0CONbits.TXREQ)    return(2);  
    else                            return(0xff);
}

*/




void    Can1Check(void)
{
    LocalType sel;

    unsigned int tmpeidH,tmpeidL;
    unsigned int tmpsidH,tmpsidL;

    sel=0;

    tmpeidH=C1EC;
    tmpeidL=C1EC & 0x00ff;
//        sRamDArry[mTestData]     =(tmpeidH >> 8);

    if(tmpeidH >= 0x8100){
        Can1Init();
    }
    else if(tmpeidL >= 0x81){
        Can1Init();
    } 

/*
    if(C1ReceiveTime>200){    
//        Can1Init();
        C1ReceiveTime=0;
    }
*/    
    tmpsidH=(unsigned int)COMPANY;   //company name
    tmpsidL=(unsigned int)(MyGroupAddr);
    tmpsidL=(unsigned int)(tmpsidL << 7);
    tmpsidL=tmpsidL | tmpsidH;

    tmpeidH=(unsigned int)(MyNc_Addr << 1);
    tmpeidL=(unsigned int)((MyLocalAddr >> 2) & 0x0001);
    tmpeidH=(unsigned int)(tmpeidL | tmpeidH);

    tmpeidL=(unsigned int)(MyLocalAddr << 14);
    tmpeidL=(unsigned int)(tmpeidL | 0x2000);


    if(!C1TX0CONbits.TXREQ){

        if((C1Time > H_INTV_TIME5) && (C1DataSeq==4)){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+8);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1Time=0;
            C1DataSeq=0;       
        }
        else  if((C1Time > H_INTV_TIME4) && (C1DataSeq==3)){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+3);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8); 
            C1DataSeq=4;       
        }
        else if((C1Time > H_INTV_TIME3) && (C1DataSeq==2)){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+2);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1DataSeq=3;       
        }
        else if((C1Time > H_INTV_TIME2) && (C1DataSeq==1)){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+1);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1DataSeq=2;       
        }
        else if((C1Time > H_INTV_TIME1) && (C1DataSeq==0)){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+0);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1DataSeq=1;
            C1Time = H_INTV_TIME1;       
        }
        else if((C1Time > H_INTV_TIME5) && (C1DataSeq>4)){
            C1Time=0;
            C1DataSeq=0;       
        }
    }
}


/*

#define     KEY_DOOR    0
#define     KEY_CLEAR   1
#define     KEY_READY   2
#define     KEY_SET     3
#define     INVALID_CMD 0xff
*/


unsigned int  CanCommandCheck(void)
{
    UserDataType i,cmd,ret;

    ret=0;

    cmd=(UserDataType)(C1RX0B1 & 0x00ff);

    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);

    if(cmd != CAN_KEY_DOOR){
        if(i & UPDN_CAR_READY){
            i=(i & ONLY_FLR);
            i=i-sRamDArry[mStartFloor];

            if(i>cF_TOPFLR){   //sRamDArry[mTopFloor]){
                ret=1;
            }
            else if(i<sRamDArry[mStartFloor]){
                ret=1;
            }
        }
        else{
            ret=1;
        }
    }
    return(ret);
}


unsigned int  CarBoardDataReceive(void)
{

    UserDataType i,j,cmd;

    sRamDArry[mCarOpCl] =(UserDataType)(C1RX0B2 & 0x00ff);
    sRamDArry[mCarKey1] =(UserDataType)((C1RX0B2 >> 8) & 0x00ff);
    sRamDArry[mCarKey9] =(UserDataType)(C1RX0B3 & 0x00ff);
    sRamDArry[mCarKey17]=(UserDataType)((C1RX0B3 >> 8) & 0x00ff);;     
    sRamDArry[mCarKey25]=(UserDataType)(C1RX0B4 & 0x00ff);


    cmd=(UserDataType)(C1RX0B1 & 0x00ff);
    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);


    if(cmd==ALL_KEY_CLEAR){
        sRamDArry[mDoor]      =0;
        sRamDArry[mEqualFloor]=0;
        sRamDArry[mHighFloor] =0;
        sRamDArry[mLowFloor]  =0;

        return(0);
    }        



    if(cmd != CAN_KEY_DOOR){
        if(i & UPDN_CAR_READY){
            j=(i & ONLY_FLR);
            if(j>cF_TOPFLR){
                return(1);
            }
        }
        else{
            return(1);
        }
    }
    


    if(cmd==CAN_KEY_DOOR){
        sRamDArry[mDoor] = i;
    }        
    else if(cmd==CAN_KEY_CLEAR){
        if((sRamDArry[mEqualFloor] & CAR_READY) && ((i & ONLY_FLR) == (sRamDArry[mEqualFloor] & ONLY_FLR))){
            sRamDArry[mEqualFloor] = (sRamDArry[mEqualFloor] & ~CAR_READY);
        }
        if((sRamDArry[mHighFloor] & CAR_READY) && ((i & ONLY_FLR) == (sRamDArry[mHighFloor] & ONLY_FLR))){
            sRamDArry[mHighFloor] = (sRamDArry[mHighFloor] & ~CAR_READY);
        }
        if((sRamDArry[mLowFloor] & CAR_READY) && ((i & ONLY_FLR) == (sRamDArry[mLowFloor] & ONLY_FLR))){
            sRamDArry[mLowFloor] = (sRamDArry[mLowFloor] & ~CAR_READY);
        }
        if((sRamDArry[mMostLongDst] & CAR_READY)  && ((i & ONLY_FLR) == (sRamDArry[mMostLongDst] & ONLY_FLR))){
            sRamDArry[mMostLongDst] = (sRamDArry[mMostLongDst] & ~CAR_READY);
        }
    }
    else if(cmd==CAN_KEY_READY){
        j=(i & ONLY_FLR);

        if(j == (sRamDArry[mMostLongDst] & ONLY_FLR)){
            sRamDArry[mMostLongDst]=(sRamDArry[mMostLongDst] | CAR_READY);    
        }
        else{
            sRamDArry[mMostLongDst]= i;    
        }
    }
    else if(cmd==CAN_KEY_SET){
        if(i & UPDN_CAR_READY){
            j=(i & ONLY_FLR);

            if(j==sRamDArry[mcurfloor]){
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] & UPDN_READY);  
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] | i);
            }
            else if(j > sRamDArry[mcurfloor]){
                if((sRamDArry[mHighFloor] & ONLY_FLR) == j){
                    sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] & UPDN_READY);                
                    sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] | i);                
                }
                else{
                    sRamDArry[mHighFloor]  = i;                
                }
            }
            else if(j < sRamDArry[mcurfloor]){
                if((sRamDArry[mLowFloor] & ONLY_FLR) == j){
                    sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] & UPDN_READY);                
                    sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] | i);                
                }
                else{
                    sRamDArry[mLowFloor]  = i;                
                }
            }
        }
    }

    return(0);
}



unsigned int  HibBoardDataReceive(void)
{
    unsigned int i,j,cmd;

    if(CanCommandCheck())   return(1);


    cmd=(C1RX0B1) & 0x00ff;
    i=((C1RX0B1 >> 8) & 0x00ff);

    if(cmd != CAN_KEY_DOOR){
        i=i-sRamDArry[mStartFloor];
    }


    if(cmd==CAN_KEY_READY){
        j=(i & ONLY_FLR);
        if(j == (sRamDArry[mMostLongDst] & ONLY_FLR)){
            sRamDArry[mMostLongDst]=(sRamDArry[mMostLongDst] | i);    
        }
        else{
            sRamDArry[mMostLongDst]= i;    
        }
    }
    else if(cmd==CAN_KEY_SET){    
        if(i & UPDN_CAR_READY){
            j=(i & ONLY_FLR);
            if(j==sRamDArry[mcurfloor]){
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] & CAR_READY);  
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] | i);
                sRamDArry[mDoor]  = 0x01;
            }
            else if(j > sRamDArry[mcurfloor]){
                if((sRamDArry[mHighFloor] & ONLY_FLR) == j){
                    sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] & CAR_READY);                
                    sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] | i);                
                }
                else{
                    sRamDArry[mHighFloor]  = i;                
                }
            }
            else if(j < sRamDArry[mcurfloor]){
                if((sRamDArry[mLowFloor] & ONLY_FLR) == j){
                    sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] & CAR_READY);                
                    sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] | i);                
                }
                else{
                    sRamDArry[mLowFloor]  = i;                
                }
            }
        }
    }

    return(0);
}





unsigned int   ClearKeyData(void)
{
    
    unsigned int cmd;
    unsigned int i,j,k;

    if(CanCommandCheck())   return(1);


    cmd=(UserDataType)(C1RX0B1 & 0x00ff);
    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);

    if(cmd != CAN_KEY_DOOR){
        i=i-sRamDArry[mStartFloor];
    }


    if((cmd==CAN_KEY_SET)|| (cmd==CAN_KEY_READY)){
        if(i & UPDN_CAR_READY){
            j=(i & ONLY_FLR);
            k=(i & UPDN_CAR_READY);
    
            if(j == (sRamDArry[mHighFloor] & ONLY_FLR)){
                sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] & ~k);                                            
            }
            if(j == (sRamDArry[mLowFloor] & ONLY_FLR)){
                sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] & ~k);                                            
            }
            if(j == (sRamDArry[mEqualFloor] & ONLY_FLR)){
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] & ~k);                                            
            }
            if(j == (sRamDArry[mMostLongDst] & ONLY_FLR)){
                sRamDArry[mMostLongDst]  = (sRamDArry[mMostLongDst] & ~k);                                            
           }
        }
    }

    return(0);
}







void    Can1ReceiveSIDEIDArrary(void)
{
    unsigned int  tmpid1,tmpid2;

    C1ReceiveGroupNumber    =(C1RX0SID >> 9) & 0x000f;
//    C1LocalNumber    =(C1RX0EID >> 8) & 0x0007;
    C1ReceiveMaterAdr=(C1RX0EID >> 8) & 0x0007;

    if(C1RX0EID & 0x80){
        C1ReceiveAdrStatus=MASTER_TX_SLAVE;
    }
    else{
        C1ReceiveAdrStatus=SLAVE_TX_MASTER;

        tmpid1=(C1RX0DLC >> 10) & 0x0007;
        tmpid2=(C1RX0EID << 6)  & 0x00c0;
        C1ReceiveSlaveAdr=(tmpid1 | tmpid2);
    }

}



void _ISR _C1Interrupt(void)
{

    if(C1INTFbits.RX0IF){
//        C1ReceiveTime=0;
        Can1ReceiveSIDEIDArrary();
        C1DataSeq=0;

        if(C1ReceiveAdrStatus == MASTER_TX_SLAVE){

//            if(TestCan1 < 100)  TestCan1++;
        
/*
            if(C1ReceiveMaterAdr==7){
                if(MyLocalAddr==0)           C1Time=35;
                else if(MyLocalAddr==1)      C1Time=30;
                else if(MyLocalAddr==2)      C1Time=25;
                else if(MyLocalAddr==3)      C1Time=20;
                else if(MyLocalAddr==4)      C1Time=15;
                else if(MyLocalAddr==5)      C1Time=10;
                else if(MyLocalAddr==6)      C1Time=5;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==6){
                if(MyLocalAddr==7)           C1Time=35;
                else if(MyLocalAddr==0)      C1Time=30;
                else if(MyLocalAddr==1)      C1Time=25;
                else if(MyLocalAddr==2)      C1Time=20;
                else if(MyLocalAddr==3)      C1Time=15;
                else if(MyLocalAddr==4)      C1Time=10;
                else if(MyLocalAddr==5)      C1Time=5;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==5){
                if(MyLocalAddr==6)           C1Time=35;
                else if(MyLocalAddr==7)      C1Time=30;
                else if(MyLocalAddr==0)      C1Time=25;
                else if(MyLocalAddr==1)      C1Time=20;
                else if(MyLocalAddr==2)      C1Time=15;
                else if(MyLocalAddr==3)      C1Time=10;
                else if(MyLocalAddr==4)      C1Time=5;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==4){
                if(MyLocalAddr==5)           C1Time=35;
                else if(MyLocalAddr==6)      C1Time=30;
                else if(MyLocalAddr==7)      C1Time=25;
                else if(MyLocalAddr==0)      C1Time=20;
                else if(MyLocalAddr==1)      C1Time=15;
                else if(MyLocalAddr==2)      C1Time=10;
                else if(MyLocalAddr==3)      C1Time=5;
                else                         C1Time=0;
            }
            else 
*/
            if(C1ReceiveMaterAdr==3){
//                if(MyLocalAddr==4)           C1Time=40;
//                else if(MyLocalAddr==5)      C1Time=35;
//                else if(MyLocalAddr==6)      C1Time=30;
//                else if(MyLocalAddr==7)      C1Time=25;
                if(MyLocalAddr==0)      C1Time=25;
                else if(MyLocalAddr==1)      C1Time=20;
                else if(MyLocalAddr==2)      C1Time=15;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==2){
                if(MyLocalAddr==3)           C1Time=25;
//                else if(MyLocalAddr==4)      C1Time=35;
//                else if(MyLocalAddr==5)      C1Time=30;
//                else if(MyLocalAddr==6)      C1Time=25;
//                else if(MyLocalAddr==7)      C1Time=20;
                else if(MyLocalAddr==0)      C1Time=20;
                else if(MyLocalAddr==1)      C1Time=15;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==1){
                if(MyLocalAddr==2)           C1Time=25;
                else if(MyLocalAddr==3)      C1Time=20;
//                else if(MyLocalAddr==4)      C1Time=30;
//                else if(MyLocalAddr==5)      C1Time=25;
//                else if(MyLocalAddr==6)      C1Time=20;
//                else if(MyLocalAddr==7)      C1Time=15;
                else if(MyLocalAddr==0)      C1Time=15;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==0){
                if(MyLocalAddr==1)           C1Time=25;
                else if(MyLocalAddr==2)      C1Time=20;
                else if(MyLocalAddr==3)      C1Time=15;
//                else if(MyLocalAddr==4)      C1Time=25;
//                else if(MyLocalAddr==5)      C1Time=20;
//                else if(MyLocalAddr==6)      C1Time=15;
//                else if(MyLocalAddr==7)      C1Time=10;
                else                         C1Time=0;
            }
        }
        else if(C1ReceiveAdrStatus == SLAVE_TX_MASTER){

//            if(TestCan1 < 100)  TestCan1++;

            if(C1ReceiveMaterAdr==MyLocalAddr){
                if(C1ReceiveSlaveAdr & 0x80){
                    CarBoardDataReceive();
                }                          
                else{
                    HibBoardDataReceive();
                }
            }
            else{
                if(!(C1ReceiveSlaveAdr & 0x80)){
                    ClearKeyData();
                }
            }
        }

        C1INTFbits.RX0IF=0;
        C1RX0CONbits.RXFUL=0;
        C1Loop=0;

        if(TestCan1 < 200)  TestCan1++;
    }    
    else{
        TestCan1=0;

        C1CTRLbits.ABAT=1;      // aboart all pending transmit
        C1INTFbits.RX1IF=0;
        C1RX1CONbits.RXFUL=0;
        C1INTFbits.WAKIF=0;
        C1INTF=0;
        C1INTFbits.ERRIF=0;

        if(C1Loop < 65530)    C1Loop++;
    }

    IFS1bits.C1IF=0;
}







void  Can1Init(void)
{
    unsigned int sid;
    
    C1CTRLbits.REQOP    = 0x4;      // Entry Configration Mode
    C1CTRLbits.CANCAP   = 0x0;        // disable CAN Capture mode  ???

    C1CTRLbits.CSIDL    = 0x1;      // when idle mode,stop can
    C1CTRLbits.ABAT     = 0x1;      // aboart all pending transmit
    C1CTRLbits.CANCKS   = 0x1;      // fcan=fcy

    C1CFG2bits.SAM      = 0x1 ;     // Bus Line is sampled three times prior to the sample point
    C1CFG2bits.WAKFIL   = 0x0 ; 	// CAN bus line filter is not used for wake-up
    C1CFG2bits.SEG2PHTS = 0x1 ;     // Freely programmable;

//    C1CFG1bits.BRP      = 0x9;      // tq=0.00000125
    C1CFG1bits.BRP      = 19;      // tq=0.0000025
  
    C1CFG1bits.SJW      = 0x0;      // Synchronized Jump Width bits 1xTq
    C1CFG2bits.SEG1PH   = 0x1 ;     // 2 Tq
    C1CFG2bits.PRSEG    = 0x2 ;     // 3 Tq
    C1CFG2bits.SEG2PH   = 0x1 ; 	// 2 Tq

    C1TX0CON            = 0x3;
    C1TX1CON            = 0x3;

    C1TX0SIDbits.TXIDE  = 0x1;
    C1TX0SIDbits.SRR    = 0x0;
    C1TX0DLCbits.TXRB0  = 0x0;
    C1TX0DLCbits.TXRB1  = 0x0;
    C1TX0DLCbits.TXRTR  = 0x0;

    C1TX1SIDbits.TXIDE  = 0x1;
    C1TX1SIDbits.SRR    = 0x0;
    C1TX1DLCbits.TXRB0  = 0x0;
    C1TX1DLCbits.TXRB1  = 0x0;
    C1TX1DLCbits.TXRTR  = 0x0;

    C1TX2SIDbits.TXIDE  = 0x1;
    C1TX2SIDbits.SRR    = 0x1;
    C1TX2DLCbits.TXRB0  = 0x0;
    C1TX2DLCbits.TXRB1  = 0x0;
    C1TX2DLCbits.TXRTR  = 0x0;


    C1RXM0SID           = 0x0;
    C1RXM0EIDH          = 0x0;
    C1RXM0EIDL          = 0x0;
    C1RXM0SIDbits.MIDE  = 0x0;

    C1RXM1SID           = 0x0;
    C1RXM1EIDH          = 0x0;
    C1RXM1EIDL          = 0x0;
    C1RXM1SIDbits.MIDE  = 0x0;

    C1RXF0SID           = 0x0;
    C1RXF0EIDH          = 0x0;
    C1RXF0EIDL          = 0x0;
    C1RXF0SIDbits.EXIDE = 0x0;

    C1RXF1SID           = 0x0;
    C1RXF1EIDH          = 0x0;
    C1RXF1EIDL          = 0x0;
    C1RXF1SIDbits.EXIDE = 0x0;

    C1RXF2SID           = 0x0;
    C1RXF2EIDH          = 0x0;
    C1RXF2EIDL          = 0x0;
    C1RXF2SIDbits.EXIDE = 0x0;

    C1RXF3SID           = 0x0;
    C1RXF3EIDH          = 0x0;
    C1RXF3EIDL          = 0x0;
    C1RXF3SIDbits.EXIDE = 0x0;

    C1RXF4SID           = 0x0;
    C1RXF4EIDH          = 0x0;
    C1RXF4EIDL          = 0x0;
    C1RXF4SIDbits.EXIDE = 0x0;

    C1RXF5SID           = 0x0;
    C1RXF5EIDH          = 0x0;
    C1RXF5EIDL          = 0x0;
    C1RXF5SIDbits.EXIDE = 0x0;

    C1RX0CONbits.RXFUL  = 0x0;
//    C1RX0CONbits.DBEN   = 0x1;
    C1RX0CONbits.DBEN   = 0x0;
    C1RX0CONbits.JTOFF  = 0x0;
    C1RX0CONbits.FILHIT0= 0x0;

    C1RX1CONbits.RXFUL  = 0x0;


    C1INTE              = 0x0;
    C1INTEbits.ERRIE    = 0x1;
    C1INTEbits.RX0IE    = 0x1;
    C1INTEbits.RX1IE    = 0x1;
//    C1INTEbits.TX0IE    = 0x1;
//    C1INTEbits.TX1IE    = 0x1;
//    C1INTEbits.TX2IE    = 0x1;

    IEC1bits.C1IE       = 0x1;


    sid=(unsigned int)COMPANY;
//    sid=(unsigned int)(sid | (GroupAddr << 7));

    
    youCAN1SetFilter(0,sid,0xffff,0xffff);
    youCAN1SetFilter(1,sid,0xffff,0xffff);
    youCAN1SetFilter(2,sid,0xffff,0xffff);
    youCAN1SetFilter(3,sid,0xffff,0xffff);
    youCAN1SetFilter(4,sid,0xffff,0xffff);
    youCAN1SetFilter(5,sid,0xffff,0xffff);
 
    youCAN1SetMask(5,0xffff,0xffff,0xffff);
    youCAN1SetMask(4,0xffff,0xffff,0xffff);
    youCAN1SetMask(3,0xffff,0xffff,0xffff);
    youCAN1SetMask(1,0xffff,0xffff,0xffff);
    youCAN1SetMask(0,sid,0x0,0x0);
//    youCAN1SetMask(0,0,0x0,0x0);


    IPC6bits.C1IP=4;
    
    C1Time=0;
    while(C1Time<10);

    C1CTRLbits.REQOP    = 0x0;

    C1Time=0;
    while(C1Time<10);

    C1EC=0;                
    C1DataSeq=0;                
    C1Time=0;
}

