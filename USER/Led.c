#include "Led.h"

void led_init(void)
{
	// 使用 GPIO A3作为 输出端口
	GPIO_InitTypeDef GPIO_InitStructA;     //               
	//GPIO_InitTypeDef GPIO_InitStructB;                    
	//GPIO_InitTypeDef GPIO_InitStructC;                    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  // power the clock of GPIO A,B,C  
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //
	
	GPIO_InitStructA.GPIO_Mode    = GPIO_Mode_Out_PP;    
	GPIO_InitStructA.GPIO_Pin     = GPIO_Pin_3;           
	GPIO_InitStructA.GPIO_Speed   = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOA,&GPIO_InitStructA);                   
	
	/*
	GPIO_InitStructB.GPIO_Mode    = GPIO_Mode_Out_PP;    
	GPIO_InitStructB.GPIO_Pin     = GPIO_Pin_0;           
	GPIO_InitStructB.GPIO_Speed   = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOB,&GPIO_InitStructB);                   
	
	GPIO_InitStructC.GPIO_Mode    = GPIO_Mode_Out_PP;    
	GPIO_InitStructC.GPIO_Pin     = GPIO_Pin_13;           
	GPIO_InitStructC.GPIO_Speed   = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOC,&GPIO_InitStructC);                   
	*/
}

void led_init2(void){
	/*RCC_APB2ENR |= (1<<2); // power GPIOA
	RCC_APB2ENR |= (1<<3); // power GPIOB
	RCC_APB2ENR |= (1<<4); // power GPIOC
	
	GPIOB_CRL &= ~( 0x0F<< (4*0)); // clear PB0
	GPIOB_CRL |= (2<<4*0);  // set PB0 Mode as GPIO_Mode_Out_PP

	GPIOA_CRL &= ~( 0x0F<< (4*3)); // clear PA3
	GPIOA_CRL |= (2<<4*3);  //  set PA3 Mode as GPIO_Mode_Out_PP
	
	GPIOC_CRH &= ~( 0x0F<< (4*5)); // clear PC13
	GPIOC_CRH |= (2<<4*5);  // set PC13 Mode as GPIO_Mode_Out_PP	
	*/
}