/********************************************************************************
*�ļ�����12864LCD�ײ���������
*��汾��V3.5
*MCU��STM32F103RBT6(72Mhz)
*Ӳ���ӿڣ�CS->=>LCD12864_Pin_4;   SID=>LCD12864_Pin_5��  CLKLCD12864_Pin_6
*˵������      
*���ߣ�HHH_MCU.2011.8.19
********************************************************************************/
#ifndef __LCD12864S_H
#define __LED12864S_H

#include "..\LCD12864_config.h"

/*==============================12864�ܽŶ���===========================*/
#define CS_H    GPIO_SetBits(RS_PORT, RS_PIN)     //=>LCD12864_Pin_4
#define CS_L    GPIO_ResetBits(RS_PORT, RS_PIN)

#define SID_H   GPIO_SetBits(RW_PORT, RW_PIN)        //=>LCD12864_Pin_5
#define SID_L   GPIO_ResetBits(RW_PORT, RW_PIN)

#define CLK_H   GPIO_SetBits(EN_PORT, EN_PIN)    //=>LCD12864_Pin_6
#define CLK_L   GPIO_ResetBits(EN_PORT, EN_PIN)
 
#define SID_Read    GPIO_ReadInputDataBit(BUSY_PORT,BUSY_PIN )     //������

/*================================��������==============================*/
void LCD_CLK_Delay(void);               //ʱ����1/2������ʱ
void Send_Byte(uint8_t Temp);               //����һ���ֽڵ�����
uint8_t Receive_Byte(void);                 //����һ���ֽڵ�����
void Write_Data (uint8_t Dat);                  //д��ʾ����
void Write_Comm(uint8_t Comm);                  //д��������
void LCD_Init (void);                   //��ʼ��LCD
void LCD_Clear(void);                   //����
void Check_Busy( void );                //LCD12864��æ
void Display_String(uint8_t x,uint8_t y,char *s); //ָ��λ����ʾ�ַ�
void Display_Image (uint8_t *DData);            //��ʾͼ��
void Show_Num(uint8_t x,uint8_t y,uint16_t Num);        //��ʾ������ֵ0~9999
#endif
