# 标准库
## 驱动说明
驱动使用硬件SPI与模块通讯，未添加DMA（暂时没必要），支持发送数据包。
可在**NRF24L01.c**中自定义地址：
```C
uint8_t NRF24L01_Send_ADDR[5] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
uint8_t NRF24L01_Receive_ADDR[5] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
```

## 例程说明
例程使用STM32F103C8T6验证可行性。
两个单片机上电后发送机按下按钮自动发送六位数据包，每次按下后数据包数据均改变，包头为```FF FE```，包尾为```EE ED```，接收机在屏幕上显示接收数据包。
**main.c**中写了一个极其简单的数据包校验函数：
```C
/**** 
	* 函    数：校验数据包
	* 参    数：Buf[]：接收的数据包
	* 返 回 值：无
	* 说    明：包头：FF FE 包尾：EE ED
	*/
void Check_RXdata(uint8_t Buf[])
{
	if (Buf[0] == 0xFF && Buf[1] == 0xFE)
	{
		if (Buf[4] == 0xEE && Buf[5] == 0xED)
		{
			Flag = 1;
		}
	}
}
```
例程为发送 + 接收二合一代码，使用```NRF24L01_MODE```控制模式，具体实现：
```C
// 控制NRF24L01收发模式
#define		WIRELESS_MODE			0

#if WIRELESS_MODE == 0
#define		NRF24L01_TX_MODE		// 发送模式
#else
#define		NRF24L01_RX_MODE		// 接收模式
#endif
```

其他的想到再写吧，有问题可以联系[我B站](https://space.bilibili.com/2004315025)或者发邮件到mrwei95@outlook.com。
