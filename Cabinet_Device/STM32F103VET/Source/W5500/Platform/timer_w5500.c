#include "../Ethernet.h"
uint8_t IsTimeElapsed = 0;
uint16_t TimerCount = 0;
uint16_t ResetTimeCounter = 0;

//TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;



void Timer_Configuration(void)
{
	
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
		//中断配置
    //TIM2_NVIC_Configuration();
	
    TIM_DeInit(TIM2);
	
    TIM_TimeBaseStructure.TIM_Period = 1000;
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_Cmd(TIM2, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);      /*先关闭等待使用*/

	
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_PrescalerConfig(TIM2, 47, TIM_PSCReloadMode_Immediate);//定时器时间间隔为 
	
	TIM_Cmd(TIM2, ENABLE);
	
	//开启中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}


__INLINE void TIM2_IRQHandle(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		if(TimerCount++ >= 1000)
		{
			TimerCount = 0;
			IsTimeElapsed = 1;
		}
		
		if(ResetTimeCounter++ < 100)
			;
	}
}


uint8_t GetIsTimeElapsed(void)
{
	return IsTimeElapsed;
}

void SetIsTimeElapsed(uint8_t flag)
{
	IsTimeElapsed = flag;
}

uint16_t GetResetTimeCounter(void)
{
	return ResetTimeCounter;
}

void SetResetTimeCounter(uint16_t count)
{
	ResetTimeCounter = count;
}
