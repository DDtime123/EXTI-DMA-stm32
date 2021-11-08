#include "Usart.h"
#include "nvic.h"
#include "stdlib.h"
// 串口 1 和 串口 2——USART1 和 USART2
USART_TypeDef* COM_USART[COMn] = {EVAL_COM1, EVAL_COM2}; 
// 串口输出端口
GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT, EVAL_COM2_TX_GPIO_PORT};
// 串口输入端口
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT, EVAL_COM2_RX_GPIO_PORT};
// 两个串口的时钟
const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK, EVAL_COM2_CLK};
// GPIO输出端口时钟
const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK, EVAL_COM2_TX_GPIO_CLK};
// GPIO输入端口时钟
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK, EVAL_COM2_RX_GPIO_CLK};
// 输入引脚
const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN, EVAL_COM2_TX_PIN};
// 输出引脚
const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN, EVAL_COM2_RX_PIN};

USART_TypeDef* DEBUG_USARTx[COMn] = {USART1, USART2};
const uint32_t DEBUG_USART_CLK[COMn] = {RCC_APB2Periph_USART1, RCC_APB1Periph_USART2};
//const uint16_t DEBUG_USART_APBxClkCmd[COMn] = {RCC_APB2PeriphClockCmd, RCC_APB1PeriphClockCmd};
int DEBUG_USART_BAUDRATE[COMn] = {115200, 115200};
uint16_t DEBUG_USART_GPIO_CLK[COMn] = {RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOA};
//const uint16_t DEBUG_USART_GPIO_APBxClkCmd[COMn] = {RCC_APB2PeriphClockCmd, RCC_APB2PeriphClockCmd};
GPIO_TypeDef* DEBUG_USART_TX_GPIO_PORT[COMn] = {GPIOA, GPIOA};
uint16_t DEBUG_USART_TX_GPIO_PIN[COMn] = {GPIO_Pin_9, GPIO_Pin_2};
GPIO_TypeDef* DEBUG_USART_RX_GPIO_PORT[COMn] = {GPIOA, GPIOA};
uint16_t DEBUG_USART_RX_GPIO_PIN[COMn] = {GPIO_Pin_10, GPIO_Pin_3};

// 初始化串口配置
void STM_EVAL_COMInit(COM_TypeDef COM,USART_InitTypeDef* USART_InitStruct)
{
	/***********************************************************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口 GPIO 的时钟
	//DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);


	if(COM == COM1){
		// 打开串口 GPIO 的时钟
		RCC_APB2PeriphClockCmd(DEBUG_USART_GPIO_CLK[COM], ENABLE);
		// 打开串口外设的时钟
		RCC_APB2PeriphClockCmd(DEBUG_USART_CLK[COM], ENABLE);
	}else{
		// 打开串口 GPIO 的时钟
		RCC_APB2PeriphClockCmd(DEBUG_USART_GPIO_CLK[COM], ENABLE);
		// 打开串口外设的时钟
		RCC_APB1PeriphClockCmd(DEBUG_USART_CLK[COM], ENABLE);
	}

	// 将 USART Tx 的 GPIO 配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN[COM];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT[COM], &GPIO_InitStructure);
	
	// 将 USART Rx 的 GPIO 配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN[COM];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT[COM], &GPIO_InitStructure);

	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE[COM];
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx[COM], &USART_InitStructure);

	// 串口中断优先级配置
	NVIC_Configuration(COM);

	// 使能串口接收中断
	USART_ITConfig(DEBUG_USARTx[COM], USART_IT_RXNE, ENABLE);

	// 使能串口
	USART_Cmd(DEBUG_USARTx[COM], ENABLE);
}

char* SendBuff;
int j;

void USARTx_DMA_Config(COM_TypeDef COM)
{
	DMA_InitTypeDef DMA_InitStructure;
	SendBuff = (char*)malloc(SENDBUFF_SIZE);
	/*填充将要发送的数据*/
	
	
	for (j=0; j<SENDBUFF_SIZE; j++)
	{
		SendBuff[j] = 'P';
	}
	SendBuff[SENDBUFF_SIZE]='\0';
	
	
	
	// 开启 DMA 时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// 设置 DMA 源地址：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;
	// 内存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
	// 方向：从内存到外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	// 传输大小
	DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
	// 外设地址不增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// 内存地址自增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 外设数据单位
	DMA_InitStructure.DMA_PeripheralDataSize =
	DMA_PeripheralDataSize_Byte;
	// 内存数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	// DMA 模式，一次或者循环模式
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// 优先级：中
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	// 配置 DMA 通道
	DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);
	// 使能 DMA
	DMA_Cmd (USART_TX_DMA_CHANNEL,ENABLE);
}



/***************** 发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
/* 发送一个字节数据到 USART */
USART_SendData(pUSARTx,ch);
/* 等待发送数据寄存器为空 */	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/***************** 发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do {
	Usart_SendByte( pUSARTx, *(str + k) );
		k++;
	} while (*(str + k)!='\0');

	/* 等待发送完成 */
	while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) {}
}
