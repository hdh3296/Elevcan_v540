/***************************************************************************/
/* DS1302.C                                                                */
/***************************************************************************/
//sbit IO   = P0^2;
//sbit SCLK = P0^1;
//sbit RSTB = P0^0;
/***************************************************************************/
/* Prototypes                                                              */
/***************************************************************************/

#include <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"


void	        clkwritebyte(void);
void	        ramwritebyte(void);
void	        reset_3w(void);
void	        wbyte_3w(UserDataType W_Byte);
void	        Initialize_DS1302(void);
void	        disp_clk_regs(void);
void	        burstramrd(void);
void	        burstramwr(void);
UserDataType    rbyte_3w(void);

UserDataType	R_Byte = 0x00;

/* ----------------------------------------------------------------------- */
void reset_3w(void)
{
    SCLK = 0;
    SCLK = 0;
    SCLK = 0;
    SCLK = 0;
    RSTB = 0;
    RSTB = 0;
    RSTB = 0;
    RSTB = 0;

    RSTB = 1;
    RSTB = 1;
    RSTB = 1;
    RSTB = 1;
    RSTB = 1;
    RSTB = 1;
    RSTB = 1;
    RSTB = 1;
}
/* ----------------------------------------------------------------------- */

void wbyte_3w(UserDataType W_Byte)
{
    unsigned int i;
    
	for(i = 0; i < 8; ++i)
	{        
		SDA = 0;
		if(W_Byte & 0x01)
		{
			SDA = 1;	/* set port pin high to read data */
		}
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;

		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;

		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		W_Byte >>= 1;
      }
}

/* ----------------------------------------------------------------------- */
UserDataType rbyte_3w(void)
{
    unsigned int i;

    TRISG = (TRISG | 0x0008);

	R_Byte = 0x00;

	for(i=0; i<8; ++i)
	{
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;
		SCLK = 1;

		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;
		SCLK = 0;

		R_Byte = R_Byte >> 1; 
        
        if(IN_DATA){
          R_Byte= R_Byte | 0x80;
        }
	}

    TRISG = (TRISG & 0xfff7);

	return R_Byte;
}

/* ----------------------------------------------------------------------- */
void clkwritebyte(void)
{
//    unsigned char ClkAdd;
//    unsigned char ClkData;

	/* Get Clock Address & Data */
//	printf("\nWrite Clock ADDRESS:");
//	scanf("%bu", &ClkAdd);
//	printf("\nWrite Clock DATA:");
//	scanf("%bx", &ClkData);

	/* Prepare Command Byte for Clock Write */
//	ClkAdd = ((ClkAdd * 2) | 0x80);

//	reset_3w();
//	wbyte_3w(ClkAdd);
//	wbyte_3w(ClkData);
//	reset_3w();
}
/* ----------------------------------------------------------------------- */

void ramwritebyte(void)
{
//    unsigned char ramadd;
//    unsigned char ramdata;

//	/* Get Ram Address & Data */
//	printf("\nWrite Ram ADDRESS (HEX):");
//	scanf("%bx", &ramadd);
//	printf("\nWrite Ram DATA (HEX):");
//	scanf("%bx", &ramdata);

	/* Prepare Command Byte for Ram Write */
//	ramadd = ((ramadd * 2) | 0xC0);

//	reset_3w();
//	wbyte_3w(ramadd);
//	wbyte_3w(ramdata);
//	reset_3w();
}


void disp_clk_regs(void)
{
	reset_3w();

	wbyte_3w(0xBF);	/* clock burst */
    sRamDArry[sec] = rbyte_3w();
    sRamDArry[Minuate] = rbyte_3w();
    sRamDArry[Hour] = rbyte_3w();
    sRamDArry[Day] = rbyte_3w();
    sRamDArry[Month] = rbyte_3w();
    rbyte_3w();    ///day
    sRamDArry[Year]  = rbyte_3w();

	reset_3w();
}


/* ----------- read RAM in burst mode --------------- */

/*
void burstramrd(void)	
{
    unsigned char rmary[31];
    unsigned char i;

	reset_3w();
	wbyte_3w(0xFF);	
	for (i=0; i<31; ++i)
	{
		rmary[i] = rbyte_3w();
	}
	reset_3w();

	printf("\nDS1302 Ram");

	printf("\n%2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX",
	rmary[0], rmary[1], rmary[2], rmary[3], rmary[4], rmary[5], rmary[6], rmary[7]);
	printf("\n%2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX",
	rmary[8], rmary[9], rmary[10], rmary[11], rmary[12], rmary[13], rmary[14], rmary[15]);
	printf("\n%2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX",
	rmary[16], rmary[17], rmary[18], rmary[19], rmary[20], rmary[21], rmary[22], rmary[23]);
	printf("\n%2.bX %2.bX %2.bX %2.bX %2.bX %2.bX %2.bX",
	rmary[24], rmary[25], rmary[26], rmary[27], rmary[28], rmary[29], rmary[30]);
}
*/

/* ------ write one value to entire array --------- */
void burstramwr(void)	
{
//    unsigned char ramdata;
//    unsigned char	i;

//	/* Get Ram Data */
//	printf("\nWrite Ram DATA (HEX):");
//	scanf("%bx", &ramdata);

//	reset_3w();
//	wbyte_3w(0xfe);	/* RAM burst write */
//	for (i=0; i<31; ++i)
//	{
//		wbyte_3w(ramdata);
//	}
//	reset_3w();
}


void Initialize_DS1302(void)	/* ----------------------------------------- */
{

//    unsigned char	yr, mn, date, dy, hr, min, sec, day;

//	printf("\nEnter the year (0-99): ");
//	scanf("%bx", &yr);
//	printf("\nEnter the month (1-12): ");
//	scanf("%bx", &mn);
//	printf("\nEnter the date (1-31): ");
//	scanf("%bx", &date);
//	printf("\nEnter the day (1-7): ");
//	scanf("%bx", &dy);
//	printf("\nEnter the hour (1-24): ");
//	scanf("%bx", &hr);
//	hr = hr & 0x3f;	/* force clock to 24 hour mode */
//	printf("\nEnter the minute (0-59): ");
//	scanf("%bx", &min);
//	printf("\nEnter the second (0-59): ");
//	scanf("%bx", &sec);

	sRamDArry[sec]      =0x00;
	sRamDArry[Minuate]  =0x00;
	sRamDArry[Hour]     =0x06;
	sRamDArry[Day]      =0x12;
	sRamDArry[Month]    =0x04;
//	dy;
	sRamDArry[Year]     =0x05;


	reset_3w();
	wbyte_3w(0x8e);	/* control register */
	wbyte_3w(0);	/* disable write protect */
	reset_3w();
	wbyte_3w(0x90);	/* trickle charger register */
	wbyte_3w(0xab);	/* enable, 2 diodes, 8K resistor */
	reset_3w();
	wbyte_3w(0xbe);	/* clock burst write (eight registers) */

	wbyte_3w(sRamDArry[sec]);
	wbyte_3w(sRamDArry[Minuate]);
	wbyte_3w(sRamDArry[Hour]);
	wbyte_3w(sRamDArry[Day]);
	wbyte_3w(sRamDArry[Month]);
	wbyte_3w(0x03);
	wbyte_3w(sRamDArry[Year]);
	wbyte_3w(0);		/* must write control register in burst mode */
	reset_3w();
}


/*
main (void)		
{
uchar i, M, M1;

	while (1)
	{ 
	printf("\nDS1302\n");
	printf("I. initialize DS1302\n");
	printf("CW. Write Byte  CR. Read Time\n");
	printf("RW. Write RAM   RR. Read RAM\n");
	printf("\nEnter Menu Selection:");

	M = _getkey();

	switch(M) 
	{
		case 'C':
		case 'c':
		printf("\rEnter Clock Routine to run:C");
		M1 = _getkey();

		switch(M1) 
            {
			case 'R':
			case 'r':	disp_clk_regs(1);	break;

	            case 'W':
      	      case 'w':	clkwritebyte();	break;
		}
		break;

		case 'I':
		case 'i':	initialize_DS1302();	break;

		case 'R':
		case 'r':
		printf("\rEnter Ram Routine to run:R");
		M1 = _getkey();

		switch(M1) 
		{
		case 'B':
		case 'b':	ramwritebyte();	break;
		case 'R':
		case 'r':	burstramrd();	break;
		case 'W':
		case 'w':	burstramwr();	break;
		}
		break;
	}
   }
}

*/
