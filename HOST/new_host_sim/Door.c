
#include  <p30f6010.h>            

#include  "door.h"
#include  "iodef.h"


extern 	__attribute__((section(".usercode"))) UserDataType SubDoorFlrChk(void);


	
void	__attribute__((section(".usercode"))) CurDoorSel(UserDataType sel)
{
	if(!sel)	bSelDoor = MAIN_DOOR;
	else		bSelDoor = SUB_DOOR;
}	                   



void  __attribute__((section(".usercode"))) MainDoorOpenCmd(void)
{
    OUT_CL_S(0);   
    OUT_OP_S(0);   	
   	OUT_CL(0);    	  
   	OUT_OP(1);      

   	S1_CLOSE1=0;                                     
    S1_OPEN1=1;
	
	if(SubDoorFlrChk()){
        S3_OPEN_SUB1=1;                          
	}	                 
}


void  __attribute__((section(".usercode"))) SubDoorOpenCmd(void)
{
   OUT_CL(0);    	  
   OUT_OP(0);
         
   OUT_CL_S(0);   
   OUT_OP_S(1);
   
   S1_CLOSE1=0;   
   S3_OPEN_SUB1=1;
}



void  __attribute__((section(".usercode"))) MainDoorCloseCmd(void)
{      
   OUT_OP(0);   
   OUT_CL(1);      
   OUT_CL_S(1);   
}


void  __attribute__((section(".usercode"))) SubDoorCloseCmd(void)
{   
   OUT_OP_S(0);   
   OUT_CL_S(1);   
   OUT_CL(1);      
}



void  __attribute__((section(".usercode"))) MainDoorOpenClrCmd(void)
{
   OUT_OP(0);   
}

void  __attribute__((section(".usercode"))) SubDoorOpenClrCmd(void)
{
   OUT_OP_S(0);   
}


void  __attribute__((section(".usercode"))) MainDoorCloseClrCmd(void)
{
   OUT_CL(0);   
   OUT_CL_S(0);   
}

void  __attribute__((section(".usercode"))) SubDoorCloseClrCmd(void)
{
   OUT_CL_S(0);   
   OUT_CL(0);   
}


void	__attribute__((section(".usercode"))) AllDoorOpenClrCmd(void)
{
	MainDoorOpenClrCmd();
	SubDoorOpenClrCmd();
}

      
void	__attribute__((section(".usercode"))) AllDoorCloseClrCmd(void)
{
	MainDoorCloseClrCmd();
	SubDoorCloseClrCmd();
}      


void	__attribute__((section(".usercode"))) AllDoorCloseCmd(void)
{
	MainDoorCloseCmd();
	SubDoorCloseCmd();
}


void	__attribute__((section(".usercode"))) SelectDoorOpen(void)
{
	if(SubDoorFlrChk()){
	     bSelDoor = MAIN_DOOR;
	}
     
	if(bSelDoor == MAIN_DOOR){
		MainDoorOpenCmd();
	}
	else{
		SubDoorOpenCmd();	
	}		
}



void	__attribute__((section(".usercode"))) SelectDoorClose(void)
{
	if(SubDoorFlrChk()){
	     bSelDoor = MAIN_DOOR;
	}

	if(bSelDoor == MAIN_DOOR){
		MainDoorCloseCmd();
	}
	else{
		SubDoorCloseCmd();	
	}
	if(sRamDArry[mSysStatus] >= sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;      
}


void	__attribute__((section(".usercode"))) DoorOpenEndCheck(void)
{
   	if(IN_OP_E){
     	bOpenEnd=0;
     }
	else{
     	bOpenEnd=1;
     	if(DoorOpenOnTime>200){
      		AllDoorOpenClrCmd();
		}      		
	}
}


void	__attribute__((section(".usercode"))) DoorCloseEndCheck(UserDataType movecar)
{	
	if(IN_HL_D){
      	if(movecar)  bsHdsRunOff=1;
   		bHoleDoorClose=0;
   	}
   	else{
   		bHoleDoorClose=1;
   		bsHdsRunOff=0;
   	}	     
                  
   	if(IN_CL_E){
      	if(movecar)  bsCleRunOff=1;      
   		bCloseEnd=0;
   	}
   	else{
   		bCloseEnd=1;
   		bsCleRunOff=0;
	}


	if(bHoleDoorClose && bCloseEnd){	
   		if(DoorCloseOnTime>2){
    		bDoorCloseOk=1;
            S1_OPEN1=0; 
    	   	S3_OPEN_SUB1=0;
      	   	S1_CLOSE1=1;
        }

   		if(DoorCloseOnTime>30){
			AllDoorCloseClrCmd();   			
   		}	   	
	}		
	else{
		bDoorCloseOk=0;
   	   	S1_CLOSE1=0;
	}
			
//	if(movecar && bAuto){
	if(movecar){
		AllDoorCloseCmd();   				
		DoorCloseOnTime=0;
	}
}












