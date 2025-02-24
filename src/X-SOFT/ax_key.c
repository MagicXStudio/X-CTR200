/**
	                           
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2018-10-26
  * @内  容  按键检测
  *
  ******************************************************************************
  * @说  明
  *
  * 1.获取键值，有软件消抖，按键抬起后输出键值。
  * 
  ******************************************************************************
  */

#include "ax_key.h"
#include "ax_delay.h"
#include "ax_sys.h"

/**
  * @简  述  KEY 按键初始化
  * @参  数  无
  * @返回值  无
  */
void AX_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使配置GPIO
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @简  述  KEY 获取按键值
  * @参  数  无
  * @返回值  按键值，按键按下为1，抬起为0（抬起后输出键值）
  */
uint8_t AX_KEY_Scan(void)
{
	if(PBin(1) == 0)		
	{
		AX_Delayms(10);
		
		if(PBin(1) == 0)
		{
			while(PBin(1) == 0);
			
			return 1;
		}
	}
	
	return 0;
}



