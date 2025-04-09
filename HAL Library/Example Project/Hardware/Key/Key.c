#include "Key/Key.h"

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：是否按按键
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if (HAL_GPIO_ReadPin(Key_GPIO_Port, Key_Pin) == 0)
	{
		Delay_ms(20);												// 延时消抖
		while (HAL_GPIO_ReadPin(Key_GPIO_Port, Key_Pin) == 0);		// 等待按键松手
		Delay_ms(20);												// 延时消抖
		KeyNum = 1;
	}
	return KeyNum;
}
