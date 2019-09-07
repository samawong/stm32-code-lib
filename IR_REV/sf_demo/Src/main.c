/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>

#include "oled.h"
#include "ds1302.h"
#include "control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint32_t Remote_Odr;    //命令暂存处		 	
extern uint8_t  Remote_Cnt;    //按键次数,此次按下键的次数
extern uint8_t  Remote_Rdy; 
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t DShour,DSminute,DSsecond;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t key;
	
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	
	DS1302_Init();
	
	OLED_Init();
	OLED_Fill(0xFF);
	HAL_Delay(10);
	OLED_Fill(0x00);
	for(int i=0;i<7;i++){
		
		OLED_ShowCN(1+i*16,0,i);
		
	}
	
	HAL_Delay(2);
	OLED_ShowStr(0,2,(unsigned char *)"Temp:",2);
	HAL_Delay(2);
	OLED_ShowStr(40,2,(unsigned char *)"27",2);
	HAL_Delay(2);
	OLED_ShowStr(70,2,(unsigned char *)"C",2);
	HAL_Delay(2);
	OLED_ShowStr(0,4,(unsigned char *)"Humi:",2);
	HAL_Delay(2);
	OLED_ShowStr(40,4,(unsigned char *)"56",2);
	HAL_Delay(2);
	OLED_ShowStr(70,4,(unsigned char *)"F",2);
	
	

	//OLED_CLS();
	//OLED_OFF();
	//HAL_Delay(2);
	//OLED_ON();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  		time_read();
		//printf("%d%d:%d%d:%d%d\n",DShour/16,DShour%16,DSminute/16,DSminute%16,(DSsecond&0x70)>>4,DSsecond&0x0f);
		unsigned char  h_ge,  h_shi,m_ge,m_shi,s_ge,s_shi;
		h_ge = (DShour%16)+0x30;
		h_shi = (DShour/16)+0x30;
		m_shi = (DSminute/16)+0x30;
		m_ge = (DSminute%16)+0x30;
		s_shi = ((DSsecond&0x70)>>4)+0x30;
		s_ge = (DSsecond&0x0f)+0x30;
		HAL_Delay(2);
		OLED_ShowStr(0,6,(unsigned char *)"Time :",2);
		HAL_Delay(2);
		OLED_ShowStr(50,6,&h_shi,2);
		HAL_Delay(2);
		OLED_ShowStr(60,6,&h_ge,2);
		HAL_Delay(2);
		OLED_ShowStr(70,6,(unsigned char *)":",2);
		HAL_Delay(2);
		OLED_ShowStr(80,6,&m_shi,2);
		HAL_Delay(2);
		OLED_ShowStr(90,6,&m_ge,2);
		HAL_Delay(2);
		OLED_ShowStr(100,6,(unsigned char *)":",2);
		HAL_Delay(2);
		OLED_ShowStr(110,6,&s_shi,2);
		HAL_Delay(2);
		OLED_ShowStr(120,6,&s_ge,2);
		
		
		if(Remote_Rdy){
			key = Remote_Process();
			switch(key){
				case 0x68:printf("0模式\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,150); break;
				case 0x88:printf("1定时\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,200);break; 
				case 0x18:
					printf("2风速下\n");
				  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,50); 
					
				  break;
				case 0x98:
					printf("3风速上\n");
				  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,25);
					
  				break;
				case 0xa8:printf("4杀菌\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,100); break;
				case 0x38:printf("5on/off键\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,0); break;
				case 0x28:printf("6童锁\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,230);break;
				case 0x42:printf("7\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,350); break;
				case 0x4a:printf("8\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,400); break;
				case 0x52:printf("9\n");__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,450); break;
				default: break;
			}
		}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_1){
		Toggle_LED();
	}
}

void Toggle_LED(void){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_15);
}*/

int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch,1, 0xFFFF);
    return ch;
}
int fgetc(FILE *f)
{
  uint8_t  ch;
    HAL_UART_Receive(&huart1,(uint8_t *)&ch, 1, 0xFFFF);
    return  ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
