#include "ds1302.h"


// Write Register Address
#define DS1302_SEC				0x80
#define DS1302_MIN				0x82
#define DS1302_HOUR				0x84
#define DS1302_DATE				0x86
#define DS1302_MONTH			0x88
#define DS1302_DAY				0x8a
#define DS1302_YEAR				0x8c
#define DS1302_CONTROL		0x8e
#define DS1302_CHARGER		0x90 					 
#define DS1302_CLKBURST		0xbe
#define DS1302_RAMBURST 	0xfe

#define RAMSIZE 					0x31	// Ram Size in bytes
#define DS1302_RAMSTART		0xc0 	// First Address


#define HEX2BCD(v)	((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)	((v) % 16 + (v) / 16 * 10)

uint8_t DSsecond ,DShour,DSminute;

uint8_t time[7] = {0x19,0x01,0x09,0x07,0x15,0x30,0x30};
uint8_t time_reg[7] = {0x8c,0x8a,0x88,0x86,0x84,0x82,0x80};

// GPIO Pins
#define DS1302_GPIO	GPIOB
#define DS1302_SCLK	GPIO_PIN_1
#define DS1302_SDA	GPIO_PIN_10
#define DS1302_RST	GPIO_PIN_11

/* Clock signal need to be at least 1 micro second wide, those delays are generated with DWT		*/
/* More info:  https://www.carminenoviello.com/2015/09/04/precisely-measure-microseconds-stm32/ */
#pragma push
#pragma O3
static void delayUS_DWT(uint32_t us) {
	volatile uint32_t cycles = (SystemCoreClock/1000000L)*us;
	volatile uint32_t start = DWT->CYCCNT;
	do  {
	} while(DWT->CYCCNT - start < cycles);
}
#pragma pop



// SDA Write(output) Mode
static void writeSDA(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = DS1302_SDA;
  GPIO_InitStructure.Mode =  GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DS1302_GPIO, &GPIO_InitStructure);
	
}

// SDA Read(input) Mode
static void readSDA(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = DS1302_SDA;
  GPIO_InitStructure.Mode =  GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DS1302_GPIO, &GPIO_InitStructure);	
}


void Write_one_byte(uint8_t data){
	uint8_t i;
	writeSDA();
	for(i=0;i<8;i++){
		HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DS1302_GPIO, DS1302_SDA, (data & 0x01) ?  GPIO_PIN_SET :  GPIO_PIN_RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_SET);
		data >>= 1;
		HAL_Delay(1);
	}
}

uint8_t read_one_byte(void){
	uint8_t i,data;
	readSDA();
	for(i=0;i<8;i++){
		data >>= 1;
		HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(DS1302_GPIO,DS1302_SDA) == GPIO_PIN_SET){
			data |= 0x80;
		}else{
			data &= 0x7F;
		}
		HAL_Delay(1);
		HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_RESET);
	}
	return data;
}

void ds1302_write_data(uint8_t reg,uint8_t data){
		HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DS1302_GPIO, DS1302_RST,  GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(DS1302_GPIO, DS1302_RST,  GPIO_PIN_SET);
	Write_one_byte(reg);
	HAL_Delay(1);
	HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_RESET);
	Write_one_byte(data);
	HAL_Delay(1);
	HAL_GPIO_WritePin(DS1302_GPIO, DS1302_RST,  GPIO_PIN_RESET);
}

uint8_t ds1302_read_data(uint8_t reg){
	uint8_t temp;
	HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DS1302_GPIO, DS1302_RST,  GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(DS1302_GPIO, DS1302_RST,  GPIO_PIN_SET);
	HAL_Delay(1);
	Write_one_byte(reg);
	HAL_Delay(1);
	HAL_GPIO_WritePin(DS1302_GPIO,DS1302_SCLK,GPIO_PIN_RESET);
	temp = read_one_byte();
	HAL_Delay(1);
	HAL_GPIO_WritePin(DS1302_GPIO, DS1302_RST,  GPIO_PIN_RESET);
	return temp;
}


void time_read(void){

	DShour = ds1302_read_data(0x85);
	DSminute = ds1302_read_data(0x83);
	DSsecond = ds1302_read_data(0x81);
}

/* Initialization */
void DS1302_Init(void)
{
  ds1302_write_data(0x8e,0x00);
	//for(int i =0;i<7;i++){
	//	ds1302_write_data(time_reg[i],time[i]);
	//}
	ds1302_write_data(0x8e,0x80);
}






