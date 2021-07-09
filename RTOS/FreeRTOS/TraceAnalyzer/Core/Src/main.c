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
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// Création du sémaphore pour la ressource partagée
xSemaphoreHandle Semaphore;
xSemaphoreHandle SemaphoreLectureRapide;
xSemaphoreHandle SemaphoreReLecture;
xSemaphoreHandle SemaphoreNational;
xSemaphoreHandle SemaphoreInternational;
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
#define TIMEOUT_FILE_TAPIS_DEPART	100  // Timeout identique en national ou international

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
/* Definitions for Task_Tache_arri */
osThreadId_t Task_Tache_arriHandle;
const osThreadAttr_t Task_Tache_arri_attributes = {
  .name = "Task_Tache_arri",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_lect */
osThreadId_t Task_Tache_lectHandle;
const osThreadAttr_t Task_Tache_lect_attributes = {
  .name = "Task_Tache_lect",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_rele */
osThreadId_t Task_Tache_releHandle;
const osThreadAttr_t Task_Tache_rele_attributes = {
  .name = "Task_Tache_rele",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_depa */
osThreadId_t Task_Tache_depaHandle;
const osThreadAttr_t Task_Tache_depa_attributes = {
  .name = "Task_Tache_depa",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task_Tache_inte */
osThreadId_t Task_Tache_inteHandle;
const osThreadAttr_t Task_Tache_inte_attributes = {
  .name = "Task_Tache_inte",
  .priority = (osPriority_t) osPriorityNormal,
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
void vApplicationIdleHook( void );
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

  vTraceEnable(TRC_START);

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

  Semaphore = xSemaphoreCreateMutex();

  SemaphoreLectureRapide = xSemaphoreCreateMutex();

  SemaphoreReLecture = xSemaphoreCreateMutex();

  SemaphoreInternational = xSemaphoreCreateMutex();

  SemaphoreNational = xSemaphoreCreateMutex();
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of File_tapis_arrivee */
  File_tapis_arriveeHandle = osMessageQueueNew (x, sizeof(unsigned int), &File_tapis_arrivee_attributes);

  /* creation of File_tapis_relecture */
  File_tapis_relectureHandle = osMessageQueueNew (y, sizeof(unsigned int), &File_tapis_relecture_attributes);

  /* creation of File_depart_national */
  File_depart_nationalHandle = osMessageQueueNew (z, sizeof(unsigned int), &File_depart_national_attributes);

  /* creation of File_depart_international */
  File_depart_internationalHandle = osMessageQueueNew (z, sizeof(unsigned int), &File_depart_international_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_Tache_arri */
  Task_Tache_arriHandle = osThreadNew(Tache_arrivee, NULL, &Task_Tache_arri_attributes);

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
void affiche_message(char *txt){
	//semaphore take
	if (xSemaphoreTake(Semaphore,(portTickType)1000/portTICK_RATE_MS)) //On prend la ressource partagée
	{
		HAL_UART_Transmit(&huart2, txt, strlen(txt), HAL_MAX_DELAY);
	}
	xSemaphoreGive(Semaphore); //On rend le jeton
}
/* USER CODE END 4 */

void vApplicationIdleHook(void)
{
	for(;;){

	}
	vTaskDelete( NULL );
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
	unsigned int liste_colis[]={ 1,  3,  1,  2,  3,  0}; // Etat des bits B2, B1 et B0 -> 0 à 3 en décimal car B2=0
	unsigned int liste_delai[]={ 5,100,200, 300,40, 500}; // Temps d'attente en ms pour le colis suivant
	unsigned int num_colis = 0; // Initilisation du numéro de colis
	unsigned int colis; // Colis (étiquette)
	char etiquette;
	char buff[] = "Le colis No 1 est depose sur le tapis roulant et il porte l'etiquette 5\r\n";
	/* creation of Task_Tache_lect */
	Task_Tache_lectHandle = osThreadNew(Tache_lecture_rapide, NULL, &Task_Tache_lect_attributes);

	for(;;){
		etiquette = liste_colis[num_colis % (sizeof(liste_colis)/sizeof(unsigned int))];
		colis = (num_colis<<3) + etiquette;
		if(!xQueueSendToBack(File_tapis_arriveeHandle, &colis, TIMEOUT_FILE_TAPIS_ARRIVEE)) // Il faudra gérer le débordement et afficher un message d'erreur
		{
			affiche_message("Debordement : Echec de l'envoi du colis\r\n");
		}
		sprintf(buff,"Le colis No %d est depose sur le tapis roulant et il porte l'etiquette %d\r\n",num_colis, etiquette);	// Il faudra gérer l'affichage comme une ressource partagée
		num_colis++;
		affiche_message(buff);
		vTaskDelay(liste_delai[num_colis % (sizeof(liste_colis)/sizeof(unsigned int))]/portTICK_RATE_MS); // Attente entre deux colis en ms

	}
	vTaskDelete( NULL );
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
  unsigned int colis; // buffer de la file
  char buff[50];
  /* Infinite loop */
  Task_Tache_inteHandle = osThreadNew(Tache_depart_international, NULL, &Task_Tache_inte_attributes);
  Task_Tache_depaHandle = osThreadNew(Tache_depart_national, NULL, &Task_Tache_depa_attributes);
  Task_Tache_lectHandle = osThreadNew(Tache_relecture, NULL, &Task_Tache_rele_attributes);
  for(;;)
  {
	  if (xQueuePeek(File_tapis_arriveeHandle,&colis,TIMEOUT_FILE_TAPIS_ARRIVEE)) //Si on reçoit quelque chose dans la file.
		{
		  if (xQueueReceive(File_tapis_arriveeHandle,&colis,TIMEOUT_FILE_TAPIS_ARRIVEE)) //Alors on l'efface de la file
			{

			  colis = colis & 0xFFFFFFFB;//Set du bit B2 à 0;

			  if (colis & 2) //Si B1 = 1 : Etiquette invisible
			  {
				  if(!xQueueSendToBack(File_tapis_relectureHandle, &colis, TIMEOUT_FILE_TAPIS_RELECTURE)) // Il faudra gérer le débordement et afficher un message d'erreur
				{
					affiche_message("Debordement : Echec de le la file relecture\r\n");
				}
			  }
			  else{ //B1=0 : Etiquette visible
				  if (colis & 1){//Traitement colis tâche national si B0 ==0
					  affiche_message("Mise sur tapis pour le national !\r\n");
					  if(!xQueueSendToBack(File_depart_nationalHandle, &colis, TIMEOUT_FILE_TAPIS_DEPART)) // Il faudra gérer le débordement et afficher un message d'erreur
						{
							affiche_message("Debordement : Echec de l'envoi du colis au national\r\n");
						}
				  }
				  else{//Traitement colis tâche international si B0==1
					  affiche_message("Mise sur tapis pour l'international !\r\n");
					  if(!xQueueSendToBack(File_depart_internationalHandle, &colis, TIMEOUT_FILE_TAPIS_DEPART)) // Il faudra gérer le débordement et afficher un message d'erreur
						{
							affiche_message("Debordement : Echec de l'envoi du colis au international\r\n");
						}
				  }
			  }


			  sprintf(buff,"Tache lecture rapide : %d\r\n",colis);
			  affiche_message(buff);
			}
		}


	  osDelay(1);
  }
  vTaskDelete( NULL );
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
	unsigned int colis; // buffer de la file
	char buff[50];
  /* Infinite loop */
  for(;;)
  {
	  if (xSemaphoreTake(SemaphoreReLecture,(portTickType)1000/portTICK_RATE_MS)) //On prend la ressource partagée
	  {
		  if (xQueuePeek(File_tapis_relectureHandle,&colis,TIMEOUT_FILE_TAPIS_RELECTURE)) //Si on reçoit quelque chose dans la file.
				{
				  if (xQueueReceive(File_tapis_relectureHandle,&colis,TIMEOUT_FILE_TAPIS_RELECTURE)) //Alors on l'efface de la file
					{
					  //Traitement colis tâche national si B0 ==0

					  //Traitement colis tâche international si B0==1

					  colis = colis | 0x0000004;//Set du bit B2 à 1;

					  colis = colis & 0xFFFFFFFD;//Set du bit B1 à 0;

					  sprintf(buff,"Tache relecture : %d\r\n",colis);

					  if(!xQueueSendToFront(File_tapis_arriveeHandle, &colis, TIMEOUT_FILE_TAPIS_ARRIVEE)) // Il faudra gérer le débordement et afficher un message d'erreur
						{
							affiche_message("Debordement : Echec de l'envoi du colis dans le retour arrivée\r\n");
						}

					  affiche_message(buff);
					}
				}
	  }
	  xSemaphoreGive(SemaphoreReLecture); //On rend le jeton
	  osDelay(1);
  }
  vTaskDelete( NULL );
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
	unsigned int pvBuffer; // buffer de la file
  /* Infinite loop */
  for(;;)
  {
	  if (xSemaphoreTake(SemaphoreNational,(portTickType)1000/portTICK_RATE_MS)) //On prend la ressource partagée
		{
		  if (xQueuePeek(File_depart_nationalHandle,&pvBuffer,TIMEOUT_FILE_TAPIS_RELECTURE)) //Si on reçoit quelque chose dans la file.
			{
			  if (xQueueReceive(File_depart_nationalHandle,&pvBuffer,TIMEOUT_FILE_TAPIS_RELECTURE)) //Alors on l'efface de la file
				{

				  affiche_message("Colis envoyé au national !\r\n");
				}
			}
		}
	  xSemaphoreGive(SemaphoreNational); //On rend le jeton
	  osDelay(1);
  }
  vTaskDelete( NULL );
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
	unsigned int pvBuffer; // buffer de la file
  /* Infinite loop */
  for(;;)
  {
	  if (xSemaphoreTake(SemaphoreInternational,(portTickType)1000/portTICK_RATE_MS)) //On prend la ressource partagée
	  	{
		  if (xQueuePeek(File_depart_internationalHandle,&pvBuffer,TIMEOUT_FILE_TAPIS_RELECTURE)) //Si on reçoit quelque chose dans la file.
			{
			  if (xQueueReceive(File_depart_internationalHandle,&pvBuffer,TIMEOUT_FILE_TAPIS_RELECTURE)) //Alors on l'efface de la file
				{

				affiche_message("Colis envoyé à l'international !\r\n");
				}
			}

	  	}
	  xSemaphoreGive(SemaphoreInternational); //On rend le jeton
	  osDelay(1);
  }
  vTaskDelete( NULL );
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
