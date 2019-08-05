#include "key.h"
#include "ds1302.h"
#include "max7219.h"

extern uint8_t DShour,DSminute;

uint8_t key_num,nHour,nMinute;

void key_scan(void){

	 if(KEY1_IN != 1 || KEY2_IN != 1){
		if(KEY1_IN == 0){
			HAL_Delay(10); 
			if(KEY1_IN == 0){				
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
				nHour = DShour%16+DShour/16*10;
				nHour ++;		
				if(nHour >23 ) nHour = 0;
				DShour = nHour%10+nHour/10*16;
				
				 ds1302_write_data(0x8e,0x00);
					ds1302_write_data(0x84,DShour);
			  ds1302_write_data(0x8e,0x80);
	      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
			}
		}
		
		if(KEY2_IN == 0){
			HAL_Delay(10);
			if(KEY2_IN == 0){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
				nMinute = DSminute%16+DSminute/16*10;
				nMinute ++;
				if(nMinute >59 ) nMinute = 0;

				DSminute = nMinute%10+nMinute/10*16;

				  ds1302_write_data(0x8e,0x00);
		ds1302_write_data(0x82,DSminute);
		ds1302_write_data(0x8e,0x80);
	      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
			}
		}
	}
  
}


