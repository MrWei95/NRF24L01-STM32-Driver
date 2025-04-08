#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

// 控制NRF24L01收发模式
#define		NRF24L01_MODE			0

#if NRF24L01_MODE == 0
#define		NRF24L01_TX_MODE		// 发送模式
#else
#define		NRF24L01_RX_MODE		// 接收模式
#endif

#endif
