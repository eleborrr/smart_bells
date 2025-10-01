#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

#include "stm32f4xx_hal.h"
#include "parse_at.h"
#include "packet_handler.h"
#include "packet.h"
#include "server_endpoints.h"
#include "esp.h"

typedef enum State {
	STATE_IDLE,
	STATE_CONNECTED,
	STATE_SEND_DATA
} State;

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;

void init_state_machine();
void start_receive(UART_HandleTypeDef *huart);
void add_packet(Packet* packet);
void handle_command();
void handle_packet();

void send_command(ServerEndpoint endpoint, const void* data);

#endif
