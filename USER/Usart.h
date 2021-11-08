#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"
//#include "nvic.h"
/** @addtogroup STM32100B_EVAL_LOW_LEVEL_COM
* @{
*/

#define COMn 2

// 1号串口——USART1 端口的初始化数据
/**
* @brief Definition for COM port1, connected to USART1
*/ 
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_RX_PIN                 GPIO_Pin_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_IRQn                   USART1_IRQn

// 2号串口——USART2 端口的初始化数据
/**
* @brief Definition for COM port2, connected to USART2 (USART2 pins remapped on GPIOD)
*/ 
#define EVAL_COM2                        USART2
#define EVAL_COM2_CLK                    RCC_APB1Periph_USART2
#define EVAL_COM2_TX_PIN                 GPIO_Pin_2
#define EVAL_COM2_TX_GPIO_PORT           GPIOA
#define EVAL_COM2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM2_RX_PIN                 GPIO_Pin_3
#define EVAL_COM2_RX_GPIO_PORT           GPIOA
#define EVAL_COM2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM2_IRQn                   USART2_IRQn

/********************************* DMA_USART *********************************************/
// 串口工作参数宏定义
/*
#define DEBUG_USARTx USART1
#define DEBUG_USART_CLK RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE 115200

// USART GPIO 引脚宏定义
#define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOA)
#define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT GPIOA
#define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_9
#define DEBUG_USART_RX_GPIO_PORT GPIOA
#define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_10
*/

// 串口对应的 DMA 请求通道
#define USART_TX_DMA_CHANNEL DMA1_Channel4
// 外设寄存器地址
#define USART_DR_ADDRESS (USART1_BASE+0x04)
// 一次发送的数据量
#define SENDBUFF_SIZE 500
/******************************************************************************************/


//const uint16_t DEBUG_USART_IRQHandler[COMn] = {USART1_IRQHandler, USART2_IRQHandler};

// 定义了 USART 1 和 2 两个串口
typedef enum 
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;  


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void STM_EVAL_COMInit(COM_TypeDef COM,USART_InitTypeDef* USART_InitStruct);

void USARTx_DMA_Config(COM_TypeDef COM);

#endif
