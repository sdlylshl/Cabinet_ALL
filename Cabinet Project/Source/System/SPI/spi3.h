#ifndef __SPI3_H
#define __SPI3_H

#include "version.h"

//#define SPI3_DMA 
  // SPI3 PB 3 4 5	
#define SPI3_SCS_PORT				GPIOA
#define SPI3_SCS_PIN				GPIO_Pin_15
#define SPI3_SCS_MODE				GPIO_Mode_Out_PP
	
#define SPI3_SCLK_PORT			GPIOB
#define SPI3_SCLK_PIN				GPIO_Pin_3
#define SPI3_SCLK_MODE			GPIO_Mode_AF_PP	

#define SPI3_MISO_PORT			GPIOB
#define SPI3_MISO_PIN				GPIO_Pin_4	
#define SPI3_MISO_MODE			GPIO_Mode_AF_PP

#define SPI3_MOSI_PORT			GPIOB		
#define SPI3_MOSI_PIN				GPIO_Pin_5	
#define SPI3_MOSI_MODE			GPIO_Mode_AF_PP

void SPI3_Config(void);
uint8_t SPI3_SendByte(uint8_t byte);
uint8_t SPI3_ReceiveByte(void);

#endif

