#include "parse_at.h"

uint8_t parse_send_data(const uint8_t* input, CommandMeta* meta) {
	uint8_t res = strchr((const char*)input, '>') != NULL;
	if (res) meta->command = CMD_SEND_DATA;
	return res;
}

uint8_t parse_ok(const uint8_t* input, CommandMeta* meta) {
	uint8_t res = strncmp((const char*)input, "OK", 2) == 0;
	if (res) meta->command = CMD_OK;
	return res;
}

uint8_t parse_connect(const uint8_t* input, CommandMeta* meta) {
    char command[8];
    unsigned int client_id;
    uint8_t res = sscanf((const char*)input, "%u,%7s", &client_id, command) == 2;
    res = res && strcmp(command, "CONNECT") == 0;
    if (res) {
    	meta->client_id = client_id;
    	meta->command = CMD_CONNECT;
    }
    return res;
}

uint8_t parse_disconnect(const uint8_t* input, CommandMeta* meta) {
    char command[7];
    unsigned int client_id;
    uint8_t res = sscanf((const char*)input, "%u,%6s", &client_id, command) == 2;
    res = res && strcmp(command, "CLOSED") == 0;
    if (res) {
    	meta->client_id = client_id;
    	meta->command = CMD_DISCONNECT;
    }
    return res;
}

uint8_t parse_data(const uint8_t* input, uint16_t input_len, CommandMeta* meta) {
    unsigned int client_id, data_len;
    int last_read_index;
    uint8_t res = sscanf((char*)input, "+IPD,%u,%u:%n", &client_id, &data_len, &last_read_index) == 2;
    if (!res || data_len == 0) return 0;
    meta->client_id = client_id;

    meta->data = get_next_list(sizeof(uint8_t));
    if (!meta->data) return 0;

    list_copy_to(meta->data, 0, input + last_read_index, data_len);

    meta->command = CMD_DATA;
    return 1;
}

void reset_command_meta(CommandMeta* meta) {
    meta->command = CMD_NONE;
    meta->client_id = 0;
    if (meta->data) {
    	free_list(meta->data);
    	meta->data = NULL;
    }
}

uint8_t parse(const uint8_t* input, uint16_t input_len, CommandMeta* meta) {
    reset_command_meta(meta);
    while (*input == '\r' || *input == '\n') {
        input++;
        input_len--;
    }

    if (parse_send_data(input, meta)) return 1;
    if (parse_ok(input, meta)) return 1;
    if (parse_connect(input, meta)) return 1;
    if (parse_disconnect(input, meta)) return 1;
    if (parse_data(input, input_len, meta)) return 1;

    return 0;
}
