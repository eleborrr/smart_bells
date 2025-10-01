#ifndef SERVER_INC_ENTITIES_EMPTY_H_
#define SERVER_INC_ENTITIES_EMPTY_H_

#include "list.h"

typedef struct Empty {} Empty;

void serialize_empty(List* res, const Empty* ptr);
void deserialize_empty(Empty* res, uint8_t** ptr);
void free_empty(Empty *ptr);

#endif
