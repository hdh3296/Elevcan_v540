

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


UserDataType   C2DataSeqStart=0;

UserDataType   C2Time=0;
UserDataType   C2DataSeq=0;
unsigned int   C2Company=0;
//unsigned int   C2ReceiveGroupNumber=0;
//unsigned int   C2ReceiveMaterAdr=0;
unsigned int   C2ReceiveSlaveAdr=0;
unsigned int   C2ReceiveAdrStatus=0;

unsigned int   C2TmpSid=0;
unsigned int   C2TmdEidL=0;
unsigned int   C2TmdEidH=0;

unsigned int   C2Loop=0;

/*
#define  H2_INTV_TIME1  100   //msec
#define  H2_INTV_TIME2  105   //msec
#define  H2_INTV_TIME3  110   //msec
#define  H2_INTV_TIME4  115   //msec
#define  H2_INTV_TIME5  120   //msec
*/

#define  H2_INTV_TIME1  100   //msec
#define  H2_INTV_TIME2  100   //msec
#define  H2_INTV_TIME3  100   //msec
#define  H2_INTV_TIME4  100   //msec
#define  H2_INTV_TIME5  100   //msec


#define  I_AM_MASTER    0x2000


void   __attribute__((section(".usercode"))) CAN2SendMessageyou(char MsgFlag,unsigned int * data, unsigned int  datalen) 
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



void  __attribute__((section(".usercode"))) SetSidEid(void)
{

    C2TmpSid=(unsigned int)cF_COMPANY;
    C2TmpSid=(C2TmpSid | (MyGroupAddr << 7));

    C2TmdEidH=0;
	C2TmdEidL=0;

#ifndef	MAX_EIGHT_CAR
	if(MyGroupAddr & 0x10)	C2TmdEidH=(C2TmdEidH | 0x0001);	
	if(MyGroupAddr & 0x20)	C2TmdEidH=(C2TmdEidH | 0x0002);


    if(MyLocalAddr & 0x01)   C2TmdEidL=(C2TmdEidL | 0x4000);
    if(MyLocalAddr & 0x02)   C2TmdEidL=(C2TmdEidL | 0x8000);
#else
	if(MyGroupAddr & 0x10)	C2TmdEidH=(C2TmdEidH | 0x0002);
	
    if(MyLocalAddr & 0x01)   C2TmdEidL=(C2TmdEidL | 0x4000);
    if(MyLocalAddr & 0x02)   C2TmdEidL=(C2TmdEidL | 0x8000);
    if(MyLocalAddr & 0x04)   C2TmdEidH=(C2TmdEidH | 0x0001);
#endif

	C2TmdEidL = (C2TmdEidL | I_AM_MASTER); //master set
	
}



void    __attribute__((section(".usercode"))) Can2Init(void)
{
    unsigned int sid;
    unsigned int eidh,eidl;


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

    C2IE       = 0x1;



	SetSidEid();

/*
    sid=(unsigned int)cF_COMPANY;
    sid=(sid | (MyGroupAddr << 7));

    eidh=0;
    eidl=0;


    if(MyLocalAddr & 0x02)   eidl=(eidl | 0x8000);
    if(MyLocalAddr & 0x01)   eidl=(eidl | 0x4000);

    if(MyGroupAddr & 0x20)   eidh=(eidh | 0x0002);
    if(MyGroupAddr & 0x10)   eidh=(eidh | 0x0001);
*/


    youCAN2SetFilter(0,C2TmpSid,C2TmdEidH,C2TmdEidL);
    youCAN2SetFilter(1,0x0,0x0,0x0);
    youCAN2SetFilter(2,0x0,0x0,0x0);
    youCAN2SetFilter(3,0x0,0x0,0x0);
    youCAN2SetFilter(4,0x0,0x0,0x0);
    youCAN2SetFilter(5,0x0,0x0,0x0);
 
    youCAN2SetMask(5,0xffff,0xffff,0xffff);
    youCAN2SetMask(4,0xffff,0xffff,0xffff);
    youCAN2SetMask(3,0xffff,0xffff,0xffff);
    youCAN2SetMask(1,0xffff,0xffff,0xffff);
    youCAN2SetMask(0,0x07ff,0x0003,0xc000);


    IPC9bits.C2IP=4;


/*
    C2Time=0;
    while(C2Time<10);

    C2CTRLbits.REQOP    = 0x0;

    C2Time=0;
    while(C2Time<10);
*/
    
    C2CTRLbits.REQOP    = 0x0;

                
    C2DataSeq=0;                
    C2Time=0;
    C2EC=0;
}







void  __attribute__((section(".usercode"))) NormalDataReturn(void)
{
    LocalType sel,xx;

    sel=0;

    if(!C2TX0CONbits.TXREQ && (C2DataSeqStart==1)){
        if(C2Time > H2_INTV_TIME5){
			xx=0;
			if(C2DataSeq == 4){
				C2DataSeq=8;
				xx=4;
			}
            youCAN2TxSidSet(sel,C2TmpSid);
            youCAN2TxEidSet(sel,C2TmdEidH,C2TmdEidL+C2DataSeq);
            LoadCanBuffer(C2DataSeq-xx);



	if(C2DataSeq==1){
		CAN_Buf[0] = sRamDArry[FLR_ON_OFF0];
		CAN_Buf[1] = sRamDArry[FLR_ON_OFF1];
		CAN_Buf[2] = sRamDArry[FLR_ON_OFF2];
		CAN_Buf[3] = sRamDArry[FLR_ON_OFF3];     
	}


			if(C2DataSeq >= 8){
				CAN_Buf[7] = CAN2_Buf[2];
			}

            CAN2SendMessageyou(sel,&CAN_Buf[0], 8);        
            C2DataSeq++;       			

			if(C2DataSeq > 8){
	            C2Time=0;
	            C2DataSeq=0;       
	            C2DataSeqStart=0;
			}
		}
	}
 
}







LocalType __attribute__((section(".usercode"))) HostReadMyData(void)
{
    if((CAN2_Buf[2] == 0x00) && (CAN2_Buf[3] == 0x00)){
        NormalDataReturn();
    }
/*
    else if((CAN2_Buf[2] == 0x01) && (CAN2_Buf[3] == 0)){
        DataReturn(CAN2_Buf[2],2);
    }
    else if((CAN2_Buf[2] == 0x02) && (CAN2_Buf[3] == 0)){
        DataReturn(CAN2_Buf[2],4);
    }
    else if((CAN2_Buf[2] == 0x03) && (CAN2_Buf[3] == 0)){
        DataReturn(CAN2_Buf[2],2);
    }
    else if((CAN2_Buf[2] == 0x04) && (CAN2_Buf[3] == 0)){
        DataReturn(CAN2_Buf[2],2);
    }
*/
}





LocalType __attribute__((section(".usercode"))) HostCommandAct(void)
{

    if((CAN2_Buf[2]    ==   (PC_COMMAND | CMD_PARKING)) && (CAN2_Buf[3] == 0x00)){
        if(CAN2_Buf[4] == 0x01) bPC_PRK = 1;
        else                    bPC_PRK = 0;
		NormalDataReturn();    
    }    
    else if((CAN2_Buf[2]    ==   (PC_COMMAND | CMD_FIRE)) && (CAN2_Buf[3] == 0x00)){
        if(CAN2_Buf[4] == 0x01) bPC_FIRE = 1;
        else                    bPC_FIRE = 0;
		NormalDataReturn();    
    }
    else if((CAN2_Buf[2]    ==   (PC_COMMAND | CMD_FAMILY_SEV)) && (CAN2_Buf[3] == 0x00)){
        if(CAN2_Buf[4] == 0x01) bPC_FAMILY = 1;
        else                    bPC_FAMILY = 0;
		NormalDataReturn();    
    }

    else if((CAN2_Buf[2]    ==   (PC_COMMAND | CMD_CALL_SEV)) && (CAN2_Buf[3] == 0x00)){
		CrtMoveFlr=(unsigned char)(CAN2_Buf[4] | CAR_READY);
		NormalDataReturn();    
    }

    else if((CAN2_Buf[2]    ==   (PC_COMMAND | CMD_EXT_CALL_SEV)) && (CAN2_Buf[3] == 0x00)){
		sRamDArry[mCrtExtMoveFlr]=(unsigned char)(CAN2_Buf[4]);
		ExtKeyCnt=3;
		CAN2_Buf[0]=0;
		NormalDataReturn();    
    }
}



LocalType __attribute__((section(".usercode"))) HostWriteMyData(void)
{

//	if( !bMoveCar ){
	    if((CAN2_Buf[2] == (CMD_EVEN_ODD)) && (CAN2_Buf[3] == 0x00)){
	        Pc_Command();
			NormalDataReturn();    
	    }    
	    else if((CAN2_Buf[2] == (CMD_MORNING)) && (CAN2_Buf[3] == 0x00)){
	        Pc_Command();
			NormalDataReturn();    
	    }    
//	}
}



LocalType __attribute__((section(".usercode"))) Can2Check(void)
{    
	unsigned int i;

    if(C2DataSeqStart==0){
        if(C2Loop > 100){
           	Can2Init();
            C2Loop=0;
        }
        return(0);
    }
    
    switch(CAN2_Buf[0]){
        case    0x23:
            HostReadMyData();
            break;
        case    0x24:
            if(CAN2_Buf[2] & PC_COMMAND){
                HostCommandAct();             
            }
            else{
                HostWriteMyData();             
            }
            break;
    }        

    return(0);
}



void      __attribute__((section(".usercode"))) Can2ReceiveSIDEIDArrary(void)
{

    unsigned int  tmpid1,tmpid2;

//    C2ReceiveGroupNumber=(C2RX0SID >> 9) & 0x000f;
//    C2ReceiveMaterAdr=(C2RX0EID >> 8) & 0x0003; //local address

	
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




void _ISR _C2Interrupt(void)
{

    if(C2INTFbits.RX0IF){
        
        Can2ReceiveSIDEIDArrary();

        CAN2_Buf[0] =(UserDataType)(C2RX0B1 & 0x00ff);
        CAN2_Buf[1] =(UserDataType)((C2RX0B1 >> 8) & 0x00ff);     

        CAN2_Buf[2] =(UserDataType)(C2RX0B2 & 0x00ff);
        CAN2_Buf[3] =(UserDataType)((C2RX0B2 >> 8) & 0x00ff);     

        CAN2_Buf[4] =(UserDataType)(C2RX0B3 & 0x00ff);
        CAN2_Buf[5] =(UserDataType)((C2RX0B3 >> 8) & 0x00ff);     

        CAN2_Buf[6] =(UserDataType)(C2RX0B4 & 0x00ff);
        CAN2_Buf[7] =(UserDataType)((C2RX0B4 >> 8) & 0x00ff);     


        C2Time=0;
        C2DataSeq=0;       


//		if((CAN2_Buf[0] == 0x23) || (CAN2_Buf[0] == 0x24) || (CAN2_Buf[0] == 0xa4)){
	        C2DataSeqStart=1;
	        C2Time=H2_INTV_TIME1 - 5;
//  		}
      
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
    }

    C2IF=0;
    C2INTFbits.RX0IF=0;
    C2RX0CONbits.RXFUL=0;
}



