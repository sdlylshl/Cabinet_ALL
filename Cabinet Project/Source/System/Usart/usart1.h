#ifndef __USART1_H
#define	__USART1_H

#include "..\System_config.h"

#include <stdio.h>
#include <stdarg.h>
//USART1
#define USART1_NVIC			1
//#define USART1_DMA			0
#define USART1_REMAP		0

#if USART1_REMAP
// USART1_REMAP = 1 
//USART1_TX PB6 
#define USART1_TX_PORT			GPIOB			
#define USART1_TX_PIN				GPIO_Pin_6	
#define USART1_TX_MODE			GPIO_Mode_AF_PP	
//USART1_RX PB7 
#define USART1_RX_PORT			GPIOB			
#define USART1_RX_PIN				GPIO_Pin_7				
#define USART1_RX_MODE			GPIO_Mode_IN_FLOATING	

#else					//default	
//USART1_REMAP = 0
//USART1_TX PA9
#define USART1_TX_PORT			GPIOA			
#define USART1_TX_PIN				GPIO_Pin_9	
#define USART1_TX_MODE			GPIO_Mode_AF_PP	

//USART1_RX PA10
#define USART1_RX_PORT			GPIOA			
#define USART1_RX_PIN				GPIO_Pin_10				
#define USART1_RX_MODE			GPIO_Mode_IN_FLOATING	
#endif

//DMA Mode
#define USART1_DR_Base  0x40013804
#define USART1_SENDBUFF_SIZE 1000
//DMA Buff
extern uint8_t USART1_SendBuff[USART1_SENDBUFF_SIZE];

extern void USART1_Config(void);
extern void USART1_printf(char *Data,...);

#endif /* __USART1_H */
