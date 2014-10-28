
#include <p30f6010.h>            
#include  "..\..\system_com\memory_map.h"

#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "door.h"
#include  "eeprom.h"
#include  "com.h"
#include  "counter.h"
#include  "you_can1.h" 
#include  "you_can2.h" 
#include  "lader.h" 
#include  "default_setup.h" 



#define F_LINE_START_PT     5
#define S_LINE_START_PT     22
#define PULL_DOWN_MENU      100
#define LEFT_MENU_MAX       200


#define FLASH_WR_BLOCK      64	//flash max write block == 64 byte
#define BACKUP_MAX_BLOCK    40  //32
#define BACKUP_COM_BLK      16  //16 byte hex --> ascii 32 byte
#define BACKUP_PER_BLK      4   //16 byte hex --> ascii 32 byte


/*
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

*/

/*
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


*/

//unsigned int Ladder_mode=0;


/*
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

*/


UserDataType	SrcAdrBlk;
UserDataType	LoaderChk;




void    __attribute__((section(".usercode"))) DataLoadSBuf(void)
{
	unsigned int  i,j,k;

	i=((SrcAdrBlk / BACKUP_PER_BLK) * FLASH_WR_BLOCK); 	
    GetFlashDataToBufRam(i);   											//block read(0-7)


	i=(SrcAdrBlk % BACKUP_PER_BLK) * BACKUP_COM_BLK;    				//pointer search in block
    
	for(j=0;j<BACKUP_COM_BLK;j++){										//16 byte load(ascii == 32 byte)
		k=(j * 2);
		src  = (unsigned char)(b_LdTmpBufRam((unsigned long)(i+j)));    // hex to ascii trans
		HextoASCIIByte();
		
	    RxBuffer2[5+k]  = firstdata;
	    RxBuffer2[6+k]  = seconddata;
	}
	k=(j * 2);

    RxBuffer2[5+k]  = ETX;
    RxBuffer2[6+k]  = 0;
}



void    __attribute__((section(".usercode"))) IntegerToString(unsigned int i)
{
	i=(i%100);

	RxBuffer2[3] = (i/10)  + '0';                     
	RxBuffer2[4] = (i%10)  + '0';                     
}


void    __attribute__((section(".usercode"))) DataDumpToLoader(void)
{
	if((SrcAdrBlk < BACKUP_MAX_BLOCK) && (LoaderChk < 20) ){    // area check and tim out check
	    RxBuffer2[0]  = ACK;
	    RxBuffer2[1]  = 'W';
	    RxBuffer2[2]  = 'F';
		IntegerToString(SrcAdrBlk);
		DataLoadSBuf();
		LoaderChk++;
	}
	else	bExportData=0;	
}




void    __attribute__((section(".usercode"))) ReceiveDataLoad(void)
{
	unsigned int i,j,k;

	j=((SrcAdrBlk % BACKUP_PER_BLK) * BACKUP_COM_BLK);						//pointer search in block

	for(i=0;i<BACKUP_COM_BLK;i++){
		k=(i*2);
		src=b_LdTmpBufRam((unsigned long)(j+i));
		HextoASCIIByte();

		if( (firstdata  < '0') || (firstdata  > 'F'))	firstdata ='0'; 		
		if( (seconddata < '0') || (seconddata > 'F'))	seconddata='0'; 		
			
		RxBuffer2[5+k]=firstdata;
		RxBuffer2[6+k]=seconddata;
	}		
	
    RxBuffer2[37]  = ETX;
    RxBuffer2[38]  = 0;
}



void    __attribute__((section(".usercode"))) DataReqToLoader(void)
{
	unsigned int i,j,k;

	if((SrcAdrBlk < BACKUP_MAX_BLOCK) && (LoaderChk < 20) ){    // area check and tim out check

	    RxBuffer2[0]  = ACK;
	    RxBuffer2[1]  = 'R';
	    RxBuffer2[2]  = 'F';
		IntegerToString(SrcAdrBlk);
		ReceiveDataLoad();	
		LoaderChk++;
	}
	else	bExportData=0;	
}





unsigned int  __attribute__((section(".usercode"))) ReceiveCmp(void)
{
	unsigned int i,j,k,good;

	good=1;

	i=(SrcAdrBlk % BACKUP_PER_BLK) * BACKUP_COM_BLK;  						//pointer search in block
    
	for(j=0;j<BACKUP_COM_BLK;j++){
		k=(j *2);
		src  = (unsigned char)(b_LdTmpBufRam((unsigned long)(i + j)));
		HextoASCIIByte();
		
	    if(RxBuffer2[5+k]  != firstdata)  good=0;
	    if(RxBuffer2[6+k]  != seconddata) good=0;	
	}

	if(RxBuffer2[0]  != ACK)	good=0;	
	if(RxBuffer2[1]  != 'w')	good=0;
	if(RxBuffer2[2]  != 'F')	good=0;

	return(good);
}


void  __attribute__((section(".usercode"))) TmpSave(void)
{
	unsigned int i,j,k,l,pt;

	i=(unsigned int)RxBuffer2[3];
    i=ASCTOHEX(i);

	j=(unsigned int)RxBuffer2[4];
    j=ASCTOHEX(j);


	SrcAdrBlk=((i * 10) + j);

	if(SrcAdrBlk  > BACKUP_MAX_BLOCK)		SrcAdrBlk=0;

/*
	if(SrcAdrBlk == BACKUP_MAX_BLOCK){
		bImportData=0;
	}
*/

	if( ((SrcAdrBlk % BACKUP_PER_BLK) == 0) && ((SrcAdrBlk/BACKUP_PER_BLK) > 0)){
		i = ((SrcAdrBlk / BACKUP_PER_BLK) -1);
		i= (i * FLASH_WR_BLOCK);  
    	flash_write_DspChar(i);
	}

	if(SrcAdrBlk == BACKUP_MAX_BLOCK){
	   	GetFlashDataToBufRam(F_BLOCK2);
	    b_LdTmpBufRam(F_Ver0)           = VERSION_0;
	    b_LdTmpBufRam(F_Ver1)           = VERSION_1;
	    b_LdTmpBufRam(F_Ver2)           = VERSION_2;	
	    flash_write_DspChar(F_BLOCK2);

        CaluDecreasePulse();

		bImportData=0;
    	SWR=1;
    	asm("RESET");
	}
			

	pt=( (SrcAdrBlk % BACKUP_PER_BLK) * BACKUP_COM_BLK);

	for(i=0;i<BACKUP_COM_BLK;i++){
		l=(i*2);
		k=(unsigned int)RxBuffer2[5+l];
	    k=ASCTOHEX(k);
		k=((k << 4) & 0xf0);
	
		j=(unsigned int)RxBuffer2[6+l];
	    j=ASCTOHEX(j);
		j=(k | j);

		b_LdTmpBufRam((unsigned long)(pt+i))=(unsigned char)(j);
	}
}




void  __attribute__((section(".usercode"))) NewLoaderChk(void)
{
	if(bExportData){
		if(ReceiveCmp()){
			SrcAdrBlk++;
		}

		LadderBuf[C_SAVE_DATA+0]='N';      
		LoaderChk=0;
		LadderKeyTime=0;
	}

	else if(bImportData){
		if(!bAuto && IN_AUTO){
			if((RxBuffer2[0]  == ACK) && (RxBuffer2[1]  == 'r')	&& (RxBuffer2[2]  == 'F')){
				SaveVerify=0x55;
				TmpSave();
				SaveVerify=0;
				RxBuffer2[0]  = 'n';
	 			RxBuffer2[1]  = 'n';
				RxBuffer2[2]  = 'n';
			}
		
			LadderBuf[C_SAVE_DATA+0]='N';      
			LoaderChk=0;
			LadderKeyTime=0;
		}
		else{
			SaveVerify=0x0;
			bImportData=0;	
		}
	}

//	if(!bImportData)	SaveVerify=0;
}




void    __attribute__((section(".usercode"))) LdDataTx(void)
{
    unsigned int i;
         
    RxBuffer2[0]  = ACK;
    RxBuffer2[1]  = cF_COMPANY;

	RxBuffer2[36] = ' ';                     
	RxBuffer2[37] = ' ';                     
	RxBuffer2[38] = ' ';                     
	RxBuffer2[39] = ' ';                     
	RxBuffer2[40] = ' ';                     

	RxBuffer2[41]=ETX;
	RxBuffer2[42]=0;


    for(i=0;i<36;i++){
        if(New485Ladder[i+0] > 0x80)    	RxBuffer2[2+i]=New485Ladder[i+0] - 0x80;
        else                            	RxBuffer2[2+i]=New485Ladder[i+0];

        if(New485Ladder[i+0] == 0)    	    RxBuffer2[2+i]=New485Ladder[i+0]=' ';
    }


	if(bExportData){
		DataDumpToLoader();
	}
	else if(bImportData){
		DataReqToLoader();
	}

	Serial2();
}
