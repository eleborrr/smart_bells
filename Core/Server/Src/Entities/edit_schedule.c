#include "Entities/edit_schedule.h"

void deserialize_edit_schedule(EditSchedule* res, uint8_t** data) {
	deserialize_uint8(&res->id, data);
	deserialize_schedule(&res->schedule, data);
}

void serialize_edit_schedule(List* res, const EditSchedule* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->id, (Serializer)serialize_uint8);
	serialize_concat_helper(res, index, &ptr->schedule, (Serializer)serialize_schedule);
}

void free_edit_schedule(EditSchedule* ptr) {
	free(ptr);
}
