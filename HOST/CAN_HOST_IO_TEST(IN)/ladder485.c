
#include    "iodef.h"

#define         MAX_LADDER_BUF  40

UserDataType    New485Ladder[MAX_LADDER_BUF]={0};      

UserDataType    LadderGroup;
UserDataType    LadderGroupSub;
UserDataType    LadderKey;
UserDataType    EnterKey;
UserDataType    Cursor;
UserDataType    EditStatus;
UserDataType    EditDigitOrChar;
UserDataType    EditDataType;
UserDataType    EditBlanck;
UserDataType    ShiftCnt;
unsigned long   DigitMax;

const unsigned char GroupLineMessage[][17]={
                                    "FL:00 EB:000    ",//0
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
                                    "FLR:TopFlr      ",//33
                                    "FLR:PrkFlr      ",//34
                                    "FLR:NoUse Go Flr",//35
                                    "FLR:FireSafe Flr",//36
                                    "FLR:SubDoor1 Flr",//37
                                    "FLR:SubDoor2 Flr",//38
                                    "FLR:SubDoor3 Flr",//39
                                    "FLR:X7 Safe  Flr",//40
                                    "FLR:Start Flr   ",//41
                                    "FLR:Nc1 Flr     ",//42
                                    "FLR:Nc2 Flr     ",//43
                                    "FLR:Nc3 Flr     ",//44
                                    "FLR:Nc4 Flr     ",//42
                                    "FLR:Nc5 Flr     ",//43
                                    "FLR:Nc6 Flr     ",//44
                                    "FLR:Nc7 Flr     ",//42
                                    "FLR:Nc8 Flr     ",//43
                                    "FLR:Nc9 Flr     ",//44
                                    "FLR:Nc10Flr     ",//42
                                    "FLR:Nc11Flr     ",//43
                                    "FLR:Nc12Flr     ",//44
                                    "FLR:Nc13Flr     ",//42
                                    "FLR:Nc14Flr     ",//43
                                    "FLR:Nc15Flr     ",//44
                                    "FLR:Nc16Flr     ",//42
                                    "FLR:Nc17Flr     ",//43
                                    "FLR:Nc18Flr     ",//44
                                    "FLR:Nc19Flr     ",//42
                                    "FLR:Nc20Flr     ",//43
                                    "FLR:Nc21Flr     ",//44
                                    "FLR:Nc22Flr     ",//42
                                    "FLR:Nc23Flr     ",//43
///////////////////////////////////////////////////////////                                                                       
                                    "TMR:Op Wait Time",//45
                                    "TMR:Op Total Tm ",//46
                                    "TMR:No Use Time ",//47
                                    "TMR:NextFlr Time",//48
                                    "TMR:LuLdOff Time",//49
                                    "TMR:Fan Off Time",//50
                                    "TMR:Lit Off Time",//51
                                    "TMR:Timer1  Time",//52
                                    "TMR:Timer2  Time",//53
                                    "TMR:Timer3  Time",//54
                                    "TMR:Timer4  Time",//55
                                    "TMR:Timer5  Time",//56
                                    "TMR:Start1  Time",//57
                                    "TMR:Start2  Time",//58
                                    "TMR:Start3  Time",//59
                                    "TMR:Start4  Time",//60
                                    "TMR:Stop1   Time",//61
                                    "TMR:Stop2   Time",//62
                                    "TMR:Stop3   Time",//63
                                    "TMR:Stop4   Time",//64
                                    "TMR:Stop5   Time",//65
                                    "TMR:Stop6   Time",//66
                                    "TMR:Stop7   Time",//61
                                    "TMR:Stop8   Time",//62
                                    "TMR:Stop9   Time",//63
                                    "TMR:Stop10  Time",//64
                                    "TMR:Stop11  Time",//65
                                    "TMR:Stop12  Time",//66
                                    "TMR:Stop13  Time",//61
                                    "TMR:Stop14  Time",//62
                                    "TMR:Stop15  Time",//63
                                    "TMR:Stop16  Time",//64
///////////////////////////////////////////////////////////                                                                                                           
                                    "ONOFF:Floor01   ",//67
                                    "ONOFF:Floor02   ",//68
                                    "ONOFF:Floor03   ",//69
                                    "ONOFF:Floor04   ",//70
                                    "ONOFF:Floor05   ",//71
                                    "ONOFF:Floor06   ",//72
                                    "ONOFF:Floor07   ",//73
                                    "ONOFF:Floor08   ",//74
                                    "ONOFF:Floor09   ",//75
                                    "ONOFF:Floor10   ",//76
                                    "ONOFF:Floor11   ",//77
                                    "ONOFF:Floor12   ",//78
                                    "ONOFF:Floor13   ",//79
                                    "ONOFF:Floor14   ",//80
                                    "ONOFF:Floor15   ",//81
                                    "ONOFF:Floor16   ",//82
                                    "ONOFF:Floor17   ",//83
                                    "ONOFF:Floor18   ",//84
                                    "ONOFF:Floor19   ",//85
                                    "ONOFF:Floor20   ",//86
                                    "ONOFF:Floor21   ",//87
                                    "ONOFF:Floor22   ",//88
                                    "ONOFF:Floor23   ",//89
                                    "ONOFF:Floor24   ",//90
                                    "ONOFF:Floor25   ",//91
                                    "ONOFF:Floor26   ",//92
                                    "ONOFF:Floor27   ",//93
                                    "ONOFF:Floor28   ",//94
                                    "ONOFF:Floor29   ",//95
                                    "ONOFF:Floor30   ",//96
                                    "ONOFF:Floor31   ",//97
                                    "ONOFF:Floor32   ",//98
///////////////////////////////////////////////////////////                                                                                                           
                                    "I_O:Manual   Spd",//128
                                    "I_O:Battery  Spd",//100
                                    "I_O:Dec      Spd",//101
                                    "I_O:Etc1     Spd",//102
                                    "I_O:Etc2     Spd",//103
                                    "I_O:Etc3     Spd",//104
                                    "I_O:Etc4     Spd",//105
                                    "I_O:Spd30    Spd",//106
                                    "I_O:Spd45    Spd",//107
                                    "I_O:Spd60    Spd",//108
                                    "I_O:Spd90    Spd",//109
                                    "I_O:Spd105   Spd",//110
                                    "I_O:Spd120   Spd",//111
                                    "I_O:Spd150   Spd",//112
                                    "I_O:Spd180   Spd",//113
                                    "I_O:Spd210   Spd",//114
                                    "I_O:MaxEv    Spd",//115
                                    "I_O:MaxSuSd1 Spd",//116
                                    "I_O:MaxSuSd2 Spd",//117
                                    "I_O:MaxSuSd3 Spd",//118                                  
                                    "I_O:Spd1        ",//119
                                    "I_O:Spd2        ",//120
                                    "I_O:Spd3        ",//121
                                    "I_O:Spd4        ",//122
                                    "I_O:Spd5        ",//123
                                    "I_O:Spd6        ",//119
                                    "I_O:Spd7        ",//120
                                    "I_O:Spd8        ",//121
                                    "I_O:Spd9        ",//122
                                    "I_O:Spd10       ",//123
                                    "I_O:Spd11       ",//122
                                    "I_O:Spd12       ",//123
///////////////////////////////////////////////////////////                                                                                                           
                                    "USER:Version    ",//124
                                    "USER:BoardId    ",//125
                                    "USER:Passward   ",//126
                                    "USER:SerialNm   ",//127
                                    "USER:UserLamp   ",//128
                                    "USER:ErrStCnt   ",//129
                                    "USER:User0      ",//130
                                    "USER:User1      ",//131
                                    "USER:User3      ",//131
                                    "USER:User4      ",//131
                                    "USER:User5      ",//131
                                    "USER:User6      ",//131
                                    "USER:User7      ",//131
                                    "USER:User8      ",//131
                                    "USER:User9      ",//131
                                    "USER:User10     ",//131
                                    "USER:User11     ",//131
                                    "USER:User12     ",//131
                                    "USER:User13     ",//131
                                    "USER:User14     ",//131
                                    "USER:User15     ",//131
                                    "USER:User16     ",//131
                                    "USER:User17     ",//131
                                    "USER:User18     ",//131
                                    "USER:User19     ",//131
                                    "USER:User20     ",//131
                                    "USER:User21     ",//131
                                    "USER:User22     ",//131
                                    "USER:User23     ",//131
                                    "USER:User24     ",//131
                                    "USER:User25     ",//131
                                    "USER:User26     ",//131
///////////////////////////////////////////////////////////                                                                                                           
                                    "W_FLR:Time0506  ",//134
                                    "W_FLR:Time0607  ",//135
                                    "W_FLR:Time0708  ",//136
                                    "W_FLR:Time0809  ",//137
                                    "W_FLR:Time0910  ",//138
                                    "W_FLR:Time1011  ",//139
                                    "W_FLR:Time1112  ",//140
                                    "W_FLR:Time1213  ",//139
                                    "W_FLR:Time1314  ",//140
                                    "W_FLR:Time1415  ",//139
                                    "W_FLR:Time1516  ",//140
                                    "W_FLR:Time1617  ",//139
                                    "W_FLR:Time1718  ",//140
                                    "W_FLR:Time1819  ",//139
                                    "W_FLR:Time1920  ",//140
                                    "W_FLR:Time2021  ",//139
                                    "W_FLR:Time0001  ",//140
                                    "W_FLR:Time0002  ",//139
                                    "W_FLR:Time0003  ",//140
                                    "W_FLR:Time0004  ",//139
                                    "W_FLR:Time0005  ",//140
                                    "W_FLR:Time0006  ",//139
                                    "W_FLR:Time0007  ",//140
                                    "W_FLR:Time0008  ",//139
                                    "W_FLR:Time0009  ",//140
                                    "W_FLR:Time0010  ",//139
                                    "W_FLR:Time0011  ",//140
                                    "W_FLR:Time0012  ",//139
                                    "W_FLR:Time0013  ",//140
                                    "W_FLR:Time0014  ",//139
                                    "W_FLR:Time0015  ",//140
                                };


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



#define SECONDLINE_BASE             18
#define DSP_VALUE_BASE              7
#define SECONDLINE_DATA             SECONDLINE_BASE + DSP_VALUE_BASE

#define FLR_DSP_GROUP               1
#define FLR_GROUP                   2
#define TIMER_GROUP                 3
#define ONOFF_GROUP                 4
#define IO_GROUP                    5
#define USER_GROUP                  6
#define OPEN_WAIT_GROUP             7



void  __attribute__((section(".usercode"))) NewMenuStart(void)
{
    EnterKey=0;
    Cursor=0;
    ShiftCnt=0;
    EditStatus=0;
    EditDigitOrChar=0;
    EditDataType=0;
    EditBlanck=0;
}


void  __attribute__((section(".usercode"))) Two_Digit(LocalType value)
{
    LocalType i,j,k;
    i=value;

    if(i>99)    i=0;

    j=(i/10);  
    i=(i%10);
  
    New485Ladder[SECONDLINE_DATA+EditBlanck+0]=j + '0';  
    New485Ladder[SECONDLINE_DATA+EditBlanck+1]=i + '0';  
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
  
    New485Ladder[SECONDLINE_DATA+EditBlanck+0]=j + '0';  
    New485Ladder[SECONDLINE_DATA+EditBlanck+1]=k + '0';  
    New485Ladder[SECONDLINE_DATA+EditBlanck+2]=i + '0';      
}



void  __attribute__((section(".usercode"))) Integer_Digit(LocalType value)
{
    LocalType i;
    i=value;
    if(i>65534)   i=0;

    New485Ladder[SECONDLINE_DATA+EditBlanck+4]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+EditBlanck+3]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+EditBlanck+2]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+EditBlanck+1]=(i%10) + '0';      

    i=i/10;
    New485Ladder[SECONDLINE_DATA+EditBlanck+0]=(i%10) + '0';          
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void  __attribute__((section(".usercode"))) FlrDspGroup(LocalType offset)
{
    LocalType i;

    i=(offset *2 );

    New485Ladder[SECONDLINE_DATA+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i+0));  
    New485Ladder[SECONDLINE_DATA+EditBlanck+1]=cF_FLRDSPCH((unsigned long)(i+1)); 
         
    Cursor=0;
    ShiftCnt=2;
    EditBlanck=7;
    EditStatus=DIGIT_ALPHAR_EDIT;
}

void  __attribute__((section(".usercode"))) FlrDspGroupSave(LocalType offset)
{

}




void  __attribute__((section(".usercode"))) FlrGroup(LocalType offset)
{
    LocalType i;
    
    i=(offset + F_TopFlr);

    i=cF_FLRDSPCH((unsigned long)i);    
    Two_Digit(i+1);     

    Cursor=0;
    ShiftCnt=2;
    EditBlanck=7;
    EditStatus=DIGIT_EDIT;
}



void  __attribute__((section(".usercode"))) FlrGroupSave(LocalType offset)
{
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

void  __attribute__((section(".usercode"))) TimerGroupSave(LocalType offset)
{

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
        New485Ladder[SECONDLINE_DATA+EditBlanck+0]='O';  
        New485Ladder[SECONDLINE_DATA+EditBlanck+1]='n';  
    }
    else{
        New485Ladder[SECONDLINE_DATA+EditBlanck+0]='O';  
        New485Ladder[SECONDLINE_DATA+EditBlanck+1]='f';  
        New485Ladder[SECONDLINE_DATA+EditBlanck+2]='f';      
    }
}


void  __attribute__((section(".usercode"))) OnOffGroupSave(LocalType offset)
{
}

void  __attribute__((section(".usercode"))) IoGroup(LocalType offset)
{
    LocalType i;
    
    i=(offset + F_ManualSpeed);

    i=cF_FLRDSPCH((unsigned long)i);
    Two_Digit(i);     
}

void  __attribute__((section(".usercode"))) IoGroupSave(LocalType offset)
{

}


void  __attribute__((section(".usercode"))) UserGroup(LocalType offset)
{
    LocalType i,j;

    switch(offset){
        case    0:
            i=(offset + F_Ver0);
            New485Ladder[SECONDLINE_DATA+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_DATA+EditBlanck+1]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_DATA+EditBlanck+2]='.';      
            New485Ladder[SECONDLINE_DATA+EditBlanck+3]=cF_FLRDSPCH((unsigned long)(i+2));      
            break;
        case    1:
            i=(offset + F_Bd_Id);
            i=cF_FLRDSPCH((unsigned long)i);
            Three_Digit(i);     
            break;
        case    2:
            i=(offset + F_Passward0);
            New485Ladder[SECONDLINE_DATA+EditBlanck+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_DATA+EditBlanck+1]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_DATA+EditBlanck+2]=cF_FLRDSPCH((unsigned long)(i+2));      
            New485Ladder[SECONDLINE_DATA+EditBlanck+3]=cF_FLRDSPCH((unsigned long)(i+3));      
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


void  __attribute__((section(".usercode"))) UserGroupSave(LocalType offset)
{

}



void  __attribute__((section(".usercode"))) OpenWaitGroup(LocalType offset)
{
    LocalType i;
    
    i=(offset + F_OpWtTm);

    i=cF_FLRDSPCH((unsigned long)i);
    Two_Digit(i);     
}

void  __attribute__((section(".usercode"))) OpenWaitGroupSave(LocalType offset)
{

}





unsigned int  __attribute__((section(".usercode"))) SaveData(void)
{
    LocalType i;

    switch(LadderGroup){
        case    FLR_DSP_GROUP:
            FlrDspGroupSave(LadderGroupSub);
            break;
        case    FLR_GROUP:
            FlrGroupSave(LadderGroupSub);
            break;
        case    TIMER_GROUP:
            TimerGroupSave(LadderGroupSub);
            break;
        case    ONOFF_GROUP:
            OnOffGroupSave(LadderGroupSub);
            break;
        case    IO_GROUP:
            IoGroupSave(LadderGroupSub);
            break;
        case    USER_GROUP:
            UserGroupSave(LadderGroupSub);
            break;
        case    OPEN_WAIT_GROUP:
            OpenWaitGroupSave(LadderGroupSub);
            break;
        default:
            break;

    }



    switch(EditStatus){
        case    DIGIT_EDIT:
            New485Ladder[i]++;
            if(New485Ladder[i]>'9')   New485Ladder[i]='0';
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]++;
            if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  New485Ladder[i]='A'; 
            else if((New485Ladder[i]>'Z'))                      New485Ladder[i]='0'; 
            break;
        case    TABLE_EDIT:
                break;    
        case    TOGGLE_EDIT:
                break;    
    }

    EnterKey=0;
    Cursor=0;         
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
            New485Ladder[i]++;
            if(New485Ladder[i]>'9')   New485Ladder[i]='0';
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]++;
            if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  New485Ladder[i]='A'; 
            else if((New485Ladder[i]>'Z'))                      New485Ladder[i]='0'; 
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
            New485Ladder[i]--;            
            if(New485Ladder[i] < '0')   New485Ladder[i]='9';
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]--;
            if((New485Ladder[i]<'0'))                      New485Ladder[i]='Z'; 
            else if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  New485Ladder[i]='9'; 
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
}


unsigned int  __attribute__((section(".usercode"))) KeyCheck(void)
{

    if(LadderBuf[C_SAVE_DATA+0] != LadderKey){
        LadderKey = LadderBuf[C_SAVE_DATA+0];
        switch(LadderKey){
            case    MENUKEY:
                    LadderGroup=(LadderGroup+1)%8;
                    LadderGroupSub=0;
                    NewMenuStart();
                    break;
            case    ESCKEY:
                    LadderGroup=0;
                    LadderGroupSub=0;
                    NewMenuStart();
                    break;
            case    UPKEY:
                    if(EnterKey==1){
                        LadderGroupSub=(LadderGroupSub+1)%32;
                        NewMenuStart();
                    }
                    else if(EnterKey==2){
                        CusorDataUp();
                    }
                    break;
            case    DOWNKEY:
                    if(EnterKey==1){
                        if(LadderGroupSub>0)    LadderGroupSub--;
                        else                    LadderGroupSub=31;                    
                        NewMenuStart();
                    }
                    else if(EnterKey==2){
                        CusorDataDn();
                    }
                    break;
            case    LEFTKEY:
                    if(EnterKey==1){
                        if(LadderGroup>0)   LadderGroup--;
                        else                LadderGroup=7;
                        LadderGroupSub=0;
                        NewMenuStart();
                    }
                    else if(EnterKey==2){
                        ShiftLeftCur();
                    }
                    break;
            case    RIGHTKEY:
                    if(EnterKey==1){
                        LadderGroup=(LadderGroup+1)%8;
                        LadderGroupSub=0;
                        NewMenuStart();
                    }
                    else if(EnterKey==2){
                        ShiftRightCur();
                    }
                    break;
            case    ENTKEY:
                    EnterKey++;
                    if(EnterKey==3){
                        SaveData();
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
                    CusorDigitSet();
                    break;
            default:
                    LadderKey = 0xff;
                    break;
        }   
    }

    return(0);
}


////////////////////new ladder////////////////////////////
unsigned int  __attribute__((section(".usercode"))) NewFlashData(void)
{
    LocalType i,j;

    KeyCheck();

    if(EnterKey==0){
        EnterKey=1;
            
        for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';
        New485Ladder[MAX_LADDER_BUF-1]=0x0;   

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
    
        switch(LadderGroup){
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
    }
    return(0);
}




void  __attribute__((section(".usercode"))) Ladder485Init(void)
{
    LocalType i;

    LadderGroup=0;
    LadderGroupSub=0;
    NewMenuStart();

    for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';

    New485Ladder[MAX_LADDER_BUF-1]=0x0;   
}
