
/*
//Earthquake  routine
//bsEarthquake 
//bBefbsEarthquake
//bSlaveEarthquake
//unsigned int  __attribute__((section(".usercode")))   EarthquakeCheck(void)
//ButtonClrCheck();   
*/


//door open wait
//over heat
//door select(running open)
//handok gbr

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



_FOSC(CSW_FSCM_OFF & XT_PLL8 & 0xc30f);
_FWDT(WDT_ON & WDTPSA_64 & WDTPSB_1 & 0x803f);
//_FWDT(WDT_OFF & WDTPSA_64 & WDTPSB_1 & 0x803f);

_FBORPOR(PBOR_ON & BORV_20 & PWRT_64 & MCLR_EN & 0x87b3);
_FGS(0x0007);

//_FGS(CODE_PROT_OFF & 0x0003);
//_FGS(0x0004);

/*
#define _CONFIG4(x) __attribute__((section("__CONFIG4.sec,x"))) int _CONFIG4 = (x);
#define _CONFIG5(x) __attribute__((section("__CONFIG5.sec,x"))) int _CONFIG5 = (x);

_CONFIG4(0x0000);
_CONFIG5(0x0000);
*/


/*
extern void   DspFloorSet(void);
extern void   CarStopCmd(void);
extern void   CarUpStartCmd(void);
extern void   CarDnStartCmd(void);
extern void   CarCurFloorRead(void);
extern void   InverterErrorCheck(void);
extern void   ManualHomeSpeedCmd(void);
*/



extern void	Initialize_DS1302(void);
extern void disp_clk_regs(void);
extern void	FireKeyCheck(void);
extern void erase_flash_row(unsigned int);
extern void program_flash(unsigned int, unsigned int);


UserDataType    ButtonCmpBuf[4]={0,0,0,0};
UserDataType    YourKey0[4]={0,0,0,0};
UserDataType    YourKey1[4]={0,0,0,0};
UserDataType    YourKey2[4]={0,0,0,0};
UserDataType    YourKey3[4]={0,0,0,0};
UserDataType    BaggageFlrOnOff[4]={0xff,0xff,0xff,0xff};
UserDataType    errbd[12]={0};
UserDataType    Olderrbd[12]={0};
UserDataType    LadderBuf[16]={0};                         
UserDataType    LadderData[16]={0};                           
UserDataType    sRamDArry[END_SRAM]={0};     
UserDataType    BdErrCntSeq[ABS_ADDRESS]={0};
UserDataType    BDid[ABS_ADDRESS]={0};
UserDataType    eDArry[E_END]={0};      
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

//UserDataType    eMvCounterCnt=0;
//UserDataType    OpenOutOffTime=0;        

UserDataType    CloseOutOffTime=0;        
UserDataType    VoiceTime=0;        
UserDataType    BellTime=0;        
UserDataType    FhmLoaderTime=0;        
UserDataType    AccTimer=0;        

//UserDataType    RstTime=0;
        
UserDataType    UpBttonTime=0;
UserDataType    DnBttonTime=0;
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
UserDataType    RelevelTime=0;
UserDataType    FireBaseFloor=0;
UserDataType    CurSpeed=0;
UserDataType    OriginalHighFlr=0;
UserDataType    OriginalLowFlr=0;
UserDataType    CountDn=0;
UserDataType    CountUp=0;
UserDataType    UseBaseTime=0;
UserDataType    PowerOnTime=0;
UserDataType    NewDoorSelect=0;
UserDataType    CurDoorSelect=0;
UserDataType    SaveMoveCounter=0;
////////////////UserDataType    LuLdCounter=0;


UserDataType    LuLdErrNm=0;
UserDataType    LuLdSeqPt=0;
UserDataType    LuLdSeqMinCnt=0;
UserDataType    LuLdSeq[5];

UserDataType    CrtMoveFlr;


UserDataType    EncoderReloadTime;     


UserDataType    NotRecoveryData;     


unsigned	int    	    NextFloorTime=0;
unsigned	int     	MinuteTime=0;
unsigned	int   	    LuLdTime=0;
//unsigned	int   	    LuOrLdOnTime=0;
unsigned	int   	    CounterTime=0;
unsigned	int   	    CounterChkTime=0;
unsigned	int    	    DoorOpenTime=0;
unsigned	int    	    LightTime=0;
unsigned	int    	    AutoNoMoveTime=0;
unsigned	int    	    SolTimer=0;
unsigned	int    	    SolWaitTimer=0;
unsigned	int    	    ExIOTimer=0;


unsigned	int    	    BreakTime=0;
unsigned	int    	    HuntingTimer=0;
unsigned	int    	    HuntingCnter=0;


//unsigned	int    	    zz=0;




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
UserDataType    Etc3Bit=0;
UserDataType    PC1Bit=0;
UserDataType    StateBit0=0;
UserDataType    StateBit1=0;   
UserDataType    StateBit2=0;
UserDataType    StateBit3=0;   
UserDataType    StateBit4=0;   
UserDataType    StateBit5=0;   
UserDataType    StateBit6=0;   
UserDataType    Vip_Floor=0;   


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
UserDataType    LadderKeyTime=0;
UserDataType    ElevStopTime=0;
UserDataType    ElevMoveTime=0;
UserDataType    MyGroupAddr;
UserDataType    MyLocalAddr;

UserDataType    CarBdButtonFlr=0;

//UserDataType    MyNc_Addr;
//UserDataType    MyLowDip;



UserDataType    SegData0;
UserDataType    SegData1;
UserDataType    SegData2;
UserDataType    SegSel;
UserDataType    LadderTime;

UserDataType    SegError;
UserDataType    ClrCnt=0;
UserDataType    SaveVerify=0;

UserDataType	lu_ld_state;
UserDataType	bef_lu_ld_state;
UserDataType	DoorJumperNm;
UserDataType	NoStart=0;
		
///////////////
//20005


UserDataType    EmgByte;
UserDataType    Su1Byte;
UserDataType    GrByte;
UserDataType    FireByte;
UserDataType    Fs_Byte;
UserDataType    X0Byte;

UserDataType    BefEmgByte;
UserDataType    BefSu1Byte;
UserDataType    BefGrByte;
UserDataType    BefFireByte;
UserDataType    BefFs_Byte;
UserDataType    BefX0Byte;



UserDataType    EmgTime;
UserDataType    PrkTime;
UserDataType    AtTime;
UserDataType    UbTime;
UserDataType    DbTime;
UserDataType    OlsTime;
UserDataType    GsTime;
UserDataType    DsTime;

UserDataType    Su1Time;
UserDataType    Sd1Time;
UserDataType    SftTime;
UserDataType    OvlTime;
UserDataType    UlsTime;
UserDataType    DlsTime;
UserDataType    LuTime;
UserDataType    LdTime;

UserDataType    RgTime;
UserDataType    BatTime;
UserDataType    PassTime;
UserDataType    FireTime;
UserDataType    WaterTime;
UserDataType    FullTime;
UserDataType    MmTime;
UserDataType    FhmInTime;

UserDataType    Fr1Time;
UserDataType    Fr2Time;
UserDataType    Gs2Time;
UserDataType    Ds2Time;
UserDataType    Su2Time;
UserDataType    Sd2Time;
//UserDataType    Su3Time;
UserDataType    BmTime;
UserDataType    InvTime;

UserDataType    X0Time;
UserDataType    X1Time;
UserDataType    X2Time;
UserDataType    X3Time;
UserDataType    X4Time;
UserDataType    X5Time;
UserDataType    X6Time;
UserDataType    X7Time;


UserDataType    Fs0Time;
UserDataType    Fs1Time;
UserDataType    Fs2Time;
UserDataType    Fs3Time;
UserDataType    Fs4Time;
UserDataType    DerTime;
UserDataType    FidTime;
UserDataType    UndTime;

///////////////
//20005

UserDataType    LoopTime=0;


UserDataType    RstTime=0;
UserDataType    InvErrTime=0;
UserDataType    RstCnt=0;

UserDataType    ErrChkNm=0;


UserDataType    HibSet[10]={0,0,0,0,0,0,0,0,0,0};

UserDataType    TmpBuzor;   
UserDataType    ExtKeyCnt=0;

UserDataType    CmdFixFlrTime=0;


unsigned long 	BefCurEncoderPulse=0;
unsigned long   TmpEncoderPulse=0;

unsigned long 	LevelEncoderPulse1,LevelEncoderPulse2,LevelEncoderPulse3;
unsigned long 	TestPulse1,LuLdEncoder,UpDnEncoder;




unsigned long  parameter_mirror[MAX_LONG_BUF]; // = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


long_field  FlashDspCharBuf[256]    __attribute__((aligned(256) , section(".auto_psv,r")));


//const unsigned int EncRate[] = {128,64,32,16};

const unsigned char DftFlrName[] = {"B7B6B5B4B3B2B10102030405060708091011121314151617181920212223242526272829303132"}; 

const unsigned char StatusMessage[][16]={
                                      "Inspection Stop ",      //000                               
                                      "Inverter  Error ",      //001                               
                                      "INV Floor Error ",      //002                               
                                      "Emergency Stop  ",      //003                               
                                      "GOV Error       ",      //004                               
                                      "Motor Overheat  ",      //005                                                                           
                                      "Slip Stop       ",      //006                               
                                      "ULS Stop        ",      //007                                                                     
                                      "DLS Stop        ",      //008                               
                                      "LuLd Off Stop   ",      //009
                                      "Next Floor Stop ",      //010
                                      "InPort Error    ",      //011
                                      "Hall Door Stop  ",      //012
                                      "Car Door  Stop  ",      //013
                                      "Relvel Error    ",      //014
                                      "No Encoder Pulse",      //015
                                      "Encoder A-B Err ",      //016
                                      "ElevSpeed Error ",      //017
                                      "Speed Port Error",      //018
                                      "No Use Speed    ",      //019
                                      "Min Dec Length  ",      //020
                                      "Flr Match Error ",      //021
                                      "System Error    ",      //022
                                      "Break Mgt Error ",      //023
                                      "Break On/Off Err",      //024
                                      "Sus Error       ",      //025
                                      "Sds Error       ",      //026
									  "LuLd ChangeError",      //027 
									  "Ld On Error	   ",      //028
									  "Ld Off Error    ",      //029
									  "Lu On Error     ",      //030
									  "Lu Off Error    ",      //031
									  "LuLd OnOff Error",      //032
                                      "CarDoor Jumper  ",      //033                                                                           
                                      "HallDoor Jumper ",      //034
                                      "CarHall Jumper  ",      //035
                                      "Earthquake      ",      //036
                                      "037             ",      //037
                                      "038             ",      //038
                                      "039             ",      //039
                                      "040             ",      //040
                                      "041             ",      //041
                                      "042             ",      //042
                                      "FHM_Error       ",      //043
                                      "No Hall Door Sw ",      //044
                                      "No Close End    ",      //045
                                      "Over Load Stop  ",      //046
                                      "Parking Mode    ",      //047
                                      "   Fire         ",      //048
                                      "Water_Sensing   ",      //049                                       
                                      "No Open End     ",      //050
                                      "VIP Drive       ",      //051                                     
                                      "FHM_Mode        ",      //052                                     
                                      "Manual Up       ",      //053
                                      "Manual Dn       ",      //054
                                      "Manual Mode     ",      //055
                                      "Safety Open     ",      //056
                                      "Open Door       ",      //057
                                      "Close Door      ",      //058                                     
                                      "Auto Up         ",      //059                                     
                                      "Auto Dn         ",      //060                                     
                                      "Slow Speed      ",      //061
                                      "Wait LuLd       ",      //062
                                      "Auto Stop       ",      //063
                                      "Wait... Home !  ",      //064
                                      "Auto Ready      ",      //065
                                    };                                       



/*******************************************************
   manual play and record
*******************************************************/





//    unsigned long xxx;

void  __attribute__((section(".usercode"))) flash_write(unsigned int pt)
{

    unsigned int write_verify,y;
    unsigned long src_data,target_data;

	if((SaveVerify == 0x55) &&  (bMoveCar==0)){

	    asm("CLRWDT");
	
	    DISABLE_INTERRUPTS;
	
	    do{
	        asm("CLRWDT");
	
	        write_verify=0;
	
	    	// Erase the 32 location row of flash
	    	erase_flash_row((unsigned int)&FlashDspCharBuf[pt]);
	    	// Write the 32 parameters back 
	    	program_flash((unsigned int)&FlashDspCharBuf[pt],(unsigned int)&parameter_mirror[0]);
	        
	        for(y=0;y<16;y++){
	            target_data=FlashDspCharBuf[pt+y].long_data;    
	            src_data=parameter_mirror[y];  
	
	            if(src_data != target_data){  
	                write_verify=1;
	                break;
	            }
	        }                        
	    }while(write_verify);
	
	
	    ENABLE_INTERRUPTS;
	}
    asm("CLRWDT");
}








void  __attribute__((section(".usercode"))) SaveFloorCnt(void)
{
    unsigned int i;

    flash_write(FLR_01_PULSE);
    for(i=0;i<16;i++)    parameter_mirror[i] = parameter_mirror[i+16];
    flash_write(FLR_17_PULSE);
}                                                                     


#ifndef	TEST_SIMULATION
void  __attribute__((section(".usercode"))) CaluDecreasePulseCommon(unsigned int i)
{
    unsigned long rpm,mpm,encoder_pulse,mm_per_pulse,dec_mm_rpm,tmp_dec_mm_rpm,tmp_dec_pulse,tmp_value;

    mm_per_pulse=parameter_mirror[MM_PULSE-ENCODER_PULSE];


    dec_mm_rpm     =parameter_mirror[(DEC_LENGTH_30 + i) - ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[(DEC_PULSE_30 + i) - ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[ (MIN_DEC_PULSE_30 + i) - ENCODER_PULSE]=tmp_dec_pulse;

}
#endif



void  __attribute__((section(".usercode"))) CaluDecreasePulse(void)
{

#ifndef	TEST_SIMULATION

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


   	mm_per_pulse    = (mm_per_pulse / (unsigned long)4);
    parameter_mirror[MM_PULSE-ENCODER_PULSE]     = mm_per_pulse;
    parameter_mirror[MPM_VARIABLE-ENCODER_PULSE] = (mm_per_pulse * (unsigned long)600);


///////////////////////////////////////
	CaluDecreasePulseCommon(0);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_30-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_30-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_30 - ENCODER_PULSE]=tmp_dec_pulse;
*/
    
/////////////////////
	CaluDecreasePulseCommon(1);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_45-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_45-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_45 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(2);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_60-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_60-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_60 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(3);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_90-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_90-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_90 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(4);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_105-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_105-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_105 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(5);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_120-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_120-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_120 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(6);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_150-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_150-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_150 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(7);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_180-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_180-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_180 - ENCODER_PULSE]=tmp_dec_pulse;
*/
/////////////////////
	CaluDecreasePulseCommon(8);
/*
    dec_mm_rpm     =parameter_mirror[DEC_LENGTH_210-ENCODER_PULSE];
    tmp_dec_mm_rpm =(dec_mm_rpm * 10000); 
    tmp_dec_pulse  = (tmp_dec_mm_rpm/mm_per_pulse);
    parameter_mirror[DEC_PULSE_210-ENCODER_PULSE]=tmp_dec_pulse;

    tmp_value      = (tmp_dec_pulse/2);
    tmp_dec_pulse  = (tmp_dec_pulse << 1);
    parameter_mirror[MIN_DEC_PULSE_210 - ENCODER_PULSE]=tmp_dec_pulse;
*/

	SaveVerify = 0x55;

    flash_write(ENCODER_PULSE);
    for(i=0;i<16;i++)   parameter_mirror[i]=parameter_mirror[i+16];
    flash_write(ENCODER_PULSE + 16);

	SaveVerify = 0x0;

#endif
}                                                                     



void  __attribute__((section(".usercode"))) DefaultEncoderRpmMpm(void)
{

    unsigned int i;
    unsigned long rpm,mpm,encoder_pulse,mm_per_pulse,dec_mm_rpm,tmp_dec_mm_rpm,tmp_dec_pulse,tmp_value;

    for(i=0;i<32;i++){
        parameter_mirror[i]=GET_LONG(ENCODER_PULSE+i);
    }    

    parameter_mirror[MPM-ENCODER_PULSE]             = SET_ELEV_SPEED_PER_MIM; //m/min
    parameter_mirror[ENCODER_PULSE-ENCODER_PULSE]   = SET_ENCODER_PULSE;      //pulse/rotate
    parameter_mirror[RPM-ENCODER_PULSE]             = SET_MOTOR_RPM;          //r/min

    parameter_mirror[DEC_LENGTH_30 -ENCODER_PULSE]  = SPEED_30_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_45 -ENCODER_PULSE]  = SPEED_45_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_60 -ENCODER_PULSE]  = SPEED_60_DEC_LENGTH;
    parameter_mirror[DEC_LENGTH_90 -ENCODER_PULSE]  = SPEED_90_DEC_LENGTH;
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

    i=((pt/64) * 16);

    flash_write(i);


/*
    asm("CLRWDT");

    i=((pt/64) * 16);


    DISABLE_INTERRUPTS;

	// Erase the 32 location row of flash
	erase_flash_row((unsigned int)&FlashDspCharBuf[i]);
	// Write the 32 parameters back 
	program_flash((unsigned int)&FlashDspCharBuf[i],(unsigned int)&parameter_mirror[0]);

    ENABLE_INTERRUPTS;

    asm("CLRWDT");
*/

}







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






UserDataType  __attribute__((section(".usercode"))) VersionCheck(void)
{
    UserDataType    i;

    i=0;
    do{
        i++;
        if(i>10)    return(i);  
    }while((cF_VER0 != VERSION_0) || (cF_VER1 != VERSION_1) || (cF_VER2 != VERSION_2));

    return(0);
}


void __attribute__((section(".usercode")))  MvCounter(void)
{
	UserDataType i,fault;

	long_field	m_data;  

	fault=0;

	MoveCounterx++;
	SaveMoveCounter++;

	if(SaveMoveCounter >= 10){

		m_data.long_data=MoveCounterx;
		
	    for(i=0;i<4;i++){
	        if(!EEPROM_write_Ready() && !bMoveCar){
	            if(EEPROM_Write_Byte(e_xx+i,m_data.byte[i]))	fault=1;                 
	        }
			else	fault=1;		
	    }
	
		if(fault == 0)	SaveMoveCounter=0;
	}	
}


UserDataType  __attribute__((section(".usercode"))) MoveCounterReadInit(void)
{
    LocalType i;

	MoveCounterx=0x0;

    i=EEPROM_Read_Word(e_xx+2);

    MoveCounterx=i;
    MoveCounterx=((MoveCounterx << 16) & 0xffff0000);  
    i=EEPROM_Read_Word(e_xx);

    MoveCounterx=(MoveCounterx | (unsigned long)i); 

}


/*
UserDataType  __attribute__((section(".usercode"))) OnOffFlrResetting(void)
{
    LocalType  x0,x1,x2,x3,bufbit,i;
    LocalType  y0,y1,y2,y3;
	
	x0=0;
	x1=0;
	x2=0;
	x3=0;
	bufbit=0x01;

	for(i=0;i<= cF_TOPFLR;i++){		
		if(i<8)			x0=(x0 | bufbit);
		else if(i<16)	x1=(x1 | bufbit);
		else if(i<24)	x2=(x2 | bufbit);
		else if(i<32)	x3=(x3 | bufbit);

		bufbit=(bufbit << 1);
		if(bufbit > 0x80)	bufbit=0x01;
	}
	
//	y0=cF_NONSERVICE0;
	y1=cF_NONSERVICE1;
	y2=cF_NONSERVICE2;
	y3=cF_NONSERVICE3;


	if((x0 == y0) && ( x1 == y1) &&  ( x2 == y2) && ( x3 == y3))	return(0);		

	x0=(x0 & y0);
	x1=(x1 & y1);
	x2=(x2 & y2);
	x3=(x3 & y3);

	SaveVerify = 0x55;
	
    GetFlashDataToBufRam(F_BLOCK1);

    b_LdTmpBufRam(F_NonService0)    = x0;
    b_LdTmpBufRam(F_NonService1)    = x1;
    b_LdTmpBufRam(F_NonService2)    = x2;
    b_LdTmpBufRam(F_NonService3)    = x3;

    flash_write_DspChar(F_BLOCK1);

	SaveVerify = 0x0;

    return(0);
}
*/


unsigned int  __attribute__((section(".usercode"))) PcCmdSaveChk(void)
{
	unsigned char i,j;

	if(bMoveCar)	return(0);



	if((unsigned char)CmdFixFlrTime != cF_FIXFLOORTIME){
		SaveVerify=0x55;

        GetFlashDataToBufRam(F_BLOCK1);
        b_LdTmpBufRam(F_FixFloorTime)   = (unsigned char)(CmdFixFlrTime);
        flash_write_DspChar(F_BLOCK1);

		SaveVerify=0;

	}


	if( (cF_NONSERVICE0 != sRamDArry[ExtCmdFlrONOFF0]) || (cF_NONSERVICE1 != sRamDArry[ExtCmdFlrONOFF1]) || (cF_NONSERVICE2 != sRamDArry[ExtCmdFlrONOFF2]) || (cF_NONSERVICE3 != sRamDArry[ExtCmdFlrONOFF3])){
		SaveVerify=0x55;

        GetFlashDataToBufRam(F_BLOCK1);

        b_LdTmpBufRam(F_NonService0)    = sRamDArry[ExtCmdFlrONOFF0];
        b_LdTmpBufRam(F_NonService1)    = sRamDArry[ExtCmdFlrONOFF1];
        b_LdTmpBufRam(F_NonService2)    = sRamDArry[ExtCmdFlrONOFF2];
        b_LdTmpBufRam(F_NonService3)    = sRamDArry[ExtCmdFlrONOFF3];

        flash_write_DspChar(F_BLOCK1);

		SaveVerify=0;
	}


	i=0;
	j=0;
	if(bPC_FAMILY)		i=1;
	if(FamilyService)	j=1;

	if(i != j){
		SaveVerify=0x55;
        GetFlashDataToBufRam(F_BLOCK1);
		if(bPC_FAMILY)	bit_LdTmpBufRamSet(F_OnOff2,bFamilyService    	% 8);
		else			bit_LdTmpBufRamReset(F_OnOff2,bFamilyService    % 8);
        flash_write_DspChar(F_BLOCK1);
		SaveVerify=0;
	}

	return(0);
}



UserDataType  __attribute__((section(".usercode"))) ReadInitSetupData(void)
{

    LocalType  i,j;
 

	MoveCounterReadInit();

    for(i=0;i<ERR_SAVE_SIZE;i++){
        eDArry[eSysErCnt+i]=0x0;         
   	}

    bSaveErrCnt=0;
    eDArry[eErrCntPt] = EEPROM_Read_Byte(eErrCntPt);

//    if(eDArry[eErrCntPt] > ((ERR_SAVE_CNT+1) * 10)){
    if(eDArry[eErrCntPt] > ((ERR_SAVE_CNT+1) * ERR_SAVE_WIDE)){
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


    
    if(VersionCheck()){
		SaveVerify = 0x55;


        b_LdTmpBufRam(F_TopFlr)         = Init_TopFlr;
        b_LdTmpBufRam(F_PrkFlr)         = Init_PrkFlr;
        b_LdTmpBufRam(F_OpWtTm)         = Init_OpWtTm;      
        b_LdTmpBufRam(F_OpTtTm)         = Init_OpTtTm;  
        b_LdTmpBufRam(F_DirTime)        = Init_DirTime;
        b_LdTmpBufRam(F_VoiceTime)      = Init_VoiceTime;
        b_LdTmpBufRam(F_BrkMgtTime)     = Init_BrkMgtTime;


        b_LdTmpBufRam(F_FixFloor)       = Init_FixFloor;
        b_LdTmpBufRam(F_OneStopFlr)     = Init_OneStopFlr;

        b_LdTmpBufRam(F_FireSafeFlr)    = Init_FireSafeFlr;
        b_LdTmpBufRam(F_X7SafeFlr)      = Init_X7SafeFlr;
        b_LdTmpBufRam(F_WaterSafeFlr)   = Init_WaterSafeFlr;

        b_LdTmpBufRam(F_KidsKeyCnt)     = Init_KidsKeyCnt;
        b_LdTmpBufRam(F_X6SafeFlr)      = Init_X6SafeFlr;
        b_LdTmpBufRam(F_X5SafeFlr)      = Init_X5SafeFlr;


        b_LdTmpBufRam(F_NonService0)    = Init_ALL_FF;
        b_LdTmpBufRam(F_NonService1)    = Init_ALL_FF;
        b_LdTmpBufRam(F_NonService2)    = Init_ALL_FF;
        b_LdTmpBufRam(F_NonService3)    = Init_ALL_FF;
                                                
                                                 //     7 ,      6,      5,        4,         3,        2,       1,     0
        b_LdTmpBufRam(F_NcNoBit0)       = Init_ALL_FF;  //                                                                     emg
        b_LdTmpBufRam(F_NcNoBit1)       = Init_ALL_FF;  //                                                                     su1
        b_LdTmpBufRam(F_NcNoBit2)       = Init_ALL_FF;  //                                                                     rg
        b_LdTmpBufRam(F_NcNoBit3)       = Init_ALL_FF;  //                                                                     fr1
        b_LdTmpBufRam(F_NcNoBit4)       = Init_ALL_FF;  //                                                                     x0
        b_LdTmpBufRam(F_NcNoBit5)       = Init_ALL_FF;  //                                                                     fs0
        b_LdTmpBufRam(F_NcNoBit6)       = Init_ALL_FF;  //                                                                     op
        b_LdTmpBufRam(F_NcNoBit7)       = Init_ALL_FF;  //                                                                     fan
        b_LdTmpBufRam(F_NcNoBit8)       = Init_ALL_FF;  //                                                                     up

        b_LdTmpBufRam(F_StartFloor)     = START_FLOOR;   


        bit_LdTmpBufRamSet  (F_OnOff0,bFhmOnOff             % 8);
        bit_LdTmpBufRamSet  (F_OnOff0,bDoorJumperOff        % 8); 
        bit_LdTmpBufRamReset(F_OnOff0,bEncoderPhase         % 8);
        bit_LdTmpBufRamSet  (F_OnOff0,bWardPriority         % 8);
        bit_LdTmpBufRamReset(F_OnOff0,bNonStop              % 8);
        bit_LdTmpBufRamSet  (F_OnOff0,bOpenTotalOnOff       % 8);
        bit_LdTmpBufRamSet  (F_OnOff0,bCloseTotalOnOff      % 8);
        bit_LdTmpBufRamSet  (F_OnOff0,bOpenWaitToTalOnOff   % 8);

        bit_LdTmpBufRamSet  (F_OnOff1,bCarDoor1Use      	% 8);
        bit_LdTmpBufRamReset(F_OnOff1,bCarDoor2Use      	% 8);
        bit_LdTmpBufRamSet  (F_OnOff1,bHoleDoor1Use     	% 8);
        bit_LdTmpBufRamReset(F_OnOff1,bHoleDoor2Use     	% 8);
        bit_LdTmpBufRamReset(F_OnOff1,bSubSafety        	% 8);
        bit_LdTmpBufRamReset(F_OnOff1,bBrkMgtUse        	% 8);
        bit_LdTmpBufRamSet  (F_OnOff1,bEncoderUse       	% 8);
        bit_LdTmpBufRamReset(F_OnOff1,bRelevelOnOff     	% 8);

        bit_LdTmpBufRamSet  (F_OnOff2,bOilLopeTypeChk   	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bOnlyOneCall      	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bManualSusChk     	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bBrkOpenUse       	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bKidsKeyChkUse    	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bCarKeyFirstService  	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bFamilyService    	% 8);
        bit_LdTmpBufRamReset(F_OnOff2,bOpenOutSet    		% 8);


        bit_LdTmpBufRamReset(F_OnOff3,bSafetyValidLR    	% 8);
        bit_LdTmpBufRamReset(F_OnOff3,bFloorSel             % 8);
        bit_LdTmpBufRamReset(F_OnOff3,bRunOpenSetClear      % 8);
        bit_LdTmpBufRamSet(F_OnOff3,bManWorkingChk      	% 8);

        SWPAB   = 0;   


        b_LdTmpBufRam(F_FanTime)        = Init_FanTime;        //3 sec
        b_LdTmpBufRam(F_LightTime)      = Init_LightTime;       //99 min
        b_LdTmpBufRam(F_FixFloorTime)   = Init_FixFloorTime;
        b_LdTmpBufRam(F_NextFlrTime)    = Init_NextFlrTime;
        b_LdTmpBufRam(F_LuLdOffTime)    = Init_LuLdOffTime;
        b_LdTmpBufRam(F_ReOpTime)       = Init_ReOpTime;  
        b_LdTmpBufRam(F_OpClWaitTime)   = Init_OpClWTime;
        b_LdTmpBufRam(F_DrJmpChkTime)   = Init_DrJmpChkTime;

        b_LdTmpBufRam(F_StTm1)          = Init_StTm1;
        b_LdTmpBufRam(F_StTm2)          = Init_StTm2;
        b_LdTmpBufRam(F_StTm3)          = Init_StTm3;
        b_LdTmpBufRam(F_StTm4)          = Init_StTm4;
        b_LdTmpBufRam(F_StTm5)          = Init_StTm5;



        b_LdTmpBufRam(F_RunOffTime)      = Init_RunOff_Time;        
        b_LdTmpBufRam(F_Bk1OffTime)      = Init_Bk1Off_Time;
        b_LdTmpBufRam(F_Bk2OffTime)      = Init_Bk2Off_Time;
        b_LdTmpBufRam(F_UDOffTime)       = Init_UDOff_Time;
        b_LdTmpBufRam(F_P4OffTime)       = Init_P4Off_Time;


        b_LdTmpBufRam(F_SolOnTime)       = Init_SolOn_Time;        
        b_LdTmpBufRam(F_DoorWaitTime)    = Init_DoorWait_Time;



#ifdef  TEST_SIMULATION  
        b_LdTmpBufRam(F_TopFlr)         = 31;
        bit_LdTmpBufRamReset  (F_OnOff0,bDoorJumperOff        % 8); 
        bit_LdTmpBufRamReset(F_OnOff3,bManWorkingChk      % 8);
#endif

        flash_write_DspChar(F_TopFlr);


/////////////////////////////////////////////////////////
		for(i=0;i<32;i++){
        	b_LdTmpBufRam(F_0506+i)           = DISABLE_FLR;
		}

        flash_write_DspChar(F_BLOCK3);
//////////////////////////////////////////////////////////////
#ifdef  TEST_SIMULATION 
#ifdef	KTL
        b_LdTmpBufRam(EMG_PORT)         =SILK_EMG   | BIT_NORMAL_OPEN;          //1     64
        b_LdTmpBufRam(PRK_PORT)         =SILK_PRK   | 0x00;          			//1     
        b_LdTmpBufRam(AUTO_PORT)        =SILK_AUTO  | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(U_B_PORT)         =SILK_U_B   | 0x80;          			//1             
        b_LdTmpBufRam(D_B_PORT)         =SILK_D_B   | 0x80;          			//1     65
        b_LdTmpBufRam(OLS_PORT)         =SILK_OLS   | 0x80;          			//1     
        b_LdTmpBufRam(GS_PORT)          =SILK_GS    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(DS_PORT)          =SILK_DS    | BIT_NORMAL_OPEN;           //1             
#else 
        b_LdTmpBufRam(EMG_PORT)         =SILK_EMG   | 0x00;          //1     64
        b_LdTmpBufRam(PRK_PORT)         =SILK_PRK   | 0x00;          //1     
        b_LdTmpBufRam(AUTO_PORT)        =SILK_AUTO  | 0x00;          //1     
        b_LdTmpBufRam(U_B_PORT)         =SILK_U_B   | 0x80;          //1             
        b_LdTmpBufRam(D_B_PORT)         =SILK_D_B   | 0x80;          //1     65
        b_LdTmpBufRam(OLS_PORT)         =SILK_OLS   | 0x80;          //1     
        b_LdTmpBufRam(GS_PORT)          =SILK_GS    | 0x00;           //1     
        b_LdTmpBufRam(DS_PORT)          =SILK_DS    | 0x00;           //1             
#endif                                                                    
        b_LdTmpBufRam(SU1_PORT)         =SILK_SU1   | 0x80;          //1     66
        b_LdTmpBufRam(SD1_PORT)         =SILK_SD1   | 0x80;          //1     
        b_LdTmpBufRam(SFT_PORT)         =SILK_SFT   | 0x00;          //1     
        b_LdTmpBufRam(OVL_PORT)         =SILK_OVL   | 0x00;          //1             
        b_LdTmpBufRam(ULS_PORT)         =SILK_ULS   | 0x00;          //1     67
        b_LdTmpBufRam(DLS_PORT)         =SILK_DLS   | 0x00;          //1     
        b_LdTmpBufRam(LU_PORT)          =SILK_LU    | 0x00;           //1     
        b_LdTmpBufRam(LD_PORT)          =SILK_LD    | 0x00;           //1             

        b_LdTmpBufRam(RG_PORT)          =SILK_GR    | 0x00;           //1     68
        b_LdTmpBufRam(BAT_PORT)         =SILK_BAT   | 0x80;          //1     
        b_LdTmpBufRam(PASS_PORT)        =SILK_PASS  | 0x80;         //1     
        b_LdTmpBufRam(FIRE_PORT)        =SILK_FIRE  | 0x80;         //1             
        b_LdTmpBufRam(WATER_PORT)       =NO_USE_IN  | 0x80;        //1     69
        b_LdTmpBufRam(FULL_PORT)        =SILK_FULL  | 0x80;         //1     
        b_LdTmpBufRam(MM_PORT)          =SILK_MM    | 0x80;          //1     
        b_LdTmpBufRam(FHM_PORT)         =SILK_FHM   | 0x80;          //1             

        b_LdTmpBufRam(FR1_PORT)         =SILK_FR1   | 0x80;          //1     70
        b_LdTmpBufRam(FR2_PORT)         =SILK_FR2   | 0x80;          //1     
        b_LdTmpBufRam(GS2_PORT)         =SILK_GS2   | 0x80;          //1     
        b_LdTmpBufRam(DS2_PORT)         =SILK_DS2   | 0x80;          //1             
        b_LdTmpBufRam(SU2_PORT)         =SILK_SU2   | 0x80;          //1     71
        b_LdTmpBufRam(SD2_PORT)         =SILK_SD2   | 0x80;          //1     
        b_LdTmpBufRam(BM_PORT)          =SILK_BM    | 0x80;          //1     
        b_LdTmpBufRam(INV_PORT)         =SILK_INV   | 0x80;          //1             

        b_LdTmpBufRam(X0_PORT)          =SILK_X0    | BIT_NORMAL_OPEN;           //1     72
        b_LdTmpBufRam(X1_PORT)          =SILK_X1    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X2_PORT)          =SILK_X2    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X3_PORT)          =SILK_X3    | BIT_NORMAL_OPEN;           //1             
        b_LdTmpBufRam(X4_PORT)          =SILK_X4    | BIT_NORMAL_OPEN;           //1     73
        b_LdTmpBufRam(X5_PORT)          =SILK_X5    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X6_PORT)          =SILK_X6    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X7_PORT)          =SILK_X7    | BIT_NORMAL_OPEN;           //1             

        b_LdTmpBufRam(FS0_PORT)         =SILK_FS0   | 0x80;          //1     74
        b_LdTmpBufRam(FS1_PORT)         =SILK_FS1   | 0x80;          //1     
        b_LdTmpBufRam(FS2_PORT)         =SILK_FS2   | 0x80;          //1     
        b_LdTmpBufRam(FS3_PORT)         =SILK_FS3   | 0x80;          //1             
        b_LdTmpBufRam(FS4_PORT)         =SILK_FS4   | 0x80;          //1     75
        b_LdTmpBufRam(DER_PORT)         =SILK_DER   | 0x80;          //1     
        b_LdTmpBufRam(FID_PORT)         =SILK_FID   | 0x80;          //1     
        b_LdTmpBufRam(UND_PORT)         =SILK_UND   | 0x80;          //1     
#else

        b_LdTmpBufRam(EMG_PORT)         =SILK_EMG   | BIT_NORMAL_OPEN;          //1     64
        b_LdTmpBufRam(PRK_PORT)         =SILK_PRK   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(AUTO_PORT)        =SILK_AUTO  | BIT_NORMAL_OPEN;         //1     
        b_LdTmpBufRam(U_B_PORT)         =SILK_U_B   | BIT_NORMAL_OPEN;          //1             
        b_LdTmpBufRam(D_B_PORT)         =SILK_D_B   | BIT_NORMAL_OPEN;          //1     65
        b_LdTmpBufRam(OLS_PORT)         =SILK_OLS   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(GS_PORT)          =SILK_GS    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(DS_PORT)          =SILK_DS    | BIT_NORMAL_OPEN;           //1             

        b_LdTmpBufRam(SU1_PORT)         =SILK_SU1   | BIT_NORMAL_OPEN;          //1     66
        b_LdTmpBufRam(SD1_PORT)         =SILK_SD1   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(SFT_PORT)         =SILK_SFT   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(OVL_PORT)         =SILK_OVL   | BIT_NORMAL_OPEN;          //1             
        b_LdTmpBufRam(ULS_PORT)         =SILK_ULS   | BIT_NORMAL_OPEN;          //1     67
        b_LdTmpBufRam(DLS_PORT)         =SILK_DLS   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(LU_PORT)          =SILK_LU    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(LD_PORT)          =SILK_LD    | BIT_NORMAL_OPEN;           //1             

        b_LdTmpBufRam(RG_PORT)          =SILK_GR    | BIT_NORMAL_OPEN;           //1     68
        b_LdTmpBufRam(BAT_PORT)         =SILK_BAT   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(PASS_PORT)        =SILK_PASS  | BIT_NORMAL_OPEN;         //1     
        b_LdTmpBufRam(FIRE_PORT)        =SILK_FIRE  | BIT_NORMAL_OPEN;         //1             
        b_LdTmpBufRam(WATER_PORT)       =SILK_WATER | BIT_NORMAL_OPEN;        //1     69
        b_LdTmpBufRam(FULL_PORT)        =SILK_FULL  | BIT_NORMAL_OPEN;         //1     
        b_LdTmpBufRam(MM_PORT)          =SILK_MM    | BIT_NORMAL_OPEN;         //1     
        b_LdTmpBufRam(FHM_PORT)         =SILK_FHM   | BIT_NORMAL_OPEN;          //1             

        b_LdTmpBufRam(FR1_PORT)         =SILK_FR1   | BIT_NORMAL_OPEN;          //1     70
        b_LdTmpBufRam(FR2_PORT)         =SILK_FR2   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(GS2_PORT)         =SILK_GS2   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(DS2_PORT)         =SILK_DS2   | BIT_NORMAL_OPEN;          //1             
        b_LdTmpBufRam(SU2_PORT)         =SILK_SU2   | BIT_NORMAL_OPEN;          //1     71
        b_LdTmpBufRam(SD2_PORT)         =SILK_SD2   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(BM_PORT)          =SILK_BM    | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(INV_PORT)         =SILK_INV   | BIT_NORMAL_OPEN;          //1             

        b_LdTmpBufRam(X0_PORT)          =SILK_X0    | BIT_NORMAL_OPEN;           //1     72
        b_LdTmpBufRam(X1_PORT)          =SILK_X1    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X2_PORT)          =SILK_X2    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X3_PORT)          =SILK_X3    | BIT_NORMAL_OPEN;           //1             
        b_LdTmpBufRam(X4_PORT)          =SILK_X4    | BIT_NORMAL_OPEN;           //1     73
        b_LdTmpBufRam(X5_PORT)          =SILK_X5    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X6_PORT)          =SILK_X6    | BIT_NORMAL_OPEN;           //1     
        b_LdTmpBufRam(X7_PORT)          =SILK_X7    | BIT_NORMAL_OPEN;           //1             

        b_LdTmpBufRam(FS0_PORT)         =SILK_FS0   | BIT_NORMAL_OPEN;          //1     74
        b_LdTmpBufRam(FS1_PORT)         =SILK_FS1   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(FS2_PORT)         =SILK_FS2   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(FS3_PORT)         =SILK_FS3   | BIT_NORMAL_OPEN;          //1             
        b_LdTmpBufRam(FS4_PORT)         =SILK_FS4   | BIT_NORMAL_OPEN;          //1     75
        b_LdTmpBufRam(DER_PORT)         =SILK_DER   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(FID_PORT)         =SILK_FID   | BIT_NORMAL_OPEN;          //1     
        b_LdTmpBufRam(UND_PORT)         =SILK_UND   | BIT_NORMAL_OPEN;          //1     

#endif

        b_LdTmpBufRam(F_SubDoorFlr1)    = Init_SubDoorFlr1;
        b_LdTmpBufRam(F_SubDoorFlr2)    = Init_SubDoorFlr2;
        b_LdTmpBufRam(F_SubDoorFlr3)    = Init_SubDoorFlr3;
        b_LdTmpBufRam(F_SubDoorFlr4)    = Init_SubDoorFlr4;
        b_LdTmpBufRam(F_SubDoorFlr5)    = Init_SubDoorFlr5;
        b_LdTmpBufRam(F_SubDoorFlr6)    = Init_SubDoorFlr6;
        b_LdTmpBufRam(F_SubDoorFlr7)    = Init_SubDoorFlr7;
        b_LdTmpBufRam(F_SubDoorFlr8)    = Init_SubDoorFlr8;


        flash_write_DspChar(EMG_PORT);

/////////////////////////////////////////////////////////

        b_LdTmpBufRam(FAN_PORT)         =SILK_FAN   | BIT_NORMAL_OPEN;
        b_LdTmpBufRam(LIT_PORT)         =SILK_LIGHT | BIT_NORMAL_OPEN;  //     
        b_LdTmpBufRam(BUZ_PORT)         =SILK_BUZ   | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(BELL_PORT)        =SILK_BELL  | BIT_NORMAL_OPEN;
        b_LdTmpBufRam(RST_PORT)         =SILK_RST   | BIT_NORMAL_OPEN;             
        b_LdTmpBufRam(ERR_PORT)         =SILK_ERR   | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(HOP_PORT)         =SILK_HOP   | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(HCL_PORT)         =SILK_HCL   | BIT_NORMAL_OPEN;

        b_LdTmpBufRam(OP_PORT)          =SILK_OP    | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(CL_PORT)          =SILK_CL    | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(S_OP_PORT)        =SILK_S_OP  | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(S_CL_PORT)        =SILK_S_CL  | BIT_NORMAL_OPEN;
        b_LdTmpBufRam(BK2_PORT)         =SILK_BK2   | BIT_NORMAL_OPEN;             
        b_LdTmpBufRam(D_S_PORT)         =SILK_D_S   | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(GBR_PORT)         =SILK_GBR   | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(BK1_PORT)         =SILK_BK1   | BIT_NORMAL_OPEN;

        b_LdTmpBufRam(UP_PORT)          =SILK_UP    | BIT_NORMAL_OPEN;
        b_LdTmpBufRam(DN_PORT)          =SILK_DN    | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(P1_PORT)          =SILK_P1    | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(P2_PORT)          =SILK_P2    | BIT_NORMAL_OPEN;             
        b_LdTmpBufRam(P3_PORT)          =SILK_P3    | BIT_NORMAL_OPEN;
        b_LdTmpBufRam(P4_PORT)          =SILK_P4    | BIT_NORMAL_OPEN;     
        b_LdTmpBufRam(DAC_PORT)         =SILK_DAC   | BIT_NORMAL_OPEN;     

        flash_write_DspChar(FAN_PORT);
////////////////////////////////////////////////


///////////////////////////////////////////////
        b_LdTmpBufRam(F_Ver0)           = VERSION_0;
        b_LdTmpBufRam(F_Ver1)           = VERSION_1;
        b_LdTmpBufRam(F_Ver2)           = VERSION_2;


        b_LdTmpBufRam(F_Bd_Id)          = (IO | MAN_USE);           

#ifdef  TEST_SIMULATION  
        b_LdTmpBufRam(F_Bd_Id)          = (LG | MAN_USE);           
#endif


        b_LdTmpBufRam(F_Passward0)      = '0';
        b_LdTmpBufRam(F_Passward1)      = '0';
        b_LdTmpBufRam(F_Passward2)      = '0';
        b_LdTmpBufRam(F_Passward3)      = '0';

        i_LdTmpBufRam(F_SerialNm10)     = 0;

        b_LdTmpBufRam(F_ErrStopCnt)     = 0xff;
        b_LdTmpBufRam(F_NormalDsp)      = 0x0;
        b_LdTmpBufRam(F_UserLamp1)      = 8;
        b_LdTmpBufRam(F_UserLamp2)      = 1;
        b_LdTmpBufRam(F_UserLamp3)      = 6;
        b_LdTmpBufRam(F_UserLamp4)      = 3;
        b_LdTmpBufRam(F_GroupNm)        = 0;
        b_LdTmpBufRam(F_LocalNm)        = 0;
        b_LdTmpBufRam(F_PcbType)        = 0;

//        b_LdTmpBufRam(F_EncoderRate)    = 1;
        i_LdTmpBufRam(F_StopPulse0)     = 1000;

        b_LdTmpBufRam(F_year)           = 0;
        b_LdTmpBufRam(F_month)          = 0;
        b_LdTmpBufRam(F_day)            = 0;

        b_LdTmpBufRam(F_Company)        = COMPANY;
        b_LdTmpBufRam(F_Airconadr)      = 0xc0;
///////////////////////////////////////////////
        //  P1  P2  P3  P4
        //  0   0   0   0           :NONE_USE_SPD  
        //  1   0   0   0           :P1
        //  0   1   0   0           :P2
        //  1   1   0   0           :P1P2
        //  0   0   1   0           :P3
        //  1   0   1   0           :P1P3
        //  0   1   1   0           :P2P3
        //  1   1   1   0           :P1P2P3
        //  0   0   0   1           :P4
        //  1   0   0   1           :P1P4
        //  0   1   0   1           :P2P4
        //  1   1   0   1           :P1P2P4
        //  0   0   1   1           :P3P4
        //  1   0   1   1           :P1P3P4
        //  0   1   1   1           :P2P3P4
        //  1   1   1   1           :P1P2P3P4

///////////////////////////////////////////////
        b_LdTmpBufRam(F_ManualSpeed)    = P1P2_SPD;                   
        b_LdTmpBufRam(F_BatterySpeed)   = NONE_USE_SPD;      
        b_LdTmpBufRam(F_DecreaseSpeed)  = P2_SPD;                    
        b_LdTmpBufRam(F_FhmSpeed)       = NONE_USE_SPD;     

        b_LdTmpBufRam(F_Etc1Speed)      = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Etc2Speed)      = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Speed30)        = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Speed45)        = P3_SPD;              

        b_LdTmpBufRam(F_Speed60)        = P1_SPD;                    
        b_LdTmpBufRam(F_Speed90)        = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Speed105)       = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Speed120)       = NONE_USE_SPD;     

        b_LdTmpBufRam(F_Speed150)       = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Speed180)       = NONE_USE_SPD;     
        b_LdTmpBufRam(F_Speed210)       = NONE_USE_SPD;    
        b_LdTmpBufRam(F_ElevSpeed)      = SPEED_60;
        b_LdTmpBufRam(F_LimitSpeed)     = SPEED_210;


        b_LdTmpBufRam(F_Su1Sd1_Velocity)= 90;      //mpm
        b_LdTmpBufRam(F_Su2Sd2_Velocity)= 90;      //mpm
        b_LdTmpBufRam(F_X0X1_Velocity)  = 210;     //mpm


        flash_write_DspChar(F_ManualSpeed);
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
		MoveCounterx=0;
		SaveMoveCounter=10;
		MvCounter();

           
   	    for(i=0;i<ERR_SAVE_SIZE;i++){
      	    eDArry[eSysErCnt+i]=0x0;         
            EEPROM_Write_Byte(eSysErCnt+i,0x0);
   	    }

	    sRamDArry[mBefErrCntPt]=0x0;
        eDArry[eErrCntPt]=0x0;
        bSaveErrCnt=0;


		NotRecoveryData=0;
	    EEPROM_Write_Word(e_GBR,NotRecoveryData);

		i=0;
		do{
			i++;
	       	PowerOnTime=0x0;
	       	EEPROM_Write_Word(e_PowerOnTime,(unsigned int)PowerOnTime);
			PowerOnTime=0x2;
			PowerOnTime=EEPROM_Read_Word(e_PowerOnTime);
			if(PowerOnTime == 0)	i = 20;
		}while(i < 10);

	}  



   	if(cF_TOPFLR < 1 ){
        LadderBuf[C_SAVE_DATA]=1;
		SaveVerify = 0x55;
        F_SetupData_ReSet(F_TopFlr,1);
    }

   	if(cF_TOPFLR > 31 ){
        LadderBuf[C_SAVE_DATA]=31;
		SaveVerify = 0x55;
        F_SetupData_ReSet(F_TopFlr,1);
    }

   	if(cF_PRKFLR > cF_TOPFLR ){
        LadderBuf[C_SAVE_DATA]=0;
		SaveVerify = 0x55;
        F_SetupData_ReSet(F_PrkFlr,1);
    }


   	if(cF_OPWTTM > 9999 ){
        LadderBuf[C_SAVE_DATA]=0;
		SaveVerify = 0x55;
        F_SetupData_ReSet(F_OpWtTm,1);
    }

   	if(cF_OPTTTM > 9999 ){
        LadderBuf[C_SAVE_DATA]=0;
		SaveVerify = 0x55;
        F_SetupData_ReSet(F_OpTtTm,1);
    }




	SaveVerify = 0x0;

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

	else if(bsInvertErr){
		if(sRamDArry[mSysStatus] >= sInvertErr)   
		sRamDArry[mSysStatus]=sInvertErr;         
   	}

	else if(bsInvCurNext){
		if(sRamDArry[mSysStatus] >= sI_C_N_FLR)   
		sRamDArry[mSysStatus]=sI_C_N_FLR;         
   	}

	else if(bsEmergency){
		if(sRamDArry[mSysStatus] >= sEMERGENCY)   
		sRamDArry[mSysStatus]=sEMERGENCY;         
	}

	else if(bsLope){
		if(sRamDArry[mSysStatus] >= sLOPE_BRK)   
		sRamDArry[mSysStatus]=sLOPE_BRK;        
	}
   
	else if(bsSlip){
		if(sRamDArry[mSysStatus] >= sSLIP)   
		sRamDArry[mSysStatus]=sSLIP;       
	}

	else if(bsUls){
		if(sRamDArry[mSysStatus] >= sULS)   
		sRamDArry[mSysStatus]=sULS;            
	}
   
	else if(bsDls){
		if(sRamDArry[mSysStatus] >= sDLS)   
		sRamDArry[mSysStatus]=sDLS;            
	}
   
	else if(bRelevelErr){
		if(sRamDArry[mSysStatus] >= sRelevelError)   
		sRamDArry[mSysStatus]=sRelevelError;                       
	}

	else if(bsHdsRunOff){
		if(sRamDArry[mSysStatus] >= sHDS_RUN_OFF)   
		sRamDArry[mSysStatus]=sHDS_RUN_OFF;                       
	}
   
	else if(bsCleRunOff){
		if(sRamDArry[mSysStatus] >= sCLE_RUN_OFF)   
		sRamDArry[mSysStatus]=sCLE_RUN_OFF;                  
	}
   
	else if(bsHdsNoOn){
		if(sRamDArry[mSysStatus] > sHDS_NO_ON)   
		sRamDArry[mSysStatus]=sHDS_NO_ON;                        
	}
   
	else if(bsCleNoOn){
		if(sRamDArry[mSysStatus] > sCLE_NO_ON)   
		sRamDArry[mSysStatus]=sCLE_NO_ON;                        
	}
   
	else if(bsNextFloor){
		if(sRamDArry[mSysStatus] > sNEXT_FLOOR)   
		sRamDArry[mSysStatus] = sNEXT_FLOOR;               
	}

	else if(bsLuLdNoOff){
		if(sRamDArry[mSysStatus] > sLULD_NO_OFF)  
		sRamDArry[mSysStatus] = sLULD_NO_OFF;                         
	}

	else if(bMotor_Overheat){
		if(sRamDArry[mSysStatus] > sMOTOR_OVERHEAT)   
		sRamDArry[mSysStatus]=sMOTOR_OVERHEAT;      
	}   


	else if(bDoorJumper){
		if(sRamDArry[mSysStatus] >= sCarDoor_Jumper)   
		sRamDArry[mSysStatus]=(sCarDoor_Jumper + DoorJumperNm);       				
	} 
  
	else if(bEncoderErr){
		if(sRamDArry[mSysStatus] >= sEncoderErr)   
		sRamDArry[mSysStatus]=sEncoderErr;       				
	}   

	else if(bEncoderABErr){
		if(sRamDArry[mSysStatus] >= sEncoderABErr)   
		sRamDArry[mSysStatus]=sEncoderABErr;       				
	}   

	else if(bEqualFloorError){
		if(sRamDArry[mSysStatus] >= sEqualFloorError)   
		sRamDArry[mSysStatus]=sEqualFloorError;       				
	}   

	else if(bsBreakMgtOpen){
		if(sRamDArry[mSysStatus] >= sBreakMgtOpen)      
		sRamDArry[mSysStatus] = sBreakMgtOpen;       				
	} 

	else if(bsBreakOpen){
		if(sRamDArry[mSysStatus] >= sBreakOpen)         
		sRamDArry[mSysStatus] = sBreakOpen;       				
	} 
  
	else if(bsSusErr){
		if(sRamDArry[mSysStatus] >= sSusErr)      
		sRamDArry[mSysStatus] = sSusErr;       				
	}
   
	else if(bsSdsErr){
		if(sRamDArry[mSysStatus] >= sSdsErr)      
		sRamDArry[mSysStatus] = sSdsErr;       				
	}   


	else if(bsLuOrLdErr && (LuLdErrNm > 0)){
		if(sRamDArry[mSysStatus] >= (sLuOrLdErr0 + LuLdErrNm-1))   
		sRamDArry[mSysStatus]=(sLuOrLdErr0 + LuLdErrNm-1);        
	}   

	else if(bsEarthquake){
		if(sRamDArry[mSysStatus] >= sEarthquake)   
		sRamDArry[mSysStatus]=sEarthquake;        
	}   

	else if(NoStart){
		switch(NoStart){		
            case    1:
			    if(sRamDArry[mSysStatus] > sSpeedSetError)  
				sRamDArry[mSysStatus]=sSpeedSetError;      
                break;
            case    2:
			    if(sRamDArry[mSysStatus] > sSpeedPortError) 
				sRamDArry[mSysStatus]=sSpeedPortError;      
                break;
            case    3:
			    if(sRamDArry[mSysStatus] > sNoUseSpeed)     
				sRamDArry[mSysStatus]=sNoUseSpeed;      
                break;
            case    4:
			    if(sRamDArry[mSysStatus] > sMinLengthErr)   
				sRamDArry[mSysStatus]=sMinLengthErr;      
                break;
            default:
			    if(sRamDArry[mSysStatus] > sSystemErr)      
				sRamDArry[mSysStatus]=sSystemErr;      
                break;
		}
	}

    SegError=sRamDArry[mSysStatus];

}



UserDataType	__attribute__((section(".usercode"))) SaveEebuf(UserDataType  ErrName)
{
	LocalType i;

/*
	for(i=0;i<=eErrCntPt;){
    	if(eDArry[eSysErCnt + i + 3] == ErrName){
    		if(eDArry[eSysErCnt + i + 2] == sRamDArry[mcurfloor]){
    			if(eDArry[eSysErCnt + i + 5] == sRamDArry[Minuate]){
    				if(eDArry[eSysErCnt + i + 4] == sRamDArry[Hour]){
						return(0);
					}
				}
			}         
		}
		i=(i + ERR_SAVE_WIDE);
	}
	
*/

	i=(eDArry[eErrCntPt] % (ERR_SAVE_CNT+1));
	
	i=(i * ERR_SAVE_WIDE);
	sRamDArry[mBefErrCntPt]=i;

	eDArry[eSysErCnt + i + 0] = sRamDArry[Month];             
    eDArry[eSysErCnt + i + 1] = sRamDArry[Day];             
    eDArry[eSysErCnt + i + 2] = sRamDArry[mcurfloor];            
    eDArry[eSysErCnt + i + 3] = ErrName;       
    eDArry[eSysErCnt + i + 4] = sRamDArry[Hour];             
    eDArry[eSysErCnt + i + 5] = sRamDArry[Minuate];             
           
	if(eDArry[eErrCntPt] < ((ERR_SAVE_CNT+1) * ERR_SAVE_WIDE) ){
     	eDArry[eErrCntPt]++; 
	}     	

	ErrChkNm=0;
    bSaveErrCnt=1;

	return(0);
}


       
UserDataType  __attribute__((section(".usercode"))) ErrSave(void)
{  
    if(sRamDArry[mDoorSeq] == READY_ELEVATOR)   return(1);		


   	if(bsCleNoOn){								//44							
      	if(!bBefbsCleNoOn){
   			SaveEebuf(sCLE_NO_ON);
            bBefbsCleNoOn=bsCleNoOn;
      	}        
   	}

   	if(bsHdsNoOn){								//43						
      	if(!bBefbsHdsNoOn){
   			SaveEebuf(sHDS_NO_ON);
        	bBefbsHdsNoOn=bsHdsNoOn;
      	}        
   	}

   	if(bsSdsErr){								//26
      	if(!bBefbsSdsErr){
			SaveEebuf(sSdsErr);
        	bBefbsSdsErr=bsSdsErr;
      	}        
   	}

   	if(bsSusErr){								//25
      	if(!bBefbsSusErr){
			SaveEebuf(sSusErr);
        	bBefbsSusErr=bsSusErr;
      	}        
   	}

   	if(bsBreakOpen){							//24
      	if(!bBefbsBreakOpen){
			SaveEebuf(sBreakOpen);
        	bBefbsBreakOpen=bsBreakOpen;
      	}        
   	}

   	if(bsBreakMgtOpen){							//23
      	if(!bBefbsBreakMgtOpen){
			SaveEebuf(sBreakMgtOpen);
        	bBefbsBreakMgtOpen=bsBreakMgtOpen;
      	}        
   	}


   	if(bEncoderABErr){							//16
      	if(!bBefbEncoderABErr){
			SaveEebuf(sEncoderABErr);
        	bBefbEncoderABErr=bEncoderABErr;
      	}        
   	}


   	if(bEncoderErr){							//15
      	if(!bBefbEncoderErr){
			SaveEebuf(sEncoderErr);
        	bBefbEncoderErr=bEncoderErr;
      	}        
   	}     


   	if(bMotor_Overheat){								
      	if(!bBefbMotor_Overheat){
   			SaveEebuf(sMOTOR_OVERHEAT);
        	bBefbMotor_Overheat=bMotor_Overheat;
      	}        
   	}

	if(bRelevelErr){							//13
		if(!bBefbRelevelErr){
			SaveEebuf(sRelevelError);
        	bBefbRelevelErr=bRelevelErr;
      	}        
   	}

	if(bsCleRunOff){							//13
		if(!bBefbsCleRunOff){
			SaveEebuf(sCLE_RUN_OFF);
        	bBefbsCleRunOff=bsCleRunOff;
      	}        
   	}


   	if(bsHdsRunOff){							//12
      	if(!bBefbsHdsRunOff){
			SaveEebuf(sHDS_RUN_OFF);
        	bBefbsHdsRunOff=bsHdsRunOff;
      	}        
   	}


   	if(bsNextFloor){							//10
      	if(!bBefbsNextFloor){
			SaveEebuf(sNEXT_FLOOR);
        	bBefbsNextFloor=bsNextFloor;
      	}        
   	}


   	if(bsLuLdNoOff){							//9
      	if(!bBefbsLuLdNoOff){
   			SaveEebuf(sLULD_NO_OFF);
        	bBefbsLuLdNoOff=bsLuLdNoOff;
      	}        
   	}


   	if(bsDls){									//8
      	if(!bBefbsDls){
			SaveEebuf(sDLS);
        	bBefbsDls=bsDls;
      	}        
   	}

   	if(bsUls){									//7
      	if(!bBefbsUls){
			SaveEebuf(sULS);
        	bBefbsUls=bsUls;
      	}        
   	}


   	if(bsSlip){									//6
      	if(!bBefbsSlip){
      		SaveEebuf(sSLIP);
        	bBefbsSlip=bsSlip;
      	}        
   	}


   	if(bsLope){									//4
      	if(!bBefbsLope){
      		SaveEebuf(sLOPE_BRK);
        	bBefbsLope=bsLope;
      	}        
   	}
   
   	if(bsEmergency){							//3
      	if(!bBefbsEmergency){
			SaveEebuf(sEMERGENCY);    
        	bBefbsEmergency=bsEmergency;
      	}        
   	}
     
   	if(bsInvCurNext){							//2
      	if(!bBefbsInvCurNext){
			SaveEebuf(sI_C_N_FLR);
        	bBefbsInvCurNext=bsInvCurNext;
      	}        
   	}     

   	if(bsInvertErr){							//1
      	if(!bBefbsInvertErr){
			SaveEebuf(sInvertErr);
        	bBefbsInvertErr=bsInvertErr;
      	}        
   	}


   	if(bsLuOrLdErr && (LuLdErrNm > 0)){							  //
      	if(!bBefsLuOrLdErr){
			SaveEebuf(sLuOrLdErr0 + LuLdErrNm-1);
        	bBefsLuOrLdErr=bsLuOrLdErr;
      	}        
   	}


/*
////////////////////
   	if(bEncoderErr){							//15
      	if(!bBefbEncoderErr){
			SaveEebuf(sEncoderErr);
        	bBefbEncoderErr=bEncoderErr;
      	}        
   	}     
*/

   	if(bDoorJumper){							  //
      	if(!bBefDoorJumper){
			SaveEebuf(sCarDoor_Jumper + DoorJumperNm);
        	bBefDoorJumper=bDoorJumper;
      	}        
   	}


   	if(bsEarthquake){							//36
      	if(!bBefbsEarthquake){
			SaveEebuf(sEarthquake);
        	bBefbsEarthquake=bsEarthquake;
      	}        
   	}

    return(0);		
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
////////	bBefbsLuLdHome=0;
	bBefbsLuLdNoOff=0;
    bBefbsLope=0;
    bBefbsInvCurNext=0;
	bBefbsDls=0;
	bBefbsUls=0; 
    bBefbEncoderErr=0;
    bBefbEncoderABErr=0;
//    bBefbsBreakMgtOpen=0;
//    bBefbsBreakOpen=0;    
    bBefbsInvertErr=0;
    bBefbsSdsErr=0;
    bBefbsSusErr=0;

	bBefDoorJumper=0;
	bBefbMotor_Overheat=0;
}




void  __attribute__((section(".usercode"))) SystemErrSave(void)
{
	unsigned char kk;

	if(bAuto){     
		ErrSave(); 
        if(!bMoveCar && bSaveErrCnt){

			kk= EEPROM_Read_Byte(ErrChkNm);
			if(eDArry[ErrChkNm] != kk){
		        EEPROM_Write_Byte((unsigned int)(ErrChkNm),eDArry[ErrChkNm]);
			}

			if(ErrChkNm >= eErrCntPt){
				bSaveErrCnt=0;
				ErrChkNm=0;
			}	
			else{
				ErrChkNm++;
			}
        }
	}              
    else    ErrFlagClr();
}








void  __attribute__((section(".usercode"))) Serial2Check(void)
{
    if(RxStatus2==RX_GOOD){
		if(bExportData || bImportData){
			NewLoaderChk();
		}
        LadderBuf[C_SAVE_DATA+0]=RxBuffer2[2];

		if(RxBuffer2[1] == '0'){
            bPasswardOk=1;
            bAllMenu=1;
			bCompanyCtl=1;
            bUserOn=1;
			bLoaderActive=1;
		} 

		if(RxBuffer2[1] == cF_COMPANY)	bLoaderActive=1;
		
     
        NewFlashData();
        RxStatus2=STX_CHK;                        
    }         
                           
    if((RxStatus2 != TX_SET) && (SerialTime2 > 10)){
        if(LadderTime>100){
            LadderBuf[C_SAVE_DATA+0]='N';      
            NewFlashData();
            LadderTime=0;
        }
        LdDataTx();
        SerialTime2=0;
    }               
}




void  __attribute__((section(".usercode"))) ClrUpDnWard(void)
{        
    S2_DN1=0;
    S1_UP1=0;                                                     //up
    S3_SHIFT1=0;
 
    bUpWard=0;              
    bDnWard=0;              

	sRamDArry[DEST_FLR] = (sRamDArry[DEST_FLR] & ONLY_FLR);
}


void  __attribute__((section(".usercode"))) UpWard(void)
{    
   S2_DN1=0;
   S1_UP1=1;
   bUpWard=1;              
   bDnWard=0;             

//	sRamDArry[DEST_FLR]= (sRamDArry[DEST_FLR] & ~DN_READY);
//	sRamDArry[DEST_FLR]= (sRamDArry[DEST_FLR] |  UP_READY);
   
   if(bMoveCar && !bUnd)    S3_SHIFT1=1; //shift
   else                     S3_SHIFT1=0; //shift
}


void  __attribute__((section(".usercode"))) DnWard(void)
{    
   S2_DN1=1;
   S1_UP1=0;         
   bUpWard=0;              
   bDnWard=1;              

//	sRamDArry[DEST_FLR]= (sRamDArry[DEST_FLR] & ~UP_READY);
//	sRamDArry[DEST_FLR]= (sRamDArry[DEST_FLR] |  DN_READY);
   
   if(bMoveCar && !bUnd)    S3_SHIFT1=1; //shift
   else                     S3_SHIFT1=0; //shift
}


UserDataType  __attribute__((section(".usercode"))) ReadyAndNoKeyCheck(void)
{
	if((sRamDArry[mDoorSeq] == READY_ELEVATOR) && 
//            (sRamDArry[mEqualFloor] == 0) && 
            (sRamDArry[mHighFloor] == 0) && 
            (sRamDArry[mLowFloor] == 0)){  
     	return(0);       
	}                      
	else	return(1);
}


void  __attribute__((section(".usercode"))) Virtual_Floor_Set(UserDataType vFloor)
{
	if(vFloor <= cF_TOPFLR){
		if(sRamDArry[mcurfloor] > (unsigned char)(vFloor)){
			sRamDArry[mLowFloor] = (unsigned char)(vFloor | CAR_READY);                     
		}
		else if(sRamDArry[mcurfloor] < (unsigned char)(vFloor)){
			sRamDArry[mHighFloor] = (unsigned char)(vFloor | CAR_READY);                     
		}
	}
}

unsigned int  __attribute__((section(".usercode"))) AutoRunReady(void)
{
    if(!bAuto  || S3_PARKING1   || S2_FIRE1 || bWaterSen || S1_POWER_FAIL)      return(0);
    else if(bCarErr || bCarStopNoRun || bCarStop || bManualStop)                return(0);                 
    else                                                                        return(1);
}


unsigned int  __attribute__((section(".usercode"))) OneStopKey(void)
{
    LocalType     cTime;
    LocalType     xx0,xx1,xx2;

    unsigned 	char  TmpOneStopFlr;
	



/*
	cTime=FixFloorStartTimeCheck();
	if(cTime <= 0)																return(0);
	xx0=TimeCmpare(cTime,0);
	xx1=TimeCmpare(cTime,5);
	if( !(xx0 | xx1))															return(0);
*/

	if( !(cF_ONESTOP_FLOOR & UPDN_READY))									return(0);


	TmpOneStopFlr = (cF_ONESTOP_FLOOR & (~(UPDN_READY)) );

  	if(S3_VIP1)																return(0);
    if(TmpOneStopFlr >= cF_TOPFLR)                                          return(0);
    if(!AutoRunReady())                                                     return(0);
    if(bTestKey)                                                            return(0);  
	if( !bUpWard && !bDnWard)												return(0); 		
	if( (sRamDArry[mAckStopFloor] & ONLY_FLR) == (TmpOneStopFlr))			return(0);
    if((sRamDArry[mcurfloor] == TmpOneStopFlr))                           	return(0);

	if(bUpWard){
        if( !(cF_ONESTOP_FLOOR & UP_READY))           						return(0);			
        if( !(sRamDArry[mHighFloor] & UPDN_CAR_READY))            			return(0);
        if((sRamDArry[mHighFloor] & ONLY_FLR) <= (TmpOneStopFlr))           return(0);
        if((sRamDArry[mcurfloor] > TmpOneStopFlr))                          return(0);
        if((sRamDArry[mcurfloor] >= cF_TOPFLR))                             return(0);
    	Virtual_Floor_Set(TmpOneStopFlr);

    }
    else if(bDnWard){
        if( !(cF_ONESTOP_FLOOR & DN_READY))           						return(0);			
        if( !(sRamDArry[mLowFloor] & UPDN_CAR_READY))            			return(0);
        if((sRamDArry[mLowFloor] & ONLY_FLR) >= (TmpOneStopFlr))            return(0);
        if((sRamDArry[mcurfloor] < TmpOneStopFlr))                          return(0);
        if((sRamDArry[mcurfloor] <  1))                                 	return(0);
	    Virtual_Floor_Set(TmpOneStopFlr);
    }

    return(0);
}




#ifdef	TEMP_GUEN

unsigned int  __attribute__((section(".usercode"))) OneStopKey_GUEN(void)
{

    unsigned 	char  TmpOneStopFlr;
	

	TmpOneStopFlr = cF_FIXFLOOR;

	if(CmdFixFlrTime == 0)													return(0);
	if(S3_PARKING1)															return(0);
  	if(S3_VIP1)																return(0);
    if(TmpOneStopFlr > cF_TOPFLR)                                           return(0);
    if(!AutoRunReady())                                                     return(0);
    if(bTestKey)                                                            return(0);  
	if( (sRamDArry[mAckStopFloor] & ONLY_FLR) == (TmpOneStopFlr))			return(0);
    if((sRamDArry[mcurfloor] == TmpOneStopFlr))                           	return(0);
	if( !bUpWard && !bDnWard)												return(0); 		


	if(bUpWard){
    	if( (sRamDArry[mcurfloor] == 0) && !(sRamDArry[mHighFloor] & UPDN_CAR_READY))	return(0);
        if((sRamDArry[mcurfloor] >  TmpOneStopFlr))                         return(0);
        if((sRamDArry[mHighFloor] & ONLY_FLR) == (TmpOneStopFlr))			return(0);

        if((sRamDArry[mHighFloor] & ONLY_FLR) > (TmpOneStopFlr)){
	    	Virtual_Floor_Set(TmpOneStopFlr);
			return(0);
		}

        if((sRamDArry[mHighFloor] & ONLY_FLR) < (TmpOneStopFlr)){
	        if( !(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
	    		Virtual_Floor_Set(TmpOneStopFlr);
	           	return(0);
			}
	        else if((sRamDArry[mHighFloor] & UPDN_CAR_READY)== DN_READY){
	    		Virtual_Floor_Set(TmpOneStopFlr);
	           	return(0);
			}
			else{
//				sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] | UP_READY);				
	           	return(0);
			}
		}
    }
    else if(bDnWard){
    	if( (sRamDArry[mcurfloor] == cF_TOPFLR) && !(sRamDArry[mLowFloor] & UPDN_CAR_READY))	return(0);
        if((sRamDArry[mcurfloor] <  TmpOneStopFlr))                         return(0);

        if((sRamDArry[mLowFloor] & ONLY_FLR) == (TmpOneStopFlr))			return(0);

        if((sRamDArry[mLowFloor] & ONLY_FLR) < (TmpOneStopFlr)){
	    	Virtual_Floor_Set(TmpOneStopFlr);
			return(0);
		}

        if((sRamDArry[mLowFloor] & ONLY_FLR) > (TmpOneStopFlr)){
	        if( !(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
	    		Virtual_Floor_Set(TmpOneStopFlr);
	           	return(0);
			}
	        else if( (sRamDArry[mLowFloor] & UPDN_CAR_READY) == UP_READY){
	    		Virtual_Floor_Set(TmpOneStopFlr);
	           	return(0);
			}
			else{
//				sRamDArry[mLowFloor]=(sRamDArry[mLowFloor] | DN_READY);				
	           	return(0);
			}
		}
    }

    return(0);
}
#endif




void  __attribute__((section(".usercode"))) CarKeyClr(void)
{
	sRamDArry[mEqualFloor]=(sRamDArry[mEqualFloor] & ~CAR_READY);
	sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] & ~CAR_READY);	
	sRamDArry[mLowFloor]=(sRamDArry[mLowFloor] & ~CAR_READY);

    sRamDArry[mCarKey1] =0x0;
    sRamDArry[mCarKey9] =0x0;;
    sRamDArry[mCarKey17]=0x0;     
    sRamDArry[mCarKey25]=0x0;

}


void  __attribute__((section(".usercode"))) KeyClr(void)
{
	sRamDArry[mEqualFloor]=0x0;
	sRamDArry[mHighFloor]=0x0;	
	sRamDArry[mLowFloor]=0x0;
    sRamDArry[mAckStopFloor] = 0x0;
    sRamDArry[mNewAckStopFloor]=0x0;

    sRamDArry[mCarKey1] =0x0;
    sRamDArry[mCarKey9] =0x0;
    sRamDArry[mCarKey17]=0x0;     
    sRamDArry[mCarKey25]=0x0;
}




void   __attribute__((section(".usercode"))) Init485_Bd(void)
{
	for(LogAddressLoop=0;LogAddressLoop<ABS_ADDRESS;LogAddressLoop++){
		BDid[sRamDArry[mDoorSeq]]=0;
		BdErrCntSeq[sRamDArry[mDoorSeq]]=0;
	}
      
	for(LogAddressLoop=0;LogAddressLoop < 12;LogAddressLoop++){
		errbd[LogAddressLoop]=0x0;
		Olderrbd[LogAddressLoop]=0x0;
	}
   
	LogAddressLoop=0;
	LogAddress=0;        
	TimeOutBd=0;
	BefRcvAdr=0;
	AbsAddress=0;
	SerialTime=0;
	bFindBoard=0;   
	errpt=0;
	ErrBdNamePt=0;
	BefErrBdNamePt=0;
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
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

    OUT_0=1;
    OUT_0=1;
    OUT_0=1;
    OUT_0=1;

    OUT_0=0;
    OUT_0=0;
    OUT_0=0;
    OUT_0=0;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


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



void __attribute__((section(".usercode")))  ButtonClrCheck(void)
{
    S2_EXT_BUT_CLR1=0;
    S2_CAR_BUT_CLR1=0;


    if(S1_POWER_FAIL || bDoorJumper){
        ClrUpDnWard();
       	bExtButClr=1;
        bCarButClr=1;   
    }

   	if(bExtButClr){   
        S2_EXT_BUT_CLR1=1; 
   	}

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


void  __attribute__((section(".usercode")))   UpDnStopCmd(void)
{
    OUT_U_W(0);
    OUT_D_W(0);
    OUT_P1(0);
    OUT_P2(0);
    OUT_P3(0);
    OUT_P4(0);
    OUT_BK2(0);
    OUT_BRK(0);
    sRamDArry[mCarMoveState]=0;

}


void   __attribute__((section(".usercode"))) CarAllStopCmd(void)
{
/*
   	OUT_BRK(0);   
   	OUT_BK2(0);   
    OUT_U_W(0);                                                               
    OUT_D_W(0);                                                               
    OUT_P3(0);                                                         
    OUT_P1(0);                                                         
    OUT_P2(0);
	OUT_P4(0);
*/


	UpDnStopCmd();

    OUT_ERR(1);        

    OUT_DAC(0);
    bDac=0;
	
	bManualStop=1;

    ManualStopTime=0;


    S2_CAR_MOVE1=0;
    
    S3_UPDN_VO1=0;
    
    ClrUpDnWard();
    
    bMoveCar=0;
    bCarUpMove=0;
    bCarDnMove=0;
   	ElevMoveTime=0;

    bDoorOpenCmd=0;
    bDoorCloseCmd=0;
 
    sRamDArry[mReqStopFloor]=0;      
    sRamDArry[mCarMoveState]=0;


   	bExtButClr=1;
    bCarButClr=1;   
    KeyClr();     

   	OUT_ON=0;
   	OUT_ON=0;
    OutData();
    OutData();
}




void  __attribute__((section(".usercode")))   CarManualStopCmd(void)
{        
    LocalType tmp;     
    unsigned int	tmp_time;

    tmp_time = (ManualStopTime * 100);
    
    tmp=0;

    bInvOutAllClr=0;        

    CounterTime=0;
    ZeroSpeedCmd_IO(); 

               
    if(tmp_time>iF_Bk1OffTime){
        OUT_BRK(0);                     
        tmp=(tmp | 0x01);;
    }

    if(tmp_time>iF_Bk2OffTime){
        OUT_BK2(0);
        tmp=(tmp | 0x02);;
    }              

    if(tmp_time>iF_UDOffTime){
        OUT_U_W(0);                                                               
        OUT_D_W(0);                                                        
        tmp=(tmp | 0x04);;
    }              

    if(tmp_time>iF_P4OffTime){
        OUT_P4(0);
        tmp=(tmp | 0x08);;
    }


    if(tmp == 0x0f){
        bInvOutAllClr=1;        
    }
    else{
        bInvOutAllClr=0;
    }
}



void   __attribute__((section(".usercode"))) CarAllStopCmdTest(void)
{
    unsigned long i,j;
 
    if(!bManualStop){
        ManualStopTime=0;
        bInvOutAllClr=0;
    }           

   	bExtButClr=1;
    bCarButClr=1;   
    ButtonClrCheck();

    bManualStop=1;
	ElevMoveTime=0;
    
    OUT_DAC(0);
    bDac=0;

    if(!OilLopeTypeChk || bCarErr || bCarStopNoRun){                                             

/*
        ZeroSpeedCmd_IO();                       
      	OUT_BRK(0);   
      	OUT_BK2(0);   
        OUT_U_W(0);                                                               
        OUT_D_W(0);                                   
        OUT_P4(0);         
*/

		UpDnStopCmd();           
        OUT_ERR(1);        



        bDoorOpenCmd=0;
        bDoorCloseCmd=0;

        ClrUpDnWard();

        if(ManualStopTime > 15){
            bInvOutAllClr=1;
        }        
    }
    else    CarManualStopCmd();
   
        
    if(bInvOutAllClr){        
		bManualStop=0;
		sRamDArry[mDoor]    = (sRamDArry[mDoor] & CLEAR_ALL_DOOR_KEY);   

		UpDnStopCmd();

/*
        ZeroSpeedCmd_IO();                       
      	OUT_BRK(0);   
      	OUT_BK2(0);   
	    OUT_U_W(0);                                                               
	    OUT_D_W(0);                                                               
        OUT_P4(0);
*/


      	if(IN_DLS)		            bHomeUpDn = 1;                   
      	else if(IN_ULS)             bHomeUpDn = 0;
      	else if(!IN_BAT){												//3.4d
    		bHomeUpDn = 1;												//3.4d
			if(!IN_X4 && (USE_CHECK == MAN_USE))	bHomeUpDn = 0;		//3.4d			
		}																//3.4d
      	else if(!IN_LU && IN_LD)    bHomeUpDn = 1;
      	else if(IN_LU && !IN_LD)    bHomeUpDn = 0;

        else if(!IN_SD1)          bHomeUpDn=0;           
        else if(!IN_SU1)  		  bHomeUpDn=1;           
        else if((sRamDArry[mcurfloor] == 0))          bHomeUpDn=0;           
        else if((sRamDArry[mcurfloor] == cF_TOPFLR))  bHomeUpDn=1;           

//        else if(!IN_SD1 || (sRamDArry[mcurfloor] == 0))          bHomeUpDn=0;           
//        else if(!IN_SU1 || (sRamDArry[mcurfloor] == cF_TOPFLR))  bHomeUpDn=1;           

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


        bFR2Start1=0;

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
    if(!bMoveCar){
    	bSetSpeedOn=0;
        if(!bCarOnceStop){
            CarOnceStopTime=0;
            bCarOnceStop=1;
        }
    }                
    else{
        bCarOnceStop=0;
        bSlipCheckStart=0;
    }
}


UserDataType	__attribute__((section(".usercode"))) NextUpDnKeyChk(unsigned int UpDn)
{
	UserDataType	i,j,k,bitvar,Fstartflr,Flastflr,ret;
	UserDataType	tmpCarkey[4];

	ret=1;
	CarBdButtonFlr=0;


	k=(UserDataType)(sRamDArry[mcurfloor]);
    k=(k & 0x00ff);

//	if(k < 1)					return(1);
//	if(k >= cF_TOPFLR)			return(1); 

	tmpCarkey[0]=(sRamDArry[mCarKey1]  & sRamDArry[FLR_ON_OFF0]);
	tmpCarkey[1]=(sRamDArry[mCarKey9]  & sRamDArry[FLR_ON_OFF1]);
	tmpCarkey[2]=(sRamDArry[mCarKey17] & sRamDArry[FLR_ON_OFF2]);
	tmpCarkey[3]=(sRamDArry[mCarKey25] & sRamDArry[FLR_ON_OFF3]);


	j=0;


    bitvar=0x01;    

   	if(UpDn){
		if(k >= cF_TOPFLR)			return(1);
		else{ 
			Fstartflr = (k+1);
			Flastflr  = cF_TOPFLR;
	
			i = (Fstartflr / 8);
			j = (j + i);
	
			i = (Fstartflr % 8);
	   	 	bitvar=(bitvar << i);    
		}
	}
	else{
		if(k < 1)		return(1);
		else{
			Fstartflr=0;
			Flastflr=(k-1);
		}		
	}


    for( ; Fstartflr <= Flastflr;Fstartflr++){
		if(tmpCarkey[j] & bitvar){
			CarBdButtonFlr=(Fstartflr | CAR_READY);
			ret=0;
   			if(UpDn==0)	return(ret);
        }
        bitvar=(bitvar << 1);
        bitvar=(bitvar & 0x00ff);

        if(bitvar==0x0){
            bitvar=0x01;
            j++;
        }
    }

    return(ret);
}


/*
UserDataType	__attribute__((section(".usercode"))) NextUpKeyChk(unsigned int Fl)
{
	UserDataType	i,j,k,bitvar;
    
    k=(Fl & ONLY_FLR);
    k=(k & 0x00ff);

    j=mCarKey1;
    bitvar=0x01;    


    for(i=0; i <= cF_TOPFLR;i++){
        if(sRamDArry[j] & bitvar){
            if(i > k)   return(0);
        }
        bitvar=(bitvar << 1);
        bitvar=(bitvar & 0x00ff);

        if(bitvar==0x0){
            bitvar=0x01;
            j++;
        }
    }
    return(1);
}


UserDataType	__attribute__((section(".usercode"))) NextDnKeyChk(unsigned int Fl)
{
	UserDataType	i,j,k,bitvar;
    
    k=(Fl & ONLY_FLR);
    k=(k & 0x00ff);
    j=mCarKey1;
    bitvar=0x01;    

    for(i=0; i< k;i++){
        if(sRamDArry[j] & bitvar){
            if(i < k)  return(0);                
        }
        bitvar=((bitvar << 1) & 0x00ff);

        if(bitvar==0x0){
            bitvar=0x01;
            j++;
        }
    }
    return(1);
}
*/



UserDataType  __attribute__((section(".usercode"))) TopDirectionSet(void)
{			
	bCarUpDnChButClr=1;
	DnWard();
	if( !(sRamDArry[mAckStopFloor] & DN_READY))	sRamDArry[DEST_FLR] = (sRamDArry[DEST_FLR]	& ~DN_READY);	
	sRamDArry[mAckStopFloor]=(sRamDArry[mcurfloor] | DN_READY);	
}


UserDataType  __attribute__((section(".usercode"))) LowDirectionSet(void)
{			
	bCarUpDnChButClr=1;
	UpWard();
	if( !(sRamDArry[mAckStopFloor] & UP_READY))	sRamDArry[DEST_FLR] = (sRamDArry[DEST_FLR]	& ~UP_READY);	
	sRamDArry[mAckStopFloor]=(sRamDArry[mcurfloor] | UP_READY);	
}


UserDataType  __attribute__((section(".usercode"))) CallMeUpDnDirectionSet(void)
{			
    if(bUpDnSet)    return(0);

        
    if((sRamDArry[mHighFloor]    & ONLY_FLR) <= (sRamDArry[DEST_FLR] & ONLY_FLR))  sRamDArry[mHighFloor]=0x0;
    if((sRamDArry[mLowFloor]     & ONLY_FLR) >= (sRamDArry[DEST_FLR] & ONLY_FLR))  sRamDArry[mLowFloor]=0x0;

     if( !(sRamDArry[mMostLongDst] & UPDN_CAR_READY) )								sRamDArry[mMostLongDst]=0x0;


   	if(bUpWard){
      	if(sRamDArry[mcurfloor] == cF_TOPFLR){
			TopDirectionSet();
		}      		
      	else if((sRamDArry[mAckStopFloor] & ONLY_FLR) == cF_TOPFLR){
			TopDirectionSet();
		}      		
      	else if(sRamDArry[mAckStopFloor] & UP_READY){
            UpWard();      	
      	} 

      	else if(sRamDArry[mAckStopFloor] & CAR_READY){
	        if(!NextUpDnKeyChk(1)){
	            UpWard();
	            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
	        }
	      	else if( (sRamDArry[mMostLongDst] & ONLY_FLR) > (sRamDArry[DEST_FLR] & ONLY_FLR) ){ 
	            UpWard();
	            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
	      	} 
	      	else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
	            UpWard();
	      	}
	      	else if(sRamDArry[mAckStopFloor] & DN_READY){
	            DnWard();
				bCarUpDnChButClr=1;
	      	}        
	      	else{
	            ClrUpDnWard();
				bCarUpDnChButClr=1;
	        } 
      	} 
      	else if(sRamDArry[mAckStopFloor] & DN_READY){
            DnWard();
			bCarUpDnChButClr=1;
      	}        
      	else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
            UpWard();
      	}
        else if(!NextUpDnKeyChk(1)){
            UpWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
        }
      	else if(sRamDArry[mDoor] & UPDN_CAR_READY){
            UpWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
      	}
      	else if( (sRamDArry[mMostLongDst] & ONLY_FLR) > (sRamDArry[DEST_FLR] & ONLY_FLR) ){ 
            UpWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | UP_READY);
      	} 
//      	else if(sRamDArry[mHighFloor] & UPDN_CAR_READY){
//            UpWard();
//      	}
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
			LowDirectionSet();
		}
      	else if((sRamDArry[mAckStopFloor] & ONLY_FLR)== 0){
			LowDirectionSet();
		}      		
      	else if(sRamDArry[mAckStopFloor] & DN_READY){
            DnWard();      	
      	}
      	else if(sRamDArry[mAckStopFloor] & CAR_READY){
	        if(!NextUpDnKeyChk(0)){
	            DnWard();
	            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
	      	} 
	      	else if( (sRamDArry[mMostLongDst] & UPDN_CAR_READY) && ((sRamDArry[mMostLongDst] & ONLY_FLR) < (sRamDArry[DEST_FLR] & ONLY_FLR)) ){ 
	            DnWard();
	            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
	      	} 
	      	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
	            DnWard();
	      	}
	      	else if(sRamDArry[mAckStopFloor] & UP_READY){
	            UpWard();      	
	   			bCarUpDnChButClr=1;
	      	} 
	      	else{ 
	            ClrUpDnWard();
				bCarUpDnChButClr=1;
	      	}
      	} 
      	else if(sRamDArry[mAckStopFloor] & UP_READY){
            UpWard();      	
   			bCarUpDnChButClr=1;
      	}
      	else if(sRamDArry[mLowFloor] & UPDN_CAR_READY){
            DnWard();
      	}
        else if(!NextUpDnKeyChk(0)){
            DnWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
      	} 
      	else if(sRamDArry[mDoor] & UPDN_CAR_READY){
            DnWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
      	}      	
      	else if( (sRamDArry[mMostLongDst] & ONLY_FLR) < (sRamDArry[DEST_FLR] & ONLY_FLR) ){ 
            DnWard();
            sRamDArry[mAckStopFloor] = (sRamDArry[mAckStopFloor] | DN_READY);
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
    bUpDnSet=1;

    sRamDArry[mMostLongDst]=0x0;

    return(0);
}

/*
UserDataType   __attribute__((section(".usercode")))  ButtonCompChk(void)
{
	if( (ButtonCmpBuf[0] != (UserDataType)(sRamDArry[mCarKey1])) ||  (ButtonCmpBuf[1] != (UserDataType)(sRamDArry[mCarKey9])) ||  (ButtonCmpBuf[2] != (UserDataType)(sRamDArry[mCarKey17])) ||  (ButtonCmpBuf[3] != (UserDataType)(sRamDArry[mCarKey25]))){
		ButtonCmpBuf[0] = (UserDataType)(sRamDArry[mCarKey1]);
		ButtonCmpBuf[1] = (UserDataType)(sRamDArry[mCarKey9]);
		ButtonCmpBuf[2] = (UserDataType)(sRamDArry[mCarKey17]);
		ButtonCmpBuf[3] = (UserDataType)(sRamDArry[mCarKey25]);
		return(0);
	}

	return(1);
}
*/

void __attribute__((section(".usercode")))  HighLowCallClear(void)
{
    if(bUpWard){
		sRamDArry[mLowFloor] = 0x0;	
    	if(((sRamDArry[mHighFloor] & ONLY_FLR) < (sRamDArry[mReqStopFloor] & ONLY_FLR)) && !bUnd){
            sRamDArry[mHighFloor]=0x0;
        }

    	if(bUnd && bDac){
			if((sRamDArry[mHighFloor] & ONLY_FLR) <= sRamDArry[mcurfloor]){
				sRamDArry[mHighFloor] = 0x0;	
			}				
		}


/*
	   	if( !(sRamDArry[mHighFloor] & UP_READY)){
			if((sRamDArry[mMostLongDst] & UPDN_CAR_READY) && ((sRamDArry[mMostLongDst] & ONLY_FLR) > (sRamDArry[mHighFloor] & ONLY_FLR)) ){
				if( (sRamDArry[mcurfloor] < (sRamDArry[mHighFloor] & ONLY_FLR)) ){
					sRamDArry[mHighFloor] = ( sRamDArry[mHighFloor] & ~DN_READY); 
					sRamDArry[mHighFloor] = ( sRamDArry[mHighFloor] | UP_READY); 
				}
			}
			else if( !ButtonCompChk()){
				if( !NextUpDnKeyChk(1)){
					sRamDArry[mMostLongDst]=(unsigned char)CarBdButtonFlr;
				}
			}		
		}
*/


    }	
    else if(bDnWard){
		sRamDArry[mHighFloor] = 0x0;	
    	if(((sRamDArry[mLowFloor] & ONLY_FLR) > (sRamDArry[mReqStopFloor] & ONLY_FLR)) && !bUnd){
            sRamDArry[mLowFloor]=0x0;
        }

    	if(bUnd && bDac){
			if((sRamDArry[mLowFloor] & ONLY_FLR) >= sRamDArry[mcurfloor]){
				sRamDArry[mLowFloor] = 0x0;	
			}				
		}


/*	        	
	   	if( !(sRamDArry[mLowFloor] & DN_READY)){
			if((sRamDArry[mMostLongDst] & UPDN_CAR_READY) && ( (sRamDArry[mMostLongDst] & ONLY_FLR) < (sRamDArry[mLowFloor] & ONLY_FLR)) ){
				if((sRamDArry[mcurfloor] > (sRamDArry[mLowFloor] & ONLY_FLR)) ){
					sRamDArry[mLowFloor] = ( sRamDArry[mLowFloor] & ~UP_READY); 
					sRamDArry[mLowFloor] = ( sRamDArry[mLowFloor] | DN_READY); 
				}
			}
			else if( !ButtonCompChk()){
				if( !NextUpDnKeyChk(0)){
					sRamDArry[mMostLongDst]=(unsigned char)CarBdButtonFlr;
				}
			}
			
		}
*/

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
//    if((INVERTER_CHECK == IO) && (bitChk_FLRDSPCH(F_OnOff1,(bEncoderUse % 8))) ){
//    if((INVERTER_CHECK == IO) && (EncoderUseChk) ){
    if(INVERTER_CHECK == IO){

        if(bFhmRun)             CounterChkTime=30;
        else if(!bManualAuto)   CounterChkTime=30;
        else                    CounterChkTime=10;
                

        if(!bMoveCar){
            CounterTime=0;
        }  

        if((bAuto || bFhmRun) && bMoveCar && (CounterTime > CounterChkTime)){
   		    bMoveOk=0;
		    bMoveUpOk=0;
		    bMoveDnOk=0;
            bCarStopNoRun=1;
            bEncoderErr=1;
        }

        if((bAuto || bFhmRun) && bMoveCar && bCarUpMove && (CountDn> 30)){
   		    bMoveOk=0;
		    bMoveUpOk=0;
		    bMoveDnOk=0;
            bCarStopNoRun=1;    
            bEncoderABErr=1;
        }

        if((bAuto || bFhmRun) && bMoveCar && bCarDnMove && (CountUp> 30)){
   		    bMoveOk=0;
		    bMoveUpOk=0;
		    bMoveDnOk=0;
            bCarStopNoRun=1;    
            bEncoderABErr=1;
        }

        if(bEncoderErr){
            if(sRamDArry[mSysStatus] >= sEncoderErr)   sRamDArry[mSysStatus]=sEncoderErr;                
            return(0);
        }

        if(bEncoderABErr){
            if(sRamDArry[mSysStatus] >= sEncoderABErr)   sRamDArry[mSysStatus]=sEncoderABErr;            
            return(0);
        }
    }
    return(1);    
}


/*
unsigned int  __attribute__((section(".usercode"))) AutoRunReady(void)
{
    if(!bAuto  || S3_PARKING1   || S2_FIRE1 || bWaterSen || S1_POWER_FAIL)      return(0);
    else if(bCarErr || bCarStopNoRun || bCarStop || bManualStop)                return(0);                 
    else                                                                        return(1);
}
*/

/*
unsigned int  __attribute__((section(".usercode"))) FullValidCheck(void)
{
    if(!IN_FULL)    return(1);
//    else if(bitChk_FLRDSPCH(F_OnOff0,bNonStop) && bMoveCar && (sRamDArry[mAckStopFloor] & CAR_READY)){
    else if(NonStopOnOffChk && bMoveCar && (sRamDArry[mAckStopFloor] & CAR_READY)){
        return(1);    
    }
    else    return(0);

}
*/




void  __attribute__((section(".usercode"))) LightOnOff(void)
{    
    OUT_LIT(1);
    if(S3_PARKING1 && (FanTime > 2))                OUT_LIT(0);
    if(S1_POWER_FAIL && bDoorCloseOk)               OUT_LIT(0);
    if(bWaterSen && bDoorOpenEnd)   	            OUT_LIT(0);
    if((LightTime >= cF_LIGHTTIME))                 OUT_LIT(0);
}


void  __attribute__((section(".usercode"))) EmergencyCheck(void)
{
	unsigned int i;
/*
    if(!IN_BAT && bAuto){                          
        if(INVERTER_CHECK == LG)    BatterySpeedCmd_IO();
    }
*/

	if(bsEmergency || bsLope || bsSlip){

        OUT_U_W(0);
        OUT_D_W(0);
        OUT_P1(0);
        OUT_P2(0);
        OUT_P3(0);
        OUT_P4(0);
        OUT_DAC(0);
        OUT_OP(0);
        OUT_CL(0);
        OUT_OP_S(0);
        OUT_CL_S(0); 
        OUT_BK2(0);
        OUT_D_S(0);
        OUT_GBR(0);
        OUT_BRK(0);
        OUT_FAN(1);
        OUT_LIT(1); 
        OUT_BUZ(0);
        OUT_BELL(0);
        OUT_RST(0);
        OUT_ERR(0);
        OUT_HOP(0);
        OUT_HCL(0);

 
// 		O_U_W_bit=0;
//   	O_OP_bit=0;
//   	O_Y_0_bit=0;
	
        bCarErr=1;        

//        if(INVERTER_CHECK == LG)    OUT_P4(0);
//        else                        OUT_P4(0);


   		ElevMoveTime=0;

		ClrUpDnWard();
				
//		OUT_FAN(1);
//        OUT_LIT(1);		
//        OUT_ERR(1);        
	}

    if(bsSlip)                  OUT_GBR(1);
    else if(bsLope)             OUT_GBR(1);
    else                        OUT_GBR(0);

    if(!IN_FR1 || !IN_FR2){
        OUT_FAN(0);
	}
	
}



/*
void __attribute__((section(".usercode")))  OnlyOneCallChk(UserDataType src)
{
    BaggageFlrOnOff[0]     = 0x0;
    BaggageFlrOnOff[1]     = 0x0;
    BaggageFlrOnOff[2]     = 0x0;
    BaggageFlrOnOff[3]     = 0x0;
    
    i=(sRamDArry[DEST_FLR] & ONLY_FLR);
    j=(i / 8);
    k=(i % 8);
    i=(0x01 << k);
    
    switch(j){
        case    0:
         BaggageFlrOnOff[0] = i;
            break;                    
        case    1:
         BaggageFlrOnOff[1] = i;
            break;                    
        case    2:
         BaggageFlrOnOff[2] = i;
            break;                    
        case    3:
         BaggageFlrOnOff[3] = i;
            break;                    
    }        				    
}
*/


unsigned int __attribute__((section(".usercode")))  OneDoorSenserNoCloseChk(void)
{

    if(!bHoleDoorCloseEnd)         return(1);
    else if(!bCarDoorCloseEnd)     return(1);
    else                           return(0);

}


unsigned int __attribute__((section(".usercode")))  OneDoorSenserCloseChk(void)
{
	DoorJumperNm=0;

    if(CarDoor1UseChk){
        if(CarDoorCloseEndCheckForDoorjmp())        DoorJumperNm= 1;
//return(1);
    }


    if(HoleDoor1UseChk){
        if(HoleDoorCloseEndCheckForDoorjmp())      DoorJumperNm=(DoorJumperNm | 2);
//return(1);
    }

    return(DoorJumperNm);
}


unsigned int __attribute__((section(".usercode")))  OnlyOneCallChk(void)
{
	UserDataType	i,j,k,ext_clr_chk;

    BaggageFlrOnOff[0]     = 0xff;
    BaggageFlrOnOff[1]     = 0xff;
    BaggageFlrOnOff[2]     = 0xff;
    BaggageFlrOnOff[3]     = 0xff;

//    if(USE_CHECK != BAGGAGE_USE)    return(0);
        


    ext_clr_chk=0;
            
/*
    bBaggageRstOn=1;
    if( AutoRunReady() && (sRamDArry[mDoorSeq] == READY_ELEVATOR)){
        bBaggageRstOn=0;
    }
*/

    if(AutoRunReady()){
        if(OnlyOneCallOnOffChk){            
            if((sRamDArry[mDoorSeq] != READY_ELEVATOR) || (sRamDArry[mHighFloor] > 0) || (sRamDArry[mLowFloor] > 0)){
                ext_clr_chk=1;
            }

            if(sRamDArry[mDoorSeq] > READY_ELEVATOR){                
                BaggageFlrOnOff[0]     = 0x0;
                BaggageFlrOnOff[1]     = 0x0;
                BaggageFlrOnOff[2]     = 0x0;
                BaggageFlrOnOff[3]     = 0x0;
            
                i=(sRamDArry[DEST_FLR] & ONLY_FLR);
                j=(i / 8);
                k=(i % 8);
                i=(0x01 << k);
            
                switch(j){
                    case    0:
            	        BaggageFlrOnOff[0] = i;
                        break;                    
                    case    1:
            	        BaggageFlrOnOff[1] = i;
                        break;                    
                    case    2:
            	        BaggageFlrOnOff[2] = i;
                        break;                    
                    case    3:
            	        BaggageFlrOnOff[3] = i;
                        break;                    
                }        				    
            }
        }
    }

    if(ext_clr_chk) bHibCallClear=1;
    else            bHibCallClear=0;
}


unsigned int __attribute__((section(".usercode")))  SafetyChk(void)
{

	unsigned int    i,j;

    i=0;

	if(IN_AUTO)				return(0);
    if(!IN_FR1 || !IN_FR2)  return(0);     
    if(S3_PARKING1)  		return(0);       


	bSafety_scrSft=0;

    if(INVERTER_CHECK != LG){
    	if(IN_SFT)	bSafety_scrSft=1;       

#ifndef	TEMP_PARK
		if(!S2_FIRE1){	                   
    		if(IN_FS1)	bSafety_scrSft=1;
		}        
#endif
                   		
	}
	else{
    	if(IN_SFT)	bSafety_scrSft=1;                           
	}


    if(SubSafetyUseChk){
        if(USE_CHECK == CARLIFT_USE){
            if(bSafety_scrSft)                                      i=1;
            else if(IN_FULL)                                i=1;
        }
        else{
            if(!bMoveCar){
    	        j=MainSubDoorFlrChk(sRamDArry[mcurfloor]);
                if(j==0)                                    i=0;
                else if(j==1){
                    if(bSafety_scrSft)                              i=1;
                }
                else if(j==2){
                    if(IN_FULL)                             i=1;
                }
                else{
                    if(OneDoorSenserNoCloseChk()){
                        if(CurDoorSelect == MAIN_DOOR){

                            if(bSafety_scrSft || (SafetyValidLR && IN_FULL)){
                            	sRamDArry[mDoor] = (sRamDArry[mDoor] | MAIN_OPEN_KEY);
                      			i=1;
							}			                            
                        }
                        else if(CurDoorSelect == SUB_DOOR){
                            if(IN_FULL || (SafetyValidLR && bSafety_scrSft)){
                            	sRamDArry[mDoor] = (sRamDArry[mDoor] | SUB_OPEN_KEY);
                      			i=1;
							}			                            
                        }
                    }
                    else{
                        if(bSafety_scrSft){
                            sRamDArry[mDoor] = (sRamDArry[mDoor] | MAIN_OPEN_KEY);
                            i=1;
                        }
                        else if(IN_FULL){
                            sRamDArry[mDoor] = (sRamDArry[mDoor] | SUB_OPEN_KEY);
                            i=1;
                        }
                    }                    
                }                        
            }
        }
    }
    else{
        if(bSafety_scrSft)                             						i=1;
    }        

    return(i);
}




/*
unsigned int __attribute__((section(".usercode")))  SafetyChk(void)
{

	unsigned int    i,j;

    i=0;


//    if(!bAuto)              return(0);

	if(IN_AUTO)				return(0);
    if(!IN_FR1 || !IN_FR2)  return(0);       
    if(S3_PARKING1)  		return(0);       

    if(SubSafetyUseChk){
        if(USE_CHECK == CARLIFT_USE){
            if(IN_SFT)                                      i=1;
            else if(IN_FULL)                                i=1;
        }
        else{
            if(!bMoveCar){
    	        j=MainSubDoorFlrChk(sRamDArry[mcurfloor]);
                if(j==0)                                    i=0;
                else if(j==1){
                    if(IN_SFT)                              i=1;
                }
                else if(j==2){
                    if(IN_FULL)                             i=1;
                }
                else{
                    if(OneDoorSenserNoCloseChk()){
                        if(CurDoorSelect == MAIN_DOOR){

                            if(IN_SFT || (SafetyValidLR && IN_FULL)){
                            	sRamDArry[mDoor] = (sRamDArry[mDoor] | MAIN_OPEN_KEY);
                      			i=1;
							}			                            
                        }
                        else if(CurDoorSelect == SUB_DOOR){
                            if(IN_FULL || (SafetyValidLR && IN_SFT)){
                            	sRamDArry[mDoor] = (sRamDArry[mDoor] | SUB_OPEN_KEY);
                      			i=1;
							}			                            	                            
                        }
                    }
                    else{
                        if(IN_SFT){
                            sRamDArry[mDoor] = (sRamDArry[mDoor] | MAIN_OPEN_KEY);
                            i=1;
                        }
                        else if(IN_FULL){
                            sRamDArry[mDoor] = (sRamDArry[mDoor] | SUB_OPEN_KEY);
                            i=1;
                        }
                    }                    
                }                        
            }
        }
    }
    else{
        if(IN_SFT)                                          i=1;
    }        

    return(i);
}
*/




unsigned int  __attribute__((section(".usercode")))  SaftyStopChk(void)
{
	UserDataType	safty_stop_chk;

    safty_stop_chk=0;

	if(bAuto){
//	    if(!CarDoor1UseChk && !CarDoor2UseChk)  safty_stop_chk=1;

	    if(!CarDoor1UseChk )  					safty_stop_chk=1;
	    if(USE_CHECK == CARLIFT_USE)            safty_stop_chk=1;    
	}  

    if(safty_stop_chk){
        if(SafetyChk() && !bLevelFind){
       		bMoveOk=0;
       		bMoveUpOk=0;
       		bMoveDnOk=0;

            if(bMoveCar){
        		bCarErr=1;  				         		            
            }
        }    
    }
    return(0);
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
		if(bCarUpMove || bUpWard){
			bCarErr=1;  
		    bExtButClr=1;
		    bCarButClr=1;
        	bsUls=1;
    		bMoveUpOk=0;
        }
    	else{            
            if(bsUls){
                if(!bManualStop)   bsUls=0;          
            }
            else                   bsUls=0;          
        }
	}
	else    bsUls=0;          
	
            
	if(IN_DLS){
		if(bCarDnMove || bDnWard){
			bCarErr=1;   
    		bExtButClr=1;
	    	bCarButClr=1;
            bsDls=1;    
    		bMoveDnOk=0;
        }
    	else{
            if(bsDls){
                if(!bManualStop)   bsDls=0;
            }          
            else                   bsDls=0;          
        }
	}                        
	else  bsDls=0;


	if(IN_GR){		
		bExtButClr=1;
		bCarButClr=1;
		bsLope=1;         
		bMoveOk=0;
		bMoveUpOk=0;
		bMoveDnOk=0;
		bCarErr=1;  
	}
#ifndef	GOBERNOR_LOCK
	else{
		bsLope=0;
	}         
#endif


	if(!bMoveUpOk && bUpWard){
		bCarErr=1;  
	}     
   
	if( !bMoveDnOk && bCarDnMove){
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


unsigned int __attribute__((section(".usercode")))  ThisFloorDoorCheck(void)
{   	
	OneDoorSelOpenKeyCheck();
	if(CurDoorSelect == SUB_DOOR)	OUT_D_S(1);
	else							OUT_D_S(0);
	return(0);
}


unsigned int __attribute__((section(".usercode")))  RunningOpenCheck(void)
{   	

#ifdef  TEST_SIMULATION                  
	return(0);
#else
	if( !RunningOpenOnOff)																	return(0);	
	if((USE_CHECK != MAN_USE) )																return(0);
 	if(!bAuto || !bDac || !bUnd || !bOnLuLd)												return(0);
	if((sRamDArry[mcurfloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR))			return(0);
	if(iF_SolOnTime || iF_DoorWaitTime )													return(0);
	if( !NoUseNoOpen())																		return(0);	

	if( !bRunningOpenOn){
	    if(S2_FIRE1)																		return(0);
	    if(S1_POWER_FAIL)																	return(0);
	}

	return(1);
#endif 
}



unsigned int __attribute__((section(".usercode")))  RunningOpenAction(void)
{   	
	if(RunningOpenCheck()){
		ThisFloorDoorCheck();
		SelectDoorOpen_you();    
		bRunningOpenOn=1;
		return(1);
	}
	else{
		bRunningOpenOn=0;
		return(0);
	} 
}



void __attribute__((section(".usercode")))  DoorCloseOkCheck(void)
{   	
	DoorCloseEndCheck((UserDataType)bMoveCar);

   	if(!bDoorCloseOk){
		if( !bRunningOpenOn){
	      	bMoveOk=0;
	      	bMoveUpOk=0;
	      	bMoveDnOk=0;            
	      	if(bMoveCar){
	        	bCarErr=1;   
	      	}
		}
		if(!bsEmergency)    S1_EMG1=0;
   	}
}




void __attribute__((section(".usercode")))  LuLdErrSave(unsigned int updn)
{         
	UserDataType	i,j,err;

	err=0;

	bsLuOrLdErr=1;
	LuLdErrNm=6;
	

	j=LuLdSeq[3];
	j= (j +1) % 4;
	if(LuLdSeq[2] == j){
		j= (j +1) % 4;
		if(LuLdSeq[1] == j){
			j= (j +1) % 4;
			if(LuLdSeq[0] == j){
				LuLdErrNm=1;
				err=1;
			}		
		}
	}


	if(err==0){		
		if(updn){
			if((LuLdSeq[0] == LuLdSeq[2]) && (LuLdSeq[1] == LuLdSeq[3])){
				if( (LuLdSeq[0] + LuLdSeq[1]) == 1)					LuLdErrNm=2;		//LD ON	
				if( (LuLdSeq[0] + LuLdSeq[1]) == 5)					LuLdErrNm=3;		//LD OFF	
				if( (LuLdSeq[0] + LuLdSeq[1]) == 3){
					if( (LuLdSeq[0] == 0) || (LuLdSeq[0] == 3))		LuLdErrNm=4;		//LU ON	
					if( (LuLdSeq[0] == 1) || (LuLdSeq[0] == 2))		LuLdErrNm=5;		//LU OFF	
				}
			}
		}
		else{
			if((LuLdSeq[0] == LuLdSeq[2]) && (LuLdSeq[1] == LuLdSeq[3])){
				if( (LuLdSeq[0] + LuLdSeq[1]) == 1)					LuLdErrNm=4;		//LU ON	
				if( (LuLdSeq[0] + LuLdSeq[1]) == 5)					LuLdErrNm=5;		//LU OFF	
				if( (LuLdSeq[0] + LuLdSeq[1]) == 3){
					if( (LuLdSeq[0] == 0) || (LuLdSeq[0] == 3))		LuLdErrNm=2;		//LD ON	
					if( (LuLdSeq[0] == 1) || (LuLdSeq[0] == 2))		LuLdErrNm=3;		//LD OFF	
				}
			}
		}
	}

   	bMoveOk=0;
   	bMoveUpOk=0;
   	bMoveDnOk=0;
            
   	bCarStop=1;   
}



void __attribute__((section(".usercode")))  LuLdOnCheck(void)
{         
	UserDataType	err;
	 
	err=0;

	lu_ld_state=0xff;

    if(!IN_LU && !IN_LD){
		if(!bOnLuLd){
			ReadEncoder();
			LuLdEncoder=CurPulse;			
		}

		bFirstOnLuLd=1;
        bOnLuLd=1;
		lu_ld_state=0;
    }      
    else{
        bOnLuLd=0;         
	    if(IN_LU && IN_LD){
	        LuLdTime=0;
			bFirstOnLuLd=0;
			lu_ld_state=2;
		}
/////////////////////////////////////////////////
	    else if(IN_LU && !IN_LD){
			if(bCarUpMove){
				lu_ld_state=1;
			}
			else if(bCarDnMove){
				lu_ld_state=3;
			}
		}
	    else if( !IN_LU && IN_LD){
			if(bCarUpMove){
				lu_ld_state=3;
			}
			else if(bCarDnMove){
				lu_ld_state=1;
			}
		}
	}


    if(!IN_LU || !IN_LD)	bOneLuOrLd=1;
    else					bOneLuOrLd=0;




#ifndef  TEST_SIMULATION  
//	if(bFhmRun || (bAuto && !bManualAuto)){
	if(bFhmRun){
		if(bMoveCar){	
			if( (lu_ld_state != LuLdSeq[LuLdSeqPt]) && (lu_ld_state <= 3) ){
				bef_lu_ld_state=LuLdSeq[LuLdSeqPt];
			
				LuLdSeqPt=(LuLdSeqPt + 1) % 4;
				LuLdSeq[LuLdSeqPt]=lu_ld_state;
				LuLdSeqMinCnt++;
				if(LuLdSeqMinCnt >= 4){
					bef_lu_ld_state=(bef_lu_ld_state + 1) % 4;	
					if(lu_ld_state != bef_lu_ld_state)	err=1;	
					LuLdSeqMinCnt=5;
				}
			}
				
			if(err){
				if(bCarUpMove)		LuLdErrSave(1);
				else				LuLdErrSave(0);
	
				bCarStopNoRun=1;   
			}
		}
		else{
			LuLdSeqMinCnt=0;
			LuLdSeqPt=0;
		}
	}
	else{
		bsLuOrLdErr=0;
		LuLdSeqMinCnt=0;
		LuLdSeqPt=0;
		LuLdErrNm=0;	
	}

#else
	LuLdErrNm=0;	
	bsLuOrLdErr=0;
//	bLuOrLdErr=0;
	LuLdSeqMinCnt=0;
	LuLdSeqPt=0;
#endif

}       





void __attribute__((section(".usercode")))  OverLoadCheck(void)
{
    if(IN_OVL && !bMoveCar && (!IN_LU || !IN_LD) && !bDoorCloseOk && bAuto){      
        S1_OVERLOAD1=1;
        if(IN_FR1){         
            bMoveOk=0;
            bMoveUpOk=0;
            bMoveDnOk=0;

			if(sRamDArry[mDoorSeq] >= DOOR_OPEN_WAIT){
	            sRamDArry[mDoorSeq]=DOOR_OPEN_START;      
	            DoorOpenTime=0;                 
			}	
      
//////////// sRamDArry[mDoorSeq]=DOOR_OPEN_START;
//            DoorOpenTime=0;                 

            if(sRamDArry[mSysStatus] >= sOVL)   sRamDArry[mSysStatus]=sOVL;            
        }
    }
    else{
        S1_OVERLOAD1=0;         
    }
}


/*
unsigned int    __attribute__((section(".usercode")))   AutoParkingCheck(void)
{    

    LocalType tmphour;

    tmphour=(sRamDArry[Hour] >> 4);
    tmphour=(tmphour * 10);
    tmphour=((sRamDArry[Hour] & 0x000f) + tmphour);

    if(cF_ParkingStart < cF_ParkingEnd){
        if((cF_ParkingStart <= tmphour) && (cF_ParkingEnd > tmphour))   return(1);
    }
    else if(cF_ParkingStart > cF_ParkingEnd){
        if(cF_ParkingStart <= tmphour)                                  return(1);
        else if(cF_ParkingEnd > tmphour)                                return(1);
    }

    return(0);
}
*/


unsigned int    __attribute__((section(".usercode"))) ParkingValidCheck(void)
{
	if(IN_PRK || bPC_PRK || bSlavePrk){
		return(1);
    }
    else    return(0);
}



void  __attribute__((section(".usercode"))) ParkingCheck(void)
{
	S4_PARKING_READY1=0;

	if(S3_PARKING1 && (ParkingValidCheck()) && !S2_FIRE1 && (!IN_LU || !IN_LD) ){      

		if(sRamDArry[mSysStatus] >= sPARKING)   sRamDArry[mSysStatus]=sPARKING; 
            
        if(!bDoorCloseOk){
        	bMoveOk=0;
        	bMoveUpOk=0;
        	bMoveDnOk=0; 
        }
     
    	bExtButClr=1;
    	bCarButClr=1;
    	bTestKey=0;
   		sRamDArry[mEqualFloor] = 0;
   		sRamDArry[mHighFloor] = 0;
   		sRamDArry[mLowFloor] = 0;
    	
	                        
   		if(!OpenKeyCheck()){
       		sRamDArry[mDoorSeq] = DOOR_OPEN_START;      		         
            S3_PARKING1=0;
   		}
  	}
  	else if((ParkingValidCheck() || bPC_PRK) && bAuto && !S2_FIRE1 && (!IN_LU || !IN_LD) ){
   		if(sRamDArry[mcurfloor]== cF_PRKFLR){
       		if((sRamDArry[mDoorSeq] >= DOOR_CLOSE_END) && bDoorCloseOk && (sRamDArry[mDoorSeq] <= READY_ELEVATOR)){
                S3_PARKING1=1;   
	    		OpenKeyCheck();
       		}                     
	   		else if( (sRamDArry[mDoorSeq] >= DOOR_OPEN_WAIT) && !bMoveCar){
				S4_PARKING_READY1=1;
			}                      
   		}
   		else if(!ReadyAndNoKeyCheck()){
   			Virtual_Floor_Set(cF_PRKFLR);
		}
  	}
  	else{
   		if(S3_PARKING1){
			sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_SUB_OPEN_KEY_CLEAR);   
			if(bSubSlavePrk)	sRamDArry[mDoor]=( sRamDArry[mDoor] | SUB_OPEN_KEY);                            
			else				sRamDArry[mDoor]=( sRamDArry[mDoor] | MAIN_OPEN_KEY);                            
       		sRamDArry[mDoorSeq] = DOOR_OPEN_START;      		             
   		}    		
   		S3_PARKING1=0;
		bSubSlavePrk=0;
  	}
}



void  __attribute__((section(".usercode"))) MyFamilyServiceCheck(void)
{      

	S4_FAMILY_SERVICE1=0;
	if(bPC_FAMILY){
		S4_FAMILY_SERVICE1=1;
	}

	S4_WAIT_FLR_SERVICE1=0;
	if(CmdFixFlrTime > 0){
    	if(cF_FIXFLOOR <= cF_TOPFLR){		
			S4_WAIT_FLR_SERVICE1=1;
		}
	}
}




void __attribute__((section(".usercode")))  VipCheck(void)
{

    if( (!IN_PASS || bOnceVip) && AutoRunReady()){
        bExtButClr=1;
        S3_VIP1=1;

        if(sRamDArry[mSysStatus] >= sVIP)   sRamDArry[mSysStatus]=sVIP;      

        if((sRamDArry[mDoorSeq] == READY_ELEVATOR) && (sRamDArry[mNewAckStopFloor]==0) ){
            sRamDArry[mDoorSeq] = DOOR_OPEN_START;    
        }                  
    }
    else{   
        S3_VIP1=0;

        bOnceVip=0;
        Vip_Floor=0;
    }    
    
    if(bOnceVip){
        if(((Vip_Floor & ONLY_FLR) != sRamDArry[mcurfloor]) &&  !bMoveCar){
            bOnceVip=0;
            Vip_Floor=0;
        }  
    }
        
}



void __attribute__((section(".usercode")))  FullCheck(void)
{

    if(!SubSafetyUseChk){
		if(!AutoRunReady())	S3_FULL1=0;
		else{
			if(!bDoorCloseOk || !bMoveCar){
		        if(!IN_FULL){
		            S3_FULL1=1;
		            if( !(sRamDArry[mHighFloor] & CAR_READY))	sRamDArry[mHighFloor]=0;
		            if( !(sRamDArry[mLowFloor]  & CAR_READY))	sRamDArry[mLowFloor]=0;
		        }
		        else{   
		            S3_FULL1=0;
		        }
			}
		}
    }
    else	S3_FULL1=0;

}


/*
UserDataType __attribute__((section(".usercode")))  SubDoorTimer(void)
{
    if(IN_X7)	return(1);
	else		return(0);
}
*/


UserDataType __attribute__((section(".usercode")))  SubFireCheck(void)
{
    if(USE_CHECK == BAGGAGE_USE)    return(0);
    if(USE_CHECK == CARLIFT_USE)   	return(0);
    if(INVERTER_CHECK == D_F)		return(0);                                             

    if(!IN_X7 && (cF_X7SAFEFLR <= cF_TOPFLR)){
		FireBaseFloor=cF_X7SAFEFLR;    
    	return(1);         
	}
    else if(!IN_X6 && (cF_X6SAFEFLR <= cF_TOPFLR)){
		FireBaseFloor=cF_X6SAFEFLR;    
    	return(1);         
	}
    else if(!IN_X5 && (cF_X5SAFEFLR <= cF_TOPFLR)){
		FireBaseFloor=cF_X5SAFEFLR;    
    	return(1);         
	}
    else                          	return(0);
}

UserDataType __attribute__((section(".usercode")))  UpLimitSpeedCheck(void)
{
    if(USE_CHECK == BAGGAGE_USE)    return(0);
    if(USE_CHECK == CARLIFT_USE)   	return(0);
    if(INVERTER_CHECK == D_F)		return(0);                                             

    if(!IN_X1)                     	return(1);         
    else                           	return(0);
}


UserDataType __attribute__((section(".usercode")))  DnLimitSpeedCheck(void)
{	
    if(USE_CHECK == BAGGAGE_USE)    return(0);
    if(USE_CHECK == CARLIFT_USE)   	return(0);
    if(INVERTER_CHECK == D_F)		return(0);                                             

    if(!IN_X0)                     	return(1);         
    else                           	return(0);
}



UserDataType __attribute__((section(".usercode")))  KidsKeyCheck(void)
{
	UserDataType	i,j,k,l;
		
    if(USE_CHECK == BAGGAGE_USE)	return(0);
    if(USE_CHECK == CARLIFT_USE)   	return(0);
    if(INVERTER_CHECK == D_F)		return(0);                                             
	if(cF_KIDS_KEY_CNT <= 1)		return(0);
    if(!IN_X2 || !KidsKeyChkUse)   	return(0);         
	
	j=mCarKey1-1;
	k=0;
	for(i=0;i <= cF_TOPFLR;i++){
		if( !(i % 8)){
			l=0x01;		
			j++;	
		}

		if(sRamDArry[j] & l){
			k++;
		}
		l=(l << 1);
	}	

	if(k > cF_KIDS_KEY_CNT)	bCarUpDnChButClr=1;														

	return(0);
}



UserDataType __attribute__((section(".usercode")))  CarKeyMostServiceCheck(void)
{

	if(bMoveCar)	return(0);
						
	S4_CAR_MOST_SERVICE1=0;
	
    if(!CarKeyFirstService)   return(0);         
                                             
	if( !(sRamDArry[mCarKey1] | sRamDArry[mCarKey9] | sRamDArry[mCarKey17] | sRamDArry[mCarKey25]))	return(0);  
	if(!bUpWard && !bDnWard)																		return(0);



/////3.4d
	if( !(sRamDArry[mHighFloor] & CAR_READY))	sRamDArry[mHighFloor]=0x0;					
	if( !(sRamDArry[mLowFloor]  & CAR_READY))	sRamDArry[mLowFloor] =0x0;					

	if(bDoorCloseOk){
		if((sRamDArry[mHighFloor] & UPDN_CAR_READY) ||  (sRamDArry[mLowFloor]  & UPDN_CAR_READY)){
			S4_CAR_MOST_SERVICE1=1;
		}
	}
/////3.4d


/*
	if(!bDoorCloseOk){  	//open
		S4_CAR_MOST_SERVICE1=1;

		if(bUpWard){
        	if(!NextUpDnKeyChk(1)){
				if( !(sRamDArry[mHighFloor] & CAR_READY))	sRamDArry[mHighFloor]=0x0;					
			}
        	else if(!NextUpDnKeyChk(0)){
				sRamDArry[mHighFloor]=0x0;
   				if(sRamDArry[mDoorSeq] >= DOOR_CLOSE_START)	ClrUpDnWard();
			}
		}
		else if(bDnWard){
	        if(!NextUpDnKeyChk(0)){
				if( !(sRamDArry[mLowFloor] & CAR_READY))	sRamDArry[mLowFloor]=0x0;					
			}
        	else if(!NextUpDnKeyChk(1)){
				sRamDArry[mLowFloor]=0x0;										
   				if(sRamDArry[mDoorSeq] >= DOOR_CLOSE_START)	ClrUpDnWard();
			}
		}
	}
	else{
		if(bUpWard){
        	if(!NextUpDnKeyChk(1)){
				S4_CAR_MOST_SERVICE1=1;
				if( !(sRamDArry[mAckStopFloor] & CAR_READY)){				
	            	sRamDArry[mHighFloor] = 0x0;
				}
			}				
			if((sRamDArry[mHighFloor] & CAR_READY) && bMoveCar)	S4_CAR_MOST_SERVICE1=1;
		}
		else{
        	if(!NextUpDnKeyChk(0)){
				S4_CAR_MOST_SERVICE1=1;
				if(!(sRamDArry[mAckStopFloor] & CAR_READY)){				
	            	sRamDArry[mLowFloor] = 0x0;
				}
			}
			if((sRamDArry[mLowFloor] & CAR_READY) && bMoveCar)	S4_CAR_MOST_SERVICE1=1;
		}
	}
*/

	return(0);  
}




void __attribute__((section(".usercode")))  BatCheck(void)
{
    if(!IN_BAT && bAuto){
        if(PowerFailTime > 20){
            PowerFailTime=21;

			if((USE_CHECK == MAN_USE) && bMoveCar){
				if(!IN_X4 && bHomeUpDn)			PowerFailTime=0;                                                                 
				else if(IN_X4 && !bHomeUpDn)	PowerFailTime=0;                                                                 		
			}


            if(bOnLuLd && bDoorOpenEnd && !bMoveCar){
              	ClrUpDnWard();       
                OUT_FAN(0);            
            }
        }

        if(PowerFailTime < 20){
            bCarErr=1;                                                                 
        }

        S1_POWER_FAIL=1;
        NextFloorTime=0; 
    }
    else{
        if(S1_POWER_FAIL){
            if(PowerFailTime > 40){
                PowerFailTime=41;
                S1_POWER_FAIL=0;
                if(INVERTER_CHECK == IO){                                             
                    OUT_P4(0);                                             
                }
            }
            else{
                if(INVERTER_CHECK == IO){                                             
                    OUT_P4(0);                                             
                }
                bCarErr=1;
            }
        }
        else{                    
            PowerFailTime=0;
        }
    }     
}



unsigned int  __attribute__((section(".usercode")))   ReLevelCheck(void)
{

    if(RelevelTime > RELEVEL_TIME){
		bRelevelErr=1;
	}

    if( (IN_LU && IN_LD)  && bLevelFind){
		bRelevelErr=1;
        bCarErr=1;   
        bCarStopNoRun=1;
	}

    if(bManualAuto)								bLevelFind=0;
    if(IN_LU && IN_LD)  						bLevelFind=0;
    if(!IN_LU && !IN_LD)  						RelevelTime=0;


	if(bRelevelErr==0){
		if(RelevelUseChk == 0){
			bLevelFind=0;	
			return(0);
		}
	
		if(S1_OVERLOAD1){
			bLevelFind=0;
			return(0);
		}
	}


    if(bAuto && !bManualStop && RelevelUseChk && !bOnLuLd && bOneLuOrLd ){
        if((sRamDArry[mDoorSeq] < READY_ELEVATOR)){ 
            if( bOneLuOrLd  && (RelevelTime < RELEVEL_TIME) ){
                if(bManualAuto){
			        LuLdTime=0;
					bFirstOnLuLd=0;
                    CarOnceStopTime = 31;
                    bManualAuto=0;
                    bLevelFind=1;
                    bDoorCloseOk=1;             

                  	if(!IN_LU && IN_LD)         bHomeUpDn = 1;
                  	else if(IN_LU && !IN_LD)    bHomeUpDn = 0;
                }
            }
            else{
                bRelevelErr=1;
            }
        }
    }


    if(bRelevelErr){
        bLevelFind=0;
    	bMoveOk=0;
    	bMoveUpOk=0;
    	bMoveDnOk=0;
		bCarStopNoRun=1;  				         
    }        
}



void __attribute__((section(".usercode")))  InputCheck(void)
{
    EmgDlsUlsCheck();   
    ReLevelCheck();
	DoorCloseOkCheck();
    OverLoadCheck();
    ParkingCheck();
	MyFamilyServiceCheck();
    VipCheck();
    FullCheck();
    LuLdOnCheck();      
    BatCheck();

//   MainLoopTime=0;      
}








void __attribute__((section(".usercode")))  AutoManualCheck(void)
{

    if(IN_AUTO || (WarmingUpTime<100) || (sRamDArry[LD_INSP] == 0x55) || ManWorkingChk){
        if(S1_AUTO1){
            if(bMoveCar)    bCarErr=1;
            else            bCarStop=1;
        }
        S1_AUTO1=0;
       	bExtButClr=1;
        bCarButClr=1;   
        bAuto=0;

		sRamDArry[mSysStatus]=sREADY;                              						
    }      
    else{
	    if(bFhmRun && (sRamDArry[FHM_SEQ]!= FHM_SEQ_5)){
			bCarStopNoRun=1;
			if(sRamDArry[mSysStatus] >= sFhmError)   sRamDArry[mSysStatus]=sFhmError;                              						
		}
		else{
	        S1_AUTO1=1;
	        bAuto=1;
		}
    }


    if(FhmOnOffChk && (INVERTER_CHECK == IO)){
	    S1_AUTO1=0;
	    bExtButClr=1;
	    bAuto=0;
	    bExtButClr=1;
	    bCarButClr=1;               
    }      
}

 
/*
unsigned int    __attribute__((section(".usercode"))) Speed210Check(void)
{
    unsigned long MinPulse;

    if(cF_SPEED210 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_210);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}



unsigned int    __attribute__((section(".usercode"))) Speed180Check(void)
{
    unsigned long MinPulse;

    if(cF_SPEED180 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_180);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}
*/


unsigned int    __attribute__((section(".usercode"))) Speed150Check(void)
{
    unsigned long MinPulse;

    if(cF_SPEED150 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_150);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed120Check(void)
{

    unsigned long MinPulse;

    if(cF_SPEED120 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_120);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed105Check(void)
{

    unsigned long MinPulse;

    if(cF_SPEED105 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_105);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}



unsigned int    __attribute__((section(".usercode"))) Speed90Check(void)
{

    unsigned long MinPulse;

    if(cF_SPEED90 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_90);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed60Check(void)
{
    unsigned long MinPulse;

    if(cF_SPEED60 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_60);

    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}


unsigned int    __attribute__((section(".usercode"))) Speed45Check(void)
{

    unsigned long MinPulse;

    if(cF_SPEED45 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_45);

    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}

unsigned int    __attribute__((section(".usercode"))) Speed30Check(void)
{
    unsigned long MinPulse;

    if(cF_SPEED30 == 0)    return(2);     

    MinPulse=GET_LONG(MIN_DEC_PULSE_30);
    if(MinPulse==0) 		return(1);

    if(TotalPulse>MinPulse) return(0);
    else                    return(1);
}






unsigned int  __attribute__((section(".usercode")))   SpeedChange(void)
{
    LocalType     ret;
    ret=1;

    switch(cF_ELEV_SPEED){
        case    SPEED_45:
            if(!Speed45Check() && (CurSpeed < SPEED_45)){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            break;     
        case    SPEED_60:
            if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
            else if(!Speed45Check() && (CurSpeed < SPEED_45)){
                CurSpeed=SPEED_45;
                DecreasePulse=GET_LONG(DEC_PULSE_45);
                ret=0;
            }
            break;     
        case    SPEED_90:
            if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
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
            else if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
            break;     
        case    SPEED_120:
            if(!Speed120Check() && (CurSpeed < SPEED_120)){
                CurSpeed=SPEED_120;
                DecreasePulse=GET_LONG(DEC_PULSE_120);
                ret=0;
            }
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
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
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
            break;     
        case    SPEED_180:
/*
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
            else if(!Speed90Check() && (CurSpeed < SPEED_90)){
                CurSpeed=SPEED_90;
                DecreasePulse=GET_LONG(DEC_PULSE_90);
                ret=0;
            }
            else if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
*/
            break;     
        case    SPEED_210:
/*

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
            else if(!Speed60Check() && (CurSpeed < SPEED_60)){
                CurSpeed=SPEED_60;
                DecreasePulse=GET_LONG(DEC_PULSE_60);
                ret=0;
            }
*/
            break;     
        default:
            break;
    }        


    if(ret==0){
        if(bCarUpMove)  StopMinimumPulse=DecreasePulse+CurPulse;
        else            StopMinimumPulse=CurPulse-DecreasePulse;
    }

    return(ret);
}




unsigned int  __attribute__((section(".usercode")))   SpeedSet(void)
{
    unsigned long tmppulse1,tmppulse2;
    LocalType     j,want_updn,ret;


NoStart=0;

    if(INVERTER_CHECK == LG)    return(0);
    if(INVERTER_CHECK == D_F)   return(0);


    ret=0;
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
    else    ret=5;    

    
    if(ret==0){
		ret=5;   //yousangyong

        switch(cF_ELEV_SPEED){
            case    SPEED_30:
                if(!Speed30Check()){
                    CurSpeed=SPEED_30;
                    DecreasePulse=GET_LONG(DEC_PULSE_30);

//                	if(cF_SPEED30 == 0) ret=2;
//					else				ret=0;

					ret=0;
                }    
				else	ret=4;

                if((cF_SPEED30 == 0))	ret=2;

                break;     
            case    SPEED_45:
                if(!Speed45Check()){
                    CurSpeed=SPEED_45;
                    DecreasePulse=GET_LONG(DEC_PULSE_45);
                    ret=0;
                }
                else if(!Speed30Check()){
                    CurSpeed=SPEED_30;
                    DecreasePulse=GET_LONG(DEC_PULSE_30);
                    ret=0;
                }
				else	ret=4;
				
               if((cF_SPEED30 == 0) && (cF_SPEED45 == 0))	ret=2;

/*
                if(ret==0){
                    switch(CurSpeed){
                        case    SPEED_45:
                            if(cF_SPEED45==0)               ret=2;
                            break;
                        case    SPEED_30:
                            if(cF_SPEED30 == 0)             ret=2;
                            if(cF_SPEED30 == cF_SPEED45)    ret=2;
                            break;
                        default:
                            ret=2;
                            break;
                    }
                }
*/
                break;     
            case    SPEED_60:
                if(!Speed60Check()){
                    CurSpeed=SPEED_60;
                    DecreasePulse=GET_LONG(DEC_PULSE_60);
                    ret=0;
                }
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
				else	ret=4;

                if((cF_SPEED30 == 0) && (cF_SPEED45 == 0) && (cF_SPEED60 == 0))	ret=2;

/*    
                if(ret==0){
                    switch(CurSpeed){
                        case    SPEED_60:
                            if(cF_SPEED60==0)   ret=2;
                            break;
                        case    SPEED_45:
                            if(cF_SPEED45 == 0)             ret=2;
                            if(cF_SPEED45 == cF_SPEED60)    ret=2;
                            break;
                        case    SPEED_30:
                            if(cF_SPEED30 == 0)             ret=2;
                            if(cF_SPEED30 == cF_SPEED45)    ret=2;
                            if(cF_SPEED30 == cF_SPEED60)    ret=2;
                            break;
                        default:
                            ret=2;
                            break;
                    }
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
                else if(!Speed45Check()){
                    CurSpeed=SPEED_45;
                    DecreasePulse=GET_LONG(DEC_PULSE_45);
                    ret=0;
                }
 				else	ret=4;

                if((cF_SPEED45 == 0) && (cF_SPEED60 == 0) && (cF_SPEED90 == 0))	ret=2;

/*   
                if(ret==0){
                    switch(CurSpeed){
                        case    SPEED_90:
                            if(cF_SPEED90==0)   ret=2;
                            break;
                        case    SPEED_60:
                            if(cF_SPEED60 == 0)             ret=2;
                            if(cF_SPEED60 == cF_SPEED90)    ret=2;
                            break;
                        case    SPEED_45:
                            if(cF_SPEED45 == 0)             ret=2;
                            if(cF_SPEED45 == cF_SPEED60)    ret=2;
                            if(cF_SPEED45 == cF_SPEED90)    ret=2;
                            break;
                        default:
                            ret=2;
                            break;
                    }
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
				else	ret=4;

                if((cF_SPEED60 == 0) && (cF_SPEED90 == 0) && (cF_SPEED105 == 0))	ret=2;

/*
                if(ret==0){
                    switch(CurSpeed){
                        case    SPEED_105:
                            if(cF_SPEED105==0)              ret=2;
                            break;
                        case    SPEED_90:
                            if(cF_SPEED90 == 0)             ret=2;
                            if(cF_SPEED90 == cF_SPEED105)   ret=2;
                            break;
                        case    SPEED_60:
                            if(cF_SPEED60 == 0)             ret=2;
                            if(cF_SPEED60 == cF_SPEED90)    ret=2;
                            if(cF_SPEED60 == cF_SPEED105)   ret=2;
                            break;
                        default:
                            ret=2;
                            break;
                    }
                }
*/
                break;     
            case    SPEED_120:
                if(!Speed120Check()){
                    CurSpeed=SPEED_120;
                    DecreasePulse=GET_LONG(DEC_PULSE_120);
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
				else	ret=4;

                if((cF_SPEED60 == 0) && (cF_SPEED90 == 0) && (cF_SPEED120 == 0))	ret=2;

/*
                if(ret==0){
                    switch(CurSpeed){
                        case    SPEED_120:
                            if(cF_SPEED120==0)              ret=2;
                            break;
                        case    SPEED_90:
                            if(cF_SPEED90 == 0)             ret=2;
                            if(cF_SPEED90 == cF_SPEED120)   ret=2;
                            break;
                        case    SPEED_60:
                            if(cF_SPEED60 == 0)             ret=2;
                            if(cF_SPEED60 == cF_SPEED90)    ret=2;
                            if(cF_SPEED60 == cF_SPEED120)   ret=2;
                            break;
                        default:
                            ret=2;
                            break;
                    }
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
				else	ret=4;

                if((cF_SPEED60 == 0) && (cF_SPEED90 == 0) && (cF_SPEED120 == 0) && (cF_SPEED150 == 0))	ret=2;

/*
                if(ret==0){
                    switch(CurSpeed){
                        case    SPEED_150:
                            if(cF_SPEED150==0)              ret=2;
                            break;
                        case    SPEED_120:
                            if(cF_SPEED120==0)              ret=2;
                            if(cF_SPEED120 == cF_SPEED150)  ret=2;
                            break;
                        case    SPEED_90:
                            if(cF_SPEED90 == 0)             ret=2;
                            if(cF_SPEED90 == cF_SPEED150)   ret=2;
                            if(cF_SPEED90 == cF_SPEED120)   ret=2;
                            break;
                        case    SPEED_60:
                            if(cF_SPEED60 == 0)             ret=2;
                            if(cF_SPEED60 == cF_SPEED90)    ret=2;
                            if(cF_SPEED60 == cF_SPEED120)   ret=2;
                            if(cF_SPEED60 == cF_SPEED150)   ret=2;
                            break;
                        default:
                            ret=2;
                            break;
                    }
                }
*/
                break;     
            case    SPEED_180:
/*
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
				else	ret=4;

                if((cF_SPEED60 == 0) && (cF_SPEED90 == 0) && (cF_SPEED120 == 0) && (cF_SPEED150 == 0)  && (cF_SPEED180 == 0))	ret=2;
*/
        
                ret=3;  //// not use
    
                break;     
            case    SPEED_210:

/*

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

                if((cF_SPEED60 == 0) && (cF_SPEED90 == 0) && (cF_SPEED120 == 0) && (cF_SPEED150 == 0)  && (cF_SPEED180 == 0)   && (cF_SPEED210 == 0))	ret=2;
*/


                ret=3;      //// not use
                break;     
            default:
                ret=1;
                break;
        }        
    }


    if(ret==0){
        if(want_updn==1){           //up want
            StopMinimumPulse=DecreasePulse + CurPulse;
            
            j=cF_TOPFLR;
            tmppulse1=FLOOR_COUNT(j);    
            if(StopMinimumPulse > (tmppulse1 - DecreasePulse)){
                ret=4;      //false
            }       
        }
        else if(want_updn==2){           //dn want
            StopMinimumPulse=CurPulse-DecreasePulse;

            tmppulse1=FLOOR_COUNT(0);    
            if(StopMinimumPulse < (tmppulse1 + DecreasePulse)){
                ret=4;      //false
            }       
        }
        else    ret=5;
    }
    

    if(ret){
        switch(ret){
            case    1:
			    if(sRamDArry[mSysStatus] > sSpeedSetError)  sRamDArry[mSysStatus]=sSpeedSetError;      
                break;
            case    2:
			    if(sRamDArry[mSysStatus] > sSpeedPortError) sRamDArry[mSysStatus]=sSpeedPortError;      
                break;
            case    3:
			    if(sRamDArry[mSysStatus] > sNoUseSpeed)     sRamDArry[mSysStatus]=sNoUseSpeed;      
                break;
            case    4:
			    if(sRamDArry[mSysStatus] > sMinLengthErr)   sRamDArry[mSysStatus]=sMinLengthErr;      
                break;
            case    5:
			    if(sRamDArry[mSysStatus] > sSystemErr)      sRamDArry[mSysStatus]=sSystemErr;      
                break;
        }

		NoStart=ret;
    }


    return(ret);

/********************
//ret==1    : SpeedSetError
//ret==2    : SpeedPortError
//ret==3    : No Use
//ret==4    : MinLengthErr
//ret==5    : SystemErr
********************/
}

      
void __attribute__((section(".usercode")))  AutoUpDownStart(void)
{   
    if(sRamDArry[mAckStopFloor]){  
        if((sRamDArry[mAckStopFloor] & 0x1f) > sRamDArry[mcurfloor]){
            if(sRamDArry[mCarMoveState]==0){
                if(bMoveUpOk)   MvCounter();
            }    
            CarUpStartCmd(); 
        }                         
        else if((sRamDArry[mAckStopFloor] & 0x1f) < sRamDArry[mcurfloor]){
            if(sRamDArry[mCarMoveState]==0){
                if(bMoveDnOk)   MvCounter();
            }
            CarDnStartCmd();
        }       
    }
}



unsigned int	__attribute__((section(".usercode"))) LoadCmdStartCheck(void)
{

	if(!AutoRunReady())								return(0);


/*
	if((sRamDArry[mVFlr1] != sRamDArry[mVFlr2]) && (sRamDArry[mVFlrCnt] > 0)){
		if((cF_FLRDSPCH(0) == 'Z') && (cF_FLRDSPCH(1) == 'Z')){		
			AccTimer=0;
			sRamDArry[ExtCmdFlrONOFF0]=0x0;	
			sRamDArry[ExtCmdFlrONOFF1]=0x0;	
			sRamDArry[ExtCmdFlrONOFF2]=0x0;	
			sRamDArry[ExtCmdFlrONOFF3]=0x0;
		}	
	}
*/



   	if(bCarUpMove || bCarDnMove)					return(0);        	

#ifdef  KTL  
     sRamDArry[mVFlrCnt]= 254;
     sRamDArry[mVFlr1] 	= cF_TOPFLR+1;
     sRamDArry[mVFlr2] 	= 1;
#else
	if(sRamDArry[mVFlrCnt] == 0)					return(0);
	if(sRamDArry[mVFlrCnt] > 254)					return(0);
	if( !(sRamDArry[mVFlr1] | sRamDArry[mVFlr2]))	return(0);

	if(sRamDArry[mVFlrCnt] > 250)	sRamDArry[mVFlrCnt] = 254;
#endif

	if(sRamDArry[mLowFloor]  & UPDN_CAR_READY)		return(0);	
	if(sRamDArry[mHighFloor] & UPDN_CAR_READY)		return(0);



		if((sRamDArry[mVFlr1] != sRamDArry[S0_FLOOR]) && (sRamDArry[mVFlr1] > 0) && (sRamDArry[mVFlr1] <= (cF_TOPFLR+1))){
			Virtual_Floor_Set(sRamDArry[mVFlr1] -1);	
		}    
		if((sRamDArry[mVFlr2] != sRamDArry[S0_FLOOR]) && (sRamDArry[mVFlr2] > 0) && (sRamDArry[mVFlr2] <= (cF_TOPFLR+1))){
			Virtual_Floor_Set((sRamDArry[mVFlr2] -1));	
		}    

	return(0);      
}


unsigned int __attribute__((section(".usercode"))) TimeCmpare(unsigned int i_basetime,unsigned int i)
{
    LocalType     Tmp_timeH,Tmp_timeM,Tmp_Stime,Tmp_Etime;
    LocalType     i_localtime;

	Tmp_timeH=cF_FLRDSPCH((unsigned long)(F_0506 + i + 0));
	if(Tmp_timeH >= 24)	return(0);
	Tmp_timeM=cF_FLRDSPCH((unsigned long)(F_0506 + i + 1));
	if(Tmp_timeM >= 60)	return(0);
	Tmp_Stime=( (Tmp_timeH << 8) | Tmp_timeM);


	Tmp_timeH=cF_FLRDSPCH((unsigned long)(F_0506 + i + 2));
	if(Tmp_timeH >= 24)	return(0);
	Tmp_timeM=cF_FLRDSPCH((unsigned long)(F_0506 + i + 3));
	if(Tmp_timeM >= 60)	return(0);
	Tmp_Etime=( (Tmp_timeH << 8) | Tmp_timeM);


	if(Tmp_Stime == Tmp_Etime)	return(0);
	if(Tmp_Stime == 0)			return(0);
	if(Tmp_Etime == 0)			return(0);

	
	if( (i_basetime >= Tmp_Stime) && (i_basetime < Tmp_Etime)){
		return(1);
	} 

	return(0);
}



unsigned int	__attribute__((section(".usercode"))) FixFloorStartTimeCheck(void)
{
    LocalType     cTime,cMin;

	cTime=0;

	if( (CmdFixFlrTime > 0)){
	    cTime=(((sRamDArry[Hour] & 0xf0) >> 4) * 10);
	    cTime=((sRamDArry[Hour] & 0x0f) + cTime);
	    cMin=(((sRamDArry[Minuate] & 0xf0) >> 4) * 10);
	    cMin=((sRamDArry[Minuate] & 0x0f) + cMin);		
		if((cTime < 24) && (cMin < 60)){	
			cTime=((cTime << 8) | cMin);

//			if(cTime > 0){
//				return(cTime);	
//			}
		}
	}
	return(cTime);	
}


unsigned int	__attribute__((section(".usercode"))) FixFloorStartCheck(void)
{

#ifndef	TEMP_GUEN

    LocalType     TmpFlrBuf;
    LocalType     cTime;



	if(S3_PARKING1)					return(0);
   	if(bCarUpMove || bCarDnMove)	return(0);        	


	TmpFlrBuf=0xff;
	cTime=FixFloorStartTimeCheck();

	if(cTime > 0){
		if(TimeCmpare(cTime,0)){
			TmpFlrBuf=cF_FLRDSPCH((unsigned long)(F_0506 +  4));
		}
		else if(TimeCmpare(cTime,5)){
			TmpFlrBuf=cF_FLRDSPCH((unsigned long)(F_0506 +  9));
		}
		else if(TimeCmpare(cTime,10)){
			TmpFlrBuf=cF_FLRDSPCH((unsigned long)(F_0506 +  14));
		}


		if((TmpFlrBuf <= cF_TOPFLR) && (FixFlrTimeCnt >= CmdFixFlrTime) && (TmpFlrBuf != sRamDArry[mcurfloor])){
			Virtual_Floor_Set(TmpFlrBuf);
			return(0);
		}
		else	TmpFlrBuf=0xff;
	}


    if(TmpFlrBuf==0xff){
    	if((CmdFixFlrTime > 0) && (cF_FIXFLOOR <= cF_TOPFLR) && (cF_FIXFLOOR != sRamDArry[mcurfloor])){		
			if(FixFlrTimeCnt >= CmdFixFlrTime){
    			Virtual_Floor_Set(cF_FIXFLOOR);
			}
    	}
    }
#endif

	return(0);
}




void __attribute__((section(".usercode")))  UpDnDirectionSet(void)
{
/*	
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
*/

    if(!bUpWard && !bDnWard){ 
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

/*
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
*/


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


LocalType  __attribute__((section(".usercode"))) UpMoveCheck(void)
{
    LocalType   i;

    i=0;    
    if(bsUls)                                                       i=1;
    if(!(sRamDArry[mHighFloor] & UPDN_CAR_READY))                   i=1;
    if( (sRamDArry[mHighFloor] & ONLY_FLR) <= sRamDArry[mcurfloor]) i=1;

    return(i);
}



LocalType  __attribute__((section(".usercode"))) DnMoveCheck(void)
{
    LocalType   i;

    i=0;
    
    if(bsDls)                                                       i=1;
    if(!(sRamDArry[mLowFloor] & UPDN_CAR_READY))                    i=1;
    if( (sRamDArry[mLowFloor] & ONLY_FLR) >= sRamDArry[mcurfloor])  i=1;

    return(i);
}



void  __attribute__((section(".usercode"))) AutoDoorSystem(void)
{

	if(SafetyChk() || 	(!OpenKeyCheck())){

        S3_PARKING1=0;          
        sRamDArry[mDoor]= (sRamDArry[mDoor] & MAIN_SUB_CLOSE_KEY_CLEAR);
    		    		         
     	if(sRamDArry[mDoorSeq] >= DOOR_OPEN_WAIT){         
            if(USE_CHECK == MAN_USE){      
                if(sRamDArry[mDoorSeq] >= DOOR_REOPEN_CHECK){         
                   	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
                    DoorOpenTime=0;
		            bReOpen=1;


					if(OpenOutSet){  
		            	bReOpen=0;
					}

        
         			if(!bUpWard && !bDnWard){                                 		   	
         				if(sRamDArry[mEqualFloor] & UP_READY)		bReOpen=0;
         	      		else if(sRamDArry[mEqualFloor] & DN_READY)	bReOpen=0;
         			}      
               		else if((bUpWard) && (sRamDArry[mEqualFloor] & UP_READY))	bReOpen=0;
               		else if((bDnWard) && (sRamDArry[mEqualFloor] & DN_READY))	bReOpen=0;
                }
            }
            else{
               	sRamDArry[mDoorSeq]=DOOR_OPEN_START;
                DoorOpenTime=0;
                bReOpen=1;
            }


            if(SafetyChk()){
                if(sRamDArry[mSysStatus] > sSFT)   sRamDArry[mSysStatus]=sSFT;      
            } 

      	}  
	}         
	else if(!CloseKeyCheck()){
         if(sRamDArry[mDoorSeq] < DOOR_CLOSE_START){
	         if(bOpenDoorOk || (sRamDArry[mDoorSeq] >= DOOR_OPEN_WAIT) ){
#ifdef	L_K_J
	         	if(!bDoorJumper && !bDoorCloseOk){
#else
	         	if(!bDoorJumper && !bDoorCloseOk && !bOutDate && !bMotor_Overheat){
#endif
	                DoorOpenTime = cF_OPWTTM+cF_REOPTM+1;
		         	sRamDArry[mDoorSeq]=DOOR_CLOSE_START;
					DoorCloseTime=0;      
				}     	          
	         }
		 }
         sRamDArry[mDoor]= (sRamDArry[mDoor] & MAIN_SUB_CLOSE_KEY_CLEAR);            
	}


  
//	AutoUpDnDirectionSet();
	

    if(sRamDArry[mDoorSeq] == READY_ELEVATOR){          
        if(bUpWard){
            if(!UpMoveCheck()){
                OneStopKey();

				#ifdef	TEMP_GUEN
                    OneStopKey_GUEN();
				#endif

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
            if(!DnMoveCheck()){
				OneStopKey();

				#ifdef	TEMP_GUEN
                    OneStopKey_GUEN();
				#endif

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
}   





//20051008insert
void __attribute__((section(".usercode"))) 	NoButtonAndDefaultLoad(void)
{
	if(sRamDArry[mReqStopFloor] & CAR_READY){
		sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mReqStopFloor];
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

    j=(sRamDArry[mHighFloor] & UPDN_CAR_READY);
    k=(sRamDArry[mLowFloor] & UPDN_CAR_READY);

    if(bCarUpMove && (j==0)){    		
		NoButtonAndDefaultLoad();
	}
    else if(bCarDnMove && (sRamDArry[mLowFloor]==0)){    
		NoButtonAndDefaultLoad();
	}
   	else if(!(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
		NoButtonAndDefaultLoad();	
	}
	else{   
       	if(bCarUpMove && (sRamDArry[mHighFloor] & UPDN_CAR_READY) && ((sRamDArry[mHighFloor] & ONLY_FLR) <= cF_TOPFLR)){    
            j=(sRamDArry[mHighFloor] & ONLY_FLR);
			if(INVERTER_CHECK == D_F){
				if(j > sRamDArry[mcurfloor])	i=1;
			}
			else{
	            longtemp1=FLOOR_COUNT(j);
	            if((longtemp1 > CurPulse) && (CurPulse > StopMinimumPulse)){
	                TotalPulse=(longtemp1-CurPulse);
	                if(TotalPulse > DecreasePulse) 	i=1;
	            }
			}
        }
       	else if(bCarDnMove && (sRamDArry[mLowFloor] & UPDN_CAR_READY)){
    		k=(sRamDArry[mLowFloor] & ONLY_FLR);
			if(INVERTER_CHECK == D_F){
				if(k < sRamDArry[mcurfloor])	i=1;
			}
			else{
	            longtemp1=FLOOR_COUNT(k);
	            if((longtemp1 < CurPulse) && (CurPulse < StopMinimumPulse)){
	                TotalPulse=(CurPulse-longtemp1);   
	                if(TotalPulse>DecreasePulse) i=1;
	            }
			}
        }

	    if(i==1){
	        save_CurSpeed=CurSpeed;

	        if(bSetSpeedOn==0)  SpeedChange();        
	
	        if(CurSpeed>save_CurSpeed){        
	            RunSpeedCmd_IO();
	        }
	            
	       	if(bCarUpMove){
	            sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mHighFloor];            																							
				OriginalHighFlr     =sRamDArry[mHighFloor];
	        }
	        else if(bCarDnMove){
	            sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mLowFloor];																							
        		OriginalLowFlr      =sRamDArry[mLowFloor];
	        }	 
	        sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
	    }
		else{
	        sRamDArry[mHighFloor]=OriginalHighFlr;
	        sRamDArry[mLowFloor] =OriginalLowFlr;
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
    if(bCarUpMove && (j==0)){    		
		NoButtonAndDefaultLoad();
	}
    else if(bCarDnMove && (k==0)){    
		NoButtonAndDefaultLoad();
	}
   	else if(!(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
		NoButtonAndDefaultLoad();	
	}
//20051008insert    

	else{
	  	if(bCarUpMove){
	        sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mHighFloor];            																							
	    }
	    else if(bCarDnMove){
	        sRamDArry[DEST_FLR]=sRamDArry[mAckStopFloor] = sRamDArry[mLowFloor];																							
	    }
	
	    sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
//	    sRamDArry[mMostLongDst] = 0;        
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


void   __attribute__((section(".usercode"))) NewFloorLoad(void)
{  	
   	if(bCarUpMove){
   		if(sRamDArry[DEST_FLR] != sRamDArry[mHighFloor]){
			if(!NewUpKeyChk()){
				if(INVERTER_CHECK == LG)    LG_INVERTER_NewFloorLoadCheck();
				else                        IO_INVERTER_NewFloorLoadCheck();
				sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);
				sRamDArry[mMostLongDst] = 0;        
			}				
   		}
   		if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
   	}
   	else if(bCarDnMove){
   		if(sRamDArry[DEST_FLR] != sRamDArry[mLowFloor]){
			if(!NewDnKeyChk()){
				if(INVERTER_CHECK == LG)    LG_INVERTER_NewFloorLoadCheck();
				else                        IO_INVERTER_NewFloorLoadCheck();
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



unsigned int   __attribute__((section(".usercode")))  FhmSuccessCheck(void)
{

	if(sRamDArry[FHM_RUN] == FHM_RUN_CMD){
		if(IN_LU && !IN_LD && !IN_SU1){
			if(FhmToggle && bFhmRun){
				if(sRamDArry[FHM_SEQ]== FHM_SEQ_5){ 
					return(0);
				}
			}					
		}
	}

	return(1);
}


void __attribute__((section(".usercode")))  FhmRunCheck(void)
{

    if( !bAuto && IN_AUTO && CounterCheck() && !ManWorkingChk){
//        if( ( (sRamDArry[FHM_RUN] == FHM_RUN_CMD) && (FhmLoaderTime < 10) ) || !IN_FHM){   
        if( ( (sRamDArry[FHM_RUN] == FHM_RUN_CMD) && (FhmLoaderTime < 10) ) ){   
            bFhmRunReset=1;
            bFhmRun=1;
            if(sRamDArry[FHM_SEQ]==0){
                sRamDArry[FHM_SEQ]=FHM_SEQ_0;
            }
        }
        else{
 			bFhmRun=0;
		}
    }
    else{
 		bFhmRun=0;     
	}


//    if((bAuto) || ((sRamDArry[FHM_RUN] == 0) && IN_FHM) ){
    if((bAuto) || ((sRamDArry[FHM_RUN] == 0) ) ){
        bFhmRunReset=0;                
        bFhmRun=0;
    }
}




void __attribute__((section(".usercode")))  ManualUpDnKeyCheck(void)
{
	LocalType KeyTime;
	unsigned int  x,y;
	unsigned long i,j;
 
  
	if(bAuto)      KeyTime=30;
	else           KeyTime=5;
      
	if(!IN_U_B && IN_D_B){
		if(UpBttonTime >= KeyTime){
			UpBttonTime = KeyTime;                  
			bManualUpKey=1;
		}                
		DnBttonTime=0;     
	}         
	else if(!IN_D_B && IN_U_B){                  
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


		ReadEncoder();

		if(sRamDArry[mSysStatus] >= sFHM_MODE)   sRamDArry[mSysStatus]=sFHM_MODE;        

		switch(sRamDArry[FHM_SEQ]){ 
			case  FHM_SEQ_0:
				if(!IN_DLS){
					if(!IN_LU && IN_LD && !IN_SD1){
						FhmTime=0;
	                    sRamDArry[FHM_SEQ]=FHM_SEQ_3;
					}
					else{
	                    sRamDArry[FHM_SEQ]=FHM_SEQ_2;
					}
				}
				else{
                    sRamDArry[FHM_SEQ]=FHM_SEQ_1;
				}
                if(INVERTER_CHECK == LG) OUT_P4(0);                                             
            
				break;

			case  FHM_SEQ_1:
				if(IN_DLS){
		            if(sRamDArry[mSysStatus] >= sDLS)   sRamDArry[mSysStatus]=sDLS;        
				}
				else if(IN_ULS){
		            if(sRamDArry[mSysStatus] >= sULS)   sRamDArry[mSysStatus]=sULS;        
				}
				else{
		    		if(sRamDArry[mSysStatus] >= sFhmError)   sRamDArry[mSysStatus]=sFhmError;        
				}
	            if(INVERTER_CHECK == LG) OUT_P4(0);
				break;
			case  FHM_SEQ_2:
				if(!IN_DLS){
					if(!IN_LU && IN_LD && !IN_SD1){
						FhmTime=0;
	                    sRamDArry[FHM_SEQ]=FHM_SEQ_3;
					}
					else{
						bManualDnKey=1;
					}
				}
				else{
	            	sRamDArry[FHM_SEQ]=FHM_SEQ_1;
				}
                if(INVERTER_CHECK == LG) OUT_P4(0);                                             
				break;
			case  FHM_SEQ_3:
				if(!IN_LU && IN_LD && !IN_SD1){
					if(FhmTime>20){
                        sRamDArry[FHM_SEQ]=FHM_SEQ_4;
                        if(INVERTER_CHECK == LG) OUT_P4(1);
                        else if(INVERTER_CHECK == IO){
                            for(FhmToggle=0;FhmToggle<32;FhmToggle++){
                                parameter_mirror[FhmToggle]= 0x0fffffff;
                            }
                            FhmToggle=0;
                            sRamDArry[mcurfloor]=0;                                                                   
                        }
					}                    
					else if(FhmTime>10){
                        if(INVERTER_CHECK == LG) OUT_P4(1);
					}                    
            	}  
				else{
                    sRamDArry[FHM_SEQ]=FHM_SEQ_0;
				}        
				break;   
			case  FHM_SEQ_4:
				if(IN_ULS)	sRamDArry[FHM_SEQ]=FHM_SEQ_1;
				else{

					if(IN_LU && !IN_LD && !IN_SU1){
						if(bFhmEncoder){
							bFhmEncoder=0;
	                        LevelEncoderPulse2=CurPulse;
						}

	                	OUT_P3(0);                                                         
	                	OUT_P1(0);                                                         
	                	OUT_P2(0);

	                    if(!bMoveCar){
	                        if(INVERTER_CHECK == LG) OUT_P4(0);
	
	                        if(INVERTER_CHECK == IO){
	                        	LevelEncoderPulse2=(CurPulse - LevelEncoderPulse2);
    							for(i=0;i<32;i++)    parameter_mirror[i] = (parameter_mirror[i] + LevelEncoderPulse1);
								SaveVerify=0x55;
	                            SaveFloorCnt();
	    
	                        }
	    
	    		    		FhmTime=0;
	                        GetFlashDataToBufRam(F_BLOCK1);
	                        b_LdTmpBufRam(F_TopFlr)    = sRamDArry[mcurfloor]; // top floor
	                        bit_LdTmpBufRamReset(F_OnOff0,bFhmOnOff);

	
							SaveVerify=0x55;
	                        flash_write_DspChar(F_BLOCK1);
							SaveVerify=0;


	                        GetFlashDataToBufRam(F_BLOCK2);
        					i_LdTmpBufRam(F_StopPulse0)     = (unsigned int)LevelEncoderPulse1;
							SaveVerify=0x55;
	                        flash_write_DspChar(F_BLOCK2);
							SaveVerify=0;

	                        sRamDArry[FHM_SEQ]=FHM_SEQ_5;
	                    }
					}	
					else{
	                    if(INVERTER_CHECK == LG) OUT_P4(1);
	
						bManualUpKey=1;
	
	                    if(INVERTER_CHECK == IO){
	                        if(!IN_LU && !IN_LD && !FhmToggle){
	                            FhmToggle=1;
	    
	                            if(!IN_SD1){					//modify ?
	                                sRamDArry[mcurfloor]=0;   
									bFhmEncoder=0;                                                                
		                            POSCNT=0;
									BefCurEncoderPulse=0;
		                            CurPulse=BASE_PULSE;        
	                            }
	                            else{ 
	                                sRamDArry[mcurfloor]++;                            
	                            }                        

	                            parameter_mirror[sRamDArry[mcurfloor]] =CurPulse; 
	                        }
	                    
	                        if(IN_LU && !IN_LD && FhmToggle){	
	                            FhmToggle=0;
	                            LevelEncoderPulse2 = CurPulse;                    

	                            if(parameter_mirror[0] != BASE_PULSE){
									bManualUpKey=0;
	                        		sRamDArry[FHM_SEQ]=FHM_SEQ_2;
								}
	                        }

	                        if(IN_LU && IN_LD && !bFhmEncoder && !IN_SD1){
								bFhmEncoder=1;
	                            LevelEncoderPulse1=(CurPulse - parameter_mirror[0]);
	                            LevelEncoderPulse2=(CurPulse - LevelEncoderPulse2);                                	
	                            LevelEncoderPulse1=(LevelEncoderPulse1 / 2);
//								LevelEncoderPulse3=LevelEncoderPulse1;
	                            LevelEncoderPulse2=(LevelEncoderPulse2 / 2);                       
	                            LevelEncoderPulse1=(LevelEncoderPulse1 - LevelEncoderPulse2); 
	                        }
	                    }
					}        
				}
	            DspFloorSet();
				break;               
			case  FHM_SEQ_5:
				if(FhmTime>10){
	                if(FhmToggle == 0){
	                    FhmToggle=1;
	                    FhmTime=20; 
	                    FhmTime=20; 
	                    FhmTime=20; 
	                }                                                               
				}                    
				else if(FhmTime>5){
	                if(INVERTER_CHECK == LG) OUT_P4(0);
	                FhmToggle=0; 
				}                    
				break;

			default:
				sRamDArry[FHM_RUN]=0;
                sRamDArry[FHM_SEQ]=0;
                if(INVERTER_CHECK == LG) OUT_P4(0);                                             
				break;            
		}
        
	}   
	else{
		sRamDArry[FHM_RUN]=0;
        sRamDArry[FHM_SEQ]=0;

        if(INVERTER_CHECK == LG) OUT_P4(0);                                             
	}
   
/*
	if(((sRamDArry[FHM_SEQ]  == FHM_SEQ_4) && (!bMoveUpOk)) || bAuto){
		sRamDArry[FHM_RUN]=0;
        sRamDArry[FHM_SEQ]=0;
	}	        
*/

}



void __attribute__((section(".usercode")))  ManualUpDown(void)
{    
    unsigned int i;
    i=1;

    if(SafetyChk()){
        i=0;        
        if(sRamDArry[mSysStatus] > sSFT)   sRamDArry[mSysStatus]=sSFT;      
    }

	if(bManualUpKey){
		if(!bDoorCloseOk){         
            if(i==1){
            	SelectDoorClose_you();
				if(bAuto)	OUT_ERR(1);
			}
            else if(!IN_LU || !IN_LD)   SelectDoorOpen_you();
		}  
        else if(!bManualStop){                         
    		CarUpStartCmd();    
    		if(!bMoveUpOk){
    			bCarErr=1;
    		}      
        }
        else{
            bCarErr=1;
        }                         
	}          
   	else if(bManualDnKey){
		if(!bDoorCloseOk){
            if(i==1){
            	SelectDoorClose_you();
				if(bAuto)	OUT_ERR(1);
			}
            else if(!IN_LU || !IN_LD)   SelectDoorOpen_you();
        }
        else if(!bManualStop){                         
            CarDnStartCmd();
            if(!bMoveDnOk){                  
                bCarErr=1;
            } 
        }
        else{
            bCarErr=1;
        }                         
    }
    else{
        bCarStop=1;
    }    
}            



unsigned int	__attribute__((section(".usercode")))  OutDateCheck(void)
{    

	bOutDate=0;

	if( !AutoRunReady())			return(1);	

#ifdef	L_K_J
	if(PowerOnTime > 720){
		bOutDate=1;	
	}
#else
	if(cF_year	== 0)				return(1);		
	if(cF_month == 0)				return(1);		
	if(cF_day 	== 0)				return(1);		
	if(cF_month > 0x12)				return(1);		
	if(cF_day 	> 0x31)				return(1);		

	if(sRamDArry[Year]	== 0)		return(1);		
	if(sRamDArry[Month] == 0)		return(1);		
	if(sRamDArry[Day] 	== 0)		return(1);		
	if(sRamDArry[Month] > 0x12)		return(1);		
	if(sRamDArry[Day] 	> 0x31)		return(1);		


	if(sRamDArry[Year]	< cF_year)	return(1);		
	if(sRamDArry[Month]	< cF_month)	return(1);		
	if(sRamDArry[Day]	< cF_day)	return(1);		


	bOutDate=1;	
#endif

	return(0);
}            




unsigned int __attribute__((section(".usercode")))  CheckFloorSensor(void)
{
	LocalType FloorPort;

	bFlrMatchChk=0;

#ifdef	TEST_SIMULATION
	bFlrMatchChk=0;
	return(0);
#else


    if(((USE_CHECK == BAGGAGE_USE) ||  (USE_CHECK == CARLIFT_USE))){ 

		if((sRamDArry[mcurfloor] == 0) && IN_SD1){
			bFlrMatchChk=1;
		}

		if((sRamDArry[mcurfloor] == cF_TOPFLR) && IN_SU1){
			bFlrMatchChk=1;
		}

        if(!IN_SD1 || !IN_SU1){
	        if(!IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
				bFlrMatchChk=1;
	        }

        	if(!IN_SD1 && !IN_SU1){           
				bFlrMatchChk=1;
			}          
			return(0);
		}

		if(!FloorSelMethod){
	        switch(sRamDArry[mcurfloor]){
	            case    1:    
	                if(IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    2:
	                if(IN_X1 || !IN_X0 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    3:
	                if(IN_X2 || !IN_X0 || !IN_X1 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    4:
	                if(IN_X3 || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X4 || !IN_X5 || !IN_X6){
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    5:
	                if(IN_X4 || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X5 || !IN_X6){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    6:
	                if(IN_X5 || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X6){ 
						bFlrMatchChk=1;
	                }                    
	                break;
/*
	            case    7:
	                if((IN_X6 || IN_X0) || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    8:
	                if((IN_X6 || IN_X1) || !IN_X0 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    9:
	                if((IN_X6 || IN_X2) || !IN_X0 || !IN_X1 || !IN_X3 || !IN_X4 || !IN_X5){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    10:
	                if((IN_X6 || IN_X3) || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X4 || !IN_X5){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    11:
	                if((IN_X6 || IN_X4) || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X5){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	            case    12:
	                if((IN_X6 || IN_X5) || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4){ 
						bFlrMatchChk=1;
	                }                    
	                break;
	*/
	            default:
						bFlrMatchChk=1;
	                break;        
	        }    
		}
		else{
			FloorPort=0;
			if( !IN_X0)	FloorPort=(FloorPort | 0x01);
			if( !IN_X1)	FloorPort=(FloorPort | 0x02);
			if( !IN_X2)	FloorPort=(FloorPort | 0x04);
			if( !IN_X3)	FloorPort=(FloorPort | 0x08);
			if( !IN_X4)	FloorPort=(FloorPort | 0x10);
			if( !IN_X5)	FloorPort=(FloorPort | 0x20);
	
	        if(sRamDArry[mcurfloor] != FloorPort){
					bFlrMatchChk=1;
			}
		}			
    }

#endif
	return(0);
}



/*
unsigned int __attribute__((section(".usercode")))  CheckFloorSensor(void)
{


#ifdef	TEST_SIMULATION
    bEqualFloorError=0;
	return(0);
#else

	LocalType FloorPort;

    bEqualFloorError=0;

    if(((USE_CHECK == BAGGAGE_USE) ||  (USE_CHECK == CARLIFT_USE))){ 

		if((sRamDArry[mcurfloor] == 0) && IN_SD1){
            bCarErr=1;
            bEqualFloorError=1;

		}

		if((sRamDArry[mcurfloor] == cF_TOPFLR) && IN_SU1){
            bCarErr=1;
            bEqualFloorError=1;
		}

        if(!IN_SD1 || !IN_SU1){
	        if(!IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
	            bCarErr=1;
	            bEqualFloorError=1;
	        }

        	if(!IN_SD1 && !IN_SU1){           
	            bCarErr=1;
	            bEqualFloorError=1;
			}          
			return(0);                    
		}

		if(!FloorSelMethod){
	        switch(sRamDArry[mcurfloor]){
	            case    1:    
	                if(IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    2:
	                if(IN_X1 || !IN_X0 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    3:
	                if(IN_X2 || !IN_X0 || !IN_X1 || !IN_X3 || !IN_X4 || !IN_X5 || !IN_X6){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    4:
	                if(IN_X3 || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X4 || !IN_X5 || !IN_X6){
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    5:
	                if(IN_X4 || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X5 || !IN_X6){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    6:
	                if(IN_X5 || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X6){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    7:
	                if((IN_X6 || IN_X0) || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    8:
	                if((IN_X6 || IN_X1) || !IN_X0 || !IN_X2 || !IN_X3 || !IN_X4 || !IN_X5){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    9:
	                if((IN_X6 || IN_X2) || !IN_X0 || !IN_X1 || !IN_X3 || !IN_X4 || !IN_X5){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    10:
	                if((IN_X6 || IN_X3) || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X4 || !IN_X5){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    11:
	                if((IN_X6 || IN_X4) || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X5){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	            case    12:
	                if((IN_X6 || IN_X5) || !IN_X0 || !IN_X1 || !IN_X2 || !IN_X3 || !IN_X4){ 
	                    bCarErr=1;
	                    bEqualFloorError=1;
	                }                    
	                break;
	
	            default:
	                bCarErr=1;
	                bEqualFloorError=1;
	                break;        
	        }    
		}
		else{
			FloorPort=0;
			if( !IN_X0)	FloorPort=(FloorPort | 0x01);
			if( !IN_X1)	FloorPort=(FloorPort | 0x02);
			if( !IN_X2)	FloorPort=(FloorPort | 0x04);
			if( !IN_X3)	FloorPort=(FloorPort | 0x08);
			if( !IN_X4)	FloorPort=(FloorPort | 0x10);
			if( !IN_X5)	FloorPort=(FloorPort | 0x20);
	
	        if(sRamDArry[mcurfloor] != FloorPort){
	            bCarErr=1;
	            bEqualFloorError=1;
			}
		}			
    }

#endif

	return(0);
}
*/

//////


void __attribute__((section(".usercode")))  PositionOkChk(void)
{
#ifdef	TEST_SIMULATION
        bsSdsErr=0;
        bsSusErr=0;
#else
    if( !IN_SU1 || (sRamDArry[mcurfloor] >= cF_TOPFLR)){
        if(!IN_SU1 && (sRamDArry[mcurfloor] == cF_TOPFLR)){
            bsSusErr=0;
        }
        else{
            bsSusErr=1;
            bCarErr=1;
        }
    
//        if(!IN_SU1) sRamDArry[mcurfloor]=cF_TOPFLR;        //modify ?
        if(!IN_SU1 && !IN_EMG) sRamDArry[mcurfloor]=cF_TOPFLR;        //modify ?
    }    
    else if(!IN_SD1 || (sRamDArry[mcurfloor] == 0)){
        if(!IN_SD1 && (sRamDArry[mcurfloor] == 0)){
            bsSdsErr=0;
        }
        else{
            bsSdsErr=1;
            bCarErr=1;
        }
    
//        if(!IN_SD1) sRamDArry[mcurfloor]=0;                 //modify ?
        if(!IN_SD1 && !IN_EMG) sRamDArry[mcurfloor]=0;                 //modify ?
    }
    else{
        bsSdsErr=0;
        bsSusErr=0;
    }
#endif

}

//////

unsigned int  __attribute__((section(".usercode")))  StopPulseCheck(void)
{
#ifdef	TEST_SIMULATION
	return(0);
#else
	unsigned int ZeroHzSet;

	LuLdTime=0;
	ZeroHzSet=0;

	if(bOnLuLd){
		ReadEncoder();

		TestPulse1= (unsigned long)iF_StopPulse;

//		  LuLdEncoder=CurPulse;			
//        TestPulse1=FLOOR_COUNT(sRamDArry[mcurfloor]);		

		if(bCarUpMove){
			if(CurPulse >= ((LuLdEncoder + TestPulse1) - LevelEncoderPulse2))	ZeroHzSet=1;			
		}
		else if(bCarDnMove){
			if(CurPulse <= ((LuLdEncoder - TestPulse1) + LevelEncoderPulse2))	ZeroHzSet=1;			
		}


		if(ZeroHzSet==1){			
            ZeroSpeedCmd_IO();
			LuLdTime = iF_RunOffTime;
		  	sRamDArry[mCarMoveState]=0;
			LevelEncoderPulse1=CurPulse;
			return(0);
		}
	}
	return(1);
#endif
}



#ifdef	TEMP_PARK
UserDataType __attribute__((section(".usercode")))  tmpDoorChk(void)
{
	switch(sRamDArry[mcurfloor]){
		case	0:
			if(!IN_FS0)	return(0);
			else		return(1);
			break;
		case	1:
			if(!IN_FS1)	return(0);
			else		return(1);
			break;
		case	2:
			if(!IN_FS2)	return(0);
			else		return(1);
			break;
		default:
			return(1);	
			break;
	}
}
#endif



void __attribute__((section(".usercode")))  DoorOpenCloseSeq(void)
{			  
	LocalType TmpTime;


    if((sRamDArry[mDoorSeq] >= DOOR_CLOSE_START) && (sRamDArry[mDoorSeq] < READY_ELEVATOR) && !S2_FIRE1){
        CloseOutOffTime=0;
        DoorOpenTime=0;
    }
 
    if((sRamDArry[mDoorSeq] >= DOOR_OPEN_START) && (sRamDArry[mDoorSeq] < DOOR_OPEN_WAIT) && !S2_FIRE1){
        DoorCloseTime=0;
    } 

    if((sRamDArry[mDoorSeq] >= DOOR_OPEN_START) && (sRamDArry[mDoorSeq] < READY_ELEVATOR)){
  //  	CheckFloorSensor();
		if(bFlrMatchChk){
            bCarErr=1;
            bEqualFloorError=1;
		}
		else{
            bEqualFloorError=0;
		}
    }


#ifndef  TEST_SIMULATION  
	if( !(!IN_FR1 && !IN_FR2) && DoorJumperChkOnOffChk){
	    if((sRamDArry[mDoorSeq] > DOOR_OPEN_START) && (sRamDArry[mDoorSeq] < READY_ELEVATOR) && ( !bDoorJumper)){
			if(sRamDArry[mDoorSeq] == DOOR_OPEN_WAIT){
				if(OneDoorSenserCloseChk())	bDoorJumper=1;	
			}
			else{
			    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){			
	        		if( (!IN_OP_E) && (CarDoorCloseEndCheckForDoorjmp()) ){
						DoorJumperNm=1;
						bDoorJumper=1;
					}
					if( (!IN_X7) && (HoleDoorCloseEndCheckForDoorjmp()) ){
						DoorJumperNm=(DoorJumperNm | 2);
						bDoorJumper=1;
					}					
			    }

			    else{
        			if(!IN_OP_E){
						if(OneDoorSenserCloseChk())	bDoorJumper=1;
					}
				}

			}
			if(bDoorJumper){		
				if(DoorJumperNm > 0)	DoorJumperNm=(DoorJumperNm-1);
			}
		}

		if(bDoorJumper){		
		  	sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;
		}

	}
#endif



/*
#ifndef	TEMP_PARK
    if(INVERTER_CHECK != LG){
	    if((sRamDArry[mDoorSeq] >= DOOR_OPEN_START) && (sRamDArry[mDoorSeq] <= READY_ELEVATOR)){
			bMotor_Overheat=0;	
			if(!S2_FIRE1 && !IN_FS0){
				bMotor_Overheat=1;                    
	             
				if(sRamDArry[mDoorSeq] > DOOR_REOPEN_CHECK){   		
			  		sRamDArry[mDoorSeq]=DOOR_OPEN_START;
				}
			}
	    }
	}
#endif
*/




    switch(sRamDArry[mDoorSeq]){
        case    DOOR_OPEN_START:

//            OneDoorSelOpenKeyCheck();

            sRamDArry[mDoor]= (sRamDArry[mDoor] & MAIN_SUB_CLOSE_KEY_CLEAR);
            
	        sRamDArry[mDoor] =(sRamDArry[mDoor] & ~UPDN_CAR_READY);

            PositionOkChk();

            if(INVERTER_CHECK == IO){				
                CurPulse=FLOOR_COUNT(sRamDArry[mcurfloor]);
            }

            sRamDArry[mEqualFloor] = 0x0;
            S3_UPDN_VO1=0;
			bDoorOpenEndFind=0;
            DoorCloseTime=0;


			ThisFloorDoorCheck();

			if(bRunningOpenOn){			
                SelectDoorOpen_you();    
                sRamDArry[mDoorSeq] = DOOR_OPEN_CHECK;
                DoorOpenTime=0;
				bRunningOpenOn=0;  
			}
			else if(S2_FIRE1 && (sRamDArry[mcurfloor] != FireBaseFloor) && (sRamDArry[mFireSeq] == FIRE_START) && bDoorCloseOk){	
                sRamDArry[mDoor]=0;
                sRamDArry[mDoorSeq] = READY_ELEVATOR;
            }

/*
          	else if(!bRunningOpenOn && S2_FIRE1 && (sRamDArry[mFireSeq] == FIRE_TWO) ){
            	sRamDArry[mDoor]=0;
               	sRamDArry[mDoorSeq] = READY_ELEVATOR;
               	sRamDArry[mFireSeq] = FIRE_THREE;
          	}
*/


#ifdef	TEMP_PARK
			else if( (NoUseNoOpen() && tmpDoorChk()) || S1_POWER_FAIL ){
#else
			else if(NoUseNoOpen() || S1_POWER_FAIL){
#endif			
                if((CloseOutOffTime >= cF_OPCLWTM) && (SolTimer > iF_DoorWaitTime)){
                    if(DoorOpenTime >= 5){
    	                SelectDoorOpen_you();    
	   	                sRamDArry[mDoorSeq] = DOOR_OPEN_CHECK;
    	                DoorOpenTime=0;
                    }                
                }     
            	if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus]=sOPEN;                     			
            }
            else{             
                bSlipCheckStart=1;
                DoorOpenTime=0;
                bReOpen=0;
                bCarUpDnChButClr=0;
//                DoorCloseTime=0;               	
                sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
//				bSolControl=0;
            }                
            break;                                        
        case	DOOR_OPEN_CHECK:        
            bSlipCheckStart=1;
            SelectDoorOpen_you();    
			OpenKeyClear();

			if(IN_FR1){                                  		
                sRamDArry[mDoor]= (sRamDArry[mDoor] & MAIN_SUB_CLOSE_KEY_CLEAR);
            }

            if(bOpenDoorOk){
				bDoorOpenEndFind= 1;
                DoorOpenTime	= 0;

                if(USE_CHECK == MAN_USE){
	                if(bReOpen){
	                    DoorOpenTime = cF_OPWTTM;    //car
	                }
	                else{
	                    DoorOpenTime = cF_REOPTM;    //hib
	                }
				}
                else{
                    DoorOpenTime = cF_REOPTM;    //hib
                }

                bReOpen=0;
                sRamDArry[mDoorSeq] = DOOR_OPEN_WAIT;
            }            		
            else if(DoorOpenTime > cF_OPTTTM){
                if(OpenTotalUseChk){
                    sRamDArry[mDoorSeq] = DOOR_OPEN_WAIT;            
                    DoorOpenTime = cF_REOPTM;   
                }
            }

            if((DoorOpenTime > 60) && (bDoorCloseOk)){
                sRamDArry[mDoorSeq] = DOOR_OPEN_WAIT;            
   	            DoorOpenTime 	= cF_OPWTTM + cF_REOPTM;
            }

            if(DoorOpenTime > 10){
                bCarUpDnChButClr=0;
            }
         		                              		         		         		
            break;                  		
		case	DOOR_OPEN_WAIT:    		      
            bDoorOpenEnd=1;
            bCarUpDnChButClr=0;
            DoorCloseTime=0;
            OpenKeyClear();

			if(OpenOutSet){  
	            SelectDoorOpen_you();    
			}

            if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus]=sOPEN;      


			OutDateCheck();

/*
			if((OneDoorSenserCloseChk()) && !(!IN_FR1 && !IN_FR2) && DoorJumperChkOnOffChk){   // && bDoorOpenEndFind){                                  		
			  	sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;
				bDoorJumper=1;
				if(DoorJumperNm > 0)	DoorJumperNm=(DoorJumperNm-1);
			}
*/


			if(bDoorJumper==0){
				if((DoorOpenTime > (cF_OPWTTM + cF_REOPTM))){
	                if(OpenWaitUseChk){    
	    				sRamDArry[mDoorSeq] = DOOR_REOPEN_CHECK;
						DoorOpenTime=0;   ///
	                }
				}
			}
            break;            
        case	DOOR_REOPEN_CHECK:     
#ifdef	L_K_J
            if(bDoorJumper){
#else
            if(bDoorJumper || bOutDate || bMotor_Overheat){
#endif
                SelectDoorOpen_you();    
                sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;         						
            }
            else{         		
                DoorCloseTime=0;      
    
                if(S3_VIP1){
		            SelectDoorOpen_you();    
					DoorOpenTime=cF_OPWTTM+1;
                    UpDnRstCheck();            		
                }
	            else{
                    if(DoorOpenTime > cF_REOPTM){             ////
        		        sRamDArry[mDoorSeq] = DOOR_CLOSE_START;
                    }
                }                               
                if(sRamDArry[mSysStatus] > sOPEN)   sRamDArry[mSysStatus]=sOPEN;      
            }         			
            break;            
        case  DOOR_CLOSE_START:
/*    
            bDoorOpenEnd=0;
            if(sRamDArry[mHighFloor] | sRamDArry[mLowFloor])	S3_UPDN_VO1=1;
			SelectDoorClose_you(); 	            		
			sRamDArry[mDoorSeq]=DOOR_CLOSE_CHECK;     
			DoorCloseTime=0;
*/    



            bDoorOpenEnd=0;
            if(sRamDArry[mHighFloor] | sRamDArry[mLowFloor])	S3_UPDN_VO1=1;

            if(sRamDArry[mSysStatus] > sCLOSE)   sRamDArry[mSysStatus]=sCLOSE;      
 	            		
			if(DoorCloseTime >= 5){         
				sRamDArry[mDoorSeq]=DOOR_CLOSE_CHECK;     
				DoorCloseTime=0;    
            }

            break;
        case  DOOR_CLOSE_CHECK:                  
/*
			if((OneDoorSenserCloseChk()) && !(!IN_FR1 && !IN_FR2) && DoorJumperChkOnOffChk && bDoorOpenEndFind){
				if( (DoorCloseTime < cF_DRJMPCHKTTM) || !CarDoorSwitchCheck() ){                                  		                                  		
				  	sRamDArry[mDoorSeq]=DOOR_REOPEN_CHECK;
					bDoorJumper=1;
					if(DoorJumperNm > 0)	DoorJumperNm=(DoorJumperNm-1);
				}
			}
*/
			if(bDoorJumper == 0){

                SelectDoorClose_you();                      //4    	            		
    
    	        if(!CloseTotalUseChk)   DoorCloseTime=0;   


                if(bDoorCloseOk){
                    sRamDArry[mDoorSeq]=DOOR_CLOSE_END;                                        
                    DoorCloseTime=0;
                    bsHdsNoOn=0;
                    bsCleNoOn=0;
                    UpDnRstCheck(); 

					#ifdef	TEST_SIMULATION
                        if(!IN_X5)	sRamDArry[mDoorSeq]=DOOR_OPEN_START; 
					#endif
           		
                }
         		      
                else if(DoorCloseTime > cF_OPTTTM){
                    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
                        bsCleNoOn=1;
           	            bCarErr=1;
                    }
                    else{
                        sRamDArry[mDoorSeq]=DOOR_OPEN_START; 
                        bReOpen=1;
                    }
                }
 
            }
			else{
	    		sRamDArry[mDoorSeq] = DOOR_REOPEN_CHECK;
			}
            break;               
        case  DOOR_CLOSE_END:  
            SelectDoorClose_you();   //5            
            if(bDoorCloseOk){

#ifdef	L_K_J
/*
				if(bOutDate){
					TmpTime=(LocalType)((sRamDArry[sec] >> 4) * 10);
					TmpTime= ((LocalType)(sRamDArry[sec] & 0x0f) +  TmpTime);
					if(TmpTime < 10)	TmpTime = (TmpTime + 10);	

					PowerOnTime = (PowerOnTime - TmpTime); 
					sRamDArry[mDoorSeq]=DOOR_OPEN_START;
	                bDoorJumper=1;

				}

*/
				if(bOutDate){
					sRamDArry[mDoorSeq]=DOOR_OPEN_START;
	                   bReOpen=0;
				}
	
				else{	
	                if(DoorCloseTime > 5){
	                    sRamDArry[mDoorSeq]=READY_ELEVATOR;  
	                }
				}	
#else
                if(DoorCloseTime > 5){
                    sRamDArry[mDoorSeq]=READY_ELEVATOR;  
                }
#endif
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
	unsigned long tmp_p;
	unsigned long tmp_p2;
//	unsigned int  HomeWard;

    if(bUnd && bDac){
        if((VoiceTime > cF_DIRTIME) &&  (sRamDArry[mDoorSeq] >= WAIT_NEXT_LULD)){
            if(cF_DIRTIME>0){
                CallMeUpDnDirectionSet();                                                                           
            }
        }
    }                
                                                                           
    HighLowCallClear();
    UpDnDirectionSet();
    
    if(sRamDArry[mDoorSeq] <= READY_ELEVATOR){
        UpDnCallClear();           
		AutoDoorSystem();   
    }
    
/*    													//abcd
    if(sRamDArry[mDoorSeq] <= DOOR_REOPEN_CHECK){
        if(!bOpenDoorOk){ 
            SelectDoorOpen_you();      
        }               
    }
*/
                     
	switch(sRamDArry[mDoorSeq]){

		case  READY_ELEVATOR:		

            UpDnStopCmd();

			sRamDArry[mDoor] =( sRamDArry[mDoor] & ~UPDN_CAR_READY);
            sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];
        
            S2_FLOW1=0;

        	if(OilLopeTypeChk)	bsLuLdNoOff=0;

//////////////////			sRamDArry[mDoorSeq]=READY_ELEVATOR;
            bCarUpDnChButClr=0;

            CloseOutOffTime=200;

			PositionOkChk();
			
////////////////////////////////////////////// SelectDoorClose_you();   //5                         	            		

			if(!bDoorCloseOk){
                if(IN_FR1 || IN_FR2){
    				sRamDArry[mDoorSeq]=DOOR_CLOSE_START;         
    				DoorCloseTime=0;               
                }
			}
			else{

/*
#ifdef	L_K_J
if( (sRamDArry[mNewAckStopFloor] != 0) &&  (PowerOnTime >= 720) ){
	if( ((sRamDArry[mNewAckStopFloor] & 0x40)  == 0) &&  ((sRamDArry[mNewAckStopFloor] & 0x3f)  == cF_PRKFLR)){
		sRamDArry[mEqualFloor]=0x0;
		sRamDArry[mHighFloor]=0x0;	
		sRamDArry[mLowFloor]=0x0;
	    sRamDArry[mAckStopFloor] = 0x0;
	    sRamDArry[mNewAckStopFloor]=0x0;
	}
}
#endif
*/
                CurDoorSelect=0;
				if((sRamDArry[mNewAckStopFloor] & 0xe0) && ((sRamDArry[mNewAckStopFloor] & ONLY_FLR) != sRamDArry[mcurfloor])){					
					sRamDArry[mAckStopFloor] = sRamDArry[mNewAckStopFloor];
                    if(!SpeedSet()){
    					sRamDArry[DEST_FLR] = sRamDArry[mNewAckStopFloor];                    
        				OriginalHighFlr     = sRamDArry[mHighFloor];
        				OriginalLowFlr      = sRamDArry[mLowFloor];
	    				sRamDArry[mNewAckStopFloor]=0; 
		    			sRamDArry[mCarMoveState]=0;
			    		NextFloorTime=0;                
				    	bSlipCheckStart=0;
						bPowerChkStart=1;
                        S3_UPDN_VO1=1; 	
                        sRamDArry[mReqStopFloor]  = sRamDArry[mcurfloor];
	    				sRamDArry[mDoorSeq]=MOVE_ELEVATOR;
                    }
                    else{
    					sRamDArry[mAckStopFloor] = sRamDArry[mNewAckStopFloor] = 0;
                        sRamDArry[mHighFloor]    = sRamDArry[mLowFloor]        = 0;                        
                    }
				}               
				else{
					FixFloorStartCheck();
					LoadCmdStartCheck();
				}

				if(sRamDArry[mSysStatus] >= sREADY)   sRamDArry[mSysStatus]=sREADY;                              
			}            

			if(!bOnLuLd){
		        LuLdTime=0;
				bFirstOnLuLd=0;

                if( (!IN_LU || !IN_LD) && bDoorCloseOk){
                    if(bManualAuto){
                        bManualAuto=0;
                        CarOnceStopTime=31;      

                      	if(!IN_LU && IN_LD)         bHomeUpDn = 1;
                      	else if(IN_LU && !IN_LD)    bHomeUpDn = 0;
                    }
                }
                else{
    				bCarErr=1;
                }
            }
            break;                

		case  MOVE_ELEVATOR:  

			AutoUpDownStart();         
            CounterTime=0;
 			bReLoadEncoder=0;

#ifdef  TEST_SIMULATION  
            if(MotorMoveTime>10){
                sRamDArry[mDoorSeq]=WAIT_NEXT_LULD;         
                NextFloorTime=0;
                LuLdTime=0;
                bUpDnSet=0;
            }			   
            else  if(NextFloorTime>cF_LULDOFFTIME){
                if(bOnLuLd)	    bCarErr=1;
                else			bCarStopNoRun=1;         
                bsLuLdNoOff=1;
            }
#else
///////////////////if(!bOnLuLd){
	    	if(IN_LU && IN_LD){
				sRamDArry[mDoorSeq]=WAIT_NEXT_LULD;   
//////				bRunningOpenOn=0;
			   	NextFloorTime=0;    
                bUpDnSet=0;
				LuLdTime=0;
			}			   
			else  if(NextFloorTime>cF_LULDOFFTIME){
				if(bOnLuLd)	    bCarErr=1;
				else			bCarStopNoRun=1;         

        		if(!OilLopeTypeChk)         bCarStopNoRun=1;

				bsLuLdNoOff=1;
			}               
#endif
            break;                         
         case  WAIT_NEXT_LULD:
                if(bCarUpMove) if(sRamDArry[mSysStatus] > sUP)   sRamDArry[mSysStatus]=sUP;      
                if(bCarDnMove) if(sRamDArry[mSysStatus] > sDN)   sRamDArry[mSysStatus]=sDN;      

    
    			if(((sRamDArry[mReqStopFloor] & ONLY_FLR) == (sRamDArry[mAckStopFloor] & ONLY_FLR))  && (sRamDArry[mReqStopFloor] & CAR_READY)){

/////					ThisFloorDoorCheck();
                    OUT_DAC(1);
                    bDac=1; 



#ifdef  TEST_SIMULATION  
	if(bDac && !bUnd){
		LuLdTime=0;
        CarLowSpeedCmd_IO();
	}
#endif    



#ifdef  TEST_SIMULATION                  
            		if(bUnd && (LuLdTime > iF_RunOffTime)){
    	       	        sRamDArry[mDoorSeq]=STOP_ELEVATOR;
         	  	      	sRamDArry[mCarMoveState]=0;
						LuLdTime=0;
    				}
#else


					RunningOpenAction();

    				if(INVERTER_CHECK == IO){
	 					if( ((sRamDArry[mcurfloor] & ONLY_FLR) == (sRamDArry[mAckStopFloor] & ONLY_FLR)) && bOnLuLd && bUnd){
							if(	!StopPulseCheck()){
		    					sRamDArry[mDoorSeq]=STOP_ELEVATOR;
							}
						}
					}
					else{
	 					if((sRamDArry[mcurfloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR))	LuLdTime =0;  //xx				
	                                    
	            		if(bUnd && (LuLdTime > iF_RunOffTime)){
	    	       	        sRamDArry[mDoorSeq]=STOP_ELEVATOR;
	         	  	      	sRamDArry[mCarMoveState]=0;
	    				}
					}


                    if(!bUnd){
        				NewFloorLoad();
    			        if((sRamDArry[mReqStopFloor] & ONLY_FLR) != (sRamDArry[mAckStopFloor] & ONLY_FLR)){
                            OUT_DAC(0); 
                            bDac=0;
                        }
                    }

#endif    

    			}
    			else if(bUnd){
					bsLuOrLdErr=0;
					LuLdErrNm=0;


                    if(!(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
    				    sRamDArry[mAckStopFloor] = ((sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY);				
	                 	OUT_DAC(1);		
	                    bDac=1;		
    				}


/*
                 	OUT_DAC(1);		//xx
                    bDac=1;		
                    if(((sRamDArry[mAckStopFloor] & ONLY_FLR) != (sRamDArry[mReqStopFloor] & ONLY_FLR)) 
    				  || !(sRamDArry[mAckStopFloor] & UPDN_CAR_READY)){
    				    sRamDArry[mAckStopFloor] = ((sRamDArry[mReqStopFloor] & ONLY_FLR) | CAR_READY);				
    				}
*/
    			}			
                else{			       
					bsLuOrLdErr=0;
					LuLdErrNm=0;
                 	OUT_DAC(0);
                    bDac=0;
		


	    			if(IN_LU && IN_LD)	bReLoadEncoder=0;
					else if(bOnLuLd && !bReLoadEncoder){
			        	if(INVERTER_CHECK == IO){
							EncoderReloadTime=0;
							tmp_p=(unsigned long)iF_StopPulse;

							tmp_p2=(unsigned long)FLOOR_COUNT(sRamDArry[mcurfloor]);

							if(bCarUpMove)	CurPulse=(tmp_p2 - tmp_p);
							if(bCarDnMove)	CurPulse=(tmp_p2 + tmp_p);

						}
						bReLoadEncoder=1;
					}

    				NewFloorLoad();                  
    			}	

        		if(bUnd && (LuLdTime==0)){				
                    UpDnCallClear();  
                }

               break;                         
         	case  STOP_ELEVATOR:

				RunningOpenAction();            			

				ReadEncoder();
			    CarStopCmd();

				if(!bOnLuLd){
					bCarErr=1;	
				}	

                if(!bMoveCar){
                	sRamDArry[mCarMoveState]=0;

					if(CurPulse > LevelEncoderPulse1)	LevelEncoderPulse2=(unsigned int)(CurPulse - LevelEncoderPulse1);
					else							    LevelEncoderPulse2=(unsigned int)(LevelEncoderPulse1 - CurPulse);


                    bVoiceReady=0;   
                    OpenKeyCheck();

                   	OUT_DAC(0);
                    bDac=0;

    				if(bUpWard && !(sRamDArry[mHighFloor] & UPDN_CAR_READY)){
    				    bCarUpDnChButClr=1;	
    			    }   		 
    			    else if(bDnWard && !(sRamDArry[mLowFloor] & UPDN_CAR_READY)){
      					bCarUpDnChButClr=1;	
    			    }   			

				
				    DoorOpenTime = 0;


//fire modify

                    if(S2_FIRE1){
                        KeyClr();
                        ClrUpDnWard();       
                        NextFloorTime=0;   
                        DoorCloseTime=0;
    				    bCarUpDnChButClr=0;
	
					}

/*
						KidsKeyCheck();
						sRamDArry[mDoorSeq] = DOOR_OPEN_START;

						if(sRamDArry[mVFlrCnt] > 0){
							if((sRamDArry[mVFlr1] == sRamDArry[S0_FLOOR]) || (sRamDArry[mVFlr2] == sRamDArry[S0_FLOOR])){

								#ifndef  KTL  
								sRamDArry[mVFlrCnt]--;
								#endif

								VirtualMoveCntReDsp();
							}				
						}

*/


					if(!bRunningOpenOn && S2_FIRE1 && (sRamDArry[mcurfloor] != FireBaseFloor) && (sRamDArry[mFireSeq] == FIRE_START) ){	
                        sRamDArry[mDoor]=0;
                        sRamDArry[mDoorSeq] = READY_ELEVATOR;
                   	}
                   	else	if(!bRunningOpenOn && S2_FIRE1 && (sRamDArry[mFireSeq] == FIRE_TWO) ){
                        sRamDArry[mDoor]=0;
                        sRamDArry[mDoorSeq] = READY_ELEVATOR;
                        sRamDArry[mFireSeq] = FIRE_THREE;
                   	}
                    else{
						KidsKeyCheck();
						sRamDArry[mDoorSeq] = DOOR_OPEN_START;

						if(sRamDArry[mVFlrCnt] > 0){
							if((sRamDArry[mVFlr1] == sRamDArry[S0_FLOOR]) || (sRamDArry[mVFlr2] == sRamDArry[S0_FLOOR])){

								#ifndef  KTL  
								sRamDArry[mVFlrCnt]--;
								#endif

								VirtualMoveCntReDsp();
							}				
						}
					}

                }
                break;         
             default:
//				bCarErr=1;
//                sRamDArry[mDoorSeq] = DOOR_CLOSE_START;                    

               if(sRamDArry[mDoorSeq] > STOP_ELEVATOR){      
					bCarErr=1;
                  sRamDArry[mDoorSeq] = DOOR_CLOSE_START;                    
               }            
               break;                
   }
}



unsigned int  __attribute__((section(".usercode"))) TestUpDn(void)
{
	ManualUpDnKeyCheck();

#ifdef	CHINA
   	bManualUpKey=0;
    bManualDnKey=0;
#endif

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
        if(bTestKey){   		
            sRamDArry[mLowFloor]  = 0x0;
            sRamDArry[mHighFloor] = 0x0;
            sRamDArry[mEqualFloor]= 0x0;				
            bTestKey=0;		
		}
   	}
	return(0);
}




void  __attribute__((section(".usercode"))) FindLuLdManual(void)
{

    LocalType     NewStopChk;

	NewStopChk=1;

    if(IN_LU && IN_LD){
		bOnceOpen=0;
		bLevelFind=0;
		bNotStopRelevel=0;
	}
	else	bNotStopRelevel=1;



#ifndef  TEST_SIMULATION      
	if(((sRamDArry[mcurfloor] == 0) && (IN_SD1)) || ((sRamDArry[mcurfloor] == cF_TOPFLR) && (IN_SU1))){
		LuLdTime=0;
		bFirstOnLuLd=0;
		bNotStopRelevel=0;
		NewStopChk=0;
	}
#endif



    if( bFirstOnLuLd && bNotStopRelevel && ((LuLdTime >= iF_RunOffTime) || ( (bCarUpMove && IN_LU) || (bCarDnMove && IN_LD)))){

#ifdef  TEST_SIMULATION      
		if(bSearchHome){
			sRamDArry[mCarMoveState]=0;
			bSearchHome=0;
		}
		CarStopCmd();
		bManualUpKey=0;
		bManualDnKey=0;                  
		
		if(LuLdTime>(F_UDOffTime + F_RunOffTime)){
			sRamDArry[mDoorSeq] = DOOR_OPEN_START;      
			bManualAuto=1;
		}
#else 

		if(bSearchHome){
			sRamDArry[mCarMoveState]=0;
			bSearchHome=0;
		}
		
		ReadEncoder();
		CarStopCmd();
		
		bManualUpKey=0;
		bManualDnKey=0;


#ifndef		CHINA		
		if(OilLopeTypeChk){
			bsNextFloor=0;      
		}
#endif
		
		if(!bMoveCar){		
			if( !bOnceOpen){
				sRamDArry[mDoorSeq] = DOOR_OPEN_START;
				bOnceOpen=1;

				if((iF_SolOnTime > 3) && (iF_DoorWaitTime > 3)){
					SolTimer=0;
				}
			}

		
			if(!bLevelFind){
				ClrUpDnWard();
			}

			bManualAuto=1;
			bLevelFind=0;
            DoorOpenTime=0;   

//			if(CurPulse > LevelEncoderPulse1)	LevelEncoderPulse2=(unsigned int)(CurPulse - LevelEncoderPulse1);
//			else							    LevelEncoderPulse2=(unsigned int)(LevelEncoderPulse1 - CurPulse);
              
	    }

////////////		if(!bOnLuLd)	bCarErr=1;

#endif
    }
    else{

///////////////////


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
                  
        bAuto=1;

        if(OilLopeTypeChk){ 
            NextFloorTime=0;    //no clear8  ????
        }


#ifndef  TEST_SIMULATION      
   	if(INVERTER_CHECK == IO){
		if(NewStopChk==1){
			StopPulseCheck();
		}
	}
#endif

    }
}      


void  __attribute__((section(".usercode"))) SlipCheck(void)
{
	if( bSlipCheckStart && (IN_LU && IN_LD) && (OneDoorSenserNoCloseChk()) ){         	         		        
        bMoveOk=0;
        bMoveUpOk=0;
        bMoveDnOk=0;
        bsSlip=1;            
        bCarErr=1;   
        bCarStopNoRun=1;
	}
}




void  __attribute__((section(".usercode"))) OilTypeStopChk(void)
{

#ifdef	CHINA
	if( bsNextFloor || bsLuLdNoOff){         	         		        
        bMoveOk=0;
        bMoveUpOk=0;
        bMoveDnOk=0;
        bCarErr=1;   
        bCarStopNoRun=1;
	}
#else
	if(!OilLopeTypeChk){
		if( bsNextFloor || bsLuLdNoOff){         	         		        
	        bMoveOk=0;
	        bMoveUpOk=0;
	        bMoveDnOk=0;
	        bCarErr=1;   
	        bCarStopNoRun=1;
		}
	}
#endif

}


void __attribute__((section(".usercode")))  NextFloorCheck(void)
{
   if(sRamDArry[mBefcurfloor] != sRamDArry[mcurfloor]){
      NextFloorTime=0;  
      sRamDArry[mBefcurfloor] = sRamDArry[mcurfloor];

      	if(OilLopeTypeChk){
	    	bsNextFloor=0;      
	      	ErrFlagClr();
		}
   }
            
   if(!bMoveCar){
      NextFloorTime=0;      
   }
   else if(NextFloorTime> (BASE_NEXT_FLR_TIME + (cF_NEXTFLRTIME * 10))){
        bsNextFloor=1;
		bCarErr=1;
   }
}









/*
*/

void  __attribute__((section(".usercode")))   AddressRead(void)
{

    MyGroupAddr=cF_GroupNm;
    MyLocalAddr=cF_LocalNm;
}











void __attribute__((section(".usercode")))  InPutRead(void)
{
    unsigned int i;

    LocalType tmp;


    OUT_ON=0;

    PORTD=0xffff;
    i=PORTD;
     
    tmp=(UserDataType)(i & 0x00ff);
    EmgByte=tmp;

	i=(i >> 8);
    tmp=(UserDataType)(i & 0x00ff);
    Su1Byte=tmp;


    tmp=0;
    if(PORTBbits.RB2)    tmp = tmp | 0x01;  //IN_RG
    if(PORTBbits.RB6)    tmp = tmp | 0x02;  //IN_BAT
    if(PORTBbits.RB7)    tmp = tmp | 0x04;  //IN_PASS
    if(PORTAbits.RA9)    tmp = tmp | 0x08;  //IN_FIRE
    if(PORTAbits.RA10)   tmp = tmp | 0x10;  //IN_WATER
    if(PORTAbits.RA14)   tmp = tmp | 0x20;  //IN_EX0
    if(PORTAbits.RA15)   tmp = tmp | 0x40;  //IN_EX1
    if(PORTFbits.RF6)    tmp = tmp | 0x80;  //IN_EX2

    GrByte=tmp;


	RD_WR=0;  

    IN_3=0;
    IN_3=0;
    IN_3=0;
    IN_3=0;



    i=PORTB; 
    tmp=(UserDataType)(i>>8);
    FireByte=tmp; 

    IN_3=1;


    IN_0=0;
    IN_0=0;
    IN_0=0;
    IN_0=0;

    i=PORTB;
    tmp=(UserDataType)(i>>8);
 
    if(INVERTER_CHECK == LG){
	    if(Bef_I_FS0 == tmp){
	        if(I_FS0_Cht >= 10){
	                I_FS0_bit = ~tmp;
	                Bef_I_FS0 = tmp;
	                I_FS0_Cht = 0;
	        }  
	    }
	    else{
	        I_FS0_Cht=0;
	        Bef_I_FS0=tmp;
	    }    
	}
	else{
		I_FS0_bit = tmp;
	}



    IN_0=1;
    IN_0=1;


    IN_1=0;
    IN_1=0;
    IN_1=0;
    IN_1=0;

    i=PORTB;
    tmp=(UserDataType)(i>>8);
    X0Byte=tmp;
  
    IN_1=1;



    if(INVERTER_CHECK != LG){

	    if(BEF_IN_FS0_IN == IN_FS0_IN){
	        if(Fs0Time>20){
	            IN_FS0_IN=BEF_IN_FS0_IN;
	            Fs0Time=0;
	        }
	    }
	    else{
	        BEF_IN_FS0_IN=IN_FS0_IN;
	        Fs0Time=0;
	    }    
	
	
	    if(BEF_IN_FS1_IN == IN_FS1_IN){
	        if(Fs1Time>20){
	            IN_FS1_IN=BEF_IN_FS1_IN;
	            Fs1Time=0;
	        }
	    }
	    else{
	        BEF_IN_FS1_IN=IN_FS1_IN;
	        Fs1Time=0;
	    }
	    
	    if(BEF_IN_FS2_IN == IN_FS2_IN){
	        if(Fs2Time>20){
	            IN_FS2_IN=BEF_IN_FS2_IN;
	            Fs2Time=0;
	        }
	    }
	    else{
	        BEF_IN_FS2_IN=IN_FS2_IN;
	        Fs2Time=0;
	    }    
	
	    if(BEF_IN_FS3_IN == IN_FS3_IN){
	        if(Fs3Time>20){
	            IN_FS3_IN=BEF_IN_FS3_IN;
	            Fs3Time=0;
	        }
	    }
	    else{
	        BEF_IN_FS3_IN=IN_FS3_IN;
	        Fs3Time=0;
	    }    
	
	    if(BEF_IN_FS4_IN == IN_FS4_IN){
	        if(Fs4Time>20){
	            IN_FS4_IN=BEF_IN_FS4_IN;
	            Fs4Time=0;
	        }
	    }
	    else{
	        BEF_IN_FS4_IN=IN_FS4_IN;
	        Fs4Time=0;
	    }    
	
	
	    if(BEF_IN_DER_IN == IN_DER_IN){
	        if(DerTime>20){
	            IN_DER_IN=BEF_IN_DER_IN;
	            DerTime=0;
	        }
	    }
	    else{
	        BEF_IN_DER_IN=IN_DER_IN;
	        DerTime=0;
	    }    
	
	
	    if(BEF_IN_FID_IN == IN_FID_IN){
	        if(FidTime>20){
	            IN_FID_IN=BEF_IN_FID_IN;
	            FidTime=0;
	        }
	    }
	    else{
	        BEF_IN_FID_IN=IN_FID_IN;
	        FidTime=0;
	    }    
	
	    if(BEF_IN_UND1_IN == IN_UND1_IN){
	        if(UndTime>20){
	            IN_UND1_IN=BEF_IN_UND1_IN;
	            UndTime=0;
	        }
	    }
	    else{
	        BEF_IN_UND1_IN=IN_UND1_IN;
	        UndTime=0;
	    }    
	}

//////////////////////
    if(BEF_IN_EMG_IN == IN_EMG_IN){
        if(EmgTime>20){
            IN_EMG_PORT=BEF_IN_EMG_IN;
            EmgTime=0;
        }
    }
    else{
        BEF_IN_EMG_IN=IN_EMG_IN;
        EmgTime=0;
    }    


    if(BEF_IN_PRK_IN == IN_PRK_IN){
        if(PrkTime>20){
            IN_PRK_PORT=BEF_IN_PRK_IN;
            PrkTime=0;
        }
    }
    else{
        BEF_IN_PRK_IN=IN_PRK_IN;
        PrkTime=0;
    }    


    if(BEF_IN_AUTO_IN == IN_AUTO_IN){
        if(AtTime>20){
            IN_AUTO_PORT=BEF_IN_AUTO_IN;
            AtTime=0;
        }
    }
    else{
        BEF_IN_AUTO_IN=IN_AUTO_IN;
        AtTime=0;
    }    


    if(BEF_IN_U_B_IN == IN_U_B_IN){
        if(UbTime>10){
            IN_U_B_PORT=BEF_IN_U_B_IN;
            UbTime=0;
        }
    }
    else{
        BEF_IN_U_B_IN=IN_U_B_IN;
        UbTime=0;
    }    


    if(BEF_IN_D_B_IN == IN_D_B_IN){
        if(DbTime>10){
            IN_D_B_PORT=BEF_IN_D_B_IN;
            DbTime=0;
        }
    }
    else{
        BEF_IN_D_B_IN=IN_D_B_IN;
        DbTime=0;
    }    



    if(BEF_IN_OP_E_IN == IN_OP_E_IN){
        if(OlsTime>10){
            IN_OP_E_PORT=BEF_IN_OP_E_IN;
            OlsTime=0;
        }
    }
    else{
        BEF_IN_OP_E_IN=IN_OP_E_IN;
        OlsTime=0;
    }    


    if(BEF_IN_CL_E_IN == IN_CL_E_IN){
        if(GsTime>10){
            IN_CL_E_PORT=BEF_IN_CL_E_IN;
            GsTime=0;
        }
    }
    else{
        BEF_IN_CL_E_IN=IN_CL_E_IN;
        GsTime=0;
    }    


    if(BEF_IN_HL_D_IN == IN_HL_D_IN){
        if(DsTime>10){
            IN_HL_D_PORT=BEF_IN_HL_D_IN;
            DsTime=0;
        }
    }
    else{
        BEF_IN_HL_D_IN=IN_HL_D_IN;
        DsTime=0;
    }    




//////////////////////

    if(BEF_IN_SU1_IN == IN_SU1_IN){
        if(Su1Time>30){
            IN_SU1_PORT=BEF_IN_SU1_IN;
            Su1Time=0;
        }
    }
    else{
        BEF_IN_SU1_IN=IN_SU1_IN;
        Su1Time=0;
    }    


    if(BEF_IN_SD1_IN == IN_SD1_IN){
        if(Sd1Time>30){
            IN_SD1_PORT=BEF_IN_SD1_IN;
            Sd1Time=0;
        }
    }
    else{
        BEF_IN_SD1_IN=IN_SD1_IN;
        Sd1Time=0;
    }    




    if(BEF_IN_SFT_IN == IN_SFT_IN){
        if(SftTime>10){
            IN_SFT_PORT=BEF_IN_SFT_IN;
            SftTime=0;
        }
    }
    else{
        BEF_IN_SFT_IN=IN_SFT_IN;
        SftTime=0;
    }    




    if(BEF_IN_OVL_IN == IN_OVL_IN){
        if(OvlTime>20){
            IN_OVL_PORT=BEF_IN_OVL_IN;
            OvlTime=0;
        }
    }
    else{
        BEF_IN_OVL_IN=IN_OVL_IN;
        OvlTime=0;
    }    



    if(BEF_IN_ULS_IN == IN_ULS_IN){
        if(UlsTime>10){
            IN_ULS_PORT=BEF_IN_ULS_IN;
            UlsTime=0;
        }
    }
    else{
        BEF_IN_ULS_IN=IN_ULS_IN;
        UlsTime=0;
    }    


    if(BEF_IN_DLS_IN == IN_DLS_IN){
        if(DlsTime>10){
            IN_DLS_PORT=BEF_IN_DLS_IN;
            DlsTime=0;
        }
    }
    else{
        BEF_IN_DLS_IN=IN_DLS_IN;
        DlsTime=0;
    }    


    if(BEF_IN_LU_IN == IN_LU_IN){
        if(LuTime>=10){
            IN_LU_PORT=BEF_IN_LU_IN;
            LuTime=0;
        }
    }
    else{
        BEF_IN_LU_IN=IN_LU_IN;
        LuTime=0;
    }    


    if(BEF_IN_LD_IN == IN_LD_IN){
        if(LdTime>=10){
            IN_LD_PORT=BEF_IN_LD_IN;
            LdTime=0;
        }
    }
    else{
        BEF_IN_LD_IN=IN_LD_IN;
        LdTime=0;
    }    

//////////////////////


    if(BEF_IN_GR_IN == IN_GR_IN){
        if(RgTime>20){
            IN_GR_PORT=BEF_IN_GR_IN;
            RgTime=0;
        }
    }
    else{
        BEF_IN_GR_IN=IN_GR_IN;
        RgTime=0;
    }    



    if(BEF_IN_BAT_IN == IN_BAT_IN){
        if(BatTime>10){
            IN_BAT_PORT=BEF_IN_BAT_IN;
            BatTime=0;
        }
    }
    else{
        BEF_IN_BAT_IN=IN_BAT_IN;
        BatTime=0;
    }    



    if(BEF_IN_PASS_IN == IN_PASS_IN){
        if(PassTime>20){
            IN_PASS_PORT=BEF_IN_PASS_IN;
            PassTime=0;
        }
    }
    else{
        BEF_IN_PASS_IN=IN_PASS_IN;
        PassTime=0;
    }    


    if(BEF_IN_FIRE_IN == IN_FIRE_IN){
        if(FireTime>20){
            IN_FIRE_PORT=BEF_IN_FIRE_IN;
            FireTime=0;
        }
    }
    else{
        BEF_IN_FIRE_IN=IN_FIRE_IN;
        FireTime=0;
    }    


    if(BEF_IN_WATER_IN == IN_WATER_IN){
        if(WaterTime>20){
            IN_WATER_PORT=BEF_IN_WATER_IN;
            WaterTime=0;
        }
    }
    else{
        BEF_IN_WATER_IN=IN_WATER_IN;
        WaterTime=0;
    }    



    if(BEF_IN_FULL_IN == IN_FULL_IN){
        if(FullTime>20){
            IN_FULL_PORT=BEF_IN_FULL_IN;
            FullTime=0;
        }
    }
    else{
        BEF_IN_FULL_IN=IN_FULL_IN;
        FullTime=0;
    }    


    if(BEF_IN_MM_IN == IN_MM_IN){
        if(MmTime>10){
            IN_MM_PORT=BEF_IN_MM_IN;
            MmTime=0;
        }
    }
    else{
        BEF_IN_MM_IN=IN_MM_IN;
        MmTime=0;
    }    



    if(BEF_IN_FHM_IN == IN_FHM_IN){
        if(FhmInTime>50){
            IN_FHM_PORT=BEF_IN_FHM_IN;
            FhmInTime=0;
        }
    }
    else{
        BEF_IN_FHM_IN=IN_FHM_IN;
        FhmInTime=0;
    }    

//////////////////////


    if(BEF_IN_FR1_IN == IN_FR1_IN){
        if(Fr1Time>20){
            IN_FR1_PORT=BEF_IN_FR1_IN;
            Fr1Time=0;
        }
    }
    else{
        BEF_IN_FR1_IN=IN_FR1_IN;
        Fr1Time=0;
    }    

    if(BEF_IN_FR2_IN == IN_FR2_IN){
        if(Fr2Time>20){
            IN_FR2_PORT=BEF_IN_FR2_IN;
            Fr2Time=0;
        }
    }
    else{
        BEF_IN_FR2_IN=IN_FR2_IN;
        Fr2Time=0;
    }    



    if(BEF_IN_GS2_IN == IN_GS2_IN){
        if(Gs2Time>20){
            IN_GS2_PORT=BEF_IN_GS2_IN;
            Gs2Time=0;
        }
    }
    else{
        BEF_IN_GS2_IN=IN_GS2_IN;
        Gs2Time=0;
    }    


    if(BEF_IN_DS2_IN == IN_DS2_IN){
        if(Ds2Time>20){
            IN_DS2_PORT=BEF_IN_DS2_IN;
            Ds2Time=0;
        }
    }
    else{
        BEF_IN_DS2_IN=IN_DS2_IN;
        Ds2Time=0;
    }


    
    if(BEF_IN_SU2_IN == IN_SU2_IN){
        if(Su2Time>10){
            IN_SU2_PORT=BEF_IN_SU2_IN;
            Su2Time=0;
        }
    }
    else{
        BEF_IN_SU2_IN=IN_SU2_IN;
        Su2Time=0;
    }    

    if(BEF_IN_SD2_IN == IN_SD2_IN){
        if(Sd2Time>10){
            IN_SD2_PORT=BEF_IN_SD2_IN;
            Sd2Time=0;
        }
    }
    else{
        BEF_IN_SD2_IN=IN_SD2_IN;
        Sd2Time=0;
    }    



    if(BEF_IN_BM_IN == IN_BM_IN){
        if(BmTime>10){
            IN_BM_PORT=BEF_IN_BM_IN;
            BmTime=0;
        }
    }
    else{
        BEF_IN_BM_IN=IN_BM_IN;
        BmTime=0;
    }    


    if(BEF_IN_INV_IN == IN_INV_IN){
        if(InvTime>10){
            IN_INV_PORT=BEF_IN_INV_IN;
            InvTime=0;
        }
    }
    else{
        BEF_IN_INV_IN=IN_INV_IN;
        InvTime=0;
    }    


    if(cF_PcbType == 1){
        IN_SU2_PORT =1;
        IN_SD2_PORT =1;
        IN_BM_PORT  =1;
        IN_INV_PORT =1;
    }

    if(BEF_IN_X0_IN == IN_X0_IN){
        if(X0Time>10){
            IN_X0_PORT=BEF_IN_X0_IN;
            X0Time=0;
        }
    }
    else{
        BEF_IN_X0_IN=IN_X0_IN;
        X0Time=0;
    }    

    if(BEF_IN_X1_IN == IN_X1_IN){
        if(X1Time>10){
            IN_X1_PORT=BEF_IN_X1_IN;
            X1Time=0;
        }
    }
    else{
        BEF_IN_X1_IN=IN_X1_IN;
        X1Time=0;
    }    


    if(BEF_IN_X2_IN == IN_X2_IN){
        if(X2Time>10){
            IN_X2_PORT=BEF_IN_X2_IN;
            X2Time=0;
        }
    }
    else{
        BEF_IN_X2_IN=IN_X2_IN;
        X2Time=0;
    }    
    if(BEF_IN_X3_IN == IN_X3_IN){
        if(X3Time>10){
            IN_X3_PORT=BEF_IN_X3_IN;
            X3Time=0;
        }
    }
    else{
        BEF_IN_X3_IN=IN_X3_IN;
        X3Time=0;
    }    


    if(BEF_IN_X4_IN == IN_X4_IN){
        if(X4Time>10){
            IN_X4_PORT=BEF_IN_X4_IN;
            X4Time=0;
        }
    }
    else{
        BEF_IN_X4_IN=IN_X4_IN;
        X4Time=0;
    }    

    if(BEF_IN_X5_IN == IN_X5_IN){
        if(X5Time>10){
            IN_X5_PORT=BEF_IN_X5_IN;
            X5Time=0;
        }
    }
    else{
        BEF_IN_X5_IN=IN_X5_IN;
        X5Time=0;
    }    

    if(BEF_IN_X6_IN == IN_X6_IN){
        if(X6Time>10){
            IN_X6_PORT=BEF_IN_X6_IN;
            X6Time=0;
        }
    }
    else{
        BEF_IN_X6_IN=IN_X6_IN;
        X6Time=0;
    }    

    if(BEF_IN_X7_IN == IN_X7_IN){
        if(X7Time>10){
            IN_X7_PORT=BEF_IN_X7_IN;
            X7Time=0;
        }
    }
    else{
        BEF_IN_X7_IN=IN_X7_IN;
        X7Time=0;
    }    



	if(ExIOTimer > 30)	sRamDArry[mExtIN0]= 0xff;

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




unsigned int  __attribute__((section(".usercode")))  UserLampSetCheck(unsigned int val)
{
	unsigned int i;

	i=0;

   	switch(val){
      	case  0:
         		if(bAuto)           i=1;
         		break;
      	case  1:
         		if(!bAuto)          i=1;
         		break;
      	case  2:
         		if(S1_OVERLOAD1)    i=1;
         		break;
      	case  3:
         		if(S2_FIRE1)        i=1;
         		break;
      	case  4:
         		if(S1_EMG1)         i=1;
         		break;
      	case  5:
         		if(S3_PARKING1)     i=1;
         		break;
      	case  6:
         		if(S3_VIP1)         i=1;
         		break;
      	case  7:
                if( AutoRunReady() && (sRamDArry[mDoorSeq] != READY_ELEVATOR))  i=1;
         		break;
      	case  8:
         		if(S3_FULL1)     	i=1;
         		break;
      	default:
         		i=0;     
         		break;
   	}

	return(i);
}


void  __attribute__((section(".usercode")))  	UserLampSet(void)
{
	unsigned int i;
	
 	i=UserLampSetCheck((unsigned int)(cF_USERLAMP1));
	if(i)	S2_LAMP_USER1=1; 	
	else	S2_LAMP_USER1=0; 	

 	i=UserLampSetCheck((unsigned int)(cF_USERLAMP2));
	if(i)	S1_MANUAL1=1; 	
	else	S1_MANUAL1=0; 	

 	i=UserLampSetCheck((unsigned int)(cF_USERLAMP3));
	if(i)	S4_USERLAMP3=1; 	
	else	S4_USERLAMP3=0; 	

	i=UserLampSetCheck((unsigned int)(cF_USERLAMP4));
	if(i)	S4_USERLAMP4=1; 	
	else	S4_USERLAMP4=0; 	
}




void  __attribute__((section(".usercode")))   VoiceStart(void)
{
    LocalType voice_start,bell_start;

    voice_start=1;
	bell_start=1;

    if(bAuto && bUnd){
//        if((sRamDArry[mDoorSeq] >= WAIT_NEXT_LULD) && (VoiceTime > cF_VOICETIME) ){
        if((sRamDArry[mDoorSeq] >= WAIT_NEXT_LULD)){
            if((sRamDArry[DEST_FLR] & ONLY_FLR) == (sRamDArry[mcurfloor] & ONLY_FLR)){
                if((cF_VOICETIME > 0) && (VoiceTime < (cF_VOICETIME + 10)) && (VoiceTime > cF_VOICETIME)){
                    voice_start=0;                
                }

                if(BellTime < 10){
                    bell_start=0;                
                }
            }
			else{
				BellTime=0;
				VoiceTime=0;
			}
        }
    }



	if((iF_SolOnTime > 3) && (iF_DoorWaitTime > 3)){
        if(bAuto && !bManualStop){ 
			if((sRamDArry[mDoorSeq] >= DOOR_CLOSE_START) && (sRamDArry[mDoorSeq] <= DOOR_CLOSE_END)){
				if(!IN_DS2 || bHoleDoorCloseEnd || bDoorCloseOk){      			//close end					
					if(SolWaitTimer > iF_DoorWaitTime){
						OUT_BELL(0);
						SolTimer = iF_SolOnTime;
					}
				}
				else if(!IN_GS2){   		// decrease
					if(SolTimer < iF_SolOnTime){
						SolWaitTimer=0;
						OUT_BELL(1);
					}
					else		OUT_BELL(0);
				}
				else{
					OUT_BELL(0);
					SolTimer=0;
				}
				bSolControl=0;
			}
			else if(sRamDArry[mDoorSeq] < DOOR_CLOSE_START){
#ifdef	TEMP_PARK
				if( (!IN_GS2) && tmpDoorChk()){
#else
				if(!IN_GS2){   		// decrease
#endif
					if( !bSolControl){
						bSolControl=1;
						SolTimer=0;
					}
				}
				else{
					bSolControl=0;
					SolTimer=100;
				}

				if(SolTimer < iF_SolOnTime){
					if(SolTimer > 3){
						OUT_BELL(1);
					}
				}
				else{
					OUT_BELL(0);
				}
			}
			else{
				OUT_BELL(0);
				bSolControl=0;
				SolTimer=0;
			}
		}
		else{
			OUT_BELL(0);
			bSolControl=0;
			SolTimer=0;
			if(bDoorCloseOk)	sRamDArry[mDoorSeq] = DOOR_CLOSE_END;
		}
	}
	else{
		bSolControl=0;
		SolTimer=100;
	}


	
    if(!voice_start){
        S2_FLOW1=1;	
    }       		
    else{
        S2_FLOW1=0;	
    }

    if(!bell_start){
		if((iF_SolOnTime == 0) || (iF_DoorWaitTime == 0))	OUT_BELL(1);
    }       		
    else{
		if((iF_SolOnTime == 0) || (iF_DoorWaitTime == 0))	OUT_BELL(0);
    }

}




void  __attribute__((section(".usercode"))) 	ServiceCheck(void)
{

	sRamDArry[FLR_ON_OFF0] =(sRamDArry[ExtCmdFlrONOFF0] & BaggageFlrOnOff[0]);
	sRamDArry[FLR_ON_OFF1] =(sRamDArry[ExtCmdFlrONOFF1] & BaggageFlrOnOff[1]);
	sRamDArry[FLR_ON_OFF2] =(sRamDArry[ExtCmdFlrONOFF2] & BaggageFlrOnOff[2]);
	sRamDArry[FLR_ON_OFF3] =(sRamDArry[ExtCmdFlrONOFF3] & BaggageFlrOnOff[3]);		



	if((sRamDArry[mVFlr1] != sRamDArry[mVFlr2]) && (sRamDArry[mVFlrCnt] > 0)){
		if((sRamDArry[mVFlr1] > 0) && (sRamDArry[mVFlr2] > 0)){
			if((cF_FLRDSPCH(0) == 'Z') && (cF_FLRDSPCH(1) == 'Z')){		
				AccTimer=0;
				sRamDArry[FLR_ON_OFF0]=0x0;	
				sRamDArry[FLR_ON_OFF1]=0x0;	
				sRamDArry[FLR_ON_OFF2]=0x0;	
				sRamDArry[FLR_ON_OFF3]=0x0;
			}
		}	
	}


//fire modify
	if(S2_FIRE1){
		sRamDArry[FLR_ON_OFF0] = 0xff;
		sRamDArry[FLR_ON_OFF1] = 0xff;
		sRamDArry[FLR_ON_OFF2] = 0xff;
		sRamDArry[FLR_ON_OFF3] = 0xff;		
	}
		
}





void    __attribute__((section(".usercode"))) WaterCheck(void)
{

    LocalType watersafefloor;
    
    watersafefloor=cF_WATERSAFEFLR;
    
    if(cF_WATERSAFEFLR > cF_TOPFLR){
        watersafefloor=cF_TOPFLR;
    }

   	if(!IN_WATER && bAuto && !S3_PARKING1){
      	if((sRamDArry[mcurfloor] == watersafefloor) && !bMoveCar){
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
            if(sRamDArry[mcurfloor] < watersafefloor){
                sRamDArry[mHighFloor]=(watersafefloor | CAR_READY);
            }
            else if(sRamDArry[mcurfloor] > watersafefloor){
                sRamDArry[mLowFloor]=(watersafefloor | CAR_READY);
            }
        }
	}
    else{
        bWaterSen=0;
    }
}



void  __attribute__((section(".usercode")))  InitialInPortChk(void)
{
    if(WarmingUpTime < 100){
//        if(!IN_U_B || !IN_D_B  || !IN_FHM){
        if(!IN_U_B || !IN_D_B ){
            if(WarmingUpTime >= 80) WarmingUpTime=80;

            if(sRamDArry[mSysStatus] > sInPortError)   sRamDArry[mSysStatus]=sInPortError;      
            bCarErr=1;
        }
    }        
}


void  __attribute__((section(".usercode")))  AllReadyCheck(void)
{
    LocalType readygood;

    readygood=1;

    if(!AutoRunReady())                         readygood=0;                                                             
    if(!bDoorCloseOk)                           readygood=0;
    if(sRamDArry[mDoorSeq] != READY_ELEVATOR)   readygood=0;


    if(readygood==0){
        MinuteTime=0;        
        FixFlrTimeCnt=0;
        LightTime=0;
    }

//////////////////////////////////////
    if(ElevStopTime>10){
        bCarUpDnChButClr=0;
    }

}


void  __attribute__((section(".usercode")))  FanOnOff(void)
{
    if(bCarUpMove || bCarDnMove || !bDoorCloseOk){
        OUT_FAN(1);
        FanTime=0;  
    }   
    else if(FanTime > cF_FANTIME){
        FanTime = cF_FANTIME +1;              
        OUT_FAN(0);
    }
}


void  __attribute__((section(".usercode")))  BuzOnOff(void)
{
    if(IN_FR1 || IN_FR2){
        if(USE_CHECK == BAGGAGE_USE){
            if(S1_OVERLOAD1){              
                OUT_BUZ(1);          
            }
            else if(bAuto && bOnLuLd && !bMoveCar && SafetyChk()){              
                OUT_BUZ(1);          
            }


            else if(bAuto && bOnLuLd && !bMoveCar && (TmpBuzor < 10)){              
                OUT_BUZ(1);          
            }


            else	OUT_BUZ(0);         
        }
        else if(USE_CHECK == CARLIFT_USE){
            if(S1_OVERLOAD1){              
                OUT_BUZ(1);          
            }
            else if(bAuto && SafetyChk()){              
                OUT_BUZ(1);          
            }
            else	OUT_BUZ(0);         
        }
        else{
            if(S1_OVERLOAD1)    OUT_BUZ(1);          
            else                OUT_BUZ(0);         
        }
    }
    
    if(!bAuto){
        OUT_BUZ(0);         
    }
}




void  __attribute__((section(".usercode")))  EtcStopSet(void)
{

    S3_STOP1=0;    

    if( bAuto && bOneLuOrLd && !bMoveCar){
		if(!IN_WATER || S1_POWER_FAIL || (sRamDArry[mDoor] & 0x10)){            
        	S3_STOP1=1;
		}

		if( bsEarthquake){
        	S3_STOP1=1;
			if(sRamDArry[mDoorSeq] > DOOR_REOPEN_CHECK){   		
		  		sRamDArry[mDoorSeq]=DOOR_OPEN_START;
			}
		}

		if( !(sRamDArry[mExtIN0] & 0x80)){
        	S3_STOP1=1;
			if(sRamDArry[mDoorSeq] > DOOR_REOPEN_CHECK){   		
		  		sRamDArry[mDoorSeq]=DOOR_OPEN_START;
			}
		}
    } 

    if(sRamDArry[mDoorSeq] >= READY_ELEVATOR)	sRamDArry[mDoor]= (sRamDArry[mDoor] & 0xef);
    if( !AutoRunReady())    					sRamDArry[mDoor]= (sRamDArry[mDoor] & 0xef); 
}



void  __attribute__((section(".usercode")))  WaitAndNotMoveChk(void)
{
    if(WarmingUpTime<100){
        bCarErr=1;
        CurFTime=0;
        NextFTime=0;
    }


    if((cF_ERRSTOPCNT < eDArry[eErrCntPt]) && (cF_ERRSTOPCNT != 0xff)){
        bCarStopNoRun=1;  
        bInspect=1;
    }
}




unsigned int  __attribute__((section(".usercode")))  CheckStartBreakMgt(void)
{
	if( (CurSelOutPortChk(cF_UP) || CurSelOutPortChk(cF_DN)) && CurSelOutPortChk(cF_BRK)){
		if(!bBK1){
			BreakTime=0;
			bBK1=1;
		}
		return(1);
	}
	else if( !CurSelOutPortChk(cF_UP) &&  !CurSelOutPortChk(cF_DN) && !CurSelOutPortChk(cF_BRK)){
		if(bBK1){
			BreakTime=0;
			bBK1=0;
		}
		return(1);
	}
	else{
		BreakTime=0;
		return(0);
	}
}



unsigned int  __attribute__((section(".usercode")))  BreakMgtOpenCheck(void)
{
	unsigned int rdy;

	#ifdef	TEST_SIMULATION	
		return(0);
	#else

    	if(INVERTER_CHECK == D_F)		return(0);                                             

		rdy=CheckStartBreakMgt();
		if(rdy == 0){
			return(0);
		}
	

		if(!BrkMgtUseChk )	return(0);

		#ifndef	CHINA
		    if(!bAuto)		return(0);
		#endif


		if(bBK1){
    		if(BreakTime > cF_BRK_MGT_TIME){
				if(IN_MM){
	            	bsBreakMgtOpen=1;
				}            
			 } 
		}
		else{
    		if(BreakTime > cF_BRK_MGT_TIME){
				if(!IN_MM){
	            	bsBreakMgtOpen=1;
				}            
			 } 
		}
		
		if(bsBreakMgtOpen)	bCarStopNoRun=1;
	#endif

	return(0);

}


unsigned int    __attribute__((section(".usercode")))  BreakOpenCheck(void)
{
	unsigned int rdy;

	#ifdef	TEST_SIMULATION	
		return(0);
	#else


		rdy=CheckStartBreakMgt();
		if(rdy == 0){
			return(0);
		}

		if(!BrkOpenUseChk )	return(0);

		#ifndef	CHINA
		    if(!bAuto)		return(0);
		#endif


		if(bBK1){
    		if(BreakTime > cF_BRK_MGT_TIME){
				if(IN_BM){
	            	bsBreakOpen=1; 
				}           
			 } 
		}	
		else{
    		if(BreakTime > cF_BRK_MGT_TIME){
				if(!IN_BM){
	            	bsBreakOpen=1;
				}            
			 } 
		}
		
		
		if(bsBreakOpen)	bCarStopNoRun=1;

	#endif

	return(0);

}



unsigned int  __attribute__((section(".usercode")))   HuntingChk(void)
{

    if(INVERTER_CHECK != D_F){
		HuntingCnter=0;
		return(0);
	}                                          
    if(!bAuto){
		HuntingCnter=0;
		return(0);
	}


	if(bBef_IN_MM == IN_MM){
		if(	HuntingTimer > 50){
			HuntingCnter=0;
		}
	}
	else{
		if(HuntingCnter > 10){
	        bsBreakMgtOpen=1;
			bCarStopNoRun=1;
		}	
		HuntingTimer=0;
		HuntingCnter++;
		bBef_IN_MM = IN_MM;
	}
	return(0);
}


unsigned int  __attribute__((section(".usercode")))   EarthquakeCheck(void)
{

	if(bAuto && !bManualStop && bSlaveEarthquake){
		bExtButClr=1;
   		bsEarthquake=1;

        sRamDArry[mLowFloor]  = 0;
        sRamDArry[mHighFloor] = 0;
	}
	else{
   		bsEarthquake=0;
		bBefbsEarthquake=0;	
	}

	return(0);
}


void  __attribute__((section(".usercode")))   InvErrChk(void)
{

    LocalType rst;

    if(OilLopeTypeChk){
        if(!IN_INV){
			bCarErr=1;
			bsInvertErr=1;
		}
		else{
			bsInvertErr=0;
		}

/*
        if(!IN_INV && bAuto && !bCarStopNoRun){
 
			if((RstTime >= 200) && (RstTime <= 210)){
                rst=1;    
            }
            else if((RstTime >= 100) && (RstTime <= 110)){
                rst=1;
            }    
            else if((RstTime >= 20) && (RstTime <= 30)){        
                rst=1;    
            }
            else    rst=0;
        
            
            if(rst){
	            if((RstTime >= 220) || (RstCnt >= 2) ){
                	OUT_RST(0);
	                bsInvertErr=1;
	            	bCarStopNoRun=1;  				         		
	            }    
				else{
	                OUT_RST(1);
	                bInvErrCnt=1;
	                ManualStopTime=0;
				}
            }
            else{
                OUT_RST(0);
                if(bInvErrCnt){
                    RstCnt++;    
                    bInvErrCnt=0;
                }            
            }
        }    
        else{
            OUT_RST(0);
            RstCnt=0;    
            bInvErrCnt=0;    
            RstTime=0;    
        }
         
        if(IN_INV && !bCarStopNoRun){
            bsInvertErr=0;
        }
*/
    }
    else{
        bsInvertErr=0;
        bInvErrCnt=0;
        InvErrTime=0;
        RstCnt=0;
    }
}

/*
void  __attribute__((section(".usercode")))   InvErrChk(void)
{

    LocalType rst;

    if(OilLopeTypeChk){
        if(!IN_INV){
			bCarErr=1;
			bsInvertErr=1;
		}

        if(!IN_INV && bAuto && !bCarStopNoRun){
 
			if((RstTime >= 200) && (RstTime <= 210)){
                rst=1;    
            }
            else if((RstTime >= 100) && (RstTime <= 110)){
                rst=1;
            }    
            else if((RstTime >= 20) && (RstTime <= 30)){        
                rst=1;    
            }
            else    rst=0;
        
            
            if(rst){
	            if((RstTime >= 220) || (RstCnt >= 2) ){
                	OUT_RST(0);
	                bsInvertErr=1;
	            	bCarStopNoRun=1;  				         		
	            }    
				else{
	                OUT_RST(1);
	                bInvErrCnt=1;
	                ManualStopTime=0;
				}
            }
            else{
                OUT_RST(0);
                if(bInvErrCnt){
                    RstCnt++;    
                    bInvErrCnt=0;
                }            
            }
        }    
        else{
            OUT_RST(0);
            RstCnt=0;    
            bInvErrCnt=0;    
            RstTime=0;    
        }
         
        if(IN_INV && !bCarStopNoRun){
            bsInvertErr=0;
        }
    }
    else{
        bsInvertErr=0;
        bInvErrCnt=0;
        InvErrTime=0;
        RstCnt=0;
    }
}
*/

////////hib_crt

unsigned int	__attribute__((section(".usercode")))	PcCmdchk(void)
{
	if( !(CrtMoveFlr & CAR_READY))	return(0);


	if(sRamDArry[mcurfloor] == (CrtMoveFlr & ONLY_FLR)){
    	if( (sRamDArry[mDoorSeq] >= DOOR_OPEN_START) && (sRamDArry[mDoorSeq] <= DOOR_OPEN_WAIT)){
			CrtMoveFlr=0;
		}
	}
	
	if(bExtButClr)								CrtMoveFlr=0;
	if( (CrtMoveFlr & ONLY_FLR) > cF_TOPFLR)	CrtMoveFlr=0;	
	if( !(CrtMoveFlr & CAR_READY))				return(0);


	if( !bCarUpMove && !bCarDnMove){
		Virtual_Floor_Set((CrtMoveFlr & ONLY_FLR));
	}
}


////////hib_crt




/*
unsigned int	__attribute__((section(".usercode")))	CarStopAndNotMoveCheck(void)
{
	if(AutoRunReady()){
		if(sRamDArry[mDoorSeq] == DOOR_OPEN_WAIT){		    		      
			if(bsBreakMgtOpen){
				bCarStopNoRun=1;
			}
		    if(bsBreakOpen){
     			bCarStopNoRun=1;
			}

		    if(!bCarStopNoRun){
				bsBreakMgtOpen=0;	
				bsBreakOpen=0;       
			}
		}
	}

	return(0);
}
*/


#ifdef	TEST_SIMULATION

unsigned int	__attribute__((section(".usercode"))) UpDnSim(void)
{
	if(!AutoRunReady())								return(0);
   	if(bCarUpMove || bCarDnMove)					return(0);        	

	if(sRamDArry[mcurfloor] == cF_TOPFLR){
		sRamDArry[mLowFloor]  = ((sRamDArry[mcurfloor]-1) | DN_READY);
		sRamDArry[mHighFloor] = 0;		
	}
	else if(sRamDArry[mcurfloor] == 0){
		sRamDArry[mHighFloor] = ((sRamDArry[mcurfloor]+1) | UP_READY);		
		sRamDArry[mLowFloor]  = 0;
	}
	else{
		if(bUpWard){
			sRamDArry[mHighFloor] = ((sRamDArry[mcurfloor]+1) | UP_READY);		
			sRamDArry[mLowFloor]  = 0;
		}         				
	   	else if(bDnWard){
			sRamDArry[mLowFloor]  = ((sRamDArry[mcurfloor]-1) | DN_READY);
			sRamDArry[mHighFloor] = 0;		
		}
		else{
			if(sRamDArry[mcurfloor] == cF_TOPFLR){
				sRamDArry[mLowFloor]  = ((sRamDArry[mcurfloor]-1) | DN_READY);
				sRamDArry[mHighFloor] = 0;		
			}
			else{
				sRamDArry[mHighFloor] = ((sRamDArry[mcurfloor]+1) | UP_READY);		
				sRamDArry[mLowFloor]  = 0;
			}
		}
	}

	if((sRamDArry[mHighFloor] & ONLY_FLR) ==  cF_TOPFLR){
		sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] & ONLY_FLR);  			
		sRamDArry[mHighFloor]=(sRamDArry[mHighFloor] | DN_READY);  			
	}
	if((sRamDArry[mLowFloor] & ONLY_FLR) ==  0){
		sRamDArry[mLowFloor]=(sRamDArry[mLowFloor] & ONLY_FLR);  			
		sRamDArry[mLowFloor]=(sRamDArry[mLowFloor] | UP_READY);  			
	}

	return(0);
}

#endif





unsigned int hdhTimer = 0;
unsigned int TestLoop = 0;


void  __attribute__((section(".usercode")))   IO_Check(void)
{


//	if(sRamDArry[mSysStatus] >= sHDS_NO_ON)   sRamDArry[mSysStatus]=sREADY;                              

   	sRamDArry[mSysStatus]=sREADY;

	bDoorOpenCmd=0;
	bDoorCloseCmd=0;


   	InPutRead();        
   	InputCheck();
   	AutoManualCheck();
    InitialInPortChk();
#ifdef	TEST_SIMULATION
    CarCurFloorReadSimulation();	
#else
   	CarCurFloorRead();   
#endif
	ServiceCheck();
    FireKeyCheck();
    WaterCheck();
    SlipCheck();         
    OilTypeStopChk();         
	EarthquakeCheck();
   	ButtonClrCheck();   
    WaitAndNotMoveChk();
	CarKeyMostServiceCheck();
    OnlyOneCallChk();
    SaftyStopChk();
	PcCmdchk();
    BreakMgtOpenCheck();
    BreakOpenCheck();
   	InvErrChk();
	CheckFloorSensor();
	HuntingChk();
    OUT_ERR(0);        

/////////
	
        if(bAuto){
            if(!bManualStop){

                if(!bManualAuto){
/*
                    if(CarOnceStopTime>30){                        
                        FindLuLdManual();
                        CarOnceStopTime=31;      
                        bTestKey=0;
                    }
*/

                    if(CarOnceStopTime>30){     
	                    FindLuLdManual();
						CarOnceStopTime=31;      
                        bTestKey=0;
						bLevelOpen=0;
					}


					if(SafetyChk() || (!OpenKeyCheck())){
			            if( (!IN_LU || !IN_LD) && !bMoveCar && !bLevelFind){
                			if(!bDoorCloseOk){
								if(bLevelOpen==0){
									if((iF_SolOnTime > 3) && (iF_DoorWaitTime > 3)){
										SolTimer=0;
									}
								}
								bLevelOpen=1;
								DoorOpenTime=0;
								sRamDArry[mDoorSeq] = DOOR_OPEN_START;
								sRamDArry[mDoor]    = (sRamDArry[mDoor] & CLEAR_ALL_DOOR_KEY);   							
							}
						}
					}	


					if(bLevelOpen){
						ThisFloorDoorCheck();
						CarOnceStopTime=0;      
//			   			SelectDoorOpen_you();
            			if( (bOpenDoorOk) || (DoorOpenTime > cF_OPTTTM)){
							bLevelOpen=0;
							SolTimer=100;
						}
						else{
                			if(SolTimer > iF_DoorWaitTime){
			   					SelectDoorOpen_you();
							}
						}
					}									



                }
                else{
                    if(!((sRamDArry[mFireSeq] == FIRE_ONE) || (sRamDArry[mFireSeq] == FIRE_THREE) )){                                    
                        DoorOpenCloseSeq();
                        DoorOpClSystem();
                    }

                    TestUpDn();
                    OneStopKey();

					#ifdef	TEMP_GUEN
	                    OneStopKey_GUEN();
					#endif


                }        
				CounterCheck();
                NextFloorCheck();
            }
        }                     
        else{    
            if(!bFhmRunReset && !bManualStop){    
				#ifndef	CHINA
                	bCarStopNoRun=0; 
				#endif
            
                bEncoderErr=0;
                bEncoderABErr=0;
            }
			bLevelOpen=0;
            bOnceOpen=0;
            bSearchHome=0;
            NextFloorTime=0;    
            NoCloseCnt=0;
            bTempCall=0;
            bInspect=0;
            bFR2Start1=0;
			bDoorJumper=0;
			DoorJumperNm=0;
            MinuteTime=0;        
            bsCleNoOn=0;
			bLevelFind=0;
			bRunningOpenOn=0;
			bEqualFloorError=0;


	      	if(OilLopeTypeChk){
		    	bsNextFloor=0;      
			}

            bTestKey=0;                        
            bCarUpDnChButClr=0;
            
            if(!S3_PARKING1){
                if(sRamDArry[mSysStatus] >= sMANUAL)   sRamDArry[mSysStatus] = sMANUAL;                                

                if(CarOnceStopTime < 10){
 					sRamDArry[mDoor]=0;
				}


                OUT_FAN(1);
                FanTime=0;  
                sRamDArry[mReqStopFloor]=0;
                sRamDArry[mAckStopFloor]=0;
                sRamDArry[mNewAckStopFloor]=0;
                bManualAuto=0;      
                OUT_DAC(0);
                bDac=0;
                
                ManualUpDnKeyCheck();
                ManualUpDown();            

                if(!bFhmRun &&  !IN_SU1 && ManualSusChk ){
            		UpBttonTime=0;    
            		bManualUpKey=0;
                }
            
                if(!bManualUpKey && !bManualDnKey){
                    if(!OpenKeyCheck() || (LoopTime < 5) ){
                        SelectDoorOpen_you();
                    }
                    else{
                        AllDoorOpenClrCmd_abcdefg();
                    }

		            sRamDArry[mDoor] = (sRamDArry[mDoor] & 0xf5);										   	
                    AllDoorCloseClrCmd_abcdefg();
                }
            }	                   
        }




    DoorOpenEndCheck();            
    InverterErrorCheck();


    if(bCarErr || bCarStopNoRun || bCarStop || bManualStop){
		if(!bOnLuLd){
	        LuLdTime=0;
			bFirstOnLuLd=0;
		}

        bOnceOpen=0;
        CarAllStopCmdTest();      	
        if(!bManualStop){      	        
            if(bCarStopNoRun){
                AllDoorOpenClrCmd_abcdefg();      	
                bTestKey=0;    
            }   
            else if(bCarErr){
                bTestKey=0;                                 		
            }           
    
            bManualAuto=0;    
            bCarStop=0;       
            bCarErr=0;        
        }     	
		bLevelFind=0;	
    }


    DoorOpenClose_you();

    MotorStop();
    AllReadyCheck();
    EtcStopSet();
   	UserLampSet();
	LightOnOff();
    FanOnOff();
    BuzOnOff();
    VoiceStart();
    EmergencyCheck();

    PcCmdSaveChk();

//  	ButtonClrCheck();   

//////////////////////////	CarStopAndNotMoveCheck();
//    InvErrChk();
//    DoorOpenSetChk();

	OUT_U_W(0);
	OUT_D_W(0);             
	OUT_P1(0);             
	OUT_P2(0);           
	OUT_P3(0);             
	OUT_P4(0);             
	OUT_DAC(0);          
		
	OUT_OP(0);              
	OUT_CL(0);              
	OUT_OP_S(0);           
	OUT_CL_S(0);           
	OUT_BK2(0);            
	OUT_D_S(0);              
	OUT_GBR(0);              
	OUT_BRK(0);             
		
	OUT_FAN(0);              
	OUT_LIT(0);            
	OUT_BUZ(0);             
	OUT_BELL(0);           
	OUT_RST(0);           
	OUT_ERR(0);           
	OUT_HOP(0);             
	OUT_HCL(0);            



	if (TestLoop)
	{
		OUT_P4(1);
		OUT_P3(1);
		OUT_P2(1);
		OUT_P1(1);
		OUT_D_W(1); 
		OUT_U_W(1);
	}
	
    OutData();

	SystemErrSave();


	WhyStop();

    sRamDArry[S1_STATE]=S1_STATE_bit;
    sRamDArry[S2_STATE]=S2_STATE_bit;
    sRamDArry[S3_STATE]=S3_STATE_bit;
    sRamDArry[S4_STATE]=S4_STATE_bit;
    sRamDArry[SelDoorStatus]=DoorStatus_bit;
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


    RCON=RCON & 0xc0ff;
    RCON=RCON | 0x1c00;    //4.1v

/*
    while(!BGST){
        CarAllStopCmd();
        asm("RESET");
    }
*/

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



/*
void  __attribute__((section(".usercode")))  FindCurFloor(void)
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
        if(CurPulse <= GET_LONG(FLR_01_PULSE + cF_TOPFLR - 1 )){
            sRamDArry[mcurfloor] = 0;
            CurPulse=0;
        }
    }    


    else if((CurPulse >= GET_LONG(FLR_01_PULSE + (i+1))) || (CurPulse < GET_LONG(FLR_01_PULSE + (i-1))) ){
        sRamDArry[mcurfloor]=0;
        CurPulse=0;
    }    


    DspFloorSet();
}
*/


void  __attribute__((section(".usercode")))  FindCurFloor(void)
{
	unsigned long backup_pulse,save_pulse;

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


	backup_pulse=CurPulse;


    if(sRamDArry[mcurfloor] == 0){
		save_pulse=GET_LONG(FLR_02_PULSE);
        if(backup_pulse >= save_pulse){
//        if(CurPulse >= GET_LONG(FLR_02_PULSE)){
            sRamDArry[mcurfloor] = 0;
            CurPulse=0;
        } 
    }           
    else if(sRamDArry[mcurfloor] > cF_TOPFLR){
        sRamDArry[mcurfloor] = 0;
        CurPulse=0;
    } 
          
    else if(sRamDArry[mcurfloor] == cF_TOPFLR){
		save_pulse=GET_LONG(FLR_01_PULSE + cF_TOPFLR - 1 );
        if(backup_pulse <= save_pulse){
//        if(CurPulse <= GET_LONG(FLR_01_PULSE + cF_TOPFLR - 1 )){
            sRamDArry[mcurfloor] = 0;
            CurPulse=0;
        }
    }    
	else{
		save_pulse=GET_LONG(FLR_01_PULSE + (i+1));
        if(backup_pulse >= save_pulse){
	        sRamDArry[mcurfloor]=0;
	        CurPulse=0;
		}

		save_pulse=GET_LONG(FLR_01_PULSE + (i-1));
        if(backup_pulse < save_pulse){
	        sRamDArry[mcurfloor]=0;
	        CurPulse=0;
		}

/*
	    else if((CurPulse >= GET_LONG(FLR_01_PULSE + (i+1))) || (CurPulse < GET_LONG(FLR_01_PULSE + (i-1))) ){
	        sRamDArry[mcurfloor]=0;
	        CurPulse=0;
	    }    
*/
	}	

    DspFloorSet();
}



//int   main(void)
int   __attribute__((section(".usercode"))) main(void)
{
    unsigned int i;



    PORTA=0xffff;
    PORTB=0xffff;
    PORTC=0xffff;
    PORTD=0xffff;
    PORTE=0xffff;
    PORTF=0xffff;
    PORTG=0xffff;


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
    C2IE       = 0x0;


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


//	CarAllStopCmd();


	for(LogAddressLoop=0;LogAddressLoop < MAX_LONG_BUF;LogAddressLoop++){
        parameter_mirror[LogAddressLoop]=0x0;
	}

	bRelevelErr=0;
	bBefbRelevelErr=0;

	bCarErr=0;
   	bCarStopNoRun=0;
    bManualAuto=0;
	bsLope=0;
   	bsSlip=0;                  
    bSlipCheckStart=0;
	bsNextFloor=0;
	bsLuLdNoOff=0;         	         		        
	bExportData=0;
	bImportData=0;
	bPowerChkStart=0;

    bBefbsBreakMgtOpen=0;
    bBefbsBreakOpen=0;
	bsBreakMgtOpen=0;    
	bsBreakOpen=0;
	bRunningOpenOn=0;   
	bEqualFloorError=0;

    AddressRead();
   
	for(LogAddressLoop=0;LogAddressLoop <= sec;LogAddressLoop++){
		sRamDArry[sRamDArry[mDoorSeq]]=0x0;
	}


	sRamDArry[mDoorSeq]=DOOR_CLOSE_START;
	DoorCloseTime=0;


    sRamDArry[S1_STATE]=S1_STATE_bit=0;
    sRamDArry[S2_STATE]=S2_STATE_bit=0;
    sRamDArry[S3_STATE]=S3_STATE_bit=0;
    sRamDArry[S4_STATE]=S4_STATE_bit=0;
    sRamDArry[SelDoorStatus]=DoorStatus_bit=0;

	Init485_Bd();

	
	bManualAuto=0;
	bHomeUpDn=0;


    INTCON1bits.NSTDIS=1;



    QEI_Init(); 
    LvdInit();
    Timer1Init();
    Uart1Init();
    Uart2Init();
    Can1Init();
    Can2Init();


    INTCON1bits.NSTDIS=1;



    asm("CLRWDT");
    ReadInitSetupData();
    asm("CLRWDT");


    if(!SWR){
        asm("RESET");
    }
    SWR=0;

    Ladder485Init();

#ifndef		RS485_FOR_CRT	
	Init485_Ladder();
   	RxStatus=STX_CHK;
   	MyDataTx();
#endif

      
   	sRamDArry[LD_INSP] = 0x0;

   
   	NoCloseCnt=0;
   	WarmingUpTime=0;
   	CurFTime=0;
   	NextFTime=0;
	SaveVerify=0;
   	    

	sRamDArry[mMostLongDst]= 0x00;
	sRamDArry[mStartFloor] = 0;   //delete value




    while(WarmingUpTime < 10){
        InPutRead();
        asm("CLRWDT");
    }        

//	OnOffFlrResetting();



    if(INVERTER_CHECK == IO){
        FindCurFloor();
    }

    C1Loop=0;
    C2Loop=0;
	bSlaveEarthquake=0;
   	bSlavePrk=0;
	bSubSlavePrk=0;

	bSlaveFire=0;
	bSubSlaveFire=0;

    bPC_PRK=0;
    bPC_FIRE=0;
	bPC_FAMILY=0;

    disp_clk_regs();
    UseBaseTime = sRamDArry[Hour];
    sRamDArry[FHM_RUN]=0;
    sRamDArry[FHM_SEQ]=0;


    bCarService=0;



    PowerOnTime=0x0;

    PowerOnTime=EEPROM_Read_Word(e_PowerOnTime);
    CurDoorSelect=EEPROM_Read_Word(e_CurDoorSelect);


    NotRecoveryData=0;
#ifdef	GOBERNOR_LOCK
    NotRecoveryData=EEPROM_Read_Word(e_GBR);
	if( NotRecoveryData & 0x01)	bsSlip=1;
	if( NotRecoveryData & 0x02)	bsLope=1;
#endif


	SaveMoveCounter=0;
	LevelEncoderPulse2=0;


	sRamDArry[ExtCmdFlrONOFF0]=cF_NONSERVICE0;
	sRamDArry[ExtCmdFlrONOFF1]=cF_NONSERVICE1;
	sRamDArry[ExtCmdFlrONOFF2]=cF_NONSERVICE2;
	sRamDArry[ExtCmdFlrONOFF3]=cF_NONSERVICE3;

	if(FamilyService)	bPC_FAMILY=1;
	else				bPC_FAMILY=0;
	
	CmdFixFlrTime=cF_FIXFLOORTIME;


	bBK1=0;
	BreakTime=0;


    do{

		ReadEncoder();
        AddressRead();

        IO_Check();                                
        SerialCheck();
        Serial2Check();

        asm("CLRWDT");

        Can1Check();
        Can2Check();

        disp_clk_regs();

        asm("CLRWDT");
   	}while(1);                                  
}






void _ISR _T1Interrupt(void)
{
    if( _T1IF ){

        _T1IF = 0 ;
        TMR1=0;

//		MainLoopTime++;

        if(EepTime<50)    EepTime++;


        EmgTime++;
        PrkTime++;
        AtTime++;
        UbTime++;
        DbTime++;
        OlsTime++;
        GsTime++;
        DsTime++;

        Su1Time++;
        Sd1Time++;
        SftTime++;
        OvlTime++;
        UlsTime++;
        DlsTime++;
        LuTime++;
        LdTime++;

        RgTime++;
        BatTime++;
        PassTime++;
        FireTime++;
        WaterTime++;
        FullTime++;
        MmTime++;
        FhmInTime++;

        Fr1Time++;
        Fr2Time++;
        Gs2Time++;
        Ds2Time++;
        Su2Time++;
        Sd2Time++;
        BmTime++;
        InvTime++;

		Fs0Time++;
		Fs1Time++;
		Fs2Time++;
		Fs3Time++;
		Fs4Time++;
		DerTime++;
		FidTime++;
		UndTime++;


        X0Time++;
        X1Time++;
        X2Time++;
        X3Time++;
        X4Time++;
        X5Time++;
        X6Time++;
        X7Time++;
        

        I_EMG_Cht++;
        I_FS0_Cht++;
        I_GR_Cht++;
        I_SU1_Cht++;
        I_X_0_Cht++;
        I_FIRE_Cht++;



        C1Time++;
        C2Time++;    
        SerialTime2++;

		

#ifndef		RS485_FOR_CRT	  
        SerialTime++;  
        if(SerialTime>10){
            TimeOutBd++;
            SerialTime=0;
        }
#else
        if(SerialTime < 100)	SerialTime++;
#endif


        if(bOpenDoorOk && (DoorOpenOnTime<250)){	
            DoorOpenOnTime++;
        }


        if((!IN_LU || !IN_LD) && (LuLdTime < 50000)){
			if(bFirstOnLuLd)	LuLdTime++;
        }


        if(LadderTime  < 20002)  LadderTime++;


		if(EncoderReloadTime < 1000)	EncoderReloadTime++;	


        msec10++;
        if(msec10 > 100){
            msec10=0;

			OUT_RUN = !OUT_RUN;

			if(TmpBuzor < 100)	TmpBuzor++;

            if(RstTime < 65530) RstTime++;

            C2Loop++;

            if(CurPulse>BefCurPulse){
                PulsePer100Msec=CurPulse-BefCurPulse;
                CountDn=0;    
                CountUp++;    
            }
            else if(CurPulse<BefCurPulse){
                PulsePer100Msec=BefCurPulse-CurPulse;    
                CountUp=0;    
                CountDn++;    
            }
            else{
                PulsePer100Msec=BefCurPulse-CurPulse;    
                CountUp=0;    
                CountDn=0;    
            }
            BefCurPulse=CurPulse;

			if(EncoderReloadTime > 200){            
	            TmpMmPerMin=GET_LONG(MPM_VARIABLE);
	            CurMeterPerMin=(PulsePer100Msec * TmpMmPerMin);
	            CurMeterPerMin=(CurMeterPerMin/(unsigned long)1000000);
			}



            if(CarOnceStopTime < 250)   CarOnceStopTime++;        
            if(PowerFailTime<250)       PowerFailTime++;
            if(LoopTime<100)            LoopTime++;


            if(!bMoveCar){
                CounterTime=0;
                ElevMoveTime=0;
                if(ElevStopTime < 250)    ElevStopTime++;
            }
            else{
                ElevStopTime=0;
                if(CounterTime < 250)   CounterTime++;
                if(ElevMoveTime < 5000)  ElevMoveTime++;
            }  


            if(bLevelFind){  
                if(RelevelTime < 250)  RelevelTime++;

                if(RelevelTime > 240){
        	        CarAllStopCmd();
                }
            }
            else    RelevelTime=0;

			
            FhmLoaderTime++;
            CurFTime++;
            NextFTime++;
            errtime++;
            DoorCloseTime++;
            DoorOpenTime++;
            NextFloorTime++;       
            UpBttonTime++;
            DnBttonTime++;   
            SerialLoopMaxTime++;

///////////			if(PowerSlipTimer < 200)	PowerSlipTimer++;

			if(BreakTime  < 1000)		BreakTime++;

			if(SolTimer < 100)			SolTimer++;
			if(SolWaitTimer < 100)		SolWaitTimer++;
            if(FhmTime<100)             FhmTime++;
            if(SelMainCarTime < 100)    SelMainCarTime++;
            if(SelSubCarTime < 100)     SelSubCarTime++;
            if(LadderKeyTime < 36500)   LadderKeyTime++;
            if(WarmingUpTime < 210)     WarmingUpTime++;                                 
//            if(OpenOutOffTime < 250)    OpenOutOffTime++;
            if(CloseOutOffTime < 250)   CloseOutOffTime++;
            if(ExIOTimer < 250)   		ExIOTimer++;
			if(HuntingTimer < 100)		HuntingTimer++;

            if(bUnd){
                if(VoiceTime < 250) VoiceTime++;
                if(BellTime < 250) BellTime++;
            }
            else{
		        VoiceTime=0;
				BellTime=0;
			}

            if( bDoorCloseOkSensor && (DoorCloseOnTime<250)){
                DoorCloseOnTime++;
            }


            sec1++;
            if(sec1 >= 10){
                sec1=0;
                bDspSeq=!bDspSeq;
                FanTime++; 
				if(AccTimer < 254)			AccTimer++;							 
                if(FixFlrTimeCnt <= 254)	FixFlrTimeCnt++;
            }

            MinuteTime++;
            if(MinuteTime>=600){
                MinuteTime=0;        
//                FixFlrTimeCnt++;
                LightTime++;

				UseBaseTime++;
				if(UseBaseTime >= 60){
					UseBaseTime=0;
        			if(PowerOnTime < 65530) PowerOnTime++;
					else					PowerOnTime=0;
				}	

                if(InvErrTime < 600)    InvErrTime++;
            }        

            if(bManualStop){
                if(ManualStopTime < 100)  ManualStopTime++;
            }
            else	ManualStopTime=0;


            if(bFR2Start1 && (sRamDArry[mFireSeq]==FIRE_THREE)){
                if(RestartTime<60)  RestartTime++;
            }
            else{
                RestartTime=0;
            }

#ifdef  TEST_SIMULATION  
            if(bMoveCar){
                if(MotorMoveTime<250)	MotorMoveTime++;
            }
            else{
        		MotorMoveTime=0;    
            }

			hdhTimer++;
			if (hdhTimer >= 2)
			{
				hdhTimer = 0;
				TestLoop = ~TestLoop;
			}		
#endif

        }      
    }
}




void _ISR _OscillatorFail(void)
{

    INTCON1bits.OSCFAIL=0;
    asm("RESET");
}


void _ISR _AddressError(void)
{   
    INTCON1bits.ADDRERR=0;
    asm("RESET");
}


void _ISR _StackError(void)
{   
    INTCON1bits.STKERR=0;
    asm("RESET");
}




void _ISR _MathError(void)
{   
    INTCON1bits.MATHERR=0;
    asm("RESET");
}



void	SaveEEpromPulse(void)
{
    unsigned int i;

	CarAllStopCmd();
	CarAllStopCmd();

    if(INVERTER_CHECK == IO){
	    if(!bSaveFlash){
	        i=(unsigned int)sRamDArry[mcurfloor];
	
	        while(EEPROM_Write_Word(e_CurFloor,i));
	
	        i=(unsigned int)CurPulse;
	        while(EEPROM_Write_Word(e_CurPulse,i));
	
	        i=(unsigned int)(CurPulse >> 16);
	        while(EEPROM_Write_Word(e_CurPulse+2,i));
	    
	        bSaveFlash=1;
	    }
	}

	SaveMoveCounter=10;
	if(MoveCounterx > 0){
 		MoveCounterx=(MoveCounterx -1);	
		MvCounter();
	}

    if(WarmingUpTime > 100){     
        while(EEPROM_Write_Word(e_CurDoorSelect,(unsigned int)CurDoorSelect));
        while(EEPROM_Write_Word(e_PowerOnTime,(unsigned int)PowerOnTime));


#ifdef	GOBERNOR_LOCK
		if(NotRecoveryData & 0x8000){
		    NotRecoveryData=(NotRecoveryData & 0x7fff);
		    NotRecoveryData=(NotRecoveryData & 0xfffc);
		}
		else{
		    if(bsSlip)	NotRecoveryData=(NotRecoveryData | 0x01);
		    if(bsLope)  NotRecoveryData=(NotRecoveryData | 0x02);
		}	
	    while(EEPROM_Write_Word(e_GBR,NotRecoveryData));
#endif

    }
}


void _ISR _LVDInterrupt(void)
{

	SaveEEpromPulse();
    LVDIF=0;
    asm("RESET");
}




void _ISR _DefaultInterrupt(void)
{
	SaveEEpromPulse();
    asm("RESET");
}





