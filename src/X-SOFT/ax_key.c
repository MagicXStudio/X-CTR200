/**
	                           
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2018-10-26
  * @��  ��  �������
  *
  ******************************************************************************
  * @˵  ��
  *
  * 1.��ȡ��ֵ�����������������̧��������ֵ��
  * 
  ******************************************************************************
  */

#include "ax_key.h"
#include "ax_delay.h"
#include "ax_sys.h"

/**
  * @��  ��  KEY ������ʼ��
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ����GPIO
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @��  ��  KEY ��ȡ����ֵ
  * @��  ��  ��
  * @����ֵ  ����ֵ����������Ϊ1��̧��Ϊ0��̧��������ֵ��
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



