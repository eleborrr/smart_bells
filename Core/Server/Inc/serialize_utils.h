#ifndef SERVER_INC_SERIALIZE_UTILS_H_
#define SERVER_INC_SERIALIZE_UTILS_H_

#include "stdint.h"
#include "buffer.h"
#include "list.h"

typedef void (*Deserializer)(void* res, uint8_t** bytes);
typedef void (*Serializer) (List* res, const void* ptr);
typedef void (*FreeFunc) (void* ptr);

void deserialize_uint32(uint32_t* res, uint8_t** bytes);
void deserialize_uint16(uint16_t* res, uint8_t** bytes);
void deserialize_uint8(uint8_t* res, uint8_t** bytes);

void deserialize_list(List* res, uint8_t** bytes, uint32_t item_size, Deserializer item_deserializer);
void deserialize_string(char* res, uint8_t** bytes);

void serialize_uint32(List* res, const uint32_t* val);
void serialize_uint16(List* res, const uint16_t* val);
void serialize_uint8(List* res, const uint8_t* val);

void serialize_list(List* res, const List* list, Serializer item_serializer);
void serialize_string(List* res, const char* list);

int serialize_concat_helper(List* dest, uint32_t index, const void* ptr, Serializer serializer);

#endif
