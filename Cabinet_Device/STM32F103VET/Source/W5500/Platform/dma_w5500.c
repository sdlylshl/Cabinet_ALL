
#include "../Ethernet.h"

// 外设    通道1     		通道2     	通道3     	通道4       通道5       通道6        通道7 
// ADC     ADC1       
// SPI                 SPI1_RX     SPI1_TX     SPI2_RX     SPI2_TX   
// USART               USART3_TX   USART3_RX   USART1_TX   USART1_RX   USART2_RX   USART2_TX
// I2C                                         I2C2_TX     I2C2_RX     I2C1_TX     I2C1_RX 
// TIM1                TIM1_CH1    TIM1_CH2    TIM1_TX4    TIM1_UP     TIM1_CH3
//                                             TIM1_TRIG
//                                             TIM1_COM      
// TIM2    TIM2_CH3    TIM2_UP                             TIM2_CH1                TIM2_CH2 
//                                                                                 TIM2_CH4 
// TIM3                TIM3_CH3    TIM3_CH4                            TIM3_CH1
//                                 TIM3_UP                             TIM3_TRIG 
// TIM4    TIM4_CH1                            TIM4_CH2    TIM4_CH3                TIM4_UP

void WIZ_DMA_Configuration(void)
{
//	DMA_InitTypeDef DMA_InitStructure;

	/* Deinitialize DMA Streams */
	//DMA_DeInit(DMA2_Stream3);	//SPI1_TX_DMA_STREAM
	//DMA_DeInit(DMA2_Stream2);	//SPI1_RX_DMA_STREAM

#if 0	
	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = DATA_BUF_SIZE;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI1->DR)) ;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  /* Configure TX DMA */
  DMA_InitStructure.DMA_Channel = DMA_Channel_0 ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aTxBuffer ;
  DMA_Init(DMA1_Stream4, &DMA_InitStructure);
  /* Configure RX DMA */
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aRxBuffer ; 
  DMA_Init(DMA1_Stream3, &DMA_InitStructure);
#endif
	
}
