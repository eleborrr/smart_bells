#include "Entities/schedule.h"

void deserialize_schedule(Schedule* res, uint8_t** data) {
	deserialize_uint8(&res->hour, data);
	deserialize_uint8(&res->minutes, data);
	deserialize_uint8(&res->weekdays, data);
	deserialize_string(res->filename, data);
}

void serialize_schedule(List* res, const Schedule* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->hour, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->minutes, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->weekdays, (Serializer)serialize_uint8);
	serialize_concat_helper(res, index, &ptr->filename, (Serializer)serialize_string);
}

void free_schedule(Schedule* ptr) {
	free(ptr);
}

void deserialize_schedules_list(List* res, uint8_t** data) {
	deserialize_list(res, data, sizeof(Schedule), (Deserializer)deserialize_schedule);
}

void serialize_schedules_list(List* res, const List* ptr) {
	serialize_list(res, ptr, (Serializer)serialize_schedule);
}
