


#include    <pic18.h>


#include        "iodef.h"
#include        "fontout.h"
#include        "comdata.h"
#include        "esdots.h"
#include        "keysort.h"
#include        "setup.h"
#include        "..\..\system_com\memory_map.h"



#ifndef  __TYPE_ES15
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
    #error  "Type Not Define Error(iodef.h)"
#endif




void    CompanyChk(unsigned char id)        
{
    unsigned int    IdPt;
    unsigned char   TmpCompany;

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
   

	IdPt=IsBufferPt(id);
    
    FDsp=0;

    HostCallMe=0;
    if(CallMeAdr == RcvBuf[IdPt + SL_mCallMe])  HostCallMe=1;


    TopFloor=RcvBuf[IdPt + SL_mTopFlr];

    CurFloor=RcvBuf[IdPt];

 






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




#ifdef	C65K80
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






	dsplamp1=(RcvBuf[IdPt] & 0x3f);
    BefCurFloor=(P0 & 0xc0);
	P0=(dsplamp1 | BefCurFloor);


	SEG_G1=UpMove;
	SEG_G2=DnMove;

	UP_LAMP=Full;       
	DN_LAMP=OverLoad;

	AUTO_LAMP=ShiftOn;  // scroll


	if(Auto){
   		MANUAL_LAMP=1;    //auto
		FULL_LAMP=0;	  // inspection
	}	
	else{
   		MANUAL_LAMP=0;	
		FULL_LAMP=1;	
	}




	SEG_adg=0;  //earthquake
	SEG_b_S=Fire;
	SEG_c_S=Parking;

	SEG_e_S=0;	// not use 
	SEG_n12=0;  // not use


    return(0);

}


