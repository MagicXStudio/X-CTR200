
  
/**
  *
  ******************************************************************************
  * @˵  ��
  *  
  *   1.PS2���ݶ���
  *   BYTE   DATA   ����
  *   01     idle
  *   02     0x73   �ֱ��Ĺ���ģʽ
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    ��
  *   06     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   07     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   08     data   ���ҡ��  0x00 = ��    0xff = ��
  *   09     data   ���ҡ��  0x00 = ��    0xff = ��
  * 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_PS2_H
#define __AX_PS2_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

#define PS2_RAD_MODE  0x73   //PS2�ֱ����ģʽ��ģ��ģʽ��

//X-SOFT�ӿں���
void AX_PS2_Init(void);  //�ֱ���ʼ��
void AX_PS2_GetKeyData(uint8_t *data);  //��ȡ������ҡ������

#endif





