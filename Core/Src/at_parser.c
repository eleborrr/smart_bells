#include "at_parser.h"

//char *patterns[MAX_DATA_LENGTH] = {"%d,CONNECT\r\n", "%d,CLOSED\r\n", "\r\n+IPD,%d,%d:"};

uint8_t parse(char* input, uint16_t input_len, CommandMeta *meta) {
  char response_buf[2048] = ""; // буффер для ответа на AT команды

  uint8_t scan_res = sscanf(input, "%d,CONNECT\r\n", &meta->client_num) == 1;
  size_t buffer_size = strlen(input) + 1;
  char *test_input = (char*)malloc(buffer_size);
  sprintf(test_input, "%d,CONNECT\r\n", meta->client_num);
  uint8_t cmp_res = strncmp(test_input, input, strlen(test_input)) == 0;
  free(test_input);
  if (scan_res && cmp_res) {
    meta->command = CONNECT;
    return 1;
  }

  scan_res = sscanf(input, "%d,CLOSED\r\n", &meta->client_num) == 1;
  buffer_size = strlen(input) + 1;
  test_input = (char*)malloc(buffer_size);
  sprintf(test_input, "%d,CLOSED\r\n", meta->client_num);
  cmp_res = strncmp(test_input, input, strlen(test_input)) == 0;
  free(test_input);
  if (scan_res && cmp_res) {
    meta->command = DISCONNECT;
    return 1;
  }

  scan_res = sscanf(input, "+IPD,%d,%d:", &meta->client_num, &meta->data_length) == 2;
  sprintf(response_buf, "scan_res = %d\r\n", scan_res);
  transmit_to_client(response_buf, meta->client_num);

  buffer_size = strlen(input) + 1;
  test_input = (char*)malloc(buffer_size);
  sprintf(test_input, "\r\n+IPD,%d,%d:", meta->client_num, meta->data_length);
  cmp_res = strncmp(test_input, input, strlen(test_input)) == 0;

  sprintf(response_buf, "cmp_res = %d\r\n", cmp_res);
  transmit_to_client(response_buf, meta->client_num);

  sprintf(response_buf, "input = %s\r\n", input);
  transmit_to_client(response_buf, meta->client_num);

  free(test_input);
  if (scan_res && cmp_res) {
    meta->data = (uint8_t *)malloc(meta->data_length);
    memcpy(meta->data, &input[input_len - meta->data_length], meta->data_length);
    meta->command = DATA;
    return 1;
  }
  meta->command = NONE;

  sprintf(response_buf, "CLIENT %d CONNECTED\r\n", meta->client_num);
  transmit_to_client(response_buf, meta->client_num);
//  transmit_to_client(input, meta->client_num);
  return 0;
}

uint8_t parseDataCommand(){

}

uint8_t receiving = 0;

enum State state = IDLE;
//void execute(CommandMeta meta) {
//  switch (state) {
//  case IDLE:
//	  if (meta.command == CONNECT) {
//		  if(!receiving){
//			  //send
//			  // receiving = 1
//			  // transmit_to_client(0, "Client {meta.client_num} connected");
//		  }
//		  else{
//			  // receiving ...
//			  state = CONNECTED;
//			  // receiving = 0;
//		  }
//	  }
//	  break;
//  case CONNECTED:
//	  break;
//  }
//  char exec_buf[500] = "";
//  sprintf(exec_buf, "command: %d, client_num: %d, data_length: %d\r\n", meta.command, meta.client_num, meta.data_length);
//  HAL_UART_Transmit(&huart4, (uint8_t *)exec_buf, strlen(exec_buf), -1);
//}
