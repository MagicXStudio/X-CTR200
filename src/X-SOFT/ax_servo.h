/**
	  
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2019-8-2
  * @brief   PWM�ӿڶ������
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_SERVO_H
#define __AX_SERVO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//X-SOFT�ӿں���
void AX_SERVO_AB_Init(void);                 //���AB�ӿڳ�ʼ��
void AX_SERVO_A_SetAngle(uint16_t angle);    //���A����   
void AX_SERVO_B_SetAngle(uint16_t angle);    //���B����

void AX_SERVO_CD_Init(void);                 //���CD�ӿڳ�ʼ��
void AX_SERVO_C_SetAngle(uint16_t angle);    //���C���� 
void AX_SERVO_D_SetAngle(uint16_t angle);    //���D���� 

void AX_SERVO_EFGH_Init(void);               //���EFGH�ӿڳ�ʼ��
void AX_SERVO_E_SetAngle(uint16_t angle);    //���E����
void AX_SERVO_F_SetAngle(uint16_t angle);    //���F���� 
void AX_SERVO_G_SetAngle(uint16_t angle);    //���G����
void AX_SERVO_H_SetAngle(uint16_t angle);    //���H���� 

#endif

