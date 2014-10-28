



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
//#include  "ladder485.h" 



extern void   DspFloorSet(void);
extern void   CarStopCmd(void);
extern void   CarUpStartCmd(void);
extern void   CarDnStartCmd(void);
extern void   CarCurFloorRead(void);
extern void   InverterErrorCheck(void);
extern void   ManualHomeSpeedCmd(void);




extern void Initialize_DS1302(void);
extern void disp_clk_regs(void);


extern  void  FireKeyCheck(void);



extern void erase_flash_row(unsigned int);
extern void program_flash(unsigned int, unsigned int);



UserDataType    errbd[12]={0};
UserDataType    Olderrbd[12]={0};
UserDataType    LadderBuf[16]={0};                         
UserDataType    LadderData[16]={0};                           
UserDataType    sRamDArry[END_SRAM]={0};     
UserDataType    BdErrCntSeq[ABS_ADDRESS]={0};
UserDataType    BDid[ABS_ADDRESS]={0};
UserDataType    eDArry[E_END]={0};      


UserDataType    TestLoop=0;
UserDataType    TestIO=0;
UserDataType    Test485=0;
UserDataType    TestCan1=0;
UserDataType    TestCan2=0;
UserDataType    TestCnt=0;
UserDataType    TestDip=0;


UserDataType    Cancle=0;
UserDataType    BefRcvAdr=0;
UserDataType    CurRcvAdr=0;
UserDataType    LogAddress=0;
UserDataType    AbsAddress=0;
UserDataType    LogAddressLoop=0;
UserDataType    TimeOutBd=0;
UserDataType    src=0;
UserDataType    firstdata=0;
UserDataType    seconddata=0;
UserDataType    Bef_I_EMG=0;
UserDataType    Bef_I_FS0=0;
UserDataType    Bef_I_GR=0;
UserDataType    Bef_I_SU1=0;
UserDataType    Bef_I_X_0=0;
UserDataType    Bef_I_FIRE=0;
UserDataType    I_EMG_Cht=0;
UserDataType    I_FS0_Cht=0;
UserDataType    I_GR_Cht=0;
UserDataType    I_SU1_Cht=0;
UserDataType    I_X_0_Cht=0;
UserDataType    I_FIRE_Cht=0;
UserDataType    NoCloseCnt=0;
UserDataType    errpt=0;
UserDataType    ErrBdNamePt=0;
UserDataType    BefErrBdNamePt=0;
UserDataType    eMvCounterCnt=0;
UserDataType    VoiceTime=0;        
UserDataType    FhmLoaderTime=0;        
UserDataType    SirenTime=0;        
UserDataType    UpBttonTime=0;
UserDataType    DnBttonTime=0;
UserDataType    CarStopTime=0;
UserDataType    DoorCloseTime=0;
UserDataType    DoorOpenOnTime=0;
UserDataType    DoorCloseOnTime=0;
UserDataType    msec10=0;
UserDataType    sec1=0;

UserDataType    EepTime=0;
UserDataType    FanTime=0; 
UserDataType    ManualStopTime=0;  
UserDataType    WarmingUpTime=0; 
UserDataType    FixFlrTimeCnt=0; 
UserDataType    errtime=0;
UserDataType    FhmTime=0;
UserDataType    CurFTime=0;
UserDataType    NextFTime=0;
UserDataType    RestartTime=0;
UserDataType    ExtCmdFlrONOFFCnt=0;
UserDataType    SerialLoopMaxTime=0;
UserDataType    FireBaseFloor=0;
UserDataType    CurSpeed=0;
UserDataType    OriginalHighFlr=0;
UserDataType    OriginalLowFlr=0;



unsigned	int    	    NextFloorTime=0;
unsigned	int     	MinuteTime=0;
unsigned	int   	    LuLdTime=0;
unsigned	int   	    CounterTime=0;
unsigned	int    	    DoorOpenTime=0;
unsigned	int    	    LightTime=0;
unsigned	int    	    AutoNoMoveTime=0;




UserDataType    OldFireBuf=0;  
UserDataType    AutoBit=0;
UserDataType    EmerBit=0;
UserDataType    SlipBit=0;
UserDataType    LuLdBit=0;
UserDataType    OpenEndBit=0;
UserDataType    BefDlsBit=0;
UserDataType    BefDestFBit=0;
UserDataType    EepRWBit=0;
UserDataType    Etc1Bit=0;
UserDataType    Etc2Bit=0;


UserDataType    S0_STATE_bit=0;
UserDataType    S1_STATE_bit=0;
UserDataType    S2_STATE_bit=0;
UserDataType    S3_STATE_bit=0;
UserDataType    S4_STATE_bit=0;

UserDataType    I_SU1_bit=0;
UserDataType    I_EMG_bit=0;
UserDataType    I_GR_bit=0;
UserDataType    I_FIRE_bit=0;
UserDataType    I_FS0_bit=0;
UserDataType    I_X0_bit=0;
UserDataType    O_OP_bit=0;
UserDataType    O_U_W_bit=0;
UserDataType    O_Y_0_bit=0;
UserDataType    DoorStatus_bit=0;
UserDataType    FhmToggle=0;
UserDataType    PowerFailTime=0;
UserDataType    CarOnceStopTime=0;

UserDataType    MyGroupAddr;
UserDataType    MyLocalAddr;
UserDataType    MyNc_Addr;



UserDataType    SegData0;
UserDataType    SegData1;
UserDataType    SegData2;
UserDataType    SegSel;

UserDataType    you;
UserDataType    errio;



unsigned long  parameter_mirror[MAX_LONG_BUF]; // = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

long_field  FlashBuf[128]           __attribute__((aligned(128), section(".auto_psv,r")));
long_field  FlashDspCharBuf[128]     __attribute__((aligned(128) , section(".auto_psv,r")));
//long_field  FlashSpeed[16]          __attribute__((aligned(16) , section(".auto_psv,r")));
//long_field  FlashDsp[16]          __attribute__((aligned(16) , section(".auto_psv,r")));

const unsigned char   DftFlrName[] = {"B7B6B5B4B3B2B10102030405060708091011121314151617181920212223242526272829303132"}; 



/*******************************************************
   manual play and record
*******************************************************/


void  __attribute__((section(".usercode"))) flash_write(unsigned int pt)
{
    asm("CLRWDT");

    DISABLE_INTERRUPTS;

	// Erase the 32 location row of flash
	erase_flash_row((unsigned int)&FlashBuf[pt]);

	// Write the 32 parameters back 
	program_flash((unsigned int)&FlashBuf[pt],(unsigned int)&parameter_mirror[0]);

    ENABLE_INTERRUPTS;

    asm("CLRWDT");
}





/*
void __attribute__((section(".usercode"))) DecreasePulseSave(void)
{

    unsigned int i;
    unsigned long   a,b,c;

    switch(cF_ELEV_SPEED){
        case    SPEED_30:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_45:
            b=GET_LONG(DEC_PULSE_45);
            break;                
        case    SPEED_60:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_90:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_105:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_120:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_150:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_180:
            b=GET_LONG(DEC_PULSE_30);
            break;     
        case    SPEED_210:
            b=GET_LONG(DEC_PULSE_30);
            break;     
    }        


    for(i=0;i<16;i++){
        a= GET_LONG(FLR_02_PULSE + i);
        c= a-b;
        parameter_mirror[i] = (unsigned long)c;
    }
    flash_write(UP_FLR_0102_PULSE);


    for(i=0;i<15;i++){
        a= GET_LONG(FLR_18_PULSE + i);
        c=a-b;
        parameter_mirror[i] = (unsigned long)c;
    }
    parameter_mirror[15] = GET_LONG(FLR_32_PULSE) + BASE_PULSE;
    flash_write(UP_FLR_1718_PULSE);


    for(i=0;i<15;i++){
        a=GET_LONG(FLR_01_PULSE + i);
        c=a+b;
        parameter_mirror[i+1] = (unsigned long)c;
    }

    parameter_mirror[0]=1;
    flash_write(DN_FLR_0100_PULSE);


    for(i=0;i<16;i++){
        a=GET_LONG(FLR_16_PULSE + i);
        c=a+b;
        parameter_mirror[i] = (unsigned long)c;
    }
    flash_write(DN_FLR_1716_PULSE);
}
*/



void  __attribute__((section(".usercode"))) SaveFloorCnt(void)
{
    unsigned int i;

    flash_write(FLR_01_PULSE);

    for(i=0;i<16;i++)    parameter_mirror[i] = parameter_mirror[i+16];
    flash_write(FLR_17_PULSE);

//    DecreasePulseSave();

}                                                                     







void  __attribute__((section(".usercode"))) CaluDecreasePulse(void)
{

    unsigned int i;
    unsigned long rpm,mpm,encoder_pulse,mm_per_pulse,dec_mm_rpm,tmp_dec_mm_rpm,tmp_dec_pulse,tmp_value;

    for(i=0;i<32;i++){
        parameter_mirror[i]=GET_LONG(ENCODER_PULSE+i);
    }    


    //move_length/pulse = (MPM * 1000)/(RPM * PULSE_PER_ROTATE)

    mpm             = parameter_mirror[MPM-ENCODER_PULSE];
    mpm             = mpm * 1000 * 10000;                       //length=mm * 10000 ==1200000000
    rpm             = parameter_mirror[RPM-ENCODER_PULSE];
  
    encoder_pulse   = parameter_mirror[ENCODER_PULSE-ENCODER_PULSE];

    mm_per_pulse    = mpm / ( rpm *  encoder_pulse);  // 1200000000/1523712
    mm_per_pulse    = mm_per_pulse * ( DOUBL_CNT / 4);

    parameter_mirror[MM_PULSE-ENCODER_PULSE]     = mm_per_pulse;
    parameter_mirror[MPM_VARIABLE-ENCODER_PULSE] = (mm_per_pulse * (unsigned long)600);

///////////////////////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_30-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_30-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_30 - ENCODER_PULSE]=tmp_dec_pulse;
    
/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_45-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_45-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_45 - ENCODER_PULSE]=tmp_dec_pulse;

/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_60-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_60-ENCODER_PULSE]=tmp_dec_pulse;

//*****************************
#ifdef  OFFICE        
    tmp_dec_pulse  = 700;
    parameter_mirror[DEC_PULSE_60-ENCODER_PULSE]=tmp_dec_pulse;
#endif
//*****************

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_60 - ENCODER_PULSE]=tmp_dec_pulse;



/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_90-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_90-ENCODER_PULSE]=tmp_dec_pulse;

//*****************************
#ifdef  OFFICE        
    tmp_dec_pulse  = 900;
    parameter_mirror[DEC_PULSE_90-ENCODER_PULSE]=tmp_dec_pulse;
#endif        
//*****************

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_90 - ENCODER_PULSE]=tmp_dec_pulse;


/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_105-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_105-ENCODER_PULSE]=tmp_dec_pulse;

//*****************************
#ifdef  OFFICE        
    tmp_dec_pulse  = 900;
    parameter_mirror[DEC_PULSE_105-ENCODER_PULSE]=tmp_dec_pulse;
#endif        
//*****************

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_105 - ENCODER_PULSE]=tmp_dec_pulse;

/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_120-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_120-ENCODER_PULSE]=tmp_dec_pulse;

#ifdef  OFFICE        
    tmp_dec_pulse  = 1200;
    parameter_mirror[DEC_PULSE_120-ENCODER_PULSE]=tmp_dec_pulse;
#endif

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_120 - ENCODER_PULSE]=tmp_dec_pulse;

/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_150-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_150-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_150 - ENCODER_PULSE]=tmp_dec_pulse;

/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_180-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_180-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_180 - ENCODER_PULSE]=tmp_dec_pulse;

/////////////////////
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_210-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_210-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    tmp_dec_pulse  = (tmp_dec_pulse  + tmp_value);
    parameter_mirror[MIN_DEC_PULSE_210 - ENCODER_PULSE]=tmp_dec_pulse;


    flash_write(ENCODER_PULSE);

    for(i=0;i<16;i++)   parameter_mirror[i]=parameter_mirror[i+16];
    flash_write(ENCODER_PULSE + 16);

}                                                                     


void  __attribute__((section(".usercode"))) DefaultEncoderRpmMpm(void)
{

    unsigned int i;
    unsigned long rpm,mpm,encoder_pulse,mm_per_pulse,dec_mm_rpm,tmp_dec_mm_rpm,tmp_dec_pulse,tmp_value;

    for(i=0;i<32;i++){
        parameter_mirror[i]=GET_LONG(ENCODER_PULSE+i);
    }    


    parameter_mirror[MPM-ENCODER_PULSE]             = SET_ELEV_SPEED_PER_MIM; // 90;    //120;   //45    //45   m/min
    parameter_mirror[ENCODER_PULSE-ENCODER_PULSE]   = SET_ENCODER_PULSE;      //8192;  //8192;  //1024  //8192 pulse/rotate
    parameter_mirror[RPM-ENCODER_PULSE]             = SET_MOTOR_RPM;          //150;   //186;   //1100  //74   r/min

    parameter_mirror[DEC_LENGTH_30-ENCODER_PULSE]   = SPEED_30_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_45-ENCODER_PULSE]   = SPEED_45_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_60-ENCODER_PULSE]   = SPEED_60_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_90-ENCODER_PULSE]   = SPEED_90_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_105-ENCODER_PULSE]  = SPEED_105_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_120-ENCODER_PULSE]  = SPEED_120_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_150-ENCODER_PULSE]  = SPEED_150_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_180-ENCODER_PULSE]  = SPEED_180_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_210-ENCODER_PULSE]  = SPEED_210_DEC_LENGTH;


    flash_write(ENCODER_PULSE);

    for(i=0;i<16;i++)   parameter_mirror[i]=parameter_mirror[i+16];
    flash_write(ENCODER_PULSE + 16);
}                                                                     



void  __attribute__((section(".usercode"))) flash_write_DspChar(unsigned int pt)
{
    unsigned int i;

    asm("CLRWDT");

    i=((pt/64) * 16);

    DISABLE_INTERRUPTS;

	// Erase the 32 location row of flash
	erase_flash_row((unsigned int)&FlashDspCharBuf[i]);

	// Write the 32 parameters back 
	program_flash((unsigned int)&FlashDspCharBuf[i],(unsigned int)&parameter_mirror[0]);

    ENABLE_INTERRUPTS;

    asm("CLRWDT");
}


/*
void  __attribute__((section(".usercode"))) flash_write_Speed(unsigned int pt)
{
    asm("CLRWDT");

    DISABLE_INTERRUPTS;

	// Erase the 32 location row of flash
	erase_flash_row((unsigned int)&FlashSpeed[pt]);

	// Write the 32 parameters back 
	program_flash((unsigned int)&FlashSpeed[pt],(unsigned int)&parameter_mirror[0]);

    ENABLE_INTERRUPTS;

    asm("CLRWDT");
}
*/

void  __attribute__((section(".usercode"))) F_SetupData_ReSet(unsigned int pt,unsigned int DtNm)
{
    LocalType  i,j,k;

    k=(pt % 64);

    j=((pt/64) * 16);

//    if(pt<64)   j=0;
//    else        j=16;

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[j+i].long_data;
    }

    for(i=0;i<DtNm;i++){
        b_LdTmpBufRam((unsigned long)(k+i))     = (UserDataType)(LadderBuf[C_SAVE_DATA+i]);
    }

    if((j==0) && (k==1)){
        if(cF_FLRDSPCH(0) == 'B'){             
            if((LadderBuf[C_SAVE_DATA+0] == '7'))      i=0;  
            else if((LadderBuf[C_SAVE_DATA+0] == '6')) i=2;  
            else if((LadderBuf[C_SAVE_DATA+0] == '5')) i=4;  
            else if((LadderBuf[C_SAVE_DATA+0] == '4')) i=6;  
            else if((LadderBuf[C_SAVE_DATA+0] == '3')) i=8;  
            else if((LadderBuf[C_SAVE_DATA+0] == '2')) i=10;  
            else if((LadderBuf[C_SAVE_DATA+0] == '1')) i=12;
            else                                       j=1;  
        }
        if(cF_FLRDSPCH(0) == '0'){ 
            if((LadderBuf[C_SAVE_DATA+0] == '1'))       i=14;
            else                                        j=1;  
        }

        if(j==0){
            for(k=0;k<64;k++,i++){
                b_LdTmpBufRam(k)  = DftFlrName[i];
            }
        }
    }

    flash_write_DspChar(pt);
}



/*
void  __attribute__((section(".usercode"))) F_SetupDataCan(unsigned int pt)
{
    LocalType  i,j,k;

    k=(pt % F_TopFlr);

    if(pt<64)   j=0;
    else        j=16;

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[j+i].long_data;
    }

    flash_write_DspChar(j);
}
*/




UserDataType  __attribute__((section(".usercode"))) ReadInitSetupData(void)
{

    LocalType  i,j;


   	for(i=0;i<2;i++){
        eDArry[eMvCounter+i] = EEPROM_Read_Byte(eMvCounter+i);
   	}


    for(i=0;i<ERR_SAVE_SIZE;i++){
        eDArry[eSysErCnt+i]=0x0;         
   	}

    bSaveErrCnt=0;
    eDArry[eErrCntPt] = EEPROM_Read_Byte(eErrCntPt);

    if(eDArry[eErrCntPt] > ((ERR_SAVE_CNT+1) * 10)){
       	for(i=0;i<ERR_SAVE_SIZE;i++){
            eDArry[eSysErCnt+i]=0x0;
            EEPROM_Write_Byte(eSysErCnt+i,0x0);
   	    }

        eDArry[eErrCntPt] = 0x0;

        EEPROM_Write_Byte(eErrCntPt,0x0);

        sRamDArry[mBefErrCntPt]=eDArry[eErrCntPt];        
    }
    else{
        if(eDArry[eErrCntPt] > ERR_SAVE_CNT)    j= (ERR_SAVE_CNT +1) * ERR_SAVE_WIDE;
        else{
            j=eDArry[eErrCntPt] * ERR_SAVE_WIDE;        
        }

        sRamDArry[mBefErrCntPt]=j;        
        
       	for(i=0;i<j;i++){
            eDArry[eSysErCnt+i]=EEPROM_Read_Byte(eSysErCnt+i);;         
   	    }
    }


    
   	if((cF_VER0 != VERSION_0) || (cF_VER1 != VERSION_1) || (cF_VER2 != VERSION_2)){  

/*
        B_SETUP_RAM(F_TopFlr%F_TopFlr)       = 31;
        B_SETUP_RAM(F_PrkFlr%F_TopFlr)       = 0;
        B_SETUP_RAM(F_OpWtTm%F_TopFlr)       = 0;    //160;
        B_SETUP_RAM(F_OpTtTm%F_TopFlr)       = 0;
        B_SETUP_RAM(F_UserLamp%F_TopFlr)     = 0;
        B_SETUP_RAM(F_FixFloor%F_TopFlr)     = 0xff;
        B_SETUP_RAM(F_FixFloorTime%F_TopFlr) = 0;

        B_SETUP_RAM(F_FireSafeFlr%F_TopFlr)  = 0x00;
        B_SETUP_RAM(F_X7SafeFlr%F_TopFlr)    = 0x01;

        B_SETUP_RAM(F_FanTime%F_TopFlr)      = 0x28;  //30 == 3 sec
        B_SETUP_RAM(F_LgtTime%F_TopFlr)      = 0x64;  //100 == 10 sec

        B_SETUP_RAM(F_SubDoorFlr1%F_TopFlr)  = 0xff;
        B_SETUP_RAM(F_SubDoorFlr2%F_TopFlr)  = 0xff;
        B_SETUP_RAM(F_SubDoorFlr3%F_TopFlr)  = 0xff;
        B_SETUP_RAM(F_ErrStopCnt%F_TopFlr)   = 0xff;
        B_SETUP_RAM(F_NextFlrTime%F_TopFlr)  = 0;
        B_SETUP_RAM(F_LuLdOffTime%F_TopFlr)  = 0;

        B_SETUP_RAM(F_NonService0%F_TopFlr)  = 0xff;
        B_SETUP_RAM(F_NonService1%F_TopFlr)  = 0xff;
        B_SETUP_RAM(F_NonService2%F_TopFlr)  = 0xff;
        B_SETUP_RAM(F_NonService3%F_TopFlr)  = 0xff;

        B_SETUP_RAM(F_SerialNm0%F_TopFlr)    = 0;
        B_SETUP_RAM(F_SerialNm1%F_TopFlr)    = 0;
        B_SETUP_RAM(F_Passward0%F_TopFlr)    = '0';
        B_SETUP_RAM(F_Passward1%F_TopFlr)    = '0';
        B_SETUP_RAM(F_Passward2%F_TopFlr)    = '0';
        B_SETUP_RAM(F_Passward3%F_TopFlr)    = '0';

        B_SETUP_RAM(F_Ver0%F_TopFlr)         = VERSION_0;
        B_SETUP_RAM(F_Ver1%F_TopFlr)         = VERSION_1;
        B_SETUP_RAM(F_Ver2%F_TopFlr)         = VERSION_2;

        B_SETUP_RAM(F_StTm1%F_TopFlr)        = 20;
        B_SETUP_RAM(F_StTm2%F_TopFlr)        = 40;
        B_SETUP_RAM(F_StTm3%F_TopFlr)        = 60;
        B_SETUP_RAM(F_StTm4%F_TopFlr)        = 80;

                                                
                                                      //     7 ,      6,      5,        4,         3,        2,       1,    0
        B_SETUP_RAM(F_NcNoBit0%F_TopFlr)     = 0xff;  //     nc,     nc,     nc,       nc,  overload,   safety, parking, oplms
        B_SETUP_RAM(F_NcNoBit1%F_TopFlr)     = 0xff;  //NcNoEx2,NcNoEx1,NcNoEx0,NcNoWater,  NcNoFire, NcNoPass, NcNoBat, NcNoGr
        B_SETUP_RAM(F_NcNoBit2%F_TopFlr)     = 0xff;  //NcNoSd3,NcNoSu3,NcNoSd2,  NcNoSu2,   NcNoFr4,  NcNoFr3, NcNoFr2, NcNoFr1
        B_SETUP_RAM(F_NcNoBit3%F_TopFlr)     = 0xff;  // NcNoX7, NcNoX6, NcNoX5,   NcNoX4,    NcNoX3,   NcNoX2,  NcNoX1, NcNoX0
        B_SETUP_RAM(F_NcNoBit3%F_TopFlr)     = 0xff;  // NcNoX7, NcNoX6, NcNoX5,   NcNoX4,    NcNoX3,   NcNoX2,  NcNoX1, NcNoX0


        B_SETUP_RAM(F_ElevSpeed%F_TopFlr)    = SPEED_60;   
        B_SETUP_RAM(F_StartFloor%F_TopFlr)   = START_FLOOR;   


        B_SETUP_RAM(F_Su1_Sd1_Velocity%F_TopFlr)    = 55;      //mpm
        B_SETUP_RAM(F_Su2_Sd2_Velocity%F_TopFlr)    = 85;      //mpm
        B_SETUP_RAM(F_Su3_Sd3_Velocity%F_TopFlr)    = 105;     //mpm

        B_SETUP_RAM(F_FhmOnOff%F_TopFlr)      = 1;       //FHM On Off          == FHM Off
        B_SETUP_RAM(F_DoorJumperOff%F_TopFlr) = 1;       //door jumper on/off  ==> 1=door jumper check on  //0=off

        I_SETUP_RAM(F_BrkStTm10%F_TopFlr)    = 800;  //you daejeoun 700;  //you daejeoun
        I_SETUP_RAM(F_BrkStTm20%F_TopFlr)    = 1500;
        I_SETUP_RAM(F_BrkStTm30%F_TopFlr)    = 1600;
        I_SETUP_RAM(F_BrkStTm40%F_TopFlr)    = 2000;
        I_SETUP_RAM(F_BrkStTm50%F_TopFlr)    = 502;
        I_SETUP_RAM(F_BrkStTm60%F_TopFlr)    = 500;

*/

        b_LdTmpBufRam(F_TopFlr)         = 31;
        b_LdTmpBufRam(F_PrkFlr)         = 0;
        b_LdTmpBufRam(F_OpWtTm)         = 0;    //160;
        b_LdTmpBufRam(F_OpTtTm)         = 0;
//        b_LdTmpBufRam(F_UserLamp)       = 0;
        b_LdTmpBufRam(F_FixFloor)       = 0xff;
        b_LdTmpBufRam(F_FixFloorTime)   = 0;
                                        
        b_LdTmpBufRam(F_FireSafeFlr)    = 0x00;
        b_LdTmpBufRam(F_X7SafeFlr)      = 0x01;

        b_LdTmpBufRam(F_FanTime)        = 0x28;  //30 == 3 sec
        b_LdTmpBufRam(F_LightTime)      = 0x64;  //100 == 10 sec

        b_LdTmpBufRam(F_SubDoorFlr1)    = 0xff;
        b_LdTmpBufRam(F_SubDoorFlr2)    = 0xff;
        b_LdTmpBufRam(F_SubDoorFlr3)    = 0xff;
//        b_LdTmpBufRam(F_ErrStopCnt)     = 0xff;
        b_LdTmpBufRam(F_NextFlrTime)    = 0;
        b_LdTmpBufRam(F_LuLdOffTime)    = 0;

        b_LdTmpBufRam(F_NonService0)    = 0xff;
        b_LdTmpBufRam(F_NonService1)    = 0xff;
        b_LdTmpBufRam(F_NonService2)    = 0xff;
        b_LdTmpBufRam(F_NonService3)    = 0xff;

/*
        b_LdTmpBufRam(F_SerialNm0)      = 0;
        b_LdTmpBufRam(F_SerialNm1)      = 0;
        b_LdTmpBufRam(F_Passward0)      = '0';
        b_LdTmpBufRam(F_Passward1)      = '0';
        b_LdTmpBufRam(F_Passward2)      = '0';
        b_LdTmpBufRam(F_Passward3)      = '0';

        b_LdTmpBufRam(F_Ver0)           = VERSION_0;
        b_LdTmpBufRam(F_Ver1)           = VERSION_1;
        b_LdTmpBufRam(F_Ver2)           = VERSION_2;
*/
        b_LdTmpBufRam(F_StTm1)          = 20;
        b_LdTmpBufRam(F_StTm2)          = 40;
        b_LdTmpBufRam(F_StTm3)          = 60;
        b_LdTmpBufRam(F_StTm4)          = 80;
                                                
                                                      //     7 ,      6,      5,        4,         3,        2,       1,    0
        b_LdTmpBufRam(F_NcNoBit0)       = 0xff;  //     nc,     nc,     nc,       nc,  overload,   safety, parking, oplms
        b_LdTmpBufRam(F_NcNoBit1)       = 0xff;  //NcNoEx2,NcNoEx1,NcNoEx0,NcNoWater,  NcNoFire, NcNoPass, NcNoBat, NcNoGr
        b_LdTmpBufRam(F_NcNoBit2)       = 0xff;  //NcNoSd3,NcNoSu3,NcNoSd2,  NcNoSu2,   NcNoFr4,  NcNoFr3, NcNoFr2, NcNoFr1
        b_LdTmpBufRam(F_NcNoBit3)       = 0xff;  // NcNoX7, NcNoX6, NcNoX5,   NcNoX4,    NcNoX3,   NcNoX2,  NcNoX1, NcNoX0
        b_LdTmpBufRam(F_NcNoBit3)       = 0xff;  // NcNoX7, NcNoX6, NcNoX5,   NcNoX4,    NcNoX3,   NcNoX2,  NcNoX1, NcNoX0


//        b_LdTmpBufRam(F_ElevSpeed)      = SPEED_90;   
        b_LdTmpBufRam(F_StartFloor)     = START_FLOOR;   

		
//        b_LdTmpBufRam(F_Su1Sd1_Velocity)= 90;      //mpm
//        b_LdTmpBufRam(F_Su2Sd2_Velocity)= 90;      //mpm
//        b_LdTmpBufRam(F_Su3Sd3_Velocity)= 120;     //mpm

        b_LdTmpBufRam(F_FhmOnOff)       = 1;       //FHM On Off          == FHM Off
        b_LdTmpBufRam(F_DoorJumperOff)  = 1;       //door jumper on/off  ==> 1=door jumper check on  //0=off


        i_LdTmpBufRam(F_BrkStTm10)      = 800;  //you daejeoun 700;  //you daejeoun
        i_LdTmpBufRam(F_BrkStTm20)      = 1500;
        i_LdTmpBufRam(F_BrkStTm30)      = 1600;
        i_LdTmpBufRam(F_BrkStTm40)      = 2000;
        i_LdTmpBufRam(F_BrkStTm50)      = 502;
        i_LdTmpBufRam(F_BrkStTm60)      = 500;


//        flash_write_DspChar(F_TopFlr/4);
        flash_write_DspChar(F_TopFlr);


///////////////////////////////////////////////

        b_LdTmpBufRam(F_Ver0)           = VERSION_0;
        b_LdTmpBufRam(F_Ver1)           = VERSION_1;
        b_LdTmpBufRam(F_Ver2)           = VERSION_2;

        b_LdTmpBufRam(F_Bd_Id)          = 0x0;

        b_LdTmpBufRam(F_Passward0)      = '0';
        b_LdTmpBufRam(F_Passward1)      = '0';
        b_LdTmpBufRam(F_Passward2)      = '0';
        b_LdTmpBufRam(F_Passward3)      = '0';

        b_LdTmpBufRam(F_SerialNm0)      = 0;
        b_LdTmpBufRam(F_SerialNm1)      = 0;

        b_LdTmpBufRam(F_UserLamp)       = 0;
        b_LdTmpBufRam(F_ErrStopCnt)     = 0xff;

///////////////////////////////////////////////
        //  P1  P2  P3  P4
        //  0   0   0   0           :0
        //  1   0   0   0           :1
        //  0   1   0   0           :2
        //  1   1   0   0           :3
        //  0   0   1   0           :4
        //  1   0   1   0           :5
        //  0   1   1   0           :6
        //  1   1   1   0           :7
        //  0   0   0   1           :8
        //  1   0   0   1           :9
        //  0   1   0   1           :10
        //  1   1   0   1           :11
        //  0   0   1   1           :12
        //  1   0   1   1           :13
        //  0   1   1   1           :14
        //  1   1   1   1           :15
///////////////////////////////////////////////
        b_LdTmpBufRam(F_ManualSpeed)      = 4;      
        b_LdTmpBufRam(F_BatterySpeed)     = 6;      
        b_LdTmpBufRam(F_DecreaseSpeed)    = 2;     
        b_LdTmpBufRam(F_Etc1Speed)        = 0;     

        b_LdTmpBufRam(F_Etc2Speed)        = 0;     
        b_LdTmpBufRam(F_Etc3Speed)        = 0;     
        b_LdTmpBufRam(F_Speed30)          = 1;     
        b_LdTmpBufRam(F_Speed45)          = 1;     

        b_LdTmpBufRam(F_Speed60)          = 1;     
        b_LdTmpBufRam(F_Speed90)          = 3;     
        b_LdTmpBufRam(F_Speed105)         = 3;     
        b_LdTmpBufRam(F_Speed120)         = 5;     

        b_LdTmpBufRam(F_Speed150)         = 0;     
        b_LdTmpBufRam(F_Speed180)         = 0;     
        b_LdTmpBufRam(F_Speed210)         = 0;     
        b_LdTmpBufRam(F_ElevSpeed)        = SPEED_120; //SPEED_90; //SPEED_120;  //SPEED_90;   

        b_LdTmpBufRam(F_Su1Sd1_Velocity)= 90;      //mpm
        b_LdTmpBufRam(F_Su2Sd2_Velocity)= 90;      //mpm
        b_LdTmpBufRam(F_Su3Sd3_Velocity)= 120;     //mpm


/*
        B_SETUP_RAM(F_ManualSpeed%64)      = 4;      
        B_SETUP_RAM(F_BatterySpeed%64)     = 6;      
        B_SETUP_RAM(F_DecreaseSpeed%64)    = 2;     
        B_SETUP_RAM(F_Etc1Speed%64)        = 0;     
        B_SETUP_RAM(F_Etc2Speed%64)        = 0;     
        B_SETUP_RAM(F_Etc3Speed%64)        = 0;     
        B_SETUP_RAM(F_Speed30%64)          = 1;     
        B_SETUP_RAM(F_Speed45%64)          = 1;     
        B_SETUP_RAM(F_Speed60%64)          = 1;     
        B_SETUP_RAM(F_Speed90%64)          = 3;     
        B_SETUP_RAM(F_Speed105%64)         = 3;     
        B_SETUP_RAM(F_Speed120%64)         = 5;     
        B_SETUP_RAM(F_Speed150%64)         = 0;     
        B_SETUP_RAM(F_Speed180%64)         = 0;     
        B_SETUP_RAM(F_Speed210%64)         = 0;     
*/
        flash_write_DspChar(F_ManualSpeed);
//        flash_write_Speed(0);
///////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////// 
        for(i=0;i<64;i++){
            b_LdTmpBufRam(i)  = DftFlrName[i+14];
        }
        flash_write_DspChar(0);         		
///////////////////////////////////////////////


///////////////////////////////////////////////
        DefaultEncoderRpmMpm();
        CaluDecreasePulse();
///////////////////////////////////////////////

   	    for(i=0;i<2;i++){
            eDArry[eMvCounter+i] = 0x0;
			EEPROM_Write_Byte(eMvCounter+i,0x0);                 
   	    }

   	    for(i=0;i<ERR_SAVE_SIZE;i++){
      	    eDArry[eSysErCnt+i]=0x0;         
            EEPROM_Write_Byte(eSysErCnt+i,0x0);
   	    }

	    sRamDArry[mBefErrCntPt]=0x0;
        eDArry[eErrCntPt]=0x0;
        bSaveErrCnt=0;
	}  



   	if(cF_TOPFLR < 1 ){
        LadderBuf[C_SAVE_DATA]=1;
        F_SetupData_ReSet(F_TopFlr,1);
    }

   	if(cF_TOPFLR > 31 ){
        LadderBuf[C_SAVE_DATA]=31;
        F_SetupData_ReSet(F_TopFlr,1);
    }

   	if(cF_PRKFLR > cF_TOPFLR ){
        LadderBuf[C_SAVE_DATA]=0;
        F_SetupData_ReSet(F_PrkFlr,1);
    }

   	if(cF_OPWTTM > 250 ){
        LadderBuf[C_SAVE_DATA]=0;
        F_SetupData_ReSet(F_OpWtTm,1);
    }

   	if(cF_OPTTTM > 250 ){
        LadderBuf[C_SAVE_DATA]=0;
        F_SetupData_ReSet(F_OpTtTm,1);
    }

   	if(cF_USERLAMP > USER_LAMP_SORT ){
        LadderBuf[C_SAVE_DATA]=0;
        F_SetupData_ReSet(F_UserLamp,1);
    }


   	return(0);     
}









void    __attribute__((section(".usercode"))) HextoASCIIByte(void)
{
    
    LocalType   i;

    i=(src & 0xf0) >> 4;
    if(i<0x0a)   i= i + '0';
    else         i= i + '7';
    firstdata=i;
        
    i=(src & 0x0f);
    if(i<0x0a)   i= i + '0';
    else         i= i + '7';
    seconddata=i;        
}




void  __attribute__((section(".usercode"))) WhyStop(void)
{
	if(bInspect){
        sRamDArry[mSysStatus]=sINSPECT;      
	}

	else if(bsInvCurNext){
		if(sRamDArry[mSysStatus] >= sI_C_N_FLR)   sRamDArry[mSysStatus]=sI_C_N_FLR;         
   	}

	else if(bsEmergency){
		if(sRamDArry[mSysStatus] >= sEMERGENCY)   sRamDArry[mSysStatus]=sEMERGENCY;         
	}

	else if(bsLope){
		if(sRamDArry[mSysStatus] >= sLOPE_BRK)   sRamDArry[mSysStatus]=sLOPE_BRK;        
	}
   
	else if(bsSlip){
		if(sRamDArry[mSysStatus] >= sSLIP)   sRamDArry[mSysStatus]=sSLIP;       
	}
   
	else if(bsUls){
		if(bUpWard && bDoorCloseOk){
			if(sRamDArry[mSysStatus] >= sULS)   sRamDArry[mSysStatus]=sULS;            
		}                  
	}
   
	else if(bsDls){
		if(bDnWard && bDoorCloseOk){
			if(sRamDArry[mSysStatus] >= sDLS)   sRamDArry[mSysStatus]=sDLS;            
		}                  
	}
   
	else if(bsHdsRunOff){
		if(sRamDArry[mSysStatus] >= sHDS_RUN_OFF)   sRamDArry[mSysStatus]=sHDS_RUN_OFF;                       
	}
   
	else if(bsCleRunOff){
		if(sRamDArry[mSysStatus] >= sCLE_RUN_OFF)   sRamDArry[mSysStatus]=sCLE_RUN_OFF;                  
	}
   
	else if(bsHdsNoOn){
		if(sRamDArry[mSysStatus] > sHDS_NO_ON)   sRamDArry[mSysStatus]=sHDS_NO_ON;                        
	}
   
	else if(bsCleNoOn){
		if(sRamDArry[mSysStatus] > sCLE_NO_ON)   sRamDArry[mSysStatus]=sCLE_NO_ON;                        
	}
   
	else if(bsNextFloor){
		if(sRamDArry[mSysStatus] > sNEXT_FLOOR)   sRamDArry[mSysStatus] = sNEXT_FLOOR;               
	}

	else if(bsLuLdNoOff){
		if(sRamDArry[mSysStatus] > sLULD_NO_OFF)  sRamDArry[mSysStatus] = sLULD_NO_OFF;                         
	}
   
	else if(bsLuLdHome){
		if(sRamDArry[mSysStatus] > sLULD_HOME) sRamDArry[mSysStatus] = sLULD_HOME;                        
	}
   
	else if(bsDestFloor){
		if(sRamDArry[mSysStatus] > sDEST_FLOOR)   sRamDArry[mSysStatus]=sDEST_FLOOR;      
	}   

	else if(bDoorJumper){
		if(sRamDArry[mSysStatus] >= sDOOR_JUMPER)   sRamDArry[mSysStatus]=sDOOR_JUMPER;       				
	}   
}



void	__attribute__((section(".usercode"))) SaveEebuf(UserDataType  ErrName)
{
	LocalType i;

/*
	if( eDArry[eErrCntPt] >= 250){
//     	eDArry[eErrCntPt]=230; 
		sRamDArry[mBefErrCntPt]=(eDArry[eErrCntPt] % (ERR_SAVE_CNT+1)) * (ERR_SAVE_WIDE);         		                   
	}     	
*/
	
	i=(eDArry[eErrCntPt] % (ERR_SAVE_CNT+1));
	
	i=(i * ERR_SAVE_WIDE);
	sRamDArry[mBefErrCntPt]=i;

	eDArry[eSysErCnt + i + 0] = sRamDArry[Month];             
    eDArry[eSysErCnt + i + 1] = sRamDArry[Day];             
    eDArry[eSysErCnt + i + 2] = sRamDArry[mcurfloor];            
    eDArry[eSysErCnt + i + 3] = ErrName;       

           
	if(eDArry[eErrCntPt] < ((ERR_SAVE_CNT+1) * 10) ){
     	eDArry[eErrCntPt]++; 
	}     	


    bSaveErrCnt=1;

}


       
void     __attribute__((section(".usercode"))) ErrSave(void)
{  

	if(bsOpeNoOn){
		if(!bBefbsOpeNoOn){
			SaveEebuf(sOPE_NO_ON);
	        bBefbsOpeNoOn=bsOpeNoOn;
		}        
	}


	if(bsCleRunOff){
		if(!bBefbsCleRunOff){
			SaveEebuf(sCLE_RUN_OFF);
        	bBefbsCleRunOff=bsCleRunOff;
      	}        
   	}


   	if(bsHdsRunOff){
      	if(!bBefbsHdsRunOff){
			SaveEebuf(sHDS_RUN_OFF);
        	bBefbsHdsRunOff=bsHdsRunOff;
      	}        
   	}


   	if(bsDls){
      	if(!bBefbsDls){
			SaveEebuf(sDLS);
        	bBefbsDls=bsDls;
      	}        
   	}


   	if(bsUls){
      	if(!bBefbsUls){
			SaveEebuf(sULS);
        	bBefbsUls=bsUls;
      	}        
   	}


   	if(bsSlip){
      	if(!bBefbsSlip){
      		SaveEebuf(sSLIP);
        	bBefbsSlip=bsSlip;
      	}        
   	}



   	if(bsLope){
      	if(!bBefbsLope){
      		SaveEebuf(sLOPE_BRK);
        	bBefbsLope=bsLope;
      	}        
   	}


   	if(bsEmergency){
      	if(!bBefbsEmergency){
			SaveEebuf(sEMERGENCY);    
        	bBefbsEmergency=bsEmergency;
      	}        
   	}


   	if(bsNextFloor){
      	if(!bBefbsNextFloor){
			SaveEebuf(sNEXT_FLOOR);
        	bBefbsNextFloor=bsNextFloor;
      	}        
   	}


   	if(bsHdsNoOn){
      	if(!bBefbsHdsNoOn){
   			SaveEebuf(sHDS_NO_ON);
        	bBefbsHdsNoOn=bsHdsNoOn;
      	}        
   	}

   	if(bsCleNoOn){
      	if(!bBefbsCleNoOn){
   			SaveEebuf(sCLE_NO_ON);
            bBefbsCleNoOn=bsCleNoOn;
      	}        
   	}


   	if(bsLuLdHome){
      	if(!bBefbsLuLdHome){
   			SaveEebuf(sLULD_HOME);
        	bBefbsLuLdHome=bsLuLdHome;
      	}        
   	}


   	if(bsLuLdNoOff){
      	if(!bBefbsLuLdNoOff){
   			SaveEebuf(sLULD_NO_OFF);
        	bBefbsLuLdNoOff=bsLuLdNoOff;
      	}        
   	}
   
   	if(bsInvCurNext){
      	if(!bBefbsInvCurNext){
			SaveEebuf(sI_C_N_FLR);
        	bBefbsInvCurNext=bsInvCurNext;
      	}        
   	}     
}


void  __attribute__((section(".usercode"))) SystemErrSave(void)
{
	if(bAuto && (I_EMG_bit != 0xff) && (I_SU1_bit != 0xff)){     
		ErrSave(); 
        if(!bMoveCar){
        	if(!EEPROM_write_Ready() && bSaveErrCnt){
		        EEPROM_Write_Byte((unsigned int)(eErrCntPt),eDArry[eErrCntPt]);
                bSaveErrCnt=0;
            }

    		if((eDArry[eErrCntPt] % (ERR_SAVE_CNT+1)) > (sRamDArry[mBefErrCntPt]/ERR_SAVE_WIDE)){
	    		if(!EEPROM_write_Ready()){
		    		if(!EEPROM_Write_Byte((unsigned int)(eSysErCnt + sRamDArry[mBefErrCntPt]),eDArry[eSysErCnt + sRamDArry[mBefErrCntPt]])){
                        sRamDArry[mBefErrCntPt]++; 
               	    }     
                }                    
	    	}
        }
	}              
}



void  __attribute__((section(".usercode"))) ErrFlagClr(void)
{        
	bBefbsSlip=0;
	bBefbsCleRunOff=0;
	bBefbsHdsRunOff=0;
	bBefbsEmergency=0;
	bBefbsNextFloor=0;
	bBefbsHdsNoOn=0;
	bBefbsCleNoOn=0;
	bBefbsLuLdHome=0;
	bBefbsLuLdNoOff=0;
    bBefbsLope=0;
	bBefbsOpeNoOn=0;
    bBefbsInvCurNext=0;
	bBefbsDls=0;
	bBefbsUls=0; 
}


UserDataType  __attribute__((section(".usercode"))) OnceSaveErrorSet(UserDataType set)
{

   LocalType  temp,temp1;
   
   temp=ErrBdNamePt/8;
   temp1=ErrBdNamePt%8;      
   
   switch(temp1){
      case  0:
         temp1=0x01;
         break;
      case  1:
         temp1=0x02;
         break;
      case  2:
         temp1=0x04;
         break;
      case  3:
         temp1=0x08;
         break;
      case  4:
         temp1=0x10;
         break;
      case  5:
         temp1=0x20;
         break;
      case  6:
         temp1=0x40;
         break;
      case  7:
         temp1=0x80;
         break;
   }
   
   if(set==2){
      if(Olderrbd[temp] & temp1) return(1);         
      else                       return(0);         
   }
   else if(set==1){
      Olderrbd[temp]=(UserDataType)(Olderrbd[temp] | temp1);         
   }
   else{
      Olderrbd[temp]=(UserDataType)(Olderrbd[temp] & ~temp1);          
   }

   return(2);     

}



void  __attribute__((section(".usercode"))) ErrorSet(void)
{
   LocalType  temp,temp1,temp2;
   

   temp=ErrBdNamePt;
   ErrBdNamePt=BDid[CurRcvAdr];
   OnceSaveErrorSet(0);
   ErrBdNamePt=temp;
      
   for(temp2=BefRcvAdr;temp2+1 < CurRcvAdr;temp2++){
      temp=temp2/8;
      temp1=temp2%8;      
      switch(temp1){
         case  0:
            temp1=0x01;
            break;
         case  1:
            temp1=0x02;
            break;
         case  2:
            temp1=0x04;
            break;
         case  3:
            temp1=0x08;
            break;
         case  4:
            temp1=0x10;
            break;
         case  5:
            temp1=0x20;
            break;
         case  6:
            temp1=0x40;
            break;
         case  7:
            temp1=0x80;
            break;
      }
      errbd[temp]=errbd[temp] | temp1;         
   }         
}



void  __attribute__((section(".usercode"))) ErrorBoardSet(void)  
{
   LocalType   vtemp,vtemp1,vtemp2,vtemp3,vtemp4;
   
      if(errtime>ERR_DSP_TIME){
            ErrBdNamePt=0;
            errtime=0;

            vtemp4=errpt;
            do{
               errpt=(errpt+1)% ABS_ADDRESS;
               vtemp=errpt/8;
               vtemp1=errpt%8;
               vtemp3=errbd[vtemp];         
               vtemp2=0x01;
               vtemp2=vtemp2<<vtemp1;          
            }while(!(vtemp2 & vtemp3) && (vtemp4 != errpt) );
      
            if(vtemp2 & vtemp3){
               errbd[vtemp]=errbd[vtemp] & (~vtemp2);         
               vtemp=errpt+1;  
               ErrBdNamePt=BDid[vtemp];
               BdErrCntSeq[ErrBdNamePt]++; 
            }            
      }            
}

      







void    __attribute__((section(".usercode"))) Com0COMM(UserDataType Absadr,UserDataType Logadr,UserDataType cmd)
{
   RxBuffer[0]=(UserDataType)ENQ;
   
   src=COMPANY;
   HextoASCIIByte();
   RxBuffer[1]=firstdata;            
   RxBuffer[2]=seconddata;            

   src=Logadr;
   HextoASCIIByte();
   RxBuffer[3]=firstdata;   
   RxBuffer[4]=seconddata;   

   src=Absadr;
   HextoASCIIByte();
   RxBuffer[5]=firstdata;   
   RxBuffer[6]=seconddata;               
   
   src=cmd;
   HextoASCIIByte();
   RxBuffer[7]=firstdata;            
   RxBuffer[8]=seconddata;               
}



void    __attribute__((section(".usercode"))) MyDataTx(void)
{         
	LocalType  i,k;

    
	Com0COMM(MAS_A,LOG_ADR,NORMAL);

    RxBuffer[0] = ACK;

	src=0;
	HextoASCIIByte();
	RxBuffer[9]=firstdata;            
	RxBuffer[10]=seconddata;            

	src=0;
	HextoASCIIByte();
	RxBuffer[11]=firstdata;   
	RxBuffer[12]=seconddata;               
   
	src=0;
	HextoASCIIByte();
	RxBuffer[13]=firstdata;            
	RxBuffer[14]=seconddata;            

	k=17;   
   
	for(i=S0_FLOOR; i < mcurfloor ; i++ ){
		src=sRamDArry[i];
		HextoASCIIByte();
		RxBuffer[ k + 0]=firstdata;   
		RxBuffer[ k + 1]=seconddata;
		k=k+2;   
	}

	src= (k-17)/2;
	HextoASCIIByte();   
	RxBuffer[15]=firstdata;
	RxBuffer[16]=seconddata;

	RxBuffer[k+0]=(UserDataType)ETX;
	RxBuffer[k+1]=0;
      

	TXEN=0;  
	Serial();
}



/*
void    Com0COMM(UserDataType Absadr,UserDataType Logadr,UserDataType cmd)
{
   RxBuffer[0]=(UserDataType)ENQ;
   
   src=GROUP_ID;
   HextoASCIIByte();
   RxBuffer[1]=firstdata;            
   RxBuffer[2]=seconddata;            

   src=Logadr;
   HextoASCIIByte();
   RxBuffer[3]=firstdata;   
   RxBuffer[4]=seconddata;   

   src=Absadr;
   HextoASCIIByte();
   RxBuffer[5]=firstdata;   
   RxBuffer[6]=seconddata;               
   
   src=cmd;
   HextoASCIIByte();
   RxBuffer[7]=firstdata;            
   RxBuffer[8]=seconddata;               
}
*/



/*
void    __attribute__((section(".usercode"))) LdDataTx(void)
{
         
    unsigned int count;
    unsigned int chun,bek,sip,il;
    unsigned long tmpcalu;


    chun=(unsigned int)CurMeterPerMin;

    il=(chun%10);

    sip=(chun/10);
    sip=(sip%10);

    bek=(chun/100);
    bek=(bek%10);

    chun=chun/1000;
    chun=(chun%10);
                

    RxBuffer2[0]  = ACK;
    RxBuffer2[1]  = COMPANY;

    RxBuffer2[2]  = ' ';
    RxBuffer2[3]  = ' ';
    RxBuffer2[4]  = ' ';
    RxBuffer2[5]  = 'F';                            //1
    RxBuffer2[6]  = 'l';                            //2
    RxBuffer2[7]  = 'r';                            //3
    RxBuffer2[8]  = ' ';                            //4
	RxBuffer2[9]  = sRamDArry[DSP1];                //5
	RxBuffer2[10] = sRamDArry[DSP2];                //6
	RxBuffer2[11] = ' ';                            //7
	RxBuffer2[12] = ' ';                            //8
	RxBuffer2[13] = ' ';                            //9
	RxBuffer2[14] = ' ';                            //10
	RxBuffer2[15] = ' ';                            //11
	RxBuffer2[16] = chun + '0';                     //12
	RxBuffer2[17] = bek  + '0';                      //13 
	RxBuffer2[18] = sip  + '0';                      //14
	RxBuffer2[19] = '.';                            //15 
	RxBuffer2[20] = il   + '0';                       //16

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
	RxBuffer2[38] = ' ';                     //
	RxBuffer2[39] = ' ';                     //
	RxBuffer2[40] = ' ';                     //

	RxBuffer2[41]=ETX;
	RxBuffer2[42]=0;


//
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


	Serial2();

}
*/


void    __attribute__((section(".usercode"))) Find_Absolute(UserDataType Absadr,UserDataType Logadr,UserDataType cmd)
{                    
	LocalType i,j,k;      

	Com0COMM(Absadr,Logadr,cmd);  
   
    RxBuffer[0]=(UserDataType)ENQ;

	src=LadderData[C_CMDTYPE];
	HextoASCIIByte();
	RxBuffer[9]=firstdata;            
	RxBuffer[10]=seconddata;            

	src=LadderData[C_BASE_MEMORY];
	HextoASCIIByte();
	RxBuffer[11]=firstdata;   
	RxBuffer[12]=seconddata;               
   
	src=LadderData[C_OFFSET_MEMORY];
	HextoASCIIByte();
	RxBuffer[13]=firstdata;            
	RxBuffer[14]=seconddata;            

	if(LadderBuf[C_CMDTYPE] == FLASH_RD_WR){
        LadderData[C_DATA_CNT]=7;

    	src=(11 + LadderData[C_DATA_CNT]);
    	HextoASCIIByte();   
    	RxBuffer[15]=firstdata;
    	RxBuffer[16]=seconddata;

        j=17;
        k=0;
   		for(i=0;i<(LadderData[C_DATA_CNT] + 10);i++){
/*
   			if((New485Ladder[k+0] >= ' ') &&  (New485Ladder[k+0] < '0'))    (New485Ladder[k+0] = New485Ladder[k+0] + 0x80);    
   			if((New485Ladder[k+1] >= ' ') &&  (New485Ladder[k+1] < '0'))    (New485Ladder[k+1] = New485Ladder[k+1] + 0x80);    
   			RxBuffer[j+0]=New485Ladder[k+0];
   			RxBuffer[j+1]=New485Ladder[k+1];
            k=k+2;
   			j=j+2;
*/

/*

            src=New485Ladder[i];
   			HextoASCIIByte();   
   			RxBuffer[j+0]=firstdata;
   			RxBuffer[j+1]=seconddata;
   			j=j+2;
*/
   		}
    }       

    else{
    	src=(11 + LadderData[C_DATA_CNT]);
    	HextoASCIIByte();   
    	RxBuffer[15]=firstdata;
    	RxBuffer[16]=seconddata;

       	src=O_OP_bit;    
    	HextoASCIIByte();   
    	RxBuffer[17]=firstdata;
    	RxBuffer[18]=seconddata;   
            
    	src=O_U_W_bit;
    	HextoASCIIByte();   
    	RxBuffer[19]=firstdata;
    	RxBuffer[20]=seconddata;
       
    	src=O_Y_0_bit;
    	HextoASCIIByte();   
    	RxBuffer[21]=firstdata;
    	RxBuffer[22]=seconddata;
    
    	src=I_EMG_bit;
    	HextoASCIIByte();   
    	RxBuffer[23]=firstdata;
    	RxBuffer[24]=seconddata;
    
       
    	src=I_SU1_bit;
    
    	HextoASCIIByte();   
    	RxBuffer[25]=firstdata;
    	RxBuffer[26]=seconddata;
    
     
    ////
        src=OldFireBuf;
    /////
    
    	HextoASCIIByte();   
    	RxBuffer[27]=firstdata;
    	RxBuffer[28]=seconddata;
    
    	src=I_X0_bit;
    
    	HextoASCIIByte();   
    	RxBuffer[29]=firstdata;
    	RxBuffer[30]=seconddata;
    
    	src=(sRamDArry[mcurfloor]+1);
    	HextoASCIIByte();   
    	RxBuffer[31]=firstdata;
    	RxBuffer[32]=seconddata;
       
    	src=ErrBdNamePt;
    	HextoASCIIByte();   
    	RxBuffer[33]=firstdata;
    	RxBuffer[34]=seconddata;
       
    	src=sRamDArry[mSysStatus];
    
    	HextoASCIIByte();   
    	RxBuffer[35]=firstdata;
    	RxBuffer[36]=seconddata;
       
    	j=37;
          
    	if(LadderData[C_DATA_CNT] > 0){
    		for(i=0;i<LadderData[C_DATA_CNT];i++){
    			src=LadderData[C_SAVE_DATA+i];
    			HextoASCIIByte();   
    			RxBuffer[j+0]=firstdata;
    			RxBuffer[j+1]=seconddata;
    			j=j+2;
    		}
    	}
    }         
	RxBuffer[j+0]=(UserDataType)ETX;
	RxBuffer[j+1]=0;      
	TXEN=0;
	Serial();
}



/*
void  __attribute__((section(".usercode"))) FlashDataRdWr(void)
{
    LocalType j;

    if(LadderBuf[C_CMD] == READ_DATA){
        for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
            LadderBuf[C_SAVE_DATA + j] =    cF_FLRDATARD((unsigned long)(LadderBuf[C_OFFSET_MEMORY] + j)); 
        }
    }   

    if(LadderBuf[C_CMD] == WRITE_DATA){
        F_SetupData_ReSet(LadderBuf[C_OFFSET_MEMORY],LadderBuf[C_DATA_CNT]);
    }   

    LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
}
*/



void  __attribute__((section(".usercode"))) FlashDataRd(void)
{
   LocalType j;

   if(LadderBuf[C_OFFSET_MEMORY]      == O_eVer)            LadderBuf[C_OFFSET_MEMORY]=F_Ver0;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eTopFlr)         LadderBuf[C_OFFSET_MEMORY]=F_TopFlr;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_ePrkFlr)         LadderBuf[C_OFFSET_MEMORY]=F_PrkFlr;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eOpWtTm)         LadderBuf[C_OFFSET_MEMORY]=F_OpWtTm;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eOpTtTm)         LadderBuf[C_OFFSET_MEMORY]=F_OpTtTm;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eUserLamp)       LadderBuf[C_OFFSET_MEMORY]=F_UserLamp;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eFixFloor)       LadderBuf[C_OFFSET_MEMORY]=F_FixFloor;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eFixFloorTime)   LadderBuf[C_OFFSET_MEMORY]=F_FixFloorTime;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService0)    LadderBuf[C_OFFSET_MEMORY]=F_NonService0;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService1)    LadderBuf[C_OFFSET_MEMORY]=F_NonService1;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService2)    LadderBuf[C_OFFSET_MEMORY]=F_NonService2;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService3)    LadderBuf[C_OFFSET_MEMORY]=F_NonService3;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eFireSafeFlr)    LadderBuf[C_OFFSET_MEMORY]=F_FireSafeFlr;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_ePassward)       LadderBuf[C_OFFSET_MEMORY]=F_Passward0;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eSerialNm)       LadderBuf[C_OFFSET_MEMORY]=F_SerialNm0;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eSubDoorFlr1)    LadderBuf[C_OFFSET_MEMORY]=F_SubDoorFlr1;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eSubDoorFlr2)    LadderBuf[C_OFFSET_MEMORY]=F_SubDoorFlr2;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eSubDoorFlr3)    LadderBuf[C_OFFSET_MEMORY]=F_SubDoorFlr3;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eErrStopCnt)     LadderBuf[C_OFFSET_MEMORY]=F_ErrStopCnt;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eNextFlrTime)    LadderBuf[C_OFFSET_MEMORY]=F_NextFlrTime;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eLuLdOffTime)    LadderBuf[C_OFFSET_MEMORY]=F_LuLdOffTime;
   else if(LadderBuf[C_OFFSET_MEMORY] == O_eNcNoBit)        LadderBuf[C_OFFSET_MEMORY]=F_NcNoBit0;

   else if((LadderBuf[C_OFFSET_MEMORY] >= O_eFlrDspCh) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eFlrDspCh + 62))){  
        LadderBuf[C_OFFSET_MEMORY]=LadderBuf[C_OFFSET_MEMORY] - O_eFlrDspCh;
   }

   for(j=0;j < LadderBuf[C_DATA_CNT];j++){           
        LadderBuf[C_SAVE_DATA + j] =    cF_FLRDSPCH((LadderBuf[C_OFFSET_MEMORY] + j)); 
//      LadderBuf[C_SAVE_DATA + j] =    cF_FLRDATARD((unsigned long)(LadderBuf[C_OFFSET_MEMORY] + j)); 
   }   
}


void  __attribute__((section(".usercode"))) FlashDataWr(void)
{
    LocalType ack;
    
    ack=1;
     
    if(LadderBuf[C_OFFSET_MEMORY]      == O_eVer)            LadderBuf[C_OFFSET_MEMORY]=F_Ver0;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eTopFlr)         LadderBuf[C_OFFSET_MEMORY]=F_TopFlr;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_ePrkFlr)         LadderBuf[C_OFFSET_MEMORY]=F_PrkFlr;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eOpWtTm)         LadderBuf[C_OFFSET_MEMORY]=F_OpWtTm;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eOpTtTm)         LadderBuf[C_OFFSET_MEMORY]=F_OpTtTm;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eUserLamp)       LadderBuf[C_OFFSET_MEMORY]=F_UserLamp;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eFixFloor)       LadderBuf[C_OFFSET_MEMORY]=F_FixFloor;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eFixFloorTime)   LadderBuf[C_OFFSET_MEMORY]=F_FixFloorTime;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService0)    LadderBuf[C_OFFSET_MEMORY]=F_NonService0;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService1)    LadderBuf[C_OFFSET_MEMORY]=F_NonService1;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService2)    LadderBuf[C_OFFSET_MEMORY]=F_NonService2;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eNonService3)    LadderBuf[C_OFFSET_MEMORY]=F_NonService3;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eFireSafeFlr)    LadderBuf[C_OFFSET_MEMORY]=F_FireSafeFlr;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_ePassward)       LadderBuf[C_OFFSET_MEMORY]=F_Passward0;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eSerialNm)       LadderBuf[C_OFFSET_MEMORY]=F_SerialNm0;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eSubDoorFlr1)    LadderBuf[C_OFFSET_MEMORY]=F_SubDoorFlr1;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eSubDoorFlr2)    LadderBuf[C_OFFSET_MEMORY]=F_SubDoorFlr2;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eSubDoorFlr3)    LadderBuf[C_OFFSET_MEMORY]=F_SubDoorFlr3;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eErrStopCnt)     LadderBuf[C_OFFSET_MEMORY]=F_ErrStopCnt;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eNextFlrTime)    LadderBuf[C_OFFSET_MEMORY]=F_NextFlrTime;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eLuLdOffTime)    LadderBuf[C_OFFSET_MEMORY]=F_LuLdOffTime;
    else if(LadderBuf[C_OFFSET_MEMORY] == O_eNcNoBit)        LadderBuf[C_OFFSET_MEMORY]=F_NcNoBit0;
    else if((LadderBuf[C_OFFSET_MEMORY] >= O_eFlrDspCh) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eFlrDspCh + 62))){  
         LadderBuf[C_OFFSET_MEMORY]=LadderBuf[C_OFFSET_MEMORY] - O_eFlrDspCh;
    }
    else ack=0;

    if(ack)  F_SetupData_ReSet(LadderBuf[C_OFFSET_MEMORY],LadderBuf[C_DATA_CNT]);
}



void    __attribute__((section(".usercode"))) ReadEepDataOldType(void)
{
    LocalType i,j,data;

    i=(unsigned int)(LadderBuf[C_OFFSET_MEMORY]);
    for(j=0;j < LadderBuf[C_DATA_CNT];j++){
        data=(UserDataType)EEPROM_Read_Byte(i);
        eDArry[LadderBuf[C_OFFSET_MEMORY]+j] = (UserDataType)data;
        LadderBuf[C_SAVE_DATA + j] = (UserDataType)data; 
        i++;
    }        
}



void    __attribute__((section(".usercode"))) WriteEepDataOldType(void)
{
    LocalType i,j;

    i=(unsigned int)(LadderBuf[C_OFFSET_MEMORY]);
    for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
        EEPROM_Write_Byte(i,LadderBuf[C_SAVE_DATA+j]);
        eDArry[i]=LadderBuf[C_SAVE_DATA+j];	         		
        i++;
    }        
}


/*
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

#define SECONDLINE_BASE 18
#define DSP_VALUE_BASE  7
#define SECONDLINE_DATA SECONDLINE_BASE + DSP_VALUE_BASE

#define FLR_DSP_GROUP   1
#define FLR_GROUP       2
#define TIMER_GROUP     3
#define ONOFF_GROUP     4
#define IO_GROUP        5
#define USER_GROUP      6
#define OPEN_WAIT_GROUP 7


void  __attribute__((section(".usercode"))) Two_Digit(LocalType value)
{
    LocalType i,j,k;
    i=value;

    if(i>99)    i=0;

    j=(i/10);  
    i=(i%10);
  
    New485Ladder[SECONDLINE_DATA+0]=j + '0';  
    New485Ladder[SECONDLINE_DATA+1]=i + '0';  
}

void  __attribute__((section(".usercode"))) Three_Digit(LocalType value)
{
    LocalType i,j,k;
    i=value;
    if(i>999)   i=0;

    j=(i/100);  
    k=(i%100);  
    k=(i/10);  
    i=(i%10);
  
    New485Ladder[SECONDLINE_DATA+0]=j + '0';  
    New485Ladder[SECONDLINE_DATA+1]=k + '0';  
    New485Ladder[SECONDLINE_DATA+2]=i + '0';      
}


void  __attribute__((section(".usercode"))) Integer_Digit(LocalType value)
{
    LocalType i;
    i=value;
    if(i>65534)   i=0;

    New485Ladder[SECONDLINE_DATA+4]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+3]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+2]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+1]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+0]=(i%10) + '0';      
    
}


void  __attribute__((section(".usercode"))) FlrDspGroup(LocalType offset)
{
    LocalType i;
    i=(offset *2 );
    switch(EnterKey){
        case    0:
            New485Ladder[SECONDLINE_DATA+0]=cF_FLRDSPCH((unsigned long)i);  
            New485Ladder[SECONDLINE_DATA+1]=cF_FLRDSPCH((unsigned long)(i+1));          
            break;
        case    1:
        case    2:
            break;
    }
    if(EnterKey==0){
        New485Ladder[SECONDLINE_DATA+0]=cF_FLRDSPCH((unsigned long)i);  
        New485Ladder[SECONDLINE_DATA+1]=cF_FLRDSPCH((unsigned long)(i+1));          
    }
}


void  __attribute__((section(".usercode"))) FlrGroup(LocalType offset)
{
    LocalType i;
    
    i=(offset + F_TopFlr);

    i=cF_FLRDSPCH((unsigned long)i);    
    Two_Digit(i+1);     
}


void  __attribute__((section(".usercode"))) TimerGroup(LocalType offset)
{
    LocalType i;
    
    switch(offset){        
        case    16:
            i=iF_F_BrkStTm10;
            Integer_Digit(i);
            break;
        case    17:
            i=iF_F_BrkStTm20;
            Integer_Digit(i);
            break;
        case    18:
            i=iF_F_BrkStTm30;
            Integer_Digit(i);
            break;
        case    19:
            i=iF_F_BrkStTm40;
            Integer_Digit(i);
            break;
        case    20:
            i=iF_F_BrkStTm50;
            Integer_Digit(i);
            break;
        case    21:
            i=iF_F_BrkStTm60;
            Integer_Digit(i);
            break;
        default:
            i=(offset + F_OpWtTm);
            i=cF_FLRDSPCH((unsigned long)i);
            Three_Digit(i);     
            break;

    }    
}



void  __attribute__((section(".usercode"))) OnOffGroup(LocalType offset)
{
    LocalType i,j,k;
    k=0x01;
    j=(offset%8);
    i=(offset/8);
    
    i=(i + F_NonService0);

    i=cF_FLRDSPCH((unsigned long)i);
    
    k=(k << j);
    i=(i & k);

    if(i){   
        New485Ladder[SECONDLINE_DATA+0]='O';  
        New485Ladder[SECONDLINE_DATA+1]='n';  
    }
    else{
        New485Ladder[SECONDLINE_DATA+0]='O';  
        New485Ladder[SECONDLINE_DATA+1]='f';  
        New485Ladder[SECONDLINE_DATA+2]='f';      
    }
}



void  __attribute__((section(".usercode"))) IoGroup(LocalType offset)
{
    LocalType i;
    
    i=(offset + F_ManualSpeed);

    i=cF_FLRDSPCH((unsigned long)i);
    Two_Digit(i);     
}



void  __attribute__((section(".usercode"))) UserGroup(LocalType offset)
{
    LocalType i,j;

    switch(offset){
        case    0:
            i=(offset + F_Ver0);
            New485Ladder[SECONDLINE_DATA+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_DATA+1]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_DATA+2]='.';      
            New485Ladder[SECONDLINE_DATA+3]=cF_FLRDSPCH((unsigned long)(i+2));      
            break;
        case    1:
            i=(offset + F_Bd_Id);
            i=cF_FLRDSPCH((unsigned long)i);
            Three_Digit(i);     
            break;
        case    2:
            i=(offset + F_Passward0);
            New485Ladder[SECONDLINE_DATA+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_DATA+1]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_DATA+2]=cF_FLRDSPCH((unsigned long)(i+2));      
            New485Ladder[SECONDLINE_DATA+3]=cF_FLRDSPCH((unsigned long)(i+3));      
            break;
        case    3:
            i=(offset + F_SerialNm0);
            j=cF_FLRDSPCH((unsigned long)i+0);
            i=cF_FLRDSPCH((unsigned long)i+1);
            i=(i*255) + j;
            Integer_Digit(i);
            break;
        case    4:
            i=(offset + F_UserLamp);
            i=cF_FLRDSPCH((unsigned long)i+0);
            Integer_Digit(i);
            break;
        case    5:
            i=(offset + F_ErrStopCnt);
            i=cF_FLRDSPCH((unsigned long)i+0);
            Three_Digit(i);
            break;
        case    6:
            i=(offset + NC_F_user0);
            i=cF_FLRDSPCH((unsigned long)i+0);
            Three_Digit(i);
            break;
        case    7:
            i=(offset + NC_F_user1);
            i=cF_FLRDSPCH((unsigned long)i+0);
            Three_Digit(i);
            break;
        case    8:
            i=(offset + NC_F_user2);
            i=cF_FLRDSPCH((unsigned long)i+0);
            Three_Digit(i);
            break;
        case    9:
            i=(offset + NC_F_user3);
            i=cF_FLRDSPCH((unsigned long)i+0);
            Three_Digit(i);
            break;

    }
}




void  __attribute__((section(".usercode"))) OpenWaitGroup(LocalType offset)
{
    LocalType i;
    
    i=(offset + F_OpWtTm);

    i=cF_FLRDSPCH((unsigned long)i);
    Two_Digit(i);     
}




#define     ONEKEY        '1'      
#define     TWOKEY        '2'      
#define     THREEKEY      '3'      
#define     FOURKEY       '4'
#define     FIVEKEY       '5'      
#define     SIXKEY        '6'
#define     SEVENKEY      '7'      
#define     EIGHTKEY      '8'      
#define     NINEKEY       '9'      
#define     ZEROKEY       '0'
#define     ENTKEY        'e'      
#define     MENUKEY       'm'      
#define     ESCKEY        'c'      
#define     UPKEY         'u'      
#define     DOWNKEY       'd'
#define     LEFTKEY       'l'      
#define     RIGHTKEY      'r'
#define     ENTKEY        'e'      



unsigned int  __attribute__((section(".usercode"))) KeyCheck(void)
{
    LocalType ret;

    ret=0;

    if(LadderBuf[C_SAVE_DATA+0] != LadderKey){
        LadderKey = LadderBuf[C_SAVE_DATA+0];
        switch(LadderKey){
            case    ENTKEY:
                    EnterKey++;
                    break;
            case    MENUKEY:
                    LadderGroup=(LadderGroup+1)%8;
                    LadderGroupSub=0;
                    EnterKey=0;
                    break;
            case    ESCKEY:
                    LadderGroup=0;
                    LadderGroupSub=0;
                    EnterKey=0;
                    break;
            case    UPKEY:
                    if(EnterKey==0){
                        LadderGroupSub=(LadderGroupSub+1)%32;
                    }
                    break;
            case    DOWNKEY:
                    if(EnterKey==0){
                        if(LadderGroupSub>0)    LadderGroupSub--;
                        else                    LadderGroupSub=31;                    
                    }
                    break;
            case    LEFTKEY:
                    if(EnterKey==0){
                        if(LadderGroup>0)   LadderGroup--;
                        else                LadderGroup=7;
                        LadderGroupSub=0;
                    }
                    break;
            case    RIGHTKEY:
                    if(EnterKey==0){
                        LadderGroup=(LadderGroup+1)%8;
                        LadderGroupSub=0;
                    }
                    break;
            case    ONEKEY:
                    break;
            case    TWOKEY:
                    break;
            case    THREEKEY:
                    break;
            case    FOURKEY:
                    break;
            case    FIVEKEY:
                    break;
            case    SIXKEY:
                    break;
            case    SEVENKEY:
                    break;
            case    EIGHTKEY:
                    break;
            case    NINEKEY:
                    break;
            case    ZEROKEY:   
                    break;
            default:
                    ret=1;
                    LadderKey = 0xff;
                    break;
        }   
    }
    else    ret=1; 

    return(ret);
}

////////////////////new ladder////////////////////////////
unsigned int  __attribute__((section(".usercode"))) NewFlashData(void)
{
    LocalType i,j;

    KeyCheck();
          
    j=LadderGroup;

    if(j>0){    
        j=(LadderGroupSub+ ((j-1) * 32))+1;
    }

    for(i=0;i<16;i++){
        New485Ladder[i+2]=GroupLineMessage[j][i];
    }

        
    New485Ladder[0]=LadderKey;    
    New485Ladder[1]=' ';

	LadderBuf[C_BASE_MEMORY]=LadderGroup;              
	LadderBuf[C_OFFSET_MEMORY]=LadderGroupSub;          

    switch(LadderGroupSub){
        case    FLR_DSP_GROUP:
            FlrDspGroup(LadderGroupSub);
            break;
        case    FLR_GROUP:
            FlrGroup(LadderGroupSub);
            break;
        case    TIMER_GROUP:
            TimerGroup(LadderGroupSub);
            break;
        case    ONOFF_GROUP:
            OnOffGroup(LadderGroupSub);
            break;
        case    IO_GROUP:
            IoGroup(LadderGroupSub);
            break;
        case    USER_GROUP:
            UserGroup(LadderGroupSub);
            break;
        case    OPEN_WAIT_GROUP:
            OpenWaitGroup(LadderGroupSub);
            break;
        default:
            break;

    }

    return(0);
}
*/


////////////////////new ladder////////////////////////////


/*
void  __attribute__((section(".usercode"))) NewFlashDataRdWr(void)
{
           
    if(LadderBuf[C_CMD] == READ_DATA){
        if(LadderBuf[C_OFFSET_MEMORY] == O_eMvCounter){
            LadderBuf[C_OFFSET_MEMORY] = eMvCounter;
            ReadEepDataOldType();
        }
        else if((LadderBuf[C_OFFSET_MEMORY] >= O_eSysErCnt) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eSysErCnt + 48))){  
            LadderBuf[C_OFFSET_MEMORY] = LadderBuf[C_OFFSET_MEMORY] - O_eSysErCnt;
            ReadEepDataOldType();
        }
        else{
            NewFlashDataRd();
        }
        LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
   }

   else if(LadderBuf[C_CMD] == WRITE_DATA){
        if(LadderBuf[C_OFFSET_MEMORY] == O_eMvCounter){
            LadderBuf[C_OFFSET_MEMORY] = eMvCounter;
            WriteEepDataOldType();
        }
        else if((LadderBuf[C_OFFSET_MEMORY] >= O_eSysErCnt) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eSysErCnt + 48))){  
             eDArry[eErrCntPt]=0;
             sRamDArry[mBefErrCntPt]=0;                

            LadderBuf[C_OFFSET_MEMORY] = LadderBuf[C_OFFSET_MEMORY] - O_eSysErCnt;
            WriteEepDataOldType();
        }
        else{
            FlashDataWr();
        }

        LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
    }   
}
*/
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

void  __attribute__((section(".usercode"))) EepDataRdWr(void)
{
       
    if(LadderBuf[C_CMD] == READ_DATA){
        if(LadderBuf[C_OFFSET_MEMORY] == O_eMvCounter){
            LadderBuf[C_OFFSET_MEMORY] = eMvCounter;
            ReadEepDataOldType();
        }
        else if((LadderBuf[C_OFFSET_MEMORY] >= O_eSysErCnt) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eSysErCnt + 48))){  
            LadderBuf[C_OFFSET_MEMORY] = LadderBuf[C_OFFSET_MEMORY] - O_eSysErCnt;
            ReadEepDataOldType();
        }
        else{
            FlashDataRd();
        }
        LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
   }

   else if(LadderBuf[C_CMD] == WRITE_DATA){
        if(LadderBuf[C_OFFSET_MEMORY] == O_eMvCounter){
            LadderBuf[C_OFFSET_MEMORY] = eMvCounter;
            WriteEepDataOldType();
        }
        else if((LadderBuf[C_OFFSET_MEMORY] >= O_eSysErCnt) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eSysErCnt + 48))){  
             eDArry[eErrCntPt]=0;
             sRamDArry[mBefErrCntPt]=0;                

            LadderBuf[C_OFFSET_MEMORY] = LadderBuf[C_OFFSET_MEMORY] - O_eSysErCnt;
            WriteEepDataOldType();
        }
        else{
            FlashDataWr();
        }

        LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
    }   
}






void  __attribute__((section(".usercode"))) EepRamDataRdWr(void)
{
    LocalType j;

    if(LadderBuf[C_CMD] == READ_DATA){
        if(LadderBuf[C_OFFSET_MEMORY] == O_eMvCounter){
            LadderBuf[C_OFFSET_MEMORY] = eMvCounter;
            for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
                LadderBuf[C_SAVE_DATA + j] = eDArry[LadderBuf[C_OFFSET_MEMORY]+j]; 
            }   
        }
        else if((LadderBuf[C_OFFSET_MEMORY] >= O_eSysErCnt) &&  (LadderBuf[C_OFFSET_MEMORY] <= (O_eSysErCnt + 48))){  
            LadderBuf[C_OFFSET_MEMORY] = LadderBuf[C_OFFSET_MEMORY] - O_eSysErCnt;
            for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
                LadderBuf[C_SAVE_DATA + j] = eDArry[LadderBuf[C_OFFSET_MEMORY]+j]; 
            }   
        }
        else{
            FlashDataRd();
        }

        LadderBuf[C_CMDTYPE]= LadderBuf[C_CMDTYPE] + RET_GOOD;
    }
    else if(LadderBuf[C_CMD] == WRITE_DATA){
/*???????????????????????????????????????????????????*/
/*???????????????????????????????????????????????????*/
/*???????????????????????????????????????????????????*/
/*???????????????????????????????????????????????????*/
        for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
            eDArry[LadderBuf[C_OFFSET_MEMORY]+j] = LadderBuf[C_SAVE_DATA+j];
        }        
        LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
    }  
}


void  __attribute__((section(".usercode"))) Ram0DataRdWr(void)
{
   LocalType i,j,k;
   
   if((LadderBuf[C_CMD] == READ_DATA) || (LadderBuf[C_CMD] == BIT_READ_DATA)){
      for(i=0;i < LadderBuf[C_DATA_CNT];i++){   
         LadderBuf[C_SAVE_DATA + i] = sRamDArry[LadderBuf[C_OFFSET_MEMORY]+i];                        
      }        
      LadderBuf[C_CMDTYPE]= LadderBuf[C_CMDTYPE] + RET_GOOD;
   }

   else if(LadderBuf[C_CMD] == WRITE_DATA){
      for(j=0;j < LadderBuf[C_DATA_CNT];j++){   
         sRamDArry[LadderBuf[C_OFFSET_MEMORY]+j] = LadderBuf[C_SAVE_DATA+j];
      }              
      LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;      
   }  
   else if(LadderBuf[C_CMD] == BIT_WRITE_DATA){
      i=0;
      for(j=1;j < LadderBuf[C_DATA_CNT];j++){
         k=LadderBuf[C_SAVE_DATA+j];
         if(k){   
            sRamDArry[LadderBuf[C_BASE_MEMORY]+i] = (sRamDArry[LadderBuf[C_BASE_MEMORY]+i] | k);
         }           
         else{             
            sRamDArry[LadderBuf[C_BASE_MEMORY]+i] = (sRamDArry[LadderBuf[C_BASE_MEMORY]+i] & ~LadderBuf[C_OFFSET_MEMORY]);
         }           
         i=i+LadderBuf[C_SAVE_DATA];
      }        
      LadderBuf[C_CMDTYPE] = LadderBuf[C_CMDTYPE] + RET_GOOD;
   }  
   
   if(LadderBuf[C_OFFSET_MEMORY] == ExtCmdFlrONOFF0) ExtCmdFlrONOFFCnt=0;	
}


void  __attribute__((section(".usercode"))) Ram0DataRdWrLong(void)
{   
    unsigned long a;
    unsigned int  i;

	if(LadderBuf[C_CMDTYPE] == LONG_READ_DATA){         

        if(LadderBuf[C_OFFSET_MEMORY] < SAVE_CUR_PULSE){
            a = GET_LONG(LadderBuf[C_OFFSET_MEMORY]);
        }
        else{
            a = CurPulse;
        }


        for(i=0;i<4;i++){ 
            LadderBuf[C_SAVE_DATA + i] = (UserDataType)a;
            a=a>>8;                        
        }
    
        LadderBuf[C_CMDTYPE]= LadderBuf[C_CMDTYPE] + RET_GOOD;
    }

	else if(LadderBuf[C_CMDTYPE] == LONG_WR_DATA){         
        F_SetupData_ReSet(LadderBuf[C_OFFSET_MEMORY],LadderBuf[C_DATA_CNT]);
    }
}


void  __attribute__((section(".usercode"))) VipCarKeyClr(void)
{
  if(S3_VIP1){
    sRamDArry[mEqualFloor]=(sRamDArry[mEqualFloor] & ~UPDN_READY);
    sRamDArry[mHighFloor] =(sRamDArry[mHighFloor] & ~UPDN_READY);
    sRamDArry[mLowFloor]  =(sRamDArry[mLowFloor] & ~UPDN_READY);
     
    if(!(sRamDArry[mEqualFloor] & CAR_READY))  sRamDArry[mEqualFloor]=0;
    if(!(sRamDArry[mHighFloor] & CAR_READY))  sRamDArry[mHighFloor]=0;	
    if(!(sRamDArry[mLowFloor] & CAR_READY))   sRamDArry[mLowFloor]=0;
  }
}


void  __attribute__((section(".usercode"))) SaveReceiveData(void)
{	
	LadderBuf[C_CMD]=RcvBuf[RCV_CMD];               
   	LadderBuf[C_CMDTYPE]=RcvBuf[RCV_CMDTYPE];             
	LadderBuf[C_BASE_MEMORY]=RcvBuf[RCV_BASE_ADR];              
	LadderBuf[C_OFFSET_MEMORY]=RcvBuf[RCV_OFFS_ADR];          
	LadderBuf[C_DATA_CNT]=RcvBuf[RCV_DATA_CNT];
                        
	LadderBuf[C_SAVE_DATA+0]=RcvBuf[RCV_DATA+0];             
	LadderBuf[C_SAVE_DATA+1]=RcvBuf[RCV_DATA+1];             
	LadderBuf[C_SAVE_DATA+2]=RcvBuf[RCV_DATA+2];             
	LadderBuf[C_SAVE_DATA+3]=RcvBuf[RCV_DATA+3];             
	LadderBuf[C_SAVE_DATA+4]=RcvBuf[RCV_DATA+4];                               


	if(LadderBuf[C_CMDTYPE] == RW_EEP_AREA)           EepDataRdWr();       
	else if(LadderBuf[C_CMDTYPE] == RW_SRAM0_AREA)    Ram0DataRdWr();         
	else if(LadderBuf[C_CMDTYPE] == LONG_READ_DATA)   Ram0DataRdWrLong();         
	else if(LadderBuf[C_CMDTYPE] == LONG_WR_DATA)     Ram0DataRdWrLong();         
	else if(LadderBuf[C_CMDTYPE] == RW_EEP_RAM_AREA)  EepRamDataRdWr();       
	else if(LadderBuf[C_CMDTYPE] == FLASH_RD_WR)      EepRamDataRdWr();       



/*
	if(LadderBuf[C_CMDTYPE] == RW_EEP_AREA)           EepDataRdWr();       
	else if(LadderBuf[C_CMDTYPE] == RW_SRAM0_AREA)    Ram0DataRdWr();         
	else if(LadderBuf[C_CMDTYPE] == RW_EEP_RAM_AREA)  EepDataRdWr();       
	else if(LadderBuf[C_CMDTYPE] == FLASH_RD_WR)      NewFlashData();       
*/

	if((RcvBuf[RCV_ABSADR] == A_LD) || (RcvBuf[RCV_ABSADR] == A_PC)){ 		
		FhmLoaderTime=0;   	

		LadderData[C_CMD]=LadderBuf[C_CMD];             
		LadderData[C_CMDTYPE]=LadderBuf[C_CMDTYPE];              
		LadderData[C_BASE_MEMORY]=LadderBuf[C_BASE_MEMORY];               
		LadderData[C_OFFSET_MEMORY]=LadderBuf[C_OFFSET_MEMORY];              

		LadderData[C_DATA_CNT]=LadderBuf[C_DATA_CNT];
                        
		LadderData[C_SAVE_DATA+0]=LadderBuf[C_SAVE_DATA+0];               
		LadderData[C_SAVE_DATA+1]=LadderBuf[C_SAVE_DATA+1];               
		LadderData[C_SAVE_DATA+2]=LadderBuf[C_SAVE_DATA+2];               
		LadderData[C_SAVE_DATA+3]=LadderBuf[C_SAVE_DATA+3];               
		LadderData[C_SAVE_DATA+4]=LadderBuf[C_SAVE_DATA+4];                                    
	}

     VipCarKeyClr();
}



void  __attribute__((section(".usercode"))) SerialCheck(void)
{

  LocalType tmp;     

  if(RxStatus==RX_GOOD){      
    if((RcvBuf[RCV_CMD] == ADR_SET_REC) && (RcvBuf[RCV_LOGADR] == LogAddress+1) && (RcvBuf[RCV_ABSADR] == AbsAddress) ){                     

	  LadderData[C_CMDTYPE]=RcvBuf[RCV_CMDTYPE];

      if(LogAddress < 99){
        for(tmp=0; tmp <= LogAddress;tmp++){
          if(RcvBuf[RCV_ABSADR] == BDid[tmp]){ 
            if(BdErrCntSeq[BDid[tmp]] > 5){                                                     
              Find_Absolute(RcvBuf[RCV_ABSADR],tmp,ADR_SET_ACK);
            }                     
            tmp=250;                     
          }                 
        }

        if(tmp<250){
          LogAddress++;
          Find_Absolute(RcvBuf[RCV_ABSADR],LogAddress,ADR_SET_ACK);
          BDid[LogAddress]=RcvBuf[RCV_ABSADR];
        }               
      }            
    }
    else{      
      if((RcvBuf[RCV_CMD] == NORMAL) || (RcvBuf[RCV_CMD] == NO_DATA)){
        BdErrCntSeq[RcvBuf[RCV_ABSADR]]=0;                 
      }                 
      else if( (RcvBuf[RCV_CMD] == WRITE_DATA) || (RcvBuf[RCV_CMD] == READ_DATA) || (RcvBuf[RCV_CMD] == LONG_READ_DATA) ||
               (RcvBuf[RCV_CMD] == BIT_WRITE_DATA) ||  (RcvBuf[RCV_CMD] == BIT_READ_DATA)){           
          if(RcvBuf[RCV_GROUP] == COMPANY){           
            SaveReceiveData();
          }              
          BdErrCntSeq[RcvBuf[RCV_ABSADR]]=0;
      }            
         
      CurRcvAdr=RcvBuf[RCV_LOGADR];         
      ErrorSet();
      BefRcvAdr=CurRcvAdr;
      TimeOutBd=CurRcvAdr;         
      RxStatus=STX_CHK;                      

      Test485++;  
    }
    
    SerialLoopMaxTime=0;      
    if(RxStatus == RX_GOOD)  RxStatus = STX_CHK;	
  }         
                           
  if(TimeOutBd > LogAddressLoop){
    if(!bFindBoard){          
      LogAddressLoop=LogAddressLoop+1;
      CurRcvAdr=LogAddressLoop;

      ErrorSet();

      AbsAddress++;
      if(AbsAddress>ABS_ADDRESS) AbsAddress=1;         
      Find_Absolute(AbsAddress,LogAddress+1,ADR_SET_SEND);
      bFindBoard=1;         
      ExtCmdFlrONOFFCnt++;
    }
    else{      	
      BefRcvAdr=0;
      CurRcvAdr=0;
      TimeOutBd=0;
      MyDataTx();
      LogAddressLoop=LogAddress;                  
      bFindBoard=0;                  
      disp_clk_regs();
    }                  
  }  
           
    ErrorBoardSet();
              
  return;
}



void  __attribute__((section(".usercode"))) Serial2Check(void)
{

    if(RxStatus2==RX_GOOD){      
        RxStatus2=STX_CHK;                        
    }         
                           
    if((RxStatus2 != TX_SET) && (SerialTime2 > 10)){
        LdDataTx();
        SerialTime2=0;
    }               

}



UserDataType	__attribute__((section(".usercode"))) SubDoorFlrChk(void)
{

  if((cF_SUBDOORFLR1 ==  sRamDArry[mcurfloor])
	|| (cF_SUBDOORFLR2 ==  sRamDArry[mcurfloor])
	|| (cF_SUBDOORFLR3 ==  sRamDArry[mcurfloor])){				
		return(0);		
  }
  else	return(1);	
}	


UserDataType __attribute__((section(".usercode"))) MainOpenKeyCheck(void)
{   
	LocalType	ret;
		 	
   	if(sRamDArry[mDoor] & 0x01){   
        if(!S2_FIRE1){
            if(bFindBoard )	sRamDArry[mDoor] = (sRamDArry[mDoor] & 0xfe);
        }

		if(!SubDoorFlrChk()){
			if(bSelDoor == MAIN_DOOR){
				ret=0;
			}
			else if((bSelDoor == SUB_DOOR) && !S3_OPEN_SUB1){
				bSelDoor = MAIN_DOOR;
				ret=0;
			}
			else{
				ret=1;
			}			
		}
		else{
			bSelDoor = MAIN_DOOR;
            if(!S2_FIRE1){
	   		    if(bFindBoard ) sRamDArry[mDoor]=(sRamDArry[mDoor] & 0xf3);   
            }
			ret=0;
		}		
	}
   	else{
		ret=1;
	}   		
		
	return(ret);
}



UserDataType __attribute__((section(".usercode"))) MainCloseKeyCheck(void)
{
	LocalType	ret;
		
   	if(sRamDArry[mDoor] & 0x02){   
        if(!S2_FIRE1){
    		if(bFindBoard ) sRamDArry[mDoor] = (sRamDArry[mDoor] & 0xfd);										   	
        }

		if(!SubDoorFlrChk()){
			if(bSelDoor == MAIN_DOOR){
				ret=0;
			}
			else if((bSelDoor == SUB_DOOR) && bDoorCloseOk){
				bSelDoor = MAIN_DOOR;
				ret=0;
			}
			else{
				ret=1;
			}
		}
		else{
			bSelDoor = MAIN_DOOR;
            if(!S2_FIRE1){
    	   		if(bFindBoard ) sRamDArry[mDoor]=(sRamDArry[mDoor] & 0xf3);   
            }
			ret=0;
		}										

	}
   	else{
		ret=1;
	}   		 

	return(ret);
}



UserDataType __attribute__((section(".usercode"))) SubOpenKeyCheck(void)
{
   	if(sRamDArry[mDoor] & 0x04){   
        if(!S2_FIRE1){
   		    if(bFindBoard) sRamDArry[mDoor]=(sRamDArry[mDoor] & 0xfb);   
        }

		if(!SubDoorFlrChk()){
			if(bSelDoor == SUB_DOOR){
				return(0);
			}
			else if((bSelDoor == MAIN_DOOR) && !S1_OPEN1){
				bSelDoor = SUB_DOOR;
				return(0);
			}
			else{
				return(1);
			}
		}
		else{
			bSelDoor = MAIN_DOOR;
            if(!S2_FIRE1){
       		    if(bFindBoard) sRamDArry[mDoor]=(sRamDArry[mDoor] & 0xf3);   
            }
			return(0);				
		}							
	}
   	else{
   		return(1);
	}   		 
}


UserDataType __attribute__((section(".usercode"))) SubCloseKeyCheck(void)
{
   	if(sRamDArry[mDoor] & 0x08){   
        if(!S2_FIRE1){
   		    if(bFindBoard) sRamDArry[mDoor]=(sRamDArry[mDoor] & 0xf7);   
        }

		if(!SubDoorFlrChk()){
			if(bSelDoor == SUB_DOOR){
				return(0);
			}
			else if((bSelDoor == MAIN_DOOR) && bDoorCloseOk){
				bSelDoor = SUB_DOOR;
				return(0);
			}
			else{
				return(1);
			}
		}							
		else{
			bSelDoor = MAIN_DOOR;
            if(!S2_FIRE1){
	   		    if(bFindBoard) sRamDArry[mDoor]=(sRamDArry[mDoor] & 0xf3);   
            }
			return(0);				
		}							
	}
   	else{
   		return(1);
	}   		 
}


UserDataType	__attribute__((section(".usercode"))) OpenKeyCheck(void)
{
	if(MainOpenKeyCheck()){
		if(!SubOpenKeyCheck())	return(0);
		else					return(1);
	}
	else						return(0);		
	
}

UserDataType	__attribute__((section(".usercode"))) CloseKeyCheck(void)
{
	if(MainCloseKeyCheck()){
		if(!SubCloseKeyCheck())	return(0);
		else					return(1);
	}
	else  					return(0);			
}




void  __attribute__((section(".usercode"))) ClrUpDnWard(void)
{        
    S2_DN1=0;
    S1_UP1=0;                                                     //up
    S3_SHIFT1=0;
 
    bUpWard=0;              
    bDnWard=0;              
}


void  __attribute__((section(".usercode"))) UpWard(void)
{    
   S2_DN1=0;
   S1_UP1=1;
   bUpWard=1;              
   bDnWard=0;             
   
   if(OUT_U_W)      S3_SHIFT1=1; //shift
   else             S3_SHIFT1=0; //shift
}


void  __attribute__((section(".usercode"))) DnWard(void)
{    
   S2_DN1=1;
   S1_UP1=0;         
   bUpWard=0;              
   bDnWard=1;              
   
   if(OUT_D_W)   S3_SHIFT1=1; //shift
   else          S3_SHIFT1=0; //shift
}


UserDataType  __attribute__((section(".usercode"))) ReadyAndNoKeyCheck(void)
{
	if((sRamDArry[mDoorSeq] == READY_ELEVATOR) && 
            (sRamDArry[mEqualFloor] == 0) && 
            (sRamDArry[mHighFloor] == 0) && 
            (sRamDArry[mLowFloor] == 0)){  
     	return(0);       
	}                      
	else	return(1);
}


void  __attribute__((section(".usercode"))) Virtual_Floor_Set(UserDataType vFloor)
{
	if(sRamDArry[mcurfloor] > vFloor){
     	sRamDArry[mLowFloor] = vFloor | CAR_READY;                     
     }
     else if(sRamDArry[mcurfloor] < vFloor){
		sRamDArry[mHighFloor] = vFloor | CAR_READY;                     
	}
}




void  __attribute__((section(".usercode"))) CarKeyClr(void)
{
	sRamDArry[mEqualFloor]=(sRamDArry[mEqualFloor] & ~CAR_READY);
	sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] & ~CAR_READY);	
	sRamDArry[mLowFloor]=(sRamDArry[mLowFloor] & ~CAR_READY);
}


void  __attribute__((section(".usercode"))) KeyClr(void)
{
	sRamDArry[mEqualFloor]=0x0;
	sRamDArry[mHighFloor]=0x0;	
	sRamDArry[mLowFloor]=0x0;
    sRamDArry[mAckStopFloor] = 0x0;
    sRamDArry[mNewAckStopFloor]=0x0;
}



void   __attribute__((section(".usercode"))) CarAllStopCmd(void)
{

    OUT_U_W=0;                                                               
    OUT_D_W=0;                                                               
    OUT_P3=0;                                                         
    OUT_P1=0;                                                         
    OUT_P2=0;

//	OUT_P4=0;   
    if(RUN_MODE == LG_INVERTER_ELEV)    OUT_P4N=0;
    else                                OUT_P4N=1;


    OUT_DAC=0;
	
	bManualStop=1;

    ManualStopTime=0;

   	OUT_BRK=0;   
   	OUT_BK2=0;   

//      	if(IN_DLS)		    bHomeUpDn = 1;                   
//      	else if(IN_ULS)     bHomeUpDn = 0;                   
//      	else                bHomeUpDn = 0;

    S2_CAR_MOVE1=0;
    
    S3_UPDN_VO1=0;
    
    ClrUpDnWard();
    
    bMoveCar=0;
    bCarUpMove=0;
    bCarDnMove=0;
    
    sRamDArry[mReqStopFloor]=0;      
    sRamDArry[mCarMoveState]=0;
    KeyClr();     
}



void   __attribute__((section(".usercode"))) CarAllStopCmdTest(void)
{
    unsigned long i,j;
 
    if(!bManualStop){
        ManualStopTime=0;
    }           


    bManualStop=1;

    
    OUT_DAC=0;

//	OUT_U_W=0;                  //jina                                             
//	OUT_D_W=0;                  //jina                                             
	OUT_P3=0;                                                         
	OUT_P1=0;                                                         
	OUT_P2=0;           

//	OUT_P4=0;           
    if(RUN_MODE == LG_INVERTER_ELEV)    OUT_P4N=0;
    else                                OUT_P4N=1;
    	
	if(ManualStopTime > 10){        
      	OUT_BRK=0;   
      	OUT_BK2=0;   
	}

	if(ManualStopTime > 15){        
		bManualStop=0;

      	OUT_BRK=0;   
      	OUT_BK2=0;   

	    OUT_U_W=0;                                                               
	    OUT_D_W=0;                                                               

      	if(IN_DLS)		    bHomeUpDn = 1;                   
      	else if(IN_ULS)     bHomeUpDn = 0;
      	else if(!IN_BAT)    bHomeUpDn = 1;

      	else if(!IN_LU && IN_LD)    bHomeUpDn = 1;
      	else if(IN_LU && !IN_LD)    bHomeUpDn = 0;

      	else if(CurPulse <= FLOOR_COUNT(0)){
            bHomeUpDn = 1;    
        }
      	else if(CurPulse >= FLOOR_COUNT(cF_TOPFLR)){
            bHomeUpDn = 0;    
        }
      	else if(CurPulse <= FLOOR_COUNT(sRamDArry[mcurfloor])){
            if(sRamDArry[mcurfloor]>0){
                i=FLOOR_COUNT(sRamDArry[mcurfloor]);
                j=CurPulse;
                TmpFhmCounter1=(unsigned long)(i-j);

                i=FLOOR_COUNT(sRamDArry[mcurfloor]-1);
                j=CurPulse;
                TmpFhmCounter2=(unsigned long)(j-i);
                                    
                if(TmpFhmCounter1 >= TmpFhmCounter2)    bHomeUpDn = 0;    
                else                                    bHomeUpDn = 1;    
            }
            else    bHomeUpDn = 1;
        }
      	else if(CurPulse >= FLOOR_COUNT(sRamDArry[mcurfloor])){
            if(sRamDArry[mcurfloor] < cF_TOPFLR){
                i=FLOOR_COUNT(sRamDArry[mcurfloor]);
                j=CurPulse;
                TmpFhmCounter1=(unsigned long)(j-i);

                i=FLOOR_COUNT(sRamDArry[mcurfloor]+1);
                j=CurPulse;
                TmpFhmCounter2=(unsigned long)(i-j);

                if(TmpFhmCounter1 >= TmpFhmCounter2)    bHomeUpDn = 1;    
                else                                    bHomeUpDn = 0;    

            }
            else    bHomeUpDn = 0;
        }

      	else                bHomeUpDn = 0;


        S2_CAR_MOVE1=0;

        S3_UPDN_VO1=0;

      	ClrUpDnWard();
      
      	bMoveCar=0;
        bCarUpMove=0;
        bCarDnMove=0;

      	sRamDArry[mReqStopFloor]=0;      
      	sRamDArry[mCarMoveState]=0;
        KeyClr();     
	}       
}


void   __attribute__((section(".usercode")))  MotorStop(void)
{
    if(	!OUT_U_W && !OUT_D_W && !OUT_P1 && !OUT_P2 && !OUT_P3 && !OUT_BRK && !OUT_BK2){
        if(!bCarOnceStop){
            CarOnceStopTime=0;
            bCarOnceStop=1;
        }
    }                
    else{
        bCarOnceStop=0;
    }
}




void  __attribute__((section(".usercode"))) CallMeUpDnDirectionSet(void)
{			
   	if(bUpWard){
      	if(sRamDArry[mcurfloor] == cF_TOPFLR){
      		sRamDArry[mAckStopFloor]=(sRamDArry[mcurfloor] | DN_READY);
			bCarUpDnChButClr=1;
      		DnWard();
		}      		
      	else if(sRamDArry[mAckStopFloor] & UP_READY){
            UpWard();      	
          	if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
    			bCarUpDnChButClr=1;
      	    }        
      	} 
      	else if((sRamDArry[mAckStopFloor] & UPDN_CAR_READY) == DN_READY){
			bCarUpDnChButClr=1;
            DnWard();      	
      	} 
      	else if(sRamDArry[mDoor] & UPDN_CAR_READY){
            UpWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
      	} 
      	else if(sRamDArry[mMostLongDst] & UPDN_CAR_READY){
            UpWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
      	} 
      	else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
            UpWard();
      	}        
      	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
			bCarUpDnChButClr=1;
         	DnWard();
      	} 
      	else{
            ClrUpDnWard();
			bCarUpDnChButClr=1;
        }
   	}
   	else if(bDnWard){
      	if(sRamDArry[mcurfloor] == 0){
      	 	UpWard();
			bCarUpDnChButClr=1;
      	 	sRamDArry[mAckStopFloor] = (sRamDArry[mcurfloor] | UP_READY);
		}      	 	
      	else if(sRamDArry[mAckStopFloor] & DN_READY){
            DnWard();      	
          	if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
    			bCarUpDnChButClr=1;
      	    }        
      	}
      	else if((sRamDArry[mAckStopFloor] & UPDN_CAR_READY) == UP_READY){
			bCarUpDnChButClr=1;
            UpWard();      	
      	} 
      	else if(sRamDArry[mDoor] & UPDN_CAR_READY){
            DnWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
      	}      	
      	else if(sRamDArry[mMostLongDst] & UPDN_CAR_READY){
            DnWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
      	} 

      	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
            DnWard();
      	} 
      	else if(sRamDArry[mHighFloor] & UPDN_READY){ 
			bCarUpDnChButClr=1;
         	UpWard();
      	}      
      	else{ 
            ClrUpDnWard();
			bCarUpDnChButClr=1;
      	}

   	}
  	else{
		if(sRamDArry[mEqualFloor] & UP_READY){
			UpWard();
      	} 
      	else if(sRamDArry[mEqualFloor] & DN_READY){
			DnWard();
      	}      
		else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
			UpWard();
     	} 
     	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
  			DnWard();
     	} 
  	
        bCarUpDnChButClr=1;	
   	}
	S3_SHIFT1=0; //shift   
}



void __attribute__((section(".usercode")))  HighLowCallClear(void)
{

/*
    if(bUpWard){
		sRamDArry[mLowFloor] = 0x0;	
    	if(((sRamDArry[mHighFloor] & ONLY_FLR) < (sRamDArry[mReqStopFloor] & ONLY_FLR)) && !IN_UND){
            if(sRamDArry[mDoor] & UPDN_CAR_READY)   sRamDArry[mHighFloor]=(cF_TOPFLR | (sRamDArry[mDoor] & UPDN_CAR_READY));	        
            else                                    sRamDArry[mHighFloor]=(sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY;
            sRamDArry[mDoor]=sRamDArry[mDoor] & ~UPDN_CAR_READY;
        }
    	else if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
            if(sRamDArry[mDoor] & UPDN_CAR_READY)   sRamDArry[mHighFloor]=(cF_TOPFLR | (sRamDArry[mDoor] & UPDN_CAR_READY));	        
            else                                    sRamDArry[mHighFloor]=(sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY;
            sRamDArry[mDoor]=sRamDArry[mDoor] & ~UPDN_CAR_READY;
        }
    }
	
    if(bDnWard){
		sRamDArry[mHighFloor] = 0x0;	
    	if(((sRamDArry[mLowFloor] & ONLY_FLR) > (sRamDArry[mReqStopFloor] & ONLY_FLR)) && !IN_UND){
            if(sRamDArry[mDoor] & UPDN_CAR_READY)   sRamDArry[mLowFloor]=(sRamDArry[mDoor] & UPDN_CAR_READY);	        
            else                                    sRamDArry[mLowFloor]=(sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY;
            sRamDArry[mDoor]=sRamDArry[mDoor] & ~UPDN_CAR_READY;
        }
    	else if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
            if(sRamDArry[mDoor] & UPDN_CAR_READY)   sRamDArry[mLowFloor]=(sRamDArry[mDoor] & UPDN_CAR_READY);	        
            else                                    sRamDArry[mLowFloor]=(sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY;
            sRamDArry[mDoor]=sRamDArry[mDoor] & ~UPDN_CAR_READY;
        }
    }	
*/


    if(bUpWard){
		sRamDArry[mLowFloor] = 0x0;	
    	if(((sRamDArry[mHighFloor] & ONLY_FLR) < (sRamDArry[mReqStopFloor] & ONLY_FLR)) && !IN_UND){
            sRamDArry[mHighFloor]=0x0;
//            sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
//            sRamDArry[mMostLongDst] = 0;        
        }
    }	
    else if(bDnWard){
		sRamDArry[mHighFloor] = 0x0;	
    	if(((sRamDArry[mLowFloor] & ONLY_FLR) > (sRamDArry[mReqStopFloor] & ONLY_FLR)) && !IN_UND){
            sRamDArry[mLowFloor]=0x0;
//            sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
//            sRamDArry[mMostLongDst] = 0;        
        }
    	else if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
            sRamDArry[mLowFloor]=0x0;
//            sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
//            sRamDArry[mMostLongDst] = 0;        
        }
    }


	if((sRamDArry[mEqualFloor] & ONLY_FLR) != sRamDArry[mcurfloor]){
		sRamDArry[mEqualFloor] = 0x0;	
	}				


	if(!(sRamDArry[mEqualFloor] & UPDN_CAR_READY)){
		sRamDArry[mEqualFloor]=0x0;	
	}
	if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
		sRamDArry[mLowFloor]=0x0;	
	}
	if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
		sRamDArry[mHighFloor]=0x0;	
	}

    if((sRamDArry[mHighFloor] & ONLY_FLR) > cF_TOPFLR)	sRamDArry[mHighFloor]=0;
     
    if((sRamDArry[mHighFloor] & ONLY_FLR) >= cF_TOPFLR){
        sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] & ~UP_READY);
    }	
}



void  __attribute__((section(".usercode"))) UpDnCallClear(void)
{
	if((sRamDArry[mHighFloor] & ONLY_FLR) <= sRamDArry[mcurfloor]){
		sRamDArry[mHighFloor]=0x0;	
	}						
	else if((sRamDArry[mHighFloor] & ONLY_FLR) > sRamDArry[mcurfloor]){
		if(bDnWard)	sRamDArry[mHighFloor]=0x0;	
	}	
					
	if((sRamDArry[mLowFloor] & ONLY_FLR) >= sRamDArry[mcurfloor]){
		sRamDArry[mLowFloor] = 0x0;	
	}				
	else if((sRamDArry[mLowFloor] & ONLY_FLR) < sRamDArry[mcurfloor]){
		if(bUpWard)	sRamDArry[mLowFloor]=0x0;	
	}

									
	if(!(sRamDArry[mEqualFloor] & UPDN_CAR_READY)){
		sRamDArry[mEqualFloor]=0x0;	
	}

    
	if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
		sRamDArry[mLowFloor]=0x0;	
	}

	if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
		sRamDArry[mHighFloor]=0x0;	
	}

    if((sRamDArry[mHighFloor] & ONLY_FLR) > cF_TOPFLR)	sRamDArry[mHighFloor]=0;
     
    if((sRamDArry[mHighFloor] & ONLY_FLR) >= cF_TOPFLR){
        sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] & ~UP_READY);
    }	
}




unsigned int  __attribute__((section(".usercode"))) CounterCheck(void)
{

    if(RUN_MODE != LG_INVERTER_ELEV){
        if((OUT_P1==0) && (OUT_P2==0)  && (OUT_P3 == 0)){
            CounterTime=0;
        }  

        if(bAuto && bMoveCar && (CounterTime > 10)){
   		    bMoveOk=0;
		    bMoveUpOk=0;
		    bMoveDnOk=0;
            bCarErr=1;
            return(0);           
        }
    }
    return(1);    
}



unsigned int  __attribute__((section(".usercode"))) LightNormal_B(void)
{
    OUT_LIT=0;
    if(S3_PARKING1 && (LightTime > cF_LIGHTTIME))   OUT_LIT=1;
    if(S2_FIRE1 && bOnLuLd && bSubWayLight)         OUT_LIT=1;
    if(S1_POWER_FAIL && bDoorOpenEnd)               OUT_LIT=1;
    if(bWaterSen && bDoorOpenEnd)   	            OUT_LIT=1;
    if((AutoNoMoveTime>60))                         OUT_LIT=1;


	if(bsEmergency || bsLope){ 
   		O_U_W_bit=0;
     	O_OP_bit=0;
     	O_Y_0_bit=0;	

        bCarErr=1;        

        if(RUN_MODE == LG_INVERTER_ELEV)    OUT_P4N=0;
        else                                OUT_P4N=1;

		ClrUpDnWard();
				
		OUT_FAN=1;

		if(bsSlip)           OUT_GBR = 1;
        if(bAuto && bsLope)  OUT_GBR = 1;
		
        OUT_LIT=0;
	}
}


unsigned int  __attribute__((section(".usercode"))) LightNormal_A(void)
{
    OUT_LIT=1;
    if(S3_PARKING1 && (LightTime > cF_LIGHTTIME))   OUT_LIT=0;
//    if(S2_FIRE1 && bOnLuLd && bSubWayLight)         OUT_LIT=0;
    if(S1_POWER_FAIL && bDoorOpenEnd)               OUT_LIT=0;
    if(bWaterSen && bDoorOpenEnd)   	            OUT_LIT=0;
    if((AutoNoMoveTime>60))                         OUT_LIT=0;


	if(bsEmergency || bsLope){ 
   		O_U_W_bit=0;
     	O_OP_bit=0;
     	O_Y_0_bit=0;
	
        bCarErr=1;        

        if(RUN_MODE == LG_INVERTER_ELEV)    OUT_P4N=0;
        else                                OUT_P4N=1;

		ClrUpDnWard();
				
		OUT_FAN=1;

		if(bsSlip)           OUT_GBR = 1;
        if(bAuto && bsLope)  OUT_GBR = 1;
		
        OUT_LIT=1;
	}
}




void  __attribute__((section(".usercode"))) EmgDlsUlsCheck(void)   
{
    bExtButClr=0;     
	bCarButClr=0;   

	if(IN_EMG || (!bAuto && IN_GR)){
		bExtButClr=1;
		bCarButClr=1;
		bMoveOk=0;
		bMoveUpOk=0;
		bMoveDnOk=0;
		S1_EMG1=1; 
		bsEmergency=1;
		bCarErr=1;  				         		
	}
	else{
		bMoveOk=1;
		bMoveUpOk=1;
		bMoveDnOk=1;
		bsEmergency=0;
        S1_EMG1=0; 
	}         


	if(IN_ULS){
		bMoveUpOk=0;                                    
		if(OUT_U_W){
			bCarErr=1;  
		}
            
		if(bUpWard && bDoorCloseOk){
			bsUls=1;
		}                        
	}
	else{
		bsUls=0;          
	}
            
	if(IN_DLS){
		bMoveDnOk=0;
		if(OUT_D_W){
			bCarErr=1;   
		}
		if(bDnWard && bDoorCloseOk){                          
			bsDls=1;    
		}     
	}                        
	else  bsDls=0;
    
	if(bAuto){
		if(IN_GR){		
			bExtButClr=1;
			bCarButClr=1;
			bsLope=1;         
			bMoveOk=0;
			bMoveUpOk=0;
			bMoveDnOk=0;
			bCarErr=1;  
	      	OUT_GBR=1;
		}
		else{
			bsLope=0;
			if(!bsSlip){         	
				OUT_GBR=0;      
			}  
		}         
	}


	if(!bMoveUpOk && OUT_U_W){
		bCarErr=1;  
	}     
   
	if( !bMoveDnOk && OUT_D_W){
         bCarErr=1;   
   	}           
}




/*
void    SDSSUSChk(void)
{
    if(!IN_SD1 && bAuto && (CurPulse >= UP_DEC_COUNT(UP_FLR_0102_PULSE)) ){
   		bMoveOk=0;
		bMoveUpOk=0;
		bMoveDnOk=0;
        bCarErr=1;   
    }    

    if(!IN_SU1 && bAuto && ((CurPulse + 1000) <= UP_DEC_COUNT(cF_TOPFLR-1))  ){
   		bMoveOk=0;
		bMoveUpOk=0;
		bMoveDnOk=0;
        bCarErr=1;   
    }
}         
*/



void __attribute__((section(".usercode")))  DoorCloseOkCheck(void)
{   	
	DoorCloseEndCheck((UserDataType)bMoveCar);
	
   	if(!bDoorCloseOk){
      	bMoveOk=0;
      	bMoveUpOk=0;
      	bMoveDnOk=0;            
      	if(bMoveCar){
            bCarErr=1;   
      	}  
       
        if(!bOnLuLd && bAuto){
            bDoorOpen=1;
            OUT_ERR=1;
    		S1_EMG1=1;
        } 
        else{
            OUT_ERR=0;
            bDoorOpen=0;
            if(!bsEmergency)    S1_EMG1=0;
        }  
   	}
    else{
        bDoorOpen=0;
        OUT_ERR=0;
//		S1_EMG1=0;
    }
}


void  __attribute__((section(".usercode")))   EmgVoice(void)
{
	if(bsEmergency || OUT_ERR ){
		S1_EMG1=1;
    }
    else{
		S1_EMG1=0;
    }
}



void __attribute__((section(".usercode")))  LuLdOnCheck(void)
{         
   if(!IN_LU && !IN_LD){
      bOnLuLd=1;                                                                                     
   }      
   else{
      bOnLuLd=0;
   }         
}       


void __attribute__((section(".usercode")))  OverLoadCheck(void)
{
    if(IN_OLR && !bMoveCar && bOnLuLd && !bDoorCloseOk && bAuto){      
        S1_OVERLOAD1=1;

        if(IN_FIRE && IN_FR1){         
            bMoveOk=0;
            bMoveUpOk=0;
            bMoveDnOk=0;      
            sRamDArry[mDoorSeq]=DOOR_OPEN_START;      
            DoorOpenTime=0;                 
//            bCarStop=1;
            if(sRamDArry[mSysStatus] >= sOVL)   sRamDArry[mSysStatus]=sOVL;            
        }
    }
    else{
        S1_OVERLOAD1=0;         
    }
}



void  __attribute__((section(".usercode"))) ParkingCheck(void)
{      
	if(S3_PARKING1 && IN_PRK && !S2_FIRE1){
		if(sRamDArry[mSysStatus] >= sPARKING)   sRamDArry[mSysStatus]=sPARKING;             
		if(LightTime> cF_LIGHTTIME){
			LightTime=cF_LIGHTTIME+1;
		}
    	bMoveOk=0;
    	bMoveUpOk=0;
    	bMoveDnOk=0;      
    	bExtButClr=1;
    	bCarButClr=1;
    	bCarStop=1;
    	bTestKey=0;
   		sRamDArry[mEqualFloor] = 0;
   		sRamDArry[mHighFloor] = 0;
   		sRamDArry[mLowFloor] = 0;
    		                        
    		if(!OpenKeyCheck()){
	    		LightTime=0;
        		sRamDArry[mDoorSeq] = DOOR_OPEN_START;      		         
                S3_PARKING1=0;
    		}
  	}
  	else if(IN_PRK && bAuto && !S2_FIRE1){
    		if(sRamDArry[mcurfloor]== cF_PRKFLR){
        		if((sRamDArry[mDoorSeq] >= DOOR_CLOSE_END) && bDoorCloseOk && (sRamDArry[mDoorSeq] <= READY_ELEVATOR)){
                    S3_PARKING1=1;   
		    		OpenKeyCheck();
		    		LightTime=0;
        		}                     
    		}
    		else if(!ReadyAndNoKeyCheck()){
    			Virtual_Floor_Set(cF_PRKFLR);
		}                      
  	}
  	else{
    		if(S3_PARKING1){
        		sRamDArry[mDoorSeq] = DOOR_OPEN_START;      		             
    		}    		
    		S3_PARKING1=0;
    		LightTime=0;    		
  	}
}




void __attribute__((section(".usercode")))  VipCheck(void)
{
   if(!IN_PASS && bAuto){
      bExtButClr=1;
      S3_VIP1=1;
      if(sRamDArry[mSysStatus] >= sVIP)   sRamDArry[mSysStatus]=sVIP;      
   }
   else{   
     S3_VIP1=0;
   }
}

void __attribute__((section(".usercode")))  FullCheck(void)
{
    if(!IN_FULL && bAuto){
        S3_FULL1=1;        
    }
    else{   
        S3_FULL1=0;        
    }
}



void __attribute__((section(".usercode")))  InputCheck(void)
{
    EmgDlsUlsCheck();   
    DoorCloseOkCheck();
    OverLoadCheck();
    ParkingCheck();
    VipCheck();
    FullCheck();

    LuLdOnCheck();      

//   MainLoopTime=0;      
}



void __attribute__((section(".usercode")))  ButtonClrCheck(void)
{
    S2_EXT_BUT_CLR1=0;
    S2_CAR_BUT_CLR1=0;


    if(S1_POWER_FAIL){
        ClrUpDnWard();
       	bExtButClr=1;
        bCarButClr=1;   
    }

//   	if(bExtButClr){   
//        S2_EXT_BUT_CLR1=1; 
//   	}

   	if(bCarButClr){
		CarKeyClr();   
        S2_CAR_BUT_CLR1=1;
   	}

   	if(bCarUpDnChButClr){    // && (sRamDArry[mDoorSeq] == STOP_ELEVATOR)){
		CarKeyClr();   
        S2_CAR_BUT_CLR1=1;
   	}
   	
   	if(bExtButClr && bCarButClr){   
		KeyClr();   
   	}
}   




void __attribute__((section(".usercode")))  AutoManualCheck(void)
{
    if(IN_AUTO || (WarmingUpTime<100) || (sRamDArry[LD_INSP] == 0x55) ){
        S1_AUTO1=0;
        bExtButClr=1;
        bAuto=0;
    }      
    else{
        S1_AUTO1=1;
        bAuto=1;
    }


    if((cF_FhmOnOff) && (RUN_MODE == IO_INVERTER)){
        S1_AUTO1=0;
        bExtButClr=1;
        bAuto=0;
    }      
}

 

unsigned int    __attribute__((section(".usercode"))) Speed210Check(void)
{
    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_210);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed180Check(void)
{
    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_180);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed150Check(void)
{
    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_150);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed120Check(void)
{

    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_120);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed105Check(void)
{

    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_105);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}



unsigned int    __attribute__((section(".usercode"))) Speed90Check(void)
{

    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_90);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed60Check(void)
{
    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_60);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}



unsigned int    __attribute__((section(".usercode"))) Speed45Check(void)
{

    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_45);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}

unsigned int    __attribute__((section(".usercode"))) Speed30Check(void)
{
    unsigned long MinPulse;

    MinPulse=GET_LONG(MIN_DEC_PULSE_30);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}








unsigned int  __attribute__((section(".usercode")))   SpeedChange(void)
{
/*
    unsigned long tmppulse1,tmppulse2;
    unsigned long l1,l2;
    LocalType     ret,j,k,i1;
*/

    LocalType     ret;
    ret=1;

/*
    j=(sRamDArry[mHighFloor] & ONLY_FLR);
    k=(sRamDArry[mLowFloor] & ONLY_FLR);

    i1=CurSpeed;
    l1=DecreasePulse;
    l2=StopMinimumPulse;
*/

    switch(cF_ELEV_SPEED){
/*
        case    SPEED_30:
            ret=1;
            break;     
        case    SPEED_45:
            ret=1;
            break;     
        case    SPEED_60:
            ret=1;
            break;     
*/
        case    SPEED_90:
            if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            break;     
        case    SPEED_105:
            if(!Speed105Check() && (CurSpeed < SPEED_105)){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            break;     
        case    SPEED_120:
            if(!Speed120Check() && (CurSpeed < SPEED_120)){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check() && (CurSpeed < SPEED_105)){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            break;     
        case    SPEED_150:
            if(!Speed150Check() && (CurSpeed < SPEED_150)){
                CurSpeed=SPEED_150;
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                ret=0;
            }
            else if(!Speed120Check() && (CurSpeed < SPEED_120)){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check() && (CurSpeed < SPEED_105)){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            break;     
        case    SPEED_180:
            if(!Speed180Check() && (CurSpeed < SPEED_180)){
                CurSpeed=SPEED_180;
                DecreasePulse=GET_LONG(DEC_PULSE_180);
                ret=0;
            }
            else if(!Speed150Check() && (CurSpeed < SPEED_150)){
                CurSpeed=SPEED_150;
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                ret=0;
            }
            else if(!Speed120Check() && (CurSpeed < SPEED_120)){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check() && (CurSpeed < SPEED_105)){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            break;     
        case    SPEED_210:
            if(!Speed210Check() && (CurSpeed < SPEED_210)){
                CurSpeed=SPEED_210;
                DecreasePulse=GET_LONG(DEC_PULSE_210);
                ret=0;
            }
            else if(!Speed180Check() && (CurSpeed < SPEED_180)){
                CurSpeed=SPEED_180;
                DecreasePulse=GET_LONG(DEC_PULSE_180);
                ret=0;
            }
            else if(!Speed150Check() && (CurSpeed < SPEED_150)){
                CurSpeed=SPEED_150;
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                ret=0;
            }
            else if(!Speed120Check() && (CurSpeed < SPEED_120)){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check() && (CurSpeed < SPEED_105)){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            break;     
        default:
            break;
    }        


    if(ret==0){
        if(bUpWard) StopMinimumPulse=DecreasePulse+CurPulse;
        else        StopMinimumPulse=CurPulse-DecreasePulse;
    }

    return(ret);
}




unsigned int  __attribute__((section(".usercode")))   SpeedSet(void)
{

    unsigned long tmppulse1,tmppulse2;
    LocalType     j,want_updn,ret;

    if(RUN_MODE == LG_INVERTER_ELEV)    return(0);


    ret=1;
    want_updn=0;

    j=(sRamDArry[mAckStopFloor] & ONLY_FLR);
    
    TotalPulse=1;

    StartPulse=CurPulse;    

    tmppulse1=FLOOR_COUNT(j);
    tmppulse2=FLOOR_COUNT(sRamDArry[mcurfloor]);

    if(j>sRamDArry[mcurfloor]){
        TotalPulse=(tmppulse1-tmppulse2);   
        want_updn=1;            //up want
    }
    else if(j<sRamDArry[mcurfloor]){
        TotalPulse=(tmppulse2-tmppulse1);   
        want_updn=2;            //dn want
    }
    else    return(ret);    

    
    switch(cF_ELEV_SPEED){
        case    SPEED_30:
            if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
            break;     
        case    SPEED_45:
            if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
/*
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_60:
            if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_90:
            if(!Speed90Check()){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_105:
            if(!Speed105Check()){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check()){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_120:
            if(!Speed120Check()){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check()){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check()){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_150:
            if(!Speed150Check()){
                CurSpeed=SPEED_150;
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                ret=0;
            }
            else if(!Speed120Check()){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check()){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check()){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_180:
            if(!Speed180Check()){
                CurSpeed=SPEED_180;
                DecreasePulse=GET_LONG(DEC_PULSE_180);
                ret=0;
            }
            else if(!Speed150Check()){
                CurSpeed=SPEED_150;
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                ret=0;
            }
            else if(!Speed120Check()){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check()){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check()){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        case    SPEED_210:
            if(!Speed210Check()){
                CurSpeed=SPEED_210;
                DecreasePulse=GET_LONG(DEC_PULSE_210);
                ret=0;
            }
            else if(!Speed180Check()){
                CurSpeed=SPEED_180;
                DecreasePulse=GET_LONG(DEC_PULSE_180);
                ret=0;
            }
            else if(!Speed150Check()){
                CurSpeed=SPEED_150;
                DecreasePulse=GET_LONG(DEC_PULSE_150);
                ret=0;
            }
            else if(!Speed120Check()){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed105Check()){
                CurSpeed=SPEED_105;
                DecreasePulse=GET_LONG(DEC_PULSE_105);
                ret=0;
            }
            else if(!Speed90Check()){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check()){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
/*
            else if(!Speed45Check()){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            else if(!Speed30Check()){
                CurSpeed=SPEED_30;
                DecreasePulse=GET_LONG(DEC_PULSE_30);
                ret=0;
            }
*/
            break;     
        default:
            break;
    }        

    if(ret==0){
        if(want_updn==1){           //up want
            StopMinimumPulse=DecreasePulse + CurPulse;
            
            j=cF_TOPFLR;
            tmppulse1=FLOOR_COUNT(j);    
            if(StopMinimumPulse > (tmppulse1 - DecreasePulse)){
                ret=1;      //false
            }       
        }
        else if(want_updn==2){           //dn want
            StopMinimumPulse=CurPulse-DecreasePulse;

            tmppulse1=FLOOR_COUNT(0);    
            if(StopMinimumPulse < (tmppulse1 + DecreasePulse)){
                ret=1;      //false
            }       
        }
        else    ret=1;
    }

    return(ret);
}

      
void __attribute__((section(".usercode")))  AutoUpDownStart(void)
{   
	if(sRamDArry[mAckStopFloor]){  
         if((sRamDArry[mAckStopFloor] & 0x1f) > sRamDArry[mcurfloor]){
               CarUpStartCmd(); 
               bsDestFloor=0;    
         }                         
         else if((sRamDArry[mAckStopFloor] & 0x1f) < sRamDArry[mcurfloor]){
               CarDnStartCmd();
               bsDestFloor=0;                     
         }       
	}
}






void	__attribute__((section(".usercode"))) FixFloorStartCheck(void)
{
	if((cF_FIXFLOORTIME > 0) && (cF_FIXFLOOR < 32) 
		&& (cF_FIXFLOOR <= cF_TOPFLR) && !S3_PARKING1){		
		if((cF_FIXFLOOR != sRamDArry[mcurfloor]) && (FixFlrTimeCnt >= cF_FIXFLOORTIME)){				
			Virtual_Floor_Set(cF_FIXFLOOR);
		}              
	}
	else{
		FixFlrTimeCnt=0;
	}
}


void __attribute__((section(".usercode")))  AutoUpDnDirectionSet(void)
{	
   	if(bUpWard){
      	if(sRamDArry[mAckStopFloor] & UP_READY){
         		UpWard();      	
      	} 
		else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
         		UpWard();
      	}
      	else if(sRamDArry[mEqualFloor] & UP_READY){
         		UpWard();
      	}       				          	
   	}
   	else if(bDnWard){
		if(sRamDArry[mAckStopFloor] & DN_READY){
         		DnWard();		
		}
      	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
         		DnWard();
      	}      
      	else if(sRamDArry[mEqualFloor] & DN_READY){
         		DnWard();
      	}
		          	
   	}
   	else{
		if(sRamDArry[mEqualFloor] & UP_READY){
			UpWard();
      	} 
      	else if(sRamDArry[mEqualFloor] & DN_READY){
			DnWard();
      	}      
		else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
			UpWard();
     	} 
     	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
  			DnWard();
     	}   	
   	}   	
}



void  __attribute__((section(".usercode"))) 	UpDnRstCheck(void)
{
	if(bUpWard){
		if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
          	    ClrUpDnWard();
              	sRamDArry[mHighFloor]=0;
              	sRamDArry[mNewAckStopFloor] = 0x0;
         	}
	}         				
   	else if(bDnWard){
       	if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
            	ClrUpDnWard();
            	sRamDArry[mNewAckStopFloor] = 0x0;
            	sRamDArry[mLowFloor]=0;
       	}         
	}
}



void  __attribute__((section(".usercode"))) AutoDoorSystem(void)
{   
	if(IN_SFT || 	(!OpenKeyCheck())){
    		S3_PARKING1=0;
          
    		LightTime=0;
    		    		
     	if(sRamDArry[mDoorSeq] >= DOOR_REOPEN_CHECK){         
           	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
               DoorOpenTime=0;
            	bReOpen=1;
            	if(IN_SFT){
                  	if(sRamDArry[mSysStatus] > sSFT)   sRamDArry[mSysStatus]=sSFT;      
            	} 

			if(!bUpWard && !bDnWard){                                 		   	
				if(sRamDArry[mEqualFloor] & UP_READY)		bReOpen=0;
	      		else if(sRamDArry[mEqualFloor] & DN_READY)	bReOpen=0;
			}      
      		else if((bUpWard) && (sRamDArry[mEqualFloor] & UP_READY))	bReOpen=0;
      		else if((bDnWard) && (sRamDArry[mEqualFloor] & DN_READY))	bReOpen=0;
      	}  
	}         
	else if(!CloseKeyCheck()){
         if(bOpenEnd || (sRamDArry[mDoorSeq] >= DOOR_OPEN_WAIT)){
//         	if(!bDoorJumper && !bPowerFail){
         	if(!bDoorJumper && !S1_POWER_FAIL){
	         	sRamDArry[mDoorSeq]=DOOR_CLOSE_START;
     	        DoorCloseTime=0;      
			}     	          
         }            
	}
  
	AutoUpDnDirectionSet();
	

    if(sRamDArry[mDoorSeq] == READY_ELEVATOR){          
        if(bUpWard){
            if((sRamDArry[mHighFloor] & UPDN_CAR_READY)){
                sRamDArry[mNewAckStopFloor] = sRamDArry[mHighFloor];
            }                          
            else{
                ClrUpDnWard();                
                sRamDArry[mEqualFloor]=0;
                sRamDArry[mHighFloor]=0;
                sRamDArry[mNewAckStopFloor] = 0x0;
            }
        }
        else if(bDnWard){
            if((sRamDArry[mLowFloor] & UPDN_CAR_READY)){
                sRamDArry[mNewAckStopFloor] = sRamDArry[mLowFloor];
            }  
            else{
                ClrUpDnWard();
                sRamDArry[mNewAckStopFloor] = 0x0;
                sRamDArry[mEqualFloor]=0;
                sRamDArry[mLowFloor]=0;
            }         
        }
    }


/*
   	if(bAuto && ((IN_FIRE || IN_X7 || IN_FIRE1 || IN_FIRE2 || IN_FIRE3 || IN_FIRE4))  ){
        S2_FIRE1=1;             
    }
    else{
        S2_FIRE1=0;             
    }
*/
}   




/*
//20051008delete
void __attribute__((section(".usercode"))) IO_INVERTER_NewFloorLoadCheck(void)
{
    unsigned long longtemp1;
    LocalType     save_CurSpeed;


    LocalType     i,j,k;

	i=0;
	
    TotalPulse=0;

    j=(sRamDArry[mHighFloor] & ONLY_FLR);
    k=(sRamDArry[mLowFloor] & ONLY_FLR);

    if(j <= cF_TOPFLR){   
       	if(bUpWard && (sRamDArry[mHighFloor] & UPDN_CAR_READY)){    
            j=(sRamDArry[mHighFloor] & ONLY_FLR);
            longtemp1=FLOOR_COUNT(j);
            if(longtemp1 > CurPulse){
                TotalPulse=(longtemp1-CurPulse);   
                if(TotalPulse>DecreasePulse) i=1;
            }
        }
       	else if(bDnWard && (sRamDArry[mLowFloor] & UPDN_CAR_READY)){
    		k=(sRamDArry[mLowFloor] & ONLY_FLR);
            longtemp1=FLOOR_COUNT(k);
            if(longtemp1 < CurPulse){
                TotalPulse=(CurPulse-longtemp1);   
                if(TotalPulse>DecreasePulse) i=1;
            }
        }
    }

///????????????????????????????
///?????????????????????????????
//??????????????????????????????

    if((i==1) && !IN_UND){
        save_CurSpeed=CurSpeed;

        SpeedChange();        

        if(CurSpeed>save_CurSpeed){        
            RunSpeedCmd_IO();
        }
            
       	if(bUpWard){
             sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mHighFloor];            																							
        }
        else if(bDnWard){
             sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mLowFloor];																							
        }
 
        sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
        sRamDArry[mMostLongDst] = 0;        
    }


    j=(sRamDArry[mHighFloor] & UPDN_CAR_READY);
    k=(sRamDArry[mLowFloor] & UPDN_CAR_READY);


   	if( ((j==0) && bUpWard) || ((k==0) && bDnWard) || !(sRamDArry[mAckStopFloor] & UPDN_CAR_READY) ){
    	if(sRamDArry[mReqStopFloor] & CAR_READY){
            sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];
            if(bUpWard){ 
                sRamDArry[mHighFloor]=sRamDArry[mAckStopFloor];    
            }
            else if(bDnWard){           
                sRamDArry[mLowFloor]=sRamDArry[mAckStopFloor];    
            }
    	}         			
    }    
}            		
//20051008delete
*/


//20051008insert
void	NoButtonAndDefaultLoad(void)
{
	if(sRamDArry[mReqStopFloor] & CAR_READY){
		sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];
/*
		if(bUpWard){ 
		    sRamDArry[mHighFloor]=sRamDArry[mAckStopFloor];    
		}
		else if(bDnWard){           
		    sRamDArry[mLowFloor]=sRamDArry[mAckStopFloor];    
		}
*/
	}         			
}


void __attribute__((section(".usercode"))) IO_INVERTER_NewFloorLoadCheck(void)
{
    unsigned long longtemp1;
    LocalType     save_CurSpeed;


    LocalType     i,j,k,l;

	i=0;
	l=0;	
    TotalPulse=0;

    j=(sRamDArry[mHighFloor] & ONLY_FLR);
    k=(sRamDArry[mLowFloor] & ONLY_FLR);

    if(bUpWard && (j==0)){    		
		NoButtonAndDefaultLoad();
	}
    else if(bDnWard && (k==0)){    
		NoButtonAndDefaultLoad();
	}
   	else if(!(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
		NoButtonAndDefaultLoad();	
	}
	else{   
       	if(bUpWard && (sRamDArry[mHighFloor] & UPDN_CAR_READY) && (j <= cF_TOPFLR)){    
            j=(sRamDArry[mHighFloor] & ONLY_FLR);
            longtemp1=FLOOR_COUNT(j);
            if((longtemp1 > CurPulse) && (CurPulse > StopMinimumPulse)){
                TotalPulse=(longtemp1-CurPulse);   
                if(TotalPulse>DecreasePulse) i=1;
            }
        }
       	else if(bDnWard && (sRamDArry[mLowFloor] & UPDN_CAR_READY)){
    		k=(sRamDArry[mLowFloor] & ONLY_FLR);
            longtemp1=FLOOR_COUNT(k);
            if((longtemp1 < CurPulse) && (CurPulse < StopMinimumPulse)){
                TotalPulse=(CurPulse-longtemp1);   
                if(TotalPulse>DecreasePulse) i=1;
            }
        }


	    if(i==1){
	        save_CurSpeed=CurSpeed;
	
	        SpeedChange();        
	
	        if(CurSpeed>save_CurSpeed){        
	            RunSpeedCmd_IO();
	        }
	            
	       	if(bUpWard){
	            sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mHighFloor];            																							
				OriginalHighFlr     =sRamDArry[mHighFloor];
	        }
	        else if(bDnWard){
	            sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mLowFloor];																							
        		OriginalLowFlr      =sRamDArry[mLowFloor];
	        }	 
	        sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
	        sRamDArry[mMostLongDst] = 0;        
	    }
		else{
	        sRamDArry[mHighFloor]=OriginalHighFlr;
	        sRamDArry[mLowFloor]=OriginalLowFlr;
		}
    }
}            		
//20051008insert



void __attribute__((section(".usercode"))) LG_INVERTER_NewFloorLoadCheck(void)
{
    LocalType     j,k;

    j=(sRamDArry[mHighFloor] & UPDN_CAR_READY);
    k=(sRamDArry[mLowFloor] & UPDN_CAR_READY);

//20051008insert    
    if(bUpWard && (j==0)){    		
		NoButtonAndDefaultLoad();
	}
    else if(bDnWard && (k==0)){    
		NoButtonAndDefaultLoad();
	}
   	else if(!(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
		NoButtonAndDefaultLoad();	
	}
//20051008insert    

	else{
	  	if(bUpWard){
	        sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mHighFloor];            																							
	    }
	    else if(bDnWard){
	        sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mLowFloor];																							
	    }
	
	    sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
	    sRamDArry[mMostLongDst] = 0;        
	}

/*    
    OriginalHighFlr =sRamDArry[mHighFloor];
    OriginalLowFlr  =sRamDArry[mLowFloor];
*/
/*
//20051008delete    

    j=(sRamDArry[mHighFloor] & UPDN_CAR_READY);
    k=(sRamDArry[mLowFloor] & UPDN_CAR_READY);

   	if( ((j==0) && bUpWard) || ((k==0) && bDnWard) || !(sRamDArry[mAckStopFloor] & UPDN_CAR_READY) ){
    	if(sRamDArry[mReqStopFloor] & CAR_READY){
            sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];
            if(bUpWard){ 
                sRamDArry[mHighFloor]=sRamDArry[mAckStopFloor];    
            }
            else if(bDnWard){           
                sRamDArry[mLowFloor]=sRamDArry[mAckStopFloor];    
            }
    	}         			
    }
//20051008delete    

*/    
}            		


unsigned int  __attribute__((section(".usercode"))) NewUpKeyChk(void)
{
    if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY) && !(sRamDArry[mDoor] & UPDN_CAR_READY)){
        return(0);
    } 
    else if((sRamDArry[mHighFloor] & UPDN_CAR_READY) && (sRamDArry[mDoor] & UPDN_CAR_READY)){
        return(0);
    } 
    else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
        return(0);
    } 
    else    return(1);    
}

unsigned int  __attribute__((section(".usercode"))) NewDnKeyChk(void)
{
    if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY) && !(sRamDArry[mDoor] & UPDN_CAR_READY)){
        return(0);
    } 
    else if((sRamDArry[mLowFloor] & UPDN_CAR_READY) && (sRamDArry[mDoor] & UPDN_CAR_READY)){
        return(0);
    } 
    else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
        return(0);
    } 
    else    return(1);    
}


void  __attribute__((section(".usercode"))) NewFloorLoad(void)
{  	
	if(bUpWard){
		if(sRamDArry[DEST_FLR] != sRamDArry[mHighFloor]){
            if(!NewUpKeyChk()){
                if(RUN_MODE == LG_INVERTER_ELEV)    LG_INVERTER_NewFloorLoadCheck();
                else                                IO_INVERTER_NewFloorLoadCheck();

                sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
                sRamDArry[mMostLongDst] = 0;        
            }
		}
		if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
	}
	else if(bDnWard){        	
		if(sRamDArry[DEST_FLR] != sRamDArry[mLowFloor]){
            if(!NewDnKeyChk()){
                if(RUN_MODE == LG_INVERTER_ELEV)    LG_INVERTER_NewFloorLoadCheck();
                else                                IO_INVERTER_NewFloorLoadCheck();

                sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
                sRamDArry[mMostLongDst] = 0;        
            }
		}
		if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;                  
	}                        

	if(!(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
		if(sRamDArry[mReqStopFloor] & CAR_READY){	
			sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];		
		}			
	}
}






void __attribute__((section(".usercode")))  FhmRunCheck(void)
{

    if(!bAuto && CounterCheck()){
        if( ( (sRamDArry[FHM_RUN] == FHM_RUN_CMD) && (FhmLoaderTime < 10) ) || !IN_EX2){   //you
            bFhmRun=1;
            if(sRamDArry[FHM_SEQ]==0){
                sRamDArry[FHM_SEQ]=FHM_SEQ_0;
            }
        }
        else bFhmRun=0;
    }
    else  bFhmRun=0;     
}



void __attribute__((section(".usercode")))  ManualUpDnKeyCheck(void)
{
	LocalType KeyTime;
	unsigned int  x,y;
	unsigned long i,j;
 
  
	if(bAuto)      KeyTime=30;
	else           KeyTime=5;
      
	if(!IN_U_B){
		if(UpBttonTime >= KeyTime){
			UpBttonTime = KeyTime;                  
			bManualUpKey=1;
		}                
		DnBttonTime=0;     
	}         
	else if(!IN_D_B){                  
		if(DnBttonTime >= KeyTime){
			DnBttonTime=KeyTime;
			bManualDnKey=1;
		}                  
		UpBttonTime=0;
	}
	else{
		DnBttonTime=0;
		UpBttonTime=0;    
		bManualUpKey=0;
		bManualDnKey=0;        
	}
   

    FhmRunCheck();


	if(bFhmRun){
		if(sRamDArry[mSysStatus] >= sFHM_MODE)   sRamDArry[mSysStatus]=sFHM_MODE;        

		switch(sRamDArry[FHM_SEQ]){ 
			case  FHM_SEQ_0:
				if(!IN_LU && IN_LD && !IN_SD1){
					FhmTime=0;
                    sRamDArry[FHM_SEQ]=FHM_SEQ_3;
				}
				else if(bsDls){
                    sRamDArry[FHM_SEQ]=FHM_SEQ_1;
				}
				else{
                    sRamDArry[FHM_SEQ]=FHM_SEQ_2;
				}

                if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;                                             
            
				break;
			case  FHM_SEQ_1:
				if(!IN_LU && IN_LD && !IN_SD1){
               		FhmTime=0;                    
                    sRamDArry[FHM_SEQ]=FHM_SEQ_3;
				}
				else if(bsUls || (!IN_LU && !IN_LD)){
               		FhmTime=0;                    
                    sRamDArry[FHM_SEQ]=FHM_SEQ_2;
				}
				else{
					bManualUpKey=1;
				}
                if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;                                             
				break;
			case  FHM_SEQ_2:
				if(!IN_LU && IN_LD && !IN_SD1){
					FhmTime=0;
                    sRamDArry[FHM_SEQ]=FHM_SEQ_3;
				}
				else if(bsDls){
                    sRamDArry[FHM_SEQ]=FHM_SEQ_1;
				}
				else{
					bManualDnKey=1;
				}
                if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;                                             
				break;
			case  FHM_SEQ_3:
				if(!IN_LU && IN_LD && !IN_SD1){
					if(FhmTime>20){
                        sRamDArry[FHM_SEQ]=FHM_SEQ_4;

                        if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=1;

                        else if(RUN_MODE == IO_INVERTER){
                            for(FhmToggle=0;FhmToggle<32;FhmToggle++){
                                parameter_mirror[FhmToggle]= 0x0fffffff;
                            }
                            FhmToggle=0;
                            sRamDArry[mcurfloor]=0;                                                                   
                            POSCNT=0;
                            CurPulse=BASE_PULSE;        
                        }
					}                    
					else if(FhmTime>10){
                        if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=1;
					}                    
            	}  
				else{
                    sRamDArry[FHM_SEQ]=FHM_SEQ_0;
				}        
				break;   
			case  FHM_SEQ_4:
                if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=1;

				if(IN_LU && !IN_LD && !IN_SU1){
                    if(RUN_MODE == IO_INVERTER){
                        TmpFhmCounter2 = CurPulse;                                  

                        i=TmpFhmCounter2;
                        j=TmpFhmCounter1;

                        i=(unsigned long)(j+i);
                        i=(i>>1);
                        TmpFhmCounter1=(unsigned long)(i);

                        i=TmpFhmCounter1;
                        j=10;
                        i=i-j;            
                        parameter_mirror[sRamDArry[mcurfloor]] =i; 
            
		    			FhmTime=0;

                        SaveFloorCnt();


            	        x=(F_TopFlr/4);
                        
                        for(y=0;y<16;y++){
                            parameter_mirror[y]=FlashDspCharBuf[x+y].long_data;
                        }
                        
                        b_LdTmpBufRam(F_TopFlr)    = sRamDArry[mcurfloor]; // top floor
                        b_LdTmpBufRam(F_FhmOnOff)  = 0;                    //FHM On Off== FHM On

                        flash_write_DspChar(F_TopFlr);

                    }
                    sRamDArry[FHM_SEQ]=FHM_SEQ_5;
                	OUT_P3=0;                                                         
                	OUT_P1=0;                                                         
                	OUT_P2=0;     
            	    OUT_U_W=0;                                                               
            	    OUT_D_W=0;                                                                     
				}
  
				else if(bsUls){
                    sRamDArry[FHM_SEQ]=FHM_SEQ_0;
				}               

				else{
					bManualUpKey=1;

                    if(RUN_MODE == IO_INVERTER){
                        if(!IN_LU && !IN_LD && !FhmToggle){
                            FhmToggle=1;
                            TmpFhmCounter1=CurPulse;
    
                            if(!IN_SD1){
                                sRamDArry[mcurfloor]=0;                                                                   
                            }
                            else{ 
                                sRamDArry[mcurfloor]++;                            
                            }                        
                        }
                    
                        if(IN_LU && !IN_LD && FhmToggle){

                            TmpFhmCounter2 = CurPulse;                                  

                            i=TmpFhmCounter2;
                            j=TmpFhmCounter1;
                            i=(unsigned long)(j+i);
                            i=(i>>1);
                            TmpFhmCounter1=(unsigned long)(i);

                            i=TmpFhmCounter1;
                            j=10;
                            i=i-j;            
                            parameter_mirror[sRamDArry[mcurfloor]] =i; 

                            FhmToggle=0;
                        }
                    }
				}        
                DspFloorSet();
				break;               
			case  FHM_SEQ_5:
				if(IN_LU && !IN_LD && !IN_SU1){
					if(FhmTime>10){
                        if(FhmToggle == 0){
                            FhmToggle=1;

//                            SaveFloorCnt();
//                            LadderBuf[C_SAVE_DATA]=sRamDArry[mcurfloor];   //top floor set
////////yousangyong           F_SetupData_ReSet(F_TopFlr,1);                 //top floor set

                            FhmTime=20; 
                            FhmTime=20; 
                            FhmTime=20; 
                        }                                                               
		    		    sRamDArry[FHM_RUN]=0;
					}                    
					else if(FhmTime>5){
                        if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;
                        FhmToggle=0; 
					}                    
				}  
				else{
                    sRamDArry[FHM_SEQ]=FHM_SEQ_0;
                    if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;
				}        
				break;
			default:
				sRamDArry[FHM_RUN]=0;
                sRamDArry[FHM_SEQ]=0;
                if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;                                             
				break;            
		}        
	}   
	else{
		sRamDArry[FHM_RUN]=0;
        sRamDArry[FHM_SEQ]=0;
        if(RUN_MODE == LG_INVERTER_ELEV) OUT_P4N=0;                                             
	}
   

	if(((sRamDArry[FHM_SEQ]  == FHM_SEQ_4) && (!bMoveUpOk)) || bAuto){
		sRamDArry[FHM_RUN]=0;
        sRamDArry[FHM_SEQ]=0;
	}	        

}



void __attribute__((section(".usercode")))  ManualUpDown(void)
{    
	if(bManualUpKey){
		if(!bDoorCloseOk){
			AllDoorCloseCmd();      
			if(sRamDArry[mSysStatus] > sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;      
		}  
                                 
		CarUpStartCmd();
    
		if(!bMoveUpOk){
			bCarStop=1;
		}      
	}          
   	else if(bManualDnKey){
		if(!bDoorCloseOk){
            AllDoorCloseCmd();                  
            if(sRamDArry[mSysStatus] > sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;      
        }           
        CarDnStartCmd();

        if(!bMoveDnOk){                  
            bCarStop=1;
        } 
    }
    else{
        bCarStop=1;
    }
}            



UserDataType __attribute__((section(".usercode"))) NoUseNoOpen(void)
{
    LocalType i,j,k;
  
    i=sRamDArry[mcurfloor]/8;
    j=sRamDArry[mcurfloor]%8;
    k=0x01;
    k = (k << j);
    if(sRamDArry[FLR_ON_OFF0+i] & k)  return(1);
    else                              return(0);   
}



void __attribute__((section(".usercode")))  DoorOpenCloseSeq(void)
{			  
    switch(sRamDArry[mDoorSeq]){
        case    DOOR_OPEN_START:
            CurPulse=FLOOR_COUNT(sRamDArry[mcurfloor]);
            POSCNT=0;

            sRamDArry[mEqualFloor] = 0x0;
            S3_UPDN_VO1=0;

            if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus]=sOPEN;
            bDoorJumper=0;
            DoorCloseTime=0;

//            if(NoUseNoOpen() || bPowerFail){               

            if(NoUseNoOpen() || S1_POWER_FAIL){               
                SelectDoorOpen();    
                if(DoorOpenTime >= 5){
                    sRamDArry[mDoorSeq] = DOOR_OPEN_CHECK;
                    DoorOpenTime=0;
                }                
            }
            else{               
                bsOpeNoOn=0;             
                bSlipCheckStart=1;
                DoorOpenTime=0;
                bReOpen=0;
//                bCarClrKey=0;

                bCarUpDnChButClr=0;
                DoorCloseTime=0;               	
                sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
            }                
            break;                                        
        case	DOOR_OPEN_CHECK:        
            if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus]=sOPEN;                        		         		         		
            bSlipCheckStart=1;

            if(bOpenEnd){ 
                bsOpeNoOn=0;             
                DoorOpenTime=0;
                if(bReOpen){
	                DoorOpenTime=(OPEN_AND_WAIT_TIME + cF_OPWTTM);
                }
                bReOpen=0;
                sRamDArry[mDoorSeq] = DOOR_OPEN_WAIT;
            }            		
            else if(DoorOpenTime > (OPEN_TOTAL_TIME + cF_OPTTTM)){
                sRamDArry[mDoorSeq] = DOOR_OPEN_WAIT;            
                bsOpeNoOn=1;             
                DoorOpenTime=(OPEN_AND_WAIT_TIME + cF_OPWTTM);
            }
  	         			
/*
            else if(DoorOpenTime > 30){
                if(bHoleDoorClose || bCloseEnd){	         		
                    sRamDArry[mDoorSeq] = DOOR_REOPEN_CHECK;
//                    bDoorJumper=1;                                        //insert
                }
            }    
*/
		          		         		        		                              		         		         		
            if(DoorOpenTime > 10){
//                bCarClrKey=0;
                bCarUpDnChButClr=0;
            }         		                              		         		         		
            break;                  		
		case	DOOR_OPEN_WAIT:    		      
//            bCarClrKey=0;
            bCarUpDnChButClr=0;

            bDoorOpenEnd=1;
            DoorCloseTime=0;               	
            if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus] = sOPEN;      

            if((bHoleDoorClose || bCloseEnd) && !(!IN_FR1 && !IN_FR2)){                                  		
                sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;
                if(cF_DoorJumperOff)   bDoorJumper=1;
            }
            else  if(!IN_X6){             
                sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;
            }
            else if((DoorOpenTime > (OPEN_AND_WAIT_TIME + cF_OPWTTM))){             
                sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;
            }                               
            break;            
        case	DOOR_REOPEN_CHECK:     
            if(bDoorJumper || S1_POWER_FAIL){
                sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;         						
                if(!bHoleDoorClose && !bCloseEnd){                         //insert	         		
                    bDoorJumper=0;
                }
            }
            else{         		
                if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus]=sOPEN;      
                DoorCloseTime=0;      
                if(S3_VIP1){
                    DoorOpenTime=(OPEN_AND_WAIT_TIME + cF_OPWTTM + REOPEN_CHK_TIME)-1;
                    UpDnRstCheck();            		
                }	
                if((DoorOpenTime > (OPEN_AND_WAIT_TIME + cF_OPWTTM + REOPEN_CHK_TIME)) || (!IN_X6)){             
		            sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                }                               
            }         			
            break;            
        case  DOOR_CLOSE_START:                
            bDoorOpenEnd=0;

            if((bUpWard && (sRamDArry[mHighFloor] & 0xe0)) ||
                (bDnWard && (sRamDArry[mLowFloor] & 0xe0)) ){
                    S3_UPDN_VO1=1;       
            }

            if(sRamDArry[mSysStatus] > sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;      
            SelectDoorClose();    	            		
            if(DoorCloseTime >= 1){         
                sRamDArry[mDoorSeq]=DOOR_CLOSE_CHECK;     
                DoorCloseTime=0;    
            }       
            break;

        case  DOOR_CLOSE_CHECK:                  
            if(sRamDArry[mSysStatus] > sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;                        
            if(bDoorCloseOk){
                sRamDArry[mDoorSeq]=DOOR_CLOSE_END;                                        
                DoorCloseTime=0;
                bsHdsNoOn=0;
                bsCleNoOn=0;
                UpDnRstCheck();            		
            }         		  
            else if(DoorCloseTime > (CLOSE_TOTAL_TIME + cF_OPTTTM)){
                sRamDArry[mDoorSeq]=DOOR_OPEN_START; 
                bReOpen=1;
            }
            break;               
        case  DOOR_CLOSE_END:  
            if(sRamDArry[mSysStatus] > sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;      
            if(bDoorCloseOk){
                if(DoorCloseTime > 5){   
                    sRamDArry[mDoorSeq]=READY_ELEVATOR;  
                }               
            }               
            else{
                sRamDArry[mDoorSeq]=DOOR_CLOSE_CHECK;
                DoorCloseTime=0;
            }            
            break;                
    }            
}





void __attribute__((section(".usercode")))  DoorOpClSystem(void)
{
     HighLowCallClear();

     if(sRamDArry[mDoorSeq] <= READY_ELEVATOR){
		UpDnCallClear();           
		AutoDoorSystem();   
     }
     
     
     if(sRamDArry[mDoorSeq] <= DOOR_REOPEN_CHECK){
   		if(!bOpenEnd){ 
            SelectDoorOpen();      
		}               
     }
                     
	switch(sRamDArry[mDoorSeq]){
		case  READY_ELEVATOR:		
			sRamDArry[mDoor] =( sRamDArry[mDoor] & ~UPDN_CAR_READY);
            sRamDArry[mMostLongDst] = 0;
            sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];
        
            S2_FLOW1=0;
			bsLuLdNoOff=0;  
			sRamDArry[mDoorSeq]=READY_ELEVATOR;
            bCarUpDnChButClr=0;
			
			if(!bDoorCloseOk){                     //door close error           
				sRamDArry[mDoorSeq]=DOOR_CLOSE_START;         
				DoorCloseTime=0;               
			}
			else{
				if((sRamDArry[mNewAckStopFloor] & 0xe0)){
					sRamDArry[mAckStopFloor] = sRamDArry[mNewAckStopFloor];
                    if(!SpeedSet()){
    					sRamDArry[DEST_FLR] = sRamDArry[mNewAckStopFloor];                    
//20051008insert    
        				OriginalHighFlr     =sRamDArry[mHighFloor];
        				OriginalLowFlr      =sRamDArry[mLowFloor];
//20051008insert
	    				sRamDArry[mNewAckStopFloor]=0; 
		    			sRamDArry[mCarMoveState]=0;
			    		NextFloorTime=0;            
				    	bSlipCheckStart=0;
                        S3_UPDN_VO1=1; 	
                        CarStopTime=0;
                        sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];

	    				sRamDArry[mDoorSeq]=MOVE_ELEVATOR;
 
                    }
                    else{
    					sRamDArry[mAckStopFloor] = sRamDArry[mNewAckStopFloor] = 0;
                        sRamDArry[mHighFloor]    = sRamDArry[mLowFloor]        = 0;                        
                    }
				}               
				if(sRamDArry[mSysStatus] >= sREADY)   sRamDArry[mSysStatus]=sREADY;                              
			}            
                  
			if(!bOnLuLd){
				bsLuLdHome=1;
				bCarErr=1;
			}
			else  bsLuLdHome=0;
			
			FixFloorStartCheck();

            break;                

		case  MOVE_ELEVATOR:  
			FixFlrTimeCnt=0;
			AutoUpDownStart();         
                    
			if(!bOnLuLd){
				sRamDArry[mDoorSeq]=WAIT_NEXT_LULD;         
			   	NextFloorTime=0;
			   	LuLdTime=0;
			}			   
			else  if(NextFloorTime>BASE_LULD_OFF_TIME){
				if(bOnLuLd)	    bCarErr=1;
				else			bCarStopNoRun=1;         
				bsLuLdNoOff=1;
			}               
            break;                         
         case  WAIT_NEXT_LULD:
                if(bUpWard) if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
                if(bDnWard) if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;      
    
    			if(((sRamDArry[mReqStopFloor] & ONLY_FLR) == (sRamDArry[mAckStopFloor] & ONLY_FLR))  && (sRamDArry[mReqStopFloor] & CAR_READY)){
                    OUT_DAC=1; 
                                    
            		if(IN_UND && (LuLdTime > iF_F_BrkStTm10)){				
    	       	        sRamDArry[mDoorSeq]=STOP_ELEVATOR;
         	  	      	sRamDArry[mCarMoveState]=0;    
    				} 
                    else if(!IN_UND){
        				NewFloorLoad();
    			        if((sRamDArry[mReqStopFloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR)){
                            OUT_DAC=0; 
                        }
                    }    						    	  	
    			}
    			else if(IN_UND){
                 	OUT_DAC=1;				
                    if(((sRamDArry[mAckStopFloor] & ONLY_FLR) != (sRamDArry[mReqStopFloor] & ONLY_FLR))
    				  || !(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
    				    sRamDArry[mAckStopFloor] = ((sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY);				
    				}
    			}			
            	else if(LuLdTime > iF_F_BrkStTm40){				
    				 sRamDArry[mAckStopFloor]= (sRamDArry[mReqStopFloor] | CAR_READY);
    	       	     sRamDArry[mDoorSeq]=STOP_ELEVATOR;
         	  	     sRamDArry[mCarMoveState]=0;    
    			} 				
                else{			            
                 	OUT_DAC=0;								
    				NewFloorLoad();                  
    			}	

        		if(IN_UND && (LuLdTime==0)){				
                    UpDnCallClear();  
                }                

               break;                         
         	case  STOP_ELEVATOR:  			            	

//			    if(VoiceTime > 5)	
//                S2_FLOW1=1;	
                 		                                             			
			    CarStopCmd();

                if(!bMoveCar){
                    bVoiceReady=0;   
                    OpenKeyCheck();
                   	OUT_DAC=0;

/*
    				if(bUpWard && !(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
    				    bCarUpDnChButClr=1;	
    			    }   		 
    			    else if(bDnWard && !(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
      					bCarUpDnChButClr=1;	
    			    }   			
*/
				
//				    sRamDArry[mReqStopFloor] = sRamDArry[mcurfloor];

				    DoorOpenTime = 0;

                    if(S2_FIRE1 && (sRamDArry[mcurfloor] != FireBaseFloor) && (sRamDArry[mFireSeq] == FIRE_START) ){
                        KeyClr();
                        ClrUpDnWard();       
                        sRamDArry[mAckStopFloor] = FireBaseFloor | CAR_READY;         
                        NextFloorTime=0;
                        DoorCloseTime=0;
    				    bCarUpDnChButClr=0;	
                        sRamDArry[mDoorSeq] = READY_ELEVATOR;
                    }
                    else if(S2_FIRE1 && (sRamDArry[mFireSeq] == FIRE_TWO) ){
                        KeyClr();
                        ClrUpDnWard();       
                        sRamDArry[mNewAckStopFloor]=0;
                        sRamDArry[mAckStopFloor] = 0;         
                        sRamDArry[mDoor]=0;
                        sRamDArry[mMostLongDst] = 0;        

                        sRamDArry[mEqualFloor] = 0x0;
                        NextFloorTime=0;
                        DoorCloseTime=0;
    				    bCarUpDnChButClr=0;	
                        sRamDArry[mDoorSeq] = READY_ELEVATOR;
                        sRamDArry[mFireSeq] = FIRE_THREE;
                    }
                    else    sRamDArry[mDoorSeq] = DOOR_OPEN_START;

                }               
                break;         
             default:
               if(!((sRamDArry[mDoorSeq] <= DOOR_CLOSE_END))){      
                  sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                    
               }            
               break;                

   }
}


void  __attribute__((section(".usercode"))) TestUpDn(void)
{
	ManualUpDnKeyCheck();
   	if(bManualUpKey){
		if(sRamDArry[mcurfloor] < cF_TOPFLR){
			if(sRamDArry[mHighFloor] == 0x0){
				sRamDArry[mHighFloor] = (cF_TOPFLR | CAR_READY);
     	    	bTestKey=1;
			}     	    		
		}         		
   	}              
     else if(bManualDnKey){
		if(sRamDArry[mcurfloor] > 0){
			if(sRamDArry[mLowFloor] == 0x0){
				sRamDArry[mLowFloor] = CAR_READY;
     	    	bTestKey=1;
			}     	    		
		}         		
   	}        
   	else{
//20051008insert    
   		if(bTestKey){   		
//			if(sRamDArry[mReqStopFloor] & CAR_READY){
         		sRamDArry[mLowFloor]  = 0x0;
         		sRamDArry[mHighFloor] = 0x0;
				sRamDArry[mEqualFloor]= 0x0;					
//				sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];					
         		bTestKey=0;		
//			}         			
		}
//20051008insert    
   	}     
}



void  __attribute__((section(".usercode"))) FindLuLdManual(void)
{
    if(LuLdTime>iF_F_BrkStTm10){
        if(((sRamDArry[mcurfloor] == 0) && IN_SD1) || ((sRamDArry[mcurfloor] == cF_TOPFLR) && IN_SU1)){
            LuLdTime=0;
            bHomeUpDn=0;
        }
        else{
            if(bSearchHome){
                sRamDArry[mCarMoveState]=0;
                bSearchHome=0;
            }
            CarStopCmd();
         	bManualUpKey=0;
            bManualDnKey=0;                  
    
            if(LuLdTime>(iF_F_BrkStTm40 + iF_F_BrkStTm10)){
                sRamDArry[mDoorSeq] = DOOR_OPEN_START;      
                bManualAuto=1;
            }
        }
    }
    else{
        bAuto=0;
        
        bSearchHome=1;
        
        if(sRamDArry[mSysStatus] > sHOME)   sRamDArry[mSysStatus]=sHOME;      
        
        if(!bHomeUpDn){
            bManualUpKey=0;
            bManualDnKey=1;
            ManualUpDown();                     
        }  
        else{
            bManualDnKey=0;
            bManualUpKey=1;
            ManualUpDown();               
        }                  
        NextFloorTime=0;
        bAuto=1;
    }
}      


void  __attribute__((section(".usercode"))) SlipCheck(void)
{
	if( bSlipCheckStart && !bOnLuLd && !bMoveCar && (!bHoleDoorClose || !bCloseEnd)){ 	         		
			bMoveOk=0;
			bMoveUpOk=0;
			bMoveDnOk=0;
			bsSlip=1;            
			bCarErr=1;   
            bCarStopNoRun=1;               
			OUT_GBR=1;
	}
}



void __attribute__((section(".usercode")))  NextFloorCheck(void)
{
   if(sRamDArry[mBefcurfloor] != sRamDArry[mcurfloor]){
      NextFloorTime=0;
      sRamDArry[mBefcurfloor] = sRamDArry[mcurfloor];
      bsNextFloor=0;
      
      ErrFlagClr();
   }
            
   if(!bMoveCar){
      NextFloorTime=0;    
      bsNextFloor=0;
   }  
   else if(NextFloorTime> (BASE_NEXT_FLR_TIME + (cF_NEXTFLRTIME * 10))){
//      if(bOnLuLd){
//           bCarErr=1;
//      }
        bsNextFloor=1;
        bCarErr=1;
   }
}



void __attribute__((section(".usercode")))  MvCounter(void)
{	

     if(bMoveCar){                  
		if(!bCntOn){
			eDArry[eMvCounter]++;
			if((eDArry[eMvCounter] == 0) || (eDArry[eMvCounter] > 255)){
				eDArry[eMvCounter+1]++;          
			}
			bCntOn=1;
            bCntOnAct=1;
            eMvCounterCnt=0;
		}               
	}
	else{
		bCntOn=0; 
	}
   
	if(bCntOnAct){
		if(!EEPROM_write_Ready() && !bMoveCar){
			if(!EEPROM_Write_Byte((unsigned int)(eMvCounter + eMvCounterCnt),eDArry[eMvCounter + eMvCounterCnt])){
				eMvCounterCnt++;
				if(eMvCounterCnt > 1){
					eMvCounterCnt=0;
					bCntOnAct=0;
				}  
			}     
		}                       
	}
}





void  __attribute__((section(".usercode"))) OutData(void)
{
    unsigned int tmpio;
    unsigned int tmpiobuf;

    TRISB=0x00ff;

    OUT_ACT1=0;
    OUT_ACT2=0;


    OUT_0=0;
    OUT_1=0;
    OUT_2=0;

    RD_WR=1;
    RD_WR=1;

    tmpio=(LATB & 0x00ff);
    tmpiobuf=(O_U_W_bit << 8);          
    tmpio=(tmpiobuf | tmpio);
    LATB=tmpio;

    OUT_0=1;
    OUT_0=1;
    OUT_0=1;
    OUT_0=1;

    OUT_0=0;
    OUT_0=0;
    OUT_0=0;
    OUT_0=0;


    tmpio=(LATB & 0x00ff);         
    tmpiobuf=(O_OP_bit << 8);          
    tmpio=(tmpiobuf | tmpio);

    LATB=tmpio;

    OUT_1=1;
    OUT_1=1;
    OUT_1=1;
    OUT_1=1;

    OUT_1=0;
    OUT_1=0;
    OUT_1=0;
    OUT_1=0;

    tmpio=(LATB & 0x00ff);         
    tmpiobuf=(O_Y_0_bit << 8);          

    tmpio=(tmpiobuf | tmpio);

    LATB=tmpio;

    OUT_2=1;
    OUT_2=1;
    OUT_2=1;
    OUT_2=1;

    OUT_2=0;
    OUT_2=0;
    OUT_2=0;
    OUT_2=0;

/////////////
    OUT_SEG_SEL0=1;
    OUT_SEG_SEL1=1;                               
    
    SegSel=(SegSel+1) % 3;

    switch(SegSel){
        case    0:
            tmpio=(LATB & 0x00ff);         
            tmpiobuf=(SegData0 << 8);          
            tmpio=(tmpiobuf | tmpio);
            LATB=tmpio;
            OUT_SEG_SEL0=0;
            OUT_SEG_SEL1=0;                               
            break;
        case    1:
            tmpio=(LATB & 0x00ff);         
            tmpiobuf=(SegData1 << 8);          
            tmpio=(tmpiobuf | tmpio);
            LATB=tmpio;
            OUT_SEG_SEL0=1;
            OUT_SEG_SEL1=0;                               
            break;
        case    2:
            tmpio=(LATB & 0x00ff);         
            tmpiobuf=(SegData2 << 8);          
            tmpio=(tmpiobuf | tmpio);
            LATB=tmpio;
            OUT_SEG_SEL0=0;
            OUT_SEG_SEL1=1;                               
            break;
        default:
            break;
    }
    
    OUT_SEG=1;
    OUT_SEG=1;
    OUT_SEG=1;
    OUT_SEG=1;

    OUT_SEG=0;
    OUT_SEG=0;
    OUT_SEG=0;
    OUT_SEG=0;
//////////////////

    OUT_ACT1=0;
    OUT_ACT2=0;

    RD_WR=0;

    TRISB=0xffff;

    sRamDArry[O_OP]  = O_OP_bit;
    sRamDArry[O_U_W] = O_U_W_bit;
    sRamDArry[O_Y_0] = O_Y_0_bit;
}





void  __attribute__((section(".usercode")))   AddressRead(void)
{
    UserDataType    tmp;
    unsigned int i;

    OUT_ON=0;
    RD_WR=0;
    IN_4=0;

    OUT_ON=0;
    RD_WR=0;
    IN_4=0;
    IN_4=0;
    IN_4=0;
    IN_4=0;

    i=PORTB; 
    tmp=(UserDataType)((i>>8));
    tmp=~tmp;
    tmp=(tmp & 0x00ff);

    MyGroupAddr=(tmp >> 4);
    MyNc_Addr  =((tmp >> 3) & 0x1);
    MyLocalAddr=(tmp & 0x03);
   
//    HostAddr=tmp & 0x00ff;    

    IN_4=1;
    IN_4=1;
    IN_4=1;
}




void __attribute__((section(".usercode")))  InPutRead(void)
{
    unsigned int i;


    LocalType tmp;

    OUT_ON=0;

    PORTD=0xffff;
    i=PORTD;
     
    tmp=(UserDataType)i;

    if(Bef_I_EMG == tmp){
        if(I_EMG_Cht >= 10){
            I_EMG_bit=tmp;

            Bef_I_EMG = tmp;
            I_EMG_Cht = 0;

/*
            if(!(cF_NCNOBIT0 & NcNoOpLmS)){
                IN_OP_E=!IN_OP_E;		         //b
            }
			
            if(!(cF_NCNOBIT0 & NcNoParking)){
                IN_PRK = !IN_PRK;		         //b
            }	
*/
        }  
    }
    else{
        I_EMG_Cht=0;
        Bef_I_EMG=tmp;
    }  


    tmp=(UserDataType)(i>>8);
    if(Bef_I_SU1 == tmp){
        if(I_SU1_Cht >= 10){
            I_SU1_bit=tmp;
            Bef_I_SU1 = tmp;
            I_SU1_Cht = 0;

/*
            if(!(cF_NCNOBIT0 & NcNoSafety)){
                IN_SFT=!IN_SFT;		
            }
						
            if(!(cF_NCNOBIT0 & NcNoOverload)){
                IN_OLR=!IN_OLR;		
            }
*/
        }  
    }
    else{
        I_SU1_Cht=0;
        Bef_I_SU1=tmp;
    }  




    tmp=0;
    if(PORTBbits.RB2)    tmp = tmp | 0x01;  //IN_RG
    if(PORTBbits.RB6)    tmp = tmp | 0x02;  //IN_BAT
    if(PORTBbits.RB7)    tmp = tmp | 0x04;  //IN_PASS
    if(PORTAbits.RA9)    tmp = tmp | 0x08;  //IN_FIRE
    if(PORTAbits.RA10)   tmp = tmp | 0x10;  //IN_WATER
    if(PORTAbits.RA14)   tmp = tmp | 0x20;  //IN_EX0
    if(PORTAbits.RA15)   tmp = tmp | 0x40;  //IN_EX1
    if(PORTFbits.RF6)    tmp = tmp | 0x80;  //IN_EX2


    if(Bef_I_GR == tmp){
        if(I_GR_Cht >= 10){
            I_GR_bit=tmp;
            Bef_I_GR = tmp;
            I_GR_Cht = 0;

/*
            if(!(cF_NCNOBIT1 & NcNoGr)){
                IN_GR=!IN_GR;		
            }
            if(!(cF_NCNOBIT1 & NcNoBat)){
                IN_BAT=!IN_BAT;		
            }
            if(!(cF_NCNOBIT1 & NcNoPass)){
                IN_PASS=!IN_PASS;		
            }
            if(!(cF_NCNOBIT1 & NcNoFire)){
                IN_FIRE=!IN_FIRE;		
            }
            if(!(cF_NCNOBIT1 & NcNoWater)){
                IN_WATER=!IN_WATER;		
            }
            if(!(cF_NCNOBIT1 & NcNoEx0)){
                IN_FULL=!IN_FULL;		
            }
            if(!(cF_NCNOBIT1 & NcNoEx1)){
                IN_EX1=!IN_EX1;		
            }
            if(!(cF_NCNOBIT1 & NcNoEx2)){
                IN_EX2=!IN_EX2;		
            }
*/
        }  
    }
    else{
        I_GR_Cht=0;
        Bef_I_GR=tmp;
    }  



    RD_WR=0;  

    IN_3=0;
    IN_3=0;
    IN_3=0;
    IN_3=0;

    i=PORTB; 
    tmp=(UserDataType)(i>>8);

    if(Bef_I_FIRE == tmp){
        if(I_FIRE_Cht >= 10){
            I_FIRE_bit=tmp; 
            Bef_I_FIRE = tmp;
            I_FIRE_Cht = 0;

/*
            if(!(cF_NCNOBIT2 & NcNoFr1)){
                IN_FR1=!IN_FR1;		
            }
            if(!(cF_NCNOBIT2 & NcNoFr2)){
                IN_FR2=!IN_FR2;		
            }
            if(!(cF_NCNOBIT2 & NcNoFr3)){
                IN_FR3=!IN_FR3;		
            }
            if(!(cF_NCNOBIT2 & NcNoFr4)){
                IN_FR4=!IN_FR4;		
            }
            if(!(cF_NCNOBIT2 & NcNoSu2)){
                IN_SU2=!IN_SU2;		
            }
            if(!(cF_NCNOBIT2 & NcNoSd2)){
                IN_SD2=!IN_SD2;		
            }
            if(!(cF_NCNOBIT2 & NcNoSu3)){
                IN_SU3=!IN_SU3;		
            }
            if(!(cF_NCNOBIT2 & NcNoSd3)){
                IN_SD3=!IN_SD3;		
            }
*/
        }  
    }
    else{
        I_FIRE_Cht=0;
        Bef_I_FIRE=tmp;
    }  

    IN_3=1;


    IN_0=0;
    IN_0=0;
    IN_0=0;
    IN_0=0;

    i=PORTB;
    tmp=(UserDataType)(i>>8);
 

    if(Bef_I_FS0 == tmp){
        if(I_FS0_Cht >= 10){
            if(RUN_MODE == LG_INVERTER_ELEV){
                I_FS0_bit = ~tmp;
                Bef_I_FS0 = tmp;
                I_FS0_Cht = 0;
            }
        }  
    }
    else{
        I_FS0_Cht=0;
        Bef_I_FS0=tmp;
    }    


    IN_0=1;
    IN_0=1;


    IN_1=0;
    IN_1=0;
    IN_1=0;
    IN_1=0;

    i=PORTB;
    tmp=(UserDataType)(i>>8);

    if(Bef_I_X_0 == tmp){
        if(I_X_0_Cht >= 10){
            I_X0_bit=tmp;

            Bef_I_X_0 = tmp;
            I_X_0_Cht = 0;

/*
            if(!(cF_NCNOBIT3 & NcNoX0)){
                IN_X0=!IN_X0;		
            }
            if(!(cF_NCNOBIT3 & NcNoX1)){
                IN_X1=!IN_X1;		
            }
            if(!(cF_NCNOBIT3 & NcNoX2)){
                IN_X2=!IN_X2;		
            }
            if(!(cF_NCNOBIT3 & NcNoX3)){
                IN_X3=!IN_X3;		
            }
            if(!(cF_NCNOBIT3 & NcNoX4)){
                IN_X4=!IN_X4;		
            }
            if(!(cF_NCNOBIT3 & NcNoX5)){
                IN_X5=!IN_X5;		
            }
            if(!(cF_NCNOBIT3 & NcNoX6)){
                IN_X6=!IN_X6;		
            }
            if(!(cF_NCNOBIT3 & NcNoX7)){
                IN_X7=!IN_X7;		
            }
*/
        }  
    }
    else{
        I_X_0_Cht=0;
        Bef_I_X_0=tmp;
    }
  
    IN_1=1;


///OLD VERSION
    OldFireBuf = 0x00;

    if((I_GR_bit   & 0x01))  OldFireBuf=(OldFireBuf | 0x01);
    if((I_FIRE_bit & 0x01))  OldFireBuf=(OldFireBuf | 0x02);
    if((I_FIRE_bit & 0x02))  OldFireBuf=(OldFireBuf | 0x20);
    if((I_FIRE_bit & 0x04))  OldFireBuf=(OldFireBuf | 0x40);
    if((I_FIRE_bit & 0x08))  OldFireBuf=(OldFireBuf | 0x80);

    OldFireBuf=(OldFireBuf | 0x04);
///OLD VERSION


    sRamDArry[I_EMG]  = I_EMG_bit;
    sRamDArry[I_SU1]  = I_SU1_bit;
    sRamDArry[I_GR]   = I_GR_bit;
    sRamDArry[I_FIRE] = I_FIRE_bit;
    sRamDArry[I_X_0]  = I_X0_bit;
    sRamDArry[I_FS0]  = I_FS0_bit;
}




void  __attribute__((section(".usercode")))  	UserLampSet(void)
{	

   	switch(cF_USERLAMP){
      	case  0:
         		if(bAuto)   S2_LAMP_USER1=1;
         		else        S2_LAMP_USER1=0;
         		break;
      	case  1:
         		if(!bAuto)   S2_LAMP_USER1=1;
         		else         S2_LAMP_USER1=0;

         		break;
      	case  2:
         		if(S1_OVERLOAD1)  S2_LAMP_USER1=1;
         		else              S2_LAMP_USER1=0;     
         		break;
      	case  3:
         		if(S2_FIRE1)      S2_LAMP_USER1=1;
         		else              S2_LAMP_USER1=0;     
         		break;
      	case  4:
         		if(S1_EMG1)    S2_LAMP_USER1=1;
         		else           S2_LAMP_USER1=0;     
         		break;
      	case  5:
         		if(S3_PARKING1)   S2_LAMP_USER1=1;
         		else                                   S2_LAMP_USER1=0;     
         		break;
      	case  6:
         		if(S3_VIP1)   S2_LAMP_USER1=1;
         		else                               S2_LAMP_USER1=0;     
         		break;
      	case  7:
         		S2_LAMP_USER1=0;     
         		break;
   	}

}

void  __attribute__((section(".usercode"))) 	ServiceCheck(void)
{
	if(ExtCmdFlrONOFFCnt > 5){
	  sRamDArry[ExtCmdFlrONOFF0]=0xff;	
	  sRamDArry[ExtCmdFlrONOFF1]=0xff;	
	  sRamDArry[ExtCmdFlrONOFF2]=0xff;	
	  sRamDArry[ExtCmdFlrONOFF3]=0xff;	
	  ExtCmdFlrONOFFCnt=6;
	}
	
	sRamDArry[FLR_ON_OFF0] =(cF_NONSERVICE0 & sRamDArry[ExtCmdFlrONOFF0]);
	sRamDArry[FLR_ON_OFF1] =(cF_NONSERVICE1 & sRamDArry[ExtCmdFlrONOFF1]);
	sRamDArry[FLR_ON_OFF2] =(cF_NONSERVICE2 & sRamDArry[ExtCmdFlrONOFF2]);
	sRamDArry[FLR_ON_OFF3] =(cF_NONSERVICE3 & sRamDArry[ExtCmdFlrONOFF3]);				
}



void    __attribute__((section(".usercode"))) WaterCheck(void)
{
   	if(!IN_WATER && bAuto && !S3_PARKING1){
      	if((sRamDArry[mcurfloor]== cF_TOPFLR) && !bMoveCar){
//                S3_STOP=1;

                if(bOnLuLd && bDoorOpenEnd){
                  	ClrUpDnWard();       
                   	bExtButClr=1;
                    bCarButClr=1;   
                    bWaterSen=1;
             		if(sRamDArry[mDoorSeq] >= DOOR_REOPEN_CHECK){
                		sRamDArry[mDoorSeq]=DOOR_OPEN_START;
             		}
                }
                else if(bOnLuLd && (sRamDArry[mDoorSeq] > DOOR_OPEN_WAIT)){
                    sRamDArry[mDoorSeq] = DOOR_OPEN_START;
                } 

            	if(sRamDArry[mSysStatus] > sWaterSense)   sRamDArry[mSysStatus]=sWaterSense;      
      	}
      	else{
                sRamDArry[mHighFloor]=cF_TOPFLR | CAR_READY;
        }
	}
    else{
        bWaterSen=0;
    }
}



#define b_IN_SU1    0xfe
#define b_IN_SD1    0xfd
#define b_IN_SFT    0xfb
#define b_IN_OLR    0xf7  
#define b_IN_ULS    0xef   
#define b_IN_DLS    0xdf
#define b_IN_LU     0xbf
#define b_IN_LD     0x7f

#define b_IN_EMG    0xfe
#define b_IN_PRK    0xfd
#define b_IN_AUTO   0xfb
#define b_IN_U_B    0xf7
#define b_IN_D_B    0xef
#define b_IN_OP_E   0xdf
#define b_IN_CL_E   0xbf
#define b_IN_HL_D   0x7f

#define b_IN_GR     0xfe
#define b_IN_BAT    0xfd
#define b_IN_PASS   0xfb
#define b_IN_FIRE   0xf7
#define b_IN_WATER  0xef
#define b_IN_FULL   0xdf
#define b_IN_EX1    0xbf
#define b_IN_EX2    0x7f

#define b_IN_FR1    0xfe
#define b_IN_FR2    0xfd
#define b_IN_FR3    0xfb
#define b_IN_FR4    0xf7
#define b_IN_SU2    0xef
#define b_IN_SD2    0xdf
#define b_IN_SU3    0xbf
#define b_IN_SD3    0x7f

#define b_IN_FS0    0x01
#define b_IN_FS1    0x02
#define b_IN_FS2    0x04
#define b_IN_FS3    0x08
#define b_IN_FS4    0x10
#define b_IN_DER    0x20
#define b_IN_FID    0x40
#define b_IN_UND    0x80

#define b_IN_X0     0xfe
#define b_IN_X1     0xfd
#define b_IN_X2     0xfb
#define b_IN_X3     0xf7
#define b_IN_X4     0xef
#define b_IN_X5     0xdf
#define b_IN_X6     0xbf
#define b_IN_X7     0x7f



#define bb_IN_FR1    0x0e
#define bb_IN_FR2    0x0d
#define bb_IN_FR3    0x0b
#define bb_IN_FR4    0x07


void  __attribute__((section(".usercode")))   IO_Check(void)
{

			bIOError=1;

            OUT_OP      =0;
            OUT_DAC     =0;                
            OUT_CL      =0;
            OUT_SIREN   =0;
            OUT_OP_S    =0;
            OUT_ERR     =0;
            OUT_CL_S    =0;
            OUT_EY1     =0;
            OUT_BK2     =0;
            OUT_EY2     =0;
            OUT_GBR     =0;
            OUT_BRK     =0;    
            OUT_U_W     =0;
            OUT_EY0     =0;
            OUT_D_W     =0; 
            OUT_P1      =0; 
            OUT_P2      =0;
            OUT_P3      =0;
            OUT_P4N     =0;
            OUT_FAN     =0;
            OUT_LIT     =0;
            OUT_BUZ     =0;
            OUT_BELL    =0;


   	sRamDArry[mSysStatus]=sREADY;
        switch(TestLoop){
        case    0:
            OUT_OP      =1;
            OUT_DAC     =1;                
            break;
        case    1:
            OUT_CL      =1;
            OUT_SIREN   =1;
            break;
        case    2:
            OUT_OP_S    =1;
            OUT_ERR     =1;
            break;
        case    3:
            OUT_CL_S    =1;
            OUT_EY1     =1;
            break;
        case    4:
            OUT_BK2     =1;
            OUT_EY2     =1;
            break;
        case    5:
            OUT_GBR     =1;
            break;
        case    6:
            OUT_BRK     =1;    
            break;
        case    7:
            OUT_U_W     =1;
            OUT_EY0     =1;
            break;
        case    8:
            OUT_D_W     =1; 
            break;
        case    9:
            OUT_P1      =1; 
            break;
        case    10:
            OUT_P2      =1;
            break;
        case    11:
            OUT_P3      =1;
            break;
        case    12:
            OUT_P4N     =1;
            break;
        case    13:
            OUT_FAN     =1;
            break;
        case    14:
            OUT_LIT     =1;
            break;
        case    15:
            OUT_BUZ     =1;
            break;
        case    16:
            OUT_BELL    =1;
            break;

    }
    
    OutData();

   	InPutRead();

    AddressRead();
    TestDip=MyGroupAddr;
    MyGroupAddr=0;

    I_EMG_bit   =I_EMG_bit  & 0x00ff;
    I_SU1_bit   =I_SU1_bit  & 0x00ff;
    I_GR_bit    =I_GR_bit   & 0x00ff;
    I_FIRE_bit  =I_FIRE_bit & 0x00ff;
    I_X0_bit    =I_X0_bit   & 0x00ff;
    I_FS0_bit   =I_FS0_bit  & 0x00ff;


    if(TestDip == 0x08){            
        switch(TestLoop){                
            case    0:

/*
#define b_IN_SU1    0x01
#define b_IN_SD1    0x02
#define b_IN_SFT    0x04
#define b_IN_OLR    0x08  
#define b_IN_ULS    0x10   
#define b_IN_DLS    0x20
#define b_IN_LU     0x40
#define b_IN_LD     0x80

#define b_IN_EMG    0x01
#define b_IN_PRK    0x02
#define b_IN_AUTO   0x04
#define b_IN_U_B    0x08
#define b_IN_D_B    0x10
#define b_IN_OP_E   0x20
#define b_IN_CL_E   0x40
#define b_IN_HL_D   0x80

#define b_IN_GR     0x01
#define b_IN_BAT    0x02
#define b_IN_PASS   0x04
#define b_IN_FIRE   0x08
#define b_IN_WATER  0x10
#define b_IN_FULL   0x20
#define b_IN_EX1    0x40
#define b_IN_EX2    0x80

#define b_IN_FR1    0x01
#define b_IN_FR2    0x02
#define b_IN_FR3    0x04
#define b_IN_FR4    0x08
#define b_IN_SU2    0x10
#define b_IN_SD2    0x20
#define b_IN_SU3    0x40
#define b_IN_SD3    0x80

#define b_IN_FS0    0x01
#define b_IN_FS1    0x02
#define b_IN_FS2    0x04
#define b_IN_FS3    0x08
#define b_IN_FS4    0x10
#define b_IN_DER    0x20
#define b_IN_FID    0x40
#define b_IN_UND    0x80

#define b_IN_X0     0x01
#define b_IN_X1     0x02
#define b_IN_X2     0x04
#define b_IN_X3     0x08
#define b_IN_X4     0x10
#define b_IN_X5     0x20
#define b_IN_X6     0x40
#define b_IN_X7     0x80
*/

                if(I_EMG_bit==b_IN_EMG){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_BAT){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										bIOError=0;
										SirenTime=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_EMG) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_BAT) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }
*/        
                break;
            case    1:
                //PRK
                if(I_EMG_bit==b_IN_PRK){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_PASS){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										bIOError=0;
										SirenTime=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*
                if((I_EMG_bit==b_IN_PRK) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_PASS) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    2:
                //AT
                if(I_EMG_bit==b_IN_AUTO){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_FIRE){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										bIOError=0;
										SirenTime=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_AUTO) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_FIRE) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    3:
                //UB
                if(I_EMG_bit==b_IN_U_B){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_WATER){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_U_B) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_WATER) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    4:
                //DB
                if(I_EMG_bit==b_IN_D_B){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_FULL){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										bIOError=0;
										SirenTime=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_D_B) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_FULL) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    5:
                //OLS
                if(I_EMG_bit==b_IN_OP_E){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_OP_E) && (I_SU1_bit==0xff) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    6:
                //GS
                if(I_EMG_bit==b_IN_CL_E){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_CL_E) && (I_SU1_bit==0xff) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    7:
                //DS
                if(I_EMG_bit==b_IN_HL_D){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==bb_IN_FR1){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_HL_D) && (I_SU1_bit==0xff) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==bb_IN_FR1) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    8:
                //SU1
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_SU1){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==bb_IN_FR2){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_SU1) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==bb_IN_FR2) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    9:
                //SD1
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_SD1){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==bb_IN_FR3){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										bIOError=0;
										SirenTime=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_SD1) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==bb_IN_FR3) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    10:
                //SFT
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_SFT){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==bb_IN_FR4){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_SFT) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==bb_IN_FR4) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    11:
                //OLR
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_OLR){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										bIOError=0;
										SirenTime=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_OLR) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    12:
                //ULS
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_ULS){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_ULS) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    13:
                //DLS
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_DLS){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_DLS) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    14:
                //LU
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_LU){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_LU) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    15:
                //LD
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_LD){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_LD) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    16:
                //RG
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_GR){
                			if(I_FIRE_bit==0x0f){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop=0;    
										SirenTime=0;
										bIOError=0;
					                    if(TestIO < 110)    TestIO++;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_GR) 
                && (I_FIRE_bit==0x0f) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop=0;    
					bIOError=0;
                    if(TestIO < 100)    TestIO++;
                }        
*/
                break;
        }
    }

    else{
        switch(TestLoop){                
            case    0:
                //EMG
                if(I_EMG_bit==b_IN_EMG){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_BAT){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X2){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*
                if((I_EMG_bit==b_IN_EMG) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_BAT) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X2) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/

                break;
            case    1:
                //PRK
                if(I_EMG_bit==b_IN_PRK){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_PASS){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X3){
									if(I_FS0_bit==0x00){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*
                if((I_EMG_bit==b_IN_PRK) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_PASS) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X3) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    2:
                if(I_EMG_bit==b_IN_AUTO){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_FIRE){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X4){
									if(I_FS0_bit==0x00){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*
                //AT
                if((I_EMG_bit==b_IN_AUTO) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_FIRE) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X4) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    3:
                //UB
                if(I_EMG_bit==b_IN_U_B){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_WATER){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X5){
									if(I_FS0_bit==0x00){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_U_B) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_WATER) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X5) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    4:
                //DB
                if(I_EMG_bit==b_IN_D_B){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_FULL){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X6){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_D_B) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_FULL) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X6) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    5:
                //OLS
                if(I_EMG_bit==b_IN_OP_E){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_EX1){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X7){
									if(I_FS0_bit==0x00){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_OP_E) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_EX1) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X7) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    6:
                //GS
                if(I_EMG_bit==b_IN_CL_E){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_EX2){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_FS0){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_CL_E) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_EX2)  //fhm 
                && (I_FIRE_bit==0xff) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_FS0)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    7:
                //DS
                if(I_EMG_bit==b_IN_HL_D){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_FR1){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_FS1){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==b_IN_HL_D) && (I_SU1_bit==0xff) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_FR1) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_FS1)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    8:
                //SU1
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_SU1){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_FR2){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_FS2){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_SU1) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_FR2) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_FS2)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    9:
                //SD1
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_SD1){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_FR3){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_FS3){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*
                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_SD1) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_FR3) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_FS3)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    10:
                //SFT
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_SFT){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_FR4){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_FS4){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_SFT) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_FR4) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_FS4)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    11:
                //OLR
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_OLR){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_SU2){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_DER){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;

/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_OLR) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_SU2) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_DER)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    12:
                //ULS
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_ULS){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_SD2){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_FID){
										SirenTime=0;
					                    TestLoop++;    
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;
/*
                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_ULS) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_SD2) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_FID)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    13:
                //DLS
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_DLS){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_SU3){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==b_IN_UND){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;
/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_DLS) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_SU3) && (I_X0_bit==0xff) && (I_FS0_bit==b_IN_UND)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    14:
                //LU
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_LU){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==b_IN_SD3){
								if(I_X0_bit==0xff){
									if(I_FS0_bit==0x00){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;
/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_LU) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==b_IN_SD3) && (I_X0_bit==0xff) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    15:
                //LD
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==b_IN_LD){
						if(I_GR_bit==0xff){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X0){
									if(I_FS0_bit==0x0){
					                    TestLoop++;    
										SirenTime=0;
										bIOError=0;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;
/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==b_IN_LD) && (I_GR_bit==0xff) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X0) && (I_FS0_bit==0x00)){
                    TestLoop++;    
					bIOError=0;
                }        
*/
                break;
            case    16:
                //RG
                if(I_EMG_bit==0xff){
					if(I_SU1_bit==0xff){
						if(I_GR_bit==b_IN_GR){
                			if(I_FIRE_bit==0xff){
								if(I_X0_bit==b_IN_X1){
									if(I_FS0_bit==0x0){
					                    TestLoop=0;    
										SirenTime=0;
										bIOError=0;
					                    if(TestIO < 110)    TestIO++;
									}
									else	you=5;
								}
								else	you=4;
							}
							else	you=3;
						}
						else	you=2;
					}
					else	you=1;
				}
				else	you=0;
/*

                if((I_EMG_bit==0xff) && (I_SU1_bit==0xff) && (I_GR_bit==b_IN_GR) 
                && (I_FIRE_bit==0xff) && (I_X0_bit==b_IN_X1) && (I_FS0_bit==0x00)){
                    TestLoop=0;    
                    if(TestIO < 100)    TestIO++;
					bIOError=0;
                }        
*/
                break;
        }
    }


	if(SirenTime > 3){
		SirenTime = 4;
		bIOError=1;	
	}	
	else	bIOError=0;	

/*        
   	InputCheck();

   	AutoManualCheck();

   	CarCurFloorRead();   
	ServiceCheck();
    FireKeyCheck();
    WaterCheck();
   	ButtonClrCheck();   
	
    if(!bManualStop){    
        if(bAuto){
            if(!bManualAuto){
                if(CarOnceStopTime>30){
                    FindLuLdManual();
                    CarOnceStopTime=31;      
                    bTestKey=0;
                }
            }
            else{
                if(!((sRamDArry[mFireSeq] == FIRE_ONE) || (sRamDArry[mFireSeq] == FIRE_THREE) )){            
                    DoorOpenCloseSeq();
                    DoorOpClSystem();
                }
                SlipCheck();         
                NextFloorCheck();
                TestUpDn();
                MvCounter();
            }        
            CounterCheck();
        }                     
        else{    
            bSearchHome=0;
            FixFlrTimeCnt=0;
            NextFloorTime=0;
            NoCloseCnt=0;
            bCarStopNoRun=0;             
            bsSlip=0;
            bTempCall=0;
            bInspect=0;
            bSlipCheckStart=0;
            
            if(!IN_GR){
                OUT_GBR=0;
            }
            
            
            bTestKey=0;                        
            bCarUpDnChButClr=0;
            
            if(!S3_PARKING1){
                if(sRamDArry[mSysStatus] >= sMANUAL)   sRamDArry[mSysStatus] = sMANUAL;                                
                OUT_FAN=1;
                FanTime=0;  
                sRamDArry[mReqStopFloor]=0;
                sRamDArry[mAckStopFloor]=0;
                sRamDArry[mNewAckStopFloor]=0;
                bManualAuto=0;      
                OUT_DAC=0;
                
                ManualUpDnKeyCheck();
                ManualUpDown();            
            
                if(!bManualUpKey && !bManualDnKey){
                    bCarStop=1; 
                    if(!OpenKeyCheck()){
                        SelectDoorOpen();
                    }
                    else AllDoorOpenClrCmd();
                
                    if(!CloseKeyCheck()){
                        SelectDoorClose();				
                    }
                    else AllDoorCloseClrCmd();
                }
            }	                  
        }
    }

    DoorOpenEndCheck();
    
    if(bUpWard || bDnWard || !bDoorCloseOk){
        OUT_FAN=1;
        FanTime=0;  
    }   
    else if(FanTime > cF_FANTIME){
        FanTime = cF_FANTIME +1;              
        OUT_FAN=0;
    }
    
    if(WarmingUpTime<100){
        bCarErr=1;
        CurFTime=0;
        NextFTime=0;
    }



    if((cF_ERRSTOPCNT < eDArry[eErrCntPt]) && (cF_ERRSTOPCNT != 0xff)){
        bCarStopNoRun=1;  
        bInspect=1;
    }
    
    InverterErrorCheck();


    if(bCarErr || bCarStopNoRun || bCarStop || bManualStop){
        if(sRamDArry[mSysStatus] >= sMANUAL)   sRamDArry[mSysStatus] = sMANUAL;      

        AutoNoMoveTime=0;
          
        CarAllStopCmdTest();
      	
        if(!bManualStop){      	        
            if(bCarStopNoRun){
                AllDoorOpenClrCmd();      	
                bTestKey=0;    
            }   
            else if(bCarErr){
                bTestKey=0;                                 		
            }           
    
            bManualAuto=0;    
            bCarStop=0;       
            bCarErr=0;        
            FixFlrTimeCnt=0;
        }     	 	
    }

    if(!bAuto && bMoveCar){
        OUT_SIREN=1;
    }
    else{
        SirenTime=0;
        OUT_SIREN=0;        
    }

    MotorStop();


    if(!IN_BAT && bAuto){
        if(RUN_MODE == IO_INVERTER){
            if(PowerFailTime > 20){
                PowerFailTime=21;
                OUT_P4N=0;                                             
            }
            else{
                OUT_P4N=1;                                             
            }
        }

        if(PowerFailTime < 20){
            bCarErr=1;                                                                 
        }


        S1_POWER_FAIL=1;
        NextFloorTime=0;
////
        if(bOnLuLd && bDoorOpenEnd && !bMoveCar){
          	ClrUpDnWard();       
            OUT_FAN=0;            
     		if(sRamDArry[mDoorSeq] >= DOOR_REOPEN_CHECK){
        		sRamDArry[mDoorSeq]=DOOR_OPEN_START;
     		}
        }
        else if(bOnLuLd && !bMoveCar && (sRamDArry[mDoorSeq] > DOOR_OPEN_WAIT)){
            sRamDArry[mDoorSeq] = DOOR_OPEN_START;
        } 
    }
    else{
        if(S1_POWER_FAIL){
            if(PowerFailTime > 40){
                PowerFailTime=41;
                S1_POWER_FAIL=0;
                if(RUN_MODE == IO_INVERTER){                                             
                    OUT_P4N=0;                                             
                }
            }
            else{
                if(RUN_MODE == IO_INVERTER){                                             
                    OUT_P4N=1;                                             
                }
                bCarErr=1;
            }
        }

        else{                    
            PowerFailTime=0;
        }
    }     


    if((bOnLuLd && bDoorOpenEnd) && bAuto && (!IN_WATER || !IN_BAT)){            
        S3_STOP1=1;
    } 
    else    S3_STOP1=0;    



    if(IN_FR1 || IN_FR2){    
       if(S1_OVERLOAD1){              
            OUT_BUZ=1;          
        }
        else{      
            OUT_BUZ=0;         
        }
    }

    
//    if(bAuto && (sRamDArry[mDoorSeq] == STOP_ELEVATOR) && (VoiceTime > 5)){


    if(bAuto && (sRamDArry[mDoorSeq] >= WAIT_NEXT_LULD) && (VoiceTime > 10) && (VoiceTime < 20) && IN_UND){
        OUT_BELL=1;     
        S2_FLOW1=1;	
    }       		
    else{
        OUT_BELL=0;          
        S2_FLOW1=0;	
    }

   	UserLampSet();

    if(LIGHT_AB == LIGHT_A) LightNormal_A(); 
    else                    LightNormal_B(); 

    OutData();

    if(bAuto){
	    SystemErrSave();
    }

	WhyStop();

    sRamDArry[S1_STATE]=S1_STATE_bit;
    sRamDArry[S2_STATE]=S2_STATE_bit;
    sRamDArry[S3_STATE]=S3_STATE_bit;
    sRamDArry[S4_STATE]=S4_STATE_bit;
    sRamDArry[SelDoorStatus]=DoorStatus_bit;
*/
}      



void  Timer1Init(void)
{
     
	T1CON = 0 ;//Turn off Timer1 by clearing control register
    IPC0bits.T1IP=1;
	TMR1 = 0 ;  //Start Timer1 at zero
    PR1=16000;
//    PR1=32000;
    _T1ON = 1;
    _T1IE = 1;
}



void  LvdInit(void)
{
    LVDIE=0;

//    RCONbits.LVDL=0x0e; //4.6v
//    RCONbits.LVDL=0x0d; //4.3v
//    RCONbits.LVDL=0x0c; //4.1v
//    LVDEN=1;

//    while(!BGST);

    RCON=RCON & 0xc0ff;
    RCON=RCON | 0x1c00;    //4.1v

    LVDIF=0;
    LVDIE=1;
}


void  Uart1Init(void)
{
    U1BRG=51;
    U1STA=0x0;

    _U1RXIP=4;
    _U1TXIP=4;

    _U1PDSEL=0;

    _U1STSEL  = 0;

    _U1ABAUD  = 0;
    _U1LPBACK = 0;
    _U1WAKE   = 0;
    _U1ALTIO  = 0;
    _U1USIDL  = 0;
    _U1UARTEN = 1;

    _U1TXEN=1;
    _U1TXISEL=1;

    _U1TXIF=0;
    _U1RXIF=0;

    _U1RXIE=1;
    _U1TXIE=1;
}


void  Uart2Init(void)
{
    U2BRG=51;
    U2STA=0x0;

    _U2RXIP=4;
    _U2TXIP=4;

    _U2PDSEL=0;

    _U2STSEL  = 0;

    _U2ABAUD  = 0;
    _U2LPBACK = 0;
    _U2WAKE   = 0;
    _U2ALTIO  = 0;
    _U2USIDL  = 0;
    _U2UARTEN = 1;

//    U2STA=0x0;

    _U2TXEN=1;
    _U2TXISEL=1;

    _U2TXIF=0;
    _U2RXIF=0;

    _U2RXIE=1;
    _U2TXIE=1;
}




void FindCurFloor(void)
{
    LocalType i;


    i=EEPROM_Read_Word(e_CurFloor);
    sRamDArry[mcurfloor]=i;


    CurPulse=0x0;
    i=EEPROM_Read_Word(e_CurPulse+2);
    CurPulse=i;
    CurPulse=((CurPulse << 16) & 0xffff0000);  
    i=EEPROM_Read_Word(e_CurPulse);

    CurPulse=(CurPulse | (unsigned long)i); 



    i=sRamDArry[mcurfloor];

    if(sRamDArry[mcurfloor] == 0){
        if(CurPulse >= GET_LONG(FLR_02_PULSE)){
            sRamDArry[mcurfloor] = 0;
            CurPulse=0;
        } 
    }           
    else if(sRamDArry[mcurfloor] > cF_TOPFLR){
        sRamDArry[mcurfloor] = 0;
        CurPulse=0;
    }           
    else if(sRamDArry[mcurfloor] == cF_TOPFLR){
        if(CurPulse <= GET_LONG(cF_TOPFLR-1)){
            sRamDArry[mcurfloor] = 0;
            CurPulse=0;
        }
    }           
    else if((CurPulse >= GET_LONG(FLR_01_PULSE + (i+1))) || (CurPulse < GET_LONG(FLR_01_PULSE + (i-1))) ){
        sRamDArry[mcurfloor]=0;
        CurPulse=0;
    }
    

/*
    for(i=0;i<32;i++){
        if(CurPulse < GET_LONG(FLR_02_PULSE + i)){
            sRamDArry[mcurfloor]=i;
            search=0;
            i=50;
        }
    }


    if(search){
        sRamDArry[mcurfloor]=0;
    }
*/
    DspFloorSet();
}






    unsigned int zz;


int main(void)
{
    unsigned int i;


    TestLoop=0;
    TestIO=0;
    Test485=0;
    TestCan1=0;
    TestCan2=0;
    TestCnt=0;


    TRISA=0xffff;
    TRISB=0xffff;
    TRISC=0x0000;
    TRISD=0xffff;
    TRISE=0x0000;

    TRISF=0x0055;  //    01010101;
  
  TRISG=0x0001;  //          01 

    SPLIM=SPLIM;

    ADPCFG=0xffff;  //portb digital i/o

   	TXEN=1;
    bSaveFlash=1;


    OUT_ACT1=1;
    OUT_ACT2=1;

    IN_0=1;
    IN_1=1;
    IN_2=1;
    IN_3=1;
    IN_4=1;

    OUT_0=0;
    OUT_1=0;
    OUT_2=0;


    RD_WR=0;

   	OUT_ON=0;
   	OUT_ON=0;


    I_SU1_bit=0xff;
    I_EMG_bit=0xff;
  	I_GR_bit=0xff;
  	I_FIRE_bit=0xff;
 	I_FS0_bit=0xff;
  	I_X0_bit=0xff;

   	O_OP_bit=0x0;
  	O_U_W_bit=0x80;
   	O_Y_0_bit=0x0;


    sRamDArry[I_EMG]  = I_EMG_bit;
    sRamDArry[I_SU1]  = I_SU1_bit;
    sRamDArry[I_GR]   = I_GR_bit;
    sRamDArry[I_FIRE] = I_FIRE_bit;
    sRamDArry[I_X_0]  = I_X0_bit;
    sRamDArry[I_FS0]  = I_FS0_bit;

    sRamDArry[O_OP]  = O_OP_bit;
    sRamDArry[O_U_W] = O_U_W_bit;
    sRamDArry[O_Y_0] = O_Y_0_bit;



	CarAllStopCmd();

   	OUT_ON=0;
   	OUT_ON=0;

    OutData();
    OutData();
    OutData();

/*
    LadderGroup=0;
    LadderGroupSub=0;
    LadderKey=0xff;
*/

	for(LogAddressLoop=0;LogAddressLoop < MAX_LONG_BUF;LogAddressLoop++){
        parameter_mirror[LogAddressLoop]=0x0;
	}

	bCarErr=0;
   	bCarStopNoRun=0;
    bManualAuto=0;
   	bsSlip=0;                  
   
    AddressRead();
   
	for(LogAddressLoop=0;LogAddressLoop <= sec;LogAddressLoop++){
		sRamDArry[sRamDArry[mDoorSeq]]=0x0;
	}
         
	for(LogAddressLoop=0;LogAddressLoop<ABS_ADDRESS;LogAddressLoop++){
		BDid[sRamDArry[mDoorSeq]]=0;
		BdErrCntSeq[sRamDArry[mDoorSeq]]=0;
	}      


	sRamDArry[mDoorSeq]=DOOR_CLOSE_START;


	DoorCloseTime=0;
	sRamDArry[mReqStopFloor]=0;
	sRamDArry[mAckStopFloor]=0;
	sRamDArry[mNewAckStopFloor]=0;
	sRamDArry[mcurfloor]=0;
	sRamDArry[mEqualFloor]=0;
	sRamDArry[mHighFloor]=0;
	sRamDArry[mLowFloor]=0;


    sRamDArry[S1_STATE]=S1_STATE_bit=0;
    sRamDArry[S2_STATE]=S2_STATE_bit=0;
    sRamDArry[S3_STATE]=S3_STATE_bit=0;
    sRamDArry[S4_STATE]=S4_STATE_bit=0;
    sRamDArry[SelDoorStatus]=DoorStatus_bit=0;


	errbd[0]=0x0;
	errbd[1]=0x0;
	errbd[2]=0x0;
	errbd[3]=0x0;
	errbd[4]=0x0;
	errbd[5]=0x0;
	errbd[6]=0x0;
	errbd[7]=0x0;
	errbd[8]=0x0;
	errbd[9]=0x0;
	errbd[10]=0x0;
	errbd[11]=0x0;

	Olderrbd[0]=0x0;
	Olderrbd[1]=0x0;
	Olderrbd[2]=0x0;
	Olderrbd[3]=0x0;
	Olderrbd[4]=0x0;
	Olderrbd[5]=0x0;
	Olderrbd[6]=0x0;
	Olderrbd[7]=0x0;
	Olderrbd[8]=0x0;
	Olderrbd[9]=0x0;
	Olderrbd[10]=0x0;
	Olderrbd[11]=0x0;
   
	LogAddressLoop=0;
	LogAddress=0;        
	TimeOutBd=0;
	BefRcvAdr=0;
	AbsAddress=0;
	SerialTime=0;
	bFindBoard=0;   
	
	bManualAuto=0;
	bHomeUpDn=0;


//   	sRamDArry[S0_FLOOR]  = sRamDArry[mcurfloor]+1;  


//    Initialize_DS1302();


    IEC0=0x0;
    IEC1=0x0;
    IEC2=0x0;
  

//    INTCON2bits.ALTIVT=0;
    INTCON1bits.NSTDIS=1;

    QEI_Init(); 
    LvdInit();
    Timer1Init();
    Uart1Init();
    Uart2Init();
    Can1Init();
    Can2Init();


//    INTCON2bits.ALTIVT=0;
    INTCON1bits.NSTDIS=1;


    asm("CLRWDT");
    ReadInitSetupData();
    asm("CLRWDT");


    RxStatus = STX_CHK;


//    for(i=0;i<40;i++)   New485Ladder[i]=' ';   
//    Ladder485Init();


   	for(NoCloseCnt=0;NoCloseCnt<30;NoCloseCnt++){	      
   		Find_Absolute(MAS_A,LOG_ADR,LOGADR_CLR);   

   		while(RxStatus != STX_CHK){
            asm("CLRWDT");
        }

		for(firstdata=0;firstdata<200;firstdata++);
		for(firstdata=0;firstdata<200;firstdata++);
		for(firstdata=0;firstdata<200;firstdata++);				
        asm("CLRWDT");
   	}

      
   	RxStatus=STX_CHK;
   	MyDataTx();

      
   	sRamDArry[LD_INSP] = 0x0;

   
   	NoCloseCnt=0;
   	WarmingUpTime=0;
   	CurFTime=0;
   	NextFTime=0;
   	    
	sRamDArry[ExtCmdFlrONOFF0]=0xff;
	sRamDArry[ExtCmdFlrONOFF1]=0xff;
	sRamDArry[ExtCmdFlrONOFF2]=0xff;
	sRamDArry[ExtCmdFlrONOFF3]=0xff;

	sRamDArry[mMostLongDst]= 0x00;
	sRamDArry[mStartFloor] = cF_START_FLOOR;
//	sRamDArry[mTopFloor]   = cF_TOPFLR;

	CurDoorSel(MAIN_DOOR);		                   

    while(WarmingUpTime < 10)   asm("CLRWDT");
     
    if(RUN_MODE == IO_INVERTER) FindCurFloor();

    C1Loop=0;
    C2Loop=0;

    do{
        AddressRead();
        MyGroupAddr=0;

        IO_Check();                                
        SerialCheck();
        Serial2Check();

        if(C1Loop<65500)  Can1Check();
        if(C2Loop<65500)  Can2Check();

        asm("CLRWDT");
   	}while(1);                                  
}






void _ISR _T1Interrupt(void)
{
    if( _T1IF ){

        _T1IF = 0 ;
        TMR1=0;

        if(EepTime<50)    EepTime++;
  
        I_EMG_Cht++;
        I_FS0_Cht++;
        I_GR_Cht++;
        I_SU1_Cht++;
        I_X_0_Cht++;
        I_FIRE_Cht++;

        C1Time++;
        C2Time++;    

        if(IN_OP_E){   	
            DoorOpenOnTime=0;
        }
        else{
            if(DoorOpenOnTime<250){	
                DoorOpenOnTime++;
            }			
        }

	 
        SerialTime2++;
  
        SerialTime++;  
        if(SerialTime>10){
            TimeOutBd++;
            SerialTime=0;
        }
   

        if(bOnLuLd){
            if(LuLdTime < 50000)	LuLdTime++;
        }		
        else        LuLdTime=0;

        if(CarStopTime < 250)  CarStopTime++;        

	
        msec10++;
        if(msec10 > 100){
            msec10=0;
            OUT_RUN = !OUT_RUN;

            if(CurPulse>BefCurPulse){
                PulsePer100Msec=CurPulse-BefCurPulse;    
            }
            else{
                PulsePer100Msec=BefCurPulse-CurPulse;    
            }
            BefCurPulse=CurPulse;
            
            TmpMmPerMin=GET_LONG(MPM_VARIABLE);
            CurMeterPerMin=(PulsePer100Msec * TmpMmPerMin);
            CurMeterPerMin=(CurMeterPerMin/(unsigned long)1000000);


            if(CarOnceStopTime < 250)  CarOnceStopTime++;        

            if(PowerFailTime<250)   PowerFailTime++;

            if(!bMoveCar)  CounterTime=0;
            else{
                if(CounterTime < 250)  CounterTime++;
            }  

            if(LightTime<250)   LightTime++;


            FhmLoaderTime++;
            CurFTime++;
            NextFTime++;
            errtime++;
            DoorCloseTime++;
            DoorOpenTime++;
            NextFloorTime++;     
            FanTime++;  
            UpBttonTime++;
            DnBttonTime++;   
            SirenTime++;   		
            SerialLoopMaxTime++;
       
            if(FhmTime<100) FhmTime++;


            if(IN_UND)      VoiceTime++;
            else		    VoiceTime=0;

		
            if(IN_HL_D || IN_CL_E){
                DoorCloseOnTime=0;
            }
            else{
                if(DoorCloseOnTime<250){
                    DoorCloseOnTime++;
	            }			
            }	     


            if(WarmingUpTime < 110) WarmingUpTime++;     


            sec1++;
            if(sec1 >= 10){
                sec1=0;
                if(!bMoveCar && bAuto &&  !bUpWard && !bDnWard && bDoorCloseOk){
                    if(AutoNoMoveTime<60000)    AutoNoMoveTime++;
                }
                else           AutoNoMoveTime=0; 
            }

            MinuteTime++;
            if(MinuteTime>=600){
                MinuteTime=0;        
                FixFlrTimeCnt++;
            }        

            if(bManualStop){
                if(ManualStopTime < 20)  ManualStopTime++;
            }
            else	ManualStopTime=0;


            if(bFR2Start && (sRamDArry[mFireSeq]==FIRE_THREE)){
                if(RestartTime<60)  RestartTime++;
            }
            else{
                RestartTime=0;
            }
        }      
    }
}




void _ISR _OscillatorFail(void)
{

    INTCON1bits.OSCFAIL=0;

    CarAllStopCmd();
   	OUT_ON=0;
    OUT_ON=0;
    OutData();
}


void _ISR _AddressError(void)
{   

    INTCON1bits.ADDRERR=0;


    CarAllStopCmd();

   	OUT_ON=0;
    OUT_ON=0;
    OutData();
}


void _ISR _StackError(void)
{   

    CarAllStopCmd();

   	OUT_ON=0;
   	OUT_ON=0;
    OutData();

    INTCON1bits.STKERR=0;

}




void _ISR _MathError(void)
{   
    INTCON1bits.MATHERR=0;

    CarAllStopCmd();

   	OUT_ON=0;
   	OUT_ON=0;
    OutData();

}



void _ISR _LVDInterrupt(void)
{
    unsigned int i;


    if(RUN_MODE == IO_INVERTER){
        if(!bSaveFlash){
            i=(unsigned int)sRamDArry[mcurfloor];
            EEPROM_Write_Word(e_CurFloor,i);

            i=(unsigned int)CurPulse;
            EEPROM_Write_Word(e_CurPulse,i);

            i=(unsigned int)(CurPulse >> 16);
            EEPROM_Write_Word(e_CurPulse+2,i);
        
            bSaveFlash=1;
        }
    }

    CarAllStopCmd();

    OUT_ON=0;
    OUT_ON=0;
    OutData();

    CarAllStopCmd();

    OUT_ON=0;
    OUT_ON=0;

    OutData();

    LVDIF=0;

}




void _ISR _DefaultInterrupt(void)
{   
    unsigned int i;

    if(RUN_MODE == IO_INVERTER){
        if(!bSaveFlash){   
            i=(unsigned int)sRamDArry[mcurfloor];
            EEPROM_Write_Word(e_CurFloor,i);

            i=(unsigned int)CurPulse;
            EEPROM_Write_Word(e_CurPulse,i);

            i=(unsigned int)(CurPulse >> 16);
            EEPROM_Write_Word(e_CurPulse+2,i);
        
            bSaveFlash=1;
        }
    }


    CarAllStopCmd();

   	OUT_ON=0;
   	OUT_ON=0;
    OutData();

/*
    if(RUN_MODE == IO_INVERTER){
        i=(unsigned int)CurPulse;
        EEPROM_Write_Word(e_CurPulse,i);

        i=(unsigned int)(CurPulse >> 16);
        EEPROM_Write_Word(e_CurPulse+2,i);
    }
*/

    CarAllStopCmd();

   	OUT_ON=0;
   	OUT_ON=0;
    OutData();
    CarAllStopCmd();

   	OUT_ON=0;
   	OUT_ON=0;
    OutData();

}





