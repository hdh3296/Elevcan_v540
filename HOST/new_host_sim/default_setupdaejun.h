

#define  	COMPANY_SIGN      		    'A'

#define  	VERSION_0         		    '0'
#define  	VERSION_1         		    '0'
#define  	VERSION_2         		    '9'


#define     LG                          0
#define     IO                          1

#define     MAN_USE                     0
#define     BAGGAGE_USE                 4


#define     INVERTER_CHECK   	        (cF_BD_ID & 0x03)
#define     USE_CHECK   	            (cF_BD_ID & 0x0c)


#define     SET_ELEV_SPEED_PER_MIM      45 
#define     SET_ENCODER_PULSE           8192 
#define     SET_MOTOR_RPM               96  


#define     BIT_NORMAL_OPEN             0x80
#define     BIT_NORMAL_CLOSE            0x00

#define     DISABLE_FLR                 32

#define     Init_ALL_FF                 0xff

#define     START_FLOOR                 0



#define		Init_TopFlr		            1
#define		Init_PrkFlr                 0
#define     Init_OpWtTm                 21    
#define     Init_OpTtTm                 0
#define     Init_DirTime                10
#define     Init_VoiceTime              10
#define     Init_FixFloor               32
#define     Init_FireSafeFlr            0
#define     Init_X7SafeFlr              1
#define     Init_WaterSafeFlr           1        
#define     Init_SubDoorFlr1            0
#define     Init_SubDoorFlr2            0
#define     Init_SubDoorFlr3            0
#define     Init_SubDoorFlr4            0

#define     Init_FanTime                3        //3 sec
#define     Init_LightTime              99       //99 min
#define     Init_FixFloorTime           0
#define     Init_NextFlrTime            0
#define     Init_LuLdOffTime            3
#define     Init_ReOpTime               1

#define     Init_StTm1                  20
#define     Init_StTm2                  40
#define     Init_StTm3                  60
#define     Init_StTm4                  80

#define     Init_BrkStTm10              800  
#define     Init_BrkStTm20              1500
#define     Init_BrkStTm30              1600
#define     Init_BrkStTm40              2000
#define     Init_BrkStTm50              2200
#define     Init_BrkStTm60              500

                                    
#define     Init_ParkingStartTime       0
#define     Init_ParkingEndTime         0

//////////////////////////////////////////////////////////////




///////////////////////////////////////////////
        //  P1  P2  P3  P4
        //  0   0   0   0               :0
        //  1   0   0   0               :1
        //  0   1   0   0               :2
        //  1   1   0   0               :3
        //  0   0   1   0               :4
        //  1   0   1   0               :5
        //  0   1   1   0               :6
        //  1   1   1   0               :7
        //  0   0   0   1               :8
        //  1   0   0   1               :9
        //  0   1   0   1               :10
        //  1   1   0   1               :11
        //  0   0   1   1               :12
        //  1   0   1   1               :13
        //  0   1   1   1               :14
        //  1   1   1   1               :15
//////////////////////////////////////////////
#define     NONE_USE_SPD                0
#define     P1_SPD                      1
#define     P2_SPD                      2
#define     P1P2_SPD                    3
#define     P3_SPD                      4
#define     P1P3_SPD                    5
#define     P2P3_SPD                    6
#define     P1P2P3_SPD                  7
#define     P4_SPD                      8
#define     P1P4_SPD                    9
#define     P2P4_SPD                    10
#define     P1P2P4_SPD                  11
#define     P3P4_SPD                    12
#define     P1P3P4_SPD                  13
#define     P2P3P4_SPD                  14
#define     P1P2P3P4_SPD                15


#define     SPEED_30                    0
#define     SPEED_45                    1
#define     SPEED_60                    2
#define     SPEED_90                    3
#define     SPEED_105                   4
#define     SPEED_120                   5 
#define     SPEED_150                   6 
#define     SPEED_180                   7 
#define     SPEED_210                   8 
////////////////////////////////////////////
////////////////////////////////////////////

#define     SPEED_30_DEC_LENGTH         500                 //mm
#define     SPEED_45_DEC_LENGTH         660                //mm
#define     SPEED_60_DEC_LENGTH         1200                //970                 //1200        //mm
#define     SPEED_90_DEC_LENGTH         1800                //mm    
#define     SPEED_105_DEC_LENGTH        2150                //2100        //mm
#define     SPEED_120_DEC_LENGTH        3200                //mm
#define     SPEED_150_DEC_LENGTH        3000                //mm
#define     SPEED_180_DEC_LENGTH        3600                //mm
#define     SPEED_210_DEC_LENGTH        3900                //mm



#define     bFhmOnOff                   0                     //1
#define     bDoorJumperOff              1                     //1    
#define     bEncoderPhase               2                     //1    
#define     bWardPriority               3
#define     bNonStop                    4
#define     bOpenTotalOnOff             5
#define     bOpenWaitOnOff              6
/////////////BIT AREA1////////////////////////
/////////////////////////////////////////////
//base adr == F_NcNoBit0
#define     bLight                      0
#define     bOpLmS                      1
#define     bParking                    2
#define     bSafety                     3
#define     bOverload                   4


