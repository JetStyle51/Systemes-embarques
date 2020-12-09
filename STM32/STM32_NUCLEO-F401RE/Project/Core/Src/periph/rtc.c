/*
 * rtc.c
 *
 *  Created on: Nov 19, 2020
 *      Author: SESA598592
 */

#include "main.h"
#include "periph/uart.h"

RTC_TimeTypeDef STime;
RTC_DateTypeDef SDate;

uint8_t timeBuff[] = "00:00:00 | 00:00:00\r\n";

void date(RTC_HandleTypeDef *hrtc, UART_HandleTypeDef *huart){
	HAL_RTC_GetTime(hrtc, &STime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &SDate, RTC_FORMAT_BIN);
	sprintf(timeBuff,"%02d/%02d/%02d | %02d:%02d:%02d\r\n", SDate.Date , SDate.Month, SDate.Year ,STime.Hours, STime.Minutes, STime.Seconds);
	uint8_t size = sizeof(timeBuff);
	Send_on_UART2(huart, timeBuff , size);
}
