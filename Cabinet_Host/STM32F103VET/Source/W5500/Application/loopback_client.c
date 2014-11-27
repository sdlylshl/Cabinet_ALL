#include "stm32f10x.h"

#include "loopback_client.h"

#define tick_second 100

uint32_t my_time;
uint32_t presentTime;
uint32_t keep_alive_time;
uint32_t cruise_interval;
uint32_t received_len;


uint32_t time_return(void)
{
  return TIM4_GetCurrentTime();
}

// SRAM address range is 0x2000 0000 ~ 0x2000 4FFF (20KB)
#define TX_RX_MAX_BUF_SIZE	300

extern uint8_t TX_BUF[TX_RX_MAX_BUF_SIZE]; // TX Buffer for applications
extern uint8_t RX_BUF[TX_RX_MAX_BUF_SIZE]; // RX Buffer for applications

//1.��ȡʣ��ռ��С

//2.��ȡ��д�ռ��С ��TX_RX_MAX_BUF_SIZE-head )|(tail-head) ��Сֵ ��һ�ο�����С��

//3.ȷ��д�����������head �ܵ� tail��ǰ��

//4.ȷ���������������tail �ܵ� head��ǰ��




unsigned char calcfcs(unsigned char *pmsg, unsigned char len)
{
	unsigned char result = 0;
	while (len--)
	{
		result ^= *pmsg++;
	}
	return result;
}

uint8_t Dest_IP[4] = {192, 168, 88, 94}; //DST_IP Address 
uint16_t Dest_PORT = 51388; //DST_IP port

#define	MAX_SOCK_NUM		8	/**< Maxmium number of socket */
//socket״̬��
extern uint8_t ch_status[MAX_SOCK_NUM] ;	/** 0:close, 1:ready, 2:connected 3:init*/
uint16_t any_port=1000;

void loopback_tcpc(uint8_t s)
{
	uint16_t RSR_len;
	uint8_t * data_buf = TX_BUF;

	

	uint8_t res = getSn_SR(s);
	switch (res)
	{
		//Socket n������״̬���ڴ�״̬�£�����ʹ�� SEND ���� RECV ����������ݰ����䡣
	case SOCK_ESTABLISHED:                 /* if connection is established */
		//printf("SOCK_ESTABLISHED\n");
		if(time_return() - presentTime >= (tick_second * 2)) 
		{  
			presentTime = time_return();
			//printf("SOCK_ESTABLISHED\n");
		}
		if(ch_status[s] == 1 || ch_status[s] == 4)
		{
			 printf("\r\n%d : Connected",s);
			 ch_status[s] = 2;
		}

		#if 0
		if ((RSR_len = getSn_RX_RSR(s)) > 0)         
		{
			printf("RSR_len: 0x%x\n", RSR_len);
			 if (RSR_len > TX_RX_MAX_BUF_SIZE) 
			 	RSR_len = TX_RX_MAX_BUF_SIZE;   
			                                                                   
			 received_len = recv(s, data_buf, RSR_len); 
			 send(s, data_buf, received_len);
		}
		#endif

	 tcpc_SendBuff(s);
		//do_tcp_alive(s, mode);
		//cruise_io(s, mode);
		//recv_loop(s, mode);

		break;
		//4.Socket n ���յ����������ӶԷ������ĶϿ���������
		//��Ҫȫ���رգ���Ҫʹ�� DISCON ���
		//Ҫ�ر�Socket����Ҫʹ�� CLOSE��� 
	case SOCK_CLOSE_WAIT:  
		if(time_return() - presentTime >= (tick_second * 2)) 
		{  
			presentTime = time_return();
			printf("SOCK_CLOSE_WAIT\n");
		}
		/* If the client request to close */
		//printf("\r\n%d : CLOSE_WAIT", s);
		if ((RSR_len = getSn_RX_RSR(s)) > 0)         /* check Rx data */
		{
			 if (RSR_len > TX_RX_MAX_BUF_SIZE) RSR_len = TX_RX_MAX_BUF_SIZE;   /* if Rx data size is lager than TX_RX_MAX_BUF_SIZE */
			                                                                            /* the data size to read is MAX_BUF_SIZE. */
			 recv(s, data_buf, RSR_len);         /* read the received data */
		}
		disconnect(s);
		ch_status[s] = 0;
		break;
		//0. Socket n���ڹر�״̬����Դ���ͷ�
	case SOCK_CLOSED: 
		//printf("SOCK_CLOSED\n");
		if(time_return() - presentTime >= (tick_second * 2)) 
		{  
			presentTime = time_return();
			printf("SOCK_CLOSED\n");
		}
		/* if a socket is closed */
		if(!ch_status[s])
		{
			 printf("\r\n%d : Loop-Back TCP Client Started. port: %d", s, Dest_PORT);
			 ch_status[s] = 1;
		}
		if(socket(s, Sn_MR_TCP, any_port++, 0x00) == 0)    /* reinitialize the socket */
		{
			 printf("\a%d : Fail to create socket.",s);
			 ch_status[s] = 0;
		}
		break;
		//1. 0x13  SOCK_INIT ��λָʾ�� Socket n �˿ڴ򿪲����� TCP����ģʽ��
	case SOCK_INIT:     /* if a socket is initiated */
		//printf("SOCK_INIT\n");
		if(ch_status[s] == 2)
			ch_status[s] = 4;
		if(time_return() - presentTime >= (tick_second * 2)) 
		{  
			connect(s, Dest_IP, Dest_PORT);
			presentTime = time_return();
			printf("SOCK_INIT\n");
		}
		break;
	default:
		if(time_return() - presentTime >= (tick_second * 2)) 
		{  
			presentTime = time_return();
			printf("default\n");
		}
		break;
	}
}

