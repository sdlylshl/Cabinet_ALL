/* Includes ------------------------------------------------------------------*/

#include <stdio.h>

#include "Ethernet.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#if defined (USE_STM324xG_EVAL)
#define MESSAGE1   "     STM32F40xx     "
#define MESSAGE2   " Device running on  "
#define MESSAGE3   "   STM324xG-EVAL    "

#else /* USE_STM324x7I_EVAL */ 
#define MESSAGE1   "     STM32F427x     "
#define MESSAGE2   " Device running on  "
#define MESSAGE3   "  STM324x7I-EVAL    "
#endif 

#define __DIV(__PCLK, __BAUD)       ((__PCLK*25)/(4*__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) * 16 + 50) / 100)
#define __USART_BRR(__PCLK, __BAUD) ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

typedef struct _CONFIG_MSG
{
	uint8_t Mac[6];
	uint8_t Lip[4];
	uint8_t Sub[4];
	uint8_t Gw[4];
	uint8_t DNS_Server_IP[4];	
	uint8_t  DHCP;
}CONFIG_MSG;


typedef struct _CONFIG_TYPE_DEF
{
	uint16_t port;
	uint8_t destip[4];
}CHCONFIG_TYPE_DEF;

	
#define SOCK_CONFIG		2	// UDP
#define SOCK_DNS		2	// UDP
#define SOCK_DHCP		3	// UDP

#define MAX_BUF_SIZE		1460
#define KEEP_ALIVE_TIME	30	// 30sec

#define ON	1
#define OFF	0

#define HIGH		1
#define LOW		0

//#define __GNUC__

#define	MAX_SOCK_NUM		_WIZCHIP_SOCK_NUM_


//CONFIG_MSG Config_Msg;
//CHCONFIG_TYPE_DEF Chconfig_Type_Def; 

// Configuration Network Information of W5500
//uint8_t Enable_DHCP = OFF;
//uint8_t MAC[6] = {0x00, 0x08, 0xDC, 0x01, 0x02, 0x02};//MAC Address
//uint8_t IP[4] = {192, 168, 88, 34};//IP Address
//uint8_t GateWay[4] = {192, 168, 88, 1};//Gateway Address
//uint8_t SubNet[4] = {255, 255, 255, 0};//SubnetMask Address

//TX MEM SIZE- SOCKET 0-7:2KB
//RX MEM SIZE- SOCKET 0-7:2KB
uint8_t txsize[MAX_SOCK_NUM] = {2,2,2,2,2,2,2,2};
uint8_t rxsize[MAX_SOCK_NUM] = {2,2,2,2,2,2,2,2};

//FOR TCP Client
//Configuration Network Information of TEST PC
uint8_t Dest_IP[4] = {192, 168, 88, 58}; //DST_IP Address 
uint16_t Dest_PORT = 8081; //DST_IP port

uint8_t ch_status[MAX_SOCK_NUM] = { 0, };	/** 0:close, 1:ready, 2:connected 3:init*/

// SRAM address range is 0x2000 0000 ~ 0x2000 4FFF (20KB)
//#define TX_RX_MAX_BUF_SIZE	2048
//#define TX_BUF	0x20004000
//#define RX_BUF	(TX_BUF+TX_RX_MAX_BUF_SIZE)
uint8_t TX_BUF[TX_RX_MAX_BUF_SIZE]; // TX Buffer for applications
uint8_t RX_BUF[TX_RX_MAX_BUF_SIZE]; // RX Buffer for applications



RCC_ClocksTypeDef RCC_ClockFreq;

uint8_t gDATABUF[DATA_BUF_SIZE];


///////////////////////////////////
// Default Network Configuration //
///////////////////////////////////

wiz_PhyConf gWIZPHYCONF = {
PHY_CONFBY_SW,
	PHY_MODE_AUTONEGO,
	PHY_SPEED_100,
	PHY_DUPLEX_FULL
};

wiz_NetInfo gWIZNETINFO = { 
{ 0x00, 0x08, 0xdc, 0x00, 0xab, 0xcf },   ///< Source Mac Address
{ 192, 168,	88, 11 },                     ///< Source IP Address
{ 255, 255, 255, 0 },                     ///< Subnet Mask 
{ 192, 168, 88, 1 },                       ///< Gateway IP Address
{ 202, 102, 152, 3 },                           ///< DNS server IP Address
 NETINFO_STATIC 		                      ///< 1 - Static, 2 - DHCP
};

wiz_NetTimeout gWIZNETTIMEOUT ={
	3, 					//< retry count 
	6000				//< time unit 100us
};

void wizchip_select(void) {
	//WIZ_SCS(0);		//低电平有效
	SPI1_select();
}

void wizchip_deselect(void) {
	//WIZ_SCS(1);
	SPI1_deselect();
}

void wizchip_write_byte(uint8_t wb) {
	SPI1_SendByte(wb);
}

uint8_t wizchip_read_byte() {
	return SPI1_ReceiveByte();
}


void network_init(void) {
	uint8_t tmpstr[6];
	ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO);
	ctlnetwork(CN_GET_NETINFO, (void*) &gWIZNETINFO);
	// Display Network Information
	ctlwizchip(CW_GET_ID, (void*) tmpstr);
	printf("\r\n=== %s NET CONF ===\r\n", (char*) tmpstr);
	printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n", gWIZNETINFO.mac[0],
			gWIZNETINFO.mac[1], gWIZNETINFO.mac[2], gWIZNETINFO.mac[3],
			gWIZNETINFO.mac[4], gWIZNETINFO.mac[5]);
	printf("SIP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0], gWIZNETINFO.ip[1],
			gWIZNETINFO.ip[2], gWIZNETINFO.ip[3]);
	printf("GAR: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0], gWIZNETINFO.gw[1],
			gWIZNETINFO.gw[2], gWIZNETINFO.gw[3]);
	printf("SUB: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0], gWIZNETINFO.sn[1],
			gWIZNETINFO.sn[2], gWIZNETINFO.sn[3]);
	printf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0], gWIZNETINFO.dns[1],
			gWIZNETINFO.dns[2], gWIZNETINFO.dns[3]);
	printf("======================\r\n");

	//配置超时时间
	ctlnetwork (CN_SET_TIMEOUT,&gWIZNETTIMEOUT);
	//ctlnetwork (CN_SET_NETMODE
	
}
/////////////////////////////////////////////////////////////

extern void wizchip_reset(void);
extern void wizchip_select(void);
extern void wizchip_deselect(void);
extern uint8_t wizchip_isreday(void);

int Ethernet_Init(void)
	{
		uint8_t tmp = 0;
//		uint32_t overtime = 0;
		uint8_t memsize[2][8] = { { 2, 2, 2, 2, 2, 2, 2, 2 }, { 2, 2, 2, 2, 2, 2, 2, 2 } };
			
			
	//RCC_Config();
	SPI1_Config();
	WIZ_GPIO_Configuration();			
	WIZ_SPI_Configuration();
	//WIZ_DMA_Configuration();
	//Timer_Configuration();
	//WIZ_USART_Configuration(); /* SysTick end of count event each 10ms */

//	RCC_GetClocksFreq(&RCC_Clocks);
	// SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

	/* Add your application code here */

	/* Infinite loop */

	RCC_GetClocksFreq(&RCC_ClockFreq);

	printf("SYSCLK frequency: %d\r\n", RCC_ClockFreq.SYSCLK_Frequency);
	printf("PCLK1 frequency: %d\r\n", RCC_ClockFreq.PCLK1_Frequency);
	printf("PCLK2 frequency: %d\r\n", RCC_ClockFreq.PCLK2_Frequency);
	
	// reg_wizchip_cris_cbfunc(void(*cris_en)(void), void(*cris_ex)(void))
	//1.注册片选函数
	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	
	//2.注册SPI读写函数
	reg_wizchip_spi_cbfunc(wizchip_read_byte, wizchip_write_byte);
	//2.
	//reg_wizchip_spiburst_cbfunc(wizchip_read_burst, wizchip_write_burst);
	//2.3 BUS读写
	//void reg_wizchip_bus_cbfunc(uint8_t(*bus_rb)(uint32_t addr), void (*bus_wb)(uint32_t addr, uint8_t wb));
	
	//3.复位W5500 
		wizchip_reset();
	
		//4.等待就绪RDY
	while (wizchip_isreday()) {
		;
	}

		/* WIZCHIP SOCKET Buffer initialize */
	if (ctlwizchip(CW_INIT_WIZCHIP, (void*) memsize) == -1) {
		printf("WIZCHIP Initialized fail.\r\n");
		return (-1)
			;
	}

	/* PHY link status check */
	//overtime =0;
	do {
		if (ctlwizchip(CW_GET_PHYLINK, (void*) &tmp) == -1)
			printf("Unknown PHY Link status.\r\n");
		if(TIM4_GetCurrentTime()>0xFFFFFF)
			return -1;
	} while (tmp == PHY_LINK_OFF);

	printf("W5500 Demo on STM32F401RE Cortex M0\r\n");

	network_init();

	return 0;
}
/**
 * @brief   Main program
 * @param  None
 * @retval None
 */
int Ethernet_main(void) {
	/*!< At this stage the microcontroller clock setting is already configured,
	 this is done through SystemInit() function which is called from startup
	 files (startup_stm32f40xx.s/startup_stm32f427x.s) before to branch to
	 application main.
	 To reconfigure the default setting of SystemInit() function, refer to
	 system_stm32f4xx.c file
	 */
//	uint32_t current_time = 0;

	int32_t ret = 0;
	uint8_t sn = 0;

Ethernet_Init();

	while (1) {

#if 0		
		if(GetIsTimeElapsed())
		{
			SetIsTimeElapsed(0);
			printf("Time Elapsed\r\n");
		}
#endif

#if 1		
		if ((ret = loopback_tcps(sn, gDATABUF, 3000)) < 0) {
			printf("%d:loopback_tcps error:%d\r\n", sn, ret);
			break;
		}
		if ((ret = loopback_tcps(sn + 1, gDATABUF, 3000)) < 0) {
			printf("%d:loopback_tcps error:%d\r\n", sn, ret);
			break;
		}
#endif
#if 0			
		if((ret = rcvonly_tcps(sn, gDATABUF, 3000)) < 0)
		{
			printf("%d:loopback_tcps error:%d\r\n", sn, ret);
			break;
		}
#endif
	}
	return 0;
}


/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
