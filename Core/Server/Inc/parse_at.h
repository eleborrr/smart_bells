#ifndef INC_PARSE_AT_H_
#define INC_PARSE_AT_H_

#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "list.h"

typedef enum Command {
	CMD_NONE,
	CMD_CONNECT,
	CMD_DATA,
	CMD_DISCONNECT,
	CMD_SEND_DATA,
	CMD_OK
} Command;

typedef struct CommandMeta {
    Command command;
    uint8_t client_id;
    List* data;
} CommandMeta;

void reset_command_meta(CommandMeta* meta);

uint8_t parse(const uint8_t* input, uint16_t input_len, CommandMeta* meta);

#endif
