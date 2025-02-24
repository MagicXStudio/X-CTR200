/**
	  
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-8-2
  * @brief   PWM接口舵机控制
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_SERVO_H
#define __AX_SERVO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//X-SOFT接口函数
void AX_SERVO_AB_Init(void);                 //舵机AB接口初始化
void AX_SERVO_A_SetAngle(uint16_t angle);    //舵机A控制   
void AX_SERVO_B_SetAngle(uint16_t angle);    //舵机B控制

void AX_SERVO_CD_Init(void);                 //舵机CD接口初始化
void AX_SERVO_C_SetAngle(uint16_t angle);    //舵机C控制 
void AX_SERVO_D_SetAngle(uint16_t angle);    //舵机D控制 

void AX_SERVO_EFGH_Init(void);               //舵机EFGH接口初始化
void AX_SERVO_E_SetAngle(uint16_t angle);    //舵机E控制
void AX_SERVO_F_SetAngle(uint16_t angle);    //舵机F控制 
void AX_SERVO_G_SetAngle(uint16_t angle);    //舵机G控制
void AX_SERVO_H_SetAngle(uint16_t angle);    //舵机H控制 

#endif

