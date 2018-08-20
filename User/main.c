#include "stm32f10x.h"
#include "bsp_GeneralTim.h"  
#include "bsp_BaseTim.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_exti.h" 
#include "bsp_led.h"
#include "bsp_SysTick.h"
#include "bsp_LCD12864.h"

/*ת�ٵ�flag,flag��ֵ,�ڴ����ж������޸�
*0:
*1:
*2:
*3:
*4:
*5:ֹͣ���ת��
*default:
*/
int flag=0;


/*
�Ƿ��޸�ת�ٵ�flag��ֻ�е��յ�ָ���ʱ��Ż�ȥ�޸�ת��
*/
int rec_flag=0;


/*�Ƿ��ǵ�һ�ο���*/
int start=1;

//int delay_time=0;

/*ͨ�ö�ʱ�����*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	/*ADC ��ʼ��*/
	ADCx_Init();
	
	/*������ʱ����ʼ��*/
	BASIC_TIM_Init();
	
	/* ͨ�ö�ʱ����ʼ�� */
	GENERAL_TIM_Init();
		
	  /*��ʼ��USART1*/
  Debug_USART_Config();

	
	/* ��ʼ��EXTI�жϣ����°����ᴥ���жϣ�
  *  �����жϻ����stm32f4xx_it.c�ļ��еĺ���
	*  KEY1_IRQHandler��KEY2_IRQHandler�������ж�
	*/
	EXTI_Key_Config(); 
	
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
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
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,1000,60);
					TIM_TimeBaseStructure.TIM_Period=999;
					TIM_OCInitStructure.TIM_Pulse = 500;
					LCD12864_Display_Words(0, 0, "Flag is 0");
					LCD12864_Display_Words(1, 0, "PWM is 1000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 60 r/n");	
					break;
				case 1:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,2000,120);
					TIM_TimeBaseStructure.TIM_Period=499;
					TIM_OCInitStructure.TIM_Pulse = 250;
					LCD12864_Display_Words(0, 0, "Flag is 1");
					LCD12864_Display_Words(1, 0, "PWM is 2000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 120 r/n");	
					break;
				case 2:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,3000,180);
					TIM_TimeBaseStructure.TIM_Period=333;
					TIM_OCInitStructure.TIM_Pulse = 160;
					LCD12864_Display_Words(0, 0, "Flag is 2");
					LCD12864_Display_Words(1, 0, "PWM is 3000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 180 r/n");	
					break;
				case 3:
					printf("flag�� %d ,���ڵ�������%d HZ ,ת���� %d r/min \r\n ",flag,4000,240);
					TIM_TimeBaseStructure.TIM_Period=249;
					TIM_OCInitStructure.TIM_Pulse = 125;
					LCD12864_Display_Words(0, 0, "Flag is 3");
					LCD12864_Display_Words(1, 0, "PWM is 4000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 240 r/n");
					break;
				case 4:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,5000,300);
					TIM_TimeBaseStructure.TIM_Period=199;
					TIM_OCInitStructure.TIM_Pulse = 100;
					LCD12864_Display_Words(0, 0, "Flag is 4");
					LCD12864_Display_Words(1, 0, "PWM is 5000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 300 r/n");
					break;
				case 5:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,6000,360);
					TIM_TimeBaseStructure.TIM_Period=167;
					TIM_OCInitStructure.TIM_Pulse = 83;
					LCD12864_Display_Words(0, 0, "Flag is 5");
					LCD12864_Display_Words(1, 0, "PWM is 6000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 360 r/n");
					break;
				case 6:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,7000,420);
					TIM_TimeBaseStructure.TIM_Period=143;
					TIM_OCInitStructure.TIM_Pulse = 71;
					LCD12864_Display_Words(0, 0, "Flag is 6");
					LCD12864_Display_Words(1, 0, "PWM is 7000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 420 r/n");
				case 7:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,8000,480);
					TIM_TimeBaseStructure.TIM_Period=125;
					TIM_OCInitStructure.TIM_Pulse = 62;
					LCD12864_Display_Words(0, 0, "Flag is 7");
					LCD12864_Display_Words(1, 0, "PWM is 8000 HZ");
					LCD12864_Display_Words(2, 0, "Speed is 480 r/n");
				case 8:
					printf("flag�� %d ,���ڵ�������%d HZ,ת���� %d r/min \r\n ",flag,9000,540);
					TIM_TimeBaseStructure.TIM_Period=111;
					TIM_OCInitStructure.TIM_Pulse = 50;
					LCD12864_Display_Words(0, 0, "Flag is 8");
					LCD12864_Display_Words(1, 0, "PWM is 9000 HZ");					
					LCD12864_Display_Words(2, 0, "Speed is 540 r/n");
				
				default:
					printf("����Ĭ�ϵ���� \r\n");
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
