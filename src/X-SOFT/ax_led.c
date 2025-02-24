/**
	   
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2019-7-26
  * @内  容  LED灯控制
  ******************************************************************************
  * @说  明
  *
  * 
  ******************************************************************************
  */

#include "ax_led.h"

/**
  * @简  述  LED 初始化
  * @参  数  无
  * @返回值  无
  */
void AX_LED_Init(void) 
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//LED GPIO配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	//关闭LED灯
	GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5);
}

