/**
	
  ******************************************************************************
  * @author  Musk Han @ XTARK
  * @version V1.1
  * @date    2019-01-01
  * @brief   PWM编码器
  *
  ******************************************************************************
  * @说  明
  *
  ******************************************************************************
  */

#include "ax_encoder.h" 

/**
  * @简  述  编码器AB初始化
  * @参  数  cycle：计数周期
  * @返回值  无
  */
void AX_ENCODER_AB_Init(uint16_t cycle)
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   

	//GPIO功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//Timer configuration in Encoder mode 
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = cycle;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	//Reset counter
	TIM2->CNT = 0;

	TIM_Cmd(TIM2, ENABLE);   
}

/**
  * @简  述  编码器AB获取计数器数值
  * @参  数  无
  * @返回值  计数器当前值
  */
uint16_t AX_ENCODER_AB_GetCounter(void)
{
	return (TIM_GetCounter(TIM2)); 
}

/**
  * @简  述  编码器AB设置计数器数值
  * @参  数  count  计数器数值
  * @返回值  无
  */
void AX_ENCODER_AB_SetCounter(uint16_t count)
{
	TIM2->CNT = count;
}

/**
  * @简  述  编码器初始化
  * @参  数  cycle：计数周期
  * @返回值  无
  */
void AX_ENCODER_CD_Init(uint16_t cycle)
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   

	//GPIO功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//Timer configuration in Encoder mode 
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = cycle;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	//Reset counter
	TIM4->CNT = 0;

	TIM_Cmd(TIM4, ENABLE);     
}

/**
  * @简  述  编码器EF获取计数器数值
  * @参  数  无
  * @返回值  计数器当前值
  */
uint16_t AX_ENCODER_CD_GetCounter(void)
{
	return (TIM_GetCounter(TIM4)); 
}

/**
  * @简  述  编码器EF设置计数器数值
  * @参  数  count  计数器数值
  * @返回值  无
  */
void AX_ENCODER_CD_SetCounter(uint16_t count)
{
	TIM4->CNT = count;
}

