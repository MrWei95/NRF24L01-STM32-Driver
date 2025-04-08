#include "main.h"
#include "Key/Key.h"
#include "OLED/OLED.h"
#include "NRF24L01/NRF24L01.h"

void Check_RXdata(uint8_t Buf[]);
uint8_t Flag = 0;
uint8_t KeyNum;


int main(void)
{
	Key_Init();
	OLED_Init();
	NRF24L01_Init();
	
	#ifdef	NRF24L01_TX_MODE
	uint8_t Wireless_TXdata[32] = {0xFF, 0xFE, 0x00, 0x00, 0xEE, 0xED};
	OLED_ShowString(0, 0, "TX Mode", OLED_8X16);
	OLED_Update();
	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum)
		{
			Wireless_TXdata[2]++;
			Wireless_TXdata[3]++;
			NRF24L01_Send(Wireless_TXdata);
			OLED_ShowHexNum(0, 32, Wireless_TXdata[2], 2, OLED_8X16);
			OLED_ShowHexNum(30, 32, Wireless_TXdata[3], 2, OLED_8X16);
			OLED_Update();
		}
	}
	#endif
	
	#ifdef	NRF24L01_RX_MODE
	uint8_t Wireless_RXBuf[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	OLED_ShowString(0, 0, "RX Mode", OLED_8X16);
	OLED_Update();
	while (1)
	{
		if(NRF24L01_R_IRQ() == 0)
		{
			NRF24L01_Receive(Wireless_RXBuf);
			Check_RXdata(Wireless_RXBuf);
			
			if (Flag == 1)
			{
				Flag = 0;
				OLED_ShowHexNum(0, 16, Wireless_RXBuf[0], 2, OLED_8X16);
				OLED_ShowHexNum(30, 16, Wireless_RXBuf[1], 2, OLED_8X16);
				OLED_ShowHexNum(0, 32, Wireless_RXBuf[2], 2, OLED_8X16);
				OLED_ShowHexNum(30, 32, Wireless_RXBuf[3], 2, OLED_8X16);
				OLED_ShowHexNum(0, 48, Wireless_RXBuf[4], 2, OLED_8X16);
				OLED_ShowHexNum(30, 48, Wireless_RXBuf[5], 2, OLED_8X16);
				OLED_Update();
			}
		}
	}
	#endif
}


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
