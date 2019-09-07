#ifndef _IIC_H
#define _IIC_H

#include "stdio.h"    
#include "stm32f1xx_hal.h"


/* ������� SDA SCL �ĺ� ��׼���
#define I2C_SDA_UP        GPIO_SetBits  (GPIOC,GPIO_PIN_8)    //SDA�ߵ�ƽ
#define I2C_SDA_LOW        GPIO_ResetBits(GPIOC,GPIO_PIN_8)    //SDA�͵�ƽ
#define I2C_SCL_UP        GPIO_SetBits  (GPIOC,GPIO_PIN_9)    //SCL�ߵ�ƽ
#define I2C_SCL_LOW        GPIO_ResetBits(GPIOC,GPIO_PIN_9)    //SCL�͵�ƽ
*/


/* ������� SDA SCL �ĺ� HAL���    */

#define I2C_SDA_UP        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET)                //SDA�ߵ�ƽ
#define I2C_SDA_LOW        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET)            //SDA�͵�ƽ
#define I2C_SCL_UP        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)              //SCL�ߵ�ƽ
#define I2C_SCL_LOW        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)            //SCL�͵�ƽ



/* ��ȡ SDA SCL ����״̬����׼���Ҳ������ͬ�߼�    */

#define I2C_SDA        HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_8)        //��ȡSDA����״̬
#define I2C_SCL        HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9)        //��ȡSCL����״̬


void         i2c_start(void);                    //*    ��ʼ�ź�    
void         i2c_ack(void);                        //*    Ӧ���ź�    
void         I2C_No_ack(void);                    //*    ��Ӧ���ź�    
void         i2c_stop(void);                        //*    ֹͣ�ź�    
char         i2c_wit_ack(void);                //*    �ȴ�Ӧ��
void         i2c_send(uint8_t dat);        //* ��������
uint8_t i2c_read(void);                        //* ��������

void SDA_OUT(void);                //*    SDA ����Ϊ���    
void SDA_IN(void);                //*    SDA ����Ϊ����    

void delay_us(uint32_t i);        //*��ʱ    

#endif