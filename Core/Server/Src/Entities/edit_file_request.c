#include "Entities/edit_file_request.h"

void deserialize_edit_file(EditFile* res, uint8_t** data) {
	deserialize_string(res->old_filename, data);
	deserialize_string(res->new_filename, data);
}

void serialize_edit_file(List* res, const EditFile* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->old_filename, (Serializer)serialize_string);
	serialize_concat_helper(res, index, &ptr->new_filename, (Serializer)serialize_string);
}

void free_edit_file(EditFile* ptr) {
	free(ptr);
}
