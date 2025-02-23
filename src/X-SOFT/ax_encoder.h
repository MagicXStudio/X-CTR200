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

/******************* (C) 版权 2019 XTARK **************************************/
