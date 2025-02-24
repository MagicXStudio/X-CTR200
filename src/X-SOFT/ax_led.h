/**
	     
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-7-26
  * @内  容  LED灯控制
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_LED_H
#define __AX_LED_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

void AX_LED_Init(void);

//X-SOFT接口函数

#define AX_LED_Green_Off()  	   GPIO_SetBits(GPIOB, GPIO_Pin_4)      //LEDG绿色熄灭
#define AX_LED_Green_On()		     GPIO_ResetBits(GPIOB, GPIO_Pin_4)    //LEDG绿色点亮
#define AX_LED_Green_Toggle()    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction) (1 - GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)))	//LEDG绿色状态翻转

#define AX_LED_Red_Off()  	   GPIO_SetBits(GPIOB, GPIO_Pin_5)      //LEDG绿色熄灭
#define AX_LED_Red_On()		     GPIO_ResetBits(GPIOB, GPIO_Pin_5)    //LEDG绿色点亮
#define AX_LED_Red_Toggle()    GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction) (1 - GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)))	//LEDG绿色状态翻转

#endif 

