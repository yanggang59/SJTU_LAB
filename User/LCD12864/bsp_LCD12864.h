#ifndef __LCD12864_H
#define	__LCD12864_H
#include "stm32f10x.h"
/* Definitions ---------------------------------------------------------------*/
	//接口输出操作(SID: PA2  SCLK: PA3) 
	#define LCD12864_SID_OUT(x)		(x) ? (GPIOA->BSRR |= 1<<2) : (GPIOA->BRR |= 1<<2)
	#define LCD12864_SCLK_OUT(x)	(x) ? (GPIOA->BSRR |= 1<<3) : (GPIOA->BRR |= 1<<3)

	/* Write command or dat select */
	#define WRITE_CMD	0xF8//写命令
	#define WRITE_DAT	0xFA//写数据

/* Exported functions declared ---------------------------------------------- */
void LCD12864_Init(void);	  	//液晶初始化函数
void LCD12864_Clear(void);					//液晶清屏
void LCD12864_Display_Words(u8 x, u8 y, u8 *str);	//液晶字符显示函数
void LCD12864_Display_Picture(u8 *pic);				//液晶图片显示函数

#endif


