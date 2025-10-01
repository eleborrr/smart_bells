#include "Entities/two_bells.h"

void serialize_two_bells(List* res, const TwoBells* ptr) {
	uint32_t index = 0;
	index += serialize_concat_helper(res, index, &ptr->bell1, (Serializer)serialize_bell_settings);
	serialize_concat_helper(res, index, &ptr->bell2, (Serializer)serialize_bell_settings);
}

void deserialize_two_bells(TwoBells* res, uint8_t** ptr) {
	deserialize_bell_settings(&res->bell1, ptr);
	deserialize_bell_settings(&res->bell2, ptr);
}

void free_two_bells(TwoBells *ptr) {
	free(ptr);
}
