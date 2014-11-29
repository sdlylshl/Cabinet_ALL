
#include "can.h"
/*���ò�ѯ��ʽ�����жϷ�ʽ�������ݿ��أ�����Ϊ�жϷ�ʽ*/
#define  Rx_Polling	1	

#ifndef Rx_Polling
#define  Rx_Interrupt	1
#endif

/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
typedef enum {KeyPressed=0,KeyRelease = !KeyPressed}KeyStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint32_t ret = 0; /* for return of the interrupt handling */

ErrorStatus HSEStartUpStatus;
u8 CAN_CellResetFlag;

/* Private functions ---------------------------------------------------------*/

TestStatus CAN_Polling(void);
void CAN_Interrupt(void);
void Can_Init(void);
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

#define TJA1054AT_STB  GPIO_Pin_8  
#define TJA1054AT_EN   GPIO_Pin_9
/*******************************************************************************
* Function Name  : CAN_Interrupt
* Description    : Configures the CAN, transmit and receive using interrupt.
* Input          : None
* Output         : None
* Return         : PASSED if the reception is well done, FAILED in other case
*******************************************************************************/


static void CAN1_GPIO_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
			RCC_APB1PeriphClockCmd(	RCC_APB1Periph_CAN1, ENABLE);
	
#if   CAN1_REMAP == 0  
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
#endif
	
#if  CAN1_REMAP == 1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);
#endif 
	
#if  CAN1_REMAP == 2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap2_CAN1,ENABLE);
#endif 
	
		/* Configure CAN pin: RX */
	  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN;
	  GPIO_InitStructure.GPIO_Mode = CAN1_RX_MODE;	
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(CAN1_RX_PORT, &GPIO_InitStructure);
	  
	  /* Configure CAN pin: TX */
		GPIO_InitStructure.GPIO_Pin = CAN1_TX_PIN;
	  GPIO_InitStructure.GPIO_Mode = CAN1_TX_MODE;	
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(CAN1_TX_PORT, &GPIO_InitStructure);
 
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the NVIC and Vector Table base address.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_NVIC_Config(void)
{
		/* Enable CAN RX0 interrupt IRQ channel */
		NVIC_SetPriority(CAN1_RX1_IRQn,4);
		NVIC_EnableIRQ(CAN1_RX1_IRQn);

		/* Enable CAN Tx interrupt IRQ channel USB_HP_CAN_TX_IRQChannel */
		NVIC_SetPriority(USB_HP_CAN1_TX_IRQn,5);
		NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);

		/* Enable CAN RX1 interrupt IRQ channel CAN_RX1_IRQChannel*/
		NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn,6);
		NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
	
		/* Enable CAN ERR interrupt IRQ channel CAN_SCE_IRQChannel*/
		NVIC_SetPriority(CAN1_SCE_IRQn,7);
		NVIC_EnableIRQ(CAN1_SCE_IRQn);
}
static void  CAN1_IT_Config(void)
{
	/*������CAN��ص��ж�,�������Ҫ����������*/

	/*CAN TX INTERRUPT*/
	CAN_ITConfig(CAN1,CAN_IT_TME|CAN_IT_RQCP0|CAN_IT_RQCP1|CAN_IT_RQCP2, ENABLE);

	/*CAN FIFO0 INTERRUPT*/
	CAN_ITConfig(CAN1,CAN_IT_FF0|CAN_IT_FMP0|CAN_IT_FOV0|CAN_IT_FMP0, ENABLE); 

	/*CAN FIFO1 INTERRUPT*/
	CAN_ITConfig(CAN1,CAN_IT_FF1|CAN_IT_FMP1|CAN_IT_FOV1|CAN_IT_FMP1, ENABLE); 

	/*CAN ESR INTERRUPT,ERROR PROCESS*/
	CAN_ITConfig(CAN1,CAN_IT_SLK|CAN_IT_WKU|CAN_IT_ERR|CAN_IT_LEC|CAN_IT_BOF|CAN_IT_EPV|CAN_IT_EWG, ENABLE); 

}
/*******************************************************************************
* Function Name  : CAN_Polling
* Description    : Configures the CAN, transmit and receive by polling
* Input          : None
* Output         : None
* Return         : PASSED if the reception is well done, FAILED in other case
*******************************************************************************/
void CAN1_Config(void)
{
#define CAN_BTR  500

	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	CAN1_GPIO_Config();
	
	/* CAN register init */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;	/*��ֹʱ�䴥��ͨѶģʽ*/
	CAN_InitStructure.CAN_ABOM=ENABLE;  /*�Զ��˳�����״̬��ʽ��0-�൱���������ֶ����ߣ�1-�൱���Զ�����*/
	CAN_InitStructure.CAN_AWUM=DISABLE;/*0-�����ͨ����0���ѣ�1-��⵽����ʱ���Զ�����*/
	CAN_InitStructure.CAN_NART=DISABLE;/*0-һֱ�ظ�����ֱ���ɹ���1-���۳ɹ��Է�ֻ����һ��*/
	CAN_InitStructure.CAN_RFLM=ENABLE;/*0-���ʱδ�������±��ĸǵ������ģ�1-FIFO������������±���ֱ�Ӷ�ʧ*/
	CAN_InitStructure.CAN_TXFP=DISABLE;/*0-���ķ������ȼ��ɱ�־��������1-���ķ������ȼ��������Ⱥ�˳�����*/
	// CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;/*ģʽ-����ģʽ-����ģʽ*/
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;

	/*=======================
	BTR=1/(Tbit)=1/(1+Tbs1+Tbs2)*Tq)=1/((1+8+7)*Tq)=1/16Tq
	Tq=Tpclk1*(prescale+1)=(prescale+1)/Fpclk1
	BTR=1/(16*(prescale+1)/Fpclk1)=Fpclk1/(16*(prescale+1))
	Precalse=(Fpclk1/(16*BTR))-1
	========================*/
#if (CAN_BTR==500)
	#if 0
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler=6;//4
	//pstr("Can BUS Run at 500Kpbs...");
	#else
	/* 36 000 000/500 000=72, 4*(1+10+7)=72*/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_10tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=4;//4
	//pstr("Can BUS Run at 500Kpbs...");
	#endif
#elif ((CAN_BTR==100))
	/*36000000/100000=360 =20*18=20*(1+15+2)*/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_15tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler=20;
	//pstr("Can BUS Run at 100Kpbs...");
#else	//(CAN_BTR==50)
	/*36000000/50000=720=45*(1+12+3)*/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_12tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;
	CAN_InitStructure.CAN_Prescaler=45;
	//pstr("Can BUS Run at 50Kpbs...");
#endif
	CAN_Init(CAN1,&CAN_InitStructure);

	 /* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber=0;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_CellResetFlag=RESET;
	
#if CAN1_NVIC	
	CAN1_NVIC_Config();
	CAN1_IT_Config();
#endif	

}



int CAN_main(void)
{
	
#ifdef DEBUG
	  debug();
#endif

	CAN1_Config();
	
	/*config TJA1054 */
	GPIO_SetBits(GPIOE,TJA1054AT_STB);  //GPIO_Pin_1);//STB
	GPIO_ResetBits(GPIOE,TJA1054AT_EN);   //EN
	GPIO_SetBits(GPIOE,TJA1054AT_STB);  //GPIO_Pin_1);//STB
	GPIO_SetBits(GPIOE,TJA1054AT_EN);   //EN
  
	/* CAN transmit at 100Kb/s and receive by polling in loopback mode */

	//pstr("    ***** Can Demo Start..... ****");
	while(1)
		{
#ifdef Test_Tx
		if(GPIO_ReadInputDataBit(GPIOD ,GPIO_Pin_3) == Bit_RESET)
			{
			NewKeyStaus = KeyPressed;
			}
		else
			{
			NewKeyStaus = KeyRelease;
			}
  
		if((NewKeyStaus == KeyRelease) && (OldKeyStatus == KeyPressed))
			{
  			i = 0;
			TxMessage.StdId=0x11;
			TxMessage.ExtId=0x223344;
			TxMessage.RTR=CAN_RTR_DATA;
			TxMessage.IDE=CAN_ID_EXT;
			TxMessage.DLC=4;
			TxMessage.Data[0]=0xaa;
			TxMessage.Data[1]=0xbb;
			TxMessage.Data[2]=0xcc;
			TxMessage.Data[3]=0xdd;
			TransmitMailbox=CAN_Transmit(&TxMessage);
			while( 1)
				{
				if(CAN_TransmitStatus(TransmitMailbox) != CANTXOK)
					{
					i++;
					pstr("Send Message Pending");
					}
				else
					{
					pstr("Send Message OK");
					i=0xfd;
					}
				if(i==0xfd)
					{
					pstr("Send Message Fail");
					break;
					} 
				}  //end while(1)
				
			/*LED ON-OFF*/	
			if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6) != RESET)
				{
				GPIO_ResetBits(GPIOC, GPIO_Pin_6);
				}
			else{
				GPIO_SetBits(GPIOC, GPIO_Pin_6);
				}

			}
		OldKeyStatus = NewKeyStaus;
#endif  // endif Test_tx
  
#ifdef Test_Rx

#ifdef Rx_Polling
		if(CAN_CellResetFlag == RESET)
			{
			CAN_ITConfig(CAN_IT_SLK|CAN_IT_WKU|CAN_IT_ERR|CAN_IT_LEC|CAN_IT_BOF|CAN_IT_EPV|CAN_IT_EWG, ENABLE); 
			CAN_CellResetFlag=SET;
			}

		if(CAN_Polling()==PASSED)
			{
			pstr("Polling Recv Message OK");
	   		}
#endif  //endif Rx_Polling

#ifdef Rx_Interrupt
		if(CAN_CellResetFlag == RESET)
			{
			CAN_Interrupt();
			pstr("Waitting for Interrupt coming.....");
			CAN_CellResetFlag = SET;
		}
#endif	//endif Test_rx

#endif


  }

}



TestStatus CAN_Polling(void)
{
	CanRxMsg RxMessage;
	u32 i = 0;
	i = 0;
	
	while((CAN_MessagePending(CAN1,CAN_FIFO0) < 1) && (i != 0xFF))
		{
		i++;
		}
	if(i != 0xFF)		/*˵�����յ�����*/
		{
		/* receive */
		RxMessage.StdId=0x00;
		RxMessage.IDE=CAN_ID_STD;
		RxMessage.DLC=0;
		RxMessage.Data[0]=0x00;
		RxMessage.Data[1]=0x00;
		CAN_Receive(CAN1,CAN_FIFO0, &RxMessage);
		//pstr("Recv a Message...");
		return PASSED;
		}
	else
		{
		return FAILED;
		}
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandle(void)
{
	if(CAN_GetITStatus(CAN1,CAN_IT_RQCP0))
		{
		
		CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP0);
		}
	if(CAN_GetITStatus(CAN1,CAN_IT_RQCP1))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP1);
		}
	if(CAN_GetITStatus(CAN1,CAN_IT_RQCP2))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP2);
		}

	//pstr("USB_HP_CAN_TX_IRQHandler");

}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandle(void)
{
	CanRxMsg RxMessage;

	if(CAN_GetITStatus(CAN1,CAN_IT_FF0))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);/**/
		}
	if(CAN_GetITStatus(CAN1,CAN_IT_FOV0))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FOV0);
		}
	
	RxMessage.StdId=0x00;
	RxMessage.ExtId=0x00;
	RxMessage.IDE=0;
	RxMessage.DLC=0;
	RxMessage.FMI=0;
	RxMessage.Data[0]=0x00;
	RxMessage.Data[1]=0x00;

	CAN_Receive(CAN1,CAN_FIFO0, &RxMessage);

	if((RxMessage.ExtId==0x1234) && (RxMessage.IDE==CAN_ID_EXT)
	  && (RxMessage.DLC==2) && ((RxMessage.Data[1]|RxMessage.Data[0]<<8)==0xDECA))
		{
		ret = 1; 
		}
	else
		{
		ret = 0; 
		}
	//pstr("USB_LP_CAN_RX0_IRQHandler (Interrupt Recv 1 Message)");
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandle(void)
{

	if(CAN_GetITStatus(CAN1,CAN_IT_FOV1))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FOV1);
		}
	if(CAN_GetITStatus(CAN1,CAN_IT_FF1))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FF1);
		}

	/*To DO: receive FIFO1 Message */
		{

		}
	
	//pstr("CAN_RX1_IRQHandler");

}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandle(void)
{
	/* �����жϹҺ�*/
	if(CAN_GetITStatus(CAN1,CAN_IT_WKU))	
		{
		//CAN_ClearITPendingBit(CAN_IT_WKU);
		}
	/*˯��ȷ���ж�״̬*/
	if(CAN_GetITStatus(CAN1,CAN_IT_SLK))
		{
		//CAN_ClearITPendingBit(CAN_IT_SLK);
		}
	/*�����ж�*/
	if(CAN_GetITStatus(CAN1,CAN_IT_BOF))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_BOF);
		CAN_ClearFlag(CAN1,CAN_FLAG_BOF);
		}
	/* ���󱻶���־�����󳬹���ֵ*/
	if(CAN_GetITStatus(CAN1,CAN_IT_EPV))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_EPV);
		CAN_ClearFlag(CAN1,CAN_FLAG_EPV);
		}
	/* ���󾯸��־���ﵽ����*/
	if(CAN_GetITStatus(CAN1,CAN_IT_EWG))
		{
		CAN_ClearITPendingBit(CAN1,CAN_IT_EWG);
		CAN_ClearFlag(CAN1,CAN_FLAG_EWG);
		}
	/*Reset Can Cell */
	{
	CAN1_Config();
	
	#if 0
	CAN_Interrupt(); /*������жϷ�ʽ*/
	#else
	CAN_ITConfig(CAN1,CAN_IT_SLK|CAN_IT_WKU|CAN_IT_ERR|CAN_IT_LEC|CAN_IT_BOF|CAN_IT_EPV|CAN_IT_EWG, ENABLE); 
	#endif
	}
	//pstr("CAN_SCE_IRQHandler,Try to Reset Can Cell");
}





/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
