/*
 * 7seg.c
 *
 *  Created on: Nov 19, 2020
 *      Author: SESA598592
 */
#include "main.h"

uint8_t seg7(uint8_t value){
	uint8_t out;
	switch(value){
		case(0):
			out = 0b1000000;
			break;
		case(1):
			out = 0b1111001;
			break;
		case(2):
			out = 0b0100100;
			break;
		case(3):
			out = 0b0110000;
			break;
		case(4):
			out = 0b0011001;
			break;
		case(5):
			out = 0b0010010;
			break;
		case(6):
			out = 0b0000010;
			break;
		case(7):
			out = 0b1111000;
			break;
		case(8):
			out = 0b0000000;
			break;
		case(9):
			out = 0b0010000;
			break;
	}
	HAL_GPIO_WritePin(HEXA_GPIO_Port, HEXA_Pin, out && 1);
	HAL_GPIO_WritePin(HEXB_GPIO_Port, HEXB_Pin, out && 2);
	HAL_GPIO_WritePin(HEXC_GPIO_Port, HEXC_Pin, out && 4);
	HAL_GPIO_WritePin(HEXD_GPIO_Port, HEXD_Pin, out && 8);
	HAL_GPIO_WritePin(HEXE_GPIO_Port, HEXE_Pin, out && 16);
	HAL_GPIO_WritePin(HEXF_GPIO_Port, HEXF_Pin, out && 32);
	HAL_GPIO_WritePin(HEXG_GPIO_Port, HEXG_Pin, out && 64);

	return (out);


}
