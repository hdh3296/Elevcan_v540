
#include  "iodef.h"
#include  "30f6010_io.h"            
#include  "default_setup.h" 


void  __attribute__((section(".usercode"))) Pc_Command(void);

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

#define     ONEKEY                  '1'      
#define     TWOKEY                  '2'      
#define     THREEKEY                '3'      
#define     FOURKEY                 '4'
#define     FIVEKEY                 '5'      
#define     SIXKEY                  '6'
#define     SEVENKEY                '7'      
#define     EIGHTKEY                '8'      
#define     NINEKEY                 '9'      
#define     ZEROKEY                 '0'
#define     ENTKEY                  'e'      
#define     MENUKEY                 'm'      
#define     ESCKEY                  'c'      
#define     UPKEY                   'u'      
#define     DOWNKEY                 'd'
#define     LEFTKEY                 'l'      
#define     RIGHTKEY                'r'
#define     ENTKEY                  'e'      


#define     DIGIT_EDIT              0
#define     DIGIT_ALPHAR_EDIT       1
#define     TABLE_EDIT              2
#define     TOGGLE_EDIT             3
#define     DIGIT_STRING_EDIT       4
#define     CLOCK_EDIT              5
#define     NO_EDIT                 6



#define SECONDLINE_CURSOR           1
#define SECONDLINE_BASE             18


#define USER_GROUP                  1
#define FLR_DSP_GROUP               2
#define FLR_GROUP                   3
#define TIMER_GROUP                 4
#define ONOFF1_GROUP                5
#define ONOFF2_GROUP                6
#define SUB_DOOR_GROUP              7
#define IO_GROUP                    8
#define OPEN_WAIT_GROUP             9
#define PARAMETER_GROUP             10
#define NCNO1_GROUP                 11
#define NCNO2_GROUP                 12
#define NCNO3_GROUP                 13
#define INPORT1_GROUP               14
#define INPORT2_GROUP               15
#define OUTPORT_GROUP               16
#define ERROR_GROUP                 17
#define MAX_GROUP                   18


#define FLR_DSP_GROUP_MAX           32
#define FLR_GROUP_MAX               16
#define TIMER_GROUP_MAX             25
#define ONOFF1_GROUP_MAX            32
#define ONOFF2_GROUP_MAX            32
#define NCNO1_GROUP_MAX             32
#define NCNO2_GROUP_MAX             16
#define NCNO3_GROUP_MAX             23
#define IO_GROUP_MAX                24
//#define USER_GROUP_MAX              19 + 2
#define USER_GROUP_MAX              32

#define OPEN_WAIT_GROUP_MAX         4
#define PARAMETER_GROUP_MAX         32
#define INPORT1_GROUP_MAX           32
#define INPORT2_GROUP_MAX           16
#define OUTPORT_GROUP_MAX           23
//#define ERROR_GROUP_MAX             20
#define ERROR_GROUP_MAX             40



#define     NORMAL_DSP_MESSAGE_CNT  32
#define     INIT_MESSAGE            8 
#define     USER_LAMP_MESSAGE_CNT   10
#define     ELEV_SPEED_MESSAGE_CNT  9
#define     IO_PORT_MESSAGE_CNT     9
#define     ELEV_BD_ID_MESSAGE_CNT  10
#define     ELEV_ONOFF_MESSAGE_CNT  32
#define     ENCODERRATE_MESSAGE_CNT 4

#define     INPORT1_SEL_MESSAGE_CNT 32
#define     INPORT2_SEL_MESSAGE_CNT 32
#define     OUTPORT_SEL_MESSAGE_CNT 32
#define     DOOR_SEL_MESSAGE_CNT 	4



#define     MAX_LADDER_BUF          40


#define     TOP_FLR                 0 
#define     PRK_FLR                 1 
#define     NO_USE_GO_FLR           2 
#define     FIRE_SAFE_FLR           3 
#define     X7_SAFE_FLR             4
#define     WATER_SAFE_FLR          5 
#define     START_FLR               6 
#define     ONE_STOP_FLR            7
#define     KIDS_KEY_CNT            8
#define     X6_SAFE_FLR             9
#define     X5_SAFE_FLR             10
#define     NC21FLR                 11
#define     NC20FLR                 12
#define     NC19FLR                 13
#define     NC18FLR                 14
#define     NC17FLR                 15
#define     NC16FLR                 16
#define     NC15FLR                 17
#define     NC14FLR                 18
#define     NC13FLR                 19
#define     NC12FLR                 20
#define     NC11FLR                 21
#define     NC10FLR                 22
#define     NC09FLR                 23
#define     NC08FLR                 24
#define     NC07FLR                 25
#define     NC06FLR                 26
#define     NC05FLR                 27
#define     NC04FLR                 28
#define     NC03FLR                 29
#define     NC02FLR                 30
#define     NC01FLR                 31


#define     VERSION                 0  
#define     BOARD_ID                1 
#define     PASSWARD                2
#define     USER_LAMP1              3
#define     USER_LAMP2              4
#define     SERIAL_NM               5   
#define     NORMAL_DSP              6  
#define     DRIVE_METHOD            7  
#define     FHM_RUN_CHK             8  
#define     ALL_MENU_CHK            9 
#define     ENGINEER_NM             10
#define     TOTAL_USE_TIME          11 
#define     INIT_DATA               12 
#define     GROUP_NUMBER            13 
#define     LOCAL_NUMBER            14 
#define     LG_INV_IN_BD            15 
#define     VIRTUAL_CALL            16 
#define     HH_MM_SS                17 
#define     YY_MM_DD                18 
#define     ERR_ST_CNT              19  
#define     COMPANY_NAME            20
#define     OUT_DATE         		21
#define     USER_LAMP3              22
#define     USER_LAMP4              23
#define     HALL_IND_SET            24
#define     User_G4                 25
#define     User_G5                 26
#define     User_G6                 27
#define     User_G7                 28
#define     User_G8                 29
#define     AIRCON_ADDR             30
#define     ENCODER_RATE            31

  
//#define     COMPANY_NAME_SET        21


#define     FHM_CHK                 0
#define     DR_JMP_CHK              1
#define     ENCODER_PH              2
#define     ONOFF2_29               3
#define     ONOFF2_28               4
#define     ONOFF2_27               5
#define     ONOFF2_26               6    
#define     ONOFF2_25               7
#define     ONOFF2_24               8
#define     ONOFF2_23               9
#define     ONOFF2_22               10
#define     ONOFF2_21               11
#define     ONOFF2_20               12    
#define     ONOFF2_19               13
#define     ONOFF2_18               14
#define     ONOFF2_17               15
#define     ONOFF2_16               16    
#define     ONOFF2_15               17
#define     ONOFF2_14               18    
#define     ONOFF2_13               19
#define     ONOFF2_12               20
#define     ONOFF2_11               21
#define     ONOFF2_10               22
#define     ONOFF2_9                23
#define     ONOFF2_8                24
#define     ONOFF2_7                25
#define     ONOFF2_6                26
#define     ONOFF2_5                27
#define     ONOFF2_4                28
#define     ONOFF2_3                29
#define     ONOFF2_2                30
#define     ONOFF2_1                31



#define     P_ENCODER_PULSE         0  
#define     P_TM_MPM                1  
#define     P_MOTOR_RPM             2  
#define     P_DEC30                 3  
#define     P_DEC45                 4  
#define     P_DEC60                 5  
#define     P_DEC90                 6  
#define     P_DEC105                7  
#define     P_DEC120                8  
#define     P_DEC150                9  
#define     P_DEC180                10 
#define     P_DEC210                11
#define     P_MINDEC30              12  
#define     P_MINDEC45              13 
#define     P_MINDEC60              14 
#define     P_MINDEC90              15 
#define     P_MINDEC105             16 
#define     P_MINDEC120             17 
#define     P_MINDEC150             18 
#define     P_MINDEC180             19 
#define     P_MINDEC210             20 
#define     P_PAR1                  21
#define     P_PAR2                  22
#define     P_PAR3                  23 
#define     P_PAR4            		24
#define     P_PAR5                  25
#define     P_PAR6                  26
#define     P_PAR7                  27
#define     P_PAR8                  28
#define     P_PAR9                  29
#define     P_PAR10                 30
#define     P_PAR11                 31


//#define     P_STOP_PULSE            12


UserDataType    New485Ladder[MAX_LADDER_BUF]={0};      


UserDataType    GroupBaseAddr;
UserDataType    LadderGroup;
UserDataType    LadderGroupSub;
UserDataType    LadderKey;
UserDataType    EnterKey;
UserDataType    Cursor;
UserDataType    EditStatus;
UserDataType    EditBlanck;
UserDataType    ShiftCnt;
UserDataType    MaxSubMenu;
UserDataType    MemPointer;


UserDataType   pw[4];

unsigned int   DigitData;
unsigned int   DigitMaxValue;
unsigned int   DigitMinValue;
unsigned int   OrgNcNo;



const unsigned char BdName485[][4]={"000"," 01"," 02"," 03"," 04"," 05"," 06"," 07"," 08"," 09"," 10",
                                          " 11"," 12"," 13"," 14"," 15"," 16"," 17"," 18"," 19"," 20",
                                          " 21"," 22"," 23"," 24"," 25"," 26"," 27"," 28"," 29"," 30",
                                          " 31"," 32","AVO","BVO","CVO","DVO","AC1","AC2","AC3","AC4",
                                          "BC1","BC2","BC3","BC4","CC1","CC2","CC3","CC4","DC1","DC2",
                                          "DC3","DC4","AXO","AX1","BXO","BX1","CXO","CX1","DXO","DX1",
                                          "A_M","BM1","BM2","CM1","CM2","DM1","DM2","ALD","BLD","CLD",
                                          "DLD","APC","BPC","CPC","DPC"};


const unsigned char GroupLineMessage[][17]={
                                    "FL:00           ",//0
///////////////////////////////////////////////////////////                                                                                                           
                                    "USER:Version    ",//1  
                                    "USER:BoardId    ",//2 
                                    "USER:Passward   ",//3  
                                    "USER:UserLamp1  ",//4  
                                    "USER:UserLamp2  ",//5  
                                    "USER:SerialNm   ",//6  
                                    "USER:Normal Dsp ",//7  
                                    "USER:DriveMethod",//8 
                                    "USER:Fhm Run    ",//9 
                                    "USER:SubMenu On ",//10 
                                    "USER:Engineer Nm",//11 
                                    "USER:Tt Use Time",//12 
                                    "USER:Init Data  ",//13 
                                    "USER:Group Nm   ",//14 
                                    "USER:Local Nm   ",//15 
                                    "USER:Inv InBd Tp",//16
                                    "USER:Call(c-f-f)",//17
                                    "USER:hh-mm-ss   ",//18 
                                    "USER:yy-mm-dd   ",//19
                                    "USER:ErrStCnt   ",//20  
                                    "USER:Company    ",//21									  
                                    "USER:OutDate    ",//22  
                                    "USER:UserLamp3  ",//23  
                                    "USER:UserLamp4  ",//24  
                                    "USER:C-K-H-O-B-R",//25  //cancle,openkey,halllantern,offset,button type,reserve
                                    "USER:User4      ",//26 
                                    "USER:User5      ",//27 
                                    "USER:User6      ",//28 
                                    "USER:User7      ",//29 
                                    "USER:User8      ",//30 
                                    "USER:Aircon Addr",//31  
//                                    "USER:EncoderRate",//32 
                                    "USER: Stop Pulse",//32 
///////////////////////////////////////////////////////////                                    
                                    "DSP:Floor01     ",//1
                                    "DSP:Floor02     ",//2
                                    "DSP:Floor03     ",//3
                                    "DSP:Floor04     ",//4
                                    "DSP:Floor05     ",//5
                                    "DSP:Floor06     ",//6
                                    "DSP:Floor07     ",//7
                                    "DSP:Floor08     ",//8
                                    "DSP:Floor09     ",//9
                                    "DSP:Floor10     ",//0
                                    "DSP:Floor11     ",//11
                                    "DSP:Floor12     ",//12
                                    "DSP:Floor13     ",//13
                                    "DSP:Floor14     ",//14
                                    "DSP:Floor15     ",//15
                                    "DSP:Floor16     ",//16
                                    "DSP:Floor17     ",//17
                                    "DSP:Floor18     ",//18
                                    "DSP:Floor19     ",//19
                                    "DSP:Floor20     ",//20
                                    "DSP:Floor21     ",//21
                                    "DSP:Floor22     ",//22
                                    "DSP:Floor23     ",//23
                                    "DSP:Floor24     ",//24
                                    "DSP:Floor25     ",//25
                                    "DSP:Floor26     ",//26
                                    "DSP:Floor27     ",//27
                                    "DSP:Floor28     ",//28
                                    "DSP:Floor29     ",//29
                                    "DSP:Floor30     ",//30
                                    "DSP:Floor31     ",//31
                                    "DSP:Floor32     ",//32
///////////////////////////////////////////////////////////                                    
                                    "FLR:TopFlr      ",//1 
                                    "FLR:PrkFlr      ",//2 
                                    "FLR:NoUse Go Flr",//3 
                                    "FLR:FireSafe Flr",//4 
                                    "FLR:X7 Safe  Flr",//5 
                                    "FLR:WaterSafeFlr",//6 
                                    "FLR:Start Flr   ",//7
                                    "FLR:OneStop Flr ",//8
                                    "FLR:Kids Key Cnt",//9
                                    "FLR:X6 Safe  Flr",//10
                                    "FLR:X5 Safe  Flr",//11
                                    "FLR:Nc21Flr     ",//12
                                    "FLR:Nc20Flr     ",//13
                                    "FLR:Nc19Flr     ",//14
                                    "FLR:Nc18Flr     ",//15
                                    "FLR:Nc17Flr     ",//16
                                    "FLR:Nc16Flr     ",//17
                                    "FLR:Nc15Flr     ",//18
                                    "FLR:Nc14Flr     ",//19
                                    "FLR:Nc13Flr     ",//20
                                    "FLR:Nc12Flr     ",//21
                                    "FLR:Nc11Flr     ",//22
                                    "FLR:Nc10Flr     ",//23
                                    "FLR:Nc09Flr     ",//24
                                    "FLR:Nc08Flr     ",//25
                                    "FLR:Nc07Flr     ",//26
                                    "FLR:Nc06Flr     ",//27
                                    "FLR:Nc05Flr     ",//28
                                    "FLR:Nc04Flr     ",//29
                                    "FLR:Nc03Flr     ",//30
                                    "FLR:Nc02Flr     ",//31
                                    "FLR:Nc01Flr     ",//32
///////////////////////////////////////////////////////////                                                                       
                                    "TMR:Op Wait Time",// 1
                                    "TMR:Op Total Tm ",// 2
                                    "TMR:No Use Time ",// 3
                                    "TMR:NextFlr Time",// 4
                                    "TMR:LuLdOff Time",// 5
                                    "TMR:Fan Off Time",// 6
                                    "TMR:Lit Off Time",// 7
                                    "TMR:OpClWaitTime",// 8
                                    "TMR:DrJmpChkTime",// 9
                                    "TMR:Dir Set Time",//10
                                    "TMR:Voice OnTime",//11
                                    "TMR:Brk Mgt Time",//12
                                    "TMR:ReOpen  Time",//13
                                    "TMR:P4  On  Time",//14
                                    "TMR:U/D On  Time",//15
                                    "TMR:Bk2 On  Time",//16
                                    "TMR:Bk1 On  Time",//17
                                    "TMR:Run On  Time",//18
                                    "TMR:Run Off Time",//19
                                    "TMR:Bk1 Off Time",//20
                                    "TMR:Bk2 Off Time",//21
                                    "TMR:U/D Off Time",//22
                                    "TMR:P4  Off Time",//23
                                    "TMR:Sol On  Time",//24
                                    "TMR:Door St Time",//25
                                    "TMR:Stop9   Time",//26
                                    "TMR:Stop10  Time",//27
                                    "TMR:Stop11  Time",//28
                                    "TMR:Stop12  Time",//29
                                    "TMR:Stop13  Time",//30
                                    "TMR:Stop14  Time",//31
                                    "TMR:Stop15  Time",//32
///////////////////////////////////////////////////////////                                                                                                           
                                    "ONOFF1:Floor01  ",//1 
                                    "ONOFF1:Floor02  ",//2 
                                    "ONOFF1:Floor03  ",//3 
                                    "ONOFF1:Floor04  ",//4  
                                    "ONOFF1:Floor05  ",//5  
                                    "ONOFF1:Floor06  ",//6  
                                    "ONOFF1:Floor07  ",//7  
                                    "ONOFF1:Floor08  ",//8  
                                    "ONOFF1:Floor09  ",//9  
                                    "ONOFF1:Floor10  ",//10 
                                    "ONOFF1:Floor11  ",//11 
                                    "ONOFF1:Floor12  ",//12
                                    "ONOFF1:Floor13  ",//13
                                    "ONOFF1:Floor14  ",//14
                                    "ONOFF1:Floor15  ",//15
                                    "ONOFF1:Floor16  ",//16
                                    "ONOFF1:Floor17  ",//17
                                    "ONOFF1:Floor18  ",//18
                                    "ONOFF1:Floor19  ",//19
                                    "ONOFF1:Floor20  ",//20
                                    "ONOFF1:Floor21  ",//21
                                    "ONOFF1:Floor22  ",//22
                                    "ONOFF1:Floor23  ",//23
                                    "ONOFF1:Floor24  ",//24
                                    "ONOFF1:Floor25  ",//25
                                    "ONOFF1:Floor26  ",//26
                                    "ONOFF1:Floor27  ",//27
                                    "ONOFF1:Floor28  ",//28
                                    "ONOFF1:Floor29  ",//29
                                    "ONOFF1:Floor30  ",//30
                                    "ONOFF1:Floor31  ",//31
                                    "ONOFF1:Floor32  ",//32
///////////////////////////////////////////////////////////                
                                                                                           
///////////////////////////////////////////////////////////                                                                                                           
                                    "ONOFF2:FHM Chk  ",//1 
                                    "ONOFF2:DrJmpChk ",//2 
                                    "ONOFF2:EncoderPh",//3 
                                    "ONOFF2:WardPrior",//4  
                                    "ONOFF2:NonStop  ",//5  
                                    "ONOFF2:OpenTotal",//6  
                                    "ONOFF2:WaitTotal",//7  
                                    "ONOFF2:ClosTotal",//8  
                                    "ONOFF2:C_Dr1 Chk",//9  
                                    "ONOFF2:C_Dr2 Chk",//10  
                                    "ONOFF2:H_Dr1 Chk",//11
                                    "ONOFF2:H_Dr2 Chk",//12 
                                    "ONOFF2:S_Sft Chk",//13
                                    "ONOFF2:MgtMonChk",//14
                                    "ONOFF2:Encod Chk",//15
                                    "ONOFF2:ReleveChk",//16
                                    "ONOFF2:OilLopeTy",//17
                                    "ONOFF2:1 CallChk",//18
                                    "ONOFF2:ManSusChk",//19
                                    "ONOFF2:BrkMonChk",//20
                                    "ONOFF2:KidKeyClr",//21
                                    "ONOFF2:F_CarKey ",//22
                                    "ONOFF2:SingleCar",//23
                                    "ONOFF2:OpOutSet ",//24
                                    "ONOFF2:SftUse RL",//25
                                    "ONOFF2:Floor Sel",//26
                                    "ONOFF2:RunningOp",//27
                                    "ONOFF2:Not Use  ",//28
                                    "ONOFF2:Not Use  ",//29
                                    "ONOFF2:Not Use  ",//30
                                    "ONOFF2:Not Use  ",//31
                                    "ONOFF2:Work Mode",//32
///////////////////////////////////////////////////////////                                                                                                           
                                    "DOOR-S:Floor01  ",//1 
                                    "DOOR-S:Floor02  ",//2 
                                    "DOOR-S:Floor03  ",//3 
                                    "DOOR-S:Floor04  ",//4  
                                    "DOOR-S:Floor05  ",//5  
                                    "DOOR-S:Floor06  ",//6  
                                    "DOOR-S:Floor07  ",//7  
                                    "DOOR-S:Floor08  ",//8  
                                    "DOOR-S:Floor09  ",//9  
                                    "DOOR-S:Floor10  ",//10 
                                    "DOOR-S:Floor11  ",//11 
                                    "DOOR-S:Floor12  ",//12
                                    "DOOR-S:Floor13  ",//13
                                    "DOOR-S:Floor14  ",//14
                                    "DOOR-S:Floor15  ",//15
                                    "DOOR-S:Floor16  ",//16
                                    "DOOR-S:Floor17  ",//17
                                    "DOOR-S:Floor18  ",//18
                                    "DOOR-S:Floor19  ",//19
                                    "DOOR-S:Floor20  ",//20
                                    "DOOR-S:Floor21  ",//21
                                    "DOOR-S:Floor22  ",//22
                                    "DOOR-S:Floor23  ",//23
                                    "DOOR-S:Floor24  ",//24
                                    "DOOR-S:Floor25  ",//25
                                    "DOOR-S:Floor26  ",//26
                                    "DOOR-S:Floor27  ",//27
                                    "DOOR-S:Floor28  ",//28
                                    "DOOR-S:Floor29  ",//29
                                    "DOOR-S:Floor30  ",//30
                                    "DOOR-S:Floor31  ",//31
                                    "DOOR-S:Floor32  ",//32
///////////////////////////////////////////////////////////                

///////////////////////////////////////////////////////////                                                                                                           
                                    "I_O:ManSpd  Port",//1  
                                    "I_O:BatSpd  Port",//2  
                                    "I_O:DecSpd  Port",//3  
                                    "I_O:FHMSpd  Port",//4  
                                    "I_O:Spd30   Port",//5  
                                    "I_O:Spd45   Port",//6  
                                    "I_O:Spd60   Port",//7  
                                    "I_O:Spd90   Port",//8 
                                    "I_O:Spd105  Port",//9 
                                    "I_O:Spd120  Port",//10 
                                    "I_O:Spd150  Port",//11 
                                    "I_O:Spd180  Port",//12 
                                    "I_O:Spd210  Port",//13 
                                    "I_O:Etc1Spd Port",//14  
                                    "I_O:Etc2Spd Port",//15  
                                    "I_O:Elev Max Spd",//16 
                                    "I_O:Limt Max Spd",//17
                                    "I_O:MaxSuSd1 Spd",//18 
                                    "I_O:MaxSuSd2 Spd",//19 
                                    "I_O:MaxX0X1  Spd",//20                                   
                                    "I_O:Spd1        ",//21 
                                    "I_O:Spd2        ",//22 
                                    "I_O:Spd3        ",//23 
                                    "I_O:Spd4        ",//24 
                                    "I_O:Spd5        ",//25  
                                    "I_O:Spd6        ",//26 
                                    "I_O:Spd7        ",//27 
                                    "I_O:Spd8        ",//28 
                                    "I_O:Spd9        ",//29 
                                    "I_O:Spd10       ",//30 
                                    "I_O:Spd11       ",//31 
                                    "I_O:Spd12       ",//32 
///////////////////////////////////////////////////////////                                                                                                           
                                    "W_FLR:(1)hm_hm_F",//1  
                                    "W_FLR:(2)hm_hm_F",//2  
                                    "W_FLR:(3)hm_hm_F",//3  
                                    "W_FLR:(4)hm_hm_F",//4  
                                    "W_FLR:Time0910  ",//5  
                                    "W_FLR:Time1011  ",//6  
                                    "W_FLR:Time1112  ",//7  
                                    "W_FLR:Time1213  ",//8  
                                    "W_FLR:Time1314  ",//9  
                                    "W_FLR:Time1415  ",//10 
                                    "W_FLR:Time1516  ",//11 
                                    "W_FLR:Time1617  ",//12 
                                    "W_FLR:Time1718  ",//13 
                                    "W_FLR:Time1819  ",//14 
                                    "W_FLR:Time1920  ",//15 
                                    "W_FLR:Time2021  ",//16 
                                    "W_FLR:Time2105  ",//17 
                                    "W_FLR:Time0002  ",//18 
                                    "W_FLR:Time0003  ",//19 
                                    "W_FLR:Time0004  ",//20 
                                    "W_FLR:Time0005  ",//21 
                                    "W_FLR:Time0006  ",//22 
                                    "W_FLR:Time0007  ",//23 
                                    "W_FLR:Time0008  ",//24 
                                    "W_FLR:Time0009  ",//25 
                                    "W_FLR:Time0010  ",//26 
                                    "W_FLR:Time0011  ",//27 
                                    "W_FLR:Time0012  ",//28 
                                    "W_FLR:Time0013  ",//29 
                                    "W_FLR:Time0014  ",//30 
                                    "W_FLR:Prk S_Time",//31 
                                    "W_FLR:Prk E_Time",//32 

/*
                                    "W_FLR:Time0506  ",//1  
                                    "W_FLR:Time0607  ",//2  
                                    "W_FLR:Time0708  ",//3  
                                    "W_FLR:Time0809  ",//4  
                                    "W_FLR:Time0910  ",//5  
                                    "W_FLR:Time1011  ",//6  
                                    "W_FLR:Time1112  ",//7  
                                    "W_FLR:Time1213  ",//8  
                                    "W_FLR:Time1314  ",//9  
                                    "W_FLR:Time1415  ",//10 
                                    "W_FLR:Time1516  ",//11 
                                    "W_FLR:Time1617  ",//12 
                                    "W_FLR:Time1718  ",//13 
                                    "W_FLR:Time1819  ",//14 
                                    "W_FLR:Time1920  ",//15 
                                    "W_FLR:Time2021  ",//16 
                                    "W_FLR:Time2105  ",//17 
                                    "W_FLR:Time0002  ",//18 
                                    "W_FLR:Time0003  ",//19 
                                    "W_FLR:Time0004  ",//20 
                                    "W_FLR:Time0005  ",//21 
                                    "W_FLR:Time0006  ",//22 
                                    "W_FLR:Time0007  ",//23 
                                    "W_FLR:Time0008  ",//24 
                                    "W_FLR:Time0009  ",//25 
                                    "W_FLR:Time0010  ",//26 
                                    "W_FLR:Time0011  ",//27 
                                    "W_FLR:Time0012  ",//28 
                                    "W_FLR:Time0013  ",//29 
                                    "W_FLR:Time0014  ",//30 
                                    "W_FLR:Prk S_Time",//31 
                                    "W_FLR:Prk E_Time",//32 
*/
///////////////////////////////////////////////////////////                                                                                                           
                                    "PAR:EncoderPulse",//1  
                                    "PAR: TM Mpm     ",//2  
                                    "PAR:Motor Rpm   ",//3  
                                    "PAR:Dec30 Length",//4  
                                    "PAR:Dec45 Length",//5  
                                    "PAR:Dec60 Length",//6  
                                    "PAR:Dec90 Length",//7  
                                    "PAR:Dec105Length",//8  
                                    "PAR:Dec120Length",//9  
                                    "PAR:Dec150Length",//10 
                                    "PAR:Dec180Length",//11 
                                    "PAR:Dec210Length",//12 
                                    "PAR:Dec30 Pulse ",//13  
                                    "PAR:Dec45 Pulse ",//14 
                                    "PAR:Dec60 Pulse ",//15 
                                    "PAR:Dec90 Pulse ",//16 
                                    "PAR:Dec105 Pulse",//17 
                                    "PAR:Dec120 Pulse",//18 
                                    "PAR:Dec150 Pulse",//19 
                                    "PAR:Dec180 Pulse",//20 
                                    "PAR:Dec210 Pulse",//21 
                                    "PAR:Min30  Pulse",//22 
                                    "PAR:Min45  Pulse",//23 
                                    "PAR:Min60  Pulse",//24 
                                    "PAR:Min90  Pulse",//25 
                                    "PAR:Min105 Pulse",//26 
                                    "PAR:Min120 Pulse",//27 
                                    "PAR:Min150 Pulse",//28 
                                    "PAR:Min180 Pulse",//29 
                                    "PAR:Min210 Pulse",//30 
                                    "PAR:Mpm Variable",//31 
                                    "PAR:MmPerPulse  ",//32 
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////                          
                                    "NcNo1:Emergency ",//1  
                                    "NcNo1:Parking   ",//2  
                                    "NcNo1:AutoButton",//3  
                                    "NcNo1:Up Button ",//4  
                                    "NcNo1:Dn Button ",//5  
                                    "NcNo1:Open limit",//6  
                                    "NcNo1:Car Door  ",//7  
                                    "NcNo1:Hall Door ",//8  
                                    "NcNo1:Su1       ",//9  
                                    "NcNo1:Sd1       ",//10 
                                    "NcNo1:Safety sw ",//11 
                                    "NcNo1:Overload  ",//12 
                                    "NcNo1:Uls       ",//13 
                                    "NcNo1:Dls       ",//14 
                                    "NcNo1:Lu        ",//15 
                                    "NcNo1:Ld        ",//16 
                                    "NcNo1:Rg        ",//17 
                                    "NcNo1:Bat       ",//18 
                                    "NcNo1:Pass      ",//19 
                                    "NcNo1:Fire      ",//20 
                                    "NcNo1:Water     ",//21 
                                    "NcNo1:Full      ",//22 
                                    "NcNo1:Mm        ",//23 
                                    "NcNo1:Fhm       ",//24
                                    "NcNo1:Fr1       ",//25 
                                    "NcNo1:Fr2       ",//26
                                    "NcNo1:Gs2       ",//27 
                                    "NcNo1:Ds2       ",//28
                                    "NcNo1:Su2       ",//29 
                                    "NcNo1:Sd2       ",//30
                                    "NcNo1:Bm        ",//31 
                                    "NcNo1:Inv       ",//32 
///////////////////////////////////////////////////////////                                                                                                           
                                    "NcNo2:x0        ",//1  
                                    "NcNo2:x1        ",//2  
                                    "NcNo2:x2        ",//3  
                                    "NcNo2:x3        ",//4  
                                    "NcNo2:x4        ",//5  
                                    "NcNo2:x5        ",//6  
                                    "NcNo2:x6        ",//7  
                                    "NcNo2:x7        ",//8  
                                    "NcNo2:Fs0       ",//9  
                                    "NcNo2:Fs1       ",//10 
                                    "NcNo2:Fs2       ",//11 
                                    "NcNo2:Fs3       ",//12 
                                    "NcNo2:Fs4       ",//13 
                                    "NcNo2:Der       ",//14 
                                    "NcNo2:Fid       ",//15 
                                    "NcNo2:Und       ",//16 
                                    "NcNo2:nc        ",//17 
                                    "NcNo2:nc        ",//18 
                                    "NcNo2:nc        ",//19 
                                    "NcNo2:nc        ",//20 
                                    "NcNo2:nc        ",//21 
                                    "NcNo2:nc        ",//22 
                                    "NcNo2:nc        ",//23 
                                    "NcNo2:nc        ",//24
                                    "NcNo2:nc        ",//25 
                                    "NcNo2:nc        ",//26
                                    "NcNo2:nc        ",//27 
                                    "NcNo2:nc        ",//28
                                    "NcNo2:nc        ",//29 
                                    "NcNo2:nc        ",//30
                                    "NcNo2:nc        ",//31 
                                    "NcNo2:nc        ",//32 
///////////////////////////////////////////////////////////                                                                                                           
/////////////////////////////////////////////////////////// 
                                    "NcNo3:Fan       ",//9
                                    "NcNo3:Lit       ",//10 
                                    "NcNo3:Buz       ",//11
                                    "NcNo3:Bell      ",//12
                                    "NcNo3:Move      ",//13
                                    "NcNo3:Err       ",//14
                                    "NcNo3:HOp       ",//15
                                    "NcNo3:HCl       ",//16
                                    "NcNo3:Op        ",//1  
                                    "NcNo3:Cl        ",//2  
                                    "NcNo3:S_Op      ",//3  
                                    "NcNo3:S_Cl      ",//4  
                                    "NcNo3:Bk2       ",//5  
                                    "NcNo3:D_S       ",//6  
                                    "NcNo3:Gbr       ",//7  
                                    "NcNo3:Bk1       ",//8  
                                    "NcNo3:Up        ",//17 
                                    "NcNo3:Dn        ",//18 
                                    "NcNo3:P1        ",//19 
                                    "NcNo3:P2        ",//20 
                                    "NcNo3:P3        ",//21 
                                    "NcNo3:P4        ",//22 
                                    "NcNo3:Dac       ",//23 
                                    "NcNo3:nc        ",//24
                                    "NcNo3:nc        ",//25 
                                    "NcNo3:nc        ",//26
                                    "NcNo3:nc        ",//27 
                                    "NcNo3:nc        ",//28
                                    "NcNo3:nc        ",//29 
                                    "NcNo3:nc        ",//30
                                    "NcNo3:nc        ",//31 
                                    "NcNo3:nc        ",//32 
///////////////////////////////////////////////////////////                                                                                                           
                                    "INP1:Emergency  ",//1  
                                    "INP1:Parking    ",//2  
                                    "INP1:Auto Button",//3  
                                    "INP1:Up Button  ",//4  
                                    "INP1:Dn Button  ",//5  
                                    "INP1:Open limit ",//6  
                                    "INP1:Car Door   ",//7  
                                    "INP1:Hall Door  ",//8  
                                    "INP1:Su1        ",//9  
                                    "INP1:Sd1        ",//10 
                                    "INP1:Safety sw  ",//11 
                                    "INP1:Overload   ",//12 
                                    "INP1:Uls        ",//13 
                                    "INP1:Dls        ",//14 
                                    "INP1:Lu         ",//15 
                                    "INP1:Ld         ",//16 
                                    "INP1:Rg         ",//17 
                                    "INP1:Bat        ",//18 
                                    "INP1:Pass       ",//19 
                                    "INP1:Fire       ",//20 
                                    "INP1:Water      ",//21 
                                    "INP1:Full       ",//22 
                                    "INP1:Mm         ",//23 
                                    "INP1:Fhm        ",//24
                                    "INP1:Fr1        ",//25 
                                    "INP1:Fr2        ",//26
                                    "INP1:Gs2        ",//27 
                                    "INP1:Ds2        ",//28
                                    "INP1:Su2        ",//29 
                                    "INP1:Sd2        ",//30
                                    "INP1:Bm         ",//31 
                                    "INP1:Inv        ",//32 
///////////////////////////////////////////////////////////                                                                                                           
                                    "INP2:x0         ",//1  
                                    "INP2:x1         ",//2  
                                    "INP2:x2         ",//3  
                                    "INP2:x3         ",//4  
                                    "INP2:x4         ",//5  
                                    "INP2:x5         ",//6  
                                    "INP2:x6         ",//7  
                                    "INP2:x7         ",//8  
                                    "INP2:Fs0        ",//9  
                                    "INP2:Fs1        ",//10 
                                    "INP2:Fs2        ",//11 
                                    "INP2:Fs3        ",//12 
                                    "INP2:Fs4        ",//13 
                                    "INP2:Der        ",//14 
                                    "INP2:Fid        ",//15 
                                    "INP2:Und        ",//16 
                                    "INP2:nc         ",//17 
                                    "INP2:nc         ",//18 
                                    "INP2:nc         ",//19 
                                    "INP2:nc         ",//20 
                                    "INP2:nc         ",//21 
                                    "INP2:nc         ",//22 
                                    "INP2:nc         ",//23 
                                    "INP2:nc         ",//24
                                    "INP2:nc         ",//25 
                                    "INP2:nc         ",//26
                                    "INP2:nc         ",//27 
                                    "INP2:nc         ",//28
                                    "INP2:nc         ",//29 
                                    "INP2:nc         ",//30
                                    "INP2:nc         ",//31 
                                    "INP2:nc         ",//32 
///////////////////////////////////////////////////////////                                                                                                           
///////////////////////////////////////////////////////////                                                                                                           
                                    "OUTP:Fan        ",//9
                                    "OUTP:Lit        ",//10 
                                    "OUTP:Buz        ",//11
                                    "OUTP:Bell       ",//12
                                    "OUTP:Move       ",//13
                                    "OUTP:Err        ",//14
                                    "OUTP:HOp        ",//15
                                    "OUTP:HCl        ",//16
                                    "OUTP:Op         ",//1  
                                    "OUTP:Cl         ",//2  
                                    "OUTP:S_Op       ",//3  
                                    "OUTP:S_Cl       ",//4  
                                    "OUTP:Bk2        ",//5  
                                    "OUTP:D_S        ",//6  
                                    "OUTP:Gbr        ",//7  
                                    "OUTP:Bk1        ",//8  

                                    "OUTP:Up         ",//17 
                                    "OUTP:Dn         ",//18 
                                    "OUTP:P1         ",//19 
                                    "OUTP:P2         ",//20 
                                    "OUTP:P3         ",//21 
                                    "OUTP:P4         ",//22 
                                    "OUTP:Dac        ",//23 
                                    "OUTP:nc         ",//24
                                    "OUTP:nc         ",//25 
                                    "OUTP:nc         ",//26
                                    "OUTP:nc         ",//27 
                                    "OUTP:nc         ",//28
                                    "OUTP:nc         ",//29 
                                    "OUTP:nc         ",//30
                                    "OUTP:nc         ",//31 
                                    "OUTP:nc         ",//32 
///////////////////////////////////////////////////////////                                                                                                           
///////////////////////////////////////////////////////////                                                                                                           
                                    "ER:NO ERRORE(01)",//1  
                                    "ER:NO ERRORE(02)",//2  
                                    "ER:NO ERRORE(03)",//3  
                                    "ER:NO ERRORE(04)",//5  
                                    "ER:NO ERRORE(05)",//6  
                                    "ER:NO ERRORE(06)",//7  
                                    "ER:NO ERRORE(07)",//8  
                                    "ER:NO ERRORE(08)",//9  
                                    "ER:NO ERRORE(09)",//10 
                                    "ER:NO ERRORE(10)",//11 
                                    "ER:NO ERRORE(11)",//12 
                                    "ER:NO ERRORE(12)",//13 
                                    "ER:NO ERRORE(13)",//14 
                                    "ER:NO ERRORE(14)",//15 
                                    "ER:NO ERRORE(15)",//16 
                                    "ER:NO ERRORE(16)",//17 
                                    "ER:NO ERRORE(17)",//18 
                                    "ER:NO ERRORE(18)",//19 
                                    "ER:NO ERRORE(19)",//20 
                                    "ER:NO ERRORE(20)",//21 
                                    "ER:NO ERRORE(21)",//22 
                                    "ER:NO ERRORE(22)",//23 
                                    "ER:NO ERRORE(23)",//24 
                                    "ER:NO ERRORE(24)",//25 
                                    "ER:NO ERRORE(25)",//26 
                                    "ER:NO ERRORE(26)",//27 
                                    "ER:NO ERRORE(27)",//28 
                                    "ER:NO ERRORE(28)",//29 
                                    "ER:NO ERRORE(29)",//30 
                                    "ER:NO ERRORE(30)",//31 
                                    "ER:NO ERRORE(31)",//32 
                                    "ER:NO ERRORE(32)",//32 
                                };


									   
const unsigned char FhmSuccessMsg[17]="  FHM Success   "; 

//digitData == 1 
const unsigned char ElevOnOffSetMessage[ELEV_ONOFF_MESSAGE_CNT][11]={   
                                    "FHM No Good",
                                    "Chk DoorJmp",
                                    "B Phase    ", 
                                    "Call But On",   
                                    "NonStop On ",   
                                    "Op TtTm On ",   
                                    "WaitTtTm On",                                      
                                    "Cl TtTm On ",   
                                    "CarDr1  Use",   
                                    "CarDr2  Use",   
                                    "HolDr1  Use",   
                                    "HolDr2  Use",   
                                    "S_Sfty  Use",   
                                    "Mgt Mon On ",   
                                    "Encoder Use",   
                                    "Relevel On ",   
                                    "Lope  Type ",   
                                    "OneCall  On",   
                                    "M/Sus  Stop",   
                                    "Brk Mon On ",   
                                    "KidsClr On ",   
                                    "F_CarKey On",   
                                    "Single Car ",   
                                    "Op Out On  ",   
                                    "Sft Comm On",   
                                    " BCD Floor ",
                                    "Run_Op  On ",   
                                    "Reserve5   ",   
                                    "Reserve4   ",   
                                    "Reserve3   ",   
                                    "Reserve2   ",   
                                    "Manual Job ",   
                                };


//digitData == 0 
const unsigned char ElevOnOffResetMessage[ELEV_ONOFF_MESSAGE_CNT][11]={
                                    "FHM Good   ",
                                    "NoChk DrJmp",
                                    "A Phase    ", 
                                    "Cur Ward On",    
                                    "NonStop Off",   
                                    "Op TtTm Off",   
                                    "WaitTtTmOff",                                      
                                    "Cl TtTm Off",   
                                    "C_Dr1 N_Use",   
                                    "C_Dr2 N_Use",   
                                    "H_Dr1 N_Use",   
                                    "H_Dr2 N_Use",   
                                    "S_Sft N_Use",   
                                    "Mgt Mon Off",   
                                    "Encod N_Use",   
                                    "Relevel Off",   
                                    "Oil  P_Type",   
                                    "OneCall Off",   
                                    "M/SusNoStop",   
                                    "Brk Mon Off",   
                                    "KidsClr Off",   
                                    "F_CarKeyOff",   
                                    "Multi Car  ",   
                                    "Op Out Off ",   
                                    "Sft CommOff",   
                                    "DirectFloor",   
                                    "Run_Op Off ",   
                                    "Reserve5   ",   
                                    "Reserve4   ",   
                                    "Reserve3   ",   
                                    "Reserve2   ",   
                                    "Auto Ready ",   
                                };


const unsigned char IOPortMessage[IO_PORT_MESSAGE_CNT][8]={
                                    "--------",//0
                                    "------P1",//1
                                    "----P2--",//2
                                    "----P2P1",//3
                                    "--P3----",//4
                                    "--P3--P1",//5
                                    "--P3P2--",//6
                                    "--P3P2P1",//7
                                    "P4------",//8
/*
                                    "P4----P1",//9
                                    "P4--P2--",//10
                                    "P4--P2P1",//11
                                    "P4P3----",//12
                                    "P4P3--P1",//13
                                    "P4P3P2--",//14
                                    "P4P3P2P1",//15
*/
                                };


const unsigned char ElevSpeedMessage[ELEV_SPEED_MESSAGE_CNT][8]={
                                    "SPEED30 ",
                                    "SPEED45 ",
                                    "SPEED60 ", 
                                    "SPEED90 ",   
                                    "SPEED105",    
                                    "SPEED120",       
                                    "SPEED150",       
                                    "SPEED180",       
                                    "SPEED210",
                                };

const unsigned char ElevBdIdMessage[ELEV_BD_ID_MESSAGE_CNT][11]={
                                    "LG  Elevato",  //0
                                    "I/O Elevato",  //1
                                    "D_F Elevato",  //2
                                    "LG  Baggage",  //3
                                    "I/O Baggage",  //4
                                    "D_F Baggage",  //5
                                    "LG  CarLift",  //6
                                    "I/O CarLift",  //7
                                    "D_F CarLift",  //8
                                    "Reserve1   ",
                                };



const unsigned char UserLampMessage[USER_LAMP_MESSAGE_CNT][11]={
                                      "AUTO       ",                                      
                                      "INSPECTION ",                                      
                                      "OVERLOAD   ",                                      
                                      "FIRE       ",                                                                            
                                      "EMERGENCY  ",
                                      "PARKING    ",
                                      "VIP        ",
                                      "USE LAMP   ",
                                      "FULL LAMP  ",
                                      "NOT USE    "                                      
                                    };                                       


const unsigned char DriveMethodMessage[3][11]={
                                      "All Drive..",                                      
                                      "1,3,5,7... ",    //�汝�                                   
                                      "2,4,6,8... ",    //礎熱                                   
                                    };                                       

const unsigned char DoorOnOffMessage[DOOR_SEL_MESSAGE_CNT][11]={
                                      "Not Door   ",    //no door                                 
                                      "MainDoor   ",    //main door                                   
                                      "Sub Door   ",    //sub door                                   
                                      "MainSubDoor",    //main sub door                                   
                                    };                                       


const unsigned char FhmMessage[2][11]={
                                      "Fhm Stop   ",                                      
                                      "Fhm Start  ",                                       
                                    };                                       


const unsigned char PcbTypeMessage[2][11]={
                                      "Ext Bd Type",   // extbd/inbd                                    
                                      "In_Bd Type ",                                      
                                    };                                       

/*
const unsigned char ReadDataFromHost[2][11]={
                                      "Read Data ?",   // extbd/inbd                                    
                                      "Dont Read  ",                                      
                                    };
                                       
const unsigned char WriteDataToHost[2][11]={
                                      "Write Data ?",   // extbd/inbd                                    
                                      "Dont Write  ",                                      
                                    };                                       

*/

const unsigned char InitMessage[INIT_MESSAGE][11]={
                                      "Not Sel Clr",                                      
                                      "MoveCnt Clr",                                      
                                      "ErrMsg  Clr",                                      
                                      "Read Data  ",                                      
                                      "Write Data ",                                                                            
                                      "Reserve3   ",
                                      "Reserve2   ",
                                      "Reserve1   ",
                                    };                                       

const unsigned char NormalDspMessage[NORMAL_DSP_MESSAGE_CNT][11]={
                                      "Cur Status ",                                      
                                      "Mpm        ",                                      
                                      "Rpm        ",                                      
                                      "Time       ",                                                                            
                                      "Date       ",                                                                            
                                      "Date_Time  ",
                                      "Encod Pulse",                                      
                                      "EMG  Input ",  
                                      "SU1  Input ",  
                                      "GR   Input ",  
                                      "FR1  Input ",  
                                      "X0   Input ",  
                                      "FS0  Input ",
                                      "Mem  Dsp   ",     
                                      "Move Counte",
                                      "Err Counter",
                                      "Can Com Chk",
                                      "485 Com Chk",
                                      "Reserve14  ",
                                      "Reserve13  ",
                                      "Reserve12  ",
                                      "Reserve11  ",
                                      "Reserve10  ",
                                      "Reserve9   ",
                                      "Reserve8   ",
                                      "Reserve7   ",
                                      "Reserve6   ",
                                      "Reserve5   ",
                                      "Reserve4   ",
                                      "Reserve3   ",
                                      "Reserve2   ",
                                      "Reserve1   ",
                                    };                                       


const unsigned char InputPort1SelMessage[][11]={
                                      "SILK_EMG   ",                                      
                                      "SILK_PRK   ",                                      
                                      "SILK_AUTO  ",                                      
                                      "SILK_U_B   ",                                                                            
                                      "SILK_D_B   ",                                                                            
                                      "SILK_OLS   ",
                                      "SILK_GS    ",                                      
                                      "SILK_DS    ",  
                                      "SILK_SU1   ",  
                                      "SILK_SD1   ",  
                                      "SILK_SFT   ",  
                                      "SILK_OLR   ",  
                                      "SILK_ULS   ",   
                                      "SILK_DLS   ",
                                      "SILK_LU    ",
                                      "SILK_LD    ",
                                      "SILK_GR    ",
                                      "SILK_BAT   ",
                                      "SILK_PASS  ",
                                      "SILK_FIRE  ",
                                      "SILK_WATER ",
                                      "SILK_FULL  ",
                                      "SILK_MM    ",
                                      "SILK_FHM   ",
                                      "SILK_FR1   ",
                                      "SILK_FR2   ",
                                      "SILK_GS2   ",
                                      "SILK_DS2   ",
                                      "SILK_SU2   ",
                                      "SILK_SD2   ",
                                      "SILK_BM    ",
                                      "SILK_INV   ",
                                      "SILK_X0    ",                                      
                                      "SILK_X1    ",                                      
                                      "SILK_X2    ",                                      
                                      "SILK_X3    ",                                                                            
                                      "SILK_X4    ",                                                                            
                                      "SILK_X5    ",
                                      "SILK_X6    ",                                      
                                      "SILK_X7    ",  
                                      "SILK_FS0   ",  
                                      "SILK_FS1   ",  
                                      "SILK_FS2   ",  
                                      "SILK_FS3   ",  
                                      "SILK_FS4   ",   
                                      "SILK_DER   ",
                                      "SILK_FID   ",
                                      "SILK_UND   ",
                                      "EXT_X0     ",
                                      "EXT_X1     ",
                                      "EXT_X2     ",
                                      "EXT_X3     ",
                                      "Not Use    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",

/*
                                      "Not Use    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
*/
                                    };                                       


const unsigned char OutputPortSelMessage[OUTPORT_SEL_MESSAGE_CNT][11]={
                                      "SILK_FAN   ",                                      
                                      "SILK_LIGHT ",                                      
                                      "SILK_BUZ   ",                                      
                                      "SILK_BELL  ",                                                                            
                                      "SILK_RST   ",                                                                            
                                      "SILK_ERR   ",
                                      "SILK_HOp   ",                                      
                                      "SILK_HCl   ",  
                                      "SILK_OP    ",  
                                      "SILK_CL    ",  
                                      "SILK_S_OP  ",  
                                      "SILK_S_CL  ",  
                                      "SILK_BK2   ",   
                                      "SILK_D_S   ",
                                      "SILK_GBR   ",
                                      "SILK_BK1   ",
                                      "SILK_UP    ",
                                      "SILK_DN    ",
                                      "SILK_P1    ",
                                      "SILK_P2    ",
                                      "SILK_P3    ",
                                      "SILK_P4    ",
                                      "SILK_DAC   ",
                                      "Not Use    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                    };                                       



const unsigned char BdName[][8]={
                                    "M_Hib  :",                                      
                                    "S_Hib  :",                                      
                                    "Voice  :",                                      
                                    "Car    :",                                                                            
                                    "Not Sel:",                                                                            
                                 };

/*   
const unsigned char EncoderRateP[ENCODERRATE_MESSAGE_CNT][11]={
                                      "rate :x128 ",   // extbd/inbd                                    
                                      "rate :x64  ",   // extbd/inbd                                    
                                      "rate :x32  ",                                      
                                      "rate :x16  "                                      
                                 };

*/


const unsigned char InputName[6][3]={
                                      "EMG",                                      
                                      "SU1",    
                                      "RG ",   
                                      "FR1",                                      
                                      "X0 ",    
                                      "FS0",   
                                    };                                       



const unsigned char blinkx[]        ="                ";  




void  __attribute__((section(".usercode")))	PasswardCheck(void)
{
    pw[0]=cF_PASSWARD0;
    pw[1]=cF_PASSWARD1;
    pw[2]=cF_PASSWARD2;
    pw[3]=cF_PASSWARD3;

    if((pw[0]=='0') && (pw[1]=='0') && (pw[2]=='0') && (pw[3]=='0')){
    	bPasswardOk=1;
    	bPasswardUse=0;
	}
    else{
    	bPasswardOk=0;   
    	bPasswardUse=1;
	}

	bCompanyCtl=0;
}



void    __attribute__((section(".usercode"))) VirtualMoveCntReDsp(void)
{
    LocalType  value;

	if((LadderGroup == USER_GROUP) && (LadderGroupSub == VIRTUAL_CALL)){
		value = sRamDArry[mVFlrCnt];
		New485Ladder[SECONDLINE_BASE+EditBlanck+0] =(value / 100) + '0';
		value = (value % 100);          
		New485Ladder[SECONDLINE_BASE+EditBlanck+1] =(value / 10)  + '0';		          
		New485Ladder[SECONDLINE_BASE+EditBlanck+2] =(value % 10)  + '0';          
	}
}



void    __attribute__((section(".usercode"))) ChunDsp(unsigned int i)
{
    unsigned int chun,bek,sip,il;
	
	chun=i;

    il=(chun%10);

    sip=(chun/10);
    sip=(sip%10);

    bek=(chun/100);
    bek=(bek%10);

    chun=chun/1000;
    chun=(chun%10);

	New485Ladder[SECONDLINE_BASE+0] = chun + '0';                     
	New485Ladder[SECONDLINE_BASE+1] = bek  + '0';                       
	New485Ladder[SECONDLINE_BASE+2] = sip  + '0';                      
	New485Ladder[SECONDLINE_BASE+3] = '.';                             
	New485Ladder[SECONDLINE_BASE+4] = il   + '0';
}



void    __attribute__((section(".usercode"))) ManDsp(unsigned int i)
{
	unsigned int value;
    unsigned int man,chun,bek,sip,il;

	value=i;


	man=(value/10000);

    value=(value % 10000);
    chun =(value / 1000);
 
    value=(value % 1000);
    bek  =(value / 100);

    value=(value % 100);
    sip  =(value / 10);

    il   =(value % 10);


    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(man  + '0');
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(chun + '0');
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(bek  + '0');
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(sip  + '0');          
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(il   + '0');          
}


/*
void    __attribute__((section(".usercode"))) ManDsp(unsigned int i)
{
	unsigned int value;

    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/10000)    + '0';
    value=value%10000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/1000)     + '0';
    value=value%1000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(value%10)       + '0';          
}
*/


	
void    __attribute__((section(".usercode"))) RpmDsp485(void)
{
    unsigned int chun;
    unsigned long tmpcalu;



//    tmpcalu=(PulsePer100Msec * 8);
//    tmpcalu=tmpcalu * 600 * 10;
//    tmpcalu=(tmpcalu/(unsigned long)SET_ENCODER_PULSE);

    tmpcalu=(PulsePer100Msec >> 2); // 4x
    tmpcalu=tmpcalu * 600 * 10;
    tmpcalu=(tmpcalu/(unsigned long)FlashDspCharBuf[ENCODER_PULSE].long_data);


    chun=(unsigned int)tmpcalu;


	ChunDsp(chun);

/*
    il=(chun%10);

    sip=(chun/10);
    sip=(sip%10);

    bek=(chun/100);
    bek=(bek%10);

    chun=chun/1000;
    chun=(chun%10);

	New485Ladder[SECONDLINE_BASE+0] = chun + '0';                     
	New485Ladder[SECONDLINE_BASE+1] = bek  + '0';                       
	New485Ladder[SECONDLINE_BASE+2] = sip  + '0';                      
	New485Ladder[SECONDLINE_BASE+3] = '.';                             
	New485Ladder[SECONDLINE_BASE+4] = il   + '0';
*/

	New485Ladder[SECONDLINE_BASE+5] = ' ';
	New485Ladder[SECONDLINE_BASE+6] = 'R';
	New485Ladder[SECONDLINE_BASE+7] = 'p';
	New485Ladder[SECONDLINE_BASE+8] = 'm';

}



void    __attribute__((section(".usercode"))) MpmDsp485(void)
{
    unsigned int chun;

    chun=(unsigned int)CurMeterPerMin;
	ChunDsp(chun);

	New485Ladder[SECONDLINE_BASE+5] = ' ';
	New485Ladder[SECONDLINE_BASE+6] = 'm';
	New485Ladder[SECONDLINE_BASE+7] = 'p';
	New485Ladder[SECONDLINE_BASE+8] = 'm';

}


void    __attribute__((section(".usercode"))) CurEncoderPulse(void)
{
    unsigned long value;

    value=CurPulse;

///value=LevelEncoderPulse2;

////////////////encoder////
/*
    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/1000000)  + '0';
    value=value%1000000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/100000)   + '0';
    value=value%100000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/10000)    + '0';
    value=value%10000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value/1000)     + '0';
    value=value%1000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+5]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+6]=(value%10)       + '0';          

    New485Ladder[SECONDLINE_BASE+EditBlanck+7] =' ';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+8] ='p';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+9] ='u';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+10]='l';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+11]='s';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+12]='e';          
*/
////////////////encoder////


    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/10000000)  + '0';
    value=value%10000000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/1000000)   + '0';
    value=value%1000000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/100000)    + '0';
    value=value%100000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value/10000)     + '0';
    value=value%10000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(value/1000)      + '0';
    value=value%1000;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+5]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+6]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+7]=(value%10)       + '0';          

    New485Ladder[SECONDLINE_BASE+EditBlanck+8] =' ';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+9] ='p';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+10] ='u';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+11]='l';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+12]='s';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+13]='e';          

}



/*
void    __attribute__((section(".usercode"))) MoveCounterDsp(void)
{
    LocalType  value;

    value=(eDArry[eMvCounter+1] << 8) & 0xff00;
    value=((eDArry[eMvCounter]) & 0x00ff) | value;

	ManDsp(value);


    New485Ladder[SECONDLINE_BASE+EditBlanck+5] =' ';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+6] ='m';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+7] ='o';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+8] ='v';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+9] ='e';          
}
*/


void    __attribute__((section(".usercode"))) MoveCounterDsp(void)
{
    unsigned long value;


    value=MoveCounterx;

    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/1000000)  + '0';
    value=value%1000000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/100000)   + '0';
    value=value%100000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/10000)    + '0';
    value=value%10000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value/1000)     + '0';
    value=value%1000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+5]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+6]=(value%10)       + '0';          


    New485Ladder[SECONDLINE_BASE+EditBlanck+7]  =' ';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+8]  ='m';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+9]  ='o';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+10] ='v';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+11] ='e';          
}



void    __attribute__((section(".usercode"))) ErrCounterDsp(void)
{
    LocalType  value;

    value=eDArry[eErrCntPt];

	ManDsp(value);

/*
    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/10000)    + '0';
    value=value%10000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/1000)     + '0';
    value=value%1000;              
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(value%10)       + '0';          
*/

    New485Ladder[SECONDLINE_BASE+EditBlanck+5]  =' ';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+6]  ='E';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+7]  ='r';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+8]  ='r';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+9]  ='o';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+10] ='r';          
}



void    __attribute__((section(".usercode"))) Rs485ComDsp(void)
{
    New485Ladder[SECONDLINE_BASE+EditBlanck+0]='E';
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]='/';
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]='B';
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=BdName485[ErrBdNamePt][0];
    New485Ladder[SECONDLINE_BASE+EditBlanck+5]=BdName485[ErrBdNamePt][1];
    New485Ladder[SECONDLINE_BASE+EditBlanck+6]=BdName485[ErrBdNamePt][2];
}

void    __attribute__((section(".usercode"))) CanComDsp(void)
{
    LocalType  value;

    switch(sRamDArry[mCallMe]){
        case    0x01:
        case    0x02:
        case    0x03:
        case    0x04:
        case    0x05:
        case    0x06:
        case    0x07:
        case    0x08:
        case    0x09:
        case    0x0a:
        case    0x0b:
        case    0x0c:
        case    0x0d:
        case    0x0e:
        case    0x0f:
        case    0x10:
        case    0x11:
        case    0x12:
        case    0x13:
        case    0x14:
        case    0x15:
        case    0x16:
        case    0x17:
        case    0x18:
        case    0x19:
        case    0x1a:
        case    0x1b:
        case    0x1c:
        case    0x1d:
        case    0x1e:
        case    0x1f:
        case    0x20:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=BdName[0][0];
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]=BdName[0][1];
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]=BdName[0][2];
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]=BdName[0][3];
            New485Ladder[SECONDLINE_BASE+EditBlanck+4]=BdName[0][4];
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]=BdName[0][5];
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]=BdName[0][6];
            New485Ladder[SECONDLINE_BASE+EditBlanck+7]=BdName[0][7];

            New485Ladder[SECONDLINE_BASE+EditBlanck+5]= (sRamDArry[mCallMe]/10) + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]= (sRamDArry[mCallMe]%10) + '0';
            break;
        case    0x41:
        case    0x42:
        case    0x43:
        case    0x44:
        case    0x45:
        case    0x46:
        case    0x47:
        case    0x48:
        case    0x49:
        case    0x4a:
        case    0x4b:
        case    0x4c:
        case    0x4d:
        case    0x4e:
        case    0x4f:
        case    0x50:
        case    0x51:
        case    0x52:
        case    0x53:
        case    0x54:
        case    0x55:
        case    0x56:
        case    0x57:
        case    0x58:
        case    0x59:
        case    0x5a:
        case    0x5b:
        case    0x5c:
        case    0x5d:
        case    0x5e:
        case    0x5f:
        case    0x60:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=BdName[1][0];
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]=BdName[1][1];
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]=BdName[1][2];
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]=BdName[1][3];
            New485Ladder[SECONDLINE_BASE+EditBlanck+4]=BdName[1][4];
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]=BdName[1][5];
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]=BdName[1][6];
            New485Ladder[SECONDLINE_BASE+EditBlanck+7]=BdName[1][7];

            New485Ladder[SECONDLINE_BASE+EditBlanck+5]= ((sRamDArry[mCallMe]-0x40)/10) + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]= ((sRamDArry[mCallMe]-0x40)%10) + '0';
            break;
        case    0x80:
        case    0x81:
        case    0x82:
        case    0x83:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=BdName[3][0];
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]=BdName[3][1];
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]=BdName[3][2];
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]=BdName[3][3];
            New485Ladder[SECONDLINE_BASE+EditBlanck+4]=BdName[3][4];
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]=BdName[3][5];
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]=BdName[3][6];
            New485Ladder[SECONDLINE_BASE+EditBlanck+7]=BdName[3][7];

            New485Ladder[SECONDLINE_BASE+EditBlanck+3]= (sRamDArry[mCallMe] & 0x03) + '1';
            break;
        default:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=BdName[4][0];
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]=BdName[4][1];
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]=BdName[4][2];
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]=BdName[4][3];
            New485Ladder[SECONDLINE_BASE+EditBlanck+4]=BdName[4][4];
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]=BdName[4][5];
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]=BdName[4][6];
            New485Ladder[SECONDLINE_BASE+EditBlanck+7]=BdName[4][7];
            sRamDArry[mCallMe]=0x00;
            break;
    }   


    
    value=Percent;

    New485Ladder[SECONDLINE_BASE+EditBlanck+8]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+9]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+10]=(value%10)      + '0';          

    New485Ladder[SECONDLINE_BASE+EditBlanck+11]  ='%'; 


    if(LadderBuf[C_SAVE_DATA+0] == 'u'){
        TxPercent=0;
        Percent=0;
        ThisReceiveSlave=0;

        sRamDArry[mCallMe]++;
        if(sRamDArry[mCallMe] > 0x83){
            sRamDArry[mCallMe]=0x0;
        }
        else if((sRamDArry[mCallMe] >= 0x41) && (sRamDArry[mCallMe] <= 0x60)){
            if((sRamDArry[mCallMe]- 0x40) > (cF_TOPFLR+1) ){            
                sRamDArry[mCallMe]=0x80;
            }
        }
        else if((sRamDArry[mCallMe] > 0x0) && (sRamDArry[mCallMe] <= 0x20)){
            if(sRamDArry[mCallMe] > (cF_TOPFLR+1) ){            
                sRamDArry[mCallMe]=0x41;
            }
        }
    }
    if(LadderBuf[C_SAVE_DATA+0] == 'd'){
        TxPercent=0;
        Percent=0;
        ThisReceiveSlave=0;

        sRamDArry[mCallMe]--;

        if(sRamDArry[mCallMe] == 0xffff){
            sRamDArry[mCallMe]=0x83;
        }
        else if(sRamDArry[mCallMe] > 0x83){
            sRamDArry[mCallMe]=0x1;
        }
        else if(sRamDArry[mCallMe] == 0x7f){
            sRamDArry[mCallMe]=(cF_TOPFLR+1) + 0x40;
        }
        else if(sRamDArry[mCallMe] == 0x40){
            sRamDArry[mCallMe]=(cF_TOPFLR+1);
        }
        else if(sRamDArry[mCallMe] == 0x20){
            sRamDArry[mCallMe]=(cF_TOPFLR+1);
        }
    }         
}




void    __attribute__((section(".usercode"))) SetBitData(LocalType  pt)
{
    if(pt & 0x01)  New485Ladder[SECONDLINE_BASE+EditBlanck+5] = '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+5] = '0';
    if(pt & 0x02)  New485Ladder[SECONDLINE_BASE+EditBlanck+6] = '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+6] = '0';
    if(pt & 0x04)  New485Ladder[SECONDLINE_BASE+EditBlanck+7] = '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+7] = '0';
    if(pt & 0x08)  New485Ladder[SECONDLINE_BASE+EditBlanck+8] = '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+8] = '0';
    if(pt & 0x10)  New485Ladder[SECONDLINE_BASE+EditBlanck+9] = '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+9] = '0';
    if(pt & 0x20)  New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '0';
    if(pt & 0x40)  New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '0';
    if(pt & 0x80)  New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '1';
    else           New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '0';
}


void    __attribute__((section(".usercode"))) Input(LocalType  pt)
{
    LocalType  i;

    pt=pt-7;

	for(i=0;i<3;i++)	New485Ladder[SECONDLINE_BASE+EditBlanck+i]=InputName[pt][i]; 

/*
    switch(pt){
        case    0:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'E';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]= 'M';
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]= 'G';
            break;
        case    1:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'S';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]= 'U';
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]= '1';
            break;
        case    2:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'R';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]= 'G';
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]= ' ';
            break;
        case    3:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'F';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]= 'R';
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]= '1';
            break;
        case    4:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'X';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]= '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]= ' ';
            break;
        case    5:
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'F';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]= 'S';
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]= '0';
            break;

    }
*/

    New485Ladder[SECONDLINE_BASE+EditBlanck+3]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]= ' ';

	SetBitData((LocalType)sRamDArry[I_EMG+pt]);

/*
    if(sRamDArry[I_EMG+pt] & 0x01)  New485Ladder[SECONDLINE_BASE+EditBlanck+5]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+5]= '1';
    if(sRamDArry[I_EMG+pt] & 0x02)  New485Ladder[SECONDLINE_BASE+EditBlanck+6]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+6]= '1';
    if(sRamDArry[I_EMG+pt] & 0x04)  New485Ladder[SECONDLINE_BASE+EditBlanck+7]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+7]= '1';
    if(sRamDArry[I_EMG+pt] & 0x08)  New485Ladder[SECONDLINE_BASE+EditBlanck+8]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+8]= '1';
    if(sRamDArry[I_EMG+pt] & 0x10)  New485Ladder[SECONDLINE_BASE+EditBlanck+9]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+9]= '1';
    if(sRamDArry[I_EMG+pt] & 0x20)  New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '1';
    if(sRamDArry[I_EMG+pt] & 0x40)  New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '1';
    if(sRamDArry[I_EMG+pt] & 0x80)  New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '0';
    else                            New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '1';
*/

}

/*
void    __attribute__((section(".usercode"))) VirtualCall(void)
{
    LocalType  value;

    New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'M';
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]= ' ';

    value=MemPointer;

    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value%10)       + '0';          


    if(sRamDArry[MemPointer] & 0x01)  New485Ladder[SECONDLINE_BASE+EditBlanck+5] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+5] = '0';
    if(sRamDArry[MemPointer] & 0x02)  New485Ladder[SECONDLINE_BASE+EditBlanck+6] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+6] = '0';
    if(sRamDArry[MemPointer] & 0x04)  New485Ladder[SECONDLINE_BASE+EditBlanck+7] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+7] = '0';
    if(sRamDArry[MemPointer] & 0x08)  New485Ladder[SECONDLINE_BASE+EditBlanck+8] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+8] = '0';
    if(sRamDArry[MemPointer] & 0x10)  New485Ladder[SECONDLINE_BASE+EditBlanck+9] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+9] = '0';
    if(sRamDArry[MemPointer] & 0x20)  New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '0';
    if(sRamDArry[MemPointer] & 0x40)  New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '0';
    if(sRamDArry[MemPointer] & 0x80)  New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '0';
}
*/

void    __attribute__((section(".usercode"))) MemDsp(void)
{
    LocalType  value;

    New485Ladder[SECONDLINE_BASE+EditBlanck+0]= 'M';
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]= ' ';
    New485Ladder[SECONDLINE_BASE+EditBlanck+4]= ' ';

    value=MemPointer;

    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value%10)       + '0';          


	SetBitData((LocalType)sRamDArry[MemPointer]);

/*
    if(sRamDArry[MemPointer] & 0x01)  New485Ladder[SECONDLINE_BASE+EditBlanck+5] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+5] = '0';
    if(sRamDArry[MemPointer] & 0x02)  New485Ladder[SECONDLINE_BASE+EditBlanck+6] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+6] = '0';
    if(sRamDArry[MemPointer] & 0x04)  New485Ladder[SECONDLINE_BASE+EditBlanck+7] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+7] = '0';
    if(sRamDArry[MemPointer] & 0x08)  New485Ladder[SECONDLINE_BASE+EditBlanck+8] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+8] = '0';
    if(sRamDArry[MemPointer] & 0x10)  New485Ladder[SECONDLINE_BASE+EditBlanck+9] = '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+9] = '0';
    if(sRamDArry[MemPointer] & 0x20)  New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+10]= '0';
    if(sRamDArry[MemPointer] & 0x40)  New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+11]= '0';
    if(sRamDArry[MemPointer] & 0x80)  New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '1';
    else                              New485Ladder[SECONDLINE_BASE+EditBlanck+12]= '0';
*/
}


void    __attribute__((section(".usercode"))) DefaultDisplay(void)
{
    LocalType  i,j,k;

    k=cF_NormalDsp;

    if(bCarErr || bCarStopNoRun)    k=0;
    
    switch(k){
        case    0:
            j=sRamDArry[mSysStatus];
            for(i=0;i<16;i++){
                New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          
            }

			if( !FhmSuccessCheck()){
				for(i=0;i<16;i++){
					New485Ladder[SECONDLINE_BASE+i] = FhmSuccessMsg[i];          
				}
			}		

            break;
        case    1:
            MpmDsp485();
            break;
        case    2:
            RpmDsp485();
            break;
        case    3:
            New485Ladder[SECONDLINE_BASE+0] =(sRamDArry[Hour]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+1] =(sRamDArry[Hour]    &  0x0f)   + '0';          
            New485Ladder[SECONDLINE_BASE+2] ='/';          
            New485Ladder[SECONDLINE_BASE+3] =(sRamDArry[Minuate] >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+4] =(sRamDArry[Minuate] & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+5] ='/';          
            New485Ladder[SECONDLINE_BASE+6] =(sRamDArry[sec]     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+7] =(sRamDArry[sec]     & 0x0f)    + '0';          
            break;
        case    4:
            New485Ladder[SECONDLINE_BASE+0] =(sRamDArry[Year]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+1] =(sRamDArry[Year]    & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+2] ='/';          
            New485Ladder[SECONDLINE_BASE+3] =(sRamDArry[Month]   >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+4] =(sRamDArry[Month]   & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+5] ='/';          
            New485Ladder[SECONDLINE_BASE+6] =(sRamDArry[Day]     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+7] =(sRamDArry[Day]     & 0x0f)    + '0';          
            break;
        case    5:
            New485Ladder[SECONDLINE_BASE+0] =(sRamDArry[Year]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+1] =(sRamDArry[Year]    & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+2] =(sRamDArry[Month]   >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+3] =(sRamDArry[Month]   & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+4] =(sRamDArry[Day]     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+5] =(sRamDArry[Day]     & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+6] ='/';          
            New485Ladder[SECONDLINE_BASE+7] =(sRamDArry[Hour]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+8] =(sRamDArry[Hour]    &  0x0f)   + '0';          
            New485Ladder[SECONDLINE_BASE+9] =(sRamDArry[Minuate] >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+10]=(sRamDArry[Minuate] & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+11]=(sRamDArry[sec]     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+12]=(sRamDArry[sec]     & 0x0f)    + '0';          
            break;
        case    6:
            CurEncoderPulse();
            break;
        case    7:
        case    8:
        case    9:
        case    10:
        case    11:
        case    12:
            Input(cF_NormalDsp);
            break;
        case    13:
            switch(LadderKey){
                case    UPKEY:
                    MemPointer=(MemPointer+1)%1000;
                    break;
                case    DOWNKEY:
                    if(MemPointer>0)    MemPointer--;
                    else                MemPointer=999;
                    break;
            }            
            LadderKey='0';
            MemDsp();
            break;
        case    14:
            MoveCounterDsp();
            break;
        case    15:
            ErrCounterDsp();
            break;
        case    16:
            CanComDsp();
            break;
        case    17:
            Rs485ComDsp();
            break;
        default:
			j=sRamDArry[mSysStatus];
			for(i=0;i<16;i++){
				New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          
			}

			if( !FhmSuccessCheck()){
				for(i=0;i<16;i++){
					New485Ladder[SECONDLINE_BASE+i] = FhmSuccessMsg[i];          
				}
			}		
            break;
    }

	if(k != 16)	sRamDArry[mCallMe]=0x0;

}


void  __attribute__((section(".usercode"))) CalendarChk(void)
{
    if(LadderGroupSub==30){
        switch(Cursor){
            case    0:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '2'){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                }
                else if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] == '2'){
                    if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor+1] > '4'){
                        New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor+1]='0';          
                    }
                }
                break;
            case    1:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor-1] == '2'){
                    if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '4'){
                        New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                    }
                }
                break;
            case    3:
            case    6:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '5')    New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                break;
        }
    }
    else if(LadderGroupSub==31){
        switch(Cursor){
            case    3:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '1')    New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                else if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] == '1'){
                    if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor+1] > '2'){
                        New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor+1]='0';          
                    }
                }
                break;
            case    4:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor-1] == '1'){
                    if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '2'){
                        New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                    }
                }
                break;
            case    6:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '3')    New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                else if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] == '3'){
                    if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor+1] > '1'){
                        New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor+1]='0';          
                    }
                }
                break;
            case    7:
                if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor-1] == '3'){
                    if(New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor] > '1'){
                        New485Ladder[SECONDLINE_BASE+EditBlanck+Cursor]='0';          
                    }
                }
                break;
        }
    }
}




void  __attribute__((section(".usercode"))) GetFlashDataToBufRam(unsigned int BytePt)
{
    LocalType  i,j;

    j=((BytePt/64) * 16);

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[j+i].long_data;
    }
}


/////////
void  __attribute__((section(".usercode"))) DspCharSave(unsigned int pt,unsigned int DtNm)
{
    LocalType  i,j,k;

    k=(pt % 64);

    j=((pt/64) * 16);

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[j+i].long_data;
    }

    for(i=0;i<DtNm;i++){
        b_LdTmpBufRam((unsigned long)(pt+i))     = New485Ladder[SECONDLINE_BASE+EditBlanck+i];
    }
    
    k = New485Ladder[SECONDLINE_BASE+EditBlanck+1];

    
    if(pt==0){ 
        if(b_LdTmpBufRam(0) == 'B'){             
            if(k == '7')        i=0;  
            else if(k == '6')   i=2;  
            else if(k == '5')   i=4;  
            else if(k == '4')   i=6;  
            else if(k == '3')   i=8;  
            else if(k == '2')   i=10;  
            else if(k == '1')   i=12;
            else                pt=1;  
        }
        else if(b_LdTmpBufRam(0) == '0'){ 
            if(k == '1')        i=14;
            else                pt=1;  
        }
        else                    pt=1;
        
        if(pt==0){
            for(k=0;k<64;k++,i++){
                b_LdTmpBufRam(k)  = DftFlrName[i];
            }
        }
    }

    flash_write_DspChar(pt);
}

/////////

void  __attribute__((section(".usercode"))) NewMenuStart(void)
{
    EnterKey=0;
    Cursor=0;
    ShiftCnt=0;
    EditStatus=0;
    EditBlanck=0;
    
    switch(LadderGroup){
        case    FLR_DSP_GROUP:    
            MaxSubMenu=FLR_DSP_GROUP_MAX;
            break;
        case    FLR_GROUP:
            MaxSubMenu=FLR_GROUP_MAX;
            break;
        case    TIMER_GROUP:
            MaxSubMenu=TIMER_GROUP_MAX;
            break;
        case    SUB_DOOR_GROUP:
            MaxSubMenu=ONOFF1_GROUP_MAX;
            break;
        case    ONOFF1_GROUP:
            MaxSubMenu=ONOFF1_GROUP_MAX;
            break;
        case    ONOFF2_GROUP: 
            MaxSubMenu=ONOFF2_GROUP_MAX;
            break;
        case    NCNO1_GROUP:
            MaxSubMenu=NCNO1_GROUP_MAX;
            break;
        case    NCNO2_GROUP:
            MaxSubMenu=NCNO2_GROUP_MAX;
            break;
        case    NCNO3_GROUP:
            MaxSubMenu=NCNO3_GROUP_MAX;
            break;
        case    IO_GROUP: 
            MaxSubMenu=IO_GROUP_MAX;
            break;
        case    USER_GROUP:    //save
            MaxSubMenu=USER_GROUP_MAX;
            break;
        case    OPEN_WAIT_GROUP:
            MaxSubMenu=OPEN_WAIT_GROUP_MAX;
            break;
        case    PARAMETER_GROUP:
            MaxSubMenu=PARAMETER_GROUP_MAX;
            break;
        case    INPORT1_GROUP:
            MaxSubMenu=INPORT1_GROUP_MAX;
            break;
        case    INPORT2_GROUP:
            MaxSubMenu=INPORT2_GROUP_MAX;
            break;
        case    OUTPORT_GROUP:
            MaxSubMenu=OUTPORT_GROUP_MAX;
            break;            
        case    ERROR_GROUP:
            MaxSubMenu=ERROR_GROUP_MAX;
            break;
    }
}




void  __attribute__((section(".usercode"))) DigitStringMessage(void)
{
    LocalType i;

    switch(LadderGroup){
/*
        case    FLR_GROUP:
            if((LadderGroupSub == 2) || (LadderGroupSub == 4) || (LadderGroupSub == 5) || (LadderGroupSub == 6)){
                if(DigitData > 32){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+0]='N';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+1]='o';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+2]='t';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=' ';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+4]='U';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+5]='s';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+6]='e';          
                }
                else{
                    New485Ladder[SECONDLINE_BASE+EditBlanck+2]=' ';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+3]=' ';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+4]=' ';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+5]=' ';          
                    New485Ladder[SECONDLINE_BASE+EditBlanck+6]=' ';          
                }
            }
            else{
                New485Ladder[SECONDLINE_BASE+EditBlanck+2]=' ';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+3]=' ';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+4]=' ';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+5]=' ';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+6]=' ';          
            }
            break;
*/
        case    TIMER_GROUP:
//            if((LadderGroupSub == 2) || (LadderGroupSub == 6)){
            if(LadderGroupSub == 6){
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+0]='M';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+1]='i';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+2]='n';          
            }
            else if((LadderGroupSub >= 13) && (LadderGroupSub <= 24)){
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+0]='H';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+1]='s';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+2]='e';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+3]='c';          
            }

/*
            else if((LadderGroupSub >= 13) && (LadderGroupSub <= 17)){
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+0]='H';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+1]='s';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+2]='e';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+3]='c';          
            }
            else if((LadderGroupSub > 12) && (LadderGroupSub <= 21)){
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+0]='m';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+1]='s';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+2]='e';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+3]='c';          
            }
*/

//            else if((LadderGroupSub == 7) || (LadderGroupSub == 9) || (LadderGroupSub == 10) || (LadderGroupSub == 12)){
            else if((LadderGroupSub == 9) || (LadderGroupSub == 10)){
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+0]='H';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+1]='s';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+2]='e';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+3]='c';          
            }
            else{
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+0]='S';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+1]='e';          
                New485Ladder[SECONDLINE_BASE+EditBlanck+ShiftCnt+2]='c';          
            }
            break;
        case    SUB_DOOR_GROUP:
			for(i=0;i<11;i++){
            	New485Ladder[SECONDLINE_BASE+EditBlanck+i]=DoorOnOffMessage[DigitData][i];
			}					
            break;
        case    ONOFF1_GROUP:
            if(DigitData){
                New485Ladder[SECONDLINE_BASE+EditBlanck+0]='S';
                New485Ladder[SECONDLINE_BASE+EditBlanck+1]='e';
                New485Ladder[SECONDLINE_BASE+EditBlanck+2]='r';
                New485Ladder[SECONDLINE_BASE+EditBlanck+3]='v';
                New485Ladder[SECONDLINE_BASE+EditBlanck+4]='i';
                New485Ladder[SECONDLINE_BASE+EditBlanck+5]='c';
                New485Ladder[SECONDLINE_BASE+EditBlanck+6]='e';
                New485Ladder[SECONDLINE_BASE+EditBlanck+7]=' ';
                New485Ladder[SECONDLINE_BASE+EditBlanck+8]=' ';
                New485Ladder[SECONDLINE_BASE+EditBlanck+9]=' ';
            }
            else{
                New485Ladder[SECONDLINE_BASE+EditBlanck+0]='N';
                New485Ladder[SECONDLINE_BASE+EditBlanck+1]='o';
                New485Ladder[SECONDLINE_BASE+EditBlanck+2]=' ';
                New485Ladder[SECONDLINE_BASE+EditBlanck+3]='S';
                New485Ladder[SECONDLINE_BASE+EditBlanck+4]='e';
                New485Ladder[SECONDLINE_BASE+EditBlanck+5]='r';
                New485Ladder[SECONDLINE_BASE+EditBlanck+6]='v';
                New485Ladder[SECONDLINE_BASE+EditBlanck+7]='i';
                New485Ladder[SECONDLINE_BASE+EditBlanck+8]='c';
                New485Ladder[SECONDLINE_BASE+EditBlanck+9]='e';
            }
            break;
        case    ONOFF2_GROUP:
            if(DigitData){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=ElevOnOffSetMessage[LadderGroupSub][i];
                }
            }
            else{               
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=ElevOnOffResetMessage[LadderGroupSub][i];
                }
            }
            break;
        case    NCNO1_GROUP:
        case    NCNO2_GROUP:
        case    NCNO3_GROUP:			
            if(DigitData){
                New485Ladder[SECONDLINE_BASE+EditBlanck+0]='N';
                New485Ladder[SECONDLINE_BASE+EditBlanck+1]='-';
                New485Ladder[SECONDLINE_BASE+EditBlanck+2]='O';
                New485Ladder[SECONDLINE_BASE+EditBlanck+3]='p';
                New485Ladder[SECONDLINE_BASE+EditBlanck+4]='e';
                New485Ladder[SECONDLINE_BASE+EditBlanck+5]='n';
                New485Ladder[SECONDLINE_BASE+EditBlanck+6]=' ';
            }
            else{               
                New485Ladder[SECONDLINE_BASE+EditBlanck+0]='N';
                New485Ladder[SECONDLINE_BASE+EditBlanck+1]='-';
                New485Ladder[SECONDLINE_BASE+EditBlanck+2]='C';
                New485Ladder[SECONDLINE_BASE+EditBlanck+3]='l';
                New485Ladder[SECONDLINE_BASE+EditBlanck+4]='o';
                New485Ladder[SECONDLINE_BASE+EditBlanck+5]='s';
                New485Ladder[SECONDLINE_BASE+EditBlanck+6]='e';
            }

            break;
        case    IO_GROUP:
            if(LadderGroupSub <= 14){
                for(i=0;i<8;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=IOPortMessage[DigitData][i];
                }
            }
            else if(LadderGroupSub <= 16){               
                for(i=0;i<8;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=ElevSpeedMessage[DigitData][i];
                }
            }
            break;
        case    USER_GROUP:  //save
			switch(LadderGroupSub){
				case	BOARD_ID:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=ElevBdIdMessage[DigitData][i];
	                }
					break;
				case	USER_LAMP1:
				case	USER_LAMP2:
				case	USER_LAMP3:
				case	USER_LAMP4:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=UserLampMessage[DigitData][i];
	                }
					break;
/*
				case	USER_LAMP2:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=UserLampMessage[DigitData][i];
	                }
					break;
*/
				case	NORMAL_DSP:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=NormalDspMessage[DigitData][i];
	                }
	                i=1;
	                i=0;
					break;
				case	DRIVE_METHOD:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=DriveMethodMessage[DigitData][i];
	                }
					break;
				case	FHM_RUN_CHK:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=FhmMessage[DigitData][i];
	                }
					break;
				case	INIT_DATA:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=InitMessage[DigitData][i];
	                }
					break;
				case	LG_INV_IN_BD:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=PcbTypeMessage[DigitData][i];
	                }
					break;
/*
				case	ENCODER_RATE:
	                for(i=0;i<11;i++){
	                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=EncoderRateP[DigitData][i];
	                }
*/
					break;
			}

/*
            if(LadderGroupSub == BOARD_ID){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=ElevBdIdMessage[DigitData][i];
                }
            }            
            else if(LadderGroupSub == USER_LAMP1){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=UserLampMessage[DigitData][i];
                }
            }            
            else if(LadderGroupSub == USER_LAMP2){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=UserLampMessage[DigitData][i];
                }
            }            
            else if(LadderGroupSub == NORMAL_DSP){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=NormalDspMessage[DigitData][i];
                }
                i=1;
                i=0;
            }            
            else if(LadderGroupSub == DRIVE_METHOD){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=DriveMethodMessage[DigitData][i];
                }
            }            
            else if(LadderGroupSub == FHM_RUN_CHK){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=FhmMessage[DigitData][i];
                }
            }            
            else if(LadderGroupSub == INIT_DATA){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=InitMessage[DigitData][i];
                }
            }            
            else if(LadderGroupSub == LG_INV_IN_BD){
                for(i=0;i<11;i++){
                    New485Ladder[SECONDLINE_BASE+EditBlanck+i]=PcbTypeMessage[DigitData][i];
                }
            }            
*/
            break;

        case    INPORT1_GROUP:
            for(i=0;i<11;i++){
                New485Ladder[SECONDLINE_BASE+EditBlanck+i]=InputPort1SelMessage[DigitData][i];
            }
            break;
        case    INPORT2_GROUP:
            for(i=0;i<11;i++){
                New485Ladder[SECONDLINE_BASE+EditBlanck+i]=InputPort1SelMessage[DigitData][i];
            }
            break;
        case    OUTPORT_GROUP:
            for(i=0;i<11;i++){
                New485Ladder[SECONDLINE_BASE+EditBlanck+i]=OutputPortSelMessage[DigitData][i];
            }
            break;

        default:
            break;

    }    
}



void  __attribute__((section(".usercode"))) Integer_Digit(void)
{
    unsigned int i;
    unsigned int value;

    if(LadderKey==UPKEY){
        if(DigitData > DigitMaxValue)   DigitData=DigitMinValue;
    }
    else if(LadderKey==DOWNKEY){
        if(DigitData < DigitMinValue)   DigitData=DigitMaxValue;
    }
    else{
        if(DigitData > DigitMaxValue)   DigitData=DigitMinValue;
        if(DigitData < DigitMinValue)   DigitData=DigitMaxValue;
    }

    value=DigitData;


    if(ShiftCnt == 1){
        New485Ladder[SECONDLINE_BASE+EditBlanck+0]=value            + '0';          
    }
    else if(ShiftCnt == 2){
        New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/10)       + '0';          
        New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value%10)       + '0';          
    }
    else if(ShiftCnt == 3){
        New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/100)      + '0';
        value=value%100;              
        New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/10)       + '0';          
        New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value%10)       + '0';          
    }
    else if(ShiftCnt == 4){
        New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/1000)     + '0';
        value=value%1000;              
        New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/100)      + '0';
        value=value%100;                        
        New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/10)       + '0';          
        New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value%10)       + '0';          
    }
    else if(ShiftCnt == 5){
        New485Ladder[SECONDLINE_BASE+EditBlanck+0]=(value/10000)    + '0';
        value=value%10000;              
        New485Ladder[SECONDLINE_BASE+EditBlanck+1]=(value/1000)     + '0';
        value=value%1000;              
        New485Ladder[SECONDLINE_BASE+EditBlanck+2]=(value/100)      + '0';
        value=value%100;                        
        New485Ladder[SECONDLINE_BASE+EditBlanck+3]=(value/10)       + '0';          
        New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(value%10)       + '0';          
    }

    DigitStringMessage();
}





/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


void  __attribute__((section(".usercode"))) FlrDspGroup(LocalType offset)
{
    LocalType i;

    i=(offset *2 );

    Cursor=0;
    ShiftCnt=2;
    EditBlanck=7;
    EditStatus=DIGIT_ALPHAR_EDIT;

    New485Ladder[SECONDLINE_BASE+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i+0));  
    New485Ladder[SECONDLINE_BASE+EditBlanck+1]=cF_FLRDSPCH((unsigned long)(i+1));          
}


void  __attribute__((section(".usercode"))) FlrDspGroupSave(LocalType offset)
{
    DspCharSave((offset*2),ShiftCnt);

#ifdef	L_K_J
	PowerOnTime=0x0;
#endif

}





void  __attribute__((section(".usercode"))) FlrGroup(void)
{
    LocalType i;

    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditBlanck=7;
    EditStatus=DIGIT_EDIT;

    DigitMaxValue=cF_TOPFLR+1;
    DigitMinValue=1;

    switch(LadderGroupSub){  
        case    TOP_FLR:      
        case    NO_USE_GO_FLR:
//        case    ONE_STOP_FLR:
		case	KIDS_KEY_CNT:
		case	X7_SAFE_FLR:
		case	X6_SAFE_FLR:
		case	X5_SAFE_FLR:

//        case    SUB_DOOR1_FLR:
//        case    SUB_DOOR2_FLR:
//        case    SUB_DOOR3_FLR:
//        case    SUB_DOOR4_FLR:
            DigitMaxValue=33;
            break;
        case    ONE_STOP_FLR:
		    ShiftCnt=3;
		    EditBlanck=6;
    		DigitMinValue=0;
            DigitMaxValue=256;
			break;
    }
    DigitData=cF_FLRDSPCH((unsigned long)i);
    DigitData=DigitData+1;
    Integer_Digit();    
}


void  __attribute__((section(".usercode"))) FlrGroupSave(void)
{
    LocalType i;

    DigitData=DigitData-1;

    i=(LadderGroupSub + GroupBaseAddr);
    GetFlashDataToBufRam(F_BLOCK1);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK1);

/*
	if(LadderGroupSub == 0 ){
		OnOffFlrResetting();
	}
*/

}



void  __attribute__((section(".usercode"))) WaitFlrConvStr(LocalType	i)
{
	New485Ladder[SECONDLINE_BASE+EditBlanck+ (i+0)] =(DigitData / 10)  	+ '0';          
	New485Ladder[SECONDLINE_BASE+EditBlanck+ (i+1)] =(DigitData % 10)  	+ '0';          
}


void  __attribute__((section(".usercode"))) WaitFlrGroup(void)
{
    LocalType i;
    
    i=((LadderGroupSub * 5) + GroupBaseAddr);

	Cursor=0;
	ShiftCnt=12;
	EditBlanck=4;
	EditStatus=CLOCK_EDIT;

	if(LadderGroupSub <= 3){
		DigitData=cF_FLRDSPCH((unsigned long)i);
		WaitFlrConvStr(0);

//		New485Ladder[SECONDLINE_BASE+EditBlanck+0] =(DigitData / 10)  	+ '0';          
//		New485Ladder[SECONDLINE_BASE+EditBlanck+1] =(DigitData % 10)  	+ '0';          
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+1));
		WaitFlrConvStr(2);
//		New485Ladder[SECONDLINE_BASE+EditBlanck+2] =(DigitData / 10)    + '0';          
//		New485Ladder[SECONDLINE_BASE+EditBlanck+3] =(DigitData % 10)    + '0';          
		New485Ladder[SECONDLINE_BASE+EditBlanck+4] ='-';          
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+2));
		WaitFlrConvStr(5);
//		New485Ladder[SECONDLINE_BASE+EditBlanck+5] =(DigitData / 10)	+ '0';          
//		New485Ladder[SECONDLINE_BASE+EditBlanck+6] =(DigitData % 10)    + '0';          
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+3));
		WaitFlrConvStr(7);
//		New485Ladder[SECONDLINE_BASE+EditBlanck+7]=(DigitData / 10)		+ '0';          
//		New485Ladder[SECONDLINE_BASE+EditBlanck+8]=(DigitData % 10)    	+ '0';          
		New485Ladder[SECONDLINE_BASE+EditBlanck+9]='-';          
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+4));
		DigitData=(DigitData + 1);
		New485Ladder[SECONDLINE_BASE+EditBlanck+10]=(DigitData / 10)	+ '0';          
		New485Ladder[SECONDLINE_BASE+EditBlanck+11]=(DigitData % 10)    + '0';          
	}
}



void  __attribute__((section(".usercode"))) WaitFlrConv(LocalType	i)
{
	DigitData=New485Ladder[SECONDLINE_BASE+EditBlanck + i ]-'0';
    DigitData=(DigitData * 10);      
	DigitData=((New485Ladder[SECONDLINE_BASE+EditBlanck + (i+1)] -'0') + DigitData);          
}


void  __attribute__((section(".usercode"))) WaitFlrGroupSave(void)
{
    LocalType i;

	if(LadderGroupSub <= 3){

	    i=(LadderGroupSub * 5);
	    GetFlashDataToBufRam(F_BLOCK3);

		WaitFlrConv(0);
	
//		DigitData=New485Ladder[SECONDLINE_BASE+EditBlanck+0]-'0';
//	    DigitData=(DigitData * 10);      
//		DigitData=((New485Ladder[SECONDLINE_BASE+EditBlanck+1] -'0') + DigitData);          

	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);

	
		i++;
		WaitFlrConv(2);

//		DigitData=New485Ladder[SECONDLINE_BASE+EditBlanck+2]-'0';
//	    DigitData=(DigitData * 10);      
//		DigitData=((New485Ladder[SECONDLINE_BASE+EditBlanck+3] -'0') + DigitData);          
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);
	
		i++;
		WaitFlrConv(5);
//		DigitData=New485Ladder[SECONDLINE_BASE+EditBlanck+5]-'0';
//	    DigitData=(DigitData * 10);      
//		DigitData=((New485Ladder[SECONDLINE_BASE+EditBlanck+6] -'0') + DigitData);          
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);
	
		i++;
		WaitFlrConv(7);
//		DigitData=New485Ladder[SECONDLINE_BASE+EditBlanck+7]-'0';
//	    DigitData=(DigitData * 10);      
//		DigitData=((New485Ladder[SECONDLINE_BASE+EditBlanck+8] -'0') + DigitData);          
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);
	
		i++;
		WaitFlrConv(10);
//		DigitData=New485Ladder[SECONDLINE_BASE+EditBlanck+10]-'0';
//	    DigitData=(DigitData * 10);      
//		DigitData=((New485Ladder[SECONDLINE_BASE+EditBlanck+11] -'0') + DigitData);          
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData-1);

		flash_write_DspChar(F_BLOCK3);
	}
}


/*
void  __attribute__((section(".usercode"))) WaitFlrGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditBlanck=7;
    EditStatus=DIGIT_EDIT;

    if(LadderGroupSub >= 30){            
        DigitMaxValue=23;
        DigitMinValue=0;
        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();    
    }
    else{
        DigitMaxValue=33;
        DigitMinValue=1;
        DigitData=cF_FLRDSPCH((unsigned long)i);
        DigitData=DigitData+1;
        Integer_Digit();    
    }
}



void  __attribute__((section(".usercode"))) WaitFlrGroupSave(void)
{
    LocalType i;

    if(LadderGroupSub < 30) DigitData=DigitData-1;

    i=(LadderGroupSub + GroupBaseAddr);

    GetFlashDataToBufRam(F_BLOCK3);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK3);
}

*/



void  __attribute__((section(".usercode"))) TimerGroup(void)
{
    LocalType i;


    switch(LadderGroupSub){        
        case    23:
        case    24:
            Cursor=0;
            ShiftCnt=2;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMinValue=0;
            DigitMaxValue=81;
            i=(LadderGroupSub + F_OpWtTm);
			DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;

        case    18:
        case    19:
        case    20:
        case    21:
        case    22:

//            Cursor=0;
//            ShiftCnt=5;
//            EditBlanck=5;
//            EditStatus=DIGIT_EDIT;
//            DigitMinValue=0;
//            DigitMaxValue=65535;
//            DigitData=iF_FLRDSPCH(F_BrkStTm10);

            Cursor=0;
            ShiftCnt=3;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMinValue=0;
            DigitMaxValue=254;
            i=(LadderGroupSub + F_OpWtTm);
			DigitData=cF_FLRDSPCH((unsigned long)i);

            Integer_Digit();
            break;
/*
        case    19:
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;
            DigitData=iF_FLRDSPCH(F_BrkStTm20);
            Integer_Digit();
            break;
        case    20:
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            DigitData=iF_FLRDSPCH(F_BrkStTm30);
            Integer_Digit();
            break;
        case    21:
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            DigitData=iF_FLRDSPCH(F_BrkStTm40);
            Integer_Digit();
            break;
        case    22:
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            DigitData=iF_FLRDSPCH(F_BrkStTm50);
            Integer_Digit();
            break;
*/

        case    0:
        case    1:
		case	2:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=3;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=254;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
			break;
        case    3:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            EditBlanck=6;
            EditStatus=DIGIT_EDIT;
//            ShiftCnt=2;
//            DigitMaxValue=95;
            ShiftCnt=3;
            DigitMaxValue=200;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
//        case    2:
        case    5:
        case    6:
        case    4:
        case    8:
        case    9:
        case   10:
//        case   12:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=2;
            EditBlanck=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=99;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
//        case    4:
        case    7:
        case    11:
        case    12:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=2;
            EditBlanck=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=20;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
        default:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=3;
            EditBlanck=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=250;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
    }    
}


void  __attribute__((section(".usercode"))) TimerGroupSave(void)
{
    LocalType i;

    i=(LadderGroupSub + F_OpWtTm);

    GetFlashDataToBufRam(F_BLOCK1);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK1);


/*
    LocalType i,j;

    j=0;

    switch(LadderGroupSub){        
        case    18:
            i=F_BrkStTm10;
            j=1;
            break;
        case    19:
            i=F_BrkStTm20;
            j=1;
            break;
        case    20:
            i=F_BrkStTm30;
            j=1;
            break;
        case    21:
            i=F_BrkStTm40;
            j=1;
            break;
        case    22:
            i=F_BrkStTm50;
            j=1;
            break;
        default:
            i=(LadderGroupSub + F_OpWtTm);
            j=2;
            break;
    }    

    if(j>0){
        GetFlashDataToBufRam(F_BLOCK1);
        if(j==1){
            i_LdTmpBufRam(i)=(LocalType)(DigitData);
        }
        else if(j==2){
            b_LdTmpBufRam(i)=(LocalType)(DigitData);
        }
        flash_write_DspChar(F_BLOCK1);
    }
*/
}



void  __attribute__((section(".usercode"))) OnOffGroup(void)
{
    LocalType i,j,BitValue;

    i=((LadderGroupSub/8) + GroupBaseAddr);
    j=(LadderGroupSub%8);
    BitValue=(0x01 << j);

    Cursor=0;
    ShiftCnt=0;
    EditBlanck=4;
    EditStatus=DIGIT_STRING_EDIT;                   
    DigitMaxValue=2;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData &  BitValue)   DigitData=1;     
    else                        DigitData=0;     

    if((LadderGroup == ONOFF2_GROUP)  && (LadderGroupSub == FHM_CHK)) EditStatus=NO_EDIT;                   

    Integer_Digit();
}




void  __attribute__((section(".usercode"))) OnOffGroupSave(void)
{
    LocalType i,j;


    i=((LadderGroupSub/8) + GroupBaseAddr);
    j=(LadderGroupSub%8);

    GetFlashDataToBufRam(F_BLOCK1);

    if(DigitData){
        bit_LdTmpBufRamSet(i,j);
    }
    else{
        bit_LdTmpBufRamReset(i,j);
    }
    flash_write_DspChar(F_BLOCK1);

}


void  __attribute__((section(".usercode"))) NcNoGroup(void)
{
    LocalType i,j,BitValue;

    i=(LadderGroupSub + GroupBaseAddr);

//    j=(offset%8);
//    BitValue=(0x01 << j);

    Cursor=0;
    ShiftCnt=0;
    EditBlanck=4;
    EditStatus=DIGIT_STRING_EDIT;                   
    DigitMaxValue=2;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData &  0x80)       DigitData=1;     
    else                        DigitData=0;     

    Integer_Digit();
}


void  __attribute__((section(".usercode"))) InNcNoGroupSave(void)
{
    LocalType i,j;


    i=(LadderGroupSub + GroupBaseAddr);

    GetFlashDataToBufRam(F_BLOCK4);

    if(DigitData){
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) | 0x80);
    }
    else{
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) & 0x7f);
    }
    flash_write_DspChar(F_BLOCK4);

}


void  __attribute__((section(".usercode"))) OutNcNoGroupSave(void)
{
    LocalType i,j;

    i=(LadderGroupSub + GroupBaseAddr);

    GetFlashDataToBufRam(F_BLOCK5);

    if(DigitData){
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) | 0x80);
    }
    else{
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) & 0x7f);
    }
    flash_write_DspChar(F_BLOCK5);

}


void  __attribute__((section(".usercode"))) IoGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=3;
    EditBlanck=5;
    EditStatus=DIGIT_EDIT;

    DigitMinValue=0;

    if(LadderGroupSub <= 14){
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;    

        if(INVERTER_CHECK == IO)      DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
        else                          DigitMaxValue=IO_PORT_MESSAGE_CNT;
//kkk        if(cF_BD_ID == IO_INVERTER) DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
//kkk        else                        DigitMaxValue=IO_PORT_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
    else if(LadderGroupSub <= 16){               
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;                   

        if(INVERTER_CHECK == IO)        DigitMaxValue=ELEV_SPEED_MESSAGE_CNT;
        else                            DigitMaxValue=ELEV_SPEED_MESSAGE_CNT;

//        if(INVERTER_CHECK == IO)        DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
//        else                            DigitMaxValue=IO_PORT_MESSAGE_CNT;

//kkk        if(cF_BD_ID == IO_INVERTER) DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
//kkk        else                        DigitMaxValue=IO_PORT_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
    else{               
        ShiftCnt=3;
        EditBlanck=7;
        DigitMaxValue=220;
        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
}


void  __attribute__((section(".usercode"))) IoGroupSave(void)
{
    LocalType i;

    i=(LadderGroupSub + GroupBaseAddr);

    if(i==16){
        switch(DigitData){
            case    SPEED_30:
                if(cF_SPEED30 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_45:
                if(cF_SPEED45 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_60:
                if(cF_SPEED60 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_90:
                if(cF_SPEED90 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_105:
                if(cF_SPEED105 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_120:
                if(cF_SPEED120 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_150:
                if(cF_SPEED150 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_180:
                if(cF_SPEED180 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_210:
                if(cF_SPEED210 == 0)    DigitData=SPEED_210;     
                break;
            default:
                DigitData=SPEED_210;     
                break;
        }
    }
    
    GetFlashDataToBufRam(F_BLOCK2);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK2);
}





void  __attribute__((section(".usercode"))) DoorGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=0;
    EditBlanck=5;
    EditStatus=DIGIT_STRING_EDIT;
    DigitMinValue=0;
	DigitMaxValue=DOOR_SEL_MESSAGE_CNT;

    DigitData=MainSubDoorFlrChk(LadderGroupSub);

    Integer_Digit();


/*

    if(LadderGroupSub <= 14){
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;    

        if(INVERTER_CHECK == IO)      DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
        else                          DigitMaxValue=IO_PORT_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
    else if(LadderGroupSub <= 16){               
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;                   

        if(INVERTER_CHECK == IO)        DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
        else                            DigitMaxValue=IO_PORT_MESSAGE_CNT;

//kkk        if(cF_BD_ID == IO_INVERTER) DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
//kkk        else                        DigitMaxValue=IO_PORT_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
    else{               
        ShiftCnt=3;
        EditBlanck=7;
        DigitMaxValue=200;
        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
*/

}


void  __attribute__((section(".usercode"))) DoorGroupSave(void)
{
    LocalType i,j,k;

////
	i=0x0;
    k=0x0;

	if(LadderGroupSub > 0){
	    i=LadderGroupSub/4;
	    k=LadderGroupSub%4;
	}

    j=0;

    switch(i){
        case    0:
            j=cF_SUBDOORFLR1;
            break;
        case    1:
            j=cF_SUBDOORFLR2;
            break;
        case    2:
            j=cF_SUBDOORFLR3;
            break;
        case    3:        
            j=cF_SUBDOORFLR4;
            break;
        case    4:
            j=cF_SUBDOORFLR5;
            break;
        case    5:
            j=cF_SUBDOORFLR6;
            break;
        case    6:
            j=cF_SUBDOORFLR7;
            break;
        case    7:        
            j=cF_SUBDOORFLR8;
            break;
    }

    switch(k){
        case    0:
            j=(j & 0xfc);
            break;
        case    1:
            j=(j & 0xf3);
			DigitData=(DigitData << 2); 
            break;
        case    2:
            j=(j & 0xcf);
			DigitData=(DigitData << 4); 
            break;
        case    3:        
            j=(j & 0x3f);
			DigitData=(DigitData << 6); 
            break;
    }
	DigitData=(DigitData | j);
	    
//////
	k=(LadderGroupSub/4);
    i=(k + GroupBaseAddr);

    GetFlashDataToBufRam(F_BLOCK4);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK4);

/*
    GetFlashDataToBufRam(F_BLOCK1);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK1);
*/
}


void  __attribute__((section(".usercode"))) UserGroup(void)
{
    LocalType i,j;

    switch(LadderGroupSub){
        case    VERSION:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=NO_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;

            i=F_Ver0;
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]='.';      
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]=cF_FLRDSPCH((unsigned long)(i+2));   


/*
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]='.';      
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]=cF_FLRDSPCH((unsigned long)(i+2));      
*/
            break;
        case    BOARD_ID:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=ELEV_BD_ID_MESSAGE_CNT;
            DigitMinValue=0;
            i=F_Bd_Id;
            DigitData=cF_FLRDSPCH((unsigned long)i);

            switch(DigitData){
                case    0x0:
                case    0x1:
                case    0x2:
                    break;
                case    0x4:
                    DigitData=3;    
                    break;
                case    0x5:
                    DigitData=4;    
                    break;
                case    0x6:
                    DigitData=5;    
                    break;
                case    0x8:
                    DigitData=6;    
                    break;
                case    0x9:
                    DigitData=7;    
                    break;
                case    0xa:
                    DigitData=8;    
                    break;
            }

            Integer_Digit();
            break;
        case    PASSWARD:
            Cursor=0;
            ShiftCnt=4;
            EditBlanck=5;
            EditStatus=DIGIT_ALPHAR_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]='*';  
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]='*';  
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]='*';      
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]='*';      
            break;
        case    SERIAL_NM:
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            i=F_SerialNm10;
            DigitData=iF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    USER_LAMP1:
        case    USER_LAMP2:
        case    USER_LAMP3:
        case    USER_LAMP4:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=USER_LAMP_MESSAGE_CNT;
            DigitMinValue=0;
			if(LadderGroupSub == USER_LAMP1)		i=F_UserLamp1;
			else if(LadderGroupSub == USER_LAMP2)	i=F_UserLamp2;
			else if(LadderGroupSub == USER_LAMP3)	i=F_UserLamp3;
			else if(LadderGroupSub == USER_LAMP4)	i=F_UserLamp4;
//			else								i=F_UserLamp2;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    AIRCON_ADDR:
            Cursor=0;
            ShiftCnt=3;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=223;
            DigitMinValue=192;
            i=F_Airconadr;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
			break;
        case    ERR_ST_CNT:
            Cursor=0;
            ShiftCnt=3;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=255;
            DigitMinValue=0;
            i=F_ErrStopCnt;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    GROUP_NUMBER:
            Cursor=0;
            ShiftCnt=2;
            EditBlanck=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=31;
            DigitMinValue=0;
            i=F_GroupNm;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    LOCAL_NUMBER:
            Cursor=0;
            ShiftCnt=1;
            EditBlanck=7;
            EditStatus=DIGIT_EDIT;

#ifndef	MAX_EIGHT_CAR
            DigitMaxValue=3;
#else
            DigitMaxValue=7;
#endif
            DigitMinValue=0;
            i=F_LocalNm;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    NORMAL_DSP:                                      //NormalDsp
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=NORMAL_DSP_MESSAGE_CNT;
            DigitMinValue=0;
            i=F_NormalDsp;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    COMPANY_NAME:                           
            Cursor=0;
            ShiftCnt=1;
            EditBlanck=7;
            EditStatus=DIGIT_ALPHAR_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;
            i=F_Company;
            New485Ladder[SECONDLINE_BASE+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i));  
            break;
        case    HH_MM_SS:
            Cursor=0;
            ShiftCnt=8;
            EditBlanck=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditBlanck+0] =(sRamDArry[Hour]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+1] =(sRamDArry[Hour]    &  0x0f)   + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+3] =(sRamDArry[Minuate] >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+4]=(sRamDArry[Minuate] & 0x0f)     + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]=(sRamDArry[sec]     >> 4)       + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+7]=(sRamDArry[sec]     & 0x0f)     + '0';          
            break;
        case    YY_MM_DD:
            Cursor=0;
            ShiftCnt=8;
            EditBlanck=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditBlanck+0] =(sRamDArry[Year]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+1] =(sRamDArry[Year]    & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+3] =(sRamDArry[Month]   >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+4] =(sRamDArry[Month]   & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+6] =(sRamDArry[Day]     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+7] =(sRamDArry[Day]     & 0x0f)    + '0';          
            break;
        case    OUT_DATE:
            Cursor=0;
            ShiftCnt=8;
            EditBlanck=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditBlanck+0] =(cF_year    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+1] =(cF_year    & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+3] =(cF_month   >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+4] =(cF_month   & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+6] =(cF_day     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+7] =(cF_day     & 0x0f)    + '0';          
            break;
        case    DRIVE_METHOD:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=3;
            DigitMinValue=0;
            if((cF_NONSERVICE3 == 0xff) || (cF_NONSERVICE2 == 0xff) || (cF_NONSERVICE1 == 0xff) || (cF_NONSERVICE0 == 0xff))  DigitData=0;
            if((cF_NONSERVICE3 == 0x55) || (cF_NONSERVICE2 == 0x55) || (cF_NONSERVICE1 == 0x55) || (cF_NONSERVICE0 == 0x55))  DigitData=1;
            if((cF_NONSERVICE3 == 0xaa) || (cF_NONSERVICE2 == 0xaa) || (cF_NONSERVICE1 == 0xaa) || (cF_NONSERVICE0 == 0xaa))  DigitData=2;
            Integer_Digit();
            break;
        case    FHM_RUN_CHK:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=2;
            DigitMinValue=0;
            if(sRamDArry[FHM_RUN] == FHM_RUN_CMD)   DigitData=1;
            else                                    DigitData=0;

            Integer_Digit();
            break;
        case    LG_INV_IN_BD:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=2;
            DigitMinValue=0;
            i=F_PcbType;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;
        case    ALL_MENU_CHK:
        case    ENGINEER_NM:
            Cursor=0;
            ShiftCnt=4;
            EditBlanck=5;
            EditStatus=DIGIT_ALPHAR_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;

            New485Ladder[SECONDLINE_BASE+EditBlanck+0]='0';  
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]='0';  
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]='0';      
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]='0';      
            break;
        case    TOTAL_USE_TIME:
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=NO_EDIT;
            DigitMaxValue=0xffff;
            DigitMinValue=0;

            DigitData=PowerOnTime;
            Integer_Digit();
            break;
        case    INIT_DATA:
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=INIT_MESSAGE;
            DigitMinValue=0;
            DigitData=0;
            Integer_Digit();
            break;
        case    VIRTUAL_CALL:
            Cursor=0;
            ShiftCnt=9;
            EditBlanck=4;
            EditStatus=CLOCK_EDIT;

            if(sRamDArry[mVFlrCnt] > 254)			sRamDArry[mVFlrCnt]=0;
            if(sRamDArry[mVFlr1]   > (cF_TOPFLR+1))	sRamDArry[mVFlr1]=0;
            if(sRamDArry[mVFlr2]   > (cF_TOPFLR+1))	sRamDArry[mVFlr2]=0;
	
			i=sRamDArry[mVFlrCnt];
            New485Ladder[SECONDLINE_BASE+EditBlanck+0] =(i / 100)	+ '0';
			i=(i % 100);           
            New485Ladder[SECONDLINE_BASE+EditBlanck+1] =(i / 10)  + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+2] =(i % 10)  + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+3] ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+4] =(sRamDArry[mVFlr1] / 10)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+5] =(sRamDArry[mVFlr1] % 10)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+6] ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+7] =(sRamDArry[mVFlr2] / 10)	+ '0';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+8] =(sRamDArry[mVFlr2] % 10)    + '0';          

            break;

        case    HALL_IND_SET:
            Cursor=0;
            ShiftCnt=11;
            EditBlanck=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditBlanck+0]  =HibSet[0] + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+1]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+2]  =HibSet[1] + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+3]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+4]  =HibSet[2] + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+5]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+6]  =HibSet[3] + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+7]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+8]  =HibSet[4] + '0';
            New485Ladder[SECONDLINE_BASE+EditBlanck+9]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditBlanck+10] =HibSet[5] + '0';
            break;
		case    User_G4:
		case    User_G5:
		case    User_G6:
		case    User_G7:
		case    User_G8:
//		case    User_G9:
			break;
		case    ENCODER_RATE: 
            Cursor=0;
            ShiftCnt=5;
            EditBlanck=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            i=F_StopPulse0;
            DigitData=iF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

/*
            Cursor=0;
            ShiftCnt=0;
            EditBlanck=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=ENCODERRATE_MESSAGE_CNT;
            DigitMinValue=0;
            i=F_EncoderRate;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
*/
           break;
        default:
            break;
    }
}



void  __attribute__((section(".usercode"))) UserGroupSave(void)
{
    LocalType i,j,k,l;

    GetFlashDataToBufRam(F_BLOCK2);

    switch(LadderGroupSub){
        case    VERSION:
        case    TOTAL_USE_TIME:
            break;
        case    BOARD_ID:
//            if(bAllMenu){    
                if((DigitData==0) || (DigitData==3)|| (DigitData==6) ){
                    b_LdTmpBufRam(F_ManualSpeed)    = 1;      
                    b_LdTmpBufRam(F_DecreaseSpeed)  = 3;     
                    b_LdTmpBufRam(F_FhmSpeed)       = 8;                     
                    b_LdTmpBufRam(F_Speed60)        = 4;     
                    b_LdTmpBufRam(F_ElevSpeed)      = SPEED_60;                                    
                }

                if(DigitData==0){
                    DigitData=(LG | MAN_USE);
                }
                else if(DigitData==1){
                    DigitData=(IO | MAN_USE);
                }
                else if(DigitData==2){
                    DigitData=(D_F | MAN_USE);
                }
                else if(DigitData==3){
                    DigitData=(LG | BAGGAGE_USE);
                }
                else if(DigitData==4){
                    DigitData=(IO | BAGGAGE_USE);
                }
                else if(DigitData==5){
                    DigitData=(D_F | BAGGAGE_USE);
                }
                else if(DigitData==6){
                    DigitData=(LG | CARLIFT_USE);
                }
                else if(DigitData==7){
                    DigitData=(IO | CARLIFT_USE);
                }
                else if(DigitData==8){
                    DigitData=(D_F | CARLIFT_USE);
                }

                i=F_Bd_Id;
                b_LdTmpBufRam(i)=(LocalType)(DigitData);

                flash_write_DspChar(F_BLOCK2);                        
//            }
            break;
        case    ALL_MENU_CHK:
            if(bCompanyCtl==0){
				if( ((sRamDArry[Month] >> 4) & 0x000f) > 1)	bCompanyCtl=1;	
                if( (sRamDArry[Month] & 0x000f)        > 9) bCompanyCtl=1;
                if( ((sRamDArry[Day] >> 4) & 0x000f)   > 3) bCompanyCtl=1;			
                if( (sRamDArry[Day] & 0x000f)		   > 9)	bCompanyCtl=1;

	
                i=((sRamDArry[Month] >> 4) & 0x000f) * 1000;
                j=(sRamDArry[Month] & 0x000f) * 100;
                i=(i+j);
                j=((sRamDArry[Day] >> 4) & 0x000f) * 10;
                i=(i+j);
                j=(sRamDArry[Day] & 0x000f);
                i=(i+j);
                j=1014;
                i=i+j;
                if(i>=10000)    i=i-10000;

                
                k=((New485Ladder[SECONDLINE_BASE+EditBlanck+0] - '0') * 1000);
                j=((New485Ladder[SECONDLINE_BASE+EditBlanck+1] - '0') * 100);
                k=(j+k);
                j=((New485Ladder[SECONDLINE_BASE+EditBlanck+2] - '0') * 10);
                k=(j+k);
                j=(New485Ladder[SECONDLINE_BASE+EditBlanck+3] - '0');
                k=(j+k);

                if(i==k){
//                    bAllMenu=1;
					bCompanyCtl=1;
                    LadderGroup=0;
                    LadderGroupSub=0;
               } 
            }
            break;
        case    ENGINEER_NM:
             if(   ('1'== New485Ladder[SECONDLINE_BASE+EditBlanck+0]) 
                && ('2'== New485Ladder[SECONDLINE_BASE+EditBlanck+1]) 
                && ('3'== New485Ladder[SECONDLINE_BASE+EditBlanck+2]) 
                && ('4'== New485Ladder[SECONDLINE_BASE+EditBlanck+3])){

                 bUserOn=1;
                 LadderGroup=0;
                 LadderGroupSub=0;
            } 
            break;
        case    PASSWARD:
            if(bPasswardOk==0){
                if(   (pw[0]== New485Ladder[SECONDLINE_BASE+EditBlanck+0]) 
                   && (pw[1]== New485Ladder[SECONDLINE_BASE+EditBlanck+1]) 
                   && (pw[2]== New485Ladder[SECONDLINE_BASE+EditBlanck+2]) 
                   && (pw[3]== New485Ladder[SECONDLINE_BASE+EditBlanck+3])){

                    bPasswardOk=1;
                    LadderGroup=0;
                    LadderGroupSub=0;
               } 
            }
            else{
                i=F_Passward0;
    
                b_LdTmpBufRam((unsigned long)(i+0))=(LocalType)(New485Ladder[SECONDLINE_BASE+EditBlanck+0]);
                b_LdTmpBufRam((unsigned long)(i+1))=(LocalType)(New485Ladder[SECONDLINE_BASE+EditBlanck+1]);
                b_LdTmpBufRam((unsigned long)(i+2))=(LocalType)(New485Ladder[SECONDLINE_BASE+EditBlanck+2]);
                b_LdTmpBufRam((unsigned long)(i+3))=(LocalType)(New485Ladder[SECONDLINE_BASE+EditBlanck+3]);
    
                flash_write_DspChar(F_BLOCK2);

				PasswardCheck();

                LadderGroup=0;
                LadderGroupSub=0;
            }
            break;
        case    SERIAL_NM:
            i=F_SerialNm10;
            i_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    USER_LAMP1:
        case    USER_LAMP2:
        case    USER_LAMP3:
        case    USER_LAMP4:
        case    GROUP_NUMBER:
        case    LOCAL_NUMBER:
			if(LadderGroupSub == USER_LAMP1)		i=F_UserLamp1;
			else if(LadderGroupSub == USER_LAMP2)	i=F_UserLamp2;
			else if(LadderGroupSub == USER_LAMP3)	i=F_UserLamp3;
			else if(LadderGroupSub == USER_LAMP4)	i=F_UserLamp4;
			else if(LadderGroupSub == LOCAL_NUMBER)	i=F_LocalNm;
			else									i=F_GroupNm;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
/*
        case    USER_LAMP2:
           i=F_UserLamp2;
           b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
           flash_write_DspChar(F_BLOCK2);
            break;
        case    GROUP_NUMBER:
            i=F_GroupNm;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    LOCAL_NUMBER:
            i=F_LocalNm;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
*/
        case    LG_INV_IN_BD:
            i=F_PcbType;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    ERR_ST_CNT:
            i=F_ErrStopCnt;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    AIRCON_ADDR:
        	i=F_Airconadr;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    NORMAL_DSP:
            i=F_NormalDsp;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    COMPANY_NAME:
            i=F_Company;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(New485Ladder[SECONDLINE_BASE+EditBlanck+0]);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    VIRTUAL_CALL:
			i=New485Ladder[SECONDLINE_BASE+EditBlanck+0];
			i=((i - '0') * 100);
			j=New485Ladder[SECONDLINE_BASE+EditBlanck+1];
			j=((j-'0') * 10);
			k=New485Ladder[SECONDLINE_BASE+EditBlanck+2];
			k=(k -'0');

			i = (i + j + k);
			if(i <= 254)	sRamDArry[mVFlrCnt]=i;	


//////////////////////////////////////////////////////////
			i=New485Ladder[SECONDLINE_BASE+EditBlanck+4];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditBlanck+5];
			j=(j-'0');
			i=(i+j);

			if(i <= (cF_TOPFLR+1))	sRamDArry[mVFlr1]=i;	
			else					sRamDArry[mVFlr1]=0;	
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
			i=New485Ladder[SECONDLINE_BASE+EditBlanck+7];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditBlanck+8];
			j=(j-'0');
			i=(i+j);

			if(i <= (cF_TOPFLR+1))	sRamDArry[mVFlr2]=i;	
			else					sRamDArry[mVFlr2]=0;	
//////////////////////////////////////////////////////////



/*
			i=New485Ladder[SECONDLINE_BASE+EditBlanck+0];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditBlanck+1];
			j=(j-'0');
			i=(i+j);

			if(i < 100)	sRamDArry[mVFlrCnt]=i;	
//////////////////////////////////////////////////////////
			i=New485Ladder[SECONDLINE_BASE+EditBlanck+3];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditBlanck+4];
			j=(j-'0');
			i=(i+j);

			if(i <= (cF_TOPFLR+1))	sRamDArry[mVFlr1]=i;	
			else					sRamDArry[mVFlr1]=0;	
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
			i=New485Ladder[SECONDLINE_BASE+EditBlanck+6];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditBlanck+7];
			j=(j-'0');
			i=(i+j);

			if(i <= (cF_TOPFLR+1))	sRamDArry[mVFlr2]=i;	
			else					sRamDArry[mVFlr2]=0;	
//////////////////////////////////////////////////////////
*/
            break;
        case    HH_MM_SS:
//            if(bAllMenu){
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+0]-'0') << 4;
                sRamDArry[Hour]=DigitData  | (New485Ladder[SECONDLINE_BASE+EditBlanck+1]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+3]-'0') << 4;
                sRamDArry[Minuate]=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+4]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+6]-'0') << 4;
                sRamDArry[sec]=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+7]-'0');
    
                Initialize_DS1302();
//            }
            break;
        case    YY_MM_DD:
//            if(bAllMenu){
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+0]-'0') << 4;
                sRamDArry[Year]=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+1]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+3]-'0') << 4;
                sRamDArry[Month]=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+4]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+6]-'0') << 4;
                sRamDArry[Day]=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+7]-'0');
    
                Initialize_DS1302();
//            }
            break;
        case    OUT_DATE:
//            if(bAllMenu){
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+0]-'0') << 4;
                b_LdTmpBufRam(F_year)=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+1]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+3]-'0') << 4;
                b_LdTmpBufRam(F_month)=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+4]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditBlanck+6]-'0') << 4;
                b_LdTmpBufRam(F_day)=DigitData | (New485Ladder[SECONDLINE_BASE+EditBlanck+7]-'0');

	            flash_write_DspChar(F_BLOCK2);
//            }
            break;
        case    DRIVE_METHOD:
            GetFlashDataToBufRam(F_BLOCK1);
            i=F_NonService0;

            if(DigitData==1)		DigitData=0x55;  //礎熱
            else if(DigitData==2)	DigitData=0xaa;	 //�汝�	
            else if(DigitData==0)	DigitData=0xff;  //瞪類 
			
            b_LdTmpBufRam((unsigned long)(i+0))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+1))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+2))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+3))=(LocalType)(DigitData);                
            flash_write_DspChar(F_BLOCK1);

			sRamDArry[ExtCmdFlrONOFF0]=cF_NONSERVICE0;
			sRamDArry[ExtCmdFlrONOFF1]=cF_NONSERVICE1;
			sRamDArry[ExtCmdFlrONOFF2]=cF_NONSERVICE2;
			sRamDArry[ExtCmdFlrONOFF3]=cF_NONSERVICE3;


            break;
        case    FHM_RUN_CHK:
            if((sRamDArry[FHM_RUN] != FHM_RUN_CMD) && (DigitData==1)){
                sRamDArry[FHM_RUN] = FHM_RUN_CMD;
                LadderKey=0xff;
            }
            else{
                sRamDArry[FHM_RUN] = 0;
            }

            LadderGroup=0;
            LadderGroupSub=0;
            break;
        case    INIT_DATA:
            switch(DigitData){
                case    1:
					MoveCounterx=0;
					SaveMoveCounter=10;
					MvCounter();
                    break;
                case    2:
					if(!bMoveCar){
	               	    for(i=0;i<ERR_SAVE_SIZE;){
							eDArry[eErrCntPt]=EEPROM_Read_Byte(eErrCntPt);
							if(eDArry[eErrCntPt] > 0){	
			        			EEPROM_Write_Byte((unsigned int)(eErrCntPt),0);
							}            
	
							if(!EEPROM_write_Ready()){
		                  	    eDArry[eSysErCnt+i]=0x0;         
		                        if( !EEPROM_Write_Byte(eSysErCnt+i,0x0)){
									i++;
								}
							}
	               	    }
	
	
	            	    sRamDArry[mBefErrCntPt]=0x0;
	                    eDArry[eErrCntPt]=0x0;
	                    bSaveErrCnt=0;
					}
                    break;
                case    3:
					bExportData=1;
					SrcAdrBlk=0;
					LoaderChk=0;
                    break;
                case    4:
					bImportData=1;
					SrcAdrBlk=0;
					LoaderChk=0;
                    break;
            }
            break;
        case    ENCODER_RATE:
            i=F_StopPulse0;
            i_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    HALL_IND_SET:
            HibSet[0]=(New485Ladder[SECONDLINE_BASE+EditBlanck+0] 	- '0');
            HibSet[1]=(New485Ladder[SECONDLINE_BASE+EditBlanck+2] 	- '0');
            HibSet[2]=(New485Ladder[SECONDLINE_BASE+EditBlanck+4] 	- '0');
            HibSet[3]=(New485Ladder[SECONDLINE_BASE+EditBlanck+6] 	- '0');
            HibSet[4]=(New485Ladder[SECONDLINE_BASE+EditBlanck+8] 	- '0');
            HibSet[5]=(New485Ladder[SECONDLINE_BASE+EditBlanck+10] 	- '0');

			if((sRamDArry[DSP1]  == '9') &&  (sRamDArry[DSP2]  == '1')){
				if(HibSet[0] > 9)	HibSet[0]=0;
				if(HibSet[1] > 9)	HibSet[1]=0;
				if(HibSet[2] > 9)	HibSet[2]=0;
				if(HibSet[3] > 9)	HibSet[3]=0;
				if(HibSet[4] > 9)	HibSet[4]=0;
				if(HibSet[5] > 9)	HibSet[5]=0;
				bHibSet=1;
			}	
			break;
        default:
            break;

    }
}




void  __attribute__((section(".usercode"))) ParameterGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=5;
    EditBlanck=5;
    EditStatus=DIGIT_EDIT;

    DigitMaxValue=0xffff;
    DigitMinValue=0;

    DigitData=(unsigned int)(GET_LONG((unsigned long)i));    
    if(LadderGroupSub==P_TM_MPM){
        DigitMaxValue=211;
        ShiftCnt=3;
    }
    
    Integer_Digit();

}


void  __attribute__((section(".usercode"))) ParameterGroupSave(void)
{
    LocalType  i;

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[ENCODER_PULSE+i].long_data;  
    }

    l_LdTmpBufRam(LadderGroupSub)=(unsigned long)DigitData;

    flash_write(ENCODER_PULSE);
}




void  __attribute__((section(".usercode"))) InportGroup(void)
{
    
    LocalType i;

    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditBlanck=4;
    EditStatus=DIGIT_STRING_EDIT;

    DigitMaxValue=NO_USE_IN+1;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData & 0x80)    OrgNcNo=0x80;  //
    else                    OrgNcNo=0x00;  //

    DigitData=(DigitData & 0x7f);

    Integer_Digit();    
}





void  __attribute__((section(".usercode"))) InportSave(void)
{
    LocalType i,j,k,ChangeDisable;

    i=(LadderGroupSub + GroupBaseAddr);
    GetFlashDataToBufRam(F_BLOCK4);

    ChangeDisable=0;
    for(k=0;k <(DigitMaxValue-1);k++){
        j=b_LdTmpBufRam(k); //
        j=(j & 0x7f);       //
        if(j == DigitData)  ChangeDisable=1;
    }
    
    if((ChangeDisable==0) || (DigitData == NO_USE_IN) ){    
        if(DigitData == NO_USE_IN) DigitData=(DigitData | 0x80);       //
        else                        DigitData=(DigitData | OrgNcNo);    //

        b_LdTmpBufRam(i)=(LocalType)(DigitData);
        flash_write_DspChar(F_BLOCK4);
    }
}




void  __attribute__((section(".usercode"))) OutportGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditBlanck=4;
    EditStatus=DIGIT_STRING_EDIT;

    DigitMaxValue=24;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData & 0x80)    OrgNcNo=0x80;  //
    else                    OrgNcNo=0x00;  //
    DigitData=(DigitData & 0x7f);

    Integer_Digit();    
}



void  __attribute__((section(".usercode"))) OutportSave(void)
{
    LocalType i,j,k,ChangeDisable;

    i=(LadderGroupSub + GroupBaseAddr);
    GetFlashDataToBufRam(F_BLOCK5);
    
    ChangeDisable=0;
    for(k=0;k < (DigitMaxValue-1);k++){
        j=b_LdTmpBufRam(k); //
        j=(j & 0x7f);       //
        if(j == DigitData)  ChangeDisable=1;
    }
    
    if((ChangeDisable==0) || (DigitData == NO_USE_OUT) ){
        if(DigitData == NO_USE_OUT) DigitData=(DigitData | 0x80);       //
        else                        DigitData=(DigitData | OrgNcNo);    //

        b_LdTmpBufRam(i)=(LocalType)(DigitData);
        flash_write_DspChar(F_BLOCK5);
    }
}



void  __attribute__((section(".usercode"))) ErrorGroup(LocalType offset)
{
    LocalType i,j;

    EditStatus=NO_EDIT;

    offset=offset * ERR_SAVE_WIDE;

    New485Ladder[2]  ='E';          
    New485Ladder[3]  ='R';
    New485Ladder[4]  =':';


    if(eDArry[eSysErCnt + offset + 0] > 0){
        New485Ladder[5]  =(eDArry[eSysErCnt + offset + 0] >> 4  ) + '0';  //month          
        New485Ladder[6]  =(eDArry[eSysErCnt + offset + 0] & 0x0f) + '0';
        New485Ladder[7]  =(eDArry[eSysErCnt + offset + 1] >> 4  ) + '0';  //date          
        New485Ladder[8]  =(eDArry[eSysErCnt + offset + 1] & 0x0f) + '0';
        New485Ladder[9] ='/';          
        New485Ladder[10] =(eDArry[eSysErCnt + offset + 4] >> 4  ) + '0';  //hour         
        New485Ladder[11] =(eDArry[eSysErCnt + offset + 4] & 0x0f) + '0';
        New485Ladder[12] =(eDArry[eSysErCnt + offset + 5] >> 4  ) + '0';  //min         
        New485Ladder[13] =(eDArry[eSysErCnt + offset + 5] & 0x0f) + '0';
        New485Ladder[14] ='/';          
        New485Ladder[15] =(eDArry[eSysErCnt + offset + 2] /10  )  + '0';  //floor       
        New485Ladder[16] =(eDArry[eSysErCnt + offset + 2] %10  )  + '0';
        New485Ladder[17] ='F';
    
        j=eDArry[eSysErCnt + 3 + offset];
        for(i=0;i<16;i++){
            New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          //error status
        }
    }
    else{
        j=LadderGroup;
//        j=(LadderGroupSub + ((j-1) * 32))+1;
        j=((j-1) * 32)+1;

        for(i=0;i<16;i++){
//            New485Ladder[i+2]=GroupLineMessage[j][i];
            New485Ladder[i+2]=GroupLineMessage[j][i];
        }
        New485Ladder[15]=(LadderGroupSub / 10)+ '0';
        New485Ladder[16]=(LadderGroupSub % 10)+ '0';

        for(i=0;i<16;i++){
//            New485Ladder[SECONDLINE_BASE+i]=GroupLineMessage[j][i];
            New485Ladder[SECONDLINE_BASE+i]=GroupLineMessage[j][i];
        }
        New485Ladder[SECONDLINE_BASE+13]=(LadderGroupSub / 10)+ '0';
        New485Ladder[SECONDLINE_BASE+14]=(LadderGroupSub % 10)+ '0';
    }
}



unsigned int  __attribute__((section(".usercode"))) SaveData(void)
{
    LocalType i;

    switch(LadderGroup){
        case    FLR_DSP_GROUP:
            FlrDspGroupSave(LadderGroupSub);
            break;
        case    FLR_GROUP:
            FlrGroupSave();
            break;
        case    TIMER_GROUP:
            TimerGroupSave();
			CmdFixFlrTime=cF_FIXFLOORTIME;
            break;
        case    SUB_DOOR_GROUP:
			DoorGroupSave();
//            OnOffGroupSave();
            break;
        case    ONOFF1_GROUP:
            OnOffGroupSave();

			sRamDArry[ExtCmdFlrONOFF0]=cF_NONSERVICE0;
			sRamDArry[ExtCmdFlrONOFF1]=cF_NONSERVICE1;
			sRamDArry[ExtCmdFlrONOFF2]=cF_NONSERVICE2;
			sRamDArry[ExtCmdFlrONOFF3]=cF_NONSERVICE3;

            break;
        case    ONOFF2_GROUP:
            OnOffGroupSave();
            if(EncoderPhaseChk) SWPAB   = 1;
            else                SWPAB   = 0;

			if(FamilyService)	bPC_FAMILY=1;
			else				bPC_FAMILY=0;

            break;
        case    NCNO1_GROUP:
        case    NCNO2_GROUP:
            InNcNoGroupSave();
            break;
        case    NCNO3_GROUP:
            OutNcNoGroupSave();
            break;
        case    IO_GROUP:
//            if(bAllMenu || bPasswardOk) 
			IoGroupSave();
            break;
        case    USER_GROUP:    //save
            UserGroupSave();
            break;
        case    OPEN_WAIT_GROUP:
            WaitFlrGroupSave();
            break;
        case    PARAMETER_GROUP:
            if(LadderGroupSub<= DEC_LENGTH_210){
//                if(bAllMenu || bPasswardOk){               
                    ParameterGroupSave();
                    CaluDecreasePulse();
//                }
            }
            break;
        case    INPORT1_GROUP:
        case    INPORT2_GROUP:
            InportSave();
            break;
        case    OUTPORT_GROUP:
            OutportSave();
            break;
        case    ERROR_GROUP:
            break;
        default:
            break;

    }

    Cursor=0;

}


void  __attribute__((section(".usercode"))) CursorOff(void)
{
    New485Ladder[SECONDLINE_CURSOR]=' ';  
}

void  __attribute__((section(".usercode"))) CursorOn(void)
{
    LocalType i;

    i=Cursor + EditBlanck;                    
    if(i>0x09)  i=i + '7';
    else        i=i + '0';
    New485Ladder[SECONDLINE_CURSOR]=i;  
}


unsigned int  __attribute__((section(".usercode"))) CusorDigitSet(void)
{
    LocalType i;
    i=SECONDLINE_BASE + EditBlanck + Cursor;

    switch(EditStatus){
        case    DIGIT_EDIT:
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]=LadderKey;
            break;
    }         
}
                        

unsigned int  __attribute__((section(".usercode"))) CusorDataUp(void)
{
    LocalType i;
    i=SECONDLINE_BASE + EditBlanck + Cursor;

    switch(EditStatus){
        case    DIGIT_EDIT:
            switch(ShiftCnt-Cursor){
                case    1:
                    DigitData++;
                    break;
                case    2:
                    DigitData=DigitData+10;
                    break;                    
                case    3:
                    DigitData=DigitData+100;
                    break;                    
                case    4:
                    DigitData=DigitData+1000;
                    break;                    
                case    5:
                    DigitData=DigitData+10000;
                    break;                    
            }
            Integer_Digit();    
            break;
        case    DIGIT_STRING_EDIT:
            if(DigitMaxValue>0){
                DigitData=(DigitData+1)%DigitMaxValue;
            }
            Integer_Digit();    
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]++;
            if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  New485Ladder[i]='A'; 
            else if((New485Ladder[i]>'Z'))                      New485Ladder[i]='0'; 
            break;
        case    CLOCK_EDIT:
            New485Ladder[i]++;
            if((New485Ladder[i]<'0'))       New485Ladder[i]='9'; 
            else if(New485Ladder[i]>'9')    New485Ladder[i]='0'; 
            CalendarChk(); 
            break;
        case    TABLE_EDIT:
                break;    
        case    TOGGLE_EDIT:
                break;    
    }         
}


unsigned int  __attribute__((section(".usercode"))) CusorDataDn(void)
{
    LocalType i;

    i=SECONDLINE_BASE + EditBlanck + Cursor;

    switch(EditStatus){
        case    DIGIT_EDIT:
            switch(ShiftCnt-Cursor){
                case    1:
                    if(DigitData > 0)           DigitData--;
                    break;
                case    2:
                    if(DigitData >= 10)         DigitData=DigitData-10;
                    break;                    
                case    3:
                    if(DigitData >= 100)        DigitData=DigitData-100;
                    break;                    
                case    4:
                    if(DigitData >= 1000)       DigitData=DigitData-1000;
                    break;                    
                case    5:
                    if(DigitData >= 10000)      DigitData=DigitData-10000;
                    break;                    
            }
            Integer_Digit();    
            break;
        case    DIGIT_STRING_EDIT:
            if(DigitData > DigitMinValue)   DigitData--; 
            else                            DigitData=(DigitMaxValue-1);
            Integer_Digit();    
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]--;
            if((New485Ladder[i]<'0'))                      New485Ladder[i]='Z'; 
            else if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  New485Ladder[i]='9'; 
            break;
        case    CLOCK_EDIT:
            New485Ladder[i]--;
            if((New485Ladder[i]<'0'))       New485Ladder[i]='9'; 
            else if(New485Ladder[i]>'9')    New485Ladder[i]='0';
            CalendarChk(); 
            break;
        case    TABLE_EDIT:
                break;    
        case    TOGGLE_EDIT:
                break;    
    }         
}


unsigned int  __attribute__((section(".usercode"))) ShiftRightCur(void)
{
    LocalType i;

    if(ShiftCnt==0) Cursor=0;
    else            Cursor=(Cursor+1)%ShiftCnt; 

    i=SECONDLINE_BASE + EditBlanck + Cursor;

    if(EditStatus == DIGIT_EDIT){
        if((New485Ladder[i] == '.') || (New485Ladder[i] == ('.' + 0x80))){
            if(ShiftCnt==0) Cursor=0;
            else            Cursor=(Cursor+1)%ShiftCnt; 
        }
    }           
    else if(EditStatus == CLOCK_EDIT){
        if((New485Ladder[i] == '-') || (New485Ladder[i] == ('-' + 0x80))){
            if(ShiftCnt==0) Cursor=0;
            else            Cursor=(Cursor+1)%ShiftCnt; 
        }
    }           
}


unsigned int  __attribute__((section(".usercode"))) ShiftLeftCur(void)
{
    LocalType i;

    if(ShiftCnt==0)     Cursor=0;
    else if(Cursor>0)   Cursor--;
    else                Cursor=ShiftCnt-1;

    i=SECONDLINE_BASE + EditBlanck + Cursor;

    if(EditStatus == DIGIT_EDIT){
        if((New485Ladder[i] == '.') || (New485Ladder[i] == ('.' + 0x80))){
            if(ShiftCnt==0)     Cursor=0;
            else if(Cursor>0)   Cursor--;
            else                Cursor=ShiftCnt-1;
        }
    }           
    else if(EditStatus == CLOCK_EDIT){
        if((New485Ladder[i] == '-') || (New485Ladder[i] == ('-' + 0x80))){
            if(ShiftCnt==0) Cursor=0;
            else if(Cursor>0)   Cursor--;
            else                Cursor=ShiftCnt-1;
        }
    }           
}


unsigned int  __attribute__((section(".usercode"))) MenuOnChk(void)
{

    LocalType i;

	i=0;

	if(LadderGroup != USER_GROUP)	return(i); 

	switch(LadderGroupSub){
		case	COMPANY_NAME:
			if(!bCompanyCtl)	i=1;
			break;
		case	INIT_DATA:
			if(!bAllMenu)		i=1;
			break;
		case	ERR_ST_CNT:
		case	OUT_DATE:
			if( !bPasswardUse || !bAllMenu)	i=1;
			break;
		default:
			break;
	}

	return(i);
}


unsigned int  __attribute__((section(".usercode"))) GroupOnChk(void)
{
    if(bAllMenu)  		return(0);
	if(!bPasswardUse)	return(0);
	
    switch(LadderGroup){
        case    USER_GROUP:  //save
        case    ERROR_GROUP:
            return(0);
            break;
        default:
            return(1);
            break;
    }
}






unsigned int  __attribute__((section(".usercode"))) EditOnCheck(void)
{
    LocalType i;
    
    i=0;

    if(EditStatus==NO_EDIT) return(i);
    if(bMoveCar)            return(i);



/*		//ver3.5
    if(!bUserOn && !bAllMenu){
        i=0;
        if(LadderGroup == USER_GROUP){     //save
            switch(LadderGroupSub){
               	case    PASSWARD:
               	case    ALL_MENU_CHK:
               	case    ENGINEER_NM:
                  	i=1;
                   	break;
            }
        }
	}
*/


    if(bAllMenu)			i=1;	//ver3.5
	else{
       	if(LadderGroup == USER_GROUP){     
           	switch(LadderGroupSub){
               	case    PASSWARD:
               	case    ALL_MENU_CHK:
 //engineer number delete   				if(bUserOn)	i=1;
					i=1;
                   	break;
               	case    ENGINEER_NM:
                   	i=1;
                   	break;
				default:
					i=0;
                   	break;
           	}
       	}
	}

	return(i);

}


unsigned int  __attribute__((section(".usercode"))) KeyCheck(void)
{
    LocalType i,j,newmenu;

	j=0;
    newmenu=1;

    LadderKey = LadderBuf[C_SAVE_DATA+0];

	if( !bLoaderActive)	LadderKey = 'N';	


    switch(LadderKey){
        case    MENUKEY:
				bHibSet=0;	
                LadderKeyTime=0;
                do{
					j++;
                    i=1;
                    LadderGroup=(LadderGroup+1)%MAX_GROUP;
                    LadderGroupSub=0;
                    NewMenuStart();
                    CursorOff();
                    i=GroupOnChk(); 
                }while(i && (j <30));
                break;
        case    ESCKEY:
				bHibSet=0;	
                LadderKeyTime=0;
                LadderGroup=0;
                LadderGroupSub=0;
                NewMenuStart();
                CursorOff(); 
                break;
        case    UPKEY:
				bHibSet=0;	
                LadderKeyTime=0;
                if(EnterKey==1){
	                do{
                        LadderGroupSub=(LadderGroupSub+1)% MaxSubMenu;
	                    i=MenuOnChk(); 
	                }while(i);
                    NewMenuStart();
                    CursorOff(); 
                }
                else if(EnterKey==2){
                    CusorDataUp();
					newmenu=0;
                }
                break;
        case    DOWNKEY:
				bHibSet=0;	
                LadderKeyTime=0;
                if(EnterKey==1){
	                do{
	                    if(LadderGroupSub>0)    LadderGroupSub--;
	                    else                    LadderGroupSub=MaxSubMenu-1;                    
	                    i=MenuOnChk(); 
	                }while(i);
                    NewMenuStart();
                    CursorOff(); 
                }
                else if(EnterKey==2){
                    CusorDataDn();
					newmenu=0;
                }
                break;
        case    LEFTKEY:
				bHibSet=0;	
                LadderKeyTime=0;
                if(EnterKey==1){
                    do{
                        i=1;
                        if(LadderGroup>0)   LadderGroup--;
                        else                LadderGroup=MAX_GROUP-1;
                        LadderGroupSub=0;
                        NewMenuStart();
                        CursorOff(); 
                        i=GroupOnChk(); 
                    }while(i);
                }
                else if(EnterKey==2){
                    ShiftLeftCur();
                    CursorOn();
					newmenu=0;
                }
                break;
        case    RIGHTKEY:
				bHibSet=0;	
                LadderKeyTime=0;
                if(EnterKey==1){
                    do{
                        i=1;
                        if(LadderGroup>0)   LadderGroup--;
                        else                LadderGroup=MAX_GROUP-1;
                        NewMenuStart();
                        CursorOff(); 
                        i=GroupOnChk(); 
                    }while(i);
                }
                else if(EnterKey==2){
                    ShiftRightCur();
                    CursorOn();
					newmenu=0;
                }
                break;
        case    ENTKEY:
				newmenu=0;
                LadderKeyTime=0;
                EnterKey++;
                if(EnterKey==2){
                    if(!EditOnCheck()){
                        EnterKey=1;
                        CursorOff(); 
                    }
                    else    CursorOn();
					bHibSet=0;	
                }
                else if(EnterKey==3){
                    if(!bMoveCar){
						SaveVerify = 0x55;
                        SaveData();
						SaveVerify = 0x0;
                    }
                    EnterKey=0;
                }
				else{
					bHibSet=0;	
				}
                break;
        case    ONEKEY:
        case    TWOKEY:
        case    THREEKEY:
        case    FOURKEY:
        case    FIVEKEY:
        case    SIXKEY:
        case    SEVENKEY:
        case    EIGHTKEY:
        case    NINEKEY:
        case    ZEROKEY:   
                LadderKeyTime=0;
                CusorDigitSet();
				newmenu=0;
                break;

#ifdef	GOBERNOR_LOCK
        case    'z':
				NotRecoveryData=(NotRecoveryData | 0x8000);
				newmenu=0;
                break;
#endif

        default:
                LadderKey = 0xff;
				newmenu=0;
                break;
    }   
	
	if(newmenu){
        for(i=0;i<16;i++){
            New485Ladder[i+2]=blinkx[i];
        }
        for(i=0;i<16;i++){
            New485Ladder[SECONDLINE_BASE+i]=blinkx[i];
        }
	}


    if(LadderKey != 0xff){
		if(!FhmSuccessCheck())	sRamDArry[FHM_SEQ]=0;
	}

    return(0);
}



////////////////////new ladder////////////////////////////
unsigned int  __attribute__((section(".usercode"))) NewFlashData(void)
{
    LocalType i,j;

    unsigned int count;
    unsigned int chun,bek,sip,il;

    chun=bek=sip=il=0;

    if(LadderGroup==0){
		bExportData=0;
		bImportData=0;

		if(sRamDArry[DSP1] == 0)	sRamDArry[DSP1] = '?';	
		if(sRamDArry[DSP2] == 0)	sRamDArry[DSP2] = '?';	
        New485Ladder[2+3]=sRamDArry[DSP1];
        New485Ladder[2+4]=sRamDArry[DSP2];


        if(bCarUpMove || bCarDnMove){ 
        
            chun=(unsigned int)CurMeterPerMin;

            if(chun)    il=(chun%10);
            
            if(chun)    sip=(chun/10);
            if(sip)     sip=(sip%10);

            if(chun)    bek=(chun/100);
            if(bek)     bek=(bek%10);;

            if(chun)    chun=chun/1000;
            if(chun)    chun=(chun%10);
        
    
    
            New485Ladder[2+8] =chun + '0';
            New485Ladder[2+9] =bek  + '0';
            New485Ladder[2+10]=sip  + '0';
            New485Ladder[2+11]='.';
            New485Ladder[2+12]=il   + '0';
            New485Ladder[2+13]='m';
            New485Ladder[2+14]='p';
            New485Ladder[2+15]='m';
        }    

/*
        if(bCarUpMove){
            New485Ladder[2+8]='E';
            New485Ladder[2+9]='/';
            New485Ladder[2+10]='L';
            New485Ladder[2+11]='.';
            New485Ladder[2+12]=' ';
            New485Ladder[2+13]='U';
            New485Ladder[2+14]='p';
            New485Ladder[2+15]=' ';
        }
        else if(bCarDnMove){
            New485Ladder[2+8]='E';
            New485Ladder[2+9]='/';
            New485Ladder[2+10]='L';
            New485Ladder[2+11]='.';
            New485Ladder[2+12]=' ';
            New485Ladder[2+13]='D';
            New485Ladder[2+14]='n';
            New485Ladder[2+15]=' ';
        }
*/

        else{
            New485Ladder[2+8]='E';
            New485Ladder[2+9]='/';
            New485Ladder[2+10]='L';
            New485Ladder[2+11]='.';
            New485Ladder[2+12]='S';
            New485Ladder[2+13]='t';
            New485Ladder[2+14]='o';
            New485Ladder[2+15]='p';
        }
    }



    if((LadderKeyTime > 36000) && (LadderKeyTime < 36002)){        
		LadderKeyTime=36012;

        LadderGroup=0;
        LadderGroupSub=0;
        EnterKey=0;

		PasswardCheck();

        bAllMenu=0;
		bUserOn=0;
		bLoaderActive=0;
    }

//engineer number delete	if(bPasswardOk &&  bUserOn)	bAllMenu=1;			//ver3.5
	if(bPasswardOk )			bAllMenu=1;			//ver3.5
	else						bAllMenu=0;			//ver3.5
	 

    KeyCheck();

    if(EnterKey==0){

        EnterKey=1;
            
        for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';
        New485Ladder[MAX_LADDER_BUF-1]=0x0;   

        j=LadderGroup;

        if(j>0){    
            j=(LadderGroupSub + ((j-1) * 32))+1;
        }

        for(i=0;i<16;i++){
            New485Ladder[i+2]=GroupLineMessage[j][i];
        }

        if(j==0){
            New485Ladder[2+3]=sRamDArry[DSP1];
            New485Ladder[2+4]=sRamDArry[DSP2];
        }
        

        New485Ladder[0]=LadderKey;    
        New485Ladder[1]=' ';

        New485Ladder[SECONDLINE_BASE+0] =(LadderGroupSub/10) + '0';          
        New485Ladder[SECONDLINE_BASE+1] =(LadderGroupSub%10) + '0';          
        
        switch(LadderGroup){
            case    FLR_DSP_GROUP:
                GroupBaseAddr=F_FlrDspCh;
                FlrDspGroup(LadderGroupSub);
                break;
            case    FLR_GROUP:
                GroupBaseAddr=F_TopFlr;
                FlrGroup();
                break;
            case    TIMER_GROUP:
                GroupBaseAddr=F_OpWtTm;
                TimerGroup();
                break;
/////////////////////////
            case    SUB_DOOR_GROUP:
                GroupBaseAddr=F_SubDoorFlr1;
				DoorGroup();
//                OnOffGroup();
                break;
///////////////////////////////
            case    ONOFF1_GROUP:
                GroupBaseAddr=F_NonService0;
                OnOffGroup();
                break;
            case    ONOFF2_GROUP:
                GroupBaseAddr=F_OnOff0;
                OnOffGroup();
                break;
            case    NCNO1_GROUP:
                GroupBaseAddr=EMG_PORT;
                NcNoGroup();
                break;
            case    NCNO2_GROUP:
                GroupBaseAddr=X0_PORT;
                NcNoGroup();
                break;
            case    NCNO3_GROUP:
                GroupBaseAddr=FAN_PORT;
                NcNoGroup();
                break;
            case    IO_GROUP:
                GroupBaseAddr=F_ManualSpeed;
                IoGroup();
                break;
            case    USER_GROUP:       //save
                GroupBaseAddr=F_Ver0;
                UserGroup();
                break;
            case    OPEN_WAIT_GROUP:
                GroupBaseAddr=F_0506;
                WaitFlrGroup();
                break;
            case    PARAMETER_GROUP:
                GroupBaseAddr=ENCODER_PULSE;
                ParameterGroup();
                break;
            case    INPORT1_GROUP:
                GroupBaseAddr=EMG_PORT;
                InportGroup();
                break;
            case    INPORT2_GROUP:
                GroupBaseAddr=X0_PORT;
                InportGroup();
                break;
            case    OUTPORT_GROUP:
                GroupBaseAddr=FAN_PORT;
                OutportGroup();
                break;
            case    ERROR_GROUP:
                ErrorGroup(LadderGroupSub);
                break;
            default:                
                break;
    
        }
    }

   	LadderBuf[C_BASE_MEMORY]=LadderGroup;              
   	LadderBuf[C_OFFSET_MEMORY]=LadderGroupSub;          

    if(LadderGroup==0){
        DefaultDisplay();
    }

    LadderTime=0;

    if(sRamDArry[FHM_RUN] == FHM_RUN_CMD)                   FhmLoaderTime=0;
    else                                                    FhmLoaderTime=10;
                                    
    if((sRamDArry[FHM_RUN] == FHM_RUN_CMD) && (LadderKey != 0xff)){
        FhmLoaderTime=10;
        sRamDArry[FHM_RUN] =0;
    }


	if((LadderGroup != USER_GROUP) || (LadderGroupSub != HALL_IND_SET) || !IN_AUTO || (sRamDArry[DSP1] != '9') || (sRamDArry[DSP2] != '1')){
		HibSet[0]=0;
		HibSet[1]=0;
		HibSet[2]=0;
		HibSet[3]=0;
		HibSet[4]=0;
		HibSet[5]=0;
		bHibSet=0;	
	}
        
    return(0);
}




void  __attribute__((section(".usercode"))) Ladder485Init(void)
{
    LocalType i;

    LadderGroup=0;
    LadderGroupSub=0;

    MaxSubMenu=USER_GROUP_MAX;   //save

    NewMenuStart();

    for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';

    New485Ladder[MAX_LADDER_BUF-1]=0x0;

	PasswardCheck();

    bAllMenu=0;
    bUserOn=0;
	bExportData=0;
	bImportData=0;
}



void  __attribute__((section(".usercode"))) Pc_Command(void)
{


    if((CAN2_Buf[2] == (CMD_EVEN_ODD)) && (CAN2_Buf[3] == 0x00)){
		sRamDArry[ExtCmdFlrONOFF0] = CAN2_Buf[4];
		sRamDArry[ExtCmdFlrONOFF1] = CAN2_Buf[5];
		sRamDArry[ExtCmdFlrONOFF2] = CAN2_Buf[6];
		sRamDArry[ExtCmdFlrONOFF3] = CAN2_Buf[7];		

/*
        GetFlashDataToBufRam(F_BLOCK1);

        b_LdTmpBufRam(F_NonService0)    = CAN2_Buf[4];
        b_LdTmpBufRam(F_NonService1)    = CAN2_Buf[5];
        b_LdTmpBufRam(F_NonService2)    = CAN2_Buf[6];
        b_LdTmpBufRam(F_NonService3)    = CAN2_Buf[7];

        flash_write_DspChar(F_BLOCK1);
*/

    }    
    else if((CAN2_Buf[2] == (CMD_MORNING)) && (CAN2_Buf[3] == 0x00)){
		CmdFixFlrTime= CAN2_Buf[4];

/*
		SaveVerify=0x55;

        GetFlashDataToBufRam(F_BLOCK1);
        b_LdTmpBufRam(F_FixFloorTime)   = CAN2_Buf[4];
        flash_write_DspChar(F_BLOCK1);

		SaveVerify=0;
*/

    }    
}


