#ifndef SERVER_SRC_ENTITIES_EDIT_SCHEDULE_H_
#define SERVER_SRC_ENTITIES_EDIT_SCHEDULE_H_

#include "schedule.h"

typedef struct {
	uint8_t id;
	Schedule schedule;
} EditSchedule;

void deserialize_edit_schedule(EditSchedule* res, uint8_t** data);
void serialize_edit_schedule(List* res, const EditSchedule* ptr);
void free_edit_schedule(EditSchedule* ptr);

#endif
