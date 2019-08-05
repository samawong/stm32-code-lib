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

//写数据函数，len为传送数据位数，数据传送为低位在前
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
 //函数名称：void SendCmd(uint8_t command)
 //功能描述: HT1621命令写入函数
 //参数说明：Cmd为写入命令数据
 //说 明：写入命令标识位100
 //-----------------------------------------------------------------------------------------
void SendCmd(uint8_t command)
{
	CS(0);
	HAL_Delay(5);
  SendBit_1621(0x80,3);   //写入命令标志100,原为 SendBit_1621(0x80,3);
	SendBit_1621(command,9); //写入命令数据，原为SendBit_1621(command,9);
	CS(1);
	HAL_Delay(5);
}

//-----------------------------------------------------------------------------------------
//函数名称：void Write_1621(uint8_t addr,uint8_t data)
//功能描述: HT1621在指定地址写入数据函数
//参数说明：Addr为写入初始地址，Data为写入数据
//说 明：因为HT1621的数据位4位，所以实际写入数据为参数的后4位
//-----------------------------------------------------------------------------------------
void Write_1621(uint8_t addr,uint8_t data)
{
CS(0);
HAL_Delay(5);	
SendBit_1621(0xa0,3); //写入数据标志101     
SendBit_1621(addr<<2,6);  //写入地址数据 
SendDataBit_1621(data,4); //写入数据 
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
//函数名称：void Ht1621WrOneNum(uchar Addr,uchar Num)
//功能描述: HT1621在指定地址写入一个数字（0-9）函数
//参数说明：Addr为写入初始地址，Num为写入数据
//说 明：因为HT1621的数据位4位，所以实际写入数据为参数的后4位
//-----------------------------------------------------------------------------------------

void Ht1621WrOneNum(uint8_t Addr,uint8_t num)
{
CS(0);//HT1621_CS=0;
SendBit_1621(0xa0,3); //写入数据标志101
SendBit_1621(Addr<<2,6); //写入地址数据
SendBit_1621(num,8);//写一个完整的数。就是连续写两个数。 
CS(1);//
}

//-----------------------------------------------------------------------------------------
//函数名称：void Ht1621WrAllData()
//功能描述: HT1621连续写入方式函数
//说 明：HT1621的数据位4位，此处每次数据为8位，写入数据总数按8位计算
//-----------------------------------------------------------------------------------------
void Ht1621WrAllData(uint8_t num)
{
  uint8_t i;
  CS(0);//

  SendBit_1621(0xa0,3); //写入数据标志101
  SendBit_1621(0x00<<2,6); //写入地址数据
  for (i=0;i<16;i++)
  {
    SendBit_1621(num,8);//0x00,8); //写入数据
  }
  CS(1);//
}


