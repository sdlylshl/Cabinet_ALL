#include"LCD12864S.h"

uint8_t const Address_Table[]={
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,//��һ�к���λ��     
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,//�ڶ��к���λ��
0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,//�����к���λ��
0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,//�����к���λ��
};

//LCD12864ͬ��ʱ����1/2������ʱ,STM32F103xx��72MHz��
void LCD_CLK_Delay(void)   
{
  uint8_t i;  
  for(i=0;i<200;i++)
  {
  	__nop();
  }
}
//��LCD12864����һ���ֽڵ�����
void Send_Byte(uint8_t Temp)
{
     uint8_t i,n=0x80;
	 CS_H;
     for(i=0;i<8;i++)
     {      
			if(n&Temp)        //��λ����Ϊ1
				SID_H;
			else 		      //��λ����Ϊ0
				SID_L;
			n=n>>1;	          //n��10000000��������һλ
			CLK_H;		      //����һ��ʱ���ź����������ݱ�д��
			LCD_CLK_Delay();
			CLK_L;		   
     }
	 CS_L;
}
//����һ���ֽڵ�����
uint8_t Receive_Byte(void)
{
     uint8_t i,temp1,temp2;
     temp1 = 0;
     temp2 = 0;
     for(i=0;i<8;i++)
     {
           temp1=temp1<<1;
			CLK_H;		      //����һ��ʱ���ź����������ݱ�д��
			LCD_CLK_Delay();
			CLK_L;	
           if(SID_Read) temp1++;
     }
     for(i=0;i<8;i++)
     {
           temp2=temp2<<1;
			CLK_H;		      //����һ��ʱ���ź����������ݱ�д��
			LCD_CLK_Delay();
			CLK_L;
           if(SID_Read) temp2++;
     }
     return ((0xf0&temp1)+(0x0f&temp2));
}
//д��ʾ���� 
void Write_Data (uint8_t Data)
{	 
	Check_Busy();			//���æµ       
	Send_Byte(0xfa);        //RW=0������MCU->LCD;RS=1,��ʾ��������ʾ����		
	Send_Byte(Data&0xf0);	//���ڿ��Ƹ�ʽ[11111��RW=0)��RS��0]
	Send_Byte(Data<<4&0xf0);		
}
//д��������
void Write_Comm(uint8_t Comm)
{
	Check_Busy();			//���æµ
	Send_Byte(0xf8);        //RW=0������MCU->LCD;RS=0,��ʾ����������		
	Send_Byte(Comm&0xf0);	//���ڿ��Ƹ�ʽ[11111��RW=0)��RS��0]
	Send_Byte(Comm<<4&0xf0);	
}
//LCD12864��æ
void Check_Busy( void )
{
     do   Send_Byte(0xfc);             //11111,RW(1),RS(0),0
     while(0x80&Receive_Byte());       //BF(.7)=1 Busy
}
//LCD12864��ʼ��
void LCD_Init (void)							
{ 
	GPIO_InitTypeDef GPIO_InitStructure;				              //����ṹ�����  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	          // ʹ�ܶ˿�ʱ�ӣ���Ҫ������ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	              //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	              //50Mʱ���ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	LCD_CLK_Delay();
	LCD_CLK_Delay();
	Write_Comm(0x30);  //����ָ���8λ������    
	Write_Comm(0x01);  //��������ַָ��ָ��00H 
	Write_Comm(0x06);  //�����ƶ����� 
	Write_Comm(0x0c);  //����ʾ�����α� 
}
//LCD12864����
void LCD_Clear(void)
{
	Check_Busy();			//���æµ
	Write_Comm(0x30);  //����ָ���  
	Write_Comm(0x01);
}

//ָ��λ����ʾ�ַ�
void Display_String(uint8_t x,uint8_t y,char *s)
{ 
	if(x>8)x=8;
	if(y>3)y=3;
	Write_Comm(Address_Table[8*y+x]); //����XYд���ַ
//	Write_Comm(Address_Table[8*y+x]); //��ʱҪд����
	while(*s>0)
	{				 
		Write_Data(*s); 
		s++;
	}
}
//ͼ����ʾ122*32
void Display_Image (unsigned char *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;){		//���������ϰ������°�������Ϊ��ʼ��ַ��ͬ����Ҫ�ֿ�
	for(x=0;x<32;x++){				//32��
		Write_Comm(0x34);
		Write_Comm((0x80+x));//�е�ַ
		Write_Comm((0x80+i));	//�е�ַ���°������������е�ַ0X88
		Write_Comm(0x30);		
		for(y=0;y<16;y++)	
			Write_Data(DData[tmp+y]);//��ȡ����д��LCD
		tmp+=16;		
	}
	i+=8;
	}
	Write_Comm(0x36);	//���书���趨
	Write_Comm(0x30);
}
//��ʾ������ֵ0~9999
void Show_Num(uint8_t x,uint8_t y,uint16_t Num)
{
	if(x>8)x=8;
	if(y>3)y=3;

	if(Num==999||Num==99||Num==9)
    Display_String(x,y,"    ");

	Write_Comm(Address_Table[8*y+x]); //����XYд���ַ
//	Write_Comm(Address_Table[8*y+x]); //��ʱҪд����


	if((Num/1000))			         //ǧλ��Ϊ0����ʾǧλ
	Write_Data(0x30+Num/1000);
	//	Lcd_WriteData(0x2e);//"."
	if((Num/1000)||(Num%1000/100))       //ǧλ�Ͱ�λ��һ��>0����ʾ��λ
	Write_Data(0x30+Num%1000/100);
	//	Lcd_WriteData(0x2e);//"."
	if((Num%1000/100)||(Num%100/10))
	Write_Data(0x30+Num%100/10);
	//	Lcd_WriteData(0x2e);//"."
	if((Num%100/10)||(0x30+Num%10))
	Write_Data(0x30+Num%10);	
}

