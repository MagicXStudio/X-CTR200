/**
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2019-7-26
  * @��  ��  ���Դ���ͨ��
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_UART_DB_H
#define __AX_UART_DB_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//X-SOFT�ӿں���
void AX_UART_DB_Init(uint32_t baud);  //UART ���Դ��ڳ�ʼ��
uint8_t AX_UART_DB_GetRxData(uint8_t *pbuf);  //UART ��ȡ���յ�����
void AX_UART_DB_SendPacket(uint8_t *pbuf, uint8_t len, uint8_t num);  //UART �������ݣ�X-ProtocolЭ�飩

#endif 

