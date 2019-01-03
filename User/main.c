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
*0:   60r/min
*1:		120r/min
*2:		180r/min
*3:		240r/min
*4:		300r/min
*5:		360r/min
*6		420r/min
*7		480r/min
*8		540r/min
*9		stop
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



// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	// ADC 初始化,用来测量重量传感器的值
	ADCx_Init();
	
	/*基本定时器初始化*/
	BASIC_TIM_Init();
	
	/* 通用定时器初始化 */
	GENERAL_TIM_Init();
		
	  /*初始化USART1*/
  Debug_USART_Config();

	
	/*暂时去除按键的功能*/
	
	/* 初始化EXTI中断，按下按键会触发中断，
  *  触发中断会进入stm32f4xx_it.c文件中的函数
	*  KEY1_IRQHandler和KEY2_IRQHandler，处理中断
	*/
	//EXTI_Key_Config(); 
	
	
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();
	
	LCD12864_Init();
	
  while(1)
  {  
		//只有当收到数据时才会更改转速和打印显示转速
		if(rec_flag)
		{			
		  rec_flag=0;
		
			switch (flag)
				{	
					case 0:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,1000,60);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=999;
						TIM_OCInitStructure.TIM_Pulse = 500;
						LCD12864_Display_Words(0, 0, "Flag is 0");
						LCD12864_Display_Words(1, 0, "PWM is 1000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 60 r/n");	
						break;
					case 1:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,2000,120);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=499;
						TIM_OCInitStructure.TIM_Pulse = 250;
						LCD12864_Display_Words(0, 0, "Flag is 1");
						LCD12864_Display_Words(1, 0, "PWM is 2000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 120 r/n");	
						break;
					case 2:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,3000,180);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=333;
						TIM_OCInitStructure.TIM_Pulse = 160;
						LCD12864_Display_Words(0, 0, "Flag is 2");
						LCD12864_Display_Words(1, 0, "PWM is 3000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 180 r/n");	
						break;
					case 3:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,4000,240);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=249;
						TIM_OCInitStructure.TIM_Pulse = 125;
						LCD12864_Display_Words(0, 0, "Flag is 3");
						LCD12864_Display_Words(1, 0, "PWM is 4000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 240 r/n");
						break;
					case 4:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,5000,300);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=199;
						TIM_OCInitStructure.TIM_Pulse = 100;
						LCD12864_Display_Words(0, 0, "Flag is 4");
						LCD12864_Display_Words(1, 0, "PWM is 5000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 300 r/n");
						break;
					case 5:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,6000,360);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=167;
						TIM_OCInitStructure.TIM_Pulse = 83;
						LCD12864_Display_Words(0, 0, "Flag is 5");
						LCD12864_Display_Words(1, 0, "PWM is 6000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 360 r/n");
						break;
					case 6:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,7000,420);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=143;
						TIM_OCInitStructure.TIM_Pulse = 71;
						LCD12864_Display_Words(0, 0, "Flag is 6");
						LCD12864_Display_Words(1, 0, "PWM is 7000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 420 r/n");
						break;
					case 7:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,8000,480);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=125;
						TIM_OCInitStructure.TIM_Pulse = 62;
						LCD12864_Display_Words(0, 0, "Flag is 7");
						LCD12864_Display_Words(1, 0, "PWM is 8000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 480 r/n");
						break;
					case 8:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,9000,540);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
						TIM_TimeBaseStructure.TIM_Period=111;
						TIM_OCInitStructure.TIM_Pulse = 50;
						LCD12864_Display_Words(0, 0, "Flag is 8");
						LCD12864_Display_Words(1, 0, "PWM is 9000 HZ");					
						LCD12864_Display_Words(2, 0, "Speed is 540 r/n");
						break;
					case 9:
						printf("Stopped \n");
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;   //失能
						LCD12864_Display_Words(0, 0, "Flag is 9");
						LCD12864_Display_Words(1, 0, "Stopping");					
						LCD12864_Display_Words(2, 0, "Speed is 0 r/n");
						break;
					
					default:
						printf("Default Situation \r\n");
						break;			
				}				
			TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
			
			TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
			
			TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);				
		}
		
		
		
//		LED1( ON ); 
//		SysTick_Delay_Ms( 1000 );
//		LED1( OFF );
//	  
//		LED2( ON );
//		SysTick_Delay_Ms( 1000 );
//		LED2( OFF );
//	
//		LED3( ON );
//		SysTick_Delay_Ms( 1000 );
//		LED3( OFF );
		
		
		// 1-PC0 在指南者里面接的是蜂鸣器，默认被拉低
    // 2-PC0 在指南者里面接的是SPI FLASH的 片选，默认被拉高
    // 所以 PC0 做 ADC 转换通道的时候，结果可能会有误差
		//PC1连了滑动变阻器，因此选择 PC2 PC3 PC4 PC5
		//转换之后的电压值 0-3.3V之间，PC2,PC3,PC4,PC5

		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
		ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;

	
		//使用的重量传感器为0-50Kg，对应的电压值是0-3.3V,暂时使用 ADC1 的 PC2,PC3,PC4 ,PC5 四个通道,注意：不使用PC0
		float sum_voltage = ADC_ConvertedValueLocal[0]+ADC_ConvertedValueLocal[1]+ADC_ConvertedValueLocal[2]+ADC_ConvertedValueLocal[3] ;
		
		float weight = sum_voltage/3.3 * 50 ;
		
		printf("-----------------------------------------------------");
		
		printf("\r\n Weight is %f Kg \r\n",weight);
		
		printf("-----------------------------------------------------");
		
		printf("\r\n\r\n");
		
		SysTick_Delay_Ms( 1000 );		 
			
	}
			
}
/*********************************************END OF FILE**********************/
