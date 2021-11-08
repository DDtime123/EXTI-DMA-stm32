#ifndef _NVIC_H_
#define _NVIC_H_
#include "stm32f10x.h"

//引脚定义
#define KEY1_INT_GPIO_PORT GPIOA
#define KEY1_INT_GPIO_CLK (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE GPIO_PinSource0
#define KEY1_INT_EXTI_LINE EXTI_Line0
#define KEY1_INT_EXTI_IRQ EXTI0_IRQn

#define KEY1_IRQHandler EXTI0_IRQHandler

#define KEY2_INT_GPIO_PORT GPIOA
#define KEY2_INT_GPIO_CLK (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)
#define KEY2_INT_GPIO_PIN GPIO_Pin_1
#define KEY2_INT_EXTI_PORTSOURCE GPIO_PortSourceGPIOA
#define KEY2_INT_EXTI_PINSOURCE GPIO_PinSource1
#define KEY2_INT_EXTI_LINE EXTI_Line1
#define KEY2_INT_EXTI_IRQ EXTI1_IRQn

#define KEY2_IRQHandler EXTI1_IRQHandler

void NVIC_Configuration(int COM);
void NVIC_GPIO_Configuration();

#endif
