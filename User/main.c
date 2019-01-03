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
�Ƿ��޸�ת�ٵ�flag��ֻ�е��յ�ָ���ʱ��Ż�ȥ�޸�ת��
*/
int rec_flag=0;


/*�Ƿ��ǵ�һ�ο���*/
int start=1;

//int delay_time=0;

/*ͨ�ö�ʱ�����*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;



// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	// ADC ��ʼ��,��������������������ֵ
	ADCx_Init();
	
	/*������ʱ����ʼ��*/
	BASIC_TIM_Init();
	
	/* ͨ�ö�ʱ����ʼ�� */
	GENERAL_TIM_Init();
		
	  /*��ʼ��USART1*/
  Debug_USART_Config();

	
	/*��ʱȥ�������Ĺ���*/
	
	/* ��ʼ��EXTI�жϣ����°����ᴥ���жϣ�
  *  �����жϻ����stm32f4xx_it.c�ļ��еĺ���
	*  KEY1_IRQHandler��KEY2_IRQHandler�������ж�
	*/
	//EXTI_Key_Config(); 
	
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();
	
	LCD12864_Init();
	
  while(1)
  {  
		//ֻ�е��յ�����ʱ�Ż����ת�ٺʹ�ӡ��ʾת��
		if(rec_flag)
		{			
		  rec_flag=0;
		
			switch (flag)
				{	
					case 0:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,1000,60);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=999;
						TIM_OCInitStructure.TIM_Pulse = 500;
						LCD12864_Display_Words(0, 0, "Flag is 0");
						LCD12864_Display_Words(1, 0, "PWM is 1000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 60 r/n");	
						break;
					case 1:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,2000,120);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=499;
						TIM_OCInitStructure.TIM_Pulse = 250;
						LCD12864_Display_Words(0, 0, "Flag is 1");
						LCD12864_Display_Words(1, 0, "PWM is 2000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 120 r/n");	
						break;
					case 2:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,3000,180);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=333;
						TIM_OCInitStructure.TIM_Pulse = 160;
						LCD12864_Display_Words(0, 0, "Flag is 2");
						LCD12864_Display_Words(1, 0, "PWM is 3000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 180 r/n");	
						break;
					case 3:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,4000,240);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=249;
						TIM_OCInitStructure.TIM_Pulse = 125;
						LCD12864_Display_Words(0, 0, "Flag is 3");
						LCD12864_Display_Words(1, 0, "PWM is 4000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 240 r/n");
						break;
					case 4:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,5000,300);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=199;
						TIM_OCInitStructure.TIM_Pulse = 100;
						LCD12864_Display_Words(0, 0, "Flag is 4");
						LCD12864_Display_Words(1, 0, "PWM is 5000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 300 r/n");
						break;
					case 5:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,6000,360);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=167;
						TIM_OCInitStructure.TIM_Pulse = 83;
						LCD12864_Display_Words(0, 0, "Flag is 5");
						LCD12864_Display_Words(1, 0, "PWM is 6000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 360 r/n");
						break;
					case 6:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,7000,420);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=143;
						TIM_OCInitStructure.TIM_Pulse = 71;
						LCD12864_Display_Words(0, 0, "Flag is 6");
						LCD12864_Display_Words(1, 0, "PWM is 7000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 420 r/n");
						break;
					case 7:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,8000,480);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=125;
						TIM_OCInitStructure.TIM_Pulse = 62;
						LCD12864_Display_Words(0, 0, "Flag is 7");
						LCD12864_Display_Words(1, 0, "PWM is 8000 HZ");
						LCD12864_Display_Words(2, 0, "Speed is 480 r/n");
						break;
					case 8:
						printf("flag is %d ,PWM is %d HZ,Speed is %d r/min \r\n ",flag,9000,540);
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ��
						TIM_TimeBaseStructure.TIM_Period=111;
						TIM_OCInitStructure.TIM_Pulse = 50;
						LCD12864_Display_Words(0, 0, "Flag is 8");
						LCD12864_Display_Words(1, 0, "PWM is 9000 HZ");					
						LCD12864_Display_Words(2, 0, "Speed is 540 r/n");
						break;
					case 9:
						printf("Stopped \n");
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;   //ʧ��
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
		
		
		// 1-PC0 ��ָ��������ӵ��Ƿ�������Ĭ�ϱ�����
    // 2-PC0 ��ָ��������ӵ���SPI FLASH�� Ƭѡ��Ĭ�ϱ�����
    // ���� PC0 �� ADC ת��ͨ����ʱ�򣬽�����ܻ������
		//PC1���˻��������������ѡ�� PC2 PC3 PC4 PC5
		//ת��֮��ĵ�ѹֵ 0-3.3V֮�䣬PC2,PC3,PC4,PC5

		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
		ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;

	
		//ʹ�õ�����������Ϊ0-50Kg����Ӧ�ĵ�ѹֵ��0-3.3V,��ʱʹ�� ADC1 �� PC2,PC3,PC4 ,PC5 �ĸ�ͨ��,ע�⣺��ʹ��PC0
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
