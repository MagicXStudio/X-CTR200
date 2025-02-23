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
  * @日  期  2019-8-2
  * @brief   PWM接口舵机控制
  *
  ******************************************************************************
  * @说  明
  *
  ******************************************************************************
  */

#include "ax_servo.h" 



/**
  * @简  述  舵机 接口初始化	
  * @参  数  无
  * @返回值  无
  */
void AX_SERVO_AB_Init(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 

	//GPIO功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//定时器配置	PWM工作模式，频率50Hz,周期20ms  
	//占空比调节范围：0-1.5ms-2.5ms 0-1500-2500	初始化为1500
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //定时器分频，分频后的频率为1M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=20000-1;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration: Channel1 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;	    //占空比初始化，90度
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel2
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	//使能定时器
	TIM_Cmd(TIM4, ENABLE);	
}

/**
  * @简  述  舵机控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_A_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare1(TIM4,angle);
}

/**
  * @简  述  舵机控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_B_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare2(TIM4,angle);
}


/**
  * @简  述  舵机 接口初始化	
  * @参  数  无
  * @返回值  无
  */
void AX_SERVO_CD_Init(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 	
	
	//GPIO功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//定时器配置	PWM工作模式，频率50Hz,周期20ms  
	//占空比调节范围：0-1.5ms-2.5ms 0-1500-2500	初始化为1500
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //定时器分频，分频后的频率为1M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=20000-1;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration: Channel1 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;	    //占空比初始化，90度
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel2
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);

	//使能定时器
	TIM_Cmd(TIM2, ENABLE);	
}

/**
  * @简  述  舵机A控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_C_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare1(TIM2,angle);
}

/**
  * @简  述  舵机B控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_D_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare2(TIM2,angle);
}

/**
  * @简  述  舵机 接口初始化	
  * @参  数  无
  * @返回值  无
  */
void AX_SERVO_EFGH_Init(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 
	
	//定时器通道IO配置
	//GPIO及复用功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3 , ENABLE); //这个就是重映射功能函数

	//定时器配置	PWM工作模式，频率50Hz,周期20ms  
	//占空比调节范围：0-1.5ms-2.5ms 0-1500-2500	初始化为1500
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //定时器分频，分频后的频率为1M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=20000-1;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	//PWM1 Mode configuration
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;	    //占空比初始化，90度
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

	//使能定时器
	TIM_Cmd(TIM3, ENABLE);	
	
	//使能MOE位
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
}

/**
  * @简  述  舵机控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_E_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare1(TIM3,angle);
}

/**
  * @简  述  舵机控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_F_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare2(TIM3,angle);
}

/**
  * @简  述  舵机控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_G_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare3(TIM3,angle);
}

/**
  * @简  述  舵机控制
  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
  * @返回值  无
  */
void AX_SERVO_H_SetAngle(uint16_t angle)
{
	if(angle > 1800)
		angle = 1800;
	
	angle = 1.111f*angle + 500;
	TIM_SetCompare4(TIM3,angle);
}




















///**
//  * @简  述  舵机 接口初始化	
//  * @参  数  无
//  * @返回值  无
//  */
//void AX_SERVO_EFGH_Init(void)
//{ 
//	
//	GPIO_InitTypeDef GPIO_InitStructure; 
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure; 
//	
//	//定时器通道IO配置
//	//GPIO及复用功能时钟使能
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	

//	//配置IO口为复用功能-定时器通道
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);

//	//TIM时钟使能
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

//	//定时器配置	PWM工作模式，频率50Hz,周期20ms  
//	//占空比调节范围：0-1.5ms-2.5ms 0-1500-2500	初始化为1500
//	TIM_TimeBaseStructure.TIM_Prescaler=72-1;  //定时器分频，分频后的频率为1M
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
//	TIM_TimeBaseStructure.TIM_Period=20000-1;   //自动重装载值
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

//	//PWM1 Mode configuration
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = 1500;	    //占空比初始化，90度
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

//	//使能定时器
//	TIM_Cmd(TIM8, ENABLE);	
//	
//	//使能MOE位
//	TIM_CtrlPWMOutputs(TIM8,ENABLE);
//}

///**
//  * @简  述  舵机控制
//  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
//             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
//  * @返回值  无
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
//  * @简  述  舵机控制
//  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
//             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
//  * @返回值  无
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
//  * @简  述  舵机控制
//  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
//             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
//  * @返回值  无
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
//  * @简  述  舵机控制
//  * @参  数  angle 舵机的角度，范围：0~1800，比例系数0.1,
//             说明：部分舵机实际控制角度小于0~1800，请注意范围保护
//  * @返回值  无
//  */
//void AX_SERVO_H_SetAngle(uint16_t angle)
//{
//	if(angle > 1800)
//		angle = 1800;
//	
//	angle = 1.111f*angle + 500;
//	TIM_SetCompare4(TIM8,angle);
//}


/******************* (C) 版权 2018 XTARK **************************************/
