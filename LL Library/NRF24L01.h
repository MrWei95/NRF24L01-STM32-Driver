#ifndef _NRF24L01_H
#define _NRF24L01_H

#include "main.h"

// 寄存器地址代码
#define		NRF24L01_CONFIG			0x00
#define		NRF24L01_EN_AA			0x01
#define		NRF24L01_EN_RXADDR		0x02
#define		NRF24L01_SETUP_AW		0x03
#define		NRF24L01_SETUP_RETR		0x04
#define		NRF24L01_RF_CH			0x05
#define		NRF24L01_RF_SETUP		0x06
#define		NRF24L01_STATUS			0x07
#define		NRF24L01_OBSERVE_TX		0x08
#define		NRF24L01_CD				0x09
#define		NRF24L01_RX_ADDR_P0		0x0A
#define		NRF24L01_RX_ADDR_P1		0x0B
#define		NRF24L01_RX_ADDR_P2		0x0C
#define		NRF24L01_RX_ADDR_P3		0x0D
#define		NRF24L01_RX_ADDR_P4		0x0E
#define		NRF24L01_RX_ADDR_P5		0x0F
#define		NRF24L01_TX_ADDR		0x10
#define		NRF24L01_RX_PW_P0		0x11
#define		NRF24L01_RX_PW_P1		0x12
#define		NRF24L01_RX_PW_P2		0x13
#define		NRF24L01_RX_PW_P3		0x14
#define		NRF24L01_RX_PW_P4		0x15
#define		NRF24L01_RX_PW_P5		0x16
#define		NRF24L01_FIFO_STATUS	0x17
#define		NRF24L01_DYNPD			0x1C
#define		NRF24L01_FEATURE		0x1D

// 操作指令代码
#define		NRF24L01_R_REGISTER		0x00
#define		NRF24L01_W_REGISTER		0x20
#define		NRF24L01_R_RX_PAYLOAD	0x61
#define		NRF24L01_W_TX_PAYLOAD	0xA0
#define		NRF24L01_FLUSH_TX		0xE1
#define		NRF24L01_FLUSH_RX		0xE2
#define		NRF24L01_NOP			0xFF

// 状态
#define		NRF24L01_RX_OK			0x40
#define		NRF24L01_TX_OK			0x20
#define		NRF24L01_MAX_TX			0x10

// IO口定义
#define		NRF24L01_CSN_SET		LL_GPIO_SetOutputPin(NRF24L01_CSN_GPIO_Port, NRF24L01_CSN_Pin)
#define		NRF24L01_CSN_RESET		LL_GPIO_ResetOutputPin(NRF24L01_CSN_GPIO_Port, NRF24L01_CSN_Pin)
#define		NRF24L01_CE_SET			LL_GPIO_SetOutputPin(NRF24L01_CE_GPIO_Port, NRF24L01_CE_Pin)
#define		NRF24L01_CE_RESET		LL_GPIO_ResetOutputPin(NRF24L01_CE_GPIO_Port, NRF24L01_CE_Pin)

uint8_t NRF24L01_R_IRQ(void);
void NRF24L01_W_Reg(uint8_t Reg, uint8_t Value);
uint8_t NRF24L01_R_Reg(uint8_t Reg);
void NRF24L01_W_Buf(uint8_t Reg, uint8_t* Buf, uint8_t Len);
void NRF24L01_R_Buf(uint8_t Reg, uint8_t* Buf, uint8_t Len);

void NRF24L01_Init(void);

void NRF24L01_Receive(uint8_t* Buf);
uint8_t NRF24L01_Send(uint8_t* Buf);

#endif
