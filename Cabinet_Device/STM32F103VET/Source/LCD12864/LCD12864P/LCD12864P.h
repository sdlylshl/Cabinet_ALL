#ifndef __LCD12864P_H_
#define __LCD12864P_H_	

#include "..\LCD12864_config.h"


void LCD12864_InitPort(void);	  //Ӳ���˿ڳ�ʼ��
void NOP(void);					 //��ʱ����
u8 LCD12864_busy(void);			 //���æ״̬
void LCD12684_Wcmd(u8 dat);		 //дָ��
void LCD12684_Wdat(u8 dat);		 //д����
void LCD12864_Init(void);		 //Һ����ʼ��
void LCD12864_Clr(void);		 //	����
void LCD12864_Pos(u8 x,u8 y);	 //������ʾλ��
void LCD12864_PhotoDis(u8 *bmp); //	��ʾͼƬ
void LCD_ShowStringXY(u8 x,u8 y,char *p);	 //	��ʾ�ַ���
void LCD_ShowString(u8 *p);
void LCD_ShowChar(u8 p); 
//**********************************************************************************************************************
#endif	



