/**
	                
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2018-10-26
  * @内  容  按键检测
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_KEY_H
#define __AX_KEY_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

//X-SOFT接口函数
void AX_KEY_Init(void);  //按键初始化
uint8_t AX_KEY_Scan(void);  //按键扫描

#endif 

