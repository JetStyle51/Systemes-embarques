/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "queue.h"
#include "semphr.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Définition du nombre d'éléments pour les files
#define x 10 // nombre d'éléments pour la File_tapis_arrivee
#define y 10 // nombre d'éléments pour la File_depart_national et File_depart_international
#define z 10 // nombre d'éléments pour la File_tapis_relecture

// Définition du delai pour la tâche de relecture
#define DELAI_RELECTURE   500

// Définition des timeout pour les files en ms
#define TIMEOUT_FILE_TAPIS_ARRIVEE   100
#define TIMEOUT_FILE_TAPIS_RELECTURE 100
#define TIMEOUT_FILE_TAPIS_DEPART		 100  // Timeout identique en national ou international

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_arri */
osThreadId_t Task_Tache_arriHandle;
const osThreadAttr_t Task_Tache_arri_attributes = {
  .name = "Task_Tache_arri",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_lect */
osThreadId_t Task_Tache_lectHandle;
const osThreadAttr_t Task_Tache_lect_attributes = {
  .name = "Task_Tache_lect",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_rele */
osThreadId_t Task_Tache_releHandle;
const osThreadAttr_t Task_Tache_rele_attributes = {
  .name = "Task_Tache_rele",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_depa */
osThreadId_t Task_Tache_depaHandle;
const osThreadAttr_t Task_Tache_depa_attributes = {
  .name = "Task_Tache_depa",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_inte */
osThreadId_t Task_Tache_inteHandle;
const osThreadAttr_t Task_Tache_inte_attributes = {
  .name = "Task_Tache_inte",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for File_tapis_arrivee */
osMessageQueueId_t File_tapis_arriveeHandle;
const osMessageQueueAttr_t File_tapis_arrivee_attributes = {
  .name = "File_tapis_arrivee"
};
/* Definitions for File_tapis_relecture */
osMessageQueueId_t File_tapis_relectureHandle;
const osMessageQueueAttr_t File_tapis_relecture_attributes = {
  .name = "File_tapis_relecture"
};
/* Definitions for File_depart_national */
osMessageQueueId_t File_depart_nationalHandle;
const osMessageQueueAttr_t File_depart_national_attributes = {
  .name = "File_depart_national"
};
/* Definitions for File_depart_international */
osMessageQueueId_t File_depart_internationalHandle;
const osMessageQueueAttr_t File_depart_international_attributes = {
  .name = "File_depart_international"
};
/* Definitions for Mutex */
osMutexId_t MutexHandle;
const osMutexAttr_t Mutex_attributes = {
  .name = "Mutex"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void IdleTask(void *argument);
void Tache_arrivee(void *argument);
void Tache_lecture_rapide(void *argument);
void Tache_relecture(void *argument);
void Tache_depart_national(void *argument);
void Tache_depart_international(void *argument);

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of Mutex */
  MutexHandle = osMutexNew(&Mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of File_tapis_arrivee */
  File_tapis_arriveeHandle = osMessageQueueNew (10, sizeof(uint16_t), &File_tapis_arrivee_attributes);

  /* creation of File_tapis_relecture */
  File_tapis_relectureHandle = osMessageQueueNew (10, sizeof(uint16_t), &File_tapis_relecture_attributes);

  /* creation of File_depart_national */
  File_depart_nationalHandle = osMessageQueueNew (10, sizeof(uint16_t), &File_depart_national_attributes);

  /* creation of File_depart_international */
  File_depart_internationalHandle = osMessageQueueNew (10, sizeof(uint16_t), &File_depart_international_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(IdleTask, NULL, &defaultTask_attributes);

  /* creation of Task_Tache_arri */
  Task_Tache_arriHandle = osThreadNew(Tache_arrivee, NULL, &Task_Tache_arri_attributes);

  /* creation of Task_Tache_lect */
  Task_Tache_lectHandle = osThreadNew(Tache_lecture_rapide, NULL, &Task_Tache_lect_attributes);

  /* creation of Task_Tache_rele */
  Task_Tache_releHandle = osThreadNew(Tache_relecture, NULL, &Task_Tache_rele_attributes);

  /* creation of Task_Tache_depa */
  Task_Tache_depaHandle = osThreadNew(Tache_depart_national, NULL, &Task_Tache_depa_attributes);

  /* creation of Task_Tache_inte */
  Task_Tache_inteHandle = osThreadNew(Tache_depart_international, NULL, &Task_Tache_inte_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void affiche_message(char *txt, unsigned int colis){
	send_to_uart(txt);
}

void send_to_uart(char *txt){
	HAL_UART_Transmit(&huart2, txt, sizeof(txt), HAL_MAX_DELAY);

}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_IdleTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_IdleTask */
void IdleTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Tache_arrivee */
/**
* @brief Function implementing the Task_Tache_arri thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Tache_arrivee */
void Tache_arrivee(void *argument)
{
	for(;;){
		osDelay(1);
	}
  /* USER CODE END Tache_arrivee */
}

/* USER CODE BEGIN Header_Tache_lecture_rapide */
/**
* @brief Function implementing the Task_Tache_lect thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Tache_lecture_rapide */
void Tache_lecture_rapide(void *argument)
{
  /* USER CODE BEGIN Tache_lecture_rapide */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Tache_lecture_rapide */
}

/* USER CODE BEGIN Header_Tache_relecture */
/**
* @brief Function implementing the Task_Tache_rele thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Tache_relecture */
void Tache_relecture(void *argument)
{
  /* USER CODE BEGIN Tache_relecture */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Tache_relecture */
}

/* USER CODE BEGIN Header_Tache_depart_national */
/**
* @brief Function implementing the Task_Tache_depa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Tache_depart_national */
void Tache_depart_national(void *argument)
{
  /* USER CODE BEGIN Tache_depart_national */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Tache_depart_national */
}

/* USER CODE BEGIN Header_Tache_depart_international */
/**
* @brief Function implementing the Task_Tache_inte thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Tache_depart_international */
void Tache_depart_international(void *argument)
{
  /* USER CODE BEGIN Tache_depart_international */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Tache_depart_international */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
