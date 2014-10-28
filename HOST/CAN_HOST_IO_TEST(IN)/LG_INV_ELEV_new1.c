

      
#include  <p30f6010.h>            
      
#include  "iodef.h"
#include  "host_io.h"            
#include  "door.h"
#include  "com.h"
#include  "counter.h"


void    DspFloorSet(void);

void    CarStopCmd(void);
void    CarUpStartCmd(void);
void    CarDnStartCmd(void);
void    CarCurFloorRead(void);
void	InverterErrorCheck(void);



extern   void   CallMeUpDnDirectionSet(void);                                                                       
extern   void   ClrUpDnWard(void);
extern   void   UpDnCallClear(void);           
extern   void   UpWard(void);
extern	 void   DnWard(void);


const   unsigned        int    seg1[]={0x0,0x06,0x0b,0x07};
const   unsigned        int    seg0[]={0x3f,0x06,0xdb,0xcf,0xe6,0xed,0xfd,0x27,0xff,0xef,0x5c};
 

void  DspFloorSet(void)
{
    LocalType i,j;  
    
    i=(UserDataType)(sRamDArry[mcurfloor] * 2);    
	sRamDArry[S0_FLOOR]  = sRamDArry[mcurfloor]+1;
        
    sRamDArry[DSP1]  = cF_FLRDSPCH((unsigned long)i);
    sRamDArry[DSP2]  = cF_FLRDSPCH((unsigned long)(i+1)); 

    j=sRamDArry[mcurfloor]+1;

    i=(j%10);    
    SegData0=~seg0[i];

    i=(j/10);
    SegData1=~seg0[i];

    SegData2=0xff;    
}


/*
void   RunSpeedCmd_ELEV(void)
{
    OUT_P1=1;
    OUT_P2=0;
    OUT_P3=0;
}

void   ManualSpeedCmd_ELEV(void)
{
    OUT_P1=0;
    OUT_P2=0;
    OUT_P3=1;
}


void   DecreaseSpeedCmd_ELEV(void)
{
    OUT_P1=0;
    OUT_P2=1;
    OUT_P3=0;
}

void   ZeroSpeedCmd_ELEV(void)
{
    OUT_P1=0;
    OUT_P2=0;
    OUT_P3=0;
}
*/


void   RunSpeedCmd_ELEV(void)
{
    OUT_P1=0;
    OUT_P2=0;
    OUT_P3=1;
}

void   ManualSpeedCmd_ELEV(void)
{
    OUT_P1=1;
    OUT_P2=0;
    OUT_P3=0;
}


void   DecreaseSpeedCmd_ELEV(void)
{
    OUT_P1=1;
    OUT_P2=1;
    OUT_P3=0;
}

void   ZeroSpeedCmd_ELEV(void)
{
    OUT_P1=0;
    OUT_P2=0;
    OUT_P3=0;
}


/*
void  ManualHomeSpeedCmd_ELEV(void)
{        
    if(bAuto){
        if(bMoveDnOk && bMoveUpOk){
            if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;                                                     
            DecreaseSpeedCmd_ELEV();
            if(LuLdTime>ZERO_HZ){
                ZeroSpeedCmd_ELEV();
            }   
        }
   	    else{
            sRamDArry[mCarMoveState]=0;
        }    
    }	 		  
}
*/


void    Mnanual_Speed_Sel_ELEV(void)
{
       
    ManualSpeedCmd_ELEV();
                  				
    if(bUpWard){
        if(!IN_LU || !IN_LD){
            if(!IN_SU1 || bSearchHome || ((bFhmRun) && (sRamDArry[FHM_SEQ] == FHM_SEQ_4)) ){
                DecreaseSpeedCmd_ELEV();
            }
        }
/*
        if(!IN_SU1 && (!IN_LU || !IN_LD)){
            DecreaseSpeedCmd_ELEV();
        }
        else if(bSearchHome && (!IN_LU || !IN_LD)){
            DecreaseSpeedCmd_ELEV();
        }
*/
    }
    else if(bDnWard){
        if(!IN_LU || !IN_LD){
            if(!IN_SD1 || bSearchHome ){
                DecreaseSpeedCmd_ELEV();
            }
        }
/*
        if(!IN_SD1 && (!IN_LU || !IN_LD)){ 
            DecreaseSpeedCmd_ELEV();
        }
        else if(bSearchHome && (!IN_LU || !IN_LD)){
            DecreaseSpeedCmd_ELEV();
        }
*/
    }
}



void   CarStopCmd_ELEV(void)
{         
    if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;            

    switch(sRamDArry[mCarMoveState]){
        case    0:
            sRamDArry[mCarMoveState]=1;
            break;							
        case  1:                       
            sRamDArry[mCarMoveState]=2;
            CarStopTime=0;
//       	  CallMeUpDnDirectionSet();                                                                       
//            UpDnCallClear();
            if(S1_POWER_FAIL){	
                LuLdTime=iF_F_BrkStTm20;			
			} 		           
            break;
        case  2:
//            CallMeUpDnDirectionSet();                                                                       
//            UpDnCallClear();           
            ZeroSpeedCmd_ELEV();
             
            if(LuLdTime>iF_F_BrkStTm20){
                OUT_BRK=0;                     
                sRamDArry[mCarMoveState]=3;         
            }              
            break;                                    
        case  3:      
//       	    CallMeUpDnDirectionSet();                                                                       
            if(LuLdTime>iF_F_BrkStTm30){
                OUT_BK2=0;
                if(sRamDArry[mSysStatus] > sSTOP)   sRamDArry[mSysStatus]=sSTOP;

                sRamDArry[mCarMoveState]=4;         
             }                       
             break;
        case  4:
//       	    CallMeUpDnDirectionSet();                                                                       
            if(LuLdTime>iF_F_BrkStTm40){
           	    CallMeUpDnDirectionSet();                                                                       
                OUT_U_W=0;                                                               
                OUT_D_W=0;                                                        
                OUT_BRK=0;
         	    OUT_BK2=0;
                ZeroSpeedCmd_ELEV();
                
                bVoiceReady=0;   
                bMoveCar=0;
                bCarUpMove=0;
                bCarDnMove=0;
                S2_CAR_MOVE1=0;
                bVoiceReady=0;   
                if(!bAuto)  ClrUpDnWard();
            }              
            break;      
    }   	
}




void   CarUpStartCmd_ELEV(void)
{
    bManualStop=0;
    if(bMoveUpOk){
        UpWard();
		if(bAuto){
	        if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
			AllDoorCloseCmd();     	
		}		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_UP)   sRamDArry[mSysStatus]=sMANUAL_UP;               	
        }
                          
        switch(sRamDArry[mCarMoveState]){
            case  0:
                CarStopTime=0;
                ZeroSpeedCmd_ELEV();
                OUT_U_W=0;                                                               
                OUT_D_W=0;                                                        
                OUT_BRK=0;                     
                OUT_BK2=0;
                sRamDArry[mCarMoveState]=1;
                break;
            case  1:
                ZeroSpeedCmd_ELEV();                
                OUT_U_W=1;                                                         

                if(CarStopTime > cF_STTM1){
                    OUT_BK2=1;
                    sRamDArry[mCarMoveState]=2;
                }                                               

                break;                  
            case  2:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=1;
                bCarDnMove=0;               
                if(CarStopTime > cF_STTM2){
                    OUT_BRK=1;                     
                    sRamDArry[mCarMoveState]=3;
                }              
                break; 
            case  3:
                if(CarStopTime > cF_STTM3){
                     OUT_U_W=1;
                     if(bAuto)                  RunSpeedCmd_ELEV();
                     else if(S1_POWER_FAIL)     DecreaseSpeedCmd_ELEV();
                     else                       Mnanual_Speed_Sel_ELEV();
                }
                break;                                                 
            default:
                sRamDArry[mCarMoveState]=0;
                break;
        }
    }
    else{
        sRamDArry[mCarMoveState]=0;
   	}     
}



void   CarDnStartCmd_ELEV(void)
{    
    bManualStop=0;

    if(bMoveDnOk){	   
        DnWard();
        if(bAuto){
            if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;      
            AllDoorCloseCmd();     	
        }		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_DN)   sRamDArry[mSysStatus]=sMANUAL_DN;               	
        }              
        switch(sRamDArry[mCarMoveState]){
            case  0:
                CarStopTime=0;
                ZeroSpeedCmd_ELEV();
                OUT_U_W=0;                                                               
                OUT_D_W=0;                                                        
                OUT_BRK=0;                     
                OUT_BK2=0;
                sRamDArry[mCarMoveState]=1;
                break;
            case  1:
                ZeroSpeedCmd_ELEV();                
                OUT_D_W=1;                                                         

                if(CarStopTime > cF_STTM1){
                    OUT_BK2=1;
                    sRamDArry[mCarMoveState]=2;
                }                                               

                break;                  
            case  2:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=1;
                bCarDnMove=0;               
                if(CarStopTime > cF_STTM2){
                    OUT_BRK=1;                     
                    sRamDArry[mCarMoveState]=3;
                }              
                break; 
            case  3:
                if(CarStopTime > cF_STTM3){
                     OUT_D_W=1;
                     if(bAuto)                  RunSpeedCmd_ELEV();
//                     else if(bPowerFail)        DecreaseSpeedCmd_ELEV();
                     else if(S1_POWER_FAIL)     DecreaseSpeedCmd_ELEV();
                     else                       Mnanual_Speed_Sel_ELEV();
                }                                                 
                break;                                                 
            default:
                sRamDArry[mCarMoveState]=0;
                break;
        }
    }
    else{
        sRamDArry[mCarMoveState]=0;
    }        
}




void  CarCurFloorRead_ELEV(void)
{
		
    if(IN_FID){
        sRamDArry[mReqStopFloor]   = (I_FS0_bit & 0x3f);				
        NextFTime=0;		
    }         
    else{   		      
        sRamDArry[mcurfloor] = (I_FS0_bit & 0x1f);  		      
        DspFloorSet();
        CurFTime=0;
    }
}



void	InverterErrorCheck_ELEV(void)
{
    if((CurFTime>10) || (NextFTime>10)){
        if(bAuto){
            bCarStopNoRun=1;       	
            bsInvCurNext=1;
        }         		
        CurFTime=11;
        NextFTime=11;
    }
    else{	
        bsInvCurNext=0;
    }
}					


/*///////////////////////////////////////
000 x  zero         //
001 x  60           //fun 13    
010 x  decrease     //fun 14
011 x  90           //fun 15
100 x  manual       //fun 16
101 x  120          //fun 17
110 x  batery       //fun 18
111 x  150          //fun 19
///////////////////////////////////////*/


void    CurSelSpeed(unsigned int spd)
{
    switch(spd){
        case    0:
            OUT_P1=0;
            OUT_P2=0;
            OUT_P3=0;    
            OUT_P4N=0;    
            break;
        case    1:
            OUT_P1=1;
            OUT_P2=0;
            OUT_P3=0;    
            OUT_P4N=0;    
            break;
        case    2:
            OUT_P1=0;
            OUT_P2=1;
            OUT_P3=0;    
            OUT_P4N=0;    
            break;
        case    3:
            OUT_P1=1;
            OUT_P2=1;
            OUT_P3=0;    
            OUT_P4N=0;    
            break;
        case    4:
            OUT_P1=0;
            OUT_P2=0;
            OUT_P3=1;    
            OUT_P4N=0;    
            break;
        case    5:
            OUT_P1=1;
            OUT_P2=0;
            OUT_P3=1;    
            OUT_P4N=0;    
            break;
        case    6:
            OUT_P1=0;
            OUT_P2=1;
            OUT_P3=1;    
            OUT_P4N=0;    
            break;
        case    7:
            OUT_P1=1;
            OUT_P2=1;
            OUT_P3=1;    
            OUT_P4N=0;    
            break;
/*
        case    8:
            OUT_P1=0;
            OUT_P2=0;
            OUT_P3=0;    
//            OUT_P4=1;    
            break;
        case    9:
            OUT_P1=1;
            OUT_P2=0;
            OUT_P3=0;    
//            OUT_P4=1;    
            break;
        case    10:
            OUT_P1=0;
            OUT_P2=1;
            OUT_P3=0;    
//            OUT_P4=1;    
            break;
        case    11:
            OUT_P1=1;
            OUT_P2=1;
            OUT_P3=0;    
//            OUT_P4=1;    
            break;
        case    12:
            OUT_P1=0;
            OUT_P2=0;
            OUT_P3=1;    
//            OUT_P4=1;    
            break;
        case    13:
            OUT_P1=1;
            OUT_P2=0;
            OUT_P3=1;    
//            OUT_P4=1;    
            break;
        case    14:
            OUT_P1=0;
            OUT_P2=1;
            OUT_P3=1;    
//            OUT_P4=1;    
            break;
        case    15:
            OUT_P1=1;
            OUT_P2=1;
            OUT_P3=1;    
//            OUT_P4=1;    
            break;
*/
        default:
            OUT_P1=0;
            OUT_P2=0;
            OUT_P3=0;    
            OUT_P4N=1;    
            break;
    }
}



void   RunSpeedCmd_IO(void)
{
    switch(CurSpeed){
        case    SPEED_30:    
            CurSelSpeed(cF_SPEED30);                        
            break;
        case    SPEED_45:
            CurSelSpeed(cF_SPEED45);                        
            break;
        case    SPEED_60:
            CurSelSpeed(cF_SPEED60);                        
            break;
        case    SPEED_90:
            CurSelSpeed(cF_SPEED90);                        
            break;
        case    SPEED_105:
            CurSelSpeed(cF_SPEED105);                        
            break;
        case    SPEED_120:
            CurSelSpeed(cF_SPEED120);                        
            break;
        case    SPEED_150:
            CurSelSpeed(cF_SPEED150);                        
            break;
        case    SPEED_180:
            CurSelSpeed(cF_SPEED180);                        
            break;
        case    SPEED_210:
            CurSelSpeed(cF_SPEED210);                        
            break;
        default:
            CurSelSpeed(0);                        
            break;
    }
}





void   ManualSpeedCmd_IO(void)
{
    CurSelSpeed(cF_MANUALSPEED);                        
/*
    OUT_P1=0;
    OUT_P2=0;
    OUT_P3=1;
*/
}


void   BatterySpeedCmd_IO(void)
{
    CurSelSpeed(cF_BATTERYSPEED);                        
/*
    OUT_P1=0;
    OUT_P2=1;
    OUT_P3=1;
*/
}


void   Etc1SpeedCmd_IO(void)
{
    CurSelSpeed(cF_ETC1SPEED);                        
//    OUT_P1=0;
//    OUT_P2=1;
//    OUT_P3=0;
}

void   Etc2SpeedCmd_IO(void)
{
    CurSelSpeed(cF_ETC2SPEED);                        
//    OUT_P1=0;
//    OUT_P2=1;
//    OUT_P3=0;
}

void   Etc3SpeedCmd_IO(void)
{
    CurSelSpeed(cF_ETC3SPEED);                        
//    OUT_P1=0;
//    OUT_P2=1;
//    OUT_P3=0;
}

void   DecreaseSpeedCmd_IO(void)
{
    CurSelSpeed(cF_DECREASESPEED);                        
//    OUT_P1=0;
//    OUT_P2=1;
//    OUT_P3=0;
}


void   ZeroSpeedCmd_IO(void)
{
    CurSelSpeed(0);                        
}



/*
void  ManualHomeSpeedCmd_IO(void)
{        
    if(bAuto){
        if(bMoveDnOk && bMoveUpOk){
            if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;                                                     
            DecreaseSpeedCmd_IO();
            if(LuLdTime>ZERO_HZ){
                ZeroSpeedCmd_IO();
            }   
        }
   	    else{
            sRamDArry[mCarMoveState]=0;
        }    
    }	 		  
}
*/


void   CarLowSpeedCmd_IO(void)
{        
    if(bAuto && bManualAuto){
        if(bMoveDnOk && bMoveUpOk){
            if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;                                                     
            DecreaseSpeedCmd_IO();
            bVoiceReady=1;

            if(LuLdTime>iF_F_BrkStTm10){
                ZeroSpeedCmd_IO();
            }   

        }
   	    else{
            sRamDArry[mCarMoveState]=0;
        }    
    }	 		     
}




void    Mnanual_Speed_Sel_IC(void)
{
       
    ManualSpeedCmd_IO();
                  				
    if(bUpWard){
        if(!IN_LU || !IN_LD){
            if(!IN_SU1 || bSearchHome || ((bFhmRun) && (sRamDArry[FHM_SEQ] == FHM_SEQ_4)) ){
                DecreaseSpeedCmd_IO();
            }
        }
/*
        if(!IN_SU1 && (!IN_LU || !IN_LD)){
            DecreaseSpeedCmd_IO();
        }
        else if(bSearchHome && (!IN_LU || !IN_LD)){
            DecreaseSpeedCmd_IO();
        }
*/
    }
    else if(bDnWard){
        if(!IN_LU || !IN_LD){
            if(!IN_SD1 || bSearchHome ){
                DecreaseSpeedCmd_IO();
            }
        }

/*
        if(!IN_SD1 && (!IN_LU || !IN_LD)){ 
            DecreaseSpeedCmd_IO();
        }
        else if(bSearchHome && (!IN_LU || !IN_LD)){
            DecreaseSpeedCmd_IO();
        }
*/
    }
}


////
void   CarStopCmd_IO(void)
{        
    switch(sRamDArry[mCarMoveState]){
        case	0:
            sRamDArry[mCarMoveState]=1;
            break;							
        case  1:                                   
            sRamDArry[mCarMoveState]=2;
            CarStopTime=0;
//            CallMeUpDnDirectionSet();                                                                       
//            UpDnCallClear();           
            break;
        case  2:
//            CallMeUpDnDirectionSet();                                                                       
//            UpDnCallClear();           
            ZeroSpeedCmd_IO();

            if(LuLdTime>iF_F_BrkStTm20){
                sRamDArry[mCarMoveState]=3;         
                OUT_BRK=0;                     
            }              
            break;                                    
        case  3:
            if(LuLdTime>iF_F_BrkStTm30){
                OUT_BK2=0;
                sRamDArry[mCarMoveState]=4;         
            }              
            break;      
        case  4:
//       	    CallMeUpDnDirectionSet();                                                                       
            if(LuLdTime>iF_F_BrkStTm40){
           	    CallMeUpDnDirectionSet();                                                                       
                ZeroSpeedCmd_IO();
                OUT_U_W=0;                                                               
                OUT_D_W=0;                                                        
                OUT_BRK=0;
                OUT_BK2=0;

                bMoveCar=0;
                bCarUpMove=0;
                bCarDnMove=0;
                S2_CAR_MOVE1=0;

                if(!bAuto)  ClrUpDnWard();
                bVoiceReady=0;   
            }              
            break;      
    }
}



void   CarUpStartCmd_IO(void)
{
    bManualStop=0;
    if(bMoveUpOk){
        UpWard();
        if(bAuto){
            if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
            AllDoorCloseCmd();     	
        }		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_UP)   sRamDArry[mSysStatus]=sMANUAL_UP;               	
        }              
		
     	
        switch(sRamDArry[mCarMoveState]){
             case  0:
                CarStopTime=0;
                ZeroSpeedCmd_IO();
                OUT_U_W=0;                                                               
                OUT_D_W=0;                                                        
                OUT_BRK=0;                     
                OUT_BK2=0;
                sRamDArry[mCarMoveState]=1;
                break;
             case  1:
                ZeroSpeedCmd_IO();                
                OUT_U_W=1;                                                         
                if(CarStopTime > cF_STTM1){
                    OUT_BK2=1;
                    sRamDArry[mCarMoveState]=2;
                }                                               
                break;                  
              case  2:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=1;
                bCarDnMove=0;               
                if(CarStopTime > cF_STTM2){
                    OUT_BRK=1;                     
                    sRamDArry[mCarMoveState]=3;
                }              
                break;      
              case  3:
                if(CarStopTime > cF_STTM3){
                     OUT_U_W=1;
                     if(bAuto)                  RunSpeedCmd_IO();
                     else                       Mnanual_Speed_Sel_IC();
//                     else if(bPowerFail)        DecreaseSpeedCmd_IO();
                     if(S1_POWER_FAIL)          Mnanual_Speed_Sel_IC();
//                     else                       Mnanual_Speed_Sel_IC();
/*
                    	if((bFhmRun) && (FhmSeq == FHM_SEQ_4) && (!IN_LU || !IN_LD)){ 
                            DecreaseSpeedCmd_IO();                         
                        }
*/
                     }
                 break;                  
              default:
                sRamDArry[mCarMoveState]=0;
                break;
        }
    }
    else{
        sRamDArry[mCarMoveState]=0;
    }     
}



void   CarDnStartCmd_IO(void)
{
    bManualStop=0;
    if(bMoveDnOk){   
        DnWard();
        if(bAuto){
            if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;      
            AllDoorCloseCmd();     	
        }		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_DN)   sRamDArry[mSysStatus]=sMANUAL_DN;               	
        }              

        switch(sRamDArry[mCarMoveState]){
            case  0:
                CarStopTime=0;
                ZeroSpeedCmd_IO();
                OUT_U_W=0;                                                               
                OUT_D_W=0;                                                        
                OUT_BRK=0;                     
                OUT_BK2=0;
                sRamDArry[mCarMoveState]=1;
                break;
            case  1:
                ZeroSpeedCmd_IO();
                OUT_D_W=1;                                                         
                if(CarStopTime > cF_STTM1){
                    sRamDArry[mCarMoveState]=2;
                    OUT_BK2=1;
                }                                               
                break;                  
            case  2:
//you                sRamDArry[S2_STATE]  =  sRamDArry[S2_STATE] | S2_CAR_MOVE;     
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=0;
                bCarDnMove=1;
                if(CarStopTime > cF_STTM2){
                    OUT_BRK=1;                     
                    sRamDArry[mCarMoveState]=3;
                }              
                break;      
            case  3:
                if(CarStopTime > cF_STTM3){
                    OUT_D_W=1;                                                                           
                    if(bAuto)               RunSpeedCmd_IO();
                    else                    Mnanual_Speed_Sel_IC();
//                    else if(bPowerFail)     DecreaseSpeedCmd_IO();
                    if(S1_POWER_FAIL)       Mnanual_Speed_Sel_IC();
//                    else                    Mnanual_Speed_Sel_IC();
                }                                                        
                break;                  
            default:
                sRamDArry[mCarMoveState]=0;
                break;
        }
    }
    else{
        sRamDArry[mCarMoveState]=0;
    }        
}




void  CarCurFloorRead_IO(void)
{
    unsigned long decrease_pulse;
    unsigned long tmppulse1,tmppulse2;

     	
    CurFTime=0;
	NextFTime=0;

    if(bFhmRun) return;


    if(sRamDArry[mcurfloor] > 31){
        sRamDArry[mcurfloor]=0;
    }


    if(!IN_SU1){
        sRamDArry[mcurfloor]=cF_TOPFLR;
    }

    if(!IN_SD1){
        sRamDArry[mcurfloor]=0;
    }


    if(bCarUpMove){

//CurSpeed=SPEED_90;
        if(!IN_SU1){
            if((CurMeterPerMin/10) > cF_SU1SD1_VELOCITY)   bCarErr=1;

            IN_UND=1;
            CarLowSpeedCmd_IO();
        }

        if(!IN_SU2){
            if((CurMeterPerMin/10) > cF_SU2SD2_VELOCITY)   bCarErr=1;

			if(CurSpeed >= SPEED_90){
	            IN_UND=1;
    	        CarLowSpeedCmd_IO();
			}
        }

        if(!IN_SU3){
            if((CurMeterPerMin/10) > cF_SU3SD3_VELOCITY)   bCarErr=1;

			if(CurSpeed >= SPEED_120){
	            IN_UND=1;
    	        CarLowSpeedCmd_IO();
			}
        }

        if(sRamDArry[mcurfloor] == cF_TOPFLR)   tmppulse1=FLOOR_COUNT(cF_TOPFLR);
        else                                    tmppulse1=FLOOR_COUNT(sRamDArry[mcurfloor]+1);
        
        tmppulse2=DecreasePulse;
        decrease_pulse=(tmppulse1-tmppulse2);

        if((unsigned long)CurPulse >= (unsigned long)decrease_pulse){
            if(sRamDArry[mcurfloor] < cF_TOPFLR) sRamDArry[mcurfloor]++;
            if(OUT_DAC || (sRamDArry[mcurfloor] >= cF_TOPFLR)){   
                IN_UND=1;
                CarLowSpeedCmd_IO();
            }
        }


        if(IN_UND){
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] < cF_TOPFLR){
                if(CurPulse > StopMinimumPulse) sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor]+1) | 0x20;
                else                            sRamDArry[mReqStopFloor]  = (sRamDArry[mReqStopFloor] & ~CAR_READY);    
            }
            else                                sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);            
        }
    }

    else if(bCarDnMove){

        if(!IN_SD1){
            if((CurMeterPerMin/10) > cF_SU1SD1_VELOCITY)   bCarErr=1;
            IN_UND=1;
            CarLowSpeedCmd_IO();
        }

        if(!IN_SD2){
            if((CurMeterPerMin/10) > cF_SU2SD2_VELOCITY)   bCarErr=1;

			if(CurSpeed >= SPEED_90){
	            IN_UND=1;
    	        CarLowSpeedCmd_IO();
			}
        }
        if(!IN_SD3){
            if((CurMeterPerMin/10) > cF_SU3SD3_VELOCITY)   bCarErr=1;
		
			if((CurSpeed >= SPEED_120)){
	            IN_UND=1;
    	        CarLowSpeedCmd_IO();
			}
        }


        if(sRamDArry[mcurfloor]==0) tmppulse1=FLOOR_COUNT(sRamDArry[mcurfloor]);
        else                        tmppulse1=FLOOR_COUNT(sRamDArry[mcurfloor]-1);

        tmppulse2=DecreasePulse;
        decrease_pulse=(tmppulse1 + tmppulse2);

        if((unsigned long)CurPulse <= (unsigned long)decrease_pulse ){
            if(sRamDArry[mcurfloor]>0)  sRamDArry[mcurfloor]--;  

            if(OUT_DAC || (sRamDArry[mcurfloor]==0)){  
                IN_UND=1;
                CarLowSpeedCmd_IO();
            }
        }

        if(IN_UND){
            CarLowSpeedCmd_IO();
        }    				
        else{
            if(sRamDArry[mcurfloor] > 0){
                if(CurPulse < StopMinimumPulse) sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor]-1) | 0x20;
                else                            sRamDArry[mReqStopFloor]  = (sRamDArry[mReqStopFloor] & ~CAR_READY);    
            }
            else                                sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);            
        }

    }


    else{
        IN_UND=0;
        sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];            
    }


    DspFloorSet();
    
    return;
}



void	InverterErrorCheck_IO(void)
{
    bsInvCurNext=0;
}


////////////////////////////////////////
////////////////////////////////////////

void    CarStopCmd(void)
{
    if(!bOnLuLd)    bCarErr=1;

    if(RUN_MODE == LG_INVERTER_ELEV)    CarStopCmd_ELEV();                                             
    else                                CarStopCmd_IO();
}

void    CarUpStartCmd(void)
{
    bSaveFlash=0;

    if(RUN_MODE == LG_INVERTER_ELEV)    CarUpStartCmd_ELEV();                                             
    else                                CarUpStartCmd_IO();
}

void    CarDnStartCmd(void)
{
    bSaveFlash=0;

    if(RUN_MODE == LG_INVERTER_ELEV)    CarDnStartCmd_ELEV();                                             
    else                                CarDnStartCmd_IO();
}


/*
void    ManualHomeSpeedCmd(void)
{
    if(RUN_MODE == LG_INVERTER_ELEV)    ManualHomeSpeedCmd_ELEV();                                             
    else                                ManualHomeSpeedCmd_IO();
}
*/

void    CarCurFloorRead(void)
{
    if(RUN_MODE == LG_INVERTER_ELEV)    CarCurFloorRead_ELEV();                                             
    else                                CarCurFloorRead_IO();
}



void	   InverterErrorCheck(void)
{
    if(RUN_MODE == LG_INVERTER_ELEV)    InverterErrorCheck_ELEV();                                             
    else                                InverterErrorCheck_IO();
}
