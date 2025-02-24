/**
  ******************************************************************************
  * @˵  ��
  *
  * 1.��������Ϊָ���û�ʹ��X-SOFT�淶�Ľӿں���ʵ�ֵײ������
	* 2.ÿ�����̶��������ԣ�ȡ��ע�ͣ��������ؼ��ɲ鿴Ч����
  * 3.ÿ�����̾��й���˵����
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include <math.h>  

#include "ax_sys.h"    //ϵͳ����
#include "ax_delay.h"  //�����ʱ

#include "ax_led.h"  //LED�ƿ���
#include "ax_key.h"  //�������
#include "ax_vin.h"  //�����ѹ���
#include "ax_flash.h"  //Ƭ��FLASHģ��EEPROM�洢

#include "ax_uart_db.h"  //���Դ��ڣ�USB����
#include "ax_can.h"  //CANͨ��

#include "ax_motor.h"  //ֱ���������
#include "ax_encoder.h" //����������
#include "ax_servo.h" //�������


/******************************************************************************
      ��������  �嵥
			
* LED��˸�����Դ���Printf�������
* VIN�����ѹ������̣����׵�����
* KEY������������̣��������
* 2·ֱ�����PWM�ٶȿ�������
* 2·���AB��������������
* 8·�����������
* CANͨ�������շ�����

*******************************************************************************/



/******************************************************************************
�������ƣ�LED��˸�����Դ���Printf���
����˵������������ʾLED���ƺ͵��Դ���Printf����
*******************************************************************************/
int main(void)
{
	uint8_t i=0;
	
	//�����ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

	//JTAG������
	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ� 
	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ��� 
	
	//�����ʱ��ʼ��
	AX_DELAY_Init(); 	
	AX_LED_Init();  //LED��ʼ��

	//���Դ��ڳ�ʼ��
	AX_UART_DB_Init(115200); //���Դ���
	printf("  \r\n"); //����ո�CPUBUG
	
	//LED����0.5S
	AX_LED_Green_On();  
	AX_Delayms(500);
	AX_LED_Green_Off();
	AX_Delayms(500);
	
	while (1)
	{	
    //���Դ��������Ϣ		
		printf("Printf������ԣ�%d \r\n",i);
		i++;
		AX_Delayms(200);
		
		//LED��ת
	    AX_LED_Green_Toggle();
		AX_LED_Red_Toggle();
	}
}



///******************************************************************************
//�������ƣ�VIN�����ѹ���
//����˵��������ѭ������ɼ����ĵ�ѹֵ
//*******************************************************************************/
//int main(void)
//{
//	uint16_t vol;
//	
//	//�����ж����ȼ�����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

//	//JTAG������
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ� 
//	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ��� 
//	
//	//�����ʱ��ʼ��
//	AX_DELAY_Init(); 	
//	
//	//���Դ��ڳ�ʼ��
//	AX_UART_DB_Init(115200); //���Դ���
//	printf("  \r\n"); //����ո�CPUBUG
//	
//	//VIN����ʼ��
//	AX_VIN_Init();
//	
//	//��ʾ��Ϣ
//	printf("*ѭ���ɼ�VIN����ڵ�ѹֵ\r\n");
//	
//	while (1) 
//	{	
//		//ÿ100MS���һ�ε�ص�ѹֵ
//		vol = AX_VIN_GetVol_X100();
//		printf("*VIN��ѹ��%d(0.01V)\r\n",vol );	
//		AX_Delayms(100);
//	}
//}



///******************************************************************************
//�������ƣ�KEY���������
//����˵�����������º�LED����˸һ��
//*******************************************************************************/
//int main(void)
//{
//	uint8_t temp;
//	
//	//�����ж����ȼ�����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

//	//JTAG������
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ� 
//	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ��� 
//	
//	//�����ʱ��ʼ��
//	AX_DELAY_Init(); 	
//	AX_LED_Init();  	
//	
//	//���Դ��ڳ�ʼ��
//	AX_UART_DB_Init(115200); //���Դ���
//	printf("  \r\n"); //����ո�CPUBUG
//	
//	//��ʼ��
//	AX_KEY_Init();
//	
//	while (1) 
//	{	
//		temp = AX_KEY_Scan();
//		
//		if(temp == 1)
//		{
//			AX_LED_Green_On();  
//			AX_Delayms(100);
//			AX_LED_Green_Off();
//		}
//		AX_Delayms(10);
//	}
//}	



///******************************************************************************
//�������ƣ�ֱ�����PWM���ٿ���
//����˵��������4·������������ͱ��ٷ�ת��������
//����˵�����������������·���ƽӿ��е�����һ·�����Կ�������������������ת�ͷ�ת
//*******************************************************************************/
//int main(void)
//{
//	uint16_t temp;
//	
//	//�����ж����ȼ�����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//���Դ��ڳ�ʼ��
//	AX_UART_DB_Init(115200); //���Դ���
//	printf("  \r\n"); //����ո�CPUBUG
//	
//	//JTAG������
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ� 
//	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ��� 		
//	
//	//�����ʱ��ʼ��
//	AX_DELAY_Init(); 	
//    AX_LED_Init();  
//	
//	//��ʼ��
//	AX_MOTOR_Init(10);  //���õ������PWMƵ��Ϊ10K

//	while (1) 
//	{	
//		//���Ƶ��ת��
//		for(temp=0; temp<=2000; temp++)
//		{
//			AX_MOTOR_A_SetSpeed(temp); 
//			AX_MOTOR_B_SetSpeed(temp); 
//			AX_Delayms(5);
//		}
//		AX_MOTOR_A_SetSpeed(0); 
//		AX_MOTOR_B_SetSpeed(0); 	
//		AX_Delayms(1000);
//		
//		//���Ƶ������ת��
//		for(temp=0; temp<=2000; temp++)
//		{
//			AX_MOTOR_A_SetSpeed(-temp); 
//			AX_MOTOR_B_SetSpeed(-temp); 
//			AX_Delayms(5);
//		}
//		AX_MOTOR_A_SetSpeed(0); 
//		AX_MOTOR_B_SetSpeed(0);   
//		AX_Delayms(1000);
//	}
//}	



/******************************************************************************
//�������ƣ�����AB����������
//����˵����300ms����5·��������ֵ�����������ʾ�����50%PWMռ�ձ�����
//����˵����2·�����������ã����ӱ������󣬼����ֶ�ת������۲촮�����ֵ�仯
//         Ҳ�ɽ�������ӵ�����ӿ�
//*******************************************************************************/
//int main(void)
//{
//	//�����ж����ȼ�����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//���Դ��ڳ�ʼ��
//	AX_UART_DB_Init(115200); //���Դ���
//	printf("  \r\n"); //����ո�CPUBUG
//	
//	//JTAG������
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ� 
//	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ��� 		
//	
//	//�����ʱ��ʼ��
//	AX_DELAY_Init(); 	
//  AX_LED_Init();  
//	
//	//��ʼ��
//	AX_MOTOR_Init(10);  //���õ������PWMƵ��Ϊ10K
//	AX_MOTOR_A_SetSpeed(1000); 
//	AX_MOTOR_B_SetSpeed(1000); 
//	
//	//������������ʼ��
//  AX_ENCODER_AB_Init(60000);  
//	AX_ENCODER_CD_Init(60000); 
//	//�趨�м�ֵ30000
//	AX_ENCODER_AB_SetCounter(30000); 
//	AX_ENCODER_CD_SetCounter(30000); 
//	
//	//��ʾ��Ϣ
//	printf("��·��������������\r\n");

//	while (1) 
//	{		
//		printf("*AB:%5d CD:%5d \r\n",
//		AX_ENCODER_AB_GetCounter(),AX_ENCODER_CD_GetCounter());  
//		AX_Delayms(300);
//	}
//}	



///******************************************************************************
//�������ƣ������������
//����˵��������8·���30�ȡ�90�ȡ�150�ȼ���˶�
//����˵��������8·����ӿ�������һ·���������������ѭ��30�㡢90�㡢150���˶���
//         ��������·�������������Ť�ش���ע���Դ��������
//*******************************************************************************/
//int main(void)
//{
//	//�����ж����ȼ�����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//���Դ��ڳ�ʼ��
//	AX_UART_DB_Init(115200); //���Դ���
//	printf("  \r\n"); //����ո�CPUBUG
//	
//	//JTAG������
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ� 
//	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ��� 		
//	
//	//�����ʱ��ʼ��
//	AX_DELAY_Init();
//  AX_LED_Init();
//	
//	//��ʼ��
//	AX_SERVO_AB_Init();
//    AX_SERVO_CD_Init();
//	AX_SERVO_EFGH_Init();

//	
//	//��ʾ��Ϣ
//	printf("��·������Ʋ���\r\n");

//	while (1) 
//	{		
//		printf("*30��...... \r\n");		
//		AX_SERVO_A_SetAngle(300);
//		AX_SERVO_B_SetAngle(300);
//		AX_SERVO_C_SetAngle(300);
//		AX_SERVO_D_SetAngle(300);
//		AX_SERVO_E_SetAngle(300);
//		AX_SERVO_F_SetAngle(300);
//		AX_SERVO_G_SetAngle(300);
//		AX_SERVO_H_SetAngle(300);
//		AX_Delayms(1000);
//		
//		printf("*90��...... \r\n");
//		AX_SERVO_A_SetAngle(900);
//		AX_SERVO_B_SetAngle(900);
//		AX_SERVO_C_SetAngle(900);
//		AX_SERVO_D_SetAngle(900);
//		AX_SERVO_E_SetAngle(900);
//		AX_SERVO_F_SetAngle(900);
//		AX_SERVO_G_SetAngle(900);
//		AX_SERVO_H_SetAngle(900);
//		AX_Delayms(1000);
//		
//		printf("*150��...... \r\n");
//		AX_SERVO_A_SetAngle(1500);
//		AX_SERVO_B_SetAngle(1500);
//		AX_SERVO_C_SetAngle(1500);
//		AX_SERVO_D_SetAngle(1500);
//		AX_SERVO_E_SetAngle(1500);
//		AX_SERVO_F_SetAngle(1500);
//		AX_SERVO_G_SetAngle(1500);
//		AX_SERVO_H_SetAngle(1500);
//		AX_Delayms(1000);
//	}
//}	


///******************************************************************************
//�������ƣ�CANͨ�������շ�����
//����˵����ͨ��CAN�ӿ�ʵ�������շ����յ����ݺ�ͨ��USB���������ʾ
//����˵����CAN������������Ϊ1M,��׼֡����
//         ���յ�֡IDΪ0x02�����ݣ�����һ֡����
//*******************************************************************************/
//int main(void)
//{
//	int8_t ax8 = 100;
//	int16_t ax16 = 0x1000;
//	int32_t ax32 = -123456;
//	uint8_t tx_buf[10];
//	uint8_t comdata[10];  //ͨ������
//	
//	//�����ж����ȼ�����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//���Դ��ڳ�ʼ��
//	AX_UART_DB_Init(115200); //���Դ���
//	printf("  \r\n"); //����ո�CPUBUG
//	
//	//JTAG������
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG�ӿ�
//	AX_JTAG_Set(SWD_ENABLE);  //��SWD�ӿ� �������������SWD�ӿڵ���
//	
//	//�����ʱ��ʼ��
//	AX_DELAY_Init();
//  AX_LED_Init();
//	
//	//CAN�ӿڳ�ʼ��
//	AX_CAN_Init();
//	
//	//���ݷ�װʾ��
//	tx_buf[0] = (*((uint8_t *)(&ax32) + 3)); //32λ����,��λ
//	tx_buf[1] = (*((uint8_t *)(&ax32) + 2)); 
//	tx_buf[2] = (*((uint8_t *)(&ax32) + 1)); 
//	tx_buf[3] = (*(uint8_t *)(&ax32));		
//	tx_buf[4] = (*((uint8_t *)(&ax16) + 1)); //16λ����,��λ
//	tx_buf[5] = (*(uint8_t *)(&ax16));
//	tx_buf[6] = (uint8_t)ax8;  //8λ����

//	while (1)
//	{
//		//����CAN����
//		if(AX_CAN_GetRxData(comdata))
//		{
//			//USB�������CAN���յ�����
//			printf("RX��ID-%02X DATA-%02X %02X %02X %02X %02X %02X %02X %02X\r\n",comdata[0],
//			comdata[1],comdata[2],comdata[3],comdata[4],comdata[5],comdata[6],comdata[7],comdata[8]);	
//			
//			//���֡��ʶΪ2��������һ֡����
//			if(comdata[0] == 0x02)
//			{
//				AX_CAN_SendPacket(tx_buf,7,0x01);  //֡��Ϊ0x01
//				ax8++;  //���ݱ仯չʾ
//				tx_buf[6] = (uint8_t)ax8;  				
//			}
//		}
//		AX_Delayms(10);
//	}
//}	
