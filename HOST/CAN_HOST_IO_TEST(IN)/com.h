

extern void    Serial(void);
extern void    Serial2(void);

#define        MAX_RTX_BUF     	    70
#define        MAX_SAVE_BUF     	30

#define         EOT             0x04
#define         ETX             0x03
#define         ENQ             0x05
#define         ACK             0x06

#define         STX_CHK         0
#define         ETX_CHK         6
#define         RX_ERROR        7
#define         RX_GOOD         8
#define         TX_SET          9
#define         BCC1_CHK        13
#define         BCC2_CHK        14


/*
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

*/

//extern  unsigned        char    RxBuffer1[MAX_RTX_BUF];
//extern  unsigned        char    RcvBuf1[MAX_RTX_DATA_COM1];
//extern  unsigned        char    RxStatus1;
//extern  unsigned        char    RxCurCnt1;
//extern  unsigned        char    SerialTime1;
//extern  unsigned        char    Chksum1;


