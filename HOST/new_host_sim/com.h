

extern void    Serial(void);
extern void    Serial2(void);

#define        MAX_RTX_BUF     	    100 //70
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


