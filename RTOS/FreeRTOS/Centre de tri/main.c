/*
 * TP Centre de tri de colis - version �tudiant
 * 4/5/2019 - YA
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

// includes Simulateur (redirection de la sortie printf)
#include "simulateur.h"

// D�finition du nombre d'�l�ments pour les files
#define x 10 // nombre d'�l�ments pour la File_tapis_arrivee 
#define y 10 // nombre d'�l�ments pour la File_depart_national et File_depart_international
#define z 10 // nombre d'�l�ments pour la File_tapis_relecture 

// D�finition du delai pour la t�che de relecture
#define DELAI_RELECTURE   500

// D�finition des timeout pour les files en ms
#define TIMEOUT_FILE_TAPIS_ARRIVEE   100
#define TIMEOUT_FILE_TAPIS_RELECTURE 100
#define TIMEOUT_FILE_TAPIS_DEPART		 100  // Timeout identique en national ou international

// Cr�ation des files
xQueueHandle File_tapis_arrivee;

// Cr�ation du s�maphore pour la ressource partag�e
xSemaphoreHandle Semaphoreprint;

//********************************************************
//* T�che arriv�e 
//*
//* R�p�te de fa�on cyclique une liste de colis � deposer
//*
//* B2=1 -> le colis est pass� par � tache-relecture �, sinon B2=0
//* B1=1 -> �tiquette non lisible sinon B1=0
//* B0=1 -> march� international / B0=0 -> march� international
//* 
//********************************************************
void tache_arrivee( void *pvParameters )
{	
	unsigned int liste_colis[]={ 1,  3,  1,  2,  3,  0}; // Etat des bits B2, B1 et B0 -> 0 � 3 en d�cimal car B2=0
	unsigned int liste_delai[]={ 5,100,200, 30,400, 50}; // Temps d'attente en ms pour le colis suivant
	unsigned int num_colis = 0; // Initilisation du num�ro de colis
	unsigned int colis; // Colis (�tiquette)
while(1)
	{ 
		colis = (num_colis<<3) + liste_colis[num_colis % (sizeof(liste_colis)/sizeof(unsigned int))];
		xQueueSendToBack(File_tapis_arrivee, &colis, TIMEOUT_FILE_TAPIS_ARRIVEE); // Il faudra g�rer le d�bordement et afficher un message d'erreur
		vTaskDelay(liste_delai[num_colis % (sizeof(liste_colis)/sizeof(unsigned int))]/portTICK_RATE_MS); // Attente entre deux colis en ms
		printf("Le colis No %d est depose sur le tapis roulant et il porte l'etiquette %d\n",num_colis, colis);	// Il faudra g�rer l'affichage comme une ressource partag�e
		num_colis++;
  }
	vTaskDelete( NULL );
}

// Main()
int main(void)
{
	// Variable d'�tat du code de retour (non utilis� pour simplifier)
	portBASE_TYPE xReturned;
	
	// ulTaskNumber[0] = tache_arrivee
	// ulTaskNumber[1] = idle task
	
	// Cr�ation des files
	File_tapis_arrivee  			= xQueueCreate(x, sizeof(unsigned int));

	// Cr�ation du s�maphore pour la ressource partag�e
	Semaphoreprint = xSemaphoreCreateMutex();
	// Cr�ation de la t�che arriv�e
	xReturned = xTaskCreate( 	tache_arrivee,// Pointeur vers la fonction
								"Tache arrivee",					// Nom de la t�che, facilite le debug
								configMINIMAL_STACK_SIZE, // Taille de pile (mots)
								NULL, 										// Pas de param�tres pour la t�che
								1, 												// Niveau de priorit� 1 pour la t�che (0 �tant la plus faible) 
								NULL ); 									// Pas d'utilisation du task handle
										// Pas d'utilisation du task handle
	// Lance le scheduler et les taches associ�es 
	vTaskStartScheduler();
	// On n'arrive jamais ici sauf en cas de probl�mes graves: pb allocation m�moire, d�bordement de pile par ex.
	while(1);
}

