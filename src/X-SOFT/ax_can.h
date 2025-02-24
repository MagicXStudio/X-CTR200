/**
	    
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2019-10-26
  * @��  ��  CANͨ��
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_CAN_H
#define __AX_CAN_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

//���ò��������ò���
#define CAN_BRP_1000K  6   //������Ϊ1M��ʱ�ӷ�Ƶ��
#define CAN_BRP_500K  12   //������Ϊ500K��ʱ�ӷ�Ƶ��
#define CAN_BRP_100K  60   //������Ϊ100K��ʱ�ӷ�Ƶ��

//X-SOFT�ӿں���
void AX_CAN_Init(void); //CAN ��ʼ��
void AX_CAN_SendPacket(uint8_t *pbuf, uint8_t len, uint8_t id);  //CAN �������ݣ�X-ProtocolЭ�飩
uint8_t AX_CAN_GetRxData(uint8_t *pbuf);  //CAN ��ȡ���յ�����

#endif 

