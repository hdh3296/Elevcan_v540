

#include  "..\..\system_com\memory_map.h"
#include  "iomap.h"
#include  "COM.h"



//#define OFFICE  1


        
/*??????????????
mpm
rpm
encoder
high speed
light
????????????????*/


#define DISABLE_INTERRUPTS 	asm("push SR \n bset SR,#7 \n bset SR,#6 \n	bclr	SR,#5")
#define ENABLE_INTERRUPTS	asm("pop SR")


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
#define  END_RAM_LONG           45
#define  MAX_LONG_BUF           END_RAM_LONG


////////////////////////////////////////////
#define     SUBWAY_LIGHT            1
#define     NORMAL_LIGHT            2
#define     FIRE_LIGHT              NORMAL_LIGHT
////////////////////////////////////////////

////////////////////////////////////////////
#define     LIGHT_A            1
#define     LIGHT_B            2
#define     LIGHT_AB           LIGHT_A
////////////////////////////////////////////

////////////////////////////////////////////
#define     LG_INVERTER_ELEV        1
#define     IO_INVERTER             2
#define     RUN_MODE                LG_INVERTER_ELEV
////////////////////////////////////////////

#define     SET_ELEV_SPEED_PER_MIM      120   //90   //120
#define     SET_ENCODER_PULSE           8192  //8192 //8192    //600   //office
#define     SET_MOTOR_RPM               186   //150  //186     //600

//ELEV_SPEED_PER_MIM; //90;    //120;   //45    //45   m/min
//ENCODER_PULSE;      //8192;  //8192;  //1024  //8192 pulse/rotate
//MOTOR_RPM;          //150;   //186;   //1100  //74   r/min

////////////////////////////////////////////

#define     SPEED_30                0
#define     SPEED_45                1
#define     SPEED_60                2
#define     SPEED_90                3
#define     SPEED_105               4
#define     SPEED_120               5 
#define     SPEED_150               6 
#define     SPEED_180               7 
#define     SPEED_210               8 
////////////////////////////////////////////
////////////////////////////////////////////

#define     SPEED_30_DEC_LENGTH     500                 //mm
#define     SPEED_45_DEC_LENGTH     800                 //mm
#define     SPEED_60_DEC_LENGTH     1200                 //1500     //970                 //1200        //mm
#define     SPEED_90_DEC_LENGTH     1900                //1800        //mm    
#define     SPEED_105_DEC_LENGTH    1900                //2150  //2100        //mm
#define     SPEED_120_DEC_LENGTH    2800                //mm
#define     SPEED_150_DEC_LENGTH    3000                //mm
#define     SPEED_180_DEC_LENGTH    3600                //mm
#define     SPEED_210_DEC_LENGTH    3900                //mm

////////////////////////////////////////////
/*
#define     SPEED_60_VALID_DIS      180
#define     SPEED_90_VALID_DIS      380
#define     SPEED_105_VALID_DIS     410
#define     SPEED_120_VALID_DIS     450 
#define     SPEED_150_VALID_DIS     500 
#define     SPEED_180_VALID_DIS     550 
#define     SPEED_210_VALID_DIS     600 
*/
////////////////////////////////////////////

/*
////////////////////////////////////////////
//#define     SPEED_60_DEC_PULSE      700; //office
//#define     SPEED_60_DEC_PULSE      1500;//daejeun

#define     SPEED_60_DEC_PULSE      2800  //yangi

#define     SPEED_90_DEC_PULSE      SPEED_60_DEC_PULSE + (SPEED_60_DEC_PULSE/(unsigned long)2)
#define     SPEED_105_DEC_PULSE     SPEED_90_DEC_PULSE + (SPEED_90_DEC_PULSE/(unsigned long)2)
#define     SPEED_120_DEC_PULSE     SPEED_60_DEC_PULSE * 2      
#define     SPEED_150_DEC_PULSE            
#define     SPEED_180_DEC_PULSE     5 
#define     SPEED_210_DEC_PULSE     6 
////////////////////////////////////////////
*/

#define     bFHM_ONOFF               0
#define     bLIGHT_NCNO              1
#define     bDOOR_JMP_CHK            2
#define     bNonService00            3                        
#define     bNonService01            4                             
#define     bNonService02            5                             
#define     bNonService03            6                           
#define     bNonService04            7                            
#define     bNonService05            8                             
#define     bNonService06            9                             
#define     bNonService07            10                           
#define     bNonService08            11                       
#define     bNonService09            12                            
#define     bNonService10            13                            
#define     bNonService11            14                          
#define     bNonService12            15                           
#define     bNonService13            16                            
#define     bNonService14            17                            
#define     bNonService15            18                           
#define     bNonService16            19                        
#define     bNonService17            20                             
#define     bNonService18            21                             
#define     bNonService19            22                           
#define     bNonService20            23                            
#define     bNonService21            24                             
#define     bNonService22            25                             
#define     bNonService23            26                           
#define     bNonService24            27                       
#define     bNonService25            28                            
#define     bNonService26            29                            
#define     bNonService27            30                          
#define     bNonService28            31                           
#define     bNonService29            32                            
#define     bNonService30            33                            
#define     bNonService31            34                           



#define     START_FLOOR             0

                                            
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

                                             

#define	    OPEN_AND_WAIT_TIME  	40
#define     OPEN_TOTAL_TIME     	70
#define	    CLOSE_TOTAL_TIME  		70
#define	    REOPEN_CHK_TIME   		3

#define	    BASE_NEXT_FLR_TIME 		200

#define	    BASE_LULD_OFF_TIME 		30

         

#define  	VERSION_0         		'0'
#define  	VERSION_1         		'0'
#define  	VERSION_2         		'2'


				


/*
extern volatile unsigned int SR __attribute__((__near__));
typedef struct tagSRBITS {
        unsigned C      :1;     
        unsigned Z      :1;     
        unsigned OV     :1;        
        unsigned N      :1;     
        unsigned RA     :1;     
        unsigned IPL    :3;     
        unsigned DC     :1;     
        unsigned DA     :1;     
        unsigned SAB    :1;     
        unsigned OAB    :1;         
        unsigned SB     :1;     
        unsigned SA     :1;     
        unsigned OB     :1;     
        unsigned OA     :1;     
} SRBITS;
extern volatile SRBITS SRbits __attribute__((__near__));
*/



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

        
/*
#define  STAT_UPDN_ON      0x00              
#define  STAT_UP_OFF       0x01              
#define  STAT_DN_OFF       0x02              
#define  STAT_UPDN_OFF     0x03              


#define  CAR_MOVE_DFLT   0x00
#define  CAR_UP_READY    0x01
#define  CAR_UP_RUN      0x02
#define  CAR_DN_READY    0x03
#define  CAR_DN_RUN      0x04
#define  CAR_STOP_READY  0x05
#define  CAR_STOP        0x06
*/


#define     NO_FIRE     0
#define     FIRE_START  1
#define     FIRE_ONE    2
#define     FIRE_TWO    3
#define     FIRE_THREE  4
//#define     FIRE_FOUR   5
//#define     FIRE_FIVE   6



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
#define  sI_C_N_FLR           1
#define  sEMERGENCY           2
#define  sLOPE_BRK            3
#define  sSLIP                4
#define  sULS                 5
#define  sDLS                 6
#define  sLULD_NO_OFF         7
#define  sNEXT_FLOOR          8
#define  sDEST_FLOOR          9
#define  sHDS_NO_ON           10
#define  sCLE_NO_ON           11
#define  sHDS_RUN_OFF         12
#define  sCLE_RUN_OFF         13
#define  sLULD_HOME           14
#define  sOVL                 15
#define  sPARKING             16   
#define  sFireOn              17         
#define  sWaterSense          18         
#define  sOPE_NO_ON           19                                                                            
#define  sDOOR_JUMPER         20
#define  sVIP                 21
#define  sFHM_MODE			  22
#define  sMANUAL_UP           23         
#define  sMANUAL_DN           24         
#define  sMANUAL              25         
#define  sSFT                 26
#define  sOPEN                27
#define  sCLOSE               28         
#define  sUP                  29         
#define  sDN                  30         
#define  sSLOW_SPEED          31         
#define  sWAIT_LULD           32         
#define  sSTOP                33        
#define  sHOME                34         
#define  sREADY               35         
//#define  sPOWER_FAIL          36         


//extern	unsigned 		char		SubDoorFlrChk(void);

//#define  EERE 		0
//#define  EEWE		1
//#define  EEMWE    	2
//#define  EERIE    	3


/////////////////////////block1////////////////////////////////////

#define  F_SETUP_BASE_ADDR      0

#define  F_FlrDspCh             F_SETUP_BASE_ADDR      // 0    0-15

/////////////////////////block2////////////////////////////////////
//floor group
#define  F_TopFlr               64                     //1     16
#define  F_PrkFlr               65                     //1
#define  F_FixFloor             66                     //1
#define  F_FireSafeFlr          67                     //1

#define  F_SubDoorFlr1          68                     //1     17
#define  F_SubDoorFlr2          69                     //1
#define  F_SubDoorFlr3          70                     //1
#define  F_X7SafeFlr            71                     //1
                                
#define  F_StartFloor           72                     //1     18
#define  NC_F_Floor1            73                     //1  
#define  NC_F_Floor2            74                     //1  
#define  NC_F_Floor3            75                     //1  
                                  
#define  NC_F_Floor4            76                       //1    31
#define  NC_F_Floor5            77                       //1
#define  NC_F_Floor6            78                       //1
#define  NC_F_Floor7            79                       //1

//timer group
#define  F_OpWtTm               80                     //1     19
#define  F_OpTtTm               81                     //1
#define  F_FixFloorTime         82                     //1
#define  F_NextFlrTime          83                     //1     

#define  F_LuLdOffTime          84                     //1     20
#define  F_FanTime              85                     //1
#define  F_LightTime            86                     //1
#define  NC_F_Time1             87                     //1

#define  NC_F_Time2             88                     //1     21
#define  NC_F_Time3             89                     //1
#define  NC_F_Time4             90                     //1  
#define  NC_F_Time5             91                     //1

#define  F_StTm1                92                     //1     22
#define  F_StTm2                93                     //1
#define  F_StTm3                94                     //1  
#define  F_StTm4                95                     //1

#define  F_BrkStTm11            96                     //1(2)  23
#define  F_BrkStTm10            97                     //1(2)
#define  F_BrkStTm21            98                     //1(2)  
#define  F_BrkStTm20            99                     //1(3)

#define  F_BrkStTm31            100                    //1(2)  24
#define  F_BrkStTm30            101                    //1(2)
#define  F_BrkStTm41            102                    //1(2)  
#define  F_BrkStTm40            103                    //1(3)

#define  F_BrkStTm51            104                     //1(2)  25
#define  F_BrkStTm50            105                     //1(2)
#define  F_BrkStTm61            106                     //1(2)  
#define  F_BrkStTm60            107                     //1(2)

//OnOff group
#define  F_NonService0          108                     //1    26    
#define  F_NonService1          109                     //1     
#define  F_NonService2          110                     //1     
#define  F_NonService3          111                     //1   

#define  F_NcNoBit0             112                     //1    27
#define  F_NcNoBit1             113                     //1
#define  F_NcNoBit2             114                     //1    
#define  F_NcNoBit3             115                     //1

#define  F_DoorJumperOff        116                     //1    28
#define  F_FhmOnOff             117                     //1
#define  NC_F_OnOff0            118                     //1
#define  NC_F_OnOff1            119                     //1
                                    
#define  NC_F_OnOff2            120                     //1     29
#define  NC_F_OnOff3            121                     //1
#define  NC_F_OnOff4            122                     //1
#define  NC_F_OnOff5            123                     //1

#define  NC_F_OnOff6            124                     //1     30
#define  NC_F_OnOff7            125                     //1
#define  NC_F_OnOff8            126                     //1
#define  NC_F_OnOff9            127                     //1
                    
/////////////////////////block3////////////////////////////////////
//i/o group                                             
#define  F_ManualSpeed          128                     //1    32
#define  F_BatterySpeed         129                     //1    
#define  F_DecreaseSpeed        130                     //1    
#define  F_Etc1Speed            131                     //1    

#define  F_Etc2Speed            132                     //1    33
#define  F_Etc3Speed            133                     //1    
#define  F_Speed30              134                     //1    
#define  F_Speed45              135                     //1    

#define  F_Speed60              136                     //1    34
#define  F_Speed90              137                     //1    
#define  F_Speed105             138                     //1    
#define  F_Speed120             139                     //1    

#define  F_Speed150             140                     //1    35
#define  F_Speed180             141                     //1    
#define  F_Speed210             142                     //1    
#define  F_ElevSpeed            143                     //1     

#define  F_Su1Sd1_Velocity      144                     //1    36
#define  F_Su2Sd2_Velocity      145                     //1     
#define  F_Su3Sd3_Velocity      146                     //1     
#define  NC_IO1                 146                     //1     

#define  NC_IO2                 147                     //1    37
#define  NC_IO3                 148                     //1     
#define  NC_IO4                 149                     //1     
#define  NC_IO5                 150                     //1     


//user group
#define  F_Ver0                 151                     //1    38
#define  F_Ver1                 152                     //1
#define  F_Ver2                 153                     //1
#define  F_Bd_Id                154                     //1

#define  F_Passward0            155                     //1    39
#define  F_Passward1            156                     //1
#define  F_Passward2            157                     //1
#define  F_Passward3            158                     //1

#define  F_SerialNm0            159                     //1(2) 40
#define  F_SerialNm1            160                     //1(2)
#define  F_UserLamp             161                     //1    
#define  F_ErrStopCnt           162                     //1 

#define  NC_F_user0             163                     //1    41
#define  NC_F_user1             164                     //1     
#define  NC_F_user2             165                     //1     
#define  NC_F_user3             166                     //1     


//wait   group
#define  F_0506                 167                     //1     42
#define  F_0607                 168                     //1     
#define  F_0708                 169                     //1     
#define  F_0809                 170                     //1     

#define  F_0910                 171                     //1     43
#define  F_1011                 172                     //1     
#define  F_1112                 173                     //1     
#define  F_1213                 174                     //1     

#define  F_1314                 175                     //1     44
#define  F_1415                 176                     //1     
#define  F_1516                 177                     //1     
#define  F_1617                 178                     //1     

#define  F_1718                 179                     //1     45
#define  F_1819                 180                     //1     
#define  F_1920                 181                     //1     
#define  F_2021                 182                     //1     





/*
#define  UP_FLR_0102_PULSE      0 
#define  UP_FLR_0203_PULSE      1
#define  UP_FLR_0304_PULSE      2
#define  UP_FLR_0405_PULSE      3
#define  UP_FLR_0506_PULSE      4
#define  UP_FLR_0607_PULSE      5
#define  UP_FLR_0708_PULSE      6
#define  UP_FLR_0809_PULSE      7
#define  UP_FLR_0910_PULSE      8 
#define  UP_FLR_1011_PULSE      9 
#define  UP_FLR_1112_PULSE      10
#define  UP_FLR_1213_PULSE      11
#define  UP_FLR_1314_PULSE      12
#define  UP_FLR_1415_PULSE      13
#define  UP_FLR_1516_PULSE      14
#define  UP_FLR_1617_PULSE      15
#define  UP_FLR_1718_PULSE      16
#define  UP_FLR_1819_PULSE      17
#define  UP_FLR_1920_PULSE      18
#define  UP_FLR_2021_PULSE      19
#define  UP_FLR_2122_PULSE      20
#define  UP_FLR_2223_PULSE      21
#define  UP_FLR_2324_PULSE      22
#define  UP_FLR_2425_PULSE      23
#define  UP_FLR_2526_PULSE      24
#define  UP_FLR_2627_PULSE      25
#define  UP_FLR_2728_PULSE      26
#define  UP_FLR_2829_PULSE      27
#define  UP_FLR_2930_PULSE      28
#define  UP_FLR_3031_PULSE      29
#define  UP_FLR_3132_PULSE      30
#define  UP_FLR_3233_PULSE      31


#define  DN_FLR_0100_PULSE      32 
#define  DN_FLR_0201_PULSE      33 
#define  DN_FLR_0302_PULSE      34
#define  DN_FLR_0403_PULSE      35
#define  DN_FLR_0504_PULSE      36
#define  DN_FLR_0605_PULSE      37
#define  DN_FLR_0706_PULSE      38
#define  DN_FLR_0807_PULSE      39
#define  DN_FLR_0908_PULSE      40
#define  DN_FLR_1009_PULSE      41
#define  DN_FLR_1110_PULSE      42
#define  DN_FLR_1211_PULSE      43
#define  DN_FLR_1312_PULSE      44
#define  DN_FLR_1413_PULSE      45
#define  DN_FLR_1514_PULSE      46
#define  DN_FLR_1615_PULSE      47
#define  DN_FLR_1716_PULSE      48
#define  DN_FLR_1817_PULSE      49
#define  DN_FLR_1918_PULSE      50
#define  DN_FLR_2019_PULSE      51
#define  DN_FLR_2120_PULSE      52
#define  DN_FLR_2221_PULSE      53
#define  DN_FLR_2322_PULSE      54
#define  DN_FLR_2423_PULSE      55
#define  DN_FLR_2524_PULSE      56
#define  DN_FLR_2625_PULSE      57
#define  DN_FLR_2726_PULSE      58
#define  DN_FLR_2827_PULSE      59
#define  DN_FLR_2928_PULSE      60
#define  DN_FLR_3039_PULSE      61
#define  DN_FLR_3130_PULSE      62
#define  DN_FLR_3231_PULSE      63
*/

#define  FLR_01_PULSE           0 //64 
#define  FLR_02_PULSE           1 //65
#define  FLR_03_PULSE           2 //66
#define  FLR_04_PULSE           3 //67
#define  FLR_05_PULSE           4 //68
#define  FLR_06_PULSE           5 //69
#define  FLR_07_PULSE           6 //70
#define  FLR_08_PULSE           7 //71
#define  FLR_09_PULSE           8 //72
#define  FLR_10_PULSE           9 //73
#define  FLR_11_PULSE           10 //74
#define  FLR_12_PULSE           11 //75
#define  FLR_13_PULSE           12 //76
#define  FLR_14_PULSE           13 //77
#define  FLR_15_PULSE           14 //78
#define  FLR_16_PULSE           15 //79
#define  FLR_17_PULSE           16 //80
#define  FLR_18_PULSE           17 //81
#define  FLR_19_PULSE           18 //82
#define  FLR_20_PULSE           19 //83
#define  FLR_21_PULSE           20 //84
#define  FLR_22_PULSE           21 //85
#define  FLR_23_PULSE           22 //86
#define  FLR_24_PULSE           23 //87
#define  FLR_25_PULSE           24 //88
#define  FLR_26_PULSE           25 //89
#define  FLR_27_PULSE           26 //90
#define  FLR_28_PULSE           27 //91
#define  FLR_29_PULSE           28 //92
#define  FLR_30_PULSE           29 //93
#define  FLR_31_PULSE           30 //94
#define  FLR_32_PULSE           31 //95


#define  ENCODER_PULSE          32 //96
#define  MPM                    33 //97
#define  RPM                    34 //98
#define  MPM_VARIABLE           35 //99
#define  MM_PULSE               36 //100
#define  DEC_PULSE_30           37 //101
#define  DEC_PULSE_45           38 //102
#define  DEC_PULSE_60           39 //103
#define  DEC_PULSE_90           40 //104
#define  DEC_PULSE_105          41 //105
#define  DEC_PULSE_120          42 //106
#define  DEC_PULSE_150          43 //107
#define  DEC_PULSE_180          44 //108
#define  DEC_PULSE_210          45 //109
#define  DEC_LENGTH_30          46 //110
#define  DEC_LENGTH_45          47 //111
#define  DEC_LENGTH_60          48 //112
#define  DEC_LENGTH_90          49 //113
#define  DEC_LENGTH_105         50 //114
#define  DEC_LENGTH_120         51 //115
#define  DEC_LENGTH_150         52 //116
#define  DEC_LENGTH_180         53 //117
#define  DEC_LENGTH_210         54 //118
#define  MIN_DEC_PULSE_30       55 //119
#define  MIN_DEC_PULSE_45       56 //120
#define  MIN_DEC_PULSE_60       57 //121
#define  MIN_DEC_PULSE_90       58 //122
#define  MIN_DEC_PULSE_105      59 //123
#define  MIN_DEC_PULSE_120      60 //124
#define  MIN_DEC_PULSE_150      61 //125
#define  MIN_DEC_PULSE_180      62 //126
#define  MIN_DEC_PULSE_210      63 //127




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


extern  UserDataType    TestLoop;
extern  UserDataType    TestIO;
extern  UserDataType    Test485;
extern  UserDataType    TestCan1;
extern  UserDataType    TestCan2;
extern  UserDataType    TestCnt;
extern  UserDataType    TestDip;



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
extern  UserDataType    VoiceTime;        
extern  UserDataType    FhmLoaderTime;        
extern  UserDataType    SirenTime;        
extern  UserDataType    UpBttonTime;
extern  UserDataType    DnBttonTime;
extern  UserDataType    CarStopTime;
extern  UserDataType    DoorCloseTime;
extern  UserDataType    DoorOpenOnTime;
extern  UserDataType    DoorCloseOnTime;
extern  UserDataType    msec10;
extern  UserDataType    sec1;
//unsigned	char    	MainLoopTime=0;

extern  UserDataType    EepTime;
//extern  UserDataType    LightTime;
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
extern  UserDataType    SerialLoopMaxTime;
extern  UserDataType    Runtime;
extern  UserDataType    FireBaseFloor;
extern  UserDataType    CurSpeed;
extern  UserDataType    OriginalHighFlr;
extern  UserDataType    OriginalLowFlr;
extern  UserDataType    OriginalDoor;
extern  UserDataType    OriginalStartFloor;


extern  unsigned	int    	    NextFloorTime;
extern  unsigned	int     	MinuteTime;
extern  unsigned	int   	    LuLdTime;
extern  unsigned	int   	    CounterTime;
extern  unsigned	int    	    DoorOpenTime;
extern  unsigned	int    	    LightTime;
extern  unsigned	int    	    AutoNoMoveTime;


extern  unsigned int   CAN_Buf[8];




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
extern  UserDataType    MyNc_Addr;

extern  UserDataType    SegData0;
extern  UserDataType    SegData1;
extern  UserDataType    SegData2;
extern  UserDataType    SegSel;


extern  UserDataType    you;
extern  UserDataType    errio;

/*
extern  unsigned	long    	TotalPulse;
extern  unsigned	long    	StopMinimumPulse;
extern  unsigned	long    	DecreasePulse;
extern  unsigned	long    	TmpFhmCounter1;
extern  unsigned	long    	TmpFhmCounter2;
extern  unsigned	long    	TmpMmPerMin;
extern  unsigned    long        DecreasePulse;
*/




extern unsigned long  parameter_mirror[MAX_LONG_BUF]; // __attribute__((aligned(MAX_LONG_BUF),far,section(".ram,r")));


extern long_field  FlashBuf[128]           __attribute__((aligned(128),section(".auto_psv,r")));
extern long_field  FlashDspCharBuf[128]    __attribute__((aligned(128) ,section(".auto_psv,r")));



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
#define  S3_CUR_KEY             GET_BITFIELD(&S3_STATE_bit).bit6
#define  S3_STOP1               GET_BITFIELD(&S3_STATE_bit).bit7

//#define  S4_TOPFLR              GET_BITFIELD(&S4_STATE_bit).bit0





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

#define  bsLuLdHome        	    GET_BITFIELD(&LuLdBit).bit0 
#define  bsDestFloor       	    GET_BITFIELD(&LuLdBit).bit1
#define  bFindBoard     	    GET_BITFIELD(&LuLdBit).bit2 
#define  bReOpen        	    GET_BITFIELD(&LuLdBit).bit3 
#define  bUpWard           	    GET_BITFIELD(&LuLdBit).bit4
#define  bDnWard        	    GET_BITFIELD(&LuLdBit).bit5 
#define  bCarStop          	    GET_BITFIELD(&LuLdBit).bit6 
#define  bCarErr        	    GET_BITFIELD(&LuLdBit).bit7


//#define  bOnceClr        	    GET_BITFIELD(&OpenEndBit).bit0 
#define  bCarStopNoRun     	    GET_BITFIELD(&OpenEndBit).bit1
#define  bTestKey       	    GET_BITFIELD(&OpenEndBit).bit2 
#define  bSlipCheckStart	    GET_BITFIELD(&OpenEndBit).bit3 
//#define  bCarClrKey   		    GET_BITFIELD(&OpenEndBit).bit4 
#define  bsLope         	    GET_BITFIELD(&OpenEndBit).bit5
#define  bBefbsEmergency   	    GET_BITFIELD(&OpenEndBit).bit6 
#define  bBefbsSlip     	    GET_BITFIELD(&OpenEndBit).bit7
 
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
#define  bCntOn         	    GET_BITFIELD(&EepRWBit).bit1
#define  bCntOnAct         	    GET_BITFIELD(&EepRWBit).bit2
#define  bDoorJumper            GET_BITFIELD(&EepRWBit).bit3
//#define  bPowerFail             GET_BITFIELD(&EepRWBit).bit4
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



#define  bSaveErrCnt            GET_BITFIELD(&Etc2Bit).bit0 
#define  bDoorOpen              GET_BITFIELD(&Etc2Bit).bit1 
#define  bDoorOpenEnd           GET_BITFIELD(&Etc2Bit).bit2
#define  bFR2Start              GET_BITFIELD(&Etc2Bit).bit3
#define  bIOError              	GET_BITFIELD(&Etc2Bit).bit4



#define  bOpenEnd               GET_BITFIELD(&DoorStatus_bit).bit0 
#define  bCloseEnd              GET_BITFIELD(&DoorStatus_bit).bit1
#define  bHoleDoorClose         GET_BITFIELD(&DoorStatus_bit).bit2 
#define  bDoorCloseOk           GET_BITFIELD(&DoorStatus_bit).bit3 
#define  bsHdsRunOff            GET_BITFIELD(&DoorStatus_bit).bit4
#define  bsCleRunOff            GET_BITFIELD(&DoorStatus_bit).bit5
#define  bSelDoor               GET_BITFIELD(&DoorStatus_bit).bit7





#define  IN_SU1                 GET_BITFIELD(&I_SU1_bit).bit0 
#define  IN_SD1                 GET_BITFIELD(&I_SU1_bit).bit1  
#define  IN_SFT                 GET_BITFIELD(&I_SU1_bit).bit2  
#define  IN_OLR                 GET_BITFIELD(&I_SU1_bit).bit3  
#define  IN_ULS                 GET_BITFIELD(&I_SU1_bit).bit4   
#define  IN_DLS                 GET_BITFIELD(&I_SU1_bit).bit5   
#define  IN_LU                  GET_BITFIELD(&I_SU1_bit).bit6   
#define  IN_LD                  GET_BITFIELD(&I_SU1_bit).bit7   

#define  IN_EMG                 GET_BITFIELD(&I_EMG_bit).bit0 
#define  IN_PRK                 GET_BITFIELD(&I_EMG_bit).bit1  
#define  IN_AUTO                GET_BITFIELD(&I_EMG_bit).bit2  
#define  IN_U_B                 GET_BITFIELD(&I_EMG_bit).bit3  
#define  IN_D_B                 GET_BITFIELD(&I_EMG_bit).bit4   
#define  IN_OP_E                GET_BITFIELD(&I_EMG_bit).bit5   
#define  IN_CL_E                GET_BITFIELD(&I_EMG_bit).bit6   
#define  IN_HL_D                GET_BITFIELD(&I_EMG_bit).bit7   

#define  IN_GR                  GET_BITFIELD(&I_GR_bit).bit0 
#define  IN_BAT                 GET_BITFIELD(&I_GR_bit).bit1  
#define  IN_PASS                GET_BITFIELD(&I_GR_bit).bit2  
#define  IN_FIRE                GET_BITFIELD(&I_GR_bit).bit3  
#define  IN_WATER               GET_BITFIELD(&I_GR_bit).bit4   
#define  IN_FULL                GET_BITFIELD(&I_GR_bit).bit5   
#define  IN_EX1                 GET_BITFIELD(&I_GR_bit).bit6   
#define  IN_EX2                 GET_BITFIELD(&I_GR_bit).bit7   

#define  IN_FR1                 GET_BITFIELD(&I_FIRE_bit).bit0 
#define  IN_FR2                 GET_BITFIELD(&I_FIRE_bit).bit1  
#define  IN_FR3                 GET_BITFIELD(&I_FIRE_bit).bit2  
#define  IN_FR4                 GET_BITFIELD(&I_FIRE_bit).bit3  
#define  IN_SU2                 GET_BITFIELD(&I_FIRE_bit).bit4   
#define  IN_SD2                 GET_BITFIELD(&I_FIRE_bit).bit5   
#define  IN_SU3                 GET_BITFIELD(&I_FIRE_bit).bit6   
#define  IN_SD3                 GET_BITFIELD(&I_FIRE_bit).bit7   

#define  IN_FS0                 GET_BITFIELD(&I_FS0_bit).bit0 
#define  IN_FS1                 GET_BITFIELD(&I_FS0_bit).bit1  
#define  IN_FS2                 GET_BITFIELD(&I_FS0_bit).bit2  
#define  IN_FS3                 GET_BITFIELD(&I_FS0_bit).bit3  
#define  IN_FS4                 GET_BITFIELD(&I_FS0_bit).bit4   
#define  IN_DER                 GET_BITFIELD(&I_FS0_bit).bit5   
#define  IN_FID                 GET_BITFIELD(&I_FS0_bit).bit6   
#define  IN_UND                 GET_BITFIELD(&I_FS0_bit).bit7   

#define  IN_X0                  GET_BITFIELD(&I_X0_bit).bit0  
#define  IN_X1                  GET_BITFIELD(&I_X0_bit).bit1 
#define  IN_X2                  GET_BITFIELD(&I_X0_bit).bit2  
#define  IN_X3                  GET_BITFIELD(&I_X0_bit).bit3  
#define  IN_X4                  GET_BITFIELD(&I_X0_bit).bit4   
#define  IN_X5                  GET_BITFIELD(&I_X0_bit).bit5   
#define  IN_X6                  GET_BITFIELD(&I_X0_bit).bit6   
#define  IN_X7                  GET_BITFIELD(&I_X0_bit).bit7   

#define  OUT_OP                 GET_BITFIELD(&O_OP_bit).bit0 
#define  OUT_CL                 GET_BITFIELD(&O_OP_bit).bit1  
#define  OUT_OP_S               GET_BITFIELD(&O_OP_bit).bit2   
#define  OUT_CL_S               GET_BITFIELD(&O_OP_bit).bit3
#define  OUT_BK2                GET_BITFIELD(&O_OP_bit).bit4  
#define  OUT_EY0                GET_BITFIELD(&O_OP_bit).bit5  
#define  OUT_GBR                GET_BITFIELD(&O_OP_bit).bit6   
#define  OUT_BRK                GET_BITFIELD(&O_OP_bit).bit7   


#define  OUT_U_W                GET_BITFIELD(&O_U_W_bit).bit0 
#define  OUT_D_W                GET_BITFIELD(&O_U_W_bit).bit1  
#define  OUT_P1                 GET_BITFIELD(&O_U_W_bit).bit2  
#define  OUT_P2                 GET_BITFIELD(&O_U_W_bit).bit3  
#define  OUT_P3                 GET_BITFIELD(&O_U_W_bit).bit4   
//#define  OUT_P4                 GET_BITFIELD(&O_U_W_bit).bit5   
#define  OUT_P4N                GET_BITFIELD(&O_U_W_bit).bit5   
#define  OUT_DAC                GET_BITFIELD(&O_U_W_bit).bit7   

#define  OUT_FAN                GET_BITFIELD(&O_Y_0_bit).bit0  
#define  OUT_LIT                GET_BITFIELD(&O_Y_0_bit).bit1  
#define  OUT_BUZ                GET_BITFIELD(&O_Y_0_bit).bit2   
#define  OUT_BELL               GET_BITFIELD(&O_Y_0_bit).bit3
#define  OUT_SIREN              GET_BITFIELD(&O_Y_0_bit).bit4
#define  OUT_ERR                GET_BITFIELD(&O_Y_0_bit).bit5
#define  OUT_EY1                GET_BITFIELD(&O_Y_0_bit).bit6
#define  OUT_EY2                GET_BITFIELD(&O_Y_0_bit).bit7



#define  GET_LONG(adr)          (unsigned long)GET_LONGFIELD(&FlashBuf[adr]).long_data

/*
#define  GET_LONG_byte0(adr)    GET_LONGFIELD(&FlashBuf[adr]).byte0[0]
#define  GET_LONG_byte1(adr)    GET_LONGFIELD(&FlashBuf[adr]).byte0[1]
#define  GET_LONG_byte2(adr)    GET_LONGFIELD(&FlashBuf[adr]).byte0[2]
#define  GET_LONG_byte3(adr)    GET_LONGFIELD(&FlashBuf[adr]).byte0[3]
*/

#define  FLOOR_COUNT(adr)       GET_LONGFIELD(&FlashBuf[adr+FLR_01_PULSE]).long_data
#define  ENCODER_COUNT(adr)     GET_LONGFIELD(&FlashBuf[adr+ENCODER_PULSE]).long_data



#define  CurPulse               GET_LONGFIELD(&parameter_mirror[CUR_PULSE]).long_data
#define  BefCurPulse            GET_LONGFIELD(&parameter_mirror[BEF_CUR_PULSE]).long_data
#define  MeterPerMin            GET_LONGFIELD(&parameter_mirror[METER_PER_MIN]).long_data
#define  CurMeterPerMin         GET_LONGFIELD(&parameter_mirror[CUR_METER_PER_MIN]).long_data


#define  TotalPulse             GET_LONGFIELD(&parameter_mirror[TOTAL_PULSE]).long_data
#define  StopMinimumPulse       GET_LONGFIELD(&parameter_mirror[STOP_MINIMUM_PULSE]).long_data
#define  DecreasePulse          GET_LONGFIELD(&parameter_mirror[DECREASE_PULSE]).long_data
#define  TmpFhmCounter1         GET_LONGFIELD(&parameter_mirror[TMP_FHM_COUNTER1]).long_data
#define  TmpFhmCounter2         GET_LONGFIELD(&parameter_mirror[TMP_FHM_COUNTER2]).long_data
#define  TmpMmPerMin            GET_LONGFIELD(&parameter_mirror[TMP_MM_PER_MIN]).long_data
#define  PulsePer100Msec        GET_LONGFIELD(&parameter_mirror[PULSE_PER_100MSEC]).long_data
#define  CurRpm                 GET_LONGFIELD(&parameter_mirror[CUR_RPM]).long_data
#define  StartPulse             GET_LONGFIELD(&parameter_mirror[START_PULSE]).long_data
//#define  Test_Pulse             GET_LONGFIELD(&parameter_mirror[TEST_PULSE]).long_data






#define  cF_TOPFLR              GET_LONGFIELD(&FlashDspCharBuf[F_TopFlr/4])         .byte[F_TopFlr%4]
#define  cF_PRKFLR              GET_LONGFIELD(&FlashDspCharBuf[F_PrkFlr/4])         .byte[F_PrkFlr%4]
#define  cF_OPWTTM              GET_LONGFIELD(&FlashDspCharBuf[F_OpWtTm/4])         .byte[F_OpWtTm%4]
#define  cF_OPTTTM              GET_LONGFIELD(&FlashDspCharBuf[F_OpTtTm/4])         .byte[F_OpTtTm%4]

#define  cF_USERLAMP            GET_LONGFIELD(&FlashDspCharBuf[F_UserLamp/4])       .byte[F_UserLamp%4]
#define  cF_FIXFLOOR            GET_LONGFIELD(&FlashDspCharBuf[F_FixFloor/4])       .byte[F_FixFloor%4]
#define  cF_FIXFLOORTIME        GET_LONGFIELD(&FlashDspCharBuf[F_FixFloorTime/4])   .byte[F_FixFloorTime%4]
#define  cF_FIRESAFEFLR         GET_LONGFIELD(&FlashDspCharBuf[F_FireSafeFlr/4])    .byte[F_FireSafeFlr%4]

#define  cF_SUBDOORFLR1         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr1/4])    .byte[F_SubDoorFlr1%4]
#define  cF_SUBDOORFLR2         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr2/4])    .byte[F_SubDoorFlr2%4]
#define  cF_SUBDOORFLR3         GET_LONGFIELD(&FlashDspCharBuf[F_SubDoorFlr3/4])    .byte[F_SubDoorFlr3%4]
#define  cF_ERRSTOPCNT          GET_LONGFIELD(&FlashDspCharBuf[F_ErrStopCnt/4])     .byte[F_ErrStopCnt%4]


#define  cF_NEXTFLRTIME         GET_LONGFIELD(&FlashDspCharBuf[F_NextFlrTime/4])    .byte[F_NextFlrTime%4]
#define  cF_LULDOFFTIME         GET_LONGFIELD(&FlashDspCharBuf[F_LuLdOffTime/4])    .byte[F_LuLdOffTime%4]
#define  cF_NCNOBIT0            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit0/4])       .byte[F_NcNoBit0%4]
#define  cF_NCNOBIT1            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit1/4])       .byte[F_NcNoBit1%4]


#define  cF_NCNOBIT2            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit2/4])       .byte[F_NcNoBit2%4]
#define  cF_NCNOBIT3            GET_LONGFIELD(&FlashDspCharBuf[F_NcNoBit3/4])       .byte[F_NcNoBit3%4]
#define  cF_X7SAFEFLR           GET_LONGFIELD(&FlashDspCharBuf[F_X7SafeFlr/4])      .byte[F_X7SafeFlr%4]
#define  cF_FANTIME             GET_LONGFIELD(&FlashDspCharBuf[F_FanTime/4])        .byte[F_FanTime%4]
#define  cF_LIGHTTIME           GET_LONGFIELD(&FlashDspCharBuf[F_LightTime/4])      .byte[F_LightTime%4]

#define  cF_NONSERVICE0         GET_LONGFIELD(&FlashDspCharBuf[F_NonService0/4])    .byte[F_NonService0%4]
#define  cF_NONSERVICE1         GET_LONGFIELD(&FlashDspCharBuf[F_NonService1/4])    .byte[F_NonService1%4]
#define  cF_NONSERVICE2         GET_LONGFIELD(&FlashDspCharBuf[F_NonService2/4])    .byte[F_NonService2%4]
#define  cF_NONSERVICE3         GET_LONGFIELD(&FlashDspCharBuf[F_NonService3/4])    .byte[F_NonService3%4]

//#define  cF_ELEV_SPEED          GET_LONGFIELD(&FlashDspCharBuf[F_ElevSpeed/4])      .byte[F_ElevSpeed%4]
//#define  cF_START_FLOOR         GET_LONGFIELD(&FlashDspCharBuf[F_StartFloor/4])     .byte[F_StartFloor%4]
//#define  cF_SERIALNM0           GET_LONGFIELD(&FlashDspCharBuf[F_SerialNm0/4])      .byte[F_SerialNm0%4]
//#define  cF_SERIALNM1           GET_LONGFIELD(&FlashDspCharBuf[F_SerialNm1/4])      .byte[F_SerialNm1%4]

#define  cF_PASSWARD            GET_LONGFIELD(&FlashDspCharBuf[F_Passward/4])       .byte[F_Passward%4]

#define  cF_VER0                GET_LONGFIELD(&FlashDspCharBuf[F_Ver0/4])           .byte[F_Ver0%4]
#define  cF_VER1                GET_LONGFIELD(&FlashDspCharBuf[F_Ver1/4])           .byte[F_Ver1%4]
#define  cF_VER2                GET_LONGFIELD(&FlashDspCharBuf[F_Ver2/4])           .byte[F_Ver2%4]
#define  cF_BD_ID               GET_LONGFIELD(&FlashDspCharBuf[F_Bd_Id/4])          .byte[F_Bd_Id%4]

#define  cF_ELEV_SPEED          GET_LONGFIELD(&FlashDspCharBuf[F_ElevSpeed/4])      .byte[F_ElevSpeed%4]
#define  cF_START_FLOOR         GET_LONGFIELD(&FlashDspCharBuf[F_StartFloor/4])     .byte[F_StartFloor%4]
#define  cF_SERIALNM0           GET_LONGFIELD(&FlashDspCharBuf[F_SerialNm0/4])      .byte[F_SerialNm0%4]
#define  cF_SERIALNM1           GET_LONGFIELD(&FlashDspCharBuf[F_SerialNm1/4])      .byte[F_SerialNm1%4]

#define  iF_F_BrkStTm10         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm10/4])      .intger[(F_BrkStTm10%4)/2]
#define  iF_F_BrkStTm20         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm20/4])      .intger[(F_BrkStTm20%4)/2]
#define  iF_F_BrkStTm30         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm30/4])      .intger[(F_BrkStTm30%4)/2]
#define  iF_F_BrkStTm40         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm40/4])      .intger[(F_BrkStTm40%4)/2]
#define  iF_F_BrkStTm50         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm50/4])      .intger[(F_BrkStTm50%4)/2]
#define  iF_F_BrkStTm60         GET_LONGFIELD(&FlashDspCharBuf[F_BrkStTm60/4])      .intger[(F_BrkStTm60%4)/2]

#define  cF_STTM1               GET_LONGFIELD(&FlashDspCharBuf[F_StTm1/4])          .byte[F_StTm1%4]
#define  cF_STTM2               GET_LONGFIELD(&FlashDspCharBuf[F_StTm2/4])          .byte[F_StTm2%4]
#define  cF_STTM3               GET_LONGFIELD(&FlashDspCharBuf[F_StTm3/4])          .byte[F_StTm3%4]
#define  cF_STTM4               GET_LONGFIELD(&FlashDspCharBuf[F_StTm4/4])          .byte[F_StTm4%4]

#define  cF_SU1SD1_VELOCITY     GET_LONGFIELD(&FlashDspCharBuf[F_Su1Sd1_Velocity/4]).byte[F_Su1Sd1_Velocity%4]
#define  cF_SU2SD2_VELOCITY     GET_LONGFIELD(&FlashDspCharBuf[F_Su2Sd2_Velocity/4]).byte[F_Su2Sd2_Velocity%4]
#define  cF_SU3SD3_VELOCITY     GET_LONGFIELD(&FlashDspCharBuf[F_Su3Sd3_Velocity/4]).byte[F_Su3Sd3_Velocity%4]
#define  cF_FhmOnOff            GET_LONGFIELD(&FlashDspCharBuf[F_FhmOnOff/4])       .byte[F_FhmOnOff%4]

#define  cF_DoorJumperOff       GET_LONGFIELD(&FlashDspCharBuf[F_DoorJumperOff/4])  .byte[F_DoorJumperOff%4]


/////speed/////////
#define  cF_MANUALSPEED         GET_LONGFIELD(&FlashDspCharBuf[F_ManualSpeed/4])  .byte[F_ManualSpeed%4]
#define  cF_BATTERYSPEED        GET_LONGFIELD(&FlashDspCharBuf[F_BatterySpeed/4]) .byte[F_BatterySpeed%4]
#define  cF_DECREASESPEED       GET_LONGFIELD(&FlashDspCharBuf[F_DecreaseSpeed/4]).byte[F_DecreaseSpeed%4]
#define  cF_ETC1SPEED           GET_LONGFIELD(&FlashDspCharBuf[F_Etc1Speed/4])    .byte[F_Etc1Speed%4]
#define  cF_ETC2SPEED           GET_LONGFIELD(&FlashDspCharBuf[F_Etc2Speed/4])    .byte[F_Etc2Speed%4]
#define  cF_ETC3SPEED           GET_LONGFIELD(&FlashDspCharBuf[F_Etc3Speed/4])    .byte[F_Etc3Speed%4]
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




#define  cF_FLRDSPCH(adr)       GET_LONGFIELD(&FlashDspCharBuf[adr/4]).byte[adr%4]
#define  b_LdTmpBufRam(adr)     GET_LONGFIELD(&parameter_mirror[(adr%64)/4]).byte[adr%4]
#define  i_LdTmpBufRam(adr)     GET_LONGFIELD(&parameter_mirror[(adr%64)/4]).intger[(adr%4)/2]
