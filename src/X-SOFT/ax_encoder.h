/**
	    
  ******************************************************************************
  * @author  Musk Han @ XTARK
  * @version V1.1
  * @date    2019-01-01
  * @brief   PWM������
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_ENCODER_H
#define __AX_ENCODER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//X-SOFT�ӿں���
void AX_ENCODER_AB_Init(uint16_t cycle);          //��������ʼ��
uint16_t AX_ENCODER_AB_GetCounter(void);          //��������ȡ��������ֵ
void AX_ENCODER_AB_SetCounter(uint16_t count);    //���������ü�������ֵ

void AX_ENCODER_CD_Init(uint16_t cycle);          //��������ʼ��
uint16_t AX_ENCODER_CD_GetCounter(void);          //��������ȡ��������ֵ
void AX_ENCODER_CD_SetCounter(uint16_t count);    //���������ü�������ֵ

#endif

