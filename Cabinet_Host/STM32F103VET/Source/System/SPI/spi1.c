#include "stm32f10x.h"
#include "config.h"

#include "spi1.h"

static void SPI1_GPIO_Config(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
	
			RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1, ENABLE);
	
#if   SPI1_REMAP  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	
    GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE);
#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#endif  

        GPIO_InitStructure.GPIO_Pin = SPI1_SCS_PIN;
        GPIO_InitStructure.GPIO_Mode = SPI1_SCS_MODE;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(SPI1_SCS_PORT, &GPIO_InitStructure);
				
        GPIO_InitStructure.GPIO_Pin = SPI1_SCLK_PIN;
        GPIO_InitStructure.GPIO_Mode = SPI1_SCLK_MODE;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(SPI1_SCLK_PORT, &GPIO_InitStructure);	
				
	      GPIO_InitStructure.GPIO_Pin = SPI1_MISO_PIN;
        GPIO_InitStructure.GPIO_Mode = SPI1_MISO_MODE;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(SPI1_MISO_PORT, &GPIO_InitStructure);	
				
				GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_PIN;
        GPIO_InitStructure.GPIO_Mode = SPI1_MOSI_MODE;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(SPI1_MOSI_PORT, &GPIO_InitStructure);
}


void SPI1_Config(void)
{
		SPI_InitTypeDef   SPI_InitStructure;

		SPI1_GPIO_Config();
	
	  /* SPI Config -------------------------------------------------------------*/
	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	  SPI_InitStructure.SPI_CRCPolynomial = 7;

	  SPI_Init(SPI1, &SPI_InitStructure);
	  
	  /* Enable SPI */
#if !defined (SPI1_DMA)	
	SPI_Cmd(SPI1, ENABLE);
#endif

		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) ;
}


uint8_t SPI1_SendByte(uint8_t byte)
{		uint8_t i = 0;
	  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
         
	  SPI_I2S_SendData(SPI1, byte);
          
	  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){if(i++>0xF0)break;}
          
	  return SPI_I2S_ReceiveData(SPI1);
}

uint8_t SPI1_ReceiveByte(void)
{	uint8_t i = 0;
	  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
         
	  SPI_I2S_SendData(SPI1, 0);
          
	  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){if(i++>0xF0)break;}
          
	  return SPI_I2S_ReceiveData(SPI1);
}
void SPI1_select(void) {
	SPI1_SCS(0);		//低电平有效
}
void SPI1_deselect(void) {
	SPI1_SCS(1);
}
