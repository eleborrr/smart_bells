#include "Entities/bell_settings.h"

void serialize_bell_settings(List* res, const BellSettings* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->num, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->channel, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->delay, (Serializer)serialize_uint16);
	serialize_concat_helper(res, index, &ptr->duration, (Serializer)serialize_uint16);
}

void deserialize_bell_settings(BellSettings* res, uint8_t** ptr) {
	deserialize_uint8(&res->num, ptr);
	deserialize_uint8(&res->channel, ptr);
	deserialize_uint16(&res->delay, ptr);
	deserialize_uint16(&res->duration, ptr);
}

void free_bell_settings(BellSettings *ptr) {
	free(ptr);
}

void serialize_bell_settings_list(List* res, const List* ptr) {
	serialize_list(res, ptr, (Serializer)serialize_bell_settings);
}

void deserialize_bell_settings_list(List* res, uint8_t** ptr) {
	deserialize_list(res, ptr, sizeof(BellSettings), deserialize_bell_settings);
}
