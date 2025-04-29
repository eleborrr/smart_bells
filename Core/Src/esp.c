#include "esp.h"

void start_receive(UART_HandleTypeDef *huart, char* buf, size_t buf_size) {
  memset(buf, 0, strlen(buf));
  HAL_UARTEx_ReceiveToIdle_IT(&huart3, (uint8_t *)buf, buf_size);
}

uint8_t init_esp(uint8_t restore_flag)
{
	char buf_rx[150] = "";
	transmit_at("AT\r\n");
	receive_at_answer(buf_rx, 30, 100);
	if(!strstr(buf_rx, "OK"))	return 0;

	if(restore_flag)
	{
		char trash[1500] = {0,};
		HAL_Delay(100);
		transmit_at("AT+RESTORE\r\n");
		receive_at_answer(trash, 1500, 1500);

		transmit_at("AT\r\n");
		receive_at_answer(buf_rx, 30, 100);
		if(!strstr(buf_rx, "OK"))	return 0;
		HAL_Delay(100);
	}

	transmit_at("AT+CWMODE=3\r\n");
	receive_at_answer(buf_rx, 30, 200);
	if(!strstr(buf_rx, "OK"))	return 0;
	HAL_Delay(100);

	if(restore_flag)
	{
		transmit_at("AT+CIPAP=\"192.168.100.1\",\"192.168.100.1\",\"255.255.255.0\"\r\n");
		receive_at_answer(buf_rx, 150, 250);
		if(!strstr(buf_rx, "OK"))	return 0;
		HAL_Delay(100);

		transmit_at("AT+CWSAP=\"tcp_test\",\"12356890\",5,3\r\n");
		receive_at_answer(buf_rx, 150, 2500);
		if(!strstr(buf_rx, "OK"))	return 0;
		HAL_Delay(100);
	}

	transmit_at("AT+CIPMUX=1\r\n");
	receive_at_answer(buf_rx, 30, 100);
	if(!strstr(buf_rx, "OK"))	return 0;
	HAL_Delay(100);

	transmit_at("AT+CIPSERVER=1,4444\r\n");
	receive_at_answer(buf_rx, 30, 100);
	if(!strstr(buf_rx, "OK"))	return 0;

	//HAL_UART_Receive_IT(UART_ESP32, &byte, 1);

	return 1;
}

void transmit_at(char* buf_tx)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)buf_tx, strlen(buf_tx), -1);
	HAL_UART_Transmit(&huart4, (uint8_t *)buf_tx, strlen(buf_tx), -1);
}

void receive_at_answer(char* buf_rx, uint16_t len, uint16_t wait_ms)
{
	memset(buf_rx, 0, strlen(buf_rx));
	HAL_UART_Receive(&huart3,(uint8_t *)buf_rx, len, wait_ms);
	HAL_UART_Transmit(&huart4,(uint8_t *)buf_rx, strlen(buf_rx), -1);
}

void disconnecting_the_client(uint8_t client)
{
	char buf_rx[30] = "";
	transmit_at("AT+CIPCLOSE=0\r\n");
	receive_at_answer(buf_rx, 30, 100);
}

void transmit_to_client(char* buf_tx, uint8_t client)
{
	char buf_rx[30] = "";
	char tmp_str[20] = {0,};
	sprintf(tmp_str,"AT+CIPSEND=0,%d\r\n", strlen(buf_tx));
	transmit_at(tmp_str);
	receive_at_answer(buf_rx, 30, 100);
	transmit_at(buf_tx);
	receive_at_answer(buf_rx, 30, 100);
}
