
#include        "..\can_4480\you_can.h"
#include        "..\comm_4480\cpu18f4480.h"



#define		NEW_CAR			1
//#define		NEW_HIB_HPI		1
//#define		NEW_ES15		1
//#define		NEW_VOICE		1

//#define		OLD_CAR			1
//#define		OLD_HIB_HPI		1
//#define		OLD_ES15		1
//#define		OLD_VOICE		1



#if  defined(NEW_CAR)   ||  defined(NEW_HIB_HPI)
	#define		 	U_COMPILER		1
	#define		 	CPU65K80			1

	#if  defined(NEW_CAR)
		#define __TYPE_CAR			1      
	#elif   defined(NEW_HIB_HPI)
		#define __TYPE_HIB_HPI		1      
	#endif
#elif   defined(NEW_ES15) || defined(NEW_VOICE) 
	#define		 	U_COMPILER		1
	#define			CPU45K80		1

	#if  defined(NEW_ES15)
		#define __TYPE_ES15			1   
	#endif   

#elif   defined(OLD_CAR)
	#define __TYPE_CAR      
#elif   defined(OLD_HIB_HPI)
	#define __TYPE_HIB_HPI      
#elif   defined(OLD_ES15)
	#define __TYPE_ES15      
#endif


#if   defined(NEW_VOICE) 
	#define __TYPE_ES15			1   
#endif




//#define __TYPE_ES15     
//#define __TYPE_HIB_HPI      
//#define __TYPE_CAR      




//#define __TYPE_DIRECT

//#define __COUNT_CAR		1     
//#define		ONE_DSP		1




#define     EXT_VERSION     	0x00

#define     SUB_DOOR_BIT    	0x01
#define		HIB_PARKING_BIT 	0x02 
#define     HALL_SENSOR     	0x04
#define     IAM_SINGLE_MODE     0x08


//#define     CARD_KEY     1



//#define	CAN_IO				1
//#define	I_AM_FLOOR_ONOFF	1
//#define	I_AM_EXT_IO_ONOFF	1




#ifdef	CAN_IO 
	#ifndef	__TYPE_ES15 
	    #error  "__TYPE_ES15 Define Error(iodef.h)" 
	    #error  "__TYPE_ES15 Define Error(iodef.h)" 
	#endif


	#if  defined(I_AM_EXT_IO_ONOFF)   ||  defined(I_AM_FLOOR_ONOFF)
		#if    defined(I_AM_EXT_IO_ONOFF)   &&  defined(I_AM_FLOOR_ONOFF) 
		    #error  "Multiple Define Error(iodef.h)" 
		    #error  "Multiple Define Error(iodef.h)" 
		#endif
	#else
	    #error  "CAN_IO Define Error(iodef.h)" 
	    #error  "CAN_IO Define Error(iodef.h)" 
	#endif

#endif






#if     defined(__TYPE_ES15)    &&  defined(__TYPE_HIB_HPI) && defined(__TYPE_CAR)
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
#elif   defined(__TYPE_ES15)    &&  defined(__TYPE_HIB_HPI)
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
#elif   defined(__TYPE_ES15)    &&  defined(__TYPE_CAR)
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
#elif   defined(__TYPE_HIB_HPI) &&  defined(__TYPE_CAR)
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
    #error  "Multiple Define Error(iodef.h)" 
#endif





#if defined(__TYPE_HIB_HPI)

    #define  __DSP_DOT
   
/*
    #define  UP_KEY         RD0
    #define  DN_KEY         RD1
    #define  UP_KEY_SUB     RD7   
    
//    #define  WR_CLK         LATE2    
//    #define  IN_ACT         LATB1
    
    #define  UP_KEY_LAMP    LATB4
    #define  DN_KEY_LAMP    LATB5
    #define  AUTO_LAMP      LATB6
    #define  MANUAL_LAMP    LATB7            
    #define  HALL_LAMP_DN   LATB0
*/

#ifdef	CPU65K80

    #define  HIB_PARKING_KEY    PORTBbits.RB0

    #define  UP_KEY         RE0
    #define  DN_KEY         RE1
    #define  UP_KEY_SUB     RE2
       
    #define  HALL_LAMP_UP   LATE4
    #define  HALL_LAMP_DN   LATE5
    #define  UP_KEY_LAMP    LATE6
    #define  DN_KEY_LAMP    LATE7

    #define  MANUAL_LAMP    LATG1		//user lamp1
    #define  AUTO_LAMP    	LATG0		//user lamp2
    #define  USER_LAMP3     LATG2
    #define  USER_LAMP4     LATG3
           

    #define  P0             LATD
    #define  P1             LATC
    #define  P2             LATF


    #define  P10             LATC0
    #define  P11             LATC1
    #define  P12             LATC2
    #define  P13             LATC3
    #define  P14             LATC4
    #define  P15             LATC5
    #define  P16             LATC6
    #define  P17             LATC7

    #define  P20             LATF0
    #define  P21             LATF1
    #define  P22             LATF2
    #define  P23             LATF3
    #define  P24             LATF4
    #define  P25             LATF5
    #define  P26             LATF6
    #define  P27             LATF7
#else

    #define  UP_KEY         RD0
    #define  DN_KEY         RD1
    #define  UP_KEY_SUB     RD7   
    
    #define  WR_CLK         LATE2    
    #define  IN_ACT         LATB1
    
    #define  UP_KEY_LAMP    LATB4
    #define  DN_KEY_LAMP    LATB5
    #define  AUTO_LAMP      LATB6
    #define  MANUAL_LAMP    LATB7            
    #define  HALL_LAMP_DN   LATB0


    #define  P0             LATD
    #define  P1             LATA
    #define  P2             LATC

    #define  P10             LATA0
    #define  P11             LATA1
    #define  P12             LATA2
    #define  P13             LATA3
    #define  P14             LATA4
    #define  P15             LATA5
    #define  P16             LATE0
    #define  P17             LATE1

    #define  P20             LATC0
    #define  P21             LATC1
    #define  P22             LATC2
    #define  P23             LATC3
    #define  P24             LATC4
    #define  P25             LATC5
    #define  P26             LATC6
    #define  P27             LATC7
#endif;

#elif defined(__TYPE_ES15)
#ifdef	CAN_IO
	#define  IO_00         RD0
	#define  IO_01         RD1
	#define  IO_02         RD2
	#define  IO_03         RD3
	#define  IO_04         RD4
	#define  IO_05         RD5
	#define  IO_06         RD6
	#define  IO_07         RD7
		
	#define  IO_08         RC0
	#define  IO_09         RC1
	#define  IO_10         RC2
	#define  IO_11         RC3
	#define  IO_12         RC4

	#ifdef	CPU45K80
		#define  IO_13         PORTBbits.RB0     //RB0
		#define  IO_14         PORTBbits.RB1
	#else
		#define  IO_13         RB0     
		#define  IO_14         RB1
	#endif

	#define  IO_15         RB4
	
	#define  IO_16         RA0
	#define  IO_17         RA1
	#define  IO_18         RA2
	#define  IO_19         RA3
	#define  IO_20         RA4
	#define  IO_21         RA5
	#define  IO_22         RE0
	#define  IO_23         RE1
	
	#define  IO_24         RE2
	#define  IO_25         RC5
	#define  IO_26         RC6
	#define  IO_27         RC7
	#define  IO_28         RB6
	#define  IO_29         RB7
	#define  IO_30         RA7
	#define  IO_31         RA6
#else
	#if defined(__TYPE_DIRECT)
	    #define  UP_KEY         RB0  
	    #define  DN_KEY         RB0
  	    
	    #define  UP_KEY_LAMP    LATC6  
	    #define  DN_KEY_LAMP    LATC6  	    
	    #define  HALL_LAMP_UP   LATC6
	    #define  HALL_LAMP_DN   LATC6
	    #define  AUTO_LAMP      LATC6


	    #define  BCD1_LAMP      LATE0  //Y0
	    #define  BCD2_LAMP      LATE1  //Y1
	    #define  BCD3_LAMP      LATE2  //Y2
	    #define  BCD4_LAMP      LATC0  //Y3
	    #define  UP_LAMP        LATC1  //Y4 
	    #define  DN_LAMP        LATC2  //Y5
	    #define  DOOR_OPEN_LAMP LATC3  //Y6
	    #define  FULL_LAMP      LATD0  //Y7
	    #define  PARKING_LAMP   LATD1  //Y8
	    #define  MANUAL_LAMP    LATD2  //Y9
	    #define  EMG_LAMP_B   	LATD3  //Y10
	    #define  EMG_LAMP   	LATC4  //Y11
	#else
	    #define  NOT_KEY        RA5  
	    #define  NOT_KEY1       RE2  //RC5
	    #define  UP_KEY         RE1  //RC7
	    #define  DN_KEY         RE0  //RC6
	    
	    #define  UP_KEY_LAMP    LATC7  //LATE1
	    #define  DN_KEY_LAMP    LATC6  //LATE0
	    #define  UP_LAMP        LATC5  //LATE2
	    
	    #define  HALL_LAMP_UP   LATB0
	    #define  HALL_LAMP_DN   LATB1
	    #define  DN_LAMP        LATB4
	    #define  AUTO_LAMP      LATB5
	    #define  MANUAL_LAMP    LATB6
	    #define  FULL_LAMP      LATB7
	    
	    #define  P0             LATD  // 0000 0000 
	    #define  P2             LATC


	    #define  SEG_A          LATD0 
	    #define  SEG_B          LATD1 
	    #define  SEG_C          LATD2 
	    #define  SEG_D        	LATD3 
	    #define  SEG_E        	LATD4 
	    #define  SEG_F       	LATD5 
	    #define  SEG_G1       	LATD6 
	    #define  SEG_G2         LATD7
 

	    #define  SEG_adg        LATC0 
	    #define  SEG_b_S        LATC1 
	    #define  SEG_c_S        LATC2 
	    #define  SEG_e_S        LATC3 
	    #define  SEG_n12        LATC4 

	#endif

#endif


#elif defined(__TYPE_CAR)

    #define  __DSP_DOT

#ifdef	CPU65K80
    #define     DATA_PORT     LATD
    #define     IN_DATA_PORT  PORTD
    
    #define     SEL0          LATB0
    #define     SEL1          LATB1
    #define     SEL2          LATB4
    #define     SEL_ACT       LATB5
    #define  	MANUAL_LAMP   LATB6
    #define  	AUTO_LAMP     LATB7
            

    #define     TOGGLE        RA0
    #define     DIPS2         RA2
    #define     DIPS3         RA1
    #define     MULTI_ADR0    RA3
    #define     MULTI_ADR1    RA5

    
    #define     OPEN_KEY       RG0
    #define     OPEN_LAMP     LATG1
    #define     CLOSE_KEY      RG2
    #define     CLOSE_LAMP    LATG3
    #define     BELL          LATG4
                    



////    #define     NO_USE1       RB4
////    #define     LIVE_LAMP     LATC7  
////    #define     P1            LATC    
////    #define     DSP_OFF        LATA4
/////   #define     WR_CLK         LATA5    
///    #define     P2             LATA


//    #define  UP_KEY_LAMP        RE2     
//    #define  DN_KEY_LAMP        RE2
//    #define  HALL_LAMP_UP       RE2
//    #define  HALL_LAMP_DN       RE2


#else
    #define     DATA_PORT     LATD
    #define     IN_DATA_PORT  PORTD
    #define     P1            LATC
    
    #define     SEL0          LATC0
    #define     SEL1          LATC1
    #define     SEL2          LATC2
    #define     SEL_ACT       LATC3

    #define     BELL          LATC4  
    #define     DIPS2         RC5
    #define     DIPS3         RC6
    #define     LIVE_LAMP     LATC7  
            
    #define     MULTI_ADR0    RB0
    #define     MULTI_ADR1    RB1
    
    #define     NO_USE1       RB4
    #define     TOGGLE        RB5
    #define     OPEN_LAMP     RB6   //LATC5
    #define     CLOSE_LAMP    RB7   //LATC6
                    
    
    #define     DSP_OFF        LATA4
    #define     WR_CLK         LATA5
    
    #define     OPEN_KEY       RE0
    #define     CLOSE_KEY      RE1
    
    #define     P2             LATA


    #define  UP_KEY_LAMP        RE2     //not use
    #define  DN_KEY_LAMP        RE2
    #define  AUTO_LAMP          RE2
    #define  MANUAL_LAMP        RE2
    #define  HALL_LAMP_UP       RE2
    #define  HALL_LAMP_DN       RE2
#endif

#else
    #error   "Type Not Define"

#endif












//#define     VIP_TEMP   1

