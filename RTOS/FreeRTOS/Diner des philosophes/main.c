/*
 * Support de cours FreeRTOS - ISEN - Octobre 2014 - YA 
 *
 * Mars 2013     - v1.0 : Version initiale compatible IDE Keil 4.7
 * Octobre 2014  - v1.1 : Version compatible IDE Keil 5.12 nécessite le software pack STMicroelectronics - STM32F4 series - STM32F407 - STM32F407VG
 *
 * Premier programme FreeRTOS 
 *
 * Basé sur la note d’application FR-191-AN-RB-004, 
 * 4th December 2010, Richard Barry – Real Time Engineers Ltd., 
 * « A simple FreeRTOS demo for the Cortex-M3 using the Keil simulator » 
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
#include <time.h>

#define NB_PHILOS 5
#define ATTENTE_MAX_MS 30

// includes Simulateur (redirection de la sortie printf)
#include "simulateur.h"

int Fourchette[5] = {1,1,1,1,1};

		// 1 la fourchette est disponible
		// 0 la fourchette est utilisée
		
///////

struct struct_parametres_tache {
	unsigned char ucNumPhilo;
	char sNomPhilo[10];
} parametres_tache[5] = {{0,"Platon"},{1,"Nietssche"},{2,"Descartes"},{3,"Spinoza"},{4,"Bidule"}};

void Philosophe( void *pvParameters )
{
	struct struct_parametres_tache *parametre_tache = (struct struct_parametres_tache*)pvParameters;
	unsigned char ucFourchetteGauche = parametres_tache -> ucNumPhilo;
	unsigned char ucFourchetteDroite = (parametres_tache -> ucNumPhilo + 1)%NB_PHILOS;
	printf("Initialisation philosophe %d %s\n",parametres_tache-> ucNumPhilo,sNomPhilo[parametres_tache -> ucNumPhilo]);
	while(1)
		if (xSemaphoreTake(Fourchette(ucFourchetteGauche), ATTENTE_MAX_MS == pdTRUE)
		{
			printf("%s a pris sa fouchette Gauche",sNomPhilo[parametres_tace -> ucNumPhilo]);
			if (xSemaphoreTake(Fourchette(ucFourchetteDroite),ATTENTE_MAX_MS) == pdTRUE)
			{
				printf("%s sa fourchette droite\n",sNomPhilo[parametres_tace -> ucNumPhilo]);
				printf("%s mange\n",sNomPhilo[parametres_tace -> ucNumPhilo]);
				xSemaphoreGive(Fourchette(ucFourchetteGauche));
				xSemaphoreGive(Fourchette(ucFourchetteDroite));
				printf("%s termine de manger\n", sNomPhilo[parametres_tace -> ucNumPhilo]);	
			}
			else
			{
				printf("%s pose sa fourchette gauche", sNomPhilo[parametres_tace -> ucNumPhilo]);
				xSemaphoreGive(Fourchette(ucFourchetteGauche));
			}
		else
		{
			printf("%s pose sa fourchette droite", sNomPhilo[parametres_tace -> ucNumPhilo]);
			xSemaphoreGive(Fourchette(ucFourchetteDroite));
		}
		printf("%s pense\n",sNomPhilo[parametres_tace -> ucNumPhilo]);
		vTaskDelay(((rand()%256)>>6)*30);
	}
		vTaskDelete(NULL);
		
}
// Main()
int main(void)
{
	
	// ulTaskNumber[0] = 1er Philo
	// ulTaskNumber[1] = 2eme Philo
	// ulTaskNumber[2] = 3eme Philo
	// ulTaskNumber[3] = 4eme Philo
	// ulTaskNumber[4] = 5eme Philo
	// ulTaskNumber[5] = idle task
	
	// Création des sémaphores
	
	for (int i=0; i<NB_PHILOS; i++) Fourchette[i] = XSemaphoreCreateMutex();
	
	// Création des philosophes
	
	for (int i=0; i<NB_PHILOS; i++)
		xTaskCreate(Philosophe, //Pointeur vers la fonction
								parametres_tache[i].sNomPhilo, // Nom de la tâche, facilite le debug
								70, // Taille de la pile (mots)
								(void *)&parametres_tache[i], //On passe i en paramètre de la tache
								1, // Niveau de priorité 1 pour la tâche (0 étant la plus faible)
								NULL ); // Pas d'utilisation du task handle
	// Lance le scheduler et les taches associées 
	vTaskStartScheduler();
	// On n'arrive jamais ici sauf en cas de problèmes graves: pb allocation mémoire, débordement de pile par ex.
	while(1);
}

