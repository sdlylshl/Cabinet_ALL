
#include"LCD12864S.h"

/*******************延时函数*******************/
void delay()    
{
    u16 a,b,c;
    for(c=1600;c>0;c--)
        for(b=100;b>0;b--)
            for(a=16;a>0;a--);
}
/********************主函数********************/


int main(void)
{
	LCD_Init ();
	LCD_Clear();
	Display_String(0,0,"你好！");
	Display_String(0,2,"STM32");
	while(1)
	{
	}
	//return 0;
}

/*********************************************/
