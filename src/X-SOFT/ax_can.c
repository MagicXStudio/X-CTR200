/**
	 __  _______  _    ____  _  __      __  __    ____   ___  _____ _____ 
	 \ \/ /_   _|/ \  |  _ \| |/ / 塔   \ \/ /   / ___| / _ \|  ___|_   _| 软
	  \  /  | | / _ \ | |_) | ' /  克    \  /____\___ \| | | | |_    | |   件
	  /  \  | |/ ___ \|  _ <| . \  创    /  \_____|__) | |_| |  _|   | |   生
	 /_/\_\ |_/_/   \_\_| \_\_|\_\ 新   /_/\_\   |____/ \___/|_|     |_|   态
                              
  ****************************************************************************** 
  *           
  * 版权所有： XTARK@塔克创新  版权所有，盗版必究
  * 官网网站： www.xtark.cn
  * 淘宝店铺： https://shop246676508.taobao.com  
  * 塔克媒体： www.cnblogs.com/xtark（博客）
	* 塔克微信： 微信公众号：塔克创新（获取最新资讯）
  *      
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-10-26
  * @内  容  CAN通信
  *
  ******************************************************************************
  * @说  明
  *
  * 
  ******************************************************************************
  */

#include "ax_can.h"
#include <stdio.h>

static uint8_t can_flag_rx_ok = 0; //接收成功标志
static CanTxMsg TxMessage;  //发送帧
static CanRxMsg RxMessage; //接收帧

/**
  * @简  述  CAN 初始化
  * @参  数  
  * @返回值	 无
	* @说  明  波特率分频参数6为1M（时间单元固定，TSJW=1，TBS1=3，TBS2=2）
  */
void AX_CAN_Init(void )
{
	GPIO_InitTypeDef GPIO_InitStructure; 	
  NVIC_InitTypeDef NVIC_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	/* 复用功能和GPIOB端口时钟使能*/	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	                        											 

  /* Configure CAN pin: RX */	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* CAN1 模块时钟使能 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); 

  /* CAN register init */
  CAN_DeInit(CAN1);	//将外设CAN的全部寄存器重设为缺省值
  CAN_StructInit(&CAN_InitStructure);  //把CAN_InitStruct中的每一个参数按缺省值填入

  /* CAN 控制单元初始化 */
  CAN_InitStructure.CAN_TTCM=DISABLE;  //没有使能时间触发模式
  CAN_InitStructure.CAN_ABOM=DISABLE;  //没有使能自动离线管理
  CAN_InitStructure.CAN_AWUM=DISABLE;  //没有使能自动唤醒模式
  CAN_InitStructure.CAN_NART=DISABLE;  //没有使能非自动重传模式
  CAN_InitStructure.CAN_RFLM=DISABLE;  //没有使能接收FIFO锁定模式
  CAN_InitStructure.CAN_TXFP=DISABLE;  //没有使能发送FIFO优先级
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;  //CAN工作模式设置为普通模式
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq; //重新同步跳跃宽度1个时间单位，范围:1~3;
  CAN_InitStructure.CAN_BS1=CAN_BS1_3tq; //时间段1为3个时间单位，范围:1~8;
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq; //时间段2为2个时间单位，范围:1~16;
  CAN_InitStructure.CAN_Prescaler=6;   //波特率分频器，设定时间单位长度，波特率=Fpclk1/((tbs1+tbs2+1)*brp),例36M/(60(1+3+2))=100K
	CAN_Init(CAN1,&CAN_InitStructure);  
	
  /* CAN 过滤器初始化 */
  CAN_FilterInitStructure.CAN_FilterNumber=1;  //指定过滤器为1
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;  //指定过滤器为标识符屏蔽位模式
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;  //过滤器位宽为32位
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;  //过滤器标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;  //过滤器标识符的低16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;  //过滤器屏蔽标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;  //过滤器屏蔽标识符的低16位值
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;  //设定了指向过滤器的FIFO为0
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //过滤器使能
  CAN_FilterInit(&CAN_FilterInitStructure);
	
  /* CAN FIFO0 message pending interrupt enable */ 
  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); //使能FIFO0消息挂号中断
  NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

}

/**
  * @简  述  CAN 发送标准帧数据
  * @参  数  *pbuf：发送数据指针
  *          len：发送数据长度个数，≤8
  *          id：帧号，帧编码范围0-0xFF
  * @返回值	 无
  */
void AX_CAN_SendPacket(uint8_t *pbuf, uint8_t len, uint8_t id)
{
	uint8_t i;  
	
	//封装数据
  TxMessage.StdId=id;	  //标准标识符
  TxMessage.ExtId=0x0000;   //扩展标识符0x0000
  TxMessage.IDE=CAN_ID_EXT;  //使用标准标识符
  TxMessage.RTR=CAN_RTR_DATA;  //为数据帧
  TxMessage.DLC=len;	 //数据长度,单位为字节
	for(i=0; i<len; i++)
	{
		TxMessage.Data[i] = *(pbuf+i);
	}
	
	//发送数据	
  CAN_Transmit(CAN1,&TxMessage); 
}

/**
  * @简  述  CAN 获取接收的数据
  * @参  数  *pbuf：接收数据指针,第1个字节为帧编码，后面为数据
  * @返回值	 0-无数据接收，other-需要读取的数据字节个数
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
  * @简  述  USB中断和CAN接收中断服务程序，这里只用到CAN的中断
  * @参  数  无
  * @返回值	 无
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	//接收到数据
	can_flag_rx_ok = 1;
	
	//接收FIFO0中的数据
  CAN_Receive(CAN1,CAN_FIFO0, &RxMessage); 
  
//	printf("ID%02X L%02X DATA%02X %02X %02X %02X %02X %02X %02X %02X\r\n",RxMessage.StdId,RxMessage.DLC,
//	RxMessage.Data[0],RxMessage.Data[1],RxMessage.Data[2],RxMessage.Data[3],
//	RxMessage.Data[4],RxMessage.Data[5],RxMessage.Data[6],RxMessage.Data[7]);		
	
} 


/******************* (C) 版权 2018 XTARK **************************************/
