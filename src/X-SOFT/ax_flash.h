/**
	   
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-7-26
  * @内  容  VIN输入电压检测
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_FLASH_H
#define __AX_FLASH_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

//X-SOFT接口函数
void AX_VIN1_Init(void);  //VIN 输入电压检测初始化
uint16_t AX_VIN1_GetVol_X100(void);  //VIN 获得输入电压

#endif

