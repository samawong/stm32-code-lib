#include "iaq_core.h"

// SDA Write(output) Mode
static void SDA_OUT(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_7;
  GPIO_InitStructure.Mode =  GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

// SDA Read(input) Mode
static void SDA_IN(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_7;
  GPIO_InitStructure.Mode =  GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void SDA(uint8_t i)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,i);
}
void SCL(uint8_t i)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,i);
}
										
static void i2c_Delay(void){

	uint8_t i;
	for(i=0;i<40;i++);
}	

//��ʼ�ź�
void i2c_Start(void){

	//��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź�
	SDA_OUT();
	SDA(1);
	SCL(1);
	i2c_Delay();
	SDA(0);
	i2c_Delay();
	SCL(0);
	i2c_Delay();
}


//ֹͣ�ź�
void i2c_Stop(void){
	//��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź�
	SDA_OUT();
	SCL(0);
	SDA(0);
	i2c_Delay();
	SCL(1);
	SDA(1);

}

//����һ���ֽ�
void i2c_SendByte(uint8_t _i2cByte){
	uint8_t i;
	SDA_OUT();
	SCL(0);
	
	//�ȷ����ֽڵĸ�λbit7
	for(i=0;i<8;i++){
		SDA((_i2cByte&0X80)>>7);
		_i2cByte <<=1;
		i2c_Delay();
		SCL(1);
		i2c_Delay();
		SCL(0);
		i2c_Delay();
	}
}

//��ȡһ���ֽ�
uint8_t i2c_ReadByte(uint8_t ack){
	uint8_t i;
	uint8_t value;
	SDA_IN();
	
	/*������1��bitΪ���ݵ�bit7*/
	value = 0;
	for(i=0;i<8;i++){
		SCL(0);
		i2c_Delay();
		SCL(1);
		value <<= 1;
		
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==GPIO_PIN_SET){
			value ++;
		}

		i2c_Delay();
	}
	if(!ack) {i2c_NACK();}
	  else {i2c_ACK();}
    return value;
}


//�ȴ�Ӧ���ź�
uint8_t i2c_WaitAck(void){
	uint8_t re = 0;
	SDA_IN();
	
	SDA(1);/* CPU�ͷ�SDA���� */
	i2c_Delay();
	SCL(1);/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
	
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==GPIO_PIN_SET){
		re ++;
		if(re>250){
			i2c_Stop();
			return 1;
		}
	}
	SCL(0);
	return 0;
}

//Ӧ���ź�
void i2c_ACK(void){
	SCL(0);       /* CPU����SDA = 0 */
	SDA_OUT();
	SDA(0);       /* CPU����1��ʱ�� */
	i2c_Delay();
	SCL(1);
	i2c_Delay();
	SCL(0);       /* CPU�ͷ�SDA���� */
}

void i2c_NACK(void){
	SCL(0);
	SDA_OUT();
	SDA(1);
	i2c_Delay();
	SCL(1);
	i2c_Delay();
	SCL(0);
}

uint8_t i2c_CheckDevice(uint8_t _Address){
	uint8_t i2cAck;
	
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7) && HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){
		i2c_Start(); //���������ź�
		
		/*�����豸��ַ+��д����bit(0=w,1=r)bit7�ȴ�*/
		i2c_SendByte(_Address | 0);
		i2cAck = i2c_WaitAck(); //����豸��ACKӦ��
		i2c_Stop();     //����ֹͣ�ź�
		return i2cAck;
	}
	return 1;  //i2c�����쳣
}

void Device_WriteData(uint8_t DeviceAddr,uint8_t *Data,int size){
	int count = size;
	uint8_t *pData = Data;
	//��ʼ�ź�
	i2c_Start();
	//����������ַ
	i2c_SendByte(DeviceAddr);
	//�ȴ�Ӧ��
	i2c_WaitAck();
	while(count --){
		//��������
		i2c_SendByte(*pData++);
		//�ȴ�Ӧ��
		i2c_WaitAck();
	}
	//�����ź�
	i2c_Stop();
}

uint8_t  iaq_ReadData(uint16_t ReadAdder,uint8_t RorW){
	uint8_t temp = 0;
	i2c_Start();
	i2c_SendByte(ReadAdder);
	i2c_WaitAck();
	i2c_SendByte(RorW);
	i2c_WaitAck();
	temp = i2c_ReadByte(0);
	i2c_Stop();
	return temp;
}



	
