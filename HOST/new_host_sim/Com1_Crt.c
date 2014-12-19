

#include <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"



#ifndef		RS485_FOR_CRT	


UserDataType  __attribute__((section(".usercode"))) OnceSaveErrorSet(UserDataType set)
{

   LocalType  temp,temp1,temp3;
   
   temp=ErrBdNamePt/8;
   temp1=ErrBdNamePt%8;      
   
	temp3=0x01;
	temp1=(temp3 << temp1);

   
   if(set==2){
      if(Olderrbd[temp] & temp1) return(1);         
      else                       return(0);         
   }
   else if(set==1){
      Olderrbd[temp]=(UserDataType)(Olderrbd[temp] | temp1);         
   }
   else{
      Olderrbd[temp]=(UserDataType)(Olderrbd[temp] & ~temp1);          
   }

   return(2);     
}




void  __attribute__((section(".usercode"))) ErrorSet(void)
{
   LocalType  temp,temp1,temp2,temp3;
   

   temp=ErrBdNamePt;
   ErrBdNamePt=BDid[CurRcvAdr];
   OnceSaveErrorSet(0);
   ErrBdNamePt=temp;
      
   for(temp2=BefRcvAdr;temp2+1 < CurRcvAdr;temp2++){
      	temp=temp2/8;
      	temp1=temp2%8;      

		temp3=0x01;
		temp1=(temp3 << temp1);
		
      	errbd[temp]=errbd[temp] | temp1;         
   }         
}



void  __attribute__((section(".usercode"))) ErrorBoardSet(void)  
{
   LocalType   vtemp,vtemp1,vtemp2,vtemp3,vtemp4;
   
      if(errtime>ERR_DSP_TIME){
            ErrBdNamePt=0;
            errtime=0;

            vtemp4=errpt;
            do{
               errpt=(errpt+1)% ABS_ADDRESS;
               vtemp=errpt/8;
               vtemp1=errpt%8;
               vtemp3=errbd[vtemp];         
               vtemp2=0x01;
               vtemp2=vtemp2<<vtemp1;          
            }while(!(vtemp2 & vtemp3) && (vtemp4 != errpt) );
      
            if(vtemp2 & vtemp3){
               errbd[vtemp]=errbd[vtemp] & (~vtemp2);         
               vtemp=errpt+1;  
               ErrBdNamePt=BDid[vtemp];
               BdErrCntSeq[ErrBdNamePt]++; 
            }            
      }            
}




void    __attribute__((section(".usercode"))) Com0COMM(UserDataType Absadr,UserDataType Logadr,UserDataType cmd)
{
   RxBuffer[0]=(UserDataType)ENQ;
   
   src=cF_COMPANY;
   HextoASCIIByte();
   RxBuffer[1]=firstdata;            
   RxBuffer[2]=seconddata;            

   src=Logadr;
   HextoASCIIByte();
   RxBuffer[3]=firstdata;   
   RxBuffer[4]=seconddata;   

   src=Absadr;
   HextoASCIIByte();
   RxBuffer[5]=firstdata;   
   RxBuffer[6]=seconddata;               
   
   src=cmd;
   HextoASCIIByte();
   RxBuffer[7]=firstdata;            
   RxBuffer[8]=seconddata;               
}



void    __attribute__((section(".usercode"))) MyDataTx(void)
{         
	LocalType  i,k;

    
	Com0COMM(MAS_A,LOG_ADR,NORMAL);

    RxBuffer[0] = ACK;

	src=0;
	HextoASCIIByte();
	RxBuffer[9]=firstdata;            
	RxBuffer[10]=seconddata;            

	src=0;
	HextoASCIIByte();
	RxBuffer[11]=firstdata;   
	RxBuffer[12]=seconddata;               
   
	src=0;
	HextoASCIIByte();
	RxBuffer[13]=firstdata;            
	RxBuffer[14]=seconddata;            

	k=17;   
   
	for(i=S0_FLOOR; i < mcurfloor ; i++ ){
		src=sRamDArry[i];
		HextoASCIIByte();
		RxBuffer[ k + 0]=firstdata;   
		RxBuffer[ k + 1]=seconddata;
		k=k+2;   
	}

	src= (k-17)/2;
	HextoASCIIByte();   
	RxBuffer[15]=firstdata;
	RxBuffer[16]=seconddata;

	RxBuffer[k+0]=(UserDataType)ETX;
	RxBuffer[k+1]=0;
      

	TXEN=0;  
	Serial();
}


void    __attribute__((section(".usercode"))) Find_Absolute(UserDataType Absadr,UserDataType Logadr,UserDataType cmd)
{                    
	LocalType i,j,k;      

	Com0COMM(Absadr,Logadr,cmd);  
   
    RxBuffer[0]=(UserDataType)ENQ;

	src=LadderData[C_CMDTYPE];
	HextoASCIIByte();
	RxBuffer[9]=firstdata;            
	RxBuffer[10]=seconddata;            

	src=LadderData[C_BASE_MEMORY];
	HextoASCIIByte();
	RxBuffer[11]=firstdata;   
	RxBuffer[12]=seconddata;               
   
	src=LadderData[C_OFFSET_MEMORY];
	HextoASCIIByte();
	RxBuffer[13]=firstdata;            
	RxBuffer[14]=seconddata;            

////////new
    LadderData[C_DATA_CNT]=7;
    src=(11 + LadderData[C_DATA_CNT]);
    HextoASCIIByte();   
    RxBuffer[15]=firstdata;
    RxBuffer[16]=seconddata;
    
    j=17;
    k=0;
    for(i=0;i<(LadderData[C_DATA_CNT] + 10);i++){
        if((New485Ladder[k+0] >= ' ') &&  (New485Ladder[k+0] < '0'))    (New485Ladder[k+0] = New485Ladder[k+0] + 0x80);    
        if((New485Ladder[k+1] >= ' ') &&  (New485Ladder[k+1] < '0'))    (New485Ladder[k+1] = New485Ladder[k+1] + 0x80);    
        RxBuffer[j+0]=New485Ladder[k+0];
        RxBuffer[j+1]=New485Ladder[k+1];
        k=k+2;
        j=j+2;
    }        
	RxBuffer[j+0]=(UserDataType)ETX;
	RxBuffer[j+1]=0;      
	TXEN=0;
	Serial();
}




void  __attribute__((section(".usercode"))) Ram0DataRdWr(void)
{
   LocalType i,j,k;
   
   if((LadderBuf[C_CMD] == READ_DATA) || (LadderBuf[C_CMD] == BIT_READ_DATA)){
      for(i=0;i < LadderBuf[C_DATA_CNT];i++){   
         LadderBuf[C_SAVE_DATA + i] = sRamDArry[LadderBuf[C_OFFSET_MEMORY]+i];                        
      }        
      LadderBuf[C_CMDTYPE]= LadderBuf[C_CMDTYPE] + RET_GOOD;
   }

   else if(LadderBuf[C_CMD] == WRITE_DATA){
      for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
         sRamDArry[LadderBuf[C_OFFSET_MEMORY]+j] = LadderBuf[C_SAVE_DATA+j];
      }              
      LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;      
   }  
   else if(LadderBuf[C_CMD] == BIT_WRITE_DATA){
      i=0;
      for(j=1;j < LadderBuf[C_DATA_CNT];j++){
         k=LadderBuf[C_SAVE_DATA+j];
         if(k){   
            sRamDArry[LadderBuf[C_BASE_MEMORY]+i] = (sRamDArry[LadderBuf[C_BASE_MEMORY]+i] | k);
         }           
         else{             
            sRamDArry[LadderBuf[C_BASE_MEMORY]+i] = (sRamDArry[LadderBuf[C_BASE_MEMORY]+i] & ~LadderBuf[C_OFFSET_MEMORY]);
         }           
         i=i+LadderBuf[C_SAVE_DATA];
      }        
      LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
   }  
   
   if(LadderBuf[C_OFFSET_MEMORY] == ExtCmdFlrONOFF0){
 		ExtCmdFlrONOFFCnt=0;
		AccTimer=0;
	}
}



void  __attribute__((section(".usercode"))) VipCarKeyClr(void)
{
  if(S3_VIP1){
    sRamDArry[mEqualFloor]=(sRamDArry[mEqualFloor] & ~UPDN_READY);
    sRamDArry[mHighFloor] =(sRamDArry[mHighFloor] & ~UPDN_READY);
    sRamDArry[mLowFloor]  =(sRamDArry[mLowFloor] & ~UPDN_READY);
     
    if(!(sRamDArry[mEqualFloor] & CAR_READY))  sRamDArry[mEqualFloor]=0;
    if(!(sRamDArry[mHighFloor] & CAR_READY))  sRamDArry[mHighFloor]=0;	
    if(!(sRamDArry[mLowFloor] & CAR_READY))   sRamDArry[mLowFloor]=0;
  }
}



void  __attribute__((section(".usercode"))) SaveReceiveData(void)
{	
	LadderBuf[C_CMD]=RcvBuf[RCV_CMD];               
   	LadderBuf[C_CMDTYPE]=RcvBuf[RCV_CMDTYPE];             
	LadderBuf[C_BASE_MEMORY]=RcvBuf[RCV_BASE_ADR];              
	LadderBuf[C_OFFSET_MEMORY]=RcvBuf[RCV_OFFS_ADR];          
	LadderBuf[C_DATA_CNT]=RcvBuf[RCV_DATA_CNT];
                        
	LadderBuf[C_SAVE_DATA+0]=RcvBuf[RCV_DATA+0];             
	LadderBuf[C_SAVE_DATA+1]=RcvBuf[RCV_DATA+1];             
	LadderBuf[C_SAVE_DATA+2]=RcvBuf[RCV_DATA+2];             
	LadderBuf[C_SAVE_DATA+3]=RcvBuf[RCV_DATA+3];             
	LadderBuf[C_SAVE_DATA+4]=RcvBuf[RCV_DATA+4];                               



	if(LadderBuf[C_CMDTYPE] == RW_SRAM0_AREA)           Ram0DataRdWr();         
	else if(LadderBuf[C_CMDTYPE] == NEW_FLASH_RD_WR)    NewFlashData();  
          
    

	if((RcvBuf[RCV_ABSADR] == A_LD) || (RcvBuf[RCV_ABSADR] == A_PC)){
        if(RcvBuf[RCV_GROUP] == '0'){
            bPasswardOk=1;
            bAllMenu=1;
			bCompanyCtl=1;
            bUserOn=1;
			bLoaderActive=1;
        }        

		if(RcvBuf[RCV_GROUP] == cF_COMPANY)	bLoaderActive=1;
		
		FhmLoaderTime=0;   	

		LadderData[C_CMD]=LadderBuf[C_CMD];             
		LadderData[C_CMDTYPE]=LadderBuf[C_CMDTYPE];              
		LadderData[C_BASE_MEMORY]=LadderBuf[C_BASE_MEMORY];               
		LadderData[C_OFFSET_MEMORY]=LadderBuf[C_OFFSET_MEMORY];              

		LadderData[C_DATA_CNT]=LadderBuf[C_DATA_CNT];
                        
		LadderData[C_SAVE_DATA+0]=LadderBuf[C_SAVE_DATA+0];               
		LadderData[C_SAVE_DATA+1]=LadderBuf[C_SAVE_DATA+1];               
		LadderData[C_SAVE_DATA+2]=LadderBuf[C_SAVE_DATA+2];               
		LadderData[C_SAVE_DATA+3]=LadderBuf[C_SAVE_DATA+3];               
		LadderData[C_SAVE_DATA+4]=LadderBuf[C_SAVE_DATA+4];                                    
	}

     VipCarKeyClr();
}



//void  __attribute__((section(".usercode"))) SerialCheck(void)
void  __attribute__((section(".usercode"))) HibHbiReqCheck(void)
{

  LocalType tmp;     

	if(ClrCnt > 20){
	
	  if(RxStatus==RX_GOOD){      
	
	    if((RcvBuf[RCV_CMD] == ADR_SET_REC) && (RcvBuf[RCV_LOGADR] == LogAddress+1) && (RcvBuf[RCV_ABSADR] == AbsAddress) ){                     
	
		  LadderData[C_CMDTYPE]=RcvBuf[RCV_CMDTYPE];
	
	      if(LogAddress < 99){
	        for(tmp=0; tmp <= LogAddress;tmp++){
	          if(RcvBuf[RCV_ABSADR] == BDid[tmp]){ 
	            if(BdErrCntSeq[BDid[tmp]] > 5){                                                     
	              Find_Absolute(RcvBuf[RCV_ABSADR],tmp,ADR_SET_ACK);
	            }                     
	            tmp=250;                     
	          }                 
	        }
	
	        if(tmp<250){
	          LogAddress++;
	          Find_Absolute(RcvBuf[RCV_ABSADR],LogAddress,ADR_SET_ACK);
	          BDid[LogAddress]=RcvBuf[RCV_ABSADR];
	
	      	  if((RcvBuf[RCV_ABSADR] == A_CAR1) || (RcvBuf[RCV_ABSADR] == A_CAR1) || (RcvBuf[RCV_ABSADR] == A_CAR3) || (RcvBuf[RCV_ABSADR] == A_CAR4) ){
	              bCarService=1;                            
	          }
	        }               
	      }            
	    }
	    else{      
	      if((RcvBuf[RCV_CMD] == NORMAL) || (RcvBuf[RCV_CMD] == NO_DATA)){
	        BdErrCntSeq[RcvBuf[RCV_ABSADR]]=0;                 
	      }                 
	      else if( (RcvBuf[RCV_CMD] == WRITE_DATA) || (RcvBuf[RCV_CMD] == READ_DATA) || (RcvBuf[RCV_CMD] == LONG_READ_DATA) ||
	               (RcvBuf[RCV_CMD] == BIT_WRITE_DATA) ||  (RcvBuf[RCV_CMD] == BIT_READ_DATA)){           
	          if((RcvBuf[RCV_GROUP] == cF_COMPANY) || (RcvBuf[RCV_GROUP] == '0')){
	            SaveReceiveData();
	          }              
	          BdErrCntSeq[RcvBuf[RCV_ABSADR]]=0;
	      }            
	         
	      CurRcvAdr=RcvBuf[RCV_LOGADR];         
	      ErrorSet();
	      BefRcvAdr=CurRcvAdr;
	      TimeOutBd=CurRcvAdr;         
	      RxStatus=STX_CHK;                        	
	    }
	    
	    SerialLoopMaxTime=0;      
	    if(RxStatus == RX_GOOD)  RxStatus = STX_CHK;	
	  }         
	                           
	  if(TimeOutBd > LogAddressLoop){
	    if(!bFindBoard){          
	      LogAddressLoop=LogAddressLoop+1;
	      CurRcvAdr=LogAddressLoop;
	      ErrorSet();
	      AbsAddress++;
	      if(AbsAddress>ABS_ADDRESS) AbsAddress=1;         
	      Find_Absolute(AbsAddress,LogAddress+1,ADR_SET_SEND);
	      bFindBoard=1;         
	      ExtCmdFlrONOFFCnt++;
	    }
	    else{      	
	      BefRcvAdr=0;
	      CurRcvAdr=0;
	      TimeOutBd=0;
	      MyDataTx();
	      LogAddressLoop=LogAddress;                  
	      bFindBoard=0;                  
	      disp_clk_regs();
	    }                  
	  }  
	           
	  ErrorBoardSet();
	}
	else{
	  if(RxStatus == STX_CHK){
	   		Find_Absolute(MAS_A,LOG_ADR,LOGADR_CLR);  
	 		ClrCnt++;
	  }	
	}	              
  return;
}


UserDataType  __attribute__((section(".usercode"))) Init485_Ladder(void)
{

    RxStatus = STX_CHK;
	
   	for(NoCloseCnt=0;NoCloseCnt<30;NoCloseCnt++){	      
   		Find_Absolute(MAS_A,LOG_ADR,LOGADR_CLR);   

//   		while((RxStatus != STX_CHK)){
		SerialTime = 0;
   		while(SerialTime < 4){
            asm("CLRWDT");
        }

		TXEN=1;  		
		RxCurCnt=0;
      	RxStatus = STX_CHK;

		for(firstdata=0;firstdata<600;firstdata++);

        asm("CLRWDT");

		ClrCnt=30;
   	}
}
#else


unsigned int	Crc;	

void    Crc_Calulate(unsigned int crcdata)
{
	register unsigned int    i;

   Crc=Crc ^ (crcdata & 0x00ff);
   for(i=0;i<=7;i++){
      if( (Crc & 0x0001) == 0x0001)    Crc=(Crc >> 1) ^ 0xA001;
      else Crc=Crc >> 1;
   }
}



///////////////

void  __attribute__((section(".usercode"))) NormalDataReturn_485(void)
{
   	unsigned char   My485Address=0,ThisCmd;
    unsigned int   j,mpm; 

	typedef  union  _long_Type
	{
	    unsigned char byte[4];
	    unsigned int  intger[2];
	    unsigned long long_data; 
	}long_type1;

	long_type1	long_type;


	ThisCmd=RxBuffer[2];

	My485Address=cF_GroupNm;
	My485Address=(My485Address << 3);
	My485Address=(My485Address | cF_LocalNm);

	
	RxBuffer[0]=0xfe;
	RxBuffer[1]=My485Address;
	RxBuffer[2]=0xA3;
	RxBuffer[3]=0x28;
//	RxBuffer[3]=0x58;
		

	RxBuffer[4] =(sRamDArry[S0_FLOOR]        + (unsigned char)(cF_START_FLOOR));
	RxBuffer[5] = sRamDArry[S1_STATE];
	RxBuffer[6] = sRamDArry[S2_STATE];
	RxBuffer[7] = sRamDArry[S3_STATE];
	RxBuffer[8] = sRamDArry[S4_STATE];
	RxBuffer[9] =(sRamDArry[DEST_FLR]        + (unsigned char)(cF_START_FLOOR));
	RxBuffer[10]= sRamDArry[DSP1];
	RxBuffer[11]= sRamDArry[DSP2];


/////////////////////////////////////////////
	j=cF_START_FLOOR;
	
	long_type.byte[0] = sRamDArry[FLR_ON_OFF0];
	long_type.byte[1] = sRamDArry[FLR_ON_OFF1];
	long_type.byte[2] = sRamDArry[FLR_ON_OFF2];
	long_type.byte[3] = sRamDArry[FLR_ON_OFF3];     
	
	long_type.long_data = (long_type.long_data << j);
	
	
	RxBuffer[12]= long_type.byte[0];
	RxBuffer[13]= long_type.byte[1];
	RxBuffer[14]= long_type.byte[2];
	RxBuffer[15]= long_type.byte[3];     
	
	RxBuffer[16]=0;
	RxBuffer[17]=0;
	RxBuffer[18]=0;
	
	if(sRamDArry[mEqualFloor] & UPDN_CAR_READY)	RxBuffer[16]=(sRamDArry[mEqualFloor]      + (unsigned char)(cF_START_FLOOR));
	if(sRamDArry[mHighFloor] & UPDN_CAR_READY)	RxBuffer[17]=(sRamDArry[mHighFloor]       + (unsigned char)(cF_START_FLOOR));
	if(sRamDArry[mLowFloor] & UPDN_CAR_READY)	RxBuffer[18]=(sRamDArry[mLowFloor]        + (unsigned char)(cF_START_FLOOR));
	
	RxBuffer[19]= sRamDArry[mDoor];
//////////////////////////////////////////////////////

	RxBuffer[20]= sRamDArry[mCarOpCl];
	RxBuffer[21]= sRamDArry[mCarKey1];
	RxBuffer[22]= sRamDArry[mCarKey9];
	RxBuffer[23]= sRamDArry[mCarKey17];     
	RxBuffer[24]= sRamDArry[mCarKey25];
	RxBuffer[25]= sRamDArry[mSysStatus];
	RxBuffer[26]= sRamDArry[O_OP];
	RxBuffer[27]= sRamDArry[O_U_W];
/////////////////////////////////////////////

	RxBuffer[28]= sRamDArry[O_Y_0];
	RxBuffer[29]= sRamDArry[I_EMG];
	RxBuffer[30]= sRamDArry[I_SU1];
	RxBuffer[31]= sRamDArry[I_GR];     
	RxBuffer[32]= sRamDArry[I_FIRE];
	RxBuffer[33]=(sRamDArry[mMostLongDst]    + (unsigned char)(cF_START_FLOOR));
	RxBuffer[34]= (unsigned char)(cF_START_FLOOR);
	RxBuffer[35]=(cF_TOPFLR       + (unsigned char)(cF_START_FLOOR));

////////////////////////////////////////////

	mpm=(unsigned int)CurMeterPerMin;
	RxBuffer[36]= (unsigned char)mpm;
	RxBuffer[37]= (unsigned char)(mpm >> 8);
	RxBuffer[38]= sRamDArry[mExtIN0];
	RxBuffer[39]= sRamDArry[I_X_0];     
	RxBuffer[40]= sRamDArry[I_FS0];
	RxBuffer[41]= sRamDArry[mUnKnown26];
	RxBuffer[42]= sRamDArry[mCrtExtMoveFlr];
	RxBuffer[43]= sRamDArry[mCallMe];
	RxBuffer[43]= ThisCmd;

    Crc=0xffff;
    for(j=0;j<(RxBuffer[3]+4);j++){
        Crc_Calulate((unsigned int)RxBuffer[j]);
    }
    RxBuffer[j]=(unsigned char)(Crc & 0x00ff);
    RxBuffer[j+1]=(unsigned char)((Crc >> 8) & 0x00ff);
    RxBuffer[j+2]=0;

	TXEN=0;  
	SerialTime=0;
   	RxCurCnt=0;	
   	RxStatus=TX_SET;
    U1TXREG=RxBuffer[RxCurCnt];
   	RxCurCnt=1;   

}




LocalType __attribute__((section(".usercode"))) HostCommandAct_485(void)
{

    if((RxBuffer[2]    ==   (PC_COMMAND | CMD_PARKING)) && (RxBuffer[3] == 0x00)){
        if(RxBuffer[4] == 0x01) bPC_PRK = 1;
        else                    bPC_PRK = 0;
    	NormalDataReturn_485();    

    }    
    else if((RxBuffer[2]    ==   (PC_COMMAND | CMD_FIRE)) && (RxBuffer[3] == 0x00)){
        if(RxBuffer[4] == 0x01) bPC_FIRE = 1;
        else                    bPC_FIRE = 0;
    	NormalDataReturn_485();    
    }
    else if((RxBuffer[2]    ==   (PC_COMMAND | CMD_FAMILY_SEV)) && (RxBuffer[3] == 0x00)){
        if(RxBuffer[4] == 0x01) bPC_FAMILY = 1;
        else                    bPC_FAMILY = 0;
    	NormalDataReturn_485();    
    }
    else if((RxBuffer[2]    ==   (PC_COMMAND | CMD_CALL_SEV)) && (RxBuffer[3] == 0x00)){
		CrtMoveFlr=(unsigned char)(RxBuffer[4] | CAR_READY);
    	NormalDataReturn_485();    
    }
    else if((RxBuffer[2]    ==   (PC_COMMAND | CMD_EXT_CALL_SEV)) && (RxBuffer[3] == 0x00)){
		sRamDArry[mCrtExtMoveFlr]=(unsigned char)(RxBuffer[4]);
		ExtKeyCnt=3;
    	NormalDataReturn_485();    
    }

}



LocalType __attribute__((section(".usercode"))) HostWriteMyData_485(void)
{
//	if( !bMoveCar ){

		CAN2_Buf[0]=RxBuffer[0];
		CAN2_Buf[1]=RxBuffer[1];
		CAN2_Buf[2]=RxBuffer[2];
		CAN2_Buf[3]=RxBuffer[3];
		CAN2_Buf[4]=RxBuffer[4];
		CAN2_Buf[5]=RxBuffer[5];
		CAN2_Buf[6]=RxBuffer[6];
		CAN2_Buf[7]=RxBuffer[7];


	    if((RxBuffer[2] == (CMD_EVEN_ODD)) && (RxBuffer[3] == 0x00)){
	        Pc_Command();
    		NormalDataReturn_485();    
	    }    
	    else if((RxBuffer[2] == (CMD_MORNING)) && (RxBuffer[3] == 0x00)){
	        Pc_Command();
    		NormalDataReturn_485();    
	    }    
//	}

}


void  __attribute__((section(".usercode"))) CrtReqCheck(void)
{
	unsigned int i,j;

	if((RxStatus==RX_GOOD) && (SerialTime > 3)){
	    Crc=0xffff;
	    for(j=0;j<(RxBuffer[3]+4);j++){
	        Crc_Calulate((unsigned int)RxBuffer[j]);
	    }


		j=(unsigned int)(RxBuffer[RxBuffer[3]+4]);
		i=(unsigned int)(RxBuffer[RxBuffer[3]+5]);
		i=(i << 8);
		j=(j | i);

		if(j == Crc){
			RxBuffer[0]=RxBuffer[2];
			RxBuffer[1]=RxBuffer[3];
			RxBuffer[2]=RxBuffer[4];
			RxBuffer[3]=RxBuffer[5];
			RxBuffer[4]=RxBuffer[6];
			RxBuffer[5]=RxBuffer[7];
			RxBuffer[6]=RxBuffer[8];
			RxBuffer[7]=RxBuffer[9];

		    switch(RxBuffer[0]){
		        case    0x23:
	        		NormalDataReturn_485();
		            break;
		        case    0x24:
		            if(RxBuffer[2] & PC_COMMAND){
		                HostCommandAct_485();             
		            }
		            else{
		                HostWriteMyData_485();             
		            }
		            break;

			}

			if(RxStatus != TX_SET){
				SerialTime=0;
			   	RxCurCnt=0;
			   	RxStatus=STX_CHK;
			}
/*
			TXEN=0;  
			SerialTime=0;
		   	RxCurCnt=0;	
		   	RxStatus=TX_SET;
		    U1TXREG=RxBuffer[RxCurCnt];
		   	RxCurCnt=1;   
*/
		}
		else{
			SerialTime=0;
		   	RxCurCnt=0;
		   	RxStatus=STX_CHK;
		}

//		TXEN=0;  
//		SerialTime=0;
//	   	RxCurCnt=0;
//	   	RxStatus=TX_SET;
//	    U1TXREG=RxBuffer[RxCurCnt];
//	   	RxCurCnt=1;
   
	}
}

#endif


////////////
void  __attribute__((section(".usercode"))) SerialCheck(void)
{
#ifndef		RS485_FOR_CRT	
	HibHbiReqCheck();
#else
	CrtReqCheck();
#endif


	if((RxStatus==TX_SET) && (SerialTime > 2)){
		TXEN=1;  		
		RxCurCnt=0;
      	RxStatus = STX_CHK;
	}

	if(RxStatus != TX_SET){
		TXEN=1;  		
	}
}




