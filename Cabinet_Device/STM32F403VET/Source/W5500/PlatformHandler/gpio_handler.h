#ifndef _GPIO_HANDLER_H_
#define _GPIO_HANDLER_H_

#define USART1_TX_PORT			GPIOA			//out
#define USART1_RX_PORT			GPIOA			//in

#define USART1_TX			GPIO_Pin_9			//out
#define USART1_RX			GPIO_Pin_10			//in

void GPIO_Configuration(void);

#endif
