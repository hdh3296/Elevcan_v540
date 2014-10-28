

#include <p30f6010.h>      
      
#include    "you_can_lib.h" 
#include    "you_can1.h" 
#include    "iodef.h"
#include    "door.h"
#include    "default_setup.h"
#include    "..\..\system_com\memory_map.h"



#define  H_INTV_TIME  110   //msec
//#define  H_INTV_TIME2  100   //msec
//#define  H_INTV_TIME3  100   //msec
//#define  H_INTV_TIME4  100   //msec
//#define  H_INTV_TIME5  100   //msec


#define  NEXT_INTERVAL 10


UserDataType   C1Time=0;
UserDataType   C1DataSeq=0;

UserDataType   SelMainCarTime=0;
UserDataType   SelSubCarTime =0;


//unsigned int   C1Company=0;
//unsigned int   C1ReceiveGroupNumber=0;
unsigned int   C1ReceiveMaterAdr=0;
unsigned int   C1ReceiveSlaveAdr=0;
unsigned int   C1ReceiveAdrStatus=0;
unsigned int   C1Loop=0;


unsigned int   ThisReceiveSlave=0;
unsigned int   TxPercent=0;
unsigned int   Percent=0;



void __attribute__((section(".usercode")))  CAN1SendMessageyou(char MsgFlag,unsigned int * data, unsigned int  datalen) 
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




void    __attribute__((section(".usercode")))  Can1Check(void)
{

    LocalType sel,i;

    unsigned int tmpeidH,tmpeidL;
    unsigned int tmpsidH,tmpsidL;

    sel=0;

    tmpeidH=C1EC;
    tmpeidL=C1EC & 0x00ff;


    if(tmpeidH >= 0x8100){
        Can1Init();
    }
    else if(tmpeidL >= 0x81){
        Can1Init();
    } 


    tmpsidH=(unsigned int)cF_COMPANY;   //company name
    tmpsidL=(unsigned int)(MyGroupAddr);
    tmpsidL=(unsigned int)(tmpsidL << 7);
    tmpsidL=tmpsidL | tmpsidH;

    tmpeidH=0;   //not use
    tmpeidL=(unsigned int)(MyLocalAddr << 14);
    tmpeidL=(unsigned int)(tmpeidL | 0x2000);


	#ifdef	MAX_EIGHT_CAR	
		if(MyLocalAddr & 0x04)	tmpeidH= (tmpeidH | 0x01);   
	#endif


    if(!C1TX0CONbits.TXREQ && (C1Time > H_INTV_TIME)){
        if(C1DataSeq==4){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+8);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1Time=0;
            C1DataSeq=0;
            if(TxPercent>0){
                Percent=((ThisReceiveSlave * 100)/TxPercent);
            }
            else    Percent=0;
    
            TxPercent++;

            if(TxPercent > 100){
                TxPercent=1;
                ThisReceiveSlave=0;
            } 

            if(!bAuto){            
                sRamDArry[mDoor]      =0;
            }


			if(ExtKeyCnt==0)	sRamDArry[mCrtExtMoveFlr]=0;
			else				ExtKeyCnt--;			
        }
        else  if(C1DataSeq==3){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+3);
            LoadCanBuffer(C1DataSeq);

            CAN1SendMessageyou(sel,&CAN_Buf[0], 8); 
            C1DataSeq=4;       
        }
        else if(C1DataSeq==2){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+2);
            LoadCanBuffer(C1DataSeq);

			if(bHibSet){
				CAN_Buf[0]=0;
	            CAN_Buf[4]= 0;  

				if(HibSet[0] == 1)		CAN_Buf[0]=(CAN_Buf[0] | 0x01);
				else if(HibSet[0] == 2)	CAN_Buf[0]=(CAN_Buf[0] | 0x02);

				else if(HibSet[0] == 3)	CAN_Buf[4]=(CAN_Buf[4] | 0x01);
				else if(HibSet[0] == 4)	CAN_Buf[4]=(CAN_Buf[4] | 0x02);
				else if(HibSet[0] == 5)	CAN_Buf[4]=(CAN_Buf[4] | 0x04);
				else if(HibSet[0] == 6)	CAN_Buf[4]=(CAN_Buf[4] | 0x08);

				if(HibSet[1] == 1)		CAN_Buf[0]=(CAN_Buf[0] | 0x04);
				else if(HibSet[1] > 1)	CAN_Buf[0]=(CAN_Buf[0] | 0x08);

				if(HibSet[2] == 1)		CAN_Buf[0]=(CAN_Buf[0] | 0x10);
				else if(HibSet[2] > 1)	CAN_Buf[0]=(CAN_Buf[0] | 0x20);

	            CAN_Buf[0]= (unsigned char)(CAN_Buf[0] | 0xc0);  


	            CAN_Buf[1]= (unsigned char)(HibSet[3]);
	            CAN_Buf[2]= (unsigned char)(HibSet[4]);
	            CAN_Buf[3]= (unsigned char)(HibSet[5]);
			}

            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1DataSeq=3;       
        }
        else if(C1DataSeq==1){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+1);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1DataSeq=2;       
        }
        else if(C1DataSeq==0){
            youCAN1TxSidSet(sel,tmpsidL);
            youCAN1TxEidSet(sel,tmpeidH,tmpeidL+0);
            LoadCanBuffer(C1DataSeq);
            CAN1SendMessageyou(sel,&CAN_Buf[0], 8);        
            C1DataSeq=1;
        }
        else{
            C1DataSeq=0;       
        }

/*
        else if((C1Time > H_INTV_TIME) && (C1DataSeq>4)){
            C1Time=0;
            C1DataSeq=0;       
        }
*/
    }
}




unsigned int  __attribute__((section(".usercode")))  CanCommandCheck(void)
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


unsigned int  __attribute__((section(".usercode")))  HibRelocateStartfloor(void)
{
//cmd/ flr/ subdoor
	
    UserDataType j,i;
//	long_field	TLF;

	if(cF_START_FLOOR == 0)		return(0);

 
	j=(UserDataType)cF_START_FLOOR;

    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);

	i=(i & ONLY_FLR);
	if(i >=	j){
		i=(i - j);	
		i=((i << 8) & 0x1f00);
		C1RX0B1= (C1RX0B1 & 0xe0ff);
		C1RX0B1=(C1RX0B1 | i);
	}

/*
    tmpx0 =(UserDataType)((C1RX0B2 >> 8) & 0x00ff);
    tmpx1 =(UserDataType)(C1RX0B3 & 0x00ff);
    tmpx2 =(UserDataType)((C1RX0B3 >> 8) & 0x00ff);     
    tmpx3 =(UserDataType)(C1RX0B4 & 0x00ff);

	TLF.byte[0]=(unsigned char)tmpx0;
	TLF.byte[1]=(unsigned char)tmpx1;
	TLF.byte[2]=(unsigned char)tmpx2;
	TLF.byte[3]=(unsigned char)tmpx3;

	TLF.long_data=(TLF.long_data >> j);


    tmpx0 =(UserDataType)((tmpx0 << 8) & 0xff00);
    C1RX0B2 = (C1RX0B2 & 0x00ff);
    C1RX0B2 = (C1RX0B2 | tmpx0);

    tmpx1 =(UserDataType)(tmpx1 & 0x00ff);
    C1RX0B3 = (C1RX0B3 & 0xff00);
    C1RX0B3 = (C1RX0B3 | tmpx1);

    tmpx2 =(UserDataType)((tmpx2 << 8) & 0xff00);
    C1RX0B3 = (C1RX0B3 & 0x00ff);
    C1RX0B3 = (C1RX0B3 | tmpx2);

    tmpx3 =(UserDataType)(tmpx3 & 0x00ff);
    C1RX0B4 = (C1RX0B4 & 0xff00);
    C1RX0B4 = (C1RX0B4 | tmpx4);
*/
	return(0);
}


unsigned int  __attribute__((section(".usercode")))  CarRelocateStartfloor(void)
{
//cmd/ flr/ opcl/ carkey0/carkey1/carkey2/carkey3/subdoor
//cmd/ flr/ opcl/ carkey0/carkey1/carkey2/carkey3/subdoor

    UserDataType j,i,cmd;
	
//  UserDataType tmpx0,tmpx1,tmpx2,tmpx3;
//	long_field	TLF;


	if(cF_START_FLOOR == 0)		return(0);

    cmd=(UserDataType)(C1RX0B1 & 0x00ff);
    if(cmd==CAN_KEY_DOOR)		return(0);

 
	j=(UserDataType)cF_START_FLOOR;

    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);

	i=(i & ONLY_FLR);

	if(i >=	j){
		i=(i - j);		
		i=((i << 8) & 0x1f00);
		C1RX0B1=(C1RX0B1 & 0xe0ff);
		C1RX0B1=(C1RX0B1 | i);
	}


/*
    tmpx0 =(UserDataType)((C1RX0B2 >> 8) & 0x00ff);
    tmpx1 =(UserDataType)(C1RX0B3 & 0x00ff);
    tmpx2 =(UserDataType)((C1RX0B3 >> 8) & 0x00ff);     
    tmpx3 =(UserDataType)(C1RX0B4 & 0x00ff);

	TLF.byte[0]=(unsigned char)tmpx0;
	TLF.byte[1]=(unsigned char)tmpx1;
	TLF.byte[2]=(unsigned char)tmpx2;
	TLF.byte[3]=(unsigned char)tmpx3;

	TLF.long_data=(TLF.long_data >> j);


    tmpx0 =(UserDataType)((tmpx0 << 8) & 0xff00);
    C1RX0B2 = (C1RX0B2 & 0x00ff);
    C1RX0B2 = (C1RX0B2 | tmpx0);

    tmpx1 =(UserDataType)(tmpx1 & 0x00ff);
    C1RX0B3 = (C1RX0B3 & 0xff00);
    C1RX0B3 = (C1RX0B3 | tmpx1);

    tmpx2 =(UserDataType)((tmpx2 << 8) & 0xff00);
    C1RX0B3 = (C1RX0B3 & 0x00ff);
    C1RX0B3 = (C1RX0B3 | tmpx2);

    tmpx3 =(UserDataType)(tmpx3 & 0x00ff);
    C1RX0B4 = (C1RX0B4 & 0xff00);
    C1RX0B4 = (C1RX0B4 | tmpx3);
*/

	return(0);
}


void  __attribute__((section(".usercode")))  CarKeyCheck(void)
{
    UserDataType tmpx0,tmpx1,tmpx2,tmpx3,j;

    j=0;

    tmpx0 =(UserDataType)((C1RX0B2 >> 8) & 0x00ff);
    tmpx1 =(UserDataType)(C1RX0B3 & 0x00ff);
    tmpx2 =(UserDataType)((C1RX0B3 >> 8) & 0x00ff);     
    tmpx3 =(UserDataType)(C1RX0B4 & 0x00ff);
        
    switch(C1ReceiveSlaveAdr){
        case    0x80:
            YourKey0[0]=tmpx0;
            YourKey0[1]=tmpx1;
            YourKey0[2]=tmpx2;
            YourKey0[3]=tmpx3;
            j=1;
            break;
        case    0x81:
            YourKey1[0]=tmpx0;
            YourKey1[1]=tmpx1;
            YourKey1[2]=tmpx2;
            YourKey1[3]=tmpx3;
            j=1;
            break;
        case    0x82:
            YourKey2[0]=tmpx0;
            YourKey2[1]=tmpx1;
            YourKey2[2]=tmpx2;
            YourKey2[3]=tmpx3;
            j=1;
            break;
        case    0x83:
            YourKey3[0]=tmpx0;
            YourKey3[1]=tmpx1;
            YourKey3[2]=tmpx2;
            YourKey3[3]=tmpx3;
            j=1;
            break;
    }
    
    if(j==1){    
        sRamDArry[mCarKey1] =YourKey0[0] | YourKey1[0] | YourKey2[0] | YourKey3[0];
        sRamDArry[mCarKey9] =YourKey0[1] | YourKey1[1] | YourKey2[1] | YourKey3[1];
        sRamDArry[mCarKey17]=YourKey0[2] | YourKey1[2] | YourKey2[2] | YourKey3[2];
        sRamDArry[mCarKey25]=YourKey0[3] | YourKey1[3] | YourKey2[3] | YourKey3[3];                
    }
}            



unsigned int   __attribute__((section(".usercode")))  ClearKeyData(void)
{
    
    unsigned int cmd;
    unsigned int i,j,k;

	if(bPC_FAMILY && (C1ReceiveMaterAdr != MyLocalAddr)){
		return(1);	
	}


    i=(C1RX0B2 & 0x00ff);
	if( (i & 0x08) && (C1ReceiveMaterAdr != MyLocalAddr)){
		return(1);  // single slave
	}


	HibRelocateStartfloor();

    if(CanCommandCheck())   return(1);


    cmd=(UserDataType)(C1RX0B1 & 0x00ff);
    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);

    if(cmd != CAN_KEY_DOOR){
        i=i-sRamDArry[mStartFloor];
    }


    if((cmd==CAN_KEY_SET) || (cmd==CAN_KEY_READY) || (cmd==CAN_KEY_CLEAR) ){
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



unsigned int  __attribute__((section(".usercode")))  FloorOnOffDataReceive(void)
{
	sRamDArry[ExtCmdFlrONOFF0]=(unsigned char)(C1RX0B1 & 0x00ff);	
	sRamDArry[ExtCmdFlrONOFF1]=(unsigned char)((C1RX0B1 >> 8) & 0x00ff);	
	sRamDArry[ExtCmdFlrONOFF2]=(unsigned char)(C1RX0B2 & 0x00ff);	
	sRamDArry[ExtCmdFlrONOFF3]=(unsigned char)((C1RX0B2 >> 8) & 0x00ff);	
	ExtCmdFlrONOFFCnt=0;
	AccTimer=0;
	return(0);
}

unsigned int  __attribute__((section(".usercode")))  ExtIODataReceive(void)
{
	sRamDArry[mExtIN0]=(unsigned char)(C1RX0B1 & 0x00ff);	
	ExIOTimer=0;
	return(0);
}

unsigned int  __attribute__((section(".usercode")))  CarBoardDataReceive(void)
{

    UserDataType i,j,cmd,seconddoor;

	CarRelocateStartfloor();

    seconddoor          =(UserDataType)((C1RX0B4 >> 8) & 0x00ff);

    
    if(S2_FIRE1){
        if(seconddoor & 0x01){
            if(SelMainCarTime < 10) return(0);
            else                    SelSubCarTime =0;    
        }
        else{
            if(SelSubCarTime < 10)  return(0);
            else                    SelMainCarTime=0;
        }
    }
    else{
        SelMainCarTime=10;
        SelSubCarTime =10;
    }


    sRamDArry[mCarOpCl] =(UserDataType)(C1RX0B2 & 0x00ff);

    CarKeyCheck();

    cmd=(UserDataType)(C1RX0B1 & 0x00ff);
    i=(UserDataType)((C1RX0B1 >> 8) & 0x00ff);


    if(cmd==ALL_KEY_CLEAR){
		if(sRamDArry[mFireSeq] != FIRE_START){
	        sRamDArry[mDoor]      =0;
	        sRamDArry[mEqualFloor]=0;
	        sRamDArry[mHighFloor] =0;
	        sRamDArry[mLowFloor]  =0;
		}	
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
        sRamDArry[mDoor] = ((i & ~CAR_READY) | sRamDArry[mDoor]);
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
				if(!S4_CAR_MOST_SERVICE1 || !bMoveCar){		/////3.4d
	                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] & UPDN_READY);  
	                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] | i);
	                if(seconddoor & 0x01)   sRamDArry[mDoor]  = (sRamDArry[mDoor] | 0x04);
	                else                    sRamDArry[mDoor]  = (sRamDArry[mDoor] | 0x01);   
				}
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



unsigned int  __attribute__((section(".usercode")))  HibBoardDataReceive(void)
{
    unsigned int i,j,cmd,seconddoor;

	HibRelocateStartfloor();

    if(CanCommandCheck())   return(1);

    seconddoor =(UserDataType)(C1RX0B2 & 0x00ff);

    cmd=(C1RX0B1) & 0x00ff;
    i=((C1RX0B1 >> 8) & 0x00ff);

    if(cmd != CAN_KEY_DOOR){
        i=i-sRamDArry[mStartFloor];
    }


    if(cmd==CAN_KEY_CLEAR){
        ClearKeyData();
    }
    else if(cmd==CAN_KEY_READY){
        j=(i & ONLY_FLR);
        if(j == (sRamDArry[mMostLongDst] & ONLY_FLR)){
            sRamDArry[mMostLongDst]=(sRamDArry[mMostLongDst] | i);    
        }
        else{
            sRamDArry[mMostLongDst]= i;    
        }
    }
    else if(cmd==CAN_KEY_SET){    
        if((i & UPDN_CAR_READY)){
            j=(i & ONLY_FLR);
            if(j==sRamDArry[mcurfloor]){
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] & CAR_READY);  
                sRamDArry[mEqualFloor]  = (sRamDArry[mEqualFloor] | i);
                if(seconddoor & 0x01)   sRamDArry[mDoor]  = (sRamDArry[mDoor] | 0x04);
                else                    sRamDArry[mDoor]  = (sRamDArry[mDoor] | 0x01);   

				if(seconddoor & 0x04)	TmpBuzor=0;
		
            }
            else if((j > sRamDArry[mcurfloor]) && !bHibCallClear){
                if((sRamDArry[mHighFloor] & ONLY_FLR) == j){
                    sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] & CAR_READY);                
                    sRamDArry[mHighFloor]  = (sRamDArry[mHighFloor] | i);                
                }
                else{
					if(!S4_CAR_MOST_SERVICE1)	sRamDArry[mHighFloor]  = i;                
                }
            }
            else if((j < sRamDArry[mcurfloor]) && !bHibCallClear){
                if((sRamDArry[mLowFloor] & ONLY_FLR) == j){
                    sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] & CAR_READY);                
                    sRamDArry[mLowFloor]  = (sRamDArry[mLowFloor] | i);                
                }
                else{
                    if(!S4_CAR_MOST_SERVICE1)	sRamDArry[mLowFloor]  = i;                
                }
            }
        }
    }


    else if(cmd==CAN_KEY_CONFIRM){
        if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        	if((i & UPDN_CAR_READY) == DN_READY){
	            if(seconddoor & 0x01)   sRamDArry[mDoor]  = (sRamDArry[mDoor] | 0x08);
	            else                    sRamDArry[mDoor]  = (sRamDArry[mDoor] | 0x02);   
			}
        }
    }


/////////////you
    else if(cmd==CAN_VIP_COMMAND){    
        if(i & UPDN_CAR_READY){
            j=(i & ONLY_FLR);
            if((j == sRamDArry[mcurfloor]) &&  (S1_OPEN1 || S3_OPEN_SUB1) ){
                Vip_Floor=i;
                bOnceVip=1;
            }
        }
    }
/////////////you
    else if(cmd==CAN_PARKING_COMMAND){    
    	i=(C1RX0B2 & 0x00ff);
		if(i & 0x02){
			bSlavePrk=1;
		}
		else	bSlavePrk=0;
    }


    return(0);
}





void    __attribute__((section(".usercode")))  PcCommandMe(void)
{
    CAN2_Buf[0] =(UserDataType)(C1RX0B1 & 0x00ff);
    CAN2_Buf[1] =(UserDataType)((C1RX0B1 >> 8) & 0x00ff);     

    CAN2_Buf[2] =(UserDataType)(C1RX0B2 & 0x00ff);
    CAN2_Buf[3] =(UserDataType)((C1RX0B2 >> 8) & 0x00ff);     

    CAN2_Buf[4] =(UserDataType)(C1RX0B3 & 0x00ff);
    CAN2_Buf[5] =(UserDataType)((C1RX0B3 >> 8) & 0x00ff);     

    CAN2_Buf[6] =(UserDataType)(C1RX0B4 & 0x00ff);
    CAN2_Buf[7] =(UserDataType)((C1RX0B4 >> 8) & 0x00ff);     


    if(CAN2_Buf[0]== 0x24){
	    if(CAN2_Buf[2] & PC_COMMAND){
	        HostCommandAct();             
	    }
	    else{
	        HostWriteMyData();             
	    }
	}
}




void    __attribute__((section(".usercode")))  Can1ReceiveSIDEIDArrary(void)
{
    unsigned int  tmpid1,tmpid2;

//    C1ReceiveGroupNumber    =(C1RX0SID >> 9) & 0x000f;
//    C1ReceiveMaterAdr       =(C1RX0EID >> 8) & 0x0003;

#ifndef	MAX_EIGHT_CAR
    C1ReceiveMaterAdr       =(C1RX0EID >> 8) & 0x0003;
#else
    C1ReceiveMaterAdr       =(C1RX0EID >> 8) & 0x0007;
#endif


    if(C1RX0EID & 0x80){
        C1ReceiveAdrStatus=MASTER_TX_SLAVE;
    }
    else{
        C1ReceiveAdrStatus=SLAVE_TX_MASTER;
        tmpid1=(C1RX0DLC >> 10) & 0x003f;
        tmpid2=(C1RX0EID << 6)  & 0x00c0;
        C1ReceiveSlaveAdr=(tmpid1 | tmpid2);
    }
}



void  _ISR _C1Interrupt(void)
{

    if(C1INTFbits.RX0IF){
        Can1ReceiveSIDEIDArrary();
        C1DataSeq=0;

		if(C1ReceiveAdrStatus == MASTER_TX_SLAVE){

//you			C1Time=0;

            if(C1ReceiveMaterAdr==0){
                if(MyLocalAddr==1)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==2)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==3)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==4)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==5)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==6)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==7)      C1Time=NEXT_INTERVAL+0;
            }
            else if(C1ReceiveMaterAdr==1){
                if(MyLocalAddr==2)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==3)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==4)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==5)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==6)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==7)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==0)      C1Time=NEXT_INTERVAL+0;
            }
            else if(C1ReceiveMaterAdr==2){
                if(MyLocalAddr==3)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==4)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==5)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==6)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==7)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==0)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==1)      C1Time=NEXT_INTERVAL+0;
            }
            else if(C1ReceiveMaterAdr==3){
                if(MyLocalAddr==4)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==5)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==6)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==7)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==0)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==1)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==2)      C1Time=NEXT_INTERVAL+0;
            }

#ifdef	MAX_EIGHT_CAR
            else if(C1ReceiveMaterAdr==4){
                if(MyLocalAddr==5)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==6)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==7)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==0)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==1)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==2)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==3)      C1Time=NEXT_INTERVAL+0;
            }
            else if(C1ReceiveMaterAdr==5){
                if(MyLocalAddr==6)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==7)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==0)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==1)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==2)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==3)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==4)      C1Time=NEXT_INTERVAL+0;
            }
            else if(C1ReceiveMaterAdr==6){
                if(MyLocalAddr==7)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==0)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==1)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==2)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==3)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==4)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==5)      C1Time=NEXT_INTERVAL+0;
            }
            else if(C1ReceiveMaterAdr==7){
                if(MyLocalAddr==0)           C1Time=NEXT_INTERVAL+60;
                else if(MyLocalAddr==1)      C1Time=NEXT_INTERVAL+50;
                else if(MyLocalAddr==2)      C1Time=NEXT_INTERVAL+40;
                else if(MyLocalAddr==3)      C1Time=NEXT_INTERVAL+30;
                else if(MyLocalAddr==4)      C1Time=NEXT_INTERVAL+20;
                else if(MyLocalAddr==5)      C1Time=NEXT_INTERVAL+10;
                else if(MyLocalAddr==6)      C1Time=NEXT_INTERVAL+0;
            }

#endif
/*
            if(C1ReceiveMaterAdr==3){
                if(MyLocalAddr==0)      	 C1Time=25;
                else if(MyLocalAddr==1)      C1Time=20;
                else if(MyLocalAddr==2)      C1Time=15;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==2){
                if(MyLocalAddr==3)           C1Time=25;
                else if(MyLocalAddr==0)      C1Time=20;
                else if(MyLocalAddr==1)      C1Time=15;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==1){
                if(MyLocalAddr==2)           C1Time=25;
                else if(MyLocalAddr==3)      C1Time=20;
                else if(MyLocalAddr==0)      C1Time=15;
                else                         C1Time=0;
            }
            else if(C1ReceiveMaterAdr==0){
                if(MyLocalAddr==1)           C1Time=25;
                else if(MyLocalAddr==2)      C1Time=20;
                else if(MyLocalAddr==3)      C1Time=15;
                else                         C1Time=0;
            }
*/


        }
        else if(C1ReceiveAdrStatus == SLAVE_TX_MASTER){
////////hib_crt
			if(C1ReceiveSlaveAdr == 0xfe){
	            if(C1ReceiveMaterAdr==MyLocalAddr){
					PcCommandMe();
				}
			}

			else{	
////////
	            if(C1ReceiveMaterAdr==MyLocalAddr){
	                if(C1ReceiveSlaveAdr & 0x80){
						if(C1ReceiveSlaveAdr == 0x8A)		FloorOnOffDataReceive();	
						else if(C1ReceiveSlaveAdr == 0x8B)	ExtIODataReceive();	
						else								CarBoardDataReceive();
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
	
	            if((C1ReceiveSlaveAdr == sRamDArry[mCallMe]) && (C1ReceiveMaterAdr==MyLocalAddr)){
	                ThisReceiveSlave++;
	            }
			}
        }

        C1INTFbits.RX0IF=0;
        C1RX0CONbits.RXFUL=0;
        C1Loop=0;
    }    
    else{
        C1CTRLbits.ABAT=1;      // aboart all pending transmit
        C1INTFbits.RX1IF=0;
        C1RX1CONbits.RXFUL=0;
        C1INTFbits.WAKIF=0;
        C1INTF=0;
        C1INTFbits.ERRIF=0;

        if(C1Loop < 65530){
            C1Loop++;
        }
    }

    IFS1bits.C1IF=0;
}







void  __attribute__((section(".usercode")))  Can1Init(void)
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


    sid=(unsigned int)cF_COMPANY;
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
    
//    C1Time=0;
//    while(C1Time<10);

    C1CTRLbits.REQOP    = 0x0;

//    C1Time=0;
//    while(C1Time<10);

    C1EC=0;                
    C1DataSeq=0;                
    C1Time=0;
}

