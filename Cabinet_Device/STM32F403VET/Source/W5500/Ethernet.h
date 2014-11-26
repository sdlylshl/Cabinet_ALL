/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    18-January-2013
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ETHERNET_H
#define __ETHERNET_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
#include "Ethernet_Config.h"

#if 0
#if defined (USE_STM324xG_EVAL)
  #include "stm324xg_eval.h"
  #include "stm324xg_eval_lcd.h"

#elif defined (USE_STM324x7I_EVAL) 
  #include "stm324x7i_eval.h"
  #include "stm324x7i_eval_lcd.h"

#else
 #error "Please select first the Evaluation board used in your application (in Project Options)"
#endif
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define WIZ_RDY_PORT				GPIOA			//in

#define WIZ_SCLK_PORT				GPIOA			//out
#define WIZ_MISO_PORT				GPIOA			//in
#define WIZ_MOSI_PORT				GPIOA			//out


#define WIZ_SCS_PORT				GPIOA			//out
#define WIZ_nRST_PORT				GPIOA			//out

/* Port A */
#define WIZ_RDY				GPIO_Pin_1			//in

#define WIZ_SCLK			GPIO_Pin_5			//out
#define WIZ_MISO			GPIO_Pin_6			//in
#define WIZ_MOSI			GPIO_Pin_7			//out


#define WIZ_SCS				GPIO_Pin_12			//out
#define WIZ_nRST			GPIO_Pin_11			//out


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);

void  wizchip_select(void);
void  wizchip_deselect(void);
uint8_t wizchip_read(void);
void  wizchip_write(uint8_t wb);


#endif /* __ETHERNET_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
