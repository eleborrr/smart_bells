#include "Entities/sync_time.h"

void deserialize_sync_time(SyncTime* res, uint8_t** data) {
	deserialize_uint8(&res->day, data);
	deserialize_uint8(&res->month, data);
	deserialize_uint16(&res->year, data);
	deserialize_uint8(&res->hours, data);
	deserialize_uint8(&res->minutes, data);
	deserialize_uint8(&res->seconds, data);
}
void serialize_sync_time(List* res, const SyncTime* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->day, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->month, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->year, (Serializer)serialize_uint16);
	index += serialize_concat_helper(res, index, &ptr->hours, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &ptr->minutes, (Serializer)serialize_uint8);
	serialize_concat_helper(res, index, &ptr->seconds, (Serializer)serialize_uint8);
}
void free_sync_time(SyncTime* ptr) {
//	free(ptr);
}
