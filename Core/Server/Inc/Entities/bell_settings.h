#ifndef SERVER_INC_ENTITIES_BELL_SETTINGS_H_
#define SERVER_INC_ENTITIES_BELL_SETTINGS_H_

#include "stdint.h"
#include "list.h"
#include "serialize_utils.h"

typedef struct BellSettings{
	uint8_t num;
	uint8_t channel;
	uint16_t delay;
	uint16_t duration;
} BellSettings;

void serialize_bell_settings(List* res, const BellSettings* ptr);
void deserialize_bell_settings(BellSettings* res, uint8_t** ptr);
void free_bell_settings(BellSettings *ptr);

void serialize_bell_settings_list(List* res, const List* ptr);
void deserialize_bell_settings_list(List* res, uint8_t** ptr);

#endif
