#ifndef __DS1302_H
#define __DS1302_H

#include "stm32f1xx_hal.h"

/* Initialization */

static void delayUS_DWT(uint32_t us);
/* GPIO and DWT */
void DS1302_Init(void);

void ds1302_write_data(uint8_t reg,uint8_t data);

uint8_t ds1302_read_data(uint8_t reg);

uint8_t read_one_byte(void);

void Write_one_byte(uint8_t data);

static void readSDA(void);

static void writeSDA(void);



void time_read(void);
#endif
