#ifndef __IAQ_CORE_H
#define __IAQ_CORE_H

#include "stm32f1xx_hal.h"

//#define SCL(n) if(n==0) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET) \
										else(n==1) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
											
//SCL_1() GPIOA->BSRR = GPIO_PIN_6
//SCL_0() GPIOA->BSRR = (uint32_t)GPIO_PIN_6 <<16U
//#define SDA(n) if(n==0) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET) \
										else(n==1) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);


#define I2C_SDA_READ()  (GPIOA->IDR & GPIO_PIN_7);
#define I2C_SCL_READ()  (GPIOA->IDR & GPIO_PIN_6);
										
										
void i2c_Start(void);
//停止信号
void i2c_Stop(void);
//发送一个字节
void i2c_SendByte(uint8_t _ucByte);
//读取一个字节
uint8_t i2c_ReadByte(uint8_t ack);
//等待应答信号
uint8_t i2c_WaitAck(void);
//应答信号
void i2c_ACK(void);
void i2c_NACK(void);
//检查设备
uint8_t i2c_CheckDevice(uint8_t _Address);
//发送数据
void  Device_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size);
void Device_ReadData(uint8_t DeviceAddr,uint8_t *Data,int size);
uint8_t  iaq_ReadData(uint16_t ReadAdder,uint8_t RorW);

#endif



