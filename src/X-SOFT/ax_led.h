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

/******************* (C) 版权 2019 XTARK **************************************/
