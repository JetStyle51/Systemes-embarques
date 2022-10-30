/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
volatile uint32_t i;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us) //warning: this function is not reentrant
{
    __HAL_TIM_SET_COUNTER(&htim4,0); //reset the timer counter
	while (__HAL_TIM_GET_COUNTER(&htim4) < us);  // wait for the counter to reach the us value provided as an argument
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == htim1.Instance){
		//change the duty cycle of TIM2 whenever the TIM1 interrupt occurs.
		static uint8_t dir = 0; //direction: are we currently increasing duty cycle or currently decreasing?
		i = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1); //the period is 1000. Duty cycle should vary between 0 and 1000.

		if(dir == 0) { //change duty cycle by changing "i" by 1 in the positive or negative direction
			i--;
			if(i == 0) {
				dir = 1;
			}
		} else {
			i++;
			if(i == 1000) {
				dir = 0;
			}

		}
		//update the PWM control register
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, i);
	}


}

//First we define our note frequencies and delays via a conversion function, an enum, and our look-up-table array.
#define FREQ_TO_DELAY_US(x) (500000 / x)
typedef enum {
	note_a 		= 0,
	note_a_sh 	= 1,
	note_b 		= 2,
	note_c 		= 3,
	note_c_sh 	= 4,
	note_d 		= 5,
	note_d_sh 	= 6,
	note_e 		= 7,
	note_f 		= 8,
	note_f_sh 	= 9,
	note_g		= 10,
	note_g_sh	= 11
} note_enum;

#define SCALE_LEN 12
uint16_t note_delays_us[] = {
	FREQ_TO_DELAY_US(220),
	FREQ_TO_DELAY_US(233),
	FREQ_TO_DELAY_US(247),
	FREQ_TO_DELAY_US(262),
	FREQ_TO_DELAY_US(277),
	FREQ_TO_DELAY_US(294),
	FREQ_TO_DELAY_US(311),
	FREQ_TO_DELAY_US(330),
	FREQ_TO_DELAY_US(349),
	FREQ_TO_DELAY_US(370),
	FREQ_TO_DELAY_US(392),
	FREQ_TO_DELAY_US(415),
	FREQ_TO_DELAY_US(440),
	FREQ_TO_DELAY_US(466),
	FREQ_TO_DELAY_US(494),
	FREQ_TO_DELAY_US(523),
	FREQ_TO_DELAY_US(554),
	FREQ_TO_DELAY_US(587),
	FREQ_TO_DELAY_US(622),
	FREQ_TO_DELAY_US(659),
	FREQ_TO_DELAY_US(698),
	FREQ_TO_DELAY_US(740),
	FREQ_TO_DELAY_US(784),
	FREQ_TO_DELAY_US(831)
};

//Now we define note durations {Quarter, Eighth, Sixteenth, Thirtysecond; Half; Whole}
#define NOTE_LEN_Q 652
#define NOTE_LEN_E (NOTE_LEN_Q/2)
#define NOTE_LEN_S (NOTE_LEN_Q/4)
#define NOTE_LEN_T (NOTE_LEN_Q/8)
#define NOTE_LEN_H (NOTE_LEN_Q*2)
#define NOTE_LEN_W (NOTE_LEN_Q*4)

//playNote struct provides the container to hold a given note in a song together
typedef struct {
	note_enum note;         //the note that is played
	uint8_t scale_pos;      //is it our upper scale or our lower scale (either 0 or 1)
	uint16_t duration_ms;   //for how long will the note be played?
	uint16_t duration_rest; //after the note, how long should we rest for?
} playNote;

//A song made up as the struct
playNote furEliseSong[] = {
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_d, 1, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_c, 0, NOTE_LEN_E, 0},
	{note_e, 0, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_e, 0, NOTE_LEN_E, 0},
	{note_g_sh, 0, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_e, 0, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_d, 1, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_c, 0, NOTE_LEN_E, 0},
	{note_e, 0, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_e, 0, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_Q, NOTE_LEN_Q}
};

//definitions finished, onto the functions to play the notes

//tx_tone takes a delay time and a play time, and will switch on and off the carrier PWM signal according to those arguments.
//this generates a tone in the PWM carrier in the AM frequency band.
void tx_tone(uint32_t dTime, uint32_t playTime) {
	uint32_t end = HAL_GetTick() + playTime;

  	while (end > HAL_GetTick()) {
	  	delay_us(dTime);
	  	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	  	delay_us(dTime);
	  	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
  	}
}

//tx_note takes a playNote structure and does the conversion into the arguments that tx_tone will take.
//firstly it transmits the note frequency (using the note_delay_us look up table) for 50 milliseconds less than requested,
//then it transmits "silence" for 50 milliseconds (this gives a gap between notes).
//Finally, if the playNote structure requests a further rest, it will extend the rest by that much amount of time.
void tx_note(playNote *n) {
	tx_tone(note_delays_us[n->note + SCALE_LEN * n->scale_pos], n->duration_ms-50);
	tx_tone(1, 50);
	if(n->duration_rest > 0) {
		tx_tone(1, n->duration_rest);
	}
}
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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //enable PWM output on LED pin

  HAL_TIM_Base_Start(&htim4); // For delay function
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  for(int i = 0; i < 35; i++) { //35 notes to send
	  		  tx_note(&furEliseSong[i]);
	  	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 35999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 2;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 17;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 3;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 2;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

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
