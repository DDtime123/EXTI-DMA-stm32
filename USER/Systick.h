#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "stm32f10x.h"

void delay_us(u32 nus);
void delay_ms(u16 nms);
void SysTick_Delay_Ms( __IO uint32_t ms);

#endif
