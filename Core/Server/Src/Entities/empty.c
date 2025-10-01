#include "Entities/empty.h"

// List* (*Serializer) (const void* ptr)
void serialize_empty(List* res, const Empty* ptr) {
}
// List* (*Deserializer) (const void* ptr)
void deserialize_empty(Empty* res, uint8_t** ptr) {
}
void free_empty(Empty *ptr) {
	free(ptr);
}
