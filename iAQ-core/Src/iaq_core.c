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

//开始信号
void i2c_Start(void){

	//当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
	SDA_OUT();
	SDA(1);
	SCL(1);
	i2c_Delay();
	SDA(0);
	i2c_Delay();
	SCL(0);
	i2c_Delay();
}


//停止信号
void i2c_Stop(void){
	//当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号
	SDA_OUT();
	SCL(0);
	SDA(0);
	i2c_Delay();
	SCL(1);
	SDA(1);

}

//发送一个字节
void i2c_SendByte(uint8_t _i2cByte){
	uint8_t i;
	SDA_OUT();
	SCL(0);
	
	//先发送字节的高位bit7
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

//读取一个字节
uint8_t i2c_ReadByte(uint8_t ack){
	uint8_t i;
	uint8_t value;
	SDA_IN();
	
	/*读到第1个bit为数据的bit7*/
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


//等待应答信号
uint8_t i2c_WaitAck(void){
	uint8_t re = 0;
	SDA_IN();
	
	SDA(1);/* CPU释放SDA总线 */
	i2c_Delay();
	SCL(1);/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
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

//应答信号
void i2c_ACK(void){
	SCL(0);       /* CPU驱动SDA = 0 */
	SDA_OUT();
	SDA(0);       /* CPU产生1个时钟 */
	i2c_Delay();
	SCL(1);
	i2c_Delay();
	SCL(0);       /* CPU释放SDA总线 */
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
		i2c_Start(); //发送启动信号
		
		/*发送设备地址+读写控制bit(0=w,1=r)bit7先传*/
		i2c_SendByte(_Address | 0);
		i2cAck = i2c_WaitAck(); //检测设备的ACK应答
		i2c_Stop();     //发送停止信号
		return i2cAck;
	}
	return 1;  //i2c总线异常
}

void Device_WriteData(uint8_t DeviceAddr,uint8_t *Data,int size){
	int count = size;
	uint8_t *pData = Data;
	//起始信号
	i2c_Start();
	//发送器件地址
	i2c_SendByte(DeviceAddr);
	//等待应答
	i2c_WaitAck();
	while(count --){
		//发送数据
		i2c_SendByte(*pData++);
		//等待应答
		i2c_WaitAck();
	}
	//结束信号
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



	
