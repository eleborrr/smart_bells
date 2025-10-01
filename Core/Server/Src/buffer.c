#include "buffer.h"

#define NODES_COUNT 150
Node nodes[NODES_COUNT];
int cur_node = 0;

Node* init_node(const Buffer* buf) {
	Node* res = &nodes[cur_node++];
	if (cur_node == NODES_COUNT) cur_node = 0;
	res->start = res->end = 0;
	res->next = NULL;
	return res;
}

void free_node(Node* node, uint8_t free_next) {
	node->start = node->end = 0;
}

Buffer* init_buf(uint32_t chunk_size, uint32_t item_size) {
	Buffer* res = malloc(sizeof(Buffer));
	res->chunk_size = chunk_size;
	res->item_size = item_size;
	res->length = 0;
	res->first = res->last = init_node(res);
	return res;
}

void free_buf(Buffer* buf) {
	buf->length = 0;
	if (buf->first) {
		free_node(buf->first, 1);
		buf->first = NULL;
	}
	buf->last = NULL;
}

void buffer_append(Buffer* buf, const void* item) {
	if (buf->last->end == buf->chunk_size) {
		Node *node = init_node(buf);
		buf->last->next = node;
		buf->last = node;
	}
	void* target = (uint8_t*)buf->last->chunk + buf->item_size * buf->last->end;
	memcpy(target, item, buf->item_size);
	buf->last->end++;
	buf->length++;
}

void buffer_drop_first(Buffer* buf, uint16_t count) {
	while (buf->first && count > 0) {
		uint16_t cur_drop = buf->first->end - buf->first->start;
		cur_drop = count < cur_drop ? count : cur_drop;

		buf->first->start += cur_drop;
		buf->length -= cur_drop;
		count -= cur_drop;

		if (buf->first->start == buf->chunk_size && buf->first != buf->last) {
			Node *tmp = buf->first;
			buf->first = buf->first->next;
			if (!buf->first)
				buf->last = NULL;
			free_node(tmp, 0);
		}
	}
}

void start_enumerator(BufferEnumerator* enumerator, Buffer *buf) {
	enumerator->buf = buf;
	enumerator->cur_node = buf->first;
	enumerator->cur_index = buf->first ? buf->first->start - 1 : -1;
}

uint8_t buffer_enumerator_move_next(BufferEnumerator *enumerator) {
	while (enumerator->cur_node) {
			enumerator->cur_index++;
		if (enumerator->cur_index < enumerator->cur_node->end) {
			return 1;
		} else {
			enumerator->cur_node = enumerator->cur_node->next;
			if (enumerator->cur_node)
				enumerator->cur_index = enumerator->cur_node->start - 1;
		}
	}
	return 0;
}

void* buffer_enumerator_current(BufferEnumerator *enumerator) {
	return (uint8_t*)enumerator->cur_node->chunk + enumerator->buf->item_size * enumerator->cur_index;
}

