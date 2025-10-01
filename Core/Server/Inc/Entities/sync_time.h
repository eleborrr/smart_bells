#ifndef SERVER_INC_ENTITIES_SYNC_TIME_H_
#define SERVER_INC_ENTITIES_SYNC_TIME_H_

#include "stdint.h"
#include "list.h"
#include "serialize_utils.h"

typedef struct SyncTime {
	uint8_t day;
	uint8_t month;
	uint16_t year;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} SyncTime;

void deserialize_sync_time(SyncTime* res, uint8_t** data);
void serialize_sync_time(List* res, const SyncTime* ptr);
void free_sync_time(SyncTime* ptr);

#endif /* SERVER_INC_ENTITIES_SYNC_TIME_H_ */
