#include "control.h"
#include "ds1302.h"
uint8_t nHour,nMinute;
extern uint8_t DShour,DSminute;


void up_hour(void){
					nHour = DShour%16+DShour/16*10;//转换成10进制
					nHour ++;		 //+1
					if(nHour >23 ) nHour = 0;
						DShour = nHour%10+nHour/10*16;  //转换成16进制
				  
				  ds1302_write_data(0x8e,0x00);
				  ds1302_write_data(0x84,DShour);
				  ds1302_write_data(0x8e,0x80);
}

void up_mintus(void){
					nMinute = DSminute%16+DSminute/16*10;
					nMinute ++;
					if(nMinute >59 ) nMinute = 0;
					DSminute = nMinute%10+nMinute/10*16;
				  
				  ds1302_write_data(0x8e,0x00);
				  ds1302_write_data(0x82,DSminute);
		      ds1302_write_data(0x8e,0x80);
}