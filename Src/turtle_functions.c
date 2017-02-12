#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include "stdbool.h"
#include <stdint.h>

static void PWM_Error_Handler(void)
{
  BSP_LED_On(LED10);
    while(1) {}
}

static void Error_Handler(void) 
{
  BSP_LED_On(LED5); 
  while(1) {}
}

void PWM_Start(void)
{
   if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2) != HAL_OK)
  {
    /* PWM Generation Error */
    PWM_Error_Handler();
  }
}
void PWM_Stop(void) 
{
   if (HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2) != HAL_OK)
  {
    /* PWM Generation Error */
    PWM_Error_Handler();
  }
}

void BLINK_LED(void) 
{
  BSP_LED_On(LED4);
}

void UNBLINK_LED(void)
{
  BSP_LED_Off(LED4);
}

void PEN_UP(void) 
{
  MX_TIM4_Init_Up();
  PWM_Start();
  HAL_Delay(500);
  PWM_Stop();
}

void PEN_DOWN(void)
{
  MX_TIM4_Init_Down();
  PWM_Start(); 
  HAL_Delay(500);
  PWM_Stop();
}

void Transmit_Data(uint8_t Send[]) 
{
  uint8_t Size = 11; 
  if (  HAL_UART_Transmit_IT(&huart3, (uint8_t*)Send, Size) != HAL_OK ) {
    Error_Handler();
  }
  //HAL_Delay(100);
}

void forward( int x ) 
{
  
  double steps = (800/(47*3.1415))*x;
  
  HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, SET);                             //Riktning framåt
  HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, SET);                             //Båda hjulen
 
  for(int i = 0; i < steps; i++ ) 
  {
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, SET);                         //Riktning framåt
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, RESET);                       //Riktning framåt
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, RESET);
    HAL_Delay(1);
  }
}

void left ( int V ) 
{ 
  double steps = ((800*120)/(47*360))*V; 
  
  HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, RESET);                           //Riktning bakåt
  HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, SET);                             //Riktning framåt
  
   for(int i = 0; i < steps; i++ ) 
  {
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, SET);                         //Riktning framåt
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, RESET);                       //Riktning framåt
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, RESET);
    HAL_Delay(1);
  }
}

void right ( int V ) 
{ 
  double steps = ((800*120)/(47*360))*V; 
  
  HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, SET);                             //Riktning framåt
  HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, RESET);                           //Riktning bakåt
  
   for(int i = 0; i < steps; i++ ) 
  {
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, SET);                         //Riktning framåt
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, RESET);                       //Riktning framåt
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, RESET);
    HAL_Delay(1);
  }
}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}