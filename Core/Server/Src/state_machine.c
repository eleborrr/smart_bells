#include "state_machine.h"

// 2КБ + AT-header
#define MAX_DATA_LENGTH 2 * 1024 + 16
uint8_t buf_rx[MAX_DATA_LENGTH];
CommandMeta meta;

void start_receive(UART_HandleTypeDef *huart) {
	HAL_UARTEx_ReceiveToIdle_IT(huart, buf_rx, MAX_DATA_LENGTH);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart == &huart3) {
		parse(buf_rx, Size, &meta);

		start_receive(&huart3);
	}
}

int arr_to_string(char *buf, const uint8_t *arr, uint16_t arr_len);

void client_connect(const CommandMeta *meta, State *state);
void client_disconnect(const CommandMeta *meta, State *state);
void handle_data(const CommandMeta *meta, State *state);

State currentState = STATE_IDLE;

typedef struct {
	State state;
	Command command;
	void (*action)(const CommandMeta *meta, State *state);
} Transition;

Transition fms[] = {
		{ STATE_IDLE, CMD_CONNECT, client_connect },
		{ STATE_CONNECTED, CMD_DISCONNECT, client_disconnect },
		{ STATE_CONNECTED, CMD_DATA, handle_data },
};
const int fms_len = sizeof(fms) / sizeof(fms[0]);

void handle_command() {
	if (meta.command == CMD_NONE)
		return;

	for (int i = 0; i < fms_len; i++) {
		if (meta.command == fms[i].command && currentState == fms[i].state) {
			fms[i].action(&meta, &currentState);
			break;
		}
	}
	reset_command_meta(&meta);
}

int arr_to_string(char *buf, const uint8_t *arr, uint16_t arr_len) {
	int used = 0;
	for (uint16_t i = 0; i < arr_len; i++) {
		used += sprintf(buf + used, "%02X ", arr[i]);
	}

	if (arr_len > 0) {
		*(buf + used - 1) = 0;
		used--;
	}

	return used;
}

void client_connect(const CommandMeta *meta, State *state) {
	char buf[14];
	int used_buf = sprintf(buf, "CONNECT(%u)\r\n", meta->client_id);
	HAL_UART_Transmit(&huart4, (uint8_t*) buf, used_buf, -1);
	*state = STATE_CONNECTED;
}

void client_disconnect(const CommandMeta *meta, State *state) {
	char buf[17];
	int used_buf = sprintf(buf, "DISCONNECT(%u)\r\n", meta->client_id);
	HAL_UART_Transmit(&huart4, (uint8_t*) buf, used_buf, -1);

	*state = STATE_IDLE;
}

Buffer *bytes, *packets;

void init_state_machine() {
	bytes = init_buf(VAL_NODE_SIZE, sizeof(uint8_t));
	packets = init_buf(STRUCT_NODE_SIZE, sizeof(Packet));
}

void handle_data(const CommandMeta *meta, State *state) {
	uint8_t* cur;
	list_foreach(meta->data, cur) {
		buffer_append(bytes, cur);
	}
	parse_packets(bytes, packets);
}

void send_command_by_endpoint_meta_data(EndpointMeta* endpoint_meta, ServerEndpoint endpoint, const void* data) {
	Packet response_packet;
	response_packet.request = endpoint;
	response_packet.payload = get_next_list(sizeof(uint8_t));
	endpoint_meta->serialize_response(response_packet.payload, data);

	List* bytes = get_packet_bytes(&response_packet);
	transmit_to_client(bytes, 0);
	if (bytes) free_list(bytes);
	free_packet(&response_packet);
}

void handle_packet() {
	BufferEnumerator e;
	start_enumerator(&e, packets);
	if (!buffer_enumerator_move_next(&e)) {
		return;
	}
	uint8_t buf[30];
	int used = sprintf((char*)buf, "Packet found\r\n");
	HAL_UART_Transmit(&huart4, buf, used, -1);
	Packet *packet = (Packet*) buffer_enumerator_current(&e);
	buffer_drop_first(packets, 1);

	const EndpointMeta *endpoint_meta = get_endpoint_meta(packet->request);
	if (endpoint_meta) {

		uint8_t request[520];
		uint8_t* items = &(packet->payload->items[0]);
		endpoint_meta->deserialize_request(request, &items);
		void *response = endpoint_meta->handler(request);
		send_command_by_endpoint_meta_data(endpoint_meta, packet->request, (const void*)response);
		if (response) endpoint_meta->free_response(response);
	}

	free_packet(packet);
}

void send_command(ServerEndpoint endpoint, const void* data) {
	if (currentState != STATE_CONNECTED) return;

	if (endpoint == SEP_SERVER_TIME){

	}

	const EndpointMeta *endpoint_meta = get_endpoint_meta(endpoint);
	if (endpoint_meta)
		send_command_by_endpoint_meta_data(endpoint_meta, endpoint, data);
}
