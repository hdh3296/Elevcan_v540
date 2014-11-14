


#include  "..\..\system_com\memory_map.h"
#include  "iomap.h"
#include  "COM.h"



extern void __attribute__((section(".usercode"))) HextoASCIIByte(void);


//#define  TEST_SIMULATION  	1
//#define  KTL  				1

#define DISABLE_INTERRUPTS 	asm("push SR \n bset SR,#7 \n bset SR,#6 \n	bclr	SR,#5")
#define ENABLE_INTERRUPTS	asm("pop SR")



#define	MAX_EIGHT_CAR	1


#define	RS485_FOR_CRT	1


//#define		CHINA			1


//#define		L_K_J			1


//#define		TEMP_PARK			1

//#define		TEMP_GUEN			1


//#define	SAMSUNG_FIRE	1

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
//outport

#define		SILK_FAN	0
#define		SILK_LIGHT	1
#define		SILK_BUZ	2
#define		SILK_BELL	3
#define		SILK_RST	4
#define		SILK_ERR	5
#define		SILK_HOP	6
#define		SILK_HCL	7
#define		SILK_OP		8
#define		SILK_CL		9
#define		SILK_S_OP	10
#define		SILK_S_CL	11
#define		SILK_BK2	12
#define		SILK_D_S	13
#define		SILK_GBR	14
#define		SILK_BK1	15
#define		SILK_UP	    16
#define		SILK_DN	    17
#define		SILK_P1	    18
#define		SILK_P2	    19
#define		SILK_P3	    20
#define		SILK_P4	    21
#define		SILK_DAC	22
#define		NO_USE_OUT  23


//inport
#define		SILK_EMG	0
#define		SILK_PRK	1
#define		SILK_AUTO	2
#define		SILK_U_B	3
#define		SILK_D_B	4
#define		SILK_OLS	5
#define		SILK_GS		6
#define		SILK_DS		7

#define		SILK_SU1	8
#define		SILK_SD1	9
#define		SILK_SFT	10
#define		SILK_OVL	11
#define		SILK_ULS	12
#define		SILK_DLS	13
#define		SILK_LU		14
#define		SILK_LD		15

#define		SILK_GR		16
#define		SILK_BAT	17
#define		SILK_PASS	18
#define		SILK_FIRE	19
#define		SILK_WATER	20
#define		SILK_FULL	21
//#define		SILK_EX1	22
#define		SILK_MM	    22
#define		SILK_FHM	23

#define		SILK_FR1	24
#define		SILK_FR2	25
#define		SILK_GS2	26
#define		SILK_DS2	27
#define		SILK_SU2	28
#define		SILK_SD2	29
//#define		SILK_SU3	30
#define		SILK_BM	    30
//#define		SILK_SD3	31
#define		SILK_INV	31

#define		SILK_X0		32
#define		SILK_X1		33
#define		SILK_X2		34
#define		SILK_X3		35
#define		SILK_X4		36
#define		SILK_X5		37
#define		SILK_X6		38
#define		SILK_X7		39

#define		SILK_FS0	40
#define		SILK_FS1	41
#define		SILK_FS2	42
#define		SILK_FS3	43
#define		SILK_FS4	44
#define		SILK_DER	45
#define		SILK_FID	46
#define		SILK_UND	47

#define		EXT_EX0	48
#define		EXT_EX1	49
#define		EXT_EX2	50
#define		EXT_EX3	51


#define		NO_USE_IN   52
////////////////////////////////////////////
////////////////////////////////////////////


#define  CUR_PULSE              32
#define  BEF_CUR_PULSE          33
#define  METER_PER_MIN          34
#define  CUR_METER_PER_MIN      35
#define  TOTAL_PULSE            36
#define  STOP_MINIMUM_PULSE     37
#define  DECREASE_PULSE         38
#define  TMP_FHM_COUNTER1       39
#define  TMP_FHM_COUNTER2       40
#define  TMP_MM_PER_MIN         41
#define  PULSE_PER_100MSEC      42
#define  CUR_RPM                43
#define  START_PULSE            44
#define  MOVE_COUNTER           45
#define  END_RAM_LONG           46
#define  MAX_LONG_BUF           END_RAM_LONG







                                            
#define     L_CMD               	0
#define	    L_GROUP_ID        		1
#define	    L_LOG_ADR         		2
#define	    L_ABS_ADR         		3
#define	    L_BASE_MEMORY     		4
#define	    L_OFFSET_MEMORY   		5
#define	    L_DATA_CNT        		6
#define	    L_SAVE_DATA       		7
              

#define	    C_CMD       			0
#define	    C_CMDTYPE      		    1
#define	    C_BASE_MEMORY     		2
#define	    C_OFFSET_MEMORY   		3
#define	    C_DATA_CNT        		4
#define	    C_SAVE_DATA       		5
			
                
#define	    ERR_DSP_TIME      		10

                                             

//#define	    OPEN_AND_WAIT_TIME_YOU  	40
//#define     OPEN_TOTAL_TIME_you     70
//#define	    CLOSE_TOTAL_TIME  		70
//#define	    REOPEN_CHK_TIME   		3

#define	    BASE_NEXT_FLR_TIME 		200
#define	    RELEVEL_TIME            160  //80 
				
//#define	    Manual_Door 			1





#ifndef	BIT_STR
#define	BIT_STR	1
typedef struct _bit_struct
{
    unsigned bit0 : 1;
    unsigned bit1 : 1;
    unsigned bit2 : 1;
    unsigned bit3 : 1;
    unsigned bit4 : 1;
    unsigned bit5 : 1;
    unsigned bit6 : 1;
    unsigned bit7 : 1;
}bit_field;



typedef  union  _long_union
{
    unsigned char byte[4];
    unsigned int  intger[2];
    unsigned long long_data; 
}long_field;


#endif


#define GET_BITFIELD(addr)              (*((volatile bit_field*) (addr)))
#define GET_LONGFIELD(addr)             (*((volatile long_field*) (addr)))

#define GET_LONGFIELD_BYTE0(addr)       (*((volatile long_field*) (addr))).byte[0]
#define GET_LONGFIELD_BYTE1(addr)       (*((volatile long_field*) (addr))).byte[1]
#define GET_LONGFIELD_BYTE2(addr)       (*((volatile long_field*) (addr))).byte[2]
#define GET_LONGFIELD_BYTE3(addr)       (*((volatile long_field*) (addr))).byte[3]

        


#define NO_FIRE             0
#define FIRE_START          1
#define FIRE_ONE            2
#define FIRE_TWO            3
#define FIRE_THREE          4


#define  DOOR_OPEN_START      0
#define  DOOR_OPEN_CHECK      1
#define  DOOR_OPEN_WAIT       2          
#define  DOOR_REOPEN_CHECK    3          
#define  DOOR_CLOSE_START     4                  
#define  DOOR_CLOSE_CHECK     5                  
#define  DOOR_CLOSE_END       6  
#define  READY_ELEVATOR       7  
#define  MOVE_ELEVATOR        8  
#define  WAIT_NEXT_LULD       9
#define  WAIT_LULD            10
#define  STOP_ELEVATOR        11



#define  sINSPECT 			  0 
#define  sInvertErr			  1                             
#define  sI_C_N_FLR           2
#define  sEMERGENCY           3
#define  sLOPE_BRK            4
#define  sMOTOR_OVERHEAT      5
#define  sSLIP                6
#define  sULS                 7
#define  sDLS                 8
#define  sLULD_NO_OFF         9
#define  sNEXT_FLOOR          10
#define  sInPortError         11
#define  sHDS_RUN_OFF         12
#define  sCLE_RUN_OFF         13
#define  sRelevelError        14
/////////////////////////////////////
#define  sEncoderErr          15
#define  sEncoderABErr        16 
#define  sSpeedSetError       17 
#define  sSpeedPortError      18 
#define  sNoUseSpeed          19 
#define  sMinLengthErr        20 
#define  sEqualFloorError     21 
#define  sSystemErr           22
#define  sBreakMgtOpen        23  
#define  sBreakOpen           24  
#define  sSusErr              25  
#define  sSdsErr              26  
//////////////////////////////////
#define  sLuOrLdErr0          27  
#define  sLuOrLdErr1          28  
#define  sLuOrLdErr2          29  
#define  sLuOrLdErr3          30  
#define  sLuOrLdErr4          31  
#define  sLuOrLdErr5          32  
#define  sCarDoor_Jumper      33
#define  sHoleDoor_Jumper     34
#define  sCarHoleDoor_Jumper  35

/////////////////////////////////////
#define  sFhmError            43
//////////////////////////////////////
#define  sHDS_NO_ON           44
#define  sCLE_NO_ON           45
#define  sOVL                 46 
#define  sPARKING             47   
#define  sFireOn              48         
#define  sWaterSense          49         
#define  sOPE_NO_ON           50                                                                            
#define  sVIP                 51
#define  sFHM_MODE			  52
#define  sMANUAL_UP           53         
#define  sMANUAL_DN           54         
#define  sMANUAL              55         
#define  sSFT                 56
#define  sOPEN                57
#define  sCLOSE               58         
#define  sUP                  59         
#define  sDN                  60         
#define  sSLOW_SPEED          61         
#define  sWAIT_LULD           62         
#define  sSTOP                63        
#define  sHOME                64         
#define  sREADY               65
         


/////////////////////////block0////////////////////////////////////

#define  F_BLOCK0               0
#define  F_FlrDspCh             F_BLOCK0      // 0    0-15

/////////////////////////block1////////////////////////////////////
//floor group
#define  F_BLOCK1               64
#define  F_TopFlr               F_BLOCK1               //1     16
#define  F_PrkFlr               65                     //1
#define  F_FixFloor             66                     //1
#define  F_FireSafeFlr          67                     //1

#define  F_X7SafeFlr            68                     //1     17                           
#define  F_WaterSafeFlr         69                     //1     
#define  F_StartFloor           70                     //1     
#define  F_OneStopFlr           71                     //1

#define  F_KidsKeyCnt           72                     //1
#define  F_X6SafeFlr            73                     //1     17                           
#define  F_X5SafeFlr         	74                     //1     


/*
#define  F_SubDoorFlr1          72                     //1     
#define  F_SubDoorFlr2          73                     //1
#define  F_SubDoorFlr3          74                     //1      18
#define  F_SubDoorFlr4          75                     //1  

#define  F_SubDoorFlr5          76                     //1  
#define  F_SubDoorFlr6          77                     //1                                    
#define  F_SubDoorFlr7          78                     //1      19
#define  F_SubDoorFlr8          79                     //1
*/


//timer group
#define  F_OpWtTm               80                     //1      20
#define  F_OpTtTm               81                     //1
#define  F_FixFloorTime         82                     //1
#define  F_NextFlrTime          83                     //1     

#define  F_LuLdOffTime          84                     //1      21
#define  F_FanTime              85                     //1
#define  F_LightTime            86                     //1
#define  F_OpClWaitTime         87                     //1


#define  F_DrJmpChkTime         88                     //1
#define  F_DirTime              89                     //1      22
#define  F_VoiceTime            90                     //1
#define  F_BrkMgtTime           91                     //1
  
#define  F_ReOpTime             92                     //1  
#define  F_StTm1                93                     //1
#define  F_StTm2                94                     //1      23
#define  F_StTm3                95                     //1

#define  F_StTm4                96                     //1  
#define  F_StTm5                97                     //1

#define  F_RunOffTime           98                     //1
#define  F_Bk1OffTime           99                     //1
#define  F_Bk2OffTime           100                     //1
#define  F_UDOffTime            101                     //1
#define  F_P4OffTime            102                     //1

#define  F_SolOnTime            103           			//1
#define  F_DoorWaitTime         104            			//1


//#define  F_BrkStTm11            98                     //1(2)   24
//#define  F_BrkStTm10            99                     //1(2)
//#define  F_BrkStTm21            100                    //1(2)  
//#define  F_BrkStTm20            101                    //1(3)
//#define  F_BrkStTm31            102                    //1(2)   25
//#define  F_BrkStTm30            103                    //1(2)

//#define  F_BrkStTm41            104                    //1(2)  
////#define  F_BrkStTm40            105                    //1(3)
//#define  F_BrkStTm51            106                    //1(2)  26
//#define  F_BrkStTm50            107                    //1(2)


//OnOff group
#define  F_NonService0          108                     //1     27    
#define  F_NonService1          109                     //1     
#define  F_NonService2          110                     //1     
#define  F_NonService3          111                     //1   

#define  F_OnOff0               112                     //1     28
#define  F_OnOff1               113                     //1
#define  F_OnOff2               114                     //1
#define  F_OnOff3               115                     //1

#define  F_NcNoBit0             116                     //1     29
#define  F_NcNoBit1             117                     //1
#define  F_NcNoBit2             118                     //1    
#define  F_NcNoBit3             119                     //1

#define  F_NcNoBit4             120                     //1     30
#define  F_NcNoBit5             121                     //1
#define  F_NcNoBit6             122                     //1
#define  F_NcNoBit7             123                     //1

#define  F_NcNoBit8             124                     //1     31
#define  F_Not_Use3             125                     //1
#define  F_Not_Use2             126                     //1
#define  F_Not_Use1             127                     //1

                    
//encoder
//light
//odd add
/////////////////////////block2////////////////////////////////////
//i/o group                                             
#define  F_BLOCK2               128
#define  F_ManualSpeed          F_BLOCK2                //1    32
#define  F_BatterySpeed         129                     //1    
#define  F_DecreaseSpeed        130                     //1    
#define  F_FhmSpeed             131                     //1    

#define  F_Speed30              132                     //1    
#define  F_Speed45              133                     //1    
#define  F_Speed60              134                     //1    34
#define  F_Speed90              135                     //1    

#define  F_Speed105             136                     //1    
#define  F_Speed120             137                     //1    
#define  F_Speed150             138                     //1    35
#define  F_Speed180             139                     //1    

#define  F_Speed210             140                     //1    
#define  F_Etc1Speed            141                     //1    33
#define  F_Etc2Speed            142                     //1    
#define  F_ElevSpeed            143                     //1     


#define  F_LimitSpeed           144                     //1    36
#define  F_Su1Sd1_Velocity      145                     //1    36
#define  F_Su2Sd2_Velocity      146                     //1     
#define  F_X0X1_Velocity        147                     //1     

#define  NC_IO2                 148                     //1    37
#define  NC_IO3                 149                     //1     
#define  NC_IO4                 150                     //1     
#define  NC_IO5                 151                     //1     


//user group
#define  F_Ver0                 152                     //1    38
#define  F_Ver1                 153                     //1
#define  F_Ver2                 154                     //1
#define  F_Bd_Id                155                     //1

#define  F_Passward0            156                     //1    39
#define  F_Passward1            157                     //1
#define  F_Passward2            158                     //1
#define  F_Passward3            159                     //1

#define  F_UserLamp1            160                     //1    
#define  F_UserLamp2            161                     //1     
#define  F_SerialNm11           162                     //1(2) 40
#define  F_SerialNm10           163                     //1(2)

#define  F_NormalDsp            164                     //1    41
#define  F_GroupNm              165                     //1    41
#define  F_LocalNm              166                     //1    41
#define  F_PcbType              167                     //1    41

#define  F_EncoderRate          168                     //1    41
#define  F_StopPulse0           169                     //1    41
#define  F_user5                170                     //1    41
#define  F_user6                171                     //1    41
#define  F_year                 172                     //1    41
#define  F_month                173                     //1    41
#define  F_day                  174                     //1    41

#define  F_ErrStopCnt           175                     //1 
#define  F_Company              176                     //1     
#define  F_Airconadr            177						//

#define  F_UserLamp3            178						//
#define  F_UserLamp4            179						//

////////////////////////////////////////////////////////////////////
//blanck        42-47(168-191)
/////////////////////////////////////////////////////////////////////


/////////////////////////block3///////////////////////////////////
//wait   group
#define  F_BLOCK3               192
#define  F_0506                 F_BLOCK3                //1     48
#define  F_0607                 193                     //1     
#define  F_0708                 194                     //1     
#define  F_0809                 195                     //1     

#define  F_0910                 196                     //1     49
#define  F_1011                 197                     //1     
#define  F_1112                 198                     //1     
#define  F_1213                 199                     //1     

#define  F_1314                 200                     //1     50
#define  F_1415                 201                     //1     
#define  F_1516                 202                     //1     
#define  F_1617                 203                     //1     

#define  F_1718                 204                     //1     51
#define  F_1819                 205                     //1     
#define  F_1920                 206                     //1     
#define  F_2021                 207                     //1     

#define  F_2105                 208                     //1     52
#define  F_0002                 209                     //1     
#define  F_0003                 210                     //1     
#define  F_0004                 211                     //1     

#define  F_0005                 212                     //1     53
#define  F_0006                 213                     //1     
#define  F_0007                 214                     //1     
#define  F_0008                 215                     //1     


#define  F_0009                 216                     //1     54
#define  F_0010                 217                     //1     
#define  F_0011                 218                     //1     
#define  F_0012                 219                     //1     


#define  F_0013                 220                     //1     55
#define  F_0014                 221                     //1     
#define  F_ParkingStart         222                     //1     
#define  F_ParkingEnd           223                     //1     


////////////////////////////////////////////////////////////////////
//blanck        54-63
/////////////////////////////////////////////////////////////////////



/////////////////////////block4///////////////////////////////////                                                                                                            
/////////////////////////4 * 64///////////////////////////////////
#define  F_BLOCK4               256
#define  EMG_PORT               F_BLOCK4    //1     1       64
#define  PRK_PORT               257         //1     
#define  AUTO_PORT              258         //1    
#define  U_B_PORT               259         //1
     
#define  D_B_PORT               260         //1     2
#define  OLS_PORT               261         //1     
#define  GS_PORT                262         //1     
#define  DS_PORT                263         //1     

#define  SU1_PORT               264         //1     3
#define  SD1_PORT               265         //1     
#define  SFT_PORT               266         //1     
#define  OVL_PORT               267         //1     

#define  ULS_PORT               268         //1     4
#define  DLS_PORT               269         //1     
#define  LU_PORT                270         //1     
#define  LD_PORT                271         //1     

#define  RG_PORT                272         //1     5
#define  BAT_PORT               273         //1     
#define  PASS_PORT              274         //1     
#define  FIRE_PORT              275         //1     

#define  WATER_PORT             276         //1     6
#define  FULL_PORT              277         //1     
//#define  EX1_PORT               278         //1     
#define  MM_PORT               278         //1     
#define  FHM_PORT               279         //1     

#define  FR1_PORT               280         //1     7
#define  FR2_PORT               281         //1     
#define  GS2_PORT               282         //1     
#define  DS2_PORT               283         //1     

#define  SU2_PORT               284         //1     8
#define  SD2_PORT               285         //1     
#define  BM_PORT               286         //1     
#define  INV_PORT               287         //1     

#define  X0_PORT                288         //1     9
#define  X1_PORT                289         //1     
#define  X2_PORT                290         //1     
#define  X3_PORT                291         //1     

#define  X4_PORT                292         //1     10
#define  X5_PORT                293         //1     
#define  X6_PORT                294         //1     
#define  X7_PORT                295         //1     

#define  FS0_PORT               296         //1     11
#define  FS1_PORT               297         //1     
#define  FS2_PORT               298         //1     
#define  FS3_PORT               299         //1     

#define  FS4_PORT               300         //1     12
#define  DER_PORT               301         //1     
#define  FID_PORT               302         //1     
#define  UND_PORT               303         //1     

#define  F_SubDoorFlr1          304         //1     
#define  F_SubDoorFlr2          305         //1
#define  F_SubDoorFlr3          306         //1      13
#define  F_SubDoorFlr4          307         //1  

#define  F_SubDoorFlr5          308         //1  
#define  F_SubDoorFlr6          309         //1                                    
#define  F_SubDoorFlr7          310         //1      14
#define  F_SubDoorFlr8          311         //1


/////////////////out port///////////////////////////    
/////////////////////////block5///////////////////////////////////                                                                                                            
/////////////////////////5 * 64///////////////////////////////////
#define  F_BLOCK5               320
#define  FAN_PORT               F_BLOCK5    //1     
#define  LIT_PORT               321         //1     
#define  BUZ_PORT               322         //1     
#define  BELL_PORT              323         //1
     
#define  RST_PORT               324         //1     
#define  ERR_PORT               325         //1     
#define  HOP_PORT               326         //1     
#define  HCL_PORT               327         //1     3

#define  OP_PORT                328         //1     
#define  CL_PORT                329         //1     
#define  S_OP_PORT              330         //1     
#define  S_CL_PORT              331         //1     

#define  BK2_PORT               332         //1
#define  D_S_PORT               333         //1     
#define  GBR_PORT               334         //1     
#define  BK1_PORT               335         //1     

#define  UP_PORT	            336
#define	 DN_PORT	            337
#define	 P1_PORT	            338
#define	 P2_PORT	            339

#define	 P3_PORT	            340
#define	 P4_PORT	            341
#define	 DAC_PORT	            342


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////




//#define  BASE_1                 (256/64) * 16    
#define  BASE_1                 96    

/////////////////////////block6,7///////////////////////////////////
#define  ENCODER_PULSE          BASE_1+ 0 
#define  MPM                    BASE_1+ 1 
#define  RPM                    BASE_1+ 2
#define  DEC_LENGTH_30          BASE_1+ 3 
#define  DEC_LENGTH_45          BASE_1+ 4 
#define  DEC_LENGTH_60          BASE_1+ 5 
#define  DEC_LENGTH_90          BASE_1+ 6  
#define  DEC_LENGTH_105         BASE_1+ 7  
#define  DEC_LENGTH_120         BASE_1+ 8
#define  DEC_LENGTH_150         BASE_1+ 9 
#define  DEC_LENGTH_180         BASE_1+ 10 
#define  DEC_LENGTH_210         BASE_1+ 11
#define  DEC_PULSE_30           BASE_1+ 12
#define  DEC_PULSE_45           BASE_1+ 13
#define  DEC_PULSE_60           BASE_1+ 14
#define  DEC_PULSE_90           BASE_1+ 15
#define  DEC_PULSE_105          BASE_1+ 16
#define  DEC_PULSE_120          BASE_1+ 17
#define  DEC_PULSE_150          BASE_1+ 18
#define  DEC_PULSE_180          BASE_1+ 19
#define  DEC_PULSE_210          BASE_1+ 20
#define  MIN_DEC_PULSE_30       BASE_1+ 21
#define  MIN_DEC_PULSE_45       BASE_1+ 22
#define  MIN_DEC_PULSE_60       BASE_1+ 23
#define  MIN_DEC_PULSE_90       BASE_1+ 24
#define  MIN_DEC_PULSE_105      BASE_1+ 25
#define  MIN_DEC_PULSE_120      BASE_1+ 26
#define  MIN_DEC_PULSE_150      BASE_1+ 27 
#define  MIN_DEC_PULSE_180      BASE_1+ 28 
#define  MIN_DEC_PULSE_210      BASE_1+ 29 
#define  MPM_VARIABLE           BASE_1+ 30 
#define  MM_PULSE               BASE_1+ 31 

//#define  PULSE_BASE             ENCODER_PULSE



/////////////////////////block8,9///////////////////////////////////

#define  FLR_01_PULSE           BASE_1+ 32
#define  FLR_02_PULSE           BASE_1+ 33 
#define  FLR_03_PULSE           BASE_1+ 34 
#define  FLR_04_PULSE           BASE_1+ 35 
#define  FLR_05_PULSE           BASE_1+ 36 
#define  FLR_06_PULSE           BASE_1+ 37 
#define  FLR_07_PULSE           BASE_1+ 38 
#define  FLR_08_PULSE           BASE_1+ 39 
#define  FLR_09_PULSE           BASE_1+ 40 
#define  FLR_10_PULSE           BASE_1+ 41 
#define  FLR_11_PULSE           BASE_1+ 42 
#define  FLR_12_PULSE           BASE_1+ 43 
#define  FLR_13_PULSE           BASE_1+ 44 
#define  FLR_14_PULSE           BASE_1+ 45 
#define  FLR_15_PULSE           BASE_1+ 46 
#define  FLR_16_PULSE           BASE_1+ 47 
#define  FLR_17_PULSE           BASE_1+ 48 
#define  FLR_18_PULSE           BASE_1+ 49 
#define  FLR_19_PULSE           BASE_1+ 50 
#define  FLR_20_PULSE           BASE_1+ 51 
#define  FLR_21_PULSE           BASE_1+ 52 
#define  FLR_22_PULSE           BASE_1+ 53 
#define  FLR_23_PULSE           BASE_1+ 54 
#define  FLR_24_PULSE           BASE_1+ 55 
#define  FLR_25_PULSE           BASE_1+ 56 
#define  FLR_26_PULSE           BASE_1+ 57 
#define  FLR_27_PULSE           BASE_1+ 58 
#define  FLR_28_PULSE           BASE_1+ 59 
#define  FLR_29_PULSE           BASE_1+ 60 
#define  FLR_30_PULSE           BASE_1+ 61 
#define  FLR_31_PULSE           BASE_1+ 62 
#define  FLR_32_PULSE           BASE_1+ 63 




#define  BASE_ADDR              0
#define  O_eVer                 BASE_ADDR                       
#define  O_eTopFlr              3           //O_eVer+3                    
#define  O_ePrkFlr              4           //O_eTopFlr+1                 
#define  O_eOpWtTm              5           //O_ePrkFlr+1                 
#define  O_eOpTtTm              6           //O_eOpWtTm+1                 
#define  O_eUserLamp            7           //O_eOpTtTm+1                 
#define  O_eFixFloor            8           //O_eUserLamp+1               
#define  O_eFixFloorTime        9           //O_eFixFloor+1                
#define  O_eNonService0         10          //O_eFixFloorTime+1                
#define  O_eNonService1         11          //O_eFixFloorTime+1                
#define  O_eNonService2         12          //O_eFixFloorTime+1                
#define  O_eNonService3         13          //O_eFixFloorTime+1                
#define  O_eFlrDspCh            14          //O_eNonService+4            
#define  O_eSysErCnt            78          //O_eFlrDspCh+64             
#define  O_ePassward            162         //O_eSysErCnt+ERR_SAVE_SIZE 
#define  O_eMvCounter           166         //O_ePassward+4            
#define  O_eSerialNm            168         //O_eMvCounter+2            
#define  O_eFireSafeFlr         170         //O_eSerialNm+2             
#define  O_eSubDoorFlr1         171         //O_eFireSafeFlr+1          
#define  O_eSubDoorFlr2         172         //O_eSubDoorFlr1+1          
#define  O_eSubDoorFlr3         173         //O_eSubDoorFlr2+1          
#define  O_eErrStopCnt          174         //O_eSubDoorFlr3+1          
#define  O_eErrCntPt            175         //O_eErrStopCnt+1           
#define  O_eNextFlrTime         176         //O_eErrCntPt+1             
#define  O_eLuLdOffTime         177         //O_eNextFlrTime+1            
#define  O_eNcNoBit             178         //O_eLuLdOffTime+1          
#define  O_eEnd                 179         //O_eNcNoBit+4              




#define  SAVE_CUR_PULSE         96




/**/
#define  MAX_AIRCON_BUF         80
#define  AIRCON_CMD_BUF         MAX_AIRCON_BUF-8

extern	unsigned char 	AirconBuf[MAX_AIRCON_BUF];
extern  unsigned int	AirConDataRcvPt;
extern	unsigned int 	AirConRcvTimer;

extern  UserDataType  YourKey0[4];
extern  UserDataType  YourKey1[4];
extern  UserDataType  YourKey2[4];
extern  UserDataType  YourKey3[4];

extern	UserDataType  HibSet[10];



extern  UserDataType    RxBuffer[MAX_RTX_BUF];
extern  UserDataType    RcvBuf[MAX_SAVE_BUF];
extern  UserDataType    RxStatus;
extern  UserDataType    RxCurCnt;
extern  UserDataType    SerialTime;
extern  UserDataType    Chksum;

extern  UserDataType    RxBuffer2[MAX_RTX_BUF];
extern  UserDataType    RcvBuf2[MAX_SAVE_BUF];
extern  UserDataType    RxStatus2;
extern  UserDataType    RxCurCnt2;
extern  UserDataType    SerialTime2;
extern  UserDataType    Chksum2;


extern  UserDataType    errbd[12];
extern  UserDataType    Olderrbd[12];
extern  UserDataType    LadderBuf[16];                         
extern  UserDataType    LadderData[16];                           
extern  UserDataType    sRamDArry[END_SRAM];     
extern  UserDataType    BdErrCntSeq[ABS_ADDRESS];
extern  UserDataType    BDid[ABS_ADDRESS];
extern  UserDataType    eDArry[E_END];      
extern  UserDataType    New485Ladder[40];      



extern  UserDataType    Cancle;
extern  UserDataType    BefRcvAdr;
extern  UserDataType    CurRcvAdr;
extern  UserDataType    LogAddress;
extern  UserDataType    AbsAddress;
extern  UserDataType    LogAddressLoop;
extern  UserDataType    TimeOutBd;
extern  UserDataType    src;
extern  UserDataType    firstdata;
extern  UserDataType    seconddata;
extern  UserDataType    Bef_I_EMG;
extern  UserDataType    Bef_I_FS0;
extern  UserDataType    Bef_I_GR;
extern  UserDataType    Bef_I_SU1;
extern  UserDataType    Bef_I_X_0;
extern  UserDataType    Bef_I_FIRE;
extern  UserDataType    I_EMG_Cht;
extern  UserDataType    I_FS0_Cht;
extern  UserDataType    I_GR_Cht;
extern  UserDataType    I_SU1_Cht;
extern  UserDataType    I_X_0_Cht;
extern  UserDataType    I_FIRE_Cht;
extern  UserDataType    NoCloseCnt;
extern  UserDataType    errpt;
extern  UserDataType    ErrBdNamePt;
extern  UserDataType    BefErrBdNamePt;
extern  UserDataType    eMvCounterCnt;
extern  UserDataType    OpenOutOffTime;        
extern  UserDataType    CloseOutOffTime;        
extern  UserDataType    VoiceTime;        
extern  UserDataType    FhmLoaderTime;        
extern	UserDataType    AccTimer;        

extern  UserDataType    RstTime;        
extern  UserDataType    UpBttonTime;
extern  UserDataType    DnBttonTime;
extern  UserDataType    DoorCloseTime;
extern  UserDataType    DoorOpenOnTime;
extern  UserDataType    DoorCloseOnTime;
extern  UserDataType    msec10;
extern  UserDataType    sec1;

extern  UserDataType    EepTime;
extern  UserDataType    FanTime; 
extern  UserDataType    ManualStopTime;  
extern  UserDataType    WarmingUpTime; 
extern  UserDataType    FixFlrTimeCnt; 
extern  UserDataType    errtime;
extern  UserDataType    FhmTime;
extern  UserDataType    CurFTime;
extern  UserDataType    NextFTime;
extern  UserDataType    RestartTime;
extern  UserDataType    ExtCmdFlrONOFFCnt;
//extern  UserDataType    SerialLoopMaxTime;
extern  UserDataType    LadderTime;
extern  UserDataType    Runtime;
extern  UserDataType    FireBaseFloor;
extern  UserDataType    CurSpeed;
extern  UserDataType    OriginalHighFlr;
extern  UserDataType    OriginalLowFlr;
extern  UserDataType    OriginalDoor;
extern  UserDataType    OriginalStartFloor;
extern  UserDataType    UseBaseTime;
extern  UserDataType    ElevStopTime;
extern  UserDataType    ElevMoveTime;
extern  UserDataType    PowerOnTime;
extern  UserDataType    NewDoorSelect;
extern  UserDataType    CurDoorSelect;
extern  UserDataType    SaveMoveCounter;
extern  UserDataType    LoopTime;
extern	UserDataType    SaveVerify;
extern	UserDataType    EncoderReloadTime;     


extern  unsigned	int    	    NextFloorTime;
extern  unsigned	int     	MinuteTime;
extern  unsigned	int   	    LuLdTime;
extern  unsigned	int   	    CounterTime;
extern  unsigned	int   	    CounterChkTime;
extern  unsigned	int    	    DoorOpenTime;
extern  unsigned	int    	    LightTime;
extern  unsigned	int    	    AutoNoMoveTime;
extern	unsigned	int    	    ExIOTimer;

extern	unsigned	int    	    BreakTime;


extern  unsigned int   CAN_Buf[8];
extern  unsigned int   CAN2_Buf[8];



extern  UserDataType    OldFireBuf;  
extern  UserDataType    AutoBit;
extern  UserDataType    EmerBit;
extern  UserDataType    SlipBit;
extern  UserDataType    LuLdBit;
extern  UserDataType    OpenEndBit;
extern  UserDataType    BefDlsBit;
extern  UserDataType    BefDestFBit;
extern  UserDataType    EepRWBit;
extern  UserDataType    Etc1Bit;
extern  UserDataType    Etc2Bit;
extern  UserDataType    Etc3Bit;
extern  UserDataType    PC1Bit;
extern  UserDataType    StateBit0;
extern  UserDataType    StateBit1;   
extern  UserDataType    StateBit2;   
extern	UserDataType    StateBit3;   
extern	UserDataType    StateBit4;   
extern	UserDataType    StateBit5;   

extern  UserDataType    Vip_Floor;   


extern  UserDataType    S0_STATE_bit;
extern  UserDataType    S1_STATE_bit;
extern  UserDataType    S2_STATE_bit;
extern  UserDataType    S3_STATE_bit;
extern  UserDataType    S4_STATE_bit;

extern  UserDataType    I_SU1_bit;
extern  UserDataType    I_EMG_bit;
extern  UserDataType    I_GR_bit;
extern  UserDataType    I_FIRE_bit;
extern  UserDataType    I_FS0_bit;
extern  UserDataType    I_X0_bit;
extern  UserDataType    O_OP_bit;
extern  UserDataType    O_U_W_bit;
extern  UserDataType    O_Y_0_bit;
extern  UserDataType    DoorStatus_bit;
extern  UserDataType    FhmToggle;
extern  UserDataType    FhmSeq;
extern  UserDataType    PowerFailTime;
extern  UserDataType    CarOnceStopTime;
extern  UserDataType    MyGroupAddr;
extern  UserDataType    MyLocalAddr;

extern  UserDataType    SegData0;
extern  UserDataType    SegData1;
extern  UserDataType    SegData2;
extern  UserDataType    SegSel;

extern  UserDataType    LadderTime;
extern  UserDataType    SegError;


extern  UserDataType   SelMainCarTime;
extern  UserDataType   SelSubCarTime;
extern  UserDataType   LadderKeyTime;

extern  UserDataType	SrcAdrBlk;
extern  UserDataType	LoaderChk;

extern	UserDataType    CrtMoveFlr;


extern  unsigned int   TxPercent;
extern  unsigned int   Percent;
extern  unsigned int   ThisReceiveSlave;



extern  unsigned long 	BefCurEncoderPulse;
extern  unsigned long   TmpEncoderPulse;
extern	unsigned long 	LevelEncoderPulse1,LevelEncoderPulse2;
extern	unsigned long 	TestPulse1,UpDnEncoder;



extern	UserDataType    SerialLoopMaxTime;
extern	UserDataType    ClrCnt;

extern	UserDataType    TmpBuzor;   
extern	UserDataType    ExtKeyCnt;

extern	UserDataType    NotRecoveryData;     
extern	UserDataType    CmdFixFlrTime;




extern unsigned long  parameter_mirror[MAX_LONG_BUF]; // __attribute__((aligned(MAX_LONG_BUF),far,section(".ram,r")));


//extern long_field  FlashBuf[128]           __attribute__((aligned(128),section(".auto_psv,r")));
extern long_field  FlashDspCharBuf[256]    __attribute__((aligned(256) ,section(".auto_psv,r")));

extern const unsigned char DftFlrName[]; 
extern const unsigned char StatusMessage[][16];
extern const unsigned int EncRate[];


//////

#define  S1_OPEN1               GET_BITFIELD(&S1_STATE_bit).bit0
#define  S1_CLOSE1              GET_BITFIELD(&S1_STATE_bit).bit1
#define  S1_OVERLOAD1           GET_BITFIELD(&S1_STATE_bit).bit2
#define  S1_EMG1                GET_BITFIELD(&S1_STATE_bit).bit3
#define  S1_POWER_FAIL          GET_BITFIELD(&S1_STATE_bit).bit4
#define  S1_AUTO1               GET_BITFIELD(&S1_STATE_bit).bit5
#define  S1_MANUAL1             GET_BITFIELD(&S1_STATE_bit).bit6
#define  S1_UP1                 GET_BITFIELD(&S1_STATE_bit).bit7

#define  S2_DN1                 GET_BITFIELD(&S2_STATE_bit).bit0
#define  S2_CAR_MOVE1           GET_BITFIELD(&S2_STATE_bit).bit1
#define  S2_EXT_BUT_CLR1        GET_BITFIELD(&S2_STATE_bit).bit2
#define  S2_FLOW1               GET_BITFIELD(&S2_STATE_bit).bit3
#define  S2_FIRE1               GET_BITFIELD(&S2_STATE_bit).bit4
#define  S2_CAR_BUT_CLR1        GET_BITFIELD(&S2_STATE_bit).bit5
#define  S2_REOPEN1             GET_BITFIELD(&S2_STATE_bit).bit6
#define  S2_LAMP_USER1          GET_BITFIELD(&S2_STATE_bit).bit7



#define  S3_VIP1                GET_BITFIELD(&S3_STATE_bit).bit0
#define  S3_PARKING1            GET_BITFIELD(&S3_STATE_bit).bit1
#define  S3_SHIFT1              GET_BITFIELD(&S3_STATE_bit).bit2
#define  S3_UPDN_VO1            GET_BITFIELD(&S3_STATE_bit).bit3
#define  S3_OPEN_SUB1           GET_BITFIELD(&S3_STATE_bit).bit4
#define  S3_FULL1               GET_BITFIELD(&S3_STATE_bit).bit5
#define  S3_CUR_KEY1            GET_BITFIELD(&S3_STATE_bit).bit6
#define  S3_STOP1               GET_BITFIELD(&S3_STATE_bit).bit7



#define  S4_CAR_MOST_SERVICE1    GET_BITFIELD(&S4_STATE_bit).bit0
#define  S4_FAMILY_SERVICE1      GET_BITFIELD(&S4_STATE_bit).bit1
//#define  S4_ARRIVE1      		 GET_BITFIELD(&S4_STATE_bit).bit2
#define  S4_WAIT_FLR_SERVICE1    GET_BITFIELD(&S4_STATE_bit).bit3
#define  S4_PARKING_READY1    	 GET_BITFIELD(&S4_STATE_bit).bit4
#define  S4_USERLAMP3    	 	 GET_BITFIELD(&S4_STATE_bit).bit5
#define  S4_USERLAMP4    	 	 GET_BITFIELD(&S4_STATE_bit).bit6



#define  bAuto         		    GET_BITFIELD(&AutoBit).bit0 
#define  bMoveOk           	    GET_BITFIELD(&AutoBit).bit1
#define  bMoveUpOk         	    GET_BITFIELD(&AutoBit).bit2 
#define  bMoveDnOk         	    GET_BITFIELD(&AutoBit).bit3 
#define  bMoveCar       	    GET_BITFIELD(&AutoBit).bit4
#define  bManualAuto    	    GET_BITFIELD(&AutoBit).bit5 
#define  bManualUpKey      	    GET_BITFIELD(&AutoBit).bit6 
#define  bManualDnKey      	    GET_BITFIELD(&AutoBit).bit7

#define  bsEmergency       	    GET_BITFIELD(&EmerBit).bit0 
#define  bOnLuLd        	    GET_BITFIELD(&EmerBit).bit1
#define  bsUls       		    GET_BITFIELD(&EmerBit).bit2 
#define  bsDls       		    GET_BITFIELD(&EmerBit).bit3 
#define  bHomeUpDn         	    GET_BITFIELD(&EmerBit).bit4
#define  bInspect         	    GET_BITFIELD(&EmerBit).bit5
#define  bExtButClr     	    GET_BITFIELD(&EmerBit).bit6 
#define  bCarButClr     	    GET_BITFIELD(&EmerBit).bit7

#define  bsSlip         	    GET_BITFIELD(&SlipBit).bit0 
#define  bVoiceReady      	    GET_BITFIELD(&SlipBit).bit1
#define  bCarUpDnChButClr       GET_BITFIELD(&SlipBit).bit2
#define  bsOpeNoOn         	    GET_BITFIELD(&SlipBit).bit3 
#define  bsLuLdNoOff       	    GET_BITFIELD(&SlipBit).bit4
#define  bsNextFloor    	    GET_BITFIELD(&SlipBit).bit5 
#define  bsHdsNoOn      	    GET_BITFIELD(&SlipBit).bit6 
#define  bsCleNoOn      	    GET_BITFIELD(&SlipBit).bit7

#define  bBefbRelevelErr        GET_BITFIELD(&LuLdBit).bit0 
#define  bsDestFloor       	    GET_BITFIELD(&LuLdBit).bit1
#define  bFindBoard     	    GET_BITFIELD(&LuLdBit).bit2 
#define  bReOpen        	    GET_BITFIELD(&LuLdBit).bit3 
#define  bUpWard           	    GET_BITFIELD(&LuLdBit).bit4
#define  bDnWard        	    GET_BITFIELD(&LuLdBit).bit5 
#define  bCarStop          	    GET_BITFIELD(&LuLdBit).bit6 
#define  bCarErr        	    GET_BITFIELD(&LuLdBit).bit7


#define  bCarStopNoRun     	    GET_BITFIELD(&OpenEndBit).bit0
#define  bTestKey       	    GET_BITFIELD(&OpenEndBit).bit1 
#define  bSlipCheckStart	    GET_BITFIELD(&OpenEndBit).bit2 
#define  bsLope         	    GET_BITFIELD(&OpenEndBit).bit3
#define  bBefbsEmergency   	    GET_BITFIELD(&OpenEndBit).bit4 
#define  bBefbsSlip     	    GET_BITFIELD(&OpenEndBit).bit5
#define  bCarDoorCloseEnd2   	GET_BITFIELD(&OpenEndBit).bit6 
#define  bHoleDoorCloseEnd2   	GET_BITFIELD(&OpenEndBit).bit7

 

#define  bBefbsDls      	    GET_BITFIELD(&BefDlsBit).bit0 
#define  bBefbsHdsRunOff   	    GET_BITFIELD(&BefDlsBit).bit1
#define  bBefbsCleRunOff   	    GET_BITFIELD(&BefDlsBit).bit2 
#define  bBefbsOpeNoOn     	    GET_BITFIELD(&BefDlsBit).bit3 
#define  bBefbsLuLdNoOff   	    GET_BITFIELD(&BefDlsBit).bit4
#define  bBefbsNextFloor   	    GET_BITFIELD(&BefDlsBit).bit5 
#define  bBefbsHdsNoOn     	    GET_BITFIELD(&BefDlsBit).bit6 
#define  bBefbsCleNoOn     	    GET_BITFIELD(&BefDlsBit).bit7

#define  bBefbsDestFloor   	    GET_BITFIELD(&BefDestFBit).bit0 
#define  bBefbsLuLdHome    	    GET_BITFIELD(&BefDestFBit).bit1
#define  bBefbsUls      	    GET_BITFIELD(&BefDestFBit).bit2
#define  bBefbsLope     	    GET_BITFIELD(&BefDestFBit).bit3
#define  bBefbTestTop      	    GET_BITFIELD(&BefDestFBit).bit4
#define  bBefbTestLow      	    GET_BITFIELD(&BefDestFBit).bit5
#define  bTempCall      	    GET_BITFIELD(&BefDestFBit).bit6
#define  bsInvCurNext      	    GET_BITFIELD(&BefDestFBit).bit7



#define  bBefbsInvCurNext  	    GET_BITFIELD(&EepRWBit).bit0
#define  bCarService         	GET_BITFIELD(&EepRWBit).bit1
#define  bD_F_FloorOn           GET_BITFIELD(&EepRWBit).bit2
#define  bDoorJumper            GET_BITFIELD(&EepRWBit).bit3
#define  bFhmRunReset           GET_BITFIELD(&EepRWBit).bit4
#define  bBefbPowerFail         GET_BITFIELD(&EepRWBit).bit5
#define  bManualStop      	    GET_BITFIELD(&EepRWBit).bit6
#define  bFhmRun         	    GET_BITFIELD(&EepRWBit).bit7

#define  bSearchHome       	    GET_BITFIELD(&Etc1Bit).bit0
#define  bCarUpMove             GET_BITFIELD(&Etc1Bit).bit1 
#define  bCarDnMove             GET_BITFIELD(&Etc1Bit).bit2 
#define  bFhmCount              GET_BITFIELD(&Etc1Bit).bit3 
#define  bSaveFlash             GET_BITFIELD(&Etc1Bit).bit4 
#define  bWaterSen              GET_BITFIELD(&Etc1Bit).bit5 
#define  bSubWayLight           GET_BITFIELD(&Etc1Bit).bit6 
#define  bCarOnceStop           GET_BITFIELD(&Etc1Bit).bit7 


#define  bEncoderErr            GET_BITFIELD(&Etc3Bit).bit0 
#define  bBefbEncoderErr        GET_BITFIELD(&Etc3Bit).bit1 
#define  bEncoderABErr          GET_BITFIELD(&Etc3Bit).bit2 
#define  bBefbEncoderABErr      GET_BITFIELD(&Etc3Bit).bit3 
#define  bUpDnSet               GET_BITFIELD(&Etc3Bit).bit4
#define  bSetSpeedOn            GET_BITFIELD(&Etc3Bit).bit5
#define  bAllMenu               GET_BITFIELD(&Etc3Bit).bit6
#define  bUserOn                GET_BITFIELD(&Etc3Bit).bit7




#define  bSaveErrCnt            GET_BITFIELD(&Etc2Bit).bit0 
#define  bInvOutAllClr          GET_BITFIELD(&Etc2Bit).bit1 
#define  bDoorOpenEnd           GET_BITFIELD(&Etc2Bit).bit2
#define  bFR2Start1             GET_BITFIELD(&Etc2Bit).bit3
#define  bPasswardOk            GET_BITFIELD(&Etc2Bit).bit4
#define  bUnd                   GET_BITFIELD(&Etc2Bit).bit5
#define  bDac                   GET_BITFIELD(&Etc2Bit).bit6
#define  bsBreakMgtOpen         GET_BITFIELD(&Etc2Bit).bit7




#define  bOpenEnd               GET_BITFIELD(&DoorStatus_bit).bit0 
#define  bCarDoorCloseEnd       GET_BITFIELD(&DoorStatus_bit).bit1   
#define  bHoleDoorCloseEnd      GET_BITFIELD(&DoorStatus_bit).bit2   
#define  bDoorCloseOk           GET_BITFIELD(&DoorStatus_bit).bit3 
#define  bsHdsRunOff            GET_BITFIELD(&DoorStatus_bit).bit4
#define  bsCleRunOff            GET_BITFIELD(&DoorStatus_bit).bit5
#define  bBefbsBreakMgtOpen     GET_BITFIELD(&DoorStatus_bit).bit6
#define  bBefbsSusErr           GET_BITFIELD(&DoorStatus_bit).bit7

#define  bPC_PRK                GET_BITFIELD(&PC1Bit).bit0 
#define  bPC_FIRE               GET_BITFIELD(&PC1Bit).bit1 
#define  bDoorOpenCmd           GET_BITFIELD(&PC1Bit).bit2 
#define  bDoorCloseCmd          GET_BITFIELD(&PC1Bit).bit3 
#define  bHoleDoorOpenEnd       GET_BITFIELD(&PC1Bit).bit4 
#define  bOpenDoorOk            GET_BITFIELD(&PC1Bit).bit5 
#define  bEqualFloorError       GET_BITFIELD(&PC1Bit).bit6 
#define  bHibCallClear          GET_BITFIELD(&PC1Bit).bit7 


#define  bOneStep               GET_BITFIELD(&StateBit0).bit0 
#define  bTwoStep               GET_BITFIELD(&StateBit0).bit1 
#define  bThreeStep             GET_BITFIELD(&StateBit0).bit2 
#define  bFourStep              GET_BITFIELD(&StateBit0).bit3 
#define  bBefbsSdsErr           GET_BITFIELD(&StateBit0).bit4 
#define  bInvErrCnt             GET_BITFIELD(&StateBit0).bit5 
#define  bDspSeq                GET_BITFIELD(&StateBit0).bit6 
#define  bLevelFind             GET_BITFIELD(&StateBit0).bit7 


#define  bsInvertErr            GET_BITFIELD(&StateBit1).bit0 
#define  bBefbsInvertErr        GET_BITFIELD(&StateBit1).bit1 
#define  bOnceOpen              GET_BITFIELD(&StateBit1).bit2 
#define  bDoorCloseOkSensor     GET_BITFIELD(&StateBit1).bit3 
#define  bsBreakOpen            GET_BITFIELD(&StateBit1).bit4 
#define  bBefbsBreakOpen        GET_BITFIELD(&StateBit1).bit5 
#define  bsSusErr               GET_BITFIELD(&StateBit1).bit6 
#define  bsSdsErr               GET_BITFIELD(&StateBit1).bit7 


#define  bOnceVip               GET_BITFIELD(&StateBit2).bit0 
#define  bNextFlrChk            GET_BITFIELD(&StateBit2).bit1 
#define  bExportData            GET_BITFIELD(&StateBit2).bit2 
#define  bImportData            GET_BITFIELD(&StateBit2).bit3 
#define  bPC_FAMILY             GET_BITFIELD(&StateBit2).bit4 
#define  bPowerChkStart         GET_BITFIELD(&StateBit2).bit5 
#define  bWritechk              GET_BITFIELD(&StateBit2).bit6 
#define  bOutDate               GET_BITFIELD(&StateBit2).bit7 


#define  bFirstOnLuLd           GET_BITFIELD(&StateBit3).bit0 
#define  bNotStopRelevel        GET_BITFIELD(&StateBit3).bit1 
#define  bPasswardUse           GET_BITFIELD(&StateBit3).bit2 
#define  bCompanyCtl        	GET_BITFIELD(&StateBit3).bit3 
#define  bLoaderActive          GET_BITFIELD(&StateBit3).bit4 
#define  bDoorOpenEndFind       GET_BITFIELD(&StateBit3).bit5 
#define  bSolControl            GET_BITFIELD(&StateBit3).bit6 
#define  bReLoadEncoder        	GET_BITFIELD(&StateBit3).bit7 



#define  bOneLuOrLd           	GET_BITFIELD(&StateBit4).bit0 
#define  bBK1        			GET_BITFIELD(&StateBit4).bit1 
#define  bsLuOrLdErr           	GET_BITFIELD(&StateBit4).bit2 
#define  bBefsLuOrLdErr        	GET_BITFIELD(&StateBit4).bit3 
#define  bBefDoorJumper         GET_BITFIELD(&StateBit4).bit4 
#define  bHibSet       			GET_BITFIELD(&StateBit4).bit5 
#define  bRunningOpenOn		    GET_BITFIELD(&StateBit4).bit6 
#define  bFhmEncoder        	GET_BITFIELD(&StateBit4).bit7 



#define  bSlavePrk      		GET_BITFIELD(&StateBit5).bit0 
#define  bMotor_Overheat      	GET_BITFIELD(&StateBit5).bit1 
#define  bBefbMotor_Overheat    GET_BITFIELD(&StateBit5).bit2 
#define  bFlrMatchChk        	GET_BITFIELD(&StateBit5).bit3 
#define  bBef_IN_MM         	GET_BITFIELD(&StateBit5).bit4 
#define  bSafety_scrSft       	GET_BITFIELD(&StateBit5).bit5 
#define  bRelevelErr		    GET_BITFIELD(&StateBit5).bit6 
#define  bLevelOpen        		GET_BITFIELD(&StateBit5).bit7 



//////////////////////////////////////////////////////////////
#define  IN_SU1_PORT            GET_BITFIELD(&I_SU1_bit).bit0 
#define  IN_SD1_PORT            GET_BITFIELD(&I_SU1_bit).bit1  
#define  IN_SFT_PORT            GET_BITFIELD(&I_SU1_bit).bit2  
#define  IN_OVL_PORT            GET_BITFIELD(&I_SU1_bit).bit3  
#define  IN_ULS_PORT            GET_BITFIELD(&I_SU1_bit).bit4   
#define  IN_DLS_PORT            GET_BITFIELD(&I_SU1_bit).bit5   
#define  IN_LU_PORT             GET_BITFIELD(&I_SU1_bit).bit6   
#define  IN_LD_PORT             GET_BITFIELD(&I_SU1_bit).bit7   

#define  IN_EMG_PORT            GET_BITFIELD(&I_EMG_bit).bit0 
#define  IN_PRK_PORT            GET_BITFIELD(&I_EMG_bit).bit1  
#define  IN_AUTO_PORT           GET_BITFIELD(&I_EMG_bit).bit2  
#define  IN_U_B_PORT            GET_BITFIELD(&I_EMG_bit).bit3  
#define  IN_D_B_PORT            GET_BITFIELD(&I_EMG_bit).bit4   
#define  IN_OP_E_PORT           GET_BITFIELD(&I_EMG_bit).bit5   
#define  IN_CL_E_PORT           GET_BITFIELD(&I_EMG_bit).bit6   
#define  IN_HL_D_PORT           GET_BITFIELD(&I_EMG_bit).bit7   

#define  IN_GR_PORT             GET_BITFIELD(&I_GR_bit).bit0 
#define  IN_BAT_PORT            GET_BITFIELD(&I_GR_bit).bit1  
#define  IN_PASS_PORT           GET_BITFIELD(&I_GR_bit).bit2  
#define  IN_FIRE_PORT           GET_BITFIELD(&I_GR_bit).bit3  
#define  IN_WATER_PORT          GET_BITFIELD(&I_GR_bit).bit4   
#define  IN_FULL_PORT           GET_BITFIELD(&I_GR_bit).bit5   
//#define  IN_EX1_PORT            GET_BITFIELD(&I_GR_bit).bit6   
#define  IN_MM_PORT            GET_BITFIELD(&I_GR_bit).bit6   
#define  IN_FHM_PORT            GET_BITFIELD(&I_GR_bit).bit7   

#define  IN_FR1_PORT            GET_BITFIELD(&I_FIRE_bit).bit0 
#define  IN_FR2_PORT            GET_BITFIELD(&I_FIRE_bit).bit1  
#define  IN_GS2_PORT            GET_BITFIELD(&I_FIRE_bit).bit2  
#define  IN_DS2_PORT            GET_BITFIELD(&I_FIRE_bit).bit3  
#define  IN_SU2_PORT            GET_BITFIELD(&I_FIRE_bit).bit4   
#define  IN_SD2_PORT            GET_BITFIELD(&I_FIRE_bit).bit5   
//#define  IN_SU3_PORT            GET_BITFIELD(&I_FIRE_bit).bit6   
#define  IN_BM_PORT            GET_BITFIELD(&I_FIRE_bit).bit6   
//#define  IN_SD3_PORT            GET_BITFIELD(&I_FIRE_bit).bit7   
#define  IN_INV_PORT            GET_BITFIELD(&I_FIRE_bit).bit7   

#define  IN_FS0_PORT            GET_BITFIELD(&I_FS0_bit).bit0 
#define  IN_FS1_PORT            GET_BITFIELD(&I_FS0_bit).bit1  
#define  IN_FS2_PORT            GET_BITFIELD(&I_FS0_bit).bit2  
#define  IN_FS3_PORT            GET_BITFIELD(&I_FS0_bit).bit3  
#define  IN_FS4_PORT            GET_BITFIELD(&I_FS0_bit).bit4   
#define  IN_DER_PORT            GET_BITFIELD(&I_FS0_bit).bit5   
#define  IN_FID_PORT            GET_BITFIELD(&I_FS0_bit).bit6   
#define  IN_UND_PORT            GET_BITFIELD(&I_FS0_bit).bit7   

#define  IN_X0_PORT             GET_BITFIELD(&I_X0_bit).bit0  
#define  IN_X1_PORT             GET_BITFIELD(&I_X0_bit).bit1 
#define  IN_X2_PORT             GET_BITFIELD(&I_X0_bit).bit2  
#define  IN_X3_PORT             GET_BITFIELD(&I_X0_bit).bit3  
#define  IN_X4_PORT             GET_BITFIELD(&I_X0_bit).bit4   
#define  IN_X5_PORT             GET_BITFIELD(&I_X0_bit).bit5   
#define  IN_X6_PORT             GET_BITFIELD(&I_X0_bit).bit6   
#define  IN_X7_PORT             GET_BITFIELD(&I_X0_bit).bit7   



#define  OUT_OP_PORT            GET_BITFIELD(&O_OP_bit).bit0 
#define  OUT_CL_PORT            GET_BITFIELD(&O_OP_bit).bit1  
#define  OUT_OP_S_PORT          GET_BITFIELD(&O_OP_bit).bit2   
#define  OUT_CL_S_PORT          GET_BITFIELD(&O_OP_bit).bit3
#define  OUT_BK2_PORT           GET_BITFIELD(&O_OP_bit).bit4  
#define  OUT_D_S_PORT           GET_BITFIELD(&O_OP_bit).bit5  
#define  OUT_GBR_PORT           GET_BITFIELD(&O_OP_bit).bit6   
#define  OUT_BRK_PORT           GET_BITFIELD(&O_OP_bit).bit7   


#define  OUT_U_W_PORT            GET_BITFIELD(&O_U_W_bit).bit0 
#define  OUT_D_W_PORT            GET_BITFIELD(&O_U_W_bit).bit1  
#define  OUT_P1_PORT             GET_BITFIELD(&O_U_W_bit).bit2  
#define  OUT_P2_PORT             GET_BITFIELD(&O_U_W_bit).bit3  
#define  OUT_P3_PORT             GET_BITFIELD(&O_U_W_bit).bit4   
#define  OUT_P4_PORT             GET_BITFIELD(&O_U_W_bit).bit5   
#define  OUT_DAC_PORT            GET_BITFIELD(&O_U_W_bit).bit7   

#define  OUT_FAN_PORT            GET_BITFIELD(&O_Y_0_bit).bit0  
#define  OUT_LIT_PORT            GET_BITFIELD(&O_Y_0_bit).bit1  
#define  OUT_BUZ_PORT            GET_BITFIELD(&O_Y_0_bit).bit2   
#define  OUT_BELL_PORT           GET_BITFIELD(&O_Y_0_bit).bit3
#define  OUT_RST_PORT            GET_BITFIELD(&O_Y_0_bit).bit4
#define  OUT_ERR_PORT            GET_BITFIELD(&O_Y_0_bit).bit5
#define  OUT_HOP_PORT            GET_BITFIELD(&O_Y_0_bit).bit6
#define  OUT_HCL_PORT            GET_BITFIELD(&O_Y_0_bit).bit7


///////////////////////////////////////////////////////////////


#define  GET_LONG(adr)          (unsigned long)GET_LONGFIELD(&FlashDspCharBuf[adr]).long_data
#define  FLOOR_COUNT(adr)       GET_LONGFIELD(&FlashDspCharBuf[(adr+FLR_01_PULSE)]).long_data


#define  CurPulse               GET_LONGFIELD(&parameter_mirror[CUR_PULSE]).long_data
#define  BefCurPulse            GET_LONGFIELD(&parameter_mirror[BEF_CUR_PULSE]).long_data
#define  MeterPerMin            GET_LONGFIELD(&parameter_mirror[METER_PER_MIN]).long_data
#define  CurMeterPerMin         GET_LONGFIELD(&parameter_mirror[CUR_METER_PER_MIN]).long_data
#define  MoveCounterx           GET_LONGFIELD(&parameter_mirror[MOVE_COUNTER]).long_data


#define  TotalPulse             GET_LONGFIELD(&parameter_mirror[TOTAL_PULSE]).long_data
#define  StopMinimumPulse       GET_LONGFIELD(&parameter_mirror[STOP_MINIMUM_PULSE]).long_data
#define  DecreasePulse          GET_LONGFIELD(&parameter_mirror[DECREASE_PULSE]).long_data
#define  TmpFhmCounter1         GET_LONGFIELD(&parameter_mirror[TMP_FHM_COUNTER1]).long_data
#define  TmpFhmCounter2         GET_LONGFIELD(&parameter_mirror[TMP_FHM_COUNTER2]).long_data
#define  TmpMmPerMin            GET_LONGFIELD(&parameter_mirror[TMP_MM_PER_MIN]).long_data
#define  PulsePer100Msec        GET_LONGFIELD(&parameter_mirror[PULSE_PER_100MSEC]).long_data
#define  CurRpm                 GET_LONGFIELD(&parameter_mirror[CUR_RPM]).long_data
#define  StartPulse             GET_LONGFIELD(&parameter_mirror[START_PULSE]).long_data







#define  cF_TOPFLR              GET_LONGFIELD(&FlashDspCharBuf[F_TopFlr/4])         .byte[F_TopFlr%4]
#define  cF_PRKFLR              GET_LONGFIELD(&FlashDspCharBuf[F_PrkFlr/4])         .byte[F_PrkFlr%4]
#define  cF_FIXFLOOR            GET_LONGFIELD(&FlashDspCharBuf[F_FixFloor/4])       .byte[F_FixFloor%4]
#define  cF_FIRESAFEFLR         GET_LONGFIELD(&FlashDspCharBuf[F_FireSafeFlr/4])    .byte[F_FireSafeFlr%4]

#define  cF_SUBDOORFLR1         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr1/4])    .byte[F_SubDoorFlr1%4]
#define  cF_SUBDOORFLR2         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr2/4])    .byte[F_SubDoorFlr2%4]
#define  cF_SUBDOORFLR3         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr3/4])    .byte[F_SubDoorFlr3%4]
#define  cF_SUBDOORFLR4         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr4/4])    .byte[F_SubDoorFlr4%4]
#define  cF_SUBDOORFLR5         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr5/4])    .byte[F_SubDoorFlr5%4]
#define  cF_SUBDOORFLR6         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr6/4])    .byte[F_SubDoorFlr6%4]
#define  cF_SUBDOORFLR7         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr7/4])    .byte[F_SubDoorFlr7%4]
#define  cF_SUBDOORFLR8         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr8/4])    .byte[F_SubDoorFlr8%4]

#define  cF_X7SAFEFLR           GET_LONGFIELD(&FlashDspCharBuf[F_X7SafeFlr/4])      .byte[F_X7SafeFlr%4]
#define  cF_WATERSAFEFLR        GET_LONGFIELD(&FlashDspCharBuf[F_WaterSafeFlr/4])   .byte[F_WaterSafeFlr%4]
#define  cF_START_FLOOR         GET_LONGFIELD(&FlashDspCharBuf[F_StartFloor/4])     .byte[F_StartFloor%4]
#define  cF_ONESTOP_FLOOR       GET_LONGFIELD(&FlashDspCharBuf[F_OneStopFlr/4])     .byte[F_OneStopFlr%4]
#define  cF_KIDS_KEY_CNT        GET_LONGFIELD(&FlashDspCharBuf[F_KidsKeyCnt/4])     .byte[F_KidsKeyCnt%4]
#define  cF_X6SAFEFLR           GET_LONGFIELD(&FlashDspCharBuf[F_X6SafeFlr/4])      .byte[F_X6SafeFlr%4]
#define  cF_X5SAFEFLR           GET_LONGFIELD(&FlashDspCharBuf[F_X5SafeFlr/4])      .byte[F_X5SafeFlr%4]


////////////////////////////////


#define  cF_OPWTTMmsec          GET_LONGFIELD(&FlashDspCharBuf[F_OpWtTm/4])         .byte[F_OpWtTm%4]
#define  cF_OPTTTMmsec          GET_LONGFIELD(&FlashDspCharBuf[F_OpTtTm/4])         .byte[F_OpTtTm%4]
#define  cF_FIXFLOORTIME        GET_LONGFIELD(&FlashDspCharBuf[F_FixFloorTime/4])   .byte[F_FixFloorTime%4]
#define  cF_NEXTFLRTIME         GET_LONGFIELD(&FlashDspCharBuf[F_NextFlrTime/4])    .byte[F_NextFlrTime%4]

#define  cF_LULDOFFTIMEmsec     GET_LONGFIELD(&FlashDspCharBuf[F_LuLdOffTime/4])    .byte[F_LuLdOffTime%4]
#define  cF_FANTIME             GET_LONGFIELD(&FlashDspCharBuf[F_FanTime/4])        .byte[F_FanTime%4]
#define  cF_LIGHTTIME           GET_LONGFIELD(&FlashDspCharBuf[F_LightTime/4])      .byte[F_LightTime%4]

#define  cF_REOPTMmsec          GET_LONGFIELD(&FlashDspCharBuf[F_ReOpTime/4])       .byte[F_ReOpTime%4]      
#define  cF_OPCLWTMmsec         GET_LONGFIELD(&FlashDspCharBuf[F_OpClWaitTime/4])   .byte[F_OpClWaitTime%4]

#define  cF_DRJMPCHKTMmsec      GET_LONGFIELD(&FlashDspCharBuf[F_DrJmpChkTime/4])   .byte[F_DrJmpChkTime%4]
#define  cF_DIRTIME             GET_LONGFIELD(&FlashDspCharBuf[F_DirTime/4])        .byte[F_DirTime%4]
#define  cF_VOICETIME           GET_LONGFIELD(&FlashDspCharBuf[F_VoiceTime/4])      .byte[F_VoiceTime%4]
#define  cF_BrkMgtmsec          GET_LONGFIELD(&FlashDspCharBuf[F_BrkMgtTime/4])     .byte[F_BrkMgtTime%4]


//??????
#define  cF_STTM1msec           GET_LONGFIELD(&FlashDspCharBuf[F_StTm1/4])          .byte[F_StTm1%4]
#define  cF_STTM2msec           GET_LONGFIELD(&FlashDspCharBuf[F_StTm2/4])          .byte[F_StTm2%4]
#define  cF_STTM3msec           GET_LONGFIELD(&FlashDspCharBuf[F_StTm3/4])          .byte[F_StTm3%4]
#define  cF_STTM4msec           GET_LONGFIELD(&FlashDspCharBuf[F_StTm4/4])          .byte[F_StTm4%4]
#define  cF_STTM5msec           GET_LONGFIELD(&FlashDspCharBuf[F_StTm5/4])          .byte[F_StTm5%4]



#define  cF_RunOffTime         GET_LONGFIELD(&FlashDspCharBuf[F_RunOffTime/4])      .byte[F_RunOffTime%4]
#define  iF_RunOffTime         (cF_RunOffTime * 100)

#define  cF_Bk1OffTime         GET_LONGFIELD(&FlashDspCharBuf[F_Bk1OffTime/4])      .byte[F_Bk1OffTime%4]
#define  iF_Bk1OffTime         (cF_Bk1OffTime * 100)

#define  cF_Bk2OffTime         GET_LONGFIELD(&FlashDspCharBuf[F_Bk2OffTime/4])      .byte[F_Bk2OffTime%4]
#define  iF_Bk2OffTime         (cF_Bk2OffTime * 100)

#define  cF_UDOffTime         GET_LONGFIELD(&FlashDspCharBuf[F_UDOffTime/4])      .byte[F_UDOffTime%4]
#define  iF_UDOffTime         (cF_UDOffTime * 100)


#define  cF_P4OffTime         GET_LONGFIELD(&FlashDspCharBuf[F_P4OffTime/4])      .byte[F_P4OffTime%4]
#define  iF_P4OffTime         (cF_P4OffTime * 100)


#define  cF_SolOnTime         GET_LONGFIELD(&FlashDspCharBuf[F_SolOnTime/4])      .byte[F_SolOnTime%4]
#define  iF_SolOnTime         (cF_SolOnTime * 1)

#define  cF_DoorWaitTime      GET_LONGFIELD(&FlashDspCharBuf[F_DoorWaitTime/4])   .byte[F_DoorWaitTime%4]
#define  iF_DoorWaitTime      (cF_DoorWaitTime * 1)


//#define  iF_F_BrkStTm10         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm10/4])      .intger[(F_BrkStTm10%4)/2]
//#define  iF_F_BrkStTm20         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm20/4])      .intger[(F_BrkStTm20%4)/2]

//#define  iF_F_BrkStTm30         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm30/4])      .intger[(F_BrkStTm30%4)/2]

//#define  iF_F_BrkStTm40         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm40/4])      .intger[(F_BrkStTm40%4)/2]

//#define  iF_F_BrkStTm50         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm50/4])      .intger[(F_BrkStTm50%4)/2]
//#define  iF_F_BrkStTm60         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm60/4])      .intger[(F_BrkStTm60%4)/2]

//#define  iF_F_UseTime10         GET_LONGFIELD(&FlashDspCharBuf[F_UseTime10/4])      .intger[(F_UseTime10%4)/2]

#define  cF_OPWTTM              (cF_OPWTTMmsec * 10)
#define  cF_OPTTTM              (cF_OPTTTMmsec * 10)
#define  cF_LULDOFFTIME         (cF_LULDOFFTIMEmsec * 10)

#define  cF_REOPTM              (cF_REOPTMmsec * 10)     
#define  cF_OPCLWTM             (cF_OPCLWTMmsec * 10)     

#define  cF_DRJMPCHKTTM         (cF_DRJMPCHKTMmsec * 10)     

#define  cF_BRK_MGT_TIME        (cF_BrkMgtmsec * 10)     


#define  cF_STTM1               (cF_STTM1msec * 1)
#define  cF_STTM2               (cF_STTM2msec * 1)
#define  cF_STTM3               (cF_STTM3msec * 1)
#define  cF_STTM4               (cF_STTM4msec * 1)
#define  cF_STTM5               (cF_STTM5msec * 1)



//////////////////////////////////////////////////////




#define  cF_NCNOBIT0            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit0/4])       .byte[F_NcNoBit0%4]
#define  cF_NCNOBIT1            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit1/4])       .byte[F_NcNoBit1%4]
#define  cF_NCNOBIT2            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit2/4])       .byte[F_NcNoBit2%4]
#define  cF_NCNOBIT3            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit3/4])       .byte[F_NcNoBit3%4]
#define  cF_NCNOBIT4            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit4/4])       .byte[F_NcNoBit4%4]
#define  cF_NCNOBIT5            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit5/4])       .byte[F_NcNoBit5%4]
#define  cF_NCNOBIT6            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit6/4])       .byte[F_NcNoBit6%4]
#define  cF_NCNOBIT7            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit7/4])       .byte[F_NcNoBit7%4]
#define  cF_NCNOBIT8            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit8/4])       .byte[F_NcNoBit8%4]


#define  cF_NONSERVICE0         GET_LONGFIELD(&FlashDspCharBuf[F_NonService0/4])    .byte[F_NonService0%4]
#define  cF_NONSERVICE1         GET_LONGFIELD(&FlashDspCharBuf[F_NonService1/4])    .byte[F_NonService1%4]
#define  cF_NONSERVICE2         GET_LONGFIELD(&FlashDspCharBuf[F_NonService2/4])    .byte[F_NonService2%4]
#define  cF_NONSERVICE3         GET_LONGFIELD(&FlashDspCharBuf[F_NonService3/4])    .byte[F_NonService3%4]


//#define  cF_PASSWARD            GET_LONGFIELD(&FlashDspCharBuf[F_Passward/4])       .byte[F_Passward%4]



#define  cF_VER0                GET_LONGFIELD(&FlashDspCharBuf[F_Ver0/4])           .byte[F_Ver0%4]
#define  cF_VER1                GET_LONGFIELD(&FlashDspCharBuf[F_Ver1/4])           .byte[F_Ver1%4]
#define  cF_VER2                GET_LONGFIELD(&FlashDspCharBuf[F_Ver2/4])           .byte[F_Ver2%4]
#define  cF_BD_ID               GET_LONGFIELD(&FlashDspCharBuf[F_Bd_Id/4])          .byte[F_Bd_Id%4]

#define  cF_PASSWARD0            GET_LONGFIELD(&FlashDspCharBuf[F_Passward0/4])     .byte[F_Passward0%4]
#define  cF_PASSWARD1            GET_LONGFIELD(&FlashDspCharBuf[F_Passward1/4])     .byte[F_Passward1%4]
#define  cF_PASSWARD2            GET_LONGFIELD(&FlashDspCharBuf[F_Passward2/4])     .byte[F_Passward2%4]
#define  cF_PASSWARD3            GET_LONGFIELD(&FlashDspCharBuf[F_Passward3/4])     .byte[F_Passward3%4]

//#define  cF_SERIALNM0           GET_LONGFIELD(&FlashDspCharBuf[F_SerialNm0/4])      .byte[F_SerialNm0%4]
//#define  cF_SERIALNM1           GET_LONGFIELD(&FlashDspCharBuf[F_SerialNm1/4])      .byte[F_SerialNm1%4]

#define  cF_USERLAMP1           GET_LONGFIELD(&FlashDspCharBuf[F_UserLamp1/4])      .byte[F_UserLamp1%4]
#define  cF_USERLAMP2           GET_LONGFIELD(&FlashDspCharBuf[F_UserLamp2/4])      .byte[F_UserLamp2%4]
#define  cF_USERLAMP3           GET_LONGFIELD(&FlashDspCharBuf[F_UserLamp3/4])      .byte[F_UserLamp3%4]
#define  cF_USERLAMP4           GET_LONGFIELD(&FlashDspCharBuf[F_UserLamp4/4])      .byte[F_UserLamp4%4]

#define  cF_ERRSTOPCNT          GET_LONGFIELD(&FlashDspCharBuf[F_ErrStopCnt/4])     .byte[F_ErrStopCnt%4]
#define  cF_NormalDsp           GET_LONGFIELD(&FlashDspCharBuf[F_NormalDsp/4])      .byte[F_NormalDsp%4]
#define  cF_GroupNm             GET_LONGFIELD(&FlashDspCharBuf[F_GroupNm/4])        .byte[F_GroupNm%4]
#define  cF_LocalNm             GET_LONGFIELD(&FlashDspCharBuf[F_LocalNm/4])        .byte[F_LocalNm%4]
#define  cF_PcbType             GET_LONGFIELD(&FlashDspCharBuf[F_PcbType/4])        .byte[F_PcbType%4]
//#define  cF_EncoderRate         GET_LONGFIELD(&FlashDspCharBuf[F_EncoderRate/4])    .byte[F_EncoderRate%4]
#define  iF_StopPulse           GET_LONGFIELD(&FlashDspCharBuf[F_StopPulse0/4])     .intger[(F_StopPulse0%4)/2]
#define  cF_Airconadr           GET_LONGFIELD(&FlashDspCharBuf[F_Airconadr/4])      .byte[F_Airconadr%4]

#define  cF_year                GET_LONGFIELD(&FlashDspCharBuf[F_year/4])           .byte[F_year%4]
#define  cF_month               GET_LONGFIELD(&FlashDspCharBuf[F_month/4])          .byte[F_month%4]
#define  cF_day                 GET_LONGFIELD(&FlashDspCharBuf[F_day/4])            .byte[F_day%4]

#define  cF_COMPANY             GET_LONGFIELD(&FlashDspCharBuf[F_Company/4])        .byte[F_Company%4]



#define  cF_ELEV_SPEED          GET_LONGFIELD(&FlashDspCharBuf[F_ElevSpeed/4])      .byte[F_ElevSpeed%4]
#define  cF_LIMIT_SPEED         GET_LONGFIELD(&FlashDspCharBuf[F_LimitSpeed/4])     .byte[F_LimitSpeed%4]

#define  cF_SU1SD1_VELOCITY     GET_LONGFIELD(&FlashDspCharBuf[F_Su1Sd1_Velocity/4]).byte[F_Su1Sd1_Velocity%4]
#define  cF_SU2SD2_VELOCITY     GET_LONGFIELD(&FlashDspCharBuf[F_Su2Sd2_Velocity/4]).byte[F_Su2Sd2_Velocity%4]
#define  cF_X0X1_VELOCITY       GET_LONGFIELD(&FlashDspCharBuf[F_X0X1_Velocity/4])  .byte[F_X0X1_Velocity%4]
#define  cF_FhmOnOff            GET_LONGFIELD(&FlashDspCharBuf[F_FhmOnOff/4])       .byte[F_FhmOnOff%4]

#define  cF_DoorJumperOff       GET_LONGFIELD(&FlashDspCharBuf[F_DoorJumperOff/4])  .byte[F_DoorJumperOff%4]


#define  cF_0506                GET_LONGFIELD(&FlashDspCharBuf[F_0506/4])           .byte[F_0506%4]
#define  cF_0607                GET_LONGFIELD(&FlashDspCharBuf[F_0607/4])           .byte[F_0607%4]
#define  cF_0708                GET_LONGFIELD(&FlashDspCharBuf[F_0708/4])           .byte[F_0708%4]
#define  cF_0809                GET_LONGFIELD(&FlashDspCharBuf[F_0809/4])           .byte[F_0809%4]
#define  cF_0910                GET_LONGFIELD(&FlashDspCharBuf[F_0910/4])           .byte[F_0910%4]
#define  cF_1011                GET_LONGFIELD(&FlashDspCharBuf[F_1011/4])           .byte[F_1011%4]
#define  cF_1112                GET_LONGFIELD(&FlashDspCharBuf[F_1112/4])           .byte[F_1112%4]
#define  cF_1213                GET_LONGFIELD(&FlashDspCharBuf[F_1213/4])           .byte[F_1213%4]
#define  cF_1314                GET_LONGFIELD(&FlashDspCharBuf[F_1314/4])           .byte[F_1314%4]
#define  cF_1415                GET_LONGFIELD(&FlashDspCharBuf[F_1415/4])           .byte[F_1415%4]
#define  cF_1516                GET_LONGFIELD(&FlashDspCharBuf[F_1516/4])           .byte[F_1516%4]
#define  cF_1617                GET_LONGFIELD(&FlashDspCharBuf[F_1617/4])           .byte[F_1617%4]
#define  cF_1718                GET_LONGFIELD(&FlashDspCharBuf[F_1718/4])           .byte[F_1718%4]
#define  cF_1819                GET_LONGFIELD(&FlashDspCharBuf[F_1819/4])           .byte[F_1819%4]
#define  cF_1920                GET_LONGFIELD(&FlashDspCharBuf[F_1920/4])           .byte[F_1920%4]
#define  cF_2021                GET_LONGFIELD(&FlashDspCharBuf[F_2021/4])           .byte[F_2021%4]
#define  cF_2105                GET_LONGFIELD(&FlashDspCharBuf[F_2105/4])           .byte[F_2105%4]

#define  cF_ParkingStart        GET_LONGFIELD(&FlashDspCharBuf[F_ParkingStart/4])   .byte[F_ParkingStart%4]
#define  cF_ParkingEnd          GET_LONGFIELD(&FlashDspCharBuf[F_ParkingEnd/4])     .byte[F_ParkingEnd%4]




//////TEST
#define  cF_SU1                 GET_LONGFIELD(&FlashDspCharBuf[SU1_PORT/4])         .byte[SU1_PORT%4]
#define  cF_SD1                 GET_LONGFIELD(&FlashDspCharBuf[SD1_PORT/4])         .byte[SD1_PORT%4]  
#define  cF_SFT                 GET_LONGFIELD(&FlashDspCharBuf[SFT_PORT/4])         .byte[SFT_PORT%4]  
#define  cF_OVL                 GET_LONGFIELD(&FlashDspCharBuf[OVL_PORT/4])         .byte[OVL_PORT%4]  
#define  cF_ULS                 GET_LONGFIELD(&FlashDspCharBuf[ULS_PORT/4])         .byte[ULS_PORT%4]   
#define  cF_DLS                 GET_LONGFIELD(&FlashDspCharBuf[DLS_PORT/4])         .byte[DLS_PORT%4]   
#define  cF_LU                  GET_LONGFIELD(&FlashDspCharBuf[LU_PORT/4])          .byte[LU_PORT%4]   
#define  cF_LD                  GET_LONGFIELD(&FlashDspCharBuf[LD_PORT/4])          .byte[LD_PORT%4]   

#define  cF_EMG                 GET_LONGFIELD(&FlashDspCharBuf[EMG_PORT/4])         .byte[EMG_PORT%4] 
#define  cF_PRK                 GET_LONGFIELD(&FlashDspCharBuf[PRK_PORT/4])         .byte[PRK_PORT%4]  
#define  cF_AUTO                GET_LONGFIELD(&FlashDspCharBuf[AUTO_PORT/4])        .byte[AUTO_PORT%4]  
#define  cF_U_B                 GET_LONGFIELD(&FlashDspCharBuf[U_B_PORT/4])         .byte[U_B_PORT%4]  
#define  cF_D_B                 GET_LONGFIELD(&FlashDspCharBuf[D_B_PORT/4])         .byte[D_B_PORT%4]   
#define  cF_OP_E                GET_LONGFIELD(&FlashDspCharBuf[OLS_PORT/4])         .byte[OLS_PORT%4]   
#define  cF_CL_E                GET_LONGFIELD(&FlashDspCharBuf[GS_PORT/4])          .byte[GS_PORT%4]   
#define  cF_HL_D                GET_LONGFIELD(&FlashDspCharBuf[DS_PORT/4])          .byte[DS_PORT%4]   

#define  cF_GR                  GET_LONGFIELD(&FlashDspCharBuf[RG_PORT/4])          .byte[RG_PORT%4] 
#define  cF_BAT                 GET_LONGFIELD(&FlashDspCharBuf[BAT_PORT/4])         .byte[BAT_PORT%4]  
#define  cF_PASS                GET_LONGFIELD(&FlashDspCharBuf[PASS_PORT/4])        .byte[PASS_PORT%4]  
#define  cF_FIRE                GET_LONGFIELD(&FlashDspCharBuf[FIRE_PORT/4])        .byte[FIRE_PORT%4]  
#define  cF_WATER               GET_LONGFIELD(&FlashDspCharBuf[WATER_PORT/4])       .byte[WATER_PORT%4]   
#define  cF_FULL                GET_LONGFIELD(&FlashDspCharBuf[FULL_PORT/4])        .byte[FULL_PORT%4]   
//#define  cF_EX1                 GET_LONGFIELD(&FlashDspCharBuf[EX1_PORT/4])         .byte[EX1_PORT%4]   
#define  cF_MM                 GET_LONGFIELD(&FlashDspCharBuf[MM_PORT/4])         .byte[MM_PORT%4]   
#define  cF_FHM                 GET_LONGFIELD(&FlashDspCharBuf[FHM_PORT/4])         .byte[FHM_PORT%4]   

#define  cF_FR1                 GET_LONGFIELD(&FlashDspCharBuf[FR1_PORT/4])         .byte[FR1_PORT%4] 
#define  cF_FR2                 GET_LONGFIELD(&FlashDspCharBuf[FR2_PORT/4])         .byte[FR2_PORT%4]  
#define  cF_GS2                 GET_LONGFIELD(&FlashDspCharBuf[GS2_PORT/4])         .byte[GS2_PORT%4]  
#define  cF_DS2                 GET_LONGFIELD(&FlashDspCharBuf[DS2_PORT/4])         .byte[DS2_PORT%4]  
#define  cF_SU2                 GET_LONGFIELD(&FlashDspCharBuf[SU2_PORT/4])         .byte[SU2_PORT%4]   
#define  cF_SD2                 GET_LONGFIELD(&FlashDspCharBuf[SD2_PORT/4])         .byte[SD2_PORT%4]   
//#define  cF_SU3                 GET_LONGFIELD(&FlashDspCharBuf[SU3_PORT/4])         .byte[SU3_PORT%4]   
#define  cF_BM                 GET_LONGFIELD(&FlashDspCharBuf[BM_PORT/4])         .byte[BM_PORT%4]   
//#define  cF_SD3                 GET_LONGFIELD(&FlashDspCharBuf[SD3_PORT/4])         .byte[SD3_PORT%4]   
#define  cF_INV                 GET_LONGFIELD(&FlashDspCharBuf[INV_PORT/4])         .byte[INV_PORT%4]   

#define  cF_FS0                 GET_LONGFIELD(&FlashDspCharBuf[FS0_PORT/4])         .byte[FS0_PORT%4] 
#define  cF_FS1                 GET_LONGFIELD(&FlashDspCharBuf[FS1_PORT/4])         .byte[FS1_PORT%4]  
#define  cF_FS2                 GET_LONGFIELD(&FlashDspCharBuf[FS2_PORT/4])         .byte[FS2_PORT%4]  
#define  cF_FS3                 GET_LONGFIELD(&FlashDspCharBuf[FS3_PORT/4])         .byte[FS3_PORT%4]  
#define  cF_FS4                 GET_LONGFIELD(&FlashDspCharBuf[FS4_PORT/4])         .byte[FS4_PORT%4]   
#define  cF_DER                 GET_LONGFIELD(&FlashDspCharBuf[DER_PORT/4])         .byte[DER_PORT%4]   
#define  cF_FID                 GET_LONGFIELD(&FlashDspCharBuf[FID_PORT/4])         .byte[FID_PORT%4]   
#define  cF_UND                 GET_LONGFIELD(&FlashDspCharBuf[UND_PORT/4])         .byte[UND_PORT%4]   

#define  cF_X0                  GET_LONGFIELD(&FlashDspCharBuf[X0_PORT/4])          .byte[X0_PORT%4]  
#define  cF_X1                  GET_LONGFIELD(&FlashDspCharBuf[X1_PORT/4])          .byte[X1_PORT%4] 
#define  cF_X2                  GET_LONGFIELD(&FlashDspCharBuf[X2_PORT/4])          .byte[X2_PORT%4]  
#define  cF_X3                  GET_LONGFIELD(&FlashDspCharBuf[X3_PORT/4])          .byte[X3_PORT%4]  
#define  cF_X4                  GET_LONGFIELD(&FlashDspCharBuf[X4_PORT/4])          .byte[X4_PORT%4]   
#define  cF_X5                  GET_LONGFIELD(&FlashDspCharBuf[X5_PORT/4])          .byte[X5_PORT%4]   
#define  cF_X6                  GET_LONGFIELD(&FlashDspCharBuf[X6_PORT/4])          .byte[X6_PORT%4]   
#define  cF_X7                  GET_LONGFIELD(&FlashDspCharBuf[X7_PORT/4])          .byte[X7_PORT%4]   
//////TEST

////out test
#define  cF_OP                  GET_LONGFIELD(&FlashDspCharBuf[OP_PORT/4])          .byte[OP_PORT%4]
#define  cF_CL                  GET_LONGFIELD(&FlashDspCharBuf[CL_PORT/4])          .byte[CL_PORT%4]
#define  cF_OP_S                GET_LONGFIELD(&FlashDspCharBuf[S_OP_PORT/4])        .byte[S_OP_PORT%4]
#define  cF_CL_S                GET_LONGFIELD(&FlashDspCharBuf[S_CL_PORT/4])        .byte[S_CL_PORT%4]
#define  cF_BK2                 GET_LONGFIELD(&FlashDspCharBuf[BK2_PORT/4])         .byte[BK2_PORT%4]
#define  cF_D_S                 GET_LONGFIELD(&FlashDspCharBuf[D_S_PORT/4])         .byte[D_S_PORT%4]
#define  cF_GBR                 GET_LONGFIELD(&FlashDspCharBuf[GBR_PORT/4])         .byte[GBR_PORT%4]
#define  cF_BRK                 GET_LONGFIELD(&FlashDspCharBuf[BK1_PORT/4])         .byte[BK1_PORT%4]
 
                                
#define  cF_FAN                 GET_LONGFIELD(&FlashDspCharBuf[FAN_PORT/4])         .byte[FAN_PORT%4]
#define  cF_LIT                 GET_LONGFIELD(&FlashDspCharBuf[LIT_PORT/4])         .byte[LIT_PORT%4]
#define  cF_BUZ                 GET_LONGFIELD(&FlashDspCharBuf[BUZ_PORT/4])         .byte[BUZ_PORT%4]
#define  cF_BELL                GET_LONGFIELD(&FlashDspCharBuf[BELL_PORT/4])        .byte[BELL_PORT%4]
#define  cF_RST                 GET_LONGFIELD(&FlashDspCharBuf[RST_PORT/4])         .byte[RST_PORT%4]
#define  cF_ERR                 GET_LONGFIELD(&FlashDspCharBuf[ERR_PORT/4])         .byte[ERR_PORT%4]
#define  cF_HOP                 GET_LONGFIELD(&FlashDspCharBuf[HOP_PORT/4])         .byte[HOP_PORT%4]
#define  cF_HCL                 GET_LONGFIELD(&FlashDspCharBuf[HCL_PORT/4])         .byte[HCL_PORT%4]

#define  cF_UP                  GET_LONGFIELD(&FlashDspCharBuf[UP_PORT/4])          .byte[UP_PORT%4]
#define  cF_DN                  GET_LONGFIELD(&FlashDspCharBuf[DN_PORT/4])          .byte[DN_PORT%4]
#define  cF_P1                  GET_LONGFIELD(&FlashDspCharBuf[P1_PORT/4])          .byte[P1_PORT%4]
#define  cF_P2                  GET_LONGFIELD(&FlashDspCharBuf[P2_PORT/4])          .byte[P2_PORT%4]
#define  cF_P3                  GET_LONGFIELD(&FlashDspCharBuf[P3_PORT/4])          .byte[P3_PORT%4]
#define  cF_P4                  GET_LONGFIELD(&FlashDspCharBuf[P4_PORT/4])          .byte[P4_PORT%4]
#define  cF_DAC                 GET_LONGFIELD(&FlashDspCharBuf[DAC_PORT/4])         .byte[DAC_PORT%4]




/////speed/////////
#define  cF_MANUALSPEED         GET_LONGFIELD(&FlashDspCharBuf[F_ManualSpeed/4])  .byte[F_ManualSpeed%4]
#define  cF_BATTERYSPEED        GET_LONGFIELD(&FlashDspCharBuf[F_BatterySpeed/4]) .byte[F_BatterySpeed%4]
#define  cF_DECREASESPEED       GET_LONGFIELD(&FlashDspCharBuf[F_DecreaseSpeed/4]).byte[F_DecreaseSpeed%4]
#define  cF_ETC1SPEED           GET_LONGFIELD(&FlashDspCharBuf[F_Etc1Speed/4])    .byte[F_Etc1Speed%4]
#define  cF_ETC2SPEED           GET_LONGFIELD(&FlashDspCharBuf[F_Etc2Speed/4])    .byte[F_Etc2Speed%4]
#define  cF_FHMSPEED            GET_LONGFIELD(&FlashDspCharBuf[F_FhmSpeed/4])     .byte[F_FhmSpeed%4]
#define  cF_SPEED30             GET_LONGFIELD(&FlashDspCharBuf[F_Speed30/4])      .byte[F_Speed30%4]
#define  cF_SPEED45             GET_LONGFIELD(&FlashDspCharBuf[F_Speed45/4])      .byte[F_Speed45%4]
#define  cF_SPEED60             GET_LONGFIELD(&FlashDspCharBuf[F_Speed60/4])      .byte[F_Speed60%4]
#define  cF_SPEED90             GET_LONGFIELD(&FlashDspCharBuf[F_Speed90/4])      .byte[F_Speed90%4]
#define  cF_SPEED105            GET_LONGFIELD(&FlashDspCharBuf[F_Speed105/4])     .byte[F_Speed105%4]
#define  cF_SPEED120            GET_LONGFIELD(&FlashDspCharBuf[F_Speed120/4])     .byte[F_Speed120%4]
#define  cF_SPEED150            GET_LONGFIELD(&FlashDspCharBuf[F_Speed150/4])     .byte[F_Speed150%4]
#define  cF_SPEED180            GET_LONGFIELD(&FlashDspCharBuf[F_Speed180/4])     .byte[F_Speed180%4]
#define  cF_SPEED210            GET_LONGFIELD(&FlashDspCharBuf[F_Speed210/4])     .byte[F_Speed210%4]
////////////////




#define  cF_FLRDSPCH(adr)           GET_LONGFIELD(&FlashDspCharBuf[adr/4])      .byte[adr%4]
#define  iF_FLRDSPCH(adr)           GET_LONGFIELD(&FlashDspCharBuf[adr/4])      .intger[(adr%4)/2]

#define  b_LdTmpBufRam(adr)         GET_LONGFIELD(&parameter_mirror[(adr%64)/4]).byte[adr%4]

#define  i_LdTmpBufRam(adr)         GET_LONGFIELD(&parameter_mirror[(adr%64)/4]).intger[(adr%4)/2]
#define  l_LdTmpBufRam(adr)         GET_LONGFIELD(&parameter_mirror[adr]).long_data



#define  bitChk_FLRDSPCH(adr,bitnm)         (cF_FLRDSPCH(adr) & ((0x01) << (bitnm)))

#define  bit_LdTmpBufRamSet(adr,bitnm)      b_LdTmpBufRam(adr)=(b_LdTmpBufRam(adr)  | ((0x01) << bitnm))
#define  bit_LdTmpBufRamReset(adr,bitnm)    b_LdTmpBufRam(adr)=(b_LdTmpBufRam(adr)  & ~((0x01) << bitnm))




#define  IN_SU1                 CurSelPortIn(cF_SU1)
#define  IN_SD1                 CurSelPortIn(cF_SD1)  
#define  IN_SFT                 CurSelPortIn(cF_SFT)  
#define  IN_OVL                 CurSelPortIn(cF_OVL)  
#define  IN_ULS                 CurSelPortIn(cF_ULS)   
#define  IN_DLS                 CurSelPortIn(cF_DLS)   
#define  IN_LU                  CurSelPortIn(cF_LU)   
#define  IN_LD                  CurSelPortIn(cF_LD)   

#define  IN_EMG                 CurSelPortIn(cF_EMG) 
#define  IN_PRK                 CurSelPortIn(cF_PRK)  
#define  IN_AUTO                CurSelPortIn(cF_AUTO)  
#define  IN_U_B                 CurSelPortIn(cF_U_B)  
#define  IN_D_B                 CurSelPortIn(cF_D_B)   
#define  IN_OP_E                CurSelPortIn(cF_OP_E)   
#define  IN_CL_E                CurSelPortIn(cF_CL_E)   //GS   
#define  IN_HL_D                CurSelPortIn(cF_HL_D)   //DS


#define  IN_GR                  CurSelPortIn(cF_GR) 
#define  IN_BAT                 CurSelPortIn(cF_BAT)  
#define  IN_PASS                CurSelPortIn(cF_PASS)  
#define  IN_FIRE                CurSelPortIn(cF_FIRE)  
#define  IN_WATER               CurSelPortIn(cF_WATER)   
#define  IN_FULL                CurSelPortIn(cF_FULL)   
#define  IN_MM                  CurSelPortIn(cF_MM)   
#define  IN_FHM                 CurSelPortIn(cF_FHM)   
	
#define  IN_FR1                 CurSelPortIn(cF_FR1) 
#define  IN_FR2                 CurSelPortIn(cF_FR2)  
#define  IN_GS2                 CurSelPortIn(cF_GS2)  
#define  IN_DS2                 CurSelPortIn(cF_DS2)  
#define  IN_SU2                 CurSelPortIn(cF_SU2)   
#define  IN_SD2                 CurSelPortIn(cF_SD2)   
#define  IN_BM                  CurSelPortIn(cF_BM)   
#define  IN_INV                 CurSelPortIn(cF_INV)   

#define  IN_FS0                 CurSelPortIn(cF_FS0) 
#define  IN_FS1                 CurSelPortIn(cF_FS1)  
#define  IN_FS2                 CurSelPortIn(cF_FS2)  
#define  IN_FS3                 CurSelPortIn(cF_FS3)  
#define  IN_FS4                 CurSelPortIn(cF_FS4)   
#define  IN_DER                 CurSelPortIn(cF_DER)   
#define  IN_FID                 CurSelPortIn(cF_FID)   
#define  IN_UND1                CurSelPortIn(cF_UND)   

#define  IN_X0                  CurSelPortIn(cF_X0)  
#define  IN_X1                  CurSelPortIn(cF_X1) 
#define  IN_X2                  CurSelPortIn(cF_X2)  
#define  IN_X3                  CurSelPortIn(cF_X3)  
#define  IN_X4                  CurSelPortIn(cF_X4)   
#define  IN_X5                  CurSelPortIn(cF_X5)   
#define  IN_X6                  CurSelPortIn(cF_X6)   
#define  IN_X7                  CurSelPortIn(cF_X7)   






#define  OUT_U_W(x)            CurSelOutPort(cF_UP,x) 
#define  OUT_D_W(x)            CurSelOutPort(cF_DN,x)  
#define  OUT_P1(x)             CurSelOutPort(cF_P1,x)  
#define  OUT_P2(x)             CurSelOutPort(cF_P2,x)  
#define  OUT_P3(x)             CurSelOutPort(cF_P3,x)   
#define  OUT_P4(x)             CurSelOutPort(cF_P4,x)   
#define  OUT_DAC(x)            CurSelOutPort(cF_DAC,x)   

#define  OUT_OP(x)              CurSelOutPort(cF_OP,x) 
#define  OUT_CL(x)              CurSelOutPort(cF_CL,x)  
#define  OUT_OP_S(x)            CurSelOutPort(cF_OP_S,x)   
#define  OUT_CL_S(x)            CurSelOutPort(cF_CL_S,x)
#define  OUT_BK2(x)             CurSelOutPort(cF_BK2,x)  
#define  OUT_D_S(x)             CurSelOutPort(cF_D_S,x)  
#define  OUT_GBR(x)             CurSelOutPort(cF_GBR,x)   
#define  OUT_BRK(x)             CurSelOutPort(cF_BRK,x)   

#define  OUT_FAN(x)             CurSelOutPort(cF_FAN,x)  
#define  OUT_LIT(x)             CurSelOutPort(cF_LIT,x)  
#define  OUT_BUZ(x)             CurSelOutPort(cF_BUZ,x)   
#define  OUT_BELL(x)            CurSelOutPort(cF_BELL,x)
#define  OUT_RST(x)             CurSelOutPort(cF_RST,x)
#define  OUT_ERR(x)             CurSelOutPort(cF_ERR,x)
#define  OUT_HOP(x)             CurSelOutPort(cF_HOP,x)
#define  OUT_HCL(x)             CurSelOutPort(cF_HCL,x)




extern  UserDataType    EmgByte;
extern  UserDataType    Su1Byte;
extern  UserDataType    GrByte;
extern  UserDataType    FireByte;
extern  UserDataType    Fs_Byte;
extern  UserDataType    X0Byte;

extern  UserDataType    BefEmgByte;
extern  UserDataType    BefSu1Byte;
extern  UserDataType    BefGrByte;
extern  UserDataType    BefFireByte;
extern	UserDataType    BefFs_Byte;
extern  UserDataType    BefX0Byte;


#define  IN_EMG_IN            GET_BITFIELD(&EmgByte).bit0 
#define  IN_PRK_IN            GET_BITFIELD(&EmgByte).bit1  
#define  IN_AUTO_IN           GET_BITFIELD(&EmgByte).bit2  
#define  IN_U_B_IN            GET_BITFIELD(&EmgByte).bit3  
#define  IN_D_B_IN            GET_BITFIELD(&EmgByte).bit4   
#define  IN_OP_E_IN           GET_BITFIELD(&EmgByte).bit5   
#define  IN_CL_E_IN           GET_BITFIELD(&EmgByte).bit6   
#define  IN_HL_D_IN           GET_BITFIELD(&EmgByte).bit7   

#define  IN_SU1_IN            GET_BITFIELD(&Su1Byte).bit0 
#define  IN_SD1_IN            GET_BITFIELD(&Su1Byte).bit1  
#define  IN_SFT_IN            GET_BITFIELD(&Su1Byte).bit2  
#define  IN_OVL_IN            GET_BITFIELD(&Su1Byte).bit3  
#define  IN_ULS_IN            GET_BITFIELD(&Su1Byte).bit4   
#define  IN_DLS_IN            GET_BITFIELD(&Su1Byte).bit5   
#define  IN_LU_IN             GET_BITFIELD(&Su1Byte).bit6   
#define  IN_LD_IN             GET_BITFIELD(&Su1Byte).bit7   


#define  IN_GR_IN             GET_BITFIELD(&GrByte).bit0 
#define  IN_BAT_IN            GET_BITFIELD(&GrByte).bit1  
#define  IN_PASS_IN           GET_BITFIELD(&GrByte).bit2  
#define  IN_FIRE_IN           GET_BITFIELD(&GrByte).bit3  
#define  IN_WATER_IN          GET_BITFIELD(&GrByte).bit4   
#define  IN_FULL_IN           GET_BITFIELD(&GrByte).bit5   
#define  IN_MM_IN             GET_BITFIELD(&GrByte).bit6   
#define  IN_FHM_IN            GET_BITFIELD(&GrByte).bit7   

#define  IN_FR1_IN            GET_BITFIELD(&FireByte).bit0 
#define  IN_FR2_IN            GET_BITFIELD(&FireByte).bit1  
#define  IN_GS2_IN            GET_BITFIELD(&FireByte).bit2  
#define  IN_DS2_IN            GET_BITFIELD(&FireByte).bit3  
#define  IN_SU2_IN            GET_BITFIELD(&FireByte).bit4   
#define  IN_SD2_IN            GET_BITFIELD(&FireByte).bit5   
#define  IN_BM_IN             GET_BITFIELD(&FireByte).bit6   
#define  IN_INV_IN            GET_BITFIELD(&FireByte).bit7   

#define  IN_FS0_IN            GET_BITFIELD(&Fs_Byte).bit0 
#define  IN_FS1_IN            GET_BITFIELD(&Fs_Byte).bit1  
#define  IN_FS2_IN            GET_BITFIELD(&Fs_Byte).bit2  
#define  IN_FS3_IN            GET_BITFIELD(&Fs_Byte).bit3  
#define  IN_FS4_IN            GET_BITFIELD(&Fs_Byte).bit4   
#define  IN_DER_IN            GET_BITFIELD(&Fs_Byte).bit5   
#define  IN_FID_IN            GET_BITFIELD(&Fs_Byte).bit6   
#define  IN_UND1_IN           GET_BITFIELD(&Fs_Byte).bit7   


#define  IN_X0_IN             GET_BITFIELD(&X0Byte).bit0  
#define  IN_X1_IN             GET_BITFIELD(&X0Byte).bit1 
#define  IN_X2_IN             GET_BITFIELD(&X0Byte).bit2  
#define  IN_X3_IN             GET_BITFIELD(&X0Byte).bit3  
#define  IN_X4_IN             GET_BITFIELD(&X0Byte).bit4   
#define  IN_X5_IN             GET_BITFIELD(&X0Byte).bit5   
#define  IN_X6_IN             GET_BITFIELD(&X0Byte).bit6   
#define  IN_X7_IN             GET_BITFIELD(&X0Byte).bit7   


#define  BEF_IN_EMG_IN            GET_BITFIELD(&BefEmgByte).bit0 
#define  BEF_IN_PRK_IN            GET_BITFIELD(&BefEmgByte).bit1  
#define  BEF_IN_AUTO_IN           GET_BITFIELD(&BefEmgByte).bit2  
#define  BEF_IN_U_B_IN            GET_BITFIELD(&BefEmgByte).bit3  
#define  BEF_IN_D_B_IN            GET_BITFIELD(&BefEmgByte).bit4   
#define  BEF_IN_OP_E_IN           GET_BITFIELD(&BefEmgByte).bit5   
#define  BEF_IN_CL_E_IN           GET_BITFIELD(&BefEmgByte).bit6   
#define  BEF_IN_HL_D_IN           GET_BITFIELD(&BefEmgByte).bit7   

#define  BEF_IN_SU1_IN            GET_BITFIELD(&BefSu1Byte).bit0 
#define  BEF_IN_SD1_IN            GET_BITFIELD(&BefSu1Byte).bit1  
#define  BEF_IN_SFT_IN            GET_BITFIELD(&BefSu1Byte).bit2  
#define  BEF_IN_OVL_IN            GET_BITFIELD(&BefSu1Byte).bit3  
#define  BEF_IN_ULS_IN            GET_BITFIELD(&BefSu1Byte).bit4   
#define  BEF_IN_DLS_IN            GET_BITFIELD(&BefSu1Byte).bit5   
#define  BEF_IN_LU_IN             GET_BITFIELD(&BefSu1Byte).bit6   
#define  BEF_IN_LD_IN             GET_BITFIELD(&BefSu1Byte).bit7   


#define  BEF_IN_GR_IN             GET_BITFIELD(&BefGrByte).bit0 
#define  BEF_IN_BAT_IN            GET_BITFIELD(&BefGrByte).bit1  
#define  BEF_IN_PASS_IN           GET_BITFIELD(&BefGrByte).bit2  
#define  BEF_IN_FIRE_IN           GET_BITFIELD(&BefGrByte).bit3  
#define  BEF_IN_WATER_IN          GET_BITFIELD(&BefGrByte).bit4   
#define  BEF_IN_FULL_IN           GET_BITFIELD(&BefGrByte).bit5   
#define  BEF_IN_MM_IN             GET_BITFIELD(&BefGrByte).bit6   
#define  BEF_IN_FHM_IN            GET_BITFIELD(&BefGrByte).bit7   

#define  BEF_IN_FR1_IN            GET_BITFIELD(&BefFireByte).bit0 
#define  BEF_IN_FR2_IN            GET_BITFIELD(&BefFireByte).bit1  
#define  BEF_IN_GS2_IN            GET_BITFIELD(&BefFireByte).bit2  
#define  BEF_IN_DS2_IN            GET_BITFIELD(&BefFireByte).bit3  
#define  BEF_IN_SU2_IN            GET_BITFIELD(&BefFireByte).bit4   
#define  BEF_IN_SD2_IN            GET_BITFIELD(&BefFireByte).bit5   
#define  BEF_IN_BM_IN             GET_BITFIELD(&BefFireByte).bit6   
#define  BEF_IN_INV_IN            GET_BITFIELD(&BefFireByte).bit7   

#define  BEF_IN_FS0_IN            GET_BITFIELD(&BefFs_Byte).bit0 
#define  BEF_IN_FS1_IN            GET_BITFIELD(&BefFs_Byte).bit1  
#define  BEF_IN_FS2_IN            GET_BITFIELD(&BefFs_Byte).bit2  
#define  BEF_IN_FS3_IN            GET_BITFIELD(&BefFs_Byte).bit3  
#define  BEF_IN_FS4_IN            GET_BITFIELD(&BefFs_Byte).bit4   
#define  BEF_IN_DER_IN            GET_BITFIELD(&BefFs_Byte).bit5   
#define  BEF_IN_FID_IN            GET_BITFIELD(&BefFs_Byte).bit6   
#define  BEF_IN_UND1_IN           GET_BITFIELD(&BefFs_Byte).bit7   


#define  BEF_IN_X0_IN             GET_BITFIELD(&BefX0Byte).bit0  
#define  BEF_IN_X1_IN             GET_BITFIELD(&BefX0Byte).bit1 
#define  BEF_IN_X2_IN             GET_BITFIELD(&BefX0Byte).bit2  
#define  BEF_IN_X3_IN             GET_BITFIELD(&BefX0Byte).bit3  
#define  BEF_IN_X4_IN             GET_BITFIELD(&BefX0Byte).bit4   
#define  BEF_IN_X5_IN             GET_BITFIELD(&BefX0Byte).bit5   
#define  BEF_IN_X6_IN             GET_BITFIELD(&BefX0Byte).bit6   
#define  BEF_IN_X7_IN             GET_BITFIELD(&BefX0Byte).bit7   




#define  FhmOnOffChk                        bitChk_FLRDSPCH(F_OnOff0,(bFhmOnOff % 8))
#define  DoorJumperChkOnOffChk              bitChk_FLRDSPCH(F_OnOff0,(bDoorJumperOff % 8))
#define  EncoderPhaseChk                    bitChk_FLRDSPCH(F_OnOff0,(bEncoderPhase % 8))
#define  WardPriorityChk                    bitChk_FLRDSPCH(F_OnOff0,(bWardPriority % 8))
#define  NonStopOnOffChk                    bitChk_FLRDSPCH(F_OnOff0,(bNonStop % 8))
#define  OpenTotalUseChk                    bitChk_FLRDSPCH(F_OnOff0,(bOpenTotalOnOff % 8))
#define  CloseTotalUseChk                   bitChk_FLRDSPCH(F_OnOff0,(bCloseTotalOnOff % 8))
#define  OpenWaitUseChk                     bitChk_FLRDSPCH(F_OnOff0,(bOpenWaitToTalOnOff % 8))


#define  CarDoor1UseChk                     bitChk_FLRDSPCH(F_OnOff1,(bCarDoor1Use % 8))
#define  CarDoor2UseChk                     bitChk_FLRDSPCH(F_OnOff1,(bCarDoor2Use % 8))
#define  HoleDoor1UseChk                    bitChk_FLRDSPCH(F_OnOff1,(bHoleDoor1Use % 8))
#define  HoleDoor2UseChk                    bitChk_FLRDSPCH(F_OnOff1,(bHoleDoor2Use % 8))
#define  SubSafetyUseChk                    bitChk_FLRDSPCH(F_OnOff1,(bSubSafety % 8))
#define  BrkMgtUseChk                       bitChk_FLRDSPCH(F_OnOff1,(bBrkMgtUse % 8))
#define  EncoderUseChk                      bitChk_FLRDSPCH(F_OnOff1,(bEncoderUse % 8))
#define  RelevelUseChk                      bitChk_FLRDSPCH(F_OnOff1,(bRelevelOnOff % 8))

#define  OilLopeTypeChk                     bitChk_FLRDSPCH(F_OnOff2,(bOilLopeTypeChk % 8))
#define  OnlyOneCallOnOffChk                bitChk_FLRDSPCH(F_OnOff2,(bOnlyOneCall % 8))
#define  ManualSusChk                       bitChk_FLRDSPCH(F_OnOff2,(bManualSusChk % 8))
#define  BrkOpenUseChk                      bitChk_FLRDSPCH(F_OnOff2,(bBrkOpenUse % 8))
#define  KidsKeyChkUse                      bitChk_FLRDSPCH(F_OnOff2,(bKidsKeyChkUse % 8))
#define  CarKeyFirstService                 bitChk_FLRDSPCH(F_OnOff2,(bCarKeyFirstService % 8))
#define  FamilyService                      bitChk_FLRDSPCH(F_OnOff2,(bFamilyService % 8))
#define  OpenOutSet                         bitChk_FLRDSPCH(F_OnOff2,(bOpenOutSet % 8))



#define  SafetyValidLR                      bitChk_FLRDSPCH(F_OnOff3,(bSafetyValidLR % 8))
#define  FloorSelMethod                     bitChk_FLRDSPCH(F_OnOff3,(bFloorSel % 8))
#define  RunningOpenOnOff                   bitChk_FLRDSPCH(F_OnOff3,(bRunOpenSetClear % 8))
//#define  CrtHibUse485                       bitChk_FLRDSPCH(F_OnOff3,(bCrtHib % 8))

/////////////////////////////////////////////////////////////////////////////////////////
#define  ManWorkingChk                      bitChk_FLRDSPCH(F_OnOff3,(bManWorkingChk % 8))



#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)


#ifdef	TEST_SIMULATION
extern  UserDataType    MotorMoveTime;
#endif


//#define     GOBERNOR_LOCK	1

