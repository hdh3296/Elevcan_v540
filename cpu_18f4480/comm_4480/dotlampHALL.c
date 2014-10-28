
#include        <io51.h>
#include        "..\com.h"
#include        "..\iomap.h"
#include        "iodef.h"
#include        "fontout.h"
#include        "comdata.h"



extern   unsigned    char  DisableFlr[4];            

extern   unsigned    char  CurStatus;       /*current floor */
extern   unsigned    char  CurFloor;       /*current floor */
extern   unsigned    char  BefCurFloor;   /*current floor */
extern   unsigned    char  Arrowshift;    /*current floor */
extern   unsigned    char  Model;         /*current floor */
extern   unsigned    char  htpt;
extern   unsigned    char  shift;
extern   unsigned    char  shiftTime;
extern   unsigned    char  shiftData[16];
extern   unsigned    char  MyAddress;        
extern   unsigned    char  MyLogAdr;        
extern   unsigned    char  src;
extern   unsigned    char  firstdata;
extern   unsigned    char  seconddata;
extern   unsigned    char  TimeOutBd;
extern   unsigned    char  MainTimer;
extern   unsigned    char  msec100;
extern   unsigned    char  UpButtonTime;
extern   unsigned    char  DnButtonTime;

extern   unsigned    char  TwoDoorAdr;


//extern   unsigned    int   SecTimer;


extern   unsigned    char  EqualFlr;
extern   unsigned    char  HighFlr;
extern   unsigned    char  LowFlr;
extern   unsigned    char  Door;


extern   unsigned    char  ErrDspOnTimer;
extern   unsigned    char  BlinkTime;

extern   bit   UpMove;
extern   bit   DnMove;
extern   bit   FloorChange;
extern   bit   ManualToggle;
extern   bit   CarMove;
extern   bit   KeyClr;
extern   bit   Auto;
extern   bit   FDsp;
extern   bit   Parking;
extern   bit   Vip;
extern   bit   Fire;
extern   bit   ShiftOn;
extern   bit   Open;
extern   bit   UpKeyBit;
extern   bit   DnKeyBit;
extern   bit   Emg;
extern   bit   Water;
extern   bit   Full;
extern   bit   OverLoad;
extern   bit   UpDnBlinkBit;


//extern   bit   StatusDspOnOff;


///

const   unsigned        char    OVL[]={
   0x00,0x00,
   0x3E,0x41,0x41,0x41,0x3E, // ;O  31
   0x00, 
   0x1F,0x20,0x40,0x20,0x1F, // ;V  38
   0x00,
   0x7F,0x49,0x49,0x49,0x41, // ;E  21
   0x00,
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00,    
   0x7F,0x40,0x40,0x40,0x40, // ;L  28
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, // ;O  31
   0x00, 
   0x7E,0x11,0x11,0x11,0x7E, // ;A  17
   0x00,   
   0x7F,0x41,0x41,0x22,0x1C, // ;D  20
   0x00,0x00,0x00 
};


const   unsigned        char    FULL[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  //F
   0x00,   
   0x3F,0x40,0x40,0x40,0x3F, // ;U  37
   0x00,
   0x7F,0x40,0x40,0x40,0x40, // ;L  28
   0x00,
   0x7F,0x40,0x40,0x40,0x40, // ;L  28
   0x00,0x00,0x00 
};


const   unsigned        char    WATER[]={
   0x00,0x00,
   0x3F,0x40,0x38,0x40,0x3F, // ;W  39
   0x00,   
   0x7E,0x11,0x11,0x11,0x7E, // ;A  17
   0x00,
   0x01,0x01,0x7F,0x01,0x01, // ;T  36
   0x00,
   0x7F,0x49,0x49,0x49,0x41, // ;E  21
   0x00,
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00,0x00,0x00 
};


const   unsigned        char    STOP[]={
   0x00,0x00,
   0x46,0x49,0x49,0x49,0x31, // ;S  35
   0x00,   
   0x01,0x01,0x7F,0x01,0x01, // ;T  36
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, // ;O  31
   0x00,
   0x7F,0x09,0x09,0x09,0x06, // ;P  32
   0x00,0x00,0x00 
};


const   unsigned        char    INS[]={
   0x00,0x00,
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x7F,0x04,0x08,0x10,0x7F,  // N  30
   0x00, 
   0x46,0x49,0x49,0x49,0x31,  // S  35
   0x00,0x00,0x00 
};

/*
const   unsigned        char    VIP[]={
   0x00,0x00,
   0x1F,0x20,0x40,0x20,0x1F,     // V  25
   0x00,0x41,0x7F,0x41,0x00,     // I  30
   0x00, 
   0x7F,0x09,0x09,0x09,0x06,     // P  35
   0x00,0x00,0x00 
};
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
   0x3E,0x41,0x49,0x49,0x7A,  // ;G  23
   0x00,0x00,0x00 
};


const   unsigned        char    FIRE[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  //F
   0x00,   
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00,
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00,
   0x7F,0x49,0x49,0x49,0x41, // ;E  21
   0x00,0x00,0x00 
};

const   unsigned        char    EMG[]={
   0x00,0x00,
   0x7F,0x49,0x49,0x49,0x41, // ;E  21
   0x00,   
   0x7F,0x02,0x0C,0x02,0x7F, // ;M  29
   0x00,
   0x3E,0x41,0x49,0x49,0x7A, // ;G  23
   0x00,0x00,0x00 
};


//



void    Lamp(void)
{
   MasterRetKeySave();

   FDsp=0;
   CurFloor=RcvBuf[RCV_DATA];
      
   if(CurFloor != BefCurFloor){
      FloorChange=1;   
      BefCurFloor=CurFloor;
      shift=0;
   }
   
   Floor_Char_load(0,RcvBuf[RCV_DATA+DSP1],RcvBuf[RCV_DATA+DSP2]);

   if(CurFloor == TwoDoorAdr){        
      if(( (TWO_DOOR == 0) && (RcvBuf[RCV_DATA+1] & S1_OPEN)) ||  ( (TWO_DOOR == 1) && (RcvBuf[RCV_DATA+3] & S3_OPEN_SUB) ) ){
         EqualFlr=0;
         if(RcvBuf[RCV_DATA+1] & S1_UP){            
            UP_KEY_LAMP=0;
         }
         else if(RcvBuf[RCV_DATA+2] & S2_DN){       
            DN_KEY_LAMP=0;
         }
      }         
   }

   Open=0;
   if((RcvBuf[RCV_DATA+1] & S1_OPEN)  || (RcvBuf[RCV_DATA+3] & S3_OPEN_SUB)){
      Open=1;   
   }


   CarMove=0;
   if(RcvBuf[RCV_DATA+2] & S2_CAR_MOVE)      CarMove=1;

   if(RcvBuf[RCV_DATA+1] & S1_UP)            UpMove=1;
   else                                      UpMove=0;

   if(RcvBuf[RCV_DATA+2] & S2_DN)            DnMove=1;
   else                                      DnMove=0;

   if((RcvBuf[RCV_DATA+3] & S3_VIP))         Vip=1;
   else                                      Vip=0;

   if((RcvBuf[RCV_DATA+3] & S3_PARKING))     Parking=1;
   else                                      Parking=0;

   if((RcvBuf[RCV_DATA+3] & S3_SHIFT))       ShiftOn=1;
   else                                      ShiftOn=0;
   
   if(RcvBuf[RCV_DATA+2] & S2_FIRE)          Fire=1;
   else                                      Fire=0;

   if(RcvBuf[RCV_DATA+2] & S2_EXT_BUT_CLR)   KeyClr=1;
   else                                      KeyClr=0;
   
   if(RcvBuf[RCV_DATA+1] & S1_EMG)           Emg=1;
   else                                      Emg=0;

   if(RcvBuf[RCV_DATA+3] & S3_WATER)         Water=1;
   else                                      Water=0;


/*         
   if(RcvBuf[RCV_DATA+2] & S2_LAMP_USER)     AUTO_LAMP=1;
   else                                      AUTO_LAMP=0;
         
   if(RcvBuf[RCV_DATA+1] & S1_AUTO){
      Auto=1;
      MANUAL_LAMP=0;
   }      
   else{
      Auto=0;
      MANUAL_LAMP=1;
   }
*/

   if(RcvBuf[RCV_DATA+1] & S1_AUTO){
      Auto=1;
   }      
   else{
      Auto=0;
   }

   

   if(((RcvBuf[RCV_DATA + DEST_FLR] & 0x1f) == (TwoDoorAdr-1)) && Auto && CarMove){
     UpDnBlinkBit=1;     
   }   
   else{ 
     UpDnBlinkBit=0;
     MANUAL_LAMP=0;
     AUTO_LAMP=0;        
     
/*     
     if(DnMove)  MANUAL_LAMP=1;
     else        MANUAL_LAMP=0;
   
     if(UpMove)  AUTO_LAMP=1;
     else        AUTO_LAMP=0;        
*/     
   }            
}


void  UpDownBlink(void)
{ 
  BlinkTime=BlinkTime%8;
       
  if(UpDnBlinkBit){
    if(DnMove){
      if(BlinkTime >= 4)    MANUAL_LAMP=0;      
      else                  MANUAL_LAMP=1;   
      AUTO_LAMP=0;
    }    
    else if(UpMove){
      if(BlinkTime >= 4)    AUTO_LAMP=0;      
      else                  AUTO_LAMP=1;   
      MANUAL_LAMP=0;
    }
    else{
      AUTO_LAMP=0;
      MANUAL_LAMP=0;
      BlinkTime=0;    
    }
  }    
  else{
    BlinkTime=0;
  }
}



void  ArrowUpDown(void)
{
   unsigned char  i,j,k;

   if(!ShiftOn){
      for(i=11;i<=15;i++){
         shiftData[i]=DspBuf[i];
      }              
      Arrowshift=0; 
   }
   
   else{
      if(UpMove){
         Arrowshift=(Arrowshift + 1)%11;
         if(Arrowshift<8){
            k=(7 - Arrowshift);
            for(i=11;i<=15;i++){
               j=(DspBuf[i] << k);
               shiftData[i]=j;           
            }
         }
      }         
      else if(DnMove){
         Arrowshift=(Arrowshift + 1)%11;
         if(Arrowshift<8){
            k=(7 - Arrowshift);
            for(i=11;i<=15;i++){
               j=(DspBuf[i] >> k);
               shiftData[i]=j;           
            }
         }
      }         
      else{
         for(i=11;i<=15;i++){
            shiftData[i]=DspBuf[i];
         }              
         Arrowshift=0;
      }             
   }
}



/*
void  ShiftData(void)
{
   unsigned char  i;
   unsigned char  j;
   
   if(Emg){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
            shiftData[i]=EMG[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }

   else if(Fire){
      shift=(shift+1)%39;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<28){ 
            shiftData[i]=FIRE[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-28];
            j++;  
            if(j>38) j=0;                   
         }            
      }
      ManualToggle=1;
   }   
   
   else if(Parking){
      shift=(shift+1)%57;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<46){ 
            shiftData[i]=PARKING[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-46];
            j++;  
            if(j>56) j=0;                   
         }            
      }
      ManualToggle=1;
   }   
   else if(!Auto){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
            shiftData[i]=INS[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }


   else{
      if(ManualToggle){
         FloorChange=0;
         shift=0;
         for(i=0;i<=10;i++){
            shiftData[i]=DspBuf[i];
         }
         ManualToggle=0;                  
      }
      
      if(FloorChange){
         if(!ShiftOn){
            FloorChange=0;
            shift=0;
            for(i=0;i<=10;i++){
               shiftData[i]=DspBuf[i];
            }            
         }      
         else if(UpMove){
            shift=(shift + 1)%9;
            for(i=0;i<=10;i++){
               shiftData[i]=(shiftData[i] >> 1);
               j=DspBuf[i] << (8 - shift);
               shiftData[i]=(shiftData[i] | j);
            
               if(shift==8)   FloorChange=0;
            }         
         }         
         else if(DnMove){
            shift=(shift + 1)%9;
            for(i=0;i<=10;i++){
               shiftData[i]=(shiftData[i] << 1);
               j=DspBuf[i] >> (8 - shift);
               shiftData[i]=(shiftData[i] | j);
            
               if(shift==8)   FloorChange=0;
            }
         }         
         else{
            FloorChange=0;
            shift=0;
            for(i=0;i<=10;i++){
               shiftData[i]=DspBuf[i];
            }            
         }      
      }
   }                     

   ArrowUpDown();
}

*/


void  ShiftData(void)
{

   unsigned char  i;
   unsigned char  j;
   
   if(Emg){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
            shiftData[i]=EMG[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }
   else if(Fire){
      shift=(shift+1)%39;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<28){ 
            shiftData[i]=FIRE[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-28];
            j++;  
            if(j>38) j=0;                   
         }            
      }
      ManualToggle=1;
   }
   
   else if(Water){
      shift=(shift+1)%39;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<28){ 
            shiftData[i]=STOP[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-28];
            j++;  
            if(j>38) j=0;                   
         }            
      }
      ManualToggle=1;
   }
   
/*      
   else if(Water){
      shift=(shift+1)%45;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<34){ 
            shiftData[i]=WATER[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-34];
            j++;  
            if(j>44) j=0;                   
         }            
      }
      ManualToggle=1;
   }   
*/
   
   else if(Parking){
      shift=(shift+1)%57;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<46){ 
            shiftData[i]=PARKING[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-46];
            j++;  
            if(j>56) j=0;                   
         }            
      }
      ManualToggle=1;
   }   

   else if(!Auto){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
            shiftData[i]=INS[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }
   else if(OverLoad){
      shift=(shift+1)%63;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<52){ 
            shiftData[i]=OVL[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-52];
            j++;  
            if(j>62) j=0;                   
         }            
      }
      ManualToggle=1;
   }   
   else if(Full){
      shift=(shift+1)%39;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<28){ 
            shiftData[i]=FULL[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-28];
            j++;  
            if(j>38) j=0;                   
         }            
      }
      ManualToggle=1;
   }
   
/*       
   else if(Vip){
      shift=(shift+1)%32;            
      j=shift;
      for(i=0;i<=10;i++){
         if(j<21){ 
            shiftData[i]=VIP[j];
            j++;            
         }
         else{
            shiftData[i]=DspBuf[j-21];
            j++;  
            if(j>31) j=0;                   
         }            
      }
      ManualToggle=1;
   }
*/


   else{
      if(ManualToggle){
         FloorChange=0;
         shift=0;
         for(i=0;i<=10;i++){
            shiftData[i]=DspBuf[i];
         }
         ManualToggle=0;                  
      }
      
      if(FloorChange){
         if(!ShiftOn){
            FloorChange=0;
            shift=0;
            for(i=0;i<=10;i++){
               shiftData[i]=DspBuf[i];
            }            
         }      
         else if(UpMove){
            shift=(shift + 1)%9;
            for(i=0;i<=10;i++){
               shiftData[i]=(shiftData[i] >> 1);
               j=DspBuf[i] << (8 - shift);
               shiftData[i]=(shiftData[i] | j);
            
               if(shift==8)   FloorChange=0;
            }         
         }         
         else if(DnMove){
            shift=(shift + 1)%9;
            for(i=0;i<=10;i++){
               shiftData[i]=(shiftData[i] << 1);
               j=DspBuf[i] >> (8 - shift);
               shiftData[i]=(shiftData[i] | j);
            
               if(shift==8)   FloorChange=0;
            }
         }         
         else{
            FloorChange=0;
            shift=0;
            for(i=0;i<=10;i++){
               shiftData[i]=DspBuf[i];
            }            
         }      
      }
   }                     

   ArrowUpDown();
}
