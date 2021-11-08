#include "stm32f10x.h"
#include "Led.h"
#include "Systick.h"
#include "Usart.h"
#include "nvic.h"
#include <stdio.h>
#include <string.h>


USART_InitTypeDef  USART_InitStructure;
__IO uint32_t LowPowerMode = 0;

char buffer[100] = {0};
char count = 0;
u8 rx_i = 0;
char rx_buffer1[100] = {0};
char rx_buffer2[100] = {0};
u8 flag = 0;
u8 flag2 = 0;
u8 key_flag = 0;
u8 key_flag2 = 0;
uint16_t c;


unsigned int i=0;
uint32_t del = 1000;

uint8_t TransferStatus;

//extern char* SendBuff;

int main(void)
{
	led_init();

	// 初始化 USART 端口配置
	/* EVAL_COM1 configuration ---------------------------------------------------*/
	/* EVAL_COM1 configured as follow:
         - BaudRate = 115200 baud  
         - Word Length = 8 Bits
         - One Stop Bit
         - No parity
         - Hardware flow control disabled (RTS and CTS signals)
         - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	
	/******************************************************************************************/
	// 初始化串口函数(非标准库函数)
	STM_EVAL_COMInit(COM1, &USART_InitStructure);
	//STM_EVAL_COMInit(COM2, &USART_InitStructure);
	//EXTI_Key_Config();
	//GPIO_SetBits(GPIOA, GPIO_Pin_3);
	/*******************************************************************************************/
	/* DMA 传输配置 */
	USARTx_DMA_Config(COM1);
	//printf("\r\n USART1 DMA TX 测试 \r\n");

	
	/*为演示 DMA 持续运行而 CPU 还能处理其它事情，持续使用 DMA 发送数据，量非常大，
	*长时间运行可能会导致电脑端串口调试助手会卡死，鼠标乱飞的情况，
	*或把 DMA 配置中的循环模式改为单次模式*/
	/* USART1 向 DMA 发出 TX 请求 , 数据传输开始*/
	//USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	
	/* 此时 CPU 是空闲的，可以干其他的事情 */
	//例如同时控制 LED

	/**********************************************************************************************/
	
	while(1){
		//Usart_SendString(USART1,"Hello USART1!\n");
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
		delay_ms(500);
		delay_ms(500);
		USART_DMACmd(USART1, USART_DMAReq_Tx, DISABLE);
		delay_ms(500);
		delay_ms(500);
		/*
		if(flag == 1)
		{
			Usart_SendString(USART1,(char *)rx_buffer1);
			memset(rx_buffer1,0,sizeof(rx_buffer1));
			//send_str_esp((uint8_t *)rx_buffer1);
			flag=0;
		}
		//delay_ms(1000);
		if(flag2 == 1)
		{
			Usart_SendString(USART2,(char *)rx_buffer2);
			memset(rx_buffer2,0,sizeof(rx_buffer2));
			//printf(rx_buffer2);
			flag2=0;
		}
		*/
		
		// 打印串口输出
		//Usart_SendString(USART1,"Hello USART1!\n");
		//delay_ms(500);
		//Usart_SendString(USART2,"Hello USART2!\n");
		/*
		switch(i%3){
			case 0: state1();
				break;
			case 1: state2();
				break;
			case 2: state3();
				break;
		}
		*/
		//delay_ms(1000);
		i++;
	}
}

//串口中断函数
void USART1_IRQHandler(void)
{
	/*
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//½ÓÊÕÖÐ¶Ï
	{
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		buffer[count++] = USART_ReceiveData(USART1);
		if(buffer[count-2] == 0x0D && buffer[count-1] == 0x0A)//½ÓÊÕµÄÊý¾Ý±ØÐëÒªÒÔ\r\n½áÎ²
		{
			for(rx_i = 0; rx_i < count; rx_i++)
			{
				rx_buffer1[rx_i] = buffer[rx_i];
				buffer[rx_i] = 0;
			}
			//send_str(rx_buffer);
			printf(rx_buffer1);
			flag = 1;
			count = 0;
			//send_str_esp("AT\r\n");
		}		
	}
	*/
	uint8_t ucTemp;
	if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) {
		ucTemp = USART_ReceiveData( USART1 );
		USART_SendData(USART1,ucTemp);
	}
}

//串口中断函数
void USART2_IRQHandler(void)
{
	/*
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//½ÓÊÕÖÐ¶Ï
	{
		//Çå¿Õ½ÓÊÕÊý¾ÝµÄ±êÖ¾Î»
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		buffer[count++] = USART_ReceiveData(USART3);
		if(buffer[count-2] == 0x0D && buffer[count-1] == 0x0A)//½ÓÊÕµÄÊý¾Ý±ØÐëÒªÒÔ\r\n½áÎ²
		{
			for(rx_i = 0; rx_i < count; rx_i++)
			{
				rx_buffer2[rx_i] = buffer[rx_i];
				buffer[rx_i] = 0;
			}
			//send_str(rx_buffer3);
			//printf(rx_buffer3);//´òÓ¡´®¿Ú3»Ø´«µÄÊý¾Ý
			flag2 = 1;
			count = 0;
		}		
	}
	*/
	uint8_t ucTemp;
	if (USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET) {
		ucTemp = USART_ReceiveData( USART2 );
		USART_SendData(USART2,ucTemp);
	}
}

//GPIO 中断函数
void KEY1_IRQHandler(void)
{
	key_flag=1;
	//确保是否产生了 EXTI Line 中断
	if (EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) {
		// LED1 取反
		//LED1_TOGGLE;
		//清除中断标志位
		//key_flag
		
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
		
				if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) )
          {
                GPIO_SetBits(GPIOA, GPIO_Pin_3);
          }
          else
          {
								GPIO_ResetBits(GPIOA, GPIO_Pin_3);
          }
		
		Usart_SendString(USART1,"EXTI0");
		//delay_ms(1000);
	}
	
}
//GPIO 中断函数
void KEY2_IRQHandler(void)
{
	//确保是否产生了 EXTI Line 中断
	if (EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) {
		// LED1 取反
		
		//清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);
		Usart_SendString(USART1,"EXTI4");
		delay_ms(1000);
	}
	
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
