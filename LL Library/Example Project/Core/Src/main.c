/* USER CODE BEGIN Header */
/**** 
	* 本程序由MrWei95开源共享
	* 部分代码由STM32CubeMX生成
	*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Key/Key.h"
#include "OLED/OLED.h"
#include "NRF24L01/NRF24L01.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

void Check_RXdata(uint8_t Buf[]);

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t Flag = 0;
uint8_t KeyNum;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

	OLED_Init();
	NRF24L01_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		#ifdef	NRF24L01_TX_MODE
		uint8_t Wireless_TXdata[32] = {0xFF, 0xFE, 0x00, 0x00, 0xEE, 0xED};
		OLED_ShowString(0, 0, "TX Mode", OLED_8X16);
		OLED_Update();
		while (1)
		{
			KeyNum = Key_GetNum();
			if (KeyNum)
			{
				NRF24L01_Send(Wireless_TXdata);
				OLED_ShowHexNum(0, 32, Wireless_TXdata[2], 2, OLED_8X16);
				OLED_ShowHexNum(30, 32, Wireless_TXdata[3], 2, OLED_8X16);
				OLED_Update();
				Wireless_TXdata[2]++;
				Wireless_TXdata[3]++;
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
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(72000000);
  LL_SetSystemCoreClock(72000000);
}

/* USER CODE BEGIN 4 */

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

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
