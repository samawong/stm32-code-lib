#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"

#define SpeedStep 100
#define KEY1_IN HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define KEY2_IN HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)
 
void key_scan(void);
void display(void);
 
#endif

