/*
 * Support de cours FreeRTOS - ISEN - Octobre 2014 - YA 
 *
 * Mars 2013     - v1.0 : Version initiale compatible IDE Keil 4.7
 * Octobre 2014  - v1.1 : Version compatible IDE Keil 5.12 n�cessite le software pack STMicroelectronics - STM32F4 series - STM32F407 - STM32F407VG
 *
 * Premier programme FreeRTOS 
 *
 * Bas� sur la note d�application FR-191-AN-RB-004, 
 * 4th December 2010, Richard Barry � Real Time Engineers Ltd., 
 * ��A simple FreeRTOS demo for the Cortex-M3 using the Keil simulator�� 
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
#include <string.h>

// includes Simulateur (redirection de la sortie printf)
#include "simulateur.h"

// D�finition du nombre d'�l�ments pour les files
#define x 10 // nombre d'�l�ments pour la File_tapis_arrivee 

// D�finition du delai pour la t�che de relecture
#define DELAI_RELECTURE   500

// D�finition des timeout pour les files en ms
#define TIMEOUT_FILE_DATA   100

// Cr�ation des files
xQueueHandle file_data;

// Cr�ation du s�maphore pour la ressource partag�e
xSemaphoreHandle Semaphore;

struct struct_parametres_tache {
	unsigned char ucNumTache;
	char nomTache[10];
} parametres_tache[3] = {{0,"A"},{1,"B"},{2,"C"}};

//********************************************************
//* SORTIE DEBUG en sortie partag�e
//********************************************************

void affiche_message(char *texte, char* pvBuffer)
{
	//semaphore take
	if (xSemaphoreTake(Semaphore,(portTickType)1000/portTICK_RATE_MS)) //On prend la ressource partag�e
	{
		printf("%s : %s\n", texte,pvBuffer); // Affichage
	}
	xSemaphoreGive(Semaphore); //On rend le jeton
}

//********************************************************
//* Cr�ation de la tache acquisition
//********************************************************
// Tache Acquisition
void tacheAcquisition( void *pvParameters )
{	
	char* pvBuffer; // buffer
	
	while(1)											// Une t�che est en g�n�ral ins�r�e dans une boucle infinie
	{ 
		//printf("Begin Acquisition\n");	// Mettre ici le code de la t�che
		pvBuffer = "MessageA";
		if(!xQueueSendToBack(file_data, &pvBuffer, TIMEOUT_FILE_DATA)) // Il faudra g�rer le d�bordement et afficher un message d'erreur
		{
			printf("Echec Envoi %s !\n",pvBuffer);
		}
		pvBuffer = "MessageB";
		if(!xQueueSendToBack(file_data, &pvBuffer, TIMEOUT_FILE_DATA)) // Il faudra g�rer le d�bordement et afficher un message d'erreur
		{
			printf("Echec Envoi %s !\n",pvBuffer);
		}
		pvBuffer = "MessageC";
		if(!xQueueSendToBack(file_data, &pvBuffer, TIMEOUT_FILE_DATA)) // Il faudra g�rer le d�bordement et afficher un message d'erreur
		{
			printf("Echec Envoi %s !\n",pvBuffer);
		}
		vTaskDelay(2000);						// Attente de deux secondes : frequency 0.5Hz
	}
	// Ce code n�est jamais atteint sauf si l�on sort volontairement 
	// de la boucle infinie (break), dans ce cas on tue la t�che 
	vTaskDelete( NULL );
}

//********************************************************
//* Cr�ation de la Tache
//********************************************************
void Tache(void *pvParameters)
{
	struct struct_parametres_tache *parametre_tache = (struct struct_parametres_tache*)pvParameters;
	char* pvBuffer; // buffer de la file
	char comp[10];
	char temp[10];
	sprintf(comp,"Message%s",&nomTache.[parametres_tache -> ucNumTache]);
	sprintf(temp,"Tache%s",&nomTache.[parametres_tache -> ucNumTache]);
	printf("comp :%s\n",comp);
	while(1)											// Une t�che est en g�n�ral ins�r�e dans une boucle infinie
	{ 
		if (xQueuePeek(file_data,&pvBuffer,TIMEOUT_FILE_DATA) ==pdTRUE) //Si on re�oit quelque chose dans la file.
		{
			if (strcmp(pvBuffer,comp)==0) //Et si ce quelque chose est "MessageC"
			{
				if (xQueueReceive(file_data,&pvBuffer,TIMEOUT_FILE_DATA) ==pdTRUE) //Alors on l'efface de la file
				{
					
					affiche_message(temp,pvBuffer); //Affichage
				}
			}
		}
	}
	// Ce code n�est jamais atteint sauf si l�on sort volontairement 
	// de la boucle infinie (break), dans ce cas on tue la t�che 
	vTaskDelete( NULL );
}


// Main()
int main(void)
{
	
	portBASE_TYPE xReturned;
	char nomTache[strlen("Tache 1")];
	
	// ulTaskNumber[0] = tacheAcquisition
	// ulTaskNumber[1] = TacheA
	// ulTaskNumber[2] = TacheB
	// ulTaskNumber[3] = TacheC
	// ulTaskNumber[4] = idle task
	
	// Cr�ation des files
	file_data  			= xQueueCreate(x, sizeof(unsigned int));
	
	// Cr�ation du s�maphore pour la ressource partag�e
	Semaphore = xSemaphoreCreateMutex();
	// Cr�ation d'une premi�re t�che
	xReturned = xTaskCreate( 	tacheAcquisition, 		// Pointeur vers la fonction
								"Ma premiere tache",// Nom de la t�che, facilite le debug
								configMINIMAL_STACK_SIZE, 								// Taille de pile (mots)
								NULL, 							// Pas de param�tres pour la t�che
								1, 									// Niveau de priorit� 1 pour la t�che (0 �tant la plus faible) 
								NULL ); 						// Pas d'utilisation du task handle
	for(int i=0;i<3;i++)
	{
		sprintf(nomTache,"Tache %d",i);
		xReturned = xTaskCreate( 	Tache, 		// Pointeur vers la fonction
								nomTache,// Nom de la t�che, facilite le debug
								configMINIMAL_STACK_SIZE, 								// Taille de pile (mots)
								(void *)&parametres_tache[i], 							// Pas de param�tres pour la t�che
								0, 									// Niveau de priorit� 1 pour la t�che (0 �tant la plus faible) 
								NULL ); 						// Pas d'utilisation du task handle
	}
	// Lance le scheduler et les taches associ�es 
	vTaskStartScheduler();
	// On n'arrive jamais ici sauf en cas de probl�mes graves: pb allocation m�moire, d�bordement de pile par ex.
	while(1);
}

