
#include <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"





#ifdef		SAMSUNG_FIRE
unsigned int	SamsungFire;
#endif


void  __attribute__((section(".usercode")))   Fire(void)
{
  switch(sRamDArry[mFireSeq]){
        case    NO_FIRE:
            break;                
        case    FIRE_START:
            bCarButClr=1;

            if(bMoveCar){                
                if(bCarUpMove){                
                	if(sRamDArry[mcurfloor] < FireBaseFloor){
                        if(!bUnd){
							sRamDArry[mAckStopFloor]=(unsigned char)(FireBaseFloor | UPDN_CAR_READY);
                            sRamDArry[mHighFloor]   =(unsigned char)(FireBaseFloor | UPDN_CAR_READY);
                        }
					}
					else{
	                    sRamDArry[mLowFloor]  = 0;
	                    sRamDArry[mHighFloor] = 0;
					}
                }

                else if(bCarDnMove){                
                	if(sRamDArry[mcurfloor] > FireBaseFloor){
                        if(!bUnd){
							sRamDArry[mAckStopFloor]=(unsigned char)(FireBaseFloor | UPDN_CAR_READY);
                            sRamDArry[mLowFloor] = (unsigned char)(FireBaseFloor | UPDN_CAR_READY);
                        }
					}
					else{
	                    sRamDArry[mLowFloor]  = 0;
	                    sRamDArry[mHighFloor] = 0;
					}
                }
            }
            else{
                if(sRamDArry[mcurfloor] == FireBaseFloor){

#ifndef	SAMSUNG_FIRE
					sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_SUB_OPEN_KEY_CLEAR);   
					if(bSubSlaveFire)	sRamDArry[mDoor]=( sRamDArry[mDoor] | SUB_OPEN_KEY);                            
					else				sRamDArry[mDoor]=( sRamDArry[mDoor] | MAIN_OPEN_KEY);                            
#endif

                    if( (bOpenDoorOk || !bDoorCloseOk) && !IN_FR1){
                        sRamDArry[mFireSeq]=FIRE_ONE;                
                    }
                    else{
						ValidDoorSel();
                        if(bOnLuLd && bDoorOpenEnd){
                          	ClrUpDnWard();       
                            bSubWayLight=1;                            
                            NextFloorTime=0;
#ifndef	SAMSUNG_FIRE
             	        	if(sRamDArry[mDoorSeq] >= DOOR_REOPEN_CHECK){
								if(NewDoorSelect == MAIN_SUB_DOOR){
									if( (CurDoorSelect == SUB_DOOR) && bSubSlaveFire){
	                		        	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
									}
								}
								else{
                		        	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
								}
                     		}
                        }
                        else if(bOnLuLd && (sRamDArry[mDoorSeq] > DOOR_OPEN_WAIT)){
							if(NewDoorSelect == MAIN_SUB_DOOR){
								if( (CurDoorSelect == SUB_DOOR) && bSubSlaveFire){
                		        	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
								}
							}
							else{
               		        	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
							}

#endif
                        }
 
#ifdef	SAMSUNG_FIRE
                        if(bOnLuLd && !SamsungFire){
                            sRamDArry[mDoorSeq] = DOOR_OPEN_START;
							SamsungFire=1;
							bReOpen=0;
                        } 
                        else if(SamsungFire && !IN_FR1){
		                	sRamDArry[mFireSeq]=FIRE_ONE;                
						}
#endif
                    }
                }
                else{
                    bReOpen=1;
                    if(ElevStopTime > 10){
                        if(sRamDArry[mcurfloor] > FireBaseFloor)        sRamDArry[mLowFloor] = (FireBaseFloor | CAR_READY);
                        else                                            sRamDArry[mHighFloor] =(FireBaseFloor | CAR_READY);
                        sRamDArry[mNewAckStopFloor]=FireBaseFloor | CAR_READY;        	
                    }
                }            
            }            

            break;
        case    FIRE_ONE:                                                        
            if(!IN_FR1){
                ClrUpDnWard();       
                S3_CUR_KEY1=1;               
                if(CloseKeyCheck() && (sRamDArry[mHighFloor]==0) && (sRamDArry[mLowFloor]==0)){
                    SelectDoorOpen_you();
                }                        
                else  if(!bDoorCloseOk){
                    bDoorCloseCmd=1;

                    if(!IN_FR2 && !IN_FR1){
                        if((sRamDArry[mHighFloor] > 0) || (sRamDArry[mLowFloor] > 0)){
                            bOpenDoorOk=0;
                            bFR2Start1=1;
                            if((RestartTime/5) % 2) OUT_BUZ(1);
                            else                    OUT_BUZ(0);

                            if(RestartTime > 50){
                                sRamDArry[mFireSeq]=FIRE_THREE;                
                            }
                        }
                        else{
                            bFR2Start1=0;
                            OUT_BUZ(0);
                        }  
                    }
                    else{
                        bFR2Start1=0;
                        OUT_BUZ(0);
                    }                  
                }

                if(bDoorCloseOk){
                    sRamDArry[mFireSeq]=FIRE_THREE;                
                }
            }
            else{
                S3_CUR_KEY1=0;
                sRamDArry[mFireSeq]=FIRE_START;                            
                sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
            }              
            break;            
        case    FIRE_TWO:
        	if(sRamDArry[mDoorSeq] == STOP_ELEVATOR){
                S3_CUR_KEY1=1;
            }

            if(!bDoorCloseOk){
                sRamDArry[mFireSeq]=FIRE_THREE;
                bCarErr=1;
                S3_CUR_KEY1=0;
            }
            break;
        case    FIRE_THREE:
            if(!IN_FR1){   
              S3_CUR_KEY1=1;       
              ClrUpDnWard();       
              if(!OpenKeyCheck()){
                  SelectDoorOpen_you();
                  sRamDArry[mHighFloor]=sRamDArry[mLowFloor]=0;
                  sRamDArry[mNewAckStopFloor]=0;
                  sRamDArry[mAckStopFloor] = 0;         
                  ClrUpDnWard(); 
              }                        
              else{
                if(DoorCloseOnTime <= 5)  bDoorCloseCmd=1;      
              }


              if(!IN_FR2 && !IN_FR1){
                  S3_CUR_KEY1=1;       
                  if((sRamDArry[mHighFloor] > 0) || (sRamDArry[mLowFloor] > 0)){
                        bDoorCloseCmd=1;
                        bOpenDoorOk=0;
                        bDoorCloseOk=1;
                        bFR2Start1=1;

                        if((RestartTime/5) % 2) OUT_BUZ(1);
                        else                    OUT_BUZ(0);
                  }

                  else{
                      bFR2Start1=0;
                      OUT_BUZ(0);
                  }  
              }
              else{
                  bFR2Start1=0;
                  OUT_BUZ(0);
              }  


              if(bOpenDoorOk){
                DoorCloseTime=0;
                sRamDArry[mFireSeq]=FIRE_ONE;     
                OUT_BUZ(0);           
              }			
              else if(bDoorCloseOk){                    
                    if(IN_FR2 || (!IN_FR2 && (RestartTime > 50))){
                        if(sRamDArry[mHighFloor] > 0){
                          S3_CUR_KEY1=0;         
                          OUT_BUZ(0);           
                          sRamDArry[mNewAckStopFloor]=sRamDArry[mHighFloor];  
                          sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                          sRamDArry[mFireSeq]=FIRE_TWO;                     
                        }
                        else if(sRamDArry[mLowFloor] > 0){
                            S3_CUR_KEY1=0;       
                            OUT_BUZ(0);           
                            sRamDArry[mNewAckStopFloor]=sRamDArry[mLowFloor];
                            sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                            sRamDArry[mFireSeq]=FIRE_TWO;                     
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
              S3_CUR_KEY1=0;
              sRamDArry[mFireSeq] = FIRE_START;                            
              sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
              OUT_BUZ(0);           
            }                            
            break;
  }
}




void  __attribute__((section(".usercode")))     FireKeyCheck(void)
{
   	if(bAuto){     	
     	if(IN_FIRE && !bPC_FIRE && IN_FR1 && !bSlaveFire && (!SubFireCheck())){
          sRamDArry[mFireSeq] = NO_FIRE;
		  S3_CUR_KEY1=0;
          S2_FIRE1=0;
          bSubWayLight=0;                            
        }
        else{
          if(sRamDArry[mSysStatus] > sFireOn)   sRamDArry[mSysStatus]=sFireOn;      
          if( !SubFireCheck())    				FireBaseFloor=cF_FIRESAFEFLR;

          S2_FIRE1=1;
          
     	  if(!IN_FIRE || bPC_FIRE || bSlaveFire || (SubFireCheck())){
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
      	S3_CUR_KEY1=0;
      	S2_FIRE1=0;
      	bFR2Start1=0;
      	bSubWayLight=0;                   
		bSlaveFire=0;
		bSubSlaveFire=0;         
    }


    
    if(IN_FR1 || IN_FR2){
        if(IN_FR1){
            bFR2Start1=0;
        }
        else if(!bMoveCar){
            bFR2Start1=0;
        }
    }

#ifdef	SAMSUNG_FIRE
	if(!S2_FIRE1)	SamsungFire=0;
#endif

    Fire();
}



