/**
  ******************************************************************************
  * @file    ax_timer_int.h
  * @author  Musk Han @ XTARK
  * @version V1.1
  * @date    2018-01-01
  * @brief   X-CTR100 定时器计数溢出中断文件
  *
  ******************************************************************************
  * @xtark  实验平台：塔克出品 X-CTR100 控制器
  *         塔克官网社区：http://www.xtark.cn
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_TIMER_INT_H
#define __AX_TIMER_INT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "ax_basis.h"

/*** X-CTR100 定时器计数溢出中断函数 **********/
void AX_TIMER_INT_TIM6_Init(uint16_t cnt_us);  //TIM6初始化

#endif

