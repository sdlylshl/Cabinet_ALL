
#include"LCD12864S.h"

/*******************��ʱ����*******************/
void delay()    
{
    u16 a,b,c;
    for(c=1600;c>0;c--)
        for(b=100;b>0;b--)
            for(a=16;a>0;a--);
}
/********************������********************/


int main(void)
{
	LCD_Init ();
	LCD_Clear();
	Display_String(0,0,"��ã�");
	Display_String(0,2,"STM32");
	while(1)
	{
	}
	//return 0;
}

/*********************************************/
