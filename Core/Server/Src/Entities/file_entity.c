#include "Entities/file_entity.h"

void deserialize_file_info(FileInfo* res, uint8_t** data) {
	deserialize_string(res->filename, data);
	deserialize_list(&res->data, data, sizeof(uint8_t), (Deserializer)deserialize_uint8);
}

void serialize_file_info(List* res, const FileInfo* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->filename, (Serializer)serialize_string);
	serialize_list(res, &ptr->data, (Serializer)serialize_uint8);
}

void free_file_info(FileInfo* ptr) {
	free(ptr);
}
