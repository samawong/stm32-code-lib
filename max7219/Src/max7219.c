#include "max7219.h"

void Delay_xms(uint32_t x)
{
	HAL_Delay(x);
}

void Max7219_pinCLK(uint8_t i)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,i);
}
void Max7219_pinCS(uint8_t i)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,i);
}
void Max7219_pinDIN(uint8_t i)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,i);
}

//--------------------------------------------
//?MAX7219(U3)????
void Write_Max7219_byte(uint8_t DATA)         
{
    	uint8_t i;    
		Max7219_pinCS(0);				//CS=0??,CS=1??	
	    for(i=8;i>=1;i--)
          {		  
            Max7219_pinCLK(0);
            Max7219_pinDIN(DATA&0x80); //&10000000, ??????????:?0??1
            DATA=DATA<<1;
            Max7219_pinCLK(1);		//?????????
           }                                 
}
//-------------------------------------------
/*?M???MAX7219????*/
void Write_Max7219_1(uint8_t add1,uint8_t dat1)
{ 
     Max7219_pinCS(0);
	 Write_Max7219_byte(add1);           //????,??????
     Write_Max7219_byte(dat1);               //????,???????? 
	 Max7219_pinCS(1);                        
}
/***

void Write_Max7219_2(uint8_t add2,uint8_t dat2)
{
	Max7219_pinCS(0);
	Write_Max7219_byte(add2);
	Write_Max7219_byte(dat2);
	Max7219_pinCLK(1);
	Write_Max7219_byte(0x00); 
	Write_Max7219_byte(0x00);
	Max7219_pinCS(1);
}

void Write_Max7219_3(uint8_t add3,uint8_t dat3)
{
	Max7219_pinCS(0);
	Write_Max7219_byte(add3);
	Write_Max7219_byte(dat3);
	Max7219_pinCLK(1);
	Write_Max7219_byte(0x00); //?1???
	Write_Max7219_byte(0x00);
	Write_Max7219_byte(0x00); //?2???
	Write_Max7219_byte(0x00);
	Max7219_pinCS(1);
}
***/

/*?????*/
void Init_MAX7219(void)
{
 Write_Max7219_1(0x09, 0xff);       //选用全译码模式:BCD,输啥显啥
 Write_Max7219_1(0x0a, 0x03);       //设置初始亮度 
 Write_Max7219_1(0x0b, 0x07);       //8只LED全用
 Write_Max7219_1(0x0c, 0x01);       //开启正常工作模式（0xX1）
 Write_Max7219_1(0x0f, 0x00);       //选择工作模式（0xX0）

	/**
 Write_Max7219_2(0x09, 0xff);       //????:BCD?
 Write_Max7219_2(0x0a, 0x03);       //?? 
 Write_Max7219_2(0x0b, 0x07);       //????;8??????
 Write_Max7219_2(0x0c, 0x01);       //????:0,????:1
 Write_Max7219_2(0x0f, 0x00);       //????:1;????,????:0

 Write_Max7219_3(0x09, 0xff);       //????:BCD?
 Write_Max7219_3(0x0a, 0x03);       //?? 
 Write_Max7219_3(0x0b, 0x07);       //????;8??????
 Write_Max7219_3(0x0c, 0x01);       //????:0,????:1
 Write_Max7219_3(0x0f, 0x00);       //????:1;????,????:0
	**/
}
