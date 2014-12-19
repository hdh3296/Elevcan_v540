

      
#include  <p30f6010.h>            
      
#include  "iodef.h"
#include  "host_io.h"            
#include  "door.h"
#include  "com.h"
#include  "counter.h"
#include  "default_setup.h"


void    DspFloorSet(void);

void    CarStopCmd(void);
void    CarUpStartCmd(void);
void    CarDnStartCmd(void);
void    CarCurFloorRead(void);
void	InverterErrorCheck(void);



//extern   void   CallMeUpDnDirectionSet(void);                                                                       
extern   void   ClrUpDnWard(void);
extern   void   UpDnCallClear(void);           
extern   void   UpWard(void);
extern	 void   DnWard(void);


const   unsigned        int    seg1[]={0x0,0x06,0x0b,0x07};
const   unsigned        int    seg0[]={0x3f,0x06,0xdb,0xcf,0xe6,0xed,0xfd,0x27,0xff,0xef,0x5c};
 


void __attribute__((section(".usercode")))   DspFloorSet(void)
{
    LocalType i,j;  

    if(bDspSeq || !(bCarErr || bCarStopNoRun || bCarStop) ){    
        i=(UserDataType)(sRamDArry[mcurfloor] * 2);
        
    	sRamDArry[S0_FLOOR]  = sRamDArry[mcurfloor]+1;
            
        sRamDArry[DSP1]  = cF_FLRDSPCH((unsigned long)i);
        sRamDArry[DSP2]  = cF_FLRDSPCH((unsigned long)(i+1)); 
    
        j=sRamDArry[mcurfloor]+1;
    
        i=(j%10);    
        SegData0=~seg0[i];
        SegData0=(SegData0 | 0x80);
    
        i=(j/10);
        SegData1=~seg0[i];
        SegData1=(SegData1 | 0x80);
    
        SegData2=0xff;
    }
    else{
/*
        i=(UserDataType)(sRamDArry[mcurfloor] * 2);
        
    	sRamDArry[S0_FLOOR]  = sRamDArry[mcurfloor]+1;
            
        sRamDArry[DSP1]  = cF_FLRDSPCH((unsigned long)i);
        sRamDArry[DSP2]  = cF_FLRDSPCH((unsigned long)(i+1)); 
        j=sRamDArry[mcurfloor]+1;
*/    

        j=SegError;
    
        i=(j%10);    
        SegData0=~seg0[i];
        SegData0=(SegData0 | 0x80);
    
        i=(j/10);
        SegData1=~seg0[i];
        SegData1=(SegData1 | 0x80);
    
        SegData2=( ~(0x79) | 0x80);
    }    
}



////////////////
/*/////////// I/O MODE////////////////////////////
000 x  zero         //
001 x  60           //fun 13    
010 x  decrease     //fun 14
011 x  90           //fun 15
100 x  manual       //fun 16
101 x  120          //fun 17
110 x  batery       //fun 18
111 x  150          //fun 19
///////////////////////////////////////*/
/*/////////// E/L MODE////////////////////////////
000 x  zero         //fun 12
001 x  manual       //fun 13
010 x  not use      //fun 14
011 x  decrease     //fun 15
100 x  auto         //fun 16
101 x  not use      //fun 17
110 x  not use      //fun 18
111 x  not use      //fun 19
///////////////////////////////////////*/

////////////////
void __attribute__((section(".usercode")))     CurSelSpeed(unsigned int spd)
{
    switch(spd){
        case    0:
            OUT_P1(0);
            OUT_P2(0);
            OUT_P3(0);    
//            OUT_P4(0);    
            break;
        case    1:
            OUT_P1(1);
            OUT_P2(0);
            OUT_P3(0);    
//            OUT_P4(0);    
            break;
        case    2:
            OUT_P1(0);
            OUT_P2(1);
            OUT_P3(0);    
//            OUT_P4(0);    
            break;
        case    3:
            OUT_P1(1);
            OUT_P2(1);
            OUT_P3(0);    
//            OUT_P4(0);    
            break;
        case    4:
            OUT_P1(0);
            OUT_P2(0);
            OUT_P3(1);    
//            OUT_P4(0);    
            break;
        case    5:
            OUT_P1(1);
            OUT_P2(0);
            OUT_P3(1);    
//            OUT_P4(0);    
            break;
        case    6:
            OUT_P1(0);
            OUT_P2(1);
            OUT_P3(1);    
//            OUT_P4(0);    
            break;
        case    7:
            OUT_P1(1);
            OUT_P2(1);
            OUT_P3(1);    
//            OUT_P4(0);    
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
            OUT_P1(0);
            OUT_P2(0);
            OUT_P3(0);    
            OUT_P4(0);    
            break;
    }
}



void __attribute__((section(".usercode")))    RunSpeedCmd_IO(void)
{

    if(INVERTER_CHECK == LG)    CurSpeed=SPEED_60;
    if(INVERTER_CHECK == D_F)   CurSpeed=SPEED_60;

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





void __attribute__((section(".usercode")))    ManualSpeedCmd_IO(void)
{
    CurSelSpeed(cF_MANUALSPEED);                        
}



void __attribute__((section(".usercode")))    BatterySpeedCmd_IO(void)
{
    CurSelSpeed(cF_BATTERYSPEED);                        
}

/*
void __attribute__((section(".usercode")))    Etc1SpeedCmd_IO(void)
{
    CurSelSpeed(cF_ETC1SPEED);                        
}

void __attribute__((section(".usercode")))    Etc2SpeedCmd_IO(void)
{
    CurSelSpeed(cF_ETC2SPEED);                        
}

void __attribute__((section(".usercode")))    Etc3SpeedCmd_IO(void)
{
    CurSelSpeed(cF_FHMSPEED);                        
}
*/

void __attribute__((section(".usercode")))    DecreaseSpeedCmd_IO(void)
{
    CurSelSpeed(cF_DECREASESPEED);     
    CounterTime=0;                   
}


void __attribute__((section(".usercode")))    ZeroSpeedCmd_IO(void)
{
    CurSelSpeed(0);                        
}

////////////////////
/////////////////////





void  __attribute__((section(".usercode")))    Mnanual_Speed_Sel(void)
{
       
    ManualSpeedCmd_IO();

    if(S1_POWER_FAIL && (cF_BATTERYSPEED > 0)){
 		BatterySpeedCmd_IO();
	}
                  				
    if(bCarUpMove){
        if(!IN_LU || !IN_LD ){
            if(!IN_SU1 || bSearchHome ){     
                DecreaseSpeedCmd_IO();
            }
        } 


/*
        if(!IN_LU || !IN_LD ){
            if(!IN_SU1 || bSearchHome || ((bFhmRun) && (sRamDArry[FHM_SEQ] == FHM_SEQ_4))){
                DecreaseSpeedCmd_IO();
            }
        }
	    else if(IN_LU && IN_LD && !bFhmEncoder && bFhmRun && (sRamDArry[FHM_SEQ] == FHM_SEQ_4) && (INVERTER_CHECK != LG)){
        	DecreaseSpeedCmd_IO();
		}
*/
    }
    else if(bCarDnMove){
        if(!IN_LU || !IN_LD){
            if(!IN_SD1 || bSearchHome){
                DecreaseSpeedCmd_IO();
            }
        }
    }
}





void  __attribute__((section(".usercode")))  CarCurFloorRead_ELEV(void)
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
    
    if(IN_UND1)  bUnd=1;      
    else         bUnd=0;      
}



void  __attribute__((section(".usercode"))) 	InverterErrorCheck_ELEV(void)
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




void  __attribute__((section(".usercode")))    CarLowSpeedCmd_IO(void)
{        
    if(bAuto && bManualAuto){
        if(bMoveDnOk && bMoveUpOk){
            if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;                                                     
            DecreaseSpeedCmd_IO();
            bVoiceReady=1;

/*
            if(LuLdTime>iF_RunOffTime){
                ZeroSpeedCmd_IO();
            }   
*/

        }
   	    else{
            sRamDArry[mCarMoveState]=0;
        }    
    }	 		     
}



/*
*/



void  __attribute__((section(".usercode")))   CarStopCmd_IO(void)
{        
    switch(sRamDArry[mCarMoveState]){
        case	0:
            sRamDArry[mCarMoveState]=1;
            break;							
        case  1:                                   
            sRamDArry[mCarMoveState]=2;

            bOneStep=0;               
            bTwoStep=0;                
            bThreeStep=0;              
            bFourStep=0;               
            break;
        case  2:
            CounterTime=0;
            ZeroSpeedCmd_IO();

            if(LuLdTime>iF_Bk1OffTime){
                bOneStep=1;               
                OUT_BRK(0);                     
            }              

            if(LuLdTime>iF_Bk2OffTime){
                bTwoStep=1;               
                OUT_BK2(0);
            }              

            if(LuLdTime>iF_UDOffTime){
                bThreeStep=1;               
          	    CallMeUpDnDirectionSet();                                                                       
                OUT_U_W(0);                                                               
                OUT_D_W(0);                                                        
            }              

            if(LuLdTime>iF_P4OffTime){
                bFourStep=1;               
                OUT_P4(0);
            }


            if(bOneStep && bTwoStep && bThreeStep && bFourStep){               
                ZeroSpeedCmd_IO();
                OUT_P4(0);
                OUT_U_W(0);                                                               
                OUT_D_W(0);                                                        
                OUT_BRK(0);
                OUT_BK2(0);

                bMoveCar=0;
                bCarUpMove=0;
                bCarDnMove=0;
                S2_CAR_MOVE1=0;
                if(!bAuto)  ClrUpDnWard();
                bVoiceReady=0;   
				ElevMoveTime=0;
            }              
            break;
        default:
            sRamDArry[mCarMoveState]=0;
            break;
    }
}



LocalType  __attribute__((section(".usercode")))  OilTypeRunState(void)
{
    LocalType i;  
    
    i=0;

    if((INVERTER_CHECK == D_F) && (!OilLopeTypeChk) && S1_AUTO1 && !bD_F_FloorOn && IN_LU && IN_LD ){ 
        i=1;
    }
        
    return(i);
}


void  __attribute__((section(".usercode")))  UpDnRunOut(void)
{
    if(bAuto)	RunSpeedCmd_IO();
    else{
        if(OilTypeRunState()){
            RunSpeedCmd_IO();
        }
        else{
            Mnanual_Speed_Sel();
        }
    } 
   
//////    if(S1_POWER_FAIL)          Mnanual_Speed_Sel();

	if(bNextFlrChk==0){
		bNextFlrChk=1;
		NextFloorTime=0;
   		CounterTime=0;
	}
}



void  __attribute__((section(".usercode")))   CarUpStartCmd_IO(void)
{
//    bManualStop=0;
    if(bMoveUpOk){
        UpWard();

        if(sRamDArry[mcurfloor]< cF_TOPFLR)  sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor]+1;
        else                                 sRamDArry[mReqStopFloor]  = cF_TOPFLR;

        if(bAuto){
            if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
        }		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_UP)   sRamDArry[mSysStatus]=sMANUAL_UP;               	
        }              
		
     	
        switch(sRamDArry[mCarMoveState]){
             case  0:
                ZeroSpeedCmd_IO();
                OUT_U_W(0);                                                               
                OUT_D_W(0);                                                        
                OUT_BRK(0);                     
                OUT_BK2(0);
                OUT_P4(0);    

				bNextFlrChk=0;
                sRamDArry[mCarMoveState]=1;
                break;
             case  1:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=1;
                bCarDnMove=0;

                if(ElevMoveTime > cF_STTM1){
                    if(INVERTER_CHECK != LG)    OUT_P4(1);
                }
                if(ElevMoveTime > cF_STTM2){
                    OUT_U_W(1);
                }                                               
                if(ElevMoveTime > cF_STTM3){
                    OUT_BK2(1);
                }              
                if(ElevMoveTime > cF_STTM4){
                     OUT_BRK(1);                     
                }
                if(ElevMoveTime > cF_STTM5){
                    UpDnRunOut();
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



void  __attribute__((section(".usercode")))   CarDnStartCmd_IO(void)
{
    if(bMoveDnOk){   
        DnWard();
        if(sRamDArry[mcurfloor]>0)  sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor]-1;
        else                        sRamDArry[mReqStopFloor]  = 0;

        if(bAuto){
            if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;      
        }		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_DN)   sRamDArry[mSysStatus]=sMANUAL_DN;               	
        }              

        switch(sRamDArry[mCarMoveState]){
            case  0:
                ZeroSpeedCmd_IO();
                OUT_U_W(0);                                                               
                OUT_D_W(0);                                                        
                OUT_BRK(0);                     
                OUT_BK2(0);
                OUT_P4(0);    

				bNextFlrChk=0;
                sRamDArry[mCarMoveState]=1;
                break;
             case  1:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=0;
                bCarDnMove=1;

                if(ElevMoveTime > cF_STTM1){
                    if(INVERTER_CHECK != LG)    OUT_P4(1);
                }
                if(ElevMoveTime > cF_STTM2){
                    OUT_D_W(1);
                }                                               
                if(ElevMoveTime > cF_STTM3){
                    OUT_BK2(1);
                }              
                if(ElevMoveTime > cF_STTM4){
                    OUT_BRK(1);                     
                }
                if(ElevMoveTime > cF_STTM5){
                    UpDnRunOut();
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



LocalType  __attribute__((section(".usercode")))    UpForceSettingSpeed(void)
{
	if(UpLimitSpeedCheck())													return(0);
//    else if((sRamDArry[mcurfloor] >= (cF_TOPFLR-1)) && (!IN_LU || !IN_LD) )	return(0);
    else if( sRamDArry[mcurfloor] >= cF_TOPFLR )							return(0);
	else																	return(1);
}


LocalType  __attribute__((section(".usercode")))    DnForceSettingSpeed(void)
{
	if(DnLimitSpeedCheck())											return(0);
//    else if((sRamDArry[mcurfloor] <= 1) && (!IN_LU || !IN_LD) )		return(0);
    else if( sRamDArry[mcurfloor] == 0 )							return(0);
	else															return(1);
}



LocalType  __attribute__((section(".usercode")))    ForceSettingSpeed(void)
{

    if(cF_LIMIT_SPEED >= SPEED_210)	return(0);
	if(bUnd)						return(0);	

    bSetSpeedOn=0;

    if(bAuto && bCarUpMove){
		if(cF_ELEV_SPEED > cF_LIMIT_SPEED){ 
			if( !UpForceSettingSpeed()){
    			if(CurSpeed > cF_LIMIT_SPEED){
                    bSetSpeedOn=1;                    
                }
            }
		}            
    }
    else if(bAuto && bCarDnMove){
		if(cF_ELEV_SPEED > cF_LIMIT_SPEED){ 
			if( !DnForceSettingSpeed()){
    			if(CurSpeed > cF_LIMIT_SPEED){
                    bSetSpeedOn=1;                    
                }
            }
		}            
    }
        

    if(bSetSpeedOn && (CurSpeed > cF_LIMIT_SPEED)){
        CurSpeed=cF_LIMIT_SPEED;

        switch(cF_LIMIT_SPEED){
            case    SPEED_30:
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                break;
            case    SPEED_45:
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                break;
            case    SPEED_60:
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                break;
            case    SPEED_90:
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                break;
            case    SPEED_105:
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                break;
            case    SPEED_120:
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                break;
            case    SPEED_150:
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                break;
            case    SPEED_180:
                DecreasePulse=GET_LONG(DEC_PULSE_180);
                break;
            case    SPEED_210:
                DecreasePulse=GET_LONG(DEC_PULSE_210);
                break;
            default:
                bSetSpeedOn=0;
                break;

        }


        if(bSetSpeedOn){
            if(bCarUpMove)  StopMinimumPulse=DecreasePulse+CurPulse;
            else            StopMinimumPulse=CurPulse-DecreasePulse;
	        RunSpeedCmd_IO();
        }
    }

	return(0);
}





void  __attribute__((section(".usercode")))  CarCurFloorRead_IO(void)
{
    unsigned long decrease_pulse;
    unsigned long tmppulse1,tmppulse2,newFloor;

    LocalType ReqFlr;  


    CurFTime=0;
	NextFTime=0;

    if(bFhmRun) return;


    ForceSettingSpeed();


    ReqFlr=(LocalType)(sRamDArry[mReqStopFloor] & ONLY_FLR);     	


    if(sRamDArry[mcurfloor] > cF_TOPFLR){
        sRamDArry[mcurfloor]=0;
    }



    if(bCarUpMove){
        if(!IN_SU1){
            if(!IN_EMG)	sRamDArry[mcurfloor]=cF_TOPFLR;   //modify ?
/////            sRamDArry[mcurfloor]=cF_TOPFLR;   //modify ?
            bUnd=1;
            CarLowSpeedCmd_IO();
        }


        if(!IN_SU2){
			if(CurMeterPerMin > (cF_SU2SD2_VELOCITY * 10)){
	            bUnd=1;
	   	        CarLowSpeedCmd_IO();
			}
		}


        if(UpLimitSpeedCheck() && (cF_X0X1_VELOCITY > cF_SU2SD2_VELOCITY)){   //x1
			if(CurMeterPerMin > (cF_X0X1_VELOCITY * 10)){
	            bUnd=1;
	   	        CarLowSpeedCmd_IO();
			}
		}



        if(sRamDArry[mcurfloor] >= cF_TOPFLR){
            tmppulse1=FLOOR_COUNT(cF_TOPFLR);
            tmppulse2=FLOOR_COUNT(cF_TOPFLR-1);
        }
        else{
            tmppulse1=FLOOR_COUNT(sRamDArry[mcurfloor]+1);
            tmppulse2=FLOOR_COUNT(sRamDArry[mcurfloor]);
        }
            
        newFloor=(tmppulse1-tmppulse2);
        newFloor=(unsigned long)(newFloor >> 1);
        newFloor=(unsigned long)(tmppulse2 + newFloor);

        if((unsigned long)CurPulse >= (unsigned long)newFloor){
            if(sRamDArry[mcurfloor] < cF_TOPFLR) sRamDArry[mcurfloor]++;
        }


        if(ReqFlr >= cF_TOPFLR){
            tmppulse1=FLOOR_COUNT(cF_TOPFLR);
        }
        else{
            tmppulse1=FLOOR_COUNT(ReqFlr);
        }
            
        tmppulse2=DecreasePulse;
        decrease_pulse=(tmppulse1-tmppulse2);

        if((unsigned long)CurPulse >= (unsigned long)decrease_pulse){
//            if(ReqFlr < cF_TOPFLR) sRamDArry[mReqStopFloor]++;

            if(bDac || (sRamDArry[mcurfloor] >= cF_TOPFLR) || (ReqFlr >= cF_TOPFLR)){   
                bUnd=1;
                CarLowSpeedCmd_IO();
                if(sRamDArry[mcurfloor] >= cF_TOPFLR){
                    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);
                }
            }
            else sRamDArry[mReqStopFloor]++;            
        }


        if(bUnd){
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] < cF_TOPFLR){
                if(CurPulse > StopMinimumPulse) sRamDArry[mReqStopFloor]  = (sRamDArry[mReqStopFloor] | 0x20);
                else                            sRamDArry[mReqStopFloor]  = (sRamDArry[mReqStopFloor] & ~CAR_READY);    
            }
            else                                sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);                        
        }

		if(sRamDArry[mcurfloor] >= cF_TOPFLR){
			sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | CAR_READY);  
	    	sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];				                      
		}
    }

    else if(bCarDnMove){
        if(!IN_SD1){                              //modify ?
            if(!IN_EMG)	sRamDArry[mcurfloor]=0;
/////////////////////////////////   sRamDArry[mcurfloor]=0;
            bUnd=1;
            CarLowSpeedCmd_IO();
     	}


        if(!IN_SD2){
			if(CurMeterPerMin > (cF_SU2SD2_VELOCITY * 10)){
	            bUnd=1;
	   	        CarLowSpeedCmd_IO();
			}
		}


        if(DnLimitSpeedCheck() && (cF_X0X1_VELOCITY > cF_SU2SD2_VELOCITY)){  //x0
			if(CurMeterPerMin > (cF_X0X1_VELOCITY * 10)){
	            bUnd=1;
	   	        CarLowSpeedCmd_IO();
			}
		}






/*
        if(!IN_SD3){
			if((CurSpeed >= SPEED_120)){
                bUnd=1;
    	        CarLowSpeedCmd_IO();
			}
        }
*/

///////////
        if(sRamDArry[mcurfloor] == 0){
            tmppulse1=FLOOR_COUNT(1);
            tmppulse2=FLOOR_COUNT(0);
        }
        else{
            tmppulse1=FLOOR_COUNT(sRamDArry[mcurfloor]);
            tmppulse2=FLOOR_COUNT(sRamDArry[mcurfloor]-1);
        }
            
        newFloor=(tmppulse1-tmppulse2);
        newFloor=(unsigned long)(newFloor >> 1);
        newFloor=(unsigned long)(tmppulse2 + newFloor);

        if((unsigned long)CurPulse <= (unsigned long)newFloor){
            if(sRamDArry[mcurfloor] > 0 ) sRamDArry[mcurfloor]--;
        }


        if(ReqFlr == 0){
            tmppulse1=FLOOR_COUNT(0);
        }
        else{
            tmppulse1=FLOOR_COUNT(ReqFlr);
        }

        tmppulse2=DecreasePulse;
        decrease_pulse=(tmppulse1 + tmppulse2);


        if((unsigned long)CurPulse <= (unsigned long)decrease_pulse){
//            if(ReqFlr > 0) sRamDArry[mReqStopFloor]--;
            if(bDac || (sRamDArry[mcurfloor] == 0) || (ReqFlr == 0)){   
                bUnd=1;
                CarLowSpeedCmd_IO();
                if(sRamDArry[mcurfloor] == 0){
                    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);
                }
            }
            else sRamDArry[mReqStopFloor]--;
        }


        if(bUnd){
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] > 0){
                if(CurPulse < StopMinimumPulse) sRamDArry[mReqStopFloor]  = (sRamDArry[mReqStopFloor] | 0x20);
                else                            sRamDArry[mReqStopFloor]  = (sRamDArry[mReqStopFloor] & ~CAR_READY);    
            }
            else                                sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);                        
        }

		if(sRamDArry[mcurfloor] == 0){
			sRamDArry[mReqStopFloor] = (sRamDArry[mcurfloor] | CAR_READY);  
	    	sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];				                      
		}

    }
    else{
        bUnd=0;
        sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];            
    }


    DspFloorSet();
    
    return;
}




LocalType  __attribute__((section(".usercode")))  CurFloorRead_OnOff(void)
{
    LocalType   j;

    j=0;

    if(!IN_SD1 && !IN_EMG){				//modify ?
///////////////////////////    if(!IN_SD1){
        sRamDArry[mcurfloor]=0;
        j++;
    }
    if(!IN_SU1 && !IN_EMG){               //modify ?
////////////////////////////////    if(!IN_SU1){
        sRamDArry[mcurfloor]=cF_TOPFLR;
        j++;
    }
    if(!IN_X0 && (cF_TOPFLR >= 2)){
        sRamDArry[mcurfloor]=1;
        j++;
    }
    if(!IN_X1 && (cF_TOPFLR >= 3)){
        sRamDArry[mcurfloor]=2;
        j++;
    }
    if(!IN_X2 && (cF_TOPFLR >= 4)){
        sRamDArry[mcurfloor]=3;
        j++;
    }
    if(!IN_X3 && (cF_TOPFLR >= 5)){
        sRamDArry[mcurfloor]=4;
        j++;
    }
    if(!IN_X4 && (cF_TOPFLR >= 6)){
        sRamDArry[mcurfloor]=5;
        j++;
    }
    if(!IN_X5 && (cF_TOPFLR >= 7)){
        sRamDArry[mcurfloor]=6;
        j++;
    }
    if(!IN_X6 && (cF_TOPFLR >= 8)){
        sRamDArry[mcurfloor]=7;
        j++;
    }



    bD_F_FloorOn=0;

    if(j == 1){
        bD_F_FloorOn=1;        
		bEqualFloorError=0;
    }
    else if(j >= 2){
		if( !IN_AUTO){
            bEqualFloorError=1;
			bCarErr=1;
		}
		else	bEqualFloorError=0;
    }
    
    return(j);
}




int  __attribute__((section(".usercode")))  Up_Direct_Dec_Chk(void)
{
  
	if(sRamDArry[mcurfloor] >= cF_TOPFLR)	return(0);
    else if( (sRamDArry[mcurfloor] & ONLY_FLR) == (sRamDArry[mAckStopFloor] & ONLY_FLR)){
		if(bDac)	return(0);
	}

	return(1);
}

int  __attribute__((section(".usercode")))  Dn_Direct_Dec_Chk(void)
{
  
	if(sRamDArry[mcurfloor] == 0)	return(0);
    else if( (sRamDArry[mcurfloor] & ONLY_FLR) == (sRamDArry[mAckStopFloor] & ONLY_FLR)){
		if(bDac)	return(0);
	}

	return(1);
}



void  __attribute__((section(".usercode")))  CarCurFloorRead_OnOff(void)
{

    LocalType ReqFlr;  


    CurFTime=0;
	NextFTime=0;

    if(bFhmRun) return;

    CurFloorRead_OnOff();


    ReqFlr=(LocalType)(sRamDArry[mReqStopFloor] & ONLY_FLR);     	



    if(sRamDArry[mcurfloor] > cF_TOPFLR){
        sRamDArry[mcurfloor]=0;
    }


    if(bCarUpMove){
        if(!IN_SU1){							//modify ?
            if(!IN_EMG)	sRamDArry[mcurfloor]=cF_TOPFLR;   
//////////////////////////////            sRamDArry[mcurfloor]=cF_TOPFLR;   
            bUnd=1;
            CarLowSpeedCmd_IO();
        }

        if(bD_F_FloorOn){
//        if(i==1){
			if( Up_Direct_Dec_Chk() == 0){
//            if( (bDac && ((sRamDArry[mcurfloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR)) ) || (sRamDArry[mcurfloor] >= cF_TOPFLR) ){   
                bUnd=1;
                CarLowSpeedCmd_IO();
                if(sRamDArry[mcurfloor] >= cF_TOPFLR){
                    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | CAR_READY);
                }
            }
        }


        if(bUnd){
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] < cF_TOPFLR){
//                if(i==0)    sRamDArry[mReqStopFloor]  = ((sRamDArry[mcurfloor]+1) | CAR_READY);                
                if(!bD_F_FloorOn)    sRamDArry[mReqStopFloor]  = ((sRamDArry[mcurfloor]+1) | CAR_READY);                
    			else if(((sRamDArry[mReqStopFloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR))  ||  !(sRamDArry[mReqStopFloor] & CAR_READY)){
                    sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];                        
                }
            }
            else    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | CAR_READY);                        
        }
    }


    else if(bCarDnMove){
        if(!IN_SD1){                             //modify ?
////            sRamDArry[mcurfloor]=0;
            if(!IN_EMG)	sRamDArry[mcurfloor]=0;

            bUnd=1;
            CarLowSpeedCmd_IO();
        }

        if(bD_F_FloorOn){
//        if(i==1){
			if( Dn_Direct_Dec_Chk() == 0){
//            if((bDac && ((sRamDArry[mcurfloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR)) ) || (sRamDArry[mcurfloor] == 0) ){   
//            if(bDac || (sRamDArry[mcurfloor] == 0) ){   
                bUnd=1;
                CarLowSpeedCmd_IO();
                if(sRamDArry[mcurfloor] == 0){
                    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);
                }
            }
        }


        if(bUnd){
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] > 0){
//                if(i==0)    sRamDArry[mReqStopFloor]  = ((sRamDArry[mcurfloor]- 1) | CAR_READY);                
                if(!bD_F_FloorOn)    sRamDArry[mReqStopFloor]  = ((sRamDArry[mcurfloor]- 1) | CAR_READY);                
    			else if(((sRamDArry[mReqStopFloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR))  ||  !(sRamDArry[mReqStopFloor] & CAR_READY)){
                    sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];                        
                }
            }
            else    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | CAR_READY);                        
        }
    }

    else{
        bUnd=0;
        sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];            
    }

    DspFloorSet();    
}




void  __attribute__((section(".usercode"))) 	InverterErrorCheck_IO(void)
{
    bsInvCurNext=0;
}



void   __attribute__((section(".usercode")))   CarStopCmd(void)
{
    if(IN_LU && IN_LD)    bCarErr=1;

    CarStopCmd_IO();
	S3_SHIFT1=0; //shift   
    bSetSpeedOn=0;
}


void  __attribute__((section(".usercode")))    CarUpStartCmd(void)
{
    bSaveFlash=0;
    bSetSpeedOn=0;

    CarUpStartCmd_IO();
}


void  __attribute__((section(".usercode")))    CarDnStartCmd(void)
{
    bSaveFlash=0;
    bSetSpeedOn=0;

    CarDnStartCmd_IO();
}



void  __attribute__((section(".usercode")))    CarCurFloorRead(void)
{
    if(INVERTER_CHECK == LG)                                CarCurFloorRead_ELEV();                                             
    else if(INVERTER_CHECK == D_F)                          CarCurFloorRead_OnOff();                                             
    else                                                    CarCurFloorRead_IO();

}



void   __attribute__((section(".usercode"))) InverterErrorCheck(void)
{
    if(INVERTER_CHECK == LG)            InverterErrorCheck_ELEV();                                             
    else                                InverterErrorCheck_IO();
}
