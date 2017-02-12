// Main program test

#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include "stdbool.h"
#include "turtle_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

ITStatus UartReady = RESET; 

/* Size of Transmission buffer */
#define BUFFERSIZE 22
uint8_t Buffer[1];
char finalBuffer[BUFFERSIZE];

int i = 0; 
int units; 
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */ 
  UartReady = SET;
  memset( &Buffer[0], '\0', sizeof(Buffer));
  //*(Buffer) = Buffer[0];
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
  UartReady = SET;
}

/*-----------------------------MAIN PROGRAM-----------------------------------*/
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM4_Init_Down();                        
  MX_USART3_UART_Init();
  
  HAL_GPIO_WritePin(MS1_GPIO_Port, MS1_Pin, SET);                               //MICROSTEPMODE
  HAL_GPIO_WritePin(MS2_GPIO_Port, MS2_Pin, SET);                               //EIGHT STEP
  
  Transmit_Data("Turtleee\n");
  while ( UartReady != SET ) {}                                                 //väntar på transmit innan buffert resetas
  UartReady = RESET;
  
  while (1) 
  {
    while ( *Buffer != '\r')                                                    //väntar på slutecken
      {
        HAL_UART_Receive_IT(&huart3, (uint8_t *)Buffer, 1);                     //Receive tecken för tecken
        while ( UartReady != SET ) {}
        UartReady = RESET;                                                      //Väntar på att recieve flaggas som klar
        finalBuffer[i] = *Buffer;                                               //kopierar över tecknet till en char array
        i++;
      }
    HAL_Delay(100);
    if( strncmp(finalBuffer, "Blink", 5) == 0 ) {                               //jämför strängen 
      BLINK_LED();
      Transmit_Data("cmd: ok \n");

    } else if ( strncmp(finalBuffer, "Turn off", 8) == 0 ) {                    //jämför
      UNBLINK_LED();
      Transmit_Data("cmd: ok \n");
      
    } else if ( strncmp(finalBuffer, "forward", 7) == 0) {                      //jämför
      sscanf(finalBuffer, "forward %d" , &units);                               //extraherar värder turle ska flytta sig 
      forward(units);
      Transmit_Data("cmd: ok \n");                                              
      
    } else if ( strncmp(finalBuffer, "left", 4) == 0) {                         //jämför "left"
      sscanf(finalBuffer, "left %d" , &units);
      left(units);
      Transmit_Data("cmd: ok \n"); 
      
    } else if ( strncmp(finalBuffer, "right", 5) == 0) {                         //jämför "right"
      sscanf(finalBuffer, "right %d" , &units);
      right(units);
      Transmit_Data("cmd: ok \n");
      
    } else if ( strncmp(finalBuffer, "pen down", 8) == 0) {                     //jämför "pendown"
      PEN_DOWN();
      Transmit_Data("cmd: ok \n");
    
    } else if ( strncmp(finalBuffer, "pen up", 6) == 0) {                       //jämför "penup"
      PEN_UP();
      Transmit_Data("cmd: ok \n");
    
    } else if ( strncmp(finalBuffer, "square", 6) == 0) { 
      sscanf(finalBuffer, "square %d" , &units);
      PEN_DOWN();
      forward(units);
      left(90);
      forward(units);
      left(90);
      forward(units);
      left(90);
      forward(units);
      Transmit_Data("cmd: ok \n");
      
    }else {                                                                     // ingen match ger invalid output 
      Transmit_Data("Invalid \n");
    }
    while ( UartReady != SET ) {}                                               //väntar på transmit innan buffert resetas
    UartReady = RESET;
    memset(&finalBuffer[0], NULL, sizeof(finalBuffer));
    i = 0;
  }
}