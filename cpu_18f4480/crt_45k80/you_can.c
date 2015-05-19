


#include    <pic18.h>


#include "you_can.h" 
#include "com.h" 
#include "crt_45k80.h" 
#include "MyUtil.h" 
#include "you_can_oldProtocol.h" 



#if defined(CPU65K80)  || defined(CPU45K80)

	#define	TXB0REQ		TXB0CONbits.TXREQ

	#define	RXB0FUL		RXB0CONbits.RXFUL
	#define	RXB0FILHIT0 RXB0CONbits.FILHIT0
	#define	RXB0FILHIT1 RXB0CONbits.FILHIT1
	#define	RXB0FILHIT2 RXB0CONbits.FILHIT2
	#define	RXB0RTRRO 	RXB0CONbits.RXRTRRO

	#define	TXB1REQ		TXB1CONbits.TXREQ
	#define	RXB1FUL		RXB1CONbits.RXFUL
	#define	RXB1FILHIT0 RXB1CONbits.FILHIT0
	#define	RXB1FILHIT1 RXB1CONbits.FILHIT1
	#define	RXB1FILHIT2 RXB1CONbits.FILHIT2
	#define	RXB1RTRRO 	RXB1CONbits.RXRTRRO


	#define	RXB0M0		RXB0CONbits.RXM0
	#define	RXB0M1		RXB0CONbits.RXM1
	#define	RXB0DBEN	RXB0CONbits.RB0DBEN
				


	#define	RXB1M0		RXB1CONbits.RXM0
	#define	RXB1M1		RXB1CONbits.RXM1
	#define	RXB1DBEN	RXB1CONbits.RB1DBEN


	#define	RXB0IF		PIR5bits.RXB0IF
	#define	RXB1IF		PIR5bits.RXB1IF


	#define	RXF0EXIDEN	RXF0SIDLbits.EXIDEN
	#define	RXF1EXIDEN	RXF1SIDLbits.EXIDEN
	#define	RXF2EXIDEN	RXF2SIDLbits.EXIDEN
	#define	RXF3EXIDEN	RXF3SIDLbits.EXIDEN
	#define	RXF4EXIDEN	RXF4SIDLbits.EXIDEN
	#define	RXF5EXIDEN	RXF5SIDLbits.EXIDEN



	#define	TXB0IE		TXBIEbits.TXB0IE
	#define	TXB1IE		TXBIEbits.TXB1IE
	#define	TXB2IE		TXBIEbits.TXB2IE

	#define	RXB0IE		BIE0bits.RXB0IE
	#define	RXB1IE		BIE0bits.RXB1IE


	#define	TXB2REQ		TXB2CONbits.TXREQ

	#define	TXB0RTR		TXB0DLCbits.TXRTR

#endif



unsigned    long    Can1TxEid=0;
unsigned    int     Can1TxSid=0;
unsigned    char    Can1TxDlc=0;
unsigned    char	Can1TxDataTotalCnt=0;
unsigned    char    Can1TxDataTxPointer=0;


unsigned    long    Can1RxEid=0;
unsigned    int     Can1RxSid=0;
unsigned    char    Can1RxDlc=0;
unsigned    char	Can1RxDataTotalCnt=0;
unsigned    char    Can1RxDataRxPointer=0;

unsigned    char    Can1TxBuf[CAN1_MAX_TX_BUF];           
unsigned    char    Can1RxBuf[CAN1_MAX_RX_BUF];           

unsigned    char    Can1ThisRxBuf[8];           


///////////////////////

void Can1PortSetting(void)//------------------------------------------------------------------------
{
   	TRISB3 = 1 ; // CAN RX
   	TRISB2 = 0 ; // CAN TX 
       	
#ifdef		 U_COMPILER		1
	CANCONbits.REQOP = 4 ;// Entry Configration Mode
#else
	REQOP2 = 1 ;// Entry Configration Mode
	REQOP1 = 0 ;
	REQOP0 = 0 ;
#endif

}



void Can1BaudSetting(void)
{
    SEG2PHTS = 1 ;      // Freely programmable
   	SAM      = 1 ;      // Bus Line is sampled three times prior to the sample point

   	SEG2PH2	 = 0 ;      // 2Tq
   	SEG2PH1	 = 0 ;
   	SEG2PH0	 = 1 ;

   	PRSEG2	 = 0 ;      // 3xTq
   	PRSEG1	 = 1 ;
   	PRSEG0	 = 0 ;

   	SEG1PH2	 = 0 ;      // 2Tq
   	SEG1PH1	 = 0 ;
   	SEG1PH0	 = 1 ;


    SJW1    = 0 ;       // 1Tq
    SJW0    = 0 ;


    BRP5    = 0 ;       // Tq = (2x4)/Fosc = (2x4)/8000000 = 1us
	BRP4    = 1 ; 
	BRP3    = 0 ; 
	BRP2    = 0 ;  
	BRP1    = 1 ;  // BRP is setting value 4 when Fosc is 8 Mhz ( tq=0.00000125 )
	BRP0    = 1 ; 

    
    BRP5    = 1 ; // Tq = 0.00000125/2
	BRP4    = 0 ; 
	BRP3    = 0 ; 
	BRP2    = 1 ;  
	BRP1    = 1 ;  
	BRP0    = 1 ; 

}   






void Can1SetFilter(char filter_no, unsigned int sid, unsigned long eid)
{      
    unsigned int uppereid;

    sid     =(sid << 5) & 0xffe0;
    eid     =(eid & 0x0003ffff);
    uppereid=(unsigned int)(eid >> 16);
    sid     =(sid | uppereid);
 
    uppereid =(unsigned int)(eid); 

    switch(filter_no)
    {
    case 0:
      RXF0SIDH  = (unsigned char)(sid >> 8); 
      RXF0SIDL  = (unsigned char)(sid);
      RXF0SIDL  = (RXF0SIDL | 0x08);
      RXF0EIDH  = (unsigned char)(uppereid >> 8);
      RXF0EIDL  = (unsigned char)(uppereid);
      break;
    case 1:
      RXF1SIDH  = (unsigned char)(sid >> 8); 
      RXF1SIDL  = (unsigned char)(sid);
      RXF1SIDL  = (RXF1SIDL | 0x08);
      RXF1EIDH  = (unsigned char)(uppereid >> 8);
      RXF1EIDL  = (unsigned char)(uppereid);
      break;
    case 2:
      RXF2SIDH  = (unsigned char)(sid >> 8); 
      RXF2SIDL  = (unsigned char)(sid);
      RXF2SIDL  = (RXF2SIDL | 0x08);
      RXF2EIDH  = (unsigned char)(uppereid >> 8);
      RXF2EIDL  = (unsigned char)(uppereid);
      break;
    case 3:
      RXF3SIDH  = (unsigned char)(sid >> 8); 
      RXF3SIDL  = (unsigned char)(sid);
      RXF3SIDL  = (RXF3SIDL | 0x08);
      RXF3EIDH  = (unsigned char)(uppereid >> 8);
      RXF3EIDL  = (unsigned char)(uppereid);
      break;
    case 4:
      RXF4SIDH  = (unsigned char)(sid >> 8); 
      RXF4SIDL  = (unsigned char)(sid);
      RXF4SIDL  = (RXF4SIDL | 0x08);
      RXF4EIDH  = (unsigned char)(uppereid >> 8);
      RXF4EIDL  = (unsigned char)(uppereid);
      break;
    case 5:
      RXF5SIDH  = (unsigned char)(sid >> 8); 
      RXF5SIDL  = (unsigned char)(sid);
      RXF5SIDL  = (RXF5SIDL | 0x08);
      RXF5EIDH  = (unsigned char)(uppereid >> 8);
      RXF5EIDL  = (unsigned char)(uppereid);
      break;
    default:
      RXF0SIDH  = (unsigned char)(sid >> 8); 
      RXF0SIDL  = (unsigned char)(sid);
      RXF0SIDL  = (RXF0SIDL | 0x08);
      RXF0EIDH  = (unsigned char)(uppereid >> 8);
      RXF0EIDL  = (unsigned char)(uppereid);
      break;
    }
}



void Can1SetMask(char mask_no, unsigned int sid, unsigned long eid)
{ 
    unsigned int uppereid;

    sid     =(sid << 5) & 0xffe0;
    eid     =(eid & 0x0003ffff);
    uppereid=(unsigned int)(eid >> 16);
    sid     =(sid | uppereid);
    uppereid=(unsigned int)(eid);

    switch(mask_no)
    {
    case 0:
      RXM0SIDH = (unsigned char)(sid >> 8);
      RXM0SIDL = (unsigned char)(sid);
      RXM0EIDH = (unsigned char)(uppereid >> 8);
      RXM0EIDL = (unsigned char)(uppereid);
      break;
    case 1:
      RXM1SIDH = (unsigned char)(sid >> 8);
      RXM1SIDL = (unsigned char)(sid);
      RXM1EIDH = (unsigned char)(uppereid >> 8);
      RXM1EIDL = (unsigned char)(uppereid);
      break;
    default:
      RXM0SIDH = (unsigned char)(sid >> 8);
      RXM0SIDL = (unsigned char)(sid);
      RXM0EIDH = (unsigned char)(uppereid >> 8);
      RXM0EIDL = (unsigned char)(uppereid);
      break;
    }
}





void Can1TxSidEidSet(char MsgFlag,unsigned int sid, unsigned long eid)
{
    unsigned int uppereid;


    sid     =(sid << 5) & 0xffe0;
    eid     =(eid & 0x0003ffff);
    uppereid=(unsigned int)(eid >> 16);
    sid     =(sid | uppereid);
 
    uppereid =(unsigned int)(eid); 

    switch(MsgFlag)
    {
    case 0:
      TXB0SIDH  = (unsigned char)(sid >> 8); 
      TXB0SIDL  = (unsigned char)(sid);
      TXB0SIDL  = (TXB0SIDL | 0x08);
      TXB0EIDH  = (unsigned char)(uppereid >> 8);
      TXB0EIDL  = (unsigned char)(uppereid);
      break;
    case 1:
      TXB1SIDH  = (unsigned char)(sid >> 8); 
      TXB1SIDL  = (unsigned char)(sid);
      TXB1SIDL  = (TXB1SIDL | 0x08);
      TXB1EIDH  = (unsigned char)(uppereid >> 8);
      TXB1EIDL  = (unsigned char)(uppereid);
      break;
    case 2:
      TXB2SIDH  = (unsigned char)(sid >> 8); 
      TXB2SIDL  = (unsigned char)(sid);
      TXB2SIDL  = (TXB2SIDL | 0x08);
      TXB2EIDH  = (unsigned char)(uppereid >> 8);
      TXB2EIDL  = (unsigned char)(uppereid);
      break;
    default:
      TXB0SIDH  = (unsigned char)(sid >> 8); 
      TXB0SIDL  = (unsigned char)(sid);
      TXB0SIDL  = (TXB0SIDL | 0x08);
      TXB0EIDH  = (unsigned char)(uppereid >> 8);
      TXB0EIDL  = (unsigned char)(uppereid);
      break;
    }
}


void Can1DlcSet(char MsgFlag,unsigned char DataCnt)
{
    switch(MsgFlag)
    {
    case 0:      
      TXB0DLC  = DataCnt; 
      break;
    case 1:
      TXB1DLC  = DataCnt; 
      break;
    case 2:
      TXB2DLC  = DataCnt; 
      break;
    default:
      TXB0DLC  = DataCnt; 
      break;
    }
}




void    Can1RxSidEidArrary(void)
{

    unsigned int  itmp1,itmp2;
    unsigned long ltmp1;
    unsigned char TmpRcvAdr;

    itmp1=(RXB0SIDH << 8);
    itmp2=RXB0SIDL;
    Can1RxSid=(unsigned int)(itmp1 | itmp2);
    Can1RxSid=(Can1RxSid >> 5);
 
   
    ltmp1=(unsigned long)(RXB0SIDL & 0x03);
    Can1RxEid=(ltmp1 << 16);

    ltmp1=(unsigned long)(RXB0EIDH);
    ltmp1=(ltmp1 << 8);
    Can1RxEid=(Can1RxEid | ltmp1);

    ltmp1=(unsigned long)(RXB0EIDL);
    Can1RxEid=(Can1RxEid | ltmp1);

	Can1RxDlc=(RXB0DLC & 0x0f);

}



void    Can1FilterSet(void)
{    
    Can1SetFilter(0,Can1RxSid,Can1RxEid);
    Can1SetFilter(1,Can1RxSid,Can1RxEid);
    Can1SetFilter(2,Can1RxSid,Can1RxEid);
    Can1SetFilter(3,Can1RxSid,Can1RxEid);
    Can1SetFilter(4,Can1RxSid,Can1RxEid);
    Can1SetFilter(5,Can1RxSid,Can1RxEid);
}


void    Can1MaskSet(void)       //new
{    
    Can1SetMask(0,Can1RxSid,Can1RxEid);
    Can1SetMask(1,Can1RxSid,Can1RxEid);
}






unsigned int   Can1ReceiveData(void)
{
	unsigned char	j,AckHost;
	unsigned int	hostnm;
	unsigned char	tmpbuf[10];

	unsigned char	tmpeid;

	unsigned char	RcvSrcAdr;
	unsigned char	RcvDectAdr;


	tmpeid=(unsigned char)(Can1RxEid >> 8);
	Can1RxDataRxPointer= ((tmpeid & 0x0f) * 8);

	for(j=0;j<Can1RxDlc;j++){
  		Can1RxBuf[0    + Can1RxDataRxPointer]=Can1ThisRxBuf[j];
		Can1RxDataRxPointer++;
	}

	if(tmpeid & 0x10){
		if( (Can1RxBuf[1]+2) == Can1RxDataRxPointer){
      		for(j=0;j<Can1RxDataRxPointer;j++)	Com1TxBuffer[j+2]=Can1RxBuf[j];

			RcvDectAdr=0;
			RcvSrcAdr=0;
			if(Can1RxEid & 0x4000)	RcvSrcAdr=(RcvSrcAdr | 0x01);	
			if(Can1RxEid & 0x8000)	RcvSrcAdr=(RcvSrcAdr | 0x02);	
			if(Can1RxEid & 0x10000)	RcvSrcAdr=(RcvSrcAdr | 0x04);	

			if(Can1RxSid & 0x80)	RcvSrcAdr=(RcvSrcAdr | 0x08);	
			if(Can1RxSid & 0x100)	RcvSrcAdr=(RcvSrcAdr | 0x10);	
			if(Can1RxSid & 0x200)	RcvSrcAdr=(RcvSrcAdr | 0x20);	
			if(Can1RxSid & 0x400)	RcvSrcAdr=(RcvSrcAdr | 0x40);	

			if(Can1RxEid & 0x20000)	RcvSrcAdr=(RcvSrcAdr | 0x80);	

			RcvDectAdr=(unsigned char)Can1RxEid;	

			Com1TxBuffer[0]= RcvDectAdr;
			Com1TxBuffer[1]= RcvSrcAdr;

 			Com1TxCnt=(Can1RxDataRxPointer+2);
			
			Crc=0xffff;
			for(j=0;j<(Com1TxCnt);j++)	Crc_Calulate(Com1TxBuffer[j]);


			Com1TxBuffer[j]=(unsigned char)(Crc & 0x00ff);
			Com1TxBuffer[j+1]=(unsigned char)((Crc & 0xff00) >> 8);

   			Com1TxThisPt=0;
 			Com1TxCnt=(Com1TxCnt+2);
			Com1TxStart();			
		}	
		else{
			Can1RxDataRxPointer=0;
		}				
	}
	return(0);
}


void    Can1Interrupt(void)
{
    unsigned int i,j,hostnm;
    unsigned char *ptr;

    if(IRXIF){
        IRXIF=0;
    }
    else if(WAKIF){
        WAKIF=0;
    }
    else if(ERRIF){
        ERRIF=0;
        if(RXB0OVFL){
            RXB0OVFL=0;
        }  
        if(RXB1OVFL){
            RXB1OVFL=0;
        }  
        if(TXBO){
            TXBO=0;
        }  
        if(TXBP){
            TXBP=0;    
        }  
        if(RXBP){
            RXBP=0;
        }  
        if(TXWARN){
            TXWARN=0;
        }  
        if(RXWARN){
            RXWARN=0;
        }  
        if(EWARN){
            EWARN=0;
        }  
        COMSTAT=0;
    }
    else if(RXB1IF){
        RXB1IF=0;
    }

    else if(RXB0IF){

		Can1RxSidEidArrary();
        ptr = (unsigned char*)&RXB0D0 ;                          			
        for(i=0;i<Can1RxDlc;i++)	Can1ThisRxBuf[i]=ptr[i];

		Can1ReceiveData();
Can1ReceiveData_oldProtocol();
        RXB0IF=0;
        RXB0FUL=0;
    }    
}





void Can1Init(void)
{
    unsigned int i;
     
    Can1PortSetting();   
    Can1BaudSetting();
    
    
	ENDRHI = 1 ; // CANTX pin will drive when recessive
    CANCAP = 0 ; // enable CAN Capture mode
    WAKFIL = 0 ; // CAN bus line filter is not used for wake-up


/***********************************************/ 	
	RXB0FUL     = 0 ;   // clear receive buffer0 full flag
	RXB0M1      = 1 ;   // Receive extended identifier valid messages
	RXB0M0      = 0 ;   // Receive extended identifier valid messages
	RXB0DBEN    = 0 ;   // no data write Receive buffer0 to receive buffer1 
	RXB0FILHIT0 = 0;    // acceptance filter0
	RXB0RTRRO   = 0 ;   // No remote transfer request(read only) 
    JTOFF       = 0 ;   // (read only)
/***********************************************/ 	


/***********************************************/ 	
	RXB1FUL     = 0 ;
	RXB1M1      = 1 ; // Receive extended identifier valid messages 
	RXB1M0      = 0 ; 
	RXB1FILHIT2 = 0 ; //filter2
	RXB1FILHIT1 = 1 ;
	RXB1FILHIT0 = 0 ;
	RXB1RTRRO   = 0 ; // No remote transfer request(read Only) 
/***********************************************/ 	

    RXF0EXIDEN=1;
    RXF1EXIDEN=1;
    RXF2EXIDEN=1;
    RXF3EXIDEN=1;
    RXF4EXIDEN=1;
    RXF5EXIDEN=1;


    Can1FilterSet();
    Can1MaskSet();

    TXB0RTR  =0;

    TXB0REQ = 0 ;   //
   	TXB1REQ = 0 ;
    TXB2REQ = 0 ;


    RXB1IP=0;

#if  defined(CPU65K80)   ||  defined(CPU45K80)
IPR5=0;
#else        
IPR3=0;
#endif


    IRXIE       =0;
    WAKIE       =0;
    ERRIE       =1;
    TXB2IE      =0;
    TXB1IE      =0;
    TXB0IE      =0;
    RXB1IE      =1;
    RXB0IE      =1;



#ifdef		 U_COMPILER		1
	CANCONbits.REQOP = 0 ;// Entry Configration Mode
#else
	REQOP2 = 0 ;// Entry Configration Mode
	REQOP1 = 0 ;
	REQOP0 = 0 ;
#endif


}//--------------------------------------------------------------------------------------------------




void  Can1TxDataLoad(unsigned char pt)
{		
	TXB0D0=Can1TxBuf[pt+0];           
	TXB0D1=Can1TxBuf[pt+1];
	TXB0D2=Can1TxBuf[pt+2];
	TXB0D3=Can1TxBuf[pt+3];
	TXB0D4=Can1TxBuf[pt+4];
	TXB0D5=Can1TxBuf[pt+5];
	TXB0D6=Can1TxBuf[pt+6];
	TXB0D7=Can1TxBuf[pt+7];
}


unsigned char	Can1TxData(unsigned char i)
{

	unsigned char ret;

	ret=1;


    if(!TXB0REQ){

        Can1DlcSet(0,Can1TxDlc);
        Can1TxSidEidSet(0,Can1TxSid,Can1TxEid);
		Can1TxDataLoad(i);

        IPR3=0;
        TXB0IP=1;

        TXB0REQ = 1 ; // 전송 요구 비트 셋

//		bCan1TxStart=0;                    
//		bCan1RxAll=0;                    

		ret=0;       

    }

	return(ret);
}




////////////////////////////////





unsigned char  Can1Check(void)
{
	unsigned int  tmpsid1,tmpsid2;
	unsigned long last_data=0,dataseq=0;
	
	if(Can1TxDataTxPointer >= Can1TxDataTotalCnt)	return(0);

	tmpsid1= HOST_COMPANY;
	tmpsid2=((Can1TxBuf[0] & 0x78) << 4);
	tmpsid1=(tmpsid1 | tmpsid2);

	
	Can1TxSid=(unsigned int)(tmpsid1);
	Can1TxEid=0xfe;
	if(Can1TxBuf[0] & 0x01)	Can1TxEid=(Can1TxEid | 0x4000);	
	if(Can1TxBuf[0] & 0x02)	Can1TxEid=(Can1TxEid | 0x8000);	
	if(Can1TxBuf[0] & 0x04)	Can1TxEid=(Can1TxEid | 0x10000);	
	if(Can1TxBuf[0] & 0x80)	Can1TxEid=(Can1TxEid | 0x20000);	

	Can1TxDlc=(Can1TxDataTotalCnt-Can1TxDataTxPointer);
	
	dataseq=(Can1TxDataTxPointer / 8);	

	dataseq=(dataseq << 8);

	if( Can1TxDlc <= 8){
		last_data=0x1000;
	}
	else	Can1TxDlc=8;
	
	Can1TxEid=(Can1TxEid | dataseq);
	Can1TxEid=(Can1TxEid | last_data);

	
	if( !Can1TxData(Can1TxDataTxPointer)){
		Can1TxDataTxPointer=(Can1TxDataTxPointer + Can1TxDlc);
		if( (last_data>0)){
			Can1TxDataTxPointer=0;
			Can1TxDataTotalCnt=0;
		}
	}
	return(0);                      
}
