

#include <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"


#ifdef	TEST_SIMULATION

extern void   DspFloorSet(void);

UserDataType    MotorMoveTime;
UserDataType    IncFlr;
UserDataType    xxCnt=0;


/*
void	SimulationKey(void)
{
//	IN_SU1
//	IN_SD1
	IN_SFT=0;
	IN_OLR=0;
	IN_ULS=0;
	IN_DLS=0;
	IN_LU=0;
	IN_LD=0;

	IN_EMG=0;
	IN_PRK=0;
	IN_AUTO=0;
//	IN_U_B
//	IN_D_B
//	IN_OP_E
	IN_CL_E=0;
	IN_HL_D=0;

	IN_GR=0;
//	IN_BAT
//	IN_PASS
//	IN_FIRE
//	IN_WATER
//	IN_EX0
//	IN_EX1
//	IN_EX2

	
//	IN_FR1
//	IN_FR2
//	IN_FR3
//	IN_FR4
//	IN_SU2
//	IN_SD2
//	IN_SU3
//	IN_SD3

//	IN_X0
//	IN_X1 
//	IN_X2
//	IN_X3
//	IN_X4
//	IN_X5
//	IN_X6
//	IN_X7
	
}
*/


unsigned int	__attribute__((section(".usercode"))) DspCharTest(void)
{
	if(!IN_X3){
		if(ElevStopTime < 100){
/*
						if(S1_UP1){
							S1_UP1=0;
							S2_DN1=1;
						}
						else{
							S1_UP1=1;
							S2_DN1=0;
						}
*/
			switch(xxCnt){
				case  0:
		         		S1_OVERLOAD1=1;
		         		break;
		      	case  2:
		         		S2_FIRE1=1;
		         		break;
		      	case  4:
		         		S1_EMG1=1;
		         		break;
		      	case  6:
		         		S3_PARKING1=1;
		         		break;
		      	case  8:						
						S1_AUTO1=0;
						break;
		      	case  10:						
		      	case  11:						
		      	case  12:						
		      	case  13:						
		      	case  14:						
		      	case  15:						
		      	case  16:						
		      	case  17:						
		      	case  18:
				        sRamDArry[DSP1]  = '0';
				        sRamDArry[DSP2]  = (xxCnt-9) + '0';
						sRamDArry[S0_FLOOR]=(xxCnt%2) + 1;
/*					
						if(S1_UP1){
							S1_UP1=0;
							S2_DN1=1;
						}
						else{
							S1_UP1=1;
							S2_DN1=0;
						}
*/
						break;						
		      	case  19:						
				        sRamDArry[DSP1]  = '1';
				        sRamDArry[DSP2]  = '0'; 
						sRamDArry[S0_FLOOR]=(xxCnt%2) + 1;
						break;						
		      	case  20:						
		      	case  21:						
		      	case  22:			
		      	case  23:			
		      	case  24:			
		      	case  25:			
		      	case  26:			
		      	case  27:			
		      	case  28:			
		      	case  29:			
		      	case  30:			
		      	case  31:			
		      	case  32:			
		      	case  33:			
		      	case  34:			
		      	case  35:			
		      	case  36:			
		      	case  37:			
		      	case  38:			
		      	case  39:			
		      	case  40:			
		      	case  41:			
		      	case  42:			
		      	case  43:			
		      	case  44:						
		      	case  45:						
				        sRamDArry[DSP1]  = '0';
				        sRamDArry[DSP2]  = (xxCnt-20) + 'A'; 
						sRamDArry[S0_FLOOR]=(xxCnt%2) + 1;
						break;
				default:
						break;
			}
		}
		else{
			ElevStopTime=0;
			xxCnt=((xxCnt + 1) % 46);
			
			switch(xxCnt){
				case  1:
				case  3:
				case  5:
				case  7:
					S1_UP1=0;
					S2_DN1=0;
					ElevStopTime=50;
					break;
				case  9:
		      	case  10:						
		      	case  11:						
		      	case  12:						
		      	case  13:						
		      	case  14:						
		      	case  15:						
		      	case  16:						
		      	case  17:						
		      	case  18:
		      	case  19:						
		      	case  20:						
		      	case  21:						
		      	case  22:			
		      	case  23:			
		      	case  24:			
		      	case  25:			
		      	case  26:			
		      	case  27:			
		      	case  28:			
		      	case  29:			
		      	case  30:			
		      	case  31:			
		      	case  32:			
		      	case  33:			
		      	case  34:			
		      	case  35:			
		      	case  36:			
		      	case  37:			
		      	case  38:			
		      	case  39:			
		      	case  40:			
		      	case  41:			
		      	case  42:			
		      	case  43:			
		      	case  44:						
		      	case  45:						
					ElevStopTime=80;
					
						if(S1_UP1){
							S1_UP1=0;
							S2_DN1=1;
						}
						else{
							S1_UP1=1;
							S2_DN1=0;
						}


					break;
			}	
		}	
	}
}


void  CarCurFloorReadSimulation(void)
{

    CurFTime=0;
    NextFTime=0;
    
    if(bAuto){
        if(MotorMoveTime>50){
            if(bUnd && bMoveCar){
                MotorMoveTime=55;                
            }
            else{
                sRamDArry[mReqStopFloor]   = (sRamDArry[mcurfloor] & ~CAR_READY);				
                MotorMoveTime=0;
                bUnd=0;
            }
        }
        else if(MotorMoveTime>40){
            if(!bDac){
                LuLdTime=0;
                sRamDArry[mReqStopFloor]   = (sRamDArry[mcurfloor] & ~CAR_READY);				
            }           
            else{
                bUnd=1;
            }     
            IncFlr=1;
        }
        else if(MotorMoveTime>30){
            LuLdTime=0;
            sRamDArry[mReqStopFloor]   = (sRamDArry[mcurfloor] | CAR_READY);				
            IncFlr=1;
        }
        else if(MotorMoveTime>25){
            LuLdTime=0;
            if(IncFlr==0){
                IncFlr=1;
                if(bUpWard){
                    if(sRamDArry[mcurfloor]<31)	sRamDArry[mcurfloor]++;
                }
                else if(bDnWard){
                    if(sRamDArry[mcurfloor]>0)	sRamDArry[mcurfloor]--;	          	
                }	          	            		
            } 
        }    		
        else if((MotorMoveTime>10)){
            IncFlr=0; 
            LuLdTime=0;
            bUnd=0;
        }     		
    }
    else{
        if(MotorMoveTime>50){
            if(bUpWard){
                if(sRamDArry[mcurfloor]<31)	sRamDArry[mcurfloor]++;
                LuLdTime=0; 
            }	          	
            else if(bDnWard){
                if(sRamDArry[mcurfloor]>0)	sRamDArry[mcurfloor]--;	          	
                LuLdTime=0; 
            }	          			
            MotorMoveTime=0;
        }     		     
        bUnd=0;
    }
    
    DspFloorSet();
	DspCharTest();
          
    if(bAuto && (bUpWard || bDnWard) && (sRamDArry[mDoorSeq] == WAIT_NEXT_LULD) && ((sRamDArry[mAckStopFloor] & 0x1f)==sRamDArry[mcurfloor])){        
//        sRamDArry[mReqStopFloor]   = (sRamDArry[mcurfloor] | CAR_READY);
//        IN_UND=1;
        if(MotorMoveTime<35)     LuLdTime=0;
//        CarLowSpeedCmd_IO();
    }          
}

#endif
