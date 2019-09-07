#include "sht30.h"
#include "iic.h"

uint8_t humi,temp;


void SHT_Init(void){
	HAL_Delay(250);
	i2c_start();
	i2c_send(0x88);
	i2c_wit_ack();
	i2c_send(0x21);
	i2c_wit_ack();
	i2c_send(0x30);
	i2c_wit_ack();
	i2c_stop();
	HAL_Delay(150);
}


void sht30_read_temp_humi(uint8_t *p){
	i2c_start();
	i2c_send(0x88);
	i2c_wit_ack();
	i2c_send(0xe0);
	i2c_wit_ack();
	i2c_send(0x00);
	i2c_wit_ack();
	
	i2c_start();
	i2c_send(0x89);
	i2c_wit_ack();
	
	p[0] = i2c_read();
	i2c_wit_ack();
	p[1] = i2c_read();
	i2c_wit_ack();
	p[2] = i2c_read();
	i2c_wit_ack();
	p[3] = i2c_read();
	i2c_wit_ack();
	p[4] = i2c_read();
	i2c_wit_ack();
	p[5] = i2c_read();
	i2c_wit_ack();
	i2c_stop();
	
}


int sht30_data_process(void){
	uint8_t temporary[6];
	uint16_t data;
	
	uint8_t sht30_data_buffer[6];
	sht30_read_temp_humi(sht30_data_buffer);
	
	temporary[0] = sht30_data_buffer[0];
	temporary[1] = sht30_data_buffer[1];
	temporary[2] = sht30_data_buffer[2];
	
		data = ((uint16_t)temporary[0]<<8)|temporary[1];
		temp = (int)((175.0 * ((float)data) / 65535.0 - 45.0) *10.0);
	
	temporary[3] = sht30_data_buffer[3];
	temporary[4] = sht30_data_buffer[4];
	temporary[5] = sht30_data_buffer[5];
	
		data = ((uint16_t)temporary[3]<<8)|temporary[4];
		humi =  (int)((100.0 * (float)data / 65535.0) *10.0); 
	
}
/*
int sht30_data_process(void){
	uint8_t temporary[3];
	uint16_t data;
	uint8_t crc_result;
	
	uint8_t sht30_data_buffer[6];
	sht30_read_temp_humi(sht30_data_buffer);
	
	temporary[0] = sht30_data_buffer[0];
	temporary[1] = sht30_data_buffer[1];
	temporary[2] = sht30_data_buffer[2];
	
	crc_result = sht30_crc8_check(temporary,2,temporary[2]);
	if(crc_result ==0){
		data = ((uint16_t)temporary[0]<<8)|temporary[1];
		temp = (int)((175.0 * ((float)data) / 65535.0 - 45.0) *10.0);
		return 1;
	}else{
		return 0;
	}
	temporary[0] = sht30_data_buffer[3];
	temporary[1] = sht30_data_buffer[4];
	temporary[2] = sht30_data_buffer[5];
	
	crc_result = sht30_crc8_check(temporary,2,temporary[2]);
  if(crc_result == 0){
		data = ((uint16_t)temporary[0]<<8)|temporary[1];
		humi =  (int)((100.0 * (float)data / 65535.0) *10.0); 
		return 2;
	}	else{
		return 0;
	}
	
}


int  crc8_compute(uint8_t *check_data, uint8_t num_of_data)
{
 	uint8_t bit;        // bit mask
 uint8_t crc = 0xFF; // calculated checksum
 uint8_t byteCtr;    // byte counter

 // calculates 8-Bit checksum with given polynomial
 for(byteCtr = 0; byteCtr < num_of_data; byteCtr++) {
     crc ^= (check_data[byteCtr]);
 	//crc校验，最高位是1就^0x31
     for(bit = 8; bit > 0; --bit) {
         if(crc & 0x80) {
             crc = (crc << 1) ^ 0x31;
         }  else {
             crc = (crc << 1);
         }
     }
 }
 return crc;
}
int sht30_crc8_check(uint8_t *p,uint8_t num_of_data,uint8_t CrcData)
{
  uint8_t crc;
  crc = crc8_compute(p, num_of_data);// calculates 8-Bit checksum
 if(crc != CrcData) 
 {   
     return 1;           
 }
 return 0;
}
*/


