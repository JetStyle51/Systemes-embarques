/*
 * uart.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Kasimashi
 */

#include "main.h"
#include "led.h"
#include "periph/uart.h"

void Send_on_UART2(UART_HandleTypeDef *huart, uint8_t buffer[], uint16_t size){

	HAL_UART_Transmit(huart, buffer, size , HAL_MAX_DELAY);
	//Clignotement();
}

void print_help(UART_HandleTypeDef *huart){
	uint8_t buffer[] = "Hello information\r\nCoucou !\r\n";
	size_t size = (uint8_t) sizeof(buffer) / sizeof(buffer[0]);
	Send_on_UART2(huart, buffer,size);
}
