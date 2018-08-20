/* Includes ------------------------------------------------------------------*/
#include "bsp_LCD12864.h"
#include "bsp_SysTick.h"		

/* Private variables ---------------------------------------------------------*/
	/* 字符显示RAM地址 */
	u8 LCD12864_DDRAM_ADDR[4][8]={
	{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},  		//第一行
	{0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},		//第二行
	{0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},		//第三行
	{0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F}		//第四行
	};


/* Private functions declared ------------------------------------------------*/
	void LCD12864_SendByte(u8 Byte);
	void LCD12864_Write(u8 writeSelect, u8 cmdOrDat);
	void LCD12864_Init(void);
/* Exported functions ------------------------------------------------------- */
	/**
	  * @brief  Initialize the LCD12864.
	  * @param  None
	  * @retval None
	  */
	void LCD12864_Init(void)
	{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		SysTick_Delay_Ms(50);		//等待液晶自检（延时>40ms）
		LCD12864_Write(WRITE_CMD, 0x30);		//功能设定
		SysTick_Delay_Us(150);		//延时>100us
					   
		LCD12864_Write(WRITE_CMD, 0x30);		//功能设定
		SysTick_Delay_Us(40);		//延时>37us
	
		LCD12864_Write(WRITE_CMD, 0x0C);		//开显示
		SysTick_Delay_Us(150);		//延时>100us
	
		LCD12864_Write(WRITE_CMD, 0x01);		//清屏
		SysTick_Delay_Ms(15);		//延时>10ms
	
		LCD12864_Write(WRITE_CMD, 0x06);		//进入设定点，初始化完成
	}

	/**
	  * @brief  Clear the screen.
	  * @param  None
	  * @retval None
	  */
	void LCD12864_Clear(void)
	{
		LCD12864_Write(WRITE_CMD, 0x01);			//清屏指令
		SysTick_Delay_Ms(2);				//延时以待液晶稳定【至少1.6ms】
	}

	/**
	  * @brief  LCD12864 display words.
	  * @param  x: row(0~3)  y: line(0~7)  str: the pointer to words
	  * @retval None
	  */
	void LCD12864_Display_Words(u8 x, u8 y, u8 *str)
	{
		LCD12864_Write(WRITE_CMD, LCD12864_DDRAM_ADDR[x][y]);
		while(*str)
		{
			LCD12864_Write(WRITE_DAT, *str);
			str++;
		}
	}

	/**
	  * @brief  LCD12864 display picture.
	  * @param  pic: The pointer to the picture array.
	  * @retval None
	  */
	void LCD12864_Display_Picture(u8 *pic)
	{
		u8 x,y,i;
		LCD12864_Write(WRITE_CMD, 0x34);		//切换到扩充指令
		LCD12864_Write(WRITE_CMD, 0x34);		//关闭图形显示
		for(i = 0; i < 9; i = i+8)
		{
			for(y=0;y<32;y++)
			{
				for(x=0;x<8;x++)
				{
					LCD12864_Write(WRITE_CMD, 0x80 + y);		//行地址
					LCD12864_Write(WRITE_CMD, 0x80 + x+i);		//列地址
					LCD12864_Write(WRITE_DAT, *pic ++);		//写数据 D15－D8
					LCD12864_Write(WRITE_DAT, *pic ++);		//写数据 D7－D0
				}
			}
		}
		LCD12864_Write(WRITE_CMD, 0x36);				//打开图形显示		
		LCD12864_Write(WRITE_CMD, 0x30);        //切换回基本指令
	}		 


/* Private functions -------------------------------------------------------- */
	/**
	  * @brief	Transmit single byte in TWO_WIRE_SERIAL_CONTROL.  
	  * @param  Byte: The byte to be written.
	  * @retval None
	  */  
	void LCD12864_SendByte(u8 Byte)
	{
		u8 i;
		for(i = 0; i < 8; i++)
		{
			LCD12864_SCLK_OUT(0);			//时钟线置低
			LCD12864_SID_OUT(Byte & (0x80>>i));	//将一字节数据送到数据总线
			LCD12864_SCLK_OUT(1);			//装载数据
			LCD12864_SCLK_OUT(0);
		}
	}


	/**
	  * @brief  LCD12864 write command or data.
	  * @param  writeSelect: Select to write command or data.
	  *   This parameter can be one of the following values:
	  *     @arg WRITE_CMD: Select to write command
	  *     @arg WRITE_DAT: Select to write data
	  * @param  cmdOrDat: The command or data to be written.
	  * @retval None
	  */  
	void LCD12864_Write(u8 writeSelect, u8 cmdOrDat)
	{
		SysTick_Delay_Ms(1);
		LCD12864_SendByte(writeSelect);				//写指令【RW=0，RS=0】
		LCD12864_SendByte(0xF0 & cmdOrDat);		//写高4位
		LCD12864_SendByte(0xF0 & cmdOrDat << 4);	//写低4位
	}











