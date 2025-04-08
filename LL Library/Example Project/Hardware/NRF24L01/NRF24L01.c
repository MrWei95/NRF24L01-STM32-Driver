#include "NRF24L01/NRF24L01.h"

uint8_t NRF24L01_Send_ADDR[5] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
uint8_t NRF24L01_Receive_ADDR[5] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0};


/**** 
	* 函    数：读取IRQ电平
	* 参    数：无
	* 返 回 值：1：高电平
				0：低电平
	* 说    明：用于判断是否有中断事件发生
	*/
uint8_t NRF24L01_R_IRQ(void)
{
	return LL_GPIO_IsInputPinSet(NRF24L01_IRQ_GPIO_Port, NRF24L01_IRQ_Pin) ? 1 : 0;
}


/**** 
	* 函    数：SPI交换一个字节
	* 参    数：Byte：字节数据
	* 返 回 值：无
	* 说    明：无
	*/
uint8_t NRF24L01_SPI_SwapByte(uint8_t Byte)
{
	while (!LL_SPI_IsActiveFlag_TXE(SPI1));
	LL_SPI_TransmitData8(SPI1, Byte);
	while (!LL_SPI_IsActiveFlag_RXNE(SPI1));
	return LL_SPI_ReceiveData8(SPI1);
}


/**** 
	* 函    数：写寄存器
	* 参    数：Reg：寄存器地址 Value：值
	* 返 回 值：无
	* 说    明：无
	*/
void NRF24L01_W_Reg(uint8_t Reg, uint8_t Value)
{
	NRF24L01_CSN_RESET;						// 表示选中NRF24L01
	NRF24L01_SPI_SwapByte(Reg);				// 交换的第一个字节就是指令
	NRF24L01_SPI_SwapByte(Value);			// 交换的第二个字节就是交换的数据
	NRF24L01_CSN_SET;						// 停止选中NRF24L01
}


/**** 
	* 函    数：读寄存器
	* 参    数：Reg：寄存器地址
	* 返 回 值：寄存器数据
	* 说    明：无
	*/
uint8_t NRF24L01_R_Reg(uint8_t Reg)
{
	uint8_t Value;
	NRF24L01_CSN_RESET;									// 表示选中NRF24L01
	NRF24L01_SPI_SwapByte(Reg);							// 交换的第一个字节就是指令
	Value = NRF24L01_SPI_SwapByte(NRF24L01_NOP);		// 交换的第二个字节就是交换的数据
	NRF24L01_CSN_SET;									// 停止选中NRF24L01
	return Value;
}


/**** 
	* 函    数：写数据包
	* 参    数：Reg：寄存器地址
				Buf：传递数据包数组
				Len：数据包长度
	* 返 回 值：无
	* 说    明：无
	*/
void NRF24L01_W_Buf(uint8_t Reg, uint8_t* Buf, uint8_t Len)
{
	uint8_t i;
	NRF24L01_CSN_RESET;									// 选中NRF24L01
	NRF24L01_SPI_SwapByte(Reg);
	for(i = 0; i < Len; i++)
		NRF24L01_SPI_SwapByte(Buf[i]);
	NRF24L01_CSN_SET;									// 停止选中NRF24L01
}


/**** 
	* 函    数：读数据包
	* 参    数：Reg：寄存器地址
				Buf：传递数据包数组
				Len：数据包长度
	* 返 回 值：无
	* 说    明：无
	*/
void NRF24L01_R_Buf(uint8_t Reg, uint8_t* Buf, uint8_t Len)
{
	uint8_t i;
	NRF24L01_CSN_RESET;									// 选中NRF24L01
	NRF24L01_SPI_SwapByte(Reg);
	for(i = 0; i<Len; i++)
		Buf[i] = NRF24L01_SPI_SwapByte(NRF24L01_NOP);
	NRF24L01_CSN_SET;									// 停止选中NRF24L01
}


/**** 
	* 函    数：NRF24L01初始化
	* 参    数：无
	* 返 回 值：无
	* 说    明：无
	*/
void NRF24L01_Init(void)
{
	LL_SPI_Enable(SPI1);
	
	NRF24L01_CE_RESET;
	
	NRF24L01_W_Buf(NRF24L01_W_REGISTER + NRF24L01_TX_ADDR, NRF24L01_Send_ADDR, 5);			// 配置发送地址
	NRF24L01_W_Buf(NRF24L01_W_REGISTER + NRF24L01_RX_ADDR_P0, NRF24L01_Receive_ADDR, 5);	// 配置接收通道0
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_CONFIG, 0x0F);							// 配置成接收模式
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_EN_AA, 0x01);								// 通道0开启自动应答
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_RF_CH, 0x00);								// 配置通信频率2.4G
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_RX_PW_P0, 32);							// 配置接收通道0接收的数据宽度32字节
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_EN_RXADDR, 0x01);							// 接收通道0使能
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_SETUP_RETR, 0x1A);						// 配置580us重发时间间隔,重发10次
	NRF24L01_W_Reg(NRF24L01_FLUSH_RX, NRF24L01_NOP);
	
	NRF24L01_CE_SET;
}


/**** 
	* 函    数：NRF24L01接收数据
	* 参    数：Buf：接收数据存放的数组
	* 返 回 值：无
	* 说    明：无
	*/
void NRF24L01_Receive(uint8_t* Buf)
{
	uint8_t Status;
	Status = NRF24L01_R_Reg(NRF24L01_R_REGISTER + NRF24L01_STATUS);
	if(Status & NRF24L01_RX_OK)
	{
		NRF24L01_R_Buf(NRF24L01_R_RX_PAYLOAD, Buf, 32);
		NRF24L01_W_Reg(NRF24L01_FLUSH_RX, NRF24L01_NOP);
		NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_STATUS, Status);
		Delay_us(150);
	}
}


/**** 
	* 函    数：NRF24L01发送数据
	* 参    数：Buf：接收数据存放的数组
	* 返 回 值：状态
	* 说    明：无
	*/
uint8_t NRF24L01_Send(uint8_t* Buf)
{
	uint8_t Status;
	NRF24L01_W_Buf(NRF24L01_W_TX_PAYLOAD, Buf, 32);						// 在发送数据缓存器发送要发送的数据
	
	NRF24L01_CE_RESET;
	NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_CONFIG, 0x0E);
	NRF24L01_CE_SET;

	while(NRF24L01_R_IRQ() == 1);										// 等待中断
	Status = NRF24L01_R_Reg(NRF24L01_R_REGISTER + NRF24L01_STATUS);
	
	if(Status & NRF24L01_MAX_TX)										// 如果发送达到最大次数
	{
		NRF24L01_W_Reg(NRF24L01_FLUSH_TX, NRF24L01_NOP);				// 清除发送数据缓存器
		NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_STATUS, Status);	// 中断位写1清除中断
		return NRF24L01_MAX_TX;
	}
	if(Status & NRF24L01_TX_OK)											// 如果发送成功,接收到应答信号
	{
		NRF24L01_W_Reg(NRF24L01_W_REGISTER + NRF24L01_STATUS, Status);	// 清除中断
		return NRF24L01_TX_OK;
	}
	return 0;
}
