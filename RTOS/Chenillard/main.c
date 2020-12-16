/*
 * Support de cours FreeRTOS - ISEN - Octobre 2014 - Yves Auffret 
 * 
 * Mars 2013     - v1.0 : Version initiale compatible IDE Keil 4.7
 * Octobre 2014  - v1.1 : Version compatible IDE Keil 5.12 nécessite le software pack STMicroelectronics - STM32F4 series - STM32F407 - STM32F407VG
 *
 * Ce programme est basé et/ou utilise du code de:
 * - la carte STM32F4-Discovery 
 * - l'IDE Keil  
 * - la bibliothèque CMSIS d'ARM 
 * - la bibliothèque STM32 de STMicroelectronics 
 * - la version 7.1 de FreeRTOS http://www.freertos.org  
 * - la note d'application Keil concernant les traces debug (printf) http://www.keil.com/support/man/docs/ulink2/ulink2_trace_itm_viewer.htm
 * - le portage de Thomas Kindler https://github.com/thomask77/FreeRTOS_ARM_CM4F
 * - la démo de JimK http://ph-elec.com/archives/stm32f4-freertos/
 * - l'adaptation pour l'IDE Keil https://my.st.com/public/STe2ecommunities/mcu/Lists/STM32Discovery/DispForm.aspx?ID=1684
 *
 */

// includes Kernel
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// includes Standard 
#include <stdio.h>
#include <stdlib.h>

// includes carte STM32F4-Discovery
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//********************************************************
//* Debug (printf) viewer - Redirection de la sortie stdout
//********************************************************
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) 
{
  if (DEMCR & TRCENA) { while (ITM_Port32(0) == 0); ITM_Port8(0) = ch; }
  return(ch);
}


//********************************************************
//* Création d'un chenillard  
//********************************************************
void Chenillard( void *pvParameters )
{	
	static int 					 iMode   = 0;				// Initialisation de iMode
	static unsigned int  uiDelay = 500;	  	// Initialisation de uiDelay
	while(1)											
	{ 
		switch (iMode)
		{ 
			case 0:	STM_EVAL_LEDOn (LED3); STM_EVAL_LEDOff(LED4); STM_EVAL_LEDOff(LED5); STM_EVAL_LEDOff(LED6); break;
			case 1:	STM_EVAL_LEDOff(LED3); STM_EVAL_LEDOff(LED4); STM_EVAL_LEDOn (LED5); STM_EVAL_LEDOff(LED6); break;
			case 2:	STM_EVAL_LEDOff(LED3); STM_EVAL_LEDOff(LED4); STM_EVAL_LEDOff(LED5); STM_EVAL_LEDOn (LED6); break;
			case 3:	STM_EVAL_LEDOff(LED3); STM_EVAL_LEDOn (LED4); STM_EVAL_LEDOff(LED5); STM_EVAL_LEDOff(LED6); break;
			default: break;
		}
		if (++iMode == 4)  iMode   = 0;
		if (uiDelay >  100) uiDelay-= 5;
		vTaskDelay(uiDelay / portTICK_RATE_MS);			// Attente variable
	}
	// Ce code n’est jamais atteint sauf si l’on sort volontairement 
	// de la boucle infinie (break), dans ce cas on tue la tâche 
	vTaskDelete( NULL );
}

//********************************************************
//* Initialisation hardware
//********************************************************
void Init_Hardware( void )
{	
	// Mise à jour de l'horloge système
	SystemCoreClockUpdate( );
		
	/* Initialisation des 4 Leds centrales de la carte STM32F4-Discovery*/
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
}

// Main()
int main(void)
{
 	// Initialisation hardware
	Init_Hardware();
	
	printf("\n\nLancement de la demo FreeRTOS - ISEN - Octobre 2014\n\n");

	// Création d'une première tâche
	xTaskCreate( 	Chenillard, 								// Pointeur vers la fonction
								"Chenillard",								// Nom de la tâche, facilite le debug
								configMINIMAL_STACK_SIZE, 	// Taille de pile (mots)
								NULL, 											// Pas de paramètres pour la tâche
								1, 													// Niveau de priorité 1 pour la tâche (0 étant la plus faible) 
								NULL ); 										// Pas d'utilisation du task handle

	// Lance le scheduler et les taches associées 
	vTaskStartScheduler();
	// On n'arrive jamais ici sauf en cas de problèmes graves: pb allocation mémoire, débordement de pile par ex.
	while(1);
}



