/**
	     
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2019-7-26
  * @��  ��  LED�ƿ���
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_LED_H
#define __AX_LED_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

void AX_LED_Init(void);

//X-SOFT�ӿں���

#define AX_LED_Green_Off()  	   GPIO_SetBits(GPIOB, GPIO_Pin_4)      //LEDG��ɫϨ��
#define AX_LED_Green_On()		     GPIO_ResetBits(GPIOB, GPIO_Pin_4)    //LEDG��ɫ����
#define AX_LED_Green_Toggle()    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction) (1 - GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)))	//LEDG��ɫ״̬��ת

#define AX_LED_Red_Off()  	   GPIO_SetBits(GPIOB, GPIO_Pin_5)      //LEDG��ɫϨ��
#define AX_LED_Red_On()		     GPIO_ResetBits(GPIOB, GPIO_Pin_5)    //LEDG��ɫ����
#define AX_LED_Red_Toggle()    GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction) (1 - GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)))	//LEDG��ɫ״̬��ת

#endif 

