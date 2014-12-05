#ifndef _CAN_H_
#define _CAN_H_


#include "version.h"

//CAN_REMAP[1:0]=”10”
//(2)
//CAN_REMAP[1:0]=”11”
//(3)
//复用功能(1)
//  CAN_REMAP[1:0]=”00”
//PA11  PB8  PD0  CAN1_RX 或 AN_RX 
//PA12  PB9  PD1  CAN1_TX 或 AN_TX 

#define CAN1_NVIC	1

#define CAN1_REMAP 0

#if CAN1_REMAP == 0
  // CAN1 PA 11 12	
#define CAN1_RX_PORT			GPIOA
#define CAN1_RX_PIN				GPIO_Pin_11
#define CAN1_RX_MODE			GPIO_Mode_IPU
	
#define CAN1_TX_PORT			GPIOB
#define CAN1_TX_PIN				GPIO_Pin_12
#define CAN1_TX_MODE			GPIO_Mode_AF_PP	
#endif

#if CAN1_REMAP == 1
  // CAN1 PB 8 9	
#define CAN1_RX_PORT			GPIOB
#define CAN1_RX_PIN				GPIO_Pin_8
#define CAN1_RX_MODE			GPIO_Mode_IPU
	
#define CAN1_TX_PORT			GPIOB
#define CAN1_TX_PIN				GPIO_Pin_9
#define CAN1_TX_MODE			GPIO_Mode_AF_PP	
#endif

#if CAN1_REMAP == 2
  // CAN1 PD 0 1
#define CAN1_RX_PORT			GPIOD
#define CAN1_RX_PIN				GPIO_Pin_0
#define CAN1_RX_MODE			GPIO_Mode_IPU
	
#define CAN1_TX_PORT			GPIOD
#define CAN1_TX_PIN				GPIO_Pin_1
#define CAN1_TX_MODE			GPIO_Mode_AF_PP	
#endif

#endif
