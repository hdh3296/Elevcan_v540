


#include    <pic18.h>

#include        "iodef.h"
#include        "fontout.h"
#include        "comdata.h"
#include        "esdots.h"
#include        "keysort.h"
#include        "setup.h"
#include        "..\..\system_com\memory_map.h"

extern	bit	bDoorOpenWaitOn;

const   unsigned        char    OVL[]={
   0x00,0x00,
   0x3E,0x41,0x41,0x41,0x3E, // O  31
   0x00, 
   0x1F,0x20,0x40,0x20,0x1F, // V  38
   0x00,
   0x7F,0x49,0x49,0x49,0x41, // E  21
   0x00,
   0x7F,0x09,0x19,0x29,0x46, // R  30
   0x00,    
   0x7F,0x40,0x40,0x40,0x40, // L  28
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, // O  31
   0x00, 
   0x7E,0x11,0x11,0x11,0x7E, // A  17
   0x00,   
   0x7F,0x41,0x41,0x22,0x1C, // D  20
   0x00,0x00,0x00 
};


const   unsigned        char    FULL[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  // F
   0x00,   
   0x3F,0x40,0x40,0x40,0x3F,  // U  37
   0x00,
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,0x00,0x00 
};


const   unsigned        char    STOP1[]={
   0x00,0x00,
   0x46,0x49,0x49,0x49,0x31, // S  35
   0x00,   
   0x01,0x01,0x7F,0x01,0x01, // T  36
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, // O  31
   0x00,
   0x7F,0x09,0x09,0x09,0x06, // P  32
   0x00,0x00,0x00 
};

const   unsigned        char    FIRE[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  //F
   0x00,   
   0x00,0x41,0x7F,0x41,0x00,  //I  25
   0x00,
   0x7F,0x09,0x19,0x29,0x46,  //R  30
   0x00,
   0x7F,0x49,0x49,0x49,0x41,  //E  21
   0x00,0x00,0x00 
};

const   unsigned        char    EMG[]={
   0x00,0x00,
   0x7F,0x49,0x49,0x49,0x41, // E  21
   0x00,   
   0x7F,0x02,0x0C,0x02,0x7F, // M  29
   0x00,
   0x3E,0x41,0x49,0x49,0x7A, // G  23
   0x00,    
   0x00,0x00,0x00,0x00,0x00,  // blanck  
   0x00,0x00,0x00 
};

const   unsigned        char    INS[]={
   0x00,0x00,
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00, 
   0x7F,0x04,0x08,0x10,0x7F,  // N  30
   0x00, 
   0x46,0x49,0x49,0x49,0x31,  // S  35
   0x00,    
   0x00,0x00,0x00,0x00,0x00,  // blanck  
   0x00,0x00,0x00 
};


/*
*/

const   unsigned        char    PARKING[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x06,  // P  25
   0x00,   
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00,   
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  // K  35
   0x00, 
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00, 
   0x7F,0x04,0x08,0x10,0x7F,  // N  30
   0x00,    
   0x3E,0x41,0x49,0x49,0x7A,  // G  23
   0x00,    
   0x00,0x00,0x00,0x00,0x00,  // blanck  
   0x00,0x00,0x00 
};


bit	bErrorCar; 

#ifdef	ONE_DSP
unsigned char  tmpbf[22];;
#endif


void    CompanyChk(unsigned char id)        
{
    unsigned int    IdPt;
    unsigned char   TmpCompany;

//    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
	IdPt=IsBufferPt(id);
    
    if(!MaskSetBit){
       if((RcvBuf[IdPt+DSP1] == 'C') && (RcvBuf[IdPt+DSP2] == 'M') && !(RcvBuf[IdPt+1] & S1_AUTO))  {
	        TmpCompany=(unsigned char)RxSidBuffer;
			if(TmpCompany != Company){ 
	            Company=TmpCompany;
	            CmpSetBit=1;
			}      
        }
    }
}



unsigned char   Lamp(unsigned char id)
{
    unsigned int    IdPt;


#ifdef	__COUNT_CAR
    unsigned char   f_dsp,s_dsp;
#endif
   
//    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
	IdPt=IsBufferPt(id);
    
    FDsp=0;

    HostCallMe=0;
    if(CallMeAdr == RcvBuf[IdPt + SL_mCallMe])  HostCallMe=1;


#if  defined(__TYPE_HIB_HPI)   ||  defined(__TYPE_ES15)
	if(RcvBuf[IdPt+SL_mCrtExtMoveFlr] & UP_READY){
		if((RcvBuf[IdPt+SL_mCrtExtMoveFlr] & (~UPDN_READY)) == MyAddress){
			UpKeyBit=1;
			UpButtonTime=10;
		}
	}

	if(RcvBuf[IdPt+SL_mCrtExtMoveFlr] & DN_READY){
		if((RcvBuf[IdPt+SL_mCrtExtMoveFlr] & (~UPDN_READY)) == MyAddress){
			DnKeyBit=1;
			DnButtonTime=10;
		}
	}
#endif


/*
    if((RcvBuf[IdPt+DSP1] == 'J') && (RcvBuf[IdPt+DSP2] == 'D') && !(RcvBuf[IdPt+1] & S1_AUTO))	SetupBit=1;
    else                                                                                        SetupBit=0;      

    if(SetupBit)    return(0);
*/

    TopFloor=RcvBuf[IdPt + SL_mTopFlr];

    CurFloor=RcvBuf[IdPt];


#ifdef	CARD_KEY
	if((RcvBuf[IdPt + 35] & 0x08))		bCardKeyValid=0;
	else									bCardKeyValid=1;
#endif



 
////////////////dot type dsp hib,hpi////////////////////////////////////////////
#if defined(__DSP_DOT)
    if((CurFloor > BefCurFloor) || (CurFloor < BefCurFloor)){
        FloorChange=1;   
        BefCurFloor=CurFloor;
////////////////////////////
#ifndef	ONE_DSP		
		shift=0;
#endif

    }

    Floor_Char_load(0,RcvBuf[IdPt+DSP1],RcvBuf[IdPt+DSP2]);



#ifdef	__COUNT_CAR
	f_dsp=RcvBuf[MyAddress-1];
	s_dsp=(f_dsp % 10) + '0';
	f_dsp=(f_dsp / 10) + '0';
    Floor_Char_load(0,f_dsp,s_dsp);
#endif
////////////////dot type es15////////////////////////////////////////////
#elif defined(__TYPE_ES15)

#if defined(__TYPE_DIRECT)

	switch(RcvBuf[IdPt])
	{
		case	1: // 1층
			BCD1_LAMP=0; // M0
			BCD2_LAMP=0; // M1
			BCD3_LAMP=0; // M2
			BCD4_LAMP=0; // M3
			break;
		case	2: // 2층
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=0;
			BCD4_LAMP=0;
			break;
		case	3:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=0;
			break;
		case	4:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=0;
			break;
		case	5:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	6:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	7:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	8:
			BCD1_LAMP=0;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	9:
			BCD1_LAMP=0;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	10:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	11:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	12:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	13:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	14:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	15:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	16:
			BCD1_LAMP=0;
			BCD2_LAMP=0;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
	}	

	//Segment not dispaly  	
    SEG_E=0;        	
    SEG_F=Fire;        	 
    SEG_G1=OverLoad;       	 
    SEG_G2=1; // 24V 전원 공급 용.(n24) 
	/*---> FULL 은 기본적으로  FULL 접점에서 출력 나온다. <---*/

/*
	DOOR_OPEN_LAMP= !Open;
	PARKING_LAMP= !Parking;
	MANUAL_LAMP=  !Auto;
	EMG_LAMP_B=   Emg;
	EMG_LAMP  =   !Emg;
*/
#else


   if(RcvBuf[IdPt+DSP1] == 'B')      dsplamp0 = 0x1f;   
   else if(RcvBuf[IdPt+DSP1] == '1') dsplamp0 = 0x06;
   else if(RcvBuf[IdPt+DSP1] == '2') dsplamp0 = 0x0b;
   else if(RcvBuf[IdPt+DSP1] == '3') dsplamp0 = 0x07;
   else                              dsplamp0 = 0x0;
   
    BefCurFloor=(P2 & 0xe0);
    BefCurFloor=(dsplamp0 | BefCurFloor);
    P2=BefCurFloor;

   BefCurFloor=RcvBuf[IdPt+DSP2] - '0';
   dsplamp1=seg0[BefCurFloor];
   if((dsplamp0==0) && (BefCurFloor==1)){
      dsplamp1=0x30;
   }
   else if(RcvBuf[IdPt+DSP2] == 'F'){
      dsplamp1=F_SEG;
   }

   if((RcvBuf[IdPt+3] & S3_PARKING)){
        dsplamp0 = 0x0;
        dsplamp1=P_SEG;
   }


   P0=dsplamp1;





/*
	switch(RcvBuf[IdPt])
	{
		case	1:
			dsplamp1=0x01;
			break;
		case	2:
			dsplamp1=0x02;
			break;
		case	3:
			dsplamp1=0x04;
			break;
		case	4:
			dsplamp1=0x08;
			break;
		case	5:
			dsplamp1=0x10;
			break;
		case	6:
			dsplamp1=0x20;
			break;
		case	7:
			dsplamp1=0x40;
			break;
	}	
*/




/*
	dsplamp1=RcvBuf[IdPt];


   	if((RcvBuf[IdPt+2] & S2_FIRE))          dsplamp1=(dsplamp1 | 0x20);
   	if((RcvBuf[IdPt+3] & S3_PARKING))       dsplamp1=(dsplamp1 | 0x40);
   	if((RcvBuf[IdPt+3] & S3_SHIFT))         dsplamp1=(dsplamp1 | 0x80);
	P0=dsplamp1;


	dsplamp0 = 0x0;

	if((RcvBuf[IdPt+3] 	& S3_PARKING))      dsplamp0=(dsplamp0 | 0x10); //parking
	if(RcvBuf[IdPt+3] 	& S3_STOP)          dsplamp0=(dsplamp0 | 0x02); //water
	if(RcvBuf[IdPt + 24] & 0x20)      		dsplamp0=(dsplamp0 | 0x04); //error  


    if((RcvBuf[IdPt+3] & S3_OPEN_SUB) && (RcvBuf[IdPt+2] 	& S2_FIRE))	dsplamp0=(dsplamp0 | 0x01); //fire      
    if((RcvBuf[IdPt+1] & S1_OPEN)     && (RcvBuf[IdPt+2] 	& S2_FIRE))	dsplamp0=(dsplamp0 | 0x01); //fire      


    BefCurFloor=(P2 & 0xe0);
    BefCurFloor=(dsplamp0 | BefCurFloor);
    P2=BefCurFloor;
*/

#endif

//	if(RcvBuf[IdPt + 24] & 0x20)      		FULL_LAMP=1; //error
//	else									FULL_LAMP=0;					  

   if(RcvBuf[IdPt+3] & S3_FULL)             FULL_LAMP=1;
   else                                     FULL_LAMP=0;

   if(RcvBuf[IdPt+1] & S1_UP)               UP_LAMP=1;
   else                                     UP_LAMP=0;

   if(RcvBuf[IdPt+2] & S2_DN)               DN_LAMP=1;
   else                                     DN_LAMP=0;

#else
    #error Not Select Board Dsplay Type -- error
#endif



#ifndef	__COUNT_CAR

    Open=0;

	if(bIamXSubDoor){
        if((RcvBuf[IdPt+3] & S3_OPEN_SUB))  Open=1;   
    }
    else{
        if(RcvBuf[IdPt+1] & S1_OPEN)        Open=1;   
    }    


   Close=0;
   if((RcvBuf[IdPt+1] & S1_CLOSE)){
      Close=1;   
   }


   CarMove=0;
   if(RcvBuf[IdPt+2] & S2_CAR_MOVE)         CarMove=1;






#ifdef	CPU65K80
#ifndef __TYPE_CAR      
   USER_LAMP3=0;
   if(RcvBuf[IdPt+4] & S4_HALLLANTERN_UP)        USER_LAMP3=1;

   USER_LAMP4=0;
   if(RcvBuf[IdPt+4] & S4_HALLLANTERN_DN)        USER_LAMP4=1;
#endif
#endif


   UpMove=0;
   if(RcvBuf[IdPt+1] & S1_UP)               UpMove=1;

   DnMove=0;
   if(RcvBuf[IdPt+2] & S2_DN)               DnMove=1;

   Vip=0;
   if((RcvBuf[IdPt+3] & S3_VIP))            Vip=1;

   Parking=0;
   if((RcvBuf[IdPt+3] & S3_PARKING))        Parking=1;

   ShiftOn=0;
   if((RcvBuf[IdPt+3] & S3_SHIFT))          ShiftOn=1;
   
   Fire=0;
   if(RcvBuf[IdPt+2] & S2_FIRE)             Fire=1;

   KeyClrExt=0;
   if(RcvBuf[IdPt+2] & S2_EXT_BUT_CLR)      KeyClrExt=1;

   KeyClr=0;
   if(RcvBuf[IdPt+2] & S2_CAR_BUT_CLR)      KeyClr=1;

   
	Emg=0;
   if(RcvBuf[IdPt+1] & S1_EMG)              Emg=1;

/*
   StopBit=0;
   if((RcvBuf[IdPt+3] & S3_STOP)&& (bDoorOpenWaitOn))             StopBit=1;
*/

   StopBit=0;
   if(RcvBuf[IdPt+3] & S3_STOP)             StopBit=1;

	CurKey=0;
   if(RcvBuf[IdPt+3] & S3_CURKEY)           CurKey=1;
         
	Auto=0;
   if(RcvBuf[IdPt+1] & S1_AUTO)             Auto=1;

	OverLoad=0;
   if(RcvBuf[IdPt+1] & S1_OVERLOAD)         OverLoad=1;

	Full=0;
   	if(RcvBuf[IdPt+3] & S3_FULL)             Full=1;

	bErrorCar=0;
   	if(RcvBuf[IdPt + SL_mSysStatus] < 25)       bErrorCar=1;
	if( !Auto)									bErrorCar=1;


#ifdef __TYPE_CAR      
   AUTO_LAMP=OverLoad;

   MANUAL_LAMP=0;
   if(RcvBuf[IdPt+1] & S1_MANUAL)           MANUAL_LAMP=1;

/*
	if(bErrorCar){
   		AUTO_LAMP=1;
   		MANUAL_LAMP=1;
	}
	else{
   		AUTO_LAMP=0;
   		MANUAL_LAMP=0;
	}
*/

#else      
   AUTO_LAMP=0;
   if(RcvBuf[IdPt+2] & S2_LAMP_USER)        AUTO_LAMP=1;

   MANUAL_LAMP=0;
   if(RcvBuf[IdPt+1] & S1_MANUAL)           MANUAL_LAMP=1;
#endif

#else
    Open=0;
    Close=1;   
	CarMove=0;
	AUTO_LAMP=0;
   	MANUAL_LAMP=0;
  	UpMove=0;
   	DnMove=0;
	Vip=0;
   	Parking=0;
   	ShiftOn=0;   
   	Fire=0;
   	KeyClrExt=0;
   	KeyClr=0;   
	Emg=0;
   	StopBit=0;
	CurKey=0;         
	Auto=1;
	OverLoad=0;
	Full=0;
#endif


#if defined(__TYPE_CAR)
   OpenLampSet=0;
   if(RcvBuf[IdPt+2] & S2_OPEN_LAMP_ON)      OpenLampSet=1;
#endif

    return(0);

}







#ifndef	ONE_DSP

void  ArrowUpDown(void)
{
   	unsigned char  i,j,k;

   if(!ShiftOn){
      for(i=11;i<=15;i++){
         shiftDataBuf[i]=DspBuf[i];
      }              
      Arrowshift=0; 
   }
   
   else{
      if(UpMove || DnMove){
         Arrowshift=(Arrowshift + 1)%11;
         if(Arrowshift<8){
            k=(7 - Arrowshift);
            for(i=11;i<=15;i++){
				if(UpMove)	j=(DspBuf[i] << k);
				else 		j=(DspBuf[i] >> k);
               shiftDataBuf[i]=j;           
            }
         }
      }         
      else{
         for(i=11;i<=15;i++){
            shiftDataBuf[i]=DspBuf[i];
         }              
         Arrowshift=0;
      }             
   }
}

#endif




#ifndef	ONE_DSP
void  ShiftData(void)
{


   unsigned char  i;

#ifndef	__COUNT_CAR
   unsigned char  j,k,l;
  
/* 
   if(Emg || !Auto){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
			if(Emg)			shiftDataBuf[i]=EMG[j];
			else if(!Auto)	shiftDataBuf[i]=INS[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }

   else if(Fire || StopBit || Full || Emg || !Auto){
*/

   if(Fire || StopBit || Full || Emg || !Auto || OverLoad || Parking){
   		if(Fire || StopBit || Full || Emg || !Auto){
			  k=39;
		}
   		else if(OverLoad || Parking){  
			  k=63;
		}

		l=(k-11);

      	shift=(shift+1)%k;            
      	j=shift;
      	for(i=0;i<=10;i++){
         	if(j< l){ 
				if(Emg)				shiftDataBuf[i]=EMG[j];
				else if(Parking)	shiftDataBuf[i]=PARKING[j];
				else if(!Auto)		shiftDataBuf[i]=INS[j];
				else if(Fire)		shiftDataBuf[i]=FIRE[j];
				else if(StopBit)	shiftDataBuf[i]=STOP1[j];
				else if(Full)		shiftDataBuf[i]=FULL[j];
				else if(OverLoad)	shiftDataBuf[i]=OVL[j];

            	j++;            
         	}
         	else{
            	shiftDataBuf[i]=DspBuf[j- l];
            	j++;  
            	if(j>(k-1)) j=0;                   
         	}            
      	}
      	ManualToggle=1;
   	}



/*   
   else if(StopBit){
      shift=(shift+1)%39;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<28){ 
            shiftDataBuf[i]=STOP1[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-28];
            j++;  
            if(j>38) j=0;                   
         }            
      }
      ManualToggle=1;
   }
   
   else if(Full){
      shift=(shift+1)%39;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<28){ 
            shiftDataBuf[i]=FULL[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-28];
            j++;  
            if(j>38) j=0;                   
         }            
      }
      ManualToggle=1;
   }
*/
      
//   else if(Water){
//      shift=(shift+1)%45;            
//      j=shift;
//      for(i=0;i<=10;i++){
//         if(j<34){ 
//            shiftDataBuf[i]=WATER[j];
//            j++;            
 //        }
 //        else{
 //           shiftDataBuf[i]=DspBuf[j-34];
//            j++;  
//            if(j>44) j=0;                   
//         }            
//      }
//      ManualToggle=1;
 //  }   

   
/*
   else if(Parking){
      shift=(shift+1)%57;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<46){ 
            shiftDataBuf[i]=PARKING[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-46];
            j++;  
            if(j>56) j=0;                   
         }            
      }
      ManualToggle=1;
   }
*/   

/*
   else if(OverLoad || Parking){  
      shift=(shift+1)%63;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<52){ 
			if(Parking)			shiftDataBuf[i]=PARKING[j];
			else if(OverLoad)	shiftDataBuf[i]=OVL[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-52];
            j++;  
            if(j>62) j=0;                   
         }            
      }
      ManualToggle=1;
   }   
*/

   
/*
   else if(!Auto){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
            shiftDataBuf[i]=INS[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }
*/
       
//   else if(Vip){
//      shift=(shift+1)%32;            
//      j=shift;
//      for(i=0;i<=10;i++){
//         if(j<21){ 
//            shiftDataBuf[i]=VIP[j];
//            j++;            
//         }
//         else{
//            shiftDataBuf[i]=DspBuf[j-21];
//            j++;  
//            if(j>31) j=0;                   
//         }            
//      }
//      ManualToggle=1;
//   }


   else{
      if(ManualToggle){
         FloorChange=0;
         shift=0;
         for(i=0;i<=10;i++){
            shiftDataBuf[i]=DspBuf[i];
         }
         ManualToggle=0;                  
      }
      
      if(FloorChange){
         if(!ShiftOn){
            FloorChange=0;
            shift=0;
            for(i=0;i<=10;i++){
               shiftDataBuf[i]=DspBuf[i];
            }            
         }      

         else if(UpMove || DnMove){
            shift=(shift + 1)%9;
            for(i=0;i<=10;i++){
				if(UpMove){
					shiftDataBuf[i]=(shiftDataBuf[i] >> 1);
	               j=(DspBuf[i] << (8 - shift));
				}
				else{
					shiftDataBuf[i]=(shiftDataBuf[i] << 1);
	               j=(DspBuf[i] >> (8 - shift));
				}

           		shiftDataBuf[i]=(shiftDataBuf[i] | j);
            
               	if(shift==8)   FloorChange=0;
            }         
         }         
         else{
            FloorChange=0;
            shift=0;
            for(i=0;i<=10;i++){
               shiftDataBuf[i]=DspBuf[i];
            }            
         }      
      }
   }                     

#else
	for(i=0;i<=10;i++){
	   shiftDataBuf[i]=DspBuf[i];
	}            
#endif

   ArrowUpDown();

}


#else
void  ShiftData(void)
{

   unsigned char  i;
   unsigned char  j,k,l,m;

  
   if(Fire || StopBit || Full || Emg || !Auto || OverLoad || Parking){
   		if(Fire || StopBit || Full || Emg || !Auto){
			  k=39;
		}
   		else if(OverLoad || Parking){  
			  k=63;
		}

		l=(k-11);

      	shift=(shift+1)%k;            
      	j=shift;
      	for(i=0;i<=10;i++){
         	if(j< l){ 
				if(Emg)				shiftDataBuf[i]=EMG[j];
				else if(Parking)	shiftDataBuf[i]=PARKING[j];
				else if(!Auto)		shiftDataBuf[i]=INS[j];
				else if(Fire)		shiftDataBuf[i]=FIRE[j];
				else if(StopBit)	shiftDataBuf[i]=STOP1[j];
				else if(Full)		shiftDataBuf[i]=FULL[j];
				else if(OverLoad)	shiftDataBuf[i]=OVL[j];
            	j++;
         	}
         	else{
         		if(UpMove || DnMove){
					if(shift >= (k-1)){
						Timexyou = !Timexyou; 					
					}

					if(Timexyou != 0){
						m=11;
					}
					else{
						m=0;
					}	
				}
				else{
					m=0;
					Timexyou=0;
				}

            	shiftDataBuf[i]=DspBuf[m+j- l];
            	j++;  
            	if(j>(k-1)){
 					j=0;
				}          
         	}            
      	}
      	ManualToggle=1;
   	}
	
   	else{
      	if(ManualToggle){
         	ManualToggle=0;                  
      	}
		      
		else{
			
         	if(UpMove || DnMove){
         		if(ShiftOn){

					if(FloorChange){
						if(shift==8){	
							FloorChange=0;
						}
						}
						else{
							for(i=0;i<=21;i++){
							tmpbf[i]=DspBuf[i];
						}
					}


					if(Timexyou==0){
						k=11;
					}	
					else{
						k=0;
					}

		            shift=(shift + 1)%9;

		            for(i=0;i<=10;i++){
						if(UpMove){
							shiftDataBuf[i]=(shiftDataBuf[i] >> 1);
			               	j=(tmpbf[i+k] << (8 - shift));
						}
						else{
							shiftDataBuf[i]=(shiftDataBuf[i] << 1);
			               	j=(tmpbf[i+k] >> (8 - shift));
						}
		
		           		shiftDataBuf[i]=(shiftDataBuf[i] | j);           
		            }         


	               	if(shift==8){
						if(Timexyou==0)	Timexyou=1;
						else			Timexyou=0;	
					}


				}
				else{
	            	shift=0;
					if(Timexyou< 7){
						k=11;
					}	
					else{
						k=0;
						if(Timexyou > 14)	Timexyou=0;
					}
					Timexyou++;

		            for(i=0;i<=10;i++){
		               shiftDataBuf[i]=DspBuf[i+k];
		            }            
				}
			}
			else{
	            FloorChange=0;
				Timexyou=0;
	            shift=0;
	            for(i=0;i<=10;i++){
	               shiftDataBuf[i]=DspBuf[i];
	            }            
			}
		}
   }                
}

#endif
