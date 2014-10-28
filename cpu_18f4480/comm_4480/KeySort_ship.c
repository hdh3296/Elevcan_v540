
#include    <pic18.h>
//#include    <pic18fxx8.h>

//#include        "iomap.h"
#include        "iodef.h"
#include        "fontout.h"
#include        "comdata.h"
#include        "esdots.h"
#include        "keysort.h"
#include        "setup.h"

#include        "..\..\system_com\memory_map.h"
//#include        "..\can_4480\you_can.h"



unsigned int  xIdPt;
unsigned char xtmpadr;
unsigned char xTmpCurFloor;
unsigned char xtmptop;
unsigned char xtmpstart;
unsigned char xtmpnext;
unsigned char xtmphigh;
unsigned char xtmplow;
unsigned char xdestflr;
unsigned char xyoufloor;
unsigned char Priority;



unsigned char maxlowflrbuf[MAX_ELEV];
unsigned char maxtopflrbuf[MAX_ELEV];
unsigned char maxtopflr;
unsigned char maxlowflr;


unsigned char Equal[MAX_ELEV];

//#define		SELECTED		7
#define		FIRST_OFFSET	8
//#define		THIRD_OFFSET	30

#define     CalCulate(a,b,c,d,e)		((a-b) + (c-d) + e)                     		  
//#define     CalCulateLong(a,b,c,d,e)	((a-b) >= (c-d))	? ((a-b) + e) : ((c-d) + e)                     		  


/*
unsigned char CalCulate(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e)
{
	unsigned char i;
	
	i = ((a-b) + (c-d) + e);
	return(i);
}
*/


unsigned char CalCulateLong(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e)
{
	unsigned char i;

	if( (a-b) >= (c-d)){
		i=((a-b) + e);
	}
	else{
		i=( (c-d) + e);
	}
	return(i);
}

unsigned char  GetElevPointer(unsigned int id)
{
    xtmpadr=MyAddress-1;         
	xIdPt=IsBufferPt(id);
    xTmpCurFloor=RcvBuf[xIdPt]-1;
    xtmptop=RcvBuf[xIdPt+SL_mTopFlr];
    xtmpstart=RcvBuf[xIdPt+SL_mStartFloor];
    xtmpnext=RcvBuf[xIdPt+SL_mMostLongDst];
    xtmphigh=RcvBuf[xIdPt+mHighFloor];
    xtmplow=RcvBuf[xIdPt+mLowFloor];
    xdestflr=RcvBuf[xIdPt+DEST_FLR];
	xyoufloor=RcvBuf[xIdPt+DEST_FLR];


	if(IsCarUpWard(xIdPt)){
		if(xtmphigh & UPDN_CAR_READY){
			xyoufloor=xtmphigh;
		}
	}
	else if(IsCarDnWard(xIdPt)){
		if(xtmplow & UPDN_CAR_READY){
			xyoufloor=xtmplow;
		}
	}




//	else{
//		xyoufloor=xTmpCurFloor;
//	}


/*
	if(IsCarArrive(xIdPt)){
		if(IsCarUpWard(xIdPt))		xyoufloor=RcvBuf[xIdPt+mHighFloor];
		else if(IsCarDnWard(xIdPt))	xyoufloor=RcvBuf[xIdPt+mLowFloor];
		else						xyoufloor=0;						
	}
	else{
		xyoufloor=RcvBuf[xIdPt+DEST_FLR];
	}
*/

	return(0);
}




unsigned char  SyncButtonCheck(void)
{
	unsigned  int   IdPt; 

	IdPt=IsBufferPt(SrcAddress);
	if(IsMyFamilyService(IdPt))	return(0);

	if(b_MyFamily){
		if(SrcAddress  != LocalNumber)	return(0);
	}		
	return(1);		
}







unsigned int  SelElevFlrDsbCheck(unsigned int id)
{
/*
    unsigned char i,j,k;
    unsigned char DsbFlr[4];
    unsigned int  IdPt;

	IdPt=IsBufferPt(id); 
    
    DsbFlr[0]=RcvBuf[IdPt + FLR_ON_OFF0];
    DsbFlr[1]=RcvBuf[IdPt + FLR_ON_OFF1];
    DsbFlr[2]=RcvBuf[IdPt + FLR_ON_OFF2];
    DsbFlr[3]=RcvBuf[IdPt + FLR_ON_OFF3];


    i=(MyAddress-1)/8;
    j=(MyAddress-1)%8;
    k=(0x01 << j);
   
    if(!(DsbFlr[i] & k)){	
        return(1);
    }
*/
    return(0);
}


unsigned int SelElevNoUseCheck(unsigned int id)
{
    unsigned int IdPt;

    maxtopflrbuf[id]=0x00;
    maxlowflrbuf[id]=0xff;

	IdPt=IsBufferPt(id);

    if(IsCarVip(IdPt))              return(1);
    if(IsCarManual(IdPt))           return(1);
    if(IsCarEmg(IdPt))              return(1);
    if(IsCarParking(IdPt))          return(1);
    if(IsCarFire(IdPt))             return(1); 
	if(IsCarExtButClr(IdPt))        return(1);

	if(IsMyFamilyService(IdPt)){
		if(id != LocalNumber)		return(1); 	//10,05
	}

	if(b_MyFamily){								//10,05
		if(id != LocalNumber)		return(1); 	//10,05
	}											//10,05


#ifdef  VIP_TEMP
    SelHostAdr=LocalNumber;    
    if(id != LocalNumber)           return(1);    
#endif


  maxtopflrbuf[id]=RcvBuf[IdPt + SL_mTopFlr];		//10,05
  maxlowflrbuf[id]=RcvBuf[IdPt + SL_mStartFloor];	//10,05

    return(0);
}



unsigned int SelElevDsbCheck(unsigned int id)
{
    
    if(SelElevNoUseCheck(id)){
		MoveTime[id]=0;
       	return(1);
	}


	if(IsCarMove(xIdPt)){
		MoveTime[id]=0;
	}

	if(IsYouFlrNoneWard(xtmphigh)){
		if(IsYouFlrNoneWard(xtmplow)){
			MoveTime[id]=0;
		}
	}

    if(MoveTime[id] > MAX_CALL_TIME){
		if( !IsYouFlrEqualMe(xTmpCurFloor,xtmpadr)){
	        MoveTime[id]= MAX_CALL_TIME + 1;
			return(1);
		}
    }
 
    return(0);
}



unsigned char   UpKeyTopDsbCheck(unsigned int id)
{
/*
    unsigned int IdPt;         
    unsigned char  tmpadr,tmptop;

    tmpadr=MyAddress-1;

	IdPt=IsBufferPt(id);
    tmptop=RcvBuf[IdPt+SL_mTopFlr];
*/

	GetElevPointer(id);
    if(xtmpadr >= xtmptop)    return(1); 
    else                    return(0); 
}



unsigned char   DnKeyTopDsbCheck(unsigned int id)
{
/*
    unsigned int IdPt;         
    unsigned char  tmpadr,tmptop;

    tmpadr=MyAddress-1;
	IdPt=IsBufferPt(id);
    tmptop=RcvBuf[IdPt+SL_mTopFlr];
    if(tmpadr > tmptop)    return(1); 
    else                   return(0); 
*/

	GetElevPointer(id);
    if(xtmpadr > xtmptop)    	return(1); 
    else                  		return(0); 
}



unsigned char   UpKeyLowDsbCheck(unsigned int id)
{
/*
    unsigned int IdPt;         
    unsigned char  tmpadr,tmpFlrOffsetPt;

    tmpadr=MyAddress-1;
	IdPt=IsBufferPt(id);
    tmpFlrOffsetPt=RcvBuf[IdPt+SL_mStartFloor];
*/

	GetElevPointer(id);
    if(xtmpadr < xtmpstart)   	return(1); 
    else                     	return(0); 
}


unsigned char   DnKeyLowDsbCheck(unsigned int id)
{

/*
    unsigned int IdPt;         
    unsigned char  tmpadr,tmpFlrOffsetPt;

    tmpadr=MyAddress-1;
	IdPt=IsBufferPt(id);
    tmpFlrOffsetPt=RcvBuf[IdPt+SL_mStartFloor];
*/

	GetElevPointer(id);
    if(xtmpadr <= xtmpstart)    return(1); 
    else                  		return(0); 
}



unsigned char	DsbChk(unsigned int id)
{

    if(SelElevFlrDsbCheck(id))  return(1);
    if(SelElevDsbCheck(id))     return(1);
  
    if(IsCarFull(xIdPt))        return(1);
	if(IsCarMostService(xIdPt))	return(1);

	return(0);
}








/*
unsigned char Chk1(unsigned char id)
{

	unsigned char ret;
	ret=0;

	GetElevPointer(id);

	if(IsReadyFlrHighMe(xIdPt,xtmpadr)){
		if(IsReadyFlrCarOrDn(xIdPt)){
			ret=1;
		}
	}		
	else if(IsReadyFlrHighOrEqualMe(xIdPt,xTmpCurFloor)){
		if(IsReadyFlrCarOrUp(xIdPt)){
			ret=1;
		}
	}
	
	return(ret);			
}


unsigned char Chk2(unsigned char id)
{
	unsigned char ret;
	ret=0;

	GetElevPointer(id);

	if(IsReadyFlrLowMe(xIdPt,xtmpadr)){
		if(IsReadyFlrCarOrUp(xIdPt)){
			ret=1;
		}
	}		
	else if(IsReadyFlrLowOrEqualMe(xIdPt,xTmpCurFloor)){
		if(IsReadyFlrCarOrDn(xIdPt)){
			ret=1;
		}
	}			

	return(ret);
}
//////////



unsigned char  NextUpKeyDsbChk(unsigned int id)
{

    unsigned char  ret;


	ret=0;

////////////////////////////////////////////////
	if(IsCarDnWard(xIdPt)){
		ret=Chk2(id);
	}
	else if(IsCarUpWard(xIdPt)){
		if(xtmpadr > xTmpCurFloor){            
			if(IsReadyFlrLowMe(xIdPt,xtmpadr)){
				if(IsReadyFlrHighOrEqualMe(xIdPt,xTmpCurFloor)){
					if(IsReadyFlrCarOrUp(xIdPt)){
						ret=1;
					}
				}
			}			
		}
		else if(xtmpadr < xTmpCurFloor){            
			ret=Chk1(id);
		}
	}

	return(ret);  
}



unsigned char  NextDnKeyDsbChk(unsigned int id)
{

    unsigned char  ret;


	ret=0;

////////////////////////////////////////////////
	if(IsCarUpWard(xIdPt)){
		ret=Chk1(id);
	}
	else if(IsCarDnWard(xIdPt)){

		if(xtmpadr < xTmpCurFloor){            
			if(IsReadyFlrHighMe(xIdPt,xtmpadr)){
				if(IsReadyFlrLowOrEqualMe(xIdPt,xTmpCurFloor)){
					if(IsReadyFlrCarOrDn(xIdPt)){
						ret=1;
					}
				}
			}			
		}
		else if(xtmpadr > xTmpCurFloor){
			ret=Chk2(id);
		}
	}

	return(ret);  
}
*/


/*
unsigned char  DestOffset(unsigned char UpDn)
{
	unsigned char destf;

	destf=RcvBuf[xIdPt+DEST_FLR];

//	if(IsDestFlrEqualMe(xIdPt,xtmpadr)){
	if(IsYouFlrEqualMe(destf,xtmpadr)){
		if(UpDn){
//			if(IsDestFlrCarAndUp(xIdPt))				return(1);	
//			if(IsDestFlrOnlyCar(xIdPt))					return(2);	
//			if(IsDestFlrUp(xIdPt))						return(3);	


			if(IsYouCarAndUp(destf))				return(1);	
			if(IsYouOnlyCar(destf))					return(2);	
			if(IsYouUp(destf))						return(3);	
		}
		else{
//			if(IsDestFlrCarAndDn(xIdPt))				return(1);	
//			if(IsDestFlrOnlyCar(xIdPt))					return(2);	
//			if(IsDestFlrDn(xIdPt))						return(3);	

			if(IsYouCarAndDn(destf))				return(1);	
			if(IsYouOnlyCar(destf))					return(2);	
			if(IsYouDn(destf))						return(3);	
		}		
	}
	
	return(0);
}
*/



unsigned char  CarKeyCheck(unsigned char startcur,unsigned char stopcur)
{

    unsigned char i,j,k,cnt;
    unsigned char tmpcarkey[4];
    unsigned int  zz;

    if(startcur < xtmpstart)	return(0);
    if(startcur > xtmptop)		return(0);

    if(stopcur > xtmptop)		return(0);
    if(stopcur < xtmpstart)		return(0);

    if(startcur > stopcur)		return(0);
         
	cnt=0;

    tmpcarkey[0]=RcvBuf[xIdPt + SL_mCarKey1];
    tmpcarkey[1]=RcvBuf[xIdPt + SL_mCarKey9];
    tmpcarkey[2]=RcvBuf[xIdPt + SL_mCarKey17];
    tmpcarkey[3]=RcvBuf[xIdPt + SL_mCarKey25];
			
	zz=(unsigned int)(startcur);
    i=(unsigned char)(zz / 8);
    j=(unsigned char)(zz % 8);
    k=(0x01 << j);

	for(;startcur <= stopcur;startcur++){
		if(tmpcarkey[i] & k){
			cnt++;
		}

		k=(k<<1);
		if(k==0){
			k=0x01;
   			i++;
		}	
	}		

    return(cnt);

}



unsigned char  UpKeyCarKeyDsbCheck(void)
{
	unsigned char ret,lfl,tfl;

	ret=1;
    if(IsCarUpWard(xIdPt)){
		if(xtmpadr > xTmpCurFloor){
			if(IsYouCarOrUp(xyoufloor)){
				tfl = xtmpadr-1;
				lfl = xTmpCurFloor + 1;
				if(CarKeyCheck(lfl,tfl) >= 2)	ret=0;				
			}			
		}
		else if(xtmpadr < xTmpCurFloor){
			tfl = xtmptop;
			lfl = xTmpCurFloor + 1;
			if(CarKeyCheck(lfl,tfl) >= 2)	ret=0;				
		}
	}
    else if(IsCarDnWard(xIdPt)){
		tfl=xTmpCurFloor-1;
		lfl=xtmpstart;			

		if(CarKeyCheck(lfl,tfl) >= 2)	ret=0;				
	}
	return(ret);
}


unsigned char  DnKeyCarKeyDsbCheck(void)
{
	unsigned char ret,lfl,tfl;

	ret=1;

    if(IsCarUpWard(xIdPt)){
		lfl=xTmpCurFloor+1;
		tfl=xtmptop;			

		if(CarKeyCheck(lfl,tfl) >= 2)	ret=0;				
	}

    else if(IsCarDnWard(xIdPt)){
		if(xtmpadr < xTmpCurFloor){
			if(IsYouCarOrDn(xyoufloor)){
				tfl = xTmpCurFloor-1;
				lfl = xtmpadr + 1;			
				if(CarKeyCheck(lfl,tfl) >= 2)	ret=0;				
			}				
		}
		else if(xtmpadr > xTmpCurFloor){
			tfl=xTmpCurFloor-1;
			lfl=xtmpstart;			

			if(CarKeyCheck(lfl,tfl) >= 2)	ret=0;				
		}
	}
    return(ret); 
}



unsigned char  UpKeyReadyChk(unsigned int id)
{
    unsigned char  ret;

	GetElevPointer(id);

	if(UpKeyCarKeyDsbCheck() == 0)	return(0);

	if(IsYouFlrNoneWard(xtmpnext))	return(1);
	if(IsYouFlrEqualMe(xtmpnext,(xdestflr & ONLY_FLR)))	return(1);
	if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
		if(IsYouUp(xdestflr))	return(2);
	}
	if(IsYouFlrEqualMe(xtmpnext,xtmpadr)){
		if(IsYouUp(xtmpnext))	return(2);
	}


    ret=1;

    if(IsCarUpWard(xIdPt)){
		if(xtmpadr > xTmpCurFloor){
			if(IsYouFlrLowMe(xtmpnext,xtmpadr)){
				if( IsYouFlrHighMe(xtmpnext,(xdestflr & ONLY_FLR))){
					if(IsYouUp(xtmpnext)){
						ret=0;
					}
				}
			}
		}
		else if(xtmpadr < xTmpCurFloor){
			if(IsYouDn(xtmpnext)){
				if(!IsYouFlrEqualMe(xtmpnext,(xdestflr & ONLY_FLR))){
					ret=0;
				}
			}
			if(IsYouFlrLowMe(xtmpnext,xtmpadr)){
				if(IsYouUp(xtmpnext)){
					ret=0;
				}
			}
		}
	}
    else if(IsCarDnWard(xIdPt)){
		if(IsYouFlrLowMe(xtmpnext,(xdestflr & ONLY_FLR))){
			if(IsYouDn(xtmpnext)){
				ret=0;
			}	
		}
		if(IsYouFlrLowMe(xtmpnext,xtmpadr)){
			if(IsYouUp(xtmpnext)){
				ret=0;
			}	
		}
	}
			
    return(ret); 
}



unsigned char  DnKeyReadyChk(unsigned int id)
{

    unsigned char  ret;

	GetElevPointer(id);

	if(DnKeyCarKeyDsbCheck() == 0)	return(0);
	if(IsYouFlrEqualMe(xtmpnext,(xdestflr & ONLY_FLR)))	return(1);
	if(IsYouFlrNoneWard(xtmpnext))	return(1);
	if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
		if(IsYouDn(xdestflr))	return(2);
	}
	if(IsYouFlrEqualMe(xtmpnext,xtmpadr)){
		if(IsYouDn(xtmpnext))	return(2);
	}

    ret=1;


    if(IsCarUpWard(xIdPt)){
		if(IsYouFlrHighMe(xtmpnext,xtmpadr)){
			if(IsYouDn(xtmpnext)){
				ret=0;
			}	
		}
		if(IsYouFlrHighMe(xtmpnext,(xdestflr & ONLY_FLR))){
			if(IsYouUp(xtmpnext)){
				ret=0;
			}	
		}
	}

    else if(IsCarDnWard(xIdPt)){
		if(xtmpadr < xTmpCurFloor){
			if(IsYouFlrHighMe(xtmpnext,xtmpadr)){
				if(IsYouFlrLowMe(xtmpnext,(xdestflr & ONLY_FLR))){
					if(IsYouDn(xtmpnext)){
						ret=0;
					}
				}
			}		
		}
		else if(xtmpadr > xTmpCurFloor){
			if(IsYouUp(xtmpnext)){	
				if(!IsYouFlrEqualMe(xtmpnext,(xdestflr & ONLY_FLR))){
					ret=0;
				}
			}				
			if(IsYouFlrHighMe(xtmpnext,xtmpadr)){
				if(IsYouDn(xtmpnext)){
					ret=0;
				}	
			}
		}
	}
    return(ret); 
}



void	CarCurStatus(unsigned int id)
{
	
	Equal[id]=100;

	if(IsYouFlrEqualMe(xyoufloor,xtmpadr))				Equal[id]=0;		
	else if(IsYouFlrEqualMe(xyoufloor,xTmpCurFloor)){
 		if(IsCarMove(xIdPt))		Equal[id]=3;		
		else{
			if(IsCarClose(xIdPt))	Equal[id]=1;
			else					Equal[id]=2;	
		}
	}
	else{
 		Equal[id]=9;		
	}


/*
	else if(IsYouFlrHighMe(xyoufloor,xTmpCurFloor)){
 		if(IsCarMove(xIdPt))		Equal[id]=1;		
		else						Equal[id]=2;		
	}
	else if(IsYouFlrLowMe(xyoufloor,xTmpCurFloor)){
 		if(IsCarMove(xIdPt))		Equal[id]=1;
		else						Equal[id]=2;								
	}
	else{
 		if(IsCarMove(xIdPt))		Equal[id]=9;		
		else{
			if(IsCarClose(xIdPt))	Equal[id]=3;
			else					Equal[id]=4;	
		}
	}
*/


//	else if(IsYouFlrEqualMe(xyoufloor,xtmpadr))		Equal[id]=0;		

//	else if(IsCarMove(xIdPt)){
//		if(IsYouFlrEqualMe(xdestflr,xTmpCurFloor)	Equal[id]=9;		
//	}																	

	
/*
	if(IsCarUpWard(xIdPt)){
		if(IsYouFlrEqualMe(xdestflr,xTmpCurFloor)){
			if(IsCarMove(xIdPt))	Equal[id]=0;																	
		}
		else if(IsYouFlrHighMe(xdestflr,xTmpCurFloor)){
			Equal[id]=1;																	
		}
		else if(IsYouFlrAnyWard(xdestflr)){
			Equal[id]=4;																	
		}
	}
	else if(IsCarDnWard(xIdPt)){
		if(IsYouFlrEqualMe(xdestflr,xTmpCurFloor)){
			if(IsCarMove(xIdPt))	Equal[id]=0;																	
		}
		else if(IsYouFlrLowMe(xdestflr,xTmpCurFloor)){
			Equal[id]=1;																	
		}			
		else if(IsYouFlrAnyWard(xdestflr)){
			Equal[id]=4;																	
		}
	}            
	else{
		if(IsCarClose(xIdPt))	Equal[id]=2;	
		else					Equal[id]=3;	
	}
*/
}



/*
unsigned char CalCulateX(unsigned char cu,unsigned char my,unsigned char de)
{                   		  
	unsigned char	i,j;

	i = CalCulate(cu,de,0,0,FIRST_OFFSET);                   		  
	j = CalCulate(my,de,0,0,FIRST_OFFSET);

	if(j > (FIRST_OFFSET + 3)){
		j = CalCulate(cu,de,my,de,FIRST_OFFSET);
	}
    else{	  
		if(i > j)	j=i;
	}

	return(j);
}



unsigned char CalCulateY(unsigned char de,unsigned char cu,unsigned char my)
{                   		  
	unsigned char	i,j;

	i = CalCulate(de,cu,0,0,FIRST_OFFSET);                   		  
	j = CalCulate(de,my,0,0,FIRST_OFFSET);



	if(j > (FIRST_OFFSET + 3)){
		j = CalCulate(de,cu,de,my,FIRST_OFFSET);
	}
    else{	  
		if(i > j)	j=i;
	}

	if(i > j)	j=i;

	return(j);
}

*/



/*
unsigned char  UpKeyCalcElev(unsigned int id)
{
    unsigned char ret;

    UpKeyCalu[id] = 0xff;

	GetElevPointer(id);

	if(DsbChk(id))	return(1);

    if(ButtonType==0){
        if(UpKeyTopDsbCheck(id))    return(1);
        if(UpKeyLowDsbCheck(id))    return(1);
    }        


	if(UpKeyReadyChk(id)==0){
		UpKeyCalu[id] = 100;
		return(0);
	}

	CarCurStatus(id);

    ret=1;

        
    if(Up_Key_Valid || UP_KEY_LAMP){

		ret=0;                                                
 					
        if(xtmpadr < xTmpCurFloor){            
            if(IsCarDnWard(xIdPt)){
				if(IsYouDn(xyoufloor)){					
					UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,THIRD_OFFSET);                     		  
				}
				else{
					if(IsYouFlrLowMe(xyoufloor,xtmpadr)){
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                     		  
					}
					else{
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
					}
				}
            }            
            else if(IsCarUpWard(xIdPt)){
				if(IsYouUp(xyoufloor)){
					UpKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,THIRD_OFFSET);                     		  
				}
				else{
					UpKeyCalu[id] = CalCulate((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);                     		  
				}
            }            
            else{
				UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
            }

        }
        else if(xtmpadr > xTmpCurFloor){
            if(IsCarUpWard(xIdPt)){
				UpKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);                     		  
				if(IsYouCarOrUp(xyoufloor)){
					if(IsYouFlrLowMe(xyoufloor,xtmpadr)){
						UpKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);                     		  
					}
				}
			}
            else if(IsCarDnWard(xIdPt)){
				if(IsYouDn(xyoufloor)){
					UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,THIRD_OFFSET);                     		  
				}			
				else{
					UpKeyCalu[id] = CalCulate(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                     		  
				}
            }            
            else{
				UpKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);                     		  
            }
        } 
        else{
            if(IsCarUpWard(xIdPt)){
                if(IsCarMainOpen(xIdPt) && bIamXSubDoor){
                    UpKeyCalu[id] = 0;
                }
                else if(IsCarSubOpen(xIdPt) && !bIamXSubDoor){
                    UpKeyCalu[id] = 0;
                }
                else if(IsYouUp(xdestflr) && IsYouFlrEqualMe(xdestflr,xtmpadr)){
                    UpKeyCalu[id] = 1;  
                }
                else if(IsYouFlrHighMe(xyoufloor,xtmpadr)){
					if(IsYouUp(xyoufloor)){
						UpKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,THIRD_OFFSET);                     		  
					}
					else{
						UpKeyCalu[id] = CalCulate((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);                     		  
					}
                }
                else{
                    UpKeyCalu[id] = 1;  
                }
            }
            else if(IsCarDnWard(xIdPt)){    
                if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
	                if(IsYouUp(xdestflr)){
	                    UpKeyCalu[id] = 1;  
	                }
					else if(IsYouDn(xdestflr)){
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,THIRD_OFFSET);                     		  
					}
					else{
		                UpKeyCalu[id] = 3;  
					}
				}
                else{
					if(IsYouDn(xtmplow)){
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,THIRD_OFFSET);                     		  
					}
					else{
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,(xtmplow & ONLY_FLR),xtmpadr,(xtmplow & ONLY_FLR),FIRST_OFFSET);                     		  
					}
                }
            }
            else{    
                UpKeyCalu[id] = 2; 
            }
		}
    }

    return(ret); 
}
*/




unsigned char  UpKeyCalcElev(unsigned int id)
{
    unsigned char ret=0;


    UpKeyCalu[id] = 0xff;

	GetElevPointer(id);

	if(DsbChk(id))	return(1);

    if(ButtonType==0){
        if(UpKeyTopDsbCheck(id))    return(1);
        if(UpKeyLowDsbCheck(id))    return(1);
    }        

	if(UpKeyReadyChk(id)==0){
		UpKeyCalu[id] = 100;
		return(1);
	}

	CarCurStatus(id);


    ret=1;        
    if(Up_Key_Valid || UP_KEY_LAMP){
		ret=0;                                                 					
        if(xtmpadr < xTmpCurFloor){            
            if(IsCarDnWard(xIdPt)){
				if(IsYouDn(xyoufloor)){					
					UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,FIRST_OFFSET);                     		  
				}
				else{
					if(IsYouFlrHighMe(xyoufloor,xtmpadr)){	
						UpKeyCalu[id]= CalCulate(0,0,xTmpCurFloor,xtmpadr,FIRST_OFFSET);
					}
					else{	
						UpKeyCalu[id]= CalCulateLong(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),(FIRST_OFFSET-1));
					}
				}
            }            
            else if(IsCarUpWard(xIdPt)){
				UpKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,FIRST_OFFSET);
				if(IsYouOnlyCar(xyoufloor)){
					UpKeyCalu[id]= CalCulateLong((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);
				}	
            }            
            else{
				UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
            }
        }
        else if(xtmpadr > xTmpCurFloor){
            if(IsCarUpWard(xIdPt)){
				UpKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);               		  
			}
            else if(IsCarDnWard(xIdPt)){
				UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,FIRST_OFFSET);
				if(!IsYouDn(xyoufloor)){
					UpKeyCalu[id]= CalCulateLong(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);
				}
            }            
            else{
				UpKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);  
            }
        } 
        else{
            if(IsCarUpWard(xIdPt)){
                if(IsCarMainOpen(xIdPt) && !bIamXSubDoor){
                    UpKeyCalu[id] = 0;
                }
                else if(IsCarSubOpen(xIdPt) && bIamXSubDoor){
                    UpKeyCalu[id] = 0;
                }
                else if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
                    UpKeyCalu[id] = 1;  
                }
                else if(IsYouFlrHighMe(xyoufloor,xtmpadr)){
					if(IsYouOnlyCar(xyoufloor)){					
						UpKeyCalu[id]= CalCulateLong((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);
					}
					if(IsYouUp(xyoufloor)){
						UpKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,FIRST_OFFSET);                     		  
					}
					else{
						UpKeyCalu[id] = CalCulate((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpstart,FIRST_OFFSET);                     		  
					}
                }
                else{
                    UpKeyCalu[id] = 1;  
                }
            }
            else if(IsCarDnWard(xIdPt)){    
                if(IsYouFlrEqualMe(xyoufloor,xtmpadr)){
	                if(IsYouUp(xyoufloor)){
	                    UpKeyCalu[id] = 1;  
	                }
					else if(IsYouDn(xyoufloor)){
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,FIRST_OFFSET);                     		  
					}
					else{
		                UpKeyCalu[id] = 3;  
					}
				}
                else{
					if(IsYouDn(xyoufloor)){
						UpKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,FIRST_OFFSET);                     		  
					}
					else{
						UpKeyCalu[id]= CalCulateLong(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);
					}
                }
            }
            else{    
                UpKeyCalu[id] = 2; 
            }
		}
    }

    return(ret); 
}




unsigned char  DnKeyCalcElev(unsigned int id)
{
    unsigned char  ret=0;



	GetElevPointer(id);

    DnKeyCalu[id] = 0xff;

	if(DsbChk(id))	return(1);


    if(ButtonType==0){
        if(DnKeyTopDsbCheck(id))    return(1);
        if(DnKeyLowDsbCheck(id))    return(1);
    }        


	if(DnKeyReadyChk(id)==0){
		DnKeyCalu[id] = 100;
		return(1);
	}

	CarCurStatus(id);

    ret=1;

    if(Dn_Key_Valid || DN_KEY_LAMP){
        ret=0;                        
        if(xtmpadr < xTmpCurFloor){
            if(IsCarUpWard(xIdPt)){
				DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,FIRST_OFFSET);                     		  
				if(!IsYouUp(xyoufloor)){
					DnKeyCalu[id]= CalCulateLong((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);
				}
			}
            else if(IsCarDnWard(xIdPt)){
				DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);
            }            
            else{				
				DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
            }
        }
        else if(xtmpadr > xTmpCurFloor){
            if(IsCarUpWard(xIdPt)){
				if(IsYouUp(xyoufloor)){
					DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,FIRST_OFFSET);                     		  
				}
				else{
					if(IsYouFlrLowMe(xyoufloor,xtmpadr)){	
						DnKeyCalu[id]= CalCulateLong(0,0,xtmpadr,xTmpCurFloor,FIRST_OFFSET);
					}
					else{	
						DnKeyCalu[id]= CalCulateLong((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(FIRST_OFFSET-1));
					}
				}
            }            
            else if(IsCarDnWard(xIdPt)){
				DnKeyCalu[id] = CalCulate(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmptop,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                     		  
				if(IsYouOnlyCar(xyoufloor)){					
					DnKeyCalu[id] = CalCulateLong(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                   		  
				}
            }            
            else{
				DnKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);                     		  
            }
        } 
        else{
            if(IsCarDnWard(xIdPt)){
                if(IsCarMainOpen(xIdPt) && !bIamXSubDoor){
                    DnKeyCalu[id] = 0;   
                }
                else if(IsCarSubOpen(xIdPt) && bIamXSubDoor){
                    DnKeyCalu[id] = 0;  
                }
                else if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
                    DnKeyCalu[id] = 1;  
                }
                else if(IsYouFlrLowMe(xyoufloor,xtmpadr)){
					if(IsYouOnlyCar(xyoufloor)){					
						DnKeyCalu[id] = CalCulateLong(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                   		  
					}
					else if(IsYouDn(xyoufloor)){
						DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,FIRST_OFFSET);                     		  
					}
					else{
						DnKeyCalu[id] = CalCulate(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmptop,xtmpadr,FIRST_OFFSET);                     		  
					}
                }
                else{
                    DnKeyCalu[id] = 1;  
                }
            }
            else if(IsCarUpWard(xIdPt)){    
                if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
	                if(IsYouDn(xdestflr)){
	                    DnKeyCalu[id] = 1;  
	                }
					else if(IsYouUp(xdestflr)){
						DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,FIRST_OFFSET);                     		  
					}
					else{
                		DnKeyCalu[id] = 3; 
					}
				}
                else{
	                if(IsYouUp(xyoufloor)){
						DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,FIRST_OFFSET);                     		  
					}
					else{
						DnKeyCalu[id] = CalCulateLong((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);                   		  
					}
                }
            }
            else{    
                DnKeyCalu[id] = 2;  
            }
        }
    }



    return(ret); 
}




/*
unsigned char  DnKeyCalcElev(unsigned int id)
{
    unsigned char  ret;

	GetElevPointer(id);

    DnKeyCalu[id] = 0xff;

	if(DsbChk(id))	return(1);

    if(ButtonType==0){
        if(DnKeyTopDsbCheck(id))    return(1);
        if(DnKeyLowDsbCheck(id))    return(1);
    }        

	if(DnKeyReadyChk(id)==0){
		DnKeyCalu[id] = 100;
		return(0);
	}

	CarCurStatus(id);

	ret=1;

    if(Dn_Key_Valid || DN_KEY_LAMP){

		ret=0;

        if(xtmpadr < xTmpCurFloor){
            if(IsCarUpWard(xIdPt)){
				if(IsYouUp(xyoufloor)){
					DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,THIRD_OFFSET);                     		  
				}			
				else{
					DnKeyCalu[id] = CalCulate((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);                     		  
				}
			}
            else if(IsCarDnWard(xIdPt)){
				DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
				if(IsYouCarOrDn(xyoufloor)){
					if(IsYouFlrHighMe(xyoufloor,xtmpadr)){
						DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
					}
				}
            }            
            else{
				DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpadr,0,0,FIRST_OFFSET);                     		  
            }
        }
        else if(xtmpadr > xTmpCurFloor){
            if(IsCarUpWard(xIdPt)){
				if(IsYouUp(xyoufloor)){
					DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,THIRD_OFFSET);                     		  
				}
				else{
					if(IsYouFlrHighMe(xyoufloor,xtmpadr)){
						DnKeyCalu[id] = CalCulate((xyoufloor & ONLY_FLR),xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,FIRST_OFFSET);                     		  
					}
					else{
						DnKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);                     		  
					}
				}
            }            
            else if(IsCarDnWard(xIdPt)){
				if(IsYouDn(xyoufloor)){
					DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,THIRD_OFFSET);                     		  
				}
				else{
					DnKeyCalu[id] = CalCulate(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                     		  
				}
            }            
            else{
				DnKeyCalu[id] = CalCulate(xtmpadr,xTmpCurFloor,0,0,FIRST_OFFSET);                     		  
            }
        } 
        else{
            if(IsCarDnWard(xIdPt)){
                if(IsCarMainOpen(xIdPt) && !bIamXSubDoor){
                    DnKeyCalu[id] = 0;   
                }
                else if(IsCarSubOpen(xIdPt) && bIamXSubDoor){
                    DnKeyCalu[id] = 0;  
                }
                else if(IsYouDn(xdestflr) && IsYouFlrEqualMe(xdestflr,xtmpadr)){
                    DnKeyCalu[id] = 1;  
                }
                else if(IsYouFlrLowMe(xyoufloor,xtmpadr)){
					if(IsYouDn(xyoufloor)){
						DnKeyCalu[id] = CalCulate(xTmpCurFloor,xtmpstart,xtmpadr,xtmpstart,THIRD_OFFSET);                     		  
					}
					else{
						DnKeyCalu[id] = CalCulate(xTmpCurFloor,(xyoufloor & ONLY_FLR),xtmpadr,(xyoufloor & ONLY_FLR),FIRST_OFFSET);                     		  
					}
                }
                else{
                    DnKeyCalu[id] = 1;  
                }
            }
            else if(IsCarUpWard(xIdPt)){    
                if(IsYouFlrEqualMe(xdestflr,xtmpadr)){
	                if(IsYouDn(xdestflr)){
	                    DnKeyCalu[id] = 1;  
	                }
					else if(IsYouUp(xdestflr)){
						DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,THIRD_OFFSET);                     		  
					}
					else{
                		DnKeyCalu[id] = 3; 
					}
				}
                else{
					if(IsYouUp(xtmphigh)){
						DnKeyCalu[id] = CalCulate(xtmptop,xTmpCurFloor,xtmptop,xtmpadr,THIRD_OFFSET);                     		  
					}
					else{
						DnKeyCalu[id] = CalCulate((xtmphigh & ONLY_FLR),xTmpCurFloor,(xtmphigh & ONLY_FLR),xtmpadr,FIRST_OFFSET);                     		  
					}
                }

            }
            else{    
                DnKeyCalu[id] = 2;  
            }

        }
    }

    return(ret); 
}

*/


void	DownButtonClear(void)
{
	DN_KEY_LAMP=0;  
	DnButtonTime=0;
	Dn_Key_Valid=0;
	Dn_Key_Clear=0;
	Tx0ConfirmCnt=0;
	TogDnKeyBitSet=0;
	TogDnKeyBitReset=0;

	MoveTime[0]=0;
	MoveTime[1]=0;
	MoveTime[2]=0;
	MoveTime[3]=0;

/*
	CallCounter[0]=0;
	CallCounter[1]=0;
	CallCounter[2]=0;
	CallCounter[3]=0;
*/
}


void	UpButtonClear(void)
{
	UP_KEY_LAMP=0;
	UpButtonTime=0;
	Up_Key_Valid=0;
	Up_Key_Clear=0;
	Tx1ConfirmCnt=0;
	TogUpKeyBitReset=0;
	TogUpKeyBitSet=0;


/*
	CallCounter[0]=0;
	CallCounter[1]=0;
	CallCounter[2]=0;
	CallCounter[3]=0;
*/

	MoveTime[0]=0;
	MoveTime[1]=0;
	MoveTime[2]=0;
	MoveTime[3]=0;
}



void    UpDownKey(void)
{

    unsigned  char  i;
    unsigned  char  valid;
    unsigned  int   IdPt; 


	IdPt=IsBufferPt(LocalNumber);
	if(IsMyFamilyService(IdPt))	b_MyFamily=1;
	else						b_MyFamily=0;



    valid=1;

    i=0;

	maxtopflr =0x0;
	maxlowflr =0xff;
    

    for(i=0;i<MAX_ELEV;i++){
        if(!SelElevNoUseCheck(i)){
            if(!SelElevFlrDsbCheck(i)){
                valid=0;
            }
        }   
		else{
			MoveTime[i]=0;
		}

		if(maxtopflr < maxtopflrbuf[i])	maxtopflr = maxtopflrbuf[i];	 
		if(maxlowflr > maxlowflrbuf[i])	maxlowflr = maxlowflrbuf[i];	 
    }



   	if(ButtonType == 0){
    	if((MyAddress-1) <= maxlowflr){
			DownButtonClear();
		}
	}

	else if(!bToggleOn){
    	if((MyAddress-1) < maxlowflr){
			DownButtonClear();
		}
	}			


/* ship
	if(valid == 0){
	    for(i=0;i<MAX_ELEV;i++){
	    	if( !KeyCancleCheck(i)) valid=1;  
	    }
	}
ship */



//    if(!KeyCancleCheck(LocalNumber)) valid=1;  

    if((valid == 0) && ((MyAddress-1) <= maxtopflr)){   
        if(UpKeyBit){
			if((UpButtonTime<BUT_CANLE_T) && (UpButtonTime > 0) ){				
				if(ButtonType==0)	i=0; //abc
				else				i=1; //abc

                if((MyAddress-1) < (maxtopflr + i)){
					if(bToggleOn){
	                    if(TogUpKeyBitSet){
	                        if(!UP_KEY_LAMP){                        
	                            UP_KEY_LAMP=1;
	                            Up_Key_Valid=1;
	                            Up_Key_Clear=0;
	                            Tx1ConfirmCnt=3;
	                        }
	                    }                    
	                    else if(TogUpKeyBitReset){
	                        UP_KEY_LAMP=0;
	                        Up_Key_Valid=0;
	                        Up_Key_Clear=1;
	                        Tx1ConfirmCnt=3;    
	                    }
	                    else if(!UP_KEY_LAMP){
	                        UP_KEY_LAMP=1;
	                        Up_Key_Valid=1;
	                        Up_Key_Clear=0;
	                        Tx1ConfirmCnt=3;
	                        TogUpKeyBitSet=1;
	                    }
	                    else{                
	                        UP_KEY_LAMP=0;
	                        Up_Key_Valid=0;
	                        Up_Key_Clear=1;
	                        Tx1ConfirmCnt=3;    
	                        TogUpKeyBitReset=1;
	                    }
					}
					else{
	                    if(!UP_KEY_LAMP){
	                        UP_KEY_LAMP=1;
	                        Up_Key_Valid=1;
	                        Up_Key_Clear=0;
	                        Tx1ConfirmCnt=3;
	                    }
					}
                }
            }
        }
        else{
            UpButtonTime=0;
            TogUpKeyBitSet=0;
            TogUpKeyBitReset=0;
        }

               
        if(DnKeyBit){
            if((DnButtonTime<BUT_CANLE_T) && (DnButtonTime > 0) ){
                if(((MyAddress-1) > maxlowflr) || (ButtonType > 0)){
                    if(ButtonType==0){
						if(MyAddress > 1){
							if(bToggleOn){
		                        if(TogDnKeyBitSet){
		                            if(!DN_KEY_LAMP){
		                                DN_KEY_LAMP=1;
		                                Dn_Key_Valid=1;
		                                Dn_Key_Clear=0;
		                                Tx0ConfirmCnt=3;
		                            }
		                        }                    
		                        else if(TogDnKeyBitReset){
		                            DN_KEY_LAMP=0;
		                            Dn_Key_Valid=0;
		                            Dn_Key_Clear=1;
		                            Tx0ConfirmCnt=3;
		                        }
		                        else if(!DN_KEY_LAMP){
		                            DN_KEY_LAMP=1;
		                            Dn_Key_Valid=1;
		                            Dn_Key_Clear=0;
		                            Tx0ConfirmCnt=3;
		                            TogDnKeyBitSet=1;
		                        }
		                        else{                
		                            DN_KEY_LAMP=0;
		                            Dn_Key_Valid=0;
		                            Dn_Key_Clear=1;
		                            Tx0ConfirmCnt=3;    
		                            TogDnKeyBitReset=1;
		                        }
							}
							else{
		                        if(!DN_KEY_LAMP){
		                            DN_KEY_LAMP=1;
		                            Dn_Key_Valid=1;
		                            Dn_Key_Clear=0;
		                            Tx0ConfirmCnt=3;
		                        }
							}
						}
                    }
                    else{
                        if(!DnKeyOkCheck(LocalNumber)){
                            DN_KEY_LAMP=1;
                            Dn_Key_Valid=1;
                            Dn_Key_Clear=0;
                            Tx0ConfirmCnt=3;
                        }
                        else{
                            DN_KEY_LAMP=0;
                            Dn_Key_Valid=0;
                            Dn_Key_Clear=0;
                            Tx0ConfirmCnt=0;
                        }
                    }
                }
            }
        }
            
        else{
            DnButtonTime=0;
            TogDnKeyBitSet=0;
            TogDnKeyBitReset=0;

			if( !bToggleOn){
	            if(ButtonType){
	                DN_KEY_LAMP=0;
	                Dn_Key_Valid=0;
	                Dn_Key_Clear=0;
	                Tx0ConfirmCnt=0;
	            }
			}                        
        }
    }
    else{
		DownButtonClear();
		UpButtonClear();
    }      
}



////////////////////////////////
void    UpDownBlink(unsigned char id)
{

	unsigned int IdPt;
	unsigned char destfl,destfl1,OnLamp,OnLampDn;

    IdPt=(id * HOST_DATA_RECOD) + RCV_DATA;

	destfl=RcvBuf[IdPt+DEST_FLR];
	destfl1=(destfl & ONLY_FLR);


    BlinkOn=0;
	OnLamp=0;
	OnLampDn=0;

	if(IsHallLanternUpLamp(IdPt)){
	   	if(((destfl1 & ONLY_FLR) == (MyAddress-1)) && (CurFloor  == MyAddress)){
			OnLamp=1;	
		}
	}


//	if(IsHallLanternUpLamp(IdPt) && (OnLamp==1)){
	if(OnLamp==1){
		HallLampUpBit=1;
        bHALL_LAMP_UP=1;   
	}
	else{
		HallLampUpBit=0;
        bHALL_LAMP_UP=0;   
	}


	OnLampDn=0;
	if(IsHallLanternDnLamp(IdPt)){     
//	   	if(((destfl1 & ONLY_FLR) == (MyAddress-1)) && (CurFloor  == MyAddress)){
	   	if(CurFloor  == MyAddress){
			OnLampDn=1;	
		}
	}


//	if(IsHallLanternDnLamp(IdPt)){
	if(OnLampDn==1){
		HallLampDnBit=1;
	    HALL_LAMP_DN=1;   
	}
	else{
		HallLampDnBit=0;
	    HALL_LAMP_DN=0;   
	}


/* shipshipshipshipshipshipshipship ship
    BlinkOn=0;
    HallLampUpBit=0;
    HallLampDnBit=0;

    if((destfl1  == (MyAddress-1)) && (CurFloor  == MyAddress) ){
//        if( IsCarAnyWard(xIdPt) && IsCarAuto(xIdPt)){			
//             if(IsCarMove(xIdPt)){
        if((UpMove || DnMove) && Auto){			
             if(CarMove){
  				if(IsYouUp(destfl)){
                     HallLampUpBit=1;
                     BlinkOn=1;  
                 }                
  				 else if(IsYouDn(destfl)){
                     HallLampDnBit=1;
                     BlinkOn=1;  
                 }                
             }
//             else{
             else if(UpMove){
//				if(IsCarUpWard(xIdPt)){	
                     HallLampUpBit=1;
                     BlinkOn=1;  
                 }                
                 else{
//				else if(IsCarDnWard(xIdPt)){	
                     HallLampDnBit=1;
                     BlinkOn=1;  
                 }                
//             }
		}
    }
    else{        
		if((UpHallElev == id) && (DnHallElev == id)){
	    	if( (CurFloor  < MyAddress) && !DnMove)	HallLampUpBit=1;
	    	if( (CurFloor  > MyAddress) && !UpMove)	HallLampDnBit=1;
        }
		else if(UpHallElev == id){
            HallLampUpBit=1;
        }
        else if(DnHallElev == id){
            HallLampDnBit=1;
        }
    }

            
    if(BlinkOn){                        
        BlinkTime=BlinkTime%10;
        if(HallLampUpBit){
            if((BlinkTime >= 5))    bHALL_LAMP_UP=0;      
            else                  	bHALL_LAMP_UP=1;   
            HALL_LAMP_DN=0;
        }
        else if(HallLampDnBit){
            if((BlinkTime >= 5))    HALL_LAMP_DN=0;      
            else                  	HALL_LAMP_DN=1;   
            bHALL_LAMP_UP=0;
        }
    }
    else{
        if(HallLampUpBit){
            bHALL_LAMP_UP=1;   
            HALL_LAMP_DN=0;
        }
        else if(HallLampDnBit){
            HALL_LAMP_DN=1;   
            bHALL_LAMP_UP=0;
        }
        else{
            bHALL_LAMP_UP=0;
            HALL_LAMP_DN=0;
        }
        BlinkTime=0;
    }

#if defined(__TYPE_ES15)
	HALL_LAMP_UP = bHALL_LAMP_UP;
#endif


 shipshipshipshipshipshipshipship ship

*/
}






//////////////////////////////////////////////
unsigned char TmpVip(void)
{
    b_vip=0;

#ifdef  VIP_TEMP
    if(!Vip && (Up_Key_Valid || Dn_Key_Valid)){        
        b_vip=1;
        return(1);
    }
#endif
    return(0);            
}



void DoorOpenCheck(unsigned char i)
{

	GetElevPointer((unsigned int)i);

    if(IsYouFlrEqualMe(xTmpCurFloor,xtmpadr) && IsCarAuto(xIdPt)){
	    if( (!bIamXSubDoor && IsCarMainOpen(xIdPt)) || (bIamXSubDoor && IsCarSubOpen(xIdPt)) ){
			if( IsCarUpWard(xIdPt) || (ButtonType)){
	            if(!TmpVip()){			
	                UP_KEY_LAMP=0;
	                Up_Key_Valid=0;
	                Tx1ConfirmCnt=0;

	            }
			}
			if(IsCarDnWard(xIdPt)){
	            if(!TmpVip()){        
	                DN_KEY_LAMP=0;
	                Dn_Key_Valid=0;
	                Tx0ConfirmCnt=0;
	            }
			}
	    }
    }
	
//	else	LockMove=0;        


/*
    unsigned char iCurFlr,j;

    b_vip=0;

    j=(HOST_DATA_RECOD * i);

    iCurFlr=RcvBuf[RCV_DATA+j];

   if((iCurFlr == MyAddress) && (RcvBuf[RCV_DATA+j+1] & S1_AUTO)){        
      if(( (bIamXSubDoor == 0) && (RcvBuf[RCV_DATA+j+1] & S1_OPEN)) ||  ( (bIamXSubDoor == 1) && (RcvBuf[RCV_DATA+j+3] & S3_OPEN_SUB) ) ){
         if((RcvBuf[RCV_DATA+j+1] & S1_UP) || (ButtonType)){			 
            if(!TmpVip()){ 
                UP_KEY_LAMP=0;
                Up_Key_Valid=0;
                Tx1ConfirmCnt=0;
            }
         }
         else if(RcvBuf[RCV_DATA+j+2] & S2_DN){       
            if(!TmpVip()){        
                DN_KEY_LAMP=0;
                Dn_Key_Valid=0;
                Tx0ConfirmCnt=0;
            }
         }
      }         
   }
*/

}




void    ButtonLampClrChk(void)
{

#ifdef  VIP_TEMP
       DoorOpenCheck(LocalNumber);
#else            
    unsigned char i;

    for(i=0;i<MAX_ELEV;i++){ 
       DoorOpenCheck(i);
    }
#endif

}                  
