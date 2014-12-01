#include "in.h"

/*
 * 函数名：SENSOR_GPIO_Config
 * 描述  ：配置SENSOR用到的I/O口
 * 输入  ：无
 * 输出  ：无
 
 typedef enum
{ GPIO_Mode_AIN = 0x0,					//模拟输入
  GPIO_Mode_IN_FLOATING = 0x04, //浮空输入
  GPIO_Mode_IPD = 0x28,					//下拉输入
  GPIO_Mode_IPU = 0x48,					//上拉输入
  GPIO_Mode_Out_OD = 0x14,			//开漏输出
  GPIO_Mode_Out_PP = 0x10,			//推挽输出
  GPIO_Mode_AF_OD = 0x1C,				//开漏复用输出
  GPIO_Mode_AF_PP = 0x18				//推挽复用输出
}GPIOMode_TypeDef;
 
 typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
 */
 
 
void SENSOR_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//定义结构体		
	
	RCC_APB2PeriphClockCmd(SENSOR_RCC_PORT, ENABLE);
	#if SENSOR1_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR1_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR1_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR1_PORT , &GPIO_InitStructure);
	//SENSOR1(1);
	#endif
	#if SENSOR2_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR2_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR2_MODE;  //开漏输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR2_PORT , &GPIO_InitStructure);
	//SENSOR2(1);
		#endif
	#if SENSOR3_USE	
	GPIO_InitStructure.GPIO_Pin  = SENSOR3_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR3_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR3_PORT , &GPIO_InitStructure);
	SENSOR3(1);
		#endif
	#if SENSOR4_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR4_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR4_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR4_PORT , &GPIO_InitStructure);
	//SENSOR4(1);
		#endif
	#if SENSOR5_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR5_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR5_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR5_PORT , &GPIO_InitStructure);
	//SENSOR5(1);
		#endif
	#if SENSOR6_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR6_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR6_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR6_PORT , &GPIO_InitStructure);
	//SENSOR6(1);	
		#endif
	#if SENSOR7_USE	
	GPIO_InitStructure.GPIO_Pin  = SENSOR7_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR7_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR7_PORT , &GPIO_InitStructure);
	//SENSOR7(1);
		#endif
	#if SENSOR8_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR8_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR8_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR8_PORT , &GPIO_InitStructure);
	//SENSOR8(1);	
	#endif
	#if SENSOR9_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR9_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR9_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR9_PORT , &GPIO_InitStructure);
	//SENSOR9(1);
	#endif
	#if SENSOR10_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR10_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR10_MODE;  //开漏输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR10_PORT , &GPIO_InitStructure);
	//SENSOR10(1);
		#endif
	#if SENSOR11_USE	
	GPIO_InitStructure.GPIO_Pin  = SENSOR11_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR11_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR11_PORT , &GPIO_InitStructure);
	//SENSOR11(1);
		#endif
	#if SENSOR12_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR12_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR12_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR12_PORT , &GPIO_InitStructure);
	//SENSOR4(1);
		#endif
	#if SENSOR13_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR13_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR13_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR13_PORT , &GPIO_InitStructure);
	//SENSOR5(1);
		#endif
	#if SENSOR14_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR14_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR14_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR14_PORT , &GPIO_InitStructure);
	//SENSOR14(1);	
		#endif
	#if SENSOR15_USE	
	GPIO_InitStructure.GPIO_Pin  = SENSOR15_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR15_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR15_PORT , &GPIO_InitStructure);
	//SENSOR15(1);
		#endif
	#if SENSOR16_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR16_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR16_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR16_PORT , &GPIO_InitStructure);
	//SENSOR16(1);	
	#endif
	#if SENSOR17_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR17_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR17_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR17_PORT , &GPIO_InitStructure);
	//SENSOR17(1);
	#endif
	#if SENSOR18_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR18_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR18_MODE;  //开漏输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR18_PORT , &GPIO_InitStructure);
	//SENSOR18(1);
		#endif
	#if SENSOR19_USE	
	GPIO_InitStructure.GPIO_Pin  = SENSOR19_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR19_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR19_PORT , &GPIO_InitStructure);
	//SENSOR19(1);
		#endif
	#if SENSOR20_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR20_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR20_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR20_PORT , &GPIO_InitStructure);
	//SENSOR20(1);
		#endif
	#if SENSOR21_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR21_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR21_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR21_PORT , &GPIO_InitStructure);
	//SENSOR21(1);
		#endif
	#if SENSOR22_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR22_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR22_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR22_PORT , &GPIO_InitStructure);
	//SENSOR22(1);	
		#endif
	#if SENSOR23_USE	
	GPIO_InitStructure.GPIO_Pin  = SENSOR23_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR23_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR23_PORT , &GPIO_InitStructure);
	//SENSOR23(1);
		#endif
	#if SENSOR24_USE
	GPIO_InitStructure.GPIO_Pin  = SENSOR24_PIN;
	GPIO_InitStructure.GPIO_Mode = SENSOR24_MODE;  //推挽输出   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SENSOR24_PORT , &GPIO_InitStructure);
	//SENSOR24(1);	
	#endif
}

uint8_t isSENSOR2LOW(){
		return (!GPIO_ReadInputDataBit(SENSOR2_PORT, SENSOR2_PIN));
	

}
uint8_t isSENSOR15LOW(){
		return (!GPIO_ReadInputDataBit(SENSOR15_PORT, SENSOR15_PIN));
	

}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
