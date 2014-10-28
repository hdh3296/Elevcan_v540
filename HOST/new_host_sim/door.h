
#include "iodef.h"



#define		NO_DOOR		    0
#define		MAIN_DOOR		1
#define		SUB_DOOR		2
#define		MAIN_SUB_DOOR   3



#define	    MAIN_OPEN_KEY               0x01
#define		MAIN_CLOSE_KEY	            0x02
#define	    SUB_OPEN_KEY                0x04
#define		SUB_CLOSE_KEY	            0x08

#define	    MAIN_OPEN_KEY_CLEAR         ~MAIN_OPEN_KEY
#define		MAIN_CLOSE_KEY_CLEAR        ~MAIN_CLOSE_KEY
#define	    SUB_OPEN_KEY_CLEAR          ~SUB_OPEN_KEY
#define		SUB_CLOSE_KEY_CLEAR         ~SUB_CLOSE_KEY

#define		MAIN_KEY_CLEAR              ~(MAIN_OPEN_KEY | MAIN_CLOSE_KEY)
#define		SUB_KEY_CLEAR               ~(SUB_OPEN_KEY  | SUB_CLOSE_KEY)

#define	    MAIN_SUB_OPEN_KEY_CLEAR     ~(MAIN_OPEN_KEY  | SUB_OPEN_KEY)
#define		MAIN_SUB_CLOSE_KEY_CLEAR    ~(MAIN_CLOSE_KEY | SUB_CLOSE_KEY)

#define		CLEAR_ALL_DOOR_KEY	    0xf0


