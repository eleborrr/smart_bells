#include "esp.h"

void transmit_string_at(char* buf_tx);
void transmit_at(uint8_t* buf_tx, uint16_t size);
#define BUF_LEN 1024

uint8_t init_esp(uint8_t restore_flag)
{
	char buf_rx[150] = "";
	transmit_string_at("AT\r\n");
	receive_at_answer(buf_rx, 30, 100);
	if(!strstr(buf_rx, "OK"))	return 0;

	if(restore_flag)
	{
		char trash[1500] = {0,};
		HAL_Delay(100);
		transmit_string_at("AT+RESTORE\r\n");
		receive_at_answer(trash, 1500, 1500);

		transmit_string_at("AT\r\n");
		receive_at_answer(buf_rx, 30, 100);
		if(!strstr(buf_rx, "OK"))	return 0;
		HAL_Delay(100);
	}

	transmit_string_at("AT+CWMODE=3\r\n");
	receive_at_answer(buf_rx, 30, 200);
	if(!strstr(buf_rx, "OK"))	return 0;
	HAL_Delay(100);

	if(restore_flag)
	{
		transmit_string_at("AT+CIPAP=\"192.168.100.1\",\"192.168.100.1\",\"255.255.255.0\"\r\n");
		receive_at_answer(buf_rx, 150, 250);
		if(!strstr(buf_rx, "OK"))	return 0;
		HAL_Delay(100);

		transmit_string_at("AT+CWSAP=\"tcp_test2\",\"12356890\",5,3\r\n");
		receive_at_answer(buf_rx, 150, 2500);
		if(!strstr(buf_rx, "OK"))	return 0;
		HAL_Delay(100);
	}

	transmit_string_at("AT+CIPMUX=1\r\n");
	receive_at_answer(buf_rx, 30, 100);
	if(!strstr(buf_rx, "OK"))	return 0;
	HAL_Delay(100);

	transmit_string_at("AT+CIPSERVER=1,4444\r\n");
	receive_at_answer(buf_rx, 30, 100);
	if(!strstr(buf_rx, "OK"))	return 0;

	return 1;
}

void transmit_string_at(char* buf_tx) {
	transmit_at((uint8_t*)buf_tx, strlen(buf_tx));
}

void transmit_at(uint8_t* buf_tx, uint16_t size)
{
	HAL_UART_Transmit(&huart3, buf_tx, size, -1);
	HAL_UART_Transmit(&huart4, buf_tx, size, -1);
}

void receive_at_answer(char* buf_rx, uint16_t len, uint16_t wait_ms)
{
	memset(buf_rx, 0, len);
	HAL_UART_Receive(&huart3,(uint8_t *)buf_rx, len, wait_ms);
	HAL_UART_Transmit(&huart4, (uint8_t *)buf_rx, strlen(buf_rx), -1);
}

void disconnecting_the_client(uint8_t client)
{
	char buf_rx[30] = "";
	transmit_string_at("AT+CIPCLOSE=0\r\n");
	receive_at_answer(buf_rx, 30, 100);
}

void transmit_to_client(List* bytes, uint8_t client)
{
	char buf_rx[BUF_LEN] = "";
	char tmp_str[20] = {0,};

	sprintf(tmp_str,"AT+CIPSEND=%u,%u\r\n", client, bytes->length);
	transmit_string_at(tmp_str);
	receive_at_answer(buf_rx, BUF_LEN, 100);
	transmit_at(bytes->items, bytes->length);
	receive_at_answer(buf_rx, BUF_LEN, 100);
}
