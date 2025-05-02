#include "stm32f4xx.h"
#include "string.h"
#include "stdio.h"

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;

enum State {
	IDLE,
	CONNECTED,
	DATA_HANDLING,
	TRASH
};

enum Command {
  NONE,
  CONNECT,
  DATA,
  GETDIRS,
  FINDMIDI,
  SETTIME,
  GETTIME,
  SETNUMVAL,
  DISCONNECT
};

typedef struct {
  enum Command command;
  int client_num;
  int data_length;
  uint8_t *data;
} CommandMeta;

uint8_t parse(char* input, uint16_t input_len, CommandMeta *meta);
