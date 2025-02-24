/**
	    
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-7-26
  * @brief   电机PWM控制函数
  *
  ******************************************************************************
  * @说  明
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_MOTOR_H
#define __AX_MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//X-SOFT接口函数
void AX_MOTOR_Init(uint8_t freq_khz); //电机PWM控制初始化
void AX_MOTOR_A_SetSpeed(int16_t speed);   //电机A控制
void AX_MOTOR_B_SetSpeed(int16_t speed);   //电机B控制


#endif

