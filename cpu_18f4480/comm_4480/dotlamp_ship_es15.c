


#include    <pic18.h>

#include        "iodef.h"
#include        "fontout.h"
#include        "comdata.h"
#include        "esdots.h"
#include        "keysort.h"
#include        "setup.h"
#include        "..\..\system_com\memory_map.h"



/*
const   unsigned        char    EMG[]={
   0x00,0x00,
   0x7F,0x49,0x49,0x49,0x41, // E  21
   0x00,   
   0x7F,0x02,0x0C,0x02,0x7F, // M  29
   0x00,
   0x3E,0x41,0x49,0x49,0x7A, // G  23
   0x00,0x00,0x00 
};
*/

/*
const   unsigned        char    INS[]={
   0x00,0x00,
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00, 
   0x7F,0x04,0x08,0x10,0x7F,  // N  30
   0x00, 
   0x46,0x49,0x49,0x49,0x31,  // S  35
   0x00,0x00,0x00 
};
*/

/*
*/

/*
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
   0x3E,0x41,0x49,0x49,0x7A,  // G  23
   0x00,    
   0x00,0x00,0x00,0x00,0x00,  // blanck  
   0x00,0x00,0x00 
};

*/


/*
const   unsigned        char    FULL[]={
   0x00,0x00,
   0x7F,0x09,0x09,0x09,0x01,  // F
   0x00,   
   0x3F,0x40,0x40,0x40,0x3F,  // U  37
   0x00,
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,0x00,0x00 
};
*/

/* ship
const   unsigned        char    STOP1[]={
   0x00,0x00,
   0x46,0x49,0x49,0x49,0x31, // S  35
   0x00,   
   0x01,0x01,0x7F,0x01,0x01, // T  36
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, // O  31
   0x00,
   0x7F,0x09,0x09,0x09,0x06, // P  32
   0x00,0x00,0x00 
};
*/



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

//#if defined(__TYPE_CAR)

const   unsigned        char    ALARM[]={
   0x00,0x00,
/*
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
*/
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

/*
#else
const   unsigned        char    OVL[]={
   0x00,0x00
};
*/
	
#endif




const   unsigned        char    FIRE[]={
   0x00,0x00,
//   0x00,0x08,0x08,0x08,0x00,  //-  
//   0x00,
//   0x7F,0x41,0x41,0x22,0x1C,  //D  
//   0x00,
//   0x7F,0x08,0x14,0x22,0x41,  //K  35
//   0x00,
//   0x00,0x00,0x00,0x00,0x00,  //space
//   0x00,

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




/////ship////////////
/*
const   unsigned        char    MASTCALL[]={
   0x00,0x00,
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x7F,0x02,0x0C,0x02,0x7F,  // M  29
   0x00,    
   0x46,0x49,0x49,0x49,0x31,  // S  35
   0x00,    
   0x01,0x01,0x7F,0x01,0x01, // T  36
   0x00,    
   0x00,0x08,0x08,0x08,0x00,  // -  
   0x00,    
   0x3E,0x41,0x41,0x41,0x22,  // C  19
   0x00,    
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00,    
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,    
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,0x00,0x00 
};
*/

const   unsigned        char    STOP1[]={
   0x00,0x00,
/*
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
*/
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
/*
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
*/
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


/*
const   unsigned        char    ARRIVAL[]={
   0x00,0x00,
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00,   
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00,   
   0x7F,0x09,0x19,0x29,0x46,  // R  30
   0x00,
   0x00,0x41,0x7F,0x41,0x00,  // I  25
   0x00, 
   0x1F,0x20,0x40,0x20,0x1F,  // V  38
   0x00, 
   0x7E,0x11,0x11,0x11,0x7E,  // A  17
   0x00, 
   0x7F,0x40,0x40,0x40,0x40,  // L  28
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,0x00,0x00 
};



const   unsigned        char    DOOR_OPEN[]={
   0x00,0x00,
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,    // D  20
   0x00,   
   0x3E,0x41,0x41,0x41,0x3E, 	// O  31
   0x00,   
   0x3E,0x41,0x41,0x41,0x3E, 	// O  31
   0x00,
   0x7F,0x09,0x19,0x29,0x46,    // R  30
   0x00, 
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, 	// O  31
   0x00, 
   0x7F,0x09,0x09,0x09,0x06,    // P  32
   0x00, 
   0x7F,0x49,0x49,0x49,0x41,    // E  21
   0x00, 
   0x7F,0x04,0x08,0x10,0x7F,    // N  30
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,0x00,0x00 
};
*/


const   unsigned        char    RollingP[]={
   0x00,0x00,
/*
   0x00,0x08,0x08,0x08,0x00,  //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,  //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,  //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
*/
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

/*
   0x00,0x00,0x00,0x00,0x00,  //space
   0x00,
   0x00,0x00,0x00,0x00,0x00,    //space
*/
   0x00,0x00,0x00 
};


/*
const   unsigned        char    NOSERVICE[]={
   0x00,0x00,
   0x00,0x08,0x08,0x08,0x00,    //-  
   0x00,
   0x7F,0x41,0x41,0x22,0x1C,    //D  
   0x00,
   0x7F,0x08,0x14,0x22,0x41,    //K  35
   0x00,
   0x00,0x00,0x00,0x00,0x00,    //space
   0x00,
   0x3E,0x41,0x41,0x41,0x3E, 	// O  31
   0x00,
   0x3F,0x40,0x40,0x40,0x3F,  	// U  37
   0x00,    
   0x01,0x01,0x7F,0x01,0x01, 	// T  36
   0x00,
   0x00,0x00,0x00,0x00,0x00,    //space
   0x00,    
   0x3E,0x41,0x41,0x41,0x3E, 	// O  31
   0x00,    
   0x7F,0x09,0x09,0x09,0x01,    // F
   0x00,
   0x00,0x00,0x00,0x00,0x00,    //space
   0x00,    
   0x46,0x49,0x49,0x49,0x31,    // S  35
   0x00,    
   0x7F,0x49,0x49,0x49,0x41,    // E  21
   0x00,    
   0x7F,0x09,0x19,0x29,0x46,    // R  30
   0x00,    
   0x1F,0x20,0x40,0x20,0x1F,    // V  38
   0x00, 
   0x00,0x41,0x7F,0x41,0x00,  	// I  25
   0x00,
   0x3E,0x41,0x41,0x41,0x22, 	// C  19
   0x00,    
   0x7F,0x49,0x49,0x49,0x41,    // E  21
   0x00,
   0x00,0x00,0x00,0x00,0x00,    //space
   0x00,0x00,0x00 
};
*/


bit	Alarm=0;
bit	NoRunErr=0;
//bit	ArrivalFlow=0;
//bit	DoorOpenSig=0;
bit	Rolling=0;
bit Co2Foam=0; 
///////////////
bit carbd=0;



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

/*
    if((RcvBuf[IdPt+DSP1] == 'J') && (RcvBuf[IdPt+DSP2] == 'D') && !(RcvBuf[IdPt+1] & S1_AUTO))  SetupBit=1;
    else                                                                                         SetupBit=0;      

    if(SetupBit)    return(0);
*/


    TopFloor=RcvBuf[IdPt + SL_mTopFlr];

    CurFloor=RcvBuf[IdPt];





 
////////////////dot type dsp hib,hpi////////////////////////////////////////////
#if defined(__DSP_DOT)
    if((CurFloor > BefCurFloor) || (CurFloor < BefCurFloor)){
        FloorChange=1;   
        BefCurFloor=CurFloor;
/////        shift=0;
    }


    Floor_Char_load(0,RcvBuf[IdPt+DSP1],RcvBuf[IdPt+DSP2]);

////////////////dot type es15////////////////////////////////////////////
#elif defined(__TYPE_ES15)

#if defined(__TYPE_DIRECT)

	switch(RcvBuf[IdPt])
	{
		case	1:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=0;
			BCD4_LAMP=0;
			break;
		case	2:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=0;
			break;
		case	3:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=0;
			break;
		case	4:
			BCD1_LAMP=0;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	5:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	6:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	7:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=0;
			break;
		case	8:
			BCD1_LAMP=0;
			BCD2_LAMP=0;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	9:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	10:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	11:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=0;
			BCD4_LAMP=1;
			break;
		case	12:
			BCD1_LAMP=0;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	13:
			BCD1_LAMP=1;
			BCD2_LAMP=0;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	14:
			BCD1_LAMP=0;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
		case	15:
			BCD1_LAMP=1;
			BCD2_LAMP=1;
			BCD3_LAMP=1;
			BCD4_LAMP=1;
			break;
	}	



	DOOR_OPEN_LAMP= !Open;
	PARKING_LAMP= !Parking;
	MANUAL_LAMP=  !Auto;
	EMG_LAMP_B=   Emg;
	EMG_LAMP  =   !Emg;

#else

/*
   if(RcvBuf[IdPt+DSP1] == 'B')      dsplamp0 = 0x1f;   
   else if(RcvBuf[IdPt+DSP1] == '1') dsplamp0 = 0x06;
   else if(RcvBuf[IdPt+DSP1] == '2') dsplamp0 = 0x0b;
   else if(RcvBuf[IdPt+DSP1] == '3') dsplamp0 = 0x07;
   else                              dsplamp0 = 0x0;
   
    BefCurFloor=(P2 & 0xe0);
    BefCurFloor=(dsplamp0 | BefCurFloor);
    P2=BefCurFloor;

   BefCurFloor=RcvBuf[IdPt+DSP2] - '0';
   dsplamp1=seg0[BefCurFloor];
   if((dsplamp0==0) && (BefCurFloor==1)){
      dsplamp1=0x30;
   }
   else if(RcvBuf[IdPt+DSP2] == 'F'){
      dsplamp1=F_SEG;
   }

   if((RcvBuf[IdPt+3] & S3_PARKING)){
        dsplamp0 = 0x0;
        dsplamp1=P_SEG;
   }


   P0=dsplamp1;

*/


/*
	switch(RcvBuf[IdPt])
	{
		case	1:
			dsplamp1=0x01;
			break;
		case	2:
			dsplamp1=0x02;
			break;
		case	3:
			dsplamp1=0x04;
			break;
		case	4:
			dsplamp1=0x08;
			break;
		case	5:
			dsplamp1=0x10;
			break;
		case	6:
			dsplamp1=0x20;
			break;
		case	7:
			dsplamp1=0x40;
			break;
	}	


   	if(RcvBuf[IdPt+3] & S3_SHIFT)            dsplamp1=(dsplamp1 | 0x80);
	P0=dsplamp1;



	dsplamp0 = 0x0;

	if((RcvBuf[IdPt+3] 	& S3_PARKING))      dsplamp0=(dsplamp0 | 0x10); //parking
	if(RcvBuf[IdPt+3] 	& S3_STOP)          dsplamp0=(dsplamp0 | 0x02); //water
	if(RcvBuf[IdPt + 24] & 0x20)      		dsplamp0=(dsplamp0 | 0x04); //error  


    if((RcvBuf[IdPt+3] & S3_OPEN_SUB) && (RcvBuf[IdPt+2] 	& S2_FIRE))	dsplamp0=(dsplamp0 | 0x01); //fire      
    if((RcvBuf[IdPt+1] & S1_OPEN)     && (RcvBuf[IdPt+2] 	& S2_FIRE))	dsplamp0=(dsplamp0 | 0x01); //fire      


    BefCurFloor=(P2 & 0xe0);
    BefCurFloor=(dsplamp0 | BefCurFloor);
    P2=BefCurFloor;

*/



#endif


   if(RcvBuf[IdPt+3] & S3_FULL)             FULL_LAMP=1;
   else                                     FULL_LAMP=0;


/*
   if(RcvBuf[IdPt+3] & S3_SHIFT)             FULL_LAMP=1;
   else                                     FULL_LAMP=0;
*/

//   if(RcvBuf[IdPt+1] & S1_UP)               UP_LAMP=1;
//   else                                     UP_LAMP=0;

   if(RcvBuf[IdPt+2] & S2_DN)               DN_LAMP=1;
   else                                     DN_LAMP=0;

#else
    #error Not Select Board Dsplay Type -- error
#endif




    Open=0;

	if(bIamXSubDoor){
        if((RcvBuf[IdPt+3] & S3_OPEN_SUB))  Open=1;   
    }
    else{
        if(RcvBuf[IdPt+1] & S1_OPEN)        Open=1;   
    }    


   Close=0;
   if((RcvBuf[IdPt+1] & S1_CLOSE)){
      Close=1;   
   }


   CarMove=0;
   if(RcvBuf[IdPt+2] & S2_CAR_MOVE)         CarMove=1;


	AUTO_LAMP=0;
   if(RcvBuf[IdPt+2] & S2_LAMP_USER)        AUTO_LAMP=1;
//   else                                     AUTO_LAMP=0;

   MANUAL_LAMP=0;
   if(((RcvBuf[IdPt+DEST_FLR] & ONLY_FLR) == (MyAddress-1)) && (CurFloor  == MyAddress)){
   		if(RcvBuf[IdPt+1] & S1_MANUAL)	           MANUAL_LAMP=1;
	}
	
//   else                                     MANUAL_LAMP=0;

   UpMove=0;
   if(RcvBuf[IdPt+1] & S1_UP)               UpMove=1;
//   else                                     UpMove=0;

   DnMove=0;
   if(RcvBuf[IdPt+2] & S2_DN)               DnMove=1;
//   else                                     DnMove=0;

   Vip=0;
   if((RcvBuf[IdPt+3] & S3_VIP))            Vip=1;
//   else                                     Vip=0;

   Parking=0;
   if((RcvBuf[IdPt+3] & S3_PARKING))        Parking=1;
//   else                                     Parking=0;

   ShiftOn=0;
   if((RcvBuf[IdPt+3] & S3_SHIFT))          ShiftOn=1;
//   else                                     ShiftOn=0;
   
   Fire=0;
   if(RcvBuf[IdPt+2] & S2_FIRE)             Fire=1;
//   else                                     Fire=0;

   KeyClrExt=0;
   if(RcvBuf[IdPt+2] & S2_EXT_BUT_CLR)      KeyClrExt=1;
//   else                                     KeyClrExt=0;

   KeyClr=0;
   if(RcvBuf[IdPt+2] & S2_CAR_BUT_CLR)      KeyClr=1;
//   else                                     KeyClr=0;

   
	Emg=0;
   if(RcvBuf[IdPt+1] & S1_EMG)              Emg=1;
//   else                                     Emg=0;

   StopBit=0;
   Co2Foam=0;	
   	if(RcvBuf[IdPt+3] & S3_STOP){
		if(RcvBuf[IdPt+4] & S4_FAMILY_SERVICE)	Co2Foam=1;  //foam
		else									StopBit=1;  //Co2
	}


	CurKey=0;
   if(RcvBuf[IdPt+3] & S3_CURKEY)           CurKey=1;
//   else                                     CurKey=0;
         
	Auto=0;
   if(RcvBuf[IdPt+1] & S1_AUTO)             Auto=1;
//   else                                     Auto=0;


	OverLoad=0;
   if(RcvBuf[IdPt+1] & S1_OVERLOAD)         OverLoad=1;

//   else                                     OverLoad=0;

	Full=0;
   if(RcvBuf[IdPt+3] & S3_FULL)             Full=1;
//   else                                     Full=0;



/*
    ArrivalFlow=0;
	if(Auto){
   		if((MyAddress-1) == (RcvBuf[IdPt + DEST_FLR] & ONLY_FLR)){
//			if(RcvBuf[IdPt+2] & S2_FLOW){
//   		if( ((RcvBuf[IdPt + DEST_FLR] & ONLY_FLR) == (CurFloor-1))){
//   		if(RcvBuf[IdPt+23] & 0x80){
	 				ArrivalFlow=1;
			}
		}
	}
*/


//	NoRunErr=0;
//   	if( (RcvBuf[IdPt+24] & 0x20) || !Auto)              NoRunErr=1;

//	Alarm=0;
//   	if( !(RcvBuf[IdPt+35] & 0x04))             			Alarm=1;

//	DoorOpenSig=0;
//   	if(Auto && Open){
//		if((RcvBuf[IdPt+25] & 0xc0) != 0x0)			DoorOpenSig=1;
//	}


/*
    ArrivalFlow=0;
//you

	if(Auto && !DoorOpenSig && CarMove){
   		if((MyAddress-1) == (RcvBuf[IdPt + DEST_FLR] & ONLY_FLR)){
			if( MyAddress == CurFloor){
				if(RcvBuf[IdPt+4] & S4_ARRIVE){
					ArrivalFlow=1;
				}
			}
		}
	}

//you
*/


	Rolling=0;
   	if(RcvBuf[IdPt+4] & 0x80)					Rolling=1;


	carbd=0;


/////////////////
//woosio lamp 

	dsplamp0=0;
	dsplamp1=0;

/*
	if(Rolling)  								dsplamp1= (dsplamp1 | 0x01);   // rollin & pitching
	else										dsplamp1= (dsplamp1 & 0xfe);

	if(Fire)  									dsplamp1= (dsplamp1 | 0x02);	// fire
	else										dsplamp1= (dsplamp1 & 0xfd);

	if(StopBit)  								dsplamp1= (dsplamp1 | 0x04);  	//CO2
	else										dsplamp1= (dsplamp1 & 0xfb);  	//CO2

	if(Co2Foam)  								dsplamp1= (dsplamp1 | 0x08);	//FOAM	
	else										dsplamp1= (dsplamp1 & 0xf7);	//FOAM

	if(RcvBuf[S1_STATE] & S1_MANUAL)			dsplamp1= (dsplamp1 | 0x10);    //mastercall
	else										dsplamp1= (dsplamp1 & 0xef);

   	if( !(RcvBuf[IdPt+35] & 0x04))             	dsplamp1= (dsplamp1 | 0x20);  	// alarm
	else										dsplamp1= (dsplamp1 & 0xdf);  	// alarm

	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_UP)  	dsplamp1= (dsplamp1 | 0x40);  	// arrival
	else										dsplamp1= (dsplamp1 & 0xbf);

	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_DN)  	dsplamp1= (dsplamp1 | 0x80);  	// door open
	else										dsplamp1= (dsplamp1 & 0x7f);

	P0=dsplamp1;


	if(RcvBuf[S2_STATE] & S2_LAMP_USER)			UP_LAMP=1;					  // no service
	else										UP_LAMP=0;
*/

	if(Rolling)  								dsplamp1= (dsplamp1 | 0x01);   // rollin & pitching
	else										dsplamp1= (dsplamp1 & 0xfe);

	if(Fire)  									dsplamp1= (dsplamp1 | 0x02);	// fire
	else										dsplamp1= (dsplamp1 & 0xfd);

	if(StopBit || Co2Foam)  					dsplamp1= (dsplamp1 | 0x04);  	//CO2 ,Foam
	else										dsplamp1= (dsplamp1 & 0xfb);  	//CO2

   	if( !(RcvBuf[IdPt+35] & 0x04))             	dsplamp1= (dsplamp1 | 0x08);  	// alarm
	else										dsplamp1= (dsplamp1 & 0xf7);  	// alarm

	if(RcvBuf[S1_STATE] & S1_MANUAL)			dsplamp1= (dsplamp1 | 0x10);    //mastercall
	else										dsplamp1= (dsplamp1 & 0xef);

   	if( RcvBuf[S2_STATE] & S2_LAMP_USER)        dsplamp1= (dsplamp1 | 0x20);  	// no service
	else										dsplamp1= (dsplamp1 & 0xdf);  	// no service

	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_UP)  	dsplamp1= (dsplamp1 | 0x40);  	// arrival
	else										dsplamp1= (dsplamp1 & 0xbf);

	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_DN)  	dsplamp1= (dsplamp1 | 0x80);  	// door open
	else										dsplamp1= (dsplamp1 & 0x7f);

	P0=dsplamp1;





/*
	if(RcvBuf[S1_STATE] & S1_MANUAL)			dsplamp1= (dsplamp1 | 0x02);
	else										dsplamp1= (dsplamp1 & 0xfd);
	if(RcvBuf[S2_STATE] & S2_LAMP_USER)			dsplamp1= (dsplamp1 | 0x01);
	else										dsplamp1= (dsplamp1 & 0xfe);
	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_UP)  	dsplamp1= (dsplamp1 | 0x04);
	else										dsplamp1= (dsplamp1 & 0xfb);
	if(RcvBuf[S4_STATE] & S4_HALLLANTERN_DN)  	dsplamp1= (dsplamp1 | 0x08);
	else										dsplamp1= (dsplamp1 & 0xf7);

	if(Fire)  									dsplamp1= (dsplamp1 | 0x10);
	else										dsplamp1= (dsplamp1 & 0xef);

	if(StopBit)  								dsplamp1= (dsplamp1 | 0x20);  //CO2
	else										dsplamp1= (dsplamp1 & 0xdf);  //CO2

	if(Rolling)  								dsplamp1= (dsplamp1 | 0x40);
	else										dsplamp1= (dsplamp1 & 0xbf);

	if(Co2Foam)  								dsplamp1= (dsplamp1 | 0x80);	//FOAM	
	else										dsplamp1= (dsplamp1 & 0xef);	//FOAM

	P0=dsplamp1;


   	if( !(RcvBuf[IdPt+35] & 0x04))             	UP_LAMP=1;  // alarm
	else										UP_LAMP=0;  // alarm
*/
    BefCurFloor=(P2 & 0xe0);
    BefCurFloor=(dsplamp0 | BefCurFloor);
    P2=BefCurFloor;
/////////////////


#if defined(__TYPE_CAR)
//   	OpenLampSet=0;
//   	if(RcvBuf[IdPt+2] & S2_OPEN_LAMP_ON)      	OpenLampSet=1;

	Alarm=0;
   	if( !(RcvBuf[IdPt+35] & 0x04))             			Alarm=1;

//	DoorOpenSig=0;
//    ArrivalFlow=0;
//	NoRunErr=0;

	if(Vip)	KeyClr=1;

	carbd=1;

#endif

#if defined(__TYPE_HIB_HPI )
		OverLoad=0;
		Alarm=0;
//		if(CurFloor  != MyAddress)	DoorOpenSig=0;
#endif


    return(0);

}






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
/*
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
*/
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



/*       
//   else if(Vip){
//      shift=(shift+1)%32;            
//      j=shift;
//      for(i=0;i<=10;i++){
//         if(j<21){ 
//            shiftDataBuf[i]=VIP[j];
//            j++;            
//         }
//         else{
//            shiftDataBuf[i]=DspBuf[j-21];
//            j++;  
//            if(j>31) j=0;                   
//         }            
//      }
//      ManualToggle=1;
//   }

*/



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
