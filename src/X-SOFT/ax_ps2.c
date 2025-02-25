/**

  ******************************************************************************
  * @˵  ��
  *  
  *   PS2���ݶ���
  *   BYTE   DATA   ����
  *   01     idle
  *   02     0x73   �ֱ��Ĺ���ģʽ
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    ��
  *   06     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   07     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   08     data   ���ҡ��  0x00 = ��    0xff = ��
  *   09     data   ���ҡ��  0x00 = ��    0xff = ��
  * 
  ******************************************************************************
  */
#include "ax_ps2.h"
#include "ax_sys.h"
#include "ax_delay.h"

//PS�ֱ������������
#define PS2_READ_DATA()  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)
#define PS2_CMD_H()      GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define PS2_CMD_L()      GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define PS2_ATT_H()      GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define PS2_ATT_L()      GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define PS2_CLK_H()      GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define PS2_CLK_L()      GPIO_ResetBits(GPIOB, GPIO_Pin_12)

/**
  * @��  ��  PS2 �ֱ���ʼ��
  * @��  ��  ��
  * @����ֵ  ��
  * @˵  ��  ���ö˿�
  */
void AX_PS2_Init(void)
{ 	 											  
	GPIO_InitTypeDef GPIO_InitStructure;         
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

//���ֱ���������
static uint8_t PS2_SendCmd(uint8_t cmd)
{
	volatile uint16_t ref=0x01;
	uint8_t temp = 0;
	
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&cmd)
			PS2_CMD_H();                   //�����Ϊ����λ
		else 
			PS2_CMD_L();

		PS2_CLK_H();                        //ʱ������
		AX_Delayus(16);
		PS2_CLK_L();
		AX_Delayus(16);
		PS2_CLK_H();
		
		if(PS2_READ_DATA())
			temp = ref|temp;
	}
	
	return temp;
}
/**
  * @��  ��  PS2 ��ȡ������ҡ����ֵ��
  * @��  ��  *data �ֱ�����
  * @����ֵ  ��
  */
void AX_PS2_GetKeyData(uint8_t *data)
{
	volatile uint16_t ref=0x01;
	uint8_t i;
	
	//������
	for(i=0;i<9;i++) 
		data[i] = 0;
	
	PS2_ATT_L();
	
	PS2_SendCmd(0x01);   //��ʼ����
	data[1] = PS2_SendCmd(0x42);  //��������
	
	for(i=2;i<9;i++)          //��ʼ��������
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			PS2_CLK_H();
			PS2_CLK_L();
			AX_Delayus(16);
			PS2_CLK_H();
		  if(PS2_READ_DATA())
				
				data[i] = ref|data[i];
		}
    AX_Delayus(16);
	}
	
	PS2_ATT_H();
}

