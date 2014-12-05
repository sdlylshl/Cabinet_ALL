
#include "gpio_w5500.h"
//Delay_ms();
#include "./System/System_config.h"

/*
 typedef enum
{ GPIO_Mode_AIN = 0x0,					//ģ������
  GPIO_Mode_IN_FLOATING = 0x04, //��������
  GPIO_Mode_IPD = 0x28,					//��������
  GPIO_Mode_IPU = 0x48,					//��������
  GPIO_Mode_Out_OD = 0x14,			//��©���
  GPIO_Mode_Out_PP = 0x10,			//�������
  GPIO_Mode_AF_OD = 0x1C,				//��©�������
  GPIO_Mode_AF_PP = 0x18				//���츴�����
}GPIOMode_TypeDef;
 
 typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
 */


void WIZ_GPIO_Configuration(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
	
	
				/*����GPIOC������ʱ��*/
					RCC_AHBPeriphClockCmd (	W5500_RCC_AHB_PORT , ENABLE);	
					RCC_APB1PeriphClockCmd(	W5500_RCC_APB1_PORT, ENABLE);
					RCC_APB2PeriphClockCmd( W5500_RCC_APB2_PORT, ENABLE);
	
	
        GPIO_InitStructure.GPIO_Pin = WIZ_RDY_PIN;
        GPIO_InitStructure.GPIO_Mode = WIZ_RDY_MODE;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(WIZ_RDY_PORT, &GPIO_InitStructure);
	
        GPIO_InitStructure.GPIO_Pin = WIZ_nRST_PIN;
        GPIO_InitStructure.GPIO_Mode = WIZ_nRST_MODE;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(WIZ_nRST_PORT, &GPIO_InitStructure);

}
