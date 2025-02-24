/**
	    
  ******************************************************************************
  * @author  Musk Han @ XTARK
  * @version V1.1
  * @date    2019-01-01
  * @brief   PWM编码器
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_ENCODER_H
#define __AX_ENCODER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//X-SOFT接口函数
void AX_ENCODER_AB_Init(uint16_t cycle);          //编码器初始化
uint16_t AX_ENCODER_AB_GetCounter(void);          //编码器获取计数器数值
void AX_ENCODER_AB_SetCounter(uint16_t count);    //编码器设置计数器数值

void AX_ENCODER_CD_Init(uint16_t cycle);          //编码器初始化
uint16_t AX_ENCODER_CD_GetCounter(void);          //编码器获取计数器数值
void AX_ENCODER_CD_SetCounter(uint16_t count);    //编码器设置计数器数值

#endif

