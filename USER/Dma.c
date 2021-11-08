#include "Dma.h"
// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定


/* 定义 aSRC_Const_Buffer 数组作为 DMA 传输数据源
* const 关键字将 aSRC_Const_Buffer 数组变量定义为常量类型
* 表示数据存储在内部的 FLASH 中
*/
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]=
{
	0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
	0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
	0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
	0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
	0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
	0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
	0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
	0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
};
/* 定义 DMA 传输目标存储器
* 存储在内部的 SRAM 中
*/
uint32_t aDST_Buffer[BUFFER_SIZE];



void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	// 开启 DMA 时钟
	RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
	// 源数据地址
	DMA_InitStructure.DMA_PeripheralBaseAddr =
	(uint32_t)aSRC_Const_Buffer;
	/************************************************************/
	// 目标地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	// 目标地址—串口地址
	//DMA_InitStructure.DMA_MemoryBaseAddr = USARTy_DR_Address;
	/************************************************************/
	// 方向：外设到存储器（这里的外设是内部的 FLASH）
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	// 传输大小
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	// 外设（内部的 FLASH）地址递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	// 内存地址递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 外设数据单位
	DMA_InitStructure.DMA_PeripheralDataSize =
	DMA_PeripheralDataSize_Word;
	// 内存数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	// DMA 模式，一次或者循环模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// 优先级：高
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// 使能内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	// 配置 DMA 通道
	DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
	// 使能 DMA
  DMA_Cmd(DMA_CHANNEL,ENABLE);
}

uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
	/* 数据长度递减 */
	while (BufferLength--) {
	/* 判断两个数据源是否对应相等 */
	if (*pBuffer != *pBuffer1) {
	/* 对应数据源不相等马上退出函数，并返回 0 */
		return 0;
	}
	/* 递增两个数据源的地址指针 */
	pBuffer++;
	pBuffer1++;
	}
	/* 完成判断并且对应数据相对 */
	return 1;
}
