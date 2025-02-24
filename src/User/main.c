/**
  ******************************************************************************
  * @说  明
  *
  * 1.例程作用为指导用户使用X-SOFT规范的接口函数实现底层操作。
	* 2.每个例程都经过测试，取消注释，编译下载即可查看效果。
  * 3.每个例程具有功能说明。
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include <math.h>  

#include "ax_sys.h"    //系统设置
#include "ax_delay.h"  //软件延时

#include "ax_led.h"  //LED灯控制
#include "ax_key.h"  //按键检测
#include "ax_vin.h"  //输入电压检测
#include "ax_flash.h"  //片上FLASH模拟EEPROM存储

#include "ax_uart_db.h"  //调试串口，USB串口
#include "ax_can.h"  //CAN通信

#include "ax_motor.h"  //直流电机控制
#include "ax_encoder.h" //编码器控制
#include "ax_servo.h" //舵机控制


/******************************************************************************
      基础例程  清单
			
* LED闪烁，调试串口Printf输出例程
* VIN输入电压检测例程，简易电量计
* KEY按键检测检测例程，软件消抖
* 2路直流电机PWM速度控制例程
* 2路电机AB正交编码器例程
* 8路舵机控制例程
* CAN通信数据收发例程

*******************************************************************************/



/******************************************************************************
例程名称：LED闪烁，调试串口Printf输出
例程说明：本例程演示LED控制和调试串口Printf功能
*******************************************************************************/
int main(void)
{
	uint8_t i=0;
	
	//设置中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

	//JTAG口设置
	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口 
	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试 
	
	//软件延时初始化
	AX_DELAY_Init(); 	
	AX_LED_Init();  //LED初始化

	//调试串口初始化
	AX_UART_DB_Init(115200); //调试串口
	printf("  \r\n"); //输出空格，CPUBUG
	
	//LED点亮0.5S
	AX_LED_Green_On();  
	AX_Delayms(500);
	AX_LED_Green_Off();
	AX_Delayms(500);
	
	while (1)
	{	
    //调试串口输出信息		
		printf("Printf输出测试：%d \r\n",i);
		i++;
		AX_Delayms(200);
		
		//LED反转
	    AX_LED_Green_Toggle();
		AX_LED_Red_Toggle();
	}
}



///******************************************************************************
//例程名称：VIN输入电压检测
//例程说明：串口循环输出采集到的电压值
//*******************************************************************************/
//int main(void)
//{
//	uint16_t vol;
//	
//	//设置中断优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

//	//JTAG口设置
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口 
//	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试 
//	
//	//软件延时初始化
//	AX_DELAY_Init(); 	
//	
//	//调试串口初始化
//	AX_UART_DB_Init(115200); //调试串口
//	printf("  \r\n"); //输出空格，CPUBUG
//	
//	//VIN检测初始化
//	AX_VIN_Init();
//	
//	//提示信息
//	printf("*循环采集VIN输入口电压值\r\n");
//	
//	while (1) 
//	{	
//		//每100MS输出一次电池电压值
//		vol = AX_VIN_GetVol_X100();
//		printf("*VIN电压：%d(0.01V)\r\n",vol );	
//		AX_Delayms(100);
//	}
//}



///******************************************************************************
//例程名称：KEY按键检测检测
//例程说明：按键按下后，LED灯闪烁一次
//*******************************************************************************/
//int main(void)
//{
//	uint8_t temp;
//	
//	//设置中断优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

//	//JTAG口设置
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口 
//	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试 
//	
//	//软件延时初始化
//	AX_DELAY_Init(); 	
//	AX_LED_Init();  	
//	
//	//调试串口初始化
//	AX_UART_DB_Init(115200); //调试串口
//	printf("  \r\n"); //输出空格，CPUBUG
//	
//	//初始化
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
//例程名称：直流电机PWM调速控制
//例程说明：控制4路电机变速正传和变速反转交替运行
//操作说明：电机可连接至四路控制接口中的任意一路，可以看到电机做间隔的增速正转和反转
//*******************************************************************************/
//int main(void)
//{
//	uint16_t temp;
//	
//	//设置中断优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//调试串口初始化
//	AX_UART_DB_Init(115200); //调试串口
//	printf("  \r\n"); //输出空格，CPUBUG
//	
//	//JTAG口设置
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口 
//	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试 		
//	
//	//软件延时初始化
//	AX_DELAY_Init(); 	
//    AX_LED_Init();  
//	
//	//初始化
//	AX_MOTOR_Init(10);  //设置电机控制PWM频率为10K

//	while (1) 
//	{	
//		//控制电机转动
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
//		//控制电机反向转动
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
//例程名称：正交AB编码器例程
//例程说明：300ms采样5路编码器数值并串口输出显示，电机50%PWM占空比运行
//操作说明：2路编码器均可用，连接编码器后，即可手动转动电机观察串口输出值变化
//         也可将电机连接到电机接口
//*******************************************************************************/
//int main(void)
//{
//	//设置中断优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//调试串口初始化
//	AX_UART_DB_Init(115200); //调试串口
//	printf("  \r\n"); //输出空格，CPUBUG
//	
//	//JTAG口设置
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口 
//	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试 		
//	
//	//软件延时初始化
//	AX_DELAY_Init(); 	
//  AX_LED_Init();  
//	
//	//初始化
//	AX_MOTOR_Init(10);  //设置电机控制PWM频率为10K
//	AX_MOTOR_A_SetSpeed(1000); 
//	AX_MOTOR_B_SetSpeed(1000); 
//	
//	//正交编码器初始化
//  AX_ENCODER_AB_Init(60000);  
//	AX_ENCODER_CD_Init(60000); 
//	//设定中间值30000
//	AX_ENCODER_AB_SetCounter(30000); 
//	AX_ENCODER_CD_SetCounter(30000); 
//	
//	//提示信息
//	printf("两路正交编码器测试\r\n");

//	while (1) 
//	{		
//		printf("*AB:%5d CD:%5d \r\n",
//		AX_ENCODER_AB_GetCounter(),AX_ENCODER_CD_GetCounter());  
//		AX_Delayms(300);
//	}
//}	



///******************************************************************************
//例程名称：舵机控制例程
//例程说明：控制8路舵机30度、90度、150度间隔运动
//操作说明：可在8路舵机接口中任意一路插入舵机，舵机即可循环30°、90°、150°运动，
//         如果插入多路舵机，或舵机负载扭矩大，请注意电源供电能力
//*******************************************************************************/
//int main(void)
//{
//	//设置中断优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//调试串口初始化
//	AX_UART_DB_Init(115200); //调试串口
//	printf("  \r\n"); //输出空格，CPUBUG
//	
//	//JTAG口设置
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口 
//	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试 		
//	
//	//软件延时初始化
//	AX_DELAY_Init();
//  AX_LED_Init();
//	
//	//初始化
//	AX_SERVO_AB_Init();
//    AX_SERVO_CD_Init();
//	AX_SERVO_EFGH_Init();

//	
//	//提示信息
//	printf("八路舵机控制测试\r\n");

//	while (1) 
//	{		
//		printf("*30度...... \r\n");		
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
//		printf("*90度...... \r\n");
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
//		printf("*150度...... \r\n");
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
//例程名称：CAN通信数据收发例程
//例程说明：通过CAN接口实现数据收发，收到数据后通过USB串口输出显示
//操作说明：CAN参数，波特率为1M,标准帧数据
//         接收到帧ID为0x02的数据，发送一帧数据
//*******************************************************************************/
//int main(void)
//{
//	int8_t ax8 = 100;
//	int16_t ax16 = 0x1000;
//	int32_t ax32 = -123456;
//	uint8_t tx_buf[10];
//	uint8_t comdata[10];  //通信数据
//	
//	//设置中断优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	
//	//调试串口初始化
//	AX_UART_DB_Init(115200); //调试串口
//	printf("  \r\n"); //输出空格，CPUBUG
//	
//	//JTAG口设置
//	AX_JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG接口
//	AX_JTAG_Set(SWD_ENABLE);  //打开SWD接口 可以利用主板的SWD接口调试
//	
//	//软件延时初始化
//	AX_DELAY_Init();
//  AX_LED_Init();
//	
//	//CAN接口初始化
//	AX_CAN_Init();
//	
//	//数据封装示例
//	tx_buf[0] = (*((uint8_t *)(&ax32) + 3)); //32位整形,高位
//	tx_buf[1] = (*((uint8_t *)(&ax32) + 2)); 
//	tx_buf[2] = (*((uint8_t *)(&ax32) + 1)); 
//	tx_buf[3] = (*(uint8_t *)(&ax32));		
//	tx_buf[4] = (*((uint8_t *)(&ax16) + 1)); //16位整形,高位
//	tx_buf[5] = (*(uint8_t *)(&ax16));
//	tx_buf[6] = (uint8_t)ax8;  //8位整形

//	while (1)
//	{
//		//接收CAN数据
//		if(AX_CAN_GetRxData(comdata))
//		{
//			//USB串口输出CAN接收的数据
//			printf("RX：ID-%02X DATA-%02X %02X %02X %02X %02X %02X %02X %02X\r\n",comdata[0],
//			comdata[1],comdata[2],comdata[3],comdata[4],comdata[5],comdata[6],comdata[7],comdata[8]);	
//			
//			//如果帧标识为2，发发送一帧数据
//			if(comdata[0] == 0x02)
//			{
//				AX_CAN_SendPacket(tx_buf,7,0x01);  //帧号为0x01
//				ax8++;  //数据变化展示
//				tx_buf[6] = (uint8_t)ax8;  				
//			}
//		}
//		AX_Delayms(10);
//	}
//}	
