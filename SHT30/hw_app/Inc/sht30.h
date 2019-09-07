#ifndef __SHT30_H
#define __SHT30_H

#include "stm32f1xx_hal.h"

/*SHT30 设备操作相关宏定义，详见手册*/
#define SHT30_ADDRESS  0X44

static const uint16_t SHT30_CMD_READ_STATUS_REG = 0xF32D;
static const uint16_t SHT30_CMD_DURATION_USEC = 1000;

#define SHT30_READ_Add {0x2c,0x06}
#define SHT30_Measurement_T_HM
#define SHT30_CalcRH
#define SHT30_Measurement_RH_HM

#define STATUS_OK 0
#define STATUS_FAIL (-1)
#define be16_to_cpu(s) (((uint16_t)(s) << 8) | (0xff & ((uint16_t)(s)) >> 8))
#define SENSIRION_COMMAND_SIZE 2


typedef struct
{

	float tempreture;
	float humidity;

} SHT30_INFO;

extern SHT30_INFO sht30_info;


void SHT30_GetValue(void);

int16_t sensirion_i2c_delayed_read_cmd(uint8_t address, uint16_t cmd,
                                       uint32_t delay_us, uint16_t *data_words,
                                       uint16_t num_words);
int16_t sensirion_i2c_read_words(uint8_t address, uint16_t *data_words,
                                 uint16_t num_words);

uint8_t sht_common_generate_crc(uint8_t *data, uint16_t count);


#endif

