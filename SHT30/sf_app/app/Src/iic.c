/*****************************************************************************
*                                                                                                                                                         *
*                        File:    ���ģ��IIC, HAL��汾����׼��Ҳ                                                     *
*                                    ���ã�ֻ��Ҫ��һЩ���Ӧ�޸ļ���                                                     *
*                                                                                                                                                         *
*****************************************************************************/

#include "iic.h"


/*******************************************************************************
* �� �� ��         : i2c_stare
* ��������         : iic��ʼ�ź�,SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾ�����ź� 
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void i2c_start(void)
{
    SDA_OUT();  
    I2C_SDA_UP;
    I2C_SCL_UP;
    delay_us(4);
     I2C_SDA_LOW;        //������ʼ�ź�
    delay_us(4);
    I2C_SCL_LOW;      //ǯסI2C���ߣ�׼�����ͻ��������
}


/*******************************************************************************
* �� �� ��         : i2c_stop
* ��������         : iicֹͣ�ź�,SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾֹͣ�ź�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void i2c_stop(void)
{
    SDA_OUT();            //sda�����
    I2C_SDA_LOW;         //���ͽ��������������ź�
    I2C_SCL_UP;
    delay_us(4);         //������������ʱ�����4��
    I2C_SDA_UP;         //����I2C���߽����ź�
    delay_us(4);
    I2C_SCL_LOW; 
}


/*******************************************************************************
* �� �� ��         : i2c_send
* ��������         : iic��������
* ��    ��         : uint8_t dat,Ҫ���͵�����
* ��    ��         : ��
*******************************************************************************/
void i2c_send(uint8_t dat)
{

     unsigned char temp;
     SDA_OUT();
   for(temp=0x80;temp!=0;temp>>=1)
   {
       if((temp & dat)== 0)
       {
          I2C_SDA_LOW;
       }
       else
       {
          I2C_SDA_UP;
       }
       delay_us(1);
       I2C_SCL_UP;
       delay_us(4);
       I2C_SCL_LOW;
   }
}


/*******************************************************************************
* �� �� ��         : i2c_read
* ��������         : iic��������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
uint8_t i2c_read(void)
{
   unsigned char temp;
   unsigned char dat;
   I2C_SDA_UP;                     //�ͷ�����׼������
     SDA_IN();
   for(temp=0x80;temp!=0;temp>>=1)
   {
      delay_us(1);
      I2C_SCL_UP;
      if(I2C_SDA==1)
      {
         dat|=temp;
      }
      else
      {
         dat&=~temp;
      }
      I2C_SCL_LOW;
   }
   return dat;
}


/*******************************************************************************
* �� �� ��         : i2c_wit_ack
* ��������         : iic�ȴ�Ӧ��
* ��    ��         : ��
* ��    ��         : 0/1������1��ʾ��Ӧ���źţ�����0��ʾӦ��
*******************************************************************************/
char i2c_wit_ack(void)
{
    
    uint8_t con=0;
    
  I2C_SDA_UP;       //�ͷ������ߣ�׼������Ӧ��
  delay_us(1);
    I2C_SCL_UP;                //CPU����SCL = 1, ��ʱ�����᷵��ACKӦ��
    SDA_IN(); 
    delay_us(1);
    
  while( I2C_SDA )    //CPU��ȡSDA����״̬
  {
        con++;
        if(con>255)
        {
            i2c_stop();
      return 1;     //��Ӧ���ź�
        }
  }

  I2C_SCL_LOW; 
  delay_us(1);
  return 0;             //��Ӧ��
}

/*******************************************************************************
* �� �� ��         : i2c_ack
* ��������         : iicӦ���ź�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void i2c_ack(void)
{
    SDA_OUT();
    I2C_SDA_LOW;
    delay_us(1);
    I2C_SCL_UP;            //CPU����1��ʱ��
    delay_us(4);         //ʱ�ӵ͵�ƽ���ڴ���4��
    I2C_SCL_LOW;         //��ʱ���ߣ�ǯסI2C�����Ա��������
    delay_us(4);
    I2C_SDA_UP;            //CPU�ͷ�SDA����
}


/*******************************************************************************
* �� �� ��         : I2C_No_ack
* ��������         : iic��Ӧ���ź�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void I2C_No_ack(void)
{
     SDA_OUT();
   I2C_SDA_UP;
     delay_us(1);
   I2C_SCL_UP;
   delay_us(4);
   I2C_SCL_LOW; 
   delay_us(4);
}


/*******************************************************************************
* �� �� ��         : SDA_OUT
* ��������         : SDA ����Ϊ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void SDA_OUT(void)
{ 
    
/*    ��׼��ʹ�ã��޸Ķ˿����ſ���
  GPIO_InitTypeDef GPIO_InitTypeStruct;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  
  GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;  
  GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_7;  
  GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB,&GPIO_InitTypeStruct); 
*/    
    
    /*    HAL��ʹ�ã�HAL��ע��Ҫ�ѳ�ʼ�������ľ�̬���ȥ��    */
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_8;                    //ʹ��STM3cubemx�Ƕ���õ�SDA_PinΪGPIO_PIN_8�ı�ǩ
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


/*******************************************************************************
* �� �� ��         : SDA_IN
* ��������         : SDA ����Ϊ����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void SDA_IN(void)  
{
  
/*    ��׼��ʹ�ã��޸Ķ˿����ſ���
  GPIO_InitTypeDef GPIO_InitTypeStruct;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);       
  GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
  GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_7;  
  GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB,&GPIO_InitTypeStruct);  
*/    
    
    /*    HAL��ʹ��, HAL��ע��Ҫ�ѳ�ʼ�������ľ�̬���ȥ��    */
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_8 ;                    //ʹ��STM3cubemx�Ƕ���õ�SDA_PinΪGPIO_PIN_8�ı�ǩ
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} 


/*******************************************************************************
* �� �� ��         : delay_us
* ��������         : ��ʱ��������ʱus
* ��    ��         : i
* ��    ��         : ��
*******************************************************************************/
void delay_us(uint32_t i)
{
    uint32_t temp;
    SysTick->LOAD=9*i;                     //������װ��ֵ, 72MHZʱ
    SysTick->CTRL=0X01;                 //ʹ�ܣ����������޶����������ⲿʱ��Դ
    SysTick->VAL=0;                 //���������
    
    do
    {
        temp=SysTick->CTRL;                            //��ȡ��ǰ������ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     //�ȴ�ʱ�䵽��
        
    SysTick->CTRL=0;         //�رռ�����
    SysTick->VAL=0;        //��ռ�����
}
