#ifndef __MAX7219_H
#define __MAX7219_H

#include "stm32f1xx_hal.h"


void Delay_xms(uint32_t x);
void Max7219_pinCLK(uint8_t i);
void Max7219_pinCS(uint8_t i);
void Max7219_pinDIN(uint8_t i);


void Write_Max7219_byte(uint8_t DATA);
void Write_Max7219_1(uint8_t add1,uint8_t dat1);
//void Write_Max7219_2(uint8_t add2,uint8_t dat2);
//void Write_Max7219_3(uint8_t add3,uint8_t dat3);

void Init_MAX7219(void);

#endif
