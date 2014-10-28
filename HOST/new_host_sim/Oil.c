
#include  <p30f6010.h>            
      
#include  "iodef.h"
#include  "host_io.h"            
#include  "door.h"
#include  "com.h"
#include  "counter.h"
#include  "default_setup.h"


/*
void  __attribute__((section(".usercode")))    CarLowSpeedCmd_Oil(void)
{        
    if(bAuto && bManualAuto){
        if(bMoveDnOk && bMoveUpOk){
            if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;                                                     

            if(bCarUpMove){
                OUT_D_W(0); //u
                OUT_P3(0);  //h
        
                OUT_U_W(1); //u
                OUT_P1(0);  //h
                OUT_P2(1);  //l  
            }
            else if(bCarDnMove){
                OUT_U_W(0); //u
                OUT_P1(0);  //h
                OUT_P2(0);  //l  
        
                OUT_D_W(0); //u
                OUT_P3(1);  //h
            }

            else{
                OUT_U_W(0); //u
                OUT_D_W(0); //u
                OUT_P1(0);  //h
                OUT_P2(0);  //l          
                OUT_P3(0);  //h
            }

            bVoiceReady=1;
        }
   	    else{
            sRamDArry[mCarMoveState]=0;

            OUT_U_W(0); //u
            OUT_D_W(0); //u
            OUT_P1(0);  //h
            OUT_P2(0);  //l          
            OUT_P3(0);  //h
        }    
    }	 		     
}

*/




LocalType  __attribute__((section(".usercode")))  CurFloorRead_OnOff(void)
{
    LocalType   j;

    j=0;

    if(!IN_SD1){
        sRamDArry[mcurfloor]=0;
        j++;
    }
    if(!IN_SU1){
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


    if(j > 1){
        
    }

    
    return(j);
}




void  __attribute__((section(".usercode")))  CarCurFloorRead_OnOff(void)
{

    LocalType ReqFlr,i;  


    CurFTime=0;
	NextFTime=0;

    if(bFhmRun) return;

    i=CurFloorRead_OnOff();


    ReqFlr=(LocalType)(sRamDArry[mReqStopFloor] & ONLY_FLR);     	



    if(sRamDArry[mcurfloor] > cF_TOPFLR){
        sRamDArry[mcurfloor]=0;
    }


    if(bCarUpMove){
        if(!IN_SU1){
            sRamDArry[mcurfloor]=cF_TOPFLR;
            bUnd=1;
//            CarLowSpeedCmd_Oil();
            CarLowSpeedCmd_IO();
        }

        if(i==1){
            if(bDac || (sRamDArry[mcurfloor] >= cF_TOPFLR) ){   
                bUnd=1;
//                CarLowSpeedCmd_Oil();
                CarLowSpeedCmd_IO();
                if(sRamDArry[mcurfloor] >= cF_TOPFLR){
                    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | CAR_READY);
                }
            }
        }


        if(bUnd){
//            CarLowSpeedCmd_Oil();
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] < cF_TOPFLR){
                if(i==0)    sRamDArry[mReqStopFloor]  = ((sRamDArry[mcurfloor]+1) | CAR_READY);                
    			else if(((sRamDArry[mReqStopFloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR))  ||  !(sRamDArry[mReqStopFloor] & CAR_READY)){
                    sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];                        
                }
            }
            else    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | CAR_READY);                        
        }
    }


    else if(bCarDnMove){
        if(!IN_SD1){
            sRamDArry[mcurfloor]=0;

            bUnd=1;
            CarLowSpeedCmd_IO();
        }

        if(i==1){
            if(bDac || (sRamDArry[mcurfloor] == 0) ){   
                bUnd=1;
//                CarLowSpeedCmd_Oil();
                CarLowSpeedCmd_IO();
                if(sRamDArry[mcurfloor] == 0){
                    sRamDArry[mReqStopFloor]  = (sRamDArry[mcurfloor] | 0x20);
                }
            }
        }


        if(bUnd){
//            CarLowSpeedCmd_Oil();
            CarLowSpeedCmd_IO();
        }			
        else{
            if(sRamDArry[mcurfloor] > 0){
                if(i==0)    sRamDArry[mReqStopFloor]  = ((sRamDArry[mcurfloor]- 1) | CAR_READY);                
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



/*
void __attribute__((section(".usercode")))    CarUpStartCmd_Oil(void)
{
    if(bMoveUpOk){
        UpWard();
		if(bAuto){
	        if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
		}		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_UP)   sRamDArry[mSysStatus]=sMANUAL_UP;               	
        }
                          
        switch(sRamDArry[mCarMoveState]){
            case  0:
                CarStopTime=0;
                ZeroSpeedCmd_IO();
                OUT_U_W(0);                                                               
                OUT_D_W(0);                                                        
                OUT_BRK(0);                     
                OUT_BK2(0);
                sRamDArry[mCarMoveState]=1;
                break;
            case  1:
                OUT_BK2(1);                     
                sRamDArry[mCarMoveState]=2;
                break;                  
            case  2:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=1;
                bCarDnMove=0;               
                OUT_BRK(1);                     
                sRamDArry[mCarMoveState]=3;
                break; 
            case  3:
//                OUT_U_W(1);
                if(bAuto){
                    OUT_U_W(1); //u
                    OUT_P1(1);  //h
                    OUT_P2(1);  //l  

//                  RunSpeedCmd_IO();
                }
                else if(S1_POWER_FAIL){
                    OUT_U_W(1); //u
                    OUT_P1(0);  //h
                    OUT_P2(1);  //l  
//                    DecreaseSpeedCmd_IO();
                }
                else{
                    OUT_U_W(1); //u
                    OUT_P1(0);  //h
                    OUT_P2(1);  //l  
//                  Mnanual_Speed_Sel();
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



void __attribute__((section(".usercode")))    CarDnStartCmd_Oil(void)
{    
//    bManualStop=0;

    if(bMoveDnOk){	   
        DnWard();
        if(bAuto){
            if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;      
        }		   
        else{       
            if(sRamDArry[mSysStatus] > sMANUAL_DN)   sRamDArry[mSysStatus]=sMANUAL_DN;               	
        }              
        switch(sRamDArry[mCarMoveState]){
            case  0:
                CarStopTime=0;
                ZeroSpeedCmd_IO();
                OUT_U_W(0);                                                               
                OUT_D_W(0);                                                        
                OUT_BRK(0);                     
                OUT_BK2(0);
                sRamDArry[mCarMoveState]=1;
                break;
            case  1:
                OUT_BK2(1);
                sRamDArry[mCarMoveState]=2;
                break;                  
            case  2:
                S2_CAR_MOVE1=1; 
                bMoveCar=1;
                bCarUpMove=0;
                bCarDnMove=1;               
                OUT_BRK(1);                     
                sRamDArry[mCarMoveState]=3;
                break; 
            case  3:
                if(bAuto){
                    OUT_D_W(1); //u
                    OUT_P3(1);  //h
                }
                else if(S1_POWER_FAIL){
                    OUT_D_W(0); //u
                    OUT_P3(1);  //h
                }
                else{
                    OUT_D_W(0); //u
                    OUT_P3(1);  //h
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


void __attribute__((section(".usercode")))    CarStopCmd_Oil(void)
{         
    if(sRamDArry[mSysStatus] >= sSLOW_SPEED)   sRamDArry[mSysStatus]=sSLOW_SPEED;            

    switch(sRamDArry[mCarMoveState]){
        case    0:
            sRamDArry[mCarMoveState]=1;
            break;							
        case  1:                       
            sRamDArry[mCarMoveState]=2;
            CarStopTime=0;
            if(S1_POWER_FAIL){	
                LuLdTime=iF_F_BrkStTm20;			
			} 		           
            break;
        case  2:
            if(sRamDArry[mSysStatus] > sSTOP)   sRamDArry[mSysStatus]=sSTOP;
    
            CallMeUpDnDirectionSet();                                                                       
            OUT_U_W(0);                                                               
            OUT_D_W(0);                                                        
            OUT_BRK(0);
            OUT_BK2(0);
            ZeroSpeedCmd_IO();
            
            bVoiceReady=0;   
            bMoveCar=0;
            bCarUpMove=0;
            bCarDnMove=0;
            S2_CAR_MOVE1=0;
            bVoiceReady=0;   
            if(!bAuto)  ClrUpDnWard();
            break;                                    
    }   	
}
*/

