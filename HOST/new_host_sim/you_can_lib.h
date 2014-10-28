

//extern void youCAN1SetFilter(int filter_no, unsigned int sid, unsigned long eid);
//extern void youCAN1SetMask(int mask_no, unsigned int sid, unsigned long eid);

extern void youCAN1TxSidSet(int MsgFlag,unsigned int sid);
extern void youCAN1TxEidSet(int MsgFlag,unsigned int eidh, unsigned int eidl);
extern void youCAN1SetMask(int mask_no, unsigned int sid, unsigned int eidh,unsigned int eidl);
extern void youCAN1SetFilter(int filter_no, unsigned int sid, unsigned int eidh,unsigned int eidl);




//extern void youCAN2SetFilter(int filter_no, unsigned int sid, unsigned long eid);
//extern void youCAN2SetMask(int mask_no, unsigned int sid, unsigned long eid);

//extern void youCAN1SetMask(int mask_no, unsigned int sid, unsigned int eidh,unsigned int eidl);
//extern void youCAN1SetFilter(int filter_no, unsigned int sid, unsigned int eidh,unsigned int eidl);
extern void youCAN2TxSidSet(int MsgFlag,unsigned int sid);
extern void youCAN2TxEidSet(int MsgFlag,unsigned int eidh, unsigned int eidl);
extern void youCAN2SetMask(int mask_no, unsigned int sid, unsigned int eidh,unsigned int eidl);
extern void youCAN2SetFilter(int filter_no, unsigned int sid, unsigned int eidh,unsigned int eidl);
extern void LoadCanBuffer(unsigned int i);


extern unsigned int   CAN_Buf[8];



#define  MASTER_TX_SLAVE     1
#define  SLAVE_TX_MASTER     2



/*
#define  H_INTV_TIME1  50   //msec
#define  H_INTV_TIME2  55   //msec
#define  H_INTV_TIME3  60   //msec
#define  H_INTV_TIME4  65   //msec
#define  H_INTV_TIME5  70   //msec
*/

