/**
	 __  _______  _    ____  _  __      __  __    ____   ___  _____ _____ 
	 \ \/ /_   _|/ \  |  _ \| |/ / 塔   \ \/ /   / ___| / _ \|  ___|_   _| 软
	  \  /  | | / _ \ | |_) | ' /  克    \  /____\___ \| | | | |_    | |   件
	  /  \  | |/ ___ \|  _ <| . \  创    /  \_____|__) | |_| |  _|   | |   生
	 /_/\_\ |_/_/   \_\_| \_\_|\_\ 新   /_/\_\   |____/ \___/|_|     |_|   态
                              
  ****************************************************************************** 
  *           
  * 版权所有： XTARK@塔克创新  版权所有，盗版必究
  * 官网网站： www.xtark.cn
  * 淘宝店铺： https://shop246676508.taobao.com  
  * 塔克媒体： www.cnblogs.com/xtark（博客）
	* 塔克微信： 微信公众号：塔克创新（获取最新资讯）
  *      
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

/******************* (C) 版权 2018 XTARK **************************************/
