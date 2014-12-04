
#include "..\Ethernet.h"
//定义一个指令表
typedef struct cntdat
{
    uint8_t id;     //控制器id
    uint8_t channel;//第几路 最大支持24路
} cntdat_t;
uint8_t cntdata[][];

void ParseData()
{
    cntdat_t *pcntdat = getcntdata();
    //1.判断id是否一致
    //2.执行

    if (i = 0; i < 10; i++)
    {

    }
}

}
