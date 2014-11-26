#include "usart1.h"

//DMA Buff
uint8_t USART1_SendBuff[USART1_SENDBUFF_SIZE];

static void USART1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    //USART1_REMAP = 0 USART1_REMAP = 1 
    //USART1_TX PA9     PB6 
    //USART1_RX PA10     PB7   
#if   USART1_REMAP  
    RCC_APB2PeriphClockCmd(|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#endif  

    // Configure USART1 Tx (PA.9 PB.6)
    GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = USART1_TX_MODE;  //  GPIO_Mode_AF_PP      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
    // Configure USART1 Rx (PA.10 PB.7)
    GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;  
    GPIO_InitStructure.GPIO_Mode = USART1_RX_MODE;  //GPIO_Mode_IN_FLOATING      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);  


}
static void USART1_NVIC_Config(void)
{
    /* Configure the NVIC Preemption Priority Bits */
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		//NVIC_SetPriorityGrouping(0);
    /* Enable the USARTy Interrupt */

//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
		NVIC_SetPriority(USART1_IRQn,3);
		NVIC_EnableIRQ(USART1_IRQn);

}
void USART1_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

    USART1_GPIO_Config();
    /* USART1 mode config */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
#if USART1_NVIC
    //使能USART1接收中断
    USART1_NVIC_Config();
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
#endif
    //
    USART_Cmd(USART1, ENABLE);

    USART_ClearFlag(USART1, USART_FLAG_TC);
}



static void USART1_DMA_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* 配置P[A|B|C|D|E]0为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
void USART1_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //开启DMA时钟
    USART1_DMA_NVIC_Config();           //配置DMA中断

    /*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;

    /*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_SendBuff;

    /*方向：从内存到外设*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;

    /*传输大小DMA_BufferSize=SENDBUFF_SIZE*/
    DMA_InitStructure.DMA_BufferSize = USART1_SENDBUFF_SIZE;

    /*外设地址不增*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    /*外设数据单位*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

    /*DMA模式：一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;

    /*优先级：中*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*禁止内存到内存的传输  */
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    /*配置DMA1的4通道*/
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    DMA_Cmd (DMA1_Channel4,ENABLE);          //使能DMA
    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断

}


/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
//int fputc(int ch, FILE *f)
//{
//    /* 将Printf内容发往串口 */
//    USART_SendData(USART1, (unsigned char) ch);
//    while (!(USART1->SR & USART_FLAG_TXE));

//    return (ch);
//}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART3_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * 函数名：USART3_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口0，即USART1
 *         -Data   要发送到串口的内容的指针
 *         -...    其他参数
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 *         典型应用USART3_printf( USART3, "\r\n this is a demo \r\n" );
 *                 USART3_printf( USART3, "\r\n %d \r\n", i );
 *                 USART3_printf( USART3, "\r\n %s \r\n", j );
 */
void USART1_printf(char *Data,...)
{
    const char *s;
    int d;
    char buf[36];

    va_list ap;
    va_start(ap, Data);

    while ( *Data != 0)     // 判断是否到达字符串结束符
    {
        if ( *Data == 0x5c )  //'\'
        {
            switch ( *++Data )
            {
                case 'r':                        //回车符
                    USART_SendData(USART1, 0x0d);
                    Data ++;
                    break;

                case 'n':                        //换行符
                    USART_SendData(USART1, 0x0a);
                    Data ++;
                    break;

                default:
                    Data ++;
                    break;
            }
        }
        else if ( *Data == '%')
        {
            //
            switch ( *++Data )
            {
                case 's':                      //字符串
                    s = va_arg(ap, const char *);
                    for ( ; *s; s++)
                    {
                        USART_SendData(USART1,*s);
                        while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
                    }
                    Data++;
                    break;

                case 'd':                    //十进制
                    d = va_arg(ap, int);
                    itoa(d, buf, 10);
                    for (s = buf; *s; s++)
                    {
                        USART_SendData(USART1,*s);
                        while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
                    }
                    Data++;
                    break;
                default:
                    Data++;
                    break;
            }
        } /* end of else if */
        else USART_SendData(USART1, *Data++);
        while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );

    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
