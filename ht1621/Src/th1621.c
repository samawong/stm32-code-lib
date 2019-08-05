#include "th1621.h"

void port_init(void){
	SendCmd(BIAS);
	SendCmd(RC256);
	SendCmd(SYSDIS);
	SendCmd(WDTDIS);
	SendCmd(SYSEN);
	SendCmd(LCDON);
}

uint8_t LCD_ADD[27]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,
                     0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x08,0x0f,0x0f,0x0f,
	                   0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};

	void display_all(void)
		{
			uint8_t LCD_ON[27]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,
                     0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x08,0x0f,0x0f,0x0f,
	                   0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
			uint8_t a=0;
			for(a=0;a<28;a++)
			{
			 Write_1621(a,LCD_ON[a]);
			}
		}

	void display_off(void)
{
	uint8_t LCD_OFF[27]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											 0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t a=0;
	for(a=0;a<28;a++)
	{
	 Write_1621(a,LCD_OFF[a]);
	}
}

//д���ݺ�����lenΪ��������λ�������ݴ���Ϊ��λ��ǰ
void SendBit_1621(uint8_t data,uint8_t len)
{
  uint8_t i;
	for(i=0;i<len; i++)
	{
		WR(0);
		HAL_Delay(5);
		if(data&0x80) 
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_SET);
		}
		else  
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_RESET);
		}
		HAL_Delay(5);
		WR(1);
		HAL_Delay(5);
    data<<=1;	    		
	}
}

 //-----------------------------------------------------------------------------------------
 //�������ƣ�void SendCmd(uint8_t command)
 //��������: HT1621����д�뺯��
 //����˵����CmdΪд����������
 //˵ ����д�������ʶλ100
 //-----------------------------------------------------------------------------------------
void SendCmd(uint8_t command)
{
	CS(0);
	HAL_Delay(5);
  SendBit_1621(0x80,3);   //д�������־100,ԭΪ SendBit_1621(0x80,3);
	SendBit_1621(command,9); //д���������ݣ�ԭΪSendBit_1621(command,9);
	CS(1);
	HAL_Delay(5);
}

//-----------------------------------------------------------------------------------------
//�������ƣ�void Write_1621(uint8_t addr,uint8_t data)
//��������: HT1621��ָ����ַд�����ݺ���
//����˵����AddrΪд���ʼ��ַ��DataΪд������
//˵ ������ΪHT1621������λ4λ������ʵ��д������Ϊ�����ĺ�4λ
//-----------------------------------------------------------------------------------------
void Write_1621(uint8_t addr,uint8_t data)
{
CS(0);
HAL_Delay(5);	
SendBit_1621(0xa0,3); //д�����ݱ�־101     
SendBit_1621(addr<<2,6);  //д���ַ���� 
SendDataBit_1621(data,4); //д������ 
CS(1);
HAL_Delay(5);
}

void SendDataBit_1621(uint8_t data,uint8_t len)
{
  uint8_t i;
	
	for(i=0;i<len; i++)
	{
		WR(0);
		HAL_Delay(5);
		if(data&0x01) 
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_SET);
		}
		else  		
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_RESET);
			}
		HAL_Delay(5);
		WR(1);
    HAL_Delay(5);	
    data>>=1;		
	}
}




//-----------------------------------------------------------------------------------------
//�������ƣ�void Ht1621WrOneNum(uchar Addr,uchar Num)
//��������: HT1621��ָ����ַд��һ�����֣�0-9������
//����˵����AddrΪд���ʼ��ַ��NumΪд������
//˵ ������ΪHT1621������λ4λ������ʵ��д������Ϊ�����ĺ�4λ
//-----------------------------------------------------------------------------------------

void Ht1621WrOneNum(uint8_t Addr,uint8_t num)
{
CS(0);//HT1621_CS=0;
SendBit_1621(0xa0,3); //д�����ݱ�־101
SendBit_1621(Addr<<2,6); //д���ַ����
SendBit_1621(num,8);//дһ��������������������д�������� 
CS(1);//
}

//-----------------------------------------------------------------------------------------
//�������ƣ�void Ht1621WrAllData()
//��������: HT1621����д�뷽ʽ����
//˵ ����HT1621������λ4λ���˴�ÿ������Ϊ8λ��д������������8λ����
//-----------------------------------------------------------------------------------------
void Ht1621WrAllData(uint8_t num)
{
  uint8_t i;
  CS(0);//

  SendBit_1621(0xa0,3); //д�����ݱ�־101
  SendBit_1621(0x00<<2,6); //д���ַ����
  for (i=0;i<16;i++)
  {
    SendBit_1621(num,8);//0x00,8); //д������
  }
  CS(1);//
}


