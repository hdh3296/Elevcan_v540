

#include    <pic18.h>


#include "you_can.h" 
#include "com.h" 
#include "crt_45k80.h" 
#include "you_can_oldProtocol.h" 
#include "MyUtil.h" 


unsigned    char    Can1RxBuf_old[90];           


unsigned int   LoadTxBuffer_oldProtocol(void)
{
	unsigned char	j,AckHost;
	unsigned int	hostnm;
	unsigned char	tmpbuf[10];

	unsigned char	tmpeid;

	unsigned char	RcvSrcAdr;
	unsigned char	RcvDectAdr;


//		if( (Can1RxBuf[1]+2) == Can1RxDataRxPointer){
//      		for(j=0;j<Can1RxDataRxPointer;j++)	Com1TxBuffer[j+2]=Can1RxBuf_old[j];
      		for(j=0;j<(Can1RxBuf_old[0]);j++)	Com1TxBuffer[j+3]=Can1RxBuf_old[j];

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

//			Com1TxBuffer[0]= RcvDectAdr;
			Com1TxBuffer[0]= 0xfe;
			Com1TxBuffer[1]= RcvSrcAdr;
			Com1TxBuffer[2]= Com1RxBuffer[2]+ 0x80;

// 			Com1TxCnt=(Can1RxDataRxPointer+2);
 			Com1TxCnt=(Can1RxBuf_old[0]+4);
			
			Crc=0xffff;
			for(j=0;j<(Com1TxCnt);j++)	Crc_Calulate(Com1TxBuffer[j]);


			Com1TxBuffer[j]=(unsigned char)(Crc & 0x00ff);
			Com1TxBuffer[j+1]=(unsigned char)((Crc & 0xff00) >> 8);

   			Com1TxThisPt=0;
 			Com1TxCnt=(Com1TxCnt+2);
			Com1TxStart();			
//	}

	return(0);
}





unsigned int   Can1ReceiveData_oldProtocol(void)
{
	unsigned char 	j,i;
	unsigned char	hostnm;
	unsigned char	RcvSrcAdr=0;

	if( (Com1RxBuffer[2] == 0x23) || (Com1RxBuffer[2] == 0x24)){                                     		
		if(Can1RxEid & HOST_BOARD){            
			if(Can1RxEid & 0x4000)	RcvSrcAdr=(RcvSrcAdr | 0x01);	
			if(Can1RxEid & 0x8000)	RcvSrcAdr=(RcvSrcAdr | 0x02);	
			if(Can1RxEid & 0x10000)	RcvSrcAdr=(RcvSrcAdr | 0x04);	
	
			if(Can1RxSid & 0x80)	RcvSrcAdr=(RcvSrcAdr | 0x08);	
			if(Can1RxSid & 0x100)	RcvSrcAdr=(RcvSrcAdr | 0x10);	
			if(Can1RxSid & 0x200)	RcvSrcAdr=(RcvSrcAdr | 0x20);	
			if(Can1RxSid & 0x400)	RcvSrcAdr=(RcvSrcAdr | 0x40);	
	
			if(RcvSrcAdr == Com1RxBuffer[0]){                                     		
				j=(unsigned char)(Can1RxEid & 0x0f);	
				if(j == HOST_LAST_DATA)	j=4;		
				j=(j * 8);
				hostnm = j;
				for(i=0;i<Can1RxDlc;i++)	Can1RxBuf_old[hostnm+i+1]=Can1ThisRxBuf[i];
		
				if(j==32){
					Can1RxBuf_old[0]=TX_DATA_CNT;
					LoadTxBuffer_oldProtocol();
				}
			}
		}
	}
	return(0);
}