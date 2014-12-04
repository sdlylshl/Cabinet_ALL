/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "config.h"

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_it.h"

#include <stdio.h>
//#include "config.h"

#define Interrupt_DBG printf
//#define Interrupt_DBG_USARTx USART3

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__INLINE void NMI_Handle(void){}
__INLINE void HardFault_Handle(void){}
__INLINE void MemManage_Handle(void){}
__INLINE void BusFault_Handle(void){}
__INLINE void UsageFault_Handle(void){}
__INLINE void SVC_Handle(void){}
__INLINE void DebugMon_Handle(void){}
__INLINE void PendSV_Handle(void){}
//__INLINE void SysTick_Handle(void){}
	 
//__INLINE void TIM2_IRQHandle(void){}

//__INLINE void USART1_IRQHandle(void){}
//__INLINE void USART2_IRQHandle(void){}
//__INLINE void USART3_IRQHandle(void){}
__INLINE void USART1_IRQHandle(void){
	     uint8_t ch;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        ch = USART1->DR;
//        NET_buf[NET_write++] = c;
//        if (NET_write == NET_BUFFSIZE)
//            NET_write = 0;
        //TO TEST print usart1 == net out
        //Net_PutChar(c);
			  USART_SendData(USART1,  ch);
  
  //  Loop until the end of transmission
 
    }
 }
__INLINE void USART2_IRQHandle(void){}
__INLINE void USART3_IRQHandle(void){
}
	
/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    Interrupt_DBG("NMI_Handler \r\n");    while (1) {}
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    Interrupt_DBG("HardFault_Handler \r\n");	while (1) {}
    /* Go to infinite loop when Hard Fault exception occurs */

}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    Interrupt_DBG("MemManage_Handler \r\n");	while (1) {}
    /* Go to infinite loop when Memory Manage exception occurs */

}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    Interrupt_DBG("BusFault_Handler \r\n");   while (1) {}
    /* Go to infinite loop when Bus Fault exception occurs */

}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    Interrupt_DBG("UsageFault_Handler \r\n");	   while (1) {}
    /* Go to infinite loop when Usage Fault exception occurs */

}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
    Interrupt_DBG("SVC_Handler \r\n");    while (1) {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
    Interrupt_DBG("DebugMon_Handler \r\n");    while (1) {}
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
    Interrupt_DBG("PendSV_Handler \r\n");    while (1) {}
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    //Interrupt_DBG("SysTick_Handler \r\n");	while (1) {}
    SysTick_Handle();
}

/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
void WWDG_IRQHandler()
{
    Interrupt_DBG("WWDG_IRQHandler \r\n");    while (1) {}
}
void PVD_IRQHandler()
{
    Interrupt_DBG("PVD_IRQHandler \r\n");    while (1) {}
}
void TAMPER_IRQHandler()
{
    Interrupt_DBG("TAMPER_IRQHandler \r\n");    while (1) {}
}
void RTC_IRQHandler()
{
    Interrupt_DBG("RTC_IRQHandler \r\n");    while (1) {}
}
void FLASH_IRQHandler()
{
    Interrupt_DBG("FLASH_IRQHandler \r\n");    while (1) {}
}
void RCC_IRQHandler()
{
    Interrupt_DBG("RCC_IRQHandler \r\n");    while (1) {}
}
void EXTI0_IRQHandler()
{
    Interrupt_DBG("EXTI0_IRQHandler \r\n");    while (1) {}
}
void EXTI1_IRQHandler()
{
    Interrupt_DBG("EXTI1_IRQHandler \r\n");    while (1) {}
}
void EXTI2_IRQHandler()
{
    Interrupt_DBG("EXTI2_IRQHandler \r\n");    while (1) {}
}
void EXTI3_IRQHandler()
{
    Interrupt_DBG("EXTI3_IRQHandler \r\n");    while (1) {}
}
void EXTI4_IRQHandler()
{
    Interrupt_DBG("EXTI4_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel1_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel1_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel2_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel2_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel3_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel3_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel4_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel4_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel5_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel5_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel6_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel6_IRQHandler \r\n");    while (1) {}
}
void DMA1_Channel7_IRQHandler()
{
    Interrupt_DBG("DMA1_Channel7_IRQHandler \r\n");    while (1) {}
}

void ADC1_2_IRQHandler()
{
    Interrupt_DBG("ADC1_2_IRQHandler \r\n");    while (1) {}
}
void USB_HP_CAN1_TX_IRQHandler()
{
    Interrupt_DBG("USB_HP_CAN1_TX_IRQHandler \r\n");    while (1) {}
}
void USB_LP_CAN1_RX0_IRQHandler()
{
    Interrupt_DBG("USB_LP_CAN1_RX0_IRQHandler \r\n");    while (1) {}
}
void CAN1_RX1_IRQHandler()
{
    Interrupt_DBG("CAN1_RX1_IRQHandler \r\n");    while (1) {}
}
void CAN1_SCE_IRQHandler()
{
    Interrupt_DBG("CAN1_SCE_IRQHandler \r\n");    while (1) {}
}
void EXTI9_5_IRQHandler()
{
    Interrupt_DBG("EXTI9_5_IRQHandler \r\n");    while (1) {}
}
void TIM1_BRK_IRQHandler()
{
    Interrupt_DBG("TIM1_BRK_IRQHandler \r\n");    while (1) {}
}
void TIM1_UP_IRQHandler()
{
    Interrupt_DBG("TIM1_UP_IRQHandler \r\n");    while (1) {}
}
void TIM1_TRG_COM_IRQHandler()
{
    Interrupt_DBG("TIM1_TRG_COM_IRQHandler \r\n");    while (1) {}
}
void TIM1_CC_IRQHandler()
{
    Interrupt_DBG("TIM1_CC_IRQHandler \r\n");    while (1) {}
}

void TIM2_IRQHandler(void)
{
	  //Interrupt_DBG("TIM2_IRQHandler \r\n");    while (1) {}
    TIM2_IRQHandle();
}
void TIM3_IRQHandler()
{
    //Interrupt_DBG("TIM3_IRQHandler \r\n");    while (1) {}
		TIM3_IRQHandle();
}
void TIM4_IRQHandler()
{
    //Interrupt_DBG("TIM4_IRQHandler \r\n");    while (1) {}
		TIM4_IRQHandle();
}
void I2C1_EV_IRQHandler()
{
    Interrupt_DBG("I2C1_EV_IRQHandler \r\n");    while (1) {}
}
void I2C1_ER_IRQHandler()
{
    Interrupt_DBG("I2C1_ER_IRQHandler \r\n");    while (1) {}
}
void I2C2_EV_IRQHandler()
{
    Interrupt_DBG("I2C2_EV_IRQHandler \r\n");    while (1) {}
}
void I2C2_ER_IRQHandler()
{
    Interrupt_DBG("I2C2_ER_IRQHandler \r\n");    while (1) {}
}
void SPI1_IRQHandler()
{
    Interrupt_DBG("SPI1_IRQHandler \r\n");    while (1) {}
}
void SPI2_IRQHandler()
{
    Interrupt_DBG("SPI2_IRQHandler \r\n");    while (1) {}
}
//在中断服务程序中，由于主机响应中断时并不知道是哪个中断源发出中断请求，
//因此必须在中断服务程序中对中断源进行判别，然后分别进行处理。
//当然，如果只涉及到一个中断请求，是不用做上述判别的。但是无论什么情况，做上述判别是个好习惯

//usart1 === net
void USART1_IRQHandler(void)
{
  //Interrupt_DBG("USART1_IRQHandler \r\n");    while (1) {}
	USART1_IRQHandle();


}
//usart2 === zigbee
void USART2_IRQHandler(void)
{
  //Interrupt_DBG("USART2_IRQHandler \r\n");    while (1) {}  
	USART2_IRQHandle();
}

void USART3_IRQHandler(void)
{
	//Interrupt_DBG("USART3_IRQHandler \r\n");    while (1) {}
	USART3_IRQHandle();
}

void EXTI15_10_IRQHandler()
{
    Interrupt_DBG("EXTI15_10_IRQHandler \r\n");		while (1) {}
}
void RTCAlarm_IRQHandler()
{
    Interrupt_DBG("RTCAlarm_IRQHandler \r\n");    while (1) {}
}
void USBWakeUp_IRQHandler()
{
    Interrupt_DBG("USBWakeUp_IRQHandler \r\n");    while (1) {}
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
void PPP_IRQHandler(void)
{
    Interrupt_DBG("PPP_IRQHandler \r\n");		while(1){}
}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
