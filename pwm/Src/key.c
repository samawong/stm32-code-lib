#include "key.h"
#include "max7219.h"
#include "tim.h"
#include "pid.h"


extern int SpeedSet;
int i,j;

void key_scan(void){

	 if(KEY1_IN != 1 || KEY2_IN != 1){
		if(KEY1_IN == 0){
			HAL_Delay(10); 
			if(KEY1_IN == 0){				
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
					
				SpeedSet = SpeedSet + 10; //速度增加
				if(SpeedSet>3000){
					SpeedSet = 3000;
				}
				display();
				HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,SpeedSet);
				
				HAL_Delay(10);
				
	      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
			}
		}
		
		if(KEY2_IN == 0){
			HAL_Delay(10);
			if(KEY2_IN == 0){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
				SpeedSet = SpeedSet - 10; //速度减
				if(SpeedSet<0){
					SpeedSet = 0;
				}
				display();
					HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
					HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
					__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,SpeedSet);
				HAL_Delay(10);
	      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
			}
		}
	}
  
}

void display(void){
    i= SpeedSet;
		j = i/1.6;
		Write_Max7219_1(8,j/1000);
		Write_Max7219_1(7,(j%1000)/100);
		
		Write_Max7219_1(6,(j%100)/10);
		
		Write_Max7219_1(5,(j%10));
	
}

