/* USER CODE BEGIN Header */
/**** 
	* 本程序由MrWei95开源共享
	* 部分代码由STM32CubeMX生成
	*/
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_ll_i2c.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Delay.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NRF24L01_CSN_Pin LL_GPIO_PIN_4
#define NRF24L01_CSN_GPIO_Port GPIOA
#define NRF24L01_SCK_Pin LL_GPIO_PIN_5
#define NRF24L01_SCK_GPIO_Port GPIOA
#define NRF24L01_MISO_Pin LL_GPIO_PIN_6
#define NRF24L01_MISO_GPIO_Port GPIOA
#define NRF24L01_MOSI_Pin LL_GPIO_PIN_7
#define NRF24L01_MOSI_GPIO_Port GPIOA
#define NRF24L01_CE_Pin LL_GPIO_PIN_0
#define NRF24L01_CE_GPIO_Port GPIOB
#define NRF24L01_IRQ_Pin LL_GPIO_PIN_1
#define NRF24L01_IRQ_GPIO_Port GPIOB
#define Key_Pin LL_GPIO_PIN_8
#define Key_GPIO_Port GPIOA
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */


// 控制NRF24L01收发模式
#define	NRF24L01_MODE	0

#if NRF24L01_MODE == 0
#define		NRF24L01_TX_MODE		// 发送模式
#else
#define		NRF24L01_RX_MODE		// 接收模式
#endif


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
