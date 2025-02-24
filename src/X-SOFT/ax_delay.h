/**
	
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-10-26
  * @内  容  软件延时函数
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_DELAY_H
#define __AX_DELAY_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x.h"

//X-SOFT接口函数
void AX_DELAY_Init(void); //延时初始化
void AX_Delayus(__IO uint16_t us);  //软件微妙延时
void AX_Delayms(__IO uint16_t ms);  //软件毫秒延时

#endif 

