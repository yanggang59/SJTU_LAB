#include "stm32f10x.h"
#include "bsp_GeneralTim.h"  
#include "bsp_BaseTim.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_exti.h" 
#include "bsp_led.h"
#include "bsp_SysTick.h"
#include "bsp_LCD12864.h"

/*转速的flag,flag的值,在串口中断里面修改
*0:
*1:
*2:
*3:
*4:
*5:停止电机转动
*default:
*/
int flag=0;


/*
是否修改转速的flag，只有当收到指令的时候才会去修改转速
*/
int rec_flag=0;


/*是否是第一次开机*/
int start=1;

//int delay_time=0;

/*通用定时器相关*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	/*ADC 初始化*/
	ADCx_Init();
	
	/*基本定时器初始化*/
	BASIC_TIM_Init();
	
	/* 通用定时器初始化 */
	GENERAL_TIM_Init();
		
	  /*初始化USART1*/
  Debug_USART_Config();

	
	/* 初始化EXTI中断，按下按键会触发中断，
  *  触发中断会进入stm32f4xx_it.c文件中的函数
	*  KEY1_IRQHandler和KEY2_IRQHandler，处理中断
	*/
	EXTI_Key_Config(); 
	
	
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();
	
	LCD12864_Init();
	
  while(1)
  {  
		if(rec_flag)
		{			
		rec_flag=0;
		
		switch (flag)
			{	
				case 0:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,1000,60);
					TIM_TimeBaseStructure.TIM_Period=999;
					TIM_OCInitStructure.TIM_Pulse = 500;
					LCD12864_Display_Words(0, 0, "Flag is 0");
					LCD12864_Display_Words(1, 0, "PWM is 1000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 60 r/n");	
					break;
				case 1:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,2000,120);
					TIM_TimeBaseStructure.TIM_Period=499;
					TIM_OCInitStructure.TIM_Pulse = 250;
					LCD12864_Display_Words(0, 0, "Flag is 1");
					LCD12864_Display_Words(1, 0, "PWM is 2000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 120 r/n");	
					break;
				case 2:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,3000,180);
					TIM_TimeBaseStructure.TIM_Period=333;
					TIM_OCInitStructure.TIM_Pulse = 160;
					LCD12864_Display_Words(0, 0, "Flag is 2");
					LCD12864_Display_Words(1, 0, "PWM is 3000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 180 r/n");	
					break;
				case 3:
					printf("flag是 %d ,现在的脉冲是%d HZ ,转速是 %d r/min \r\n ",flag,4000,240);
					TIM_TimeBaseStructure.TIM_Period=249;
					TIM_OCInitStructure.TIM_Pulse = 125;
					LCD12864_Display_Words(0, 0, "Flag is 3");
					LCD12864_Display_Words(1, 0, "PWM is 4000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 240 r/n");
					break;
				case 4:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,5000,300);
					TIM_TimeBaseStructure.TIM_Period=199;
					TIM_OCInitStructure.TIM_Pulse = 100;
					LCD12864_Display_Words(0, 0, "Flag is 4");
					LCD12864_Display_Words(1, 0, "PWM is 5000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 300 r/n");
					break;
				case 5:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,6000,360);
					TIM_TimeBaseStructure.TIM_Period=167;
					TIM_OCInitStructure.TIM_Pulse = 83;
					LCD12864_Display_Words(0, 0, "Flag is 5");
					LCD12864_Display_Words(1, 0, "PWM is 6000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 360 r/n");
					break;
				case 6:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,7000,420);
					TIM_TimeBaseStructure.TIM_Period=143;
					TIM_OCInitStructure.TIM_Pulse = 71;
					LCD12864_Display_Words(0, 0, "Flag is 6");
					LCD12864_Display_Words(1, 0, "PWM is 7000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 420 r/n");
				case 7:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,8000,480);
					TIM_TimeBaseStructure.TIM_Period=125;
					TIM_OCInitStructure.TIM_Pulse = 62;
					LCD12864_Display_Words(0, 0, "Flag is 7");
					LCD12864_Display_Words(1, 0, "PWM is 8000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 480 r/n");
				case 8:
					printf("flag是 %d ,现在的脉冲是%d HZ,转速是 %d r/min \r\n ",flag,9000,540);
					TIM_TimeBaseStructure.TIM_Period=111;
					TIM_OCInitStructure.TIM_Pulse = 50;
					LCD12864_Display_Words(0, 0, "Flag is 8");
					LCD12864_Display_Words(1, 0, "PWM is 9000 HZ");					
					LCD12864_Display_Words(2, 0, "Speed is 540 r/n");
				
				default:
					printf("这是默认的情况 \r\n");
					break;			
			}				
			TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
			
			TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
			
			TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);				
		}
		
		
		
		LED1( ON ); 
		SysTick_Delay_Ms( 1000 );
		LED1( OFF );
	  
		LED2( ON );
		SysTick_Delay_Ms( 1000 );
		LED2( OFF );
	
		LED3( ON );
		SysTick_Delay_Ms( 1000 );
		LED3( OFF );
		
		
		
		
	}
			
}
/*********************************************END OF FILE**********************/
