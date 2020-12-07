/*
 * cpt_mod8_V1.c
 * compteur moduo 8, valeur du compteur sort sur leg2 � 0
 * delai d'incr�mentation du compteur entr� sur lese 10 switches en ms
 *
 */

#include <stdio.h> // header file for printf()
#include "io.h"
#include "alt_types.h"
#include "system.h"

 /* tempo approximative
 * 2 instructions per loop
 * NIOS II economic  18 MIPs avec clock � 195MHz => clock � 50MHz  4,6 10**6 instructions/seconde
 * => 1 instruction en 217 ns => environ 10 clock/instruction
 * 20 ns per clock cycle
 * => 400ns per loop => tempo de 400*2500*delai=1000000ns*delai = delai ms
 */

void tempo(int nb)
{
unsigned long itr, i;

		itr= nb*2500;		// pour tempo approximative
		for(i=0; i<itr;i++); // de 1 ms par nb
		
}


int main()
{
	static alt_u8 valeur = 0x00; // valeur initiale leds eteintes
	static alt_u16 delai;

	while(1)
	{
		delai= IORD(SWITCH_BASE,0);// lecture registre data du PIO SWITCH
		tempo(delai);
		if (valeur ==7)  valeur = 0;
						else valeur++;

		IOWR(CPT_LED_MOD8_BASE,0, valeur);// ecriture de valeur dans le registre DATA du PIO LED
		printf("valeur = %d\n", valeur);


	}


}
