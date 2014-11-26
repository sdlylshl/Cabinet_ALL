#ifndef __COMMON_H_
#define __COMMON_H_
// π”√StdPeriph_Driverø‚
//#define USE_STDPERIPH_DRIVER 1

//#include "stdint.h"

#include "stm32f10x.h"
//#include "stm32f4xx.h"
#include "../System/System_config.h"
#include "Ethernet.h"
#include "Ethernet\socket.h"
#include "Ethernet\W5500\w5500.h"
#include "Ethernet\wizchip_conf.h"
//extern void printf();
#include "Application\loopback_server.h"
#include "Application\loopback_client.h"
//#include "Platform\rcc_handler.h"
#include "Platform\gpio_w5500.h"
//#include "Platform\timer_w5500.h"
//#include "Platform\uart_w5500.h"
#include "Platform\spi_w5500.h"
#include "Platform\dma_w5500.h"
//extern void RCC_Configuration();
//extern void GPIO_Configuration();
//extern void Timer_Configuration();
//extern void DMA_Configuration();
//extern void SPI_Configuration();
//extern void USART_Configuration();


#define DATA_BUF_SIZE   1024

#endif
