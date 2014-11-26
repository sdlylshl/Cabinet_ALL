#ifndef _GPIO_HANDLER_H_
#define _GPIO_HANDLER_H_


#include "../Ethernet_Config.h"
#define  W5500_RCC_AHB_PORT	 (0|RCC_AHBPeriph_DMA1)
#define  W5500_RCC_APB1_PORT (RCC_APB1Periph_SPI2)

#define  W5500_RCC_APB2_PORT (RCC_APB2Periph_GPIOA|	\
															RCC_APB2Periph_GPIOB|	\
															RCC_APB2Periph_GPIOC|	\
															RCC_APB2Periph_GPIOE|	\
															RCC_APB2Periph_SPI1|	\
															RCC_APB2Periph_USART1|\
															RCC_APB2Periph_AFIO)


#define WIZ_RDY_PORT				GPIOD
#define WIZ_RDY_PIN					GPIO_Pin_8
#define WIZ_RDY_MODE				GPIO_Mode_IPU		
	
#define WIZ_nRST_PORT				GPIOD
#define WIZ_nRST_PIN				GPIO_Pin_9		
#define WIZ_nRST_MODE				GPIO_Mode_Out_PP

#define WIZ_SPI							SPI2
  // SPI2 PB 12 13 14 15	
#define WIZ_SCS_PORT				GPIOB
#define WIZ_SCS_PIN					GPIO_Pin_12
#define WIZ_SCS_MODE				GPIO_Mode_Out_PP
	
#define WIZ_SCLK_PORT				GPIOB
#define WIZ_SCLK_PIN				GPIO_Pin_13
#define WIZ_SCLK_MODE				GPIO_Mode_AF_PP	

#define WIZ_MISO_PORT				GPIOB
#define WIZ_MISO_PIN				GPIO_Pin_14	
#define WIZ_MISO_MODE				GPIO_Mode_AF_PP

#define WIZ_MOSI_PORT				GPIOB		
#define WIZ_MOSI_PIN				GPIO_Pin_15	
#define WIZ_MOSI_MODE				GPIO_Mode_AF_PP


#define	WIZ_nRST(x)   x ? GPIO_SetBits(WIZ_nRST_PORT,WIZ_nRST_PIN): GPIO_ResetBits(WIZ_nRST_PORT,WIZ_nRST_PIN)
#define	WIZ_SCS(x)   x ? GPIO_SetBits(WIZ_SCS_PORT,WIZ_SCS_PIN): GPIO_ResetBits(WIZ_SCS_PORT,WIZ_SCS_PIN)
													//uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
void wizchip_reset(void);
void wizchip_select(void);
void wizchip_deselect(void);
uint8_t wizchip_isreday(void);
void WIZ_GPIO_Configuration(void);

#endif
