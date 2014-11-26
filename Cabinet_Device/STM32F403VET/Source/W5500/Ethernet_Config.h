#ifndef __COMMON_H_
#define __COMMON_H_
// π”√StdPeriph_Driverø‚
//#define USE_STDPERIPH_DRIVER 1

//#include "stdint.h"

//#include "stm32f10x.h"
#include "stm32f4xx.h"

#include "Ethernet\socket.h"
#include "Ethernet\W5500\w5500.h"
#include "Ethernet\wizchip_conf.h"
//extern void printf();
#include "Application\loopback.h"

#include "PlatformHandler\rcc_handler.h"
#include "PlatformHandler\gpio_handler.h"
#include "PlatformHandler\timer_handler.h"
#include "PlatformHandler\uart_handler.h"
#include "PlatformHandler\spi_handler.h"
#include "PlatformHandler\dma_handler.h"
//extern void RCC_Configuration();
//extern void GPIO_Configuration();
//extern void Timer_Configuration();
//extern void DMA_Configuration();
//extern void SPI_Configuration();
//extern void USART_Configuration();


#define DATA_BUF_SIZE   1024

#endif
