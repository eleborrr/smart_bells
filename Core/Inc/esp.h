/*
 * esp.h
 *
 *  Created on: Dec 13, 2024
 *      Author: grey2
 */

#ifndef INC_ESP_H_
#define INC_ESP_H_

#include "stm32f4xx.h"
#include "string.h"
#include "stdio.h"

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;

void start_receive(UART_HandleTypeDef *huart, char* buf, size_t buf_size);
uint8_t init_esp(uint8_t restore_flag);
void transmit_at(char* buf_tx);
void receive_at_answer(char* buf_rx, uint16_t len, uint16_t wait_ms);
void disconnecting_the_client(uint8_t client);
void transmit_to_client(char* buf_tx, uint8_t client);

#endif /* INC_ESP_H_ */
