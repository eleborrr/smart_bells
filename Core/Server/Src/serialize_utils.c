#include "serialize_utils.h"

void parse_uint(uint32_t* res, uint8_t** bytes, uint8_t count) {
	*res = 0;
	for (uint8_t i = 0; i < count; i++)
	{
		*res |= ((uint32_t)(**bytes)) << (8 * (count - 1 - i));
		(*bytes)++;
	}

}

void deserialize_uint32(uint32_t* res, uint8_t** bytes) {
	parse_uint(res, bytes, sizeof(uint32_t));
}
void deserialize_uint16(uint16_t* res, uint8_t** bytes) {
	parse_uint(res, bytes, sizeof(uint16_t));
}
void deserialize_uint8(uint8_t* res, uint8_t** bytes) {
	parse_uint(res, bytes, sizeof(uint8_t));
}

void deserialize_list(List* res, uint8_t** bytes, uint32_t item_size, Deserializer item_deserializer) {
	res->item_size = item_size;
	res->length = 0;
	uint32_t len;
	deserialize_uint32(&len, bytes);
	for (uint32_t i = 0; i < len; i++) {
		uint8_t cur[30];
		item_deserializer(cur, bytes);
		list_copy_to(res, i, cur, 1);
	}
}
void deserialize_string(char* res, uint8_t** bytes) {
	List* t = get_next_list(sizeof(char));
	deserialize_list(t, bytes, sizeof(char), (Deserializer)deserialize_uint8);
	memcpy(res, t->items, t->item_size * t->length);
	res[t->length] = 0;
	free_list(t);
}


void serialize_uint(List* res, uint32_t val, uint8_t count) {
	for (uint8_t i = 0; i < count; i++) {
		uint8_t cur = (val >> (8 * (count - 1 - i))) & 0xff;
		list_add(res, &cur);
	}
}

void serialize_uint32(List* res, const uint32_t* val) {
	serialize_uint(res, *val, sizeof(uint32_t));
}
void serialize_uint16(List* res, const uint16_t* val) {
	serialize_uint(res, *val, sizeof(uint16_t));
}
void serialize_uint8(List* res, const uint8_t* val) {
	serialize_uint(res, *val, sizeof(uint8_t));
}

int serialize_concat_helper(List* dest, uint32_t index, const void* ptr, Serializer serializer) {
	List* res = get_next_list(sizeof(uint8_t));
	serializer(res, ptr);
	list_list_copy_to(dest, index, res);
	index = res->length;
	free_list(res);
	return index;
}
void serialize_list(List* res, const List* list, Serializer item_serializer) {
	uint32_t index = 0;

	index += serialize_concat_helper(res, index, &list->length, (Serializer)serialize_uint32);

	void* cur;
	list_foreach(list, cur) {
		index += serialize_concat_helper(res, index, cur, item_serializer);
	}
}
void serialize_string(List* res, const char* list) {
	List* t = get_next_list(sizeof(char));
	list_copy_to(t, 0, list, strlen(list));
	serialize_list(res, t, (Serializer)serialize_uint8);
}
