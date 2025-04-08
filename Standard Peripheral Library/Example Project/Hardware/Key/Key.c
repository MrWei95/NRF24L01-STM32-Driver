#include "Key/Key.h"

/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：是否按按键
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
	{
		Delay_ms(20);											// 延时消抖
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0);	// 等待按键松手
		Delay_ms(20);											// 延时消抖
		KeyNum = 1;
	}
	return KeyNum;
}
