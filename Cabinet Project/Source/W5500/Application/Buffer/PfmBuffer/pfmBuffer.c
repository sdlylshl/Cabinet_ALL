
#include <stdio.h>

#include "pfmBuffer.h"

#include "./W5500/Ethernet_config.h"

//CRC_Enable();
#include "./System/System_config.h"


//����������
//#define TX_RX_MAX_BUF_SIZE	255
//����ָ����󳤶�
#define MAX_INSTRUCTION_LEN 128

extern uint8_t RX_BUF[0xFF]; // RX Buffer for applications
uint32_t DEVICE_ID_CRC;
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

//1.��ȡʣ��ռ��С
static uint8_t PfmBuffer_getSpace(){
	if (recv_write == recv_read){
		return 0xFF;
	}
	else{
		return (0xFF - recv_write + recv_read + 1);
	}
}
//2.��ȡ��д�ռ��С ��TX_RX_MAX_BUF_SIZE-head )|(tail-head) ��Сֵ ��һ�ο�����С��
uint8_t PfmBuffer_getUsable(){
	uint8_t space = PfmBuffer_getSpace();
	uint8_t endl;
	if (recv_write){
		endl = 0xFF - recv_write + 1;
	}
	else{
		endl = 0xFF;
	}
	return ((space) < (endl) ? (space) : (endl));
}
//3.ȷ��д�����������head �ܵ� tail��ǰ��
//4.��ȡ���ÿռ�Ĵ�С
uint8_t PfmBuffer_Read(void)
{

	return (0xFF - recv_read + recv_write + 1);
}
uint8_t PfmBuffer_Next(uint8_t size)
{
	uint8_t overdata = PfmBuffer_Read();
	//����Ƿ����
	if (overdata > size){
		recv_read = recv_read + size;
		return size;
	}
	else{
		recv_read = recv_read + overdata;
		return overdata;
	}

}
//4.ȷ���������������tail �ܵ� head��ǰ��


//5.�������͵����ջ����� 
uint8_t tcpc_RevcDatToBuff(uint8_t sn){
	uint16_t RSR_len;
	int32_t received_len;
	uint8_t buf_usable = PfmBuffer_getUsable();
	uint8_t stt[] = "12";
	//1.��ȡ�յ�����
	//received_len = getSn_RX_RSR(sn);
	while ((RSR_len = getSn_RX_RSR(sn)) > 0)
	{
		printf("RSR_len: 0x%x\n", RSR_len);
		if (RSR_len > buf_usable)
			RSR_len = buf_usable;

		received_len = recv(sn, &RX_BUF[recv_write], RSR_len);
		send(sn, &RX_BUF[recv_write], received_len);
		send(sn, stt, 2);
		recv_write = recv_write + RSR_len;
	}
	return 0;
}

int8_t CRC_check(uint8_t position, uint8_t len){
	uint32_t CRCvalue;
	uint32_t CRCrecv;

	CRC_Enable();
	CRC_ResetDR();
	while (len--)
	{
		CRC_CalcCRC((uint32_t)(RX_BUF[position++]));
	}
	//���ģʽ
	CRCrecv = (RX_BUF[position] << 24) | (RX_BUF[position + 1] << 16) | (RX_BUF[position + 2] << 8) | (RX_BUF[position + 3]);
	//С��ģʽ
	//CRCrecv = (RX_BUF[position+3] << 24) | (RX_BUF[position+2] << 16) | (RX_BUF[position+1] << 8) | (RX_BUF[position]);

	CRCvalue = CRC_GetCRC();
	CRC_Disable();
	if (CRCrecv == CRCvalue)
		return 1;
	else
		return 0;

}
//6.�����ջ����������ݽ����ɵ���ָ�� ��ŵ�cmdS[MAX_CMDS]
void ParseInstruction()
{
	uint8_t len_tmp;
	uint8_t i;
	// SendCMD(recv_write);
	// SendCMD(recv_read);
	//��ͷ��� �����յ������ݳ���С����С���������� ���ټ���ͷ
	// DEBUG: NET_fetchParseInstruction
	// DEBUG(USARTn, "\r\n net parseRcvBufToLst2 \r\n");
	while (PfmBuffer_Read())
	{
		//����ͷ
		if (RX_BUF[recv_read] == 0xE0)
		{

			//��ͷ
			if (RX_BUF[recv_read + 1] == 0x55 && RX_BUF[recv_read + 2] == 0xAA){
				//ȡ�����ݳ��� 
				len_tmp = RX_BUF[recv_read + 3];

			}else{
			recv_read++;
		}
			//����ָ����󳤶�
			if (len_tmp < MAX_INSTRUCTION_LEN)
			{
				//���յ�����ָ�� recv_read+3 ����len λ��  len1+sn2+crc4+endl =8�ֽ� endl �ɺ���
				if (PfmBuffer_Read() >= len_tmp + 8)
				{


					//CRCУ�� ������ͷ0xE0 0x55 0xAA +len + data +crc
					//if (CRC_check(recv_read, len_tmp + 4)){
						if(true){
#ifdef CABINET_DEVICE 
						//data
						//if (DEVICE_ID_CRC == RX_BUF[recv_read + 5])
						if (true)
						{
							//����
							Locker_open(RX_BUF[recv_read + 8]-0x30);
						}
						else{
							//ERRO1���豸����

						}
#endif // CABINET_DEVICE 


						//memcpy();
						//1.��ȡָ���
						datcmd_t[0].len = len_tmp;
						//2.���ݸ���
						for (i = 0; i < len_tmp; i++){
							datcmd_t[0].data[i] = RX_BUF[recv_read + i + 4];
						}
						datcmd_t[0].usable = 1;
					}
					else{
						//ERRO2�����ݽ���ʧ��	��Ӧʧ����Ϣ

					}
					//�Ƶ���һ��ָ��	
					PfmBuffer_Next(len_tmp + 8);

				}
				else{
					//δ���յ���������
					break;
				}
			}
			else{
				recv_read++;
			}

		}
		else{
			recv_read++;
		}

	}//end while
}
