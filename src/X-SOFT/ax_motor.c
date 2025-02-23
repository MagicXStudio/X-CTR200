/**
	 __  _______  _    ____  _  __      __  __    ____   ___  _____ _____ 
	 \ \/ /_   _|/ \  |  _ \| |/ / ��   \ \/ /   / ___| / _ \|  ___|_   _| ��
	  \  /  | | / _ \ | |_) | ' /  ��    \  /____\___ \| | | | |_    | |   ��
	  /  \  | |/ ___ \|  _ <| . \  ��    /  \_____|__) | |_| |  _|   | |   ��
	 /_/\_\ |_/_/   \_\_| \_\_|\_\ ��   /_/\_\   |____/ \___/|_|     |_|   ̬
                              
  ****************************************************************************** 
  *           
  * ��Ȩ���У� XTARK@���˴���  ��Ȩ���У�����ؾ�
  * ������վ�� www.xtark.cn
  * �Ա����̣� https://shop246676508.taobao.com  
  * ����ý�壺 www.cnblogs.com/xtark�����ͣ�
	* ����΢�ţ� ΢�Ź��ںţ����˴��£���ȡ������Ѷ��
  *      
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  2019-8-2
  * @brief   ���PWM���ƺ���
  *
  ******************************************************************************
  * @˵  ��
  *
  ******************************************************************************
  */

#include "ax_motor.h" 

/**
  * @��  ��  ���PWM���Ƴ�ʼ��	
  * @��  ��  freq_khz:PWM���Ƶ�ʣ���Χ1~20,��λKHz
  * @����ֵ  ��
  */
void AX_MOTOR_Init(uint8_t freq_khz)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 

	//��ʱ��ͨ��IO����
	//GPIO�����ù���ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//����������IO����
	//IOʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	//���A�������IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//���B�������IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//��ʱ������
	//��������
	if(freq_khz == 0)
	freq_khz = 1;
	if(freq_khz > 20)
	freq_khz = 20;
	 
	//TIMʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	//Time base configuration
	TIM_TimeBaseStructure.TIM_Period = 2000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 36/freq_khz-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration: Channel1 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	    //ռ�ձȳ�ʼ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


	//PWM1 Mode configuration: Channel3
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel4
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM5, ENABLE);

	//TIM enable counter
	TIM_Cmd(TIM5, ENABLE);   
}

/**
  * @��  �� ���A PWM�ٶȿ���
  * @��  �� speed ���ת����ֵ����Χ-2000~2000
  * @����ֵ ��
  */
void AX_MOTOR_A_SetSpeed(int16_t speed)
{
	uint16_t temp;

  if(speed > 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	  GPIO_SetBits(GPIOC, GPIO_Pin_5);
		temp = speed;	
	}
	else if(speed < 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	  GPIO_SetBits(GPIOC, GPIO_Pin_4);
		temp = (-speed);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	  GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		temp = 0;
	}
	
	if(temp>2000)
		temp = 2000;
	
	TIM_SetCompare3(TIM5,temp);
}

/**
  * @��  �� ���B PWM�ٶȿ���
  * @��  �� speed ���ת����ֵ����Χ-2000~2000
  * @����ֵ ��
  */
void AX_MOTOR_B_SetSpeed(int16_t speed)
{
	uint16_t temp;

    if(speed > 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	  GPIO_SetBits(GPIOC, GPIO_Pin_3);
		temp = speed;	
	}
	else if(speed < 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	  GPIO_SetBits(GPIOC, GPIO_Pin_2);
		temp = (-speed);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	  GPIO_ResetBits(GPIOC, GPIO_Pin_3);
		temp = 0;
	}
	
	if(temp>2000)
		temp = 2000;
	
	TIM_SetCompare4(TIM5,temp);
}


/******************* (C) ��Ȩ 2019 XTARK **************************************/

