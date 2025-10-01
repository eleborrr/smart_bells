#ifndef SERVER_INC_ENTITIES_TWO_BELLS_H_
#define SERVER_INC_ENTITIES_TWO_BELLS_H_

#include "bell_settings.h"

typedef struct TwoBells{
	BellSettings bell1;
	BellSettings bell2;
} TwoBells;

void serialize_two_bells(List* res, const TwoBells* ptr);
void deserialize_two_bells(TwoBells* res, uint8_t** ptr);
void free_two_bells(TwoBells *ptr);

#endif
