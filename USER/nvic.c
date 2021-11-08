#include "nvic.h"
uint16_t DEBUG_USART_IRQ[2] = {USART1_IRQn, USART2_IRQn};
uint16_t DEBUG_GPIO_IRQ[2] = {TIM1_UP_IRQn, TIM1_UP_IRQn};

void NVIC_Configuration(int COM)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 配置 NVIC 为优先级组 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* 配置中断源：按键 1 */
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ[COM];
	/* 配置抢占优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* 配置中断源：按键 2，其他使用上面相关配置 */
	//NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	//NVIC_Init(&NVIC_InitStructure);
}

void NVIC_GPIO_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 配置 NVIC 为优先级组 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* 配置中断源：按键 1 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	/* 配置抢占优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* 配置中断源：按键 2，其他使用上面相关配置 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/*开启按键 GPIO 口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);

	/* 配置 NVIC 中断*/
	NVIC_GPIO_Configuration();
	
	/*--------------------------KEY1 配置---------------------*/
	/* 选择按键用到的 GPIO */
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	/* 配置为浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择 EXTI 的信号源 */
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, \
	KEY1_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;

	/* EXTI 为中断模式 */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 下降沿中断 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	/* 上升沿中断 */
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	/* 使能中断 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/*--------------------------KEY2 配置------------------*/
	/* 选择按键用到的 GPIO */
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	/* 配置为浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择 EXTI 的信号源 */
	GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, \
	KEY2_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;

	/* EXTI 为中断模式 */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 下降沿中断 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;

	/* 使能中断 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

