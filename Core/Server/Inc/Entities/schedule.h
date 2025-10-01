#ifndef SERVER_INC_ENTITIES_SCHEDULE_H_
#define SERVER_INC_ENTITIES_SCHEDULE_H_

#include "list.h"
#include "serialize_utils.h"

typedef enum {
	Monday = 0b100000,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
} Weekdays;

typedef struct {
	uint8_t hour;
	uint8_t minutes;
	Weekdays weekdays;
	char filename[50];
} Schedule;

void deserialize_schedule(Schedule* res, uint8_t** data);
void serialize_schedule(List* res, const Schedule* ptr);
void free_schedule(Schedule* ptr);

void deserialize_schedules_list(List* res, uint8_t** data);
void serialize_schedules_list(List* res, const List* ptr);

#endif
