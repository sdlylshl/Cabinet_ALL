#include "LCD12864_config.h"
void LCD12864P_InitPort(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//����ṹ��		
	
	RCC_APB2PeriphClockCmd(LCD12864_RCC_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = LCD12864_DAT_PIN;		//���ݿ����óɿ�©���ģʽ����ģʽ�¶�����Ĵ�����ֵ�õ�IO��״̬
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  
	GPIO_Init(LCD12864_DAT_PORT , &GPIO_InitStructure);    //IO�ڳ�ʼ������

	GPIO_InitStructure.GPIO_Pin  = RS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(RS_PORT , &GPIO_InitStructure);
	GPIO_SetBits(RS_PORT,RS_PIN);
	GPIO_ResetBits(RS_PORT,RS_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = RW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(RW_PORT , &GPIO_InitStructure); 
	GPIO_SetBits(RW_PORT,RW_PIN);
	GPIO_ResetBits(RW_PORT,RW_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(EN_PORT , &GPIO_InitStructure); 
	GPIO_SetBits(EN_PORT,EN_PIN);
	GPIO_ResetBits(EN_PORT,EN_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = PSB_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(PSB_PORT , &GPIO_InitStructure); 
	GPIO_SetBits(PSB_PORT,PSB_PIN);
	GPIO_ResetBits(PSB_PORT,PSB_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(RST_PORT , &GPIO_InitStructure);
	GPIO_SetBits(RST_PORT,RST_PIN);
	GPIO_ResetBits(RST_PORT,RST_PIN);
	
//	GPIO_Init(LCD12864_GPIO , &GPIO_InitStructure);	  //��ʼ��IO������
	GPIO_Write(LCD12864_DAT_PORT ,0xff00);
	LCD_WriteData(0);	
}
void LCD12864S_InitPort(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//����ṹ��		
	
	RCC_APB2PeriphClockCmd(LCD12864_RCC_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = LCD12864_DAT_PIN;		//���ݿ����óɿ�©���ģʽ����ģʽ�¶�����Ĵ�����ֵ�õ�IO��״̬
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  
	GPIO_Init(LCD12864_DAT_PORT , &GPIO_InitStructure);    //IO�ڳ�ʼ������

	GPIO_InitStructure.GPIO_Pin  = RS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(RS_PORT , &GPIO_InitStructure);
	GPIO_SetBits(RS_PORT,RS_PIN);
	GPIO_ResetBits(RS_PORT,RS_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = RW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(RW_PORT , &GPIO_InitStructure); 
	GPIO_SetBits(RW_PORT,RW_PIN);
	GPIO_ResetBits(RW_PORT,RW_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(EN_PORT , &GPIO_InitStructure); 
	GPIO_SetBits(EN_PORT,EN_PIN);
	GPIO_ResetBits(EN_PORT,EN_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = PSB_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(PSB_PORT , &GPIO_InitStructure); 
	GPIO_SetBits(PSB_PORT,PSB_PIN);
	GPIO_ResetBits(PSB_PORT,PSB_PIN);
	
	GPIO_InitStructure.GPIO_Pin  = RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(RST_PORT , &GPIO_InitStructure);
	GPIO_SetBits(RST_PORT,RST_PIN);
	GPIO_ResetBits(RST_PORT,RST_PIN);
	
//	GPIO_Init(LCD12864_GPIO , &GPIO_InitStructure);	  //��ʼ��IO������
	GPIO_Write(LCD12864_DAT_PORT ,0xff00);
	LCD_WriteData(0);	
}
