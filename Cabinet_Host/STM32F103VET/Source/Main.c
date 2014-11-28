#include "config.h"
char * str = "\r\n This is a USART1_printf demo \r\n";
int main(){

    uint32_t Time = 0;
    //RCC_Config();
    NVIC_Config();
    //DMA_Config();
    //LCD12864P_main();
    LED_GPIO_Config();

    TIM1_Config();
    TIM2_Config();
    TIM3_Config();
    TIM4_Config();
    TIM2_Start();
    TIM3_Start();
    TIM4_Start();

    USART1_Config();
    Ethernet_Init();	
    //Ethernet_main();
    printf("%slist",str);

    while(1){
        loopback_tcpc(1);
        Time = time4;
        printf("Time1 :%x \r\n",Time);	
        //Delay_ms(1000);
        Time = time4;
        printf("Time2 :%x \r\n",Time);		
        LED8(ON);LED7(ON);LED6(ON);
        Time = time4;
        printf("Time2 :%x \r\n",Time);	
        //Delay_ms(1000);
        LED8(OFF);LED7(OFF);LED6(OFF);
        printf("%s",str);
        ParseInstruction();	
        //PfmBuffer_Next(PfmBuffer_Read());
    }	
    //return 0;
}


#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif
