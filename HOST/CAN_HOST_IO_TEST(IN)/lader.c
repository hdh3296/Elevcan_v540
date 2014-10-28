
#include <p30f6010.h>            
#include  "30f6010_io.h"            
#include  "..\..\system_com\memory_map.h"
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"
#include  "you_can1.h" 
#include  "you_can2.h" 
#include  "lader.h" 



#define F_LINE_START_PT     5
#define S_LINE_START_PT     22
#define PULL_DOWN_MENU      100
#define LEFT_MENU_MAX       200

const unsigned char StatusMessage[][16]={
                                      "INSPECTION STOP ",                                      
                                      "INV FLOOR ERROR ",                                      
                                      "EMERGENCY STOP  ",                                      
                                      "LOPE BREAK      ",                                      
                                      "SLIP STOP       ",                                      
                                      "ULS STOP        ",                                                                            
                                      "DLS STOP        ",                                      
                                      "LULD OFF STOP   ", 
                                      "NEXT FLOOR STOP ", 
                                      "DEST FLOOR STOP ",
                                      "NO HOLE DOOR SW ",
                                      "NO CLOSE END    ",
                                      "HOLE DOOR STOP  ",
                                      "CLOSE END STOP  ",
                                      "LULD ERROR      ",
                                      "OVER LOAD STOP  ",
                                      "PARKING MODE    ",
                                      "FIRE SUBWAY     ",
                                      "WATER_ON SUBWAY ",                                        
                                      "NO OPEN END     ",
                                      "DOOR JUMPER     ",                                                                            
                                      "VIP DRIVE       ",                                      
                                      "FHM_MODE        ",                                      
                                      "MANUAL UP       ",
                                      "MANUAL DN       ",
                                      "MANUAL MODE     ",
                                      "SAFETY OPEN     ",
                                      "OPEN DOOR       ",
                                      "CLOSE DOOR      ",                                      
                                      "AUTO UP         ",                                      
                                      "AUTO DN         ",                                      
                                      "SLOW SPEED      ",
                                      "WAIT LULD       ",
                                      "AUTO STOP       ",
                                      "WAIT... HOME !  ",
                                      "AUTO READY      ",
                                    };                                       


const unsigned char SetFlrMessage[][16]={
                                    "TOP-FLOOR SET   ",//3
                                    "PARKING-FL SET  ",//4
					                "FIRE SAFE FLR   ",//5
                                    "DISPLAY-SET(    ",//6
                                    "OPEN WAIT TIME  ",//7
                                    "OPEN TOTALTIME  ",//8
                                    "USER LAMP SET   ", //9                                                                           
                                    "INSPECTION SET  ",//a
                                    "FIX FLR SET     ",//b
                                    "FIX FLR TIME    ",//c
                                    "NO STOP FLR(    ",//d
                                    "MOVE COUNTER    ",//e                                   
                                    "                ",//f
                                    "FHM START       ",//h                                    
                                    "                ",//i                                     
                                    "                ",//j                                                                         
                                    "ERROR COUNTE    ",//k                                    
                                    "NEXT FLR TIME   ",//l                                    
                                    "NC-NO(          ",//n                                    
					                "SUB DOOR1 FLR   ",//o
					                "SUB DOOR2 FLR   ",//p
					                "SUB DOOR3 FLR   ",//q
					                "NEW PASSWARD    ",//r
					                "SERIAL NUMBER   ",//s
                                    "ERR STOP CNT    ",//g                                    
                                    "M R/W DATA      ",//t
                                    "L R/W DATA      ",//u
                                    };                                       




unsigned int Ladder_mode=0;


void    __attribute__((section(".usercode"))) FirstLineClear(void)
{
    unsigned int    i;
    for(i=0;i<16;i++)   RxBuffer2[F_LINE_START_PT + i]=' ';       
}

void    __attribute__((section(".usercode"))) SecondLineClear(void)
{
    unsigned int    i;
    for(i=0;i<16;i++)   RxBuffer2[S_LINE_START_PT + i]=' ';       
}


void    __attribute__((section(".usercode"))) SetFlrDsp(void)
{
    unsigned int    i;
    unsigned int    pt;


    pt=Ladder_mode%100;

    FirstLineClear();

    for(i=0;i<16;i++){
        RxBuffer2[F_LINE_START_PT + i]=SetFlrMessage[pt][i];       
    }
}


void    __attribute__((section(".usercode"))) TopDataTx(void)
{
    unsigned int    i,j;

    SecondLineClear();
    j=cF_TOPFLR;

    RxBuffer2[S_LINE_START_PT + 0]=(j/10)+'0';       
    RxBuffer2[S_LINE_START_PT + 1]=(j%10)+'0';       
}




void    __attribute__((section(".usercode"))) CurFlrDsp(void)
{
    RxBuffer2[5]  = 'F';                            //1
    RxBuffer2[6]  = 'l';                            //2
    RxBuffer2[7]  = 'r';                            //3
    RxBuffer2[8]  = ' ';                            //4
	RxBuffer2[9]  = sRamDArry[DSP1];                //5
	RxBuffer2[10] = sRamDArry[DSP2];                //6
	RxBuffer2[11] = ' ';
	RxBuffer2[12] = ' ';
}


void    __attribute__((section(".usercode"))) TestDsp(void)
{

    if(TestDip == 0x08){            
        RxBuffer2[4]  = '0';
        RxBuffer2[5]  = ' ';                     //1
    }
    else{            
        RxBuffer2[4]  = '1';
        RxBuffer2[5]  = ' ';                     //1
    }

    if(TestIO >= 100){
        RxBuffer2[6]  = 'I';                     //2
        RxBuffer2[7]  = 'O';                     //3
        RxBuffer2[8]  = ' ';                     //4
    	RxBuffer2[9]  = 'O';                     //5
    	RxBuffer2[10] = 'K';                     //6
    	RxBuffer2[11] = '!';                     //7
    	RxBuffer2[12] = ' ';                     //8
    }
    else{
        RxBuffer2[6]  = 'W';                     //2
        RxBuffer2[7]  = 'a';                     //3
        RxBuffer2[8]  = 'i';                     //4
    	RxBuffer2[9]  = 't';                     //5
    	RxBuffer2[10] = 'I';                     //6
    	RxBuffer2[11] = 'O';                     //7
    	RxBuffer2[12] = ' ';                     //8
    }    

    if((TestCan1 >= 200) && (TestCan2 >= 200)){
    	RxBuffer2[13] = 'C';                     //9
    	RxBuffer2[14] = 'A';                     //10
    	RxBuffer2[15] = 'N';                     //11
    	RxBuffer2[16] = ' ';                     //12
    	RxBuffer2[17] = 'O';                     //13 
    	RxBuffer2[18] = 'K';                     //14
    	RxBuffer2[19] = '!';                     //15 
    }
    else{
    	RxBuffer2[13] = 'W';                     //9
    	RxBuffer2[14] = 'a';                     //10
    	RxBuffer2[15] = 'i';                     //11
    	RxBuffer2[16] = 't';                     //12
    	RxBuffer2[17] = 'C';                     //13 
    	RxBuffer2[18] = 'a';                     //14
    	RxBuffer2[19] = 'n';                     //15 
    }


    if(Test485 >= 100){
        RxBuffer2[20] = '4';
        RxBuffer2[21] = '8';                     //1
        RxBuffer2[22] = '5';                     //2
        RxBuffer2[23] = ' ';                     //3
        RxBuffer2[24] = 'O';                     //4
    	RxBuffer2[25] = 'K';                     //5
    	RxBuffer2[26] = '!';                     //5
        RxBuffer2[27] = ' ';
        RxBuffer2[28] = ' ';
    }
    else{
        RxBuffer2[20] = 'W';
        RxBuffer2[21] = 'a';                     //1
        RxBuffer2[22] = 'i';                     //2
        RxBuffer2[23] = 't';                     //3
        RxBuffer2[24] = ' ';                     //4
    	RxBuffer2[25] = '4';                     //5
    	RxBuffer2[26] = '8';                     //5
        RxBuffer2[27] = '5';
        RxBuffer2[28] = ' ';
    }
    
    if((TestCnt >= 100) || (TestDip == 0x08)){
        RxBuffer2[29] = 'C';                     //1
        RxBuffer2[30] = 'N';                     //2
        RxBuffer2[31] = 'T';                     //3
        RxBuffer2[32] = ' ';                     //4
    	RxBuffer2[33] = 'O';                     //5
    	RxBuffer2[34] = 'K';                     //5
    	RxBuffer2[35] = '!';                     //5
    	RxBuffer2[36] = ' ';                     //5
    	RxBuffer2[37] = ' ';                     //5
    }
    else{
        RxBuffer2[29] = 'W';                     //1
        RxBuffer2[30] = 'a';                     //2
        RxBuffer2[31] = 'i';                     //3
        RxBuffer2[32] = 't';                     //4
    	RxBuffer2[33] = ' ';                     //5
    	RxBuffer2[34] = 'C';                     //5
    	RxBuffer2[35] = 'n';                     //5
    	RxBuffer2[36] = 't';                     //5
    	RxBuffer2[37] = ' ';                     //5
    }



	if(bIOError){

		if(you==0)		errio=I_EMG_bit;
		if(you==1)		errio=I_SU1_bit;
		if(you==2)		errio=I_GR_bit;
		if(you==3)		errio=I_FIRE_bit;
		if(you==4)		errio=I_X0_bit;
		if(you==5)		errio=I_FS0_bit;

        RxBuffer2[4]  = 'E';
        RxBuffer2[5]  = you + '0';

		if(errio & 0x01)	RxBuffer2[6]='1';
		else				RxBuffer2[6]='0';

		if(errio & 0x02)	RxBuffer2[7]='1';
		else				RxBuffer2[7]='0';

		if(errio & 0x04)	RxBuffer2[8]='1';
		else				RxBuffer2[8]='0';

		if(errio & 0x08)	RxBuffer2[9]='1';
		else				RxBuffer2[9]='0';

		if(errio & 0x10)	RxBuffer2[10]='1';
		else				RxBuffer2[10]='0';

		if(errio & 0x20)	RxBuffer2[11]='1';
		else				RxBuffer2[11]='0';

		if(errio & 0x40)	RxBuffer2[12]='1';
		else				RxBuffer2[12]='0';

		if(errio & 0x80)	RxBuffer2[13]='1';
		else				RxBuffer2[13]='0';
	}

}








void    __attribute__((section(".usercode"))) CounterDsp(void)
{
    unsigned int count;

    RxBuffer2[21] = ' ';
    RxBuffer2[22] = 'C';                     //1
    RxBuffer2[23] = 'o';                     //2
    RxBuffer2[24] = 'u';                     //3
    RxBuffer2[25] = 'n';                     //4
	RxBuffer2[26] = 't';                     //5
	RxBuffer2[27] = ' ';                     //6
	RxBuffer2[28] = ' ';                     //7
	RxBuffer2[29] = ' ';                     //8
	RxBuffer2[30] = ' ';                     //9
	RxBuffer2[31] = ' ';                     //10
	RxBuffer2[32] = ' ';                     //11
	RxBuffer2[33] = ' ';                     //12
	RxBuffer2[34] = ' ';                     //13 
	RxBuffer2[35] = ' ';                     //14
	RxBuffer2[36] = ' ';                     //15 
	RxBuffer2[37] = ' ';                     //16

    count=eDArry[eMvCounter+1];   		
    count=(count * 256);
   		   		
    count=count + eDArry[eMvCounter];   	
   			

    RxBuffer2[28]=(count/10000)+'0';
    count=(count%10000);
      	
    RxBuffer2[29]=(count/1000)+'0';
    count=(count%1000);
      	
    RxBuffer2[30]=(count/100)+'0';
    count=(count%100);
      	
    RxBuffer2[31]=(count/10)+'0';
    count=(count%10);
      	      
    RxBuffer2[32]=count +'0';

}



void    __attribute__((section(".usercode"))) StatusDsp(void)
{
    unsigned int i;

    for(i=0;i<16;i++){
        RxBuffer2[22+i]=StatusMessage[sRamDArry[mSysStatus]][i];
    }
}



void    __attribute__((section(".usercode"))) RpmDsp(void)
{
    unsigned int count;
    unsigned int chun,bek,sip,il;
    unsigned long tmpcalu;


    tmpcalu=(PulsePer100Msec * 8);
    tmpcalu=tmpcalu * 600 * 10;
    tmpcalu=(tmpcalu/(unsigned long)SET_ENCODER_PULSE);
    chun=(unsigned int)tmpcalu;


    il=(chun%10);

    sip=(chun/10);
    sip=(sip%10);

    bek=(chun/100);
    bek=(bek%10);

    chun=chun/1000;
    chun=(chun%10);

	RxBuffer2[13] = chun + '0';                     
	RxBuffer2[14] = bek  + '0';                       
	RxBuffer2[15] = sip  + '0';                      
	RxBuffer2[16] = '.';                             
	RxBuffer2[17] = il   + '0';
	RxBuffer2[18] = 'r';
	RxBuffer2[19] = 'p';
	RxBuffer2[20] = 'm';
}



void    __attribute__((section(".usercode"))) MpmDsp(void)
{
    unsigned int count;
    unsigned int chun,bek,sip,il;

    chun=(unsigned int)CurMeterPerMin;

    il=(chun%10);

    sip=(chun/10);
    sip=(sip%10);

    bek=(chun/100);
    bek=(bek%10);

    chun=chun/1000;
    chun=(chun%10);

	RxBuffer2[13] = chun + '0';                     
	RxBuffer2[14] = bek  + '0';                       
	RxBuffer2[15] = sip  + '0';                      
	RxBuffer2[16] = '.';                             
	RxBuffer2[17] = il   + '0';
	RxBuffer2[18] = 'm';
	RxBuffer2[19] = 'p';
	RxBuffer2[20] = 'm';
}




void    __attribute__((section(".usercode"))) LdDataTx(void)
{         
    RxBuffer2[0]  = ACK;
    RxBuffer2[1]  = COMPANY;

    RxBuffer2[2]  = ' ';                            //cmd
    RxBuffer2[3]  = ' ';                            //cmd
    RxBuffer2[4]  = ' ';                            //cmd

	RxBuffer2[38] = ' ';                     
	RxBuffer2[39] = ' ';                     
	RxBuffer2[40] = ' ';                     

	RxBuffer2[41]=ETX;
	RxBuffer2[42]=0;


    switch(Ladder_mode){
        case    0:
                TestDsp();
/*
                CurFlrDsp();
                MpmDsp();
                StatusDsp();
*/
            break;
        case    1:
                CurFlrDsp();
                MpmDsp();
                CounterDsp();
            break;
        case    100:
                SetFlrDsp();
                TopDataTx();
            break;
        case    101:
                SetFlrDsp();
//                PrtDataTx();
            break;
    }
	Serial2();
}



void    __attribute__((section(".usercode"))) LdCmdSet(void)
{   
    unsigned int  ldkey;
    ldkey=RcvBuf2[5];
    switch(ldkey){
        case    'm':
            Ladder_mode=Ladder_mode/PULL_DOWN_MENU;
            Ladder_mode=(Ladder_mode+1) * PULL_DOWN_MENU;
            if(Ladder_mode >= LEFT_MENU_MAX)  Ladder_mode=0;
            break;   
        case    's':
            break;   
        case    'u':
            Ladder_mode++;
            break;   
        case    'd':
            Ladder_mode--;
            break;   
        case    'e':
            break;   
        case    'n':
            break;   
    }
}  

