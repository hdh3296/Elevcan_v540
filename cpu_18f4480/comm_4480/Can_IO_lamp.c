


#include    <pic18.h>

#include        "iodef.h"
#include        "fontout.h"
#include        "comdata.h"
#include        "esdots.h"
#include        "keysort.h"
#include        "setup.h"
#include        "..\..\system_com\memory_map.h"








#if defined(__TYPE_CAR)

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


const   unsigned        char    ALARM[]={
   0x00,0x00,
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00,   
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,   
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00,
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00, 
   0x7F,0x02,0x0C,0x02,0x7F,  // M  29
   0x00,
   0x00,0x00,0x00,0x00,0x00, //space
   0x00,0x00,0x00 
};

	
#endif




const   unsigned        char    FIRE[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  //F
   0x00,   
   0x00,0x41,0x7F,0x41,0x00,  //I  25
   0x00,
   0x7F,0x09,0x19,0x29,0x46,  //R  30
   0x00,
   0x7F,0x49,0x49,0x49,0x41,  //E  21
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,0x00,0x00 
};





const   unsigned        char    STOP1[]={
   0x00,0x00,
   0x3E,0x41,0x41,0x41,0x22, // C  19
   0x00, 
   0x3E,0x41,0x41,0x41,0x3E, // O  31
   0x00, 
   0x42,0x61,0x51,0x49,0x46, // 2  
   0x00, 
   0x00,0x00,0x00,0x00,0x00,  // blanck  
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,0x00,0x00 
};


const   unsigned        char    STOP2[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  //F
   0x00, 
   0x3E,0x41,0x41,0x41,0x3E, // O  31
   0x00, 
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00, 
   0x7F,0x02,0x0C,0x02,0x7F,  // M  29
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,0x00,0x00 
};



const   unsigned        char    RollingP[]={
   0x00,0x00,
   0x7F,0x09,0x19,0x29,0x46,  //R  30
   0x00,   
   0x3E,0x41,0x41,0x41,0x3E,  // O  31
   0x00,
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,   
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,   
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x09,0x09,0x09,0x06,  // P  25
   0x00,
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00, 
   0x01,0x01,0x7F,0x01,0x01, 	// T  36
   0x00,    
   0x3E,0x41,0x41,0x41,0x22, 	// C  19
   0x00,    
   0x7F,0x08,0x08,0x08,0x7F,  // H  
   0x00,    
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00,    
   0x7F,0x04,0x08,0x10,0x7F,    // N  30
   0x00,    
   0x3E,0x41,0x49,0x49,0x7A,  // G  23
   0x00,   
   0x00,0x00,0x00 
};




bit	Alarm=0;
bit	NoRunErr=0;
bit	Rolling=0;
bit Co2Foam=0; 
bit carbd=0;






unsigned char  SyncButtonCheck(void)
{
	return(1);		
}



void    CompanyChk(unsigned char id)        
{
    unsigned int    IdPt;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
    
    if(!MaskSetBit){
       if((RcvBuf[IdPt+DSP1] == 'C') && (RcvBuf[IdPt+DSP2] == 'M') && !(RcvBuf[IdPt+1] & S1_AUTO))  {
            Company=(unsigned char)RxSidBuffer;
            CmpSetBit=1;      
        }
    }
}



unsigned char   Lamp(unsigned char id)
{

    unsigned int    IdPt;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;
    
    FDsp=0;

    HostCallMe=0;
    if(CallMeAdr == RcvBuf[IdPt + SL_mCallMe])  HostCallMe=1;


    TopFloor=RcvBuf[IdPt + SL_mTopFlr];

    CurFloor=RcvBuf[IdPt];

    return(0);

}




/*

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

      else if(DnMove){
         Arrowshift=(Arrowshift + 1)%11;
         if(Arrowshift<8){
            k=(7 - Arrowshift);
            for(i=11;i<=15;i++){
               j=(DspBuf[i] >> k);
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




void  ShiftData(void)
{

   unsigned char  i;
   unsigned char  j;


   	if(Rolling && (carbd==0)){
      shift=(shift+1)%93;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<82){ 
			if(Rolling)	shiftDataBuf[i]=RollingP[j];
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-82];
            j++;  
            if(j>92) j=0;                   
         }            
      }
      ManualToggle=1;
   	}


	else if((Fire && (carbd==0)) || (StopBit && (carbd==0)) || (Alarm && (carbd==1)) ){
      shift=(shift+1)%48;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<37){ 
			if(StopBit){
				if(Co2Foam)		shiftDataBuf[i]=STOP2[j];
				else			shiftDataBuf[i]=STOP1[j];
			}
			else if(Fire)		shiftDataBuf[i]=FIRE[j];
#if defined(__TYPE_CAR)
			else if(Alarm)	    shiftDataBuf[i]=ALARM[j];  //ship
#endif
            j++;            
         }
         else{
            shiftDataBuf[i]=DspBuf[j-37];
            j++;  
            if(j>47) j=0;                   
         }            
      }
      ManualToggle=1;
   }

#if defined(__TYPE_CAR)
   else if(OverLoad){  
      shift=(shift+1)%63;             
      j=shift;
      for(i=0;i<=10;i++){
         if(j<52){ 
			if(OverLoad)			shiftDataBuf[i]=OVL[j];
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
#endif






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


   ArrowUpDown();

}
*/