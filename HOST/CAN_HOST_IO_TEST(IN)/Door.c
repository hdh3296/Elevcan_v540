
#include  <p30f6010.h>            

#include  "door.h"
#include  "iodef.h"


extern 	UserDataType SubDoorFlrChk(void);


	
void	CurDoorSel(UserDataType sel)
{
	if(!sel)	bSelDoor = MAIN_DOOR;
	else		bSelDoor = SUB_DOOR;
}	                   



void  MainDoorOpenCmd(void)
{
    OUT_CL_S=0;   
    OUT_OP_S=0;   	
   	OUT_CL=0;    	  
   	OUT_OP=1;      
//you   	sRamDArry[S1_STATE]  =  (sRamDArry[S1_STATE] & ~S1_CLOSE);   //close                                  
   	S1_CLOSE1=0;   //close                                  
//you	sRamDArry[S1_STATE]  =  (sRamDArry[S1_STATE] | S1_OPEN);   //open             
    S1_OPEN1=1;
	
	if(SubDoorFlrChk()){
//you      	sRamDArry[S3_STATE]  =  (sRamDArry[S3_STATE] | S3_OPEN_SUB);   //open    
        S3_OPEN_SUB1=1;                          
	}	                 
}


void  SubDoorOpenCmd(void)
{
   OUT_CL=0;    	  
   OUT_OP=0;
         
   OUT_CL_S=0;   
   OUT_OP_S=1;
   
   S1_CLOSE1=0;   
//you   sRamDArry[S1_STATE]  =  (sRamDArry[S1_STATE] & ~S1_CLOSE);   //close                                  
//you   sRamDArry[S3_STATE]  =  (sRamDArry[S3_STATE] | S3_OPEN_SUB);   //close                                  
   S3_OPEN_SUB1=1;
}



void  MainDoorCloseCmd(void)
{      
   OUT_OP=0;   
   OUT_CL=1;      
}


void  SubDoorCloseCmd(void)
{   
   OUT_OP_S=0;   
   OUT_CL_S=1;   
}



void  MainDoorOpenClrCmd(void)
{
   OUT_OP=0;   
}

void  SubDoorOpenClrCmd(void)
{
   OUT_OP_S=0;   
}


void  MainDoorCloseClrCmd(void)
{
   OUT_CL=0;   
}

void  SubDoorCloseClrCmd(void)
{
   OUT_CL_S=0;   
}


void	AllDoorOpenClrCmd(void)
{
	MainDoorOpenClrCmd();
	SubDoorOpenClrCmd();
}

      
void	AllDoorCloseClrCmd(void)
{
	MainDoorCloseClrCmd();
	SubDoorCloseClrCmd();
}      


void	AllDoorCloseCmd(void)
{
	MainDoorCloseCmd();
	SubDoorCloseCmd();
}


void	SelectDoorOpen(void)
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



void	SelectDoorClose(void)
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


void	DoorOpenEndCheck(void)
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


void	DoorCloseEndCheck(UserDataType movecar)
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
		bDoorCloseOk=1;

        S1_OPEN1=0; 
//you      	sRamDArry[S1_STATE]  =  (sRamDArry[S1_STATE] & (~S1_OPEN));     //open                     

//you	   	sRamDArry[S3_STATE]  =  (sRamDArry[S3_STATE] & ~S3_OPEN_SUB);   //close                                  
	   	S3_OPEN_SUB1=0;

//you      	sRamDArry[S1_STATE]  =  (sRamDArry[S1_STATE] | S1_CLOSE);   //close On                     
	   	S1_CLOSE1=1;

   		if(DoorCloseOnTime>30){
			AllDoorCloseClrCmd();   			
   		}	   	
	}		
	else{
		bDoorCloseOk=0;
	}
			
//	if(movecar && bAuto){
	if(movecar){
		AllDoorCloseCmd();   				
		DoorCloseOnTime=0;
	}
}












