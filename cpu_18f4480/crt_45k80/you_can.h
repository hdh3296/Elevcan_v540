

#define     HOST_BOARD          0x2000
#define     HOST_LAST_DATA      0x08


#define  	H_INTV_TIME1  50   //msec
#define  	H_INTV_TIME2  55   //msec
#define  	H_INTV_TIME3  60   //msec
#define  	H_INTV_TIME4  65   //msec
#define  	H_INTV_TIME5  70   //msec



#define		CAN1_MAX_TX_BUF		100
#define		CAN1_MAX_RX_BUF		100




extern  void    Can1DlcSet(char MsgFlag,unsigned char DataCnt);
extern  void    Can1Init(void);
extern  void    Can1Interrupt(void);
extern  void    Can1SetFilter(char filter_no, unsigned int sid, unsigned long eid);
extern  void    Can1SetMask(char mask_no, unsigned int sid, unsigned long eid);
extern	unsigned char	Can1Check(void);




extern	unsigned    long    Can1TxEid;
extern	unsigned    int     Can1TxSid;
extern	unsigned    char    Can1TxDlc;
extern	unsigned    char	Can1TxDataTotalCnt;
extern	unsigned    char    Can1TxDataTxPointer;


extern	unsigned    long    Can1RxEid;
extern	unsigned    int     Can1RxSid;
extern	unsigned    char    Can1RxDlc;
extern	unsigned    char	Can1RxDataTotalCnt;
extern	unsigned    char    Can1RxDataRxPointer;

extern	unsigned    char    Can1TxBuf[CAN1_MAX_TX_BUF];           
extern	unsigned    char    Can1RxBuf[CAN1_MAX_RX_BUF];           

extern	unsigned    char    Can1ThisRxBuf[8];           
extern	unsigned    int     Can1RxTimer;           

