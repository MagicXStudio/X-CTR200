/**
	    
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-10-26
  * @内  容  CAN通信
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_CAN_H
#define __AX_CAN_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

//常用波特率设置参数
#define CAN_BRP_1000K  6   //波特率为1M的时钟分频数
#define CAN_BRP_500K  12   //波特率为500K的时钟分频数
#define CAN_BRP_100K  60   //波特率为100K的时钟分频数

//X-SOFT接口函数
void AX_CAN_Init(void); //CAN 初始化
void AX_CAN_SendPacket(uint8_t *pbuf, uint8_t len, uint8_t id);  //CAN 发送数据（X-Protocol协议）
uint8_t AX_CAN_GetRxData(uint8_t *pbuf);  //CAN 获取接收的数据

#endif 

