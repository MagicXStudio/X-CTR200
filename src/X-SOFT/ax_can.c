/**
	 __  _______  _    ____  _  __      __  __    ____   ___  _____ _____ 
	 \ \/ /_   _|/ \  |  _ \| |/ / ��   \ \/ /   / ___| / _ \|  ___|_   _| ��
	  \  /  | | / _ \ | |_) | ' /  ��    \  /____\___ \| | | | |_    | |   ��
	  /  \  | |/ ___ \|  _ <| . \  ��    /  \_____|__) | |_| |  _|   | |   ��
	 /_/\_\ |_/_/   \_\_| \_\_|\_\ ��   /_/\_\   |____/ \___/|_|     |_|   ̬
                              
  ****************************************************************************** 
  *           
  * ��Ȩ���У� XTARK@���˴���  ��Ȩ���У�����ؾ�
  * ������վ�� www.xtark.cn
  * �Ա����̣� https://shop246676508.taobao.com  
  * ����ý�壺 www.cnblogs.com/xtark�����ͣ�
	* ����΢�ţ� ΢�Ź��ںţ����˴��£���ȡ������Ѷ��
  *      
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2019-10-26
  * @��  ��  CANͨ��
  *
  ******************************************************************************
  * @˵  ��
  *
  * 
  ******************************************************************************
  */

#include "ax_can.h"
#include <stdio.h>

static uint8_t can_flag_rx_ok = 0; //���ճɹ���־
static CanTxMsg TxMessage;  //����֡
static CanRxMsg RxMessage; //����֡

/**
  * @��  ��  CAN ��ʼ��
  * @��  ��  
  * @����ֵ	 ��
	* @˵  ��  �����ʷ�Ƶ����6Ϊ1M��ʱ�䵥Ԫ�̶���TSJW=1��TBS1=3��TBS2=2��
  */
void AX_CAN_Init(void )
{
	GPIO_InitTypeDef GPIO_InitStructure; 	
  NVIC_InitTypeDef NVIC_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	/* ���ù��ܺ�GPIOB�˿�ʱ��ʹ��*/	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	                        											 

  /* Configure CAN pin: RX */	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // ��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* CAN1 ģ��ʱ��ʹ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); 

  /* CAN register init */
  CAN_DeInit(CAN1);	//������CAN��ȫ���Ĵ�������Ϊȱʡֵ
  CAN_StructInit(&CAN_InitStructure);  //��CAN_InitStruct�е�ÿһ��������ȱʡֵ����

  /* CAN ���Ƶ�Ԫ��ʼ�� */
  CAN_InitStructure.CAN_TTCM=DISABLE;  //û��ʹ��ʱ�䴥��ģʽ
  CAN_InitStructure.CAN_ABOM=DISABLE;  //û��ʹ���Զ����߹���
  CAN_InitStructure.CAN_AWUM=DISABLE;  //û��ʹ���Զ�����ģʽ
  CAN_InitStructure.CAN_NART=DISABLE;  //û��ʹ�ܷ��Զ��ش�ģʽ
  CAN_InitStructure.CAN_RFLM=DISABLE;  //û��ʹ�ܽ���FIFO����ģʽ
  CAN_InitStructure.CAN_TXFP=DISABLE;  //û��ʹ�ܷ���FIFO���ȼ�
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;  //CAN����ģʽ����Ϊ��ͨģʽ
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq; //����ͬ����Ծ���1��ʱ�䵥λ����Χ:1~3;
  CAN_InitStructure.CAN_BS1=CAN_BS1_3tq; //ʱ���1Ϊ3��ʱ�䵥λ����Χ:1~8;
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq; //ʱ���2Ϊ2��ʱ�䵥λ����Χ:1~16;
  CAN_InitStructure.CAN_Prescaler=6;   //�����ʷ�Ƶ�����趨ʱ�䵥λ���ȣ�������=Fpclk1/((tbs1+tbs2+1)*brp),��36M/(60(1+3+2))=100K
	CAN_Init(CAN1,&CAN_InitStructure);  
	
  /* CAN ��������ʼ�� */
  CAN_FilterInitStructure.CAN_FilterNumber=1;  //ָ��������Ϊ1
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;  //ָ��������Ϊ��ʶ������λģʽ
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;  //������λ��Ϊ32λ
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;  //��������ʶ���ĸ�16λֵ
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;  //��������ʶ���ĵ�16λֵ
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;  //���������α�ʶ���ĸ�16λֵ
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;  //���������α�ʶ���ĵ�16λֵ
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;  //�趨��ָ���������FIFOΪ0
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //������ʹ��
  CAN_FilterInit(&CAN_FilterInitStructure);
	
  /* CAN FIFO0 message pending interrupt enable */ 
  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); //ʹ��FIFO0��Ϣ�Һ��ж�
  NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

}

/**
  * @��  ��  CAN ���ͱ�׼֡����
  * @��  ��  *pbuf����������ָ��
  *          len���������ݳ��ȸ�������8
  *          id��֡�ţ�֡���뷶Χ0-0xFF
  * @����ֵ	 ��
  */
void AX_CAN_SendPacket(uint8_t *pbuf, uint8_t len, uint8_t id)
{
	uint8_t i;  
	
	//��װ����
  TxMessage.StdId=id;	  //��׼��ʶ��
  TxMessage.ExtId=0x0000;   //��չ��ʶ��0x0000
  TxMessage.IDE=CAN_ID_EXT;  //ʹ�ñ�׼��ʶ��
  TxMessage.RTR=CAN_RTR_DATA;  //Ϊ����֡
  TxMessage.DLC=len;	 //���ݳ���,��λΪ�ֽ�
	for(i=0; i<len; i++)
	{
		TxMessage.Data[i] = *(pbuf+i);
	}
	
	//��������	
  CAN_Transmit(CAN1,&TxMessage); 
}

/**
  * @��  ��  CAN ��ȡ���յ�����
  * @��  ��  *pbuf����������ָ��,��1���ֽ�Ϊ֡���룬����Ϊ����
  * @����ֵ	 0-�����ݽ��գ�other-��Ҫ��ȡ�������ֽڸ���
  */
uint8_t AX_CAN_GetRxData(uint8_t *pbuf)
{
	uint8_t i;
	
	if(can_flag_rx_ok != 0)
	{
		pbuf[0] = RxMessage.StdId;
		
		for(i=0; i<RxMessage.DLC; i++)
		{
			*(pbuf+i+1) = RxMessage.Data[i];
		}
		
		can_flag_rx_ok = 0;
		
		return RxMessage.DLC+1;
	}
	else
	{
		return 0;
	}	
}

/**
  * @��  ��  USB�жϺ�CAN�����жϷ����������ֻ�õ�CAN���ж�
  * @��  ��  ��
  * @����ֵ	 ��
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	//���յ�����
	can_flag_rx_ok = 1;
	
	//����FIFO0�е�����
  CAN_Receive(CAN1,CAN_FIFO0, &RxMessage); 
  
//	printf("ID%02X L%02X DATA%02X %02X %02X %02X %02X %02X %02X %02X\r\n",RxMessage.StdId,RxMessage.DLC,
//	RxMessage.Data[0],RxMessage.Data[1],RxMessage.Data[2],RxMessage.Data[3],
//	RxMessage.Data[4],RxMessage.Data[5],RxMessage.Data[6],RxMessage.Data[7]);		
	
} 


/******************* (C) ��Ȩ 2018 XTARK **************************************/
