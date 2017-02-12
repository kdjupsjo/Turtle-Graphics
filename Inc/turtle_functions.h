#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include "stdbool.h"

#ifndef FOWARD_H_
#define FOWARD_H_

void forward( int x ); 

#endif

#ifndef BLINK_H_
#define BLINK_H_

void BLINK_LED(void); 

#endif

#ifndef UNBLINK_H_
#define UNBLINK_H_

void UNBLINK_LED(void);

#endif

#ifndef PEN_UP_H_
#define PEN_UP_H_

void PEN_UP(void);

#endif

#ifndef PEN_DOWN_H_
#define PEN_DOWN_H_

void PEN_DOWN(void);

#endif

#ifndef PWM_START_H_
#define PWM_START_H_

void PWM_Start(void);

#endif

#ifndef PWM_STOP_H_
#define PWM_STOP_H_

void PWM_Stop(void);

#endif

#ifndef PWM_ERROR_HANDLER_H_
#define PWM_ERROR_HANDLER_H_

void PWM_Error_Handler(void);

#endif

#ifndef FOWARD_H_
#define FOWARD_H_

void foward(uint8_t X);

#endif

#ifndef RIGHT_H_
#define RIGHT_H_

void right(int V); 

#endif

#ifndef LEFT_H_
#define LEFT_H_

void left(int V); 

#endif

#ifndef SYSTEMCLOCK_CONFIG_H_
#define SYSTEMCLOCK_CONFIG_H_

void SystemClock_Config(void);

#endif

#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

void Error_Handler(void); 

#endif

#ifndef TRANSMIT_DATA_H_
#define TRANSMIT_DATA_H_

void Transmit_Data(uint8_t Send[]); 

#endif

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif