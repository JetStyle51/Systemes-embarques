/*
 * led.c
 *
 *  Created on: Nov 19, 2020
 *      Author: SESA598592
 */
#include "main.h"

void Clignotement(void){
/* Clignotement */
  HAL_Delay(10);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  //*((unsigned int *)0x40020014) = 0x00000020;

  HAL_Delay(10);
  //*((unsigned int *)0x40020014) = 0x00000000;
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  /* Clignotement */
}
