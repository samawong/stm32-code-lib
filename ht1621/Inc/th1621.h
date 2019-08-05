#ifndef __TH1621_H
#define __TH1621_H

#include "stm32f0xx_hal.h"

#define CS(n) if(n==0)  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10,GPIO_PIN_RESET);  else if(n==1)HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10,GPIO_PIN_SET)
#define WR(n) if(n==0)  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11,GPIO_PIN_RESET);  else if(n==1)HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11,GPIO_PIN_SET)
#define DATA(n) if(n==0)HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_RESET);  else if(n==1)HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_SET)

#define BIAS 0x52  // 
#define SYSEN 0x02  //打开系统震荡器
#define LCDOFF 0x04 //关LCD偏压
#define LCDON 0x06  //开LCD偏压
#define RC256 0x30   //0b1000 0011 0000  System clock source, on-chip RC oscillator
#define SYSDIS 0x00  //0b1000 0000 0000  Turn off both system oscillator and LCD bias generator
#define WDTDIS 0xa0  //0b1000 0000 1010  Disable WDT time-out flag output

#define ON  1
#define OFF 0

void port_init(void);
extern void display_all(void);
extern void display_off(void);
void SendBit_1621(uint8_t data,uint8_t len);
extern void SendCmd(uint8_t command);
void Write_1621(uint8_t addr,uint8_t data);
void SendDataBit_1621(uint8_t data,uint8_t len);
void Ht1621WrOneNum(uint8_t Addr,uint8_t num);
void Ht1621WrAllData(uint8_t num);

#endif

