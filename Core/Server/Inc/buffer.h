#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define VAL_NODE_SIZE 64
#define STRUCT_NODE_SIZE 4

typedef struct Node {
	uint8_t chunk[64];
	int start, end;
	struct Node* next;
} Node;

typedef struct Buffer {
	int length;
	uint32_t chunk_size;
	uint32_t item_size;
	Node* first;
	Node* last;
} Buffer;

Buffer* init_buf(uint32_t chunk_size, uint32_t item_size);
void free_buf(Buffer* buf);
void buffer_append(Buffer* buf, const void* item);
void buffer_drop_first(Buffer* buf, uint16_t count);


typedef struct BufferEnumerator {
	int cur_index;
	Buffer* buf;
	Node* cur_node;
} BufferEnumerator;

void start_enumerator(BufferEnumerator* enumerator, Buffer *buf);
uint8_t buffer_enumerator_move_next(BufferEnumerator* enumerator);
void* buffer_enumerator_current(BufferEnumerator* enumerator);

#endif
