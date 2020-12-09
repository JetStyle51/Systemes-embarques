/*
 * uart.h
 *
 *  Created on: Nov 19, 2020
 *      Author: SESA598592
 */

#ifndef INC_PERIPH_UART_H_
#define INC_PERIPH_UART_H_

void Send_on_UART2(UART_HandleTypeDef *huart, uint8_t buffer[], uint16_t size);
void print_help(UART_HandleTypeDef *huart);

#endif /* INC_PERIPH_UART_H_ */
