#ifndef INC_ESP_H_
#define INC_ESP_H_

#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "list.h"

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;

uint8_t init_esp(uint8_t restore_flag);
void receive_at_answer(char* buf_rx, uint16_t len, uint16_t wait_ms);
void disconnecting_the_client(uint8_t client);
void transmit_to_client(List* bytes, uint8_t client);

#endif
