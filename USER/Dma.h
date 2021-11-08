#ifndef _DMA_H_
#define _DMA_H_
#include "stm32f10x.h"

#define DMA_CHANNEL DMA1_Channel6
#define DMA_CLOCK RCC_AHBPeriph_DMA1

// 传输完成标志
#define DMA_FLAG_TC DMA1_FLAG_TC6

// 要发送的数据大小
#define BUFFER_SIZE 32

void DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);




#endif
