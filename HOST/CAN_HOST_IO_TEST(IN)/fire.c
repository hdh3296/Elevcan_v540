
#include <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"


extern void             ClrUpDnWard(void);
extern UserDataType     OpenKeyCheck(void);
extern UserDataType     CloseKeyCheck(void);
extern void	  SelectDoorOpen(void);
extern void	  AllDoorCloseCmd(void);      

void  Fire(void)
{
  switch(sRamDArry[mFireSeq]){
        case    NO_FIRE:
            break;                
        case    FIRE_START:
            bCarButClr=1;
            if(bMoveCar){                
//                bCarButClr=1;
                if(OUT_U_W){                
                    if(sRamDArry[mcurfloor] > FireBaseFloor){
                        if(!IN_UND){
                            sRamDArry[mAckStopFloor]=sRamDArry[mcurfloor] | CAR_READY; 
                        }
                    }
                    else if(sRamDArry[mcurfloor] < FireBaseFloor){
                        if(!IN_UND){
                            sRamDArry[mHighFloor]=FireBaseFloor | CAR_READY;
                            sRamDArry[mAckStopFloor]=FireBaseFloor | CAR_READY;
                        }
                    }                
                }
                else if(OUT_D_W){                
                    if(sRamDArry[mcurfloor] < FireBaseFloor){
                        if(!IN_UND){
                            sRamDArry[mAckStopFloor]=sRamDArry[mcurfloor] | CAR_READY; 
                        }
                    }
                    else if(sRamDArry[mcurfloor] > FireBaseFloor){
                        if(!IN_UND){
                            sRamDArry[mLowFloor] = FireBaseFloor | CAR_READY;
                            sRamDArry[mAckStopFloor]=FireBaseFloor | CAR_READY;
                        }
                    }                
                }
            }
            else{
                if(sRamDArry[mcurfloor] == FireBaseFloor){
                    if(bOpenEnd && !IN_FR1){
                        sRamDArry[mFireSeq]=FIRE_ONE;                
                    }
                    else{
                        if(bOnLuLd && bDoorOpenEnd){
                          	ClrUpDnWard();       
//                           	bExtButClr=1;
//                            bCarButClr=1;   
                            bSubWayLight=1;                            
                            NextFloorTime=0;
             	        	if(sRamDArry[mDoorSeq] >= DOOR_REOPEN_CHECK){
                		        sRamDArry[mDoorSeq]=DOOR_OPEN_START;
                     		}
                        }
                        else if(bOnLuLd && (sRamDArry[mDoorSeq] > DOOR_OPEN_WAIT)){
                            sRamDArry[mDoorSeq] = DOOR_OPEN_START;
                        } 
                    }
                }
                else{
                    bReOpen=1;
                    sRamDArry[mAckStopFloor]=FireBaseFloor | CAR_READY;
                    sRamDArry[mNewAckStopFloor]=FireBaseFloor | CAR_READY;        	
                }            
            }            
            break;
        case    FIRE_ONE:                                    
            if(!IN_FR1){
              ClrUpDnWard();       
              S3_CUR_KEY=1;               
              if(CloseKeyCheck() && (sRamDArry[mHighFloor]==0) && (sRamDArry[mLowFloor]==0)){
                SelectDoorOpen();
              }                        
              else  if(!bDoorCloseOk){
                AllDoorCloseCmd();      
              }
              if(bDoorCloseOk &&  (DoorCloseOnTime> 5)){
                sRamDArry[mFireSeq]=FIRE_THREE;                
                sRamDArry[mDoor]=0;
              }
            }
            else{
              S3_CUR_KEY=0;
              sRamDArry[mFireSeq]=FIRE_START;                            
              sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
            }              
            break;            
        case    FIRE_TWO:
        	if(sRamDArry[mDoorSeq] == STOP_ELEVATOR){
                S3_CUR_KEY=1;
            }

            if(!bDoorCloseOk){
                sRamDArry[mFireSeq]=FIRE_THREE;
                bCarErr=1;
                S3_CUR_KEY=0;
            }
            break;
        case    FIRE_THREE:
            if(!IN_FR1){   
              S3_CUR_KEY=1;       
              ClrUpDnWard();       
              if(!OpenKeyCheck()){
                  SelectDoorOpen();
                  sRamDArry[mHighFloor]=sRamDArry[mLowFloor]=0;
                  sRamDArry[mNewAckStopFloor]=0;
                  sRamDArry[mAckStopFloor] = 0;         
                  ClrUpDnWard(); 
              }                        
              else{
                    if(DoorCloseOnTime <= 5)  AllDoorCloseCmd();      
              }

              if(!IN_FR2){
                  S3_CUR_KEY=1;       
                  if((sRamDArry[mHighFloor] > 0) || (sRamDArry[mLowFloor] > 0)){
                      bFR2Start=1;
                      if((RestartTime/5) % 2) OUT_BUZ=1;
                      else                    OUT_BUZ=0;
                  }
                  else{
                      bFR2Start=0;
                  }  
              }


              if(bOpenEnd){
                DoorCloseTime=0;
                sRamDArry[mFireSeq]=FIRE_ONE;     
                sRamDArry[mDoor]=0;

                OUT_BUZ=0;           
              }			
              else if(bDoorCloseOk){
                if((DoorCloseOnTime> 5)){
                    if(IN_FR2 || (!IN_FR2 && (RestartTime > 50))){
                        if(sRamDArry[mHighFloor] > 0){
                          S3_CUR_KEY=0;         
                          OUT_BUZ=0;           
                          sRamDArry[mNewAckStopFloor]=sRamDArry[mHighFloor];  
                          sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                          sRamDArry[mFireSeq]=FIRE_TWO;                     
                        }
                        else if(sRamDArry[mLowFloor] > 0){
                            S3_CUR_KEY=0;       
                            OUT_BUZ=0;           
                            sRamDArry[mNewAckStopFloor]=sRamDArry[mLowFloor];
                            sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                            sRamDArry[mFireSeq]=FIRE_TWO;                     
                        }
                    }
                 }                    
              }
              else{
                sRamDArry[mHighFloor]=sRamDArry[mLowFloor]=0;
                sRamDArry[mNewAckStopFloor]=0;
                sRamDArry[mAckStopFloor] = 0;         
              }
            }
            else{
              S3_CUR_KEY=0;
              sRamDArry[mFireSeq] = FIRE_START;                            
              sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
              OUT_BUZ=0;           
            }                            
            break;
  }
}




void    FireKeyCheck(void)
{
   	if(bAuto){     	
     	if(IN_FIRE && IN_X7 && IN_FR1){
          sRamDArry[mFireSeq] = NO_FIRE;
          S3_CUR_KEY=0;
          S2_FIRE1=0;
          bSubWayLight=0;                            
        }
        else{
          if(sRamDArry[mSysStatus] > sFireOn)   sRamDArry[mSysStatus]=sFireOn;      
          if(!IN_X7)    FireBaseFloor=cF_X7SAFEFLR;    
          else          FireBaseFloor=cF_FIRESAFEFLR;
          S2_FIRE1=1;
          
     	  if(!IN_FIRE || !IN_X7){
            if(sRamDArry[mFireSeq]==NO_FIRE){
                sRamDArry[mFireSeq]=FIRE_START;
            }
          }         
          else if(!IN_FR1){
            if(sRamDArry[mFireSeq] == NO_FIRE){
              if(bMoveCar){
                sRamDArry[mFireSeq]=FIRE_TWO;
              }
              else{
                sRamDArry[mFireSeq]=FIRE_THREE;            
              }
            }
          }

          if(FireBaseFloor>cF_TOPFLR)   FireBaseFloor=0;     
        }
    }

    else{
      sRamDArry[mFireSeq] = NO_FIRE;
      S3_CUR_KEY=0;
      S2_FIRE1=0;
      bSubWayLight=0;                            
    }

    if(IN_FR1 || IN_FR2)    bFR2Start=0;        
  
    Fire();
}






