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
  * @brief   PWM�ӿڶ������
  *
  ******************************************************************************
  * @˵  ��
  *
  ******************************************************************************
  */

#include "ax_servo.h" 



/**
  * @��  ��  ��� �ӿڳ�ʼ��	
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_SERVO_AB_Init(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 

	//GPIO����ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//TIMʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//��ʱ������	PWM����ģʽ��Ƶ��50Hz,����20ms  
	//ռ�ձȵ��ڷ�Χ��0-1.5ms-2.5ms 0-1500-2500	��ʼ��Ϊ1500
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //��ʱ����Ƶ����Ƶ���Ƶ��Ϊ1M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=20000-1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration: Channel1 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;	    //ռ�ձȳ�ʼ����90��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel2
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4, ENABLE);	
}

/**
  * @��  ��  �������
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_A_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare1(TIM4,angle);
}

/**
  * @��  ��  �������
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_B_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare2(TIM4,angle);
}


/**
  * @��  ��  ��� �ӿڳ�ʼ��	
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_SERVO_CD_Init(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 	
	
	//GPIO����ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�100MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIMʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//��ʱ������	PWM����ģʽ��Ƶ��50Hz,����20ms  
	//ռ�ձȵ��ڷ�Χ��0-1.5ms-2.5ms 0-1500-2500	��ʼ��Ϊ1500
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //��ʱ����Ƶ����Ƶ���Ƶ��Ϊ1M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=20000-1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration: Channel1 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;	    //ռ�ձȳ�ʼ����90��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel2
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2, ENABLE);	
}

/**
  * @��  ��  ���A����
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_C_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare1(TIM2,angle);
}

/**
  * @��  ��  ���B����
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_D_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare2(TIM2,angle);
}

/**
  * @��  ��  ��� �ӿڳ�ʼ��	
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_SERVO_EFGH_Init(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 
	
	//��ʱ��ͨ��IO����
	//GPIO�����ù���ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	

	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//TIMʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3 , ENABLE); //���������ӳ�书�ܺ���

	//��ʱ������	PWM����ģʽ��Ƶ��50Hz,����20ms  
	//ռ�ձȵ��ڷ�Χ��0-1.5ms-2.5ms 0-1500-2500	��ʼ��Ϊ1500
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //��ʱ����Ƶ����Ƶ���Ƶ��Ϊ1M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=20000-1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;	    //ռ�ձȳ�ʼ����90��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	//PWM1 Mode configuration
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	//PWM1 Mode configuration
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	//PWM1 Mode configuration
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3, ENABLE);	
	
	//ʹ��MOEλ
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
}

/**
  * @��  ��  �������
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_E_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare1(TIM3,angle);
}

/**
  * @��  ��  �������
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_F_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare2(TIM3,angle);
}

/**
  * @��  ��  �������
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_G_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare3(TIM3,angle);
}

/**
  * @��  ��  �������
  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
  * @����ֵ  ��
  */
void AX_SERVO_H_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare4(TIM3,angle);
}




















///**
//  * @��  ��  ��� �ӿڳ�ʼ��	
//  * @��  ��  ��
//  * @����ֵ  ��
//  */
//void AX_SERVO_EFGH_Init(void)
//{ 
//	
//	GPIO_InitTypeDef GPIO_InitStructure; 
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure; 
//	
//	//��ʱ��ͨ��IO����
//	//GPIO�����ù���ʱ��ʹ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	

//	//����IO��Ϊ���ù���-��ʱ��ͨ��
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);

//	//TIMʱ��ʹ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

//	//��ʱ������	PWM����ģʽ��Ƶ��50Hz,����20ms  
//	//ռ�ձȵ��ڷ�Χ��0-1.5ms-2.5ms 0-1500-2500	��ʼ��Ϊ1500
//	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //��ʱ����Ƶ����Ƶ���Ƶ��Ϊ1M
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_Period=20000-1;   //�Զ���װ��ֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

//	//PWM1 Mode configuration
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = 1500;	    //ռ�ձȳ�ʼ����90��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);

//	//PWM1 Mode configuration
//	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
//	
//	//PWM1 Mode configuration
//	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
//	
//	//PWM1 Mode configuration
//	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM8, ENABLE);

//	//ʹ�ܶ�ʱ��
//	TIM_Cmd(TIM8, ENABLE);	
//	
//	//ʹ��MOEλ
//	TIM_CtrlPWMOutputs(TIM8,ENABLE);
//}

///**
//  * @��  ��  �������
//  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
//             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
//  * @����ֵ  ��
//  */
//void AX_SERVO_E_SetAngle(uint16_t angle)
//{
//	if(angle > 1800)
//		angle = 1800;
//	
//	angle = 1.111f*angle + 500;
//	TIM_SetCompare1(TIM8,angle);
//}

///**
//  * @��  ��  �������
//  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
//             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
//  * @����ֵ  ��
//  */
//void AX_SERVO_F_SetAngle(uint16_t angle)
//{
//	if(angle > 1800)
//		angle = 1800;
//	
//	angle = 1.111f*angle + 500;
//	TIM_SetCompare2(TIM8,angle);
//}

///**
//  * @��  ��  �������
//  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
//             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
//  * @����ֵ  ��
//  */
//void AX_SERVO_G_SetAngle(uint16_t angle)
//{
//	if(angle > 1800)
//		angle = 1800;
//	
//	angle = 1.111f*angle + 500;
//	TIM_SetCompare3(TIM8,angle);
//}

///**
//  * @��  ��  �������
//  * @��  ��  angle ����ĽǶȣ���Χ��0~1800������ϵ��0.1,
//             ˵�������ֶ��ʵ�ʿ��ƽǶ�С��0~1800����ע�ⷶΧ����
//  * @����ֵ  ��
//  */
//void AX_SERVO_H_SetAngle(uint16_t angle)
//{
//	if(angle > 1800)
//		angle = 1800;
//	
//	angle = 1.111f*angle + 500;
//	TIM_SetCompare4(TIM8,angle);
//}


/******************* (C) ��Ȩ 2018 XTARK **************************************/
