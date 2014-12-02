#include "stm32f10x.h"

#include "pfmBuffer.h"
//缓冲区长度
//#define TX_RX_MAX_BUF_SIZE	255
//单条指令最大长度
#define MAX_INSTRUCTION_LEN 128
extern uint8_t RX_BUF[0xFF]; // RX Buffer for applications

uint8_t recv_write;
uint8_t recv_read;

typedef struct cmd{
    uint8_t usable;
    uint8_t len;
    uint8_t data[128];
}cmd_t;

cmd_t datcmd_t[10];
void PfmBuffer_Init(void){
    recv_write = 0;
    recv_read = 0;
}

//1.获取剩余空间大小
static uint8_t PfmBuffer_getSpace(){
    if(recv_write == recv_read){
        return 0xFF;
    }else{
        return (0xFF -recv_write + recv_read+1);
    }
}
//2.获取可写空间大小 （TX_RX_MAX_BUF_SIZE-head )|(tail-head) 较小值 【一次可填充大小】
static uint8_t PfmBuffer_getUsable(){
    uint8_t space = PfmBuffer_getSpace();
    uint8_t endl;
    if(recv_write){
        endl = 0xFF-recv_write+1;
    }else{
        endl = 0xFF;
    }
    return ((space)<(endl)?(space):(endl));
}
//3.确保写操作不会造成head 跑到 tail的前面
//4.获取已用空间的大小
uint8_t PfmBuffer_Read(void)
{

    return (0xFF-recv_read+recv_write+1);
}
uint8_t PfmBuffer_Next(uint8_t size)
{
    uint8_t overdata=PfmBuffer_Read();
    //检测是否溢出
    if(overdata>size){
        recv_read = recv_read+size;
        return size;
    }else{
        recv_read = recv_read+overdata;
        return overdata;
    }

}
//4.确保读操作不会造成tail 跑到 head的前面

//5.将数据送到接收缓冲区 
uint8_t tcpc_SendBuff(uint8_t sn){
    uint16_t RSR_len;
    int32_t received_len;
    uint8_t buf_usable = PfmBuffer_getUsable();
    uint8_t stt[] = "12";
    //1.获取收到数据
    //received_len = getSn_RX_RSR(sn);
    while ((RSR_len = getSn_RX_RSR(sn)) > 0)         
    {
        printf("RSR_len: 0x%x\n", RSR_len);
        if (RSR_len > buf_usable) 
            RSR_len = buf_usable;   

        received_len = recv(sn, &RX_BUF[recv_write], RSR_len); 
        send(sn, &RX_BUF[recv_write], received_len);
        send(sn, stt, 2);
        recv_write= recv_write+RSR_len;
    }
    return 0;
}

void CRC_Enable(void)
{
    /* Enable CRC clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
}

void CRC_Disable(void){
    /* Disable CRC clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, DISABLE);

}
int8_t CRC_check(uint8_t position,uint8_t len){
    uint32_t CRCvalue;
    uint32_t CRCrecv;

    CRC_Enable();	
    CRC_ResetDR();		
    while(len--)
    {
        CRC_CalcCRC((uint32_t)(RX_BUF[position++]));
    }		
    //大端模式
    CRCrecv = (RX_BUF[position] << 24) | (RX_BUF[position+1] << 16) | (RX_BUF[position+2] << 8) | (RX_BUF[position+3]);
    //小端模式
    //CRCrecv = (RX_BUF[position+3] << 24) | (RX_BUF[position+2] << 16) | (RX_BUF[position+1] << 8) | (RX_BUF[position]);

    CRCvalue=CRC_GetCRC();
    CRC_Disable();
    if(CRCrecv  == CRCvalue)
        return 1;
    else
        return 0;

}
//6.将接收缓冲器中数据解析成单条指令 存放到cmdS[MAX_CMDS]
void ParseInstruction()
{
    uint8_t len_tmp;
    uint8_t i;
    // SendCMD(recv_write);
    // SendCMD(recv_read);
    //包头检测 若接收到的数据长度小于最小心跳包长度 则不再检测包头
    // DEBUG: NET_fetchParseInstruction
    // DEBUG(USARTn, "\r\n net parseRcvBufToLst2 \r\n");
    while (PfmBuffer_Read())
    {
        //检测包头
        if (RX_BUF[recv_read] == 0xE0 )
        {

            //包头
            if(RX_BUF[recv_read+1] == 0x55 &&RX_BUF[recv_read+2] == 0xAA){
                //取得数据长度 
                len_tmp = RX_BUF[recv_read+3];

            }
            //单条指令最大长度
            if (len_tmp < MAX_INSTRUCTION_LEN)
            {
                //接收到完整指令 recv_read+3 代表len 位置  len1+sn2+crc4+endl =8字节 endl 可忽略
                if (PfmBuffer_Read() >= len_tmp + 8)
                {


                    //CRC校验 包含包头0xE0 0x55 0xAA +len + data +crc
                    if(CRC_check(recv_read,len_tmp+4)){
                        //memcpy();
                        //1.获取指令表
                        datcmd_t[0].len = len_tmp;
                        //2.数据复制
                        for(i=0;i<len_tmp;i++){
                            datcmd_t[0].data[i]= RX_BUF[recv_read+i+4];
                        }
                        datcmd_t[0].usable = 1;
                    }
                    //移到下一条指令	
                    PfmBuffer_Next(len_tmp+8);

                }else{
                    //未接收到完整数据
                    break;
                }
            }else{
                recv_read++;
            }

        }else{
            recv_read++;
        }

    }//end while
}
